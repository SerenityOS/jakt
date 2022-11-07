#include "typechecker.h"
namespace Jakt {
namespace typechecker {
ErrorOr<String> typechecker::AlreadyImplementedFor::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("AlreadyImplementedFor("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("trait_name: "));TRY(builder.appendff("\"{}\", ", trait_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("encounter_span: "));TRY(builder.appendff("{}", encounter_span));
}
TRY(builder.append(")"));return builder.to_string(); }
typechecker::AlreadyImplementedFor::AlreadyImplementedFor(String a_trait_name, utility::Span a_encounter_span) :trait_name(a_trait_name), encounter_span(a_encounter_span){}

ErrorOr<String> typechecker::Typechecker::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Typechecker("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("compiler: "));TRY(builder.appendff("{}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("program: "));TRY(builder.appendff("{}, ", *program));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_module_id: "));TRY(builder.appendff("{}, ", current_module_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_struct_type_id: "));TRY(builder.appendff("{}, ", current_struct_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_function_id: "));TRY(builder.appendff("{}, ", current_function_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("inside_defer: "));TRY(builder.appendff("{}, ", inside_defer));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("checkidx: "));TRY(builder.appendff("{}, ", checkidx));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("ignore_errors: "));TRY(builder.appendff("{}, ", ignore_errors));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_type_hints: "));TRY(builder.appendff("{}, ", dump_type_hints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("dump_try_hints: "));TRY(builder.appendff("{}, ", dump_try_hints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("lambda_count: "));TRY(builder.appendff("{}, ", lambda_count));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("generic_inferences: "));TRY(builder.appendff("{}", generic_inferences));
}
TRY(builder.append(")"));return builder.to_string(); }
bool typechecker::Typechecker::is_floating(types::TypeId const type_id) const {
{
return (((((*this).program))->is_floating(type_id)));
}
}

ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>>> typechecker::Typechecker::typecheck_match_body(parser::ParsedMatchBody const body,types::ScopeId const scope_id,types::SafetyMode const safety_mode,types::GenericInferences& generic_inferences,JaktInternal::Optional<types::TypeId> const final_result_type,utility::Span const span) {
{
JaktInternal::Optional<types::TypeId> result_type = final_result_type;
types::CheckedMatchBody const checked_match_body = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedMatchBody, ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedMatchBody::Block>();
parser::ParsedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedMatchBody> __jakt_var_294; {
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(block,scope_id,safety_mode,final_result_type))));
if ((((((checked_block).control_flow)).may_return()) || ((((checked_block).yielded_type)).has_value()))){
types::TypeId const block_type_id = ((checked_block).yielded_type).value_or_lazy_evaluated([&] { return types::void_type_id(); });
utility::Span const yield_span = ((block).find_yield_span()).value_or_lazy_evaluated([&] { return span; });
if (((result_type).has_value())){
TRY((((*this).check_types_for_compat((result_type.value()),block_type_id,generic_inferences,yield_span))));
}
else {
(result_type = block_type_id);
}

}
JaktInternal::Optional<types::CheckedMatchBody> final_body = JaktInternal::OptionalNone();
if ((((((checked_block).yielded_type)).has_value()) && (!(((((checked_block).control_flow)).never_returns()))))){
(final_body =  types::CheckedMatchBody { typename types::CheckedMatchBody::Expression(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Block>(checked_block,span,(((checked_block).yielded_type).value()))))) } );
}
else {
(final_body =  types::CheckedMatchBody { typename types::CheckedMatchBody::Block(checked_block) } );
}

__jakt_var_294 = (final_body.value()); goto __jakt_label_285;

}
__jakt_label_285:; __jakt_var_294.release_value(); }));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedMatchBody::Expression>();
NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedMatchBody> __jakt_var_295; {
NonnullRefPtr<types::CheckedExpression> const checked_expression = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,result_type))));
if (((result_type).has_value())){
TRY((((*this).check_types_for_compat((result_type.value()),((checked_expression)->type()),generic_inferences,span))));
}
else {
(result_type = ((checked_expression)->type()));
}

__jakt_var_295 =  types::CheckedMatchBody { typename types::CheckedMatchBody::Expression(checked_expression) } ; goto __jakt_label_286;

}
__jakt_label_286:; __jakt_var_295.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
return ((Tuple{checked_match_body, result_type}));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_predecl(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
size_t const module_struct_len = ((((((*this).current_module()))->structures)).size());
size_t const module_enum_len = ((((((*this).current_module()))->enums)).size());
size_t struct_index = static_cast<size_t>(0ULL);
size_t enum_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord parsed_record = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();{
TRY((((*this).typecheck_struct_predecl_initial(parsed_record,((struct_index++)),module_struct_len,scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();{
TRY((((*this).typecheck_struct_predecl_initial(parsed_record,((struct_index++)),module_struct_len,scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
TRY((((*this).typecheck_enum_predecl_initial(parsed_record,((enum_index++)),module_enum_len,scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
TRY((((*this).typecheck_enum_predecl_initial(parsed_record,((enum_index++)),module_enum_len,scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::RecordType::Garbage>();
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedNamespace> _magic = ((((parsed_namespace).namespaces)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNamespace> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNamespace namespace_ = (_magic_value.value());
{
String debug_name = String("namespace(");
if (((((namespace_).name)).has_value())){
(debug_name += (((namespace_).name).value()));
}
else {
(debug_name += String("unnamed-namespace"));
}

(debug_name += String(")"));
types::ScopeId const namespace_scope_id = TRY((((*this).create_scope(scope_id,false,debug_name))));
NonnullRefPtr<types::Scope> child_scope = TRY((((*this).get_scope(namespace_scope_id))));
(((child_scope)->namespace_name) = ((namespace_).name));
(((child_scope)->import_path_if_extern) = ((namespace_).import_path_if_extern));
(((child_scope)->before_extern_include) = ((namespace_).generating_import_extern_before_include));
(((child_scope)->after_extern_include) = ((namespace_).generating_import_extern_after_include));
NonnullRefPtr<types::Scope> parent_scope = TRY((((*this).get_scope(scope_id))));
TRY((((((parent_scope)->children)).push(namespace_scope_id))));
TRY((((*this).typecheck_namespace_predecl(namespace_,namespace_scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedTrait> _magic = ((((parsed_namespace).traits)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedTrait> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedTrait parsed_trait = (_magic_value.value());
{
TRY((((*this).typecheck_trait_predecl(parsed_trait,scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedTrait> _magic = ((((parsed_namespace).traits)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedTrait> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedTrait parsed_trait = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((parsed_trait).name)))));
if (((trait_id).has_value())){
TRY((((*this).typecheck_trait(parsed_trait,(trait_id.value()),scope_id))));
}
else {
TRY((((((*this).compiler))->panic(String("can't find trait that has been previous added")))));
}

}

}
}

(struct_index = static_cast<size_t>(0ULL));
(enum_index = static_cast<size_t>(0ULL));
{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord parsed_record = (_magic_value.value());
{
types::StructId const struct_id = types::StructId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(struct_index,module_struct_len)));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();{
TRY((((*this).typecheck_struct_predecl(parsed_record,struct_id,scope_id))));
((struct_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();{
TRY((((*this).typecheck_struct_predecl(parsed_record,struct_id,scope_id))));
((struct_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
types::EnumId const enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
TRY((((*this).typecheck_enum_predecl(parsed_record,enum_id,scope_id))));
((enum_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
types::EnumId const enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
TRY((((*this).typecheck_enum_predecl(parsed_record,enum_id,scope_id))));
((enum_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::RecordType::Garbage>();
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedExternalTraitImplementation> _magic = ((((parsed_namespace).external_trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedExternalTraitImplementation> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedExternalTraitImplementation implementation = (_magic_value.value());
{
types::TypeId const for_type = TRY((((*this).typecheck_typename(((implementation).for_type),scope_id,JaktInternal::OptionalNone()))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *((*this).get_type(for_type));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct struct_ = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((implementation).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return String(""); }) == String("this"))){
(this_arg_type_id = for_type);
}
TRY((((*this).typecheck_function_predecl(((method).parsed_function),((struct_).scope_id),this_arg_type_id,JaktInternal::OptionalNone()))));
}

}
}

TRY((((*this).fill_trait_implementation_list(((implementation).traits),((((struct_).trait_implementations))),((struct_).scope_id),scope_id))));
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = ((((implementation).traits)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((trait_name).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait((trait_id.value())));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
String const name = ((jakt__name__function_id__).get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).get<1>());

if (((TRY((((*this).find_function_in_scope(((struct_).scope_id),name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function_ = ((*this).get_function(function_id));
if (((((((function_)->block)).statements)).is_empty())){
continue;
}
TRY((((*this).add_function_to_scope(((struct_).scope_id),name,function_id,((trait_name).name_span)))));
}

}
}

}
else {
continue;
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
{
types::CheckedStruct struct_ = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((implementation).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return String(""); }) == String("this"))){
(this_arg_type_id = for_type);
}
TRY((((*this).typecheck_function_predecl(((method).parsed_function),((struct_).scope_id),this_arg_type_id,JaktInternal::OptionalNone()))));
}

}
}

TRY((((*this).fill_trait_implementation_list(((implementation).traits),((((struct_).trait_implementations))),((struct_).scope_id),scope_id))));
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = ((((implementation).traits)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((trait_name).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait((trait_id.value())));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
String const name = ((jakt__name__function_id__).get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).get<1>());

if (((TRY((((*this).find_function_in_scope(((struct_).scope_id),name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function_ = ((*this).get_function(function_id));
if (((((((function_)->block)).statements)).is_empty())){
continue;
}
TRY((((*this).add_function_to_scope(((struct_).scope_id),name,function_id,((trait_name).name_span)))));
}

}
}

}
else {
continue;
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((implementation).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return String(""); }) == String("this"))){
(this_arg_type_id = for_type);
}
TRY((((*this).typecheck_function_predecl(((method).parsed_function),((enum_).scope_id),this_arg_type_id,JaktInternal::OptionalNone()))));
}

}
}

TRY((((*this).fill_trait_implementation_list(((implementation).traits),((((enum_).trait_implementations))),((enum_).scope_id),scope_id))));
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = ((((implementation).traits)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((trait_name).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait((trait_id.value())));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
String const name = ((jakt__name__function_id__).get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).get<1>());

if (((TRY((((*this).find_function_in_scope(((enum_).scope_id),name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function_ = ((*this).get_function(function_id));
if (((((((function_)->block)).statements)).is_empty())){
continue;
}
TRY((((*this).add_function_to_scope(((enum_).scope_id),name,function_id,((trait_name).name_span)))));
}

}
}

}
else {
continue;
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
{
types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((implementation).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return String(""); }) == String("this"))){
(this_arg_type_id = for_type);
}
TRY((((*this).typecheck_function_predecl(((method).parsed_function),((enum_).scope_id),this_arg_type_id,JaktInternal::OptionalNone()))));
}

}
}

TRY((((*this).fill_trait_implementation_list(((implementation).traits),((((enum_).trait_implementations))),((enum_).scope_id),scope_id))));
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = ((((implementation).traits)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((trait_name).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait((trait_id.value())));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
String const name = ((jakt__name__function_id__).get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).get<1>());

if (((TRY((((*this).find_function_in_scope(((enum_).scope_id),name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function_ = ((*this).get_function(function_id));
if (((((((function_)->block)).statements)).is_empty())){
continue;
}
TRY((((*this).add_function_to_scope(((enum_).scope_id),name,function_id,((trait_name).name_span)))));
}

}
}

}
else {
continue;
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((String::formatted(String("Cannot implement traits for type '{}'"),TRY((((*this).type_name(for_type))))))),((((implementation).for_type))->span())))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_set(JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> const values,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
if ((!(((TRY((((*this).get_scope(scope_id)))))->can_throw)))){
TRY((((*this).error(String("Set initialization needs to be in a try statement or a function marked as throws"),span))));
}
types::TypeId inner_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> inner_type_span = JaktInternal::OptionalNone();
JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> output = (TRY((Array<NonnullRefPtr<types::CheckedExpression>>::create_with({}))));
types::StructId const set_struct_id = TRY((((*this).find_struct_in_prelude(String("Set")))));
JaktInternal::Optional<types::TypeId> inner_hint = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedExpression>> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedExpression> value = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,inner_hint))));
types::TypeId const current_value_type_id = ((checked_value)->type());
if (((inner_type_id).equals(types::unknown_type_id()))){
if ((((current_value_type_id).equals(types::void_type_id())) || ((current_value_type_id).equals(types::unknown_type_id())))){
TRY((((*this).error(String("Cannot create a set with values of type void"),((value)->span())))));
}
(inner_type_id = current_value_type_id);
(inner_type_span = ((value)->span()));
}
else if ((!(((inner_type_id).equals(current_value_type_id))))){
String const set_type_name = TRY((((*this).type_name(inner_type_id))));
TRY((((*this).error_with_hint(TRY((String::formatted(String("Type '{}' does not match type '{}' of previous values in set"),TRY((((*this).type_name(current_value_type_id)))),set_type_name))),((value)->span()),TRY((String::formatted(String("Set was inferred to store type '{}' here"),set_type_name))),(inner_type_span.value())))));
}
TRY((((output).push(checked_value))));
}

}
}

if ((((inner_type_id).equals(types::unknown_type_id())) && (((type_hint).has_value()) && (!((((type_hint.value())).equals(types::unknown_type_id()))))))){
if (((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
if (((id).equals(set_struct_id))){
(inner_type_id = ((args)[static_cast<i64>(0LL)]));
}
else {
utility::panic(String("expected Set struct"));
}

}
else {
utility::panic(String("expected Set struct"));
}

}
if (((inner_type_id).equals(types::unknown_type_id()))){
TRY((((*this).error(String("Cannot infer generic type for Set<T>"),span))));
}
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(set_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id})))))))))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::JaktSet>(output,span,type_id,inner_type_id))));
}
}

bool typechecker::Typechecker::is_struct(types::TypeId const type_id) const {
{
if (((((*this).get_type(type_id)))->index() == 23 /* Struct */)){
types::StructId const struct_id = (((*this).get_type(type_id))->get<types::Type::Struct>()).value;
return (((((((*this).get_struct(struct_id))).record_type)).index() == 0 /* Struct */));
}
else {
return (false);
}

}
}

bool typechecker::Typechecker::is_integer(types::TypeId const type_id) const {
{
return (((((*this).program))->is_integer(type_id)));
}
}

ErrorOr<void> typechecker::Typechecker::dump_try_hint(utility::Span const span) const {
{
outln(String("{{\"type\":\"try\",\"file_id\":{},\"position\":{}}}"),((((span).file_id)).id),((span).start));
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_call(parser::ParsedCall const call,types::ScopeId const caller_scope_id,utility::Span const span,JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const this_expr,JaktInternal::Optional<types::StructOrEnumId> const parent_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> type_hint,bool const must_be_enum_constructor) {
{
JaktInternal::Array<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> args = (TRY((Array<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>>::create_with({}))));
types::TypeId return_type = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
JaktInternal::Array<types::TypeId> generic_arguments = (TRY((Array<types::TypeId>::create_with({}))));
bool callee_throws = false;
JaktInternal::Array<types::ResolvedNamespace> resolved_namespaces = (TRY((Array<types::ResolvedNamespace>::create_with({}))));
JaktInternal::Optional<types::FunctionId> resolved_function_id = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> maybe_this_type_id = JaktInternal::OptionalNone();
JaktInternal::Optional<types::FunctionId> generic_checked_function_to_instantiate = JaktInternal::OptionalNone();
JaktInternal::Dictionary<String,String> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_296([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
{
JaktInternal::ArrayIterator<String> _magic = ((((call).namespace_)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
TRY((((resolved_namespaces).push(types::ResolvedNamespace(name,JaktInternal::OptionalNone())))));
}

}
}

types::ScopeId const callee_scope_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = (((parent_id).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = (parent_id.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructOrEnumId::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_297; {
types::CheckedStruct struct_ = ((*this).get_struct(id));
types::ScopeId scope_id = ((struct_).scope_id);
while ((!(((resolved_function_id).has_value())))){
(resolved_function_id = TRY((((*this).resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor,true)))));
if (((resolved_function_id).has_value())){
break;
}
if (((((struct_).super_struct_id)).has_value())){
types::StructId const parent_struct_id = (((struct_).super_struct_id).value());
(struct_ = ((*this).get_struct(parent_struct_id)));
(scope_id = ((struct_).scope_id));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Could not find ‘{}’"),((call).name)))),span))));
break;
}

}
__jakt_var_297 = scope_id; goto __jakt_label_287;

}
__jakt_label_287:; __jakt_var_297.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructOrEnumId::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_298; {
types::ScopeId const scope_id = ((((*this).get_enum(id))).scope_id);
(resolved_function_id = TRY((((*this).resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor,false)))));
__jakt_var_298 = scope_id; goto __jakt_label_288;

}
__jakt_label_288:; __jakt_var_298.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
else {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_299; {
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == String("print")) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("println")) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("eprintln")) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("eprint")) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("format")) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
(resolved_function_id = TRY((((*this).resolve_call(call,resolved_namespaces,span,caller_scope_id,must_be_enum_constructor,false)))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
__jakt_var_299 = caller_scope_id; goto __jakt_label_289;

}
__jakt_label_289:; __jakt_var_299.release_value(); }));
}
}()))
;
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == String("print")) {
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> arg = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == String("format"))){
(return_type = types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("println")) {
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> arg = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == String("format"))){
(return_type = types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("eprintln")) {
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> arg = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == String("format"))){
(return_type = types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("eprint")) {
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> arg = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == String("format"))){
(return_type = types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("format")) {
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> arg = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == String("format"))){
(return_type = types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
if ((!(((resolved_function_id).has_value())))){
JaktInternal::Array<types::TypeId> checked_type_args = (TRY((Array<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedType>> _magic = ((((call).type_args)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedType> type_arg = (_magic_value.value());
{
TRY((((checked_type_args).push(TRY((((*this).typecheck_typename(type_arg,caller_scope_id,JaktInternal::OptionalNone()))))))));
}

}
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> arg = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Call>(types::CheckedCall(resolved_namespaces,((call).name),args,checked_type_args,resolved_function_id,return_type,callee_throws),span,return_type))));
}
types::FunctionId const function_id = (resolved_function_id.value());
NonnullRefPtr<types::CheckedFunction> const callee = ((*this).get_function(function_id));
if (((callee)->is_instantiated)){
TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
}
(callee_throws = ((callee)->can_throw));
(return_type = ((callee)->return_type_id));
types::ScopeId const scope_containing_callee = (((TRY((((*this).get_scope(((callee)->function_scope_id))))))->parent).value());
if (((((callee)->type)).index() == 1 /* ImplicitConstructor */)){
types::CheckedStruct const struct_ = ((*this).get_struct((((callee)->struct_id).value())));
TRY((((*this).check_implicit_constructor_argument_access(caller_scope_id,call,struct_))));
}
else {
TRY((((*this).check_method_access(caller_scope_id,scope_containing_callee,callee,span))));
}

size_t type_arg_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedType>> _magic = ((((call).type_args)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedType> parsed_type = (_magic_value.value());
{
types::TypeId const checked_type = TRY((((*this).typecheck_typename(parsed_type,caller_scope_id,JaktInternal::OptionalNone()))));
if ((((((((callee)->generics))->params)).size()) <= type_arg_index)){
TRY((((*this).error(String("Trying to access generic parameter out of bounds"),((parsed_type)->span())))));
continue;
}
types::TypeId const typevar_type_id = ((((((((callee)->generics))->params))[type_arg_index])).type_id());
if ((!(((typevar_type_id).equals(checked_type))))){
TRY((((((*this).generic_inferences)).set(TRY((((typevar_type_id).to_string()))),TRY((((checked_type).to_string())))))));
}
({auto& _jakt_ref = type_arg_index;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}

}
}

size_t arg_offset = static_cast<size_t>(0ULL);
if (((this_expr).has_value())){
types::TypeId const type_id = (((this_expr.value()))->type());
(maybe_this_type_id = type_id);
NonnullRefPtr<types::Type> const param_type = ((*this).get_type(type_id));
if (((param_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = (param_type->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (param_type->get<types::Type::GenericInstance>()).args;
types::CheckedStruct const structure = ((*this).get_struct(id));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((structure).generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((((structure).generic_parameters))[i])).type_id)).equals(((args)[i])))){
continue;
}
TRY((((((*this).generic_inferences)).set(TRY((((((((((structure).generic_parameters))[i])).type_id)).to_string()))),TRY((((((args)[i])).to_string())))))));
}

}
}

}
if (((callee)->is_static())){
TRY((((*this).error(String("Cannot call static method on an instance of an object"),span))));
}
else {
(arg_offset = static_cast<size_t>(1ULL));
}

if ((((callee)->is_mutating()) && (!((((this_expr.value()))->is_mutable(((*this).program))))))){
TRY((((*this).error(String("Cannot call mutating method on an immutable object instance"),span))));
}
}
else if ((!(((callee)->is_static())))){
TRY((((*this).error_with_hint(String("Cannot call an instance method statically"),span,String("Add a dot before the method name to call an instance method"),span))));
}
JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>>> resolved_args = TRY((((*this).resolve_default_params(((((callee)->generics))->base_params),((call).args),caller_scope_id,safety_mode,arg_offset,span))));
if ((((((((callee)->generics))->base_params)).size()) == (JaktInternal::checked_add<size_t>(((resolved_args).size()),arg_offset)))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>((JaktInternal::checked_sub<size_t>(((((((callee)->generics))->base_params)).size()),arg_offset)))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>> const name_span_checked_arg_ = ((resolved_args)[i]);
String const name = ((name_span_checked_arg_).get<0>());
utility::Span const span = ((name_span_checked_arg_).get<1>());
NonnullRefPtr<types::CheckedExpression> const checked_arg = ((name_span_checked_arg_).get<2>());

TRY((((*this).check_types_for_compat(((((((((((callee)->generics))->base_params))[(JaktInternal::checked_add<size_t>(i,arg_offset))])).variable)).type_id),((checked_arg)->type()),((((*this).generic_inferences))),((checked_arg)->span())))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

}
if ((((type_hint).has_value()) && (!(((((type_hint).value())).equals(types::unknown_type_id())))))){
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
TRY((((*this).check_types_for_compat(return_type,(type_hint.value()),((((*this).generic_inferences))),span))));
(((*this).ignore_errors) = old_ignore_errors);
}
(return_type = TRY((((*this).substitute_typevars_in_type(return_type,((*this).generic_inferences))))));
if ((((type_hint).has_value()) && (!(((((type_hint).value())).equals(types::unknown_type_id())))))){
bool const old_ignore_errors = ((*this).ignore_errors);
if (((callee)->is_instantiated)){
(((*this).ignore_errors) = true);
}
TRY((((*this).check_types_for_compat((type_hint.value()),return_type,((((*this).generic_inferences))),span))));
(((*this).ignore_errors) = old_ignore_errors);
}
{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((((((callee)->generics))->params)).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter generic_typevar = (_magic_value.value());
{
if (((((generic_typevar).kind)).index() == 1 /* Parameter */)){
JaktInternal::Optional<String> const substitution = ((((*this).generic_inferences)).get(TRY((((((generic_typevar).type_id())).to_string())))));
if (((substitution).has_value())){
TRY((((generic_arguments).push(TRY((types::TypeId::TypeId::from_string((substitution.value()))))))));
}
else {
TRY((((*this).error(String("Not all generic parameters have known types"),span))));
}

}
}

}
}

if (((!(((callee)->is_instantiated))) || ((!(((((callee)->linkage)).index() == 1 /* External */))) && (!(((((callee)->generics))->is_specialized_for_types(generic_arguments))))))){
(generic_checked_function_to_instantiate = static_cast<JaktInternal::Optional<types::FunctionId>>(function_id));
}
else if (((callee)->is_instantiated)){
if ((((type_hint).has_value()) && (!(((((type_hint).value())).equals(types::unknown_type_id())))))){
TRY((((*this).check_types_for_compat((type_hint.value()),return_type,((((*this).generic_inferences))),span))));
}
}
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
(return_type = TRY((((*this).substitute_typevars_in_type(return_type,((*this).generic_inferences))))));
if ((callee_throws && (!(((TRY((((*this).get_scope(caller_scope_id)))))->can_throw))))){
TRY((((*this).error(String("Call to function that may throw needs to be in a try statement or a function marked as throws"),span))));
}
if (((generic_checked_function_to_instantiate).has_value())){
if (((maybe_this_type_id).has_value())){
(maybe_this_type_id = TRY((((*this).substitute_typevars_in_type((maybe_this_type_id.value()),((*this).generic_inferences))))));
}
TRY((((*this).typecheck_and_specialize_generic_function((generic_checked_function_to_instantiate.value()),generic_arguments,callee_scope_id,maybe_this_type_id,((*this).generic_inferences),((call).type_args),span))));
}
if ((((*this).dump_try_hints) && callee_throws)){
TRY((((*this).dump_try_hint(span))));
}
types::CheckedCall const function_call = types::CheckedCall(resolved_namespaces,((call).name),args,generic_arguments,resolved_function_id,return_type,callee_throws);
NonnullRefPtr<types::CheckedExpression> const checked_call = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Call>(function_call,span,return_type)));
bool const in_comptime_function = (((((*this).current_function_id)).has_value()) && ((((*this).get_function(((((*this).current_function_id)).value()))))->is_comptime));
if (((!(in_comptime_function)) && (((resolved_function_id).has_value()) && ((((*this).get_function((resolved_function_id.value()))))->is_comptime)))){
NonnullRefPtr<types::CheckedFunction> const resolved_function = ((*this).get_function((resolved_function_id.value())));
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((interpreter::Interpreter::Interpreter::create(((*this).compiler),((*this).program),(TRY((Array<utility::Span>::create_with({})))))));
NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(generic_checked_function_to_instantiate.value_or_lazy_evaluated([&] { return (resolved_function_id.value()); })));
JaktInternal::Array<types::Value> call_args = (TRY((Array<types::Value>::create_with({}))));
JaktInternal::Optional<types::Value> this_argument = JaktInternal::OptionalNone();
NonnullRefPtr<interpreter::InterpreterScope> eval_scope = TRY((interpreter::InterpreterScope::InterpreterScope::from_runtime_scope(caller_scope_id,((*this).program),JaktInternal::OptionalNone())));
{
JaktInternal::DictionaryIterator<String,String> _magic = ((((*this).generic_inferences)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,String>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,String> entry = (_magic_value.value());
{
JaktInternal::Tuple<String,String> const key_value_ = entry;
String const key = ((key_value_).get<0>());
String const value = ((key_value_).get<1>());

TRY((((((eval_scope)->type_bindings)).set(key,TRY((types::TypeId::TypeId::from_string(value)))))));
}

}
}

if (((this_expr).has_value())){
auto __jakt_var_300 = [&]() -> ErrorOr<void> {{
interpreter::StatementResult const evaluated_this = TRY((((interpreter)->execute_expression((this_expr.value()),eval_scope))));
if (((evaluated_this).index() == 5 /* JustValue */)){
types::Value const value = (evaluated_this.get<interpreter::StatementResult::JustValue>()).value;
(this_argument = value);
}
else if (((evaluated_this).index() == 1 /* Throw */)){
types::Value const value = (evaluated_this.get<interpreter::StatementResult::Throw>()).value;
TRY((((*this).error(TRY((String::formatted(String("Error executing this expression (evaluation threw {})"),value))),(((this_expr.value()))->span())))));
}
else {
TRY((((*this).error(String("Invalid this expression"),(((this_expr.value()))->span())))));
}

}

;return {};}();
if (__jakt_var_300.is_error()) {{
TRY((((*this).error(String("Error executing this expression"),(((this_expr.value()))->span())))));
}
};
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> argument = (_magic_value.value());
{
interpreter::StatementResult const value = ({ Optional<interpreter::StatementResult> __jakt_var_301;
auto __jakt_var_302 = [&]() -> ErrorOr<interpreter::StatementResult> { return TRY((((interpreter)->execute_expression(((argument).get<1>()),eval_scope)))); }();
if (__jakt_var_302.is_error()) {{
TRY((((*this).error(String("Error in argument"),span))));
continue;
}
} else {__jakt_var_301 = __jakt_var_302.release_value();
}
__jakt_var_301.release_value(); });
if (((value).index() == 1 /* Throw */)){
TRY((((*this).error(TRY((String::formatted(String("Compiletime call failed: {}"),value))),((((argument).get<1>()))->span())))));
break;
}
types::Value const evaluated_value = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = value;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Return>();
types::Value const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::JustValue>();
types::Value const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
return Error::from_errno(static_cast<i32>(69));
}
};/*case end*/
}/*switch end*/
}()
));
TRY((((call_args).push(evaluated_value))));
}

}
}

JaktInternal::Dictionary<String,types::TypeId> type_bindings = (TRY((Dictionary<String, types::TypeId>::create_with_entries({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((((resolved_function)->generics))->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::FunctionGenericParameter const param = ((((((resolved_function)->generics))->params))[i]);
TRY((((type_bindings).set(TRY((((((param).type_id())).to_string()))),((((function_call).type_args))[i])))));
}

}
}

JaktInternal::Optional<interpreter::ExecutionResult> result = JaktInternal::OptionalNone();
NonnullRefPtr<interpreter::InterpreterScope> invocation_scope = TRY((interpreter::InterpreterScope::InterpreterScope::create((TRY((Dictionary<String, types::Value>::create_with_entries({})))),JaktInternal::OptionalNone(),type_bindings)));
auto __jakt_var_303 = [&]() -> ErrorOr<void> {{
(result = TRY((((interpreter)->execute((resolved_function_id.value()),resolved_namespaces,this_argument,call_args,span,invocation_scope)))));
}

;return {};}();
if (__jakt_var_303.is_error()) {auto error = __jakt_var_303.release_error();{
TRY((((*this).error(TRY((String::formatted(String("Compiletime call failed: {}"),error))),span))));
return (checked_call);
}
};
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::ExecutionResult::Return>();
types::Value const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((interpreter::value_to_checked_expression(x,interpreter))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::ExecutionResult::Throw>();
types::Value const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_304; {
TRY((((*this).error(TRY((String::formatted(String("Compiletime call failed: {}"),x))),span))));
__jakt_var_304 = checked_call; goto __jakt_label_290;

}
__jakt_label_290:; __jakt_var_304.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
return (checked_call);
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_guard(NonnullRefPtr<parser::ParsedExpression> const expr,parser::ParsedBlock const else_block,parser::ParsedBlock const remaining_code,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
bool seen_scope_exit = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedStatement>> _magic = ((((else_block).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedStatement> statement = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedStatement::Break>();
{
(seen_scope_exit = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedStatement::Continue>();
{
(seen_scope_exit = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Return>();{
(seen_scope_exit = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Throw>();{
(seen_scope_exit = true);
return JaktInternal::LoopBreak{};
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
}

}
}

types::CheckedBlock const checked_else_block = TRY((((*this).typecheck_block(else_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((!(seen_scope_exit)) && ((((checked_else_block).control_flow)).may_return()))){
TRY((((*this).error(String("Else block of guard must either `return`, `break`, `continue`, or `throw`"),span))));
}
JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings(expr,JaktInternal::OptionalNone(),remaining_code,TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Block>(else_block,span))),span))));
NonnullRefPtr<parser::ParsedExpression> const new_condition = ((new_condition_new_then_block_new_else_statement_).get<0>());
JaktInternal::Optional<parser::ParsedBlock> const new_then_block = ((new_condition_new_then_block_new_else_statement_).get<1>());
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const new_else_statement = ((new_condition_new_then_block_new_else_statement_).get<2>());

NonnullRefPtr<types::CheckedExpression> const checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("Condition must be a boolean expression"),((new_condition)->span())))));
}
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block((new_then_block.value()),scope_id,safety_mode,JaktInternal::OptionalNone()))));
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> checked_else = JaktInternal::OptionalNone();
if (((new_else_statement).has_value())){
(checked_else = TRY((((*this).typecheck_statement((new_else_statement.value()),scope_id,safety_mode,JaktInternal::OptionalNone())))));
}
if (((((checked_block).yielded_type)).has_value())){
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Yield>(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Match>(checked_condition,(TRY((Array<types::CheckedMatchCase>::create_with({ types::CheckedMatchCase { typename types::CheckedMatchCase::Expression(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Boolean>(true,span))), types::CheckedMatchBody { typename types::CheckedMatchBody::Expression(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Block>(checked_block,span,(((checked_block).yielded_type).value()))))) } ,span) } ,  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll(false, types::CheckedMatchBody { typename types::CheckedMatchBody::Block(checked_else_block) } ,span) } })))),span,(((checked_block).yielded_type).value()),false))),span))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::If>(checked_condition,checked_block,checked_else,span))));
}
}

ErrorOr<bool> typechecker::Typechecker::add_comptime_binding_to_scope(types::ScopeId const scope_id,String const name,types::Value const value,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
{
JaktInternal::DictionaryIterator<String,types::Value> _magic = ((((scope)->comptime_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::Value>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::Value> existing = (_magic_value.value());
{
if ((name == ((existing).get<0>()))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("Redefinition of comptime variable ‘{}’"),name))),span,String("previous definition here"),((((existing).get<1>())).span)))));
}
}

}
}

TRY((((((scope)->comptime_bindings)).set(name,value))));
return (true);
}
}

ErrorOr<bool> typechecker::Typechecker::add_trait_to_scope(types::ScopeId const scope_id,String const trait_name,types::TraitId const trait_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::TraitId> const found_trait_id = ((((scope)->traits)).get(trait_name));
if ((((found_trait_id).has_value()) && (!((((found_trait_id.value())).equals(trait_id)))))){
TRY((((*this).error(TRY((String::formatted(String("Redefinition of trait ‘{}’"),trait_name))),span))));
return (false);
}
TRY((((((scope)->traits)).set(trait_name,trait_id))));
return (true);
}
}

ErrorOr<bool> typechecker::Typechecker::signatures_match(NonnullRefPtr<types::CheckedFunction> const first,NonnullRefPtr<types::CheckedFunction> const second) {
{
Function<ErrorOr<bool>(typechecker::Typechecker&, types::TypeId, types::TypeId)> const types_match = [](typechecker::Typechecker& typechecker, types::TypeId a, types::TypeId b) -> ErrorOr<bool> {
types::TypeId const mapped_a = TRY((types::TypeId::TypeId::from_string(((((((typechecker))).generic_inferences)).map(TRY((((a).to_string()))))))));
types::TypeId const mapped_b = TRY((types::TypeId::TypeId::from_string(((((((typechecker))).generic_inferences)).map(TRY((((b).to_string()))))))));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *((((typechecker))).get_type(mapped_a));
switch(__jakt_match_variant.index()) {
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((((typechecker))).implements_trait(mapped_b,id,JaktInternal::OptionalNone())))));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((((typechecker))).implements_trait(mapped_b,id,args)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_305; {
bool const old_ignore_errors = ((((typechecker))).ignore_errors);
(((((typechecker))).ignore_errors) = true);
ScopeGuard __jakt_var_306([&] {
{
(((((typechecker))).ignore_errors) = old_ignore_errors);
}

});
__jakt_var_305 = TRY((((((typechecker))).check_types_for_compat(mapped_a,mapped_b,((((((typechecker))).generic_inferences))),utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)))))); goto __jakt_label_291;

}
__jakt_label_291:; __jakt_var_305.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
}
;
if (TRY((types_match(((*this)),((first)->return_type_id),((second)->return_type_id))))){
if ((((first)->can_throw) == ((second)->can_throw))){
if ((((((first)->params)).size()) == ((((second)->params)).size()))){
size_t arg_start = static_cast<size_t>(0ULL);
if (((first)->is_static())){
if (((second)->is_static())){
}
else {
return (false);
}

}
else {
if ((!(((second)->is_static())))){
if ((((first)->is_mutating()) == ((second)->is_mutating()))){
(arg_start = static_cast<size_t>(1ULL));
}
else {
return (false);
}

}
else {
return (false);
}

}

{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(arg_start),static_cast<size_t>(((((first)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (TRY((types_match(((*this)),((((((((first)->params))[i])).variable)).type_id),((((((((second)->params))[i])).variable)).type_id))))){
}
else {
return (false);
}

}

}
}

return (true);
}
else {
return (false);
}

}
else {
return (false);
}

}
else {
return (false);
}

}
}

ErrorOr<String> typechecker::Typechecker::type_name(types::TypeId const type_id) const {
{
return (TRY((((((*this).program))->type_name(type_id)))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_namespaced_var_or_simple_enum_constructor_call(String const name,JaktInternal::Array<String> const namespace_,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint,utility::Span const span) {
{
JaktInternal::Array<types::ScopeId> scopes = (TRY((Array<types::ScopeId>::create_with({scope_id}))));
{
JaktInternal::ArrayIterator<String> _magic = ((namespace_).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String ns = (_magic_value.value());
{
types::ScopeId const scope = ((scopes)[(JaktInternal::checked_sub<size_t>(((scopes).size()),static_cast<size_t>(1ULL)))]);
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> const ns_in_scope = TRY((((*this).find_namespace_in_scope(scope,ns))));
JaktInternal::Optional<types::EnumId> const enum_in_scope = TRY((((((*this).program))->find_enum_in_scope(scope,ns))));
types::ScopeId next_scope = scope;
if (((ns_in_scope).has_value())){
(next_scope = (((ns_in_scope.value())).get<0>()));
}
else if (((enum_in_scope).has_value())){
(next_scope = ((((*this).get_enum((enum_in_scope.value())))).scope_id));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Namespace ‘{}’ not found"),ns))),span))));
}

TRY((((scopes).push(next_scope))));
}

}
}

types::ScopeId const scope = (((scopes).last()).value());
size_t i = static_cast<size_t>(0ULL);
size_t const min_length = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = ((((scopes).size()) <= ((namespace_).size())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((scopes).size()));
}
else {
return JaktInternal::ExplicitValue(((namespace_).size()));
}
}()))
;
JaktInternal::Array<types::CheckedNamespace> checked_namespaces = (TRY((Array<types::CheckedNamespace>::create_with({}))));
while ((i < min_length)){
TRY((((checked_namespaces).push(types::CheckedNamespace(((namespace_)[i]),scope)))));
((i++));
}
JaktInternal::Optional<types::CheckedVariable> const var = TRY((((*this).find_var_in_scope(scope,name))));
if (((var).has_value())){
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NamespacedVar>(checked_namespaces,(var.value()),span))));
}
parser::ParsedCall const implicit_constructor_call = parser::ParsedCall(namespace_,name,(TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>>::create_with({})))),(TRY((Array<NonnullRefPtr<parser::ParsedType>>::create_with({})))));
NonnullRefPtr<types::CheckedExpression> const call_expression = TRY((((*this).typecheck_call(implicit_constructor_call,scope_id,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),safety_mode,type_hint,true))));
types::TypeId const type_id = ((call_expression)->type());
types::CheckedCall const call = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedCall, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *call_expression;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(call);
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(String("typecheck_call returned something other than a CheckedCall")))));
}
};/*case end*/
}/*switch end*/
}()
));
if (((((call).function_id)).has_value())){
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Call>(call,span,type_id))));
}
TRY((((*this).error(TRY((String::formatted(String("Variable '{}' not found"),name))),span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NamespacedVar>(checked_namespaces,types::CheckedVariable(name,types::unknown_type_id(),false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ),span))));
}
}

