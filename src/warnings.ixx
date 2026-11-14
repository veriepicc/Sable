// Sable Programming Language
// Static warning analysis: an AST pass over a module with a registry of
// individually controllable warning kinds. Runs before codegen and never
// changes generated code; it only produces diagnostics.
//
// Default policy is "all off", so enabling nothing keeps existing behaviour
// identical. The CLI turns sets on with -Wall / -W<name>, escalates with
// -Werror, and silences with -Wnone / -Wno-<name>.

export module sable.warnings;

import std;
import sable.types;
import sable.ast;

export namespace sable::warnings {

// ============================================================================
// Warning kinds
// ============================================================================

enum class WarningKind : std::uint8_t {
    UnusedLocal,           // let/var bound but never read
    UnusedParameter,       // function parameter never read
    ShadowedVariable,      // local shadows an outer local or parameter
    UnreachableCode,       // statements after return/break/continue
    ImplicitNarrowing,     // signed value assigned to a narrower unsigned type
    SelfAssignment,        // x = x, x -= x, x /= x, x %= x
    RedundantCompare,      // x == x (always true), x != x (always false)
    ConstCondition,        // if/while condition is a literal
    EmptyBlock,            // if/while/for/loop with an empty body
    DuplicateSwitchCase,   // same case value twice
    UnreachableSwitchCase, // a case after the default
    Count,
};

[[nodiscard]] constexpr std::string_view warning_name(WarningKind kind) {
    switch (kind) {
        case WarningKind::UnusedLocal:           return "unused-local";
        case WarningKind::UnusedParameter:       return "unused-parameter";
        case WarningKind::ShadowedVariable:      return "shadowed-variable";
        case WarningKind::UnreachableCode:       return "unreachable-code";
        case WarningKind::ImplicitNarrowing:     return "implicit-narrowing";
        case WarningKind::SelfAssignment:        return "self-assignment";
        case WarningKind::RedundantCompare:      return "redundant-compare";
        case WarningKind::ConstCondition:        return "const-condition";
        case WarningKind::EmptyBlock:            return "empty-block";
        case WarningKind::DuplicateSwitchCase:   return "duplicate-switch-case";
        case WarningKind::UnreachableSwitchCase: return "unreachable-switch-case";
        case WarningKind::Count:                 break;
    }
    return "unknown";
}

// A short human description, used by `-Whelp`.
[[nodiscard]] constexpr std::string_view warning_description(WarningKind kind) {
    switch (kind) {
        case WarningKind::UnusedLocal:           return "binding is never read";
        case WarningKind::UnusedParameter:       return "parameter is never read";
        case WarningKind::ShadowedVariable:      return "binding shadows an outer one";
        case WarningKind::UnreachableCode:       return "statement after a terminator";
        case WarningKind::ImplicitNarrowing:     return "signed value assigned to narrower unsigned type";
        case WarningKind::SelfAssignment:        return "value assigned to or combined with itself";
        case WarningKind::RedundantCompare:      return "comparison that is always the same result";
        case WarningKind::ConstCondition:        return "literal condition";
        case WarningKind::EmptyBlock:            return "empty control-flow body";
        case WarningKind::DuplicateSwitchCase:   return "duplicate switch case value";
        case WarningKind::UnreachableSwitchCase: return "switch case after the default";
        case WarningKind::Count:                 break;
    }
    return "";
}

[[nodiscard]] inline std::optional<WarningKind> parse_warning_name(std::string_view name) {
    for (std::uint8_t i = 0; i < static_cast<std::uint8_t>(WarningKind::Count); ++i) {
        auto kind = static_cast<WarningKind>(i);
        if (warning_name(kind) == name) {
            return kind;
        }
    }
    return std::nullopt;
}

// ============================================================================
// Policy
// ============================================================================

enum class WarningLevel : std::uint8_t { Allow, Warn, Error };

class WarningPolicy {
public:
    void set_default(WarningLevel level) { default_level_ = level; }

