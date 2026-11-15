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
    UnusedImport,          // import whose members are never referenced
    ComparisonOfBoolToInt, // bool compared against a numeric literal
    EmptyFunctionBody,     // function with an empty body
    LoopNeverRuns,         // for range(a, b) with a >= b and both literal
    UnusedDecl,            // function/struct/class/view/enum/const/static never referenced
    ShiftCount,            // shift amount is a negative or >= 64 literal (well-defined mask/0 result)
    ComparisonAlwaysTrue,  // comparison of a literal against itself, or identical operands
    DuplicateCondition,    // same condition tested twice in one if/else chain
    ShadowedParameter,     // local binding shadows an enclosing parameter
    UnusedLoopVariable,    // for/parallel-for loop variable never read
    DivByZeroConst,        // division/modulo by a constant expression that evaluates to zero
    VoidValueUsed,         // value of a void call consumed as an expression
    RedundantCast,         // cast of a literal to its own type
    AssignInCondition,     // assignment used as a condition (if x = 1)
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
        case WarningKind::UnusedImport:          return "unused-import";
        case WarningKind::ComparisonOfBoolToInt: return "bool-int-compare";
        case WarningKind::EmptyFunctionBody:     return "empty-function";
        case WarningKind::LoopNeverRuns:         return "loop-never-runs";
        case WarningKind::UnusedDecl:            return "unused-decl";
        case WarningKind::ShiftCount:            return "shift-count";
        case WarningKind::ComparisonAlwaysTrue:  return "comparison-always-true";
        case WarningKind::DuplicateCondition:    return "duplicate-condition";
        case WarningKind::ShadowedParameter:     return "shadowed-parameter";
        case WarningKind::UnusedLoopVariable:    return "unused-loop-var";
        case WarningKind::DivByZeroConst:        return "div-by-zero-const";
        case WarningKind::VoidValueUsed:         return "void-value-used";
        case WarningKind::RedundantCast:         return "redundant-cast";
        case WarningKind::AssignInCondition:     return "assign-in-condition";
        case WarningKind::Count:                 break;
    }
    return "unknown";
}