NonnullRefPtr<types::Module> typechecker::Typechecker::current_module() const {
{
return (((((*this).program))->get_module(((*this).current_module_id))));
}
}

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>>> typechecker::Typechecker::typecheck_match_variant(parser::ParsedMatchCase const case_,types::TypeId const subject_type_id,size_t const variant_index,JaktInternal::Optional<types::TypeId> const final_result_type,types::CheckedEnumVariant const variant,JaktInternal::Array<parser::EnumVariantPatternArgument> const variant_arguments,utility::Span const arguments_span,types::ScopeId const scope_id,types::SafetyMode const safety_mode) {
{
JaktInternal::Optional<String> covered_name = JaktInternal::OptionalNone();
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((String::formatted(String("catch-enum-variant({})"),((variant).name()))))))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& name = __jakt_match_value.name;
{
(covered_name = name);
if ((!(((variant_arguments).is_empty())))){
TRY((((*this).error(TRY((String::formatted(String("Match case '{}' cannot have arguments"),name))),arguments_span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& name = __jakt_match_value.name;
types::TypeId const& type_id = __jakt_match_value.type_id;
utility::Span const& span = __jakt_match_value.span;
{
(covered_name = name);
if ((!(((variant_arguments).is_empty())))){
if ((((variant_arguments).size()) != static_cast<size_t>(1ULL))){
TRY((((*this).error(TRY((String::formatted(String("Match case ‘{}’ must have exactly one argument"),name))),span))));
}
else {
parser::EnumVariantPatternArgument const variant_argument = ((variant_arguments)[static_cast<i64>(0LL)]);
types::TypeId const variable_type_id = TRY((((*this).substitute_typevars_in_type(type_id,((*this).generic_inferences)))));
types::VarId const var_id = TRY((((module)->add_variable(types::CheckedVariable(((variant_argument).binding),variable_type_id,false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } )))));
TRY((((*this).add_var_to_scope(new_scope_id,((variant_argument).binding),var_id,span))));
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& name = __jakt_match_value.name;
JaktInternal::Array<types::VarId> const& fields = __jakt_match_value.fields;
{
(covered_name = name);
JaktInternal::Array<types::CheckedVariable> field_variables = (TRY((Array<types::CheckedVariable>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId var_id = (_magic_value.value());
{
TRY((((field_variables).push(((((*this).program))->get_variable(var_id))))));
}

}
}

JaktInternal::Set<String> seen_names = (TRY((Set<String>::create_with_values({}))));
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((variant_arguments).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument arg = (_magic_value.value());
{
if ((!(((((arg).name)).has_value())))){
bool found_field_name = false;
JaktInternal::Array<String> field_names = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedVariable> _magic = ((field_variables).iterator());
for (;;){
JaktInternal::Optional<types::CheckedVariable> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedVariable var = (_magic_value.value());
{
TRY((((field_names).push(((var).name)))));
if ((((var).name) == ((arg).binding))){
(found_field_name = true);
}
}

}
}

if ((!(found_field_name))){
JaktInternal::Array<String> unused_field_names = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<String> _magic = ((field_names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String field_name = (_magic_value.value());
{
if (((seen_names).contains(field_name))){
continue;
}
TRY((((unused_field_names).push(field_name))));
}

}
}

TRY((((*this).error_with_hint(TRY((String::formatted(String("Match case argument '{}' for struct-like enum variant '{}' cannot be anon"),((arg).binding),name))),((arg).span),TRY((String::formatted(String("Available arguments for '{}' are: {}\n"),name,utility::join(unused_field_names,String(", "))))),((arg).span)))));
continue;
}
}
String const arg_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); });
if (((seen_names).contains(arg_name))){
TRY((((*this).error(TRY((String::formatted(String("Match case argument '{}' is already defined"),arg_name))),((arg).span)))));
continue;
}
TRY((((seen_names).add(arg_name))));
JaktInternal::Optional<types::CheckedVariable> matched_field_variable = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedVariable> _magic = ((field_variables).iterator());
for (;;){
JaktInternal::Optional<types::CheckedVariable> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedVariable var = (_magic_value.value());
{
if ((((var).name) == arg_name)){
(matched_field_variable = var);
}
}

}
}

JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>>>>{
auto __jakt_enum_value = (((matched_field_variable).has_value()));
if (__jakt_enum_value == true) {
{
types::TypeId const substituted_type_id = TRY((((*this).substitute_typevars_in_type((((matched_field_variable.value())).type_id),((*this).generic_inferences)))));
utility::Span const matched_span = (((matched_field_variable.value())).definition_span);
if (((*this).dump_type_hints)){
TRY((((*this).dump_type_hint((((matched_field_variable.value())).type_id),((arg).span)))));
}
types::VarId const var_id = TRY((((module)->add_variable(types::CheckedVariable(((arg).binding),substituted_type_id,false,matched_span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } )))));
TRY((((*this).add_var_to_scope(new_scope_id,((arg).binding),var_id,matched_span))));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((*this).error(TRY((String::formatted(String("Match case argument '{}' does not exist in struct-like enum variant '{}'"),arg_name,name))),((arg).span)))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::todo(TRY((String::formatted(String("implement {} match case for matched variant"),((variant).name())))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).get<1>());

types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::EnumVariant(((variant).name()),variant_arguments,subject_type_id,variant_index,new_scope_id,checked_body,((case_).marker_span)) } ;
return ((Tuple{covered_name, checked_match_case, result_type}));
}
}

ErrorOr<void> typechecker::Typechecker::error_with_hint(String const message,utility::Span const span,String const hint,utility::Span const hint_span) {
{
if ((!(((*this).ignore_errors)))){
TRY((((((((*this).compiler))->errors)).push( error::JaktError { typename error::JaktError::MessageWithHint(message,span,hint,hint_span) } ))));
}
}
return {};
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>>> typechecker::Typechecker::find_type_scope(types::ScopeId const scope_id,String const name) const {
{
types::ScopeId current = scope_id;
for (;;){
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(current))));
JaktInternal::Optional<types::TypeId> const maybe_type = ((((scope)->types)).get(name));
if (((maybe_type).has_value())){
return ((Tuple{(maybe_type.value()), current}));
}
{
JaktInternal::ArrayIterator<types::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<types::ScopeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ScopeId child_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((*this).get_scope(child_id))));
if ((!(((((child_scope)->namespace_name)).has_value())))){
JaktInternal::Optional<types::TypeId> const maybe_type = ((((child_scope)->types)).get(name));
if (((maybe_type).has_value())){
return ((Tuple{(maybe_type.value()), child_id}));
}
}
}

}
}

if (((((scope)->parent)).has_value())){
(current = ((((scope)->parent)).value()));
}
else {
break;
}

}
return (JaktInternal::OptionalNone());
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_indexed_tuple(NonnullRefPtr<parser::ParsedExpression> const expr,size_t const index,types::ScopeId const scope_id,bool const is_optional,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude(String("Tuple")))));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
types::TypeId expr_type_id = types::unknown_type_id();
if (((((*this).get_type(((checked_expr)->type()))))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(((checked_expr)->type())))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(((checked_expr)->type())))->get<types::Type::GenericInstance>()).args;
if (((id).equals(tuple_struct_id))){
if (is_optional){
TRY((((*this).error(String("Optional chaining is not allowed on a non-optional tuple type"),span))));
}
if ((index >= ((args).size()))){
TRY((((*this).error(String("Tuple index past the end of the tuple"),span))));
}
else {
(expr_type_id = ((args)[index]));
}

}
else if ((is_optional && ((id).equals(optional_struct_id)))){
types::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((((*this).get_type(inner_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(inner_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(inner_type_id))->get<types::Type::GenericInstance>()).args;
if (((id).equals(tuple_struct_id))){
if ((index >= ((args).size()))){
TRY((((*this).error(String("Optional-chained tuple index past the end of the tuple"),span))));
}
else {
(expr_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({((args)[index])}))))))))))));
}

}
}
else {
TRY((((*this).error(String("Optional-chained tuple index used on non-tuple value"),span))));
}

}
}
else if (is_optional){
TRY((((*this).error(String("Optional-chained tuple index used on non-tuple value"),span))));
}
else {
TRY((((*this).error(String("Tuple index used on non-tuple value"),span))));
}

return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedTuple>(checked_expr,index,span,is_optional,expr_type_id))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::find_or_add_type_id(NonnullRefPtr<types::Type> const type) {
{
return (TRY((((((*this).program))->find_or_add_type_id(type,((*this).current_module_id))))));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>>> typechecker::Typechecker::find_namespace_in_scope(types::ScopeId const scope_id,String const name) const {
{
return (TRY((((((*this).program))->find_namespace_in_scope(scope_id,name)))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_typename(NonnullRefPtr<parser::ParsedType> const parsed_type,types::ScopeId const scope_id,JaktInternal::Optional<String> const name) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<types::TypeId>>{
auto&& __jakt_match_variant = *parsed_type;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Reference>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_307; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
__jakt_var_307 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Reference>(inner_type_id))))))); goto __jakt_label_292;

}
__jakt_label_292:; __jakt_var_307.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::MutableReference>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_308; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
__jakt_var_308 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::MutableReference>(inner_type_id))))))); goto __jakt_label_293;

}
__jakt_label_293:; __jakt_var_308.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::NamespacedName>();String const& name = __jakt_match_value.name;
JaktInternal::Array<String> const& namespaces = __jakt_match_value.namespaces;
JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> const& params = __jakt_match_value.params;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_309; {
types::ScopeId current_namespace_scope_id = scope_id;
{
JaktInternal::ArrayIterator<String> _magic = ((namespaces).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String ns = (_magic_value.value());
{
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> const result = TRY((((*this).find_namespace_in_scope(current_namespace_scope_id,ns))));
if (((result).has_value())){
(current_namespace_scope_id = (((result.value())).get<0>()));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Unknown namespace: '{}'"),ns))),span))));
return (types::unknown_type_id());
}

}

}
}

JaktInternal::Array<types::TypeId> generic_args = (TRY((Array<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedType>> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedType> param = (_magic_value.value());
{
types::TypeId const checked_arg = TRY((((*this).typecheck_typename(param,scope_id,name))));
TRY((((generic_args).push(checked_arg))));
}

}
}

JaktInternal::Optional<types::TypeId> type_id = JaktInternal::OptionalNone();
if (((generic_args).is_empty())){
NonnullRefPtr<parser::ParsedType> const synthetic_typename = TRY((parser::ParsedType::template create<typename parser::ParsedType::Name>(name,span)));
(type_id = TRY((((*this).typecheck_typename(synthetic_typename,current_namespace_scope_id,name)))));
}
else {
(type_id = TRY((((*this).typecheck_generic_resolved_type(name,generic_args,current_namespace_scope_id,span)))));
}

__jakt_var_309 = (type_id.value()); goto __jakt_label_294;

}
__jakt_label_294:; __jakt_var_309.release_value(); }));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_310; {
JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>> const maybe_type_and_scope = TRY((((*this).find_type_scope(scope_id,name))));
if (((maybe_type_and_scope).has_value())){
if ((!((((((maybe_type_and_scope.value())).get<1>())).equals(((*this).prelude_scope_id())))))){
return ((((maybe_type_and_scope.value())).get<0>()));
}
}
__jakt_var_310 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId,ErrorOr<types::TypeId>>{
auto __jakt_enum_value = (name);
if (__jakt_enum_value == String("i8")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } ));
}
else if (__jakt_enum_value == String("i16")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } ));
}
else if (__jakt_enum_value == String("i32")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } ));
}
else if (__jakt_enum_value == String("i64")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } ));
}
else if (__jakt_enum_value == String("u8")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } ));
}
else if (__jakt_enum_value == String("u16")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } ));
}
else if (__jakt_enum_value == String("u32")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } ));
}
else if (__jakt_enum_value == String("u64")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } ));
}
else if (__jakt_enum_value == String("f32")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::F32() } ));
}
else if (__jakt_enum_value == String("f64")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::F64() } ));
}
else if (__jakt_enum_value == String("c_char")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } ));
}
else if (__jakt_enum_value == String("c_int")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } ));
}
else if (__jakt_enum_value == String("usize")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } ));
}
else if (__jakt_enum_value == String("String")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ));
}
else if (__jakt_enum_value == String("bool")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
else if (__jakt_enum_value == String("void")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } ));
}
else if (__jakt_enum_value == String("never")) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Never() } ));
}
else {
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_311; {
if (((maybe_type_and_scope).has_value())){
return ((((maybe_type_and_scope.value())).get<0>()));
}
TRY((((*this).error(TRY((String::formatted(String("Unknown type ‘{}’"),name))),span))));
__jakt_var_311 = types::unknown_type_id(); goto __jakt_label_296;

}
__jakt_label_296:; __jakt_var_311.release_value(); }));
}
}()))
; goto __jakt_label_295;

}
__jakt_label_295:; __jakt_var_310.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedType::Empty>();
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_312; {
__jakt_var_312 = types::unknown_type_id(); goto __jakt_label_297;

}
__jakt_label_297:; __jakt_var_312.release_value(); }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::JaktTuple>();JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> const& types = __jakt_match_value.types;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_313; {
JaktInternal::Array<types::TypeId> checked_types = (TRY((Array<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedType>> _magic = ((types).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedType> parsed_type = (_magic_value.value());
{
TRY((((checked_types).push(TRY((((*this).typecheck_typename(parsed_type,scope_id,name))))))));
}

}
}

types::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude(String("Tuple")))));
__jakt_var_313 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(tuple_struct_id,checked_types))))))); goto __jakt_label_298;

}
__jakt_label_298:; __jakt_var_313.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::JaktArray>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_314; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
types::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(String("Array")))));
__jakt_var_314 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(array_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id}))))))))))); goto __jakt_label_299;

}
__jakt_label_299:; __jakt_var_314.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Dictionary>();NonnullRefPtr<parser::ParsedType> const& key = __jakt_match_value.key;
NonnullRefPtr<parser::ParsedType> const& value = __jakt_match_value.value;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_315; {
types::TypeId const key_type_id = TRY((((*this).typecheck_typename(key,scope_id,name))));
types::TypeId const value_type_id = TRY((((*this).typecheck_typename(value,scope_id,name))));
types::StructId const dict_struct_id = TRY((((*this).find_struct_in_prelude(String("Dictionary")))));
__jakt_var_315 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(dict_struct_id,(TRY((Array<types::TypeId>::create_with({key_type_id, value_type_id}))))))))))); goto __jakt_label_300;

}
__jakt_label_300:; __jakt_var_315.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Set>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_316; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
types::StructId const set_struct_id = TRY((((*this).find_struct_in_prelude(String("Set")))));
__jakt_var_316 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(set_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id}))))))))))); goto __jakt_label_301;

}
__jakt_label_301:; __jakt_var_316.release_value(); }));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Optional>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_317; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
__jakt_var_317 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id}))))))))))); goto __jakt_label_302;

}
__jakt_label_302:; __jakt_var_317.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::WeakPtr>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_318; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
types::StructId const weakptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
__jakt_var_318 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(weakptr_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id}))))))))))); goto __jakt_label_303;

}
__jakt_label_303:; __jakt_var_318.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::RawPtr>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_319; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
__jakt_var_319 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::RawPtr>(inner_type_id))))))); goto __jakt_label_304;

}
__jakt_label_304:; __jakt_var_319.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::GenericType>();String const& name = __jakt_match_value.name;
JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> const& generic_parameters = __jakt_match_value.generic_parameters;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_320; {
JaktInternal::Array<types::TypeId> checked_inner_types = (TRY((Array<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedType>> _magic = ((generic_parameters).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedType> inner_type = (_magic_value.value());
{
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner_type,scope_id,name))));
TRY((((checked_inner_types).push(inner_type_id))));
}

}
}

__jakt_var_320 = TRY((((*this).typecheck_generic_resolved_type(name,checked_inner_types,scope_id,span)))); goto __jakt_label_305;

}
__jakt_label_305:; __jakt_var_320.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Function>();JaktInternal::Array<parser::ParsedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
NonnullRefPtr<parser::ParsedType> const& return_type = __jakt_match_value.return_type;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_321; {
String const function_name = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<types::TypeId>>{
auto __jakt_enum_value = (((name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((name.value()));
}
else {
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_322;
auto __jakt_var_323 = [&]() -> ErrorOr<String> { return TRY((String::formatted(String("lambda{}"),((((*this).lambda_count)++))))); }();
if (!__jakt_var_323.is_error()) __jakt_var_322 = __jakt_var_323.release_value();
__jakt_var_322; }).value_or_lazy_evaluated([&] { return String(""); }));
}
}()))
;
JaktInternal::Array<types::CheckedParameter> checked_params = (TRY((Array<types::CheckedParameter>::create_with({}))));
bool first = true;
JaktInternal::Dictionary<String,String> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_324([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
{
JaktInternal::ArrayIterator<parser::ParsedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedParameter param = (_magic_value.value());
{
TRY((((checked_params).push(TRY((((*this).typecheck_parameter(param,scope_id,first,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))))))));
(first = false);
}

}
}

NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::create(function_name,span, types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).typecheck_typename(return_type,scope_id,JaktInternal::OptionalNone())))),((return_type)->span()),checked_params,TRY((types::FunctionGenerics::create(scope_id,checked_params,(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,JaktInternal::OptionalNone(),false),can_throw, parser::FunctionType { typename parser::FunctionType::Expression() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
JaktInternal::Array<types::TypeId> param_type_ids = (TRY((Array<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((param_type_ids).push(((((param).variable)).type_id)))));
}

}
}

__jakt_var_321 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Function>(param_type_ids,can_throw,((checked_function)->return_type_id),function_id))))))); goto __jakt_label_306;

}
__jakt_label_306:; __jakt_var_321.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_predecl(parser::ParsedRecord const parsed_record,types::EnumId const enum_id,types::ScopeId const scope_id) {
{
types::TypeId const enum_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Enum>(enum_id)))))));
types::ScopeId const enum_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((String::formatted(String("enum({})"),((parsed_record).name))))))));
TRY((((*this).add_enum_to_scope(scope_id,((parsed_record).name),enum_id,((parsed_record).name_span)))));
types::TypeId const underlying_type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();NonnullRefPtr<parser::ParsedType> const& underlying_type = __jakt_match_value.underlying_type;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_typename(underlying_type,scope_id,JaktInternal::OptionalNone())))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } ));
};/*case end*/
}/*switch end*/
}()
));
bool const is_boxed = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();bool const& is_boxed = __jakt_match_value.is_boxed;
return JaktInternal::ExplicitValue(is_boxed);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
}/*switch end*/
}()
));
JaktInternal::Array<types::CheckedField> checked_fields = (TRY((Array<types::CheckedField>::create_with({}))));
JaktInternal::Set<String> seen_fields = (TRY((Set<String>::create_with_values({}))));
if (((((parsed_record).record_type)).index() == 3 /* SumEnum */)){
JaktInternal::Array<parser::ParsedField> const fields = (((parsed_record).record_type).get<parser::RecordType::SumEnum>()).fields;
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField field = (_magic_value.value());
{
parser::ParsedVarDecl const var_decl = ((field).var_decl);
if (((seen_fields).contains(((var_decl).name)))){
TRY((((*this).error(TRY((String::formatted(String("Field '{}' is defined more than once"),((var_decl).name)))),((var_decl).span)))));
continue;
}
TRY((((seen_fields).add(((var_decl).name)))));
types::TypeId const type_id = TRY((((*this).typecheck_typename(((var_decl).parsed_type),enum_scope_id,((var_decl).name)))));
types::CheckedVariable const checked_var = types::CheckedVariable(((var_decl).name),type_id,((var_decl).is_mutable),((var_decl).span),((((var_decl).parsed_type))->span()),TRY((((*this).typecheck_visibility(((field).visibility),enum_scope_id)))));
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> default_value = JaktInternal::OptionalNone();
if (((((field).default_value)).has_value())){
(default_value = TRY((((*this).typecheck_expression((((field).default_value).value()),enum_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,type_id)))));
}
if ((((*this).dump_type_hints) && ((((var_decl).parsed_type))->index() == 13 /* Empty */))){
TRY((((*this).dump_type_hint(type_id,((var_decl).span)))));
}
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const variable_id = TRY((((module)->add_variable(checked_var))));
TRY((((checked_fields).push(types::CheckedField(variable_id,default_value)))));
}

}
}

}
NonnullRefPtr<types::Module> module = ((*this).current_module());
(((((module)->enums))[((enum_id).id)]) = types::CheckedEnum(((parsed_record).name),((parsed_record).name_span),(TRY((Array<types::CheckedGenericParameter>::create_with({})))),(TRY((Array<types::CheckedEnumVariant>::create_with({})))),checked_fields,enum_scope_id,((parsed_record).definition_linkage),(TRY((Dictionary<String, JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>::create_with_entries({})))),((parsed_record).record_type),underlying_type_id,enum_type_id,is_boxed));
JaktInternal::Array<types::CheckedGenericParameter> generic_parameters = ((((((module)->enums))[((enum_id).id)])).generic_parameters);
TRY((((generic_parameters).ensure_capacity(((((parsed_record).generic_parameters)).size())))));
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((parsed_record).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter gen_parameter = (_magic_value.value());
{
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::TypeVariable>(((gen_parameter).name))))))));
types::TypeId const parameter_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
types::CheckedGenericParameter checked_param = TRY((types::CheckedGenericParameter::CheckedGenericParameter::make(parameter_type_id,((gen_parameter).span))));
if (((((gen_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((gen_parameter).requires_list).value()),((((checked_param).constraints))),scope_id))));
}
TRY((((generic_parameters).push(checked_param))));
TRY((((*this).add_type_to_scope(enum_scope_id,((gen_parameter).name),parameter_type_id,((gen_parameter).span)))));
}

}
}

if (((((parsed_record).implements_list)).has_value())){
TRY((((*this).fill_trait_implementation_list((((parsed_record).implements_list).value()),((((((((module)->enums))[((enum_id).id)])).trait_implementations))),enum_scope_id,JaktInternal::OptionalNone()))));
}
bool const is_extern = ((((parsed_record).definition_linkage)).index() == 1 /* External */);
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((parsed_record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
parser::ParsedFunction const func = ((method).parsed_function);
types::ScopeId const method_scope_id = TRY((((*this).create_scope(enum_scope_id,((func).can_throw),TRY((String::formatted(String("method({}::{})"),((parsed_record).name),((func).name))))))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(method_scope_id,((func).can_throw),TRY((String::formatted(String("method-block({}::{})"),((parsed_record).name),((func).name))))))));
bool const is_generic = ((!(((((parsed_record).generic_parameters)).is_empty()))) || (!(((((func).generic_parameters)).is_empty()))));
NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((func).name),((func).name_span),TRY((((*this).typecheck_visibility(((method).visibility),enum_scope_id)))),types::unknown_type_id(),JaktInternal::OptionalNone(),(TRY((Array<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::create(method_scope_id,(TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::TypeId::none(),false),((func).can_throw),((func).type),((func).linkage),method_scope_id,JaktInternal::OptionalNone(),((!(is_generic)) || is_extern),func,((func).is_comptime),false,false)));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
JaktInternal::Array<types::FunctionGenericParameter> generic_parameters = (TRY((Array<types::FunctionGenericParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((func).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter generic_parameter = (_magic_value.value());
{
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::TypeVariable>(((generic_parameter).name))))))));
types::TypeId const type_var_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
types::FunctionGenericParameter parameter = TRY((types::FunctionGenericParameter::FunctionGenericParameter::parameter(type_var_type_id,((generic_parameter).span))));
if (((((generic_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((generic_parameter).requires_list).value()),((((((parameter).checked_parameter)).constraints))),scope_id))));
}
TRY((((generic_parameters).push(parameter))));
if ((!(((func).must_instantiate)))){
TRY((((*this).add_type_to_scope(method_scope_id,((generic_parameter).name),type_var_type_id,((generic_parameter).span)))));
}
}

}
}

(((((checked_function)->generics))->params) = generic_parameters);
{
JaktInternal::ArrayIterator<parser::ParsedParameter> _magic = ((((func).params)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedParameter param = (_magic_value.value());
{
if ((((((param).variable)).name) == String("this"))){
types::CheckedVariable const checked_variable = types::CheckedVariable(((((param).variable)).name),enum_type_id,((((param).variable)).is_mutable),((((param).variable)).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,JaktInternal::OptionalNone())))));
}
else {
types::TypeId const param_type = TRY((((*this).typecheck_typename(((((param).variable)).parsed_type),method_scope_id,((((param).variable)).name)))));
types::CheckedVariable const checked_variable = types::CheckedVariable(((((param).variable)).name),param_type,((((param).variable)).is_mutable),((((param).variable)).span),((((((param).variable)).parsed_type))->span()), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,JaktInternal::OptionalNone())))));
}

}

}
}

TRY((((*this).add_function_to_scope(enum_scope_id,((func).name),function_id,((parsed_record).name_span)))));
types::TypeId const function_return_type_id = TRY((((*this).typecheck_typename(((func).return_type),method_scope_id,JaktInternal::OptionalNone()))));
(((checked_function)->return_type_id) = function_return_type_id);
}

}
}

}
return {};
}

ErrorOr<JaktInternal::Optional<types::CheckedEnumVariant>> typechecker::Typechecker::get_enum_variant(types::CheckedEnum const enum_,String const variant_name) {
{
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if ((((variant).name()) == variant_name)){
return (variant);
}
}

}
}

return (JaktInternal::OptionalNone());
}
}

types::ScopeId typechecker::Typechecker::root_scope_id() const {
{
return (types::ScopeId(types::ModuleId(static_cast<size_t>(1ULL)),static_cast<size_t>(0ULL)));
}
}

