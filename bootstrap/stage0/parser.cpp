#include "parser.h"
namespace Jakt {
namespace parser {
f32 f64_to_f32(f64 const number) {
{
f32 f32_value = static_cast<i64>(0LL);
{
f32_value = (f32)number;
}

return f32_value;
}
}

utility::Span merge_spans(utility::Span const start,utility::Span const end) {
{
if ((((((((end).file_id)).id)) == (static_cast<size_t>(0ULL))) && (((((end).start)) == (static_cast<size_t>(0ULL))) && ((((end).end)) == (static_cast<size_t>(0ULL)))))){
return start;
}
if (((((((start).file_id)).id)) != (((((end).file_id)).id)))){
utility::panic(__jakt_format((StringView::from_string_literal("cannot merge spans from two different files ({} and {})"sv)),start,end));
}
return utility::Span(((start).file_id),((start).start),((end).end));
}
}

ByteString parser::ParsedFunctionParameters::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedFunctionParameters("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parameters: {}, ", parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("has_varargs: {}", has_varargs);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedFunctionParameters::ParsedFunctionParameters(JaktInternal::DynamicArray<parser::ParsedParameter> a_parameters, bool a_has_varargs): parameters(move(a_parameters)), has_varargs(move(a_has_varargs)){}

ByteString parser::ParsedModuleImport::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedModuleImport("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module_name: {}, ", module_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("alias_name: {}, ", alias_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("import_list: {}, ", import_list);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("relative_path: {}, ", relative_path);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parent_path_count: {}", parent_path_count);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedModuleImport::is_equivalent_to(parser::ParsedModuleImport const other) const {
{
return (((((*this).module_name)).equals(((other).module_name))) && (((*this).has_same_alias_than(other)) && ((*this).has_same_import_semantics(other))));
}
}

bool parser::ParsedModuleImport::has_same_import_semantics(parser::ParsedModuleImport const other) const {
{
return ((((((*this).import_list)).is_empty())) == (((((other).import_list)).is_empty())));
}
}

bool parser::ParsedModuleImport::has_same_alias_than(parser::ParsedModuleImport const other) const {
{
if (((((*this).alias_name)).has_value())){
return (((((other).alias_name)).has_value()) && (((((other).alias_name).value())).equals((((*this).alias_name).value()))));
}
else {
return (!(((((other).alias_name)).has_value())));
}

}
}

void parser::ParsedModuleImport::merge_import_list(parser::ImportList const list) {
{
JaktInternal::Set<ByteString> name_set = Set<ByteString>::create_with_values({});
bool everything = false;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, void>{
auto&& __jakt_match_variant = ((*this).import_list);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* List */: {
auto&& __jakt_match_value = __jakt_match_variant.as.List;JaktInternal::DynamicArray<parser::ImportName> const& names = __jakt_match_value.value;
{
{
JaktInternal::ArrayIterator<parser::ImportName> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<parser::ImportName> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ImportName name = (_magic_value.value());
{
((name_set).add(((name).literal_name())));
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* All */: {
{
(everything = true);
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
if ((!(everything))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, void>{
auto&& __jakt_match_variant = list;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* List */: {
auto&& __jakt_match_value = __jakt_match_variant.as.List;JaktInternal::DynamicArray<parser::ImportName> const& names = __jakt_match_value.value;
{
{
JaktInternal::ArrayIterator<parser::ImportName> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<parser::ImportName> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ImportName name = (_magic_value.value());
{
if ((!(((name_set).contains(((name).literal_name())))))){
((((*this).import_list)).add(name));
}
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* All */: {
{
(everything = true);
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
}
if (everything){
(((*this).import_list) = parser::ImportList::All());
}
}
}

parser::ParsedModuleImport::ParsedModuleImport(parser::ImportName a_module_name, JaktInternal::Optional<parser::ImportName> a_alias_name, parser::ImportList a_import_list, bool a_relative_path, size_t a_parent_path_count): module_name(move(a_module_name)), alias_name(move(a_alias_name)), import_list(move(a_import_list)), relative_path(move(a_relative_path)), parent_path_count(move(a_parent_path_count)){}

ByteString parser::ParsedExternImport::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedExternImport("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_c: {}, ", is_c);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("assigned_namespace: {}, ", assigned_namespace);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("before_include: {}, ", before_include);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("after_include: {}, ", after_include);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("should_auto_import: {}", should_auto_import);
}
builder.append(")"sv);return builder.to_string(); }
ByteString parser::ParsedExternImport::get_path() const {
{
return (((((*this).assigned_namespace)).import_path_if_extern).value());
}
}

ByteString parser::ParsedExternImport::get_name() const {
{
return (((((*this).assigned_namespace)).name).value());
}
}

bool parser::ParsedExternImport::is_equivalent_to(parser::ParsedExternImport const other) const {
{
return (((*this).is_c) && (((other).is_c) && (((((*this).get_path())) == (((other).get_path()))) && (((((*this).get_name())) == (((other).get_name()))) && ((((*this).should_auto_import)) == (((other).should_auto_import)))))));
}
}

parser::ParsedExternImport::ParsedExternImport(bool a_is_c, parser::ParsedNamespace a_assigned_namespace, JaktInternal::DynamicArray<parser::IncludeAction> a_before_include, JaktInternal::DynamicArray<parser::IncludeAction> a_after_include, bool a_should_auto_import): is_c(move(a_is_c)), assigned_namespace(move(a_assigned_namespace)), before_include(move(a_before_include)), after_include(move(a_after_include)), should_auto_import(move(a_should_auto_import)){}

ByteString parser::ParsedAlias::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedAlias("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("alias_name: {}, ", alias_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("target: {}", target);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedAlias::ParsedAlias(JaktInternal::Optional<parser::ParsedName> a_alias_name, JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> a_target): alias_name(move(a_alias_name)), target(move(a_target)){}

ByteString parser::ParsedNamespace::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedNamespace("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: {}, ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("functions: {}, ", functions);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("records: {}, ", records);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("traits: {}, ", traits);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_trait_implementations: {}, ", external_trait_implementations);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespaces: {}, ", namespaces);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("aliases: {}, ", aliases);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module_imports: {}, ", module_imports);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("extern_imports: {}, ", extern_imports);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("import_path_if_extern: {}, ", import_path_if_extern);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generating_import_extern_before_include: {}, ", generating_import_extern_before_include);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generating_import_extern_after_include: {}, ", generating_import_extern_after_include);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("forall_chunks: {}, ", forall_chunks);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_generated_code: {}, ", is_generated_code);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_auto_extern_imported: {}", is_auto_extern_imported);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedNamespace::is_equivalent_to(parser::ParsedNamespace const other) const {
{
return (((((*this).name)) == (((other).name))) && ((((*this).import_path_if_extern)) == (((other).import_path_if_extern))));
}
}

void parser::ParsedNamespace::add_module_import(parser::ParsedModuleImport const import_) {
{
{
JaktInternal::ArrayIterator<parser::ParsedModuleImport> _magic = ((((*this).module_imports)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedModuleImport> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedModuleImport module_import = (_magic_value.value());
{
if (((module_import).is_equivalent_to(import_))){
((module_import).merge_import_list(((import_).import_list)));
return;
}
}

}
}

((((*this).module_imports)).push(import_));
}
}

void parser::ParsedNamespace::add_extern_import(parser::ParsedExternImport const import_) {
{
{
JaktInternal::ArrayIterator<parser::ParsedExternImport> _magic = ((((*this).extern_imports)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedExternImport> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedExternImport extern_import = (_magic_value.value());
{
if (((extern_import).is_equivalent_to(import_))){
((((extern_import).assigned_namespace)).merge_with(((import_).assigned_namespace)));
((((extern_import).before_include)).push_values(((((import_).before_include)))));
((((extern_import).after_include)).push_values(((((import_).after_include)))));
return;
}
}

}
}

((((*this).extern_imports)).push(import_));
}
}

void parser::ParsedNamespace::add_child_namespace(parser::ParsedNamespace const namespace_) {
{
{
JaktInternal::ArrayIterator<parser::ParsedNamespace> _magic = ((((*this).namespaces)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNamespace child_namespace = (_magic_value.value());
{
if (((child_namespace).is_equivalent_to(namespace_))){
((child_namespace).merge_with(namespace_));
return;
}
}

}
}

((((*this).namespaces)).push(namespace_));
}
}

void parser::ParsedNamespace::add_alias(parser::ParsedAlias const alias) {
{
((((*this).aliases)).push(alias));
}
}

void parser::ParsedNamespace::merge_with(parser::ParsedNamespace const namespace_) {
{
((((*this).functions)).push_values(((((namespace_).functions)))));
((((*this).records)).push_values(((((namespace_).records)))));
((((*this).module_imports)).add_capacity(((((namespace_).module_imports)).size())));
{
JaktInternal::ArrayIterator<parser::ParsedModuleImport> _magic = ((((namespace_).module_imports)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedModuleImport> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedModuleImport import_ = (_magic_value.value());
{
((*this).add_module_import(import_));
}

}
}

((((*this).extern_imports)).add_capacity(((((namespace_).extern_imports)).size())));
{
JaktInternal::ArrayIterator<parser::ParsedExternImport> _magic = ((((namespace_).extern_imports)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedExternImport> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedExternImport import_ = (_magic_value.value());
{
((*this).add_extern_import(import_));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedNamespace> _magic = ((((namespace_).namespaces)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedNamespace child_namespace = (_magic_value.value());
{
((*this).add_child_namespace(child_namespace));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedAlias> _magic = ((((namespace_).aliases)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedAlias> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedAlias alias = (_magic_value.value());
{
((*this).add_alias(alias));
}

}
}

}
}

parser::ParsedNamespace::ParsedNamespace(JaktInternal::Optional<ByteString> a_name, JaktInternal::Optional<utility::Span> a_name_span, JaktInternal::DynamicArray<parser::ParsedFunction> a_functions, JaktInternal::DynamicArray<parser::ParsedRecord> a_records, JaktInternal::DynamicArray<parser::ParsedTrait> a_traits, JaktInternal::DynamicArray<parser::ParsedExternalTraitImplementation> a_external_trait_implementations, JaktInternal::DynamicArray<parser::ParsedNamespace> a_namespaces, JaktInternal::DynamicArray<parser::ParsedAlias> a_aliases, JaktInternal::DynamicArray<parser::ParsedModuleImport> a_module_imports, JaktInternal::DynamicArray<parser::ParsedExternImport> a_extern_imports, JaktInternal::Optional<ByteString> a_import_path_if_extern, JaktInternal::DynamicArray<parser::IncludeAction> a_generating_import_extern_before_include, JaktInternal::DynamicArray<parser::IncludeAction> a_generating_import_extern_after_include, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>> a_forall_chunks, bool a_is_generated_code, bool a_is_auto_extern_imported): name(move(a_name)), name_span(move(a_name_span)), functions(move(a_functions)), records(move(a_records)), traits(move(a_traits)), external_trait_implementations(move(a_external_trait_implementations)), namespaces(move(a_namespaces)), aliases(move(a_aliases)), module_imports(move(a_module_imports)), extern_imports(move(a_extern_imports)), import_path_if_extern(move(a_import_path_if_extern)), generating_import_extern_before_include(move(a_generating_import_extern_before_include)), generating_import_extern_after_include(move(a_generating_import_extern_after_include)), forall_chunks(move(a_forall_chunks)), is_generated_code(move(a_is_generated_code)), is_auto_extern_imported(move(a_is_auto_extern_imported)){}

ByteString parser::ValueEnumVariant::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ValueEnumVariant("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("value: {}", value);
}
builder.append(")"sv);return builder.to_string(); }
parser::ValueEnumVariant::ValueEnumVariant(ByteString a_name, utility::Span a_span, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_value): name(move(a_name)), span(move(a_span)), value(move(a_value)){}

ByteString parser::SumEnumVariant::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("SumEnumVariant("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("default_values: {}", default_values);
}
builder.append(")"sv);return builder.to_string(); }
parser::SumEnumVariant::SumEnumVariant(ByteString a_name, utility::Span a_span, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedVarDecl>> a_params, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>>>> a_default_values): name(move(a_name)), span(move(a_span)), params(move(a_params)), default_values(move(a_default_values)){}

ByteString parser::ParsedRecord::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedRecord("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}, ", generic_parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("definition_linkage: {}, ", definition_linkage);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("implements_list: {}, ", implements_list);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("methods: {}, ", methods);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("record_type: {}, ", record_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("nested_records: {}, ", nested_records);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}", external_name);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedRecord::ParsedRecord(ByteString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> a_implements_list, JaktInternal::DynamicArray<parser::ParsedMethod> a_methods, parser::RecordType a_record_type, JaktInternal::DynamicArray<parser::ParsedRecord> a_nested_records, JaktInternal::Optional<parser::ExternalName> a_external_name): name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)), definition_linkage(move(a_definition_linkage)), implements_list(move(a_implements_list)), methods(move(a_methods)), record_type(move(a_record_type)), nested_records(move(a_nested_records)), external_name(move(a_external_name)){}

ByteString parser::ParsedFunction::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedFunction("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}, ", id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("visibility: {}, ", visibility);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}, ", generic_parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type: {}, ", return_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type_span: {}, ", return_type_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type: {}, ", type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("linkage: {}, ", linkage);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("must_instantiate: {}, ", must_instantiate);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_comptime: {}, ", is_comptime);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_fat_arrow: {}, ", is_fat_arrow);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_unsafe: {}, ", is_unsafe);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("has_varargs: {}, ", has_varargs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_jakt_main: {}, ", is_jakt_main);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}, ", external_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("deprecated_message: {}, ", deprecated_message);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("stores_arguments: {}, ", stores_arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("force_inline: {}", force_inline);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedFunction::equals(parser::ParsedFunction const other,bool const ignore_block) const {
{
if (((([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((*this).name),((other).name)) || ((((*this).can_throw)) != (((other).can_throw)))) || ((((*this).is_comptime)) != (((other).is_comptime)))) || ((((*this).is_fat_arrow)) != (((other).is_fat_arrow))))){
return false;
}
if (((!(ignore_block)) && (!(((((*this).block)).equals(((other).block))))))){
return false;
}
if (((((((*this).params)).size())) != (((((other).params)).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t param_index = (_magic_value.value());
{
if ((!(((((((*this).params))[param_index])).equals(((((other).params))[param_index])))))){
return false;
}
}

}
}

if (((((((*this).generic_parameters)).size())) != (((((other).generic_parameters)).size())))){
return false;
}
return true;
}
}

parser::ParsedFunction::ParsedFunction(size_t a_id, ByteString a_name, utility::Span a_name_span, parser::Visibility a_visibility, JaktInternal::DynamicArray<parser::ParsedParameter> a_params, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::ParsedBlock a_block, NonnullRefPtr<typename parser::ParsedType> a_return_type, utility::Span a_return_type_span, bool a_can_throw, parser::FunctionType a_type, parser::FunctionLinkage a_linkage, bool a_must_instantiate, bool a_is_comptime, bool a_is_fat_arrow, bool a_is_unsafe, bool a_has_varargs, bool a_is_jakt_main, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<ByteString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> a_stores_arguments, parser::InlineState a_force_inline): id(move(a_id)), name(move(a_name)), name_span(move(a_name_span)), visibility(move(a_visibility)), params(move(a_params)), generic_parameters(move(a_generic_parameters)), block(move(a_block)), return_type(move(a_return_type)), return_type_span(move(a_return_type_span)), can_throw(move(a_can_throw)), type(move(a_type)), linkage(move(a_linkage)), must_instantiate(move(a_must_instantiate)), is_comptime(move(a_is_comptime)), is_fat_arrow(move(a_is_fat_arrow)), is_unsafe(move(a_is_unsafe)), has_varargs(move(a_has_varargs)), is_jakt_main(move(a_is_jakt_main)), external_name(move(a_external_name)), deprecated_message(move(a_deprecated_message)), stores_arguments(move(a_stores_arguments)), force_inline(move(a_force_inline)){}

ByteString parser::ParsedParameter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedParameter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("requires_label: {}, ", requires_label);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variable: {}, ", variable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("default_argument: {}, ", default_argument);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedParameter::equals(parser::ParsedParameter const rhs_param) const {
{
if ((((((*this).requires_label)) == (((rhs_param).requires_label))) && ((((*this).variable)).equals(((rhs_param).variable))))){
if ((((((*this).default_argument)).has_value()) && ((((rhs_param).default_argument)).has_value()))){
return (((((*this).default_argument).value()))->equals((((rhs_param).default_argument).value())));
}
return ((!(((((*this).default_argument)).has_value()))) && (!(((((rhs_param).default_argument)).has_value()))));
}
else {
return false;
}

}
}

parser::ParsedParameter::ParsedParameter(bool a_requires_label, parser::ParsedVariable a_variable, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_default_argument, utility::Span a_span): requires_label(move(a_requires_label)), variable(move(a_variable)), default_argument(move(a_default_argument)), span(move(a_span)){}

ByteString parser::ParsedName::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedName("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedName::ParsedName(ByteString a_name, utility::Span a_span): name(move(a_name)), span(move(a_span)){}

ByteString parser::ParsedNameWithGenericParameters::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedNameWithGenericParameters("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}", generic_parameters);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedNameWithGenericParameters::ParsedNameWithGenericParameters(ByteString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> a_generic_parameters): name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)){}

ByteString parser::ParsedGenericParameter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedGenericParameter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("requires_list: {}, ", requires_list);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_value: {}", is_value);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedGenericParameter::ParsedGenericParameter(ByteString a_name, utility::Span a_span, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> a_requires_list, bool a_is_value): name(move(a_name)), span(move(a_span)), requires_list(move(a_requires_list)), is_value(move(a_is_value)){}

ByteString parser::ParsedTrait::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedTrait("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}, ", generic_parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("requirements: {}", requirements);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedTrait::ParsedTrait(ByteString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<parser::ParsedGenericParameter> a_generic_parameters, parser::ParsedTraitRequirements a_requirements): name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)), requirements(move(a_requirements)){}

ByteString parser::ParsedExternalTraitImplementation::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedExternalTraitImplementation("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("for_type: {}, ", for_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("traits: {}, ", traits);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("methods: {}", methods);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedExternalTraitImplementation::ParsedExternalTraitImplementation(NonnullRefPtr<typename parser::ParsedType> a_for_type, JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> a_traits, JaktInternal::DynamicArray<parser::ParsedMethod> a_methods): for_type(move(a_for_type)), traits(move(a_traits)), methods(move(a_methods)){}

ByteString parser::ParsedBlock::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedBlock("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("stmts: {}", stmts);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedBlock::equals(parser::ParsedBlock const rhs_block) const {
{
if (((((((*this).stmts)).size())) != (((((rhs_block).stmts)).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).stmts)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t x = (_magic_value.value());
{
if ((!(((((((*this).stmts))[x]))->equals(((((rhs_block).stmts))[x])))))){
return false;
}
}

}
}

return true;
}
}

JaktInternal::Optional<utility::Span> parser::ParsedBlock::find_yield_span() const {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedStatement>> _magic = ((((*this).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedStatement> stmt = (_magic_value.value());
{
if (((stmt)->__jakt_init_index() == 14 /* Yield */)){
NonnullRefPtr<typename parser::ParsedExpression> const expr = (stmt)->as.Yield.expr;
return ((expr)->span());
}
}

}
}

return JaktInternal::OptionalNone();
}
}

JaktInternal::Optional<utility::Span> parser::ParsedBlock::find_yield_keyword_span() const {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedStatement>> _magic = ((((*this).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedStatement> stmt = (_magic_value.value());
{
if (((stmt)->__jakt_init_index() == 14 /* Yield */)){
NonnullRefPtr<typename parser::ParsedExpression> const expr = (stmt)->as.Yield.expr;
return ((stmt)->span());
}
}

}
}

return JaktInternal::OptionalNone();
}
}

JaktInternal::Optional<utility::Span> parser::ParsedBlock::span(parser::Parser const parser) const {
{
JaktInternal::Optional<size_t> start = JaktInternal::OptionalNone();
size_t end = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedStatement>> _magic = ((((*this).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedStatement> stmt = (_magic_value.value());
{
utility::Span const stmt_span = ((stmt)->span());
if ((!(((start).has_value())))){
(start = ((stmt_span).start));
}
(end = ((stmt_span).end));
}

}
}

if (((start).has_value())){
return ((parser).span((start.value()),end));
}
return JaktInternal::OptionalNone();
}
}

parser::ParsedBlock::ParsedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>> a_stmts): stmts(move(a_stmts)){}

ByteString parser::EnumVariantPatternArgument::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("EnumVariantPatternArgument("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: {}, ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("binding: \"{}\", ", binding);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_reference: {}, ", is_reference);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_mutable: {}", is_mutable);
}
builder.append(")"sv);return builder.to_string(); }
ByteString parser::EnumVariantPatternArgument::name_in_enum() const {
{
return ((*this).name).value_or_lazy_evaluated([&] { return ((*this).binding); });
}
}

utility::Span parser::EnumVariantPatternArgument::name_in_enum_span() const {
{
return ((*this).name_span).value_or_lazy_evaluated([&] { return ((*this).span); });
}
}

bool parser::EnumVariantPatternArgument::equals(parser::EnumVariantPatternArgument const rhs_variant_pattern_argument) const {
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((*this).binding),((rhs_variant_pattern_argument).binding))){
return false;
}
if ((((((*this).name)).has_value()) && ((((rhs_variant_pattern_argument).name)).has_value()))){
return (((((*this).name).value())) == ((((rhs_variant_pattern_argument).name).value())));
}
if (((((*this).is_reference)) != (((rhs_variant_pattern_argument).is_reference)))){
return false;
}
if (((((*this).is_mutable)) != (((rhs_variant_pattern_argument).is_mutable)))){
return false;
}
return ((!(((((*this).name)).has_value()))) && (!(((((rhs_variant_pattern_argument).name)).has_value()))));
}
}

parser::EnumVariantPatternArgument::EnumVariantPatternArgument(JaktInternal::Optional<ByteString> a_name, JaktInternal::Optional<utility::Span> a_name_span, ByteString a_binding, utility::Span a_span, bool a_is_reference, bool a_is_mutable): name(move(a_name)), name_span(move(a_name_span)), binding(move(a_binding)), span(move(a_span)), is_reference(move(a_is_reference)), is_mutable(move(a_is_mutable)){}

ByteString parser::ParsedPatternDefault::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedPatternDefault("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variable: {}, ", variable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("value: {}", value);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedPatternDefault::ParsedPatternDefault(parser::ParsedVarDecl a_variable, NonnullRefPtr<typename parser::ParsedExpression> a_value): variable(move(a_variable)), value(move(a_value)){}

ByteString parser::ParsedMatchCase::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedMatchCase("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("patterns: {}, ", patterns);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}, ", marker_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("body: {}", body);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedMatchCase::has_equal_pattern(parser::ParsedMatchCase const rhs_match_case) const {
{
if (((((((*this).patterns)).size())) == (((((rhs_match_case).patterns)).size())))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((((*this).patterns)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((((*this).patterns))[i])).is_equal_pattern(((((rhs_match_case).patterns))[i])))))){
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
}

bool parser::ParsedMatchCase::equals(parser::ParsedMatchCase const rhs_match_case) const {
{
if (((((((*this).patterns)).size())) == (((((rhs_match_case).patterns)).size())))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((((*this).patterns)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((((*this).patterns))[i])).equals(((((rhs_match_case).patterns))[i])))))){
return false;
}
}

}
}

return ((((*this).body)).equals(((rhs_match_case).body)));
}
else {
return false;
}

}
}

parser::ParsedMatchCase::ParsedMatchCase(JaktInternal::DynamicArray<parser::ParsedMatchPattern> a_patterns, utility::Span a_marker_span, parser::ParsedMatchBody a_body): patterns(move(a_patterns)), marker_span(move(a_marker_span)), body(move(a_body)){}

ByteString parser::ParsedVarDecl::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedVarDecl("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parsed_type: {}, ", parsed_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_mutable: {}, ", is_mutable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inlay_span: {}, ", inlay_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}", external_name);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedVarDecl::equals(parser::ParsedVarDecl const rhs_var_decl) const {
{
return (((((*this).name)) == (((rhs_var_decl).name))) && ((((*this).is_mutable)) == (((rhs_var_decl).is_mutable))));
}
}

parser::ParsedVarDecl::ParsedVarDecl(ByteString a_name, NonnullRefPtr<typename parser::ParsedType> a_parsed_type, bool a_is_mutable, JaktInternal::Optional<utility::Span> a_inlay_span, utility::Span a_span, JaktInternal::Optional<parser::ExternalName> a_external_name): name(move(a_name)), parsed_type(move(a_parsed_type)), is_mutable(move(a_is_mutable)), inlay_span(move(a_inlay_span)), span(move(a_span)), external_name(move(a_external_name)){}

ByteString parser::ParsedVarDeclTuple::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedVarDeclTuple("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var_decls: {}, ", var_decls);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedVarDeclTuple::ParsedVarDeclTuple(JaktInternal::DynamicArray<parser::ParsedVarDecl> a_var_decls, utility::Span a_span): var_decls(move(a_var_decls)), span(move(a_span)){}

ByteString parser::ParsedField::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedField("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var_decl: {}, ", var_decl);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("visibility: {}, ", visibility);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("default_value: {}", default_value);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedField::ParsedField(parser::ParsedVarDecl a_var_decl, parser::Visibility a_visibility, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_default_value): var_decl(move(a_var_decl)), visibility(move(a_visibility)), default_value(move(a_default_value)){}

ByteString parser::ParsedMethod::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedMethod("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parsed_function: {}, ", parsed_function);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("visibility: {}, ", visibility);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_virtual: {}, ", is_virtual);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_override: {}", is_override);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedMethod::ParsedMethod(parser::ParsedFunction a_parsed_function, parser::Visibility a_visibility, bool a_is_virtual, bool a_is_override): parsed_function(move(a_parsed_function)), visibility(move(a_visibility)), is_virtual(move(a_is_virtual)), is_override(move(a_is_override)){}

ByteString parser::ParsedVariable::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedVariable("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parsed_type: {}, ", parsed_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_mutable: {}, ", is_mutable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedVariable::equals(parser::ParsedVariable const rhs_parsed_varible) const {
{
return (((((*this).name)) == (((rhs_parsed_varible).name))) && (((((*this).parsed_type))->equals(((rhs_parsed_varible).parsed_type))) && ((((*this).is_mutable)) == (((rhs_parsed_varible).is_mutable)))));
}
}

parser::ParsedVariable::ParsedVariable(ByteString a_name, NonnullRefPtr<typename parser::ParsedType> a_parsed_type, bool a_is_mutable, utility::Span a_span): name(move(a_name)), parsed_type(move(a_parsed_type)), is_mutable(move(a_is_mutable)), span(move(a_span)){}

ByteString parser::ParsedCall::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedCall("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespace_: {}, ", namespace_);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}, ", args);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_args: {}", type_args);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::ParsedCall::equals(parser::ParsedCall const rhs_parsed_call) const {
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((*this).name),((rhs_parsed_call).name))){
return false;
}
if (((((((*this).args)).size())) != (((((rhs_parsed_call).args)).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> const lhs_str___lhs_expr_ = ((((*this).args))[i]);
ByteString const lhs_str = ((lhs_str___lhs_expr_).template get<0>());
utility::Span const _ = ((lhs_str___lhs_expr_).template get<1>());
NonnullRefPtr<typename parser::ParsedExpression> const lhs_expr = ((lhs_str___lhs_expr_).template get<2>());

JaktInternal::Tuple<ByteString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>> const rhs_str____rhs_expr_ = ((((rhs_parsed_call).args))[i]);
ByteString const rhs_str = ((rhs_str____rhs_expr_).template get<0>());
utility::Span const __ = ((rhs_str____rhs_expr_).template get<1>());
NonnullRefPtr<typename parser::ParsedExpression> const rhs_expr = ((rhs_str____rhs_expr_).template get<2>());

if (([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(lhs_str,rhs_str) || (!(((lhs_expr)->equals(rhs_expr)))))){
return false;
}
}

}
}

return true;
}
}

parser::ParsedCall::ParsedCall(JaktInternal::DynamicArray<ByteString> a_namespace_, ByteString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>> a_args, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> a_type_args): namespace_(move(a_namespace_)), name(move(a_name)), args(move(a_args)), type_args(move(a_type_args)){}

ByteString parser::ParsedTypeQualifiers::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedTypeQualifiers("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_mutable: {}, ", is_mutable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_immutable: {}", is_immutable);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedTypeQualifiers::ParsedTypeQualifiers(bool a_is_mutable, bool a_is_immutable): is_mutable(move(a_is_mutable)), is_immutable(move(a_is_immutable)){}

ByteString parser::CheckedQualifiers::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedQualifiers("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_immutable: {}", is_immutable);
}
builder.append(")"sv);return builder.to_string(); }
bool parser::CheckedQualifiers::equals(parser::CheckedQualifiers const other) const {
{
return ((((*this).is_immutable)) == (((other).is_immutable)));
}
}

parser::CheckedQualifiers::CheckedQualifiers(bool a_is_immutable): is_immutable(move(a_is_immutable)){}


ByteString parser::VisibilityRestriction::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("VisibilityRestriction("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespace_: {}, ", namespace_);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\"", name);
}
builder.append(")"sv);return builder.to_string(); }
parser::VisibilityRestriction::VisibilityRestriction(JaktInternal::DynamicArray<ByteString> a_namespace_, ByteString a_name): namespace_(move(a_namespace_)), name(move(a_name)){}

ByteString parser::ParsedAttributeArgument::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedAttributeArgument("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("assigned_value: {}", assigned_value);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedAttributeArgument::ParsedAttributeArgument(ByteString a_name, utility::Span a_span, JaktInternal::Optional<ByteString> a_assigned_value): name(move(a_name)), span(move(a_span)), assigned_value(move(a_assigned_value)){}

ByteString parser::ParsedAttribute::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ParsedAttribute("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("assigned_value: {}, ", assigned_value);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arguments: {}", arguments);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedAttribute::ParsedAttribute(ByteString a_name, utility::Span a_span, JaktInternal::Optional<ByteString> a_assigned_value, JaktInternal::DynamicArray<parser::ParsedAttributeArgument> a_arguments): name(move(a_name)), span(move(a_span)), assigned_value(move(a_assigned_value)), arguments(move(a_arguments)){}

ByteString parser::Parser::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Parser("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("tokens: {}, ", tokens);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_have_trailing_closure: {}, ", can_have_trailing_closure);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("next_function_id: {}", next_function_id);
}
builder.append(")"sv);return builder.to_string(); }
parser::ParsedNamespace parser::Parser::parse(NonnullRefPtr<compiler::Compiler> const compiler,JaktInternal::DynamicArray<lexer::Token> const tokens) {
{
parser::Parser parser = parser::Parser(static_cast<size_t>(0ULL),tokens,compiler,true,static_cast<size_t>(0ULL));
return ((parser).parse_namespace(false));
}
}

utility::Span parser::Parser::span(size_t const start,size_t const end) const {
{
return utility::Span((((((*this).compiler))->current_file).value()),start,end);
}
}

utility::Span parser::Parser::empty_span() const {
{
return ((*this).span(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)));
}
}

void parser::Parser::error(ByteString const message,utility::Span const span) {
{
if ((!(((((*this).compiler))->ignore_parser_errors)))){
((((((*this).compiler))->errors)).push(error::JaktError::Message(message,span)));
}
}
}

void parser::Parser::error_with_hint(ByteString const message,utility::Span const span,ByteString const hint,utility::Span const hint_span) {
{
if ((!(((((*this).compiler))->ignore_parser_errors)))){
((((((*this).compiler))->errors)).push(error::JaktError::MessageWithHint(message,span,hint,hint_span)));
}
}
}

bool parser::Parser::eof() const {
{
return [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((*this).index),JaktInternal::checked_sub(((((*this).tokens)).size()),static_cast<size_t>(1ULL)));
}
}

bool parser::Parser::eol() const {
{
return (((*this).eof()) || ((((((*this).tokens))[((*this).index)])).__jakt_init_index() == 55 /* Eol */));
}
}

lexer::Token parser::Parser::peek(size_t const steps) const {
{
if ((((*this).eof()) || [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(JaktInternal::checked_add(steps,((*this).index)),((((*this).tokens)).size())))){
return (((((*this).tokens)).last()).value());
}
return ((((*this).tokens))[JaktInternal::checked_add(((*this).index),steps)]);
}
}

lexer::Token parser::Parser::previous() const {
{
if ((((((*this).index)) == (static_cast<size_t>(0ULL))) || [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((*this).index),((((*this).tokens)).size())))){
return lexer::Token::Eof(((*this).span(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))));
}
return ((((*this).tokens))[JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL))]);
}
}

lexer::Token parser::Parser::current() const {
{
return ((*this).peek(static_cast<size_t>(0ULL)));
}
}

void parser::Parser::inject_token(lexer::Token const token) {
{
((((*this).tokens)).insert(JaktInternal::checked_add(((*this).index),static_cast<size_t>(1ULL)),token));
}
}

JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace> parser::Parser::parse_forall() {
{
JaktInternal::DynamicArray<parser::ParsedGenericParameter> const parameters = ((*this).parse_generic_parameters());
parser::ParsedNamespace const contents = ((*this).parse_namespace(true));
return (Tuple{parameters, contents});
}
}

parser::ParsedNamespace parser::Parser::parse_namespace(bool const process_only_one_entity) {
{
parser::ParsedNamespace parsed_namespace = parser::ParsedNamespace(JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),DynamicArray<parser::ParsedFunction>::create_with({}),DynamicArray<parser::ParsedRecord>::create_with({}),DynamicArray<parser::ParsedTrait>::create_with({}),DynamicArray<parser::ParsedExternalTraitImplementation>::create_with({}),DynamicArray<parser::ParsedNamespace>::create_with({}),DynamicArray<parser::ParsedAlias>::create_with({}),DynamicArray<parser::ParsedModuleImport>::create_with({}),DynamicArray<parser::ParsedExternImport>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<parser::IncludeAction>::create_with({}),DynamicArray<parser::IncludeAction>::create_with({}),DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>>::create_with({}),false,false);
JaktInternal::DynamicArray<parser::ParsedAttribute> active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({});
bool saw_an_entity = false;
while ((!(((*this).eof())))){
if ((process_only_one_entity && saw_an_entity)){
break;
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedNamespace>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 112 /* Trait */: {
{
if ((!(((active_attributes).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("Cannot apply attributes to trait declarations"sv)),((((active_attributes)[static_cast<i64>(0LL)])).span)));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
}
((((*this).index)++));
((((parsed_namespace).traits)).push(((*this).parse_trait())));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,parser::ParsedNamespace> {
auto __jakt_enum_value = (name);
if (__jakt_enum_value == "type"sv) {
{
if ((!(((active_attributes).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("Cannot apply attributes to external trait declarations"sv)),((((active_attributes)[static_cast<i64>(0LL)])).span)));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
}
((((*this).index)++));
((((parsed_namespace).external_trait_implementations)).push(((*this).parse_external_trait_implementation())));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "use"sv) {
{
if ((!(((active_attributes).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("Cannot apply attributes to use declarations"sv)),((((active_attributes)[static_cast<i64>(0LL)])).span)));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
}
((((*this).index)++));
((((parsed_namespace).aliases)).push(((*this).parse_using())));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "forall"sv) {
{
if ((!(((active_attributes).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("Cannot apply attributes to forall declarations"sv)),((((active_attributes)[static_cast<i64>(0LL)])).span)));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
}
((((*this).index)++));
((((parsed_namespace).forall_chunks)).push(((*this).parse_forall())));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((*this).error((ByteString::from_utf8_without_validation("Unexpected token (expected keyword)"sv)),((((*this).current())).span())));
return JaktInternal::LoopBreak{};
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
})), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 78 /* Import */: {
{
if ((!(((active_attributes).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("Cannot apply attributes to imports"sv)),((((active_attributes)[static_cast<i64>(0LL)])).span)));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
}
((((*this).index)++));
((*this).parse_import(((parsed_namespace))));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
{
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 11 /* LSquare */)){
((((*this).index)) += (static_cast<size_t>(2ULL)));
((*this).parse_attribute_list(((active_attributes))));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Unexpected token (expected ‘[[’)"sv)),((((*this).current())).span())));
((((*this).index)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 104 /* Unsafe */: {
{
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 75 /* Fn */)){
parser::ParsedFunction parsed_function = ((*this).parse_function(parser::FunctionLinkage::Internal(),parser::Visibility::Public(),((((*this).current())).__jakt_init_index() == 76 /* Comptime */),false,true,false));
((*this).apply_attributes(((parsed_function)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).functions)).push(parsed_function));
(saw_an_entity = true);
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected 'fn' after 'unsafe'"sv)),((((*this).current())).span())));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
{
parser::ParsedFunction parsed_function = ((*this).parse_function(parser::FunctionLinkage::Internal(),parser::Visibility::Public(),((((*this).current())).__jakt_init_index() == 76 /* Comptime */),false,false,false));
((*this).apply_attributes(((parsed_function)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).functions)).push(parsed_function));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
{
parser::ParsedFunction parsed_function = ((*this).parse_function(parser::FunctionLinkage::Internal(),parser::Visibility::Public(),((((*this).current())).__jakt_init_index() == 76 /* Comptime */),false,false,false));
((*this).apply_attributes(((parsed_function)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).functions)).push(parsed_function));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
{
parser::ParsedRecord parsed_record = ((*this).parse_record(parser::DefinitionLinkage::Internal()));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).records)).push(parsed_record));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
{
parser::ParsedRecord parsed_record = ((*this).parse_record(parser::DefinitionLinkage::Internal()));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).records)).push(parsed_record));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
{
parser::ParsedRecord parsed_record = ((*this).parse_record(parser::DefinitionLinkage::Internal()));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).records)).push(parsed_record));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
{
parser::ParsedRecord parsed_record = ((*this).parse_record(parser::DefinitionLinkage::Internal()));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).records)).push(parsed_record));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87 /* Namespace */: {
{
((((*this).index)++));
JaktInternal::Optional<JaktInternal::Tuple<ByteString,utility::Span>> const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Tuple<ByteString,utility::Span>>, parser::ParsedNamespace>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::Tuple<ByteString,utility::Span>>> __jakt_var_7; {
((((*this).index)++));
__jakt_var_7 = static_cast<JaktInternal::Optional<JaktInternal::Tuple<ByteString,utility::Span>>>((Tuple{name, span})); goto __jakt_label_3;

}
__jakt_label_3:; __jakt_var_7.release_value(); }));
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
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘{’"sv)),((((*this).current())).span())));
}

parser::ParsedNamespace namespace_ = ((*this).parse_namespace(false));
if (((((*this).current())).__jakt_init_index() == 10 /* RCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Incomplete namespace"sv)),((((*this).previous())).span())));
}

if (((name).has_value())){
(((namespace_).name) = (((name.value())).template get<0>()));
(((namespace_).name_span) = (((name.value())).template get<1>()));
}
((*this).apply_attributes(((namespace_)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((parsed_namespace).add_child_namespace(namespace_));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 72 /* Extern */: {
{
((((*this).index)++));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedNamespace>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 104 /* Unsafe */: {
{
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 75 /* Fn */)){
parser::ParsedFunction parsed_function = ((*this).parse_function(parser::FunctionLinkage::External(),parser::Visibility::Public(),false,false,true,false));
((*this).apply_attributes(((parsed_function)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).functions)).push(parsed_function));
(saw_an_entity = true);
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected 'fn' after 'unsafe'"sv)),((((*this).current())).span())));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
{
parser::ParsedFunction parsed_function = ((*this).parse_function(parser::FunctionLinkage::External(),parser::Visibility::Public(),false,false,false,false));
((*this).apply_attributes(((parsed_function)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).functions)).push(parsed_function));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
{
parser::ParsedRecord parsed_struct = ((*this).parse_struct(parser::DefinitionLinkage::External()));
((*this).apply_attributes(((parsed_struct)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).records)).push(parsed_struct));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
{
parser::ParsedRecord parsed_class = ((*this).parse_class(parser::DefinitionLinkage::External()));
((*this).apply_attributes(((parsed_class)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).records)).push(parsed_class));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
{
parser::ParsedRecord parsed_enum = ((*this).parse_enum(parser::DefinitionLinkage::External(),false));
((*this).apply_attributes(((parsed_enum)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((((parsed_namespace).records)).push(parsed_enum));
(saw_an_entity = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((*this).error((ByteString::from_utf8_without_validation("Unexpected keyword"sv)),((((*this).current())).span())));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Unexpected token (expected keyword)"sv)),((((*this).current())).span())));
return JaktInternal::LoopBreak{};
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
return parsed_namespace;
}
}

void parser::Parser::apply_attributes(parser::ParsedNamespace& namespace_,JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes) {
{
{
JaktInternal::ArrayIterator<parser::ParsedAttribute> _magic = ((((active_attributes))).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedAttribute> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedAttribute attribute = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,void> {
auto __jakt_enum_value = (((attribute).name));
if (__jakt_enum_value == "extern_import"sv) {
{
if ((!(((((attribute).assigned_value)).has_value())))){
{
JaktInternal::ArrayIterator<parser::ParsedAttributeArgument> _magic = ((((attribute).arguments)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedAttributeArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedAttributeArgument argument = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,void> {
auto __jakt_enum_value = (((argument).name));
if (__jakt_enum_value == "from"sv) {
{
(((((namespace_))).import_path_if_extern) = ((argument).assigned_value));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "define_before"sv) {
{
if (((((argument).assigned_value)).has_value())){
if (((((argument).name)).starts_with((ByteString::from_utf8_without_validation("define"sv))))){
JaktInternal::DynamicArray<ByteString> const parts = (((((argument).assigned_value).value())).split('='));
if (((((parts).size())) != (static_cast<size_t>(2ULL)))){
((*this).error(__jakt_format((StringView::from_string_literal("The argument '{}' expects a value in the form 'name=value'"sv)),((argument).name)),((argument).span)));
return JaktInternal::LoopContinue{};
}
parser::IncludeAction const action = parser::IncludeAction::Define(((parts)[static_cast<i64>(0LL)]),((attribute).span),((parts)[static_cast<i64>(1LL)]));
if (((((argument).name)).ends_with((ByteString::from_utf8_without_validation("before"sv))))){
((((((namespace_))).generating_import_extern_before_include)).push(action));
}
else {
((((((namespace_))).generating_import_extern_after_include)).push(action));
}

}
else {
parser::IncludeAction const action = parser::IncludeAction::Undefine((((argument).assigned_value).value()),((attribute).span));
if (((((argument).name)).ends_with((ByteString::from_utf8_without_validation("before"sv))))){
((((((namespace_))).generating_import_extern_before_include)).push(action));
}
else {
((((((namespace_))).generating_import_extern_after_include)).push(action));
}

}

}
else {
((*this).error(__jakt_format((StringView::from_string_literal("The argument '{}' expects a value"sv)),((argument).name)),((argument).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "undefine_before"sv) {
{
if (((((argument).assigned_value)).has_value())){
if (((((argument).name)).starts_with((ByteString::from_utf8_without_validation("define"sv))))){
JaktInternal::DynamicArray<ByteString> const parts = (((((argument).assigned_value).value())).split('='));
if (((((parts).size())) != (static_cast<size_t>(2ULL)))){
((*this).error(__jakt_format((StringView::from_string_literal("The argument '{}' expects a value in the form 'name=value'"sv)),((argument).name)),((argument).span)));
return JaktInternal::LoopContinue{};
}
parser::IncludeAction const action = parser::IncludeAction::Define(((parts)[static_cast<i64>(0LL)]),((attribute).span),((parts)[static_cast<i64>(1LL)]));
if (((((argument).name)).ends_with((ByteString::from_utf8_without_validation("before"sv))))){
((((((namespace_))).generating_import_extern_before_include)).push(action));
}
else {
((((((namespace_))).generating_import_extern_after_include)).push(action));
}

}
else {
parser::IncludeAction const action = parser::IncludeAction::Undefine((((argument).assigned_value).value()),((attribute).span));
if (((((argument).name)).ends_with((ByteString::from_utf8_without_validation("before"sv))))){
((((((namespace_))).generating_import_extern_before_include)).push(action));
}
else {
((((((namespace_))).generating_import_extern_after_include)).push(action));
}

}

}
else {
((*this).error(__jakt_format((StringView::from_string_literal("The argument '{}' expects a value"sv)),((argument).name)),((argument).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "define_after"sv) {
{
if (((((argument).assigned_value)).has_value())){
if (((((argument).name)).starts_with((ByteString::from_utf8_without_validation("define"sv))))){
JaktInternal::DynamicArray<ByteString> const parts = (((((argument).assigned_value).value())).split('='));
if (((((parts).size())) != (static_cast<size_t>(2ULL)))){
((*this).error(__jakt_format((StringView::from_string_literal("The argument '{}' expects a value in the form 'name=value'"sv)),((argument).name)),((argument).span)));
return JaktInternal::LoopContinue{};
}
parser::IncludeAction const action = parser::IncludeAction::Define(((parts)[static_cast<i64>(0LL)]),((attribute).span),((parts)[static_cast<i64>(1LL)]));
if (((((argument).name)).ends_with((ByteString::from_utf8_without_validation("before"sv))))){
((((((namespace_))).generating_import_extern_before_include)).push(action));
}
else {
((((((namespace_))).generating_import_extern_after_include)).push(action));
}

}
else {
parser::IncludeAction const action = parser::IncludeAction::Undefine((((argument).assigned_value).value()),((attribute).span));
if (((((argument).name)).ends_with((ByteString::from_utf8_without_validation("before"sv))))){
((((((namespace_))).generating_import_extern_before_include)).push(action));
}
else {
((((((namespace_))).generating_import_extern_after_include)).push(action));
}

}

}
else {
((*this).error(__jakt_format((StringView::from_string_literal("The argument '{}' expects a value"sv)),((argument).name)),((argument).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "undefine_after"sv) {
{
if (((((argument).assigned_value)).has_value())){
if (((((argument).name)).starts_with((ByteString::from_utf8_without_validation("define"sv))))){
JaktInternal::DynamicArray<ByteString> const parts = (((((argument).assigned_value).value())).split('='));
if (((((parts).size())) != (static_cast<size_t>(2ULL)))){
((*this).error(__jakt_format((StringView::from_string_literal("The argument '{}' expects a value in the form 'name=value'"sv)),((argument).name)),((argument).span)));
return JaktInternal::LoopContinue{};
}
parser::IncludeAction const action = parser::IncludeAction::Define(((parts)[static_cast<i64>(0LL)]),((attribute).span),((parts)[static_cast<i64>(1LL)]));
if (((((argument).name)).ends_with((ByteString::from_utf8_without_validation("before"sv))))){
((((((namespace_))).generating_import_extern_before_include)).push(action));
}
else {
((((((namespace_))).generating_import_extern_after_include)).push(action));
}

}
else {
parser::IncludeAction const action = parser::IncludeAction::Undefine((((argument).assigned_value).value()),((attribute).span));
if (((((argument).name)).ends_with((ByteString::from_utf8_without_validation("before"sv))))){
((((((namespace_))).generating_import_extern_before_include)).push(action));
}
else {
((((((namespace_))).generating_import_extern_after_include)).push(action));
}

}

}
else {
((*this).error(__jakt_format((StringView::from_string_literal("The argument '{}' expects a value"sv)),((argument).name)),((argument).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
((*this).error(__jakt_format((StringView::from_string_literal("Invalid argument for attribute '{}'"sv)),((attribute).name)),((argument).span)));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return {};
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
else {
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' does not take a value"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "generated"sv) {
{
if ((!(((((attribute).assigned_value)).has_value())))){
(((((namespace_))).is_generated_code) = true);
}
else {
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' does not take a value"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' does not apply to namespaces"sv)),((attribute).name)),((attribute).span)));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
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

void parser::Parser::apply_attributes(parser::ParsedField& field,JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes) {
{
{
JaktInternal::ArrayIterator<parser::ParsedAttribute> _magic = ((((active_attributes))).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedAttribute> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedAttribute attribute = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,void> {
auto __jakt_enum_value = (((attribute).name));
if (__jakt_enum_value == "name"sv) {
{
if (((((attribute).assigned_value)).has_value())){
if (((((((((field))).var_decl)).external_name)).has_value())){
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' cannot be applied more than once"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}
if (((((((attribute).assigned_value).value())).starts_with((ByteString::from_utf8_without_validation("operator("sv)))) && (((((attribute).assigned_value).value())).ends_with((ByteString::from_utf8_without_validation(")"sv)))))){
ByteString const operator_name = (((((attribute).assigned_value).value())).substring(static_cast<size_t>(9ULL),JaktInternal::checked_sub((((((attribute).assigned_value).value())).length()),static_cast<size_t>(10ULL))));
(((((((field))).var_decl)).external_name) = parser::ExternalName::Operator(operator_name,false));
}
else if (((((((attribute).assigned_value).value())).starts_with((ByteString::from_utf8_without_validation("prefix-operator("sv)))) && (((((attribute).assigned_value).value())).ends_with((ByteString::from_utf8_without_validation(")"sv)))))){
ByteString const operator_name = (((((attribute).assigned_value).value())).substring(static_cast<size_t>(16ULL),JaktInternal::checked_sub((((((attribute).assigned_value).value())).length()),static_cast<size_t>(17ULL))));
(((((((field))).var_decl)).external_name) = parser::ExternalName::Operator(operator_name,true));
}
else {
(((((((field))).var_decl)).external_name) = parser::ExternalName::Plain((((attribute).assigned_value).value())));
}

}
else {
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' requires a value"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' does not apply to fields"sv)),((attribute).name)),((attribute).span)));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
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

void parser::Parser::apply_attributes(parser::ParsedFunction& parsed_function,JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes) {
{
{
JaktInternal::ArrayIterator<parser::ParsedAttribute> _magic = ((((active_attributes))).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedAttribute> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedAttribute attribute = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,void> {
auto __jakt_enum_value = (((attribute).name));
if (__jakt_enum_value == "name"sv) {
{
if (((((attribute).assigned_value)).has_value())){
if (((((((parsed_function))).external_name)).has_value())){
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' cannot be applied more than once"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}
if (((((((attribute).assigned_value).value())).starts_with((ByteString::from_utf8_without_validation("operator("sv)))) && (((((attribute).assigned_value).value())).ends_with((ByteString::from_utf8_without_validation(")"sv)))))){
ByteString const operator_name = (((((attribute).assigned_value).value())).substring(static_cast<size_t>(9ULL),JaktInternal::checked_sub((((((attribute).assigned_value).value())).length()),static_cast<size_t>(10ULL))));
(((((parsed_function))).external_name) = parser::ExternalName::Operator(operator_name,false));
}
else if (((((((attribute).assigned_value).value())).starts_with((ByteString::from_utf8_without_validation("prefix-operator("sv)))) && (((((attribute).assigned_value).value())).ends_with((ByteString::from_utf8_without_validation(")"sv)))))){
ByteString const operator_name = (((((attribute).assigned_value).value())).substring(static_cast<size_t>(16ULL),JaktInternal::checked_sub((((((attribute).assigned_value).value())).length()),static_cast<size_t>(17ULL))));
(((((parsed_function))).external_name) = parser::ExternalName::Operator(operator_name,true));
}
else {
(((((parsed_function))).external_name) = parser::ExternalName::Plain((((attribute).assigned_value).value())));
}

}
else {
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' requires a value"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "deprecated"sv) {
{
if (((((((parsed_function))).deprecated_message)).has_value())){
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' cannot be applied more than once"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}
ByteString const message = ((((((attribute).arguments)).first())).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return __jakt_format((StringView::from_string_literal("The function '{}' is marked as deprecated"sv)),((((parsed_function))).name)); });
(((((parsed_function))).deprecated_message) = message);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "inline"sv) {
{
if ((!(((((((parsed_function))).force_inline)).__jakt_init_index() == 0 /* Default */)))){
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' cannot be applied more than once"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}
parser::InlineState const inline_state = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::InlineState,void> {
auto __jakt_enum_value = (((((((attribute).arguments)).first())).map([](auto& _value) { return _value.name; })).value_or_lazy_evaluated([&] { return (ByteString::from_utf8_without_validation(""sv)); }));
if (__jakt_enum_value == "never"sv) {
return JaktInternal::ExplicitValue(parser::InlineState::Default());
}
else if (__jakt_enum_value == ""sv) {
return JaktInternal::ExplicitValue(parser::InlineState::ForceInline());
}
else if (__jakt_enum_value == "always"sv) {
return JaktInternal::ExplicitValue(parser::InlineState::ForceInline());
}
else if (__jakt_enum_value == "make_available"sv) {
return JaktInternal::ExplicitValue(parser::InlineState::MakeDefinitionAvailable());
}
else {
{
((*this).error(__jakt_format((StringView::from_string_literal("Invalid argument for attribute '{}'"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}
}
}());
    if (_jakt_value.is_return())
        return {};
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
(((((parsed_function))).force_inline) = inline_state);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "stores_arguments"sv) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>> stores_arguments = DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>::create_with({});
{
JaktInternal::ArrayIterator<parser::ParsedAttributeArgument> _magic = ((((attribute).arguments)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedAttributeArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedAttributeArgument argument = (_magic_value.value());
{
JaktInternal::Optional<ByteString> const target = ((argument).assigned_value);
JaktInternal::Optional<size_t> target_index = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> name_index = JaktInternal::OptionalNone();
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<parser::ParsedParameter> _magic = ((((((parsed_function))).params)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_8([&] {
((index) += (static_cast<size_t>(1ULL)));
});
if (((((((param).variable)).name)) == (((argument).name)))){
(name_index = index);
}
if ((((target).has_value()) && ((((((param).variable)).name)) == ((target.value()))))){
(target_index = index);
}
}

}
}

if ((!(((name_index).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Argument '{}' declared as stored here does not exist"sv)),((argument).name)),((argument).span)));
continue;
}
if ((((target).has_value()) && (!(((target_index).has_value()))))){
((*this).error(__jakt_format((StringView::from_string_literal("Argument '{}' declared as store target here does not exist"sv)),(target.value())),((argument).span)));
continue;
}
JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel> entry = (Tuple{(name_index.value()), parser::ArgumentStoreLevel::InStaticStorage()});
if (((target).has_value())){
(((entry).template get<1>()) = parser::ArgumentStoreLevel::InObject((target_index.value())));
}
((stores_arguments).push(entry));
}

}
}

if (((((((parsed_function))).stores_arguments)).has_value())){
(((((((parsed_function))).stores_arguments).value())).push_values(((stores_arguments))));
}
else {
(((((parsed_function))).stores_arguments) = stores_arguments);
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' does not apply to functions"sv)),((attribute).name)),((attribute).span)));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
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

void parser::Parser::apply_attributes(parser::ParsedMethod& parsed_method,JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes) {
{
((*this).apply_attributes(((((((parsed_method))).parsed_function))),active_attributes));
}
}

void parser::Parser::apply_attributes(parser::ParsedRecord& parsed_record,JaktInternal::DynamicArray<parser::ParsedAttribute> const& active_attributes) {
{
{
JaktInternal::ArrayIterator<parser::ParsedAttribute> _magic = ((((active_attributes))).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedAttribute> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedAttribute attribute = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,void> {
auto __jakt_enum_value = (((attribute).name));
if (__jakt_enum_value == "name"sv) {
{
if (((((attribute).assigned_value)).has_value())){
if (((((((parsed_record))).external_name)).has_value())){
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' cannot be applied more than once"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}
if (((((((attribute).assigned_value).value())).starts_with((ByteString::from_utf8_without_validation("operator("sv)))) && (((((attribute).assigned_value).value())).ends_with((ByteString::from_utf8_without_validation(")"sv)))))){
((*this).error((ByteString::from_utf8_without_validation("A record cannot be renamed to an operator"sv)),((attribute).span)));
return JaktInternal::LoopContinue{};
}
(((((parsed_record))).external_name) = parser::ExternalName::Plain((((attribute).assigned_value).value())));
}
else {
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' requires a value"sv)),((attribute).name)),((attribute).span)));
return JaktInternal::LoopContinue{};
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
((*this).error(__jakt_format((StringView::from_string_literal("The attribute '{}' does not apply to records"sv)),((attribute).name)),((attribute).span)));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
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

void parser::Parser::parse_attribute_list(JaktInternal::DynamicArray<parser::ParsedAttribute>& active_attributes) {
{
while ((((!(((*this).eof()))) && (!(((((*this).current())).__jakt_init_index() == 12 /* RSquare */)))) && (!(((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 12 /* RSquare */))))){
JaktInternal::Optional<parser::ParsedAttribute> const attribute = ((*this).parse_attribute());
if (((attribute).has_value())){
((((active_attributes))).push((attribute.value())));
}
}
if ((((((*this).current())).__jakt_init_index() == 12 /* RSquare */) && ((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 12 /* RSquare */))){
((((*this).index)) += (static_cast<size_t>(2ULL)));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘]]’"sv)),((((*this).current())).span())));
}

}
}

JaktInternal::Optional<parser::ParsedAttribute> parser::Parser::parse_attribute() {
{
utility::Span const span = ((((*this).current())).span());
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, JaktInternal::Optional<parser::ParsedAttribute>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_9; {
((((*this).index)++));
__jakt_var_9 = name; goto __jakt_label_4;

}
__jakt_label_4:; __jakt_var_9.release_value(); }));
};/*case end*/
case 99 /* This */: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_10; {
((((*this).index)++));
__jakt_var_10 = (ByteString::from_utf8_without_validation("this"sv)); goto __jakt_label_5;

}
__jakt_label_5:; __jakt_var_10.release_value(); }));
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected identifier"sv)),((((*this).current())).span())));
((((*this).index)++));
return JaktInternal::OptionalNone();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<parser::ParsedAttributeArgument> arguments = DynamicArray<parser::ParsedAttributeArgument>::create_with({});
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
((((*this).index)++));
while (((!(((*this).eof()))) && (!(((((*this).current())).__jakt_init_index() == 8 /* RParen */))))){
utility::Span const span = ((((*this).current())).span());
ByteString const argument_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, JaktInternal::Optional<parser::ParsedAttribute>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_11; {
((((*this).index)++));
__jakt_var_11 = name; goto __jakt_label_6;

}
__jakt_label_6:; __jakt_var_11.release_value(); }));
};/*case end*/
case 99 /* This */: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_12; {
((((*this).index)++));
__jakt_var_12 = (ByteString::from_utf8_without_validation("this"sv)); goto __jakt_label_7;

}
__jakt_label_7:; __jakt_var_12.release_value(); }));
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_13; {
((((*this).index)++));
__jakt_var_13 = quote; goto __jakt_label_8;

}
__jakt_label_8:; __jakt_var_13.release_value(); }));
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected identifier or string literal"sv)),((((*this).current())).span())));
return JaktInternal::OptionalNone();
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
JaktInternal::Optional<ByteString> argument_value = JaktInternal::OptionalNone();
if (((((*this).current())).__jakt_init_index() == 5 /* Colon */)){
((((*this).index)++));
(argument_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>, JaktInternal::Optional<parser::ParsedAttribute>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_14; {
((((*this).index)++));
__jakt_var_14 = name; goto __jakt_label_9;

}
__jakt_label_9:; __jakt_var_14.release_value(); }));
};/*case end*/
case 99 /* This */: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_15; {
((((*this).index)++));
__jakt_var_15 = (ByteString::from_utf8_without_validation("this"sv)); goto __jakt_label_10;

}
__jakt_label_10:; __jakt_var_15.release_value(); }));
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_16; {
((((*this).index)++));
__jakt_var_16 = quote; goto __jakt_label_11;

}
__jakt_label_11:; __jakt_var_16.release_value(); }));
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected identifier or string literal"sv)),((((*this).current())).span())));
return JaktInternal::OptionalNone();
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
}));
}
((arguments).push(parser::ParsedAttributeArgument(argument_name,span,argument_value)));
if (((((*this).current())).__jakt_init_index() == 52 /* Comma */)){
((((*this).index)++));
}
else if ((!(((((*this).current())).__jakt_init_index() == 8 /* RParen */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘,’ or ‘)’"sv)),((((*this).current())).span())));
break;
}
}
if (((((*this).current())).__jakt_init_index() == 8 /* RParen */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘)’"sv)),((((*this).current())).span())));
}

}
JaktInternal::Optional<ByteString> assigned_value = JaktInternal::OptionalNone();
if (((((*this).current())).__jakt_init_index() == 16 /* Equal */)){
((((*this).index)++));
(assigned_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>, JaktInternal::Optional<parser::ParsedAttribute>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_17; {
((((*this).index)++));
__jakt_var_17 = static_cast<JaktInternal::Optional<ByteString>>(name); goto __jakt_label_12;

}
__jakt_label_12:; __jakt_var_17.release_value(); }));
};/*case end*/
case 99 /* This */: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_18; {
((((*this).index)++));
__jakt_var_18 = (ByteString::from_utf8_without_validation("this"sv)); goto __jakt_label_13;

}
__jakt_label_13:; __jakt_var_18.release_value(); }));
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_19; {
((((*this).index)++));
__jakt_var_19 = static_cast<JaktInternal::Optional<ByteString>>(quote); goto __jakt_label_14;

}
__jakt_label_14:; __jakt_var_19.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_20; {
((*this).error((ByteString::from_utf8_without_validation("Expected identifier or string literal"sv)),((((*this).current())).span())));
__jakt_var_20 = JaktInternal::OptionalNone(); goto __jakt_label_15;

}
__jakt_label_15:; __jakt_var_20; }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
return parser::ParsedAttribute(name,span,assigned_value,arguments);
}
}

parser::ParsedAlias parser::Parser::parse_using() {
{
parser::ParsedAlias alias = parser::ParsedAlias(JaktInternal::OptionalNone(),DynamicArray<parser::ParsedNameWithGenericParameters>::create_with({}));
for (;;){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedAlias>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 61 /* As */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 56 /* Eof */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* ColonColon */: {
{
((((*this).index)++));
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
parser::ParsedNameWithGenericParameters parsed_name = parser::ParsedNameWithGenericParameters(name,span,DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({}));
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 28 /* LessThan */)){
((((*this).index)++));
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedAlias>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* GreaterThan */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
{
((*this).inject_token(lexer::Token::GreaterThan(((((*this).current())).span()))));
((((*this).index)) += (static_cast<size_t>(1ULL)));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
size_t const index_before = ((*this).index);
NonnullRefPtr<typename parser::ParsedType> const inner_type = ((*this).parse_typename());
if (((index_before) == (((*this).index)))){
((*this).error((ByteString::from_utf8_without_validation("Expected type name"sv)),((((*this).current())).span())));
return JaktInternal::LoopBreak{};
}
((((parsed_name).generic_parameters)).push(inner_type));
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
((((alias).target)).push(parsed_name));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Semicolon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Semicolon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* Colon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Colon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7 /* LParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LParen;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RParen;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LCurly;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RCurly;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LSquare;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* RSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RSquare;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* PercentSign */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSign;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* Plus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Plus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15 /* Minus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Minus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* Equal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Equal;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* PlusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* PlusPlus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusPlus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* MinusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* MinusMinus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusMinus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* AsteriskEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AsteriskEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* ForwardSlashEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlashEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* PercentSignEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSignEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* NotEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NotEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* DoubleEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DoubleEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* GreaterThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThan;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThanOrEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* LessThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThan;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* LessThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThanOrEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* LeftArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftArithmeticShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31 /* LeftShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32 /* LeftShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShiftEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34 /* RightArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightArithmeticShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35 /* RightShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShiftEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36 /* Asterisk */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Asterisk;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 37 /* Ampersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Ampersand;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 38 /* AmpersandEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 39 /* AmpersandAmpersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandAmpersand;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40 /* Pipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Pipe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41 /* PipeEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipeEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 42 /* PipePipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipePipe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 43 /* Caret */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Caret;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44 /* CaretEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CaretEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 45 /* Dollar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dollar;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 46 /* Tilde */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Tilde;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 47 /* ForwardSlash */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlash;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 48 /* ExclamationPoint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ExclamationPoint;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 49 /* QuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMark;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMark;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMarkEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comma;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 54 /* DotDot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DotDot;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 57 /* FatArrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.FatArrow;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 58 /* Arrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Arrow;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59 /* And */: {
auto&& __jakt_match_value = __jakt_match_variant.as.And;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60 /* Anon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Anon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boxed;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 63 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 64 /* Catch */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Catch;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 66 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 67 /* Cpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Cpp;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 68 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 69 /* Destructor */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Destructor;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 70 /* Else */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Else;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 72 /* Extern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Extern;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 73 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 74 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fn;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 77 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 78 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79 /* Relative */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Relative;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80 /* In */: {
auto&& __jakt_match_value = __jakt_match_variant.as.In;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 81 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 82 /* Let */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Let;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 83 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 84 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 85 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 86 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 88 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 89 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 93 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 94 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 95 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 97 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 100 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 101 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 102 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 103 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 104 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 106 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 107 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 108 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 109 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 110 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 111 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 112 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 113 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
return JaktInternal::LoopBreak{};
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
if (((((*this).previous())).__jakt_init_index() == 6 /* ColonColon */)){
utility::Span const span = (((*this).previous())).as.ColonColon.value;
((*this).error((ByteString::from_utf8_without_validation("Expected alias target name"sv)),span));
}
if (((((*this).current())).__jakt_init_index() == 61 /* As */)){
((((*this).index)++));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedAlias>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
(((alias).alias_name) = parser::ParsedName(name,span));
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Semicolon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Semicolon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* Colon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Colon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* ColonColon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ColonColon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7 /* LParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LParen;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RParen;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LCurly;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RCurly;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LSquare;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* RSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RSquare;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* PercentSign */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSign;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* Plus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Plus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15 /* Minus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Minus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* Equal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Equal;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* PlusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* PlusPlus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusPlus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* MinusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* MinusMinus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusMinus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* AsteriskEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AsteriskEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* ForwardSlashEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlashEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* PercentSignEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSignEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* NotEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NotEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* DoubleEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DoubleEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* GreaterThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThan;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThanOrEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* LessThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThan;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* LessThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThanOrEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* LeftArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftArithmeticShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31 /* LeftShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32 /* LeftShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShiftEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34 /* RightArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightArithmeticShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35 /* RightShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShiftEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36 /* Asterisk */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Asterisk;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 37 /* Ampersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Ampersand;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 38 /* AmpersandEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 39 /* AmpersandAmpersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandAmpersand;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40 /* Pipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Pipe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41 /* PipeEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipeEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 42 /* PipePipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipePipe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 43 /* Caret */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Caret;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44 /* CaretEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CaretEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 45 /* Dollar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dollar;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 46 /* Tilde */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Tilde;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 47 /* ForwardSlash */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlash;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 48 /* ExclamationPoint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ExclamationPoint;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 49 /* QuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMark;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMark;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMarkEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comma;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 54 /* DotDot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DotDot;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 56 /* Eof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eof;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 57 /* FatArrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.FatArrow;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 58 /* Arrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Arrow;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59 /* And */: {
auto&& __jakt_match_value = __jakt_match_variant.as.And;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60 /* Anon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Anon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 61 /* As */: {
auto&& __jakt_match_value = __jakt_match_variant.as.As;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boxed;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 63 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 64 /* Catch */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Catch;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 66 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 67 /* Cpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Cpp;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 68 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 69 /* Destructor */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Destructor;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 70 /* Else */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Else;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 72 /* Extern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Extern;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 73 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 74 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fn;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 77 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 78 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79 /* Relative */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Relative;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80 /* In */: {
auto&& __jakt_match_value = __jakt_match_variant.as.In;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 81 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 82 /* Let */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Let;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 83 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 84 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 85 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 86 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 88 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 89 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 93 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 94 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 95 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 97 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 100 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 101 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 102 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 103 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 104 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 106 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 107 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 108 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 109 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 110 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 111 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 112 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 113 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected alias name"sv)),span));
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
}
return alias;
}
}

parser::ParsedExternalTraitImplementation parser::Parser::parse_external_trait_implementation() {
{
NonnullRefPtr<typename parser::ParsedType> const type_name = ((*this).parse_typename());
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 110 /* Implements */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘implements’"sv)),((((*this).current())).span())));
}

JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> const trait_list = ((*this).parse_trait_list());
if ((!(((trait_list).has_value())))){
((*this).error((ByteString::from_utf8_without_validation("Expected non-empty trait list"sv)),((((*this).current())).span())));
return parser::ParsedExternalTraitImplementation(type_name,DynamicArray<parser::ParsedNameWithGenericParameters>::create_with({}),DynamicArray<parser::ParsedMethod>::create_with({}));
}
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>> const fields_methods_records_ = ((*this).parse_struct_class_body(parser::DefinitionLinkage::Internal(),parser::Visibility::Public(),false));
JaktInternal::DynamicArray<parser::ParsedField> const fields = ((fields_methods_records_).template get<0>());
JaktInternal::DynamicArray<parser::ParsedMethod> const methods = ((fields_methods_records_).template get<1>());
JaktInternal::DynamicArray<parser::ParsedRecord> const records = ((fields_methods_records_).template get<2>());

if ((!(((records).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("External trait implementations cannot have nested records"sv)),((((records)[static_cast<i64>(0LL)])).name_span)));
}
if ((!(((fields).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("External trait implementations cannot have fields"sv)),((((((fields)[static_cast<i64>(0LL)])).var_decl)).span)));
}
return parser::ParsedExternalTraitImplementation(type_name,(trait_list.value()),methods);
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘{’"sv)),((((*this).current())).span())));
return parser::ParsedExternalTraitImplementation(type_name,(trait_list.value()),DynamicArray<parser::ParsedMethod>::create_with({}));
}

}
}

parser::ParsedTrait parser::Parser::parse_trait() {
{
parser::ParsedTrait parsed_trait = parser::ParsedTrait((ByteString::from_utf8_without_validation(""sv)),((*this).empty_span()),DynamicArray<parser::ParsedGenericParameter>::create_with({}),parser::ParsedTraitRequirements::Nothing());
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const name_span = (((*this).current())).as.Identifier.span;
(((parsed_trait).name) = name);
(((parsed_trait).name_span) = name_span);
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 28 /* LessThan */)){
(((parsed_trait).generic_parameters) = ((*this).parse_generic_parameters()));
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedTrait>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LCurly */: {
{
((((*this).index)++));
JaktInternal::DynamicArray<parser::ParsedFunction> methods = DynamicArray<parser::ParsedFunction>::create_with({});
JaktInternal::DynamicArray<parser::ParsedAttribute> active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({});
for (;;){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedTrait>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 56 /* Eof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eof;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected '}' to close the trait body"sv)),span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
{
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 11 /* LSquare */)){
((((*this).index)) += (static_cast<size_t>(2ULL)));
((*this).parse_attribute_list(((active_attributes))));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Unexpected token (expected ‘[[’)"sv)),((((*this).current())).span())));
((((*this).index)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
{
parser::ParsedFunction method = ((*this).parse_function(parser::FunctionLinkage::Internal(),parser::Visibility::Public(),false,false,false,true));
if (((((((method).block)).stmts)).is_empty())){
(((method).linkage) = parser::FunctionLinkage::External());
}
((*this).apply_attributes(((method)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((methods).push(method));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;utility::Span const& span = __jakt_match_value.span;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;utility::Span const& span = __jakt_match_value.span;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;utility::Span const& span = __jakt_match_value.span;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;utility::Span const& span = __jakt_match_value.span;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Semicolon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Semicolon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* Colon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Colon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* ColonColon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ColonColon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7 /* LParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LParen;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RParen;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LCurly;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* RSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RSquare;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* PercentSign */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSign;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* Plus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Plus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15 /* Minus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Minus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* Equal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Equal;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* PlusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* PlusPlus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusPlus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* MinusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* MinusMinus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusMinus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* AsteriskEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AsteriskEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* ForwardSlashEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlashEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* PercentSignEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSignEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* NotEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NotEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* DoubleEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DoubleEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* GreaterThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThan;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThanOrEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* LessThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThan;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* LessThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThanOrEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* LeftArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftArithmeticShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31 /* LeftShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32 /* LeftShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShiftEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34 /* RightArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightArithmeticShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35 /* RightShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShiftEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36 /* Asterisk */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Asterisk;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 37 /* Ampersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Ampersand;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 38 /* AmpersandEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 39 /* AmpersandAmpersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandAmpersand;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40 /* Pipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Pipe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41 /* PipeEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipeEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 42 /* PipePipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipePipe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 43 /* Caret */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Caret;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44 /* CaretEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CaretEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 45 /* Dollar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dollar;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 46 /* Tilde */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Tilde;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 47 /* ForwardSlash */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlash;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 48 /* ExclamationPoint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ExclamationPoint;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 49 /* QuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMark;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMark;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMarkEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comma;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 54 /* DotDot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DotDot;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 57 /* FatArrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.FatArrow;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 58 /* Arrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Arrow;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59 /* And */: {
auto&& __jakt_match_value = __jakt_match_variant.as.And;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60 /* Anon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Anon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 61 /* As */: {
auto&& __jakt_match_value = __jakt_match_variant.as.As;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boxed;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 63 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 64 /* Catch */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Catch;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 66 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 67 /* Cpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Cpp;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 68 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 69 /* Destructor */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Destructor;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 70 /* Else */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Else;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 72 /* Extern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Extern;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 73 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 74 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 77 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 78 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79 /* Relative */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Relative;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80 /* In */: {
auto&& __jakt_match_value = __jakt_match_variant.as.In;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 81 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 82 /* Let */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Let;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 83 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 84 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 85 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 86 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 88 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 89 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 93 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 94 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 95 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 97 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 100 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 101 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 102 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 103 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 104 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 106 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 107 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 108 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 109 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 110 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 111 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 112 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;utility::Span const& span = __jakt_match_value.value;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 113 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.span;
{
((*this).error_with_hint((ByteString::from_utf8_without_validation("Expected 'function' keyword inside trait definition"sv)),span,__jakt_format((StringView::from_string_literal("Inside '{}' trait's definition only function declarations can appear"sv)),((parsed_trait).name)),((parsed_trait).name_span)));
return parsed_trait;
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
(((parsed_trait).requirements) = parser::ParsedTraitRequirements::Methods(methods));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* Equal */: {
{
((((*this).index)) += (static_cast<size_t>(1ULL)));
NonnullRefPtr<typename parser::ParsedExpression> const expression = ((*this).parse_expression(false,true));
(((parsed_trait).requirements) = parser::ParsedTraitRequirements::ComptimeExpression(expression));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected '{' to enter the body of the trait, or '=' to specify trait requirements"sv)),((((*this).current())).span())));
return parsed_trait;
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
return parsed_trait;
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),((((*this).current())).span())));
return parsed_trait;
}

}
}

parser::ParsedRecord parser::Parser::parse_record(parser::DefinitionLinkage const definition_linkage) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::ParsedRecord, parser::ParsedRecord>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 98 /* Struct */: {
return JaktInternal::ExplicitValue(((*this).parse_struct(definition_linkage)));
};/*case end*/
case 65 /* Class */: {
return JaktInternal::ExplicitValue(((*this).parse_class(definition_linkage)));
};/*case end*/
case 71 /* Enum */: {
return JaktInternal::ExplicitValue(((*this).parse_enum(definition_linkage,false)));
};/*case end*/
case 62 /* Boxed */: {
return JaktInternal::ExplicitValue(({ Optional<parser::ParsedRecord> __jakt_var_21; {
((((*this).index)++));
__jakt_var_21 = ((*this).parse_enum(definition_linkage,true)); goto __jakt_label_16;

}
__jakt_label_16:; __jakt_var_21.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<parser::ParsedRecord> __jakt_var_22; {
((*this).error((ByteString::from_utf8_without_validation("Expected `struct`, `class`, `enum`, or `boxed`"sv)),((((*this).current())).span())));
__jakt_var_22 = parser::ParsedRecord((ByteString::from_utf8_without_validation(""sv)),((*this).empty_span()),DynamicArray<parser::ParsedGenericParameter>::create_with({}),definition_linkage,JaktInternal::OptionalNone(),DynamicArray<parser::ParsedMethod>::create_with({}),parser::RecordType::Garbage(),DynamicArray<parser::ParsedRecord>::create_with({}),JaktInternal::OptionalNone()); goto __jakt_label_17;

}
__jakt_label_17:; __jakt_var_22.release_value(); }));
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

void parser::Parser::parse_import(parser::ParsedNamespace& parent) {
{
if (((((*this).current())).__jakt_init_index() == 72 /* Extern */)){
((((*this).index)++));
((((parent))).add_extern_import(((*this).parse_extern_import(parent))));
}
else {
((((parent))).add_module_import(((*this).parse_module_import())));
}

}
}

parser::ParsedExternImport parser::Parser::parse_extern_import(parser::ParsedNamespace& parent) {
{
parser::ParsedExternImport parsed_import = parser::ParsedExternImport(false,parser::ParsedNamespace(JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),DynamicArray<parser::ParsedFunction>::create_with({}),DynamicArray<parser::ParsedRecord>::create_with({}),DynamicArray<parser::ParsedTrait>::create_with({}),DynamicArray<parser::ParsedExternalTraitImplementation>::create_with({}),DynamicArray<parser::ParsedNamespace>::create_with({}),DynamicArray<parser::ParsedAlias>::create_with({}),DynamicArray<parser::ParsedModuleImport>::create_with({}),DynamicArray<parser::ParsedExternImport>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<parser::IncludeAction>::create_with({}),DynamicArray<parser::IncludeAction>::create_with({}),DynamicArray<JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedGenericParameter>,parser::ParsedNamespace>>::create_with({}),false,false),DynamicArray<parser::IncludeAction>::create_with({}),DynamicArray<parser::IncludeAction>::create_with({}),false);
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const span = (((*this).current())).as.Identifier.span;
((((*this).index)++));
if ((((name) == ((ByteString::from_utf8_without_validation("c"sv)))) || ((name) == ((ByteString::from_utf8_without_validation("C"sv)))))){
(((parsed_import).is_c) = true);
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected 'c' or path after `import extern`"sv)),((((*this).current())).span())));
}

}
(((((parsed_import).assigned_namespace)).name_span) = ((((*this).current())).span()));
ByteString const import_path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, parser::ParsedExternImport>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_23; {
((((*this).index)++));
__jakt_var_23 = quote; goto __jakt_label_18;

}
__jakt_label_18:; __jakt_var_23.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_24; {
((*this).error((ByteString::from_utf8_without_validation("Expected path after `import extern`"sv)),((((*this).current())).span())));
__jakt_var_24 = (ByteString::from_utf8_without_validation(""sv)); goto __jakt_label_19;

}
__jakt_label_19:; __jakt_var_24.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((((*this).current())).__jakt_init_index() == 61 /* As */)){
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const span = (((*this).current())).as.Identifier.span;
((((*this).index)++));
(((((parsed_import).assigned_namespace)).name) = name);
(((((parsed_import).assigned_namespace)).name_span) = span);
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected name after 'as' keyword to name the extern import"sv)),((((*this).current())).span())));
}

}
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
(((parsed_import).assigned_namespace) = ((*this).parse_namespace(false)));
(((((parsed_import).assigned_namespace)).import_path_if_extern) = static_cast<JaktInternal::Optional<ByteString>>(import_path));
(((((parsed_import).assigned_namespace)).generating_import_extern_before_include) = ((parsed_import).before_include));
(((((parsed_import).assigned_namespace)).generating_import_extern_after_include) = ((parsed_import).after_include));
if (((((*this).current())).__jakt_init_index() == 10 /* RCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '}' to end namespace for the extern import"sv)),((((*this).current())).span())));
}

}
else {
(((parsed_import).should_auto_import) = true);
(((((parsed_import).assigned_namespace)).import_path_if_extern) = static_cast<JaktInternal::Optional<ByteString>>(import_path));
(((((parsed_import).assigned_namespace)).generating_import_extern_before_include) = ((parsed_import).before_include));
(((((parsed_import).assigned_namespace)).generating_import_extern_after_include) = ((parsed_import).after_include));
(((((parsed_import).assigned_namespace)).is_auto_extern_imported) = true);
}

((((parent))).add_child_namespace(((parsed_import).assigned_namespace)));
for (;;){
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,parser::ParsedExternImport> {
auto __jakt_enum_value = (name);
if (__jakt_enum_value == "before_include"sv) {
{
((((*this).index)++));
JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>> const actions = ((*this).parse_include_action());
if (((actions).has_value())){
((((parsed_import).before_include)).push_values((((actions.value())))));
}
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "after_include"sv) {
{
((((*this).index)++));
JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>> const actions = ((*this).parse_include_action());
if (((actions).has_value())){
((((parsed_import).after_include)).push_values((((actions.value())))));
}
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
}
else {
break;
}

}
return parsed_import;
}
}

JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>> parser::Parser::parse_include_action() {
{
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>>> {
auto __jakt_enum_value = (name);
if (__jakt_enum_value == "define"sv) {
{
((((*this).index)++));
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
((*this).skip_newlines());
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '{' to start define action"sv)),((((*this).current())).span())));
return JaktInternal::OptionalNone();
}

JaktInternal::DynamicArray<parser::IncludeAction> defines = DynamicArray<parser::IncludeAction>::create_with({});
for (;;){
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const span = ((((*this).current())).span());
((((*this).index)++));
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 16 /* Equal */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '=' to assign value to defined symbols"sv)),((((*this).current())).span())));
continue;
}

ByteString const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& quote = __jakt_match_value.quote;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_25; {
((((*this).index)++));
__jakt_var_25 = quote; goto __jakt_label_20;

}
__jakt_label_20:; __jakt_var_25.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_26; {
((*this).error((ByteString::from_utf8_without_validation("Expected quoted string to assign value to defined symbols"sv)),((((*this).current())).span())));
__jakt_var_26 = (ByteString::from_utf8_without_validation(""sv)); goto __jakt_label_21;

}
__jakt_label_21:; __jakt_var_26.release_value(); }));
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
((defines).push(parser::IncludeAction::Define(name,span,value)));
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 52 /* Comma */)){
((((*this).index)++));
((*this).skip_newlines());
}
}
else {
break;
}

}
if (((((*this).current())).__jakt_init_index() == 10 /* RCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '}' to end define action"sv)),((((*this).current())).span())));
}

return static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>>>(defines);
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "undefine"sv) {
{
((((*this).index)++));
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
((*this).skip_newlines());
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '{' to start undefine include action"sv)),((((*this).current())).span())));
return JaktInternal::OptionalNone();
}

JaktInternal::DynamicArray<parser::IncludeAction> defines = DynamicArray<parser::IncludeAction>::create_with({});
for (;;){
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const span = ((((*this).current())).span());
((((*this).index)++));
((defines).push(parser::IncludeAction::Undefine(name,span)));
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 52 /* Comma */)){
((((*this).index)++));
((*this).skip_newlines());
}
}
else {
break;
}

}
if (((((*this).current())).__jakt_init_index() == 10 /* RCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '}' to end undefine action"sv)),((((*this).current())).span())));
}

return static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<parser::IncludeAction>>>(defines);
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((*this).error((ByteString::from_utf8_without_validation("Expected 'define' or 'undefine' in include action"sv)),((((*this).current())).span())));
return JaktInternal::OptionalNone();
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected 'define' or 'undefine' in include action"sv)),((((*this).current())).span())));
return JaktInternal::OptionalNone();
}

}
}

parser::ParsedModuleImport parser::Parser::parse_module_import() {
{
parser::ParsedModuleImport parsed_import = parser::ParsedModuleImport(parser::ImportName::Literal((ByteString::from_utf8_without_validation(""sv)),((*this).empty_span())),JaktInternal::OptionalNone(),parser::ImportList::List(DynamicArray<parser::ImportName>::create_with({})),false,static_cast<size_t>(0ULL));
if (((((*this).current())).__jakt_init_index() == 79 /* Relative */)){
(((parsed_import).relative_path) = true);
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
if (((name) == ((ByteString::from_utf8_without_validation("parent"sv))))){
((((*this).index)++));
((((parsed_import).parent_path_count)++));
while (((((*this).current())).__jakt_init_index() == 6 /* ColonColon */)){
((((*this).index)++));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedModuleImport>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(name,(ByteString::from_utf8_without_validation("parent"sv)))){
return JaktInternal::LoopBreak{};
}
((((*this).index)++));
((((parsed_import).parent_path_count)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
return JaktInternal::LoopBreak{};
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
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
((((*this).index)++));
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedModuleImport>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;lexer::LiteralPrefix const& prefix = __jakt_match_value.prefix;
ByteString const& number = __jakt_match_value.number;
lexer::LiteralSuffix const& suffix = __jakt_match_value.suffix;
utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename parser::ParsedExpression> const numeric_constant = ((*this).parse_number(prefix,number,suffix,span));
if (((numeric_constant)->__jakt_init_index() == 1 /* NumericConstant */)){
parser::NumericConstant const val = (numeric_constant)->as.NumericConstant.val;
(((parsed_import).parent_path_count) = ((val).to_usize()));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Invalid Numeric Constant"sv)),span));
return JaktInternal::LoopBreak{};
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error(__jakt_format((StringView::from_string_literal("Incomplete relative import defintion, `)`; got ‘{}’"sv)),((*this).current())),((((*this).current())).span())));
return parsed_import;
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
if (((((*this).current())).__jakt_init_index() == 6 /* ColonColon */)){
((((*this).index)++));
}
else {
((*this).error(__jakt_format((StringView::from_string_literal("Expected `::` after {}, got ‘{}’"sv)),((*this).previous()),((*this).current())),((((*this).current())).span())));
return parsed_import;
}

}
}
}
}
(((parsed_import).module_name) = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::ImportName, parser::ParsedModuleImport>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::ImportName, parser::ParsedModuleImport>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<size_t>(1ULL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(({ Optional<parser::ImportName> __jakt_var_27; {
bool const previous_can_have_trailing_closure = ((*this).can_have_trailing_closure);
(((*this).can_have_trailing_closure) = false);
NonnullRefPtr<typename parser::ParsedExpression> const expression = parser::ParsedExpression::Call((((*this).parse_call()).value()),span);
(((*this).can_have_trailing_closure) = previous_can_have_trailing_closure);
((((*this).index)--));
__jakt_var_27 = parser::ImportName::Comptime(expression); goto __jakt_label_22;

}
__jakt_label_22:; __jakt_var_27.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(parser::ImportName::Literal(name,span));
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
((*this).error((ByteString::from_utf8_without_validation("Expected module name"sv)),((((*this).current())).span())));
return parsed_import;
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
((((*this).index)++));
if (((*this).eol())){
return parsed_import;
}
if ((!(((((*this).current())).__jakt_init_index() == 9 /* LCurly */)))){
ByteString module_name = ((((parsed_import).module_name)).literal_name());
utility::Span module_span = ((((parsed_import).module_name)).span());
while (((((*this).current())).__jakt_init_index() == 6 /* ColonColon */)){
((((*this).index)++));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(module_name,(ByteString::from_utf8_without_validation("::"sv)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedModuleImport>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(module_name,name);
(module_span = parser::merge_spans(module_span,span));
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 61 /* As */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected module name fragment"sv)),((((*this).current())).span())));
return parsed_import;
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
(((parsed_import).module_name) = parser::ImportName::Literal(module_name,module_span));
}
if (((((*this).current())).__jakt_init_index() == 61 /* As */)){
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const span = (((*this).current())).as.Identifier.span;
((((*this).index)++));
(((parsed_import).alias_name) = parser::ImportName::Literal(name,span));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected name"sv)),((((*this).current())).span())));
((((*this).index)++));
}

}
if (((*this).eol())){
return parsed_import;
}
if ((!(((((*this).current())).__jakt_init_index() == 9 /* LCurly */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected '{'"sv)),((((*this).current())).span())));
}
((((*this).index)++));
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedModuleImport>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (((((parsed_import).import_list)).__jakt_init_index() == 0 /* List */)){
JaktInternal::DynamicArray<parser::ImportName> const names = (((parsed_import).import_list)).as.List.value;
JaktInternal::DynamicArray<parser::ImportName> mutable_names = names;
((mutable_names).push(parser::ImportName::Literal(name,span)));
}
else {
((*this).error_with_hint(__jakt_format((StringView::from_string_literal("Already importing everything from '{}'"sv)),((((parsed_import).module_name)).literal_name())),((((*this).current())).span()),(ByteString::from_utf8_without_validation("Remove the '*' to import specific names"sv)),((((*this).current())).span())));
}

((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36 /* Asterisk */: {
{
if (((((parsed_import).import_list)).__jakt_init_index() == 0 /* List */)){
JaktInternal::DynamicArray<parser::ImportName> const names = (((parsed_import).import_list)).as.List.value;
if (((names).is_empty())){
(((parsed_import).import_list) = parser::ImportList::All());
}
else {
if (((((parsed_import).import_list)).__jakt_init_index() == 1 /* All */)){
((*this).error(__jakt_format((StringView::from_string_literal("Cannot repeat '*' in import list for '{}'"sv)),((((parsed_import).module_name)).literal_name())),((((*this).current())).span())));
}
else {
((*this).error(__jakt_format((StringView::from_string_literal("Cannot mix '*' and specific names in import list for '{}'"sv)),((((parsed_import).module_name)).literal_name())),((((*this).current())).span())));
}

}

}
else {
if (((((parsed_import).import_list)).__jakt_init_index() == 1 /* All */)){
((*this).error(__jakt_format((StringView::from_string_literal("Cannot repeat '*' in import list for '{}'"sv)),((((parsed_import).module_name)).literal_name())),((((*this).current())).span())));
}
else {
((*this).error(__jakt_format((StringView::from_string_literal("Cannot mix '*' and specific names in import list for '{}'"sv)),((((parsed_import).module_name)).literal_name())),((((*this).current())).span())));
}

}

((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected import symbol"sv)),((((*this).current())).span())));
((((*this).index)++));
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
return parsed_import;
}
}

JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ValueEnumVariant>,JaktInternal::DynamicArray<parser::ParsedMethod>> parser::Parser::parse_value_enum_body(parser::ParsedRecord const partial_enum,parser::DefinitionLinkage const definition_linkage) {
{
JaktInternal::DynamicArray<parser::ParsedMethod> methods = DynamicArray<parser::ParsedMethod>::create_with({});
JaktInternal::DynamicArray<parser::ValueEnumVariant> variants = DynamicArray<parser::ValueEnumVariant>::create_with({});
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected `{` to start the enum body"sv)),((((*this).current())).span())));
}

((*this).skip_newlines());
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete enum definition, expected variant name"sv)),((((*this).previous())).span())));
return (Tuple{variants, methods});
}
JaktInternal::Optional<parser::Visibility> last_visibility = JaktInternal::OptionalNone();
JaktInternal::Optional<utility::Span> last_visibility_span = JaktInternal::OptionalNone();
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ValueEnumVariant>,JaktInternal::DynamicArray<parser::ParsedMethod>>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 16 /* Equal */)){
((((*this).index)) += (static_cast<size_t>(2ULL)));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
((variants).push(parser::ValueEnumVariant(name,span,expr)));
}
else {
((((*this).index)++));
((variants).push(parser::ValueEnumVariant(name,span,JaktInternal::OptionalNone())));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
{
if (((last_visibility).has_value())){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Multiple visibility modifiers on one field or method are not allowed"sv)),span,(ByteString::from_utf8_without_validation("Previous modifier is here"sv)),(last_visibility_span.value())));
}
(last_visibility = parser::Visibility::Private());
(last_visibility_span = span);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
{
if (((last_visibility).has_value())){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Multiple visibility modifiers on one field or method are not allowed"sv)),span,(ByteString::from_utf8_without_validation("Previous modifier is here"sv)),(last_visibility_span.value())));
}
(last_visibility = parser::Visibility::Public());
(last_visibility_span = span);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
{
bool const is_comptime = ((((*this).current())).__jakt_init_index() == 76 /* Comptime */);
parser::FunctionLinkage const function_linkage = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ValueEnumVariant>,JaktInternal::DynamicArray<parser::ParsedMethod>>>{
auto&& __jakt_match_variant = definition_linkage;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Internal */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::Internal());
};/*case end*/
case 1 /* External */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
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
});
if ((((function_linkage).__jakt_init_index() == 1 /* External */) && is_comptime)){
((*this).error((ByteString::from_utf8_without_validation("External functions cannot be comptime"sv)),((((*this).current())).span())));
}
parser::Visibility const visibility = last_visibility.value_or_lazy_evaluated([&] { return parser::Visibility::Public(); });
(last_visibility = JaktInternal::OptionalNone());
(last_visibility_span = JaktInternal::OptionalNone());
parser::ParsedMethod const parsed_method = ((*this).parse_method(function_linkage,visibility,false,false,is_comptime,false,false));
((methods).push(parsed_method));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
{
bool const is_comptime = ((((*this).current())).__jakt_init_index() == 76 /* Comptime */);
parser::FunctionLinkage const function_linkage = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ValueEnumVariant>,JaktInternal::DynamicArray<parser::ParsedMethod>>>{
auto&& __jakt_match_variant = definition_linkage;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Internal */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::Internal());
};/*case end*/
case 1 /* External */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
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
});
if ((((function_linkage).__jakt_init_index() == 1 /* External */) && is_comptime)){
((*this).error((ByteString::from_utf8_without_validation("External functions cannot be comptime"sv)),((((*this).current())).span())));
}
parser::Visibility const visibility = last_visibility.value_or_lazy_evaluated([&] { return parser::Visibility::Public(); });
(last_visibility = JaktInternal::OptionalNone());
(last_visibility_span = JaktInternal::OptionalNone());
parser::ParsedMethod const parsed_method = ((*this).parse_method(function_linkage,visibility,false,false,is_comptime,false,false));
((methods).push(parsed_method));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected identifier or the end of enum block"sv)),((((*this).current())).span())));
((((*this).index)++));
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
if ((!(((((*this).current())).__jakt_init_index() == 10 /* RCurly */)))){
((*this).error((ByteString::from_utf8_without_validation("Invalid enum definition, expected `}`"sv)),((((*this).current())).span())));
return (Tuple{variants, methods});
}
((((*this).index)++));
if (((variants).is_empty())){
((*this).error((ByteString::from_utf8_without_validation("Empty enums are not allowed"sv)),((partial_enum).name_span)));
}
return (Tuple{variants, methods});
}
}

JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>> parser::Parser::parse_sum_enum_body(parser::ParsedRecord const partial_enum,parser::DefinitionLinkage const definition_linkage,bool const is_boxed) {
{
JaktInternal::DynamicArray<parser::ParsedMethod> methods = DynamicArray<parser::ParsedMethod>::create_with({});
JaktInternal::DynamicArray<parser::SumEnumVariant> variants = DynamicArray<parser::SumEnumVariant>::create_with({});
JaktInternal::DynamicArray<parser::ParsedField> fields = DynamicArray<parser::ParsedField>::create_with({});
JaktInternal::DynamicArray<parser::ParsedRecord> records = DynamicArray<parser::ParsedRecord>::create_with({});
bool seen_a_variant = false;
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected `{` to start the enum body"sv)),((((*this).current())).span())));
}

((*this).skip_newlines());
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete enum definition, expected variant or field name"sv)),((((*this).previous())).span())));
return (Tuple{variants, fields, methods, records});
}
JaktInternal::Optional<parser::Visibility> last_visibility = JaktInternal::OptionalNone();
JaktInternal::Optional<utility::Span> last_visibility_span = JaktInternal::OptionalNone();
bool last_extern = false;
JaktInternal::DynamicArray<parser::ParsedAttribute> active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({});
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 72 /* Extern */: {
{
if (last_extern){
((*this).error((ByteString::from_utf8_without_validation("Multiple extern modifiers are not allowed"sv)),((((*this).current())).span())));
}
(last_extern = true);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (last_extern){
((*this).error((ByteString::from_utf8_without_validation("An enum variant or common field cannot be extern"sv)),span));
(last_extern = false);
}
if ((!(((active_attributes).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("An enum variant or common field cannot have attributes"sv)),span));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
}
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 5 /* Colon */)){
parser::ParsedField const field = ((*this).parse_field(last_visibility.value_or_lazy_evaluated([&] { return parser::Visibility::Public(); })));
if (seen_a_variant){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Common enum fields must be declared before variants"sv)),span,(ByteString::from_utf8_without_validation("Previous variant is here"sv)),(((((variants).last()).value())).span)));
}
else {
((fields).push(field));
}

return JaktInternal::LoopContinue{};
}
(seen_a_variant = true);
if ((!(((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 7 /* LParen */)))){
((((*this).index)++));
((variants).push(parser::SumEnumVariant(name,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
return JaktInternal::LoopContinue{};
}
((((*this).index)) += (static_cast<size_t>(2ULL)));
JaktInternal::DynamicArray<parser::ParsedVarDecl> var_decls = DynamicArray<parser::ParsedVarDecl>::create_with({});
JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>>> default_values = DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>>>::create_with({});
while ((!(((*this).eof())))){
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 5 /* Colon */)){
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
parser::ParsedVarDecl var_decl = ((*this).parse_variable_declaration(false));
if (((((var_decl).parsed_type))->__jakt_init_index() == 0 /* Name */)){
ByteString const name = (((var_decl).parsed_type))->as.Name.name;
utility::Span const span = (((var_decl).parsed_type))->as.Name.span;
(((var_decl).inlay_span) = span);
if ((((name) == (((partial_enum).name))) && (!(is_boxed)))){
((*this).error((ByteString::from_utf8_without_validation("use 'boxed enum' to make the enum recursive"sv)),((var_decl).span)));
}
}
((var_decls).push(var_decl));
continue;
}
else {
((*this).error((ByteString::from_utf8_without_validation("Enum variant missing type"sv)),((((*this).current())).span())));
((((*this).index)++));
continue;
}

}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
{
((var_decls).push(parser::ParsedVarDecl((ByteString::from_utf8_without_validation(""sv)),((*this).parse_typename()),false,JaktInternal::OptionalNone(),((((*this).current())).span()),JaktInternal::OptionalNone())));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
{
((var_decls).push(parser::ParsedVarDecl((ByteString::from_utf8_without_validation(""sv)),((*this).parse_typename()),false,JaktInternal::OptionalNone(),((((*this).current())).span()),JaktInternal::OptionalNone())));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
{
((var_decls).push(parser::ParsedVarDecl((ByteString::from_utf8_without_validation(""sv)),((*this).parse_typename()),false,JaktInternal::OptionalNone(),((((*this).current())).span()),JaktInternal::OptionalNone())));
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
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* Equal */: {
{
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const default_value = ((*this).parse_expression(false,false));
((default_values).push(static_cast<JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>>>(default_value)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((default_values).push(JaktInternal::OptionalNone()));
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
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error(__jakt_format((StringView::from_string_literal("Incomplete enum variant definition, expected `,` or `)`; got ‘{}’"sv)),((*this).current())),((((*this).current())).span())));
return JaktInternal::LoopBreak{};
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
((variants).push(parser::SumEnumVariant(name,span,var_decls,default_values)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
{
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 11 /* LSquare */)){
((((*this).index)) += (static_cast<size_t>(2ULL)));
((*this).parse_attribute_list(((active_attributes))));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Unexpected token (expected ‘[[’)"sv)),((((*this).current())).span())));
((((*this).index)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
{
if (((last_visibility).has_value())){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Multiple visibility modifiers on one field or method are not allowed"sv)),span,(ByteString::from_utf8_without_validation("Previous modifier is here"sv)),(last_visibility_span.value())));
}
(last_visibility = parser::Visibility::Private());
(last_visibility_span = span);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
{
if (((last_visibility).has_value())){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Multiple visibility modifiers on one field or method are not allowed"sv)),span,(ByteString::from_utf8_without_validation("Previous modifier is here"sv)),(last_visibility_span.value())));
}
(last_visibility = parser::Visibility::Public());
(last_visibility_span = span);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
{
bool const is_comptime = ((((*this).current())).__jakt_init_index() == 76 /* Comptime */);
parser::FunctionLinkage const function_linkage = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = definition_linkage;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Internal */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::Internal());
};/*case end*/
case 1 /* External */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
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
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
if ((((function_linkage).__jakt_init_index() == 1 /* External */) && is_comptime)){
((*this).error((ByteString::from_utf8_without_validation("External functions cannot be comptime"sv)),((((*this).current())).span())));
}
parser::Visibility const visibility = last_visibility.value_or_lazy_evaluated([&] { return parser::Visibility::Public(); });
(last_visibility = JaktInternal::OptionalNone());
(last_visibility_span = JaktInternal::OptionalNone());
parser::ParsedMethod parsed_method = ((*this).parse_method(function_linkage,visibility,false,false,is_comptime,false,false));
((*this).apply_attributes(((parsed_method)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((methods).push(parsed_method));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
{
bool const is_comptime = ((((*this).current())).__jakt_init_index() == 76 /* Comptime */);
parser::FunctionLinkage const function_linkage = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = definition_linkage;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Internal */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::Internal());
};/*case end*/
case 1 /* External */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
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
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
if ((((function_linkage).__jakt_init_index() == 1 /* External */) && is_comptime)){
((*this).error((ByteString::from_utf8_without_validation("External functions cannot be comptime"sv)),((((*this).current())).span())));
}
parser::Visibility const visibility = last_visibility.value_or_lazy_evaluated([&] { return parser::Visibility::Public(); });
(last_visibility = JaktInternal::OptionalNone());
(last_visibility_span = JaktInternal::OptionalNone());
parser::ParsedMethod parsed_method = ((*this).parse_method(function_linkage,visibility,false,false,is_comptime,false,false));
((*this).apply_attributes(((parsed_method)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((methods).push(parsed_method));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
{
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot have visibility modifiers"sv)),((((*this).current())).span())));
(last_visibility = JaktInternal::OptionalNone());
}
parser::ParsedRecord parsed_record = ((*this).parse_record(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::DefinitionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::DefinitionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(definition_linkage);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
})));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((records).push(parsed_record));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
{
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot have visibility modifiers"sv)),((((*this).current())).span())));
(last_visibility = JaktInternal::OptionalNone());
}
parser::ParsedRecord parsed_record = ((*this).parse_record(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::DefinitionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::DefinitionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(definition_linkage);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
})));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((records).push(parsed_record));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
{
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot have visibility modifiers"sv)),((((*this).current())).span())));
(last_visibility = JaktInternal::OptionalNone());
}
parser::ParsedRecord parsed_record = ((*this).parse_record(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::DefinitionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::DefinitionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(definition_linkage);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
})));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((records).push(parsed_record));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
{
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot have visibility modifiers"sv)),((((*this).current())).span())));
(last_visibility = JaktInternal::OptionalNone());
}
parser::ParsedRecord parsed_record = ((*this).parse_record(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::DefinitionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::DefinitionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(definition_linkage);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
})));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((records).push(parsed_record));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected identifier or the end of enum block"sv)),((((*this).current())).span())));
((((*this).index)++));
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
if ((!(((((*this).current())).__jakt_init_index() == 10 /* RCurly */)))){
((*this).error((ByteString::from_utf8_without_validation("Invalid enum definition, expected `}`"sv)),((((*this).current())).span())));
return (Tuple{variants, fields, methods, records});
}
((((*this).index)++));
if (((variants).is_empty())){
((*this).error((ByteString::from_utf8_without_validation("Empty enums are not allowed"sv)),((partial_enum).name_span)));
}
return (Tuple{variants, fields, methods, records});
}
}

parser::ParsedRecord parser::Parser::parse_enum(parser::DefinitionLinkage const definition_linkage,bool const is_boxed) {
{
parser::ParsedRecord parsed_enum = parser::ParsedRecord((ByteString::from_utf8_without_validation(""sv)),((*this).empty_span()),DynamicArray<parser::ParsedGenericParameter>::create_with({}),definition_linkage,JaktInternal::OptionalNone(),DynamicArray<parser::ParsedMethod>::create_with({}),parser::RecordType::Garbage(),DynamicArray<parser::ParsedRecord>::create_with({}),JaktInternal::OptionalNone());
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> underlying_type = JaktInternal::OptionalNone();
if (((((*this).current())).__jakt_init_index() == 71 /* Enum */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘enum’ keyword"sv)),((((*this).current())).span())));
return parsed_enum;
}

if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete enum definition, expected name"sv)),((((*this).current())).span())));
return parsed_enum;
}
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const span = (((*this).current())).as.Identifier.span;
(((parsed_enum).name) = name);
(((parsed_enum).name_span) = span);
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Incomplete enum definition, expected name"sv)),((((*this).current())).span())));
}

if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete enum definition, expected generic parameters or underlying type or body"sv)),((((*this).current())).span())));
return parsed_enum;
}
if (((((*this).current())).__jakt_init_index() == 28 /* LessThan */)){
(((parsed_enum).generic_parameters) = ((*this).parse_generic_parameters()));
}
if (((((*this).current())).__jakt_init_index() == 110 /* Implements */)){
((((*this).index)++));
(((parsed_enum).implements_list) = ((*this).parse_trait_list()));
}
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete enum definition, expected underlying type or body"sv)),((((*this).current())).span())));
return parsed_enum;
}
if (((((*this).current())).__jakt_init_index() == 5 /* Colon */)){
if (is_boxed){
((*this).error((ByteString::from_utf8_without_validation("Invalid enum definition: Value enums must not have an underlying type"sv)),((((*this).current())).span())));
}
((((*this).index)++));
(underlying_type = ((*this).parse_typename()));
}
((*this).skip_newlines());
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete enum definition, expected body"sv)),((((*this).current())).span())));
return parsed_enum;
}
if (((underlying_type).has_value())){
JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ValueEnumVariant>,JaktInternal::DynamicArray<parser::ParsedMethod>> const variants_methods_ = ((*this).parse_value_enum_body(parsed_enum,definition_linkage));
JaktInternal::DynamicArray<parser::ValueEnumVariant> const variants = ((variants_methods_).template get<0>());
JaktInternal::DynamicArray<parser::ParsedMethod> const methods = ((variants_methods_).template get<1>());

(((parsed_enum).methods) = methods);
(((parsed_enum).record_type) = parser::RecordType::ValueEnum((underlying_type.value()),variants));
}
else {
JaktInternal::Tuple<JaktInternal::DynamicArray<parser::SumEnumVariant>,JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>> const variants_fields_methods_records_ = ((*this).parse_sum_enum_body(parsed_enum,definition_linkage,is_boxed));
JaktInternal::DynamicArray<parser::SumEnumVariant> const variants = ((variants_fields_methods_records_).template get<0>());
JaktInternal::DynamicArray<parser::ParsedField> const fields = ((variants_fields_methods_records_).template get<1>());
JaktInternal::DynamicArray<parser::ParsedMethod> const methods = ((variants_fields_methods_records_).template get<2>());
JaktInternal::DynamicArray<parser::ParsedRecord> const records = ((variants_fields_methods_records_).template get<3>());

(((parsed_enum).methods) = methods);
(((parsed_enum).record_type) = parser::RecordType::SumEnum(is_boxed,fields,variants));
(((parsed_enum).nested_records) = records);
}

return parsed_enum;
}
}

JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>> parser::Parser::parse_struct_class_body(parser::DefinitionLinkage const definition_linkage,parser::Visibility const default_visibility,bool const is_class) {
{
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘{’"sv)),((((*this).current())).span())));
}

JaktInternal::DynamicArray<parser::ParsedField> fields = DynamicArray<parser::ParsedField>::create_with({});
JaktInternal::DynamicArray<parser::ParsedMethod> methods = DynamicArray<parser::ParsedMethod>::create_with({});
JaktInternal::DynamicArray<parser::ParsedRecord> records = DynamicArray<parser::ParsedRecord>::create_with({});
JaktInternal::Optional<parser::Visibility> last_visibility = JaktInternal::OptionalNone();
JaktInternal::Optional<utility::Span> last_visibility_span = JaktInternal::OptionalNone();
bool last_virtual = false;
bool last_override = false;
bool last_extern = false;
bool error = false;
JaktInternal::DynamicArray<parser::ParsedAttribute> active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({});
while ((!(((*this).eof())))){
lexer::Token const token = ((*this).current());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Expected function or parameter after visibility modifier"sv)),((token).span())));
}
if ((!(((active_attributes).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("Expected function after attribute"sv)),((token).span())));
}
((((*this).index)++));
return (Tuple{fields, methods, records});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 72 /* Extern */: {
{
(last_extern = true);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
{
if (((last_visibility).has_value())){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Multiple visibility modifiers on one field or method are not allowed"sv)),span,(ByteString::from_utf8_without_validation("Previous modifier is here"sv)),(last_visibility_span.value())));
}
(last_visibility = parser::Visibility::Public());
(last_visibility_span = span);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
{
if (((last_visibility).has_value())){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Multiple visibility modifiers on one field or method are not allowed"sv)),span,(ByteString::from_utf8_without_validation("Previous modifier is here"sv)),(last_visibility_span.value())));
}
(last_visibility = parser::Visibility::Private());
(last_visibility_span = span);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;utility::Span const& span = __jakt_match_value.value;
{
if (((last_visibility).has_value())){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Multiple visibility modifiers on one field or method are not allowed"sv)),span,(ByteString::from_utf8_without_validation("Previous modifier is here"sv)),(last_visibility_span.value())));
}
(last_visibility = ((*this).parse_restricted_visibility_modifier()));
(last_visibility_span = span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
{
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 11 /* LSquare */)){
((((*this).index)) += (static_cast<size_t>(2ULL)));
((*this).parse_attribute_list(((active_attributes))));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Unexpected token (expected ‘[[’)"sv)),((((*this).current())).span())));
((((*this).index)) += (static_cast<size_t>(1ULL)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
{
parser::Visibility const visibility = last_visibility.value_or_lazy_evaluated([&] { return default_visibility; });
(last_visibility = JaktInternal::OptionalNone());
(last_visibility_span = JaktInternal::OptionalNone());
if ((last_virtual || last_override)){
((*this).error((ByteString::from_utf8_without_validation("Fields cannot be ‘virtual’ or ‘override’"sv)),((((*this).current())).span())));
}
(last_virtual = false);
(last_override = false);
if (last_extern){
((*this).error((ByteString::from_utf8_without_validation("Fields cannot be ‘extern’"sv)),((((*this).current())).span())));
}
(last_extern = false);
parser::ParsedField field = ((*this).parse_field(visibility));
((*this).apply_attributes(((field)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((fields).push(field));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
{
bool const is_comptime = ((((*this).current())).__jakt_init_index() == 76 /* Comptime */);
bool const is_destructor = ((((*this).current())).__jakt_init_index() == 69 /* Destructor */);
parser::FunctionLinkage const function_linkage = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = definition_linkage;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Internal */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::Internal());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 1 /* External */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
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
});
(last_extern = false);
if ((((function_linkage).__jakt_init_index() == 1 /* External */) && is_comptime)){
((*this).error((ByteString::from_utf8_without_validation("External functions cannot be comptime"sv)),((((*this).current())).span())));
}
parser::Visibility const visibility = last_visibility.value_or_lazy_evaluated([&] { return default_visibility; });
(last_visibility = JaktInternal::OptionalNone());
(last_visibility_span = JaktInternal::OptionalNone());
bool const is_virtual = last_virtual;
bool const is_override = last_override;
(last_virtual = false);
(last_override = false);
parser::ParsedMethod parsed_method = ((*this).parse_method(function_linkage,visibility,is_virtual,is_override,is_comptime,is_destructor,false));
((*this).apply_attributes(((parsed_method)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((methods).push(parsed_method));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
{
bool const is_comptime = ((((*this).current())).__jakt_init_index() == 76 /* Comptime */);
bool const is_destructor = ((((*this).current())).__jakt_init_index() == 69 /* Destructor */);
parser::FunctionLinkage const function_linkage = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = definition_linkage;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Internal */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::Internal());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 1 /* External */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
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
});
(last_extern = false);
if ((((function_linkage).__jakt_init_index() == 1 /* External */) && is_comptime)){
((*this).error((ByteString::from_utf8_without_validation("External functions cannot be comptime"sv)),((((*this).current())).span())));
}
parser::Visibility const visibility = last_visibility.value_or_lazy_evaluated([&] { return default_visibility; });
(last_visibility = JaktInternal::OptionalNone());
(last_visibility_span = JaktInternal::OptionalNone());
bool const is_virtual = last_virtual;
bool const is_override = last_override;
(last_virtual = false);
(last_override = false);
parser::ParsedMethod parsed_method = ((*this).parse_method(function_linkage,visibility,is_virtual,is_override,is_comptime,is_destructor,false));
((*this).apply_attributes(((parsed_method)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((methods).push(parsed_method));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 69 /* Destructor */: {
{
bool const is_comptime = ((((*this).current())).__jakt_init_index() == 76 /* Comptime */);
bool const is_destructor = ((((*this).current())).__jakt_init_index() == 69 /* Destructor */);
parser::FunctionLinkage const function_linkage = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage, JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>>{
auto&& __jakt_match_variant = definition_linkage;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Internal */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::FunctionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::Internal());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}));
};/*case end*/
case 1 /* External */: {
return JaktInternal::ExplicitValue(parser::FunctionLinkage::External());
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
});
(last_extern = false);
if ((((function_linkage).__jakt_init_index() == 1 /* External */) && is_comptime)){
((*this).error((ByteString::from_utf8_without_validation("External functions cannot be comptime"sv)),((((*this).current())).span())));
}
parser::Visibility const visibility = last_visibility.value_or_lazy_evaluated([&] { return default_visibility; });
(last_visibility = JaktInternal::OptionalNone());
(last_visibility_span = JaktInternal::OptionalNone());
bool const is_virtual = last_virtual;
bool const is_override = last_override;
(last_virtual = false);
(last_override = false);
parser::ParsedMethod parsed_method = ((*this).parse_method(function_linkage,visibility,is_virtual,is_override,is_comptime,is_destructor,false));
((*this).apply_attributes(((parsed_method)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((methods).push(parsed_method));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105 /* Virtual */: {
{
(last_virtual = true);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Override */: {
{
(last_override = true);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
{
if ((last_virtual || last_override)){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot be ‘virtual’ or ‘override’"sv)),((((*this).current())).span())));
(last_virtual = false);
(last_override = false);
}
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot have visibility modifiers"sv)),((((*this).current())).span())));
(last_visibility = JaktInternal::OptionalNone());
}
parser::ParsedRecord parsed_record = ((*this).parse_record(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::DefinitionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::DefinitionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(definition_linkage);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
})));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((records).push(parsed_record));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
{
if ((last_virtual || last_override)){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot be ‘virtual’ or ‘override’"sv)),((((*this).current())).span())));
(last_virtual = false);
(last_override = false);
}
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot have visibility modifiers"sv)),((((*this).current())).span())));
(last_visibility = JaktInternal::OptionalNone());
}
parser::ParsedRecord parsed_record = ((*this).parse_record(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::DefinitionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::DefinitionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(definition_linkage);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
})));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((records).push(parsed_record));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
{
if ((last_virtual || last_override)){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot be ‘virtual’ or ‘override’"sv)),((((*this).current())).span())));
(last_virtual = false);
(last_override = false);
}
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot have visibility modifiers"sv)),((((*this).current())).span())));
(last_visibility = JaktInternal::OptionalNone());
}
parser::ParsedRecord parsed_record = ((*this).parse_record(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::DefinitionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::DefinitionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(definition_linkage);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
})));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((records).push(parsed_record));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
{
if ((last_virtual || last_override)){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot be ‘virtual’ or ‘override’"sv)),((((*this).current())).span())));
(last_virtual = false);
(last_override = false);
}
if (((last_visibility).has_value())){
((*this).error((ByteString::from_utf8_without_validation("Nested types cannot have visibility modifiers"sv)),((((*this).current())).span())));
(last_visibility = JaktInternal::OptionalNone());
}
parser::ParsedRecord parsed_record = ((*this).parse_record(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::DefinitionLinkage,JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>>> {
auto __jakt_enum_value = (last_extern);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::DefinitionLinkage::External());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(definition_linkage);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
})));
((*this).apply_attributes(((parsed_record)),((active_attributes))));
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
((records).push(parsed_record));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(active_attributes = DynamicArray<parser::ParsedAttribute>::create_with({}));
if ((!(error))){
((*this).error(__jakt_format((StringView::from_string_literal("Invalid member, did not expect a {} here"sv)),token),((token).span())));
(error = true);
}
((((*this).index)++));
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
if (is_class){
((*this).error((ByteString::from_utf8_without_validation("Incomplete class body, expected ‘}’"sv)),((((*this).current())).span())));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Incomplete struct body, expected ‘}’"sv)),((((*this).current())).span())));
}

return (Tuple{fields, methods, records});
}
}

parser::ParsedRecord parser::Parser::parse_struct(parser::DefinitionLinkage const definition_linkage) {
{
parser::ParsedRecord parsed_struct = parser::ParsedRecord((ByteString::from_utf8_without_validation(""sv)),((*this).empty_span()),DynamicArray<parser::ParsedGenericParameter>::create_with({}),definition_linkage,JaktInternal::OptionalNone(),DynamicArray<parser::ParsedMethod>::create_with({}),parser::RecordType::Garbage(),DynamicArray<parser::ParsedRecord>::create_with({}),JaktInternal::OptionalNone());
if (((((*this).current())).__jakt_init_index() == 98 /* Struct */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected `struct` keyword"sv)),((((*this).current())).span())));
return parsed_struct;
}

if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete struct definition, expected name"sv)),((((*this).current())).span())));
return parsed_struct;
}
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const span = (((*this).current())).as.Identifier.span;
((((*this).index)++));
(((parsed_struct).name) = name);
(((parsed_struct).name_span) = span);
}
else {
((*this).error((ByteString::from_utf8_without_validation("Incomplete struct definition, expected name"sv)),((((*this).current())).span())));
}

if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete struct definition, expected generic parameters or body"sv)),((((*this).current())).span())));
return parsed_struct;
}
(((parsed_struct).generic_parameters) = ((*this).parse_generic_parameters()));
if (((((*this).current())).__jakt_init_index() == 110 /* Implements */)){
((((*this).index)++));
(((parsed_struct).implements_list) = ((*this).parse_trait_list()));
}
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type = JaktInternal::OptionalNone();
if (((((*this).current())).__jakt_init_index() == 5 /* Colon */)){
((((*this).index)++));
(super_type = ((*this).parse_typename()));
}
((*this).skip_newlines());
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete struct definition, expected body"sv)),((((*this).current())).span())));
return parsed_struct;
}
JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>> const fields_methods_records_ = ((*this).parse_struct_class_body(definition_linkage,parser::Visibility::Public(),false));
JaktInternal::DynamicArray<parser::ParsedField> const fields = ((fields_methods_records_).template get<0>());
JaktInternal::DynamicArray<parser::ParsedMethod> const methods = ((fields_methods_records_).template get<1>());
JaktInternal::DynamicArray<parser::ParsedRecord> const records = ((fields_methods_records_).template get<2>());

(((parsed_struct).methods) = methods);
(((parsed_struct).record_type) = parser::RecordType::Struct(fields,super_type));
(((parsed_struct).nested_records) = records);
return parsed_struct;
}
}

parser::ParsedRecord parser::Parser::parse_class(parser::DefinitionLinkage const definition_linkage) {
{
parser::ParsedRecord parsed_class = parser::ParsedRecord((ByteString::from_utf8_without_validation(""sv)),((*this).empty_span()),DynamicArray<parser::ParsedGenericParameter>::create_with({}),definition_linkage,JaktInternal::OptionalNone(),DynamicArray<parser::ParsedMethod>::create_with({}),parser::RecordType::Garbage(),DynamicArray<parser::ParsedRecord>::create_with({}),JaktInternal::OptionalNone());
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type = JaktInternal::OptionalNone();
if (((((*this).current())).__jakt_init_index() == 65 /* Class */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected `class` keyword"sv)),((((*this).current())).span())));
return parsed_class;
}

if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete class definition, expected name"sv)),((((*this).current())).span())));
return parsed_class;
}
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
utility::Span const span = (((*this).current())).as.Identifier.span;
((((*this).index)++));
(((parsed_class).name) = name);
(((parsed_class).name_span) = span);
}
else {
((*this).error((ByteString::from_utf8_without_validation("Incomplete class definition, expected name"sv)),((((*this).current())).span())));
}

if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete class definition, expected generic parameters or super class or body"sv)),((((*this).current())).span())));
return parsed_class;
}
(((parsed_class).generic_parameters) = ((*this).parse_generic_parameters()));
if (((((*this).current())).__jakt_init_index() == 110 /* Implements */)){
((((*this).index)++));
(((parsed_class).implements_list) = ((*this).parse_trait_list()));
}
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete class definition, expected super class or body"sv)),((((*this).current())).span())));
return parsed_class;
}
if (((((*this).current())).__jakt_init_index() == 5 /* Colon */)){
((((*this).index)++));
(super_type = ((*this).parse_typename()));
}
((*this).skip_newlines());
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete class definition, expected body"sv)),((((*this).current())).span())));
return parsed_class;
}
JaktInternal::Tuple<JaktInternal::DynamicArray<parser::ParsedField>,JaktInternal::DynamicArray<parser::ParsedMethod>,JaktInternal::DynamicArray<parser::ParsedRecord>> const fields_methods_records_ = ((*this).parse_struct_class_body(definition_linkage,parser::Visibility::Private(),true));
JaktInternal::DynamicArray<parser::ParsedField> const fields = ((fields_methods_records_).template get<0>());
JaktInternal::DynamicArray<parser::ParsedMethod> const methods = ((fields_methods_records_).template get<1>());
JaktInternal::DynamicArray<parser::ParsedRecord> const records = ((fields_methods_records_).template get<2>());

(((parsed_class).methods) = methods);
(((parsed_class).record_type) = parser::RecordType::Class(fields,super_type));
(((parsed_class).nested_records) = records);
return parsed_class;
}
}

parser::ParsedFunctionParameters parser::Parser::parse_function_parameters(bool const for_trailing_closure) {
{
if (((!(for_trailing_closure)) && ((((*this).current())).__jakt_init_index() == 7 /* LParen */))){
((((*this).index)++));
}
else if ((for_trailing_closure && ((((*this).current())).__jakt_init_index() == 40 /* Pipe */))){
((((*this).index)++));
}
else {
((*this).error(__jakt_format((StringView::from_string_literal("Expected '{:c}'"sv)),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u32,parser::ParsedFunctionParameters> {
auto __jakt_enum_value = (for_trailing_closure);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<u32>(U'|'));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(static_cast<u32>(U')'));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})),((((*this).current())).span())));
}

((*this).skip_newlines());
parser::ParsedFunctionParameters result = parser::ParsedFunctionParameters(DynamicArray<parser::ParsedParameter>::create_with({}),false);
bool current_param_requires_label = true;
bool current_param_is_mutable = false;
bool error = false;
bool parameter_complete = false;
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedFunctionParameters>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
{
if ((!(for_trailing_closure))){
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
if ((!(error))){
((*this).error((ByteString::from_utf8_without_validation("Expected parameter"sv)),((((*this).current())).span())));
(error = true);
}
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40 /* Pipe */: {
{
if (for_trailing_closure){
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
if ((!(error))){
((*this).error((ByteString::from_utf8_without_validation("Expected parameter"sv)),((((*this).current())).span())));
(error = true);
}
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
if (((!(parameter_complete)) && (!(error)))){
((*this).error((ByteString::from_utf8_without_validation("Expected parameter"sv)),((((*this).current())).span())));
(error = true);
}
((((*this).index)++));
(current_param_requires_label = true);
(current_param_is_mutable = false);
(parameter_complete = false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
if (((!(parameter_complete)) && (!(error)))){
((*this).error((ByteString::from_utf8_without_validation("Expected parameter"sv)),((((*this).current())).span())));
(error = true);
}
((((*this).index)++));
(current_param_requires_label = true);
(current_param_is_mutable = false);
(parameter_complete = false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 54 /* DotDot */: {
{
if (((result).has_varargs)){
((*this).error((ByteString::from_utf8_without_validation("Multiple varargs cannot be present in one parameter list"sv)),((((*this).current())).span())));
(error = true);
}
if (current_param_is_mutable){
((*this).error((ByteString::from_utf8_without_validation("A variadic argument cannot be mutable"sv)),((((*this).current())).span())));
(error = true);
}
if ((!(current_param_requires_label))){
((*this).error((ByteString::from_utf8_without_validation("A variadic argument cannot be anonymous"sv)),((((*this).current())).span())));
(error = true);
}
(((result).has_varargs) = true);
((((*this).index)++));
(parameter_complete = false);
(current_param_requires_label = true);
(current_param_is_mutable = false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60 /* Anon */: {
{
if (((result).has_varargs)){
((*this).error((ByteString::from_utf8_without_validation("A variadic argument may only appear at the end of a parameter list"sv)),((((*this).current())).span())));
(error = true);
}
if ((parameter_complete && (!(error)))){
((*this).error((ByteString::from_utf8_without_validation("‘anon’ must appear at start of parameter declaration, not the end"sv)),((((*this).current())).span())));
(error = true);
}
if ((current_param_is_mutable && (!(error)))){
((*this).error((ByteString::from_utf8_without_validation("‘anon’ must appear before ‘mut’"sv)),((((*this).current())).span())));
(error = true);
}
if (((!(current_param_requires_label)) && (!(error)))){
((*this).error((ByteString::from_utf8_without_validation("‘anon’ cannot appear multiple times in one parameter declaration"sv)),((((*this).current())).span())));
(error = true);
}
((((*this).index)++));
(current_param_requires_label = false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 86 /* Mut */: {
{
if (((result).has_varargs)){
((*this).error((ByteString::from_utf8_without_validation("A variadic argument may only appear at the end of a parameter list"sv)),((((*this).current())).span())));
(error = true);
}
if ((parameter_complete && (!(error)))){
((*this).error((ByteString::from_utf8_without_validation("‘mut’ must appear at start of parameter declaration, not the end"sv)),((((*this).current())).span())));
(error = true);
}
if ((current_param_is_mutable && (!(error)))){
((*this).error((ByteString::from_utf8_without_validation("‘mut’ cannot appear multiple times in one parameter declaration"sv)),((((*this).current())).span())));
(error = true);
}
((((*this).index)++));
(current_param_is_mutable = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* This */: {
{
if (((result).has_varargs)){
((*this).error((ByteString::from_utf8_without_validation("A variadic argument may only appear at the end of a parameter list"sv)),((((*this).current())).span())));
(error = true);
}
((((result).parameters)).push(parser::ParsedParameter(false,parser::ParsedVariable((ByteString::from_utf8_without_validation("this"sv)),parser::ParsedType::Empty(JaktInternal::OptionalNone()),current_param_is_mutable,((((*this).current())).span())),JaktInternal::OptionalNone(),((((*this).current())).span()))));
((((*this).index)++));
(parameter_complete = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
if (((result).has_varargs)){
((*this).error((ByteString::from_utf8_without_validation("A variadic argument may only appear at the end of a parameter list"sv)),((((*this).current())).span())));
(error = true);
}
parser::ParsedVarDecl const var_decl = ((*this).parse_variable_declaration(current_param_is_mutable));
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> default_argument = JaktInternal::OptionalNone();
if (((((*this).current())).__jakt_init_index() == 16 /* Equal */)){
((((*this).index)++));
(default_argument = ((*this).parse_expression(false,true)));
}
((((result).parameters)).push(parser::ParsedParameter(current_param_requires_label,parser::ParsedVariable(((var_decl).name),((var_decl).parsed_type),((var_decl).is_mutable),((((*this).previous())).span())),default_argument,((((*this).previous())).span()))));
(parameter_complete = true);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
if ((!(error))){
((*this).error((ByteString::from_utf8_without_validation("Expected parameter"sv)),((((*this).current())).span())));
(error = true);
}
((((*this).index)++));
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
return result;
}
}

parser::ParsedFunction parser::Parser::parse_function(parser::FunctionLinkage const linkage,parser::Visibility const visibility,bool const is_comptime,bool const is_destructor,bool const is_unsafe,bool const allow_missing_body) {
{
parser::ParsedFunction parsed_function = parser::ParsedFunction(((((*this).next_function_id)++)),(ByteString::from_utf8_without_validation(""sv)),((*this).empty_span()),visibility,DynamicArray<parser::ParsedParameter>::create_with({}),DynamicArray<parser::ParsedGenericParameter>::create_with({}),parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({})),parser::ParsedType::Empty(JaktInternal::OptionalNone()),((*this).span(static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))),false,parser::FunctionType::Normal(),linkage,false,is_comptime,false,is_unsafe,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),parser::InlineState::Default());
if (is_destructor){
(((parsed_function).type) = parser::FunctionType::Destructor());
((((parsed_function).params)).push(parser::ParsedParameter(false,parser::ParsedVariable((ByteString::from_utf8_without_validation("this"sv)),parser::ParsedType::Empty(JaktInternal::OptionalNone()),true,((((*this).current())).span())),JaktInternal::OptionalNone(),((((*this).current())).span()))));
}
if ((!(is_destructor))){
((((*this).index)++));
}
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete function definition"sv)),((((*this).current())).span())));
return parsed_function;
}
if (is_destructor){
(((parsed_function).name) = (ByteString::from_utf8_without_validation("~"sv)));
(((parsed_function).name_span) = ((((*this).previous())).span()));
}
else {
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
(((parsed_function).name) = name);
(((parsed_function).name_span) = ((((*this).current())).span()));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Incomplete function definition"sv)),((((*this).current())).span())));
return parsed_function;
}

}

((((*this).index)++));
if ((!(is_destructor))){
(((parsed_function).generic_parameters) = ((*this).parse_generic_parameters()));
}
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete function"sv)),((((*this).current())).span())));
}
if ((!(is_destructor))){
parser::ParsedFunctionParameters const fn_parameters = ((*this).parse_function_parameters(false));
(((parsed_function).params) = ((fn_parameters).parameters));
(((parsed_function).has_varargs) = ((fn_parameters).has_varargs));
}
(((parsed_function).is_jakt_main) = ((((parsed_function).name)) == ((ByteString::from_utf8_without_validation("main"sv)))));
bool can_throw = ((parsed_function).is_jakt_main);
if (((((*this).current())).__jakt_init_index() == 101 /* Throws */)){
if (is_destructor){
((*this).error((ByteString::from_utf8_without_validation("Destructor cannot throw"sv)),((((*this).current())).span())));
}
else {
(can_throw = true);
}

((((*this).index)++));
}
(((parsed_function).can_throw) = can_throw);
if (((((*this).current())).__jakt_init_index() == 58 /* Arrow */)){
((((*this).index)++));
utility::Span const start = ((((*this).current())).span());
(((parsed_function).return_type) = ((*this).parse_typename()));
(((parsed_function).return_type_span) = parser::merge_spans(start,((((*this).previous())).span())));
}
else {
if (((parsed_function).is_jakt_main)){
(((parsed_function).return_type) = parser::ParsedType::Name(JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("c_int"sv)),((((*this).previous())).span())));
}
(((parsed_function).return_type_span) = ((((*this).previous())).span()));
}

if (((linkage).__jakt_init_index() == 1 /* External */)){
return parsed_function;
}
if (((((*this).current())).__jakt_init_index() == 57 /* FatArrow */)){
(((parsed_function).block) = ((*this).parse_fat_arrow()));
(((parsed_function).is_fat_arrow) = true);
}
else {
if (allow_missing_body){
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
}
else {
return parsed_function;
}

}
(((parsed_function).block) = ((*this).parse_block()));
}

return parsed_function;
}
}

parser::ParsedBlock parser::Parser::parse_fat_arrow() {
{
((((*this).index)++));
utility::Span const start = ((((*this).current())).span());
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
NonnullRefPtr<typename parser::ParsedStatement> const return_statement = parser::ParsedStatement::Return(expr,parser::merge_spans(start,((((*this).current())).span())));
return parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({return_statement}));
}
}

parser::ParsedField parser::Parser::parse_field(parser::Visibility const visibility) {
{
parser::ParsedVarDecl const parsed_variable_declaration = ((*this).parse_variable_declaration(true));
if (((((parsed_variable_declaration).parsed_type))->__jakt_init_index() == 15 /* Empty */)){
((*this).error((ByteString::from_utf8_without_validation("Field missing type"sv)),((parsed_variable_declaration).span)));
}
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> default_value = JaktInternal::OptionalNone();
if (((((*this).peek(static_cast<size_t>(0ULL)))).__jakt_init_index() == 16 /* Equal */)){
((((*this).index)++));
(default_value = ((*this).parse_expression(false,false)));
}
return parser::ParsedField(parsed_variable_declaration,visibility,default_value);
}
}

parser::ParsedMethod parser::Parser::parse_method(parser::FunctionLinkage const linkage,parser::Visibility const visibility,bool const is_virtual,bool const is_override,bool const is_comptime,bool const is_destructor,bool const is_unsafe) {
{
parser::ParsedFunction parsed_function = ((*this).parse_function(linkage,visibility,is_comptime,is_destructor,is_unsafe,false));
if (((linkage).__jakt_init_index() == 1 /* External */)){
(((parsed_function).must_instantiate) = true);
}
return parser::ParsedMethod(parsed_function,visibility,is_virtual,is_override);
}
}

JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> parser::Parser::parse_type_parameter_list() {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> params = DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({});
if (((((*this).current())).__jakt_init_index() == 28 /* LessThan */)){
((((*this).index)++));
bool saw_ending_bracket = false;
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* GreaterThan */: {
{
((((*this).index)++));
(saw_ending_bracket = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
{
((*this).inject_token(lexer::Token::GreaterThan(((((*this).current())).span()))));
((((*this).index)++));
(saw_ending_bracket = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
size_t index_before = ((*this).index);
((params).push(((*this).parse_typename())));
if (((((*this).index)) == (index_before))){
((*this).error((ByteString::from_utf8_without_validation("Expected type parameter"sv)),((((*this).current())).span())));
return JaktInternal::LoopBreak{};
}
if (((((*this).current())).__jakt_init_index() == 52 /* Comma */)){
((((*this).index)++));
}
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
if ((!(saw_ending_bracket))){
((*this).error((ByteString::from_utf8_without_validation("Expected `>` after type parameters"sv)),((((*this).current())).span())));
}
}
return params;
}
}

NonnullRefPtr<typename parser::ParsedType> parser::Parser::parse_typename() {
{
NonnullRefPtr<typename parser::ParsedType> const base = ((*this).parse_typename_base());
NonnullRefPtr<typename parser::ParsedType> result = base;
bool done = false;
while ((!(done))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedType>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* ColonColon */: {
{
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
((((*this).index)++));
(result = parser::ParsedType::DependentType(JaktInternal::OptionalNone(),result,name,parser::merge_spans(((base)->span()),((((*this).current())).span()))));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected identifier after `::`"sv)),((((*this).current())).span())));
(done = true);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(done = true);
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
return result;
}
}

NonnullRefPtr<typename parser::ParsedType> parser::Parser::parse_typename_base() {
{
utility::Span const start = ((((*this).current())).span());
if (((((*this).current())).__jakt_init_index() == 76 /* Comptime */)){
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
return parser::ParsedType::Const(JaktInternal::OptionalNone(),expr,parser::merge_spans(start,((expr)->span())));
}
parser::ParsedTypeQualifiers qualifiers = parser::ParsedTypeQualifiers(false,false);
bool is_reference = false;
bool is_mutable_reference = false;
if (((((*this).current())).__jakt_init_index() == 37 /* Ampersand */)){
(is_reference = true);
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 86 /* Mut */)){
(is_mutable_reference = true);
((((*this).index)++));
}
}
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
if (((name) == ((ByteString::from_utf8_without_validation("const"sv))))){
(((qualifiers).is_immutable) = true);
((((*this).index)++));
}
else if (((((*this).current())).__jakt_init_index() == 86 /* Mut */)){
(((qualifiers).is_mutable) = true);
((((*this).index)++));
}
}
else if (((((*this).current())).__jakt_init_index() == 86 /* Mut */)){
(((qualifiers).is_mutable) = true);
((((*this).index)++));
}
NonnullRefPtr<typename parser::ParsedType> parsed_type = ((*this).parse_type_shorthand(qualifiers));
if (((parsed_type)->__jakt_init_index() == 15 /* Empty */)){
(parsed_type = ((*this).parse_type_longhand(qualifiers)));
}
if (((((*this).current())).__jakt_init_index() == 49 /* QuestionMark */)){
((((*this).index)++));
utility::Span const span = parser::merge_spans(start,((((*this).current())).span()));
(parsed_type = parser::ParsedType::Optional(JaktInternal::OptionalNone(),parsed_type,span));
}
if (is_reference){
utility::Span const span = parser::merge_spans(start,((((*this).current())).span()));
if (is_mutable_reference){
(parsed_type = parser::ParsedType::MutableReference(JaktInternal::OptionalNone(),parsed_type,span));
}
else {
(parsed_type = parser::ParsedType::Reference(JaktInternal::OptionalNone(),parsed_type,span));
}

}
return parsed_type;
}
}

NonnullRefPtr<typename parser::ParsedType> parser::Parser::parse_type_longhand(parser::ParsedTypeQualifiers const qualifiers) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedType>, NonnullRefPtr<typename parser::ParsedType>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 93 /* Raw */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedType>> __jakt_var_28; {
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedType> const inner = ((*this).parse_typename());
utility::Span const span = parser::merge_spans(start,((((*this).current())).span()));
__jakt_var_28 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedType>, NonnullRefPtr<typename parser::ParsedType>>{
auto&& __jakt_match_variant = *inner;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* Optional */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Optional;NonnullRefPtr<typename parser::ParsedType> const& inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(parser::ParsedType::Optional(qualifiers,parser::ParsedType::RawPtr(JaktInternal::OptionalNone(),inner,span),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(parser::ParsedType::RawPtr(qualifiers,inner,span));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_23;

}
__jakt_label_23:; __jakt_var_28.release_value(); }));
};/*case end*/
case 106 /* Weak */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedType>> __jakt_var_29; {
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedType> const inner = ((*this).parse_typename());
utility::Span const span = parser::merge_spans(start,((((*this).current())).span()));
__jakt_var_29 = parser::ParsedType::WeakPtr(qualifiers,inner,span); goto __jakt_label_24;

}
__jakt_label_24:; __jakt_var_29.release_value(); }));
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedType>> __jakt_var_30; {
utility::Span const span = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedType> parsed_type = parser::ParsedType::Name(qualifiers,name,span);
if (((((*this).current())).__jakt_init_index() == 28 /* LessThan */)){
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> params = ((*this).parse_type_parameter_list());
(parsed_type = parser::ParsedType::GenericType(qualifiers,name,params,span));
}
if (((((*this).current())).__jakt_init_index() == 6 /* ColonColon */)){
((((*this).index)++));
JaktInternal::DynamicArray<ByteString> namespaces = DynamicArray<ByteString>::create_with({name});
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedType>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& namespace_name = __jakt_match_value.name;
{
if (((((*this).previous())).__jakt_init_index() == 6 /* ColonColon */)){
((namespaces).push(namespace_name));
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘::’ here"sv)),utility::Span(((span).file_id),((span).start),((span).start))));
return JaktInternal::LoopBreak{};
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* ColonColon */: {
{
if (((((*this).previous())).__jakt_init_index() == 3 /* Identifier */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected name after"sv)),span));
return JaktInternal::LoopBreak{};
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
return JaktInternal::LoopBreak{};
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
ByteString const type_name = (((namespaces).pop()).value());
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> params = ((*this).parse_type_parameter_list());
(parsed_type = parser::ParsedType::NamespacedName(JaktInternal::OptionalNone(),type_name,namespaces,params,((((*this).previous())).span())));
}
__jakt_var_30 = parsed_type; goto __jakt_label_25;

}
__jakt_label_25:; __jakt_var_30.release_value(); }));
};/*case end*/
case 75 /* Fn */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedType>> __jakt_var_31; {
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
parser::ParsedFunctionParameters const fn_parameters = ((*this).parse_function_parameters(false));
if (((fn_parameters).has_varargs)){
((*this).error((ByteString::from_utf8_without_validation("Function type cannot have variadic arguments"sv)),((((*this).current())).span())));
}
bool const can_throw = ((((*this).current())).__jakt_init_index() == 101 /* Throws */);
if (can_throw){
((((*this).index)++));
}
NonnullRefPtr<typename parser::ParsedType> return_type = parser::ParsedType::Empty(JaktInternal::OptionalNone());
if (((((*this).current())).__jakt_init_index() == 58 /* Arrow */)){
((((*this).index)++));
(return_type = ((*this).parse_typename()));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '->'"sv)),((((*this).current())).span())));
}

__jakt_var_31 = parser::ParsedType::Function(qualifiers,((fn_parameters).parameters),can_throw,return_type,parser::merge_spans(start,((return_type)->span()))); goto __jakt_label_26;

}
__jakt_label_26:; __jakt_var_31.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedType>> __jakt_var_32; {
((*this).error((ByteString::from_utf8_without_validation("Expected type name"sv)),((((*this).current())).span())));
__jakt_var_32 = parser::ParsedType::Empty(qualifiers); goto __jakt_label_27;

}
__jakt_label_27:; __jakt_var_32.release_value(); }));
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

parser::ParsedVarDeclTuple parser::Parser::parse_destructuring_assignment(bool const is_mutable) {
{
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
JaktInternal::DynamicArray<parser::ParsedVarDecl> var_declarations = DynamicArray<parser::ParsedVarDecl>::create_with({});
for (;;){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedVarDeclTuple>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
{
((var_declarations).push(((*this).parse_variable_declaration(is_mutable))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected close of destructuring assignment block"sv)),((((*this).current())).span())));
(var_declarations = DynamicArray<parser::ParsedVarDecl>::create_with({}));
return JaktInternal::LoopBreak{};
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
return parser::ParsedVarDeclTuple(var_declarations,parser::merge_spans(start,((((*this).previous())).span())));
}
}

parser::ParsedVarDecl parser::Parser::parse_variable_declaration(bool const is_mutable) {
{
utility::Span const span = ((((*this).current())).span());
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 5 /* Colon */)){
((((*this).index)++));
}
else {
return parser::ParsedVarDecl(name,parser::ParsedType::Empty(JaktInternal::OptionalNone()),is_mutable,span,span,JaktInternal::OptionalNone());
}

NonnullRefPtr<typename parser::ParsedType> const parsed_type = ((*this).parse_typename());
if ((is_mutable && (((parsed_type)->__jakt_init_index() == 8 /* Reference */) || ((parsed_type)->__jakt_init_index() == 9 /* MutableReference */)))){
((*this).error((ByteString::from_utf8_without_validation("Reference parameter can not be mutable"sv)),span));
}
return parser::ParsedVarDecl(name,parsed_type,is_mutable,JaktInternal::OptionalNone(),span,JaktInternal::OptionalNone());
}
else {
return parser::ParsedVarDecl((ByteString::from_utf8_without_validation(""sv)),parser::ParsedType::Empty(JaktInternal::OptionalNone()),false,JaktInternal::OptionalNone(),span,JaktInternal::OptionalNone());
}

}
}

NonnullRefPtr<typename parser::ParsedType> parser::Parser::parse_type_shorthand(parser::ParsedTypeQualifiers const qualifiers) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedType>, NonnullRefPtr<typename parser::ParsedType>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(((*this).parse_type_shorthand_array_or_dictionary(qualifiers)));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(((*this).parse_type_shorthand_set(qualifiers)));
};/*case end*/
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(((*this).parse_type_shorthand_tuple(qualifiers)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(parser::ParsedType::Empty(qualifiers));
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

NonnullRefPtr<typename parser::ParsedType> parser::Parser::parse_type_shorthand_array_or_dictionary(parser::ParsedTypeQualifiers const qualifiers) {
{
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedType> const inner = ((*this).parse_typename());
if (((((*this).current())).__jakt_init_index() == 12 /* RSquare */)){
((((*this).index)++));
return parser::ParsedType::JaktArray(qualifiers,inner,parser::merge_spans(start,((((*this).previous())).span())));
}
if (((((*this).current())).__jakt_init_index() == 5 /* Colon */)){
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedType> const value = ((*this).parse_typename());
if (((((*this).current())).__jakt_init_index() == 12 /* RSquare */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ']'"sv)),((((*this).current())).span())));
}

return parser::ParsedType::Dictionary(qualifiers,inner,value,parser::merge_spans(start,((((*this).current())).span())));
}
((*this).error((ByteString::from_utf8_without_validation("Expected shorthand type"sv)),((((*this).current())).span())));
return parser::ParsedType::Empty(qualifiers);
}
}

NonnullRefPtr<typename parser::ParsedType> parser::Parser::parse_type_shorthand_set(parser::ParsedTypeQualifiers const qualifiers) {
{
utility::Span const start = ((((*this).current())).span());
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
}
NonnullRefPtr<typename parser::ParsedType> const inner = ((*this).parse_typename());
if (((((*this).current())).__jakt_init_index() == 10 /* RCurly */)){
((((*this).index)++));
return parser::ParsedType::Set(qualifiers,inner,parser::merge_spans(start,((((*this).current())).span())));
}
((*this).error((ByteString::from_utf8_without_validation("Expected '}'"sv)),((((*this).current())).span())));
return parser::ParsedType::Empty(qualifiers);
}
}

NonnullRefPtr<typename parser::ParsedType> parser::Parser::parse_type_shorthand_tuple(parser::ParsedTypeQualifiers const qualifiers) {
{
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> types = DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({});
while ((!(((*this).eof())))){
if (((((*this).current())).__jakt_init_index() == 8 /* RParen */)){
((((*this).index)++));
return parser::ParsedType::JaktTuple(qualifiers,types,parser::merge_spans(start,((((*this).previous())).span())));
}
if (((((*this).current())).__jakt_init_index() == 52 /* Comma */)){
((((*this).index)++));
}
size_t const index_before = ((*this).index);
NonnullRefPtr<typename parser::ParsedType> const type = ((*this).parse_typename());
size_t const index_after = ((*this).index);
if (((index_before) == (index_after))){
break;
}
((types).push(type));
}
((*this).error((ByteString::from_utf8_without_validation("Expected ‘)’"sv)),((((*this).current())).span())));
return parser::ParsedType::Empty(qualifiers);
}
}

parser::ParsedBlock parser::Parser::parse_block() {
{
utility::Span const start = ((((*this).current())).span());
parser::ParsedBlock block = parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({}));
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Incomplete block"sv)),start));
return block;
}
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '{'"sv)),start));
}

while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedBlock>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
((((*this).index)++));
return block;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Semicolon */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((((block).stmts)).push(((*this).parse_statement(true))));
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
((*this).error((ByteString::from_utf8_without_validation("Expected complete block"sv)),((((*this).current())).span())));
return block;
}
}

NonnullRefPtr<typename parser::ParsedStatement> parser::Parser::parse_statement(bool const inside_block) {
{
utility::Span const start = ((((*this).current())).span());
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedStatement>, NonnullRefPtr<typename parser::ParsedStatement>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 67 /* Cpp */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_33; {
((((*this).index)++));
__jakt_var_33 = parser::ParsedStatement::InlineCpp(((*this).parse_block()),parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_28;

}
__jakt_label_28:; __jakt_var_33.release_value(); }));
};/*case end*/
case 68 /* Defer */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_34; {
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedStatement> const statement = ((*this).parse_statement(false));
__jakt_var_34 = parser::ParsedStatement::Defer(statement,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_29;

}
__jakt_label_29:; __jakt_var_34.release_value(); }));
};/*case end*/
case 104 /* Unsafe */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedStatement>, NonnullRefPtr<typename parser::ParsedStatement>>{
auto&& __jakt_match_variant = ((*this).peek(static_cast<size_t>(1ULL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_35; {
((((*this).index)++));
parser::ParsedBlock const block = ((*this).parse_block());
__jakt_var_35 = parser::ParsedStatement::UnsafeBlock(block,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_30;

}
__jakt_label_30:; __jakt_var_35.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_36; {
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(true,false));
__jakt_var_36 = parser::ParsedStatement::Expression(expr,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_31;

}
__jakt_label_31:; __jakt_var_36.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 63 /* Break */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_37; {
((((*this).index)++));
__jakt_var_37 = parser::ParsedStatement::Break(start); goto __jakt_label_32;

}
__jakt_label_32:; __jakt_var_37.release_value(); }));
};/*case end*/
case 66 /* Continue */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_38; {
((((*this).index)++));
__jakt_var_38 = parser::ParsedStatement::Continue(start); goto __jakt_label_33;

}
__jakt_label_33:; __jakt_var_38.release_value(); }));
};/*case end*/
case 83 /* Loop */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_39; {
((((*this).index)++));
parser::ParsedBlock const block = ((*this).parse_block());
__jakt_var_39 = parser::ParsedStatement::Loop(block,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_34;

}
__jakt_label_34:; __jakt_var_39.release_value(); }));
};/*case end*/
case 100 /* Throw */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_40; {
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
__jakt_var_40 = parser::ParsedStatement::Throw(expr,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_35;

}
__jakt_label_35:; __jakt_var_40.release_value(); }));
};/*case end*/
case 107 /* While */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_41; {
((((*this).index)++));
bool const previous_can_have_trailing_closure = ((*this).can_have_trailing_closure);
(((*this).can_have_trailing_closure) = false);
NonnullRefPtr<typename parser::ParsedExpression> const condition = ((*this).parse_expression(false,true));
(((*this).can_have_trailing_closure) = previous_can_have_trailing_closure);
parser::ParsedBlock const block = ((*this).parse_block());
__jakt_var_41 = parser::ParsedStatement::While(condition,block,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_36;

}
__jakt_label_36:; __jakt_var_41.release_value(); }));
};/*case end*/
case 108 /* Yield */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_42; {
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
if ((!(inside_block))){
((*this).error((ByteString::from_utf8_without_validation("‘yield’ can only be used inside a block"sv)),parser::merge_spans(start,((expr)->span()))));
}
__jakt_var_42 = parser::ParsedStatement::Yield(expr,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_37;

}
__jakt_label_37:; __jakt_var_42.release_value(); }));
};/*case end*/
case 95 /* Return */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_43; {
((((*this).index)++));
__jakt_var_43 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedStatement>, NonnullRefPtr<typename parser::ParsedStatement>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
return JaktInternal::ExplicitValue(parser::ParsedStatement::Return(JaktInternal::OptionalNone(),start));
};/*case end*/
case 56 /* Eof */: {
return JaktInternal::ExplicitValue(parser::ParsedStatement::Return(JaktInternal::OptionalNone(),start));
};/*case end*/
case 10 /* RCurly */: {
return JaktInternal::ExplicitValue(parser::ParsedStatement::Return(JaktInternal::OptionalNone(),start));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(parser::ParsedStatement::Return(((*this).parse_expression(false,false)),parser::merge_spans(start,((((*this).previous())).span()))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_38;

}
__jakt_label_38:; __jakt_var_43.release_value(); }));
};/*case end*/
case 82 /* Let */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_44; {
bool const is_mutable = ((((*this).current())).__jakt_init_index() == 86 /* Mut */);
((((*this).index)++));
JaktInternal::DynamicArray<parser::ParsedVarDecl> vars = DynamicArray<parser::ParsedVarDecl>::create_with({});
bool is_destructuring_assingment = false;
ByteString tuple_var_name = (ByteString::from_utf8_without_validation(""sv));
parser::ParsedVarDecl tuple_var_decl = parser::ParsedVarDecl((ByteString::from_utf8_without_validation(""sv)),parser::ParsedType::Empty(JaktInternal::OptionalNone()),is_mutable,JaktInternal::OptionalNone(),((((*this).current())).span()),JaktInternal::OptionalNone());
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
(vars = ((((*this).parse_destructuring_assignment(is_mutable))).var_decls));
{
JaktInternal::ArrayIterator<parser::ParsedVarDecl> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedVarDecl> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedVarDecl var = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(tuple_var_name,((var).name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(tuple_var_name,(ByteString::from_utf8_without_validation("_"sv)));
}

}
}

(((tuple_var_decl).name) = tuple_var_name);
(is_destructuring_assingment = true);
}
else {
(tuple_var_decl = ((*this).parse_variable_declaration(is_mutable)));
}

NonnullRefPtr<typename parser::ParsedExpression> const init = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedStatement>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* Equal */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_45; {
((((*this).index)++));
__jakt_var_45 = ((*this).parse_expression(false,false)); goto __jakt_label_40;

}
__jakt_label_40:; __jakt_var_45.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_46; {
((*this).error((ByteString::from_utf8_without_validation("Expected initializer"sv)),((((*this).current())).span())));
__jakt_var_46 = parser::ParsedExpression::Garbage(((((*this).current())).span())); goto __jakt_label_41;

}
__jakt_label_41:; __jakt_var_46.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename parser::ParsedStatement> return_statement = parser::ParsedStatement::VarDecl(tuple_var_decl,init,parser::merge_spans(start,((((*this).previous())).span())));
if (is_destructuring_assingment){
NonnullRefPtr<typename parser::ParsedStatement> const old_return_statement = return_statement;
(return_statement = parser::ParsedStatement::DestructuringAssignment(vars,old_return_statement,parser::merge_spans(start,((((*this).previous())).span()))));
}
__jakt_var_44 = return_statement; goto __jakt_label_39;

}
__jakt_label_39:; __jakt_var_44.release_value(); }));
};/*case end*/
case 86 /* Mut */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_47; {
bool const is_mutable = ((((*this).current())).__jakt_init_index() == 86 /* Mut */);
((((*this).index)++));
JaktInternal::DynamicArray<parser::ParsedVarDecl> vars = DynamicArray<parser::ParsedVarDecl>::create_with({});
bool is_destructuring_assingment = false;
ByteString tuple_var_name = (ByteString::from_utf8_without_validation(""sv));
parser::ParsedVarDecl tuple_var_decl = parser::ParsedVarDecl((ByteString::from_utf8_without_validation(""sv)),parser::ParsedType::Empty(JaktInternal::OptionalNone()),is_mutable,JaktInternal::OptionalNone(),((((*this).current())).span()),JaktInternal::OptionalNone());
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
(vars = ((((*this).parse_destructuring_assignment(is_mutable))).var_decls));
{
JaktInternal::ArrayIterator<parser::ParsedVarDecl> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedVarDecl> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedVarDecl var = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(tuple_var_name,((var).name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(tuple_var_name,(ByteString::from_utf8_without_validation("_"sv)));
}

}
}

(((tuple_var_decl).name) = tuple_var_name);
(is_destructuring_assingment = true);
}
else {
(tuple_var_decl = ((*this).parse_variable_declaration(is_mutable)));
}

NonnullRefPtr<typename parser::ParsedExpression> const init = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedStatement>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* Equal */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_48; {
((((*this).index)++));
__jakt_var_48 = ((*this).parse_expression(false,false)); goto __jakt_label_43;

}
__jakt_label_43:; __jakt_var_48.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_49; {
((*this).error((ByteString::from_utf8_without_validation("Expected initializer"sv)),((((*this).current())).span())));
__jakt_var_49 = parser::ParsedExpression::Garbage(((((*this).current())).span())); goto __jakt_label_44;

}
__jakt_label_44:; __jakt_var_49.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename parser::ParsedStatement> return_statement = parser::ParsedStatement::VarDecl(tuple_var_decl,init,parser::merge_spans(start,((((*this).previous())).span())));
if (is_destructuring_assingment){
NonnullRefPtr<typename parser::ParsedStatement> const old_return_statement = return_statement;
(return_statement = parser::ParsedStatement::DestructuringAssignment(vars,old_return_statement,parser::merge_spans(start,((((*this).previous())).span()))));
}
__jakt_var_47 = return_statement; goto __jakt_label_42;

}
__jakt_label_42:; __jakt_var_47.release_value(); }));
};/*case end*/
case 77 /* If */: {
return JaktInternal::ExplicitValue(((*this).parse_if_statement()));
};/*case end*/
case 74 /* For */: {
return JaktInternal::ExplicitValue(((*this).parse_for_statement()));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_50; {
parser::ParsedBlock const block = ((*this).parse_block());
__jakt_var_50 = parser::ParsedStatement::Block(block,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_45;

}
__jakt_label_45:; __jakt_var_50.release_value(); }));
};/*case end*/
case 109 /* Guard */: {
return JaktInternal::ExplicitValue(((*this).parse_guard_statement()));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_51; {
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(true,false));
__jakt_var_51 = parser::ParsedStatement::Expression(expr,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_46;

}
__jakt_label_46:; __jakt_var_51.release_value(); }));
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

NonnullRefPtr<typename parser::ParsedStatement> parser::Parser::parse_guard_statement() {
{
utility::Span const span = ((((*this).current())).span());
((((*this).index)++));
bool const previous_can_have_trailing_closure = ((*this).can_have_trailing_closure);
(((*this).can_have_trailing_closure) = false);
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,true));
(((*this).can_have_trailing_closure) = previous_can_have_trailing_closure);
if (((((*this).current())).__jakt_init_index() == 70 /* Else */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected `else` keyword"sv)),((((*this).current())).span())));
}

parser::ParsedBlock const else_block = ((*this).parse_block());
parser::ParsedBlock remaining_code = parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({}));
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedStatement>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
return parser::ParsedStatement::Guard(expr,else_block,remaining_code,span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Semicolon */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((((remaining_code).stmts)).push(((*this).parse_statement(true))));
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
return parser::ParsedStatement::Guard(expr,else_block,remaining_code,span);
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_try_block() {
{
utility::Span const start_span = ((((*this).current())).span());
NonnullRefPtr<typename parser::ParsedStatement> const stmt = ((*this).parse_statement(false));
ByteString error_name = (ByteString::from_utf8_without_validation(""sv));
utility::Span error_span = ((((*this).current())).span());
if (((((*this).current())).__jakt_init_index() == 64 /* Catch */)){
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
(error_span = ((((*this).current())).span()));
(error_name = name);
((((*this).index)++));
}
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘catch’"sv)),((((*this).current())).span())));
}

parser::ParsedBlock const catch_block = ((*this).parse_block());
return parser::ParsedExpression::TryBlock(stmt,error_name,error_span,catch_block,parser::merge_spans(start_span,((((*this).previous())).span())));
}
}

NonnullRefPtr<typename parser::ParsedStatement> parser::Parser::parse_for_statement() {
{
utility::Span const start_span = ((((*this).current())).span());
((((*this).index)++));
ByteString iterator_name = (ByteString::from_utf8_without_validation(""sv));
JaktInternal::DynamicArray<parser::ParsedVarDecl> destructured_var_decls = DynamicArray<parser::ParsedVarDecl>::create_with({});
utility::Span name_span = ((((*this).current())).span());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedStatement>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
{
(iterator_name = name);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7 /* LParen */: {
{
parser::ParsedVarDeclTuple const destructured_assignment = ((*this).parse_destructuring_assignment(false));
(destructured_var_decls = ((destructured_assignment).var_decls));
ByteString tuple_var_name = (ByteString::from_utf8_without_validation(""sv));
{
JaktInternal::ArrayIterator<parser::ParsedVarDecl> _magic = ((destructured_var_decls).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedVarDecl> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedVarDecl var = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(tuple_var_name,((var).name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(tuple_var_name,(ByteString::from_utf8_without_validation("__"sv)));
}

}
}

(name_span = ((destructured_assignment).span));
(iterator_name = tuple_var_name);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected iterator name or destructuring pattern"sv)),((((*this).current())).span())));
return parser::ParsedStatement::Garbage(parser::merge_spans(start_span,((((*this).current())).span())));
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
if (((((*this).current())).__jakt_init_index() == 80 /* In */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘in’"sv)),((((*this).current())).span())));
return parser::ParsedStatement::Garbage(parser::merge_spans(start_span,((((*this).current())).span())));
}

bool const previous_can_have_trailing_closure = ((*this).can_have_trailing_closure);
(((*this).can_have_trailing_closure) = false);
NonnullRefPtr<typename parser::ParsedExpression> const range = ((*this).parse_expression(false,false));
(((*this).can_have_trailing_closure) = previous_can_have_trailing_closure);
bool is_destructuring = false;
parser::ParsedBlock block = ((*this).parse_block());
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((destructured_var_decls).size()),static_cast<size_t>(0ULL))){
(is_destructuring = true);
ByteString tuple_var_name = (ByteString::from_utf8_without_validation("jakt__"sv));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(tuple_var_name,iterator_name);
parser::ParsedVarDecl tuple_var_decl = parser::ParsedVarDecl(tuple_var_name,parser::ParsedType::Empty(JaktInternal::OptionalNone()),false,JaktInternal::OptionalNone(),((((*this).current())).span()),JaktInternal::OptionalNone());
NonnullRefPtr<typename parser::ParsedExpression> const init = parser::ParsedExpression::Var(iterator_name,parser::merge_spans(start_span,((((*this).previous())).span())));
NonnullRefPtr<typename parser::ParsedStatement> const var_decl = parser::ParsedStatement::VarDecl(tuple_var_decl,init,parser::merge_spans(start_span,((((*this).previous())).span())));
NonnullRefPtr<typename parser::ParsedStatement> const destructured_vars_stmt = parser::ParsedStatement::DestructuringAssignment(destructured_var_decls,var_decl,parser::merge_spans(start_span,((((*this).previous())).span())));
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>> block_stmts = DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({});
((block_stmts).push(destructured_vars_stmt));
((block_stmts).push_values(((((block).stmts)))));
(((block).stmts) = block_stmts);
}
return parser::ParsedStatement::For(iterator_name,name_span,is_destructuring,range,block,parser::merge_spans(start_span,((((*this).previous())).span())));
}
}

NonnullRefPtr<typename parser::ParsedStatement> parser::Parser::parse_if_statement() {
{
if ((!(((((*this).current())).__jakt_init_index() == 77 /* If */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘if’ statement"sv)),((((*this).current())).span())));
return parser::ParsedStatement::Garbage(((((*this).current())).span()));
}
utility::Span const start_span = ((((*this).current())).span());
((((*this).index)++));
bool const previous_can_have_trailing_closure = ((*this).can_have_trailing_closure);
(((*this).can_have_trailing_closure) = false);
NonnullRefPtr<typename parser::ParsedExpression> const condition = ((*this).parse_expression(false,true));
(((*this).can_have_trailing_closure) = previous_can_have_trailing_closure);
parser::ParsedBlock const then_block = ((*this).parse_block());
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> else_statement = JaktInternal::OptionalNone();
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 70 /* Else */)){
((((*this).index)++));
((*this).skip_newlines());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedStatement>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 77 /* If */: {
{
(else_statement = ((*this).parse_if_statement()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
{
parser::ParsedBlock const block = ((*this).parse_block());
if (((then_block).equals(block))){
((*this).error((ByteString::from_utf8_without_validation("if and else have identical blocks"sv)),((((*this).current())).span())));
}
(else_statement = parser::ParsedStatement::Block(block,parser::merge_spans(start_span,((((*this).previous())).span()))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("‘else’ missing ‘if’ or block"sv)),((((*this).previous())).span())));
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
return parser::ParsedStatement::If(condition,then_block,else_statement,parser::merge_spans(start_span,((((*this).previous())).span())));
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_expression(bool const allow_assignments,bool const allow_newlines) {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> expr_stack = DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>>::create_with({});
i64 last_precedence = static_cast<i64>(1000000LL);
NonnullRefPtr<typename parser::ParsedExpression> const lhs = ((*this).parse_operand());
((expr_stack).push(lhs));
for (;;){
if (allow_newlines){
if ((((*this).eof()) || ((((*this).current())).__jakt_init_index() == 9 /* LCurly */))){
break;
}
((*this).skip_newlines());
}
else {
if (((*this).eol())){
break;
}
}

NonnullRefPtr<typename parser::ParsedExpression> const parsed_operator = ((*this).parse_operator(allow_assignments));
if (((parsed_operator)->__jakt_init_index() == 30 /* Garbage */)){
break;
}
i64 const precedence = ((parsed_operator)->precedence());
((*this).skip_newlines());
NonnullRefPtr<typename parser::ParsedExpression> const rhs = ((*this).parse_operand());
while (([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(precedence,last_precedence) && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((expr_stack).size()),static_cast<size_t>(1ULL)))){
NonnullRefPtr<typename parser::ParsedExpression> const rhs = (((expr_stack).pop()).value());
NonnullRefPtr<typename parser::ParsedExpression> const op = (((expr_stack).pop()).value());
(last_precedence = ((op)->precedence()));
if ([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(last_precedence,precedence)){
((expr_stack).push(op));
((expr_stack).push(rhs));
break;
}
NonnullRefPtr<typename parser::ParsedExpression> const lhs = (((expr_stack).pop()).value());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = *op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;parser::BinaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
{
utility::Span const new_span = parser::merge_spans(((lhs)->span()),((rhs)->span()));
((expr_stack).push(parser::ParsedExpression::BinaryOp(lhs,op,rhs,new_span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("operator is not an operator"sv))));
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
((expr_stack).push(parsed_operator));
((expr_stack).push(rhs));
(last_precedence = precedence);
}
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((expr_stack).size()),static_cast<size_t>(1ULL))){
NonnullRefPtr<typename parser::ParsedExpression> const rhs = (((expr_stack).pop()).value());
NonnullRefPtr<typename parser::ParsedExpression> const parsed_operator = (((expr_stack).pop()).value());
NonnullRefPtr<typename parser::ParsedExpression> const lhs = (((expr_stack).pop()).value());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = *parsed_operator;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;parser::BinaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
{
utility::Span const new_span = parser::merge_spans(((lhs)->span()),((rhs)->span()));
((expr_stack).push(parser::ParsedExpression::BinaryOp(lhs,op,rhs,new_span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("operator is not an operator"sv))));
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
return ((expr_stack)[static_cast<i64>(0LL)]);
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_operand_base() {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_52; {
__jakt_var_52 = parser::ParsedExpression::Var((ByteString::from_utf8_without_validation("this"sv)),span); goto __jakt_label_47;

}
__jakt_label_47:; __jakt_var_52.release_value(); }));
};/*case end*/
case 85 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_53; {
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
utility::Span const span = parser::merge_spans(start,((expr)->span()));
__jakt_var_53 = parser::ParsedExpression::Must(expr,span); goto __jakt_label_48;

}
__jakt_label_48:; __jakt_var_53.release_value(); }));
};/*case end*/
case 103 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_54; {
((((*this).index)++));
__jakt_var_54 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(((*this).parse_try_block()));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_55; {
NonnullRefPtr<typename parser::ParsedExpression> const expression = ((*this).parse_expression(true,true));
JaktInternal::Optional<parser::ParsedBlock> catch_block = JaktInternal::OptionalNone();
JaktInternal::Optional<ByteString> catch_name = JaktInternal::OptionalNone();
JaktInternal::Optional<utility::Span> catch_span = JaktInternal::OptionalNone();
if (((((*this).current())).__jakt_init_index() == 64 /* Catch */)){
(catch_span = ((((*this).current())).span()));
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
(catch_name = name);
((((*this).index)++));
}
(catch_block = ((*this).parse_block()));
}
__jakt_var_55 = parser::ParsedExpression::Try(expression,catch_block,catch_span,catch_name,span); goto __jakt_label_50;

}
__jakt_label_50:; __jakt_var_55.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_49;

}
__jakt_label_49:; __jakt_var_54.release_value(); }));
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& quote = __jakt_match_value.quote;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_56; {
((((*this).index)++));
__jakt_var_56 = parser::ParsedExpression::QuotedString(quote,span); goto __jakt_label_51;

}
__jakt_label_51:; __jakt_var_56.release_value(); }));
};/*case end*/
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;ByteString const& quote = __jakt_match_value.quote;
JaktInternal::Optional<ByteString> const& prefix = __jakt_match_value.prefix;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_57; {
((((*this).index)++));
__jakt_var_57 = parser::ParsedExpression::SingleQuotedString(quote,prefix,span); goto __jakt_label_52;

}
__jakt_label_52:; __jakt_var_57.release_value(); }));
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;lexer::LiteralPrefix const& prefix = __jakt_match_value.prefix;
ByteString const& number = __jakt_match_value.number;
lexer::LiteralSuffix const& suffix = __jakt_match_value.suffix;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(((*this).parse_number(prefix,number,suffix,span)));
};/*case end*/
case 102 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_58; {
((((*this).index)++));
__jakt_var_58 = parser::ParsedExpression::Boolean(true,span); goto __jakt_label_53;

}
__jakt_label_53:; __jakt_var_58.release_value(); }));
};/*case end*/
case 73 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_59; {
((((*this).index)++));
__jakt_var_59 = parser::ParsedExpression::Boolean(false,span); goto __jakt_label_54;

}
__jakt_label_54:; __jakt_var_59.release_value(); }));
};/*case end*/
case 99 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_60; {
((((*this).index)++));
__jakt_var_60 = parser::ParsedExpression::Var((ByteString::from_utf8_without_validation("this"sv)),span); goto __jakt_label_55;

}
__jakt_label_55:; __jakt_var_60.release_value(); }));
};/*case end*/
case 88 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_61; {
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
utility::Span const span = parser::merge_spans(start,((expr)->span()));
__jakt_var_61 = parser::ParsedExpression::UnaryOp(expr,parser::UnaryOperator::LogicalNot(),span); goto __jakt_label_56;

}
__jakt_label_56:; __jakt_var_61.release_value(); }));
};/*case end*/
case 46 /* Tilde */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Tilde;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_62; {
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
utility::Span const span = parser::merge_spans(start,((expr)->span()));
__jakt_var_62 = parser::ParsedExpression::UnaryOp(expr,parser::UnaryOperator::BitwiseNot(),span); goto __jakt_label_57;

}
__jakt_label_57:; __jakt_var_62.release_value(); }));
};/*case end*/
case 97 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_63; {
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedType> const parsed_type = ((*this).parse_typename());
utility::Span const span = parser::merge_spans(start,((parsed_type)->span()));
__jakt_var_63 = parser::ParsedExpression::UnaryOp(parser::ParsedExpression::Garbage(span),parser::UnaryOperator::Sizeof(parsed_type),span); goto __jakt_label_58;

}
__jakt_label_58:; __jakt_var_63.release_value(); }));
};/*case end*/
case 94 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_64; {
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedType> const type = ((*this).parse_typename());
utility::Span const span = parser::merge_spans(start,((type)->span()));
__jakt_var_64 = parser::ParsedExpression::Reflect(type,span); goto __jakt_label_59;

}
__jakt_label_59:; __jakt_var_64.release_value(); }));
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_65; {
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 7 /* LParen */)){
if (((name) == ((ByteString::from_utf8_without_validation("Some"sv))))){
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
return parser::ParsedExpression::OptionalSome(expr,span);
}
JaktInternal::Optional<parser::ParsedCall> const call = ((*this).parse_call());
return parser::ParsedExpression::Call((call.value()),span);
}
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 28 /* LessThan */)){
(((((*this).compiler))->ignore_parser_errors) = true);
JaktInternal::Optional<parser::ParsedCall> const call = ((*this).parse_call());
(((((*this).compiler))->ignore_parser_errors) = false);
if ((!(((call).has_value())))){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>> {
auto __jakt_enum_value = (name);
if (__jakt_enum_value == "None"sv) {
return JaktInternal::ExplicitValue(parser::ParsedExpression::OptionalNone(span));
}
else {
return JaktInternal::ExplicitValue(parser::ParsedExpression::Var(name,span));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return parser::ParsedExpression::Call((call.value()),span);
}
((((*this).index)++));
if (((name) == ((ByteString::from_utf8_without_validation("None"sv))))){
return parser::ParsedExpression::OptionalNone(span);
}
__jakt_var_65 = parser::ParsedExpression::Var(name,span); goto __jakt_label_60;

}
__jakt_label_60:; __jakt_var_65.release_value(); }));
};/*case end*/
case 7 /* LParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LParen;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_66; {
utility::Span const start_span = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> expr = ((*this).parse_expression(false,false));
((*this).skip_newlines());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> tuple_exprs = DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>>::create_with({expr});
utility::Span end_span = start_span;
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
(end_span = ((expr)->span()));
((tuple_exprs).push(expr));
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
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Expected ')'"sv)),((((*this).current())).span())));
}
(expr = parser::ParsedExpression::JaktTuple(tuple_exprs,parser::merge_spans(start_span,end_span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected ')'"sv)),((((*this).current())).span())));
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
__jakt_var_66 = expr; goto __jakt_label_61;

}
__jakt_label_61:; __jakt_var_66.release_value(); }));
};/*case end*/
case 18 /* PlusPlus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusPlus;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_67; {
parser::UnaryOperator const op = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::UnaryOperator, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* PlusPlus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::PreIncrement());
};/*case end*/
case 20 /* MinusMinus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::PreDecrement());
};/*case end*/
case 15 /* Minus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::Negate());
};/*case end*/
default: {
{
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("unreachable"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
utility::Span const span = parser::merge_spans(start,((expr)->span()));
__jakt_var_67 = parser::ParsedExpression::UnaryOp(expr,op,span); goto __jakt_label_62;

}
__jakt_label_62:; __jakt_var_67.release_value(); }));
};/*case end*/
case 20 /* MinusMinus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusMinus;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_68; {
parser::UnaryOperator const op = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::UnaryOperator, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* PlusPlus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::PreIncrement());
};/*case end*/
case 20 /* MinusMinus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::PreDecrement());
};/*case end*/
case 15 /* Minus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::Negate());
};/*case end*/
default: {
{
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("unreachable"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
utility::Span const span = parser::merge_spans(start,((expr)->span()));
__jakt_var_68 = parser::ParsedExpression::UnaryOp(expr,op,span); goto __jakt_label_63;

}
__jakt_label_63:; __jakt_var_68.release_value(); }));
};/*case end*/
case 15 /* Minus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Minus;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_69; {
parser::UnaryOperator const op = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::UnaryOperator, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* PlusPlus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::PreIncrement());
};/*case end*/
case 20 /* MinusMinus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::PreDecrement());
};/*case end*/
case 15 /* Minus */: {
return JaktInternal::ExplicitValue(parser::UnaryOperator::Negate());
};/*case end*/
default: {
{
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("unreachable"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
utility::Span const span = parser::merge_spans(start,((expr)->span()));
__jakt_var_69 = parser::ParsedExpression::UnaryOp(expr,op,span); goto __jakt_label_64;

}
__jakt_label_64:; __jakt_var_69.release_value(); }));
};/*case end*/
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_70; {
__jakt_var_70 = ((*this).parse_array_or_dictionary_literal()); goto __jakt_label_65;

}
__jakt_label_65:; __jakt_var_70.release_value(); }));
};/*case end*/
case 84 /* Match */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_71; {
__jakt_var_71 = ((*this).parse_match_expression()); goto __jakt_label_66;

}
__jakt_label_66:; __jakt_var_71.release_value(); }));
};/*case end*/
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_72; {
__jakt_var_72 = ((*this).parse_set_literal()); goto __jakt_label_67;

}
__jakt_label_67:; __jakt_var_72.release_value(); }));
};/*case end*/
case 37 /* Ampersand */: {
return JaktInternal::ExplicitValue(((*this).parse_ampersand()));
};/*case end*/
case 36 /* Asterisk */: {
return JaktInternal::ExplicitValue(((*this).parse_asterisk()));
};/*case end*/
case 75 /* Fn */: {
return JaktInternal::ExplicitValue(((*this).parse_lambda()));
};/*case end*/
case 54 /* DotDot */: {
return JaktInternal::ExplicitValue(((*this).parse_range()));
};/*case end*/
case 104 /* Unsafe */: {
return JaktInternal::ExplicitValue(((*this).parse_unsafe_expr()));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_73; {
utility::Span const span = ((((*this).current())).span());
((((*this).index)++));
((*this).error((ByteString::from_utf8_without_validation("Unsupported expression"sv)),span));
__jakt_var_73 = parser::ParsedExpression::Garbage(span); goto __jakt_label_68;

}
__jakt_label_68:; __jakt_var_73.release_value(); }));
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

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_number(lexer::LiteralPrefix const prefix,ByteString const number,lexer::LiteralSuffix suffix,utility::Span const span) {
{
((((*this).index)++));
u64 total = static_cast<u64>(0ULL);
if ((!(((prefix).__jakt_init_index() == 0 /* None */)))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = prefix;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Hexadecimal */: {
{
if (((((number).length())) == (static_cast<size_t>(0ULL)))){
((*this).error(__jakt_format((StringView::from_string_literal("Could not parse hexadecimal number due to no digits"sv))),span));
return parser::ParsedExpression::Garbage(span);
}
{
DeprecatedStringCodePointIterator _magic = ((number).code_points());
for (;;){
JaktInternal::Optional<u32> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u32 cp = (_magic_value.value());
{
u8 const byte = as_saturated<u8, u32>(cp);
if (((byte) != (static_cast<u8>(u8'_')))){
u8 offset = static_cast<u8>(0);
if (([](u8 const& self, u8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(byte,static_cast<u8>(u8'a')) && [](u8 const& self, u8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(byte,static_cast<u8>(u8'z')))){
(offset = static_cast<u8>(39));
}
else if (([](u8 const& self, u8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(byte,static_cast<u8>(u8'A')) && [](u8 const& self, u8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(byte,static_cast<u8>(u8'Z')))){
(offset = static_cast<u8>(7));
}
u8 const value = JaktInternal::checked_sub(byte,offset);
u64 const digit = as_saturated<u64, u8>(JaktInternal::checked_sub(value,static_cast<u8>(u8'0')));
(total = JaktInternal::checked_add(JaktInternal::checked_mul(total,static_cast<u64>(16ULL)),digit));
}
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Octal */: {
{
if (((((number).length())) == (static_cast<size_t>(0ULL)))){
((*this).error(__jakt_format((StringView::from_string_literal("Could not parse octal number due to no digits"sv))),span));
return parser::ParsedExpression::Garbage(span);
}
{
DeprecatedStringCodePointIterator _magic = ((number).code_points());
for (;;){
JaktInternal::Optional<u32> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u32 cp = (_magic_value.value());
{
u8 const byte = as_saturated<u8, u32>(cp);
if (((byte) != (static_cast<u8>(u8'_')))){
u64 const digit = as_saturated<u64, u8>(JaktInternal::checked_sub(byte,static_cast<u8>(u8'0')));
(total = JaktInternal::checked_add(JaktInternal::checked_mul(total,static_cast<u64>(8ULL)),digit));
}
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Binary */: {
{
if (((((number).length())) == (static_cast<size_t>(0ULL)))){
((*this).error(__jakt_format((StringView::from_string_literal("Could not parse binary number due to no digits"sv))),span));
return parser::ParsedExpression::Garbage(span);
}
{
DeprecatedStringCodePointIterator _magic = ((number).code_points());
for (;;){
JaktInternal::Optional<u32> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u32 cp = (_magic_value.value());
{
u8 const byte = as_saturated<u8, u32>(cp);
if (((byte) != (static_cast<u8>(u8'_')))){
u64 const digit = as_saturated<u64, u8>(JaktInternal::checked_sub(byte,static_cast<u8>(u8'0')));
(total = JaktInternal::checked_add(JaktInternal::checked_mul(total,static_cast<u64>(2ULL)),digit));
}
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* None */: {
{
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
JaktInternal::Optional<parser::NumericConstant> const constant_value = ((*this).make_integer_numeric_constant(total,suffix,span));
if (((constant_value).has_value())){
return parser::ParsedExpression::NumericConstant((constant_value.value()),span);
}
return parser::ParsedExpression::Garbage(span);
}
bool number_too_large = false;
bool floating = false;
u64 fraction_nominator = static_cast<u64>(0ULL);
u64 fraction_denominator = static_cast<u64>(1ULL);
if (((((number).length())) == (static_cast<size_t>(0ULL)))){
((*this).error(__jakt_format((StringView::from_string_literal("Could not parse number due to no digits"sv))),span));
return parser::ParsedExpression::Garbage(span);
}
{
DeprecatedStringCodePointIterator _magic = ((number).code_points());
for (;;){
JaktInternal::Optional<u32> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u32 cp = (_magic_value.value());
{
u8 const byte = as_saturated<u8, u32>(cp);
if (((byte) != (static_cast<u8>(u8'_')))){
if (((byte) == (static_cast<u8>(u8'.')))){
(floating = true);
continue;
}
u64 const digit = as_saturated<u64, u8>(JaktInternal::checked_sub(byte,static_cast<u8>(u8'0')));
if (floating){
(fraction_nominator = JaktInternal::checked_add(JaktInternal::checked_mul(fraction_nominator,static_cast<u64>(10ULL)),digit));
((fraction_denominator) *= (static_cast<u64>(10ULL)));
}
else {
u64 const old_total = total;
(total = unchecked_add<u64>(unchecked_mul<u64>(total,static_cast<u64>(10ULL)),digit));
if ([](u64 const& self, u64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(total,old_total)){
(number_too_large = true);
}
}

}
}

}
}

if (number_too_large){
((*this).error(__jakt_format((StringView::from_string_literal("Integer literal too large"sv))),span));
return parser::ParsedExpression::Garbage(span);
}
if ((floating && ((suffix).__jakt_init_index() == 0 /* None */))){
(suffix = lexer::LiteralSuffix::F64());
}
bool const is_float_suffix = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = suffix;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 11 /* F64 */: {
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
if ((floating && (!(is_float_suffix)))){
return parser::ParsedExpression::Garbage(span);
}
JaktInternal::Optional<parser::NumericConstant> const constant_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<parser::NumericConstant>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = suffix;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<parser::NumericConstant>> __jakt_var_74; {
f64 const number = ((parser::u64_to_float<f64>(total)) + (((parser::u64_to_float<f64>(fraction_nominator)) / (parser::u64_to_float<f64>(fraction_denominator)))));
__jakt_var_74 = ((*this).make_float_numeric_constant(number,suffix,span)); goto __jakt_label_69;

}
__jakt_label_69:; __jakt_var_74.release_value(); }));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<parser::NumericConstant>> __jakt_var_75; {
f64 const number = ((parser::u64_to_float<f64>(total)) + (((parser::u64_to_float<f64>(fraction_nominator)) / (parser::u64_to_float<f64>(fraction_denominator)))));
__jakt_var_75 = ((*this).make_float_numeric_constant(number,suffix,span)); goto __jakt_label_70;

}
__jakt_label_70:; __jakt_var_75.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).make_integer_numeric_constant(total,suffix,span)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((constant_value).has_value())){
return parser::ParsedExpression::NumericConstant((constant_value.value()),span);
}
return parser::ParsedExpression::Garbage(span);
}
}

JaktInternal::Optional<parser::NumericConstant> parser::Parser::make_integer_numeric_constant(u64 const number,lexer::LiteralSuffix const suffix,utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Optional<parser::NumericConstant>>{
auto&& __jakt_match_variant = suffix;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* None */: {
{
JaktInternal::Optional<i64> const n = (fallible_integer_cast<i64>((number)));
if (((n).has_value())){
return parser::NumericConstant::UnknownSigned((n.value()));
}
return parser::NumericConstant::UnknownUnsigned(number);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* U8 */: {
{
JaktInternal::Optional<u8> const n = (fallible_integer_cast<u8>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::U8((n.value()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* U16 */: {
{
JaktInternal::Optional<u16> const n = (fallible_integer_cast<u16>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::U16((n.value()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* U32 */: {
{
JaktInternal::Optional<u32> const n = (fallible_integer_cast<u32>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::U32((n.value()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* U64 */: {
{
JaktInternal::Optional<u64> const n = (fallible_integer_cast<u64>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::U64((n.value()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* UZ */: {
{
JaktInternal::Optional<size_t> const n = (fallible_integer_cast<size_t>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::USize((infallible_integer_cast<u64>(((n.value())))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* I8 */: {
{
JaktInternal::Optional<i8> const n = (fallible_integer_cast<i8>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::I8((n.value()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7 /* I16 */: {
{
JaktInternal::Optional<i16> const n = (fallible_integer_cast<i16>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::I16((n.value()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* I32 */: {
{
JaktInternal::Optional<i32> const n = (fallible_integer_cast<i32>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::I32((n.value()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* I64 */: {
{
JaktInternal::Optional<i64> const n = (fallible_integer_cast<i64>((number)));
if ((!(((n).has_value())))){
((*this).error(__jakt_format((StringView::from_string_literal("Number {} cannot fit in integer type {}"sv)),number,suffix),span));
return parser::NumericConstant::U64(number);
}
return parser::NumericConstant::I64((n.value()));
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
return JaktInternal::OptionalNone();
}
}

JaktInternal::Optional<parser::NumericConstant> parser::Parser::make_float_numeric_constant(f64 const number,lexer::LiteralSuffix const suffix,utility::Span const span) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<parser::NumericConstant>, JaktInternal::Optional<parser::NumericConstant>>{
auto&& __jakt_match_variant = suffix;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(parser::NumericConstant::F32(parser::f64_to_f32(number)));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(parser::NumericConstant::F64(number));
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
});
}
}

JaktInternal::DynamicArray<parser::ParsedCapture> parser::Parser::parse_captures() {
{
JaktInternal::DynamicArray<parser::ParsedCapture> captures = DynamicArray<parser::ParsedCapture>::create_with({});
if (((((*this).current())).__jakt_init_index() == 11 /* LSquare */)){
((((*this).index)++));
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::DynamicArray<parser::ParsedCapture>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 37 /* Ampersand */: {
{
((((*this).index)++));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::DynamicArray<parser::ParsedCapture>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 86 /* Mut */: {
{
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
((captures).push(parser::ParsedCapture::ByMutableReference(name,((((*this).current())).span()))));
((((*this).index)++));
}
else {
((*this).error(__jakt_format((StringView::from_string_literal("Expected identifier, got '{}'"sv)),((*this).current())),((((*this).current())).span())));
((((*this).index)++));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
{
((captures).push(parser::ParsedCapture::ByReference(name,((((*this).current())).span()))));
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error(__jakt_format((StringView::from_string_literal("Expected identifier or mut, got '{}'"sv)),((*this).current())),((((*this).current())).span())));
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
{
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
((captures).push(parser::ParsedCapture::ByComptimeDependency(name,((((*this).current())).span()))));
((((*this).index)++));
}
else {
((*this).error(__jakt_format((StringView::from_string_literal("Expected identifier, got '{}'"sv)),((*this).current())),((((*this).current())).span())));
((((*this).index)++));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
{
((captures).push(parser::ParsedCapture::ByValue(name,((((*this).current())).span()))));
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* This */: {
{
((captures).push(parser::ParsedCapture::ByValue((ByteString::from_utf8_without_validation("this"sv)),((((*this).current())).span()))));
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error(__jakt_format((StringView::from_string_literal("Unexpected token '{}' in captures list"sv)),((*this).current())),((((*this).current())).span())));
((((*this).index)++));
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
return captures;
}
else {
return DynamicArray<parser::ParsedCapture>::create_with({});
}

}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_lambda() {
{
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
JaktInternal::DynamicArray<parser::ParsedCapture> const captures = ((*this).parse_captures());
parser::ParsedFunctionParameters const fn_parameters = ((*this).parse_function_parameters(false));
bool const can_throw = ((((*this).current())).__jakt_init_index() == 101 /* Throws */);
if (can_throw){
((((*this).index)++));
}
if (((fn_parameters).has_varargs)){
((*this).error((ByteString::from_utf8_without_validation("Anonymous functions cannot have varargs"sv)),((((*this).current())).span())));
}
NonnullRefPtr<typename parser::ParsedType> return_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedType>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 58 /* Arrow */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedType>> __jakt_var_76; {
((((*this).index)++));
__jakt_var_76 = ((*this).parse_typename()); goto __jakt_label_71;

}
__jakt_label_71:; __jakt_var_76.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(parser::ParsedType::Empty(JaktInternal::OptionalNone()));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool is_fat_arrow = false;
parser::ParsedBlock const block = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::ParsedBlock, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 57 /* FatArrow */: {
return JaktInternal::ExplicitValue(({ Optional<parser::ParsedBlock> __jakt_var_77; {
(is_fat_arrow = true);
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(true,false));
utility::Span const span = ((expr)->span());
__jakt_var_77 = parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename parser::ParsedStatement>>::create_with({parser::ParsedStatement::Return(expr,span)})); goto __jakt_label_72;

}
__jakt_label_72:; __jakt_var_77.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((*this).parse_block()));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return parser::ParsedExpression::Function(captures,((fn_parameters).parameters),can_throw,is_fat_arrow,return_type,block,parser::merge_spans(start,((((*this).current())).span())));
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_asterisk() {
{
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
return parser::ParsedExpression::UnaryOp(expr,parser::UnaryOperator::Dereference(),parser::merge_spans(start,((((*this).current())).span())));
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_ampersand() {
{
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 93 /* Raw */)){
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
return parser::ParsedExpression::UnaryOp(expr,parser::UnaryOperator::RawAddress(),parser::merge_spans(start,((expr)->span())));
}
if (((((*this).current())).__jakt_init_index() == 86 /* Mut */)){
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
return parser::ParsedExpression::UnaryOp(expr,parser::UnaryOperator::MutableReference(),parser::merge_spans(start,((expr)->span())));
}
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
return parser::ParsedExpression::UnaryOp(expr,parser::UnaryOperator::Reference(),parser::merge_spans(start,((expr)->span())));
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_range() {
{
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> to = JaktInternal::OptionalNone();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(to = ((*this).parse_operand()));
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
return parser::ParsedExpression::Range(JaktInternal::OptionalNone(),to,parser::merge_spans(start,((((*this).current())).span())));
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_unsafe_expr() {
{
utility::Span const start = ((((*this).current())).span());
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_operand());
return parser::ParsedExpression::Unsafe(expr,parser::merge_spans(start,((expr)->span())));
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_set_literal() {
{
utility::Span const start = ((((*this).current())).span());
if ((!(((((*this).current())).__jakt_init_index() == 9 /* LCurly */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘{’"sv)),((((*this).current())).span())));
return parser::ParsedExpression::Garbage(((((*this).current())).span()));
}
((((*this).index)++));
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> output = DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>>::create_with({});
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RCurly */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
if (((expr)->__jakt_init_index() == 30 /* Garbage */)){
return JaktInternal::LoopBreak{};
}
((output).push(expr));
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
size_t const end = JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL));
if (([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(end,((((*this).tokens)).size())) || (!(((((((*this).tokens))[end])).__jakt_init_index() == 10 /* RCurly */))))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘}’ to close the set"sv)),((((((*this).tokens))[end])).span())));
}
return parser::ParsedExpression::Set(output,parser::merge_spans(start,((((((*this).tokens))[end])).span())));
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_operand() {
{
((*this).skip_newlines());
utility::Span const start = ((((*this).current())).span());
((*this).skip_newlines());
NonnullRefPtr<typename parser::ParsedExpression> expr = ((*this).parse_operand_base());
return ((*this).parse_operand_postfix_operator(start,expr));
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_operand_postfix_operator(utility::Span const start,NonnullRefPtr<typename parser::ParsedExpression> const expr) {
{
NonnullRefPtr<typename parser::ParsedExpression> result = expr;
for (;;){
(result = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 54 /* DotDot */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_78; {
((((*this).index)++));
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> to = JaktInternal::OptionalNone();
utility::Span span_end = ((((*this).current())).span());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(to = ((*this).parse_operand()));
(span_end = (((to.value()))->span()));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
__jakt_var_78 = parser::ParsedExpression::Range(result,to,parser::merge_spans(start,span_end)); goto __jakt_label_73;

}
__jakt_label_73:; __jakt_var_78.release_value(); }));
};/*case end*/
case 48 /* ExclamationPoint */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_79; {
((((*this).index)++));
__jakt_var_79 = parser::ParsedExpression::ForcedUnwrap(result,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_74;

}
__jakt_label_74:; __jakt_var_79.release_value(); }));
};/*case end*/
case 18 /* PlusPlus */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_80; {
((((*this).index)++));
__jakt_var_80 = parser::ParsedExpression::UnaryOp(result,parser::UnaryOperator::PostIncrement(),parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_75;

}
__jakt_label_75:; __jakt_var_80.release_value(); }));
};/*case end*/
case 20 /* MinusMinus */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_81; {
((((*this).index)++));
__jakt_var_81 = parser::ParsedExpression::UnaryOp(result,parser::UnaryOperator::PostDecrement(),parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_76;

}
__jakt_label_76:; __jakt_var_81.release_value(); }));
};/*case end*/
case 61 /* As */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_82; {
((((*this).index)++));
utility::Span const cast_span = parser::merge_spans(((((*this).previous())).span()),((((*this).current())).span()));
parser::TypeCast const cast = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::TypeCast, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 48 /* ExclamationPoint */: {
return JaktInternal::ExplicitValue(({ Optional<parser::TypeCast> __jakt_var_83; {
((((*this).index)++));
__jakt_var_83 = parser::TypeCast::Infallible(((*this).parse_typename())); goto __jakt_label_78;

}
__jakt_label_78:; __jakt_var_83.release_value(); }));
};/*case end*/
case 49 /* QuestionMark */: {
return JaktInternal::ExplicitValue(({ Optional<parser::TypeCast> __jakt_var_84; {
((((*this).index)++));
__jakt_var_84 = parser::TypeCast::Fallible(((*this).parse_typename())); goto __jakt_label_79;

}
__jakt_label_79:; __jakt_var_84.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<parser::TypeCast> __jakt_var_85; {
((*this).error_with_hint((ByteString::from_utf8_without_validation("Invalid cast syntax"sv)),cast_span,(ByteString::from_utf8_without_validation("Use `as!` for an infallible cast, or `as?` for a fallible cast"sv)),((((*this).previous())).span())));
__jakt_var_85 = parser::TypeCast::Fallible(((*this).parse_typename())); goto __jakt_label_80;

}
__jakt_label_80:; __jakt_var_85.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
utility::Span const span = parser::merge_spans(start,parser::merge_spans(cast_span,((((*this).current())).span())));
__jakt_var_82 = parser::ParsedExpression::UnaryOp(result,parser::UnaryOperator::TypeCast(cast),span); goto __jakt_label_77;

}
__jakt_label_77:; __jakt_var_82.release_value(); }));
};/*case end*/
case 81 /* Is */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_86; {
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedType> const parsed_type = ((*this).parse_typename());
utility::Span const span = parser::merge_spans(start,((((*this).current())).span()));
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> bindings = DynamicArray<parser::EnumVariantPatternArgument>::create_with({});
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> unary_operator_is = JaktInternal::OptionalNone();
if ((((((*this).current())).__jakt_init_index() == 7 /* LParen */) && (((parsed_type)->__jakt_init_index() == 1 /* NamespacedName */) || ((parsed_type)->__jakt_init_index() == 0 /* Name */)))){
(bindings = ((*this).parse_variant_arguments()));
(unary_operator_is = parser::ParsedExpression::UnaryOp(result,parser::UnaryOperator::IsEnumVariant(parsed_type,bindings),span));
}
else {
(unary_operator_is = parser::ParsedExpression::UnaryOp(result,parser::UnaryOperator::Is(parsed_type),span));
}

__jakt_var_86 = (unary_operator_is.value()); goto __jakt_label_81;

}
__jakt_label_81:; __jakt_var_86.release_value(); }));
};/*case end*/
case 6 /* ColonColon */: {
return JaktInternal::ExplicitValue(((*this).parse_postfix_colon_colon(start,result)));
};/*case end*/
case 49 /* QuestionMark */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_87; {
bool const is_optional = ((((*this).current())).__jakt_init_index() == 49 /* QuestionMark */);
if (is_optional){
((((*this).index)++));
if ((!(((((*this).current())).__jakt_init_index() == 53 /* Dot */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘.’ after ‘?’ for optional chaining access"sv)),((((*this).current())).span())));
}
}
((((*this).index)++));
__jakt_var_87 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;lexer::LiteralPrefix const& prefix = __jakt_match_value.prefix;
ByteString const& number = __jakt_match_value.number;
lexer::LiteralSuffix const& suffix = __jakt_match_value.suffix;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_88; {
NonnullRefPtr<typename parser::ParsedExpression> const numeric_constant = ((*this).parse_number(prefix,number,suffix,span));
__jakt_var_88 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>> {
auto __jakt_enum_value = (((numeric_constant)->__jakt_init_index() == 1 /* NumericConstant */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_89; {
parser::NumericConstant const val = (numeric_constant)->as.NumericConstant.val;
size_t const num = ((val).to_usize());
__jakt_var_89 = parser::ParsedExpression::IndexedTuple(result,num,is_optional,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_84;

}
__jakt_label_84:; __jakt_var_89.release_value(); }));
}
else {
{
((*this).error((ByteString::from_utf8_without_validation("Invalid Numeric Constant"sv)),span));
return expr;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}); goto __jakt_label_83;

}
__jakt_label_83:; __jakt_var_88.release_value(); }));
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_90; {
((((*this).index)++));
__jakt_var_90 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_91; {
size_t const original_index = ((*this).index);
JaktInternal::DynamicArray<error::JaktError> const existing_errors = ((((((((*this).compiler))->errors))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})])).to_array());
((((*this).index)--));
JaktInternal::Optional<parser::ParsedCall> const call = ((*this).parse_call());
__jakt_var_91 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>> {
auto __jakt_enum_value = (((call).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::ParsedExpression::MethodCall(result,(call.value()),is_optional,parser::merge_spans(start,((((*this).previous())).span()))));
}
else {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_92; {
(((*this).index) = original_index);
(((((*this).compiler))->errors) = existing_errors);
__jakt_var_92 = parser::ParsedExpression::IndexedStruct(result,name,is_optional,parser::merge_spans(start,((((*this).current())).span()))); goto __jakt_label_87;

}
__jakt_label_87:; __jakt_var_92.release_value(); }));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}); goto __jakt_label_86;

}
__jakt_label_86:; __jakt_var_91.release_value(); }));
};/*case end*/
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_93; {
((((*this).index)--));
JaktInternal::Optional<parser::ParsedCall> const call = ((*this).parse_call());
__jakt_var_93 = parser::ParsedExpression::MethodCall(result,(call.value()),is_optional,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_88;

}
__jakt_label_88:; __jakt_var_93.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(parser::ParsedExpression::IndexedStruct(result,name,is_optional,parser::merge_spans(start,((((*this).current())).span()))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}); goto __jakt_label_85;

}
__jakt_label_85:; __jakt_var_90.release_value(); }));
};/*case end*/
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_94; {
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const index = ((*this).parse_expression(false,false));
if ((!(((((*this).current())).__jakt_init_index() == 12 /* RSquare */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘]’ to close the index"sv)),((((*this).current())).span())));
}
((((*this).index)++));
__jakt_var_94 = parser::ParsedExpression::ComptimeIndex(result,index,is_optional,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_89;

}
__jakt_label_89:; __jakt_var_94.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_95; {
((*this).error((ByteString::from_utf8_without_validation("Unsupported dot operation"sv)),((((*this).current())).span())));
((((*this).index)++));
__jakt_var_95 = result; goto __jakt_label_90;

}
__jakt_label_90:; __jakt_var_95.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}); goto __jakt_label_82;

}
__jakt_label_82:; __jakt_var_87.release_value(); }));
};/*case end*/
case 53 /* Dot */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_96; {
bool const is_optional = ((((*this).current())).__jakt_init_index() == 49 /* QuestionMark */);
if (is_optional){
((((*this).index)++));
if ((!(((((*this).current())).__jakt_init_index() == 53 /* Dot */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘.’ after ‘?’ for optional chaining access"sv)),((((*this).current())).span())));
}
}
((((*this).index)++));
__jakt_var_96 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;lexer::LiteralPrefix const& prefix = __jakt_match_value.prefix;
ByteString const& number = __jakt_match_value.number;
lexer::LiteralSuffix const& suffix = __jakt_match_value.suffix;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_97; {
NonnullRefPtr<typename parser::ParsedExpression> const numeric_constant = ((*this).parse_number(prefix,number,suffix,span));
__jakt_var_97 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>> {
auto __jakt_enum_value = (((numeric_constant)->__jakt_init_index() == 1 /* NumericConstant */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_98; {
parser::NumericConstant const val = (numeric_constant)->as.NumericConstant.val;
size_t const num = ((val).to_usize());
__jakt_var_98 = parser::ParsedExpression::IndexedTuple(result,num,is_optional,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_93;

}
__jakt_label_93:; __jakt_var_98.release_value(); }));
}
else {
{
((*this).error((ByteString::from_utf8_without_validation("Invalid Numeric Constant"sv)),span));
return expr;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}); goto __jakt_label_92;

}
__jakt_label_92:; __jakt_var_97.release_value(); }));
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_99; {
((((*this).index)++));
__jakt_var_99 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* LessThan */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_100; {
size_t const original_index = ((*this).index);
JaktInternal::DynamicArray<error::JaktError> const existing_errors = ((((((((*this).compiler))->errors))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})])).to_array());
((((*this).index)--));
JaktInternal::Optional<parser::ParsedCall> const call = ((*this).parse_call());
__jakt_var_100 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>> {
auto __jakt_enum_value = (((call).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(parser::ParsedExpression::MethodCall(result,(call.value()),is_optional,parser::merge_spans(start,((((*this).previous())).span()))));
}
else {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_101; {
(((*this).index) = original_index);
(((((*this).compiler))->errors) = existing_errors);
__jakt_var_101 = parser::ParsedExpression::IndexedStruct(result,name,is_optional,parser::merge_spans(start,((((*this).current())).span()))); goto __jakt_label_96;

}
__jakt_label_96:; __jakt_var_101.release_value(); }));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}); goto __jakt_label_95;

}
__jakt_label_95:; __jakt_var_100.release_value(); }));
};/*case end*/
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_102; {
((((*this).index)--));
JaktInternal::Optional<parser::ParsedCall> const call = ((*this).parse_call());
__jakt_var_102 = parser::ParsedExpression::MethodCall(result,(call.value()),is_optional,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_97;

}
__jakt_label_97:; __jakt_var_102.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(parser::ParsedExpression::IndexedStruct(result,name,is_optional,parser::merge_spans(start,((((*this).current())).span()))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}); goto __jakt_label_94;

}
__jakt_label_94:; __jakt_var_99.release_value(); }));
};/*case end*/
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_103; {
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const index = ((*this).parse_expression(false,false));
if ((!(((((*this).current())).__jakt_init_index() == 12 /* RSquare */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘]’ to close the index"sv)),((((*this).current())).span())));
}
((((*this).index)++));
__jakt_var_103 = parser::ParsedExpression::ComptimeIndex(result,index,is_optional,parser::merge_spans(start,((((*this).previous())).span()))); goto __jakt_label_98;

}
__jakt_label_98:; __jakt_var_103.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_104; {
((*this).error((ByteString::from_utf8_without_validation("Unsupported dot operation"sv)),((((*this).current())).span())));
((((*this).index)++));
__jakt_var_104 = result; goto __jakt_label_99;

}
__jakt_label_99:; __jakt_var_104.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}); goto __jakt_label_91;

}
__jakt_label_91:; __jakt_var_96.release_value(); }));
};/*case end*/
case 11 /* LSquare */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_105; {
((((*this).index)++));
NonnullRefPtr<typename parser::ParsedExpression> const index_expr = ((*this).parse_expression(false,true));
if (((((*this).current())).__jakt_init_index() == 12 /* RSquare */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ']'"sv)),((((*this).current())).span())));
}

size_t const end = JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL));
__jakt_var_105 = parser::ParsedExpression::IndexedExpression(result,index_expr,parser::merge_spans(start,((((((*this).tokens))[end])).span()))); goto __jakt_label_100;

}
__jakt_label_100:; __jakt_var_105.release_value(); }));
};/*case end*/
default: {
{
return JaktInternal::LoopBreak{};
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
}));
}
return result;
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_postfix_colon_colon(utility::Span const start,NonnullRefPtr<typename parser::ParsedExpression> const expr) {
{
((((*this).index)++));
JaktInternal::DynamicArray<ByteString> namespace_ = DynamicArray<ByteString>::create_with({});
if (((expr)->__jakt_init_index() == 9 /* Var */)){
ByteString const name = (expr)->as.Var.name;
((namespace_).push(name));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected namespace"sv)),((expr)->span())));
}

while ((!(((*this).eof())))){
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const current_name = (((*this).current())).as.Identifier.name;
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
((((*this).index)--));
JaktInternal::Optional<parser::ParsedCall> call = ((*this).parse_call());
((((call.value())).namespace_) = namespace_);
return parser::ParsedExpression::Call((call.value()),parser::merge_spans(((expr)->span()),((((*this).current())).span())));
}
if (((((*this).current())).__jakt_init_index() == 28 /* LessThan */)){
((((*this).index)--));
JaktInternal::Optional<parser::ParsedCall> const maybe_call = ((*this).parse_call());
if (((maybe_call).has_value())){
parser::ParsedCall call = (maybe_call.value());
(((call).namespace_) = namespace_);
return parser::ParsedExpression::Call(call,parser::merge_spans(((expr)->span()),((((*this).current())).span())));
}
return parser::ParsedExpression::Garbage(((((*this).current())).span()));
}
if (((((*this).current())).__jakt_init_index() == 6 /* ColonColon */)){
if (((((*this).previous())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).previous())).as.Identifier.name;
((namespace_).push(name));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected namespace"sv)),((expr)->span())));
}

((((*this).index)++));
}
else {
return parser::ParsedExpression::NamespacedVar(current_name,namespace_,parser::merge_spans(start,((((*this).current())).span())));
}

}
else {
((*this).error((ByteString::from_utf8_without_validation("Unsupported static method call"sv)),((((*this).current())).span())));
return expr;
}

}
((*this).error((ByteString::from_utf8_without_validation("Incomplete static method call"sv)),((((*this).current())).span())));
return expr;
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_operator(bool const allow_assignments) {
{
utility::Span const span = ((((*this).current())).span());
parser::BinaryOperator const op = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::BinaryOperator, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 50 /* QuestionMarkQuestionMark */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::NoneCoalescing());
};/*case end*/
case 14 /* Plus */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::Add());
};/*case end*/
case 15 /* Minus */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::Subtract());
};/*case end*/
case 36 /* Asterisk */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::Multiply());
};/*case end*/
case 47 /* ForwardSlash */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::Divide());
};/*case end*/
case 13 /* PercentSign */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::Modulo());
};/*case end*/
case 59 /* And */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::LogicalAnd());
};/*case end*/
case 89 /* Or */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::LogicalOr());
};/*case end*/
case 25 /* DoubleEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::Equal());
};/*case end*/
case 24 /* NotEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::NotEqual());
};/*case end*/
case 28 /* LessThan */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::LessThan());
};/*case end*/
case 29 /* LessThanOrEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::LessThanOrEqual());
};/*case end*/
case 26 /* GreaterThan */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::GreaterThan());
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::GreaterThanOrEqual());
};/*case end*/
case 37 /* Ampersand */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseAnd());
};/*case end*/
case 39 /* AmpersandAmpersand */: {
return JaktInternal::ExplicitValue(({ Optional<parser::BinaryOperator> __jakt_var_106; {
((*this).error((ByteString::from_utf8_without_validation("‘&&’ is not allowed, use ‘and’ instead"sv)),span));
__jakt_var_106 = parser::BinaryOperator::LogicalAnd(); goto __jakt_label_101;

}
__jakt_label_101:; __jakt_var_106.release_value(); }));
};/*case end*/
case 40 /* Pipe */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseOr());
};/*case end*/
case 42 /* PipePipe */: {
return JaktInternal::ExplicitValue(({ Optional<parser::BinaryOperator> __jakt_var_107; {
((*this).error((ByteString::from_utf8_without_validation("‘||’ is not allowed, use ‘or’ instead"sv)),span));
__jakt_var_107 = parser::BinaryOperator::LogicalOr(); goto __jakt_label_102;

}
__jakt_label_102:; __jakt_var_107.release_value(); }));
};/*case end*/
case 43 /* Caret */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseXor());
};/*case end*/
case 31 /* LeftShift */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseLeftShift());
};/*case end*/
case 33 /* RightShift */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseRightShift());
};/*case end*/
case 30 /* LeftArithmeticShift */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::ArithmeticLeftShift());
};/*case end*/
case 34 /* RightArithmeticShift */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::ArithmeticRightShift());
};/*case end*/
case 16 /* Equal */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::Assign());
};/*case end*/
case 32 /* LeftShiftEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseLeftShiftAssign());
};/*case end*/
case 35 /* RightShiftEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseRightShiftAssign());
};/*case end*/
case 38 /* AmpersandEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseAndAssign());
};/*case end*/
case 41 /* PipeEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseOrAssign());
};/*case end*/
case 44 /* CaretEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::BitwiseXorAssign());
};/*case end*/
case 17 /* PlusEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::AddAssign());
};/*case end*/
case 19 /* MinusEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::SubtractAssign());
};/*case end*/
case 21 /* AsteriskEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::MultiplyAssign());
};/*case end*/
case 22 /* ForwardSlashEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::DivideAssign());
};/*case end*/
case 23 /* PercentSignEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::ModuloAssign());
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
return JaktInternal::ExplicitValue(parser::BinaryOperator::NoneCoalescingAssign());
};/*case end*/
default: {
{
return parser::ParsedExpression::Garbage(span);
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((((*this).index)++));
if (((!(allow_assignments)) && ((op).is_assignment()))){
((*this).error((ByteString::from_utf8_without_validation("Assignment is not allowed in this position"sv)),span));
return parser::ParsedExpression::Operator(op,span);
}
return parser::ParsedExpression::Operator(op,span);
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_match_expression() {
{
utility::Span start = ((((*this).current())).span());
((((*this).index)++));
bool const previous_can_have_trailing_closure = ((*this).can_have_trailing_closure);
(((*this).can_have_trailing_closure) = false);
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,true));
(((*this).can_have_trailing_closure) = previous_can_have_trailing_closure);
JaktInternal::DynamicArray<parser::ParsedMatchCase> const cases = ((*this).parse_match_cases());
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((cases).size()),static_cast<size_t>(1ULL))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(JaktInternal::checked_sub(((cases).size()),static_cast<size_t>(1ULL)))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(JaktInternal::checked_add(i,static_cast<size_t>(1ULL))),static_cast<size_t>(((cases).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t k = (_magic_value.value());
{
if (((((cases)[i])).has_equal_pattern(((cases)[k])))){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Duplicated match pattern"sv)),((((cases)[k])).marker_span),(ByteString::from_utf8_without_validation("Original pattern here"sv)),((((cases)[i])).marker_span)));
}
}

}
}

}

}
}

}
return parser::ParsedExpression::Match(expr,cases,parser::merge_spans(start,((((*this).previous())).span())),start);
}
}

JaktInternal::DynamicArray<parser::ParsedMatchCase> parser::Parser::parse_match_cases() {
{
JaktInternal::DynamicArray<parser::ParsedMatchCase> cases = DynamicArray<parser::ParsedMatchCase>::create_with({});
((*this).skip_newlines());
if ((!(((((*this).current())).__jakt_init_index() == 9 /* LCurly */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘{’"sv)),((((*this).current())).span())));
return cases;
}
((((*this).index)++));
((*this).skip_newlines());
while (((!(((*this).eof()))) && (!(((((*this).current())).__jakt_init_index() == 10 /* RCurly */))))){
utility::Span const marker_span = ((((*this).current())).span());
size_t const pattern_start_index = ((*this).index);
JaktInternal::DynamicArray<parser::ParsedMatchPattern> const patterns = ((*this).parse_match_patterns());
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 57 /* FatArrow */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘=>’"sv)),((((*this).current())).span())));
}

((*this).skip_newlines());
parser::ParsedMatchBody const body = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::ParsedMatchBody, JaktInternal::DynamicArray<parser::ParsedMatchCase>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LCurly */: {
return JaktInternal::ExplicitValue(parser::ParsedMatchBody::Block(((*this).parse_block())));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(parser::ParsedMatchBody::Expression(((*this).parse_expression(false,true))));
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
JaktInternal::ArrayIterator<parser::ParsedMatchPattern> _magic = ((patterns).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMatchPattern> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMatchPattern pattern = (_magic_value.value());
{
((cases).push(parser::ParsedMatchCase(DynamicArray<parser::ParsedMatchPattern>::create_with({pattern}),marker_span,body)));
}

}
}

if (((((*this).index)) == (pattern_start_index))){
break;
}
if ((((((*this).current())).__jakt_init_index() == 55 /* Eol */) || ((((*this).current())).__jakt_init_index() == 52 /* Comma */))){
((((*this).index)++));
}
((*this).skip_newlines());
}
((*this).skip_newlines());
if ((!(((((*this).current())).__jakt_init_index() == 10 /* RCurly */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘}’"sv)),((((*this).current())).span())));
}
((((*this).index)++));
return cases;
}
}

JaktInternal::DynamicArray<parser::ParsedMatchPattern> parser::Parser::parse_match_patterns() {
{
JaktInternal::DynamicArray<parser::ParsedMatchPattern> patterns = DynamicArray<parser::ParsedMatchPattern>::create_with({});
((*this).skip_newlines());
while ((!(((*this).eof())))){
parser::ParsedMatchPattern pattern = ((*this).parse_match_pattern());
ScopeGuard __jakt_var_108([&] {
((patterns).push(pattern));
});
JaktInternal::Dictionary<ByteString,parser::ParsedPatternDefault> defaults = ((pattern).common.init_common.defaults);
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
if (((name) == ((ByteString::from_utf8_without_validation("default"sv))))){
JaktInternal::Dictionary<ByteString,parser::ParsedPatternDefault> defaults = ((pattern).common.init_common.defaults);
((((*this).index)) += (static_cast<size_t>(1ULL)));
if ((!(((((*this).current())).__jakt_init_index() == 7 /* LParen */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected '(' after 'default'"sv)),((((*this).current())).span())));
continue;
}
((((*this).index)) += (static_cast<size_t>(1ULL)));
while (((!(((((*this).current())).__jakt_init_index() == 8 /* RParen */))) && (!(((*this).eof()))))){
bool const is_mutable = ((((*this).current())).__jakt_init_index() == 86 /* Mut */);
if (is_mutable){
((((*this).index)++));
}
parser::ParsedVarDecl const declaration = ((*this).parse_variable_declaration(is_mutable));
NonnullRefPtr<typename parser::ParsedExpression> const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedExpression>, JaktInternal::DynamicArray<parser::ParsedMatchPattern>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* Equal */: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_109; {
((((*this).index)++));
__jakt_var_109 = ((*this).parse_expression(false,false)); goto __jakt_label_103;

}
__jakt_label_103:; __jakt_var_109.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename parser::ParsedExpression>> __jakt_var_110; {
((*this).error((ByteString::from_utf8_without_validation("Expected initializer"sv)),((((*this).current())).span())));
__jakt_var_110 = parser::ParsedExpression::Garbage(((((*this).current())).span())); goto __jakt_label_104;

}
__jakt_label_104:; __jakt_var_110.release_value(); }));
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
((defaults).set(((declaration).name),parser::ParsedPatternDefault(declaration,value)));
}
if (((((*this).current())).__jakt_init_index() == 8 /* RParen */)){
((((*this).index)) += (static_cast<size_t>(1ULL)));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected a ')' to end 'defaults' list"sv)),((((*this).current())).span())));
}

}
}
((*this).skip_newlines());
if (((((*this).current())).__jakt_init_index() == 40 /* Pipe */)){
((((*this).index)++));
continue;
}
break;
}
return patterns;
}
}

parser::ParsedMatchPattern parser::Parser::parse_match_pattern() {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<parser::ParsedMatchPattern, parser::ParsedMatchPattern>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 102 /* True */: {
return JaktInternal::ExplicitValue(parser::ParsedMatchPattern::Expression(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({}),((*this).parse_operand())));
};/*case end*/
case 73 /* False */: {
return JaktInternal::ExplicitValue(parser::ParsedMatchPattern::Expression(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({}),((*this).parse_operand())));
};/*case end*/
case 2 /* Number */: {
return JaktInternal::ExplicitValue(parser::ParsedMatchPattern::Expression(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({}),((*this).parse_operand())));
};/*case end*/
case 1 /* QuotedString */: {
return JaktInternal::ExplicitValue(parser::ParsedMatchPattern::Expression(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({}),((*this).parse_operand())));
};/*case end*/
case 0 /* SingleQuotedString */: {
return JaktInternal::ExplicitValue(parser::ParsedMatchPattern::Expression(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({}),((*this).parse_operand())));
};/*case end*/
case 7 /* LParen */: {
return JaktInternal::ExplicitValue(parser::ParsedMatchPattern::Expression(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({}),((*this).parse_operand())));
};/*case end*/
case 70 /* Else */: {
return JaktInternal::ExplicitValue(({ Optional<parser::ParsedMatchPattern> __jakt_var_111; {
((((*this).index)++));
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments = ((*this).parse_variant_arguments());
utility::Span const arguments_start = ((((*this).current())).span());
utility::Span const arguments_end = ((((*this).previous())).span());
utility::Span const arguments_span = parser::merge_spans(arguments_start,arguments_end);
__jakt_var_111 = parser::ParsedMatchPattern::CatchAll(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({}),variant_arguments,arguments_span); goto __jakt_label_105;

}
__jakt_label_105:; __jakt_var_111.release_value(); }));
};/*case end*/
case 3 /* Identifier */: {
return JaktInternal::ExplicitValue(({ Optional<parser::ParsedMatchPattern> __jakt_var_112; {
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> variant_names = DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>>::create_with({});
bool just_saw_name = false;
while ((!(((*this).eof())))){
((*this).skip_newlines());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::ParsedMatchPattern>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
{
if (just_saw_name){
return JaktInternal::LoopBreak{};
}
(just_saw_name = true);
((((*this).index)++));
((variant_names).push((Tuple{name, ((((*this).current())).span())})));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* ColonColon */: {
{
((((*this).index)++));
(just_saw_name = false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
return JaktInternal::LoopBreak{};
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
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments = ((*this).parse_variant_arguments());
utility::Span const arguments_start = ((((*this).current())).span());
utility::Span const arguments_end = ((((*this).previous())).span());
utility::Span const arguments_span = parser::merge_spans(arguments_start,arguments_end);
__jakt_var_112 = parser::ParsedMatchPattern::EnumVariant(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({}),variant_names,variant_arguments,arguments_span); goto __jakt_label_106;

}
__jakt_label_106:; __jakt_var_112.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<parser::ParsedMatchPattern> __jakt_var_113; {
((*this).error((ByteString::from_utf8_without_validation("Expected pattern or ‘else’"sv)),((((*this).current())).span())));
__jakt_var_113 = parser::ParsedMatchPattern::Invalid(Dictionary<ByteString, parser::ParsedPatternDefault>::create_with_entries({})); goto __jakt_label_107;

}
__jakt_label_107:; __jakt_var_113.release_value(); }));
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

JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> parser::Parser::parse_variant_arguments() {
{
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments = DynamicArray<parser::EnumVariantPatternArgument>::create_with({});
bool has_parens = false;
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
(has_parens = true);
((((*this).index)++));
bool is_reference = false;
bool is_mutable = false;
while ((!(((*this).eof())))){
((*this).skip_newlines());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 37 /* Ampersand */: {
{
(is_reference = true);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 86 /* Mut */: {
{
(is_mutable = true);
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& arg_name = __jakt_match_value.name;
{
utility::Span const arg_name_span = ((((*this).current())).span());
if (((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 5 /* Colon */)){
((((*this).index)) += (static_cast<size_t>(2ULL)));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const arg_binding = (((*this).current())).as.Identifier.name;
utility::Span const span = ((((*this).current())).span());
((((*this).index)++));
((variant_arguments).push(parser::EnumVariantPatternArgument(static_cast<JaktInternal::Optional<ByteString>>(arg_name),static_cast<JaktInternal::Optional<utility::Span>>(arg_name_span),arg_binding,span,is_reference,is_mutable)));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected binding after ‘:’"sv)),((((*this).current())).span())));
}

}
else {
((variant_arguments).push(parser::EnumVariantPatternArgument(JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),arg_name,((((*this).current())).span()),is_reference,is_mutable)));
((((*this).index)++));
}

(is_reference = false);
(is_mutable = false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected pattern argument name"sv)),((((*this).current())).span())));
return JaktInternal::LoopBreak{};
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
return variant_arguments;
}
}

JaktInternal::Optional<parser::ParsedCall> parser::Parser::parse_call() {
{
parser::ParsedCall call = parser::ParsedCall(DynamicArray<ByteString>::create_with({}),(ByteString::from_utf8_without_validation(""sv)),DynamicArray<JaktInternal::Tuple<ByteString,utility::Span,NonnullRefPtr<typename parser::ParsedExpression>>>::create_with({}),DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({}));
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
(((call).name) = name);
((((*this).index)++));
size_t const index_reset = ((*this).index);
if (((((*this).current())).__jakt_init_index() == 28 /* LessThan */)){
((((*this).index)++));
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> inner_types = DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({});
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Optional<parser::ParsedCall>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* GreaterThan */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
{
((*this).inject_token(lexer::Token::GreaterThan(((((*this).current())).span()))));
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
size_t const index_before = ((*this).index);
NonnullRefPtr<typename parser::ParsedType> const inner_type = ((*this).parse_typename());
if (((index_before) == (((*this).index)))){
(((*this).index) = index_reset);
return JaktInternal::LoopBreak{};
}
((inner_types).push(inner_type));
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
(((call).type_args) = inner_types);
}
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
((((*this).index)++));
}
else {
(((*this).index) = index_reset);
((*this).error((ByteString::from_utf8_without_validation("Expected '('"sv)),((((*this).current())).span())));
return JaktInternal::OptionalNone();
}

while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Optional<parser::ParsedCall>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::Span const label_span = ((((*this).current())).span());
ByteString const label = ((*this).parse_argument_label());
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
((((call).args)).push((Tuple{label, label_span, expr})));
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
if (((*this).can_have_trailing_closure)){
utility::Span const start = ((((*this).current())).span());
size_t const start_index = ((*this).index);
JaktInternal::Optional<parser::ParsedBlock> block = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<parser::ParsedParameter> params = DynamicArray<parser::ParsedParameter>::create_with({});
bool has_varargs = false;
size_t errors_before = ((((((*this).compiler))->errors)).size());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Optional<parser::ParsedCall>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LCurly */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40 /* Pipe */: {
{
parser::ParsedFunctionParameters const parameters = ((*this).parse_function_parameters(true));
(params = ((parameters).parameters));
(has_varargs = ((parameters).has_varargs));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
return call;
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
if (((((*this).current())).__jakt_init_index() == 9 /* LCurly */)){
if (has_varargs){
((*this).error((ByteString::from_utf8_without_validation("Function expressions cannot have varargs"sv)),((((*this).current())).span())));
}
(block = ((*this).parse_block()));
utility::Span const span = parser::merge_spans(start,((((*this).current())).span()));
JaktInternal::DynamicArray<parser::ParsedCapture> const captures = DynamicArray<parser::ParsedCapture>::create_with({parser::ParsedCapture::AllByReference((ByteString::from_utf8_without_validation(""sv)),((*this).empty_span()))});
NonnullRefPtr<typename parser::ParsedExpression> const trailing_closure = parser::ParsedExpression::Function(captures,params,false,false,parser::ParsedType::Empty(JaktInternal::OptionalNone()),(block.value()),span);
NonnullRefPtr<typename parser::ParsedExpression> const reference_to_closure = parser::ParsedExpression::UnaryOp(trailing_closure,parser::UnaryOperator::Reference(),span);
((((call).args)).push((Tuple{(ByteString::from_utf8_without_validation(""sv)), ((*this).empty_span()), reference_to_closure})));
}
else {
(((*this).index) = start_index);
(((((*this).compiler))->errors) = ((((((((*this).compiler))->errors))[(JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(errors_before)})])).to_array()));
return call;
}

}
return call;
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected function call"sv)),((((*this).current())).span())));
return call;
}

}
}

void parser::Parser::skip_newlines() {
{
while (((((*this).current())).__jakt_init_index() == 55 /* Eol */)){
((((*this).index)++));
}
}
}

JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> parser::Parser::parse_trait_list() {
{
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
((((*this).index)++));
JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters> result = DynamicArray<parser::ParsedNameWithGenericParameters>::create_with({});
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 55 /* Eol */: {
{
((((*this).index)++));
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 56 /* Eof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eof;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected ')' to close the trait list"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
parser::ParsedNameWithGenericParameters parsed_name = parser::ParsedNameWithGenericParameters(name,span,DynamicArray<NonnullRefPtr<typename parser::ParsedType>>::create_with({}));
((((*this).index)++));
(((parsed_name).generic_parameters) = ((*this).parse_type_parameter_list()));
((result).push(parsed_name));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Semicolon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Semicolon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* Colon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Colon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* ColonColon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ColonColon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7 /* LParen */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LParen;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LCurly;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RCurly;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LSquare;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* RSquare */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RSquare;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* PercentSign */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSign;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* Plus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Plus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 15 /* Minus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Minus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* Equal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Equal;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* PlusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* PlusPlus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PlusPlus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* MinusEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* MinusMinus */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MinusMinus;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* AsteriskEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AsteriskEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* ForwardSlashEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlashEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* PercentSignEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PercentSignEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* NotEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NotEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* DoubleEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DoubleEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* GreaterThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThan;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* GreaterThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GreaterThanOrEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* LessThan */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThan;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* LessThanOrEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LessThanOrEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* LeftArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftArithmeticShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31 /* LeftShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32 /* LeftShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.LeftShiftEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 34 /* RightArithmeticShift */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightArithmeticShift;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 35 /* RightShiftEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RightShiftEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 36 /* Asterisk */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Asterisk;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 37 /* Ampersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Ampersand;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 38 /* AmpersandEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 39 /* AmpersandAmpersand */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AmpersandAmpersand;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 40 /* Pipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Pipe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 41 /* PipeEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipeEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 42 /* PipePipe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PipePipe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 43 /* Caret */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Caret;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 44 /* CaretEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CaretEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 45 /* Dollar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dollar;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 46 /* Tilde */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Tilde;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 47 /* ForwardSlash */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForwardSlash;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 48 /* ExclamationPoint */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ExclamationPoint;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 49 /* QuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMark;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 50 /* QuestionMarkQuestionMark */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMark;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 51 /* QuestionMarkQuestionMarkEqual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuestionMarkQuestionMarkEqual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 54 /* DotDot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DotDot;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 57 /* FatArrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.FatArrow;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 58 /* Arrow */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Arrow;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59 /* And */: {
auto&& __jakt_match_value = __jakt_match_variant.as.And;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60 /* Anon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Anon;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 61 /* As */: {
auto&& __jakt_match_value = __jakt_match_variant.as.As;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boxed;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 63 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 64 /* Catch */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Catch;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 66 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 67 /* Cpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Cpp;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 68 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 69 /* Destructor */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Destructor;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 70 /* Else */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Else;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 72 /* Extern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Extern;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 73 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 74 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fn;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 77 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 78 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79 /* Relative */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Relative;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80 /* In */: {
auto&& __jakt_match_value = __jakt_match_variant.as.In;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 81 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 82 /* Let */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Let;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 83 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 84 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 85 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 86 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 88 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 89 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 93 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 94 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 95 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 97 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 100 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 101 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 102 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 103 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 104 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 106 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 107 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 108 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 109 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 110 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 111 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 112 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;utility::Span const& span = __jakt_match_value.value;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 113 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.span;
{
((*this).error((ByteString::from_utf8_without_validation("Expected trait name"sv)),span));
return JaktInternal::LoopBreak{};
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
if (((result).is_empty())){
((*this).error((ByteString::from_utf8_without_validation("Expected trait list to have at least one trait inside it"sv)),((((*this).previous())).span())));
return JaktInternal::OptionalNone();
}
else {
return static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>>>(result);
}

}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected '(' to start the trait list"sv)),((((*this).current())).span())));
return JaktInternal::OptionalNone();
}

}
}

JaktInternal::DynamicArray<parser::ParsedGenericParameter> parser::Parser::parse_generic_parameters() {
{
if ((!(((((*this).current())).__jakt_init_index() == 28 /* LessThan */)))){
return DynamicArray<parser::ParsedGenericParameter>::create_with({});
}
((((*this).index)++));
JaktInternal::DynamicArray<parser::ParsedGenericParameter> generic_parameters = DynamicArray<parser::ParsedGenericParameter>::create_with({});
((*this).skip_newlines());
bool saw_ending_bracket = false;
bool next_generic_is_value = false;
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, JaktInternal::DynamicArray<parser::ParsedGenericParameter>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Identifier */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identifier;ByteString const& name = __jakt_match_value.name;
utility::Span const& span = __jakt_match_value.span;
{
ByteString effective_name = name;
JaktInternal::Optional<JaktInternal::DynamicArray<parser::ParsedNameWithGenericParameters>> requires_list = JaktInternal::OptionalNone();
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 111 /* Requires */)){
((((*this).index)++));
(requires_list = ((*this).parse_trait_list()));
}
((generic_parameters).push(parser::ParsedGenericParameter(name,span,requires_list,next_generic_is_value)));
(next_generic_is_value = false);
if ((((((*this).current())).__jakt_init_index() == 52 /* Comma */) || ((((*this).current())).__jakt_init_index() == 55 /* Eol */))){
((((*this).index)++));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
{
((((*this).index)++));
(next_generic_is_value = true);
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* GreaterThan */: {
{
((((*this).index)++));
(saw_ending_bracket = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 33 /* RightShift */: {
{
((*this).inject_token(lexer::Token::GreaterThan(((((*this).current())).span()))));
((((*this).index)) += (static_cast<size_t>(1ULL)));
(saw_ending_bracket = true);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 113 /* Garbage */: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected `>` to end the generic parameters"sv)),((((*this).current())).span())));
return generic_parameters;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
((*this).error((ByteString::from_utf8_without_validation("Expected generic parameter name"sv)),((((*this).current())).span())));
return generic_parameters;
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
if ((!(saw_ending_bracket))){
((*this).error((ByteString::from_utf8_without_validation("Expected `>` to end the generic parameters"sv)),((((*this).current())).span())));
return generic_parameters;
}
return generic_parameters;
}
}

ByteString parser::Parser::parse_argument_label() {
{
if ((((((*this).peek(static_cast<size_t>(1ULL)))).__jakt_init_index() == 5 /* Colon */) && ((((*this).current())).__jakt_init_index() == 3 /* Identifier */))){
ByteString const name = (((*this).current())).as.Identifier.name;
((((*this).index)) += (static_cast<size_t>(2ULL)));
return name;
}
return (ByteString::from_utf8_without_validation(""sv));
}
}

parser::Visibility parser::Parser::parse_restricted_visibility_modifier() {
{
utility::Span restricted_span = ((((*this).current())).span());
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 7 /* LParen */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘(’"sv)),((((*this).current())).span())));
return parser::Visibility::Restricted(DynamicArray<parser::VisibilityRestriction>::create_with({}),restricted_span);
}

JaktInternal::DynamicArray<parser::VisibilityRestriction> whitelist = DynamicArray<parser::VisibilityRestriction>::create_with({});
bool expect_comma = false;
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((*this).index),((((*this).tokens)).size()))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, parser::Visibility>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* RParen */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comma;utility::Span const& span = __jakt_match_value.value;
{
if (expect_comma){
(expect_comma = false);
}
else {
((*this).error((ByteString::from_utf8_without_validation("Unexpected comma"sv)),span));
}

((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
if (expect_comma){
((*this).error((ByteString::from_utf8_without_validation("Expected comma"sv)),((((*this).current())).span())));
}
((*this).skip_newlines());
JaktInternal::DynamicArray<ByteString> names = DynamicArray<ByteString>::create_with({});
for (;;){
if (((((*this).current())).__jakt_init_index() == 3 /* Identifier */)){
ByteString const name = (((*this).current())).as.Identifier.name;
((names).push(name));
((((*this).index)++));
if (((((*this).current())).__jakt_init_index() == 6 /* ColonColon */)){
((((*this).index)++));
}
else {
break;
}

}
else {
break;
}

}
if (((names).is_empty())){
((*this).error((ByteString::from_utf8_without_validation("Expected identifier"sv)),((((*this).current())).span())));
}
else {
ByteString const name = (((names).pop()).value());
((whitelist).push(parser::VisibilityRestriction(names,name)));
}

(expect_comma = true);
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
(((restricted_span).end) = ((((((*this).current())).span())).end));
if (((whitelist).is_empty())){
((*this).error_with_hint((ByteString::from_utf8_without_validation("Restriction list cannot be empty"sv)),restricted_span,(ByteString::from_utf8_without_validation("Did you mean to use ‘private’ instead of ‘restricted’?"sv)),restricted_span));
}
if (((((*this).current())).__jakt_init_index() == 8 /* RParen */)){
((((*this).index)++));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘)’"sv)),((((*this).current())).span())));
}

return parser::Visibility::Restricted(whitelist,restricted_span);
}
}

NonnullRefPtr<typename parser::ParsedExpression> parser::Parser::parse_array_or_dictionary_literal() {
{
bool is_dictionary = false;
utility::Span const start = ((((*this).current())).span());
if ((!(((((*this).current())).__jakt_init_index() == 11 /* LSquare */)))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘[’"sv)),((((*this).current())).span())));
return parser::ParsedExpression::Garbage(((((*this).current())).span()));
}
((((*this).index)++));
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> fill_size_expr = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> output = DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>>::create_with({});
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> dict_output = DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>>::create_with({});
while ((!(((*this).eof())))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, NonnullRefPtr<typename parser::ParsedExpression>>{
auto&& __jakt_match_variant = ((*this).current());
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* RSquare */: {
{
((((*this).index)++));
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 52 /* Comma */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
{
((((*this).index)++));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Semicolon */: {
{
if (((((output).size())) == (static_cast<size_t>(1ULL)))){
((((*this).index)++));
(fill_size_expr = ((*this).parse_expression(false,false)));
}
else {
((*this).error((ByteString::from_utf8_without_validation("Can't fill an Array with more than one expression"sv)),((((*this).current())).span())));
((((*this).index)++));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* Colon */: {
{
((((*this).index)++));
if (((dict_output).is_empty())){
if (((((*this).current())).__jakt_init_index() == 12 /* RSquare */)){
((((*this).index)++));
(is_dictionary = true);
return JaktInternal::LoopBreak{};
}
else {
((*this).error((ByteString::from_utf8_without_validation("Expected ‘]’"sv)),((((*this).current())).span())));
}

}
else {
((*this).error((ByteString::from_utf8_without_validation("Missing key in dictionary literal"sv)),((((*this).current())).span())));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
NonnullRefPtr<typename parser::ParsedExpression> const expr = ((*this).parse_expression(false,false));
if (((expr)->__jakt_init_index() == 30 /* Garbage */)){
return JaktInternal::LoopBreak{};
}
if (((((*this).current())).__jakt_init_index() == 5 /* Colon */)){
if ((!(((output).is_empty())))){
((*this).error((ByteString::from_utf8_without_validation("Mixing dictionary and array values"sv)),((((*this).current())).span())));
}
(is_dictionary = true);
((((*this).index)++));
if (((*this).eof())){
((*this).error((ByteString::from_utf8_without_validation("Key missing value in dictionary"sv)),((((*this).current())).span())));
return parser::ParsedExpression::Garbage(((((*this).current())).span()));
}
NonnullRefPtr<typename parser::ParsedExpression> const value = ((*this).parse_expression(false,false));
((dict_output).push((Tuple{expr, value})));
}
else if ((!(is_dictionary))){
((output).push(expr));
}
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
size_t const end = JaktInternal::checked_sub(((*this).index),static_cast<size_t>(1ULL));
if (([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(end,((((*this).tokens)).size())) || (!(((((((*this).tokens))[end])).__jakt_init_index() == 12 /* RSquare */))))){
((*this).error((ByteString::from_utf8_without_validation("Expected ‘]’ to close the array"sv)),((((((*this).tokens))[end])).span())));
}
if (is_dictionary){
return parser::ParsedExpression::JaktDictionary(dict_output,parser::merge_spans(start,((((((*this).tokens))[end])).span())));
}
else {
return parser::ParsedExpression::JaktArray(output,fill_size_expr,parser::merge_spans(start,((((((*this).tokens))[end])).span())));
}

}
}

parser::Parser::Parser(size_t a_index, JaktInternal::DynamicArray<lexer::Token> a_tokens, NonnullRefPtr<compiler::Compiler> a_compiler, bool a_can_have_trailing_closure, size_t a_next_function_id): index(move(a_index)), tokens(move(a_tokens)), compiler(move(a_compiler)), can_have_trailing_closure(move(a_can_have_trailing_closure)), next_function_id(move(a_next_function_id)){}

ByteString parser::ExternalName::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Plain */: {
builder.append("ExternalName::Plain"sv);
[[maybe_unused]] auto const& that = this->as.Plain;
builder.appendff("(\"{}\")", that.value);
break;}
case 1 /* PreprocessorName */: {
builder.append("ExternalName::PreprocessorName"sv);
[[maybe_unused]] auto const& that = this->as.PreprocessorName;
builder.appendff("(\"{}\")", that.value);
break;}
case 2 /* Operator */: {
builder.append("ExternalName::Operator"sv);
[[maybe_unused]] auto const& that = this->as.Operator;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_prefix: {}", that.is_prefix);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] ExternalName ExternalName::Plain(ByteString value){
ExternalName __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Plain.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] ExternalName ExternalName::PreprocessorName(ByteString value){
ExternalName __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.PreprocessorName.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] ExternalName ExternalName::Operator(ByteString name, bool is_prefix){
ExternalName __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Operator.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Operator.is_prefix) (decltype(is_prefix))(move(is_prefix));
return __jakt_uninit_enum;
}
ExternalName& ExternalName::operator=(ExternalName const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Plain */:
new (&this->as.Plain.value) (decltype(this->as.Plain.value))(rhs.as.Plain.value);
break;
case 1 /* PreprocessorName */:
new (&this->as.PreprocessorName.value) (decltype(this->as.PreprocessorName.value))(rhs.as.PreprocessorName.value);
break;
case 2 /* Operator */:
new (&this->as.Operator.name) (decltype(this->as.Operator.name))(rhs.as.Operator.name);
new (&this->as.Operator.is_prefix) (decltype(this->as.Operator.is_prefix))(rhs.as.Operator.is_prefix);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Plain */:
this->as.Plain.value = rhs.as.Plain.value;
break;
case 1 /* PreprocessorName */:
this->as.PreprocessorName.value = rhs.as.PreprocessorName.value;
break;
case 2 /* Operator */:
this->as.Operator.name = rhs.as.Operator.name;
this->as.Operator.is_prefix = rhs.as.Operator.is_prefix;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ExternalName::ExternalName(ExternalName const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Plain */:
new (&this->as.Plain.value) (decltype(this->as.Plain.value))(rhs.as.Plain.value);
break;
case 1 /* PreprocessorName */:
new (&this->as.PreprocessorName.value) (decltype(this->as.PreprocessorName.value))(rhs.as.PreprocessorName.value);
break;
case 2 /* Operator */:
new (&this->as.Operator.name) (decltype(this->as.Operator.name))(rhs.as.Operator.name);
new (&this->as.Operator.is_prefix) (decltype(this->as.Operator.is_prefix))(rhs.as.Operator.is_prefix);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ExternalName& ExternalName::operator=(ExternalName &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Plain */:
new (&this->as.Plain.value) (decltype(this->as.Plain.value))(move(rhs.as.Plain.value));
break;
case 1 /* PreprocessorName */:
new (&this->as.PreprocessorName.value) (decltype(this->as.PreprocessorName.value))(move(rhs.as.PreprocessorName.value));
break;
case 2 /* Operator */:
new (&this->as.Operator.name) (decltype(this->as.Operator.name))(move(rhs.as.Operator.name));
new (&this->as.Operator.is_prefix) (decltype(this->as.Operator.is_prefix))(move(rhs.as.Operator.is_prefix));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Plain */:
this->as.Plain.value = move(rhs.as.Plain.value);
break;
case 1 /* PreprocessorName */:
this->as.PreprocessorName.value = move(rhs.as.PreprocessorName.value);
break;
case 2 /* Operator */:
this->as.Operator.name = move(rhs.as.Operator.name);
this->as.Operator.is_prefix = move(rhs.as.Operator.is_prefix);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ExternalName::ExternalName(ExternalName &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Plain */:
new (&this->as.Plain.value) (decltype(this->as.Plain.value))(move(rhs.as.Plain.value));
break;
case 1 /* PreprocessorName */:
new (&this->as.PreprocessorName.value) (decltype(this->as.PreprocessorName.value))(move(rhs.as.PreprocessorName.value));
break;
case 2 /* Operator */:
new (&this->as.Operator.name) (decltype(this->as.Operator.name))(move(rhs.as.Operator.name));
new (&this->as.Operator.is_prefix) (decltype(this->as.Operator.is_prefix))(move(rhs.as.Operator.is_prefix));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ExternalName::~ExternalName(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ExternalName::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Plain */:this->as.Plain.value.~ByteString();
break;
case 1 /* PreprocessorName */:this->as.PreprocessorName.value.~ByteString();
break;
case 2 /* Operator */:this->as.Operator.name.~ByteString();
break;
}
}
ByteString parser::ExternalName::as_name_for_definition() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Plain */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Plain;ByteString const& name = __jakt_match_value.value;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 1 /* PreprocessorName */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PreprocessorName;ByteString const& name = __jakt_match_value.value;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 2 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("operator"sv))) + (name)));
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

ByteString parser::ExternalName::as_name_for_use() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Plain */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Plain;ByteString const& name = __jakt_match_value.value;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 1 /* PreprocessorName */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PreprocessorName;ByteString const& name = __jakt_match_value.value;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 2 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal(" {} "sv)),name));
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

bool parser::ExternalName::is_prefix() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Plain */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 1 /* PreprocessorName */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 2 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;bool const& is_prefix = __jakt_match_value.is_prefix;
return JaktInternal::ExplicitValue(is_prefix);
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

bool parser::ExternalName::is_scopable() const {
{
return (!(((*this).__jakt_init_index() == 1 /* PreprocessorName */)));
}
}

ByteString parser::NumericConstant::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* I8 */: {
builder.append("NumericConstant::I8"sv);
[[maybe_unused]] auto const& that = this->as.I8;
builder.appendff("({})", that.value);
break;}
case 1 /* I16 */: {
builder.append("NumericConstant::I16"sv);
[[maybe_unused]] auto const& that = this->as.I16;
builder.appendff("({})", that.value);
break;}
case 2 /* I32 */: {
builder.append("NumericConstant::I32"sv);
[[maybe_unused]] auto const& that = this->as.I32;
builder.appendff("({})", that.value);
break;}
case 3 /* I64 */: {
builder.append("NumericConstant::I64"sv);
[[maybe_unused]] auto const& that = this->as.I64;
builder.appendff("({})", that.value);
break;}
case 4 /* U8 */: {
builder.append("NumericConstant::U8"sv);
[[maybe_unused]] auto const& that = this->as.U8;
builder.appendff("({})", that.value);
break;}
case 5 /* U16 */: {
builder.append("NumericConstant::U16"sv);
[[maybe_unused]] auto const& that = this->as.U16;
builder.appendff("({})", that.value);
break;}
case 6 /* U32 */: {
builder.append("NumericConstant::U32"sv);
[[maybe_unused]] auto const& that = this->as.U32;
builder.appendff("({})", that.value);
break;}
case 7 /* U64 */: {
builder.append("NumericConstant::U64"sv);
[[maybe_unused]] auto const& that = this->as.U64;
builder.appendff("({})", that.value);
break;}
case 8 /* USize */: {
builder.append("NumericConstant::USize"sv);
[[maybe_unused]] auto const& that = this->as.USize;
builder.appendff("({})", that.value);
break;}
case 9 /* F32 */: {
builder.append("NumericConstant::F32"sv);
[[maybe_unused]] auto const& that = this->as.F32;
builder.appendff("({})", that.value);
break;}
case 10 /* F64 */: {
builder.append("NumericConstant::F64"sv);
[[maybe_unused]] auto const& that = this->as.F64;
builder.appendff("({})", that.value);
break;}
case 11 /* UnknownSigned */: {
builder.append("NumericConstant::UnknownSigned"sv);
[[maybe_unused]] auto const& that = this->as.UnknownSigned;
builder.appendff("({})", that.value);
break;}
case 12 /* UnknownUnsigned */: {
builder.append("NumericConstant::UnknownUnsigned"sv);
[[maybe_unused]] auto const& that = this->as.UnknownUnsigned;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] NumericConstant NumericConstant::I8(i8 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.I8.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::I16(i16 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.I16.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::I32(i32 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.I32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::I64(i64 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.I64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::U8(u8 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.as.U8.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::U16(u16 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
new (&__jakt_uninit_enum.as.U16.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::U32(u32 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
new (&__jakt_uninit_enum.as.U32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::U64(u64 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
new (&__jakt_uninit_enum.as.U64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::USize(u64 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
new (&__jakt_uninit_enum.as.USize.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::F32(f32 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
new (&__jakt_uninit_enum.as.F32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::F64(f64 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
new (&__jakt_uninit_enum.as.F64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::UnknownSigned(i64 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
new (&__jakt_uninit_enum.as.UnknownSigned.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericConstant NumericConstant::UnknownUnsigned(u64 value){
NumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
new (&__jakt_uninit_enum.as.UnknownUnsigned.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
NumericConstant& NumericConstant::operator=(NumericConstant const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(rhs.as.I8.value);
break;
case 1 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(rhs.as.I16.value);
break;
case 2 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(rhs.as.I32.value);
break;
case 3 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(rhs.as.I64.value);
break;
case 4 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(rhs.as.U8.value);
break;
case 5 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(rhs.as.U16.value);
break;
case 6 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(rhs.as.U32.value);
break;
case 7 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(rhs.as.U64.value);
break;
case 8 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(rhs.as.USize.value);
break;
case 9 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(rhs.as.F32.value);
break;
case 10 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(rhs.as.F64.value);
break;
case 11 /* UnknownSigned */:
new (&this->as.UnknownSigned.value) (decltype(this->as.UnknownSigned.value))(rhs.as.UnknownSigned.value);
break;
case 12 /* UnknownUnsigned */:
new (&this->as.UnknownUnsigned.value) (decltype(this->as.UnknownUnsigned.value))(rhs.as.UnknownUnsigned.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
this->as.I8.value = rhs.as.I8.value;
break;
case 1 /* I16 */:
this->as.I16.value = rhs.as.I16.value;
break;
case 2 /* I32 */:
this->as.I32.value = rhs.as.I32.value;
break;
case 3 /* I64 */:
this->as.I64.value = rhs.as.I64.value;
break;
case 4 /* U8 */:
this->as.U8.value = rhs.as.U8.value;
break;
case 5 /* U16 */:
this->as.U16.value = rhs.as.U16.value;
break;
case 6 /* U32 */:
this->as.U32.value = rhs.as.U32.value;
break;
case 7 /* U64 */:
this->as.U64.value = rhs.as.U64.value;
break;
case 8 /* USize */:
this->as.USize.value = rhs.as.USize.value;
break;
case 9 /* F32 */:
this->as.F32.value = rhs.as.F32.value;
break;
case 10 /* F64 */:
this->as.F64.value = rhs.as.F64.value;
break;
case 11 /* UnknownSigned */:
this->as.UnknownSigned.value = rhs.as.UnknownSigned.value;
break;
case 12 /* UnknownUnsigned */:
this->as.UnknownUnsigned.value = rhs.as.UnknownUnsigned.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
NumericConstant::NumericConstant(NumericConstant const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(rhs.as.I8.value);
break;
case 1 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(rhs.as.I16.value);
break;
case 2 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(rhs.as.I32.value);
break;
case 3 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(rhs.as.I64.value);
break;
case 4 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(rhs.as.U8.value);
break;
case 5 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(rhs.as.U16.value);
break;
case 6 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(rhs.as.U32.value);
break;
case 7 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(rhs.as.U64.value);
break;
case 8 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(rhs.as.USize.value);
break;
case 9 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(rhs.as.F32.value);
break;
case 10 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(rhs.as.F64.value);
break;
case 11 /* UnknownSigned */:
new (&this->as.UnknownSigned.value) (decltype(this->as.UnknownSigned.value))(rhs.as.UnknownSigned.value);
break;
case 12 /* UnknownUnsigned */:
new (&this->as.UnknownUnsigned.value) (decltype(this->as.UnknownUnsigned.value))(rhs.as.UnknownUnsigned.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
NumericConstant& NumericConstant::operator=(NumericConstant &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(move(rhs.as.I8.value));
break;
case 1 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(move(rhs.as.I16.value));
break;
case 2 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(move(rhs.as.I32.value));
break;
case 3 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(move(rhs.as.I64.value));
break;
case 4 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(move(rhs.as.U8.value));
break;
case 5 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(move(rhs.as.U16.value));
break;
case 6 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(move(rhs.as.U32.value));
break;
case 7 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(move(rhs.as.U64.value));
break;
case 8 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(move(rhs.as.USize.value));
break;
case 9 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(move(rhs.as.F32.value));
break;
case 10 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(move(rhs.as.F64.value));
break;
case 11 /* UnknownSigned */:
new (&this->as.UnknownSigned.value) (decltype(this->as.UnknownSigned.value))(move(rhs.as.UnknownSigned.value));
break;
case 12 /* UnknownUnsigned */:
new (&this->as.UnknownUnsigned.value) (decltype(this->as.UnknownUnsigned.value))(move(rhs.as.UnknownUnsigned.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
this->as.I8.value = move(rhs.as.I8.value);
break;
case 1 /* I16 */:
this->as.I16.value = move(rhs.as.I16.value);
break;
case 2 /* I32 */:
this->as.I32.value = move(rhs.as.I32.value);
break;
case 3 /* I64 */:
this->as.I64.value = move(rhs.as.I64.value);
break;
case 4 /* U8 */:
this->as.U8.value = move(rhs.as.U8.value);
break;
case 5 /* U16 */:
this->as.U16.value = move(rhs.as.U16.value);
break;
case 6 /* U32 */:
this->as.U32.value = move(rhs.as.U32.value);
break;
case 7 /* U64 */:
this->as.U64.value = move(rhs.as.U64.value);
break;
case 8 /* USize */:
this->as.USize.value = move(rhs.as.USize.value);
break;
case 9 /* F32 */:
this->as.F32.value = move(rhs.as.F32.value);
break;
case 10 /* F64 */:
this->as.F64.value = move(rhs.as.F64.value);
break;
case 11 /* UnknownSigned */:
this->as.UnknownSigned.value = move(rhs.as.UnknownSigned.value);
break;
case 12 /* UnknownUnsigned */:
this->as.UnknownUnsigned.value = move(rhs.as.UnknownUnsigned.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
NumericConstant::NumericConstant(NumericConstant &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(move(rhs.as.I8.value));
break;
case 1 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(move(rhs.as.I16.value));
break;
case 2 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(move(rhs.as.I32.value));
break;
case 3 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(move(rhs.as.I64.value));
break;
case 4 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(move(rhs.as.U8.value));
break;
case 5 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(move(rhs.as.U16.value));
break;
case 6 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(move(rhs.as.U32.value));
break;
case 7 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(move(rhs.as.U64.value));
break;
case 8 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(move(rhs.as.USize.value));
break;
case 9 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(move(rhs.as.F32.value));
break;
case 10 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(move(rhs.as.F64.value));
break;
case 11 /* UnknownSigned */:
new (&this->as.UnknownSigned.value) (decltype(this->as.UnknownSigned.value))(move(rhs.as.UnknownSigned.value));
break;
case 12 /* UnknownUnsigned */:
new (&this->as.UnknownUnsigned.value) (decltype(this->as.UnknownUnsigned.value))(move(rhs.as.UnknownUnsigned.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
NumericConstant::~NumericConstant(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void NumericConstant::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* I8 */:break;
case 1 /* I16 */:break;
case 2 /* I32 */:break;
case 3 /* I64 */:break;
case 4 /* U8 */:break;
case 5 /* U16 */:break;
case 6 /* U32 */:break;
case 7 /* U64 */:break;
case 8 /* USize */:break;
case 9 /* F32 */:break;
case 10 /* F64 */:break;
case 11 /* UnknownSigned */:break;
case 12 /* UnknownUnsigned */:break;
}
}
size_t parser::NumericConstant::to_usize() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 11 /* UnknownSigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnknownSigned;i64 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
case 12 /* UnknownUnsigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnknownUnsigned;u64 const& num = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((num))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((static_cast<i64>(0LL)))));
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

ByteString parser::DefinitionLinkage::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Internal */: {
return ByteString("DefinitionLinkage::Internal"sv);
break;}
case 1 /* External */: {
return ByteString("DefinitionLinkage::External"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] DefinitionLinkage DefinitionLinkage::Internal(){
DefinitionLinkage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] DefinitionLinkage DefinitionLinkage::External(){
DefinitionLinkage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
DefinitionLinkage& DefinitionLinkage::operator=(DefinitionLinkage const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
DefinitionLinkage::DefinitionLinkage(DefinitionLinkage const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
DefinitionLinkage& DefinitionLinkage::operator=(DefinitionLinkage &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
DefinitionLinkage::DefinitionLinkage(DefinitionLinkage &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
DefinitionLinkage::~DefinitionLinkage(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void DefinitionLinkage::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Internal */:break;
case 1 /* External */:break;
}
}
ByteString parser::ImportName::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Literal */: {
builder.append("ImportName::Literal"sv);
[[maybe_unused]] auto const& that = this->as.Literal;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* Comptime */: {
builder.append("ImportName::Comptime"sv);
[[maybe_unused]] auto const& that = this->as.Comptime;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expression: {}", that.expression);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] ImportName ImportName::Literal(ByteString name, utility::Span span){
ImportName __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Literal.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Literal.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] ImportName ImportName::Comptime(NonnullRefPtr<typename parser::ParsedExpression> expression){
ImportName __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Comptime.expression) (decltype(expression))(move(expression));
return __jakt_uninit_enum;
}
ImportName& ImportName::operator=(ImportName const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Literal */:
new (&this->as.Literal.name) (decltype(this->as.Literal.name))(rhs.as.Literal.name);
new (&this->as.Literal.span) (decltype(this->as.Literal.span))(rhs.as.Literal.span);
break;
case 1 /* Comptime */:
new (&this->as.Comptime.expression) (decltype(this->as.Comptime.expression))(rhs.as.Comptime.expression);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Literal */:
this->as.Literal.name = rhs.as.Literal.name;
this->as.Literal.span = rhs.as.Literal.span;
break;
case 1 /* Comptime */:
this->as.Comptime.expression = rhs.as.Comptime.expression;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ImportName::ImportName(ImportName const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Literal */:
new (&this->as.Literal.name) (decltype(this->as.Literal.name))(rhs.as.Literal.name);
new (&this->as.Literal.span) (decltype(this->as.Literal.span))(rhs.as.Literal.span);
break;
case 1 /* Comptime */:
new (&this->as.Comptime.expression) (decltype(this->as.Comptime.expression))(rhs.as.Comptime.expression);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ImportName& ImportName::operator=(ImportName &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Literal */:
new (&this->as.Literal.name) (decltype(this->as.Literal.name))(move(rhs.as.Literal.name));
new (&this->as.Literal.span) (decltype(this->as.Literal.span))(move(rhs.as.Literal.span));
break;
case 1 /* Comptime */:
new (&this->as.Comptime.expression) (decltype(this->as.Comptime.expression))(move(rhs.as.Comptime.expression));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Literal */:
this->as.Literal.name = move(rhs.as.Literal.name);
this->as.Literal.span = move(rhs.as.Literal.span);
break;
case 1 /* Comptime */:
this->as.Comptime.expression = move(rhs.as.Comptime.expression);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ImportName::ImportName(ImportName &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Literal */:
new (&this->as.Literal.name) (decltype(this->as.Literal.name))(move(rhs.as.Literal.name));
new (&this->as.Literal.span) (decltype(this->as.Literal.span))(move(rhs.as.Literal.span));
break;
case 1 /* Comptime */:
new (&this->as.Comptime.expression) (decltype(this->as.Comptime.expression))(move(rhs.as.Comptime.expression));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ImportName::~ImportName(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ImportName::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Literal */:this->as.Literal.name.~ByteString();
this->as.Literal.span.~Span();
break;
case 1 /* Comptime */:this->as.Comptime.expression.~NonnullRefPtr();
break;
}
}
bool parser::ImportName::equals(parser::ImportName const other) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Literal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Literal;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Literal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Literal;ByteString const& other_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(((name) == (other_name)));
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
}));
};/*case end*/
case 1 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;NonnullRefPtr<typename parser::ParsedExpression> const& expression = __jakt_match_value.expression;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;NonnullRefPtr<typename parser::ParsedExpression> const& other_expression = __jakt_match_value.expression;
return JaktInternal::ExplicitValue(((expression)->equals(other_expression)));
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
}));
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

ByteString parser::ImportName::literal_name() const {
{
if (((*this).__jakt_init_index() == 0 /* Literal */)){
ByteString const name = (*this).as.Literal.name;
return name;
}
else {
utility::panic((ByteString::from_utf8_without_validation("Cannot get literal name of non-literal import name"sv)));
}

}
}

utility::Span parser::ImportName::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Literal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Literal;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;NonnullRefPtr<typename parser::ParsedExpression> const& expression = __jakt_match_value.expression;
{
return ((expression)->span());
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

ByteString parser::ImportList::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* List */: {
builder.append("ImportList::List"sv);
[[maybe_unused]] auto const& that = this->as.List;
builder.appendff("({})", that.value);
break;}
case 1 /* All */: {
return ByteString("ImportList::All"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] ImportList ImportList::List(JaktInternal::DynamicArray<parser::ImportName> value){
ImportList __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.List.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] ImportList ImportList::All(){
ImportList __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
ImportList& ImportList::operator=(ImportList const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* List */:
new (&this->as.List.value) (decltype(this->as.List.value))(rhs.as.List.value);
break;
case 1 /* All */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* List */:
this->as.List.value = rhs.as.List.value;
break;
case 1 /* All */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ImportList::ImportList(ImportList const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* List */:
new (&this->as.List.value) (decltype(this->as.List.value))(rhs.as.List.value);
break;
case 1 /* All */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ImportList& ImportList::operator=(ImportList &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* List */:
new (&this->as.List.value) (decltype(this->as.List.value))(move(rhs.as.List.value));
break;
case 1 /* All */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* List */:
this->as.List.value = move(rhs.as.List.value);
break;
case 1 /* All */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ImportList::ImportList(ImportList &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* List */:
new (&this->as.List.value) (decltype(this->as.List.value))(move(rhs.as.List.value));
break;
case 1 /* All */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ImportList::~ImportList(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ImportList::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* List */:this->as.List.value.~DynamicArray();
break;
case 1 /* All */:break;
}
}
bool parser::ImportList::is_empty() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* List */: {
auto&& __jakt_match_value = __jakt_match_variant.as.List;JaktInternal::DynamicArray<parser::ImportName> const& names = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((names).is_empty()));
};/*case end*/
case 1 /* All */: {
return JaktInternal::ExplicitValue(false);
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

void parser::ImportList::add(parser::ImportName const name) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, void>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* List */: {
auto&& __jakt_match_value = __jakt_match_variant.as.List;JaktInternal::DynamicArray<parser::ImportName> const& names = __jakt_match_value.value;
{
JaktInternal::DynamicArray<parser::ImportName> mutable_names = names;
((mutable_names).push(name));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* All */: {
{
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
}
}

ByteString parser::IncludeAction::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Define */: {
builder.append("IncludeAction::Define"sv);
[[maybe_unused]] auto const& that = this->as.Define;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("value: \"{}\"", that.value);
}
builder.append(")"sv);
break;}
case 1 /* Undefine */: {
builder.append("IncludeAction::Undefine"sv);
[[maybe_unused]] auto const& that = this->as.Undefine;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] IncludeAction IncludeAction::Define(ByteString name, utility::Span span, ByteString value){
IncludeAction __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Define.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Define.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum.as.Define.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] IncludeAction IncludeAction::Undefine(ByteString name, utility::Span span){
IncludeAction __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Undefine.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Undefine.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
IncludeAction& IncludeAction::operator=(IncludeAction const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Define */:
new (&this->as.Define.name) (decltype(this->as.Define.name))(rhs.as.Define.name);
new (&this->as.Define.span) (decltype(this->as.Define.span))(rhs.as.Define.span);
new (&this->as.Define.value) (decltype(this->as.Define.value))(rhs.as.Define.value);
break;
case 1 /* Undefine */:
new (&this->as.Undefine.name) (decltype(this->as.Undefine.name))(rhs.as.Undefine.name);
new (&this->as.Undefine.span) (decltype(this->as.Undefine.span))(rhs.as.Undefine.span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Define */:
this->as.Define.name = rhs.as.Define.name;
this->as.Define.span = rhs.as.Define.span;
this->as.Define.value = rhs.as.Define.value;
break;
case 1 /* Undefine */:
this->as.Undefine.name = rhs.as.Undefine.name;
this->as.Undefine.span = rhs.as.Undefine.span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
IncludeAction::IncludeAction(IncludeAction const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Define */:
new (&this->as.Define.name) (decltype(this->as.Define.name))(rhs.as.Define.name);
new (&this->as.Define.span) (decltype(this->as.Define.span))(rhs.as.Define.span);
new (&this->as.Define.value) (decltype(this->as.Define.value))(rhs.as.Define.value);
break;
case 1 /* Undefine */:
new (&this->as.Undefine.name) (decltype(this->as.Undefine.name))(rhs.as.Undefine.name);
new (&this->as.Undefine.span) (decltype(this->as.Undefine.span))(rhs.as.Undefine.span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
IncludeAction& IncludeAction::operator=(IncludeAction &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Define */:
new (&this->as.Define.name) (decltype(this->as.Define.name))(move(rhs.as.Define.name));
new (&this->as.Define.span) (decltype(this->as.Define.span))(move(rhs.as.Define.span));
new (&this->as.Define.value) (decltype(this->as.Define.value))(move(rhs.as.Define.value));
break;
case 1 /* Undefine */:
new (&this->as.Undefine.name) (decltype(this->as.Undefine.name))(move(rhs.as.Undefine.name));
new (&this->as.Undefine.span) (decltype(this->as.Undefine.span))(move(rhs.as.Undefine.span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Define */:
this->as.Define.name = move(rhs.as.Define.name);
this->as.Define.span = move(rhs.as.Define.span);
this->as.Define.value = move(rhs.as.Define.value);
break;
case 1 /* Undefine */:
this->as.Undefine.name = move(rhs.as.Undefine.name);
this->as.Undefine.span = move(rhs.as.Undefine.span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
IncludeAction::IncludeAction(IncludeAction &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Define */:
new (&this->as.Define.name) (decltype(this->as.Define.name))(move(rhs.as.Define.name));
new (&this->as.Define.span) (decltype(this->as.Define.span))(move(rhs.as.Define.span));
new (&this->as.Define.value) (decltype(this->as.Define.value))(move(rhs.as.Define.value));
break;
case 1 /* Undefine */:
new (&this->as.Undefine.name) (decltype(this->as.Undefine.name))(move(rhs.as.Undefine.name));
new (&this->as.Undefine.span) (decltype(this->as.Undefine.span))(move(rhs.as.Undefine.span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
IncludeAction::~IncludeAction(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void IncludeAction::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Define */:this->as.Define.name.~ByteString();
this->as.Define.span.~Span();
this->as.Define.value.~ByteString();
break;
case 1 /* Undefine */:this->as.Undefine.name.~ByteString();
this->as.Undefine.span.~Span();
break;
}
}
ByteString parser::RecordType::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Struct */: {
builder.append("RecordType::Struct"sv);
[[maybe_unused]] auto const& that = this->as.Struct;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", that.fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("super_type: {}", that.super_type);
}
builder.append(")"sv);
break;}
case 1 /* Class */: {
builder.append("RecordType::Class"sv);
[[maybe_unused]] auto const& that = this->as.Class;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", that.fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("super_type: {}", that.super_type);
}
builder.append(")"sv);
break;}
case 2 /* ValueEnum */: {
builder.append("RecordType::ValueEnum"sv);
[[maybe_unused]] auto const& that = this->as.ValueEnum;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("underlying_type: {}, ", that.underlying_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variants: {}", that.variants);
}
builder.append(")"sv);
break;}
case 3 /* SumEnum */: {
builder.append("RecordType::SumEnum"sv);
[[maybe_unused]] auto const& that = this->as.SumEnum;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_boxed: {}, ", that.is_boxed);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", that.fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variants: {}", that.variants);
}
builder.append(")"sv);
break;}
case 4 /* Garbage */: {
return ByteString("RecordType::Garbage"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] RecordType RecordType::Struct(JaktInternal::DynamicArray<parser::ParsedField> fields, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type){
RecordType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Struct.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum.as.Struct.super_type) (decltype(super_type))(move(super_type));
return __jakt_uninit_enum;
}
[[nodiscard]] RecordType RecordType::Class(JaktInternal::DynamicArray<parser::ParsedField> fields, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedType>> super_type){
RecordType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Class.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum.as.Class.super_type) (decltype(super_type))(move(super_type));
return __jakt_uninit_enum;
}
[[nodiscard]] RecordType RecordType::ValueEnum(NonnullRefPtr<typename parser::ParsedType> underlying_type, JaktInternal::DynamicArray<parser::ValueEnumVariant> variants){
RecordType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.ValueEnum.underlying_type) (decltype(underlying_type))(move(underlying_type));
new (&__jakt_uninit_enum.as.ValueEnum.variants) (decltype(variants))(move(variants));
return __jakt_uninit_enum;
}
[[nodiscard]] RecordType RecordType::SumEnum(bool is_boxed, JaktInternal::DynamicArray<parser::ParsedField> fields, JaktInternal::DynamicArray<parser::SumEnumVariant> variants){
RecordType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.SumEnum.is_boxed) (decltype(is_boxed))(move(is_boxed));
new (&__jakt_uninit_enum.as.SumEnum.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum.as.SumEnum.variants) (decltype(variants))(move(variants));
return __jakt_uninit_enum;
}
[[nodiscard]] RecordType RecordType::Garbage(){
RecordType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
RecordType& RecordType::operator=(RecordType const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.fields) (decltype(this->as.Struct.fields))(rhs.as.Struct.fields);
new (&this->as.Struct.super_type) (decltype(this->as.Struct.super_type))(rhs.as.Struct.super_type);
break;
case 1 /* Class */:
new (&this->as.Class.fields) (decltype(this->as.Class.fields))(rhs.as.Class.fields);
new (&this->as.Class.super_type) (decltype(this->as.Class.super_type))(rhs.as.Class.super_type);
break;
case 2 /* ValueEnum */:
new (&this->as.ValueEnum.underlying_type) (decltype(this->as.ValueEnum.underlying_type))(rhs.as.ValueEnum.underlying_type);
new (&this->as.ValueEnum.variants) (decltype(this->as.ValueEnum.variants))(rhs.as.ValueEnum.variants);
break;
case 3 /* SumEnum */:
new (&this->as.SumEnum.is_boxed) (decltype(this->as.SumEnum.is_boxed))(rhs.as.SumEnum.is_boxed);
new (&this->as.SumEnum.fields) (decltype(this->as.SumEnum.fields))(rhs.as.SumEnum.fields);
new (&this->as.SumEnum.variants) (decltype(this->as.SumEnum.variants))(rhs.as.SumEnum.variants);
break;
case 4 /* Garbage */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
this->as.Struct.fields = rhs.as.Struct.fields;
this->as.Struct.super_type = rhs.as.Struct.super_type;
break;
case 1 /* Class */:
this->as.Class.fields = rhs.as.Class.fields;
this->as.Class.super_type = rhs.as.Class.super_type;
break;
case 2 /* ValueEnum */:
this->as.ValueEnum.underlying_type = rhs.as.ValueEnum.underlying_type;
this->as.ValueEnum.variants = rhs.as.ValueEnum.variants;
break;
case 3 /* SumEnum */:
this->as.SumEnum.is_boxed = rhs.as.SumEnum.is_boxed;
this->as.SumEnum.fields = rhs.as.SumEnum.fields;
this->as.SumEnum.variants = rhs.as.SumEnum.variants;
break;
case 4 /* Garbage */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
RecordType::RecordType(RecordType const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.fields) (decltype(this->as.Struct.fields))(rhs.as.Struct.fields);
new (&this->as.Struct.super_type) (decltype(this->as.Struct.super_type))(rhs.as.Struct.super_type);
break;
case 1 /* Class */:
new (&this->as.Class.fields) (decltype(this->as.Class.fields))(rhs.as.Class.fields);
new (&this->as.Class.super_type) (decltype(this->as.Class.super_type))(rhs.as.Class.super_type);
break;
case 2 /* ValueEnum */:
new (&this->as.ValueEnum.underlying_type) (decltype(this->as.ValueEnum.underlying_type))(rhs.as.ValueEnum.underlying_type);
new (&this->as.ValueEnum.variants) (decltype(this->as.ValueEnum.variants))(rhs.as.ValueEnum.variants);
break;
case 3 /* SumEnum */:
new (&this->as.SumEnum.is_boxed) (decltype(this->as.SumEnum.is_boxed))(rhs.as.SumEnum.is_boxed);
new (&this->as.SumEnum.fields) (decltype(this->as.SumEnum.fields))(rhs.as.SumEnum.fields);
new (&this->as.SumEnum.variants) (decltype(this->as.SumEnum.variants))(rhs.as.SumEnum.variants);
break;
case 4 /* Garbage */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
RecordType& RecordType::operator=(RecordType &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.fields) (decltype(this->as.Struct.fields))(move(rhs.as.Struct.fields));
new (&this->as.Struct.super_type) (decltype(this->as.Struct.super_type))(move(rhs.as.Struct.super_type));
break;
case 1 /* Class */:
new (&this->as.Class.fields) (decltype(this->as.Class.fields))(move(rhs.as.Class.fields));
new (&this->as.Class.super_type) (decltype(this->as.Class.super_type))(move(rhs.as.Class.super_type));
break;
case 2 /* ValueEnum */:
new (&this->as.ValueEnum.underlying_type) (decltype(this->as.ValueEnum.underlying_type))(move(rhs.as.ValueEnum.underlying_type));
new (&this->as.ValueEnum.variants) (decltype(this->as.ValueEnum.variants))(move(rhs.as.ValueEnum.variants));
break;
case 3 /* SumEnum */:
new (&this->as.SumEnum.is_boxed) (decltype(this->as.SumEnum.is_boxed))(move(rhs.as.SumEnum.is_boxed));
new (&this->as.SumEnum.fields) (decltype(this->as.SumEnum.fields))(move(rhs.as.SumEnum.fields));
new (&this->as.SumEnum.variants) (decltype(this->as.SumEnum.variants))(move(rhs.as.SumEnum.variants));
break;
case 4 /* Garbage */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
this->as.Struct.fields = move(rhs.as.Struct.fields);
this->as.Struct.super_type = move(rhs.as.Struct.super_type);
break;
case 1 /* Class */:
this->as.Class.fields = move(rhs.as.Class.fields);
this->as.Class.super_type = move(rhs.as.Class.super_type);
break;
case 2 /* ValueEnum */:
this->as.ValueEnum.underlying_type = move(rhs.as.ValueEnum.underlying_type);
this->as.ValueEnum.variants = move(rhs.as.ValueEnum.variants);
break;
case 3 /* SumEnum */:
this->as.SumEnum.is_boxed = move(rhs.as.SumEnum.is_boxed);
this->as.SumEnum.fields = move(rhs.as.SumEnum.fields);
this->as.SumEnum.variants = move(rhs.as.SumEnum.variants);
break;
case 4 /* Garbage */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
RecordType::RecordType(RecordType &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.fields) (decltype(this->as.Struct.fields))(move(rhs.as.Struct.fields));
new (&this->as.Struct.super_type) (decltype(this->as.Struct.super_type))(move(rhs.as.Struct.super_type));
break;
case 1 /* Class */:
new (&this->as.Class.fields) (decltype(this->as.Class.fields))(move(rhs.as.Class.fields));
new (&this->as.Class.super_type) (decltype(this->as.Class.super_type))(move(rhs.as.Class.super_type));
break;
case 2 /* ValueEnum */:
new (&this->as.ValueEnum.underlying_type) (decltype(this->as.ValueEnum.underlying_type))(move(rhs.as.ValueEnum.underlying_type));
new (&this->as.ValueEnum.variants) (decltype(this->as.ValueEnum.variants))(move(rhs.as.ValueEnum.variants));
break;
case 3 /* SumEnum */:
new (&this->as.SumEnum.is_boxed) (decltype(this->as.SumEnum.is_boxed))(move(rhs.as.SumEnum.is_boxed));
new (&this->as.SumEnum.fields) (decltype(this->as.SumEnum.fields))(move(rhs.as.SumEnum.fields));
new (&this->as.SumEnum.variants) (decltype(this->as.SumEnum.variants))(move(rhs.as.SumEnum.variants));
break;
case 4 /* Garbage */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
RecordType::~RecordType(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void RecordType::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Struct */:this->as.Struct.fields.~DynamicArray();
this->as.Struct.super_type.~Optional();
break;
case 1 /* Class */:this->as.Class.fields.~DynamicArray();
this->as.Class.super_type.~Optional();
break;
case 2 /* ValueEnum */:this->as.ValueEnum.underlying_type.~NonnullRefPtr();
this->as.ValueEnum.variants.~DynamicArray();
break;
case 3 /* SumEnum */:this->as.SumEnum.fields.~DynamicArray();
this->as.SumEnum.variants.~DynamicArray();
break;
case 4 /* Garbage */:break;
}
}
ByteString parser::RecordType::record_type_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("struct"sv)));
};/*case end*/
case 1 /* Class */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("class"sv)));
};/*case end*/
case 2 /* ValueEnum */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("value enum"sv)));
};/*case end*/
case 3 /* SumEnum */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("sum enum"sv)));
};/*case end*/
case 4 /* Garbage */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("<garbage record type>"sv)));
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

ByteString parser::FunctionType::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Normal */: {
return ByteString("FunctionType::Normal"sv);
break;}
case 1 /* Destructor */: {
return ByteString("FunctionType::Destructor"sv);
break;}
case 2 /* ImplicitConstructor */: {
return ByteString("FunctionType::ImplicitConstructor"sv);
break;}
case 3 /* ImplicitEnumConstructor */: {
return ByteString("FunctionType::ImplicitEnumConstructor"sv);
break;}
case 4 /* ExternalClassConstructor */: {
return ByteString("FunctionType::ExternalClassConstructor"sv);
break;}
case 5 /* Expression */: {
return ByteString("FunctionType::Expression"sv);
break;}
case 6 /* Closure */: {
return ByteString("FunctionType::Closure"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] FunctionType FunctionType::Normal(){
FunctionType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionType FunctionType::Destructor(){
FunctionType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionType FunctionType::ImplicitConstructor(){
FunctionType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionType FunctionType::ImplicitEnumConstructor(){
FunctionType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionType FunctionType::ExternalClassConstructor(){
FunctionType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionType FunctionType::Expression(){
FunctionType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionType FunctionType::Closure(){
FunctionType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
FunctionType& FunctionType::operator=(FunctionType const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Normal */:
break;
case 1 /* Destructor */:
break;
case 2 /* ImplicitConstructor */:
break;
case 3 /* ImplicitEnumConstructor */:
break;
case 4 /* ExternalClassConstructor */:
break;
case 5 /* Expression */:
break;
case 6 /* Closure */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Normal */:
break;
case 1 /* Destructor */:
break;
case 2 /* ImplicitConstructor */:
break;
case 3 /* ImplicitEnumConstructor */:
break;
case 4 /* ExternalClassConstructor */:
break;
case 5 /* Expression */:
break;
case 6 /* Closure */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
FunctionType::FunctionType(FunctionType const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Normal */:
break;
case 1 /* Destructor */:
break;
case 2 /* ImplicitConstructor */:
break;
case 3 /* ImplicitEnumConstructor */:
break;
case 4 /* ExternalClassConstructor */:
break;
case 5 /* Expression */:
break;
case 6 /* Closure */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
FunctionType& FunctionType::operator=(FunctionType &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Normal */:
break;
case 1 /* Destructor */:
break;
case 2 /* ImplicitConstructor */:
break;
case 3 /* ImplicitEnumConstructor */:
break;
case 4 /* ExternalClassConstructor */:
break;
case 5 /* Expression */:
break;
case 6 /* Closure */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Normal */:
break;
case 1 /* Destructor */:
break;
case 2 /* ImplicitConstructor */:
break;
case 3 /* ImplicitEnumConstructor */:
break;
case 4 /* ExternalClassConstructor */:
break;
case 5 /* Expression */:
break;
case 6 /* Closure */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
FunctionType::FunctionType(FunctionType &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Normal */:
break;
case 1 /* Destructor */:
break;
case 2 /* ImplicitConstructor */:
break;
case 3 /* ImplicitEnumConstructor */:
break;
case 4 /* ExternalClassConstructor */:
break;
case 5 /* Expression */:
break;
case 6 /* Closure */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
FunctionType::~FunctionType(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void FunctionType::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Normal */:break;
case 1 /* Destructor */:break;
case 2 /* ImplicitConstructor */:break;
case 3 /* ImplicitEnumConstructor */:break;
case 4 /* ExternalClassConstructor */:break;
case 5 /* Expression */:break;
case 6 /* Closure */:break;
}
}
ByteString parser::ArgumentStoreLevel::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* InObject */: {
builder.append("ArgumentStoreLevel::InObject"sv);
[[maybe_unused]] auto const& that = this->as.InObject;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("argument_index: {}", that.argument_index);
}
builder.append(")"sv);
break;}
case 1 /* InStaticStorage */: {
return ByteString("ArgumentStoreLevel::InStaticStorage"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] ArgumentStoreLevel ArgumentStoreLevel::InObject(size_t argument_index){
ArgumentStoreLevel __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.InObject.argument_index) (decltype(argument_index))(move(argument_index));
return __jakt_uninit_enum;
}
[[nodiscard]] ArgumentStoreLevel ArgumentStoreLevel::InStaticStorage(){
ArgumentStoreLevel __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
ArgumentStoreLevel& ArgumentStoreLevel::operator=(ArgumentStoreLevel const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* InObject */:
new (&this->as.InObject.argument_index) (decltype(this->as.InObject.argument_index))(rhs.as.InObject.argument_index);
break;
case 1 /* InStaticStorage */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* InObject */:
this->as.InObject.argument_index = rhs.as.InObject.argument_index;
break;
case 1 /* InStaticStorage */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ArgumentStoreLevel::ArgumentStoreLevel(ArgumentStoreLevel const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* InObject */:
new (&this->as.InObject.argument_index) (decltype(this->as.InObject.argument_index))(rhs.as.InObject.argument_index);
break;
case 1 /* InStaticStorage */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ArgumentStoreLevel& ArgumentStoreLevel::operator=(ArgumentStoreLevel &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* InObject */:
new (&this->as.InObject.argument_index) (decltype(this->as.InObject.argument_index))(move(rhs.as.InObject.argument_index));
break;
case 1 /* InStaticStorage */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* InObject */:
this->as.InObject.argument_index = move(rhs.as.InObject.argument_index);
break;
case 1 /* InStaticStorage */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ArgumentStoreLevel::ArgumentStoreLevel(ArgumentStoreLevel &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* InObject */:
new (&this->as.InObject.argument_index) (decltype(this->as.InObject.argument_index))(move(rhs.as.InObject.argument_index));
break;
case 1 /* InStaticStorage */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ArgumentStoreLevel::~ArgumentStoreLevel(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ArgumentStoreLevel::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* InObject */:break;
case 1 /* InStaticStorage */:break;
}
}
ByteString parser::InlineState::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Default */: {
return ByteString("InlineState::Default"sv);
break;}
case 1 /* MakeDefinitionAvailable */: {
return ByteString("InlineState::MakeDefinitionAvailable"sv);
break;}
case 2 /* ForceInline */: {
return ByteString("InlineState::ForceInline"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] InlineState InlineState::Default(){
InlineState __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] InlineState InlineState::MakeDefinitionAvailable(){
InlineState __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] InlineState InlineState::ForceInline(){
InlineState __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
InlineState& InlineState::operator=(InlineState const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* MakeDefinitionAvailable */:
break;
case 2 /* ForceInline */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* MakeDefinitionAvailable */:
break;
case 2 /* ForceInline */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
InlineState::InlineState(InlineState const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* MakeDefinitionAvailable */:
break;
case 2 /* ForceInline */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
InlineState& InlineState::operator=(InlineState &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* MakeDefinitionAvailable */:
break;
case 2 /* ForceInline */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* MakeDefinitionAvailable */:
break;
case 2 /* ForceInline */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
InlineState::InlineState(InlineState &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Default */:
break;
case 1 /* MakeDefinitionAvailable */:
break;
case 2 /* ForceInline */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
InlineState::~InlineState(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void InlineState::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Default */:break;
case 1 /* MakeDefinitionAvailable */:break;
case 2 /* ForceInline */:break;
}
}
ByteString parser::ParsedTraitRequirements::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Nothing */: {
return ByteString("ParsedTraitRequirements::Nothing"sv);
break;}
case 1 /* Methods */: {
builder.append("ParsedTraitRequirements::Methods"sv);
[[maybe_unused]] auto const& that = this->as.Methods;
builder.appendff("({})", that.value);
break;}
case 2 /* ComptimeExpression */: {
builder.append("ParsedTraitRequirements::ComptimeExpression"sv);
[[maybe_unused]] auto const& that = this->as.ComptimeExpression;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] ParsedTraitRequirements ParsedTraitRequirements::Nothing(){
ParsedTraitRequirements __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedTraitRequirements ParsedTraitRequirements::Methods(JaktInternal::DynamicArray<parser::ParsedFunction> value){
ParsedTraitRequirements __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Methods.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedTraitRequirements ParsedTraitRequirements::ComptimeExpression(NonnullRefPtr<typename parser::ParsedExpression> value){
ParsedTraitRequirements __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.ComptimeExpression.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
ParsedTraitRequirements& ParsedTraitRequirements::operator=(ParsedTraitRequirements const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
new (&this->as.Methods.value) (decltype(this->as.Methods.value))(rhs.as.Methods.value);
break;
case 2 /* ComptimeExpression */:
new (&this->as.ComptimeExpression.value) (decltype(this->as.ComptimeExpression.value))(rhs.as.ComptimeExpression.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
this->as.Methods.value = rhs.as.Methods.value;
break;
case 2 /* ComptimeExpression */:
this->as.ComptimeExpression.value = rhs.as.ComptimeExpression.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedTraitRequirements::ParsedTraitRequirements(ParsedTraitRequirements const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
new (&this->as.Methods.value) (decltype(this->as.Methods.value))(rhs.as.Methods.value);
break;
case 2 /* ComptimeExpression */:
new (&this->as.ComptimeExpression.value) (decltype(this->as.ComptimeExpression.value))(rhs.as.ComptimeExpression.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ParsedTraitRequirements& ParsedTraitRequirements::operator=(ParsedTraitRequirements &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
new (&this->as.Methods.value) (decltype(this->as.Methods.value))(move(rhs.as.Methods.value));
break;
case 2 /* ComptimeExpression */:
new (&this->as.ComptimeExpression.value) (decltype(this->as.ComptimeExpression.value))(move(rhs.as.ComptimeExpression.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
this->as.Methods.value = move(rhs.as.Methods.value);
break;
case 2 /* ComptimeExpression */:
this->as.ComptimeExpression.value = move(rhs.as.ComptimeExpression.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedTraitRequirements::ParsedTraitRequirements(ParsedTraitRequirements &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
new (&this->as.Methods.value) (decltype(this->as.Methods.value))(move(rhs.as.Methods.value));
break;
case 2 /* ComptimeExpression */:
new (&this->as.ComptimeExpression.value) (decltype(this->as.ComptimeExpression.value))(move(rhs.as.ComptimeExpression.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ParsedTraitRequirements::~ParsedTraitRequirements(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ParsedTraitRequirements::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Nothing */:break;
case 1 /* Methods */:this->as.Methods.value.~DynamicArray();
break;
case 2 /* ComptimeExpression */:this->as.ComptimeExpression.value.~NonnullRefPtr();
break;
}
}
ByteString parser::ParsedStatement::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Expression */: {
builder.append("ParsedStatement::Expression"sv);
[[maybe_unused]] auto const& that = this->as.Expression;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* Defer */: {
builder.append("ParsedStatement::Defer"sv);
[[maybe_unused]] auto const& that = this->as.Defer;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("statement: {}, ", that.statement);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 2 /* UnsafeBlock */: {
builder.append("ParsedStatement::UnsafeBlock"sv);
[[maybe_unused]] auto const& that = this->as.UnsafeBlock;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 3 /* DestructuringAssignment */: {
builder.append("ParsedStatement::DestructuringAssignment"sv);
[[maybe_unused]] auto const& that = this->as.DestructuringAssignment;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("vars: {}, ", that.vars);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var_decl: {}, ", that.var_decl);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 4 /* VarDecl */: {
builder.append("ParsedStatement::VarDecl"sv);
[[maybe_unused]] auto const& that = this->as.VarDecl;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var: {}, ", that.var);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("init: {}, ", that.init);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 5 /* If */: {
builder.append("ParsedStatement::If"sv);
[[maybe_unused]] auto const& that = this->as.If;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("condition: {}, ", that.condition);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("then_block: {}, ", that.then_block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("else_statement: {}, ", that.else_statement);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 6 /* Block */: {
builder.append("ParsedStatement::Block"sv);
[[maybe_unused]] auto const& that = this->as.Block;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 7 /* Loop */: {
builder.append("ParsedStatement::Loop"sv);
[[maybe_unused]] auto const& that = this->as.Loop;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 8 /* While */: {
builder.append("ParsedStatement::While"sv);
[[maybe_unused]] auto const& that = this->as.While;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("condition: {}, ", that.condition);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 9 /* For */: {
builder.append("ParsedStatement::For"sv);
[[maybe_unused]] auto const& that = this->as.For;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("iterator_name: \"{}\", ", that.iterator_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", that.name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_destructuring: {}, ", that.is_destructuring);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("range: {}, ", that.range);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 10 /* Break */: {
builder.append("ParsedStatement::Break"sv);
[[maybe_unused]] auto const& that = this->as.Break;
builder.appendff("({})", that.value);
break;}
case 11 /* Continue */: {
builder.append("ParsedStatement::Continue"sv);
[[maybe_unused]] auto const& that = this->as.Continue;
builder.appendff("({})", that.value);
break;}
case 12 /* Return */: {
builder.append("ParsedStatement::Return"sv);
[[maybe_unused]] auto const& that = this->as.Return;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 13 /* Throw */: {
builder.append("ParsedStatement::Throw"sv);
[[maybe_unused]] auto const& that = this->as.Throw;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 14 /* Yield */: {
builder.append("ParsedStatement::Yield"sv);
[[maybe_unused]] auto const& that = this->as.Yield;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 15 /* InlineCpp */: {
builder.append("ParsedStatement::InlineCpp"sv);
[[maybe_unused]] auto const& that = this->as.InlineCpp;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 16 /* Guard */: {
builder.append("ParsedStatement::Guard"sv);
[[maybe_unused]] auto const& that = this->as.Guard;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("else_block: {}, ", that.else_block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("remaining_code: {}, ", that.remaining_code);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 17 /* Garbage */: {
builder.append("ParsedStatement::Garbage"sv);
[[maybe_unused]] auto const& that = this->as.Garbage;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Expression(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->as.Expression.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Expression.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Defer(NonnullRefPtr<typename parser::ParsedStatement> statement, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->as.Defer.statement) (decltype(statement))(move(statement));
new (&__jakt_uninit_enum->as.Defer.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::UnsafeBlock(parser::ParsedBlock block, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->as.UnsafeBlock.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.UnsafeBlock.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::DestructuringAssignment(JaktInternal::DynamicArray<parser::ParsedVarDecl> vars, NonnullRefPtr<typename parser::ParsedStatement> var_decl, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->as.DestructuringAssignment.vars) (decltype(vars))(move(vars));
new (&__jakt_uninit_enum->as.DestructuringAssignment.var_decl) (decltype(var_decl))(move(var_decl));
new (&__jakt_uninit_enum->as.DestructuringAssignment.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::VarDecl(parser::ParsedVarDecl var, NonnullRefPtr<typename parser::ParsedExpression> init, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->as.VarDecl.var) (decltype(var))(move(var));
new (&__jakt_uninit_enum->as.VarDecl.init) (decltype(init))(move(init));
new (&__jakt_uninit_enum->as.VarDecl.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::If(NonnullRefPtr<typename parser::ParsedExpression> condition, parser::ParsedBlock then_block, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> else_statement, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->as.If.condition) (decltype(condition))(move(condition));
new (&__jakt_uninit_enum->as.If.then_block) (decltype(then_block))(move(then_block));
new (&__jakt_uninit_enum->as.If.else_statement) (decltype(else_statement))(move(else_statement));
new (&__jakt_uninit_enum->as.If.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Block(parser::ParsedBlock block, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->as.Block.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Block.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Loop(parser::ParsedBlock block, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->as.Loop.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Loop.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::While(NonnullRefPtr<typename parser::ParsedExpression> condition, parser::ParsedBlock block, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->as.While.condition) (decltype(condition))(move(condition));
new (&__jakt_uninit_enum->as.While.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.While.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::For(ByteString iterator_name, utility::Span name_span, bool is_destructuring, NonnullRefPtr<typename parser::ParsedExpression> range, parser::ParsedBlock block, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->as.For.iterator_name) (decltype(iterator_name))(move(iterator_name));
new (&__jakt_uninit_enum->as.For.name_span) (decltype(name_span))(move(name_span));
new (&__jakt_uninit_enum->as.For.is_destructuring) (decltype(is_destructuring))(move(is_destructuring));
new (&__jakt_uninit_enum->as.For.range) (decltype(range))(move(range));
new (&__jakt_uninit_enum->as.For.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.For.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Break(utility::Span value){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->as.Break.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Continue(utility::Span value){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->as.Continue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Return(JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> expr, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->as.Return.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Return.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Throw(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->as.Throw.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Throw.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Yield(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->as.Yield.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Yield.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::InlineCpp(parser::ParsedBlock block, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 16;
new (&__jakt_uninit_enum->as.InlineCpp.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.InlineCpp.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Guard(NonnullRefPtr<typename parser::ParsedExpression> expr, parser::ParsedBlock else_block, parser::ParsedBlock remaining_code, utility::Span span){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 17;
new (&__jakt_uninit_enum->as.Guard.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Guard.else_block) (decltype(else_block))(move(else_block));
new (&__jakt_uninit_enum->as.Guard.remaining_code) (decltype(remaining_code))(move(remaining_code));
new (&__jakt_uninit_enum->as.Guard.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedStatement> ParsedStatement::Garbage(utility::Span value){
NonnullRefPtr<ParsedStatement> __jakt_uninit_enum = adopt_ref(*new ParsedStatement);
__jakt_uninit_enum->__jakt_variant_index = 18;
new (&__jakt_uninit_enum->as.Garbage.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
ParsedStatement& ParsedStatement::operator=(ParsedStatement const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.expr) (decltype(this->as.Expression.expr))(rhs.as.Expression.expr);
new (&this->as.Expression.span) (decltype(this->as.Expression.span))(rhs.as.Expression.span);
break;
case 1 /* Defer */:
new (&this->as.Defer.statement) (decltype(this->as.Defer.statement))(rhs.as.Defer.statement);
new (&this->as.Defer.span) (decltype(this->as.Defer.span))(rhs.as.Defer.span);
break;
case 2 /* UnsafeBlock */:
new (&this->as.UnsafeBlock.block) (decltype(this->as.UnsafeBlock.block))(rhs.as.UnsafeBlock.block);
new (&this->as.UnsafeBlock.span) (decltype(this->as.UnsafeBlock.span))(rhs.as.UnsafeBlock.span);
break;
case 3 /* DestructuringAssignment */:
new (&this->as.DestructuringAssignment.vars) (decltype(this->as.DestructuringAssignment.vars))(rhs.as.DestructuringAssignment.vars);
new (&this->as.DestructuringAssignment.var_decl) (decltype(this->as.DestructuringAssignment.var_decl))(rhs.as.DestructuringAssignment.var_decl);
new (&this->as.DestructuringAssignment.span) (decltype(this->as.DestructuringAssignment.span))(rhs.as.DestructuringAssignment.span);
break;
case 4 /* VarDecl */:
new (&this->as.VarDecl.var) (decltype(this->as.VarDecl.var))(rhs.as.VarDecl.var);
new (&this->as.VarDecl.init) (decltype(this->as.VarDecl.init))(rhs.as.VarDecl.init);
new (&this->as.VarDecl.span) (decltype(this->as.VarDecl.span))(rhs.as.VarDecl.span);
break;
case 5 /* If */:
new (&this->as.If.condition) (decltype(this->as.If.condition))(rhs.as.If.condition);
new (&this->as.If.then_block) (decltype(this->as.If.then_block))(rhs.as.If.then_block);
new (&this->as.If.else_statement) (decltype(this->as.If.else_statement))(rhs.as.If.else_statement);
new (&this->as.If.span) (decltype(this->as.If.span))(rhs.as.If.span);
break;
case 6 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(rhs.as.Block.block);
new (&this->as.Block.span) (decltype(this->as.Block.span))(rhs.as.Block.span);
break;
case 7 /* Loop */:
new (&this->as.Loop.block) (decltype(this->as.Loop.block))(rhs.as.Loop.block);
new (&this->as.Loop.span) (decltype(this->as.Loop.span))(rhs.as.Loop.span);
break;
case 8 /* While */:
new (&this->as.While.condition) (decltype(this->as.While.condition))(rhs.as.While.condition);
new (&this->as.While.block) (decltype(this->as.While.block))(rhs.as.While.block);
new (&this->as.While.span) (decltype(this->as.While.span))(rhs.as.While.span);
break;
case 9 /* For */:
new (&this->as.For.iterator_name) (decltype(this->as.For.iterator_name))(rhs.as.For.iterator_name);
new (&this->as.For.name_span) (decltype(this->as.For.name_span))(rhs.as.For.name_span);
new (&this->as.For.is_destructuring) (decltype(this->as.For.is_destructuring))(rhs.as.For.is_destructuring);
new (&this->as.For.range) (decltype(this->as.For.range))(rhs.as.For.range);
new (&this->as.For.block) (decltype(this->as.For.block))(rhs.as.For.block);
new (&this->as.For.span) (decltype(this->as.For.span))(rhs.as.For.span);
break;
case 10 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(rhs.as.Break.value);
break;
case 11 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(rhs.as.Continue.value);
break;
case 12 /* Return */:
new (&this->as.Return.expr) (decltype(this->as.Return.expr))(rhs.as.Return.expr);
new (&this->as.Return.span) (decltype(this->as.Return.span))(rhs.as.Return.span);
break;
case 13 /* Throw */:
new (&this->as.Throw.expr) (decltype(this->as.Throw.expr))(rhs.as.Throw.expr);
new (&this->as.Throw.span) (decltype(this->as.Throw.span))(rhs.as.Throw.span);
break;
case 14 /* Yield */:
new (&this->as.Yield.expr) (decltype(this->as.Yield.expr))(rhs.as.Yield.expr);
new (&this->as.Yield.span) (decltype(this->as.Yield.span))(rhs.as.Yield.span);
break;
case 15 /* InlineCpp */:
new (&this->as.InlineCpp.block) (decltype(this->as.InlineCpp.block))(rhs.as.InlineCpp.block);
new (&this->as.InlineCpp.span) (decltype(this->as.InlineCpp.span))(rhs.as.InlineCpp.span);
break;
case 16 /* Guard */:
new (&this->as.Guard.expr) (decltype(this->as.Guard.expr))(rhs.as.Guard.expr);
new (&this->as.Guard.else_block) (decltype(this->as.Guard.else_block))(rhs.as.Guard.else_block);
new (&this->as.Guard.remaining_code) (decltype(this->as.Guard.remaining_code))(rhs.as.Guard.remaining_code);
new (&this->as.Guard.span) (decltype(this->as.Guard.span))(rhs.as.Guard.span);
break;
case 17 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(rhs.as.Garbage.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.expr = rhs.as.Expression.expr;
this->as.Expression.span = rhs.as.Expression.span;
break;
case 1 /* Defer */:
this->as.Defer.statement = rhs.as.Defer.statement;
this->as.Defer.span = rhs.as.Defer.span;
break;
case 2 /* UnsafeBlock */:
this->as.UnsafeBlock.block = rhs.as.UnsafeBlock.block;
this->as.UnsafeBlock.span = rhs.as.UnsafeBlock.span;
break;
case 3 /* DestructuringAssignment */:
this->as.DestructuringAssignment.vars = rhs.as.DestructuringAssignment.vars;
this->as.DestructuringAssignment.var_decl = rhs.as.DestructuringAssignment.var_decl;
this->as.DestructuringAssignment.span = rhs.as.DestructuringAssignment.span;
break;
case 4 /* VarDecl */:
this->as.VarDecl.var = rhs.as.VarDecl.var;
this->as.VarDecl.init = rhs.as.VarDecl.init;
this->as.VarDecl.span = rhs.as.VarDecl.span;
break;
case 5 /* If */:
this->as.If.condition = rhs.as.If.condition;
this->as.If.then_block = rhs.as.If.then_block;
this->as.If.else_statement = rhs.as.If.else_statement;
this->as.If.span = rhs.as.If.span;
break;
case 6 /* Block */:
this->as.Block.block = rhs.as.Block.block;
this->as.Block.span = rhs.as.Block.span;
break;
case 7 /* Loop */:
this->as.Loop.block = rhs.as.Loop.block;
this->as.Loop.span = rhs.as.Loop.span;
break;
case 8 /* While */:
this->as.While.condition = rhs.as.While.condition;
this->as.While.block = rhs.as.While.block;
this->as.While.span = rhs.as.While.span;
break;
case 9 /* For */:
this->as.For.iterator_name = rhs.as.For.iterator_name;
this->as.For.name_span = rhs.as.For.name_span;
this->as.For.is_destructuring = rhs.as.For.is_destructuring;
this->as.For.range = rhs.as.For.range;
this->as.For.block = rhs.as.For.block;
this->as.For.span = rhs.as.For.span;
break;
case 10 /* Break */:
this->as.Break.value = rhs.as.Break.value;
break;
case 11 /* Continue */:
this->as.Continue.value = rhs.as.Continue.value;
break;
case 12 /* Return */:
this->as.Return.expr = rhs.as.Return.expr;
this->as.Return.span = rhs.as.Return.span;
break;
case 13 /* Throw */:
this->as.Throw.expr = rhs.as.Throw.expr;
this->as.Throw.span = rhs.as.Throw.span;
break;
case 14 /* Yield */:
this->as.Yield.expr = rhs.as.Yield.expr;
this->as.Yield.span = rhs.as.Yield.span;
break;
case 15 /* InlineCpp */:
this->as.InlineCpp.block = rhs.as.InlineCpp.block;
this->as.InlineCpp.span = rhs.as.InlineCpp.span;
break;
case 16 /* Guard */:
this->as.Guard.expr = rhs.as.Guard.expr;
this->as.Guard.else_block = rhs.as.Guard.else_block;
this->as.Guard.remaining_code = rhs.as.Guard.remaining_code;
this->as.Guard.span = rhs.as.Guard.span;
break;
case 17 /* Garbage */:
this->as.Garbage.value = rhs.as.Garbage.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedStatement::ParsedStatement(ParsedStatement const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.expr) (decltype(this->as.Expression.expr))(rhs.as.Expression.expr);
new (&this->as.Expression.span) (decltype(this->as.Expression.span))(rhs.as.Expression.span);
break;
case 1 /* Defer */:
new (&this->as.Defer.statement) (decltype(this->as.Defer.statement))(rhs.as.Defer.statement);
new (&this->as.Defer.span) (decltype(this->as.Defer.span))(rhs.as.Defer.span);
break;
case 2 /* UnsafeBlock */:
new (&this->as.UnsafeBlock.block) (decltype(this->as.UnsafeBlock.block))(rhs.as.UnsafeBlock.block);
new (&this->as.UnsafeBlock.span) (decltype(this->as.UnsafeBlock.span))(rhs.as.UnsafeBlock.span);
break;
case 3 /* DestructuringAssignment */:
new (&this->as.DestructuringAssignment.vars) (decltype(this->as.DestructuringAssignment.vars))(rhs.as.DestructuringAssignment.vars);
new (&this->as.DestructuringAssignment.var_decl) (decltype(this->as.DestructuringAssignment.var_decl))(rhs.as.DestructuringAssignment.var_decl);
new (&this->as.DestructuringAssignment.span) (decltype(this->as.DestructuringAssignment.span))(rhs.as.DestructuringAssignment.span);
break;
case 4 /* VarDecl */:
new (&this->as.VarDecl.var) (decltype(this->as.VarDecl.var))(rhs.as.VarDecl.var);
new (&this->as.VarDecl.init) (decltype(this->as.VarDecl.init))(rhs.as.VarDecl.init);
new (&this->as.VarDecl.span) (decltype(this->as.VarDecl.span))(rhs.as.VarDecl.span);
break;
case 5 /* If */:
new (&this->as.If.condition) (decltype(this->as.If.condition))(rhs.as.If.condition);
new (&this->as.If.then_block) (decltype(this->as.If.then_block))(rhs.as.If.then_block);
new (&this->as.If.else_statement) (decltype(this->as.If.else_statement))(rhs.as.If.else_statement);
new (&this->as.If.span) (decltype(this->as.If.span))(rhs.as.If.span);
break;
case 6 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(rhs.as.Block.block);
new (&this->as.Block.span) (decltype(this->as.Block.span))(rhs.as.Block.span);
break;
case 7 /* Loop */:
new (&this->as.Loop.block) (decltype(this->as.Loop.block))(rhs.as.Loop.block);
new (&this->as.Loop.span) (decltype(this->as.Loop.span))(rhs.as.Loop.span);
break;
case 8 /* While */:
new (&this->as.While.condition) (decltype(this->as.While.condition))(rhs.as.While.condition);
new (&this->as.While.block) (decltype(this->as.While.block))(rhs.as.While.block);
new (&this->as.While.span) (decltype(this->as.While.span))(rhs.as.While.span);
break;
case 9 /* For */:
new (&this->as.For.iterator_name) (decltype(this->as.For.iterator_name))(rhs.as.For.iterator_name);
new (&this->as.For.name_span) (decltype(this->as.For.name_span))(rhs.as.For.name_span);
new (&this->as.For.is_destructuring) (decltype(this->as.For.is_destructuring))(rhs.as.For.is_destructuring);
new (&this->as.For.range) (decltype(this->as.For.range))(rhs.as.For.range);
new (&this->as.For.block) (decltype(this->as.For.block))(rhs.as.For.block);
new (&this->as.For.span) (decltype(this->as.For.span))(rhs.as.For.span);
break;
case 10 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(rhs.as.Break.value);
break;
case 11 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(rhs.as.Continue.value);
break;
case 12 /* Return */:
new (&this->as.Return.expr) (decltype(this->as.Return.expr))(rhs.as.Return.expr);
new (&this->as.Return.span) (decltype(this->as.Return.span))(rhs.as.Return.span);
break;
case 13 /* Throw */:
new (&this->as.Throw.expr) (decltype(this->as.Throw.expr))(rhs.as.Throw.expr);
new (&this->as.Throw.span) (decltype(this->as.Throw.span))(rhs.as.Throw.span);
break;
case 14 /* Yield */:
new (&this->as.Yield.expr) (decltype(this->as.Yield.expr))(rhs.as.Yield.expr);
new (&this->as.Yield.span) (decltype(this->as.Yield.span))(rhs.as.Yield.span);
break;
case 15 /* InlineCpp */:
new (&this->as.InlineCpp.block) (decltype(this->as.InlineCpp.block))(rhs.as.InlineCpp.block);
new (&this->as.InlineCpp.span) (decltype(this->as.InlineCpp.span))(rhs.as.InlineCpp.span);
break;
case 16 /* Guard */:
new (&this->as.Guard.expr) (decltype(this->as.Guard.expr))(rhs.as.Guard.expr);
new (&this->as.Guard.else_block) (decltype(this->as.Guard.else_block))(rhs.as.Guard.else_block);
new (&this->as.Guard.remaining_code) (decltype(this->as.Guard.remaining_code))(rhs.as.Guard.remaining_code);
new (&this->as.Guard.span) (decltype(this->as.Guard.span))(rhs.as.Guard.span);
break;
case 17 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(rhs.as.Garbage.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ParsedStatement& ParsedStatement::operator=(ParsedStatement &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.expr) (decltype(this->as.Expression.expr))(move(rhs.as.Expression.expr));
new (&this->as.Expression.span) (decltype(this->as.Expression.span))(move(rhs.as.Expression.span));
break;
case 1 /* Defer */:
new (&this->as.Defer.statement) (decltype(this->as.Defer.statement))(move(rhs.as.Defer.statement));
new (&this->as.Defer.span) (decltype(this->as.Defer.span))(move(rhs.as.Defer.span));
break;
case 2 /* UnsafeBlock */:
new (&this->as.UnsafeBlock.block) (decltype(this->as.UnsafeBlock.block))(move(rhs.as.UnsafeBlock.block));
new (&this->as.UnsafeBlock.span) (decltype(this->as.UnsafeBlock.span))(move(rhs.as.UnsafeBlock.span));
break;
case 3 /* DestructuringAssignment */:
new (&this->as.DestructuringAssignment.vars) (decltype(this->as.DestructuringAssignment.vars))(move(rhs.as.DestructuringAssignment.vars));
new (&this->as.DestructuringAssignment.var_decl) (decltype(this->as.DestructuringAssignment.var_decl))(move(rhs.as.DestructuringAssignment.var_decl));
new (&this->as.DestructuringAssignment.span) (decltype(this->as.DestructuringAssignment.span))(move(rhs.as.DestructuringAssignment.span));
break;
case 4 /* VarDecl */:
new (&this->as.VarDecl.var) (decltype(this->as.VarDecl.var))(move(rhs.as.VarDecl.var));
new (&this->as.VarDecl.init) (decltype(this->as.VarDecl.init))(move(rhs.as.VarDecl.init));
new (&this->as.VarDecl.span) (decltype(this->as.VarDecl.span))(move(rhs.as.VarDecl.span));
break;
case 5 /* If */:
new (&this->as.If.condition) (decltype(this->as.If.condition))(move(rhs.as.If.condition));
new (&this->as.If.then_block) (decltype(this->as.If.then_block))(move(rhs.as.If.then_block));
new (&this->as.If.else_statement) (decltype(this->as.If.else_statement))(move(rhs.as.If.else_statement));
new (&this->as.If.span) (decltype(this->as.If.span))(move(rhs.as.If.span));
break;
case 6 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(move(rhs.as.Block.block));
new (&this->as.Block.span) (decltype(this->as.Block.span))(move(rhs.as.Block.span));
break;
case 7 /* Loop */:
new (&this->as.Loop.block) (decltype(this->as.Loop.block))(move(rhs.as.Loop.block));
new (&this->as.Loop.span) (decltype(this->as.Loop.span))(move(rhs.as.Loop.span));
break;
case 8 /* While */:
new (&this->as.While.condition) (decltype(this->as.While.condition))(move(rhs.as.While.condition));
new (&this->as.While.block) (decltype(this->as.While.block))(move(rhs.as.While.block));
new (&this->as.While.span) (decltype(this->as.While.span))(move(rhs.as.While.span));
break;
case 9 /* For */:
new (&this->as.For.iterator_name) (decltype(this->as.For.iterator_name))(move(rhs.as.For.iterator_name));
new (&this->as.For.name_span) (decltype(this->as.For.name_span))(move(rhs.as.For.name_span));
new (&this->as.For.is_destructuring) (decltype(this->as.For.is_destructuring))(move(rhs.as.For.is_destructuring));
new (&this->as.For.range) (decltype(this->as.For.range))(move(rhs.as.For.range));
new (&this->as.For.block) (decltype(this->as.For.block))(move(rhs.as.For.block));
new (&this->as.For.span) (decltype(this->as.For.span))(move(rhs.as.For.span));
break;
case 10 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(move(rhs.as.Break.value));
break;
case 11 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(move(rhs.as.Continue.value));
break;
case 12 /* Return */:
new (&this->as.Return.expr) (decltype(this->as.Return.expr))(move(rhs.as.Return.expr));
new (&this->as.Return.span) (decltype(this->as.Return.span))(move(rhs.as.Return.span));
break;
case 13 /* Throw */:
new (&this->as.Throw.expr) (decltype(this->as.Throw.expr))(move(rhs.as.Throw.expr));
new (&this->as.Throw.span) (decltype(this->as.Throw.span))(move(rhs.as.Throw.span));
break;
case 14 /* Yield */:
new (&this->as.Yield.expr) (decltype(this->as.Yield.expr))(move(rhs.as.Yield.expr));
new (&this->as.Yield.span) (decltype(this->as.Yield.span))(move(rhs.as.Yield.span));
break;
case 15 /* InlineCpp */:
new (&this->as.InlineCpp.block) (decltype(this->as.InlineCpp.block))(move(rhs.as.InlineCpp.block));
new (&this->as.InlineCpp.span) (decltype(this->as.InlineCpp.span))(move(rhs.as.InlineCpp.span));
break;
case 16 /* Guard */:
new (&this->as.Guard.expr) (decltype(this->as.Guard.expr))(move(rhs.as.Guard.expr));
new (&this->as.Guard.else_block) (decltype(this->as.Guard.else_block))(move(rhs.as.Guard.else_block));
new (&this->as.Guard.remaining_code) (decltype(this->as.Guard.remaining_code))(move(rhs.as.Guard.remaining_code));
new (&this->as.Guard.span) (decltype(this->as.Guard.span))(move(rhs.as.Guard.span));
break;
case 17 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(move(rhs.as.Garbage.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.expr = move(rhs.as.Expression.expr);
this->as.Expression.span = move(rhs.as.Expression.span);
break;
case 1 /* Defer */:
this->as.Defer.statement = move(rhs.as.Defer.statement);
this->as.Defer.span = move(rhs.as.Defer.span);
break;
case 2 /* UnsafeBlock */:
this->as.UnsafeBlock.block = move(rhs.as.UnsafeBlock.block);
this->as.UnsafeBlock.span = move(rhs.as.UnsafeBlock.span);
break;
case 3 /* DestructuringAssignment */:
this->as.DestructuringAssignment.vars = move(rhs.as.DestructuringAssignment.vars);
this->as.DestructuringAssignment.var_decl = move(rhs.as.DestructuringAssignment.var_decl);
this->as.DestructuringAssignment.span = move(rhs.as.DestructuringAssignment.span);
break;
case 4 /* VarDecl */:
this->as.VarDecl.var = move(rhs.as.VarDecl.var);
this->as.VarDecl.init = move(rhs.as.VarDecl.init);
this->as.VarDecl.span = move(rhs.as.VarDecl.span);
break;
case 5 /* If */:
this->as.If.condition = move(rhs.as.If.condition);
this->as.If.then_block = move(rhs.as.If.then_block);
this->as.If.else_statement = move(rhs.as.If.else_statement);
this->as.If.span = move(rhs.as.If.span);
break;
case 6 /* Block */:
this->as.Block.block = move(rhs.as.Block.block);
this->as.Block.span = move(rhs.as.Block.span);
break;
case 7 /* Loop */:
this->as.Loop.block = move(rhs.as.Loop.block);
this->as.Loop.span = move(rhs.as.Loop.span);
break;
case 8 /* While */:
this->as.While.condition = move(rhs.as.While.condition);
this->as.While.block = move(rhs.as.While.block);
this->as.While.span = move(rhs.as.While.span);
break;
case 9 /* For */:
this->as.For.iterator_name = move(rhs.as.For.iterator_name);
this->as.For.name_span = move(rhs.as.For.name_span);
this->as.For.is_destructuring = move(rhs.as.For.is_destructuring);
this->as.For.range = move(rhs.as.For.range);
this->as.For.block = move(rhs.as.For.block);
this->as.For.span = move(rhs.as.For.span);
break;
case 10 /* Break */:
this->as.Break.value = move(rhs.as.Break.value);
break;
case 11 /* Continue */:
this->as.Continue.value = move(rhs.as.Continue.value);
break;
case 12 /* Return */:
this->as.Return.expr = move(rhs.as.Return.expr);
this->as.Return.span = move(rhs.as.Return.span);
break;
case 13 /* Throw */:
this->as.Throw.expr = move(rhs.as.Throw.expr);
this->as.Throw.span = move(rhs.as.Throw.span);
break;
case 14 /* Yield */:
this->as.Yield.expr = move(rhs.as.Yield.expr);
this->as.Yield.span = move(rhs.as.Yield.span);
break;
case 15 /* InlineCpp */:
this->as.InlineCpp.block = move(rhs.as.InlineCpp.block);
this->as.InlineCpp.span = move(rhs.as.InlineCpp.span);
break;
case 16 /* Guard */:
this->as.Guard.expr = move(rhs.as.Guard.expr);
this->as.Guard.else_block = move(rhs.as.Guard.else_block);
this->as.Guard.remaining_code = move(rhs.as.Guard.remaining_code);
this->as.Guard.span = move(rhs.as.Guard.span);
break;
case 17 /* Garbage */:
this->as.Garbage.value = move(rhs.as.Garbage.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedStatement::ParsedStatement(ParsedStatement &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.expr) (decltype(this->as.Expression.expr))(move(rhs.as.Expression.expr));
new (&this->as.Expression.span) (decltype(this->as.Expression.span))(move(rhs.as.Expression.span));
break;
case 1 /* Defer */:
new (&this->as.Defer.statement) (decltype(this->as.Defer.statement))(move(rhs.as.Defer.statement));
new (&this->as.Defer.span) (decltype(this->as.Defer.span))(move(rhs.as.Defer.span));
break;
case 2 /* UnsafeBlock */:
new (&this->as.UnsafeBlock.block) (decltype(this->as.UnsafeBlock.block))(move(rhs.as.UnsafeBlock.block));
new (&this->as.UnsafeBlock.span) (decltype(this->as.UnsafeBlock.span))(move(rhs.as.UnsafeBlock.span));
break;
case 3 /* DestructuringAssignment */:
new (&this->as.DestructuringAssignment.vars) (decltype(this->as.DestructuringAssignment.vars))(move(rhs.as.DestructuringAssignment.vars));
new (&this->as.DestructuringAssignment.var_decl) (decltype(this->as.DestructuringAssignment.var_decl))(move(rhs.as.DestructuringAssignment.var_decl));
new (&this->as.DestructuringAssignment.span) (decltype(this->as.DestructuringAssignment.span))(move(rhs.as.DestructuringAssignment.span));
break;
case 4 /* VarDecl */:
new (&this->as.VarDecl.var) (decltype(this->as.VarDecl.var))(move(rhs.as.VarDecl.var));
new (&this->as.VarDecl.init) (decltype(this->as.VarDecl.init))(move(rhs.as.VarDecl.init));
new (&this->as.VarDecl.span) (decltype(this->as.VarDecl.span))(move(rhs.as.VarDecl.span));
break;
case 5 /* If */:
new (&this->as.If.condition) (decltype(this->as.If.condition))(move(rhs.as.If.condition));
new (&this->as.If.then_block) (decltype(this->as.If.then_block))(move(rhs.as.If.then_block));
new (&this->as.If.else_statement) (decltype(this->as.If.else_statement))(move(rhs.as.If.else_statement));
new (&this->as.If.span) (decltype(this->as.If.span))(move(rhs.as.If.span));
break;
case 6 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(move(rhs.as.Block.block));
new (&this->as.Block.span) (decltype(this->as.Block.span))(move(rhs.as.Block.span));
break;
case 7 /* Loop */:
new (&this->as.Loop.block) (decltype(this->as.Loop.block))(move(rhs.as.Loop.block));
new (&this->as.Loop.span) (decltype(this->as.Loop.span))(move(rhs.as.Loop.span));
break;
case 8 /* While */:
new (&this->as.While.condition) (decltype(this->as.While.condition))(move(rhs.as.While.condition));
new (&this->as.While.block) (decltype(this->as.While.block))(move(rhs.as.While.block));
new (&this->as.While.span) (decltype(this->as.While.span))(move(rhs.as.While.span));
break;
case 9 /* For */:
new (&this->as.For.iterator_name) (decltype(this->as.For.iterator_name))(move(rhs.as.For.iterator_name));
new (&this->as.For.name_span) (decltype(this->as.For.name_span))(move(rhs.as.For.name_span));
new (&this->as.For.is_destructuring) (decltype(this->as.For.is_destructuring))(move(rhs.as.For.is_destructuring));
new (&this->as.For.range) (decltype(this->as.For.range))(move(rhs.as.For.range));
new (&this->as.For.block) (decltype(this->as.For.block))(move(rhs.as.For.block));
new (&this->as.For.span) (decltype(this->as.For.span))(move(rhs.as.For.span));
break;
case 10 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(move(rhs.as.Break.value));
break;
case 11 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(move(rhs.as.Continue.value));
break;
case 12 /* Return */:
new (&this->as.Return.expr) (decltype(this->as.Return.expr))(move(rhs.as.Return.expr));
new (&this->as.Return.span) (decltype(this->as.Return.span))(move(rhs.as.Return.span));
break;
case 13 /* Throw */:
new (&this->as.Throw.expr) (decltype(this->as.Throw.expr))(move(rhs.as.Throw.expr));
new (&this->as.Throw.span) (decltype(this->as.Throw.span))(move(rhs.as.Throw.span));
break;
case 14 /* Yield */:
new (&this->as.Yield.expr) (decltype(this->as.Yield.expr))(move(rhs.as.Yield.expr));
new (&this->as.Yield.span) (decltype(this->as.Yield.span))(move(rhs.as.Yield.span));
break;
case 15 /* InlineCpp */:
new (&this->as.InlineCpp.block) (decltype(this->as.InlineCpp.block))(move(rhs.as.InlineCpp.block));
new (&this->as.InlineCpp.span) (decltype(this->as.InlineCpp.span))(move(rhs.as.InlineCpp.span));
break;
case 16 /* Guard */:
new (&this->as.Guard.expr) (decltype(this->as.Guard.expr))(move(rhs.as.Guard.expr));
new (&this->as.Guard.else_block) (decltype(this->as.Guard.else_block))(move(rhs.as.Guard.else_block));
new (&this->as.Guard.remaining_code) (decltype(this->as.Guard.remaining_code))(move(rhs.as.Guard.remaining_code));
new (&this->as.Guard.span) (decltype(this->as.Guard.span))(move(rhs.as.Guard.span));
break;
case 17 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(move(rhs.as.Garbage.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ParsedStatement::~ParsedStatement(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ParsedStatement::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Expression */:this->as.Expression.expr.~NonnullRefPtr();
this->as.Expression.span.~Span();
break;
case 1 /* Defer */:this->as.Defer.statement.~NonnullRefPtr();
this->as.Defer.span.~Span();
break;
case 2 /* UnsafeBlock */:this->as.UnsafeBlock.block.~ParsedBlock();
this->as.UnsafeBlock.span.~Span();
break;
case 3 /* DestructuringAssignment */:this->as.DestructuringAssignment.vars.~DynamicArray();
this->as.DestructuringAssignment.var_decl.~NonnullRefPtr();
this->as.DestructuringAssignment.span.~Span();
break;
case 4 /* VarDecl */:this->as.VarDecl.var.~ParsedVarDecl();
this->as.VarDecl.init.~NonnullRefPtr();
this->as.VarDecl.span.~Span();
break;
case 5 /* If */:this->as.If.condition.~NonnullRefPtr();
this->as.If.then_block.~ParsedBlock();
this->as.If.else_statement.~Optional();
this->as.If.span.~Span();
break;
case 6 /* Block */:this->as.Block.block.~ParsedBlock();
this->as.Block.span.~Span();
break;
case 7 /* Loop */:this->as.Loop.block.~ParsedBlock();
this->as.Loop.span.~Span();
break;
case 8 /* While */:this->as.While.condition.~NonnullRefPtr();
this->as.While.block.~ParsedBlock();
this->as.While.span.~Span();
break;
case 9 /* For */:this->as.For.iterator_name.~ByteString();
this->as.For.name_span.~Span();
this->as.For.range.~NonnullRefPtr();
this->as.For.block.~ParsedBlock();
this->as.For.span.~Span();
break;
case 10 /* Break */:this->as.Break.value.~Span();
break;
case 11 /* Continue */:this->as.Continue.value.~Span();
break;
case 12 /* Return */:this->as.Return.expr.~Optional();
this->as.Return.span.~Span();
break;
case 13 /* Throw */:this->as.Throw.expr.~NonnullRefPtr();
this->as.Throw.span.~Span();
break;
case 14 /* Yield */:this->as.Yield.expr.~NonnullRefPtr();
this->as.Yield.span.~Span();
break;
case 15 /* InlineCpp */:this->as.InlineCpp.block.~ParsedBlock();
this->as.InlineCpp.span.~Span();
break;
case 16 /* Guard */:this->as.Guard.expr.~NonnullRefPtr();
this->as.Guard.else_block.~ParsedBlock();
this->as.Guard.remaining_code.~ParsedBlock();
this->as.Guard.span.~Span();
break;
case 17 /* Garbage */:this->as.Garbage.value.~Span();
break;
}
}
bool parser::ParsedStatement::equals(NonnullRefPtr<typename parser::ParsedStatement> const rhs_statement) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((lhs_expr)->equals(rhs_expr)));
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
}));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename parser::ParsedStatement> const& lhs_statement = __jakt_match_value.statement;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename parser::ParsedStatement> const& rhs_statement = __jakt_match_value.statement;
return JaktInternal::ExplicitValue(((lhs_statement)->equals(rhs_statement)));
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
}));
};/*case end*/
case 2 /* UnsafeBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnsafeBlock;parser::ParsedBlock const& lhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* UnsafeBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnsafeBlock;parser::ParsedBlock const& rhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(((lhs_block).equals(rhs_block)));
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
}));
};/*case end*/
case 4 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;parser::ParsedVarDecl const& lhs_var = __jakt_match_value.var;
NonnullRefPtr<typename parser::ParsedExpression> const& lhs_init = __jakt_match_value.init;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;parser::ParsedVarDecl const& rhs_var = __jakt_match_value.var;
NonnullRefPtr<typename parser::ParsedExpression> const& rhs_init = __jakt_match_value.init;
return JaktInternal::ExplicitValue((((lhs_var).equals(rhs_var)) && ((lhs_init)->equals(rhs_init))));
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
}));
};/*case end*/
case 3 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<parser::ParsedVarDecl> const& lhs_vars = __jakt_match_value.vars;
NonnullRefPtr<typename parser::ParsedStatement> const& lhs_var_decl = __jakt_match_value.var_decl;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<parser::ParsedVarDecl> const& rhs_vars = __jakt_match_value.vars;
NonnullRefPtr<typename parser::ParsedStatement> const& rhs_var_decl = __jakt_match_value.var_decl;
{
if (((((lhs_vars).size())) != (((rhs_vars).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_vars).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((lhs_vars)[i])).equals(((rhs_vars)[i])))))){
return false;
}
}

}
}

if ((!(((lhs_var_decl)->equals(rhs_var_decl))))){
return false;
}
return true;
}
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
}));
};/*case end*/
case 5 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_condition = __jakt_match_value.condition;
parser::ParsedBlock const& lhs_then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const& lhs_else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_condition = __jakt_match_value.condition;
parser::ParsedBlock const& rhs_then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const& rhs_else_statement = __jakt_match_value.else_statement;
{
if ((!((((lhs_condition)->equals(rhs_condition)) && ((lhs_then_block).equals(rhs_then_block)))))){
return false;
}
if ((!(((lhs_else_statement).has_value())))){
return (!(((rhs_else_statement).has_value())));
}
else {
if ((!(((rhs_else_statement).has_value())))){
return false;
}
if ((((lhs_else_statement.value()))->equals((rhs_else_statement.value())))){
return true;
}
return false;
}

}
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
}));
};/*case end*/
case 6 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;parser::ParsedBlock const& lhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;parser::ParsedBlock const& rhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(((lhs_block).equals(rhs_block)));
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
}));
};/*case end*/
case 7 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;parser::ParsedBlock const& lhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;parser::ParsedBlock const& rhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(((lhs_block).equals(rhs_block)));
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
}));
};/*case end*/
case 8 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_condition = __jakt_match_value.condition;
parser::ParsedBlock const& lhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_condition = __jakt_match_value.condition;
parser::ParsedBlock const& rhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue((((lhs_condition)->equals(rhs_condition)) && ((lhs_block).equals(rhs_block))));
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
}));
};/*case end*/
case 9 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;ByteString const& lhs_iterator_name = __jakt_match_value.iterator_name;
NonnullRefPtr<typename parser::ParsedExpression> const& lhs_range = __jakt_match_value.range;
parser::ParsedBlock const& lhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;ByteString const& rhs_iterator_name = __jakt_match_value.iterator_name;
NonnullRefPtr<typename parser::ParsedExpression> const& rhs_range = __jakt_match_value.range;
parser::ParsedBlock const& rhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_114; {
__jakt_var_114 = ((((lhs_iterator_name) == (rhs_iterator_name)) && ((lhs_range)->equals(rhs_range))) && ((lhs_block).equals(rhs_block))); goto __jakt_label_108;

}
__jakt_label_108:; __jakt_var_114.release_value(); }));
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
}));
};/*case end*/
case 10 /* Break */: {
return JaktInternal::ExplicitValue(((rhs_statement)->__jakt_init_index() == 10 /* Break */));
};/*case end*/
case 11 /* Continue */: {
return JaktInternal::ExplicitValue(((rhs_statement)->__jakt_init_index() == 11 /* Continue */));
};/*case end*/
case 12 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& lhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& rhs_expr = __jakt_match_value.expr;
{
if ((!(((lhs_expr).has_value())))){
return (!(((rhs_expr).has_value())));
}
else {
if ((!(((rhs_expr).has_value())))){
return false;
}
if ((((lhs_expr.value()))->equals((rhs_expr.value())))){
return true;
}
return false;
}

}
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
}));
};/*case end*/
case 13 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((lhs_expr)->equals(rhs_expr)));
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
}));
};/*case end*/
case 14 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((lhs_expr)->equals(rhs_expr)));
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
}));
};/*case end*/
case 15 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;parser::ParsedBlock const& lhs_block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;parser::ParsedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(((lhs_block).equals(block)));
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
}));
};/*case end*/
case 16 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
parser::ParsedBlock const& lhs_else_block = __jakt_match_value.else_block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
parser::ParsedBlock const& rhs_else_block = __jakt_match_value.else_block;
return JaktInternal::ExplicitValue((((lhs_expr)->equals(rhs_expr)) && ((lhs_else_block).equals(rhs_else_block))));
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
}));
};/*case end*/
case 17 /* Garbage */: {
return JaktInternal::ExplicitValue(((rhs_statement)->__jakt_init_index() == 17 /* Garbage */));
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

utility::Span parser::ParsedStatement::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* UnsafeBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnsafeBlock;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 17 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
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

ByteString parser::BinaryOperator::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Add */: {
return ByteString("BinaryOperator::Add"sv);
break;}
case 1 /* Subtract */: {
return ByteString("BinaryOperator::Subtract"sv);
break;}
case 2 /* Multiply */: {
return ByteString("BinaryOperator::Multiply"sv);
break;}
case 3 /* Divide */: {
return ByteString("BinaryOperator::Divide"sv);
break;}
case 4 /* Modulo */: {
return ByteString("BinaryOperator::Modulo"sv);
break;}
case 5 /* LessThan */: {
return ByteString("BinaryOperator::LessThan"sv);
break;}
case 6 /* LessThanOrEqual */: {
return ByteString("BinaryOperator::LessThanOrEqual"sv);
break;}
case 7 /* GreaterThan */: {
return ByteString("BinaryOperator::GreaterThan"sv);
break;}
case 8 /* GreaterThanOrEqual */: {
return ByteString("BinaryOperator::GreaterThanOrEqual"sv);
break;}
case 9 /* Equal */: {
return ByteString("BinaryOperator::Equal"sv);
break;}
case 10 /* NotEqual */: {
return ByteString("BinaryOperator::NotEqual"sv);
break;}
case 11 /* BitwiseAnd */: {
return ByteString("BinaryOperator::BitwiseAnd"sv);
break;}
case 12 /* BitwiseXor */: {
return ByteString("BinaryOperator::BitwiseXor"sv);
break;}
case 13 /* BitwiseOr */: {
return ByteString("BinaryOperator::BitwiseOr"sv);
break;}
case 14 /* BitwiseLeftShift */: {
return ByteString("BinaryOperator::BitwiseLeftShift"sv);
break;}
case 15 /* BitwiseRightShift */: {
return ByteString("BinaryOperator::BitwiseRightShift"sv);
break;}
case 16 /* ArithmeticLeftShift */: {
return ByteString("BinaryOperator::ArithmeticLeftShift"sv);
break;}
case 17 /* ArithmeticRightShift */: {
return ByteString("BinaryOperator::ArithmeticRightShift"sv);
break;}
case 18 /* LogicalAnd */: {
return ByteString("BinaryOperator::LogicalAnd"sv);
break;}
case 19 /* LogicalOr */: {
return ByteString("BinaryOperator::LogicalOr"sv);
break;}
case 20 /* NoneCoalescing */: {
return ByteString("BinaryOperator::NoneCoalescing"sv);
break;}
case 21 /* Assign */: {
return ByteString("BinaryOperator::Assign"sv);
break;}
case 22 /* BitwiseAndAssign */: {
return ByteString("BinaryOperator::BitwiseAndAssign"sv);
break;}
case 23 /* BitwiseOrAssign */: {
return ByteString("BinaryOperator::BitwiseOrAssign"sv);
break;}
case 24 /* BitwiseXorAssign */: {
return ByteString("BinaryOperator::BitwiseXorAssign"sv);
break;}
case 25 /* BitwiseLeftShiftAssign */: {
return ByteString("BinaryOperator::BitwiseLeftShiftAssign"sv);
break;}
case 26 /* BitwiseRightShiftAssign */: {
return ByteString("BinaryOperator::BitwiseRightShiftAssign"sv);
break;}
case 27 /* AddAssign */: {
return ByteString("BinaryOperator::AddAssign"sv);
break;}
case 28 /* SubtractAssign */: {
return ByteString("BinaryOperator::SubtractAssign"sv);
break;}
case 29 /* MultiplyAssign */: {
return ByteString("BinaryOperator::MultiplyAssign"sv);
break;}
case 30 /* ModuloAssign */: {
return ByteString("BinaryOperator::ModuloAssign"sv);
break;}
case 31 /* DivideAssign */: {
return ByteString("BinaryOperator::DivideAssign"sv);
break;}
case 32 /* NoneCoalescingAssign */: {
return ByteString("BinaryOperator::NoneCoalescingAssign"sv);
break;}
case 33 /* Garbage */: {
return ByteString("BinaryOperator::Garbage"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] BinaryOperator BinaryOperator::Add(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::Subtract(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::Multiply(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::Divide(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::Modulo(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::LessThan(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::LessThanOrEqual(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::GreaterThan(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::GreaterThanOrEqual(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::Equal(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::NotEqual(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseAnd(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseXor(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseOr(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 14;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseLeftShift(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 15;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseRightShift(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 16;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::ArithmeticLeftShift(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 17;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::ArithmeticRightShift(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 18;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::LogicalAnd(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 19;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::LogicalOr(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 20;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::NoneCoalescing(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 21;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::Assign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 22;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseAndAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 23;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseOrAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 24;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseXorAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 25;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseLeftShiftAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 26;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::BitwiseRightShiftAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 27;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::AddAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 28;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::SubtractAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 29;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::MultiplyAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 30;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::ModuloAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 31;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::DivideAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 32;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::NoneCoalescingAssign(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 33;
return __jakt_uninit_enum;
}
[[nodiscard]] BinaryOperator BinaryOperator::Garbage(){
BinaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 34;
return __jakt_uninit_enum;
}
BinaryOperator& BinaryOperator::operator=(BinaryOperator const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Add */:
break;
case 1 /* Subtract */:
break;
case 2 /* Multiply */:
break;
case 3 /* Divide */:
break;
case 4 /* Modulo */:
break;
case 5 /* LessThan */:
break;
case 6 /* LessThanOrEqual */:
break;
case 7 /* GreaterThan */:
break;
case 8 /* GreaterThanOrEqual */:
break;
case 9 /* Equal */:
break;
case 10 /* NotEqual */:
break;
case 11 /* BitwiseAnd */:
break;
case 12 /* BitwiseXor */:
break;
case 13 /* BitwiseOr */:
break;
case 14 /* BitwiseLeftShift */:
break;
case 15 /* BitwiseRightShift */:
break;
case 16 /* ArithmeticLeftShift */:
break;
case 17 /* ArithmeticRightShift */:
break;
case 18 /* LogicalAnd */:
break;
case 19 /* LogicalOr */:
break;
case 20 /* NoneCoalescing */:
break;
case 21 /* Assign */:
break;
case 22 /* BitwiseAndAssign */:
break;
case 23 /* BitwiseOrAssign */:
break;
case 24 /* BitwiseXorAssign */:
break;
case 25 /* BitwiseLeftShiftAssign */:
break;
case 26 /* BitwiseRightShiftAssign */:
break;
case 27 /* AddAssign */:
break;
case 28 /* SubtractAssign */:
break;
case 29 /* MultiplyAssign */:
break;
case 30 /* ModuloAssign */:
break;
case 31 /* DivideAssign */:
break;
case 32 /* NoneCoalescingAssign */:
break;
case 33 /* Garbage */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Add */:
break;
case 1 /* Subtract */:
break;
case 2 /* Multiply */:
break;
case 3 /* Divide */:
break;
case 4 /* Modulo */:
break;
case 5 /* LessThan */:
break;
case 6 /* LessThanOrEqual */:
break;
case 7 /* GreaterThan */:
break;
case 8 /* GreaterThanOrEqual */:
break;
case 9 /* Equal */:
break;
case 10 /* NotEqual */:
break;
case 11 /* BitwiseAnd */:
break;
case 12 /* BitwiseXor */:
break;
case 13 /* BitwiseOr */:
break;
case 14 /* BitwiseLeftShift */:
break;
case 15 /* BitwiseRightShift */:
break;
case 16 /* ArithmeticLeftShift */:
break;
case 17 /* ArithmeticRightShift */:
break;
case 18 /* LogicalAnd */:
break;
case 19 /* LogicalOr */:
break;
case 20 /* NoneCoalescing */:
break;
case 21 /* Assign */:
break;
case 22 /* BitwiseAndAssign */:
break;
case 23 /* BitwiseOrAssign */:
break;
case 24 /* BitwiseXorAssign */:
break;
case 25 /* BitwiseLeftShiftAssign */:
break;
case 26 /* BitwiseRightShiftAssign */:
break;
case 27 /* AddAssign */:
break;
case 28 /* SubtractAssign */:
break;
case 29 /* MultiplyAssign */:
break;
case 30 /* ModuloAssign */:
break;
case 31 /* DivideAssign */:
break;
case 32 /* NoneCoalescingAssign */:
break;
case 33 /* Garbage */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BinaryOperator::BinaryOperator(BinaryOperator const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Add */:
break;
case 1 /* Subtract */:
break;
case 2 /* Multiply */:
break;
case 3 /* Divide */:
break;
case 4 /* Modulo */:
break;
case 5 /* LessThan */:
break;
case 6 /* LessThanOrEqual */:
break;
case 7 /* GreaterThan */:
break;
case 8 /* GreaterThanOrEqual */:
break;
case 9 /* Equal */:
break;
case 10 /* NotEqual */:
break;
case 11 /* BitwiseAnd */:
break;
case 12 /* BitwiseXor */:
break;
case 13 /* BitwiseOr */:
break;
case 14 /* BitwiseLeftShift */:
break;
case 15 /* BitwiseRightShift */:
break;
case 16 /* ArithmeticLeftShift */:
break;
case 17 /* ArithmeticRightShift */:
break;
case 18 /* LogicalAnd */:
break;
case 19 /* LogicalOr */:
break;
case 20 /* NoneCoalescing */:
break;
case 21 /* Assign */:
break;
case 22 /* BitwiseAndAssign */:
break;
case 23 /* BitwiseOrAssign */:
break;
case 24 /* BitwiseXorAssign */:
break;
case 25 /* BitwiseLeftShiftAssign */:
break;
case 26 /* BitwiseRightShiftAssign */:
break;
case 27 /* AddAssign */:
break;
case 28 /* SubtractAssign */:
break;
case 29 /* MultiplyAssign */:
break;
case 30 /* ModuloAssign */:
break;
case 31 /* DivideAssign */:
break;
case 32 /* NoneCoalescingAssign */:
break;
case 33 /* Garbage */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
BinaryOperator& BinaryOperator::operator=(BinaryOperator &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Add */:
break;
case 1 /* Subtract */:
break;
case 2 /* Multiply */:
break;
case 3 /* Divide */:
break;
case 4 /* Modulo */:
break;
case 5 /* LessThan */:
break;
case 6 /* LessThanOrEqual */:
break;
case 7 /* GreaterThan */:
break;
case 8 /* GreaterThanOrEqual */:
break;
case 9 /* Equal */:
break;
case 10 /* NotEqual */:
break;
case 11 /* BitwiseAnd */:
break;
case 12 /* BitwiseXor */:
break;
case 13 /* BitwiseOr */:
break;
case 14 /* BitwiseLeftShift */:
break;
case 15 /* BitwiseRightShift */:
break;
case 16 /* ArithmeticLeftShift */:
break;
case 17 /* ArithmeticRightShift */:
break;
case 18 /* LogicalAnd */:
break;
case 19 /* LogicalOr */:
break;
case 20 /* NoneCoalescing */:
break;
case 21 /* Assign */:
break;
case 22 /* BitwiseAndAssign */:
break;
case 23 /* BitwiseOrAssign */:
break;
case 24 /* BitwiseXorAssign */:
break;
case 25 /* BitwiseLeftShiftAssign */:
break;
case 26 /* BitwiseRightShiftAssign */:
break;
case 27 /* AddAssign */:
break;
case 28 /* SubtractAssign */:
break;
case 29 /* MultiplyAssign */:
break;
case 30 /* ModuloAssign */:
break;
case 31 /* DivideAssign */:
break;
case 32 /* NoneCoalescingAssign */:
break;
case 33 /* Garbage */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Add */:
break;
case 1 /* Subtract */:
break;
case 2 /* Multiply */:
break;
case 3 /* Divide */:
break;
case 4 /* Modulo */:
break;
case 5 /* LessThan */:
break;
case 6 /* LessThanOrEqual */:
break;
case 7 /* GreaterThan */:
break;
case 8 /* GreaterThanOrEqual */:
break;
case 9 /* Equal */:
break;
case 10 /* NotEqual */:
break;
case 11 /* BitwiseAnd */:
break;
case 12 /* BitwiseXor */:
break;
case 13 /* BitwiseOr */:
break;
case 14 /* BitwiseLeftShift */:
break;
case 15 /* BitwiseRightShift */:
break;
case 16 /* ArithmeticLeftShift */:
break;
case 17 /* ArithmeticRightShift */:
break;
case 18 /* LogicalAnd */:
break;
case 19 /* LogicalOr */:
break;
case 20 /* NoneCoalescing */:
break;
case 21 /* Assign */:
break;
case 22 /* BitwiseAndAssign */:
break;
case 23 /* BitwiseOrAssign */:
break;
case 24 /* BitwiseXorAssign */:
break;
case 25 /* BitwiseLeftShiftAssign */:
break;
case 26 /* BitwiseRightShiftAssign */:
break;
case 27 /* AddAssign */:
break;
case 28 /* SubtractAssign */:
break;
case 29 /* MultiplyAssign */:
break;
case 30 /* ModuloAssign */:
break;
case 31 /* DivideAssign */:
break;
case 32 /* NoneCoalescingAssign */:
break;
case 33 /* Garbage */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BinaryOperator::BinaryOperator(BinaryOperator &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Add */:
break;
case 1 /* Subtract */:
break;
case 2 /* Multiply */:
break;
case 3 /* Divide */:
break;
case 4 /* Modulo */:
break;
case 5 /* LessThan */:
break;
case 6 /* LessThanOrEqual */:
break;
case 7 /* GreaterThan */:
break;
case 8 /* GreaterThanOrEqual */:
break;
case 9 /* Equal */:
break;
case 10 /* NotEqual */:
break;
case 11 /* BitwiseAnd */:
break;
case 12 /* BitwiseXor */:
break;
case 13 /* BitwiseOr */:
break;
case 14 /* BitwiseLeftShift */:
break;
case 15 /* BitwiseRightShift */:
break;
case 16 /* ArithmeticLeftShift */:
break;
case 17 /* ArithmeticRightShift */:
break;
case 18 /* LogicalAnd */:
break;
case 19 /* LogicalOr */:
break;
case 20 /* NoneCoalescing */:
break;
case 21 /* Assign */:
break;
case 22 /* BitwiseAndAssign */:
break;
case 23 /* BitwiseOrAssign */:
break;
case 24 /* BitwiseXorAssign */:
break;
case 25 /* BitwiseLeftShiftAssign */:
break;
case 26 /* BitwiseRightShiftAssign */:
break;
case 27 /* AddAssign */:
break;
case 28 /* SubtractAssign */:
break;
case 29 /* MultiplyAssign */:
break;
case 30 /* ModuloAssign */:
break;
case 31 /* DivideAssign */:
break;
case 32 /* NoneCoalescingAssign */:
break;
case 33 /* Garbage */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
BinaryOperator::~BinaryOperator(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void BinaryOperator::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Add */:break;
case 1 /* Subtract */:break;
case 2 /* Multiply */:break;
case 3 /* Divide */:break;
case 4 /* Modulo */:break;
case 5 /* LessThan */:break;
case 6 /* LessThanOrEqual */:break;
case 7 /* GreaterThan */:break;
case 8 /* GreaterThanOrEqual */:break;
case 9 /* Equal */:break;
case 10 /* NotEqual */:break;
case 11 /* BitwiseAnd */:break;
case 12 /* BitwiseXor */:break;
case 13 /* BitwiseOr */:break;
case 14 /* BitwiseLeftShift */:break;
case 15 /* BitwiseRightShift */:break;
case 16 /* ArithmeticLeftShift */:break;
case 17 /* ArithmeticRightShift */:break;
case 18 /* LogicalAnd */:break;
case 19 /* LogicalOr */:break;
case 20 /* NoneCoalescing */:break;
case 21 /* Assign */:break;
case 22 /* BitwiseAndAssign */:break;
case 23 /* BitwiseOrAssign */:break;
case 24 /* BitwiseXorAssign */:break;
case 25 /* BitwiseLeftShiftAssign */:break;
case 26 /* BitwiseRightShiftAssign */:break;
case 27 /* AddAssign */:break;
case 28 /* SubtractAssign */:break;
case 29 /* MultiplyAssign */:break;
case 30 /* ModuloAssign */:break;
case 31 /* DivideAssign */:break;
case 32 /* NoneCoalescingAssign */:break;
case 33 /* Garbage */:break;
}
}
bool parser::BinaryOperator::equals(parser::BinaryOperator const rhs_op) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 0 /* Add */));
};/*case end*/
case 1 /* Subtract */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 1 /* Subtract */));
};/*case end*/
case 2 /* Multiply */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 2 /* Multiply */));
};/*case end*/
case 3 /* Divide */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 3 /* Divide */));
};/*case end*/
case 4 /* Modulo */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 4 /* Modulo */));
};/*case end*/
case 5 /* LessThan */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 5 /* LessThan */));
};/*case end*/
case 6 /* LessThanOrEqual */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 6 /* LessThanOrEqual */));
};/*case end*/
case 7 /* GreaterThan */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 7 /* GreaterThan */));
};/*case end*/
case 8 /* GreaterThanOrEqual */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 8 /* GreaterThanOrEqual */));
};/*case end*/
case 9 /* Equal */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 9 /* Equal */));
};/*case end*/
case 10 /* NotEqual */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 10 /* NotEqual */));
};/*case end*/
case 11 /* BitwiseAnd */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 11 /* BitwiseAnd */));
};/*case end*/
case 12 /* BitwiseXor */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 12 /* BitwiseXor */));
};/*case end*/
case 13 /* BitwiseOr */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 13 /* BitwiseOr */));
};/*case end*/
case 14 /* BitwiseLeftShift */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 14 /* BitwiseLeftShift */));
};/*case end*/
case 15 /* BitwiseRightShift */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 15 /* BitwiseRightShift */));
};/*case end*/
case 16 /* ArithmeticLeftShift */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 16 /* ArithmeticLeftShift */));
};/*case end*/
case 17 /* ArithmeticRightShift */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 17 /* ArithmeticRightShift */));
};/*case end*/
case 19 /* LogicalOr */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 19 /* LogicalOr */));
};/*case end*/
case 18 /* LogicalAnd */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 18 /* LogicalAnd */));
};/*case end*/
case 20 /* NoneCoalescing */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 20 /* NoneCoalescing */));
};/*case end*/
case 21 /* Assign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 21 /* Assign */));
};/*case end*/
case 22 /* BitwiseAndAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 22 /* BitwiseAndAssign */));
};/*case end*/
case 23 /* BitwiseOrAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 23 /* BitwiseOrAssign */));
};/*case end*/
case 24 /* BitwiseXorAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 24 /* BitwiseXorAssign */));
};/*case end*/
case 25 /* BitwiseLeftShiftAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 25 /* BitwiseLeftShiftAssign */));
};/*case end*/
case 26 /* BitwiseRightShiftAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 26 /* BitwiseRightShiftAssign */));
};/*case end*/
case 27 /* AddAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 27 /* AddAssign */));
};/*case end*/
case 28 /* SubtractAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 28 /* SubtractAssign */));
};/*case end*/
case 29 /* MultiplyAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 29 /* MultiplyAssign */));
};/*case end*/
case 30 /* ModuloAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 30 /* ModuloAssign */));
};/*case end*/
case 31 /* DivideAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 31 /* DivideAssign */));
};/*case end*/
case 32 /* NoneCoalescingAssign */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 32 /* NoneCoalescingAssign */));
};/*case end*/
case 33 /* Garbage */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 33 /* Garbage */));
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

bool parser::BinaryOperator::is_assignment() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* Assign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 22 /* BitwiseAndAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 23 /* BitwiseOrAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 24 /* BitwiseXorAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 25 /* BitwiseLeftShiftAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 26 /* BitwiseRightShiftAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 27 /* AddAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 28 /* SubtractAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 29 /* MultiplyAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 30 /* ModuloAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 31 /* DivideAssign */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 32 /* NoneCoalescingAssign */: {
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

ByteString parser::TypeCast::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Fallible */: {
builder.append("TypeCast::Fallible"sv);
[[maybe_unused]] auto const& that = this->as.Fallible;
builder.appendff("({})", that.value);
break;}
case 1 /* Infallible */: {
builder.append("TypeCast::Infallible"sv);
[[maybe_unused]] auto const& that = this->as.Infallible;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] TypeCast TypeCast::Fallible(NonnullRefPtr<typename parser::ParsedType> value){
TypeCast __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Fallible.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] TypeCast TypeCast::Infallible(NonnullRefPtr<typename parser::ParsedType> value){
TypeCast __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Infallible.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
TypeCast& TypeCast::operator=(TypeCast const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
new (&this->as.Fallible.value) (decltype(this->as.Fallible.value))(rhs.as.Fallible.value);
break;
case 1 /* Infallible */:
new (&this->as.Infallible.value) (decltype(this->as.Infallible.value))(rhs.as.Infallible.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
this->as.Fallible.value = rhs.as.Fallible.value;
break;
case 1 /* Infallible */:
this->as.Infallible.value = rhs.as.Infallible.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
TypeCast::TypeCast(TypeCast const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
new (&this->as.Fallible.value) (decltype(this->as.Fallible.value))(rhs.as.Fallible.value);
break;
case 1 /* Infallible */:
new (&this->as.Infallible.value) (decltype(this->as.Infallible.value))(rhs.as.Infallible.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
TypeCast& TypeCast::operator=(TypeCast &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
new (&this->as.Fallible.value) (decltype(this->as.Fallible.value))(move(rhs.as.Fallible.value));
break;
case 1 /* Infallible */:
new (&this->as.Infallible.value) (decltype(this->as.Infallible.value))(move(rhs.as.Infallible.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
this->as.Fallible.value = move(rhs.as.Fallible.value);
break;
case 1 /* Infallible */:
this->as.Infallible.value = move(rhs.as.Infallible.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
TypeCast::TypeCast(TypeCast &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
new (&this->as.Fallible.value) (decltype(this->as.Fallible.value))(move(rhs.as.Fallible.value));
break;
case 1 /* Infallible */:
new (&this->as.Infallible.value) (decltype(this->as.Infallible.value))(move(rhs.as.Infallible.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
TypeCast::~TypeCast(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void TypeCast::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Fallible */:this->as.Fallible.value.~NonnullRefPtr();
break;
case 1 /* Infallible */:this->as.Infallible.value.~NonnullRefPtr();
break;
}
}
NonnullRefPtr<typename parser::ParsedType> parser::TypeCast::parsed_type() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename parser::ParsedType>, NonnullRefPtr<typename parser::ParsedType>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Fallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fallible;NonnullRefPtr<typename parser::ParsedType> const& parsed_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(parsed_type);
};/*case end*/
case 1 /* Infallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Infallible;NonnullRefPtr<typename parser::ParsedType> const& parsed_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(parsed_type);
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

ByteString parser::UnaryOperator::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* PreIncrement */: {
return ByteString("UnaryOperator::PreIncrement"sv);
break;}
case 1 /* PostIncrement */: {
return ByteString("UnaryOperator::PostIncrement"sv);
break;}
case 2 /* PreDecrement */: {
return ByteString("UnaryOperator::PreDecrement"sv);
break;}
case 3 /* PostDecrement */: {
return ByteString("UnaryOperator::PostDecrement"sv);
break;}
case 4 /* Negate */: {
return ByteString("UnaryOperator::Negate"sv);
break;}
case 5 /* Dereference */: {
return ByteString("UnaryOperator::Dereference"sv);
break;}
case 6 /* RawAddress */: {
return ByteString("UnaryOperator::RawAddress"sv);
break;}
case 7 /* Reference */: {
return ByteString("UnaryOperator::Reference"sv);
break;}
case 8 /* MutableReference */: {
return ByteString("UnaryOperator::MutableReference"sv);
break;}
case 9 /* LogicalNot */: {
return ByteString("UnaryOperator::LogicalNot"sv);
break;}
case 10 /* BitwiseNot */: {
return ByteString("UnaryOperator::BitwiseNot"sv);
break;}
case 11 /* TypeCast */: {
builder.append("UnaryOperator::TypeCast"sv);
[[maybe_unused]] auto const& that = this->as.TypeCast;
builder.appendff("({})", that.value);
break;}
case 12 /* Is */: {
builder.append("UnaryOperator::Is"sv);
[[maybe_unused]] auto const& that = this->as.Is;
builder.appendff("({})", that.value);
break;}
case 13 /* IsEnumVariant */: {
builder.append("UnaryOperator::IsEnumVariant"sv);
[[maybe_unused]] auto const& that = this->as.IsEnumVariant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner: {}, ", that.inner);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("bindings: {}", that.bindings);
}
builder.append(")"sv);
break;}
case 14 /* Sizeof */: {
builder.append("UnaryOperator::Sizeof"sv);
[[maybe_unused]] auto const& that = this->as.Sizeof;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] UnaryOperator UnaryOperator::PreIncrement(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::PostIncrement(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::PreDecrement(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::PostDecrement(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::Negate(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::Dereference(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::RawAddress(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::Reference(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::MutableReference(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::LogicalNot(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::BitwiseNot(){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::TypeCast(parser::TypeCast value){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
new (&__jakt_uninit_enum.as.TypeCast.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::Is(NonnullRefPtr<typename parser::ParsedType> value){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
new (&__jakt_uninit_enum.as.Is.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::IsEnumVariant(NonnullRefPtr<typename parser::ParsedType> inner, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> bindings){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 14;
new (&__jakt_uninit_enum.as.IsEnumVariant.inner) (decltype(inner))(move(inner));
new (&__jakt_uninit_enum.as.IsEnumVariant.bindings) (decltype(bindings))(move(bindings));
return __jakt_uninit_enum;
}
[[nodiscard]] UnaryOperator UnaryOperator::Sizeof(NonnullRefPtr<typename parser::ParsedType> value){
UnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 15;
new (&__jakt_uninit_enum.as.Sizeof.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
UnaryOperator& UnaryOperator::operator=(UnaryOperator const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
new (&this->as.TypeCast.value) (decltype(this->as.TypeCast.value))(rhs.as.TypeCast.value);
break;
case 12 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(rhs.as.Is.value);
break;
case 13 /* IsEnumVariant */:
new (&this->as.IsEnumVariant.inner) (decltype(this->as.IsEnumVariant.inner))(rhs.as.IsEnumVariant.inner);
new (&this->as.IsEnumVariant.bindings) (decltype(this->as.IsEnumVariant.bindings))(rhs.as.IsEnumVariant.bindings);
break;
case 14 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(rhs.as.Sizeof.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
this->as.TypeCast.value = rhs.as.TypeCast.value;
break;
case 12 /* Is */:
this->as.Is.value = rhs.as.Is.value;
break;
case 13 /* IsEnumVariant */:
this->as.IsEnumVariant.inner = rhs.as.IsEnumVariant.inner;
this->as.IsEnumVariant.bindings = rhs.as.IsEnumVariant.bindings;
break;
case 14 /* Sizeof */:
this->as.Sizeof.value = rhs.as.Sizeof.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
UnaryOperator::UnaryOperator(UnaryOperator const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
new (&this->as.TypeCast.value) (decltype(this->as.TypeCast.value))(rhs.as.TypeCast.value);
break;
case 12 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(rhs.as.Is.value);
break;
case 13 /* IsEnumVariant */:
new (&this->as.IsEnumVariant.inner) (decltype(this->as.IsEnumVariant.inner))(rhs.as.IsEnumVariant.inner);
new (&this->as.IsEnumVariant.bindings) (decltype(this->as.IsEnumVariant.bindings))(rhs.as.IsEnumVariant.bindings);
break;
case 14 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(rhs.as.Sizeof.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
UnaryOperator& UnaryOperator::operator=(UnaryOperator &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
new (&this->as.TypeCast.value) (decltype(this->as.TypeCast.value))(move(rhs.as.TypeCast.value));
break;
case 12 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(move(rhs.as.Is.value));
break;
case 13 /* IsEnumVariant */:
new (&this->as.IsEnumVariant.inner) (decltype(this->as.IsEnumVariant.inner))(move(rhs.as.IsEnumVariant.inner));
new (&this->as.IsEnumVariant.bindings) (decltype(this->as.IsEnumVariant.bindings))(move(rhs.as.IsEnumVariant.bindings));
break;
case 14 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(move(rhs.as.Sizeof.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
this->as.TypeCast.value = move(rhs.as.TypeCast.value);
break;
case 12 /* Is */:
this->as.Is.value = move(rhs.as.Is.value);
break;
case 13 /* IsEnumVariant */:
this->as.IsEnumVariant.inner = move(rhs.as.IsEnumVariant.inner);
this->as.IsEnumVariant.bindings = move(rhs.as.IsEnumVariant.bindings);
break;
case 14 /* Sizeof */:
this->as.Sizeof.value = move(rhs.as.Sizeof.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
UnaryOperator::UnaryOperator(UnaryOperator &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
new (&this->as.TypeCast.value) (decltype(this->as.TypeCast.value))(move(rhs.as.TypeCast.value));
break;
case 12 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(move(rhs.as.Is.value));
break;
case 13 /* IsEnumVariant */:
new (&this->as.IsEnumVariant.inner) (decltype(this->as.IsEnumVariant.inner))(move(rhs.as.IsEnumVariant.inner));
new (&this->as.IsEnumVariant.bindings) (decltype(this->as.IsEnumVariant.bindings))(move(rhs.as.IsEnumVariant.bindings));
break;
case 14 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(move(rhs.as.Sizeof.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
UnaryOperator::~UnaryOperator(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void UnaryOperator::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* PreIncrement */:break;
case 1 /* PostIncrement */:break;
case 2 /* PreDecrement */:break;
case 3 /* PostDecrement */:break;
case 4 /* Negate */:break;
case 5 /* Dereference */:break;
case 6 /* RawAddress */:break;
case 7 /* Reference */:break;
case 8 /* MutableReference */:break;
case 9 /* LogicalNot */:break;
case 10 /* BitwiseNot */:break;
case 11 /* TypeCast */:this->as.TypeCast.value.~TypeCast();
break;
case 12 /* Is */:this->as.Is.value.~NonnullRefPtr();
break;
case 13 /* IsEnumVariant */:this->as.IsEnumVariant.inner.~NonnullRefPtr();
this->as.IsEnumVariant.bindings.~DynamicArray();
break;
case 14 /* Sizeof */:this->as.Sizeof.value.~NonnullRefPtr();
break;
}
}
bool parser::UnaryOperator::equals(parser::UnaryOperator const rhs_op) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* PreIncrement */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 0 /* PreIncrement */));
};/*case end*/
case 1 /* PostIncrement */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 1 /* PostIncrement */));
};/*case end*/
case 2 /* PreDecrement */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 2 /* PreDecrement */));
};/*case end*/
case 3 /* PostDecrement */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 3 /* PostDecrement */));
};/*case end*/
case 4 /* Negate */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 4 /* Negate */));
};/*case end*/
case 5 /* Dereference */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 5 /* Dereference */));
};/*case end*/
case 6 /* RawAddress */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 6 /* RawAddress */));
};/*case end*/
case 7 /* Reference */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 7 /* Reference */));
};/*case end*/
case 8 /* MutableReference */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 8 /* MutableReference */));
};/*case end*/
case 9 /* LogicalNot */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 9 /* LogicalNot */));
};/*case end*/
case 10 /* BitwiseNot */: {
return JaktInternal::ExplicitValue(((rhs_op).__jakt_init_index() == 10 /* BitwiseNot */));
};/*case end*/
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;parser::TypeCast const& lhs_type_cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = rhs_op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;parser::TypeCast const& rhs_type_cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((lhs_type_cast).parsed_type()))->equals(((rhs_type_cast).parsed_type()))));
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
}));
};/*case end*/
case 12 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;NonnullRefPtr<typename parser::ParsedType> const& lhs_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = rhs_op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;NonnullRefPtr<typename parser::ParsedType> const& rhs_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((lhs_type)->equals(rhs_type)));
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
}));
};/*case end*/
case 14 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;NonnullRefPtr<typename parser::ParsedType> const& lhs_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = rhs_op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;NonnullRefPtr<typename parser::ParsedType> const& rhs_type = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((lhs_type)->equals(rhs_type)));
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
}));
};/*case end*/
case 13 /* IsEnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IsEnumVariant;NonnullRefPtr<typename parser::ParsedType> const& lhs_inner_type = __jakt_match_value.inner;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& lhs_bindings = __jakt_match_value.bindings;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = rhs_op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* IsEnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IsEnumVariant;NonnullRefPtr<typename parser::ParsedType> const& rhs_inner_type = __jakt_match_value.inner;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& rhs_bindings = __jakt_match_value.bindings;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_115; {
bool equal = false;
if ((((lhs_inner_type)->equals(rhs_inner_type)) && ((((lhs_bindings).size())) == (((rhs_bindings).size()))))){
bool bindings_equal = true;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((lhs_bindings).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((lhs_bindings)[i])).equals(((rhs_bindings)[i])))))){
(bindings_equal = false);
break;
}
}

}
}

if (bindings_equal){
(equal = true);
}
}
__jakt_var_115 = equal; goto __jakt_label_109;

}
__jakt_label_109:; __jakt_var_115.release_value(); }));
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
}));
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

ByteString parser::ParsedMatchPattern::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* EnumVariant */: {
builder.append("ParsedMatchPattern::EnumVariant"sv);
[[maybe_unused]] auto const& that = this->as.EnumVariant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variant_names: {}, ", that.variant_names);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variant_arguments: {}, ", that.variant_arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arguments_span: {}", that.arguments_span);
}
builder.append(")"sv);
break;}
case 1 /* Expression */: {
builder.append("ParsedMatchPattern::Expression"sv);
[[maybe_unused]] auto const& that = this->as.Expression;
builder.appendff("({})", that.value);
break;}
case 2 /* CatchAll */: {
builder.append("ParsedMatchPattern::CatchAll"sv);
[[maybe_unused]] auto const& that = this->as.CatchAll;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variant_arguments: {}, ", that.variant_arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arguments_span: {}", that.arguments_span);
}
builder.append(")"sv);
break;}
case 3 /* Invalid */: {
return ByteString("ParsedMatchPattern::Invalid"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] ParsedMatchPattern ParsedMatchPattern::EnumVariant(JaktInternal::Dictionary<ByteString,parser::ParsedPatternDefault> defaults, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> variant_names, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments, utility::Span arguments_span){
ParsedMatchPattern __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.EnumVariant.variant_names) (decltype(variant_names))(move(variant_names));
new (&__jakt_uninit_enum.as.EnumVariant.variant_arguments) (decltype(variant_arguments))(move(variant_arguments));
new (&__jakt_uninit_enum.as.EnumVariant.arguments_span) (decltype(arguments_span))(move(arguments_span));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedMatchPattern ParsedMatchPattern::Expression(JaktInternal::Dictionary<ByteString,parser::ParsedPatternDefault> defaults, NonnullRefPtr<typename parser::ParsedExpression> value){
ParsedMatchPattern __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.Expression.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedMatchPattern ParsedMatchPattern::CatchAll(JaktInternal::Dictionary<ByteString,parser::ParsedPatternDefault> defaults, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> variant_arguments, utility::Span arguments_span){
ParsedMatchPattern __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.CatchAll.variant_arguments) (decltype(variant_arguments))(move(variant_arguments));
new (&__jakt_uninit_enum.as.CatchAll.arguments_span) (decltype(arguments_span))(move(arguments_span));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedMatchPattern ParsedMatchPattern::Invalid(JaktInternal::Dictionary<ByteString,parser::ParsedPatternDefault> defaults){
ParsedMatchPattern __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
return __jakt_uninit_enum;
}
ParsedMatchPattern& ParsedMatchPattern::operator=(ParsedMatchPattern const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.defaults = rhs.common.init_common.defaults;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.variant_names) (decltype(this->as.EnumVariant.variant_names))(rhs.as.EnumVariant.variant_names);
new (&this->as.EnumVariant.variant_arguments) (decltype(this->as.EnumVariant.variant_arguments))(rhs.as.EnumVariant.variant_arguments);
new (&this->as.EnumVariant.arguments_span) (decltype(this->as.EnumVariant.arguments_span))(rhs.as.EnumVariant.arguments_span);
break;
case 1 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(rhs.as.Expression.value);
break;
case 2 /* CatchAll */:
new (&this->as.CatchAll.variant_arguments) (decltype(this->as.CatchAll.variant_arguments))(rhs.as.CatchAll.variant_arguments);
new (&this->as.CatchAll.arguments_span) (decltype(this->as.CatchAll.arguments_span))(rhs.as.CatchAll.arguments_span);
break;
case 3 /* Invalid */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
this->as.EnumVariant.variant_names = rhs.as.EnumVariant.variant_names;
this->as.EnumVariant.variant_arguments = rhs.as.EnumVariant.variant_arguments;
this->as.EnumVariant.arguments_span = rhs.as.EnumVariant.arguments_span;
break;
case 1 /* Expression */:
this->as.Expression.value = rhs.as.Expression.value;
break;
case 2 /* CatchAll */:
this->as.CatchAll.variant_arguments = rhs.as.CatchAll.variant_arguments;
this->as.CatchAll.arguments_span = rhs.as.CatchAll.arguments_span;
break;
case 3 /* Invalid */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedMatchPattern::ParsedMatchPattern(ParsedMatchPattern const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.defaults) (decltype(this->common.init_common.defaults))(rhs.common.init_common.defaults);
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.variant_names) (decltype(this->as.EnumVariant.variant_names))(rhs.as.EnumVariant.variant_names);
new (&this->as.EnumVariant.variant_arguments) (decltype(this->as.EnumVariant.variant_arguments))(rhs.as.EnumVariant.variant_arguments);
new (&this->as.EnumVariant.arguments_span) (decltype(this->as.EnumVariant.arguments_span))(rhs.as.EnumVariant.arguments_span);
break;
case 1 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(rhs.as.Expression.value);
break;
case 2 /* CatchAll */:
new (&this->as.CatchAll.variant_arguments) (decltype(this->as.CatchAll.variant_arguments))(rhs.as.CatchAll.variant_arguments);
new (&this->as.CatchAll.arguments_span) (decltype(this->as.CatchAll.arguments_span))(rhs.as.CatchAll.arguments_span);
break;
case 3 /* Invalid */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ParsedMatchPattern& ParsedMatchPattern::operator=(ParsedMatchPattern &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.defaults = move(rhs.common.init_common.defaults);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.variant_names) (decltype(this->as.EnumVariant.variant_names))(move(rhs.as.EnumVariant.variant_names));
new (&this->as.EnumVariant.variant_arguments) (decltype(this->as.EnumVariant.variant_arguments))(move(rhs.as.EnumVariant.variant_arguments));
new (&this->as.EnumVariant.arguments_span) (decltype(this->as.EnumVariant.arguments_span))(move(rhs.as.EnumVariant.arguments_span));
break;
case 1 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(move(rhs.as.Expression.value));
break;
case 2 /* CatchAll */:
new (&this->as.CatchAll.variant_arguments) (decltype(this->as.CatchAll.variant_arguments))(move(rhs.as.CatchAll.variant_arguments));
new (&this->as.CatchAll.arguments_span) (decltype(this->as.CatchAll.arguments_span))(move(rhs.as.CatchAll.arguments_span));
break;
case 3 /* Invalid */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
this->as.EnumVariant.variant_names = move(rhs.as.EnumVariant.variant_names);
this->as.EnumVariant.variant_arguments = move(rhs.as.EnumVariant.variant_arguments);
this->as.EnumVariant.arguments_span = move(rhs.as.EnumVariant.arguments_span);
break;
case 1 /* Expression */:
this->as.Expression.value = move(rhs.as.Expression.value);
break;
case 2 /* CatchAll */:
this->as.CatchAll.variant_arguments = move(rhs.as.CatchAll.variant_arguments);
this->as.CatchAll.arguments_span = move(rhs.as.CatchAll.arguments_span);
break;
case 3 /* Invalid */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedMatchPattern::ParsedMatchPattern(ParsedMatchPattern &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.defaults) (decltype(this->common.init_common.defaults))(move(rhs.common.init_common.defaults));
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.variant_names) (decltype(this->as.EnumVariant.variant_names))(move(rhs.as.EnumVariant.variant_names));
new (&this->as.EnumVariant.variant_arguments) (decltype(this->as.EnumVariant.variant_arguments))(move(rhs.as.EnumVariant.variant_arguments));
new (&this->as.EnumVariant.arguments_span) (decltype(this->as.EnumVariant.arguments_span))(move(rhs.as.EnumVariant.arguments_span));
break;
case 1 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(move(rhs.as.Expression.value));
break;
case 2 /* CatchAll */:
new (&this->as.CatchAll.variant_arguments) (decltype(this->as.CatchAll.variant_arguments))(move(rhs.as.CatchAll.variant_arguments));
new (&this->as.CatchAll.arguments_span) (decltype(this->as.CatchAll.arguments_span))(move(rhs.as.CatchAll.arguments_span));
break;
case 3 /* Invalid */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ParsedMatchPattern::~ParsedMatchPattern(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.defaults.~Dictionary();
this->__jakt_destroy_variant(); }
void ParsedMatchPattern::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* EnumVariant */:this->as.EnumVariant.variant_names.~DynamicArray();
this->as.EnumVariant.variant_arguments.~DynamicArray();
this->as.EnumVariant.arguments_span.~Span();
break;
case 1 /* Expression */:this->as.Expression.value.~NonnullRefPtr();
break;
case 2 /* CatchAll */:this->as.CatchAll.variant_arguments.~DynamicArray();
this->as.CatchAll.arguments_span.~Span();
break;
case 3 /* Invalid */:break;
}
}
bool parser::ParsedMatchPattern::defaults_equal(JaktInternal::Dictionary<ByteString,parser::ParsedPatternDefault> const defaults) const {
{
if (((((defaults).size())) != (((((*this).common.init_common.defaults)).size())))){
return false;
}
{
JaktInternal::DictionaryIterator<ByteString,parser::ParsedPatternDefault> _magic = ((((*this).common.init_common.defaults)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,parser::ParsedPatternDefault>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,parser::ParsedPatternDefault> name__default___ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,parser::ParsedPatternDefault> const jakt__name__default___ = name__default___;
ByteString const name = ((jakt__name__default___).template get<0>());
parser::ParsedPatternDefault const default_ = ((jakt__name__default___).template get<1>());

JaktInternal::Optional<parser::ParsedPatternDefault> const matching = ((defaults).get(name));
if ((!(((matching).has_value())))){
return false;
}
if ((!((((((matching.value())).value))->equals(((default_).value)))))){
return false;
}
if ((((((((matching.value())).variable)).is_mutable)) != (((((default_).variable)).is_mutable)))){
return false;
}
}

}
}

return true;
}
}

bool parser::ParsedMatchPattern::is_equal_pattern(parser::ParsedMatchPattern const rhs_parsed_match_pattern) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> const& lhs_variant_names = __jakt_match_value.variant_names;
{
if (((rhs_parsed_match_pattern).__jakt_init_index() == 0 /* EnumVariant */)){
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,utility::Span>> const rhs_variant_names = (rhs_parsed_match_pattern).as.EnumVariant.variant_names;
size_t namespace_count = ((lhs_variant_names).size());
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((rhs_variant_names).size()),namespace_count)){
(namespace_count = ((rhs_variant_names).size()));
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(namespace_count)});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
ByteString const lhs_name = ((((lhs_variant_names)[JaktInternal::checked_sub(JaktInternal::checked_sub(((lhs_variant_names).size()),i),static_cast<size_t>(1ULL))])).template get<0>());
ByteString const rhs_name = ((((rhs_variant_names)[JaktInternal::checked_sub(JaktInternal::checked_sub(((rhs_variant_names).size()),i),static_cast<size_t>(1ULL))])).template get<0>());
if (((lhs_name) == (rhs_name))){
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
};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_parsed_expression = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = rhs_parsed_match_pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_parsed_expression = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((lhs_parsed_expression)->equals(rhs_parsed_expression)));
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
}));
};/*case end*/
case 2 /* CatchAll */: {
return JaktInternal::ExplicitValue(((rhs_parsed_match_pattern).__jakt_init_index() == 2 /* CatchAll */));
};/*case end*/
case 3 /* Invalid */: {
return JaktInternal::ExplicitValue(((rhs_parsed_match_pattern).__jakt_init_index() == 3 /* Invalid */));
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

bool parser::ParsedMatchPattern::equals(parser::ParsedMatchPattern const rhs_parsed_match_pattern) const {
{
if (((*this).is_equal_pattern(rhs_parsed_match_pattern))){
if (((*this).defaults_equal(((rhs_parsed_match_pattern).common.init_common.defaults)))){
if (((*this).__jakt_init_index() == 0 /* EnumVariant */)){
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const lhs_variant_arguments = (*this).as.EnumVariant.variant_arguments;
if (((rhs_parsed_match_pattern).__jakt_init_index() == 0 /* EnumVariant */)){
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const rhs_variant_arguments = (rhs_parsed_match_pattern).as.EnumVariant.variant_arguments;
if (((((lhs_variant_arguments).size())) == (((rhs_variant_arguments).size())))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((lhs_variant_arguments).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((lhs_variant_arguments)[i])).equals(((rhs_variant_arguments)[i])))))){
return false;
}
}

}
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
}

ByteString parser::ParsedMatchBody::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Expression */: {
builder.append("ParsedMatchBody::Expression"sv);
[[maybe_unused]] auto const& that = this->as.Expression;
builder.appendff("({})", that.value);
break;}
case 1 /* Block */: {
builder.append("ParsedMatchBody::Block"sv);
[[maybe_unused]] auto const& that = this->as.Block;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] ParsedMatchBody ParsedMatchBody::Expression(NonnullRefPtr<typename parser::ParsedExpression> value){
ParsedMatchBody __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Expression.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedMatchBody ParsedMatchBody::Block(parser::ParsedBlock value){
ParsedMatchBody __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Block.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
ParsedMatchBody& ParsedMatchBody::operator=(ParsedMatchBody const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(rhs.as.Expression.value);
break;
case 1 /* Block */:
new (&this->as.Block.value) (decltype(this->as.Block.value))(rhs.as.Block.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.value = rhs.as.Expression.value;
break;
case 1 /* Block */:
this->as.Block.value = rhs.as.Block.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedMatchBody::ParsedMatchBody(ParsedMatchBody const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(rhs.as.Expression.value);
break;
case 1 /* Block */:
new (&this->as.Block.value) (decltype(this->as.Block.value))(rhs.as.Block.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ParsedMatchBody& ParsedMatchBody::operator=(ParsedMatchBody &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(move(rhs.as.Expression.value));
break;
case 1 /* Block */:
new (&this->as.Block.value) (decltype(this->as.Block.value))(move(rhs.as.Block.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.value = move(rhs.as.Expression.value);
break;
case 1 /* Block */:
this->as.Block.value = move(rhs.as.Block.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedMatchBody::ParsedMatchBody(ParsedMatchBody &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(move(rhs.as.Expression.value));
break;
case 1 /* Block */:
new (&this->as.Block.value) (decltype(this->as.Block.value))(move(rhs.as.Block.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ParsedMatchBody::~ParsedMatchBody(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ParsedMatchBody::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Expression */:this->as.Expression.value.~NonnullRefPtr();
break;
case 1 /* Block */:this->as.Block.value.~ParsedBlock();
break;
}
}
bool parser::ParsedMatchBody::equals(parser::ParsedMatchBody const rhs_match_body) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_116; {
__jakt_var_116 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool,bool> {
auto __jakt_enum_value = (((rhs_match_body).__jakt_init_index() == 0 /* Expression */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_117; {
NonnullRefPtr<typename parser::ParsedExpression> const rhs_expr = (rhs_match_body).as.Expression.value;
__jakt_var_117 = ((lhs_expr)->equals(rhs_expr)); goto __jakt_label_111;

}
__jakt_label_111:; __jakt_var_117.release_value(); }));
}
else {
{
return false;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_110;

}
__jakt_label_110:; __jakt_var_116.release_value(); }));
};/*case end*/
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;parser::ParsedBlock const& lhs_block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_118; {
__jakt_var_118 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool,bool> {
auto __jakt_enum_value = (((rhs_match_body).__jakt_init_index() == 1 /* Block */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_119; {
parser::ParsedBlock const rhs_block = (rhs_match_body).as.Block.value;
__jakt_var_119 = ((lhs_block).equals(rhs_block)); goto __jakt_label_113;

}
__jakt_label_113:; __jakt_var_119.release_value(); }));
}
else {
{
return false;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_112;

}
__jakt_label_112:; __jakt_var_118.release_value(); }));
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

ByteString parser::ParsedCapture::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* ByValue */: {
return ByteString("ParsedCapture::ByValue"sv);
break;}
case 1 /* ByReference */: {
return ByteString("ParsedCapture::ByReference"sv);
break;}
case 2 /* ByMutableReference */: {
return ByteString("ParsedCapture::ByMutableReference"sv);
break;}
case 3 /* ByComptimeDependency */: {
return ByteString("ParsedCapture::ByComptimeDependency"sv);
break;}
case 4 /* AllByReference */: {
return ByteString("ParsedCapture::AllByReference"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] ParsedCapture ParsedCapture::ByValue(ByteString name, utility::Span span){
ParsedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedCapture ParsedCapture::ByReference(ByteString name, utility::Span span){
ParsedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedCapture ParsedCapture::ByMutableReference(ByteString name, utility::Span span){
ParsedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedCapture ParsedCapture::ByComptimeDependency(ByteString name, utility::Span span){
ParsedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] ParsedCapture ParsedCapture::AllByReference(ByteString name, utility::Span span){
ParsedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
ParsedCapture& ParsedCapture::operator=(ParsedCapture const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.name = rhs.common.init_common.name;
this->common.init_common.span = rhs.common.init_common.span;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedCapture::ParsedCapture(ParsedCapture const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.name) (decltype(this->common.init_common.name))(rhs.common.init_common.name);
new (&this->common.init_common.span) (decltype(this->common.init_common.span))(rhs.common.init_common.span);
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ParsedCapture& ParsedCapture::operator=(ParsedCapture &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.name = move(rhs.common.init_common.name);
this->common.init_common.span = move(rhs.common.init_common.span);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedCapture::ParsedCapture(ParsedCapture &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.name) (decltype(this->common.init_common.name))(move(rhs.common.init_common.name));
new (&this->common.init_common.span) (decltype(this->common.init_common.span))(move(rhs.common.init_common.span));
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ParsedCapture::~ParsedCapture(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.name.~ByteString();
this->common.init_common.span.~Span();
this->__jakt_destroy_variant(); }
void ParsedCapture::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* ByValue */:break;
case 1 /* ByReference */:break;
case 2 /* ByMutableReference */:break;
case 3 /* ByComptimeDependency */:break;
case 4 /* AllByReference */:break;
}
}
ByteString parser::ParsedExpression::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Boolean */: {
builder.append("ParsedExpression::Boolean"sv);
[[maybe_unused]] auto const& that = this->as.Boolean;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: {}, ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* NumericConstant */: {
builder.append("ParsedExpression::NumericConstant"sv);
[[maybe_unused]] auto const& that = this->as.NumericConstant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: {}, ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 2 /* QuotedString */: {
builder.append("ParsedExpression::QuotedString"sv);
[[maybe_unused]] auto const& that = this->as.QuotedString;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: \"{}\", ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 3 /* SingleQuotedString */: {
builder.append("ParsedExpression::SingleQuotedString"sv);
[[maybe_unused]] auto const& that = this->as.SingleQuotedString;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: \"{}\", ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("prefix: {}, ", that.prefix);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 4 /* Call */: {
builder.append("ParsedExpression::Call"sv);
[[maybe_unused]] auto const& that = this->as.Call;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("call: {}, ", that.call);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 5 /* MethodCall */: {
builder.append("ParsedExpression::MethodCall"sv);
[[maybe_unused]] auto const& that = this->as.MethodCall;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("call: {}, ", that.call);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 6 /* IndexedTuple */: {
builder.append("ParsedExpression::IndexedTuple"sv);
[[maybe_unused]] auto const& that = this->as.IndexedTuple;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 7 /* IndexedStruct */: {
builder.append("ParsedExpression::IndexedStruct"sv);
[[maybe_unused]] auto const& that = this->as.IndexedStruct;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("field_name: \"{}\", ", that.field_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 8 /* ComptimeIndex */: {
builder.append("ParsedExpression::ComptimeIndex"sv);
[[maybe_unused]] auto const& that = this->as.ComptimeIndex;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 9 /* Var */: {
builder.append("ParsedExpression::Var"sv);
[[maybe_unused]] auto const& that = this->as.Var;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 10 /* IndexedExpression */: {
builder.append("ParsedExpression::IndexedExpression"sv);
[[maybe_unused]] auto const& that = this->as.IndexedExpression;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("base: {}, ", that.base);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 11 /* UnaryOp */: {
builder.append("ParsedExpression::UnaryOp"sv);
[[maybe_unused]] auto const& that = this->as.UnaryOp;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("op: {}, ", that.op);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 12 /* BinaryOp */: {
builder.append("ParsedExpression::BinaryOp"sv);
[[maybe_unused]] auto const& that = this->as.BinaryOp;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("lhs: {}, ", that.lhs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("op: {}, ", that.op);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("rhs: {}, ", that.rhs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 13 /* Operator */: {
builder.append("ParsedExpression::Operator"sv);
[[maybe_unused]] auto const& that = this->as.Operator;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("op: {}, ", that.op);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 14 /* OptionalSome */: {
builder.append("ParsedExpression::OptionalSome"sv);
[[maybe_unused]] auto const& that = this->as.OptionalSome;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 15 /* OptionalNone */: {
builder.append("ParsedExpression::OptionalNone"sv);
[[maybe_unused]] auto const& that = this->as.OptionalNone;
builder.appendff("({})", that.value);
break;}
case 16 /* JaktArray */: {
builder.append("ParsedExpression::JaktArray"sv);
[[maybe_unused]] auto const& that = this->as.JaktArray;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}, ", that.values);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fill_size: {}, ", that.fill_size);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 17 /* JaktDictionary */: {
builder.append("ParsedExpression::JaktDictionary"sv);
[[maybe_unused]] auto const& that = this->as.JaktDictionary;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}, ", that.values);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 18 /* Set */: {
builder.append("ParsedExpression::Set"sv);
[[maybe_unused]] auto const& that = this->as.Set;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}, ", that.values);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 19 /* JaktTuple */: {
builder.append("ParsedExpression::JaktTuple"sv);
[[maybe_unused]] auto const& that = this->as.JaktTuple;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}, ", that.values);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 20 /* Range */: {
builder.append("ParsedExpression::Range"sv);
[[maybe_unused]] auto const& that = this->as.Range;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("from: {}, ", that.from);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("to: {}, ", that.to);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 21 /* ForcedUnwrap */: {
builder.append("ParsedExpression::ForcedUnwrap"sv);
[[maybe_unused]] auto const& that = this->as.ForcedUnwrap;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 22 /* Match */: {
builder.append("ParsedExpression::Match"sv);
[[maybe_unused]] auto const& that = this->as.Match;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("cases: {}, ", that.cases);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
case 23 /* EnumVariantArg */: {
builder.append("ParsedExpression::EnumVariantArg"sv);
[[maybe_unused]] auto const& that = this->as.EnumVariantArg;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arg: {}, ", that.arg);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enum_variant: {}, ", that.enum_variant);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 24 /* NamespacedVar */: {
builder.append("ParsedExpression::NamespacedVar"sv);
[[maybe_unused]] auto const& that = this->as.NamespacedVar;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespace_: {}, ", that.namespace_);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 25 /* Function */: {
builder.append("ParsedExpression::Function"sv);
[[maybe_unused]] auto const& that = this->as.Function;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("captures: {}, ", that.captures);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", that.params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", that.can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_fat_arrow: {}, ", that.is_fat_arrow);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type: {}, ", that.return_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 26 /* Must */: {
builder.append("ParsedExpression::Must"sv);
[[maybe_unused]] auto const& that = this->as.Must;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 27 /* Try */: {
builder.append("ParsedExpression::Try"sv);
[[maybe_unused]] auto const& that = this->as.Try;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("catch_block: {}, ", that.catch_block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("catch_span: {}, ", that.catch_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("catch_name: {}, ", that.catch_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 28 /* TryBlock */: {
builder.append("ParsedExpression::TryBlock"sv);
[[maybe_unused]] auto const& that = this->as.TryBlock;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("stmt: {}, ", that.stmt);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("error_name: \"{}\", ", that.error_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("error_span: {}, ", that.error_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("catch_block: {}, ", that.catch_block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 29 /* Reflect */: {
builder.append("ParsedExpression::Reflect"sv);
[[maybe_unused]] auto const& that = this->as.Reflect;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type: {}, ", that.type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 30 /* Garbage */: {
builder.append("ParsedExpression::Garbage"sv);
[[maybe_unused]] auto const& that = this->as.Garbage;
builder.appendff("({})", that.value);
break;}
case 31 /* Unsafe */: {
builder.append("ParsedExpression::Unsafe"sv);
[[maybe_unused]] auto const& that = this->as.Unsafe;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Boolean(bool val, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->as.Boolean.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.Boolean.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::NumericConstant(parser::NumericConstant val, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->as.NumericConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.NumericConstant.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::QuotedString(ByteString val, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->as.QuotedString.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.QuotedString.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::SingleQuotedString(ByteString val, JaktInternal::Optional<ByteString> prefix, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->as.SingleQuotedString.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.SingleQuotedString.prefix) (decltype(prefix))(move(prefix));
new (&__jakt_uninit_enum->as.SingleQuotedString.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Call(parser::ParsedCall call, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->as.Call.call) (decltype(call))(move(call));
new (&__jakt_uninit_enum->as.Call.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::MethodCall(NonnullRefPtr<typename parser::ParsedExpression> expr, parser::ParsedCall call, bool is_optional, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->as.MethodCall.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.MethodCall.call) (decltype(call))(move(call));
new (&__jakt_uninit_enum->as.MethodCall.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.MethodCall.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::IndexedTuple(NonnullRefPtr<typename parser::ParsedExpression> expr, size_t index, bool is_optional, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->as.IndexedTuple.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedTuple.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedTuple.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.IndexedTuple.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::IndexedStruct(NonnullRefPtr<typename parser::ParsedExpression> expr, ByteString field_name, bool is_optional, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->as.IndexedStruct.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedStruct.field_name) (decltype(field_name))(move(field_name));
new (&__jakt_uninit_enum->as.IndexedStruct.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.IndexedStruct.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::ComptimeIndex(NonnullRefPtr<typename parser::ParsedExpression> expr, NonnullRefPtr<typename parser::ParsedExpression> index, bool is_optional, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->as.ComptimeIndex.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.ComptimeIndex.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.ComptimeIndex.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.ComptimeIndex.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Var(ByteString name, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->as.Var.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.Var.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::IndexedExpression(NonnullRefPtr<typename parser::ParsedExpression> base, NonnullRefPtr<typename parser::ParsedExpression> index, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->as.IndexedExpression.base) (decltype(base))(move(base));
new (&__jakt_uninit_enum->as.IndexedExpression.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedExpression.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::UnaryOp(NonnullRefPtr<typename parser::ParsedExpression> expr, parser::UnaryOperator op, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->as.UnaryOp.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.UnaryOp.op) (decltype(op))(move(op));
new (&__jakt_uninit_enum->as.UnaryOp.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::BinaryOp(NonnullRefPtr<typename parser::ParsedExpression> lhs, parser::BinaryOperator op, NonnullRefPtr<typename parser::ParsedExpression> rhs, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->as.BinaryOp.lhs) (decltype(lhs))(move(lhs));
new (&__jakt_uninit_enum->as.BinaryOp.op) (decltype(op))(move(op));
new (&__jakt_uninit_enum->as.BinaryOp.rhs) (decltype(rhs))(move(rhs));
new (&__jakt_uninit_enum->as.BinaryOp.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Operator(parser::BinaryOperator op, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->as.Operator.op) (decltype(op))(move(op));
new (&__jakt_uninit_enum->as.Operator.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::OptionalSome(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->as.OptionalSome.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.OptionalSome.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::OptionalNone(utility::Span value){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 16;
new (&__jakt_uninit_enum->as.OptionalNone.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::JaktArray(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> fill_size, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 17;
new (&__jakt_uninit_enum->as.JaktArray.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktArray.fill_size) (decltype(fill_size))(move(fill_size));
new (&__jakt_uninit_enum->as.JaktArray.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::JaktDictionary(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> values, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 18;
new (&__jakt_uninit_enum->as.JaktDictionary.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktDictionary.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Set(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 19;
new (&__jakt_uninit_enum->as.Set.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.Set.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::JaktTuple(JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> values, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 20;
new (&__jakt_uninit_enum->as.JaktTuple.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktTuple.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Range(JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> from, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> to, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 21;
new (&__jakt_uninit_enum->as.Range.from) (decltype(from))(move(from));
new (&__jakt_uninit_enum->as.Range.to) (decltype(to))(move(to));
new (&__jakt_uninit_enum->as.Range.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::ForcedUnwrap(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 22;
new (&__jakt_uninit_enum->as.ForcedUnwrap.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.ForcedUnwrap.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Match(NonnullRefPtr<typename parser::ParsedExpression> expr, JaktInternal::DynamicArray<parser::ParsedMatchCase> cases, utility::Span span, utility::Span marker_span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 23;
new (&__jakt_uninit_enum->as.Match.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Match.cases) (decltype(cases))(move(cases));
new (&__jakt_uninit_enum->as.Match.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Match.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::EnumVariantArg(NonnullRefPtr<typename parser::ParsedExpression> expr, parser::EnumVariantPatternArgument arg, NonnullRefPtr<typename parser::ParsedType> enum_variant, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 24;
new (&__jakt_uninit_enum->as.EnumVariantArg.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.EnumVariantArg.arg) (decltype(arg))(move(arg));
new (&__jakt_uninit_enum->as.EnumVariantArg.enum_variant) (decltype(enum_variant))(move(enum_variant));
new (&__jakt_uninit_enum->as.EnumVariantArg.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::NamespacedVar(ByteString name, JaktInternal::DynamicArray<ByteString> namespace_, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 25;
new (&__jakt_uninit_enum->as.NamespacedVar.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.NamespacedVar.namespace_) (decltype(namespace_))(move(namespace_));
new (&__jakt_uninit_enum->as.NamespacedVar.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Function(JaktInternal::DynamicArray<parser::ParsedCapture> captures, JaktInternal::DynamicArray<parser::ParsedParameter> params, bool can_throw, bool is_fat_arrow, NonnullRefPtr<typename parser::ParsedType> return_type, parser::ParsedBlock block, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 26;
new (&__jakt_uninit_enum->as.Function.captures) (decltype(captures))(move(captures));
new (&__jakt_uninit_enum->as.Function.params) (decltype(params))(move(params));
new (&__jakt_uninit_enum->as.Function.can_throw) (decltype(can_throw))(move(can_throw));
new (&__jakt_uninit_enum->as.Function.is_fat_arrow) (decltype(is_fat_arrow))(move(is_fat_arrow));
new (&__jakt_uninit_enum->as.Function.return_type) (decltype(return_type))(move(return_type));
new (&__jakt_uninit_enum->as.Function.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Function.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Must(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 27;
new (&__jakt_uninit_enum->as.Must.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Must.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Try(NonnullRefPtr<typename parser::ParsedExpression> expr, JaktInternal::Optional<parser::ParsedBlock> catch_block, JaktInternal::Optional<utility::Span> catch_span, JaktInternal::Optional<ByteString> catch_name, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 28;
new (&__jakt_uninit_enum->as.Try.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Try.catch_block) (decltype(catch_block))(move(catch_block));
new (&__jakt_uninit_enum->as.Try.catch_span) (decltype(catch_span))(move(catch_span));
new (&__jakt_uninit_enum->as.Try.catch_name) (decltype(catch_name))(move(catch_name));
new (&__jakt_uninit_enum->as.Try.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::TryBlock(NonnullRefPtr<typename parser::ParsedStatement> stmt, ByteString error_name, utility::Span error_span, parser::ParsedBlock catch_block, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 29;
new (&__jakt_uninit_enum->as.TryBlock.stmt) (decltype(stmt))(move(stmt));
new (&__jakt_uninit_enum->as.TryBlock.error_name) (decltype(error_name))(move(error_name));
new (&__jakt_uninit_enum->as.TryBlock.error_span) (decltype(error_span))(move(error_span));
new (&__jakt_uninit_enum->as.TryBlock.catch_block) (decltype(catch_block))(move(catch_block));
new (&__jakt_uninit_enum->as.TryBlock.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Reflect(NonnullRefPtr<typename parser::ParsedType> type, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 30;
new (&__jakt_uninit_enum->as.Reflect.type) (decltype(type))(move(type));
new (&__jakt_uninit_enum->as.Reflect.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Garbage(utility::Span value){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 31;
new (&__jakt_uninit_enum->as.Garbage.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedExpression> ParsedExpression::Unsafe(NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span){
NonnullRefPtr<ParsedExpression> __jakt_uninit_enum = adopt_ref(*new ParsedExpression);
__jakt_uninit_enum->__jakt_variant_index = 32;
new (&__jakt_uninit_enum->as.Unsafe.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Unsafe.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
ParsedExpression& ParsedExpression::operator=(ParsedExpression const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
new (&this->as.Boolean.val) (decltype(this->as.Boolean.val))(rhs.as.Boolean.val);
new (&this->as.Boolean.span) (decltype(this->as.Boolean.span))(rhs.as.Boolean.span);
break;
case 1 /* NumericConstant */:
new (&this->as.NumericConstant.val) (decltype(this->as.NumericConstant.val))(rhs.as.NumericConstant.val);
new (&this->as.NumericConstant.span) (decltype(this->as.NumericConstant.span))(rhs.as.NumericConstant.span);
break;
case 2 /* QuotedString */:
new (&this->as.QuotedString.val) (decltype(this->as.QuotedString.val))(rhs.as.QuotedString.val);
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(rhs.as.QuotedString.span);
break;
case 3 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.val) (decltype(this->as.SingleQuotedString.val))(rhs.as.SingleQuotedString.val);
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(rhs.as.SingleQuotedString.prefix);
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(rhs.as.SingleQuotedString.span);
break;
case 4 /* Call */:
new (&this->as.Call.call) (decltype(this->as.Call.call))(rhs.as.Call.call);
new (&this->as.Call.span) (decltype(this->as.Call.span))(rhs.as.Call.span);
break;
case 5 /* MethodCall */:
new (&this->as.MethodCall.expr) (decltype(this->as.MethodCall.expr))(rhs.as.MethodCall.expr);
new (&this->as.MethodCall.call) (decltype(this->as.MethodCall.call))(rhs.as.MethodCall.call);
new (&this->as.MethodCall.is_optional) (decltype(this->as.MethodCall.is_optional))(rhs.as.MethodCall.is_optional);
new (&this->as.MethodCall.span) (decltype(this->as.MethodCall.span))(rhs.as.MethodCall.span);
break;
case 6 /* IndexedTuple */:
new (&this->as.IndexedTuple.expr) (decltype(this->as.IndexedTuple.expr))(rhs.as.IndexedTuple.expr);
new (&this->as.IndexedTuple.index) (decltype(this->as.IndexedTuple.index))(rhs.as.IndexedTuple.index);
new (&this->as.IndexedTuple.is_optional) (decltype(this->as.IndexedTuple.is_optional))(rhs.as.IndexedTuple.is_optional);
new (&this->as.IndexedTuple.span) (decltype(this->as.IndexedTuple.span))(rhs.as.IndexedTuple.span);
break;
case 7 /* IndexedStruct */:
new (&this->as.IndexedStruct.expr) (decltype(this->as.IndexedStruct.expr))(rhs.as.IndexedStruct.expr);
new (&this->as.IndexedStruct.field_name) (decltype(this->as.IndexedStruct.field_name))(rhs.as.IndexedStruct.field_name);
new (&this->as.IndexedStruct.is_optional) (decltype(this->as.IndexedStruct.is_optional))(rhs.as.IndexedStruct.is_optional);
new (&this->as.IndexedStruct.span) (decltype(this->as.IndexedStruct.span))(rhs.as.IndexedStruct.span);
break;
case 8 /* ComptimeIndex */:
new (&this->as.ComptimeIndex.expr) (decltype(this->as.ComptimeIndex.expr))(rhs.as.ComptimeIndex.expr);
new (&this->as.ComptimeIndex.index) (decltype(this->as.ComptimeIndex.index))(rhs.as.ComptimeIndex.index);
new (&this->as.ComptimeIndex.is_optional) (decltype(this->as.ComptimeIndex.is_optional))(rhs.as.ComptimeIndex.is_optional);
new (&this->as.ComptimeIndex.span) (decltype(this->as.ComptimeIndex.span))(rhs.as.ComptimeIndex.span);
break;
case 9 /* Var */:
new (&this->as.Var.name) (decltype(this->as.Var.name))(rhs.as.Var.name);
new (&this->as.Var.span) (decltype(this->as.Var.span))(rhs.as.Var.span);
break;
case 10 /* IndexedExpression */:
new (&this->as.IndexedExpression.base) (decltype(this->as.IndexedExpression.base))(rhs.as.IndexedExpression.base);
new (&this->as.IndexedExpression.index) (decltype(this->as.IndexedExpression.index))(rhs.as.IndexedExpression.index);
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(rhs.as.IndexedExpression.span);
break;
case 11 /* UnaryOp */:
new (&this->as.UnaryOp.expr) (decltype(this->as.UnaryOp.expr))(rhs.as.UnaryOp.expr);
new (&this->as.UnaryOp.op) (decltype(this->as.UnaryOp.op))(rhs.as.UnaryOp.op);
new (&this->as.UnaryOp.span) (decltype(this->as.UnaryOp.span))(rhs.as.UnaryOp.span);
break;
case 12 /* BinaryOp */:
new (&this->as.BinaryOp.lhs) (decltype(this->as.BinaryOp.lhs))(rhs.as.BinaryOp.lhs);
new (&this->as.BinaryOp.op) (decltype(this->as.BinaryOp.op))(rhs.as.BinaryOp.op);
new (&this->as.BinaryOp.rhs) (decltype(this->as.BinaryOp.rhs))(rhs.as.BinaryOp.rhs);
new (&this->as.BinaryOp.span) (decltype(this->as.BinaryOp.span))(rhs.as.BinaryOp.span);
break;
case 13 /* Operator */:
new (&this->as.Operator.op) (decltype(this->as.Operator.op))(rhs.as.Operator.op);
new (&this->as.Operator.span) (decltype(this->as.Operator.span))(rhs.as.Operator.span);
break;
case 14 /* OptionalSome */:
new (&this->as.OptionalSome.expr) (decltype(this->as.OptionalSome.expr))(rhs.as.OptionalSome.expr);
new (&this->as.OptionalSome.span) (decltype(this->as.OptionalSome.span))(rhs.as.OptionalSome.span);
break;
case 15 /* OptionalNone */:
new (&this->as.OptionalNone.value) (decltype(this->as.OptionalNone.value))(rhs.as.OptionalNone.value);
break;
case 16 /* JaktArray */:
new (&this->as.JaktArray.values) (decltype(this->as.JaktArray.values))(rhs.as.JaktArray.values);
new (&this->as.JaktArray.fill_size) (decltype(this->as.JaktArray.fill_size))(rhs.as.JaktArray.fill_size);
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(rhs.as.JaktArray.span);
break;
case 17 /* JaktDictionary */:
new (&this->as.JaktDictionary.values) (decltype(this->as.JaktDictionary.values))(rhs.as.JaktDictionary.values);
new (&this->as.JaktDictionary.span) (decltype(this->as.JaktDictionary.span))(rhs.as.JaktDictionary.span);
break;
case 18 /* Set */:
new (&this->as.Set.values) (decltype(this->as.Set.values))(rhs.as.Set.values);
new (&this->as.Set.span) (decltype(this->as.Set.span))(rhs.as.Set.span);
break;
case 19 /* JaktTuple */:
new (&this->as.JaktTuple.values) (decltype(this->as.JaktTuple.values))(rhs.as.JaktTuple.values);
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(rhs.as.JaktTuple.span);
break;
case 20 /* Range */:
new (&this->as.Range.from) (decltype(this->as.Range.from))(rhs.as.Range.from);
new (&this->as.Range.to) (decltype(this->as.Range.to))(rhs.as.Range.to);
new (&this->as.Range.span) (decltype(this->as.Range.span))(rhs.as.Range.span);
break;
case 21 /* ForcedUnwrap */:
new (&this->as.ForcedUnwrap.expr) (decltype(this->as.ForcedUnwrap.expr))(rhs.as.ForcedUnwrap.expr);
new (&this->as.ForcedUnwrap.span) (decltype(this->as.ForcedUnwrap.span))(rhs.as.ForcedUnwrap.span);
break;
case 22 /* Match */:
new (&this->as.Match.expr) (decltype(this->as.Match.expr))(rhs.as.Match.expr);
new (&this->as.Match.cases) (decltype(this->as.Match.cases))(rhs.as.Match.cases);
new (&this->as.Match.span) (decltype(this->as.Match.span))(rhs.as.Match.span);
new (&this->as.Match.marker_span) (decltype(this->as.Match.marker_span))(rhs.as.Match.marker_span);
break;
case 23 /* EnumVariantArg */:
new (&this->as.EnumVariantArg.expr) (decltype(this->as.EnumVariantArg.expr))(rhs.as.EnumVariantArg.expr);
new (&this->as.EnumVariantArg.arg) (decltype(this->as.EnumVariantArg.arg))(rhs.as.EnumVariantArg.arg);
new (&this->as.EnumVariantArg.enum_variant) (decltype(this->as.EnumVariantArg.enum_variant))(rhs.as.EnumVariantArg.enum_variant);
new (&this->as.EnumVariantArg.span) (decltype(this->as.EnumVariantArg.span))(rhs.as.EnumVariantArg.span);
break;
case 24 /* NamespacedVar */:
new (&this->as.NamespacedVar.name) (decltype(this->as.NamespacedVar.name))(rhs.as.NamespacedVar.name);
new (&this->as.NamespacedVar.namespace_) (decltype(this->as.NamespacedVar.namespace_))(rhs.as.NamespacedVar.namespace_);
new (&this->as.NamespacedVar.span) (decltype(this->as.NamespacedVar.span))(rhs.as.NamespacedVar.span);
break;
case 25 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(rhs.as.Function.captures);
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.is_fat_arrow) (decltype(this->as.Function.is_fat_arrow))(rhs.as.Function.is_fat_arrow);
new (&this->as.Function.return_type) (decltype(this->as.Function.return_type))(rhs.as.Function.return_type);
new (&this->as.Function.block) (decltype(this->as.Function.block))(rhs.as.Function.block);
new (&this->as.Function.span) (decltype(this->as.Function.span))(rhs.as.Function.span);
break;
case 26 /* Must */:
new (&this->as.Must.expr) (decltype(this->as.Must.expr))(rhs.as.Must.expr);
new (&this->as.Must.span) (decltype(this->as.Must.span))(rhs.as.Must.span);
break;
case 27 /* Try */:
new (&this->as.Try.expr) (decltype(this->as.Try.expr))(rhs.as.Try.expr);
new (&this->as.Try.catch_block) (decltype(this->as.Try.catch_block))(rhs.as.Try.catch_block);
new (&this->as.Try.catch_span) (decltype(this->as.Try.catch_span))(rhs.as.Try.catch_span);
new (&this->as.Try.catch_name) (decltype(this->as.Try.catch_name))(rhs.as.Try.catch_name);
new (&this->as.Try.span) (decltype(this->as.Try.span))(rhs.as.Try.span);
break;
case 28 /* TryBlock */:
new (&this->as.TryBlock.stmt) (decltype(this->as.TryBlock.stmt))(rhs.as.TryBlock.stmt);
new (&this->as.TryBlock.error_name) (decltype(this->as.TryBlock.error_name))(rhs.as.TryBlock.error_name);
new (&this->as.TryBlock.error_span) (decltype(this->as.TryBlock.error_span))(rhs.as.TryBlock.error_span);
new (&this->as.TryBlock.catch_block) (decltype(this->as.TryBlock.catch_block))(rhs.as.TryBlock.catch_block);
new (&this->as.TryBlock.span) (decltype(this->as.TryBlock.span))(rhs.as.TryBlock.span);
break;
case 29 /* Reflect */:
new (&this->as.Reflect.type) (decltype(this->as.Reflect.type))(rhs.as.Reflect.type);
new (&this->as.Reflect.span) (decltype(this->as.Reflect.span))(rhs.as.Reflect.span);
break;
case 30 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(rhs.as.Garbage.value);
break;
case 31 /* Unsafe */:
new (&this->as.Unsafe.expr) (decltype(this->as.Unsafe.expr))(rhs.as.Unsafe.expr);
new (&this->as.Unsafe.span) (decltype(this->as.Unsafe.span))(rhs.as.Unsafe.span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
this->as.Boolean.val = rhs.as.Boolean.val;
this->as.Boolean.span = rhs.as.Boolean.span;
break;
case 1 /* NumericConstant */:
this->as.NumericConstant.val = rhs.as.NumericConstant.val;
this->as.NumericConstant.span = rhs.as.NumericConstant.span;
break;
case 2 /* QuotedString */:
this->as.QuotedString.val = rhs.as.QuotedString.val;
this->as.QuotedString.span = rhs.as.QuotedString.span;
break;
case 3 /* SingleQuotedString */:
this->as.SingleQuotedString.val = rhs.as.SingleQuotedString.val;
this->as.SingleQuotedString.prefix = rhs.as.SingleQuotedString.prefix;
this->as.SingleQuotedString.span = rhs.as.SingleQuotedString.span;
break;
case 4 /* Call */:
this->as.Call.call = rhs.as.Call.call;
this->as.Call.span = rhs.as.Call.span;
break;
case 5 /* MethodCall */:
this->as.MethodCall.expr = rhs.as.MethodCall.expr;
this->as.MethodCall.call = rhs.as.MethodCall.call;
this->as.MethodCall.is_optional = rhs.as.MethodCall.is_optional;
this->as.MethodCall.span = rhs.as.MethodCall.span;
break;
case 6 /* IndexedTuple */:
this->as.IndexedTuple.expr = rhs.as.IndexedTuple.expr;
this->as.IndexedTuple.index = rhs.as.IndexedTuple.index;
this->as.IndexedTuple.is_optional = rhs.as.IndexedTuple.is_optional;
this->as.IndexedTuple.span = rhs.as.IndexedTuple.span;
break;
case 7 /* IndexedStruct */:
this->as.IndexedStruct.expr = rhs.as.IndexedStruct.expr;
this->as.IndexedStruct.field_name = rhs.as.IndexedStruct.field_name;
this->as.IndexedStruct.is_optional = rhs.as.IndexedStruct.is_optional;
this->as.IndexedStruct.span = rhs.as.IndexedStruct.span;
break;
case 8 /* ComptimeIndex */:
this->as.ComptimeIndex.expr = rhs.as.ComptimeIndex.expr;
this->as.ComptimeIndex.index = rhs.as.ComptimeIndex.index;
this->as.ComptimeIndex.is_optional = rhs.as.ComptimeIndex.is_optional;
this->as.ComptimeIndex.span = rhs.as.ComptimeIndex.span;
break;
case 9 /* Var */:
this->as.Var.name = rhs.as.Var.name;
this->as.Var.span = rhs.as.Var.span;
break;
case 10 /* IndexedExpression */:
this->as.IndexedExpression.base = rhs.as.IndexedExpression.base;
this->as.IndexedExpression.index = rhs.as.IndexedExpression.index;
this->as.IndexedExpression.span = rhs.as.IndexedExpression.span;
break;
case 11 /* UnaryOp */:
this->as.UnaryOp.expr = rhs.as.UnaryOp.expr;
this->as.UnaryOp.op = rhs.as.UnaryOp.op;
this->as.UnaryOp.span = rhs.as.UnaryOp.span;
break;
case 12 /* BinaryOp */:
this->as.BinaryOp.lhs = rhs.as.BinaryOp.lhs;
this->as.BinaryOp.op = rhs.as.BinaryOp.op;
this->as.BinaryOp.rhs = rhs.as.BinaryOp.rhs;
this->as.BinaryOp.span = rhs.as.BinaryOp.span;
break;
case 13 /* Operator */:
this->as.Operator.op = rhs.as.Operator.op;
this->as.Operator.span = rhs.as.Operator.span;
break;
case 14 /* OptionalSome */:
this->as.OptionalSome.expr = rhs.as.OptionalSome.expr;
this->as.OptionalSome.span = rhs.as.OptionalSome.span;
break;
case 15 /* OptionalNone */:
this->as.OptionalNone.value = rhs.as.OptionalNone.value;
break;
case 16 /* JaktArray */:
this->as.JaktArray.values = rhs.as.JaktArray.values;
this->as.JaktArray.fill_size = rhs.as.JaktArray.fill_size;
this->as.JaktArray.span = rhs.as.JaktArray.span;
break;
case 17 /* JaktDictionary */:
this->as.JaktDictionary.values = rhs.as.JaktDictionary.values;
this->as.JaktDictionary.span = rhs.as.JaktDictionary.span;
break;
case 18 /* Set */:
this->as.Set.values = rhs.as.Set.values;
this->as.Set.span = rhs.as.Set.span;
break;
case 19 /* JaktTuple */:
this->as.JaktTuple.values = rhs.as.JaktTuple.values;
this->as.JaktTuple.span = rhs.as.JaktTuple.span;
break;
case 20 /* Range */:
this->as.Range.from = rhs.as.Range.from;
this->as.Range.to = rhs.as.Range.to;
this->as.Range.span = rhs.as.Range.span;
break;
case 21 /* ForcedUnwrap */:
this->as.ForcedUnwrap.expr = rhs.as.ForcedUnwrap.expr;
this->as.ForcedUnwrap.span = rhs.as.ForcedUnwrap.span;
break;
case 22 /* Match */:
this->as.Match.expr = rhs.as.Match.expr;
this->as.Match.cases = rhs.as.Match.cases;
this->as.Match.span = rhs.as.Match.span;
this->as.Match.marker_span = rhs.as.Match.marker_span;
break;
case 23 /* EnumVariantArg */:
this->as.EnumVariantArg.expr = rhs.as.EnumVariantArg.expr;
this->as.EnumVariantArg.arg = rhs.as.EnumVariantArg.arg;
this->as.EnumVariantArg.enum_variant = rhs.as.EnumVariantArg.enum_variant;
this->as.EnumVariantArg.span = rhs.as.EnumVariantArg.span;
break;
case 24 /* NamespacedVar */:
this->as.NamespacedVar.name = rhs.as.NamespacedVar.name;
this->as.NamespacedVar.namespace_ = rhs.as.NamespacedVar.namespace_;
this->as.NamespacedVar.span = rhs.as.NamespacedVar.span;
break;
case 25 /* Function */:
this->as.Function.captures = rhs.as.Function.captures;
this->as.Function.params = rhs.as.Function.params;
this->as.Function.can_throw = rhs.as.Function.can_throw;
this->as.Function.is_fat_arrow = rhs.as.Function.is_fat_arrow;
this->as.Function.return_type = rhs.as.Function.return_type;
this->as.Function.block = rhs.as.Function.block;
this->as.Function.span = rhs.as.Function.span;
break;
case 26 /* Must */:
this->as.Must.expr = rhs.as.Must.expr;
this->as.Must.span = rhs.as.Must.span;
break;
case 27 /* Try */:
this->as.Try.expr = rhs.as.Try.expr;
this->as.Try.catch_block = rhs.as.Try.catch_block;
this->as.Try.catch_span = rhs.as.Try.catch_span;
this->as.Try.catch_name = rhs.as.Try.catch_name;
this->as.Try.span = rhs.as.Try.span;
break;
case 28 /* TryBlock */:
this->as.TryBlock.stmt = rhs.as.TryBlock.stmt;
this->as.TryBlock.error_name = rhs.as.TryBlock.error_name;
this->as.TryBlock.error_span = rhs.as.TryBlock.error_span;
this->as.TryBlock.catch_block = rhs.as.TryBlock.catch_block;
this->as.TryBlock.span = rhs.as.TryBlock.span;
break;
case 29 /* Reflect */:
this->as.Reflect.type = rhs.as.Reflect.type;
this->as.Reflect.span = rhs.as.Reflect.span;
break;
case 30 /* Garbage */:
this->as.Garbage.value = rhs.as.Garbage.value;
break;
case 31 /* Unsafe */:
this->as.Unsafe.expr = rhs.as.Unsafe.expr;
this->as.Unsafe.span = rhs.as.Unsafe.span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedExpression::ParsedExpression(ParsedExpression const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
new (&this->as.Boolean.val) (decltype(this->as.Boolean.val))(rhs.as.Boolean.val);
new (&this->as.Boolean.span) (decltype(this->as.Boolean.span))(rhs.as.Boolean.span);
break;
case 1 /* NumericConstant */:
new (&this->as.NumericConstant.val) (decltype(this->as.NumericConstant.val))(rhs.as.NumericConstant.val);
new (&this->as.NumericConstant.span) (decltype(this->as.NumericConstant.span))(rhs.as.NumericConstant.span);
break;
case 2 /* QuotedString */:
new (&this->as.QuotedString.val) (decltype(this->as.QuotedString.val))(rhs.as.QuotedString.val);
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(rhs.as.QuotedString.span);
break;
case 3 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.val) (decltype(this->as.SingleQuotedString.val))(rhs.as.SingleQuotedString.val);
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(rhs.as.SingleQuotedString.prefix);
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(rhs.as.SingleQuotedString.span);
break;
case 4 /* Call */:
new (&this->as.Call.call) (decltype(this->as.Call.call))(rhs.as.Call.call);
new (&this->as.Call.span) (decltype(this->as.Call.span))(rhs.as.Call.span);
break;
case 5 /* MethodCall */:
new (&this->as.MethodCall.expr) (decltype(this->as.MethodCall.expr))(rhs.as.MethodCall.expr);
new (&this->as.MethodCall.call) (decltype(this->as.MethodCall.call))(rhs.as.MethodCall.call);
new (&this->as.MethodCall.is_optional) (decltype(this->as.MethodCall.is_optional))(rhs.as.MethodCall.is_optional);
new (&this->as.MethodCall.span) (decltype(this->as.MethodCall.span))(rhs.as.MethodCall.span);
break;
case 6 /* IndexedTuple */:
new (&this->as.IndexedTuple.expr) (decltype(this->as.IndexedTuple.expr))(rhs.as.IndexedTuple.expr);
new (&this->as.IndexedTuple.index) (decltype(this->as.IndexedTuple.index))(rhs.as.IndexedTuple.index);
new (&this->as.IndexedTuple.is_optional) (decltype(this->as.IndexedTuple.is_optional))(rhs.as.IndexedTuple.is_optional);
new (&this->as.IndexedTuple.span) (decltype(this->as.IndexedTuple.span))(rhs.as.IndexedTuple.span);
break;
case 7 /* IndexedStruct */:
new (&this->as.IndexedStruct.expr) (decltype(this->as.IndexedStruct.expr))(rhs.as.IndexedStruct.expr);
new (&this->as.IndexedStruct.field_name) (decltype(this->as.IndexedStruct.field_name))(rhs.as.IndexedStruct.field_name);
new (&this->as.IndexedStruct.is_optional) (decltype(this->as.IndexedStruct.is_optional))(rhs.as.IndexedStruct.is_optional);
new (&this->as.IndexedStruct.span) (decltype(this->as.IndexedStruct.span))(rhs.as.IndexedStruct.span);
break;
case 8 /* ComptimeIndex */:
new (&this->as.ComptimeIndex.expr) (decltype(this->as.ComptimeIndex.expr))(rhs.as.ComptimeIndex.expr);
new (&this->as.ComptimeIndex.index) (decltype(this->as.ComptimeIndex.index))(rhs.as.ComptimeIndex.index);
new (&this->as.ComptimeIndex.is_optional) (decltype(this->as.ComptimeIndex.is_optional))(rhs.as.ComptimeIndex.is_optional);
new (&this->as.ComptimeIndex.span) (decltype(this->as.ComptimeIndex.span))(rhs.as.ComptimeIndex.span);
break;
case 9 /* Var */:
new (&this->as.Var.name) (decltype(this->as.Var.name))(rhs.as.Var.name);
new (&this->as.Var.span) (decltype(this->as.Var.span))(rhs.as.Var.span);
break;
case 10 /* IndexedExpression */:
new (&this->as.IndexedExpression.base) (decltype(this->as.IndexedExpression.base))(rhs.as.IndexedExpression.base);
new (&this->as.IndexedExpression.index) (decltype(this->as.IndexedExpression.index))(rhs.as.IndexedExpression.index);
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(rhs.as.IndexedExpression.span);
break;
case 11 /* UnaryOp */:
new (&this->as.UnaryOp.expr) (decltype(this->as.UnaryOp.expr))(rhs.as.UnaryOp.expr);
new (&this->as.UnaryOp.op) (decltype(this->as.UnaryOp.op))(rhs.as.UnaryOp.op);
new (&this->as.UnaryOp.span) (decltype(this->as.UnaryOp.span))(rhs.as.UnaryOp.span);
break;
case 12 /* BinaryOp */:
new (&this->as.BinaryOp.lhs) (decltype(this->as.BinaryOp.lhs))(rhs.as.BinaryOp.lhs);
new (&this->as.BinaryOp.op) (decltype(this->as.BinaryOp.op))(rhs.as.BinaryOp.op);
new (&this->as.BinaryOp.rhs) (decltype(this->as.BinaryOp.rhs))(rhs.as.BinaryOp.rhs);
new (&this->as.BinaryOp.span) (decltype(this->as.BinaryOp.span))(rhs.as.BinaryOp.span);
break;
case 13 /* Operator */:
new (&this->as.Operator.op) (decltype(this->as.Operator.op))(rhs.as.Operator.op);
new (&this->as.Operator.span) (decltype(this->as.Operator.span))(rhs.as.Operator.span);
break;
case 14 /* OptionalSome */:
new (&this->as.OptionalSome.expr) (decltype(this->as.OptionalSome.expr))(rhs.as.OptionalSome.expr);
new (&this->as.OptionalSome.span) (decltype(this->as.OptionalSome.span))(rhs.as.OptionalSome.span);
break;
case 15 /* OptionalNone */:
new (&this->as.OptionalNone.value) (decltype(this->as.OptionalNone.value))(rhs.as.OptionalNone.value);
break;
case 16 /* JaktArray */:
new (&this->as.JaktArray.values) (decltype(this->as.JaktArray.values))(rhs.as.JaktArray.values);
new (&this->as.JaktArray.fill_size) (decltype(this->as.JaktArray.fill_size))(rhs.as.JaktArray.fill_size);
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(rhs.as.JaktArray.span);
break;
case 17 /* JaktDictionary */:
new (&this->as.JaktDictionary.values) (decltype(this->as.JaktDictionary.values))(rhs.as.JaktDictionary.values);
new (&this->as.JaktDictionary.span) (decltype(this->as.JaktDictionary.span))(rhs.as.JaktDictionary.span);
break;
case 18 /* Set */:
new (&this->as.Set.values) (decltype(this->as.Set.values))(rhs.as.Set.values);
new (&this->as.Set.span) (decltype(this->as.Set.span))(rhs.as.Set.span);
break;
case 19 /* JaktTuple */:
new (&this->as.JaktTuple.values) (decltype(this->as.JaktTuple.values))(rhs.as.JaktTuple.values);
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(rhs.as.JaktTuple.span);
break;
case 20 /* Range */:
new (&this->as.Range.from) (decltype(this->as.Range.from))(rhs.as.Range.from);
new (&this->as.Range.to) (decltype(this->as.Range.to))(rhs.as.Range.to);
new (&this->as.Range.span) (decltype(this->as.Range.span))(rhs.as.Range.span);
break;
case 21 /* ForcedUnwrap */:
new (&this->as.ForcedUnwrap.expr) (decltype(this->as.ForcedUnwrap.expr))(rhs.as.ForcedUnwrap.expr);
new (&this->as.ForcedUnwrap.span) (decltype(this->as.ForcedUnwrap.span))(rhs.as.ForcedUnwrap.span);
break;
case 22 /* Match */:
new (&this->as.Match.expr) (decltype(this->as.Match.expr))(rhs.as.Match.expr);
new (&this->as.Match.cases) (decltype(this->as.Match.cases))(rhs.as.Match.cases);
new (&this->as.Match.span) (decltype(this->as.Match.span))(rhs.as.Match.span);
new (&this->as.Match.marker_span) (decltype(this->as.Match.marker_span))(rhs.as.Match.marker_span);
break;
case 23 /* EnumVariantArg */:
new (&this->as.EnumVariantArg.expr) (decltype(this->as.EnumVariantArg.expr))(rhs.as.EnumVariantArg.expr);
new (&this->as.EnumVariantArg.arg) (decltype(this->as.EnumVariantArg.arg))(rhs.as.EnumVariantArg.arg);
new (&this->as.EnumVariantArg.enum_variant) (decltype(this->as.EnumVariantArg.enum_variant))(rhs.as.EnumVariantArg.enum_variant);
new (&this->as.EnumVariantArg.span) (decltype(this->as.EnumVariantArg.span))(rhs.as.EnumVariantArg.span);
break;
case 24 /* NamespacedVar */:
new (&this->as.NamespacedVar.name) (decltype(this->as.NamespacedVar.name))(rhs.as.NamespacedVar.name);
new (&this->as.NamespacedVar.namespace_) (decltype(this->as.NamespacedVar.namespace_))(rhs.as.NamespacedVar.namespace_);
new (&this->as.NamespacedVar.span) (decltype(this->as.NamespacedVar.span))(rhs.as.NamespacedVar.span);
break;
case 25 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(rhs.as.Function.captures);
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.is_fat_arrow) (decltype(this->as.Function.is_fat_arrow))(rhs.as.Function.is_fat_arrow);
new (&this->as.Function.return_type) (decltype(this->as.Function.return_type))(rhs.as.Function.return_type);
new (&this->as.Function.block) (decltype(this->as.Function.block))(rhs.as.Function.block);
new (&this->as.Function.span) (decltype(this->as.Function.span))(rhs.as.Function.span);
break;
case 26 /* Must */:
new (&this->as.Must.expr) (decltype(this->as.Must.expr))(rhs.as.Must.expr);
new (&this->as.Must.span) (decltype(this->as.Must.span))(rhs.as.Must.span);
break;
case 27 /* Try */:
new (&this->as.Try.expr) (decltype(this->as.Try.expr))(rhs.as.Try.expr);
new (&this->as.Try.catch_block) (decltype(this->as.Try.catch_block))(rhs.as.Try.catch_block);
new (&this->as.Try.catch_span) (decltype(this->as.Try.catch_span))(rhs.as.Try.catch_span);
new (&this->as.Try.catch_name) (decltype(this->as.Try.catch_name))(rhs.as.Try.catch_name);
new (&this->as.Try.span) (decltype(this->as.Try.span))(rhs.as.Try.span);
break;
case 28 /* TryBlock */:
new (&this->as.TryBlock.stmt) (decltype(this->as.TryBlock.stmt))(rhs.as.TryBlock.stmt);
new (&this->as.TryBlock.error_name) (decltype(this->as.TryBlock.error_name))(rhs.as.TryBlock.error_name);
new (&this->as.TryBlock.error_span) (decltype(this->as.TryBlock.error_span))(rhs.as.TryBlock.error_span);
new (&this->as.TryBlock.catch_block) (decltype(this->as.TryBlock.catch_block))(rhs.as.TryBlock.catch_block);
new (&this->as.TryBlock.span) (decltype(this->as.TryBlock.span))(rhs.as.TryBlock.span);
break;
case 29 /* Reflect */:
new (&this->as.Reflect.type) (decltype(this->as.Reflect.type))(rhs.as.Reflect.type);
new (&this->as.Reflect.span) (decltype(this->as.Reflect.span))(rhs.as.Reflect.span);
break;
case 30 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(rhs.as.Garbage.value);
break;
case 31 /* Unsafe */:
new (&this->as.Unsafe.expr) (decltype(this->as.Unsafe.expr))(rhs.as.Unsafe.expr);
new (&this->as.Unsafe.span) (decltype(this->as.Unsafe.span))(rhs.as.Unsafe.span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ParsedExpression& ParsedExpression::operator=(ParsedExpression &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
new (&this->as.Boolean.val) (decltype(this->as.Boolean.val))(move(rhs.as.Boolean.val));
new (&this->as.Boolean.span) (decltype(this->as.Boolean.span))(move(rhs.as.Boolean.span));
break;
case 1 /* NumericConstant */:
new (&this->as.NumericConstant.val) (decltype(this->as.NumericConstant.val))(move(rhs.as.NumericConstant.val));
new (&this->as.NumericConstant.span) (decltype(this->as.NumericConstant.span))(move(rhs.as.NumericConstant.span));
break;
case 2 /* QuotedString */:
new (&this->as.QuotedString.val) (decltype(this->as.QuotedString.val))(move(rhs.as.QuotedString.val));
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(move(rhs.as.QuotedString.span));
break;
case 3 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.val) (decltype(this->as.SingleQuotedString.val))(move(rhs.as.SingleQuotedString.val));
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(move(rhs.as.SingleQuotedString.prefix));
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(move(rhs.as.SingleQuotedString.span));
break;
case 4 /* Call */:
new (&this->as.Call.call) (decltype(this->as.Call.call))(move(rhs.as.Call.call));
new (&this->as.Call.span) (decltype(this->as.Call.span))(move(rhs.as.Call.span));
break;
case 5 /* MethodCall */:
new (&this->as.MethodCall.expr) (decltype(this->as.MethodCall.expr))(move(rhs.as.MethodCall.expr));
new (&this->as.MethodCall.call) (decltype(this->as.MethodCall.call))(move(rhs.as.MethodCall.call));
new (&this->as.MethodCall.is_optional) (decltype(this->as.MethodCall.is_optional))(move(rhs.as.MethodCall.is_optional));
new (&this->as.MethodCall.span) (decltype(this->as.MethodCall.span))(move(rhs.as.MethodCall.span));
break;
case 6 /* IndexedTuple */:
new (&this->as.IndexedTuple.expr) (decltype(this->as.IndexedTuple.expr))(move(rhs.as.IndexedTuple.expr));
new (&this->as.IndexedTuple.index) (decltype(this->as.IndexedTuple.index))(move(rhs.as.IndexedTuple.index));
new (&this->as.IndexedTuple.is_optional) (decltype(this->as.IndexedTuple.is_optional))(move(rhs.as.IndexedTuple.is_optional));
new (&this->as.IndexedTuple.span) (decltype(this->as.IndexedTuple.span))(move(rhs.as.IndexedTuple.span));
break;
case 7 /* IndexedStruct */:
new (&this->as.IndexedStruct.expr) (decltype(this->as.IndexedStruct.expr))(move(rhs.as.IndexedStruct.expr));
new (&this->as.IndexedStruct.field_name) (decltype(this->as.IndexedStruct.field_name))(move(rhs.as.IndexedStruct.field_name));
new (&this->as.IndexedStruct.is_optional) (decltype(this->as.IndexedStruct.is_optional))(move(rhs.as.IndexedStruct.is_optional));
new (&this->as.IndexedStruct.span) (decltype(this->as.IndexedStruct.span))(move(rhs.as.IndexedStruct.span));
break;
case 8 /* ComptimeIndex */:
new (&this->as.ComptimeIndex.expr) (decltype(this->as.ComptimeIndex.expr))(move(rhs.as.ComptimeIndex.expr));
new (&this->as.ComptimeIndex.index) (decltype(this->as.ComptimeIndex.index))(move(rhs.as.ComptimeIndex.index));
new (&this->as.ComptimeIndex.is_optional) (decltype(this->as.ComptimeIndex.is_optional))(move(rhs.as.ComptimeIndex.is_optional));
new (&this->as.ComptimeIndex.span) (decltype(this->as.ComptimeIndex.span))(move(rhs.as.ComptimeIndex.span));
break;
case 9 /* Var */:
new (&this->as.Var.name) (decltype(this->as.Var.name))(move(rhs.as.Var.name));
new (&this->as.Var.span) (decltype(this->as.Var.span))(move(rhs.as.Var.span));
break;
case 10 /* IndexedExpression */:
new (&this->as.IndexedExpression.base) (decltype(this->as.IndexedExpression.base))(move(rhs.as.IndexedExpression.base));
new (&this->as.IndexedExpression.index) (decltype(this->as.IndexedExpression.index))(move(rhs.as.IndexedExpression.index));
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(move(rhs.as.IndexedExpression.span));
break;
case 11 /* UnaryOp */:
new (&this->as.UnaryOp.expr) (decltype(this->as.UnaryOp.expr))(move(rhs.as.UnaryOp.expr));
new (&this->as.UnaryOp.op) (decltype(this->as.UnaryOp.op))(move(rhs.as.UnaryOp.op));
new (&this->as.UnaryOp.span) (decltype(this->as.UnaryOp.span))(move(rhs.as.UnaryOp.span));
break;
case 12 /* BinaryOp */:
new (&this->as.BinaryOp.lhs) (decltype(this->as.BinaryOp.lhs))(move(rhs.as.BinaryOp.lhs));
new (&this->as.BinaryOp.op) (decltype(this->as.BinaryOp.op))(move(rhs.as.BinaryOp.op));
new (&this->as.BinaryOp.rhs) (decltype(this->as.BinaryOp.rhs))(move(rhs.as.BinaryOp.rhs));
new (&this->as.BinaryOp.span) (decltype(this->as.BinaryOp.span))(move(rhs.as.BinaryOp.span));
break;
case 13 /* Operator */:
new (&this->as.Operator.op) (decltype(this->as.Operator.op))(move(rhs.as.Operator.op));
new (&this->as.Operator.span) (decltype(this->as.Operator.span))(move(rhs.as.Operator.span));
break;
case 14 /* OptionalSome */:
new (&this->as.OptionalSome.expr) (decltype(this->as.OptionalSome.expr))(move(rhs.as.OptionalSome.expr));
new (&this->as.OptionalSome.span) (decltype(this->as.OptionalSome.span))(move(rhs.as.OptionalSome.span));
break;
case 15 /* OptionalNone */:
new (&this->as.OptionalNone.value) (decltype(this->as.OptionalNone.value))(move(rhs.as.OptionalNone.value));
break;
case 16 /* JaktArray */:
new (&this->as.JaktArray.values) (decltype(this->as.JaktArray.values))(move(rhs.as.JaktArray.values));
new (&this->as.JaktArray.fill_size) (decltype(this->as.JaktArray.fill_size))(move(rhs.as.JaktArray.fill_size));
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(move(rhs.as.JaktArray.span));
break;
case 17 /* JaktDictionary */:
new (&this->as.JaktDictionary.values) (decltype(this->as.JaktDictionary.values))(move(rhs.as.JaktDictionary.values));
new (&this->as.JaktDictionary.span) (decltype(this->as.JaktDictionary.span))(move(rhs.as.JaktDictionary.span));
break;
case 18 /* Set */:
new (&this->as.Set.values) (decltype(this->as.Set.values))(move(rhs.as.Set.values));
new (&this->as.Set.span) (decltype(this->as.Set.span))(move(rhs.as.Set.span));
break;
case 19 /* JaktTuple */:
new (&this->as.JaktTuple.values) (decltype(this->as.JaktTuple.values))(move(rhs.as.JaktTuple.values));
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(move(rhs.as.JaktTuple.span));
break;
case 20 /* Range */:
new (&this->as.Range.from) (decltype(this->as.Range.from))(move(rhs.as.Range.from));
new (&this->as.Range.to) (decltype(this->as.Range.to))(move(rhs.as.Range.to));
new (&this->as.Range.span) (decltype(this->as.Range.span))(move(rhs.as.Range.span));
break;
case 21 /* ForcedUnwrap */:
new (&this->as.ForcedUnwrap.expr) (decltype(this->as.ForcedUnwrap.expr))(move(rhs.as.ForcedUnwrap.expr));
new (&this->as.ForcedUnwrap.span) (decltype(this->as.ForcedUnwrap.span))(move(rhs.as.ForcedUnwrap.span));
break;
case 22 /* Match */:
new (&this->as.Match.expr) (decltype(this->as.Match.expr))(move(rhs.as.Match.expr));
new (&this->as.Match.cases) (decltype(this->as.Match.cases))(move(rhs.as.Match.cases));
new (&this->as.Match.span) (decltype(this->as.Match.span))(move(rhs.as.Match.span));
new (&this->as.Match.marker_span) (decltype(this->as.Match.marker_span))(move(rhs.as.Match.marker_span));
break;
case 23 /* EnumVariantArg */:
new (&this->as.EnumVariantArg.expr) (decltype(this->as.EnumVariantArg.expr))(move(rhs.as.EnumVariantArg.expr));
new (&this->as.EnumVariantArg.arg) (decltype(this->as.EnumVariantArg.arg))(move(rhs.as.EnumVariantArg.arg));
new (&this->as.EnumVariantArg.enum_variant) (decltype(this->as.EnumVariantArg.enum_variant))(move(rhs.as.EnumVariantArg.enum_variant));
new (&this->as.EnumVariantArg.span) (decltype(this->as.EnumVariantArg.span))(move(rhs.as.EnumVariantArg.span));
break;
case 24 /* NamespacedVar */:
new (&this->as.NamespacedVar.name) (decltype(this->as.NamespacedVar.name))(move(rhs.as.NamespacedVar.name));
new (&this->as.NamespacedVar.namespace_) (decltype(this->as.NamespacedVar.namespace_))(move(rhs.as.NamespacedVar.namespace_));
new (&this->as.NamespacedVar.span) (decltype(this->as.NamespacedVar.span))(move(rhs.as.NamespacedVar.span));
break;
case 25 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(move(rhs.as.Function.captures));
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.is_fat_arrow) (decltype(this->as.Function.is_fat_arrow))(move(rhs.as.Function.is_fat_arrow));
new (&this->as.Function.return_type) (decltype(this->as.Function.return_type))(move(rhs.as.Function.return_type));
new (&this->as.Function.block) (decltype(this->as.Function.block))(move(rhs.as.Function.block));
new (&this->as.Function.span) (decltype(this->as.Function.span))(move(rhs.as.Function.span));
break;
case 26 /* Must */:
new (&this->as.Must.expr) (decltype(this->as.Must.expr))(move(rhs.as.Must.expr));
new (&this->as.Must.span) (decltype(this->as.Must.span))(move(rhs.as.Must.span));
break;
case 27 /* Try */:
new (&this->as.Try.expr) (decltype(this->as.Try.expr))(move(rhs.as.Try.expr));
new (&this->as.Try.catch_block) (decltype(this->as.Try.catch_block))(move(rhs.as.Try.catch_block));
new (&this->as.Try.catch_span) (decltype(this->as.Try.catch_span))(move(rhs.as.Try.catch_span));
new (&this->as.Try.catch_name) (decltype(this->as.Try.catch_name))(move(rhs.as.Try.catch_name));
new (&this->as.Try.span) (decltype(this->as.Try.span))(move(rhs.as.Try.span));
break;
case 28 /* TryBlock */:
new (&this->as.TryBlock.stmt) (decltype(this->as.TryBlock.stmt))(move(rhs.as.TryBlock.stmt));
new (&this->as.TryBlock.error_name) (decltype(this->as.TryBlock.error_name))(move(rhs.as.TryBlock.error_name));
new (&this->as.TryBlock.error_span) (decltype(this->as.TryBlock.error_span))(move(rhs.as.TryBlock.error_span));
new (&this->as.TryBlock.catch_block) (decltype(this->as.TryBlock.catch_block))(move(rhs.as.TryBlock.catch_block));
new (&this->as.TryBlock.span) (decltype(this->as.TryBlock.span))(move(rhs.as.TryBlock.span));
break;
case 29 /* Reflect */:
new (&this->as.Reflect.type) (decltype(this->as.Reflect.type))(move(rhs.as.Reflect.type));
new (&this->as.Reflect.span) (decltype(this->as.Reflect.span))(move(rhs.as.Reflect.span));
break;
case 30 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(move(rhs.as.Garbage.value));
break;
case 31 /* Unsafe */:
new (&this->as.Unsafe.expr) (decltype(this->as.Unsafe.expr))(move(rhs.as.Unsafe.expr));
new (&this->as.Unsafe.span) (decltype(this->as.Unsafe.span))(move(rhs.as.Unsafe.span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
this->as.Boolean.val = move(rhs.as.Boolean.val);
this->as.Boolean.span = move(rhs.as.Boolean.span);
break;
case 1 /* NumericConstant */:
this->as.NumericConstant.val = move(rhs.as.NumericConstant.val);
this->as.NumericConstant.span = move(rhs.as.NumericConstant.span);
break;
case 2 /* QuotedString */:
this->as.QuotedString.val = move(rhs.as.QuotedString.val);
this->as.QuotedString.span = move(rhs.as.QuotedString.span);
break;
case 3 /* SingleQuotedString */:
this->as.SingleQuotedString.val = move(rhs.as.SingleQuotedString.val);
this->as.SingleQuotedString.prefix = move(rhs.as.SingleQuotedString.prefix);
this->as.SingleQuotedString.span = move(rhs.as.SingleQuotedString.span);
break;
case 4 /* Call */:
this->as.Call.call = move(rhs.as.Call.call);
this->as.Call.span = move(rhs.as.Call.span);
break;
case 5 /* MethodCall */:
this->as.MethodCall.expr = move(rhs.as.MethodCall.expr);
this->as.MethodCall.call = move(rhs.as.MethodCall.call);
this->as.MethodCall.is_optional = move(rhs.as.MethodCall.is_optional);
this->as.MethodCall.span = move(rhs.as.MethodCall.span);
break;
case 6 /* IndexedTuple */:
this->as.IndexedTuple.expr = move(rhs.as.IndexedTuple.expr);
this->as.IndexedTuple.index = move(rhs.as.IndexedTuple.index);
this->as.IndexedTuple.is_optional = move(rhs.as.IndexedTuple.is_optional);
this->as.IndexedTuple.span = move(rhs.as.IndexedTuple.span);
break;
case 7 /* IndexedStruct */:
this->as.IndexedStruct.expr = move(rhs.as.IndexedStruct.expr);
this->as.IndexedStruct.field_name = move(rhs.as.IndexedStruct.field_name);
this->as.IndexedStruct.is_optional = move(rhs.as.IndexedStruct.is_optional);
this->as.IndexedStruct.span = move(rhs.as.IndexedStruct.span);
break;
case 8 /* ComptimeIndex */:
this->as.ComptimeIndex.expr = move(rhs.as.ComptimeIndex.expr);
this->as.ComptimeIndex.index = move(rhs.as.ComptimeIndex.index);
this->as.ComptimeIndex.is_optional = move(rhs.as.ComptimeIndex.is_optional);
this->as.ComptimeIndex.span = move(rhs.as.ComptimeIndex.span);
break;
case 9 /* Var */:
this->as.Var.name = move(rhs.as.Var.name);
this->as.Var.span = move(rhs.as.Var.span);
break;
case 10 /* IndexedExpression */:
this->as.IndexedExpression.base = move(rhs.as.IndexedExpression.base);
this->as.IndexedExpression.index = move(rhs.as.IndexedExpression.index);
this->as.IndexedExpression.span = move(rhs.as.IndexedExpression.span);
break;
case 11 /* UnaryOp */:
this->as.UnaryOp.expr = move(rhs.as.UnaryOp.expr);
this->as.UnaryOp.op = move(rhs.as.UnaryOp.op);
this->as.UnaryOp.span = move(rhs.as.UnaryOp.span);
break;
case 12 /* BinaryOp */:
this->as.BinaryOp.lhs = move(rhs.as.BinaryOp.lhs);
this->as.BinaryOp.op = move(rhs.as.BinaryOp.op);
this->as.BinaryOp.rhs = move(rhs.as.BinaryOp.rhs);
this->as.BinaryOp.span = move(rhs.as.BinaryOp.span);
break;
case 13 /* Operator */:
this->as.Operator.op = move(rhs.as.Operator.op);
this->as.Operator.span = move(rhs.as.Operator.span);
break;
case 14 /* OptionalSome */:
this->as.OptionalSome.expr = move(rhs.as.OptionalSome.expr);
this->as.OptionalSome.span = move(rhs.as.OptionalSome.span);
break;
case 15 /* OptionalNone */:
this->as.OptionalNone.value = move(rhs.as.OptionalNone.value);
break;
case 16 /* JaktArray */:
this->as.JaktArray.values = move(rhs.as.JaktArray.values);
this->as.JaktArray.fill_size = move(rhs.as.JaktArray.fill_size);
this->as.JaktArray.span = move(rhs.as.JaktArray.span);
break;
case 17 /* JaktDictionary */:
this->as.JaktDictionary.values = move(rhs.as.JaktDictionary.values);
this->as.JaktDictionary.span = move(rhs.as.JaktDictionary.span);
break;
case 18 /* Set */:
this->as.Set.values = move(rhs.as.Set.values);
this->as.Set.span = move(rhs.as.Set.span);
break;
case 19 /* JaktTuple */:
this->as.JaktTuple.values = move(rhs.as.JaktTuple.values);
this->as.JaktTuple.span = move(rhs.as.JaktTuple.span);
break;
case 20 /* Range */:
this->as.Range.from = move(rhs.as.Range.from);
this->as.Range.to = move(rhs.as.Range.to);
this->as.Range.span = move(rhs.as.Range.span);
break;
case 21 /* ForcedUnwrap */:
this->as.ForcedUnwrap.expr = move(rhs.as.ForcedUnwrap.expr);
this->as.ForcedUnwrap.span = move(rhs.as.ForcedUnwrap.span);
break;
case 22 /* Match */:
this->as.Match.expr = move(rhs.as.Match.expr);
this->as.Match.cases = move(rhs.as.Match.cases);
this->as.Match.span = move(rhs.as.Match.span);
this->as.Match.marker_span = move(rhs.as.Match.marker_span);
break;
case 23 /* EnumVariantArg */:
this->as.EnumVariantArg.expr = move(rhs.as.EnumVariantArg.expr);
this->as.EnumVariantArg.arg = move(rhs.as.EnumVariantArg.arg);
this->as.EnumVariantArg.enum_variant = move(rhs.as.EnumVariantArg.enum_variant);
this->as.EnumVariantArg.span = move(rhs.as.EnumVariantArg.span);
break;
case 24 /* NamespacedVar */:
this->as.NamespacedVar.name = move(rhs.as.NamespacedVar.name);
this->as.NamespacedVar.namespace_ = move(rhs.as.NamespacedVar.namespace_);
this->as.NamespacedVar.span = move(rhs.as.NamespacedVar.span);
break;
case 25 /* Function */:
this->as.Function.captures = move(rhs.as.Function.captures);
this->as.Function.params = move(rhs.as.Function.params);
this->as.Function.can_throw = move(rhs.as.Function.can_throw);
this->as.Function.is_fat_arrow = move(rhs.as.Function.is_fat_arrow);
this->as.Function.return_type = move(rhs.as.Function.return_type);
this->as.Function.block = move(rhs.as.Function.block);
this->as.Function.span = move(rhs.as.Function.span);
break;
case 26 /* Must */:
this->as.Must.expr = move(rhs.as.Must.expr);
this->as.Must.span = move(rhs.as.Must.span);
break;
case 27 /* Try */:
this->as.Try.expr = move(rhs.as.Try.expr);
this->as.Try.catch_block = move(rhs.as.Try.catch_block);
this->as.Try.catch_span = move(rhs.as.Try.catch_span);
this->as.Try.catch_name = move(rhs.as.Try.catch_name);
this->as.Try.span = move(rhs.as.Try.span);
break;
case 28 /* TryBlock */:
this->as.TryBlock.stmt = move(rhs.as.TryBlock.stmt);
this->as.TryBlock.error_name = move(rhs.as.TryBlock.error_name);
this->as.TryBlock.error_span = move(rhs.as.TryBlock.error_span);
this->as.TryBlock.catch_block = move(rhs.as.TryBlock.catch_block);
this->as.TryBlock.span = move(rhs.as.TryBlock.span);
break;
case 29 /* Reflect */:
this->as.Reflect.type = move(rhs.as.Reflect.type);
this->as.Reflect.span = move(rhs.as.Reflect.span);
break;
case 30 /* Garbage */:
this->as.Garbage.value = move(rhs.as.Garbage.value);
break;
case 31 /* Unsafe */:
this->as.Unsafe.expr = move(rhs.as.Unsafe.expr);
this->as.Unsafe.span = move(rhs.as.Unsafe.span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedExpression::ParsedExpression(ParsedExpression &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
new (&this->as.Boolean.val) (decltype(this->as.Boolean.val))(move(rhs.as.Boolean.val));
new (&this->as.Boolean.span) (decltype(this->as.Boolean.span))(move(rhs.as.Boolean.span));
break;
case 1 /* NumericConstant */:
new (&this->as.NumericConstant.val) (decltype(this->as.NumericConstant.val))(move(rhs.as.NumericConstant.val));
new (&this->as.NumericConstant.span) (decltype(this->as.NumericConstant.span))(move(rhs.as.NumericConstant.span));
break;
case 2 /* QuotedString */:
new (&this->as.QuotedString.val) (decltype(this->as.QuotedString.val))(move(rhs.as.QuotedString.val));
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(move(rhs.as.QuotedString.span));
break;
case 3 /* SingleQuotedString */:
new (&this->as.SingleQuotedString.val) (decltype(this->as.SingleQuotedString.val))(move(rhs.as.SingleQuotedString.val));
new (&this->as.SingleQuotedString.prefix) (decltype(this->as.SingleQuotedString.prefix))(move(rhs.as.SingleQuotedString.prefix));
new (&this->as.SingleQuotedString.span) (decltype(this->as.SingleQuotedString.span))(move(rhs.as.SingleQuotedString.span));
break;
case 4 /* Call */:
new (&this->as.Call.call) (decltype(this->as.Call.call))(move(rhs.as.Call.call));
new (&this->as.Call.span) (decltype(this->as.Call.span))(move(rhs.as.Call.span));
break;
case 5 /* MethodCall */:
new (&this->as.MethodCall.expr) (decltype(this->as.MethodCall.expr))(move(rhs.as.MethodCall.expr));
new (&this->as.MethodCall.call) (decltype(this->as.MethodCall.call))(move(rhs.as.MethodCall.call));
new (&this->as.MethodCall.is_optional) (decltype(this->as.MethodCall.is_optional))(move(rhs.as.MethodCall.is_optional));
new (&this->as.MethodCall.span) (decltype(this->as.MethodCall.span))(move(rhs.as.MethodCall.span));
break;
case 6 /* IndexedTuple */:
new (&this->as.IndexedTuple.expr) (decltype(this->as.IndexedTuple.expr))(move(rhs.as.IndexedTuple.expr));
new (&this->as.IndexedTuple.index) (decltype(this->as.IndexedTuple.index))(move(rhs.as.IndexedTuple.index));
new (&this->as.IndexedTuple.is_optional) (decltype(this->as.IndexedTuple.is_optional))(move(rhs.as.IndexedTuple.is_optional));
new (&this->as.IndexedTuple.span) (decltype(this->as.IndexedTuple.span))(move(rhs.as.IndexedTuple.span));
break;
case 7 /* IndexedStruct */:
new (&this->as.IndexedStruct.expr) (decltype(this->as.IndexedStruct.expr))(move(rhs.as.IndexedStruct.expr));
new (&this->as.IndexedStruct.field_name) (decltype(this->as.IndexedStruct.field_name))(move(rhs.as.IndexedStruct.field_name));
new (&this->as.IndexedStruct.is_optional) (decltype(this->as.IndexedStruct.is_optional))(move(rhs.as.IndexedStruct.is_optional));
new (&this->as.IndexedStruct.span) (decltype(this->as.IndexedStruct.span))(move(rhs.as.IndexedStruct.span));
break;
case 8 /* ComptimeIndex */:
new (&this->as.ComptimeIndex.expr) (decltype(this->as.ComptimeIndex.expr))(move(rhs.as.ComptimeIndex.expr));
new (&this->as.ComptimeIndex.index) (decltype(this->as.ComptimeIndex.index))(move(rhs.as.ComptimeIndex.index));
new (&this->as.ComptimeIndex.is_optional) (decltype(this->as.ComptimeIndex.is_optional))(move(rhs.as.ComptimeIndex.is_optional));
new (&this->as.ComptimeIndex.span) (decltype(this->as.ComptimeIndex.span))(move(rhs.as.ComptimeIndex.span));
break;
case 9 /* Var */:
new (&this->as.Var.name) (decltype(this->as.Var.name))(move(rhs.as.Var.name));
new (&this->as.Var.span) (decltype(this->as.Var.span))(move(rhs.as.Var.span));
break;
case 10 /* IndexedExpression */:
new (&this->as.IndexedExpression.base) (decltype(this->as.IndexedExpression.base))(move(rhs.as.IndexedExpression.base));
new (&this->as.IndexedExpression.index) (decltype(this->as.IndexedExpression.index))(move(rhs.as.IndexedExpression.index));
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(move(rhs.as.IndexedExpression.span));
break;
case 11 /* UnaryOp */:
new (&this->as.UnaryOp.expr) (decltype(this->as.UnaryOp.expr))(move(rhs.as.UnaryOp.expr));
new (&this->as.UnaryOp.op) (decltype(this->as.UnaryOp.op))(move(rhs.as.UnaryOp.op));
new (&this->as.UnaryOp.span) (decltype(this->as.UnaryOp.span))(move(rhs.as.UnaryOp.span));
break;
case 12 /* BinaryOp */:
new (&this->as.BinaryOp.lhs) (decltype(this->as.BinaryOp.lhs))(move(rhs.as.BinaryOp.lhs));
new (&this->as.BinaryOp.op) (decltype(this->as.BinaryOp.op))(move(rhs.as.BinaryOp.op));
new (&this->as.BinaryOp.rhs) (decltype(this->as.BinaryOp.rhs))(move(rhs.as.BinaryOp.rhs));
new (&this->as.BinaryOp.span) (decltype(this->as.BinaryOp.span))(move(rhs.as.BinaryOp.span));
break;
case 13 /* Operator */:
new (&this->as.Operator.op) (decltype(this->as.Operator.op))(move(rhs.as.Operator.op));
new (&this->as.Operator.span) (decltype(this->as.Operator.span))(move(rhs.as.Operator.span));
break;
case 14 /* OptionalSome */:
new (&this->as.OptionalSome.expr) (decltype(this->as.OptionalSome.expr))(move(rhs.as.OptionalSome.expr));
new (&this->as.OptionalSome.span) (decltype(this->as.OptionalSome.span))(move(rhs.as.OptionalSome.span));
break;
case 15 /* OptionalNone */:
new (&this->as.OptionalNone.value) (decltype(this->as.OptionalNone.value))(move(rhs.as.OptionalNone.value));
break;
case 16 /* JaktArray */:
new (&this->as.JaktArray.values) (decltype(this->as.JaktArray.values))(move(rhs.as.JaktArray.values));
new (&this->as.JaktArray.fill_size) (decltype(this->as.JaktArray.fill_size))(move(rhs.as.JaktArray.fill_size));
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(move(rhs.as.JaktArray.span));
break;
case 17 /* JaktDictionary */:
new (&this->as.JaktDictionary.values) (decltype(this->as.JaktDictionary.values))(move(rhs.as.JaktDictionary.values));
new (&this->as.JaktDictionary.span) (decltype(this->as.JaktDictionary.span))(move(rhs.as.JaktDictionary.span));
break;
case 18 /* Set */:
new (&this->as.Set.values) (decltype(this->as.Set.values))(move(rhs.as.Set.values));
new (&this->as.Set.span) (decltype(this->as.Set.span))(move(rhs.as.Set.span));
break;
case 19 /* JaktTuple */:
new (&this->as.JaktTuple.values) (decltype(this->as.JaktTuple.values))(move(rhs.as.JaktTuple.values));
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(move(rhs.as.JaktTuple.span));
break;
case 20 /* Range */:
new (&this->as.Range.from) (decltype(this->as.Range.from))(move(rhs.as.Range.from));
new (&this->as.Range.to) (decltype(this->as.Range.to))(move(rhs.as.Range.to));
new (&this->as.Range.span) (decltype(this->as.Range.span))(move(rhs.as.Range.span));
break;
case 21 /* ForcedUnwrap */:
new (&this->as.ForcedUnwrap.expr) (decltype(this->as.ForcedUnwrap.expr))(move(rhs.as.ForcedUnwrap.expr));
new (&this->as.ForcedUnwrap.span) (decltype(this->as.ForcedUnwrap.span))(move(rhs.as.ForcedUnwrap.span));
break;
case 22 /* Match */:
new (&this->as.Match.expr) (decltype(this->as.Match.expr))(move(rhs.as.Match.expr));
new (&this->as.Match.cases) (decltype(this->as.Match.cases))(move(rhs.as.Match.cases));
new (&this->as.Match.span) (decltype(this->as.Match.span))(move(rhs.as.Match.span));
new (&this->as.Match.marker_span) (decltype(this->as.Match.marker_span))(move(rhs.as.Match.marker_span));
break;
case 23 /* EnumVariantArg */:
new (&this->as.EnumVariantArg.expr) (decltype(this->as.EnumVariantArg.expr))(move(rhs.as.EnumVariantArg.expr));
new (&this->as.EnumVariantArg.arg) (decltype(this->as.EnumVariantArg.arg))(move(rhs.as.EnumVariantArg.arg));
new (&this->as.EnumVariantArg.enum_variant) (decltype(this->as.EnumVariantArg.enum_variant))(move(rhs.as.EnumVariantArg.enum_variant));
new (&this->as.EnumVariantArg.span) (decltype(this->as.EnumVariantArg.span))(move(rhs.as.EnumVariantArg.span));
break;
case 24 /* NamespacedVar */:
new (&this->as.NamespacedVar.name) (decltype(this->as.NamespacedVar.name))(move(rhs.as.NamespacedVar.name));
new (&this->as.NamespacedVar.namespace_) (decltype(this->as.NamespacedVar.namespace_))(move(rhs.as.NamespacedVar.namespace_));
new (&this->as.NamespacedVar.span) (decltype(this->as.NamespacedVar.span))(move(rhs.as.NamespacedVar.span));
break;
case 25 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(move(rhs.as.Function.captures));
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.is_fat_arrow) (decltype(this->as.Function.is_fat_arrow))(move(rhs.as.Function.is_fat_arrow));
new (&this->as.Function.return_type) (decltype(this->as.Function.return_type))(move(rhs.as.Function.return_type));
new (&this->as.Function.block) (decltype(this->as.Function.block))(move(rhs.as.Function.block));
new (&this->as.Function.span) (decltype(this->as.Function.span))(move(rhs.as.Function.span));
break;
case 26 /* Must */:
new (&this->as.Must.expr) (decltype(this->as.Must.expr))(move(rhs.as.Must.expr));
new (&this->as.Must.span) (decltype(this->as.Must.span))(move(rhs.as.Must.span));
break;
case 27 /* Try */:
new (&this->as.Try.expr) (decltype(this->as.Try.expr))(move(rhs.as.Try.expr));
new (&this->as.Try.catch_block) (decltype(this->as.Try.catch_block))(move(rhs.as.Try.catch_block));
new (&this->as.Try.catch_span) (decltype(this->as.Try.catch_span))(move(rhs.as.Try.catch_span));
new (&this->as.Try.catch_name) (decltype(this->as.Try.catch_name))(move(rhs.as.Try.catch_name));
new (&this->as.Try.span) (decltype(this->as.Try.span))(move(rhs.as.Try.span));
break;
case 28 /* TryBlock */:
new (&this->as.TryBlock.stmt) (decltype(this->as.TryBlock.stmt))(move(rhs.as.TryBlock.stmt));
new (&this->as.TryBlock.error_name) (decltype(this->as.TryBlock.error_name))(move(rhs.as.TryBlock.error_name));
new (&this->as.TryBlock.error_span) (decltype(this->as.TryBlock.error_span))(move(rhs.as.TryBlock.error_span));
new (&this->as.TryBlock.catch_block) (decltype(this->as.TryBlock.catch_block))(move(rhs.as.TryBlock.catch_block));
new (&this->as.TryBlock.span) (decltype(this->as.TryBlock.span))(move(rhs.as.TryBlock.span));
break;
case 29 /* Reflect */:
new (&this->as.Reflect.type) (decltype(this->as.Reflect.type))(move(rhs.as.Reflect.type));
new (&this->as.Reflect.span) (decltype(this->as.Reflect.span))(move(rhs.as.Reflect.span));
break;
case 30 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(move(rhs.as.Garbage.value));
break;
case 31 /* Unsafe */:
new (&this->as.Unsafe.expr) (decltype(this->as.Unsafe.expr))(move(rhs.as.Unsafe.expr));
new (&this->as.Unsafe.span) (decltype(this->as.Unsafe.span))(move(rhs.as.Unsafe.span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ParsedExpression::~ParsedExpression(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ParsedExpression::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Boolean */:this->as.Boolean.span.~Span();
break;
case 1 /* NumericConstant */:this->as.NumericConstant.val.~NumericConstant();
this->as.NumericConstant.span.~Span();
break;
case 2 /* QuotedString */:this->as.QuotedString.val.~ByteString();
this->as.QuotedString.span.~Span();
break;
case 3 /* SingleQuotedString */:this->as.SingleQuotedString.val.~ByteString();
this->as.SingleQuotedString.prefix.~Optional();
this->as.SingleQuotedString.span.~Span();
break;
case 4 /* Call */:this->as.Call.call.~ParsedCall();
this->as.Call.span.~Span();
break;
case 5 /* MethodCall */:this->as.MethodCall.expr.~NonnullRefPtr();
this->as.MethodCall.call.~ParsedCall();
this->as.MethodCall.span.~Span();
break;
case 6 /* IndexedTuple */:this->as.IndexedTuple.expr.~NonnullRefPtr();
this->as.IndexedTuple.span.~Span();
break;
case 7 /* IndexedStruct */:this->as.IndexedStruct.expr.~NonnullRefPtr();
this->as.IndexedStruct.field_name.~ByteString();
this->as.IndexedStruct.span.~Span();
break;
case 8 /* ComptimeIndex */:this->as.ComptimeIndex.expr.~NonnullRefPtr();
this->as.ComptimeIndex.index.~NonnullRefPtr();
this->as.ComptimeIndex.span.~Span();
break;
case 9 /* Var */:this->as.Var.name.~ByteString();
this->as.Var.span.~Span();
break;
case 10 /* IndexedExpression */:this->as.IndexedExpression.base.~NonnullRefPtr();
this->as.IndexedExpression.index.~NonnullRefPtr();
this->as.IndexedExpression.span.~Span();
break;
case 11 /* UnaryOp */:this->as.UnaryOp.expr.~NonnullRefPtr();
this->as.UnaryOp.op.~UnaryOperator();
this->as.UnaryOp.span.~Span();
break;
case 12 /* BinaryOp */:this->as.BinaryOp.lhs.~NonnullRefPtr();
this->as.BinaryOp.op.~BinaryOperator();
this->as.BinaryOp.rhs.~NonnullRefPtr();
this->as.BinaryOp.span.~Span();
break;
case 13 /* Operator */:this->as.Operator.op.~BinaryOperator();
this->as.Operator.span.~Span();
break;
case 14 /* OptionalSome */:this->as.OptionalSome.expr.~NonnullRefPtr();
this->as.OptionalSome.span.~Span();
break;
case 15 /* OptionalNone */:this->as.OptionalNone.value.~Span();
break;
case 16 /* JaktArray */:this->as.JaktArray.values.~DynamicArray();
this->as.JaktArray.fill_size.~Optional();
this->as.JaktArray.span.~Span();
break;
case 17 /* JaktDictionary */:this->as.JaktDictionary.values.~DynamicArray();
this->as.JaktDictionary.span.~Span();
break;
case 18 /* Set */:this->as.Set.values.~DynamicArray();
this->as.Set.span.~Span();
break;
case 19 /* JaktTuple */:this->as.JaktTuple.values.~DynamicArray();
this->as.JaktTuple.span.~Span();
break;
case 20 /* Range */:this->as.Range.from.~Optional();
this->as.Range.to.~Optional();
this->as.Range.span.~Span();
break;
case 21 /* ForcedUnwrap */:this->as.ForcedUnwrap.expr.~NonnullRefPtr();
this->as.ForcedUnwrap.span.~Span();
break;
case 22 /* Match */:this->as.Match.expr.~NonnullRefPtr();
this->as.Match.cases.~DynamicArray();
this->as.Match.span.~Span();
this->as.Match.marker_span.~Span();
break;
case 23 /* EnumVariantArg */:this->as.EnumVariantArg.expr.~NonnullRefPtr();
this->as.EnumVariantArg.arg.~EnumVariantPatternArgument();
this->as.EnumVariantArg.enum_variant.~NonnullRefPtr();
this->as.EnumVariantArg.span.~Span();
break;
case 24 /* NamespacedVar */:this->as.NamespacedVar.name.~ByteString();
this->as.NamespacedVar.namespace_.~DynamicArray();
this->as.NamespacedVar.span.~Span();
break;
case 25 /* Function */:this->as.Function.captures.~DynamicArray();
this->as.Function.params.~DynamicArray();
this->as.Function.return_type.~NonnullRefPtr();
this->as.Function.block.~ParsedBlock();
this->as.Function.span.~Span();
break;
case 26 /* Must */:this->as.Must.expr.~NonnullRefPtr();
this->as.Must.span.~Span();
break;
case 27 /* Try */:this->as.Try.expr.~NonnullRefPtr();
this->as.Try.catch_block.~Optional();
this->as.Try.catch_span.~Optional();
this->as.Try.catch_name.~Optional();
this->as.Try.span.~Span();
break;
case 28 /* TryBlock */:this->as.TryBlock.stmt.~NonnullRefPtr();
this->as.TryBlock.error_name.~ByteString();
this->as.TryBlock.error_span.~Span();
this->as.TryBlock.catch_block.~ParsedBlock();
this->as.TryBlock.span.~Span();
break;
case 29 /* Reflect */:this->as.Reflect.type.~NonnullRefPtr();
this->as.Reflect.span.~Span();
break;
case 30 /* Garbage */:this->as.Garbage.value.~Span();
break;
case 31 /* Unsafe */:this->as.Unsafe.expr.~NonnullRefPtr();
this->as.Unsafe.span.~Span();
break;
}
}
utility::Span parser::ParsedExpression::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15 /* OptionalNone */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalNone;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 17 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 18 /* Set */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Set;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 20 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 21 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 22 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 23 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 24 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 25 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 28 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 30 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 31 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
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

i64 parser::ParsedExpression::precedence() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;parser::BinaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Multiply */: {
return JaktInternal::ExplicitValue(static_cast<i64>(100LL));
};/*case end*/
case 4 /* Modulo */: {
return JaktInternal::ExplicitValue(static_cast<i64>(100LL));
};/*case end*/
case 3 /* Divide */: {
return JaktInternal::ExplicitValue(static_cast<i64>(100LL));
};/*case end*/
case 0 /* Add */: {
return JaktInternal::ExplicitValue(static_cast<i64>(90LL));
};/*case end*/
case 1 /* Subtract */: {
return JaktInternal::ExplicitValue(static_cast<i64>(90LL));
};/*case end*/
case 14 /* BitwiseLeftShift */: {
return JaktInternal::ExplicitValue(static_cast<i64>(85LL));
};/*case end*/
case 15 /* BitwiseRightShift */: {
return JaktInternal::ExplicitValue(static_cast<i64>(85LL));
};/*case end*/
case 16 /* ArithmeticLeftShift */: {
return JaktInternal::ExplicitValue(static_cast<i64>(85LL));
};/*case end*/
case 17 /* ArithmeticRightShift */: {
return JaktInternal::ExplicitValue(static_cast<i64>(85LL));
};/*case end*/
case 5 /* LessThan */: {
return JaktInternal::ExplicitValue(static_cast<i64>(80LL));
};/*case end*/
case 6 /* LessThanOrEqual */: {
return JaktInternal::ExplicitValue(static_cast<i64>(80LL));
};/*case end*/
case 7 /* GreaterThan */: {
return JaktInternal::ExplicitValue(static_cast<i64>(80LL));
};/*case end*/
case 8 /* GreaterThanOrEqual */: {
return JaktInternal::ExplicitValue(static_cast<i64>(80LL));
};/*case end*/
case 9 /* Equal */: {
return JaktInternal::ExplicitValue(static_cast<i64>(80LL));
};/*case end*/
case 10 /* NotEqual */: {
return JaktInternal::ExplicitValue(static_cast<i64>(80LL));
};/*case end*/
case 11 /* BitwiseAnd */: {
return JaktInternal::ExplicitValue(static_cast<i64>(73LL));
};/*case end*/
case 12 /* BitwiseXor */: {
return JaktInternal::ExplicitValue(static_cast<i64>(72LL));
};/*case end*/
case 13 /* BitwiseOr */: {
return JaktInternal::ExplicitValue(static_cast<i64>(71LL));
};/*case end*/
case 18 /* LogicalAnd */: {
return JaktInternal::ExplicitValue(static_cast<i64>(70LL));
};/*case end*/
case 19 /* LogicalOr */: {
return JaktInternal::ExplicitValue(static_cast<i64>(69LL));
};/*case end*/
case 20 /* NoneCoalescing */: {
return JaktInternal::ExplicitValue(static_cast<i64>(69LL));
};/*case end*/
case 21 /* Assign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 22 /* BitwiseAndAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 23 /* BitwiseOrAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 24 /* BitwiseXorAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 25 /* BitwiseLeftShiftAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 26 /* BitwiseRightShiftAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 27 /* AddAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 28 /* SubtractAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 29 /* MultiplyAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 30 /* ModuloAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 31 /* DivideAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
case 32 /* NoneCoalescingAssign */: {
return JaktInternal::ExplicitValue(static_cast<i64>(50LL));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
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
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
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

bool parser::ParsedExpression::equals(NonnullRefPtr<typename parser::ParsedExpression> const rhs_expression) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& lhs_val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& rhs_val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(((lhs_val) == (rhs_val)));
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
}));
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;parser::NumericConstant const& lhs_val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;parser::NumericConstant const& rhs_val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(((((lhs_val).to_usize())) == (((rhs_val).to_usize()))));
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
}));
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& lhs_val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& rhs_val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(((lhs_val) == (rhs_val)));
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
}));
};/*case end*/
case 3 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;ByteString const& lhs_val = __jakt_match_value.val;
JaktInternal::Optional<ByteString> const& lhs_prefix = __jakt_match_value.prefix;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;ByteString const& rhs_val = __jakt_match_value.val;
JaktInternal::Optional<ByteString> const& rhs_prefix = __jakt_match_value.prefix;
return JaktInternal::ExplicitValue((((lhs_val) == (rhs_val)) && ((lhs_prefix) == (rhs_prefix))));
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
}));
};/*case end*/
case 4 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;parser::ParsedCall const& lhs_call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;parser::ParsedCall const& rhs_call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(((lhs_call).equals(rhs_call)));
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
}));
};/*case end*/
case 5 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
parser::ParsedCall const& lhs_call = __jakt_match_value.call;
bool const& lhs_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
parser::ParsedCall const& rhs_call = __jakt_match_value.call;
bool const& rhs_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(((((lhs_optional) == (rhs_optional)) && ((lhs_expr)->equals(rhs_expr))) && ((lhs_call).equals(rhs_call))));
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
}));
};/*case end*/
case 6 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
size_t const& lhs_index = __jakt_match_value.index;
bool const& lhs_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
size_t const& rhs_index = __jakt_match_value.index;
bool const& rhs_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(((((lhs_optional) == (rhs_optional)) && ((lhs_expr)->equals(rhs_expr))) && ((lhs_index) == (rhs_index))));
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
}));
};/*case end*/
case 7 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
ByteString const& lhs_field = __jakt_match_value.field_name;
bool const& lhs_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
ByteString const& rhs_field = __jakt_match_value.field_name;
bool const& rhs_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(((((lhs_optional) == (rhs_optional)) && ((lhs_expr)->equals(rhs_expr))) && ((lhs_field) == (rhs_field))));
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
}));
};/*case end*/
case 8 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
NonnullRefPtr<typename parser::ParsedExpression> const& lhs_index = __jakt_match_value.index;
bool const& lhs_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
NonnullRefPtr<typename parser::ParsedExpression> const& rhs_index = __jakt_match_value.index;
bool const& rhs_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(((((lhs_optional) == (rhs_optional)) && ((lhs_expr)->equals(rhs_expr))) && ((lhs_index)->equals(rhs_index))));
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
}));
};/*case end*/
case 9 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;ByteString const& lhs_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;ByteString const& rhs_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(((lhs_name) == (rhs_name)));
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
}));
};/*case end*/
case 10 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_base = __jakt_match_value.base;
NonnullRefPtr<typename parser::ParsedExpression> const& lhs_index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_base = __jakt_match_value.base;
NonnullRefPtr<typename parser::ParsedExpression> const& rhs_index = __jakt_match_value.index;
return JaktInternal::ExplicitValue((((lhs_base)->equals(rhs_base)) && ((lhs_index)->equals(rhs_index))));
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
}));
};/*case end*/
case 11 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
parser::UnaryOperator const& lhs_op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
parser::UnaryOperator const& rhs_op = __jakt_match_value.op;
return JaktInternal::ExplicitValue((((lhs_expr)->equals(rhs_expr)) && ((lhs_op).equals(rhs_op))));
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
}));
};/*case end*/
case 12 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& lhs_op = __jakt_match_value.op;
NonnullRefPtr<typename parser::ParsedExpression> const& lhs_rhs = __jakt_match_value.rhs;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_lhs = __jakt_match_value.lhs;
parser::BinaryOperator const& rhs_op = __jakt_match_value.op;
NonnullRefPtr<typename parser::ParsedExpression> const& rhs_rhs = __jakt_match_value.rhs;
return JaktInternal::ExplicitValue(((((lhs_lhs)->equals(rhs_lhs)) && ((lhs_op).equals(rhs_op))) && ((lhs_rhs)->equals(rhs_rhs))));
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
}));
};/*case end*/
case 13 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;parser::BinaryOperator const& lhs_op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* Operator */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Operator;parser::BinaryOperator const& rhs_op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(((lhs_op).equals(rhs_op)));
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
}));
};/*case end*/
case 14 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((lhs_expr)->equals(rhs_expr)));
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
}));
};/*case end*/
case 15 /* OptionalNone */: {
return JaktInternal::ExplicitValue(((rhs_expression)->__jakt_init_index() == 15 /* OptionalNone */));
};/*case end*/
case 16 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& lhs_values = __jakt_match_value.values;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& lhs_fill_size = __jakt_match_value.fill_size;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& rhs_values = __jakt_match_value.values;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& rhs_fill_size = __jakt_match_value.fill_size;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_120; {
if ((!(((lhs_fill_size).has_value())))){
if (((rhs_fill_size).has_value())){
return false;
}
}
else {
if ((!(((rhs_fill_size).has_value())))){
return false;
}
if ((!((((lhs_fill_size.value()))->equals((rhs_fill_size.value())))))){
return false;
}
}

__jakt_var_120 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool,bool> {
auto __jakt_enum_value = (((((lhs_values).size())) == (((rhs_values).size()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_121; {
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_values).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((lhs_values)[i]))->equals(((rhs_values)[i])))))){
return false;
}
}

}
}

__jakt_var_121 = true; goto __jakt_label_115;

}
__jakt_label_115:; __jakt_var_121.release_value(); }));
}
else {
{
return false;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_114;

}
__jakt_label_114:; __jakt_var_120.release_value(); }));
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
}));
};/*case end*/
case 17 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> const& lhs_values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,NonnullRefPtr<typename parser::ParsedExpression>>> const& rhs_values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_122; {
__jakt_var_122 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool,bool> {
auto __jakt_enum_value = (((((lhs_values).size())) == (((rhs_values).size()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_123; {
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_values).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!((((((((lhs_values)[i])).template get<0>()))->equals(((((rhs_values)[i])).template get<0>()))) && ((((((lhs_values)[i])).template get<1>()))->equals(((((rhs_values)[i])).template get<1>()))))))){
return false;
}
}

}
}

__jakt_var_123 = true; goto __jakt_label_117;

}
__jakt_label_117:; __jakt_var_123.release_value(); }));
}
else {
{
return false;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_116;

}
__jakt_label_116:; __jakt_var_122.release_value(); }));
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
}));
};/*case end*/
case 18 /* Set */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Set;JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& lhs_values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* Set */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Set;JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& rhs_values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_124; {
__jakt_var_124 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool,bool> {
auto __jakt_enum_value = (((((lhs_values).size())) == (((rhs_values).size()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_125; {
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_values).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((lhs_values)[i]))->equals(((rhs_values)[i])))))){
return false;
}
}

}
}

__jakt_var_125 = true; goto __jakt_label_119;

}
__jakt_label_119:; __jakt_var_125.release_value(); }));
}
else {
{
return false;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_118;

}
__jakt_label_118:; __jakt_var_124.release_value(); }));
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
}));
};/*case end*/
case 19 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& lhs_values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedExpression>> const& rhs_values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_126; {
__jakt_var_126 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool,bool> {
auto __jakt_enum_value = (((((lhs_values).size())) == (((rhs_values).size()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_127; {
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_values).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((lhs_values)[i]))->equals(((rhs_values)[i])))))){
return false;
}
}

}
}

__jakt_var_127 = true; goto __jakt_label_121;

}
__jakt_label_121:; __jakt_var_127.release_value(); }));
}
else {
{
return false;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_120;

}
__jakt_label_120:; __jakt_var_126.release_value(); }));
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
}));
};/*case end*/
case 20 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& lhs_from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& lhs_to = __jakt_match_value.to;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& rhs_from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> const& rhs_to = __jakt_match_value.to;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_128; {
bool equal = false;
if ((((((lhs_from).has_value())) == (((rhs_from).has_value()))) && ((((lhs_to).has_value())) == (((rhs_to).has_value()))))){
if ((((lhs_from).has_value()) && ((lhs_to).has_value()))){
(equal = ((((lhs_from.value()))->equals((rhs_from.value()))) && (((lhs_to.value()))->equals((rhs_to.value())))));
}
else {
(equal = true);
}

}
__jakt_var_128 = equal; goto __jakt_label_122;

}
__jakt_label_122:; __jakt_var_128.release_value(); }));
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
}));
};/*case end*/
case 21 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((lhs_expr)->equals(rhs_expr)));
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
}));
};/*case end*/
case 22 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<parser::ParsedMatchCase> const& lhs_cases = __jakt_match_value.cases;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<parser::ParsedMatchCase> const& rhs_cases = __jakt_match_value.cases;
{
if ((((lhs_expr)->equals(rhs_expr)) && ((((lhs_cases).size())) == (((rhs_cases).size()))))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((lhs_cases).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
bool current_case_has_match = false;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((rhs_cases).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t k = (_magic_value.value());
{
if (((((lhs_cases)[i])).equals(((rhs_cases)[k])))){
(current_case_has_match = true);
break;
}
}

}
}

if (current_case_has_match){
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
}));
};/*case end*/
case 23 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((lhs_expr)->equals(rhs_expr)));
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
}));
};/*case end*/
case 24 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;ByteString const& lhs_name = __jakt_match_value.name;
JaktInternal::DynamicArray<ByteString> const& lhs_namespace = __jakt_match_value.namespace_;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;ByteString const& rhs_name = __jakt_match_value.name;
JaktInternal::DynamicArray<ByteString> const& rhs_namespace = __jakt_match_value.namespace_;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_129; {
if (((((lhs_namespace).size())) != (((rhs_namespace).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_namespace).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((lhs_namespace)[i]),((rhs_namespace)[i]))){
return false;
}
}

}
}

__jakt_var_129 = ((lhs_name) == (rhs_name)); goto __jakt_label_123;

}
__jakt_label_123:; __jakt_var_129.release_value(); }));
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
}));
};/*case end*/
case 26 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
utility::Span const& lhs_span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
utility::Span const& rhs_span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_130; {
bool equals = (((((rhs_span).start)) == (((lhs_span).start))) && ((((rhs_span).end)) == (((lhs_span).end))));
if ((!(equals))){
(equals = ((lhs_expr)->equals(rhs_expr)));
}
__jakt_var_130 = equals; goto __jakt_label_124;

}
__jakt_label_124:; __jakt_var_130.release_value(); }));
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
}));
};/*case end*/
case 27 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;NonnullRefPtr<typename parser::ParsedExpression> const& lhs_expr = __jakt_match_value.expr;
JaktInternal::Optional<parser::ParsedBlock> const& lhs_catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
JaktInternal::Optional<parser::ParsedBlock> const& rhs_catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_131; {
bool equals = ((lhs_expr)->equals(rhs_expr));
if (equals){
if (((lhs_catch_block).has_value())){
if (((rhs_catch_block).has_value())){
(equals = (((lhs_catch_block.value())).equals((rhs_catch_block.value()))));
}
else {
(equals = false);
}

}
else {
(equals = (!(((rhs_catch_block).has_value()))));
}

}
__jakt_var_131 = equals; goto __jakt_label_125;

}
__jakt_label_125:; __jakt_var_131.release_value(); }));
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
}));
};/*case end*/
case 28 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename parser::ParsedStatement> const& lhs_stmt = __jakt_match_value.stmt;
ByteString const& lhs_error_name = __jakt_match_value.error_name;
parser::ParsedBlock const& lhs_catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename parser::ParsedStatement> const& rhs_stmt = __jakt_match_value.stmt;
ByteString const& rhs_error_name = __jakt_match_value.error_name;
parser::ParsedBlock const& rhs_catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(((((lhs_stmt)->equals(rhs_stmt)) && ((lhs_error_name) == (rhs_error_name))) && ((lhs_catch_block).equals(rhs_catch_block))));
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
}));
};/*case end*/
case 25 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<parser::ParsedCapture> const& lhs_captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<parser::ParsedParameter> const& lhs_params = __jakt_match_value.params;
bool const& lhs_can_throw = __jakt_match_value.can_throw;
NonnullRefPtr<typename parser::ParsedType> const& lhs_return_type = __jakt_match_value.return_type;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<parser::ParsedCapture> const& rhs_captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<parser::ParsedParameter> const& rhs_params = __jakt_match_value.params;
bool const& rhs_can_throw = __jakt_match_value.can_throw;
NonnullRefPtr<typename parser::ParsedType> const& rhs_return_type = __jakt_match_value.return_type;
{
if ((((lhs_return_type)->equals(rhs_return_type)) && (((lhs_can_throw) == (rhs_can_throw)) && (((((lhs_captures).size())) == (((rhs_captures).size()))) && ((((lhs_params).size())) == (((rhs_params).size()))))))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((lhs_captures).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((((lhs_captures)[i])).common.init_common.name)) == (((((rhs_captures)[i])).common.init_common.name)))))){
return false;
}
}

}
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
if ((!(((((lhs_params)[i])).equals(((rhs_params)[i])))))){
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
}));
};/*case end*/
case 29 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;NonnullRefPtr<typename parser::ParsedType> const& type = __jakt_match_value.type;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 29 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;NonnullRefPtr<typename parser::ParsedType> const& rhs_type = __jakt_match_value.type;
return JaktInternal::ExplicitValue(((type)->equals(rhs_type)));
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
}));
};/*case end*/
case 30 /* Garbage */: {
return JaktInternal::ExplicitValue(((rhs_expression)->__jakt_init_index() == 30 /* Garbage */));
};/*case end*/
case 31 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 31 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->equals(rhs_expr)));
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
}));
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

ByteString parser::ParsedType::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Name */: {
builder.append("ParsedType::Name"sv);
[[maybe_unused]] auto const& that = this->as.Name;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* NamespacedName */: {
builder.append("ParsedType::NamespacedName"sv);
[[maybe_unused]] auto const& that = this->as.NamespacedName;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespaces: {}, ", that.namespaces);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", that.params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 2 /* GenericType */: {
builder.append("ParsedType::GenericType"sv);
[[maybe_unused]] auto const& that = this->as.GenericType;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}, ", that.generic_parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 3 /* JaktArray */: {
builder.append("ParsedType::JaktArray"sv);
[[maybe_unused]] auto const& that = this->as.JaktArray;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner: {}, ", that.inner);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 4 /* Dictionary */: {
builder.append("ParsedType::Dictionary"sv);
[[maybe_unused]] auto const& that = this->as.Dictionary;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("key: {}, ", that.key);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("value: {}, ", that.value);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 5 /* JaktTuple */: {
builder.append("ParsedType::JaktTuple"sv);
[[maybe_unused]] auto const& that = this->as.JaktTuple;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("types: {}, ", that.types);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 6 /* Set */: {
builder.append("ParsedType::Set"sv);
[[maybe_unused]] auto const& that = this->as.Set;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner: {}, ", that.inner);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 7 /* Optional */: {
builder.append("ParsedType::Optional"sv);
[[maybe_unused]] auto const& that = this->as.Optional;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner: {}, ", that.inner);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 8 /* Reference */: {
builder.append("ParsedType::Reference"sv);
[[maybe_unused]] auto const& that = this->as.Reference;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner: {}, ", that.inner);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 9 /* MutableReference */: {
builder.append("ParsedType::MutableReference"sv);
[[maybe_unused]] auto const& that = this->as.MutableReference;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner: {}, ", that.inner);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 10 /* RawPtr */: {
builder.append("ParsedType::RawPtr"sv);
[[maybe_unused]] auto const& that = this->as.RawPtr;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner: {}, ", that.inner);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 11 /* WeakPtr */: {
builder.append("ParsedType::WeakPtr"sv);
[[maybe_unused]] auto const& that = this->as.WeakPtr;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner: {}, ", that.inner);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 12 /* Function */: {
builder.append("ParsedType::Function"sv);
[[maybe_unused]] auto const& that = this->as.Function;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", that.params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", that.can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type: {}, ", that.return_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 13 /* Const */: {
builder.append("ParsedType::Const"sv);
[[maybe_unused]] auto const& that = this->as.Const;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 14 /* DependentType */: {
builder.append("ParsedType::DependentType"sv);
[[maybe_unused]] auto const& that = this->as.DependentType;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("base: {}, ", that.base);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 15 /* Empty */: {
return ByteString("ParsedType::Empty"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::Name(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, ByteString name, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Name.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.Name.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::NamespacedName(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, ByteString name, JaktInternal::DynamicArray<ByteString> namespaces, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> params, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.NamespacedName.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.NamespacedName.namespaces) (decltype(namespaces))(move(namespaces));
new (&__jakt_uninit_enum->as.NamespacedName.params) (decltype(params))(move(params));
new (&__jakt_uninit_enum->as.NamespacedName.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::GenericType(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, ByteString name, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> generic_parameters, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.GenericType.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.GenericType.generic_parameters) (decltype(generic_parameters))(move(generic_parameters));
new (&__jakt_uninit_enum->as.GenericType.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::JaktArray(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.JaktArray.inner) (decltype(inner))(move(inner));
new (&__jakt_uninit_enum->as.JaktArray.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::Dictionary(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> key, NonnullRefPtr<typename parser::ParsedType> value, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Dictionary.key) (decltype(key))(move(key));
new (&__jakt_uninit_enum->as.Dictionary.value) (decltype(value))(move(value));
new (&__jakt_uninit_enum->as.Dictionary.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::JaktTuple(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> types, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.JaktTuple.types) (decltype(types))(move(types));
new (&__jakt_uninit_enum->as.JaktTuple.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::Set(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Set.inner) (decltype(inner))(move(inner));
new (&__jakt_uninit_enum->as.Set.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::Optional(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Optional.inner) (decltype(inner))(move(inner));
new (&__jakt_uninit_enum->as.Optional.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::Reference(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Reference.inner) (decltype(inner))(move(inner));
new (&__jakt_uninit_enum->as.Reference.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::MutableReference(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.MutableReference.inner) (decltype(inner))(move(inner));
new (&__jakt_uninit_enum->as.MutableReference.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::RawPtr(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.RawPtr.inner) (decltype(inner))(move(inner));
new (&__jakt_uninit_enum->as.RawPtr.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::WeakPtr(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> inner, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.WeakPtr.inner) (decltype(inner))(move(inner));
new (&__jakt_uninit_enum->as.WeakPtr.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::Function(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, JaktInternal::DynamicArray<parser::ParsedParameter> params, bool can_throw, NonnullRefPtr<typename parser::ParsedType> return_type, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Function.params) (decltype(params))(move(params));
new (&__jakt_uninit_enum->as.Function.can_throw) (decltype(can_throw))(move(can_throw));
new (&__jakt_uninit_enum->as.Function.return_type) (decltype(return_type))(move(return_type));
new (&__jakt_uninit_enum->as.Function.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::Const(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedExpression> expr, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Const.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Const.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::DependentType(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers, NonnullRefPtr<typename parser::ParsedType> base, ByteString name, utility::Span span){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.DependentType.base) (decltype(base))(move(base));
new (&__jakt_uninit_enum->as.DependentType.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.DependentType.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ParsedType> ParsedType::Empty(JaktInternal::Optional<parser::ParsedTypeQualifiers> qualifiers){
NonnullRefPtr<ParsedType> __jakt_uninit_enum = adopt_ref(*new ParsedType);
__jakt_uninit_enum->__jakt_variant_index = 16;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
ParsedType& ParsedType::operator=(ParsedType const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.qualifiers = rhs.common.init_common.qualifiers;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Name */:
new (&this->as.Name.name) (decltype(this->as.Name.name))(rhs.as.Name.name);
new (&this->as.Name.span) (decltype(this->as.Name.span))(rhs.as.Name.span);
break;
case 1 /* NamespacedName */:
new (&this->as.NamespacedName.name) (decltype(this->as.NamespacedName.name))(rhs.as.NamespacedName.name);
new (&this->as.NamespacedName.namespaces) (decltype(this->as.NamespacedName.namespaces))(rhs.as.NamespacedName.namespaces);
new (&this->as.NamespacedName.params) (decltype(this->as.NamespacedName.params))(rhs.as.NamespacedName.params);
new (&this->as.NamespacedName.span) (decltype(this->as.NamespacedName.span))(rhs.as.NamespacedName.span);
break;
case 2 /* GenericType */:
new (&this->as.GenericType.name) (decltype(this->as.GenericType.name))(rhs.as.GenericType.name);
new (&this->as.GenericType.generic_parameters) (decltype(this->as.GenericType.generic_parameters))(rhs.as.GenericType.generic_parameters);
new (&this->as.GenericType.span) (decltype(this->as.GenericType.span))(rhs.as.GenericType.span);
break;
case 3 /* JaktArray */:
new (&this->as.JaktArray.inner) (decltype(this->as.JaktArray.inner))(rhs.as.JaktArray.inner);
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(rhs.as.JaktArray.span);
break;
case 4 /* Dictionary */:
new (&this->as.Dictionary.key) (decltype(this->as.Dictionary.key))(rhs.as.Dictionary.key);
new (&this->as.Dictionary.value) (decltype(this->as.Dictionary.value))(rhs.as.Dictionary.value);
new (&this->as.Dictionary.span) (decltype(this->as.Dictionary.span))(rhs.as.Dictionary.span);
break;
case 5 /* JaktTuple */:
new (&this->as.JaktTuple.types) (decltype(this->as.JaktTuple.types))(rhs.as.JaktTuple.types);
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(rhs.as.JaktTuple.span);
break;
case 6 /* Set */:
new (&this->as.Set.inner) (decltype(this->as.Set.inner))(rhs.as.Set.inner);
new (&this->as.Set.span) (decltype(this->as.Set.span))(rhs.as.Set.span);
break;
case 7 /* Optional */:
new (&this->as.Optional.inner) (decltype(this->as.Optional.inner))(rhs.as.Optional.inner);
new (&this->as.Optional.span) (decltype(this->as.Optional.span))(rhs.as.Optional.span);
break;
case 8 /* Reference */:
new (&this->as.Reference.inner) (decltype(this->as.Reference.inner))(rhs.as.Reference.inner);
new (&this->as.Reference.span) (decltype(this->as.Reference.span))(rhs.as.Reference.span);
break;
case 9 /* MutableReference */:
new (&this->as.MutableReference.inner) (decltype(this->as.MutableReference.inner))(rhs.as.MutableReference.inner);
new (&this->as.MutableReference.span) (decltype(this->as.MutableReference.span))(rhs.as.MutableReference.span);
break;
case 10 /* RawPtr */:
new (&this->as.RawPtr.inner) (decltype(this->as.RawPtr.inner))(rhs.as.RawPtr.inner);
new (&this->as.RawPtr.span) (decltype(this->as.RawPtr.span))(rhs.as.RawPtr.span);
break;
case 11 /* WeakPtr */:
new (&this->as.WeakPtr.inner) (decltype(this->as.WeakPtr.inner))(rhs.as.WeakPtr.inner);
new (&this->as.WeakPtr.span) (decltype(this->as.WeakPtr.span))(rhs.as.WeakPtr.span);
break;
case 12 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.return_type) (decltype(this->as.Function.return_type))(rhs.as.Function.return_type);
new (&this->as.Function.span) (decltype(this->as.Function.span))(rhs.as.Function.span);
break;
case 13 /* Const */:
new (&this->as.Const.expr) (decltype(this->as.Const.expr))(rhs.as.Const.expr);
new (&this->as.Const.span) (decltype(this->as.Const.span))(rhs.as.Const.span);
break;
case 14 /* DependentType */:
new (&this->as.DependentType.base) (decltype(this->as.DependentType.base))(rhs.as.DependentType.base);
new (&this->as.DependentType.name) (decltype(this->as.DependentType.name))(rhs.as.DependentType.name);
new (&this->as.DependentType.span) (decltype(this->as.DependentType.span))(rhs.as.DependentType.span);
break;
case 15 /* Empty */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Name */:
this->as.Name.name = rhs.as.Name.name;
this->as.Name.span = rhs.as.Name.span;
break;
case 1 /* NamespacedName */:
this->as.NamespacedName.name = rhs.as.NamespacedName.name;
this->as.NamespacedName.namespaces = rhs.as.NamespacedName.namespaces;
this->as.NamespacedName.params = rhs.as.NamespacedName.params;
this->as.NamespacedName.span = rhs.as.NamespacedName.span;
break;
case 2 /* GenericType */:
this->as.GenericType.name = rhs.as.GenericType.name;
this->as.GenericType.generic_parameters = rhs.as.GenericType.generic_parameters;
this->as.GenericType.span = rhs.as.GenericType.span;
break;
case 3 /* JaktArray */:
this->as.JaktArray.inner = rhs.as.JaktArray.inner;
this->as.JaktArray.span = rhs.as.JaktArray.span;
break;
case 4 /* Dictionary */:
this->as.Dictionary.key = rhs.as.Dictionary.key;
this->as.Dictionary.value = rhs.as.Dictionary.value;
this->as.Dictionary.span = rhs.as.Dictionary.span;
break;
case 5 /* JaktTuple */:
this->as.JaktTuple.types = rhs.as.JaktTuple.types;
this->as.JaktTuple.span = rhs.as.JaktTuple.span;
break;
case 6 /* Set */:
this->as.Set.inner = rhs.as.Set.inner;
this->as.Set.span = rhs.as.Set.span;
break;
case 7 /* Optional */:
this->as.Optional.inner = rhs.as.Optional.inner;
this->as.Optional.span = rhs.as.Optional.span;
break;
case 8 /* Reference */:
this->as.Reference.inner = rhs.as.Reference.inner;
this->as.Reference.span = rhs.as.Reference.span;
break;
case 9 /* MutableReference */:
this->as.MutableReference.inner = rhs.as.MutableReference.inner;
this->as.MutableReference.span = rhs.as.MutableReference.span;
break;
case 10 /* RawPtr */:
this->as.RawPtr.inner = rhs.as.RawPtr.inner;
this->as.RawPtr.span = rhs.as.RawPtr.span;
break;
case 11 /* WeakPtr */:
this->as.WeakPtr.inner = rhs.as.WeakPtr.inner;
this->as.WeakPtr.span = rhs.as.WeakPtr.span;
break;
case 12 /* Function */:
this->as.Function.params = rhs.as.Function.params;
this->as.Function.can_throw = rhs.as.Function.can_throw;
this->as.Function.return_type = rhs.as.Function.return_type;
this->as.Function.span = rhs.as.Function.span;
break;
case 13 /* Const */:
this->as.Const.expr = rhs.as.Const.expr;
this->as.Const.span = rhs.as.Const.span;
break;
case 14 /* DependentType */:
this->as.DependentType.base = rhs.as.DependentType.base;
this->as.DependentType.name = rhs.as.DependentType.name;
this->as.DependentType.span = rhs.as.DependentType.span;
break;
case 15 /* Empty */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedType::ParsedType(ParsedType const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.qualifiers) (decltype(this->common.init_common.qualifiers))(rhs.common.init_common.qualifiers);
switch (rhs.__jakt_init_index()) {
case 0 /* Name */:
new (&this->as.Name.name) (decltype(this->as.Name.name))(rhs.as.Name.name);
new (&this->as.Name.span) (decltype(this->as.Name.span))(rhs.as.Name.span);
break;
case 1 /* NamespacedName */:
new (&this->as.NamespacedName.name) (decltype(this->as.NamespacedName.name))(rhs.as.NamespacedName.name);
new (&this->as.NamespacedName.namespaces) (decltype(this->as.NamespacedName.namespaces))(rhs.as.NamespacedName.namespaces);
new (&this->as.NamespacedName.params) (decltype(this->as.NamespacedName.params))(rhs.as.NamespacedName.params);
new (&this->as.NamespacedName.span) (decltype(this->as.NamespacedName.span))(rhs.as.NamespacedName.span);
break;
case 2 /* GenericType */:
new (&this->as.GenericType.name) (decltype(this->as.GenericType.name))(rhs.as.GenericType.name);
new (&this->as.GenericType.generic_parameters) (decltype(this->as.GenericType.generic_parameters))(rhs.as.GenericType.generic_parameters);
new (&this->as.GenericType.span) (decltype(this->as.GenericType.span))(rhs.as.GenericType.span);
break;
case 3 /* JaktArray */:
new (&this->as.JaktArray.inner) (decltype(this->as.JaktArray.inner))(rhs.as.JaktArray.inner);
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(rhs.as.JaktArray.span);
break;
case 4 /* Dictionary */:
new (&this->as.Dictionary.key) (decltype(this->as.Dictionary.key))(rhs.as.Dictionary.key);
new (&this->as.Dictionary.value) (decltype(this->as.Dictionary.value))(rhs.as.Dictionary.value);
new (&this->as.Dictionary.span) (decltype(this->as.Dictionary.span))(rhs.as.Dictionary.span);
break;
case 5 /* JaktTuple */:
new (&this->as.JaktTuple.types) (decltype(this->as.JaktTuple.types))(rhs.as.JaktTuple.types);
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(rhs.as.JaktTuple.span);
break;
case 6 /* Set */:
new (&this->as.Set.inner) (decltype(this->as.Set.inner))(rhs.as.Set.inner);
new (&this->as.Set.span) (decltype(this->as.Set.span))(rhs.as.Set.span);
break;
case 7 /* Optional */:
new (&this->as.Optional.inner) (decltype(this->as.Optional.inner))(rhs.as.Optional.inner);
new (&this->as.Optional.span) (decltype(this->as.Optional.span))(rhs.as.Optional.span);
break;
case 8 /* Reference */:
new (&this->as.Reference.inner) (decltype(this->as.Reference.inner))(rhs.as.Reference.inner);
new (&this->as.Reference.span) (decltype(this->as.Reference.span))(rhs.as.Reference.span);
break;
case 9 /* MutableReference */:
new (&this->as.MutableReference.inner) (decltype(this->as.MutableReference.inner))(rhs.as.MutableReference.inner);
new (&this->as.MutableReference.span) (decltype(this->as.MutableReference.span))(rhs.as.MutableReference.span);
break;
case 10 /* RawPtr */:
new (&this->as.RawPtr.inner) (decltype(this->as.RawPtr.inner))(rhs.as.RawPtr.inner);
new (&this->as.RawPtr.span) (decltype(this->as.RawPtr.span))(rhs.as.RawPtr.span);
break;
case 11 /* WeakPtr */:
new (&this->as.WeakPtr.inner) (decltype(this->as.WeakPtr.inner))(rhs.as.WeakPtr.inner);
new (&this->as.WeakPtr.span) (decltype(this->as.WeakPtr.span))(rhs.as.WeakPtr.span);
break;
case 12 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.return_type) (decltype(this->as.Function.return_type))(rhs.as.Function.return_type);
new (&this->as.Function.span) (decltype(this->as.Function.span))(rhs.as.Function.span);
break;
case 13 /* Const */:
new (&this->as.Const.expr) (decltype(this->as.Const.expr))(rhs.as.Const.expr);
new (&this->as.Const.span) (decltype(this->as.Const.span))(rhs.as.Const.span);
break;
case 14 /* DependentType */:
new (&this->as.DependentType.base) (decltype(this->as.DependentType.base))(rhs.as.DependentType.base);
new (&this->as.DependentType.name) (decltype(this->as.DependentType.name))(rhs.as.DependentType.name);
new (&this->as.DependentType.span) (decltype(this->as.DependentType.span))(rhs.as.DependentType.span);
break;
case 15 /* Empty */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ParsedType& ParsedType::operator=(ParsedType &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.qualifiers = move(rhs.common.init_common.qualifiers);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Name */:
new (&this->as.Name.name) (decltype(this->as.Name.name))(move(rhs.as.Name.name));
new (&this->as.Name.span) (decltype(this->as.Name.span))(move(rhs.as.Name.span));
break;
case 1 /* NamespacedName */:
new (&this->as.NamespacedName.name) (decltype(this->as.NamespacedName.name))(move(rhs.as.NamespacedName.name));
new (&this->as.NamespacedName.namespaces) (decltype(this->as.NamespacedName.namespaces))(move(rhs.as.NamespacedName.namespaces));
new (&this->as.NamespacedName.params) (decltype(this->as.NamespacedName.params))(move(rhs.as.NamespacedName.params));
new (&this->as.NamespacedName.span) (decltype(this->as.NamespacedName.span))(move(rhs.as.NamespacedName.span));
break;
case 2 /* GenericType */:
new (&this->as.GenericType.name) (decltype(this->as.GenericType.name))(move(rhs.as.GenericType.name));
new (&this->as.GenericType.generic_parameters) (decltype(this->as.GenericType.generic_parameters))(move(rhs.as.GenericType.generic_parameters));
new (&this->as.GenericType.span) (decltype(this->as.GenericType.span))(move(rhs.as.GenericType.span));
break;
case 3 /* JaktArray */:
new (&this->as.JaktArray.inner) (decltype(this->as.JaktArray.inner))(move(rhs.as.JaktArray.inner));
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(move(rhs.as.JaktArray.span));
break;
case 4 /* Dictionary */:
new (&this->as.Dictionary.key) (decltype(this->as.Dictionary.key))(move(rhs.as.Dictionary.key));
new (&this->as.Dictionary.value) (decltype(this->as.Dictionary.value))(move(rhs.as.Dictionary.value));
new (&this->as.Dictionary.span) (decltype(this->as.Dictionary.span))(move(rhs.as.Dictionary.span));
break;
case 5 /* JaktTuple */:
new (&this->as.JaktTuple.types) (decltype(this->as.JaktTuple.types))(move(rhs.as.JaktTuple.types));
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(move(rhs.as.JaktTuple.span));
break;
case 6 /* Set */:
new (&this->as.Set.inner) (decltype(this->as.Set.inner))(move(rhs.as.Set.inner));
new (&this->as.Set.span) (decltype(this->as.Set.span))(move(rhs.as.Set.span));
break;
case 7 /* Optional */:
new (&this->as.Optional.inner) (decltype(this->as.Optional.inner))(move(rhs.as.Optional.inner));
new (&this->as.Optional.span) (decltype(this->as.Optional.span))(move(rhs.as.Optional.span));
break;
case 8 /* Reference */:
new (&this->as.Reference.inner) (decltype(this->as.Reference.inner))(move(rhs.as.Reference.inner));
new (&this->as.Reference.span) (decltype(this->as.Reference.span))(move(rhs.as.Reference.span));
break;
case 9 /* MutableReference */:
new (&this->as.MutableReference.inner) (decltype(this->as.MutableReference.inner))(move(rhs.as.MutableReference.inner));
new (&this->as.MutableReference.span) (decltype(this->as.MutableReference.span))(move(rhs.as.MutableReference.span));
break;
case 10 /* RawPtr */:
new (&this->as.RawPtr.inner) (decltype(this->as.RawPtr.inner))(move(rhs.as.RawPtr.inner));
new (&this->as.RawPtr.span) (decltype(this->as.RawPtr.span))(move(rhs.as.RawPtr.span));
break;
case 11 /* WeakPtr */:
new (&this->as.WeakPtr.inner) (decltype(this->as.WeakPtr.inner))(move(rhs.as.WeakPtr.inner));
new (&this->as.WeakPtr.span) (decltype(this->as.WeakPtr.span))(move(rhs.as.WeakPtr.span));
break;
case 12 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.return_type) (decltype(this->as.Function.return_type))(move(rhs.as.Function.return_type));
new (&this->as.Function.span) (decltype(this->as.Function.span))(move(rhs.as.Function.span));
break;
case 13 /* Const */:
new (&this->as.Const.expr) (decltype(this->as.Const.expr))(move(rhs.as.Const.expr));
new (&this->as.Const.span) (decltype(this->as.Const.span))(move(rhs.as.Const.span));
break;
case 14 /* DependentType */:
new (&this->as.DependentType.base) (decltype(this->as.DependentType.base))(move(rhs.as.DependentType.base));
new (&this->as.DependentType.name) (decltype(this->as.DependentType.name))(move(rhs.as.DependentType.name));
new (&this->as.DependentType.span) (decltype(this->as.DependentType.span))(move(rhs.as.DependentType.span));
break;
case 15 /* Empty */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Name */:
this->as.Name.name = move(rhs.as.Name.name);
this->as.Name.span = move(rhs.as.Name.span);
break;
case 1 /* NamespacedName */:
this->as.NamespacedName.name = move(rhs.as.NamespacedName.name);
this->as.NamespacedName.namespaces = move(rhs.as.NamespacedName.namespaces);
this->as.NamespacedName.params = move(rhs.as.NamespacedName.params);
this->as.NamespacedName.span = move(rhs.as.NamespacedName.span);
break;
case 2 /* GenericType */:
this->as.GenericType.name = move(rhs.as.GenericType.name);
this->as.GenericType.generic_parameters = move(rhs.as.GenericType.generic_parameters);
this->as.GenericType.span = move(rhs.as.GenericType.span);
break;
case 3 /* JaktArray */:
this->as.JaktArray.inner = move(rhs.as.JaktArray.inner);
this->as.JaktArray.span = move(rhs.as.JaktArray.span);
break;
case 4 /* Dictionary */:
this->as.Dictionary.key = move(rhs.as.Dictionary.key);
this->as.Dictionary.value = move(rhs.as.Dictionary.value);
this->as.Dictionary.span = move(rhs.as.Dictionary.span);
break;
case 5 /* JaktTuple */:
this->as.JaktTuple.types = move(rhs.as.JaktTuple.types);
this->as.JaktTuple.span = move(rhs.as.JaktTuple.span);
break;
case 6 /* Set */:
this->as.Set.inner = move(rhs.as.Set.inner);
this->as.Set.span = move(rhs.as.Set.span);
break;
case 7 /* Optional */:
this->as.Optional.inner = move(rhs.as.Optional.inner);
this->as.Optional.span = move(rhs.as.Optional.span);
break;
case 8 /* Reference */:
this->as.Reference.inner = move(rhs.as.Reference.inner);
this->as.Reference.span = move(rhs.as.Reference.span);
break;
case 9 /* MutableReference */:
this->as.MutableReference.inner = move(rhs.as.MutableReference.inner);
this->as.MutableReference.span = move(rhs.as.MutableReference.span);
break;
case 10 /* RawPtr */:
this->as.RawPtr.inner = move(rhs.as.RawPtr.inner);
this->as.RawPtr.span = move(rhs.as.RawPtr.span);
break;
case 11 /* WeakPtr */:
this->as.WeakPtr.inner = move(rhs.as.WeakPtr.inner);
this->as.WeakPtr.span = move(rhs.as.WeakPtr.span);
break;
case 12 /* Function */:
this->as.Function.params = move(rhs.as.Function.params);
this->as.Function.can_throw = move(rhs.as.Function.can_throw);
this->as.Function.return_type = move(rhs.as.Function.return_type);
this->as.Function.span = move(rhs.as.Function.span);
break;
case 13 /* Const */:
this->as.Const.expr = move(rhs.as.Const.expr);
this->as.Const.span = move(rhs.as.Const.span);
break;
case 14 /* DependentType */:
this->as.DependentType.base = move(rhs.as.DependentType.base);
this->as.DependentType.name = move(rhs.as.DependentType.name);
this->as.DependentType.span = move(rhs.as.DependentType.span);
break;
case 15 /* Empty */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ParsedType::ParsedType(ParsedType &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.qualifiers) (decltype(this->common.init_common.qualifiers))(move(rhs.common.init_common.qualifiers));
switch (rhs.__jakt_init_index()) {
case 0 /* Name */:
new (&this->as.Name.name) (decltype(this->as.Name.name))(move(rhs.as.Name.name));
new (&this->as.Name.span) (decltype(this->as.Name.span))(move(rhs.as.Name.span));
break;
case 1 /* NamespacedName */:
new (&this->as.NamespacedName.name) (decltype(this->as.NamespacedName.name))(move(rhs.as.NamespacedName.name));
new (&this->as.NamespacedName.namespaces) (decltype(this->as.NamespacedName.namespaces))(move(rhs.as.NamespacedName.namespaces));
new (&this->as.NamespacedName.params) (decltype(this->as.NamespacedName.params))(move(rhs.as.NamespacedName.params));
new (&this->as.NamespacedName.span) (decltype(this->as.NamespacedName.span))(move(rhs.as.NamespacedName.span));
break;
case 2 /* GenericType */:
new (&this->as.GenericType.name) (decltype(this->as.GenericType.name))(move(rhs.as.GenericType.name));
new (&this->as.GenericType.generic_parameters) (decltype(this->as.GenericType.generic_parameters))(move(rhs.as.GenericType.generic_parameters));
new (&this->as.GenericType.span) (decltype(this->as.GenericType.span))(move(rhs.as.GenericType.span));
break;
case 3 /* JaktArray */:
new (&this->as.JaktArray.inner) (decltype(this->as.JaktArray.inner))(move(rhs.as.JaktArray.inner));
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(move(rhs.as.JaktArray.span));
break;
case 4 /* Dictionary */:
new (&this->as.Dictionary.key) (decltype(this->as.Dictionary.key))(move(rhs.as.Dictionary.key));
new (&this->as.Dictionary.value) (decltype(this->as.Dictionary.value))(move(rhs.as.Dictionary.value));
new (&this->as.Dictionary.span) (decltype(this->as.Dictionary.span))(move(rhs.as.Dictionary.span));
break;
case 5 /* JaktTuple */:
new (&this->as.JaktTuple.types) (decltype(this->as.JaktTuple.types))(move(rhs.as.JaktTuple.types));
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(move(rhs.as.JaktTuple.span));
break;
case 6 /* Set */:
new (&this->as.Set.inner) (decltype(this->as.Set.inner))(move(rhs.as.Set.inner));
new (&this->as.Set.span) (decltype(this->as.Set.span))(move(rhs.as.Set.span));
break;
case 7 /* Optional */:
new (&this->as.Optional.inner) (decltype(this->as.Optional.inner))(move(rhs.as.Optional.inner));
new (&this->as.Optional.span) (decltype(this->as.Optional.span))(move(rhs.as.Optional.span));
break;
case 8 /* Reference */:
new (&this->as.Reference.inner) (decltype(this->as.Reference.inner))(move(rhs.as.Reference.inner));
new (&this->as.Reference.span) (decltype(this->as.Reference.span))(move(rhs.as.Reference.span));
break;
case 9 /* MutableReference */:
new (&this->as.MutableReference.inner) (decltype(this->as.MutableReference.inner))(move(rhs.as.MutableReference.inner));
new (&this->as.MutableReference.span) (decltype(this->as.MutableReference.span))(move(rhs.as.MutableReference.span));
break;
case 10 /* RawPtr */:
new (&this->as.RawPtr.inner) (decltype(this->as.RawPtr.inner))(move(rhs.as.RawPtr.inner));
new (&this->as.RawPtr.span) (decltype(this->as.RawPtr.span))(move(rhs.as.RawPtr.span));
break;
case 11 /* WeakPtr */:
new (&this->as.WeakPtr.inner) (decltype(this->as.WeakPtr.inner))(move(rhs.as.WeakPtr.inner));
new (&this->as.WeakPtr.span) (decltype(this->as.WeakPtr.span))(move(rhs.as.WeakPtr.span));
break;
case 12 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.return_type) (decltype(this->as.Function.return_type))(move(rhs.as.Function.return_type));
new (&this->as.Function.span) (decltype(this->as.Function.span))(move(rhs.as.Function.span));
break;
case 13 /* Const */:
new (&this->as.Const.expr) (decltype(this->as.Const.expr))(move(rhs.as.Const.expr));
new (&this->as.Const.span) (decltype(this->as.Const.span))(move(rhs.as.Const.span));
break;
case 14 /* DependentType */:
new (&this->as.DependentType.base) (decltype(this->as.DependentType.base))(move(rhs.as.DependentType.base));
new (&this->as.DependentType.name) (decltype(this->as.DependentType.name))(move(rhs.as.DependentType.name));
new (&this->as.DependentType.span) (decltype(this->as.DependentType.span))(move(rhs.as.DependentType.span));
break;
case 15 /* Empty */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ParsedType::~ParsedType(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.qualifiers.~Optional();
this->__jakt_destroy_variant(); }
void ParsedType::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Name */:this->as.Name.name.~ByteString();
this->as.Name.span.~Span();
break;
case 1 /* NamespacedName */:this->as.NamespacedName.name.~ByteString();
this->as.NamespacedName.namespaces.~DynamicArray();
this->as.NamespacedName.params.~DynamicArray();
this->as.NamespacedName.span.~Span();
break;
case 2 /* GenericType */:this->as.GenericType.name.~ByteString();
this->as.GenericType.generic_parameters.~DynamicArray();
this->as.GenericType.span.~Span();
break;
case 3 /* JaktArray */:this->as.JaktArray.inner.~NonnullRefPtr();
this->as.JaktArray.span.~Span();
break;
case 4 /* Dictionary */:this->as.Dictionary.key.~NonnullRefPtr();
this->as.Dictionary.value.~NonnullRefPtr();
this->as.Dictionary.span.~Span();
break;
case 5 /* JaktTuple */:this->as.JaktTuple.types.~DynamicArray();
this->as.JaktTuple.span.~Span();
break;
case 6 /* Set */:this->as.Set.inner.~NonnullRefPtr();
this->as.Set.span.~Span();
break;
case 7 /* Optional */:this->as.Optional.inner.~NonnullRefPtr();
this->as.Optional.span.~Span();
break;
case 8 /* Reference */:this->as.Reference.inner.~NonnullRefPtr();
this->as.Reference.span.~Span();
break;
case 9 /* MutableReference */:this->as.MutableReference.inner.~NonnullRefPtr();
this->as.MutableReference.span.~Span();
break;
case 10 /* RawPtr */:this->as.RawPtr.inner.~NonnullRefPtr();
this->as.RawPtr.span.~Span();
break;
case 11 /* WeakPtr */:this->as.WeakPtr.inner.~NonnullRefPtr();
this->as.WeakPtr.span.~Span();
break;
case 12 /* Function */:this->as.Function.params.~DynamicArray();
this->as.Function.return_type.~NonnullRefPtr();
this->as.Function.span.~Span();
break;
case 13 /* Const */:this->as.Const.expr.~NonnullRefPtr();
this->as.Const.span.~Span();
break;
case 14 /* DependentType */:this->as.DependentType.base.~NonnullRefPtr();
this->as.DependentType.name.~ByteString();
this->as.DependentType.span.~Span();
break;
case 15 /* Empty */:break;
}
}
utility::Span parser::ParsedType::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* Empty */: {
return JaktInternal::ExplicitValue(utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)));
};/*case end*/
case 0 /* Name */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Name;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* NamespacedName */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedName;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* GenericType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericType;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* Dictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dictionary;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* Set */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Set;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* Optional */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Optional;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* WeakPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WeakPtr;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* DependentType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentType;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
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

bool parser::ParsedType::equals(NonnullRefPtr<typename parser::ParsedType> const rhs_parsed_type) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* DependentType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentType;NonnullRefPtr<typename parser::ParsedType> const& base = __jakt_match_value.base;
ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* DependentType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentType;NonnullRefPtr<typename parser::ParsedType> const& rhs_base = __jakt_match_value.base;
ByteString const& rhs_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((((base)->equals(rhs_base)) && ((name) == (rhs_name))));
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
}));
};/*case end*/
case 0 /* Name */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Name;ByteString const& lhs_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Name */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Name;ByteString const& rhs_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(((lhs_name) == (rhs_name)));
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
}));
};/*case end*/
case 1 /* NamespacedName */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedName;ByteString const& lhs_name = __jakt_match_value.name;
JaktInternal::DynamicArray<ByteString> const& lhs_namespaces = __jakt_match_value.namespaces;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& lhs_params = __jakt_match_value.params;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* NamespacedName */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedName;ByteString const& rhs_name = __jakt_match_value.name;
JaktInternal::DynamicArray<ByteString> const& rhs_namespaces = __jakt_match_value.namespaces;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& rhs_params = __jakt_match_value.params;
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(lhs_name,rhs_name)){
return false;
}
if (((((lhs_namespaces).size())) != (((rhs_namespaces).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_namespaces).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t namespace_index = (_magic_value.value());
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((lhs_namespaces)[namespace_index]),((rhs_namespaces)[namespace_index]))){
return false;
}
}

}
}

if (((((lhs_params).size())) != (((rhs_params).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_params).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t param_index = (_magic_value.value());
{
if ((!(((((lhs_params)[param_index]))->equals(((rhs_params)[param_index])))))){
return false;
}
}

}
}

return true;
}
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
}));
};/*case end*/
case 2 /* GenericType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericType;ByteString const& lhs_name = __jakt_match_value.name;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& lhs_generic_parameters = __jakt_match_value.generic_parameters;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* GenericType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericType;ByteString const& rhs_name = __jakt_match_value.name;
JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& rhs_generic_parameters = __jakt_match_value.generic_parameters;
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(lhs_name,rhs_name)){
return false;
}
if (((((lhs_generic_parameters).size())) != (((rhs_generic_parameters).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_generic_parameters).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t param_index = (_magic_value.value());
{
if ((!(((((lhs_generic_parameters)[param_index]))->equals(((rhs_generic_parameters)[param_index])))))){
return false;
}
}

}
}

return true;
}
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
}));
};/*case end*/
case 3 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;NonnullRefPtr<typename parser::ParsedType> const& lhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;NonnullRefPtr<typename parser::ParsedType> const& rhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(((lhs_inner)->equals(rhs_inner)));
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
}));
};/*case end*/
case 4 /* Dictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dictionary;NonnullRefPtr<typename parser::ParsedType> const& lhs_key = __jakt_match_value.key;
NonnullRefPtr<typename parser::ParsedType> const& lhs_value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* Dictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dictionary;NonnullRefPtr<typename parser::ParsedType> const& rhs_key = __jakt_match_value.key;
NonnullRefPtr<typename parser::ParsedType> const& rhs_value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((((lhs_key)->equals(rhs_key)) && ((lhs_value)->equals(rhs_value))));
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
}));
};/*case end*/
case 5 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& lhs_types = __jakt_match_value.types;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename parser::ParsedType>> const& rhs_types = __jakt_match_value.types;
{
if (((((lhs_types).size())) != (((rhs_types).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_types).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t type_index = (_magic_value.value());
{
if ((!(((((lhs_types)[type_index]))->equals(((rhs_types)[type_index])))))){
return false;
}
}

}
}

return true;
}
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
}));
};/*case end*/
case 6 /* Set */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Set;NonnullRefPtr<typename parser::ParsedType> const& lhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* Set */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Set;NonnullRefPtr<typename parser::ParsedType> const& rhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(((lhs_inner)->equals(rhs_inner)));
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
}));
};/*case end*/
case 7 /* Optional */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Optional;NonnullRefPtr<typename parser::ParsedType> const& lhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* Optional */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Optional;NonnullRefPtr<typename parser::ParsedType> const& rhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(((lhs_inner)->equals(rhs_inner)));
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
}));
};/*case end*/
case 8 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;NonnullRefPtr<typename parser::ParsedType> const& lhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;NonnullRefPtr<typename parser::ParsedType> const& rhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(((lhs_inner)->equals(rhs_inner)));
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
}));
};/*case end*/
case 9 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;NonnullRefPtr<typename parser::ParsedType> const& lhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;NonnullRefPtr<typename parser::ParsedType> const& rhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(((lhs_inner)->equals(rhs_inner)));
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
}));
};/*case end*/
case 10 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;NonnullRefPtr<typename parser::ParsedType> const& lhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;NonnullRefPtr<typename parser::ParsedType> const& rhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(((lhs_inner)->equals(rhs_inner)));
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
}));
};/*case end*/
case 11 /* WeakPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WeakPtr;NonnullRefPtr<typename parser::ParsedType> const& lhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* WeakPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WeakPtr;NonnullRefPtr<typename parser::ParsedType> const& rhs_inner = __jakt_match_value.inner;
return JaktInternal::ExplicitValue(((lhs_inner)->equals(rhs_inner)));
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
}));
};/*case end*/
case 12 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<parser::ParsedParameter> const& lhs_params = __jakt_match_value.params;
bool const& lhs_can_throw = __jakt_match_value.can_throw;
NonnullRefPtr<typename parser::ParsedType> const& lhs_return_type = __jakt_match_value.return_type;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<parser::ParsedParameter> const& rhs_params = __jakt_match_value.params;
bool const& rhs_can_throw = __jakt_match_value.can_throw;
NonnullRefPtr<typename parser::ParsedType> const& rhs_return_type = __jakt_match_value.return_type;
{
if (((lhs_can_throw) != (rhs_can_throw))){
return false;
}
if ((!(((lhs_return_type)->equals(rhs_return_type))))){
return false;
}
if (((((lhs_params).size())) != (((rhs_params).size())))){
return false;
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((lhs_params).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t param_index = (_magic_value.value());
{
if ((!(((((lhs_params)[param_index])).equals(((rhs_params)[param_index])))))){
return false;
}
}

}
}

return true;
}
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
}));
};/*case end*/
case 15 /* Empty */: {
return JaktInternal::ExplicitValue(((rhs_parsed_type)->__jakt_init_index() == 15 /* Empty */));
};/*case end*/
case 13 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;NonnullRefPtr<typename parser::ParsedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs_parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;NonnullRefPtr<typename parser::ParsedExpression> const& rhs_expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->equals(rhs_expr)));
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
}));
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

ByteString parser::FunctionLinkage::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Internal */: {
return ByteString("FunctionLinkage::Internal"sv);
break;}
case 1 /* External */: {
return ByteString("FunctionLinkage::External"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] FunctionLinkage FunctionLinkage::Internal(){
FunctionLinkage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionLinkage FunctionLinkage::External(){
FunctionLinkage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
FunctionLinkage& FunctionLinkage::operator=(FunctionLinkage const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
FunctionLinkage::FunctionLinkage(FunctionLinkage const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
FunctionLinkage& FunctionLinkage::operator=(FunctionLinkage &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
FunctionLinkage::FunctionLinkage(FunctionLinkage &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Internal */:
break;
case 1 /* External */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
FunctionLinkage::~FunctionLinkage(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void FunctionLinkage::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Internal */:break;
case 1 /* External */:break;
}
}
ByteString parser::Visibility::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Public */: {
return ByteString("Visibility::Public"sv);
break;}
case 1 /* Private */: {
return ByteString("Visibility::Private"sv);
break;}
case 2 /* Restricted */: {
builder.append("Visibility::Restricted"sv);
[[maybe_unused]] auto const& that = this->as.Restricted;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("whitelist: {}, ", that.whitelist);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] Visibility Visibility::Public(){
Visibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] Visibility Visibility::Private(){
Visibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] Visibility Visibility::Restricted(JaktInternal::DynamicArray<parser::VisibilityRestriction> whitelist, utility::Span span){
Visibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Restricted.whitelist) (decltype(whitelist))(move(whitelist));
new (&__jakt_uninit_enum.as.Restricted.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
Visibility& Visibility::operator=(Visibility const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
new (&this->as.Restricted.whitelist) (decltype(this->as.Restricted.whitelist))(rhs.as.Restricted.whitelist);
new (&this->as.Restricted.span) (decltype(this->as.Restricted.span))(rhs.as.Restricted.span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
this->as.Restricted.whitelist = rhs.as.Restricted.whitelist;
this->as.Restricted.span = rhs.as.Restricted.span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Visibility::Visibility(Visibility const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
new (&this->as.Restricted.whitelist) (decltype(this->as.Restricted.whitelist))(rhs.as.Restricted.whitelist);
new (&this->as.Restricted.span) (decltype(this->as.Restricted.span))(rhs.as.Restricted.span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Visibility& Visibility::operator=(Visibility &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
new (&this->as.Restricted.whitelist) (decltype(this->as.Restricted.whitelist))(move(rhs.as.Restricted.whitelist));
new (&this->as.Restricted.span) (decltype(this->as.Restricted.span))(move(rhs.as.Restricted.span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
this->as.Restricted.whitelist = move(rhs.as.Restricted.whitelist);
this->as.Restricted.span = move(rhs.as.Restricted.span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Visibility::Visibility(Visibility &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
new (&this->as.Restricted.whitelist) (decltype(this->as.Restricted.whitelist))(move(rhs.as.Restricted.whitelist));
new (&this->as.Restricted.span) (decltype(this->as.Restricted.span))(move(rhs.as.Restricted.span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Visibility::~Visibility(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void Visibility::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Public */:break;
case 1 /* Private */:break;
case 2 /* Restricted */:this->as.Restricted.whitelist.~DynamicArray();
this->as.Restricted.span.~Span();
break;
}
}
}
} // namespace Jakt
