#include "typechecker.h"
namespace Jakt {
namespace typechecker {
ErrorOr<DeprecatedString> typechecker::TraitImplementationDescriptor::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("TraitImplementationDescriptor("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trait_id: {}, ", trait_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trait_name: \"{}\", ", trait_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("implemented_type_args: {}", implemented_type_args));
}
TRY(builder.append(")"sv));return builder.to_string(); }
typechecker::TraitImplementationDescriptor::TraitImplementationDescriptor(types::TraitId a_trait_id, DeprecatedString a_trait_name, JaktInternal::DynamicArray<types::TypeId> a_implemented_type_args) :trait_id(move(a_trait_id)), trait_name(move(a_trait_name)), implemented_type_args(move(a_implemented_type_args)){}

ErrorOr<DeprecatedString> typechecker::TraitImplCheck::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("TraitImplCheck("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("missing_methods: {}, ", missing_methods));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("unmatched_signatures: {}, ", unmatched_signatures));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("private_matching_methods: {}, ", private_matching_methods));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("already_implemented_for: {}", already_implemented_for));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> typechecker::TraitImplCheck::throw_errors(utility::Span const record_decl_span,typechecker::Typechecker& typechecker) {
{
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>> _magic = ((((*this).missing_methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>> trait_name__missing_methods__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>> const jakt__trait_name__missing_methods__ = trait_name__missing_methods__;
DeprecatedString const trait_name = ((jakt__trait_name__missing_methods__).template get<0>());
JaktInternal::Dictionary<DeprecatedString,types::FunctionId> const missing_methods = ((jakt__trait_name__missing_methods__).template get<1>());

JaktInternal::Dictionary<DeprecatedString,utility::Span> const unmatched_signatures = ((((*this).unmatched_signatures))[trait_name]);
JaktInternal::Dictionary<DeprecatedString,utility::Span> const private_matching_methods = ((((*this).private_matching_methods))[trait_name]);
{
JaktInternal::DictionaryIterator<DeprecatedString,types::FunctionId> _magic = ((missing_methods).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::FunctionId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::FunctionId> method_name__trait_method_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::FunctionId> const jakt__method_name__trait_method_id__ = method_name__trait_method_id__;
DeprecatedString const method_name = ((jakt__method_name__trait_method_id__).template get<0>());
types::FunctionId const trait_method_id = ((jakt__method_name__trait_method_id__).template get<1>());

JaktInternal::Optional<typechecker::AlreadyImplementedFor> const already_implemented_for = ((((*this).already_implemented_for)).get(method_name));
JaktInternal::Optional<utility::Span> const unmatched_signature = ((unmatched_signatures).get(method_name));
JaktInternal::Optional<utility::Span> const private_matching_method = ((private_matching_methods).get(method_name));
if (((already_implemented_for).has_value())){
TRY((((((typechecker))).error(TRY((__jakt_format((StringView::from_string_literal("Cannot implement ‘{}’ for ‘{}’ because it's already implementing ‘{}’"sv)),method_name,trait_name,(((already_implemented_for.value())).trait_name)))),(((already_implemented_for.value())).encounter_span)))));
}
else if (((private_matching_method).has_value())){
utility::Span const span = (private_matching_method.value());
TRY((((((typechecker))).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Implementation of ‘{}’ for trait ‘{}’ is valid but is not public"sv)),method_name,trait_name))),span,TRY(DeprecatedString::from_utf8("Consider adding ‘public’ to make the method accessible"sv)),span))));
}
else {
NonnullRefPtr<types::CheckedFunction> const func = ((((typechecker))).get_function(trait_method_id));
if ((!(((((((func)->block)).statements)).is_empty())))){
continue;
}
if (((unmatched_signature).has_value())){
utility::Span const method_span = (unmatched_signature.value());
TRY((((((typechecker))).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Missing implementation for method ‘{}’ of trait ‘{}’"sv)),method_name,trait_name))),record_decl_span,TRY(DeprecatedString::from_utf8("The method is declared here, but its signature doesn't match"sv)),method_span))));
}
else {
utility::Span const trait_method_span = ((((((typechecker))).get_function(trait_method_id)))->name_span);
TRY((((((typechecker))).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Missing implementation for method ‘{}’ of trait ‘{}’"sv)),method_name,trait_name))),record_decl_span,TRY(DeprecatedString::from_utf8("Consider implementing the method with the signature specified here"sv)),trait_method_span))));
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

ErrorOr<void> typechecker::TraitImplCheck::ensure_capacity(size_t const count) {
{
TRY((((((*this).missing_methods)).ensure_capacity(count))));
TRY((((((*this).unmatched_signatures)).ensure_capacity(count))));
TRY((((((*this).private_matching_methods)).ensure_capacity(count))));
TRY((((((*this).already_implemented_for)).ensure_capacity(count))));
}
return {};
}

ErrorOr<void> typechecker::TraitImplCheck::register_method(types::TypeId const self_type_id,DeprecatedString const method_name,types::FunctionId const method_id,typechecker::Typechecker& typechecker) {
{
NonnullRefPtr<types::CheckedFunction> const method = ((((typechecker))).get_function(method_id));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>> _magic = ((((*this).missing_methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>> trait_name__methods__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>> const jakt__trait_name__methods__ = trait_name__methods__;
DeprecatedString const trait_name = ((jakt__trait_name__methods__).template get<0>());
JaktInternal::Dictionary<DeprecatedString,types::FunctionId> const methods = ((jakt__trait_name__methods__).template get<1>());

JaktInternal::Optional<types::FunctionId> const trait_method_id = ((methods).get(method_name));
if (((trait_method_id).has_value())){
NonnullRefPtr<types::CheckedFunction> const trait_method = ((((typechecker))).get_function((trait_method_id.value())));
if (TRY((((((typechecker))).signatures_match(self_type_id,trait_method,method))))){
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

ErrorOr<typechecker::TraitImplCheck> typechecker::TraitImplCheck::make() {
{
return typechecker::TraitImplCheck((TRY((Dictionary<DeprecatedString, JaktInternal::Dictionary<DeprecatedString,types::FunctionId>>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, JaktInternal::Dictionary<DeprecatedString,utility::Span>>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, JaktInternal::Dictionary<DeprecatedString,utility::Span>>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, typechecker::AlreadyImplementedFor>::create_with_entries({})))));
}
}

typechecker::TraitImplCheck::TraitImplCheck(JaktInternal::Dictionary<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,types::FunctionId>> a_missing_methods, JaktInternal::Dictionary<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,utility::Span>> a_unmatched_signatures, JaktInternal::Dictionary<DeprecatedString,JaktInternal::Dictionary<DeprecatedString,utility::Span>> a_private_matching_methods, JaktInternal::Dictionary<DeprecatedString,typechecker::AlreadyImplementedFor> a_already_implemented_for) :missing_methods(move(a_missing_methods)), unmatched_signatures(move(a_unmatched_signatures)), private_matching_methods(move(a_private_matching_methods)), already_implemented_for(move(a_already_implemented_for)){}

ErrorOr<void> typechecker::TraitImplCheck::register_trait(types::TraitId const trait_id,DeprecatedString const trait_name,JaktInternal::Dictionary<DeprecatedString,types::FunctionId> const trait_methods) {
{
TRY(((*this).unmatched_signatures).set(trait_name, (TRY((Dictionary<DeprecatedString, utility::Span>::create_with_entries({}))))));
TRY(((*this).private_matching_methods).set(trait_name, (TRY((Dictionary<DeprecatedString, utility::Span>::create_with_entries({}))))));
JaktInternal::Dictionary<DeprecatedString,types::FunctionId> missing_methods = (TRY((Dictionary<DeprecatedString, types::FunctionId>::create_with_entries({}))));
TRY((((missing_methods).ensure_capacity(((trait_methods).size())))));
{
JaktInternal::DictionaryIterator<DeprecatedString,types::FunctionId> _magic = ((trait_methods).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::FunctionId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::FunctionId> method_name__method_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::FunctionId> const jakt__method_name__method_id__ = method_name__method_id__;
DeprecatedString const method_name = ((jakt__method_name__method_id__).template get<0>());
types::FunctionId const method_id = ((jakt__method_name__method_id__).template get<1>());

TRY((((missing_methods).set(method_name,method_id))));
}

}
}

TRY((((((*this).missing_methods)).set(trait_name,missing_methods))));
}
return {};
}

ErrorOr<DeprecatedString> typechecker::AlreadyImplementedFor::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("AlreadyImplementedFor("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trait_name: \"{}\", ", trait_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("encounter_span: {}", encounter_span));
}
TRY(builder.append(")"sv));return builder.to_string(); }
typechecker::AlreadyImplementedFor::AlreadyImplementedFor(DeprecatedString a_trait_name, utility::Span a_encounter_span) :trait_name(move(a_trait_name)), encounter_span(move(a_encounter_span)){}

ErrorOr<DeprecatedString> typechecker::ImportRestrictions::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("ImportRestrictions("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("functions: {}, ", functions));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("structs: {}, ", structs));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("enums: {}, ", enums));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("types: {}, ", types));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("traits: {}, ", traits));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("namespaces: {}", namespaces));
}
TRY(builder.append(")"sv));return builder.to_string(); }
typechecker::ImportRestrictions::ImportRestrictions(bool a_functions, bool a_structs, bool a_enums, bool a_types, bool a_traits, bool a_namespaces) :functions(move(a_functions)), structs(move(a_structs)), enums(move(a_enums)), types(move(a_types)), traits(move(a_traits)), namespaces(move(a_namespaces)){}

typechecker::ImportRestrictions typechecker::ImportRestrictions::all() {
{
return typechecker::ImportRestrictions(true,true,true,true,true,true);
}
}

ErrorOr<DeprecatedString> typechecker::Typechecker::debug_description() const { auto builder = MUST(DeprecatedStringBuilder::create());TRY(builder.append("Typechecker("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("compiler: {}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("program: {}, ", *program));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_module_id: {}, ", current_module_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_struct_type_id: {}, ", current_struct_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_function_id: {}, ", current_function_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("inside_defer: {}, ", inside_defer));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("checkidx: {}, ", checkidx));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("ignore_errors: {}, ", ignore_errors));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("dump_type_hints: {}, ", dump_type_hints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("dump_try_hints: {}, ", dump_try_hints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("lambda_count: {}, ", lambda_count));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generic_inferences: {}, ", generic_inferences));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("self_type_id: {}, ", self_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("root_module_name: \"{}\", ", root_module_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("in_comptime_function_call: {}, ", in_comptime_function_call));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("had_an_error: {}", had_an_error));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> typechecker::Typechecker::typecheck_struct_predecl_initial(parser::ParsedRecord const parsed_record,size_t const struct_index,size_t const module_struct_len,types::ScopeId const scope_id) {
{
types::ModuleId const module_id = ((*this).current_module_id);
types::StructId const struct_id = types::StructId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(struct_index,module_struct_len)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
TRY((((((module)->types)).push(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(struct_id)))))));
types::TypeId const struct_type_id = types::TypeId(module_id,(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((*this).add_type_to_scope(scope_id,((parsed_record).name),struct_type_id,((parsed_record).name_span)))));
types::ScopeId const struct_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((__jakt_format((StringView::from_string_literal("struct({})"sv)),((parsed_record).name)))),false))));
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(struct_scope_id))));
(((scope)->namespace_name) = ((parsed_record).name));
(((scope)->external_name) = ((parsed_record).external_name));
TRY((((((module)->structures)).push(types::CheckedStruct(((parsed_record).name),((parsed_record).name_span),(TRY((DynamicArray<types::CheckedGenericParameter>::create_with({})))),(TRY((DynamicArray<types::CheckedField>::create_with({})))),struct_scope_id,((parsed_record).definition_linkage),(TRY((Dictionary<DeprecatedString, JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>::create_with_entries({})))),((parsed_record).record_type),struct_type_id,JaktInternal::OptionalNone(),((parsed_record).external_name))))));
}
return {};
}

ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>>> typechecker::Typechecker::typecheck_match_body(parser::ParsedMatchBody const body,types::ScopeId const scope_id,types::SafetyMode const safety_mode,types::GenericInferences& generic_inferences,JaktInternal::Optional<types::TypeId> const final_result_type,utility::Span const span) {
{
JaktInternal::Optional<types::TypeId> result_type = final_result_type;
types::CheckedMatchBody const checked_match_body = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedMatchBody, ErrorOr<JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedMatchBody::Block>();
parser::ParsedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedMatchBody> __jakt_var_418; {
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
(final_body =  types::CheckedMatchBody { typename types::CheckedMatchBody::Expression(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Block>(checked_block,span,(((checked_block).yielded_type).value()))))) } );
}
else {
(final_body =  types::CheckedMatchBody { typename types::CheckedMatchBody::Block(checked_block) } );
}

__jakt_var_418 = (final_body.value()); goto __jakt_label_394;

}
__jakt_label_394:; __jakt_var_418.release_value(); }));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedMatchBody::Expression>();
NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedMatchBody> __jakt_var_419; {
NonnullRefPtr<typename types::CheckedExpression> const checked_expression = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,result_type))));
if (((result_type).has_value())){
TRY((((*this).check_types_for_compat((result_type.value()),((checked_expression)->type()),generic_inferences,span))));
}
else {
(result_type = ((checked_expression)->type()));
}

__jakt_var_419 =  types::CheckedMatchBody { typename types::CheckedMatchBody::Expression(checked_expression) } ; goto __jakt_label_395;

}
__jakt_label_395:; __jakt_var_419.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return (Tuple{checked_match_body, result_type});
}
}

ErrorOr<DeprecatedString> typechecker::Typechecker::type_name(types::TypeId const type_id,bool const debug_mode) const {
{
types::TypeId id = type_id;
if ((((((((*this).program))->get_type(id)))->index() == 30 /* Self */) && ((((*this).self_type_id)).has_value()))){
(id = (((*this).self_type_id).value()));
}
return TRY((((((*this).program))->type_name(id,debug_mode))));
}
}

ErrorOr<types::ScopeId> typechecker::Typechecker::create_scope(JaktInternal::Optional<types::ScopeId> const parent_scope_id,bool const can_throw,DeprecatedString const debug_name,bool const for_block) {
{
return TRY((((((*this).program))->create_scope(parent_scope_id,can_throw,debug_name,((*this).current_module_id),for_block))));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_return(JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const expr,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode) {
{
if (((*this).inside_defer)){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("‘return’ is not allowed inside ‘defer’"sv)),span))));
}
if ((!(((expr).has_value())))){
if (((((*this).current_function_id)).has_value())){
NonnullRefPtr<types::CheckedFunction> const current_function = ((*this).get_function((((*this).current_function_id).value())));
NonnullRefPtr<typename types::Type> const return_type = ((*this).get_type(((current_function)->return_type_id)));
if (((!(((return_type)->index() == 0 /* Void */))) && (!(((return_type)->index() == 16 /* Unknown */))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("’return’ with no value in function ’{}’ returning ’{}’"sv)),((current_function)->name),TRY((((*this).type_name(((current_function)->return_type_id),false))))))),span,TRY((__jakt_format((StringView::from_string_literal("Add return value of type ’{}’ here"sv)),TRY((((*this).type_name(((current_function)->return_type_id),false))))))),span))));
}
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Return>(JaktInternal::OptionalNone(),span)));
}
if (((!((((((*this).current_function_id)).has_value()) && ((((*this).get_function((((*this).current_function_id).value()))))->is_comptime)))) && (((expr.value()))->index() == 25 /* Function */))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Returning a function is not currently supported"sv)),span))));
}
JaktInternal::Optional<types::TypeId> type_hint = JaktInternal::OptionalNone();
if (((((*this).current_function_id)).has_value())){
(type_hint = static_cast<JaktInternal::Optional<types::TypeId>>(((((*this).get_function((((*this).current_function_id).value()))))->return_type_id)));
}
JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings((expr.value()),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),scope_id,span))));
NonnullRefPtr<typename parser::ParsedExpression> const new_condition = ((new_condition_new_then_block_new_else_statement_).template get<0>());
JaktInternal::Optional<parser::ParsedBlock> const new_then_block = ((new_condition_new_then_block_new_else_statement_).template get<1>());
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const new_else_statement = ((new_condition_new_then_block_new_else_statement_).template get<2>());

NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,type_hint,span))));
if (((type_hint).has_value())){
if (((checked_expr)->index() == 25 /* OptionalNone */)){
utility::Span const span = ((checked_expr)->get<types::CheckedExpression::OptionalNone>()).span;
if (((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type((type_hint.value()))))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type((type_hint.value()))))->get<types::Type::GenericInstance>()).args;
if (((!(((id).equals(TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv)))))))))) && (!(((id).equals(TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv)))))))))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot assign None to a non-optional type"sv)),span))));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot assign None to a non-optional type"sv)),span))));
}

}
TRY((((*this).unify_with_type(((checked_expr)->type()),(type_hint.value()),span))));
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Return>(checked_expr,span)));
}
}

NonnullRefPtr<types::CheckedTrait> typechecker::Typechecker::get_trait(types::TraitId const id) const {
{
return ((((*this).program))->get_trait(id));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_function_predecl(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
JaktInternal::DynamicArray<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_function_predecl(child_namespace,child_namespace_scope_id,comptime_pass,generic_pass))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((parsed_namespace).functions)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction fun = (_magic_value.value());
{
if (((((fun).is_comptime) == comptime_pass) && (generic_pass == (!(((((fun).generic_parameters)).is_empty())))))){
TRY((((*this).typecheck_function_predecl(fun,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
}
}

}
}

NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
types::ScopeId const record_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_420; {
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
return JaktInternal::LoopContinue{};
}
__jakt_var_420 = ((((*this).get_struct((struct_id.value())))).scope_id); goto __jakt_label_396;

}
__jakt_label_396:; __jakt_var_420.release_value(); }));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_421; {
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
return JaktInternal::LoopContinue{};
}
__jakt_var_421 = ((((*this).get_struct((struct_id.value())))).scope_id); goto __jakt_label_397;

}
__jakt_label_397:; __jakt_var_421.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_422; {
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
return JaktInternal::LoopContinue{};
}
__jakt_var_422 = ((((*this).get_enum((enum_id.value())))).scope_id); goto __jakt_label_398;

}
__jakt_label_398:; __jakt_var_422.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((((((method).parsed_function)).is_comptime) != comptime_pass)){
continue;
}
if ((generic_pass == (!(((((((method).parsed_function)).generic_parameters)).is_empty()))))){
continue;
}
if (((!(((((record).generic_parameters)).is_empty()))) || (!(((((((method).parsed_function)).generic_parameters)).is_empty()))))){
NonnullRefPtr<types::CheckedFunction> func = ((*this).get_function((TRY((((*this).find_function_matching_signature_in_scope(record_scope_id,((method).parsed_function))))).value())));
types::ScopeId const method_scope_id = ((func)->function_scope_id);
types::ScopeId const check_scope = TRY((((*this).create_scope(method_scope_id,((func)->can_throw),TRY((__jakt_format((StringView::from_string_literal("method-checking({}::{})"sv)),((record).name),((func)->name)))),true))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((func)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((*this).add_var_to_scope(check_scope,((((param).variable))->name),TRY((((module)->add_variable(((param).variable))))),((((param).variable))->definition_span)))));
}

}
}

bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::CheckedBlock const block = TRY((((*this).typecheck_block(((((method).parsed_function)).block),check_scope, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
types::TypeId const function_return_type_id = ((func)->return_type_id);
types::TypeId return_type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
if (((function_return_type_id).equals(types::unknown_type_id()))){
if ((!(((((block).statements)).is_empty())))){
if ((((((((block).statements)).last()).value()))->index() == 8 /* Return */)){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const val = (((((((block).statements)).last()).value()))->get<types::CheckedStatement::Return>()).val;
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

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_set(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const values,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
if ((!(((TRY((((*this).get_scope(scope_id)))))->can_throw)))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Set initialization needs to be in a try statement or a function marked as throws"sv)),span))));
}
types::TypeId inner_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> inner_type_span = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> output = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
types::StructId const set_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Set"sv))))));
JaktInternal::Optional<types::TypeId> inner_hint = JaktInternal::OptionalNone();
JaktInternal::Optional<JaktInternal::DynamicArray<types::TypeId>> const type_hint_ids = TRY((((*this).get_type_ids_from_type_hint_if_struct_ids_match(type_hint,set_struct_id))));
if (((type_hint_ids).has_value())){
(inner_hint = (((type_hint_ids.value()))[static_cast<i64>(0LL)]));
}
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedExpression>> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedExpression> value = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedExpression> const checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,inner_hint))));
types::TypeId const current_value_type_id = ((checked_value)->type());
if (((inner_type_id).equals(types::unknown_type_id()))){
if ((((current_value_type_id).equals(types::void_type_id())) || ((current_value_type_id).equals(types::unknown_type_id())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot create a set with values of type void"sv)),((value)->span())))));
}
(inner_type_id = current_value_type_id);
(inner_type_span = ((value)->span()));
}
else if ((!(((inner_type_id).equals(current_value_type_id))))){
DeprecatedString const set_type_name = TRY((((*this).type_name(inner_type_id,false))));
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Type '{}' does not match type '{}' of previous values in set"sv)),TRY((((*this).type_name(current_value_type_id,false)))),set_type_name))),((value)->span()),TRY((__jakt_format((StringView::from_string_literal("Set was inferred to store type '{}' here"sv)),set_type_name))),(inner_type_span.value())))));
}
TRY((((output).push(checked_value))));
}

}
}

if (((inner_type_id).equals(types::unknown_type_id()))){
if (((inner_hint).has_value())){
(inner_type_id = (inner_hint.value()));
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot infer generic type for Set<T>"sv)),span))));
}

}
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(set_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({inner_type_id})))))))))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::JaktSet>(output,span,type_id,inner_type_id)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_methods_predecl(parser::ParsedRecord const parsed_record,types::StructId const struct_id,types::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
ScopeGuard __jakt_var_423([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = struct_type_id);
ScopeGuard __jakt_var_424([&] {
(((*this).self_type_id) = old_self_type_id);
});
types::ScopeId const struct_scope_id = ((((((((*this).current_module()))->structures))[((struct_id).id)])).scope_id);
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((parsed_record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((((((method).parsed_function)).is_comptime) != comptime_pass)){
continue;
}
if ((generic_pass != (!(((((((method).parsed_function)).generic_parameters)).is_empty()))))){
continue;
}
types::FunctionId const function_id = TRY((((*this).typecheck_function_predecl(((method).parsed_function),struct_scope_id,struct_type_id,JaktInternal::OptionalNone()))));
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function(function_id));
(((checked_function)->is_override) = ((method).is_override));
(((checked_function)->is_virtual) = ((method).is_virtual));
(((checked_function)->visibility) = TRY((((*this).typecheck_visibility(((method).visibility),struct_scope_id)))));
if ((((checked_function)->is_virtual) && TRY((((checked_function)->is_static()))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Functions cannot be both virtual and static"sv)),((checked_function)->name_span)))));
}
if ((((checked_function)->is_override) && TRY((((checked_function)->is_static()))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Functions cannot be both override and static"sv)),((checked_function)->name_span)))));
}
}

}
}

if (((!(comptime_pass)) && ((((parsed_record).implements_list)).has_value()))){
TRY((((*this).fill_trait_implementation_list((((parsed_record).implements_list).value()),((((((((module)->structures))[((struct_id).id)])).trait_implementations))),struct_scope_id,JaktInternal::OptionalNone()))));
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = (((((parsed_record).implements_list).value())).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters implements_entry = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((implements_entry).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((((((((((*this).program))->modules))[(((((trait_id.value())).module)).id)]))->traits))[(((trait_id.value())).id)]);
{
JaktInternal::DictionaryIterator<DeprecatedString,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::FunctionId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
DeprecatedString const name = ((jakt__name__function_id__).template get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).template get<1>());

if (((TRY((((*this).find_functions_with_name_in_scope(struct_scope_id,name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function = ((((((((((*this).program))->modules))[((((function_id).module)).id)]))->functions))[((function_id).id)]);
if (((((((function)->block)).statements)).is_empty())){
continue;
}
TRY((((*this).add_function_to_scope(struct_scope_id,name,(TRY((DynamicArray<types::FunctionId>::create_with({function_id})))),((implements_entry).name_span)))));
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
}
return {};
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<types::FunctionId>>> typechecker::Typechecker::find_functions_with_name_in_scope(types::ScopeId const parent_scope_id,DeprecatedString const function_name) const {
{
return TRY((((((*this).program))->find_functions_with_name_in_scope(parent_scope_id,function_name))));
}
}

bool typechecker::Typechecker::is_class(types::TypeId const type_id) const {
{
if (((((*this).get_type(type_id)))->index() == 23 /* Struct */)){
types::StructId const struct_id = ((((*this).get_type(type_id)))->get<types::Type::Struct>()).value;
return ((((((*this).get_struct(struct_id))).record_type)).index() == 1 /* Class */);
}
else {
return false;
}

}
}

ErrorOr<types::CheckedVisibility> typechecker::Typechecker::typecheck_visibility(parser::Visibility const visibility,types::ScopeId const scope_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedVisibility, ErrorOr<types::CheckedVisibility>>{
auto&& __jakt_match_variant = visibility;
switch(__jakt_match_variant.index()) {
case 1: {
return JaktInternal::ExplicitValue( types::CheckedVisibility { typename types::CheckedVisibility::Private() } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::CheckedVisibility { typename types::CheckedVisibility::Public() } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::Visibility::Restricted>();JaktInternal::DynamicArray<parser::VisibilityRestriction> const& whitelist = __jakt_match_value.whitelist;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedVisibility> __jakt_var_425; {
JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> restricted_scopes = (TRY((DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>>::create_with({}))));
{
JaktInternal::ArrayIterator<parser::VisibilityRestriction> _magic = ((whitelist).iterator());
for (;;){
JaktInternal::Optional<parser::VisibilityRestriction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::VisibilityRestriction entry = (_magic_value.value());
{
NonnullRefPtr<typename types::MaybeResolvedScope> parent_scope = TRY((types::MaybeResolvedScope::template __jakt_create<typename types::MaybeResolvedScope::Resolved>(scope_id)));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((((entry).namespace_)).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString ns = (_magic_value.value());
{
(parent_scope = TRY((types::MaybeResolvedScope::template __jakt_create<typename types::MaybeResolvedScope::Unresolved>(parent_scope,ns))));
}

}
}

NonnullRefPtr<typename types::MaybeResolvedScope> unresolved = TRY((types::MaybeResolvedScope::template __jakt_create<typename types::MaybeResolvedScope::Unresolved>(parent_scope,((entry).name))));
TRY((((restricted_scopes).push(TRY((((unresolved)->try_resolve(((*this).program)))))))));
}

}
}

__jakt_var_425 =  types::CheckedVisibility { typename types::CheckedVisibility::Restricted(restricted_scopes,span) } ; goto __jakt_label_399;

}
__jakt_label_399:; __jakt_var_425.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_try_block(NonnullRefPtr<typename parser::ParsedStatement> const stmt,DeprecatedString const error_name,utility::Span const error_span,parser::ParsedBlock const catch_block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
types::ScopeId const try_scope_id = TRY((((*this).create_scope(scope_id,true,TRY(DeprecatedString::from_utf8("try"sv)),true))));
NonnullRefPtr<typename types::CheckedStatement> const checked_stmt = TRY((((*this).typecheck_statement(stmt,try_scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::StructId const error_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Error"sv))))));
NonnullRefPtr<types::CheckedVariable> const error_decl = TRY((types::CheckedVariable::__jakt_create(error_name,((((*this).get_struct(error_struct_id))).type_id),false,error_span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const error_id = TRY((((module)->add_variable(error_decl))));
NonnullRefPtr<types::Scope> const parent_scope = TRY((((*this).get_scope(scope_id))));
types::ScopeId const catch_scope_id = TRY((((*this).create_scope(scope_id,((parent_scope)->can_throw),TRY(DeprecatedString::from_utf8("catch"sv)),true))));
TRY((((*this).add_var_to_scope(catch_scope_id,error_name,error_id,error_span))));
types::CheckedBlock const checked_catch_block = TRY((((*this).typecheck_block(catch_block,catch_scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_catch_block).yielded_type)).has_value())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("A ‘catch’ block as part of a try block is not allowed to yield values"sv)),(((catch_block).find_yield_span()).value())))));
}
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::TryBlock>(checked_stmt,checked_catch_block,error_name,error_span,span,types::void_type_id())));
}
}

ErrorOr<JaktInternal::Optional<types::Value>> typechecker::Typechecker::find_comptime_binding_in_scope(types::ScopeId const scope_id,DeprecatedString const name) const {
{
return TRY((((((*this).program))->find_comptime_binding_in_scope(scope_id,name))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_constructor(parser::ParsedRecord const parsed_record,types::EnumId const enum_id,types::ScopeId const parent_scope_id) {
{
u64 next_constant_value = static_cast<u64>(0ULL);
JaktInternal::Set<DeprecatedString> seen_names = (TRY((Set<DeprecatedString>::create_with_values({}))));
types::CheckedEnum enum_ = ((*this).get_enum(enum_id));
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = ((enum_).type_id));
ScopeGuard __jakt_var_426([&] {
(((*this).self_type_id) = old_self_type_id);
});
JaktInternal::Set<DeprecatedString> common_seen_fields = (TRY((Set<DeprecatedString>::create_with_values({}))));
JaktInternal::DynamicArray<types::VarId> common_fields = (TRY((DynamicArray<types::VarId>::create_with({}))));
JaktInternal::DynamicArray<types::CheckedParameter> common_params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((*this).get_variable(((field).variable_id)));
TRY((((common_params).push(types::CheckedParameter(true,variable,((field).default_value))))));
TRY((((common_seen_fields).add(((variable)->name)))));
TRY((((common_fields).push(((field).variable_id)))));
}

}
}

({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();NonnullRefPtr<typename parser::ParsedType> const& underlying_type = __jakt_match_value.underlying_type;
JaktInternal::DynamicArray<parser::ValueEnumVariant> const& variants = __jakt_match_value.variants;
{
types::TypeId const underlying_type_id = TRY((((*this).typecheck_typename(underlying_type,parent_scope_id,JaktInternal::OptionalNone()))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<parser::ValueEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<parser::ValueEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ValueEnumVariant variant = (_magic_value.value());
{
if (((seen_names).contains(((variant).name)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant '{}' is defined more than once"sv)),((variant).name)))),((variant).span)))));
}
else {
TRY((((seen_names).add(((variant).name)))));
NonnullRefPtr<typename types::CheckedExpression> const expr = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>,ErrorOr<void>>{
auto __jakt_enum_value = (((((variant).value)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_427; {
NonnullRefPtr<typename types::CheckedExpression> const value_expression = TRY((((*this).cast_to_underlying((((variant).value).value()),parent_scope_id,underlying_type))));
JaktInternal::Optional<types::NumberConstant> const number_constant = ((value_expression)->to_number_constant(((*this).program)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>>{
auto __jakt_enum_value = (((number_constant).has_value()));
if (__jakt_enum_value == true) {
{
(next_constant_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<void>>{
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
{
utility::todo(TRY(DeprecatedString::from_utf8("Implement floats"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant '{}' in enum '{}' has a non-constant value: {}"sv)),((variant).name),((enum_).name),value_expression))),((variant).span)))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
__jakt_var_427 = value_expression; goto __jakt_label_400;

}
__jakt_label_400:; __jakt_var_427.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((*this).cast_to_underlying(TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::NumericConstant>( parser::NumericConstant { typename parser::NumericConstant::U64(((next_constant_value++))) } ,((variant).span)))),parent_scope_id,underlying_type)))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
TRY((((((enum_).variants)).push( types::CheckedEnumVariant { typename types::CheckedEnumVariant::WithValue(enum_id,((variant).name),expr,((variant).span)) } ))));
types::VarId const var_id = TRY((((module)->add_variable(TRY((types::CheckedVariable::__jakt_create(((variant).name),((enum_).type_id),false,((variant).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))))));
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
JaktInternal::DynamicArray<parser::SumEnumVariant> const& variants = __jakt_match_value.variants;
{
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<parser::SumEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<parser::SumEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::SumEnumVariant variant = (_magic_value.value());
{
if (((seen_names).contains(((variant).name)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant '{}' is defined more than once"sv)),((variant).name)))),((variant).span)))));
continue;
}
TRY((((seen_names).add(((variant).name)))));
bool const is_structlike = ((((((variant).params)).has_value()) && ((((((variant).params).value())).size()) > static_cast<size_t>(0ULL))) && ((((((((variant).params).value()))[static_cast<i64>(0LL)])).name) != TRY(DeprecatedString::from_utf8(""sv))));
bool const is_typed = ((((((variant).params)).has_value()) && ((((((variant).params).value())).size()) == static_cast<size_t>(1ULL))) && ((((((((variant).params).value()))[static_cast<i64>(0LL)])).name) == TRY(DeprecatedString::from_utf8(""sv))));
if (is_structlike){
JaktInternal::Set<DeprecatedString> seen_fields = (TRY((Set<DeprecatedString>::create_with_values({}))));
{
JaktInternal::SetIterator<DeprecatedString> _magic = ((common_seen_fields).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString name = (_magic_value.value());
{
TRY((((seen_fields).add(name))));
}

}
}

JaktInternal::DynamicArray<types::CheckedParameter> params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((common_params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((params).push(param))));
}

}
}

JaktInternal::DynamicArray<types::VarId> fields = (TRY((DynamicArray<types::VarId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((common_fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> const _magic_value = ((_magic).next());
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
JaktInternal::Optional<parser::ParsedVarDecl> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedVarDecl param = (_magic_value.value());
{
if (((seen_fields).contains(((param).name)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant '{}' has a member named '{}' more than once"sv)),((variant).name),((param).name)))),((param).span)))));
continue;
}
TRY((((seen_fields).add(((param).name)))));
types::TypeId const type_id = TRY((((*this).typecheck_typename(((param).parsed_type),((enum_).scope_id),((param).name)))));
NonnullRefPtr<types::CheckedVariable> const checked_var = TRY((types::CheckedVariable::__jakt_create(((param).name),type_id,((param).is_mutable),((param).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
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
JaktInternal::Optional<JaktInternal::DynamicArray<types::FunctionId>> const maybe_enum_variant_constructor = TRY((((*this).find_functions_with_name_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
bool const can_function_throw = is_boxed;
types::ScopeId const function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((__jakt_format((StringView::from_string_literal("enum-variant-constructor({}::{})"sv)),((enum_).name),((variant).name)))),true))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((__jakt_format((StringView::from_string_literal("enum-variant-constructor-block({}::{})"sv)),((enum_).name),((variant).name)))),true))));
NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::__jakt_create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),params,TRY((types::FunctionGenerics::__jakt_create(function_scope_id,params,(TRY((DynamicArray<types::FunctionGenericParameter>::create_with({})))),(TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),((variant).name),(TRY((DynamicArray<types::FunctionId>::create_with({function_id})))),((variant).span)))));
}
}
else if (is_typed){
JaktInternal::DynamicArray<types::CheckedParameter> params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((common_params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
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
JaktInternal::Optional<JaktInternal::DynamicArray<types::FunctionId>> const maybe_enum_variant_constructor = TRY((((*this).find_functions_with_name_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
bool const can_function_throw = is_boxed;
types::ScopeId const function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((__jakt_format((StringView::from_string_literal("enum-variant-constructor({}::{})"sv)),((enum_).name),((variant).name)))),true))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((__jakt_format((StringView::from_string_literal("enum-variant-constructor-block({}::{})"sv)),((enum_).name),((variant).name)))),true))));
NonnullRefPtr<types::CheckedVariable> const variable = TRY((types::CheckedVariable::__jakt_create(TRY(DeprecatedString::from_utf8("value"sv)),type_id,false,((param).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
TRY((((params).push(types::CheckedParameter(false,variable,JaktInternal::OptionalNone())))));
NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::__jakt_create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),params,TRY((types::FunctionGenerics::__jakt_create(function_scope_id,params,(TRY((DynamicArray<types::FunctionGenericParameter>::create_with({})))),(TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } ,types::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),((variant).name),(TRY((DynamicArray<types::FunctionId>::create_with({function_id})))),((variant).span)))));
}
}
else {
JaktInternal::DynamicArray<types::CheckedParameter> params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((common_params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
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
JaktInternal::Optional<JaktInternal::DynamicArray<types::FunctionId>> const maybe_enum_variant_constructor = TRY((((*this).find_functions_with_name_in_scope(((enum_).scope_id),((variant).name)))));
if ((!(((maybe_enum_variant_constructor).has_value())))){
bool const can_function_throw = is_boxed;
types::ScopeId const function_scope_id = TRY((((*this).create_scope(parent_scope_id,can_function_throw,TRY((__jakt_format((StringView::from_string_literal("enum-variant-constructor({}::{})"sv)),((enum_).name),((variant).name)))),true))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,can_function_throw,TRY((__jakt_format((StringView::from_string_literal("enum-variant-constructor-block({}::{})"sv)),((enum_).name),((variant).name)))),true))));
NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::__jakt_create(((variant).name),((variant).span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Enum>(enum_id))))))),JaktInternal::OptionalNone(),params,TRY((types::FunctionGenerics::__jakt_create(function_scope_id,params,(TRY((DynamicArray<types::FunctionGenericParameter>::create_with({})))),(TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } ,types::TypeId::none(),false),can_function_throw, parser::FunctionType { typename parser::FunctionType::ImplicitEnumConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),((variant).name),(TRY((DynamicArray<types::FunctionId>::create_with({function_id})))),((variant).span)))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_trait(parser::ParsedTrait const parsed_trait,types::TraitId const trait_id,types::ScopeId const scope_id) {
{
NonnullRefPtr<types::CheckedTrait> const checked_trait = ((((((((((*this).program))->modules))[((((trait_id).module)).id)]))->traits))[((trait_id).id)]);
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Trait>(trait_id))))))));
ScopeGuard __jakt_var_428([&] {
(((*this).self_type_id) = old_self_type_id);
});
{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((parsed_trait).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> const _magic_value = ((_magic).next());
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

ErrorOr<typechecker::FunctionMatchResult> typechecker::Typechecker::match_function_and_resolve_args(parser::ParsedCall const call,types::ScopeId const caller_scope_id,types::FunctionId const candidate,types::SafetyMode const safety_mode,utility::Span const span,JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const this_expr) {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> args = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
JaktInternal::Optional<types::TypeId> maybe_this_type_id = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<error::JaktError> argument_errors = (TRY((DynamicArray<error::JaktError>::create_with({}))));
size_t const num_old_compiler_errors = ((((((*this).compiler))->errors)).size());
NonnullRefPtr<types::CheckedFunction> const callee_candidate = ((*this).get_function(candidate));
types::ScopeId const scope_containing_callee = (((TRY((((*this).get_scope(((callee_candidate)->function_scope_id))))))->parent).value());
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const generic_inference_checkpoint = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
if (((callee_candidate)->is_instantiated)){
TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
}
ScopeGuard __jakt_var_429([&] {
{
((((*this).generic_inferences)).restore(generic_inference_checkpoint));
}

});
if (((((callee_candidate)->type)).index() == 2 /* ImplicitConstructor */)){
types::CheckedStruct const struct_ = ((*this).get_struct((((callee_candidate)->struct_id).value())));
TRY((((*this).check_implicit_constructor_argument_access(caller_scope_id,call,struct_))));
}
else {
TRY((((*this).check_method_access(caller_scope_id,scope_containing_callee,callee_candidate,span))));
}

size_t type_arg_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedType>> _magic = ((((call).type_args)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedType> parsed_type = (_magic_value.value());
{
types::TypeId const checked_type = TRY((((*this).typecheck_typename(parsed_type,caller_scope_id,JaktInternal::OptionalNone()))));
if ((((((((callee_candidate)->generics))->params)).size()) <= type_arg_index)){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Trying to access generic parameter out of bounds"sv)),((parsed_type)->span())))));
continue;
}
types::TypeId const typevar_type_id = ((((((((callee_candidate)->generics))->params))[type_arg_index])).type_id());
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
NonnullRefPtr<typename types::Type> const param_type = ((*this).get_type(type_id));
if (((param_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = ((param_type)->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((param_type)->get<types::Type::GenericInstance>()).args;
types::CheckedStruct const structure = ((*this).get_struct(id));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((structure).generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
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
if (TRY((((callee_candidate)->is_static())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot call static method on an instance of an object"sv)),span))));
}
else {
(arg_offset = static_cast<size_t>(1ULL));
}

if ((TRY((((callee_candidate)->is_mutating()))) && (!((((this_expr.value()))->is_mutable(((*this).program))))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot call mutating method on an immutable object instance"sv)),span))));
}
}
else if ((!(TRY((((callee_candidate)->is_static())))))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Cannot call an instance method statically"sv)),span,TRY(DeprecatedString::from_utf8("Add a dot before the method name to call an instance method"sv)),span))));
}
i64 total_function_specificity = static_cast<i64>(0LL);
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename types::CheckedExpression>>> const resolved_args = TRY((((*this).resolve_default_params(((((callee_candidate)->generics))->base_params),((call).args),caller_scope_id,safety_mode,arg_offset,span))));
if ((((((((callee_candidate)->generics))->base_params)).size()) == (JaktInternal::checked_add<size_t>(((resolved_args).size()),arg_offset)))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>((JaktInternal::checked_sub<size_t>(((((((callee_candidate)->generics))->base_params)).size()),arg_offset)))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename types::CheckedExpression>> const name_span_checked_arg_ = ((resolved_args)[i]);
DeprecatedString const name = ((name_span_checked_arg_).template get<0>());
utility::Span const span = ((name_span_checked_arg_).template get<1>());
NonnullRefPtr<typename types::CheckedExpression> const checked_arg = ((name_span_checked_arg_).template get<2>());

NonnullRefPtr<typename types::Type> const type_to = ((*this).get_type(((((((((((callee_candidate)->generics))->base_params))[(JaktInternal::checked_add<size_t>(i,arg_offset))])).variable))->type_id)));
({auto& _jakt_ref = total_function_specificity;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, ((type_to)->specificity(((*this).program),(static_cast<i64>(1LL) << static_cast<i64>(31LL)))));});
TRY((((*this).check_types_for_compat(((((((((((callee_candidate)->generics))->base_params))[(JaktInternal::checked_add<size_t>(i,arg_offset))])).variable))->type_id),((checked_arg)->type()),((((*this).generic_inferences))),((checked_arg)->span())))));
TRY((((args).push(checked_arg))));
}

}
}

}
size_t const num_match_errors = (JaktInternal::checked_sub<size_t>(((((((*this).compiler))->errors)).size()),num_old_compiler_errors));
if ((num_match_errors > static_cast<size_t>(0ULL))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(num_match_errors)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t error_index = (_magic_value.value());
{
TRY((((argument_errors).push((((((((*this).compiler))->errors)).pop()).value())))));
}

}
}

return  typechecker::FunctionMatchResult { typename typechecker::FunctionMatchResult::MatchError(argument_errors) } ;
}
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const used_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
return  typechecker::FunctionMatchResult { typename typechecker::FunctionMatchResult::MatchSuccess(args,maybe_this_type_id,used_inferences,total_function_specificity) } ;
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::unify_with_type(types::TypeId const found_type,JaktInternal::Optional<types::TypeId> const expected_type,utility::Span const span) {
{
if ((!(((expected_type).has_value())))){
return found_type;
}
if ((((expected_type.value())).equals(types::unknown_type_id()))){
return found_type;
}
if (TRY((((*this).check_types_for_compat((expected_type.value()),found_type,((((*this).generic_inferences))),span))))){
return found_type;
}
return TRY((((*this).substitute_typevars_in_type(found_type,((*this).generic_inferences)))));
}
}

ErrorOr<types::StructId> typechecker::Typechecker::find_struct_in_prelude(DeprecatedString const name) const {
{
return TRY((((((*this).program))->find_struct_in_prelude(name))));
}
}

bool typechecker::Typechecker::is_numeric(types::TypeId const type_id) const {
{
return ((((*this).program))->is_numeric(type_id));
}
}

types::CheckedStruct typechecker::Typechecker::get_struct(types::StructId const id) const {
{
return ((((*this).program))->get_struct(id));
}
}

types::CheckedEnum typechecker::Typechecker::get_enum(types::EnumId const id) const {
{
return ((((*this).program))->get_enum(id));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::dereference_if_needed(NonnullRefPtr<typename types::CheckedExpression> const checked_expr,utility::Span const span) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((checked_expr)->type())));
switch(__jakt_match_variant.index()) {
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Dereference() } ,span,type_id))));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Dereference() } ,span,type_id))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(checked_expr);
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<void> typechecker::Typechecker::dump_type_hint(types::TypeId const type_id,utility::Span const span) const {
{
outln((StringView::from_string_literal("{{\"type\":\"hint\",\"file_id\":{},\"position\":{},\"typename\":\"{}\"}}"sv)),((((span).file_id)).id),((span).end),TRY((((*this).type_name(type_id,false)))));
}
return {};
}

ErrorOr<void> typechecker::Typechecker::fill_trait_implementation_list(JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> const parsed_impl_list,JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>& trait_implementations,types::ScopeId const scope_id,JaktInternal::Optional<types::ScopeId> const trait_name_scope_id_override) {
{
types::ScopeId const trait_name_scope_id = trait_name_scope_id_override.value_or_lazy_evaluated([&] { return scope_id; });
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = ((parsed_impl_list).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> const maybe_type_id = TRY((((*this).find_type_in_scope(trait_name_scope_id,((trait_name).name)))));
if (((maybe_type_id).has_value())){
if (((((*this).get_type((maybe_type_id.value()))))->index() == 26 /* Trait */)){
types::TraitId const trait_id = ((((*this).get_type((maybe_type_id.value()))))->get<types::Type::Trait>()).value;
JaktInternal::DynamicArray<types::TypeId> generic_arguments = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedType>> _magic = ((((trait_name).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedType> argument = (_magic_value.value());
{
types::TypeId const argument_type_id = TRY((((*this).typecheck_typename(argument,scope_id,JaktInternal::OptionalNone()))));
TRY((((generic_arguments).push(argument_type_id))));
}

}
}

TRY((((((trait_implementations))).set(((trait_name).name),(Tuple{trait_id, generic_arguments})))));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Expected ‘{}’ to be a trait"sv)),((trait_name).name)))),((trait_name).name_span)))));
continue;
}

}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot find trait ‘{}’"sv)),((trait_name).name)))),((trait_name).name_span)))));
continue;
}

}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_statement(NonnullRefPtr<typename parser::ParsedStatement> const statement,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedStatement>, ErrorOr<NonnullRefPtr<typename types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Expression>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Expression>(TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,types::TypeId::none())))),span))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::UnsafeBlock>();parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Block>(TRY((((*this).typecheck_block(block,scope_id, types::SafetyMode { typename types::SafetyMode::Unsafe() } ,JaktInternal::OptionalNone())))),span))));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Yield>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Yield>(TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,type_hint)))),span))));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Return>();JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& expr = __jakt_match_value.expr;
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
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Defer>();NonnullRefPtr<typename parser::ParsedStatement> const& statement = __jakt_match_value.statement;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_defer(statement,scope_id,safety_mode,span)))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Loop>();parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_loop(block,scope_id,safety_mode,span)))));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Throw>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_throw(expr,scope_id,safety_mode,span)))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::While>();NonnullRefPtr<typename parser::ParsedExpression> const& condition = __jakt_match_value.condition;
parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_while(condition,block,scope_id,safety_mode,span)))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedStatement::Continue>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Continue>(span))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedStatement::Break>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Break>(span))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::VarDecl>();parser::ParsedVarDecl const& var = __jakt_match_value.var;
NonnullRefPtr<typename parser::ParsedExpression> const& init = __jakt_match_value.init;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_var_decl(var,init,scope_id,safety_mode,span)))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::DestructuringAssignment>();JaktInternal::DynamicArray<parser::ParsedVarDecl> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename parser::ParsedStatement> const& var_decl = __jakt_match_value.var_decl;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_destructuring_assignment(vars,var_decl,scope_id,safety_mode,span)))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::If>();NonnullRefPtr<typename parser::ParsedExpression> const& condition = __jakt_match_value.condition;
parser::ParsedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const& else_statement = __jakt_match_value.else_statement;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_if(condition,then_block,else_statement,scope_id,safety_mode,span)))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedStatement::Garbage>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Garbage>(span))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::For>();DeprecatedString const& iterator_name = __jakt_match_value.iterator_name;
utility::Span const& name_span = __jakt_match_value.name_span;
bool const& is_destructuring = __jakt_match_value.is_destructuring;
NonnullRefPtr<typename parser::ParsedExpression> const& range = __jakt_match_value.range;
parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_for(iterator_name,name_span,is_destructuring,range,block,scope_id,safety_mode,span)))));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Guard>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::ParsedBlock const& else_block = __jakt_match_value.else_block;
parser::ParsedBlock const& remaining_code = __jakt_match_value.remaining_code;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_guard(expr,else_block,remaining_code,scope_id,safety_mode,span)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_unary_negate(NonnullRefPtr<typename types::CheckedExpression> const expr,utility::Span const span,types::TypeId const type_id) {
{
if (((!(((((*this).program))->is_integer(type_id)))) || ((((*this).program))->is_signed(type_id)))){
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,type_id)));
}
types::TypeId const flipped_sign_type = TRY((((((*this).get_type(type_id)))->flip_signedness())));
types::CheckedNumericConstant const constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedNumericConstant, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NumericConstant>();types::CheckedNumericConstant const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(val);
};/*case end*/
default: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,type_id)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::NumberConstant const number = (((constant).number_constant()).value());
size_t const raw_number = TRY((((number).to_usize())));
size_t const max_signed = (infallible_integer_cast<size_t>((((TRY((types::Type::template __jakt_create<typename types::Type::I64>())))->max()))));
i64 negated_number = static_cast<i64>(0LL);
if ((raw_number == (JaktInternal::checked_add<size_t>(max_signed,static_cast<size_t>(1ULL))))){
(negated_number = ((TRY((types::Type::template __jakt_create<typename types::Type::I64>())))->min()));
}
if ((raw_number <= max_signed)){
(negated_number = (JaktInternal::checked_sub<i64>(static_cast<i64>(0LL),(infallible_integer_cast<i64>((raw_number))))));
}
types::NumberConstant const negated_number_constant =  types::NumberConstant { typename types::NumberConstant::Signed((infallible_integer_cast<i64>((negated_number)))) } ;
if (((raw_number > (JaktInternal::checked_add<size_t>(max_signed,static_cast<size_t>(1ULL)))) || (!(TRY((((negated_number_constant).can_fit_number(flipped_sign_type,((*this).program))))))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Negative literal -{} too small for type ‘{}’"sv)),raw_number,TRY((((*this).type_name(flipped_sign_type,false))))))),span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(expr, types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,type_id)));
}
types::CheckedNumericConstant const new_constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedNumericConstant, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(flipped_sign_type));
switch(__jakt_match_variant.index()) {
case 6: {
return JaktInternal::ExplicitValue( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8((infallible_integer_cast<i8>((negated_number)))) } );
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16((infallible_integer_cast<i16>((negated_number)))) } );
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((negated_number)))) } );
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I64((infallible_integer_cast<i64>((negated_number)))) } );
};/*case end*/
default: {
{
utility::panic(TRY(DeprecatedString::from_utf8("Unreachable"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>(new_constant,span,type_id))), types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } ,span,flipped_sign_type)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_function(parser::ParsedFunction const parsed_function,types::ScopeId const parent_scope_id) {
{
bool const in_comptime_function_call = ((*this).in_comptime_function_call);
ScopeGuard __jakt_var_430([&] {
(((*this).in_comptime_function_call) = in_comptime_function_call);
});
(((*this).in_comptime_function_call) = ((parsed_function).is_comptime));
if (((!(((((parsed_function).generic_parameters)).is_empty()))) && (!(((parsed_function).must_instantiate))))){
return {};
}
JaktInternal::Optional<types::FunctionId> const function_id = TRY((((*this).find_function_matching_signature_in_scope(parent_scope_id,parsed_function))));
if (((function_id).has_value())){
(((*this).current_function_id) = (function_id.value()));
if ((((parsed_function).name) == TRY(DeprecatedString::from_utf8("main"sv)))){
TRY((((*this).typecheck_jakt_main(parsed_function,parent_scope_id))));
}
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function((function_id.value())));
types::ScopeId const function_scope_id = ((checked_function)->function_scope_id);
parser::FunctionLinkage const function_linkage = ((checked_function)->linkage);
NonnullRefPtr<types::Module> module = ((*this).current_module());
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((param).variable);
types::VarId const var_id = TRY((((module)->add_variable(variable))));
TRY((((*this).add_var_to_scope(function_scope_id,((variable)->name),var_id,((variable)->definition_span)))));
}

}
}

types::TypeId function_return_type_id = TRY((((*this).typecheck_typename(((parsed_function).return_type),function_scope_id,JaktInternal::OptionalNone()))));
if (((!(((parsed_function).is_fat_arrow))) && (((((parsed_function).return_type))->index() == 13 /* Empty */) && (((parsed_function).name) != TRY(DeprecatedString::from_utf8("main"sv)))))){
(function_return_type_id = types::void_type_id());
}
if (((function_return_type_id).equals(types::never_type_id()))){
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(function_scope_id))));
(((scope)->can_throw) = true);
}
types::CheckedBlock const block = TRY((((*this).typecheck_block(((parsed_function).block),function_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
if (((((block).yielded_type)).has_value())){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Functions are not allowed to yield values"sv)),(((((parsed_function).block)).find_yield_span()).value()),TRY(DeprecatedString::from_utf8("You might want to return instead"sv)),(((((parsed_function).block)).find_yield_keyword_span()).value())))));
}
types::TypeId const return_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId,ErrorOr<void>>{
auto __jakt_enum_value = (((function_return_type_id).equals(types::unknown_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((*this).infer_function_return_type(block)));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).resolve_type_var(function_return_type_id,function_scope_id)))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((!(((function_linkage).index() == 1 /* External */))) && ((!(((return_type_id).equals(types::void_type_id())))) && (!(((((block).control_flow)).always_transfers_control())))))){
if ((((return_type_id).equals(types::never_type_id())) && (!(((((block).control_flow)).never_returns()))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Control reaches end of never-returning function"sv)),((parsed_function).name_span)))));
}
else if ((!(((((block).control_flow)).never_returns())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Control reaches end of non-void function"sv)),((parsed_function).name_span)))));
}
}
(((checked_function)->block) = block);
(((checked_function)->return_type_id) = return_type_id);
(((*this).current_function_id) = JaktInternal::OptionalNone());
}
else {
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("Previously defined function {} not found in scope {}"sv)),((parsed_function).name),parent_scope_id)))))));
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_declarations(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
JaktInternal::DynamicArray<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_declarations(child_namespace,child_namespace_scope_id,comptime_pass,generic_pass))));
}

}
}

if (((!(comptime_pass)) && (!(generic_pass)))){
{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find struct that has been previous added"sv))))));
}
TRY((((*this).typecheck_struct(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find struct that has been previous added"sv))))));
}
TRY((((*this).typecheck_struct(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find enum that has been previous added"sv))))));
}
TRY((((*this).typecheck_enum(record,(enum_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find enum that has been previous added"sv))))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

}
{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((parsed_namespace).functions)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction fun = (_magic_value.value());
{
if (((((fun).is_comptime) == comptime_pass) && (generic_pass == (!(((((fun).generic_parameters)).is_empty())))))){
TRY((((*this).typecheck_function(fun,scope_id))));
}
}

}
}

if (((!(comptime_pass)) && (!(generic_pass)))){
{
JaktInternal::ArrayIterator<parser::ParsedExternalTraitImplementation> _magic = ((((parsed_namespace).external_trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedExternalTraitImplementation> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedExternalTraitImplementation implementation = (_magic_value.value());
{
types::TypeId const for_type = TRY((((*this).typecheck_typename(((implementation).for_type),scope_id,JaktInternal::OptionalNone()))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
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
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((TRY((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))) == TRY(DeprecatedString::from_utf8("this"sv)))){
TRY((((*this).typecheck_method(((method).parsed_function), types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id) } ))));
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
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((TRY((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))) == TRY(DeprecatedString::from_utf8("this"sv)))){
TRY((((*this).typecheck_method(((method).parsed_function), types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id) } ))));
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
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((TRY((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))) == TRY(DeprecatedString::from_utf8("this"sv)))){
TRY((((*this).typecheck_method(((method).parsed_function), types::StructLikeId { typename types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id) } ))));
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
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
if ((TRY((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))) == TRY(DeprecatedString::from_utf8("this"sv)))){
TRY((((*this).typecheck_method(((method).parsed_function), types::StructLikeId { typename types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id) } ))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

}
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_constructor(parser::ParsedRecord const parsed_record,types::StructId const struct_id,types::ScopeId const scope_id) {
{
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = struct_type_id);
ScopeGuard __jakt_var_431([&] {
(((*this).self_type_id) = old_self_type_id);
});
types::CheckedStruct const struct_ = ((*this).get_struct(struct_id));
JaktInternal::Optional<JaktInternal::DynamicArray<types::FunctionId>> const constructor_ids = TRY((((*this).find_functions_with_name_in_scope(((struct_).scope_id),((parsed_record).name)))));
if (((constructor_ids).has_value())){
if ((((((parsed_record).record_type)).index() == 1 /* Class */) && ((((parsed_record).definition_linkage)).index() == 1 /* External */))){
{
JaktInternal::ArrayIterator<types::FunctionId> _magic = (((constructor_ids.value())).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId constructor_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> func = ((*this).get_function(constructor_id));
(((func)->linkage) =  parser::FunctionLinkage { typename parser::FunctionLinkage::External() } );
}

}
}

}
}
else if ((!(((((parsed_record).definition_linkage)).index() == 1 /* External */)))){
bool const constructor_can_throw = ((((parsed_record).record_type)).index() == 1 /* Class */);
types::ScopeId const function_scope_id = TRY((((*this).create_scope(((struct_).scope_id),constructor_can_throw,TRY((__jakt_format((StringView::from_string_literal("generated-constructor({})"sv)),((parsed_record).name)))),true))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,constructor_can_throw,TRY((__jakt_format((StringView::from_string_literal("generated-constructor-block({})"sv)),((parsed_record).name)))),true))));
NonnullRefPtr<types::CheckedFunction> checked_constructor = TRY((types::CheckedFunction::__jakt_create(((parsed_record).name),((parsed_record).name_span), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,struct_type_id,JaktInternal::OptionalNone(),(TRY((DynamicArray<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::__jakt_create(function_scope_id,(TRY((DynamicArray<types::CheckedParameter>::create_with({})))),(TRY((DynamicArray<types::FunctionGenericParameter>::create_with({})))),(TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),constructor_can_throw, parser::FunctionType { typename parser::FunctionType::ImplicitConstructor() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,function_scope_id,struct_id,true,JaktInternal::OptionalNone(),false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),((parsed_record).external_name),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const function_id = TRY((((module)->add_function(checked_constructor))));
JaktInternal::DynamicArray<types::StructId> const inheritance_chain = TRY((((*this).struct_inheritance_chain(struct_id))));
NonnullRefPtr<types::CheckedFunction> func = (((((module)->functions)).last()).value());
{
JaktInternal::ArrayIterator<types::StructId> _magic = ((inheritance_chain).iterator());
for (;;){
JaktInternal::Optional<types::StructId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::StructId field_struct_id = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((((*this).get_struct(field_struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((*this).get_variable(((field).variable_id)));
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> default_value = ((field).default_value);
if (((!(((default_value).has_value()))) && ((((field).default_value_expression)).has_value()))){
(((field).default_value) = TRY((((*this).typecheck_expression((((field).default_value_expression).value()),block_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,((variable)->type_id))))));
}
TRY((((func)->add_param(types::CheckedParameter(true,variable,((field).default_value))))));
}

}
}

}

}
}

TRY((((*this).add_function_to_scope(((struct_).scope_id),((parsed_record).name),(TRY((DynamicArray<types::FunctionId>::create_with({function_id})))),((parsed_record).name_span)))));
}
(((*this).current_struct_type_id) = JaktInternal::OptionalNone());
}
return {};
}

ErrorOr<types::TypeId> typechecker::Typechecker::resolve_type_var(types::TypeId const type_var_type_id,types::ScopeId const scope_id) const {
{
types::TypeId current_type_id = type_var_type_id;
for (;;){
(current_type_id = TRY((((((*this).generic_inferences)).map(current_type_id)))));
NonnullRefPtr<typename types::Type> const type_var_type = ((*this).get_type(current_type_id));
if (((type_var_type)->index() == 18 /* TypeVariable */)){
DeprecatedString const type_name = ((type_var_type)->get<types::Type::TypeVariable>()).name;
JaktInternal::Optional<types::TypeId> const maybe_found_type_id = TRY((((*this).find_type_in_scope(scope_id,type_name))));
if (((maybe_found_type_id).has_value())){
types::TypeId const found_type_id = ((maybe_found_type_id).value());
if (((found_type_id).equals(current_type_id))){
return current_type_id;
}
(current_type_id = found_type_id);
}
else {
return current_type_id;
}

}
else {
return current_type_id;
}

}
return current_type_id;
}
}

ErrorOr<void> typechecker::Typechecker::check_type_argument_requirements(types::TypeId const generic_argument,JaktInternal::DynamicArray<types::TraitId> const constraints,utility::Span const arg_span) {
{
if ((!(((constraints).is_empty())))){
JaktInternal::Tuple<JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>,utility::Span> const implemented_traits_decl_span_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>,utility::Span>, ErrorOr<void>>{
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot use ‘{}’ here as only enums, structs and classes can implement the required traits"sv)),TRY((((*this).type_name(generic_argument,false))))))),arg_span))));
{
return ErrorOr<void>{};
}

abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const implemented_traits = ((implemented_traits_decl_span_).template get<0>());
utility::Span const decl_span = ((implemented_traits_decl_span_).template get<1>());

{
JaktInternal::ArrayIterator<types::TraitId> _magic = ((constraints).iterator());
for (;;){
JaktInternal::Optional<types::TraitId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TraitId constraint = (_magic_value.value());
{
DeprecatedString const trait_name = ((((((*this).program))->get_trait(constraint)))->name);
JaktInternal::Optional<JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const implemented_trait = ((implemented_traits).get(trait_name));
if (((!(((implemented_trait).has_value()))) || (!((((((implemented_trait.value())).template get<0>())).equals(constraint)))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Cannot use ‘{}’ here as it doesn't implement the trait ‘{}’"sv)),TRY((((*this).type_name(generic_argument,false)))),trait_name))),arg_span,TRY(DeprecatedString::from_utf8("Consider implementing the required trait for this type"sv)),decl_span))));
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

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<types::TypeId>>> typechecker::Typechecker::get_type_ids_from_type_hint_if_struct_ids_match(JaktInternal::Optional<types::TypeId> const type_hint,types::StructId const expected_struct_id) const {
{
if ((!(((type_hint).has_value())))){
return JaktInternal::OptionalNone();
}
if (((TRY((((*this).unwrap_type_from_optional_if_needed(((*this).get_type((type_hint.value()))))))))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((TRY((((*this).unwrap_type_from_optional_if_needed(((*this).get_type((type_hint.value()))))))))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((TRY((((*this).unwrap_type_from_optional_if_needed(((*this).get_type((type_hint.value()))))))))->get<types::Type::GenericInstance>()).args;
if (((id).equals(expected_struct_id))){
return args;
}
}
return JaktInternal::OptionalNone();
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_generic_arguments_method_call(NonnullRefPtr<typename types::CheckedExpression> const checked_expr,parser::ParsedCall const call,types::ScopeId const scope_id,utility::Span const span,bool const is_optional,types::SafetyMode const safety_mode) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>> checked_args = (TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
TRY((((checked_args).ensure_capacity(((((call).args)).size())))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> name_____expr__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> const jakt__name_____expr__ = name_____expr__;
DeprecatedString const name = ((jakt__name_____expr__).template get<0>());
utility::Span const _ = ((jakt__name_____expr__).template get<1>());
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((jakt__name_____expr__).template get<2>());

NonnullRefPtr<typename types::CheckedExpression> const checked_arg_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((checked_args).push((Tuple{name, checked_arg_expr})))));
}

}
}

JaktInternal::DynamicArray<types::TypeId> checked_type_args = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedType>> _magic = ((((call).type_args)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedType> type_arg = (_magic_value.value());
{
TRY((((checked_type_args).push(TRY((((*this).typecheck_typename(type_arg,scope_id,JaktInternal::OptionalNone()))))))));
}

}
}

return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::MethodCall>(checked_expr,types::CheckedCall((TRY((DynamicArray<types::ResolvedNamespace>::create_with({})))),((call).name),checked_args,checked_type_args,JaktInternal::OptionalNone(),types::unknown_type_id(),false,JaktInternal::OptionalNone()),span,is_optional,types::unknown_type_id())));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_loop(parser::ParsedBlock const parsed_block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(parsed_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("A ‘loop’ block is not allowed to yield values"sv)),(((parsed_block).find_yield_span()).value())))));
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Loop>(checked_block,span)));
}
}

ErrorOr<NonnullRefPtr<types::Scope>> typechecker::Typechecker::get_scope(types::ScopeId const id) const {
{
return TRY((((((*this).program))->get_scope(id))));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_indexed_tuple(NonnullRefPtr<typename parser::ParsedExpression> const expr,size_t const index,types::ScopeId const scope_id,bool const is_optional,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Tuple"sv))))));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
types::TypeId expr_type_id = types::unknown_type_id();
if (((((*this).get_type(((checked_expr)->type()))))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(((checked_expr)->type()))))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(((checked_expr)->type()))))->get<types::Type::GenericInstance>()).args;
if (((id).equals(tuple_struct_id))){
if (is_optional){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Optional chaining is not allowed on a non-optional tuple type"sv)),span))));
}
if ((index >= ((args).size()))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Tuple index past the end of the tuple"sv)),span))));
}
else {
(expr_type_id = ((args)[index]));
}

}
else if ((is_optional && ((id).equals(optional_struct_id)))){
types::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((((*this).get_type(inner_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(inner_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(inner_type_id)))->get<types::Type::GenericInstance>()).args;
if (((id).equals(tuple_struct_id))){
if ((index >= ((args).size()))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Optional-chained tuple index past the end of the tuple"sv)),span))));
}
else {
(expr_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({((args)[index])}))))))))))));
}

}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Optional-chained tuple index used on non-tuple value"sv)),span))));
}

}
}
else if (is_optional){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Optional-chained tuple index used on non-tuple value"sv)),span))));
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Tuple index used on non-tuple value"sv)),span))));
}

return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedTuple>(checked_expr,index,span,is_optional,expr_type_id)));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_while(NonnullRefPtr<typename parser::ParsedExpression> const condition,parser::ParsedBlock const block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<typename types::CheckedExpression> const checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Condition must be a boolean expression"sv)),((condition)->span())))));
}
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("A ‘while’ block is not allowed to yield values"sv)),(((block).find_yield_span()).value())))));
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::While>(checked_condition,checked_block,span)));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::prelude_struct_type_named(DeprecatedString const name) {
{
types::StructId const struct_id = TRY((((*this).find_struct_in_prelude(name))));
NonnullRefPtr<typename types::Type> const type = TRY((types::Type::template __jakt_create<typename types::Type::Struct>(struct_id)));
return TRY((((*this).find_or_add_type_id(type))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_alias(parser::ParsedAlias const alias,types::ScopeId const scope_id,typechecker::ImportRestrictions const allow) {
{
parser::ParsedName const aliased_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::ParsedName,ErrorOr<void>>{
auto __jakt_enum_value = (((((alias).alias_name)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((((alias).alias_name).value()));
}
else {
return JaktInternal::ExplicitValue(({ Optional<parser::ParsedName> __jakt_var_432; {
parser::ParsedNameWithGenericParameters const name = (((((alias).target)).last()).value());
if ((!(((((name).generic_parameters)).is_empty())))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Cannot alias a generic instance of a type to the type itself"sv))))),((name).name_span),TRY((__jakt_format((StringView::from_string_literal("Add an alias name here: 'as <name>'"sv))))),((name).name_span)))));
}
__jakt_var_432 = parser::ParsedName(((name).name),((name).name_span)); goto __jakt_label_401;

}
__jakt_label_401:; __jakt_var_432.release_value(); }));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::ScopeId resolved_scope_id = scope_id;
JaktInternal::DynamicArray<types::ResolvedNamespace> alias_path = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>((JaktInternal::checked_sub<size_t>(((((alias).target)).size()),static_cast<size_t>(1ULL))))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> const namespace_ = TRY((((*this).find_namespace_in_scope(resolved_scope_id,((((((alias).target))[i])).name),false))));
if ((!(((namespace_).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unknown namespace '{}'"sv)),((((((alias).target))[i])).name)))),((((((alias).target))[i])).name_span)))));
return {};
}
(resolved_scope_id = (((namespace_.value())).template get<0>()));
TRY((((alias_path).push(types::ResolvedNamespace(((((((alias).target))[i])).name),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))));
}

}
}

NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
types::ScopeId const alias_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId,ErrorOr<void>>{
auto __jakt_enum_value = (((((scope)->alias_scope)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((((scope)->alias_scope).value()));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_433; {
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((__jakt_format((StringView::from_string_literal("alias-scope({})"sv)),((scope)->debug_name)))),false))));
NonnullRefPtr<types::Scope> new_scope = TRY((((*this).get_scope(new_scope_id))));
(((new_scope)->alias_path) = alias_path);
TRY((((((TRY((((*this).get_scope(scope_id)))))->children)).push(new_scope_id))));
__jakt_var_433 = new_scope_id; goto __jakt_label_402;

}
__jakt_label_402:; __jakt_var_433.release_value(); }));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).find_and_import_name_from_scope((((((((alias).target)).last()).value())).name),(((((((alias).target)).last()).value())).name_span),((aliased_name).name),((aliased_name).span),resolved_scope_id,alias_scope_id,allow))));
}
return {};
}

ErrorOr<types::CheckedUnaryOperator> typechecker::Typechecker::typecheck_is_enum_variant(NonnullRefPtr<typename types::CheckedExpression> const checked_expr,NonnullRefPtr<typename parser::ParsedType> const inner,JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const bindings,types::ScopeId const scope_id) {
{
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::TypeId const type_id = TRY((((*this).typecheck_typename(inner,scope_id,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
types::CheckedUnaryOperator checked_op =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Is(type_id) } ;
types::TypeId const expr_type_id = ((checked_expr)->type());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::CheckedUnaryOperator>>{
auto&& __jakt_match_variant = *inner;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::NamespacedName>();DeprecatedString const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (((((*this).get_type(expr_type_id)))->index() == 24 /* Enum */)){
types::EnumId const enum_id = ((((*this).get_type(expr_type_id)))->get<types::Type::Enum>()).value;
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::Optional<types::CheckedEnumVariant> const variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedEnumVariantBinding>> const checked_enum_variant_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),bindings,span))));
(checked_op =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::IsEnumVariant((variant.value()),(checked_enum_variant_bindings.value()),expr_type_id) } );
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant {} does not exist on {}"sv)),variant_name,TRY((((*this).type_name(type_id,false))))))),span))));
return checked_op;
}

}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unknown type or invalid type name: {}"sv)),variant_name))),span))));
return checked_op;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();DeprecatedString const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (((((*this).get_type(expr_type_id)))->index() == 24 /* Enum */)){
types::EnumId const enum_id = ((((*this).get_type(expr_type_id)))->get<types::Type::Enum>()).value;
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::Optional<types::CheckedEnumVariant> const variant = TRY((((*this).get_enum_variant(enum_,variant_name))));
if (((variant).has_value())){
JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedEnumVariantBinding>> const checked_enum_variant_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),bindings,span))));
(checked_op =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::IsEnumVariant((variant.value()),(checked_enum_variant_bindings.value()),expr_type_id) } );
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant {} does not exist on {}"sv)),variant_name,TRY((((*this).type_name(type_id,false))))))),span))));
return checked_op;
}

}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unknown type or invalid type name: {}"sv)),variant_name))),span))));
return checked_op;
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return checked_op;
}
}

ErrorOr<bool> typechecker::Typechecker::add_var_to_scope(types::ScopeId const scope_id,DeprecatedString const name,types::VarId const var_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::VarId> const existing_var = ((((scope)->vars)).get(name));
if (((existing_var).has_value())){
NonnullRefPtr<types::CheckedVariable> const variable_ = ((*this).get_variable((existing_var.value())));
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Redefinition of variable ‘{}’"sv)),name))),span,TRY(DeprecatedString::from_utf8("previous definition here"sv)),((variable_)->definition_span)))));
}
TRY((((((scope)->vars)).set(name,var_id))));
TRY((((*this).set_owner_scope_if_needed(scope_id,var_id))));
return true;
}
}

ErrorOr<bool> typechecker::Typechecker::add_comptime_binding_to_scope(types::ScopeId const scope_id,DeprecatedString const name,types::Value const value,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::Value> const existing_binding = ((((scope)->comptime_bindings)).get(name));
if (((existing_binding).has_value())){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Redefinition of comptime variable ‘{}’"sv)),name))),span,TRY(DeprecatedString::from_utf8("previous definition here"sv)),(((existing_binding.value())).span)))));
}
TRY((((((scope)->comptime_bindings)).set(name,value))));
return true;
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_match(NonnullRefPtr<typename parser::ParsedExpression> const expr,JaktInternal::DynamicArray<parser::ParsedMatchCase> const cases,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const subject_type_id = ((checked_expr)->type());
NonnullRefPtr<typename types::Type> const type_to_match_on = ((*this).get_type(subject_type_id));
JaktInternal::DynamicArray<types::CheckedMatchCase> checked_cases = (TRY((DynamicArray<types::CheckedMatchCase>::create_with({}))));
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_434([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
JaktInternal::Optional<types::TypeId> final_result_type = JaktInternal::OptionalNone();
if ((((type_hint).has_value()) && ((!((((type_hint.value())).equals(types::unknown_type_id())))) && (!(((((*this).get_type((type_hint.value()))))->index() == 18 /* TypeVariable */)))))){
(final_result_type = type_hint);
}
if (((type_to_match_on)->index() == 20 /* GenericEnumInstance */)){
types::EnumId const id = ((type_to_match_on)->get<types::Type::GenericEnumInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((type_to_match_on)->get<types::Type::GenericEnumInstance>()).args;
types::CheckedEnum const enum_ = ((*this).get_enum(id));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
DeprecatedString const generic = TRY((((((((((enum_).generic_parameters))[i])).type_id)).to_string())));
DeprecatedString const argument_type = TRY((((((args)[i])).to_string())));
if ((generic != argument_type)){
TRY((((((*this).generic_inferences)).set(generic,argument_type))));
}
}

}
}

}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
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
JaktInternal::Set<DeprecatedString> covered_variants = (TRY((Set<DeprecatedString>::create_with_values({}))));
size_t const case_count = ((cases).size());
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<parser::ParsedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchCase case_ = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<parser::ParsedMatchPattern> _magic = ((((case_).patterns)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchPattern> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchPattern pattern = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::EnumVariant>();JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> variant_names_ = variant_names;
if ((((variant_names_).size()) == static_cast<size_t>(1ULL))){
JaktInternal::Tuple<DeprecatedString,utility::Span> const temp = ((variant_names_)[static_cast<i64>(0LL)]);
(variant_names_ = (TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>::create_with({(Tuple{((enum_).name), ((((variant_names_)[static_cast<i64>(0LL)])).template get<1>())}), temp})))));
}
if (((variant_names_).is_empty())){
return JaktInternal::LoopContinue{};
}
if ((((((variant_names_)[static_cast<i64>(0LL)])).template get<0>()) != ((enum_).name))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Match case '{}' does not match enum '{}'"sv)),((((variant_names_)[static_cast<i64>(0LL)])).template get<0>()),((enum_).name)))),((((variant_names_)[static_cast<i64>(0LL)])).template get<1>())))));
return JaktInternal::LoopContinue{};
}
size_t i = static_cast<size_t>(0ULL);
JaktInternal::Optional<types::CheckedEnumVariant> matched_variant = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> variant_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant v = (_magic_value.value());
{
if ((((v).name()) == ((((variant_names_)[static_cast<i64>(1LL)])).template get<0>()))){
(matched_variant = v);
(variant_index = i);
}
((i++));
}

}
}

if ((!(((matched_variant).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum '{}' does not contain a variant named '{}'"sv)),((enum_).name),((((variant_names_)[static_cast<i64>(1LL)])).template get<0>())))),((case_).marker_span)))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Match>(checked_expr,(TRY((DynamicArray<types::CheckedMatchCase>::create_with({})))),span,types::unknown_type_id(),false)));
}
JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> const covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,(variant_index.value()),final_result_type,(matched_variant.value()),variant_arguments,((pattern).defaults()),arguments_span,scope_id,safety_mode))));
JaktInternal::Optional<DeprecatedString> const covered_name = ((covered_name_checked_match_case_result_type_).template get<0>());
types::CheckedMatchCase const checked_match_case = ((covered_name_checked_match_case_result_type_).template get<1>());
JaktInternal::Optional<types::TypeId> const result_type = ((covered_name_checked_match_case_result_type_).template get<2>());

if (((covered_name).has_value())){
TRY((((covered_variants).add((covered_name.value())))));
}
(final_result_type = result_type);
TRY((((checked_cases).push(checked_match_case))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::CatchAll>();JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if ((current_case_index != (JaktInternal::checked_sub<size_t>(case_count,static_cast<size_t>(1ULL))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Match else case is only allowed as the last case"sv)),((case_).marker_span)))));
}
if (seen_catch_all){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Multiple catch-all cases in match are not allowed"sv)),((case_).marker_span)))));
}
else {
(seen_catch_all = true);
}

if ((((variant_arguments).size()) > static_cast<size_t>(0ULL))){
size_t variant_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if ((!(((covered_variants).contains(((variant).name())))))){
(expanded_catch_all = true);
JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> const covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,variant_index,final_result_type,variant,variant_arguments,((pattern).defaults()),arguments_span,scope_id,safety_mode))));
JaktInternal::Optional<DeprecatedString> const covered_name = ((covered_name_checked_match_case_result_type_).template get<0>());
types::CheckedMatchCase const checked_match_case = ((covered_name_checked_match_case_result_type_).template get<1>());
JaktInternal::Optional<types::TypeId> const result_type = ((covered_name_checked_match_case_result_type_).template get<2>());

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
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY(DeprecatedString::from_utf8("catch-all"sv)),true))));
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,parser::ParsedPatternDefault> _magic = ((((pattern).defaults())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> ___default___ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
DeprecatedString const _ = ((jakt_____default___).template get<0>());
parser::ParsedPatternDefault const default_ = ((jakt_____default___).template get<1>());

NonnullRefPtr<typename types::CheckedStatement> const checked_var_decl = TRY((((*this).typecheck_var_decl(((default_).variable),((default_).value),new_scope_id,safety_mode,((((default_).variable)).span)))));
TRY((((defaults).push(checked_var_decl))));
}

}
}

JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).template get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).template get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll(defaults,false,checked_body,((case_).marker_span)) } ;
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

((current_case_index++));
}

}
}

JaktInternal::DynamicArray<DeprecatedString> enum_variant_names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
JaktInternal::DynamicArray<DeprecatedString> missing_variants = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
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
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((enum_variant_names).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString variant = (_magic_value.value());
{
if ((!(((covered_variants).contains(variant))))){
TRY((((missing_variants).push(variant))));
}
}

}
}

if ((((missing_variants).size()) > static_cast<size_t>(0ULL))){
if ((!(seen_catch_all))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Match expression is not exhaustive, missing variants are: {}"sv)),TRY((utility::join(missing_variants,TRY(DeprecatedString::from_utf8(", "sv)))))))),span))));
}
}
else if ((seen_catch_all && (!(expanded_catch_all)))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("All variants are covered, but an irrefutable pattern is also present"sv)),span))));
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
JaktInternal::Set<DeprecatedString> covered_variants = (TRY((Set<DeprecatedString>::create_with_values({}))));
size_t const case_count = ((cases).size());
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<parser::ParsedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchCase case_ = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<parser::ParsedMatchPattern> _magic = ((((case_).patterns)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchPattern> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchPattern pattern = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::EnumVariant>();JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> variant_names_ = variant_names;
if ((((variant_names_).size()) == static_cast<size_t>(1ULL))){
JaktInternal::Tuple<DeprecatedString,utility::Span> const temp = ((variant_names_)[static_cast<i64>(0LL)]);
(variant_names_ = (TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>::create_with({(Tuple{((enum_).name), ((((variant_names_)[static_cast<i64>(0LL)])).template get<1>())}), temp})))));
}
if (((variant_names_).is_empty())){
return JaktInternal::LoopContinue{};
}
if ((((((variant_names_)[static_cast<i64>(0LL)])).template get<0>()) != ((enum_).name))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Match case '{}' does not match enum '{}'"sv)),((((variant_names_)[static_cast<i64>(0LL)])).template get<0>()),((enum_).name)))),((((variant_names_)[static_cast<i64>(0LL)])).template get<1>())))));
return JaktInternal::LoopContinue{};
}
size_t i = static_cast<size_t>(0ULL);
JaktInternal::Optional<types::CheckedEnumVariant> matched_variant = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> variant_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant v = (_magic_value.value());
{
if ((((v).name()) == ((((variant_names_)[static_cast<i64>(1LL)])).template get<0>()))){
(matched_variant = v);
(variant_index = i);
}
((i++));
}

}
}

if ((!(((matched_variant).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum '{}' does not contain a variant named '{}'"sv)),((enum_).name),((((variant_names_)[static_cast<i64>(1LL)])).template get<0>())))),((case_).marker_span)))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Match>(checked_expr,(TRY((DynamicArray<types::CheckedMatchCase>::create_with({})))),span,types::unknown_type_id(),false)));
}
JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> const covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,(variant_index.value()),final_result_type,(matched_variant.value()),variant_arguments,((pattern).defaults()),arguments_span,scope_id,safety_mode))));
JaktInternal::Optional<DeprecatedString> const covered_name = ((covered_name_checked_match_case_result_type_).template get<0>());
types::CheckedMatchCase const checked_match_case = ((covered_name_checked_match_case_result_type_).template get<1>());
JaktInternal::Optional<types::TypeId> const result_type = ((covered_name_checked_match_case_result_type_).template get<2>());

if (((covered_name).has_value())){
TRY((((covered_variants).add((covered_name.value())))));
}
(final_result_type = result_type);
TRY((((checked_cases).push(checked_match_case))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::CatchAll>();JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if ((current_case_index != (JaktInternal::checked_sub<size_t>(case_count,static_cast<size_t>(1ULL))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Match else case is only allowed as the last case"sv)),((case_).marker_span)))));
}
if (seen_catch_all){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Multiple catch-all cases in match are not allowed"sv)),((case_).marker_span)))));
}
else {
(seen_catch_all = true);
}

if ((((variant_arguments).size()) > static_cast<size_t>(0ULL))){
size_t variant_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if ((!(((covered_variants).contains(((variant).name())))))){
(expanded_catch_all = true);
JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>> const covered_name_checked_match_case_result_type_ = TRY((((*this).typecheck_match_variant(case_,subject_type_id,variant_index,final_result_type,variant,variant_arguments,((pattern).defaults()),arguments_span,scope_id,safety_mode))));
JaktInternal::Optional<DeprecatedString> const covered_name = ((covered_name_checked_match_case_result_type_).template get<0>());
types::CheckedMatchCase const checked_match_case = ((covered_name_checked_match_case_result_type_).template get<1>());
JaktInternal::Optional<types::TypeId> const result_type = ((covered_name_checked_match_case_result_type_).template get<2>());

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
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY(DeprecatedString::from_utf8("catch-all"sv)),true))));
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,parser::ParsedPatternDefault> _magic = ((((pattern).defaults())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> ___default___ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
DeprecatedString const _ = ((jakt_____default___).template get<0>());
parser::ParsedPatternDefault const default_ = ((jakt_____default___).template get<1>());

NonnullRefPtr<typename types::CheckedStatement> const checked_var_decl = TRY((((*this).typecheck_var_decl(((default_).variable),((default_).value),new_scope_id,safety_mode,((((default_).variable)).span)))));
TRY((((defaults).push(checked_var_decl))));
}

}
}

JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).template get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).template get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll(defaults,false,checked_body,((case_).marker_span)) } ;
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

((current_case_index++));
}

}
}

JaktInternal::DynamicArray<DeprecatedString> enum_variant_names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
JaktInternal::DynamicArray<DeprecatedString> missing_variants = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
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
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((enum_variant_names).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString variant = (_magic_value.value());
{
if ((!(((covered_variants).contains(variant))))){
TRY((((missing_variants).push(variant))));
}
}

}
}

if ((((missing_variants).size()) > static_cast<size_t>(0ULL))){
if ((!(seen_catch_all))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Match expression is not exhaustive, missing variants are: {}"sv)),TRY((utility::join(missing_variants,TRY(DeprecatedString::from_utf8(", "sv)))))))),span))));
}
}
else if ((seen_catch_all && (!(expanded_catch_all)))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("All variants are covered, but an irrefutable pattern is also present"sv)),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
{
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Can't match on 'void' type"sv)),((checked_expr)->span())))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
bool const is_boolean_match = ((type_to_match_on)->index() == 1 /* Bool */);
bool seen_true = false;
bool seen_false = false;
JaktInternal::Optional<utility::Span> catch_all_span = JaktInternal::OptionalNone();
bool is_enum_match = false;
bool is_value_match = false;
bool seen_catch_all = false;
bool all_variants_constant = true;
size_t const case_count = ((cases).size());
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<parser::ParsedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchCase case_ = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<parser::ParsedMatchPattern> _magic = ((((case_).patterns)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchPattern> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchPattern pattern = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::EnumVariant>();JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if (is_value_match){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot have an enum match case in a match expression containing value matches"sv)),((case_).marker_span)))));
}
if ((((variant_names).size()) == static_cast<size_t>(0ULL))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("typecheck_match - else - EnumVariant - variant_names.size() == 0"sv))))));
}
(is_enum_match = true);
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((__jakt_format((StringView::from_string_literal("catch-enum-variant({})"sv)),variant_names))),true))));
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,parser::ParsedPatternDefault> _magic = ((((pattern).defaults())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> ___default___ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
DeprecatedString const _ = ((jakt_____default___).template get<0>());
parser::ParsedPatternDefault const default_ = ((jakt_____default___).template get<1>());

NonnullRefPtr<typename types::CheckedStatement> const checked_var_decl = TRY((((*this).typecheck_var_decl(((default_).variable),((default_).value),new_scope_id,safety_mode,((((default_).variable)).span)))));
TRY((((defaults).push(checked_var_decl))));
}

}
}

JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).template get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).template get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::EnumVariant(defaults,(((((variant_names).last()).value())).template get<0>()),variant_arguments,subject_type_id,static_cast<size_t>(0ULL),new_scope_id,checked_body,((case_).marker_span)) } ;
TRY((((checked_cases).push(checked_match_case))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedMatchPattern::CatchAll>();JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
{
if ((current_case_index != (JaktInternal::checked_sub<size_t>(case_count,static_cast<size_t>(1ULL))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Match else case is only allowed as the last case"sv)),((case_).marker_span)))));
}
(catch_all_span = ((case_).marker_span));
if (seen_catch_all){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Multiple catch-all cases in match are not allowed"sv)),((case_).marker_span)))));
}
else {
(seen_catch_all = true);
}

if ((((variant_arguments).size()) != static_cast<size_t>(0ULL))){
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = false);
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Bindings aren't allowed in a generic else"sv)),((case_).marker_span)))));
(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
}
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY(DeprecatedString::from_utf8("catch-all"sv)),true))));
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,parser::ParsedPatternDefault> _magic = ((((pattern).defaults())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> ___default___ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
DeprecatedString const _ = ((jakt_____default___).template get<0>());
parser::ParsedPatternDefault const default_ = ((jakt_____default___).template get<1>());

NonnullRefPtr<typename types::CheckedStatement> const checked_var_decl = TRY((((*this).typecheck_var_decl(((default_).variable),((default_).value),new_scope_id,safety_mode,((((default_).variable)).span)))));
TRY((((defaults).push(checked_var_decl))));
}

}
}

JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).template get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).template get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll(defaults,(((variant_arguments).size()) != static_cast<size_t>(0ULL)),checked_body,((case_).marker_span)) } ;
TRY((((checked_cases).push(checked_match_case))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedMatchPattern::Expression>();
NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.value;
{
if (is_enum_match){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot have a value match case in a match expression containing enum matches"sv)),((case_).marker_span)))));
}
(is_value_match = true);
JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings(expr,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),scope_id,span))));
NonnullRefPtr<typename parser::ParsedExpression> const new_condition = ((new_condition_new_then_block_new_else_statement_).template get<0>());
JaktInternal::Optional<parser::ParsedBlock> const new_then_block = ((new_condition_new_then_block_new_else_statement_).template get<1>());
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const new_else_statement = ((new_condition_new_then_block_new_else_statement_).template get<2>());

NonnullRefPtr<typename types::CheckedExpression> const checked_expression = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,static_cast<JaktInternal::Optional<types::TypeId>>(subject_type_id),span))));
if ((is_boolean_match && ((checked_expression)->index() == 0 /* Boolean */))){
bool const val = ((checked_expression)->get<types::CheckedExpression::Boolean>()).val;
if (val){
(seen_true = true);
}
else {
(seen_false = true);
}

}
if ((!(((((checked_expression)->to_number_constant(((*this).program)))).has_value())))){
(all_variants_constant = false);
}
types::TypeId expression_type = ((checked_expression)->type());
if (((checked_expression)->index() == 9 /* Range */)){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const from = ((checked_expression)->get<types::CheckedExpression::Range>()).from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const to = ((checked_expression)->get<types::CheckedExpression::Range>()).to;
if ((((from).has_value()) || ((to).has_value()))){
if (((from).has_value())){
(expression_type = (((from.value()))->type()));
}
else if (((to).has_value())){
(expression_type = (((to.value()))->type()));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("There has to be at least a 'from', or a 'to' in a range expression"sv)),((expr)->span())))));
return JaktInternal::LoopContinue{};
}

}
TRY((((*this).check_types_for_compat(expression_type,subject_type_id,((((*this).generic_inferences))),((case_).marker_span)))));
if ((!(((((pattern).defaults())).is_empty())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Expression patterns cannot have default bindings"sv)),((case_).marker_span)))));
}
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((__jakt_format((StringView::from_string_literal("catch-expression({})"sv)),expr))),true))));
JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).template get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).template get<1>());

(final_result_type = result_type);
types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::Expression((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),checked_expression,checked_body,((case_).marker_span)) } ;
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

((current_case_index++));
}

}
}

if ((is_value_match && (!((seen_catch_all || ((is_boolean_match && seen_true) && seen_false)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Match expression is not exhaustive, a value match must contain an irrefutable 'else' pattern"sv)),span))));
}
if ((is_value_match && (seen_catch_all && (is_boolean_match && (seen_true && seen_false))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("All cases are covered, but an irrefutable pattern is also present"sv)),(catch_all_span.value())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Match>(checked_expr,checked_cases,span,final_result_type.value_or_lazy_evaluated([&] { return types::void_type_id(); }),true)));
}
}

ErrorOr<void> typechecker::Typechecker::map_generic_arguments(types::TypeId const type_id,JaktInternal::DynamicArray<types::TypeId> const args) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
{
types::CheckedStruct const struct_ = ((*this).get_struct(id));
TRY((((((*this).generic_inferences)).set_all(((struct_).generic_parameters),args))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
{
types::CheckedEnum const enum_ = ((*this).get_enum(id));
TRY((((((*this).generic_inferences)).set_all(((enum_).generic_parameters),args))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
{
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait(id));
TRY((((((*this).generic_inferences)).set_all(((trait_)->generic_parameters),args))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_throw(NonnullRefPtr<typename parser::ParsedExpression> const expr,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const error_type_id = TRY((((*this).find_type_in_prelude(TRY(DeprecatedString::from_utf8("Error"sv))))));
if ((!(((((checked_expr)->type())).equals(error_type_id))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("throw expression does not produce an error"sv)),((expr)->span())))));
}
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
if ((!(((scope)->can_throw)))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Throw statement needs to be in a try statement or a function marked as throws"sv)),((expr)->span())))));
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Throw>(checked_expr,span)));
}
}

ErrorOr<void> typechecker::Typechecker::fill_trait_requirements(JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> const names,JaktInternal::DynamicArray<types::TraitId>& trait_requirements,JaktInternal::DynamicArray<types::TypeId>& trait_implementations,types::ScopeId const scope_id) {
{
TRY((((((trait_requirements))).ensure_capacity(((names).size())))));
{
JaktInternal::ArrayIterator<parser::ParsedNameWithGenericParameters> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters name = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> type_id = TRY((((*this).find_type_in_scope(scope_id,((name).name)))));
if (((type_id).has_value())){
if (((((*this).get_type((type_id.value()))))->index() == 26 /* Trait */)){
types::TraitId const trait_id = ((((*this).get_type((type_id.value()))))->get<types::Type::Trait>()).value;
if ((!(((((name).generic_parameters)).is_empty())))){
JaktInternal::DynamicArray<types::TypeId> generic_arguments = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedType>> _magic = ((((name).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedType> argument = (_magic_value.value());
{
TRY((((generic_arguments).push(TRY((((*this).typecheck_typename(argument,scope_id,JaktInternal::OptionalNone()))))))));
}

}
}

NonnullRefPtr<typename types::Type> const final_type = TRY((types::Type::template __jakt_create<typename types::Type::GenericTraitInstance>(trait_id,generic_arguments)));
(type_id = TRY((((*this).find_or_add_type_id(final_type)))));
}
TRY((((((trait_implementations))).push((type_id.value())))));
TRY((((((trait_requirements))).push(trait_id))));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Requirement ‘{}’ is not a trait"sv)),((name).name)))),((name).name_span)))));
continue;
}

}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Couldn't find trait ‘{}’"sv)),((name).name)))),((name).name_span)))));
continue;
}

}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_dictionary(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> const values,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
types::StructId const dictionary_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Dictionary"sv))))));
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> checked_kv_pairs = (TRY((DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
types::TypeId key_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> key_type_span = JaktInternal::OptionalNone();
types::TypeId value_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> value_type_span = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> key_hint = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> value_hint = JaktInternal::OptionalNone();
JaktInternal::Optional<JaktInternal::DynamicArray<types::TypeId>> const type_hint_ids = TRY((((*this).get_type_ids_from_type_hint_if_struct_ids_match(type_hint,dictionary_struct_id))));
if (((type_hint_ids).has_value())){
(key_hint = (((type_hint_ids.value()))[static_cast<i64>(0LL)]));
(value_hint = (((type_hint_ids.value()))[static_cast<i64>(1LL)]));
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>> key__value__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>> const jakt__key__value__ = key__value__;
NonnullRefPtr<typename parser::ParsedExpression> const key = ((jakt__key__value__).template get<0>());
NonnullRefPtr<typename parser::ParsedExpression> const value = ((jakt__key__value__).template get<1>());

NonnullRefPtr<typename types::CheckedExpression> const checked_key = TRY((((*this).typecheck_expression(key,scope_id,safety_mode,key_hint))));
types::TypeId const current_key_type_id = ((checked_key)->type());
NonnullRefPtr<typename types::CheckedExpression> const checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,value_hint))));
types::TypeId const current_value_type_id = ((checked_value)->type());
types::TypeId const VOID_TYPE_ID = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
if ((((key_type_id).equals(types::unknown_type_id())) && ((value_type_id).equals(types::unknown_type_id())))){
if (((current_key_type_id).equals(VOID_TYPE_ID))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Can't create a dictionary with keys of type void"sv)),((key)->span())))));
}
if (((current_value_type_id).equals(VOID_TYPE_ID))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Can't create a dictionary with values of type void"sv)),((value)->span())))));
}
(key_type_id = current_key_type_id);
(key_type_span = static_cast<JaktInternal::Optional<utility::Span>>(((key)->span())));
(value_type_id = current_value_type_id);
(value_type_span = static_cast<JaktInternal::Optional<utility::Span>>(((value)->span())));
}
else {
if ((!(((key_type_id).equals(current_key_type_id))))){
DeprecatedString const key_type_name = TRY((((*this).type_name(key_type_id,false))));
DeprecatedString const current_key_type_name = TRY((((*this).type_name(current_key_type_id,false))));
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Type '{}' does not match type '{}' of previous keys in dictionary"sv)),current_key_type_name,key_type_name))),((key)->span()),TRY((__jakt_format((StringView::from_string_literal("Dictionary was inferred to store keys of type '{}' here"sv)),key_type_name))),(key_type_span.value())))));
}
if ((!(((value_type_id).equals(current_value_type_id))))){
DeprecatedString const value_type_name = TRY((((*this).type_name(value_type_id,false))));
DeprecatedString const current_value_type_name = TRY((((*this).type_name(current_value_type_id,false))));
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Type '{}' does not match type '{}' of previous values in dictionary"sv)),current_value_type_name,value_type_name))),((value)->span()),TRY((__jakt_format((StringView::from_string_literal("Dictionary was inferred to store values of type '{}' here"sv)),value_type_name))),(value_type_span.value())))));
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
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot infer key type for Dictionary<K, V>"sv)),span))));
}

}
if (((value_type_id).equals(types::unknown_type_id()))){
if (((value_hint).has_value())){
(value_type_id = (value_hint.value()));
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot infer value type for Dictionary"sv)),span))));
}

}
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(dictionary_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({key_type_id, value_type_id})))))))))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::JaktDictionary>(checked_kv_pairs,span,type_id,key_type_id,value_type_id)));
}
}

ErrorOr<types::CheckedBlock> typechecker::Typechecker::typecheck_block(parser::ParsedBlock const parsed_block,types::ScopeId const parent_scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const yield_type_hint) {
{
bool const parent_throws = ((TRY((((*this).get_scope(parent_scope_id)))))->can_throw);
types::ScopeId const block_scope_id = TRY((((*this).create_scope(parent_scope_id,parent_throws,TRY(DeprecatedString::from_utf8("block"sv)),true))));
types::CheckedBlock checked_block = types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false);
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedStatement>> _magic = ((((parsed_block).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedStatement> parsed_statement = (_magic_value.value());
{
if ((!(((((checked_block).control_flow)).is_reachable())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Unreachable code"sv)),((parsed_statement)->span())))));
}
NonnullRefPtr<typename types::CheckedStatement> const checked_statement = TRY((((*this).typecheck_statement(parsed_statement,block_scope_id,safety_mode,yield_type_hint))));
(((checked_block).control_flow) = ((((checked_block).control_flow)).updated(TRY((((*this).statement_control_flow(checked_statement)))))));
JaktInternal::Optional<utility::Span> const yield_span = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<utility::Span>, ErrorOr<types::CheckedBlock>>{
auto&& __jakt_match_variant = *parsed_statement;
switch(__jakt_match_variant.index()) {
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Yield>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<utility::Span>>(((expr)->span())));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedStatement::Guard>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<utility::Span>>(((expr)->span())));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const checked_yield_expression = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>>, ErrorOr<types::CheckedBlock>>{
auto&& __jakt_match_variant = *checked_statement;
switch(__jakt_match_variant.index()) {
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Yield>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>>>(expr));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
if ((((yield_span).has_value()) && ((checked_yield_expression).has_value()))){
types::TypeId const type_var_type_id = (((checked_yield_expression.value()))->type());
types::TypeId const type_ = TRY((((*this).resolve_type_var(type_var_type_id,block_scope_id))));
if ((((checked_yield_expression.value()))->index() == 25 /* OptionalNone */)){
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
return checked_block;
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_default_fields(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
JaktInternal::DynamicArray<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_default_fields(child_namespace,child_namespace_scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
if ((((((record).record_type)).index() == 0 /* Struct */) || ((((record).record_type)).index() == 1 /* Class */))){
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find previously added struct"sv))))));
}
TRY((((*this).typecheck_struct_default_fields(record,(struct_id.value()),scope_id))));
}
}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_jakt_main(parser::ParsedFunction const parsed_function,types::ScopeId const parent_scope_id) {
{
DeprecatedString const param_type_error = TRY(DeprecatedString::from_utf8("Main function  must take a single array of strings as its parameter"sv));
JaktInternal::Optional<JaktInternal::DynamicArray<types::FunctionId>> const func_ids = TRY((((*this).find_functions_with_name_in_scope(parent_scope_id,TRY(DeprecatedString::from_utf8("main"sv))))));
if (((((func_ids.value())).size()) > static_cast<size_t>(1ULL))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Function 'main' declared multiple times."sv)),((parsed_function).name_span)))));
}
if ((((((parsed_function).params)).size()) > static_cast<size_t>(1ULL))){
TRY((((*this).error(param_type_error,((parsed_function).name_span)))));
}
if ((!(((((parsed_function).params)).is_empty())))){
if (((((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type))->index() == 3 /* JaktArray */)){
NonnullRefPtr<typename parser::ParsedType> const inner = ((((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type))->get<parser::ParsedType::JaktArray>()).inner;
utility::Span const span = ((((((((((parsed_function).params))[static_cast<i64>(0LL)])).variable)).parsed_type))->get<parser::ParsedType::JaktArray>()).span;
if (((inner)->index() == 0 /* Name */)){
DeprecatedString const name = ((inner)->get<parser::ParsedType::Name>()).name;
utility::Span const span = ((inner)->get<parser::ParsedType::Name>()).span;
if ((name != TRY(DeprecatedString::from_utf8("String"sv)))){
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
DeprecatedString const return_type_error = TRY(DeprecatedString::from_utf8("Main function  must return c_int"sv));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *((parsed_function).return_type);
switch(__jakt_match_variant.index()) {
case 13: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();DeprecatedString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if ((name != TRY(DeprecatedString::from_utf8("c_int"sv)))){
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return {};
}

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_binary_operation(NonnullRefPtr<typename types::CheckedExpression> const checked_lhs,parser::BinaryOperator const op,NonnullRefPtr<typename types::CheckedExpression> const checked_rhs,types::ScopeId const scope_id,utility::Span const span) {
{
types::TypeId const lhs_type_id = ((checked_lhs)->type());
types::TypeId const rhs_type_id = ((checked_rhs)->type());
utility::Span const lhs_span = ((checked_lhs)->span());
utility::Span const rhs_span = ((checked_rhs)->span());
types::TypeId type_id = ((checked_lhs)->type());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::TypeId>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 20: {
{
if (((op).index() == 32 /* NoneCoalescingAssign */)){
if (((checked_lhs)->index() == 24 /* Var */)){
NonnullRefPtr<types::CheckedVariable> const var = ((checked_lhs)->get<types::CheckedExpression::Var>()).var;
utility::Span const span = ((checked_lhs)->get<types::CheckedExpression::Var>()).span;
if ((!(((var)->is_mutable)))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("left-hand side of ??= must be a mutable variable"sv)),span,TRY(DeprecatedString::from_utf8("This variable isn't marked as mutable"sv)),((var)->definition_span)))));
return types::unknown_type_id();
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("left-hand side of ??= must be a mutable variable"sv)),span))));
return types::unknown_type_id();
}

}
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if (((id).equals(TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))))))){
if (((lhs_type_id).equals(rhs_type_id))){
return lhs_type_id;
}
types::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((inner_type_id).equals(rhs_type_id))){
return inner_type_id;
}
}
else {
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span,TRY(DeprecatedString::from_utf8("Left side of ?? must be an Optional but isn't"sv)),lhs_span))));
}

}
else {
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span,TRY(DeprecatedString::from_utf8("Left side of ?? must be an Optional but isn't"sv)),lhs_span))));
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return lhs_type_id;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32: {
{
if (((op).index() == 32 /* NoneCoalescingAssign */)){
if (((checked_lhs)->index() == 24 /* Var */)){
NonnullRefPtr<types::CheckedVariable> const var = ((checked_lhs)->get<types::CheckedExpression::Var>()).var;
utility::Span const span = ((checked_lhs)->get<types::CheckedExpression::Var>()).span;
if ((!(((var)->is_mutable)))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("left-hand side of ??= must be a mutable variable"sv)),span,TRY(DeprecatedString::from_utf8("This variable isn't marked as mutable"sv)),((var)->definition_span)))));
return types::unknown_type_id();
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("left-hand side of ??= must be a mutable variable"sv)),span))));
return types::unknown_type_id();
}

}
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if (((id).equals(TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))))))){
if (((lhs_type_id).equals(rhs_type_id))){
return lhs_type_id;
}
types::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
if (((inner_type_id).equals(rhs_type_id))){
return inner_type_id;
}
}
else {
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span,TRY(DeprecatedString::from_utf8("Left side of ?? must be an Optional but isn't"sv)),lhs_span))));
}

}
else {
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span,TRY(DeprecatedString::from_utf8("Left side of ?? must be an Optional but isn't"sv)),lhs_span))));
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return lhs_type_id;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5: {
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary comparison between incompatible types ({} vs {})"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6: {
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary comparison between incompatible types ({} vs {})"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7: {
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary comparison between incompatible types ({} vs {})"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8: {
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary comparison between incompatible types ({} vs {})"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9: {
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary comparison between incompatible types ({} vs {})"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10: {
{
if ((!(((lhs_type_id).equals(rhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary comparison between incompatible types ({} vs {})"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18: {
{
if ((!(((lhs_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("left side of logical binary operation is not a boolean"sv)),lhs_span))));
}
if ((!(((rhs_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("right side of logical binary operation is not a boolean"sv)),rhs_span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
{
if ((!(((lhs_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("left side of logical binary operation is not a boolean"sv)),lhs_span))));
}
if ((!(((rhs_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("right side of logical binary operation is not a boolean"sv)),rhs_span))));
}
(type_id = types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21: {
{
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
return lhs_type_id;
}
if (((checked_rhs)->index() == 25 /* OptionalNone */)){
utility::Span const span = ((checked_rhs)->get<types::CheckedExpression::OptionalNone>()).span;
types::TypeId const type_id = ((checked_rhs)->get<types::CheckedExpression::OptionalNone>()).type_id;
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if (((id).equals(TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))))))){
return lhs_type_id;
}
else if ((!(((id).equals(TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))))))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot assign None to a non-optional type"sv)),span))));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot assign None to a non-optional type"sv)),span))));
}

}
NonnullRefPtr<typename types::Type> const lhs_type = TRY((((*this).unwrap_type_from_optional_if_needed(((*this).get_type(lhs_type_id))))));
if (((lhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = ((lhs_type)->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((lhs_type)->get<types::Type::GenericInstance>()).args;
if (((((((((*this).program))->get_struct(id))).name) == TRY(DeprecatedString::from_utf8("WeakPtr"sv))) && (!(((lhs_type_id).equals(rhs_type_id)))))){
JaktInternal::Optional<types::TypeId> const unified_type = TRY((((*this).unify(((args)[static_cast<i64>(0LL)]),lhs_span,((checked_rhs)->type()),rhs_span))));
if (((unified_type).has_value())){
return (unified_type.value());
}
}
}
types::TypeId const effective_lhs_type_id = TRY((((*this).find_or_add_type_id(lhs_type))));
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,effective_lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
return ((result).value_or(lhs_type_id));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
{
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((((*this).get_type(lhs_type_id)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type(lhs_type_id)))->get<types::Type::GenericInstance>()).args;
if ((((id).equals(weak_ptr_struct_id)) && ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->index() == 23 /* Struct */))){
types::StructId const lhs_struct_id = ((((*this).get_type(((args)[static_cast<i64>(0LL)]))))->get<types::Type::Struct>()).value;
if (((((*this).get_type(rhs_type_id)))->index() == 23 /* Struct */)){
types::StructId const rhs_struct_id = ((((*this).get_type(rhs_type_id)))->get<types::Type::Struct>()).value;
if (((lhs_struct_id).equals(rhs_struct_id))){
return lhs_type_id;
}
}
}
}
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
if ((!(((checked_lhs)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Assignment to immutable variable"sv)),((checked_lhs)->span())))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
}
(type_id = lhs_type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
{
JaktInternal::Optional<types::TypeId> const result = TRY((((*this).unify(rhs_type_id,rhs_span,lhs_type_id,lhs_span))));
if ((!(((result).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return type_id;
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_predecl_initial(parser::ParsedRecord const parsed_record,size_t const enum_index,size_t const module_enum_len,types::ScopeId const scope_id) {
{
types::ModuleId const module_id = ((*this).current_module_id);
types::EnumId const enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
TRY((((((module)->types)).push(TRY((types::Type::template __jakt_create<typename types::Type::Enum>(enum_id)))))));
types::TypeId const enum_type_id = types::TypeId(module_id,(JaktInternal::checked_sub<size_t>(((((((*this).current_module()))->types)).size()),static_cast<size_t>(1ULL))));
TRY((((*this).add_type_to_scope(scope_id,((parsed_record).name),enum_type_id,((parsed_record).name_span)))));
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = enum_type_id);
ScopeGuard __jakt_var_435([&] {
(((*this).self_type_id) = old_self_type_id);
});
bool const is_boxed = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((((module)->enums)).push(types::CheckedEnum(((parsed_record).name),((parsed_record).name_span),(TRY((DynamicArray<types::CheckedGenericParameter>::create_with({})))),(TRY((DynamicArray<types::CheckedEnumVariant>::create_with({})))),(TRY((DynamicArray<types::CheckedField>::create_with({})))),((*this).prelude_scope_id()),((parsed_record).definition_linkage),(TRY((Dictionary<DeprecatedString, JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>::create_with_entries({})))),((parsed_record).record_type),enum_type_id,enum_type_id,is_boxed)))));
}
return {};
}

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_generic_resolved_type(DeprecatedString const name,JaktInternal::DynamicArray<types::TypeId> const checked_inner_types,types::ScopeId const scope_id,utility::Span const span) {
{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,name))));
if (((struct_id).has_value())){
return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>((struct_id.value()),checked_inner_types)))))));
}
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,name))));
if (((enum_id).has_value())){
return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericEnumInstance>((enum_id.value()),checked_inner_types)))))));
}
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((((*this).program))->find_trait_in_scope(scope_id,name))));
if (((trait_id).has_value())){
return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericTraitInstance>((trait_id.value()),checked_inner_types)))))));
}
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("could not find {}"sv)),name))),span))));
return types::unknown_type_id();
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_comptime_index(NonnullRefPtr<typename parser::ParsedExpression> const expr,NonnullRefPtr<typename parser::ParsedExpression> const index,types::ScopeId const scope_id,bool const is_optional,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<typename types::CheckedExpression> const checked_index = TRY((((*this).typecheck_expression(index,scope_id,safety_mode,JaktInternal::OptionalNone()))));
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((((*this).interpreter())));
NonnullRefPtr<interpreter::InterpreterScope> scope = TRY((interpreter::InterpreterScope::from_runtime_scope(scope_id,((*this).program),JaktInternal::OptionalNone())));
interpreter::StatementResult const index_result = ({ Optional<interpreter::StatementResult> __jakt_var_436;
auto __jakt_var_437 = [&]() -> ErrorOr<interpreter::StatementResult> { return TRY((((interpreter)->execute_expression(checked_index,scope)))); }();
if (__jakt_var_437.is_error()) {auto error = __jakt_var_437.release_error();
{
warnln((StringView::from_string_literal("Error while evaluating comptime index: {}"sv)),error);
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::ComptimeIndex>(TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)))),checked_index,is_optional,span)));
}
} else {__jakt_var_436 = __jakt_var_437.release_value();
}
__jakt_var_436.release_value(); });
typechecker::NumericOrStringValue const index_constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<typechecker::NumericOrStringValue, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = index_result;
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::JustValue>();
types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<typechecker::NumericOrStringValue, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
DeprecatedString const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::StringValue(val) } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U8>();
u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))) } );
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U16>();
u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U32>();
u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U64>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))) } );
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::USize>();
size_t const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I8>();
i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))) } );
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I16>();
i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))) } );
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I32>();
i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))) } );
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I64>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue( typechecker::NumericOrStringValue { typename typechecker::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))) } );
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Index expression evaluation failed: expected numeric or string type, found {}"sv)),((value).impl)))),span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Garbage>(span)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Index expression evaluation returned an invalid object {}"sv)),index_result))),span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Garbage>(span)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = index_constant;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename typechecker::NumericOrStringValue::StringValue>();
DeprecatedString const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_indexed_struct(expr,val,scope_id,is_optional,safety_mode,span)))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename typechecker::NumericOrStringValue::UnsignedNumericValue>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_indexed_tuple(expr,(infallible_integer_cast<size_t>((val))),scope_id,is_optional,safety_mode,span)))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename typechecker::NumericOrStringValue::SignedNumericValue>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_indexed_tuple(expr,(infallible_integer_cast<size_t>((val))),scope_id,is_optional,safety_mode,span)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_fields(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
JaktInternal::DynamicArray<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
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
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
if ((((((record).record_type)).index() == 0 /* Struct */) || ((((record).record_type)).index() == 1 /* Class */))){
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find previously added struct"sv))))));
}
TRY((((*this).typecheck_struct_fields(record,(struct_id.value())))));
}
}

}
}

}
return {};
}

typechecker::Typechecker::Typechecker(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, types::ModuleId a_current_module_id, JaktInternal::Optional<types::TypeId> a_current_struct_type_id, JaktInternal::Optional<types::FunctionId> a_current_function_id, bool a_inside_defer, size_t a_checkidx, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, types::GenericInferences a_generic_inferences, JaktInternal::Optional<types::TypeId> a_self_type_id, DeprecatedString a_root_module_name, bool a_in_comptime_function_call, bool a_had_an_error) :compiler(move(a_compiler)), program(move(a_program)), current_module_id(move(a_current_module_id)), current_struct_type_id(move(a_current_struct_type_id)), current_function_id(move(a_current_function_id)), inside_defer(move(a_inside_defer)), checkidx(move(a_checkidx)), ignore_errors(move(a_ignore_errors)), dump_type_hints(move(a_dump_type_hints)), dump_try_hints(move(a_dump_try_hints)), lambda_count(move(a_lambda_count)), generic_inferences(move(a_generic_inferences)), self_type_id(move(a_self_type_id)), root_module_name(move(a_root_module_name)), in_comptime_function_call(move(a_in_comptime_function_call)), had_an_error(move(a_had_an_error)){}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::cast_to_underlying(NonnullRefPtr<typename parser::ParsedExpression> const expr,types::ScopeId const scope_id,NonnullRefPtr<typename parser::ParsedType> const parsed_type) {
{
NonnullRefPtr<typename parser::ParsedExpression> const cast_expression = TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::UnaryOp>(expr, parser::UnaryOperator { typename parser::UnaryOperator::TypeCast( parser::TypeCast { typename parser::TypeCast::Infallible(parsed_type) } ) } ,((expr)->span()))));
return TRY((((*this).typecheck_expression(cast_expression,scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::substitute_typevars_in_type(types::TypeId const type_id,types::GenericInferences const generic_inferences) {
{
return TRY((((((*this).program))->substitute_typevars_in_type(type_id,generic_inferences,((*this).current_module_id)))));
}
}

ErrorOr<DeprecatedString> typechecker::Typechecker::get_argument_name(JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> const arg) const {
{
if ((!(((((arg).template get<0>())).is_empty())))){
return ((arg).template get<0>());
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *((arg).template get<2>());
switch(__jakt_match_variant.index()) {
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Var>();DeprecatedString const& name = __jakt_match_value.name;
{
return name;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::UnaryOp>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::UnaryOperator const& op = __jakt_match_value.op;
{
if (((((op).index() == 7 /* Reference */) || ((op).index() == 8 /* MutableReference */)) || ((op).index() == 5 /* Dereference */))){
if (((expr)->index() == 9 /* Var */)){
DeprecatedString const name = ((expr)->get<parser::ParsedExpression::Var>()).name;
return name;
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return TRY(DeprecatedString::from_utf8(""sv));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>>> typechecker::Typechecker::find_type_scope(types::ScopeId const scope_id,DeprecatedString const name) const {
{
return TRY((((((*this).program))->template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<types::TypeId,types::ScopeId>>(scope_id,(([name, this](types::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<types::TypeId,types::ScopeId>>> {
{
JaktInternal::Optional<types::TypeId> const maybe_type = ((((TRY((((*this).get_scope(scope_id)))))->types)).get(name));
if (((maybe_type).has_value())){
return  typename utility::IterationDecision<JaktInternal::Tuple<types::TypeId,types::ScopeId>> { typename utility::IterationDecision<JaktInternal::Tuple<types::TypeId,types::ScopeId>>::Break((Tuple{(maybe_type.value()), scope_id})) } ;
}
return  typename utility::IterationDecision<JaktInternal::Tuple<types::TypeId,types::ScopeId>> { typename utility::IterationDecision<JaktInternal::Tuple<types::TypeId,types::ScopeId>>::Continue() } ;
}
}
))))));
}
}

ErrorOr<types::FunctionId> typechecker::Typechecker::typecheck_and_specialize_generic_function(types::FunctionId const function_id,JaktInternal::DynamicArray<types::TypeId> const generic_arguments,types::ScopeId const parent_scope_id,JaktInternal::Optional<types::TypeId> const this_type_id,types::GenericInferences const generic_substitutions,JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const type_args,utility::Span const call_span,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>>> const args) {
{
NonnullRefPtr<types::CheckedFunction> checked_function = ((*this).get_function(function_id));
if ((!(((((checked_function)->parsed_function)).has_value())))){
return function_id;
}
size_t const specialization_index = ((((((checked_function)->generics))->specializations)).size());
TRY((((((((checked_function)->generics))->specializations)).push(generic_arguments))));
types::ModuleId const old_module_id = ((*this).current_module_id);
ScopeGuard __jakt_var_438([&] {
(((*this).current_module_id) = old_module_id);
});
(((*this).current_module_id) = ((((checked_function)->function_scope_id)).module_id));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const new_function_id = ((module)->next_function_id());
parser::ParsedFunction parsed_function = TRY((((checked_function)->to_parsed_function())));
types::ScopeId const scope_id = TRY((((*this).create_scope(((((checked_function)->generics))->base_scope_id),((parsed_function).can_throw),TRY((__jakt_format((StringView::from_string_literal("function-specialization({})"sv)),((parsed_function).name)))),true))));
if ((((((parsed_function).generic_parameters)).size()) != ((generic_arguments).size()))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Generic function {} expects {} generic arguments, but {} were given"sv)),((parsed_function).name),((((parsed_function).generic_parameters)).size()),((generic_arguments).size())))),((parsed_function).name_span)))));
}
if (((((((parsed_function).generic_parameters)).size()) <= ((generic_arguments).size())) && (((((parsed_function).generic_parameters)).size()) <= ((((((checked_function)->generics))->params)).size())))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_function).generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
utility::Span arg_span = call_span;
if ((((type_args).size()) > i)){
(arg_span = ((((type_args)[i]))->span()));
}
if ((((generic_arguments).size()) > i)){
TRY((((*this).check_type_argument_requirements(((generic_arguments)[i]),((((((((((checked_function)->generics))->params))[i])).checked_parameter)).constraints),arg_span))));
}
}

}
}

utility::Span const span = ((parsed_function).name_span);
{
JaktInternal::DictionaryIterator<DeprecatedString,DeprecatedString> _magic = ((((generic_substitutions).iterator())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,DeprecatedString> substitution = (_magic_value.value());
{
if (((((*this).get_type(TRY((types::TypeId::from_string(((substitution).template get<0>())))))))->index() == 18 /* TypeVariable */)){
DeprecatedString const type_name = ((((*this).get_type(TRY((types::TypeId::from_string(((substitution).template get<0>())))))))->get<types::Type::TypeVariable>()).name;
types::TypeId const type_id = TRY((types::TypeId::from_string(((substitution).template get<1>()))));
JaktInternal::Optional<types::ScopeId> const dependent_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::ScopeId>, ErrorOr<types::FunctionId>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_struct(struct_id))).scope_id));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_struct(struct_id))).scope_id));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_enum(enum_id))).scope_id));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_enum(enum_id))).scope_id));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& trait_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_trait(trait_id)))->scope_id));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_trait(trait_id)))->scope_id));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
TRY((((*this).add_type_to_scope(scope_id,type_name,type_id,span))));
if (((dependent_scope_id).has_value())){
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
TRY((((((scope)->aliases)).set(type_name,(dependent_scope_id.value())))));
}
}
}

}
}

(((parsed_function).must_instantiate) = true);
(((checked_function)->is_instantiated) = true);
(((*this).current_function_id) = static_cast<JaktInternal::Optional<types::FunctionId>>(new_function_id));
TRY((((*this).typecheck_function_predecl(parsed_function,scope_id,this_type_id,((checked_function)->generics)))));
TRY((((*this).typecheck_function(parsed_function,scope_id))));
(((*this).current_function_id) = JaktInternal::OptionalNone());
NonnullRefPtr<types::Scope> base_scope = TRY((((*this).get_scope((((TRY((((*this).get_scope(((((checked_function)->generics))->base_scope_id))))))->parent).value())))));
TRY(((((((((base_scope)->functions)).get(((checked_function)->name))).value())).push(new_function_id))));
NonnullRefPtr<types::CheckedFunction> function = ((*this).get_function(new_function_id));
(((function)->specialization_index) = specialization_index);
return new_function_id;
}
else {
return function_id;
}

}
}

ErrorOr<JaktInternal::Optional<types::ScopeId>> typechecker::Typechecker::required_scope_id_in_hierarchy_for(NonnullRefPtr<typename types::CheckedExpression> const expr,types::ScopeId const current_scope_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::ScopeId>, ErrorOr<JaktInternal::Optional<types::ScopeId>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(((*this).root_scope_id()));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(((*this).root_scope_id()));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(((*this).root_scope_id()));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(((*this).root_scope_id()));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(((*this).root_scope_id()));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(((*this).root_scope_id()));
};/*case end*/
case 33: {
return JaktInternal::ExplicitValue(((*this).root_scope_id()));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();types::CheckedUnaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::ScopeId>, ErrorOr<JaktInternal::Optional<types::ScopeId>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktArray>();JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::ScopeId>> __jakt_var_439; {
JaktInternal::Optional<types::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
(final_scope_id = TRY((((*this).scope_lifetime_union(final_scope_id,TRY((((*this).required_scope_id_in_hierarchy_for(val,current_scope_id)))))))));
}

}
}

__jakt_var_439 = final_scope_id; goto __jakt_label_403;

}
__jakt_label_403:; __jakt_var_439.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktTuple>();JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::ScopeId>> __jakt_var_440; {
JaktInternal::Optional<types::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
(final_scope_id = TRY((((*this).scope_lifetime_union(final_scope_id,TRY((((*this).required_scope_id_in_hierarchy_for(val,current_scope_id)))))))));
}

}
}

__jakt_var_440 = final_scope_id; goto __jakt_label_404;

}
__jakt_label_404:; __jakt_var_440.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktSet>();JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::ScopeId>> __jakt_var_441; {
JaktInternal::Optional<types::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
(final_scope_id = TRY((((*this).scope_lifetime_union(final_scope_id,TRY((((*this).required_scope_id_in_hierarchy_for(val,current_scope_id)))))))));
}

}
}

__jakt_var_441 = final_scope_id; goto __jakt_label_405;

}
__jakt_label_405:; __jakt_var_441.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktDictionary>();JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::ScopeId>> __jakt_var_442; {
JaktInternal::Optional<types::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> key__val__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> const jakt__key__val__ = key__val__;
NonnullRefPtr<typename types::CheckedExpression> const key = ((jakt__key__val__).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const val = ((jakt__key__val__).template get<1>());

(final_scope_id = TRY((((*this).scope_lifetime_union(final_scope_id,TRY((((*this).scope_lifetime_union(TRY((((*this).required_scope_id_in_hierarchy_for(key,current_scope_id)))),TRY((((*this).required_scope_id_in_hierarchy_for(val,current_scope_id)))))))))))));
}

}
}

__jakt_var_442 = final_scope_id; goto __jakt_label_406;

}
__jakt_label_406:; __jakt_var_442.release_value(); }));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedExpression>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedDictionary>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedTuple>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedStruct>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedCommonEnumMember>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ComptimeIndex>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 19: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 20: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 21: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Var>();NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->owner_scope).value_or_lazy_evaluated([&] { return current_scope_id; }));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NamespacedVar>();NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->owner_scope).value_or_lazy_evaluated([&] { return current_scope_id; }));
};/*case end*/
case 25: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 26: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ForcedUnwrap>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(expr,current_scope_id)))));
};/*case end*/
case 28: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Function>();JaktInternal::DynamicArray<types::CheckedCapture> const& captures = __jakt_match_value.captures;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::ScopeId>> __jakt_var_443; {
JaktInternal::Optional<types::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<types::CheckedCapture> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedCapture capture = (_magic_value.value());
{
JaktInternal::Optional<types::ScopeId> scope_id = JaktInternal::OptionalNone();
if ((((capture).index() == 2 /* ByMutableReference */) || ((capture).index() == 1 /* ByReference */))){
JaktInternal::Optional<JaktInternal::Optional<types::ScopeId>> const scope_id = ((TRY((((*this).find_var_in_scope(current_scope_id,((capture).name())))))).map([](auto& _value) { return _value->owner_scope; }));
}
(final_scope_id = TRY((((*this).scope_lifetime_union(final_scope_id,scope_id)))));
}

}
}

__jakt_var_443 = final_scope_id; goto __jakt_label_407;

}
__jakt_label_407:; __jakt_var_443.release_value(); }));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::DependentFunction>();JaktInternal::DynamicArray<types::CheckedCapture> const& captures = __jakt_match_value.captures;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::ScopeId>> __jakt_var_444; {
JaktInternal::Optional<types::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<types::CheckedCapture> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedCapture capture = (_magic_value.value());
{
JaktInternal::Optional<types::ScopeId> scope_id = JaktInternal::OptionalNone();
if ((((capture).index() == 2 /* ByMutableReference */) || ((capture).index() == 1 /* ByReference */))){
JaktInternal::Optional<JaktInternal::Optional<types::ScopeId>> const scope_id = ((TRY((((*this).find_var_in_scope(current_scope_id,((capture).name())))))).map([](auto& _value) { return _value->owner_scope; }));
}
(final_scope_id = TRY((((*this).scope_lifetime_union(final_scope_id,scope_id)))));
}

}
}

__jakt_var_444 = final_scope_id; goto __jakt_label_408;

}
__jakt_label_408:; __jakt_var_444.release_value(); }));
};/*case end*/
case 31: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 32: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
case 34: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

NonnullRefPtr<types::CheckedFunction> typechecker::Typechecker::get_function(types::FunctionId const id) const {
{
return ((((*this).program))->get_function(id));
}
}

ErrorOr<JaktInternal::Optional<typechecker::TraitImplementationDescriptor>> typechecker::Typechecker::find_any_singular_trait_implementation(types::TypeId const type_id,JaktInternal::DynamicArray<DeprecatedString> const trait_names,types::ScopeId const scope_id,utility::Span const span) {
{
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((trait_names).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString trait_name = (_magic_value.value());
{
JaktInternal::Optional<typechecker::TraitImplementationDescriptor> const maybe_impl = TRY((((*this).find_singular_trait_implementation(type_id,trait_name,scope_id,span))));
if (((maybe_impl).has_value())){
return maybe_impl;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<void> typechecker::Typechecker::specialize_trait(types::TraitId const trait_id,JaktInternal::DynamicArray<types::TypeId> const generic_parameters) {
{
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait(trait_id));
if (((((trait_)->generic_parameters)).is_empty())){
return {};
}
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericTraitInstance>(trait_id,generic_parameters))))))));
ScopeGuard __jakt_var_445([&] {
(((*this).self_type_id) = old_self_type_id);
});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((trait_)->generic_parameters)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
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

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>>> typechecker::Typechecker::typecheck_match_variant(parser::ParsedMatchCase const case_,types::TypeId const subject_type_id,size_t const variant_index,JaktInternal::Optional<types::TypeId> const final_result_type,types::CheckedEnumVariant const variant,JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const variant_arguments,JaktInternal::Dictionary<DeprecatedString,parser::ParsedPatternDefault> const default_bindings,utility::Span const arguments_span,types::ScopeId const scope_id,types::SafetyMode const safety_mode) {
{
JaktInternal::Optional<DeprecatedString> covered_name = JaktInternal::OptionalNone();
types::ScopeId const new_scope_id = TRY((((*this).create_scope(scope_id,((TRY((((*this).get_scope(scope_id)))))->can_throw),TRY((__jakt_format((StringView::from_string_literal("catch-enum-variant({})"sv)),((variant).name())))),true))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<DeprecatedString>,types::CheckedMatchCase,JaktInternal::Optional<types::TypeId>>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();DeprecatedString const& name = __jakt_match_value.name;
{
(covered_name = name);
if ((!(((variant_arguments).is_empty())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Match case '{}' cannot have arguments"sv)),name))),arguments_span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();DeprecatedString const& name = __jakt_match_value.name;
types::TypeId const& type_id = __jakt_match_value.type_id;
utility::Span const& span = __jakt_match_value.span;
{
(covered_name = name);
if ((!(((variant_arguments).is_empty())))){
if ((((variant_arguments).size()) != static_cast<size_t>(1ULL))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Match case ‘{}’ must have exactly one argument"sv)),name))),span))));
}
else {
parser::EnumVariantPatternArgument const variant_argument = ((variant_arguments)[static_cast<i64>(0LL)]);
types::TypeId const variable_type_id = TRY((((*this).substitute_typevars_in_type(type_id,((*this).generic_inferences)))));
types::VarId const var_id = TRY((((module)->add_variable(TRY((types::CheckedVariable::__jakt_create(((variant_argument).binding),variable_type_id,((variant_argument).is_mutable),span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))))));
TRY((((*this).add_var_to_scope(new_scope_id,((variant_argument).binding),var_id,span))));
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();DeprecatedString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<types::VarId> const& fields = __jakt_match_value.fields;
{
(covered_name = name);
JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> field_variables = (TRY((DynamicArray<NonnullRefPtr<types::CheckedVariable>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId var_id = (_magic_value.value());
{
TRY((((field_variables).push(((((*this).program))->get_variable(var_id))))));
}

}
}

JaktInternal::Set<DeprecatedString> seen_names = (TRY((Set<DeprecatedString>::create_with_values({}))));
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((variant_arguments).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument arg = (_magic_value.value());
{
if ((!(((((arg).name)).has_value())))){
bool found_field_name = false;
JaktInternal::DynamicArray<DeprecatedString> field_names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedVariable>> _magic = ((field_variables).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedVariable> var = (_magic_value.value());
{
TRY((((field_names).push(((var)->name)))));
if ((((var)->name) == ((arg).binding))){
(found_field_name = true);
}
}

}
}

if ((!(found_field_name))){
JaktInternal::DynamicArray<DeprecatedString> unused_field_names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((field_names).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString field_name = (_magic_value.value());
{
if (((seen_names).contains(field_name))){
continue;
}
TRY((((unused_field_names).push(field_name))));
}

}
}

TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Match case argument '{}' for struct-like enum variant '{}' cannot be anon"sv)),((arg).binding),name))),((arg).span),TRY((__jakt_format((StringView::from_string_literal("Available arguments for '{}' are: {}\n"sv)),name,TRY((utility::join(unused_field_names,TRY(DeprecatedString::from_utf8(", "sv)))))))),((arg).span)))));
continue;
}
}
DeprecatedString const arg_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); });
if (((seen_names).contains(arg_name))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Match case argument '{}' is already defined"sv)),arg_name))),((arg).span)))));
continue;
}
TRY((((seen_names).add(arg_name))));
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> matched_field_variable = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedVariable>> _magic = ((field_variables).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedVariable> var = (_magic_value.value());
{
if ((((var)->name) == arg_name)){
(matched_field_variable = var);
}
}

}
}

if (((matched_field_variable).has_value())){
types::TypeId const substituted_type_id = TRY((((*this).substitute_typevars_in_type((((matched_field_variable.value()))->type_id),((*this).generic_inferences)))));
utility::Span const matched_span = (((matched_field_variable.value()))->definition_span);
if (((*this).dump_type_hints)){
TRY((((*this).dump_type_hint((((matched_field_variable.value()))->type_id),((arg).span)))));
}
types::VarId const var_id = TRY((((module)->add_variable(TRY((types::CheckedVariable::__jakt_create(((arg).binding),substituted_type_id,((arg).is_mutable),matched_span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))))));
TRY((((*this).add_var_to_scope(new_scope_id,((arg).binding),var_id,matched_span))));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Match case argument '{}' does not exist in struct-like enum variant '{}'"sv)),arg_name,name))),((arg).span)))));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();DeprecatedString const& name = __jakt_match_value.name;
{
(covered_name = name);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,parser::ParsedPatternDefault> _magic = ((default_bindings).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> ___default___ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
DeprecatedString const _ = ((jakt_____default___).template get<0>());
parser::ParsedPatternDefault const default_ = ((jakt_____default___).template get<1>());

NonnullRefPtr<typename types::CheckedStatement> const checked_var_decl = TRY((((*this).typecheck_var_decl(((default_).variable),((default_).value),new_scope_id,safety_mode,((((default_).variable)).span)))));
TRY((((defaults).push(checked_var_decl))));
}

}
}

JaktInternal::Tuple<types::CheckedMatchBody,JaktInternal::Optional<types::TypeId>> const checked_body_result_type_ = TRY((((*this).typecheck_match_body(((case_).body),new_scope_id,safety_mode,((((*this).generic_inferences))),final_result_type,((case_).marker_span)))));
types::CheckedMatchBody const checked_body = ((checked_body_result_type_).template get<0>());
JaktInternal::Optional<types::TypeId> const result_type = ((checked_body_result_type_).template get<1>());

types::CheckedMatchCase const checked_match_case =  types::CheckedMatchCase { typename types::CheckedMatchCase::EnumVariant(defaults,((variant).name()),variant_arguments,subject_type_id,variant_index,new_scope_id,checked_body,((case_).marker_span)) } ;
return (Tuple{covered_name, checked_match_case, result_type});
}
}

ErrorOr<void> typechecker::Typechecker::include_prelude() {
{
DeprecatedString const module_name = TRY(DeprecatedString::from_utf8("__prelude__"sv));
jakt__path::Path const file_name = TRY((jakt__path::Path::from_string(module_name)));
JaktInternal::DynamicArray<u8> const file_contents = (TRY((DynamicArray<u8>::create_with({static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(83), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(79), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(83), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(68), static_cast<u8>(121), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(107), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(100), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(95), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(111), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(38), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(97), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(100), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(83), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(97), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(100), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(68), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(67), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(80), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(67), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(80), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(107), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(121), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(111), static_cast<u8>(102), static_cast<u8>(102), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(68), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(67), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(80), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(95), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(102), static_cast<u8>(56), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(121), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(98), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(98), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(121), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(86), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(119), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(68), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(66), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(66), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(86), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(119), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(106), static_cast<u8>(115), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(66), static_cast<u8>(117), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(101), static_cast<u8>(112), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(32), static_cast<u8>(65), static_cast<u8>(80), static_cast<u8>(73), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(87), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(80), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(117), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(40), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(111), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(75), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(121), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(75), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(66), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(66), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(68), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(121), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(75), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(109), static_cast<u8>(111), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(60), static_cast<u8>(65), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(73), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(86), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(63), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(86), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(34), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(91), static_cast<u8>(93), static_cast<u8>(34), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(121), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(69), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(95), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(86), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(119), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(69), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(61), static_cast<u8>(34), static_cast<u8>(95), static_cast<u8>(95), static_cast<u8>(106), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(95), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(34), static_cast<u8>(93), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(95), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(86), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(119), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(69), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(111), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(95), static_cast<u8>(119), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(117), static_cast<u8>(102), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(119), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(100), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(108), static_cast<u8>(40), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(95), static_cast<u8>(95), static_cast<u8>(95), static_cast<u8>(106), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(112), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(85), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(112), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(97), static_cast<u8>(100), static_cast<u8>(100), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(115), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(108), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(101), static_cast<u8>(120), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(100), static_cast<u8>(105), static_cast<u8>(118), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(45), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(98), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(80), static_cast<u8>(117), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(80), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(119), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(68), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(68), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(98), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(86), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(98), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(60), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(62), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(32), static_cast<u8>(46), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(46), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(91), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(93), static_cast<u8>(40), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(38), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(73), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(115), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(95), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(77), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(70), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(98), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(86), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(98), static_cast<u8>(105), static_cast<u8>(108), static_cast<u8>(105), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(80), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(112), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(111), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(66), static_cast<u8>(108), static_cast<u8>(111), static_cast<u8>(99), static_cast<u8>(107), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(110), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(99), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(109), static_cast<u8>(112), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(69), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(76), static_cast<u8>(105), static_cast<u8>(107), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(40), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(100), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(67), static_cast<u8>(108), static_cast<u8>(97), static_cast<u8>(115), static_cast<u8>(115), static_cast<u8>(40), static_cast<u8>(102), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(70), static_cast<u8>(105), static_cast<u8>(101), static_cast<u8>(108), static_cast<u8>(100), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(47), static_cast<u8>(47), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(69), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(40), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(100), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(108), static_cast<u8>(121), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(108), static_cast<u8>(117), static_cast<u8>(101), static_cast<u8>(69), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(69), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(40), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(95), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(120), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(118), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(83), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(69), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(93), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(100), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(77), static_cast<u8>(101), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(111), static_cast<u8>(100), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(103), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(109), static_cast<u8>(97), static_cast<u8>(112), static_cast<u8>(112), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(115), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(91), static_cast<u8>(40), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(93), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(100), static_cast<u8>(95), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(58), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(100), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(120), static_cast<u8>(101), static_cast<u8>(100), static_cast<u8>(32), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(100), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(66), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(56), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(49), static_cast<u8>(54), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(73), static_cast<u8>(56), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(73), static_cast<u8>(49), static_cast<u8>(54), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(73), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(73), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(74), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(116), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(67), static_cast<u8>(67), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(67), static_cast<u8>(73), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(110), static_cast<u8>(107), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(110), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(78), static_cast<u8>(101), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(79), static_cast<u8>(114), static_cast<u8>(69), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(40), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(100), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(80), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(77), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(58), static_cast<u8>(58), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(10), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(114), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(109), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(104), static_cast<u8>(105), static_cast<u8>(115), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(86), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(100), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(118), static_cast<u8>(111), static_cast<u8>(105), static_cast<u8>(100), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(66), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(98), static_cast<u8>(111), static_cast<u8>(111), static_cast<u8>(108), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(56), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(117), static_cast<u8>(56), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(49), static_cast<u8>(54), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(117), static_cast<u8>(49), static_cast<u8>(54), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(117), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(117), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(73), static_cast<u8>(56), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(105), static_cast<u8>(56), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(73), static_cast<u8>(49), static_cast<u8>(54), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(105), static_cast<u8>(49), static_cast<u8>(54), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(73), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(105), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(73), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(105), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(102), static_cast<u8>(51), static_cast<u8>(50), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(102), static_cast<u8>(54), static_cast<u8>(52), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(117), static_cast<u8>(115), static_cast<u8>(105), static_cast<u8>(122), static_cast<u8>(101), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(74), static_cast<u8>(97), static_cast<u8>(107), static_cast<u8>(116), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(103), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(67), static_cast<u8>(67), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(99), static_cast<u8>(104), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(67), static_cast<u8>(73), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(99), static_cast<u8>(95), static_cast<u8>(105), static_cast<u8>(110), static_cast<u8>(116), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(85), static_cast<u8>(110), static_cast<u8>(107), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(107), static_cast<u8>(110), static_cast<u8>(111), static_cast<u8>(119), static_cast<u8>(110), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(78), static_cast<u8>(101), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(110), static_cast<u8>(101), static_cast<u8>(118), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(83), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(117), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(79), static_cast<u8>(114), static_cast<u8>(69), static_cast<u8>(110), static_cast<u8>(117), static_cast<u8>(109), static_cast<u8>(40), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(100), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(109), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(34), static_cast<u8>(115), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(117), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(34), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(99), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(100), static_cast<u8>(46), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(84), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(86), static_cast<u8>(97), static_cast<u8>(114), static_cast<u8>(105), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(109), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(34), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(34), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(80), static_cast<u8>(116), static_cast<u8>(114), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(109), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(34), static_cast<u8>(114), static_cast<u8>(97), static_cast<u8>(119), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(34), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(46), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(109), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(34), static_cast<u8>(38), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(34), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(46), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(77), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(97), static_cast<u8>(98), static_cast<u8>(108), static_cast<u8>(101), static_cast<u8>(82), static_cast<u8>(101), static_cast<u8>(102), static_cast<u8>(101), static_cast<u8>(114), static_cast<u8>(101), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(41), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(102), static_cast<u8>(111), static_cast<u8>(114), static_cast<u8>(109), static_cast<u8>(97), static_cast<u8>(116), static_cast<u8>(40), static_cast<u8>(34), static_cast<u8>(38), static_cast<u8>(109), static_cast<u8>(117), static_cast<u8>(116), static_cast<u8>(32), static_cast<u8>(123), static_cast<u8>(125), static_cast<u8>(34), static_cast<u8>(44), static_cast<u8>(32), static_cast<u8>(116), static_cast<u8>(121), static_cast<u8>(112), static_cast<u8>(101), static_cast<u8>(46), static_cast<u8>(110), static_cast<u8>(97), static_cast<u8>(109), static_cast<u8>(101), static_cast<u8>(40), static_cast<u8>(41), static_cast<u8>(41), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(70), static_cast<u8>(117), static_cast<u8>(110), static_cast<u8>(99), static_cast<u8>(116), static_cast<u8>(105), static_cast<u8>(111), static_cast<u8>(110), static_cast<u8>(32), static_cast<u8>(61), static_cast<u8>(62), static_cast<u8>(32), static_cast<u8>(34), static_cast<u8>(102), static_cast<u8>(110), static_cast<u8>(34), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(32), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(125), static_cast<u8>(10), static_cast<u8>(10)}))));
JaktInternal::Optional<utility::FileId> const old_file_id = ((((*this).compiler))->current_file);
JaktInternal::DynamicArray<u8> const old_file_contents = ((((*this).compiler))->current_file_contents);
ScopeGuard __jakt_var_446([&] {
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
types::ScopeId const prelude_scope_id = TRY((((*this).create_scope(JaktInternal::OptionalNone(),false,TRY(DeprecatedString::from_utf8("prelude"sv)),false))));
JaktInternal::DynamicArray<lexer::Token> const tokens = TRY((lexer::Lexer::lex(((*this).compiler))));
if (((((*this).compiler))->dump_lexer)){
{
JaktInternal::ArrayIterator<lexer::Token> _magic = ((tokens).iterator());
for (;;){
JaktInternal::Optional<lexer::Token> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
outln((StringView::from_string_literal("token: {}"sv)),token);
}

}
}

}
parser::ParsedNamespace const parsed_namespace = TRY((parser::Parser::parse(((*this).compiler),tokens)));
if (((((*this).compiler))->dump_parser)){
outln((StringView::from_string_literal("{:#}"sv)),parsed_namespace);
}
TRY((((((*this).compiler))->dbg_println(TRY((__jakt_format((StringView::from_string_literal("before typechecking parsed prelude, modules ‘{}’"sv)),((((*this).program))->modules))))))));
TRY((((*this).typecheck_module(parsed_namespace,prelude_scope_id))));
}
return {};
}

ErrorOr<types::ModuleId> typechecker::Typechecker::create_module(DeprecatedString const name,bool const is_root,JaktInternal::Optional<DeprecatedString> const path) {
{
size_t const new_id = ((((((*this).program))->modules)).size());
types::ModuleId const module_id = types::ModuleId(new_id);
NonnullRefPtr<types::Module> const module = TRY((types::Module::__jakt_create(module_id,name,(TRY((DynamicArray<NonnullRefPtr<types::CheckedFunction>>::create_with({})))),(TRY((DynamicArray<types::CheckedStruct>::create_with({})))),(TRY((DynamicArray<types::CheckedEnum>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<types::Scope>>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<typename types::Type>>::create_with({TRY((types::Type::template __jakt_create<typename types::Type::Void>())), TRY((types::Type::template __jakt_create<typename types::Type::Bool>())), TRY((types::Type::template __jakt_create<typename types::Type::U8>())), TRY((types::Type::template __jakt_create<typename types::Type::U16>())), TRY((types::Type::template __jakt_create<typename types::Type::U32>())), TRY((types::Type::template __jakt_create<typename types::Type::U64>())), TRY((types::Type::template __jakt_create<typename types::Type::I8>())), TRY((types::Type::template __jakt_create<typename types::Type::I16>())), TRY((types::Type::template __jakt_create<typename types::Type::I32>())), TRY((types::Type::template __jakt_create<typename types::Type::I64>())), TRY((types::Type::template __jakt_create<typename types::Type::F32>())), TRY((types::Type::template __jakt_create<typename types::Type::F64>())), TRY((types::Type::template __jakt_create<typename types::Type::Usize>())), TRY((types::Type::template __jakt_create<typename types::Type::JaktString>())), TRY((types::Type::template __jakt_create<typename types::Type::CChar>())), TRY((types::Type::template __jakt_create<typename types::Type::CInt>())), TRY((types::Type::template __jakt_create<typename types::Type::Unknown>())), TRY((types::Type::template __jakt_create<typename types::Type::Never>()))})))),(TRY((DynamicArray<NonnullRefPtr<types::CheckedTrait>>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<types::CheckedVariable>>::create_with({})))),(TRY((DynamicArray<types::ModuleId>::create_with({})))),path.value_or_lazy_evaluated([&] { return (((((((*this).compiler))->current_file_path()).value())).to_string()); }),is_root)));
TRY((((((((*this).program))->modules)).push(module))));
return module_id;
}
}

types::ScopeId typechecker::Typechecker::prelude_scope_id() const {
{
return ((((*this).program))->prelude_scope_id());
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_namespaced_var_or_simple_enum_constructor_call(DeprecatedString const name,JaktInternal::DynamicArray<DeprecatedString> const namespace_,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint,utility::Span const span) {
{
JaktInternal::DynamicArray<types::ScopeId> scopes = (TRY((DynamicArray<types::ScopeId>::create_with({scope_id}))));
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((namespace_).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString ns = (_magic_value.value());
{
types::ScopeId const scope = ((scopes)[(JaktInternal::checked_sub<size_t>(((scopes).size()),static_cast<size_t>(1ULL)))]);
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> const ns_in_scope = TRY((((*this).find_namespace_in_scope(scope,ns,false))));
JaktInternal::Optional<types::EnumId> const enum_in_scope = TRY((((((*this).program))->find_enum_in_scope(scope,ns))));
types::ScopeId next_scope = scope;
if (((ns_in_scope).has_value())){
(next_scope = (((ns_in_scope.value())).template get<0>()));
}
else if (((enum_in_scope).has_value())){
(next_scope = ((((*this).get_enum((enum_in_scope.value())))).scope_id));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Namespace ‘{}’ not found"sv)),ns))),span))));
}

TRY((((scopes).push(next_scope))));
}

}
}

types::ScopeId const scope = (((scopes).last()).value());
size_t i = static_cast<size_t>(0ULL);
size_t const min_length = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = ((((scopes).size()) <= ((namespace_).size())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((scopes).size()));
}
else {
return JaktInternal::ExplicitValue(((namespace_).size()));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::CheckedNamespace> checked_namespaces = (TRY((DynamicArray<types::CheckedNamespace>::create_with({}))));
while ((i < min_length)){
TRY((((checked_namespaces).push(types::CheckedNamespace(((namespace_)[i]),scope)))));
((i++));
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> const var = TRY((((*this).find_var_in_scope(scope,name))));
if (((var).has_value())){
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NamespacedVar>(checked_namespaces,(var.value()),span)));
}
parser::ParsedCall const implicit_constructor_call = parser::ParsedCall(namespace_,name,(TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({})))));
NonnullRefPtr<typename types::CheckedExpression> const call_expression = TRY((((*this).typecheck_call(implicit_constructor_call,scope_id,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),safety_mode,type_hint,true))));
types::TypeId const type_id = ((call_expression)->type());
types::CheckedCall const call = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedCall, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *call_expression;
switch(__jakt_match_variant.index()) {
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(call);
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("typecheck_call returned something other than a CheckedCall"sv))))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((((call).function_id)).has_value())){
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Call>(call,span,type_id)));
}
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Variable '{}' not found"sv)),name))),span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NamespacedVar>(checked_namespaces,TRY((types::CheckedVariable::__jakt_create(name,types::unknown_type_id(),false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))),span)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_predecl(parser::ParsedRecord const parsed_record,types::StructId const struct_id,types::ScopeId const scope_id) {
{
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
ScopeGuard __jakt_var_447([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = struct_type_id);
ScopeGuard __jakt_var_448([&] {
(((*this).self_type_id) = old_self_type_id);
});
types::ScopeId const struct_scope_id = ((((((((*this).current_module()))->structures))[((struct_id).id)])).scope_id);
TRY((((*this).add_struct_to_scope(scope_id,((parsed_record).name),struct_id,((parsed_record).name_span)))));
JaktInternal::Optional<types::StructId> super_struct_id = JaktInternal::OptionalNone();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const& super_parsed_type = __jakt_match_value.super_type;
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>>{
auto __jakt_enum_value = (((super_parsed_type).has_value()));
if (__jakt_enum_value == true) {
{
types::TypeId const super_type_id = TRY((((*this).typecheck_typename((super_parsed_type.value()),scope_id,JaktInternal::OptionalNone()))));
NonnullRefPtr<typename types::Type> const super_type = ((*this).get_type(super_type_id));
if (((super_type)->index() == 23 /* Struct */)){
types::StructId const struct_id = ((super_type)->get<types::Type::Struct>()).value;
(super_struct_id = struct_id);
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Class can only inherit from another class"sv)),(((super_parsed_type.value()))->span())))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == false) {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const& super_parsed_type = __jakt_match_value.super_type;
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>>{
auto __jakt_enum_value = (((super_parsed_type).has_value()));
if (__jakt_enum_value == true) {
{
types::TypeId const super_type_id = TRY((((*this).typecheck_typename((super_parsed_type.value()),scope_id,JaktInternal::OptionalNone()))));
NonnullRefPtr<typename types::Type> const super_type = ((*this).get_type(super_type_id));
if (((super_type)->index() == 23 /* Struct */)){
types::StructId const struct_id = ((super_type)->get<types::Type::Struct>()).value;
(super_struct_id = struct_id);
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Struct can only inherit from another struct"sv)),(((super_parsed_type.value()))->span())))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == false) {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY(DeprecatedString::from_utf8("Expected Struct or Class in typecheck_struct_predecl"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<types::Module> module = ((*this).current_module());
(((((module)->structures))[((struct_id).id)]) = types::CheckedStruct(((parsed_record).name),((parsed_record).name_span),(TRY((DynamicArray<types::CheckedGenericParameter>::create_with({})))),(TRY((DynamicArray<types::CheckedField>::create_with({})))),struct_scope_id,((parsed_record).definition_linkage),(TRY((Dictionary<DeprecatedString, JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>::create_with_entries({})))),((parsed_record).record_type),struct_type_id,super_struct_id,((parsed_record).external_name)));
JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters = ((((((module)->structures))[((struct_id).id)])).generic_parameters);
TRY((((generic_parameters).ensure_capacity(((((parsed_record).generic_parameters)).size())))));
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((parsed_record).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter gen_parameter = (_magic_value.value());
{
types::TypeId const parameter_type_id = types::TypeId(((*this).current_module_id),((((((*this).current_module()))->types)).size()));
types::CheckedGenericParameter parameter = TRY((types::CheckedGenericParameter::make(parameter_type_id,((gen_parameter).span))));
JaktInternal::DynamicArray<types::TypeId> trait_implementations = (TRY((DynamicArray<types::TypeId>::create_with({}))));
TRY((((((module)->types)).push(TRY((types::Type::template __jakt_create<typename types::Type::TypeVariable>(((gen_parameter).name),trait_implementations)))))));
if (((((gen_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((gen_parameter).requires_list).value()),((((parameter).constraints))),((trait_implementations)),scope_id))));
}
TRY((((generic_parameters).push(parameter))));
TRY((((*this).add_type_to_scope(struct_scope_id,((gen_parameter).name),parameter_type_id,((gen_parameter).span)))));
}

}
}

bool const is_extern = ((((parsed_record).definition_linkage)).index() == 1 /* External */);
(((((((module)->structures))[((struct_id).id)])).generic_parameters) = generic_parameters);
(((*this).current_struct_type_id) = JaktInternal::OptionalNone());
}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_unary_operation(NonnullRefPtr<typename types::CheckedExpression> const checked_expr,types::CheckedUnaryOperator const checked_op,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode) {
{
types::TypeId const expr_type_id = ((checked_expr)->type());
NonnullRefPtr<typename types::Type> const expr_type = ((*this).get_type(expr_type_id));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = checked_op;
switch(__jakt_match_variant.index()) {
case 0: {
{
if (((*this).is_integer(expr_type_id))){
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Increment/decrement of immutable variable"sv)),span))));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Increment/decrement of non-numeric value"sv)),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
{
if (((*this).is_integer(expr_type_id))){
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Increment/decrement of immutable variable"sv)),span))));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Increment/decrement of non-numeric value"sv)),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
{
if (((*this).is_integer(expr_type_id))){
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Increment/decrement of immutable variable"sv)),span))));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Increment/decrement of non-numeric value"sv)),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
{
if (((*this).is_integer(expr_type_id))){
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Increment/decrement of immutable variable"sv)),span))));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Increment/decrement of non-numeric value"sv)),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9: {
{
if ((!(TRY((((*this).check_types_for_compat(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ),((checked_expr)->type()),((((*this).generic_inferences))),span))))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot use a logical Not on a value of non-boolean type"sv)),span))));
}
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,expr_type_id)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,expr_type_id)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::TypeCast>();
types::CheckedTypeCast const& cast = __jakt_match_value.value;
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,((cast).type_id()))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
{
return TRY((((*this).typecheck_unary_negate(checked_expr,span,expr_type_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } ))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::RawPtr>(expr_type_id))))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7: {
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Reference>(expr_type_id))))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8: {
{
if ((!(((checked_expr)->is_mutable(((*this).program)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot make mutable reference to immutable value"sv)),span))));
}
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::MutableReference>(expr_type_id))))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5: {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr_type;
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& type_id = __jakt_match_value.value;
{
if (((safety_mode).index() == 0 /* Safe */)){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Dereference of raw pointer outside of unsafe block"sv)),span))));
}
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,type_id)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,type_id)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
{
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,type_id)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Dereference of a non-pointer type ‘{}’"sv)),TRY((((*this).type_name(expr_type_id,false))))))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::UnaryOp>(checked_expr,checked_op,span,expr_type_id)));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::infer_unsigned_int(u64 const val,utility::Span const span,JaktInternal::Optional<types::TypeId> const type_hint) {
{
NonnullRefPtr<typename types::CheckedExpression> expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } ))));
if (((type_hint).has_value())){
types::TypeId const hint = (type_hint.value());
if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8((infallible_integer_cast<i8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16((infallible_integer_cast<i16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16((infallible_integer_cast<u16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((((type_)->max()) < val)){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U32((infallible_integer_cast<u32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))){
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))));
}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))){
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))));
}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))){
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))));
}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((val > static_cast<u64>(255ULL))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))));
}

}
}
return expr;
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::strip_optional_from_type(types::TypeId const type_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<types::TypeId>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_449; {
if (((id).equals(TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))))))){
return ((args)[static_cast<i64>(0LL)]);
}
__jakt_var_449 = type_id; goto __jakt_label_409;

}
__jakt_label_409:; __jakt_var_449.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<types::FieldRecord>> typechecker::Typechecker::lookup_struct_field(types::StructId const struct_id,DeprecatedString const name) const {
{
JaktInternal::DynamicArray<types::StructId> chain = (TRY((DynamicArray<types::StructId>::create_with({}))));
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
JaktInternal::Optional<types::StructId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::StructId current_struct_id = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((((*this).get_struct(current_struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((*this).get_variable(((field).variable_id)));
if ((((variable)->name) == name)){
return types::FieldRecord(current_struct_id,((field).variable_id));
}
}

}
}

}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<types::CheckedParameter> typechecker::Typechecker::typecheck_parameter(parser::ParsedParameter const parameter,types::ScopeId const scope_id,bool const first,JaktInternal::Optional<types::TypeId> const this_arg_type_id,JaktInternal::Optional<types::ScopeId> const check_scope) {
{
types::TypeId type_id = TRY((((*this).typecheck_typename(((((parameter).variable)).parsed_type),scope_id,((((parameter).variable)).name)))));
if ((first && (((((parameter).variable)).name) == TRY(DeprecatedString::from_utf8("this"sv))))){
if (((this_arg_type_id).has_value())){
(type_id = (this_arg_type_id.value()));
}
}
NonnullRefPtr<types::CheckedVariable> const variable = TRY((types::CheckedVariable::__jakt_create(((((parameter).variable)).name),type_id,((((parameter).variable)).is_mutable),((((parameter).variable)).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> checked_default_value = JaktInternal::OptionalNone();
if (((((parameter).default_argument)).has_value())){
NonnullRefPtr<typename types::CheckedExpression> checked_default_value_expr = TRY((((*this).typecheck_expression((((parameter).default_argument).value()),scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,type_id))));
if (((checked_default_value_expr)->index() == 25 /* OptionalNone */)){
utility::Span const expr_span = ((checked_default_value_expr)->get<types::CheckedExpression::OptionalNone>()).span;
(checked_default_value_expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::OptionalNone>(expr_span,type_id))));
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
return checked_parameter;
}
}

ErrorOr<JaktInternal::Optional<types::TypeId>> typechecker::Typechecker::unify(types::TypeId const lhs,utility::Span const lhs_span,types::TypeId const rhs,utility::Span const rhs_span) {
{
if ((!(TRY((((*this).check_types_for_compat(lhs,rhs,((((*this).generic_inferences))),lhs_span))))))){
return JaktInternal::OptionalNone();
}
return TRY((((*this).substitute_typevars_in_type(lhs,((*this).generic_inferences)))));
}
}

ErrorOr<types::BlockControlFlow> typechecker::Typechecker::maybe_statement_control_flow(JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const statement,types::BlockControlFlow const other_branch) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (((statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((*this).statement_control_flow((statement.value()))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(((other_branch).partial()));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool typechecker::Typechecker::is_floating(types::TypeId const type_id) const {
{
return ((((*this).program))->is_floating(type_id));
}
}

ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> typechecker::Typechecker::find_var_in_scope(types::ScopeId const scope_id,DeprecatedString const var) const {
{
return TRY((((((*this).program))->find_var_in_scope(scope_id,var))));
}
}

ErrorOr<void> typechecker::Typechecker::set_owner_scope_if_needed(types::ScopeId const parent_scope_id,JaktInternal::DynamicArray<types::FunctionId> const overload_set) {
{
{
JaktInternal::ArrayIterator<types::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId overload = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> function = ((*this).get_function(overload));
if ((!(((((function)->owner_scope)).has_value())))){
(((function)->owner_scope) = parent_scope_id);
}
}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::set_owner_scope_if_needed(types::ScopeId const parent_scope_id,types::VarId const var_id) {
{
NonnullRefPtr<types::CheckedVariable> variable = ((*this).get_variable(var_id));
if ((!(((((variable)->owner_scope)).has_value())))){
(((variable)->owner_scope) = parent_scope_id);
}
}
return {};
}

ErrorOr<bool> typechecker::Typechecker::add_type_to_scope(types::ScopeId const scope_id,DeprecatedString const type_name,types::TypeId const type_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::TypeId> const found_type_id = ((((scope)->types)).get(type_name));
if ((((found_type_id).has_value()) && (!((((found_type_id.value())).equals(type_id)))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Redefinition of type ‘{}’"sv)),type_name))),span))));
return false;
}
TRY((((((scope)->types)).set(type_name,type_id))));
return true;
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::find_type_in_prelude(DeprecatedString const name) const {
{
types::ScopeId const scope_id = ((*this).prelude_scope_id());
JaktInternal::Optional<types::TypeId> const type_id = TRY((((*this).find_type_in_scope(scope_id,name))));
if (((type_id).has_value())){
return ((type_id).value());
}
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("internal error: {} builtin definition not found"sv)),name)))))));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::infer_signed_int(i64 const val,utility::Span const span,JaktInternal::Optional<types::TypeId> const type_hint) {
{
NonnullRefPtr<typename types::CheckedExpression> expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } ))));
if (((type_hint).has_value())){
types::TypeId const hint = (type_hint.value());
if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8((infallible_integer_cast<i8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16((infallible_integer_cast<i16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16((infallible_integer_cast<u16>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < ((type_)->min())) || (val > (infallible_integer_cast<i64>((((type_)->max()))))))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U32((infallible_integer_cast<u32>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if ((val < static_cast<i64>(0LL))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } )))));
}

}
else if (((hint).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))){
types::TypeId const builtin_typeid = types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } );
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(builtin_typeid));
if (((val < static_cast<i64>(0LL)) || (val > static_cast<i64>(255LL)))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Integer promotion failed"sv)),span,TRY((__jakt_format((StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv)),((type_)->min()),((type_)->max()),TRY((((*this).type_name(builtin_typeid,false))))))),span))));
}
else {
(expr = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8((infallible_integer_cast<u8>((val)))) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } )))));
}

}
}
return expr;
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_aliases(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id,typechecker::ImportRestrictions const allow) {
{
JaktInternal::DynamicArray<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_aliases(child_namespace,child_namespace_scope_id,allow))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedAlias> _magic = ((((parsed_namespace).aliases)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedAlias> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedAlias alias = (_magic_value.value());
{
TRY((((*this).typecheck_alias(alias,scope_id,allow))));
}

}
}

}
return {};
}

ErrorOr<bool> typechecker::Typechecker::add_struct_to_scope(types::ScopeId const scope_id,DeprecatedString const name,types::StructId const struct_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::StructId> const maybe_scope_id = ((((scope)->structs)).get(name));
if (((maybe_scope_id).has_value())){
types::StructId const existing_struct_id = (maybe_scope_id.value());
utility::Span const definition_span = ((((*this).get_struct(existing_struct_id))).name_span);
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("redefinition of struct/class {}"sv)),name))),span,TRY((__jakt_format((StringView::from_string_literal("struct/class {} was first defined here"sv)),name))),definition_span))));
return false;
}
TRY((((((scope)->structs)).set(name,struct_id))));
return true;
}
}

ErrorOr<void> typechecker::Typechecker::error(DeprecatedString const message,utility::Span const span) {
{
if ((!(((*this).ignore_errors)))){
TRY((((((((*this).compiler))->errors)).push( error::JaktError { typename error::JaktError::Message(message,span) } ))));
}
else {
(((*this).had_an_error) = true);
}

}
return {};
}

ErrorOr<bool> typechecker::Typechecker::check_restricted_access(types::ScopeId const accessor,DeprecatedString const accessee_kind,types::ScopeId const accessee,DeprecatedString const name,JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> const whitelist,utility::Span const span) {
{
types::ScopeId const most_specific_active_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId,ErrorOr<bool>>{
auto __jakt_enum_value = (((((*this).current_function_id)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((((*this).get_function((((*this).current_function_id).value()))))->function_scope_id));
}
else {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_450; {
if ((!(((((*this).current_struct_type_id)).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Can't access {0} ‘{1}’ from this global scope, because ‘{1}’ restricts access to it"sv)),accessee_kind,name))),span))));
return false;
}
__jakt_var_450 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId, ErrorOr<bool>>{
auto&& __jakt_match_variant = *((*this).get_type((((*this).current_struct_type_id).value())));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_struct(id))).scope_id));
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Internal error: current_struct_type_id is not a struct"sv)),span))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_410;

}
__jakt_label_410:; __jakt_var_450.release_value(); }));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::MaybeResolvedScope>> _magic = ((whitelist).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::MaybeResolvedScope>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::MaybeResolvedScope> scope = (_magic_value.value());
{
NonnullRefPtr<typename types::MaybeResolvedScope> const resolved_scope = TRY((((scope)->try_resolve(((*this).program)))));
if (((resolved_scope)->index() == 0 /* Resolved */)){
types::ScopeId const scope_id = ((resolved_scope)->get<types::MaybeResolvedScope::Resolved>()).value;
if (TRY((((*this).scope_can_access(most_specific_active_scope_id,scope_id))))){
return true;
}
}
else {
continue;
}

}

}
}

NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(most_specific_active_scope_id))));
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot access {} ‘{}’ from this scope"sv)),accessee_kind,name))),span))));
return false;
}
}

ErrorOr<bool> typechecker::Typechecker::check_types_for_compat(types::TypeId const lhs_type_id,types::TypeId const rhs_type_id,types::GenericInferences& generic_inferences,utility::Span const span) {
{
if (((((lhs_type_id).equals(rhs_type_id)) || ((lhs_type_id).equals(types::unknown_type_id()))) || ((rhs_type_id).equals(types::unknown_type_id())))){
return true;
}
NonnullRefPtr<typename types::Type> const lhs_type = ((*this).get_type(lhs_type_id));
NonnullRefPtr<typename types::Type> const rhs_type = ((*this).get_type(rhs_type_id));
if (((lhs_type)->index() == 30 /* Self */)){
if ((!(((((*this).self_type_id)).has_value())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Invalid use of the 'Self' type"sv)),span))));
}
else {
return TRY((((*this).check_types_for_compat((((*this).self_type_id).value()),rhs_type_id,generic_inferences,span))));
}

}
if (((rhs_type)->index() == 30 /* Self */)){
if ((!(((((*this).self_type_id)).has_value())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Invalid use of the 'Self' type"sv)),span))));
}
else {
return TRY((((*this).check_types_for_compat(lhs_type_id,(((*this).self_type_id).value()),generic_inferences,span))));
}

}
DeprecatedString const lhs_type_id_string = TRY((((lhs_type_id).to_string())));
DeprecatedString const rhs_type_id_string = TRY((((rhs_type_id).to_string())));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
types::StructId const weakptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
types::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Array"sv))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *lhs_type;
switch(__jakt_match_variant.index()) {
case 18: {
{
JaktInternal::Optional<DeprecatedString> seen_type_id_string = ((((generic_inferences))).get(lhs_type_id_string));
if (((seen_type_id_string).has_value())){
types::TypeId const seen_type_id = TRY((types::TypeId::from_string((seen_type_id_string.value()))));
if (((((*this).get_type(seen_type_id)))->index() == 18 /* TypeVariable */)){
return TRY((((*this).check_types_for_compat(seen_type_id,lhs_type_id,generic_inferences,span))));
}
if ((((seen_type_id_string).value()) != rhs_type_id_string)){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(seen_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
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
JaktInternal::DynamicArray<types::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs_type)->index() == 20 /* GenericEnumInstance */)){
types::EnumId const rhs_enum_id = ((rhs_type)->get<types::Type::GenericEnumInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const rhs_args = ((rhs_type)->get<types::Type::GenericEnumInstance>()).args;
if (((lhs_enum_id).equals(rhs_enum_id))){
types::CheckedEnum const lhs_enum = ((*this).get_enum(lhs_enum_id));
if ((((lhs_args).size()) == ((rhs_args).size()))){
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((lhs_args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((lhs_args)[idx]),((rhs_args)[idx]),generic_inferences,span))))))){
return false;
}
(++(idx));
}
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("mismatched number of generic parameters for {}"sv)),((lhs_enum).name)))),span))));
return false;
}

}
}
else {
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::DynamicArray<types::TypeId> const& lhs_params = __jakt_match_value.params;
bool const& lhs_can_throw = __jakt_match_value.can_throw;
types::TypeId const& lhs_return_type_id = __jakt_match_value.return_type_id;
{
if (((rhs_type)->index() == 29 /* Function */)){
JaktInternal::DynamicArray<types::TypeId> const rhs_params = ((rhs_type)->get<types::Type::Function>()).params;
bool const rhs_can_throw = ((rhs_type)->get<types::Type::Function>()).can_throw;
types::TypeId const rhs_return_type_id = ((rhs_type)->get<types::Type::Function>()).return_type_id;
if ((!((lhs_can_throw == rhs_can_throw)))){
DeprecatedString const lhs_throw = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<bool>>{
auto __jakt_enum_value = (lhs_can_throw);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Yes"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("No"sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
DeprecatedString const rhs_throw = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<bool>>{
auto __jakt_enum_value = (rhs_can_throw);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Yes"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("No"sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Function can throw mismatch: expected ‘{}’, but got ‘{}’"sv)),lhs_throw,rhs_throw))),span))));
}
if ((!((((lhs_params).size()) == ((rhs_params).size()))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Function parameter count mismatch: expected ‘{}’, but got ‘{}’"sv)),((lhs_params).size()),((rhs_params).size())))),span))));
return false;
}
if ((!(TRY((((*this).check_types_for_compat(lhs_return_type_id,rhs_return_type_id,generic_inferences,span))))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Function type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span,TRY((__jakt_format((StringView::from_string_literal("The return types differ: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_return_type_id,false)))),TRY((((*this).type_name(rhs_return_type_id,false))))))),span))));
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((lhs_params).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(TRY((((*this).check_types_for_compat(((lhs_params)[i]),((rhs_params)[i]),generic_inferences,span))))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Function type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span,TRY((__jakt_format((StringView::from_string_literal("The parameter types differ at argument {}: expected ‘{}’, but got ‘{}’"sv)),(JaktInternal::checked_add<size_t>(i,static_cast<size_t>(1ULL))),TRY((((*this).type_name(((lhs_params)[i]),false)))),TRY((((*this).type_name(((rhs_params)[i]),false))))))),span))));
return false;
}
}

}
}

}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
{
types::StructId const lhs_struct_id = id;
JaktInternal::DynamicArray<types::TypeId> const lhs_args = args;
if ((((lhs_struct_id).equals(optional_struct_id)) || ((lhs_struct_id).equals(weakptr_struct_id)))){
if ((((lhs_args).size()) > static_cast<size_t>(0ULL))){
if (((((lhs_args)[static_cast<i64>(0LL)])).equals(rhs_type_id))){
return true;
}
}
}
if (((rhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = ((rhs_type)->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((rhs_type)->get<types::Type::GenericInstance>()).args;
types::StructId const rhs_struct_id = id;
if (((lhs_struct_id).equals(rhs_struct_id))){
JaktInternal::DynamicArray<types::TypeId> const rhs_args = args;
types::CheckedStruct const lhs_struct = ((*this).get_struct(lhs_struct_id));
if ((((lhs_args).size()) == ((rhs_args).size()))){
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((lhs_args)[idx]),((rhs_args)[idx]),generic_inferences,span))))))){
return false;
}
(++(idx));
}
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("mismatched number of generic parameters for {}"sv)),((lhs_struct).name)))),span))));
return false;
}

}
else if (((lhs_struct_id).equals(array_struct_id))){
types::TypeId const array_value_type_id = ((args)[static_cast<i64>(0LL)]);
if (((array_value_type_id).equals(types::unknown_type_id()))){
return true;
}
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}

}
else {
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
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
return true;
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *rhs_type;
switch(__jakt_match_variant.index()) {
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
{
if (((enum_id).equals(id))){
types::CheckedEnum const lhs_enum = ((*this).get_enum(enum_id));
if ((((args).size()) != ((((lhs_enum).generic_parameters)).size()))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("mismatched number of generic parameters for {}"sv)),((lhs_enum).name)))),span))));
return false;
}
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((((((lhs_enum).generic_parameters))[idx])).type_id),((args)[idx]),generic_inferences,span))))))){
return false;
}
(++(idx));
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18: {
{
JaktInternal::Optional<DeprecatedString> const seen_type_id_string = ((((generic_inferences))).get(rhs_type_id_string));
if (((seen_type_id_string).has_value())){
if ((((seen_type_id_string).value()) != lhs_type_id_string)){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(TRY((types::TypeId::from_string(((seen_type_id_string).value())))),false))))))),span))));
return false;
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& lhs_struct_id = __jakt_match_value.value;
{
if ((((lhs_type_id).equals(rhs_type_id)) || ((*this).is_subclass_of(rhs_type_id,lhs_type_id)))){
return true;
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *rhs_type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
{
if ((!(((lhs_struct_id).equals(id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}
types::CheckedStruct const lhs_struct = ((*this).get_struct(lhs_struct_id));
if ((((args).size()) != ((((lhs_struct).generic_parameters)).size()))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("mismatched number of generic parameters for {}"sv)),((lhs_struct).name)))),span))));
return false;
}
size_t idx = static_cast<size_t>(0ULL);
while ((idx < ((args).size()))){
if ((!(TRY((((*this).check_types_for_compat(((((((lhs_struct).generic_parameters))[idx])).type_id),((args)[idx]),generic_inferences,span))))))){
return false;
}
(++(idx));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18: {
{
JaktInternal::Optional<DeprecatedString> const seen_type_id_string = ((((generic_inferences))).get(rhs_type_id_string));
if (((seen_type_id_string).has_value())){
if ((((seen_type_id_string).value()) != lhs_type_id_string)){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(TRY((types::TypeId::from_string(((seen_type_id_string).value())))),false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
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
if (((*this).is_subclass_of(lhs_type_id,rhs_type_id))){
return true;
}
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& lhs_rawptr_type_id = __jakt_match_value.value;
{
if (((lhs_rawptr_type_id).equals(rhs_type_id))){
return true;
}
if (((rhs_type)->index() == 25 /* RawPtr */)){
types::TypeId const rhs_rawptr_type_id = ((rhs_type)->get<types::Type::RawPtr>()).value;
if ((!(TRY((((*this).check_types_for_compat(lhs_rawptr_type_id,rhs_rawptr_type_id,generic_inferences,span))))))){
return false;
}
}
else {
if ((!(((rhs_type_id).equals(lhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
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
types::TypeId const rhs_inner_type_id = ((rhs_type)->get<types::Type::Reference>()).value;
if ((!(TRY((((*this).check_types_for_compat(lhs_inner_type_id,rhs_inner_type_id,generic_inferences,span))))))){
return false;
}
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& lhs_inner_type_id = __jakt_match_value.value;
{
if (((rhs_type)->index() == 28 /* MutableReference */)){
types::TypeId const rhs_inner_type_id = ((rhs_type)->get<types::Type::MutableReference>()).value;
if ((!(TRY((((*this).check_types_for_compat(lhs_inner_type_id,rhs_inner_type_id,generic_inferences,span))))))){
return false;
}
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
if ((((((generic_inferences))).map_name(rhs_type_id_string)) != ((((generic_inferences))).map_name(lhs_type_id_string)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),span))));
return false;
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return true;
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_predecl(parser::ParsedRecord const parsed_record,types::EnumId const enum_id,types::ScopeId const scope_id) {
{
types::TypeId const enum_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Enum>(enum_id)))))));
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = enum_type_id);
ScopeGuard __jakt_var_451([&] {
(((*this).self_type_id) = old_self_type_id);
});
types::ScopeId const enum_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((__jakt_format((StringView::from_string_literal("enum({})"sv)),((parsed_record).name)))),false))));
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(enum_scope_id))));
(((scope)->namespace_name) = ((parsed_record).name));
TRY((((*this).add_enum_to_scope(scope_id,((parsed_record).name),enum_id,((parsed_record).name_span)))));
types::TypeId const underlying_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();NonnullRefPtr<typename parser::ParsedType> const& underlying_type = __jakt_match_value.underlying_type;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_typename(underlying_type,scope_id,JaktInternal::OptionalNone())))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } ));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool const is_boxed = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::CheckedField> checked_fields = (TRY((DynamicArray<types::CheckedField>::create_with({}))));
JaktInternal::Set<DeprecatedString> seen_fields = (TRY((Set<DeprecatedString>::create_with_values({}))));
if (((((parsed_record).record_type)).index() == 3 /* SumEnum */)){
JaktInternal::DynamicArray<parser::ParsedField> const fields = ((((parsed_record).record_type)).get<parser::RecordType::SumEnum>()).fields;
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField field = (_magic_value.value());
{
parser::ParsedVarDecl const var_decl = ((field).var_decl);
if (((seen_fields).contains(((var_decl).name)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Field '{}' is defined more than once"sv)),((var_decl).name)))),((var_decl).span)))));
continue;
}
TRY((((seen_fields).add(((var_decl).name)))));
types::TypeId const type_id = TRY((((*this).typecheck_typename(((var_decl).parsed_type),enum_scope_id,((var_decl).name)))));
NonnullRefPtr<types::CheckedVariable> const checked_var = TRY((types::CheckedVariable::__jakt_create(((var_decl).name),type_id,((var_decl).is_mutable),((var_decl).span),((((var_decl).parsed_type))->span()),TRY((((*this).typecheck_visibility(((field).visibility),enum_scope_id)))),JaktInternal::OptionalNone(),((var_decl).external_name))));
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> default_value = JaktInternal::OptionalNone();
if (((((field).default_value)).has_value())){
(default_value = TRY((((*this).typecheck_expression((((field).default_value).value()),enum_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,type_id)))));
}
if ((((*this).dump_type_hints) && ((((var_decl).parsed_type))->index() == 13 /* Empty */))){
TRY((((*this).dump_type_hint(type_id,((var_decl).span)))));
}
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const variable_id = TRY((((module)->add_variable(checked_var))));
TRY((((checked_fields).push(types::CheckedField(variable_id,default_value,((field).default_value))))));
}

}
}

}
NonnullRefPtr<types::Module> module = ((*this).current_module());
(((((module)->enums))[((enum_id).id)]) = types::CheckedEnum(((parsed_record).name),((parsed_record).name_span),(TRY((DynamicArray<types::CheckedGenericParameter>::create_with({})))),(TRY((DynamicArray<types::CheckedEnumVariant>::create_with({})))),checked_fields,enum_scope_id,((parsed_record).definition_linkage),(TRY((Dictionary<DeprecatedString, JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>::create_with_entries({})))),((parsed_record).record_type),underlying_type_id,enum_type_id,is_boxed));
JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters = ((((((module)->enums))[((enum_id).id)])).generic_parameters);
TRY((((generic_parameters).ensure_capacity(((((parsed_record).generic_parameters)).size())))));
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((parsed_record).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter gen_parameter = (_magic_value.value());
{
types::TypeId const parameter_type_id = types::TypeId(((*this).current_module_id),((((((*this).current_module()))->types)).size()));
types::CheckedGenericParameter checked_param = TRY((types::CheckedGenericParameter::make(parameter_type_id,((gen_parameter).span))));
JaktInternal::DynamicArray<types::TypeId> trait_implementations = (TRY((DynamicArray<types::TypeId>::create_with({}))));
TRY((((((module)->types)).push(TRY((types::Type::template __jakt_create<typename types::Type::TypeVariable>(((gen_parameter).name),trait_implementations)))))));
if (((((gen_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((gen_parameter).requires_list).value()),((((checked_param).constraints))),((trait_implementations)),scope_id))));
}
TRY((((generic_parameters).push(checked_param))));
TRY((((*this).add_type_to_scope(enum_scope_id,((gen_parameter).name),parameter_type_id,((gen_parameter).span)))));
}

}
}

if (((((parsed_record).implements_list)).has_value())){
TRY((((*this).fill_trait_implementation_list((((parsed_record).implements_list).value()),((((((((module)->enums))[((enum_id).id)])).trait_implementations))),enum_scope_id,JaktInternal::OptionalNone()))));
}
}
return {};
}

ErrorOr<void> typechecker::Typechecker::check_member_access(types::ScopeId const accessor,types::ScopeId const accessee,NonnullRefPtr<types::CheckedVariable> const member,utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((member)->visibility);
switch(__jakt_match_variant.index()) {
case 1: {
{
if ((!(TRY((((*this).scope_can_access(accessor,accessee))))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Can't access field ‘{}’, because it is marked private"sv)),((member)->name)))),span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedVisibility::Restricted>();JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> const& scopes = __jakt_match_value.scopes;
{
TRY((((*this).check_restricted_access(accessor,TRY(DeprecatedString::from_utf8("field"sv)),accessee,((member)->name),scopes,span))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return {};
}

bool typechecker::Typechecker::is_integer(types::TypeId const type_id) const {
{
return ((((*this).program))->is_integer(type_id));
}
}

ErrorOr<bool> typechecker::Typechecker::signatures_match(types::TypeId const self_type_id,NonnullRefPtr<types::CheckedFunction> const first,NonnullRefPtr<types::CheckedFunction> const second) {
{
Function<ErrorOr<bool>(typechecker::Typechecker&, types::TypeId, types::TypeId)> const types_match = [self_type_id](typechecker::Typechecker& typechecker, types::TypeId a, types::TypeId b) -> ErrorOr<bool> {
{
types::TypeId const mapped_a = TRY((((((((typechecker))).generic_inferences)).map(a))));
types::TypeId const mapped_b = TRY((((((((typechecker))).generic_inferences)).map(b))));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *((((typechecker))).get_type(mapped_a));
switch(__jakt_match_variant.index()) {
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((((typechecker))).implements_trait(mapped_b,id,JaktInternal::OptionalNone())))));
};/*case end*/
case 30: {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_452; {
bool const old_ignore_errors = ((((typechecker))).ignore_errors);
(((((typechecker))).ignore_errors) = true);
ScopeGuard __jakt_var_453([&] {
{
(((((typechecker))).ignore_errors) = old_ignore_errors);
(((((typechecker))).had_an_error) = false);
}

});
__jakt_var_452 = TRY((((((typechecker))).check_types_for_compat(self_type_id,mapped_b,((((((typechecker))).generic_inferences))),utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)))))); goto __jakt_label_411;

}
__jakt_label_411:; __jakt_var_452.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((((typechecker))).implements_trait(mapped_b,id,args)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_454; {
bool const old_ignore_errors = ((((typechecker))).ignore_errors);
(((((typechecker))).ignore_errors) = true);
ScopeGuard __jakt_var_455([&] {
{
(((((typechecker))).ignore_errors) = old_ignore_errors);
(((((typechecker))).had_an_error) = false);
}

});
__jakt_var_454 = TRY((((((typechecker))).check_types_for_compat(mapped_a,mapped_b,((((((typechecker))).generic_inferences))),utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)))))); goto __jakt_label_412;

}
__jakt_label_412:; __jakt_var_454.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
;
if (TRY((types_match(((*this)),((first)->return_type_id),((second)->return_type_id))))){
if ((((first)->can_throw) == ((second)->can_throw))){
if ((((((first)->params)).size()) == ((((second)->params)).size()))){
size_t arg_start = static_cast<size_t>(0ULL);
if (TRY((((first)->is_static())))){
if (TRY((((second)->is_static())))){
}
else {
return false;
}

}
else {
if ((!(TRY((((second)->is_static())))))){
if ((TRY((((first)->is_mutating()))) == TRY((((second)->is_mutating()))))){
(arg_start = static_cast<size_t>(1ULL));
}
else {
return false;
}

}
else {
return false;
}

}

{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(arg_start),static_cast<size_t>(((((first)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (TRY((types_match(((*this)),((((((((first)->params))[i])).variable))->type_id),((((((((second)->params))[i])).variable))->type_id))))){
}
else {
return false;
}

}

}
}

return true;
}
else {
return false;
}

}
else {
return false;
}

}
else {
return false;
}

}
}

ErrorOr<NonnullRefPtr<typename types::Type>> typechecker::Typechecker::unwrap_type_from_optional_if_needed(NonnullRefPtr<typename types::Type> const type) const {
{
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
if (((type)->index() == 19 /* GenericInstance */)){
types::StructId const id = ((type)->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((type)->get<types::Type::GenericInstance>()).args;
if (((id).equals(optional_struct_id))){
return ((*this).get_type(((args)[static_cast<i64>(0LL)])));
}
}
return type;
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_guard(NonnullRefPtr<typename parser::ParsedExpression> const expr,parser::ParsedBlock const else_block,parser::ParsedBlock const remaining_code,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
bool seen_scope_exit = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedStatement>> _magic = ((((else_block).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedStatement> statement = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 10: {
{
(seen_scope_exit = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
{
(seen_scope_exit = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12: {
{
(seen_scope_exit = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13: {
{
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

types::CheckedBlock const checked_else_block = TRY((((*this).typecheck_block(else_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((!(seen_scope_exit)) && ((((checked_else_block).control_flow)).may_return()))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Else block of guard must either `return`, `break`, `continue`, or `throw`"sv)),span))));
}
JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings(expr,JaktInternal::OptionalNone(),remaining_code,TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::Block>(else_block,span))),scope_id,span))));
NonnullRefPtr<typename parser::ParsedExpression> const new_condition = ((new_condition_new_then_block_new_else_statement_).template get<0>());
JaktInternal::Optional<parser::ParsedBlock> const new_then_block = ((new_condition_new_then_block_new_else_statement_).template get<1>());
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const new_else_statement = ((new_condition_new_then_block_new_else_statement_).template get<2>());

NonnullRefPtr<typename types::CheckedExpression> const checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Condition must be a boolean expression"sv)),((new_condition)->span())))));
}
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block((new_then_block.value()),scope_id,safety_mode,JaktInternal::OptionalNone()))));
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> checked_else = JaktInternal::OptionalNone();
if (((new_else_statement).has_value())){
(checked_else = TRY((((*this).typecheck_statement((new_else_statement.value()),scope_id,safety_mode,JaktInternal::OptionalNone())))));
}
if (((((checked_block).yielded_type)).has_value())){
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Yield>(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Match>(checked_condition,(TRY((DynamicArray<types::CheckedMatchCase>::create_with({ types::CheckedMatchCase { typename types::CheckedMatchCase::Expression((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Boolean>(true,span))), types::CheckedMatchBody { typename types::CheckedMatchBody::Expression(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Block>(checked_block,span,(((checked_block).yielded_type).value()))))) } ,span) } ,  types::CheckedMatchCase { typename types::CheckedMatchCase::CatchAll((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),false, types::CheckedMatchBody { typename types::CheckedMatchBody::Block(checked_else_block) } ,span) } })))),span,(((checked_block).yielded_type).value()),false))),span)));
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::If>(checked_condition,checked_block,checked_else,span)));
}
}

NonnullRefPtr<typename types::Type> typechecker::Typechecker::get_type(types::TypeId const id) const {
{
return ((((*this).program))->get_type(id));
}
}

ErrorOr<bool> typechecker::Typechecker::add_trait_to_scope(types::ScopeId const scope_id,DeprecatedString const trait_name,types::TraitId const trait_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::TraitId> const found_trait_id = ((((scope)->traits)).get(trait_name));
if ((((found_trait_id).has_value()) && (!((((found_trait_id.value())).equals(trait_id)))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Redefinition of trait ‘{}’"sv)),trait_name))),span))));
return false;
}
TRY((((((scope)->traits)).set(trait_name,trait_id))));
return true;
}
}

ErrorOr<JaktInternal::Optional<types::ScopeId>> typechecker::Typechecker::scope_lifetime_union(JaktInternal::Optional<types::ScopeId> const first,JaktInternal::Optional<types::ScopeId> const second) const {
{
if (((!(((first).has_value()))) || (!(((second).has_value()))))){
return JaktInternal::OptionalNone();
}
types::ScopeId const first_id = (first.value());
types::ScopeId const second_id = (second.value());
if (((first_id).equals(((*this).root_scope_id())))){
return second_id;
}
if (((second_id).equals(((*this).root_scope_id())))){
return first_id;
}
{
JaktInternal::Optional<types::ScopeId> scope_id = static_cast<JaktInternal::Optional<types::ScopeId>>(first_id);
while (((scope_id).has_value())){
if ((((scope_id.value())).equals(second_id))){
return first_id;
}
(scope_id = ((TRY((((*this).get_scope((scope_id.value()))))))->parent));
}
}

{
JaktInternal::Optional<types::ScopeId> scope_id = static_cast<JaktInternal::Optional<types::ScopeId>>(second_id);
while (((scope_id).has_value())){
if ((((scope_id.value())).equals(first_id))){
return second_id;
}
(scope_id = ((TRY((((*this).get_scope((scope_id.value()))))))->parent));
}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_destructuring_assignment(JaktInternal::DynamicArray<parser::ParsedVarDecl> const vars,NonnullRefPtr<typename parser::ParsedStatement> const var_decl,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> var_decls = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({}))));
NonnullRefPtr<typename types::CheckedStatement> const checked_tuple_var_decl = TRY((((*this).typecheck_statement(var_decl,scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::TypeId expr_type_id = types::unknown_type_id();
types::VarId tuple_var_id = types::VarId(types::ModuleId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL));
if (((checked_tuple_var_decl)->index() == 3 /* VarDecl */)){
types::VarId const var_id = ((checked_tuple_var_decl)->get<types::CheckedStatement::VarDecl>()).var_id;
NonnullRefPtr<typename types::CheckedExpression> const init = ((checked_tuple_var_decl)->get<types::CheckedStatement::VarDecl>()).init;
(expr_type_id = ((init)->type()));
(tuple_var_id = var_id);
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Destructuting assignment should be a variable declaration"sv)),span))));
}

JaktInternal::DynamicArray<types::TypeId> inner_types = (TRY((DynamicArray<types::TypeId>::create_with({}))));
NonnullRefPtr<typename types::Type> const tuple_type = ((*this).get_type(expr_type_id));
if (((tuple_type)->index() == 19 /* GenericInstance */)){
JaktInternal::DynamicArray<types::TypeId> const args = ((tuple_type)->get<types::Type::GenericInstance>()).args;
(inner_types = args);
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Tuple Type should be Generic Instance"sv)),span))));
}

NonnullRefPtr<types::CheckedVariable> const tuple_variable = ((((*this).program))->get_variable(tuple_var_id));
if ((((vars).size()) == ((inner_types).size()))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vars).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedVarDecl new_var = ((vars)[i]);
(((new_var).parsed_type) = TRY((parser::ParsedType::template __jakt_create<typename parser::ParsedType::Name>(TRY((((*this).type_name(((inner_types)[i]),false)))),span))));
NonnullRefPtr<typename parser::ParsedExpression> const init = TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::IndexedTuple>(TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::Var>(((tuple_variable)->name),span))),i,false,span)));
TRY((((var_decls).push(TRY((((*this).typecheck_var_decl(((vars)[i]),init,scope_id,safety_mode,span))))))));
}

}
}

}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Tuple inner types sould have same size as tuple members"sv)),span))));
}

return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::DestructuringAssignment>(var_decls,checked_tuple_var_decl,span)));
}
}

ErrorOr<bool> typechecker::Typechecker::is_scope_directly_accessible_from(types::ScopeId const scope_id,types::ScopeId const from_scope_id) const {
{
return TRY((((((*this).program))->is_scope_directly_accessible_from(scope_id,from_scope_id))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_default_fields(parser::ParsedRecord const parsed_record,types::StructId const struct_id,types::ScopeId const scope_id) {
{
types::CheckedStruct structure = ((*this).get_struct(struct_id));
types::ScopeId const checked_struct_scope_id = ((structure).scope_id);
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(struct_id)))))));
JaktInternal::Optional<types::TypeId> const previous_struct_type_id = ((*this).current_struct_type_id);
(((*this).current_struct_type_id) = struct_type_id);
ScopeGuard __jakt_var_456([&] {
{
(((*this).current_struct_type_id) = previous_struct_type_id);
}

});
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = struct_type_id);
ScopeGuard __jakt_var_457([&] {
(((*this).self_type_id) = old_self_type_id);
});
JaktInternal::DynamicArray<parser::ParsedField> const parsed_fields = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<parser::ParsedField>, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();JaktInternal::DynamicArray<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();JaktInternal::DynamicArray<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("typecheck_struct_default_fields cannot handle non-structs"sv))))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
i64 index = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((parsed_fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField unchecked_member = (_magic_value.value());
{
ScopeGuard __jakt_var_458([&] {
({auto& _jakt_ref = index;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, static_cast<i64>(1LL));});
});
if (((!(((((unchecked_member).default_value)).has_value()))) || ((((((((structure).fields))[index])).default_value)).has_value()))){
continue;
}
(((((((structure).fields))[index])).default_value) = TRY((((*this).typecheck_expression((((unchecked_member).default_value).value()),checked_struct_scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone())))));
}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_constructors(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
JaktInternal::DynamicArray<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
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
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find previously added struct"sv))))));
}
TRY((((*this).typecheck_struct_constructor(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((record).name)))));
if ((!(((struct_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find previously added struct"sv))))));
}
TRY((((*this).typecheck_struct_constructor(record,(struct_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find previously added enum"sv))))));
}
TRY((((*this).typecheck_enum_constructor(record,(enum_id.value()),scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((record).name)))));
if ((!(((enum_id).has_value())))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find previously added enum"sv))))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_block_statement(parser::ParsedBlock const parsed_block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(parsed_block,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("A block used as a statement cannot yield values, as the value cannot be observed in any way"sv)),(((parsed_block).find_yield_span()).value())))));
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Block>(checked_block,span)));
}
}

ErrorOr<types::FunctionId> typechecker::Typechecker::typecheck_function_predecl(parser::ParsedFunction const parsed_function,types::ScopeId const parent_scope_id,JaktInternal::Optional<types::TypeId> const this_arg_type_id,JaktInternal::Optional<NonnullRefPtr<types::FunctionGenerics>> generics) {
{
types::ScopeId const function_scope_id = TRY((((*this).create_scope(parent_scope_id,((parsed_function).can_throw),TRY((__jakt_format((StringView::from_string_literal("fn({})"sv)),((parsed_function).name)))),true))));
DeprecatedString const scope_debug_name = TRY((__jakt_format((StringView::from_string_literal("function-block({})"sv)),((parsed_function).name))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(function_scope_id,((parsed_function).can_throw),scope_debug_name,true))));
size_t const module_id = ((((*this).current_module_id)).id);
bool base_definition = false;
if ((!(((generics).has_value())))){
(generics = TRY((types::FunctionGenerics::__jakt_create(function_scope_id,(TRY((DynamicArray<types::CheckedParameter>::create_with({})))),(TRY((DynamicArray<types::FunctionGenericParameter>::create_with({})))),(TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))))))));
(base_definition = true);
}
bool const is_generic_function = (!(((((parsed_function).generic_parameters)).is_empty())));
bool const is_generic = (is_generic_function || (((this_arg_type_id).has_value()) && ((((*this).get_type((this_arg_type_id.value()))))->index() == 19 /* GenericInstance */)));
NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::__jakt_create(((parsed_function).name),((parsed_function).name_span),TRY((((*this).typecheck_visibility(((parsed_function).visibility),parent_scope_id)))),types::unknown_type_id(),((parsed_function).return_type_span),(TRY((DynamicArray<types::CheckedParameter>::create_with({})))),(generics.value()),types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),((parsed_function).can_throw),((parsed_function).type),((parsed_function).linkage),function_scope_id,JaktInternal::OptionalNone(),((!(is_generic)) || (!(base_definition))),parsed_function,((parsed_function).is_comptime),false,false,((parsed_function).is_unsafe),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),((parsed_function).external_name),((parsed_function).deprecated_message),JaktInternal::OptionalNone())));
NonnullRefPtr<types::Module> current_module = ((*this).current_module());
types::FunctionId const function_id = TRY((((current_module)->add_function(checked_function))));
types::ScopeId const checked_function_scope_id = ((checked_function)->function_scope_id);
bool const external_linkage = ((((parsed_function).linkage)).index() == 1 /* External */);
JaktInternal::Optional<types::ScopeId> const check_scope = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::ScopeId>,ErrorOr<types::FunctionId>>{
auto __jakt_enum_value = ((is_generic || ((((parsed_function).return_type))->index() == 13 /* Empty */)));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::ScopeId>>(TRY((((*this).create_scope(parent_scope_id,((parsed_function).can_throw),scope_debug_name,true))))));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((parsed_function).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter generic_parameter = (_magic_value.value());
{
types::TypeId type_var_type_id = types::TypeId(((current_module)->id),((((current_module)->types)).size()));
if (base_definition){
types::FunctionGenericParameter parameter = TRY((types::FunctionGenericParameter::parameter(type_var_type_id,((generic_parameter).span))));
JaktInternal::DynamicArray<types::TypeId> trait_implementations = (TRY((DynamicArray<types::TypeId>::create_with({}))));
TRY((((((current_module)->types)).push(TRY((types::Type::template __jakt_create<typename types::Type::TypeVariable>(((generic_parameter).name),trait_implementations)))))));
if (((((generic_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((generic_parameter).requires_list).value()),((((((parameter).checked_parameter)).constraints))),((trait_implementations)),parent_scope_id))));
}
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
JaktInternal::Optional<parser::ParsedParameter> const _magic_value = ((_magic).next());
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

if (((((parsed_function).stores_arguments)).has_value())){
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>> _magic = (((((parsed_function).stores_arguments).value())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel> index_____ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel> const jakt__index_____ = index_____;
size_t const index = ((jakt__index_____).template get<0>());
parser::ArgumentStoreLevel const _ = ((jakt__index_____).template get<1>());

if ((index >= ((((checked_function)->params)).size()))){
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("stores_argument() index out of bounds"sv))))));
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<types::FunctionId>>{
auto&& __jakt_match_variant = *((*this).get_type(((((((((checked_function)->params))[index])).variable))->type_id)));
switch(__jakt_match_variant.index()) {
case 27: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("This parameter is not a reference"sv)),((((((((checked_function)->params))[index])).variable))->definition_span),TRY(DeprecatedString::from_utf8("stores_argument() may only be used to declare reference lifetime requirements"sv)),((((((((checked_function)->params))[index])).variable))->definition_span)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

}
(((checked_function)->stores_arguments) = ((parsed_function).stores_arguments));
types::TypeId function_return_type_id = TRY((((*this).typecheck_typename(((parsed_function).return_type),checked_function_scope_id,JaktInternal::OptionalNone()))));
if (((((parsed_function).return_type))->index() == 13 /* Empty */)){
if (((parsed_function).is_fat_arrow)){
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::CheckedBlock const block = TRY((((*this).typecheck_block(((parsed_function).block),(check_scope.value()), types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
if (((*this).had_an_error)){
(function_return_type_id = types::void_type_id());
(((*this).ignore_errors) = false);
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Can't infer the return type of this function"sv)),((parsed_function).return_type_span),TRY(DeprecatedString::from_utf8("Try adding an explicit return type to the function here"sv)),((parsed_function).return_type_span)))));
}
else {
(function_return_type_id = ((*this).infer_function_return_type(block)));
}

(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
}
else {
(function_return_type_id = types::void_type_id());
}

}
(((checked_function)->return_type_id) = function_return_type_id);
TRY((((*this).check_that_type_doesnt_contain_reference(function_return_type_id,((parsed_function).return_type_span)))));
if (((!(((((parsed_function).generic_parameters)).is_empty()))) && ((function_return_type_id).equals(types::unknown_type_id())))){
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::CheckedBlock const block = TRY((((*this).typecheck_block(((parsed_function).block),(check_scope.value()), types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
types::TypeId const return_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId,ErrorOr<types::FunctionId>>{
auto __jakt_enum_value = (((function_return_type_id).equals(types::unknown_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((*this).infer_function_return_type(block)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((*this).resolve_type_var(function_return_type_id,parent_scope_id)))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((checked_function)->block) = block);
(((checked_function)->return_type_id) = return_type_id);
}
TRY((((*this).add_function_to_scope(parent_scope_id,((parsed_function).name),(TRY((DynamicArray<types::FunctionId>::create_with({function_id})))),((parsed_function).name_span)))));
return function_id;
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::find_or_add_type_id(NonnullRefPtr<typename types::Type> const type) {
{
return TRY((((((*this).program))->find_or_add_type_id(type,((*this).current_module_id)))));
}
}

ErrorOr<typechecker::Typechecker> typechecker::Typechecker::typecheck(NonnullRefPtr<compiler::Compiler> compiler,parser::ParsedNamespace const parsed_namespace) {
{
JaktInternal::Optional<utility::FileId> const input_file = ((compiler)->current_file);
if ((!(((input_file).has_value())))){
TRY((((compiler)->panic(TRY(DeprecatedString::from_utf8("trying to typecheck a non-existant file"sv))))));
}
DeprecatedString const true_module_name = TRY((((((((compiler)->files))[(((input_file.value())).id)])).basename(true))));
types::ModuleId const placeholder_module_id = types::ModuleId(static_cast<size_t>(0ULL));
DeprecatedString const root_module_name = TRY(((((((compiler)->current_file_path()).value())).basename(true))));
typechecker::Typechecker typechecker = typechecker::Typechecker(compiler,TRY((types::CheckedProgram::__jakt_create(compiler,(TRY((DynamicArray<NonnullRefPtr<types::Module>>::create_with({})))),(TRY((Dictionary<DeprecatedString, types::LoadedModule>::create_with_entries({}))))))),placeholder_module_id,types::TypeId::none(),JaktInternal::OptionalNone(),false,static_cast<size_t>(0ULL),false,((compiler)->dump_type_hints),((compiler)->dump_try_hints),static_cast<u64>(0ULL),types::GenericInferences((TRY((Dictionary<DeprecatedString, DeprecatedString>::create_with_entries({}))))),JaktInternal::OptionalNone(),root_module_name,false,false);
TRY((((typechecker).include_prelude())));
types::ModuleId const root_module_id = TRY((((typechecker).create_module(root_module_name,true,JaktInternal::OptionalNone()))));
(((typechecker).current_module_id) = root_module_id);
TRY((((compiler)->set_current_file((input_file.value())))));
types::LoadedModule const loaded_module = types::LoadedModule(root_module_id,(input_file.value()));
TRY((((((typechecker).program))->set_loaded_module(true_module_name,loaded_module))));
types::ScopeId const PRELUDE_SCOPE_ID = ((typechecker).prelude_scope_id());
types::ScopeId const root_scope_id = TRY((((typechecker).create_scope(PRELUDE_SCOPE_ID,false,TRY(DeprecatedString::from_utf8("root"sv)),false))));
TRY((((typechecker).typecheck_module_import(parser::ParsedModuleImport( parser::ImportName { typename parser::ImportName::Literal(TRY(DeprecatedString::from_utf8("jakt::prelude::prelude"sv)),utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))) } ,JaktInternal::OptionalNone(), parser::ImportList { typename parser::ImportList::All() } ),root_scope_id))));
TRY((((typechecker).typecheck_module(parsed_namespace,root_scope_id))));
return typechecker;
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedEnumVariantBinding>>> typechecker::Typechecker::typecheck_enum_variant_bindings(types::CheckedEnumVariant const variant,JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const bindings,utility::Span const span) {
{
if (((variant).index() == 1 /* Typed */)){
types::TypeId const type_id = ((variant).get<types::CheckedEnumVariant::Typed>()).type_id;
if ((((bindings).size()) != static_cast<size_t>(1ULL))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant ‘{}’ must have exactly one argument"sv)),((variant).name())))),span))));
return JaktInternal::OptionalNone();
}
return (TRY((DynamicArray<types::CheckedEnumVariantBinding>::create_with({types::CheckedEnumVariantBinding(JaktInternal::OptionalNone(),((((bindings)[static_cast<i64>(0LL)])).binding),type_id,span)}))));
}
if (((variant).index() == 3 /* StructLike */)){
JaktInternal::DynamicArray<types::VarId> const fields = ((variant).get<types::CheckedEnumVariant::StructLike>()).fields;
JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> checked_vars = (TRY((DynamicArray<NonnullRefPtr<types::CheckedVariable>>::create_with({}))));
JaktInternal::DynamicArray<types::CheckedEnumVariantBinding> checked_enum_variant_bindings = (TRY((DynamicArray<types::CheckedEnumVariantBinding>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> const _magic_value = ((_magic).next());
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
JaktInternal::Optional<parser::EnumVariantPatternArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument binding = (_magic_value.value());
{
bool found = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedVariable>> _magic = ((checked_vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedVariable> var = (_magic_value.value());
{
DeprecatedString const binding_name = ((binding).name).value_or_lazy_evaluated([&] { return ((binding).binding); });
types::TypeId const type_id = ((var)->type_id);
if ((binding_name == ((var)->name))){
TRY((((checked_enum_variant_bindings).push(types::CheckedEnumVariantBinding(((binding).name),((binding).binding),type_id,span)))));
(found = true);
break;
}
}

}
}

if ((!(found))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant ‘{}’ doesn't have field with name ‘{}’"sv)),((variant).name()),((binding).name_in_enum())))),((binding).name_in_enum_span())))));
}
}

}
}

if ((((checked_enum_variant_bindings).size()) > static_cast<size_t>(0ULL))){
return checked_enum_variant_bindings;
}
return JaktInternal::OptionalNone();
}
else {
return JaktInternal::OptionalNone();
}

}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct(parser::ParsedRecord const record,types::StructId const struct_id,types::ScopeId const parent_scope_id) {
{
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = struct_type_id);
ScopeGuard __jakt_var_459([&] {
(((*this).self_type_id) = old_self_type_id);
});
JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>>> all_virtuals = (TRY((Dictionary<DeprecatedString, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>>>::create_with_entries({}))));
JaktInternal::Optional<types::StructId> super_struct_id = ((((*this).get_struct(struct_id))).super_struct_id);
while (((super_struct_id).has_value())){
types::CheckedStruct const super_struct = ((*this).get_struct((super_struct_id.value())));
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(((super_struct).scope_id)))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
DeprecatedString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<types::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<types::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function(function_id));
if (((function)->is_virtual)){
if ((!(((all_virtuals).contains(((function)->name)))))){
TRY(all_virtuals.set(((function)->name), (TRY((DynamicArray<NonnullRefPtr<types::CheckedFunction>>::create_with({function}))))));
}
else {
TRY((((((all_virtuals)[((function)->name)])).push(function))));
}

}
}

}
}

}

}
}

(super_struct_id = ((super_struct).super_struct_id));
}
typechecker::TraitImplCheck checks = TRY((typechecker::TraitImplCheck::make()));
{
JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const trait_implementations = ((((*this).get_struct(struct_id))).trait_implementations);
TRY((((checks).ensure_capacity(((trait_implementations).size())))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> _magic = ((trait_implementations).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> trait_name__trait_id_and_generic_params__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const jakt__trait_name__trait_id_and_generic_params__ = trait_name__trait_id_and_generic_params__;
DeprecatedString const trait_name = ((jakt__trait_name__trait_id_and_generic_params__).template get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>> const trait_id_and_generic_params = ((jakt__trait_name__trait_id_and_generic_params__).template get<1>());

TRY((((checks).register_trait(((trait_id_and_generic_params).template get<0>()),trait_name,((((((*this).program))->get_trait(((trait_id_and_generic_params).template get<0>()))))->methods)))));
}

}
}

}

{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
TRY((((*this).typecheck_override(method,((((*this).get_struct(struct_id))).scope_id),all_virtuals))));
TRY((((*this).typecheck_method(((method).parsed_function), types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id) } ))));
}

}
}

{
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(true))));
ScopeGuard __jakt_var_460([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const trait_implementations = ((((*this).get_struct(struct_id))).trait_implementations);
TRY((((checks).ensure_capacity(((trait_implementations).size())))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> _magic = ((trait_implementations).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> trait_name__trait_id_and_generic_params__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const jakt__trait_name__trait_id_and_generic_params__ = trait_name__trait_id_and_generic_params__;
DeprecatedString const trait_name = ((jakt__trait_name__trait_id_and_generic_params__).template get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>> const trait_id_and_generic_params = ((jakt__trait_name__trait_id_and_generic_params__).template get<1>());

JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>> const trait_id_generic_params_ = trait_id_and_generic_params;
types::TraitId const trait_id = ((trait_id_generic_params_).template get<0>());
JaktInternal::DynamicArray<types::TypeId> const generic_params = ((trait_id_generic_params_).template get<1>());

NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait(trait_id));
if ((((((trait_)->generic_parameters)).size()) != ((generic_params).size()))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Trait ‘{}’ expects {} generic parameters, but {} were given"sv)),trait_name,((((trait_)->generic_parameters)).size()),((generic_params).size())))),((trait_)->name_span)))));
continue;
}
TRY((((*this).specialize_trait(trait_id,generic_params))));
}

}
}

NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(((((*this).get_struct(struct_id))).scope_id)))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> name__overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> const jakt__name__overload_set__ = name__overload_set__;
DeprecatedString const name = ((jakt__name__overload_set__).template get<0>());
JaktInternal::DynamicArray<types::FunctionId> const overload_set = ((jakt__name__overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<types::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId function_id = (_magic_value.value());
{
TRY((((checks).register_method(struct_type_id,name,function_id,((*this))))));
}

}
}

}

}
}

}

TRY((((checks).throw_errors(((((*this).get_struct(struct_id))).name_span),((*this))))));
(((*this).current_struct_type_id) = JaktInternal::OptionalNone());
}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_lambda(JaktInternal::DynamicArray<parser::ParsedCapture> const captures,JaktInternal::DynamicArray<parser::ParsedParameter> const params,bool const can_throw,bool const is_fat_arrow,NonnullRefPtr<typename parser::ParsedType> const return_type,parser::ParsedBlock const block,utility::Span const span,types::ScopeId const scope_id,types::SafetyMode const safety_mode) {
{
NonnullRefPtr<typename parser::ParsedType> const synthetic_type = TRY((parser::ParsedType::template __jakt_create<typename parser::ParsedType::Function>(params,can_throw,return_type,span)));
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_461([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
types::TypeId type_id = TRY((((*this).typecheck_typename(synthetic_type,scope_id,JaktInternal::OptionalNone()))));
JaktInternal::Tuple<types::TypeId,types::FunctionId> return_type_id_pseudo_function_id_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<types::TypeId,types::FunctionId>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();types::TypeId const& return_type_id = __jakt_match_value.return_type_id;
types::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue((Tuple{return_type_id, pseudo_function_id}));
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("Expected the just-checked function to be of a function type"sv))))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::TypeId return_type_id = ((return_type_id_pseudo_function_id_).template get<0>());
types::FunctionId pseudo_function_id = ((return_type_id_pseudo_function_id_).template get<1>());

NonnullRefPtr<types::Module> module = ((*this).current_module());
types::ScopeId effective_namespace_parent_scope_id = scope_id;
NonnullRefPtr<types::Scope> effective_namespace_parent_scope = TRY((((*this).get_scope(scope_id))));
while (((effective_namespace_parent_scope)->is_block_scope)){
(effective_namespace_parent_scope_id = (((effective_namespace_parent_scope)->parent).value()));
(effective_namespace_parent_scope = TRY((((*this).get_scope(effective_namespace_parent_scope_id)))));
}
types::ScopeId lambda_scope_id = TRY((((*this).create_scope(effective_namespace_parent_scope_id,can_throw,TRY(DeprecatedString::from_utf8("lambda"sv)),true))));
bool is_capturing_everything = false;
JaktInternal::DynamicArray<types::CheckedCapture> checked_captures = (TRY((DynamicArray<types::CheckedCapture>::create_with({}))));
bool has_dependent_capture = false;
{
JaktInternal::ArrayIterator<parser::ParsedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedCapture> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedCapture capture = (_magic_value.value());
{
if (((capture).index() == 4 /* AllByReference */)){
TRY((((checked_captures).push( types::CheckedCapture { typename types::CheckedCapture::AllByReference(TRY(DeprecatedString::from_utf8(""sv)),((capture).span())) } ))));
if ((!(is_capturing_everything))){
(is_capturing_everything = true);
(lambda_scope_id = TRY((((*this).create_scope(scope_id,can_throw,TRY(DeprecatedString::from_utf8("lambda"sv)),true)))));
}
}
else if (((TRY((((*this).find_var_in_scope(scope_id,((capture).name())))))).has_value())){
DeprecatedString const name = ((capture).name());
utility::Span const span = ((capture).span());
TRY((((checked_captures).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedCapture, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = capture;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue( types::CheckedCapture { typename types::CheckedCapture::ByValue(name,span) } );
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue( types::CheckedCapture { typename types::CheckedCapture::ByReference(name,span) } );
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue( types::CheckedCapture { typename types::CheckedCapture::ByMutableReference(name,span) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(({ Optional<types::CheckedCapture> __jakt_var_462; {
(has_dependent_capture = true);
if ((!(((*this).in_comptime_function_call)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Comptime dependency capture ‘{}’ is only allowed in comptime function calls"sv)),name))),span))));
}
__jakt_var_462 =  types::CheckedCapture { typename types::CheckedCapture::ByComptimeDependency(name,span) } ; goto __jakt_label_413;

}
__jakt_label_413:; __jakt_var_462.release_value(); }));
};/*case end*/
case 4: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("AllByReference capture should not be looked up by name"sv))))));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
})))));
if ((!(is_capturing_everything))){
NonnullRefPtr<types::CheckedVariable> const var = (TRY((((*this).find_var_in_scope(scope_id,((capture).name()))))).value());
bool const is_this = (((var)->name) == TRY(DeprecatedString::from_utf8("this"sv)));
types::VarId const var_id = TRY((((module)->add_variable(TRY((types::CheckedVariable::__jakt_create(name,((var)->type_id),(((var)->is_mutable) && ((is_this || ((capture).index() == 1 /* ByReference */)) || ((capture).index() == 2 /* ByMutableReference */))),((var)->definition_span),((var)->type_span),((var)->visibility),((var)->owner_scope),JaktInternal::OptionalNone())))))));
TRY((((*this).add_var_to_scope(lambda_scope_id,name,var_id,span))));
}
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Variable '{}' not found"sv)),((capture).name())))),span))));
}

}

}
}

if ((!(is_capturing_everything))){
types::ScopeId current_scope_id = scope_id;
NonnullRefPtr<types::Scope> lambda_scope = TRY((((*this).get_scope(lambda_scope_id))));
while ((!(((current_scope_id).equals(effective_namespace_parent_scope_id))))){
NonnullRefPtr<types::Scope> const current_scope = TRY((((*this).get_scope(current_scope_id))));
TRY((((((lambda_scope)->resolution_mixins)).push(current_scope_id))));
(current_scope_id = (((current_scope)->parent).value()));
}
}
JaktInternal::DynamicArray<types::CheckedParameter> checked_params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
bool first = true;
{
JaktInternal::ArrayIterator<parser::ParsedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedParameter param = (_magic_value.value());
{
types::CheckedParameter const checked_param = TRY((((*this).typecheck_parameter(param,scope_id,first,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
TRY((((checked_params).push(checked_param))));
types::VarId const var_id = TRY((((module)->add_variable(((checked_param).variable)))));
TRY((((*this).add_var_to_scope(lambda_scope_id,((((checked_param).variable))->name),var_id,((((checked_param).variable))->definition_span)))));
(first = false);
}

}
}

JaktInternal::Optional<types::FunctionId> const previous_function_id = ((*this).current_function_id);
(((*this).current_function_id) = pseudo_function_id);
ScopeGuard __jakt_var_463([&] {
{
(((*this).current_function_id) = previous_function_id);
}

});
if (has_dependent_capture){
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::DependentFunction>(checked_captures,checked_params,can_throw,return_type_id,block,span,type_id,pseudo_function_id,lambda_scope_id)));
}
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block(block,lambda_scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((return_type_id).equals(types::unknown_type_id()))){
bool return_type_updated = false;
if (((!(is_fat_arrow)) && ((return_type)->index() == 13 /* Empty */))){
(return_type_id = types::void_type_id());
(return_type_updated = true);
}
else if ((is_fat_arrow && ((!(((((checked_block).statements)).is_empty()))) && (((((((checked_block).statements)).last()).value()))->index() == 8 /* Return */)))){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const val = (((((((checked_block).statements)).last()).value()))->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
(return_type_id = TRY((((*this).resolve_type_var((((val.value()))->type()),lambda_scope_id)))));
(return_type_updated = true);
}
}
if (return_type_updated){
(type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::DynamicArray<types::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
types::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Function>(params,can_throw,return_type_id,pseudo_function_id))))))));
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("Expected the just-checked function to be of a function type"sv))))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
}
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Function>(checked_captures,checked_params,can_throw,return_type_id,checked_block,span,type_id,pseudo_function_id,lambda_scope_id)));
}
}

NonnullRefPtr<types::CheckedVariable> typechecker::Typechecker::get_variable(types::VarId const id) const {
{
return ((((*this).program))->get_variable(id));
}
}

ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename types::CheckedExpression>>>> typechecker::Typechecker::resolve_default_params(JaktInternal::DynamicArray<types::CheckedParameter> const params,JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const args,types::ScopeId const scope_id,types::SafetyMode const safety_mode,size_t const arg_offset,utility::Span const span) {
{
size_t params_with_default_value = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
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
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename types::CheckedExpression>>> resolved_args = (TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(arg_offset),static_cast<size_t>(((params).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedParameter const param = ((params)[i]);
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> maybe_checked_expr = JaktInternal::OptionalNone();
if ((!(((param).requires_label)))){
if ((((args).size()) <= consumed_arg)){
if ((!(((((param).default_value)).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Missing argument for function parameter {}"sv)),((((param).variable))->name)))),span))));
continue;
}
(maybe_checked_expr = ((param).default_value));
}
else {
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> const name_span_expr_ = ((args)[consumed_arg]);
DeprecatedString const name = ((name_span_expr_).template get<0>());
utility::Span const span = ((name_span_expr_).template get<1>());
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((name_span_expr_).template get<2>());

if (((!(((name).is_empty()))) && (name != ((((param).variable))->name)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Wrong parameter name in argument label (got '{}', expected '{}')"sv)),name,((((param).variable))->name)))),span))));
}
(maybe_checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,((((param).variable))->type_id))))));
((consumed_arg++));
}

}
else {
(maybe_checked_expr = ((param).default_value));
if ((((args).size()) > consumed_arg)){
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> const name_span_expr_ = ((args)[consumed_arg]);
DeprecatedString const name = ((name_span_expr_).template get<0>());
utility::Span const span = ((name_span_expr_).template get<1>());
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((name_span_expr_).template get<2>());

if (TRY((((*this).validate_argument_label(param,name,span,expr,maybe_checked_expr))))){
(maybe_checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,((((param).variable))->type_id))))));
((consumed_arg++));
}
}
}

if (((maybe_checked_expr).has_value())){
NonnullRefPtr<typename types::CheckedExpression> checked_arg = (maybe_checked_expr.value());
TRY((((resolved_args).push((Tuple{((((param).variable))->name), span, checked_arg})))));
}
}

}
}

return resolved_args;
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Wrong number of arguments"sv)),span))));
return (TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
}

}
}

ErrorOr<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>> typechecker::Typechecker::find_all_implementations_of_trait(types::TypeId const type_id,types::TraitId const trait_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>, ErrorOr<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>> __jakt_var_464; {
types::CheckedStruct const struct_ = ((*this).get_struct(struct_id));
JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>> implementations = (TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> _magic = ((((struct_).trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> ___trait_descriptor__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const jakt_____trait_descriptor__ = ___trait_descriptor__;
DeprecatedString const _ = ((jakt_____trait_descriptor__).template get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>> const trait_descriptor = ((jakt_____trait_descriptor__).template get<1>());

if (((((trait_descriptor).template get<0>())).equals(trait_id))){
TRY((((implementations).push(((trait_descriptor).template get<1>())))));
}
}

}
}

__jakt_var_464 = implementations; goto __jakt_label_414;

}
__jakt_label_414:; __jakt_var_464.release_value(); }));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>> __jakt_var_465; {
types::CheckedStruct const struct_ = ((*this).get_struct(struct_id));
JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>> implementations = (TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> _magic = ((((struct_).trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> ___trait_descriptor__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const jakt_____trait_descriptor__ = ___trait_descriptor__;
DeprecatedString const _ = ((jakt_____trait_descriptor__).template get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>> const trait_descriptor = ((jakt_____trait_descriptor__).template get<1>());

if (((((trait_descriptor).template get<0>())).equals(trait_id))){
TRY((((implementations).push(((trait_descriptor).template get<1>())))));
}
}

}
}

__jakt_var_465 = implementations; goto __jakt_label_415;

}
__jakt_label_415:; __jakt_var_465.release_value(); }));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>> __jakt_var_466; {
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>> implementations = (TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> _magic = ((((enum_).trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> ___trait_descriptor__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const jakt_____trait_descriptor__ = ___trait_descriptor__;
DeprecatedString const _ = ((jakt_____trait_descriptor__).template get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>> const trait_descriptor = ((jakt_____trait_descriptor__).template get<1>());

if (((((trait_descriptor).template get<0>())).equals(trait_id))){
TRY((((implementations).push(((trait_descriptor).template get<1>())))));
}
}

}
}

__jakt_var_466 = implementations; goto __jakt_label_416;

}
__jakt_label_416:; __jakt_var_466.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>> __jakt_var_467; {
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>> implementations = (TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))));
{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> _magic = ((((enum_).trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> ___trait_descriptor__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>> const jakt_____trait_descriptor__ = ___trait_descriptor__;
DeprecatedString const _ = ((jakt_____trait_descriptor__).template get<0>());
JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>> const trait_descriptor = ((jakt_____trait_descriptor__).template get<1>());

if (((((trait_descriptor).template get<0>())).equals(trait_id))){
TRY((((implementations).push(((trait_descriptor).template get<1>())))));
}
}

}
}

__jakt_var_467 = implementations; goto __jakt_label_417;

}
__jakt_label_417:; __jakt_var_467.release_value(); }));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>> __jakt_var_468; {
if (((id).equals(trait_id))){
return (TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({(TRY((DynamicArray<types::TypeId>::create_with({}))))}))));
}
__jakt_var_468 = (TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({})))); goto __jakt_label_418;

}
__jakt_label_418:; __jakt_var_468.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>> __jakt_var_469; {
if ((!(((id).equals(trait_id))))){
return (TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))));
}
__jakt_var_469 = (TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({args})))); goto __jakt_label_419;

}
__jakt_label_419:; __jakt_var_469.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>>> typechecker::Typechecker::find_namespace_in_scope(types::ScopeId const scope_id,DeprecatedString const name,bool const treat_aliases_as_imports) const {
{
return TRY((((((*this).program))->find_namespace_in_scope(scope_id,name,treat_aliases_as_imports))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_struct_fields(parser::ParsedRecord const record,types::StructId const struct_id) {
{
types::CheckedStruct structure = ((*this).get_struct(struct_id));
types::ScopeId const checked_struct_scope_id = ((((*this).get_struct(struct_id))).scope_id);
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(struct_id)))))));
(((*this).current_struct_type_id) = struct_type_id);
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = struct_type_id);
ScopeGuard __jakt_var_470([&] {
(((*this).self_type_id) = old_self_type_id);
});
JaktInternal::DynamicArray<parser::ParsedField> const parsed_fields = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<parser::ParsedField>, ErrorOr<void>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();JaktInternal::DynamicArray<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();JaktInternal::DynamicArray<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("typecheck_struct_fields cannot handle non-structs"sv))))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((parsed_fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField unchecked_member = (_magic_value.value());
{
parser::ParsedVarDecl const parsed_var_decl = ((unchecked_member).var_decl);
types::TypeId const checked_member_type = TRY((((*this).typecheck_typename(((parsed_var_decl).parsed_type),checked_struct_scope_id,((parsed_var_decl).name)))));
TRY((((*this).check_that_type_doesnt_contain_reference(checked_member_type,((((parsed_var_decl).parsed_type))->span())))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const variable_id = TRY((((module)->add_variable(TRY((types::CheckedVariable::__jakt_create(((parsed_var_decl).name),checked_member_type,((parsed_var_decl).is_mutable),((parsed_var_decl).span),JaktInternal::OptionalNone(),TRY((((*this).typecheck_visibility(((unchecked_member).visibility),checked_struct_scope_id)))),JaktInternal::OptionalNone(),((parsed_var_decl).external_name))))))));
TRY((((((structure).fields)).push(types::CheckedField(variable_id,JaktInternal::OptionalNone(),((unchecked_member).default_value))))));
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_call(parser::ParsedCall const call,types::ScopeId const caller_scope_id,utility::Span const span,JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const this_expr,JaktInternal::Optional<types::StructLikeId> const parent_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> type_hint,bool const must_be_enum_constructor) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>> args = (TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({}))));
types::TypeId return_type = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
JaktInternal::DynamicArray<types::TypeId> generic_arguments = (TRY((DynamicArray<types::TypeId>::create_with({}))));
bool callee_throws = false;
JaktInternal::DynamicArray<types::ResolvedNamespace> resolved_namespaces = (TRY((DynamicArray<types::ResolvedNamespace>::create_with({}))));
JaktInternal::DynamicArray<types::FunctionId> resolved_function_id_candidates = (TRY((DynamicArray<types::FunctionId>::create_with({}))));
JaktInternal::Optional<types::FunctionId> resolved_function_id = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> maybe_this_type_id = JaktInternal::OptionalNone();
JaktInternal::Optional<types::FunctionId> generic_checked_function_to_instantiate = JaktInternal::OptionalNone();
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_471([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((((call).namespace_)).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString name = (_magic_value.value());
{
TRY((((resolved_namespaces).push(types::ResolvedNamespace(name,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))));
}

}
}

types::ScopeId callee_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (((parent_id).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = (parent_id.value());
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_472; {
types::CheckedStruct struct_ = ((*this).get_struct(id));
types::ScopeId scope_id = ((struct_).scope_id);
while (((resolved_function_id_candidates).is_empty())){
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
(resolved_function_id_candidates = TRY((((*this).resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor)))));
(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
if ((!(((resolved_function_id_candidates).is_empty())))){
break;
}
if (((((struct_).super_struct_id)).has_value())){
types::StructId const parent_struct_id = (((struct_).super_struct_id).value());
(struct_ = ((*this).get_struct(parent_struct_id)));
(scope_id = ((struct_).scope_id));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Could not find ‘{}’"sv)),((call).name)))),span))));
break;
}

}
__jakt_var_472 = scope_id; goto __jakt_label_420;

}
__jakt_label_420:; __jakt_var_472.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_473; {
types::ScopeId const scope_id = ((((*this).get_enum(id))).scope_id);
(resolved_function_id_candidates = TRY((((*this).resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor)))));
__jakt_var_473 = scope_id; goto __jakt_label_421;

}
__jakt_label_421:; __jakt_var_473.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Trait>();
types::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_474; {
types::ScopeId const scope_id = ((((*this).get_trait(id)))->scope_id);
(resolved_function_id_candidates = TRY((((*this).resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor)))));
__jakt_var_474 = scope_id; goto __jakt_label_422;

}
__jakt_label_422:; __jakt_var_474.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
return JaktInternal::ExplicitValue(({ Optional<types::ScopeId> __jakt_var_475; {
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("print"sv))) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("println"sv))) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("eprintln"sv))) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("eprint"sv))) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("format"sv))) {
{
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
(resolved_function_id_candidates = TRY((((*this).resolve_call(call,resolved_namespaces,span,caller_scope_id,must_be_enum_constructor)))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_475 = caller_scope_id; goto __jakt_label_423;

}
__jakt_label_423:; __jakt_var_475.release_value(); }));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> generic_inferences_from_parent = (TRY((Dictionary<DeprecatedString, DeprecatedString>::create_with_entries({}))));
if ((((parent_id).has_value()) && (((((parent_id.value())).generic_arguments())).has_value()))){
JaktInternal::DynamicArray<types::TypeId> const arguments = ((((parent_id.value())).generic_arguments()).value());
JaktInternal::DynamicArray<types::TypeId> const parameters = TRY(((((parent_id.value())).generic_parameters(((((*this).program)))))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((arguments).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((generic_inferences_from_parent).set(TRY((((((parameters)[i])).to_string()))),TRY((((((arguments)[i])).to_string())))))));
TRY((((((*this).generic_inferences)).set(TRY((((((parameters)[i])).to_string()))),TRY((((((arguments)[i])).to_string())))))));
}

}
}

}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("print"sv))) {
{
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> arg = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> const type_hint = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::TypeId>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (first);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::TypeId>> __jakt_var_476; {
(first = false);
__jakt_var_476 = static_cast<JaktInternal::Optional<types::TypeId>>(TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("StringView"sv))))))); goto __jakt_label_424;

}
__jakt_label_424:; __jakt_var_476.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<typename types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).template get<2>()),caller_scope_id,safety_mode,type_hint))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == TRY(DeprecatedString::from_utf8("format"sv)))){
(return_type = TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("String"sv)))))));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("println"sv))) {
{
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> arg = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> const type_hint = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::TypeId>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (first);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::TypeId>> __jakt_var_477; {
(first = false);
__jakt_var_477 = static_cast<JaktInternal::Optional<types::TypeId>>(TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("StringView"sv))))))); goto __jakt_label_425;

}
__jakt_label_425:; __jakt_var_477.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<typename types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).template get<2>()),caller_scope_id,safety_mode,type_hint))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == TRY(DeprecatedString::from_utf8("format"sv)))){
(return_type = TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("String"sv)))))));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("eprintln"sv))) {
{
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> arg = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> const type_hint = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::TypeId>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (first);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::TypeId>> __jakt_var_478; {
(first = false);
__jakt_var_478 = static_cast<JaktInternal::Optional<types::TypeId>>(TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("StringView"sv))))))); goto __jakt_label_426;

}
__jakt_label_426:; __jakt_var_478.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<typename types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).template get<2>()),caller_scope_id,safety_mode,type_hint))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == TRY(DeprecatedString::from_utf8("format"sv)))){
(return_type = TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("String"sv)))))));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("eprint"sv))) {
{
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> arg = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> const type_hint = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::TypeId>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (first);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::TypeId>> __jakt_var_479; {
(first = false);
__jakt_var_479 = static_cast<JaktInternal::Optional<types::TypeId>>(TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("StringView"sv))))))); goto __jakt_label_427;

}
__jakt_label_427:; __jakt_var_479.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<typename types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).template get<2>()),caller_scope_id,safety_mode,type_hint))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == TRY(DeprecatedString::from_utf8("format"sv)))){
(return_type = TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("String"sv)))))));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("format"sv))) {
{
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> arg = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> const type_hint = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::TypeId>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (first);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::TypeId>> __jakt_var_480; {
(first = false);
__jakt_var_480 = static_cast<JaktInternal::Optional<types::TypeId>>(TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("StringView"sv))))))); goto __jakt_label_428;

}
__jakt_label_428:; __jakt_var_480.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<typename types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).template get<2>()),caller_scope_id,safety_mode,type_hint))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

if ((((call).name) == TRY(DeprecatedString::from_utf8("format"sv)))){
(return_type = TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("String"sv)))))));
(callee_throws = true);
}
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
i64 max_found_specificity = (-(static_cast<i64>(1LL)));
JaktInternal::DynamicArray<error::JaktError> errors_while_trying_to_find_matching_function = (TRY((DynamicArray<error::JaktError>::create_with({}))));
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> generic_inferences_for_best_match = (TRY((Dictionary<DeprecatedString, DeprecatedString>::create_with_entries({}))));
{
JaktInternal::ArrayIterator<types::FunctionId> _magic = ((resolved_function_id_candidates).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId candidate = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = TRY((((*this).match_function_and_resolve_args(call,caller_scope_id,candidate,safety_mode,span,this_expr))));
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typechecker::FunctionMatchResult::MatchSuccess>();JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& resolved_args = __jakt_match_value.args;
JaktInternal::Optional<types::TypeId> const& resolved_this_type_id = __jakt_match_value.maybe_this_type_id;
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const& used_generic_inferences = __jakt_match_value.used_generic_inferences;
i64 const& specificity = __jakt_match_value.specificity;
{
if ((specificity > max_found_specificity)){
(resolved_function_id = candidate);
(maybe_this_type_id = resolved_this_type_id);
(max_found_specificity = specificity);
(generic_inferences_for_best_match = used_generic_inferences);
(args = (TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>>::create_with({})))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((resolved_args).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> resolved_arg = (_magic_value.value());
{
TRY((((args).push((Tuple{((call).name), resolved_arg})))));
}

}
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typechecker::FunctionMatchResult::MatchError>();JaktInternal::DynamicArray<error::JaktError> const& errors = __jakt_match_value.errors;
{
{
JaktInternal::ArrayIterator<error::JaktError> _magic = ((errors).iterator());
for (;;){
JaktInternal::Optional<error::JaktError> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
error::JaktError error = (_magic_value.value());
{
TRY((((errors_while_trying_to_find_matching_function).push(error))));
}

}
}

return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

if ((!(((resolved_function_id).has_value())))){
if ((!(((resolved_function_id_candidates).is_empty())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("No function with matching signature found."sv)),span))));
{
JaktInternal::ArrayIterator<error::JaktError> _magic = ((errors_while_trying_to_find_matching_function).iterator());
for (;;){
JaktInternal::Optional<error::JaktError> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
error::JaktError match_error = (_magic_value.value());
{
TRY((((((((*this).compiler))->errors)).push(match_error))));
}

}
}

}
JaktInternal::DynamicArray<types::TypeId> checked_type_args = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedType>> _magic = ((((call).type_args)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedType> type_arg = (_magic_value.value());
{
TRY((((checked_type_args).push(TRY((((*this).typecheck_typename(type_arg,caller_scope_id,JaktInternal::OptionalNone()))))))));
}

}
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> arg = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedExpression> const checked_arg = TRY((((*this).typecheck_expression(((arg).template get<2>()),caller_scope_id,safety_mode,JaktInternal::OptionalNone()))));
TRY((((args).push((Tuple{((call).name), checked_arg})))));
}

}
}

return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Call>(types::CheckedCall(resolved_namespaces,((call).name),args,checked_type_args,JaktInternal::OptionalNone(),types::builtin( types::BuiltinType { typename types::BuiltinType::Unknown() } ),callee_throws,JaktInternal::OptionalNone()),span,types::builtin( types::BuiltinType { typename types::BuiltinType::Unknown() } ))));
}
((((*this).generic_inferences)).restore(generic_inferences_for_best_match));
TRY((((((*this).generic_inferences)).set_from(generic_inferences_from_parent))));
NonnullRefPtr<types::CheckedFunction> const callee = ((*this).get_function((resolved_function_id.value())));
(callee_throws = ((callee)->can_throw));
(return_type = ((callee)->return_type_id));
if ((((callee)->is_unsafe) && ((safety_mode).index() == 0 /* Safe */))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot call unsafe function in safe context"sv)),span))));
}
if ((((type_hint).has_value()) && (!(((((type_hint).value())).equals(types::unknown_type_id())))))){
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
TRY((((*this).check_types_for_compat(return_type,(type_hint.value()),((((*this).generic_inferences))),span))));
(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
}
(return_type = TRY((((*this).substitute_typevars_in_type(return_type,((*this).generic_inferences))))));
if ((((type_hint).has_value()) && (!(((((type_hint).value())).equals(types::unknown_type_id())))))){
bool const old_ignore_errors = ((*this).ignore_errors);
if (((callee)->is_instantiated)){
(((*this).ignore_errors) = true);
}
TRY((((*this).check_types_for_compat((type_hint.value()),return_type,((((*this).generic_inferences))),span))));
(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
}
{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((((((callee)->generics))->params)).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter generic_typevar = (_magic_value.value());
{
if (((((generic_typevar).kind)).index() == 1 /* Parameter */)){
JaktInternal::Optional<DeprecatedString> const substitution = ((((*this).generic_inferences)).get(TRY((((((generic_typevar).type_id())).to_string())))));
if (((substitution).has_value())){
TRY((((generic_arguments).push(TRY((types::TypeId::from_string((substitution.value()))))))));
}
else if ((!(((*this).in_comptime_function_call)))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Not all generic parameters have known types"sv)),span))));
}
else {
TRY((((generic_arguments).push(((generic_typevar).type_id())))));
}

}
}

}
}

if (((!(((callee)->is_instantiated))) || ((!(((((callee)->linkage)).index() == 1 /* External */))) && (!(((((callee)->generics))->is_specialized_for_types(generic_arguments))))))){
(generic_checked_function_to_instantiate = static_cast<JaktInternal::Optional<types::FunctionId>>((resolved_function_id.value())));
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
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(return_type = TRY((((*this).substitute_typevars_in_type(return_type,((*this).generic_inferences))))));
if ((callee_throws && (!(((TRY((((*this).get_scope(caller_scope_id)))))->can_throw))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Call to function that may throw needs to be in a try statement or a function marked as throws"sv)),span))));
}
if (((generic_checked_function_to_instantiate).has_value())){
if (((maybe_this_type_id).has_value())){
(maybe_this_type_id = TRY((((*this).substitute_typevars_in_type((maybe_this_type_id.value()),((*this).generic_inferences))))));
}
(resolved_function_id = TRY((((*this).typecheck_and_specialize_generic_function((generic_checked_function_to_instantiate.value()),generic_arguments,callee_scope_id,maybe_this_type_id,((*this).generic_inferences),((call).type_args),span,args)))));
}
if ((((*this).dump_try_hints) && callee_throws)){
TRY((((*this).dump_try_hint(span))));
}
JaktInternal::Optional<DeprecatedString> const external_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<DeprecatedString>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (((resolved_function_id).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<DeprecatedString>> __jakt_var_481; {
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function((resolved_function_id.value())));
if (((((function)->deprecated_message)).has_value())){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Call to deprecated function: {}"sv)),(((function)->deprecated_message).value())))),span))));
}
__jakt_var_481 = ((function)->external_name); goto __jakt_label_429;

}
__jakt_label_429:; __jakt_var_481.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((resolved_function_id).has_value())){
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function((resolved_function_id.value())));
if (((((function)->stores_arguments)).has_value())){
JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>> const argument_behaviour = (((function)->stores_arguments).value());
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>> _magic = ((argument_behaviour).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel> index__level__ = (_magic_value.value());
{
JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel> const jakt__index__level__ = index__level__;
size_t const index = ((jakt__index__level__).template get<0>());
parser::ArgumentStoreLevel const level = ((jakt__index__level__).template get<1>());

Function<ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>(size_t)> const resolve_arg = [&args, &this_expr, &function](size_t index) -> ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> {
{
if (TRY((((function)->is_static())))){
return ((((args)[index])).template get<1>());
}
if ((index == static_cast<size_t>(0ULL))){
return (this_expr.value());
}
return ((((args)[(JaktInternal::checked_sub<size_t>(index,static_cast<size_t>(1ULL)))])).template get<1>());
}
}
;
JaktInternal::Optional<types::ScopeId> const arg_scope_id = TRY((((*this).required_scope_id_in_hierarchy_for(TRY((resolve_arg(index))),caller_scope_id))));
JaktInternal::Optional<types::ScopeId> const stored_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::ScopeId>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = level;
switch(__jakt_match_variant.index()) {
case 1: {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::ScopeId>>(((*this).root_scope_id())));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ArgumentStoreLevel::InObject>();size_t const& argument_index = __jakt_match_value.argument_index;
return JaktInternal::ExplicitValue(TRY((((*this).required_scope_id_in_hierarchy_for(TRY((resolve_arg(argument_index))),caller_scope_id)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
if (TRY((((*this).scope_lifetime_subsumes(stored_scope_id,arg_scope_id))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot pass this argument by reference, it is not guaranteed to outlive the object it will be stored in"sv)),((TRY((resolve_arg(index))))->span())))));
}
}

}
}

}
}
types::CheckedCall const function_call = types::CheckedCall(resolved_namespaces,((call).name),args,generic_arguments,resolved_function_id,return_type,callee_throws,external_name);
NonnullRefPtr<typename types::CheckedExpression> const checked_call = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Call>(function_call,span,return_type)));
bool const in_comptime_function = (((((*this).current_function_id)).has_value()) && ((((*this).get_function(((((*this).current_function_id)).value()))))->is_comptime));
if (((!(in_comptime_function)) && (((resolved_function_id).has_value()) && ((((*this).get_function((resolved_function_id.value()))))->is_comptime)))){
NonnullRefPtr<types::CheckedFunction> const resolved_function = ((*this).get_function((resolved_function_id.value())));
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((((*this).interpreter())));
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(generic_checked_function_to_instantiate.value_or_lazy_evaluated([&] { return (resolved_function_id.value()); })));
JaktInternal::DynamicArray<types::Value> call_args = (TRY((DynamicArray<types::Value>::create_with({}))));
JaktInternal::Optional<types::Value> this_argument = JaktInternal::OptionalNone();
NonnullRefPtr<interpreter::InterpreterScope> eval_scope = TRY((interpreter::InterpreterScope::from_runtime_scope(caller_scope_id,((*this).program),JaktInternal::OptionalNone())));
{
JaktInternal::DictionaryIterator<DeprecatedString,DeprecatedString> _magic = ((((((*this).generic_inferences)).iterator())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,DeprecatedString>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,DeprecatedString> entry = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,DeprecatedString> const key_value_ = entry;
DeprecatedString const key = ((key_value_).template get<0>());
DeprecatedString const value = ((key_value_).template get<1>());

TRY((((((eval_scope)->type_bindings)).set(key,TRY((types::TypeId::from_string(value)))))));
}

}
}

if (((this_expr).has_value())){
auto __jakt_var_482 = [&]() -> ErrorOr<void> {{
interpreter::StatementResult const evaluated_this = TRY((((interpreter)->execute_expression((this_expr.value()),eval_scope))));
if (((evaluated_this).index() == 5 /* JustValue */)){
types::Value const value = ((evaluated_this).get<interpreter::StatementResult::JustValue>()).value;
(this_argument = value);
}
else if (((evaluated_this).index() == 1 /* Throw */)){
types::Value const value = ((evaluated_this).get<interpreter::StatementResult::Throw>()).value;
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Error executing this expression (evaluation threw {})"sv)),value))),(((this_expr.value()))->span())))));
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Invalid this expression"sv)),(((this_expr.value()))->span())))));
}

}

;return {};}();
if (__jakt_var_482.is_error()) {{
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Error executing this expression"sv)),(((this_expr.value()))->span())))));
}
};
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>> argument = (_magic_value.value());
{
interpreter::StatementResult const value = ({ Optional<interpreter::StatementResult> __jakt_var_483;
auto __jakt_var_484 = [&]() -> ErrorOr<interpreter::StatementResult> { return TRY((((interpreter)->execute_expression(((argument).template get<1>()),eval_scope)))); }();
if (__jakt_var_484.is_error()) {{
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Error in argument"sv)),span))));
continue;
}
} else {__jakt_var_483 = __jakt_var_484.release_value();
}
__jakt_var_483.release_value(); });
if (((value).index() == 1 /* Throw */)){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Compiletime call failed: {}"sv)),value))),((((argument).template get<1>()))->span())))));
break;
}
types::Value const evaluated_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
TRY((((call_args).push(evaluated_value))));
}

}
}

JaktInternal::Dictionary<DeprecatedString,types::TypeId> type_bindings = (TRY((Dictionary<DeprecatedString, types::TypeId>::create_with_entries({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((((resolved_function)->generics))->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
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
NonnullRefPtr<interpreter::InterpreterScope> invocation_scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<DeprecatedString, types::Value>::create_with_entries({})))),JaktInternal::OptionalNone(),type_bindings)));
auto __jakt_var_485 = [&]() -> ErrorOr<void> {{
(result = TRY((((interpreter)->execute((resolved_function_id.value()),resolved_namespaces,this_argument,call_args,span,invocation_scope)))));
}

;return {};}();
if (__jakt_var_485.is_error()) {auto error = __jakt_var_485.release_error();{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Compiletime call failed: {}"sv)),error))),span))));
return checked_call;
}
};
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
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
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_486; {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Compiletime call failed: {}"sv)),x))),((x).span)))));
__jakt_var_486 = checked_call; goto __jakt_label_430;

}
__jakt_label_430:; __jakt_var_486.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return checked_call;
}
}

ErrorOr<JaktInternal::DynamicArray<types::FunctionId>> typechecker::Typechecker::resolve_call(parser::ParsedCall const call,JaktInternal::DynamicArray<types::ResolvedNamespace> namespaces,utility::Span const span,types::ScopeId const scope_id,bool const must_be_enum_constructor) {
{
types::ScopeId current_scope_id = scope_id;
JaktInternal::DynamicArray<bool> is_base_ns_alias_or_import = (TRY((DynamicArray<bool>::filled(((namespaces).size()), false))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).namespace_)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t namespace_index = (_magic_value.value());
{
DeprecatedString const scope_name = ((((call).namespace_))[namespace_index]);
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> const maybe_ns_scope = TRY((((*this).find_namespace_in_scope(current_scope_id,scope_name,false))));
if (((maybe_ns_scope).has_value())){
JaktInternal::Tuple<types::ScopeId,bool> const scope_id_is_import_ = (maybe_ns_scope.value());
types::ScopeId const scope_id = ((scope_id_is_import_).template get<0>());
bool const is_import = ((scope_id_is_import_).template get<1>());

if (is_import){
(((((namespaces)[namespace_index])).name) = ((((((((*this).program))->modules))[((((scope_id).module_id)).id)]))->name));
}
(((((namespaces)[namespace_index])).external_name) = ((TRY((((*this).get_scope(scope_id)))))->external_name));
(((is_base_ns_alias_or_import)[namespace_index]) = (((TRY((((*this).find_namespace_in_scope(current_scope_id,scope_name,true)))).value())).template get<1>()));
(current_scope_id = scope_id);
continue;
}
JaktInternal::Optional<types::StructId> const maybe_struct_scope = TRY((((*this).find_struct_in_scope(current_scope_id,scope_name))));
if (((maybe_struct_scope).has_value())){
types::CheckedStruct const structure = ((*this).get_struct((maybe_struct_scope.value())));
(((((namespaces)[namespace_index])).external_name) = ((structure).external_name));
(current_scope_id = ((structure).scope_id));
continue;
}
JaktInternal::Optional<types::EnumId> const maybe_enum_scope = TRY((((((*this).program))->find_enum_in_scope(current_scope_id,scope_name))));
if (((maybe_enum_scope).has_value())){
types::CheckedEnum const enum_ = ((*this).get_enum((maybe_enum_scope.value())));
(current_scope_id = ((enum_).scope_id));
continue;
}
if (((TRY((((((*this).generic_inferences)).find_and_map(scope_name,((((*this).program)))))))).has_value())){
types::TypeId const type_id = (TRY((((((*this).generic_inferences)).find_and_map(scope_name,((((*this).program))))))).value());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::DynamicArray<types::FunctionId>>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
(current_scope_id = ((((*this).get_enum(enum_id))).scope_id));
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
{
(current_scope_id = ((((*this).get_enum(enum_id))).scope_id));
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
(current_scope_id = ((((*this).get_struct(struct_id))).scope_id));
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
{
(current_scope_id = ((((*this).get_struct(struct_id))).scope_id));
return JaktInternal::LoopContinue{};
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Not a namespace, enum, class, or struct: ‘{}’"sv)),TRY((utility::join(((call).namespace_),TRY(DeprecatedString::from_utf8("::"sv)))))))),span))));
}

}
}

types::ScopeId initial_scope_id = current_scope_id;
JaktInternal::Optional<types::ScopeId> owning_scope = JaktInternal::OptionalNone();
ScopeGuard __jakt_var_487([&] {
{
JaktInternal::DynamicArray<types::ResolvedNamespace> resolved_namespaces = (MUST((DynamicArray<types::ResolvedNamespace>::create_with({}))));
{
i64 ns_index = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::ResolvedNamespace> _magic = ((namespaces).iterator());
for (;;){
JaktInternal::Optional<types::ResolvedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ResolvedNamespace ns = (_magic_value.value());
{
ScopeGuard __jakt_var_488([&] {
({auto& _jakt_ref = ns_index;_jakt_ref = JaktInternal::checked_add<i64>(_jakt_ref, static_cast<i64>(1LL));});
});
if ((!(((is_base_ns_alias_or_import)[ns_index])))){
MUST((((resolved_namespaces).push(ns))));
}
}

}
}

}

if ((!(((owning_scope).has_value())))){
JaktInternal::DynamicArray<types::ResolvedNamespace> aliased_namespaces = (MUST((DynamicArray<types::ResolvedNamespace>::create_with({}))));
for (;;){
NonnullRefPtr<types::Scope> const scope = MUST((((*this).get_scope(current_scope_id))));
if (((((scope)->alias_path)).has_value())){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>((((((scope)->alias_path).value())).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
MUST((((aliased_namespaces).push((((((scope)->alias_path).value()))[(JaktInternal::checked_sub<size_t>(i,static_cast<size_t>(1ULL)))])))));
}

}
}

}
else if (((((scope)->namespace_name)).has_value())){
MUST((((aliased_namespaces).push(types::ResolvedNamespace((((scope)->namespace_name).value()),((scope)->external_name),JaktInternal::OptionalNone())))));
}
if (MUST((((*this).is_scope_directly_accessible_from(current_scope_id,initial_scope_id))))){
break;
}
JaktInternal::Optional<types::ScopeId> const parent = ((scope)->parent);
if ((!(((parent).has_value())))){
break;
}
(current_scope_id = (parent.value()));
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((aliased_namespaces).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
MUST((((resolved_namespaces).push(((aliased_namespaces)[(JaktInternal::checked_sub<size_t>(i,static_cast<size_t>(1ULL)))])))));
}

}
}

}
((namespaces).shrink(static_cast<size_t>(0ULL)));
MUST((((namespaces).push_values(((resolved_namespaces))))));
}

});
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> const maybe_var = TRY((((*this).find_var_in_scope(current_scope_id,((call).name)))));
if (((maybe_var).has_value())){
types::TypeId const inner_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<JaktInternal::DynamicArray<types::FunctionId>>>{
auto&& __jakt_match_variant = *((*this).get_type((((maybe_var.value()))->type_id)));
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
return JaktInternal::ExplicitValue((((maybe_var.value()))->type_id));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((((*this).get_type(inner_type)))->index() == 29 /* Function */)){
types::FunctionId const pseudo_function_id = ((((*this).get_type(inner_type)))->get<types::Type::Function>()).pseudo_function_id;
return (TRY((DynamicArray<types::FunctionId>::create_with({pseudo_function_id}))));
}
}
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>> const maybe_overload_set = TRY((((*this).find_scoped_functions_with_name_in_scope(current_scope_id,((call).name)))));
if (((maybe_overload_set).has_value())){
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function((((((maybe_overload_set.value())).template get<0>()))[static_cast<i64>(0LL)])));
if (((!(must_be_enum_constructor)) || ((((function)->type)).index() == 3 /* ImplicitEnumConstructor */))){
(owning_scope = ((function)->owner_scope));
(current_scope_id = (((maybe_overload_set.value())).template get<1>()));
return (((maybe_overload_set.value())).template get<0>());
}
}
if (must_be_enum_constructor){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("No such enum constructor ‘{}’"sv)),((call).name)))),span))));
return (TRY((DynamicArray<types::FunctionId>::create_with({}))));
}
JaktInternal::Optional<types::StructId> const maybe_struct_id = TRY((((*this).find_struct_in_scope(current_scope_id,((call).name)))));
if (((maybe_struct_id).has_value())){
types::StructId const struct_id = (maybe_struct_id.value());
types::CheckedStruct const structure = ((*this).get_struct(struct_id));
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>> const maybe_function_id = TRY((((*this).find_scoped_functions_with_name_in_scope(((structure).scope_id),((structure).name)))));
if (((maybe_function_id).has_value())){
(current_scope_id = (((maybe_function_id.value())).template get<1>()));
return (((maybe_function_id.value())).template get<0>());
}
}
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Call to unknown function: ‘{}’"sv)),((call).name)))),span))));
return (TRY((DynamicArray<types::FunctionId>::create_with({}))));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_if(NonnullRefPtr<typename parser::ParsedExpression> const condition,parser::ParsedBlock const then_block,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const else_statement,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((((*this).expand_context_for_bindings(condition,JaktInternal::OptionalNone(),then_block,else_statement,scope_id,span))));
NonnullRefPtr<typename parser::ParsedExpression> const new_condition = ((new_condition_new_then_block_new_else_statement_).template get<0>());
JaktInternal::Optional<parser::ParsedBlock> const new_then_block = ((new_condition_new_then_block_new_else_statement_).template get<1>());
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const new_else_statement = ((new_condition_new_then_block_new_else_statement_).template get<2>());

NonnullRefPtr<typename types::CheckedExpression> const checked_condition = TRY((((*this).typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
if ((!(((((checked_condition)->type())).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } )))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Condition must be a boolean expression"sv)),((new_condition)->span())))));
}
types::CheckedBlock const checked_block = TRY((((*this).typecheck_block((new_then_block.value()),scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((((checked_block).yielded_type)).has_value())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("An 'if' block is not allowed to yield values"sv)),((((new_then_block.value())).find_yield_span()).value())))));
}
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> checked_else = JaktInternal::OptionalNone();
if (((new_else_statement).has_value())){
(checked_else = TRY((((*this).typecheck_statement((new_else_statement.value()),scope_id,safety_mode,JaktInternal::OptionalNone())))));
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::If>(checked_condition,checked_block,checked_else,span)));
}
}

ErrorOr<void> typechecker::Typechecker::check_implicit_constructor_argument_access(types::ScopeId const caller_scope_id,parser::ParsedCall const call,types::CheckedStruct const struct_) {
{
if ((!(TRY((((*this).scope_can_access(caller_scope_id,((struct_).scope_id)))))))){
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> arg = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((*this).get_variable(((field).variable_id)));
DeprecatedString const name = TRY((((*this).get_argument_name(arg))));
if (((((variable)->name) == name) && ((((variable)->visibility)).index() == 1 /* Private */))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Can't access field '{}' when calling implicit constructor of '{}' because it is marked private"sv)),((variable)->name),((struct_).name)))),((arg).template get<1>())))));
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

ErrorOr<void> typechecker::Typechecker::typecheck_enum(parser::ParsedRecord const record,types::EnumId const enum_id,types::ScopeId const parent_scope_id) {
{
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = ((((*this).get_enum(enum_id))).type_id));
ScopeGuard __jakt_var_489([&] {
(((*this).self_type_id) = old_self_type_id);
});
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
TRY((((*this).typecheck_method(((method).parsed_function), types::StructLikeId { typename types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id) } ))));
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_expression_and_dereference_if_needed(NonnullRefPtr<typename parser::ParsedExpression> const expr,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint,utility::Span const span) {
{
NonnullRefPtr<typename types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,type_hint))));
return TRY((((*this).dereference_if_needed(checked_expr,span))));
}
}

ErrorOr<JaktInternal::Optional<types::TypeId>> typechecker::Typechecker::find_type_in_scope(types::ScopeId const scope_id,DeprecatedString const name) const {
{
return ((TRY((((*this).find_type_scope(scope_id,name))))).map([](auto& _value) { return _value.template get<0>(); }));
}
}

ErrorOr<JaktInternal::Optional<types::CheckedEnumVariant>> typechecker::Typechecker::get_enum_variant(types::CheckedEnum const enum_,DeprecatedString const variant_name) {
{
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if ((((variant).name()) == variant_name)){
return variant;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<bool> typechecker::Typechecker::scope_can_access(types::ScopeId const accessor,types::ScopeId const accessee) const {
{
if (((accessor).equals(accessee))){
return true;
}
NonnullRefPtr<types::Scope> accessor_scope = TRY((((*this).get_scope(accessor))));
while (((((accessor_scope)->parent)).has_value())){
types::ScopeId const parent = (((accessor_scope)->parent).value());
if (((parent).equals(accessee))){
return true;
}
(accessor_scope = TRY((((*this).get_scope(parent)))));
}
return false;
}
}

ErrorOr<JaktInternal::DynamicArray<types::StructId>> typechecker::Typechecker::struct_inheritance_chain(types::StructId const struct_id) const {
{
JaktInternal::DynamicArray<types::StructId> chain = (TRY((DynamicArray<types::StructId>::create_with({}))));
JaktInternal::Optional<types::StructId> current = static_cast<JaktInternal::Optional<types::StructId>>(struct_id);
TRY((((chain).push((current.value())))));
while (((current).has_value())){
JaktInternal::Optional<types::StructId> const parent = ((((*this).get_struct((current.value())))).super_struct_id);
if (((parent).has_value())){
TRY((((chain).push((parent.value())))));
}
(current = parent);
}
JaktInternal::DynamicArray<types::StructId> reverse_chain = (TRY((DynamicArray<types::StructId>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((chain).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((reverse_chain).push(((chain)[(JaktInternal::checked_sub<size_t>((JaktInternal::checked_sub<size_t>(((chain).size()),static_cast<size_t>(1ULL))),i))])))));
}

}
}

return reverse_chain;
}
}

ErrorOr<bool> typechecker::Typechecker::type_contains_reference(types::TypeId const type_id) {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 27: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 28: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_for(DeprecatedString const iterator_name,utility::Span const name_span,bool const is_destructuring,NonnullRefPtr<typename parser::ParsedExpression> const range,parser::ParsedBlock const block,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
JaktInternal::Optional<utility::Span> const maybe_span = ((block).find_yield_span());
if (((maybe_span).has_value())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("a 'for' loop block is not allowed to yield values"sv)),(maybe_span.value())))));
}
NonnullRefPtr<typename types::CheckedExpression> iterable_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(range,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId resolved_iterable_result_type = types::unknown_type_id();
NonnullRefPtr<typename parser::ParsedExpression> expression_to_iterate = range;
JaktInternal::Optional<typechecker::TraitImplementationDescriptor> const iterable_trait_implementation = TRY((((*this).find_any_singular_trait_implementation(((iterable_expr)->type()),(TRY((DynamicArray<DeprecatedString>::create_with({TRY(DeprecatedString::from_utf8("Iterable"sv)), TRY(DeprecatedString::from_utf8("ThrowingIterable"sv))})))),scope_id,((iterable_expr)->span())))));
if ((!(((iterable_trait_implementation).has_value())))){
JaktInternal::Optional<typechecker::TraitImplementationDescriptor> const into_iterator_trait_implementation = TRY((((*this).find_any_singular_trait_implementation(((iterable_expr)->type()),(TRY((DynamicArray<DeprecatedString>::create_with({TRY(DeprecatedString::from_utf8("IntoIterator"sv)), TRY(DeprecatedString::from_utf8("IntoThrowingIterator"sv))})))),scope_id,((iterable_expr)->span())))));
if ((!(((into_iterator_trait_implementation).has_value())))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Iterable expression is not iterable"sv)),((range)->span()),TRY((__jakt_format((StringView::from_string_literal("Consider implementing (Throwing)Iterable<T> or Into(Throwing)Iterator<T> for the type of this expression (‘{}’)"sv)),TRY((((*this).type_name(((iterable_expr)->type()),false))))))),((range)->span())))));
}
else {
(resolved_iterable_result_type = (((((into_iterator_trait_implementation.value())).implemented_type_args))[static_cast<i64>(0LL)]));
(expression_to_iterate = TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::MethodCall>(range,parser::ParsedCall((TRY((DynamicArray<DeprecatedString>::create_with({})))),TRY(DeprecatedString::from_utf8("iterator"sv)),(TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({}))))),false,name_span))));
}

}
else {
(resolved_iterable_result_type = (((((iterable_trait_implementation.value())).implemented_type_args))[static_cast<i64>(0LL)]));
}

NonnullRefPtr<typename parser::ParsedStatement> const rewritten_statement = TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::Block>(parser::ParsedBlock((TRY((DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(TRY(DeprecatedString::from_utf8("_magic"sv)),TRY((parser::ParsedType::template __jakt_create<typename parser::ParsedType::Empty>())),true,JaktInternal::OptionalNone(),name_span,JaktInternal::OptionalNone()),expression_to_iterate,span))), TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::Loop>(parser::ParsedBlock((TRY((DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(TRY(DeprecatedString::from_utf8("_magic_value"sv)),TRY((parser::ParsedType::template __jakt_create<typename parser::ParsedType::Empty>())),false,JaktInternal::OptionalNone(),name_span,JaktInternal::OptionalNone()),TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::MethodCall>(TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::Var>(TRY(DeprecatedString::from_utf8("_magic"sv)),name_span))),parser::ParsedCall((TRY((DynamicArray<DeprecatedString>::create_with({})))),TRY(DeprecatedString::from_utf8("next"sv)),(TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({}))))),false,name_span))),span))), TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::If>(TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::UnaryOp>(TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::MethodCall>(TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::Var>(TRY(DeprecatedString::from_utf8("_magic_value"sv)),name_span))),parser::ParsedCall((TRY((DynamicArray<DeprecatedString>::create_with({})))),TRY(DeprecatedString::from_utf8("has_value"sv)),(TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({}))))),false,name_span))), parser::UnaryOperator { typename parser::UnaryOperator::LogicalNot() } ,name_span))),parser::ParsedBlock((TRY((DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::Break>(span)))}))))),JaktInternal::OptionalNone(),span))), TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::VarDecl>(parser::ParsedVarDecl(iterator_name,TRY((parser::ParsedType::template __jakt_create<typename parser::ParsedType::Empty>())),true,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<utility::Span>,ErrorOr<NonnullRefPtr<typename types::CheckedStatement>>>{
auto __jakt_enum_value = (is_destructuring);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(name_span);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),name_span,JaktInternal::OptionalNone()),TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::ForcedUnwrap>(TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::Var>(TRY(DeprecatedString::from_utf8("_magic_value"sv)),name_span))),name_span))),span))), TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::Block>(block,span)))}))))),span)))}))))),span)));
return TRY((((*this).typecheck_statement(rewritten_statement,scope_id,safety_mode,JaktInternal::OptionalNone()))));
}
}

ErrorOr<JaktInternal::Optional<types::FunctionId>> typechecker::Typechecker::find_function_matching_signature_in_scope(types::ScopeId const parent_scope_id,parser::ParsedFunction const prototype) const {
{
DeprecatedString const function_name = ((prototype).name);
JaktInternal::Optional<JaktInternal::DynamicArray<types::FunctionId>> const candidate_ids = TRY((((((*this).program))->find_functions_with_name_in_scope(parent_scope_id,function_name))));
if (((candidate_ids).has_value())){
{
JaktInternal::ArrayIterator<types::FunctionId> _magic = (((candidate_ids.value())).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId candidate_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const candidate = ((*this).get_function(candidate_id));
if ((((((candidate)->parsed_function)).has_value()) && (((((candidate)->parsed_function).value())).equals(prototype)))){
return candidate_id;
}
}

}
}

}
return JaktInternal::OptionalNone();
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_array(types::ScopeId const scope_id,JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const values,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const fill_size,utility::Span const span,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
if ((!(((TRY((((*this).get_scope(scope_id)))))->can_throw)))){
DeprecatedString const message = TRY(DeprecatedString::from_utf8("Array initialization inside non-throwing scope"sv));
if (((((*this).current_function_id)).has_value())){
NonnullRefPtr<types::CheckedFunction> const current_function = ((*this).get_function((((*this).current_function_id).value())));
TRY((((*this).error_with_hint(message,span,TRY((__jakt_format((StringView::from_string_literal("Add `throws` keyword to function {}"sv)),((current_function)->name)))),((current_function)->name_span)))));
}
else {
TRY((((*this).error(message,span))));
}

}
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> repeat = JaktInternal::OptionalNone();
if (((fill_size).has_value())){
NonnullRefPtr<typename parser::ParsedExpression> const fill_size_value = ((fill_size).value());
NonnullRefPtr<typename types::CheckedExpression> const fill_size_checked = TRY((((*this).typecheck_expression_and_dereference_if_needed(fill_size_value,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const fill_size_type = ((fill_size_checked)->type());
if ((!(((*this).is_integer(fill_size_type))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type '{}' is not convertible to an integer. Only integer values can be array fill size expressions."sv)),TRY((((*this).type_name(fill_size_type,false))))))),((fill_size_value)->span())))));
}
(repeat = fill_size_checked);
}
types::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Array"sv))))));
types::TypeId inner_type_id = types::unknown_type_id();
JaktInternal::Optional<utility::Span> inferred_type_span = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> inner_hint = JaktInternal::OptionalNone();
JaktInternal::Optional<JaktInternal::DynamicArray<types::TypeId>> const type_hint_ids = TRY((((*this).get_type_ids_from_type_hint_if_struct_ids_match(type_hint,array_struct_id))));
if (((type_hint_ids).has_value())){
(inner_hint = (((type_hint_ids.value()))[static_cast<i64>(0LL)]));
}
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedExpression>> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedExpression> value = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,inner_hint))));
types::TypeId const current_value_type_id = ((checked_expr)->type());
if (((current_value_type_id).equals(types::void_type_id()))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot create an array with values of type void\n"sv)),span))));
}
if (((inner_type_id).equals(types::unknown_type_id()))){
(inner_type_id = current_value_type_id);
(inferred_type_span = ((value)->span()));
}
else if ((!(((inner_type_id).equals(current_value_type_id))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Type '{}' does not match type '{}' of previous values in array"sv)),TRY((((*this).type_name(current_value_type_id,false)))),TRY((((*this).type_name(inner_type_id,false))))))),((value)->span()),TRY((__jakt_format((StringView::from_string_literal("Array was inferred to store type '{}' here"sv)),TRY((((*this).type_name(inner_type_id,false))))))),(inferred_type_span.value())))));
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
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot infer generic type for Array<T>"sv)),span))));
}
}
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(array_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({inner_type_id})))))))))));
if (((type_hint).has_value())){
TRY((((*this).check_types_for_compat((type_hint.value()),type_id,((((*this).generic_inferences))),span))));
}
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::JaktArray>(vals,repeat,span,type_id,inner_type_id)));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_trait_predecl(parser::ParsedTrait const parsed_trait,types::ScopeId const scope_id) {
{
types::ScopeId const trait_scope_id = TRY((((*this).create_scope(scope_id,false,TRY((__jakt_format((StringView::from_string_literal("trait({})"sv)),((parsed_trait).name)))),false))));
TRY((((*this).add_type_to_scope(trait_scope_id,TRY(DeprecatedString::from_utf8("Self"sv)),TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Self>())))))),((parsed_trait).name_span)))));
NonnullRefPtr<types::CheckedTrait> checked_trait = TRY((types::CheckedTrait::__jakt_create(((parsed_trait).name),((parsed_trait).name_span),(TRY((Dictionary<DeprecatedString, types::FunctionId>::create_with_entries({})))),(TRY((DynamicArray<types::CheckedGenericParameter>::create_with({})))),trait_scope_id)));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::TraitId const trait_id = types::TraitId(((*this).current_module_id),((((((((((*this).program))->modules))[((((*this).current_module_id)).id)]))->traits)).size()));
types::TypeId const trait_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Trait>(trait_id)))))));
TRY((((((((((((*this).program))->modules))[((((*this).current_module_id)).id)]))->traits)).push(checked_trait))));
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = trait_type_id);
ScopeGuard __jakt_var_490([&] {
(((*this).self_type_id) = old_self_type_id);
});
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
TRY((((*this).add_type_to_scope(scope_id,((parsed_trait).name),trait_type_id,((parsed_trait).name_span)))));
TRY((((*this).add_trait_to_scope(scope_id,((parsed_trait).name),trait_id,((parsed_trait).name_span)))));
JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters = ((((((module)->traits))[((trait_id).id)]))->generic_parameters);
TRY((((generic_parameters).ensure_capacity(((((parsed_trait).generic_parameters)).size())))));
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((parsed_trait).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter gen_parameter = (_magic_value.value());
{
types::TypeId const parameter_type_id = types::TypeId(((*this).current_module_id),((((((*this).current_module()))->types)).size()));
JaktInternal::DynamicArray<types::TypeId> trait_implementations = (TRY((DynamicArray<types::TypeId>::create_with({}))));
types::CheckedGenericParameter parameter = TRY((types::CheckedGenericParameter::make(parameter_type_id,((gen_parameter).span))));
TRY((((((module)->types)).push(TRY((types::Type::template __jakt_create<typename types::Type::TypeVariable>(((gen_parameter).name),trait_implementations)))))));
if (((((gen_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((gen_parameter).requires_list).value()),((((parameter).constraints))),((trait_implementations)),scope_id))));
}
TRY((((generic_parameters).push(parameter))));
TRY((((*this).add_type_to_scope(trait_scope_id,((gen_parameter).name),parameter_type_id,((gen_parameter).span)))));
}

}
}

types::StructId const synthetic_struct_id = types::StructId(((*this).current_module_id),((((((((((*this).program))->modules))[((((*this).current_module_id)).id)]))->structures)).size()));
TRY((((((module)->structures)).push(types::CheckedStruct(((parsed_trait).name),((parsed_trait).name_span),generic_parameters,(TRY((DynamicArray<types::CheckedField>::create_with({})))),trait_scope_id, parser::DefinitionLinkage { typename parser::DefinitionLinkage::External() } ,(TRY((Dictionary<DeprecatedString, JaktInternal::Tuple<types::TraitId,JaktInternal::DynamicArray<types::TypeId>>>::create_with_entries({})))), parser::RecordType { typename parser::RecordType::Struct((TRY((DynamicArray<parser::ParsedField>::create_with({})))),JaktInternal::OptionalNone()) } ,trait_type_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))));
types::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(synthetic_struct_id)))))));
{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((parsed_trait).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction parsed_function = (_magic_value.value());
{
types::ScopeId const method_scope_id = TRY((((*this).create_scope(trait_scope_id,((parsed_function).can_throw),TRY((__jakt_format((StringView::from_string_literal("trait-method({}::{})"sv)),((parsed_trait).name),((parsed_function).name)))),true))));
types::FunctionId const function_id = ((((((*this).program))->get_module(((*this).current_module_id))))->next_function_id());
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if (((!(((((parsed_function).params)).is_empty()))) && ((((((((((parsed_function).params)).first()).value())).variable)).name) == TRY(DeprecatedString::from_utf8("this"sv))))){
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

ErrorOr<bool> typechecker::Typechecker::implements_trait(types::TypeId const type_id,types::TraitId const trait_id,JaktInternal::Optional<JaktInternal::DynamicArray<types::TypeId>> const generic_arguments) {
{
Function<ErrorOr<bool>(JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>>, types::TraitId, JaktInternal::DynamicArray<types::TypeId>, typechecker::Typechecker&)> const has_matching_trait = [type_id](JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>> trait_implementations, types::TraitId trait_id, JaktInternal::DynamicArray<types::TypeId> passed_generic_arguments, typechecker::Typechecker& typechecker) -> ErrorOr<bool> {
{
bool const old_ignore_errors = ((((typechecker))).ignore_errors);
(((((typechecker))).ignore_errors) = true);
ScopeGuard __jakt_var_491([&] {
{
(((((typechecker))).ignore_errors) = old_ignore_errors);
(((((typechecker))).had_an_error) = false);
}

});
bool found = false;
{
JaktInternal::ArrayIterator<JaktInternal::DynamicArray<types::TypeId>> _magic = ((trait_implementations).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::DynamicArray<types::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::DynamicArray<types::TypeId> implemented_generic_arguments = (_magic_value.value());
{
if ((((implemented_generic_arguments).size()) != ((passed_generic_arguments).size()))){
continue;
}
bool ok = false;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((implemented_generic_arguments).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
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

return found;
}
}
;
JaktInternal::DynamicArray<types::TypeId> const empty = (TRY((DynamicArray<types::TypeId>::create_with({}))));
return TRY((has_matching_trait(TRY((((*this).find_all_implementations_of_trait(type_id,trait_id)))),trait_id,generic_arguments.value_or_lazy_evaluated([&] { return empty; }),((*this)))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_module_import(parser::ParsedModuleImport const import_,types::ScopeId const scope_id) {
{
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>> const module_names_and_spans = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = ((import_).module_name);
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ImportName::Literal>();DeprecatedString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>>>((TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>::create_with({(Tuple{name, span})}))))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ImportName::Comptime>();NonnullRefPtr<typename parser::ParsedExpression> const& expression = __jakt_match_value.expression;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>>> __jakt_var_492; {
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((((*this).interpreter())));
NonnullRefPtr<interpreter::InterpreterScope> eval_scope = TRY((interpreter::InterpreterScope::from_runtime_scope(scope_id,((*this).program),JaktInternal::OptionalNone())));
types::ScopeId const exec_scope = TRY((((*this).create_scope(scope_id,true,TRY(DeprecatedString::from_utf8("comptime-import"sv)),true))));
interpreter::StatementResult const result = TRY((((interpreter)->execute_expression(TRY((((*this).typecheck_expression(expression,exec_scope, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone())))),eval_scope))));
__jakt_var_492 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>> __jakt_var_493; {
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("module name must evalute to a string literal or an array of strings"sv)),((expression)->span()),TRY(DeprecatedString::from_utf8("this expression evaluates to an invalid value"sv)),((expression)->span())))));
__jakt_var_493 = JaktInternal::OptionalNone(); goto __jakt_label_432;

}
__jakt_label_432:; __jakt_var_493; }));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>> __jakt_var_494; {
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("module name must evalute to a string literal or an array of strings"sv)),((expression)->span()),TRY(DeprecatedString::from_utf8("this expression evaluates to an invalid value"sv)),((expression)->span())))));
__jakt_var_494 = JaktInternal::OptionalNone(); goto __jakt_label_433;

}
__jakt_label_433:; __jakt_var_494; }));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>> __jakt_var_495; {
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("module name must evalute to a string literal or an array of strings"sv)),((expression)->span()),TRY(DeprecatedString::from_utf8("this expression evaluates to an invalid value"sv)),((expression)->span())))));
__jakt_var_495 = JaktInternal::OptionalNone(); goto __jakt_label_434;

}
__jakt_label_434:; __jakt_var_495; }));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>> __jakt_var_496; {
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("module name must evalute to a string literal or an array of strings"sv)),((expression)->span()),TRY(DeprecatedString::from_utf8("this expression evaluates to an invalid value"sv)),((expression)->span())))));
__jakt_var_496 = JaktInternal::OptionalNone(); goto __jakt_label_435;

}
__jakt_label_435:; __jakt_var_496; }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Throw>();
types::Value const& error = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>> __jakt_var_497; {
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("module name must evalute to a string literal or an array of strings"sv)),((expression)->span()),TRY((__jakt_format((StringView::from_string_literal("this expression threw an error: {}"sv)),error))),((expression)->span())))));
__jakt_var_497 = JaktInternal::OptionalNone(); goto __jakt_label_436;

}
__jakt_label_436:; __jakt_var_497; }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::JustValue>();
types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
DeprecatedString const& string = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>>>((TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>::create_with({(Tuple{string, ((value).span)})}))))));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktArray>();JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>>> __jakt_var_498; {
if (((values).is_empty())){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("module name must evalute to a string literal or an array of strings"sv)),((expression)->span()),TRY(DeprecatedString::from_utf8("this expression evaluates to an empty array"sv)),((expression)->span())))));
}
JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>> result = (TRY((DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
DeprecatedString const& string = __jakt_match_value.value;
return (TRY((((result).push((Tuple{string, ((value).span)})))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("module name must evalute to a string literal or an array of strings"sv)),((value).span),TRY(DeprecatedString::from_utf8("this expression evaluates to an invalid value"sv)),((value).span)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

__jakt_var_498 = static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>>>(result); goto __jakt_label_437;

}
__jakt_label_437:; __jakt_var_498.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,utility::Span>>> __jakt_var_499; {
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("module name must evalute to a string literal"sv)),((expression)->span()),TRY(DeprecatedString::from_utf8("this expression evaluates to a non-string value"sv)),((expression)->span())))));
__jakt_var_499 = JaktInternal::OptionalNone(); goto __jakt_label_438;

}
__jakt_label_438:; __jakt_var_499; }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_431;

}
__jakt_label_431:; __jakt_var_492.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((!(((module_names_and_spans).has_value())))){
return {};
}
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span>> module_name_and_span = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<DeprecatedString> names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<DeprecatedString,utility::Span>> _magic = (((module_names_and_spans.value())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,utility::Span>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,utility::Span> name_and_span = (_magic_value.value());
{
TRY((((names).push(((name_and_span).template get<0>())))));
JaktInternal::Optional<types::LoadedModule> maybe_loaded_module = ((((*this).program))->get_loaded_module(((name_and_span).template get<0>())));
if ((!(((maybe_loaded_module).has_value())))){
JaktInternal::Optional<jakt__path::Path> const maybe_file_name = TRY((((((*this).compiler))->search_for_path(((name_and_span).template get<0>())))));
jakt__path::Path const file_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<jakt__path::Path,ErrorOr<void>>{
auto __jakt_enum_value = (((maybe_file_name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((maybe_file_name.value()));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY((((*this).get_root_path())))).parent())))).join(((name_and_span).template get<0>())))))).replace_extension(TRY(DeprecatedString::from_utf8("jakt"sv)))))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("No module in module set {{{}}} was found"sv)),TRY((utility::join(names,TRY(DeprecatedString::from_utf8(", "sv)))))))),((((import_).module_name)).span())))));
return {};
}
JaktInternal::Tuple<DeprecatedString,utility::Span> const module_name_module_span_ = (module_name_and_span.value());
DeprecatedString const module_name = ((module_name_module_span_).template get<0>());
utility::Span const module_span = ((module_name_module_span_).template get<1>());

DeprecatedString const sanitized_module_name = ((module_name).replace(TRY(DeprecatedString::from_utf8(":"sv)),TRY(DeprecatedString::from_utf8("_"sv))));
types::ModuleId imported_module_id = types::ModuleId(static_cast<size_t>(0ULL));
JaktInternal::Optional<types::LoadedModule> maybe_loaded_module = ((((*this).program))->get_loaded_module(sanitized_module_name));
if ((!(((maybe_loaded_module).has_value())))){
JaktInternal::Optional<jakt__path::Path> const maybe_file_name = TRY((((((*this).compiler))->search_for_path(module_name))));
jakt__path::Path const file_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<jakt__path::Path,ErrorOr<void>>{
auto __jakt_enum_value = (((maybe_file_name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((maybe_file_name.value()));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY((((*this).get_root_path())))).parent())))).join(module_name))))).replace_extension(TRY(DeprecatedString::from_utf8("jakt"sv)))))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
utility::FileId const file_id = TRY((((((*this).compiler))->get_file_id_or_register(file_name))));
JaktInternal::Optional<parser::ParsedNamespace> const parsed_namespace = TRY((((*this).lex_and_parse_file_contents(file_id))));
if ((!(((parsed_namespace).has_value())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Module '{}' not found"sv)),module_name))),module_span))));
return {};
}
types::ModuleId const original_current_module_id = ((*this).current_module_id);
(imported_module_id = TRY((((*this).create_module(sanitized_module_name,false,((file_name).to_string()))))));
TRY((((((*this).program))->set_loaded_module(sanitized_module_name,types::LoadedModule(imported_module_id,file_id)))));
(((*this).current_module_id) = imported_module_id);
types::ScopeId const imported_scope_id = TRY((((*this).create_scope(((*this).root_scope_id()),false,TRY((__jakt_format((StringView::from_string_literal("module({})"sv)),sanitized_module_name))),false))));
NonnullRefPtr<types::Scope> imported_scope = TRY((((*this).get_scope(imported_scope_id))));
(((imported_scope)->namespace_name) = sanitized_module_name);
TRY((((*this).typecheck_module((parsed_namespace.value()),imported_scope_id))));
(((*this).current_module_id) = original_current_module_id);
}
else {
(imported_module_id = (((maybe_loaded_module.value())).module_id));
}

JaktInternal::DynamicArray<types::ModuleId> current_module_imports = ((((*this).current_module()))->imports);
TRY((((current_module_imports).push(imported_module_id))));
if (((((import_).import_list)).is_empty())){
JaktInternal::Dictionary<DeprecatedString,types::ModuleId> scope_imports = ((TRY((((*this).get_scope(scope_id)))))->imports);
DeprecatedString import_name = module_name;
if (((((import_).alias_name)).has_value())){
(import_name = TRY(((((((import_).alias_name).value())).literal_name()))));
}
TRY((((scope_imports).set(import_name,imported_module_id))));
}
else if (((((import_).import_list)).index() == 1 /* All */)){
NonnullRefPtr<types::Scope> const import_scope = TRY((((*this).get_scope(types::ScopeId(imported_module_id,static_cast<size_t>(0ULL))))));
{
JaktInternal::DictionaryIterator<DeprecatedString,types::VarId> _magic = ((((import_scope)->vars)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::VarId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::VarId> name__var_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::VarId> const jakt__name__var_id__ = name__var_id__;
DeprecatedString const name = ((jakt__name__var_id__).template get<0>());
types::VarId const var_id = ((jakt__name__var_id__).template get<1>());

TRY((((*this).add_var_to_scope(scope_id,name,var_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<DeprecatedString,types::Value> _magic = ((((import_scope)->comptime_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::Value> name__value__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::Value> const jakt__name__value__ = name__value__;
DeprecatedString const name = ((jakt__name__value__).template get<0>());
types::Value const value = ((jakt__name__value__).template get<1>());

TRY((((*this).add_comptime_binding_to_scope(scope_id,name,value,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<DeprecatedString,types::StructId> _magic = ((((import_scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::StructId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::StructId> name__struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::StructId> const jakt__name__struct_id__ = name__struct_id__;
DeprecatedString const name = ((jakt__name__struct_id__).template get<0>());
types::StructId const struct_id = ((jakt__name__struct_id__).template get<1>());

TRY((((*this).add_struct_to_scope(scope_id,name,struct_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> _magic = ((((import_scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> name__overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,JaktInternal::DynamicArray<types::FunctionId>> const jakt__name__overload_set__ = name__overload_set__;
DeprecatedString const name = ((jakt__name__overload_set__).template get<0>());
JaktInternal::DynamicArray<types::FunctionId> const overload_set = ((jakt__name__overload_set__).template get<1>());

TRY((((*this).add_function_to_scope(scope_id,name,overload_set,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<DeprecatedString,types::EnumId> _magic = ((((import_scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::EnumId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::EnumId> name__enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::EnumId> const jakt__name__enum_id__ = name__enum_id__;
DeprecatedString const name = ((jakt__name__enum_id__).template get<0>());
types::EnumId const enum_id = ((jakt__name__enum_id__).template get<1>());

TRY((((*this).add_enum_to_scope(scope_id,name,enum_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<DeprecatedString,types::TypeId> _magic = ((((import_scope)->types)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::TypeId> name__type_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::TypeId> const jakt__name__type_id__ = name__type_id__;
DeprecatedString const name = ((jakt__name__type_id__).template get<0>());
types::TypeId const type_id = ((jakt__name__type_id__).template get<1>());

TRY((((*this).add_type_to_scope(scope_id,name,type_id,((((import_).module_name)).span())))));
}

}
}

{
JaktInternal::DictionaryIterator<DeprecatedString,types::TraitId> _magic = ((((import_scope)->traits)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::TraitId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::TraitId> name__trait_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::TraitId> const jakt__name__trait_id__ = name__trait_id__;
DeprecatedString const name = ((jakt__name__trait_id__).template get<0>());
types::TraitId const trait_id = ((jakt__name__trait_id__).template get<1>());

TRY((((*this).add_trait_to_scope(scope_id,name,trait_id,((((import_).module_name)).span())))));
}

}
}

}
else if (((((import_).import_list)).index() == 0 /* List */)){
JaktInternal::DynamicArray<parser::ImportName> const names = ((((import_).import_list)).get<parser::ImportList::List>()).value;
types::ScopeId const import_scope_id = types::ScopeId(imported_module_id,static_cast<size_t>(0ULL));
{
JaktInternal::ArrayIterator<parser::ImportName> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<parser::ImportName> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ImportName imported_name = (_magic_value.value());
{
bool const found = TRY((((*this).find_and_import_name_from_scope(TRY((((imported_name).literal_name()))),((imported_name).span()),TRY((((imported_name).literal_name()))),((imported_name).span()),import_scope_id,scope_id,typechecker::ImportRestrictions::all()))));
if ((!(found))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Imported name '{}' not found in module '{}'"sv)),TRY((((imported_name).literal_name()))),module_name))),((imported_name).span())))));
}
}

}
}

}
}
return {};
}

ErrorOr<JaktInternal::Optional<types::FunctionId>> typechecker::Typechecker::typecheck_method(parser::ParsedFunction const func,types::StructLikeId const parent_id) {
{
JaktInternal::DynamicArray<types::CheckedGenericParameter> parent_generic_parameters = (TRY((DynamicArray<types::CheckedGenericParameter>::create_with({}))));
types::ScopeId parent_scope_id = ((*this).prelude_scope_id());
parser::DefinitionLinkage parent_definition_linkage =  parser::DefinitionLinkage { typename parser::DefinitionLinkage::Internal() } ;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<types::FunctionId>>>{
auto&& __jakt_match_variant = parent_id;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct structure = ((*this).get_struct(struct_id));
(parent_scope_id = ((structure).scope_id));
(parent_definition_linkage = ((structure).definition_linkage));
(parent_generic_parameters = ((structure).generic_parameters));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
(parent_scope_id = ((enum_).scope_id));
(parent_definition_linkage = ((enum_).definition_linkage));
(parent_generic_parameters = ((enum_).generic_parameters));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Trait>();
types::TraitId const& trait_id = __jakt_match_value.value;
{
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait(trait_id));
(parent_scope_id = ((trait_)->scope_id));
(parent_definition_linkage =  parser::DefinitionLinkage { typename parser::DefinitionLinkage::Internal() } );
(parent_generic_parameters = ((trait_)->generic_parameters));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((((!(((((func).generic_parameters)).is_empty()))) || (!(((parent_generic_parameters).is_empty())))) && (!(((func).must_instantiate))))){
return JaktInternal::OptionalNone();
}
JaktInternal::Optional<types::FunctionId> const method_id = TRY((((*this).find_function_matching_signature_in_scope(parent_scope_id,func))));
if (((method_id).has_value())){
TRY((((*this).typecheck_function(func,parent_scope_id))));
return (method_id.value());
}
else {
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("Previously defined function {} not found in scope {}"sv)),((func).name),parent_scope_id)))))));
}

}
}

ErrorOr<void> typechecker::Typechecker::typecheck_extern_import(parser::ParsedExternImport const import_,types::ScopeId const scope_id) {
{
{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((((import_).assigned_namespace)).functions)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction f = (_magic_value.value());
{
if ((!(((((f).linkage)).index() == 1 /* External */)))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Expected all functions in an `import extern` to be be external"sv)),((f).name_span)))));
}
if ((((import_).is_c) && (!(((((f).generic_parameters)).is_empty()))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("imported function '{}' is declared to have C linkage, but is generic"sv)),((f).name)))),((f).name_span),TRY(DeprecatedString::from_utf8("this function may not be generic"sv)),((f).name_span)))));
}
if ((!(((((((f).block)).stmts)).is_empty())))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("imported extern function is not allowed to have a body"sv)),((f).name_span)))));
}
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((((import_).assigned_namespace)).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
if ((!(((((record).definition_linkage)).index() == 1 /* External */)))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Expected all records in an `import extern` to be external"sv)),((record).name_span)))));
}
if ((((import_).is_c) && (!(((((record).generic_parameters)).is_empty()))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("imported {} '{}' is declared to have C linkage, but is generic"sv)),TRY((((((record).record_type)).record_type_name()))),((record).name)))),((record).name_span),TRY((__jakt_format((StringView::from_string_literal("this {} may not be generic"sv)),TRY((((((record).record_type)).record_type_name())))))),((record).name_span)))));
}
}

}
}

}
return {};
}

ErrorOr<types::BlockControlFlow> typechecker::Typechecker::statement_control_flow(NonnullRefPtr<typename types::CheckedStatement> const statement) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 8: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(true) } );
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(false) } );
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Yield>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((TRY((((expr)->control_flow())))).updated( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(false) } )));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::If>();NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Boolean>();bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (val);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((then_block).control_flow));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (((else_statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((*this).statement_control_flow((else_statement.value()))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((((then_block).control_flow)).branch_unify_with(TRY((((*this).maybe_statement_control_flow(else_statement,((then_block).control_flow))))))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Block>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::While>();NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Boolean>();bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (val);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = ((block).control_flow);
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Loop>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = ((block).control_flow);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (might_break);
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
}
else if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (((((block).control_flow)).may_break()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = ((block).control_flow);
switch(__jakt_match_variant.index()) {
case 4: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Expression>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((expr)->control_flow()))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<JaktInternal::Optional<types::StructId>> typechecker::Typechecker::find_struct_in_scope(types::ScopeId const scope_id,DeprecatedString const name) const {
{
return TRY((((((*this).program))->find_struct_in_scope(scope_id,name))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_override(parser::ParsedMethod const method,types::ScopeId const parent_scope_id,JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>>> const all_virtuals) {
{
if (((method).is_override)){
JaktInternal::Optional<JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>>> overrides = ((all_virtuals).get(((((method).parsed_function)).name)));
if (((overrides).has_value())){
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const override_target = (((overrides.value())).pop());
if (((override_target).has_value())){
JaktInternal::Optional<types::FunctionId> const method_id = TRY((((*this).find_function_matching_signature_in_scope(parent_scope_id,((method).parsed_function)))));
NonnullRefPtr<types::CheckedFunction> const method_function = ((*this).get_function((method_id.value())));
if ((!(((((method_function)->return_type_id)).equals((((override_target.value()))->return_type_id)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Override function return type does not match virtual function"sv)),((method_function)->return_type_span).value_or_lazy_evaluated([&] { return ((method_function)->name_span); })))));
}
if ((((method_function)->can_throw) != (((override_target.value()))->can_throw))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Override function throwability does not match virtual function"sv)),((method_function)->name_span)))));
}
if ((((((method_function)->params)).size()) != (((((override_target.value()))->params)).size()))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Override function parameters do not match virtual function"sv)),((method_function)->name_span)))));
return {};
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((method_function)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t param_index = (_magic_value.value());
{
types::CheckedParameter const method_param = ((((method_function)->params))[param_index]);
types::CheckedParameter const virtual_param = (((((override_target.value()))->params))[param_index]);
if ((((((virtual_param).variable))->is_mutable) != ((((method_param).variable))->is_mutable))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Override function parameter mutability does not match virtual function"sv)),((((method_param).variable))->definition_span)))));
}
if (((param_index == static_cast<size_t>(0ULL)) && (((((method_param).variable))->name) == TRY(DeprecatedString::from_utf8("this"sv))))){
continue;
}
if ((!(((((((method_param).variable))->type_id)).equals(((((virtual_param).variable))->type_id)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Override function parameter type does not match virtual function"sv)),((((method_param).variable))->type_span).value_or_lazy_evaluated([&] { return ((((method_param).variable))->definition_span); })))));
}
}

}
}

}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Missing virtual for override"sv)),((((method).parsed_function)).name_span)))));
return {};
}

}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Missing virtual for override"sv)),((((method).parsed_function)).name_span)))));
return {};
}

}
else {
if (((all_virtuals).contains(((((method).parsed_function)).name)))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Missing override keyword on function that is virtual"sv)),((((method).parsed_function)).name_span)))));
}
return {};
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::check_that_type_doesnt_contain_reference(types::TypeId const type_id,utility::Span const span) {
{
if (TRY((((*this).type_contains_reference(type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Reference type ‘{}’ not usable in this context"sv)),TRY((((*this).type_name(type_id,false))))))),span))));
}
}
return {};
}

ErrorOr<JaktInternal::Optional<parser::ParsedNamespace>> typechecker::Typechecker::lex_and_parse_file_contents(utility::FileId const file_id) {
{
JaktInternal::Tuple<JaktInternal::Optional<utility::FileId>,JaktInternal::DynamicArray<u8>> const old_file_state = ((((*this).compiler))->current_file_state());
if ((!(TRY((((((*this).compiler))->set_current_file(file_id))))))){
return JaktInternal::OptionalNone();
}
ScopeGuard __jakt_var_500([&] {
((((*this).compiler))->restore_file_state(old_file_state));
});
JaktInternal::DynamicArray<lexer::Token> const tokens = TRY((lexer::Lexer::lex(((*this).compiler))));
if (((((*this).compiler))->dump_lexer)){
{
JaktInternal::ArrayIterator<lexer::Token> _magic = ((tokens).iterator());
for (;;){
JaktInternal::Optional<lexer::Token> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
outln((StringView::from_string_literal("token: {}"sv)),token);
}

}
}

}
parser::ParsedNamespace const parsed_namespace = TRY((parser::Parser::parse(((*this).compiler),tokens)));
if (((((*this).compiler))->dump_parser)){
outln((StringView::from_string_literal("{:#}"sv)),parsed_namespace);
}
return parsed_namespace;
}
}

ErrorOr<bool> typechecker::Typechecker::find_and_import_name_from_scope(DeprecatedString const from_name,utility::Span const from_span,DeprecatedString const to_name,utility::Span const to_span,types::ScopeId const from_scope_id,types::ScopeId const into_scope_id,typechecker::ImportRestrictions const allow) {
{
bool found = false;
if (((allow).functions)){
JaktInternal::Optional<JaktInternal::DynamicArray<types::FunctionId>> const maybe_overload_set = TRY((((*this).find_functions_with_name_in_scope(from_scope_id,from_name))));
if (((maybe_overload_set).has_value())){
(found = true);
TRY((((*this).add_function_to_scope(into_scope_id,to_name,(maybe_overload_set.value()),to_span))));
}
}
if (((allow).enums)){
JaktInternal::Optional<types::EnumId> const maybe_enum_id = TRY((((((*this).program))->find_enum_in_scope(from_scope_id,from_name))));
if (((maybe_enum_id).has_value())){
(found = true);
TRY((((*this).add_enum_to_scope(into_scope_id,to_name,(maybe_enum_id.value()),to_span))));
}
}
if (((allow).types)){
JaktInternal::Optional<types::TypeId> const maybe_type_id = TRY((((*this).find_type_in_scope(from_scope_id,from_name))));
if (((maybe_type_id).has_value())){
(found = true);
TRY((((*this).add_type_to_scope(into_scope_id,to_name,(maybe_type_id.value()),to_span))));
}
}
if (((allow).structs)){
JaktInternal::Optional<types::StructId> const maybe_struct_id = TRY((((*this).find_struct_in_scope(from_scope_id,from_name))));
if (((maybe_struct_id).has_value())){
(found = true);
TRY((((*this).add_struct_to_scope(into_scope_id,to_name,(maybe_struct_id.value()),to_span))));
}
}
if (((allow).traits)){
JaktInternal::Optional<types::TraitId> const maybe_trait_id = TRY((((*this).find_trait_in_scope(from_scope_id,from_name))));
if (((maybe_trait_id).has_value())){
(found = true);
TRY((((*this).add_trait_to_scope(into_scope_id,to_name,(maybe_trait_id.value()),to_span))));
}
}
if (((allow).namespaces)){
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> const maybe_scope_id = TRY((((*this).find_namespace_in_scope(from_scope_id,from_name,false))));
if (((maybe_scope_id).has_value())){
(found = true);
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(into_scope_id))));
TRY((((((scope)->aliases)).set(to_name,(((maybe_scope_id.value())).template get<0>())))));
}
}
return found;
}
}

ErrorOr<bool> typechecker::Typechecker::validate_argument_label(types::CheckedParameter const param,DeprecatedString const label,utility::Span const span,NonnullRefPtr<typename parser::ParsedExpression> const expr,JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const default_value) {
{
DeprecatedString const name = TRY((((*this).get_argument_name((Tuple{label, span, expr})))));
if ((name == ((((param).variable))->name))){
return true;
}
if ((!(((default_value).has_value())))){
if (((label).is_empty())){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Missing argument label (expected '{}:')"sv)),((((param).variable))->name)))),((expr)->span())))));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Wrong parameter name in argument label (got '{}', expected '{}')"sv)),label,((((param).variable))->name)))),span))));
}

}
return false;
}
}

ErrorOr<bool> typechecker::Typechecker::add_enum_to_scope(types::ScopeId const scope_id,DeprecatedString const name,types::EnumId const enum_id,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::EnumId> const maybe_enum_id = ((((scope)->enums)).get(name));
if (((maybe_enum_id).has_value())){
types::EnumId const existing_enum_id = (maybe_enum_id.value());
utility::Span const definition_span = ((((*this).get_enum(existing_enum_id))).name_span);
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("redefinition of enum {}"sv)),name))),span,TRY((__jakt_format((StringView::from_string_literal("enum {} was first defined here"sv)),name))),definition_span))));
return false;
}
TRY((((((scope)->enums)).set(name,enum_id))));
return true;
}
}

ErrorOr<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>>> typechecker::Typechecker::expand_context_for_bindings(NonnullRefPtr<typename parser::ParsedExpression> const condition,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const acc,JaktInternal::Optional<parser::ParsedBlock> const then_block,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const else_statement,types::ScopeId const scope_id,utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>>>>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.index()) {
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::BinaryOp>();NonnullRefPtr<typename parser::ParsedExpression> const& lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename parser::ParsedExpression> const& rhs = __jakt_match_value.rhs;
{
if (((op).index() == 18 /* LogicalAnd */)){
JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,JaktInternal::Optional<parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>>> const rhs_condition_rhs_then_block_rhs_else_statement_ = TRY((((*this).expand_context_for_bindings(rhs,acc,then_block,else_statement,scope_id,span))));
NonnullRefPtr<typename parser::ParsedExpression> const rhs_condition = ((rhs_condition_rhs_then_block_rhs_else_statement_).template get<0>());
JaktInternal::Optional<parser::ParsedBlock> const rhs_then_block = ((rhs_condition_rhs_then_block_rhs_else_statement_).template get<1>());
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const rhs_else_statement = ((rhs_condition_rhs_then_block_rhs_else_statement_).template get<2>());

NonnullRefPtr<typename parser::ParsedExpression> accumulated_condition = rhs_condition;
return TRY((((*this).expand_context_for_bindings(lhs,accumulated_condition,rhs_then_block,rhs_else_statement,scope_id,span))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::UnaryOp>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::UnaryOperator const& op = __jakt_match_value.op;
{
if (((op).index() == 13 /* IsEnumVariant */)){
NonnullRefPtr<typename parser::ParsedType> const inner = ((op).get<parser::UnaryOperator::IsEnumVariant>()).inner;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const bindings = ((op).get<parser::UnaryOperator::IsEnumVariant>()).bindings;
NonnullRefPtr<typename parser::ParsedExpression> const unary_op_single_condition = TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::UnaryOp>(expr, parser::UnaryOperator { typename parser::UnaryOperator::Is(inner) } ,span)));
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>> outer_if_stmts = (TRY((DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({}))));
bool const ignore_errors_state = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
NonnullRefPtr<typename types::CheckedExpression> const pre_checked_unary_op = TRY((((*this).typecheck_expression(unary_op_single_condition,scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = ignore_errors_state);
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((bindings).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument binding = (_magic_value.value());
{
parser::ParsedVarDecl const var = parser::ParsedVarDecl(((binding).binding),TRY((parser::ParsedType::template __jakt_create<typename parser::ParsedType::Empty>())),false,JaktInternal::OptionalNone(),((binding).span),JaktInternal::OptionalNone());
if (((pre_checked_unary_op)->index() == 6 /* UnaryOp */)){
types::CheckedUnaryOperator const op = ((pre_checked_unary_op)->get<types::CheckedExpression::UnaryOp>()).op;
if (((op).index() == 14 /* IsSome */)){
NonnullRefPtr<typename parser::ParsedExpression> const init = TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::ForcedUnwrap>(expr,span)));
TRY((((outer_if_stmts).push(TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::VarDecl>(var,init,span)))))));
}
else {
NonnullRefPtr<typename parser::ParsedExpression> const enum_variant_arg = TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::EnumVariantArg>(expr,binding,inner,span)));
TRY((((outer_if_stmts).push(TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::VarDecl>(var,enum_variant_arg,span)))))));
}

}
else {
NonnullRefPtr<typename parser::ParsedExpression> const enum_variant_arg = TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::EnumVariantArg>(expr,binding,inner,span)));
TRY((((outer_if_stmts).push(TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::VarDecl>(var,enum_variant_arg,span)))))));
}

}

}
}

NonnullRefPtr<typename parser::ParsedExpression> inner_condition = condition;
if (((then_block).has_value())){
if (((acc).has_value())){
(inner_condition = (acc.value()));
TRY((((outer_if_stmts).push(TRY((parser::ParsedStatement::template __jakt_create<typename parser::ParsedStatement::If>(inner_condition,(then_block.value()),else_statement,span)))))));
}
else {
TRY((((outer_if_stmts).push_values((((((then_block.value())).stmts)))))));
}

}
parser::ParsedBlock const new_then_block = parser::ParsedBlock(outer_if_stmts);
return TRY((((*this).expand_context_for_bindings(unary_op_single_condition,JaktInternal::OptionalNone(),new_then_block,else_statement,scope_id,span))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename parser::ParsedExpression> base_condition = condition;
if (((acc).has_value())){
(base_condition = TRY((parser::ParsedExpression::template __jakt_create<typename parser::ParsedExpression::BinaryOp>(condition, parser::BinaryOperator { typename parser::BinaryOperator::LogicalAnd() } ,(acc.value()),span))));
}
return (Tuple{base_condition, then_block, else_statement});
}
}

ErrorOr<JaktInternal::Optional<types::TraitId>> typechecker::Typechecker::find_trait_in_scope(types::ScopeId const scope_id,DeprecatedString const name) const {
{
return TRY((((((*this).program))->find_trait_in_scope(scope_id,name))));
}
}

NonnullRefPtr<types::Module> typechecker::Typechecker::current_module() const {
{
return ((((*this).program))->get_module(((*this).current_module_id)));
}
}

types::ScopeId typechecker::Typechecker::root_scope_id() const {
{
return types::ScopeId(types::ModuleId(static_cast<size_t>(1ULL)),static_cast<size_t>(0ULL));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_defer(NonnullRefPtr<typename parser::ParsedStatement> const statement,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
bool const was_inside_defer = ((*this).inside_defer);
(((*this).inside_defer) = true);
ScopeGuard __jakt_var_501([&] {
(((*this).inside_defer) = was_inside_defer);
});
NonnullRefPtr<typename types::CheckedStatement> const checked_statement = TRY((((*this).typecheck_statement(statement,scope_id,safety_mode,JaktInternal::OptionalNone()))));
if (((checked_statement)->index() == 5 /* Block */)){
types::CheckedBlock const block = ((checked_statement)->get<types::CheckedStatement::Block>()).block;
if (((((block).yielded_type)).has_value())){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("‘yield’ inside ‘defer’ is meaningless"sv)),span))));
}
}
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Defer>(checked_statement,span)));
}
}

ErrorOr<bool> typechecker::Typechecker::add_function_to_scope(types::ScopeId const parent_scope_id,DeprecatedString const name,JaktInternal::DynamicArray<types::FunctionId> const overload_set,utility::Span const span) {
{
NonnullRefPtr<types::Scope> scope = TRY((((*this).get_scope(parent_scope_id))));
if (((((scope)->functions)).contains(name))){
JaktInternal::DynamicArray<types::FunctionId> const existing_function_binding = ((((scope)->functions))[name]);
{
JaktInternal::ArrayIterator<types::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function_to_add = ((*this).get_function(function_id));
{
JaktInternal::ArrayIterator<types::FunctionId> _magic = ((existing_function_binding).iterator());
for (;;){
JaktInternal::Optional<types::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionId existing_function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const existing_function = ((*this).get_function(existing_function_id));
if (TRY((((function_to_add)->signature_matches(existing_function))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Redefinition of function ‘{}’."sv)),((function_to_add)->name)))),(((((function_to_add)->parsed_function).value())).name_span),TRY(DeprecatedString::from_utf8("Previous definition is here"sv)),(((((existing_function)->parsed_function).value())).name_span)))));
}
}

}
}

TRY((((((((scope)->functions))[name])).push(function_id))));
}

}
}

}
else {
TRY((((((scope)->functions)).set(name,overload_set))));
}

TRY((((*this).set_owner_scope_if_needed(parent_scope_id,overload_set))));
return true;
}
}

ErrorOr<void> typechecker::Typechecker::check_method_access(types::ScopeId const accessor,types::ScopeId const accessee,NonnullRefPtr<types::CheckedFunction> const method,utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((method)->visibility);
switch(__jakt_match_variant.index()) {
case 1: {
{
if ((!(TRY((((*this).scope_can_access(accessor,accessee))))))){
if ((!(((((method)->type)).index() == 0 /* Normal */)))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Can't access constructor ‘{}’, because it is marked private"sv)),((method)->name)))),span,TRY(DeprecatedString::from_utf8("Private constructors are created if any fields are private"sv)),span))));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Can't access method ‘{}’, because it is marked private"sv)),((method)->name)))),span))));
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedVisibility::Restricted>();JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> const& scopes = __jakt_match_value.scopes;
{
TRY((((*this).check_restricted_access(accessor,TRY(DeprecatedString::from_utf8("function"sv)),accessee,((method)->name),scopes,span))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return {};
}

ErrorOr<types::TypeId> typechecker::Typechecker::final_type_resolution_form(types::TypeId const type_id,types::ScopeId const scope_id) const {
{
types::TypeId const mapped_type_id = TRY((((*this).resolve_type_var(type_id,scope_id))));
if ((((((*this).get_type(mapped_type_id)))->index() == 30 /* Self */) && ((((*this).self_type_id)).has_value()))){
return (((*this).self_type_id).value());
}
return mapped_type_id;
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::FunctionId>,types::ScopeId>>> typechecker::Typechecker::find_scoped_functions_with_name_in_scope(types::ScopeId const parent_scope_id,DeprecatedString const function_name) const {
{
return TRY((((((*this).program))->find_scoped_functions_with_name_in_scope(parent_scope_id,function_name))));
}
}

ErrorOr<NonnullRefPtr<interpreter::Interpreter>> typechecker::Typechecker::interpreter() {
{
return TRY((interpreter::Interpreter::create(((*this).compiler),((*this).program),TRY((types::TypecheckFunctions::__jakt_create([this](parser::ParsedBlock parsed_block, types::ScopeId parent_scope_id, types::SafetyMode safety_mode, JaktInternal::Optional<types::TypeId> yield_type_hint) -> ErrorOr<types::CheckedBlock> {
{
return TRY((((*this).typecheck_block(parsed_block,parent_scope_id,safety_mode,yield_type_hint))));
}
}
,[this](NonnullRefPtr<types::CheckedFunction> function) -> ErrorOr<types::FunctionId> {
{
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const id = ((module)->next_function_id());
TRY((((((module)->functions)).push(function))));
return id;
}
}
))),(TRY((DynamicArray<utility::Span>::create_with({})))))));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_enum_methods_predecl(parser::ParsedRecord const parsed_record,types::EnumId const enum_id,types::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::TypeId const enum_type_id = ((((*this).get_enum(enum_id))).type_id);
bool const is_extern = ((((parsed_record).definition_linkage)).index() == 1 /* External */);
{
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((parsed_record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
parser::ParsedFunction const func = ((method).parsed_function);
if ((((func).is_comptime) != comptime_pass)){
continue;
}
if ((generic_pass != (!(((((func).generic_parameters)).is_empty()))))){
continue;
}
types::ScopeId const method_scope_id = TRY((((*this).create_scope(scope_id,((func).can_throw),TRY((__jakt_format((StringView::from_string_literal("method({}::{})"sv)),((parsed_record).name),((func).name)))),true))));
types::ScopeId const block_scope_id = TRY((((*this).create_scope(method_scope_id,((func).can_throw),TRY((__jakt_format((StringView::from_string_literal("method-block({}::{})"sv)),((parsed_record).name),((func).name)))),true))));
bool const is_generic = ((!(((((parsed_record).generic_parameters)).is_empty()))) || (!(((((func).generic_parameters)).is_empty()))));
NonnullRefPtr<types::CheckedFunction> checked_function = TRY((types::CheckedFunction::__jakt_create(((func).name),((func).name_span),TRY((((*this).typecheck_visibility(((method).visibility),scope_id)))),types::unknown_type_id(),JaktInternal::OptionalNone(),(TRY((DynamicArray<types::CheckedParameter>::create_with({})))),TRY((types::FunctionGenerics::__jakt_create(method_scope_id,(TRY((DynamicArray<types::CheckedParameter>::create_with({})))),(TRY((DynamicArray<types::FunctionGenericParameter>::create_with({})))),(TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),block_scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,types::TypeId::none(),false),((func).can_throw),((func).type),((func).linkage),method_scope_id,JaktInternal::OptionalNone(),((!(is_generic)) || is_extern),func,((func).is_comptime),false,false,((func).is_unsafe),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
JaktInternal::DynamicArray<types::FunctionGenericParameter> generic_parameters = (TRY((DynamicArray<types::FunctionGenericParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<parser::ParsedGenericParameter> _magic = ((((func).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedGenericParameter generic_parameter = (_magic_value.value());
{
types::TypeId const type_var_type_id = types::TypeId(((*this).current_module_id),((((((*this).current_module()))->types)).size()));
types::FunctionGenericParameter parameter = TRY((types::FunctionGenericParameter::parameter(type_var_type_id,((generic_parameter).span))));
JaktInternal::DynamicArray<types::TypeId> trait_implementations = (TRY((DynamicArray<types::TypeId>::create_with({}))));
TRY((((((module)->types)).push(TRY((types::Type::template __jakt_create<typename types::Type::TypeVariable>(((generic_parameter).name),trait_implementations)))))));
if (((((generic_parameter).requires_list)).has_value())){
TRY((((*this).fill_trait_requirements((((generic_parameter).requires_list).value()),((((((parameter).checked_parameter)).constraints))),((trait_implementations)),scope_id))));
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
JaktInternal::Optional<parser::ParsedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedParameter param = (_magic_value.value());
{
if ((((((param).variable)).name) == TRY(DeprecatedString::from_utf8("this"sv)))){
NonnullRefPtr<types::CheckedVariable> const checked_variable = TRY((types::CheckedVariable::__jakt_create(((((param).variable)).name),enum_type_id,((((param).variable)).is_mutable),((((param).variable)).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,JaktInternal::OptionalNone())))));
}
else {
types::TypeId const param_type = TRY((((*this).typecheck_typename(((((param).variable)).parsed_type),method_scope_id,((((param).variable)).name)))));
NonnullRefPtr<types::CheckedVariable> const checked_variable = TRY((types::CheckedVariable::__jakt_create(((((param).variable)).name),param_type,((((param).variable)).is_mutable),((((param).variable)).span),((((((param).variable)).parsed_type))->span()), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> default_value = JaktInternal::OptionalNone();
if (((((param).default_argument)).has_value())){
types::TypeId const param_type = TRY((((*this).typecheck_typename(((((param).variable)).parsed_type),method_scope_id,((((param).variable)).name)))));
(default_value = TRY((((*this).typecheck_expression((((param).default_argument).value()),scope_id, types::SafetyMode { typename types::SafetyMode::Safe() } ,param_type)))));
}
TRY((((checked_function)->add_param(types::CheckedParameter(((param).requires_label),checked_variable,default_value)))));
}

}

}
}

TRY((((*this).add_function_to_scope(scope_id,((func).name),(TRY((DynamicArray<types::FunctionId>::create_with({function_id})))),((parsed_record).name_span)))));
types::TypeId const function_return_type_id = TRY((((*this).typecheck_typename(((func).return_type),method_scope_id,JaktInternal::OptionalNone()))));
(((checked_function)->return_type_id) = function_return_type_id);
}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::dump_try_hint(utility::Span const span) const {
{
outln((StringView::from_string_literal("{{\"type\":\"try\",\"file_id\":{},\"position\":{}}}"sv)),((((span).file_id)).id),((span).start));
}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_methods_predecl(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
JaktInternal::DynamicArray<types::ScopeId> const children = ((TRY((((*this).get_scope(scope_id)))))->children);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((parsed_namespace).namespaces)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
parser::ParsedNamespace const child_namespace = ((((parsed_namespace).namespaces))[i]);
types::ScopeId const child_namespace_scope_id = ((children)[i]);
TRY((((*this).typecheck_namespace_methods_predecl(child_namespace,child_namespace_scope_id,comptime_pass,generic_pass))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord parsed_record = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((parsed_record).name)))));
if ((!(((struct_id).has_value())))){
return JaktInternal::LoopContinue{};
}
TRY((((*this).typecheck_struct_methods_predecl(parsed_record,(struct_id.value()),((((*this).get_struct((struct_id.value())))).scope_id),comptime_pass,generic_pass))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
{
JaktInternal::Optional<types::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,((parsed_record).name)))));
if ((!(((struct_id).has_value())))){
return JaktInternal::LoopContinue{};
}
TRY((((*this).typecheck_struct_methods_predecl(parsed_record,(struct_id.value()),((((*this).get_struct((struct_id.value())))).scope_id),comptime_pass,generic_pass))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((parsed_record).name)))));
if ((!(((enum_id).has_value())))){
return JaktInternal::LoopContinue{};
}
TRY((((*this).typecheck_enum_methods_predecl(parsed_record,(enum_id.value()),((((*this).get_enum((enum_id.value())))).scope_id),comptime_pass,generic_pass))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
{
JaktInternal::Optional<types::EnumId> const enum_id = TRY((((((*this).program))->find_enum_in_scope(scope_id,((parsed_record).name)))));
if ((!(((enum_id).has_value())))){
return JaktInternal::LoopContinue{};
}
TRY((((*this).typecheck_enum_methods_predecl(parsed_record,(enum_id.value()),((((*this).get_enum((enum_id.value())))).scope_id),comptime_pass,generic_pass))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

}
return {};
}

ErrorOr<void> typechecker::Typechecker::typecheck_module(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
TRY((((*this).typecheck_namespace_imports(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_predecl(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_methods_predecl(parsed_namespace,scope_id,true,false))));
TRY((((*this).typecheck_namespace_methods_predecl(parsed_namespace,scope_id,false,false))));
TRY((((*this).typecheck_namespace_methods_predecl(parsed_namespace,scope_id,true,true))));
TRY((((*this).typecheck_namespace_methods_predecl(parsed_namespace,scope_id,false,true))));
TRY((((*this).typecheck_namespace_aliases(parsed_namespace,scope_id,typechecker::ImportRestrictions(false,true,true,true,true,true)))));
TRY((((*this).typecheck_namespace_fields(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_constructors(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_function_predecl(parsed_namespace,scope_id,true,false))));
TRY((((*this).typecheck_namespace_function_predecl(parsed_namespace,scope_id,false,false))));
TRY((((*this).typecheck_namespace_function_predecl(parsed_namespace,scope_id,true,true))));
TRY((((*this).typecheck_namespace_function_predecl(parsed_namespace,scope_id,false,true))));
TRY((((*this).typecheck_namespace_aliases(parsed_namespace,scope_id,typechecker::ImportRestrictions(true,false,false,false,false,false)))));
TRY((((*this).typecheck_namespace_default_fields(parsed_namespace,scope_id))));
TRY((((*this).typecheck_namespace_declarations(parsed_namespace,scope_id,true,false))));
TRY((((*this).typecheck_namespace_declarations(parsed_namespace,scope_id,true,true))));
TRY((((*this).typecheck_namespace_declarations(parsed_namespace,scope_id,false,false))));
TRY((((*this).typecheck_namespace_declarations(parsed_namespace,scope_id,false,true))));
}
return {};
}

ErrorOr<void> typechecker::Typechecker::error_with_hint(DeprecatedString const message,utility::Span const span,DeprecatedString const hint,utility::Span const hint_span) {
{
if ((!(((*this).ignore_errors)))){
TRY((((((((*this).compiler))->errors)).push( error::JaktError { typename error::JaktError::MessageWithHint(message,span,hint,hint_span) } ))));
}
}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_var_decl(parser::ParsedVarDecl const var,NonnullRefPtr<typename parser::ParsedExpression> const init,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span) {
{
types::TypeId lhs_type_id = TRY((((*this).typecheck_typename(((var).parsed_type),scope_id,((var).name)))));
NonnullRefPtr<typename types::CheckedExpression> checked_expr = TRY((((*this).typecheck_expression(init,scope_id,safety_mode,lhs_type_id))));
types::TypeId const rhs_type_id = ((checked_expr)->type());
if (((rhs_type_id).equals(types::void_type_id()))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot assign `void` to a variable"sv)),((checked_expr)->span())))));
}
if ((((lhs_type_id).equals(types::unknown_type_id())) && (!(((rhs_type_id).equals(types::unknown_type_id())))))){
(lhs_type_id = rhs_type_id);
}
types::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
if (TRY((((*this).type_contains_reference(lhs_type_id))))){
JaktInternal::Optional<types::ScopeId> const init_scope_id = TRY((((*this).required_scope_id_in_hierarchy_for(checked_expr,scope_id))));
if (TRY((((*this).scope_lifetime_subsumes(scope_id,init_scope_id))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot assign a reference to a variable that outlives the reference"sv)),((checked_expr)->span())))));
}
}
NonnullRefPtr<typename types::Type> const lhs_type = ((*this).get_type(lhs_type_id));
if (((checked_expr)->index() == 25 /* OptionalNone */)){
utility::Span const span = ((checked_expr)->get<types::CheckedExpression::OptionalNone>()).span;
types::TypeId const type_id = ((checked_expr)->get<types::CheckedExpression::OptionalNone>()).type_id;
if (((lhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = ((lhs_type)->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((lhs_type)->get<types::Type::GenericInstance>()).args;
if ((!((((id).equals(optional_struct_id)) || ((id).equals(weak_ptr_struct_id)))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot assign None to a non-optional type"sv)),span))));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot assign None to a non-optional type"sv)),span))));
}

}
if (((lhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = ((lhs_type)->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((lhs_type)->get<types::Type::GenericInstance>()).args;
if (((id).equals(weak_ptr_struct_id))){
if (((!(((lhs_type_id).equals(rhs_type_id)))) && ((!(((((args)[static_cast<i64>(0LL)])).equals(rhs_type_id)))) && ((!(((rhs_type_id).equals(types::unknown_type_id())))) && (!(((*this).is_subclass_of(((args)[static_cast<i64>(0LL)]),rhs_type_id)))))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),((checked_expr)->span())))));
}
}
else if (((id).equals(optional_struct_id))){
if (((!(((lhs_type_id).equals(rhs_type_id)))) && ((!(((((args)[static_cast<i64>(0LL)])).equals(rhs_type_id)))) && ((!(((rhs_type_id).equals(types::unknown_type_id())))) && (!(((*this).is_subclass_of(((args)[static_cast<i64>(0LL)]),rhs_type_id)))))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),((checked_expr)->span())))));
}
}
else {
if (((!(((lhs_type_id).equals(rhs_type_id)))) && (!(((rhs_type_id).equals(types::unknown_type_id())))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),((checked_expr)->span())))));
}
}

}
else if (((lhs_type)->is_builtin())){
JaktInternal::Optional<types::NumberConstant> const number_constant = ((checked_expr)->to_number_constant(((*this).program)));
bool is_rhs_zero = false;
if (((number_constant).has_value())){
(is_rhs_zero = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<NonnullRefPtr<typename types::CheckedStatement>>>{
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
if (((!((((*this).is_numeric(lhs_type_id)) && is_rhs_zero))) && (((*this).is_integer(lhs_type_id)) ^ ((*this).is_integer(rhs_type_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),((checked_expr)->span())))));
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::Garbage>(span)));
}
}
else {
if (((!(((lhs_type_id).equals(rhs_type_id)))) && ((!(((rhs_type_id).equals(types::unknown_type_id())))) && (!(((*this).is_subclass_of(lhs_type_id,rhs_type_id))))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(lhs_type_id,false)))),TRY((((*this).type_name(rhs_type_id,false))))))),((checked_expr)->span())))));
}
}

NonnullRefPtr<types::CheckedVariable> const checked_var = TRY((types::CheckedVariable::__jakt_create(((var).name),lhs_type_id,((var).is_mutable),((var).span),JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if ((((*this).dump_type_hints) && ((((var).inlay_span)).has_value()))){
TRY((((*this).dump_type_hint(lhs_type_id,(((var).inlay_span).value())))));
}
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const var_id = TRY((((module)->add_variable(checked_var))));
TRY((((*this).add_var_to_scope(scope_id,((var).name),var_id,((checked_var)->definition_span)))));
return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::VarDecl>(var_id,checked_expr,span)));
}
}

bool typechecker::Typechecker::is_subclass_of(types::TypeId const ancestor_type_id,types::TypeId const child_type_id) const {
{
NonnullRefPtr<typename types::Type> const ancestor_type = ((*this).get_type(ancestor_type_id));
NonnullRefPtr<typename types::Type> const child_type = ((*this).get_type(child_type_id));
if (((ancestor_type)->index() == 23 /* Struct */)){
types::StructId const ancestor_struct_id = ((ancestor_type)->get<types::Type::Struct>()).value;
if (((child_type)->index() == 23 /* Struct */)){
types::StructId const child_struct_id = ((child_type)->get<types::Type::Struct>()).value;
types::CheckedStruct ancestor_struct = ((*this).get_struct(ancestor_struct_id));
types::StructId current_struct_id = child_struct_id;
for (;;){
types::CheckedStruct const current_struct = ((*this).get_struct(current_struct_id));
if (((((current_struct).super_struct_id)).has_value())){
if (((ancestor_struct_id).equals((((current_struct).super_struct_id).value())))){
return true;
}
(current_struct_id = (((current_struct).super_struct_id).value()));
}
else {
return false;
}

}
return false;
}
else {
return false;
}

}
else {
return false;
}

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
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord parsed_record = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
{
TRY((((*this).typecheck_struct_predecl_initial(parsed_record,((struct_index++)),module_struct_len,scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
{
TRY((((*this).typecheck_struct_predecl_initial(parsed_record,((struct_index++)),module_struct_len,scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
{
TRY((((*this).typecheck_enum_predecl_initial(parsed_record,((enum_index++)),module_enum_len,scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
{
TRY((((*this).typecheck_enum_predecl_initial(parsed_record,((enum_index++)),module_enum_len,scope_id))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedNamespace> _magic = ((((parsed_namespace).namespaces)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNamespace namespace_ = (_magic_value.value());
{
DeprecatedString debug_name = TRY(DeprecatedString::from_utf8("namespace("sv));
if (((((namespace_).name)).has_value())){
(debug_name += (((namespace_).name).value()));
}
else {
(debug_name += TRY(DeprecatedString::from_utf8("unnamed-namespace"sv)));
}

(debug_name += TRY(DeprecatedString::from_utf8(")"sv)));
types::ScopeId const parent_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::ScopeId,ErrorOr<void>>{
auto __jakt_enum_value = (((((namespace_).import_path_if_extern)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::ScopeId(types::ModuleId(static_cast<size_t>(1ULL)),static_cast<size_t>(0ULL)));
}
else {
return JaktInternal::ExplicitValue(scope_id);
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
types::ScopeId const namespace_scope_id = TRY((((*this).create_scope(parent_scope_id,false,debug_name,false))));
NonnullRefPtr<types::Scope> child_scope = TRY((((*this).get_scope(namespace_scope_id))));
(((child_scope)->namespace_name) = ((namespace_).name));
(((child_scope)->import_path_if_extern) = ((namespace_).import_path_if_extern));
(((child_scope)->before_extern_include) = ((namespace_).generating_import_extern_before_include));
(((child_scope)->after_extern_include) = ((namespace_).generating_import_extern_after_include));
if (((((namespace_).import_path_if_extern)).has_value())){
TRY((((((child_scope)->resolution_mixins)).push(scope_id))));
}
NonnullRefPtr<types::Scope> parent_scope = TRY((((*this).get_scope(scope_id))));
TRY((((((parent_scope)->children)).push(namespace_scope_id))));
TRY((((*this).typecheck_namespace_predecl(namespace_,namespace_scope_id))));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedTrait> _magic = ((((parsed_namespace).traits)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedTrait> const _magic_value = ((_magic).next());
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
JaktInternal::Optional<parser::ParsedTrait> const _magic_value = ((_magic).next());
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
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("can't find trait that has been previous added"sv))))));
}

}

}
}

(struct_index = static_cast<size_t>(0ULL));
(enum_index = static_cast<size_t>(0ULL));
{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((parsed_namespace).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord parsed_record = (_magic_value.value());
{
types::StructId const struct_id = types::StructId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(struct_index,module_struct_len)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((parsed_record).record_type);
switch(__jakt_match_variant.index()) {
case 0: {
{
TRY((((*this).typecheck_struct_predecl(parsed_record,struct_id,scope_id))));
((struct_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
{
TRY((((*this).typecheck_struct_predecl(parsed_record,struct_id,scope_id))));
((struct_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
{
types::EnumId const enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
TRY((((*this).typecheck_enum_predecl(parsed_record,enum_id,scope_id))));
((enum_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
{
types::EnumId const enum_id = types::EnumId(((*this).current_module_id),(JaktInternal::checked_add<size_t>(enum_index,module_enum_len)));
TRY((((*this).typecheck_enum_predecl(parsed_record,enum_id,scope_id))));
((enum_index++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedExternalTraitImplementation> _magic = ((((parsed_namespace).external_trait_implementations)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedExternalTraitImplementation> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedExternalTraitImplementation implementation = (_magic_value.value());
{
types::TypeId const for_type = TRY((((*this).typecheck_typename(((implementation).for_type),scope_id,JaktInternal::OptionalNone()))));
JaktInternal::Optional<types::TypeId> const old_self_type_id = ((*this).self_type_id);
(((*this).self_type_id) = for_type);
ScopeGuard __jakt_var_502([&] {
{
(((*this).self_type_id) = old_self_type_id);
}

});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
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
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((TRY((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))) == TRY(DeprecatedString::from_utf8("this"sv)))){
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
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((trait_name).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait((trait_id.value())));
{
JaktInternal::DictionaryIterator<DeprecatedString,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::FunctionId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
DeprecatedString const name = ((jakt__name__function_id__).template get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).template get<1>());

if (((TRY((((*this).find_functions_with_name_in_scope(((struct_).scope_id),name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function(function_id));
if (((((((function)->block)).statements)).is_empty())){
continue;
}
NonnullRefPtr<types::CheckedFunction> replaced_function = TRY((((function)->copy())));
types::GenericInferences const inferences = ((*this).generic_inferences);
TRY((((replaced_function)->map_types((([inferences](types::TypeId type_id) -> ErrorOr<types::TypeId> {
{
return TRY((((inferences).map(type_id))));
}
}
))))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const new_function_id = TRY((((module)->add_function(replaced_function))));
TRY((((*this).add_function_to_scope(((struct_).scope_id),name,(TRY((DynamicArray<types::FunctionId>::create_with({new_function_id})))),((trait_name).name_span)))));
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
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((TRY((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))) == TRY(DeprecatedString::from_utf8("this"sv)))){
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
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((trait_name).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait((trait_id.value())));
{
JaktInternal::DictionaryIterator<DeprecatedString,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::FunctionId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
DeprecatedString const name = ((jakt__name__function_id__).template get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).template get<1>());

if (((TRY((((*this).find_functions_with_name_in_scope(((struct_).scope_id),name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function(function_id));
if (((((((function)->block)).statements)).is_empty())){
continue;
}
NonnullRefPtr<types::CheckedFunction> replaced_function = TRY((((function)->copy())));
types::GenericInferences const inferences = ((*this).generic_inferences);
TRY((((replaced_function)->map_types((([inferences](types::TypeId type_id) -> ErrorOr<types::TypeId> {
{
return TRY((((inferences).map(type_id))));
}
}
))))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const new_function_id = TRY((((module)->add_function(replaced_function))));
TRY((((*this).add_function_to_scope(((struct_).scope_id),name,(TRY((DynamicArray<types::FunctionId>::create_with({new_function_id})))),((trait_name).name_span)))));
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
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((TRY((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))) == TRY(DeprecatedString::from_utf8("this"sv)))){
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
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((trait_name).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait((trait_id.value())));
{
JaktInternal::DictionaryIterator<DeprecatedString,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::FunctionId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
DeprecatedString const name = ((jakt__name__function_id__).template get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).template get<1>());

if (((TRY((((*this).find_functions_with_name_in_scope(((enum_).scope_id),name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function(function_id));
if (((((((function)->block)).statements)).is_empty())){
continue;
}
NonnullRefPtr<types::CheckedFunction> replaced_function = TRY((((function)->copy())));
types::GenericInferences const inferences = ((*this).generic_inferences);
TRY((((replaced_function)->map_types((([inferences](types::TypeId type_id) -> ErrorOr<types::TypeId> {
{
return TRY((((inferences).map(type_id))));
}
}
))))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const new_function_id = TRY((((module)->add_function(replaced_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),name,(TRY((DynamicArray<types::FunctionId>::create_with({new_function_id})))),((trait_name).name_span)))));
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
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
JaktInternal::Optional<types::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((TRY((((((((((((method).parsed_function)).params)).first())).map([](auto& _value) { return _value.variable; }))).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))) == TRY(DeprecatedString::from_utf8("this"sv)))){
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
JaktInternal::Optional<parser::ParsedNameWithGenericParameters> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNameWithGenericParameters trait_name = (_magic_value.value());
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,((trait_name).name)))));
if (((trait_id).has_value())){
NonnullRefPtr<types::CheckedTrait> const trait_ = ((*this).get_trait((trait_id.value())));
{
JaktInternal::DictionaryIterator<DeprecatedString,types::FunctionId> _magic = ((((trait_)->methods)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,types::FunctionId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,types::FunctionId> name__function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,types::FunctionId> const jakt__name__function_id__ = name__function_id__;
DeprecatedString const name = ((jakt__name__function_id__).template get<0>());
types::FunctionId const function_id = ((jakt__name__function_id__).template get<1>());

if (((TRY((((*this).find_functions_with_name_in_scope(((enum_).scope_id),name))))).has_value())){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function(function_id));
if (((((((function)->block)).statements)).is_empty())){
continue;
}
NonnullRefPtr<types::CheckedFunction> replaced_function = TRY((((function)->copy())));
types::GenericInferences const inferences = ((*this).generic_inferences);
TRY((((replaced_function)->map_types((([inferences](types::TypeId type_id) -> ErrorOr<types::TypeId> {
{
return TRY((((inferences).map(type_id))));
}
}
))))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const new_function_id = TRY((((module)->add_function(replaced_function))));
TRY((((*this).add_function_to_scope(((enum_).scope_id),name,(TRY((DynamicArray<types::FunctionId>::create_with({new_function_id})))),((trait_name).name_span)))));
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
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Cannot implement traits for type '{}'"sv)),TRY((((*this).type_name(for_type,false))))))),((((implementation).for_type))->span())))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> typechecker::Typechecker::typecheck_inline_cpp(parser::ParsedBlock const block,utility::Span const span,types::SafetyMode const safety_mode) {
{
if (((safety_mode).index() == 0 /* Safe */)){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Use of inline cpp block outside of unsafe block"sv)),span))));
}
JaktInternal::DynamicArray<DeprecatedString> strings = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedStatement>> _magic = ((((block).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedStatement> statement = (_magic_value.value());
{
if (((statement)->index() == 0 /* Expression */)){
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((statement)->get<parser::ParsedStatement::Expression>()).expr;
if (((expr)->index() == 2 /* QuotedString */)){
DeprecatedString const val = ((expr)->get<parser::ParsedExpression::QuotedString>()).val;
utility::Span const span = ((expr)->get<parser::ParsedExpression::QuotedString>()).span;
TRY((((strings).push(val))));
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Expected block of strings"sv)),span))));
}

}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Expected block of strings"sv)),span))));
}

}

}
}

return TRY((types::CheckedStatement::template __jakt_create<typename types::CheckedStatement::InlineCpp>(strings,span)));
}
}

bool typechecker::Typechecker::is_struct(types::TypeId const type_id) const {
{
if (((((*this).get_type(type_id)))->index() == 23 /* Struct */)){
types::StructId const struct_id = ((((*this).get_type(type_id)))->get<types::Type::Struct>()).value;
return ((((((*this).get_struct(struct_id))).record_type)).index() == 0 /* Struct */);
}
else {
return false;
}

}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_expression(NonnullRefPtr<typename parser::ParsedExpression> const expr,types::ScopeId const scope_id,types::SafetyMode const safety_mode,JaktInternal::Optional<types::TypeId> const type_hint) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.index()) {
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedStruct>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
DeprecatedString const& field_name = __jakt_match_value.field_name;
utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_indexed_struct(expr,field_name,scope_id,is_optional,safety_mode,span)))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::ComptimeIndex>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename parser::ParsedExpression> const& index = __jakt_match_value.index;
utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_comptime_index(expr,index,scope_id,is_optional,safety_mode,span)))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Boolean>();bool const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_503; {
TRY((((*this).unify_with_type(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ),type_hint,span))));
__jakt_var_503 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Boolean>(val,span))); goto __jakt_label_439;

}
__jakt_label_439:; __jakt_var_503.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::NumericConstant>();parser::NumericConstant const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_504; {
JaktInternal::Optional<types::TypeId> type_hint_unwrapped = type_hint;
if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
types::StructId const id = ((((*this).get_type((type_hint.value()))))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type((type_hint.value()))))->get<types::Type::GenericInstance>()).args;
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
if (((id).equals(optional_struct_id))){
(type_hint_unwrapped = ((args)[static_cast<i64>(0LL)]));
}
}
__jakt_var_504 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::I8>();
i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I8(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } )))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::I16>();
i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I16(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } )))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::I32>();
i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } )))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::I64>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::I64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } )))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::U8>();
u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U8(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } )))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::U16>();
u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U16(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } )))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::U32>();
u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } )))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::U64>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::U64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } )))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::USize>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::USize(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } )))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::F32>();
f32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::F32(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::F32() } )))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::NumericConstant::F64>();
f64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::NumericConstant>( types::CheckedNumericConstant { typename types::CheckedNumericConstant::F64(val) } ,span,types::builtin( types::BuiltinType { typename types::BuiltinType::F64() } )))));
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
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_440;

}
__jakt_label_440:; __jakt_var_504.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::SingleQuotedString>();DeprecatedString const& val = __jakt_match_value.val;
JaktInternal::Optional<DeprecatedString> const& prefix = __jakt_match_value.prefix;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (TRY((prefix.try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))));
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8(""sv))) {
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::CharacterConstant>(val,span))));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("b"sv))) {
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::ByteConstant>(val,span))));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("c"sv))) {
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::CCharacterConstant>(val,span))));
}
else {
{
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("Unknown string prefix {}"sv)),prefix)))))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::QuotedString>();DeprecatedString const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_505; {
if (((*this).dump_try_hints)){
TRY((((*this).dump_try_hint(span))));
}
__jakt_var_505 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = ((((type_hint).has_value()) && (!((((type_hint.value())).equals(types::unknown_type_id()))))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_506; {
types::TypeId type_id = TRY((((*this).strip_optional_from_type(TRY((((((*this).generic_inferences)).map((type_hint.value())))))))));
types::TypeId const prelude_string_type_id = TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("String"sv))))));
types::TypeId const prelude_string_view_type_id = TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("StringView"sv))))));
bool may_throw = ((type_id).equals(prelude_string_type_id));
if (((!(((type_id).equals(prelude_string_type_id)))) && (!(((type_id).equals(prelude_string_view_type_id)))))){
if (((((*this).get_type(type_id)))->is_concrete())){
JaktInternal::Optional<typechecker::TraitImplementationDescriptor> const trait_implementation = TRY((((*this).find_any_singular_trait_implementation(type_id,(TRY((DynamicArray<DeprecatedString>::create_with({TRY(DeprecatedString::from_utf8("FromStringLiteral"sv)), TRY(DeprecatedString::from_utf8("ThrowingFromStringLiteral"sv))})))),scope_id,span))));
if ((!(((trait_implementation).has_value())))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Type {} cannot be used as an overloaded string literal type"sv)),TRY((((*this).type_name(type_id,true))))))),span,TRY((__jakt_format((StringView::from_string_literal("Consider implementing the FromStringLiteral trait for {}"sv)),TRY((((*this).type_name(type_id,false))))))),span))));
(type_id = prelude_string_type_id);
}
else {
(may_throw = ((((trait_implementation.value())).trait_name) == TRY(DeprecatedString::from_utf8("ThrowingFromStringLiteral"sv))));
}

}
else if ((!(((((*this).get_type(type_id)))->is_concrete())))){
(type_id = TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("String"sv)))))));
(may_throw = true);
}
}
TRY((((*this).unify((type_hint.value()),span,type_id,span))));
__jakt_var_506 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::QuotedString>(types::CheckedStringLiteral( types::StringLiteral { typename types::StringLiteral::Static(val) } ,type_id,may_throw),span))); goto __jakt_label_442;

}
__jakt_label_442:; __jakt_var_506.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::QuotedString>(types::CheckedStringLiteral( types::StringLiteral { typename types::StringLiteral::Static(val) } ,TRY((((*this).prelude_struct_type_named(TRY(DeprecatedString::from_utf8("String"sv)))))),true),span))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_441;

}
__jakt_label_441:; __jakt_var_505.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Call>();parser::ParsedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_507; {
__jakt_var_507 = TRY((((*this).typecheck_call(call,scope_id,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),safety_mode,type_hint,false)))); goto __jakt_label_443;

}
__jakt_label_443:; __jakt_var_507.release_value(); }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::MethodCall>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::ParsedCall const& call = __jakt_match_value.call;
utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_508; {
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const checked_expr_type_id = ((checked_expr)->type());
bool found_optional = false;
JaktInternal::Optional<types::StructLikeId> const parent_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructLikeId>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(TRY((((*this).final_type_resolution_form(checked_expr_type_id,scope_id))))));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),id) } ));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Enum(JaktInternal::OptionalNone(),id) } ));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("String"sv))))))) } ));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::StructLikeId>> __jakt_var_509; {
__jakt_var_509 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructLikeId>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::StructLikeId>> __jakt_var_510; {
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
JaktInternal::Optional<types::StructLikeId> struct_id = JaktInternal::OptionalNone();
if ((!(((id).equals(optional_struct_id))))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Can't use ‘{}’ as an optional type in optional chained call"sv)),((((*this).get_struct(id))).name)))),span))));
}
else {
(found_optional = true);
(struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructLikeId>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((args)[static_cast<i64>(0LL)])));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id) } );
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id) } );
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Enum(JaktInternal::OptionalNone(),id) } );
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Enum(JaktInternal::OptionalNone(),id) } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::StructLikeId> __jakt_var_511; {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Can't use non-struct type as an optional type in optional chained call"sv)),span))));
(found_optional = false);
__jakt_var_511 =  types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),optional_struct_id) } ; goto __jakt_label_447;

}
__jakt_label_447:; __jakt_var_511.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}

__jakt_var_510 = static_cast<JaktInternal::Optional<types::StructLikeId>>(struct_id.value_or_lazy_evaluated([&] { return  types::StructLikeId { typename types::StructLikeId::Struct(JaktInternal::OptionalNone(),optional_struct_id) } ; })); goto __jakt_label_446;

}
__jakt_label_446:; __jakt_var_510.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Struct(args,id) } ));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_445;

}
__jakt_label_445:; __jakt_var_509.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Enum(args,id) } ));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Trait(JaktInternal::OptionalNone(),id) } ));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Trait(args,id) } ));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::TypeVariable>();JaktInternal::DynamicArray<types::TypeId> const& trait_implementations = __jakt_match_value.trait_implementations;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructLikeId>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (((trait_implementations).size()));
if (__jakt_enum_value == static_cast<size_t>(0ULL)) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
else {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructLikeId>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((trait_implementations)[static_cast<i64>(0LL)])));
switch(__jakt_match_variant.index()) {
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
types::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Trait(JaktInternal::OptionalNone(),id) } ));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();types::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<types::StructLikeId>>( types::StructLikeId { typename types::StructLikeId::Trait(args,id) } ));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::StructLikeId> __jakt_var_512; {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("no methods available on value (type: {} {})"sv)),TRY((((((*this).get_type(checked_expr_type_id)))->constructor_name()))),TRY((((*this).type_name(checked_expr_type_id,false))))))),((checked_expr)->span())))));
__jakt_var_512 = JaktInternal::OptionalNone(); goto __jakt_label_448;

}
__jakt_label_448:; __jakt_var_512; }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((is_optional && (!(found_optional)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Optional chain mismatch: expected optional chain, found {}"sv)),TRY((((*this).type_name(checked_expr_type_id,false))))))),((checked_expr)->span())))));
}
NonnullRefPtr<typename types::CheckedExpression> const checked_call_expr = TRY((((*this).typecheck_call(call,scope_id,span,checked_expr,parent_id,safety_mode,type_hint,false))));
types::TypeId const type_id = ((checked_call_expr)->type());
__jakt_var_508 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_call_expr;
switch(__jakt_match_variant.index()) {
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_513; {
types::TypeId result_type = ((call).return_type);
if (is_optional){
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
(result_type = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({result_type}))))))))))));
}
__jakt_var_513 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::MethodCall>(checked_expr,call,span,is_optional,result_type))); goto __jakt_label_449;

}
__jakt_label_449:; __jakt_var_513.release_value(); }));
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("typecheck_call should return `CheckedExpression::Call()`"sv))))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_444;

}
__jakt_label_444:; __jakt_var_508.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Range>();JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& to = __jakt_match_value.to;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_514; {
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> checked_from = JaktInternal::OptionalNone();
JaktInternal::Optional<types::TypeId> from_type = JaktInternal::OptionalNone();
utility::Span from_span = span;
if ((((from).has_value()) && ((!((((from.value()))->index() == 1 /* NumericConstant */))) && (!((((from.value()))->index() == 1 /* NumericConstant */)))))){
(checked_from = TRY((((*this).typecheck_expression((from.value()),scope_id,safety_mode,JaktInternal::OptionalNone())))));
(from_type = (((checked_from.value()))->type()));
(from_span = (((checked_from.value()))->span()));
}
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> checked_to = JaktInternal::OptionalNone();
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
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Range values differ in types"sv)),span))));
}
}
else if (((from).has_value())){
(values_type_id = from_type);
}
else if (((to).has_value())){
(values_type_id = to_type);
}
types::StructId const range_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Range"sv))))));
NonnullRefPtr<typename types::Type> const range_type = TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(range_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({((values_type_id).value_or(types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } )))})))))));
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(range_type))));
__jakt_var_514 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Range>(checked_from,checked_to,span,type_id))); goto __jakt_label_450;

}
__jakt_label_450:; __jakt_var_514.release_value(); }));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Reflect>();NonnullRefPtr<typename parser::ParsedType> const& type = __jakt_match_value.type;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_515; {
types::EnumId const reflected_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::EnumId, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive(TRY(DeprecatedString::from_utf8("Type"sv))))));
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructOrEnumId::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("unreachable"sv))))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::TypeId const reflected_type = TRY((((*this).typecheck_typename(type,scope_id,JaktInternal::OptionalNone()))));
__jakt_var_515 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Reflect>(reflected_type,span,TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Enum>(reflected_type_enum_id)))))))))); goto __jakt_label_451;

}
__jakt_label_451:; __jakt_var_515.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::UnaryOp>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
parser::UnaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_516; {
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 5: {
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone())))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
types::CheckedUnaryOperator const checked_op = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedUnaryOperator, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::PreIncrement() } );
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::PostIncrement() } );
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::PreDecrement() } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::PostDecrement() } );
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Negate() } );
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Dereference() } );
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::RawAddress() } );
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Reference() } );
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::MutableReference() } );
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::LogicalNot() } );
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::BitwiseNot() } );
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::TypeCast>();
parser::TypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedUnaryOperator> __jakt_var_517; {
types::TypeId const type_id = TRY((((*this).typecheck_typename(((cast).parsed_type()),scope_id,JaktInternal::OptionalNone()))));
types::CheckedTypeCast const checked_cast = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedTypeCast, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(({ Optional<types::CheckedTypeCast> __jakt_var_518; {
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
NonnullRefPtr<typename types::Type> const optional_type = TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({type_id})))))));
types::TypeId const optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
__jakt_var_518 =  types::CheckedTypeCast { typename types::CheckedTypeCast::Fallible(optional_type_id) } ; goto __jakt_label_454;

}
__jakt_label_454:; __jakt_var_518.release_value(); }));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue( types::CheckedTypeCast { typename types::CheckedTypeCast::Infallible(type_id) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_517 =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::TypeCast(checked_cast) } ; goto __jakt_label_453;

}
__jakt_label_453:; __jakt_var_517.release_value(); }));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::Sizeof>();
NonnullRefPtr<typename parser::ParsedType> const& unchecked_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedUnaryOperator> __jakt_var_519; {
types::TypeId const type_id = TRY((((*this).typecheck_typename(unchecked_type,scope_id,JaktInternal::OptionalNone()))));
__jakt_var_519 =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Sizeof(type_id) } ; goto __jakt_label_455;

}
__jakt_label_455:; __jakt_var_519.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::UnaryOperator::Is>();
NonnullRefPtr<typename parser::ParsedType> const& unchecked_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<types::CheckedUnaryOperator> __jakt_var_520; {
bool const old_ignore_errors = ((*this).ignore_errors);
(((*this).ignore_errors) = true);
types::TypeId const type_id = TRY((((*this).typecheck_typename(unchecked_type,scope_id,JaktInternal::OptionalNone()))));
(((*this).ignore_errors) = old_ignore_errors);
(((*this).had_an_error) = false);
types::CheckedUnaryOperator operator_is =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::Is(type_id) } ;
if (((unchecked_type)->index() == 0 /* Name */)){
DeprecatedString const name = ((unchecked_type)->get<parser::ParsedType::Name>()).name;
types::TypeId const expr_type_id = ((checked_expr)->type());
if (((((*this).get_type(expr_type_id)))->index() == 24 /* Enum */)){
types::EnumId const enum_id = ((((*this).get_type(expr_type_id)))->get<types::Type::Enum>()).value;
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
bool exists = false;
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
(exists = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();DeprecatedString const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((var_name == name));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();DeprecatedString const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((var_name == name));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();DeprecatedString const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((var_name == name));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();DeprecatedString const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((var_name == name));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
}));
if (exists){
(operator_is =  types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::IsEnumVariant(variant,(TRY((DynamicArray<types::CheckedEnumVariantBinding>::create_with({})))),expr_type_id) } );
break;
}
}

}
}

if (((!(exists)) && ((type_id).equals(types::unknown_type_id())))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant {} does not exist on {}"sv)),name,TRY((((*this).type_name(expr_type_id,false))))))),span))));
}
}
else if (((name == TRY(DeprecatedString::from_utf8("Some"sv))) || (name == TRY(DeprecatedString::from_utf8("None"sv))))){
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
NonnullRefPtr<typename types::Type> const checked_expr_type = ((*this).get_type(((checked_expr)->type())));
if ((!(((checked_expr_type)->index() == 19 /* GenericInstance */)))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("The left-hand side of an `is {}` statement must have a {} variant"sv)),name,name))),((checked_expr)->span())))));
}
(operator_is = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::CheckedUnaryOperator,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (name);
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("Some"sv))) {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::IsSome() } );
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("None"sv))) {
return JaktInternal::ExplicitValue( types::CheckedUnaryOperator { typename types::CheckedUnaryOperator::IsNone() } );
}
else {
{
utility::panic(TRY(DeprecatedString::from_utf8("unreachable"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (((type_id).equals(types::unknown_type_id()))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unknown type or invalid type name: {}"sv)),name))),span))));
}
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("The right-hand side of an `is` operator must be a type name or enum variant"sv)),span))));
}

__jakt_var_520 = operator_is; goto __jakt_label_456;

}
__jakt_label_456:; __jakt_var_520.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::UnaryOperator::IsEnumVariant>();NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& bindings = __jakt_match_value.bindings;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_is_enum_variant(checked_expr,inner,bindings,scope_id)))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_516 = TRY((((*this).typecheck_unary_operation(checked_expr,checked_op,span,scope_id,safety_mode)))); goto __jakt_label_452;

}
__jakt_label_452:; __jakt_var_516.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::BinaryOp>();NonnullRefPtr<typename parser::ParsedExpression> const& lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename parser::ParsedExpression> const& rhs = __jakt_match_value.rhs;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_521; {
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> original_checked_lhs = JaktInternal::OptionalNone();
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> original_checked_rhs = JaktInternal::OptionalNone();
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> checked_lhs = JaktInternal::OptionalNone();
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> checked_rhs = JaktInternal::OptionalNone();
if ((((lhs)->index() == 1 /* NumericConstant */) || ((lhs)->index() == 1 /* NumericConstant */))){
(original_checked_rhs = TRY((((*this).typecheck_expression(rhs,scope_id,safety_mode,JaktInternal::OptionalNone())))));
(checked_rhs = TRY((((*this).dereference_if_needed((original_checked_rhs.value()),span)))));
types::TypeId const hint = (((checked_rhs.value()))->type());
(original_checked_lhs = TRY((((*this).typecheck_expression(lhs,scope_id,safety_mode,hint)))));
(checked_lhs = TRY((((*this).dereference_if_needed((original_checked_lhs.value()),span)))));
}
else {
(original_checked_lhs = TRY((((*this).typecheck_expression(lhs,scope_id,safety_mode,JaktInternal::OptionalNone())))));
(checked_lhs = TRY((((*this).dereference_if_needed((original_checked_lhs.value()),span)))));
types::TypeId const hint = (((checked_lhs.value()))->type());
(original_checked_rhs = TRY((((*this).typecheck_expression(rhs,scope_id,safety_mode,hint)))));
(checked_rhs = TRY((((*this).dereference_if_needed((original_checked_rhs.value()),span)))));
}

if ((TRY((((*this).type_contains_reference((((original_checked_lhs.value()))->type()))))) && ((rhs)->index() == 11 /* UnaryOp */))){
parser::UnaryOperator const op = ((rhs)->get<parser::ParsedExpression::UnaryOp>()).op;
if ((((op).index() == 7 /* Reference */) || ((op).index() == 8 /* MutableReference */))){
TRY((((*this).error_with_hint(TRY(DeprecatedString::from_utf8("Attempt to rebind a reference will result in write-through"sv)),span,TRY(DeprecatedString::from_utf8("This reference will be immediately dereferenced and then assigned"sv)),((rhs)->span())))));
}
}
types::TypeId const output_type = TRY((((*this).typecheck_binary_operation((checked_lhs.value()),op,(checked_rhs.value()),scope_id,span))));
__jakt_var_521 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::BinaryOp>((checked_lhs.value()),op,(checked_rhs.value()),span,output_type))); goto __jakt_label_457;

}
__jakt_label_457:; __jakt_var_521.release_value(); }));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedExpression::OptionalNone>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_522; {
JaktInternal::Optional<types::TypeId> type_hint_unwrapped = type_hint;
if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
types::StructId const id = ((((*this).get_type((type_hint.value()))))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type((type_hint.value()))))->get<types::Type::GenericInstance>()).args;
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
if (((id).equals(optional_struct_id))){
(type_hint_unwrapped = ((args)[static_cast<i64>(0LL)]));
}
}
__jakt_var_522 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::OptionalNone>(span,type_hint_unwrapped.value_or_lazy_evaluated([&] { return types::unknown_type_id(); })))); goto __jakt_label_458;

}
__jakt_label_458:; __jakt_var_522.release_value(); }));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::OptionalSome>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_523; {
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::TypeId const type_id = ((checked_expr)->type());
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
NonnullRefPtr<typename types::Type> const optional_type = TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({type_id})))))));
types::TypeId const optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
__jakt_var_523 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::OptionalSome>(checked_expr,span,optional_type_id))); goto __jakt_label_459;

}
__jakt_label_459:; __jakt_var_523.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Var>();DeprecatedString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>> const var = TRY((((*this).find_var_in_scope(scope_id,name))));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>,ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto __jakt_enum_value = (((var).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Var>((var.value()),span))));
}
else {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_524; {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Variable '{}' not found"sv)),name))),span))));
__jakt_var_524 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Var>(TRY((types::CheckedVariable::__jakt_create(name,((type_hint).value_or(types::unknown_type_id())),false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))),span))); goto __jakt_label_460;

}
__jakt_label_460:; __jakt_var_524.release_value(); }));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::ForcedUnwrap>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_525; {
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(((checked_expr)->type())));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
types::StructId const weakptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
types::TypeId const type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_526; {
types::TypeId inner_type_id = types::unknown_type_id();
if ((((id).equals(optional_struct_id)) || ((id).equals(weakptr_struct_id)))){
(inner_type_id = ((args)[static_cast<i64>(0LL)]));
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Forced unwrap only works on Optional"sv)),span))));
}

__jakt_var_526 = inner_type_id; goto __jakt_label_462;

}
__jakt_label_462:; __jakt_var_526.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_527; {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Forced unwrap only works on Optional"sv)),span))));
__jakt_var_527 = types::unknown_type_id(); goto __jakt_label_463;

}
__jakt_label_463:; __jakt_var_527.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_525 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::ForcedUnwrap>(checked_expr,span,type_id))); goto __jakt_label_461;

}
__jakt_label_461:; __jakt_var_525.release_value(); }));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::JaktArray>();JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& values = __jakt_match_value.values;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& fill_size = __jakt_match_value.fill_size;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_array(scope_id,values,fill_size,span,safety_mode,type_hint)))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::JaktTuple>();JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& values = __jakt_match_value.values;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_528; {
types::TypeId const VOID_TYPE_ID = types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> checked_values = (TRY((DynamicArray<NonnullRefPtr<typename types::CheckedExpression>>::create_with({}))));
JaktInternal::DynamicArray<types::TypeId> checked_types = (TRY((DynamicArray<types::TypeId>::create_with({}))));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedExpression>> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedExpression> value = (_magic_value.value());
{
NonnullRefPtr<typename types::CheckedExpression> const checked_value = TRY((((*this).typecheck_expression(value,scope_id,safety_mode,JaktInternal::OptionalNone()))));
types::TypeId const type_id = ((checked_value)->type());
if (((type_id).equals(VOID_TYPE_ID))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Cannot create a tuple that contains a value of type void"sv)),((value)->span())))));
}
TRY((((checked_types).push(type_id))));
TRY((((checked_values).push(checked_value))));
}

}
}

if ((((type_hint).has_value()) && ((((*this).get_type((type_hint.value()))))->index() == 19 /* GenericInstance */))){
types::StructId const id = ((((*this).get_type((type_hint.value()))))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type((type_hint.value()))))->get<types::Type::GenericInstance>()).args;
if ((((checked_types).size()) == ((args).size()))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::TypeId value_type = ((checked_types)[i]);
JaktInternal::Optional<types::TypeId> const unified = TRY((((*this).unify(((args)[i]),span,value_type,span))));
if (((unified).has_value())){
bool type_optional = false;
if (((((*this).get_type((unified.value()))))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type((unified.value()))))->get<types::Type::GenericInstance>()).id;
if (((id).equals(optional_struct_id))){
(type_optional = true);
}
}
bool value_optional = false;
if (((((*this).get_type(value_type)))->index() == 19 /* GenericInstance */)){
types::StructId const id = ((((*this).get_type(value_type)))->get<types::Type::GenericInstance>()).id;
if (((id).equals(optional_struct_id))){
(value_optional = true);
}
}
(((checked_types)[i]) = (unified.value()));
if ((type_optional && ((!(value_optional)) && (!(((((checked_values)[i]))->index() == 26 /* OptionalSome */)))))){
if ((((((checked_values)[i]))->index() == 25 /* OptionalNone */) && ((((*this).get_type((unified.value()))))->index() == 19 /* GenericInstance */))){
types::StructId const id = ((((*this).get_type((unified.value()))))->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<types::TypeId> const args = ((((*this).get_type((unified.value()))))->get<types::Type::GenericInstance>()).args;
(value_type = ((args)[static_cast<i64>(0LL)]));
}
NonnullRefPtr<typename types::Type> const optional_type = TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({value_type})))))));
types::TypeId const optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
(((checked_values)[i]) = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::OptionalSome>(((checked_values)[i]),span,optional_type_id))));
}
}
}

}
}

}
}
types::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Tuple"sv))))));
types::TypeId const type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(tuple_struct_id,checked_types)))))));
if (((type_hint).has_value())){
TRY((((*this).check_types_for_compat((type_hint.value()),type_id,((((*this).generic_inferences))),span))));
}
__jakt_var_528 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::JaktTuple>(checked_values,span,type_id))); goto __jakt_label_464;

}
__jakt_label_464:; __jakt_var_528.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedExpression>();NonnullRefPtr<typename parser::ParsedExpression> const& base = __jakt_match_value.base;
NonnullRefPtr<typename parser::ParsedExpression> const& index = __jakt_match_value.index;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_529; {
NonnullRefPtr<typename types::CheckedExpression> const checked_base = TRY((((*this).typecheck_expression_and_dereference_if_needed(base,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
NonnullRefPtr<typename types::CheckedExpression> const checked_index = TRY((((*this).typecheck_expression_and_dereference_if_needed(index,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
__jakt_var_529 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((*this).get_type(((checked_base)->type())));
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_530; {
types::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Array"sv))))));
types::StructId const array_slice_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("ArraySlice"sv))))));
types::StructId const dictionary_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Dictionary"sv))))));
NonnullRefPtr<typename types::CheckedExpression> result = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Garbage>(span)));
if ((((id).equals(array_struct_id)) || ((id).equals(array_slice_struct_id)))){
if ((((*this).is_integer(((checked_index)->type()))) || ((checked_index)->index() == 9 /* Range */))){
types::TypeId const type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_index;
switch(__jakt_match_variant.index()) {
case 9: {
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_531; {
types::StructId const array_slice_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("ArraySlice"sv))))));
__jakt_var_531 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(array_slice_struct_id,args))))))); goto __jakt_label_467;

}
__jakt_label_467:; __jakt_var_531.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(result = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedExpression>(checked_base,checked_index,span,type_id))));
}
else {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Index must be an integer or a range"sv)),span))));
}

}
else if (((id).equals(dictionary_struct_id))){
(result = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedDictionary>(checked_base,checked_index,span,((args)[static_cast<i64>(1LL)])))));
}
__jakt_var_530 = result; goto __jakt_label_466;

}
__jakt_label_466:; __jakt_var_530.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_532; {
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Index used on value that cannot be indexed"sv)),span))));
__jakt_var_532 = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Garbage>(span))); goto __jakt_label_468;

}
__jakt_label_468:; __jakt_var_532.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_465;

}
__jakt_label_465:; __jakt_var_529.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::IndexedTuple>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_indexed_tuple(expr,index,scope_id,is_optional,safety_mode,span)))));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::ParsedExpression::Garbage>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Garbage>(span))));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::NamespacedVar>();DeprecatedString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<DeprecatedString> const& namespace_ = __jakt_match_value.namespace_;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_namespaced_var_or_simple_enum_constructor_call(name,namespace_,scope_id,safety_mode,type_hint,span)))));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Match>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<parser::ParsedMatchCase> const& cases = __jakt_match_value.cases;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_match(expr,cases,marker_span,scope_id,safety_mode,type_hint)))));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::EnumVariantArg>();NonnullRefPtr<typename parser::ParsedExpression> const& inner_expr = __jakt_match_value.expr;
parser::EnumVariantPatternArgument const& arg = __jakt_match_value.arg;
NonnullRefPtr<typename parser::ParsedType> const& enum_variant = __jakt_match_value.enum_variant;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::CheckedExpression>> __jakt_var_533; {
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(inner_expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::CheckedEnumVariantBinding checked_binding = types::CheckedEnumVariantBinding(TRY(DeprecatedString::from_utf8(""sv)),TRY(DeprecatedString::from_utf8(""sv)),types::unknown_type_id(),span);
JaktInternal::Optional<types::CheckedEnumVariant> checked_enum_variant = JaktInternal::OptionalNone();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *enum_variant;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::NamespacedName>();DeprecatedString const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
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
JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedEnumVariantBinding>> const checked_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),(TRY((DynamicArray<parser::EnumVariantPatternArgument>::create_with({arg})))),span))));
if (((checked_bindings).has_value())){
JaktInternal::DynamicArray<types::CheckedEnumVariantBinding> const bindings = (checked_bindings.value());
(checked_binding = ((bindings)[static_cast<i64>(0LL)]));
}
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant {} does not exist"sv)),variant_name))),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unknown type or invalid type name: {}"sv)),variant_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();DeprecatedString const& variant_name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
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
JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedEnumVariantBinding>> const checked_bindings = TRY((((*this).typecheck_enum_variant_bindings((variant.value()),(TRY((DynamicArray<parser::EnumVariantPatternArgument>::create_with({arg})))),span))));
if (((checked_bindings).has_value())){
JaktInternal::DynamicArray<types::CheckedEnumVariantBinding> const bindings = (checked_bindings.value());
(checked_binding = ((bindings)[static_cast<i64>(0LL)]));
}
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Enum variant {} does not exist"sv)),variant_name))),span))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unknown type or invalid type name: {}"sv)),variant_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename types::CheckedExpression> output = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Garbage>(span)));
if (((checked_enum_variant).has_value())){
(output = TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::EnumVariantArg>(checked_expr,checked_binding,(checked_enum_variant.value()),span))));
}
__jakt_var_533 = output; goto __jakt_label_469;

}
__jakt_label_469:; __jakt_var_533.release_value(); }));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::JaktDictionary>();JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> const& values = __jakt_match_value.values;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_dictionary(values,span,scope_id,safety_mode,type_hint)))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Set>();JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& values = __jakt_match_value.values;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_set(values,span,scope_id,safety_mode,type_hint)))));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Function>();JaktInternal::DynamicArray<parser::ParsedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<parser::ParsedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
bool const& is_fat_arrow = __jakt_match_value.is_fat_arrow;
NonnullRefPtr<typename parser::ParsedType> const& return_type = __jakt_match_value.return_type;
parser::ParsedBlock const& block = __jakt_match_value.block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_lambda(captures,params,can_throw,is_fat_arrow,return_type,block,span,scope_id,safety_mode)))));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::Try>();NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<parser::ParsedBlock> const& catch_block = __jakt_match_value.catch_block;
JaktInternal::Optional<DeprecatedString> const& catch_name = __jakt_match_value.catch_name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_try(expr,catch_block,catch_name,scope_id,safety_mode,span,type_hint)))));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedExpression::TryBlock>();NonnullRefPtr<typename parser::ParsedStatement> const& stmt = __jakt_match_value.stmt;
parser::ParsedBlock const& catch_block = __jakt_match_value.catch_block;
DeprecatedString const& error_name = __jakt_match_value.error_name;
utility::Span const& error_span = __jakt_match_value.error_span;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).typecheck_try_block(stmt,error_name,error_span,catch_block,scope_id,safety_mode,span)))));
};/*case end*/
case 13: {
{
TRY((((((*this).compiler))->panic(TRY(DeprecatedString::from_utf8("idk how to handle this thing"sv))))));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_indexed_struct(NonnullRefPtr<typename parser::ParsedExpression> const expr,DeprecatedString const field_name,types::ScopeId const scope_id,bool const is_optional,types::SafetyMode const safety_mode,utility::Span const span) {
{
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
types::TypeId const checked_expr_type_id = ((checked_expr)->type());
NonnullRefPtr<typename types::Type> const checked_expr_type = ((*this).get_type(checked_expr_type_id));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_expr_type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
{
types::TypeId type_id = checked_expr_type_id;
if (is_optional){
if ((!(((id).equals(optional_struct_id))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Optional chaining is only allowed on optional types"sv)),span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,JaktInternal::OptionalNone(),span,is_optional,types::unknown_type_id())));
}
(type_id = ((args)[static_cast<i64>(0LL)]));
}
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const checkpoint = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_534([&] {
((((*this).generic_inferences)).restore(checkpoint));
});
TRY((((*this).map_generic_arguments(type_id,args))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& struct_id = __jakt_match_value.id;
{
types::CheckedStruct const structure = ((*this).get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((*this).get_variable(((field).variable_id)));
if ((((member)->name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member)->type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((structure).scope_id),member,span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,((field).variable_id),span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field_name))),span))));
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
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((*this).get_variable(((field).variable_id)));
if ((((member)->name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member)->type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((structure).scope_id),member,span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,((field).variable_id),span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field_name))),span))));
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
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((*this).get_variable(((field).variable_id)));
if ((((member)->name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member)->type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((enum_).scope_id),member,span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedCommonEnumMember>(checked_expr,field_name,span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown common member of enum: {}.{}"sv)),((enum_).name),field_name))),span))));
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
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((*this).get_variable(((field).variable_id)));
if ((((member)->name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member)->type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((enum_).scope_id),member,span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedCommonEnumMember>(checked_expr,field_name,span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown common member of enum: {}.{}"sv)),((enum_).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
return (TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Member field access on value of non-struct type ‘{}’"sv)),TRY((((*this).type_name(checked_expr_type_id,false))))))),span))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
if (is_optional){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Optional chaining is not allowed on non-optional types"sv)),span))));
}
types::CheckedStruct const structure = ((*this).get_struct(struct_id));
JaktInternal::Optional<types::FieldRecord> const field_record = TRY((((*this).lookup_struct_field(struct_id,field_name))));
if (((field_record).has_value())){
NonnullRefPtr<types::CheckedVariable> const member = ((*this).get_variable((((field_record.value())).field_id)));
types::TypeId const resolved_type_id = TRY((((*this).resolve_type_var(((member)->type_id),scope_id))));
TRY((((*this).check_member_access(scope_id,((((*this).get_struct((((field_record.value())).struct_id)))).scope_id),member,span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,(((field_record.value())).field_id),span,is_optional,resolved_type_id)));
}
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<types::TypeId> const& args = __jakt_match_value.args;
{
if (is_optional){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Optional chaining is not allowed on non-optional types"sv)),span))));
}
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const checkpoint = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_535([&] {
((((*this).generic_inferences)).restore(checkpoint));
});
TRY((((*this).map_generic_arguments(checked_expr_type_id,args))));
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((*this).get_variable(((field).variable_id)));
if ((((member)->name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member)->type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((enum_).scope_id),member,span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedCommonEnumMember>(checked_expr,field_name,span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown common member of enum: {}.{}"sv)),((enum_).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<types::TypeId> const args = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
if (is_optional){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("Optional chaining is not allowed on non-optional types"sv)),span))));
}
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const checkpoint = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_536([&] {
((((*this).generic_inferences)).restore(checkpoint));
});
TRY((((*this).map_generic_arguments(checked_expr_type_id,args))));
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const member = ((*this).get_variable(((field).variable_id)));
if ((((member)->name) == field_name)){
types::TypeId resolved_type_id = TRY((((*this).resolve_type_var(((member)->type_id),scope_id))));
if (is_optional){
(resolved_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({resolved_type_id}))))))))))));
}
TRY((((*this).check_member_access(scope_id,((enum_).scope_id),member,span))));
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedCommonEnumMember>(checked_expr,field_name,span,is_optional,resolved_type_id)));
}
}

}
}

TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("unknown common member of enum: {}.{}"sv)),((enum_).name),field_name))),span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
return (TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Member field access on value of non-struct type ‘{}’"sv)),TRY((((*this).type_name(checked_expr_type_id,false))))))),span))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::IndexedStruct>(checked_expr,field_name,JaktInternal::OptionalNone(),span,is_optional,types::unknown_type_id())));
}
}

ErrorOr<void> typechecker::Typechecker::typecheck_namespace_imports(parser::ParsedNamespace const parsed_namespace,types::ScopeId const scope_id) {
{
{
JaktInternal::ArrayIterator<parser::ParsedModuleImport> _magic = ((((parsed_namespace).module_imports)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedModuleImport> const _magic_value = ((_magic).next());
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
JaktInternal::Optional<parser::ParsedExternImport> const _magic_value = ((_magic).next());
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

ErrorOr<jakt__path::Path> typechecker::Typechecker::get_root_path() const {
{
JaktInternal::Optional<types::LoadedModule> const root_module = ((((*this).program))->get_loaded_module(((*this).root_module_name)));
if (((root_module).has_value())){
utility::FileId const file_id = (((root_module.value())).file_id);
return (TRY((((((*this).compiler))->get_file_path(file_id)))).value());
}
return TRY((jakt__path::Path::from_string(TRY(DeprecatedString::from_utf8("."sv)))));
}
}

ErrorOr<JaktInternal::Optional<typechecker::TraitImplementationDescriptor>> typechecker::Typechecker::find_singular_trait_implementation(types::TypeId const type_id,DeprecatedString const trait_name,types::ScopeId const scope_id,utility::Span const span) {
{
JaktInternal::Optional<types::TraitId> const trait_id = TRY((((*this).find_trait_in_scope(scope_id,trait_name))));
if ((!(((trait_id).has_value())))){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<JaktInternal::DynamicArray<types::TypeId>> const trait_impls = TRY((((*this).find_all_implementations_of_trait(type_id,(trait_id.value())))));
if (((trait_impls).is_empty())){
return JaktInternal::OptionalNone();
}
if ((((trait_impls).size()) > static_cast<size_t>(1ULL))){
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("type ‘{}’ implements trait ‘{}’ more than once, but a singular implementation is allowed"sv)),TRY((((*this).type_name(type_id,false)))),trait_name))),span))));
}
return typechecker::TraitImplementationDescriptor((trait_id.value()),trait_name,((trait_impls)[static_cast<i64>(0LL)]));
}
}

ErrorOr<NonnullRefPtr<typename types::CheckedExpression>> typechecker::Typechecker::typecheck_try(NonnullRefPtr<typename parser::ParsedExpression> const expr,JaktInternal::Optional<parser::ParsedBlock> const catch_block,JaktInternal::Optional<DeprecatedString> const catch_name,types::ScopeId const scope_id,types::SafetyMode const safety_mode,utility::Span const span,JaktInternal::Optional<types::TypeId> const type_hint) {
{
types::ScopeId const try_scope_id = TRY((((*this).create_scope(scope_id,true,TRY(DeprecatedString::from_utf8("try"sv)),true))));
NonnullRefPtr<typename types::CheckedExpression> const checked_expr = TRY((((*this).typecheck_expression(expr,try_scope_id,safety_mode,type_hint))));
types::StructId const error_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Error"sv))))));
NonnullRefPtr<types::Module> module = ((*this).current_module());
JaktInternal::Optional<types::CheckedBlock> checked_catch_block = JaktInternal::OptionalNone();
types::TypeId const expression_type_id = ((checked_expr)->type());
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
NonnullRefPtr<typename types::Type> const optional_type = TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({expression_type_id})))))));
types::TypeId const optional_type_id = TRY((((*this).find_or_add_type_id(optional_type))));
types::TypeId type_id = optional_type_id;
if (((catch_block).has_value())){
NonnullRefPtr<types::Scope> const parent_scope = TRY((((*this).get_scope(scope_id))));
types::ScopeId const catch_scope_id = TRY((((*this).create_scope(scope_id,((parent_scope)->can_throw),TRY(DeprecatedString::from_utf8("catch"sv)),true))));
if (((catch_name).has_value())){
types::StructId const error_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Error"sv))))));
NonnullRefPtr<types::CheckedVariable> const error_decl = TRY((types::CheckedVariable::__jakt_create((catch_name.value()),((((*this).get_struct(error_struct_id))).type_id),false,span,JaktInternal::OptionalNone(), types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::VarId const error_id = TRY((((module)->add_variable(error_decl))));
TRY((((*this).add_var_to_scope(catch_scope_id,(catch_name.value()),error_id,span))));
}
types::CheckedBlock const block = TRY((((*this).typecheck_block((catch_block.value()),catch_scope_id,safety_mode,JaktInternal::OptionalNone()))));
if ((((((block).control_flow)).always_transfers_control()) || ((((block).yielded_type)).has_value()))){
if ((!(((((block).yielded_type).value_or_lazy_evaluated([&] { return expression_type_id; })).equals(expression_type_id))))){
TRY((((*this).error_with_hint(TRY((__jakt_format((StringView::from_string_literal("Expected a value of type ‘{}’, but got ‘{}’"sv)),TRY((((*this).type_name(expression_type_id,false)))),TRY((((*this).type_name((((block).yielded_type).value()),false))))))),span,TRY((__jakt_format((StringView::from_string_literal("Expression 'catch' block must either yield the same type as the expression it is catching, or yield nothing"sv))))),span))));
}
else {
(type_id = ((block).yielded_type).value_or_lazy_evaluated([&] { return expression_type_id; }));
}

}
else {
if ((!(((expression_type_id).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } )))))){
TRY((((*this).error(TRY(DeprecatedString::from_utf8("In a try expression that returns a value, 'catch' block must either yield a value or transfer control flow"sv)),span))));
}
}

(checked_catch_block = block);
}
return TRY((types::CheckedExpression::template __jakt_create<typename types::CheckedExpression::Try>(checked_expr,checked_catch_block,catch_name,span,type_id,expression_type_id)));
}
}

ErrorOr<types::TypeId> typechecker::Typechecker::typecheck_typename(NonnullRefPtr<typename parser::ParsedType> const parsed_type,types::ScopeId const scope_id,JaktInternal::Optional<DeprecatedString> const name) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<types::TypeId>>{
auto&& __jakt_match_variant = *parsed_type;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Reference>();NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_537; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
__jakt_var_537 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Reference>(inner_type_id))))))); goto __jakt_label_470;

}
__jakt_label_470:; __jakt_var_537.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::MutableReference>();NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_538; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
__jakt_var_538 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::MutableReference>(inner_type_id))))))); goto __jakt_label_471;

}
__jakt_label_471:; __jakt_var_538.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::NamespacedName>();DeprecatedString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<DeprecatedString> const& namespaces = __jakt_match_value.namespaces;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& params = __jakt_match_value.params;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_539; {
types::ScopeId current_namespace_scope_id = scope_id;
{
JaktInternal::ArrayIterator<DeprecatedString> _magic = ((namespaces).iterator());
for (;;){
JaktInternal::Optional<DeprecatedString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
DeprecatedString ns = (_magic_value.value());
{
JaktInternal::Optional<JaktInternal::Tuple<types::ScopeId,bool>> const result = TRY((((*this).find_namespace_in_scope(current_namespace_scope_id,ns,false))));
if (((result).has_value())){
(current_namespace_scope_id = (((result.value())).template get<0>()));
}
else {
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unknown namespace: '{}'"sv)),ns))),span))));
return types::unknown_type_id();
}

}

}
}

JaktInternal::DynamicArray<types::TypeId> generic_args = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedType>> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedType> param = (_magic_value.value());
{
types::TypeId const checked_arg = TRY((((*this).typecheck_typename(param,scope_id,name))));
TRY((((generic_args).push(checked_arg))));
}

}
}

JaktInternal::Optional<types::TypeId> type_id = JaktInternal::OptionalNone();
if (((generic_args).is_empty())){
NonnullRefPtr<typename parser::ParsedType> const synthetic_typename = TRY((parser::ParsedType::template __jakt_create<typename parser::ParsedType::Name>(name,span)));
(type_id = TRY((((*this).typecheck_typename(synthetic_typename,current_namespace_scope_id,name)))));
}
else {
(type_id = TRY((((*this).typecheck_generic_resolved_type(name,generic_args,current_namespace_scope_id,span)))));
}

__jakt_var_539 = (type_id.value()); goto __jakt_label_472;

}
__jakt_label_472:; __jakt_var_539.release_value(); }));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Name>();DeprecatedString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_540; {
JaktInternal::Optional<JaktInternal::Tuple<types::TypeId,types::ScopeId>> const maybe_type_and_scope = TRY((((*this).find_type_scope(scope_id,name))));
if (((maybe_type_and_scope).has_value())){
if ((!((((((maybe_type_and_scope.value())).template get<1>())).equals(((*this).prelude_scope_id())))))){
return (((maybe_type_and_scope.value())).template get<0>());
}
}
__jakt_var_540 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId,ErrorOr<types::TypeId>>{
auto __jakt_enum_value = (name);
if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("i8"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("i16"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("i32"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("i64"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("u8"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("u16"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("u32"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("u64"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("f32"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::F32() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("f64"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::F64() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("c_char"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("c_int"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("usize"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("bool"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("void"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } ));
}
else if (__jakt_enum_value == TRY(DeprecatedString::from_utf8("never"sv))) {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Never() } ));
}
else {
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_541; {
if (((maybe_type_and_scope).has_value())){
return (((maybe_type_and_scope.value())).template get<0>());
}
TRY((((*this).error(TRY((__jakt_format((StringView::from_string_literal("Unknown type ‘{}’"sv)),name))),span))));
__jakt_var_541 = types::unknown_type_id(); goto __jakt_label_474;

}
__jakt_label_474:; __jakt_var_541.release_value(); }));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_473;

}
__jakt_label_473:; __jakt_var_540.release_value(); }));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_542; {
__jakt_var_542 = types::unknown_type_id(); goto __jakt_label_475;

}
__jakt_label_475:; __jakt_var_542.release_value(); }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::JaktTuple>();JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& types = __jakt_match_value.types;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_543; {
JaktInternal::DynamicArray<types::TypeId> checked_types = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedType>> _magic = ((types).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedType> parsed_type = (_magic_value.value());
{
TRY((((checked_types).push(TRY((((*this).typecheck_typename(parsed_type,scope_id,name))))))));
}

}
}

types::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Tuple"sv))))));
__jakt_var_543 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(tuple_struct_id,checked_types))))))); goto __jakt_label_476;

}
__jakt_label_476:; __jakt_var_543.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::JaktArray>();NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_544; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
types::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Array"sv))))));
__jakt_var_544 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(array_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({inner_type_id}))))))))))); goto __jakt_label_477;

}
__jakt_label_477:; __jakt_var_544.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Dictionary>();NonnullRefPtr<typename parser::ParsedType> const& key = __jakt_match_value.key;
NonnullRefPtr<typename parser::ParsedType> const& value = __jakt_match_value.value;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_545; {
types::TypeId const key_type_id = TRY((((*this).typecheck_typename(key,scope_id,name))));
types::TypeId const value_type_id = TRY((((*this).typecheck_typename(value,scope_id,name))));
types::StructId const dict_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Dictionary"sv))))));
__jakt_var_545 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(dict_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({key_type_id, value_type_id}))))))))))); goto __jakt_label_478;

}
__jakt_label_478:; __jakt_var_545.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Set>();NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_546; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
types::StructId const set_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Set"sv))))));
__jakt_var_546 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(set_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({inner_type_id}))))))))))); goto __jakt_label_479;

}
__jakt_label_479:; __jakt_var_546.release_value(); }));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Optional>();NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_547; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
types::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
__jakt_var_547 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(optional_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({inner_type_id}))))))))))); goto __jakt_label_480;

}
__jakt_label_480:; __jakt_var_547.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::WeakPtr>();NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_548; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
types::StructId const weakptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
__jakt_var_548 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(weakptr_struct_id,(TRY((DynamicArray<types::TypeId>::create_with({inner_type_id}))))))))))); goto __jakt_label_481;

}
__jakt_label_481:; __jakt_var_548.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::RawPtr>();NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_549; {
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner,scope_id,name))));
__jakt_var_549 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::RawPtr>(inner_type_id))))))); goto __jakt_label_482;

}
__jakt_label_482:; __jakt_var_549.release_value(); }));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::GenericType>();DeprecatedString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& generic_parameters = __jakt_match_value.generic_parameters;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_550; {
JaktInternal::DynamicArray<types::TypeId> checked_inner_types = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedType>> _magic = ((generic_parameters).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedType> inner_type = (_magic_value.value());
{
types::TypeId const inner_type_id = TRY((((*this).typecheck_typename(inner_type,scope_id,name))));
TRY((((checked_inner_types).push(inner_type_id))));
}

}
}

__jakt_var_550 = TRY((((*this).typecheck_generic_resolved_type(name,checked_inner_types,scope_id,span)))); goto __jakt_label_483;

}
__jakt_label_483:; __jakt_var_550.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::ParsedType::Function>();JaktInternal::DynamicArray<parser::ParsedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
NonnullRefPtr<typename parser::ParsedType> const& return_type = __jakt_match_value.return_type;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<types::TypeId> __jakt_var_551; {
DeprecatedString const function_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<types::TypeId>>{
auto __jakt_enum_value = (((name).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((name.value()));
}
else {
return JaktInternal::ExplicitValue(TRY((({ Optional<DeprecatedString> __jakt_var_552;
auto __jakt_var_553 = [&]() -> ErrorOr<DeprecatedString> { return TRY((__jakt_format((StringView::from_string_literal("lambda{}"sv)),((((*this).lambda_count)++))))); }();
if (!__jakt_var_553.is_error()) __jakt_var_552 = __jakt_var_553.release_value();
__jakt_var_552; }).try_value_or_lazy_evaluated([&]() -> ErrorOr<DeprecatedString> { return TRY(DeprecatedString::from_utf8(""sv)); }))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<types::CheckedParameter> checked_params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
bool first = true;
JaktInternal::Dictionary<DeprecatedString,DeprecatedString> const old_generic_inferences = TRY((((((*this).generic_inferences)).perform_checkpoint(false))));
ScopeGuard __jakt_var_554([&] {
{
((((*this).generic_inferences)).restore(old_generic_inferences));
}

});
{
JaktInternal::ArrayIterator<parser::ParsedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedParameter> const _magic_value = ((_magic).next());
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

NonnullRefPtr<types::CheckedFunction> const checked_function = TRY((types::CheckedFunction::__jakt_create(function_name,span, types::CheckedVisibility { typename types::CheckedVisibility::Public() } ,TRY((((*this).typecheck_typename(return_type,scope_id,JaktInternal::OptionalNone())))),((return_type)->span()),checked_params,TRY((types::FunctionGenerics::__jakt_create(scope_id,checked_params,(TRY((DynamicArray<types::FunctionGenericParameter>::create_with({})))),(TRY((DynamicArray<JaktInternal::DynamicArray<types::TypeId>>::create_with({}))))))),types::CheckedBlock((TRY((DynamicArray<NonnullRefPtr<typename types::CheckedStatement>>::create_with({})))),scope_id, types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ,JaktInternal::OptionalNone(),false),can_throw, parser::FunctionType { typename parser::FunctionType::Expression() } , parser::FunctionLinkage { typename parser::FunctionLinkage::Internal() } ,scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<types::Module> module = ((*this).current_module());
types::FunctionId const function_id = TRY((((module)->add_function(checked_function))));
JaktInternal::DynamicArray<types::TypeId> param_type_ids = (TRY((DynamicArray<types::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((param_type_ids).push(((((param).variable))->type_id)))));
}

}
}

__jakt_var_551 = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Function>(param_type_ids,can_throw,((checked_function)->return_type_id),function_id))))))); goto __jakt_label_484;

}
__jakt_label_484:; __jakt_var_551.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

types::TypeId typechecker::Typechecker::infer_function_return_type(types::CheckedBlock const block) const {
{
if (((((block).statements)).is_empty())){
return types::void_type_id();
}
if ((((((((block).statements)).last()).value()))->index() == 8 /* Return */)){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const val = (((((((block).statements)).last()).value()))->get<types::CheckedStatement::Return>()).val;
if (((val).has_value())){
return (((val.value()))->type());
}
}
return types::void_type_id();
}
}

ErrorOr<bool> typechecker::Typechecker::scope_lifetime_subsumes(JaktInternal::Optional<types::ScopeId> const larger,JaktInternal::Optional<types::ScopeId> const smaller) const {
{
if ((!(((larger).has_value())))){
return false;
}
if ((!(((smaller).has_value())))){
return true;
}
types::ScopeId const larger_id = (larger.value());
types::ScopeId const smaller_id = (smaller.value());
if (((larger_id).equals(smaller_id))){
return false;
}
JaktInternal::Optional<types::ScopeId> scope_id = ((TRY((((((*this).program))->get_scope(smaller_id)))))->parent);
while (((scope_id).has_value())){
if ((((scope_id.value())).equals(larger_id))){
return true;
}
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope((scope_id.value())))));
{
JaktInternal::ArrayIterator<types::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<types::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ScopeId child_scope_id = (_magic_value.value());
{
if (((child_scope_id).equals(larger_id))){
return true;
}
}

}
}

(scope_id = ((scope)->parent));
}
return false;
}
}

ErrorOr<DeprecatedString> typechecker::NumericOrStringValue::debug_description() const {
auto builder = TRY(DeprecatedStringBuilder::create());
switch (this->index()) {case 0 /* StringValue */: {
TRY(builder.append("NumericOrStringValue::StringValue"sv));
[[maybe_unused]] auto const& that = this->template get<NumericOrStringValue::StringValue>();
TRY(builder.appendff("(\"{}\")", that.value));
break;}
case 1 /* SignedNumericValue */: {
TRY(builder.append("NumericOrStringValue::SignedNumericValue"sv));
[[maybe_unused]] auto const& that = this->template get<NumericOrStringValue::SignedNumericValue>();
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* UnsignedNumericValue */: {
TRY(builder.append("NumericOrStringValue::UnsignedNumericValue"sv));
[[maybe_unused]] auto const& that = this->template get<NumericOrStringValue::UnsignedNumericValue>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> typechecker::FunctionMatchResult::debug_description() const {
auto builder = TRY(DeprecatedStringBuilder::create());
switch (this->index()) {case 0 /* MatchSuccess */: {
TRY(builder.append("FunctionMatchResult::MatchSuccess"sv));
[[maybe_unused]] auto const& that = this->template get<FunctionMatchResult::MatchSuccess>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("args: {}, ", that.args));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("maybe_this_type_id: {}, ", that.maybe_this_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("used_generic_inferences: {}, ", that.used_generic_inferences));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("specificity: {}", that.specificity));
}
TRY(builder.append(")"sv));
break;}
case 1 /* MatchError */: {
TRY(builder.append("FunctionMatchResult::MatchError"sv));
[[maybe_unused]] auto const& that = this->template get<FunctionMatchResult::MatchError>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("errors: {}", that.errors));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
}
} // namespace Jakt