ErrorOr<JaktInternal::Optional<types::FunctionId>> typechecker::Typechecker::find_function_in_scope(types::ScopeId const parent_scope_id,String const function_name) const {
{
return (TRY((((((*this).program))->find_function_in_scope(parent_scope_id,function_name)))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_loop(parser::ParsedBlock const parsed_block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(parsed_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(String("A ‘loop’ block is not allowed to yield values"),(((parsed_block).find_yield_span()).value())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Loop>(checked_block,span))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_trait(parser::ParsedTrait const parsed_trait,types::TraitId const trait_id,types::ScopeId const scope_id) {
{
NonnullRefPtr<types::CheckedTrait> const checked_trait = ((((((((((*this).program))->modules))[((((trait_id).module)).id)]))->traits))[((trait_id).id)]);
{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((parsed_trait).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction parsed_function = (_magic_value.value());
{
if (((((((parsed_function).block)).stmts)).is_empty())){
continue;
}
TRY((((*this).typecheck_function(parsed_function,((checked_trait)->scope_id)))));
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_defer(NonnullRefPtr<parser::ParsedStatement> const statement,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
bool const was_inside_defer = ((*this).inside_defer);
(((*this).inside_defer) = true);
ScopeGuard __jakt_var_325([&] {
(((*this).inside_defer) = was_inside_defer);
});
NonnullRefPtr<types::CheckedStatement> const checked_statement = TRY((((*this).typecheck_statement(statement,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((checked_statement)->index() == 5 /* Block */)){
types::CheckedBlock const block = (checked_statement->get<types::CheckedStatement::Block>()).block;
if (((((block).yielded_type)).has_value())){
TRY((((*this).error(String("‘yield’ inside ‘defer’ is meaningless"),span))));
}
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Defer>(checked_statement,span))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_unary_operation(NonnullRefPtr<types::CheckedExpression> const checked_expr,types::CheckedUnaryOperator const checked_op,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode) {
{
types::TypeId const expr_type_id = ((checked_expr)->type());
NonnullRefPtr<types::Type> const expr_type = ((*this).get_type(expr_type_id));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = checked_op;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PreIncrement>();
{
if (((*this).is_integer(expr_type_id))){
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Increment/decrement of immutable variable"),span))));
}
}
else {
TRY((((*this).error(String("Increment/decrement of non-numeric value"),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PostIncrement>();
{
if (((*this).is_integer(expr_type_id))){
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Increment/decrement of immutable variable"),span))));
}
}
else {
TRY((((*this).error(String("Increment/decrement of non-numeric value"),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PreDecrement>();
{
if (((*this).is_integer(expr_type_id))){
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Increment/decrement of immutable variable"),span))));
}
}
else {
TRY((((*this).error(String("Increment/decrement of non-numeric value"),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PostDecrement>();
{
if (((*this).is_integer(expr_type_id))){
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Increment/decrement of immutable variable"),span))));
}
}
else {
TRY((((*this).error(String("Increment/decrement of non-numeric value"),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::LogicalNot>();
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,expr_type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::BitwiseNot>();
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,expr_type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::TypeCast>();
types::CheckedTypeCast const& cast = __jakt_match_value.value;
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,((cast).type_id())))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Negate>();
{
return (TRY((((*this).typecheck_unary_negate(checked_expr,span,expr_type_id)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Is>();
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedUnaryOperator::IsEnumVariant>();{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::RawAddress>();
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::RawPtr>(expr_type_id)))))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Reference>();
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Reference>(expr_type_id)))))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::MutableReference>();
{
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Cannot make mutable reference to immutable value"),span))));
}
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::MutableReference>(expr_type_id)))))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Dereference>();
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr_type;
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& type_id = __jakt_match_value.value;
{
if (((safety_mode).index() == 0 /* Safe */)){
TRY((((*this).error(String("Dereference of raw pointer outside of unsafe block"),span))));
}
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((String::formatted(String("Dereference of a non-pointer type ‘{}’"),TRY((((*this).type_name(expr_type_id))))))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,expr_type_id))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_module(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
TRY((((*this).typecheck_namespace_imports(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_predecl(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_fields(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_constructors(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_function_predecl(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_declarations(parsed_namespace,scope_id))));
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_declarations(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
JaktInternal::Array<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_declarations(child_namespace,child_namespace_scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find struct that has been previous added")))));
}
TRY((((*this).typecheck_struct(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find struct that has been previous added")))));
}
TRY((((*this).typecheck_struct(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find enum that has been previous added")))));
}
TRY((((*this).typecheck_enum(record,(enum_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find enum that has been previous added")))));
}
TRY((((*this).typecheck_enum(record,(enum_id.value()),scope_id))));
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
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((parsed_namespace).functions)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction fun = (_magic_value.value());
{
(((*this).current_function_id) = TRY((((*this).find_function_in_scope(scope_id,((fun).name))))));
TRY((((*this).typecheck_function(fun,scope_id))));
(((*this).current_function_id) = JaktInternal::OptionalNone());
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedExternalTraitImplementation> _magic = ((((parsed_namespace).external_trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedExternalTraitImplementation> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedExternalTraitImplementation implementation = (_magic_value.value());
{
types::TypeId const for_type = TRY((((*this).typecheck_typename(((implementation).for_type),scope_id,JaktInternal::OptionalNone()))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *((*this).get_type(for_type));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct struct_ = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((implementation).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return String(""); }) == String("this"))){
TRY((((*this).typecheck_method(((method).parsed_function), types::StructOrEnumId { typename types::StructOrEnumId::Struct(struct_id) } ))));
}
else {
TRY((((*this).typecheck_function(((method).parsed_function),((struct_).scope_id)))));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
{
types::CheckedStruct struct_ = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((implementation).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return String(""); }) == String("this"))){
TRY((((*this).typecheck_method(((method).parsed_function), types::StructOrEnumId { typename types::StructOrEnumId::Struct(struct_id) } ))));
}
else {
TRY((((*this).typecheck_function(((method).parsed_function),((struct_).scope_id)))));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((implementation).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return String(""); }) == String("this"))){
TRY((((*this).typecheck_method(((method).parsed_function), types::StructOrEnumId { typename types::StructOrEnumId::Enum(enum_id) } ))));
}
else {
TRY((((*this).typecheck_function(((method).parsed_function),((enum_).scope_id)))));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
{
types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((implementation).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return String(""); }) == String("this"))){
TRY((((*this).typecheck_method(((method).parsed_function), types::StructOrEnumId { typename types::StructOrEnumId::Enum(enum_id) } ))));
}
else {
TRY((((*this).typecheck_function(((method).parsed_function),((enum_).scope_id)))));
}

}

}
}

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
}

}
}

}
return {};
}

ErrorOr<JaktInternal::Array<JaktInternal::Array<types::TypeId>>> typechecker::Typechecker::find_all_implementations_of_trait(types::TypeId const type_id,types::TraitId const trait_id) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<JaktInternal::Array<types::TypeId>>, ErrorOr<JaktInternal::Array<JaktInternal::Array<types::TypeId>>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Array<types::TypeId>>> __jakt_var_326; {
types::CheckedStruct const struct_ = ((*this).get_struct(struct_id));
JaktInternal::Array<JaktInternal::Array<types::TypeId>> implementations = (TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> _magic = ((((struct_).trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> ___trait_descriptor__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const jakt_____trait_descriptor__ = ___trait_descriptor__;
String const _ = ((jakt_____trait_descriptor__).get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>> const trait_descriptor = ((jakt_____trait_descriptor__).get<1>());

if (((((trait_descriptor).get<0>())).equals(trait_id))){
TRY((((implementations).push(((trait_descriptor).get<1>())))));
}
}

}
}

__jakt_var_326 = implementations; goto __jakt_label_307;

}
__jakt_label_307:; __jakt_var_326.release_value(); }));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Array<types::TypeId>>> __jakt_var_327; {
types::CheckedStruct const struct_ = ((*this).get_struct(struct_id));
JaktInternal::Array<JaktInternal::Array<types::TypeId>> implementations = (TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> _magic = ((((struct_).trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> ___trait_descriptor__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const jakt_____trait_descriptor__ = ___trait_descriptor__;
String const _ = ((jakt_____trait_descriptor__).get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>> const trait_descriptor = ((jakt_____trait_descriptor__).get<1>());

if (((((trait_descriptor).get<0>())).equals(trait_id))){
TRY((((implementations).push(((trait_descriptor).get<1>())))));
}
}

}
}

__jakt_var_327 = implementations; goto __jakt_label_308;

}
__jakt_label_308:; __jakt_var_327.release_value(); }));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Array<types::TypeId>>> __jakt_var_328; {
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::Array<JaktInternal::Array<types::TypeId>> implementations = (TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> _magic = ((((enum_).trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> ___trait_descriptor__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const jakt_____trait_descriptor__ = ___trait_descriptor__;
String const _ = ((jakt_____trait_descriptor__).get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>> const trait_descriptor = ((jakt_____trait_descriptor__).get<1>());

if (((((trait_descriptor).get<0>())).equals(trait_id))){
TRY((((implementations).push(((trait_descriptor).get<1>())))));
}
}

}
}

__jakt_var_328 = implementations; goto __jakt_label_309;

}
__jakt_label_309:; __jakt_var_328.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Array<types::TypeId>>> __jakt_var_329; {
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::Array<JaktInternal::Array<types::TypeId>> implementations = (TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> _magic = ((((enum_).trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> ___trait_descriptor__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const jakt_____trait_descriptor__ = ___trait_descriptor__;
String const _ = ((jakt_____trait_descriptor__).get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>> const trait_descriptor = ((jakt_____trait_descriptor__).get<1>());

if (((((trait_descriptor).get<0>())).equals(trait_id))){
TRY((((implementations).push(((trait_descriptor).get<1>())))));
}
}

}
}

__jakt_var_329 = implementations; goto __jakt_label_310;

}
__jakt_label_310:; __jakt_var_329.release_value(); }));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Array<types::TypeId>>> __jakt_var_330; {
if (((id).equals(trait_id))){
return ((TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({(TRY((Array<types::TypeId>::create_with({}))))})))));
}
__jakt_var_330 = (TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({})))); goto __jakt_label_311;

}
__jakt_label_311:; __jakt_var_330.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Array<types::TypeId>>> __jakt_var_331; {
if ((!(((id).equals(trait_id))))){
return ((TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({})))));
}
__jakt_var_331 = (TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({args})))); goto __jakt_label_312;

}
__jakt_label_312:; __jakt_var_331.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::substitute_typevars_in_type(types::TypeId const type_id,types::GenericInferences const generic_inferences) {
{
return (TRY((((((*this).program))->substitute_typevars_in_type(type_id,generic_inferences,((*this).current_module_id))))));
}
}

ErrorOr<types::StructId> typechecker::Typechecker::find_struct_in_prelude(String const name) const {
{
return (TRY((((((*this).program))->find_struct_in_prelude(name)))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::cast_to_underlying(NonnullRefPtr<parser::ParsedExpression> const expr,types::ScopeId const scope_id,NonnullRefPtr<parser::ParsedType> const parsed_type) {
{
NonnullRefPtr<parser::ParsedExpression> const cast_expression = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::UnaryOp>(expr, parser::UnaryOperator { typename parser::UnaryOperator::TypeCast( parser::TypeCast { typename parser::TypeCast::Infallible(parsed_type) } ) } ,((expr)->span()))));
return (TRY((((*this).typecheck_expression(cast_expression,scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone())))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_module_import(parser::ParsedModuleImport const import_,types::ScopeId const scope_id) {
{
JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> const module_names_and_spans = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = ((import_).module_name);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ImportName::Literal>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>>((TRY((Array<JaktInternal::Tuple<String,utility::Span>>::create_with({(Tuple{name, span})}))))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ImportName::Comptime>();NonnullRefPtr<parser::ParsedExpression> const& expression = __jakt_match_value.expression;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>> __jakt_var_332; {
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((interpreter::Interpreter::Interpreter::create(((*this).compiler),((*this).program),(TRY((Array<utility::Span>::create_with({})))))));
NonnullRefPtr<interpreter::InterpreterScope> eval_scope = TRY((interpreter::InterpreterScope::InterpreterScope::from_runtime_scope(scope_id,((*this).program),JaktInternal::OptionalNone())));
types::ScopeId const exec_scope = TRY((((*this).create_scope(scope_id,true,String("comptime-import")))));
interpreter::StatementResult const result = TRY((((interpreter)->execute_expression(TRY((((*this).typecheck_expression(expression,exec_scope, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone())))),eval_scope))));
__jakt_var_332 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Return>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_333; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an invalid value"),((expression)->span())))));
__jakt_var_333 = JaktInternal::OptionalNone(); goto __jakt_label_314;

}
__jakt_label_314:; __jakt_var_333; }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Yield>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_334; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an invalid value"),((expression)->span())))));
__jakt_var_334 = JaktInternal::OptionalNone(); goto __jakt_label_315;

}
__jakt_label_315:; __jakt_var_334; }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Continue>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_335; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an invalid value"),((expression)->span())))));
__jakt_var_335 = JaktInternal::OptionalNone(); goto __jakt_label_316;

}
__jakt_label_316:; __jakt_var_335; }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Break>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_336; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an invalid value"),((expression)->span())))));
__jakt_var_336 = JaktInternal::OptionalNone(); goto __jakt_label_317;

}
__jakt_label_317:; __jakt_var_336; }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Throw>();
types::Value const& error = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_337; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),TRY((String::formatted(String("this expression threw an error: {}"),error))),((expression)->span())))));
__jakt_var_337 = JaktInternal::OptionalNone(); goto __jakt_label_318;

}
__jakt_label_318:; __jakt_var_337; }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::JustValue>();
types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
String const& string = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>>((TRY((Array<JaktInternal::Tuple<String,utility::Span>>::create_with({(Tuple{string, ((value).span)})}))))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktArray>();JaktInternal::Array<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>> __jakt_var_338; {
if (((values).is_empty())){
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an empty array"),((expression)->span())))));
}
JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>> result = (TRY((Array<JaktInternal::Tuple<String,utility::Span>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
String const& string = __jakt_match_value.value;
return (TRY((((result).push((Tuple{string, ((value).span)})))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((value).span),String("this expression evaluates to an invalid value"),((value).span)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}

}
}

__jakt_var_338 = static_cast<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>>(result); goto __jakt_label_319;

}
__jakt_label_319:; __jakt_var_338.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_339; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal"),((expression)->span()),String("this expression evaluates to a non-string value"),((expression)->span())))));
__jakt_var_339 = JaktInternal::OptionalNone(); goto __jakt_label_320;

}
__jakt_label_320:; __jakt_var_339; }));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_313;

}
__jakt_label_313:; __jakt_var_332.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
if ((!(((module_names_and_spans).has_value())))){
return {};
}
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span>> module_name_and_span = JaktInternal::OptionalNone();
JaktInternal::Array<String> names = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span>> _magic = (((module_names_and_spans.value())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span> name_and_span = (_magic_value.value());
{
TRY((((names).push(((name_and_span).get<0>())))));
JaktInternal::Optional<types::LoadedModule> maybe_loaded_module = ((((*this).program))->get_loaded_module(((name_and_span).get<0>())));
if ((!(((maybe_loaded_module).has_value())))){
JaktInternal::Optional<path::Path> const maybe_file_name = TRY((((((*this).compiler))->search_for_path(((name_and_span).get<0>())))));
path::Path const file_name = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<path::Path,ErrorOr<void>>{
auto __jakt_enum_value = (((maybe_file_name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((maybe_file_name.value()));
}
else {
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY((((*this).get_root_path())))).parent())))).join(((name_and_span).get<0>())))))).replace_extension(String("jakt"))))));
}
}()))
;
if (File::exists(((file_name).to_string()))){
(module_name_and_span = name_and_span);
break;
}
}
else {
(module_name_and_span = name_and_span);
break;
}

}

}
}

if ((!(((module_name_and_span).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("No module in module set {{{}}} was found"),utility::join(names,String(", "))))),((((import_).module_name)).span())))));
return {};
}
JaktInternal::Tuple<String,utility::Span> const module_name_module_span_ = (module_name_and_span.value());
String const module_name = ((module_name_module_span_).get<0>());
utility::Span const module_span = ((module_name_module_span_).get<1>());

types::ModuleId imported_module_id = types::ModuleId(static_cast<size_t>(0ULL));
JaktInternal::Optional<types::LoadedModule> maybe_loaded_module = ((((*this).program))->get_loaded_module(module_name));
if ((!(((maybe_loaded_module).has_value())))){
JaktInternal::Optional<path::Path> const maybe_file_name = TRY((((((*this).compiler))->search_for_path(module_name))));
path::Path const file_name = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<path::Path,ErrorOr<void>>{
auto __jakt_enum_value = (((maybe_file_name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((maybe_file_name.value()));
}
else {
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY((((*this).get_root_path())))).parent())))).join(module_name))))).replace_extension(String("jakt"))))));
}
}()))
;
utility::FileId const file_id = TRY((((((*this).compiler))->get_file_id_or_register(file_name))));
JaktInternal::Optional<parser::ParsedNamespace> const parsed_namespace = TRY((((*this).lex_and_parse_file_contents(file_id))));
if ((!(((parsed_namespace).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Module '{}' not found"),module_name))),module_span))));
return {};
}
types::ModuleId const original_current_module_id = ((*this).current_module_id);
String const sanitized_module_name = TRY((((module_name).replace(String(":"),String("_")))));
(imported_module_id = TRY((((*this).create_module(sanitized_module_name,false,((file_name).to_string()))))));
TRY((((((*this).program))->set_loaded_module(sanitized_module_name,types::LoadedModule(imported_module_id,file_id)))));
(((*this).current_module_id) = imported_module_id);
types::ScopeId const imported_scope_id = TRY((((*this).create_scope(((*this).root_scope_id()),false,TRY((String::formatted(String("module({})"),sanitized_module_name)))))));
TRY((((*this).typecheck_module((parsed_namespace.value()),imported_scope_id))));
(((*this).current_module_id) = original_current_module_id);
}
else {
(imported_module_id = (((maybe_loaded_module.value())).module_id));
}

JaktInternal::Array<types::ModuleId> current_module_imports = ((((*this).current_module()))->imports);
TRY((((current_module_imports).push(imported_module_id))));
if (((((import_).import_list)).is_empty())){
JaktInternal::Dictionary<String,types::ModuleId> scope_imports = ((TRY((((*this).get_scope(scope_id)))))->imports);
String import_name = module_name;
if (((((import_).alias_name)).has_value())){
(import_name = (((((import_).alias_name).value())).literal_name()));
}
TRY((((scope_imports).set(import_name,imported_module_id))));
}
else if (((((import_).import_list)).index() == 1 /* All */)){
NonnullRefPtr<types::Scope> const import_scope = TRY((((*this).get_scope(types::ScopeId(imported_module_id,static_cast<size_t>(0ULL))))));
{
JaktInternal::DictionaryIterator<String,types::VarId> _magic = ((((import_scope)->vars)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::VarId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::VarId> name__var_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::VarId> const jakt__name__var_id__ = name__var_id__;
String const name = ((jakt__name__var_id__).get<0>());
types::VarId const var_id = ((jakt__name__var_id__).get<1>());

TRY((((*this).add_var_to_scope(scope_id,name,var_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<String,types::Value> _magic = ((((import_scope)->comptime_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::Value>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::Value> name__value__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::Value> const jakt__name__value__ = name__value__;
String const name = ((jakt__name__value__).get<0>());
types::Value const value = ((jakt__name__value__).get<1>());

TRY((((*this).add_comptime_binding_to_scope(scope_id,name,value,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<String,types::StructId> _magic = ((((import_scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::StructId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::StructId> name__struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::StructId> const jakt__name__struct_id__ = name__struct_id__;
String const name = ((jakt__name__struct_id__).get<0>());
types::StructId const struct_id = ((jakt__name__struct_id__).get<1>());

TRY((((*this).add_struct_to_scope(scope_id,name,struct_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((import_scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
String const name = ((jakt__name__function_id__).get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).get<1>());

TRY((((*this).add_function_to_scope(scope_id,name,function_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<String,types::EnumId> _magic = ((((import_scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::EnumId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::EnumId> name__enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::EnumId> const jakt__name__enum_id__ = name__enum_id__;
String const name = ((jakt__name__enum_id__).get<0>());
types::EnumId const enum_id = ((jakt__name__enum_id__).get<1>());

TRY((((*this).add_enum_to_scope(scope_id,name,enum_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<String,types::TypeId> _magic = ((((import_scope)->types)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::TypeId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::TypeId> name__type_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::TypeId> const jakt__name__type_id__ = name__type_id__;
String const name = ((jakt__name__type_id__).get<0>());
types::TypeId const type_id = ((jakt__name__type_id__).get<1>());

TRY((((*this).add_type_to_scope(scope_id,name,type_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<String,types::TraitId> _magic = ((((import_scope)->traits)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::TraitId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::TraitId> name__trait_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::TraitId> const jakt__name__trait_id__ = name__trait_id__;
String const name = ((jakt__name__trait_id__).get<0>());
types::TraitId const trait_id = ((jakt__name__trait_id__).get<1>());

TRY((((*this).add_trait_to_scope(scope_id,name,trait_id,((((import_).module_name)).span())))));
}

}
}

}
else if (((((import_).import_list)).index() == 0 /* List */)){
JaktInternal::Array<parser::ImportName> const names = (((import_).import_list).get<parser::ImportList::List>()).value;
types::ScopeId const import_scope_id = types::ScopeId(imported_module_id,static_cast<size_t>(0ULL));
{
JaktInternal::ArrayIterator<parser::ImportName> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<parser::ImportName> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ImportName imported_name = (_magic_value.value());
{
bool found = false;
JaktInternal::Optional<types::FunctionId> const maybe_function_id = TRY((((*this).find_function_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_function_id).has_value())){
(found = true);
TRY((((*this).add_function_to_scope(scope_id,((imported_name).literal_name()),(maybe_function_id.value()),((imported_name).span())))));
}
JaktInternal::Optional<types::EnumId> const maybe_enum_id = TRY((((((*this).program))->find_enum_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_enum_id).has_value())){
(found = true);
TRY((((*this).add_enum_to_scope(scope_id,((imported_name).literal_name()),(maybe_enum_id.value()),((imported_name).span())))));
}
JaktInternal::Optional<types::TypeId> const maybe_type_id = TRY((((*this).find_type_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_type_id).has_value())){
(found = true);
TRY((((*this).add_type_to_scope(scope_id,((imported_name).literal_name()),(maybe_type_id.value()),((imported_name).span())))));
}
JaktInternal::Optional<types::StructId> const maybe_struct_id = TRY((((*this).find_struct_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_struct_id).has_value())){
(found = true);
TRY((((*this).add_struct_to_scope(scope_id,((imported_name).literal_name()),(maybe_struct_id.value()),((imported_name).span())))));
}
JaktInternal::Optional<types::TraitId> const maybe_trait_id = TRY((((*this).find_trait_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_trait_id).has_value())){
(found = true);
TRY((((*this).add_trait_to_scope(scope_id,((imported_name).literal_name()),(maybe_trait_id.value()),((imported_name).span())))));
}
if ((!(found))){
TRY((((*this).error(TRY((String::formatted(String("Imported name '{}' not found in module '{}'"),((imported_name).literal_name()),module_name))),((imported_name).span())))));
}
}

}
}

}
}
return {};
}

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_binary_operation(NonnullRefPtr<types::CheckedExpression> const checked_lhs,parser::BinaryOperator const op,NonnullRefPtr<types::CheckedExpression> const checked_rhs,types::ScopeId const scope_id,utility::Span const span) {
{
types::TypeId const lhs_type_id = ((checked_lhs)->type());
types::TypeId const rhs_type_id = ((checked_rhs)->type());
utility::Span const lhs_span = ((checked_lhs)->span());
utility::Span const rhs_span = ((checked_rhs)->span());
types::TypeId type_id = ((checked_lhs)->type());
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::TypeId>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::NoneCoalescing>();
{
if (((op).index() == 32 /* NoneCoalescingAssign */)){
if (((checked_lhs)->index() == 22 /* Var */)){
types::CheckedVariable const var = (checked_lhs->get<types::CheckedExpression::Var>()).var;
utility::Span const span = (checked_lhs->get<types::CheckedExpression::Var>()).span;
if ((!(((var).is_mutable)))){
TRY((((*this).error_with_hint(String("left-hand side of ??= must be a mutable variable"),span,String("This variable isn't marked as mutable"),((var).definition_span)))));
return (types::unknown_type_id());
}
}
else {
TRY((((*this).error(String("left-hand side of ??= must be a mutable variable"),span))));
return (types::unknown_type_id());
}

}
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if (((id).equals(TRY((((*this).find_struct_in_prelude(String("Optional")))))))){
if (((lhs_type_id).equals(rhs_type_id))){
return (lhs_type_id);
}
types::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((inner_type_id).equals(rhs_type_id))){
return (inner_type_id);
}
}
else {
TRY((((*this).error_with_hint(TRY((String::formatted(String("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span,String("Left side of ?? must be an Optional but isn't"),lhs_span))));
}

}
else {
TRY((((*this).error_with_hint(TRY((String::formatted(String("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span,String("Left side of ?? must be an Optional but isn't"),lhs_span))));
}

TRY((((*this).error(TRY((String::formatted(String("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::NoneCoalescingAssign>();
{
if (((op).index() == 32 /* NoneCoalescingAssign */)){
if (((checked_lhs)->index() == 22 /* Var */)){
types::CheckedVariable const var = (checked_lhs->get<types::CheckedExpression::Var>()).var;
utility::Span const span = (checked_lhs->get<types::CheckedExpression::Var>()).span;
if ((!(((var).is_mutable)))){
TRY((((*this).error_with_hint(String("left-hand side of ??= must be a mutable variable"),span,String("This variable isn't marked as mutable"),((var).definition_span)))));
return (types::unknown_type_id());
}
}
else {
TRY((((*this).error(String("left-hand side of ??= must be a mutable variable"),span))));
return (types::unknown_type_id());
}

}
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if (((id).equals(TRY((((*this).find_struct_in_prelude(String("Optional")))))))){
if (((lhs_type_id).equals(rhs_type_id))){
return (lhs_type_id);
}
types::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((inner_type_id).equals(rhs_type_id))){
return (inner_type_id);
}
}
else {
TRY((((*this).error_with_hint(TRY((String::formatted(String("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span,String("Left side of ?? must be an Optional but isn't"),lhs_span))));
}

}
else {
TRY((((*this).error_with_hint(TRY((String::formatted(String("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span,String("Left side of ?? must be an Optional but isn't"),lhs_span))));
}

TRY((((*this).error(TRY((String::formatted(String("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::LessThan>();
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Binary comparison between incompatible types ({} vs {})"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::LessThanOrEqual>();
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Binary comparison between incompatible types ({} vs {})"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::GreaterThan>();
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Binary comparison between incompatible types ({} vs {})"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::GreaterThanOrEqual>();
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Binary comparison between incompatible types ({} vs {})"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Equal>();
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Binary comparison between incompatible types ({} vs {})"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::NotEqual>();
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Binary comparison between incompatible types ({} vs {})"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::LogicalAnd>();
{
if ((!(((lhs_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("left side of logical binary operation is not a boolean"),lhs_span))));
}
if ((!(((rhs_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("right side of logical binary operation is not a boolean"),rhs_span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::LogicalOr>();
{
if ((!(((lhs_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("left side of logical binary operation is not a boolean"),lhs_span))));
}
if ((!(((rhs_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("right side of logical binary operation is not a boolean"),rhs_span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Assign>();
{
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
return (lhs_type_id);
}
if (((checked_rhs)->index() == 23 /* OptionalNone */)){
utility::Span const span = (checked_rhs->get<types::CheckedExpression::OptionalNone>()).span;
types::TypeId const type_id = (checked_rhs->get<types::CheckedExpression::OptionalNone>()).type_id;
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if (((id).equals(TRY((((*this).find_struct_in_prelude(String("Optional")))))))){
return (lhs_type_id);
}
else if ((!(((id).equals(TRY((((*this).find_struct_in_prelude(String("WeakPtr")))))))))){
TRY((((*this).error(String("Cannot assign None to a non-optional type"),span))));
}
}
else {
TRY((((*this).error(String("Cannot assign None to a non-optional type"),span))));
}

}
NonnullRefPtr<types::Type> const lhs_type = ((*this).get_type(lhs_type_id));
if (((lhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = (lhs_type->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (lhs_type->get<types::Type::GenericInstance>()).args;
if (((((((((*this).program))->get_struct(id))).name) == String("Optional")) && ((((checked_rhs)->type())).equals(((args)[static_cast<i64>(0LL)]))))){
return (lhs_type_id);
}
if (((((((((*this).program))->get_struct(id))).name) == String("WeakPtr")) && ((((checked_rhs)->type())).equals(((args)[static_cast<i64>(0LL)]))))){
return (lhs_type_id);
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
return (((result).value_or(lhs_type_id)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::AddAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::SubtractAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::MultiplyAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::DivideAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::ModuloAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseAndAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseOrAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseXorAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseLeftShiftAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseRightShiftAssign>();
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Assignment between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(String("Assignment to immutable variable"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Add>();
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Subtract>();
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Multiply>();
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Divide>();
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Modulo>();
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
}
(type_id = lhs_type_id);
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
return (type_id);
}
}

ErrorOr<JaktInternal::Optional<types::StructId>> typechecker::Typechecker::find_struct_in_scope(types::ScopeId const scope_id,String const name) const {
{
return (TRY((((((*this).program))->find_struct_in_scope(scope_id,name)))));
}
}

ErrorOr<void> typechecker::Typechecker::check_method_access(types::ScopeId const accessor,types::ScopeId const accessee,NonnullRefPtr<types::CheckedFunction> const method,utility::Span const span) {
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((method)->visibility);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedVisibility::Private>();
{
if ((!(TRY((((*this).scope_can_access(accessor,accessee))))))){
if ((!(((((method)->type)).index() == 0 /* Normal */)))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("Can't access constructor ‘{}’, because it is marked private"),((method)->name)))),span,String("Private constructors are created if any fields are private"),span))));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Can't access method ‘{}’, because it is marked private"),((method)->name)))),span))));
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedVisibility::Restricted>();JaktInternal::Array<NonnullRefPtr<types::MaybeResolvedScope>> const& scopes = __jakt_match_value.scopes;
{
TRY((((*this).check_restricted_access(accessor,String("function"),accessee,((method)->name),scopes,span))));
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
}
return {};
}

ErrorOr<types::CheckedBlock> typechecker::Typechecker::typecheck_block(parser::ParsedBlock const parsed_block,types::ScopeId const parent_scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const yield_type_hint) {
{
bool const parent_throws = ((TRY((((*this).get_scope(parent_scope_id)))))->can_throw);
types::ScopeId const block_scope_id = TRY((((*this).create_scope(parent_scope_id,parent_throws,String("block")))));
types::CheckedBlock checked_block = types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::TypeId::none(),false);
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedStatement>> _magic = ((((parsed_block).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedStatement> parsed_statement = (_magic_value.value());
{
if ((!(((((checked_block).control_flow)).is_reachable())))){
TRY((((*this).error(String("Unreachable code"),((parsed_statement)->span())))));
}
NonnullRefPtr<types::CheckedStatement> const checked_statement = TRY((((*this).typecheck_statement(parsed_statement,block_scope_id,safety_mode,yield_type_hint))));
(((checked_block).control_flow) = ((((checked_block).control_flow)).updated(((*this).statement_control_flow(checked_statement)))));
JaktInternal::Optional<utility::Span> const yield_span = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<utility::Span>, ErrorOr<types::CheckedBlock>>{
auto&& __jakt_match_variant = *parsed_statement;
switch(__jakt_match_variant.index()) {
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Yield>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<utility::Span>>(((expr)->span())));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Guard>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<utility::Span>>(((expr)->span())));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
));
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const checked_yield_expression = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>>, ErrorOr<types::CheckedBlock>>{
auto&& __jakt_match_variant = *checked_statement;
switch(__jakt_match_variant.index()) {
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Yield>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>>>(expr));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
));
if ((((yield_span).has_value()) && ((checked_yield_expression).has_value()))){
types::TypeId const type_var_type_id = (((checked_yield_expression.value()))->type());
types::TypeId const type_ = TRY((((*this).resolve_type_var(type_var_type_id,block_scope_id))));
if ((((checked_yield_expression.value()))->index() == 23 /* OptionalNone */)){
(((checked_block).yielded_none) = true);
}
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).check_types_for_compat(((((checked_block).yielded_type)).value()),type_,((((*this).generic_inferences))),((yield_span).value())))));
}
else {
(((checked_block).yielded_type) = static_cast<JaktInternal::Optional<types::TypeId>>(type_));
}

}
TRY((((((checked_block).statements)).push(checked_statement))));
}

}
}

if (((((checked_block).yielded_type)).has_value())){
(((checked_block).yielded_type) = static_cast<JaktInternal::Optional<types::TypeId>>(TRY((((*this).substitute_typevars_in_type(((((checked_block).yielded_type)).value()),((*this).generic_inferences)))))));
}
return (checked_block);
}
}

ErrorOr<JaktInternal::Optional<types::TypeId>> typechecker::Typechecker::find_type_in_scope(types::ScopeId const scope_id,String const name) const {
{
types::ScopeId current = scope_id;
for (;;){
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(current))));
JaktInternal::Optional<types::TypeId> const maybe_type = ((((scope)->types)).get(name));
if (((maybe_type).has_value())){
return (maybe_type);
}
{
JaktInternal::ArrayIterator<types::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<types::ScopeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ScopeId child_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((*this).get_scope(child_id))));
if ((!(((((child_scope)->namespace_name)).has_value())))){
JaktInternal::Optional<types::TypeId> const maybe_type = ((((child_scope)->types)).get(name));
if (((maybe_type).has_value())){
return (maybe_type);
}
}
}

}
}

if (((((scope)->parent)).has_value())){
(current = ((((scope)->parent)).value()));
}
else {
break;
}

}
return (JaktInternal::OptionalNone());
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_function(parser::ParsedFunction const parsed_function,types::ScopeId const parent_scope_id) {
{
if (((!(((((parsed_function).generic_parameters)).is_empty()))) && (!(((parsed_function).must_instantiate))))){
return {};
}
JaktInternal::Optional<types::FunctionId> const function_id = TRY((((*this).find_function_in_scope(parent_scope_id,((parsed_function).name)))));
if ((!(((function_id).has_value())))){
TRY((((((*this).compiler))->panic(String("Internal error: missing previously defined function")))));
}
if ((((parsed_function).name) == String("main"))){
TRY((((*this).typecheck_jakt_main(parsed_function))));
}
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function((function_id.value())));
types::ScopeId const function_scope_id = ((checked_function)->function_scope_id);
parser::FunctionLinkage const function_linkage = ((checked_function)->linkage);
JaktInternal::Array<types::CheckedVariable> param_vars = (TRY((Array<types::CheckedVariable>::create_with({}))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
types::CheckedVariable const variable = ((param).variable);
TRY((((param_vars).push(variable))));
types::VarId const var_id = TRY((((module)->add_variable(variable))));
TRY((((*this).add_var_to_scope(function_scope_id,((variable).name),var_id,((variable).definition_span)))));
}

}
}

types::TypeId function_return_type_id = TRY((((*this).typecheck_typename(((parsed_function).return_type),function_scope_id,JaktInternal::OptionalNone()))));
if (((!(((parsed_function).is_fat_arrow))) && (((((parsed_function).return_type))->index() == 13 /* Empty */) && (((parsed_function).name) != String("main"))))){
(function_return_type_id = types::void_type_id());
}
(((checked_function)->return_type_id) = function_return_type_id);
if (((function_return_type_id).equals(types::never_type_id()))){
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(function_scope_id))));
(((scope)->can_throw) = true);
}
types::CheckedBlock const block = TRY((((*this).typecheck_block(((parsed_function).block),function_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
if (((((block).yielded_type)).has_value())){
TRY((((*this).error_with_hint(String("Functions are not allowed to yield values"),(((((parsed_function).block)).find_yield_span()).value()),String("You might want to return instead"),(((((parsed_function).block)).find_yield_keyword_span()).value())))));
}
(function_return_type_id = TRY((((*this).typecheck_typename(((parsed_function).return_type),function_scope_id,JaktInternal::OptionalNone())))));
types::TypeId const UNKNOWN_TYPE_ID = types::unknown_type_id();
types::TypeId const VOID_TYPE_ID = types::void_type_id();
types::TypeId return_type_id = VOID_TYPE_ID;
if (((function_return_type_id).equals(UNKNOWN_TYPE_ID))){
(return_type_id = ((*this).infer_function_return_type(block)));
}
else {
(return_type_id = TRY((((*this).resolve_type_var(function_return_type_id,function_scope_id)))));
}

bool const external_linkage = ((function_linkage).index() == 1 /* External */);
if (((!(external_linkage)) && ((!(((return_type_id).equals(VOID_TYPE_ID)))) && (!(((((block).control_flow)).always_transfers_control())))))){
if ((((return_type_id).equals(types::never_type_id())) && (!(((((block).control_flow)).never_returns()))))){
TRY((((*this).error(String("Control reaches end of never-returning function"),((parsed_function).name_span)))));
}
else if ((!(((((block).control_flow)).never_returns())))){
TRY((((*this).error(String("Control reaches end of non-void function"),((parsed_function).name_span)))));
}
}
(((checked_function)->block) = block);
(((checked_function)->return_type_id) = return_type_id);
}
return {};
}

ErrorOr<void> typechecker::Typechecker::check_type_argument_requirements(types::TypeId const generic_argument,JaktInternal::Array<types::TraitId> const constraints,utility::Span const arg_span) {
{
if ((!(((constraints).is_empty())))){
JaktInternal::Tuple<JaktInternal::Dictionary<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>,utility::Span> const implemented_traits_decl_span_ = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::Dictionary<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>,utility::Span>, ErrorOr<void>>{
auto&& __jakt_match_variant = *((*this).get_type(generic_argument));
switch(__jakt_match_variant.index()) {
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue((Tuple{((((*this).get_enum(id))).trait_implementations), ((((*this).get_enum(id))).name_span)}));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{((((*this).get_enum(id))).trait_implementations), ((((*this).get_enum(id))).name_span)}));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue((Tuple{((((*this).get_struct(id))).trait_implementations), ((((*this).get_struct(id))).name_span)}));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{((((*this).get_struct(id))).trait_implementations), ((((*this).get_struct(id))).name_span)}));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((String::formatted(String("Cannot use ‘{}’ here as only enums, structs and classes can implement the required traits"),TRY((((*this).type_name(generic_argument))))))),arg_span))));
{
return ErrorOr<void>{};
}

abort();
}
};/*case end*/
}/*switch end*/
}()
));
JaktInternal::Dictionary<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const implemented_traits = ((implemented_traits_decl_span_).get<0>());
utility::Span const decl_span = ((implemented_traits_decl_span_).get<1>());

{
JaktInternal::ArrayIterator<types::TraitId> _magic = ((constraints).iterator());
for (;;){
JaktInternal::Optional<types::TraitId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TraitId constraint = (_magic_value.value());
{
String const trait_name = ((((((*this).program))->get_trait(constraint)))->name);
JaktInternal::Optional<JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const implemented_trait = ((implemented_traits).get(trait_name));
if (((!(((implemented_trait).has_value()))) || (!((((((implemented_trait.value())).get<0>())).equals(constraint)))))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("Cannot use ‘{}’ here as it doesn't implement the trait ‘{}’"),TRY((((*this).type_name(generic_argument)))),trait_name))),arg_span,String("Consider implementing the required trait for this type"),decl_span))));
}
}

}
}

}
else {
return {};
}

}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_inline_cpp(parser::ParsedBlock const block,utility::Span const span,types::SafetyMode const safety_mode) {
{
if (((safety_mode).index() == 0 /* Safe */)){
TRY((((*this).error(String("Use of inline cpp block outside of unsafe block"),span))));
}
JaktInternal::Array<String> strings = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedStatement>> _magic = ((((block).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedStatement> statement = (_magic_value.value());
{
if (((statement)->index() == 0 /* Expression */)){
NonnullRefPtr<parser::ParsedExpression> const expr = (statement->get<parser::ParsedStatement::Expression>()).expr;
if (((expr)->index() == 2 /* QuotedString */)){
String const val = (expr->get<parser::ParsedExpression::QuotedString>()).val;
utility::Span const span = (expr->get<parser::ParsedExpression::QuotedString>()).span;
TRY((((strings).push(val))));
}
else {
TRY((((*this).error(String("Expected block of strings"),span))));
}

}
else {
TRY((((*this).error(String("Expected block of strings"),span))));
}

}

}
}

return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::InlineCpp>(strings,span))));
}
}

ErrorOr<bool> typechecker::Typechecker::check_restricted_access(types::ScopeId const accessor,String const accessee_kind,types::ScopeId const accessee,String const name,JaktInternal::Array<NonnullRefPtr<types::MaybeResolvedScope>> const whitelist,utility::Span const span) {
{
types::ScopeId const most_specific_active_scope_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId,ErrorOr<bool>>{
auto __jakt_enum_value = (((((*this).current_function_id)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((((*this).get_function((((*this).current_function_id).value()))))->function_scope_id));
}
else {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_340; {
if ((!(((((*this).current_struct_type_id)).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Can't access {0} ‘{1}’ from this global scope, because ‘{1}’ restricts access to it"),accessee_kind,name))),span))));
return (false);
}
__jakt_var_340 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId, ErrorOr<bool>>{
auto&& __jakt_match_variant = *((*this).get_type((((*this).current_struct_type_id).value())));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_struct(id))).scope_id));
};/*case end*/
default: {
{
utility::panic(TRY((String::formatted(String("Internal error: current_struct_type_id is not a struct"),span))));
}
};/*case end*/
}/*switch end*/
}()
)); goto __jakt_label_321;

}
__jakt_label_321:; __jakt_var_340.release_value(); }));
}
}()))
;
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::MaybeResolvedScope>> _magic = ((whitelist).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::MaybeResolvedScope>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::MaybeResolvedScope> scope = (_magic_value.value());
{
NonnullRefPtr<types::MaybeResolvedScope> const resolved_scope = TRY((((scope)->try_resolve(((*this).program)))));
if (((resolved_scope)->index() == 0 /* Resolved */)){
types::ScopeId const scope_id = (resolved_scope->get<types::MaybeResolvedScope::Resolved>()).value;
if (TRY((((*this).scope_can_access(most_specific_active_scope_id,scope_id))))){
return (true);
}
}
else {
continue;
}

}

}
}

NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(most_specific_active_scope_id))));
TRY((((*this).error(TRY((String::formatted(String("Cannot access {} ‘{}’ from this scope"),accessee_kind,name))),span))));
return (false);
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_throw(NonnullRefPtr<parser::ParsedExpression> const expr,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const error_type_id = TRY((((*this).find_type_in_prelude(String("Error")))));
if ((!(((((checked_expr)->type())).equals(error_type_id))))){
TRY((((*this).error(String("throw expression does not produce an error"),((expr)->span())))));
}
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
if ((!(((scope)->can_throw)))){
TRY((((*this).error(String("Throw statement needs to be in a try statement or a function marked as throws"),((expr)->span())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Throw>(checked_expr,span))));
}
}

ErrorOr<JaktInternal::Array<types::StructId>> typechecker::Typechecker::struct_inheritance_chain(types::StructId const struct_id) const {
{
JaktInternal::Array<types::StructId> chain = (TRY((Array<types::StructId>::create_with({}))));
JaktInternal::Optional<types::StructId> current = static_cast<JaktInternal::Optional<types::StructId>>(struct_id);
TRY((((chain).push((current.value())))));
while (((current).has_value())){
JaktInternal::Optional<types::StructId> const parent = ((((*this).get_struct((current.value())))).super_struct_id);
if (((parent).has_value())){
TRY((((chain).push((parent.value())))));
}
(current = parent);
}
JaktInternal::Array<types::StructId> reverse_chain = (TRY((Array<types::StructId>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((chain).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((reverse_chain).push(((chain)[(JaktInternal::checked_sub<size_t>((JaktInternal::checked_sub<size_t>(((chain).size()),static_cast<size_t>(1ULL))),i))])))));
}

}
}

return (reverse_chain);
}
}

ErrorOr<bool> typechecker::Typechecker::add_function_to_scope(types::ScopeId const parent_scope_id,String const name,types::FunctionId const function_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(parent_scope_id))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> existing_function = (_magic_value.value());
{
if ((name == ((existing_function).get<0>()))){
NonnullRefPtr<types::CheckedFunction> const function_ = ((*this).get_function(((existing_function).get<1>())));
TRY((((*this).error_with_hint(TRY((String::formatted(String("Redefinition of function ‘{}’"),name))),span,String("previous definition here"),((function_)->name_span)))));
return (false);
}
}

}
}

TRY((((((scope)->functions)).set(name,function_id))));
return (true);
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_while(NonnullRefPtr<parser::ParsedExpression> const condition,parser::ParsedBlock const block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<types::CheckedExpression> const checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("Condition must be a boolean expression"),((condition)->span())))));
}
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(String("A ‘while’ block is not allowed to yield values"),(((block).find_yield_span()).value())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::While>(checked_condition,checked_block,span))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_expression_and_dereference_if_needed(NonnullRefPtr<parser::ParsedExpression> const expr,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint,utility::Span const span) {
{
NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,type_hint))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((checked_expr)->type())));
switch(__jakt_match_variant.index()) {
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
{
(checked_expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Dereference() } ,span,type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
{
(checked_expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Dereference() } ,span,type_id))));
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
return (checked_expr);
}
}

ErrorOr<path::Path> typechecker::Typechecker::get_root_path() const {
{
JaktInternal::Optional<types::LoadedModule> const root_module = ((((*this).program))->get_loaded_module(String("Root Module")));
if (((root_module).has_value())){
utility::FileId const file_id = (((root_module.value())).file_id);
return ((TRY((((((*this).compiler))->get_file_path(file_id)))).value()));
}
return (TRY((path::Path::Path::from_string(String(".")))));
}
}

ErrorOr<bool> typechecker::Typechecker::scope_can_access(types::ScopeId const accessor,types::ScopeId const accessee) const {
{
if (((accessor).equals(accessee))){
return (true);
}
NonnullRefPtr<types::Scope> accessor_scope = TRY((((*this).get_scope(accessor))));
while (((((accessor_scope)->parent)).has_value())){
types::ScopeId const parent = (((accessor_scope)->parent).value());
if (((parent).equals(accessee))){
return (true);
}
(accessor_scope = TRY((((*this).get_scope(parent)))));
}
return (false);
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_fields(parser::ParsedRecord const record,types::StructId const struct_id) {
{
types::CheckedStruct structure = ((*this).get_struct(struct_id));
types::ScopeId const checked_struct_scope_id = ((((*this).get_struct(struct_id))).scope_id);
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
JaktInternal::Array<parser::ParsedField> const parsed_fields = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<parser::ParsedField>, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();JaktInternal::Array<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();JaktInternal::Array<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(String("typecheck_struct_fields cannot handle non-structs")))));
}
};/*case end*/
}/*switch end*/
}()
));
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((parsed_fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField unchecked_member = (_magic_value.value());
{
parser::ParsedVarDecl const parsed_var_decl = ((unchecked_member).var_decl);
types::TypeId const checked_member_type = TRY((((*this).typecheck_typename(((parsed_var_decl).parsed_type),checked_struct_scope_id,((parsed_var_decl).name)))));
TRY((((*this).check_that_type_doesnt_contain_reference(checked_member_type,((((parsed_var_decl).parsed_type))->span())))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const variable_id = TRY((((module)->add_variable(types::CheckedVariable(((parsed_var_decl).name),checked_member_type,((parsed_var_decl).is_mutable),((parsed_var_decl).span),JaktInternal::OptionalNone(),TRY((((*this).typecheck_visibility(((unchecked_member).visibility),checked_struct_scope_id)))))))));
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> default_value = JaktInternal::OptionalNone();
if (((((unchecked_member).default_value)).has_value())){
(default_value = TRY((((*this).typecheck_expression((((unchecked_member).default_value).value()),checked_struct_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone())))));
}
TRY((((((structure).fields)).push(types::CheckedField(variable_id,default_value)))));
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_expression(NonnullRefPtr<parser::ParsedExpression> const expr,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedStruct>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
String const& field_name = __jakt_match_value.field_name;
utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_indexed_struct(expr,field_name,scope_id,is_optional,safety_mode,span)))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Boolean>();bool const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Boolean>(val,span))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::NumericConstant>();parser::NumericConstant const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_341; {
JaktInternal::Optional<types::TypeId> type_hint_unwrapped = type_hint;
if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
types::StructId const id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
if (((id).equals(optional_struct_id))){
(type_hint_unwrapped = ((args)[static_cast<i64>(0LL)]));
}
}
__jakt_var_341 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::I8>();
i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::I16>();
i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::I32>();
i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::I64>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } )))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::U8>();
u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::U16>();
u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::U32>();
u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::U64>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::USize>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::F32>();
f32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::F32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::F32() } )))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::F64>();
f64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::F64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::F64() } )))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::UnknownSigned>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).infer_signed_int(val,span,type_hint_unwrapped)))));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::UnknownUnsigned>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).infer_unsigned_int(val,span,type_hint_unwrapped)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_322;

}
__jakt_label_322:; __jakt_var_341.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::SingleQuotedString>();String const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::CharacterConstant>(val,span))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::SingleQuotedByteString>();String const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::ByteConstant>(val,span))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::QuotedString>();String const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_342; {
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
TRY((((*this).unify_with_type(types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ),type_hint,span))));
__jakt_var_342 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::QuotedString>(val,span))); goto __jakt_label_323;

}
__jakt_label_323:; __jakt_var_342.release_value(); }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Call>();parser::ParsedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_343; {
__jakt_var_343 = TRY((((*this).typecheck_call(call,scope_id,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),safety_mode,type_hint,false)))); goto __jakt_label_324;

}
__jakt_label_324:; __jakt_var_343.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::MethodCall>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::ParsedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_344; {
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const checked_expr_type_id = ((checked_expr)->type());
bool found_optional = false;
JaktInternal::Optional<types::StructOrEnumId> const parent_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructOrEnumId>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(checked_expr_type_id));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructOrEnumId>>( types::StructOrEnumId { typename types::StructOrEnumId::Struct(id) } ));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructOrEnumId>>( types::StructOrEnumId { typename types::StructOrEnumId::Enum(id) } ));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::JaktString>();
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructOrEnumId>>( types::StructOrEnumId { typename types::StructOrEnumId::Struct(TRY((((*this).find_struct_in_prelude(String("String")))))) } ));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::StructOrEnumId>> __jakt_var_345; {
__jakt_var_345 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructOrEnumId>,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::StructOrEnumId>> __jakt_var_346; {
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
JaktInternal::Optional<types::StructOrEnumId> struct_id = JaktInternal::OptionalNone();
if ((!(((id).equals(optional_struct_id))))){
TRY((((*this).error(TRY((String::formatted(String("Can't use ‘{}’ as an optional type in optional chained call"),((((*this).get_struct(id))).name)))),span))));
}
else {
(found_optional = true);
(struct_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructOrEnumId>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((args)[static_cast<i64>(0LL)])));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::StructOrEnumId { typename types::StructOrEnumId::Struct(struct_id) } );
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue( types::StructOrEnumId { typename types::StructOrEnumId::Struct(struct_id) } );
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::StructOrEnumId { typename types::StructOrEnumId::Enum(id) } );
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue( types::StructOrEnumId { typename types::StructOrEnumId::Enum(id) } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::StructOrEnumId> __jakt_var_347; {
TRY((((*this).error(String("Can't use non-struct type as an optional type in optional chained call"),span))));
(found_optional = false);
__jakt_var_347 =  types::StructOrEnumId { typename types::StructOrEnumId::Struct(optional_struct_id) } ; goto __jakt_label_328;

}
__jakt_label_328:; __jakt_var_347.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
}

__jakt_var_346 = static_cast<JaktInternal::Optional<types::StructOrEnumId>>(struct_id.value_or_lazy_evaluated([&] { return  types::StructOrEnumId { typename types::StructOrEnumId::Struct(optional_struct_id) } ; })); goto __jakt_label_327;

}
__jakt_label_327:; __jakt_var_346.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructOrEnumId>>( types::StructOrEnumId { typename types::StructOrEnumId::Struct(id) } ));
}
}()))
; goto __jakt_label_326;

}
__jakt_label_326:; __jakt_var_345.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructOrEnumId>>( types::StructOrEnumId { typename types::StructOrEnumId::Enum(id) } ));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::StructOrEnumId>> __jakt_var_348; {
TRY((((*this).error(TRY((String::formatted(String("no methods available on value (type: {})"),TRY((((*this).type_name(checked_expr_type_id))))))),((checked_expr)->span())))));
JaktInternal::Optional<types::StructOrEnumId> const none = JaktInternal::OptionalNone();
__jakt_var_348 = none; goto __jakt_label_329;

}
__jakt_label_329:; __jakt_var_348.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
if ((is_optional && (!(found_optional)))){
TRY((((*this).error(TRY((String::formatted(String("Optional chain mismatch: expected optional chain, found {}"),TRY((((*this).type_name(checked_expr_type_id))))))),((checked_expr)->span())))));
}
NonnullRefPtr<types::CheckedExpression> const checked_call_expr = TRY((((*this).typecheck_call(call,scope_id,span,checked_expr,parent_id,safety_mode,type_hint,false))));
types::TypeId const type_id = ((checked_call_expr)->type());
__jakt_var_344 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_call_expr;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_349; {
types::TypeId result_type = ((call).return_type);
if (is_optional){
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
(result_type = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({result_type}))))))))))));
}
__jakt_var_349 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::MethodCall>(checked_expr,call,span,is_optional,result_type))); goto __jakt_label_330;

}
__jakt_label_330:; __jakt_var_349.release_value(); }));
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(String("typecheck_call should return `CheckedExpression::Call()`")))));
}
};/*case end*/
}/*switch end*/
}()
)); goto __jakt_label_325;

}
__jakt_label_325:; __jakt_var_344.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Range>();JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const& to = __jakt_match_value.to;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_350; {
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_from = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> from_type = JaktInternal::OptionalNone();
utility::Span from_span = span;
if ((((from).has_value()) && ((!((((from.value()))->index() == 1 /* NumericConstant */))) && (!((((from.value()))->index() == 1 /* NumericConstant */)))))){
(checked_from = TRY((((*this).typecheck_expression((from.value()),scope_id,safety_mode,JaktInternal::OptionalNone())))));
(from_type = (((checked_from.value()))->type()));
(from_span = (((checked_from.value()))->span()));
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_to = JaktInternal::OptionalNone();
types::TypeId to_type = types::unknown_type_id();
utility::Span to_span = span;
if (((to).has_value())){
(checked_to = TRY((((*this).typecheck_expression((to.value()),scope_id,safety_mode,from_type)))));
(to_type = (((checked_to.value()))->type()));
(to_span = (((checked_to.value()))->span()));
}
if ((((from).has_value()) && ((((from.value()))->index() == 1 /* NumericConstant */) || (((from.value()))->index() == 1 /* NumericConstant */)))){
(checked_from = TRY((((*this).typecheck_expression((from.value()),scope_id,safety_mode,to_type)))));
(from_type = (((checked_from.value()))->type()));
(from_span = (((checked_from.value()))->span()));
}
JaktInternal::Optional<types::TypeId> values_type_id = JaktInternal::OptionalNone();
if ((((from).has_value()) && ((to).has_value()))){
(values_type_id = TRY((((*this).unify((from_type.value()),from_span,to_type,from_span)))));
if ((!(((values_type_id).has_value())))){
TRY((((*this).error(String("Range values differ in types"),span))));
}
}
else if (((from).has_value())){
(values_type_id = from_type);
}
else if (((to).has_value())){
(values_type_id = to_type);
}
types::StructId const range_struct_id = TRY((((*this).find_struct_in_prelude(String("Range")))));
NonnullRefPtr<types::Type> const range_type = TRY((types::Type::template create<typename types::Type::GenericInstance>(range_struct_id,(TRY((Array<types::TypeId>::create_with({((values_type_id).value_or(types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } )))})))))));
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(range_type))));
__jakt_var_350 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Range>(checked_from,checked_to,span,type_id))); goto __jakt_label_331;

}
__jakt_label_331:; __jakt_var_350.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::UnaryOp>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::UnaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_351; {
NonnullRefPtr<types::CheckedExpression> const checked_expr = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::Dereference>();
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone())))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)))));
};/*case end*/
}/*switch end*/
}()
));
types::CheckedUnaryOperator const checked_op = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedUnaryOperator, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::PreIncrement>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::PreIncrement() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::PostIncrement>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::PostIncrement() } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::PreDecrement>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::PreDecrement() } );
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::PostDecrement>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::PostDecrement() } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::Negate>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::Dereference>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Dereference() } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::RawAddress>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::RawAddress() } );
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::Reference>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Reference() } );
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::MutableReference>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::MutableReference() } );
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::LogicalNot>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::LogicalNot() } );
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::BitwiseNot>();
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::BitwiseNot() } );
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::TypeCast>();
parser::TypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedUnaryOperator> __jakt_var_352; {
types::TypeId const type_id = TRY((((*this).typecheck_typename(((cast).parsed_type()),scope_id,JaktInternal::OptionalNone()))));
types::CheckedTypeCast const checked_cast = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedTypeCast, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::TypeCast::Fallible>();
return JaktInternal::ExplicitValue(({ Optional<types::CheckedTypeCast> __jakt_var_353; {
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
NonnullRefPtr<types::Type> const optional_type = TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({type_id})))))));
types::TypeId const optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
__jakt_var_353 =  types::CheckedTypeCast { typename types::CheckedTypeCast::Fallible(optional_type_id) } ; goto __jakt_label_334;

}
__jakt_label_334:; __jakt_var_353.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::TypeCast::Infallible>();
return JaktInternal::ExplicitValue( types::CheckedTypeCast { typename types::CheckedTypeCast::Infallible(type_id) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
__jakt_var_352 =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::TypeCast(checked_cast) } ; goto __jakt_label_333;

}
__jakt_label_333:; __jakt_var_352.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::Is>();
NonnullRefPtr<parser::ParsedType> const& unchecked_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedUnaryOperator> __jakt_var_354; {
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::TypeId const type_id = TRY((((*this).typecheck_typename(unchecked_type,scope_id,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
types::CheckedUnaryOperator operator_is =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Is(type_id) } ;
if (((unchecked_type)->index() == 0 /* Name */)){
String const name = (unchecked_type->get<parser::ParsedType::Name>()).name;
types::TypeId const expr_type_id = ((checked_expr)->type());
if (((((*this).get_type(expr_type_id)))->index() == 24 /* Enum */)){
types::EnumId const enum_id = (((*this).get_type(expr_type_id))->get<types::Type::Enum>()).value;
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
bool exists = false;
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
(exists = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((var_name == name));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((var_name == name));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((var_name == name));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
}/*switch end*/
}()
)));
if (exists){
(operator_is =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::IsEnumVariant(variant,(TRY((Array<types::CheckedEnumVariantBinding>::create_with({})))),expr_type_id) } );
break;
}
}

}
}

