#include "ide.h"
namespace Jakt {
namespace ide {
ErrorOr<ide::JaktSymbol> record_to_symbol(parser::ParsedRecord const record) {
{
JaktInternal::Array<ide::JaktSymbol> children = (TRY((Array<ide::JaktSymbol>::create_with({}))));
utility::Span record_span = ((record).name_span);
String const record_kind = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<ide::JaktSymbol>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();JaktInternal::Array<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_657; {
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField field = (_magic_value.value());
{
TRY((((children).push(ide::JaktSymbol(((((field).var_decl)).name),JaktInternal::OptionalNone(),String("field"),((((field).var_decl)).span),((((field).var_decl)).span),(TRY((Array<ide::JaktSymbol>::create_with({})))))))));
}

}
}

__jakt_var_657 = String("struct"); goto __jakt_label_602;

}
__jakt_label_602:; __jakt_var_657.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();JaktInternal::Array<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_658; {
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField field = (_magic_value.value());
{
TRY((((children).push(ide::JaktSymbol(((((field).var_decl)).name),JaktInternal::OptionalNone(),String("field"),((((field).var_decl)).span),((((field).var_decl)).span),(TRY((Array<ide::JaktSymbol>::create_with({})))))))));
}

}
}

__jakt_var_658 = String("class"); goto __jakt_label_603;

}
__jakt_label_603:; __jakt_var_658.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();JaktInternal::Array<parser::ValueEnumVariant> const& variants = __jakt_match_value.variants;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_659; {
{
JaktInternal::ArrayIterator<parser::ValueEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<parser::ValueEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ValueEnumVariant variant = (_magic_value.value());
{
TRY((((children).push(ide::JaktSymbol(((variant).name),JaktInternal::OptionalNone(),String("enum-member"),((variant).span),((variant).span),(TRY((Array<ide::JaktSymbol>::create_with({})))))))));
}

}
}

__jakt_var_659 = String("enum"); goto __jakt_label_604;

}
__jakt_label_604:; __jakt_var_659.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();JaktInternal::Array<parser::SumEnumVariant> const& variants = __jakt_match_value.variants;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_660; {
{
JaktInternal::ArrayIterator<parser::SumEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<parser::SumEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::SumEnumVariant variant = (_magic_value.value());
{
JaktInternal::Array<ide::JaktSymbol> variant_children = (TRY((Array<ide::JaktSymbol>::create_with({}))));
if (((((variant).params)).has_value())){
{
JaktInternal::ArrayIterator<parser::ParsedVarDecl> _magic = (((((variant).params).value())).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedVarDecl> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedVarDecl param = (_magic_value.value());
{
if ((((param).name) != String(""))){
TRY((((variant_children).push(ide::JaktSymbol(((param).name),JaktInternal::OptionalNone(),String("field"),((param).span),((param).span),(TRY((Array<ide::JaktSymbol>::create_with({})))))))));
}
}

}
}

}
TRY((((children).push(ide::JaktSymbol(((variant).name),JaktInternal::OptionalNone(),String("enum-member"),((variant).span),((variant).span),variant_children)))));
}

}
}

__jakt_var_660 = String("enum"); goto __jakt_label_605;

}
__jakt_label_605:; __jakt_var_660.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::RecordType::Garbage>();
return JaktInternal::ExplicitValue(String("garbage"));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
ide::JaktSymbol const function_symbol = TRY((ide::function_to_symbol(((method).parsed_function),String("method"))));
TRY((((children).push(function_symbol))));
(record_span = TRY((parser::merge_spans(record_span,((function_symbol).range)))));
}

}
}

return (ide::JaktSymbol(((record).name),JaktInternal::OptionalNone(),record_kind,record_span,((record).name_span),children));
}
}

ErrorOr<JaktInternal::Optional<String>> find_typename_in_program(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<String>, ErrorOr<JaktInternal::Optional<String>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::Variable>();String const& name = __jakt_match_value.name;
types::TypeId const& type_id = __jakt_match_value.type_id;
ide::Mutability const& mutability = __jakt_match_value.mutability;
ide::VarType const& var_type = __jakt_match_value.var_type;
ide::VarVisibility const& visibility = __jakt_match_value.visibility;
JaktInternal::Optional<types::TypeId> const& struct_type_id = __jakt_match_value.struct_type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_661; {
String const result = TRY((ide::get_var_signature(program,name,type_id,mutability,var_type,visibility,struct_type_id)));
__jakt_var_661 = static_cast<JaktInternal::Optional<String>>(result); goto __jakt_label_606;

}
__jakt_label_606:; __jakt_var_661.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Call>();
types::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_662; {
String const result = TRY((ide::get_function_signature(program,function_id)));
__jakt_var_662 = static_cast<JaktInternal::Optional<String>>(result); goto __jakt_label_607;

}
__jakt_label_607:; __jakt_var_662.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Typename>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_663; {
String const result = TRY((ide::get_type_signature(program,type_id)));
__jakt_var_663 = static_cast<JaktInternal::Optional<String>>(result); goto __jakt_label_608;

}
__jakt_label_608:; __jakt_var_663.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::NameSet>();
JaktInternal::Array<String> const& names = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_664; {
String output = String("");
bool first = true;
{
JaktInternal::ArrayIterator<String> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
if ((!(first))){
(output += String(" | "));
}
else {
(first = false);
}

(output += name);
}

}
}

__jakt_var_664 = static_cast<JaktInternal::Optional<String>>(output); goto __jakt_label_609;

}
__jakt_label_609:; __jakt_var_664.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::EnumVariant>();String const& name = __jakt_match_value.name;
types::TypeId const& type_id = __jakt_match_value.type_id;
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> const& variants = __jakt_match_value.variants;
JaktInternal::Optional<types::NumberConstant> const& number_constant = __jakt_match_value.number_constant;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<String>> __jakt_var_665; {
String const result = TRY((ide::get_enum_variant_signature(program,name,type_id,variants,number_constant)));
__jakt_var_665 = static_cast<JaktInternal::Optional<String>>(result); goto __jakt_label_610;

}
__jakt_label_610:; __jakt_var_665.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
else {
return (JaktInternal::OptionalNone());
}

}
}