    void set(WarningKind kind, WarningLevel level) {
        levels_[static_cast<std::uint8_t>(kind)] = level;
    }

    void enable_all() {
        default_level_ = WarningLevel::Warn;
        levels_.clear();
    }

    void disable_all() {
        default_level_ = WarningLevel::Allow;
        levels_.clear();
    }

    void set_all_level(WarningLevel level) {
        for (std::uint8_t i = 0; i < static_cast<std::uint8_t>(WarningKind::Count); ++i) {
            levels_[i] = level;
        }
    }

    [[nodiscard]] WarningLevel level_of(WarningKind kind) const {
        if (auto it = levels_.find(static_cast<std::uint8_t>(kind)); it != levels_.end()) {
            return it->second;
        }
        return default_level_;
    }

    [[nodiscard]] bool enabled(WarningKind kind) const {
        return level_of(kind) != WarningLevel::Allow;
    }

    [[nodiscard]] bool treats_as_error(WarningKind kind) const {
        return level_of(kind) == WarningLevel::Error;
    }

private:
    std::unordered_map<std::uint8_t, WarningLevel> levels_;
    WarningLevel default_level_ = WarningLevel::Allow;
};

// ============================================================================
// Diagnostics
// ============================================================================

struct Diagnostic {
    WarningKind kind = WarningKind::UnusedLocal;
    std::string message;
    SourceSpan span{};
    bool is_error = false;
};

struct WarningResult {
    std::vector<Diagnostic> diagnostics;
    std::vector<std::string> warnings;
    std::vector<std::string> errors;

    [[nodiscard]] bool has_errors() const noexcept { return !errors.empty(); }
};

// ============================================================================
// Analyzer
// ============================================================================

namespace detail {
template <typename... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;
} // namespace detail

class Analyzer {
public:
    explicit Analyzer(const WarningPolicy& policy) : policy_(policy) {}

    [[nodiscard]] WarningResult analyze(const ast::Module& module) {
        for (const auto& decl : module.decls) {
            analyze_decl(*decl, decl->span);
        }
        WarningResult result;
        for (auto& d : diagnostics_) {
            d.is_error = policy_.treats_as_error(d.kind);
            std::string text = std::format("{} [{}]", d.message, warning_name(d.kind));
            const bool located_here = !d.span.start.file.empty() && d.span.start.file != "<unknown>";
            std::string located = located_here
                ? std::format("{}:{}:{}: {}", d.span.start.file, d.span.start.line,
                              d.span.start.column, text)
                : text;
            if (d.is_error) {
                result.errors.push_back(located);
            } else {
                result.warnings.push_back(located);
            }
        }
        result.diagnostics = diagnostics_;
        return result;
    }

private:
    enum class BindingKind { Let, Parameter, LoopVar };

    struct Binding {
        std::string name;
        SourceSpan span{};
        BindingKind kind = BindingKind::Let;
        bool used = false;
    };

    struct Scope {
        std::unordered_map<std::string, Binding> bindings;
        Scope* parent = nullptr;
    };

    const WarningPolicy& policy_;
    std::vector<Diagnostic> diagnostics_;

    Scope* scope_ = nullptr;
    std::vector<std::unique_ptr<Scope>> scopes_;
    SourceSpan fallback_span_{};  // enclosing statement span, for expr diagnostics

    // ---- scope helpers -----------------------------------------------------

    void push_scope() {
        scopes_.push_back(std::make_unique<Scope>());
        scopes_.back()->parent = scope_;
        scope_ = scopes_.back().get();
    }

    // Report every unused Let/Parameter binding owned by the scope being closed.
    void pop_scope() {
        Scope* closing = scope_;
        for (const auto& [name, b] : closing->bindings) {
            if (b.used || name.starts_with("_") || name == "self") {
                continue;
            }
            switch (b.kind) {
                case BindingKind::Let:
                    report(WarningKind::UnusedLocal, b.span,
                           std::format("unused local '{}'", name));
                    break;
                case BindingKind::Parameter:
                    report(WarningKind::UnusedParameter, b.span,
                           std::format("unused parameter '{}'", name));
                    break;
                case BindingKind::LoopVar:
                    break; // loop variables are frequently intentional, skip
            }
        }
        scope_ = scope_->parent;
    }