if (((!(exists)) && ((type_id).equals(types::unknown_type_id())))){
TRY((((*this).error(TRY((String::formatted(String("Enum variant {} does not exist on {}"),name,TRY((((*this).type_name(expr_type_id))))))),span))));
}
}
else if (((type_id).equals(types::unknown_type_id()))){
TRY((((*this).error(TRY((String::formatted(String("Unknown type or invalid type name: {}"),name))),span))));
}
}
else {
TRY((((*this).error(String("The right-hand side of an `is` operator must be a type name or enum variant"),span))));
}

__jakt_var_354 = operator_is; goto __jakt_label_335;

}
__jakt_label_335:; __jakt_var_354.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::UnaryOperator::IsEnumVariant>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& bindings = __jakt_match_value.bindings;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_is_enum_variant(checked_expr,inner,bindings,scope_id)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
__jakt_var_351 = TRY((((*this).typecheck_unary_operation(checked_expr,checked_op,span,scope_id,safety_mode)))); goto __jakt_label_332;

}
__jakt_label_332:; __jakt_var_351.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::BinaryOp>();NonnullRefPtr<parser::ParsedExpression> const& lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<parser::ParsedExpression> const& rhs = __jakt_match_value.rhs;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_355; {
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_lhs = JaktInternal::OptionalNone();
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_rhs = JaktInternal::OptionalNone();
if ((((lhs)->index() == 1 /* NumericConstant */) || ((lhs)->index() == 1 /* NumericConstant */))){
(checked_rhs = TRY((((*this).typecheck_expression_and_dereference_if_needed(rhs,scope_id,safety_mode,JaktInternal::OptionalNone(),span)))));
types::TypeId const hint = (((checked_rhs.value()))->type());
(checked_lhs = TRY((((*this).typecheck_expression_and_dereference_if_needed(lhs,scope_id,safety_mode,hint,span)))));
}
else {
(checked_lhs = TRY((((*this).typecheck_expression_and_dereference_if_needed(lhs,scope_id,safety_mode,JaktInternal::OptionalNone(),span)))));
types::TypeId const hint = (((checked_lhs.value()))->type());
(checked_rhs = TRY((((*this).typecheck_expression_and_dereference_if_needed(rhs,scope_id,safety_mode,hint,span)))));
}

types::TypeId const output_type = TRY((((*this).typecheck_binary_operation((checked_lhs.value()),op,(checked_rhs.value()),scope_id,span))));
__jakt_var_355 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::BinaryOp>((checked_lhs.value()),op,(checked_rhs.value()),span,output_type))); goto __jakt_label_336;

}
__jakt_label_336:; __jakt_var_355.release_value(); }));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedExpression::OptionalNone>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_356; {
JaktInternal::Optional<types::TypeId> type_hint_unwrapped = type_hint;
if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
types::StructId const id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
if (((id).equals(optional_struct_id))){
(type_hint_unwrapped = ((args)[static_cast<i64>(0LL)]));
}
}
__jakt_var_356 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::OptionalNone>(span,type_hint_unwrapped.value_or_lazy_evaluated([&] { return types::unknown_type_id(); })))); goto __jakt_label_337;

}
__jakt_label_337:; __jakt_var_356.release_value(); }));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::OptionalSome>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_357; {
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::TypeId const type_id = ((checked_expr)->type());
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
NonnullRefPtr<types::Type> const optional_type = TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({type_id})))))));
types::TypeId const optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
__jakt_var_357 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::OptionalSome>(checked_expr,span,optional_type_id))); goto __jakt_label_338;

}
__jakt_label_338:; __jakt_var_357.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Var>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::Optional<types::CheckedVariable> const var = TRY((((*this).find_var_in_scope(scope_id,name))));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = (((var).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Var>((var.value()),span))));
}
else {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_358; {
TRY((((*this).error(TRY((String::formatted(String("Variable '{}' not found"),name))),span))));
__jakt_var_358 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Var>(types::CheckedVariable(name,((type_hint).value_or(types::unknown_type_id())),false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ),span))); goto __jakt_label_339;

}
__jakt_label_339:; __jakt_var_358.release_value(); }));
}
}()))
);
}
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::ForcedUnwrap>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_359; {
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
NonnullRefPtr<types::Type> const type = ((*this).get_type(((checked_expr)->type())));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
types::StructId const weakptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
types::TypeId const type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_360; {
types::TypeId inner_type_id = types::unknown_type_id();
if ((((id).equals(optional_struct_id)) || ((id).equals(weakptr_struct_id)))){
(inner_type_id = ((args)[static_cast<i64>(0LL)]));
}
else {
TRY((((*this).error(String("Forced unwrap only works on Optional"),span))));
}

__jakt_var_360 = inner_type_id; goto __jakt_label_341;

}
__jakt_label_341:; __jakt_var_360.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_361; {
TRY((((*this).error(String("Forced unwrap only works on Optional"),span))));
__jakt_var_361 = types::unknown_type_id(); goto __jakt_label_342;

}
__jakt_label_342:; __jakt_var_361.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
__jakt_var_359 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::ForcedUnwrap>(checked_expr,span,type_id))); goto __jakt_label_340;

}
__jakt_label_340:; __jakt_var_359.release_value(); }));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::JaktArray>();JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> const& values = __jakt_match_value.values;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const& fill_size = __jakt_match_value.fill_size;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_array(scope_id,values,fill_size,span,safety_mode,type_hint)))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::JaktTuple>();JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> const& values = __jakt_match_value.values;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_362; {
types::TypeId const VOID_TYPE_ID = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> checked_values = (TRY((Array<NonnullRefPtr<types::CheckedExpression>>::create_with({}))));
JaktInternal::Array<types::TypeId> checked_types = (TRY((Array<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedExpression>> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedExpression> value = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::TypeId const type_id = ((checked_value)->type());
if (((type_id).equals(VOID_TYPE_ID))){
TRY((((*this).error(String("Cannot create a tuple that contains a value of type void"),((value)->span())))));
}
TRY((((checked_types).push(type_id))));
TRY((((checked_values).push(checked_value))));
}

}
}

types::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude(String("Tuple")))));
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(tuple_struct_id,checked_types)))))));
if (((type_hint).has_value())){
TRY((((*this).check_types_for_compat((type_hint.value()),type_id,((((*this).generic_inferences))),span))));
}
__jakt_var_362 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::JaktTuple>(checked_values,span,type_id))); goto __jakt_label_343;

}
__jakt_label_343:; __jakt_var_362.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedExpression>();NonnullRefPtr<parser::ParsedExpression> const& base = __jakt_match_value.base;
NonnullRefPtr<parser::ParsedExpression> const& index = __jakt_match_value.index;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_363; {
NonnullRefPtr<types::CheckedExpression> const checked_base = TRY((((*this).typecheck_expression_and_dereference_if_needed(base,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
NonnullRefPtr<types::CheckedExpression> const checked_index = TRY((((*this).typecheck_expression_and_dereference_if_needed(index,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
__jakt_var_363 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((checked_base)->type())));
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_364; {
types::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(String("Array")))));
types::StructId const array_slice_struct_id = TRY((((*this).find_struct_in_prelude(String("ArraySlice")))));
types::StructId const dictionary_struct_id = TRY((((*this).find_struct_in_prelude(String("Dictionary")))));
NonnullRefPtr<types::CheckedExpression> result = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Garbage>(span)));
if ((((id).equals(array_struct_id)) || ((id).equals(array_slice_struct_id)))){
if ((((*this).is_integer(((checked_index)->type()))) || ((checked_index)->index() == 8 /* Range */))){
types::TypeId const type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_index;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Range>();return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_365; {
types::StructId const array_slice_struct_id = TRY((((*this).find_struct_in_prelude(String("ArraySlice")))));
__jakt_var_365 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(array_slice_struct_id,args))))))); goto __jakt_label_346;

}
__jakt_label_346:; __jakt_var_365.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
}/*switch end*/
}()
));
(result = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedExpression>(checked_base,checked_index,span,type_id))));
}
else {
TRY((((*this).error(String("Index must be an integer or a range"),span))));
}

}
else if (((id).equals(dictionary_struct_id))){
(result = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedDictionary>(checked_base,checked_index,span,((args)[static_cast<i64>(1LL)])))));
}
__jakt_var_364 = result; goto __jakt_label_345;

}
__jakt_label_345:; __jakt_var_364.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_366; {
TRY((((*this).error(String("Index used on value that cannot be indexed"),span))));
__jakt_var_366 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Garbage>(span))); goto __jakt_label_347;

}
__jakt_label_347:; __jakt_var_366.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)); goto __jakt_label_344;

}
__jakt_label_344:; __jakt_var_363.release_value(); }));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedTuple>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_367; {
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude(String("Tuple")))));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
types::TypeId expr_type_id = types::unknown_type_id();
if (((((*this).get_type(((checked_expr)->type()))))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(((checked_expr)->type())))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(((checked_expr)->type())))->get<types::Type::GenericInstance>()).args;
if (((id).equals(tuple_struct_id))){
if (is_optional){
TRY((((*this).error(String("Optional chaining is not allowed on a non-optional tuple type"),span))));
}
if ((index >= ((args).size()))){
TRY((((*this).error(String("Tuple index past the end of the tuple"),span))));
}
else {
(expr_type_id = ((args)[index]));
}

}
else if ((is_optional && ((id).equals(optional_struct_id)))){
types::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((((*this).get_type(inner_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type(inner_type_id))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type(inner_type_id))->get<types::Type::GenericInstance>()).args;
if (((id).equals(tuple_struct_id))){
if ((index >= ((args).size()))){
TRY((((*this).error(String("Optional-chained tuple index past the end of the tuple"),span))));
}
else {
(expr_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({((args)[index])}))))))))))));
}

}
}
else {
TRY((((*this).error(String("Optional-chained tuple index used on non-tuple value"),span))));
}

}
}
else if (is_optional){
TRY((((*this).error(String("Optional-chained tuple index used on non-tuple value"),span))));
}
else {
TRY((((*this).error(String("Tuple index used on non-tuple value"),span))));
}

__jakt_var_367 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedTuple>(checked_expr,index,span,is_optional,expr_type_id))); goto __jakt_label_348;

}
__jakt_label_348:; __jakt_var_367.release_value(); }));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedExpression::Garbage>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Garbage>(span))));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::NamespacedVar>();String const& name = __jakt_match_value.name;
JaktInternal::Array<String> const& namespace_ = __jakt_match_value.namespace_;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_namespaced_var_or_simple_enum_constructor_call(name,namespace_,scope_id,safety_mode,type_hint,span)))));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Match>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Array<parser::ParsedMatchCase> const& cases = __jakt_match_value.cases;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_match(expr,cases,marker_span,scope_id,safety_mode,type_hint)))));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::EnumVariantArg>();NonnullRefPtr<parser::ParsedExpression> const& inner_expr = __jakt_match_value.expr;
parser::EnumVariantPatternArgument const& arg = __jakt_match_value.arg;
NonnullRefPtr<parser::ParsedType> const& enum_variant = __jakt_match_value.enum_variant;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_368; {
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(inner_expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::CheckedEnumVariantBinding checked_binding = types::CheckedEnumVariantBinding(String(""),String(""),types::unknown_type_id(),span);
JaktInternal::Optional<types::CheckedEnumVariant> checked_enum_variant = JaktInternal::OptionalNone();
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *enum_variant;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::NamespacedName>();String const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((checked_expr)->type())));
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::Optional<types::CheckedEnumVariant> const variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
(checked_enum_variant = variant);
JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>> const checked_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),(TRY((Array<parser::EnumVariantPatternArgument>::create_with({arg})))),span))));
if (((checked_bindings).has_value())){
JaktInternal::Array<types::CheckedEnumVariantBinding> const bindings = (checked_bindings.value());
(checked_binding = ((bindings)[static_cast<i64>(0LL)]));
}
}
else {
TRY((((*this).error(TRY((String::formatted(String("Enum variant {} does not exist"),variant_name))),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((String::formatted(String("Unknown type or invalid type name: {}"),variant_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();String const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((checked_expr)->type())));
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::Optional<types::CheckedEnumVariant> const variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
(checked_enum_variant = variant);
JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>> const checked_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),(TRY((Array<parser::EnumVariantPatternArgument>::create_with({arg})))),span))));
if (((checked_bindings).has_value())){
JaktInternal::Array<types::CheckedEnumVariantBinding> const bindings = (checked_bindings.value());
(checked_binding = ((bindings)[static_cast<i64>(0LL)]));
}
}
else {
TRY((((*this).error(TRY((String::formatted(String("Enum variant {} does not exist"),variant_name))),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((String::formatted(String("Unknown type or invalid type name: {}"),variant_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
))), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
NonnullRefPtr<types::CheckedExpression> output = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Garbage>(span)));
if (((checked_enum_variant).has_value())){
(output = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::EnumVariantArg>(checked_expr,checked_binding,(checked_enum_variant.value()),span))));
}
__jakt_var_368 = output; goto __jakt_label_349;

}
__jakt_label_349:; __jakt_var_368.release_value(); }));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::JaktDictionary>();JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>>> const& values = __jakt_match_value.values;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_dictionary(values,span,scope_id,safety_mode,type_hint)))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Set>();JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> const& values = __jakt_match_value.values;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_set(values,span,scope_id,safety_mode,type_hint)))));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Function>();JaktInternal::Array<parser::ParsedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::Array<parser::ParsedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
bool const& is_fat_arrow = __jakt_match_value.is_fat_arrow;
NonnullRefPtr<parser::ParsedType> const& return_type = __jakt_match_value.return_type;
parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_lambda(captures,params,can_throw,is_fat_arrow,return_type,block,span,scope_id,safety_mode)))));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Try>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<parser::ParsedBlock> const& catch_block = __jakt_match_value.catch_block;
JaktInternal::Optional<String> const& catch_name = __jakt_match_value.catch_name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_try(expr,catch_block,catch_name,scope_id,safety_mode,span,type_hint)))));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::TryBlock>();NonnullRefPtr<parser::ParsedStatement> const& stmt = __jakt_match_value.stmt;
parser::ParsedBlock const& catch_block = __jakt_match_value.catch_block;
String const& error_name = __jakt_match_value.error_name;
utility::Span const& error_span = __jakt_match_value.error_span;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_try_block(stmt,error_name,error_span,catch_block,scope_id,safety_mode,span)))));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Operator>();{
TRY((((((*this).compiler))->panic(String("idk how to handle this thing")))));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<void> typechecker::Typechecker::dump_type_hint(types::TypeId const type_id,utility::Span const span) const {
{
outln(String("{{\"type\":\"hint\",\"file_id\":{},\"position\":{},\"typename\":\"{}\"}}"),((((span).file_id)).id),((span).end),TRY((((*this).type_name(type_id)))));
}
return {};
}

typechecker::Typechecker::Typechecker(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, types::ModuleId a_current_module_id, JaktInternal::Optional<types::TypeId> a_current_struct_type_id, JaktInternal::Optional<types::FunctionId> a_current_function_id, bool a_inside_defer, size_t a_checkidx, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, types::GenericInferences a_generic_inferences) :compiler(a_compiler), program(a_program), current_module_id(a_current_module_id), current_struct_type_id(a_current_struct_type_id), current_function_id(a_current_function_id), inside_defer(a_inside_defer), checkidx(a_checkidx), ignore_errors(a_ignore_errors), dump_type_hints(a_dump_type_hints), dump_try_hints(a_dump_try_hints), lambda_count(a_lambda_count), generic_inferences(a_generic_inferences){}

ErrorOr<types::TypeId> typechecker::Typechecker::resolve_type_var(types::TypeId const type_var_type_id,types::ScopeId const scope_id) const {
{
types::TypeId current_type_id = type_var_type_id;
for (;;){
NonnullRefPtr<types::Type> const type_var_type = ((*this).get_type(current_type_id));
if (((type_var_type)->index() == 18 /* TypeVariable */)){
String const type_name = (type_var_type->get<types::Type::TypeVariable>()).value;
JaktInternal::Optional<types::TypeId> const maybe_found_type_id = TRY((((*this).find_type_in_scope(scope_id,type_name))));
if (((maybe_found_type_id).has_value())){
types::TypeId const found_type_id = ((maybe_found_type_id).value());
if (((found_type_id).equals(current_type_id))){
return (current_type_id);
}
(current_type_id = found_type_id);
}
else {
return (current_type_id);
}

}
else {
return (current_type_id);
}

}
return (current_type_id);
}
}

bool typechecker::Typechecker::is_subclass_of(types::TypeId const ancestor_type_id,types::TypeId const child_type_id) const {
{
NonnullRefPtr<types::Type> const ancestor_type = ((*this).get_type(ancestor_type_id));
NonnullRefPtr<types::Type> const child_type = ((*this).get_type(child_type_id));
if (((ancestor_type)->index() == 23 /* Struct */)){
types::StructId const ancestor_struct_id = (ancestor_type->get<types::Type::Struct>()).value;
if (((child_type)->index() == 23 /* Struct */)){
types::StructId const child_struct_id = (child_type->get<types::Type::Struct>()).value;
types::CheckedStruct ancestor_struct = ((*this).get_struct(ancestor_struct_id));
types::StructId current_struct_id = child_struct_id;
for (;;){
types::CheckedStruct const current_struct = ((*this).get_struct(current_struct_id));
if (((((current_struct).super_struct_id)).has_value())){
if (((ancestor_struct_id).equals((((current_struct).super_struct_id).value())))){
return (true);
}
(current_struct_id = (((current_struct).super_struct_id).value()));
}
else {
return (false);
}

}
return (false);
}
else {
return (false);
}

}
else {
return (false);
}

}
}

ErrorOr<types::ModuleId> typechecker::Typechecker::create_module(String const name,bool const is_root,JaktInternal::Optional<String> const path) {
{
size_t const new_id = ((((((*this).program))->modules)).size());
types::ModuleId const module_id = types::ModuleId(new_id);
NonnullRefPtr<types::Module> const module = TRY((types::Module::create(module_id,name,(TRY((Array<NonnullRefPtr<types::CheckedFunction>>::create_with({})))),(TRY((Array<types::CheckedStruct>::create_with({})))),(TRY((Array<types::CheckedEnum>::create_with({})))),(TRY((Array<NonnullRefPtr<types::Scope>>::create_with({})))),(TRY((Array<NonnullRefPtr<types::Type>>::create_with({TRY((types::Type::template create<typename types::Type::Void>())), TRY((types::Type::template create<typename types::Type::Bool>())), TRY((types::Type::template create<typename types::Type::U8>())), TRY((types::Type::template create<typename types::Type::U16>())), TRY((types::Type::template create<typename types::Type::U32>())), TRY((types::Type::template create<typename types::Type::U64>())), TRY((types::Type::template create<typename types::Type::I8>())), TRY((types::Type::template create<typename types::Type::I16>())), TRY((types::Type::template create<typename types::Type::I32>())), TRY((types::Type::template create<typename types::Type::I64>())), TRY((types::Type::template create<typename types::Type::F32>())), TRY((types::Type::template create<typename types::Type::F64>())), TRY((types::Type::template create<typename types::Type::Usize>())), TRY((types::Type::template create<typename types::Type::JaktString>())), TRY((types::Type::template create<typename types::Type::CChar>())), TRY((types::Type::template create<typename types::Type::CInt>())), TRY((types::Type::template create<typename types::Type::Unknown>())), TRY((types::Type::template create<typename types::Type::Never>()))})))),(TRY((Array<NonnullRefPtr<types::CheckedTrait>>::create_with({})))),(TRY((Array<types::CheckedVariable>::create_with({})))),(TRY((Array<types::ModuleId>::create_with({})))),path.value_or_lazy_evaluated([&] { return (((((((*this).compiler))->current_file_path()).value())).to_string()); }),is_root)));
TRY((((((((*this).program))->modules)).push(module))));
return (module_id);
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_block_statement(parser::ParsedBlock const parsed_block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(parsed_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(String("A block used as a statement cannot yield values, as the value cannot be observed in any way"),(((parsed_block).find_yield_span()).value())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Block>(checked_block,span))));
}
}

ErrorOr<JaktInternal::Optional<types::FieldRecord>> typechecker::Typechecker::lookup_struct_field(types::StructId const struct_id,String const name) const {
{
JaktInternal::Array<types::StructId> chain = (TRY((Array<types::StructId>::create_with({}))));
JaktInternal::Optional<types::StructId> current = static_cast<JaktInternal::Optional<types::StructId>>(struct_id);
TRY((((chain).push((current.value())))));
while (((current).has_value())){
JaktInternal::Optional<types::StructId> const parent = ((((*this).get_struct((current.value())))).super_struct_id);
if (((parent).has_value())){
TRY((((chain).push((parent.value())))));
}
(current = parent);
}
{
JaktInternal::ArrayIterator<types::StructId> _magic = ((chain).iterator());
for (;;){
JaktInternal::Optional<types::StructId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::StructId current_struct_id = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((((*this).get_struct(current_struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const variable = ((*this).get_variable(((field).variable_id)));
if ((((variable).name) == name)){
return (types::FieldRecord(current_struct_id,((field).variable_id)));
}
}

}
}

}

}
}

return (JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>>> typechecker::Typechecker::expand_context_for_bindings(NonnullRefPtr<parser::ParsedExpression> const condition,JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const acc,JaktInternal::Optional<parser::ParsedBlock> const then_block,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const else_statement,utility::Span const span) {
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>>>>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.index()) {
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::BinaryOp>();NonnullRefPtr<parser::ParsedExpression> const& lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<parser::ParsedExpression> const& rhs = __jakt_match_value.rhs;
{
if (((op).index() == 18 /* LogicalAnd */)){
JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>> const rhs_condition_rhs_then_block_rhs_else_statement_ = TRY((((*this).expand_context_for_bindings(rhs,acc,then_block,else_statement,span))));
NonnullRefPtr<parser::ParsedExpression> const rhs_condition = ((rhs_condition_rhs_then_block_rhs_else_statement_).get<0>());
JaktInternal::Optional<parser::ParsedBlock> const rhs_then_block = ((rhs_condition_rhs_then_block_rhs_else_statement_).get<1>());
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const rhs_else_statement = ((rhs_condition_rhs_then_block_rhs_else_statement_).get<2>());

NonnullRefPtr<parser::ParsedExpression> accumulated_condition = rhs_condition;
return (TRY((((*this).expand_context_for_bindings(lhs,accumulated_condition,rhs_then_block,rhs_else_statement,span)))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::UnaryOp>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::UnaryOperator const& op = __jakt_match_value.op;
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::UnaryOperator::IsEnumVariant>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& bindings = __jakt_match_value.bindings;
{
NonnullRefPtr<parser::ParsedExpression> const unary_op_single_condition = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::UnaryOp>(expr, parser::UnaryOperator { typename parser::UnaryOperator::Is(inner) } ,span)));
JaktInternal::Array<NonnullRefPtr<parser::ParsedStatement>> outer_if_stmts = (TRY((Array<NonnullRefPtr<parser::ParsedStatement>>::create_with({}))));
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((bindings).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument binding = (_magic_value.value());
{
parser::ParsedVarDecl const var = parser::ParsedVarDecl(((binding).binding),TRY((parser::ParsedType::template create<typename parser::ParsedType::Empty>())),false,JaktInternal::OptionalNone(),((binding).span));
NonnullRefPtr<parser::ParsedExpression> const enum_variant_arg = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::EnumVariantArg>(expr,binding,inner,span)));
TRY((((outer_if_stmts).push(TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::VarDecl>(var,enum_variant_arg,span)))))));
}

}
}

NonnullRefPtr<parser::ParsedExpression> inner_condition = condition;
if (((then_block).has_value())){
if (((acc).has_value())){
(inner_condition = (acc.value()));
TRY((((outer_if_stmts).push(TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::If>(inner_condition,(then_block.value()),else_statement,span)))))));
}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedStatement>> _magic = (((((then_block.value())).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedStatement> stmt = (_magic_value.value());
{
TRY((((outer_if_stmts).push(stmt))));
}

}
}

}

}
parser::ParsedBlock const new_then_block = parser::ParsedBlock(outer_if_stmts);
return (TRY((((*this).expand_context_for_bindings(unary_op_single_condition,JaktInternal::OptionalNone(),new_then_block,else_statement,span)))));
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
NonnullRefPtr<parser::ParsedExpression> base_condition = condition;
if (((acc).has_value())){
(base_condition = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::BinaryOp>(condition, parser::BinaryOperator { typename parser::BinaryOperator::LogicalAnd() } ,(acc.value()),span))));
}
return ((Tuple{base_condition, then_block, else_statement}));
}
}

ErrorOr<JaktInternal::Optional<types::TypeId>> typechecker::Typechecker::unify(types::TypeId const lhs,utility::Span const lhs_span,types::TypeId const rhs,utility::Span const rhs_span) {
{
if ((!(TRY((((*this).check_types_for_compat(lhs,rhs,((((*this).generic_inferences))),lhs_span))))))){
return (JaktInternal::OptionalNone());
}
return (TRY((((*this).substitute_typevars_in_type(lhs,((*this).generic_inferences))))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::find_type_in_prelude(String const name) const {
{
types::ScopeId const scope_id = ((*this).prelude_scope_id());
JaktInternal::Optional<types::TypeId> const type_id = TRY((((*this).find_type_in_scope(scope_id,name))));
if (((type_id).has_value())){
return (((type_id).value()));
}
TRY((((((*this).compiler))->panic(TRY((String::formatted(String("internal error: {} builtin definition not found"),name)))))));
}
}

bool typechecker::Typechecker::is_numeric(types::TypeId const type_id) const {
{
return (((((*this).program))->is_numeric(type_id)));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_array(types::ScopeId const scope_id,JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> const values,JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const fill_size,utility::Span const span,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
if ((!(((TRY((((*this).get_scope(scope_id)))))->can_throw)))){
String const message = String("Array initialization inside non-throwing scope");
if (((((*this).current_function_id)).has_value())){
NonnullRefPtr<types::CheckedFunction> const current_function = ((*this).get_function((((*this).current_function_id).value())));
TRY((((*this).error_with_hint(message,span,TRY((String::formatted(String("Add `throws` keyword to function {}"),((current_function)->name)))),((current_function)->name_span)))));
}
else {
TRY((((*this).error(message,span))));
}

}
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> repeat = JaktInternal::OptionalNone();
if (((fill_size).has_value())){
NonnullRefPtr<parser::ParsedExpression> const fill_size_value = ((fill_size).value());
NonnullRefPtr<types::CheckedExpression> const fill_size_checked = TRY((((*this).typecheck_expression_and_dereference_if_needed(fill_size_value,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const fill_size_type = ((fill_size_checked)->type());
if ((!(((*this).is_integer(fill_size_type))))){
TRY((((*this).error(TRY((String::formatted(String("Type '{}' is not convertible to an integer. Only integer values can be array fill size expressions."),TRY((((*this).type_name(fill_size_type))))))),((fill_size_value)->span())))));
}
(repeat = fill_size_checked);
}
types::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(String("Array")))));
types::TypeId inner_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> inferred_type_span = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> inner_hint = JaktInternal::OptionalNone();
if (((type_hint).has_value())){
if (((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */)){
types::StructId const id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
if (((id).equals(array_struct_id))){
(inner_hint = static_cast<JaktInternal::Optional<types::TypeId>>(((args)[static_cast<i64>(0LL)])));
}
}
}
JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> vals = (TRY((Array<NonnullRefPtr<types::CheckedExpression>>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedExpression>> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedExpression> value = (_magic_value.value());
{
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,inner_hint))));
types::TypeId const current_value_type_id = ((checked_expr)->type());
if (((current_value_type_id).equals(types::void_type_id()))){
TRY((((*this).error(String("Cannot create an array with values of type void\n"),span))));
}
if (((inner_type_id).equals(types::unknown_type_id()))){
(inner_type_id = current_value_type_id);
(inferred_type_span = ((value)->span()));
}
else if ((!(((inner_type_id).equals(current_value_type_id))))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("Type '{}' does not match type '{}' of previous values in array"),TRY((((*this).type_name(current_value_type_id)))),TRY((((*this).type_name(inner_type_id))))))),((value)->span()),TRY((String::formatted(String("Array was inferred to store type '{}' here"),TRY((((*this).type_name(inner_type_id))))))),(inferred_type_span.value())))));
}
TRY((((vals).push(checked_expr))));
}

}
}

if (((inner_type_id).equals(types::unknown_type_id()))){
if (((inner_hint).has_value())){
(inner_type_id = (inner_hint.value()));
}
else if ((((type_hint).has_value()) && (((type_hint.value())).equals(types::unknown_type_id())))){
TRY((((*this).error(String("Cannot infer generic type for Array<T>"),span))));
}
}
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(array_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id})))))))))));
if (((type_hint).has_value())){
TRY((((*this).check_types_for_compat((type_hint.value()),type_id,((((*this).generic_inferences))),span))));
}
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::JaktArray>(vals,repeat,span,type_id,inner_type_id))));
}
}

ErrorOr<bool> typechecker::Typechecker::add_var_to_scope(types::ScopeId const scope_id,String const name,types::VarId const var_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
{
JaktInternal::DictionaryIterator<String,types::VarId> _magic = ((((scope)->vars)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::VarId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::VarId> existing_var = (_magic_value.value());
{
if ((name == ((existing_var).get<0>()))){
types::CheckedVariable const variable_ = ((*this).get_variable(((existing_var).get<1>())));
TRY((((*this).error_with_hint(TRY((String::formatted(String("Redefinition of variable ‘{}’"),name))),span,String("previous definition here"),((variable_).definition_span)))));
}
}

}
}

TRY((((((scope)->vars)).set(name,var_id))));
return (true);
}
}

ErrorOr<NonnullRefPtr<types::Scope>> typechecker::Typechecker::get_scope(types::ScopeId const id) const {
{
return (TRY((((((*this).program))->get_scope(id)))));
}
}