ErrorOr<JaktInternal::Array<String>> completions_for_type_id(NonnullRefPtr<types::CheckedProgram> const program,types::TypeId const type_id) {
{
JaktInternal::Array<String> output = (TRY((Array<String>::create_with({}))));
NonnullRefPtr<types::Type> const ty = ((program)->get_type(type_id));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Array<String>>>{
auto&& __jakt_match_variant = *ty;
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
NonnullRefPtr<types::Scope> const scope = TRY((((program)->get_scope(((enum_).scope_id)))));
TRY((((output).push_values(TRY((ide::find_function_completions_in_scope(scope,program)))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const structure = ((program)->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const field_var = ((program)->get_variable(((field).variable_id)));
TRY((((output).push(((field_var).name)))));
}

}
}

NonnullRefPtr<types::Scope> const scope = TRY((((program)->get_scope(((structure).scope_id)))));
TRY((((output).push_values(TRY((ide::find_function_completions_in_scope(scope,program)))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
{
types::CheckedStruct const structure = ((program)->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const field_var = ((program)->get_variable(((field).variable_id)));
TRY((((output).push(((field_var).name)))));
}

}
}

NonnullRefPtr<types::Scope> const scope = TRY((((program)->get_scope(((structure).scope_id)))));
TRY((((output).push_values(TRY((ide::find_function_completions_in_scope(scope,program)))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
return (output);
}
}

ErrorOr<ide::Usage> get_enum_variant_usage_from_type_id_and_name(NonnullRefPtr<types::CheckedProgram> const program,types::TypeId const type_id,String const name) {
{
{
JaktInternal::ArrayIterator<types::CheckedEnum> _magic = ((((((program)->get_module(((type_id).module))))->enums)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnum> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnum enum_ = (_magic_value.value());
{
if ((!(((((enum_).type_id)).equals(type_id))))){
continue;
}
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if ((((variant).name()) == name)){
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> const variants = TRY((ide::enum_variant_fields(program,variant)));
JaktInternal::Optional<types::NumberConstant> const number_constant = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, ErrorOr<ide::Usage>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();String const& name = __jakt_match_value.name;
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->to_number_constant(program)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
));
utility::Span const span = ((variant).span());
return ( ide::Usage { typename ide::Usage::EnumVariant(span,name,type_id,variants,number_constant) } );
}
}

}
}

utility::panic(String("unreachable: should have found variant"));
}

}
}

utility::panic(String("unreachable: should have found variant"));
}
}

ErrorOr<String> get_enum_variant_signature_from_type_id_and_name(NonnullRefPtr<types::CheckedProgram> const program,types::TypeId const type_id,String const name) {
{
NonnullRefPtr<types::Module> const mod = ((((program)->modules))[((((type_id).module)).id)]);
{
JaktInternal::ArrayIterator<types::CheckedEnum> _magic = ((((mod)->enums)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnum> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnum enum_ = (_magic_value.value());
{
if (((((enum_).type_id)).equals(type_id))){
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& v_name = __jakt_match_value.name;
{
if ((v_name == name)){
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> const params = TRY((ide::enum_variant_fields(program,variant)));
JaktInternal::Optional<types::NumberConstant> const none = JaktInternal::OptionalNone();
return (TRY((ide::get_enum_variant_signature(program,name,type_id,params,none))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& v_name = __jakt_match_value.name;
{
if ((v_name == name)){
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> const params = TRY((ide::enum_variant_fields(program,variant)));
JaktInternal::Optional<types::NumberConstant> const none = JaktInternal::OptionalNone();
return (TRY((ide::get_enum_variant_signature(program,name,type_id,params,none))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();String const& v_name = __jakt_match_value.name;
{
if ((v_name == name)){
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> const params = TRY((ide::enum_variant_fields(program,variant)));
JaktInternal::Optional<types::NumberConstant> const value = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, ErrorOr<String>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_666; {
__jakt_var_666 = ((expr)->to_number_constant(program)); goto __jakt_label_611;

}
__jakt_label_611:; __jakt_var_666.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_667; {
JaktInternal::Optional<types::NumberConstant> const none = JaktInternal::OptionalNone();
__jakt_var_667 = none; goto __jakt_label_612;

}
__jakt_label_612:; __jakt_var_667.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
return (TRY((ide::get_enum_variant_signature(program,name,type_id,params,value))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& v_name = __jakt_match_value.name;
{
if ((v_name == name)){
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> const params = TRY((ide::enum_variant_fields(program,variant)));
JaktInternal::Optional<types::NumberConstant> const none = JaktInternal::OptionalNone();
return (TRY((ide::get_enum_variant_signature(program,name,type_id,params,none))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}

}
}

}
}

}
}

return (String(""));
}
}

ErrorOr<String> get_type_signature(NonnullRefPtr<types::CheckedProgram> const program,types::TypeId const type_id) {
{
types::StructId const array_struct_id = TRY((((program)->find_struct_in_prelude(String("Array")))));
types::StructId const dictionary_struct_id = TRY((((program)->find_struct_in_prelude(String("Dictionary")))));
types::StructId const optional_struct_id = TRY((((program)->find_struct_in_prelude(String("Optional")))));
types::StructId const range_struct_id = TRY((((program)->find_struct_in_prelude(String("Range")))));
types::StructId const set_struct_id = TRY((((program)->find_struct_in_prelude(String("Set")))));
types::StructId const tuple_struct_id = TRY((((program)->find_struct_in_prelude(String("Tuple")))));
types::StructId const weak_ptr_struct_id = TRY((((program)->find_struct_in_prelude(String("WeakPtr")))));
NonnullRefPtr<types::Type> const type = ((program)->get_type(type_id));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Never>();
return JaktInternal::ExplicitValue(String("never"));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Void>();
return JaktInternal::ExplicitValue(String("void"));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Bool>();
return JaktInternal::ExplicitValue(String("bool"));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U8>();
return JaktInternal::ExplicitValue(String("u8"));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U16>();
return JaktInternal::ExplicitValue(String("u16"));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U32>();
return JaktInternal::ExplicitValue(String("u32"));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U64>();
return JaktInternal::ExplicitValue(String("u64"));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I8>();
return JaktInternal::ExplicitValue(String("i8"));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I16>();
return JaktInternal::ExplicitValue(String("i16"));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I32>();
return JaktInternal::ExplicitValue(String("i32"));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I64>();
return JaktInternal::ExplicitValue(String("i64"));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::F32>();
return JaktInternal::ExplicitValue(String("f32"));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::F64>();
return JaktInternal::ExplicitValue(String("f64"));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Usize>();
return JaktInternal::ExplicitValue(String("usize"));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::JaktString>();
return JaktInternal::ExplicitValue(String("String"));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CInt>();
return JaktInternal::ExplicitValue(String("c_int"));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CChar>();
return JaktInternal::ExplicitValue(String("c_char"));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
String const& name = __jakt_match_value.value;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Unknown>();
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_trait(trait_id)))->name));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::Array<types::TypeId> const& params = __jakt_match_value.params;
types::TypeId const& return_type_id = __jakt_match_value.return_type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_668; {
JaktInternal::Array<String> param_names = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId x = (_magic_value.value());
{
TRY((((param_names).push(TRY((((program)->type_name(x))))))));
}

}
}

String const return_type = TRY((((program)->type_name(return_type_id))));
__jakt_var_668 = TRY((String::formatted(String("function({}) -> {}"),utility::join(param_names,String(", ")),return_type))); goto __jakt_label_613;

}
__jakt_label_613:; __jakt_var_668.release_value(); }));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((String("raw ") + TRY((ide::get_type_signature(program,type_id)))));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_669; {
types::CheckedEnum const enum_ = ((program)->get_enum(id));
__jakt_var_669 = ((JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((enum_).is_boxed));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("boxed "));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
 + String("enum ")) + ((enum_).name)); goto __jakt_label_614;

}
__jakt_label_614:; __jakt_var_669.release_value(); }));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_670; {
types::CheckedStruct const struct_ = ((program)->get_struct(id));
__jakt_var_670 = (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();return JaktInternal::ExplicitValue(String("class "));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();return JaktInternal::ExplicitValue(String("struct "));
};/*case end*/
default: {
{
utility::panic(String("unreachable: should've been struct"));
}
};/*case end*/
}/*switch end*/
}()
)) + ((struct_).name)); goto __jakt_label_615;

}
__jakt_label_615:; __jakt_var_670.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_671; {
types::CheckedStruct const record = ((program)->get_struct(id));
String output = ((record).name);
(output += String("<"));
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_671 = (output + String(">")); goto __jakt_label_616;

}
__jakt_label_616:; __jakt_var_671.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_672; {
types::CheckedEnum const enum_ = ((program)->get_enum(id));
String output = String("");
if (((enum_).is_boxed)){
(output += String("boxed "));
}
(output += String("enum "));
(output += ((enum_).name));
(output += String("<"));
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_672 = (output + String(">")); goto __jakt_label_617;

}
__jakt_label_617:; __jakt_var_672.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_673; {
NonnullRefPtr<types::CheckedTrait> const trait_ = ((program)->get_trait(id));
String output = String("");
(output += String("trait "));
(output += ((trait_)->name));
(output += String("<"));
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_673 = (output + String(">")); goto __jakt_label_618;

}
__jakt_label_618:; __jakt_var_673.release_value(); }));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_674; {
if (((id).equals(array_struct_id))){
if (((args).is_empty())){
return (String("[]"));
}
return (TRY((String::formatted(String("[{}]"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)]))))))));
}
if (((id).equals(dictionary_struct_id))){
if ((((args).size()) < static_cast<size_t>(2ULL))){
return (String("[:]"));
}
return (TRY((String::formatted(String("[{}: {}]"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(1LL)]))))))));
}
if (((id).equals(optional_struct_id))){
if (((args).is_empty())){
return (String(""));
}
return (TRY((String::formatted(String("{}?"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)]))))))));
}
if (((id).equals(range_struct_id))){
if (((args).is_empty())){
return (String(""));
}
return (TRY((String::formatted(String("{}..{}"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))),TRY((((program)->type_name(((args)[static_cast<i64>(0LL)])))))))));
}
if (((id).equals(set_struct_id))){
if (((args).is_empty())){
return (String(""));
}
return (TRY((String::formatted(String("{{{}}}"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)]))))))));
}
if (((id).equals(tuple_struct_id))){
String output = String("(");
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
return ((output + String(")")));
}
if (((id).equals(weak_ptr_struct_id))){
if (((args).is_empty())){
return (String(""));
}
return (TRY((String::formatted(String("weak {}?"),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)]))))))));
}
types::CheckedStruct const record = ((program)->get_struct(id));
String output = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();return JaktInternal::ExplicitValue(String("class "));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();return JaktInternal::ExplicitValue(String("struct "));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
utility::panic(String("unreachable: can't be an enum"));
}
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
utility::panic(String("unreachable: can't be an enum"));
}
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::RecordType::Garbage>();
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
(output += ((record).name));
(output += String("<"));
if ((!(((args).is_empty())))){
(output += TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(output += String(", "));
(output += TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_674 = (output + String(">")); goto __jakt_label_619;

}
__jakt_label_619:; __jakt_var_674.release_value(); }));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("&{}"),TRY((((program)->type_name(type_id))))))));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("&mut {}"),TRY((((program)->type_name(type_id))))))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_scope(NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<types::Scope> const scope,utility::Span const span) {
{
{
JaktInternal::DictionaryIterator<String,types::VarId> _magic = ((((scope)->vars)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::VarId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::VarId> scope_var = (_magic_value.value());
{
types::CheckedVariable const var = ((program)->get_variable(((scope_var).get<1>())));
if (((((var).definition_span)).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((var).type_id)) } ));
}
}

}
}