    void mark_used(const std::string& name) {
        for (Scope* s = scope_; s != nullptr; s = s->parent) {
            if (auto it = s->bindings.find(name); it != s->bindings.end()) {
                it->second.used = true;
                return;
            }
        }
    }

    void report(WarningKind kind, const SourceSpan& span, std::string message) {
        if (!policy_.enabled(kind)) {
            return;
        }
        // expression spans are not populated by the parser yet; fall back to the
        // enclosing statement's span so diagnostics still point somewhere real
        // expression spans default to file "<unknown>"; fall back to the enclosing
        // statement's span so diagnostics still point somewhere real
        auto located = [](const SourceSpan& s) {
            return !s.start.file.empty() && s.start.file != "<unknown>";
        };
        const SourceSpan& effective = located(span) ? span : fallback_span_;
        diagnostics_.push_back(Diagnostic{.kind = kind, .message = std::move(message), .span = effective});
    }

    // ---- type helpers ------------------------------------------------------

    static bool is_integer_primitive(PrimitiveType p) {
        switch (p) {
            case PrimitiveType::I8: case PrimitiveType::I16: case PrimitiveType::I32:
            case PrimitiveType::I64: case PrimitiveType::I128:
            case PrimitiveType::U8: case PrimitiveType::U16: case PrimitiveType::U32:
            case PrimitiveType::U64: case PrimitiveType::U128:
                return true;
            default:
                return false;
        }
    }

    static std::size_t primitive_bits(PrimitiveType p) {
        switch (p) {
            case PrimitiveType::I8: case PrimitiveType::U8: return 8;
            case PrimitiveType::I16: case PrimitiveType::U16: return 16;
            case PrimitiveType::I32: case PrimitiveType::U32: return 32;
            case PrimitiveType::I64: case PrimitiveType::U64: return 64;
            case PrimitiveType::I128: case PrimitiveType::U128: return 128;
            default: return 0;
        }
    }

    static bool is_signed_primitive(PrimitiveType p) {
        switch (p) {
            case PrimitiveType::I8: case PrimitiveType::I16: case PrimitiveType::I32:
            case PrimitiveType::I64: case PrimitiveType::I128:
                return true;
            default:
                return false;
        }
    }

    // ---- declarations ------------------------------------------------------

    void analyze_decl(const ast::Decl& decl, const SourceSpan& decl_span) {
        std::visit(detail::overloaded{
            [&](const ast::FnDecl& fn) { analyze_fn(fn, decl_span); },
            [&](const ast::ClassDecl& cls) {
                for (const auto& m : cls.methods) {
                    analyze_fn_body(m.name, m.params, m.body, decl_span);
                }
            },
            [&](const auto&) {},
        }, decl.kind);
    }

    void analyze_fn(const ast::FnDecl& fn, const SourceSpan& decl_span) {
        if (!fn.has_body()) {
            return;
        }
        analyze_fn_body(fn.name, fn.params, fn.body_ref(), decl_span);
    }

    void analyze_fn_body(const std::string& name, const ast::ParamList& params,
                         const ast::StmtSuite& body, const SourceSpan& fn_span) {
        (void)name;
        SourceSpan saved_fallback = fallback_span_;
        fallback_span_ = fn_span;
        push_scope();
        for (const auto& p : params) {
            Binding b;
            b.name = p.name;
            b.kind = BindingKind::Parameter;
            b.span = fn_span;
            b.used = (p.name == "self" || p.name.starts_with("_"));
            scope_->bindings[p.name] = b;
        }
        analyze_suite(body);
        pop_scope(); // reports unused parameters
        fallback_span_ = saved_fallback;
    }