ErrorOr<bool> typechecker::Typechecker::check_types_for_compat(types::TypeId const lhs_type_id,types::TypeId const rhs_type_id,types::GenericInferences& generic_inferences,utility::Span const span) {
{
if (((((lhs_type_id).equals(rhs_type_id)) || ((lhs_type_id).equals(types::unknown_type_id()))) || ((rhs_type_id).equals(types::unknown_type_id())))){
return (true);
}
NonnullRefPtr<types::Type> const lhs_type = ((*this).get_type(lhs_type_id));
NonnullRefPtr<types::Type> const rhs_type = ((*this).get_type(rhs_type_id));
String const lhs_type_id_string = TRY((((lhs_type_id).to_string())));
String const rhs_type_id_string = TRY((((rhs_type_id).to_string())));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
types::StructId const weakptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
types::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(String("Array")))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *lhs_type;
switch(__jakt_match_variant.index()) {
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
{
JaktInternal::Optional<String> seen_type_id_string = ((((generic_inferences))).get(lhs_type_id_string));
if (((seen_type_id_string).has_value())){
types::TypeId const seen_type_id = TRY((types::TypeId::TypeId::from_string((seen_type_id_string.value()))));
if (((((*this).get_type(seen_type_id)))->index() == 18 /* TypeVariable */)){
return (TRY((((*this).check_types_for_compat(seen_type_id,lhs_type_id,generic_inferences,span)))));
}
if ((((seen_type_id_string).value()) != rhs_type_id_string)){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(seen_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
}
else {
TRY((((((generic_inferences))).set(lhs_type_id_string,rhs_type_id_string))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& lhs_enum_id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs_type)->index() == 20 /* GenericEnumInstance */)){
types::EnumId const rhs_enum_id = (rhs_type->get<types::Type::GenericEnumInstance>()).id;
JaktInternal::Array<types::TypeId> const rhs_args = (rhs_type->get<types::Type::GenericEnumInstance>()).args;
if (((lhs_enum_id).equals(rhs_enum_id))){
types::CheckedEnum const lhs_enum = ((*this).get_enum(lhs_enum_id));
if ((((lhs_args).size()) == ((rhs_args).size()))){
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((lhs_args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((lhs_args)[idx]),((rhs_args)[idx]),generic_inferences,span))))))){
return (false);
}
(++(idx));
}
}
else {
TRY((((*this).error(TRY((String::formatted(String("mismatched number of generic parameters for {}"),((lhs_enum).name)))),span))));
return (false);
}

}
}
else {
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::Array<types::TypeId> const& lhs_params = __jakt_match_value.params;
bool const& lhs_can_throw = __jakt_match_value.can_throw;
types::TypeId const& lhs_return_type_id = __jakt_match_value.return_type_id;
{
if (((rhs_type)->index() == 29 /* Function */)){
JaktInternal::Array<types::TypeId> const rhs_params = (rhs_type->get<types::Type::Function>()).params;
bool const rhs_can_throw = (rhs_type->get<types::Type::Function>()).can_throw;
types::TypeId const rhs_return_type_id = (rhs_type->get<types::Type::Function>()).return_type_id;
if ((!((lhs_can_throw == rhs_can_throw)))){
String const lhs_throw = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<bool>>{
auto __jakt_enum_value = (lhs_can_throw);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("Yes"));
}
else {
return JaktInternal::ExplicitValue(String("No"));
}
}()))
;
String const rhs_throw = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<bool>>{
auto __jakt_enum_value = (rhs_can_throw);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("Yes"));
}
else {
return JaktInternal::ExplicitValue(String("No"));
}
}()))
;
TRY((((*this).error(TRY((String::formatted(String("Function can throw mismatch: expected ‘{}’, but got ‘{}’"),lhs_throw,rhs_throw))),span))));
}
if ((!((((lhs_params).size()) == ((rhs_params).size()))))){
TRY((((*this).error(TRY((String::formatted(String("Function parameter count mismatch: expected ‘{}’, but got ‘{}’"),((lhs_params).size()),((rhs_params).size())))),span))));
return (false);
}
if ((!(TRY((((*this).check_types_for_compat(lhs_return_type_id,rhs_return_type_id,generic_inferences,span))))))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("Function type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span,TRY((String::formatted(String("The return types differ: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_return_type_id)))),TRY((((*this).type_name(rhs_return_type_id))))))),span))));
return (false);
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((lhs_params).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(TRY((((*this).check_types_for_compat(((lhs_params)[i]),((rhs_params)[i]),generic_inferences,span))))))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("Function type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span,TRY((String::formatted(String("The parameter types differ at argument {}: expected ‘{}’, but got ‘{}’"),(JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))),TRY((((*this).type_name(((lhs_params)[i]))))),TRY((((*this).type_name(((rhs_params)[i])))))))),span))));
return (false);
}
}

}
}

}
else {
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
{
types::StructId const lhs_struct_id = id;
JaktInternal::Array<types::TypeId> const lhs_args = args;
if ((((lhs_struct_id).equals(optional_struct_id)) || ((lhs_struct_id).equals(weakptr_struct_id)))){
if ((((lhs_args).size()) > static_cast<size_t>(0ULL))){
if (((((lhs_args)[static_cast<i64>(0LL)])).equals(rhs_type_id))){
return (true);
}
}
}
if (((rhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = (rhs_type->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (rhs_type->get<types::Type::GenericInstance>()).args;
types::StructId const rhs_struct_id = id;
if (((lhs_struct_id).equals(rhs_struct_id))){
JaktInternal::Array<types::TypeId> const rhs_args = args;
types::CheckedStruct const lhs_struct = ((*this).get_struct(lhs_struct_id));
if ((((lhs_args).size()) == ((rhs_args).size()))){
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((lhs_args)[idx]),((rhs_args)[idx]),generic_inferences,span))))))){
return (false);
}
(++(idx));
}
}
else {
TRY((((*this).error(TRY((String::formatted(String("mismatched number of generic parameters for {}"),((lhs_struct).name)))),span))));
return (false);
}

}
else if (((lhs_struct_id).equals(array_struct_id))){
types::TypeId const array_value_type_id = ((args)[static_cast<i64>(0LL)]);
if (((array_value_type_id).equals(types::unknown_type_id()))){
return (true);
}
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
else {
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}

}
else {
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
if (((lhs_type_id).equals(rhs_type_id))){
return (true);
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *rhs_type;
switch(__jakt_match_variant.index()) {
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
{
if (((enum_id).equals(id))){
types::CheckedEnum const lhs_enum = ((*this).get_enum(enum_id));
if ((((args).size()) != ((((lhs_enum).generic_parameters)).size()))){
TRY((((*this).error(TRY((String::formatted(String("mismatched number of generic parameters for {}"),((lhs_enum).name)))),span))));
return (false);
}
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((((((lhs_enum).generic_parameters))[idx])).type_id),((args)[idx]),generic_inferences,span))))))){
return (false);
}
(++(idx));
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
{
JaktInternal::Optional<String> const seen_type_id_string = ((((generic_inferences))).get(rhs_type_id_string));
if (((seen_type_id_string).has_value())){
if ((((seen_type_id_string).value()) != lhs_type_id_string)){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(TRY((types::TypeId::TypeId::from_string(((seen_type_id_string).value()))))))))))),span))));
return (false);
}
}
else {
TRY((((((generic_inferences))).set(lhs_type_id_string,rhs_type_id_string))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& lhs_struct_id = __jakt_match_value.value;
{
if (((lhs_type_id).equals(rhs_type_id))){
return (true);
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *rhs_type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
{
if ((!(((lhs_struct_id).equals(id))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
types::CheckedStruct const lhs_struct = ((*this).get_struct(lhs_struct_id));
if ((((args).size()) != ((((lhs_struct).generic_parameters)).size()))){
TRY((((*this).error(TRY((String::formatted(String("mismatched number of generic parameters for {}"),((lhs_struct).name)))),span))));
return (false);
}
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((((((lhs_struct).generic_parameters))[idx])).type_id),((args)[idx]),generic_inferences,span))))))){
return (false);
}
(++(idx));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
{
JaktInternal::Optional<String> const seen_type_id_string = ((((generic_inferences))).get(rhs_type_id_string));
if (((seen_type_id_string).has_value())){
if ((((seen_type_id_string).value()) != lhs_type_id_string)){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(TRY((types::TypeId::TypeId::from_string(((seen_type_id_string).value())))))))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
}
else {
TRY((((((generic_inferences))).set(lhs_type_id_string,rhs_type_id_string))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
NonnullRefPtr<types::Type> const rhs_type = ((*this).get_type(rhs_type_id));
if (((*this).is_subclass_of(lhs_type_id,rhs_type_id))){
return (true);
}
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& lhs_rawptr_type_id = __jakt_match_value.value;
{
if (((lhs_rawptr_type_id).equals(rhs_type_id))){
return (true);
}
if (((rhs_type)->index() == 25 /* RawPtr */)){
types::TypeId const rhs_rawptr_type_id = (rhs_type->get<types::Type::RawPtr>()).value;
if ((!(TRY((((*this).check_types_for_compat(lhs_rawptr_type_id,rhs_rawptr_type_id,generic_inferences,span))))))){
return (false);
}
}
else {
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& lhs_inner_type_id = __jakt_match_value.value;
{
if (((rhs_type)->index() == 27 /* Reference */)){
types::TypeId const rhs_inner_type_id = (rhs_type->get<types::Type::Reference>()).value;
if ((!(TRY((((*this).check_types_for_compat(lhs_inner_type_id,rhs_inner_type_id,generic_inferences,span))))))){
return (false);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
if ((((((generic_inferences))).map(rhs_type_id_string)) != ((((generic_inferences))).map(lhs_type_id_string)))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),span))));
return (false);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
return (true);
}
}

ErrorOr<JaktInternal::Optional<types::CheckedVariable>> typechecker::Typechecker::find_var_in_scope(types::ScopeId const scope_id,String const var) const {
{
return (TRY((((((*this).program))->find_var_in_scope(scope_id,var)))));
}
}

types::CheckedStruct typechecker::Typechecker::get_struct(types::StructId const id) const {
{
return (((((*this).program))->get_struct(id)));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_lambda(JaktInternal::Array<parser::ParsedCapture> const captures,JaktInternal::Array<parser::ParsedParameter> const params,bool const can_throw,bool const is_fat_arrow,NonnullRefPtr<parser::ParsedType> const return_type,parser::ParsedBlock const block,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode) {
{
NonnullRefPtr<parser::ParsedType> const synthetic_type = TRY((parser::ParsedType::template create<typename parser::ParsedType::Function>(params,can_throw,return_type,span)));
JaktInternal::Dictionary<String,String> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_369([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
types::TypeId type_id = TRY((((*this).typecheck_typename(synthetic_type,scope_id,JaktInternal::OptionalNone()))));
JaktInternal::Tuple<types::TypeId,types::FunctionId> return_type_id_pseudo_function_id_ = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<types::TypeId,types::FunctionId>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();types::TypeId const& return_type_id = __jakt_match_value.return_type_id;
types::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue((Tuple{return_type_id, pseudo_function_id}));
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(String("Expected the just-checked function to be of a function type")))));
}
};/*case end*/
}/*switch end*/
}()
));
types::TypeId return_type_id = ((return_type_id_pseudo_function_id_).get<0>());
types::FunctionId pseudo_function_id = ((return_type_id_pseudo_function_id_).get<1>());

types::ScopeId const lambda_scope_id = TRY((((*this).create_scope(scope_id,can_throw,String("lambda")))));
JaktInternal::Array<types::CheckedCapture> checked_captures = (TRY((Array<types::CheckedCapture>::create_with({}))));
{
JaktInternal::ArrayIterator<parser::ParsedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedCapture> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedCapture capture = (_magic_value.value());
{
if (((TRY((((*this).find_var_in_scope(scope_id,((capture).name())))))).has_value())){
TRY((((checked_captures).push(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedCapture, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = capture;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedCapture::ByValue>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue( types::CheckedCapture { typename types::CheckedCapture::ByValue(name,span) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedCapture::ByReference>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue( types::CheckedCapture { typename types::CheckedCapture::ByReference(name,span) } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedCapture::ByMutableReference>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue( types::CheckedCapture { typename types::CheckedCapture::ByMutableReference(name,span) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
))))));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Variable '{}' not found"),((capture).name())))),span))));
}

}

}
}

NonnullRefPtr<types::Module> module = ((*this).current_module());
JaktInternal::Array<types::CheckedParameter> checked_params = (TRY((Array<types::CheckedParameter>::create_with({}))));
bool first = true;
{
JaktInternal::ArrayIterator<parser::ParsedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedParameter param = (_magic_value.value());
{
types::CheckedParameter const checked_param = TRY((((*this).typecheck_parameter(param,scope_id,first,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
TRY((((checked_params).push(checked_param))));
types::VarId const var_id = TRY((((module)->add_variable(((checked_param).variable)))));
TRY((((*this).add_var_to_scope(lambda_scope_id,((((checked_param).variable)).name),var_id,((((checked_param).variable)).definition_span)))));
(first = false);
}

}
}

JaktInternal::Optional<types::FunctionId> const previous_function_id = ((*this).current_function_id);
(((*this).current_function_id) = pseudo_function_id);
ScopeGuard __jakt_var_370([&] {
{
(((*this).current_function_id) = previous_function_id);
}

});
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(block,lambda_scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((return_type_id).equals(types::unknown_type_id()))){
bool return_type_updated = false;
if (((!(is_fat_arrow)) && ((return_type)->index() == 13 /* Empty */))){
(return_type_id = types::void_type_id());
(return_type_updated = true);
}
else if ((is_fat_arrow && ((!(((((checked_block).statements)).is_empty()))) && (((((((checked_block).statements)).last()).value()))->index() == 8 /* Return */)))){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const val = ((((((checked_block).statements)).last()).value())->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
(return_type_id = TRY((((*this).resolve_type_var((((val.value()))->type()),lambda_scope_id)))));
(return_type_updated = true);
}
}
if (return_type_updated){
(type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::Array<types::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
types::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Function>(params,can_throw,return_type_id,pseudo_function_id))))))));
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(String("Expected the just-checked function to be of a function type")))));
}
};/*case end*/
}/*switch end*/
}()
)));
}
}
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Function>(checked_captures,checked_params,can_throw,return_type_id,checked_block,span,type_id,pseudo_function_id))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_try(NonnullRefPtr<parser::ParsedExpression> const expr,JaktInternal::Optional<parser::ParsedBlock> const catch_block,JaktInternal::Optional<String> const catch_name,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span,JaktInternal::Optional<types::TypeId> const type_hint) {
{
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,type_hint))));
types::StructId const error_struct_id = TRY((((*this).find_struct_in_prelude(String("Error")))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
JaktInternal::Optional<types::CheckedBlock> checked_catch_block = JaktInternal::OptionalNone();
types::TypeId const expression_type_id = ((checked_expr)->type());
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
NonnullRefPtr<types::Type> const optional_type = TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({expression_type_id})))))));
types::TypeId const optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
types::TypeId type_id = optional_type_id;
if (((catch_block).has_value())){
types::ScopeId const catch_scope_id = TRY((((*this).create_scope(scope_id,true,String("catch")))));
if (((catch_name).has_value())){
types::StructId const error_struct_id = TRY((((*this).find_struct_in_prelude(String("Error")))));
types::CheckedVariable const error_decl = types::CheckedVariable((catch_name.value()),((((*this).get_struct(error_struct_id))).type_id),false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const error_id = TRY((((module)->add_variable(error_decl))));
TRY((((*this).add_var_to_scope(catch_scope_id,(catch_name.value()),error_id,span))));
}
types::CheckedBlock const block = TRY((((*this).typecheck_block((catch_block.value()),catch_scope_id,safety_mode,JaktInternal::OptionalNone()))));
if ((((((block).control_flow)).always_transfers_control()) || ((((block).yielded_type)).has_value()))){
if ((!(((((block).yielded_type).value_or_lazy_evaluated([&] { return expression_type_id; })).equals(expression_type_id))))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("Expected a value of type ‘{}’, but got ‘{}’"),TRY((((*this).type_name(expression_type_id)))),TRY((((*this).type_name((((block).yielded_type).value())))))))),span,TRY((String::formatted(String("Expression 'catch' block must either yield the same type as the expression it is catching, or yield nothing")))),span))));
}
else {
(type_id = ((block).yielded_type).value_or_lazy_evaluated([&] { return expression_type_id; }));
}

}
(checked_catch_block = block);
}
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Try>(checked_expr,checked_catch_block,catch_name,span,type_id,expression_type_id))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_return(JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const expr,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode) {
{
if (((*this).inside_defer)){
TRY((((*this).error(String("‘return’ is not allowed inside ‘defer’"),span))));
}
if ((!(((expr).has_value())))){
if (((((*this).current_function_id)).has_value())){
NonnullRefPtr<types::CheckedFunction> const current_function = ((*this).get_function((((*this).current_function_id).value())));
NonnullRefPtr<types::Type> const return_type = ((*this).get_type(((current_function)->return_type_id)));
if (((!(((return_type)->index() == 0 /* Void */))) && (!(((return_type)->index() == 16 /* Unknown */))))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("’return’ with no value in function ’{}’ returning ’{}’"),((current_function)->name),TRY((((*this).type_name(((current_function)->return_type_id)))))))),span,TRY((String::formatted(String("Add return value of type ’{}’ here"),TRY((((*this).type_name(((current_function)->return_type_id)))))))),span))));
}
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Return>(JaktInternal::OptionalNone(),span))));
}
if (((!((((((*this).current_function_id)).has_value()) && ((((*this).get_function((((*this).current_function_id).value()))))->is_comptime)))) && (((expr.value()))->index() == 25 /* Function */))){
TRY((((*this).error(String("Returning a function is not currently supported"),span))));
}
JaktInternal::Optional<types::TypeId> type_hint = JaktInternal::OptionalNone();
if (((((*this).current_function_id)).has_value())){
(type_hint = static_cast<JaktInternal::Optional<types::TypeId>>(((((*this).get_function((((*this).current_function_id).value()))))->return_type_id)));
}
JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings((expr.value()),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),span))));
NonnullRefPtr<parser::ParsedExpression> const new_condition = ((new_condition_new_then_block_new_else_statement_).get<0>());
JaktInternal::Optional<parser::ParsedBlock> const new_then_block = ((new_condition_new_then_block_new_else_statement_).get<1>());
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const new_else_statement = ((new_condition_new_then_block_new_else_statement_).get<2>());

NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,type_hint,span))));
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Return>(checked_expr,span))));
}
}

ErrorOr<void> typechecker::Typechecker::include_prelude() {
{
String const module_name = String("__prelude__");
path::Path const file_name = TRY((path::Path::Path::from_string(module_name)));
JaktInternal::Array<u8> const file_contents = (TRY((Array<u8>::create_with({static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(83), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(83), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(107), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(100), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(83), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(98), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(98), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(121), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(66), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(106), static_cast<u8>(115), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(66), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(87), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(80), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(117), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(40), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(111), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(75), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(66), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(66), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(111), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(69), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(69), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(117), static_cast<u8>(102), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(119), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(100), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(108), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(95), static_cast<u8>(95), static_cast<u8>(95), static_cast<u8>(106), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10)}))));
JaktInternal::Optional<utility::FileId> const old_file_id = ((((*this).compiler))->current_file);
JaktInternal::Array<u8> const old_file_contents = ((((*this).compiler))->current_file_contents);
ScopeGuard __jakt_var_371([&] {
{
(((((*this).compiler))->current_file) = old_file_id);
(((((*this).compiler))->current_file_contents) = old_file_contents);
}

});
utility::FileId const file_id = TRY((((((*this).compiler))->get_file_id_or_register(file_name))));
(((((*this).compiler))->current_file) = file_id);
(((((*this).compiler))->current_file_contents) = file_contents);
types::ModuleId const prelude_module_id = TRY((((*this).create_module(module_name,false,JaktInternal::OptionalNone()))));
(((*this).current_module_id) = prelude_module_id);
TRY((((((*this).program))->set_loaded_module(module_name,types::LoadedModule(prelude_module_id,file_id)))));
types::ScopeId const prelude_scope_id = TRY((((*this).create_scope(JaktInternal::OptionalNone(),false,String("prelude")))));
JaktInternal::Array<lexer::Token> const tokens = TRY((lexer::Lexer::Lexer::lex(((*this).compiler))));
if (((((*this).compiler))->dump_lexer)){
{
JaktInternal::ArrayIterator<lexer::Token> _magic = ((tokens).iterator());
for (;;){
JaktInternal::Optional<lexer::Token> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
outln(String("token: {}"),token);
}

}
}

}
parser::ParsedNamespace const parsed_namespace = TRY((parser::Parser::Parser::parse(((*this).compiler),tokens)));
if (((((*this).compiler))->dump_parser)){
outln(String("{:#}"),parsed_namespace);
}
((((*this).compiler))->dbg_println(TRY((String::formatted(String("before typechecking parsed prelude, modules ‘{}’"),((((*this).program))->modules))))));
TRY((((*this).typecheck_module(parsed_namespace,prelude_scope_id))));
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_fields(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
JaktInternal::Array<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_fields(child_namespace,child_namespace_scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
if ((((((record).record_type)).index() == 0 /* Struct */) || ((((record).record_type)).index() == 1 /* Class */))){
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find previously added struct")))));
}
TRY((((*this).typecheck_struct_fields(record,(struct_id.value())))));
}
}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_and_specialize_generic_function(types::FunctionId const function_id,JaktInternal::Array<types::TypeId> const generic_arguments,types::ScopeId const parent_scope_id,JaktInternal::Optional<types::TypeId> const this_type_id,types::GenericInferences const generic_substitutions,JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> const type_args,utility::Span const call_span) {
{
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function(function_id));
TRY((((((((checked_function)->generics))->specializations)).push(generic_arguments))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const function_id = ((module)->next_function_id());
if ((!(((((checked_function)->parsed_function)).has_value())))){
return {};
}
parser::ParsedFunction parsed_function = ((checked_function)->to_parsed_function());
types::ScopeId const scope_id = TRY((((*this).create_scope(((((checked_function)->generics))->base_scope_id),((parsed_function).can_throw),TRY((String::formatted(String("function-specialization({})"),((parsed_function).name))))))));
if ((((((parsed_function).generic_parameters)).size()) != ((generic_arguments).size()))){
TRY((((*this).error(TRY((String::formatted(String("Generic function {} expects {} generic arguments, but {} were given"),((parsed_function).name),((((parsed_function).generic_parameters)).size()),((generic_arguments).size())))),((parsed_function).name_span)))));
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_function).generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
utility::Span arg_span = call_span;
if ((((type_args).size()) > i)){
(arg_span = ((((type_args)[i]))->span()));
}
TRY((((*this).check_type_argument_requirements(((generic_arguments)[i]),((((((((((checked_function)->generics))->params))[i])).checked_parameter)).constraints),arg_span))));
}

}
}

utility::Span const span = ((parsed_function).name_span);
{
JaktInternal::DictionaryIterator<String,String> _magic = ((generic_substitutions).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,String>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,String> substitution = (_magic_value.value());
{
if (((((*this).get_type(TRY((types::TypeId::TypeId::from_string(((substitution).get<0>())))))))->index() == 18 /* TypeVariable */)){
String const type_name = (((*this).get_type(TRY((types::TypeId::TypeId::from_string(((substitution).get<0>()))))))->get<types::Type::TypeVariable>()).value;
TRY((((*this).add_type_to_scope(scope_id,type_name,TRY((types::TypeId::TypeId::from_string(((substitution).get<1>())))),span))));
}
}

}
}

(((parsed_function).must_instantiate) = true);
(((checked_function)->is_instantiated) = true);
(((*this).current_function_id) = static_cast<JaktInternal::Optional<types::FunctionId>>(function_id));
TRY((((*this).typecheck_function_predecl(parsed_function,scope_id,this_type_id,((checked_function)->generics)))));
TRY((((*this).typecheck_function(parsed_function,scope_id))));
(((*this).current_function_id) = JaktInternal::OptionalNone());
(((checked_function)->function_scope_id) = scope_id);
}
return {};
}

ErrorOr<JaktInternal::Optional<parser::ParsedNamespace>> typechecker::Typechecker::lex_and_parse_file_contents(utility::FileId const file_id) {
{
JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::Array<u8>> const old_file_state = ((((*this).compiler))->current_file_state());
if ((!(((((*this).compiler))->set_current_file(file_id))))){
return (JaktInternal::OptionalNone());
}
ScopeGuard __jakt_var_372([&] {
((((*this).compiler))->restore_file_state(old_file_state));
});
JaktInternal::Array<lexer::Token> const tokens = TRY((lexer::Lexer::Lexer::lex(((*this).compiler))));
if (((((*this).compiler))->dump_lexer)){
{
JaktInternal::ArrayIterator<lexer::Token> _magic = ((tokens).iterator());
for (;;){
JaktInternal::Optional<lexer::Token> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
outln(String("token: {}"),token);
}

}
}

}
parser::ParsedNamespace const parsed_namespace = TRY((parser::Parser::Parser::parse(((*this).compiler),tokens)));
if (((((*this).compiler))->dump_parser)){
outln(String("{:#}"),parsed_namespace);
}
return (parsed_namespace);
}
}

types::BlockControlFlow typechecker::Typechecker::statement_control_flow(NonnullRefPtr<types::CheckedStatement> const statement) const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Return>();return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Throw>();return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Break>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(true) } );
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Continue>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(false) } );
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Yield>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((((expr)->control_flow())).updated( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(false) } )));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::If>();NonnullRefPtr<types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Boolean>();bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,types::BlockControlFlow>{
auto __jakt_enum_value = (val);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((then_block).control_flow));
}
else {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,types::BlockControlFlow>{
auto __jakt_enum_value = (((else_statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((*this).statement_control_flow((else_statement.value()))));
}
else {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
}()))
);
}
}()))
);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = ((then_block).control_flow);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::NeverReturns>();
return JaktInternal::ExplicitValue(((*this).maybe_statement_control_flow(else_statement,((then_block).control_flow))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::AlwaysReturns>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = ((*this).maybe_statement_control_flow(else_statement,((then_block).control_flow)));
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::NeverReturns>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::AlwaysReturns>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::MayReturn>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(might_break) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(might_break) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(might_break) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::MayReturn>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();return JaktInternal::ExplicitValue(((*this).maybe_statement_control_flow(else_statement,((then_block).control_flow))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();return JaktInternal::ExplicitValue(((*this).maybe_statement_control_flow(else_statement,((then_block).control_flow))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();return JaktInternal::ExplicitValue(((*this).maybe_statement_control_flow(else_statement,((then_block).control_flow))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();return JaktInternal::ExplicitValue(((*this).maybe_statement_control_flow(else_statement,((then_block).control_flow))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Block>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::While>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = ((block).control_flow);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::NeverReturns>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::AlwaysReturns>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Loop>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = ((block).control_flow);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,types::BlockControlFlow>{
auto __jakt_enum_value = (might_break);
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
}
else {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
}()))
);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::NeverReturns>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::AlwaysReturns>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::BlockControlFlow::MayReturn>();
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,types::BlockControlFlow>{
auto __jakt_enum_value = (((((block).control_flow)).may_break()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
else {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = ((block).control_flow);
switch(__jakt_match_variant.index()) {
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
}/*switch end*/
}()
)));
}
}()))
);
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Expression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->control_flow()));
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<void> typechecker::Typechecker::fill_trait_implementation_list(JaktInternal::Array<parser::ParsedNameWithGenericParameters> const parsed_impl_list,JaktInternal::Dictionary<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>& trait_implementations,types::ScopeId const scope_id,JaktInternal::Optional<types::ScopeId> const trait_name_scope_id_override) {
{
types::ScopeId const trait_name_scope_id = trait_name_scope_id_override.value_or_lazy_evaluated([&] { return scope_id; });
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = ((parsed_impl_list).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> const maybe_type_id = TRY((((*this).find_type_in_scope(trait_name_scope_id,((trait_name).name)))));
if (((maybe_type_id).has_value())){
if (((((*this).get_type((maybe_type_id.value()))))->index() == 26 /* Trait */)){
types::TraitId const trait_id = (((*this).get_type((maybe_type_id.value())))->get<types::Type::Trait>()).value;
JaktInternal::Array<types::TypeId> generic_arguments = (TRY((Array<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedType>> _magic = ((((trait_name).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedType> argument = (_magic_value.value());
{
types::TypeId const argument_type_id = TRY((((*this).typecheck_typename(argument,scope_id,JaktInternal::OptionalNone()))));
TRY((((generic_arguments).push(argument_type_id))));
}

}
}

TRY((((((trait_implementations))).set(((trait_name).name),(Tuple{trait_id, generic_arguments})))));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Expected ‘{}’ to be a trait"),((trait_name).name)))),((trait_name).name_span)))));
continue;
}

}
else {
TRY((((*this).error(TRY((String::formatted(String("Cannot find trait ‘{}’"),((trait_name).name)))),((trait_name).name_span)))));
continue;
}

}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::specialize_trait(types::TraitId const trait_id,JaktInternal::Array<types::TypeId> const generic_parameters) {
{
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait(trait_id));
if (((((trait_)->generic_parameters)).is_empty())){
return {};
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((trait_)->generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedGenericParameter const parameter = ((((trait_)->generic_parameters))[i]);
types::TypeId const type = ((generic_parameters)[i]);
TRY((((*this).check_types_for_compat(((parameter).type_id),type,((((*this).generic_inferences))),((parameter).span)))));
}

}
}

}
return {};
}

NonnullRefPtr<types::CheckedTrait> typechecker::Typechecker::get_trait(types::TraitId const id) const {
{
return (((((*this).program))->get_trait(id)));
}
}

NonnullRefPtr<types::CheckedFunction> typechecker::Typechecker::get_function(types::FunctionId const id) const {
{
return (((((*this).program))->get_function(id)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_predecl(parser::ParsedRecord const parsed_record,types::StructId const struct_id,types::ScopeId const scope_id) {
{
JaktInternal::Dictionary<String,String> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
ScopeGuard __jakt_var_373([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
types::ScopeId const struct_scope_id = ((((((((*this).current_module()))->structures))[((struct_id).id)])).scope_id);
TRY((((*this).add_struct_to_scope(scope_id,((parsed_record).name),struct_id,((parsed_record).name_span)))));
JaktInternal::Optional<types::StructId> super_struct_id = JaktInternal::OptionalNone();
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> const& super_parsed_type = __jakt_match_value.super_type;
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>>{
auto __jakt_enum_value = (((super_parsed_type).has_value()));
if (__jakt_enum_value == true) {
{
types::TypeId const super_type_id = TRY((((*this).typecheck_typename((super_parsed_type.value()),scope_id,JaktInternal::OptionalNone()))));
NonnullRefPtr<types::Type> const super_type = ((*this).get_type(super_type_id));
if (((super_type)->index() == 23 /* Struct */)){
types::StructId const struct_id = (super_type->get<types::Type::Struct>()).value;
(super_struct_id = struct_id);
}
else {
TRY((((*this).error(String("Class can only inherit from another class"),(((super_parsed_type.value()))->span())))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> const& super_parsed_type = __jakt_match_value.super_type;
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>>{
auto __jakt_enum_value = (((super_parsed_type).has_value()));
if (__jakt_enum_value == true) {
{
types::TypeId const super_type_id = TRY((((*this).typecheck_typename((super_parsed_type.value()),scope_id,JaktInternal::OptionalNone()))));
NonnullRefPtr<types::Type> const super_type = ((*this).get_type(super_type_id));
if (((super_type)->index() == 23 /* Struct */)){
types::StructId const struct_id = (super_type->get<types::Type::Struct>()).value;
(super_struct_id = struct_id);
}
else {
TRY((((*this).error(String("Struct can only inherit from another struct"),(((super_parsed_type.value()))->span())))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(String("Expected Struct or Class in typecheck_struct_predecl"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
NonnullRefPtr<types::Module> module = ((*this).current_module());
(((((module)->structures))[((struct_id).id)]) = types::CheckedStruct(((parsed_record).name),((parsed_record).name_span),(TRY((Array<types::CheckedGenericParameter>::create_with({})))),(TRY((Array<types::CheckedField>::create_with({})))),struct_scope_id,((parsed_record).definition_linkage),(TRY((Dictionary<String, JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>::create_with_entries({})))),((parsed_record).record_type),struct_type_id,super_struct_id));
JaktInternal::Array<types::CheckedGenericParameter> generic_parameters = ((((((module)->structures))[((struct_id).id)])).generic_parameters);
TRY((((generic_parameters).ensure_capacity(((((parsed_record).generic_parameters)).size())))));
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((parsed_record).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter gen_parameter = (_magic_value.value());
{
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::TypeVariable>(((gen_parameter).name))))))));
types::TypeId const parameter_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
types::CheckedGenericParameter parameter = TRY((types::CheckedGenericParameter::CheckedGenericParameter::make(parameter_type_id,((gen_parameter).span))));
if (((((gen_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((gen_parameter).requires_list).value()),((((parameter).constraints))),scope_id))));
}
TRY((((generic_parameters).push(parameter))));
TRY((((*this).add_type_to_scope(struct_scope_id,((gen_parameter).name),parameter_type_id,((gen_parameter).span)))));
}

}
}

if (((((parsed_record).implements_list)).has_value())){
TRY((((*this).fill_trait_implementation_list((((parsed_record).implements_list).value()),((((((((module)->structures))[((struct_id).id)])).trait_implementations))),struct_scope_id,JaktInternal::OptionalNone()))));
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = (((((parsed_record).implements_list).value())).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters implements_entry = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((implements_entry).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((((((((((*this).program))->modules))[(((((trait_id.value())).module)).id)]))->traits))[(((trait_id.value())).id)]);
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
String const name = ((jakt__name__function_id__).get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).get<1>());

if (((TRY((((*this).find_function_in_scope(struct_scope_id,name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function_ = ((((((((((*this).program))->modules))[((((function_id).module)).id)]))->functions))[((function_id).id)]);
if (((((((function_)->block)).statements)).is_empty())){
continue;
}
TRY((((*this).add_function_to_scope(struct_scope_id,name,function_id,((implements_entry).name_span)))));
}

}
}

}
else {
continue;
}

}

}
}

}
bool const is_extern = ((((parsed_record).definition_linkage)).index() == 1 /* External */);
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((parsed_record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
parser::ParsedFunction const func = ((method).parsed_function);
types::ScopeId const method_scope_id = TRY((((*this).create_scope(struct_scope_id,((func).can_throw),TRY((String::formatted(String("method({}::{})"),((parsed_record).name),((func).name))))))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(method_scope_id,((func).can_throw),TRY((String::formatted(String("method-block({}::{})"),((parsed_record).name),((func).name))))))));
bool const is_generic = ((!(((((parsed_record).generic_parameters)).is_empty()))) || (!(((((func).generic_parameters)).is_empty()))));
NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((func).name),((func).name_span),TRY((((*this).typecheck_visibility(((method).visibility),struct_scope_id)))),types::unknown_type_id(),((func).return_type_span),(TRY((Array<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::create(method_scope_id,(TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::TypeId::none(),false),((func).can_throw),((func).type),((func).linkage),method_scope_id,struct_id,((!(is_generic)) || is_extern),((method).parsed_function),((((method).parsed_function)).is_comptime),((method).is_virtual),((method).is_override))));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
JaktInternal::Optional<types::FunctionId> const previous_index = ((*this).current_function_id);
(((*this).current_function_id) = function_id);
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((func).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter gen_parameter = (_magic_value.value());
{
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::TypeVariable>(((gen_parameter).name))))))));
types::TypeId const type_var_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
types::FunctionGenericParameter parameter = TRY((types::FunctionGenericParameter::FunctionGenericParameter::parameter(type_var_type_id,((gen_parameter).span))));
if (((((gen_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((gen_parameter).requires_list).value()),((((((parameter).checked_parameter)).constraints))),scope_id))));
}
TRY((((((((checked_function)->generics))->params)).push(parameter))));
TRY((((*this).add_type_to_scope(method_scope_id,((gen_parameter).name),type_var_type_id,((gen_parameter).span)))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedParameter> _magic = ((((func).params)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedParameter param = (_magic_value.value());
{
if ((((((param).variable)).name) == String("this"))){
types::CheckedVariable const checked_variable = types::CheckedVariable(((((param).variable)).name),struct_type_id,((((param).variable)).is_mutable),((((param).variable)).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,JaktInternal::OptionalNone())))));
}
else {
types::TypeId const param_type = TRY((((*this).typecheck_typename(((((param).variable)).parsed_type),method_scope_id,((((param).variable)).name)))));
types::CheckedVariable const checked_variable = types::CheckedVariable(((((param).variable)).name),param_type,((((param).variable)).is_mutable),((((param).variable)).span),((((((param).variable)).parsed_type))->span()), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_default_value = JaktInternal::OptionalNone();
if (((((param).default_argument)).has_value())){
NonnullRefPtr<types::CheckedExpression> checked_default_value_expr = TRY((((*this).typecheck_expression((((param).default_argument).value()),scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,param_type))));
if (((checked_default_value_expr)->index() == 23 /* OptionalNone */)){
utility::Span const expr_span = (checked_default_value_expr->get<types::CheckedExpression::OptionalNone>()).span;
(checked_default_value_expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::OptionalNone>(expr_span,param_type))));
}
types::TypeId const default_value_type_id = ((checked_default_value_expr)->type());
(checked_default_value = checked_default_value_expr);
TRY((((*this).check_types_for_compat(param_type,default_value_type_id,((((*this).generic_inferences))),((param).span)))));
}
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,checked_default_value)))));
}

}

}
}

if ((((checked_function)->is_virtual) && ((checked_function)->is_static()))){
TRY((((*this).error(String("Functions cannot be both virtual and static"),((checked_function)->name_span)))));
}
if ((((checked_function)->is_override) && ((checked_function)->is_static()))){
TRY((((*this).error(String("Functions cannot be both override and static"),((checked_function)->name_span)))));
}
TRY((((*this).add_function_to_scope(struct_scope_id,((func).name),function_id,((parsed_record).name_span)))));
types::TypeId const function_return_type_id = TRY((((*this).typecheck_typename(((func).return_type),method_scope_id,JaktInternal::OptionalNone()))));
(((checked_function)->return_type_id) = function_return_type_id);
(((((module)->functions))[((function_id).id)]) = checked_function);
(((*this).current_function_id) = previous_index);
}

}
}

(((((((module)->structures))[((struct_id).id)])).generic_parameters) = generic_parameters);
(((*this).current_struct_type_id) = JaktInternal::OptionalNone());
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_predecl_initial(parser::ParsedRecord const parsed_record,size_t const enum_index,size_t const module_enum_len,types::ScopeId const scope_id) {
{
types::ModuleId const module_id = ((*this).current_module_id);
types::EnumId const enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::Enum>(enum_id)))))));
types::TypeId const enum_type_id = types::TypeId(module_id,(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((*this).add_type_to_scope(scope_id,((parsed_record).name),enum_type_id,((parsed_record).name_span)))));
bool const is_boxed = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();bool const& is_boxed = __jakt_match_value.is_boxed;
return JaktInternal::ExplicitValue(is_boxed);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
}/*switch end*/
}()
));
TRY((((((module)->enums)).push(types::CheckedEnum(((parsed_record).name),((parsed_record).name_span),(TRY((Array<types::CheckedGenericParameter>::create_with({})))),(TRY((Array<types::CheckedEnumVariant>::create_with({})))),(TRY((Array<types::CheckedField>::create_with({})))),((*this).prelude_scope_id()),((parsed_record).definition_linkage),(TRY((Dictionary<String, JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>::create_with_entries({})))),((parsed_record).record_type),enum_type_id,enum_type_id,is_boxed)))));
}
return {};
}

NonnullRefPtr<types::Type> typechecker::Typechecker::get_type(types::TypeId const id) const {
{
return (((((*this).program))->get_type(id)));
}
}

ErrorOr<JaktInternal::Optional<types::TraitId>> typechecker::Typechecker::find_trait_in_scope(types::ScopeId const scope_id,String const name) const {
{
types::ScopeId current = scope_id;
for (;;){
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(current))));
JaktInternal::Optional<types::TraitId> const maybe_trait = ((((scope)->traits)).get(name));
if (((maybe_trait).has_value())){
return (maybe_trait);
}
{
JaktInternal::ArrayIterator<types::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<types::ScopeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ScopeId child_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((*this).get_scope(child_id))));
if ((!(((((child_scope)->namespace_name)).has_value())))){
JaktInternal::Optional<types::TraitId> const maybe_trait = ((((child_scope)->traits)).get(name));
if (((maybe_trait).has_value())){
return (maybe_trait);
}
}
}

}
}