{
JaktInternal::DictionaryIterator<String,JaktInternal::Array<types::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Array<types::FunctionId>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Array<types::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Array<types::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
String const _ = ((jakt_____overload_set__).get<0>());
JaktInternal::Array<types::FunctionId> const overload_set = ((jakt_____overload_set__).get<1>());

{
JaktInternal::ArrayIterator<types::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_function(program,checked_function,span)));
if (((usage).has_value())){
return ((usage.value()));
}
}

}
}

}

}
}

{
JaktInternal::DictionaryIterator<String,types::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::StructId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::StructId> struct_id = (_magic_value.value());
{
types::CheckedStruct const checked_struct = ((program)->get_struct(((struct_id).get<1>())));
JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_struct(program,checked_struct,span)));
if (((usage).has_value())){
return ((usage.value()));
}
}

}
}

{
JaktInternal::DictionaryIterator<String,types::EnumId> _magic = ((((scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::EnumId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::EnumId> enum_id = (_magic_value.value());
{
types::CheckedEnum const checked_enum = ((program)->get_enum(((enum_id).get<1>())));
JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_enum(program,checked_enum,span)));
if (((usage).has_value())){
return ((usage.value()));
}
}

}
}

{
JaktInternal::ArrayIterator<types::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<types::ScopeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ScopeId child = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const scope = TRY((((program)->get_scope(child))));
JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_scope(program,scope,span)));
if (((usage).has_value())){
return ((usage.value()));
}
}

}
}

return (JaktInternal::OptionalNone());
}
}

ErrorOr<String> get_constructor_signature(NonnullRefPtr<types::CheckedProgram> const program,types::FunctionId const function_id) {
{
NonnullRefPtr<types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
types::TypeId const type_id = ((checked_function)->return_type_id);
NonnullRefPtr<types::Module> const mod = ((((program)->modules))[((((type_id).module)).id)]);
{
JaktInternal::ArrayIterator<types::CheckedStruct> _magic = ((((mod)->structures)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedStruct> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedStruct struct_ = (_magic_value.value());
{
if (((((struct_).type_id)).equals(type_id))){
String output = TRY((ide::get_type_signature(program,type_id)));
(output += String("("));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(output += String(", "));
}

types::CheckedVariable const variable = ((program)->get_variable(((field).variable_id)));
if (((variable).is_mutable)){
(output += String("mut "));
}
(output += TRY((String::formatted(String("{}: {}"),((variable).name),TRY((((program)->type_name(((variable).type_id)))))))));
}

}
}

(output += String(")"));
return (output);
}
}

}
}

return (String(""));
}
}

ErrorOr<JaktInternal::Array<String>> find_dot_completions(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<String>, ErrorOr<JaktInternal::Array<String>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::Variable>();types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<String>> __jakt_var_675; {
__jakt_var_675 = TRY((ide::completions_for_type_id(program,type_id))); goto __jakt_label_620;

}
__jakt_label_620:; __jakt_var_675.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Call>();
types::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<String>> __jakt_var_676; {
types::TypeId const result_type_id = ((((program)->get_function(function_id)))->return_type_id);
__jakt_var_676 = TRY((ide::completions_for_type_id(program,result_type_id))); goto __jakt_label_621;

}
__jakt_label_621:; __jakt_var_676.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
)));
}
else {
return ((TRY((Array<String>::create_with({})))));
}

}
}

ErrorOr<utility::Span> find_definition_in_program(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::Variable>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Call>();
types::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_function(function_id)))->name_span));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Typename>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::NameSet>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::EnumVariant>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
else {
return (span);
}

}
}