    // ---- statements --------------------------------------------------------

    void analyze_suite(const ast::StmtSuite& suite) {
        bool terminated = false;
        for (const auto& stmt : suite.stmts) {
            if (terminated) {
                report(WarningKind::UnreachableCode, stmt->span, "unreachable statement");
            }
            analyze_stmt(*stmt);
            if (stmt_terminates(*stmt)) {
                terminated = true;
            }
        }
    }
    [[nodiscard]] static bool stmt_terminates(const ast::Stmt& stmt) {
        return std::visit(detail::overloaded{
            [&](const ast::ReturnStmt&) { return true; },
            [&](const ast::BreakStmt&) { return true; },
            [&](const ast::ContinueStmt&) { return true; },
            [&](const ast::BlockStmt& s) {
                return !s.block.stmts.empty() && stmt_terminates(*s.block.stmts.back());
            },
            [&](const ast::IfStmt& s) {
                return s.has_else() && !s.then_block.empty() && !s.else_block->empty() &&
                       stmt_terminates(*s.then_block.back()) && stmt_terminates(*s.else_block->back());
            },
            [&](const auto&) { return false; },
        }, stmt.kind);
    }

    void analyze_stmt(const ast::Stmt& stmt) {
        const SourceSpan& stmt_span = stmt.span;
        SourceSpan saved_fallback = fallback_span_;
        fallback_span_ = stmt_span;
        std::visit(detail::overloaded{
            [&](const ast::LetStmt& s) { analyze_let(s, stmt_span); },
            [&](const ast::ExprStmt& s) { if (s.expr) analyze_expr(*s.expr); },
            [&](const ast::ReturnStmt& s) { if (s.value) analyze_expr(*s.value); },
            [&](const ast::IfStmt& s) { analyze_if(s, stmt_span); },
            [&](const ast::WhileStmt& s) {
                if (s.condition) {
                    analyze_expr(*s.condition);
                    if (is_literal_expr(*s.condition)) {
                        report(WarningKind::ConstCondition, stmt_span,
                               "while condition is a constant; loop never or always runs");
                    }
                }
                if (s.body.stmts.empty()) {
                    report(WarningKind::EmptyBlock, stmt_span, "empty while body");
                }
                push_scope();
                analyze_suite(s.body);
                pop_scope();
            },
            [&](const ast::ForStmt& s) {
                if (s.iterable) analyze_expr(*s.iterable);
                push_scope();
                declare(s.name, stmt_span, BindingKind::LoopVar);
                if (s.body.stmts.empty()) {
                    report(WarningKind::EmptyBlock, stmt_span, "empty for body");
                }
                analyze_suite(s.body);
                pop_scope();
            },
            [&](const ast::LoopStmt& s) {
                push_scope();
                if (s.body.stmts.empty()) {
                    report(WarningKind::EmptyBlock, stmt_span, "empty loop body");
                }
                analyze_suite(s.body);
                pop_scope();
            },
            [&](const ast::SwitchStmt& s) { analyze_switch(s, stmt_span); },
            [&](const ast::BlockStmt& s) {
                push_scope();
                analyze_suite(s.block.stmts);
                pop_scope();
            },
            [&](const ast::DeferStmt& s) { if (s.stmt) analyze_stmt(*s.stmt); },
            [&](const ast::ParallelForStmt& s) {
                if (s.start) analyze_expr(*s.start);
                if (s.end) analyze_expr(*s.end);
                push_scope();
                declare(s.name, stmt_span, BindingKind::LoopVar);
                analyze_suite(s.body);
                pop_scope();
            },
            [&](const auto&) {},
        }, stmt.kind);
        fallback_span_ = saved_fallback;
    }

