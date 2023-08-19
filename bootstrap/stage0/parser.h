#pragma once
#include "__unified_forward.h"
#include "error.h"
#include "lexer.h"
#include "utility.h"
#include "compiler.h"
namespace Jakt {
namespace parser {
namespace Visibility_Details {
struct Public {
};
struct Private {
};
struct Restricted {
JaktInternal::DynamicArray<parser::VisibilityRestriction> whitelist;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Restricted(_MemberT0&& member_0, _MemberT1&& member_1):
whitelist{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct Visibility : public Variant<Visibility_Details::Public, Visibility_Details::Private, Visibility_Details::Restricted> {
using Variant<Visibility_Details::Public, Visibility_Details::Private, Visibility_Details::Restricted>::Variant;
    using Public = Visibility_Details::Public;
    using Private = Visibility_Details::Private;
    using Restricted = Visibility_Details::Restricted;
ErrorOr<DeprecatedString> debug_description() const;
};
struct ParsedBlock {
  public:
public: JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>> stmts;public: ParsedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>> a_stmts);

public: JaktInternal::Optional<utility::Span> find_yield_span() const;
public: bool equals(parser::ParsedBlock const rhs_block) const;
public: ErrorOr<JaktInternal::Optional<utility::Span>> span(parser::Parser const parser) const;
public: JaktInternal::Optional<utility::Span> find_yield_keyword_span() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace FunctionType_Details {
struct Normal {
};
struct Destructor {
};
struct ImplicitConstructor {
};
struct ImplicitEnumConstructor {
};
struct ExternalClassConstructor {
};
struct Expression {
};
struct Closure {
};
}
struct FunctionType : public Variant<FunctionType_Details::Normal, FunctionType_Details::Destructor, FunctionType_Details::ImplicitConstructor, FunctionType_Details::ImplicitEnumConstructor, FunctionType_Details::ExternalClassConstructor, FunctionType_Details::Expression, FunctionType_Details::Closure> {
using Variant<FunctionType_Details::Normal, FunctionType_Details::Destructor, FunctionType_Details::ImplicitConstructor, FunctionType_Details::ImplicitEnumConstructor, FunctionType_Details::ExternalClassConstructor, FunctionType_Details::Expression, FunctionType_Details::Closure>::Variant;
    using Normal = FunctionType_Details::Normal;
    using Destructor = FunctionType_Details::Destructor;
    using ImplicitConstructor = FunctionType_Details::ImplicitConstructor;
    using ImplicitEnumConstructor = FunctionType_Details::ImplicitEnumConstructor;
    using ExternalClassConstructor = FunctionType_Details::ExternalClassConstructor;
    using Expression = FunctionType_Details::Expression;
    using Closure = FunctionType_Details::Closure;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace FunctionLinkage_Details {
struct Internal {
};
struct External {
};
}
struct FunctionLinkage : public Variant<FunctionLinkage_Details::Internal, FunctionLinkage_Details::External> {
using Variant<FunctionLinkage_Details::Internal, FunctionLinkage_Details::External>::Variant;
    using Internal = FunctionLinkage_Details::Internal;
    using External = FunctionLinkage_Details::External;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace ExternalName_Details {
struct Plain{
DeprecatedString value;
template<typename _MemberT0>
Plain(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct PreprocessorName{
DeprecatedString value;
template<typename _MemberT0>
PreprocessorName(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Operator {
DeprecatedString name;
bool is_prefix;
template<typename _MemberT0, typename _MemberT1>
Operator(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
is_prefix{ forward<_MemberT1>(member_1)}
{}
};
}
struct ExternalName : public Variant<ExternalName_Details::Plain, ExternalName_Details::PreprocessorName, ExternalName_Details::Operator> {
using Variant<ExternalName_Details::Plain, ExternalName_Details::PreprocessorName, ExternalName_Details::Operator>::Variant;
    using Plain = ExternalName_Details::Plain;
    using PreprocessorName = ExternalName_Details::PreprocessorName;
    using Operator = ExternalName_Details::Operator;
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<DeprecatedString> as_name_for_use() const;
bool is_scopable() const;
bool is_prefix() const;
ErrorOr<DeprecatedString> as_name_for_definition() const;
};
namespace InlineState_Details {
struct Default {
};
struct MakeDefinitionAvailable {
};
struct ForceInline {
};
}
struct InlineState : public Variant<InlineState_Details::Default, InlineState_Details::MakeDefinitionAvailable, InlineState_Details::ForceInline> {
using Variant<InlineState_Details::Default, InlineState_Details::MakeDefinitionAvailable, InlineState_Details::ForceInline>::Variant;
    using Default = InlineState_Details::Default;
    using MakeDefinitionAvailable = InlineState_Details::MakeDefinitionAvailable;
    using ForceInline = InlineState_Details::ForceInline;
ErrorOr<DeprecatedString> debug_description() const;
};
struct ParsedFunction {
  public:
public: size_t id;public: DeprecatedString name;public: utility::Span name_span;public: parser::Visibility visibility;public: JaktInternal::DynamicArray<parser::ParsedParameter> params;public: JaktInternal::DynamicArray<parser::ParsedGenericParameter> generic_parameters;public: parser::ParsedBlock block;public: NonnullRefPtr<typename parser::ParsedType> return_type;public: utility::Span return_type_span;public: bool can_throw;public: parser::FunctionType type;public: parser::FunctionLinkage linkage;public: bool must_instantiate;public: bool is_comptime;public: bool is_fat_arrow;public: bool is_unsafe;public: JaktInternal::Optional<parser::ExternalName> external_name;public: JaktInternal::Optional<DeprecatedString> deprecated_message;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> stores_arguments;public: parser::InlineState force_inline;public: ParsedFunction(size_t a_id, DeprecatedString a_name, utility::Span a_name_span, parser::Visibility a_visibility, JaktInternal::DynamicArray<parser::ParsedParameter> a_params, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::ParsedBlock a_block, NonnullRefPtr<typename parser::ParsedType> a_return_type, utility::Span a_return_type_span, bool a_can_throw, parser::FunctionType a_type, parser::FunctionLinkage a_linkage, bool a_must_instantiate, bool a_is_comptime, bool a_is_fat_arrow, bool a_is_unsafe, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<DeprecatedString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> a_stores_arguments, parser::InlineState a_force_inline);

public: bool equals(parser::ParsedFunction const other, bool const ignore_block) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ImportList_Details {
struct List{
JaktInternal::DynamicArray<parser::ImportName> value;
template<typename _MemberT0>
List(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct All {
};
}
struct ImportList : public Variant<ImportList_Details::List, ImportList_Details::All> {
using Variant<ImportList_Details::List, ImportList_Details::All>::Variant;
    using List = ImportList_Details::List;
    using All = ImportList_Details::All;
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<void> add(parser::ImportName const name);
bool is_empty() const;
};
struct ParsedVariable {
  public:
public: DeprecatedString name;public: NonnullRefPtr<typename parser::ParsedType> parsed_type;public: bool is_mutable;public: utility::Span span;public: ParsedVariable(DeprecatedString a_name, NonnullRefPtr<typename parser::ParsedType> a_parsed_type, bool a_is_mutable, utility::Span a_span);

public: bool equals(parser::ParsedVariable const rhs_parsed_varible) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedAttribute {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<DeprecatedString> assigned_value;public: JaktInternal::DynamicArray<parser::ParsedAttributeArgument> arguments;public: ParsedAttribute(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<DeprecatedString> a_assigned_value, JaktInternal::DynamicArray<parser::ParsedAttributeArgument> a_arguments);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedParameter {
  public:
public: bool requires_label;public: parser::ParsedVariable variable;public: JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> default_argument;public: utility::Span span;public: ParsedParameter(bool a_requires_label, parser::ParsedVariable a_variable, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_default_argument, utility::Span a_span);

public: bool equals(parser::ParsedParameter const rhs_param) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedCall {
  public:
public: JaktInternal::DynamicArray<DeprecatedString> namespace_;public: DeprecatedString name;public: JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> args;public: JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> type_args;public: ParsedCall(JaktInternal::DynamicArray<DeprecatedString> a_namespace_, DeprecatedString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> a_args, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> a_type_args);

public: bool equals(parser::ParsedCall const rhs_parsed_call) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedGenericParameter {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> requires_list;public: bool is_value;public: ParsedGenericParameter(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> a_requires_list, bool a_is_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedVarDeclTuple {
  public:
public: JaktInternal::DynamicArray<parser::ParsedVarDecl> var_decls;public: utility::Span span;public: ParsedVarDeclTuple(JaktInternal::DynamicArray<parser::ParsedVarDecl> a_var_decls, utility::Span a_span);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ImportName_Details {
struct Literal {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Literal(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Comptime {
NonnullRefPtr<typename parser::ParsedExpression> expression;
template<typename _MemberT0>
Comptime(_MemberT0&& member_0):
expression{ forward<_MemberT0>(member_0)}
{}
};
}
struct ImportName : public Variant<ImportName_Details::Literal, ImportName_Details::Comptime> {
using Variant<ImportName_Details::Literal, ImportName_Details::Comptime>::Variant;
    using Literal = ImportName_Details::Literal;
    using Comptime = ImportName_Details::Comptime;
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<DeprecatedString> literal_name() const;
bool equals(parser::ImportName const other) const;
utility::Span span() const;
};
struct ParsedModuleImport {
  public:
public: parser::ImportName module_name;public: JaktInternal::Optional<parser::ImportName> alias_name;public: parser::ImportList import_list;public: bool has_same_alias_than(parser::ParsedModuleImport const other) const;
public: ParsedModuleImport(parser::ImportName a_module_name, JaktInternal::Optional<parser::ImportName> a_alias_name, parser::ImportList a_import_list);

public: bool has_same_import_semantics(parser::ParsedModuleImport const other) const;
public: ErrorOr<void> merge_import_list(parser::ImportList const list);
public: bool is_equivalent_to(parser::ParsedModuleImport const other) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace IncludeAction_Details {
struct Define {
DeprecatedString name;
utility::Span span;
DeprecatedString value;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Define(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)},
value{ forward<_MemberT2>(member_2)}
{}
};
struct Undefine {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Undefine(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct IncludeAction : public Variant<IncludeAction_Details::Define, IncludeAction_Details::Undefine> {
using Variant<IncludeAction_Details::Define, IncludeAction_Details::Undefine>::Variant;
    using Define = IncludeAction_Details::Define;
    using Undefine = IncludeAction_Details::Undefine;
ErrorOr<DeprecatedString> debug_description() const;
};
struct Parser {
  public:
public: size_t index;public: JaktInternal::DynamicArray<lexer::Token> tokens;public: NonnullRefPtr<compiler::Compiler> compiler;public: bool can_have_trailing_closure;public: size_t next_function_id;public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_operand_base();
public: utility::Span span(size_t const start, size_t const end) const;
public: ErrorOr<JaktInternal::Optional<parser::NumericConstant>> make_integer_numeric_constant(u64 const number, lexer::LiteralSuffix const suffix, utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_shorthand(parser::ParsedTypeQualifiers const qualifiers);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_lambda();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_longhand(parser::ParsedTypeQualifiers const qualifiers);
public: ErrorOr<parser::ParsedAlias> parse_using();
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedParameter>> parse_function_parameters();
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedMatchCase>> parse_match_cases();
public: ErrorOr<JaktInternal::Optional<parser::ParsedAttribute>> parse_attribute();
public: ErrorOr<parser::ParsedMethod> parse_method(parser::FunctionLinkage const linkage, parser::Visibility const visibility, bool const is_virtual, bool const is_override, bool const is_comptime, bool const is_destructor, bool const is_unsafe);
public: ErrorOr<parser::ParsedNamespace> parse_namespace(bool const process_only_one_entity);
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>> parse_forall();
public: ErrorOr<parser::ParsedVarDecl> parse_variable_declaration(bool const is_mutable);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_shorthand_set(parser::ParsedTypeQualifiers const qualifiers);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> parse_if_statement();
public: ErrorOr<JaktInternal::Optional<parser::ParsedCall>> parse_call();
public: ErrorOr<void> inject_token(lexer::Token const token);
public: ErrorOr<parser::ParsedRecord> parse_class(parser::DefinitionLinkage const definition_linkage);
public: ErrorOr<parser::ParsedExternalTraitImplementation> parse_external_trait_implementation();
public: ErrorOr<parser::ParsedMatchPattern> parse_match_pattern();
public: ErrorOr<parser::ParsedFunction> parse_function(parser::FunctionLinkage const linkage, parser::Visibility const visibility, bool const is_comptime, bool const is_destructor, bool const is_unsafe, bool const allow_missing_body);
public: ErrorOr<parser::ParsedExternImport> parse_extern_import(parser::ParsedNamespace& parent);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_typename();
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>>> parse_struct_class_body(parser::DefinitionLinkage const definition_linkage, parser::Visibility const default_visibility, bool const is_class);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_unsafe_expr();
public: static ErrorOr<parser::ParsedNamespace> parse(NonnullRefPtr<compiler::Compiler> const compiler, JaktInternal::DynamicArray<lexer::Token> const tokens);
public: ErrorOr<JaktInternal::Optional<parser::NumericConstant>> make_float_numeric_constant(f64 const number, lexer::LiteralSuffix const suffix, utility::Span const span);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_range();
public: ErrorOr<parser::ParsedBlock> parse_fat_arrow();
public: void skip_newlines();
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ValueEnumVariant>,JaktInternal::DynamicArray<parser::ParsedMethod>>> parse_value_enum_body(parser::ParsedRecord const partial_enum, parser::DefinitionLinkage const definition_linkage);
public: lexer::Token previous() const;
public: ErrorOr<JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>>> parse_type_parameter_list();
public: ErrorOr<JaktInternal::DynamicArray<parser::EnumVariantPatternArgument>> parse_variant_arguments();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> parse_guard_statement();
public: bool eof() const;
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_asterisk();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_match_expression();
public: ErrorOr<void> apply_attributes(parser::ParsedField& field, JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes);
public: ErrorOr<void> apply_attributes(parser::ParsedFunction& parsed_function, JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes);
public: ErrorOr<void> apply_attributes(parser::ParsedMethod& parsed_method, JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes);
public: ErrorOr<void> apply_attributes(parser::ParsedRecord& parsed_record, JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes);
public: lexer::Token current() const;
public: ErrorOr<parser::ParsedRecord> parse_enum(parser::DefinitionLinkage const definition_linkage, bool const is_boxed);
public: ErrorOr<parser::ParsedBlock> parse_block();
public: utility::Span empty_span() const;
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_postfix_colon_colon(utility::Span const start, NonnullRefPtr<typename parser::ParsedExpression> const expr);
public: ErrorOr<void> error(DeprecatedString const message, utility::Span const span);
public: ErrorOr<parser::ParsedTrait> parse_trait();
public: ErrorOr<parser::Visibility> parse_restricted_visibility_modifier();
public: ErrorOr<parser::ParsedVarDeclTuple> parse_destructuring_assignment(bool const is_mutable);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_operand_postfix_operator(utility::Span const start, NonnullRefPtr<typename parser::ParsedExpression> const expr);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_set_literal();
public: ErrorOr<void> parse_attribute_list(JaktInternal::DynamicArray<parser::ParsedAttribute>& active_attributes);
public: Parser(size_t a_index, JaktInternal::DynamicArray<lexer::Token> a_tokens, NonnullRefPtr<compiler::Compiler> a_compiler, bool a_can_have_trailing_closure, size_t a_next_function_id);

public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_expression(bool const allow_assignments, bool const allow_newlines);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_operator(bool const allow_assignments);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> parse_for_statement();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_typename_base();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_operand();
public: ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>>> parse_sum_enum_body(parser::ParsedRecord const partial_enum, parser::DefinitionLinkage const definition_linkage, bool const is_boxed);
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedCapture>> parse_captures();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_number(lexer::LiteralPrefix const prefix, DeprecatedString const number, lexer::LiteralSuffix suffix, utility::Span const span);
public: ErrorOr<parser::ParsedModuleImport> parse_module_import();
public: ErrorOr<parser::ParsedRecord> parse_record(parser::DefinitionLinkage const definition_linkage);
public: lexer::Token peek(size_t const steps) const;
public: ErrorOr<void> error_with_hint(DeprecatedString const message, utility::Span const span, DeprecatedString const hint, utility::Span const hint_span);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_shorthand_array_or_dictionary(parser::ParsedTypeQualifiers const qualifiers);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedType>> parse_type_shorthand_tuple(parser::ParsedTypeQualifiers const qualifiers);
public: bool eol() const;
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_array_or_dictionary_literal();
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedMatchPattern>> parse_match_patterns();
public: ErrorOr<void> parse_import(parser::ParsedNamespace& parent);
public: ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> parse_statement(bool const inside_block);
public: ErrorOr<parser::ParsedField> parse_field(parser::Visibility const visibility);
public: ErrorOr<DeprecatedString> parse_argument_label();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_ampersand();
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>>> parse_include_action();
public: ErrorOr<NonnullRefPtr<typename parser::ParsedExpression>> parse_try_block();
public: ErrorOr<JaktInternal::DynamicArray<parser::ParsedGenericParameter>> parse_generic_parameters();
public: ErrorOr<parser::ParsedRecord> parse_struct(parser::DefinitionLinkage const definition_linkage);
public: ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>>> parse_trait_list();
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedExternalTraitImplementation {
  public:
public: NonnullRefPtr<typename parser::ParsedType> for_type;public: JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> traits;public: JaktInternal::DynamicArray<parser::ParsedMethod> methods;public: ParsedExternalTraitImplementation(NonnullRefPtr<typename parser::ParsedType> a_for_type, JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> a_traits, JaktInternal::DynamicArray<parser::ParsedMethod> a_methods);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ArgumentStoreLevel_Details {
struct InObject {
size_t argument_index;
template<typename _MemberT0>
InObject(_MemberT0&& member_0):
argument_index{ forward<_MemberT0>(member_0)}
{}
};
struct InStaticStorage {
};
}
struct ArgumentStoreLevel : public Variant<ArgumentStoreLevel_Details::InObject, ArgumentStoreLevel_Details::InStaticStorage> {
using Variant<ArgumentStoreLevel_Details::InObject, ArgumentStoreLevel_Details::InStaticStorage>::Variant;
    using InObject = ArgumentStoreLevel_Details::InObject;
    using InStaticStorage = ArgumentStoreLevel_Details::InStaticStorage;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace NumericConstant_Details {
struct I8{
i8 value;
template<typename _MemberT0>
I8(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I16{
i16 value;
template<typename _MemberT0>
I16(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I32{
i32 value;
template<typename _MemberT0>
I32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct I64{
i64 value;
template<typename _MemberT0>
I64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U8{
u8 value;
template<typename _MemberT0>
U8(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U16{
u16 value;
template<typename _MemberT0>
U16(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U32{
u32 value;
template<typename _MemberT0>
U32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct U64{
u64 value;
template<typename _MemberT0>
U64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct USize{
u64 value;
template<typename _MemberT0>
USize(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct F32{
f32 value;
template<typename _MemberT0>
F32(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct F64{
f64 value;
template<typename _MemberT0>
F64(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct UnknownSigned{
i64 value;
template<typename _MemberT0>
UnknownSigned(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct UnknownUnsigned{
u64 value;
template<typename _MemberT0>
UnknownUnsigned(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct NumericConstant : public Variant<NumericConstant_Details::I8, NumericConstant_Details::I16, NumericConstant_Details::I32, NumericConstant_Details::I64, NumericConstant_Details::U8, NumericConstant_Details::U16, NumericConstant_Details::U32, NumericConstant_Details::U64, NumericConstant_Details::USize, NumericConstant_Details::F32, NumericConstant_Details::F64, NumericConstant_Details::UnknownSigned, NumericConstant_Details::UnknownUnsigned> {
using Variant<NumericConstant_Details::I8, NumericConstant_Details::I16, NumericConstant_Details::I32, NumericConstant_Details::I64, NumericConstant_Details::U8, NumericConstant_Details::U16, NumericConstant_Details::U32, NumericConstant_Details::U64, NumericConstant_Details::USize, NumericConstant_Details::F32, NumericConstant_Details::F64, NumericConstant_Details::UnknownSigned, NumericConstant_Details::UnknownUnsigned>::Variant;
    using I8 = NumericConstant_Details::I8;
    using I16 = NumericConstant_Details::I16;
    using I32 = NumericConstant_Details::I32;
    using I64 = NumericConstant_Details::I64;
    using U8 = NumericConstant_Details::U8;
    using U16 = NumericConstant_Details::U16;
    using U32 = NumericConstant_Details::U32;
    using U64 = NumericConstant_Details::U64;
    using USize = NumericConstant_Details::USize;
    using F32 = NumericConstant_Details::F32;
    using F64 = NumericConstant_Details::F64;
    using UnknownSigned = NumericConstant_Details::UnknownSigned;
    using UnknownUnsigned = NumericConstant_Details::UnknownUnsigned;
ErrorOr<DeprecatedString> debug_description() const;
size_t to_usize() const;
};
namespace TypeCast_Details {
struct Fallible{
NonnullRefPtr<typename parser::ParsedType> value;
template<typename _MemberT0>
Fallible(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Infallible{
NonnullRefPtr<typename parser::ParsedType> value;
template<typename _MemberT0>
Infallible(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct TypeCast : public Variant<TypeCast_Details::Fallible, TypeCast_Details::Infallible> {
using Variant<TypeCast_Details::Fallible, TypeCast_Details::Infallible>::Variant;
    using Fallible = TypeCast_Details::Fallible;
    using Infallible = TypeCast_Details::Infallible;
ErrorOr<DeprecatedString> debug_description() const;
NonnullRefPtr<typename parser::ParsedType> parsed_type() const;
};
namespace UnaryOperator_Details {
struct PreIncrement {
};
struct PostIncrement {
};
struct PreDecrement {
};
struct PostDecrement {
};
struct Negate {
};
struct Dereference {
};
struct RawAddress {
};
struct Reference {
};
struct MutableReference {
};
struct LogicalNot {
};
struct BitwiseNot {
};
struct TypeCast{
parser::TypeCast value;
template<typename _MemberT0>
TypeCast(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Is{
NonnullRefPtr<typename parser::ParsedType> value;
template<typename _MemberT0>
Is(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct IsEnumVariant {
NonnullRefPtr<typename parser::ParsedType> inner;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> bindings;
template<typename _MemberT0, typename _MemberT1>
IsEnumVariant(_MemberT0&& member_0, _MemberT1&& member_1):
inner{ forward<_MemberT0>(member_0)},
bindings{ forward<_MemberT1>(member_1)}
{}
};
struct Sizeof{
NonnullRefPtr<typename parser::ParsedType> value;
template<typename _MemberT0>
Sizeof(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct UnaryOperator : public Variant<UnaryOperator_Details::PreIncrement, UnaryOperator_Details::PostIncrement, UnaryOperator_Details::PreDecrement, UnaryOperator_Details::PostDecrement, UnaryOperator_Details::Negate, UnaryOperator_Details::Dereference, UnaryOperator_Details::RawAddress, UnaryOperator_Details::Reference, UnaryOperator_Details::MutableReference, UnaryOperator_Details::LogicalNot, UnaryOperator_Details::BitwiseNot, UnaryOperator_Details::TypeCast, UnaryOperator_Details::Is, UnaryOperator_Details::IsEnumVariant, UnaryOperator_Details::Sizeof> {
using Variant<UnaryOperator_Details::PreIncrement, UnaryOperator_Details::PostIncrement, UnaryOperator_Details::PreDecrement, UnaryOperator_Details::PostDecrement, UnaryOperator_Details::Negate, UnaryOperator_Details::Dereference, UnaryOperator_Details::RawAddress, UnaryOperator_Details::Reference, UnaryOperator_Details::MutableReference, UnaryOperator_Details::LogicalNot, UnaryOperator_Details::BitwiseNot, UnaryOperator_Details::TypeCast, UnaryOperator_Details::Is, UnaryOperator_Details::IsEnumVariant, UnaryOperator_Details::Sizeof>::Variant;
    using PreIncrement = UnaryOperator_Details::PreIncrement;
    using PostIncrement = UnaryOperator_Details::PostIncrement;
    using PreDecrement = UnaryOperator_Details::PreDecrement;
    using PostDecrement = UnaryOperator_Details::PostDecrement;
    using Negate = UnaryOperator_Details::Negate;
    using Dereference = UnaryOperator_Details::Dereference;
    using RawAddress = UnaryOperator_Details::RawAddress;
    using Reference = UnaryOperator_Details::Reference;
    using MutableReference = UnaryOperator_Details::MutableReference;
    using LogicalNot = UnaryOperator_Details::LogicalNot;
    using BitwiseNot = UnaryOperator_Details::BitwiseNot;
    using TypeCast = UnaryOperator_Details::TypeCast;
    using Is = UnaryOperator_Details::Is;
    using IsEnumVariant = UnaryOperator_Details::IsEnumVariant;
    using Sizeof = UnaryOperator_Details::Sizeof;
ErrorOr<DeprecatedString> debug_description() const;
bool equals(parser::UnaryOperator const rhs_op) const;
};
namespace BinaryOperator_Details {
struct Add {
};
struct Subtract {
};
struct Multiply {
};
struct Divide {
};
struct Modulo {
};
struct LessThan {
};
struct LessThanOrEqual {
};
struct GreaterThan {
};
struct GreaterThanOrEqual {
};
struct Equal {
};
struct NotEqual {
};
struct BitwiseAnd {
};
struct BitwiseXor {
};
struct BitwiseOr {
};
struct BitwiseLeftShift {
};
struct BitwiseRightShift {
};
struct ArithmeticLeftShift {
};
struct ArithmeticRightShift {
};
struct LogicalAnd {
};
struct LogicalOr {
};
struct NoneCoalescing {
};
struct Assign {
};
struct BitwiseAndAssign {
};
struct BitwiseOrAssign {
};
struct BitwiseXorAssign {
};
struct BitwiseLeftShiftAssign {
};
struct BitwiseRightShiftAssign {
};
struct AddAssign {
};
struct SubtractAssign {
};
struct MultiplyAssign {
};
struct ModuloAssign {
};
struct DivideAssign {
};
struct NoneCoalescingAssign {
};
struct Garbage {
};
}
struct BinaryOperator : public Variant<BinaryOperator_Details::Add, BinaryOperator_Details::Subtract, BinaryOperator_Details::Multiply, BinaryOperator_Details::Divide, BinaryOperator_Details::Modulo, BinaryOperator_Details::LessThan, BinaryOperator_Details::LessThanOrEqual, BinaryOperator_Details::GreaterThan, BinaryOperator_Details::GreaterThanOrEqual, BinaryOperator_Details::Equal, BinaryOperator_Details::NotEqual, BinaryOperator_Details::BitwiseAnd, BinaryOperator_Details::BitwiseXor, BinaryOperator_Details::BitwiseOr, BinaryOperator_Details::BitwiseLeftShift, BinaryOperator_Details::BitwiseRightShift, BinaryOperator_Details::ArithmeticLeftShift, BinaryOperator_Details::ArithmeticRightShift, BinaryOperator_Details::LogicalAnd, BinaryOperator_Details::LogicalOr, BinaryOperator_Details::NoneCoalescing, BinaryOperator_Details::Assign, BinaryOperator_Details::BitwiseAndAssign, BinaryOperator_Details::BitwiseOrAssign, BinaryOperator_Details::BitwiseXorAssign, BinaryOperator_Details::BitwiseLeftShiftAssign, BinaryOperator_Details::BitwiseRightShiftAssign, BinaryOperator_Details::AddAssign, BinaryOperator_Details::SubtractAssign, BinaryOperator_Details::MultiplyAssign, BinaryOperator_Details::ModuloAssign, BinaryOperator_Details::DivideAssign, BinaryOperator_Details::NoneCoalescingAssign, BinaryOperator_Details::Garbage> {
using Variant<BinaryOperator_Details::Add, BinaryOperator_Details::Subtract, BinaryOperator_Details::Multiply, BinaryOperator_Details::Divide, BinaryOperator_Details::Modulo, BinaryOperator_Details::LessThan, BinaryOperator_Details::LessThanOrEqual, BinaryOperator_Details::GreaterThan, BinaryOperator_Details::GreaterThanOrEqual, BinaryOperator_Details::Equal, BinaryOperator_Details::NotEqual, BinaryOperator_Details::BitwiseAnd, BinaryOperator_Details::BitwiseXor, BinaryOperator_Details::BitwiseOr, BinaryOperator_Details::BitwiseLeftShift, BinaryOperator_Details::BitwiseRightShift, BinaryOperator_Details::ArithmeticLeftShift, BinaryOperator_Details::ArithmeticRightShift, BinaryOperator_Details::LogicalAnd, BinaryOperator_Details::LogicalOr, BinaryOperator_Details::NoneCoalescing, BinaryOperator_Details::Assign, BinaryOperator_Details::BitwiseAndAssign, BinaryOperator_Details::BitwiseOrAssign, BinaryOperator_Details::BitwiseXorAssign, BinaryOperator_Details::BitwiseLeftShiftAssign, BinaryOperator_Details::BitwiseRightShiftAssign, BinaryOperator_Details::AddAssign, BinaryOperator_Details::SubtractAssign, BinaryOperator_Details::MultiplyAssign, BinaryOperator_Details::ModuloAssign, BinaryOperator_Details::DivideAssign, BinaryOperator_Details::NoneCoalescingAssign, BinaryOperator_Details::Garbage>::Variant;
    using Add = BinaryOperator_Details::Add;
    using Subtract = BinaryOperator_Details::Subtract;
    using Multiply = BinaryOperator_Details::Multiply;
    using Divide = BinaryOperator_Details::Divide;
    using Modulo = BinaryOperator_Details::Modulo;
    using LessThan = BinaryOperator_Details::LessThan;
    using LessThanOrEqual = BinaryOperator_Details::LessThanOrEqual;
    using GreaterThan = BinaryOperator_Details::GreaterThan;
    using GreaterThanOrEqual = BinaryOperator_Details::GreaterThanOrEqual;
    using Equal = BinaryOperator_Details::Equal;
    using NotEqual = BinaryOperator_Details::NotEqual;
    using BitwiseAnd = BinaryOperator_Details::BitwiseAnd;
    using BitwiseXor = BinaryOperator_Details::BitwiseXor;
    using BitwiseOr = BinaryOperator_Details::BitwiseOr;
    using BitwiseLeftShift = BinaryOperator_Details::BitwiseLeftShift;
    using BitwiseRightShift = BinaryOperator_Details::BitwiseRightShift;
    using ArithmeticLeftShift = BinaryOperator_Details::ArithmeticLeftShift;
    using ArithmeticRightShift = BinaryOperator_Details::ArithmeticRightShift;
    using LogicalAnd = BinaryOperator_Details::LogicalAnd;
    using LogicalOr = BinaryOperator_Details::LogicalOr;
    using NoneCoalescing = BinaryOperator_Details::NoneCoalescing;
    using Assign = BinaryOperator_Details::Assign;
    using BitwiseAndAssign = BinaryOperator_Details::BitwiseAndAssign;
    using BitwiseOrAssign = BinaryOperator_Details::BitwiseOrAssign;
    using BitwiseXorAssign = BinaryOperator_Details::BitwiseXorAssign;
    using BitwiseLeftShiftAssign = BinaryOperator_Details::BitwiseLeftShiftAssign;
    using BitwiseRightShiftAssign = BinaryOperator_Details::BitwiseRightShiftAssign;
    using AddAssign = BinaryOperator_Details::AddAssign;
    using SubtractAssign = BinaryOperator_Details::SubtractAssign;
    using MultiplyAssign = BinaryOperator_Details::MultiplyAssign;
    using ModuloAssign = BinaryOperator_Details::ModuloAssign;
    using DivideAssign = BinaryOperator_Details::DivideAssign;
    using NoneCoalescingAssign = BinaryOperator_Details::NoneCoalescingAssign;
    using Garbage = BinaryOperator_Details::Garbage;
ErrorOr<DeprecatedString> debug_description() const;
bool equals(parser::BinaryOperator const rhs_op) const;
bool is_assignment() const;
};
struct EnumVariantPatternArgument {
  public:
public: JaktInternal::Optional<DeprecatedString> name;public: JaktInternal::Optional<utility::Span> name_span;public: DeprecatedString binding;public: utility::Span span;public: bool is_reference;public: bool is_mutable;public: utility::Span name_in_enum_span() const;
public: DeprecatedString name_in_enum() const;
public: EnumVariantPatternArgument(JaktInternal::Optional<DeprecatedString> a_name, JaktInternal::Optional<utility::Span> a_name_span, DeprecatedString a_binding, utility::Span a_span, bool a_is_reference, bool a_is_mutable);

public: bool equals(parser::EnumVariantPatternArgument const rhs_variant_pattern_argument) const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ParsedExpression_Details {
struct Boolean {
bool val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Boolean(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct NumericConstant {
parser::NumericConstant val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
NumericConstant(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct QuotedString {
DeprecatedString val;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
QuotedString(_MemberT0&& member_0, _MemberT1&& member_1):
val{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct SingleQuotedString {
DeprecatedString val;
JaktInternal::Optional<DeprecatedString> prefix;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
SingleQuotedString(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
val{ forward<_MemberT0>(member_0)},
prefix{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Call {
parser::ParsedCall call;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Call(_MemberT0&& member_0, _MemberT1&& member_1):
call{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct MethodCall {
NonnullRefPtr<typename parser::ParsedExpression> expr;
parser::ParsedCall call;
bool is_optional;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
MethodCall(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
call{ forward<_MemberT1>(member_1)},
is_optional{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct IndexedTuple {
NonnullRefPtr<typename parser::ParsedExpression> expr;
size_t index;
bool is_optional;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
IndexedTuple(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
is_optional{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct IndexedStruct {
NonnullRefPtr<typename parser::ParsedExpression> expr;
DeprecatedString field_name;
bool is_optional;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
IndexedStruct(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
field_name{ forward<_MemberT1>(member_1)},
is_optional{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct ComptimeIndex {
NonnullRefPtr<typename parser::ParsedExpression> expr;
NonnullRefPtr<typename parser::ParsedExpression> index;
bool is_optional;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
ComptimeIndex(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
is_optional{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Var {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Var(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct IndexedExpression {
NonnullRefPtr<typename parser::ParsedExpression> base;
NonnullRefPtr<typename parser::ParsedExpression> index;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
IndexedExpression(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
base{ forward<_MemberT0>(member_0)},
index{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct UnaryOp {
NonnullRefPtr<typename parser::ParsedExpression> expr;
parser::UnaryOperator op;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
UnaryOp(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
expr{ forward<_MemberT0>(member_0)},
op{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct BinaryOp {
NonnullRefPtr<typename parser::ParsedExpression> lhs;
parser::BinaryOperator op;
NonnullRefPtr<typename parser::ParsedExpression> rhs;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
BinaryOp(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
lhs{ forward<_MemberT0>(member_0)},
op{ forward<_MemberT1>(member_1)},
rhs{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Operator {
parser::BinaryOperator op;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Operator(_MemberT0&& member_0, _MemberT1&& member_1):
op{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct OptionalSome {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
OptionalSome(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct OptionalNone{
utility::Span value;
template<typename _MemberT0>
OptionalNone(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct JaktArray {
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> fill_size;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
JaktArray(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
values{ forward<_MemberT0>(member_0)},
fill_size{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct JaktDictionary {
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> values;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
JaktDictionary(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Set {
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Set(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct JaktTuple {
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
JaktTuple(_MemberT0&& member_0, _MemberT1&& member_1):
values{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Range {
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> from;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> to;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Range(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
from{ forward<_MemberT0>(member_0)},
to{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct ForcedUnwrap {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ForcedUnwrap(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Match {
NonnullRefPtr<typename parser::ParsedExpression> expr;
JaktInternal::DynamicArray<parser::ParsedMatchCase> cases;
utility::Span span;
utility::Span marker_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Match(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
cases{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)},
marker_span{ forward<_MemberT3>(member_3)}
{}
};
struct EnumVariantArg {
NonnullRefPtr<typename parser::ParsedExpression> expr;
parser::EnumVariantPatternArgument arg;
NonnullRefPtr<typename parser::ParsedType> enum_variant;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
EnumVariantArg(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
arg{ forward<_MemberT1>(member_1)},
enum_variant{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct NamespacedVar {
DeprecatedString name;
JaktInternal::DynamicArray<DeprecatedString> namespace_;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
NamespacedVar(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
name{ forward<_MemberT0>(member_0)},
namespace_{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Function {
JaktInternal::DynamicArray<parser::ParsedCapture> captures;
JaktInternal::DynamicArray<parser::ParsedParameter> params;
bool can_throw;
bool is_fat_arrow;
NonnullRefPtr<typename parser::ParsedType> return_type;
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5, typename _MemberT6>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5, _MemberT6&& member_6):
captures{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
can_throw{ forward<_MemberT2>(member_2)},
is_fat_arrow{ forward<_MemberT3>(member_3)},
return_type{ forward<_MemberT4>(member_4)},
block{ forward<_MemberT5>(member_5)},
span{ forward<_MemberT6>(member_6)}
{}
};
struct Try {
NonnullRefPtr<typename parser::ParsedExpression> expr;
JaktInternal::Optional<parser::ParsedBlock> catch_block;
JaktInternal::Optional<utility::Span> catch_span;
JaktInternal::Optional<DeprecatedString> catch_name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
Try(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
expr{ forward<_MemberT0>(member_0)},
catch_block{ forward<_MemberT1>(member_1)},
catch_span{ forward<_MemberT2>(member_2)},
catch_name{ forward<_MemberT3>(member_3)},
span{ forward<_MemberT4>(member_4)}
{}
};
struct TryBlock {
NonnullRefPtr<typename parser::ParsedStatement> stmt;
DeprecatedString error_name;
utility::Span error_span;
parser::ParsedBlock catch_block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
TryBlock(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
stmt{ forward<_MemberT0>(member_0)},
error_name{ forward<_MemberT1>(member_1)},
error_span{ forward<_MemberT2>(member_2)},
catch_block{ forward<_MemberT3>(member_3)},
span{ forward<_MemberT4>(member_4)}
{}
};
struct Reflect {
NonnullRefPtr<typename parser::ParsedType> type;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Reflect(_MemberT0&& member_0, _MemberT1&& member_1):
type{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Garbage{
utility::Span value;
template<typename _MemberT0>
Garbage(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Unsafe {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Unsafe(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct ParsedExpression : public Variant<ParsedExpression_Details::Boolean, ParsedExpression_Details::NumericConstant, ParsedExpression_Details::QuotedString, ParsedExpression_Details::SingleQuotedString, ParsedExpression_Details::Call, ParsedExpression_Details::MethodCall, ParsedExpression_Details::IndexedTuple, ParsedExpression_Details::IndexedStruct, ParsedExpression_Details::ComptimeIndex, ParsedExpression_Details::Var, ParsedExpression_Details::IndexedExpression, ParsedExpression_Details::UnaryOp, ParsedExpression_Details::BinaryOp, ParsedExpression_Details::Operator, ParsedExpression_Details::OptionalSome, ParsedExpression_Details::OptionalNone, ParsedExpression_Details::JaktArray, ParsedExpression_Details::JaktDictionary, ParsedExpression_Details::Set, ParsedExpression_Details::JaktTuple, ParsedExpression_Details::Range, ParsedExpression_Details::ForcedUnwrap, ParsedExpression_Details::Match, ParsedExpression_Details::EnumVariantArg, ParsedExpression_Details::NamespacedVar, ParsedExpression_Details::Function, ParsedExpression_Details::Try, ParsedExpression_Details::TryBlock, ParsedExpression_Details::Reflect, ParsedExpression_Details::Garbage, ParsedExpression_Details::Unsafe>, public RefCounted<ParsedExpression> {
using Variant<ParsedExpression_Details::Boolean, ParsedExpression_Details::NumericConstant, ParsedExpression_Details::QuotedString, ParsedExpression_Details::SingleQuotedString, ParsedExpression_Details::Call, ParsedExpression_Details::MethodCall, ParsedExpression_Details::IndexedTuple, ParsedExpression_Details::IndexedStruct, ParsedExpression_Details::ComptimeIndex, ParsedExpression_Details::Var, ParsedExpression_Details::IndexedExpression, ParsedExpression_Details::UnaryOp, ParsedExpression_Details::BinaryOp, ParsedExpression_Details::Operator, ParsedExpression_Details::OptionalSome, ParsedExpression_Details::OptionalNone, ParsedExpression_Details::JaktArray, ParsedExpression_Details::JaktDictionary, ParsedExpression_Details::Set, ParsedExpression_Details::JaktTuple, ParsedExpression_Details::Range, ParsedExpression_Details::ForcedUnwrap, ParsedExpression_Details::Match, ParsedExpression_Details::EnumVariantArg, ParsedExpression_Details::NamespacedVar, ParsedExpression_Details::Function, ParsedExpression_Details::Try, ParsedExpression_Details::TryBlock, ParsedExpression_Details::Reflect, ParsedExpression_Details::Garbage, ParsedExpression_Details::Unsafe>::Variant;
    using Boolean = ParsedExpression_Details::Boolean;
    using NumericConstant = ParsedExpression_Details::NumericConstant;
    using QuotedString = ParsedExpression_Details::QuotedString;
    using SingleQuotedString = ParsedExpression_Details::SingleQuotedString;
    using Call = ParsedExpression_Details::Call;
    using MethodCall = ParsedExpression_Details::MethodCall;
    using IndexedTuple = ParsedExpression_Details::IndexedTuple;
    using IndexedStruct = ParsedExpression_Details::IndexedStruct;
    using ComptimeIndex = ParsedExpression_Details::ComptimeIndex;
    using Var = ParsedExpression_Details::Var;
    using IndexedExpression = ParsedExpression_Details::IndexedExpression;
    using UnaryOp = ParsedExpression_Details::UnaryOp;
    using BinaryOp = ParsedExpression_Details::BinaryOp;
    using Operator = ParsedExpression_Details::Operator;
    using OptionalSome = ParsedExpression_Details::OptionalSome;
    using OptionalNone = ParsedExpression_Details::OptionalNone;
    using JaktArray = ParsedExpression_Details::JaktArray;
    using JaktDictionary = ParsedExpression_Details::JaktDictionary;
    using Set = ParsedExpression_Details::Set;
    using JaktTuple = ParsedExpression_Details::JaktTuple;
    using Range = ParsedExpression_Details::Range;
    using ForcedUnwrap = ParsedExpression_Details::ForcedUnwrap;
    using Match = ParsedExpression_Details::Match;
    using EnumVariantArg = ParsedExpression_Details::EnumVariantArg;
    using NamespacedVar = ParsedExpression_Details::NamespacedVar;
    using Function = ParsedExpression_Details::Function;
    using Try = ParsedExpression_Details::Try;
    using TryBlock = ParsedExpression_Details::TryBlock;
    using Reflect = ParsedExpression_Details::Reflect;
    using Garbage = ParsedExpression_Details::Garbage;
    using Unsafe = ParsedExpression_Details::Unsafe;
template<typename V, typename... Args> static auto __jakt_create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) ParsedExpression(V(forward<Args>(args)...)));
}
ErrorOr<DeprecatedString> debug_description() const;
bool equals(NonnullRefPtr<typename parser::ParsedExpression> const rhs_expression) const;
utility::Span span() const;
i64 precedence() const;
};
struct ParsedNamespace {
  public:
public: JaktInternal::Optional<DeprecatedString> name;public: JaktInternal::Optional<utility::Span> name_span;public: JaktInternal::DynamicArray<parser::ParsedFunction> functions;public: JaktInternal::DynamicArray<parser::ParsedRecord> records;public: JaktInternal::DynamicArray<parser::ParsedTrait> traits;public: JaktInternal::DynamicArray<parser::ParsedExternalTraitImplementation> external_trait_implementations;public: JaktInternal::DynamicArray<parser::ParsedNamespace> namespaces;public: JaktInternal::DynamicArray<parser::ParsedAlias> aliases;public: JaktInternal::DynamicArray<parser::ParsedModuleImport> module_imports;public: JaktInternal::DynamicArray<parser::ParsedExternImport> extern_imports;public: JaktInternal::Optional<DeprecatedString> import_path_if_extern;public: JaktInternal::DynamicArray<parser::IncludeAction> generating_import_extern_before_include;public: JaktInternal::DynamicArray<parser::IncludeAction> generating_import_extern_after_include;public: JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>> forall_chunks;public: ErrorOr<void> add_child_namespace(parser::ParsedNamespace const namespace_);
public: ParsedNamespace(JaktInternal::Optional<DeprecatedString> a_name, JaktInternal::Optional<utility::Span> a_name_span, JaktInternal::DynamicArray<parser::ParsedFunction> a_functions, JaktInternal::DynamicArray<parser::ParsedRecord> a_records, JaktInternal::DynamicArray<parser::ParsedTrait> a_traits, JaktInternal::DynamicArray<parser::ParsedExternalTraitImplementation> a_external_trait_implementations, JaktInternal::DynamicArray<parser::ParsedNamespace> a_namespaces, JaktInternal::DynamicArray<parser::ParsedAlias> a_aliases, JaktInternal::DynamicArray<parser::ParsedModuleImport> a_module_imports, JaktInternal::DynamicArray<parser::ParsedExternImport> a_extern_imports, JaktInternal::Optional<DeprecatedString> a_import_path_if_extern, JaktInternal::DynamicArray<parser::IncludeAction> a_generating_import_extern_before_include, JaktInternal::DynamicArray<parser::IncludeAction> a_generating_import_extern_after_include, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>> a_forall_chunks);

public: bool is_equivalent_to(parser::ParsedNamespace const other) const;
public: ErrorOr<void> add_extern_import(parser::ParsedExternImport const import_);
public: ErrorOr<void> add_alias(parser::ParsedAlias const alias);
public: ErrorOr<void> merge_with(parser::ParsedNamespace const namespace_);
public: ErrorOr<void> add_module_import(parser::ParsedModuleImport const import_);
public: ErrorOr<DeprecatedString> debug_description() const;
};struct ValueEnumVariant {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> value;public: ValueEnumVariant(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace DefinitionLinkage_Details {
struct Internal {
};
struct External {
};
}
struct DefinitionLinkage : public Variant<DefinitionLinkage_Details::Internal, DefinitionLinkage_Details::External> {
using Variant<DefinitionLinkage_Details::Internal, DefinitionLinkage_Details::External>::Variant;
    using Internal = DefinitionLinkage_Details::Internal;
    using External = DefinitionLinkage_Details::External;
ErrorOr<DeprecatedString> debug_description() const;
};
namespace RecordType_Details {
struct Struct {
JaktInternal::DynamicArray<parser::ParsedField> fields;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type;
template<typename _MemberT0, typename _MemberT1>
Struct(_MemberT0&& member_0, _MemberT1&& member_1):
fields{ forward<_MemberT0>(member_0)},
super_type{ forward<_MemberT1>(member_1)}
{}
};
struct Class {
JaktInternal::DynamicArray<parser::ParsedField> fields;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type;
template<typename _MemberT0, typename _MemberT1>
Class(_MemberT0&& member_0, _MemberT1&& member_1):
fields{ forward<_MemberT0>(member_0)},
super_type{ forward<_MemberT1>(member_1)}
{}
};
struct ValueEnum {
NonnullRefPtr<typename parser::ParsedType> underlying_type;
JaktInternal::DynamicArray<parser::ValueEnumVariant> variants;
template<typename _MemberT0, typename _MemberT1>
ValueEnum(_MemberT0&& member_0, _MemberT1&& member_1):
underlying_type{ forward<_MemberT0>(member_0)},
variants{ forward<_MemberT1>(member_1)}
{}
};
struct SumEnum {
bool is_boxed;
JaktInternal::DynamicArray<parser::ParsedField> fields;
JaktInternal::DynamicArray<parser::SumEnumVariant> variants;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
SumEnum(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
is_boxed{ forward<_MemberT0>(member_0)},
fields{ forward<_MemberT1>(member_1)},
variants{ forward<_MemberT2>(member_2)}
{}
};
struct Garbage {
};
}
struct RecordType : public Variant<RecordType_Details::Struct, RecordType_Details::Class, RecordType_Details::ValueEnum, RecordType_Details::SumEnum, RecordType_Details::Garbage> {
using Variant<RecordType_Details::Struct, RecordType_Details::Class, RecordType_Details::ValueEnum, RecordType_Details::SumEnum, RecordType_Details::Garbage>::Variant;
    using Struct = RecordType_Details::Struct;
    using Class = RecordType_Details::Class;
    using ValueEnum = RecordType_Details::ValueEnum;
    using SumEnum = RecordType_Details::SumEnum;
    using Garbage = RecordType_Details::Garbage;
ErrorOr<DeprecatedString> debug_description() const;
ErrorOr<DeprecatedString> record_type_name() const;
};
struct ParsedRecord {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<parser::ParsedGenericParameter> generic_parameters;public: parser::DefinitionLinkage definition_linkage;public: JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> implements_list;public: JaktInternal::DynamicArray<parser::ParsedMethod> methods;public: parser::RecordType record_type;public: JaktInternal::Optional<parser::ExternalName> external_name;public: ParsedRecord(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> a_implements_list, JaktInternal::DynamicArray<parser::ParsedMethod> a_methods, parser::RecordType a_record_type, JaktInternal::Optional<parser::ExternalName> a_external_name);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ParsedMatchBody_Details {
struct Expression{
NonnullRefPtr<typename parser::ParsedExpression> value;
template<typename _MemberT0>
Expression(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Block{
parser::ParsedBlock value;
template<typename _MemberT0>
Block(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct ParsedMatchBody : public Variant<ParsedMatchBody_Details::Expression, ParsedMatchBody_Details::Block> {
using Variant<ParsedMatchBody_Details::Expression, ParsedMatchBody_Details::Block>::Variant;
    using Expression = ParsedMatchBody_Details::Expression;
    using Block = ParsedMatchBody_Details::Block;
ErrorOr<DeprecatedString> debug_description() const;
bool equals(parser::ParsedMatchBody const rhs_match_body) const;
};
struct ParsedMatchCase {
  public:
public: JaktInternal::DynamicArray<parser::ParsedMatchPattern> patterns;public: utility::Span marker_span;public: parser::ParsedMatchBody body;public: bool has_equal_pattern(parser::ParsedMatchCase const rhs_match_case) const;
public: bool equals(parser::ParsedMatchCase const rhs_match_case) const;
public: ParsedMatchCase(JaktInternal::DynamicArray<parser::ParsedMatchPattern> a_patterns, utility::Span a_marker_span, parser::ParsedMatchBody a_body);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedExternImport {
  public:
public: bool is_c;public: parser::ParsedNamespace assigned_namespace;public: JaktInternal::DynamicArray<parser::IncludeAction> before_include;public: JaktInternal::DynamicArray<parser::IncludeAction> after_include;public: bool should_auto_import;public: ErrorOr<bool> is_equivalent_to(parser::ParsedExternImport const other) const;
public: ParsedExternImport(bool a_is_c, parser::ParsedNamespace a_assigned_namespace, JaktInternal::DynamicArray<parser::IncludeAction> a_before_include, JaktInternal::DynamicArray<parser::IncludeAction> a_after_include, bool a_should_auto_import);

public: DeprecatedString get_path() const;
public: DeprecatedString get_name() const;
public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ParsedTraitRequirements_Details {
struct Nothing {
};
struct Methods{
JaktInternal::DynamicArray<parser::ParsedFunction> value;
template<typename _MemberT0>
Methods(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct ComptimeExpression{
NonnullRefPtr<typename parser::ParsedExpression> value;
template<typename _MemberT0>
ComptimeExpression(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct ParsedTraitRequirements : public Variant<ParsedTraitRequirements_Details::Nothing, ParsedTraitRequirements_Details::Methods, ParsedTraitRequirements_Details::ComptimeExpression> {
using Variant<ParsedTraitRequirements_Details::Nothing, ParsedTraitRequirements_Details::Methods, ParsedTraitRequirements_Details::ComptimeExpression>::Variant;
    using Nothing = ParsedTraitRequirements_Details::Nothing;
    using Methods = ParsedTraitRequirements_Details::Methods;
    using ComptimeExpression = ParsedTraitRequirements_Details::ComptimeExpression;
ErrorOr<DeprecatedString> debug_description() const;
};
struct SumEnumVariant {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedVarDecl>> params;public: JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>>>> default_values;public: SumEnumVariant(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedVarDecl>> a_params, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>>>> a_default_values);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedTypeQualifiers {
  public:
public: bool is_mutable;public: bool is_immutable;public: ParsedTypeQualifiers(bool a_is_mutable, bool a_is_immutable);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ParsedType_Details {
struct Name {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Name(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct NamespacedName {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
DeprecatedString name;
JaktInternal::DynamicArray<DeprecatedString> namespaces;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> params;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
NamespacedName(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
qualifiers{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
namespaces{ forward<_MemberT2>(member_2)},
params{ forward<_MemberT3>(member_3)},
span{ forward<_MemberT4>(member_4)}
{}
};
struct GenericType {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
DeprecatedString name;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> generic_parameters;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
GenericType(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
qualifiers{ forward<_MemberT0>(member_0)},
name{ forward<_MemberT1>(member_1)},
generic_parameters{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct JaktArray {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
JaktArray(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
inner{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Dictionary {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> key;
NonnullRefPtr<typename parser::ParsedType> value;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Dictionary(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
qualifiers{ forward<_MemberT0>(member_0)},
key{ forward<_MemberT1>(member_1)},
value{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct JaktTuple {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> types;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
JaktTuple(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
types{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Set {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Set(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
inner{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Optional {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Optional(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
inner{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Reference {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Reference(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
inner{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct MutableReference {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
MutableReference(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
inner{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct RawPtr {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
RawPtr(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
inner{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct WeakPtr {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> inner;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
WeakPtr(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
inner{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct Function {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
JaktInternal::DynamicArray<parser::ParsedParameter> params;
bool can_throw;
NonnullRefPtr<typename parser::ParsedType> return_type;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4>
Function(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4):
qualifiers{ forward<_MemberT0>(member_0)},
params{ forward<_MemberT1>(member_1)},
can_throw{ forward<_MemberT2>(member_2)},
return_type{ forward<_MemberT3>(member_3)},
span{ forward<_MemberT4>(member_4)}
{}
};
struct Const {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
Const(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
qualifiers{ forward<_MemberT0>(member_0)},
expr{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct DependentType {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
NonnullRefPtr<typename parser::ParsedType> base;
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
DependentType(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
qualifiers{ forward<_MemberT0>(member_0)},
base{ forward<_MemberT1>(member_1)},
name{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Empty {
JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers;
template<typename _MemberT0>
Empty(_MemberT0&& member_0):
qualifiers{ forward<_MemberT0>(member_0)}
{}
};
}
struct ParsedType : public Variant<ParsedType_Details::Name, ParsedType_Details::NamespacedName, ParsedType_Details::GenericType, ParsedType_Details::JaktArray, ParsedType_Details::Dictionary, ParsedType_Details::JaktTuple, ParsedType_Details::Set, ParsedType_Details::Optional, ParsedType_Details::Reference, ParsedType_Details::MutableReference, ParsedType_Details::RawPtr, ParsedType_Details::WeakPtr, ParsedType_Details::Function, ParsedType_Details::Const, ParsedType_Details::DependentType, ParsedType_Details::Empty>, public RefCounted<ParsedType> {
using Variant<ParsedType_Details::Name, ParsedType_Details::NamespacedName, ParsedType_Details::GenericType, ParsedType_Details::JaktArray, ParsedType_Details::Dictionary, ParsedType_Details::JaktTuple, ParsedType_Details::Set, ParsedType_Details::Optional, ParsedType_Details::Reference, ParsedType_Details::MutableReference, ParsedType_Details::RawPtr, ParsedType_Details::WeakPtr, ParsedType_Details::Function, ParsedType_Details::Const, ParsedType_Details::DependentType, ParsedType_Details::Empty>::Variant;
    using Name = ParsedType_Details::Name;
    using NamespacedName = ParsedType_Details::NamespacedName;
    using GenericType = ParsedType_Details::GenericType;
    using JaktArray = ParsedType_Details::JaktArray;
    using Dictionary = ParsedType_Details::Dictionary;
    using JaktTuple = ParsedType_Details::JaktTuple;
    using Set = ParsedType_Details::Set;
    using Optional = ParsedType_Details::Optional;
    using Reference = ParsedType_Details::Reference;
    using MutableReference = ParsedType_Details::MutableReference;
    using RawPtr = ParsedType_Details::RawPtr;
    using WeakPtr = ParsedType_Details::WeakPtr;
    using Function = ParsedType_Details::Function;
    using Const = ParsedType_Details::Const;
    using DependentType = ParsedType_Details::DependentType;
    using Empty = ParsedType_Details::Empty;
template<typename V, typename... Args> static auto __jakt_create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) ParsedType(V(forward<Args>(args)...)));
}
ErrorOr<DeprecatedString> debug_description() const;
JaktInternal::Optional<parser::ParsedTypeQualifiers> const& qualifiers() const { switch(this->index()) {case 0 /* Name */: return this->template get<ParsedType::Name>().qualifiers;
case 1 /* NamespacedName */: return this->template get<ParsedType::NamespacedName>().qualifiers;
case 2 /* GenericType */: return this->template get<ParsedType::GenericType>().qualifiers;
case 3 /* JaktArray */: return this->template get<ParsedType::JaktArray>().qualifiers;
case 4 /* Dictionary */: return this->template get<ParsedType::Dictionary>().qualifiers;
case 5 /* JaktTuple */: return this->template get<ParsedType::JaktTuple>().qualifiers;
case 6 /* Set */: return this->template get<ParsedType::Set>().qualifiers;
case 7 /* Optional */: return this->template get<ParsedType::Optional>().qualifiers;
case 8 /* Reference */: return this->template get<ParsedType::Reference>().qualifiers;
case 9 /* MutableReference */: return this->template get<ParsedType::MutableReference>().qualifiers;
case 10 /* RawPtr */: return this->template get<ParsedType::RawPtr>().qualifiers;
case 11 /* WeakPtr */: return this->template get<ParsedType::WeakPtr>().qualifiers;
case 12 /* Function */: return this->template get<ParsedType::Function>().qualifiers;
case 13 /* Const */: return this->template get<ParsedType::Const>().qualifiers;
case 14 /* DependentType */: return this->template get<ParsedType::DependentType>().qualifiers;
case 15 /* Empty */: return this->template get<ParsedType::Empty>().qualifiers;
default: VERIFY_NOT_REACHED();
}
}
bool equals(NonnullRefPtr<typename parser::ParsedType> const rhs_parsed_type) const;
utility::Span span() const;
};
struct ParsedNameWithGenericParameters {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> generic_parameters;public: ParsedNameWithGenericParameters(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> a_generic_parameters);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedVarDecl {
  public:
public: DeprecatedString name;public: NonnullRefPtr<typename parser::ParsedType> parsed_type;public: bool is_mutable;public: JaktInternal::Optional<utility::Span> inlay_span;public: utility::Span span;public: JaktInternal::Optional<parser::ExternalName> external_name;public: bool equals(parser::ParsedVarDecl const rhs_var_decl) const;
public: ParsedVarDecl(DeprecatedString a_name, NonnullRefPtr<typename parser::ParsedType> a_parsed_type, bool a_is_mutable, JaktInternal::Optional<utility::Span> a_inlay_span, utility::Span a_span, JaktInternal::Optional<parser::ExternalName> a_external_name);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedPatternDefault {
  public:
public: parser::ParsedVarDecl variable;public: NonnullRefPtr<typename parser::ParsedExpression> value;public: ParsedPatternDefault(parser::ParsedVarDecl a_variable, NonnullRefPtr<typename parser::ParsedExpression> a_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ParsedCapture_Details {
struct ByValue {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByValue(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByReference {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByReference(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByMutableReference {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByMutableReference(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct ByComptimeDependency {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
ByComptimeDependency(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct AllByReference {
DeprecatedString name;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
AllByReference(_MemberT0&& member_0, _MemberT1&& member_1):
name{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
}
struct ParsedCapture : public Variant<ParsedCapture_Details::ByValue, ParsedCapture_Details::ByReference, ParsedCapture_Details::ByMutableReference, ParsedCapture_Details::ByComptimeDependency, ParsedCapture_Details::AllByReference> {
using Variant<ParsedCapture_Details::ByValue, ParsedCapture_Details::ByReference, ParsedCapture_Details::ByMutableReference, ParsedCapture_Details::ByComptimeDependency, ParsedCapture_Details::AllByReference>::Variant;
    using ByValue = ParsedCapture_Details::ByValue;
    using ByReference = ParsedCapture_Details::ByReference;
    using ByMutableReference = ParsedCapture_Details::ByMutableReference;
    using ByComptimeDependency = ParsedCapture_Details::ByComptimeDependency;
    using AllByReference = ParsedCapture_Details::AllByReference;
ErrorOr<DeprecatedString> debug_description() const;
DeprecatedString const& name() const { switch(this->index()) {case 0 /* ByValue */: return this->template get<ParsedCapture::ByValue>().name;
case 1 /* ByReference */: return this->template get<ParsedCapture::ByReference>().name;
case 2 /* ByMutableReference */: return this->template get<ParsedCapture::ByMutableReference>().name;
case 3 /* ByComptimeDependency */: return this->template get<ParsedCapture::ByComptimeDependency>().name;
case 4 /* AllByReference */: return this->template get<ParsedCapture::AllByReference>().name;
default: VERIFY_NOT_REACHED();
}
}
utility::Span const& span() const { switch(this->index()) {case 0 /* ByValue */: return this->template get<ParsedCapture::ByValue>().span;
case 1 /* ByReference */: return this->template get<ParsedCapture::ByReference>().span;
case 2 /* ByMutableReference */: return this->template get<ParsedCapture::ByMutableReference>().span;
case 3 /* ByComptimeDependency */: return this->template get<ParsedCapture::ByComptimeDependency>().span;
case 4 /* AllByReference */: return this->template get<ParsedCapture::AllByReference>().span;
default: VERIFY_NOT_REACHED();
}
}
};
namespace ParsedStatement_Details {
struct Expression {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Expression(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Defer {
NonnullRefPtr<typename parser::ParsedStatement> statement;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Defer(_MemberT0&& member_0, _MemberT1&& member_1):
statement{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct UnsafeBlock {
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
UnsafeBlock(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct DestructuringAssignment {
JaktInternal::DynamicArray<parser::ParsedVarDecl> vars;
NonnullRefPtr<typename parser::ParsedStatement> var_decl;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
DestructuringAssignment(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
vars{ forward<_MemberT0>(member_0)},
var_decl{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct VarDecl {
parser::ParsedVarDecl var;
NonnullRefPtr<typename parser::ParsedExpression> init;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
VarDecl(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
var{ forward<_MemberT0>(member_0)},
init{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct If {
NonnullRefPtr<typename parser::ParsedExpression> condition;
parser::ParsedBlock then_block;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> else_statement;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
If(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
condition{ forward<_MemberT0>(member_0)},
then_block{ forward<_MemberT1>(member_1)},
else_statement{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Block {
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Block(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Loop {
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Loop(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct While {
NonnullRefPtr<typename parser::ParsedExpression> condition;
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
While(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
condition{ forward<_MemberT0>(member_0)},
block{ forward<_MemberT1>(member_1)},
span{ forward<_MemberT2>(member_2)}
{}
};
struct For {
DeprecatedString iterator_name;
utility::Span name_span;
bool is_destructuring;
NonnullRefPtr<typename parser::ParsedExpression> range;
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3, typename _MemberT4, typename _MemberT5>
For(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3, _MemberT4&& member_4, _MemberT5&& member_5):
iterator_name{ forward<_MemberT0>(member_0)},
name_span{ forward<_MemberT1>(member_1)},
is_destructuring{ forward<_MemberT2>(member_2)},
range{ forward<_MemberT3>(member_3)},
block{ forward<_MemberT4>(member_4)},
span{ forward<_MemberT5>(member_5)}
{}
};
struct Break{
utility::Span value;
template<typename _MemberT0>
Break(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Continue{
utility::Span value;
template<typename _MemberT0>
Continue(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
struct Return {
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Return(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Throw {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Throw(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Yield {
NonnullRefPtr<typename parser::ParsedExpression> expr;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
Yield(_MemberT0&& member_0, _MemberT1&& member_1):
expr{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct InlineCpp {
parser::ParsedBlock block;
utility::Span span;
template<typename _MemberT0, typename _MemberT1>
InlineCpp(_MemberT0&& member_0, _MemberT1&& member_1):
block{ forward<_MemberT0>(member_0)},
span{ forward<_MemberT1>(member_1)}
{}
};
struct Guard {
NonnullRefPtr<typename parser::ParsedExpression> expr;
parser::ParsedBlock else_block;
parser::ParsedBlock remaining_code;
utility::Span span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
Guard(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
expr{ forward<_MemberT0>(member_0)},
else_block{ forward<_MemberT1>(member_1)},
remaining_code{ forward<_MemberT2>(member_2)},
span{ forward<_MemberT3>(member_3)}
{}
};
struct Garbage{
utility::Span value;
template<typename _MemberT0>
Garbage(_MemberT0&& member_0):
value{ forward<_MemberT0>(member_0)}
{}
};
}
struct ParsedStatement : public Variant<ParsedStatement_Details::Expression, ParsedStatement_Details::Defer, ParsedStatement_Details::UnsafeBlock, ParsedStatement_Details::DestructuringAssignment, ParsedStatement_Details::VarDecl, ParsedStatement_Details::If, ParsedStatement_Details::Block, ParsedStatement_Details::Loop, ParsedStatement_Details::While, ParsedStatement_Details::For, ParsedStatement_Details::Break, ParsedStatement_Details::Continue, ParsedStatement_Details::Return, ParsedStatement_Details::Throw, ParsedStatement_Details::Yield, ParsedStatement_Details::InlineCpp, ParsedStatement_Details::Guard, ParsedStatement_Details::Garbage>, public RefCounted<ParsedStatement> {
using Variant<ParsedStatement_Details::Expression, ParsedStatement_Details::Defer, ParsedStatement_Details::UnsafeBlock, ParsedStatement_Details::DestructuringAssignment, ParsedStatement_Details::VarDecl, ParsedStatement_Details::If, ParsedStatement_Details::Block, ParsedStatement_Details::Loop, ParsedStatement_Details::While, ParsedStatement_Details::For, ParsedStatement_Details::Break, ParsedStatement_Details::Continue, ParsedStatement_Details::Return, ParsedStatement_Details::Throw, ParsedStatement_Details::Yield, ParsedStatement_Details::InlineCpp, ParsedStatement_Details::Guard, ParsedStatement_Details::Garbage>::Variant;
    using Expression = ParsedStatement_Details::Expression;
    using Defer = ParsedStatement_Details::Defer;
    using UnsafeBlock = ParsedStatement_Details::UnsafeBlock;
    using DestructuringAssignment = ParsedStatement_Details::DestructuringAssignment;
    using VarDecl = ParsedStatement_Details::VarDecl;
    using If = ParsedStatement_Details::If;
    using Block = ParsedStatement_Details::Block;
    using Loop = ParsedStatement_Details::Loop;
    using While = ParsedStatement_Details::While;
    using For = ParsedStatement_Details::For;
    using Break = ParsedStatement_Details::Break;
    using Continue = ParsedStatement_Details::Continue;
    using Return = ParsedStatement_Details::Return;
    using Throw = ParsedStatement_Details::Throw;
    using Yield = ParsedStatement_Details::Yield;
    using InlineCpp = ParsedStatement_Details::InlineCpp;
    using Guard = ParsedStatement_Details::Guard;
    using Garbage = ParsedStatement_Details::Garbage;
template<typename V, typename... Args> static auto __jakt_create(Args&&... args) {
return adopt_nonnull_ref_or_enomem(new (nothrow) ParsedStatement(V(forward<Args>(args)...)));
}
ErrorOr<DeprecatedString> debug_description() const;
bool equals(NonnullRefPtr<typename parser::ParsedStatement> const rhs_statement) const;
utility::Span span() const;
};
struct CheckedQualifiers {
  public:
public: bool is_immutable;public: bool equals(parser::CheckedQualifiers const other) const;
public: CheckedQualifiers(bool a_is_immutable);

public: public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedName {
  public:
public: DeprecatedString name;public: utility::Span span;public: ParsedName(DeprecatedString a_name, utility::Span a_span);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedAlias {
  public:
public: JaktInternal::Optional<parser::ParsedName> alias_name;public: JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> target;public: ParsedAlias(JaktInternal::Optional<parser::ParsedName> a_alias_name, JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> a_target);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedAttributeArgument {
  public:
public: DeprecatedString name;public: utility::Span span;public: JaktInternal::Optional<DeprecatedString> assigned_value;public: ParsedAttributeArgument(DeprecatedString a_name, utility::Span a_span, JaktInternal::Optional<DeprecatedString> a_assigned_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedMethod {
  public:
public: parser::ParsedFunction parsed_function;public: parser::Visibility visibility;public: bool is_virtual;public: bool is_override;public: ParsedMethod(parser::ParsedFunction a_parsed_function, parser::Visibility a_visibility, bool a_is_virtual, bool a_is_override);

public: ErrorOr<DeprecatedString> debug_description() const;
};namespace ParsedMatchPattern_Details {
struct EnumVariant {
JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults;
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> variant_names;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments;
utility::Span arguments_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2, typename _MemberT3>
EnumVariant(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2, _MemberT3&& member_3):
defaults{ forward<_MemberT0>(member_0)},
variant_names{ forward<_MemberT1>(member_1)},
variant_arguments{ forward<_MemberT2>(member_2)},
arguments_span{ forward<_MemberT3>(member_3)}
{}
};
struct Expression{
JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults;
NonnullRefPtr<typename parser::ParsedExpression> value;
template<typename _MemberT0, typename _MemberT1>
Expression(_MemberT0&& member_0, _MemberT1&& member_1):
defaults{ forward<_MemberT0>(member_0)},
value{ forward<_MemberT1>(member_1)}
{}
};
struct CatchAll {
JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments;
utility::Span arguments_span;
template<typename _MemberT0, typename _MemberT1, typename _MemberT2>
CatchAll(_MemberT0&& member_0, _MemberT1&& member_1, _MemberT2&& member_2):
defaults{ forward<_MemberT0>(member_0)},
variant_arguments{ forward<_MemberT1>(member_1)},
arguments_span{ forward<_MemberT2>(member_2)}
{}
};
struct Invalid {
JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> defaults;
template<typename _MemberT0>
Invalid(_MemberT0&& member_0):
defaults{ forward<_MemberT0>(member_0)}
{}
};
}
struct ParsedMatchPattern : public Variant<ParsedMatchPattern_Details::EnumVariant, ParsedMatchPattern_Details::Expression, ParsedMatchPattern_Details::CatchAll, ParsedMatchPattern_Details::Invalid> {
using Variant<ParsedMatchPattern_Details::EnumVariant, ParsedMatchPattern_Details::Expression, ParsedMatchPattern_Details::CatchAll, ParsedMatchPattern_Details::Invalid>::Variant;
    using EnumVariant = ParsedMatchPattern_Details::EnumVariant;
    using Expression = ParsedMatchPattern_Details::Expression;
    using CatchAll = ParsedMatchPattern_Details::CatchAll;
    using Invalid = ParsedMatchPattern_Details::Invalid;
ErrorOr<DeprecatedString> debug_description() const;
JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> const& defaults() const { switch(this->index()) {case 0 /* EnumVariant */: return this->template get<ParsedMatchPattern::EnumVariant>().defaults;
case 1 /* Expression */: return this->template get<ParsedMatchPattern::Expression>().defaults;
case 2 /* CatchAll */: return this->template get<ParsedMatchPattern::CatchAll>().defaults;
case 3 /* Invalid */: return this->template get<ParsedMatchPattern::Invalid>().defaults;
default: VERIFY_NOT_REACHED();
}
}
bool equals(parser::ParsedMatchPattern const rhs_parsed_match_pattern) const;
bool is_equal_pattern(parser::ParsedMatchPattern const rhs_parsed_match_pattern) const;
bool defaults_equal(JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> const defaults) const;
};
struct VisibilityRestriction {
  public:
public: JaktInternal::DynamicArray<DeprecatedString> namespace_;public: DeprecatedString name;public: VisibilityRestriction(JaktInternal::DynamicArray<DeprecatedString> a_namespace_, DeprecatedString a_name);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedField {
  public:
public: parser::ParsedVarDecl var_decl;public: parser::Visibility visibility;public: JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> default_value;public: ParsedField(parser::ParsedVarDecl a_var_decl, parser::Visibility a_visibility, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_default_value);

public: ErrorOr<DeprecatedString> debug_description() const;
};struct ParsedTrait {
  public:
public: DeprecatedString name;public: utility::Span name_span;public: JaktInternal::DynamicArray<parser::ParsedGenericParameter> generic_parameters;public: parser::ParsedTraitRequirements requirements;public: ParsedTrait(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::ParsedTraitRequirements a_requirements);

public: ErrorOr<DeprecatedString> debug_description() const;
};template <typename T>
T u64_to_float(u64 const number);
}
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::Visibility> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::Visibility const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedBlock> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedBlock const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::FunctionType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::FunctionType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::FunctionLinkage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::FunctionLinkage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ExternalName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ExternalName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::InlineState> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::InlineState const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedFunction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedFunction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ImportList> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ImportList const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVariable> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVariable const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAttribute> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAttribute const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedCall> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedCall const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedGenericParameter> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedGenericParameter const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVarDeclTuple> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVarDeclTuple const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ImportName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ImportName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedModuleImport> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedModuleImport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::IncludeAction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::IncludeAction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::Parser> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::Parser const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExternalTraitImplementation> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExternalTraitImplementation const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ArgumentStoreLevel> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ArgumentStoreLevel const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::NumericConstant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::NumericConstant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::TypeCast> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::TypeCast const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::UnaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::UnaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::BinaryOperator> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::BinaryOperator const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::EnumVariantPatternArgument> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::EnumVariantPatternArgument const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExpression> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExpression const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedNamespace> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedNamespace const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ValueEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ValueEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::DefinitionLinkage> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::DefinitionLinkage const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::RecordType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::RecordType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedRecord> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedRecord const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchBody> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchBody const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchCase> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchCase const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedExternImport> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedExternImport const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTraitRequirements> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTraitRequirements const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::SumEnumVariant> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::SumEnumVariant const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTypeQualifiers> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTypeQualifiers const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedType> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedType const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedNameWithGenericParameters> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedNameWithGenericParameters const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedVarDecl> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedVarDecl const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedPatternDefault> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedPatternDefault const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedCapture> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedCapture const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedStatement> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedStatement const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::CheckedQualifiers> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::CheckedQualifiers const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedName> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedName const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAlias> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAlias const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedAttributeArgument> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedAttributeArgument const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMethod> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMethod const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedMatchPattern> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedMatchPattern const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::VisibilityRestriction> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::VisibilityRestriction const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedField> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedField const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
template<>struct Jakt::Formatter<Jakt::parser::ParsedTrait> : Jakt::Formatter<Jakt::StringView>{
Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::parser::ParsedTrait const& value) {
JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));return format_error;}
};
namespace Jakt {
} // namespace Jakt
