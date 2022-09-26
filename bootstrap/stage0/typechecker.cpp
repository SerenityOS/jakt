#include "typechecker.h"
namespace Jakt {
namespace typechecker {
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
bool typechecker::Typechecker::is_floating(const types::TypeId type_id) const {
{
return (((((*this).program))->is_floating(type_id)));
}
}

ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>>> typechecker::Typechecker::typecheck_match_body(const parser::ParsedMatchBody body,const types::ScopeId scope_id,const types::SafetyMode safety_mode,types::GenericInferences& generic_inferences,const JaktInternal::Optional<types::TypeId> final_result_type,const utility::Span span) {
{
JaktInternal::Optional<types::TypeId> result_type = final_result_type;
const types::CheckedMatchBody checked_match_body = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedMatchBody, ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedMatchBody::Block>();
parser::ParsedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedMatchBody> __jakt_var_227; {
const types::CheckedBlock checked_block = TRY((((*this).typecheck_block(block,scope_id,safety_mode,final_result_type))));
if ((((((checked_block).control_flow)).may_return()) || ((((checked_block).yielded_type)).has_value()))){
const types::TypeId block_type_id = ((checked_block).yielded_type).value_or_lazy_evaluated([&] { return types::void_type_id(); });
const utility::Span yield_span = ((block).find_yield_span()).value_or_lazy_evaluated([&] { return span; });
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

__jakt_var_227 = (final_body.value()); goto __jakt_label_218;

}
__jakt_label_218:; __jakt_var_227.release_value(); }));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedMatchBody::Expression>();
NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedMatchBody> __jakt_var_228; {
const NonnullRefPtr<types::CheckedExpression> checked_expression = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,result_type))));
if (((result_type).has_value())){
TRY((((*this).check_types_for_compat((result_type.value()),((checked_expression)->type()),generic_inferences,span))));
}
else {
(result_type = ((checked_expression)->type()));
}

__jakt_var_228 =  types::CheckedMatchBody { typename types::CheckedMatchBody::Expression(checked_expression) } ; goto __jakt_label_219;

}
__jakt_label_219:; __jakt_var_228.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
return ((Tuple{checked_match_body, result_type}));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_predecl(const parser::ParsedNamespace parsed_namespace,const types::ScopeId scope_id) {
{
const size_t module_struct_len = ((((((*this).current_module()))->structures)).size());
const size_t module_enum_len = ((((((*this).current_module()))->enums)).size());
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
const types::ScopeId namespace_scope_id = TRY((((*this).create_scope(scope_id,false,debug_name))));
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
const types::StructId struct_id = types::StructId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(struct_index,module_struct_len)));
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
const types::EnumId enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
TRY((((*this).typecheck_enum_predecl(parsed_record,enum_id,scope_id))));
((enum_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
const types::EnumId enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
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

}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_set(const JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> values,const utility::Span span,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
types::TypeId inner_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> inner_type_span = JaktInternal::OptionalNone();
JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> output = (TRY((Array<NonnullRefPtr<types::CheckedExpression>>::create_with({}))));
const types::StructId set_struct_id = TRY((((*this).find_struct_in_prelude(String("Set")))));
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
const NonnullRefPtr<types::CheckedExpression> checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,inner_hint))));
const types::TypeId current_value_type_id = ((checked_value)->type());
if (((inner_type_id).equals(types::unknown_type_id()))){
if ((((current_value_type_id).equals(types::void_type_id())) || ((current_value_type_id).equals(types::unknown_type_id())))){
TRY((((*this).error(String("Cannot create a set with values of type void"),((value)->span())))));
}
(inner_type_id = current_value_type_id);
(inner_type_span = ((value)->span()));
}
else if ((!(((inner_type_id).equals(current_value_type_id))))){
const String set_type_name = TRY((((*this).type_name(inner_type_id))));
TRY((((*this).error_with_hint(TRY((String::formatted(String("Type '{}' does not match type '{}' of previous values in set"),TRY((((*this).type_name(current_value_type_id)))),set_type_name))),((value)->span()),TRY((String::formatted(String("Set was inferred to store type '{}' here"),set_type_name))),(inner_type_span.value())))));
}
TRY((((output).push(checked_value))));
}

}
}

if ((((inner_type_id).equals(types::unknown_type_id())) && (((type_hint).has_value()) && (!((((type_hint.value())).equals(types::unknown_type_id()))))))){
if (((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
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
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(set_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id})))))))))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::JaktSet>(output,span,type_id,inner_type_id))));
}
}

bool typechecker::Typechecker::is_struct(const types::TypeId type_id) const {
{
if (((((*this).get_type(type_id)))->index() == 22 /* Struct */)){
const types::StructId struct_id = (((*this).get_type(type_id))->get<types::Type::Struct>()).value;
return (((((((*this).get_struct(struct_id))).record_type)).index() == 0 /* Struct */));
}
else {
return (false);
}

}
}

bool typechecker::Typechecker::is_integer(const types::TypeId type_id) const {
{
return (((((*this).program))->is_integer(type_id)));
}
}

ErrorOr<void> typechecker::Typechecker::dump_try_hint(const utility::Span span) const {
{
outln(String("{{\"type\":\"try\",\"file_id\":{},\"position\":{}}}"),((((span).file_id)).id),((span).start));
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_call(const parser::ParsedCall call,const types::ScopeId caller_scope_id,const utility::Span span,const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> this_expr,const JaktInternal::Optional<types::StructOrEnumId> parent_id,const types::SafetyMode safety_mode,JaktInternal::Optional<types::TypeId> type_hint,const bool must_be_enum_constructor) {
{
JaktInternal::Array<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> args = (TRY((Array<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>>::create_with({}))));
types::TypeId return_type = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
JaktInternal::Array<types::TypeId> generic_arguments = (TRY((Array<types::TypeId>::create_with({}))));
bool callee_throws = false;
JaktInternal::Array<types::ResolvedNamespace> resolved_namespaces = (TRY((Array<types::ResolvedNamespace>::create_with({}))));
JaktInternal::Optional<types::FunctionId> resolved_function_id = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> maybe_this_type_id = JaktInternal::OptionalNone();
JaktInternal::Optional<types::FunctionId> generic_checked_function_to_instantiate = JaktInternal::OptionalNone();
const JaktInternal::Dictionary<String,String> old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_229([&] {
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

const types::ScopeId callee_scope_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = (((parent_id).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = (parent_id.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructOrEnumId::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_230; {
types::CheckedStruct struct_ = ((*this).get_struct(id));
types::ScopeId scope_id = ((struct_).scope_id);
while ((!(((resolved_function_id).has_value())))){
(resolved_function_id = TRY((((*this).resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor,true)))));
if (((resolved_function_id).has_value())){
break;
}
if (((((struct_).super_struct_id)).has_value())){
const types::StructId parent_struct_id = (((struct_).super_struct_id).value());
(struct_ = ((*this).get_struct(parent_struct_id)));
(scope_id = ((struct_).scope_id));
}
else {
TRY((((*this).error(TRY((String::formatted(String("Could not find ‘{}’"),((call).name)))),span))));
break;
}

}
__jakt_var_230 = scope_id; goto __jakt_label_220;

}
__jakt_label_220:; __jakt_var_230.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructOrEnumId::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_231; {
const types::ScopeId scope_id = ((((*this).get_enum(id))).scope_id);
(resolved_function_id = TRY((((*this).resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor,false)))));
__jakt_var_231 = scope_id; goto __jakt_label_221;

}
__jakt_label_221:; __jakt_var_231.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
else {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_232; {
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
__jakt_var_232 = caller_scope_id; goto __jakt_label_222;

}
__jakt_label_222:; __jakt_var_232.release_value(); }));
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
const NonnullRefPtr<types::CheckedExpression> checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
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
const NonnullRefPtr<types::CheckedExpression> checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
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
const NonnullRefPtr<types::CheckedExpression> checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
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
const NonnullRefPtr<types::CheckedExpression> checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
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
const NonnullRefPtr<types::CheckedExpression> checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
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
const NonnullRefPtr<types::CheckedExpression> checked_arg = TRY((((*this).typecheck_expression(((arg).get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Call>(types::CheckedCall(resolved_namespaces,((call).name),args,checked_type_args,resolved_function_id,return_type,callee_throws),span,return_type))));
}
const types::FunctionId function_id = (resolved_function_id.value());
const NonnullRefPtr<types::CheckedFunction> callee = ((*this).get_function(function_id));
if (((callee)->is_instantiated)){
TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
}
(callee_throws = ((callee)->can_throw));
(return_type = ((callee)->return_type_id));
const types::ScopeId scope_containing_callee = (((TRY((((*this).get_scope(((callee)->function_scope_id))))))->parent).value());
TRY((((*this).check_method_access(caller_scope_id,scope_containing_callee,callee,span))));
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
const types::TypeId checked_type = TRY((((*this).typecheck_typename(parsed_type,caller_scope_id,JaktInternal::OptionalNone()))));
if ((((((((callee)->generics))->params)).size()) <= type_arg_index)){
TRY((((*this).error(String("Trying to access generic parameter out of bounds"),((parsed_type)->span())))));
continue;
}
const types::TypeId typevar_type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = ((((((callee)->generics))->params))[type_arg_index]);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::FunctionGenericParameter::InferenceGuide>();
types::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::FunctionGenericParameter::Parameter>();
types::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
if ((!(((typevar_type_id).equals(checked_type))))){
TRY((((((*this).generic_inferences)).set(TRY((((typevar_type_id).to_string()))),TRY((((checked_type).to_string())))))));
}
({auto& _jakt_ref = type_arg_index;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}

}
}

size_t arg_offset = static_cast<size_t>(0ULL);
if (((this_expr).has_value())){
const types::TypeId type_id = (((this_expr.value()))->type());
(maybe_this_type_id = type_id);
const NonnullRefPtr<types::Type> param_type = ((*this).get_type(type_id));
if (((param_type)->index() == 19 /* GenericInstance */)){
const types::StructId id = (param_type->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (param_type->get<types::Type::GenericInstance>()).args;
const types::CheckedStruct structure = ((*this).get_struct(id));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((structure).generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((structure).generic_parameters))[i])).equals(((args)[i])))){
continue;
}
TRY((((((*this).generic_inferences)).set(TRY((((((((structure).generic_parameters))[i])).to_string()))),TRY((((((args)[i])).to_string())))))));
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
const JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>> name_span_checked_arg_ = ((resolved_args)[i]);
const String name = ((name_span_checked_arg_).get<0>());
const utility::Span span = ((name_span_checked_arg_).get<1>());
const NonnullRefPtr<types::CheckedExpression> checked_arg = ((name_span_checked_arg_).get<2>());

TRY((((*this).check_types_for_compat(((((((((((callee)->generics))->base_params))[(JaktInternal::checked_add<size_t>(i,arg_offset))])).variable)).type_id),((checked_arg)->type()),((((*this).generic_inferences))),((checked_arg)->span())))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

}
if ((((type_hint).has_value()) && (!(((((type_hint).value())).equals(types::unknown_type_id())))))){
const bool old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
TRY((((*this).check_types_for_compat(return_type,(type_hint.value()),((((*this).generic_inferences))),span))));
(((*this).ignore_errors) = old_ignore_errors);
}
(return_type = TRY((((*this).substitute_typevars_in_type(return_type,((*this).generic_inferences))))));
if ((((type_hint).has_value()) && (!(((((type_hint).value())).equals(types::unknown_type_id())))))){
const bool old_ignore_errors = ((*this).ignore_errors);
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
if (((generic_typevar).index() == 1 /* Parameter */)){
const types::TypeId id = (generic_typevar.get<types::FunctionGenericParameter::Parameter>()).value;
const JaktInternal::Optional<String> substitution = ((((*this).generic_inferences)).get(TRY((((id).to_string())))));
if (((substitution).has_value())){
TRY((((generic_arguments).push(TRY((types::TypeId::from_string((substitution.value()))))))));
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
TRY((((*this).typecheck_and_specialize_generic_function((generic_checked_function_to_instantiate.value()),generic_arguments,callee_scope_id,maybe_this_type_id,((*this).generic_inferences)))));
}
if ((((*this).dump_try_hints) && callee_throws)){
TRY((((*this).dump_try_hint(span))));
}
const types::CheckedCall function_call = types::CheckedCall(resolved_namespaces,((call).name),args,generic_arguments,resolved_function_id,return_type,callee_throws);
const NonnullRefPtr<types::CheckedExpression> checked_call = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Call>(function_call,span,return_type)));
const bool in_comptime_function = (((((*this).current_function_id)).has_value()) && ((((*this).get_function(((((*this).current_function_id)).value()))))->is_comptime));
if (((!(in_comptime_function)) && (((resolved_function_id).has_value()) && ((((*this).get_function((resolved_function_id.value()))))->is_comptime)))){
const NonnullRefPtr<types::CheckedFunction> resolved_function = ((*this).get_function((resolved_function_id.value())));
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((interpreter::Interpreter::create(((*this).compiler),((*this).program),(TRY((Array<utility::Span>::create_with({})))))));
const NonnullRefPtr<types::CheckedFunction> function_ = ((((*this).program))->get_function(generic_checked_function_to_instantiate.value_or_lazy_evaluated([&] { return (resolved_function_id.value()); })));
JaktInternal::Array<types::Value> call_args = (TRY((Array<types::Value>::create_with({}))));
JaktInternal::Optional<types::Value> this_argument = JaktInternal::OptionalNone();
NonnullRefPtr<interpreter::InterpreterScope> eval_scope = TRY((interpreter::InterpreterScope::from_runtime_scope(caller_scope_id,((*this).program),JaktInternal::OptionalNone())));
{
JaktInternal::DictionaryIterator<String,String> _magic = ((((*this).generic_inferences)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,String>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,String> entry = (_magic_value.value());
{
const JaktInternal::Tuple<String,String> key_value_ = entry;
const String key = ((key_value_).get<0>());
const String value = ((key_value_).get<1>());

TRY((((((eval_scope)->type_bindings)).set(key,TRY((types::TypeId::from_string(value)))))));
}

}
}

if (((this_expr).has_value())){
auto __jakt_var_233 = [&]() -> ErrorOr<void> {{
const interpreter::StatementResult evaluated_this = TRY((((interpreter)->execute_expression((this_expr.value()),eval_scope))));
if (((evaluated_this).index() == 5 /* JustValue */)){
const types::Value value = (evaluated_this.get<interpreter::StatementResult::JustValue>()).value;
(this_argument = value);
}
else if (((evaluated_this).index() == 1 /* Throw */)){
const types::Value value = (evaluated_this.get<interpreter::StatementResult::Throw>()).value;
TRY((((*this).error(TRY((String::formatted(String("Error executing this expression (evaluation threw {})"),value))),(((this_expr.value()))->span())))));
}
else {
TRY((((*this).error(String("Invalid this expression"),(((this_expr.value()))->span())))));
}

}

;return {};}();
if (__jakt_var_233.is_error()) {{
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
const interpreter::StatementResult value = ({ Optional<interpreter::StatementResult> __jakt_var_234;
auto __jakt_var_235 = [&]() -> ErrorOr<interpreter::StatementResult> { return TRY((((interpreter)->execute_expression(((argument).get<1>()),eval_scope)))); }();
if (__jakt_var_235.is_error()) {{
TRY((((*this).error(String("Error in argument"),span))));
continue;
}
} else {__jakt_var_234 = __jakt_var_235.release_value();
}
__jakt_var_234.release_value(); });
if (((value).index() == 1 /* Throw */)){
TRY((((*this).error(TRY((String::formatted(String("Compiletime call failed: {}"),value))),((((argument).get<1>()))->span())))));
break;
}
const types::Value evaluated_value = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
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
const types::FunctionGenericParameter param = ((((((resolved_function)->generics))->params))[i]);
TRY((((type_bindings).set(TRY((((((param).type_id())).to_string()))),((((function_call).type_args))[i])))));
}

}
}

JaktInternal::Optional<interpreter::ExecutionResult> result = JaktInternal::OptionalNone();
NonnullRefPtr<interpreter::InterpreterScope> invocation_scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<String, types::Value>::create_with_entries({})))),JaktInternal::OptionalNone(),type_bindings)));
auto __jakt_var_236 = [&]() -> ErrorOr<void> {{
(result = TRY((((interpreter)->execute((resolved_function_id.value()),resolved_namespaces,this_argument,call_args,span,invocation_scope)))));
}

;return {};}();
if (__jakt_var_236.is_error()) {auto error = __jakt_var_236.release_error();{
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
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_237; {
TRY((((*this).error(TRY((String::formatted(String("Compiletime call failed: {}"),x))),span))));
__jakt_var_237 = checked_call; goto __jakt_label_224;

}
__jakt_label_224:; __jakt_var_237.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
return (checked_call);
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_guard(const NonnullRefPtr<parser::ParsedExpression> expr,const parser::ParsedBlock else_block,const parser::ParsedBlock remaining_code,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
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

const types::CheckedBlock checked_else_block = TRY((((*this).typecheck_block(else_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((!(seen_scope_exit)) && ((((checked_else_block).control_flow)).may_return()))){
TRY((((*this).error(String("Else block of guard must either `return`, `break`, `continue`, or `throw`"),span))));
}
const JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,parser::ParsedBlock,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>> new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings(expr,JaktInternal::OptionalNone(),remaining_code,TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Block>(else_block,span))),span))));
const NonnullRefPtr<parser::ParsedExpression> new_condition = ((new_condition_new_then_block_new_else_statement_).get<0>());
const parser::ParsedBlock new_then_block = ((new_condition_new_then_block_new_else_statement_).get<1>());
const JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> new_else_statement = ((new_condition_new_then_block_new_else_statement_).get<2>());

const NonnullRefPtr<types::CheckedExpression> checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("Condition must be a boolean expression"),((new_condition)->span())))));
}
const types::CheckedBlock checked_block = TRY((((*this).typecheck_block(new_then_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
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

ErrorOr<bool> typechecker::Typechecker::add_comptime_binding_to_scope(const types::ScopeId scope_id,const String name,const types::Value value,const utility::Span span) {
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

ErrorOr<types::CheckedVisibility> typechecker::Typechecker::typecheck_visibility(const parser::Visibility visibility,const types::ScopeId scope_id) {
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
return JaktInternal::ExplicitValue(({ Optional<types::CheckedVisibility> __jakt_var_238; {
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

__jakt_var_238 =  types::CheckedVisibility { typename types::CheckedVisibility::Restricted(restricted_scopes,span) } ; goto __jakt_label_225;

}
__jakt_label_225:; __jakt_var_238.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

ErrorOr<String> typechecker::Typechecker::type_name(const types::TypeId type_id) const {
{
return (TRY((((((*this).program))->type_name(type_id)))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_namespaced_var_or_simple_enum_constructor_call(const String name,const JaktInternal::Array<String> namespace_,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> type_hint,const utility::Span span) {
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
const types::ScopeId scope = ((scopes)[(JaktInternal::checked_sub<size_t>(((scopes).size()),static_cast<size_t>(1ULL)))]);
const JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> ns_in_scope = TRY((((*this).find_namespace_in_scope(scope,ns))));
const JaktInternal::Optional<types::EnumId> enum_in_scope = TRY((((((*this).program))->find_enum_in_scope(scope,ns))));
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

const types::ScopeId scope = (((scopes).last()).value());
size_t i = static_cast<size_t>(0ULL);
const size_t min_length = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
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
const JaktInternal::Optional<types::CheckedVariable> var = TRY((((*this).find_var_in_scope(scope,name))));
if (((var).has_value())){
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NamespacedVar>(checked_namespaces,(var.value()),span))));
}
const parser::ParsedCall implicit_constructor_call = parser::ParsedCall(namespace_,name,(TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>>::create_with({})))),(TRY((Array<NonnullRefPtr<parser::ParsedType>>::create_with({})))));
const NonnullRefPtr<types::CheckedExpression> call_expression = TRY((((*this).typecheck_call(implicit_constructor_call,scope_id,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),safety_mode,type_hint,true))));
const types::TypeId type_id = ((call_expression)->type());
const types::CheckedCall call = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedCall, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *call_expression;
switch(__jakt_match_variant.index()) {
case 18: {
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

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>>> typechecker::Typechecker::typecheck_match_variant(const parser::ParsedMatchCase case_,const types::TypeId subject_type_id,const size_t variant_index,const JaktInternal::Optional<types::TypeId> final_result_type,const types::CheckedEnumVariant variant,const JaktInternal::Array<parser::EnumVariantPatternArgument> variant_arguments,const utility::Span arguments_span,const types::ScopeId scope_id,const types::SafetyMode safety_mode) {
{
JaktInternal::Optional<String> covered_name = JaktInternal::OptionalNone();
const types::ScopeId new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((String::formatted(String("catch-enum-variant({})"),((variant).name()))))))));
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
const parser::EnumVariantPatternArgument variant_argument = ((variant_arguments)[static_cast<i64>(0LL)]);
const types::TypeId variable_type_id = TRY((((*this).substitute_typevars_in_type(type_id,((*this).generic_inferences)))));
const types::VarId var_id = TRY((((module)->add_variable(types::CheckedVariable(((variant_argument).binding),variable_type_id,false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } )))));
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
const String arg_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); });
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
const types::TypeId substituted_type_id = TRY((((*this).substitute_typevars_in_type((((matched_field_variable.value())).type_id),((*this).generic_inferences)))));
const utility::Span matched_span = (((matched_field_variable.value())).definition_span);
if (((*this).dump_type_hints)){
TRY((((*this).dump_type_hint((((matched_field_variable.value())).type_id),((arg).span)))));
}
const types::VarId var_id = TRY((((module)->add_variable(types::CheckedVariable(((arg).binding),substituted_type_id,false,matched_span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } )))));
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
const JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
const types::CheckedMatchBody checked_body = ((checked_body_result_type_).get<0>());
const JaktInternal::Optional<types::TypeId> result_type = ((checked_body_result_type_).get<1>());

const types::CheckedMatchCase checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::EnumVariant(((variant).name()),variant_arguments,subject_type_id,variant_index,new_scope_id,checked_body,((case_).marker_span)) } ;
return ((Tuple{covered_name, checked_match_case, result_type}));
}
}