ErrorOr<String> get_var_signature(NonnullRefPtr<types::CheckedProgram> const program,String const name,types::TypeId const var_type_id,ide::Mutability const mutability,ide::VarType const var_type,ide::VarVisibility const visibility,JaktInternal::Optional<types::TypeId> const struct_type_id) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = var_type;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::VarType::Variable>();
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_677; {
String const mut_string = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = mutability;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Mutability::Mutable>();
return JaktInternal::ExplicitValue(String("mut"));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Mutability::Immutable>();
return JaktInternal::ExplicitValue(String("let"));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
));
String const type_name = TRY((ide::get_type_signature(program,var_type_id)));
__jakt_var_677 = TRY((String::formatted(String("{} {}: {}"),mut_string,name,type_name))); goto __jakt_label_622;

}
__jakt_label_622:; __jakt_var_677.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::VarType::Field>();
{
String record_string = String("");
if (((struct_type_id).has_value())){
(record_string = TRY((ide::get_type_signature(program,(struct_type_id.value())))));
}
String const visibility_string = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = visibility;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::VarVisibility::Public>();
return JaktInternal::ExplicitValue(String("public "));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::VarVisibility::Private>();
return JaktInternal::ExplicitValue(String("private "));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
));
String const type_name = TRY((ide::get_type_signature(program,var_type_id)));
if ((record_string != String(""))){
return (TRY((String::formatted(String("{}\\n\\t{}{}: {}"),record_string,visibility_string,name,type_name))));
}
else {
return (TRY((String::formatted(String("{}{}: {}"),visibility_string,name,type_name))));
}

}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>> enum_variant_fields(NonnullRefPtr<types::CheckedProgram> const program,types::CheckedEnumVariant const checked_enum_variant) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>, ErrorOr<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>>>{
auto&& __jakt_match_variant = checked_enum_variant;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();JaktInternal::Array<types::VarId> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>> __jakt_var_678; {
JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> output = (TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
types::CheckedVariable const variable = ((program)->get_variable(field));
JaktInternal::Optional<String> const var_name = static_cast<JaktInternal::Optional<String>>(((variable).name));
JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId> const o = (Tuple{var_name, ((variable).type_id)});
TRY((((output).push(o))));
}

}
}

__jakt_var_678 = output; goto __jakt_label_623;

}
__jakt_label_623:; __jakt_var_678.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>> __jakt_var_679; {
JaktInternal::Optional<String> const string_none = JaktInternal::OptionalNone();
__jakt_var_679 = (TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({(Tuple{string_none, type_id})})))); goto __jakt_label_624;

}
__jakt_label_624:; __jakt_var_679.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<utility::Span> find_type_definition_in_program(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::Variable>();utility::Span const& span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_680; {
__jakt_var_680 = TRY((ide::find_type_definition_for_type_id(program,type_id,span))); goto __jakt_label_625;

}
__jakt_label_625:; __jakt_var_680.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Call>();
types::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_681; {
__jakt_var_681 = ((((program)->get_function(function_id)))->name_span); goto __jakt_label_626;

}
__jakt_label_626:; __jakt_var_681.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::Typename>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_682; {
__jakt_var_682 = TRY((ide::find_type_definition_for_type_id(program,type_id,span))); goto __jakt_label_627;

}
__jakt_label_627:; __jakt_var_682.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename ide::Usage::NameSet>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<ide::Usage::EnumVariant>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
else {
return (span);
}

}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_expression(NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<types::CheckedExpression> const expr,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const none = JaktInternal::OptionalNone();
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::BinaryOp>();NonnullRefPtr<types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_683; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,lhs,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_683 = TRY((ide::find_span_in_expression(program,rhs,span))); goto __jakt_label_628;

}
__jakt_label_628:; __jakt_var_683.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktArray>();JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_684; {
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedExpression> val = (_magic_value.value());
{
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,val,span)));
if (((found).has_value())){
return (found);
}
}

}
}

if (((repeat).has_value())){
return (TRY((ide::find_span_in_expression(program,(repeat.value()),span))));
}
__jakt_var_684 = none; goto __jakt_label_629;

}
__jakt_label_629:; __jakt_var_684.release_value(); }));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Block>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& call_span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_685; {
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> ___expr__ = (_magic_value.value());
{
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> const jakt_____expr__ = ___expr__;
String const _ = ((jakt_____expr__).get<0>());
NonnullRefPtr<types::CheckedExpression> const expr = ((jakt_____expr__).get<1>());

JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
}

}
}

if ((((((call).function_id)).has_value()) && ((call_span).contains(span)))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Call((((call).function_id).value())) } ));
}
__jakt_var_685 = none; goto __jakt_label_630;

}
__jakt_label_630:; __jakt_var_685.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktDictionary>();JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_686; {
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>> key__value__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>> const jakt__key__value__ = key__value__;
NonnullRefPtr<types::CheckedExpression> const key = ((jakt__key__value__).get<0>());
NonnullRefPtr<types::CheckedExpression> const value = ((jakt__key__value__).get<1>());

JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,key,span)));
if (((found).has_value())){
return (found);
}
(found = TRY((ide::find_span_in_expression(program,value,span))));
if (((found).has_value())){
return (found);
}
}

}
}

__jakt_var_686 = none; goto __jakt_label_631;

}
__jakt_label_631:; __jakt_var_686.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedExpression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_687; {
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
(found = TRY((ide::find_span_in_expression(program,index,span))));
if (((found).has_value())){
return (found);
}
__jakt_var_687 = none; goto __jakt_label_632;

}
__jakt_label_632:; __jakt_var_687.release_value(); }));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedStruct>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
String const& index = __jakt_match_value.index;
utility::Span const& index_span = __jakt_match_value.span;
types::TypeId const& known_type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_688; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
if (((index_span).contains(span))){
types::TypeId const type_id = ((expr)->type());
JaktInternal::Optional<types::TypeId> result_type = JaktInternal::OptionalNone();
if ((!(((known_type_id).equals(types::unknown_type_id()))))){
(result_type = static_cast<JaktInternal::Optional<types::TypeId>>(known_type_id));
}
if (((((program)->get_type(type_id)))->index() == 23 /* Struct */)){
types::StructId const struct_id = ((((program)->get_type(type_id)))->get<types::Type::Struct>()).value;
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((((program)->get_struct(struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const var = ((program)->get_variable(((field).variable_id)));
if ((index != ((var).name))){
continue;
}
return ( ide::Usage { typename ide::Usage::Variable(((var).definition_span),index,result_type.value_or_lazy_evaluated([&] { return ((var).type_id); }), ide::Mutability { typename ide::Mutability::DoesNotApply() } , ide::VarType { typename ide::VarType::Field() } ,JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::VarVisibility, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = ((var).visibility);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedVisibility::Public>();
return JaktInternal::ExplicitValue( ide::VarVisibility { typename ide::VarVisibility::Public() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedVisibility::Private>();
return JaktInternal::ExplicitValue( ide::VarVisibility { typename ide::VarVisibility::Private() } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedVisibility::Restricted>();return JaktInternal::ExplicitValue( ide::VarVisibility { typename ide::VarVisibility::Restricted() } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)),type_id) } );
}

}
}

}
}
__jakt_var_688 = none; goto __jakt_label_633;

}
__jakt_label_633:; __jakt_var_688.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedDictionary>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_689; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_689 = TRY((ide::find_span_in_expression(program,index,span))); goto __jakt_label_634;

}
__jakt_label_634:; __jakt_var_689.release_value(); }));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Match>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Array<types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
utility::Span const& match_span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_690; {
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase match_case = (_magic_value.value());
{
JaktInternal::Optional<ide::Usage> const found = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::EnumVariant>();String const& name = __jakt_match_value.name;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
types::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
size_t const& index = __jakt_match_value.index;
types::ScopeId const& scope_id = __jakt_match_value.scope_id;
types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_691; {
if (((marker_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>(TRY((ide::get_enum_variant_usage_from_type_id_and_name(program,subject_type_id,name)))));
}
__jakt_var_691 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_636;

}
__jakt_label_636:; __jakt_var_691.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::Expression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expression;
types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_692; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_692 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_637;

}
__jakt_label_637:; __jakt_var_692.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::CatchAll>();types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((marker_span).contains(span)));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_693; {
JaktInternal::Set<String> const all_cases = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Set<String>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *((program)->get_type(type_id));
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<String>> __jakt_var_694; {
JaktInternal::Set<String> names = (TRY((Set<String>::create_with_values({}))));
types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
TRY((((names).add(((variant).name())))));
}

}
}

