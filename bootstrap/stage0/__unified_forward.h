#pragma once
#include <lib.h>
#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
const unsigned int CP_UTF8 = 65001;
#endif
#include <Jakt/Forward.h>
#include <stdio.h>
#include <AK/Queue.h>
namespace Jakt {
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
namespace IterationDecision_Details {
template<typename T>
struct Break;
template<typename T>
struct Continue;
}
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
namespace MessageSeverity_Details {
struct Hint;
struct Error;
}
struct MessageSeverity;

namespace JaktError_Details {
struct Message;
struct MessageWithHint;
}
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
namespace LiteralSuffix_Details {
struct None;
struct UZ;
struct U8;
struct U16;
struct U32;
struct U64;
struct I8;
struct I16;
struct I32;
struct I64;
struct F32;
struct F64;
}
struct LiteralSuffix;

namespace Token_Details {
struct SingleQuotedString;
struct QuotedString;
struct Number;
struct Identifier;
struct Semicolon;
struct Colon;
struct ColonColon;
struct LParen;
struct RParen;
struct LCurly;
struct RCurly;
struct LSquare;
struct RSquare;
struct PercentSign;
struct Plus;
struct Minus;
struct Equal;
struct PlusEqual;
struct PlusPlus;
struct MinusEqual;
struct MinusMinus;
struct AsteriskEqual;
struct ForwardSlashEqual;
struct PercentSignEqual;
struct NotEqual;
struct DoubleEqual;
struct GreaterThan;
struct GreaterThanOrEqual;
struct LessThan;
struct LessThanOrEqual;
struct LeftArithmeticShift;
struct LeftShift;
struct LeftShiftEqual;
struct RightShift;
struct RightArithmeticShift;
struct RightShiftEqual;
struct Asterisk;
struct Ampersand;
struct AmpersandEqual;
struct AmpersandAmpersand;
struct Pipe;
struct PipeEqual;
struct PipePipe;
struct Caret;
struct CaretEqual;
struct Dollar;
struct Tilde;
struct ForwardSlash;
struct ExclamationPoint;
struct QuestionMark;
struct QuestionMarkQuestionMark;
struct QuestionMarkQuestionMarkEqual;
struct Comma;
struct Dot;
struct DotDot;
struct Eol;
struct Eof;
struct FatArrow;
struct Arrow;
struct And;
struct Anon;
struct As;
struct Boxed;
struct Break;
struct Catch;
struct Class;
struct Continue;
struct Cpp;
struct Defer;
struct Destructor;
struct Else;
struct Enum;
struct Extern;
struct False;
struct For;
struct Fn;
struct Comptime;
struct If;
struct Import;
struct In;
struct Is;
struct Let;
struct Loop;
struct Match;
struct Mut;
struct Namespace;
struct Not;
struct Or;
struct Override;
struct Private;
struct Public;
struct Raw;
struct Reflect;
struct Return;
struct Restricted;
struct Sizeof;
struct Struct;
struct This;
struct Throw;
struct Throws;
struct True;
struct Try;
struct Unsafe;
struct Virtual;
struct Weak;
struct While;
struct Yield;
struct Guard;
struct Implements;
struct Requires;
struct Trait;
struct Garbage;
}
struct Token;

namespace LiteralPrefix_Details {
struct None;
struct Hexadecimal;
struct Octal;
struct Binary;
}
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
namespace ExternalName_Details {
struct Plain;
struct PreprocessorName;
struct Operator;
}
struct ExternalName;

namespace ImportName_Details {
struct Literal;
struct Comptime;
}
struct ImportName;

namespace ParsedMatchPattern_Details {
struct EnumVariant;
struct Expression;
struct CatchAll;
struct Invalid;
}
struct ParsedMatchPattern;

namespace Visibility_Details {
struct Public;
struct Private;
struct Restricted;
}
struct Visibility;

namespace ArgumentStoreLevel_Details {
struct InObject;
struct InStaticStorage;
}
struct ArgumentStoreLevel;

namespace ParsedMatchBody_Details {
struct Expression;
struct Block;
}
struct ParsedMatchBody;

namespace ParsedCapture_Details {
struct ByValue;
struct ByReference;
struct ByMutableReference;
struct ByComptimeDependency;
struct AllByReference;
}
struct ParsedCapture;

namespace ParsedType_Details {
struct Name;
struct NamespacedName;
struct GenericType;
struct JaktArray;
struct Dictionary;
struct JaktTuple;
struct Set;
struct Optional;
struct Reference;
struct MutableReference;
struct RawPtr;
struct WeakPtr;
struct Function;
struct Const;
struct DependentType;
struct Empty;
}
struct ParsedType;

namespace InlineState_Details {
struct Default;
struct MakeDefinitionAvailable;
struct ForceInline;
}
struct InlineState;

namespace ParsedTraitRequirements_Details {
struct Nothing;
struct Methods;
struct ComptimeExpression;
}
struct ParsedTraitRequirements;

namespace TypeCast_Details {
struct Fallible;
struct Infallible;
}
struct TypeCast;

namespace DefinitionLinkage_Details {
struct Internal;
struct External;
}
struct DefinitionLinkage;

namespace ImportList_Details {
struct List;
struct All;
}
struct ImportList;

namespace ParsedExpression_Details {
struct Boolean;
struct NumericConstant;
struct QuotedString;
struct SingleQuotedString;
struct Call;
struct MethodCall;
struct IndexedTuple;
struct IndexedStruct;
struct ComptimeIndex;
struct Var;
struct IndexedExpression;
struct UnaryOp;
struct BinaryOp;
struct Operator;
struct OptionalSome;
struct OptionalNone;
struct JaktArray;
struct JaktDictionary;
struct Set;
struct JaktTuple;
struct Range;
struct ForcedUnwrap;
struct Match;
struct EnumVariantArg;
struct NamespacedVar;
struct Function;
struct Try;
struct TryBlock;
struct Reflect;
struct Garbage;
struct Unsafe;
}
struct ParsedExpression;

namespace FunctionLinkage_Details {
struct Internal;
struct External;
}
struct FunctionLinkage;

namespace UnaryOperator_Details {
struct PreIncrement;
struct PostIncrement;
struct PreDecrement;
struct PostDecrement;
struct Negate;
struct Dereference;
struct RawAddress;
struct Reference;
struct MutableReference;
struct LogicalNot;
struct BitwiseNot;
struct TypeCast;
struct Is;
struct IsEnumVariant;
struct Sizeof;
}
struct UnaryOperator;

namespace BinaryOperator_Details {
struct Add;
struct Subtract;
struct Multiply;
struct Divide;
struct Modulo;
struct LessThan;
struct LessThanOrEqual;
struct GreaterThan;
struct GreaterThanOrEqual;
struct Equal;
struct NotEqual;
struct BitwiseAnd;
struct BitwiseXor;
struct BitwiseOr;
struct BitwiseLeftShift;
struct BitwiseRightShift;
struct ArithmeticLeftShift;
struct ArithmeticRightShift;
struct LogicalAnd;
struct LogicalOr;
struct NoneCoalescing;
struct Assign;
struct BitwiseAndAssign;
struct BitwiseOrAssign;
struct BitwiseXorAssign;
struct BitwiseLeftShiftAssign;
struct BitwiseRightShiftAssign;
struct AddAssign;
struct SubtractAssign;
struct MultiplyAssign;
struct ModuloAssign;
struct DivideAssign;
struct NoneCoalescingAssign;
struct Garbage;
}
struct BinaryOperator;

namespace NumericConstant_Details {
struct I8;
struct I16;
struct I32;
struct I64;
struct U8;
struct U16;
struct U32;
struct U64;
struct USize;
struct F32;
struct F64;
struct UnknownSigned;
struct UnknownUnsigned;
}
struct NumericConstant;

namespace ParsedStatement_Details {
struct Expression;
struct Defer;
struct UnsafeBlock;
struct DestructuringAssignment;
struct VarDecl;
struct If;
struct Block;
struct Loop;
struct While;
struct For;
struct Break;
struct Continue;
struct Return;
struct Throw;
struct Yield;
struct InlineCpp;
struct Guard;
struct Garbage;
}
struct ParsedStatement;

namespace IncludeAction_Details {
struct Define;
struct Undefine;
}
struct IncludeAction;

namespace RecordType_Details {
struct Struct;
struct Class;
struct ValueEnum;
struct SumEnum;
struct Garbage;
}
struct RecordType;

namespace FunctionType_Details {
struct Normal;
struct Destructor;
struct ImplicitConstructor;
struct ImplicitEnumConstructor;
struct ExternalClassConstructor;
struct Expression;
struct Closure;
}
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
namespace CheckedUnaryOperator_Details {
struct PreIncrement;
struct PostIncrement;
struct PreDecrement;
struct PostDecrement;
struct Negate;
struct Dereference;
struct RawAddress;
struct Reference;
struct MutableReference;
struct LogicalNot;
struct BitwiseNot;
struct TypeCast;
struct Is;
struct IsEnumVariant;
struct IsSome;
struct IsNone;
struct Sizeof;
}
struct CheckedUnaryOperator;

namespace NumericOrStringValue_Details {
struct StringValue;
struct SignedNumericValue;
struct UnsignedNumericValue;
}
struct NumericOrStringValue;

namespace FunctionGenericParameterKind_Details {
struct InferenceGuide;
struct Parameter;
}
struct FunctionGenericParameterKind;

namespace Type_Details {
struct Void;
struct Bool;
struct U8;
struct U16;
struct U32;
struct U64;
struct I8;
struct I16;
struct I32;
struct I64;
struct F32;
struct F64;
struct Usize;
struct JaktString;
struct CChar;
struct CInt;
struct Unknown;
struct Never;
struct TypeVariable;
struct Dependent;
struct GenericInstance;
struct GenericEnumInstance;
struct GenericTraitInstance;
struct GenericResolvedType;
struct Struct;
struct Enum;
struct RawPtr;
struct Trait;
struct Reference;
struct MutableReference;
struct Function;
struct Self;
struct Const;
}
struct Type;

namespace ValueImpl_Details {
struct Void;
struct Bool;
struct U8;
struct U16;
struct U32;
struct U64;
struct I8;
struct I16;
struct I32;
struct I64;
struct F32;
struct F64;
struct USize;
struct JaktString;
struct StringView;
struct CChar;
struct CInt;
struct Struct;
struct Class;
struct Enum;
struct JaktArray;
struct JaktDictionary;
struct JaktSet;
struct RawPtr;
struct OptionalSome;
struct OptionalNone;
struct JaktTuple;
struct Function;
}
struct ValueImpl;

namespace BlockControlFlow_Details {
struct AlwaysReturns;
struct AlwaysTransfersControl;
struct NeverReturns;
struct MayReturn;
struct PartialAlwaysReturns;
struct PartialAlwaysTransfersControl;
struct PartialNeverReturns;
}
struct BlockControlFlow;

namespace CheckedMatchBody_Details {
struct Expression;
struct Block;
}
struct CheckedMatchBody;

namespace CheckedStatement_Details {
struct Expression;
struct Defer;
struct DestructuringAssignment;
struct VarDecl;
struct If;
struct Block;
struct Loop;
struct While;
struct Return;
struct Break;
struct Continue;
struct Throw;
struct Yield;
struct InlineCpp;
struct Garbage;
}
struct CheckedStatement;

namespace CheckedEnumVariant_Details {
struct Untyped;
struct Typed;
struct WithValue;
struct StructLike;
}
struct CheckedEnumVariant;

namespace CheckedMatchCase_Details {
struct EnumVariant;
struct Expression;
struct ClassInstance;
struct CatchAll;
}
struct CheckedMatchCase;

namespace CheckedTypeCast_Details {
struct Fallible;
struct Infallible;
}
struct CheckedTypeCast;

namespace NumberConstant_Details {
struct Signed;
struct Unsigned;
struct Floating;
}
struct NumberConstant;

namespace CheckedVisibility_Details {
struct Public;
struct Private;
struct Restricted;
}
struct CheckedVisibility;

namespace CheckedNumericConstant_Details {
struct I8;
struct I16;
struct I32;
struct I64;
struct U8;
struct U16;
struct U32;
struct U64;
struct USize;
struct F32;
struct F64;
}
struct CheckedNumericConstant;

namespace CheckedCapture_Details {
struct ByValue;
struct ByReference;
struct ByMutableReference;
struct ByComptimeDependency;
struct AllByReference;
}
struct CheckedCapture;

namespace StructOrEnumId_Details {
struct Struct;
struct Enum;
}
struct StructOrEnumId;

namespace SafetyMode_Details {
struct Safe;
struct Unsafe;
}
struct SafetyMode;

namespace MaybeResolvedScope_Details {
struct Resolved;
struct Unresolved;
}
struct MaybeResolvedScope;

namespace StringLiteral_Details {
struct Static;
}
struct StringLiteral;

namespace StructLikeId_Details {
struct Struct;
struct Enum;
struct Trait;
}
struct StructLikeId;

namespace CheckedExpression_Details {
struct Boolean;
struct NumericConstant;
struct QuotedString;
struct ByteConstant;
struct CharacterConstant;
struct CCharacterConstant;
struct UnaryOp;
struct BinaryOp;
struct JaktTuple;
struct Range;
struct JaktArray;
struct JaktSet;
struct JaktDictionary;
struct IndexedExpression;
struct IndexedDictionary;
struct IndexedTuple;
struct IndexedStruct;
struct IndexedCommonEnumMember;
struct ComptimeIndex;
struct Match;
struct EnumVariantArg;
struct Call;
struct MethodCall;
struct NamespacedVar;
struct Var;
struct OptionalNone;
struct OptionalSome;
struct ForcedUnwrap;
struct Block;
struct Function;
struct DependentFunction;
struct Try;
struct TryBlock;
struct Reflect;
struct Garbage;
}
struct CheckedExpression;

namespace BuiltinType_Details {
struct Void;
struct Bool;
struct U8;
struct U16;
struct U32;
struct U64;
struct I8;
struct I16;
struct I32;
struct I64;
struct F32;
struct F64;
struct Usize;
struct JaktString;
struct CChar;
struct CInt;
struct Unknown;
struct Never;
}
struct BuiltinType;

namespace CheckedTraitRequirements_Details {
struct Nothing;
struct Methods;
struct ComptimeExpression;
}
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
namespace ExecutionResult_Details {
struct Return;
struct Throw;
}
struct ExecutionResult;

namespace Deferred_Details {
struct Expression;
struct Statement;
}
struct Deferred;

namespace StatementResult_Details {
struct Return;
struct Throw;
struct Yield;
struct Continue;
struct Break;
struct JustValue;
}
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
namespace NumericOrStringValue_Details {
struct StringValue;
struct SignedNumericValue;
struct UnsignedNumericValue;
}
struct NumericOrStringValue;

namespace FunctionMatchResult_Details {
struct MatchSuccess;
struct MatchError;
}
struct FunctionMatchResult;

ErrorOr<JaktInternal::Dictionary<DeprecatedString,DeprecatedString>> defines_from(JaktInternal::DynamicArray<parser::IncludeAction> const actions);

}
namespace codegen {
struct ControlFlowState;
struct CodegenDebugInfo;
struct LineSpan;
struct CodeGenerator;
namespace AllowedControlExits_Details {
struct Nothing;
struct JustReturn;
struct AtLoop;
}
struct AllowedControlExits;

bool are_loop_exits_allowed(codegen::AllowedControlExits const allowed_control_exits);

bool is_return_allowed(codegen::AllowedControlExits const allowed_control_exits);

}
namespace formatter {
struct FormattedToken;
struct ReflowState;
struct Formatter;
struct Stage0;
namespace State_Details {
struct Toplevel;
struct Extern;
struct Import;
struct ImportList;
struct EntityDeclaration;
struct Implements;
struct CaptureList;
struct ParameterList;
struct RestrictionList;
struct EntityDefinition;
struct StatementContext;
struct MatchPattern;
struct VariableDeclaration;
struct GenericCallTypeParams;
struct TypeContext;
struct FunctionTypeContext;
}
struct State;

namespace ExpressionMode_Details {
struct OutsideExpression;
struct BeforeExpressions;
struct AtExpressionStart;
struct InExpression;
}
struct ExpressionMode;

namespace BreakablePoint_Details {
struct Paren;
struct Curly;
struct Square;
struct Logical;
}
struct BreakablePoint;

namespace Entity_Details {
struct Struct;
struct Enum;
struct Namespace;
struct Function;
}
struct Entity;

void bubble_sort(JaktInternal::DynamicArray<DeprecatedString> values);

}
namespace ide {
struct JaktSymbol;
namespace Mutability_Details {
struct DoesNotApply;
struct Immutable;
struct Mutable;
}
struct Mutability;

namespace VarVisibility_Details {
struct DoesNotApply;
struct Public;
struct Private;
struct Restricted;
}
struct VarVisibility;

namespace Usage_Details {
struct Variable;
struct Call;
struct Typename;
struct NameSet;
struct EnumVariant;
}
struct Usage;

namespace VarType_Details {
struct Variable;
struct Field;
}
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
namespace LineResult_Details {
struct Line;
struct Eof;
}
struct LineResult;

namespace XTermColor_Details {
struct Default;
struct Black;
struct Red;
struct Green;
struct Yellow;
struct Blue;
struct Magenta;
struct Cyan;
struct White;
struct Unchanged;
}
struct XTermColor;

namespace Color_Details {
struct Components;
struct XTerm;
}
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