ErrorOr<void> typechecker::Typechecker::error_with_hint(const String message,const utility::Span span,const String hint,const utility::Span hint_span) {
{
if ((!(((*this).ignore_errors)))){
TRY((((((((*this).compiler))->errors)).push( error::JaktError { typename error::JaktError::MessageWithHint(message,span,hint,hint_span) } ))));
}
}
return {};
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>>> typechecker::Typechecker::find_type_scope(const types::ScopeId scope_id,const String name) const {
{
types::ScopeId current = scope_id;
for (;;){
const NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(current))));
const JaktInternal::Optional<types::TypeId> maybe_type = ((((scope)->types)).get(name));
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
const NonnullRefPtr<types::Scope> child_scope = TRY((((*this).get_scope(child_id))));
if ((!(((((child_scope)->namespace_name)).has_value())))){
const JaktInternal::Optional<types::TypeId> maybe_type = ((((child_scope)->types)).get(name));
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

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_indexed_tuple(const NonnullRefPtr<parser::ParsedExpression> expr,const size_t index,const types::ScopeId scope_id,const bool is_optional,const types::SafetyMode safety_mode,const utility::Span span) {
{
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const types::StructId tuple_struct_id = TRY((((*this).find_struct_in_prelude(String("Tuple")))));
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
types::TypeId expr_type_id = types::unknown_type_id();
if (((((*this).get_type(((checked_expr)->type()))))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(((checked_expr)->type())))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(((checked_expr)->type())))->get<types::Type::GenericInstance>()).args;
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
const types::TypeId inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((((*this).get_type(inner_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(inner_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(inner_type_id))->get<types::Type::GenericInstance>()).args;
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

ErrorOr<types::TypeId> typechecker::Typechecker::find_or_add_type_id(const NonnullRefPtr<types::Type> type) {
{
return (TRY((((((*this).program))->find_or_add_type_id(type,((*this).current_module_id))))));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>>> typechecker::Typechecker::find_namespace_in_scope(const types::ScopeId scope_id,const String name) const {
{
return (TRY((((((*this).program))->find_namespace_in_scope(scope_id,name)))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_typename(const NonnullRefPtr<parser::ParsedType> parsed_type,const types::ScopeId scope_id,const JaktInternal::Optional<String> name) {
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::TypeId>>{
auto&& __jakt_match_variant = *parsed_type;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Reference>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
{
const types::TypeId inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Reference>(inner_type_id)))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::MutableReference>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
{
const types::TypeId inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::MutableReference>(inner_type_id)))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::NamespacedName>();String const& name = __jakt_match_value.name;
JaktInternal::Array<String> const& namespaces = __jakt_match_value.namespaces;
JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> const& params = __jakt_match_value.params;
utility::Span const& span = __jakt_match_value.span;
{
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
const JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> result = TRY((((*this).find_namespace_in_scope(current_namespace_scope_id,ns))));
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
const types::TypeId checked_arg = TRY((((*this).typecheck_typename(param,scope_id,name))));
TRY((((generic_args).push(checked_arg))));
}

}
}

if (((generic_args).is_empty())){
const NonnullRefPtr<parser::ParsedType> synthetic_typename = TRY((parser::ParsedType::template create<typename parser::ParsedType::Name>(name,span)));
return (TRY((((*this).typecheck_typename(synthetic_typename,current_namespace_scope_id,name)))));
}
else {
return (TRY((((*this).typecheck_generic_resolved_type(name,generic_args,current_namespace_scope_id,span)))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
const JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>> maybe_type_and_scope = TRY((((*this).find_type_scope(scope_id,name))));
if (((maybe_type_and_scope).has_value())){
if ((!((((((maybe_type_and_scope.value())).get<1>())).equals(((*this).prelude_scope_id())))))){
return ((((maybe_type_and_scope.value())).get<0>()));
}
}
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId,ErrorOr<types::TypeId>>{
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
{
if (((maybe_type_and_scope).has_value())){
return ((((maybe_type_and_scope.value())).get<0>()));
}
TRY((((*this).error(TRY((String::formatted(String("Unknown type ‘{}’"),name))),span))));
return (types::unknown_type_id());
}
}
}()))
);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedType::Empty>();
{
return (types::unknown_type_id());
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::JaktTuple>();JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> const& types = __jakt_match_value.types;
utility::Span const& span = __jakt_match_value.span;
{
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

const types::StructId tuple_struct_id = TRY((((*this).find_struct_in_prelude(String("Tuple")))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(tuple_struct_id,checked_types)))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::JaktArray>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
{
const types::TypeId inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
const types::StructId array_struct_id = TRY((((*this).find_struct_in_prelude(String("Array")))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(array_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id})))))))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Dictionary>();NonnullRefPtr<parser::ParsedType> const& key = __jakt_match_value.key;
NonnullRefPtr<parser::ParsedType> const& value = __jakt_match_value.value;
utility::Span const& span = __jakt_match_value.span;
{
const types::TypeId key_type_id = TRY((((*this).typecheck_typename(key,scope_id,name))));
const types::TypeId value_type_id = TRY((((*this).typecheck_typename(value,scope_id,name))));
const types::StructId dict_struct_id = TRY((((*this).find_struct_in_prelude(String("Dictionary")))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(dict_struct_id,(TRY((Array<types::TypeId>::create_with({key_type_id, value_type_id})))))))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Set>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
{
const types::TypeId inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
const types::StructId set_struct_id = TRY((((*this).find_struct_in_prelude(String("Set")))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(set_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id})))))))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Optional>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
{
const types::TypeId inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id})))))))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::WeakPtr>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
{
const types::TypeId inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
const types::StructId weakptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(weakptr_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id})))))))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::RawPtr>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
{
const types::TypeId inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::RawPtr>(inner_type_id)))))));
return (type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::GenericType>();String const& name = __jakt_match_value.name;
JaktInternal::Array<NonnullRefPtr<parser::ParsedType>> const& generic_parameters = __jakt_match_value.generic_parameters;
utility::Span const& span = __jakt_match_value.span;
{
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
const types::TypeId inner_type_id = TRY((((*this).typecheck_typename(inner_type,scope_id,name))));
TRY((((checked_inner_types).push(inner_type_id))));
}

}
}

return (TRY((((*this).typecheck_generic_resolved_type(name,checked_inner_types,scope_id,span)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Function>();JaktInternal::Array<parser::ParsedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
NonnullRefPtr<parser::ParsedType> const& return_type = __jakt_match_value.return_type;
utility::Span const& span = __jakt_match_value.span;
{
const String function_name = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<types::TypeId>>{
auto __jakt_enum_value = (((name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((name.value()));
}
else {
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_239;
auto __jakt_var_240 = [&]() -> ErrorOr<String> { return TRY((String::formatted(String("lambda{}"),((((*this).lambda_count)++))))); }();
if (!__jakt_var_240.is_error()) __jakt_var_239 = __jakt_var_240.release_value();
__jakt_var_239; }).value_or_lazy_evaluated([&] { return String(""); }));
}
}()))
;
JaktInternal::Array<types::CheckedParameter> checked_params = (TRY((Array<types::CheckedParameter>::create_with({}))));
bool first = true;
const JaktInternal::Dictionary<String,String> old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_241([&] {
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

const NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(function_name,span, types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).typecheck_typename(return_type,scope_id,JaktInternal::OptionalNone())))),((return_type)->span()),checked_params,TRY((types::FunctionGenerics::create(checked_params,(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,JaktInternal::OptionalNone(),false),can_throw, parser::FunctionType { typename parser::FunctionType::Expression() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,scope_id,true,JaktInternal::OptionalNone(),false,false,false)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::FunctionId function_id = TRY((((module)->add_function(checked_function))));
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

return (TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Function>(param_type_ids,can_throw,((checked_function)->return_type_id),function_id))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_predecl(const parser::ParsedRecord parsed_record,const types::EnumId enum_id,const types::ScopeId scope_id) {
{
const types::TypeId enum_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Enum>(enum_id)))))));
const types::ScopeId enum_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((String::formatted(String("enum({})"),((parsed_record).name))))))));
TRY((((*this).add_enum_to_scope(scope_id,((parsed_record).name),enum_id,((parsed_record).name_span)))));
const types::TypeId underlying_type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<void>>{
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
const bool is_boxed = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
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
NonnullRefPtr<types::Module> module = ((*this).current_module());
(((((module)->enums))[((enum_id).id)]) = types::CheckedEnum(((parsed_record).name),((parsed_record).name_span),(TRY((Array<types::TypeId>::create_with({})))),(TRY((Array<types::CheckedEnumVariant>::create_with({})))),enum_scope_id,((parsed_record).definition_linkage),((parsed_record).record_type),underlying_type_id,enum_type_id,is_boxed));
JaktInternal::Array<types::TypeId> generic_parameters = ((((((module)->enums))[((enum_id).id)])).generic_parameters);
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
const types::TypeId parameter_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((generic_parameters).push(parameter_type_id))));
TRY((((*this).add_type_to_scope(enum_scope_id,((gen_parameter).name),parameter_type_id,((gen_parameter).span)))));
}

}
}

const bool is_extern = ((((parsed_record).definition_linkage)).index() == 1 /* External */);
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((parsed_record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
const parser::ParsedFunction func = ((method).parsed_function);
const types::ScopeId method_scope_id = TRY((((*this).create_scope(enum_scope_id,((func).can_throw),TRY((String::formatted(String("method({}::{})"),((parsed_record).name),((func).name))))))));
const types::ScopeId block_scope_id = TRY((((*this).create_scope(method_scope_id,((func).can_throw),TRY((String::formatted(String("method-block({}::{})"),((parsed_record).name),((func).name))))))));
const bool is_generic = ((!(((((parsed_record).generic_parameters)).is_empty()))) || (!(((((func).generic_parameters)).is_empty()))));
NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((func).name),((func).name_span),TRY((((*this).typecheck_visibility(((method).visibility),enum_scope_id)))),types::unknown_type_id(),JaktInternal::OptionalNone(),(TRY((Array<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::create((TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),((func).can_throw),((func).type),((func).linkage),method_scope_id,((!(is_generic)) || is_extern),func,((func).is_comptime),false,false)));
const types::FunctionId function_id = TRY((((module)->add_function(checked_function))));
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
const types::TypeId type_var_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((generic_parameters).push( types::FunctionGenericParameter { typename types::FunctionGenericParameter::Parameter(type_var_type_id) } ))));
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
const types::CheckedVariable checked_variable = types::CheckedVariable(((((param).variable)).name),enum_type_id,((((param).variable)).is_mutable),((((param).variable)).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,JaktInternal::OptionalNone())))));
}
else {
const types::TypeId param_type = TRY((((*this).typecheck_typename(((((param).variable)).parsed_type),method_scope_id,((((param).variable)).name)))));
const types::CheckedVariable checked_variable = types::CheckedVariable(((((param).variable)).name),param_type,((((param).variable)).is_mutable),((((param).variable)).span),((((((param).variable)).parsed_type))->span()), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,JaktInternal::OptionalNone())))));
}

}

}
}

TRY((((*this).add_function_to_scope(enum_scope_id,((func).name),function_id,((parsed_record).name_span)))));
const types::TypeId function_return_type_id = TRY((((*this).typecheck_typename(((func).return_type),method_scope_id,JaktInternal::OptionalNone()))));
(((checked_function)->return_type_id) = function_return_type_id);
}

}
}

}
return {};
}