__jakt_var_694 = names; goto __jakt_label_639;

}
__jakt_label_639:; __jakt_var_694.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<String>> __jakt_var_695; {
JaktInternal::Set<String> names = (TRY((Set<String>::create_with_values({}))));
types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
TRY((((names).add(((variant).name())))));
}

}
}

__jakt_var_695 = names; goto __jakt_label_640;

}
__jakt_label_640:; __jakt_var_695.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<String>> __jakt_var_696; {
__jakt_var_696 = (TRY((Set<String>::create_with_values({TRY((String::formatted(String("else ({})"),TRY((((program)->type_name(type_id)))))))})))); goto __jakt_label_641;

}
__jakt_label_641:; __jakt_var_696.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
JaktInternal::Set<String> remaining_cases = all_cases;
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase other_case = (_magic_value.value());
{
if (((other_case).index() == 0 /* EnumVariant */)){
String const name = ((other_case).get<types::CheckedMatchCase::EnumVariant>()).name;
((remaining_cases).remove(name));
}
}

}
}

__jakt_var_693 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((remaining_cases).is_empty()));
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_697; {
JaktInternal::Array<String> cases_array = (TRY((Array<String>::create_with({}))));
TRY((((cases_array).ensure_capacity(((remaining_cases).size())))));
{
JaktInternal::SetIterator<String> _magic = ((remaining_cases).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
TRY((((cases_array).push(name))));
}

}
}

__jakt_var_697 = static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::NameSet(cases_array) } ); goto __jakt_label_642;

}
__jakt_label_642:; __jakt_var_697.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}()))
; goto __jakt_label_638;

}
__jakt_label_638:; __jakt_var_693.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}()))
);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
if (((found).has_value())){
return (found);
}
}

}
}

__jakt_var_690 = TRY((ide::find_span_in_expression(program,expr,span))); goto __jakt_label_635;

}
__jakt_label_635:; __jakt_var_690.release_value(); }));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ForcedUnwrap>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& method_span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> ___expr__ = (_magic_value.value());
{
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> const jakt_____expr__ = ___expr__;
String const _ = ((jakt_____expr__).get<0>());
NonnullRefPtr<types::CheckedExpression> const expr = ((jakt_____expr__).get<1>());

(found = TRY((ide::find_span_in_expression(program,expr,span))));
if (((found).has_value())){
return (found);
}
}

}
}

if ((((((call).function_id)).has_value()) && ((method_span).contains(span)))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Call((((call).function_id).value())) } ));
}
return (none);
}
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Var>();types::CheckedVariable const& var = __jakt_match_value.var;
utility::Span const& var_span = __jakt_match_value.span;
{
JaktInternal::Optional<types::TypeId> const none_type_id = JaktInternal::OptionalNone();
if (((var_span).contains(span))){
ide::Mutability const mutability = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::Mutability,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((var).is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( ide::Mutability { typename ide::Mutability::Mutable() } );
}
else {
return JaktInternal::ExplicitValue( ide::Mutability { typename ide::Mutability::Immutable() } );
}
}()))
;
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Variable(((var).definition_span),((var).name),((var).type_id),mutability, ide::VarType { typename ide::VarType::Variable() } , ide::VarVisibility { typename ide::VarVisibility::DoesNotApply() } ,none_type_id) } ));
}
return (none);
}
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NamespacedVar>();JaktInternal::Array<types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
types::CheckedVariable const& var = __jakt_match_value.var;
utility::Span const& var_span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_698; {
if ((((var_span).contains(span)) && (!(((namespaces).is_empty()))))){
types::CheckedNamespace const last_ns = (((namespaces).last()).value());
if (((((TRY((((program)->get_scope(((last_ns).scope))))))->namespace_name)).has_value())){
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((program)->find_enum_in_scope(((last_ns).scope),((last_ns).name)))));
if (((enum_id).has_value())){
types::CheckedEnum const enum_ = ((program)->get_enum((enum_id.value())));
return (static_cast<JaktInternal::Optional<ide::Usage>>(TRY((ide::get_enum_variant_usage_from_type_id_and_name(program,((enum_).type_id),((var).name))))));
}
}
}
__jakt_var_698 = none; goto __jakt_label_643;

}
__jakt_label_643:; __jakt_var_698.release_value(); }));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::TryBlock>();NonnullRefPtr<types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
String const& error_name = __jakt_match_value.error_name;
types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_699; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_statement(program,stmt,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_699 = TRY((ide::find_span_in_block(program,catch_block,span))); goto __jakt_label_644;

}
__jakt_label_644:; __jakt_var_699.release_value(); }));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Try>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<types::CheckedBlock> const& catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_700; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_700 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((catch_block).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,(catch_block.value()),span))));
}
else {
return JaktInternal::ExplicitValue(none);
}
}()))
; goto __jakt_label_645;

}
__jakt_label_645:; __jakt_var_700.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Range>();JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& to = __jakt_match_value.to;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_701; {
if (((from).has_value())){
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,(from.value()),span)));
if (((found).has_value())){
return (found);
}
}
if (((to).has_value())){
return (TRY((ide::find_span_in_expression(program,(to.value()),span))));
}
__jakt_var_701 = none; goto __jakt_label_646;

}
__jakt_label_646:; __jakt_var_701.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(none);
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_block(NonnullRefPtr<types::CheckedProgram> const program,types::CheckedBlock const block,utility::Span const span) {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedStatement> statement = (_magic_value.value());
{
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_statement(program,statement,span)));
if (((found).has_value())){
return (found);
}
}

}
}