if (((((scope)->parent)).has_value())){
(current = ((((scope)->parent)).value()));
}
else {
break;
}

}
return (JaktInternal::OptionalNone());
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_extern_import(parser::ParsedExternImport const import_,types::ScopeId const scope_id) {
{
{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((((import_).assigned_namespace)).functions)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction f = (_magic_value.value());
{
if ((!(((((f).linkage)).index() == 1 /* External */)))){
TRY((((*this).error(String("Expected all functions in an `import extern` to be be external"),((f).name_span)))));
}
if ((((import_).is_c) && (!(((((f).generic_parameters)).is_empty()))))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("imported function '{}' is declared to have C linkage, but is generic"),((f).name)))),((f).name_span),String("this function may not be generic"),((f).name_span)))));
}
if ((!(((((((f).block)).stmts)).is_empty())))){
TRY((((*this).error(String("imported extern function is not allowed to have a body"),((f).name_span)))));
}
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((((import_).assigned_namespace)).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
if ((!(((((record).definition_linkage)).index() == 1 /* External */)))){
TRY((((*this).error(String("Expected all records in an `import extern` to be external"),((record).name_span)))));
}
if ((((import_).is_c) && (!(((((record).generic_parameters)).is_empty()))))){
TRY((((*this).error_with_hint(TRY((String::formatted(String("imported {} '{}' is declared to have C linkage, but is generic"),((((record).record_type)).record_type_name()),((record).name)))),((record).name_span),TRY((String::formatted(String("this {} may not be generic"),((((record).record_type)).record_type_name())))),((record).name_span)))));
}
}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::check_member_access(types::ScopeId const accessor,types::ScopeId const accessee,types::CheckedVariable const member,utility::Span const span) {
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((member).visibility);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedVisibility::Private>();
{
if ((!(TRY((((*this).scope_can_access(accessor,accessee))))))){
TRY((((*this).error(TRY((String::formatted(String("Can't access field ‘{}’, because it is marked private"),((member).name)))),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedVisibility::Restricted>();JaktInternal::Array<NonnullRefPtr<types::MaybeResolvedScope>> const& scopes = __jakt_match_value.scopes;
{
TRY((((*this).check_restricted_access(accessor,String("field"),accessee,((member).name),scopes,span))));
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
}
return {};
}

ErrorOr<JaktInternal::Optional<types::FunctionId>> typechecker::Typechecker::typecheck_method(parser::ParsedFunction const func,types::StructOrEnumId const parent_id) {
{
JaktInternal::Array<types::CheckedGenericParameter> parent_generic_parameters = (TRY((Array<types::CheckedGenericParameter>::create_with({}))));
types::ScopeId scope_id = ((*this).prelude_scope_id());
parser::DefinitionLinkage definition_linkage =  parser::DefinitionLinkage { typename parser::DefinitionLinkage::Internal() } ;
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<types::FunctionId>>>{
auto&& __jakt_match_variant = parent_id;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructOrEnumId::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct structure = ((*this).get_struct(struct_id));
(parent_generic_parameters = ((structure).generic_parameters));
(scope_id = ((structure).scope_id));
(definition_linkage = ((structure).definition_linkage));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructOrEnumId::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
(definition_linkage = ((enum_).definition_linkage));
(scope_id = ((enum_).scope_id));
(parent_generic_parameters = ((enum_).generic_parameters));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
if ((((!(((((func).generic_parameters)).is_empty()))) || (!(((parent_generic_parameters).is_empty())))) && (!(((func).must_instantiate))))){
return (JaktInternal::OptionalNone());
}
types::ScopeId const structure_scope_id = scope_id;
parser::DefinitionLinkage const structure_linkage = definition_linkage;
JaktInternal::Optional<types::FunctionId> const method_id = TRY((((*this).find_function_in_scope(structure_scope_id,((func).name)))));
if ((!(((method_id).has_value())))){
TRY((((((*this).compiler))->panic(String("we just pushed the checked function, but it's not present")))));
}
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function((method_id.value())));
types::ScopeId const function_scope_id = ((checked_function)->function_scope_id);
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
types::CheckedVariable const variable = ((param).variable);
types::VarId const var_id = TRY((((module)->add_variable(variable))));
TRY((((*this).add_var_to_scope(function_scope_id,((variable).name),var_id,((variable).definition_span)))));
}

}
}

(((*this).current_function_id) = method_id);
types::TypeId const VOID_TYPE_ID = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
types::CheckedBlock const block = TRY((((*this).typecheck_block(((func).block),function_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
types::TypeId const function_return_type_id = TRY((((*this).typecheck_typename(((func).return_type),function_scope_id,JaktInternal::OptionalNone()))));
types::TypeId return_type_id = function_return_type_id;
if ((((function_return_type_id).equals(types::unknown_type_id())) && (!(((((block).statements)).is_empty()))))){
if (((((((block).statements))[static_cast<i64>(0LL)]))->index() == 8 /* Return */)){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const val = (((((block).statements))[static_cast<i64>(0LL)])->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
(return_type_id = (((val.value()))->type()));
}
else {
(return_type_id = VOID_TYPE_ID);
}

}
else {
(return_type_id = VOID_TYPE_ID);
}

}
else if (((function_return_type_id).equals(types::unknown_type_id()))){
(return_type_id = VOID_TYPE_ID);
}
if (((!(((structure_linkage).index() == 1 /* External */))) && ((!(((return_type_id).equals(VOID_TYPE_ID)))) && (!(((((block).control_flow)).always_transfers_control())))))){
if ((((return_type_id).equals(types::never_type_id())) && (!(((((block).control_flow)).never_returns()))))){
TRY((((*this).error(String("Control reaches end of never-returning function"),((func).name_span)))));
}
else if ((!(((((block).control_flow)).never_returns())))){
TRY((((*this).error(String("Control reaches end of non-void function"),((func).name_span)))));
}
}
(((checked_function)->block) = block);
(((checked_function)->return_type_id) = return_type_id);
return ((method_id.value()));
}
}

ErrorOr<void> typechecker::Typechecker::error(String const message,utility::Span const span) {
{
if ((!(((*this).ignore_errors)))){
TRY((((((((*this).compiler))->errors)).push( error::JaktError { typename error::JaktError::Message(message,span) } ))));
}
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::infer_unsigned_int(u64 const val,utility::Span const span,JaktInternal::Optional<types::TypeId> const type_hint) {
{
NonnullRefPtr<types::CheckedExpression> expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } ))));
if (((type_hint).has_value())){
types::TypeId const hint = (type_hint.value());
if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8((infallible_integer_cast<i8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16((infallible_integer_cast<i16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16((infallible_integer_cast<u16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U32((infallible_integer_cast<u32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))){
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))));
}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))){
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))));
}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))){
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))));
}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((val > static_cast<u64>(255ULL))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))));
}

}
}
return (expr);
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_unary_negate(NonnullRefPtr<types::CheckedExpression> const expr,utility::Span const span,types::TypeId const type_id) {
{
if (((!(((((*this).program))->is_integer(type_id)))) || ((((*this).program))->is_signed(type_id)))){
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,type_id))));
}
types::TypeId const flipped_sign_type = TRY((((((*this).get_type(type_id)))->flip_signedness())));
types::CheckedNumericConstant const constant = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedNumericConstant, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NumericConstant>();types::CheckedNumericConstant const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(val);
};/*case end*/
default: {
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,type_id))));
}
};/*case end*/
}/*switch end*/
}()
));
types::NumberConstant const number = (((constant).number_constant()).value());
size_t const raw_number = ((number).to_usize());
size_t const max_signed = (infallible_integer_cast<size_t>((((TRY((types::Type::template create<typename types::Type::I64>())))->max()))));
i64 negated_number = static_cast<i64>(0LL);
if ((raw_number == (JaktInternal::checked_add<size_t>(max_signed,static_cast<size_t>(1ULL))))){
(negated_number = ((TRY((types::Type::template create<typename types::Type::I64>())))->min()));
}
if ((raw_number <= max_signed)){
(negated_number = (JaktInternal::checked_sub<i64>(static_cast<i64>(0LL),(infallible_integer_cast<i64>((raw_number))))));
}
types::NumberConstant const negated_number_constant =  types::NumberConstant { typename types::NumberConstant::Signed((infallible_integer_cast<i64>((negated_number)))) } ;
if (((raw_number > (JaktInternal::checked_add<size_t>(max_signed,static_cast<size_t>(1ULL)))) || (!(((negated_number_constant).can_fit_number(flipped_sign_type,((*this).program))))))){
TRY((((*this).error(TRY((String::formatted(String("Negative literal -{} too small for type ‘{}’"),raw_number,TRY((((*this).type_name(flipped_sign_type))))))),span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,type_id))));
}
types::CheckedNumericConstant const new_constant = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedNumericConstant, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(flipped_sign_type));
switch(__jakt_match_variant.index()) {
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I8>();
return JaktInternal::ExplicitValue( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8((infallible_integer_cast<i8>((negated_number)))) } );
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I16>();
return JaktInternal::ExplicitValue( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16((infallible_integer_cast<i16>((negated_number)))) } );
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I32>();
return JaktInternal::ExplicitValue( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((negated_number)))) } );
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::I64>();
return JaktInternal::ExplicitValue( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I64((infallible_integer_cast<i64>((negated_number)))) } );
};/*case end*/
default: {
{
utility::panic(String("Unreachable"));
}
};/*case end*/
}/*switch end*/
}()
));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>(new_constant,span,type_id))), types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,flipped_sign_type))));
}
}

ErrorOr<JaktInternal::Optional<types::FunctionId>> typechecker::Typechecker::resolve_call(parser::ParsedCall const call,JaktInternal::Array<types::ResolvedNamespace> namespaces,utility::Span const span,types::ScopeId const scope_id,bool const must_be_enum_constructor,bool const ignore_errors) {
{
JaktInternal::Optional<types::FunctionId> callee = JaktInternal::OptionalNone();
types::ScopeId current_scope_id = scope_id;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).namespace_)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t namespace_index = (_magic_value.value());
{
String const scope_name = ((((call).namespace_))[namespace_index]);
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> const maybe_ns_scope = TRY((((*this).find_namespace_in_scope(current_scope_id,scope_name))));
if (((maybe_ns_scope).has_value())){
JaktInternal::Tuple<types::ScopeId,bool> const scope_id_is_import_ = (maybe_ns_scope.value());
types::ScopeId const scope_id = ((scope_id_is_import_).get<0>());
bool const is_import = ((scope_id_is_import_).get<1>());

if (is_import){
(((((namespaces)[namespace_index])).name) = ((((((((*this).program))->modules))[((((scope_id).module_id)).id)]))->name));
}
(current_scope_id = scope_id);
continue;
}
JaktInternal::Optional<types::StructId> const maybe_struct_scope = TRY((((*this).find_struct_in_scope(current_scope_id,scope_name))));
if (((maybe_struct_scope).has_value())){
types::CheckedStruct const structure = ((*this).get_struct((maybe_struct_scope.value())));
(current_scope_id = ((structure).scope_id));
continue;
}
JaktInternal::Optional<types::EnumId> const maybe_enum_scope = TRY((((((*this).program))->find_enum_in_scope(current_scope_id,scope_name))));
if (((maybe_enum_scope).has_value())){
types::CheckedEnum const enum_ = ((*this).get_enum((maybe_enum_scope.value())));
(current_scope_id = ((enum_).scope_id));
continue;
}
TRY((((*this).error(TRY((String::formatted(String("Not a namespace, enum, class, or struct: ‘{}’"),utility::join(((call).namespace_),String("::"))))),span))));
}

}
}

JaktInternal::Optional<types::CheckedVariable> const maybe_var = TRY((((*this).find_var_in_scope(current_scope_id,((call).name)))));
if (((maybe_var).has_value())){
types::TypeId const inner_type = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<JaktInternal::Optional<types::FunctionId>>>{
auto&& __jakt_match_variant = *((*this).get_type((((maybe_var.value())).type_id)));
switch(__jakt_match_variant.index()) {
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
default: {
return JaktInternal::ExplicitValue((((maybe_var.value())).type_id));
};/*case end*/
}/*switch end*/
}()
));
if (((((*this).get_type(inner_type)))->index() == 29 /* Function */)){
types::FunctionId const pseudo_function_id = (((*this).get_type(inner_type))->get<types::Type::Function>()).pseudo_function_id;
return (pseudo_function_id);
}
}
JaktInternal::Optional<types::FunctionId> const maybe_function_id = TRY((((*this).find_function_in_scope(current_scope_id,((call).name)))));
if (((maybe_function_id).has_value())){
types::FunctionId const function_id = (maybe_function_id.value());
if (((!(must_be_enum_constructor)) || ((((((*this).get_function(function_id)))->type)).index() == 2 /* ImplicitEnumConstructor */))){
return (function_id);
}
}
if (must_be_enum_constructor){
TRY((((*this).error(TRY((String::formatted(String("No such enum constructor ‘{}’"),((call).name)))),span))));
return (callee);
}
JaktInternal::Optional<types::StructId> const maybe_struct_id = TRY((((*this).find_struct_in_scope(current_scope_id,((call).name)))));
if (((maybe_struct_id).has_value())){
types::StructId const struct_id = (maybe_struct_id.value());
types::CheckedStruct const structure = ((*this).get_struct(struct_id));
JaktInternal::Optional<types::FunctionId> const maybe_function_id = TRY((((*this).find_function_in_scope(((structure).scope_id),((call).name)))));
if (((maybe_function_id).has_value())){
return ((maybe_function_id.value()));
}
return (callee);
}
if ((!(ignore_errors))){
TRY((((*this).error(TRY((String::formatted(String("Call to unknown function: ‘{}’"),((call).name)))),span))));
}
return (JaktInternal::OptionalNone());
}
}

ErrorOr<NonnullRefPtr<types::CheckedProgram>> typechecker::Typechecker::typecheck(NonnullRefPtr<compiler::Compiler> compiler,parser::ParsedNamespace const parsed_namespace) {
{
JaktInternal::Optional<utility::FileId> const input_file = ((compiler)->current_file);
if ((!(((input_file).has_value())))){
TRY((((compiler)->panic(String("trying to typecheck a non-existant file")))));
}
types::ModuleId const placeholder_module_id = types::ModuleId(static_cast<size_t>(0ULL));
typechecker::Typechecker typechecker = typechecker::Typechecker(compiler,TRY((types::CheckedProgram::create(compiler,(TRY((Array<NonnullRefPtr<types::Module>>::create_with({})))),(TRY((Dictionary<String, types::LoadedModule>::create_with_entries({}))))))),placeholder_module_id,types::TypeId::TypeId::none(),JaktInternal::OptionalNone(),false,static_cast<size_t>(0ULL),false,((compiler)->dump_type_hints),((compiler)->dump_try_hints),static_cast<u64>(0ULL),types::GenericInferences((TRY((Dictionary<String, String>::create_with_entries({}))))));
TRY((((typechecker).include_prelude())));
String const root_module_name = String("Root Module");
types::ModuleId const root_module_id = TRY((((typechecker).create_module(root_module_name,true,JaktInternal::OptionalNone()))));
(((typechecker).current_module_id) = root_module_id);
((compiler)->set_current_file((input_file.value())));
TRY((((((typechecker).program))->set_loaded_module(root_module_name,types::LoadedModule(root_module_id,(input_file.value()))))));
types::ScopeId const PRELUDE_SCOPE_ID = ((typechecker).prelude_scope_id());
types::ScopeId const root_scope_id = TRY((((typechecker).create_scope(PRELUDE_SCOPE_ID,false,String("root")))));
TRY((((typechecker).typecheck_module_import(parser::ParsedModuleImport( parser::ImportName { typename parser::ImportName::Literal(String("jakt::prelude::prelude"),utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))) } ,JaktInternal::OptionalNone(), parser::ImportList { typename parser::ImportList::All() } ),root_scope_id))));
TRY((((typechecker).typecheck_module(parsed_namespace,root_scope_id))));
return (((typechecker).program));
}
}

ErrorOr<bool> typechecker::Typechecker::add_enum_to_scope(types::ScopeId const scope_id,String const name,types::EnumId const enum_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::EnumId> const maybe_enum_id = ((((scope)->enums)).get(name));
if (((maybe_enum_id).has_value())){
types::EnumId const existing_enum_id = (maybe_enum_id.value());
utility::Span const definition_span = ((((*this).get_enum(existing_enum_id))).name_span);
TRY((((*this).error_with_hint(TRY((String::formatted(String("redefinition of enum {}"),name))),span,TRY((String::formatted(String("enum {} was first defined here"),name))),definition_span))));
return (false);
}
TRY((((((scope)->enums)).set(name,enum_id))));
return (true);
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_dictionary(JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>>> const values,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
types::StructId const dictionary_struct_id = TRY((((*this).find_struct_in_prelude(String("Dictionary")))));
JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> checked_kv_pairs = (TRY((Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>>::create_with({}))));
types::TypeId key_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> key_type_span = JaktInternal::OptionalNone();
types::TypeId value_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> value_type_span = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> key_hint = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> value_hint = JaktInternal::OptionalNone();
if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
types::StructId const id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
if (((id).equals(dictionary_struct_id))){
(key_hint = ((args)[static_cast<i64>(0LL)]));
(value_hint = ((args)[static_cast<i64>(1LL)]));
}
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>> key__value__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>> const jakt__key__value__ = key__value__;
NonnullRefPtr<parser::ParsedExpression> const key = ((jakt__key__value__).get<0>());
NonnullRefPtr<parser::ParsedExpression> const value = ((jakt__key__value__).get<1>());

NonnullRefPtr<types::CheckedExpression> const checked_key = TRY((((*this).typecheck_expression(key,scope_id,safety_mode,key_hint))));
types::TypeId const current_key_type_id = ((checked_key)->type());
NonnullRefPtr<types::CheckedExpression> const checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,value_hint))));
types::TypeId const current_value_type_id = ((checked_value)->type());
types::TypeId const VOID_TYPE_ID = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
if ((((key_type_id).equals(types::unknown_type_id())) && ((value_type_id).equals(types::unknown_type_id())))){
if (((current_key_type_id).equals(VOID_TYPE_ID))){
TRY((((*this).error(String("Can't create a dictionary with keys of type void"),((key)->span())))));
}
if (((current_value_type_id).equals(VOID_TYPE_ID))){
TRY((((*this).error(String("Can't create a dictionary with values of type void"),((value)->span())))));
}
(key_type_id = current_key_type_id);
(key_type_span = static_cast<JaktInternal::Optional<utility::Span>>(((key)->span())));
(value_type_id = current_value_type_id);
(value_type_span = static_cast<JaktInternal::Optional<utility::Span>>(((value)->span())));
}
else {
if ((!(((key_type_id).equals(current_key_type_id))))){
String const key_type_name = TRY((((*this).type_name(key_type_id))));
String const current_key_type_name = TRY((((*this).type_name(current_key_type_id))));
TRY((((*this).error_with_hint(TRY((String::formatted(String("Type '{}' does not match type '{}' of previous keys in dictionary"),current_key_type_name,key_type_name))),((key)->span()),TRY((String::formatted(String("Dictionary was inferred to store keys of type '{}' here"),key_type_name))),(key_type_span.value())))));
}
if ((!(((value_type_id).equals(current_value_type_id))))){
String const value_type_name = TRY((((*this).type_name(value_type_id))));
String const current_value_type_name = TRY((((*this).type_name(current_value_type_id))));
TRY((((*this).error_with_hint(TRY((String::formatted(String("Type '{}' does not match type '{}' of previous values in dictionary"),current_value_type_name,value_type_name))),((value)->span()),TRY((String::formatted(String("Dictionary was inferred to store values of type '{}' here"),value_type_name))),(value_type_span.value())))));
}
}

TRY((((checked_kv_pairs).push((Tuple{checked_key, checked_value})))));
}

}
}

if (((key_type_id).equals(types::unknown_type_id()))){
if (((key_hint).has_value())){
(key_type_id = (key_hint.value()));
}
else {
TRY((((*this).error(String("Cannot infer key type for Dictionary<K, V>"),span))));
}

}
if (((value_type_id).equals(types::unknown_type_id()))){
if (((value_hint).has_value())){
(value_type_id = (value_hint.value()));
}
else {
TRY((((*this).error(String("Cannot infer value type for Dictionary"),span))));
}

}
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(dictionary_struct_id,(TRY((Array<types::TypeId>::create_with({key_type_id, value_type_id})))))))))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::JaktDictionary>(checked_kv_pairs,span,type_id,key_type_id,value_type_id))));
}
}

ErrorOr<void> typechecker::Typechecker::check_implicit_constructor_argument_access(types::ScopeId const caller_scope_id,parser::ParsedCall const call,types::CheckedStruct const struct_) {
{
if ((!(TRY((((*this).scope_can_access(caller_scope_id,((struct_).scope_id)))))))){
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> arg = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const variable = ((*this).get_variable(((field).variable_id)));
if (((((variable).name) == ((arg).get<0>())) && ((((variable).visibility)).index() == 1 /* Private */))){
TRY((((*this).error(TRY((String::formatted(String("Can't access field '{}' when calling implicit constructor of '{}' because it is marked private"),((variable).name),((struct_).name)))),((arg).get<1>())))));
return {};
}
}

}
}

}

}
}

}
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_if(NonnullRefPtr<parser::ParsedExpression> const condition,parser::ParsedBlock const then_block,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const else_statement,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings(condition,JaktInternal::OptionalNone(),then_block,else_statement,span))));
NonnullRefPtr<parser::ParsedExpression> const new_condition = ((new_condition_new_then_block_new_else_statement_).get<0>());
JaktInternal::Optional<parser::ParsedBlock> const new_then_block = ((new_condition_new_then_block_new_else_statement_).get<1>());
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const new_else_statement = ((new_condition_new_then_block_new_else_statement_).get<2>());

NonnullRefPtr<types::CheckedExpression> const checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("Condition must be a boolean expression"),((new_condition)->span())))));
}
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block((new_then_block.value()),scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(String("An 'if' block is not allowed to yield values"),((((new_then_block.value())).find_yield_span()).value())))));
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> checked_else = JaktInternal::OptionalNone();
if (((new_else_statement).has_value())){
(checked_else = TRY((((*this).typecheck_statement((new_else_statement.value()),scope_id,safety_mode,JaktInternal::OptionalNone())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::If>(checked_condition,checked_block,checked_else,span))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::unify_with_type(types::TypeId const found_type,JaktInternal::Optional<types::TypeId> const expected_type,utility::Span const span) {
{
if ((!(((expected_type).has_value())))){
return (found_type);
}
if ((((expected_type.value())).equals(types::unknown_type_id()))){
return (found_type);
}
if (TRY((((*this).check_types_for_compat((expected_type.value()),found_type,((((*this).generic_inferences))),span))))){
return (found_type);
}
return (TRY((((*this).substitute_typevars_in_type(found_type,((*this).generic_inferences))))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_trait_predecl(parser::ParsedTrait const parsed_trait,types::ScopeId const scope_id) {
{
types::ScopeId const trait_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((String::formatted(String("trait({})"),((parsed_trait).name))))))));
NonnullRefPtr<types::CheckedTrait> checked_trait = TRY((types::CheckedTrait::create(((parsed_trait).name),((parsed_trait).name_span),(TRY((Dictionary<String, types::FunctionId>::create_with_entries({})))),(TRY((Array<types::CheckedGenericParameter>::create_with({})))),trait_scope_id)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::TraitId const trait_id = types::TraitId(((*this).current_module_id),((((((((((*this).program))->modules))[((((*this).current_module_id)).id)]))->traits)).size()));
types::TypeId const trait_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Trait>(trait_id)))))));
TRY((((((((((((*this).program))->modules))[((((*this).current_module_id)).id)]))->traits)).push(checked_trait))));
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
TRY((((*this).add_type_to_scope(scope_id,((parsed_trait).name),trait_type_id,((parsed_trait).name_span)))));
TRY((((*this).add_trait_to_scope(scope_id,((parsed_trait).name),trait_id,((parsed_trait).name_span)))));
JaktInternal::Array<types::CheckedGenericParameter> generic_parameters = ((((((module)->traits))[((trait_id).id)]))->generic_parameters);
TRY((((generic_parameters).ensure_capacity(((((parsed_trait).generic_parameters)).size())))));
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((parsed_trait).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter gen_parameter = (_magic_value.value());
{
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::TypeVariable>(((gen_parameter).name))))))));
types::TypeId const parameter_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
types::CheckedGenericParameter parameter = TRY((types::CheckedGenericParameter::CheckedGenericParameter::make(parameter_type_id,((gen_parameter).span))));
if (((((gen_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((gen_parameter).requires_list).value()),((((parameter).constraints))),scope_id))));
}
TRY((((generic_parameters).push(parameter))));
TRY((((*this).add_type_to_scope(trait_scope_id,((gen_parameter).name),parameter_type_id,((gen_parameter).span)))));
}

}
}

types::StructId const synthetic_struct_id = types::StructId(((*this).current_module_id),((((((((((*this).program))->modules))[((((*this).current_module_id)).id)]))->structures)).size()));
TRY((((((module)->structures)).push(types::CheckedStruct(((parsed_trait).name),((parsed_trait).name_span),generic_parameters,(TRY((Array<types::CheckedField>::create_with({})))),trait_scope_id, parser::DefinitionLinkage { typename parser::DefinitionLinkage::External() } ,(TRY((Dictionary<String, JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>::create_with_entries({})))), parser::RecordType { typename parser::RecordType::Struct((TRY((Array<parser::ParsedField>::create_with({})))),JaktInternal::OptionalNone()) } ,trait_type_id,JaktInternal::OptionalNone())))));
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(synthetic_struct_id)))))));
{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((parsed_trait).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction parsed_function = (_magic_value.value());
{
types::ScopeId const method_scope_id = TRY((((*this).create_scope(trait_scope_id,((parsed_function).can_throw),TRY((String::formatted(String("trait-method({}::{})"),((parsed_trait).name),((parsed_function).name))))))));
types::FunctionId const function_id = ((((((*this).program))->get_module(((*this).current_module_id))))->next_function_id());
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if (((!(((((parsed_function).params)).is_empty()))) && ((((((((((parsed_function).params)).first()).value())).variable)).name) == String("this")))){
(this_arg_type_id = struct_type_id);
}
TRY((((*this).typecheck_function_predecl(parsed_function,trait_scope_id,this_arg_type_id,JaktInternal::OptionalNone()))));
TRY((((((checked_trait)->methods)).set(((parsed_function).name),function_id))));
}

}
}

}
return {};
}

ErrorOr<types::CheckedVisibility> typechecker::Typechecker::typecheck_visibility(parser::Visibility const visibility,types::ScopeId const scope_id) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedVisibility, ErrorOr<types::CheckedVisibility>>{
auto&& __jakt_match_variant = visibility;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::Visibility::Private>();
return JaktInternal::ExplicitValue( types::CheckedVisibility { typename types::CheckedVisibility::Private() } );
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::Visibility::Public>();
return JaktInternal::ExplicitValue( types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::Visibility::Restricted>();JaktInternal::Array<parser::VisibilityRestriction> const& whitelist = __jakt_match_value.whitelist;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedVisibility> __jakt_var_374; {
JaktInternal::Array<NonnullRefPtr<types::MaybeResolvedScope>> restricted_scopes = (TRY((Array<NonnullRefPtr<types::MaybeResolvedScope>>::create_with({}))));
{
JaktInternal::ArrayIterator<parser::VisibilityRestriction> _magic = ((whitelist).iterator());
for (;;){
JaktInternal::Optional<parser::VisibilityRestriction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::VisibilityRestriction entry = (_magic_value.value());
{
NonnullRefPtr<types::MaybeResolvedScope> parent_scope = TRY((types::MaybeResolvedScope::template create<typename types::MaybeResolvedScope::Resolved>(scope_id)));
{
JaktInternal::ArrayIterator<String> _magic = ((((entry).namespace_)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String ns = (_magic_value.value());
{
(parent_scope = TRY((types::MaybeResolvedScope::template create<typename types::MaybeResolvedScope::Unresolved>(parent_scope,ns))));
}

}
}

NonnullRefPtr<types::MaybeResolvedScope> unresolved = TRY((types::MaybeResolvedScope::template create<typename types::MaybeResolvedScope::Unresolved>(parent_scope,((entry).name))));
TRY((((restricted_scopes).push(TRY((((unresolved)->try_resolve(((*this).program)))))))));
}

}
}

__jakt_var_374 =  types::CheckedVisibility { typename types::CheckedVisibility::Restricted(restricted_scopes,span) } ; goto __jakt_label_350;

}
__jakt_label_350:; __jakt_var_374.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_destructuring_assignment(JaktInternal::Array<parser::ParsedVarDecl> const vars,NonnullRefPtr<parser::ParsedStatement> const var_decl,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
JaktInternal::Array<NonnullRefPtr<types::CheckedStatement>> var_decls = (TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({}))));
NonnullRefPtr<types::CheckedStatement> const checked_tuple_var_decl = TRY((((*this).typecheck_statement(var_decl,scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::TypeId expr_type_id = types::unknown_type_id();
types::VarId tuple_var_id = types::VarId(types::ModuleId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL));
if (((checked_tuple_var_decl)->index() == 3 /* VarDecl */)){
types::VarId const var_id = (checked_tuple_var_decl->get<types::CheckedStatement::VarDecl>()).var_id;
NonnullRefPtr<types::CheckedExpression> const init = (checked_tuple_var_decl->get<types::CheckedStatement::VarDecl>()).init;
(expr_type_id = ((init)->type()));
(tuple_var_id = var_id);
}
else {
TRY((((*this).error(String("Destructuting assignment should be a variable declaration"),span))));
}

JaktInternal::Array<types::TypeId> inner_types = (TRY((Array<types::TypeId>::create_with({}))));
NonnullRefPtr<types::Type> const tuple_type = ((*this).get_type(expr_type_id));
if (((tuple_type)->index() == 19 /* GenericInstance */)){
JaktInternal::Array<types::TypeId> const args = (tuple_type->get<types::Type::GenericInstance>()).args;
(inner_types = args);
}
else {
TRY((((*this).error(String("Tuple Type should be Generic Instance"),span))));
}

types::CheckedVariable const tuple_variable = ((((*this).program))->get_variable(tuple_var_id));
if ((((vars).size()) == ((inner_types).size()))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vars).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedVarDecl new_var = ((vars)[i]);
(((new_var).parsed_type) = TRY((parser::ParsedType::template create<typename parser::ParsedType::Name>(TRY((((*this).type_name(((inner_types)[i]))))),span))));
NonnullRefPtr<parser::ParsedExpression> const init = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::IndexedTuple>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::Var>(((tuple_variable).name),span))),i,false,span)));
TRY((((var_decls).push(TRY((((*this).typecheck_var_decl(((vars)[i]),init,scope_id,safety_mode,span))))))));
}

}
}

}
else {
TRY((((*this).error(String("Tuple inner types sould have same size as tuple members"),span))));
}

return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::DestructuringAssignment>(var_decls,checked_tuple_var_decl,span))));
}
}

types::ScopeId typechecker::Typechecker::prelude_scope_id() const {
{
return (((((*this).program))->prelude_scope_id()));
}
}

ErrorOr<bool> typechecker::Typechecker::add_type_to_scope(types::ScopeId const scope_id,String const type_name,types::TypeId const type_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::TypeId> const found_type_id = ((((scope)->types)).get(type_name));
if ((((found_type_id).has_value()) && (!((((found_type_id.value())).equals(type_id)))))){
TRY((((*this).error(TRY((String::formatted(String("Redefinition of type ‘{}’"),type_name))),span))));
return (false);
}
TRY((((((scope)->types)).set(type_name,type_id))));
return (true);
}
}

ErrorOr<types::ScopeId> typechecker::Typechecker::create_scope(JaktInternal::Optional<types::ScopeId> const parent_scope_id,bool const can_throw,String const debug_name) {
{
return (TRY((((((*this).program))->create_scope(parent_scope_id,can_throw,debug_name,((*this).current_module_id))))));
}
}