ErrorOr<JaktInternal::Optional<types::CheckedEnumVariant>> typechecker::Typechecker::get_enum_variant(const types::CheckedEnum enum_,const String variant_name) {
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

ErrorOr<JaktInternal::Optional<types::FunctionId>> typechecker::Typechecker::find_function_in_scope(const types::ScopeId parent_scope_id,const String function_name) const {
{
return (TRY((((((*this).program))->find_function_in_scope(parent_scope_id,function_name)))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_loop(const parser::ParsedBlock parsed_block,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
const types::CheckedBlock checked_block = TRY((((*this).typecheck_block(parsed_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(String("A ‘loop’ block is not allowed to yield values"),(((parsed_block).find_yield_span()).value())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Loop>(checked_block,span))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_defer(const NonnullRefPtr<parser::ParsedStatement> statement,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
const bool was_inside_defer = ((*this).inside_defer);
(((*this).inside_defer) = true);
ScopeGuard __jakt_var_242([&] {
(((*this).inside_defer) = was_inside_defer);
});
const NonnullRefPtr<types::CheckedStatement> checked_statement = TRY((((*this).typecheck_statement(statement,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((checked_statement)->index() == 5 /* Block */)){
const types::CheckedBlock block = (checked_statement->get<types::CheckedStatement::Block>()).block;
if (((((block).yielded_type)).has_value())){
TRY((((*this).error(String("‘yield’ inside ‘defer’ is meaningless"),span))));
}
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Defer>(checked_statement,span))));
}
}

ErrorOr<void> typechecker::Typechecker::error(const String message,const utility::Span span) {
{
if ((!(((*this).ignore_errors)))){
TRY((((((((*this).compiler))->errors)).push( error::JaktError { typename error::JaktError::Message(message,span) } ))));
}
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_module(const parser::ParsedNamespace parsed_namespace,const types::ScopeId scope_id) {
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

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_declarations(const parser::ParsedNamespace parsed_namespace,const types::ScopeId scope_id) {
{
const JaktInternal::Array<types::ScopeId> children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
const parser::ParsedNamespace child_namespace = ((((parsed_namespace).namespaces))[i]);
const types::ScopeId child_namespace_scope_id = ((children)[i]);
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
const JaktInternal::Optional<types::StructId> struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find struct that has been previous added")))));
}
TRY((((*this).typecheck_struct(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();{
const JaktInternal::Optional<types::StructId> struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find struct that has been previous added")))));
}
TRY((((*this).typecheck_struct(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
const JaktInternal::Optional<types::EnumId> enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find enum that has been previous added")))));
}
TRY((((*this).typecheck_enum(record,(enum_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
const JaktInternal::Optional<types::EnumId> enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
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

}
return {};
}

ErrorOr<types::TypeId> typechecker::Typechecker::substitute_typevars_in_type(const types::TypeId type_id,const types::GenericInferences generic_inferences) {
{
return (TRY((((((*this).program))->substitute_typevars_in_type(type_id,generic_inferences,((*this).current_module_id))))));
}
}

ErrorOr<types::StructId> typechecker::Typechecker::find_struct_in_prelude(const String name) const {
{
return (TRY((((((*this).program))->find_struct_in_prelude(name)))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::cast_to_underlying(const NonnullRefPtr<parser::ParsedExpression> expr,const types::ScopeId scope_id,const NonnullRefPtr<parser::ParsedType> parsed_type) {
{
const NonnullRefPtr<parser::ParsedExpression> cast_expression = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::UnaryOp>(expr, parser::UnaryOperator { typename parser::UnaryOperator::TypeCast( parser::TypeCast { typename parser::TypeCast::Infallible(parsed_type) } ) } ,((expr)->span()))));
return (TRY((((*this).typecheck_expression(cast_expression,scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone())))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_module_import(const parser::ParsedModuleImport import_,const types::ScopeId scope_id) {
{
const JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> module_names_and_spans = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = ((import_).module_name);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ImportName::Literal>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>>((TRY((Array<JaktInternal::Tuple<String,utility::Span>>::create_with({(Tuple{name, span})}))))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ImportName::Comptime>();NonnullRefPtr<parser::ParsedExpression> const& expression = __jakt_match_value.expression;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>> __jakt_var_243; {
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((interpreter::Interpreter::create(((*this).compiler),((*this).program),(TRY((Array<utility::Span>::create_with({})))))));
NonnullRefPtr<interpreter::InterpreterScope> eval_scope = TRY((interpreter::InterpreterScope::from_runtime_scope(scope_id,((*this).program),JaktInternal::OptionalNone())));
const types::ScopeId exec_scope = TRY((((*this).create_scope(scope_id,true,String("comptime-import")))));
const interpreter::StatementResult result = TRY((((interpreter)->execute_expression(TRY((((*this).typecheck_expression(expression,exec_scope, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone())))),eval_scope))));
__jakt_var_243 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Return>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_244; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an invalid value"),((expression)->span())))));
__jakt_var_244 = JaktInternal::OptionalNone(); goto __jakt_label_228;

}
__jakt_label_228:; __jakt_var_244; }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Yield>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_245; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an invalid value"),((expression)->span())))));
__jakt_var_245 = JaktInternal::OptionalNone(); goto __jakt_label_229;

}
__jakt_label_229:; __jakt_var_245; }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Continue>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_246; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an invalid value"),((expression)->span())))));
__jakt_var_246 = JaktInternal::OptionalNone(); goto __jakt_label_230;

}
__jakt_label_230:; __jakt_var_246; }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Break>();
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_247; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),String("this expression evaluates to an invalid value"),((expression)->span())))));
__jakt_var_247 = JaktInternal::OptionalNone(); goto __jakt_label_231;

}
__jakt_label_231:; __jakt_var_247; }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Throw>();
types::Value const& error = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_248; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal or an array of strings"),((expression)->span()),TRY((String::formatted(String("this expression threw an error: {}"),error))),((expression)->span())))));
__jakt_var_248 = JaktInternal::OptionalNone(); goto __jakt_label_232;

}
__jakt_label_232:; __jakt_var_248; }));
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
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>> __jakt_var_249; {
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

__jakt_var_249 = static_cast<JaktInternal::Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>>>(result); goto __jakt_label_233;

}
__jakt_label_233:; __jakt_var_249.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span>>> __jakt_var_250; {
TRY((((*this).error_with_hint(String("module name must evalute to a string literal"),((expression)->span()),String("this expression evaluates to a non-string value"),((expression)->span())))));
__jakt_var_250 = JaktInternal::OptionalNone(); goto __jakt_label_234;

}
__jakt_label_234:; __jakt_var_250; }));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_227;

}
__jakt_label_227:; __jakt_var_243.release_value(); }));
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
const JaktInternal::Optional<NonnullRefPtr<utility::FilePath>> maybe_file_name = TRY((((((*this).compiler))->search_for_path(((name_and_span).get<0>())))));
const NonnullRefPtr<utility::FilePath> file_name = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<utility::FilePath>,ErrorOr<void>>{
auto __jakt_enum_value = (((maybe_file_name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((maybe_file_name.value()));
}
else {
return JaktInternal::ExplicitValue(TRY((utility::FilePath::make(TRY((String::formatted(String("{}/{}.jakt"),TRY((((TRY((((*this).get_root_path()))))->dirname()))),((name_and_span).get<0>()))))))));
}
}()))
;
if (File::exists(((file_name)->path))){
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
const JaktInternal::Tuple<String,utility::Span> module_name_module_span_ = (module_name_and_span.value());
const String module_name = ((module_name_module_span_).get<0>());
const utility::Span module_span = ((module_name_module_span_).get<1>());

types::ModuleId imported_module_id = types::ModuleId(static_cast<size_t>(0ULL));
JaktInternal::Optional<types::LoadedModule> maybe_loaded_module = ((((*this).program))->get_loaded_module(module_name));
if ((!(((maybe_loaded_module).has_value())))){
const JaktInternal::Optional<NonnullRefPtr<utility::FilePath>> maybe_file_name = TRY((((((*this).compiler))->search_for_path(module_name))));
const NonnullRefPtr<utility::FilePath> file_name = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<utility::FilePath>,ErrorOr<void>>{
auto __jakt_enum_value = (((maybe_file_name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((maybe_file_name.value()));
}
else {
return JaktInternal::ExplicitValue(TRY((utility::FilePath::make(TRY((String::formatted(String("{}/{}.jakt"),TRY((((TRY((((*this).get_root_path()))))->dirname()))),module_name)))))));
}
}()))
;
const utility::FileId file_id = TRY((((((*this).compiler))->get_file_id_or_register(file_name))));
const JaktInternal::Optional<parser::ParsedNamespace> parsed_namespace = TRY((((*this).lex_and_parse_file_contents(file_id))));
if ((!(((parsed_namespace).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Module '{}' not found"),module_name))),module_span))));
return {};
}
const types::ModuleId original_current_module_id = ((*this).current_module_id);
(imported_module_id = TRY((((*this).create_module(module_name,false,((file_name)->path))))));
TRY((((((*this).program))->set_loaded_module(module_name,types::LoadedModule(imported_module_id,file_id)))));
(((*this).current_module_id) = imported_module_id);
const types::ScopeId imported_scope_id = TRY((((*this).create_scope(((*this).root_scope_id()),false,TRY((String::formatted(String("module({})"),module_name)))))));
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
else {
const types::ScopeId import_scope_id = types::ScopeId(imported_module_id,static_cast<size_t>(0ULL));
{
JaktInternal::ArrayIterator<parser::ImportName> _magic = ((((import_).import_list)).iterator());
for (;;){
JaktInternal::Optional<parser::ImportName> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ImportName imported_name = (_magic_value.value());
{
bool found = false;
const JaktInternal::Optional<types::FunctionId> maybe_function_id = TRY((((*this).find_function_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_function_id).has_value())){
(found = true);
TRY((((*this).add_function_to_scope(scope_id,((imported_name).literal_name()),(maybe_function_id.value()),((imported_name).span())))));
}
const JaktInternal::Optional<types::EnumId> maybe_enum_id = TRY((((((*this).program))->find_enum_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_enum_id).has_value())){
(found = true);
TRY((((*this).add_enum_to_scope(scope_id,((imported_name).literal_name()),(maybe_enum_id.value()),((imported_name).span())))));
}
const JaktInternal::Optional<types::TypeId> maybe_type_id = TRY((((*this).find_type_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_type_id).has_value())){
(found = true);
TRY((((*this).add_type_to_scope(scope_id,((imported_name).literal_name()),(maybe_type_id.value()),((imported_name).span())))));
}
const JaktInternal::Optional<types::StructId> maybe_struct_id = TRY((((*this).find_struct_in_scope(import_scope_id,((imported_name).literal_name())))));
if (((maybe_struct_id).has_value())){
(found = true);
TRY((((*this).add_struct_to_scope(scope_id,((imported_name).literal_name()),(maybe_struct_id.value()),((imported_name).span())))));
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

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_binary_operation(const NonnullRefPtr<types::CheckedExpression> checked_lhs,const parser::BinaryOperator op,const NonnullRefPtr<types::CheckedExpression> checked_rhs,const types::ScopeId scope_id,const utility::Span span) {
{
const types::TypeId lhs_type_id = ((checked_lhs)->type());
const types::TypeId rhs_type_id = ((checked_rhs)->type());
const utility::Span lhs_span = ((checked_lhs)->span());
const utility::Span rhs_span = ((checked_rhs)->span());
types::TypeId type_id = ((checked_lhs)->type());
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::TypeId>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::NoneCoalescing>();
{
if (((op).index() == 32 /* NoneCoalescingAssign */)){
if (((checked_lhs)->index() == 21 /* Var */)){
const types::CheckedVariable var = (checked_lhs->get<types::CheckedExpression::Var>()).var;
const utility::Span span = (checked_lhs->get<types::CheckedExpression::Var>()).span;
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
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if (((id).equals(TRY((((*this).find_struct_in_prelude(String("Optional")))))))){
if (((lhs_type_id).equals(rhs_type_id))){
return (lhs_type_id);
}
const types::TypeId inner_type_id = ((args)[static_cast<i64>(0LL)]);
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
if (((checked_lhs)->index() == 21 /* Var */)){
const types::CheckedVariable var = (checked_lhs->get<types::CheckedExpression::Var>()).var;
const utility::Span span = (checked_lhs->get<types::CheckedExpression::Var>()).span;
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
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if (((id).equals(TRY((((*this).find_struct_in_prelude(String("Optional")))))))){
if (((lhs_type_id).equals(rhs_type_id))){
return (lhs_type_id);
}
const types::TypeId inner_type_id = ((args)[static_cast<i64>(0LL)]);
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
if (((checked_rhs)->index() == 22 /* OptionalNone */)){
const utility::Span span = (checked_rhs->get<types::CheckedExpression::OptionalNone>()).span;
const types::TypeId type_id = (checked_rhs->get<types::CheckedExpression::OptionalNone>()).type_id;
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
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
const NonnullRefPtr<types::Type> lhs_type = ((*this).get_type(lhs_type_id));
if (((lhs_type)->index() == 19 /* GenericInstance */)){
const types::StructId id = (lhs_type->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (lhs_type->get<types::Type::GenericInstance>()).args;
if (((((((((*this).program))->get_struct(id))).name) == String("Optional")) && ((((checked_rhs)->type())).equals(((args)[static_cast<i64>(0LL)]))))){
return (lhs_type_id);
}
if (((((((((*this).program))->get_struct(id))).name) == String("WeakPtr")) && ((((checked_rhs)->type())).equals(((args)[static_cast<i64>(0LL)]))))){
return (lhs_type_id);
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(lhs_type_id))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 22 /* Struct */))){
const types::StructId lhs_struct_id = (((*this).get_type(((args)[static_cast<i64>(0LL)])))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 22 /* Struct */)){
const types::StructId rhs_struct_id = (((*this).get_type(rhs_type_id))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return (lhs_type_id);
}
}
}
}
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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
const JaktInternal::Optional<types::TypeId> result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
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

ErrorOr<JaktInternal::Optional<types::StructId>> typechecker::Typechecker::find_struct_in_scope(const types::ScopeId scope_id,const String name) const {
{
return (TRY((((((*this).program))->find_struct_in_scope(scope_id,name)))));
}
}

ErrorOr<void> typechecker::Typechecker::check_method_access(const types::ScopeId accessor,const types::ScopeId accessee,const NonnullRefPtr<types::CheckedFunction> method,const utility::Span span) {
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

ErrorOr<types::CheckedBlock> typechecker::Typechecker::typecheck_block(const parser::ParsedBlock parsed_block,const types::ScopeId parent_scope_id,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> yield_type_hint) {
{
const bool parent_throws = ((TRY((((*this).get_scope(parent_scope_id)))))->can_throw);
const types::ScopeId block_scope_id = TRY((((*this).create_scope(parent_scope_id,parent_throws,String("block")))));
types::CheckedBlock checked_block = types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false);
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
const NonnullRefPtr<types::CheckedStatement> checked_statement = TRY((((*this).typecheck_statement(parsed_statement,block_scope_id,safety_mode,yield_type_hint))));
(((checked_block).control_flow) = ((((checked_block).control_flow)).updated(((*this).statement_control_flow(checked_statement)))));
const JaktInternal::Optional<utility::Span> yield_span = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<utility::Span>, ErrorOr<types::CheckedBlock>>{
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
const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_yield_expression = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>>, ErrorOr<types::CheckedBlock>>{
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
const types::TypeId type_var_type_id = (((checked_yield_expression.value()))->type());
const types::TypeId type_ = TRY((((*this).resolve_type_var(type_var_type_id,block_scope_id))));
if ((((checked_yield_expression.value()))->index() == 22 /* OptionalNone */)){
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

ErrorOr<JaktInternal::Optional<types::TypeId>> typechecker::Typechecker::find_type_in_scope(const types::ScopeId scope_id,const String name) const {
{
types::ScopeId current = scope_id;
for (;;){
const NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(current))));
const JaktInternal::Optional<types::TypeId> maybe_type = ((((scope)->types)).get(name));
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
const NonnullRefPtr<types::Scope> child_scope = TRY((((*this).get_scope(child_id))));
if ((!(((((child_scope)->namespace_name)).has_value())))){
const JaktInternal::Optional<types::TypeId> maybe_type = ((((child_scope)->types)).get(name));
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

ErrorOr<void> typechecker::Typechecker::typecheck_function(const parser::ParsedFunction parsed_function,const types::ScopeId parent_scope_id) {
{
if (((!(((((parsed_function).generic_parameters)).is_empty()))) && (!(((parsed_function).must_instantiate))))){
return {};
}
const JaktInternal::Optional<types::FunctionId> function_id = TRY((((*this).find_function_in_scope(parent_scope_id,((parsed_function).name)))));
if ((!(((function_id).has_value())))){
TRY((((((*this).compiler))->panic(String("Internal error: missing previously defined function")))));
}
if ((((parsed_function).name) == String("main"))){
TRY((((*this).typecheck_jakt_main(parsed_function))));
}
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function((function_id.value())));
const types::ScopeId function_scope_id = ((checked_function)->function_scope_id);
const parser::FunctionLinkage function_linkage = ((checked_function)->linkage);
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
const types::CheckedVariable variable = ((param).variable);
TRY((((param_vars).push(variable))));
const types::VarId var_id = TRY((((module)->add_variable(variable))));
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
const types::CheckedBlock block = TRY((((*this).typecheck_block(((parsed_function).block),function_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
if (((((block).yielded_type)).has_value())){
TRY((((*this).error_with_hint(String("Functions are not allowed to yield values"),(((((parsed_function).block)).find_yield_span()).value()),String("You might want to return instead"),(((((parsed_function).block)).find_yield_keyword_span()).value())))));
}
(function_return_type_id = TRY((((*this).typecheck_typename(((parsed_function).return_type),function_scope_id,JaktInternal::OptionalNone())))));
const types::TypeId UNKNOWN_TYPE_ID = types::unknown_type_id();
const types::TypeId VOID_TYPE_ID = types::void_type_id();
types::TypeId return_type_id = VOID_TYPE_ID;
if (((function_return_type_id).equals(UNKNOWN_TYPE_ID))){
(return_type_id = ((*this).infer_function_return_type(block)));
}
else {
(return_type_id = TRY((((*this).resolve_type_var(function_return_type_id,function_scope_id)))));
}

const bool external_linkage = ((function_linkage).index() == 1 /* External */);
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

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_inline_cpp(const parser::ParsedBlock block,const utility::Span span,const types::SafetyMode safety_mode) {
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
const NonnullRefPtr<parser::ParsedExpression> expr = (statement->get<parser::ParsedStatement::Expression>()).expr;
if (((expr)->index() == 2 /* QuotedString */)){
const String val = (expr->get<parser::ParsedExpression::QuotedString>()).val;
const utility::Span span = (expr->get<parser::ParsedExpression::QuotedString>()).span;
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

ErrorOr<bool> typechecker::Typechecker::check_restricted_access(const types::ScopeId accessor,const String accessee_kind,const types::ScopeId accessee,const String name,const JaktInternal::Array<NonnullRefPtr<types::MaybeResolvedScope>> whitelist,const utility::Span span) {
{
const types::ScopeId most_specific_active_scope_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId,ErrorOr<bool>>{
auto __jakt_enum_value = (((((*this).current_function_id)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((((*this).get_function((((*this).current_function_id).value()))))->function_scope_id));
}
else {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_251; {
if ((!(((((*this).current_struct_type_id)).has_value())))){
TRY((((*this).error(TRY((String::formatted(String("Can't access {0} ‘{1}’ from this global scope, because ‘{1}’ restricts access to it"),accessee_kind,name))),span))));
return (false);
}
__jakt_var_251 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId, ErrorOr<bool>>{
auto&& __jakt_match_variant = *((*this).get_type((((*this).current_struct_type_id).value())));
switch(__jakt_match_variant.index()) {
case 22: {
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
)); goto __jakt_label_235;

}
__jakt_label_235:; __jakt_var_251.release_value(); }));
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
const NonnullRefPtr<types::MaybeResolvedScope> resolved_scope = TRY((((scope)->try_resolve(((*this).program)))));
if (((resolved_scope)->index() == 0 /* Resolved */)){
const types::ScopeId scope_id = (resolved_scope->get<types::MaybeResolvedScope::Resolved>()).value;
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

const NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(most_specific_active_scope_id))));
TRY((((*this).error(TRY((String::formatted(String("Cannot access {} ‘{}’ from this scope"),accessee_kind,name))),span))));
return (false);
}
}

ErrorOr<JaktInternal::Array<types::StructId>> typechecker::Typechecker::struct_inheritance_chain(const types::StructId struct_id) const {
{
JaktInternal::Array<types::StructId> chain = (TRY((Array<types::StructId>::create_with({}))));
JaktInternal::Optional<types::StructId> current = static_cast<JaktInternal::Optional<types::StructId>>(struct_id);
TRY((((chain).push((current.value())))));
while (((current).has_value())){
const JaktInternal::Optional<types::StructId> parent = ((((*this).get_struct((current.value())))).super_struct_id);
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

ErrorOr<bool> typechecker::Typechecker::add_function_to_scope(const types::ScopeId parent_scope_id,const String name,const types::FunctionId function_id,const utility::Span span) {
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
const NonnullRefPtr<types::CheckedFunction> function_ = ((*this).get_function(((existing_function).get<1>())));
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

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_while(const NonnullRefPtr<parser::ParsedExpression> condition,const parser::ParsedBlock block,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
const NonnullRefPtr<types::CheckedExpression> checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("Condition must be a boolean expression"),((condition)->span())))));
}
const types::CheckedBlock checked_block = TRY((((*this).typecheck_block(block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(String("A ‘while’ block is not allowed to yield values"),(((block).find_yield_span()).value())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::While>(checked_condition,checked_block,span))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_expression_and_dereference_if_needed(const NonnullRefPtr<parser::ParsedExpression> expr,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> type_hint,const utility::Span span) {
{
NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,type_hint))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((checked_expr)->type())));
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
{
(checked_expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Dereference() } ,span,type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
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

ErrorOr<NonnullRefPtr<utility::FilePath>> typechecker::Typechecker::get_root_path() const {
{
const utility::FileId file_id = (((((((*this).program))->get_loaded_module(String("Root Module"))).value())).file_id);
return ((TRY((((((*this).compiler))->get_file_path(file_id)))).value()));
}
}

ErrorOr<bool> typechecker::Typechecker::scope_can_access(const types::ScopeId accessor,const types::ScopeId accessee) const {
{
if (((accessor).equals(accessee))){
return (true);
}
NonnullRefPtr<types::Scope> accessor_scope = TRY((((*this).get_scope(accessor))));
while (((((accessor_scope)->parent)).has_value())){
const types::ScopeId parent = (((accessor_scope)->parent).value());
if (((parent).equals(accessee))){
return (true);
}
(accessor_scope = TRY((((*this).get_scope(parent)))));
}
return (false);
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_fields(const parser::ParsedRecord record,const types::StructId struct_id) {
{
types::CheckedStruct structure = ((*this).get_struct(struct_id));
const types::ScopeId checked_struct_scope_id = ((((*this).get_struct(struct_id))).scope_id);
const types::TypeId struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
const JaktInternal::Array<parser::ParsedField> parsed_fields = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<parser::ParsedField>, ErrorOr<void>>{
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
const parser::ParsedVarDecl parsed_var_decl = ((unchecked_member).var_decl);
const types::TypeId checked_member_type = TRY((((*this).typecheck_typename(((parsed_var_decl).parsed_type),checked_struct_scope_id,((parsed_var_decl).name)))));
TRY((((*this).check_that_type_doesnt_contain_reference(checked_member_type,((((parsed_var_decl).parsed_type))->span())))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::VarId var_id = TRY((((module)->add_variable(types::CheckedVariable(((parsed_var_decl).name),checked_member_type,((parsed_var_decl).is_mutable),((parsed_var_decl).span),JaktInternal::OptionalNone(),TRY((((*this).typecheck_visibility(((unchecked_member).visibility),checked_struct_scope_id)))))))));
TRY((((((structure).fields)).push(var_id))));
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_expression(const NonnullRefPtr<parser::ParsedExpression> expr,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> type_hint) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedStruct>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
String const& field = __jakt_match_value.field;
utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_indexed_struct(expr,field,scope_id,is_optional,safety_mode,span)))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Boolean>();bool const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Boolean>(val,span))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::NumericConstant>();lexer::NumericConstant const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_252; {
JaktInternal::Optional<types::TypeId> type_hint_unwrapped = type_hint;
if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
const types::StructId id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
if (((id).equals(optional_struct_id))){
(type_hint_unwrapped = ((args)[static_cast<i64>(0LL)]));
}
}
__jakt_var_252 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::I8>();
i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::I16>();
i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::I32>();
i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::I64>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } )))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::U8>();
u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::U16>();
u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::U32>();
u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::U64>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::USize>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::F32>();
f32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::F32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::F32() } )))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::F64>();
f64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::F64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::F64() } )))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::UnknownSigned>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).infer_signed_int(val,span,type_hint_unwrapped)))));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename lexer::NumericConstant::UnknownUnsigned>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).infer_unsigned_int(val,span,type_hint_unwrapped)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_236;

}
__jakt_label_236:; __jakt_var_252.release_value(); }));
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
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_253; {
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
TRY((((*this).unify_with_type(types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ),type_hint,span))));
__jakt_var_253 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::QuotedString>(val,span))); goto __jakt_label_237;

}
__jakt_label_237:; __jakt_var_253.release_value(); }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Call>();parser::ParsedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_254; {
__jakt_var_254 = TRY((((*this).typecheck_call(call,scope_id,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),safety_mode,type_hint,false)))); goto __jakt_label_238;

}
__jakt_label_238:; __jakt_var_254.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::MethodCall>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::ParsedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_255; {
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const types::TypeId checked_expr_type_id = ((checked_expr)->type());
bool found_optional = false;
const JaktInternal::Optional<types::StructOrEnumId> parent_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructOrEnumId>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(checked_expr_type_id));
switch(__jakt_match_variant.index()) {
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructOrEnumId>>( types::StructOrEnumId { typename types::StructOrEnumId::Struct(id) } ));
};/*case end*/
case 23: {
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
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::StructOrEnumId>> __jakt_var_256; {
__jakt_var_256 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructOrEnumId>,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::StructOrEnumId>> __jakt_var_257; {
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
JaktInternal::Optional<types::StructOrEnumId> struct_id = JaktInternal::OptionalNone();
if ((!(((id).equals(optional_struct_id))))){
TRY((((*this).error(TRY((String::formatted(String("Can't use ‘{}’ as an optional type in optional chained call"),((((*this).get_struct(id))).name)))),span))));
}
else {
(found_optional = true);
(struct_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructOrEnumId>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((args)[static_cast<i64>(0LL)])));
switch(__jakt_match_variant.index()) {
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::StructOrEnumId { typename types::StructOrEnumId::Struct(struct_id) } );
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue( types::StructOrEnumId { typename types::StructOrEnumId::Struct(struct_id) } );
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::StructOrEnumId { typename types::StructOrEnumId::Enum(id) } );
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue( types::StructOrEnumId { typename types::StructOrEnumId::Enum(id) } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::StructOrEnumId> __jakt_var_258; {
TRY((((*this).error(String("Can't use non-struct type as an optional type in optional chained call"),span))));
(found_optional = false);
__jakt_var_258 =  types::StructOrEnumId { typename types::StructOrEnumId::Struct(optional_struct_id) } ; goto __jakt_label_242;

}
__jakt_label_242:; __jakt_var_258.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
}

__jakt_var_257 = static_cast<JaktInternal::Optional<types::StructOrEnumId>>(struct_id.value_or_lazy_evaluated([&] { return  types::StructOrEnumId { typename types::StructOrEnumId::Struct(optional_struct_id) } ; })); goto __jakt_label_241;

}
__jakt_label_241:; __jakt_var_257.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructOrEnumId>>( types::StructOrEnumId { typename types::StructOrEnumId::Struct(id) } ));
}
}()))
; goto __jakt_label_240;

}
__jakt_label_240:; __jakt_var_256.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructOrEnumId>>( types::StructOrEnumId { typename types::StructOrEnumId::Enum(id) } ));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::StructOrEnumId>> __jakt_var_259; {
TRY((((*this).error(TRY((String::formatted(String("no methods available on value (type: {})"),TRY((((*this).type_name(checked_expr_type_id))))))),((checked_expr)->span())))));
const JaktInternal::Optional<types::StructOrEnumId> none = JaktInternal::OptionalNone();
__jakt_var_259 = none; goto __jakt_label_243;

}
__jakt_label_243:; __jakt_var_259.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
if ((is_optional && (!(found_optional)))){
TRY((((*this).error(TRY((String::formatted(String("Optional chain mismatch: expected optional chain, found {}"),TRY((((*this).type_name(checked_expr_type_id))))))),((checked_expr)->span())))));
}
const NonnullRefPtr<types::CheckedExpression> checked_call_expr = TRY((((*this).typecheck_call(call,scope_id,span,checked_expr,parent_id,safety_mode,type_hint,false))));
const types::TypeId type_id = ((checked_call_expr)->type());
__jakt_var_255 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_call_expr;
switch(__jakt_match_variant.index()) {
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_260; {
types::TypeId result_type = ((call).return_type);
if (is_optional){
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
(result_type = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({result_type}))))))))))));
}
__jakt_var_260 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::MethodCall>(checked_expr,call,span,is_optional,result_type))); goto __jakt_label_244;

}
__jakt_label_244:; __jakt_var_260.release_value(); }));
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(String("typecheck_call should return `CheckedExpression::Call()`")))));
}
};/*case end*/
}/*switch end*/
}()
)); goto __jakt_label_239;

}
__jakt_label_239:; __jakt_var_255.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Range>();JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> const& to = __jakt_match_value.to;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_261; {
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
const types::StructId range_struct_id = TRY((((*this).find_struct_in_prelude(String("Range")))));
const NonnullRefPtr<types::Type> range_type = TRY((types::Type::template create<typename types::Type::GenericInstance>(range_struct_id,(TRY((Array<types::TypeId>::create_with({((values_type_id).value_or(types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } )))})))))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(range_type))));
__jakt_var_261 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Range>(checked_from,checked_to,span,type_id))); goto __jakt_label_245;

}
__jakt_label_245:; __jakt_var_261.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::UnaryOp>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::UnaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_262; {
const NonnullRefPtr<types::CheckedExpression> checked_expr = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
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
const types::CheckedUnaryOperator checked_op = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedUnaryOperator, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
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
return JaktInternal::ExplicitValue(({ Optional<types::CheckedUnaryOperator> __jakt_var_263; {
const types::TypeId type_id = TRY((((*this).typecheck_typename(((cast).parsed_type()),scope_id,JaktInternal::OptionalNone()))));
const types::CheckedTypeCast checked_cast = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedTypeCast, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::TypeCast::Fallible>();
return JaktInternal::ExplicitValue(({ Optional<types::CheckedTypeCast> __jakt_var_264; {
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
const NonnullRefPtr<types::Type> optional_type = TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({type_id})))))));
const types::TypeId optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
__jakt_var_264 =  types::CheckedTypeCast { typename types::CheckedTypeCast::Fallible(optional_type_id) } ; goto __jakt_label_248;

}
__jakt_label_248:; __jakt_var_264.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::TypeCast::Infallible>();
return JaktInternal::ExplicitValue( types::CheckedTypeCast { typename types::CheckedTypeCast::Infallible(type_id) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
__jakt_var_263 =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::TypeCast(checked_cast) } ; goto __jakt_label_247;

}
__jakt_label_247:; __jakt_var_263.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::Is>();
NonnullRefPtr<parser::ParsedType> const& unchecked_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedUnaryOperator> __jakt_var_265; {
const bool old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
const types::TypeId type_id = TRY((((*this).typecheck_typename(unchecked_type,scope_id,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
types::CheckedUnaryOperator operator_is =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Is(type_id) } ;
if (((unchecked_type)->index() == 0 /* Name */)){
const String name = (unchecked_type->get<parser::ParsedType::Name>()).name;
const types::TypeId expr_type_id = ((checked_expr)->type());
if (((((*this).get_type(expr_type_id)))->index() == 23 /* Enum */)){
const types::EnumId enum_id = (((*this).get_type(expr_type_id))->get<types::Type::Enum>()).value;
const types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
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

__jakt_var_265 = operator_is; goto __jakt_label_249;

}
__jakt_label_249:; __jakt_var_265.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::UnaryOperator::IsEnumVariant>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& bindings = __jakt_match_value.bindings;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_is_enum_variant(checked_expr,inner,bindings,scope_id)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
__jakt_var_262 = TRY((((*this).typecheck_unary_operation(checked_expr,checked_op,span,scope_id,safety_mode)))); goto __jakt_label_246;

}
__jakt_label_246:; __jakt_var_262.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::BinaryOp>();NonnullRefPtr<parser::ParsedExpression> const& lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<parser::ParsedExpression> const& rhs = __jakt_match_value.rhs;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_266; {
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_lhs = JaktInternal::OptionalNone();
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_rhs = JaktInternal::OptionalNone();
if ((((lhs)->index() == 1 /* NumericConstant */) || ((lhs)->index() == 1 /* NumericConstant */))){
(checked_rhs = TRY((((*this).typecheck_expression_and_dereference_if_needed(rhs,scope_id,safety_mode,JaktInternal::OptionalNone(),span)))));
const types::TypeId hint = (((checked_rhs.value()))->type());
(checked_lhs = TRY((((*this).typecheck_expression_and_dereference_if_needed(lhs,scope_id,safety_mode,hint,span)))));
}
else {
(checked_lhs = TRY((((*this).typecheck_expression_and_dereference_if_needed(lhs,scope_id,safety_mode,JaktInternal::OptionalNone(),span)))));
const types::TypeId hint = (((checked_lhs.value()))->type());
(checked_rhs = TRY((((*this).typecheck_expression_and_dereference_if_needed(rhs,scope_id,safety_mode,hint,span)))));
}

const types::TypeId output_type = TRY((((*this).typecheck_binary_operation((checked_lhs.value()),op,(checked_rhs.value()),scope_id,span))));
__jakt_var_266 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::BinaryOp>((checked_lhs.value()),op,(checked_rhs.value()),span,output_type))); goto __jakt_label_250;

}
__jakt_label_250:; __jakt_var_266.release_value(); }));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedExpression::OptionalNone>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_267; {
JaktInternal::Optional<types::TypeId> type_hint_unwrapped = type_hint;
if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
const types::StructId id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
if (((id).equals(optional_struct_id))){
(type_hint_unwrapped = ((args)[static_cast<i64>(0LL)]));
}
}
__jakt_var_267 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::OptionalNone>(span,type_hint_unwrapped.value_or_lazy_evaluated([&] { return types::unknown_type_id(); })))); goto __jakt_label_251;

}
__jakt_label_251:; __jakt_var_267.release_value(); }));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::OptionalSome>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_268; {
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone()))));
const types::TypeId type_id = ((checked_expr)->type());
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
const NonnullRefPtr<types::Type> optional_type = TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({type_id})))))));
const types::TypeId optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
__jakt_var_268 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::OptionalSome>(checked_expr,span,optional_type_id))); goto __jakt_label_252;

}
__jakt_label_252:; __jakt_var_268.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Var>();String const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
const JaktInternal::Optional<types::CheckedVariable> var = TRY((((*this).find_var_in_scope(scope_id,name))));
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>,ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto __jakt_enum_value = (((var).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Var>((var.value()),span))));
}
else {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_269; {
TRY((((*this).error(TRY((String::formatted(String("Variable '{}' not found"),name))),span))));
__jakt_var_269 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Var>(types::CheckedVariable(name,((type_hint).value_or(types::unknown_type_id())),false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ),span))); goto __jakt_label_253;

}
__jakt_label_253:; __jakt_var_269.release_value(); }));
}
}()))
);
}
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::ForcedUnwrap>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_270; {
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const NonnullRefPtr<types::Type> type = ((*this).get_type(((checked_expr)->type())));
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
const types::StructId weakptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
const types::TypeId type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_271; {
types::TypeId inner_type_id = types::unknown_type_id();
if ((((id).equals(optional_struct_id)) || ((id).equals(weakptr_struct_id)))){
(inner_type_id = ((args)[static_cast<i64>(0LL)]));
}
else {
TRY((((*this).error(String("Forced unwrap only works on Optional"),span))));
}

__jakt_var_271 = inner_type_id; goto __jakt_label_255;

}
__jakt_label_255:; __jakt_var_271.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_272; {
TRY((((*this).error(String("Forced unwrap only works on Optional"),span))));
__jakt_var_272 = types::unknown_type_id(); goto __jakt_label_256;

}
__jakt_label_256:; __jakt_var_272.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
__jakt_var_270 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::ForcedUnwrap>(checked_expr,span,type_id))); goto __jakt_label_254;

}
__jakt_label_254:; __jakt_var_270.release_value(); }));
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
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_273; {
const types::TypeId VOID_TYPE_ID = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
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
const NonnullRefPtr<types::CheckedExpression> checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,JaktInternal::OptionalNone()))));
const types::TypeId type_id = ((checked_value)->type());
if (((type_id).equals(VOID_TYPE_ID))){
TRY((((*this).error(String("Cannot create a tuple that contains a value of type void"),((value)->span())))));
}
TRY((((checked_types).push(type_id))));
TRY((((checked_values).push(checked_value))));
}

}
}