return (JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_program(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> iterator = ((((program)->modules)).iterator());
JaktInternal::Optional<NonnullRefPtr<types::Module>> const dummy = ((iterator).next());
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = iterator;
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const scope = TRY((((program)->get_scope(types::ScopeId(((module)->id),static_cast<size_t>(0ULL))))));
return (TRY((ide::find_span_in_scope(program,scope,span))));
}

}
}

return (JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Array<String>> find_function_completions_in_scope(NonnullRefPtr<types::Scope> const scope,NonnullRefPtr<types::CheckedProgram> const program) {
{
JaktInternal::Array<String> output = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<String> _magic = ((TRY((((((scope)->functions)).keys())))).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String function_name = (_magic_value.value());
{
JaktInternal::Array<types::FunctionId> const overload_set = (((((scope)->functions)).get(function_name)).value());
{
JaktInternal::ArrayIterator<types::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
if (((((((checked_function)->params)).first())).has_value())){
types::CheckedParameter const param = (((((checked_function)->params)).first()).value());
if ((((((param).variable)).name) == String("this"))){
String full_call = ((checked_function)->name);
bool first = true;
(full_call += String("("));
JaktInternal::ArrayIterator<types::CheckedParameter> iter = ((((checked_function)->params)).iterator());
JaktInternal::Optional<types::CheckedParameter> const dummy = ((iter).next());
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = iter;
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(full_call += String(", "));
}
else {
(first = false);
}

(full_call += ((((param).variable)).name));
}

}
}

(full_call += String(")"));
TRY((((output).push(full_call))));
}
}
else {
TRY((((output).push(TRY((String::formatted(String("{}()"),((checked_function)->name))))))));
}

}

}
}

}

}
}

return (output);
}
}

ErrorOr<JaktInternal::Array<ide::JaktSymbol>> find_symbols_in_namespace(parser::ParsedNamespace const namespace_) {
{
JaktInternal::Array<ide::JaktSymbol> symbols = (TRY((Array<ide::JaktSymbol>::create_with({}))));
{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((namespace_).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
TRY((((symbols).push(TRY((ide::record_to_symbol(record)))))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((namespace_).functions)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction function_ = (_magic_value.value());
{
TRY((((symbols).push(TRY((ide::function_to_symbol(function_,String("function"))))))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedNamespace> _magic = ((((namespace_).namespaces)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNamespace> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNamespace sub_namespace = (_magic_value.value());
{
TRY((((symbols).push_values(TRY((ide::find_symbols_in_namespace(sub_namespace)))))));
}

}
}

if ((!(((((namespace_).name_span)).has_value())))){
return (symbols);
}
utility::Span namespace_span = (((namespace_).name_span).value());
{
JaktInternal::ArrayIterator<ide::JaktSymbol> _magic = ((symbols).iterator());
for (;;){
JaktInternal::Optional<ide::JaktSymbol> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ide::JaktSymbol child = (_magic_value.value());
{
(namespace_span = TRY((parser::merge_spans((((namespace_).name_span).value()),((child).range)))));
}

}
}

return ((TRY((Array<ide::JaktSymbol>::create_with({ide::JaktSymbol((((namespace_).name).value()),JaktInternal::OptionalNone(),String("namespace"),namespace_span,(((namespace_).name_span).value()),symbols)})))));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_function(NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<types::CheckedFunction> const checked_function,utility::Span const span) {
{
if (((((checked_function)->return_type_span)).has_value())){
if ((((((checked_function)->return_type_span).value())).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((checked_function)->return_type_id)) } ));
}
}
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if (((((((param).variable)).definition_span)).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((((param).variable)).type_id)) } ));
}
}

}
}

return (TRY((ide::find_span_in_block(program,((checked_function)->block),span))));
}
}

ErrorOr<utility::Span> find_type_definition_for_type_id(NonnullRefPtr<types::CheckedProgram> const program,types::TypeId const type_id,utility::Span const span) {
{
types::StructId const array_struct_id = TRY((((program)->find_struct_in_prelude(String("Array")))));
types::StructId const dictionary_struct_id = TRY((((program)->find_struct_in_prelude(String("Dictionary")))));
types::StructId const optional_struct_id = TRY((((program)->find_struct_in_prelude(String("Optional")))));
types::StructId const range_struct_id = TRY((((program)->find_struct_in_prelude(String("Range")))));
types::StructId const set_struct_id = TRY((((program)->find_struct_in_prelude(String("Set")))));
types::StructId const tuple_struct_id = TRY((((program)->find_struct_in_prelude(String("Tuple")))));
types::StructId const weak_ptr_struct_id = TRY((((program)->find_struct_in_prelude(String("WeakPtr")))));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
auto&& __jakt_match_variant = *((program)->get_type(type_id));
switch(__jakt_match_variant.index()) {
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Never>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::F32>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::F64>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I8>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I16>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I32>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I64>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U8>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U16>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U32>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::U64>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Usize>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CChar>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CInt>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Bool>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Void>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Unknown>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::JaktString>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_trait(id)))->name_span));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_702; {
utility::Span output = span;
if ((((((((struct_id).equals(array_struct_id)) || ((struct_id).equals(optional_struct_id))) || ((struct_id).equals(range_struct_id))) || ((struct_id).equals(set_struct_id))) || ((struct_id).equals(tuple_struct_id))) || ((struct_id).equals(weak_ptr_struct_id)))){
(output = TRY((ide::find_type_definition_for_type_id(program,((args)[static_cast<i64>(0LL)]),span))));
}
else if (((struct_id).equals(dictionary_struct_id))){
(output = TRY((ide::find_type_definition_for_type_id(program,((args)[static_cast<i64>(1LL)]),span))));
}
else {
(output = ((((program)->get_struct(struct_id))).name_span));
}

__jakt_var_702 = output; goto __jakt_label_647;

}
__jakt_label_647:; __jakt_var_702.release_value(); }));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_struct(struct_id))).name_span));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_enum(id))).name_span));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_trait(id)))->name_span));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_enum(id))).name_span));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();types::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_struct(id))).name_span));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> get_enum_variant_signature(NonnullRefPtr<types::CheckedProgram> const program,String const name,types::TypeId const type_id,JaktInternal::Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> const variants,JaktInternal::Optional<types::NumberConstant> const number_constant) {
{
String output = TRY((ide::get_type_signature(program,type_id)));
(output += String("::"));
(output += name);
if ((!(((variants).is_empty())))){
(output += String("("));
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId> variant_name__variant_type_id__ = (_magic_value.value());
{
JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId> const jakt__variant_name__variant_type_id__ = variant_name__variant_type_id__;
JaktInternal::Optional<String> const variant_name = ((jakt__variant_name__variant_type_id__).get<0>());
types::TypeId const variant_type_id = ((jakt__variant_name__variant_type_id__).get<1>());

if (first){
(first = false);
}
else {
(output += String(", "));
}

if (((variant_name).has_value())){
(output += (variant_name.value()));
(output += String(": "));
}
(output += TRY((((program)->type_name(variant_type_id)))));
}

}
}

(output += String(")"));
}
if (((number_constant).has_value())){
(output += String(" = "));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = (number_constant.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Signed>();
i64 const& value = __jakt_match_value.value;
{
(output += TRY((String::formatted(String("{}"),value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Unsigned>();
u64 const& value = __jakt_match_value.value;
{
(output += TRY((String::formatted(String("{}"),value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Floating>();
f64 const& value = __jakt_match_value.value;
{
(output += TRY((String::formatted(String("{}"),value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}
return (output);
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_enum(NonnullRefPtr<types::CheckedProgram> const program,types::CheckedEnum const checked_enum,utility::Span const span) {
{
NonnullRefPtr<types::Scope> const scope = TRY((((program)->get_scope(((checked_enum).scope_id)))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((checked_enum).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& name = __jakt_match_value.name;
JaktInternal::Array<types::VarId> const& fields = __jakt_match_value.fields;
utility::Span const& variant_span = __jakt_match_value.span;
{
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
types::CheckedVariable const var = ((program)->get_variable(field));
if (((((var).definition_span)).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((var).type_id)) } ));
}
}

}
}

if (((variant_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::EnumVariant(span,name,((checked_enum).type_id),(TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({})))),JaktInternal::OptionalNone()) } ));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& name = __jakt_match_value.name;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),TRY((ide::enum_variant_fields(program,variant))),JaktInternal::OptionalNone()) } ));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& name = __jakt_match_value.name;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),(TRY((Array<JaktInternal::Tuple<JaktInternal::Optional<String>,types::TypeId>>::create_with({})))),JaktInternal::OptionalNone()) } ));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();String const& name = __jakt_match_value.name;
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),TRY((ide::enum_variant_fields(program,variant))),((expr)->to_number_constant(program))) } ));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}

}
}

JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_scope(program,scope,span)));
return (usage);
}
}

ErrorOr<ide::JaktSymbol> function_to_symbol(parser::ParsedFunction const function_,String const kind) {
{
utility::Span function_span = ((function_).name_span);
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedStatement>> _magic = ((((((function_).block)).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedStatement> stmt = (_magic_value.value());
{
(function_span = TRY((parser::merge_spans(function_span,((stmt)->span())))));
}

}
}

return (ide::JaktSymbol(((function_).name),JaktInternal::OptionalNone(),kind,function_span,((function_).name_span),(TRY((Array<ide::JaktSymbol>::create_with({}))))));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_statement(NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<types::CheckedStatement> const statement,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const none = JaktInternal::OptionalNone();
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Block>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Defer>();NonnullRefPtr<types::CheckedStatement> const& statement = __jakt_match_value.statement;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_statement(program,statement,span))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Expression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::If>();NonnullRefPtr<types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_703; {
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,condition,span)));
if (((found).has_value())){
return (found);
}
(found = TRY((ide::find_span_in_block(program,then_block,span))));
if (((found).has_value())){
return (found);
}
if (((else_statement).has_value())){
return (TRY((ide::find_span_in_statement(program,(else_statement.value()),span))));
}
__jakt_var_703 = none; goto __jakt_label_648;

}
__jakt_label_648:; __jakt_var_703.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::InlineCpp>();return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_704; {
JaktInternal::Optional<ide::Usage> const output = JaktInternal::OptionalNone();
__jakt_var_704 = output; goto __jakt_label_649;

}
__jakt_label_649:; __jakt_var_704.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Loop>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Return>();JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((val).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,(val.value()),span))));
}
else {
return JaktInternal::ExplicitValue(none);
}
}()))
);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Throw>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::VarDecl>();types::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<types::CheckedExpression> const& init = __jakt_match_value.init;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_705; {
types::CheckedVariable const checked_var = ((program)->get_variable(var_id));
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,init,span)));
if (((found).has_value())){
return (found);
}
if (((((checked_var).type_span)).has_value())){
utility::Span const type_span = (((checked_var).type_span).value());
if (((type_span).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((checked_var).type_id)) } ));
}
}
if (((((checked_var).definition_span)).contains(span))){
ide::Mutability const mutability = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::Mutability,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((checked_var).is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( ide::Mutability { typename ide::Mutability::Mutable() } );
}
else {
return JaktInternal::ExplicitValue( ide::Mutability { typename ide::Mutability::Immutable() } );
}
}()))
;
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Variable(((checked_var).definition_span),((checked_var).name),((checked_var).type_id),mutability, ide::VarType { typename ide::VarType::Variable() } , ide::VarVisibility { typename ide::VarVisibility::DoesNotApply() } ,JaktInternal::OptionalNone()) } ));
}
__jakt_var_705 = none; goto __jakt_label_650;

}
__jakt_label_650:; __jakt_var_705.release_value(); }));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::While>();NonnullRefPtr<types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_706; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,condition,span)));
if (((found).has_value())){
return (found);
}
__jakt_var_706 = TRY((ide::find_span_in_block(program,block,span))); goto __jakt_label_651;

}
__jakt_label_651:; __jakt_var_706.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::DestructuringAssignment>();JaktInternal::Array<NonnullRefPtr<types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_707; {
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedStatement>> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedStatement> var = (_magic_value.value());
{
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_statement(program,var,span)));
if (((found).has_value())){
return (found);
}
}

}
}

__jakt_var_707 = TRY((ide::find_span_in_statement(program,var_decl,span))); goto __jakt_label_652;

}
__jakt_label_652:; __jakt_var_707.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Yield>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Break>();
return JaktInternal::ExplicitValue(none);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Continue>();
return JaktInternal::ExplicitValue(none);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Garbage>();
return JaktInternal::ExplicitValue(none);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_struct(NonnullRefPtr<types::CheckedProgram> const program,types::CheckedStruct const checked_struct,utility::Span const span) {
{
NonnullRefPtr<types::Scope> const scope = TRY((((program)->get_scope(((checked_struct).scope_id)))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((checked_struct).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const variable = ((program)->get_variable(((field).variable_id)));
if (((((variable).definition_span)).contains(span))){
return (static_cast<JaktInternal::Optional<ide::Usage>>( ide::Usage { typename ide::Usage::Typename(((variable).type_id)) } ));
}
}

}
}

JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_scope(program,scope,span)));
return (usage);
}
}

ErrorOr<String> get_function_signature(NonnullRefPtr<types::CheckedProgram> const program,types::FunctionId const function_id) {
{
NonnullRefPtr<types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = ((checked_function)->type);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::FunctionType::ImplicitEnumConstructor>();
{
types::TypeId const type_id = ((checked_function)->return_type_id);
String const name = ((checked_function)->name);
return (TRY((ide::get_enum_variant_signature_from_type_id_and_name(program,type_id,name))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::FunctionType::ImplicitConstructor>();
{
return (TRY((ide::get_constructor_signature(program,function_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
String generic_parameters = String("");
bool is_first_param = true;
if ((!(((((((checked_function)->generics))->params)).is_empty())))){
(generic_parameters += String("<"));
{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((((((checked_function)->generics))->params)).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter parameter = (_magic_value.value());
{
String const generic_type = TRY((((program)->type_name(((parameter).type_id())))));
String const separator = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (is_first_param);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(""));
}
else {
return JaktInternal::ExplicitValue(String(", "));
}
}()))
;
(generic_parameters += TRY((String::formatted(String("{}{}"),separator,generic_type))));
(is_first_param = false);
}

}
}

(generic_parameters += String(">"));
}
String parameters = String("");
(is_first_param = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
String const anon_value = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((param).requires_label));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(""));
}
else {
return JaktInternal::ExplicitValue(String("anon "));
}
}()))
;
String const is_mutable = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((((param).variable)).is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("mut "));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
String variable_type = TRY((((program)->type_name(((((param).variable)).type_id)))));
if ((variable_type != String("void"))){
(variable_type = (String(": ") + variable_type));
}
else {
(variable_type = String(""));
}