ErrorOr<bool> typechecker::Typechecker::validate_argument_label(types::CheckedParameter const param,String const label,utility::Span const span,NonnullRefPtr<parser::ParsedExpression> const expr,JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const default_value) {
{
if ((label == ((((param).variable)).name))){
return (true);
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Var>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if ((name == ((((param).variable)).name))){
return (true);
}
if ((!(((default_value).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Wrong parameter name in argument label (got '{}', expected '{}')"),name,((((param).variable)).name)))),span))));
}
return (false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::UnaryOp>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::UnaryOperator const& op = __jakt_match_value.op;
{
if (((((op).index() == 7 /* Reference */) || ((op).index() == 8 /* MutableReference */)) || ((op).index() == 5 /* Dereference */))){
if (((expr)->index() == 9 /* Var */)){
String const name = (expr->get<parser::ParsedExpression::Var>()).name;
utility::Span const span = (expr->get<parser::ParsedExpression::Var>()).span;
if ((name == ((((param).variable)).name))){
return (true);
}
if ((!(((default_value).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Wrong parameter name in argument label (got ‘{}’, expected ‘{}’)"),name,((((param).variable)).name)))),span))));
}
return (false);
}
}
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
if ((!(((default_value).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Wrong parameter name in argument label (got '{}', expected '{}')"),label,((((param).variable)).name)))),span))));
}
return (false);
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::infer_signed_int(i64 const val,utility::Span const span,JaktInternal::Optional<types::TypeId> const type_hint) {
{
NonnullRefPtr<types::CheckedExpression> expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } ))));
if (((type_hint).has_value())){
types::TypeId const hint = (type_hint.value());
if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8((infallible_integer_cast<i8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16((infallible_integer_cast<i16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16((infallible_integer_cast<u16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U32((infallible_integer_cast<u32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } );
NonnullRefPtr<types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < static_cast<i64>(0LL)) || (val > static_cast<i64>(255LL)))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))));
}

}
}
return (expr);
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_indexed_struct(NonnullRefPtr<parser::ParsedExpression> const expr,String const field_name,types::ScopeId const scope_id,bool const is_optional,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const checked_expr_type_id = ((checked_expr)->type());
NonnullRefPtr<types::Type> const checked_expr_type = ((*this).get_type(checked_expr_type_id));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_expr_type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
{
types::TypeId type_id = checked_expr_type_id;
if (is_optional){
if ((!(((id).equals(optional_struct_id))))){
TRY((((*this).error(String("Optional chaining is only allowed on optional types"),span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,span,is_optional,types::unknown_type_id()))));
}
(type_id = ((args)[static_cast<i64>(0LL)]));
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
{
types::CheckedStruct const structure = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const member = ((*this).get_variable(((field).variable_id)));
if ((((member).name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((structure).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,span,is_optional,resolved_type_id))));
}
}

}
}

TRY((((*this).error(TRY((String::formatted(String("unknown member of struct: {}.{}"),((structure).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const structure = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const member = ((*this).get_variable(((field).variable_id)));
if ((((member).name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((structure).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,span,is_optional,resolved_type_id))));
}
}

}
}

TRY((((*this).error(TRY((String::formatted(String("unknown member of struct: {}.{}"),((structure).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const member = ((*this).get_variable(((field).variable_id)));
if ((((member).name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((enum_).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedCommonEnumMember>(checked_expr,field_name,span,is_optional,resolved_type_id))));
}
}

}
}

TRY((((*this).error(TRY((String::formatted(String("unknown common member of enum: {}.{}"),((enum_).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const member = ((*this).get_variable(((field).variable_id)));
if ((((member).name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((enum_).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedCommonEnumMember>(checked_expr,field_name,span,is_optional,resolved_type_id))));
}
}

}
}

TRY((((*this).error(TRY((String::formatted(String("unknown common member of enum: {}.{}"),((enum_).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
return (TRY((((*this).error(TRY((String::formatted(String("Member field access on value of non-struct type ‘{}’"),TRY((((*this).type_name(checked_expr_type_id))))))),span))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
if (is_optional){
TRY((((*this).error(String("Optional chaining is not allowed on non-optional types"),span))));
}
types::CheckedStruct const structure = ((*this).get_struct(struct_id));
JaktInternal::Optional<types::FieldRecord> const field_record = TRY((((*this).lookup_struct_field(struct_id,field_name))));
if (((field_record).has_value())){
types::CheckedVariable const member = ((*this).get_variable((((field_record.value())).field_id)));
types::TypeId const resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
TRY((((*this).check_member_access(scope_id,((((*this).get_struct((((field_record.value())).struct_id)))).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,span,is_optional,resolved_type_id))));
}
TRY((((*this).error(TRY((String::formatted(String("unknown member of struct: {}.{}"),((structure).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
{
if (is_optional){
TRY((((*this).error(String("Optional chaining is not allowed on non-optional types"),span))));
}
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const member = ((*this).get_variable(((field).variable_id)));
if ((((member).name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((enum_).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedCommonEnumMember>(checked_expr,field_name,span,is_optional,resolved_type_id))));
}
}

}
}

TRY((((*this).error(TRY((String::formatted(String("unknown common member of enum: {}.{}"),((enum_).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
if (is_optional){
TRY((((*this).error(String("Optional chaining is not allowed on non-optional types"),span))));
}
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const member = ((*this).get_variable(((field).variable_id)));
if ((((member).name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((enum_).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedCommonEnumMember>(checked_expr,field_name,span,is_optional,resolved_type_id))));
}
}

}
}

TRY((((*this).error(TRY((String::formatted(String("unknown common member of enum: {}.{}"),((enum_).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
return (TRY((((*this).error(TRY((String::formatted(String("Member field access on value of non-struct type ‘{}’"),TRY((((*this).type_name(checked_expr_type_id))))))),span))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,span,is_optional,types::unknown_type_id()))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_function_predecl(parser::ParsedFunction const parsed_function,types::ScopeId const parent_scope_id,JaktInternal::Optional<types::TypeId> const this_arg_type_id,JaktInternal::Optional<NonnullRefPtr<types::FunctionGenerics>> generics) {
{
types::ScopeId const function_scope_id = TRY((((*this).create_scope(parent_scope_id,((parsed_function).can_throw),TRY((String::formatted(String("function({})"),((parsed_function).name))))))));
String const scope_debug_name = TRY((String::formatted(String("function-block({})"),((parsed_function).name))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,((parsed_function).can_throw),scope_debug_name))));
size_t const module_id = ((((*this).current_module_id)).id);
bool base_definition = false;
if ((!(((generics).has_value())))){
(generics = TRY((types::FunctionGenerics::create(function_scope_id,(TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))));
(base_definition = true);
}
bool const is_generic_function = (!(((((parsed_function).generic_parameters)).is_empty())));
bool const is_generic = (is_generic_function || (((this_arg_type_id).has_value()) && ((((*this).get_type((this_arg_type_id.value()))))->index() == 19 /* GenericInstance */)));
NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((parsed_function).name),((parsed_function).name_span),TRY((((*this).typecheck_visibility(((parsed_function).visibility),parent_scope_id)))),types::unknown_type_id(),((parsed_function).return_type_span),(TRY((Array<types::CheckedParameter>::create_with({})))),(generics.value()),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::TypeId::none(),false),((parsed_function).can_throw), parser::FunctionType { typename parser::FunctionType::Normal() } ,((parsed_function).linkage),function_scope_id,JaktInternal::OptionalNone(),((!(is_generic)) || (!(base_definition))),parsed_function,((parsed_function).is_comptime),false,false)));
NonnullRefPtr<types::Module> current_module = ((*this).current_module());
types::FunctionId const function_id = TRY((((current_module)->add_function(checked_function))));
types::ScopeId const checked_function_scope_id = ((checked_function)->function_scope_id);
bool const external_linkage = ((((parsed_function).linkage)).index() == 1 /* External */);
JaktInternal::Optional<types::ScopeId> const check_scope = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::ScopeId>,ErrorOr<void>>{
auto __jakt_enum_value = (is_generic);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::ScopeId>>(TRY((((*this).create_scope(parent_scope_id,((parsed_function).can_throw),scope_debug_name))))));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}()))
;
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((parsed_function).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter generic_parameter = (_magic_value.value());
{
types::TypeId type_var_type_id = types::TypeId(((current_module)->id),((((current_module)->types)).size()));
if (base_definition){
types::FunctionGenericParameter parameter = TRY((types::FunctionGenericParameter::FunctionGenericParameter::parameter(type_var_type_id,((generic_parameter).span))));
if (((((generic_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((generic_parameter).requires_list).value()),((((((parameter).checked_parameter)).constraints))),parent_scope_id))));
}
TRY((((((current_module)->types)).push(TRY((types::Type::template create<typename types::Type::TypeVariable>(((generic_parameter).name))))))));
TRY((((((((checked_function)->generics))->params)).push(parameter))));
}
else if (((((((((((checked_function)->generics))->params))[i])).kind)).index() == 1 /* Parameter */)){
(type_var_type_id = ((((((((checked_function)->generics))->params))[i])).type_id()));
}
if (((!(((parsed_function).must_instantiate))) || external_linkage)){
TRY((((*this).add_type_to_scope(checked_function_scope_id,((generic_parameter).name),type_var_type_id,((generic_parameter).span)))));
}
if (((check_scope).has_value())){
TRY((((*this).add_type_to_scope((check_scope.value()),((generic_parameter).name),type_var_type_id,((generic_parameter).span)))));
}
((i++));
}

}
}

bool first = true;
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<parser::ParsedParameter> _magic = ((((parsed_function).params)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedParameter parameter = (_magic_value.value());
{
types::CheckedParameter const checked_param = TRY((((*this).typecheck_parameter(parameter,checked_function_scope_id,first,this_arg_type_id,check_scope))));
TRY((((((checked_function)->params)).push(checked_param))));
if (base_definition){
TRY((((((((checked_function)->generics))->base_params)).push(checked_param))));
}
(first = false);
}

}
}

types::TypeId function_return_type_id = TRY((((*this).typecheck_typename(((parsed_function).return_type),checked_function_scope_id,JaktInternal::OptionalNone()))));
if (((!(((parsed_function).is_fat_arrow))) && ((((parsed_function).return_type))->index() == 13 /* Empty */))){
(function_return_type_id = types::void_type_id());
}
(((checked_function)->return_type_id) = function_return_type_id);
TRY((((*this).check_that_type_doesnt_contain_reference(function_return_type_id,((parsed_function).return_type_span)))));
if ((!(((((parsed_function).generic_parameters)).is_empty())))){
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::CheckedBlock const block = TRY((((*this).typecheck_block(((parsed_function).block),(check_scope.value()), types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
types::TypeId const return_type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId,ErrorOr<void>>{
auto __jakt_enum_value = (((function_return_type_id).equals(types::unknown_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((*this).infer_function_return_type(block)));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).resolve_type_var(function_return_type_id,parent_scope_id)))));
}
}()))
;
(((checked_function)->block) = block);
(((checked_function)->return_type_id) = return_type_id);
}
TRY((((*this).add_function_to_scope(parent_scope_id,((parsed_function).name),function_id,((parsed_function).name_span)))));
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_try_block(NonnullRefPtr<parser::ParsedStatement> const stmt,String const error_name,utility::Span const error_span,parser::ParsedBlock const catch_block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
types::ScopeId const try_scope_id = TRY((((*this).create_scope(scope_id,true,String("try")))));
NonnullRefPtr<types::CheckedStatement> const checked_stmt = TRY((((*this).typecheck_statement(stmt,try_scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::StructId const error_struct_id = TRY((((*this).find_struct_in_prelude(String("Error")))));
types::CheckedVariable const error_decl = types::CheckedVariable(error_name,((((*this).get_struct(error_struct_id))).type_id),false,error_span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const error_id = TRY((((module)->add_variable(error_decl))));
types::ScopeId const catch_scope_id = TRY((((*this).create_scope(scope_id,true,String("catch")))));
TRY((((*this).add_var_to_scope(catch_scope_id,error_name,error_id,error_span))));
types::CheckedBlock const checked_catch_block = TRY((((*this).typecheck_block(catch_block,catch_scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_catch_block).yielded_type)).has_value())){
TRY((((*this).error(String("A ‘catch’ block as part of a try block is not allowed to yield values"),(((catch_block).find_yield_span()).value())))));
}
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::TryBlock>(checked_stmt,checked_catch_block,error_name,error_span,span,types::void_type_id()))));
}
}

ErrorOr<types::CheckedUnaryOperator> typechecker::Typechecker::typecheck_is_enum_variant(NonnullRefPtr<types::CheckedExpression> const checked_expr,NonnullRefPtr<parser::ParsedType> const inner,JaktInternal::Array<parser::EnumVariantPatternArgument> const bindings,types::ScopeId const scope_id) {
{
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::TypeId const type_id = TRY((((*this).typecheck_typename(inner,scope_id,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
types::CheckedUnaryOperator checked_op =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Is(type_id) } ;
types::TypeId const expr_type_id = ((checked_expr)->type());
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::CheckedUnaryOperator>>{
auto&& __jakt_match_variant = *inner;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::NamespacedName>();String const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (((((*this).get_type(expr_type_id)))->index() == 24 /* Enum */)){
types::EnumId const enum_id = (((*this).get_type(expr_type_id))->get<types::Type::Enum>()).value;
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::Optional<types::CheckedEnumVariant> const variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>> const checked_enum_variant_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),bindings,span))));
(checked_op =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::IsEnumVariant((variant.value()),(checked_enum_variant_bindings.value()),expr_type_id) } );
}
else {
TRY((((*this).error(TRY((String::formatted(String("Enum variant {} does not exist on {}"),variant_name,TRY((((*this).type_name(type_id))))))),span))));
return (checked_op);
}

}
else {
TRY((((*this).error(TRY((String::formatted(String("Unknown type or invalid type name: {}"),variant_name))),span))));
return (checked_op);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();String const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (((((*this).get_type(expr_type_id)))->index() == 24 /* Enum */)){
types::EnumId const enum_id = (((*this).get_type(expr_type_id))->get<types::Type::Enum>()).value;
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::Optional<types::CheckedEnumVariant> const variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>> const checked_enum_variant_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),bindings,span))));
(checked_op =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::IsEnumVariant((variant.value()),(checked_enum_variant_bindings.value()),expr_type_id) } );
}
else {
TRY((((*this).error(TRY((String::formatted(String("Enum variant {} does not exist on {}"),variant_name,TRY((((*this).type_name(type_id))))))),span))));
return (checked_op);
}

}
else {
TRY((((*this).error(TRY((String::formatted(String("Unknown type or invalid type name: {}"),variant_name))),span))));
return (checked_op);
}

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
return (checked_op);
}
}

types::CheckedVariable typechecker::Typechecker::get_variable(types::VarId const id) const {
{
return (((((*this).program))->get_variable(id)));
}
}

bool typechecker::Typechecker::is_class(types::TypeId const type_id) const {
{
if (((((*this).get_type(type_id)))->index() == 23 /* Struct */)){
types::StructId const struct_id = (((*this).get_type(type_id))->get<types::Type::Struct>()).value;
return (((((((*this).get_struct(struct_id))).record_type)).index() == 1 /* Class */));
}
else {
return (false);
}

}
}

types::TypeId typechecker::Typechecker::infer_function_return_type(types::CheckedBlock const block) const {
{
if (((((block).statements)).is_empty())){
return (types::void_type_id());
}
if ((((((((block).statements)).last()).value()))->index() == 8 /* Return */)){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const val = ((((((block).statements)).last()).value())->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
return ((((val.value()))->type()));
}
}
return (types::void_type_id());
}
}

ErrorOr<JaktInternal::Optional<types::Value>> typechecker::Typechecker::find_comptime_binding_in_scope(types::ScopeId const scope_id,String const name) const {
{
return (TRY((((((*this).program))->find_comptime_binding_in_scope(scope_id,name)))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_statement(NonnullRefPtr<parser::ParsedStatement> const statement,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedStatement>, ErrorOr<NonnullRefPtr<types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Expression>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Expression>(TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,types::TypeId::TypeId::none())))),span))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::UnsafeBlock>();parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Block>(TRY((((*this).typecheck_block(block,scope_id, types::SafetyMode { typename types::SafetyMode::Unsafe() } ,JaktInternal::OptionalNone())))),span))));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Yield>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Yield>(TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,type_hint)))),span))));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Return>();JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_return(expr,span,scope_id,safety_mode)))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Block>();parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_block_statement(block,scope_id,safety_mode,span)))));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::InlineCpp>();parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_inline_cpp(block,span,safety_mode)))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Defer>();NonnullRefPtr<parser::ParsedStatement> const& statement = __jakt_match_value.statement;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_defer(statement,scope_id,safety_mode,span)))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Loop>();parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_loop(block,scope_id,safety_mode,span)))));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Throw>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_throw(expr,scope_id,safety_mode,span)))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::While>();NonnullRefPtr<parser::ParsedExpression> const& condition = __jakt_match_value.condition;
parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_while(condition,block,scope_id,safety_mode,span)))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedStatement::Continue>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Continue>(span))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedStatement::Break>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Break>(span))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::VarDecl>();parser::ParsedVarDecl const& var = __jakt_match_value.var;
NonnullRefPtr<parser::ParsedExpression> const& init = __jakt_match_value.init;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_var_decl(var,init,scope_id,safety_mode,span)))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::DestructuringAssignment>();JaktInternal::Array<parser::ParsedVarDecl> const& vars = __jakt_match_value.vars;
NonnullRefPtr<parser::ParsedStatement> const& var_decl = __jakt_match_value.var_decl;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_destructuring_assignment(vars,var_decl,scope_id,safety_mode,span)))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::If>();NonnullRefPtr<parser::ParsedExpression> const& condition = __jakt_match_value.condition;
parser::ParsedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const& else_statement = __jakt_match_value.else_statement;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_if(condition,then_block,else_statement,scope_id,safety_mode,span)))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedStatement::Garbage>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Garbage>(span))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::For>();String const& iterator_name = __jakt_match_value.iterator_name;
utility::Span const& name_span = __jakt_match_value.name_span;
NonnullRefPtr<parser::ParsedExpression> const& range = __jakt_match_value.range;
parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_for(iterator_name,name_span,range,block,scope_id,safety_mode,span)))));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Guard>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::ParsedBlock const& else_block = __jakt_match_value.else_block;
parser::ParsedBlock const& remaining_code = __jakt_match_value.remaining_code;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_guard(expr,else_block,remaining_code,scope_id,safety_mode,span)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>>>> typechecker::Typechecker::resolve_default_params(JaktInternal::Array<types::CheckedParameter> const params,JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> const args,types::ScopeId const scope_id,types::SafetyMode const safety_mode,size_t const arg_offset,utility::Span const span) {
{
size_t params_with_default_value = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if (((((param).default_value)).has_value())){
((params_with_default_value++));
}
}

}
}

if (((((args).size()) >= (JaktInternal::checked_sub<size_t>((JaktInternal::checked_sub<size_t>(((params).size()),arg_offset)),params_with_default_value))) && (((args).size()) <= (JaktInternal::checked_sub<size_t>(((params).size()),arg_offset))))){
size_t consumed_arg = static_cast<size_t>(0ULL);
JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>>> resolved_args = (TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>>>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(arg_offset),static_cast<size_t>(((params).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedParameter const param = ((params)[i]);
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> maybe_checked_expr = JaktInternal::OptionalNone();
if ((!(((param).requires_label)))){
if ((((args).size()) > consumed_arg)){
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> const name_span_expr_ = ((args)[consumed_arg]);
String const name = ((name_span_expr_).get<0>());
utility::Span const span = ((name_span_expr_).get<1>());
NonnullRefPtr<parser::ParsedExpression> const expr = ((name_span_expr_).get<2>());

(maybe_checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,((((param).variable)).type_id))))));
((consumed_arg++));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Missing argument for function parameter {}"),((((param).variable)).name)))),span))));
continue;
}

}
else {
(maybe_checked_expr = ((param).default_value));
if ((((args).size()) > consumed_arg)){
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> const name_span_expr_ = ((args)[consumed_arg]);
String const name = ((name_span_expr_).get<0>());
utility::Span const span = ((name_span_expr_).get<1>());
NonnullRefPtr<parser::ParsedExpression> const expr = ((name_span_expr_).get<2>());

if (TRY((((*this).validate_argument_label(param,name,span,expr,maybe_checked_expr))))){
(maybe_checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,((((param).variable)).type_id))))));
((consumed_arg++));
}
}
}

if (((maybe_checked_expr).has_value())){
NonnullRefPtr<types::CheckedExpression> checked_arg = (maybe_checked_expr.value());
TRY((((resolved_args).push((Tuple{((((param).variable)).name), span, checked_arg})))));
}
}

}
}

return (resolved_args);
}
else {
TRY((((*this).error(String("Wrong number of arguments"),span))));
return ((TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>>>::create_with({})))));
}

}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_generic_arguments_method_call(NonnullRefPtr<types::CheckedExpression> const checked_expr,parser::ParsedCall const call,types::ScopeId const scope_id,utility::Span const span,bool const is_optional,types::SafetyMode const safety_mode) {
{
JaktInternal::Array<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> checked_args = (TRY((Array<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>>::create_with({}))));
TRY((((checked_args).ensure_capacity(((((call).args)).size())))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> name_____expr__ = (_magic_value.value());
{
JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> const jakt__name_____expr__ = name_____expr__;
String const name = ((jakt__name_____expr__).get<0>());
utility::Span const _ = ((jakt__name_____expr__).get<1>());
NonnullRefPtr<parser::ParsedExpression> const expr = ((jakt__name_____expr__).get<2>());

NonnullRefPtr<types::CheckedExpression> const checked_arg_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((checked_args).push((Tuple{name, checked_arg_expr})))));
}

}
}

JaktInternal::Array<types::TypeId> checked_type_args = (TRY((Array<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedType>> _magic = ((((call).type_args)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<parser::ParsedType>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<parser::ParsedType> type_arg = (_magic_value.value());
{
TRY((((checked_type_args).push(TRY((((*this).typecheck_typename(type_arg,scope_id,JaktInternal::OptionalNone()))))))));
}

}
}

return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::MethodCall>(checked_expr,types::CheckedCall((TRY((Array<types::ResolvedNamespace>::create_with({})))),((call).name),checked_args,checked_type_args,JaktInternal::OptionalNone(),types::unknown_type_id(),false),span,is_optional,types::unknown_type_id()))));
}
}

ErrorOr<void> typechecker::Typechecker::check_that_type_doesnt_contain_reference(types::TypeId const type_id,utility::Span const span) {
{
NonnullRefPtr<types::Type> const type = ((*this).get_type(type_id));
bool const contains_reference = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
return JaktInternal::ExplicitValue(true);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
}/*switch end*/
}()
));
if (contains_reference){
TRY((((*this).error(TRY((String::formatted(String("Reference type ‘{}’ not usable in this context"),TRY((((*this).type_name(type_id))))))),span))));
}
}
return {};
}

types::CheckedEnum typechecker::Typechecker::get_enum(types::EnumId const id) const {
{
return (((((*this).program))->get_enum(id)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_function_predecl(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
JaktInternal::Array<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_function_predecl(child_namespace,child_namespace_scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((parsed_namespace).functions)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction fun = (_magic_value.value());
{
TRY((((*this).typecheck_function_predecl(fun,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
}

}
}

NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
types::ScopeId const record_scope_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_375; {
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
return JaktInternal::LoopContinue{};
}
__jakt_var_375 = ((((*this).get_struct((struct_id.value())))).scope_id); goto __jakt_label_351;

}
__jakt_label_351:; __jakt_var_375.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_376; {
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
return JaktInternal::LoopContinue{};
}
__jakt_var_376 = ((((*this).get_struct((struct_id.value())))).scope_id); goto __jakt_label_352;

}
__jakt_label_352:; __jakt_var_376.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_377; {
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
return JaktInternal::LoopContinue{};
}
__jakt_var_377 = ((((*this).get_enum((enum_id.value())))).scope_id); goto __jakt_label_353;

}
__jakt_label_353:; __jakt_var_377.release_value(); }));
};/*case end*/
}/*switch end*/
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
if (((!(((((record).generic_parameters)).is_empty()))) || (!(((((((method).parsed_function)).generic_parameters)).is_empty()))))){
NonnullRefPtr<types::CheckedFunction> func = ((*this).get_function((TRY((((*this).find_function_in_scope(record_scope_id,((((method).parsed_function)).name))))).value())));
types::ScopeId const method_scope_id = ((func)->function_scope_id);
types::ScopeId const check_scope = TRY((((*this).create_scope(method_scope_id,((func)->can_throw),TRY((String::formatted(String("method-checking({}::{})"),((record).name),((func)->name))))))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((func)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((*this).add_var_to_scope(check_scope,((((param).variable)).name),TRY((((module)->add_variable(((param).variable))))),((((param).variable)).definition_span)))));
}

}
}

bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::CheckedBlock const block = TRY((((*this).typecheck_block(((((method).parsed_function)).block),check_scope, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
types::TypeId const function_return_type_id = ((func)->return_type_id);
types::TypeId return_type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
if (((function_return_type_id).equals(types::unknown_type_id()))){
if ((!(((((block).statements)).is_empty())))){
if ((((((((block).statements)).last()).value()))->index() == 8 /* Return */)){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const val = ((((((block).statements)).last()).value())->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
(return_type_id = TRY((((*this).resolve_type_var((((val.value()))->type()),method_scope_id)))));
}
}
}
}
else {
(return_type_id = TRY((((*this).resolve_type_var(function_return_type_id,scope_id)))));
}

(((func)->block) = block);
(((func)->return_type_id) = return_type_id);
}
}

}
}

}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_constructor(parser::ParsedRecord const record,types::EnumId const enum_id,types::ScopeId const parent_scope_id) {
{
u64 next_constant_value = static_cast<u64>(0ULL);
JaktInternal::Set<String> seen_names = (TRY((Set<String>::create_with_values({}))));
types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
JaktInternal::Set<String> common_seen_fields = (TRY((Set<String>::create_with_values({}))));
JaktInternal::Array<types::VarId> common_fields = (TRY((Array<types::VarId>::create_with({}))));
JaktInternal::Array<types::CheckedParameter> common_params = (TRY((Array<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const variable = ((*this).get_variable(((field).variable_id)));
TRY((((common_params).push(types::CheckedParameter(true,variable,((field).default_value))))));
TRY((((common_seen_fields).add(((variable).name)))));
TRY((((common_fields).push(((field).variable_id)))));
}

}
}

JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();NonnullRefPtr<parser::ParsedType> const& underlying_type = __jakt_match_value.underlying_type;
JaktInternal::Array<parser::ValueEnumVariant> const& variants = __jakt_match_value.variants;
{
types::TypeId const underlying_type_id = TRY((((*this).typecheck_typename(underlying_type,parent_scope_id,JaktInternal::OptionalNone()))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<parser::ValueEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<parser::ValueEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ValueEnumVariant variant = (_magic_value.value());
{
if (((seen_names).contains(((variant).name)))){
TRY((((*this).error(TRY((String::formatted(String("Enum variant '{}' is defined more than once"),((variant).name)))),((variant).span)))));
}
else {
TRY((((seen_names).add(((variant).name)))));
NonnullRefPtr<types::CheckedExpression> const expr = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>,ErrorOr<void>>{
auto __jakt_enum_value = (((((variant).value)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_378; {
NonnullRefPtr<types::CheckedExpression> const value_expression = TRY((((*this).cast_to_underlying((((variant).value).value()),parent_scope_id,underlying_type))));
JaktInternal::Optional<types::NumberConstant> const number_constant = ((value_expression)->to_number_constant(((*this).program)));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>>{
auto __jakt_enum_value = (((number_constant).has_value()));
if (__jakt_enum_value == true) {
{
(next_constant_value = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<void>>{
auto&& __jakt_match_variant = (number_constant.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Signed>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>(((JaktInternal::checked_add<i64>(val,static_cast<i64>(1LL)))))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Unsigned>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue((JaktInternal::checked_add<u64>(val,static_cast<u64>(1ULL))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Floating>();
f64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<u64> __jakt_var_379; {
utility::todo(String("Implement floats"));
__jakt_var_379 = static_cast<u64>(0ULL); goto __jakt_label_355;

}
__jakt_label_355:; __jakt_var_379.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((*this).error(TRY((String::formatted(String("Enum variant '{}' in enum '{}' has a non-constant value: {}"),((variant).name),((enum_).name),value_expression))),((variant).span)))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
__jakt_var_378 = value_expression; goto __jakt_label_354;

}
__jakt_label_354:; __jakt_var_378.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).cast_to_underlying(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::NumericConstant>( parser::NumericConstant { typename parser::NumericConstant::U64(((next_constant_value++))) } ,((variant).span)))),parent_scope_id,underlying_type)))));
}
}()))
;
TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::WithValue(enum_id,((variant).name),expr,((variant).span)) } ))));
types::VarId const var_id = TRY((((module)->add_variable(types::CheckedVariable(((variant).name),((enum_).type_id),false,((variant).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } )))));
TRY((((*this).add_var_to_scope(((enum_).scope_id),((variant).name),var_id,((variant).span)))));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();bool const& is_boxed = __jakt_match_value.is_boxed;
JaktInternal::Array<parser::SumEnumVariant> const& variants = __jakt_match_value.variants;
{
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<parser::SumEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<parser::SumEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::SumEnumVariant variant = (_magic_value.value());
{
if (((seen_names).contains(((variant).name)))){
TRY((((*this).error(TRY((String::formatted(String("Enum variant '{}' is defined more than once"),((variant).name)))),((variant).span)))));
continue;
}
TRY((((seen_names).add(((variant).name)))));
bool const is_structlike = ((((((variant).params)).has_value()) && ((((((variant).params).value())).size()) > static_cast<size_t>(0ULL))) && ((((((((variant).params).value()))[static_cast<i64>(0LL)])).name) != String("")));
bool const is_typed = ((((((variant).params)).has_value()) && ((((((variant).params).value())).size()) == static_cast<size_t>(1ULL))) && ((((((((variant).params).value()))[static_cast<i64>(0LL)])).name) == String("")));
if (is_structlike){
JaktInternal::Set<String> seen_fields = (TRY((Set<String>::create_with_values({}))));
{
JaktInternal::SetIterator<String> _magic = ((common_seen_fields).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
TRY((((seen_fields).add(name))));
}

}
}

JaktInternal::Array<types::CheckedParameter> params = (TRY((Array<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((common_params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((params).push(param))));
}

}
}

JaktInternal::Array<types::VarId> fields = (TRY((Array<types::VarId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((common_fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
TRY((((fields).push(field))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedVarDecl> _magic = (((((variant).params).value())).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedVarDecl> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedVarDecl param = (_magic_value.value());
{
if (((seen_fields).contains(((param).name)))){
TRY((((*this).error(TRY((String::formatted(String("Enum variant '{}' has a member named '{}' more than once"),((variant).name),((param).name)))),((param).span)))));
continue;
}
TRY((((seen_fields).add(((param).name)))));
types::TypeId const type_id = TRY((((*this).typecheck_typename(((param).parsed_type),((enum_).scope_id),((param).name)))));
types::CheckedVariable const checked_var = types::CheckedVariable(((param).name),type_id,((param).is_mutable),((param).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((params).push(types::CheckedParameter(true,checked_var,JaktInternal::OptionalNone())))));
if ((((*this).dump_type_hints) && ((((param).parsed_type))->index() == 13 /* Empty */))){
TRY((((*this).dump_type_hint(type_id,((param).span)))));
}
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const var_id = TRY((((module)->add_variable(checked_var))));
TRY((((fields).push(var_id))));
}

}
}

TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::StructLike(enum_id,((variant).name),fields,((variant).span)) } ))));
JaktInternal::Optional<types::FunctionId> const maybe_enum_variant_constructor = TRY((((*this).find_function_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
bool const can_function_throw = is_boxed;
types::ScopeId const function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor({}::{})"),((enum_).name),((variant).name))))))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor-block({}::{})"),((enum_).name),((variant).name))))))));
NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),params,TRY((types::FunctionGenerics::create(function_scope_id,params,(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false)));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),((variant).name),function_id,((variant).span)))));
}
}
else if (is_typed){
JaktInternal::Array<types::CheckedParameter> params = (TRY((Array<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((common_params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((params).push(param))));
}

}
}

parser::ParsedVarDecl const param = (((((variant).params).value()))[static_cast<i64>(0LL)]);
types::TypeId const type_id = TRY((((*this).typecheck_typename(((param).parsed_type),((enum_).scope_id),((param).name)))));
TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::Typed(enum_id,((variant).name),type_id,((variant).span)) } ))));
JaktInternal::Optional<types::FunctionId> const maybe_enum_variant_constructor = TRY((((*this).find_function_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
bool const can_function_throw = is_boxed;
types::ScopeId const function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor({}::{})"),((enum_).name),((variant).name))))))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor-block({}::{})"),((enum_).name),((variant).name))))))));
types::CheckedVariable const variable = types::CheckedVariable(String("value"),type_id,false,((param).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((params).push(types::CheckedParameter(false,variable,JaktInternal::OptionalNone())))));
NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),params,TRY((types::FunctionGenerics::create(function_scope_id,params,(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } ,types::TypeId::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false)));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),((variant).name),function_id,((variant).span)))));
}
}
else {
JaktInternal::Array<types::CheckedParameter> params = (TRY((Array<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((common_params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((params).push(param))));
}

}
}

TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::Untyped(enum_id,((variant).name),((variant).span)) } ))));
JaktInternal::Optional<types::FunctionId> const maybe_enum_variant_constructor = TRY((((*this).find_function_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
bool const can_function_throw = is_boxed;
types::ScopeId const function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor({}::{})"),((enum_).name),((variant).name))))))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor-block({}::{})"),((enum_).name),((variant).name))))))));
NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),params,TRY((types::FunctionGenerics::create(function_scope_id,params,(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } ,types::TypeId::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false)));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),((variant).name),function_id,((variant).span)))));
}
}

}

}
}

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
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_constructor(parser::ParsedRecord const parsed_record,types::StructId const struct_id,types::ScopeId const scope_id) {
{
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
types::CheckedStruct const struct_ = ((*this).get_struct(struct_id));
JaktInternal::Optional<types::FunctionId> const constructor_id = TRY((((*this).find_function_in_scope(((struct_).scope_id),((parsed_record).name)))));
if (((constructor_id).has_value())){
if ((((((parsed_record).record_type)).index() == 1 /* Class */) && ((((parsed_record).definition_linkage)).index() == 1 /* External */))){
NonnullRefPtr<types::CheckedFunction> func = ((*this).get_function((constructor_id.value())));
(((func)->linkage) =  parser::FunctionLinkage { typename parser::FunctionLinkage::External() } );
}
}
else if ((!(((((parsed_record).definition_linkage)).index() == 1 /* External */)))){
bool const constructor_can_throw = ((((parsed_record).record_type)).index() == 1 /* Class */);
types::ScopeId const function_scope_id = TRY((((*this).create_scope(((struct_).scope_id),constructor_can_throw,TRY((String::formatted(String("generated-constructor({})"),((parsed_record).name))))))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,constructor_can_throw,TRY((String::formatted(String("generated-constructor-block({})"),((parsed_record).name))))))));
NonnullRefPtr<types::CheckedFunction> checked_constructor = TRY((types::CheckedFunction::create(((parsed_record).name),((parsed_record).name_span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,struct_type_id,JaktInternal::OptionalNone(),(TRY((Array<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::create(function_scope_id,(TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::TypeId::none(),false),constructor_can_throw, parser::FunctionType { typename parser::FunctionType::ImplicitConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,struct_id,true,JaktInternal::OptionalNone(),false,false,false)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const function_id = TRY((((module)->add_function(checked_constructor))));
JaktInternal::Array<types::StructId> const inheritance_chain = TRY((((*this).struct_inheritance_chain(struct_id))));
NonnullRefPtr<types::CheckedFunction> func = (((((module)->functions)).last()).value());
{
JaktInternal::ArrayIterator<types::StructId> _magic = ((inheritance_chain).iterator());
for (;;){
JaktInternal::Optional<types::StructId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::StructId field_struct_id = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((((*this).get_struct(field_struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const variable = ((*this).get_variable(((field).variable_id)));
TRY((((func)->add_param(types::CheckedParameter(true,variable,((field).default_value))))));
}

}
}

}

}
}

TRY((((*this).add_function_to_scope(((struct_).scope_id),((parsed_record).name),function_id,((parsed_record).name_span)))));
}
(((*this).current_struct_type_id) = JaktInternal::OptionalNone());
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_var_decl(parser::ParsedVarDecl const var,NonnullRefPtr<parser::ParsedExpression> const init,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
types::TypeId lhs_type_id = TRY((((*this).typecheck_typename(((var).parsed_type),scope_id,((var).name)))));
NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(init,scope_id,safety_mode,lhs_type_id))));
types::TypeId const rhs_type_id = ((checked_expr)->type());
if (((rhs_type_id).equals(types::void_type_id()))){
TRY((((*this).error(String("Cannot assign `void` to a variable"),((checked_expr)->span())))));
}
if ((((lhs_type_id).equals(types::unknown_type_id())) && (!(((rhs_type_id).equals(types::unknown_type_id())))))){
(lhs_type_id = rhs_type_id);
}
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
NonnullRefPtr<types::Type> const lhs_type = ((*this).get_type(lhs_type_id));
TRY((((*this).check_that_type_doesnt_contain_reference(lhs_type_id,span))));
if (((checked_expr)->index() == 23 /* OptionalNone */)){
utility::Span const span = (checked_expr->get<types::CheckedExpression::OptionalNone>()).span;
types::TypeId const type_id = (checked_expr->get<types::CheckedExpression::OptionalNone>()).type_id;
if (((lhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = (lhs_type->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (lhs_type->get<types::Type::GenericInstance>()).args;
if ((!((((id).equals(optional_struct_id)) || ((id).equals(weak_ptr_struct_id)))))){
TRY((((*this).error(String("Cannot assign None to a non-optional type"),span))));
}
}
else {
TRY((((*this).error(String("Cannot assign None to a non-optional type"),span))));
}

}
if (((lhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = (lhs_type->get<types::Type::GenericInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (lhs_type->get<types::Type::GenericInstance>()).args;
if (((id).equals(weak_ptr_struct_id))){
if ((!(((var).is_mutable)))){
TRY((((*this).error(String("Weak reference must be mutable"),((var).span)))));
}
if (((!(((lhs_type_id).equals(rhs_type_id)))) && ((!(((((args)[static_cast<i64>(0LL)])).equals(rhs_type_id)))) && (!(((rhs_type_id).equals(types::unknown_type_id()))))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),((checked_expr)->span())))));
}
}
else if (((id).equals(optional_struct_id))){
if (((!(((lhs_type_id).equals(rhs_type_id)))) && ((!(((((args)[static_cast<i64>(0LL)])).equals(rhs_type_id)))) && (!(((rhs_type_id).equals(types::unknown_type_id()))))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),((checked_expr)->span())))));
}
}
else {
if (((!(((lhs_type_id).equals(rhs_type_id)))) && (!(((rhs_type_id).equals(types::unknown_type_id())))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),((checked_expr)->span())))));
}
}

}
else if (((lhs_type)->is_builtin())){
JaktInternal::Optional<types::NumberConstant> const number_constant = ((checked_expr)->to_number_constant(((*this).program)));
bool is_rhs_zero = false;
if (((number_constant).has_value())){
(is_rhs_zero = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<NonnullRefPtr<types::CheckedStatement>>>{
auto&& __jakt_match_variant = (number_constant.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Signed>();
i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((value == static_cast<i64>(0LL)));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Unsigned>();
u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((value == static_cast<u64>(0ULL)));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Floating>();
f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((value == static_cast<f64>(0)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
if (((!((((*this).is_numeric(lhs_type_id)) && is_rhs_zero))) && (((*this).is_integer(lhs_type_id)) ^ ((*this).is_integer(rhs_type_id))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),((checked_expr)->span())))));
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Garbage>(span))));
}
}
else {
if (((!(((lhs_type_id).equals(rhs_type_id)))) && (!(((rhs_type_id).equals(types::unknown_type_id())))))){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(rhs_type_id))))))),((checked_expr)->span())))));
}
}

types::CheckedVariable const checked_var = types::CheckedVariable(((var).name),lhs_type_id,((var).is_mutable),((var).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
if ((((*this).dump_type_hints) && ((((var).inlay_span)).has_value()))){
TRY((((*this).dump_type_hint(lhs_type_id,(((var).inlay_span).value())))));
}
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const var_id = TRY((((module)->add_variable(checked_var))));
TRY((((*this).add_var_to_scope(scope_id,((var).name),var_id,((checked_var).definition_span)))));
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::VarDecl>(var_id,checked_expr,span))));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>>> typechecker::Typechecker::typecheck_enum_variant_bindings(types::CheckedEnumVariant const variant,JaktInternal::Array<parser::EnumVariantPatternArgument> const bindings,utility::Span const span) {
{
if (((variant).index() == 1 /* Typed */)){
types::TypeId const type_id = (variant.get<types::CheckedEnumVariant::Typed>()).type_id;
if ((((bindings).size()) != static_cast<size_t>(1ULL))){
TRY((((*this).error(TRY((String::formatted(String("Enum variant ‘{}’ must have exactly one argument"),((variant).name())))),span))));
return (JaktInternal::OptionalNone());
}
return ((TRY((Array<types::CheckedEnumVariantBinding>::create_with({types::CheckedEnumVariantBinding(JaktInternal::OptionalNone(),((((bindings)[static_cast<i64>(0LL)])).binding),type_id,span)})))));
}
if (((variant).index() == 3 /* StructLike */)){
JaktInternal::Array<types::VarId> const fields = (variant.get<types::CheckedEnumVariant::StructLike>()).fields;
JaktInternal::Array<types::CheckedVariable> checked_vars = (TRY((Array<types::CheckedVariable>::create_with({}))));
JaktInternal::Array<types::CheckedEnumVariantBinding> checked_enum_variant_bindings = (TRY((Array<types::CheckedEnumVariantBinding>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
TRY((((checked_vars).push(((*this).get_variable(field))))));
}

}
}

{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((bindings).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument binding = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<types::CheckedVariable> _magic = ((checked_vars).iterator());
for (;;){
JaktInternal::Optional<types::CheckedVariable> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedVariable var = (_magic_value.value());
{
String const binding_name = ((binding).name).value_or_lazy_evaluated([&] { return ((binding).binding); });
types::TypeId const type_id = ((var).type_id);
if ((binding_name == ((var).name))){
TRY((((checked_enum_variant_bindings).push(types::CheckedEnumVariantBinding(((binding).name),((binding).binding),type_id,span)))));
break;
}
}

}
}

}

}
}

if ((((checked_enum_variant_bindings).size()) > static_cast<size_t>(0ULL))){
return (checked_enum_variant_bindings);
}
return (JaktInternal::OptionalNone());
}
else {
return (JaktInternal::OptionalNone());
}

}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_imports(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
{
JaktInternal::ArrayIterator<parser::ParsedModuleImport> _magic = ((((parsed_namespace).module_imports)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedModuleImport> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedModuleImport module_import = (_magic_value.value());
{
TRY((((*this).typecheck_module_import(module_import,scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedExternImport> _magic = ((((parsed_namespace).extern_imports)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedExternImport> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedExternImport extern_import = (_magic_value.value());
{
TRY((((*this).typecheck_extern_import(extern_import,scope_id))));
}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum(parser::ParsedRecord const record,types::EnumId const enum_id,types::ScopeId const parent_scope_id) {
{
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
TRY((((*this).typecheck_method(((method).parsed_function), types::StructOrEnumId { typename types::StructOrEnumId::Enum(enum_id) } ))));
}

}
}

}
return {};
}

ErrorOr<bool> typechecker::Typechecker::implements_trait(types::TypeId const type_id,types::TraitId const trait_id,JaktInternal::Optional<JaktInternal::Array<types::TypeId>> const generic_arguments) {
{
Function<ErrorOr<bool>(JaktInternal::Array<JaktInternal::Array<types::TypeId>>, types::TraitId, JaktInternal::Array<types::TypeId>, typechecker::Typechecker&)> const has_matching_trait = [](JaktInternal::Array<JaktInternal::Array<types::TypeId>> trait_implementations, types::TraitId trait_id, JaktInternal::Array<types::TypeId> passed_generic_arguments, typechecker::Typechecker& typechecker) -> ErrorOr<bool> {
bool const old_ignore_errors = ((((typechecker))).ignore_errors);
(((((typechecker))).ignore_errors) = true);
ScopeGuard __jakt_var_380([&] {
{
(((((typechecker))).ignore_errors) = old_ignore_errors);
}

});
bool found = false;
{
JaktInternal::ArrayIterator<JaktInternal::Array<types::TypeId>> _magic = ((trait_implementations).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Array<types::TypeId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Array<types::TypeId> implemented_generic_arguments = (_magic_value.value());
{
if ((((implemented_generic_arguments).size()) != ((passed_generic_arguments).size()))){
continue;
}
bool ok = false;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((implemented_generic_arguments).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(ok = TRY((((((typechecker))).check_types_for_compat(((implemented_generic_arguments)[i]),((passed_generic_arguments)[i]),((((((typechecker))).generic_inferences))),utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)))))));
if ((!(ok))){
break;
}
}

}
}

if ((!(ok))){
continue;
}
(found = true);
break;
}

}
}

return (found);
}
;
JaktInternal::Array<types::TypeId> const empty = (TRY((Array<types::TypeId>::create_with({}))));
return (TRY((has_matching_trait(TRY((((*this).find_all_implementations_of_trait(type_id,trait_id)))),trait_id,generic_arguments.value_or_lazy_evaluated([&] { return empty; }),((*this))))));
}
}

ErrorOr<types::CheckedParameter> typechecker::Typechecker::typecheck_parameter(parser::ParsedParameter const parameter,types::ScopeId const scope_id,bool const first,JaktInternal::Optional<types::TypeId> const this_arg_type_id,JaktInternal::Optional<types::ScopeId> const check_scope) {
{
types::TypeId type_id = TRY((((*this).typecheck_typename(((((parameter).variable)).parsed_type),scope_id,((((parameter).variable)).name)))));
if ((first && (((((parameter).variable)).name) == String("this")))){
if (((this_arg_type_id).has_value())){
(type_id = (this_arg_type_id.value()));
}
}
types::CheckedVariable const variable = types::CheckedVariable(((((parameter).variable)).name),type_id,((((parameter).variable)).is_mutable),((((parameter).variable)).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_default_value = JaktInternal::OptionalNone();
if (((((parameter).default_argument)).has_value())){
NonnullRefPtr<types::CheckedExpression> checked_default_value_expr = TRY((((*this).typecheck_expression((((parameter).default_argument).value()),scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,type_id))));
if (((checked_default_value_expr)->index() == 23 /* OptionalNone */)){
utility::Span const expr_span = (checked_default_value_expr->get<types::CheckedExpression::OptionalNone>()).span;
(checked_default_value_expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::OptionalNone>(expr_span,type_id))));
}
types::TypeId const default_value_type_id = ((checked_default_value_expr)->type());
(checked_default_value = checked_default_value_expr);
if ((!(TRY((((*this).check_types_for_compat(type_id,default_value_type_id,((((*this).generic_inferences))),((checked_default_value_expr)->span())))))))){
(checked_default_value = JaktInternal::OptionalNone());
}
}
types::CheckedParameter const checked_parameter = types::CheckedParameter(((parameter).requires_label),variable,checked_default_value);
if (((check_scope).has_value())){
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const var_id = TRY((((module)->add_variable(variable))));
TRY((((*this).add_var_to_scope((check_scope.value()),((((parameter).variable)).name),var_id,((((parameter).variable)).span)))));
}
return (checked_parameter);
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct(parser::ParsedRecord const record,types::StructId const struct_id,types::ScopeId const parent_scope_id) {
{
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
JaktInternal::Dictionary<String,NonnullRefPtr<types::CheckedFunction>> all_virtuals = (TRY((Dictionary<String, NonnullRefPtr<types::CheckedFunction>>::create_with_entries({}))));
JaktInternal::Optional<types::StructId> super_struct_id = ((((*this).get_struct(struct_id))).super_struct_id);
while (((super_struct_id).has_value())){
types::CheckedStruct const super_struct = ((*this).get_struct((super_struct_id.value())));
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(((super_struct).scope_id)))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> function_tuple = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function_ = ((*this).get_function(((function_tuple).get<1>())));
if (((function_)->is_virtual)){
TRY(all_virtuals.set(((function_)->name), function_));
}
}

}
}

(super_struct_id = ((super_struct).super_struct_id));
}
typechecker::TraitImplCheck checks = TRY((typechecker::TraitImplCheck::TraitImplCheck::make()));
{
JaktInternal::Dictionary<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const trait_implementations = ((((*this).get_struct(struct_id))).trait_implementations);
TRY((((checks).ensure_capacity(((trait_implementations).size())))));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> _magic = ((trait_implementations).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> trait_name__trait_id_and_generic_params__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const jakt__trait_name__trait_id_and_generic_params__ = trait_name__trait_id_and_generic_params__;
String const trait_name = ((jakt__trait_name__trait_id_and_generic_params__).get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>> const trait_id_and_generic_params = ((jakt__trait_name__trait_id_and_generic_params__).get<1>());

TRY((((checks).register_trait(((trait_id_and_generic_params).get<0>()),trait_name,((((((*this).program))->get_trait(((trait_id_and_generic_params).get<0>()))))->methods)))));
}

}
}

}

{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if (((method).is_override)){
if ((!(((all_virtuals).contains(((((method).parsed_function)).name)))))){
TRY((((*this).error(String("Missing virtual for override"),((((method).parsed_function)).name_span)))));
}
}
else if (((all_virtuals).contains(((((method).parsed_function)).name)))){
TRY((((*this).error(String("Missing override keyword on function that is virtual"),((((method).parsed_function)).name_span)))));
}
TRY((((*this).typecheck_method(((method).parsed_function), types::StructOrEnumId { typename types::StructOrEnumId::Struct(struct_id) } ))));
}

}
}

{
JaktInternal::Dictionary<String,String> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
ScopeGuard __jakt_var_381([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
JaktInternal::Dictionary<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const trait_implementations = ((((*this).get_struct(struct_id))).trait_implementations);
TRY((((checks).ensure_capacity(((trait_implementations).size())))));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> _magic = ((trait_implementations).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> trait_name__trait_id_and_generic_params__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>> const jakt__trait_name__trait_id_and_generic_params__ = trait_name__trait_id_and_generic_params__;
String const trait_name = ((jakt__trait_name__trait_id_and_generic_params__).get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>> const trait_id_and_generic_params = ((jakt__trait_name__trait_id_and_generic_params__).get<1>());

JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>> const trait_id_generic_params_ = trait_id_and_generic_params;
types::TraitId const trait_id = ((trait_id_generic_params_).get<0>());
JaktInternal::Array<types::TypeId> const generic_params = ((trait_id_generic_params_).get<1>());

NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait(trait_id));
if ((((((trait_)->generic_parameters)).size()) != ((generic_params).size()))){
TRY((((*this).error(TRY((String::formatted(String("Trait ‘{}’ expects {} generic parameters, but {} were given"),trait_name,((((trait_)->generic_parameters)).size()),((generic_params).size())))),((trait_)->name_span)))));
continue;
}
TRY((((*this).specialize_trait(trait_id,generic_params))));
}

}
}

NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(((((*this).get_struct(struct_id))).scope_id)))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
String const name = ((jakt__name__function_id__).get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).get<1>());