const types::StructId tuple_struct_id = TRY((((*this).find_struct_in_prelude(String("Tuple")))));
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(tuple_struct_id,checked_types)))))));
__jakt_var_273 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::JaktTuple>(checked_values,span,type_id))); goto __jakt_label_257;

}
__jakt_label_257:; __jakt_var_273.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedExpression>();NonnullRefPtr<parser::ParsedExpression> const& base = __jakt_match_value.base;
NonnullRefPtr<parser::ParsedExpression> const& index = __jakt_match_value.index;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_274; {
const NonnullRefPtr<types::CheckedExpression> checked_base = TRY((((*this).typecheck_expression_and_dereference_if_needed(base,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const NonnullRefPtr<types::CheckedExpression> checked_index = TRY((((*this).typecheck_expression_and_dereference_if_needed(index,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
__jakt_var_274 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((checked_base)->type())));
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_275; {
const types::StructId array_struct_id = TRY((((*this).find_struct_in_prelude(String("Array")))));
const types::StructId array_slice_struct_id = TRY((((*this).find_struct_in_prelude(String("ArraySlice")))));
const types::StructId dictionary_struct_id = TRY((((*this).find_struct_in_prelude(String("Dictionary")))));
NonnullRefPtr<types::CheckedExpression> result = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Garbage>(span)));
if ((((id).equals(array_struct_id)) || ((id).equals(array_slice_struct_id)))){
if ((((*this).is_integer(((checked_index)->type()))) || ((checked_index)->index() == 8 /* Range */))){
const types::TypeId type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_index;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Range>();return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_276; {
const types::StructId array_slice_struct_id = TRY((((*this).find_struct_in_prelude(String("ArraySlice")))));
__jakt_var_276 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(array_slice_struct_id,args))))))); goto __jakt_label_260;

}
__jakt_label_260:; __jakt_var_276.release_value(); }));
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
__jakt_var_275 = result; goto __jakt_label_259;

}
__jakt_label_259:; __jakt_var_275.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_277; {
TRY((((*this).error(String("Index used on value that cannot be indexed"),span))));
__jakt_var_277 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Garbage>(span))); goto __jakt_label_261;

}
__jakt_label_261:; __jakt_var_277.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)); goto __jakt_label_258;

}
__jakt_label_258:; __jakt_var_274.release_value(); }));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedTuple>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_278; {
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const types::StructId tuple_struct_id = TRY((((*this).find_struct_in_prelude(String("Tuple")))));
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
types::TypeId expr_type_id = types::unknown_type_id();
if (((((*this).get_type(((checked_expr)->type()))))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(((checked_expr)->type())))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(((checked_expr)->type())))->get<types::Type::GenericInstance>()).args;
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
const types::TypeId inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((((*this).get_type(inner_type_id)))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type(inner_type_id))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type(inner_type_id))->get<types::Type::GenericInstance>()).args;
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

__jakt_var_278 = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedTuple>(checked_expr,index,span,is_optional,expr_type_id))); goto __jakt_label_262;

}
__jakt_label_262:; __jakt_var_278.release_value(); }));
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
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_279; {
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(inner_expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
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
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
const types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
const JaktInternal::Optional<types::CheckedEnumVariant> variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
(checked_enum_variant = variant);
const JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>> checked_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),(TRY((Array<parser::EnumVariantPatternArgument>::create_with({arg})))),span))));
if (((checked_bindings).has_value())){
const JaktInternal::Array<types::CheckedEnumVariantBinding> bindings = (checked_bindings.value());
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
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
const types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
const JaktInternal::Optional<types::CheckedEnumVariant> variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
(checked_enum_variant = variant);
const JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>> checked_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),(TRY((Array<parser::EnumVariantPatternArgument>::create_with({arg})))),span))));
if (((checked_bindings).has_value())){
const JaktInternal::Array<types::CheckedEnumVariantBinding> bindings = (checked_bindings.value());
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
__jakt_var_279 = output; goto __jakt_label_263;

}
__jakt_label_263:; __jakt_var_279.release_value(); }));
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
NonnullRefPtr<parser::ParsedType> const& return_type = __jakt_match_value.return_type;
parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_lambda(captures,params,can_throw,return_type,block,span,scope_id,safety_mode)))));
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

ErrorOr<void> typechecker::Typechecker::dump_type_hint(const types::TypeId type_id,const utility::Span span) const {
{
outln(String("{{\"type\":\"hint\",\"file_id\":{},\"position\":{},\"typename\":\"{}\"}}"),((((span).file_id)).id),((span).end),TRY((((*this).type_name(type_id)))));
}
return {};
}

typechecker::Typechecker::Typechecker(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, types::ModuleId a_current_module_id, JaktInternal::Optional<types::TypeId> a_current_struct_type_id, JaktInternal::Optional<types::FunctionId> a_current_function_id, bool a_inside_defer, size_t a_checkidx, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, types::GenericInferences a_generic_inferences) :compiler(a_compiler), program(a_program), current_module_id(a_current_module_id), current_struct_type_id(a_current_struct_type_id), current_function_id(a_current_function_id), inside_defer(a_inside_defer), checkidx(a_checkidx), ignore_errors(a_ignore_errors), dump_type_hints(a_dump_type_hints), dump_try_hints(a_dump_try_hints), lambda_count(a_lambda_count), generic_inferences(a_generic_inferences){}