String const separator = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (is_first_param);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(""));
}
else {
return JaktInternal::ExplicitValue(String(", "));
}
}()))
;
(parameters += TRY((String::formatted(String("{}{}{}{}{}"),separator,anon_value,is_mutable,((((param).variable)).name),variable_type))));
(is_first_param = false);
}

}
}

String const throws_str = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((checked_function)->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(" throws"));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
String returns = TRY((((program)->type_name(((checked_function)->return_type_id)))));
if ((returns != String("void"))){
(returns = (String(" -> ") + returns));
}
else {
(returns = String(""));
}

return (TRY((String::formatted(String("function {}{}({}){}{}"),((checked_function)->name),generic_parameters,parameters,throws_str,returns))));
}
}

ErrorOr<String> ide::JaktSymbol::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("JaktSymbol("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("name: "));TRY(builder.appendff("\"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("detail: "));TRY(builder.appendff("{}, ", detail));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("kind: "));TRY(builder.appendff("\"{}\", ", kind));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("range: "));TRY(builder.appendff("{}, ", range));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("selection_range: "));TRY(builder.appendff("{}, ", selection_range));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("children: "));TRY(builder.appendff("{}", children));
}
TRY(builder.append(")"));return builder.to_string(); }
ide::JaktSymbol::JaktSymbol(String a_name, JaktInternal::Optional<String> a_detail, String a_kind, utility::Span a_range, utility::Span a_selection_range, JaktInternal::Array<ide::JaktSymbol> a_children) :name(a_name), detail(a_detail), kind(a_kind), range(a_range), selection_range(a_selection_range), children(a_children){}

ErrorOr<String> ide::JaktSymbol::to_json() const {
{
StringBuilder json_builder = TRY((StringBuilder::create()));
TRY((((json_builder).append_string(String("{")))));
TRY((((json_builder).append_string(TRY((String::formatted(String("\"name\": \"{}\","),((*this).name))))))));
if (((((*this).detail)).has_value())){
TRY((((json_builder).append_string(TRY((String::formatted(String("\"detail\": \"{}\","),((*this).detail))))))));
}
TRY((((json_builder).append_string(TRY((String::formatted(String("\"kind\": \"{}\","),((*this).kind))))))));
TRY((((json_builder).append_string(TRY((String::formatted(String("\"range\": {{\"start\": {}, \"end\": {}}},"),((((*this).range)).start),((((*this).range)).end))))))));
TRY((((json_builder).append_string(TRY((String::formatted(String("\"selection_range\": {{\"start\": {}, \"end\": {}}},"),((((*this).selection_range)).start),((((*this).selection_range)).end))))))));
JaktInternal::Array<String> child_symbols = (TRY((Array<String>::create_with({}))));
TRY((((child_symbols).ensure_capacity(((((*this).children)).size())))));
{
JaktInternal::ArrayIterator<ide::JaktSymbol> _magic = ((((*this).children)).iterator());
for (;;){
JaktInternal::Optional<ide::JaktSymbol> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ide::JaktSymbol child = (_magic_value.value());
{
TRY((((child_symbols).push(TRY((((child).to_json())))))));
}

}
}

TRY((((json_builder).append_string(TRY((String::formatted(String("\"children\": [{}]"),utility::join(child_symbols,String(",")))))))));
TRY((((json_builder).append_string(String("}")))));
return (TRY((((json_builder).to_string()))));
}
}

ErrorOr<String> ide::Mutability::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* DoesNotApply */: {
[[maybe_unused]] auto const& that = this->template get<Mutability::DoesNotApply>();
TRY(builder.append("Mutability::DoesNotApply"));
break;}
case 1 /* Immutable */: {
[[maybe_unused]] auto const& that = this->template get<Mutability::Immutable>();
TRY(builder.append("Mutability::Immutable"));
break;}
case 2 /* Mutable */: {
[[maybe_unused]] auto const& that = this->template get<Mutability::Mutable>();
TRY(builder.append("Mutability::Mutable"));
break;}
}
return builder.to_string();
}
ErrorOr<String> ide::Usage::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Variable */: {
[[maybe_unused]] auto const& that = this->template get<Usage::Variable>();
TRY(builder.append("Usage::Variable"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\"", that.name));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("mutability: {}", that.mutability));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("var_type: {}", that.var_type));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("visibility: {}", that.visibility));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("struct_type_id: {}", that.struct_type_id));
}
TRY(builder.append(")"));
break;}
case 1 /* Call */: {
[[maybe_unused]] auto const& that = this->template get<Usage::Call>();
TRY(builder.append("Usage::Call"));
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* Typename */: {
[[maybe_unused]] auto const& that = this->template get<Usage::Typename>();
TRY(builder.append("Usage::Typename"));
TRY(builder.appendff("({})", that.value));
break;}
case 3 /* NameSet */: {
[[maybe_unused]] auto const& that = this->template get<Usage::NameSet>();
TRY(builder.append("Usage::NameSet"));
TRY(builder.appendff("({})", that.value));
break;}
case 4 /* EnumVariant */: {
[[maybe_unused]] auto const& that = this->template get<Usage::EnumVariant>();
TRY(builder.append("Usage::EnumVariant"));
TRY(builder.append("("));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\"", that.name));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("variants: {}", that.variants));
TRY(builder.append(", "));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("number_constant: {}", that.number_constant));
}
TRY(builder.append(")"));
break;}
}
return builder.to_string();
}
ErrorOr<String> ide::VarType::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Variable */: {
[[maybe_unused]] auto const& that = this->template get<VarType::Variable>();
TRY(builder.append("VarType::Variable"));
break;}
case 1 /* Field */: {
[[maybe_unused]] auto const& that = this->template get<VarType::Field>();
TRY(builder.append("VarType::Field"));
break;}
}
return builder.to_string();
}
ErrorOr<String> ide::VarVisibility::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* DoesNotApply */: {
[[maybe_unused]] auto const& that = this->template get<VarVisibility::DoesNotApply>();
TRY(builder.append("VarVisibility::DoesNotApply"));
break;}
case 1 /* Public */: {
[[maybe_unused]] auto const& that = this->template get<VarVisibility::Public>();
TRY(builder.append("VarVisibility::Public"));
break;}
case 2 /* Private */: {
[[maybe_unused]] auto const& that = this->template get<VarVisibility::Private>();
TRY(builder.append("VarVisibility::Private"));
break;}
case 3 /* Restricted */: {
[[maybe_unused]] auto const& that = this->template get<VarVisibility::Restricted>();
TRY(builder.append("VarVisibility::Restricted"));
break;}
}
return builder.to_string();
}
}
} // namespace Jakt