TRY((((checks).register_method(name,function_id,((*this))))));
}

}
}

}

TRY((((checks).throw_errors(((((*this).get_struct(struct_id))).name_span),((*this))))));
(((*this).current_struct_type_id) = JaktInternal::OptionalNone());
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_predecl_initial(parser::ParsedRecord const parsed_record,size_t const struct_index,size_t const module_struct_len,types::ScopeId const scope_id) {
{
types::ModuleId const module_id = ((*this).current_module_id);
types::StructId const struct_id = types::StructId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(struct_index,module_struct_len)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
types::TypeId const struct_type_id = types::TypeId(module_id,(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((*this).add_type_to_scope(scope_id,((parsed_record).name),struct_type_id,((parsed_record).name_span)))));
types::ScopeId const struct_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((String::formatted(String("struct({})"),((parsed_record).name))))))));
TRY((((((module)->structures)).push(types::CheckedStruct(((parsed_record).name),((parsed_record).name_span),(TRY((Array<types::CheckedGenericParameter>::create_with({})))),(TRY((Array<types::CheckedField>::create_with({})))),struct_scope_id,((parsed_record).definition_linkage),(TRY((Dictionary<String, JaktInternal::Tuple<types::TraitId,JaktInternal::Array<types::TypeId>>>::create_with_entries({})))),((parsed_record).record_type),struct_type_id,JaktInternal::OptionalNone())))));
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_match(NonnullRefPtr<parser::ParsedExpression> const expr,JaktInternal::Array<parser::ParsedMatchCase> const cases,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
NonnullRefPtr<types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const subject_type_id = ((checked_expr)->type());
NonnullRefPtr<types::Type> const type_to_match_on = ((*this).get_type(subject_type_id));
JaktInternal::Array<types::CheckedMatchCase> checked_cases = (TRY((Array<types::CheckedMatchCase>::create_with({}))));
JaktInternal::Dictionary<String,String> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_382([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
JaktInternal::Optional<types::TypeId> final_result_type = JaktInternal::OptionalNone();
if ((((type_hint).has_value()) && ((!((((type_hint.value())).equals(types::unknown_type_id())))) && (!(((((*this).get_type((type_hint.value()))))->index() == 18 /* TypeVariable */)))))){
(final_result_type = type_hint);
}
if (((type_to_match_on)->index() == 20 /* GenericEnumInstance */)){
types::EnumId const id = (type_to_match_on->get<types::Type::GenericEnumInstance>()).id;
JaktInternal::Array<types::TypeId> const args = (type_to_match_on->get<types::Type::GenericEnumInstance>()).args;
types::CheckedEnum const enum_ = ((*this).get_enum(id));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
String const generic = TRY((((((((((enum_).generic_parameters))[i])).type_id)).to_string())));
String const argument_type = TRY((((((args)[i])).to_string())));
if ((generic != argument_type)){
TRY((((((*this).generic_inferences)).set(generic,argument_type))));
}
}

}
}

}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type_to_match_on;
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
bool seen_catch_all = false;
bool expanded_catch_all = false;
JaktInternal::Optional<utility::Span> catch_all_span = JaktInternal::OptionalNone();
JaktInternal::Set<String> covered_variants = (TRY((Set<String>::create_with_values({}))));
size_t const case_count = ((cases).size());
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<parser::ParsedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchCase case_ = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<parser::ParsedMatchPattern> _magic = ((((case_).patterns)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchPattern> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchPattern pattern = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::EnumVariant>();JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>> variant_names_ = variant_names;
if ((((variant_names_).size()) == static_cast<size_t>(1ULL))){
JaktInternal::Tuple<String,utility::Span> const temp = ((variant_names_)[static_cast<i64>(0LL)]);
(variant_names_ = (TRY((Array<JaktInternal::Tuple<String,utility::Span>>::create_with({(Tuple{((enum_).name), ((((variant_names_)[static_cast<i64>(0LL)])).get<1>())}), temp})))));
}
if (((variant_names_).is_empty())){
return JaktInternal::LoopContinue{};
}
if ((((((variant_names_)[static_cast<i64>(0LL)])).get<0>()) != ((enum_).name))){
TRY((((*this).error(TRY((String::formatted(String("Match case '{}' does not match enum '{}'"),((((variant_names_)[static_cast<i64>(0LL)])).get<0>()),((enum_).name)))),((((variant_names_)[static_cast<i64>(0LL)])).get<1>())))));
return JaktInternal::LoopContinue{};
}
size_t i = static_cast<size_t>(0ULL);
JaktInternal::Optional<types::CheckedEnumVariant> matched_variant = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> variant_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant v = (_magic_value.value());
{
if ((((v).name()) == ((((variant_names_)[static_cast<i64>(1LL)])).get<0>()))){
(matched_variant = v);
(variant_index = i);
}
((i++));
}

}
}

if ((!(((matched_variant).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Enum '{}' does not contain a variant named '{}'"),((enum_).name),((((variant_names_)[static_cast<i64>(1LL)])).get<0>())))),((case_).marker_span)))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Match>(checked_expr,(TRY((Array<types::CheckedMatchCase>::create_with({})))),span,types::unknown_type_id(),false))));
}
JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> const covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,(variant_index.value()),final_result_type,(matched_variant.value()),variant_arguments,arguments_span,scope_id,safety_mode))));
JaktInternal::Optional<String> const covered_name = ((covered_name_checked_match_case_result_type_).get<0>());
types::CheckedMatchCase const checked_match_case = ((covered_name_checked_match_case_result_type_).get<1>());
JaktInternal::Optional<types::TypeId> const result_type = ((covered_name_checked_match_case_result_type_).get<2>());

if (((covered_name).has_value())){
TRY((((covered_variants).add((covered_name.value())))));
}
(final_result_type = result_type);
TRY((((checked_cases).push(checked_match_case))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::CatchAll>();JaktInternal::Array<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if ((current_case_index != (JaktInternal::checked_sub<size_t>(case_count,static_cast<size_t>(1ULL))))){
TRY((((*this).error(String("Match else case is only allowed as the last case"),((case_).marker_span)))));
}
if (seen_catch_all){
TRY((((*this).error(String("Multiple catch-all cases in match are not allowed"),((case_).marker_span)))));
}
else {
(seen_catch_all = true);
}

if ((((variant_arguments).size()) > static_cast<size_t>(0ULL))){
size_t variant_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if ((!(((covered_variants).contains(((variant).name())))))){
(expanded_catch_all = true);
JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> const covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,variant_index,final_result_type,variant,variant_arguments,arguments_span,scope_id,safety_mode))));
JaktInternal::Optional<String> const covered_name = ((covered_name_checked_match_case_result_type_).get<0>());
types::CheckedMatchCase const checked_match_case = ((covered_name_checked_match_case_result_type_).get<1>());
JaktInternal::Optional<types::TypeId> const result_type = ((covered_name_checked_match_case_result_type_).get<2>());

if (((covered_name).has_value())){
TRY((((covered_variants).add((covered_name.value())))));
}
(final_result_type = result_type);
TRY((((checked_cases).push(checked_match_case))));
}
((variant_index++));
}

}
}

}
else {
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),String("catch-all")))));
JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll(false,checked_body,((case_).marker_span)) } ;
TRY((((checked_cases).push(checked_match_case))));
}

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
}

}
}

((current_case_index++));
}

}
}

JaktInternal::Array<String> enum_variant_names = (TRY((Array<String>::create_with({}))));
JaktInternal::Array<String> missing_variants = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
TRY((((enum_variant_names).push(((variant).name())))));
}

}
}

{
JaktInternal::ArrayIterator<String> _magic = ((enum_variant_names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String variant = (_magic_value.value());
{
if ((!(((covered_variants).contains(variant))))){
TRY((((missing_variants).push(variant))));
}
}

}
}

if ((((missing_variants).size()) > static_cast<size_t>(0ULL))){
if ((!(seen_catch_all))){
TRY((((*this).error(TRY((String::formatted(String("Match expression is not exhaustive, missing variants are: {}"),utility::join(missing_variants,String(", "))))),span))));
}
}
else if ((seen_catch_all && (!(expanded_catch_all)))){
TRY((((*this).error(String("All variants are covered, but an irrefutable pattern is also present"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
bool seen_catch_all = false;
bool expanded_catch_all = false;
JaktInternal::Optional<utility::Span> catch_all_span = JaktInternal::OptionalNone();
JaktInternal::Set<String> covered_variants = (TRY((Set<String>::create_with_values({}))));
size_t const case_count = ((cases).size());
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<parser::ParsedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchCase case_ = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<parser::ParsedMatchPattern> _magic = ((((case_).patterns)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchPattern> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchPattern pattern = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::EnumVariant>();JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>> variant_names_ = variant_names;
if ((((variant_names_).size()) == static_cast<size_t>(1ULL))){
JaktInternal::Tuple<String,utility::Span> const temp = ((variant_names_)[static_cast<i64>(0LL)]);
(variant_names_ = (TRY((Array<JaktInternal::Tuple<String,utility::Span>>::create_with({(Tuple{((enum_).name), ((((variant_names_)[static_cast<i64>(0LL)])).get<1>())}), temp})))));
}
if (((variant_names_).is_empty())){
return JaktInternal::LoopContinue{};
}
if ((((((variant_names_)[static_cast<i64>(0LL)])).get<0>()) != ((enum_).name))){
TRY((((*this).error(TRY((String::formatted(String("Match case '{}' does not match enum '{}'"),((((variant_names_)[static_cast<i64>(0LL)])).get<0>()),((enum_).name)))),((((variant_names_)[static_cast<i64>(0LL)])).get<1>())))));
return JaktInternal::LoopContinue{};
}
size_t i = static_cast<size_t>(0ULL);
JaktInternal::Optional<types::CheckedEnumVariant> matched_variant = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> variant_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant v = (_magic_value.value());
{
if ((((v).name()) == ((((variant_names_)[static_cast<i64>(1LL)])).get<0>()))){
(matched_variant = v);
(variant_index = i);
}
((i++));
}

}
}

if ((!(((matched_variant).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Enum '{}' does not contain a variant named '{}'"),((enum_).name),((((variant_names_)[static_cast<i64>(1LL)])).get<0>())))),((case_).marker_span)))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Match>(checked_expr,(TRY((Array<types::CheckedMatchCase>::create_with({})))),span,types::unknown_type_id(),false))));
}
JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> const covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,(variant_index.value()),final_result_type,(matched_variant.value()),variant_arguments,arguments_span,scope_id,safety_mode))));
JaktInternal::Optional<String> const covered_name = ((covered_name_checked_match_case_result_type_).get<0>());
types::CheckedMatchCase const checked_match_case = ((covered_name_checked_match_case_result_type_).get<1>());
JaktInternal::Optional<types::TypeId> const result_type = ((covered_name_checked_match_case_result_type_).get<2>());

if (((covered_name).has_value())){
TRY((((covered_variants).add((covered_name.value())))));
}
(final_result_type = result_type);
TRY((((checked_cases).push(checked_match_case))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::CatchAll>();JaktInternal::Array<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if ((current_case_index != (JaktInternal::checked_sub<size_t>(case_count,static_cast<size_t>(1ULL))))){
TRY((((*this).error(String("Match else case is only allowed as the last case"),((case_).marker_span)))));
}
if (seen_catch_all){
TRY((((*this).error(String("Multiple catch-all cases in match are not allowed"),((case_).marker_span)))));
}
else {
(seen_catch_all = true);
}

if ((((variant_arguments).size()) > static_cast<size_t>(0ULL))){
size_t variant_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if ((!(((covered_variants).contains(((variant).name())))))){
(expanded_catch_all = true);
JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> const covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,variant_index,final_result_type,variant,variant_arguments,arguments_span,scope_id,safety_mode))));
JaktInternal::Optional<String> const covered_name = ((covered_name_checked_match_case_result_type_).get<0>());
types::CheckedMatchCase const checked_match_case = ((covered_name_checked_match_case_result_type_).get<1>());
JaktInternal::Optional<types::TypeId> const result_type = ((covered_name_checked_match_case_result_type_).get<2>());

if (((covered_name).has_value())){
TRY((((covered_variants).add((covered_name.value())))));
}
(final_result_type = result_type);
TRY((((checked_cases).push(checked_match_case))));
}
((variant_index++));
}

}
}

}
else {
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),String("catch-all")))));
JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll(false,checked_body,((case_).marker_span)) } ;
TRY((((checked_cases).push(checked_match_case))));
}

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
}

}
}

((current_case_index++));
}

}
}

JaktInternal::Array<String> enum_variant_names = (TRY((Array<String>::create_with({}))));
JaktInternal::Array<String> missing_variants = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
TRY((((enum_variant_names).push(((variant).name())))));
}

}
}

{
JaktInternal::ArrayIterator<String> _magic = ((enum_variant_names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String variant = (_magic_value.value());
{
if ((!(((covered_variants).contains(variant))))){
TRY((((missing_variants).push(variant))));
}
}

}
}

if ((((missing_variants).size()) > static_cast<size_t>(0ULL))){
if ((!(seen_catch_all))){
TRY((((*this).error(TRY((String::formatted(String("Match expression is not exhaustive, missing variants are: {}"),utility::join(missing_variants,String(", "))))),span))));
}
}
else if ((seen_catch_all && (!(expanded_catch_all)))){
TRY((((*this).error(String("All variants are covered, but an irrefutable pattern is also present"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Void>();
{
TRY((((*this).error(String("Can't match on 'void' type"),((checked_expr)->span())))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
bool is_enum_match = false;
bool is_value_match = false;
bool seen_catch_all = false;
bool all_variants_constant = true;
size_t const case_count = ((cases).size());
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<parser::ParsedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchCase case_ = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<parser::ParsedMatchPattern> _magic = ((((case_).patterns)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchPattern> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchPattern pattern = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::EnumVariant>();JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if (is_value_match){
TRY((((*this).error(String("Cannot have an enum match case in a match expression containing value matches"),((case_).marker_span)))));
}
if ((((variant_names).size()) == static_cast<size_t>(0ULL))){
TRY((((((*this).compiler))->panic(String("typecheck_match - else - EnumVariant - variant_names.size() == 0")))));
}
(is_enum_match = true);
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((String::formatted(String("catch-enum-variant({})"),variant_names)))))));
JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::EnumVariant((((((variant_names).last()).value())).get<0>()),variant_arguments,subject_type_id,static_cast<size_t>(0ULL),new_scope_id,checked_body,((case_).marker_span)) } ;
TRY((((checked_cases).push(checked_match_case))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::CatchAll>();JaktInternal::Array<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
{
if ((current_case_index != (JaktInternal::checked_sub<size_t>(case_count,static_cast<size_t>(1ULL))))){
TRY((((*this).error(String("Match else case is only allowed as the last case"),((case_).marker_span)))));
}
if (seen_catch_all){
TRY((((*this).error(String("Multiple catch-all cases in match are not allowed"),((case_).marker_span)))));
}
else {
(seen_catch_all = true);
}

types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),String("catch-all")))));
JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll((((variant_arguments).size()) != static_cast<size_t>(0ULL)),checked_body,((case_).marker_span)) } ;
TRY((((checked_cases).push(checked_match_case))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedMatchPattern::Expression>();
NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.value;
{
if (is_enum_match){
TRY((((*this).error(String("Cannot have a value match case in a match expression containing enum matches"),((case_).marker_span)))));
}
(is_value_match = true);
JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings(expr,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),span))));
NonnullRefPtr<parser::ParsedExpression> const new_condition = ((new_condition_new_then_block_new_else_statement_).get<0>());
JaktInternal::Optional<parser::ParsedBlock> const new_then_block = ((new_condition_new_then_block_new_else_statement_).get<1>());
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> const new_else_statement = ((new_condition_new_then_block_new_else_statement_).get<2>());

NonnullRefPtr<types::CheckedExpression> const checked_expression = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,static_cast<JaktInternal::Optional<types::TypeId>>(subject_type_id),span))));
if ((!(((((checked_expression)->to_number_constant(((*this).program)))).has_value())))){
(all_variants_constant = false);
}
types::TypeId expression_type = ((checked_expression)->type());
if (((checked_expression)->index() == 8 /* Range */)){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const from = (checked_expression->get<types::CheckedExpression::Range>()).from;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const to = (checked_expression->get<types::CheckedExpression::Range>()).to;
if ((((from).has_value()) || ((to).has_value()))){
if (((from).has_value())){
(expression_type = (((from.value()))->type()));
}
else if (((to).has_value())){
(expression_type = (((to.value()))->type()));
}
}
else {
TRY((((*this).error(String("There has to be at least a 'from', or a 'to' in a range expression"),((expr)->span())))));
return JaktInternal::LoopContinue{};
}

}
TRY((((*this).check_types_for_compat(expression_type,subject_type_id,((((*this).generic_inferences))),((case_).marker_span)))));
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((String::formatted(String("catch-expression({})"),expr)))))));
JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::Expression(checked_expression,checked_body,((case_).marker_span)) } ;
TRY((((checked_cases).push(checked_match_case))));
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
}

}
}

((current_case_index++));
}

}
}

if ((is_value_match && (!(seen_catch_all)))){
TRY((((*this).error(String("match expression is not exhaustive, a value match must contain an irrefutable 'else' pattern"),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Match>(checked_expr,checked_cases,span,final_result_type.value_or_lazy_evaluated([&] { return types::void_type_id(); }),true))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_generic_resolved_type(String const name,JaktInternal::Array<types::TypeId> const checked_inner_types,types::ScopeId const scope_id,utility::Span const span) {
{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,name))));
if (((struct_id).has_value())){
return (TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>((struct_id.value()),checked_inner_types))))))));
}
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,name))));
if (((enum_id).has_value())){
return (TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericEnumInstance>((enum_id.value()),checked_inner_types))))))));
}
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((((*this).program))->find_trait_in_scope(scope_id,name))));
if (((trait_id).has_value())){
return (TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericTraitInstance>((trait_id.value()),checked_inner_types))))))));
}
TRY((((*this).error(TRY((String::formatted(String("could not find {}"),name))),span))));
return (types::unknown_type_id());
}
}

types::BlockControlFlow typechecker::Typechecker::maybe_statement_control_flow(JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> const statement,types::BlockControlFlow const other_branch) const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,types::BlockControlFlow>{
auto __jakt_enum_value = (((statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((*this).statement_control_flow((statement.value()))));
}
else {
return JaktInternal::ExplicitValue(((other_branch).partial()));
}
}()))
);
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_jakt_main(parser::ParsedFunction const parsed_function) {
{
String const param_type_error = String("Main function must take a single array of strings as its parameter");
if ((((((parsed_function).params)).size()) > static_cast<size_t>(1ULL))){
TRY((((*this).error(param_type_error,((parsed_function).name_span)))));
}
if ((!(((((parsed_function).params)).is_empty())))){
if (((((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type))->index() == 3 /* JaktArray */)){
NonnullRefPtr<parser::ParsedType> const inner = (((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type)->get<parser::ParsedType::JaktArray>()).inner;
utility::Span const span = (((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type)->get<parser::ParsedType::JaktArray>()).span;
if (((inner)->index() == 0 /* Name */)){
String const name = (inner->get<parser::ParsedType::Name>()).name;
utility::Span const span = (inner->get<parser::ParsedType::Name>()).span;
if ((name != String("String"))){
TRY((((*this).error(param_type_error,span))));
}
}
else {
TRY((((*this).error(param_type_error,span))));
}

}
else {
TRY((((*this).error(param_type_error,((parsed_function).name_span)))));
}

}
String const return_type_error = String("Main function must return c_int");
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *((parsed_function).return_type);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedType::Empty>();
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if ((name != String("c_int"))){
TRY((((*this).error(return_type_error,span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(return_type_error,((parsed_function).return_type_span)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_for(String const iterator_name,utility::Span const name_span,NonnullRefPtr<parser::ParsedExpression> const range,parser::ParsedBlock const block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
JaktInternal::Optional<utility::Span> const maybe_span = ((block).find_yield_span());
if (((maybe_span).has_value())){
TRY((((*this).error(String("a 'for' loop block is not allowed to yield values"),(maybe_span.value())))));
}
NonnullRefPtr<types::CheckedExpression> iterable_expr = TRY((((*this).typecheck_expression(range,scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::TypeId resolved_iterable_result_type = types::unknown_type_id();
NonnullRefPtr<parser::ParsedExpression> expression_to_iterate = range;
types::TraitId const iterable_trait_id = (TRY((((*this).find_trait_in_scope(scope_id,String("Iterable"))))).value());
types::TraitId const throwing_iterable_trait_id = (TRY((((*this).find_trait_in_scope(scope_id,String("ThrowingIterable"))))).value());
JaktInternal::Array<JaktInternal::Array<types::TypeId>> const implemented_iterable_trait_args = TRY((utility::add_arrays<JaktInternal::Array<types::TypeId>>(TRY((((*this).find_all_implementations_of_trait(((iterable_expr)->type()),iterable_trait_id)))),TRY((((*this).find_all_implementations_of_trait(((iterable_expr)->type()),throwing_iterable_trait_id)))))));
if (((implemented_iterable_trait_args).is_empty())){
types::TraitId const into_iterator_trait_id = (TRY((((*this).find_trait_in_scope(scope_id,String("IntoIterator"))))).value());
types::TraitId const into_throwing_iterator_trait_id = (TRY((((*this).find_trait_in_scope(scope_id,String("IntoThrowingIterator"))))).value());
JaktInternal::Array<JaktInternal::Array<types::TypeId>> const implemented_into_iterator_trait_id = TRY((utility::add_arrays<JaktInternal::Array<types::TypeId>>(TRY((((*this).find_all_implementations_of_trait(((iterable_expr)->type()),into_iterator_trait_id)))),TRY((((*this).find_all_implementations_of_trait(((iterable_expr)->type()),into_throwing_iterator_trait_id)))))));
if (((implemented_into_iterator_trait_id).is_empty())){
TRY((((*this).error_with_hint(String("Iterable expression is not iterable"),((range)->span()),TRY((String::formatted(String("Consider implementing (Throwing)Iterable<T> or Into(Throwing)Iterator<T> for the type of this expression (‘{}’)"),TRY((((*this).type_name(((iterable_expr)->type())))))))),((range)->span())))));
}
else if ((((implemented_into_iterator_trait_id).size()) != static_cast<size_t>(1ULL))){
String type_names = String("");
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Array<types::TypeId>> _magic = ((implemented_into_iterator_trait_id).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Array<types::TypeId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Array<types::TypeId> args = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(type_names += String(", "));
}

(type_names += TRY((String::formatted(String("‘IntoIterator<{}>’"),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)])))))))));
}

}
}

TRY((((*this).error_with_hint(String("Iterable expression implements multiple versions of the IntoIterator trait"),((range)->span()),TRY((String::formatted(String("This expression's type implements {}, but only one is allowed"),type_names))),((range)->span())))));
}
else {
(resolved_iterable_result_type = ((((implemented_into_iterator_trait_id)[static_cast<i64>(0LL)]))[static_cast<i64>(0LL)]));
(expression_to_iterate = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::MethodCall>(range,parser::ParsedCall((TRY((Array<String>::create_with({})))),String("iterator"),(TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>>::create_with({})))),(TRY((Array<NonnullRefPtr<parser::ParsedType>>::create_with({}))))),false,name_span))));
}

}
else {
if ((((implemented_iterable_trait_args).size()) != static_cast<size_t>(1ULL))){
String type_names = String("");
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Array<types::TypeId>> _magic = ((implemented_iterable_trait_args).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Array<types::TypeId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Array<types::TypeId> args = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(type_names += String(", "));
}

(type_names += TRY((String::formatted(String("‘Iterable<{}>’"),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)])))))))));
}

}
}

TRY((((*this).error_with_hint(String("Iterable expression implements multiple versions of the Iterable trait"),((range)->span()),TRY((String::formatted(String("This expression's type implements {}, but only one is allowed"),type_names))),((range)->span())))));
}
(resolved_iterable_result_type = ((((implemented_iterable_trait_args)[static_cast<i64>(0LL)]))[static_cast<i64>(0LL)]));
}

NonnullRefPtr<parser::ParsedStatement> const rewritten_statement = TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Block>(parser::ParsedBlock((TRY((Array<NonnullRefPtr<parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(String("_magic"),TRY((parser::ParsedType::template create<typename parser::ParsedType::Empty>())),true,JaktInternal::OptionalNone(),name_span),expression_to_iterate,span))), TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Loop>(parser::ParsedBlock((TRY((Array<NonnullRefPtr<parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(String("_magic_value"),TRY((parser::ParsedType::template create<typename parser::ParsedType::Empty>())),true,JaktInternal::OptionalNone(),name_span),TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::MethodCall>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::Var>(String("_magic"),name_span))),parser::ParsedCall((TRY((Array<String>::create_with({})))),String("next"),(TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>>::create_with({})))),(TRY((Array<NonnullRefPtr<parser::ParsedType>>::create_with({}))))),false,name_span))),span))), TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::If>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::UnaryOp>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::MethodCall>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::Var>(String("_magic_value"),name_span))),parser::ParsedCall((TRY((Array<String>::create_with({})))),String("has_value"),(TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>>::create_with({})))),(TRY((Array<NonnullRefPtr<parser::ParsedType>>::create_with({}))))),false,name_span))), parser::UnaryOperator { typename parser::UnaryOperator::LogicalNot() } ,name_span))),parser::ParsedBlock((TRY((Array<NonnullRefPtr<parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Break>(span)))}))))),JaktInternal::OptionalNone(),span))), TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(iterator_name,TRY((parser::ParsedType::template create<typename parser::ParsedType::Empty>())),true,name_span,name_span),TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::ForcedUnwrap>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::Var>(String("_magic_value"),name_span))),name_span))),span))), TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Block>(block,span)))}))))),span)))}))))),span)));
return (TRY((((*this).typecheck_statement(rewritten_statement,scope_id,safety_mode,JaktInternal::OptionalNone())))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_constructors(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
JaktInternal::Array<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_constructors(child_namespace,child_namespace_scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find previously added struct")))));
}
TRY((((*this).typecheck_struct_constructor(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find previously added struct")))));
}
TRY((((*this).typecheck_struct_constructor(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find previously added enum")))));
}
TRY((((*this).typecheck_enum_constructor(record,(enum_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find previously added enum")))));
}
TRY((((*this).typecheck_enum_constructor(record,(enum_id.value()),scope_id))));
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
}

}
}

}
return {};
}

ErrorOr<bool> typechecker::Typechecker::add_struct_to_scope(types::ScopeId const scope_id,String const name,types::StructId const struct_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::StructId> const maybe_scope_id = ((((scope)->structs)).get(name));
if (((maybe_scope_id).has_value())){
types::StructId const existing_struct_id = (maybe_scope_id.value());
utility::Span const definition_span = ((((*this).get_struct(existing_struct_id))).name_span);
TRY((((*this).error_with_hint(TRY((String::formatted(String("redefinition of struct/class {}"),name))),span,TRY((String::formatted(String("struct/class {} was first defined here"),name))),definition_span))));
return (false);
}
TRY((((((scope)->structs)).set(name,struct_id))));
return (true);
}
}

ErrorOr<void> typechecker::Typechecker::fill_trait_requirements(JaktInternal::Array<parser::ParsedNameWithGenericParameters> const names,JaktInternal::Array<types::TraitId>& trait_requirements,types::ScopeId const scope_id) {
{
TRY((((((trait_requirements))).ensure_capacity(((names).size())))));
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters name = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> const type_id = TRY((((*this).find_type_in_scope(scope_id,((name).name)))));
if (((type_id).has_value())){
if (((((*this).get_type((type_id.value()))))->index() == 26 /* Trait */)){
types::TraitId const trait_id = (((*this).get_type((type_id.value())))->get<types::Type::Trait>()).value;
TRY((((((trait_requirements))).push(trait_id))));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Requirement ‘{}’ is not a trait"),((name).name)))),((name).name_span)))));
continue;
}

}
else {
TRY((((*this).error(TRY((String::formatted(String("Couldn't find trait ‘{}’"),((name).name)))),((name).name_span)))));
continue;
}

}

}
}

}
return {};
}

ErrorOr<String> typechecker::TraitImplCheck::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("TraitImplCheck("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("missing_methods: "));TRY(builder.appendff("{}, ", missing_methods));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("unmatched_signatures: "));TRY(builder.appendff("{}, ", unmatched_signatures));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("private_matching_methods: "));TRY(builder.appendff("{}, ", private_matching_methods));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("already_implemented_for: "));TRY(builder.appendff("{}", already_implemented_for));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<void> typechecker::TraitImplCheck::ensure_capacity(size_t const count) {
{
TRY((((((*this).missing_methods)).ensure_capacity(count))));
TRY((((((*this).unmatched_signatures)).ensure_capacity(count))));
TRY((((((*this).private_matching_methods)).ensure_capacity(count))));
TRY((((((*this).already_implemented_for)).ensure_capacity(count))));
}
return {};
}

ErrorOr<typechecker::TraitImplCheck> typechecker::TraitImplCheck::make() {
{
return (typechecker::TraitImplCheck((TRY((Dictionary<String, JaktInternal::Dictionary<String,types::FunctionId>>::create_with_entries({})))),(TRY((Dictionary<String, JaktInternal::Dictionary<String,utility::Span>>::create_with_entries({})))),(TRY((Dictionary<String, JaktInternal::Dictionary<String,utility::Span>>::create_with_entries({})))),(TRY((Dictionary<String, typechecker::AlreadyImplementedFor>::create_with_entries({}))))));
}
}

typechecker::TraitImplCheck::TraitImplCheck(JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,types::FunctionId>> a_missing_methods, JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,utility::Span>> a_unmatched_signatures, JaktInternal::Dictionary<String,JaktInternal::Dictionary<String,utility::Span>> a_private_matching_methods, JaktInternal::Dictionary<String,typechecker::AlreadyImplementedFor> a_already_implemented_for) :missing_methods(a_missing_methods), unmatched_signatures(a_unmatched_signatures), private_matching_methods(a_private_matching_methods), already_implemented_for(a_already_implemented_for){}

ErrorOr<void> typechecker::TraitImplCheck::register_trait(types::TraitId const trait_id,String const trait_name,JaktInternal::Dictionary<String,types::FunctionId> const trait_methods) {
{
TRY(((*this).unmatched_signatures).set(trait_name, (TRY((Dictionary<String, utility::Span>::create_with_entries({}))))));
TRY(((*this).private_matching_methods).set(trait_name, (TRY((Dictionary<String, utility::Span>::create_with_entries({}))))));
JaktInternal::Dictionary<String,types::FunctionId> missing_methods = (TRY((Dictionary<String, types::FunctionId>::create_with_entries({}))));
TRY((((missing_methods).ensure_capacity(((trait_methods).size())))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((trait_methods).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> method_name__method_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__method_name__method_id__ = method_name__method_id__;
String const method_name = ((jakt__method_name__method_id__).get<0>());
types::FunctionId const method_id = ((jakt__method_name__method_id__).get<1>());

TRY((((missing_methods).set(method_name,method_id))));
}

}
}

TRY((((((*this).missing_methods)).set(trait_name,missing_methods))));
}
return {};
}

ErrorOr<void> typechecker::TraitImplCheck::register_method(String const method_name,types::FunctionId const method_id,typechecker::Typechecker& typechecker) {
{
NonnullRefPtr<types::CheckedFunction> const method = ((((typechecker))).get_function(method_id));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Dictionary<String,types::FunctionId>> _magic = ((((*this).missing_methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Dictionary<String,types::FunctionId>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Dictionary<String,types::FunctionId>> trait_name__methods__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Dictionary<String,types::FunctionId>> const jakt__trait_name__methods__ = trait_name__methods__;
String const trait_name = ((jakt__trait_name__methods__).get<0>());
JaktInternal::Dictionary<String,types::FunctionId> const methods = ((jakt__trait_name__methods__).get<1>());

JaktInternal::Optional<types::FunctionId> const trait_method_id = ((methods).get(method_name));
if (((trait_method_id).has_value())){
NonnullRefPtr<types::CheckedFunction> const trait_method = ((((typechecker))).get_function((trait_method_id.value())));
if (TRY((((((typechecker))).signatures_match(trait_method,method))))){
if (((((method)->visibility)).index() == 0 /* Public */)){
((((((*this).missing_methods))[trait_name])).remove(method_name));
TRY(((*this).already_implemented_for).set(method_name, typechecker::AlreadyImplementedFor(trait_name,((method)->name_span))));
break;
}
else {
TRY((((((((*this).private_matching_methods))[trait_name])).set(method_name,((method)->name_span)))));
continue;
}

}
else {
TRY((((((((*this).unmatched_signatures))[trait_name])).set(method_name,((method)->name_span)))));
continue;
}

}
else {
continue;
}

}

}
}

}
return {};
}

ErrorOr<void> typechecker::TraitImplCheck::throw_errors(utility::Span const record_decl_span,typechecker::Typechecker& typechecker) {
{
{
JaktInternal::DictionaryIterator<String,JaktInternal::Dictionary<String,types::FunctionId>> _magic = ((((*this).missing_methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Dictionary<String,types::FunctionId>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Dictionary<String,types::FunctionId>> trait_name__missing_methods__ = (_magic_value.value());
{
JaktInternal::Tuple<String,JaktInternal::Dictionary<String,types::FunctionId>> const jakt__trait_name__missing_methods__ = trait_name__missing_methods__;
String const trait_name = ((jakt__trait_name__missing_methods__).get<0>());
JaktInternal::Dictionary<String,types::FunctionId> const missing_methods = ((jakt__trait_name__missing_methods__).get<1>());

JaktInternal::Dictionary<String,utility::Span> const unmatched_signatures = ((((*this).unmatched_signatures))[trait_name]);
JaktInternal::Dictionary<String,utility::Span> const private_matching_methods = ((((*this).private_matching_methods))[trait_name]);
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((missing_methods).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> method_name__trait_method_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt__method_name__trait_method_id__ = method_name__trait_method_id__;
String const method_name = ((jakt__method_name__trait_method_id__).get<0>());
types::FunctionId const trait_method_id = ((jakt__method_name__trait_method_id__).get<1>());

JaktInternal::Optional<typechecker::AlreadyImplementedFor> const already_implemented_for = ((((*this).already_implemented_for)).get(method_name));
JaktInternal::Optional<utility::Span> const unmatched_signature = ((unmatched_signatures).get(method_name));
JaktInternal::Optional<utility::Span> const private_matching_method = ((private_matching_methods).get(method_name));
if (((already_implemented_for).has_value())){
TRY((((((typechecker))).error(TRY((String::formatted(String("Cannot implement ‘{}’ for ‘{}’ because it's already implementing ‘{}’"),method_name,trait_name,(((already_implemented_for.value())).trait_name)))),(((already_implemented_for.value())).encounter_span)))));
}
else if (((private_matching_method).has_value())){
utility::Span const span = (private_matching_method.value());
TRY((((((typechecker))).error_with_hint(TRY((String::formatted(String("Implementation of ‘{}’ for trait ‘{}’ is valid but is not public"),method_name,trait_name))),span,String("Consider adding ‘public’ to make the method accessible"),span))));
}
else {
NonnullRefPtr<types::CheckedFunction> const func = ((((typechecker))).get_function(trait_method_id));
if ((!(((((((func)->block)).statements)).is_empty())))){
continue;
}
if (((unmatched_signature).has_value())){
utility::Span const method_span = (unmatched_signature.value());
TRY((((((typechecker))).error_with_hint(TRY((String::formatted(String("Missing implementation for method ‘{}’ of trait ‘{}’"),method_name,trait_name))),record_decl_span,String("The method is declared here, but its signature doesn't match"),method_span))));
}
else {
utility::Span const trait_method_span = ((((((typechecker))).get_function(trait_method_id)))->name_span);
TRY((((((typechecker))).error_with_hint(TRY((String::formatted(String("Missing implementation for method ‘{}’ of trait ‘{}’"),method_name,trait_name))),record_decl_span,String("Consider implementing the method with the signature specified here"),trait_method_span))));
}

}

}

}
}

}

}
}

}
return {};
}

}
} // namespace Jakt