// A short human description, used by `-Wlist`.
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
        case WarningKind::UnusedImport:          return "imported module is never referenced";
        case WarningKind::ComparisonOfBoolToInt: return "bool compared against an integer literal";
        case WarningKind::EmptyFunctionBody:     return "function body is empty";
        case WarningKind::LoopNeverRuns:         return "literal range makes the loop dead";
        case WarningKind::UnusedDecl:            return "declaration is never referenced";
        case WarningKind::ShiftCount:            return "shift amount is negative or >= width";
        case WarningKind::ComparisonAlwaysTrue:  return "comparison always yields the same result";
        case WarningKind::DuplicateCondition:    return "condition repeats an earlier branch";
        case WarningKind::ShadowedParameter:     return "binding shadows an enclosing parameter";
        case WarningKind::UnusedLoopVariable:    return "loop variable is never read";
        case WarningKind::DivByZeroConst:        return "division by a constant zero";
        case WarningKind::VoidValueUsed:         return "void call result is consumed";
        case WarningKind::RedundantCast:         return "cast to the value's own type";
        case WarningKind::AssignInCondition:     return "assignment used as a condition";
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
        // pass 1: collect enums, imports, and referenced top-level names
        for (const auto& decl : module.decls) {
            analyze_decl(*decl, decl->span);
        }
        // pass 2: walk declarations (types/imports are marked used here)
        for (const auto& decl : module.decls) {
            analyze_decl_body(*decl, decl->span);
        }
        // report unused imports
        for (const auto& [name, b] : import_bindings_) {
            if (!b.used) {
                report(WarningKind::UnusedImport, b.span,
                       std::format("import '{}' is never used", b.path));
            }
        }
        // report unreferenced top-level declarations
        for (const auto& [name, b] : declared_names_) {
            if (!b.used) {
                report(WarningKind::UnusedDecl, b.span,
                       std::format("{} '{}' is never referenced", b.kind, name));
            }
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
        bool is_bool = false;
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
                    report(WarningKind::UnusedLoopVariable, b.span,
                           std::format("unused loop variable '{}'", name));
                    break;
            }
        }
        scope_ = scope_->parent;
    }

    void mark_used(const std::string& name) {
        if (auto it = import_bindings_.find(name); it != import_bindings_.end()) {
            it->second.used = true;
        }
        if (auto it = declared_names_.find(name); it != declared_names_.end()) {
            if (name != current_decl_name_) {
                it->second.used = true;
            }
        }
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

    // top-level names referenced anywhere (used for unused-import detection)
    std::unordered_set<std::string> referenced_names_;
    // imports seen, keyed by the bound name
    struct ImportBinding { std::string bound_name; std::string path; SourceSpan span{}; bool used = false; };
    std::unordered_map<std::string, ImportBinding> import_bindings_;
    // top-level declarations, keyed by name (unused-decl)
    struct DeclBinding { std::string kind; SourceSpan span{}; bool used = false; };
    std::unordered_map<std::string, DeclBinding> declared_names_;
    // names of functions/methods that return void, so a value binding from them can
    // be flagged
    std::unordered_set<std::string> void_functions_;
    // name of the top-level declaration whose body is being walked; a reference to
    // it from inside itself (self-recursion) is not counted as an external use.
    std::string current_decl_name_;
    // parameter names of the function currently being analyzed (shadowed-parameter)
    std::unordered_set<std::string> param_names_;
    // integer values of top-level constants, so a divisor like `TEN` can be folded
    std::unordered_map<std::string, std::int64_t> const_int_values_;

    void analyze_decl(const ast::Decl& decl, const SourceSpan& decl_span) {
        std::visit(detail::overloaded{
            [&](const ast::ImportDecl& imp) {
                std::string bound = imp.alias ? *imp.alias : last_path_component(imp.path);
                ImportBinding b;
                b.bound_name = bound;
                b.path = imp.path;
                b.span = decl_span;
                import_bindings_[bound] = std::move(b);
            },
            [&](const ast::FnDecl& f) {
                mark_decl("function", f.name, decl_span, f.attrs);
                if (f.return_type.is_void()) {
                    void_functions_.insert(f.name);
                }
            },
            [&](const ast::StructDecl& s) {
                mark_decl("struct", s.name, decl_span, s.attrs);
            },
            [&](const ast::ViewDecl& v) {
                mark_decl("view", v.name, decl_span, v.attrs);
            },
            [&](const ast::ClassDecl& c) {
                mark_decl("class", c.name, decl_span, c.attrs);
            },
            [&](const ast::EnumDecl& e) {
                mark_decl("enum", e.name, decl_span, e.attrs);
            },
            [&](const ast::ConstDecl& c) {
                mark_decl("constant", c.name, decl_span, c.attrs);
                std::int64_t value = 0;
                if (c.value && try_literal_i64(*c.value, value)) {
                    const_int_values_.insert_or_assign(c.name, value);
                }
            },
            [&](const ast::StaticDecl& s) {
                mark_decl("global", s.name, decl_span, s.attrs);
            },
            [&](const auto&) {},
        }, decl.kind);
    }

    void mark_decl(std::string_view kind, const std::string& name, const SourceSpan& span,
                   const ast::DeclAttrs& attrs) {
        if (name.starts_with("_") || name == "main" || attrs.is_extern()) {
            return;
        }
        declared_names_.insert_or_assign(
            name, DeclBinding{.kind = std::string(kind), .span = span, .used = false});
    }

    static std::string last_path_component(const std::string& path) {
        if (auto pos = path.find_last_of("./"); pos != std::string::npos) {
            return path.substr(pos + 1);
        }
        return path;
    }

    // mark a declared type name (and any named type nested inside it) as used, so
    // a struct/view/enum referenced only from a type annotation is not reported
    // as an unused declaration.
    void mark_type_used(const Type& type) {
        std::visit(detail::overloaded{
            [&](const ArrayType& a) { if (a.element) mark_type_used(*a.element); },
            [&](const PointerType& p) { if (p.pointee) mark_type_used(*p.pointee); },
            [&](const StructType& s) {
                for (const auto& [_, t] : s.fields) {
                    if (t) mark_type_used(*t);
                }
            },
            [&](const FunctionType& f) {
                for (const auto& p : f.params) {
                    if (p) mark_type_used(*p);
                }
                if (f.ret) mark_type_used(*f.ret);
            },
            [&](const std::string& name) {
                if (auto it = declared_names_.find(name); it != declared_names_.end()) {
                    it->second.used = true;
                }
            },
            [&](const auto&) {},
        }, type.kind);
    }

    void analyze_fn(const ast::FnDecl& fn, const SourceSpan& decl_span) {
        if (!fn.has_body()) {
            return;
        }
        analyze_fn_body(fn.name, fn.params, fn.body_ref(), decl_span);
    }

    // pass-2 walk of a top-level declaration: mark referenced types, build the
    // set of parameter names (for shadowed-parameter), then analyze the body.
    void analyze_decl_body(const ast::Decl& decl, const SourceSpan& decl_span) {
        std::string saved_decl = current_decl_name_;
        std::visit(detail::overloaded{
            [&](const ast::FnDecl& f) {
                current_decl_name_ = f.name;
                mark_type_used(f.return_type);
                for (const auto& p : f.params) mark_type_used(p.type);
                analyze_fn(f, decl_span);
            },
            [&](const ast::StructDecl& s) {
                current_decl_name_ = s.name;
                for (const auto& fld : s.fields) mark_type_used(fld.type);
            },
            [&](const ast::ViewDecl& v) {
                current_decl_name_ = v.name;
                for (const auto& fld : v.fields) mark_type_used(fld.type);
            },
            [&](const ast::ClassDecl& c) {
                current_decl_name_ = c.name;
                for (const auto& fld : c.fields) mark_type_used(fld.type);
                for (const auto& m : c.methods) {
                    mark_type_used(m.return_type);
                    for (const auto& p : m.params) mark_type_used(p.type);
                    analyze_fn_body(m.name, m.params, m.body, decl_span);
                }
            },
            [&](const ast::ConstDecl& c) { mark_type_used(c.type); },
            [&](const ast::StaticDecl& s) { mark_type_used(s.type); },
            [&](const ast::TypeAliasDecl& t) { mark_type_used(t.target); },
            [&](const auto&) {},
        }, decl.kind);
        current_decl_name_ = std::move(saved_decl);
    }

    void analyze_fn_body(const std::string& name, const ast::ParamList& params,
                         const ast::StmtSuite& body, const SourceSpan& fn_span) {
        (void)name;
        if (body.stmts.empty()) {
            report(WarningKind::EmptyFunctionBody, fn_span,
                   std::format("function '{}' has an empty body", name));
        }
        SourceSpan saved_fallback = fallback_span_;
        fallback_span_ = fn_span;
        auto saved_params = std::move(param_names_);
        param_names_.clear();
        push_scope();
        for (const auto& p : params) {
            Binding b;
            b.name = p.name;
            b.kind = BindingKind::Parameter;
            b.span = fn_span;
            b.used = (p.name == "self" || p.name.starts_with("_"));
            if (auto* prim = std::get_if<PrimitiveType>(&p.type.kind)) {
                b.is_bool = (*prim == PrimitiveType::Bool);
            }
            scope_->bindings[p.name] = b;
            param_names_.insert(p.name);
        }
        analyze_suite(body);
        pop_scope(); // reports unused parameters
        param_names_ = std::move(saved_params);
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
                    check_condition_expr(*s.condition, stmt_span);
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
                if (s.iterable) {
                    analyze_expr(*s.iterable);
                    check_loop_bounds(s, stmt_span);
                }
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
        bool shadows_param = param_names_.contains(s.name);
        for (Scope* p = scope_->parent; p != nullptr; p = p->parent) {
            if (auto it = p->bindings.find(s.name); it != p->bindings.end()) {
                report(WarningKind::ShadowedVariable, span,
                       std::format("'{}' shadows an outer binding", s.name));
                break;
            }
        }
        if (shadows_param) {
            report(WarningKind::ShadowedParameter, span,
                   std::format("'{}' shadows a parameter", s.name));
        }

        if (s.init) {
            analyze_expr(*s.init);
            check_implicit_narrowing(*s.init, s.type, span, s.name);
            if (!s.type) {
                if (auto* call = std::get_if<ast::CallExpr>(&s.init->kind);
                    call && call->callee && call->callee->is<ast::IdentExpr>() &&
                    void_functions_.contains(call->callee->as<ast::IdentExpr>().name)) {
                    report(WarningKind::VoidValueUsed, span,
                           std::format("'{}' binds the result of '{}', which returns void",
                                       s.name, call->callee->as<ast::IdentExpr>().name));
                }
            }
        }
        declare(s.name, span, BindingKind::Let);
        // remember whether this binding is a bool, for bool-int-compare
        if (s.init) {
            if (auto* lit = std::get_if<ast::LiteralExpr>(&s.init->kind)) {
                if (std::holds_alternative<bool>(lit->value)) {
                    scope_->bindings[s.name].is_bool = true;
                }
            }
        }
        if (s.type) {
            if (auto* prim = std::get_if<PrimitiveType>(&s.type->kind)) {
                if (*prim == PrimitiveType::Bool) {
                    scope_->bindings[s.name].is_bool = true;
                }
            }
        }
    }

    void analyze_if(const ast::IfStmt& s, const SourceSpan& span) {
        std::vector<std::string> conditions;
        analyze_if_chain(s, span, conditions);
    }

    // walks an if / else-if / else chain, reporting a branch whose condition
    // duplicates an earlier one in the same chain.
    // shared condition checks used by if / while / for-condition sites
    void check_condition_expr(const ast::Expr& cond, const SourceSpan& span) {
        if (auto* bin = std::get_if<ast::BinaryExpr>(&cond.kind)) {
            if (bin->op == ast::BinaryExpr::Op::Assign) {
                report(WarningKind::AssignInCondition, span,
                       "assignment ('=') used as a condition; did you mean '=='?");
            }
        }
    }

    void analyze_if_chain(const ast::IfStmt& s, const SourceSpan& span,
                          std::vector<std::string>& seen) {
        if (s.condition) {
            analyze_expr(*s.condition);
            check_condition_expr(*s.condition, span);
            if (is_literal_expr(*s.condition)) {
                report(WarningKind::ConstCondition, span, "if condition is a constant");
            } else if (auto key = condition_key(*s.condition)) {
                if (std::find(seen.begin(), seen.end(), *key) != seen.end()) {
                    report(WarningKind::DuplicateCondition, span,
                           std::format("condition '{}' was already tested in this chain", *key));
                } else {
                    seen.push_back(*key);
                }
            }
        }
        if (s.then_block.stmts.empty() && !s.has_else()) {
            report(WarningKind::EmptyBlock, span, "empty if body");
        }
        push_scope();
        analyze_suite(s.then_block);
        pop_scope();
        if (s.has_else()) {
            // an `else if` is represented as an else block holding a single IfStmt;
            // continue the chain so duplicate conditions across it are caught.
            if (s.else_block->stmts.size() == 1 && s.else_block->stmts[0]->is<ast::IfStmt>()) {
                analyze_if_chain(s.else_block->stmts[0]->as<ast::IfStmt>(),
                                 s.else_block->stmts[0]->span, seen);
            } else {
                push_scope();
                analyze_suite(*s.else_block);
                pop_scope();
            }
        }
    }

    // a stable textual key for a simple condition, or nullopt when the expression
    // is too complex to compare reliably.
    [[nodiscard]] static std::optional<std::string> condition_key(const ast::Expr& expr) {
        if (auto* id = std::get_if<ast::IdentExpr>(&expr.kind)) {
            return "id:" + id->name;
        }
        if (auto* lit = std::get_if<ast::LiteralExpr>(&expr.kind)) {
            if (auto* i = std::get_if<std::int64_t>(&lit->value)) return "lit:" + std::to_string(*i);
            if (auto* u = std::get_if<std::uint64_t>(&lit->value)) return "lit:" + std::to_string(*u);
            if (auto* b = std::get_if<bool>(&lit->value)) return std::string("lit:") + (*b ? "true" : "false");
            if (auto* c = std::get_if<char32_t>(&lit->value)) return "lit:" + std::to_string(static_cast<std::int64_t>(*c));
            return std::nullopt;
        }
        if (auto* f = std::get_if<ast::FieldExpr>(&expr.kind)) {
            if (!f->base) return std::nullopt;
            auto base = condition_key(*f->base);
            if (!base) return std::nullopt;
            return "field:" + *base + "." + f->field;
        }
        if (auto* b = std::get_if<ast::BinaryExpr>(&expr.kind)) {
            if (!b->lhs || !b->rhs) return std::nullopt;
            auto l = condition_key(*b->lhs);
            auto r = condition_key(*b->rhs);
            if (!l || !r) return std::nullopt;
            return std::format("bin:{}|{}|{}", static_cast<int>(b->op), *l, *r);
        }
        if (auto* u = std::get_if<ast::UnaryExpr>(&expr.kind)) {
            if (!u->operand) return std::nullopt;
            auto inner = condition_key(*u->operand);
            if (!inner) return std::nullopt;
            return std::format("un:{}|{}", static_cast<int>(u->op), *inner);
        }
        return std::nullopt;
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
            [&](const ast::FieldExpr& e) {
                if (e.base) analyze_expr(*e.base);
                // a field access resolves the name through the struct registry, never
                // as a top-level decl, so it must not keep a same-named decl alive.
            },
            [&](const ast::CastExpr& e) {
                if (e.expr) analyze_expr(*e.expr);
                // cast of a literal to the type it already has
                if (e.expr) {
                    if (auto* lit = std::get_if<ast::LiteralExpr>(&e.expr->kind)) {
                        auto* lp = std::get_if<PrimitiveType>(&e.target_type.kind);
                        auto* sp = std::get_if<PrimitiveType>(&lit->type.kind);
                        if (lp && sp && *lp == *sp) {
                            report(WarningKind::RedundantCast, expr.span,
                                   std::format("cast to '{}' is redundant; the literal is already that type",
                                               std::string(primitive_name(*lp))));
                        }
                    }
                }
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

    // range(a, b) with both literal and a >= b is an empty loop
    void check_loop_bounds(const ast::ForStmt& s, const SourceSpan& span) {
        auto* call = std::get_if<ast::CallExpr>(&s.iterable->kind);
        if (!call || call->args.size() != 2 || !call->callee->is<ast::IdentExpr>()) {
            return;
        }
        const auto& fname = call->callee->as<ast::IdentExpr>().name;
        if (fname != "range" && fname != "rangeto") {
            return;
        }
        std::int64_t lo = 0;
        std::int64_t hi = 0;
        if (try_literal_i64(*call->args[0], lo) && try_literal_i64(*call->args[1], hi) && lo >= hi) {
            report(WarningKind::LoopNeverRuns, span,
                   std::format("range({}, {}) is empty; the loop body never runs", lo, hi));
        }
    }

    [[nodiscard]] static bool try_literal_i64(const ast::Expr& expr, std::int64_t& out) {
        if (auto* lit = std::get_if<ast::LiteralExpr>(&expr.kind)) {
            if (auto* i = std::get_if<std::int64_t>(&lit->value)) { out = *i; return true; }
            if (auto* u = std::get_if<std::uint64_t>(&lit->value)) {
                out = static_cast<std::int64_t>(*u);
                return true;
            }
            if (auto* b = std::get_if<bool>(&lit->value)) { out = *b ? 1 : 0; return true; }
        }
        if (auto* un = std::get_if<ast::UnaryExpr>(&expr.kind);
            un && un->op == ast::UnaryExpr::Op::Neg && un->operand) {
            std::int64_t inner = 0;
            if (try_literal_i64(*un->operand, inner)) { out = -inner; return true; }
        }
        return false;
    }

    // fold a constant integer expression: literals, named constants, and + - * of
    // foldable operands. used to catch division/modulo by a constant zero.
    [[nodiscard]] bool try_const_i64(const ast::Expr& expr, std::int64_t& out) const {
        if (try_literal_i64(expr, out)) {
            return true;
        }
        if (auto* id = std::get_if<ast::IdentExpr>(&expr.kind)) {
            if (auto it = const_int_values_.find(id->name); it != const_int_values_.end()) {
                out = it->second;
                return true;
            }
            return false;
        }
        auto* b = std::get_if<ast::BinaryExpr>(&expr.kind);
        if (!b || !b->lhs || !b->rhs) return false;
        std::int64_t l = 0;
        std::int64_t r = 0;
        if (!try_const_i64(*b->lhs, l) || !try_const_i64(*b->rhs, r)) return false;
        switch (b->op) {
            case ast::BinaryExpr::Op::Add: out = l + r; return true;
            case ast::BinaryExpr::Op::Sub: out = l - r; return true;
            case ast::BinaryExpr::Op::Mul: out = l * r; return true;
            case ast::BinaryExpr::Op::Shl: out = (r >= 0 && r < 64) ? (l << r) : 0; return true;
            default: return false;
        }
    }

    void analyze_binary(const ast::BinaryExpr& e, const SourceSpan& span) {
        if (e.lhs) analyze_expr(*e.lhs);
        if (e.rhs) analyze_expr(*e.rhs);

        using Op = ast::BinaryExpr::Op;

        // bool compared against an integer literal
        if (e.lhs && e.rhs) {
            auto bool_side = [](const ast::Expr& ex) -> bool {
                if (auto* lit = std::get_if<ast::LiteralExpr>(&ex.kind)) {
                    return std::holds_alternative<bool>(lit->value);
                }
                return false;
            };
            auto int_side = [](const ast::Expr& ex) -> bool {
                if (auto* lit = std::get_if<ast::LiteralExpr>(&ex.kind)) {
                    return std::holds_alternative<std::int64_t>(lit->value) ||
                           std::holds_alternative<std::uint64_t>(lit->value);
                }
                return false;
            };
            const bool cmp = e.op == Op::Eq || e.op == Op::Ne || e.op == Op::Lt ||
                             e.op == Op::Gt || e.op == Op::Le || e.op == Op::Ge;
            if (cmp && ((bool_side(*e.lhs) && int_side(*e.rhs)) ||
                        (int_side(*e.lhs) && bool_side(*e.rhs)))) {
                report(WarningKind::ComparisonOfBoolToInt, span,
                       "bool compared against an integer literal");
            } else if (cmp) {
                // ident/expr whose declared type is bool, compared with an int literal
                auto ident_is_bool = [&](const ast::Expr& ex) -> bool {
                    if (auto* id = std::get_if<ast::IdentExpr>(&ex.kind)) {
                        for (Scope* s = scope_; s != nullptr; s = s->parent) {
                            if (auto it = s->bindings.find(id->name); it != s->bindings.end()) {
                                return it->second.is_bool;
                            }
                        }
                    }
                    return false;
                };
                if ((ident_is_bool(*e.lhs) && int_side(*e.rhs)) ||
                    (int_side(*e.lhs) && ident_is_bool(*e.rhs))) {
                    report(WarningKind::ComparisonOfBoolToInt, span,
                           "bool value compared against an integer literal");
                }
            }
        }

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

        // comparison of two distinct identifiers that never change between them is
        // not provable, but a comparison of the SAME literal on both sides is: e.g.
        // 3 == 3. also catches the degenerate `<`/`>` of equal literals (always false).
        if (e.lhs && e.rhs) {
            const bool cmp = e.op == Op::Eq || e.op == Op::Ne || e.op == Op::Lt ||
                             e.op == Op::Gt || e.op == Op::Le || e.op == Op::Ge;
            if (cmp) {
                std::int64_t l = 0;
                std::int64_t r = 0;
                const bool l_const = try_const_i64(*e.lhs, l);
                const bool r_const = try_const_i64(*e.rhs, r);
                if (l_const && r_const && !(e.lhs->is<ast::IdentExpr>() && e.rhs->is<ast::IdentExpr>())) {
                    report(WarningKind::ComparisonAlwaysTrue, span,
                           std::format("comparison of two constants ({} vs {}) is always the same result", l, r));
                }
            }
        }

        // shift by a negative or >= 64 literal count (only variable shifts actually
        // mask; a literal count this large is almost always a bug)
        if ((e.op == Op::Shl || e.op == Op::Shr) && e.rhs) {
            std::int64_t count = 0;
            if (try_const_i64(*e.rhs, count) && (count < 0 || count >= 64)) {
                report(WarningKind::ShiftCount, span,
                       std::format("shift count {} is outside 0..63; the result is 0 or masked",
                                   count));
            }
        }

        // division / modulo by a constant expression that folds to zero. the literal
        // case is a hard error in codegen; a named constant or folded expr reaches
        // codegen as a non-literal and would fault at runtime, so warn here.
        if ((e.op == Op::Div || e.op == Op::Mod) && e.rhs) {
            std::int64_t divisor = 0;
            if (try_const_i64(*e.rhs, divisor) && divisor == 0) {
                report(WarningKind::DivByZeroConst, span,
                       "division/modulo by a constant that evaluates to zero");
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
