#pragma once
#include <lib.h>
#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
const unsigned int CP_UTF8 = 65001;
#endif
#include <AK/Array.h>
#include <Jakt/Forward.h>
#include <stdio.h>
#include <AK/Queue.h>
namespace Jakt {
namespace jakt__prelude__static_array {
}
namespace jakt__prelude__iteration {
}
namespace jakt__prelude__string {
}
namespace jakt__prelude__operators {
enum class Ordering: u8;
}
namespace jakt__prelude__hash {
}
namespace jakt__prelude__prelude {
}
namespace jakt__arguments {
struct ArgsParser;
}
namespace jakt__platform {
struct Target;
JaktInternal::Optional<size_t> last_namespace_separator(DeprecatedString const name);





ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> add_to_each(JaktInternal::DynamicArray<DeprecatedString> const strings, DeprecatedString const prefix, DeprecatedString const suffix);


ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> platform_import_names();

}
namespace jakt__platform__unknown_path {


}
namespace jakt__path {
struct Path;
}
namespace jakt__platform__unknown_fs {
class DirectoryIterator;
ErrorOr<DeprecatedString> current_directory();

ErrorOr<void> make_directory(DeprecatedString const path);

ErrorOr<DeprecatedString> real_path(DeprecatedString const path);

}
namespace jakt__file_iterator {
class RecursiveFileIterator;
}
namespace jakt__platform__unknown_process {
struct Process;
struct ExitPollResult;
ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<size_t>,jakt__platform__unknown_process::ExitPollResult>> wait_for_some_set_of_processes_that_at_least_includes(JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::Process> const& processes);

ErrorOr<jakt__platform__unknown_process::ExitPollResult> wait_for_process(jakt__platform__unknown_process::Process const& process);

ErrorOr<jakt__platform__unknown_process::Process> start_background_process(JaktInternal::DynamicArray<DeprecatedString> const args);

ErrorOr<JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult>> poll_process_exit(jakt__platform__unknown_process::Process const& process);

ErrorOr<void> forcefully_kill_process(jakt__platform__unknown_process::Process const& process);

}
namespace build {
struct Builder;
struct ParallelExecutionPool;
}
namespace utility {
struct Span;
struct FileId;
template<typename T>
struct IterationDecision;

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> append_to_each(JaktInternal::DynamicArray<DeprecatedString> const strings, DeprecatedString const suffix);

bool is_ascii_alpha(u8 const c);

bool is_whitespace(u8 const byte);

bool is_ascii_digit(u8 const c);

bool is_ascii_alphanumeric(u8 const c);

ErrorOr<DeprecatedString> join(JaktInternal::DynamicArray<DeprecatedString> const strings, DeprecatedString const separator);

ErrorOr<void> write_to_file(DeprecatedString const data, DeprecatedString const output_filename);

bool is_ascii_octdigit(u8 const c);

[[noreturn]] void todo(DeprecatedString const message);

ErrorOr<DeprecatedString> escape_for_quotes(DeprecatedString const s);

bool is_ascii_hexdigit(u8 const c);

ErrorOr<DeprecatedString> interpret_escapes(DeprecatedString const s);

[[noreturn]] void panic(DeprecatedString const message);

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> prepend_to_each(JaktInternal::DynamicArray<DeprecatedString> const strings, DeprecatedString const prefix);

bool is_ascii_binary(u8 const c);

}
namespace error {
struct MessageSeverity;

struct JaktError;

ErrorOr<void> print_error_json(DeprecatedString const file_name, error::JaktError const error);

ErrorOr<void> print_error(DeprecatedString const file_name, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const file_contents, error::JaktError const error);

ErrorOr<void> display_message_with_span(error::MessageSeverity const severity, DeprecatedString const file_name, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const contents, DeprecatedString const message, utility::Span const span);

ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,size_t>>> gather_line_spans(JaktInternal::DynamicArray<u8> const file_contents);

ErrorOr<void> print_underline(error::MessageSeverity const severity, size_t const width, JaktInternal::Tuple<size_t,size_t> const file_span, utility::Span const error_span, size_t const line_number, size_t const largest_line_number);

ErrorOr<void> print_source_line(error::MessageSeverity const severity, JaktInternal::DynamicArray<u8> const file_contents, JaktInternal::Tuple<size_t,size_t> const file_span, utility::Span const error_span, size_t const line_number, size_t const largest_line_number);

ErrorOr<void> display_message_with_span_json(error::MessageSeverity const severity, DeprecatedString const file_name, DeprecatedString const message, utility::Span const span);

}
namespace compiler {
class Compiler;
}
namespace lexer {
struct Lexer;
struct LiteralSuffix;

struct Token;

struct LiteralPrefix;

}
namespace parser {
struct ParsedFunction;
struct ParsedGenericParameter;
struct EnumVariantPatternArgument;
struct ParsedPatternDefault;
struct ParsedExternalTraitImplementation;
struct ParsedTrait;
struct ParsedAttributeArgument;
struct ParsedExternImport;
struct CheckedQualifiers;
struct ParsedModuleImport;
struct ParsedVariable;
struct ParsedNameWithGenericParameters;
struct SumEnumVariant;
struct ParsedMatchCase;
struct ParsedRecord;
struct ParsedBlock;
struct ParsedVarDeclTuple;
struct ParsedAttribute;
struct Parser;
struct ParsedCall;
struct ParsedNamespace;
struct ParsedVarDecl;
struct ParsedName;
struct ParsedAlias;
struct ParsedMethod;
struct ParsedField;
struct ParsedParameter;
struct ParsedTypeQualifiers;
struct ValueEnumVariant;
struct VisibilityRestriction;
struct ExternalName;

struct ImportName;

struct ParsedMatchPattern;

struct Visibility;

struct ArgumentStoreLevel;

struct ParsedMatchBody;

struct ParsedCapture;

struct ParsedType;

struct InlineState;

struct ParsedTraitRequirements;

struct TypeCast;

struct DefinitionLinkage;

struct ImportList;

struct ParsedExpression;

struct FunctionLinkage;

struct UnaryOperator;

struct BinaryOperator;

struct NumericConstant;

struct ParsedStatement;

struct IncludeAction;

struct RecordType;

struct FunctionType;

ErrorOr<utility::Span> merge_spans(utility::Span const start, utility::Span const end);

f32 f64_to_f32(f64 const number);

}
namespace ids {
struct FunctionId;
struct StructId;
struct VarId;
struct ScopeId;
struct TypeId;
struct ModuleId;
struct EnumId;
struct TraitId;
}
namespace types {
struct CheckedNamespace;
class Module;
struct GenericInferences;
class TypecheckFunctions;
class CheckedProgram;
struct FunctionGenericParameter;
struct ResolvedNamespace;
struct FieldRecord;
struct CheckedCall;
struct CheckedBlock;
struct OperatorTraitImplementation;
struct LoadedModule;
struct ResolvedForallChunk;
struct SpecializedType;
class Scope;
struct CheckedVarDecl;
struct CheckedEnum;
struct CheckedStruct;
struct CheckedField;
struct CheckedParameter;
struct CheckedBinaryOperator;
struct Value;
class CheckedFunction;
class FunctionGenerics;
struct CheckedGenericParameter;
struct CheckedEnumVariantBinding;
class CheckedTrait;
struct CheckedStringLiteral;
class CheckedVariable;
struct ClassInstanceRebind;
struct CheckedUnaryOperator;

struct NumericOrStringValue;

struct FunctionGenericParameterKind;

struct Type;

struct ValueImpl;

struct BlockControlFlow;

struct CheckedMatchBody;

struct CheckedStatement;

struct CheckedEnumVariant;

struct CheckedMatchCase;

struct CheckedTypeCast;

struct NumberConstant;

struct CheckedVisibility;

struct CheckedNumericConstant;

struct CheckedCapture;

struct StructOrEnumId;

struct SafetyMode;

struct MaybeResolvedScope;

struct StringLiteral;

struct StructLikeId;

struct CheckedExpression;

struct BuiltinType;

struct CheckedTraitRequirements;

ErrorOr<DeprecatedString> comptime_format_impl(DeprecatedString const format_string, JaktInternal::ArraySlice<types::Value> const arguments, NonnullRefPtr<types::CheckedProgram> const& program);

ids::TypeId builtin(types::BuiltinType const builtin);

ids::TypeId void_type_id();

ids::TypeId unknown_type_id();

ids::TypeId never_type_id();

ErrorOr<DeprecatedString> format_value_impl(DeprecatedString const format_string, types::Value const value, NonnullRefPtr<types::CheckedProgram> const& program);

}
namespace interpreter {
class InterpreterScope;
class Interpreter;
enum class InterpretError: i32;
struct ExecutionResult;

struct Deferred;

struct StatementResult;

ErrorOr<size_t> align_of_impl(ids::TypeId const type_id, NonnullRefPtr<interpreter::Interpreter> const interpreter);

ErrorOr<size_t> size_of_impl(ids::TypeId const type_id, NonnullRefPtr<interpreter::Interpreter> const interpreter);

ErrorOr<types::Value> cast_value_to_type(types::Value const this_value, ids::TypeId const type_id, NonnullRefPtr<interpreter::Interpreter> const interpreter, bool const saturating);

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> value_to_checked_expression(types::Value const this_value, NonnullRefPtr<interpreter::Interpreter> interpreter);

}
namespace jakt__prelude__configuration {
struct UserConfiguration;
extern JaktInternal::Optional<StringView> ___jakt_get_user_configuration_value(StringView const name);

}
namespace cpp_import__common {
struct CppImportErrors;
ErrorOr<DeprecatedString> read_all(DeprecatedString const filename);


}
namespace cpp_import__none {
ErrorOr<ids::ScopeId> process_cpp_import(NonnullRefPtr<types::CheckedProgram>& program, jakt__path::Path const import_path, ids::ScopeId const scope_id, bool const is_c, JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const defines);

}
namespace typechecker {
template <typename K,typename V>struct InternalDictionaryProduct;
struct TraitImplementationDescriptor;
struct TraitImplCheck;
struct AlreadyImplementedFor;
struct ImportRestrictions;
struct Typechecker;
struct NumericOrStringValue;

struct FunctionMatchResult;

ErrorOr<JaktInternal::Dictionary<DeprecatedString,DeprecatedString>> defines_from(JaktInternal::DynamicArray<parser::IncludeAction> const actions);

}
namespace codegen {
struct ControlFlowState;
struct CodegenDebugInfo;
struct LineSpan;
struct CodeGenerator;
struct AllowedControlExits;

bool are_loop_exits_allowed(codegen::AllowedControlExits const allowed_control_exits);

bool is_return_allowed(codegen::AllowedControlExits const allowed_control_exits);

}
namespace formatter {
struct FormattedToken;
struct ReflowState;
struct Formatter;
struct Stage0;
struct State;

struct ExpressionMode;

struct BreakablePoint;

struct Entity;

void bubble_sort(JaktInternal::DynamicArray<DeprecatedString> values);

}
namespace ide {
struct JaktSymbol;
struct Mutability;

struct VarVisibility;

struct Usage;

struct VarType;

ErrorOr<ide::JaktSymbol> record_to_symbol(parser::ParsedRecord const record);

ErrorOr<ide::Usage> get_enum_variant_usage_from_type_id_and_name(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id, DeprecatedString const name);

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> completions_for_type_id(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id);

ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,ids::TypeId>>> enum_variant_fields(NonnullRefPtr<types::CheckedProgram> const program, types::CheckedEnumVariant const checked_enum_variant);

ErrorOr<DeprecatedString> get_enum_variant_signature_from_type_id_and_name(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id, DeprecatedString const name);

ErrorOr<DeprecatedString> get_type_signature(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_scope(NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<types::Scope> const scope, utility::Span const span);

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> find_dot_completions(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<utility::Span> find_definition_in_program(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<DeprecatedString> get_var_signature(NonnullRefPtr<types::CheckedProgram> const program, DeprecatedString const name, ids::TypeId const var_type_id, ide::Mutability const mutability, ide::VarType const var_type, ide::VarVisibility const visibility, JaktInternal::Optional<ids::TypeId> const struct_type_id);

ErrorOr<DeprecatedString> get_constructor_signature(NonnullRefPtr<types::CheckedProgram> const program, ids::FunctionId const function_id);

ErrorOr<utility::Span> find_type_definition_in_program(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_expression(NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<typename types::CheckedExpression> const expr, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_program(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> find_function_completions_in_scope(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::CheckedProgram> const program);

ErrorOr<JaktInternal::DynamicArray<ide::JaktSymbol>> find_symbols_in_namespace(parser::ParsedNamespace const namespace_);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_function(NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<types::CheckedFunction> const checked_function, utility::Span const span);

ErrorOr<JaktInternal::Optional<DeprecatedString>> find_typename_in_program(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<utility::Span> find_type_definition_for_type_id(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_statement(NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<typename types::CheckedStatement> const statement, utility::Span const span);

ErrorOr<DeprecatedString> get_enum_variant_signature(NonnullRefPtr<types::CheckedProgram> const program, DeprecatedString const name, ids::TypeId const type_id, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,ids::TypeId>> const variants, JaktInternal::Optional<types::NumberConstant> const number_constant);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_enum(NonnullRefPtr<types::CheckedProgram> const program, types::CheckedEnum const checked_enum, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_block(NonnullRefPtr<types::CheckedProgram> const program, types::CheckedBlock const block, utility::Span const span);

ErrorOr<ide::JaktSymbol> function_to_symbol(parser::ParsedFunction const function, DeprecatedString const kind);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_struct(NonnullRefPtr<types::CheckedProgram> const program, types::CheckedStruct const checked_struct, utility::Span const span);

ErrorOr<DeprecatedString> get_function_signature(NonnullRefPtr<types::CheckedProgram> const program, ids::FunctionId const function_id);

}
namespace project {
struct Project;
}
namespace platform {


ErrorOr<DeprecatedString> library_name_for_target(DeprecatedString const name, jakt__platform::Target const target);


}
namespace jakt__libc__io {
}
namespace repl_backend__common {
struct Style;
struct LineResult;

struct XTermColor;

struct Color;

}
namespace repl_backend__default {
struct Editor;
}
namespace repl {
struct REPL;
ErrorOr<DeprecatedString> serialize_unary_operation(types::CheckedUnaryOperator const op, DeprecatedString const expr);

ErrorOr<DeprecatedString> serialize_ast_node(NonnullRefPtr<typename types::CheckedExpression> const node);

}
namespace platform__unknown_compiler {
ErrorOr<JaktInternal::DynamicArray<DeprecatedString>> run_compiler(DeprecatedString const cxx_compiler_path, DeprecatedString const cpp_filename, DeprecatedString const output_filename, DeprecatedString const runtime_path, JaktInternal::DynamicArray<DeprecatedString> const extra_include_paths, JaktInternal::DynamicArray<DeprecatedString> const extra_lib_paths, JaktInternal::DynamicArray<DeprecatedString> const extra_link_libs, bool const optimize, JaktInternal::DynamicArray<DeprecatedString> const extra_compiler_flags, bool const use_ccache);

}
struct FormatRange;
ErrorOr<void> format_output(jakt__path::Path const file_path, JaktInternal::DynamicArray<lexer::Token> const tokens, JaktInternal::Optional<FormatRange> const format_range, bool const format_debug, bool const format_inplace);

ErrorOr<void> install(jakt__path::Path const from, jakt__path::Path const to);

ErrorOr<void> mkdir_p(jakt__path::Path const path);

ErrorOr<DeprecatedString> usage();

ErrorOr<JaktInternal::DynamicArray<jakt__path::Path>> find_with_extension(jakt__path::Path const path, DeprecatedString const extension);

ErrorOr<int> compiler_main(JaktInternal::DynamicArray<DeprecatedString> const args);

ErrorOr<DeprecatedString> help();

ErrorOr<JaktInternal::Optional<FormatRange>> parse_format_range(DeprecatedString const range, size_t const input_file_length);

ErrorOr<DeprecatedString> indent(size_t const level);

ErrorOr<int> selfhost_crosscompiler_main(JaktInternal::DynamicArray<DeprecatedString> const args);

} // namespace Jakt