bool typechecker::Typechecker::is_subclass_of(const types::TypeId ancestor_type_id,const types::TypeId child_type_id) const {
{
const NonnullRefPtr<types::Type> ancestor_type = ((*this).get_type(ancestor_type_id));
const NonnullRefPtr<types::Type> child_type = ((*this).get_type(child_type_id));
if (((ancestor_type)->index() == 22 /* Struct */)){
const types::StructId ancestor_struct_id = (ancestor_type->get<types::Type::Struct>()).value;
if (((child_type)->index() == 22 /* Struct */)){
const types::StructId child_struct_id = (child_type->get<types::Type::Struct>()).value;
types::CheckedStruct ancestor_struct = ((*this).get_struct(ancestor_struct_id));
types::StructId current_struct_id = child_struct_id;
for (;;){
const types::CheckedStruct current_struct = ((*this).get_struct(current_struct_id));
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

ErrorOr<types::ModuleId> typechecker::Typechecker::create_module(const String name,const bool is_root,const JaktInternal::Optional<String> path) {
{
const size_t new_id = ((((((*this).program))->modules)).size());
const types::ModuleId module_id = types::ModuleId(new_id);
const NonnullRefPtr<types::Module> module = TRY((types::Module::create(module_id,name,(TRY((Array<NonnullRefPtr<types::CheckedFunction>>::create_with({})))),(TRY((Array<types::CheckedStruct>::create_with({})))),(TRY((Array<types::CheckedEnum>::create_with({})))),(TRY((Array<NonnullRefPtr<types::Scope>>::create_with({})))),(TRY((Array<NonnullRefPtr<types::Type>>::create_with({TRY((types::Type::template create<typename types::Type::Void>())), TRY((types::Type::template create<typename types::Type::Bool>())), TRY((types::Type::template create<typename types::Type::U8>())), TRY((types::Type::template create<typename types::Type::U16>())), TRY((types::Type::template create<typename types::Type::U32>())), TRY((types::Type::template create<typename types::Type::U64>())), TRY((types::Type::template create<typename types::Type::I8>())), TRY((types::Type::template create<typename types::Type::I16>())), TRY((types::Type::template create<typename types::Type::I32>())), TRY((types::Type::template create<typename types::Type::I64>())), TRY((types::Type::template create<typename types::Type::F32>())), TRY((types::Type::template create<typename types::Type::F64>())), TRY((types::Type::template create<typename types::Type::Usize>())), TRY((types::Type::template create<typename types::Type::JaktString>())), TRY((types::Type::template create<typename types::Type::CChar>())), TRY((types::Type::template create<typename types::Type::CInt>())), TRY((types::Type::template create<typename types::Type::Unknown>())), TRY((types::Type::template create<typename types::Type::Never>()))})))),(TRY((Array<types::CheckedVariable>::create_with({})))),(TRY((Array<types::ModuleId>::create_with({})))),path.value_or_lazy_evaluated([&] { return (((((((*this).compiler))->current_file_path()).value()))->path); }),is_root)));
TRY((((((((*this).program))->modules)).push(module))));
return (module_id);
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_block_statement(const parser::ParsedBlock parsed_block,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
const types::CheckedBlock checked_block = TRY((((*this).typecheck_block(parsed_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(String("A block used as a statement cannot yield values, as the value cannot be observed in any way"),(((parsed_block).find_yield_span()).value())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Block>(checked_block,span))));
}
}

ErrorOr<JaktInternal::Optional<types::FieldRecord>> typechecker::Typechecker::lookup_struct_field(const types::StructId struct_id,const String name) const {
{
JaktInternal::Array<types::StructId> chain = (TRY((Array<types::StructId>::create_with({}))));
JaktInternal::Optional<types::StructId> current = static_cast<JaktInternal::Optional<types::StructId>>(struct_id);
TRY((((chain).push((current.value())))));
while (((current).has_value())){
const JaktInternal::Optional<types::StructId> parent = ((((*this).get_struct((current.value())))).super_struct_id);
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
JaktInternal::ArrayIterator<types::VarId> _magic = ((((((*this).get_struct(current_struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field_id = (_magic_value.value());
{
const types::CheckedVariable field = ((*this).get_variable(field_id));
if ((((field).name) == name)){
return (types::FieldRecord(current_struct_id,field_id));
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

ErrorOr<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,parser::ParsedBlock,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>>> typechecker::Typechecker::expand_context_for_bindings(const NonnullRefPtr<parser::ParsedExpression> condition,const JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> acc,const parser::ParsedBlock then_block,const JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> else_statement,const utility::Span span) {
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,parser::ParsedBlock,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>>>>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.index()) {
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::BinaryOp>();NonnullRefPtr<parser::ParsedExpression> const& lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<parser::ParsedExpression> const& rhs = __jakt_match_value.rhs;
{
if (((op).index() == 18 /* LogicalAnd */)){
const JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,parser::ParsedBlock,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>> rhs_condition_rhs_then_block_rhs_else_statement_ = TRY((((*this).expand_context_for_bindings(rhs,acc,then_block,else_statement,span))));
const NonnullRefPtr<parser::ParsedExpression> rhs_condition = ((rhs_condition_rhs_then_block_rhs_else_statement_).get<0>());
const parser::ParsedBlock rhs_then_block = ((rhs_condition_rhs_then_block_rhs_else_statement_).get<1>());
const JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> rhs_else_statement = ((rhs_condition_rhs_then_block_rhs_else_statement_).get<2>());

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
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,parser::ParsedBlock,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::UnaryOperator::IsEnumVariant>();NonnullRefPtr<parser::ParsedType> const& inner = __jakt_match_value.inner;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& bindings = __jakt_match_value.bindings;
{
const NonnullRefPtr<parser::ParsedExpression> unary_op_single_condition = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::UnaryOp>(expr, parser::UnaryOperator { typename parser::UnaryOperator::Is(inner) } ,span)));
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
const parser::ParsedVarDecl var = parser::ParsedVarDecl(((binding).binding),TRY((parser::ParsedType::template create<typename parser::ParsedType::Empty>())),false,JaktInternal::OptionalNone(),((binding).span));
const NonnullRefPtr<parser::ParsedExpression> enum_variant_arg = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::EnumVariantArg>(expr,binding,inner,span)));
TRY((((outer_if_stmts).push(TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::VarDecl>(var,enum_variant_arg,span)))))));
}

}
}

NonnullRefPtr<parser::ParsedExpression> inner_condition = condition;
parser::ParsedBlock new_then_block = then_block;
JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> new_else_statement = else_statement;
if (((acc).has_value())){
(inner_condition = (acc.value()));
TRY((((outer_if_stmts).push(TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::If>(inner_condition,then_block,else_statement,span)))))));
}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<parser::ParsedStatement>> _magic = ((((then_block).stmts)).iterator());
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

(new_then_block = parser::ParsedBlock(outer_if_stmts));
return (TRY((((*this).expand_context_for_bindings(unary_op_single_condition,JaktInternal::OptionalNone(),new_then_block,new_else_statement,span)))));
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

ErrorOr<JaktInternal::Optional<types::TypeId>> typechecker::Typechecker::unify(const types::TypeId lhs,const utility::Span lhs_span,const types::TypeId rhs,const utility::Span rhs_span) {
{
if ((!(TRY((((*this).check_types_for_compat(lhs,rhs,((((*this).generic_inferences))),lhs_span))))))){
return (JaktInternal::OptionalNone());
}
return (TRY((((*this).substitute_typevars_in_type(lhs,((*this).generic_inferences))))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::find_type_in_prelude(const String name) const {
{
const types::ScopeId scope_id = ((*this).prelude_scope_id());
const JaktInternal::Optional<types::TypeId> type_id = TRY((((*this).find_type_in_scope(scope_id,name))));
if (((type_id).has_value())){
return (((type_id).value()));
}
TRY((((((*this).compiler))->panic(TRY((String::formatted(String("internal error: {} builtin definition not found"),name)))))));
}
}

bool typechecker::Typechecker::is_numeric(const types::TypeId type_id) const {
{
return (((((*this).program))->is_numeric(type_id)));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_array(const types::ScopeId scope_id,const JaktInternal::Array<NonnullRefPtr<parser::ParsedExpression>> values,const JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> fill_size,const utility::Span span,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
if ((!(((TRY((((*this).get_scope(scope_id)))))->can_throw)))){
const String message = String("Array initialization inside non-throwing scope");
if (((((*this).current_function_id)).has_value())){
const NonnullRefPtr<types::CheckedFunction> current_function = ((*this).get_function((((*this).current_function_id).value())));
TRY((((*this).error_with_hint(message,span,TRY((String::formatted(String("Add `throws` keyword to function {}"),((current_function)->name)))),((current_function)->name_span)))));
}
else {
TRY((((*this).error(message,span))));
}

}
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> repeat = JaktInternal::OptionalNone();
if (((fill_size).has_value())){
const NonnullRefPtr<parser::ParsedExpression> fill_size_value = ((fill_size).value());
const NonnullRefPtr<types::CheckedExpression> fill_size_checked = TRY((((*this).typecheck_expression_and_dereference_if_needed(fill_size_value,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const types::TypeId fill_size_type = ((fill_size_checked)->type());
if ((!(((*this).is_integer(fill_size_type))))){
TRY((((*this).error(TRY((String::formatted(String("Type '{}' is not convertible to an integer. Only integer values can be array fill size expressions."),TRY((((*this).type_name(fill_size_type))))))),((fill_size_value)->span())))));
}
(repeat = fill_size_checked);
}
const types::StructId array_struct_id = TRY((((*this).find_struct_in_prelude(String("Array")))));
types::TypeId inner_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> inferred_type_span = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> inner_hint = JaktInternal::OptionalNone();
if (((type_hint).has_value())){
if (((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */)){
const types::StructId id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
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
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,inner_hint))));
const types::TypeId current_value_type_id = ((checked_expr)->type());
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
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(array_struct_id,(TRY((Array<types::TypeId>::create_with({inner_type_id})))))))))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::JaktArray>(vals,repeat,span,type_id,inner_type_id))));
}
}

ErrorOr<bool> typechecker::Typechecker::add_var_to_scope(const types::ScopeId scope_id,const String name,const types::VarId var_id,const utility::Span span) {
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
const types::CheckedVariable variable_ = ((*this).get_variable(((existing_var).get<1>())));
TRY((((*this).error_with_hint(TRY((String::formatted(String("Redefinition of variable ‘{}’"),name))),span,String("previous definition here"),((variable_).definition_span)))));
}
}

}
}

TRY((((((scope)->vars)).set(name,var_id))));
return (true);
}
}

ErrorOr<NonnullRefPtr<types::Scope>> typechecker::Typechecker::get_scope(const types::ScopeId id) const {
{
return (TRY((((((*this).program))->get_scope(id)))));
}
}

ErrorOr<bool> typechecker::Typechecker::check_types_for_compat(const types::TypeId lhs_type_id,const types::TypeId rhs_type_id,types::GenericInferences& generic_inferences,const utility::Span span) {
{
if (((((lhs_type_id).equals(rhs_type_id)) || ((lhs_type_id).equals(types::unknown_type_id()))) || ((rhs_type_id).equals(types::unknown_type_id())))){
return (true);
}
const NonnullRefPtr<types::Type> lhs_type = ((*this).get_type(lhs_type_id));
const NonnullRefPtr<types::Type> rhs_type = ((*this).get_type(rhs_type_id));
const String lhs_type_id_string = TRY((((lhs_type_id).to_string())));
const String rhs_type_id_string = TRY((((rhs_type_id).to_string())));
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
const types::StructId weakptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
const types::StructId array_struct_id = TRY((((*this).find_struct_in_prelude(String("Array")))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *lhs_type;
switch(__jakt_match_variant.index()) {
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
{
JaktInternal::Optional<String> seen_type_id_string = ((((generic_inferences))).get(lhs_type_id_string));
if (((seen_type_id_string).has_value())){
const types::TypeId seen_type_id = TRY((types::TypeId::from_string((seen_type_id_string.value()))));
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
const types::EnumId rhs_enum_id = (rhs_type->get<types::Type::GenericEnumInstance>()).id;
const JaktInternal::Array<types::TypeId> rhs_args = (rhs_type->get<types::Type::GenericEnumInstance>()).args;
if (((lhs_enum_id).equals(rhs_enum_id))){
const types::CheckedEnum lhs_enum = ((*this).get_enum(lhs_enum_id));
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
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::Array<types::TypeId> const& lhs_params = __jakt_match_value.params;
bool const& lhs_can_throw = __jakt_match_value.can_throw;
types::TypeId const& lhs_return_type_id = __jakt_match_value.return_type_id;
{
if (((rhs_type)->index() == 27 /* Function */)){
const JaktInternal::Array<types::TypeId> rhs_params = (rhs_type->get<types::Type::Function>()).params;
const bool rhs_can_throw = (rhs_type->get<types::Type::Function>()).can_throw;
const types::TypeId rhs_return_type_id = (rhs_type->get<types::Type::Function>()).return_type_id;
if ((!((lhs_can_throw == rhs_can_throw)))){
const String lhs_throw = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<bool>>{
auto __jakt_enum_value = (lhs_can_throw);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("Yes"));
}
else {
return JaktInternal::ExplicitValue(String("No"));
}
}()))
;
const String rhs_throw = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<bool>>{
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
const types::StructId lhs_struct_id = id;
const JaktInternal::Array<types::TypeId> lhs_args = args;
if ((((lhs_struct_id).equals(optional_struct_id)) || ((lhs_struct_id).equals(weakptr_struct_id)))){
if ((((lhs_args).size()) > static_cast<size_t>(0ULL))){
if (((((lhs_args)[static_cast<i64>(0LL)])).equals(rhs_type_id))){
return (true);
}
}
}
if (((rhs_type)->index() == 19 /* GenericInstance */)){
const types::StructId id = (rhs_type->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (rhs_type->get<types::Type::GenericInstance>()).args;
const types::StructId rhs_struct_id = id;
if (((lhs_struct_id).equals(rhs_struct_id))){
const JaktInternal::Array<types::TypeId> rhs_args = args;
const types::CheckedStruct lhs_struct = ((*this).get_struct(lhs_struct_id));
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
const types::TypeId array_value_type_id = ((args)[static_cast<i64>(0LL)]);
if (((array_value_type_id).equals(types::unknown_type_id()))){
return (true);
}
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
case 23: {
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
const types::CheckedEnum lhs_enum = ((*this).get_enum(enum_id));
if ((((args).size()) != ((((lhs_enum).generic_parameters)).size()))){
TRY((((*this).error(TRY((String::formatted(String("mismatched number of generic parameters for {}"),((lhs_enum).name)))),span))));
return (false);
}
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((((lhs_enum).generic_parameters))[idx]),((args)[idx]),generic_inferences,span))))))){
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
const JaktInternal::Optional<String> seen_type_id_string = ((((generic_inferences))).get(rhs_type_id_string));
if (((seen_type_id_string).has_value())){
if ((((seen_type_id_string).value()) != lhs_type_id_string)){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(lhs_type_id)))),TRY((((*this).type_name(TRY((types::TypeId::from_string(((seen_type_id_string).value()))))))))))),span))));
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
case 22: {
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
const types::CheckedStruct lhs_struct = ((*this).get_struct(lhs_struct_id));
if ((((args).size()) != ((((lhs_struct).generic_parameters)).size()))){
TRY((((*this).error(TRY((String::formatted(String("mismatched number of generic parameters for {}"),((lhs_struct).name)))),span))));
return (false);
}
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((((lhs_struct).generic_parameters))[idx]),((args)[idx]),generic_inferences,span))))))){
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
const JaktInternal::Optional<String> seen_type_id_string = ((((generic_inferences))).get(rhs_type_id_string));
if (((seen_type_id_string).has_value())){
if ((((seen_type_id_string).value()) != lhs_type_id_string)){
TRY((((*this).error(TRY((String::formatted(String("Type mismatch: expected ‘{}’, but got ‘{}’"),TRY((((*this).type_name(TRY((types::TypeId::from_string(((seen_type_id_string).value())))))))),TRY((((*this).type_name(rhs_type_id))))))),span))));
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
const NonnullRefPtr<types::Type> rhs_type = ((*this).get_type(rhs_type_id));
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
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& lhs_rawptr_type_id = __jakt_match_value.value;
{
if (((lhs_rawptr_type_id).equals(rhs_type_id))){
return (true);
}
if (((rhs_type)->index() == 24 /* RawPtr */)){
const types::TypeId rhs_rawptr_type_id = (rhs_type->get<types::Type::RawPtr>()).value;
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
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& lhs_inner_type_id = __jakt_match_value.value;
{
if (((rhs_type)->index() == 25 /* Reference */)){
const types::TypeId rhs_inner_type_id = (rhs_type->get<types::Type::Reference>()).value;
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

ErrorOr<JaktInternal::Optional<types::CheckedVariable>> typechecker::Typechecker::find_var_in_scope(const types::ScopeId scope_id,const String var) const {
{
return (TRY((((((*this).program))->find_var_in_scope(scope_id,var)))));
}
}

types::CheckedStruct typechecker::Typechecker::get_struct(const types::StructId id) const {
{
return (((((*this).program))->get_struct(id)));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_lambda(const JaktInternal::Array<parser::ParsedCapture> captures,const JaktInternal::Array<parser::ParsedParameter> params,const bool can_throw,const NonnullRefPtr<parser::ParsedType> return_type,const parser::ParsedBlock block,const utility::Span span,const types::ScopeId scope_id,const types::SafetyMode safety_mode) {
{
const NonnullRefPtr<parser::ParsedType> synthetic_type = TRY((parser::ParsedType::template create<typename parser::ParsedType::Function>(params,can_throw,return_type,span)));
const JaktInternal::Dictionary<String,String> old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_280([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
types::TypeId type_id = TRY((((*this).typecheck_typename(synthetic_type,scope_id,JaktInternal::OptionalNone()))));
JaktInternal::Tuple<types::TypeId,types::FunctionId> return_type_id_pseudo_function_id_ = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<types::TypeId,types::FunctionId>, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 27: {
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

const types::ScopeId lambda_scope_id = TRY((((*this).create_scope(scope_id,can_throw,String("lambda")))));
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
const types::CheckedParameter checked_param = TRY((((*this).typecheck_parameter(param,scope_id,first,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
TRY((((checked_params).push(checked_param))));
const types::VarId var_id = TRY((((module)->add_variable(((checked_param).variable)))));
TRY((((*this).add_var_to_scope(lambda_scope_id,((((checked_param).variable)).name),var_id,((((checked_param).variable)).definition_span)))));
(first = false);
}

}
}

const JaktInternal::Optional<types::FunctionId> previous_function_id = ((*this).current_function_id);
(((*this).current_function_id) = pseudo_function_id);
ScopeGuard __jakt_var_281([&] {
{
(((*this).current_function_id) = previous_function_id);
}

});
const types::CheckedBlock checked_block = TRY((((*this).typecheck_block(block,lambda_scope_id,safety_mode,JaktInternal::OptionalNone()))));
if ((((return_type_id).equals(types::unknown_type_id())) && (!(((((checked_block).statements)).is_empty()))))){
if ((((((((checked_block).statements)).last()).value()))->index() == 8 /* Return */)){
const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> val = ((((((checked_block).statements)).last()).value())->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
(return_type_id = TRY((((*this).resolve_type_var((((val.value()))->type()),lambda_scope_id)))));
(type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 27: {
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
}
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::Function>(checked_captures,checked_params,can_throw,return_type_id,checked_block,span,type_id,pseudo_function_id))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_try(const NonnullRefPtr<parser::ParsedExpression> expr,const JaktInternal::Optional<parser::ParsedBlock> catch_block,const JaktInternal::Optional<String> catch_name,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span,const JaktInternal::Optional<types::TypeId> type_hint) {
{
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,type_hint))));
const types::StructId error_struct_id = TRY((((*this).find_struct_in_prelude(String("Error")))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
JaktInternal::Optional<types::CheckedBlock> checked_catch_block = JaktInternal::OptionalNone();
const types::TypeId expression_type_id = ((checked_expr)->type());
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
const NonnullRefPtr<types::Type> optional_type = TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({expression_type_id})))))));
const types::TypeId optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
types::TypeId type_id = optional_type_id;
if (((catch_block).has_value())){
const types::ScopeId catch_scope_id = TRY((((*this).create_scope(scope_id,true,String("catch")))));
if (((catch_name).has_value())){
const types::StructId error_struct_id = TRY((((*this).find_struct_in_prelude(String("Error")))));
const types::CheckedVariable error_decl = types::CheckedVariable((catch_name.value()),((((*this).get_struct(error_struct_id))).type_id),false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::VarId error_id = TRY((((module)->add_variable(error_decl))));
TRY((((*this).add_var_to_scope(catch_scope_id,(catch_name.value()),error_id,span))));
}
const types::CheckedBlock block = TRY((((*this).typecheck_block((catch_block.value()),catch_scope_id,safety_mode,JaktInternal::OptionalNone()))));
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

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_return(const JaktInternal::Optional<NonnullRefPtr<parser::ParsedExpression>> expr,const utility::Span span,const types::ScopeId scope_id,const types::SafetyMode safety_mode) {
{
if (((*this).inside_defer)){
TRY((((*this).error(String("‘return’ is not allowed inside ‘defer’"),span))));
}
if ((!(((expr).has_value())))){
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Return>(JaktInternal::OptionalNone(),span))));
}
if (((!((((((*this).current_function_id)).has_value()) && ((((*this).get_function((((*this).current_function_id).value()))))->is_comptime)))) && (((expr.value()))->index() == 25 /* Function */))){
TRY((((*this).error(String("Returning a function is not currently supported"),span))));
}
JaktInternal::Optional<types::TypeId> type_hint = JaktInternal::OptionalNone();
if (((((*this).current_function_id)).has_value())){
(type_hint = static_cast<JaktInternal::Optional<types::TypeId>>(((((*this).get_function((((*this).current_function_id).value()))))->return_type_id)));
}
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression((expr.value()),scope_id,safety_mode,type_hint))));
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Return>(checked_expr,span))));
}
}

ErrorOr<void> typechecker::Typechecker::include_prelude() {
{
const String module_name = String("__prelude__");
const NonnullRefPtr<utility::FilePath> file_name = TRY((utility::FilePath::make(module_name)));
const JaktInternal::Array<u8> file_contents = (TRY((Array<u8>::create_with({static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(83), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(83), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(83), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(98), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(98), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(121), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(66), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(106), static_cast<u8>(115), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(66), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(87), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(80), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(117), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(40), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(111), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(75), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(66), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(66), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(111), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(69), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(69), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(117), static_cast<u8>(102), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(119), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(100), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(108), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(95), static_cast<u8>(95), static_cast<u8>(95), static_cast<u8>(106), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(73), static_cast<u8>(88), static_cast<u8>(77), static_cast<u8>(69), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(111), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(67), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(119), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(107), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(103), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(73), static_cast<u8>(76), static_cast<u8>(69), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(109), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(73), static_cast<u8>(76), static_cast<u8>(69), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(99), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(73), static_cast<u8>(76), static_cast<u8>(69), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(111), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(73), static_cast<u8>(76), static_cast<u8>(69), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(111), static_cast<u8>(102), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(73), static_cast<u8>(76), static_cast<u8>(69), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(121), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(109), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(10)}))));
const JaktInternal::Optional<utility::FileId> old_file_id = ((((*this).compiler))->current_file);
const JaktInternal::Array<u8> old_file_contents = ((((*this).compiler))->current_file_contents);
ScopeGuard __jakt_var_282([&] {
{
(((((*this).compiler))->current_file) = old_file_id);
(((((*this).compiler))->current_file_contents) = old_file_contents);
}

});
const utility::FileId file_id = TRY((((((*this).compiler))->get_file_id_or_register(file_name))));
(((((*this).compiler))->current_file) = file_id);
(((((*this).compiler))->current_file_contents) = file_contents);
const types::ModuleId prelude_module_id = TRY((((*this).create_module(module_name,false,JaktInternal::OptionalNone()))));
(((*this).current_module_id) = prelude_module_id);
TRY((((((*this).program))->set_loaded_module(module_name,types::LoadedModule(prelude_module_id,file_id)))));
const types::ScopeId prelude_scope_id = TRY((((*this).create_scope(JaktInternal::OptionalNone(),false,String("prelude")))));
const JaktInternal::Array<lexer::Token> tokens = TRY((lexer::Lexer::lex(((*this).compiler))));
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
const parser::ParsedNamespace parsed_namespace = TRY((parser::Parser::parse(((*this).compiler),tokens)));
if (((((*this).compiler))->dump_parser)){
outln(String("{:#}"),parsed_namespace);
}
((((*this).compiler))->dbg_println(TRY((String::formatted(String("before typechecking parsed prelude, modules ‘{}’"),((((*this).program))->modules))))));
TRY((((*this).typecheck_module(parsed_namespace,prelude_scope_id))));
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_fields(const parser::ParsedNamespace parsed_namespace,const types::ScopeId scope_id) {
{
const JaktInternal::Array<types::ScopeId> children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
const parser::ParsedNamespace child_namespace = ((((parsed_namespace).namespaces))[i]);
const types::ScopeId child_namespace_scope_id = ((children)[i]);
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
const JaktInternal::Optional<types::StructId> struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
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

ErrorOr<void> typechecker::Typechecker::typecheck_and_specialize_generic_function(const types::FunctionId function_id,const JaktInternal::Array<types::TypeId> generic_arguments,const types::ScopeId parent_scope_id,const JaktInternal::Optional<types::TypeId> this_type_id,const types::GenericInferences generic_substitutions) {
{
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function(function_id));
TRY((((((((checked_function)->generics))->specializations)).push(generic_arguments))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::FunctionId function_id = ((module)->next_function_id());
if ((!(((((checked_function)->parsed_function)).has_value())))){
return {};
}
parser::ParsedFunction parsed_function = ((checked_function)->to_parsed_function());
const types::ScopeId scope_id = TRY((((*this).create_scope(parent_scope_id,((parsed_function).can_throw),TRY((String::formatted(String("function-specialization({})"),((parsed_function).name))))))));
if ((((((parsed_function).generic_parameters)).size()) != ((generic_arguments).size()))){
TRY((((*this).error(TRY((String::formatted(String("Generic function {} expects {} generic arguments, but {} were given"),((parsed_function).name),((((parsed_function).generic_parameters)).size()),((generic_arguments).size())))),((parsed_function).name_span)))));
}
const utility::Span span = ((parsed_function).name_span);
{
JaktInternal::DictionaryIterator<String,String> _magic = ((generic_substitutions).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,String>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,String> substitution = (_magic_value.value());
{
if (((((*this).get_type(TRY((types::TypeId::from_string(((substitution).get<0>())))))))->index() == 18 /* TypeVariable */)){
const String type_name = (((*this).get_type(TRY((types::TypeId::from_string(((substitution).get<0>()))))))->get<types::Type::TypeVariable>()).value;
TRY((((*this).add_type_to_scope(scope_id,type_name,TRY((types::TypeId::from_string(((substitution).get<1>())))),span))));
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

ErrorOr<JaktInternal::Optional<parser::ParsedNamespace>> typechecker::Typechecker::lex_and_parse_file_contents(const utility::FileId file_id) {
{
const utility::FileId old_file_id = (((((*this).compiler))->current_file).value());
if ((!(((((*this).compiler))->set_current_file(file_id))))){
return (JaktInternal::OptionalNone());
}
ScopeGuard __jakt_var_283([&] {
((((*this).compiler))->set_current_file(old_file_id));
});
const JaktInternal::Array<lexer::Token> tokens = TRY((lexer::Lexer::lex(((*this).compiler))));
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
const parser::ParsedNamespace parsed_namespace = TRY((parser::Parser::parse(((*this).compiler),tokens)));
if (((((*this).compiler))->dump_parser)){
outln(String("{:#}"),parsed_namespace);
}
return (parsed_namespace);
}
}

types::BlockControlFlow typechecker::Typechecker::statement_control_flow(const NonnullRefPtr<types::CheckedStatement> statement) const {
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

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_unary_operation(const NonnullRefPtr<types::CheckedExpression> checked_expr,const types::CheckedUnaryOperator checked_op,const utility::Span span,const types::ScopeId scope_id,const types::SafetyMode safety_mode) {
{
const types::TypeId expr_type_id = ((checked_expr)->type());
const NonnullRefPtr<types::Type> expr_type = ((*this).get_type(expr_type_id));
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
case 24: {
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
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
{
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
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

ErrorOr<types::TypeId> typechecker::Typechecker::resolve_type_var(const types::TypeId type_var_type_id,const types::ScopeId scope_id) const {
{
types::TypeId current_type_id = type_var_type_id;
for (;;){
const NonnullRefPtr<types::Type> type_var_type = ((*this).get_type(current_type_id));
if (((type_var_type)->index() == 18 /* TypeVariable */)){
const String type_name = (type_var_type->get<types::Type::TypeVariable>()).value;
const JaktInternal::Optional<types::TypeId> maybe_found_type_id = TRY((((*this).find_type_in_scope(scope_id,type_name))));
if (((maybe_found_type_id).has_value())){
const types::TypeId found_type_id = ((maybe_found_type_id).value());
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

NonnullRefPtr<types::CheckedFunction> typechecker::Typechecker::get_function(const types::FunctionId id) const {
{
return (((((*this).program))->get_function(id)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_predecl(const parser::ParsedRecord parsed_record,const types::StructId struct_id,const types::ScopeId scope_id) {
{
const JaktInternal::Dictionary<String,String> old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
ScopeGuard __jakt_var_284([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
const types::TypeId struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
const types::ScopeId struct_scope_id = ((((((((*this).current_module()))->structures))[((struct_id).id)])).scope_id);
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
const types::TypeId super_type_id = TRY((((*this).typecheck_typename((super_parsed_type.value()),scope_id,JaktInternal::OptionalNone()))));
const NonnullRefPtr<types::Type> super_type = ((*this).get_type(super_type_id));
if (((super_type)->index() == 22 /* Struct */)){
const types::StructId struct_id = (super_type->get<types::Type::Struct>()).value;
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
const types::TypeId super_type_id = TRY((((*this).typecheck_typename((super_parsed_type.value()),scope_id,JaktInternal::OptionalNone()))));
const NonnullRefPtr<types::Type> super_type = ((*this).get_type(super_type_id));
if (((super_type)->index() == 22 /* Struct */)){
const types::StructId struct_id = (super_type->get<types::Type::Struct>()).value;
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
(((((module)->structures))[((struct_id).id)]) = types::CheckedStruct(((parsed_record).name),((parsed_record).name_span),(TRY((Array<types::TypeId>::create_with({})))),(TRY((Array<types::VarId>::create_with({})))),struct_scope_id,((parsed_record).definition_linkage),((parsed_record).record_type),struct_type_id,super_struct_id));
JaktInternal::Array<types::TypeId> generic_parameters = ((((((module)->structures))[((struct_id).id)])).generic_parameters);
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
const types::TypeId parameter_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((generic_parameters).push(parameter_type_id))));
TRY((((*this).add_type_to_scope(struct_scope_id,((gen_parameter).name),parameter_type_id,((gen_parameter).span)))));
}

}
}

const bool is_extern = ((((parsed_record).definition_linkage)).index() == 1 /* External */);
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((parsed_record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
const parser::ParsedFunction func = ((method).parsed_function);
const types::ScopeId method_scope_id = TRY((((*this).create_scope(struct_scope_id,((func).can_throw),TRY((String::formatted(String("method({}::{})"),((parsed_record).name),((func).name))))))));
const types::ScopeId block_scope_id = TRY((((*this).create_scope(method_scope_id,((func).can_throw),TRY((String::formatted(String("method-block({}::{})"),((parsed_record).name),((func).name))))))));
const bool is_generic = ((!(((((parsed_record).generic_parameters)).is_empty()))) || (!(((((func).generic_parameters)).is_empty()))));
NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((func).name),((func).name_span),TRY((((*this).typecheck_visibility(((method).visibility),struct_scope_id)))),types::unknown_type_id(),((func).return_type_span),(TRY((Array<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::create((TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),((func).can_throw),((func).type),((func).linkage),method_scope_id,((!(is_generic)) || is_extern),((method).parsed_function),((((method).parsed_function)).is_comptime),((method).is_virtual),((method).is_override))));
const types::FunctionId function_id = TRY((((module)->add_function(checked_function))));
const JaktInternal::Optional<types::FunctionId> previous_index = ((*this).current_function_id);
(((*this).current_function_id) = function_id);
JaktInternal::Optional<types::ScopeId> check_scope = JaktInternal::OptionalNone();
if (is_generic){
(check_scope = TRY((((*this).create_scope(method_scope_id,((func).can_throw),TRY((String::formatted(String("method-checking({}::{})"),((parsed_record).name),((func).name)))))))));
}
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
const types::TypeId type_var_type_id = types::TypeId(((*this).current_module_id),(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((((((checked_function)->generics))->params)).push( types::FunctionGenericParameter { typename types::FunctionGenericParameter::Parameter(type_var_type_id) } ))));
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
const types::CheckedVariable checked_variable = types::CheckedVariable(((((param).variable)).name),struct_type_id,((((param).variable)).is_mutable),((((param).variable)).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,JaktInternal::OptionalNone())))));
if (((check_scope).has_value())){
const types::VarId var_id = TRY((((module)->add_variable(checked_variable))));
TRY((((*this).add_var_to_scope((check_scope.value()),((((param).variable)).name),var_id,((((param).variable)).span)))));
}
}
else {
const types::TypeId param_type = TRY((((*this).typecheck_typename(((((param).variable)).parsed_type),method_scope_id,((((param).variable)).name)))));
const types::CheckedVariable checked_variable = types::CheckedVariable(((((param).variable)).name),param_type,((((param).variable)).is_mutable),((((param).variable)).span),((((((param).variable)).parsed_type))->span()), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_default_value = JaktInternal::OptionalNone();
if (((((param).default_argument)).has_value())){
NonnullRefPtr<types::CheckedExpression> checked_default_value_expr = TRY((((*this).typecheck_expression((((param).default_argument).value()),scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,param_type))));
if (((checked_default_value_expr)->index() == 22 /* OptionalNone */)){
const utility::Span expr_span = (checked_default_value_expr->get<types::CheckedExpression::OptionalNone>()).span;
(checked_default_value_expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::OptionalNone>(expr_span,param_type))));
}
const types::TypeId default_value_type_id = ((checked_default_value_expr)->type());
(checked_default_value = checked_default_value_expr);
TRY((((*this).check_types_for_compat(param_type,default_value_type_id,((((*this).generic_inferences))),((param).span)))));
}
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,checked_default_value)))));
if (((check_scope).has_value())){
const types::VarId var_id = TRY((((module)->add_variable(checked_variable))));
TRY((((*this).add_var_to_scope((check_scope.value()),((((param).variable)).name),var_id,((((param).variable)).span)))));
}
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
const types::TypeId function_return_type_id = TRY((((*this).typecheck_typename(((func).return_type),method_scope_id,JaktInternal::OptionalNone()))));
(((checked_function)->return_type_id) = function_return_type_id);
if (is_generic){
if ((!(((check_scope).has_value())))){
TRY((((((*this).compiler))->panic(String("Generic method with generic parameters must have a check scope")))));
}
const bool old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
const types::CheckedBlock block = TRY((((*this).typecheck_block(((func).block),(check_scope.value()), types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
types::TypeId return_type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
if (((function_return_type_id).equals(types::unknown_type_id()))){
if ((!(((((block).statements)).is_empty())))){
if ((((((((block).statements)).last()).value()))->index() == 8 /* Return */)){
const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> val = ((((((block).statements)).last()).value())->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
(return_type_id = TRY((((*this).resolve_type_var((((val.value()))->type()),method_scope_id)))));
}
}
}
}
else {
(return_type_id = TRY((((*this).resolve_type_var(function_return_type_id,scope_id)))));
}

(((checked_function)->block) = block);
(((checked_function)->return_type_id) = return_type_id);
}
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

ErrorOr<void> typechecker::Typechecker::typecheck_enum_predecl_initial(const parser::ParsedRecord parsed_record,const size_t enum_index,const size_t module_enum_len,const types::ScopeId scope_id) {
{
const types::ModuleId module_id = ((*this).current_module_id);
const types::EnumId enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::Enum>(enum_id)))))));
const types::TypeId enum_type_id = types::TypeId(module_id,(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((*this).add_type_to_scope(scope_id,((parsed_record).name),enum_type_id,((parsed_record).name_span)))));
const bool is_boxed = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
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
TRY((((((module)->enums)).push(types::CheckedEnum(((parsed_record).name),((parsed_record).name_span),(TRY((Array<types::TypeId>::create_with({})))),(TRY((Array<types::CheckedEnumVariant>::create_with({})))),((*this).prelude_scope_id()),((parsed_record).definition_linkage),((parsed_record).record_type),enum_type_id,enum_type_id,is_boxed)))));
}
return {};
}

NonnullRefPtr<types::Type> typechecker::Typechecker::get_type(const types::TypeId id) const {
{
return (((((*this).program))->get_type(id)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_extern_import(const parser::ParsedExternImport import_,const types::ScopeId scope_id) {
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

ErrorOr<void> typechecker::Typechecker::check_member_access(const types::ScopeId accessor,const types::ScopeId accessee,const types::CheckedVariable member,const utility::Span span) {
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

ErrorOr<void> typechecker::Typechecker::typecheck_method(const parser::ParsedFunction func,const types::StructOrEnumId parent_id) {
{
JaktInternal::Array<types::TypeId> parent_generic_parameters = (TRY((Array<types::TypeId>::create_with({}))));
types::ScopeId scope_id = ((*this).prelude_scope_id());
parser::DefinitionLinkage definition_linkage =  parser::DefinitionLinkage { typename parser::DefinitionLinkage::Internal() } ;
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
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
const types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
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
return {};
}
const types::ScopeId structure_scope_id = scope_id;
const parser::DefinitionLinkage structure_linkage = definition_linkage;
const JaktInternal::Optional<types::FunctionId> method_id = TRY((((*this).find_function_in_scope(structure_scope_id,((func).name)))));
if ((!(((method_id).has_value())))){
TRY((((((*this).compiler))->panic(String("we just pushed the checked function, but it's not present")))));
}
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function((method_id.value())));
const types::ScopeId function_scope_id = ((checked_function)->function_scope_id);
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
const types::CheckedVariable variable = ((param).variable);
const types::VarId var_id = TRY((((module)->add_variable(variable))));
TRY((((*this).add_var_to_scope(function_scope_id,((variable).name),var_id,((variable).definition_span)))));
}

}
}

(((*this).current_function_id) = method_id);
const types::TypeId VOID_TYPE_ID = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
const types::CheckedBlock block = TRY((((*this).typecheck_block(((func).block),function_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
const types::TypeId function_return_type_id = TRY((((*this).typecheck_typename(((func).return_type),function_scope_id,JaktInternal::OptionalNone()))));
types::TypeId return_type_id = function_return_type_id;
if ((((function_return_type_id).equals(types::unknown_type_id())) && (!(((((block).statements)).is_empty()))))){
if (((((((block).statements))[static_cast<i64>(0LL)]))->index() == 8 /* Return */)){
const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> val = (((((block).statements))[static_cast<i64>(0LL)])->get<types::CheckedStatement::Return>()).val;
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
}
return {};
}

ErrorOr<bool> typechecker::Typechecker::add_struct_to_scope(const types::ScopeId scope_id,const String name,const types::StructId struct_id,const utility::Span span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
const JaktInternal::Optional<types::StructId> maybe_scope_id = ((((scope)->structs)).get(name));
if (((maybe_scope_id).has_value())){
const types::StructId existing_struct_id = (maybe_scope_id.value());
const utility::Span definition_span = ((((*this).get_struct(existing_struct_id))).name_span);
TRY((((*this).error_with_hint(TRY((String::formatted(String("redefinition of struct/class {}"),name))),span,TRY((String::formatted(String("struct/class {} was first defined here"),name))),definition_span))));
return (false);
}
TRY((((((scope)->structs)).set(name,struct_id))));
return (true);
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::infer_unsigned_int(const u64 val,const utility::Span span,const JaktInternal::Optional<types::TypeId> type_hint) {
{
NonnullRefPtr<types::CheckedExpression> expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } ))));
if (((type_hint).has_value())){
const types::TypeId hint = (type_hint.value());
if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8((infallible_integer_cast<i8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16((infallible_integer_cast<i16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16((infallible_integer_cast<u16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
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
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
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

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_unary_negate(const NonnullRefPtr<types::CheckedExpression> expr,const utility::Span span,const types::TypeId type_id) {
{
if (((!(((((*this).program))->is_integer(type_id)))) || ((((*this).program))->is_signed(type_id)))){
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,type_id))));
}
const types::TypeId flipped_sign_type = TRY((((((*this).get_type(type_id)))->flip_signedness())));
const types::CheckedNumericConstant constant = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedNumericConstant, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
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
const types::NumberConstant number = (((constant).number_constant()).value());
const size_t raw_number = ((number).to_usize());
const size_t max_signed = (infallible_integer_cast<size_t>((((TRY((types::Type::template create<typename types::Type::I64>())))->max()))));
i64 negated_number = static_cast<i64>(0LL);
if ((raw_number == (JaktInternal::checked_add<size_t>(max_signed,static_cast<size_t>(1ULL))))){
(negated_number = ((TRY((types::Type::template create<typename types::Type::I64>())))->min()));
}
if ((raw_number <= max_signed)){
(negated_number = (JaktInternal::checked_sub<i64>(static_cast<i64>(0LL),(infallible_integer_cast<i64>((raw_number))))));
}
const types::NumberConstant negated_number_constant =  types::NumberConstant { typename types::NumberConstant::Signed((infallible_integer_cast<i64>((negated_number)))) } ;
if (((raw_number > (JaktInternal::checked_add<size_t>(max_signed,static_cast<size_t>(1ULL)))) || (!(((negated_number_constant).can_fit_number(flipped_sign_type,((*this).program))))))){
TRY((((*this).error(TRY((String::formatted(String("Negative literal -{} too small for type ‘{}’"),raw_number,TRY((((*this).type_name(flipped_sign_type))))))),span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::UnaryOp>(expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,type_id))));
}
const types::CheckedNumericConstant new_constant = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedNumericConstant, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
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

ErrorOr<JaktInternal::Optional<types::FunctionId>> typechecker::Typechecker::resolve_call(const parser::ParsedCall call,JaktInternal::Array<types::ResolvedNamespace> namespaces,const utility::Span span,const types::ScopeId scope_id,const bool must_be_enum_constructor,const bool ignore_errors) {
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
const String scope_name = ((((call).namespace_))[namespace_index]);
const JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> maybe_ns_scope = TRY((((*this).find_namespace_in_scope(current_scope_id,scope_name))));
if (((maybe_ns_scope).has_value())){
const JaktInternal::Tuple<types::ScopeId,bool> scope_id_is_import_ = (maybe_ns_scope.value());
const types::ScopeId scope_id = ((scope_id_is_import_).get<0>());
const bool is_import = ((scope_id_is_import_).get<1>());

if (is_import){
(((((namespaces)[namespace_index])).name) = ((((((((*this).program))->modules))[((((scope_id).module_id)).id)]))->name));
}
(current_scope_id = scope_id);
continue;
}
const JaktInternal::Optional<types::StructId> maybe_struct_scope = TRY((((*this).find_struct_in_scope(current_scope_id,scope_name))));
if (((maybe_struct_scope).has_value())){
const types::CheckedStruct structure = ((*this).get_struct((maybe_struct_scope.value())));
(current_scope_id = ((structure).scope_id));
continue;
}
const JaktInternal::Optional<types::EnumId> maybe_enum_scope = TRY((((((*this).program))->find_enum_in_scope(current_scope_id,scope_name))));
if (((maybe_enum_scope).has_value())){
const types::CheckedEnum enum_ = ((*this).get_enum((maybe_enum_scope.value())));
(current_scope_id = ((enum_).scope_id));
continue;
}
TRY((((*this).error(TRY((String::formatted(String("Not a namespace, enum, class, or struct: ‘{}’"),utility::join(((call).namespace_),String("::"))))),span))));
}

}
}

const JaktInternal::Optional<types::CheckedVariable> maybe_var = TRY((((*this).find_var_in_scope(current_scope_id,((call).name)))));
if (((maybe_var).has_value())){
const types::TypeId inner_type = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<JaktInternal::Optional<types::FunctionId>>>{
auto&& __jakt_match_variant = *((*this).get_type((((maybe_var.value())).type_id)));
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 26: {
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
if (((((*this).get_type(inner_type)))->index() == 27 /* Function */)){
const types::FunctionId pseudo_function_id = (((*this).get_type(inner_type))->get<types::Type::Function>()).pseudo_function_id;
return (pseudo_function_id);
}
}
const JaktInternal::Optional<types::FunctionId> maybe_function_id = TRY((((*this).find_function_in_scope(current_scope_id,((call).name)))));
if (((maybe_function_id).has_value())){
const types::FunctionId function_id = (maybe_function_id.value());
if (((!(must_be_enum_constructor)) || ((((((*this).get_function(function_id)))->type)).index() == 2 /* ImplicitEnumConstructor */))){
return (function_id);
}
}
if (must_be_enum_constructor){
TRY((((*this).error(TRY((String::formatted(String("No such enum constructor ‘{}’"),((call).name)))),span))));
return (callee);
}
const JaktInternal::Optional<types::StructId> maybe_struct_id = TRY((((*this).find_struct_in_scope(current_scope_id,((call).name)))));
if (((maybe_struct_id).has_value())){
const types::StructId struct_id = (maybe_struct_id.value());
const types::CheckedStruct structure = ((*this).get_struct(struct_id));
const JaktInternal::Optional<types::FunctionId> maybe_function_id = TRY((((*this).find_function_in_scope(((structure).scope_id),((call).name)))));
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

ErrorOr<NonnullRefPtr<types::CheckedProgram>> typechecker::Typechecker::typecheck(NonnullRefPtr<compiler::Compiler> compiler,const parser::ParsedNamespace parsed_namespace) {
{
const JaktInternal::Optional<utility::FileId> input_file = ((compiler)->current_file);
if ((!(((input_file).has_value())))){
TRY((((compiler)->panic(String("trying to typecheck a non-existant file")))));
}
const types::ModuleId placeholder_module_id = types::ModuleId(static_cast<size_t>(0ULL));
typechecker::Typechecker typechecker = typechecker::Typechecker(compiler,TRY((types::CheckedProgram::create(compiler,(TRY((Array<NonnullRefPtr<types::Module>>::create_with({})))),(TRY((Dictionary<String, types::LoadedModule>::create_with_entries({}))))))),placeholder_module_id,types::TypeId::none(),JaktInternal::OptionalNone(),false,static_cast<size_t>(0ULL),false,((compiler)->dump_type_hints),((compiler)->dump_try_hints),static_cast<u64>(0ULL),types::GenericInferences((TRY((Dictionary<String, String>::create_with_entries({}))))));
TRY((((typechecker).include_prelude())));
const String root_module_name = String("Root Module");
const types::ModuleId root_module_id = TRY((((typechecker).create_module(root_module_name,true,JaktInternal::OptionalNone()))));
(((typechecker).current_module_id) = root_module_id);
((compiler)->set_current_file((input_file.value())));
TRY((((((typechecker).program))->set_loaded_module(root_module_name,types::LoadedModule(root_module_id,(input_file.value()))))));
const types::ScopeId PRELUDE_SCOPE_ID = ((typechecker).prelude_scope_id());
const types::ScopeId root_scope_id = TRY((((typechecker).create_scope(PRELUDE_SCOPE_ID,false,String("root")))));
TRY((((typechecker).typecheck_module(parsed_namespace,root_scope_id))));
return (((typechecker).program));
}
}

ErrorOr<bool> typechecker::Typechecker::add_enum_to_scope(const types::ScopeId scope_id,const String name,const types::EnumId enum_id,const utility::Span span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
const JaktInternal::Optional<types::EnumId> maybe_enum_id = ((((scope)->enums)).get(name));
if (((maybe_enum_id).has_value())){
const types::EnumId existing_enum_id = (maybe_enum_id.value());
const utility::Span definition_span = ((((*this).get_enum(existing_enum_id))).name_span);
TRY((((*this).error_with_hint(TRY((String::formatted(String("redefinition of enum {}"),name))),span,TRY((String::formatted(String("enum {} was first defined here"),name))),definition_span))));
return (false);
}
TRY((((((scope)->enums)).set(name,enum_id))));
return (true);
}
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_dictionary(const JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>>> values,const utility::Span span,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
const types::StructId dictionary_struct_id = TRY((((*this).find_struct_in_prelude(String("Dictionary")))));
JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> checked_kv_pairs = (TRY((Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>>::create_with({}))));
types::TypeId key_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> key_type_span = JaktInternal::OptionalNone();
types::TypeId value_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> value_type_span = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> key_hint = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> value_hint = JaktInternal::OptionalNone();
if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
const types::StructId id = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (((*this).get_type((type_hint.value())))->get<types::Type::GenericInstance>()).args;
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
const JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,NonnullRefPtr<parser::ParsedExpression>> jakt__key__value__ = key__value__;
const NonnullRefPtr<parser::ParsedExpression> key = ((jakt__key__value__).get<0>());
const NonnullRefPtr<parser::ParsedExpression> value = ((jakt__key__value__).get<1>());

const NonnullRefPtr<types::CheckedExpression> checked_key = TRY((((*this).typecheck_expression(key,scope_id,safety_mode,key_hint))));
const types::TypeId current_key_type_id = ((checked_key)->type());
const NonnullRefPtr<types::CheckedExpression> checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,value_hint))));
const types::TypeId current_value_type_id = ((checked_value)->type());
const types::TypeId VOID_TYPE_ID = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
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
const String key_type_name = TRY((((*this).type_name(key_type_id))));
const String current_key_type_name = TRY((((*this).type_name(current_key_type_id))));
TRY((((*this).error_with_hint(TRY((String::formatted(String("Type '{}' does not match type '{}' of previous keys in dictionary"),current_key_type_name,key_type_name))),((key)->span()),TRY((String::formatted(String("Dictionary was inferred to store keys of type '{}' here"),key_type_name))),(key_type_span.value())))));
}
if ((!(((value_type_id).equals(current_value_type_id))))){
const String value_type_name = TRY((((*this).type_name(value_type_id))));
const String current_value_type_name = TRY((((*this).type_name(current_value_type_id))));
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
const types::TypeId type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(dictionary_struct_id,(TRY((Array<types::TypeId>::create_with({key_type_id, value_type_id})))))))))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::JaktDictionary>(checked_kv_pairs,span,type_id,key_type_id,value_type_id))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_if(const NonnullRefPtr<parser::ParsedExpression> condition,const parser::ParsedBlock then_block,const JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> else_statement,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
const JaktInternal::Tuple<NonnullRefPtr<parser::ParsedExpression>,parser::ParsedBlock,JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>>> new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings(condition,JaktInternal::OptionalNone(),then_block,else_statement,span))));
const NonnullRefPtr<parser::ParsedExpression> new_condition = ((new_condition_new_then_block_new_else_statement_).get<0>());
const parser::ParsedBlock new_then_block = ((new_condition_new_then_block_new_else_statement_).get<1>());
const JaktInternal::Optional<NonnullRefPtr<parser::ParsedStatement>> new_else_statement = ((new_condition_new_then_block_new_else_statement_).get<2>());

const NonnullRefPtr<types::CheckedExpression> checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(String("Condition must be a boolean expression"),((new_condition)->span())))));
}
const types::CheckedBlock checked_block = TRY((((*this).typecheck_block(new_then_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(String("An 'if' block is not allowed to yield values"),(((new_then_block).find_yield_span()).value())))));
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> checked_else = JaktInternal::OptionalNone();
if (((new_else_statement).has_value())){
(checked_else = TRY((((*this).typecheck_statement((new_else_statement.value()),scope_id,safety_mode,JaktInternal::OptionalNone())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::If>(checked_condition,checked_block,checked_else,span))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::unify_with_type(const types::TypeId found_type,const JaktInternal::Optional<types::TypeId> expected_type,const utility::Span span) {
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

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_throw(const NonnullRefPtr<parser::ParsedExpression> expr,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const types::TypeId error_type_id = TRY((((*this).find_type_in_prelude(String("Error")))));
if ((!(((((checked_expr)->type())).equals(error_type_id))))){
TRY((((*this).error(String("throw expression does not produce an error"),((expr)->span())))));
}
const NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
if ((!(((scope)->can_throw)))){
TRY((((*this).error(String("Throw statement needs to be in a try statement or a function marked as throws"),((expr)->span())))));
}
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Throw>(checked_expr,span))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_destructuring_assignment(const JaktInternal::Array<parser::ParsedVarDecl> vars,const NonnullRefPtr<parser::ParsedStatement> var_decl,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
JaktInternal::Array<NonnullRefPtr<types::CheckedStatement>> var_decls = (TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({}))));
const NonnullRefPtr<types::CheckedStatement> checked_tuple_var_decl = TRY((((*this).typecheck_statement(var_decl,scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::TypeId expr_type_id = types::unknown_type_id();
types::VarId tuple_var_id = types::VarId(types::ModuleId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL));
if (((checked_tuple_var_decl)->index() == 3 /* VarDecl */)){
const types::VarId var_id = (checked_tuple_var_decl->get<types::CheckedStatement::VarDecl>()).var_id;
const NonnullRefPtr<types::CheckedExpression> init = (checked_tuple_var_decl->get<types::CheckedStatement::VarDecl>()).init;
(expr_type_id = ((init)->type()));
(tuple_var_id = var_id);
}
else {
TRY((((*this).error(String("Destructuting assignment should be a variable declaration"),span))));
}

JaktInternal::Array<types::TypeId> inner_types = (TRY((Array<types::TypeId>::create_with({}))));
const NonnullRefPtr<types::Type> tuple_type = ((*this).get_type(expr_type_id));
if (((tuple_type)->index() == 19 /* GenericInstance */)){
const JaktInternal::Array<types::TypeId> args = (tuple_type->get<types::Type::GenericInstance>()).args;
(inner_types = args);
}
else {
TRY((((*this).error(String("Tuple Type should be Generic Instance"),span))));
}

const types::CheckedVariable tuple_variable = ((((*this).program))->get_variable(tuple_var_id));
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
const NonnullRefPtr<parser::ParsedExpression> init = TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::IndexedTuple>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::Var>(((tuple_variable).name),span))),i,false,span)));
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

ErrorOr<bool> typechecker::Typechecker::add_type_to_scope(const types::ScopeId scope_id,const String type_name,const types::TypeId type_id,const utility::Span span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
const JaktInternal::Optional<types::TypeId> found_type_id = ((((scope)->types)).get(type_name));
if ((((found_type_id).has_value()) && (!((((found_type_id.value())).equals(type_id)))))){
TRY((((*this).error(TRY((String::formatted(String("Redefinition of type ‘{}’"),type_name))),span))));
return (false);
}
TRY((((((scope)->types)).set(type_name,type_id))));
return (true);
}
}

ErrorOr<types::ScopeId> typechecker::Typechecker::create_scope(const JaktInternal::Optional<types::ScopeId> parent_scope_id,const bool can_throw,const String debug_name) {
{
return (TRY((((((*this).program))->create_scope(parent_scope_id,can_throw,debug_name,((*this).current_module_id))))));
}
}

ErrorOr<bool> typechecker::Typechecker::validate_argument_label(const types::CheckedParameter param,const String label,const utility::Span span,const NonnullRefPtr<parser::ParsedExpression> expr,const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> default_value) {
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
const String name = (expr->get<parser::ParsedExpression::Var>()).name;
const utility::Span span = (expr->get<parser::ParsedExpression::Var>()).span;
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

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::infer_signed_int(const i64 val,const utility::Span span,const JaktInternal::Optional<types::TypeId> type_hint) {
{
NonnullRefPtr<types::CheckedExpression> expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } ))));
if (((type_hint).has_value())){
const types::TypeId hint = (type_hint.value());
if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8((infallible_integer_cast<i8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16((infallible_integer_cast<i16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16((infallible_integer_cast<u16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U32((infallible_integer_cast<u32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(String("Integer promotion failed"),span,TRY((String::formatted(String("Cannot fit value into range [{}, {}] of type {}."),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))){
const types::TypeId builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } );
const NonnullRefPtr<types::Type> type_ = ((*this).get_type(builtin_typeid));
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

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_indexed_struct(const NonnullRefPtr<parser::ParsedExpression> expr,const String field,const types::ScopeId scope_id,const bool is_optional,const types::SafetyMode safety_mode,const utility::Span span) {
{
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const types::TypeId checked_expr_type_id = ((checked_expr)->type());
const NonnullRefPtr<types::Type> checked_expr_type = ((*this).get_type(checked_expr_type_id));
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
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
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field,span,is_optional,types::unknown_type_id()))));
}
(type_id = ((args)[static_cast<i64>(0LL)]));
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
{
const types::CheckedStruct structure = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId member_id = (_magic_value.value());
{
const types::CheckedVariable member = ((*this).get_variable(member_id));
if ((((member).name) == field)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((structure).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field,span,is_optional,resolved_type_id))));
}
}

}
}

TRY((((*this).error(TRY((String::formatted(String("unknown member of struct: {}.{}"),((structure).name),field))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
const types::CheckedStruct structure = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId member_id = (_magic_value.value());
{
const types::CheckedVariable member = ((*this).get_variable(member_id));
if ((((member).name) == field)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((Array<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((structure).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field,span,is_optional,resolved_type_id))));
}
}

}
}

TRY((((*this).error(TRY((String::formatted(String("unknown member of struct: {}.{}"),((structure).name),field))),span))));
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
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
if (is_optional){
TRY((((*this).error(String("Optional chaining is not allowed on non-optional types"),span))));
}
const types::CheckedStruct structure = ((*this).get_struct(struct_id));
const JaktInternal::Optional<types::FieldRecord> field_record = TRY((((*this).lookup_struct_field(struct_id,field))));
if (((field_record).has_value())){
const types::CheckedVariable member = ((*this).get_variable((((field_record.value())).field_id)));
const types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member).type_id),scope_id))));
TRY((((*this).check_member_access(scope_id,((((*this).get_struct((((field_record.value())).struct_id)))).scope_id),member,span))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field,span,is_optional,resolved_type_id))));
}
TRY((((*this).error(TRY((String::formatted(String("unknown member of struct: {}.{}"),((structure).name),field))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
return (TRY((((*this).error(TRY((String::formatted(String("Member field access on value of non-struct type ‘{}’"),TRY((((*this).type_name(checked_expr_type_id))))))),span))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field,span,is_optional,types::unknown_type_id()))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_function_predecl(const parser::ParsedFunction parsed_function,const types::ScopeId parent_scope_id,const JaktInternal::Optional<types::TypeId> this_arg_type_id,JaktInternal::Optional<NonnullRefPtr<types::FunctionGenerics>> generics) {
{
const types::ScopeId function_scope_id = TRY((((*this).create_scope(parent_scope_id,((parsed_function).can_throw),TRY((String::formatted(String("function({})"),((parsed_function).name))))))));
const String scope_debug_name = TRY((String::formatted(String("function-block({})"),((parsed_function).name))));
const types::ScopeId block_scope_id = TRY((((*this).create_scope(function_scope_id,((parsed_function).can_throw),scope_debug_name))));
const size_t module_id = ((((*this).current_module_id)).id);
bool base_definition = false;
if ((!(((generics).has_value())))){
(generics = TRY((types::FunctionGenerics::create((TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))));
(base_definition = true);
}
const bool is_generic_function = (!(((((parsed_function).generic_parameters)).is_empty())));
const bool is_generic = (is_generic_function || (((this_arg_type_id).has_value()) && ((((*this).get_type((this_arg_type_id.value()))))->index() == 19 /* GenericInstance */)));
NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((parsed_function).name),((parsed_function).name_span),TRY((((*this).typecheck_visibility(((parsed_function).visibility),parent_scope_id)))),types::unknown_type_id(),((parsed_function).return_type_span),(TRY((Array<types::CheckedParameter>::create_with({})))),(generics.value()),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),((parsed_function).can_throw), parser::FunctionType { typename parser::FunctionType::Normal() } ,((parsed_function).linkage),function_scope_id,((!(is_generic)) || (!(base_definition))),parsed_function,((parsed_function).is_comptime),false,false)));
NonnullRefPtr<types::Module> current_module = ((*this).current_module());
const types::FunctionId function_id = TRY((((current_module)->add_function(checked_function))));
const types::ScopeId checked_function_scope_id = ((checked_function)->function_scope_id);
const bool external_linkage = ((((parsed_function).linkage)).index() == 1 /* External */);
const JaktInternal::Optional<types::ScopeId> check_scope = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::ScopeId>,ErrorOr<void>>{
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
TRY((((((current_module)->types)).push(TRY((types::Type::template create<typename types::Type::TypeVariable>(((generic_parameter).name))))))));
TRY((((((((checked_function)->generics))->params)).push( types::FunctionGenericParameter { typename types::FunctionGenericParameter::Parameter(type_var_type_id) } ))));
}
else if (((((((((checked_function)->generics))->params))[i])).index() == 1 /* Parameter */)){
const types::TypeId var_type_id = (((((((checked_function)->generics))->params))[i]).get<types::FunctionGenericParameter::Parameter>()).value;
(type_var_type_id = var_type_id);
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
const types::CheckedParameter checked_param = TRY((((*this).typecheck_parameter(parameter,checked_function_scope_id,first,this_arg_type_id,check_scope))));
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
const bool old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
const types::CheckedBlock block = TRY((((*this).typecheck_block(((parsed_function).block),(check_scope.value()), types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
const types::TypeId return_type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId,ErrorOr<void>>{
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

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_try_block(const NonnullRefPtr<parser::ParsedStatement> stmt,const String error_name,const utility::Span error_span,const parser::ParsedBlock catch_block,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
const types::ScopeId try_scope_id = TRY((((*this).create_scope(scope_id,true,String("try")))));
const NonnullRefPtr<types::CheckedStatement> checked_stmt = TRY((((*this).typecheck_statement(stmt,try_scope_id,safety_mode,JaktInternal::OptionalNone()))));
const types::StructId error_struct_id = TRY((((*this).find_struct_in_prelude(String("Error")))));
const types::CheckedVariable error_decl = types::CheckedVariable(error_name,((((*this).get_struct(error_struct_id))).type_id),false,error_span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::VarId error_id = TRY((((module)->add_variable(error_decl))));
const types::ScopeId catch_scope_id = TRY((((*this).create_scope(scope_id,true,String("catch")))));
TRY((((*this).add_var_to_scope(catch_scope_id,error_name,error_id,error_span))));
const types::CheckedBlock checked_catch_block = TRY((((*this).typecheck_block(catch_block,catch_scope_id,safety_mode,JaktInternal::OptionalNone()))));
return (TRY((types::CheckedExpression::template create<typename types::CheckedExpression::TryBlock>(checked_stmt,checked_catch_block,error_name,error_span,span,types::void_type_id()))));
}
}

ErrorOr<types::CheckedUnaryOperator> typechecker::Typechecker::typecheck_is_enum_variant(const NonnullRefPtr<types::CheckedExpression> checked_expr,const NonnullRefPtr<parser::ParsedType> inner,const JaktInternal::Array<parser::EnumVariantPatternArgument> bindings,const types::ScopeId scope_id) {
{
const bool old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
const types::TypeId type_id = TRY((((*this).typecheck_typename(inner,scope_id,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
types::CheckedUnaryOperator checked_op =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Is(type_id) } ;
const types::TypeId expr_type_id = ((checked_expr)->type());
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::CheckedUnaryOperator>>{
auto&& __jakt_match_variant = *inner;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::NamespacedName>();String const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (((((*this).get_type(expr_type_id)))->index() == 23 /* Enum */)){
const types::EnumId enum_id = (((*this).get_type(expr_type_id))->get<types::Type::Enum>()).value;
const types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
const JaktInternal::Optional<types::CheckedEnumVariant> variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
const JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>> checked_enum_variant_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),bindings,span))));
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
if (((((*this).get_type(expr_type_id)))->index() == 23 /* Enum */)){
const types::EnumId enum_id = (((*this).get_type(expr_type_id))->get<types::Type::Enum>()).value;
const types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
const JaktInternal::Optional<types::CheckedEnumVariant> variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
const JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>> checked_enum_variant_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),bindings,span))));
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

types::CheckedVariable typechecker::Typechecker::get_variable(const types::VarId id) const {
{
return (((((*this).program))->get_variable(id)));
}
}

bool typechecker::Typechecker::is_class(const types::TypeId type_id) const {
{
if (((((*this).get_type(type_id)))->index() == 22 /* Struct */)){
const types::StructId struct_id = (((*this).get_type(type_id))->get<types::Type::Struct>()).value;
return (((((((*this).get_struct(struct_id))).record_type)).index() == 1 /* Class */));
}
else {
return (false);
}

}
}

types::TypeId typechecker::Typechecker::infer_function_return_type(const types::CheckedBlock block) const {
{
if (((((block).statements)).is_empty())){
return (types::void_type_id());
}
if ((((((((block).statements)).last()).value()))->index() == 8 /* Return */)){
const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> val = ((((((block).statements)).last()).value())->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
return ((((val.value()))->type()));
}
}
return (types::void_type_id());
}
}

ErrorOr<JaktInternal::Optional<types::Value>> typechecker::Typechecker::find_comptime_binding_in_scope(const types::ScopeId scope_id,const String name) const {
{
return (TRY((((((*this).program))->find_comptime_binding_in_scope(scope_id,name)))));
}
}

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_statement(const NonnullRefPtr<parser::ParsedStatement> statement,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> type_hint) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedStatement>, ErrorOr<NonnullRefPtr<types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Expression>();NonnullRefPtr<parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template create<typename types::CheckedStatement::Expression>(TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,types::TypeId::none())))),span))));
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

ErrorOr<JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<types::CheckedExpression>>>> typechecker::Typechecker::resolve_default_params(const JaktInternal::Array<types::CheckedParameter> params,const JaktInternal::Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>> args,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const size_t arg_offset,const utility::Span span) {
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
const types::CheckedParameter param = ((params)[i]);
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> maybe_checked_expr = JaktInternal::OptionalNone();
if ((!(((param).requires_label)))){
if ((((args).size()) > consumed_arg)){
const JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> name_span_expr_ = ((args)[consumed_arg]);
const String name = ((name_span_expr_).get<0>());
const utility::Span span = ((name_span_expr_).get<1>());
const NonnullRefPtr<parser::ParsedExpression> expr = ((name_span_expr_).get<2>());

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
const JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> name_span_expr_ = ((args)[consumed_arg]);
const String name = ((name_span_expr_).get<0>());
const utility::Span span = ((name_span_expr_).get<1>());
const NonnullRefPtr<parser::ParsedExpression> expr = ((name_span_expr_).get<2>());

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

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_generic_arguments_method_call(const NonnullRefPtr<types::CheckedExpression> checked_expr,const parser::ParsedCall call,const types::ScopeId scope_id,const utility::Span span,const bool is_optional,const types::SafetyMode safety_mode) {
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
const JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>> jakt__name_____expr__ = name_____expr__;
const String name = ((jakt__name_____expr__).get<0>());
const utility::Span _ = ((jakt__name_____expr__).get<1>());
const NonnullRefPtr<parser::ParsedExpression> expr = ((jakt__name_____expr__).get<2>());

const NonnullRefPtr<types::CheckedExpression> checked_arg_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone()))));
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

ErrorOr<void> typechecker::Typechecker::check_that_type_doesnt_contain_reference(const types::TypeId type_id,const utility::Span span) {
{
const NonnullRefPtr<types::Type> type = ((*this).get_type(type_id));
const bool contains_reference = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 26: {
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

types::CheckedEnum typechecker::Typechecker::get_enum(const types::EnumId id) const {
{
return (((((*this).program))->get_enum(id)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_function_predecl(const parser::ParsedNamespace parsed_namespace,const types::ScopeId scope_id) {
{
const JaktInternal::Array<types::ScopeId> children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
const parser::ParsedNamespace child_namespace = ((((parsed_namespace).namespaces))[i]);
const types::ScopeId child_namespace_scope_id = ((children)[i]);
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

}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_constructor(const parser::ParsedRecord record,const types::EnumId enum_id,const types::ScopeId parent_scope_id) {
{
u64 next_constant_value = static_cast<u64>(0ULL);
JaktInternal::Set<String> seen_names = (TRY((Set<String>::create_with_values({}))));
types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();NonnullRefPtr<parser::ParsedType> const& underlying_type = __jakt_match_value.underlying_type;
JaktInternal::Array<parser::ValueEnumVariant> const& variants = __jakt_match_value.variants;
{
const types::TypeId underlying_type_id = TRY((((*this).typecheck_typename(underlying_type,parent_scope_id,JaktInternal::OptionalNone()))));
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
const NonnullRefPtr<types::CheckedExpression> expr = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<types::CheckedExpression>,ErrorOr<void>>{
auto __jakt_enum_value = (((((variant).value)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<types::CheckedExpression>> __jakt_var_285; {
const NonnullRefPtr<types::CheckedExpression> value_expression = TRY((((*this).cast_to_underlying((((variant).value).value()),parent_scope_id,underlying_type))));
const JaktInternal::Optional<types::NumberConstant> number_constant = ((value_expression)->to_number_constant(((*this).program)));
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
return JaktInternal::ExplicitValue(({ Optional<u64> __jakt_var_286; {
utility::todo(String("Implement floats"));
__jakt_var_286 = static_cast<u64>(0ULL); goto __jakt_label_265;

}
__jakt_label_265:; __jakt_var_286.release_value(); }));
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
__jakt_var_285 = value_expression; goto __jakt_label_264;

}
__jakt_label_264:; __jakt_var_285.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).cast_to_underlying(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::NumericConstant>( lexer::NumericConstant { typename lexer::NumericConstant::U64(((next_constant_value++))) } ,((variant).span)))),parent_scope_id,underlying_type)))));
}
}()))
;
TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::WithValue(enum_id,((variant).name),expr,((variant).span)) } ))));
const types::VarId var_id = TRY((((module)->add_variable(types::CheckedVariable(((variant).name),((enum_).type_id),false,((variant).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } )))));
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
const bool is_structlike = ((((((variant).params)).has_value()) && ((((((variant).params).value())).size()) > static_cast<size_t>(0ULL))) && ((((((((variant).params).value()))[static_cast<i64>(0LL)])).name) != String("")));
const bool is_typed = ((((((variant).params)).has_value()) && ((((((variant).params).value())).size()) == static_cast<size_t>(1ULL))) && ((((((((variant).params).value()))[static_cast<i64>(0LL)])).name) == String("")));
if (is_structlike){
JaktInternal::Set<String> seen_fields = (TRY((Set<String>::create_with_values({}))));
JaktInternal::Array<types::VarId> fields = (TRY((Array<types::VarId>::create_with({}))));
JaktInternal::Array<types::CheckedParameter> params = (TRY((Array<types::CheckedParameter>::create_with({}))));
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
const types::TypeId type_id = TRY((((*this).typecheck_typename(((param).parsed_type),((enum_).scope_id),((param).name)))));
const types::CheckedVariable checked_var = types::CheckedVariable(((param).name),type_id,((param).is_mutable),((param).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
TRY((((params).push(types::CheckedParameter(true,checked_var,JaktInternal::OptionalNone())))));
if (((*this).dump_type_hints)){
TRY((((*this).dump_type_hint(type_id,((param).span)))));
}
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::VarId var_id = TRY((((module)->add_variable(checked_var))));
TRY((((fields).push(var_id))));
}

}
}

TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::StructLike(enum_id,((variant).name),fields,((variant).span)) } ))));
const JaktInternal::Optional<types::FunctionId> maybe_enum_variant_constructor = TRY((((*this).find_function_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
const bool can_function_throw = is_boxed;
const types::ScopeId function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor({}::{})"),((enum_).name),((variant).name))))))));
const types::ScopeId block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor-block({}::{})"),((enum_).name),((variant).name))))))));
const NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),params,TRY((types::FunctionGenerics::create(params,(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,true,JaktInternal::OptionalNone(),false,false,false)));
const types::FunctionId function_id = TRY((((module)->add_function(checked_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),((variant).name),function_id,((variant).span)))));
}
}
else if (is_typed){
const parser::ParsedVarDecl param = (((((variant).params).value()))[static_cast<i64>(0LL)]);
const types::TypeId type_id = TRY((((*this).typecheck_typename(((param).parsed_type),((enum_).scope_id),((param).name)))));
TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::Typed(enum_id,((variant).name),type_id,((variant).span)) } ))));
const JaktInternal::Optional<types::FunctionId> maybe_enum_variant_constructor = TRY((((*this).find_function_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
const bool can_function_throw = is_boxed;
const types::ScopeId function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor({}::{})"),((enum_).name),((variant).name))))))));
const types::ScopeId block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor-block({}::{})"),((enum_).name),((variant).name))))))));
const types::CheckedVariable variable = types::CheckedVariable(String("value"),type_id,false,((param).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
const types::CheckedParameter param = types::CheckedParameter(false,variable,JaktInternal::OptionalNone());
const NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),(TRY((Array<types::CheckedParameter>::create_with({param})))),TRY((types::FunctionGenerics::create((TRY((Array<types::CheckedParameter>::create_with({param})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } ,types::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,true,JaktInternal::OptionalNone(),false,false,false)));
const types::FunctionId function_id = TRY((((module)->add_function(checked_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),((variant).name),function_id,((variant).span)))));
}
}
else {
TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::Untyped(enum_id,((variant).name),((variant).span)) } ))));
const JaktInternal::Optional<types::FunctionId> maybe_enum_variant_constructor = TRY((((*this).find_function_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
const bool can_function_throw = is_boxed;
const types::ScopeId function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor({}::{})"),((enum_).name),((variant).name))))))));
const types::ScopeId block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((String::formatted(String("enum-variant-constructor-block({}::{})"),((enum_).name),((variant).name))))))));
const NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),(TRY((Array<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::create((TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } ,types::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,true,JaktInternal::OptionalNone(),false,false,false)));
const types::FunctionId function_id = TRY((((module)->add_function(checked_function))));
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

ErrorOr<void> typechecker::Typechecker::typecheck_struct_constructor(const parser::ParsedRecord parsed_record,const types::StructId struct_id,const types::ScopeId scope_id) {
{
const types::TypeId struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
const types::CheckedStruct struct_ = ((*this).get_struct(struct_id));
const JaktInternal::Optional<types::FunctionId> constructor_id = TRY((((*this).find_function_in_scope(((struct_).scope_id),((parsed_record).name)))));
if (((constructor_id).has_value())){
if ((((((parsed_record).record_type)).index() == 1 /* Class */) && ((((parsed_record).definition_linkage)).index() == 1 /* External */))){
NonnullRefPtr<types::CheckedFunction> func = ((*this).get_function((constructor_id.value())));
(((func)->linkage) =  parser::FunctionLinkage { typename parser::FunctionLinkage::External() } );
}
}
else if ((!(((((parsed_record).definition_linkage)).index() == 1 /* External */)))){
const bool constructor_can_throw = ((((parsed_record).record_type)).index() == 1 /* Class */);
const types::ScopeId function_scope_id = TRY((((*this).create_scope(((struct_).scope_id),constructor_can_throw,TRY((String::formatted(String("generated-constructor({})"),((parsed_record).name))))))));
const types::ScopeId block_scope_id = TRY((((*this).create_scope(function_scope_id,constructor_can_throw,TRY((String::formatted(String("generated-constructor-block({})"),((parsed_record).name))))))));
NonnullRefPtr<types::CheckedFunction> checked_constructor = TRY((types::CheckedFunction::create(((parsed_record).name),((parsed_record).name_span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,struct_type_id,JaktInternal::OptionalNone(),(TRY((Array<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::create((TRY((Array<types::CheckedParameter>::create_with({})))),(TRY((Array<types::FunctionGenericParameter>::create_with({})))),(TRY((Array<JaktInternal::Array<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((Array<NonnullRefPtr<types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),constructor_can_throw, parser::FunctionType { typename parser::FunctionType::ImplicitConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,true,JaktInternal::OptionalNone(),false,false,false)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::FunctionId function_id = TRY((((module)->add_function(checked_constructor))));
const JaktInternal::Array<types::StructId> inheritance_chain = TRY((((*this).struct_inheritance_chain(struct_id))));
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
JaktInternal::ArrayIterator<types::VarId> _magic = ((((((*this).get_struct(field_struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field_id = (_magic_value.value());
{
const types::CheckedVariable field = ((*this).get_variable(field_id));
if (((((field).visibility)).index() == 1 /* Private */)){
(((checked_constructor)->visibility) =  types::CheckedVisibility { typename types::CheckedVisibility::Private() } );
}
TRY((((func)->add_param(types::CheckedParameter(true,field,JaktInternal::OptionalNone())))));
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

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_var_decl(const parser::ParsedVarDecl var,const NonnullRefPtr<parser::ParsedExpression> init,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
types::TypeId lhs_type_id = TRY((((*this).typecheck_typename(((var).parsed_type),scope_id,((var).name)))));
NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(init,scope_id,safety_mode,lhs_type_id))));
const types::TypeId rhs_type_id = ((checked_expr)->type());
if (((rhs_type_id).equals(types::void_type_id()))){
TRY((((*this).error(String("Cannot assign `void` to a variable"),((checked_expr)->span())))));
}
if ((((lhs_type_id).equals(types::unknown_type_id())) && (!(((rhs_type_id).equals(types::unknown_type_id())))))){
(lhs_type_id = rhs_type_id);
}
const types::StructId weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(String("WeakPtr")))));
const types::StructId optional_struct_id = TRY((((*this).find_struct_in_prelude(String("Optional")))));
const NonnullRefPtr<types::Type> lhs_type = ((*this).get_type(lhs_type_id));
TRY((((*this).check_that_type_doesnt_contain_reference(lhs_type_id,span))));
if (((checked_expr)->index() == 22 /* OptionalNone */)){
const utility::Span span = (checked_expr->get<types::CheckedExpression::OptionalNone>()).span;
const types::TypeId type_id = (checked_expr->get<types::CheckedExpression::OptionalNone>()).type_id;
if (((lhs_type)->index() == 19 /* GenericInstance */)){
const types::StructId id = (lhs_type->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (lhs_type->get<types::Type::GenericInstance>()).args;
if ((!((((id).equals(optional_struct_id)) || ((id).equals(weak_ptr_struct_id)))))){
TRY((((*this).error(String("Cannot assign None to a non-optional type"),span))));
}
}
else {
TRY((((*this).error(String("Cannot assign None to a non-optional type"),span))));
}

}
if (((lhs_type)->index() == 19 /* GenericInstance */)){
const types::StructId id = (lhs_type->get<types::Type::GenericInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (lhs_type->get<types::Type::GenericInstance>()).args;
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
const JaktInternal::Optional<types::NumberConstant> number_constant = ((checked_expr)->to_number_constant(((*this).program)));
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

const types::CheckedVariable checked_var = types::CheckedVariable(((var).name),lhs_type_id,((var).is_mutable),((var).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
if ((((*this).dump_type_hints) && ((((var).inlay_span)).has_value()))){
TRY((((*this).dump_type_hint(lhs_type_id,(((var).inlay_span).value())))));
}
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::VarId var_id = TRY((((module)->add_variable(checked_var))));
TRY((((*this).add_var_to_scope(scope_id,((var).name),var_id,((checked_var).definition_span)))));
return (TRY((types::CheckedStatement::template create<typename types::CheckedStatement::VarDecl>(var_id,checked_expr,span))));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Array<types::CheckedEnumVariantBinding>>> typechecker::Typechecker::typecheck_enum_variant_bindings(const types::CheckedEnumVariant variant,const JaktInternal::Array<parser::EnumVariantPatternArgument> bindings,const utility::Span span) {
{
if (((variant).index() == 1 /* Typed */)){
const types::TypeId type_id = (variant.get<types::CheckedEnumVariant::Typed>()).type_id;
if ((((bindings).size()) != static_cast<size_t>(1ULL))){
TRY((((*this).error(TRY((String::formatted(String("Enum variant ‘{}’ must have exactly one argument"),((variant).name())))),span))));
return (JaktInternal::OptionalNone());
}
return ((TRY((Array<types::CheckedEnumVariantBinding>::create_with({types::CheckedEnumVariantBinding(JaktInternal::OptionalNone(),((((bindings)[static_cast<i64>(0LL)])).binding),type_id,span)})))));
}
if (((variant).index() == 3 /* StructLike */)){
const JaktInternal::Array<types::VarId> fields = (variant.get<types::CheckedEnumVariant::StructLike>()).fields;
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
const String binding_name = ((binding).name).value_or_lazy_evaluated([&] { return ((binding).binding); });
const types::TypeId type_id = ((var).type_id);
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

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_imports(const parser::ParsedNamespace parsed_namespace,const types::ScopeId scope_id) {
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

ErrorOr<void> typechecker::Typechecker::typecheck_enum(const parser::ParsedRecord record,const types::EnumId enum_id,const types::ScopeId parent_scope_id) {
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

ErrorOr<types::CheckedParameter> typechecker::Typechecker::typecheck_parameter(const parser::ParsedParameter parameter,const types::ScopeId scope_id,const bool first,const JaktInternal::Optional<types::TypeId> this_arg_type_id,const JaktInternal::Optional<types::ScopeId> check_scope) {
{
types::TypeId type_id = TRY((((*this).typecheck_typename(((((parameter).variable)).parsed_type),scope_id,((((parameter).variable)).name)))));
if ((first && (((((parameter).variable)).name) == String("this")))){
if (((this_arg_type_id).has_value())){
(type_id = (this_arg_type_id.value()));
}
}
const types::CheckedVariable variable = types::CheckedVariable(((((parameter).variable)).name),type_id,((((parameter).variable)).is_mutable),((((parameter).variable)).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> checked_default_value = JaktInternal::OptionalNone();
if (((((parameter).default_argument)).has_value())){
NonnullRefPtr<types::CheckedExpression> checked_default_value_expr = TRY((((*this).typecheck_expression((((parameter).default_argument).value()),scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,type_id))));
if (((checked_default_value_expr)->index() == 22 /* OptionalNone */)){
const utility::Span expr_span = (checked_default_value_expr->get<types::CheckedExpression::OptionalNone>()).span;
(checked_default_value_expr = TRY((types::CheckedExpression::template create<typename types::CheckedExpression::OptionalNone>(expr_span,type_id))));
}
const types::TypeId default_value_type_id = ((checked_default_value_expr)->type());
(checked_default_value = checked_default_value_expr);
if ((!(TRY((((*this).check_types_for_compat(type_id,default_value_type_id,((((*this).generic_inferences))),((checked_default_value_expr)->span())))))))){
(checked_default_value = JaktInternal::OptionalNone());
}
}
const types::CheckedParameter checked_parameter = types::CheckedParameter(((parameter).requires_label),variable,checked_default_value);
if (((check_scope).has_value())){
NonnullRefPtr<types::Module> module = ((*this).current_module());
const types::VarId var_id = TRY((((module)->add_variable(variable))));
TRY((((*this).add_var_to_scope((check_scope.value()),((((parameter).variable)).name),var_id,((((parameter).variable)).span)))));
}
return (checked_parameter);
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct(const parser::ParsedRecord record,const types::StructId struct_id,const types::ScopeId parent_scope_id) {
{
const types::TypeId struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
JaktInternal::Dictionary<String,NonnullRefPtr<types::CheckedFunction>> all_virtuals = (TRY((Dictionary<String, NonnullRefPtr<types::CheckedFunction>>::create_with_entries({}))));
JaktInternal::Optional<types::StructId> super_struct_id = ((((*this).get_struct(struct_id))).super_struct_id);
while (((super_struct_id).has_value())){
const types::CheckedStruct super_struct = ((*this).get_struct((super_struct_id.value())));
const NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(((super_struct).scope_id)))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> function_tuple = (_magic_value.value());
{
const NonnullRefPtr<types::CheckedFunction> function_ = ((*this).get_function(((function_tuple).get<1>())));
if (((function_)->is_virtual)){
TRY(all_virtuals.set(((function_)->name), function_));
}
}

}
}

(super_struct_id = ((super_struct).super_struct_id));
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

(((*this).current_struct_type_id) = JaktInternal::OptionalNone());
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_predecl_initial(const parser::ParsedRecord parsed_record,const size_t struct_index,const size_t module_struct_len,const types::ScopeId scope_id) {
{
const types::ModuleId module_id = ((*this).current_module_id);
const types::StructId struct_id = types::StructId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(struct_index,module_struct_len)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
TRY((((((module)->types)).push(TRY((types::Type::template create<typename types::Type::Struct>(struct_id)))))));
const types::TypeId struct_type_id = types::TypeId(module_id,(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((*this).add_type_to_scope(scope_id,((parsed_record).name),struct_type_id,((parsed_record).name_span)))));
const types::ScopeId struct_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((String::formatted(String("struct({})"),((parsed_record).name))))))));
TRY((((((module)->structures)).push(types::CheckedStruct(((parsed_record).name),((parsed_record).name_span),(TRY((Array<types::TypeId>::create_with({})))),(TRY((Array<types::VarId>::create_with({})))),struct_scope_id,((parsed_record).definition_linkage),((parsed_record).record_type),struct_type_id,JaktInternal::OptionalNone())))));
}
return {};
}

ErrorOr<NonnullRefPtr<types::CheckedExpression>> typechecker::Typechecker::typecheck_match(const NonnullRefPtr<parser::ParsedExpression> expr,const JaktInternal::Array<parser::ParsedMatchCase> cases,const utility::Span span,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const JaktInternal::Optional<types::TypeId> type_hint) {
{
const NonnullRefPtr<types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
const types::TypeId subject_type_id = ((checked_expr)->type());
const NonnullRefPtr<types::Type> type_to_match_on = ((*this).get_type(subject_type_id));
JaktInternal::Array<types::CheckedMatchCase> checked_cases = (TRY((Array<types::CheckedMatchCase>::create_with({}))));
const JaktInternal::Dictionary<String,String> old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_287([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
JaktInternal::Optional<types::TypeId> final_result_type = JaktInternal::OptionalNone();
if ((((type_hint).has_value()) && ((!((((type_hint.value())).equals(types::unknown_type_id())))) && (!(((((*this).get_type((type_hint.value()))))->index() == 18 /* TypeVariable */)))))){
(final_result_type = type_hint);
}
if (((type_to_match_on)->index() == 20 /* GenericEnumInstance */)){
const types::EnumId id = (type_to_match_on->get<types::Type::GenericEnumInstance>()).id;
const JaktInternal::Array<types::TypeId> args = (type_to_match_on->get<types::Type::GenericEnumInstance>()).args;
const types::CheckedEnum enum_ = ((*this).get_enum(id));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
const String generic = TRY((((((((enum_).generic_parameters))[i])).to_string())));
const String argument_type = TRY((((((args)[i])).to_string())));
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
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
const types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
bool seen_catch_all = false;
bool expanded_catch_all = false;
JaktInternal::Optional<utility::Span> catch_all_span = JaktInternal::OptionalNone();
JaktInternal::Set<String> covered_variants = (TRY((Set<String>::create_with_values({}))));
const size_t case_count = ((cases).size());
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
const JaktInternal::Tuple<String,utility::Span> temp = ((variant_names_)[static_cast<i64>(0LL)]);
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
const JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,(variant_index.value()),final_result_type,(matched_variant.value()),variant_arguments,arguments_span,scope_id,safety_mode))));
const JaktInternal::Optional<String> covered_name = ((covered_name_checked_match_case_result_type_).get<0>());
const types::CheckedMatchCase checked_match_case = ((covered_name_checked_match_case_result_type_).get<1>());
const JaktInternal::Optional<types::TypeId> result_type = ((covered_name_checked_match_case_result_type_).get<2>());

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
const JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,variant_index,final_result_type,variant,variant_arguments,arguments_span,scope_id,safety_mode))));
const JaktInternal::Optional<String> covered_name = ((covered_name_checked_match_case_result_type_).get<0>());
const types::CheckedMatchCase checked_match_case = ((covered_name_checked_match_case_result_type_).get<1>());
const JaktInternal::Optional<types::TypeId> result_type = ((covered_name_checked_match_case_result_type_).get<2>());

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
const types::ScopeId new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),String("catch-all")))));
const JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
const types::CheckedMatchBody checked_body = ((checked_body_result_type_).get<0>());
const JaktInternal::Optional<types::TypeId> result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
const types::CheckedMatchCase checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll(false,checked_body,((case_).marker_span)) } ;
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
const types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
bool seen_catch_all = false;
bool expanded_catch_all = false;
JaktInternal::Optional<utility::Span> catch_all_span = JaktInternal::OptionalNone();
JaktInternal::Set<String> covered_variants = (TRY((Set<String>::create_with_values({}))));
const size_t case_count = ((cases).size());
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
const JaktInternal::Tuple<String,utility::Span> temp = ((variant_names_)[static_cast<i64>(0LL)]);
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
const JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,(variant_index.value()),final_result_type,(matched_variant.value()),variant_arguments,arguments_span,scope_id,safety_mode))));
const JaktInternal::Optional<String> covered_name = ((covered_name_checked_match_case_result_type_).get<0>());
const types::CheckedMatchCase checked_match_case = ((covered_name_checked_match_case_result_type_).get<1>());
const JaktInternal::Optional<types::TypeId> result_type = ((covered_name_checked_match_case_result_type_).get<2>());

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
const JaktInternal::Tuple<JaktInternal::Optional<String>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,variant_index,final_result_type,variant,variant_arguments,arguments_span,scope_id,safety_mode))));
const JaktInternal::Optional<String> covered_name = ((covered_name_checked_match_case_result_type_).get<0>());
const types::CheckedMatchCase checked_match_case = ((covered_name_checked_match_case_result_type_).get<1>());
const JaktInternal::Optional<types::TypeId> result_type = ((covered_name_checked_match_case_result_type_).get<2>());

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
const types::ScopeId new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),String("catch-all")))));
const JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
const types::CheckedMatchBody checked_body = ((checked_body_result_type_).get<0>());
const JaktInternal::Optional<types::TypeId> result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
const types::CheckedMatchCase checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll(false,checked_body,((case_).marker_span)) } ;
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
const size_t case_count = ((cases).size());
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
const types::ScopeId new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((String::formatted(String("catch-enum-variant({})"),variant_names)))))));
const JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
const types::CheckedMatchBody checked_body = ((checked_body_result_type_).get<0>());
const JaktInternal::Optional<types::TypeId> result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
const types::CheckedMatchCase checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::EnumVariant((((((variant_names).last()).value())).get<0>()),variant_arguments,subject_type_id,static_cast<size_t>(0ULL),new_scope_id,checked_body,((case_).marker_span)) } ;
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

const types::ScopeId new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),String("catch-all")))));
const JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
const types::CheckedMatchBody checked_body = ((checked_body_result_type_).get<0>());
const JaktInternal::Optional<types::TypeId> result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
const types::CheckedMatchCase checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll((((variant_arguments).size()) != static_cast<size_t>(0ULL)),checked_body,((case_).marker_span)) } ;
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
const NonnullRefPtr<types::CheckedExpression> checked_expression = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,static_cast<JaktInternal::Optional<types::TypeId>>(subject_type_id)))));
if ((!(((((checked_expression)->to_number_constant(((*this).program)))).has_value())))){
(all_variants_constant = false);
}
types::TypeId expression_type = ((checked_expression)->type());
if (((checked_expression)->index() == 8 /* Range */)){
const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> from = (checked_expression->get<types::CheckedExpression::Range>()).from;
const JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> to = (checked_expression->get<types::CheckedExpression::Range>()).to;
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
const types::ScopeId new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((String::formatted(String("catch-expression({})"),expr)))))));
const JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
const types::CheckedMatchBody checked_body = ((checked_body_result_type_).get<0>());
const JaktInternal::Optional<types::TypeId> result_type = ((checked_body_result_type_).get<1>());

