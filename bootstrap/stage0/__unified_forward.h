#pragma once
#include <lib.h>
#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
const unsigned int CP_UTF8 = 65001;
#endif
#include <AK/Array.h>
#include <Jakt/Forward.h>
#include <AK/Queue.h>
#include <stdio.h>
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
namespace jakt__prelude__class_name {
}
namespace jakt__prelude__prelude {
}
namespace jakt__arguments {
struct ArgsParser;
}
namespace jakt__compiler {
extern ErrorOr<ByteString> target_triple_string();

extern JaktInternal::Optional<StringView> user_configuration_value(StringView const name);

}
namespace jakt__platform {
struct Target;





ErrorOr<JaktInternal::DynamicArray<ByteString>> platform_import_names();

ErrorOr<JaktInternal::DynamicArray<ByteString>> add_to_each(JaktInternal::DynamicArray<ByteString> const strings, ByteString const prefix, ByteString const suffix);

JaktInternal::Optional<size_t> last_namespace_separator(ByteString const name);

}
namespace jakt__platform__unknown_path {


}
namespace jakt__path {
struct Path;
}
namespace jakt__platform__unknown_fs {
class DirectoryIterator;
ErrorOr<void> make_directory(ByteString const path);

ErrorOr<ByteString> current_directory();

ErrorOr<ByteString> real_path(ByteString const path);

}
namespace jakt__file_iterator {
class RecursiveFileIterator;
}
namespace jakt__platform__unknown_process {
struct Process;
struct ExitPollResult;
ErrorOr<jakt__platform__unknown_process::Process> start_background_process(JaktInternal::DynamicArray<ByteString> const args);

ErrorOr<JaktInternal::Optional<jakt__platform__unknown_process::ExitPollResult>> poll_process_exit(jakt__platform__unknown_process::Process const& process);

ErrorOr<jakt__platform__unknown_process::ExitPollResult> wait_for_process(jakt__platform__unknown_process::Process const& process);

ErrorOr<void> forcefully_kill_process(jakt__platform__unknown_process::Process const& process);

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<size_t>,jakt__platform__unknown_process::ExitPollResult>> wait_for_some_set_of_processes_that_at_least_includes(JaktInternal::Dictionary<size_t,jakt__platform__unknown_process::Process> const& processes);

}
namespace build {
struct ParallelExecutionPool;
struct Builder;
}
namespace jakt__platform__utility {
ErrorOr<ByteString> join(JaktInternal::DynamicArray<ByteString> const strings, ByteString const separator);

}
namespace utility {
struct Span;
struct FileId;
template<typename T>
struct IterationDecision;

[[noreturn]] void panic(ByteString const message);

[[noreturn]] void todo(ByteString const message);

ByteString to_string(JaktInternal::DynamicArray<u8> const bytes);

ByteString join(JaktInternal::DynamicArray<ByteString> const strings, ByteString const separator);

JaktInternal::DynamicArray<ByteString> prepend_to_each(JaktInternal::DynamicArray<ByteString> const strings, ByteString const prefix);

JaktInternal::DynamicArray<ByteString> append_to_each(JaktInternal::DynamicArray<ByteString> const strings, ByteString const suffix);

ErrorOr<void> write_to_file(ByteString const data, ByteString const output_filename);

ByteString escape_for_quotes(ByteString const s);

ByteString interpret_escapes(ByteString const s);

bool is_ascii_alpha(u8 const c);

bool is_ascii_digit(u8 const c);

bool is_ascii_hexdigit(u8 const c);

bool is_ascii_octdigit(u8 const c);

bool is_ascii_binary(u8 const c);

bool is_ascii_alphanumeric(u8 const c);

bool is_whitespace(u8 const byte);

}
namespace error {
struct JaktError;

struct MessageSeverity;

void print_error_json(ByteString const file_name, error::JaktError const error);

ErrorOr<void> print_error(ByteString const file_name, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const file_contents, error::JaktError const error);

void display_message_with_span_json(error::MessageSeverity const severity, ByteString const file_name, ByteString const message, utility::Span const span);

void display_message_with_span(error::MessageSeverity const severity, ByteString const file_name, JaktInternal::Optional<JaktInternal::DynamicArray<u8>> const contents, ByteString const message, utility::Span const span);

void print_source_line(error::MessageSeverity const severity, JaktInternal::DynamicArray<u8> const file_contents, JaktInternal::Tuple<size_t,size_t> const file_span, utility::Span const error_span, size_t const line_number, size_t const largest_line_number);

void print_underline(error::MessageSeverity const severity, size_t const width, JaktInternal::Tuple<size_t,size_t> const file_span, utility::Span const error_span, size_t const line_number, size_t const largest_line_number);

JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,size_t>> gather_line_spans(JaktInternal::DynamicArray<u8> const file_contents);

}
namespace compiler {
class Compiler;
}
namespace lexer {
struct Lexer;
struct Token;

struct LiteralPrefix;

struct LiteralSuffix;

}
namespace parser {
struct ParsedFunctionParameters;
struct ParsedModuleImport;
struct ParsedExternImport;
struct ParsedAlias;
struct ParsedNamespace;
struct ValueEnumVariant;
struct SumEnumVariant;
struct ParsedRecord;
struct ParsedFunction;
struct ParsedParameter;
struct ParsedName;
struct ParsedNameWithGenericParameters;
struct ParsedGenericParameter;
struct ParsedTrait;
struct ParsedExternalTraitImplementation;
struct ParsedBlock;
struct EnumVariantPatternArgument;
struct ParsedPatternDefault;
struct ParsedMatchCase;
struct ParsedVarDecl;
struct ParsedVarDeclTuple;
struct ParsedField;
struct ParsedMethod;
struct ParsedVariable;
struct ParsedCall;
struct ParsedTypeQualifiers;
struct CheckedQualifiers;
struct VisibilityRestriction;
struct ParsedAttributeArgument;
struct ParsedAttribute;
struct Parser;
struct ExternalName;

struct NumericConstant;

struct DefinitionLinkage;

struct ImportName;

struct ImportList;

struct IncludeAction;

struct RecordType;

struct FunctionType;

struct ArgumentStoreLevel;

struct InlineState;

struct ParsedTraitRequirements;

struct ParsedStatement;

struct BinaryOperator;

struct TypeCast;

struct UnaryOperator;

struct ParsedMatchPattern;

struct ParsedMatchBody;

struct ParsedCapture;

struct ParsedExpression;

struct ParsedType;

struct FunctionLinkage;

struct Visibility;

f32 f64_to_f32(f64 const number);

utility::Span merge_spans(utility::Span const start, utility::Span const end);

}
namespace ids {
struct ModuleId;
struct VarId;
struct FunctionId;
struct StructId;
struct EnumId;
struct TypeId;
struct TraitId;
struct ScopeId;
}
namespace types {
struct GenericInferences;
struct SpecializedType;
struct ResolutionMixin;
class Scope;
struct ResolvedForallChunk;
class Module;
class CheckedTrait;
struct LoadedModule;
struct CheckedNamespace;
class CheckedFunction;
class FunctionGenerics;
struct CheckedParameter;
struct FunctionGenericParameter;
class CheckedVariable;
struct CheckedVarDecl;
struct CheckedBlock;
struct FieldRecord;
struct CheckedField;
struct CheckedStruct;
struct CheckedEnum;
struct CheckedGenericParameter;
struct CheckedEnumVariantBinding;
struct CheckedStringLiteral;
struct ClassInstanceRebind;
struct OperatorTraitImplementation;
struct CheckedBinaryOperator;
struct ResolvedNamespace;
struct CheckedCall;
class CheckedProgram;
struct Value;
class TypecheckFunctions;
struct StructOrEnumId;

struct StructLikeId;

struct SafetyMode;

struct BuiltinType;

struct Type;

struct CheckedTraitRequirements;

struct MaybeResolvedScope;

struct CheckedVisibility;

struct CheckedCapture;

struct FunctionGenericParameterKind;

struct BlockControlFlow;

struct CheckedEnumVariant;

struct CheckedStatement;

struct NumberConstant;

struct CheckedNumericConstant;

struct StringLiteral;

struct CheckedTypeCast;

struct CheckedUnaryOperator;

struct CheckedMatchBody;

struct CheckedMatchCase;

struct CheckedExpression;

struct ValueImpl;

struct NumericOrStringValue;

ids::TypeId unknown_type_id();

ids::TypeId void_type_id();

ids::TypeId never_type_id();

ids::TypeId builtin(types::BuiltinType const builtin);

ErrorOr<ByteString> format_value_impl(ByteString const format_string, types::Value const value, NonnullRefPtr<types::CheckedProgram> const& program);

ErrorOr<ByteString> comptime_format_impl(ByteString const format_string, JaktInternal::ArraySlice<types::Value> const arguments, NonnullRefPtr<types::CheckedProgram> const& program);

}
namespace interpreter {
class InterpreterScope;
class Interpreter;
enum class InterpretError: i32;
struct Deferred;

struct ExecutionResult;

struct StatementResult;

ErrorOr<size_t> align_of_impl(ids::TypeId const type_id, NonnullRefPtr<interpreter::Interpreter> const interpreter);

ErrorOr<size_t> size_of_impl(ids::TypeId const type_id, NonnullRefPtr<interpreter::Interpreter> const interpreter);

ErrorOr<types::Value> cast_value_to_type(types::Value const this_value, ids::TypeId const type_id, NonnullRefPtr<interpreter::Interpreter> const interpreter, bool const saturating);

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> value_to_checked_expression(types::Value const this_value, NonnullRefPtr<interpreter::Interpreter> interpreter);

}
namespace jakt__prelude__configuration {
struct UserConfiguration;
}
namespace cpp_import__common {
struct CppImportErrors;

ErrorOr<ByteString> read_all(ByteString const filename);

}
namespace cpp_import__none {
struct CppImportProcessor;
}
namespace typechecker {
struct TraitImplementationDescriptor;
struct ImportRestrictions;
template <typename K,typename V>struct InternalDictionaryProduct;
struct Typechecker;
struct AlreadyImplementedFor;
struct TraitImplCheck;
struct FunctionMatchResult;

struct BreakContinueLegalityTracker;

struct ReturnLegalityTracker;

struct NumericOrStringValue;

ErrorOr<JaktInternal::Dictionary<ByteString,ByteString>> defines_from(JaktInternal::DynamicArray<parser::IncludeAction> const actions);

ErrorOr<void> dump_scope(ids::ScopeId const scope_id, NonnullRefPtr<types::CheckedProgram> const& program, i64 const indent);

}
namespace codegen {
struct ControlFlowState;
struct LineSpan;
struct CodegenDebugInfo;
struct CodeGenerator;
struct AllowedControlExits;

bool are_loop_exits_allowed(codegen::AllowedControlExits const allowed_control_exits);

bool is_return_allowed(codegen::AllowedControlExits const allowed_control_exits);

}
namespace formatter {
struct FormattedToken;
struct Stage0;
struct ReflowState;
struct Formatter;
struct Entity;

struct ExpressionMode;

struct State;

struct BreakablePoint;

void bubble_sort(JaktInternal::DynamicArray<ByteString> values);

}
namespace ide {
struct JaktSymbol;
struct Mutability;

struct VarType;

struct VarVisibility;

struct Usage;

ErrorOr<JaktInternal::DynamicArray<ide::JaktSymbol>> find_symbols_in_namespace(parser::ParsedNamespace const namespace_);

ide::JaktSymbol record_to_symbol(parser::ParsedRecord const record);

ide::JaktSymbol function_to_symbol(parser::ParsedFunction const function, ByteString const kind);

ErrorOr<utility::Span> find_definition_in_program(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<utility::Span> find_type_definition_for_type_id(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id, utility::Span const span);

ErrorOr<utility::Span> find_type_definition_in_program(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<JaktInternal::Optional<ByteString>> find_typename_in_program(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<JaktInternal::DynamicArray<ByteString>> completions_for_type_id(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id);

ErrorOr<JaktInternal::DynamicArray<ByteString>> find_function_completions_in_scope(NonnullRefPtr<types::Scope> const scope, NonnullRefPtr<types::CheckedProgram> const program);

ErrorOr<JaktInternal::DynamicArray<ByteString>> find_dot_completions(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_program(NonnullRefPtr<types::CheckedProgram> const program, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_scope(NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<types::Scope> const scope, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_enum(NonnullRefPtr<types::CheckedProgram> const program, types::CheckedEnum const checked_enum, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_struct(NonnullRefPtr<types::CheckedProgram> const program, types::CheckedStruct const checked_struct, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_function(NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<types::CheckedFunction> const checked_function, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_block(NonnullRefPtr<types::CheckedProgram> const program, types::CheckedBlock const block, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_statement(NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<typename types::CheckedStatement> const statement, utility::Span const span);

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_expression(NonnullRefPtr<types::CheckedProgram> const program, NonnullRefPtr<typename types::CheckedExpression> const expr, utility::Span const span);

ErrorOr<ByteString> get_function_signature(NonnullRefPtr<types::CheckedProgram> const program, ids::FunctionId const function_id);

ErrorOr<ByteString> get_var_signature(NonnullRefPtr<types::CheckedProgram> const program, ByteString const name, ids::TypeId const var_type_id, ide::Mutability const mutability, ide::VarType const var_type, ide::VarVisibility const visibility, JaktInternal::Optional<ids::TypeId> const struct_type_id);

ErrorOr<ByteString> get_type_signature(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id);

ErrorOr<ByteString> get_enum_variant_signature(NonnullRefPtr<types::CheckedProgram> const program, ByteString const name, ids::TypeId const type_id, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const variants, JaktInternal::Optional<types::NumberConstant> const number_constant);

ErrorOr<ByteString> get_enum_variant_signature_from_type_id_and_name(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id, ByteString const name);

ide::Usage get_enum_variant_usage_from_type_id_and_name(NonnullRefPtr<types::CheckedProgram> const program, ids::TypeId const type_id, ByteString const name);

JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> enum_variant_fields(NonnullRefPtr<types::CheckedProgram> const program, types::CheckedEnumVariant const checked_enum_variant);

ErrorOr<ByteString> get_constructor_signature(NonnullRefPtr<types::CheckedProgram> const program, ids::FunctionId const function_id);

}
namespace project {
struct Project;
}
namespace platform {



ErrorOr<ByteString> library_name_for_target(ByteString const name, jakt__platform::Target const target);

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
ErrorOr<ByteString> serialize_unary_operation(types::CheckedUnaryOperator const op, ByteString const expr);

ErrorOr<ByteString> serialize_ast_node(NonnullRefPtr<typename types::CheckedExpression> const node);

}
namespace git {

ErrorOr<ByteString> commit_hash();

}
namespace platform__unknown_compiler {
ErrorOr<JaktInternal::DynamicArray<ByteString>> run_compiler(ByteString const cxx_compiler_path, ByteString const cpp_filename, ByteString const output_filename, ByteString const runtime_path, JaktInternal::DynamicArray<ByteString> const extra_include_paths, JaktInternal::DynamicArray<ByteString> const extra_lib_paths, JaktInternal::DynamicArray<ByteString> const extra_link_libs, bool const optimize, JaktInternal::DynamicArray<ByteString> const extra_compiler_flags, bool const use_ccache);

}
struct FormatRange;
ByteString usage();

ByteString help();

ByteString indent(size_t const level);

JaktInternal::Optional<FormatRange> parse_format_range(ByteString const range, size_t const input_file_length);

ErrorOr<void> install(jakt__path::Path const from, jakt__path::Path const to);

ErrorOr<int> selfhost_crosscompiler_main(JaktInternal::DynamicArray<ByteString> const args);

ErrorOr<void> mkdir_p(jakt__path::Path const path);

ErrorOr<JaktInternal::DynamicArray<jakt__path::Path>> find_with_extension(jakt__path::Path const path, ByteString const extension);

ByteString escape_for_depfile(ByteString const input);

ErrorOr<int> compiler_main(JaktInternal::DynamicArray<ByteString> const args);

ErrorOr<void> format_output(jakt__path::Path const file_path, JaktInternal::DynamicArray<lexer::Token> const tokens, JaktInternal::Optional<FormatRange> const format_range, bool const format_debug, bool const format_inplace);

ErrorOr<void> write_only_if_updated(ByteString const data, ByteString const output_filename);

bool file_needs_updating(ByteString const path, ByteString const new_contents);

} // namespace Jakt