    void analyze_let(const ast::LetStmt& s, const SourceSpan& span) {
        for (Scope* p = scope_->parent; p != nullptr; p = p->parent) {
            if (auto it = p->bindings.find(s.name); it != p->bindings.end()) {
                report(WarningKind::ShadowedVariable, span,
                       std::format("'{}' shadows an outer binding", s.name));
                break;
            }
        }

        if (s.init) {
            analyze_expr(*s.init);
            check_implicit_narrowing(*s.init, s.type, span, s.name);
        }
        declare(s.name, span, BindingKind::Let);
    }

    void analyze_if(const ast::IfStmt& s, const SourceSpan& span) {
        if (s.condition) {
            analyze_expr(*s.condition);
            if (is_literal_expr(*s.condition)) {
                report(WarningKind::ConstCondition, span, "if condition is a constant");
            }
        }
        if (s.then_block.stmts.empty() && !s.has_else()) {
            report(WarningKind::EmptyBlock, span, "empty if body");
        }
        push_scope();
        analyze_suite(s.then_block);
        pop_scope();
        if (s.has_else()) {
            push_scope();
            analyze_suite(*s.else_block);
            pop_scope();
        }
    }

    void analyze_switch(const ast::SwitchStmt& s, const SourceSpan& span) {
        if (s.subject) analyze_expr(*s.subject);
        std::unordered_set<std::string> seen;
        bool saw_default = false;
        for (const auto& c : s.cases) {
            if (saw_default) {
                report(WarningKind::UnreachableSwitchCase, c.value ? c.value->span : span,
                       "switch case is unreachable (default already matched)");
            }
            if (c.value) {
                if (auto* lit = std::get_if<ast::LiteralExpr>(&c.value->kind)) {
                    std::string key;
                    if (auto* i = std::get_if<std::int64_t>(&lit->value)) key = std::to_string(*i);
                    else if (auto* u = std::get_if<std::uint64_t>(&lit->value)) key = std::to_string(*u);
                    else if (auto* ch = std::get_if<char32_t>(&lit->value)) key = std::to_string(static_cast<std::int64_t>(*ch));
                    if (!key.empty() && !seen.insert(key).second) {
                        report(WarningKind::DuplicateSwitchCase, c.value->span,
                               std::format("duplicate switch case value {}", key));
                    }
                }
            }
            push_scope();
            analyze_suite(c.body);
            pop_scope();
        }
        if (s.has_else()) {
            push_scope();
            analyze_suite(*s.else_block);
            pop_scope();
        }
    }

    void declare(const std::string& name, const SourceSpan& span, BindingKind kind) {
        Binding b;
        b.name = name;
        b.span = span;
        b.kind = kind;
        b.used = name.starts_with("_");
        scope_->bindings.insert_or_assign(name, b);
    }

    // ---- expressions -------------------------------------------------------

    [[nodiscard]] static bool is_literal_expr(const ast::Expr& expr) {
        return std::holds_alternative<ast::LiteralExpr>(expr.kind);
    }