(final_result_type = result_type);
const types::CheckedMatchCase checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::Expression(checked_expression,checked_body,((case_).marker_span)) } ;
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

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_generic_resolved_type(const String name,const JaktInternal::Array<types::TypeId> checked_inner_types,const types::ScopeId scope_id,const utility::Span span) {
{
const JaktInternal::Optional<types::StructId> struct_id = TRY((((*this).find_struct_in_scope(scope_id,name))));
if (((struct_id).has_value())){
return (TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericInstance>((struct_id.value()),checked_inner_types))))))));
}
const JaktInternal::Optional<types::EnumId> enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,name))));
if (((enum_id).has_value())){
return (TRY((((*this).find_or_add_type_id(TRY((types::Type::template create<typename types::Type::GenericEnumInstance>((enum_id.value()),checked_inner_types))))))));
}
TRY((((*this).error(TRY((String::formatted(String("could not find {}"),name))),span))));
return (types::unknown_type_id());
}
}

types::BlockControlFlow typechecker::Typechecker::maybe_statement_control_flow(const JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> statement,const types::BlockControlFlow other_branch) const {
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

ErrorOr<void> typechecker::Typechecker::typecheck_jakt_main(const parser::ParsedFunction parsed_function) {
{
const String param_type_error = String("Main function must take a single array of strings as its parameter");
if ((((((parsed_function).params)).size()) > static_cast<size_t>(1ULL))){
TRY((((*this).error(param_type_error,((parsed_function).name_span)))));
}
if ((!(((((parsed_function).params)).is_empty())))){
if (((((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type))->index() == 3 /* JaktArray */)){
const NonnullRefPtr<parser::ParsedType> inner = (((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type)->get<parser::ParsedType::JaktArray>()).inner;
const utility::Span span = (((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type)->get<parser::ParsedType::JaktArray>()).span;
if (((inner)->index() == 0 /* Name */)){
const String name = (inner->get<parser::ParsedType::Name>()).name;
const utility::Span span = (inner->get<parser::ParsedType::Name>()).span;
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
const String return_type_error = String("Main function must return c_int");
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

ErrorOr<NonnullRefPtr<types::CheckedStatement>> typechecker::Typechecker::typecheck_for(const String iterator_name,const utility::Span name_span,const NonnullRefPtr<parser::ParsedExpression> range,const parser::ParsedBlock block,const types::ScopeId scope_id,const types::SafetyMode safety_mode,const utility::Span span) {
{
const JaktInternal::Optional<utility::Span> maybe_span = ((block).find_yield_span());
if (((maybe_span).has_value())){
TRY((((*this).error(String("a 'for' loop block is not allowed to yield values"),(maybe_span.value())))));
}
const NonnullRefPtr<types::CheckedExpression> iterable_expr = TRY((((*this).typecheck_expression(range,scope_id,safety_mode,JaktInternal::OptionalNone()))));
bool iterable_should_be_mutable = false;
const NonnullRefPtr<types::Type> iterable_type = ((((*this).program))->get_type(((iterable_expr)->type())));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<types::CheckedStatement>>>{
auto&& __jakt_match_variant = *iterable_type;
switch(__jakt_match_variant.index()) {
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
{
(iterable_should_be_mutable = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
{
const types::CheckedStruct struct_ = ((*this).get_struct(id));
const JaktInternal::Optional<types::FunctionId> next_method_function_id = TRY((((*this).find_function_in_scope(((struct_).scope_id),String("next")))));
if ((!(((next_method_function_id).has_value())))){
TRY((((*this).error(String("Iterator must have a .next() method"),((range)->span())))));
}
else {
const NonnullRefPtr<types::CheckedFunction> next_method_function = ((*this).get_function((next_method_function_id.value())));
if (((next_method_function)->is_mutating())){
(iterable_should_be_mutable = true);
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
{
const types::CheckedStruct struct_ = ((*this).get_struct(id));
const JaktInternal::Optional<types::FunctionId> next_method_function_id = TRY((((*this).find_function_in_scope(((struct_).scope_id),String("next")))));
if ((!(((next_method_function_id).has_value())))){
TRY((((*this).error(String("Iterator must have a .next() method"),((range)->span())))));
}
else {
const NonnullRefPtr<types::CheckedFunction> next_method_function = ((*this).get_function((next_method_function_id.value())));
if (((next_method_function)->is_mutating())){
(iterable_should_be_mutable = true);
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(String("Iterator must have a .next() method"),name_span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
const NonnullRefPtr<parser::ParsedStatement> rewritten_statement = TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Block>(parser::ParsedBlock((TRY((Array<NonnullRefPtr<parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(String("_magic"),TRY((parser::ParsedType::template create<typename parser::ParsedType::Empty>())),iterable_should_be_mutable,JaktInternal::OptionalNone(),name_span),range,span))), TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Loop>(parser::ParsedBlock((TRY((Array<NonnullRefPtr<parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(String("_magic_value"),TRY((parser::ParsedType::template create<typename parser::ParsedType::Empty>())),iterable_should_be_mutable,JaktInternal::OptionalNone(),name_span),TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::MethodCall>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::Var>(String("_magic"),name_span))),parser::ParsedCall((TRY((Array<String>::create_with({})))),String("next"),(TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>>::create_with({})))),(TRY((Array<NonnullRefPtr<parser::ParsedType>>::create_with({}))))),false,name_span))),span))), TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::If>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::UnaryOp>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::MethodCall>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::Var>(String("_magic_value"),name_span))),parser::ParsedCall((TRY((Array<String>::create_with({})))),String("has_value"),(TRY((Array<JaktInternal::Tuple<String,utility::Span,NonnullRefPtr<parser::ParsedExpression>>>::create_with({})))),(TRY((Array<NonnullRefPtr<parser::ParsedType>>::create_with({}))))),false,name_span))), parser::UnaryOperator { typename parser::UnaryOperator::LogicalNot() } ,name_span))),parser::ParsedBlock((TRY((Array<NonnullRefPtr<parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Break>(span)))}))))),JaktInternal::OptionalNone(),span))), TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(iterator_name,TRY((parser::ParsedType::template create<typename parser::ParsedType::Empty>())),iterable_should_be_mutable,name_span,name_span),TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::ForcedUnwrap>(TRY((parser::ParsedExpression::template create<typename parser::ParsedExpression::Var>(String("_magic_value"),name_span))),name_span))),span))), TRY((parser::ParsedStatement::template create<typename parser::ParsedStatement::Block>(block,span)))}))))),span)))}))))),span)));
return (TRY((((*this).typecheck_statement(rewritten_statement,scope_id,safety_mode,JaktInternal::OptionalNone())))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_constructors(const parser::ParsedNamespace parsed_namespace,const types::ScopeId scope_id) {
{
const JaktInternal::Array<types::ScopeId> children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
const parser::ParsedNamespace child_namespace = ((((parsed_namespace).namespaces))[i]);
const types::ScopeId child_namespace_scope_id = ((children)[i]);
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
const JaktInternal::Optional<types::StructId> struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find previously added struct")))));
}
TRY((((*this).typecheck_struct_constructor(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();{
const JaktInternal::Optional<types::StructId> struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find previously added struct")))));
}
TRY((((*this).typecheck_struct_constructor(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
const JaktInternal::Optional<types::EnumId> enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(String("can't find previously added enum")))));
}
TRY((((*this).typecheck_enum_constructor(record,(enum_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
const JaktInternal::Optional<types::EnumId> enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
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

}
} // namespace Jakt