    void analyze_expr(const ast::Expr& expr) {
        std::visit(detail::overloaded{
            [&](const ast::LiteralExpr&) {},
            [&](const ast::IdentExpr& e) { mark_used(e.name); },
            [&](const ast::BinaryExpr& e) { analyze_binary(e, expr.span); },
            [&](const ast::UnaryExpr& e) { if (e.operand) analyze_expr(*e.operand); },
            [&](const ast::CallExpr& e) {
                if (e.callee) analyze_expr(*e.callee);
                for (const auto& a : e.args) analyze_expr(*a);
            },
            [&](const ast::IndexExpr& e) {
                if (e.base) analyze_expr(*e.base);
                if (e.index) analyze_expr(*e.index);
            },
            [&](const ast::FieldExpr& e) { if (e.base) analyze_expr(*e.base); },
            [&](const ast::CastExpr& e) {
                if (e.expr) analyze_expr(*e.expr);
            },
            [&](const ast::FStringExpr& e) {
                for (const auto& part : e.parts) {
                    if (part.expr) analyze_expr(*part.expr);
                }
            },
            [&](const ast::ArrayExpr& e) {
                for (const auto& el : e.elements) analyze_expr(*el);
            },
            [&](const ast::StructExpr& e) {
                for (const auto& [_, v] : e.fields) {
                    if (v) analyze_expr(*v);
                }
            },
            [&](const ast::IfExpr& e) {
                if (e.condition) analyze_expr(*e.condition);
                push_scope(); analyze_suite(e.then_block); pop_scope();
                if (e.has_else()) { push_scope(); analyze_suite(*e.else_block); pop_scope(); }
            },
            [&](const ast::BlockExpr& e) {
                push_scope();
                analyze_suite(e.block.stmts);
                if (e.block.result) analyze_expr(*e.block.result);
                pop_scope();
            },
            [&](const ast::SpawnExpr& e) {
                if (e.callee) analyze_expr(*e.callee);
                for (const auto& a : e.args) analyze_expr(*a);
            },
            [&](const ast::AwaitExpr& e) { if (e.handle) analyze_expr(*e.handle); },
            [&](const ast::AtomicLoadExpr& e) { if (e.ptr) analyze_expr(*e.ptr); },
            [&](const ast::AtomicStoreExpr& e) {
                if (e.ptr) analyze_expr(*e.ptr);
                if (e.value) analyze_expr(*e.value);
            },
            [&](const ast::AtomicAddExpr& e) {
                if (e.ptr) analyze_expr(*e.ptr);
                if (e.value) analyze_expr(*e.value);
            },
            [&](const ast::AtomicCompareExchangeExpr& e) {
                if (e.ptr) analyze_expr(*e.ptr);
                if (e.expected) analyze_expr(*e.expected);
                if (e.desired) analyze_expr(*e.desired);
            },
        }, expr.kind);
    }

    void analyze_binary(const ast::BinaryExpr& e, const SourceSpan& span) {
        if (e.lhs) analyze_expr(*e.lhs);
        if (e.rhs) analyze_expr(*e.rhs);

        using Op = ast::BinaryExpr::Op;
        if (e.lhs && e.rhs && e.lhs->is<ast::IdentExpr>() && e.rhs->is<ast::IdentExpr>()) {
            const auto& l = e.lhs->as<ast::IdentExpr>().name;
            const auto& r = e.rhs->as<ast::IdentExpr>().name;
            if (l == r) {
                switch (e.op) {
                    case Op::Assign: case Op::SubAssign: case Op::DivAssign: case Op::ModAssign:
                        report(WarningKind::SelfAssignment, span,
                               std::format("'{}' assigned to itself", l));
                        break;
                    case Op::Eq: case Op::Ne: case Op::Lt: case Op::Gt: case Op::Le: case Op::Ge:
                        report(WarningKind::RedundantCompare, span,
                               std::format("'{}' compared with itself is always the same result", l));
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void check_implicit_narrowing(const ast::Expr& source, const std::optional<Type>& target,
                                  const SourceSpan& span, const std::string& name) {
        if (!target || !target->is_primitive() || !source.has_resolved_type()) {
            return;
        }
        auto* tp = std::get_if<PrimitiveType>(&target->kind);
        auto* sp = std::get_if<PrimitiveType>(&source.resolved_type->kind);
        if (!tp || !sp || !is_integer_primitive(*tp) || !is_integer_primitive(*sp)) {
            return;
        }
        if (primitive_bits(*tp) >= primitive_bits(*sp)) {
            return;
        }
        // only flag a signed source narrowed into an unsigned target: that is the
        // case where a negative value silently becomes a large positive one
        if (is_signed_primitive(*sp) && !is_signed_primitive(*tp)) {
            std::string what = name.empty() ? std::string("value") : std::format("'{}'", name);
            report(WarningKind::ImplicitNarrowing, span,
                   std::format("{} is signed but assigned to unsigned {} ({}-bit) and may wrap",
                               what, warning_name(WarningKind::ImplicitNarrowing), primitive_bits(*tp)));
        }
    }
};

} // namespace sable::warnings
