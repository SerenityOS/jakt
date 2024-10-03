#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "typechecker.h"
#include "jakt__file_iterator.h"
#include "jakt__prelude__string.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace typechecker {
ErrorOr<JaktInternal::Dictionary<ByteString,ByteString>> defines_from(JaktInternal::DynamicArray<Jakt::parser::IncludeAction> const actions) {
{
JaktInternal::Dictionary<ByteString,ByteString> defines = Dictionary<ByteString, ByteString>::create_with_entries({});
{
JaktInternal::ArrayIterator<Jakt::parser::IncludeAction> _magic = actions.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::IncludeAction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::IncludeAction action = _magic_value.value();
{
Jakt::parser::IncludeAction __jakt_tmp378 = action;
if (__jakt_tmp378.__jakt_init_index() == 0 /* Define */){
ByteString const name = __jakt_tmp378.as.Define.name;
ByteString const value = __jakt_tmp378.as.Define.value;
defines.set(name,value);
}
}

}
}

return defines;
}
}

ErrorOr<void> dump_scope(Jakt::ids::ScopeId const scope_id,NonnullRefPtr<Jakt::types::CheckedProgram> const& program,i64 const indent) {
{
NonnullRefPtr<Jakt::types::Scope> scope = program->get_scope(scope_id);
warnln(StringView::from_string_literal("{: >{}}Scope (ns={}) {}"sv),ByteString::from_utf8_without_validation(""sv),indent,scope->namespace_name,scope->debug_name);
i64 const cindent = JaktInternal::checked_add(indent,static_cast<i64>(2LL));
warnln(StringView::from_string_literal("{: >{}}Types:"sv),ByteString::from_utf8_without_validation(""sv),cindent);
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::TypeId> _magic = scope->types.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::TypeId> name__type_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::TypeId> const jakt__name__type_id__ = name__type_id__;
ByteString const name = jakt__name__type_id__.template get<0>();
Jakt::ids::TypeId const type_id = jakt__name__type_id__.template get<1>();

NonnullRefPtr<typename Jakt::types::Type> const type = program->get_type(type_id);
warnln(StringView::from_string_literal("{: >{}}{}: {}"sv),ByteString::from_utf8_without_validation(""sv),JaktInternal::checked_add(cindent,static_cast<i64>(2LL)),name,TRY((program->type_name(type_id,true))));
}

}
}

warnln(StringView::from_string_literal("{: >{}}Specializations:"sv),ByteString::from_utf8_without_validation(""sv),cindent);
{
JaktInternal::DictionaryIterator<ByteString,Jakt::types::SpecializedType> _magic = scope->explicitly_specialized_types.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::types::SpecializedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::types::SpecializedType> name__type__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::types::SpecializedType> const jakt__name__type__ = name__type__;
ByteString const name = jakt__name__type__.template get<0>();
Jakt::types::SpecializedType const type = jakt__name__type__.template get<1>();

ByteString const type_name = TRY((program->type_name(type.type_id,true)));
ByteString args = ByteString::from_utf8_without_validation(""sv);
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = type.arguments.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
args = ((args + TRY((program->type_name(arg,true)))) + ByteString::from_utf8_without_validation(", "sv));
}

}
}

warnln(StringView::from_string_literal("{: >{}}{}<{}> = {}"sv),ByteString::from_utf8_without_validation(""sv),JaktInternal::checked_add(cindent,static_cast<i64>(2LL)),name,args,type_name);
}

}
}

warnln(StringView::from_string_literal("{: >{}}Variables:"sv),ByteString::from_utf8_without_validation(""sv),cindent);
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::VarId> _magic = scope->vars.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::VarId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::VarId> name__var_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::VarId> const jakt__name__var_id__ = name__var_id__;
ByteString const name = jakt__name__var_id__.template get<0>();
Jakt::ids::VarId const var_id = jakt__name__var_id__.template get<1>();

NonnullRefPtr<Jakt::types::CheckedVariable> const var = program->get_variable(var_id);
warnln(StringView::from_string_literal("{: >{}}{}: {}"sv),ByteString::from_utf8_without_validation(""sv),JaktInternal::checked_add(cindent,static_cast<i64>(2LL)),name,TRY((program->type_name(var->type_id,true))));
}

}
}

warnln(StringView::from_string_literal("{: >{}}Functions:"sv),ByteString::from_utf8_without_validation(""sv),cindent);
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = scope->functions.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> name__ids__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const jakt__name__ids__ = name__ids__;
ByteString const name = jakt__name__ids__.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const ids = jakt__name__ids__.template get<1>();

warnln(StringView::from_string_literal("{: >{}}{}:"sv),ByteString::from_utf8_without_validation(""sv),JaktInternal::checked_add(cindent,static_cast<i64>(2LL)),name);
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = ids.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = program->get_function(id);
ByteString args = ByteString::from_utf8_without_validation(""sv);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter arg = _magic_value.value();
{
args = ((args + TRY((program->type_name(arg.variable->type_id,true)))) + ByteString::from_utf8_without_validation(", "sv));
}

}
}

ByteString generics = ByteString::from_utf8_without_validation(""sv);
{
JaktInternal::ArrayIterator<Jakt::types::FunctionGenericParameter> _magic = function->generics->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::FunctionGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::FunctionGenericParameter generic = _magic_value.value();
{
generics = ((generics + TRY((program->type_name(generic.type_id(),true)))) + ByteString::from_utf8_without_validation(", "sv));
}

}
}

if (!generics.is_empty()){
generics = __jakt_format(StringView::from_string_literal("<{}>"sv),generics);
}
warnln(StringView::from_string_literal("{: >{}}fn{}({}) -> {}"sv),ByteString::from_utf8_without_validation(""sv),JaktInternal::checked_add(cindent,static_cast<i64>(4LL)),generics,args,TRY((program->type_name(function->return_type_id,true))));
}

}
}

}

}
}

warnln(StringView::from_string_literal("{: >{}}Structs:"sv),ByteString::from_utf8_without_validation(""sv),cindent);
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::StructId> _magic = scope->structs.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::StructId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> name__id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> const jakt__name__id__ = name__id__;
ByteString const name = jakt__name__id__.template get<0>();
Jakt::ids::StructId const id = jakt__name__id__.template get<1>();

Jakt::types::CheckedStruct const struct_ = program->get_struct(id);
warnln(StringView::from_string_literal("{: >{}}{}@{}: {}"sv),ByteString::from_utf8_without_validation(""sv),JaktInternal::checked_add(cindent,static_cast<i64>(2LL)),id.id,id.module,struct_.name);
}

}
}

warnln(StringView::from_string_literal("{: >{}}Aliases:"sv),ByteString::from_utf8_without_validation(""sv),cindent);
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::ScopeId> _magic = scope->aliases.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId> name__id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId> const jakt__name__id__ = name__id__;
ByteString const name = jakt__name__id__.template get<0>();
Jakt::ids::ScopeId const id = jakt__name__id__.template get<1>();

NonnullRefPtr<Jakt::types::Scope> const scope = program->get_scope(id);
warnln(StringView::from_string_literal("{: >{}}{}: {}"sv),ByteString::from_utf8_without_validation(""sv),JaktInternal::checked_add(cindent,static_cast<i64>(2LL)),name,scope->debug_name);
}

}
}

warnln(StringView::from_string_literal("{: >{}}Children:"sv),ByteString::from_utf8_without_validation(""sv),cindent);
{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId id = _magic_value.value();
{
TRY((Jakt::typechecker::dump_scope(id,program,JaktInternal::checked_add(cindent,static_cast<i64>(2LL)))));
}

}
}

}
return {};
}

ByteString Jakt::typechecker::TraitImplementationDescriptor::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("TraitImplementationDescriptor("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_id: {}, ", trait_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_name: \"{}\", ", trait_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("implemented_type_args: {}", implemented_type_args);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::typechecker::TraitImplementationDescriptor::TraitImplementationDescriptor(Jakt::ids::TraitId a_trait_id, ByteString a_trait_name, JaktInternal::DynamicArray<Jakt::ids::TypeId> a_implemented_type_args): trait_id(move(a_trait_id)), trait_name(move(a_trait_name)), implemented_type_args(move(a_implemented_type_args)){}

ByteString Jakt::typechecker::ImportRestrictions::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ImportRestrictions("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("functions: {}, ", functions);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("structs: {}, ", structs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enums: {}, ", enums);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("types: {}, ", types);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("traits: {}, ", traits);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespaces: {}", namespaces);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::typechecker::ImportRestrictions Jakt::typechecker::ImportRestrictions::all() {
{
return Jakt::typechecker::ImportRestrictions(true,true,true,true,true,true);
}
}

Jakt::typechecker::ImportRestrictions::ImportRestrictions(bool a_functions, bool a_structs, bool a_enums, bool a_types, bool a_traits, bool a_namespaces): functions(move(a_functions)), structs(move(a_structs)), enums(move(a_enums)), types(move(a_types)), traits(move(a_traits)), namespaces(move(a_namespaces)){}

ByteString Jakt::typechecker::Typechecker::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Typechecker("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("program: {}, ", *program);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_module_id: {}, ", current_module_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_struct_type_id: {}, ", current_struct_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_function_id: {}, ", current_function_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("break_continue_tracker: {}, ", break_continue_tracker);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_tracker: {}, ", return_tracker);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("ignore_errors: {}, ", ignore_errors);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dump_type_hints: {}, ", dump_type_hints);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("dump_try_hints: {}, ", dump_try_hints);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("lambda_count: {}, ", lambda_count);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("self_type_id: {}, ", self_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("root_module_name: \"{}\", ", root_module_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("in_comptime_function_call: {}, ", in_comptime_function_call);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("had_an_error: {}, ", had_an_error);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("cpp_import_cache: {}, ", cpp_import_cache);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("cpp_import_processor: {}, ", cpp_import_processor);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("temp_var_count: {}, ", temp_var_count);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_block: {}", current_block);
}
builder.append(")"sv);return builder.to_string(); }
JaktInternal::Tuple<bool,bool> Jakt::typechecker::Typechecker::enter_ignore_error_mode(bool const ignore_errors) {
{
bool const old_ignore_errors = this->ignore_errors;
bool const old_had_an_error = this->had_an_error;
this->ignore_errors = (ignore_errors || old_ignore_errors);
this->had_an_error = false;
return Tuple{old_ignore_errors, old_had_an_error};
}
}

void Jakt::typechecker::Typechecker::exit_ignore_error_mode(JaktInternal::Tuple<bool,bool> const snapshot) {
{
this->ignore_errors = snapshot.template get<0>();
this->had_an_error = snapshot.template get<1>();
}
}

void Jakt::typechecker::Typechecker::set_self_type_id(Jakt::ids::TypeId const type_id) {
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp80 = this->get_type(type_id);
if (__jakt_tmp80->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp80->as.Struct.value;
JaktInternal::Optional<Jakt::ids::TypeId> __jakt_tmp79 = this->get_struct(struct_id).implements_type;
if (__jakt_tmp79.has_value()){
Jakt::ids::TypeId const replacement_type_id = __jakt_tmp79.value();
this->self_type_id = replacement_type_id;
}
else {
this->self_type_id = type_id;
}

}
else {
this->self_type_id = type_id;
}

}
}

ErrorOr<ByteString> Jakt::typechecker::Typechecker::type_name(Jakt::ids::TypeId const type_id,bool const debug_mode) const {
{
Jakt::ids::TypeId id = type_id;
if ((this->program->get_type(id)->__jakt_init_index() == 30 /* Self */) && this->self_type_id.has_value()){
id = this->self_type_id.value();
}
return this->program->type_name(id,debug_mode);
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::dump_type_hint(Jakt::ids::TypeId const type_id,Jakt::utility::Span const span) const {
{
outln(StringView::from_string_literal("{{\"type\":\"hint\",\"file_id\":{},\"position\":{},\"typename\":\"{}\"}}"sv),span.file_id.id,span.end,TRY((this->type_name(type_id,false))));
}
return {};
}

void Jakt::typechecker::Typechecker::dump_try_hint(Jakt::utility::Span const span) const {
{
outln(StringView::from_string_literal("{{\"type\":\"try\",\"file_id\":{},\"position\":{}}}"sv),span.file_id.id,span.start);
}
}

ErrorOr<Jakt::typechecker::Typechecker> Jakt::typechecker::Typechecker::typecheck(NonnullRefPtr<Jakt::compiler::Compiler> compiler,Jakt::parser::ParsedNamespace const parsed_namespace) {
{
JaktInternal::Optional<Jakt::utility::FileId> const input_file = compiler->current_file;
if (!input_file.has_value()){
compiler->panic(ByteString::from_utf8_without_validation("trying to typecheck a non-existent file"sv));
}
ByteString const true_module_name = compiler->files.operator[](input_file.value().id).basename(true);
Jakt::ids::ModuleId const placeholder_module_id = Jakt::ids::ModuleId(static_cast<size_t>(0ULL));
ByteString const root_module_name = compiler->current_file_path().value().basename(true);
Jakt::typechecker::Typechecker typechecker = Jakt::typechecker::Typechecker(compiler,Jakt::types::CheckedProgram::__jakt_create(compiler,DynamicArray<NonnullRefPtr<Jakt::types::Module>>::create_with({}),Dictionary<ByteString, JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>>::create_with_entries({}),Dictionary<ByteString, Jakt::types::LoadedModule>::create_with_entries({})),placeholder_module_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::typechecker::BreakContinueLegalityTracker::None(),Jakt::typechecker::ReturnLegalityTracker::None(),false,compiler->dump_type_hints,compiler->dump_try_hints,static_cast<u64>(0ULL),Jakt::types::GenericInferences(Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({})),JaktInternal::OptionalNone(),root_module_name,false,false,Dictionary<ByteString, Jakt::ids::ScopeId>::create_with_entries({}),JaktInternal::OptionalNone(),static_cast<u64>(0ULL),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),Jakt::ids::ScopeId(Jakt::ids::ModuleId(static_cast<size_t>(18446744073709551615ULL)),static_cast<size_t>(18446744073709551615ULL)),Jakt::types::BlockControlFlow::NeverReturns(),JaktInternal::OptionalNone(),false));
TRY((typechecker.include_prelude()));
Jakt::ids::ModuleId const root_module_id = typechecker.create_module(root_module_name,true,JaktInternal::OptionalNone());
typechecker.current_module_id = root_module_id;
TRY((compiler->set_current_file(input_file.value())));
Jakt::types::LoadedModule const loaded_module = Jakt::types::LoadedModule(root_module_id,input_file.value());
typechecker.program->set_loaded_module(true_module_name,loaded_module);
Jakt::ids::ScopeId const PRELUDE_SCOPE_ID = typechecker.prelude_scope_id();
Jakt::ids::ScopeId const root_scope_id = typechecker.create_scope(PRELUDE_SCOPE_ID,false,ByteString::from_utf8_without_validation("root"sv),false);
Jakt::ids::ScopeId const main_scope_id = typechecker.create_scope(root_scope_id,false,ByteString::from_utf8_without_validation("anon(main-file)"sv),false);
NonnullRefPtr<Jakt::types::Scope> root_scope = typechecker.get_scope(root_scope_id);
root_scope->children.push(main_scope_id);
TRY((typechecker.typecheck_module_import(Jakt::parser::ParsedModuleImport(Jakt::parser::ImportName::Literal(ByteString::from_utf8_without_validation("jakt::prelude::prelude"sv),Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))),JaktInternal::OptionalNone(),Jakt::parser::ImportList::All(),false,static_cast<size_t>(0ULL)),root_scope_id)));
{
JaktInternal::DictionaryIterator<size_t,Jakt::ids::StructId> _magic = typechecker.program->modules.operator[](static_cast<i64>(0LL))->builtin_implementation_structs.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,Jakt::ids::StructId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<size_t,Jakt::ids::StructId> ___struct_id__ = _magic_value.value();
{
JaktInternal::Tuple<size_t,Jakt::ids::StructId> const jakt_____struct_id__ = ___struct_id__;
size_t const _ = jakt_____struct_id__.template get<0>();
Jakt::ids::StructId const struct_id = jakt_____struct_id__.template get<1>();

Jakt::types::CheckedStruct const struct_ = typechecker.get_struct(struct_id);
TRY((typechecker.typecheck_entity_trait_implementations_predecl(struct_.scope_id,struct_.type_id,struct_.trait_implementations,struct_.name,struct_.name_span)));
}

}
}

{
JaktInternal::DictionaryIterator<size_t,Jakt::ids::StructId> _magic = typechecker.program->modules.operator[](static_cast<i64>(0LL))->builtin_implementation_structs.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,Jakt::ids::StructId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<size_t,Jakt::ids::StructId> ___struct_id__ = _magic_value.value();
{
JaktInternal::Tuple<size_t,Jakt::ids::StructId> const jakt_____struct_id__ = ___struct_id__;
size_t const _ = jakt_____struct_id__.template get<0>();
Jakt::ids::StructId const struct_id = jakt_____struct_id__.template get<1>();

Jakt::types::CheckedStruct const struct_ = typechecker.get_struct(struct_id);
TRY((typechecker.typecheck_entity_trait_implementations(struct_.scope_id,struct_.type_id,struct_.trait_implementations,struct_.name,struct_.name_span)));
}

}
}

TRY((typechecker.typecheck_module(parsed_namespace,main_scope_id)));
return typechecker;
}
}

NonnullRefPtr<Jakt::types::CheckedFunction> Jakt::typechecker::Typechecker::get_function(Jakt::ids::FunctionId const id) const {
{
return this->program->get_function(id);
}
}

NonnullRefPtr<Jakt::types::CheckedVariable> Jakt::typechecker::Typechecker::get_variable(Jakt::ids::VarId const id) const {
{
return this->program->get_variable(id);
}
}

NonnullRefPtr<Jakt::types::CheckedTrait> Jakt::typechecker::Typechecker::get_trait(Jakt::ids::TraitId const id) const {
{
return this->program->get_trait(id);
}
}

NonnullRefPtr<typename Jakt::types::Type> Jakt::typechecker::Typechecker::get_type(Jakt::ids::TypeId const id) const {
{
return this->program->get_type(id);
}
}

Jakt::types::CheckedEnum Jakt::typechecker::Typechecker::get_enum(Jakt::ids::EnumId const id) const {
{
return this->program->get_enum(id);
}
}

Jakt::types::CheckedStruct Jakt::typechecker::Typechecker::get_struct(Jakt::ids::StructId const id) const {
{
return this->program->get_struct(id);
}
}

NonnullRefPtr<Jakt::types::Scope> Jakt::typechecker::Typechecker::get_scope(Jakt::ids::ScopeId const id) const {
{
return this->program->get_scope(id);
}
}

ErrorOr<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>>> Jakt::typechecker::Typechecker::find_var_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const var,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope_id) const {
{
return this->program->find_var_in_scope(scope_id,var,false,root_scope_id);
}
}

JaktInternal::Optional<Jakt::types::FieldRecord> Jakt::typechecker::Typechecker::lookup_struct_field(Jakt::ids::StructId const struct_id,ByteString const name) const {
{
JaktInternal::DynamicArray<Jakt::ids::StructId> chain = DynamicArray<Jakt::ids::StructId>::create_with({});
JaktInternal::Optional<Jakt::ids::StructId> current = static_cast<JaktInternal::Optional<Jakt::ids::StructId>>(struct_id);
chain.push(current.value());
while (current.has_value()){
JaktInternal::Optional<Jakt::ids::StructId> const parent = this->get_struct(current.value()).super_struct_id;
if (parent.has_value()){
chain.push(parent.value());
}
current = parent;
}
{
JaktInternal::ArrayIterator<Jakt::ids::StructId> _magic = chain.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::StructId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::StructId current_struct_id = _magic_value.value();
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = this->get_struct(current_struct_id).fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->get_variable(field->variable_id);
if (variable->name == name){
return Jakt::types::FieldRecord(current_struct_id,field->variable_id);
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

ErrorOr<JaktInternal::Optional<Jakt::types::Value>> Jakt::typechecker::Typechecker::find_comptime_binding_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name) const {
{
return this->program->find_comptime_binding_in_scope(scope_id,name,false,JaktInternal::OptionalNone());
}
}

Jakt::jakt__path::Path Jakt::typechecker::Typechecker::get_root_path() const {
{
JaktInternal::Optional<Jakt::types::LoadedModule> const root_module = this->program->get_loaded_module(this->root_module_name);
if (root_module.has_value()){
Jakt::utility::FileId const file_id = root_module.value().file_id;
return this->compiler->get_file_path(file_id).value();
}
return Jakt::jakt__path::Path::from_string(ByteString::from_utf8_without_validation("."sv));
}
}

Jakt::ids::ScopeId Jakt::typechecker::Typechecker::prelude_scope_id() const {
{
return this->program->prelude_scope_id();
}
}

Jakt::ids::ScopeId Jakt::typechecker::Typechecker::root_scope_id() const {
{
return Jakt::ids::ScopeId(Jakt::ids::ModuleId(static_cast<size_t>(1ULL)),static_cast<size_t>(0ULL));
}
}

Jakt::ids::ScopeId Jakt::typechecker::Typechecker::main_scope_id() const {
{
return Jakt::ids::ScopeId(Jakt::ids::ModuleId(static_cast<size_t>(1ULL)),static_cast<size_t>(1ULL));
}
}

NonnullRefPtr<Jakt::types::Module> Jakt::typechecker::Typechecker::current_module() const {
{
return this->program->get_module(this->current_module_id);
}
}

bool Jakt::typechecker::Typechecker::scope_can_access(Jakt::ids::ScopeId const accessor,Jakt::ids::ScopeId const accessee) const {
{
if (accessor.equals(accessee)){
return true;
}
NonnullRefPtr<Jakt::types::Scope> accessor_scope = this->get_scope(accessor);
while (accessor_scope->parent.has_value()){
Jakt::ids::ScopeId const parent = accessor_scope->parent.value();
if (parent.equals(accessee)){
return true;
}
accessor_scope = this->get_scope(parent);
}
return false;
}
}

void Jakt::typechecker::Typechecker::error(Jakt::error::JaktError const err) {
{
this->had_an_error = true;
if (!this->ignore_errors){
this->compiler->errors.push(err);
}
}
}

void Jakt::typechecker::Typechecker::error(ByteString const message,Jakt::utility::Span const span) {
{
this->error(Jakt::error::JaktError::Message(message,span));
}
}

void Jakt::typechecker::Typechecker::error_with_hint(ByteString const message,Jakt::utility::Span const span,ByteString const hint,Jakt::utility::Span const hint_span) {
{
this->error(Jakt::error::JaktError::MessageWithHint(message,span,hint,hint_span));
}
}

bool Jakt::typechecker::Typechecker::is_integer(Jakt::ids::TypeId const type_id) const {
{
return this->program->is_integer(type_id);
}
}

bool Jakt::typechecker::Typechecker::is_floating(Jakt::ids::TypeId const type_id) const {
{
return this->program->is_floating(type_id);
}
}

bool Jakt::typechecker::Typechecker::is_numeric(Jakt::ids::TypeId const type_id) const {
{
return this->program->is_numeric(type_id);
}
}

Jakt::ids::ScopeId Jakt::typechecker::Typechecker::create_scope(JaktInternal::Optional<Jakt::ids::ScopeId> const parent_scope_id,bool const can_throw,ByteString const debug_name,bool const for_block) {
{
return this->program->create_scope(parent_scope_id,can_throw,debug_name,this->current_module_id,for_block);
}
}

Jakt::ids::ModuleId Jakt::typechecker::Typechecker::create_module(ByteString const name,bool const is_root,JaktInternal::Optional<ByteString> const path) {
{
size_t const new_id = this->program->modules.size();
Jakt::ids::ModuleId const module_id = Jakt::ids::ModuleId(new_id);
NonnullRefPtr<Jakt::types::Module> const module = Jakt::types::Module::__jakt_create(module_id,name,DynamicArray<NonnullRefPtr<typename Jakt::types::Type>>::create_with({Jakt::types::Type::Void(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::Bool(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::U8(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::U16(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::U32(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::U64(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::I8(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::I16(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::I32(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::I64(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::F32(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::F64(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::Usize(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::JaktString(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::CChar(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::CInt(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::Unknown(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::Never(Jakt::parser::CheckedQualifiers(false))}),path.value_or_lazy_evaluated([&] { return this->compiler->current_file_path().value().to_string(); }),is_root,DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>>::create_with({}),DynamicArray<Jakt::types::CheckedStruct>::create_with({}),DynamicArray<Jakt::types::CheckedEnum>::create_with({}),DynamicArray<NonnullRefPtr<Jakt::types::Scope>>::create_with({}),DynamicArray<NonnullRefPtr<Jakt::types::CheckedTrait>>::create_with({}),DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>>::create_with({}),DynamicArray<Jakt::ids::ModuleId>::create_with({}),Dictionary<size_t, Jakt::ids::StructId>::create_with_entries({}));
this->program->modules.push(module);
return module_id;
}
}

ErrorOr<JaktInternal::DynamicArray<u8>> Jakt::typechecker::Typechecker::get_prelude_contents() const {
{
NonnullRefPtr<File> file = TRY((File::open_for_reading(this->compiler->prelude_path.to_string())));
return file->read_all();
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::include_prelude() {
{
ByteString const module_name = ByteString::from_utf8_without_validation("__prelude__"sv);
Jakt::jakt__path::Path const file_name = Jakt::jakt__path::Path::from_string(module_name);
JaktInternal::DynamicArray<u8> const file_contents = TRY((this->get_prelude_contents()));
JaktInternal::Optional<Jakt::utility::FileId> const old_file_id = this->compiler->current_file;
JaktInternal::DynamicArray<u8> const old_file_contents = this->compiler->current_file_contents;
ScopeGuard __jakt_var_23([&] {
{
this->compiler->current_file = old_file_id;
this->compiler->current_file_contents = old_file_contents;
}

});
Jakt::utility::FileId const file_id = this->compiler->get_file_id_or_register(file_name);
this->compiler->current_file = file_id;
this->compiler->current_file_contents = file_contents;
Jakt::ids::ModuleId const prelude_module_id = this->create_module(module_name,false,JaktInternal::OptionalNone());
this->current_module_id = prelude_module_id;
this->program->set_loaded_module(module_name,Jakt::types::LoadedModule(prelude_module_id,file_id));
Jakt::ids::ScopeId const prelude_scope_id = this->create_scope(JaktInternal::OptionalNone(),false,ByteString::from_utf8_without_validation("prelude"sv),false);
JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens = Jakt::lexer::Lexer::lex(this->compiler);
if (this->compiler->dump_lexer){
{
JaktInternal::ArrayIterator<Jakt::lexer::Token> _magic = tokens.iterator();
for (;;){
JaktInternal::Optional<Jakt::lexer::Token> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::lexer::Token token = _magic_value.value();
{
outln(StringView::from_string_literal("token: {}"sv),token);
}

}
}

}
Jakt::parser::ParsedNamespace const parsed_namespace = Jakt::parser::Parser::parse(this->compiler,tokens);
if (this->compiler->dump_parser){
outln(StringView::from_string_literal("{:#}"sv),parsed_namespace);
}
this->compiler->dbg_println(__jakt_format(StringView::from_string_literal("before typechecking parsed prelude, modules ‘{}’"sv),this->program->modules));
TRY((this->typecheck_module(parsed_namespace,prelude_scope_id)));
}
return {};
}

ErrorOr<JaktInternal::Optional<Jakt::parser::ParsedNamespace>> Jakt::typechecker::Typechecker::lex_and_parse_file_contents(Jakt::utility::FileId const file_id) {
{
JaktInternal::Tuple<JaktInternal::Optional<Jakt::utility::FileId>,JaktInternal::DynamicArray<u8>> const old_file_state = this->compiler->current_file_state();
if (!TRY((this->compiler->set_current_file(file_id)))){
return JaktInternal::OptionalNone();
}
ScopeGuard __jakt_var_24([&] {
this->compiler->restore_file_state(old_file_state);
});
JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens = Jakt::lexer::Lexer::lex(this->compiler);
if (this->compiler->dump_lexer){
{
JaktInternal::ArrayIterator<Jakt::lexer::Token> _magic = tokens.iterator();
for (;;){
JaktInternal::Optional<Jakt::lexer::Token> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::lexer::Token token = _magic_value.value();
{
outln(StringView::from_string_literal("token: {}"sv),token);
}

}
}

}
Jakt::parser::ParsedNamespace const parsed_namespace = Jakt::parser::Parser::parse(this->compiler,tokens);
if (this->compiler->dump_parser){
outln(StringView::from_string_literal("{:#}"sv),parsed_namespace);
}
return parsed_namespace;
}
}

ErrorOr<Jakt::ids::StructId> Jakt::typechecker::Typechecker::find_struct_in_prelude(ByteString const name) const {
{
return this->program->find_struct_in_prelude(name);
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::prelude_struct_type_named(ByteString const name) {
{
Jakt::ids::StructId const struct_id = TRY((this->find_struct_in_prelude(name)));
NonnullRefPtr<typename Jakt::types::Type> const type = Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id);
return this->find_or_add_type_id(type);
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::find_type_in_prelude(ByteString const name) const {
{
Jakt::ids::ScopeId const scope_id = this->prelude_scope_id();
JaktInternal::Optional<Jakt::ids::TypeId> const type_id = TRY((this->find_type_in_scope(scope_id,name)));
if (type_id.has_value()){
return type_id.value();
}
this->compiler->panic(__jakt_format(StringView::from_string_literal("internal error: {} builtin definition not found"sv),name));
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::TypeId>> Jakt::typechecker::Typechecker::unify(Jakt::ids::TypeId const lhs,Jakt::utility::Span const lhs_span,Jakt::ids::TypeId const rhs,Jakt::utility::Span const rhs_span) {
{
if (!TRY((this->check_types_for_compat(lhs,rhs,this->generic_inferences,lhs_span)))){
return JaktInternal::OptionalNone();
}
return this->substitute_typevars_in_type(lhs,this->generic_inferences);
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::unify_with_type(Jakt::ids::TypeId const found_type,JaktInternal::Optional<Jakt::ids::TypeId> const expected_type,Jakt::utility::Span const span) {
{
if (!expected_type.has_value()){
return found_type;
}
if (expected_type.value().equals(Jakt::types::unknown_type_id())){
return found_type;
}
if (TRY((this->check_types_for_compat(expected_type.value(),found_type,this->generic_inferences,span)))){
return found_type;
}
return this->substitute_typevars_in_type(found_type,this->generic_inferences);
}
}

Jakt::ids::TypeId Jakt::typechecker::Typechecker::find_or_add_type_id(NonnullRefPtr<typename Jakt::types::Type> const type) {
{
return this->program->find_or_add_type_id(type,this->current_module_id,false);
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::TypeId>> Jakt::typechecker::Typechecker::find_type_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name) const {
{
return this->program->find_type_in_scope(scope_id,name,false,JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::TraitId>> Jakt::typechecker::Typechecker::find_trait_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name) const {
{
return this->program->find_trait_in_scope(scope_id,name,false,JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::DynamicArray<Jakt::typechecker::TraitImplementationDescriptor>> Jakt::typechecker::Typechecker::find_all_trait_implementations(Jakt::ids::TypeId const type_id,JaktInternal::DynamicArray<ByteString> const trait_names,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics) {
{
JaktInternal::DynamicArray<Jakt::typechecker::TraitImplementationDescriptor> result = DynamicArray<Jakt::typechecker::TraitImplementationDescriptor>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = trait_names.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString trait_name = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TraitId> __jakt_tmp81 = TRY((this->find_trait_in_scope(scope_id,trait_name)));
if (__jakt_tmp81.has_value()){
Jakt::ids::TraitId const trait_id = __jakt_tmp81.value();
{
JaktInternal::ArrayIterator<JaktInternal::DynamicArray<Jakt::ids::TypeId>> _magic = TRY((this->find_all_implementations_of_trait(type_id,trait_id,filter_for_generics))).iterator();
for (;;){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::DynamicArray<Jakt::ids::TypeId> impl = _magic_value.value();
{
result.push(Jakt::typechecker::TraitImplementationDescriptor(trait_id,trait_name,impl));
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

return result;
}
}

ErrorOr<JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor>> Jakt::typechecker::Typechecker::find_singular_trait_implementation(Jakt::ids::TypeId const type_id,ByteString const trait_name,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics) {
{
JaktInternal::Optional<Jakt::ids::TraitId> const trait_id = TRY((this->find_trait_in_scope(scope_id,trait_name)));
if (!trait_id.has_value()){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const trait_impls = TRY((this->find_all_implementations_of_trait(type_id,trait_id.value(),filter_for_generics)));
if (trait_impls.is_empty()){
return JaktInternal::OptionalNone();
}
if (trait_impls.size() > static_cast<size_t>(1ULL)){
this->error(__jakt_format(StringView::from_string_literal("type ‘{}’ implements trait ‘{}’ more than once, but a singular implementation is allowed"sv),TRY((this->type_name(type_id,false))),trait_name),span);
}
return Jakt::typechecker::TraitImplementationDescriptor(trait_id.value(),trait_name,trait_impls.operator[](static_cast<i64>(0LL)));
}
}

ErrorOr<JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor>> Jakt::typechecker::Typechecker::find_any_singular_trait_implementation(Jakt::ids::TypeId const type_id,JaktInternal::DynamicArray<ByteString> const trait_names,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics) {
{
{
JaktInternal::ArrayIterator<ByteString> _magic = trait_names.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString trait_name = _magic_value.value();
{
JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor> const maybe_impl = TRY((this->find_singular_trait_implementation(type_id,trait_name,scope_id,span,filter_for_generics)));
if (maybe_impl.has_value()){
return maybe_impl;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>> Jakt::typechecker::Typechecker::find_type_scope(Jakt::ids::ScopeId const scope_id,ByteString const name) const {
{
return this->program->find_type_scope(scope_id,name,false,JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>> Jakt::typechecker::Typechecker::find_namespace_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const treat_aliases_as_imports,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->program->find_namespace_in_scope(scope_id,name,treat_aliases_as_imports,false,root_scope);
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::add_struct_to_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,Jakt::ids::StructId const struct_id,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
JaktInternal::Optional<Jakt::ids::StructId> const maybe_scope_id = scope->structs.get(name);
if (maybe_scope_id.has_value()){
if (this->get_scope(scope_id)->is_from_generated_code){
return false;
}
Jakt::ids::StructId const existing_struct_id = maybe_scope_id.value();
Jakt::utility::Span const definition_span = this->get_struct(existing_struct_id).name_span;
this->error_with_hint(__jakt_format(StringView::from_string_literal("redefinition of struct/class {}"sv),name),span,__jakt_format(StringView::from_string_literal("struct/class {} was first defined here"sv),name),definition_span);
return false;
}
scope->structs.set(name,struct_id);
return true;
}
}

bool Jakt::typechecker::Typechecker::add_enum_to_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,Jakt::ids::EnumId const enum_id,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
JaktInternal::Optional<Jakt::ids::EnumId> const maybe_enum_id = scope->enums.get(name);
if (maybe_enum_id.has_value()){
if (this->get_scope(scope_id)->is_from_generated_code){
return false;
}
Jakt::ids::EnumId const existing_enum_id = maybe_enum_id.value();
Jakt::utility::Span const definition_span = this->get_enum(existing_enum_id).name_span;
this->error_with_hint(__jakt_format(StringView::from_string_literal("redefinition of enum {}"sv),name),span,__jakt_format(StringView::from_string_literal("enum {} was first defined here"sv),name),definition_span);
return false;
}
scope->enums.set(name,enum_id);
return true;
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::add_type_to_scope(Jakt::ids::ScopeId const scope_id,ByteString const type_name,Jakt::ids::TypeId const type_id,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
JaktInternal::Optional<Jakt::ids::TypeId> const found_type_id = scope->types.get(type_name);
if (found_type_id.has_value() && (!found_type_id.value().equals(type_id))){
if (this->get_scope(scope_id)->is_from_generated_code){
return false;
}
this->error(__jakt_format(StringView::from_string_literal("Redefinition of type ‘{}’ (duplicate: {} in {})"sv),type_name,TRY((this->type_name(found_type_id.value(),true))),this->debug_description_of(scope_id)),span);
TRY((this->generic_inferences.debug_description(this->program)));
return false;
}
scope->types.set(type_name,type_id);
return true;
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::add_trait_to_scope(Jakt::ids::ScopeId const scope_id,ByteString const trait_name,Jakt::ids::TraitId const trait_id,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
JaktInternal::Optional<Jakt::ids::TraitId> const found_trait_id = scope->traits.get(trait_name);
if (found_trait_id.has_value() && (!found_trait_id.value().equals(trait_id))){
this->error(__jakt_format(StringView::from_string_literal("Redefinition of trait ‘{}’"sv),trait_name),span);
return false;
}
scope->traits.set(trait_name,trait_id);
return true;
}
}

bool Jakt::typechecker::Typechecker::add_function_to_scope(Jakt::ids::ScopeId const parent_scope_id,ByteString const name,JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(parent_scope_id);
if (scope->functions.contains(name)){
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const existing_function_binding = scope->functions.operator[](name);
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = overload_set.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId function_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function_to_add = this->get_function(function_id);
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = existing_function_binding.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId existing_function_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> const existing_function = this->get_function(existing_function_id);
if (function_to_add->signature_matches(existing_function,false)){
if (this->get_scope(parent_scope_id)->is_from_generated_code){
continue;
}
this->error_with_hint(__jakt_format(StringView::from_string_literal("Redefinition of function ‘{}’."sv),function_to_add->name),function_to_add->parsed_function.value().name_span,ByteString::from_utf8_without_validation("Previous definition is here"sv),existing_function->parsed_function.value().name_span);
}
}

}
}

scope->functions.operator[](name).push(function_id);
}

}
}

}
else {
scope->functions.set(name,overload_set);
}

this->program->set_owner_scope_if_needed(parent_scope_id,overload_set,span);
return true;
}
}

bool Jakt::typechecker::Typechecker::add_var_to_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,Jakt::ids::VarId const var_id,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
JaktInternal::Optional<Jakt::ids::VarId> const existing_var = scope->vars.get(name);
if (existing_var.has_value()){
NonnullRefPtr<Jakt::types::CheckedVariable> const variable_ = this->get_variable(existing_var.value());
this->error_with_hint(__jakt_format(StringView::from_string_literal("Redefinition of variable ‘{}’"sv),name),span,ByteString::from_utf8_without_validation("previous definition here"sv),variable_->definition_span);
}
scope->vars.set(name,var_id);
this->program->set_owner_scope_if_needed(scope_id,var_id);
return true;
}
}

bool Jakt::typechecker::Typechecker::add_comptime_binding_to_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,Jakt::types::Value const value,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
JaktInternal::Optional<Jakt::types::Value> const existing_binding = scope->comptime_bindings.get(name);
if (existing_binding.has_value()){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Redefinition of comptime variable ‘{}’"sv),name),span,ByteString::from_utf8_without_validation("previous definition here"sv),existing_binding.value().span);
}
scope->comptime_bindings.set(name,value);
return true;
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> Jakt::typechecker::Typechecker::find_functions_with_name_in_scope(Jakt::ids::ScopeId const parent_scope_id,ByteString const function_name,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope_id) const {
{
return this->program->find_functions_with_name_in_scope(parent_scope_id,function_name,false,root_scope_id);
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>> Jakt::typechecker::Typechecker::find_scoped_functions_with_name_in_scope(Jakt::ids::ScopeId const parent_scope_id,ByteString const function_name,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope_id) const {
{
return this->program->find_scoped_functions_with_name_in_scope(parent_scope_id,function_name,false,root_scope_id);
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> Jakt::typechecker::Typechecker::find_function_matching_signature_in_scope(Jakt::ids::ScopeId const parent_scope_id,Jakt::parser::ParsedFunction const prototype) const {
{
ByteString const function_name = prototype.name;
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const candidate_ids = TRY((this->program->find_functions_with_name_in_scope(parent_scope_id,function_name,false,JaktInternal::OptionalNone())));
if (candidate_ids.has_value()){
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = candidate_ids.value().iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId candidate_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> const candidate = this->get_function(candidate_id);
if (candidate->parsed_function.has_value() && candidate->parsed_function.value().equals(prototype,false)){
return candidate_id;
}
}

}
}

}
return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> Jakt::typechecker::Typechecker::find_function_matching_trait_implementation_in_scope(Jakt::ids::TypeId const self_type_id,Jakt::ids::ScopeId const parent_scope_id,ByteString const function_name,Jakt::typechecker::TraitImplementationDescriptor const& trait_descriptor) {
{
NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->get_trait(trait_descriptor.trait_id);
Jakt::types::CheckedTraitRequirements __jakt_tmp82 = trait_->requirements;
if (__jakt_tmp82.__jakt_init_index() == 1 /* Methods */){
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const methods = __jakt_tmp82.as.Methods.value;
if (methods.contains(function_name)){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> __jakt_tmp83 = TRY((this->program->find_functions_with_name_in_scope(parent_scope_id,function_name,false,JaktInternal::OptionalNone())));
if (__jakt_tmp83.has_value()){
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const candidate_ids = __jakt_tmp83.value();
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(true);
ScopeGuard __jakt_var_25([&] {
{
this->generic_inferences.restore(old_generic_inferences);
}

});
this->generic_inferences.set_all(trait_->generic_parameters,trait_descriptor.implemented_type_args);
NonnullRefPtr<Jakt::types::CheckedFunction> const expected_function = this->get_function(methods.operator[](function_name));
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = candidate_ids.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId candidate_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> const candidate = this->get_function(candidate_id);
if (TRY((this->signatures_match(self_type_id,candidate,expected_function))).template get<0>()){
return candidate_id;
}
}

}
}

return JaktInternal::OptionalNone();
}
else {
return JaktInternal::OptionalNone();
}

}
else {
return JaktInternal::OptionalNone();
}

}
else {
return JaktInternal::OptionalNone();
}

}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::StructId>> Jakt::typechecker::Typechecker::find_struct_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->program->find_struct_in_scope(scope_id,name,false,root_scope);
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::unwrap_type_id_from_optional_if_needed(Jakt::ids::TypeId const type_id) const {
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp84 = this->get_type(type_id);
if (__jakt_tmp84->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp84->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp84->as.GenericInstance.args;
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
if (id.equals(optional_struct_id)){
return args.operator[](static_cast<i64>(0LL));
}
}
return type_id;
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::Type>> Jakt::typechecker::Typechecker::unwrap_type_from_optional_if_needed(NonnullRefPtr<typename Jakt::types::Type> const type) const {
{
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp85 = type;
if (__jakt_tmp85->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp85->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp85->as.GenericInstance.args;
if (id.equals(optional_struct_id)){
return this->get_type(args.operator[](static_cast<i64>(0LL)));
}
}
return type;
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>>> Jakt::typechecker::Typechecker::get_type_ids_from_type_hint_if_struct_ids_match(Jakt::ids::TypeId const type_hint_id,Jakt::ids::StructId const expected_struct_id) const {
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp86 = TRY((this->unwrap_type_from_optional_if_needed(this->get_type(type_hint_id))));
if (__jakt_tmp86->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp86->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp86->as.GenericInstance.args;
if (id.equals(expected_struct_id)){
return args;
}
}
return JaktInternal::OptionalNone();
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_module(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id) {
{
TRY((this->typecheck_namespace_imports(parsed_namespace,scope_id)));
TRY((this->typecheck_namespace_predecl(parsed_namespace,scope_id)));
TRY((this->typecheck_namespace_methods_predecl(parsed_namespace,scope_id,true,false)));
TRY((this->typecheck_namespace_methods_predecl(parsed_namespace,scope_id,false,false)));
TRY((this->typecheck_namespace_methods_predecl(parsed_namespace,scope_id,true,true)));
TRY((this->typecheck_namespace_methods_predecl(parsed_namespace,scope_id,false,true)));
TRY((this->typecheck_namespace_aliases(parsed_namespace,scope_id,Jakt::typechecker::ImportRestrictions(false,true,true,true,true,true))));
TRY((this->typecheck_namespace_fields(parsed_namespace,scope_id)));
TRY((this->typecheck_namespace_constructors(parsed_namespace,scope_id)));
TRY((this->typecheck_namespace_function_predecl(parsed_namespace,scope_id,true,false)));
TRY((this->typecheck_namespace_function_predecl(parsed_namespace,scope_id,false,false)));
TRY((this->typecheck_namespace_function_predecl(parsed_namespace,scope_id,true,true)));
TRY((this->typecheck_namespace_function_predecl(parsed_namespace,scope_id,false,true)));
TRY((this->typecheck_namespace_aliases(parsed_namespace,scope_id,Jakt::typechecker::ImportRestrictions(true,false,false,false,false,false))));
TRY((this->typecheck_namespace_declarations(parsed_namespace,scope_id,true,false)));
TRY((this->typecheck_namespace_declarations(parsed_namespace,scope_id,true,true)));
TRY((this->typecheck_namespace_declarations(parsed_namespace,scope_id,false,false)));
TRY((this->typecheck_namespace_declarations(parsed_namespace,scope_id,false,true)));
this->collect_exports(parsed_namespace,scope_id);
}
return {};
}

void Jakt::typechecker::Typechecker::collect_exports(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id) {
{
NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> const parent_scope = Jakt::types::MaybeResolvedScope::Resolved(scope_id);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedExport> _magic = parsed_namespace.exports.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedExport> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedExport exp = _magic_value.value();
{
JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>> exported_types = Dictionary<Jakt::ids::TypeId, JaktInternal::DynamicArray<Jakt::parser::ParsedName>>::create_with_entries({});
JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> __jakt_tmp87 = this->program->exports.get(exp.file.name);
if (__jakt_tmp87.has_value()){
JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>> const exported = __jakt_tmp87.value();
exported_types = exported;
}
{
JaktInternal::ArrayIterator<JaktInternal::DynamicArray<Jakt::parser::ParsedName>> _magic = exp.names.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedName>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::DynamicArray<Jakt::parser::ParsedName> name_list = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::ScopeId> parent_scope = scope_id;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_sub(name_list.size(),static_cast<size_t>(1ULL)))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::ScopeId> const found_scope = this->program->find_namespace_in_immediate_children_of_scope(parent_scope.value(),name_list.operator[](i).name,false);
JaktInternal::Optional<Jakt::ids::ScopeId> __jakt_tmp88 = found_scope;
if (__jakt_tmp88.has_value()){
Jakt::ids::ScopeId const scope_id = __jakt_tmp88.value();
parent_scope = scope_id;
}
else {
this->error(__jakt_format(StringView::from_string_literal("Cannot find scope for ‘{}‘"sv),name_list.operator[](i).name),name_list.operator[](i).span);
parent_scope = JaktInternal::OptionalNone();
break;
}

}

}
}

JaktInternal::Optional<Jakt::ids::ScopeId> __jakt_tmp89 = parent_scope;
if (__jakt_tmp89.has_value()){
Jakt::ids::ScopeId const search_scope = __jakt_tmp89.value();
Jakt::parser::ParsedName const type_name = name_list.last().value();
JaktInternal::Optional<Jakt::ids::TypeId> const found_type = MUST((this->program->find_type_in_scope(search_scope,type_name.name,false,JaktInternal::OptionalNone())));
JaktInternal::Optional<Jakt::ids::TypeId> __jakt_tmp90 = found_type;
if (__jakt_tmp90.has_value()){
Jakt::ids::TypeId const exported_type = __jakt_tmp90.value();
exported_types.set(exported_type,name_list);
}
else {
this->error(__jakt_format(StringView::from_string_literal("Cannot find exported type ‘{}‘"sv),type_name.name),type_name.span);
continue;
}

}
else {
continue;
}

}

}
}

this->program->exports.set(exp.file.name,exported_types);
}

}
}

}
}

ErrorOr<Jakt::types::CheckedVisibility> Jakt::typechecker::Typechecker::typecheck_visibility(Jakt::parser::Visibility const visibility,Jakt::ids::ScopeId const scope_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedVisibility, ErrorOr<Jakt::types::CheckedVisibility>>{
auto&& __jakt_match_variant = visibility;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Private */:return JaktInternal::ExplicitValue(Jakt::types::CheckedVisibility::Private());
case 0 /* Public */:return JaktInternal::ExplicitValue(Jakt::types::CheckedVisibility::Public());
case 2 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;JaktInternal::DynamicArray<Jakt::parser::VisibilityRestriction> const& whitelist = __jakt_match_value.whitelist;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> restricted_scopes = DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::parser::VisibilityRestriction> _magic = whitelist.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::VisibilityRestriction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::VisibilityRestriction entry = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> parent_scope = Jakt::types::MaybeResolvedScope::Resolved(scope_id);
{
JaktInternal::ArrayIterator<ByteString> _magic = entry.namespace_.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString ns = _magic_value.value();
{
parent_scope = Jakt::types::MaybeResolvedScope::Unresolved(parent_scope,ns);
}

}
}

NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> unresolved = Jakt::types::MaybeResolvedScope::Unresolved(parent_scope,entry.name);
restricted_scopes.push(TRY((unresolved->try_resolve(this->program))));
}

}
}

return JaktInternal::ExplicitValue<Jakt::types::CheckedVisibility>(Jakt::types::CheckedVisibility::Restricted(restricted_scopes,span));
}
VERIFY_NOT_REACHED();
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

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_fields(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id) {
{
JaktInternal::DynamicArray<Jakt::ids::ScopeId> const children = this->get_scope(scope_id)->children;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parsed_namespace.namespaces.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::parser::ParsedNamespace const child_namespace = parsed_namespace.namespaces.operator[](i);
Jakt::ids::ScopeId const child_namespace_scope_id = children.operator[](i);
TRY((this->typecheck_namespace_fields(child_namespace,child_namespace_scope_id)));
}

}
}

JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> __jakt_tmp91 = this->get_scope(scope_id)->resolved_forall_chunks;
if (__jakt_tmp91.has_value()){
JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk> const chunks = __jakt_tmp91.value();
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedForallChunk> _magic = chunks.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedForallChunk> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolvedForallChunk chunk = _magic_value.value();
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> all_types = Jakt::typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create(chunk.parameters);
size_t i = static_cast<size_t>(0ULL);
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = all_types;
for (;;){
JaktInternal::Optional<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> stuff = _magic_value.value();
{
ScopeGuard __jakt_var_26([&] {
i += static_cast<size_t>(1ULL);
});
TRY((this->typecheck_namespace_fields(chunk.parsed_namespace,chunk.generated_scopes.operator[](i))));
}

}
}

}

}
}

}
AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>> records_to_process = AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>>();
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_namespace.records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord parsed_record = _magic_value.value();
{
records_to_process.enqueue(Tuple{parsed_record, scope_id});
}

}
}

while (!records_to_process.is_empty()){
JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId> const record_scope_id_ = records_to_process.dequeue();
Jakt::parser::ParsedRecord const record = record_scope_id_.template get<0>();
Jakt::ids::ScopeId const scope_id = record_scope_id_.template get<1>();

Jakt::types::StructLikeId const id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::StructLikeId, ErrorOr<void>>{
auto&& __jakt_match_variant = record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */:case 1 /* Class */:{
JaktInternal::Optional<Jakt::ids::StructId> const struct_id = TRY((this->find_struct_in_scope(scope_id,record.name,JaktInternal::OptionalNone())));
if (!struct_id.has_value()){
this->compiler->panic(ByteString::from_utf8_without_validation("can't find previously added struct"sv));
}
TRY((this->typecheck_struct_fields(record,struct_id.value())));
return JaktInternal::ExplicitValue<Jakt::types::StructLikeId>(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id.value()));
}
VERIFY_NOT_REACHED();
case 2 /* ValueEnum */:case 3 /* SumEnum */:{
JaktInternal::Optional<Jakt::ids::EnumId> const enum_id = TRY((this->program->find_enum_in_scope(scope_id,record.name,false,JaktInternal::OptionalNone())));
if (!enum_id.has_value()){
this->compiler->panic(ByteString::from_utf8_without_validation("can't find previously added enum"sv));
}
return JaktInternal::ExplicitValue<Jakt::types::StructLikeId>(Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id.value()));
}
VERIFY_NOT_REACHED();
default:{
return JaktInternal::LoopContinue{};
}
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
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = record.nested_records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord nested_record = _magic_value.value();
{
TRY((this->warn_about_unimplemented_nested_record(nested_record)));
records_to_process.enqueue(Tuple{nested_record, id.scope_id(this->program)});
}

}
}

}
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::warn_about_unimplemented_nested_record(Jakt::parser::ParsedRecord const record) {
{
if (record.definition_linkage.__jakt_init_index() == 0 /* Internal */){
this->error(ByteString::from_utf8_without_validation("Only external nested types are currently supported"sv),record.name_span);
}
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_struct_fields(Jakt::parser::ParsedRecord const record,Jakt::ids::StructId const struct_id) {
{
Jakt::types::CheckedStruct structure = this->get_struct(struct_id);
Jakt::ids::ScopeId const checked_struct_scope_id = this->get_struct(struct_id).scope_id;
Jakt::ids::TypeId const struct_type_id = this->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id));
this->current_struct_type_id = struct_type_id;
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(struct_type_id);
ScopeGuard __jakt_var_27([&] {
this->self_type_id = old_self_type_id;
});
JaktInternal::DynamicArray<Jakt::parser::ParsedField> const parsed_fields = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::parser::ParsedField>, ErrorOr<void>>{
auto&& __jakt_match_variant = record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
case 1 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<Jakt::parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
default:{
this->compiler->panic(ByteString::from_utf8_without_validation("typecheck_struct_fields cannot handle non-structs"sv));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool const in_generated_code = this->get_scope(structure.scope_id)->is_from_generated_code;
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedField> _magic = parsed_fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedField> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedField unchecked_member = _magic_value.value();
{
Jakt::parser::ParsedVarDecl const parsed_var_decl = unchecked_member.var_decl;
Jakt::ids::TypeId const checked_member_type = TRY((this->typecheck_typename(parsed_var_decl.parsed_type,checked_struct_scope_id,parsed_var_decl.name,JaktInternal::OptionalNone())));
if (!in_generated_code){
TRY((this->check_that_type_doesnt_contain_reference(checked_member_type,parsed_var_decl.parsed_type->span())));
}
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::VarId const variable_id = module->add_variable(Jakt::types::CheckedVariable::__jakt_create(parsed_var_decl.name,checked_member_type,parsed_var_decl.is_mutable,parsed_var_decl.span,JaktInternal::OptionalNone(),TRY((this->typecheck_visibility(unchecked_member.visibility,checked_struct_scope_id))),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),parsed_var_decl.external_name));
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> const default_value_expression = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>,ErrorOr<void>> {
auto __jakt_enum_value = (unchecked_member.default_value.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>(Tuple{unchecked_member.default_value.value(), checked_struct_scope_id}));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
structure.fields.push(Jakt::types::CheckedField::__jakt_create(variable_id,default_value_expression,JaktInternal::OptionalNone()));
}

}
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_module_import(Jakt::parser::ParsedModuleImport const import_,Jakt::ids::ScopeId const scope_id) {
{
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>> const module_names_and_spans = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = import_.module_name;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Literal */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Literal;ByteString const& name = __jakt_match_value.name;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>>(DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>::create_with({Tuple{name, span}})));
};/*case end*/
case 1 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expression = __jakt_match_value.expression;
{
NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter = this->interpreter();
NonnullRefPtr<Jakt::interpreter::InterpreterScope> eval_scope = Jakt::interpreter::InterpreterScope::from_runtime_scope(scope_id,this->program,JaktInternal::OptionalNone());
Jakt::ids::ScopeId const exec_scope = this->create_scope(scope_id,true,ByteString::from_utf8_without_validation("comptime-import"sv),true);
Jakt::interpreter::StatementResult const result = TRY((interpreter->execute_expression(TRY((this->typecheck_expression(expression,exec_scope,Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone()))),eval_scope)));
return JaktInternal::ExplicitValue<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */:case 2 /* Yield */:case 3 /* Continue */:case 4 /* Break */:{
this->error_with_hint(ByteString::from_utf8_without_validation("module name must evaluate to a string literal or an array of strings"sv),expression->span(),ByteString::from_utf8_without_validation("this expression evaluates to an invalid value"sv),expression->span());
return JaktInternal::ExplicitValue<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>>(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& error = __jakt_match_value.value;
{
this->error_with_hint(ByteString::from_utf8_without_validation("module name must evaluate to a string literal or an array of strings"sv),expression->span(),__jakt_format(StringView::from_string_literal("this expression threw an error: {}"sv),error),expression->span());
return JaktInternal::ExplicitValue<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>>(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>, ErrorOr<void>>{
auto&& __jakt_match_variant = *value.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& string = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>>(DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>::create_with({Tuple{string, value.span}})));
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
if (values.is_empty()){
this->error_with_hint(ByteString::from_utf8_without_validation("module name must evaluate to a string literal or an array of strings"sv),expression->span(),ByteString::from_utf8_without_validation("this expression evaluates to an empty array"sv),expression->span());
}
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> result = DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = values.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value value = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *value.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& string = __jakt_match_value.value;
return ({result.push(Tuple{string, value.span});}), JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
this->error_with_hint(ByteString::from_utf8_without_validation("module name must evaluate to a string literal or an array of strings"sv),value.span,ByteString::from_utf8_without_validation("this expression evaluates to an invalid value"sv),value.span);
}
return JaktInternal::ExplicitValue<void>();
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

return JaktInternal::ExplicitValue<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>>(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>>(result));
}
VERIFY_NOT_REACHED();
};/*case end*/
default:{
this->error_with_hint(ByteString::from_utf8_without_validation("module name must evaluate to a string literal"sv),expression->span(),ByteString::from_utf8_without_validation("this expression evaluates to a non-string value"sv),expression->span());
return JaktInternal::ExplicitValue<JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>>>(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
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
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (!module_names_and_spans.has_value()){
return {};
}
size_t const parent_path_count = import_.parent_path_count;
bool const import_is_relative = import_.relative_path;
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> module_name_and_span = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<ByteString> names = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> _magic = module_names_and_spans.value().iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span> name_and_span = _magic_value.value();
{
names.push(name_and_span.template get<0>());
JaktInternal::Optional<Jakt::types::LoadedModule> maybe_loaded_module = this->program->get_loaded_module(name_and_span.template get<0>());
if (!maybe_loaded_module.has_value()){
JaktInternal::Optional<Jakt::jakt__path::Path> const maybe_file_name = TRY((this->compiler->search_for_path(name_and_span.template get<0>(),import_is_relative,parent_path_count)));
Jakt::jakt__path::Path const file_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::jakt__path::Path,ErrorOr<void>> {
auto __jakt_enum_value = (maybe_file_name.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(maybe_file_name.value());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(TRY((this->get_root_path().parent().join(name_and_span.template get<0>()).replace_extension(ByteString::from_utf8_without_validation("jakt"sv)))));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
if (File::exists(file_name.to_string())){
module_name_and_span = name_and_span;
break;
}
}
else {
module_name_and_span = name_and_span;
break;
}

}

}
}

if (!module_name_and_span.has_value()){
this->error(__jakt_format(StringView::from_string_literal("No module in module set {{{}}} was found"sv),Jakt::utility::join(names,ByteString::from_utf8_without_validation(", "sv))),import_.module_name.span());
return {};
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span> const module_name_module_span_ = module_name_and_span.value();
ByteString const module_name = module_name_module_span_.template get<0>();
Jakt::utility::Span const module_span = module_name_module_span_.template get<1>();

JaktInternal::Optional<Jakt::jakt__path::Path> const maybe_file_name = TRY((this->compiler->search_for_path(module_name,import_is_relative,parent_path_count)));
Jakt::jakt__path::Path const file_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::jakt__path::Path,ErrorOr<void>> {
auto __jakt_enum_value = (maybe_file_name.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(maybe_file_name.value());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(TRY((this->get_root_path().parent().join(module_name).replace_extension(ByteString::from_utf8_without_validation("jakt"sv)))));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool const is_in_the_stdlib = TRY((file_name.absolute())).to_string().starts_with(TRY((this->compiler->std_include_path.absolute())).to_string());
ByteString const sanitized_module_name = Jakt::utility::join(Jakt::utility::map<ByteString, ByteString>(TRY((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::jakt__path::Path,ErrorOr<void>> {
auto __jakt_enum_value = (is_in_the_stdlib);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::jakt__path::Path::from_string(__jakt_format(StringView::from_string_literal("{}/{}"sv),ByteString::from_utf8_without_validation("jakt"sv),TRY((file_name.absolute())).relative_to(TRY((this->compiler->std_include_path.absolute()))).to_string())));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(TRY((file_name.absolute())).relative_to(TRY((this->get_root_path().parent().absolute()))));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}).replace_extension(ByteString::from_utf8_without_validation(""sv)))).components(),[](ByteString item) -> ByteString {{
if (item == ByteString::from_utf8_without_validation(".."sv)){
return ByteString::from_utf8_without_validation("parent"sv);
}
return item;
}
}
),ByteString::from_utf8_without_validation("__"sv));
Jakt::ids::ModuleId imported_module_id = Jakt::ids::ModuleId(static_cast<size_t>(0ULL));
JaktInternal::Optional<Jakt::types::LoadedModule> maybe_loaded_module = this->program->get_loaded_module(sanitized_module_name);
if (!maybe_loaded_module.has_value()){
Jakt::utility::FileId const file_id = this->compiler->get_file_id_or_register(file_name);
JaktInternal::Tuple<JaktInternal::Optional<Jakt::utility::FileId>,JaktInternal::DynamicArray<u8>> const old_file_state = this->compiler->current_file_state();
TRY((this->compiler->set_current_file(file_id)));
ScopeGuard __jakt_var_28([&] {
this->compiler->restore_file_state(old_file_state);
});
JaktInternal::Optional<Jakt::parser::ParsedNamespace> const parsed_namespace = TRY((this->lex_and_parse_file_contents(file_id)));
if (!parsed_namespace.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Module '{}' not found"sv),module_name),module_span);
return {};
}
Jakt::ids::ModuleId const original_current_module_id = this->current_module_id;
imported_module_id = this->create_module(sanitized_module_name,false,file_name.to_string());
this->program->set_loaded_module(sanitized_module_name,Jakt::types::LoadedModule(imported_module_id,file_id));
this->current_module_id = imported_module_id;
Jakt::ids::ScopeId const imported_scope_id = this->create_scope(this->root_scope_id(),false,__jakt_format(StringView::from_string_literal("module({})"sv),sanitized_module_name),false);
NonnullRefPtr<Jakt::types::Scope> imported_scope = this->get_scope(imported_scope_id);
imported_scope->module_namespace_name = sanitized_module_name;
imported_scope->is_from_generated_code = parsed_namespace.value().is_generated_code;
TRY((this->typecheck_module(parsed_namespace.value(),imported_scope_id)));
this->current_module_id = original_current_module_id;
}
else {
imported_module_id = maybe_loaded_module.value().module_id;
}

JaktInternal::DynamicArray<Jakt::ids::ModuleId> current_module_imports = this->current_module()->imports;
current_module_imports.push(imported_module_id);
Jakt::parser::ImportList __jakt_tmp92 = import_.import_list;
if (import_.import_list.is_empty()){
JaktInternal::Dictionary<ByteString,Jakt::ids::ModuleId> scope_imports = this->get_scope(scope_id)->imports;
ByteString import_name = static_cast<JaktInternal::DynamicArray<ByteString>>(module_name.split(':')).last().value();
if (import_.alias_name.has_value()){
import_name = import_.alias_name.value().literal_name();
}
scope_imports.set(import_name,imported_module_id);
}
else if (import_.import_list.__jakt_init_index() == 1 /* All */){
NonnullRefPtr<Jakt::types::Scope> const import_scope = this->get_scope(Jakt::ids::ScopeId(imported_module_id,static_cast<size_t>(0ULL)));
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::VarId> _magic = import_scope->vars.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::VarId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::VarId> name__var_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::VarId> const jakt__name__var_id__ = name__var_id__;
ByteString const name = jakt__name__var_id__.template get<0>();
Jakt::ids::VarId const var_id = jakt__name__var_id__.template get<1>();

this->add_var_to_scope(scope_id,name,var_id,import_.module_name.span());
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::types::Value> _magic = import_scope->comptime_bindings.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::types::Value>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::types::Value> name__value__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::types::Value> const jakt__name__value__ = name__value__;
ByteString const name = jakt__name__value__.template get<0>();
Jakt::types::Value const value = jakt__name__value__.template get<1>();

this->add_comptime_binding_to_scope(scope_id,name,value,import_.module_name.span());
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::StructId> _magic = import_scope->structs.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::StructId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> name__struct_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> const jakt__name__struct_id__ = name__struct_id__;
ByteString const name = jakt__name__struct_id__.template get<0>();
Jakt::ids::StructId const struct_id = jakt__name__struct_id__.template get<1>();

TRY((this->add_struct_to_scope(scope_id,name,struct_id,import_.module_name.span())));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = import_scope->functions.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> name__overload_set__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const jakt__name__overload_set__ = name__overload_set__;
ByteString const name = jakt__name__overload_set__.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set = jakt__name__overload_set__.template get<1>();

this->add_function_to_scope(scope_id,name,overload_set,import_.module_name.span());
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::EnumId> _magic = import_scope->enums.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::EnumId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> name__enum_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> const jakt__name__enum_id__ = name__enum_id__;
ByteString const name = jakt__name__enum_id__.template get<0>();
Jakt::ids::EnumId const enum_id = jakt__name__enum_id__.template get<1>();

this->add_enum_to_scope(scope_id,name,enum_id,import_.module_name.span());
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::TypeId> _magic = import_scope->types.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::TypeId> name__type_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::TypeId> const jakt__name__type_id__ = name__type_id__;
ByteString const name = jakt__name__type_id__.template get<0>();
Jakt::ids::TypeId const type_id = jakt__name__type_id__.template get<1>();

TRY((this->add_type_to_scope(scope_id,name,type_id,import_.module_name.span())));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::TraitId> _magic = import_scope->traits.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::TraitId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::TraitId> name__trait_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::TraitId> const jakt__name__trait_id__ = name__trait_id__;
ByteString const name = jakt__name__trait_id__.template get<0>();
Jakt::ids::TraitId const trait_id = jakt__name__trait_id__.template get<1>();

TRY((this->add_trait_to_scope(scope_id,name,trait_id,import_.module_name.span())));
}

}
}

}
else if (__jakt_tmp92.__jakt_init_index() == 0 /* List */){
JaktInternal::DynamicArray<Jakt::parser::ImportName> const names = __jakt_tmp92.as.List.value;
Jakt::ids::ScopeId const import_scope_id = Jakt::ids::ScopeId(imported_module_id,static_cast<size_t>(0ULL));
{
JaktInternal::ArrayIterator<Jakt::parser::ImportName> _magic = names.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ImportName> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ImportName imported_name = _magic_value.value();
{
bool const found = TRY((this->find_and_import_name_from_scope(imported_name.literal_name(),imported_name.span(),imported_name.literal_name(),imported_name.span(),import_scope_id,scope_id,Jakt::typechecker::ImportRestrictions::all())));
if (!found){
this->error(__jakt_format(StringView::from_string_literal("Imported name '{}' not found in module '{}'"sv),imported_name.literal_name(),module_name),imported_name.span());
}
}

}
}

}
}
return {};
}

ErrorOr<bool> Jakt::typechecker::Typechecker::find_and_import_name_from_scope(ByteString const from_name,Jakt::utility::Span const from_span,ByteString const to_name,Jakt::utility::Span const to_span,Jakt::ids::ScopeId const from_scope_id,Jakt::ids::ScopeId const into_scope_id,Jakt::typechecker::ImportRestrictions const allow) {
{
bool found = false;
if (allow.functions){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const maybe_overload_set = TRY((this->find_functions_with_name_in_scope(from_scope_id,from_name,JaktInternal::OptionalNone())));
if (maybe_overload_set.has_value()){
found = true;
this->add_function_to_scope(into_scope_id,to_name,maybe_overload_set.value(),to_span);
}
}
if (allow.enums){
JaktInternal::Optional<Jakt::ids::EnumId> const maybe_enum_id = TRY((this->program->find_enum_in_scope(from_scope_id,from_name,false,JaktInternal::OptionalNone())));
if (maybe_enum_id.has_value()){
found = true;
this->add_enum_to_scope(into_scope_id,to_name,maybe_enum_id.value(),to_span);
}
}
if (allow.types){
JaktInternal::Optional<Jakt::ids::TypeId> const maybe_type_id = TRY((this->find_type_in_scope(from_scope_id,from_name)));
if (maybe_type_id.has_value()){
found = true;
TRY((this->add_type_to_scope(into_scope_id,to_name,maybe_type_id.value(),to_span)));
}
}
if (allow.structs){
JaktInternal::Optional<Jakt::ids::StructId> const maybe_struct_id = TRY((this->find_struct_in_scope(from_scope_id,from_name,JaktInternal::OptionalNone())));
if (maybe_struct_id.has_value()){
found = true;
TRY((this->add_struct_to_scope(into_scope_id,to_name,maybe_struct_id.value(),to_span)));
}
}
if (allow.traits){
JaktInternal::Optional<Jakt::ids::TraitId> const maybe_trait_id = TRY((this->find_trait_in_scope(from_scope_id,from_name)));
if (maybe_trait_id.has_value()){
found = true;
TRY((this->add_trait_to_scope(into_scope_id,to_name,maybe_trait_id.value(),to_span)));
}
}
if (allow.namespaces){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> const maybe_scope_id = TRY((this->find_namespace_in_scope(from_scope_id,from_name,false,JaktInternal::OptionalNone())));
if (maybe_scope_id.has_value()){
found = true;
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(into_scope_id);
scope->aliases.set(to_name,maybe_scope_id.value().template get<0>());
}
}
return found;
}
}

ErrorOr<Jakt::ids::ScopeId> Jakt::typechecker::Typechecker::cache_or_process_cpp_import(Jakt::jakt__path::Path const import_path,Jakt::ids::ScopeId const scope_id,bool const is_c,JaktInternal::Dictionary<ByteString,ByteString> const defines) {
{
if (!this->cpp_import_processor.has_value()){
this->cpp_import_processor = Jakt::cpp_import__none::CppImportProcessor::create(this->compiler->debug_print_cpp_import);
}
NonnullRefPtr<Jakt::types::Module> module = this->program->get_module(scope_id.module_id);
Jakt::ids::ScopeId const result_scope_id = TRY((this->cpp_import_processor.value().process_cpp_import(this->program,import_path,scope_id,is_c,defines)));
return result_scope_id;
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_extern_import(Jakt::parser::ParsedExternImport const import_,Jakt::ids::ScopeId const scope_id) {
{
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedFunction> _magic = import_.assigned_namespace.functions.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedFunction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedFunction f = _magic_value.value();
{
if (!(f.linkage.__jakt_init_index() == 1 /* External */)){
this->error(ByteString::from_utf8_without_validation("Expected all functions in an `import extern` to be be external"sv),f.name_span);
}
if (import_.is_c && (!f.generic_parameters.is_empty())){
this->error_with_hint(__jakt_format(StringView::from_string_literal("imported function '{}' is declared to have C linkage, but is generic"sv),f.name),f.name_span,ByteString::from_utf8_without_validation("this function may not be generic"sv),f.name_span);
}
if (!f.block.stmts.is_empty()){
this->error(ByteString::from_utf8_without_validation("imported extern function is not allowed to have a body"sv),f.name_span);
}
}

}
}

{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = import_.assigned_namespace.records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord record = _magic_value.value();
{
if (!(record.definition_linkage.__jakt_init_index() == 1 /* External */)){
this->error(ByteString::from_utf8_without_validation("Expected all records in an `import extern` to be external"sv),record.name_span);
}
if (import_.is_c && (!record.generic_parameters.is_empty())){
this->error_with_hint(__jakt_format(StringView::from_string_literal("imported {} '{}' is declared to have C linkage, but is generic"sv),record.record_type.record_type_name(),record.name),record.name_span,__jakt_format(StringView::from_string_literal("this {} may not be generic"sv),record.record_type.record_type_name()),record.name_span);
}
}

}
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_imports(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id) {
{
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedModuleImport> _magic = parsed_namespace.module_imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedModuleImport> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedModuleImport module_import = _magic_value.value();
{
TRY((this->typecheck_module_import(module_import,scope_id)));
}

}
}

JaktInternal::DynamicArray<Jakt::parser::ParsedExternImport> coalesced_imports = DynamicArray<Jakt::parser::ParsedExternImport>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedExternImport> _magic = parsed_namespace.extern_imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedExternImport> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedExternImport extern_import = _magic_value.value();
{
if (!extern_import.should_auto_import){
continue;
}
ByteString const path = extern_import.get_path();
JaktInternal::Optional<Jakt::ids::ScopeId> const existing_scope = this->cpp_import_cache.get(path);
if (existing_scope.has_value()){
Jakt::ids::ScopeId const import_scope_id = existing_scope.value();
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
scope->resolution_mixins.push(Jakt::types::ResolutionMixin(import_scope_id,true,true,true,true,true,true,true,true,true));
if (extern_import.assigned_namespace.name.has_value()){
this->get_scope(import_scope_id)->namespace_name = extern_import.assigned_namespace.name.value();
this->get_scope(import_scope_id)->external_name = Jakt::parser::ExternalName::Plain(ByteString::from_utf8_without_validation(""sv));
}
continue;
}
JaktInternal::Optional<Jakt::jakt__path::Path> const entry = TRY((this->compiler->find_in_search_paths(Jakt::jakt__path::Path::from_string(path),false,static_cast<size_t>(0ULL))));
if (!entry.has_value()){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Could not find imported extern file '{}'"sv),path),extern_import.assigned_namespace.name_span.value(),ByteString::from_utf8_without_validation("make sure the file exists and is in the include search paths"sv),extern_import.assigned_namespace.name_span.value());
continue;
}
coalesced_imports.push(extern_import);
}

}
}

if (!coalesced_imports.is_empty()){
Jakt::ids::ScopeId const child_scope_id = this->create_scope(this->root_scope_id(),false,ByteString::from_utf8_without_validation("coalesced-extern-imports"sv),false);
{
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
scope->resolution_mixins.push(Jakt::types::ResolutionMixin(child_scope_id,true,true,true,true,true,true,true,true,true));
}

TRY((this->typecheck_auto_extern_imports(coalesced_imports,child_scope_id)));
}
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedExternImport> _magic = parsed_namespace.extern_imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedExternImport> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedExternImport extern_import = _magic_value.value();
{
if (!extern_import.should_auto_import){
TRY((this->typecheck_extern_import(extern_import,scope_id)));
}
}

}
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_auto_extern_imports(JaktInternal::DynamicArray<Jakt::parser::ParsedExternImport> const imports,Jakt::ids::ScopeId const child_scope_id) {
{
if (imports.is_empty()){
return {};
}
ByteStringBuilder builder = ByteStringBuilder::create();
ByteStringBuilder path_name_builder = ByteStringBuilder::create();
builder.append(StringView::from_string_literal("#pragma once\n"sv));
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedExternImport> _magic = imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedExternImport> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedExternImport import_ = _magic_value.value();
{
path_name_builder.append(StringView::from_string_literal("_"sv));
path_name_builder.append(Jakt::jakt__path::Path::from_string(import_.get_path()).basename(true));
{
JaktInternal::ArrayIterator<Jakt::parser::IncludeAction> _magic = import_.before_include.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::IncludeAction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::IncludeAction action = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Define */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Define;ByteString const& name = __jakt_match_value.name;
ByteString const& value = __jakt_match_value.value;
return ({builder.appendff(ByteString::from_utf8_without_validation("#define {} {}\n"sv),name,value);}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Undefine */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Undefine;ByteString const& name = __jakt_match_value.name;
return ({builder.appendff(ByteString::from_utf8_without_validation("#undef {}\n"sv),name);}), JaktInternal::ExplicitValue<void>();
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

if (import_.is_c){
builder.append(StringView::from_string_literal("extern \"C\" {\n"sv));
}
builder.appendff(ByteString::from_utf8_without_validation("#include <{}>\n"sv),import_.get_path());
if (import_.is_c){
builder.append(StringView::from_string_literal("}\n"sv));
}
{
JaktInternal::ArrayIterator<Jakt::parser::IncludeAction> _magic = import_.after_include.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::IncludeAction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::IncludeAction action = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Define */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Define;ByteString const& name = __jakt_match_value.name;
ByteString const& value = __jakt_match_value.value;
return ({builder.appendff(ByteString::from_utf8_without_validation("#define {} {}\n"sv),name,value);}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Undefine */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Undefine;ByteString const& name = __jakt_match_value.name;
return ({builder.appendff(ByteString::from_utf8_without_validation("#undef {}\n"sv),name);}), JaktInternal::ExplicitValue<void>();
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

}
}

ByteString const contents = builder.to_string();
ByteString const filename = __jakt_format(StringView::from_string_literal("jakt_autogen_{}.h"sv),path_name_builder.to_string().hash());
Jakt::jakt__path::Path const output = TRY((this->compiler->binary_dir.absolute())).join(filename);
TRY((Jakt::utility::write_to_file(contents,output.to_string())));
Jakt::ids::ScopeId const import_scope_id = ({ Optional<Jakt::ids::ScopeId> __jakt_var_29;
auto __jakt_var_30 = [&]() -> ErrorOr<Jakt::ids::ScopeId> { return this->cache_or_process_cpp_import(output,child_scope_id,false,Dictionary<ByteString, ByteString>::create_with_entries({})); }();
if (__jakt_var_30.is_error()) {auto e = __jakt_var_30.release_error();
{
if (ByteString::from_utf8_without_validation(e.string_literal()) == ByteString::from_utf8_without_validation(Jakt::cpp_import__common::CppImportErrors::path_not_found())){
warnln(StringView::from_string_literal("[ICE] File gone missing during typecheck: {}"sv),output);
return {};
}
else {
return e;
}

}
} else {__jakt_var_29 = __jakt_var_30.release_value();
}
__jakt_var_29.release_value(); });
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedExternImport> _magic = imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedExternImport> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedExternImport import_ = _magic_value.value();
{
this->cpp_import_cache.set(import_.get_path(),import_scope_id);
}

}
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_constructors(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id) {
{
JaktInternal::DynamicArray<Jakt::ids::ScopeId> const children = this->get_scope(scope_id)->children;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parsed_namespace.namespaces.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::parser::ParsedNamespace const child_namespace = parsed_namespace.namespaces.operator[](i);
Jakt::ids::ScopeId const child_namespace_scope_id = children.operator[](i);
TRY((this->typecheck_namespace_constructors(child_namespace,child_namespace_scope_id)));
}

}
}

JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> __jakt_tmp93 = this->get_scope(scope_id)->resolved_forall_chunks;
if (__jakt_tmp93.has_value()){
JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk> const chunks = __jakt_tmp93.value();
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedForallChunk> _magic = chunks.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedForallChunk> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolvedForallChunk chunk = _magic_value.value();
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> all_types = Jakt::typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create(chunk.parameters);
size_t i = static_cast<size_t>(0ULL);
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = all_types;
for (;;){
JaktInternal::Optional<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> stuff = _magic_value.value();
{
ScopeGuard __jakt_var_31([&] {
i += static_cast<size_t>(1ULL);
});
TRY((this->typecheck_namespace_constructors(chunk.parsed_namespace,chunk.generated_scopes.operator[](i))));
}

}
}

}

}
}

}
AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>> records_to_process = AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>>();
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_namespace.records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord parsed_record = _magic_value.value();
{
records_to_process.enqueue(Tuple{parsed_record, scope_id});
}

}
}

while (!records_to_process.is_empty()){
JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId> const record_scope_id_ = records_to_process.dequeue();
Jakt::parser::ParsedRecord const record = record_scope_id_.template get<0>();
Jakt::ids::ScopeId const scope_id = record_scope_id_.template get<1>();

Jakt::types::StructLikeId const id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::StructLikeId, ErrorOr<void>>{
auto&& __jakt_match_variant = record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */:case 1 /* Class */:{
JaktInternal::Optional<Jakt::ids::StructId> const struct_id = TRY((this->find_struct_in_scope(scope_id,record.name,JaktInternal::OptionalNone())));
if (!struct_id.has_value()){
this->compiler->panic(ByteString::from_utf8_without_validation("can't find previously added struct"sv));
}
TRY((this->typecheck_struct_constructor(record,struct_id.value(),scope_id)));
return JaktInternal::ExplicitValue<Jakt::types::StructLikeId>(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id.value()));
}
VERIFY_NOT_REACHED();
case 3 /* SumEnum */:case 2 /* ValueEnum */:{
JaktInternal::Optional<Jakt::ids::EnumId> const enum_id = TRY((this->program->find_enum_in_scope(scope_id,record.name,false,JaktInternal::OptionalNone())));
if (!enum_id.has_value()){
this->compiler->panic(ByteString::from_utf8_without_validation("can't find previously added enum"sv));
}
TRY((this->typecheck_enum_constructor(record,enum_id.value(),scope_id)));
return JaktInternal::ExplicitValue<Jakt::types::StructLikeId>(Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id.value()));
}
VERIFY_NOT_REACHED();
default:{
return JaktInternal::LoopContinue{};
}
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
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = record.nested_records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord nested_record = _magic_value.value();
{
TRY((this->warn_about_unimplemented_nested_record(nested_record)));
records_to_process.enqueue(Tuple{nested_record, id.scope_id(this->program)});
}

}
}

}
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_aliases(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id,Jakt::typechecker::ImportRestrictions const allow) {
{
JaktInternal::DynamicArray<Jakt::ids::ScopeId> const children = this->get_scope(scope_id)->children;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parsed_namespace.namespaces.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::parser::ParsedNamespace const child_namespace = parsed_namespace.namespaces.operator[](i);
Jakt::ids::ScopeId const child_namespace_scope_id = children.operator[](i);
TRY((this->typecheck_namespace_aliases(child_namespace,child_namespace_scope_id,allow)));
}

}
}

JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> __jakt_tmp94 = this->get_scope(scope_id)->resolved_forall_chunks;
if (__jakt_tmp94.has_value()){
JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk> const chunks = __jakt_tmp94.value();
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedForallChunk> _magic = chunks.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedForallChunk> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolvedForallChunk chunk = _magic_value.value();
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> all_types = Jakt::typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create(chunk.parameters);
size_t i = static_cast<size_t>(0ULL);
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = all_types;
for (;;){
JaktInternal::Optional<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> stuff = _magic_value.value();
{
ScopeGuard __jakt_var_32([&] {
i += static_cast<size_t>(1ULL);
});
TRY((this->typecheck_namespace_aliases(chunk.parsed_namespace,chunk.generated_scopes.operator[](i),allow)));
}

}
}

}

}
}

}
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedAlias> _magic = parsed_namespace.aliases.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedAlias> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedAlias alias = _magic_value.value();
{
TRY((this->typecheck_alias(alias,scope_id,allow)));
}

}
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_alias(Jakt::parser::ParsedAlias const alias,Jakt::ids::ScopeId const scope_id,Jakt::typechecker::ImportRestrictions const allow) {
{
Jakt::parser::ParsedName const aliased_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::parser::ParsedName,ErrorOr<void>> {
auto __jakt_enum_value = (alias.alias_name.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(alias.alias_name.value());
}else {{
Jakt::parser::ParsedNameWithGenericParameters const name = alias.target.last().value();
if (!name.generic_parameters.is_empty()){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Cannot alias a generic instance of a type to the type itself"sv)),name.name_span,__jakt_format(StringView::from_string_literal("Add an alias name here: 'as <name>'"sv)),name.name_span);
}
return JaktInternal::ExplicitValue<Jakt::parser::ParsedName>(Jakt::parser::ParsedName(name.name,name.name_span));
}
VERIFY_NOT_REACHED();
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::ScopeId resolved_scope_id = scope_id;
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> alias_path = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_sub(alias.target.size(),static_cast<size_t>(1ULL)))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> const namespace_ = TRY((this->find_namespace_in_scope(resolved_scope_id,alias.target.operator[](i).name,false,JaktInternal::OptionalNone())));
if (!namespace_.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Unknown namespace '{}'"sv),alias.target.operator[](i).name),alias.target.operator[](i).name_span);
return {};
}
resolved_scope_id = namespace_.value().template get<0>();
alias_path.push(Jakt::types::ResolvedNamespace(alias.target.operator[](i).name,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()));
}

}
}

NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
Jakt::ids::ScopeId const alias_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId,ErrorOr<void>> {
auto __jakt_enum_value = (scope->alias_scope.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(scope->alias_scope.value());
}else if (!__jakt_enum_value) {{
Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,false,__jakt_format(StringView::from_string_literal("alias-scope({})"sv),scope->debug_name),false);
NonnullRefPtr<Jakt::types::Scope> new_scope = this->get_scope(new_scope_id);
new_scope->alias_path = alias_path;
this->get_scope(scope_id)->children.push(new_scope_id);
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(new_scope_id);
}
VERIFY_NOT_REACHED();
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY((this->find_and_import_name_from_scope(alias.target.last().value().name,alias.target.last().value().name_span,aliased_name.name,aliased_name.span,resolved_scope_id,alias_scope_id,allow)));
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_function_predecl(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
JaktInternal::DynamicArray<Jakt::ids::ScopeId> const children = this->get_scope(scope_id)->children;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parsed_namespace.namespaces.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::parser::ParsedNamespace const child_namespace = parsed_namespace.namespaces.operator[](i);
Jakt::ids::ScopeId const child_namespace_scope_id = children.operator[](i);
TRY((this->typecheck_namespace_function_predecl(child_namespace,child_namespace_scope_id,comptime_pass,generic_pass)));
}

}
}

{
JaktInternal::ArrayIterator<Jakt::parser::ParsedFunction> _magic = parsed_namespace.functions.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedFunction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedFunction fun = _magic_value.value();
{
if ((fun.is_comptime == comptime_pass) && (generic_pass == !fun.generic_parameters.is_empty())){
TRY((this->typecheck_function_predecl(fun,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
}
}

}
}

NonnullRefPtr<Jakt::types::Module> module = this->current_module();
AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>> records_to_process = AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>>();
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_namespace.records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord parsed_record = _magic_value.value();
{
records_to_process.enqueue(Tuple{parsed_record, scope_id});
}

}
}

while (!records_to_process.is_empty()){
JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId> const record_scope_id_ = records_to_process.dequeue();
Jakt::parser::ParsedRecord const record = record_scope_id_.template get<0>();
Jakt::ids::ScopeId const scope_id = record_scope_id_.template get<1>();

Jakt::ids::ScopeId const record_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId, ErrorOr<void>>{
auto&& __jakt_match_variant = record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */:case 1 /* Class */:{
JaktInternal::Optional<Jakt::ids::StructId> const struct_id = TRY((this->find_struct_in_scope(scope_id,record.name,JaktInternal::OptionalNone())));
if (!struct_id.has_value()){
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(this->get_struct(struct_id.value()).scope_id);
}
VERIFY_NOT_REACHED();
default:{
JaktInternal::Optional<Jakt::ids::EnumId> const enum_id = TRY((this->program->find_enum_in_scope(scope_id,record.name,false,JaktInternal::OptionalNone())));
if (!enum_id.has_value()){
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(this->get_enum(enum_id.value()).scope_id);
}
VERIFY_NOT_REACHED();
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
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = record.nested_records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord nested_record = _magic_value.value();
{
TRY((this->warn_about_unimplemented_nested_record(nested_record)));
records_to_process.enqueue(Tuple{nested_record, record_scope_id});
}

}
}

{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = record.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
if (method.parsed_function.is_comptime != comptime_pass){
continue;
}
if (generic_pass == !method.parsed_function.generic_parameters.is_empty()){
continue;
}
if ((!record.generic_parameters.is_empty()) || (!method.parsed_function.generic_parameters.is_empty())){
NonnullRefPtr<Jakt::types::CheckedFunction> func = this->get_function(TRY((this->find_function_matching_signature_in_scope(record_scope_id,method.parsed_function))).value());
Jakt::ids::ScopeId const method_scope_id = func->function_scope_id;
Jakt::ids::ScopeId const check_scope = this->create_scope(method_scope_id,func->can_throw,__jakt_format(StringView::from_string_literal("method-checking({}::{})"sv),record.name,func->name),true);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = func->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
this->add_var_to_scope(check_scope,param.variable->name,module->add_variable(param.variable),param.variable->definition_span);
}

}
}

JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
Jakt::types::CheckedBlock const block = TRY((this->typecheck_block(method.parsed_function.block,check_scope,Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone())));
this->exit_ignore_error_mode(snapshot);
Jakt::ids::TypeId const function_return_type_id = func->return_type_id;
Jakt::ids::TypeId return_type_id = Jakt::types::builtin(Jakt::types::BuiltinType::Void());
if (function_return_type_id.equals(Jakt::types::unknown_type_id())){
if (!block.statements.is_empty()){
NonnullRefPtr<typename Jakt::types::CheckedStatement> __jakt_tmp95 = block.statements.last().value();
if (__jakt_tmp95->__jakt_init_index() == 8 /* Return */){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const val = __jakt_tmp95->as.Return.val;
if (val.has_value()){
return_type_id = TRY((this->resolve_type_var(val.value()->type(),method_scope_id)));
}
}
}
}
else {
return_type_id = TRY((this->resolve_type_var(function_return_type_id,scope_id)));
}

func->block = block;
func->return_type_id = return_type_id;
}
}

}
}

}
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> __jakt_tmp96 = this->get_scope(scope_id)->resolved_forall_chunks;
if (__jakt_tmp96.has_value()){
JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk> const chunks = __jakt_tmp96.value();
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedForallChunk> _magic = chunks.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedForallChunk> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolvedForallChunk chunk = _magic_value.value();
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> all_types = Jakt::typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create(chunk.parameters);
size_t i = static_cast<size_t>(0ULL);
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = all_types;
for (;;){
JaktInternal::Optional<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> stuff = _magic_value.value();
{
ScopeGuard __jakt_var_33([&] {
i += static_cast<size_t>(1ULL);
});
TRY((this->typecheck_namespace_function_predecl(chunk.parsed_namespace,chunk.generated_scopes.operator[](i),comptime_pass,generic_pass)));
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

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_predecl(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id) {
{
size_t const module_struct_len = this->current_module()->structures.size();
size_t const module_enum_len = this->current_module()->enums.size();
size_t struct_index = static_cast<size_t>(0ULL);
size_t enum_index = static_cast<size_t>(0ULL);
AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>> records_to_process = AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>>();
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_namespace.records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord parsed_record = _magic_value.value();
{
records_to_process.enqueue(Tuple{parsed_record, scope_id});
}

}
}

while (!records_to_process.is_empty()){
JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId> const parsed_record_scope_id_ = records_to_process.dequeue();
Jakt::parser::ParsedRecord const parsed_record = parsed_record_scope_id_.template get<0>();
Jakt::ids::ScopeId const scope_id = parsed_record_scope_id_.template get<1>();

Jakt::types::StructLikeId const id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::StructLikeId, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */:case 1 /* Class */:{
TRY((this->typecheck_struct_predecl_initial(parsed_record,struct_index++,module_struct_len,scope_id)));
return JaktInternal::ExplicitValue<Jakt::types::StructLikeId>(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),Jakt::ids::StructId(scope_id.module_id,JaktInternal::checked_sub(struct_index,static_cast<size_t>(1ULL)))));
}
VERIFY_NOT_REACHED();
case 3 /* SumEnum */:case 2 /* ValueEnum */:{
TRY((this->typecheck_enum_predecl_initial(parsed_record,enum_index++,module_enum_len,scope_id)));
return JaktInternal::ExplicitValue<Jakt::types::StructLikeId>(Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),Jakt::ids::EnumId(scope_id.module_id,JaktInternal::checked_sub(enum_index,static_cast<size_t>(1ULL)))));
}
VERIFY_NOT_REACHED();
case 4 /* Garbage */:{
return JaktInternal::LoopContinue{};
}
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
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_record.nested_records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord record = _magic_value.value();
{
records_to_process.enqueue(Tuple{record, id.scope_id(this->program)});
}

}
}

}
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedNamespace> _magic = parsed_namespace.namespaces.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedNamespace> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedNamespace namespace_ = _magic_value.value();
{
ByteString debug_name = ByteString::from_utf8_without_validation("namespace("sv);
if (namespace_.name.has_value()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(debug_name,namespace_.name.value());
}
else {
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(debug_name,ByteString::from_utf8_without_validation("unnamed-namespace"sv));
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(debug_name,ByteString::from_utf8_without_validation(")"sv));
JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,bool> existing_scope_id_existing_scope_is_imported_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,bool>,ErrorOr<void>> {
auto __jakt_enum_value = (namespace_.name.has_value());
if (__jakt_enum_value) {{
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> const result = TRY((this->find_namespace_in_scope(scope_id,namespace_.name.value(),false,JaktInternal::OptionalNone())));
return JaktInternal::ExplicitValue<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,bool>>(Tuple{result.map([](auto& _value) { return _value.template get<0>(); }), result.map([](auto& _value) { return _value.template get<1>(); }).value_or_lazy_evaluated([&] { return false; })});
}
VERIFY_NOT_REACHED();
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), false});
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
JaktInternal::Optional<Jakt::ids::ScopeId> existing_scope_id = existing_scope_id_existing_scope_is_imported_.template get<0>();
bool existing_scope_is_imported = existing_scope_id_existing_scope_is_imported_.template get<1>();

JaktInternal::Optional<Jakt::ids::ScopeId> namespace_scope_id = existing_scope_id;
if (existing_scope_id.has_value()){
if (existing_scope_is_imported){
this->error(__jakt_format(StringView::from_string_literal("Invalid extension of imported namespace '{}'"sv),namespace_.name.value()),namespace_.name_span.value_or_lazy_evaluated([&] { return namespace_.keyword_span; }));
}
}
else {
if (namespace_.import_path_if_extern.has_value()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(debug_name,ByteString::from_utf8_without_validation(" (extern "sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(debug_name,namespace_.import_path_if_extern.value());
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(debug_name,ByteString::from_utf8_without_validation(")"sv));
}
Jakt::ids::ScopeId const parent_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId,ErrorOr<void>> {
auto __jakt_enum_value = (namespace_.import_path_if_extern.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::ids::ScopeId(Jakt::ids::ModuleId(static_cast<size_t>(1ULL)),static_cast<size_t>(0ULL)));
}else {return JaktInternal::ExplicitValue(scope_id);
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
Jakt::ids::ScopeId const child_scope_id = this->create_scope(parent_scope_id,false,debug_name,false);
NonnullRefPtr<Jakt::types::Scope> child_scope = this->get_scope(child_scope_id);
child_scope->namespace_name = namespace_.name;
child_scope->import_path_if_extern = namespace_.import_path_if_extern;
child_scope->before_extern_include = namespace_.generating_import_extern_before_include;
child_scope->after_extern_include = namespace_.generating_import_extern_after_include;
child_scope->is_from_generated_code = (child_scope->is_from_generated_code || namespace_.is_generated_code);
if (namespace_.import_path_if_extern.has_value()){
child_scope->resolution_mixins.push(Jakt::types::ResolutionMixin(scope_id,true,true,true,true,true,true,true,true,true));
}
namespace_scope_id = child_scope_id;
}

NonnullRefPtr<Jakt::types::Scope> parent_scope = this->get_scope(scope_id);
parent_scope->children.push(namespace_scope_id.value());
TRY((this->typecheck_namespace_predecl(namespace_,namespace_scope_id.value())));
}

}
}

{
JaktInternal::ArrayIterator<Jakt::parser::ParsedTrait> _magic = parsed_namespace.traits.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedTrait> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedTrait parsed_trait = _magic_value.value();
{
TRY((this->typecheck_trait_predecl(parsed_trait,scope_id)));
}

}
}

struct_index = static_cast<size_t>(0ULL);
enum_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_namespace.records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord parsed_record = _magic_value.value();
{
records_to_process.enqueue(Tuple{parsed_record, scope_id});
}

}
}

while (!records_to_process.is_empty()){
JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId> const parsed_record_scope_id_ = records_to_process.dequeue();
Jakt::parser::ParsedRecord const parsed_record = parsed_record_scope_id_.template get<0>();
Jakt::ids::ScopeId const scope_id = parsed_record_scope_id_.template get<1>();

Jakt::ids::ScopeId const id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */:case 1 /* Class */:{
Jakt::ids::StructId const struct_id = Jakt::ids::StructId(this->current_module_id,JaktInternal::checked_add(struct_index,module_struct_len));
TRY((this->typecheck_struct_predecl(parsed_record,struct_id,scope_id)));
struct_index++;
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(this->get_struct(struct_id).scope_id);
}
VERIFY_NOT_REACHED();
case 3 /* SumEnum */:case 2 /* ValueEnum */:{
Jakt::ids::EnumId const enum_id = Jakt::ids::EnumId(this->current_module_id,JaktInternal::checked_add(enum_index,module_enum_len));
TRY((this->typecheck_enum_predecl(parsed_record,enum_id,scope_id)));
enum_index++;
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(this->get_enum(enum_id).scope_id);
}
VERIFY_NOT_REACHED();
case 4 /* Garbage */:{
return JaktInternal::LoopContinue{};
}
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
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_record.nested_records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord record = _magic_value.value();
{
records_to_process.enqueue(Tuple{record, id});
}

}
}

}
{
JaktInternal::ArrayIterator<bool> _magic = DynamicArray<bool>::create_with({false, true}).iterator();
for (;;){
JaktInternal::Optional<bool> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
bool default_pass = _magic_value.value();
{
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedExternalTraitImplementation> _magic = parsed_namespace.external_trait_implementations.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedExternalTraitImplementation> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedExternalTraitImplementation implementation = _magic_value.value();
{
Jakt::ids::TypeId const for_type = TRY((this->typecheck_typename(implementation.for_type,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(for_type);
ScopeGuard __jakt_var_34([&] {
this->self_type_id = old_self_type_id;
});
NonnullRefPtr<typename Jakt::types::Type> type = this->get_type(for_type);
if (type->is_builtin()){
type = this->get_type(this->get_struct(this->program->builtin_implementation_struct(type->as_builtin_type(),this->program->prelude_module_id())).type_id);
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct struct_ = this->get_struct(struct_id);
TRY((this->resolve_external_trait_implementations(implementation,struct_.scope_id,struct_.trait_implementations,for_type,scope_id,default_pass)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
Jakt::types::CheckedStruct struct_ = this->get_struct(struct_id);
TRY((this->resolve_external_trait_implementations(implementation,struct_.scope_id,struct_.trait_implementations,for_type,scope_id,default_pass)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum enum_ = this->get_enum(enum_id);
TRY((this->resolve_external_trait_implementations(implementation,enum_.scope_id,enum_.trait_implementations,for_type,scope_id,default_pass)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
Jakt::types::CheckedEnum enum_ = this->get_enum(enum_id);
TRY((this->resolve_external_trait_implementations(implementation,enum_.scope_id,enum_.trait_implementations,for_type,scope_id,default_pass)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
if (!default_pass){
this->error(__jakt_format(StringView::from_string_literal("Cannot implement traits for type '{}'"sv),TRY((this->type_name(for_type,false)))),implementation.for_type->span());
}
}
return JaktInternal::ExplicitValue<void>();
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
}

{
JaktInternal::ArrayIterator<Jakt::parser::ParsedTrait> _magic = parsed_namespace.traits.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedTrait> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedTrait parsed_trait = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TraitId> const trait_id = TRY((this->find_trait_in_scope(scope_id,parsed_trait.name)));
if (trait_id.has_value()){
TRY((this->typecheck_trait(parsed_trait,trait_id.value(),scope_id,true)));
}
else {
this->compiler->panic(ByteString::from_utf8_without_validation("can't find trait that has been previous added"sv));
}

}

}
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter>,Jakt::parser::ParsedNamespace>> _magic = parsed_namespace.forall_chunks.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter>,Jakt::parser::ParsedNamespace>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter>,Jakt::parser::ParsedNamespace> chunk_parameters__chunk_namespace__ = _magic_value.value();
{
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter>,Jakt::parser::ParsedNamespace> const jakt__chunk_parameters__chunk_namespace__ = chunk_parameters__chunk_namespace__;
JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> const chunk_parameters = jakt__chunk_parameters__chunk_namespace__.template get<0>();
Jakt::parser::ParsedNamespace const chunk_namespace = jakt__chunk_parameters__chunk_namespace__.template get<1>();

JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const resolved_parameters = TRY((this->typecheck_forall_chunk_parameters(chunk_parameters,scope_id)));
Jakt::types::ResolvedForallChunk resolved_chunk = Jakt::types::ResolvedForallChunk(resolved_parameters,chunk_namespace,DynamicArray<Jakt::ids::ScopeId>::create_with({}));
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> all_types = Jakt::typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create(resolved_parameters);
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = all_types;
for (;;){
JaktInternal::Optional<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> parameters = _magic_value.value();
{
ByteStringBuilder debug_name_builder = ByteStringBuilder::create();
debug_name_builder.append(StringView::from_string_literal("forall<"sv));
bool first = true;
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = parameters.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> name__value__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> const jakt__name__value__ = name__value__;
ByteString const name = jakt__name__value__.template get<0>();
JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId> const value = jakt__name__value__.template get<1>();

if (first){
first = false;
}
else {
debug_name_builder.append(StringView::from_string_literal(", "sv));
}

debug_name_builder.append(name);
debug_name_builder.append(StringView::from_string_literal("="sv));
debug_name_builder.append(TRY((this->type_name(value.template get<1>(),false))));
}

}
}

debug_name_builder.append(StringView::from_string_literal("> namespace"sv));
Jakt::ids::ScopeId const namespace_scope_id = this->create_scope(scope_id,false,debug_name_builder.to_string(),false);
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = parameters.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> name__value__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> const jakt__name__value__ = name__value__;
ByteString const name = jakt__name__value__.template get<0>();
JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId> const value = jakt__name__value__.template get<1>();

TRY((this->add_type_to_scope(namespace_scope_id,name,value.template get<1>(),value.template get<0>())));
}

}
}

NonnullRefPtr<Jakt::types::Scope> parent_scope = this->get_scope(scope_id);
parent_scope->children.push(namespace_scope_id);
parent_scope->resolution_mixins.push(Jakt::types::ResolutionMixin(namespace_scope_id,true,true,true,true,true,true,true,true,true));
TRY((this->typecheck_namespace_predecl(chunk_namespace,namespace_scope_id)));
resolved_chunk.generated_scopes.push(namespace_scope_id);
}

}
}

NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
if (!scope->resolved_forall_chunks.has_value()){
scope->resolved_forall_chunks = DynamicArray<Jakt::types::ResolvedForallChunk>::create_with({});
}
scope->resolved_forall_chunks.value().push(resolved_chunk);
}

}
}

}
return {};
}

ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>>> Jakt::typechecker::Typechecker::typecheck_forall_chunk_parameters(JaktInternal::DynamicArray<Jakt::parser::ParsedGenericParameter> const chunk_parameters,Jakt::ids::ScopeId const scope_id) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::ids::TraitId>>> named_requirements = DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::ids::TraitId>>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedGenericParameter> _magic = chunk_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedGenericParameter parameter = _magic_value.value();
{
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters>> __jakt_tmp97 = parameter.requires_list;
if (__jakt_tmp97.has_value()){
JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> const requires_list = __jakt_tmp97.value();
if (!requires_list.is_empty()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations = DynamicArray<Jakt::ids::TypeId>::create_with({});
JaktInternal::DynamicArray<Jakt::ids::TraitId> trait_requirements = DynamicArray<Jakt::ids::TraitId>::create_with({});
TRY((this->fill_trait_requirements(requires_list,trait_requirements,trait_implementations,scope_id)));
if (trait_requirements.is_empty()){
continue;
}
named_requirements.push(Tuple{parameter.name, parameter.span, trait_requirements});
}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("forall type '{}' is not allowed to be unconditional"sv),parameter.name),parameter.span,ByteString::from_utf8_without_validation("Try adding a 'requires' clause to the this type"sv),parameter.span);
continue;
}

}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("forall type '{}' is not allowed to be unconditional"sv),parameter.name),parameter.span,ByteString::from_utf8_without_validation("Try adding a 'requires' clause to the this type"sv),parameter.span);
continue;
}

}

}
}

JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_35([&] {
this->exit_ignore_error_mode(snapshot);
});
JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> results = Dictionary<ByteString, JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>>::create_with_entries({});
NonnullRefPtr<Jakt::types::Module> const module = this->current_module();
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::ids::TraitId>>> _magic = named_requirements.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::ids::TraitId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::ids::TraitId>> name__span__traits__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::ids::TraitId>> const jakt__name__span__traits__ = name__span__traits__;
ByteString const name = jakt__name__span__traits__.template get<0>();
Jakt::utility::Span const span = jakt__name__span__traits__.template get<1>();
JaktInternal::DynamicArray<Jakt::ids::TraitId> const traits = jakt__name__span__traits__.template get<2>();

{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(module->types.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t type_index = _magic_value.value();
{
Jakt::ids::TypeId type_id = Jakt::ids::TypeId(module->id,type_index);
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
TRY((this->check_type_argument_requirements(type_id,traits,span,scope_id)));
bool const matches = !this->had_an_error;
this->exit_ignore_error_mode(snapshot);
if (!matches){
continue;
}
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(type_id);
if (type->is_builtin()){
type_id = Jakt::types::builtin(type->as_builtin_type());
}
if (results.contains(name)){
results.operator[](name).push(Tuple{span, type_id});
}
else {
results.set(name, DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create_with({Tuple{span, type_id}}));
}

}

}
}

}

}
}

return results;
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_methods_predecl(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
JaktInternal::DynamicArray<Jakt::ids::ScopeId> const children = this->get_scope(scope_id)->children;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parsed_namespace.namespaces.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::parser::ParsedNamespace const child_namespace = parsed_namespace.namespaces.operator[](i);
Jakt::ids::ScopeId const child_namespace_scope_id = children.operator[](i);
TRY((this->typecheck_namespace_methods_predecl(child_namespace,child_namespace_scope_id,comptime_pass,generic_pass)));
}

}
}

AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>> records_to_process = AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>>();
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_namespace.records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord parsed_record = _magic_value.value();
{
records_to_process.enqueue(Tuple{parsed_record, scope_id});
}

}
}

while (!records_to_process.is_empty()){
JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId> const parsed_record_scope_id_ = records_to_process.dequeue();
Jakt::parser::ParsedRecord const parsed_record = parsed_record_scope_id_.template get<0>();
Jakt::ids::ScopeId const scope_id = parsed_record_scope_id_.template get<1>();

Jakt::ids::ScopeId const record_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */:case 1 /* Class */:{
JaktInternal::Optional<Jakt::ids::StructId> const struct_id = TRY((this->find_struct_in_scope(scope_id,parsed_record.name,JaktInternal::OptionalNone())));
if (!struct_id.has_value()){
return JaktInternal::LoopContinue{};
}
Jakt::ids::ScopeId const struct_scope_id = this->get_struct(struct_id.value()).scope_id;
TRY((this->typecheck_struct_methods_predecl(parsed_record,struct_id.value(),struct_scope_id,comptime_pass,generic_pass)));
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(struct_scope_id);
}
VERIFY_NOT_REACHED();
case 3 /* SumEnum */:case 2 /* ValueEnum */:{
JaktInternal::Optional<Jakt::ids::EnumId> const enum_id = TRY((this->program->find_enum_in_scope(scope_id,parsed_record.name,false,JaktInternal::OptionalNone())));
if (!enum_id.has_value()){
return JaktInternal::LoopContinue{};
}
Jakt::ids::ScopeId const enum_scope_id = this->get_enum(enum_id.value()).scope_id;
TRY((this->typecheck_enum_methods_predecl(parsed_record,enum_id.value(),enum_scope_id,comptime_pass,generic_pass)));
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(enum_scope_id);
}
VERIFY_NOT_REACHED();
case 4 /* Garbage */:{
return JaktInternal::LoopContinue{};
}
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
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_record.nested_records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord record = _magic_value.value();
{
records_to_process.enqueue(Tuple{record, record_scope_id});
}

}
}

}
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> __jakt_tmp98 = this->get_scope(scope_id)->resolved_forall_chunks;
if (__jakt_tmp98.has_value()){
JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk> const chunks = __jakt_tmp98.value();
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedForallChunk> _magic = chunks.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedForallChunk> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolvedForallChunk chunk = _magic_value.value();
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> all_types = Jakt::typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create(chunk.parameters);
size_t i = static_cast<size_t>(0ULL);
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = all_types;
for (;;){
JaktInternal::Optional<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> stuff = _magic_value.value();
{
ScopeGuard __jakt_var_36([&] {
i += static_cast<size_t>(1ULL);
});
TRY((this->typecheck_namespace_methods_predecl(chunk.parsed_namespace,chunk.generated_scopes.operator[](i),comptime_pass,generic_pass)));
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

ErrorOr<void> Jakt::typechecker::Typechecker::resolve_external_trait_implementations(Jakt::parser::ParsedExternalTraitImplementation const implementation,Jakt::ids::ScopeId const entity_scope_id,JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>& trait_implementations,Jakt::ids::TypeId const for_type,Jakt::ids::ScopeId const scope_id,bool const default_pass) {
{
if (default_pass){
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const impls = TRY((this->fill_trait_implementation_list(implementation.traits,trait_implementations,entity_scope_id,scope_id)));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedNameWithGenericParameters> _magic = implementation.traits.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedNameWithGenericParameters> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedNameWithGenericParameters trait_name = _magic_value.value();
{
ScopeGuard __jakt_var_37([&] {
index += static_cast<size_t>(1ULL);
});
JaktInternal::Optional<Jakt::ids::TraitId> const trait_id = TRY((this->find_trait_in_scope(scope_id,trait_name.name)));
if (trait_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->get_trait(trait_id.value());
Jakt::types::CheckedTraitRequirements __jakt_tmp99 = trait_->requirements;
if (__jakt_tmp99.__jakt_init_index() == 1 /* Methods */){
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const methods = __jakt_tmp99.as.Methods.value;
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_38([&] {
{
this->generic_inferences.restore(old_generic_inferences);
}

});
this->generic_inferences.set_all(trait_->generic_parameters,impls.operator[](index).template get<1>());
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::FunctionId> _magic = methods.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> name__function_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> const jakt__name__function_id__ = name__function_id__;
ByteString const name = jakt__name__function_id__.template get<0>();
Jakt::ids::FunctionId const function_id = jakt__name__function_id__.template get<1>();

NonnullRefPtr<Jakt::types::CheckedFunction>& function = this->program->modules.operator[](function_id.module.id)->functions.operator[](function_id.id);
if (function->block.statements.is_empty()){
continue;
}
Jakt::types::GenericInferences const inferences = this->generic_inferences;
TRY((function->map_types([inferences](Jakt::ids::TypeId type_id) -> ErrorOr<Jakt::ids::TypeId> {{
return inferences.map(type_id);
}
}
)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> ids = TRY((this->find_functions_with_name_in_scope(entity_scope_id,name,JaktInternal::OptionalNone())));
if (!ids.has_value()){
this->add_function_to_scope(entity_scope_id,name,DynamicArray<Jakt::ids::FunctionId>::create_with({function_id}),trait_name.name_span);
}
}

}
}

}
else {
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
else {
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = implementation.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if (method.parsed_function.params.first().map([](auto& _value) { return _value.variable; }).map([](auto& _value) { return _value.name; }).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }) == ByteString::from_utf8_without_validation("this"sv)){
this_arg_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ids::TypeId>, ErrorOr<void>>{
auto&& __jakt_match_variant = *this->get_type(for_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const struct_ = this->get_struct(id);
Jakt::ids::TypeId type = for_type;
if (!struct_.generic_parameters.is_empty()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> type_arguments = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = struct_.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter param = _magic_value.value();
{
type_arguments.push(param.type_id);
}

}
}

type = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),id,type_arguments));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ids::TypeId>>(type);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(id);
Jakt::ids::TypeId type = for_type;
if (!enum_.generic_parameters.is_empty()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> type_arguments = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = enum_.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter param = _magic_value.value();
{
type_arguments.push(param.type_id);
}

}
}

type = this->find_or_add_type_id(Jakt::types::Type::GenericEnumInstance(Jakt::parser::CheckedQualifiers(false),id,type_arguments));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ids::TypeId>>(type);
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return JaktInternal::ExplicitValue(for_type);
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
TRY((this->typecheck_function_predecl(method.parsed_function,entity_scope_id,this_arg_type_id,JaktInternal::OptionalNone(),Jakt::types::ResolutionMixin(scope_id,true,true,true,true,true,true,true,true,true))));
}

}
}

}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_trait_predecl(Jakt::parser::ParsedTrait const parsed_trait,Jakt::ids::ScopeId const scope_id) {
{
Jakt::ids::ScopeId const trait_scope_id = this->create_scope(scope_id,false,__jakt_format(StringView::from_string_literal("trait({})"sv),parsed_trait.name),false);
TRY((this->add_type_to_scope(trait_scope_id,ByteString::from_utf8_without_validation("Self"sv),this->find_or_add_type_id(Jakt::types::Type::Self(Jakt::parser::CheckedQualifiers(false))),parsed_trait.name_span)));
NonnullRefPtr<Jakt::types::CheckedTrait> checked_trait = Jakt::types::CheckedTrait::__jakt_create(parsed_trait.name,parsed_trait.name_span,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedTraitRequirements, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_trait.requirements;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Methods */:return JaktInternal::ExplicitValue(Jakt::types::CheckedTraitRequirements::Methods(Dictionary<ByteString, Jakt::ids::FunctionId>::create_with_entries({})));
default:return JaktInternal::ExplicitValue(Jakt::types::CheckedTraitRequirements::Nothing());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),DynamicArray<Jakt::types::CheckedGenericParameter>::create_with({}),trait_scope_id);
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::TraitId const trait_id = Jakt::ids::TraitId(this->current_module_id,this->program->modules.operator[](this->current_module_id.id)->traits.size());
Jakt::ids::TypeId const trait_type_id = this->find_or_add_type_id(Jakt::types::Type::Trait(Jakt::parser::CheckedQualifiers(false),trait_id));
this->program->modules.operator[](this->current_module_id.id)->traits.push(checked_trait);
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(trait_type_id);
ScopeGuard __jakt_var_39([&] {
this->self_type_id = old_self_type_id;
});
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
TRY((this->add_type_to_scope(scope_id,parsed_trait.name,trait_type_id,parsed_trait.name_span)));
TRY((this->add_trait_to_scope(scope_id,parsed_trait.name,trait_id,parsed_trait.name_span)));
NonnullRefPtr<Jakt::types::Scope> trait_scope = this->get_scope(trait_scope_id);
trait_scope->relevant_type_id = trait_type_id;
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters = module->traits.operator[](trait_id.id)->generic_parameters;
generic_parameters.ensure_capacity(parsed_trait.generic_parameters.size());
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedGenericParameter> _magic = parsed_trait.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedGenericParameter gen_parameter = _magic_value.value();
{
Jakt::ids::TypeId const parameter_type_id = Jakt::ids::TypeId(this->current_module_id,this->current_module()->types.size());
JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations = DynamicArray<Jakt::ids::TypeId>::create_with({});
Jakt::types::CheckedGenericParameter parameter = Jakt::types::CheckedGenericParameter::make(parameter_type_id,gen_parameter.span);
module->types.push(Jakt::types::Type::TypeVariable(Jakt::parser::CheckedQualifiers(false),gen_parameter.name,trait_implementations,gen_parameter.is_value));
if (gen_parameter.requires_list.has_value()){
TRY((this->fill_trait_requirements(gen_parameter.requires_list.value(),parameter.constraints,trait_implementations,scope_id)));
}
generic_parameters.push(parameter);
TRY((this->add_type_to_scope(trait_scope_id,gen_parameter.name,parameter_type_id,gen_parameter.span)));
}

}
}

Jakt::ids::StructId const synthetic_struct_id = Jakt::ids::StructId(this->current_module_id,this->program->modules.operator[](this->current_module_id.id)->structures.size());
module->structures.push(Jakt::types::CheckedStruct(parsed_trait.name,parsed_trait.name_span,generic_parameters,JaktInternal::OptionalNone(),DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>>::create_with({}),trait_scope_id,Jakt::parser::DefinitionLinkage::External(),Dictionary<ByteString, JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>::create_with_entries({}),Jakt::parser::RecordType::Struct(DynamicArray<Jakt::parser::ParsedField>::create_with({}),JaktInternal::OptionalNone()),trait_type_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()));
Jakt::ids::TypeId const struct_type_id = this->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),synthetic_struct_id));
Jakt::parser::ParsedTraitRequirements __jakt_tmp100 = parsed_trait.requirements;
if (__jakt_tmp100.__jakt_init_index() == 1 /* Methods */){
JaktInternal::DynamicArray<Jakt::parser::ParsedFunction> const methods = __jakt_tmp100.as.Methods.value;
Jakt::types::CheckedTraitRequirements __jakt_tmp101 = checked_trait->requirements;
if (__jakt_tmp101.__jakt_init_index() == 1 /* Methods */){
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const checked_methods = __jakt_tmp101.as.Methods.value;
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> mutable_checked_methods = checked_methods;
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedFunction> _magic = methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedFunction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedFunction parsed_function = _magic_value.value();
{
Jakt::ids::ScopeId const method_scope_id = this->create_scope(trait_scope_id,parsed_function.can_throw,__jakt_format(StringView::from_string_literal("trait-method({}::{})"sv),parsed_trait.name,parsed_function.name),true);
Jakt::ids::FunctionId const function_id = this->program->get_module(this->current_module_id)->next_function_id();
JaktInternal::Optional<Jakt::ids::TypeId> this_arg_type_id = JaktInternal::OptionalNone();
if ((!parsed_function.params.is_empty()) && (parsed_function.params.first().value().variable.name == ByteString::from_utf8_without_validation("this"sv))){
this_arg_type_id = struct_type_id;
}
TRY((this->typecheck_function_predecl(parsed_function,trait_scope_id,this_arg_type_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
mutable_checked_methods.set(parsed_function.name,function_id);
}

}
}

}
else {
Jakt::abort();
}

}
else {
return {};
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_trait(Jakt::parser::ParsedTrait const parsed_trait,Jakt::ids::TraitId const trait_id,Jakt::ids::ScopeId const scope_id,bool const comptime_pass) {
{
NonnullRefPtr<Jakt::types::CheckedTrait> checked_trait = this->program->modules.operator[](trait_id.module.id)->traits.operator[](trait_id.id);
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(this->find_or_add_type_id(Jakt::types::Type::Trait(Jakt::parser::CheckedQualifiers(false),trait_id)));
ScopeGuard __jakt_var_40([&] {
this->self_type_id = old_self_type_id;
});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_trait.requirements;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* ComptimeExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeExpression;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expression = __jakt_match_value.value;
{
if (comptime_pass){
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expression = TRY((this->typecheck_expression(expression,checked_trait->scope_id,Jakt::types::SafetyMode::Safe(),Jakt::typechecker::TypeHint::MustBe(Jakt::types::builtin(Jakt::types::BuiltinType::Bool())))));
checked_trait->requirements = Jakt::types::CheckedTraitRequirements::ComptimeExpression(checked_expression);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_enum_predecl_initial(Jakt::parser::ParsedRecord const parsed_record,size_t const enum_index,size_t const module_enum_len,Jakt::ids::ScopeId const scope_id) {
{
Jakt::ids::ModuleId const module_id = this->current_module_id;
Jakt::ids::EnumId const enum_id = Jakt::ids::EnumId(this->current_module_id,JaktInternal::checked_add(enum_index,module_enum_len));
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
module->types.push(Jakt::types::Type::Enum(Jakt::parser::CheckedQualifiers(false),enum_id));
Jakt::ids::TypeId const enum_type_id = Jakt::ids::TypeId(module_id,JaktInternal::checked_sub(this->current_module()->types.size(),static_cast<size_t>(1ULL)));
TRY((this->add_type_to_scope(scope_id,parsed_record.name,enum_type_id,parsed_record.name_span)));
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(enum_type_id);
ScopeGuard __jakt_var_41([&] {
this->self_type_id = old_self_type_id;
});
bool const is_boxed = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* SumEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SumEnum;bool const& is_boxed = __jakt_match_value.is_boxed;
return JaktInternal::ExplicitValue(is_boxed);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
module->enums.push(Jakt::types::CheckedEnum(parsed_record.name,parsed_record.name_span,DynamicArray<Jakt::types::CheckedGenericParameter>::create_with({}),DynamicArray<Jakt::types::CheckedEnumVariant>::create_with({}),DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>>::create_with({}),this->prelude_scope_id(),parsed_record.definition_linkage,Dictionary<ByteString, JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>::create_with_entries({}),parsed_record.record_type,enum_type_id,enum_type_id,is_boxed));
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_enum_predecl(Jakt::parser::ParsedRecord const parsed_record,Jakt::ids::EnumId const enum_id,Jakt::ids::ScopeId const scope_id) {
{
Jakt::ids::TypeId const enum_type_id = this->find_or_add_type_id(Jakt::types::Type::Enum(Jakt::parser::CheckedQualifiers(false),enum_id));
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(enum_type_id);
ScopeGuard __jakt_var_42([&] {
this->self_type_id = old_self_type_id;
});
Jakt::ids::ScopeId const enum_scope_id = this->create_scope(scope_id,false,__jakt_format(StringView::from_string_literal("enum({})"sv),parsed_record.name),false);
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(enum_scope_id);
scope->namespace_name = parsed_record.name;
scope->relevant_type_id = enum_type_id;
this->add_enum_to_scope(scope_id,parsed_record.name,enum_id,parsed_record.name_span);
Jakt::ids::TypeId const underlying_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* ValueEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ValueEnum;NonnullRefPtr<typename Jakt::parser::ParsedType> const& underlying_type = __jakt_match_value.underlying_type;
return JaktInternal::ExplicitValue(TRY((this->typecheck_typename(underlying_type,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
};/*case end*/
default:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool const is_boxed = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* SumEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SumEnum;bool const& is_boxed = __jakt_match_value.is_boxed;
return JaktInternal::ExplicitValue(is_boxed);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> checked_fields = DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>>::create_with({});
JaktInternal::Set<ByteString> seen_fields = Set<ByteString>::create_with_values({});
Jakt::parser::RecordType __jakt_tmp102 = parsed_record.record_type;
if (__jakt_tmp102.__jakt_init_index() == 3 /* SumEnum */){
JaktInternal::DynamicArray<Jakt::parser::ParsedField> const fields = __jakt_tmp102.as.SumEnum.fields;
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedField> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedField> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedField field = _magic_value.value();
{
Jakt::parser::ParsedVarDecl const var_decl = field.var_decl;
if (seen_fields.contains(var_decl.name)){
this->error(__jakt_format(StringView::from_string_literal("Field '{}' is defined more than once"sv),var_decl.name),var_decl.span);
continue;
}
seen_fields.add(var_decl.name);
Jakt::ids::TypeId const type_id = TRY((this->typecheck_typename(var_decl.parsed_type,enum_scope_id,var_decl.name,JaktInternal::OptionalNone())));
NonnullRefPtr<Jakt::types::CheckedVariable> const checked_var = Jakt::types::CheckedVariable::__jakt_create(var_decl.name,type_id,var_decl.is_mutable,var_decl.span,var_decl.parsed_type->span(),TRY((this->typecheck_visibility(field.visibility,enum_scope_id))),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),var_decl.external_name);
if (this->dump_type_hints && (var_decl.parsed_type->__jakt_init_index() == 15 /* Empty */)){
TRY((this->dump_type_hint(type_id,var_decl.span)));
}
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::VarId const variable_id = module->add_variable(checked_var);
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> const default_value_expression = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>,ErrorOr<void>> {
auto __jakt_enum_value = (field.default_value.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>(Tuple{field.default_value.value(), enum_scope_id}));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
checked_fields.push(Jakt::types::CheckedField::__jakt_create(variable_id,default_value_expression,JaktInternal::OptionalNone()));
}

}
}

}
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
module->enums.operator[](enum_id.id) = Jakt::types::CheckedEnum(parsed_record.name,parsed_record.name_span,DynamicArray<Jakt::types::CheckedGenericParameter>::create_with({}),DynamicArray<Jakt::types::CheckedEnumVariant>::create_with({}),checked_fields,enum_scope_id,parsed_record.definition_linkage,Dictionary<ByteString, JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>::create_with_entries({}),parsed_record.record_type,underlying_type_id,enum_type_id,is_boxed);
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters = module->enums.operator[](enum_id.id).generic_parameters;
generic_parameters.ensure_capacity(parsed_record.generic_parameters.size());
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedGenericParameter> _magic = parsed_record.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedGenericParameter gen_parameter = _magic_value.value();
{
Jakt::ids::TypeId const parameter_type_id = Jakt::ids::TypeId(this->current_module_id,this->current_module()->types.size());
Jakt::types::CheckedGenericParameter checked_param = Jakt::types::CheckedGenericParameter::make(parameter_type_id,gen_parameter.span);
JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations = DynamicArray<Jakt::ids::TypeId>::create_with({});
module->types.push(Jakt::types::Type::TypeVariable(Jakt::parser::CheckedQualifiers(false),gen_parameter.name,trait_implementations,gen_parameter.is_value));
if (gen_parameter.requires_list.has_value()){
TRY((this->fill_trait_requirements(gen_parameter.requires_list.value(),checked_param.constraints,trait_implementations,scope_id)));
}
generic_parameters.push(checked_param);
TRY((this->add_type_to_scope(enum_scope_id,gen_parameter.name,parameter_type_id,gen_parameter.span)));
}

}
}

if (parsed_record.implements_list.has_value()){
TRY((this->fill_trait_implementation_list(parsed_record.implements_list.value(),module->enums.operator[](enum_id.id).trait_implementations,enum_scope_id,JaktInternal::OptionalNone())));
}
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_enum_methods_predecl(Jakt::parser::ParsedRecord const parsed_record,Jakt::ids::EnumId const enum_id,Jakt::ids::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::TypeId const enum_type_id = this->get_enum(enum_id).type_id;
bool const is_extern = parsed_record.definition_linkage.__jakt_init_index() == 1 /* External */;
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = parsed_record.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
Jakt::parser::ParsedFunction const func = method.parsed_function;
if (func.is_comptime != comptime_pass){
continue;
}
if (generic_pass != !func.generic_parameters.is_empty()){
continue;
}
Jakt::ids::ScopeId const method_scope_id = this->create_scope(scope_id,func.can_throw,__jakt_format(StringView::from_string_literal("method({}::{})"sv),parsed_record.name,func.name),true);
Jakt::ids::ScopeId const block_scope_id = this->create_scope(method_scope_id,func.can_throw,__jakt_format(StringView::from_string_literal("method-block({}::{})"sv),parsed_record.name,func.name),true);
bool const is_generic = (!parsed_record.generic_parameters.is_empty()) || (!func.generic_parameters.is_empty());
bool has_varargs = method.parsed_function.has_varargs;
if (has_varargs && (method.parsed_function.linkage.__jakt_init_index() == 0 /* Internal */)){
this->error(ByteString::from_utf8_without_validation("Only external functions are allowed to be declared using varargs"sv),method.parsed_function.name_span);
has_varargs = false;
}
NonnullRefPtr<Jakt::types::CheckedFunction> checked_function = Jakt::types::CheckedFunction::__jakt_create(func.name,func.name_span,TRY((this->typecheck_visibility(method.visibility,scope_id))),Jakt::types::unknown_type_id(),JaktInternal::OptionalNone(),DynamicArray<Jakt::types::CheckedParameter>::create_with({}),Jakt::types::FunctionGenerics::__jakt_create(method_scope_id,DynamicArray<Jakt::types::CheckedParameter>::create_with({}),DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({}),DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({})),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),block_scope_id,Jakt::types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false),func.can_throw,func.type,func.linkage,method_scope_id,JaktInternal::OptionalNone(),(!is_generic) || is_extern,func,func.is_comptime,false,false,func.is_unsafe,has_varargs,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default(),false);
Jakt::ids::FunctionId const function_id = module->add_function(checked_function);
JaktInternal::DynamicArray<Jakt::types::FunctionGenericParameter> generic_parameters = DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedGenericParameter> _magic = func.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedGenericParameter generic_parameter = _magic_value.value();
{
Jakt::ids::TypeId const type_var_type_id = Jakt::ids::TypeId(this->current_module_id,this->current_module()->types.size());
Jakt::types::FunctionGenericParameter parameter = Jakt::types::FunctionGenericParameter::parameter(type_var_type_id,generic_parameter.span);
JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations = DynamicArray<Jakt::ids::TypeId>::create_with({});
module->types.push(Jakt::types::Type::TypeVariable(Jakt::parser::CheckedQualifiers(false),generic_parameter.name,trait_implementations,generic_parameter.is_value));
if (generic_parameter.requires_list.has_value()){
TRY((this->fill_trait_requirements(generic_parameter.requires_list.value(),parameter.checked_parameter.constraints,trait_implementations,scope_id)));
}
generic_parameters.push(parameter);
if (!func.must_instantiate){
TRY((this->add_type_to_scope(method_scope_id,generic_parameter.name,type_var_type_id,generic_parameter.span)));
}
}

}
}

checked_function->generics->params = generic_parameters;
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedParameter> _magic = func.params.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedParameter param = _magic_value.value();
{
if (param.variable.name == ByteString::from_utf8_without_validation("this"sv)){
NonnullRefPtr<Jakt::types::CheckedVariable> const checked_variable = Jakt::types::CheckedVariable::__jakt_create(param.variable.name,enum_type_id,param.variable.is_mutable,param.variable.span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
checked_function->add_param(Jakt::types::CheckedParameter(param.requires_label,checked_variable,JaktInternal::OptionalNone()));
}
else {
Jakt::ids::TypeId const param_type = TRY((this->typecheck_typename(param.variable.parsed_type,method_scope_id,param.variable.name,JaktInternal::OptionalNone())));
NonnullRefPtr<Jakt::types::CheckedVariable> const checked_variable = Jakt::types::CheckedVariable::__jakt_create(param.variable.name,param_type,param.variable.is_mutable,param.variable.span,param.variable.parsed_type->span(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
checked_function->add_param(Jakt::types::CheckedParameter(param.requires_label,checked_variable,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>,ErrorOr<void>> {
auto __jakt_enum_value = (param.default_argument.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Tuple{param.default_argument.value(), method_scope_id});
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
})));
}

}

}
}

this->add_function_to_scope(scope_id,func.name,DynamicArray<Jakt::ids::FunctionId>::create_with({function_id}),parsed_record.name_span);
Jakt::ids::TypeId const function_return_type_id = TRY((this->typecheck_typename(func.return_type,method_scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
checked_function->return_type_id = function_return_type_id;
}

}
}

}
return {};
}

JaktInternal::DynamicArray<Jakt::ids::StructId> Jakt::typechecker::Typechecker::struct_inheritance_chain(Jakt::ids::StructId const struct_id) const {
{
JaktInternal::DynamicArray<Jakt::ids::StructId> chain = DynamicArray<Jakt::ids::StructId>::create_with({});
JaktInternal::Optional<Jakt::ids::StructId> current = static_cast<JaktInternal::Optional<Jakt::ids::StructId>>(struct_id);
chain.push(current.value());
while (current.has_value()){
JaktInternal::Optional<Jakt::ids::StructId> const parent = this->get_struct(current.value()).super_struct_id;
if (parent.has_value()){
chain.push(parent.value());
}
current = parent;
}
JaktInternal::DynamicArray<Jakt::ids::StructId> reverse_chain = DynamicArray<Jakt::ids::StructId>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(chain.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
reverse_chain.push(chain.operator[](JaktInternal::checked_sub(JaktInternal::checked_sub(chain.size(),static_cast<size_t>(1ULL)),i)));
}

}
}

return reverse_chain;
}
}

bool Jakt::typechecker::Typechecker::struct_inherits_from(Jakt::ids::StructId const struct_id,Jakt::ids::StructId const super_struct_id,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::StructId>> const struct_inheritance_chain) const {
{
JaktInternal::DynamicArray<Jakt::ids::StructId> const chain = struct_inheritance_chain.value_or_lazy_evaluated([&] { return this->struct_inheritance_chain(struct_id); });
{
JaktInternal::ArrayIterator<Jakt::ids::StructId> _magic = chain.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::StructId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::StructId id = _magic_value.value();
{
if (id.equals(super_struct_id)){
return true;
}
}

}
}

return false;
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_struct_constructor(Jakt::parser::ParsedRecord const parsed_record,Jakt::ids::StructId const struct_id,Jakt::ids::ScopeId const scope_id) {
{
Jakt::ids::TypeId const struct_type_id = this->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id));
this->current_struct_type_id = struct_type_id;
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(struct_type_id);
ScopeGuard __jakt_var_43([&] {
this->self_type_id = old_self_type_id;
});
Jakt::types::CheckedStruct const struct_ = this->get_struct(struct_id);
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const constructor_ids = TRY((this->find_functions_with_name_in_scope(struct_.scope_id,parsed_record.name,JaktInternal::OptionalNone())));
if (constructor_ids.has_value()){
if ((parsed_record.record_type.__jakt_init_index() == 1 /* Class */) && (parsed_record.definition_linkage.__jakt_init_index() == 1 /* External */)){
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = constructor_ids.value().iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId constructor_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> func = this->get_function(constructor_id);
func->linkage = Jakt::parser::FunctionLinkage::External();
}

}
}

}
}
else if (!(parsed_record.definition_linkage.__jakt_init_index() == 1 /* External */)){
Jakt::ids::ScopeId const function_scope_id = this->create_scope(struct_.scope_id,false,__jakt_format(StringView::from_string_literal("generated-constructor({})"sv),parsed_record.name),true);
Jakt::ids::ScopeId const block_scope_id = this->create_scope(function_scope_id,false,__jakt_format(StringView::from_string_literal("generated-constructor-block({})"sv),parsed_record.name),true);
JaktInternal::DynamicArray<Jakt::ids::StructId> const inheritance_chain = this->struct_inheritance_chain(struct_id);
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> constructor_parameters = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
size_t const parent_index_in_chain = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<void>> {
auto __jakt_enum_value = (inheritance_chain.size() >= static_cast<size_t>(2ULL));
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::checked_sub(inheritance_chain.size(),static_cast<size_t>(2ULL)));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
{
JaktInternal::ArrayIterator<Jakt::ids::StructId> _magic = inheritance_chain.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(parent_index_in_chain),static_cast<size_t>(9223372036854775807LL)}).iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::StructId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::StructId parent_struct_id = _magic_value.value();
{
Jakt::types::CheckedStruct const parent_struct = this->get_struct(parent_struct_id);
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(parent_struct.scope_id);
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const parent_constructors = scope->functions.get(parent_struct.name);
if (parent_constructors.has_value()){
Jakt::ids::FunctionId const id = parent_constructors.value().operator[](static_cast<i64>(0LL));
NonnullRefPtr<Jakt::types::CheckedFunction> const ctor = this->get_function(id);
constructor_parameters.push_values(ctor->params);
}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = this->get_struct(parent_struct_id).fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->get_variable(field->variable_id);
constructor_parameters.push(Jakt::types::CheckedParameter(true,variable,field->default_value_expression));
}

}
}

}

}

}
}

NonnullRefPtr<Jakt::types::CheckedFunction> checked_constructor = Jakt::types::CheckedFunction::__jakt_create(parsed_record.name,parsed_record.name_span,Jakt::types::CheckedVisibility::Public(),struct_type_id,JaktInternal::OptionalNone(),constructor_parameters,Jakt::types::FunctionGenerics::__jakt_create(function_scope_id,constructor_parameters,DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({}),DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({})),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),block_scope_id,Jakt::types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false),false,Jakt::parser::FunctionType::ImplicitConstructor(),Jakt::parser::FunctionLinkage::Internal(),function_scope_id,struct_id,true,JaktInternal::OptionalNone(),false,false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,parsed_record.external_name,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default(),false);
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::FunctionId const function_id = module->add_function(checked_constructor);
this->add_function_to_scope(struct_.scope_id,parsed_record.name,DynamicArray<Jakt::ids::FunctionId>::create_with({function_id}),parsed_record.name_span);
}
this->current_struct_type_id = JaktInternal::OptionalNone();
}
return {};
}

bool Jakt::typechecker::Typechecker::is_class(Jakt::ids::TypeId const type_id) const {
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp103 = this->get_type(type_id);
if (__jakt_tmp103->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp103->as.Struct.value;
return this->get_struct(struct_id).record_type.__jakt_init_index() == 1 /* Class */;
}
else {
return false;
}

}
}

bool Jakt::typechecker::Typechecker::is_struct(Jakt::ids::TypeId const type_id) const {
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp104 = this->get_type(type_id);
if (__jakt_tmp104->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp104->as.Struct.value;
return this->get_struct(struct_id).record_type.__jakt_init_index() == 0 /* Struct */;
}
else {
return false;
}

}
}

ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> Jakt::typechecker::Typechecker::fill_trait_implementation_list(JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> const parsed_impl_list,JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>& trait_implementations,Jakt::ids::ScopeId const scope_id,JaktInternal::Optional<Jakt::ids::ScopeId> const trait_name_scope_id_override) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> result = DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>::create_with({});
Jakt::ids::ScopeId type_scope = scope_id;
JaktInternal::Optional<Jakt::ids::ScopeId> __jakt_tmp105 = trait_name_scope_id_override;
if (__jakt_tmp105.has_value()){
Jakt::ids::ScopeId const id = __jakt_tmp105.value();
Jakt::ids::ScopeId const aliased_scope_id = this->create_scope(id,false,__jakt_format(StringView::from_string_literal("trait-alias-mixin({})"sv),this->get_scope(id)->debug_name),false);
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
scope->resolution_mixins.push(Jakt::types::ResolutionMixin(aliased_scope_id,true,true,true,true,true,true,true,true,true));
}
Jakt::ids::ScopeId const trait_name_scope_id = trait_name_scope_id_override.value_or_lazy_evaluated([&] { return scope_id; });
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedNameWithGenericParameters> _magic = parsed_impl_list.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedNameWithGenericParameters> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedNameWithGenericParameters trait_name = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TypeId> const maybe_type_id = TRY((this->find_type_in_scope(trait_name_scope_id,trait_name.name)));
if (maybe_type_id.has_value()){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp106 = this->get_type(maybe_type_id.value());
if (__jakt_tmp106->__jakt_init_index() == 26 /* Trait */){
Jakt::ids::TraitId const trait_id = __jakt_tmp106->as.Trait.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> generic_arguments = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = trait_name.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> argument = _magic_value.value();
{
Jakt::ids::TypeId const argument_type_id = TRY((this->typecheck_typename(argument,type_scope,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
generic_arguments.push(argument_type_id);
}

}
}

JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> existing_list = trait_implementations.get(trait_name.name);
if (existing_list.has_value()){
bool found = false;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> _magic = existing_list.value().iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> id__args__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const jakt__id__args__ = id__args__;
Jakt::ids::TraitId const id = jakt__id__args__.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = jakt__id__args__.template get<1>();

if (id.equals(trait_id)){
if (args.size() != generic_arguments.size()){
continue;
}
bool args_match = true;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (args.operator[](i).equals(generic_arguments.operator[](i))){
}
else {
args_match = false;
break;
}

}

}
}

if (args_match){
found = true;
break;
}
else {
continue;
}

}
else {
continue;
}

}

}
}

if (!found){
existing_list.value().push(Tuple{trait_id, generic_arguments});
}
}
else {
trait_implementations.set(trait_name.name,DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>::create_with({Tuple{trait_id, generic_arguments}}));
}

result.push(Tuple{trait_id, generic_arguments});
}
else {
this->error(__jakt_format(StringView::from_string_literal("Expected ‘{}’ to be a trait"sv),trait_name.name),trait_name.name_span);
continue;
}

}
else {
this->error(__jakt_format(StringView::from_string_literal("Cannot find trait ‘{}’"sv),trait_name.name),trait_name.name_span);
continue;
}

}

}
}

return result;
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::specialize_trait(Jakt::ids::TraitId const trait_id,JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters) {
{
NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->get_trait(trait_id);
if (trait_->generic_parameters.is_empty()){
return {};
}
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(this->find_or_add_type_id(Jakt::types::Type::GenericTraitInstance(Jakt::parser::CheckedQualifiers(false),trait_id,generic_parameters)));
ScopeGuard __jakt_var_44([&] {
this->self_type_id = old_self_type_id;
});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(trait_->generic_parameters.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::CheckedGenericParameter const parameter = trait_->generic_parameters.operator[](i);
Jakt::ids::TypeId const type = generic_parameters.operator[](i);
TRY((this->check_types_for_compat(parameter.type_id,type,this->generic_inferences,parameter.span)));
}

}
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_struct_predecl(Jakt::parser::ParsedRecord const parsed_record,Jakt::ids::StructId const struct_id,Jakt::ids::ScopeId const scope_id) {
{
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(true);
ScopeGuard __jakt_var_45([&] {
{
this->generic_inferences.restore(old_generic_inferences);
}

});
Jakt::ids::TypeId const struct_type_id = this->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id));
this->current_struct_type_id = struct_type_id;
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(struct_type_id);
ScopeGuard __jakt_var_46([&] {
this->self_type_id = old_self_type_id;
});
Jakt::ids::ScopeId const struct_scope_id = this->current_module()->structures.operator[](struct_id.id).scope_id;
TRY((this->add_struct_to_scope(scope_id,parsed_record.name,struct_id,parsed_record.name_span)));
JaktInternal::Optional<Jakt::ids::StructId> super_struct_id = JaktInternal::OptionalNone();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const& super_parsed_type = __jakt_match_value.super_type;
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>> {
auto __jakt_enum_value = (super_parsed_type.has_value());
if (__jakt_enum_value) {{
Jakt::ids::TypeId const super_type_id = TRY((this->typecheck_typename(super_parsed_type.value(),scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<typename Jakt::types::Type> const super_type = this->get_type(super_type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp107 = super_type;
if (__jakt_tmp107->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp107->as.Struct.value;
super_struct_id = struct_id;
}
else {
this->error(ByteString::from_utf8_without_validation("Class can only inherit from another class"sv),super_parsed_type.value()->span());
}

}
return JaktInternal::ExplicitValue<void>();
}else if (!__jakt_enum_value) {{
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const& super_parsed_type = __jakt_match_value.super_type;
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>> {
auto __jakt_enum_value = (super_parsed_type.has_value());
if (__jakt_enum_value) {{
Jakt::ids::TypeId const super_type_id = TRY((this->typecheck_typename(super_parsed_type.value(),scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<typename Jakt::types::Type> const super_type = this->get_type(super_type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp108 = super_type;
if (__jakt_tmp108->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp108->as.Struct.value;
super_struct_id = struct_id;
}
else {
this->error(ByteString::from_utf8_without_validation("Struct can only inherit from another struct"sv),super_parsed_type.value()->span());
}

}
return JaktInternal::ExplicitValue<void>();
}else if (!__jakt_enum_value) {{
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Expected Struct or Class in typecheck_struct_predecl"sv));
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
module->structures.operator[](struct_id.id) = Jakt::types::CheckedStruct(parsed_record.name,parsed_record.name_span,DynamicArray<Jakt::types::CheckedGenericParameter>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>>::create_with({}),struct_scope_id,parsed_record.definition_linkage,Dictionary<ByteString, JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>::create_with_entries({}),parsed_record.record_type,struct_type_id,super_struct_id,parsed_record.external_name,JaktInternal::OptionalNone(),parsed_record.create_function_name);
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters = module->structures.operator[](struct_id.id).generic_parameters;
generic_parameters.ensure_capacity(parsed_record.generic_parameters.size());
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedGenericParameter> _magic = parsed_record.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedGenericParameter gen_parameter = _magic_value.value();
{
Jakt::ids::TypeId const parameter_type_id = Jakt::ids::TypeId(this->current_module_id,this->current_module()->types.size());
Jakt::types::CheckedGenericParameter parameter = Jakt::types::CheckedGenericParameter::make(parameter_type_id,gen_parameter.span);
JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations = DynamicArray<Jakt::ids::TypeId>::create_with({});
module->types.push(Jakt::types::Type::TypeVariable(Jakt::parser::CheckedQualifiers(false),gen_parameter.name,trait_implementations,gen_parameter.is_value));
if (gen_parameter.requires_list.has_value()){
TRY((this->fill_trait_requirements(gen_parameter.requires_list.value(),parameter.constraints,trait_implementations,scope_id)));
}
generic_parameters.push(parameter);
TRY((this->add_type_to_scope(struct_scope_id,gen_parameter.name,parameter_type_id,gen_parameter.span)));
}

}
}

bool const is_extern = parsed_record.definition_linkage.__jakt_init_index() == 1 /* External */;
module->structures.operator[](struct_id.id).generic_parameters = generic_parameters;
this->current_struct_type_id = JaktInternal::OptionalNone();
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_struct_methods_predecl(Jakt::parser::ParsedRecord const parsed_record,Jakt::ids::StructId const struct_id,Jakt::ids::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(true);
ScopeGuard __jakt_var_47([&] {
{
this->generic_inferences.restore(old_generic_inferences);
}

});
Jakt::ids::TypeId const struct_type_id = this->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id));
this->current_struct_type_id = struct_type_id;
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(struct_type_id);
ScopeGuard __jakt_var_48([&] {
this->self_type_id = old_self_type_id;
});
Jakt::ids::ScopeId const struct_scope_id = this->current_module()->structures.operator[](struct_id.id).scope_id;
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = parsed_record.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
if (method.parsed_function.is_comptime != comptime_pass){
continue;
}
if (generic_pass != !method.parsed_function.generic_parameters.is_empty()){
continue;
}
Jakt::ids::FunctionId const function_id = TRY((this->typecheck_function_predecl(method.parsed_function,struct_scope_id,struct_type_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<Jakt::types::CheckedFunction> checked_function = this->get_function(function_id);
checked_function->is_override = method.is_override;
checked_function->is_virtual = method.is_virtual;
checked_function->visibility = TRY((this->typecheck_visibility(method.visibility,struct_scope_id)));
if (checked_function->is_virtual && checked_function->is_static()){
this->error(ByteString::from_utf8_without_validation("Functions cannot be both virtual and static"sv),checked_function->name_span);
}
if (checked_function->is_override && checked_function->is_static()){
this->error(ByteString::from_utf8_without_validation("Functions cannot be both override and static"sv),checked_function->name_span);
}
}

}
}

if ((!comptime_pass) && parsed_record.implements_list.has_value()){
TRY((this->fill_trait_implementation_list(parsed_record.implements_list.value(),module->structures.operator[](struct_id.id).trait_implementations,struct_scope_id,JaktInternal::OptionalNone())));
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedNameWithGenericParameters> _magic = parsed_record.implements_list.value().iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedNameWithGenericParameters> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedNameWithGenericParameters implements_entry = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TraitId> const trait_id = TRY((this->find_trait_in_scope(scope_id,implements_entry.name)));
if (trait_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->program->modules.operator[](trait_id.value().module.id)->traits.operator[](trait_id.value().id);
Jakt::types::CheckedTraitRequirements __jakt_tmp109 = trait_->requirements;
if (__jakt_tmp109.__jakt_init_index() == 1 /* Methods */){
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const methods = __jakt_tmp109.as.Methods.value;
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::FunctionId> _magic = methods.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> name__function_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> const jakt__name__function_id__ = name__function_id__;
ByteString const name = jakt__name__function_id__.template get<0>();
Jakt::ids::FunctionId const function_id = jakt__name__function_id__.template get<1>();

if (TRY((this->find_functions_with_name_in_scope(struct_scope_id,name,JaktInternal::OptionalNone()))).has_value()){
continue;
}
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->modules.operator[](function_id.module.id)->functions.operator[](function_id.id);
if (function->block.statements.is_empty()){
continue;
}
this->add_function_to_scope(struct_scope_id,name,DynamicArray<Jakt::ids::FunctionId>::create_with({function_id}),implements_entry.name_span);
}

}
}

}
else {
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
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_struct_predecl_initial(Jakt::parser::ParsedRecord const parsed_record,size_t const struct_index,size_t const module_struct_len,Jakt::ids::ScopeId const scope_id) {
{
Jakt::ids::ModuleId const module_id = this->current_module_id;
Jakt::ids::StructId const struct_id = Jakt::ids::StructId(this->current_module_id,JaktInternal::checked_add(struct_index,module_struct_len));
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
module->types.push(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id));
Jakt::ids::TypeId const struct_type_id = Jakt::ids::TypeId(module_id,JaktInternal::checked_sub(this->current_module()->types.size(),static_cast<size_t>(1ULL)));
TRY((this->add_type_to_scope(scope_id,parsed_record.name,struct_type_id,parsed_record.name_span)));
Jakt::ids::ScopeId const struct_scope_id = this->create_scope(scope_id,false,__jakt_format(StringView::from_string_literal("struct({})"sv),parsed_record.name),false);
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(struct_scope_id);
scope->namespace_name = parsed_record.name;
scope->external_name = parsed_record.external_name;
scope->relevant_type_id = struct_type_id;
module->structures.push(Jakt::types::CheckedStruct(parsed_record.name,parsed_record.name_span,DynamicArray<Jakt::types::CheckedGenericParameter>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>>::create_with({}),struct_scope_id,parsed_record.definition_linkage,Dictionary<ByteString, JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>::create_with_entries({}),parsed_record.record_type,struct_type_id,JaktInternal::OptionalNone(),parsed_record.external_name,JaktInternal::OptionalNone(),parsed_record.create_function_name));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::parser::ParsedField> const& fields = __jakt_match_value.fields;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const field_names_and_spans = Jakt::utility::map<Jakt::parser::ParsedField, JaktInternal::Tuple<ByteString,Jakt::utility::Span>>(fields,[](Jakt::parser::ParsedField item) -> JaktInternal::Tuple<ByteString,Jakt::utility::Span> {{
return Tuple{item.var_decl.name, item.var_decl.span};
}
}
);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const method_names_and_spans = Jakt::utility::map<Jakt::parser::ParsedMethod, JaktInternal::Tuple<ByteString,Jakt::utility::Span>>(parsed_record.methods,[](Jakt::parser::ParsedMethod item) -> JaktInternal::Tuple<ByteString,Jakt::utility::Span> {{
return Tuple{item.parsed_function.name, item.parsed_function.name_span};
}
}
);
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> _magic = field_names_and_spans.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span> x = _magic_value.value();
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> _magic = method_names_and_spans.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span> y = _magic_value.value();
{
if (x.template get<0>() == y.template get<0>()){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Can't have a member variable and member function both named `{}`"sv),x.template get<0>()),Jakt::utility::Span::last(x.template get<1>(),y.template get<1>()),__jakt_format(StringView::from_string_literal("`{}` is first defined here"sv),x.template get<0>()),Jakt::utility::Span::first(x.template get<1>(),y.template get<1>()));
}
}

}
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<Jakt::parser::ParsedField> const& fields = __jakt_match_value.fields;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const field_names_and_spans = Jakt::utility::map<Jakt::parser::ParsedField, JaktInternal::Tuple<ByteString,Jakt::utility::Span>>(fields,[](Jakt::parser::ParsedField item) -> JaktInternal::Tuple<ByteString,Jakt::utility::Span> {{
return Tuple{item.var_decl.name, item.var_decl.span};
}
}
);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const method_names_and_spans = Jakt::utility::map<Jakt::parser::ParsedMethod, JaktInternal::Tuple<ByteString,Jakt::utility::Span>>(parsed_record.methods,[](Jakt::parser::ParsedMethod item) -> JaktInternal::Tuple<ByteString,Jakt::utility::Span> {{
return Tuple{item.parsed_function.name, item.parsed_function.name_span};
}
}
);
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> _magic = field_names_and_spans.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span> x = _magic_value.value();
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> _magic = method_names_and_spans.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span> y = _magic_value.value();
{
if (x.template get<0>() == y.template get<0>()){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Can't have a member variable and member function both named `{}`"sv),x.template get<0>()),Jakt::utility::Span::last(x.template get<1>(),y.template get<1>()),__jakt_format(StringView::from_string_literal("`{}` is first defined here"sv),x.template get<0>()),Jakt::utility::Span::first(x.template get<1>(),y.template get<1>()));
}
}

}
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_entity_trait_implementations_predecl(Jakt::ids::ScopeId const scope_id,Jakt::ids::TypeId const type_id,JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const trait_implementations,ByteString const name,Jakt::utility::Span const name_span) {
{
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> _magic = trait_implementations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> trait_name__trait_ids_and_generic_params__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const jakt__trait_name__trait_ids_and_generic_params__ = trait_name__trait_ids_and_generic_params__;
ByteString const trait_name = jakt__trait_name__trait_ids_and_generic_params__.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const trait_ids_and_generic_params = jakt__trait_name__trait_ids_and_generic_params__.template get<1>();

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> _magic = trait_ids_and_generic_params.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> trait_id_and_generic_params = _magic_value.value();
{
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_49([&] {
this->generic_inferences.restore(old_generic_inferences);
});
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const trait_id_generic_params_ = trait_id_and_generic_params;
Jakt::ids::TraitId const trait_id = trait_id_generic_params_.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_params = trait_id_generic_params_.template get<1>();

NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->get_trait(trait_id);
if (trait_->generic_parameters.size() != generic_params.size()){
this->error(__jakt_format(StringView::from_string_literal("Trait ‘{}’ expects {} generic parameters, but {} were given"sv),trait_name,trait_->generic_parameters.size(),generic_params.size()),trait_->name_span);
continue;
}
TRY((this->specialize_trait(trait_id,generic_params)));
Jakt::types::CheckedTraitRequirements __jakt_tmp110 = trait_->requirements;
if (__jakt_tmp110.__jakt_init_index() == 1 /* Methods */){
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const methods = __jakt_tmp110.as.Methods.value;
this->generic_inferences.set_all(trait_->generic_parameters,generic_params);
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::FunctionId> _magic = methods.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> method_name__method_function_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> const jakt__method_name__method_function_id__ = method_name__method_function_id__;
ByteString const method_name = jakt__method_name__method_function_id__.template get<0>();
Jakt::ids::FunctionId const method_function_id = jakt__method_name__method_function_id__.template get<1>();

NonnullRefPtr<Jakt::types::CheckedFunction> const method = this->get_function(method_function_id);
if ((!method->parsed_function.has_value()) || method->parsed_function.value().block.stmts.is_empty()){
continue;
}
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const f = TRY((this->find_functions_with_name_in_scope(scope_id,method_name,JaktInternal::OptionalNone())));
if (f.has_value()){
continue;
}
JaktInternal::Optional<Jakt::ids::ScopeId> mixin_scope_id = JaktInternal::OptionalNone();
if (!trait_->generic_parameters.is_empty()){
Jakt::ids::ScopeId const id = this->program->create_scope(JaktInternal::OptionalNone(),false,__jakt_format(StringView::from_string_literal("trait({}).generic-mixin"sv),trait_->name),scope_id.module_id,false);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(trait_->generic_parameters.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::CheckedGenericParameter const generic_param = trait_->generic_parameters.operator[](i);
Jakt::ids::TypeId const generic_param_type = generic_params.operator[](i);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp111 = this->get_type(generic_param.type_id);
if (__jakt_tmp111->__jakt_init_index() == 18 /* TypeVariable */){
ByteString const name = __jakt_tmp111->as.TypeVariable.name;
bool const is_value = __jakt_tmp111->as.TypeVariable.is_value;
TRY((this->add_type_to_scope(id,name,generic_param_type,generic_param.span)));
if (is_value){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp112 = this->get_type(generic_param_type);
if (__jakt_tmp112->__jakt_init_index() == 31 /* Const */){
Jakt::types::Value const value = __jakt_tmp112->as.Const.value;
this->add_comptime_binding_to_scope(id,name,value,generic_param.span);
}
}
mixin_scope_id = id;
}
else {
continue;
}

}

}
}

}
TRY((this->typecheck_function_predecl(method->parsed_function.value(),scope_id,type_id,JaktInternal::OptionalNone(),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::ResolutionMixin>,ErrorOr<void>> {
auto __jakt_enum_value = (mixin_scope_id.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::ResolutionMixin(mixin_scope_id.value(),true,true,true,true,true,true,true,true,true));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
}))));
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
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_entity_trait_implementations(Jakt::ids::ScopeId const scope_id,Jakt::ids::TypeId const type_id,JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const trait_implementations,ByteString const name,Jakt::utility::Span const name_span) {
{
Jakt::typechecker::TraitImplCheck checks = Jakt::typechecker::TraitImplCheck::make();
checks.ensure_capacity(trait_implementations.size());
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> _magic = trait_implementations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> trait_name__trait_ids_and_generic_params__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const jakt__trait_name__trait_ids_and_generic_params__ = trait_name__trait_ids_and_generic_params__;
ByteString const trait_name = jakt__trait_name__trait_ids_and_generic_params__.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const trait_ids_and_generic_params = jakt__trait_name__trait_ids_and_generic_params__.template get<1>();

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> _magic = trait_ids_and_generic_params.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> trait_id_and_generic_params = _magic_value.value();
{
checks.register_trait(this->find_or_add_type_id(Jakt::types::Type::GenericTraitInstance(Jakt::parser::CheckedQualifiers(false),trait_id_and_generic_params.template get<0>(),trait_id_and_generic_params.template get<1>())),trait_name,this->program->get_trait(trait_id_and_generic_params.template get<0>())->requirements);
}

}
}

}

}
}

{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> _magic = trait_implementations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> trait_name__trait_ids_and_generic_params__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const jakt__trait_name__trait_ids_and_generic_params__ = trait_name__trait_ids_and_generic_params__;
ByteString const trait_name = jakt__trait_name__trait_ids_and_generic_params__.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const trait_ids_and_generic_params = jakt__trait_name__trait_ids_and_generic_params__.template get<1>();

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> _magic = trait_ids_and_generic_params.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> trait_id_and_generic_params = _magic_value.value();
{
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_50([&] {
this->generic_inferences.restore(old_generic_inferences);
});
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const trait_id_generic_params_ = trait_id_and_generic_params;
Jakt::ids::TraitId const trait_id = trait_id_generic_params_.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_params = trait_id_generic_params_.template get<1>();

NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->get_trait(trait_id);
if (trait_->generic_parameters.size() != generic_params.size()){
this->error(__jakt_format(StringView::from_string_literal("Trait ‘{}’ expects {} generic parameters, but {} were given"sv),trait_name,trait_->generic_parameters.size(),generic_params.size()),trait_->name_span);
continue;
}
TRY((this->specialize_trait(trait_id,generic_params)));
Jakt::types::CheckedTraitRequirements __jakt_tmp113 = trait_->requirements;
if (__jakt_tmp113.__jakt_init_index() == 1 /* Methods */){
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const methods = __jakt_tmp113.as.Methods.value;
this->generic_inferences.set_all(trait_->generic_parameters,generic_params);
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::FunctionId> _magic = methods.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> method_name__method_function_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> const jakt__method_name__method_function_id__ = method_name__method_function_id__;
ByteString const method_name = jakt__method_name__method_function_id__.template get<0>();
Jakt::ids::FunctionId const method_function_id = jakt__method_name__method_function_id__.template get<1>();

NonnullRefPtr<Jakt::types::CheckedFunction> const method = this->get_function(method_function_id);
if ((!method->parsed_function.has_value()) || method->parsed_function.value().block.stmts.is_empty()){
continue;
}
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const ids = TRY((this->find_functions_with_name_in_scope(scope_id,method_name,JaktInternal::OptionalNone())));
JaktInternal::Optional<Jakt::ids::FunctionId> this_function = JaktInternal::OptionalNone();
if (ids.has_value()){
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = ids.value().iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId id = _magic_value.value();
{
if (this->get_function(id)->parsed_function.map([](auto& _value) { return _value.id; }) == method->parsed_function.map([](auto& _value) { return _value.id; })){
this_function = id;
break;
}
}

}
}

if (!this_function.has_value()){
continue;
}
}
if (this_function.has_value() && this->get_function(this_function.value())->is_fully_checked){
continue;
}
TRY((this->typecheck_function(method->parsed_function.value(),scope_id)));
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
}

NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(scope_id);
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = scope->functions.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> name__overload_set__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const jakt__name__overload_set__ = name__overload_set__;
ByteString const name = jakt__name__overload_set__.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set = jakt__name__overload_set__.template get<1>();

{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = overload_set.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId function_id = _magic_value.value();
{
TRY((checks.register_method(type_id,name,function_id,*this)));
}

}
}

}

}
}

TRY((checks.throw_errors(name_span,*this)));
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_trait_implementations_predecl(Jakt::ids::ScopeId const scope_id) {
{
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(scope_id);
{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child = _magic_value.value();
{
TRY((this->typecheck_namespace_trait_implementations_predecl(child)));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::StructId> _magic = scope->structs.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::StructId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> ___struct_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> const jakt_____struct_id__ = ___struct_id__;
ByteString const _ = jakt_____struct_id__.template get<0>();
Jakt::ids::StructId const struct_id = jakt_____struct_id__.template get<1>();

Jakt::types::CheckedStruct const struct_ = this->get_struct(struct_id);
TRY((this->typecheck_entity_trait_implementations_predecl(struct_.scope_id,struct_.type_id,struct_.trait_implementations,struct_.name,struct_.name_span)));
}

}
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_trait_implementations(Jakt::ids::ScopeId const scope_id) {
{
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(scope_id);
{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child = _magic_value.value();
{
TRY((this->typecheck_namespace_trait_implementations(child)));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::StructId> _magic = scope->structs.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::StructId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> ___struct_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> const jakt_____struct_id__ = ___struct_id__;
ByteString const _ = jakt_____struct_id__.template get<0>();
Jakt::ids::StructId const struct_id = jakt_____struct_id__.template get<1>();

Jakt::types::CheckedStruct const struct_ = this->get_struct(struct_id);
if (struct_.trait_implementations.is_empty()){
continue;
}
TRY((this->typecheck_entity_trait_implementations(struct_.scope_id,struct_.type_id,struct_.trait_implementations,struct_.name,struct_.name_span)));
}

}
}

}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_namespace_declarations(Jakt::parser::ParsedNamespace const parsed_namespace,Jakt::ids::ScopeId const scope_id,bool const comptime_pass,bool const generic_pass) {
{
JaktInternal::DynamicArray<Jakt::ids::ScopeId> const children = this->get_scope(scope_id)->children;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parsed_namespace.namespaces.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::parser::ParsedNamespace const child_namespace = parsed_namespace.namespaces.operator[](i);
Jakt::ids::ScopeId const child_namespace_scope_id = children.operator[](i);
TRY((this->typecheck_namespace_declarations(child_namespace,child_namespace_scope_id,comptime_pass,generic_pass)));
}

}
}

JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> __jakt_tmp114 = this->get_scope(scope_id)->resolved_forall_chunks;
if (__jakt_tmp114.has_value()){
JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk> const chunks = __jakt_tmp114.value();
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedForallChunk> _magic = chunks.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedForallChunk> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolvedForallChunk chunk = _magic_value.value();
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> all_types = Jakt::typechecker::InternalDictionaryProduct<ByteString, JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>::create(chunk.parameters);
size_t i = static_cast<size_t>(0ULL);
{
Jakt::typechecker::InternalDictionaryProduct<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> _magic = all_types;
for (;;){
JaktInternal::Optional<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>> stuff = _magic_value.value();
{
ScopeGuard __jakt_var_51([&] {
i += static_cast<size_t>(1ULL);
});
TRY((this->typecheck_namespace_declarations(chunk.parsed_namespace,chunk.generated_scopes.operator[](i),comptime_pass,generic_pass)));
}

}
}

}

}
}

}
if ((!comptime_pass) && (!generic_pass)){
AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>> records_to_process = AK::Queue<JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId>>();
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = parsed_namespace.records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord parsed_record = _magic_value.value();
{
records_to_process.enqueue(Tuple{parsed_record, scope_id});
}

}
}

while (!records_to_process.is_empty()){
JaktInternal::Tuple<Jakt::parser::ParsedRecord,Jakt::ids::ScopeId> const record_scope_id_ = records_to_process.dequeue();
Jakt::parser::ParsedRecord const record = record_scope_id_.template get<0>();
Jakt::ids::ScopeId const scope_id = record_scope_id_.template get<1>();

Jakt::types::StructLikeId const id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::StructLikeId, ErrorOr<void>>{
auto&& __jakt_match_variant = record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */:case 1 /* Class */:{
JaktInternal::Optional<Jakt::ids::StructId> const struct_id = TRY((this->find_struct_in_scope(scope_id,record.name,JaktInternal::OptionalNone())));
if (!struct_id.has_value()){
this->compiler->panic(ByteString::from_utf8_without_validation("can't find struct that has been previous added"sv));
}
TRY((this->typecheck_struct(record,struct_id.value(),scope_id)));
return JaktInternal::ExplicitValue<Jakt::types::StructLikeId>(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id.value()));
}
VERIFY_NOT_REACHED();
case 3 /* SumEnum */:case 2 /* ValueEnum */:{
JaktInternal::Optional<Jakt::ids::EnumId> const enum_id = TRY((this->program->find_enum_in_scope(scope_id,record.name,false,JaktInternal::OptionalNone())));
if (!enum_id.has_value()){
this->compiler->panic(ByteString::from_utf8_without_validation("can't find enum that has been previous added"sv));
}
TRY((this->typecheck_enum(record,enum_id.value(),scope_id)));
return JaktInternal::ExplicitValue<Jakt::types::StructLikeId>(Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id.value()));
}
VERIFY_NOT_REACHED();
default:{
return JaktInternal::LoopContinue{};
}
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
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = record.nested_records.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedRecord nested_record = _magic_value.value();
{
TRY((this->warn_about_unimplemented_nested_record(nested_record)));
records_to_process.enqueue(Tuple{nested_record, id.scope_id(this->program)});
}

}
}

}
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedTrait> _magic = parsed_namespace.traits.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedTrait> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedTrait parsed_trait = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TraitId> const trait_id = TRY((this->find_trait_in_scope(scope_id,parsed_trait.name)));
if (trait_id.has_value()){
TRY((this->typecheck_trait(parsed_trait,trait_id.value(),scope_id,false)));
}
else {
this->compiler->panic(ByteString::from_utf8_without_validation("can't find trait that has been previous added"sv));
}

}

}
}

TRY((this->typecheck_namespace_trait_implementations_predecl(scope_id)));
}
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedFunction> _magic = parsed_namespace.functions.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedFunction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedFunction fun = _magic_value.value();
{
if ((fun.is_comptime == comptime_pass) && (generic_pass == !fun.generic_parameters.is_empty())){
TRY((this->typecheck_function(fun,scope_id)));
}
}

}
}

if ((!comptime_pass) && (!generic_pass)){
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedExternalTraitImplementation> _magic = parsed_namespace.external_trait_implementations.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedExternalTraitImplementation> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedExternalTraitImplementation implementation = _magic_value.value();
{
Jakt::ids::TypeId for_type = TRY((this->typecheck_typename(implementation.for_type,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(for_type);
if (type->is_builtin()){
Jakt::ids::StructId const struct_id = this->program->builtin_implementation_struct(type->as_builtin_type(),this->program->prelude_module_id());
for_type = this->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id));
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *this->get_type(for_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct struct_ = this->get_struct(struct_id);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = implementation.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
if (method.parsed_function.params.first().map([](auto& _value) { return _value.variable; }).map([](auto& _value) { return _value.name; }).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }) == ByteString::from_utf8_without_validation("this"sv)){
TRY((this->typecheck_method(method.parsed_function,Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id))));
}
else {
TRY((this->typecheck_function(method.parsed_function,struct_.scope_id)));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
Jakt::types::CheckedStruct struct_ = this->get_struct(struct_id);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = implementation.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
if (method.parsed_function.params.first().map([](auto& _value) { return _value.variable; }).map([](auto& _value) { return _value.name; }).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }) == ByteString::from_utf8_without_validation("this"sv)){
TRY((this->typecheck_method(method.parsed_function,Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id))));
}
else {
TRY((this->typecheck_function(method.parsed_function,struct_.scope_id)));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum enum_ = this->get_enum(enum_id);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = implementation.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
if (method.parsed_function.params.first().map([](auto& _value) { return _value.variable; }).map([](auto& _value) { return _value.name; }).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }) == ByteString::from_utf8_without_validation("this"sv)){
TRY((this->typecheck_method(method.parsed_function,Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id))));
}
else {
TRY((this->typecheck_function(method.parsed_function,enum_.scope_id)));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
Jakt::types::CheckedEnum enum_ = this->get_enum(enum_id);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = implementation.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
if (method.parsed_function.params.first().map([](auto& _value) { return _value.variable; }).map([](auto& _value) { return _value.name; }).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }) == ByteString::from_utf8_without_validation("this"sv)){
TRY((this->typecheck_method(method.parsed_function,Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id))));
}
else {
TRY((this->typecheck_function(method.parsed_function,enum_.scope_id)));
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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
if ((!comptime_pass) && (!generic_pass)){
TRY((this->typecheck_namespace_trait_implementations(scope_id)));
}
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_enum_constructor(Jakt::parser::ParsedRecord const parsed_record,Jakt::ids::EnumId const enum_id,Jakt::ids::ScopeId const parent_scope_id) {
{
u64 next_constant_value = static_cast<u64>(0ULL);
JaktInternal::Set<ByteString> seen_names = Set<ByteString>::create_with_values({});
Jakt::types::CheckedEnum enum_ = this->get_enum(enum_id);
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(enum_.type_id);
ScopeGuard __jakt_var_52([&] {
this->self_type_id = old_self_type_id;
});
JaktInternal::Set<ByteString> common_seen_fields = Set<ByteString>::create_with_values({});
JaktInternal::DynamicArray<Jakt::ids::VarId> common_fields = DynamicArray<Jakt::ids::VarId>::create_with({});
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> common_params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->get_variable(field->variable_id);
common_params.push(Jakt::types::CheckedParameter(true,variable,field->default_value_expression));
common_seen_fields.add(variable->name);
common_fields.push(field->variable_id);
}

}
}

({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = parsed_record.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* ValueEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ValueEnum;NonnullRefPtr<typename Jakt::parser::ParsedType> const& underlying_type = __jakt_match_value.underlying_type;
JaktInternal::DynamicArray<Jakt::parser::ValueEnumVariant> const& variants = __jakt_match_value.variants;
{
Jakt::ids::TypeId const underlying_type_id = TRY((this->typecheck_typename(underlying_type,parent_scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
{
JaktInternal::ArrayIterator<Jakt::parser::ValueEnumVariant> _magic = variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ValueEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ValueEnumVariant variant = _magic_value.value();
{
if (seen_names.contains(variant.name)){
this->error(__jakt_format(StringView::from_string_literal("Enum variant '{}' is defined more than once"sv),variant.name),variant.span);
}
else {
seen_names.add(variant.name);
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>,ErrorOr<void>> {
auto __jakt_enum_value = (variant.value.has_value());
if (__jakt_enum_value) {{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const value_expression = TRY((this->cast_to_underlying(variant.value.value(),parent_scope_id,underlying_type)));
JaktInternal::Optional<Jakt::types::NumberConstant> const number_constant = value_expression->to_number_constant(this->program);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<void>> {
auto __jakt_enum_value = (number_constant.has_value());
if (__jakt_enum_value) {{
next_constant_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<void>>{
auto&& __jakt_match_variant = number_constant.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Signed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Signed;i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(infallible_integer_cast<u64>(JaktInternal::checked_add(val,static_cast<i64>(1LL))));
};/*case end*/
case 1 /* Unsigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsigned;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(JaktInternal::checked_add(val,static_cast<u64>(1ULL)));
};/*case end*/
case 2 /* Floating */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Floating;f64 const& val = __jakt_match_value.value;
{
Jakt::utility::todo(ByteString::from_utf8_without_validation("Implement floats"sv));
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
});
}
return JaktInternal::ExplicitValue<void>();
}else {{
this->error(__jakt_format(StringView::from_string_literal("Enum variant '{}' in enum '{}' has a non-constant value: {}"sv),variant.name,enum_.name,value_expression),variant.span);
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(value_expression);
}
VERIFY_NOT_REACHED();
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(TRY((this->cast_to_underlying(Jakt::parser::ParsedExpression::NumericConstant(Jakt::parser::NumericConstant::UnknownUnsigned(next_constant_value++),variant.span),parent_scope_id,underlying_type))));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
enum_.variants.push(Jakt::types::CheckedEnumVariant::WithValue(enum_id,variant.name,expr,variant.span));
Jakt::ids::VarId const var_id = module->add_variable(Jakt::types::CheckedVariable::__jakt_create(variant.name,enum_.type_id,false,variant.span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()));
this->add_var_to_scope(enum_.scope_id,variant.name,var_id,variant.span);
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* SumEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SumEnum;bool const& is_boxed = __jakt_match_value.is_boxed;
JaktInternal::DynamicArray<Jakt::parser::SumEnumVariant> const& variants = __jakt_match_value.variants;
{
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
{
JaktInternal::ArrayIterator<Jakt::parser::SumEnumVariant> _magic = variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::SumEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::SumEnumVariant variant = _magic_value.value();
{
if (seen_names.contains(variant.name)){
this->error(__jakt_format(StringView::from_string_literal("Enum variant '{}' is defined more than once"sv),variant.name),variant.span);
continue;
}
seen_names.add(variant.name);
bool const is_structlike = (variant.params.has_value() && (variant.params.value().size() > static_cast<size_t>(0ULL))) && [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(variant.params.value().operator[](static_cast<i64>(0LL)).name,ByteString::from_utf8_without_validation(""sv));
bool const is_typed = (variant.params.has_value() && (variant.params.value().size() == static_cast<size_t>(1ULL))) && (variant.params.value().operator[](static_cast<i64>(0LL)).name == ByteString::from_utf8_without_validation(""sv));
if (is_structlike){
JaktInternal::Set<ByteString> seen_fields = Set<ByteString>::create_with_values({});
{
JaktInternal::SetIterator<ByteString> _magic = common_seen_fields.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString name = _magic_value.value();
{
seen_fields.add(name);
}

}
}

JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = common_params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
params.push(param);
}

}
}

JaktInternal::DynamicArray<Jakt::ids::VarId> fields = DynamicArray<Jakt::ids::VarId>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = common_fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::VarId field = _magic_value.value();
{
fields.push(field);
}

}
}

JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl>> __jakt_tmp116 = variant.params;
if (__jakt_tmp116.has_value()){
JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl> const variant_params = __jakt_tmp116.value();
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>>>> __jakt_tmp115 = variant.default_values;
if (__jakt_tmp115.has_value()){
JaktInternal::DynamicArray<JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const variant_default_values = __jakt_tmp115.value();
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(variant_params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::parser::ParsedVarDecl const param = variant_params.operator[](i);
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const default_value = variant_default_values.operator[](i);
if (seen_fields.contains(param.name)){
this->error(__jakt_format(StringView::from_string_literal("Enum variant '{}' has a member named '{}' more than once"sv),variant.name,param.name),param.span);
continue;
}
seen_fields.add(param.name);
Jakt::ids::TypeId const type_id = TRY((this->typecheck_typename(param.parsed_type,enum_.scope_id,param.name,JaktInternal::OptionalNone())));
NonnullRefPtr<Jakt::types::CheckedVariable> const checked_var = Jakt::types::CheckedVariable::__jakt_create(param.name,type_id,param.is_mutable,param.span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
params.push(Jakt::types::CheckedParameter(true,checked_var,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>,ErrorOr<void>> {
auto __jakt_enum_value = (default_value.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Tuple{default_value.value(), enum_.scope_id});
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
})));
if (this->dump_type_hints && (param.parsed_type->__jakt_init_index() == 15 /* Empty */)){
TRY((this->dump_type_hint(type_id,param.span)));
}
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::VarId const var_id = module->add_variable(checked_var);
fields.push(var_id);
}

}
}

}
}
enum_.variants.push(Jakt::types::CheckedEnumVariant::StructLike(enum_id,variant.name,fields,variant.span));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const maybe_enum_variant_constructor = TRY((this->find_functions_with_name_in_scope(enum_.scope_id,variant.name,JaktInternal::OptionalNone())));
if (!maybe_enum_variant_constructor.has_value()){
Jakt::ids::ScopeId const function_scope_id = this->create_scope(parent_scope_id,false,__jakt_format(StringView::from_string_literal("enum-variant-constructor({}::{})"sv),enum_.name,variant.name),true);
Jakt::ids::ScopeId const block_scope_id = this->create_scope(function_scope_id,false,__jakt_format(StringView::from_string_literal("enum-variant-constructor-block({}::{})"sv),enum_.name,variant.name),true);
NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = Jakt::types::CheckedFunction::__jakt_create(variant.name,variant.span,Jakt::types::CheckedVisibility::Public(),this->find_or_add_type_id(Jakt::types::Type::Enum(Jakt::parser::CheckedQualifiers(false),enum_id)),JaktInternal::OptionalNone(),params,Jakt::types::FunctionGenerics::__jakt_create(function_scope_id,params,DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({}),DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({})),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),block_scope_id,Jakt::types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false),false,Jakt::parser::FunctionType::ImplicitEnumConstructor(),Jakt::parser::FunctionLinkage::Internal(),function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default(),false);
Jakt::ids::FunctionId const function_id = module->add_function(checked_function);
this->add_function_to_scope(enum_.scope_id,variant.name,DynamicArray<Jakt::ids::FunctionId>::create_with({function_id}),variant.span);
}
}
else if (is_typed){
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = common_params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
params.push(param);
}

}
}

Jakt::parser::ParsedVarDecl const param = variant.params.value().operator[](static_cast<i64>(0LL));
Jakt::ids::TypeId const type_id = TRY((this->typecheck_typename(param.parsed_type,enum_.scope_id,param.name,JaktInternal::OptionalNone())));
enum_.variants.push(Jakt::types::CheckedEnumVariant::Typed(enum_id,variant.name,type_id,variant.span));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const maybe_enum_variant_constructor = TRY((this->find_functions_with_name_in_scope(enum_.scope_id,variant.name,JaktInternal::OptionalNone())));
if (!maybe_enum_variant_constructor.has_value()){
Jakt::ids::ScopeId const function_scope_id = this->create_scope(parent_scope_id,false,__jakt_format(StringView::from_string_literal("enum-variant-constructor({}::{})"sv),enum_.name,variant.name),true);
Jakt::ids::ScopeId const block_scope_id = this->create_scope(function_scope_id,false,__jakt_format(StringView::from_string_literal("enum-variant-constructor-block({}::{})"sv),enum_.name,variant.name),true);
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = Jakt::types::CheckedVariable::__jakt_create(ByteString::from_utf8_without_validation("value"sv),type_id,false,param.span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
params.push(Jakt::types::CheckedParameter(false,variable,JaktInternal::OptionalNone()));
NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = Jakt::types::CheckedFunction::__jakt_create(variant.name,variant.span,Jakt::types::CheckedVisibility::Public(),this->find_or_add_type_id(Jakt::types::Type::Enum(Jakt::parser::CheckedQualifiers(false),enum_id)),JaktInternal::OptionalNone(),params,Jakt::types::FunctionGenerics::__jakt_create(function_scope_id,params,DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({}),DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({})),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),block_scope_id,Jakt::types::BlockControlFlow::AlwaysReturns(),JaktInternal::OptionalNone(),false),false,Jakt::parser::FunctionType::ImplicitEnumConstructor(),Jakt::parser::FunctionLinkage::Internal(),function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default(),false);
Jakt::ids::FunctionId const function_id = module->add_function(checked_function);
this->add_function_to_scope(enum_.scope_id,variant.name,DynamicArray<Jakt::ids::FunctionId>::create_with({function_id}),variant.span);
}
}
else {
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = common_params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
params.push(param);
}

}
}

enum_.variants.push(Jakt::types::CheckedEnumVariant::Untyped(enum_id,variant.name,variant.span));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const maybe_enum_variant_constructor = TRY((this->find_functions_with_name_in_scope(enum_.scope_id,variant.name,JaktInternal::OptionalNone())));
if (!maybe_enum_variant_constructor.has_value()){
Jakt::ids::ScopeId const function_scope_id = this->create_scope(parent_scope_id,false,__jakt_format(StringView::from_string_literal("enum-variant-constructor({}::{})"sv),enum_.name,variant.name),true);
Jakt::ids::ScopeId const block_scope_id = this->create_scope(function_scope_id,false,__jakt_format(StringView::from_string_literal("enum-variant-constructor-block({}::{})"sv),enum_.name,variant.name),true);
NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = Jakt::types::CheckedFunction::__jakt_create(variant.name,variant.span,Jakt::types::CheckedVisibility::Public(),this->find_or_add_type_id(Jakt::types::Type::Enum(Jakt::parser::CheckedQualifiers(false),enum_id)),JaktInternal::OptionalNone(),params,Jakt::types::FunctionGenerics::__jakt_create(function_scope_id,params,DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({}),DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({})),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),block_scope_id,Jakt::types::BlockControlFlow::AlwaysReturns(),JaktInternal::OptionalNone(),false),false,Jakt::parser::FunctionType::ImplicitEnumConstructor(),Jakt::parser::FunctionLinkage::Internal(),function_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default(),false);
Jakt::ids::FunctionId const function_id = module->add_function(checked_function);
this->add_function_to_scope(enum_.scope_id,variant.name,DynamicArray<Jakt::ids::FunctionId>::create_with({function_id}),variant.span);
}
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_enum(Jakt::parser::ParsedRecord const record,Jakt::ids::EnumId const enum_id,Jakt::ids::ScopeId const parent_scope_id) {
{
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(this->get_enum(enum_id).type_id);
ScopeGuard __jakt_var_53([&] {
this->self_type_id = old_self_type_id;
});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = record.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
TRY((this->typecheck_method(method.parsed_function,Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),enum_id))));
}

}
}

}
return {};
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::cast_to_underlying(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,Jakt::ids::ScopeId const scope_id,NonnullRefPtr<typename Jakt::parser::ParsedType> const parsed_type) {
{
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const cast_expression = Jakt::parser::ParsedExpression::UnaryOp(expr,Jakt::parser::UnaryOperator::TypeCast(Jakt::parser::TypeCast::Infallible(parsed_type)),expr->span());
return this->typecheck_expression(cast_expression,scope_id,Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone());
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_struct(Jakt::parser::ParsedRecord const record,Jakt::ids::StructId const struct_id,Jakt::ids::ScopeId const parent_scope_id) {
{
Jakt::ids::TypeId const struct_type_id = this->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id));
this->current_struct_type_id = struct_type_id;
JaktInternal::Optional<Jakt::ids::TypeId> const old_self_type_id = this->self_type_id;
this->set_self_type_id(struct_type_id);
ScopeGuard __jakt_var_54([&] {
this->self_type_id = old_self_type_id;
});
JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>>> all_virtuals = Dictionary<ByteString, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>>>::create_with_entries({});
JaktInternal::Optional<Jakt::ids::StructId> super_struct_id = this->get_struct(struct_id).super_struct_id;
while (super_struct_id.has_value()){
Jakt::types::CheckedStruct const super_struct = this->get_struct(super_struct_id.value());
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(super_struct.scope_id);
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = scope->functions.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> ___overload_set__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = jakt_____overload_set__.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set = jakt_____overload_set__.template get<1>();

{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = overload_set.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId function_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->get_function(function_id);
if (function->is_virtual){
if (!all_virtuals.contains(function->name)){
all_virtuals.set(function->name, DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>>::create_with({function}));
}
else {
all_virtuals.operator[](function->name).push(function);
}

}
}

}
}

}

}
}

super_struct_id = super_struct.super_struct_id;
}
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = record.methods.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMethod method = _magic_value.value();
{
TRY((this->typecheck_override(method,this->get_struct(struct_id).scope_id,all_virtuals)));
TRY((this->typecheck_method(method.parsed_function,Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id))));
}

}
}

this->current_struct_type_id = JaktInternal::OptionalNone();
}
return {};
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_override(Jakt::parser::ParsedMethod const method,Jakt::ids::ScopeId const parent_scope_id,JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>>> const all_virtuals) {
{
if (method.is_override){
JaktInternal::Optional<JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>>> overrides = all_virtuals.get(method.parsed_function.name);
if (overrides.has_value()){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const override_target = overrides.value().pop();
if (override_target.has_value()){
JaktInternal::Optional<Jakt::ids::FunctionId> const method_id = TRY((this->find_function_matching_signature_in_scope(parent_scope_id,method.parsed_function)));
NonnullRefPtr<Jakt::types::CheckedFunction> const method_function = this->get_function(method_id.value());
if (!method_function->return_type_id.equals(override_target.value()->return_type_id)){
this->error(ByteString::from_utf8_without_validation("Override function return type does not match virtual function"sv),method_function->return_type_span.value_or_lazy_evaluated([&] { return method_function->name_span; }));
}
if (method_function->can_throw != override_target.value()->can_throw){
this->error(ByteString::from_utf8_without_validation("Override function throwability does not match virtual function"sv),method_function->name_span);
}
if (method_function->params.size() != override_target.value()->params.size()){
this->error(ByteString::from_utf8_without_validation("Override function parameters do not match virtual function"sv),method_function->name_span);
return {};
}
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(method_function->params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t param_index = _magic_value.value();
{
Jakt::types::CheckedParameter const method_param = method_function->params.operator[](param_index);
Jakt::types::CheckedParameter const virtual_param = override_target.value()->params.operator[](param_index);
if (virtual_param.variable->is_mutable != method_param.variable->is_mutable){
this->error(ByteString::from_utf8_without_validation("Override function parameter mutability does not match virtual function"sv),method_param.variable->definition_span);
}
if ((param_index == static_cast<size_t>(0ULL)) && (method_param.variable->name == ByteString::from_utf8_without_validation("this"sv))){
continue;
}
if (!method_param.variable->type_id.equals(virtual_param.variable->type_id)){
this->error(ByteString::from_utf8_without_validation("Override function parameter type does not match virtual function"sv),method_param.variable->type_span.value_or_lazy_evaluated([&] { return method_param.variable->definition_span; }));
}
}

}
}

}
else {
this->error(ByteString::from_utf8_without_validation("Missing virtual for override"sv),method.parsed_function.name_span);
return {};
}

}
else {
this->error(ByteString::from_utf8_without_validation("Missing virtual for override"sv),method.parsed_function.name_span);
return {};
}

}
else {
if (all_virtuals.contains(method.parsed_function.name)){
this->error(ByteString::from_utf8_without_validation("Missing override keyword on function that is virtual"sv),method.parsed_function.name_span);
}
return {};
}

}
return {};
}

ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> Jakt::typechecker::Typechecker::typecheck_method(Jakt::parser::ParsedFunction const func,Jakt::types::StructLikeId const parent_id) {
{
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> parent_generic_parameters = DynamicArray<Jakt::types::CheckedGenericParameter>::create_with({});
Jakt::ids::ScopeId parent_scope_id = this->prelude_scope_id();
Jakt::parser::DefinitionLinkage parent_definition_linkage = Jakt::parser::DefinitionLinkage::Internal();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>>>{
auto&& __jakt_match_variant = parent_id;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct structure = this->get_struct(struct_id);
parent_scope_id = structure.scope_id;
parent_definition_linkage = structure.definition_linkage;
parent_generic_parameters = structure.generic_parameters;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
parent_scope_id = enum_.scope_id;
parent_definition_linkage = enum_.definition_linkage;
parent_generic_parameters = enum_.generic_parameters;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& trait_id = __jakt_match_value.value;
{
NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->get_trait(trait_id);
parent_scope_id = trait_->scope_id;
parent_definition_linkage = Jakt::parser::DefinitionLinkage::Internal();
parent_generic_parameters = trait_->generic_parameters;
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
if ((!func.generic_parameters.is_empty()) && (!func.must_instantiate)){
return JaktInternal::OptionalNone();
}
JaktInternal::Optional<Jakt::ids::FunctionId> const method_id = TRY((this->find_function_matching_signature_in_scope(parent_scope_id,func)));
if (method_id.has_value()){
TRY((this->typecheck_function(func,parent_scope_id)));
return method_id.value();
}
else {
this->compiler->panic(__jakt_format(StringView::from_string_literal("Previously defined function {} not found in scope {}"sv),func.name,parent_scope_id));
}

}
}

ErrorOr<Jakt::types::CheckedParameter> Jakt::typechecker::Typechecker::typecheck_parameter(Jakt::parser::ParsedParameter const parameter,Jakt::ids::ScopeId const scope_id,bool const first,JaktInternal::Optional<Jakt::ids::TypeId> const this_arg_type_id,JaktInternal::Optional<Jakt::ids::ScopeId> const check_scope) {
{
Jakt::ids::TypeId type_id = TRY((this->typecheck_typename(parameter.variable.parsed_type,scope_id,parameter.variable.name,JaktInternal::OptionalNone())));
if (first && (parameter.variable.name == ByteString::from_utf8_without_validation("this"sv))){
if (this_arg_type_id.has_value()){
type_id = this_arg_type_id.value();
}
}
if (this->get_type(type_id)->common.init_common.qualifiers.is_immutable){
type_id = this->with_qualifiers(Jakt::parser::CheckedQualifiers(false),type_id);
if (parameter.variable.is_mutable){
this->error(ByteString::from_utf8_without_validation("Cannot have a mutable binding to an immutable parameter"sv),parameter.variable.span);
}
}
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = Jakt::types::CheckedVariable::__jakt_create(parameter.variable.name,type_id,parameter.variable.is_mutable,parameter.variable.span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
Jakt::types::CheckedParameter const checked_parameter = Jakt::types::CheckedParameter(parameter.requires_label,variable,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>,ErrorOr<Jakt::types::CheckedParameter>> {
auto __jakt_enum_value = (parameter.default_argument.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Tuple{parameter.default_argument.value(), scope_id});
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
if (check_scope.has_value()){
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::VarId const var_id = module->add_variable(variable);
this->add_var_to_scope(check_scope.value(),parameter.variable.name,var_id,parameter.variable.span);
}
return checked_parameter;
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::fill_trait_requirements(JaktInternal::DynamicArray<Jakt::parser::ParsedNameWithGenericParameters> const names,JaktInternal::DynamicArray<Jakt::ids::TraitId>& trait_requirements,JaktInternal::DynamicArray<Jakt::ids::TypeId>& trait_implementations,Jakt::ids::ScopeId const scope_id) {
{
trait_requirements.ensure_capacity(names.size());
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedNameWithGenericParameters> _magic = names.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedNameWithGenericParameters> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedNameWithGenericParameters name = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TypeId> type_id = TRY((this->find_type_in_scope(scope_id,name.name)));
if (type_id.has_value()){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp117 = this->get_type(type_id.value());
if (__jakt_tmp117->__jakt_init_index() == 26 /* Trait */){
Jakt::ids::TraitId const trait_id = __jakt_tmp117->as.Trait.value;
if (!name.generic_parameters.is_empty()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> generic_arguments = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = name.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> argument = _magic_value.value();
{
generic_arguments.push(TRY((this->typecheck_typename(argument,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
}

}
}

NonnullRefPtr<typename Jakt::types::Type> const final_type = Jakt::types::Type::GenericTraitInstance(Jakt::parser::CheckedQualifiers(false),trait_id,generic_arguments);
type_id = this->find_or_add_type_id(final_type);
}
trait_implementations.push(type_id.value());
trait_requirements.push(trait_id);
}
else {
this->error(__jakt_format(StringView::from_string_literal("Requirement ‘{}’ is not a trait"sv),name.name),name.name_span);
continue;
}

}
else {
this->error(__jakt_format(StringView::from_string_literal("Couldn't find trait ‘{}’"sv),name.name),name.name_span);
continue;
}

}

}
}

}
return {};
}

ErrorOr<Jakt::ids::FunctionId> Jakt::typechecker::Typechecker::typecheck_function_predecl(Jakt::parser::ParsedFunction const parsed_function,Jakt::ids::ScopeId const parent_scope_id,JaktInternal::Optional<Jakt::ids::TypeId> const this_arg_type_id,JaktInternal::Optional<NonnullRefPtr<Jakt::types::FunctionGenerics>> generics,JaktInternal::Optional<Jakt::types::ResolutionMixin> scope_mixin) {
{
Jakt::ids::ScopeId const function_scope_id = this->create_scope(parent_scope_id,parsed_function.can_throw,__jakt_format(StringView::from_string_literal("fn({})"sv),parsed_function.name),true);
if (scope_mixin.has_value()){
NonnullRefPtr<Jakt::types::Scope> function_scope = this->get_scope(function_scope_id);
function_scope->resolution_mixins.push(scope_mixin.value());
}
ByteString const scope_debug_name = __jakt_format(StringView::from_string_literal("function-block({})"sv),parsed_function.name);
Jakt::ids::ScopeId const block_scope_id = this->create_scope(function_scope_id,parsed_function.can_throw,scope_debug_name,true);
size_t const module_id = this->current_module_id.id;
bool base_definition = false;
if (!generics.has_value()){
generics = Jakt::types::FunctionGenerics::__jakt_create(function_scope_id,DynamicArray<Jakt::types::CheckedParameter>::create_with({}),DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({}),DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({}));
base_definition = true;
}
bool const is_generic_function = !parsed_function.generic_parameters.is_empty();
bool const is_generic = is_generic_function || (this_arg_type_id.has_value() && (this->get_type(this_arg_type_id.value())->__jakt_init_index() == 20 /* GenericInstance */));
bool has_varargs = parsed_function.has_varargs;
if (has_varargs && (parsed_function.linkage.__jakt_init_index() == 0 /* Internal */)){
this->error(ByteString::from_utf8_without_validation("Only external functions are allowed to be declared using varargs"sv),parsed_function.name_span);
has_varargs = false;
}
NonnullRefPtr<Jakt::types::CheckedFunction> checked_function = Jakt::types::CheckedFunction::__jakt_create(parsed_function.name,parsed_function.name_span,TRY((this->typecheck_visibility(parsed_function.visibility,parent_scope_id))),Jakt::types::unknown_type_id(),parsed_function.return_type_span,DynamicArray<Jakt::types::CheckedParameter>::create_with({}),generics.value(),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),block_scope_id,Jakt::types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false),parsed_function.can_throw,parsed_function.type,parsed_function.linkage,function_scope_id,JaktInternal::OptionalNone(),(!is_generic) || (!base_definition),parsed_function,parsed_function.is_comptime,false,false,parsed_function.is_unsafe,has_varargs,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,parsed_function.external_name,parsed_function.deprecated_message,JaktInternal::OptionalNone(),parsed_function.force_inline,false);
NonnullRefPtr<Jakt::types::Module> current_module = this->current_module();
Jakt::ids::FunctionId const function_id = current_module->add_function(checked_function);
Jakt::ids::ScopeId const checked_function_scope_id = checked_function->function_scope_id;
bool const external_linkage = parsed_function.linkage.__jakt_init_index() == 1 /* External */;
JaktInternal::Optional<Jakt::ids::ScopeId> const check_scope = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ids::ScopeId>,ErrorOr<Jakt::ids::FunctionId>> {
auto __jakt_enum_value = (is_generic || (parsed_function.return_type->__jakt_init_index() == 15 /* Empty */));
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(this->create_scope(parent_scope_id,parsed_function.can_throw,scope_debug_name,true)));
}else {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedGenericParameter> _magic = parsed_function.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedGenericParameter generic_parameter = _magic_value.value();
{
Jakt::ids::TypeId type_var_type_id = Jakt::ids::TypeId(current_module->id,current_module->types.size());
if (base_definition){
Jakt::types::FunctionGenericParameter parameter = Jakt::types::FunctionGenericParameter::parameter(type_var_type_id,generic_parameter.span);
JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations = DynamicArray<Jakt::ids::TypeId>::create_with({});
current_module->types.push(Jakt::types::Type::TypeVariable(Jakt::parser::CheckedQualifiers(false),generic_parameter.name,trait_implementations,generic_parameter.is_value));
if (generic_parameter.requires_list.has_value()){
TRY((this->fill_trait_requirements(generic_parameter.requires_list.value(),parameter.checked_parameter.constraints,trait_implementations,parent_scope_id)));
}
checked_function->generics->params.push(parameter);
}
else if (checked_function->generics->params.operator[](i).kind.__jakt_init_index() == 1 /* Parameter */){
type_var_type_id = checked_function->generics->params.operator[](i).type_id();
}
if ((!parsed_function.must_instantiate) || external_linkage){
TRY((this->add_type_to_scope(checked_function_scope_id,generic_parameter.name,type_var_type_id,generic_parameter.span)));
}
if (check_scope.has_value()){
TRY((this->add_type_to_scope(check_scope.value(),generic_parameter.name,type_var_type_id,generic_parameter.span)));
}
i++;
}

}
}

bool first = true;
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedParameter> _magic = parsed_function.params.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedParameter parameter = _magic_value.value();
{
Jakt::types::CheckedParameter const checked_param = TRY((this->typecheck_parameter(parameter,checked_function_scope_id,first,this_arg_type_id,check_scope)));
checked_function->params.push(checked_param);
if (base_definition){
checked_function->generics->base_params.push(checked_param);
}
first = false;
}

}
}

if (parsed_function.stores_arguments.has_value()){
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>> _magic = parsed_function.stores_arguments.value().iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel> index_____ = _magic_value.value();
{
JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel> const jakt__index_____ = index_____;
size_t const index = jakt__index_____.template get<0>();
Jakt::parser::ArgumentStoreLevel const _ = jakt__index_____.template get<1>();

if (index >= checked_function->params.size()){
this->compiler->panic(ByteString::from_utf8_without_validation("stores_argument() index out of bounds"sv));
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::ids::FunctionId>>{
auto&& __jakt_match_variant = *this->get_type(checked_function->params.operator[](index).variable->type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* Reference */:case 28 /* MutableReference */:{
}
return JaktInternal::ExplicitValue<void>();
default:{
this->error_with_hint(ByteString::from_utf8_without_validation("This parameter is not a reference"sv),checked_function->params.operator[](index).variable->definition_span,ByteString::from_utf8_without_validation("stores_argument() may only be used to declare reference lifetime requirements"sv),checked_function->params.operator[](index).variable->definition_span);
}
return JaktInternal::ExplicitValue<void>();
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
checked_function->stores_arguments = parsed_function.stores_arguments;
Jakt::ids::TypeId function_return_type_id = TRY((this->typecheck_typename(parsed_function.return_type,checked_function_scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if (parsed_function.return_type->__jakt_init_index() == 15 /* Empty */){
if (parsed_function.is_fat_arrow){
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_55([&] {
this->exit_ignore_error_mode(snapshot);
});
Jakt::types::CheckedBlock const block = TRY((this->typecheck_block(parsed_function.block,check_scope.value(),Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone())));
if (this->had_an_error){
function_return_type_id = Jakt::types::void_type_id();
this->ignore_errors = false;
this->error_with_hint(ByteString::from_utf8_without_validation("Can't infer the return type of this function"sv),parsed_function.return_type_span,ByteString::from_utf8_without_validation("Try adding an explicit return type to the function here"sv),parsed_function.return_type_span);
}
else {
function_return_type_id = this->infer_function_return_type(block);
}

}
else {
function_return_type_id = Jakt::types::void_type_id();
}

}
checked_function->return_type_id = function_return_type_id;
if (!this->get_scope(parent_scope_id)->is_from_generated_code){
TRY((this->check_that_type_doesnt_contain_reference(function_return_type_id,parsed_function.return_type_span)));
}
if ((!parsed_function.generic_parameters.is_empty()) && function_return_type_id.equals(Jakt::types::unknown_type_id())){
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_56([&] {
this->exit_ignore_error_mode(snapshot);
});
Jakt::types::CheckedBlock const block = TRY((this->typecheck_block(parsed_function.block,check_scope.value(),Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone())));
Jakt::ids::TypeId const return_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId,ErrorOr<Jakt::ids::FunctionId>> {
auto __jakt_enum_value = (function_return_type_id.equals(Jakt::types::unknown_type_id()));
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(this->infer_function_return_type(block));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(TRY((this->resolve_type_var(function_return_type_id,parent_scope_id))));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
checked_function->block = block;
checked_function->return_type_id = return_type_id;
}
this->add_function_to_scope(parent_scope_id,parsed_function.name,DynamicArray<Jakt::ids::FunctionId>::create_with({function_id}),parsed_function.name_span);
return function_id;
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::check_that_type_doesnt_contain_reference(Jakt::ids::TypeId const type_id,Jakt::utility::Span const span) {
{
if (this->type_contains_reference(type_id)){
this->error(__jakt_format(StringView::from_string_literal("Reference type ‘{}’ not usable in this context"sv),TRY((this->type_name(type_id,false)))),span);
}
}
return {};
}

bool Jakt::typechecker::Typechecker::type_contains_reference(Jakt::ids::TypeId const type_id) {
{
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(type_id);
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* Reference */:case 28 /* MutableReference */:return JaktInternal::ExplicitValue(true);
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::check_type_argument_requirements(Jakt::ids::TypeId const generic_argument,JaktInternal::DynamicArray<Jakt::ids::TraitId> const constraints,Jakt::utility::Span const arg_span,JaktInternal::Optional<Jakt::ids::ScopeId> const scope_id) {
{
if (!constraints.is_empty()){
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(generic_argument);
JaktInternal::Tuple<JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>,Jakt::utility::Span> const implemented_traits_decl_span_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>,Jakt::utility::Span>, ErrorOr<void>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(Tuple{this->get_enum(id).trait_implementations, this->get_enum(id).name_span});
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Tuple{this->get_enum(id).trait_implementations, this->get_enum(id).name_span});
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(Tuple{this->get_struct(id).trait_implementations, this->get_struct(id).name_span});
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Tuple{this->get_struct(id).trait_implementations, this->get_struct(id).name_span});
};/*case end*/
default:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>,Jakt::utility::Span>,ErrorOr<void>> {
auto __jakt_enum_value = (type->is_builtin());
if (__jakt_enum_value) {{
Jakt::ids::StructId const struct_id = this->program->builtin_implementation_struct(type->as_builtin_type(),this->program->prelude_module_id());
return JaktInternal::ExplicitValue<JaktInternal::Tuple<JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>,Jakt::utility::Span>>(Tuple{this->get_struct(struct_id).trait_implementations, this->get_struct(struct_id).name_span});
}
VERIFY_NOT_REACHED();
}else if (!__jakt_enum_value) {{
this->error(__jakt_format(StringView::from_string_literal("Cannot use ‘{}’ here as only enums, structs and classes can implement the required traits"sv),TRY((this->type_name(generic_argument,false)))),arg_span);
{
return ErrorOr<void>{};
}

Jakt::abort();
}
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const implemented_traits = implemented_traits_decl_span_.template get<0>();
Jakt::utility::Span const decl_span = implemented_traits_decl_span_.template get<1>();

{
JaktInternal::ArrayIterator<Jakt::ids::TraitId> _magic = constraints.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TraitId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TraitId constraint = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->program->get_trait(constraint);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = trait_->requirements;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Nothing */:case 1 /* Methods */:{
ByteString const trait_name = trait_->name;
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const implemented_trait = implemented_traits.get(trait_name);
if ((!implemented_trait.has_value()) || (!implemented_trait.value().first().map([](auto& _value) { return _value.template get<0>(); }).map([&](auto& _value) { return _value.equals(constraint); }).value_or_lazy_evaluated([&] { return false; }))){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Cannot use ‘{}’ here as it doesn't implement the trait ‘{}’"sv),TRY((this->type_name(generic_argument,false))),trait_name),arg_span,ByteString::from_utf8_without_validation("Consider implementing the required trait for this type"sv),decl_span);
}
}
return JaktInternal::ExplicitValue<void>();
case 2 /* ComptimeExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeExpression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
{
NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter = this->interpreter();
NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),JaktInternal::OptionalNone(),Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({{this->find_or_add_type_id(Jakt::types::Type::Self(Jakt::parser::CheckedQualifiers(false))), generic_argument}}),this->compiler,scope_id);
JaktInternal::Optional<Jakt::interpreter::StatementResult> const result = ({ Optional<Jakt::interpreter::StatementResult> __jakt_var_57;
auto __jakt_var_58 = [&]() -> ErrorOr<Jakt::interpreter::StatementResult> { return interpreter->execute_expression(expr,scope); }();
if (!__jakt_var_58.is_error()) __jakt_var_57 = __jakt_var_58.release_value();
__jakt_var_57; });
bool meets_requirement = false;
if (result.has_value()){
meets_requirement = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = result.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = *value.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default:{
this->error(__jakt_format(StringView::from_string_literal("Invalid result type for comptime requirements in trait ‘{}’, expected ‘bool’ but got ‘{}’"sv),trait_->name,value.impl),arg_span);
return JaktInternal::ExplicitValue<bool>(false);
}
VERIFY_NOT_REACHED();
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
}));
};/*case end*/
default:{
this->error(__jakt_format(StringView::from_string_literal("Invalid result type for comptime requirements in trait ‘{}’, expected ‘bool’ but got ‘{}’"sv),trait_->name,result),arg_span);
return JaktInternal::ExplicitValue<bool>(false);
}
VERIFY_NOT_REACHED();
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
if (!meets_requirement){
this->error(__jakt_format(StringView::from_string_literal("Cannot use ‘{}’ here as it doesn't meet the comptime requirements for ‘{}’"sv),TRY((this->type_name(generic_argument,false))),trait_->name),arg_span);
}
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
else {
return {};
}

}
return {};
}

ErrorOr<Jakt::ids::FunctionId> Jakt::typechecker::Typechecker::typecheck_and_specialize_generic_function(Jakt::ids::FunctionId const function_id,JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_arguments,Jakt::ids::ScopeId const parent_scope_id,JaktInternal::Optional<Jakt::ids::TypeId> const this_type_id,Jakt::types::GenericInferences const generic_substitutions,JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> const type_args,Jakt::utility::Span const call_span,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>> const args) {
{
NonnullRefPtr<Jakt::types::CheckedFunction> checked_function = this->get_function(function_id);
if (!checked_function->parsed_function.has_value()){
return function_id;
}
size_t const specialization_index = checked_function->generics->specializations.size();
checked_function->generics->specializations.push(generic_arguments);
Jakt::ids::ModuleId const old_module_id = this->current_module_id;
ScopeGuard __jakt_var_59([&] {
this->current_module_id = old_module_id;
});
this->current_module_id = checked_function->function_scope_id.module_id;
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::FunctionId const new_function_id = module->next_function_id();
Jakt::parser::ParsedFunction parsed_function = checked_function->to_parsed_function();
ByteString arg_names = ByteString::from_utf8_without_validation(""sv);
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = generic_arguments.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
if (!arg_names.is_empty()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(arg_names,ByteString::from_utf8_without_validation(", "sv));
}
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(arg_names,TRY((this->type_name(arg,false))));
}

}
}

Jakt::ids::ScopeId const scope_id = this->create_scope(checked_function->generics->base_scope_id,parsed_function.can_throw,__jakt_format(StringView::from_string_literal("function-specialization({}<{}>)"sv),parsed_function.name,arg_names),true);
if (parsed_function.generic_parameters.size() != generic_arguments.size()){
this->error(__jakt_format(StringView::from_string_literal("Generic function {} expects {} generic arguments, but {} were given"sv),parsed_function.name,parsed_function.generic_parameters.size(),generic_arguments.size()),parsed_function.name_span);
}
if ((parsed_function.generic_parameters.size() <= generic_arguments.size()) && (parsed_function.generic_parameters.size() <= checked_function->generics->params.size())){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parsed_function.generic_parameters.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::utility::Span arg_span = call_span;
if (type_args.size() > i){
arg_span = type_args.operator[](i)->span();
}
if (generic_arguments.size() > i){
TRY((this->check_type_argument_requirements(generic_arguments.operator[](i),checked_function->generics->params.operator[](i).checked_parameter.constraints,arg_span,scope_id)));
}
}

}
}

Jakt::utility::Span const span = parsed_function.name_span;
if (this_type_id.has_value()){
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const p = DynamicArray<Jakt::types::CheckedGenericParameter>::create_with({});
JaktInternal::DynamicArray<Jakt::ids::TypeId> const a = DynamicArray<Jakt::ids::TypeId>::create_with({});
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const params_args_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>, ErrorOr<Jakt::ids::FunctionId>>{
auto&& __jakt_match_variant = *this->get_type(this_type_id.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Tuple{this->get_struct(id).generic_parameters, args});
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Tuple{this->get_enum(id).generic_parameters, args});
};/*case end*/
default:return JaktInternal::ExplicitValue(Tuple{p, a});
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const params = params_args_.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = params_args_.template get<1>();

{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::CheckedGenericParameter const param = params.operator[](i);
Jakt::ids::TypeId const arg = generic_substitutions.map(args.operator[](i));
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp118 = this->get_type(param.type_id);
if (__jakt_tmp118->__jakt_init_index() == 18 /* TypeVariable */){
ByteString const type_name = __jakt_tmp118->as.TypeVariable.name;
JaktInternal::Optional<Jakt::ids::ScopeId> const dependent_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ids::ScopeId>, ErrorOr<Jakt::ids::FunctionId>>{
auto&& __jakt_match_variant = *this->get_type(param.type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_struct(struct_id).scope_id);
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_struct(struct_id).scope_id);
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_enum(enum_id).scope_id);
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_enum(enum_id).scope_id);
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& trait_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_trait(trait_id)->scope_id);
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_trait(trait_id)->scope_id);
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
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
TRY((this->add_type_to_scope(scope_id,type_name,arg,span)));
if (dependent_scope_id.has_value()){
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
scope->aliases.set(type_name,dependent_scope_id.value());
}
}
else {
continue;
}

}

}
}

}
{
JaktInternal::ArrayIterator<Jakt::types::FunctionGenericParameter> _magic = checked_function->generics->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::FunctionGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::FunctionGenericParameter generic_parameter = _magic_value.value();
{
Jakt::ids::TypeId const parameter_type_id = generic_parameter.checked_parameter.type_id;
JaktInternal::Optional<Jakt::ids::TypeId> const mapped = generic_substitutions.get(parameter_type_id);
if (mapped.has_value()){
Jakt::ids::TypeId const type_id = mapped.value();
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp119 = this->get_type(parameter_type_id);
if (__jakt_tmp119->__jakt_init_index() == 18 /* TypeVariable */){
ByteString const type_name = __jakt_tmp119->as.TypeVariable.name;
bool const is_value = __jakt_tmp119->as.TypeVariable.is_value;
JaktInternal::Optional<Jakt::ids::ScopeId> const dependent_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ids::ScopeId>, ErrorOr<Jakt::ids::FunctionId>>{
auto&& __jakt_match_variant = *this->get_type(parameter_type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_struct(struct_id).scope_id);
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_struct(struct_id).scope_id);
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_enum(enum_id).scope_id);
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_enum(enum_id).scope_id);
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& trait_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_trait(trait_id)->scope_id);
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_trait(trait_id)->scope_id);
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
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
TRY((this->add_type_to_scope(scope_id,type_name,type_id,span)));
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
if (is_value){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp120 = this->get_type(type_id);
if (__jakt_tmp120->__jakt_init_index() == 31 /* Const */){
Jakt::types::Value const value = __jakt_tmp120->as.Const.value;
scope->comptime_bindings.set(type_name, value);
NonnullRefPtr<Jakt::types::CheckedVariable> const checked_var = Jakt::types::CheckedVariable::__jakt_create(type_name,TRY((value.impl->type_id(this->program))),false,value.span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
scope->vars.set(type_name, module->add_variable(checked_var));
}
}
if (dependent_scope_id.has_value()){
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
scope->aliases.set(type_name,dependent_scope_id.value());
}
}
else {
continue;
}

}
else {
continue;
}

}

}
}

parsed_function.must_instantiate = true;
checked_function->is_instantiated = true;
JaktInternal::Optional<Jakt::ids::FunctionId> const previous_function_id = this->current_function_id;
this->current_function_id = static_cast<JaktInternal::Optional<Jakt::ids::FunctionId>>(new_function_id);
TRY((this->typecheck_function_predecl(parsed_function,scope_id,this_type_id,checked_function->generics,JaktInternal::OptionalNone())));
TRY((this->typecheck_function(parsed_function,scope_id)));
this->current_function_id = previous_function_id;
NonnullRefPtr<Jakt::types::Scope> base_scope = this->get_scope(this->get_scope(checked_function->generics->base_scope_id)->parent.value());
base_scope->functions.get(checked_function->name).value().push(new_function_id);
NonnullRefPtr<Jakt::types::CheckedFunction> function = this->get_function(new_function_id);
function->specialization_index = specialization_index;
return new_function_id;
}
else {
return function_id;
}

}
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_jakt_main(Jakt::parser::ParsedFunction const parsed_function,Jakt::ids::ScopeId const parent_scope_id) {
{
ByteString const param_type_error = ByteString::from_utf8_without_validation("Main function must take a single array of strings as its parameter"sv);
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const func_ids = TRY((this->find_functions_with_name_in_scope(parent_scope_id,ByteString::from_utf8_without_validation("main"sv),JaktInternal::OptionalNone())));
if (func_ids.value().size() > static_cast<size_t>(1ULL)){
this->error(ByteString::from_utf8_without_validation("Function 'main' declared multiple times."sv),parsed_function.name_span);
}
if (parsed_function.params.size() > static_cast<size_t>(1ULL)){
this->error(param_type_error,parsed_function.name_span);
}
if (!parsed_function.params.is_empty()){
NonnullRefPtr<typename Jakt::parser::ParsedType> __jakt_tmp121 = parsed_function.params.operator[](static_cast<i64>(0LL)).variable.parsed_type;
if (__jakt_tmp121->__jakt_init_index() == 3 /* JaktArray */){
NonnullRefPtr<typename Jakt::parser::ParsedType> const inner = __jakt_tmp121->as.JaktArray.inner;
Jakt::utility::Span const span = __jakt_tmp121->as.JaktArray.span;
NonnullRefPtr<typename Jakt::parser::ParsedType> __jakt_tmp122 = inner;
if (__jakt_tmp122->__jakt_init_index() == 0 /* Name */){
ByteString const name = __jakt_tmp122->as.Name.name;
Jakt::utility::Span const span = __jakt_tmp122->as.Name.span;
if ([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(name,ByteString::from_utf8_without_validation("String"sv))){
this->error(param_type_error,span);
}
}
else {
this->error(param_type_error,span);
}

}
else {
this->error(param_type_error,parsed_function.name_span);
}

}
ByteString const return_type_error = ByteString::from_utf8_without_validation("Main function must return c_int"sv);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *parsed_function.return_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* Empty */:{
}
return JaktInternal::ExplicitValue<void>();
case 0 /* Name */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Name;ByteString const& name = __jakt_match_value.name;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(name,ByteString::from_utf8_without_validation("c_int"sv))){
this->error(return_type_error,span);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
this->error(return_type_error,parsed_function.return_type_span);
}
return JaktInternal::ExplicitValue<void>();
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

Jakt::ids::TypeId Jakt::typechecker::Typechecker::infer_function_return_type(Jakt::types::CheckedBlock const block) const {
{
if (block.statements.is_empty()){
return Jakt::types::void_type_id();
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> __jakt_tmp123 = block.statements.last().value();
if (__jakt_tmp123->__jakt_init_index() == 8 /* Return */){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const val = __jakt_tmp123->as.Return.val;
if (val.has_value()){
return val.value()->type();
}
}
return Jakt::types::void_type_id();
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::typecheck_function(Jakt::parser::ParsedFunction const parsed_function,Jakt::ids::ScopeId const parent_scope_id) {
{
bool const in_comptime_function_call = this->in_comptime_function_call;
ScopeGuard __jakt_var_60([&] {
this->in_comptime_function_call = in_comptime_function_call;
});
this->in_comptime_function_call = parsed_function.is_comptime;
if ((!parsed_function.generic_parameters.is_empty()) && (!parsed_function.must_instantiate)){
return {};
}
JaktInternal::Optional<Jakt::ids::FunctionId> const function_id = TRY((this->find_function_matching_signature_in_scope(parent_scope_id,parsed_function)));
if (function_id.has_value()){
this->current_function_id = function_id.value();
if ((parsed_function.name == ByteString::from_utf8_without_validation("main"sv)) && parent_scope_id.equals(this->main_scope_id())){
TRY((this->typecheck_jakt_main(parsed_function,parent_scope_id)));
}
NonnullRefPtr<Jakt::types::CheckedFunction> checked_function = this->get_function(function_id.value());
Jakt::ids::ScopeId const function_scope_id = checked_function->function_scope_id;
Jakt::parser::FunctionLinkage const function_linkage = checked_function->linkage;
if (checked_function->is_fully_checked){
if (!this->get_scope(parent_scope_id)->is_from_generated_code){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Function ‘{}’ is already defined"sv),parsed_function.name),parsed_function.name_span,ByteString::from_utf8_without_validation("Try removing this definition"sv),checked_function->parsed_function.value().name_span);
}
return {};
}
ScopeGuard __jakt_var_61([&] {
checked_function->is_fully_checked = true;
});
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = checked_function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = param.variable;
Jakt::ids::VarId const var_id = module->add_variable(variable);
this->add_var_to_scope(function_scope_id,variable->name,var_id,variable->definition_span);
}

}
}

Jakt::ids::TypeId function_return_type_id = TRY((this->typecheck_typename(parsed_function.return_type,function_scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if ((!parsed_function.is_fat_arrow) && ((parsed_function.return_type->__jakt_init_index() == 15 /* Empty */) && [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(parsed_function.name,ByteString::from_utf8_without_validation("main"sv)))){
function_return_type_id = Jakt::types::void_type_id();
}
if (function_return_type_id.equals(Jakt::types::never_type_id())){
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(function_scope_id);
scope->can_throw = true;
}
Jakt::types::CheckedBlock const block = TRY((this->typecheck_block(parsed_function.block,function_scope_id,Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone())));
if (block.yielded_type.has_value()){
this->error_with_hint(ByteString::from_utf8_without_validation("Functions are not allowed to yield values"sv),parsed_function.block.find_yield_span().value(),ByteString::from_utf8_without_validation("You might want to return instead"sv),parsed_function.block.find_yield_keyword_span().value());
}
Jakt::ids::TypeId const return_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId,ErrorOr<void>> {
auto __jakt_enum_value = (function_return_type_id.equals(Jakt::types::unknown_type_id()));
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(this->infer_function_return_type(block));
}else {return JaktInternal::ExplicitValue(TRY((this->resolve_type_var(function_return_type_id,function_scope_id))));
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((!(function_linkage.__jakt_init_index() == 1 /* External */)) && ((!return_type_id.equals(Jakt::types::void_type_id())) && (!block.control_flow.always_transfers_control()))){
if (return_type_id.equals(Jakt::types::never_type_id()) && (!block.control_flow.never_returns())){
this->error(ByteString::from_utf8_without_validation("Control reaches end of never-returning function"sv),parsed_function.name_span);
}
else if ((!block.control_flow.never_returns()) && (!parsed_function.is_jakt_main)){
this->error(ByteString::from_utf8_without_validation("Control reaches end of non-void function"sv),parsed_function.name_span);
}
}
if (!(function_linkage.__jakt_init_index() == 1 /* External */)){
if (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = *this->get_type(function_return_type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* Trait */:case 22 /* GenericTraitInstance */:return JaktInternal::ExplicitValue(true);
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Invalid use of trait in return type ‘{}’"sv),TRY((this->type_name(function_return_type_id,false)))),parsed_function.return_type_span,ByteString::from_utf8_without_validation("Return type must either be a concrete type, or be explicitly generic"sv),parsed_function.return_type_span);
}
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = checked_function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
Jakt::ids::TypeId const type_id = param.variable->type_id;
if (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<void>>{
auto&& __jakt_match_variant = *this->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* Trait */:case 22 /* GenericTraitInstance */:return JaktInternal::ExplicitValue(true);
default:return JaktInternal::ExplicitValue(false);
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
})){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Invalid use of trait in parameter type ‘{}’"sv),TRY((this->type_name(type_id,false)))),param.variable->type_span.value_or_lazy_evaluated([&] { return param.variable->definition_span; }),ByteString::from_utf8_without_validation("Parameter type must either be a concrete type, or be explicitly generic"sv),param.variable->type_span.value_or_lazy_evaluated([&] { return param.variable->definition_span; }));
}
if (this->get_type(type_id)->__jakt_init_index() == 16 /* Unknown */){
this->error(ByteString::from_utf8_without_validation("Cannot infer type of parameter, and no type was specified"sv),param.variable->type_span.value_or_lazy_evaluated([&] { return param.variable->definition_span; }));
}
}

}
}

}
checked_function->block = block;
checked_function->return_type_id = return_type_id;
ScopeGuard __jakt_var_62([&] {
this->current_function_id = JaktInternal::OptionalNone();
});
if (parsed_function.is_raw_constructor){
if (!this->self_type_id.has_value()){
this->error(ByteString::from_utf8_without_validation("Invalid use of raw_constructor outside of a class"sv),parsed_function.name_span);
return {};
}
Jakt::ids::TypeId const self_type_id = this->self_type_id.value();
NonnullRefPtr<typename Jakt::types::Type> const self_type = this->get_type(self_type_id);
Jakt::types::CheckedStruct struct_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedStruct, ErrorOr<void>>{
auto&& __jakt_match_variant = *self_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_struct(id));
};/*case end*/
default:{
this->error(ByteString::from_utf8_without_validation("Invalid use of raw_constructor outside of a class"sv),parsed_function.name_span);
return {};
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (struct_.record_type.__jakt_init_index() == 1 /* Class */){
if (!return_type_id.equals(Jakt::types::void_type_id())){
this->error(ByteString::from_utf8_without_validation("raw_constructor class must return void"sv),parsed_function.return_type_span);
}
if (parsed_function.params.size() < static_cast<size_t>(1ULL)){
this->error(ByteString::from_utf8_without_validation("raw_constructor class must take at least `this'"sv),parsed_function.name_span);
return {};
}
Jakt::parser::ParsedParameter const this_param = parsed_function.params.operator[](static_cast<i64>(0LL));
if ([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(this_param.variable.name,ByteString::from_utf8_without_validation("this"sv))){
this->error(ByteString::from_utf8_without_validation("raw_constructor class must take `this' as its first parameter"sv),this_param.variable.span);
return {};
}
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = struct_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const var = this->get_variable(field->variable_id);
if (field->default_value_expression.has_value()){
field->default_value_in_definition_scope = TRY((this->typecheck_expression(field->default_value_expression.value().template get<0>(),field->default_value_expression.value().template get<1>(),Jakt::types::SafetyMode::Safe(),Jakt::typechecker::TypeHint::MustBe(var->type_id))));
}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Field '{}' in class '{}' must have a default value"sv),var->name,struct_.name),var->definition_span,ByteString::from_utf8_without_validation("Class is declared to have a raw constructor here"sv),parsed_function.name_span);
return {};
}

}

}
}

checked_function->external_name = Jakt::parser::ExternalName::Plain(struct_.name_for_codegen().as_name_for_definition());
checked_function->type = Jakt::parser::FunctionType::Constructor();
checked_function->is_raw_constructor = true;
}
else {
this->error(ByteString::from_utf8_without_validation("Invalid use of raw_constructor on a non-class type"sv),parsed_function.name_span);
return {};
}

}
}
else {
this->compiler->panic(__jakt_format(StringView::from_string_literal("Previously defined function {} not found in scope {}"sv),parsed_function.name,parent_scope_id));
}

}
return {};
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::choose_broader_type_id(Jakt::ids::TypeId const original_type_id,Jakt::ids::TypeId const potential_type_id,Jakt::types::GenericInferences& generic_inferences,Jakt::utility::Span const span) {
{
if ((!TRY((this->check_types_for_compat(Jakt::typechecker::TypeHint::CouldBe(original_type_id),potential_type_id,this->generic_inferences,span)))) && TRY((this->check_types_for_compat(potential_type_id,Jakt::typechecker::TypeHint::CouldBe(original_type_id),this->generic_inferences,span)))){
return potential_type_id;
}
return original_type_id;
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::check_types_for_compat(Jakt::ids::TypeId const lhs_type_id,Jakt::typechecker::TypeHint const rhs_type_hint,Jakt::types::GenericInferences& generic_inferences,Jakt::utility::Span const span) {
{
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(rhs_type_hint.__jakt_init_index() == 1 /* CouldBe */);
ScopeGuard __jakt_var_63([&] {
this->exit_ignore_error_mode(snapshot);
});
return this->check_types_for_compat(lhs_type_id,rhs_type_hint.common.init_common.type_id,generic_inferences,span);
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::check_types_for_compat(Jakt::typechecker::TypeHint const lhs_type_hint,Jakt::ids::TypeId const rhs_type_id,Jakt::types::GenericInferences& generic_inferences,Jakt::utility::Span const span) {
{
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(lhs_type_hint.__jakt_init_index() == 1 /* CouldBe */);
ScopeGuard __jakt_var_64([&] {
this->exit_ignore_error_mode(snapshot);
});
return this->check_types_for_compat(lhs_type_hint.common.init_common.type_id,rhs_type_id,generic_inferences,span);
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::check_types_for_compat(Jakt::ids::TypeId const lhs_type_id,Jakt::ids::TypeId const rhs_type_id,Jakt::types::GenericInferences& generic_inferences,Jakt::utility::Span const span) {
{
if ((lhs_type_id.equals(rhs_type_id) || lhs_type_id.equals(Jakt::types::unknown_type_id())) || rhs_type_id.equals(Jakt::types::unknown_type_id())){
return true;
}
NonnullRefPtr<typename Jakt::types::Type> const lhs_type = this->get_type(lhs_type_id);
NonnullRefPtr<typename Jakt::types::Type> const rhs_type = this->get_type(rhs_type_id);
if (lhs_type->common.init_common.qualifiers.is_immutable && (!rhs_type->common.init_common.qualifiers.is_immutable)){
return this->check_types_for_compat(lhs_type_id,this->with_qualifiers(lhs_type->common.init_common.qualifiers,rhs_type_id),generic_inferences,span);
}
if (lhs_type->is_builtin() && (rhs_type->is_builtin() && (lhs_type->as_builtin_type().id() == rhs_type->as_builtin_type().id()))){
return true;
}
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp124 = lhs_type;
if (__jakt_tmp124->__jakt_init_index() == 26 /* Trait */){
Jakt::ids::TraitId const trait_id = __jakt_tmp124->as.Trait.value;
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_65([&] {
this->exit_ignore_error_mode(snapshot);
});
TRY((this->check_type_argument_requirements(rhs_type_id,DynamicArray<Jakt::ids::TraitId>::create_with({trait_id}),span,JaktInternal::OptionalNone())));
if (!this->had_an_error){
return true;
}
}
if (lhs_type->__jakt_init_index() == 30 /* Self */){
if (!this->self_type_id.has_value()){
this->error(ByteString::from_utf8_without_validation("Invalid use of the 'Self' type"sv),span);
}
else {
return this->check_types_for_compat(this->self_type_id.value(),rhs_type_id,generic_inferences,span);
}

}
if (rhs_type->__jakt_init_index() == 30 /* Self */){
if (!this->self_type_id.has_value()){
this->error(ByteString::from_utf8_without_validation("Invalid use of the 'Self' type"sv),span);
}
else {
return this->check_types_for_compat(lhs_type_id,this->self_type_id.value(),generic_inferences,span);
}

}
if ((rhs_type->__jakt_init_index() == 18 /* TypeVariable */) && (!(lhs_type->__jakt_init_index() == 18 /* TypeVariable */))){
return this->check_types_for_compat(rhs_type_id,lhs_type_id,generic_inferences,span);
}
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp126 = rhs_type;
if (__jakt_tmp126->__jakt_init_index() == 31 /* Const */){
Jakt::types::Value const rhs = __jakt_tmp126->as.Const.value;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp125 = lhs_type;
if (__jakt_tmp125->__jakt_init_index() == 31 /* Const */){
Jakt::types::Value const lhs = __jakt_tmp125->as.Const.value;
if (rhs.impl->equals(lhs.impl)){
return true;
}
NonnullRefPtr<Jakt::interpreter::Interpreter> const interpreter = this->interpreter();
this->error(__jakt_format(StringView::from_string_literal("Literal type value mismatch: expected '{}', found '{}'"sv),TRY((Jakt::types::comptime_format_impl(ByteString::from_utf8_without_validation("{}"sv),DynamicArray<Jakt::types::Value>::create_with({lhs}).operator[](JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}),this->program))),TRY((Jakt::types::comptime_format_impl(ByteString::from_utf8_without_validation("{}"sv),DynamicArray<Jakt::types::Value>::create_with({rhs}).operator[](JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}),this->program)))),span);
return false;
}
}
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
Jakt::ids::StructId const weakptr_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv))));
Jakt::ids::StructId const array_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Array"sv))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *lhs_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */:{
JaktInternal::Optional<Jakt::ids::TypeId> const maybe_resolved_inference = generic_inferences.get(lhs_type_id);
JaktInternal::Optional<Jakt::ids::TypeId> __jakt_tmp127 = maybe_resolved_inference;
if (__jakt_tmp127.has_value()){
Jakt::ids::TypeId const resolved_inference = __jakt_tmp127.value();
return this->check_types_for_compat(resolved_inference,rhs_type_id,generic_inferences,span);
}
else {
generic_inferences.set(lhs_type_id,rhs_type_id);
}

}
return JaktInternal::ExplicitValue<void>();
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;Jakt::ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp128 = rhs_type;
if (__jakt_tmp128->__jakt_init_index() == 19 /* Dependent */){
Jakt::ids::TypeId const rhs_namespace_type = __jakt_tmp128->as.Dependent.namespace_type;
ByteString const rhs_name = __jakt_tmp128->as.Dependent.name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const rhs_args = __jakt_tmp128->as.Dependent.args;
TRY((this->check_types_for_compat(namespace_type,rhs_namespace_type,generic_inferences,span)));
if ([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(name,rhs_name)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: mismatched names for dependent types: ‘{}’ and ‘{}’"sv),name,rhs_name),span);
return false;
}
if (args.size() != rhs_args.size()){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: mismatched number of generic parameters for dependent types: ‘{}’ and ‘{}’"sv),name,rhs_name),span);
return false;
}
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (!TRY((this->check_types_for_compat(args.operator[](i),rhs_args.operator[](i),generic_inferences,span)))){
return false;
}
}

}
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& lhs_enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp129 = rhs_type;
if (__jakt_tmp129->__jakt_init_index() == 21 /* GenericEnumInstance */){
Jakt::ids::EnumId const rhs_enum_id = __jakt_tmp129->as.GenericEnumInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const rhs_args = __jakt_tmp129->as.GenericEnumInstance.args;
if (lhs_enum_id.equals(rhs_enum_id)){
Jakt::types::CheckedEnum const lhs_enum = this->get_enum(lhs_enum_id);
if (lhs_args.size() == rhs_args.size()){
size_t idx = static_cast<size_t>(0ULL);
while (idx < lhs_args.size()){
if (!TRY((this->check_types_for_compat(lhs_args.operator[](idx),rhs_args.operator[](idx),generic_inferences,span)))){
return false;
}
++idx;
}
}
else {
this->error(__jakt_format(StringView::from_string_literal("mismatched number of generic parameters for {}"sv),lhs_enum.name),span);
return false;
}

}
}
else {
if (!rhs_type_id.equals(lhs_type_id)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& lhs_params = __jakt_match_value.params;
bool const& lhs_can_throw = __jakt_match_value.can_throw;
Jakt::ids::TypeId const& lhs_return_type_id = __jakt_match_value.return_type_id;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp130 = rhs_type;
if (__jakt_tmp130->__jakt_init_index() == 29 /* Function */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const rhs_params = __jakt_tmp130->as.Function.params;
bool const rhs_can_throw = __jakt_tmp130->as.Function.can_throw;
Jakt::ids::TypeId const rhs_return_type_id = __jakt_tmp130->as.Function.return_type_id;
if (!(lhs_can_throw == rhs_can_throw)){
ByteString const lhs_throw = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<bool>> {
auto __jakt_enum_value = (lhs_can_throw);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Yes"sv));
}else {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("No"sv));
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const rhs_throw = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<bool>> {
auto __jakt_enum_value = (rhs_can_throw);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Yes"sv));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("No"sv));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
this->error(__jakt_format(StringView::from_string_literal("Function can throw mismatch: expected ‘{}’, but got ‘{}’"sv),lhs_throw,rhs_throw),span);
}
if (!(lhs_params.size() == rhs_params.size())){
this->error(__jakt_format(StringView::from_string_literal("Function parameter count mismatch: expected ‘{}’, but got ‘{}’"sv),lhs_params.size(),rhs_params.size()),span);
return false;
}
if (!TRY((this->check_types_for_compat(lhs_return_type_id,rhs_return_type_id,generic_inferences,span)))){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Function type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("The return types differ: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_return_type_id,false))),TRY((this->type_name(rhs_return_type_id,false)))),span);
return false;
}
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(lhs_params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (!TRY((this->check_types_for_compat(lhs_params.operator[](i),rhs_params.operator[](i),generic_inferences,span)))){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Function type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("The parameter types differ at argument {}: expected ‘{}’, but got ‘{}’"sv),JaktInternal::checked_add(i,static_cast<size_t>(1ULL)),TRY((this->type_name(lhs_params.operator[](i),false))),TRY((this->type_name(rhs_params.operator[](i),false)))),span);
return false;
}
}

}
}

}
else {
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::ids::StructId const lhs_struct_id = id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> lhs_args = args;
if (lhs_struct_id.equals(optional_struct_id) || lhs_struct_id.equals(weakptr_struct_id)){
if (lhs_args.size() > static_cast<size_t>(0ULL)){
Jakt::ids::TypeId const inner_lhs_type_id = lhs_args.operator[](static_cast<i64>(0LL));
if (inner_lhs_type_id.equals(rhs_type_id) || this->is_subclass_of(inner_lhs_type_id,rhs_type_id)){
return true;
}
}
}
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp131 = rhs_type;
if (__jakt_tmp131->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp131->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp131->as.GenericInstance.args;
Jakt::ids::StructId const rhs_struct_id = id;
if (lhs_struct_id.equals(rhs_struct_id)){
JaktInternal::DynamicArray<Jakt::ids::TypeId> rhs_args = args;
Jakt::types::CheckedStruct const lhs_struct = this->get_struct(lhs_struct_id);
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>> __jakt_tmp132 = lhs_struct.generic_parameter_defaults;
if (__jakt_tmp132.has_value()){
JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>> const defaults = __jakt_tmp132.value();
if (lhs_args.size() < defaults.size()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_args = lhs_args.operator[](JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}).to_array();
size_t idx = lhs_args.size();
while ((idx < defaults.size()) && defaults.operator[](idx).has_value()){
new_args.push(defaults.operator[](idx).value());
++idx;
}
lhs_args = new_args;
}
if (rhs_args.size() < defaults.size()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_args = rhs_args.operator[](JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}).to_array();
size_t idx = rhs_args.size();
while ((idx < defaults.size()) && defaults.operator[](idx).has_value()){
new_args.push(defaults.operator[](idx).value());
++idx;
}
rhs_args = new_args;
}
}
if (lhs_args.size() == rhs_args.size()){
size_t idx = static_cast<size_t>(0ULL);
while (idx < args.size()){
if (!TRY((this->check_types_for_compat(lhs_args.operator[](idx),rhs_args.operator[](idx),generic_inferences,span)))){
return false;
}
++idx;
}
}
else {
this->error(__jakt_format(StringView::from_string_literal("mismatched number of generic parameters for {}"sv),lhs_struct.name),span);
return false;
}

}
else if (lhs_struct_id.equals(array_struct_id)){
Jakt::ids::TypeId const array_value_type_id = args.operator[](static_cast<i64>(0LL));
if (array_value_type_id.equals(Jakt::types::unknown_type_id())){
return true;
}
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
else {
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}

}
else {
if (!rhs_type_id.equals(lhs_type_id)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
if (lhs_type_id.equals(rhs_type_id)){
return true;
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *rhs_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if (enum_id.equals(id)){
Jakt::types::CheckedEnum const lhs_enum = this->get_enum(enum_id);
if (args.size() != lhs_enum.generic_parameters.size()){
this->error(__jakt_format(StringView::from_string_literal("mismatched number of generic parameters for {}"sv),lhs_enum.name),span);
return false;
}
size_t idx = static_cast<size_t>(0ULL);
while (idx < args.size()){
if (!TRY((this->check_types_for_compat(lhs_enum.generic_parameters.operator[](idx).type_id,args.operator[](idx),generic_inferences,span)))){
return false;
}
++idx;
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* TypeVariable */:{
JaktInternal::Optional<Jakt::ids::TypeId> const maybe_seen_type_id = generic_inferences.get(rhs_type_id);
if (maybe_seen_type_id.has_value()){
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(maybe_seen_type_id.value(),lhs_type_id)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(maybe_seen_type_id.value(),false)))),span);
return false;
}
}
else {
generic_inferences.set(lhs_type_id,rhs_type_id);
}

}
return JaktInternal::ExplicitValue<void>();
default:{
if (!rhs_type_id.equals(lhs_type_id)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
}
return JaktInternal::ExplicitValue<void>();
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
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& lhs_struct_id = __jakt_match_value.value;
{
if (lhs_type_id.equals(rhs_type_id)){
return true;
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = *rhs_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if (!lhs_struct_id.equals(id)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
Jakt::types::CheckedStruct const lhs_struct = this->get_struct(lhs_struct_id);
if (args.size() != lhs_struct.generic_parameters.size()){
this->error(__jakt_format(StringView::from_string_literal("mismatched number of generic parameters for {}"sv),lhs_struct.name),span);
return false;
}
size_t idx = static_cast<size_t>(0ULL);
while (idx < args.size()){
if (!TRY((this->check_types_for_compat(lhs_struct.generic_parameters.operator[](idx).type_id,args.operator[](idx),generic_inferences,span)))){
return false;
}
++idx;
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* TypeVariable */:{
JaktInternal::Optional<Jakt::ids::TypeId> const seen_type_id = generic_inferences.get(rhs_type_id);
if (seen_type_id.has_value()){
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(seen_type_id.value(),lhs_type_id)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(seen_type_id.value(),false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
}
else {
generic_inferences.set(lhs_type_id,rhs_type_id);
}

}
return JaktInternal::ExplicitValue<void>();
default:{
if (this->is_subclass_of(lhs_type_id,rhs_type_id)){
return true;
}
if (!rhs_type_id.equals(lhs_type_id)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
}
return JaktInternal::ExplicitValue<void>();
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
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& lhs_rawptr_type_id = __jakt_match_value.value;
{
if (lhs_rawptr_type_id.equals(rhs_type_id)){
return true;
}
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp133 = rhs_type;
if (__jakt_tmp133->__jakt_init_index() == 25 /* RawPtr */){
Jakt::ids::TypeId const rhs_rawptr_type_id = __jakt_tmp133->as.RawPtr.value;
if (!TRY((this->check_types_for_compat(lhs_rawptr_type_id,rhs_rawptr_type_id,generic_inferences,span)))){
return false;
}
}
else {
if (!rhs_type_id.equals(lhs_type_id)){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& lhs_inner_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp134 = rhs_type;
if (__jakt_tmp134->__jakt_init_index() == 27 /* Reference */){
Jakt::ids::TypeId const rhs_inner_type_id = __jakt_tmp134->as.Reference.value;
if (!TRY((this->check_types_for_compat(lhs_inner_type_id,rhs_inner_type_id,generic_inferences,span)))){
return false;
}
}
else {
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& lhs_inner_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp135 = rhs_type;
if (__jakt_tmp135->__jakt_init_index() == 28 /* MutableReference */){
Jakt::ids::TypeId const rhs_inner_type_id = __jakt_tmp135->as.MutableReference.value;
if (!TRY((this->check_types_for_compat(lhs_inner_type_id,rhs_inner_type_id,generic_inferences,span)))){
return false;
}
}
else {
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(generic_inferences.map(rhs_type_id),generic_inferences.map(lhs_type_id))){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return false;
}
}
return JaktInternal::ExplicitValue<void>();
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

bool Jakt::typechecker::Typechecker::is_subclass_of(Jakt::ids::TypeId const ancestor_type_id,Jakt::ids::TypeId const child_type_id) const {
{
NonnullRefPtr<typename Jakt::types::Type> const ancestor_type = this->get_type(ancestor_type_id);
NonnullRefPtr<typename Jakt::types::Type> const child_type = this->get_type(child_type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp136 = ancestor_type;
if (__jakt_tmp136->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const ancestor_struct_id = __jakt_tmp136->as.Struct.value;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp137 = child_type;
if (__jakt_tmp137->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const child_struct_id = __jakt_tmp137->as.Struct.value;
Jakt::types::CheckedStruct ancestor_struct = this->get_struct(ancestor_struct_id);
Jakt::ids::StructId current_struct_id = child_struct_id;
for (;;){
Jakt::types::CheckedStruct const current_struct = this->get_struct(current_struct_id);
if (current_struct.super_struct_id.has_value()){
if (ancestor_struct_id.equals(current_struct.super_struct_id.value())){
return true;
}
current_struct_id = current_struct.super_struct_id.value();
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

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::substitute_typevars_in_type(Jakt::ids::TypeId const type_id,Jakt::types::GenericInferences const generic_inferences) {
{
return this->program->substitute_typevars_in_type(type_id,generic_inferences,this->current_module_id);
}
}

ErrorOr<Jakt::types::CheckedBlock> Jakt::typechecker::Typechecker::typecheck_block(Jakt::parser::ParsedBlock const parsed_block,Jakt::ids::ScopeId const parent_scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const yield_type_hint) {
{
bool const parent_throws = this->get_scope(parent_scope_id)->can_throw;
Jakt::ids::ScopeId const block_scope_id = this->create_scope(parent_scope_id,parent_throws,ByteString::from_utf8_without_validation("block"sv),true);
Jakt::types::CheckedBlock const old_block = this->current_block;
this->current_block = Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),block_scope_id,Jakt::types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false);
ScopeGuard __jakt_var_66([&] {
this->current_block = old_block;
});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = parsed_block.stmts.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> parsed_statement = _magic_value.value();
{
if (!this->current_block.control_flow.is_reachable()){
this->error(ByteString::from_utf8_without_validation("Unreachable code"sv),parsed_statement->span());
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_statement = TRY((this->typecheck_statement(parsed_statement,block_scope_id,safety_mode,yield_type_hint)));
this->current_block.control_flow = this->current_block.control_flow.updated(checked_statement->control_flow());
JaktInternal::Optional<Jakt::utility::Span> const yield_span = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::utility::Span>, ErrorOr<Jakt::types::CheckedBlock>>{
auto&& __jakt_match_variant = *parsed_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::utility::Span>,ErrorOr<Jakt::types::CheckedBlock>> {
auto __jakt_enum_value = (expr.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(expr.value()->span());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
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
case 16 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::utility::Span>>(expr->span()));
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
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
bool yield_present = false;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const checked_yield_expression = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>>, ErrorOr<Jakt::types::CheckedBlock>>{
auto&& __jakt_match_variant = *checked_statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& expr = __jakt_match_value.expr;
{
yield_present = true;
return JaktInternal::ExplicitValue<JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(expr);
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
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
if (yield_present){
if (yield_span.has_value() && checked_yield_expression.has_value()){
Jakt::ids::TypeId const type_var_type_id = checked_yield_expression.value()->type();
Jakt::ids::TypeId const type_ = TRY((this->resolve_type_var(type_var_type_id,block_scope_id)));
if (checked_yield_expression.value()->__jakt_init_index() == 25 /* OptionalNone */){
this->current_block.yielded_none = true;
}
if (this->current_block.yielded_type.has_value()){
TRY((this->check_types_for_compat(this->current_block.yielded_type.value(),type_,this->generic_inferences,yield_span.value())));
}
else {
this->current_block.yielded_type = static_cast<JaktInternal::Optional<Jakt::ids::TypeId>>(type_);
}

}
else {
if (this->current_block.yielded_type.has_value()){
TRY((this->check_types_for_compat(this->current_block.yielded_type.value(),Jakt::types::void_type_id(),this->generic_inferences,yield_span.value())));
}
else {
this->current_block.yielded_type = static_cast<JaktInternal::Optional<Jakt::ids::TypeId>>(Jakt::types::void_type_id());
}

}

}
this->current_block.statements.push(checked_statement);
}

}
}

if (this->current_block.yielded_type.has_value()){
this->current_block.yielded_type = static_cast<JaktInternal::Optional<Jakt::ids::TypeId>>(TRY((this->substitute_typevars_in_type(this->current_block.yielded_type.value(),this->generic_inferences))));
}
return this->current_block;
}
}

ByteString Jakt::typechecker::Typechecker::debug_description_of(Jakt::ids::ScopeId const scope_id) const {
{
JaktInternal::DynamicArray<ByteString> ss = DynamicArray<ByteString>::create_with({});
Jakt::ids::ScopeId current_scope_id = scope_id;
for (;;){
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(current_scope_id);
ByteString const d = __jakt_format(StringView::from_string_literal("{} (named {})"sv),scope->debug_name,scope->namespace_name);
ss.insert(static_cast<size_t>(0ULL),d);
if (scope->parent.has_value()){
current_scope_id = scope->parent.value();
}
else {
break;
}

}
return Jakt::utility::join(ss,ByteString::from_utf8_without_validation(" -> "sv));
}
}

Jakt::parser::CheckedQualifiers Jakt::typechecker::Typechecker::typecheck_type_qualifiers(JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> const qualifiers) const {
{
JaktInternal::Optional<Jakt::parser::ParsedTypeQualifiers> __jakt_tmp138 = qualifiers;
if (__jakt_tmp138.has_value()){
Jakt::parser::ParsedTypeQualifiers const q = __jakt_tmp138.value();
return Jakt::parser::CheckedQualifiers(q.is_immutable);
}
else {
return Jakt::parser::CheckedQualifiers(false);
}

}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::typecheck_typename(NonnullRefPtr<typename Jakt::parser::ParsedType> const parsed_type,Jakt::ids::ScopeId const scope_id,JaktInternal::Optional<ByteString> const name,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
Jakt::ids::TypeId const output = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<Jakt::ids::TypeId>>{
auto&& __jakt_match_variant = *parsed_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* DependentType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentType;NonnullRefPtr<typename Jakt::parser::ParsedType> const& base = __jakt_match_value.base;
ByteString const& dependent_name = __jakt_match_value.name;
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> const& generic_args = __jakt_match_value.generic_args;
{
Jakt::ids::TypeId const base_type = TRY((this->typecheck_typename(base,scope_id,name,JaktInternal::OptionalNone())));
JaktInternal::DynamicArray<Jakt::ids::TypeId> args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = generic_args.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> arg = _magic_value.value();
{
args.push(TRY((this->typecheck_typename(arg,scope_id,name,JaktInternal::OptionalNone()))));
}

}
}

Jakt::ids::TypeId const type_id = this->find_or_add_type_id(Jakt::types::Type::Dependent(Jakt::parser::CheckedQualifiers(false),base_type,dependent_name,args));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(TRY((this->substitute_typevars_in_type(type_id,this->generic_inferences))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 13 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression(expr,scope_id,Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone())));
NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter = this->interpreter();
NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope = Jakt::interpreter::InterpreterScope::from_runtime_scope(scope_id,this->program,JaktInternal::OptionalNone());
JaktInternal::Optional<Jakt::interpreter::StatementResult> const value = ({ Optional<Jakt::interpreter::StatementResult> __jakt_var_67;
auto __jakt_var_68 = [&]() -> ErrorOr<Jakt::interpreter::StatementResult> { return interpreter->execute_expression(checked_expr,scope); }();
if (!__jakt_var_68.is_error()) __jakt_var_67 = __jakt_var_68.release_value();
__jakt_var_67; });
if (value.has_value()){
Jakt::interpreter::StatementResult __jakt_tmp139 = value.value();
if (__jakt_tmp139.__jakt_init_index() == 5 /* JustValue */){
Jakt::types::Value const resolved_value = __jakt_tmp139.as.JustValue.value;
return this->find_or_add_type_id(Jakt::types::Type::Const(Jakt::parser::CheckedQualifiers(false),resolved_value));
}
}
this->error(ByteString::from_utf8_without_validation("Could not evaluate const expression"sv),expr->span());
return this->find_or_add_type_id(Jakt::types::Type::Unknown(Jakt::parser::CheckedQualifiers(false)));
}
};/*case end*/
case 8 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;NonnullRefPtr<typename Jakt::parser::ParsedType> const& inner = __jakt_match_value.inner;
{
Jakt::ids::TypeId const inner_type_id = TRY((this->typecheck_typename(inner,scope_id,name,JaktInternal::OptionalNone())));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::Reference(Jakt::parser::CheckedQualifiers(false),inner_type_id)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;NonnullRefPtr<typename Jakt::parser::ParsedType> const& inner = __jakt_match_value.inner;
{
Jakt::ids::TypeId const inner_type_id = TRY((this->typecheck_typename(inner,scope_id,name,JaktInternal::OptionalNone())));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::MutableReference(Jakt::parser::CheckedQualifiers(false),inner_type_id)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* NamespacedName */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedName;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<ByteString> const& namespaces = __jakt_match_value.namespaces;
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> const& params = __jakt_match_value.params;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::ScopeId current_namespace_scope_id = scope_id;
{
JaktInternal::ArrayIterator<ByteString> _magic = namespaces.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString ns = _magic_value.value();
{
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> const result = TRY((this->find_namespace_in_scope(current_namespace_scope_id,ns,false,JaktInternal::OptionalNone())));
if (result.has_value()){
current_namespace_scope_id = result.value().template get<0>();
}
else {
this->error(__jakt_format(StringView::from_string_literal("Unknown namespace: '{}'"sv),ns),span);
return Jakt::types::unknown_type_id();
}

}

}
}

JaktInternal::DynamicArray<Jakt::ids::TypeId> generic_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = params.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> param = _magic_value.value();
{
Jakt::ids::TypeId const checked_arg = TRY((this->typecheck_typename(param,scope_id,name,JaktInternal::OptionalNone())));
generic_args.push(checked_arg);
}

}
}

JaktInternal::Optional<Jakt::ids::TypeId> type_id = JaktInternal::OptionalNone();
if (generic_args.is_empty()){
NonnullRefPtr<typename Jakt::parser::ParsedType> const synthetic_typename = Jakt::parser::ParsedType::Name(parsed_type->common.init_common.qualifiers,name,span);
type_id = TRY((this->typecheck_typename(synthetic_typename,current_namespace_scope_id,name,JaktInternal::OptionalNone())));
}
else {
type_id = TRY((this->typecheck_generic_resolved_type(name,generic_args,current_namespace_scope_id,span)));
}

return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(type_id.value());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 0 /* Name */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Name;ByteString const& name = __jakt_match_value.name;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>> const maybe_type_and_scope = TRY((this->find_type_scope(scope_id,name)));
if (maybe_type_and_scope.has_value()){
if (!maybe_type_and_scope.value().template get<1>().equals(this->prelude_scope_id())){
return this->with_qualifiers(this->typecheck_type_qualifiers(parsed_type->common.init_common.qualifiers),maybe_type_and_scope.value().template get<0>());
}
}
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId,ErrorOr<Jakt::ids::TypeId>> {
auto __jakt_enum_value = (name);
if (__jakt_enum_value == ByteString::from_utf8_without_validation("i8"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I8()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("i16"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I16()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("i32"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I32()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("i64"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I64()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("u8"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U8()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("u16"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U16()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("u32"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U32()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("u64"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U64()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("f32"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::F32()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("f64"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::F64()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("c_char"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::CChar()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("c_int"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::CInt()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("usize"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Usize()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("bool"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("void"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("never"sv)) {return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Never()));
}else {{
if (maybe_type_and_scope.has_value()){
return maybe_type_and_scope.value().template get<0>();
}
if (this->get_scope(scope_id)->is_from_generated_code && (name == ByteString::from_utf8_without_validation("unknown"sv))){
return Jakt::types::builtin(Jakt::types::BuiltinType::Unknown());
}
this->error(__jakt_format(StringView::from_string_literal("Unknown type ‘{}’ in scope {}"sv),name,this->debug_description_of(scope_id)),span);
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(Jakt::types::unknown_type_id());
}
VERIFY_NOT_REACHED();
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 15 /* Empty */:{
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(Jakt::types::unknown_type_id());
}
VERIFY_NOT_REACHED();
case 5 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> const& types = __jakt_match_value.types;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> checked_types = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = types.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> parsed_type = _magic_value.value();
{
checked_types.push(TRY((this->typecheck_typename(parsed_type,scope_id,name,JaktInternal::OptionalNone()))));
}

}
}

Jakt::ids::StructId const tuple_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Tuple"sv))));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),tuple_struct_id,checked_types)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;NonnullRefPtr<typename Jakt::parser::ParsedType> const& inner = __jakt_match_value.inner;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::TypeId const inner_type_id = TRY((this->typecheck_typename(inner,scope_id,name,JaktInternal::OptionalNone())));
Jakt::ids::StructId const array_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Array"sv))));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),array_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* Dictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dictionary;NonnullRefPtr<typename Jakt::parser::ParsedType> const& key = __jakt_match_value.key;
NonnullRefPtr<typename Jakt::parser::ParsedType> const& value = __jakt_match_value.value;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::TypeId const key_type_id = TRY((this->typecheck_typename(key,scope_id,name,JaktInternal::OptionalNone())));
Jakt::ids::TypeId const value_type_id = TRY((this->typecheck_typename(value,scope_id,name,JaktInternal::OptionalNone())));
Jakt::ids::StructId const dict_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Dictionary"sv))));
TRY((this->ensure_type_implements_trait(key_type_id,ByteString::from_utf8_without_validation("Hashable"sv),JaktInternal::OptionalNone(),scope_id,span)));
TRY((this->ensure_type_implements_trait(key_type_id,ByteString::from_utf8_without_validation("Equal"sv),DynamicArray<Jakt::ids::TypeId>::create_with({key_type_id}),scope_id,span)));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),dict_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({key_type_id, value_type_id}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* Set */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Set;NonnullRefPtr<typename Jakt::parser::ParsedType> const& inner = __jakt_match_value.inner;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::TypeId const inner_type_id = TRY((this->typecheck_typename(inner,scope_id,name,JaktInternal::OptionalNone())));
Jakt::ids::StructId const set_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Set"sv))));
TRY((this->ensure_type_implements_trait(inner_type_id,ByteString::from_utf8_without_validation("Hashable"sv),JaktInternal::OptionalNone(),scope_id,span)));
TRY((this->ensure_type_implements_trait(inner_type_id,ByteString::from_utf8_without_validation("Equal"sv),DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id}),scope_id,span)));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),set_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* Optional */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Optional;NonnullRefPtr<typename Jakt::parser::ParsedType> const& inner = __jakt_match_value.inner;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::TypeId const inner_type_id = TRY((this->typecheck_typename(inner,scope_id,name,JaktInternal::OptionalNone())));
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* WeakPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WeakPtr;NonnullRefPtr<typename Jakt::parser::ParsedType> const& inner = __jakt_match_value.inner;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::TypeId const inner_type_id = TRY((this->typecheck_typename(inner,scope_id,name,JaktInternal::OptionalNone())));
Jakt::ids::StructId const weakptr_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv))));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),weakptr_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id}))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;NonnullRefPtr<typename Jakt::parser::ParsedType> const& inner = __jakt_match_value.inner;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::TypeId const inner_type_id = TRY((this->typecheck_typename(inner,scope_id,name,JaktInternal::OptionalNone())));
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::RawPtr(Jakt::parser::CheckedQualifiers(false),inner_type_id)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* GenericType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericType;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>> const& generic_parameters = __jakt_match_value.generic_parameters;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> checked_inner_types = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = generic_parameters.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> inner_type = _magic_value.value();
{
Jakt::ids::TypeId const inner_type_id = TRY((this->typecheck_typename(inner_type,scope_id,name,JaktInternal::OptionalNone())));
checked_inner_types.push(inner_type_id);
}

}
}

return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(TRY((this->typecheck_generic_resolved_type(name,checked_inner_types,scope_id,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
NonnullRefPtr<typename Jakt::parser::ParsedType> const& return_type = __jakt_match_value.return_type;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
ByteString const function_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<Jakt::ids::TypeId>> {
auto __jakt_enum_value = (name.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(name.value());
}else {return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_69;
auto __jakt_var_70 = [&]() -> ErrorOr<ByteString> { return __jakt_format(StringView::from_string_literal("lambda{}"sv),this->lambda_count++); }();
if (!__jakt_var_70.is_error()) __jakt_var_69 = __jakt_var_70.release_value();
__jakt_var_69; }).value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }));
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> checked_params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
bool first = true;
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_71([&] {
{
this->generic_inferences.restore(old_generic_inferences);
}

});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedParameter> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedParameter param = _magic_value.value();
{
checked_params.push(TRY((this->typecheck_parameter(param,scope_id,first,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
first = false;
}

}
}

NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = Jakt::types::CheckedFunction::__jakt_create(function_name,span,Jakt::types::CheckedVisibility::Public(),TRY((this->typecheck_typename(return_type,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))),return_type->span(),checked_params,Jakt::types::FunctionGenerics::__jakt_create(scope_id,checked_params,DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({}),DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({})),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),scope_id,Jakt::types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false),can_throw,Jakt::parser::FunctionType::Expression(),Jakt::parser::FunctionLinkage::Internal(),scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default(),false);
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::FunctionId const function_id = module->add_function(checked_function);
JaktInternal::DynamicArray<Jakt::ids::TypeId> param_type_ids = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = checked_function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
param_type_ids.push(param.variable->type_id);
}

}
}

return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(this->find_or_add_type_id(Jakt::types::Type::Function(Jakt::parser::CheckedQualifiers(false),param_type_ids,can_throw,checked_function->return_type_id,function_id)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::parser::CheckedQualifiers const qualifiers = this->typecheck_type_qualifiers(parsed_type->common.init_common.qualifiers);
return this->with_qualifiers(qualifiers,output);
}
}

Jakt::ids::TypeId Jakt::typechecker::Typechecker::with_qualifiers(Jakt::parser::CheckedQualifiers const qualifiers,Jakt::ids::TypeId const type_id) {
{
return this->program->apply_qualifiers_to_type(qualifiers,type_id);
}
}

ErrorOr<void> Jakt::typechecker::Typechecker::ensure_type_implements_trait(Jakt::ids::TypeId const type_id,ByteString const trait_name,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span) {
{
if (this->get_type(type_id)->__jakt_init_index() == 18 /* TypeVariable */){
return {};
}
JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor> const implementation = TRY((this->find_any_singular_trait_implementation(type_id,DynamicArray<ByteString>::create_with({trait_name}),scope_id,span,filter_for_generics)));
if (!implementation.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Type ‘{}’ does not implement trait ‘{}’"sv),TRY((this->type_name(type_id,false))),trait_name),span);
}
}
return {};
}

ErrorOr<JaktInternal::Optional<Jakt::ids::TypeId>> Jakt::typechecker::Typechecker::find_explicitly_specialized_type_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,JaktInternal::DynamicArray<Jakt::ids::TypeId> const arguments,Jakt::utility::Span const span) {
{
JaktInternal::DynamicArray<Jakt::types::SpecializedType> matching_types = DynamicArray<Jakt::types::SpecializedType>::create_with({});
TRY((this->program->template for_each_scope_accessible_unqualified_from_scope<bool>(scope_id,[&matching_types, &name, &arguments, &span, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
if (!mixin.mixin_types){
return Jakt::utility::IterationDecision<bool>::Continue();
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(mixin.scope_id);
if (!scope->explicitly_specialized_types.contains(name)){
return Jakt::utility::IterationDecision<bool>::Continue();
}
Jakt::types::SpecializedType const specialized_type = scope->explicitly_specialized_types.operator[](name);
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_72([&] {
this->generic_inferences.restore(checkpoint);
});
bool is_okay = true;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(specialized_type.arguments.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (arguments.size() <= i){
break;
}
Jakt::ids::TypeId const given_arg = arguments.operator[](i);
Jakt::ids::TypeId const specialized_arg = specialized_type.arguments.operator[](i);
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_73([&] {
this->exit_ignore_error_mode(snapshot);
});
if (!TRY((this->check_types_for_compat(specialized_arg,given_arg,this->generic_inferences,span)))){
is_okay = false;
break;
}
}

}
}

if (is_okay){
matching_types.push(specialized_type);
}
return Jakt::utility::IterationDecision<bool>::Continue();
}
}
,false,JaktInternal::OptionalNone())));
JaktInternal::Optional<Jakt::ids::TypeId> result = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::types::SpecializedType> chosen_specialization = JaktInternal::OptionalNone();
i64 max_seen_specificity = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::SpecializedType> _magic = matching_types.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::SpecializedType> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::SpecializedType specialization = _magic_value.value();
{
i64 total_specificity = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = specialization.arguments.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
total_specificity += this->get_type(arg)->specificity(this->program,static_cast<i64>(1LL) << static_cast<i64>(31LL));
}

}
}

if (total_specificity > max_seen_specificity){
max_seen_specificity = total_specificity;
result = specialization.type_id;
chosen_specialization = specialization;
}
}

}
}

if (chosen_specialization.has_value()){
JaktInternal::Optional<Jakt::types::StructLikeId> __jakt_tmp140 = Jakt::types::StructLikeId::from_type_id(result.value(),this->program);
if (__jakt_tmp140.has_value()){
Jakt::types::StructLikeId const struct_like_id = __jakt_tmp140.value();
this->generic_inferences.set_all(struct_like_id.generic_parameters_as_checked(this->program),chosen_specialization.value().arguments);
}
}
return result;
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::typecheck_generic_resolved_type(ByteString const name,JaktInternal::DynamicArray<Jakt::ids::TypeId> const checked_inner_types,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::ids::TypeId> const explicitly_specialized_type = TRY((this->find_explicitly_specialized_type_in_scope(scope_id,name,checked_inner_types,span)));
if (explicitly_specialized_type.has_value()){
return Jakt::types::StructLikeId::from_type_id(explicitly_specialized_type.value(),this->program).value().specialized_by(checked_inner_types,this->program,this->current_module()->id,Jakt::parser::CheckedQualifiers(false));
}
JaktInternal::Optional<Jakt::ids::StructId> const struct_id = TRY((this->find_struct_in_scope(scope_id,name,JaktInternal::OptionalNone())));
if (struct_id.has_value()){
Jakt::types::CheckedStruct const struct_ = this->get_struct(struct_id.value());
JaktInternal::DynamicArray<Jakt::ids::TypeId> effective_inner_types = checked_inner_types.operator[](JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}).to_array();
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>> __jakt_tmp141 = struct_.generic_parameter_defaults;
if (__jakt_tmp141.has_value()){
JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>> const defaults = __jakt_tmp141.value();
size_t start = effective_inner_types.size();
if (start > defaults.size()){
start = defaults.size();
}
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(start),static_cast<size_t>(defaults.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TypeId> __jakt_tmp142 = defaults.operator[](i);
if (__jakt_tmp142.has_value()){
Jakt::ids::TypeId const default_ = __jakt_tmp142.value();
effective_inner_types.push(default_);
}
else {
break;
}

}

}
}

}
return this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),struct_id.value(),effective_inner_types));
}
JaktInternal::Optional<Jakt::ids::EnumId> const enum_id = TRY((this->program->find_enum_in_scope(scope_id,name,false,JaktInternal::OptionalNone())));
if (enum_id.has_value()){
return this->find_or_add_type_id(Jakt::types::Type::GenericEnumInstance(Jakt::parser::CheckedQualifiers(false),enum_id.value(),checked_inner_types));
}
JaktInternal::Optional<Jakt::ids::TraitId> const trait_id = TRY((this->program->find_trait_in_scope(scope_id,name,false,JaktInternal::OptionalNone())));
if (trait_id.has_value()){
return this->find_or_add_type_id(Jakt::types::Type::GenericTraitInstance(Jakt::parser::CheckedQualifiers(false),trait_id.value(),checked_inner_types));
}
this->error(__jakt_format(StringView::from_string_literal("could not find {}"sv),name),span);
return Jakt::types::unknown_type_id();
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_unary_operation(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr,Jakt::types::CheckedUnaryOperator const checked_op,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode) {
{
Jakt::ids::TypeId const expr_type_id = checked_expr->type();
NonnullRefPtr<typename Jakt::types::Type> const expr_type = this->get_type(expr_type_id);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = checked_op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* PreIncrement */:case 1 /* PostIncrement */:case 2 /* PreDecrement */:case 3 /* PostDecrement */:{
if (this->is_integer(expr_type_id)){
if (!checked_expr->is_mutable(this->program)){
this->error(ByteString::from_utf8_without_validation("Increment/decrement of immutable variable"sv),span);
}
}
else {
this->error(ByteString::from_utf8_without_validation("Increment/decrement of non-numeric value"sv),span);
}

}
return JaktInternal::ExplicitValue<void>();
case 9 /* LogicalNot */:{
if (!TRY((this->check_types_for_compat(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()),checked_expr->type(),this->generic_inferences,span)))){
this->error(ByteString::from_utf8_without_validation("Cannot use a logical Not on a value of non-boolean type"sv),span);
}
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,expr_type_id);
}
return JaktInternal::ExplicitValue<void>();
case 10 /* BitwiseNot */:{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,expr_type_id);
}
return JaktInternal::ExplicitValue<void>();
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;Jakt::types::CheckedTypeCast const& cast = __jakt_match_value.value;
{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,cast.type_id());
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Negate */:{
return this->typecheck_unary_negate(checked_expr,span,expr_type_id);
}
return JaktInternal::ExplicitValue<void>();
case 12 /* Is */:case 13 /* IsEnumVariant */:case 14 /* IsSome */:case 15 /* IsNone */:{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,Jakt::types::builtin(Jakt::types::BuiltinType::Bool()));
}
return JaktInternal::ExplicitValue<void>();
case 16 /* Sizeof */:{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,Jakt::types::builtin(Jakt::types::BuiltinType::Usize()));
}
return JaktInternal::ExplicitValue<void>();
case 6 /* RawAddress */:{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,this->find_or_add_type_id(Jakt::types::Type::RawPtr(Jakt::parser::CheckedQualifiers(false),expr_type_id)));
}
return JaktInternal::ExplicitValue<void>();
case 7 /* Reference */:{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,this->find_or_add_type_id(Jakt::types::Type::Reference(Jakt::parser::CheckedQualifiers(false),expr_type_id)));
}
return JaktInternal::ExplicitValue<void>();
case 8 /* MutableReference */:{
if (!checked_expr->is_mutable(this->program)){
this->error(ByteString::from_utf8_without_validation("Cannot make mutable reference to immutable value"sv),span);
}
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,this->find_or_add_type_id(Jakt::types::Type::MutableReference(Jakt::parser::CheckedQualifiers(false),expr_type_id)));
}
return JaktInternal::ExplicitValue<void>();
case 5 /* Dereference */:{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
if (safety_mode.__jakt_init_index() == 0 /* Safe */){
this->error(ByteString::from_utf8_without_validation("Dereference of raw pointer outside of unsafe block"sv),span);
}
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,type_id);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
this->error(__jakt_format(StringView::from_string_literal("Dereference of a non-pointer type ‘{}’"sv),TRY((this->type_name(expr_type_id,false)))),span);
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return JaktInternal::ExplicitValue<void>();
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,checked_op,span,expr_type_id);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_unary_negate(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,Jakt::utility::Span const span,Jakt::ids::TypeId const type_id) {
{
if ((!this->program->is_integer(type_id)) || this->program->is_signed(type_id)){
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),expr,Jakt::types::CheckedUnaryOperator::Negate(),span,type_id);
}
Jakt::ids::TypeId const flipped_sign_type = this->get_type(type_id)->flip_signedness();
Jakt::types::CheckedNumericConstant const constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedNumericConstant, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;Jakt::types::CheckedNumericConstant const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(val);
};/*case end*/
default:{
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),expr,Jakt::types::CheckedUnaryOperator::Negate(),span,type_id);
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::NumberConstant const number = constant.number_constant().value();
size_t const raw_number = number.to_usize();
size_t const max_signed = infallible_integer_cast<size_t>(Jakt::types::Type::I64(Jakt::parser::CheckedQualifiers(false))->max());
i64 negated_number = static_cast<i64>(0LL);
if (raw_number == JaktInternal::checked_add(max_signed,static_cast<size_t>(1ULL))){
negated_number = Jakt::types::Type::I64(Jakt::parser::CheckedQualifiers(false))->min();
}
if (raw_number <= max_signed){
negated_number = JaktInternal::checked_sub(static_cast<i64>(0LL),infallible_integer_cast<i64>(raw_number));
}
Jakt::types::NumberConstant const negated_number_constant = Jakt::types::NumberConstant::Signed(static_cast<i64>(negated_number));
if ((raw_number > JaktInternal::checked_add(max_signed,static_cast<size_t>(1ULL))) || (!negated_number_constant.can_fit_number(flipped_sign_type,this->program))){
this->error(__jakt_format(StringView::from_string_literal("Negative literal -{} too small for type ‘{}’"sv),raw_number,TRY((this->type_name(flipped_sign_type,false)))),span);
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),expr,Jakt::types::CheckedUnaryOperator::Negate(),span,type_id);
}
Jakt::types::CheckedNumericConstant const new_constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedNumericConstant, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *this->get_type(flipped_sign_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */:return JaktInternal::ExplicitValue(Jakt::types::CheckedNumericConstant::I8(infallible_integer_cast<i8>(negated_number)));
case 7 /* I16 */:return JaktInternal::ExplicitValue(Jakt::types::CheckedNumericConstant::I16(infallible_integer_cast<i16>(negated_number)));
case 8 /* I32 */:return JaktInternal::ExplicitValue(Jakt::types::CheckedNumericConstant::I32(infallible_integer_cast<i32>(negated_number)));
case 9 /* I64 */:return JaktInternal::ExplicitValue(Jakt::types::CheckedNumericConstant::I64(static_cast<i64>(negated_number)));
default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Unreachable"sv));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),new_constant,span,type_id),Jakt::types::CheckedUnaryOperator::Negate(),span,flipped_sign_type);
}
}

ErrorOr<JaktInternal::Tuple<Jakt::types::CheckedBinaryOperator,Jakt::ids::TypeId>> Jakt::typechecker::Typechecker::typecheck_binary_operation(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_lhs,Jakt::parser::BinaryOperator const op,NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_rhs,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span) {
{
Jakt::ids::TypeId const lhs_type_id = checked_lhs->type();
Jakt::ids::TypeId const rhs_type_id = checked_rhs->type();
Jakt::utility::Span const lhs_span = checked_lhs->span();
Jakt::utility::Span const rhs_span = checked_rhs->span();
Jakt::ids::TypeId type_id = checked_lhs->type();
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(scope_id);
Jakt::types::CheckedBinaryOperator checked_operator = Jakt::types::CheckedBinaryOperator(op,JaktInternal::OptionalNone());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<Jakt::types::CheckedBinaryOperator,Jakt::ids::TypeId>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* NoneCoalescing */:case 32 /* NoneCoalescingAssign */:{
if (op.__jakt_init_index() == 32 /* NoneCoalescingAssign */){
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp145 = checked_lhs;
if (__jakt_tmp145->__jakt_init_index() == 24 /* Var */){
NonnullRefPtr<Jakt::types::CheckedVariable> const var = __jakt_tmp145->as.Var.var;
Jakt::utility::Span const span = __jakt_tmp145->as.Var.span;
if (!var->is_mutable){
this->error_with_hint(ByteString::from_utf8_without_validation("left-hand side of ??= must be a mutable variable"sv),span,ByteString::from_utf8_without_validation("This variable isn't marked as mutable"sv),var->definition_span);
return Tuple{checked_operator, Jakt::types::unknown_type_id()};
}
}
else {
this->error(ByteString::from_utf8_without_validation("left-hand side of ??= must be a mutable variable"sv),span);
return Tuple{checked_operator, Jakt::types::unknown_type_id()};
}

}
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp146 = this->get_type(lhs_type_id);
if (__jakt_tmp146->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp146->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp146->as.GenericInstance.args;
if (id.equals(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv)))))){
if (lhs_type_id.equals(rhs_type_id)){
return Tuple{checked_operator, lhs_type_id};
}
Jakt::ids::TypeId const inner_type_id = args.operator[](static_cast<i64>(0LL));
if (inner_type_id.equals(rhs_type_id)){
return Tuple{checked_operator, inner_type_id};
}
}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,ByteString::from_utf8_without_validation("Left side of ?? must be an Optional but isn't"sv),lhs_span);
}

}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,ByteString::from_utf8_without_validation("Left side of ?? must be an Optional but isn't"sv),lhs_span);
}

this->error(__jakt_format(StringView::from_string_literal("None coalescing (??) with incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
return Tuple{checked_operator, lhs_type_id};
}
return JaktInternal::ExplicitValue<void>();
case 18 /* LogicalAnd */:case 19 /* LogicalOr */:{
if (!lhs_type_id.equals(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()))){
this->error(ByteString::from_utf8_without_validation("left side of logical binary operation is not a boolean"sv),lhs_span);
}
if (!rhs_type_id.equals(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()))){
this->error(ByteString::from_utf8_without_validation("right side of logical binary operation is not a boolean"sv),rhs_span);
}
type_id = Jakt::types::builtin(Jakt::types::BuiltinType::Bool());
}
return JaktInternal::ExplicitValue<void>();
case 21 /* Assign */:{
if (!checked_lhs->is_mutable(this->program)){
this->error(ByteString::from_utf8_without_validation("Assignment to immutable variable"sv),checked_lhs->span());
return Tuple{checked_operator, lhs_type_id};
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp147 = checked_rhs;
if (__jakt_tmp147->__jakt_init_index() == 25 /* OptionalNone */){
Jakt::utility::Span const span = __jakt_tmp147->as.OptionalNone.span;
Jakt::ids::TypeId const type_id = __jakt_tmp147->as.OptionalNone.type_id;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp148 = this->get_type(lhs_type_id);
if (__jakt_tmp148->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp148->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp148->as.GenericInstance.args;
if (id.equals(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv)))))){
return Tuple{checked_operator, lhs_type_id};
}
if (!id.equals(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv)))))){
this->error(ByteString::from_utf8_without_validation("Cannot assign None to a non-optional type"sv),span);
}
}
else {
this->error(ByteString::from_utf8_without_validation("Cannot assign None to a non-optional type"sv),span);
}

}
NonnullRefPtr<typename Jakt::types::Type> const lhs_type = TRY((this->unwrap_type_from_optional_if_needed(this->get_type(lhs_type_id))));
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp149 = lhs_type;
if (__jakt_tmp149->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp149->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp149->as.GenericInstance.args;
if ((this->program->get_struct(id).name == ByteString::from_utf8_without_validation("WeakPtr"sv)) && (!lhs_type_id.equals(rhs_type_id))){
JaktInternal::Optional<Jakt::ids::TypeId> const unified_type = TRY((this->unify(args.operator[](static_cast<i64>(0LL)),lhs_span,checked_rhs->type(),rhs_span)));
if (unified_type.has_value()){
return Tuple{checked_operator, unified_type.value()};
}
}
}
Jakt::ids::TypeId const effective_lhs_type_id = this->find_or_add_type_id(lhs_type);
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
JaktInternal::Optional<Jakt::ids::TypeId> result = TRY((this->unify(lhs_type_id,lhs_span,rhs_type_id,rhs_span)));
if (!result.has_value()){
result = TRY((this->unify(effective_lhs_type_id,lhs_span,rhs_type_id,rhs_span)));
}
this->exit_ignore_error_mode(snapshot);
if (!result.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Assignment between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span);
}
return Tuple{checked_operator, result.value_or(lhs_type_id)};
}
return JaktInternal::ExplicitValue<void>();
case 27 /* AddAssign */:case 28 /* SubtractAssign */:case 29 /* MultiplyAssign */:case 31 /* DivideAssign */:case 30 /* ModuloAssign */:case 22 /* BitwiseAndAssign */:case 23 /* BitwiseOrAssign */:case 24 /* BitwiseXorAssign */:case 25 /* BitwiseLeftShiftAssign */:case 26 /* BitwiseRightShiftAssign */:case 0 /* Add */:case 1 /* Subtract */:case 2 /* Multiply */:case 3 /* Divide */:case 4 /* Modulo */:case 5 /* LessThan */:case 6 /* LessThanOrEqual */:case 7 /* GreaterThan */:case 8 /* GreaterThanOrEqual */:case 9 /* Equal */:case 10 /* NotEqual */:{
JaktInternal::DynamicArray<ByteString> const empty_array = DynamicArray<ByteString>::create_with({});
JaktInternal::Tuple<JaktInternal::DynamicArray<ByteString>,bool> const trait_names_is_assignment_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<ByteString>,bool>, ErrorOr<JaktInternal::Tuple<Jakt::types::CheckedBinaryOperator,Jakt::ids::TypeId>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Add"sv), ByteString::from_utf8_without_validation("ThrowingAdd"sv)}), false});
case 1 /* Subtract */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Subtract"sv), ByteString::from_utf8_without_validation("ThrowingSubtract"sv)}), false});
case 2 /* Multiply */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Multiply"sv), ByteString::from_utf8_without_validation("ThrowingMultiply"sv)}), false});
case 3 /* Divide */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Divide"sv), ByteString::from_utf8_without_validation("ThrowingDivide"sv)}), false});
case 4 /* Modulo */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Modulo"sv), ByteString::from_utf8_without_validation("ThrowingModulo"sv)}), false});
case 5 /* LessThan */:case 6 /* LessThanOrEqual */:case 7 /* GreaterThan */:case 8 /* GreaterThanOrEqual */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Compare"sv), ByteString::from_utf8_without_validation("ThrowingCompare"sv)}), false});
case 9 /* Equal */:case 10 /* NotEqual */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Equal"sv), ByteString::from_utf8_without_validation("ThrowingEqual"sv)}), false});
case 27 /* AddAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("AddAssign"sv), ByteString::from_utf8_without_validation("ThrowingAddAssign"sv)}), true});
case 28 /* SubtractAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("SubtractAssign"sv), ByteString::from_utf8_without_validation("ThrowingSubtractAssign"sv)}), true});
case 29 /* MultiplyAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("MultiplyAssign"sv), ByteString::from_utf8_without_validation("ThrowingMultiplyAssign"sv)}), true});
case 31 /* DivideAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("DivideAssign"sv), ByteString::from_utf8_without_validation("ThrowingDivideAssign"sv)}), true});
case 30 /* ModuloAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("ModuloAssign"sv), ByteString::from_utf8_without_validation("ThrowingModuloAssign"sv)}), true});
case 22 /* BitwiseAndAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("BitwiseAndAssign"sv), ByteString::from_utf8_without_validation("ThrowingBitwiseAndAssign"sv)}), true});
case 23 /* BitwiseOrAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("BitwiseOrAssign"sv), ByteString::from_utf8_without_validation("ThrowingBitwiseOrAssign"sv)}), true});
case 24 /* BitwiseXorAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("BitwiseXorAssign"sv), ByteString::from_utf8_without_validation("ThrowingBitwiseXorAssign"sv)}), true});
case 25 /* BitwiseLeftShiftAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("BitwiseLeftShiftAssign"sv), ByteString::from_utf8_without_validation("ThrowingBitwiseLeftShiftAssign"sv)}), true});
case 26 /* BitwiseRightShiftAssign */:return JaktInternal::ExplicitValue(Tuple{DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("BitwiseRightShiftAssign"sv), ByteString::from_utf8_without_validation("ThrowingBitwiseRightShiftAssign"sv)}), true});
default:return JaktInternal::ExplicitValue(Tuple{empty_array, false});
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<ByteString> const trait_names = trait_names_is_assignment_.template get<0>();
bool const is_assignment = trait_names_is_assignment_.template get<1>();

ByteString const function_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<JaktInternal::Tuple<Jakt::types::CheckedBinaryOperator,Jakt::ids::TypeId>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("add"sv));
case 1 /* Subtract */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("subtract"sv));
case 2 /* Multiply */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("multiply"sv));
case 3 /* Divide */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("divide"sv));
case 4 /* Modulo */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("modulo"sv));
case 5 /* LessThan */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("less_than"sv));
case 6 /* LessThanOrEqual */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("less_than_or_equal"sv));
case 7 /* GreaterThan */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("greater_than"sv));
case 8 /* GreaterThanOrEqual */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("greater_than_or_equal"sv));
case 9 /* Equal */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("equals"sv));
case 10 /* NotEqual */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("not_equals"sv));
case 27 /* AddAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("add_assign"sv));
case 28 /* SubtractAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("subtract_assign"sv));
case 29 /* MultiplyAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("multiply_assign"sv));
case 31 /* DivideAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("divide_assign"sv));
case 30 /* ModuloAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("modulo_assign"sv));
case 22 /* BitwiseAndAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("bitwise_and_assign"sv));
case 23 /* BitwiseOrAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("bitwise_or_assign"sv));
case 24 /* BitwiseXorAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("bitwise_xor_assign"sv));
case 25 /* BitwiseLeftShiftAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("bitwise_left_shift_assign"sv));
case 26 /* BitwiseRightShiftAssign */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("bitwise_right_shift_assign"sv));
default:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation(""sv));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor> const add_trait_implementation = TRY((this->find_any_singular_trait_implementation(lhs_type_id,trait_names,scope_id,lhs_span,DynamicArray<Jakt::ids::TypeId>::create_with({rhs_type_id}))));
JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor> __jakt_tmp290 = add_trait_implementation;
if (__jakt_tmp290.has_value()){
Jakt::typechecker::TraitImplementationDescriptor const implementation = __jakt_tmp290.value();
if (implementation.trait_name.starts_with(ByteString::from_utf8_without_validation("Throwing"sv)) && (!scope->can_throw)){
this->error(ByteString::from_utf8_without_validation("Call to function that may throw needs to be in a try statement or a function marked as throws"sv),span);
}
JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool> const parent_id___ = TRY((this->struct_like_id_from_type_id(lhs_type_id,scope_id,span,false,true)));
JaktInternal::Optional<Jakt::types::StructLikeId> const parent_id = parent_id___.template get<0>();
bool const _ = parent_id___.template get<1>();

JaktInternal::Optional<Jakt::ids::FunctionId> const implementation_function_id = TRY((this->find_function_matching_trait_implementation_in_scope(lhs_type_id,parent_id.map([&](auto& _value) { return _value.scope_id(this->program); }).value_or_lazy_evaluated([&] { return scope_id; }),function_name,implementation)));
if (implementation_function_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const implementation_function = this->get_function(implementation_function_id.value());
if (implementation_function->is_mutating() && (!checked_lhs->is_mutable(this->program))){
if (is_assignment){
this->error(ByteString::from_utf8_without_validation("Assignment to immutable variable"sv),span);
}
else {
this->error(ByteString::from_utf8_without_validation("Cannot call mutating function on an immutable object instance"sv),span);
}

}
type_id = implementation_function->return_type_id;
Jakt::types::CheckedCall call_expression = Jakt::types::CheckedCall(DynamicArray<Jakt::types::ResolvedNamespace>::create_with({}),function_name,DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({Tuple{ByteString::from_utf8_without_validation(""sv), checked_rhs}}),DynamicArray<Jakt::ids::TypeId>::create_with({}),implementation_function_id,type_id,implementation_function->can_throw,implementation_function->external_name,implementation_function->force_inline);
checked_operator.trait_implementation = Jakt::types::OperatorTraitImplementation(implementation.trait_id,implementation.implemented_type_args,call_expression);
}
else {
this->error(__jakt_format(StringView::from_string_literal("Failed to find an implementation of '{}' (trait {}) in type {} ({})"sv),function_name,implementation.trait_name,TRY((this->type_name(lhs_type_id,false))),this->get_scope(parent_id.value().scope_id(this->program))->debug_name),lhs_span);
type_id = Jakt::types::unknown_type_id();
}

}
else if (!is_assignment){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp292 = this->get_type(lhs_type_id);
if (__jakt_tmp292->__jakt_init_index() == 25 /* RawPtr */){
Jakt::ids::TypeId const lhs_deref_type_id = __jakt_tmp292->as.RawPtr.value;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp291 = this->get_type(rhs_type_id);
if (__jakt_tmp291->__jakt_init_index() == 25 /* RawPtr */){
Jakt::ids::TypeId const rhs_deref_type_id = __jakt_tmp291->as.RawPtr.value;
if (lhs_deref_type_id.equals(rhs_deref_type_id)){
type_id = Jakt::types::builtin(Jakt::types::BuiltinType::Bool());
}
else {
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp293 = this->get_type(lhs_type_id);
if (__jakt_tmp293->__jakt_init_index() == 18 /* TypeVariable */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const trait_implementations = __jakt_tmp293->as.TypeVariable.trait_implementations;
if (trait_implementations.is_empty()){
}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Consider implementing ‘(Throwing){}<{}, ...>’ for the type of this expression (‘{}’)"sv),trait_names.operator[](static_cast<i64>(0LL)),TRY((this->type_name(rhs_type_id,false))),TRY((this->type_name(lhs_type_id,false)))),lhs_span);
}

}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Consider implementing ‘(Throwing){}<{}, ...>’ for the type of this expression (‘{}’)"sv),trait_names.operator[](static_cast<i64>(0LL)),TRY((this->type_name(rhs_type_id,false))),TRY((this->type_name(lhs_type_id,false)))),lhs_span);
}

}

}
else {
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp294 = this->get_type(lhs_type_id);
if (__jakt_tmp294->__jakt_init_index() == 18 /* TypeVariable */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const trait_implementations = __jakt_tmp294->as.TypeVariable.trait_implementations;
if (trait_implementations.is_empty()){
}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Consider implementing ‘(Throwing){}<{}, ...>’ for the type of this expression (‘{}’)"sv),trait_names.operator[](static_cast<i64>(0LL)),TRY((this->type_name(rhs_type_id,false))),TRY((this->type_name(lhs_type_id,false)))),lhs_span);
}

}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Consider implementing ‘(Throwing){}<{}, ...>’ for the type of this expression (‘{}’)"sv),trait_names.operator[](static_cast<i64>(0LL)),TRY((this->type_name(rhs_type_id,false))),TRY((this->type_name(lhs_type_id,false)))),lhs_span);
}

}

}
else {
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp295 = this->get_type(lhs_type_id);
if (__jakt_tmp295->__jakt_init_index() == 18 /* TypeVariable */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const trait_implementations = __jakt_tmp295->as.TypeVariable.trait_implementations;
if (trait_implementations.is_empty()){
}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Consider implementing ‘(Throwing){}<{}, ...>’ for the type of this expression (‘{}’)"sv),trait_names.operator[](static_cast<i64>(0LL)),TRY((this->type_name(rhs_type_id,false))),TRY((this->type_name(lhs_type_id,false)))),lhs_span);
}

}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Consider implementing ‘(Throwing){}<{}, ...>’ for the type of this expression (‘{}’)"sv),trait_names.operator[](static_cast<i64>(0LL)),TRY((this->type_name(rhs_type_id,false))),TRY((this->type_name(lhs_type_id,false)))),lhs_span);
}

}

}
else {
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp296 = this->get_type(lhs_type_id);
if (__jakt_tmp296->__jakt_init_index() == 18 /* TypeVariable */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const trait_implementations = __jakt_tmp296->as.TypeVariable.trait_implementations;
if (trait_implementations.is_empty()){
}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Consider implementing ‘(Throwing){}<{}, ...>’ for the type of this expression (‘{}’)"sv),trait_names.operator[](static_cast<i64>(0LL)),TRY((this->type_name(rhs_type_id,false))),TRY((this->type_name(lhs_type_id,false)))),lhs_span);
}

}
else {
this->error_with_hint(__jakt_format(StringView::from_string_literal("Binary arithmetic operation between incompatible types (‘{}’ and ‘{}’)"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Consider implementing ‘(Throwing){}<{}, ...>’ for the type of this expression (‘{}’)"sv),trait_names.operator[](static_cast<i64>(0LL)),TRY((this->type_name(rhs_type_id,false))),TRY((this->type_name(lhs_type_id,false)))),lhs_span);
}

}

}
return JaktInternal::ExplicitValue<void>();
default:{
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Tuple{checked_operator, type_id};
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_statement(NonnullRefPtr<typename Jakt::parser::ParsedStatement> const statement,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedStatement>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::Expression(TRY((this->typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone()))),span));
};/*case end*/
case 2 /* UnsafeBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnsafeBlock;Jakt::parser::ParsedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::Block(TRY((this->typecheck_block(block,scope_id,Jakt::types::SafetyMode::Unsafe(),JaktInternal::OptionalNone()))),span));
};/*case end*/
case 14 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_yield(expr,span,scope_id,safety_mode,type_hint))));
};/*case end*/
case 12 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_return(expr,span,scope_id,safety_mode))));
};/*case end*/
case 6 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::parser::ParsedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_block_statement(block,scope_id,safety_mode,span))));
};/*case end*/
case 15 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;Jakt::parser::ParsedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_inline_cpp(block,span,safety_mode))));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename Jakt::parser::ParsedStatement> const& statement = __jakt_match_value.statement;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_defer(statement,scope_id,safety_mode,span))));
};/*case end*/
case 7 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::parser::ParsedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_loop(block,scope_id,safety_mode,span))));
};/*case end*/
case 13 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_throw(expr,scope_id,safety_mode,span))));
};/*case end*/
case 8 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& condition = __jakt_match_value.condition;
Jakt::parser::ParsedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_while(condition,block,scope_id,safety_mode,span))));
};/*case end*/
case 11 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;Jakt::utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->typecheck_continue(span));
};/*case end*/
case 10 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;Jakt::utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->typecheck_break(span));
};/*case end*/
case 4 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;Jakt::parser::ParsedVarDecl const& var = __jakt_match_value.var;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& init = __jakt_match_value.init;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_var_decl(var,init,scope_id,safety_mode,span))));
};/*case end*/
case 3 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename Jakt::parser::ParsedStatement> const& var_decl = __jakt_match_value.var_decl;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_destructuring_assignment(vars,var_decl,scope_id,safety_mode,span))));
};/*case end*/
case 5 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& condition = __jakt_match_value.condition;
Jakt::parser::ParsedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const& else_statement = __jakt_match_value.else_statement;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_if(condition,then_block,else_statement,scope_id,safety_mode,span))));
};/*case end*/
case 17 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;Jakt::utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::Garbage(span));
};/*case end*/
case 9 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;ByteString const& iterator_name = __jakt_match_value.iterator_name;
Jakt::utility::Span const& name_span = __jakt_match_value.name_span;
bool const& is_destructuring = __jakt_match_value.is_destructuring;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& range = __jakt_match_value.range;
Jakt::parser::ParsedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_for(iterator_name,name_span,is_destructuring,range,block,scope_id,safety_mode,span))));
};/*case end*/
case 16 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::parser::ParsedBlock const& else_block = __jakt_match_value.else_block;
Jakt::parser::ParsedBlock const& remaining_code = __jakt_match_value.remaining_code;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_guard(expr,else_block,remaining_code,scope_id,safety_mode,span))));
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

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_yield(JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const expr,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
if (!expr.has_value()){
return Jakt::types::CheckedStatement::Yield(JaktInternal::OptionalNone(),span);
}
return Jakt::types::CheckedStatement::Yield(TRY((this->typecheck_expression(expr.value(),scope_id,safety_mode,type_hint))),span);
}
}

NonnullRefPtr<typename Jakt::types::CheckedStatement> Jakt::typechecker::Typechecker::typecheck_continue(Jakt::utility::Span const span) {
{
if (!(this->break_continue_tracker.__jakt_init_index() == 1 /* AnyLoop */)){
if (this->break_continue_tracker.__jakt_init_index() == 2 /* Defer */){
this->error(ByteString::from_utf8_without_validation("‘continue’ inside loop cannot be deferred"sv),span);
}
else {
this->error(ByteString::from_utf8_without_validation("‘continue’ statements can only be used inside loops"sv),span);
}

}
return Jakt::types::CheckedStatement::Continue(span);
}
}

NonnullRefPtr<typename Jakt::types::CheckedStatement> Jakt::typechecker::Typechecker::typecheck_break(Jakt::utility::Span const span) {
{
if (!(this->break_continue_tracker.__jakt_init_index() == 1 /* AnyLoop */)){
if (this->break_continue_tracker.__jakt_init_index() == 2 /* Defer */){
this->error(ByteString::from_utf8_without_validation("‘break’ inside loop cannot be deferred"sv),span);
}
else {
this->error(ByteString::from_utf8_without_validation("‘break’ statements can only be used inside loops"sv),span);
}

}
return Jakt::types::CheckedStatement::Break(span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_guard(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,Jakt::parser::ParsedBlock const else_block,Jakt::parser::ParsedBlock const remaining_code,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
bool seen_scope_exit = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = else_block.stmts.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> statement = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* Break */:case 11 /* Continue */:case 12 /* Return */:case 13 /* Throw */:{
seen_scope_exit = true;
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
default:{
}
return JaktInternal::ExplicitValue<void>();
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

Jakt::types::CheckedBlock const checked_else_block = TRY((this->typecheck_block(else_block,scope_id,safety_mode,JaktInternal::OptionalNone())));
if ((!seen_scope_exit) && checked_else_block.control_flow.may_return()){
this->error(ByteString::from_utf8_without_validation("Else block of guard must either `return`, `break`, `continue`, or `throw`"sv),span);
}
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> pre_condition = DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({});
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((this->expand_context_for_bindings(expr,JaktInternal::OptionalNone(),pre_condition,remaining_code,Jakt::parser::ParsedStatement::Block(else_block,span),scope_id,span)));
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const new_condition = new_condition_new_then_block_new_else_statement_.template get<0>();
JaktInternal::Optional<Jakt::parser::ParsedBlock> const new_then_block = new_condition_new_then_block_new_else_statement_.template get<1>();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const new_else_statement = new_condition_new_then_block_new_else_statement_.template get<2>();

TRY(([](Jakt::typechecker::Typechecker& self, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const& unchecked, Jakt::ids::ScopeId scope_id, Jakt::types::SafetyMode safety_mode, Jakt::types::CheckedBlock& block) -> ErrorOr<void> {{
if (!unchecked.is_empty()){
block.statements.add_capacity(unchecked.size());
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = unchecked.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> stmt = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_stmt = TRY((self.typecheck_statement(stmt,scope_id,safety_mode,JaktInternal::OptionalNone())));
block.control_flow = block.control_flow.updated(checked_stmt->control_flow());
block.statements.push(checked_stmt);
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
((*this),pre_condition,scope_id,safety_mode,this->current_block)));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_condition = TRY((this->typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
if (!checked_condition->type().equals(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()))){
this->error(ByteString::from_utf8_without_validation("Condition must be a boolean expression"sv),new_condition->span());
}
Jakt::types::CheckedBlock const checked_block = TRY((this->typecheck_block(new_then_block.value(),scope_id,safety_mode,JaktInternal::OptionalNone())));
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> checked_else = JaktInternal::OptionalNone();
if (new_else_statement.has_value()){
checked_else = TRY((this->typecheck_statement(new_else_statement.value(),scope_id,safety_mode,JaktInternal::OptionalNone())));
}
if (checked_block.yielded_type.has_value()){
return Jakt::types::CheckedStatement::Yield(Jakt::types::CheckedExpression::Match(JaktInternal::OptionalNone(),checked_condition,DynamicArray<Jakt::types::CheckedMatchCase>::create_with({Jakt::types::CheckedMatchCase(DynamicArray<Jakt::types::CheckedMatchPattern>::create_with({Jakt::types::CheckedMatchPattern::Expression(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),Jakt::types::CheckedExpression::Boolean(JaktInternal::OptionalNone(),true,span),span)}),Jakt::types::CheckedMatchBody::Expression(Jakt::types::CheckedExpression::Block(JaktInternal::OptionalNone(),checked_block,span,checked_block.yielded_type.value()))), Jakt::types::CheckedMatchCase(DynamicArray<Jakt::types::CheckedMatchPattern>::create_with({Jakt::types::CheckedMatchPattern::CatchAll(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),false,span)}),Jakt::types::CheckedMatchBody::Block(checked_else_block))}),span,checked_block.yielded_type.value(),false),span);
}
return Jakt::types::CheckedStatement::If(checked_condition,checked_block,checked_else,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_for(ByteString const iterator_name,Jakt::utility::Span const name_span,bool const is_destructuring,NonnullRefPtr<typename Jakt::parser::ParsedExpression> const range,Jakt::parser::ParsedBlock const block,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
Jakt::typechecker::BreakContinueLegalityTracker const previous_break_continue_tracker = this->break_continue_tracker;
this->break_continue_tracker = Jakt::typechecker::BreakContinueLegalityTracker::AnyLoop();
ScopeGuard __jakt_var_74([&] {
this->break_continue_tracker = previous_break_continue_tracker;
});
JaktInternal::Optional<Jakt::utility::Span> const maybe_span = block.find_yield_span();
if (maybe_span.has_value()){
this->error(ByteString::from_utf8_without_validation("a 'for' loop block is not allowed to yield values"sv),maybe_span.value());
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> iterable_expr = TRY((this->typecheck_expression_and_dereference_if_needed(range,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::ids::TypeId resolved_iterable_result_type = Jakt::types::unknown_type_id();
NonnullRefPtr<typename Jakt::parser::ParsedExpression> expression_to_iterate = range;
JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor> const iterable_trait_implementation = TRY((this->find_any_singular_trait_implementation(iterable_expr->type(),DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Iterable"sv), ByteString::from_utf8_without_validation("ThrowingIterable"sv)}),scope_id,iterable_expr->span(),JaktInternal::OptionalNone())));
if (!iterable_trait_implementation.has_value()){
JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor> const into_iterator_trait_implementation = TRY((this->find_any_singular_trait_implementation(iterable_expr->type(),DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("IntoIterator"sv), ByteString::from_utf8_without_validation("IntoThrowingIterator"sv)}),scope_id,iterable_expr->span(),JaktInternal::OptionalNone())));
if (!into_iterator_trait_implementation.has_value()){
this->error_with_hint(ByteString::from_utf8_without_validation("Iterable expression is not iterable"sv),range->span(),__jakt_format(StringView::from_string_literal("Consider implementing (Throwing)Iterable<T> or Into(Throwing)Iterator<T> for the type of this expression (‘{}’)"sv),TRY((this->type_name(iterable_expr->type(),false)))),range->span());
}
else {
resolved_iterable_result_type = into_iterator_trait_implementation.value().implemented_type_args.operator[](static_cast<i64>(0LL));
expression_to_iterate = Jakt::parser::ParsedExpression::MethodCall(range,Jakt::parser::ParsedCall(DynamicArray<ByteString>::create_with({}),ByteString::from_utf8_without_validation("iterator"sv),DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>>::create_with({}),DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>>::create_with({})),false,name_span);
}

}
else {
resolved_iterable_result_type = iterable_trait_implementation.value().implemented_type_args.operator[](static_cast<i64>(0LL));
}

NonnullRefPtr<typename Jakt::parser::ParsedStatement> const rewritten_statement = Jakt::parser::ParsedStatement::Block(Jakt::parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({Jakt::parser::ParsedStatement::VarDecl(Jakt::parser::ParsedVarDecl(ByteString::from_utf8_without_validation("_magic"sv),Jakt::parser::ParsedType::Empty(JaktInternal::OptionalNone()),true,JaktInternal::OptionalNone(),name_span,JaktInternal::OptionalNone()),expression_to_iterate,span), Jakt::parser::ParsedStatement::Loop(Jakt::parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({Jakt::parser::ParsedStatement::VarDecl(Jakt::parser::ParsedVarDecl(ByteString::from_utf8_without_validation("_magic_value"sv),Jakt::parser::ParsedType::Empty(JaktInternal::OptionalNone()),false,JaktInternal::OptionalNone(),name_span,JaktInternal::OptionalNone()),Jakt::parser::ParsedExpression::MethodCall(Jakt::parser::ParsedExpression::Var(ByteString::from_utf8_without_validation("_magic"sv),name_span),Jakt::parser::ParsedCall(DynamicArray<ByteString>::create_with({}),ByteString::from_utf8_without_validation("next"sv),DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>>::create_with({}),DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>>::create_with({})),false,name_span),span), Jakt::parser::ParsedStatement::If(Jakt::parser::ParsedExpression::UnaryOp(Jakt::parser::ParsedExpression::MethodCall(Jakt::parser::ParsedExpression::Var(ByteString::from_utf8_without_validation("_magic_value"sv),name_span),Jakt::parser::ParsedCall(DynamicArray<ByteString>::create_with({}),ByteString::from_utf8_without_validation("has_value"sv),DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>>::create_with({}),DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>>::create_with({})),false,name_span),Jakt::parser::UnaryOperator::LogicalNot(),name_span),Jakt::parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({Jakt::parser::ParsedStatement::Break(span)})),JaktInternal::OptionalNone(),span), Jakt::parser::ParsedStatement::VarDecl(Jakt::parser::ParsedVarDecl(iterator_name,Jakt::parser::ParsedType::Empty(JaktInternal::OptionalNone()),true,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::utility::Span>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>>> {
auto __jakt_enum_value = (is_destructuring);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(name_span);
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),name_span,JaktInternal::OptionalNone()),Jakt::parser::ParsedExpression::ForcedUnwrap(Jakt::parser::ParsedExpression::Var(ByteString::from_utf8_without_validation("_magic_value"sv),name_span),name_span),span), Jakt::parser::ParsedStatement::Block(block,span)})),span)})),span);
return this->typecheck_statement(rewritten_statement,scope_id,safety_mode,JaktInternal::OptionalNone());
}
}

ErrorOr<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>>> Jakt::typechecker::Typechecker::expand_context_for_bindings(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const condition,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const acc,JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>& pre_condition,JaktInternal::Optional<Jakt::parser::ParsedBlock> const then_block,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const else_statement,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>>>>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& lhs = __jakt_match_value.lhs;
Jakt::parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& rhs = __jakt_match_value.rhs;
{
if (op.__jakt_init_index() == 18 /* LogicalAnd */){
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> pre_rhs = DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({});
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>> const rhs_condition_rhs_then_block_rhs_else_statement_ = TRY((this->expand_context_for_bindings(rhs,acc,pre_rhs,then_block,else_statement,scope_id,span)));
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const rhs_condition = rhs_condition_rhs_then_block_rhs_else_statement_.template get<0>();
JaktInternal::Optional<Jakt::parser::ParsedBlock> const rhs_then_block = rhs_condition_rhs_then_block_rhs_else_statement_.template get<1>();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const rhs_else_statement = rhs_condition_rhs_then_block_rhs_else_statement_.template get<2>();

if (pre_rhs.is_empty()){
return this->expand_context_for_bindings(lhs,rhs_condition,pre_condition,rhs_then_block,rhs_else_statement,scope_id,span);
}
else {
Jakt::parser::ParsedBlock then_block = Jakt::parser::ParsedBlock(pre_rhs);
then_block.stmts.push(Jakt::parser::ParsedStatement::If(rhs_condition,rhs_then_block.value_or_lazy_evaluated([&] { return Jakt::parser::ParsedBlock(DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({})); }),rhs_else_statement,rhs->span()));
return this->expand_context_for_bindings(lhs,JaktInternal::OptionalNone(),pre_condition,then_block,else_statement,scope_id,lhs->span());
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::parser::UnaryOperator const& op = __jakt_match_value.op;
{
Jakt::parser::UnaryOperator __jakt_tmp297 = op;
if (__jakt_tmp297.__jakt_init_index() == 13 /* IsEnumVariant */){
NonnullRefPtr<typename Jakt::parser::ParsedType> const inner = __jakt_tmp297.as.IsEnumVariant.inner;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const bindings = __jakt_tmp297.as.IsEnumVariant.bindings;
ByteString const tmp_name = __jakt_format(StringView::from_string_literal("__jakt_tmp{}"sv),this->temp_var_count);
this->temp_var_count++;
Jakt::parser::ParsedVarDecl const tmp_decl = Jakt::parser::ParsedVarDecl(tmp_name,Jakt::parser::ParsedType::Empty(JaktInternal::OptionalNone()),true,JaktInternal::OptionalNone(),expr->span(),JaktInternal::OptionalNone());
NonnullRefPtr<typename Jakt::parser::ParsedStatement> const var_decl_stmt = Jakt::parser::ParsedStatement::VarDecl(tmp_decl,expr,expr->span());
pre_condition.push(var_decl_stmt);
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const unary_op_single_condition = Jakt::parser::ParsedExpression::UnaryOp(Jakt::parser::ParsedExpression::Var(tmp_name,expr->span()),Jakt::parser::UnaryOperator::Is(inner),span);
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> outer_if_stmts = DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({});
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
Jakt::ids::ScopeId const wrapped_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,ByteString::from_utf8_without_validation("hidden-temp-var-in-IsEnumVariant"sv),true);
TRY((this->typecheck_statement(var_decl_stmt,wrapped_scope_id,Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone())));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const pre_checked_unary_op = TRY((this->typecheck_expression(unary_op_single_condition,wrapped_scope_id,Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone())));
this->exit_ignore_error_mode(snapshot);
{
JaktInternal::ArrayIterator<Jakt::parser::EnumVariantPatternArgument> _magic = bindings.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::EnumVariantPatternArgument> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::EnumVariantPatternArgument binding = _magic_value.value();
{
Jakt::parser::ParsedVarDecl const var = Jakt::parser::ParsedVarDecl(binding.binding,Jakt::parser::ParsedType::Empty(JaktInternal::OptionalNone()),false,JaktInternal::OptionalNone(),binding.span,JaktInternal::OptionalNone());
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const tmp_access = Jakt::parser::ParsedExpression::Var(tmp_name,binding.span);
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp298 = pre_checked_unary_op;
if (__jakt_tmp298->__jakt_init_index() == 6 /* UnaryOp */){
Jakt::types::CheckedUnaryOperator const op = __jakt_tmp298->as.UnaryOp.op;
if (op.__jakt_init_index() == 14 /* IsSome */){
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const init = Jakt::parser::ParsedExpression::ForcedUnwrap(tmp_access,span);
outer_if_stmts.push(Jakt::parser::ParsedStatement::VarDecl(var,init,span));
}
else {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const enum_variant_arg = Jakt::parser::ParsedExpression::EnumVariantArg(tmp_access,binding,inner,span);
outer_if_stmts.push(Jakt::parser::ParsedStatement::VarDecl(var,enum_variant_arg,span));
}

}
else {
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const enum_variant_arg = Jakt::parser::ParsedExpression::EnumVariantArg(tmp_access,binding,inner,span);
outer_if_stmts.push(Jakt::parser::ParsedStatement::VarDecl(var,enum_variant_arg,span));
}

}

}
}

NonnullRefPtr<typename Jakt::parser::ParsedExpression> inner_condition = condition;
if (then_block.has_value()){
if (acc.has_value()){
inner_condition = acc.value();
outer_if_stmts.push(Jakt::parser::ParsedStatement::If(inner_condition,then_block.value(),else_statement,span));
}
else {
outer_if_stmts.push_values(then_block.value().stmts);
}

}
Jakt::parser::ParsedBlock const new_then_block = Jakt::parser::ParsedBlock(outer_if_stmts);
return this->expand_context_for_bindings(unary_op_single_condition,JaktInternal::OptionalNone(),pre_condition,new_then_block,else_statement,scope_id,span);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename Jakt::parser::ParsedExpression> base_condition = condition;
if (acc.has_value()){
base_condition = Jakt::parser::ParsedExpression::BinaryOp(condition,Jakt::parser::BinaryOperator::LogicalAnd(),acc.value(),span);
}
return Tuple{base_condition, then_block, else_statement};
}
}


ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_if(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const condition,Jakt::parser::ParsedBlock const then_block,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const else_statement,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> prev_unchecked = DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({});
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((this->expand_context_for_bindings(condition,JaktInternal::OptionalNone(),prev_unchecked,then_block,else_statement,scope_id,span)));
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const new_condition = new_condition_new_then_block_new_else_statement_.template get<0>();
JaktInternal::Optional<Jakt::parser::ParsedBlock> const new_then_block = new_condition_new_then_block_new_else_statement_.template get<1>();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const new_else_statement = new_condition_new_then_block_new_else_statement_.template get<2>();

TRY(([](Jakt::typechecker::Typechecker& self, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const& unchecked, Jakt::ids::ScopeId scope_id, Jakt::types::SafetyMode safety_mode, Jakt::types::CheckedBlock& block) -> ErrorOr<void> {{
if (!unchecked.is_empty()){
block.statements.add_capacity(unchecked.size());
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = unchecked.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> stmt = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_stmt = TRY((self.typecheck_statement(stmt,scope_id,safety_mode,JaktInternal::OptionalNone())));
block.control_flow = block.control_flow.updated(checked_stmt->control_flow());
block.statements.push(checked_stmt);
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
((*this),prev_unchecked,scope_id,safety_mode,this->current_block)));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_condition = TRY((this->typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
if (!checked_condition->type().equals(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()))){
this->error(ByteString::from_utf8_without_validation("Condition must be a boolean expression"sv),new_condition->span());
}
Jakt::types::CheckedBlock const checked_block = TRY((this->typecheck_block(new_then_block.value(),scope_id,safety_mode,JaktInternal::OptionalNone())));
if (checked_block.yielded_type.has_value()){
this->error(ByteString::from_utf8_without_validation("An 'if' block is not allowed to yield values"sv),new_then_block.value().find_yield_span().value());
}
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> checked_else = JaktInternal::OptionalNone();
if (new_else_statement.has_value()){
checked_else = TRY((this->typecheck_statement(new_else_statement.value(),scope_id,safety_mode,JaktInternal::OptionalNone())));
}
return Jakt::types::CheckedStatement::If(checked_condition,checked_block,checked_else,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_destructuring_assignment(JaktInternal::DynamicArray<Jakt::parser::ParsedVarDecl> const vars,NonnullRefPtr<typename Jakt::parser::ParsedStatement> const var_decl,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> var_decls = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_tuple_var_decl = TRY((this->typecheck_statement(var_decl,scope_id,safety_mode,JaktInternal::OptionalNone())));
Jakt::ids::TypeId expr_type_id = Jakt::types::unknown_type_id();
Jakt::ids::VarId tuple_var_id = Jakt::ids::VarId(Jakt::ids::ModuleId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL));
NonnullRefPtr<typename Jakt::types::CheckedStatement> __jakt_tmp299 = checked_tuple_var_decl;
if (__jakt_tmp299->__jakt_init_index() == 3 /* VarDecl */){
Jakt::ids::VarId const var_id = __jakt_tmp299->as.VarDecl.var_id;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const init = __jakt_tmp299->as.VarDecl.init;
expr_type_id = init->type();
tuple_var_id = var_id;
}
else {
this->error(ByteString::from_utf8_without_validation("Destructuting assignment should be a variable declaration"sv),span);
}

JaktInternal::DynamicArray<Jakt::ids::TypeId> inner_types = DynamicArray<Jakt::ids::TypeId>::create_with({});
NonnullRefPtr<typename Jakt::types::Type> const tuple_type = this->get_type(expr_type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp300 = tuple_type;
if (__jakt_tmp300->__jakt_init_index() == 20 /* GenericInstance */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp300->as.GenericInstance.args;
inner_types = args;
}
else {
this->error(ByteString::from_utf8_without_validation("Tuple Type should be Generic Instance"sv),span);
}

NonnullRefPtr<Jakt::types::CheckedVariable> const tuple_variable = this->program->get_variable(tuple_var_id);
if (vars.size() == inner_types.size()){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(vars.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::parser::ParsedVarDecl new_var = vars.operator[](i);
new_var.parsed_type = Jakt::parser::ParsedType::Name(JaktInternal::OptionalNone(),TRY((this->type_name(inner_types.operator[](i),false))),span);
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const init = Jakt::parser::ParsedExpression::IndexedTuple(Jakt::parser::ParsedExpression::Var(tuple_variable->name,span),i,false,span);
var_decls.push(TRY((this->typecheck_var_decl(vars.operator[](i),init,scope_id,safety_mode,span))));
}

}
}

}
else {
this->error(ByteString::from_utf8_without_validation("Tuple inner types sould have same size as tuple members"sv),span);
}

return Jakt::types::CheckedStatement::DestructuringAssignment(var_decls,checked_tuple_var_decl,span);
}
}

NonnullRefPtr<Jakt::interpreter::Interpreter> Jakt::typechecker::Typechecker::interpreter() {
{
return Jakt::interpreter::Interpreter::create(this->compiler,this->program,Jakt::types::TypecheckFunctions::__jakt_create([this](Jakt::parser::ParsedBlock parsed_block, Jakt::ids::ScopeId parent_scope_id, Jakt::types::SafetyMode safety_mode, JaktInternal::Optional<Jakt::ids::TypeId> yield_type_hint, JaktInternal::Optional<Jakt::ids::FunctionId> containing_function_id) -> ErrorOr<Jakt::types::CheckedBlock> {{
JaktInternal::Optional<Jakt::ids::FunctionId> const previous_function_id = this->current_function_id;
this->current_function_id = containing_function_id;
ScopeGuard __jakt_var_75([&] {
{
this->current_function_id = previous_function_id;
}

});
JaktInternal::Optional<Jakt::typechecker::TypeHint> type_hint = JaktInternal::OptionalNone();
if (yield_type_hint.has_value()){
type_hint = Jakt::typechecker::TypeHint::MustBe(yield_type_hint.value());
}
return this->typecheck_block(parsed_block,parent_scope_id,safety_mode,type_hint);
}
}
,[this](NonnullRefPtr<Jakt::types::CheckedFunction> function) -> ErrorOr<Jakt::ids::FunctionId> {{
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::FunctionId const id = module->next_function_id();
module->functions.push(function);
return id;
}
}
),DynamicArray<Jakt::utility::Span>::create_with({}));
}
}

bool Jakt::typechecker::Typechecker::scope_lifetime_subsumes(JaktInternal::Optional<Jakt::ids::ScopeId> const larger,JaktInternal::Optional<Jakt::ids::ScopeId> const smaller) const {
{
if (!larger.has_value()){
return false;
}
if (!smaller.has_value()){
return true;
}
Jakt::ids::ScopeId const larger_id = larger.value();
Jakt::ids::ScopeId const smaller_id = smaller.value();
if (larger_id.equals(smaller_id)){
return false;
}
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = this->program->get_scope(smaller_id)->parent;
while (scope_id.has_value()){
if (scope_id.value().equals(larger_id)){
return true;
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(scope_id.value());
{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child_scope_id = _magic_value.value();
{
if (child_scope_id.equals(larger_id)){
return true;
}
}

}
}

scope_id = scope->parent;
}
return false;
}
}

JaktInternal::Optional<Jakt::ids::ScopeId> Jakt::typechecker::Typechecker::scope_lifetime_union(JaktInternal::Optional<Jakt::ids::ScopeId> const first,JaktInternal::Optional<Jakt::ids::ScopeId> const second) const {
{
if ((!first.has_value()) || (!second.has_value())){
return JaktInternal::OptionalNone();
}
Jakt::ids::ScopeId const first_id = first.value();
Jakt::ids::ScopeId const second_id = second.value();
if (first_id.equals(this->root_scope_id())){
return second_id;
}
if (second_id.equals(this->root_scope_id())){
return first_id;
}
{
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(first_id);
while (scope_id.has_value()){
if (scope_id.value().equals(second_id)){
return first_id;
}
scope_id = this->get_scope(scope_id.value())->parent;
}
}

{
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(second_id);
while (scope_id.has_value()){
if (scope_id.value().equals(first_id)){
return second_id;
}
scope_id = this->get_scope(scope_id.value())->parent;
}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> Jakt::typechecker::Typechecker::required_scope_id_in_hierarchy_for(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,Jakt::ids::ScopeId const current_scope_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>, ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */:case 1 /* NumericConstant */:case 2 /* QuotedString */:case 3 /* ByteConstant */:case 4 /* CharacterConstant */:case 5 /* CCharacterConstant */:case 34 /* Reflect */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(this->root_scope_id()), expr});
case 7 /* BinaryOp */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;Jakt::types::CheckedUnaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>, ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* PreIncrement */:case 2 /* PreDecrement */:return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
case 5 /* Dereference */:return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
case 7 /* Reference */:case 8 /* MutableReference */:return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
case 11 /* TypeCast */:return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
default:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
{
JaktInternal::Optional<Jakt::ids::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = _magic_value.value();
{
final_scope_id = this->scope_lifetime_union(final_scope_id,TRY((this->required_scope_id_in_hierarchy_for(val,current_scope_id))).template get<0>());
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(Tuple{final_scope_id, expr});
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
{
JaktInternal::Optional<Jakt::ids::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = _magic_value.value();
{
final_scope_id = this->scope_lifetime_union(final_scope_id,TRY((this->required_scope_id_in_hierarchy_for(val,current_scope_id))).template get<0>());
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(Tuple{final_scope_id, expr});
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
{
JaktInternal::Optional<Jakt::ids::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = _magic_value.value();
{
final_scope_id = this->scope_lifetime_union(final_scope_id,TRY((this->required_scope_id_in_hierarchy_for(val,current_scope_id))).template get<0>());
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(Tuple{final_scope_id, expr});
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
{
JaktInternal::Optional<Jakt::ids::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> key__val__ = _magic_value.value();
{
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt__key__val__ = key__val__;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const key = jakt__key__val__.template get<0>();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const val = jakt__key__val__.template get<1>();

final_scope_id = this->scope_lifetime_union(final_scope_id,this->scope_lifetime_union(TRY((this->required_scope_id_in_hierarchy_for(key,current_scope_id))).template get<0>(),TRY((this->required_scope_id_in_hierarchy_for(val,current_scope_id))).template get<0>()));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(Tuple{final_scope_id, expr});
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* Range */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 18 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 19 /* Match */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 20 /* EnumVariantArg */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 21 /* Call */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(var->owner_scope.value_or_lazy_evaluated([&] { return current_scope_id; })), expr});
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(var->owner_scope.value_or_lazy_evaluated([&] { return current_scope_id; })), expr});
};/*case end*/
case 25 /* OptionalNone */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 26 /* OptionalSome */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 28 /* Block */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::types::CheckedCapture> const& captures = __jakt_match_value.captures;
{
JaktInternal::Optional<Jakt::ids::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedCapture> _magic = captures.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedCapture> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedCapture capture = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = JaktInternal::OptionalNone();
if ((capture.__jakt_init_index() == 2 /* ByMutableReference */) || (capture.__jakt_init_index() == 1 /* ByReference */)){
JaktInternal::Optional<JaktInternal::Optional<Jakt::ids::ScopeId>> const scope_id = TRY((this->find_var_in_scope(current_scope_id,capture.common.init_common.name,JaktInternal::OptionalNone()))).map([](auto& _value) { return _value->owner_scope; });
}
final_scope_id = this->scope_lifetime_union(final_scope_id,scope_id);
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(Tuple{final_scope_id, expr});
}
VERIFY_NOT_REACHED();
};/*case end*/
case 30 /* DependentFunction */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentFunction;JaktInternal::DynamicArray<Jakt::types::CheckedCapture> const& captures = __jakt_match_value.captures;
{
JaktInternal::Optional<Jakt::ids::ScopeId> final_scope_id = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedCapture> _magic = captures.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedCapture> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedCapture capture = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = JaktInternal::OptionalNone();
if ((capture.__jakt_init_index() == 2 /* ByMutableReference */) || (capture.__jakt_init_index() == 1 /* ByReference */)){
JaktInternal::Optional<JaktInternal::Optional<Jakt::ids::ScopeId>> const scope_id = TRY((this->find_var_in_scope(current_scope_id,capture.common.init_common.name,JaktInternal::OptionalNone()))).map([](auto& _value) { return _value->owner_scope; });
}
final_scope_id = this->scope_lifetime_union(final_scope_id,scope_id);
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(Tuple{final_scope_id, expr});
}
VERIFY_NOT_REACHED();
};/*case end*/
case 31 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(expr,current_scope_id))));
};/*case end*/
case 32 /* Try */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 33 /* TryBlock */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
case 35 /* Garbage */:return JaktInternal::ExplicitValue(Tuple{static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(JaktInternal::OptionalNone()), expr});
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_var_decl(Jakt::parser::ParsedVarDecl const var,NonnullRefPtr<typename Jakt::parser::ParsedExpression> const init,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
Jakt::ids::TypeId lhs_type_id = TRY((this->typecheck_typename(var.parsed_type,scope_id,var.name,JaktInternal::OptionalNone())));
NonnullRefPtr<typename Jakt::types::CheckedExpression> checked_expr = TRY((this->typecheck_expression(init,scope_id,safety_mode,Jakt::typechecker::TypeHint::MustBe(lhs_type_id))));
Jakt::ids::TypeId const rhs_type_id = checked_expr->type();
if (rhs_type_id.equals(Jakt::types::void_type_id())){
this->error(ByteString::from_utf8_without_validation("Cannot assign `void` to a variable"sv),checked_expr->span());
}
else {
NonnullRefPtr<typename Jakt::types::Type> const unwrapped_type = TRY((this->unwrap_type_from_optional_if_needed(this->get_type(rhs_type_id))));
if (unwrapped_type->equals(this->get_type(Jakt::types::void_type_id()))){
this->error(ByteString::from_utf8_without_validation("Cannot assign `Optional<void>` to a variable"sv),checked_expr->span());
}
}

if (this->get_type(lhs_type_id)->common.init_common.qualifiers.is_immutable){
lhs_type_id = this->with_qualifiers(Jakt::parser::CheckedQualifiers(false),lhs_type_id);
if (var.is_mutable){
this->error(ByteString::from_utf8_without_validation("Cannot have a mutable binding to an immutable object"sv),var.span);
}
}
if (lhs_type_id.equals(Jakt::types::unknown_type_id()) && (!rhs_type_id.equals(Jakt::types::unknown_type_id()))){
lhs_type_id = rhs_type_id;
}
Jakt::ids::StructId const weak_ptr_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv))));
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
if (this->type_contains_reference(lhs_type_id)){
JaktInternal::Tuple<JaktInternal::Optional<Jakt::ids::ScopeId>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const init_scope_id_cause_expr_ = TRY((this->required_scope_id_in_hierarchy_for(checked_expr,scope_id)));
JaktInternal::Optional<Jakt::ids::ScopeId> const init_scope_id = init_scope_id_cause_expr_.template get<0>();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const cause_expr = init_scope_id_cause_expr_.template get<1>();

if (this->scope_lifetime_subsumes(scope_id,init_scope_id)){
this->error_with_hint(ByteString::from_utf8_without_validation("Cannot assign a reference to a variable that outlives the reference"sv),checked_expr->span(),ByteString::from_utf8_without_validation("Limited by this expression's lifetime"sv),cause_expr->span());
}
}
NonnullRefPtr<typename Jakt::types::Type> const lhs_type = this->get_type(lhs_type_id);
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp301 = checked_expr;
if (__jakt_tmp301->__jakt_init_index() == 25 /* OptionalNone */){
Jakt::utility::Span const span = __jakt_tmp301->as.OptionalNone.span;
Jakt::ids::TypeId const type_id = __jakt_tmp301->as.OptionalNone.type_id;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp302 = lhs_type;
if (__jakt_tmp302->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp302->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp302->as.GenericInstance.args;
if (!(id.equals(optional_struct_id) || id.equals(weak_ptr_struct_id))){
this->error(ByteString::from_utf8_without_validation("Cannot assign None to a non-optional type"sv),span);
}
}
else {
this->error(ByteString::from_utf8_without_validation("Cannot assign None to a non-optional type"sv),span);
}

}
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp303 = lhs_type;
if (__jakt_tmp303->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp303->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp303->as.GenericInstance.args;
if (id.equals(weak_ptr_struct_id)){
if ((!lhs_type_id.equals(rhs_type_id)) && ((!args.operator[](static_cast<i64>(0LL)).equals(rhs_type_id)) && ((!rhs_type_id.equals(Jakt::types::unknown_type_id())) && (!this->is_subclass_of(args.operator[](static_cast<i64>(0LL)),rhs_type_id))))){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),checked_expr->span());
}
}
else if (id.equals(optional_struct_id)){
if ((!lhs_type_id.equals(rhs_type_id)) && ((!args.operator[](static_cast<i64>(0LL)).equals(rhs_type_id)) && ((!rhs_type_id.equals(Jakt::types::unknown_type_id())) && (!this->is_subclass_of(args.operator[](static_cast<i64>(0LL)),rhs_type_id))))){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),checked_expr->span());
}
}
else {
if ((!lhs_type_id.equals(rhs_type_id)) && (!rhs_type_id.equals(Jakt::types::unknown_type_id()))){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),checked_expr->span());
}
}

}
else if (lhs_type->is_builtin()){
JaktInternal::Optional<Jakt::types::NumberConstant> const number_constant = checked_expr->to_number_constant(this->program);
bool is_rhs_zero = false;
if (number_constant.has_value()){
is_rhs_zero = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>>>{
auto&& __jakt_match_variant = number_constant.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Signed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Signed;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value == static_cast<i64>(0LL));
};/*case end*/
case 1 /* Unsigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsigned;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value == static_cast<u64>(0ULL));
};/*case end*/
case 2 /* Floating */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Floating;f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value == static_cast<f64>(0));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
if ((!(this->is_numeric(lhs_type_id) && is_rhs_zero)) && (this->is_integer(lhs_type_id) ^ this->is_integer(rhs_type_id))){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),checked_expr->span());
return Jakt::types::CheckedStatement::Garbage(span);
}
}
else {
if ((!lhs_type_id.equals(rhs_type_id)) && ((!rhs_type_id.equals(Jakt::types::unknown_type_id())) && (!this->is_subclass_of(lhs_type_id,rhs_type_id)))){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got ‘{}’"sv),TRY((this->type_name(lhs_type_id,false))),TRY((this->type_name(rhs_type_id,false)))),checked_expr->span());
}
}

NonnullRefPtr<Jakt::types::CheckedVariable> const checked_var = Jakt::types::CheckedVariable::__jakt_create(var.name,lhs_type_id,var.is_mutable,var.span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
if (this->dump_type_hints && var.inlay_span.has_value()){
TRY((this->dump_type_hint(lhs_type_id,var.inlay_span.value())));
}
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::VarId const var_id = module->add_variable(checked_var);
this->add_var_to_scope(scope_id,var.name,var_id,checked_var->definition_span);
return Jakt::types::CheckedStatement::VarDecl(var_id,checked_expr,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_while(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const condition,Jakt::parser::ParsedBlock const block,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
Jakt::typechecker::BreakContinueLegalityTracker const previous_break_continue_tracker = this->break_continue_tracker;
this->break_continue_tracker = Jakt::typechecker::BreakContinueLegalityTracker::AnyLoop();
ScopeGuard __jakt_var_76([&] {
this->break_continue_tracker = previous_break_continue_tracker;
});
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> pre_condition = DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({});
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>> const new_condition_new_body__break_ = TRY((this->expand_context_for_bindings(condition,JaktInternal::OptionalNone(),pre_condition,block,Jakt::parser::ParsedStatement::Break(condition->span()),scope_id,span)));
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const new_condition = new_condition_new_body__break_.template get<0>();
JaktInternal::Optional<Jakt::parser::ParsedBlock> const new_body = new_condition_new_body__break_.template get<1>();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _break = new_condition_new_body__break_.template get<2>();

Jakt::ids::ScopeId const loop_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,ByteString::from_utf8_without_validation("loop-condition-scope"sv),true);
Jakt::types::CheckedBlock loop_pre = Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),loop_scope_id,Jakt::types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false);
TRY(([](Jakt::typechecker::Typechecker& self, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const& unchecked, Jakt::ids::ScopeId scope_id, Jakt::types::SafetyMode safety_mode, Jakt::types::CheckedBlock& block) -> ErrorOr<void> {{
if (!unchecked.is_empty()){
block.statements.add_capacity(unchecked.size());
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = unchecked.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> stmt = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_stmt = TRY((self.typecheck_statement(stmt,scope_id,safety_mode,JaktInternal::OptionalNone())));
block.control_flow = block.control_flow.updated(checked_stmt->control_flow());
block.statements.push(checked_stmt);
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
((*this),pre_condition,loop_scope_id,safety_mode,loop_pre)));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_condition = TRY((this->typecheck_expression_and_dereference_if_needed(new_condition,loop_scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
if (!checked_condition->type().equals(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()))){
this->error(ByteString::from_utf8_without_validation("Condition must be a boolean expression"sv),condition->span());
}
Jakt::types::CheckedBlock const checked_block = TRY((this->typecheck_block(new_body.value(),loop_scope_id,safety_mode,JaktInternal::OptionalNone())));
if (checked_block.yielded_type.has_value()){
this->error(ByteString::from_utf8_without_validation("A ‘while’ block is not allowed to yield values"sv),block.find_yield_span().value());
}
if (loop_pre.statements.is_empty()){
return Jakt::types::CheckedStatement::While(checked_condition,checked_block,span);
}
else {
NonnullRefPtr<typename Jakt::types::CheckedStatement> const if_or_break = Jakt::types::CheckedStatement::If(checked_condition,checked_block,Jakt::types::CheckedStatement::Break(checked_condition->span()),span);
loop_pre.control_flow = loop_pre.control_flow.updated(if_or_break->control_flow());
loop_pre.statements.push(if_or_break);
return Jakt::types::CheckedStatement::Loop(loop_pre,span);
}

}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_try_block(NonnullRefPtr<typename Jakt::parser::ParsedStatement> const stmt,ByteString const error_name,Jakt::utility::Span const error_span,Jakt::parser::ParsedBlock const catch_block,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
Jakt::ids::ScopeId const try_scope_id = this->create_scope(scope_id,true,ByteString::from_utf8_without_validation("try"sv),true);
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_stmt = TRY((this->typecheck_statement(stmt,try_scope_id,safety_mode,JaktInternal::OptionalNone())));
Jakt::ids::StructId const error_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Error"sv))));
NonnullRefPtr<Jakt::types::CheckedVariable> const error_decl = Jakt::types::CheckedVariable::__jakt_create(error_name,this->get_struct(error_struct_id).type_id,false,error_span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::VarId const error_id = module->add_variable(error_decl);
NonnullRefPtr<Jakt::types::Scope> const parent_scope = this->get_scope(scope_id);
Jakt::ids::ScopeId const catch_scope_id = this->create_scope(scope_id,parent_scope->can_throw,ByteString::from_utf8_without_validation("catch"sv),true);
this->add_var_to_scope(catch_scope_id,error_name,error_id,error_span);
Jakt::types::CheckedBlock const checked_catch_block = TRY((this->typecheck_block(catch_block,catch_scope_id,safety_mode,JaktInternal::OptionalNone())));
if (checked_catch_block.yielded_type.has_value()){
this->error(ByteString::from_utf8_without_validation("A ‘catch’ block as part of a try block is not allowed to yield values"sv),catch_block.find_yield_span().value());
}
return Jakt::types::CheckedExpression::TryBlock(JaktInternal::OptionalNone(),checked_stmt,checked_catch_block,error_name,error_span,span,Jakt::types::void_type_id());
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_try(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,JaktInternal::Optional<Jakt::parser::ParsedBlock> const catch_block,JaktInternal::Optional<Jakt::utility::Span> const catch_span,JaktInternal::Optional<ByteString> const catch_name,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
Jakt::ids::ScopeId const try_scope_id = this->create_scope(scope_id,true,ByteString::from_utf8_without_validation("try"sv),true);
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression(expr,try_scope_id,safety_mode,type_hint)));
Jakt::ids::StructId const error_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Error"sv))));
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
JaktInternal::Optional<Jakt::types::CheckedBlock> checked_catch_block = JaktInternal::OptionalNone();
Jakt::ids::TypeId const expression_type_id = checked_expr->type();
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
NonnullRefPtr<typename Jakt::types::Type> const optional_type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({expression_type_id}));
Jakt::ids::TypeId const optional_type_id = this->find_or_add_type_id(optional_type);
Jakt::ids::TypeId type_id = optional_type_id;
if (catch_block.has_value()){
NonnullRefPtr<Jakt::types::Scope> const parent_scope = this->get_scope(scope_id);
Jakt::ids::ScopeId const catch_scope_id = this->create_scope(scope_id,parent_scope->can_throw,ByteString::from_utf8_without_validation("catch"sv),true);
if (catch_name.has_value()){
Jakt::ids::StructId const error_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Error"sv))));
NonnullRefPtr<Jakt::types::CheckedVariable> const error_decl = Jakt::types::CheckedVariable::__jakt_create(catch_name.value(),this->get_struct(error_struct_id).type_id,false,span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::VarId const error_id = module->add_variable(error_decl);
this->add_var_to_scope(catch_scope_id,catch_name.value(),error_id,span);
}
Jakt::types::CheckedBlock const block = TRY((this->typecheck_block(catch_block.value(),catch_scope_id,safety_mode,JaktInternal::OptionalNone())));
if (block.control_flow.always_transfers_control() || block.yielded_type.has_value()){
if (!block.yielded_type.value_or_lazy_evaluated([&] { return expression_type_id; }).equals(expression_type_id)){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Expected a value of type ‘{}’, but got ‘{}’"sv),TRY((this->type_name(expression_type_id,false))),TRY((this->type_name(block.yielded_type.value(),false)))),span,__jakt_format(StringView::from_string_literal("Expression 'catch' block must either yield the same type as the expression it is catching, or yield nothing"sv)),span);
}
else {
type_id = block.yielded_type.value_or_lazy_evaluated([&] { return expression_type_id; });
}

}
else {
if (!expression_type_id.equals(Jakt::types::builtin(Jakt::types::BuiltinType::Void()))){
this->error(ByteString::from_utf8_without_validation("In a try expression that returns a value, 'catch' block must either yield a value or transfer control flow"sv),catch_span.value_or_lazy_evaluated([&] { return span; }));
}
}

checked_catch_block = block;
}
return Jakt::types::CheckedExpression::Try(JaktInternal::OptionalNone(),checked_expr,checked_catch_block,catch_span,catch_name,span,type_id,expression_type_id);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_throw(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::ids::TypeId const error_type_id = TRY((this->find_type_in_prelude(ByteString::from_utf8_without_validation("Error"sv))));
if (!checked_expr->type().equals(error_type_id)){
this->error(ByteString::from_utf8_without_validation("throw expression does not produce an error"sv),expr->span());
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(scope_id);
if (!scope->can_throw){
this->error(ByteString::from_utf8_without_validation("Throw statement needs to be in a try statement or a function marked as throws"sv),expr->span());
}
return Jakt::types::CheckedStatement::Throw(checked_expr,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_loop(Jakt::parser::ParsedBlock const parsed_block,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
Jakt::typechecker::BreakContinueLegalityTracker const previous_break_continue_tracker = this->break_continue_tracker;
this->break_continue_tracker = Jakt::typechecker::BreakContinueLegalityTracker::AnyLoop();
ScopeGuard __jakt_var_77([&] {
this->break_continue_tracker = previous_break_continue_tracker;
});
Jakt::types::CheckedBlock const checked_block = TRY((this->typecheck_block(parsed_block,scope_id,safety_mode,JaktInternal::OptionalNone())));
if (checked_block.yielded_type.has_value()){
this->error(ByteString::from_utf8_without_validation("A ‘loop’ block is not allowed to yield values"sv),parsed_block.find_yield_span().value());
}
return Jakt::types::CheckedStatement::Loop(checked_block,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_defer(NonnullRefPtr<typename Jakt::parser::ParsedStatement> const statement,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
Jakt::typechecker::ReturnLegalityTracker const previous_return_tracker = this->return_tracker;
this->return_tracker = Jakt::typechecker::ReturnLegalityTracker::Defer();
ScopeGuard __jakt_var_78([&] {
this->return_tracker = previous_return_tracker;
});
Jakt::typechecker::BreakContinueLegalityTracker const previous_break_continue_tracker = this->break_continue_tracker;
this->break_continue_tracker = Jakt::typechecker::BreakContinueLegalityTracker::Defer();
ScopeGuard __jakt_var_79([&] {
this->break_continue_tracker = previous_break_continue_tracker;
});
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_statement = TRY((this->typecheck_statement(statement,scope_id,safety_mode,JaktInternal::OptionalNone())));
NonnullRefPtr<typename Jakt::types::CheckedStatement> __jakt_tmp304 = checked_statement;
if (__jakt_tmp304->__jakt_init_index() == 5 /* Block */){
Jakt::types::CheckedBlock const block = __jakt_tmp304->as.Block.block;
if (block.yielded_type.has_value()){
this->error(ByteString::from_utf8_without_validation("‘yield’ inside ‘defer’ is meaningless"sv),span);
}
}
return Jakt::types::CheckedStatement::Defer(checked_statement,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_block_statement(Jakt::parser::ParsedBlock const parsed_block,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
Jakt::types::CheckedBlock const checked_block = TRY((this->typecheck_block(parsed_block,scope_id,safety_mode,JaktInternal::OptionalNone())));
if (checked_block.yielded_type.has_value()){
this->error(ByteString::from_utf8_without_validation("A block used as a statement cannot yield values, as the value cannot be observed in any way"sv),parsed_block.find_yield_span().value());
}
return Jakt::types::CheckedStatement::Block(checked_block,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_inline_cpp(Jakt::parser::ParsedBlock const block,Jakt::utility::Span const span,Jakt::types::SafetyMode const safety_mode) {
{
if (safety_mode.__jakt_init_index() == 0 /* Safe */){
this->error(ByteString::from_utf8_without_validation("Use of inline cpp block outside of unsafe block"sv),span);
}
JaktInternal::DynamicArray<ByteString> strings = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = block.stmts.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> statement = _magic_value.value();
{
NonnullRefPtr<typename Jakt::parser::ParsedStatement> __jakt_tmp306 = statement;
if (__jakt_tmp306->__jakt_init_index() == 0 /* Expression */){
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr = __jakt_tmp306->as.Expression.expr;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> __jakt_tmp305 = expr;
if (__jakt_tmp305->__jakt_init_index() == 2 /* QuotedString */){
ByteString const val = __jakt_tmp305->as.QuotedString.val;
Jakt::utility::Span const span = __jakt_tmp305->as.QuotedString.span;
strings.push(val);
}
else {
this->error(ByteString::from_utf8_without_validation("Expected block of strings"sv),span);
}

}
else {
this->error(ByteString::from_utf8_without_validation("Expected block of strings"sv),span);
}

}

}
}

return Jakt::types::CheckedStatement::InlineCpp(strings,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::typechecker::Typechecker::typecheck_return(JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const expr,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode) {
{
if (this->return_tracker.__jakt_init_index() == 2 /* Defer */){
this->error(ByteString::from_utf8_without_validation("‘return’ is not allowed inside ‘defer’"sv),span);
}
if (!expr.has_value()){
if (this->current_function_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const current_function = this->get_function(this->current_function_id.value());
NonnullRefPtr<typename Jakt::types::Type> const return_type = this->get_type(current_function->return_type_id);
if ((!(return_type->__jakt_init_index() == 0 /* Void */)) && (!(return_type->__jakt_init_index() == 16 /* Unknown */))){
this->error_with_hint(__jakt_format(StringView::from_string_literal("’return’ with no value in function ’{}’ returning ’{}’"sv),current_function->name,TRY((this->type_name(current_function->return_type_id,false)))),span,__jakt_format(StringView::from_string_literal("Add return value of type ’{}’ here"sv),TRY((this->type_name(current_function->return_type_id,false)))),span);
}
}
return Jakt::types::CheckedStatement::Return(JaktInternal::OptionalNone(),span);
}
if ((!(this->current_function_id.has_value() && this->get_function(this->current_function_id.value())->is_comptime)) && (expr.value()->__jakt_init_index() == 25 /* Function */)){
this->error(ByteString::from_utf8_without_validation("Returning a function is not currently supported"sv),span);
}
JaktInternal::Optional<Jakt::ids::TypeId> type_hint_id = JaktInternal::OptionalNone();
if (this->current_function_id.has_value()){
type_hint_id = static_cast<JaktInternal::Optional<Jakt::ids::TypeId>>(this->get_function(this->current_function_id.value())->return_type_id);
}
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> pre_condition = DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({});
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>> const new_condition_new_then_block_new_else_statement_ = TRY((this->expand_context_for_bindings(expr.value(),JaktInternal::OptionalNone(),pre_condition,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),scope_id,span)));
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const new_condition = new_condition_new_then_block_new_else_statement_.template get<0>();
JaktInternal::Optional<Jakt::parser::ParsedBlock> const new_then_block = new_condition_new_then_block_new_else_statement_.template get<1>();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const new_else_statement = new_condition_new_then_block_new_else_statement_.template get<2>();

JaktInternal::Optional<Jakt::typechecker::TypeHint> type_hint = JaktInternal::OptionalNone();
if (type_hint_id.has_value()){
type_hint = Jakt::typechecker::TypeHint::MustBe(type_hint_id.value());
}
TRY(([](Jakt::typechecker::Typechecker& self, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const& unchecked, Jakt::ids::ScopeId scope_id, Jakt::types::SafetyMode safety_mode, Jakt::types::CheckedBlock& block) -> ErrorOr<void> {{
if (!unchecked.is_empty()){
block.statements.add_capacity(unchecked.size());
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = unchecked.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> stmt = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_stmt = TRY((self.typecheck_statement(stmt,scope_id,safety_mode,JaktInternal::OptionalNone())));
block.control_flow = block.control_flow.updated(checked_stmt->control_flow());
block.statements.push(checked_stmt);
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
((*this),pre_condition,scope_id,safety_mode,this->current_block)));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,type_hint,span)));
if (type_hint_id.has_value()){
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp307 = checked_expr;
if (__jakt_tmp307->__jakt_init_index() == 25 /* OptionalNone */){
Jakt::utility::Span const span = __jakt_tmp307->as.OptionalNone.span;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp308 = this->get_type(type_hint_id.value());
if (__jakt_tmp308->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp308->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp308->as.GenericInstance.args;
if ((!id.equals(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv)))))) && (!id.equals(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv))))))){
this->error(ByteString::from_utf8_without_validation("Cannot assign None to a non-optional type"sv),span);
}
}
else {
this->error(ByteString::from_utf8_without_validation("Cannot assign None to a non-optional type"sv),span);
}

}
}
return Jakt::types::CheckedStatement::Return(checked_expr,span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::dereference_if_needed(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr,Jakt::utility::Span const span) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *this->get_type(checked_expr->type());
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,Jakt::types::CheckedUnaryOperator::Dereference(),span,type_id));
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),checked_expr,Jakt::types::CheckedUnaryOperator::Dereference(),span,type_id));
};/*case end*/
default:return JaktInternal::ExplicitValue(checked_expr);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_expression_and_dereference_if_needed(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::typechecker::TypeHint> effective_hint = type_hint;
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp310 = type_hint;
if (__jakt_tmp310.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp310.value();
Jakt::typechecker::TypeHint __jakt_tmp309 = hint;
if (__jakt_tmp309.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp309.common.init_common.type_id;
effective_hint = Jakt::typechecker::TypeHint::CouldBe(type_id);
}
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> checked_expr = TRY((this->typecheck_expression(expr,scope_id,safety_mode,effective_hint)));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = TRY((this->dereference_if_needed(checked_expr,span)));
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp312 = type_hint;
if (__jakt_tmp312.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp312.value();
Jakt::typechecker::TypeHint __jakt_tmp311 = hint;
if (__jakt_tmp311.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp311.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return result;
}
}

void Jakt::typechecker::Typechecker::map_generic_arguments(Jakt::ids::TypeId const type_id,JaktInternal::DynamicArray<Jakt::ids::TypeId> const args) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, void>{
auto&& __jakt_match_variant = *this->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedStruct const struct_ = this->get_struct(id);
this->generic_inferences.set_all(struct_.generic_parameters,args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(id);
this->generic_inferences.set_all(enum_.generic_parameters,args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = this->get_trait(id);
this->generic_inferences.set_all(trait_->generic_parameters,args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_indexed_struct(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,ByteString const field_name,Jakt::ids::ScopeId const scope_id,bool const is_optional,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::ids::TypeId const checked_expr_type_id = checked_expr->type();
NonnullRefPtr<typename Jakt::types::Type> const checked_expr_type = this->get_type(checked_expr_type_id);
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_expr_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::ids::TypeId type_id = checked_expr_type_id;
if (is_optional){
if (!id.equals(optional_struct_id)){
this->error(ByteString::from_utf8_without_validation("Optional chaining is only allowed on optional types"sv),span);
return Jakt::types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),checked_expr,field_name,JaktInternal::OptionalNone(),span,is_optional,Jakt::types::unknown_type_id());
}
type_id = args.operator[](static_cast<i64>(0LL));
}
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(type_id);
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_80([&] {
this->generic_inferences.restore(checkpoint);
});
this->map_generic_arguments(type_id,args);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
Jakt::types::CheckedStruct const structure = this->get_struct(struct_id);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = structure.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = this->get_variable(field->variable_id);
if (member->name == field_name){
Jakt::ids::TypeId resolved_type_id = TRY((this->resolve_type_var(member->type_id,scope_id)));
if (is_optional){
resolved_type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({resolved_type_id})));
}
TRY((this->check_member_access(scope_id,structure.scope_id,member,span)));
return Jakt::types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),checked_expr,field_name,field->variable_id,span,is_optional,resolved_type_id);
}
}

}
}

this->error(__jakt_format(StringView::from_string_literal("unknown member of struct: {}.{}"sv),structure.name,field_name),span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const structure = this->get_struct(struct_id);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = structure.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = this->get_variable(field->variable_id);
if (member->name == field_name){
Jakt::ids::TypeId resolved_type_id = TRY((this->resolve_type_var(member->type_id,scope_id)));
if (is_optional){
resolved_type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({resolved_type_id})));
}
TRY((this->check_member_access(scope_id,structure.scope_id,member,span)));
return Jakt::types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),checked_expr,field_name,field->variable_id,span,is_optional,resolved_type_id);
}
}

}
}

this->error(__jakt_format(StringView::from_string_literal("unknown member of struct: {}.{}"sv),structure.name,field_name),span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = this->get_variable(field->variable_id);
if (member->name == field_name){
Jakt::ids::TypeId resolved_type_id = TRY((this->resolve_type_var(member->type_id,scope_id)));
if (is_optional){
resolved_type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({resolved_type_id})));
}
TRY((this->check_member_access(scope_id,enum_.scope_id,member,span)));
return Jakt::types::CheckedExpression::IndexedCommonEnumMember(JaktInternal::OptionalNone(),checked_expr,field_name,span,is_optional,resolved_type_id);
}
}

}
}

this->error(__jakt_format(StringView::from_string_literal("unknown common member of enum: {}.{}"sv),enum_.name,field_name),span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = this->get_variable(field->variable_id);
if (member->name == field_name){
Jakt::ids::TypeId resolved_type_id = TRY((this->resolve_type_var(member->type_id,scope_id)));
if (is_optional){
resolved_type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({resolved_type_id})));
}
TRY((this->check_member_access(scope_id,enum_.scope_id,member,span)));
return Jakt::types::CheckedExpression::IndexedCommonEnumMember(JaktInternal::OptionalNone(),checked_expr,field_name,span,is_optional,resolved_type_id);
}
}

}
}

this->error(__jakt_format(StringView::from_string_literal("unknown common member of enum: {}.{}"sv),enum_.name,field_name),span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:return ({this->error(__jakt_format(StringView::from_string_literal("Member field access on value of non-struct type ‘{}’"sv),TRY((this->type_name(checked_expr_type_id,false)))),span);}), JaktInternal::ExplicitValue<void>();
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
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
if (is_optional){
this->error(ByteString::from_utf8_without_validation("Optional chaining is not allowed on non-optional types"sv),span);
}
Jakt::types::CheckedStruct const structure = this->get_struct(struct_id);
JaktInternal::Optional<Jakt::types::FieldRecord> const field_record = this->lookup_struct_field(struct_id,field_name);
if (field_record.has_value()){
NonnullRefPtr<Jakt::types::CheckedVariable> const member = this->get_variable(field_record.value().field_id);
Jakt::ids::TypeId const resolved_type_id = TRY((this->resolve_type_var(member->type_id,scope_id)));
TRY((this->check_member_access(scope_id,this->get_struct(field_record.value().struct_id).scope_id,member,span)));
return Jakt::types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),checked_expr,field_name,field_record.value().field_id,span,is_optional,resolved_type_id);
}
this->error(__jakt_format(StringView::from_string_literal("unknown member of struct: {}.{}"sv),structure.name,field_name),span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if (is_optional){
this->error(ByteString::from_utf8_without_validation("Optional chaining is not allowed on non-optional types"sv),span);
}
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_81([&] {
this->generic_inferences.restore(checkpoint);
});
this->map_generic_arguments(checked_expr_type_id,args);
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = this->get_variable(field->variable_id);
if (member->name == field_name){
Jakt::ids::TypeId resolved_type_id = TRY((this->resolve_type_var(member->type_id,scope_id)));
if (is_optional){
resolved_type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({resolved_type_id})));
}
TRY((this->check_member_access(scope_id,enum_.scope_id,member,span)));
return Jakt::types::CheckedExpression::IndexedCommonEnumMember(JaktInternal::OptionalNone(),checked_expr,field_name,span,is_optional,resolved_type_id);
}
}

}
}

this->error(__jakt_format(StringView::from_string_literal("unknown common member of enum: {}.{}"sv),enum_.name,field_name),span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
if (is_optional){
this->error(ByteString::from_utf8_without_validation("Optional chaining is not allowed on non-optional types"sv),span);
}
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_82([&] {
this->generic_inferences.restore(checkpoint);
});
this->map_generic_arguments(checked_expr_type_id,args);
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = this->get_variable(field->variable_id);
if (member->name == field_name){
Jakt::ids::TypeId resolved_type_id = TRY((this->resolve_type_var(member->type_id,scope_id)));
if (is_optional){
resolved_type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({resolved_type_id})));
}
TRY((this->check_member_access(scope_id,enum_.scope_id,member,span)));
return Jakt::types::CheckedExpression::IndexedCommonEnumMember(JaktInternal::OptionalNone(),checked_expr,field_name,span,is_optional,resolved_type_id);
}
}

}
}

this->error(__jakt_format(StringView::from_string_literal("unknown common member of enum: {}.{}"sv),enum_.name,field_name),span);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:return ({this->error(__jakt_format(StringView::from_string_literal("Member field access on value of non-struct type ‘{}’"sv),TRY((this->type_name(checked_expr_type_id,false)))),span);}), JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Jakt::types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),checked_expr,field_name,JaktInternal::OptionalNone(),span,is_optional,Jakt::types::unknown_type_id());
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_indexed_tuple(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,size_t const index,Jakt::ids::ScopeId const scope_id,bool const is_optional,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::ids::StructId const tuple_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Tuple"sv))));
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
Jakt::ids::TypeId expr_type_id = Jakt::types::unknown_type_id();
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp313 = this->get_type(checked_expr->type());
if (__jakt_tmp313->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp313->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp313->as.GenericInstance.args;
if (id.equals(tuple_struct_id)){
if (is_optional){
this->error(ByteString::from_utf8_without_validation("Optional chaining is not allowed on a non-optional tuple type"sv),span);
}
if (index >= args.size()){
this->error(ByteString::from_utf8_without_validation("Tuple index past the end of the tuple"sv),span);
}
else {
expr_type_id = args.operator[](index);
}

}
else if (is_optional && id.equals(optional_struct_id)){
Jakt::ids::TypeId const inner_type_id = args.operator[](static_cast<i64>(0LL));
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp314 = this->get_type(inner_type_id);
if (__jakt_tmp314->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp314->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp314->as.GenericInstance.args;
if (id.equals(tuple_struct_id)){
if (index >= args.size()){
this->error(ByteString::from_utf8_without_validation("Optional-chained tuple index past the end of the tuple"sv),span);
}
else {
expr_type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({args.operator[](index)})));
}

}
}
else {
this->error(ByteString::from_utf8_without_validation("Optional-chained tuple index used on non-tuple value"sv),span);
}

}
}
else if (is_optional){
this->error(ByteString::from_utf8_without_validation("Optional-chained tuple index used on non-tuple value"sv),span);
}
else {
this->error(ByteString::from_utf8_without_validation("Tuple index used on non-tuple value"sv),span);
}

return Jakt::types::CheckedExpression::IndexedTuple(JaktInternal::OptionalNone(),checked_expr,index,span,is_optional,expr_type_id);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_comptime_index(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,NonnullRefPtr<typename Jakt::parser::ParsedExpression> const index,Jakt::ids::ScopeId const scope_id,bool const is_optional,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span) {
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_index = TRY((this->typecheck_expression(index,scope_id,safety_mode,JaktInternal::OptionalNone())));
NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter = this->interpreter();
NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope = Jakt::interpreter::InterpreterScope::from_runtime_scope(scope_id,this->program,JaktInternal::OptionalNone());
Jakt::interpreter::StatementResult const index_result = ({ Optional<Jakt::interpreter::StatementResult> __jakt_var_83;
auto __jakt_var_84 = [&]() -> ErrorOr<Jakt::interpreter::StatementResult> { return interpreter->execute_expression(checked_index,scope); }();
if (__jakt_var_84.is_error()) {auto error = __jakt_var_84.release_error();
{
warnln(StringView::from_string_literal("Error while evaluating comptime index: {}"sv),error);
return Jakt::types::CheckedExpression::ComptimeIndex(JaktInternal::OptionalNone(),TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))),checked_index,is_optional,span);
}
} else {__jakt_var_83 = __jakt_var_84.release_value();
}
__jakt_var_83.release_value(); });
Jakt::typechecker::NumericOrStringValue const index_constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::typechecker::NumericOrStringValue, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = index_result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::typechecker::NumericOrStringValue, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *value.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::StringValue(val));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::UnsignedNumericValue(infallible_integer_cast<u64>(val)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::UnsignedNumericValue(infallible_integer_cast<u64>(val)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::UnsignedNumericValue(infallible_integer_cast<u64>(val)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::UnsignedNumericValue(infallible_integer_cast<u64>(val)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::UnsignedNumericValue(infallible_integer_cast<u64>(val)));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::SignedNumericValue(static_cast<i64>(val)));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::SignedNumericValue(static_cast<i64>(val)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::SignedNumericValue(static_cast<i64>(val)));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::typechecker::NumericOrStringValue::SignedNumericValue(static_cast<i64>(val)));
};/*case end*/
default:{
this->error(__jakt_format(StringView::from_string_literal("Index expression evaluation failed: expected numeric or string type, found {}"sv),value.impl),span);
return Jakt::types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default:{
this->error(__jakt_format(StringView::from_string_literal("Index expression evaluation returned an invalid object {}"sv),index_result),span);
return Jakt::types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = index_constant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* StringValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringValue;ByteString const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((this->typecheck_indexed_struct(expr,val,scope_id,is_optional,safety_mode,span))));
};/*case end*/
case 2 /* UnsignedNumericValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnsignedNumericValue;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((this->typecheck_indexed_tuple(expr,infallible_integer_cast<size_t>(val),scope_id,is_optional,safety_mode,span))));
};/*case end*/
case 1 /* SignedNumericValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SignedNumericValue;i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((this->typecheck_indexed_tuple(expr,infallible_integer_cast<size_t>(val),scope_id,is_optional,safety_mode,span))));
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

ErrorOr<void> Jakt::typechecker::Typechecker::check_member_access(Jakt::ids::ScopeId const accessor,Jakt::ids::ScopeId const accessee,NonnullRefPtr<Jakt::types::CheckedVariable> const member,Jakt::utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = member->visibility;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Private */:{
if (!this->scope_can_access(accessor,accessee)){
this->error(__jakt_format(StringView::from_string_literal("Can't access field ‘{}’, because it is marked private"sv),member->name),span);
}
}
return JaktInternal::ExplicitValue<void>();
case 2 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> const& scopes = __jakt_match_value.scopes;
{
TRY((this->check_restricted_access(accessor,ByteString::from_utf8_without_validation("field"sv),accessee,member->name,scopes,span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

ErrorOr<void> Jakt::typechecker::Typechecker::check_method_access(Jakt::ids::ScopeId const accessor,Jakt::ids::ScopeId const accessee,NonnullRefPtr<Jakt::types::CheckedFunction> const method,Jakt::utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = method->visibility;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Private */:{
if (!this->scope_can_access(accessor,accessee)){
if (!(method->type.__jakt_init_index() == 0 /* Normal */)){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Can't access constructor ‘{}’, because it is marked private"sv),method->name),span,ByteString::from_utf8_without_validation("Private constructors are created if any fields are private"sv),span);
}
else {
this->error(__jakt_format(StringView::from_string_literal("Can't access method ‘{}’, because it is marked private"sv),method->name),span);
}

}
}
return JaktInternal::ExplicitValue<void>();
case 2 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> const& scopes = __jakt_match_value.scopes;
{
TRY((this->check_restricted_access(accessor,ByteString::from_utf8_without_validation("function"sv),accessee,method->name,scopes,span)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

ErrorOr<bool> Jakt::typechecker::Typechecker::check_restricted_access(Jakt::ids::ScopeId const accessor,ByteString const accessee_kind,Jakt::ids::ScopeId const accessee,ByteString const name,JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> const whitelist,Jakt::utility::Span const span) {
{
Jakt::ids::ScopeId const most_specific_active_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId,ErrorOr<bool>> {
auto __jakt_enum_value = (this->current_function_id.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(this->get_function(this->current_function_id.value())->function_scope_id);
}else {{
if (!this->current_struct_type_id.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Can't access {0} ‘{1}’ from this global scope, because ‘{1}’ restricts access to it"sv),accessee_kind,name),span);
return false;
}
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId, ErrorOr<bool>>{
auto&& __jakt_match_variant = *this->get_type(this->current_struct_type_id.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_struct(id).scope_id);
};/*case end*/
default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Internal error: current_struct_type_id is not a struct"sv),span));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> _magic = whitelist.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> scope = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> const resolved_scope = TRY((scope->try_resolve(this->program)));
NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> __jakt_tmp315 = resolved_scope;
if (__jakt_tmp315->__jakt_init_index() == 0 /* Resolved */){
Jakt::ids::ScopeId const scope_id = __jakt_tmp315->as.Resolved.value;
if (this->scope_can_access(most_specific_active_scope_id,scope_id)){
return true;
}
}
else {
continue;
}

}

}
}

NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(most_specific_active_scope_id);
this->error(__jakt_format(StringView::from_string_literal("Cannot access {} ‘{}’ from this scope"sv),accessee_kind,name),span);
return false;
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::infer_signed_int(i64 const val,Jakt::utility::Span const span,JaktInternal::Optional<Jakt::ids::TypeId> const type_hint_id) {
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I64(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::I64()));
if (type_hint_id.has_value()){
Jakt::ids::TypeId const hint = type_hint_id.value();
NonnullRefPtr<typename Jakt::types::Type> const hint_type = this->get_type(hint);
if (hint_type->is_concrete() && (!hint_type->is_numeric())){
this->error(__jakt_format(StringView::from_string_literal("Integer literal cannot be promoted to a type of {}"sv),TRY((this->type_name(hint,false)))),span);
}
if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::I8()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::I8());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if ((val < type_->min()) || (val > infallible_integer_cast<i64>(type_->max()))){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I8(infallible_integer_cast<i8>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::I8()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::I16()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::I16());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if ((val < type_->min()) || (val > infallible_integer_cast<i64>(type_->max()))){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I16(infallible_integer_cast<i16>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::I16()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::I32()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::I32());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if ((val < type_->min()) || (val > infallible_integer_cast<i64>(type_->max()))){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I32(infallible_integer_cast<i32>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::I32()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::U8()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::U8());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if ((val < type_->min()) || (val > infallible_integer_cast<i64>(type_->max()))){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U8(infallible_integer_cast<u8>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::U8()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::U16()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::U16());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if ((val < type_->min()) || (val > infallible_integer_cast<i64>(type_->max()))){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U16(infallible_integer_cast<u16>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::U16()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::U32()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::U32());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if ((val < type_->min()) || (val > infallible_integer_cast<i64>(type_->max()))){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U32(infallible_integer_cast<u32>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::U32()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::U64()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::Usize());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (val < static_cast<i64>(0LL)){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U64(infallible_integer_cast<u64>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::U64()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::Usize()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::Usize());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (val < static_cast<i64>(0LL)){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::USize(infallible_integer_cast<u64>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::Usize()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::CInt()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::CInt());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (val < static_cast<i64>(0LL)){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I32(infallible_integer_cast<i32>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::CInt()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::CChar()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::CChar());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if ((val < static_cast<i64>(0LL)) || (val > static_cast<i64>(255LL))){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U8(infallible_integer_cast<u8>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::CChar()));
}

}
}
return expr;
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::infer_unsigned_int(u64 const val,Jakt::utility::Span const span,JaktInternal::Optional<Jakt::ids::TypeId> const type_hint_id) {
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U64(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::U64()));
if (type_hint_id.has_value()){
Jakt::ids::TypeId const hint = type_hint_id.value();
NonnullRefPtr<typename Jakt::types::Type> const hint_type = this->get_type(hint);
if (hint_type->is_concrete() && (!hint_type->is_numeric())){
this->error(__jakt_format(StringView::from_string_literal("Integer literal cannot be promoted to a type of {}"sv),TRY((this->type_name(hint,false)))),span);
}
if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::I8()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::I8());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (type_->max() < val){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I8(infallible_integer_cast<i8>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::I8()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::I16()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::I16());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (type_->max() < val){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I16(infallible_integer_cast<i16>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::I16()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::I32()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::I32());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (type_->max() < val){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I32(infallible_integer_cast<i32>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::I32()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::U8()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::U8());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (type_->max() < val){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U8(infallible_integer_cast<u8>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::U8()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::U16()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::U16());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (type_->max() < val){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U16(infallible_integer_cast<u16>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::U16()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::U32()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::U32());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (type_->max() < val){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U32(infallible_integer_cast<u32>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::U32()));
}

}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::U64()))){
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U64(static_cast<u64>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::U64()));
}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::Usize()))){
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::USize(static_cast<u64>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::Usize()));
}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::CInt()))){
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::USize(static_cast<u64>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::CInt()));
}
else if (hint.equals(Jakt::types::builtin(Jakt::types::BuiltinType::CChar()))){
Jakt::ids::TypeId const builtin_typeid = Jakt::types::builtin(Jakt::types::BuiltinType::CChar());
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(builtin_typeid);
if (val > static_cast<u64>(255ULL)){
this->error_with_hint(ByteString::from_utf8_without_validation("Integer promotion failed"sv),span,__jakt_format(StringView::from_string_literal("Cannot fit value into range [{}, {}] of type {}."sv),type_->min(),type_->max(),TRY((this->type_name(builtin_typeid,false)))),span);
}
else {
expr = Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U8(infallible_integer_cast<u8>(val)),span,Jakt::types::builtin(Jakt::types::BuiltinType::CChar()));
}

}
}
return expr;
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::strip_optional_from_type(Jakt::ids::TypeId const type_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<Jakt::ids::TypeId>>{
auto&& __jakt_match_variant = *this->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if (id.equals(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv)))))){
return args.operator[](static_cast<i64>(0LL));
}
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(type_id);
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return JaktInternal::ExplicitValue(type_id);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::final_type_resolution_form(Jakt::ids::TypeId const type_id,Jakt::ids::ScopeId const scope_id) const {
{
Jakt::ids::TypeId const mapped_type_id = TRY((this->resolve_type_var(type_id,scope_id)));
if ((this->get_type(mapped_type_id)->__jakt_init_index() == 30 /* Self */) && this->self_type_id.has_value()){
return this->self_type_id.value();
}
return mapped_type_id;
}
}

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>> Jakt::typechecker::Typechecker::struct_like_id_from_type_id(Jakt::ids::TypeId const type_id,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span,bool const for_optional_chain,bool const treat_string_as_builtin) {
{
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(type_id);
bool found_optional = false;
JaktInternal::Optional<Jakt::types::StructLikeId> const parent_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::StructLikeId>, ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),id)));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),id)));
};/*case end*/
case 13 /* JaktString */:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::StructLikeId>,ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>>> {
auto __jakt_enum_value = (treat_string_as_builtin);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),this->program->builtin_implementation_struct(type->as_builtin_type(),this->program->prelude_module_id())));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("String"sv)))))));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::types::StructLikeId>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::StructLikeId>,ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>>> {
auto __jakt_enum_value = (for_optional_chain);
if (__jakt_enum_value) {{
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
JaktInternal::Optional<Jakt::types::StructLikeId> struct_id = JaktInternal::OptionalNone();
if (!id.equals(optional_struct_id)){
this->error(__jakt_format(StringView::from_string_literal("Can't use ‘{}’ as an optional type in optional chained call"sv),this->get_struct(id).name),span);
}
else {
found_optional = true;
struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::StructLikeId>, ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>>>{
auto&& __jakt_match_variant = *this->get_type(args.operator[](static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),struct_id));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),id));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Enum(JaktInternal::OptionalNone(),id));
};/*case end*/
default:{
this->error(ByteString::from_utf8_without_validation("Can't use non-struct type as an optional type in optional chained call"sv),span);
found_optional = false;
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),optional_struct_id));
}
VERIFY_NOT_REACHED();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::types::StructLikeId>>(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(struct_id.value_or_lazy_evaluated([&] { return Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),optional_struct_id); })));
}
VERIFY_NOT_REACHED();
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Struct(args,id)));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Enum(args,id)));
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Trait(JaktInternal::OptionalNone(),id)));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Trait(args,id)));
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& trait_implementations = __jakt_match_value.trait_implementations;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::StructLikeId>,ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>>> {
auto __jakt_enum_value = (trait_implementations.size());
if (__jakt_enum_value == static_cast<size_t>(0ULL)) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}else {return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::StructLikeId>, ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>>>{
auto&& __jakt_match_variant = *this->get_type(trait_implementations.operator[](static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Trait(JaktInternal::OptionalNone(),id)));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::StructLikeId>>(Jakt::types::StructLikeId::Trait(args,id)));
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::StructLikeId>,ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool>>> {
auto __jakt_enum_value = (type->is_builtin());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Struct(JaktInternal::OptionalNone(),this->program->builtin_implementation_struct(type->as_builtin_type(),this->program->prelude_module_id())));
}else {{
this->error(__jakt_format(StringView::from_string_literal("no methods available on value (type: {} {})"sv),this->get_type(type_id)->constructor_name(),TRY((this->type_name(type_id,false)))),span);
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::types::StructLikeId>>(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Tuple{parent_id, found_optional};
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_expression(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
ByteString const& field_name = __jakt_match_value.field_name;
Jakt::utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = TRY((this->typecheck_indexed_struct(expr,field_name,scope_id,is_optional,safety_mode,span)));
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp317 = type_hint;
if (__jakt_tmp317.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp317.value();
Jakt::typechecker::TypeHint __jakt_tmp316 = hint;
if (__jakt_tmp316.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp316.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& index = __jakt_match_value.index;
Jakt::utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = TRY((this->typecheck_comptime_index(expr,index,scope_id,is_optional,safety_mode,span)));
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp319 = type_hint;
if (__jakt_tmp319.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp319.value();
Jakt::typechecker::TypeHint __jakt_tmp318 = hint;
if (__jakt_tmp318.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp318.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
if (type_hint.has_value()){
TRY((this->unify_with_type(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()),type_hint.value().common.init_common.type_id,span)));
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Boolean(JaktInternal::OptionalNone(),val,span));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;Jakt::parser::NumericConstant const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::Optional<Jakt::ids::TypeId> type_hint_unwrapped = JaktInternal::OptionalNone();
if (type_hint.has_value()){
type_hint_unwrapped = TRY((this->unwrap_type_id_from_optional_if_needed(type_hint.value().common.init_common.type_id)));
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I8(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::I8())));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I16(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::I16())));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I32(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::I32())));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I64(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::I64())));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U8(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::U8())));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U16(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::U16())));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U32(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::U32())));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U64(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::U64())));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::USize(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::Usize())));
};/*case end*/
case 9 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::F32(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::F32())));
};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::F64(val),span,Jakt::types::builtin(Jakt::types::BuiltinType::F64())));
};/*case end*/
case 11 /* UnknownSigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnknownSigned;i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((this->infer_signed_int(val,span,type_hint_unwrapped))));
};/*case end*/
case 12 /* UnknownUnsigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnknownUnsigned;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((this->infer_unsigned_int(val,span,type_hint_unwrapped))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp321 = type_hint;
if (__jakt_tmp321.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp321.value();
Jakt::typechecker::TypeHint __jakt_tmp320 = hint;
if (__jakt_tmp320.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp320.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;ByteString const& val = __jakt_match_value.val;
JaktInternal::Optional<ByteString> const& prefix = __jakt_match_value.prefix;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (prefix.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation(""sv); }));
if (__jakt_enum_value == ByteString::from_utf8_without_validation(""sv)) {return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::CharacterConstant(JaktInternal::OptionalNone(),val,span));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("b"sv)) {return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::ByteConstant(JaktInternal::OptionalNone(),val,span));
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("c"sv)) {return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::CCharacterConstant(JaktInternal::OptionalNone(),val,span));
}else {{
this->compiler->panic(__jakt_format(StringView::from_string_literal("Unknown string prefix {}"sv),prefix));
}
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp323 = type_hint;
if (__jakt_tmp323.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp323.value();
Jakt::typechecker::TypeHint __jakt_tmp322 = hint;
if (__jakt_tmp322.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp322.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;ByteString const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (type_hint.has_value() && (!type_hint.value().common.init_common.type_id.equals(Jakt::types::unknown_type_id())));
if (__jakt_enum_value) {{
Jakt::ids::TypeId type_id = TRY((this->strip_optional_from_type(this->generic_inferences.map(type_hint.value().common.init_common.type_id))));
Jakt::ids::TypeId const prelude_string_type_id = TRY((this->prelude_struct_type_named(ByteString::from_utf8_without_validation("String"sv))));
Jakt::ids::TypeId const prelude_string_view_type_id = TRY((this->prelude_struct_type_named(ByteString::from_utf8_without_validation("StringView"sv))));
bool may_throw = false;
if ((!type_id.equals(prelude_string_type_id)) && (!type_id.equals(prelude_string_view_type_id))){
if (this->get_type(type_id)->is_concrete()){
JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor> const trait_implementation = TRY((this->find_any_singular_trait_implementation(type_id,DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("FromStringLiteral"sv), ByteString::from_utf8_without_validation("ThrowingFromStringLiteral"sv)}),scope_id,span,JaktInternal::OptionalNone())));
if (!trait_implementation.has_value()){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Type {} cannot be used as an overloaded string literal type"sv),TRY((this->type_name(type_id,true)))),span,__jakt_format(StringView::from_string_literal("Consider implementing the FromStringLiteral trait for {}"sv),TRY((this->type_name(type_id,false)))),span);
type_id = prelude_string_type_id;
}
else {
may_throw = (trait_implementation.value().trait_name == ByteString::from_utf8_without_validation("ThrowingFromStringLiteral"sv));
}

}
else if (!this->get_type(type_id)->is_concrete()){
type_id = TRY((this->prelude_struct_type_named(ByteString::from_utf8_without_validation("String"sv))));
}
}
TRY((this->unify(type_hint.value().common.init_common.type_id,span,type_id,span)));
if (may_throw && (!this->get_scope(scope_id)->can_throw)){
this->error(ByteString::from_utf8_without_validation("Operation that may throw needs to be in a try statement or a function marked as throws"sv),span);
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::QuotedString(JaktInternal::OptionalNone(),Jakt::types::CheckedStringLiteral(Jakt::types::StringLiteral::Static(val),type_id,may_throw),span));
}
VERIFY_NOT_REACHED();
}else {{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = Jakt::types::CheckedExpression::QuotedString(JaktInternal::OptionalNone(),Jakt::types::CheckedStringLiteral(Jakt::types::StringLiteral::Static(val),TRY((this->prelude_struct_type_named(ByteString::from_utf8_without_validation("String"sv)))),false),span);
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp325 = type_hint;
if (__jakt_tmp325.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp325.value();
Jakt::typechecker::TypeHint __jakt_tmp324 = hint;
if (__jakt_tmp324.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp324.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 4 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::parser::ParsedCall const& call = __jakt_match_value.call;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_call(call,scope_id,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),safety_mode,type_hint,false))));
};/*case end*/
case 5 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::parser::ParsedCall const& call = __jakt_match_value.call;
Jakt::utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::ids::TypeId const checked_expr_type_id = checked_expr->type();
Jakt::ids::TypeId const final_type_id = TRY((this->final_type_resolution_form(checked_expr_type_id,scope_id)));
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(final_type_id);
JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool> const parent_id_found_optional_ = TRY((this->struct_like_id_from_type_id(final_type_id,scope_id,span,is_optional,false)));
JaktInternal::Optional<Jakt::types::StructLikeId> const parent_id = parent_id_found_optional_.template get<0>();
bool const found_optional = parent_id_found_optional_.template get<1>();

if (is_optional && (!found_optional)){
this->error(__jakt_format(StringView::from_string_literal("Optional chain mismatch: expected optional chain, found {}"sv),TRY((this->type_name(checked_expr_type_id,false)))),checked_expr->span());
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_call_expr = TRY((this->typecheck_call(call,scope_id,span,checked_expr,parent_id,safety_mode,type_hint,false)));
Jakt::ids::TypeId const type_id = checked_call_expr->type();
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_call_expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
{
Jakt::ids::TypeId result_type = call.return_type;
if (is_optional){
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
result_type = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({result_type})));
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::MethodCall(JaktInternal::OptionalNone(),checked_expr,call,span,is_optional,result_type));
}
VERIFY_NOT_REACHED();
};/*case end*/
default:{
this->compiler->panic(ByteString::from_utf8_without_validation("typecheck_call should return `CheckedExpression::Call()`"sv));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& to = __jakt_match_value.to;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> checked_from = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::ids::TypeId> from_type = JaktInternal::OptionalNone();
Jakt::utility::Span from_span = span;
if (from.has_value() && ((!(from.value()->__jakt_init_index() == 1 /* NumericConstant */)) && (!(from.value()->__jakt_init_index() == 1 /* NumericConstant */)))){
checked_from = TRY((this->typecheck_expression(from.value(),scope_id,safety_mode,JaktInternal::OptionalNone())));
from_type = checked_from.value()->type();
from_span = checked_from.value()->span();
}
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> checked_to = JaktInternal::OptionalNone();
Jakt::ids::TypeId to_type = Jakt::types::unknown_type_id();
Jakt::utility::Span to_span = span;
if (to.has_value()){
JaktInternal::Optional<Jakt::typechecker::TypeHint> type_hint = JaktInternal::OptionalNone();
if (from_type.has_value()){
type_hint = Jakt::typechecker::TypeHint::MustBe(from_type.value());
}
checked_to = TRY((this->typecheck_expression(to.value(),scope_id,safety_mode,type_hint)));
to_type = checked_to.value()->type();
to_span = checked_to.value()->span();
}
if (from.has_value() && ((from.value()->__jakt_init_index() == 1 /* NumericConstant */) || (from.value()->__jakt_init_index() == 1 /* NumericConstant */))){
checked_from = TRY((this->typecheck_expression(from.value(),scope_id,safety_mode,Jakt::typechecker::TypeHint::MustBe(to_type))));
from_type = checked_from.value()->type();
from_span = checked_from.value()->span();
}
JaktInternal::Optional<Jakt::ids::TypeId> values_type_id = JaktInternal::OptionalNone();
if (from.has_value() && to.has_value()){
values_type_id = TRY((this->unify(from_type.value(),from_span,to_type,from_span)));
if (!values_type_id.has_value()){
this->error(ByteString::from_utf8_without_validation("Range values differ in types"sv),span);
}
}
else if (from.has_value()){
values_type_id = from_type;
}
else if (to.has_value()){
values_type_id = to_type;
}
Jakt::ids::StructId const range_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Range"sv))));
NonnullRefPtr<typename Jakt::types::Type> const range_type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),range_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({values_type_id.value_or(Jakt::types::builtin(Jakt::types::BuiltinType::I64()))}));
Jakt::ids::TypeId const type_id = this->find_or_add_type_id(range_type);
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp327 = type_hint;
if (__jakt_tmp327.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp327.value();
Jakt::typechecker::TypeHint __jakt_tmp326 = hint;
if (__jakt_tmp326.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const hint_id = __jakt_tmp326.common.init_common.type_id;
TRY((this->unify_with_type(type_id,hint_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Range(JaktInternal::OptionalNone(),checked_from,checked_to,span,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 29 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;NonnullRefPtr<typename Jakt::parser::ParsedType> const& type = __jakt_match_value.type;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::EnumId const reflected_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = TRY((this->program->find_reflected_primitive(ByteString::from_utf8_without_validation("Type"sv))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default:{
this->compiler->panic(ByteString::from_utf8_without_validation("unreachable"sv));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::TypeId const reflected_type = TRY((this->typecheck_typename(type,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Reflect(JaktInternal::OptionalNone(),reflected_type,span,this->find_or_add_type_id(Jakt::types::Type::Enum(Jakt::parser::CheckedQualifiers(false),reflected_type_enum_id))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::parser::UnaryOperator const& op = __jakt_match_value.op;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Dereference */:return JaktInternal::ExplicitValue(TRY((this->typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone()))));
case 4 /* Negate */:return JaktInternal::ExplicitValue(TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,type_hint,span))));
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;Jakt::parser::TypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Infallible */:{
Jakt::typechecker::TypeHint const type_hint = Jakt::typechecker::TypeHint::CouldBe(TRY((this->typecheck_typename(cast.parsed_type(),scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,type_hint,span))));
}
VERIFY_NOT_REACHED();
default:return JaktInternal::ExplicitValue(TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default:return JaktInternal::ExplicitValue(TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span))));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::CheckedUnaryOperator const checked_op = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedUnaryOperator, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* PreIncrement */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::PreIncrement());
case 1 /* PostIncrement */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::PostIncrement());
case 2 /* PreDecrement */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::PreDecrement());
case 3 /* PostDecrement */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::PostDecrement());
case 4 /* Negate */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::Negate());
case 5 /* Dereference */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::Dereference());
case 6 /* RawAddress */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::RawAddress());
case 7 /* Reference */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::Reference());
case 8 /* MutableReference */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::MutableReference());
case 9 /* LogicalNot */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::LogicalNot());
case 10 /* BitwiseNot */:return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::BitwiseNot());
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;Jakt::parser::TypeCast const& cast = __jakt_match_value.value;
{
Jakt::ids::TypeId const type_id = TRY((this->typecheck_typename(cast.parsed_type(),scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
Jakt::types::CheckedTypeCast const checked_cast = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedTypeCast, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Fallible */:{
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
NonnullRefPtr<typename Jakt::types::Type> const optional_type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({type_id}));
Jakt::ids::TypeId const optional_type_id = this->find_or_add_type_id(optional_type);
return JaktInternal::ExplicitValue<Jakt::types::CheckedTypeCast>(Jakt::types::CheckedTypeCast::Fallible(optional_type_id));
}
VERIFY_NOT_REACHED();
case 1 /* Infallible */:return JaktInternal::ExplicitValue(Jakt::types::CheckedTypeCast::Infallible(type_id));
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::CheckedUnaryOperator result = Jakt::types::CheckedUnaryOperator::TypeCast(checked_cast);
if (checked_cast.type_id().equals(checked_expr->type())){
result = Jakt::types::CheckedUnaryOperator::TypeCast(Jakt::types::CheckedTypeCast::Identity(type_id));
}
return JaktInternal::ExplicitValue<Jakt::types::CheckedUnaryOperator>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 14 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;NonnullRefPtr<typename Jakt::parser::ParsedType> const& unchecked_type = __jakt_match_value.value;
{
Jakt::ids::TypeId const type_id = TRY((this->typecheck_typename(unchecked_type,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
return JaktInternal::ExplicitValue<Jakt::types::CheckedUnaryOperator>(Jakt::types::CheckedUnaryOperator::Sizeof(type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;NonnullRefPtr<typename Jakt::parser::ParsedType> const& unchecked_type = __jakt_match_value.value;
{
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
Jakt::ids::TypeId const type_id = TRY((this->typecheck_typename(unchecked_type,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
this->exit_ignore_error_mode(snapshot);
Jakt::types::CheckedUnaryOperator operator_is = Jakt::types::CheckedUnaryOperator::Is(type_id);
NonnullRefPtr<typename Jakt::parser::ParsedType> __jakt_tmp328 = unchecked_type;
if (__jakt_tmp328->__jakt_init_index() == 0 /* Name */){
ByteString const name = __jakt_tmp328->as.Name.name;
Jakt::ids::TypeId const expr_type_id = checked_expr->type();
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp329 = this->get_type(expr_type_id);
if (__jakt_tmp329->__jakt_init_index() == 24 /* Enum */){
Jakt::ids::EnumId const enum_id = __jakt_tmp329->as.Enum.value;
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
bool exists = false;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
exists = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(var_name == name);
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(var_name == name);
};/*case end*/
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(var_name == name);
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& var_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(var_name == name);
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
if (exists){
operator_is = Jakt::types::CheckedUnaryOperator::IsEnumVariant(variant,DynamicArray<Jakt::types::CheckedEnumVariantBinding>::create_with({}),expr_type_id);
break;
}
}

}
}

if ((!exists) && type_id.equals(Jakt::types::unknown_type_id())){
this->error(__jakt_format(StringView::from_string_literal("Enum variant {} does not exist on {}"sv),name,TRY((this->type_name(expr_type_id,false)))),span);
}
}
else if ((name == ByteString::from_utf8_without_validation("Some"sv)) || (name == ByteString::from_utf8_without_validation("None"sv))){
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
NonnullRefPtr<typename Jakt::types::Type> const checked_expr_type = this->get_type(checked_expr->type());
if (!(checked_expr_type->__jakt_init_index() == 20 /* GenericInstance */)){
this->error(__jakt_format(StringView::from_string_literal("The left-hand side of an `is {}` statement must have a {} variant"sv),name,name),checked_expr->span());
}
operator_is = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedUnaryOperator,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (name);
if (__jakt_enum_value == ByteString::from_utf8_without_validation("Some"sv)) {return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::IsSome());
}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("None"sv)) {return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::IsNone());
}else {{
Jakt::utility::panic(ByteString::from_utf8_without_validation("unreachable"sv));
}
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
else if (type_id.equals(Jakt::types::unknown_type_id())){
this->error(__jakt_format(StringView::from_string_literal("Unknown type or invalid type name: {}"sv),name),span);
}
}
else {
this->error(ByteString::from_utf8_without_validation("The right-hand side of an `is` operator must be a type name or enum variant"sv),span);
}

return JaktInternal::ExplicitValue<Jakt::types::CheckedUnaryOperator>(operator_is);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 13 /* IsEnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IsEnumVariant;NonnullRefPtr<typename Jakt::parser::ParsedType> const& inner = __jakt_match_value.inner;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& bindings = __jakt_match_value.bindings;
return JaktInternal::ExplicitValue(TRY((this->typecheck_is_enum_variant(checked_expr,inner,bindings,scope_id))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = TRY((this->typecheck_unary_operation(checked_expr,checked_op,span,scope_id,safety_mode)));
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp331 = type_hint;
if (__jakt_tmp331.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp331.value();
Jakt::typechecker::TypeHint __jakt_tmp330 = hint;
if (__jakt_tmp330.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp330.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& lhs = __jakt_match_value.lhs;
Jakt::parser::BinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& rhs = __jakt_match_value.rhs;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> original_checked_lhs = JaktInternal::OptionalNone();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> original_checked_rhs = JaktInternal::OptionalNone();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> checked_lhs = JaktInternal::OptionalNone();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> checked_rhs = JaktInternal::OptionalNone();
NonnullRefPtr<typename Jakt::parser::ParsedExpression> __jakt_tmp332 = lhs;
if (__jakt_tmp332->__jakt_init_index() == 1 /* NumericConstant */){
Jakt::parser::NumericConstant const val = __jakt_tmp332->as.NumericConstant.val;
if ((val.__jakt_init_index() == 11 /* UnknownSigned */) || (val.__jakt_init_index() == 12 /* UnknownUnsigned */)){
original_checked_rhs = TRY((this->typecheck_expression(rhs,scope_id,safety_mode,JaktInternal::OptionalNone())));
checked_rhs = TRY((this->dereference_if_needed(original_checked_rhs.value(),span)));
Jakt::ids::TypeId const hint = checked_rhs.value()->type();
original_checked_lhs = TRY((this->typecheck_expression(lhs,scope_id,safety_mode,Jakt::typechecker::TypeHint::MustBe(hint))));
checked_lhs = TRY((this->dereference_if_needed(original_checked_lhs.value(),span)));
}
else {
original_checked_lhs = TRY((this->typecheck_expression(lhs,scope_id,safety_mode,JaktInternal::OptionalNone())));
checked_lhs = TRY((this->dereference_if_needed(original_checked_lhs.value(),span)));
Jakt::ids::TypeId const hint = checked_lhs.value()->type();
original_checked_rhs = TRY((this->typecheck_expression(rhs,scope_id,safety_mode,Jakt::typechecker::TypeHint::CouldBe(hint))));
checked_rhs = TRY((this->dereference_if_needed(original_checked_rhs.value(),span)));
}

}
else {
original_checked_lhs = TRY((this->typecheck_expression(lhs,scope_id,safety_mode,JaktInternal::OptionalNone())));
checked_lhs = TRY((this->dereference_if_needed(original_checked_lhs.value(),span)));
Jakt::ids::TypeId const hint = checked_lhs.value()->type();
original_checked_rhs = TRY((this->typecheck_expression(rhs,scope_id,safety_mode,Jakt::typechecker::TypeHint::CouldBe(hint))));
checked_rhs = TRY((this->dereference_if_needed(original_checked_rhs.value(),span)));
}

if (this->type_contains_reference(original_checked_lhs.value()->type())){
NonnullRefPtr<typename Jakt::parser::ParsedExpression> __jakt_tmp333 = rhs;
if (__jakt_tmp333->__jakt_init_index() == 11 /* UnaryOp */){
Jakt::parser::UnaryOperator const op = __jakt_tmp333->as.UnaryOp.op;
if ((op.__jakt_init_index() == 7 /* Reference */) || (op.__jakt_init_index() == 8 /* MutableReference */)){
this->error_with_hint(ByteString::from_utf8_without_validation("Attempt to rebind a reference will result in write-through"sv),span,ByteString::from_utf8_without_validation("This reference will be immediately dereferenced and then assigned"sv),rhs->span());
}
}
}
JaktInternal::Tuple<Jakt::types::CheckedBinaryOperator,Jakt::ids::TypeId> const checked_operator_output_type_ = TRY((this->typecheck_binary_operation(checked_lhs.value(),op,checked_rhs.value(),scope_id,span)));
Jakt::types::CheckedBinaryOperator const checked_operator = checked_operator_output_type_.template get<0>();
Jakt::ids::TypeId const output_type = checked_operator_output_type_.template get<1>();

JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp335 = type_hint;
if (__jakt_tmp335.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp335.value();
Jakt::typechecker::TypeHint __jakt_tmp334 = hint;
if (__jakt_tmp334.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp334.common.init_common.type_id;
TRY((this->unify_with_type(output_type,type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::BinaryOp(JaktInternal::OptionalNone(),checked_lhs.value(),checked_operator,checked_rhs.value(),span,output_type));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 15 /* OptionalNone */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalNone;Jakt::utility::Span const& span = __jakt_match_value.value;
{
JaktInternal::Optional<Jakt::ids::TypeId> type_hint_unwrapped = JaktInternal::OptionalNone();
if (type_hint.has_value()){
type_hint_unwrapped = TRY((this->unwrap_type_id_from_optional_if_needed(type_hint.value().common.init_common.type_id)));
}
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp337 = type_hint;
if (__jakt_tmp337.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp337.value();
Jakt::typechecker::TypeHint __jakt_tmp336 = hint;
if (__jakt_tmp336.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp336.common.init_common.type_id;
TRY((this->unify_with_type(type_hint_unwrapped.value_or_lazy_evaluated([&] { return Jakt::types::unknown_type_id(); }),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::OptionalNone(JaktInternal::OptionalNone(),span,type_hint_unwrapped.value_or_lazy_evaluated([&] { return Jakt::types::unknown_type_id(); })));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 14 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::Optional<Jakt::typechecker::TypeHint> inner_hint = JaktInternal::OptionalNone();
if (type_hint.has_value()){
Jakt::ids::TypeId const type_hint_unwrapped_id = TRY((this->unwrap_type_id_from_optional_if_needed(type_hint.value().common.init_common.type_id)));
inner_hint = Jakt::typechecker::TypeHint::CouldBe(type_hint_unwrapped_id);
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression(expr,scope_id,safety_mode,inner_hint)));
Jakt::ids::TypeId type_id = checked_expr->type();
if (type_hint.has_value()){
Jakt::ids::TypeId const type_hint_unwrapped_id = TRY((this->unwrap_type_id_from_optional_if_needed(type_hint.value().common.init_common.type_id)));
type_id = TRY((this->choose_broader_type_id(type_id,type_hint_unwrapped_id,this->generic_inferences,span)));
}
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
NonnullRefPtr<typename Jakt::types::Type> const optional_type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({type_id}));
Jakt::ids::TypeId const optional_type_id = this->find_or_add_type_id(optional_type);
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp339 = type_hint;
if (__jakt_tmp339.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp339.value();
Jakt::typechecker::TypeHint __jakt_tmp338 = hint;
if (__jakt_tmp338.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp338.common.init_common.type_id;
TRY((this->unify_with_type(optional_type_id,type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::OptionalSome(JaktInternal::OptionalNone(),checked_expr,span,optional_type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;ByteString const& name = __jakt_match_value.name;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>> const var = TRY((this->find_var_in_scope(scope_id,name,JaktInternal::OptionalNone())));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (var.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::Var(JaktInternal::OptionalNone(),var.value(),span));
}else {{
this->error(__jakt_format(StringView::from_string_literal("Variable '{}' not found"sv),name),span);
JaktInternal::Optional<Jakt::ids::TypeId> type_id = JaktInternal::OptionalNone();
if (type_hint.has_value()){
type_id = type_hint.value().common.init_common.type_id;
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Var(JaktInternal::OptionalNone(),Jakt::types::CheckedVariable::__jakt_create(name,type_id.value_or(Jakt::types::unknown_type_id()),false,span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()),span));
}
VERIFY_NOT_REACHED();
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp341 = type_hint;
if (__jakt_tmp341.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp341.value();
Jakt::typechecker::TypeHint __jakt_tmp340 = hint;
if (__jakt_tmp340.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp340.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(checked_expr->type());
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
Jakt::ids::StructId const weakptr_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv))));
Jakt::ids::TypeId const type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::ids::TypeId inner_type_id = Jakt::types::unknown_type_id();
if (id.equals(optional_struct_id) || id.equals(weakptr_struct_id)){
inner_type_id = args.operator[](static_cast<i64>(0LL));
}
else {
this->error(ByteString::from_utf8_without_validation("Forced unwrap only works on Optional"sv),span);
}

return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(inner_type_id);
}
VERIFY_NOT_REACHED();
};/*case end*/
default:{
this->error(ByteString::from_utf8_without_validation("Forced unwrap only works on Optional"sv),span);
return JaktInternal::ExplicitValue<Jakt::ids::TypeId>(Jakt::types::unknown_type_id());
}
VERIFY_NOT_REACHED();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp343 = type_hint;
if (__jakt_tmp343.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp343.value();
Jakt::typechecker::TypeHint __jakt_tmp342 = hint;
if (__jakt_tmp342.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const hint_id = __jakt_tmp342.common.init_common.type_id;
TRY((this->unify_with_type(type_id,hint_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::ForcedUnwrap(JaktInternal::OptionalNone(),checked_expr,span,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& values = __jakt_match_value.values;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& fill_size = __jakt_match_value.fill_size;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_array(scope_id,values,fill_size,span,safety_mode,type_hint))));
};/*case end*/
case 19 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& values = __jakt_match_value.values;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::ids::TypeId const VOID_TYPE_ID = Jakt::types::builtin(Jakt::types::BuiltinType::Void());
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> checked_values = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
JaktInternal::DynamicArray<Jakt::ids::TypeId> checked_types = DynamicArray<Jakt::ids::TypeId>::create_with({});
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> _magic = values.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedExpression> value = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_value = TRY((this->typecheck_expression(value,scope_id,safety_mode,JaktInternal::OptionalNone())));
Jakt::ids::TypeId const type_id = checked_value->type();
if (type_id.equals(VOID_TYPE_ID)){
this->error(ByteString::from_utf8_without_validation("Cannot create a tuple that contains a value of type void"sv),value->span());
}
checked_types.push(type_id);
checked_values.push(checked_value);
}

}
}

if (type_hint.has_value()){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp344 = this->get_type(type_hint.value().common.init_common.type_id);
if (__jakt_tmp344->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp344->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp344->as.GenericInstance.args;
if (checked_types.size() == args.size()){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::ids::TypeId value_type = checked_types.operator[](i);
JaktInternal::Optional<Jakt::ids::TypeId> const unified = TRY((this->unify(args.operator[](i),span,value_type,span)));
if (unified.has_value()){
bool type_optional = false;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp345 = this->get_type(unified.value());
if (__jakt_tmp345->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp345->as.GenericInstance.id;
if (id.equals(optional_struct_id)){
type_optional = true;
}
}
bool value_optional = false;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp346 = this->get_type(value_type);
if (__jakt_tmp346->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp346->as.GenericInstance.id;
if (id.equals(optional_struct_id)){
value_optional = true;
}
}
checked_types.operator[](i) = unified.value();
if (type_optional && ((!value_optional) && (!(checked_values.operator[](i)->__jakt_init_index() == 26 /* OptionalSome */)))){
if (checked_values.operator[](i)->__jakt_init_index() == 25 /* OptionalNone */){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp347 = this->get_type(unified.value());
if (__jakt_tmp347->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp347->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp347->as.GenericInstance.args;
value_type = args.operator[](static_cast<i64>(0LL));
}
}
NonnullRefPtr<typename Jakt::types::Type> const optional_type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({value_type}));
Jakt::ids::TypeId const optional_type_id = this->find_or_add_type_id(optional_type);
checked_values.operator[](i) = Jakt::types::CheckedExpression::OptionalSome(JaktInternal::OptionalNone(),checked_values.operator[](i),span,optional_type_id);
}
}
}

}
}

}
}
}
Jakt::ids::StructId const tuple_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Tuple"sv))));
Jakt::ids::TypeId const type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),tuple_struct_id,checked_types));
if (type_hint.has_value()){
TRY((this->check_types_for_compat(type_hint.value(),type_id,this->generic_inferences,span)));
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::JaktTuple(JaktInternal::OptionalNone(),checked_values,span,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& base = __jakt_match_value.base;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& index = __jakt_match_value.index;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_base = TRY((this->typecheck_expression_and_dereference_if_needed(base,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::ids::StructId const dictionary_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Dictionary"sv))));
NonnullRefPtr<typename Jakt::types::Type> const checked_base_type = this->get_type(checked_base->type());
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint = this->generic_inferences.perform_checkpoint(true);
ScopeGuard __jakt_var_85([&] {
this->generic_inferences.restore(checkpoint);
});
bool is_dictionary = false;
JaktInternal::Optional<Jakt::typechecker::TypeHint> index_type_hint = JaktInternal::OptionalNone();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_base_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
is_dictionary = id.equals(dictionary_struct_id);
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const generic_parameters = this->get_struct(id).generic_parameters;
this->generic_inferences.set_all(generic_parameters,args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const generic_parameters = this->get_enum(id).generic_parameters;
this->generic_inferences.set_all(generic_parameters,args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const generic_parameters = this->get_trait(id)->generic_parameters;
this->generic_inferences.set_all(generic_parameters,args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename Jakt::types::CheckedExpression> result = Jakt::types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> trait_implementation = JaktInternal::OptionalNone();
Jakt::ids::TypeId type_id = Jakt::types::builtin(Jakt::types::BuiltinType::Void());
JaktInternal::DynamicArray<ByteString> const trait_names = DynamicArray<ByteString>::create_with({ByteString::from_utf8_without_validation("Index"sv), ByteString::from_utf8_without_validation("ThrowingIndex"sv)});
ByteString const function_name = ByteString::from_utf8_without_validation("index"sv);
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>,Jakt::typechecker::TraitImplementationDescriptor>> accepted_implementations = DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>,Jakt::typechecker::TraitImplementationDescriptor>>::create_with({});
Jakt::ids::TypeId expected_index_type = Jakt::types::void_type_id();
this->had_an_error = false;
{
JaktInternal::ArrayIterator<Jakt::typechecker::TraitImplementationDescriptor> _magic = TRY((this->find_all_trait_implementations(checked_base->type(),trait_names,scope_id,span,JaktInternal::OptionalNone()))).iterator();
for (;;){
JaktInternal::Optional<Jakt::typechecker::TraitImplementationDescriptor> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::typechecker::TraitImplementationDescriptor implementation = _magic_value.value();
{
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const inner_checkpoint = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_86([&] {
this->generic_inferences.restore(inner_checkpoint);
});
expected_index_type = TRY((this->substitute_typevars_in_type(implementation.implemented_type_args.operator[](static_cast<i64>(0LL)),this->generic_inferences)));
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_87([&] {
this->exit_ignore_error_mode(snapshot);
});
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_index = TRY((this->typecheck_expression_and_dereference_if_needed(index,scope_id,safety_mode,Jakt::typechecker::TypeHint::MustBe(expected_index_type),span)));
if (this->had_an_error){
continue;
}
accepted_implementations.push(Tuple{checked_index, this->generic_inferences.perform_checkpoint(false), implementation});
}

}
}

if (accepted_implementations.size() > static_cast<size_t>(1ULL)){
this->error(__jakt_format(StringView::from_string_literal("Ambiguous trait implementations for indexing operation on type {}"sv),TRY((this->type_name(checked_base->type(),false)))),span);
}
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>,Jakt::typechecker::TraitImplementationDescriptor>> const add_trait_implementation = accepted_implementations.first();
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>,Jakt::typechecker::TraitImplementationDescriptor>> __jakt_tmp348 = add_trait_implementation;
if (__jakt_tmp348.has_value()){
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>,Jakt::typechecker::TraitImplementationDescriptor> const impl = __jakt_tmp348.value();
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>,Jakt::typechecker::TraitImplementationDescriptor> const checked_index_checkpoint_implementation_ = impl;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_index = checked_index_checkpoint_implementation_.template get<0>();
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint = checked_index_checkpoint_implementation_.template get<1>();
Jakt::typechecker::TraitImplementationDescriptor const implementation = checked_index_checkpoint_implementation_.template get<2>();

this->generic_inferences.set_from(checkpoint);
if (implementation.trait_name.starts_with(ByteString::from_utf8_without_validation("Throwing"sv)) && (!this->get_scope(scope_id)->can_throw)){
this->error(ByteString::from_utf8_without_validation("Call to function that may throw needs to be in a try statement or a function marked as throws"sv),span);
}
JaktInternal::Tuple<JaktInternal::Optional<Jakt::types::StructLikeId>,bool> const parent_id___ = TRY((this->struct_like_id_from_type_id(checked_base->type(),scope_id,span,false,true)));
JaktInternal::Optional<Jakt::types::StructLikeId> const parent_id = parent_id___.template get<0>();
bool const _ = parent_id___.template get<1>();

JaktInternal::Optional<Jakt::ids::FunctionId> const implementation_function_id = TRY((this->find_function_matching_trait_implementation_in_scope(checked_base->type(),parent_id.map([&](auto& _value) { return _value.scope_id(this->program); }).value_or_lazy_evaluated([&] { return scope_id; }),function_name,implementation)));
if (implementation_function_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const implementation_function = this->get_function(implementation_function_id.value());
if (implementation_function->is_mutating() && (!checked_base->is_mutable(this->program))){
this->error(ByteString::from_utf8_without_validation("Cannot call mutating function on an immutable object instance"sv),span);
}
Jakt::types::CheckedCall call_expression = Jakt::types::CheckedCall(DynamicArray<Jakt::types::ResolvedNamespace>::create_with({}),function_name,DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({Tuple{ByteString::from_utf8_without_validation(""sv), checked_index}}),DynamicArray<Jakt::ids::TypeId>::create_with({}),implementation_function_id,this->generic_inferences.map(implementation_function->return_type_id),implementation_function->can_throw,implementation_function->external_name,implementation_function->force_inline);
trait_implementation = Jakt::types::OperatorTraitImplementation(implementation.trait_id,TRY((this->generic_inferences.map(implementation.implemented_type_args))),call_expression);
type_id = TRY((this->substitute_typevars_in_type(call_expression.return_type,this->generic_inferences)));
this->had_an_error = false;
}
else {
this->error(__jakt_format(StringView::from_string_literal("Failed to find an implementation of '{}' (trait {}) in type {} ({})"sv),function_name,implementation.trait_name,TRY((this->type_name(checked_base->type(),false))),this->get_scope(parent_id.value().scope_id(this->program))->debug_name),span);
}

if (is_dictionary){
result = Jakt::types::CheckedExpression::IndexedDictionary(JaktInternal::OptionalNone(),checked_base,checked_index,trait_implementation,span,type_id);
}
else {
result = Jakt::types::CheckedExpression::IndexedExpression(JaktInternal::OptionalNone(),checked_base,checked_index,trait_implementation,span,type_id);
}

}
else {
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expected_index = TRY((this->typecheck_expression_and_dereference_if_needed(index,scope_id,safety_mode,Jakt::typechecker::TypeHint::CouldBe(expected_index_type),span)));
this->error(__jakt_format(StringView::from_string_literal("Type ‘{}’ cannot be indexed by an expression of type ‘{}’"sv),TRY((this->type_name(checked_base->type(),false))),TRY((this->type_name(expected_index->type(),false)))),span);
result = Jakt::types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
}

JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp350 = type_hint;
if (__jakt_tmp350.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp350.value();
Jakt::typechecker::TypeHint __jakt_tmp349 = hint;
if (__jakt_tmp349.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp349.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const result = TRY((this->typecheck_indexed_tuple(expr,index,scope_id,is_optional,safety_mode,span)));
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp352 = type_hint;
if (__jakt_tmp352.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp352.value();
Jakt::typechecker::TypeHint __jakt_tmp351 = hint;
if (__jakt_tmp351.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp351.common.init_common.type_id;
TRY((this->unify_with_type(result->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 30 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;Jakt::utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,Jakt::types::builtin(Jakt::types::BuiltinType::Void())));
};/*case end*/
case 24 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<ByteString> const& namespace_ = __jakt_match_value.namespace_;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_namespaced_var_or_simple_enum_constructor_call(name,namespace_,scope_id,safety_mode,type_hint,span))));
};/*case end*/
case 22 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<Jakt::parser::ParsedMatchCase> const& cases = __jakt_match_value.cases;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_match(expr,cases,marker_span,scope_id,safety_mode,type_hint))));
};/*case end*/
case 23 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& inner_expr = __jakt_match_value.expr;
Jakt::parser::EnumVariantPatternArgument const& arg = __jakt_match_value.arg;
NonnullRefPtr<typename Jakt::parser::ParsedType> const& enum_variant = __jakt_match_value.enum_variant;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression_and_dereference_if_needed(inner_expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::types::CheckedEnumVariantBinding checked_binding = Jakt::types::CheckedEnumVariantBinding(ByteString::from_utf8_without_validation(""sv),ByteString::from_utf8_without_validation(""sv),Jakt::types::unknown_type_id(),span);
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> checked_enum_variant = JaktInternal::OptionalNone();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *enum_variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* NamespacedName */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedName;ByteString const& variant_name = __jakt_match_value.name;
Jakt::utility::Span const& span = __jakt_match_value.span;
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *this->get_type(checked_expr->type());
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const variant = this->get_enum_variant(enum_,variant_name);
if (variant.has_value()){
checked_enum_variant = variant;
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding>> const checked_bindings = TRY((this->typecheck_enum_variant_bindings(variant.value(),DynamicArray<Jakt::parser::EnumVariantPatternArgument>::create_with({arg}),span)));
if (checked_bindings.has_value()){
JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding> const bindings = checked_bindings.value();
checked_binding = bindings.operator[](static_cast<i64>(0LL));
}
}
else {
this->error(__jakt_format(StringView::from_string_literal("Enum variant {} does not exist"sv),variant_name),span);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
this->error(__jakt_format(StringView::from_string_literal("Unknown type or invalid type name: {}"sv),variant_name),span);
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Name */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Name;ByteString const& variant_name = __jakt_match_value.name;
Jakt::utility::Span const& span = __jakt_match_value.span;
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *this->get_type(checked_expr->type());
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const variant = this->get_enum_variant(enum_,variant_name);
if (variant.has_value()){
checked_enum_variant = variant;
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding>> const checked_bindings = TRY((this->typecheck_enum_variant_bindings(variant.value(),DynamicArray<Jakt::parser::EnumVariantPatternArgument>::create_with({arg}),span)));
if (checked_bindings.has_value()){
JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding> const bindings = checked_bindings.value();
checked_binding = bindings.operator[](static_cast<i64>(0LL));
}
}
else {
this->error(__jakt_format(StringView::from_string_literal("Enum variant {} does not exist"sv),variant_name),span);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
this->error(__jakt_format(StringView::from_string_literal("Unknown type or invalid type name: {}"sv),variant_name),span);
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename Jakt::types::CheckedExpression> output = Jakt::types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
if (checked_enum_variant.has_value()){
output = Jakt::types::CheckedExpression::EnumVariantArg(JaktInternal::OptionalNone(),checked_expr,checked_binding,checked_enum_variant.value(),span);
}
JaktInternal::Optional<Jakt::typechecker::TypeHint> __jakt_tmp354 = type_hint;
if (__jakt_tmp354.has_value()){
Jakt::typechecker::TypeHint const hint = __jakt_tmp354.value();
Jakt::typechecker::TypeHint __jakt_tmp353 = hint;
if (__jakt_tmp353.__jakt_init_index() == 0 /* MustBe */){
Jakt::ids::TypeId const type_id = __jakt_tmp353.common.init_common.type_id;
TRY((this->unify_with_type(output->type(),type_id,span)));
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(output);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 17 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const& values = __jakt_match_value.values;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_dictionary(values,span,scope_id,safety_mode,type_hint))));
};/*case end*/
case 18 /* Set */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Set;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const& values = __jakt_match_value.values;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_set(values,span,scope_id,safety_mode,type_hint))));
};/*case end*/
case 25 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::parser::ParsedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
bool const& is_fat_arrow = __jakt_match_value.is_fat_arrow;
NonnullRefPtr<typename Jakt::parser::ParsedType> const& return_type = __jakt_match_value.return_type;
Jakt::parser::ParsedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_lambda(captures,params,can_throw,is_fat_arrow,return_type,block,span,scope_id,safety_mode))));
};/*case end*/
case 26 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_must(expr,span,scope_id,safety_mode,type_hint))));
};/*case end*/
case 27 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<Jakt::parser::ParsedBlock> const& catch_block = __jakt_match_value.catch_block;
JaktInternal::Optional<Jakt::utility::Span> const& catch_span = __jakt_match_value.catch_span;
JaktInternal::Optional<ByteString> const& catch_name = __jakt_match_value.catch_name;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_try(expr,catch_block,catch_span,catch_name,scope_id,safety_mode,span,type_hint))));
};/*case end*/
case 28 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename Jakt::parser::ParsedStatement> const& stmt = __jakt_match_value.stmt;
Jakt::parser::ParsedBlock const& catch_block = __jakt_match_value.catch_block;
ByteString const& error_name = __jakt_match_value.error_name;
Jakt::utility::Span const& error_span = __jakt_match_value.error_span;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((this->typecheck_try_block(stmt,error_name,error_span,catch_block,scope_id,safety_mode,span))));
};/*case end*/
case 31 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((this->typecheck_expression(expr,scope_id,Jakt::types::SafetyMode::Unsafe(),type_hint))));
};/*case end*/
case 13 /* Operator */:{
this->compiler->panic(ByteString::from_utf8_without_validation("idk how to handle this thing"sv));
}
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_must(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
Jakt::ids::ScopeId const must_scope_id = this->create_scope(scope_id,true,ByteString::from_utf8_without_validation("must"sv),true);
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression(expr,must_scope_id,safety_mode,type_hint)));
if (!checked_expr->can_throw()){
this->error(__jakt_format(StringView::from_string_literal("‘must’ operator used on non-throwing expression"sv)),span);
}
return Jakt::types::CheckedExpression::Must(JaktInternal::OptionalNone(),checked_expr,span,checked_expr->type());
}
}

ErrorOr<Jakt::types::CheckedUnaryOperator> Jakt::typechecker::Typechecker::typecheck_is_enum_variant(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr,NonnullRefPtr<typename Jakt::parser::ParsedType> const inner,JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const bindings,Jakt::ids::ScopeId const scope_id) {
{
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
Jakt::ids::TypeId const type_id = TRY((this->typecheck_typename(inner,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
this->exit_ignore_error_mode(snapshot);
Jakt::types::CheckedUnaryOperator checked_op = Jakt::types::CheckedUnaryOperator::Is(type_id);
Jakt::ids::TypeId const expr_type_id = checked_expr->type();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::types::CheckedUnaryOperator>>{
auto&& __jakt_match_variant = *inner;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* NamespacedName */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedName;ByteString const& variant_name = __jakt_match_value.name;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp356 = this->get_type(expr_type_id);
if (__jakt_tmp356->__jakt_init_index() == 24 /* Enum */){
Jakt::ids::EnumId const enum_id = __jakt_tmp356->as.Enum.value;
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const variant = this->get_enum_variant(enum_,variant_name);
if (variant.has_value()){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding>> const checked_enum_variant_bindings = TRY((this->typecheck_enum_variant_bindings(variant.value(),bindings,span)));
checked_op = Jakt::types::CheckedUnaryOperator::IsEnumVariant(variant.value(),checked_enum_variant_bindings.value(),expr_type_id);
}
else {
this->error(__jakt_format(StringView::from_string_literal("Enum variant {} does not exist on {}"sv),variant_name,TRY((this->type_name(type_id,false)))),span);
return checked_op;
}

}
else {
this->error(__jakt_format(StringView::from_string_literal("Unknown type or invalid type name: {}"sv),variant_name),span);
return checked_op;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Name */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Name;ByteString const& variant_name = __jakt_match_value.name;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp356 = this->get_type(expr_type_id);
if (__jakt_tmp356->__jakt_init_index() == 24 /* Enum */){
Jakt::ids::EnumId const enum_id = __jakt_tmp356->as.Enum.value;
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const variant = this->get_enum_variant(enum_,variant_name);
if (variant.has_value()){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding>> const checked_enum_variant_bindings = TRY((this->typecheck_enum_variant_bindings(variant.value(),bindings,span)));
checked_op = Jakt::types::CheckedUnaryOperator::IsEnumVariant(variant.value(),checked_enum_variant_bindings.value(),expr_type_id);
}
else {
this->error(__jakt_format(StringView::from_string_literal("Enum variant {} does not exist on {}"sv),variant_name,TRY((this->type_name(type_id,false)))),span);
return checked_op;
}

}
else {
this->error(__jakt_format(StringView::from_string_literal("Unknown type or invalid type name: {}"sv),variant_name),span);
return checked_op;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

JaktInternal::Optional<Jakt::types::CheckedEnumVariant> Jakt::typechecker::Typechecker::get_enum_variant(Jakt::types::CheckedEnum const enum_,ByteString const variant_name) {
{
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
if (variant.name() == variant_name){
return variant;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding>>> Jakt::typechecker::Typechecker::typecheck_enum_variant_bindings(Jakt::types::CheckedEnumVariant const variant,JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const bindings,Jakt::utility::Span const span) {
{
Jakt::types::CheckedEnumVariant __jakt_tmp357 = variant;
if (__jakt_tmp357.__jakt_init_index() == 1 /* Typed */){
Jakt::ids::TypeId const type_id = __jakt_tmp357.as.Typed.type_id;
if (bindings.size() != static_cast<size_t>(1ULL)){
this->error(__jakt_format(StringView::from_string_literal("Enum variant ‘{}’ must have exactly one argument"sv),variant.name()),span);
return JaktInternal::OptionalNone();
}
if (this->dump_type_hints){
TRY((this->dump_type_hint(type_id,bindings.operator[](static_cast<i64>(0LL)).span)));
}
return DynamicArray<Jakt::types::CheckedEnumVariantBinding>::create_with({Jakt::types::CheckedEnumVariantBinding(JaktInternal::OptionalNone(),bindings.operator[](static_cast<i64>(0LL)).binding,type_id,span)});
}
JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>> checked_vars = DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>>::create_with({});
JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding> checked_enum_variant_bindings = DynamicArray<Jakt::types::CheckedEnumVariantBinding>::create_with({});
Jakt::types::CheckedEnumVariant __jakt_tmp358 = variant;
if (__jakt_tmp358.__jakt_init_index() == 3 /* StructLike */){
JaktInternal::DynamicArray<Jakt::ids::VarId> const fields = __jakt_tmp358.as.StructLike.fields;
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::VarId field = _magic_value.value();
{
checked_vars.push(this->get_variable(field));
}

}
}

}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = this->program->get_enum(variant.enum_id()).fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
checked_vars.push(this->get_variable(field->variable_id));
}

}
}

}

{
JaktInternal::ArrayIterator<Jakt::parser::EnumVariantPatternArgument> _magic = bindings.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::EnumVariantPatternArgument> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::EnumVariantPatternArgument binding = _magic_value.value();
{
bool found = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedVariable>> _magic = checked_vars.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedVariable> var = _magic_value.value();
{
ByteString const binding_name = binding.name.value_or_lazy_evaluated([&] { return binding.binding; });
Jakt::ids::TypeId const type_id = var->type_id;
if (binding_name == var->name){
if (this->dump_type_hints){
TRY((this->dump_type_hint(type_id,binding.span)));
}
checked_enum_variant_bindings.push(Jakt::types::CheckedEnumVariantBinding(binding.name,binding.binding,type_id,span));
found = true;
break;
}
}

}
}

if (!found){
this->error(__jakt_format(StringView::from_string_literal("Enum variant ‘{}’ doesn't have field with name ‘{}’"sv),variant.name(),binding.name_in_enum()),binding.name_in_enum_span());
}
}

}
}

if (checked_enum_variant_bindings.size() > static_cast<size_t>(0ULL)){
return checked_enum_variant_bindings;
}
return JaktInternal::OptionalNone();
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_lambda(JaktInternal::DynamicArray<Jakt::parser::ParsedCapture> const captures,JaktInternal::DynamicArray<Jakt::parser::ParsedParameter> const params,bool const can_throw,bool const is_fat_arrow,NonnullRefPtr<typename Jakt::parser::ParsedType> const return_type,Jakt::parser::ParsedBlock const block,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode) {
{
Jakt::typechecker::ReturnLegalityTracker const previous_return_tracker = this->return_tracker;
this->return_tracker = Jakt::typechecker::ReturnLegalityTracker::Lambda();
ScopeGuard __jakt_var_88([&] {
this->return_tracker = previous_return_tracker;
});
NonnullRefPtr<typename Jakt::parser::ParsedType> const synthetic_type = Jakt::parser::ParsedType::Function(JaktInternal::OptionalNone(),params,can_throw,return_type,span);
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_89([&] {
{
this->generic_inferences.restore(old_generic_inferences);
}

});
Jakt::ids::TypeId type_id = TRY((this->typecheck_typename(synthetic_type,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::FunctionId> return_type_id_pseudo_function_id_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::FunctionId>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *this->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
Jakt::ids::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(Tuple{return_type_id, pseudo_function_id});
};/*case end*/
default:{
this->compiler->panic(ByteString::from_utf8_without_validation("Expected the just-checked function to be of a function type"sv));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::TypeId return_type_id = return_type_id_pseudo_function_id_.template get<0>();
Jakt::ids::FunctionId pseudo_function_id = return_type_id_pseudo_function_id_.template get<1>();

NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::ScopeId effective_namespace_parent_scope_id = scope_id;
NonnullRefPtr<Jakt::types::Scope> effective_namespace_parent_scope = this->get_scope(scope_id);
while (effective_namespace_parent_scope->is_block_scope){
effective_namespace_parent_scope_id = effective_namespace_parent_scope->parent.value();
effective_namespace_parent_scope = this->get_scope(effective_namespace_parent_scope_id);
}
Jakt::ids::ScopeId lambda_scope_id = this->create_scope(effective_namespace_parent_scope_id,can_throw,ByteString::from_utf8_without_validation("lambda"sv),true);
bool is_capturing_everything = false;
JaktInternal::DynamicArray<Jakt::types::CheckedCapture> checked_captures = DynamicArray<Jakt::types::CheckedCapture>::create_with({});
bool has_dependent_capture = false;
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedCapture> _magic = captures.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedCapture> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedCapture capture = _magic_value.value();
{
if (capture.__jakt_init_index() == 4 /* AllByReference */){
checked_captures.push(Jakt::types::CheckedCapture::AllByReference(ByteString::from_utf8_without_validation(""sv),capture.common.init_common.span));
if (!is_capturing_everything){
is_capturing_everything = true;
lambda_scope_id = this->create_scope(scope_id,can_throw,ByteString::from_utf8_without_validation("lambda"sv),true);
}
}
else if (TRY((this->find_var_in_scope(scope_id,capture.common.init_common.name,JaktInternal::OptionalNone()))).has_value()){
ByteString const name = capture.common.init_common.name;
Jakt::utility::Span const span = capture.common.init_common.span;
checked_captures.push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedCapture, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = capture;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* ByValue */:return JaktInternal::ExplicitValue(Jakt::types::CheckedCapture::ByValue(name,span));
case 1 /* ByReference */:return JaktInternal::ExplicitValue(Jakt::types::CheckedCapture::ByReference(name,span));
case 2 /* ByMutableReference */:return JaktInternal::ExplicitValue(Jakt::types::CheckedCapture::ByMutableReference(name,span));
case 3 /* ByComptimeDependency */:{
has_dependent_capture = true;
if (!this->in_comptime_function_call){
this->error(__jakt_format(StringView::from_string_literal("Comptime dependency capture ‘{}’ is only allowed in comptime function calls"sv),name),span);
}
return JaktInternal::ExplicitValue<Jakt::types::CheckedCapture>(Jakt::types::CheckedCapture::ByComptimeDependency(name,span));
}
VERIFY_NOT_REACHED();
case 4 /* AllByReference */:{
this->compiler->panic(ByteString::from_utf8_without_validation("AllByReference capture should not be looked up by name"sv));
}
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
if (!is_capturing_everything){
NonnullRefPtr<Jakt::types::CheckedVariable> const var = TRY((this->find_var_in_scope(scope_id,capture.common.init_common.name,JaktInternal::OptionalNone()))).value();
bool const is_this = var->name == ByteString::from_utf8_without_validation("this"sv);
Jakt::ids::VarId const var_id = module->add_variable(Jakt::types::CheckedVariable::__jakt_create(name,var->type_id,var->is_mutable && ((is_this || (capture.__jakt_init_index() == 1 /* ByReference */)) || (capture.__jakt_init_index() == 2 /* ByMutableReference */)),var->definition_span,var->type_span,var->visibility,var->owner_scope,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()));
this->add_var_to_scope(lambda_scope_id,name,var_id,span);
}
}
else {
this->error(__jakt_format(StringView::from_string_literal("Variable '{}' not found"sv),capture.common.init_common.name),span);
}

}

}
}

if (!is_capturing_everything){
Jakt::ids::ScopeId current_scope_id = scope_id;
NonnullRefPtr<Jakt::types::Scope> lambda_scope = this->get_scope(lambda_scope_id);
while (!current_scope_id.equals(effective_namespace_parent_scope_id)){
NonnullRefPtr<Jakt::types::Scope> const current_scope = this->get_scope(current_scope_id);
lambda_scope->resolution_mixins.push(Jakt::types::ResolutionMixin(current_scope_id,false,true,true,true,true,true,true,true,true));
current_scope_id = current_scope->parent.value();
}
}
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> checked_params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedParameter> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedParameter param = _magic_value.value();
{
Jakt::types::CheckedParameter const checked_param = TRY((this->typecheck_parameter(param,scope_id,first,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
checked_params.push(checked_param);
Jakt::ids::VarId const var_id = module->add_variable(checked_param.variable);
this->add_var_to_scope(lambda_scope_id,checked_param.variable->name,var_id,checked_param.variable->definition_span);
first = false;
}

}
}

JaktInternal::Optional<Jakt::ids::FunctionId> const previous_function_id = this->current_function_id;
this->current_function_id = pseudo_function_id;
ScopeGuard __jakt_var_90([&] {
{
this->current_function_id = previous_function_id;
}

});
if (has_dependent_capture){
return Jakt::types::CheckedExpression::DependentFunction(JaktInternal::OptionalNone(),checked_captures,checked_params,can_throw,return_type_id,block,span,type_id,pseudo_function_id,lambda_scope_id);
}
Jakt::types::CheckedBlock const checked_block = TRY((this->typecheck_block(block,lambda_scope_id,safety_mode,JaktInternal::OptionalNone())));
if (return_type_id.equals(Jakt::types::unknown_type_id())){
bool return_type_updated = false;
if ((!is_fat_arrow) && (return_type->__jakt_init_index() == 15 /* Empty */)){
return_type_id = Jakt::types::void_type_id();
return_type_updated = true;
}
else if (is_fat_arrow && (!checked_block.statements.is_empty())){
NonnullRefPtr<typename Jakt::types::CheckedStatement> __jakt_tmp359 = checked_block.statements.last().value();
if (__jakt_tmp359->__jakt_init_index() == 8 /* Return */){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const val = __jakt_tmp359->as.Return.val;
if (val.has_value()){
return_type_id = TRY((this->resolve_type_var(val.value()->type(),lambda_scope_id)));
return_type_updated = true;
}
}
}
if (return_type_updated){
NonnullRefPtr<Jakt::types::CheckedFunction> f = this->get_function(pseudo_function_id);
f->return_type_id = return_type_id;
type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *this->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(this->find_or_add_type_id(Jakt::types::Type::Function(Jakt::parser::CheckedQualifiers(false),params,can_throw,return_type_id,pseudo_function_id)));
};/*case end*/
default:{
this->compiler->panic(ByteString::from_utf8_without_validation("Expected the just-checked function to be of a function type"sv));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}
return Jakt::types::CheckedExpression::Function(JaktInternal::OptionalNone(),checked_captures,checked_params,can_throw,return_type_id,checked_block,span,type_id,pseudo_function_id,lambda_scope_id);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_namespaced_var_or_simple_enum_constructor_call(ByteString const name,JaktInternal::DynamicArray<ByteString> const namespace_,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint,Jakt::utility::Span const span) {
{
JaktInternal::DynamicArray<Jakt::ids::ScopeId> scopes = DynamicArray<Jakt::ids::ScopeId>::create_with({scope_id});
{
JaktInternal::ArrayIterator<ByteString> _magic = namespace_.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString ns = _magic_value.value();
{
Jakt::ids::ScopeId const scope = scopes.operator[](JaktInternal::checked_sub(scopes.size(),static_cast<size_t>(1ULL)));
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> const ns_in_scope = TRY((this->find_namespace_in_scope(scope,ns,false,JaktInternal::OptionalNone())));
JaktInternal::Optional<Jakt::ids::EnumId> const enum_in_scope = TRY((this->program->find_enum_in_scope(scope,ns,false,JaktInternal::OptionalNone())));
Jakt::ids::ScopeId next_scope = scope;
if (ns_in_scope.has_value()){
next_scope = ns_in_scope.value().template get<0>();
}
else if (enum_in_scope.has_value()){
next_scope = this->get_enum(enum_in_scope.value()).scope_id;
}
else {
this->error(__jakt_format(StringView::from_string_literal("Namespace ‘{}’ not found"sv),ns),span);
}

scopes.push(next_scope);
}

}
}

Jakt::ids::ScopeId const scope = scopes.last().value();
size_t i = static_cast<size_t>(0ULL);
size_t const min_length = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (scopes.size() <= namespace_.size());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(scopes.size());
}else {return JaktInternal::ExplicitValue(namespace_.size());
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::CheckedNamespace> checked_namespaces = DynamicArray<Jakt::types::CheckedNamespace>::create_with({});
while (i < min_length){
checked_namespaces.push(Jakt::types::CheckedNamespace(namespace_.operator[](i),scope));
i++;
}
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>> const var = TRY((this->find_var_in_scope(scope,name,JaktInternal::OptionalNone())));
if (var.has_value()){
return Jakt::types::CheckedExpression::NamespacedVar(JaktInternal::OptionalNone(),checked_namespaces,var.value(),span);
}
Jakt::parser::ParsedCall const implicit_constructor_call = Jakt::parser::ParsedCall(namespace_,name,DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>>::create_with({}),DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>>::create_with({}));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const call_expression = TRY((this->typecheck_call(implicit_constructor_call,scope_id,span,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),safety_mode,type_hint,true)));
Jakt::ids::TypeId const type_id = call_expression->type();
Jakt::types::CheckedCall const call = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedCall, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *call_expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(call);
};/*case end*/
default:{
this->compiler->panic(ByteString::from_utf8_without_validation("typecheck_call returned something other than a CheckedCall"sv));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (call.function_id.has_value()){
return Jakt::types::CheckedExpression::Call(JaktInternal::OptionalNone(),call,span,type_id);
}
this->error(__jakt_format(StringView::from_string_literal("Variable '{}' not found"sv),name),span);
return Jakt::types::CheckedExpression::NamespacedVar(JaktInternal::OptionalNone(),checked_namespaces,Jakt::types::CheckedVariable::__jakt_create(name,Jakt::types::unknown_type_id(),false,span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()),span);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_array(Jakt::ids::ScopeId const scope_id,JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const values,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const fill_size,Jakt::utility::Span const span,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> repeat = JaktInternal::OptionalNone();
if (fill_size.has_value()){
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const fill_size_value = fill_size.value();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const fill_size_checked = TRY((this->typecheck_expression_and_dereference_if_needed(fill_size_value,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::ids::TypeId const fill_size_type = fill_size_checked->type();
if (!this->is_integer(fill_size_type)){
this->error(__jakt_format(StringView::from_string_literal("Type '{}' is not convertible to an integer. Only integer values can be array fill size expressions."sv),TRY((this->type_name(fill_size_type,false)))),fill_size_value->span());
}
repeat = fill_size_checked;
}
Jakt::ids::StructId const array_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Array"sv))));
Jakt::ids::TypeId inner_type_id = Jakt::types::unknown_type_id();
JaktInternal::Optional<Jakt::utility::Span> inferred_type_span = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::ids::TypeId> inner_hint_id = JaktInternal::OptionalNone();
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> type_hint_ids = JaktInternal::OptionalNone();
if (type_hint.has_value()){
type_hint_ids = TRY((this->get_type_ids_from_type_hint_if_struct_ids_match(type_hint.value().common.init_common.type_id,array_struct_id)));
}
if (type_hint_ids.has_value()){
inner_hint_id = type_hint_ids.value().operator[](static_cast<i64>(0LL));
}
JaktInternal::Optional<Jakt::typechecker::TypeHint> value_type_hint = JaktInternal::OptionalNone();
if (inner_hint_id.has_value()){
value_type_hint = Jakt::typechecker::TypeHint::MustBe(inner_hint_id.value());
}
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> _magic = values.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedExpression> value = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression(value,scope_id,safety_mode,value_type_hint)));
Jakt::ids::TypeId const current_value_type_id = checked_expr->type();
if (current_value_type_id.equals(Jakt::types::void_type_id())){
this->error(ByteString::from_utf8_without_validation("Cannot create an array with values of type void\n"sv),span);
}
if (inner_type_id.equals(Jakt::types::unknown_type_id())){
inner_type_id = current_value_type_id;
inferred_type_span = value->span();
}
else if (!inner_type_id.equals(current_value_type_id)){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Type '{}' does not match type '{}' of previous values in array"sv),TRY((this->type_name(current_value_type_id,false))),TRY((this->type_name(inner_type_id,false)))),value->span(),__jakt_format(StringView::from_string_literal("Array was inferred to store type '{}' here"sv),TRY((this->type_name(inner_type_id,false)))),inferred_type_span.value());
}
vals.push(checked_expr);
}

}
}

if (inner_type_id.equals(Jakt::types::unknown_type_id())){
if (inner_hint_id.has_value()){
inner_type_id = inner_hint_id.value();
}
else if (type_hint.has_value() && type_hint.value().common.init_common.type_id.equals(Jakt::types::unknown_type_id())){
this->error(ByteString::from_utf8_without_validation("Cannot infer generic type for Array<T>"sv),span);
}
}
Jakt::ids::TypeId const type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),array_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id})));
if (type_hint.has_value()){
TRY((this->check_types_for_compat(type_hint.value(),type_id,this->generic_inferences,span)));
}
if (inner_hint_id.has_value()){
inner_type_id = TRY((this->choose_broader_type_id(inner_type_id,inner_hint_id.value(),this->generic_inferences,span)));
}
return Jakt::types::CheckedExpression::JaktArray(JaktInternal::OptionalNone(),vals,repeat,span,type_id,inner_type_id);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_set(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const values,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
Jakt::ids::TypeId inner_type_id = Jakt::types::unknown_type_id();
JaktInternal::Optional<Jakt::utility::Span> inner_type_span = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> output = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
Jakt::ids::StructId const set_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Set"sv))));
JaktInternal::Optional<Jakt::ids::TypeId> inner_hint_id = JaktInternal::OptionalNone();
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> type_hint_ids = JaktInternal::OptionalNone();
if (type_hint.has_value()){
type_hint_ids = TRY((this->get_type_ids_from_type_hint_if_struct_ids_match(type_hint.value().common.init_common.type_id,set_struct_id)));
}
if (type_hint_ids.has_value()){
inner_hint_id = type_hint_ids.value().operator[](static_cast<i64>(0LL));
}
JaktInternal::Optional<Jakt::typechecker::TypeHint> value_type_hint = JaktInternal::OptionalNone();
if (inner_hint_id.has_value()){
value_type_hint = Jakt::typechecker::TypeHint::MustBe(inner_hint_id.value());
}
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> _magic = values.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedExpression> value = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_value = TRY((this->typecheck_expression(value,scope_id,safety_mode,value_type_hint)));
Jakt::ids::TypeId const current_value_type_id = checked_value->type();
if (inner_type_id.equals(Jakt::types::unknown_type_id())){
if (current_value_type_id.equals(Jakt::types::void_type_id()) || current_value_type_id.equals(Jakt::types::unknown_type_id())){
this->error(ByteString::from_utf8_without_validation("Cannot create a set with values of type void"sv),value->span());
}
inner_type_id = current_value_type_id;
inner_type_span = value->span();
}
else if (!inner_type_id.equals(current_value_type_id)){
ByteString const set_type_name = TRY((this->type_name(inner_type_id,false)));
this->error_with_hint(__jakt_format(StringView::from_string_literal("Type '{}' does not match type '{}' of previous values in set"sv),TRY((this->type_name(current_value_type_id,false))),set_type_name),value->span(),__jakt_format(StringView::from_string_literal("Set was inferred to store type '{}' here"sv),set_type_name),inner_type_span.value());
}
output.push(checked_value);
}

}
}

if (inner_type_id.equals(Jakt::types::unknown_type_id())){
if (inner_hint_id.has_value()){
inner_type_id = inner_hint_id.value();
}
else {
this->error(ByteString::from_utf8_without_validation("Cannot infer generic type for Set<T>"sv),span);
}

}
if (!inner_type_id.equals(Jakt::types::unknown_type_id())){
TRY((this->ensure_type_implements_trait(inner_type_id,ByteString::from_utf8_without_validation("Hashable"sv),JaktInternal::OptionalNone(),scope_id,span)));
TRY((this->ensure_type_implements_trait(inner_type_id,ByteString::from_utf8_without_validation("Equal"sv),DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id}),scope_id,span)));
}
if (inner_hint_id.has_value()){
inner_type_id = TRY((this->choose_broader_type_id(inner_type_id,inner_hint_id.value(),this->generic_inferences,span)));
}
Jakt::ids::TypeId const type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),set_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id})));
return Jakt::types::CheckedExpression::JaktSet(JaktInternal::OptionalNone(),output,span,type_id,inner_type_id);
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_generic_arguments_method_call(NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr,Jakt::parser::ParsedCall const call,Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span,bool const is_optional,Jakt::types::SafetyMode const safety_mode) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> checked_args = DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
checked_args.ensure_capacity(call.args.size());
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> _magic = call.args.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> name_____expr__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const jakt__name_____expr__ = name_____expr__;
ByteString const name = jakt__name_____expr__.template get<0>();
Jakt::utility::Span const _ = jakt__name_____expr__.template get<1>();
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr = jakt__name_____expr__.template get<2>();

NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_arg_expr = TRY((this->typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone())));
checked_args.push(Tuple{name, checked_arg_expr});
}

}
}

JaktInternal::DynamicArray<Jakt::ids::TypeId> checked_type_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = call.type_args.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> type_arg = _magic_value.value();
{
checked_type_args.push(TRY((this->typecheck_typename(type_arg,scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
}

}
}

return Jakt::types::CheckedExpression::MethodCall(JaktInternal::OptionalNone(),checked_expr,Jakt::types::CheckedCall(DynamicArray<Jakt::types::ResolvedNamespace>::create_with({}),call.name,checked_args,checked_type_args,JaktInternal::OptionalNone(),Jakt::types::unknown_type_id(),false,JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default()),span,is_optional,Jakt::types::unknown_type_id());
}
}

ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::types::CheckedMatchPattern,Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool>> Jakt::typechecker::Typechecker::typecheck_match_variant(Jakt::parser::ParsedMatchCase const& case_,Jakt::ids::TypeId const subject_type_id,size_t const variant_index,JaktInternal::Optional<Jakt::ids::TypeId> const final_result_type,Jakt::types::CheckedEnumVariant const variant,JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const variant_arguments,JaktInternal::Dictionary<ByteString,Jakt::parser::ParsedPatternDefault> const default_bindings,Jakt::utility::Span const arguments_span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode) {
{
JaktInternal::Optional<ByteString> covered_name = JaktInternal::OptionalNone();
Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,__jakt_format(StringView::from_string_literal("catch-enum-variant({})"sv),variant.name()),true);
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::types::CheckedMatchPattern,Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
{
covered_name = name;
if (!variant_arguments.is_empty()){
this->error(__jakt_format(StringView::from_string_literal("Match case '{}' cannot have arguments"sv),name),arguments_span);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
covered_name = name;
if (!variant_arguments.is_empty()){
if (variant_arguments.size() != static_cast<size_t>(1ULL)){
this->error(__jakt_format(StringView::from_string_literal("Match case ‘{}’ must have exactly one argument"sv),name),span);
}
else {
Jakt::parser::EnumVariantPatternArgument const variant_argument = variant_arguments.operator[](static_cast<i64>(0LL));
Jakt::ids::TypeId const variable_type_id = TRY((this->substitute_typevars_in_type(type_id,this->generic_inferences)));
Jakt::ids::VarId const var_id = module->add_variable(Jakt::types::CheckedVariable::__jakt_create(variant_argument.binding,variable_type_id,variant_argument.is_mutable,span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()));
this->add_var_to_scope(new_scope_id,variant_argument.binding,var_id,span);
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
covered_name = name;
JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>> field_variables = DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::VarId var_id = _magic_value.value();
{
field_variables.push(this->program->get_variable(var_id));
}

}
}

JaktInternal::Set<ByteString> seen_names = Set<ByteString>::create_with_values({});
{
JaktInternal::ArrayIterator<Jakt::parser::EnumVariantPatternArgument> _magic = variant_arguments.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::EnumVariantPatternArgument> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::EnumVariantPatternArgument arg = _magic_value.value();
{
if (!arg.name.has_value()){
bool found_field_name = false;
JaktInternal::DynamicArray<ByteString> field_names = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedVariable>> _magic = field_variables.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedVariable> var = _magic_value.value();
{
field_names.push(var->name);
if (var->name == arg.binding){
found_field_name = true;
}
}

}
}

if (!found_field_name){
JaktInternal::DynamicArray<ByteString> unused_field_names = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = field_names.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString field_name = _magic_value.value();
{
if (seen_names.contains(field_name)){
continue;
}
unused_field_names.push(field_name);
}

}
}

this->error_with_hint(__jakt_format(StringView::from_string_literal("Match case argument '{}' for struct-like enum variant '{}' cannot be anon"sv),arg.binding,name),arg.span,__jakt_format(StringView::from_string_literal("Available arguments for '{}' are: {}\n"sv),name,Jakt::utility::join(unused_field_names,ByteString::from_utf8_without_validation(", "sv))),arg.span);
continue;
}
}
ByteString const arg_name = arg.name.value_or_lazy_evaluated([&] { return arg.binding; });
if (seen_names.contains(arg_name)){
this->error(__jakt_format(StringView::from_string_literal("Match case argument '{}' is already defined"sv),arg_name),arg.span);
continue;
}
seen_names.add(arg_name);
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>> matched_field_variable = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedVariable>> _magic = field_variables.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedVariable> var = _magic_value.value();
{
if (var->name == arg_name){
matched_field_variable = var;
}
}

}
}

if (matched_field_variable.has_value()){
Jakt::ids::TypeId const substituted_type_id = TRY((this->substitute_typevars_in_type(matched_field_variable.value()->type_id,this->generic_inferences)));
Jakt::utility::Span const matched_span = matched_field_variable.value()->definition_span;
if (this->dump_type_hints){
TRY((this->dump_type_hint(matched_field_variable.value()->type_id,arg.span)));
}
Jakt::ids::VarId const var_id = module->add_variable(Jakt::types::CheckedVariable::__jakt_create(arg.binding,substituted_type_id,arg.is_mutable,matched_span,JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()));
this->add_var_to_scope(new_scope_id,arg.binding,var_id,matched_span);
}
else {
this->error(__jakt_format(StringView::from_string_literal("Match case argument '{}' does not exist in struct-like enum variant '{}'"sv),arg_name,name),arg.span);
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& name = __jakt_match_value.name;
{
covered_name = name;
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
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,Jakt::parser::ParsedPatternDefault> _magic = default_bindings.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> ___default___ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
ByteString const _ = jakt_____default___.template get<0>();
Jakt::parser::ParsedPatternDefault const default_ = jakt_____default___.template get<1>();

NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_var_decl = TRY((this->typecheck_var_decl(default_.variable,default_.value,new_scope_id,safety_mode,default_.variable.span)));
defaults.push(checked_var_decl);
}

}
}

JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const checked_body_result_type_seen_none_ = TRY((this->typecheck_match_body(case_.body,new_scope_id,safety_mode,this->generic_inferences,final_result_type,case_.marker_span)));
Jakt::types::CheckedMatchBody const checked_body = checked_body_result_type_seen_none_.template get<0>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = checked_body_result_type_seen_none_.template get<1>();
bool const seen_none = checked_body_result_type_seen_none_.template get<2>();

Jakt::types::CheckedMatchPattern const checked_match_pattern = Jakt::types::CheckedMatchPattern::EnumVariant(defaults,variant.name(),variant_arguments,subject_type_id,variant_index,new_scope_id,case_.marker_span);
return Tuple{covered_name, checked_match_pattern, checked_body, result_type, seen_none};
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_match(NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,JaktInternal::DynamicArray<Jakt::parser::ParsedMatchCase> const cases,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expr = TRY((this->typecheck_expression_and_dereference_if_needed(expr,scope_id,safety_mode,JaktInternal::OptionalNone(),span)));
Jakt::ids::TypeId const subject_type_id = checked_expr->type();
NonnullRefPtr<typename Jakt::types::Type> const type_to_match_on = this->get_type(subject_type_id);
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> checked_cases = DynamicArray<Jakt::types::CheckedMatchCase>::create_with({});
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_91([&] {
{
this->generic_inferences.restore(old_generic_inferences);
}

});
JaktInternal::Optional<Jakt::ids::TypeId> final_result_type = JaktInternal::OptionalNone();
if (type_hint.has_value() && ((!type_hint.value().common.init_common.type_id.equals(Jakt::types::unknown_type_id())) && (!(this->get_type(type_hint.value().common.init_common.type_id)->__jakt_init_index() == 18 /* TypeVariable */)))){
final_result_type = type_hint.value().common.init_common.type_id;
}
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp360 = type_to_match_on;
if (__jakt_tmp360->__jakt_init_index() == 21 /* GenericEnumInstance */){
Jakt::ids::EnumId const id = __jakt_tmp360->as.GenericEnumInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp360->as.GenericEnumInstance.args;
Jakt::types::CheckedEnum const enum_ = this->get_enum(id);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enum_.generic_parameters.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::ids::TypeId const generic = enum_.generic_parameters.operator[](i).type_id;
Jakt::ids::TypeId const argument_type = args.operator[](i);
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(generic,argument_type)){
this->generic_inferences.set(generic,argument_type);
}
}

}
}

}
bool yielded_none = false;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type_to_match_on;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
bool seen_catch_all = false;
bool expanded_catch_all = false;
JaktInternal::Optional<Jakt::utility::Span> catch_all_span = JaktInternal::OptionalNone();
JaktInternal::Set<ByteString> covered_variants = Set<ByteString>::create_with_values({});
size_t const case_count = cases.size();
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMatchCase> _magic = cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMatchCase case_ = _magic_value.value();
{
JaktInternal::DynamicArray<Jakt::types::CheckedMatchPattern> checked_patterns = DynamicArray<Jakt::types::CheckedMatchPattern>::create_with({});
JaktInternal::Optional<Jakt::types::CheckedMatchBody> last_checked_body = JaktInternal::OptionalNone();
ScopeGuard __jakt_var_92([&] {
if (!checked_patterns.is_empty()){
checked_cases.push(Jakt::types::CheckedMatchCase(checked_patterns,last_checked_body.value()));
}
});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMatchPattern> _magic = case_.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMatchPattern pattern = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
Jakt::utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> variant_names_ = variant_names;
if (variant_names_.size() == static_cast<size_t>(1ULL)){
JaktInternal::Tuple<ByteString,Jakt::utility::Span> const temp = variant_names_.operator[](static_cast<i64>(0LL));
variant_names_ = DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>::create_with({Tuple{enum_.name, variant_names_.operator[](static_cast<i64>(0LL)).template get<1>()}, temp});
}
if (variant_names_.is_empty()){
return JaktInternal::LoopContinue{};
}
if ([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(variant_names_.operator[](static_cast<i64>(0LL)).template get<0>(),enum_.name)){
this->error(__jakt_format(StringView::from_string_literal("Match case '{}' does not match enum '{}'"sv),variant_names_.operator[](static_cast<i64>(0LL)).template get<0>(),enum_.name),variant_names_.operator[](static_cast<i64>(0LL)).template get<1>());
return JaktInternal::LoopContinue{};
}
size_t i = static_cast<size_t>(0ULL);
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> matched_variant = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> variant_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant v = _magic_value.value();
{
if (v.name() == variant_names_.operator[](static_cast<i64>(1LL)).template get<0>()){
matched_variant = v;
variant_index = i;
}
i++;
}

}
}

if (!matched_variant.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Enum '{}' does not contain a variant named '{}'"sv),enum_.name,variant_names_.operator[](static_cast<i64>(1LL)).template get<0>()),case_.marker_span);
return Jakt::types::CheckedExpression::Match(JaktInternal::OptionalNone(),checked_expr,DynamicArray<Jakt::types::CheckedMatchCase>::create_with({}),span,Jakt::types::unknown_type_id(),false);
}
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::types::CheckedMatchPattern,Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const covered_name_checked_match_case_checked_body_result_type_seen_none_ = TRY((this->typecheck_match_variant(case_,subject_type_id,variant_index.value(),final_result_type,matched_variant.value(),variant_arguments,pattern.common.init_common.defaults,arguments_span,scope_id,safety_mode)));
JaktInternal::Optional<ByteString> const covered_name = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<0>();
Jakt::types::CheckedMatchPattern const checked_match_case = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<1>();
Jakt::types::CheckedMatchBody const checked_body = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<2>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<3>();
bool const seen_none = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<4>();

last_checked_body = checked_body;
yielded_none |= seen_none;
if (covered_name.has_value()){
covered_variants.add(covered_name.value());
}
final_result_type = result_type;
checked_patterns.push(checked_match_case);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
Jakt::utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if (current_case_index != JaktInternal::checked_sub(case_count,static_cast<size_t>(1ULL))){
this->error(ByteString::from_utf8_without_validation("Match else case is only allowed as the last case"sv),case_.marker_span);
}
if (seen_catch_all){
this->error(ByteString::from_utf8_without_validation("Multiple catch-all cases in match are not allowed"sv),case_.marker_span);
}
else {
seen_catch_all = true;
}

if (variant_arguments.size() > static_cast<size_t>(0ULL)){
size_t variant_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
if (!covered_variants.contains(variant.name())){
expanded_catch_all = true;
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::types::CheckedMatchPattern,Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const covered_name_checked_match_pattern_checked_body_result_type_seen_none_ = TRY((this->typecheck_match_variant(case_,subject_type_id,variant_index,final_result_type,variant,variant_arguments,pattern.common.init_common.defaults,arguments_span,scope_id,safety_mode)));
JaktInternal::Optional<ByteString> const covered_name = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<0>();
Jakt::types::CheckedMatchPattern const checked_match_pattern = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<1>();
Jakt::types::CheckedMatchBody const checked_body = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<2>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<3>();
bool const seen_none = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<4>();

last_checked_body = checked_body;
yielded_none |= seen_none;
if (covered_name.has_value()){
covered_variants.add(covered_name.value());
}
final_result_type = result_type;
checked_patterns.push(checked_match_pattern);
}
variant_index++;
}

}
}

}
else {
Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,ByteString::from_utf8_without_validation("catch-all"sv),true);
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,Jakt::parser::ParsedPatternDefault> _magic = pattern.common.init_common.defaults.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> ___default___ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
ByteString const _ = jakt_____default___.template get<0>();
Jakt::parser::ParsedPatternDefault const default_ = jakt_____default___.template get<1>();

NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_var_decl = TRY((this->typecheck_var_decl(default_.variable,default_.value,new_scope_id,safety_mode,default_.variable.span)));
defaults.push(checked_var_decl);
}

}
}

JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const checked_body_result_type_seen_none_ = TRY((this->typecheck_match_body(case_.body,new_scope_id,safety_mode,this->generic_inferences,final_result_type,case_.marker_span)));
Jakt::types::CheckedMatchBody const checked_body = checked_body_result_type_seen_none_.template get<0>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = checked_body_result_type_seen_none_.template get<1>();
bool const seen_none = checked_body_result_type_seen_none_.template get<2>();

last_checked_body = checked_body;
yielded_none |= seen_none;
final_result_type = result_type;
Jakt::types::CheckedMatchPattern const checked_match_pattern = Jakt::types::CheckedMatchPattern::CatchAll(defaults,false,case_.marker_span);
checked_patterns.push(checked_match_pattern);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

current_case_index++;
}

}
}

JaktInternal::DynamicArray<ByteString> enum_variant_names = DynamicArray<ByteString>::create_with({});
JaktInternal::DynamicArray<ByteString> missing_variants = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
enum_variant_names.push(variant.name());
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = enum_variant_names.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString variant = _magic_value.value();
{
if (!covered_variants.contains(variant)){
missing_variants.push(variant);
}
}

}
}

if (missing_variants.size() > static_cast<size_t>(0ULL)){
if (!seen_catch_all){
this->error(__jakt_format(StringView::from_string_literal("Match expression is not exhaustive, missing variants are: {}"sv),Jakt::utility::join(missing_variants,ByteString::from_utf8_without_validation(", "sv))),span);
}
}
else if (seen_catch_all && (!expanded_catch_all)){
this->error(ByteString::from_utf8_without_validation("All variants are covered, but an irrefutable pattern is also present"sv),span);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
bool seen_catch_all = false;
bool expanded_catch_all = false;
JaktInternal::Optional<Jakt::utility::Span> catch_all_span = JaktInternal::OptionalNone();
JaktInternal::Set<ByteString> covered_variants = Set<ByteString>::create_with_values({});
size_t const case_count = cases.size();
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMatchCase> _magic = cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMatchCase case_ = _magic_value.value();
{
JaktInternal::DynamicArray<Jakt::types::CheckedMatchPattern> checked_patterns = DynamicArray<Jakt::types::CheckedMatchPattern>::create_with({});
JaktInternal::Optional<Jakt::types::CheckedMatchBody> last_checked_body = JaktInternal::OptionalNone();
ScopeGuard __jakt_var_93([&] {
if (!checked_patterns.is_empty()){
checked_cases.push(Jakt::types::CheckedMatchCase(checked_patterns,last_checked_body.value()));
}
});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMatchPattern> _magic = case_.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMatchPattern pattern = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
Jakt::utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> variant_names_ = variant_names;
if (variant_names_.size() == static_cast<size_t>(1ULL)){
JaktInternal::Tuple<ByteString,Jakt::utility::Span> const temp = variant_names_.operator[](static_cast<i64>(0LL));
variant_names_ = DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>>::create_with({Tuple{enum_.name, variant_names_.operator[](static_cast<i64>(0LL)).template get<1>()}, temp});
}
if (variant_names_.is_empty()){
return JaktInternal::LoopContinue{};
}
if ([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(variant_names_.operator[](static_cast<i64>(0LL)).template get<0>(),enum_.name)){
this->error(__jakt_format(StringView::from_string_literal("Match case '{}' does not match enum '{}'"sv),variant_names_.operator[](static_cast<i64>(0LL)).template get<0>(),enum_.name),variant_names_.operator[](static_cast<i64>(0LL)).template get<1>());
return JaktInternal::LoopContinue{};
}
size_t i = static_cast<size_t>(0ULL);
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> matched_variant = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> variant_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant v = _magic_value.value();
{
if (v.name() == variant_names_.operator[](static_cast<i64>(1LL)).template get<0>()){
matched_variant = v;
variant_index = i;
}
i++;
}

}
}

if (!matched_variant.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Enum '{}' does not contain a variant named '{}'"sv),enum_.name,variant_names_.operator[](static_cast<i64>(1LL)).template get<0>()),case_.marker_span);
return Jakt::types::CheckedExpression::Match(JaktInternal::OptionalNone(),checked_expr,DynamicArray<Jakt::types::CheckedMatchCase>::create_with({}),span,Jakt::types::unknown_type_id(),false);
}
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::types::CheckedMatchPattern,Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const covered_name_checked_match_case_checked_body_result_type_seen_none_ = TRY((this->typecheck_match_variant(case_,subject_type_id,variant_index.value(),final_result_type,matched_variant.value(),variant_arguments,pattern.common.init_common.defaults,arguments_span,scope_id,safety_mode)));
JaktInternal::Optional<ByteString> const covered_name = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<0>();
Jakt::types::CheckedMatchPattern const checked_match_case = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<1>();
Jakt::types::CheckedMatchBody const checked_body = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<2>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<3>();
bool const seen_none = covered_name_checked_match_case_checked_body_result_type_seen_none_.template get<4>();

last_checked_body = checked_body;
yielded_none |= seen_none;
if (covered_name.has_value()){
covered_variants.add(covered_name.value());
}
final_result_type = result_type;
checked_patterns.push(checked_match_case);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
Jakt::utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if (current_case_index != JaktInternal::checked_sub(case_count,static_cast<size_t>(1ULL))){
this->error(ByteString::from_utf8_without_validation("Match else case is only allowed as the last case"sv),case_.marker_span);
}
if (seen_catch_all){
this->error(ByteString::from_utf8_without_validation("Multiple catch-all cases in match are not allowed"sv),case_.marker_span);
}
else {
seen_catch_all = true;
}

if (variant_arguments.size() > static_cast<size_t>(0ULL)){
size_t variant_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
if (!covered_variants.contains(variant.name())){
expanded_catch_all = true;
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::types::CheckedMatchPattern,Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const covered_name_checked_match_pattern_checked_body_result_type_seen_none_ = TRY((this->typecheck_match_variant(case_,subject_type_id,variant_index,final_result_type,variant,variant_arguments,pattern.common.init_common.defaults,arguments_span,scope_id,safety_mode)));
JaktInternal::Optional<ByteString> const covered_name = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<0>();
Jakt::types::CheckedMatchPattern const checked_match_pattern = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<1>();
Jakt::types::CheckedMatchBody const checked_body = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<2>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<3>();
bool const seen_none = covered_name_checked_match_pattern_checked_body_result_type_seen_none_.template get<4>();

last_checked_body = checked_body;
yielded_none |= seen_none;
if (covered_name.has_value()){
covered_variants.add(covered_name.value());
}
final_result_type = result_type;
checked_patterns.push(checked_match_pattern);
}
variant_index++;
}

}
}

}
else {
Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,ByteString::from_utf8_without_validation("catch-all"sv),true);
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,Jakt::parser::ParsedPatternDefault> _magic = pattern.common.init_common.defaults.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> ___default___ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
ByteString const _ = jakt_____default___.template get<0>();
Jakt::parser::ParsedPatternDefault const default_ = jakt_____default___.template get<1>();

NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_var_decl = TRY((this->typecheck_var_decl(default_.variable,default_.value,new_scope_id,safety_mode,default_.variable.span)));
defaults.push(checked_var_decl);
}

}
}

JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const checked_body_result_type_seen_none_ = TRY((this->typecheck_match_body(case_.body,new_scope_id,safety_mode,this->generic_inferences,final_result_type,case_.marker_span)));
Jakt::types::CheckedMatchBody const checked_body = checked_body_result_type_seen_none_.template get<0>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = checked_body_result_type_seen_none_.template get<1>();
bool const seen_none = checked_body_result_type_seen_none_.template get<2>();

last_checked_body = checked_body;
yielded_none |= seen_none;
final_result_type = result_type;
Jakt::types::CheckedMatchPattern const checked_match_pattern = Jakt::types::CheckedMatchPattern::CatchAll(defaults,false,case_.marker_span);
checked_patterns.push(checked_match_pattern);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

current_case_index++;
}

}
}

JaktInternal::DynamicArray<ByteString> enum_variant_names = DynamicArray<ByteString>::create_with({});
JaktInternal::DynamicArray<ByteString> missing_variants = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
enum_variant_names.push(variant.name());
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = enum_variant_names.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString variant = _magic_value.value();
{
if (!covered_variants.contains(variant)){
missing_variants.push(variant);
}
}

}
}

if (missing_variants.size() > static_cast<size_t>(0ULL)){
if (!seen_catch_all){
this->error(__jakt_format(StringView::from_string_literal("Match expression is not exhaustive, missing variants are: {}"sv),Jakt::utility::join(missing_variants,ByteString::from_utf8_without_validation(", "sv))),span);
}
}
else if (seen_catch_all && (!expanded_catch_all)){
this->error(ByteString::from_utf8_without_validation("All variants are covered, but an irrefutable pattern is also present"sv),span);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Void */:{
this->error(ByteString::from_utf8_without_validation("Can't match on 'void' type"sv),checked_expr->span());
}
return JaktInternal::ExplicitValue<void>();
default:return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (type_to_match_on->is_boxed(this->program));
if (__jakt_enum_value) {{
JaktInternal::Tuple<Jakt::ids::StructId,JaktInternal::DynamicArray<Jakt::ids::StructId>> const struct_to_match_on_struct_inheritance_chain_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<Jakt::ids::StructId,JaktInternal::DynamicArray<Jakt::ids::StructId>>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *type_to_match_on;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Tuple{id, this->struct_inheritance_chain(id)});
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(Tuple{id, this->struct_inheritance_chain(id)});
};/*case end*/
default:{
this->compiler->panic(ByteString::from_utf8_without_validation("Expected struct or generic instance in inheritance-style match expression"sv));
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::StructId const struct_to_match_on = struct_to_match_on_struct_inheritance_chain_.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::StructId> const struct_inheritance_chain = struct_to_match_on_struct_inheritance_chain_.template get<1>();

bool seen_catch_all = false;
bool catch_all_matches_original_type = false;
JaktInternal::Optional<Jakt::utility::Span> catch_all_marker_span = JaktInternal::OptionalNone();
JaktInternal::Set<Jakt::ids::StructId> covered_cases = Set<Jakt::ids::StructId>::create_with_values({});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMatchCase> _magic = cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMatchCase case_ = _magic_value.value();
{
JaktInternal::DynamicArray<Jakt::types::CheckedMatchPattern> checked_patterns = DynamicArray<Jakt::types::CheckedMatchPattern>::create_with({});
JaktInternal::Optional<Jakt::types::CheckedMatchBody> last_checked_body = JaktInternal::OptionalNone();
ScopeGuard __jakt_var_94([&] {
if (!checked_patterns.is_empty()){
checked_cases.push(Jakt::types::CheckedMatchCase(checked_patterns,last_checked_body.value()));
}
});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMatchPattern> _magic = case_.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMatchPattern pattern = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
Jakt::utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
JaktInternal::DynamicArray<ByteString> names = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> _magic = variant_names.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span> name = _magic_value.value();
{
names.push(name.template get<0>());
}

}
}

Jakt::ids::TypeId const type = TRY((this->typecheck_typename(Jakt::parser::ParsedType::NamespacedName(JaktInternal::OptionalNone(),names.last().value(),names.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(JaktInternal::checked_sub(names.size(),static_cast<size_t>(1ULL)))}).to_array(),DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedType>>::create_with({}),case_.marker_span),scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if (seen_catch_all){
this->error_with_hint(ByteString::from_utf8_without_validation("This case is unreachable because a catch-all case is present before it"sv),case_.marker_span,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (catch_all_matches_original_type);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Catch-all case matching the original subject type seen here"sv));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Catch-all case seen here"sv));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        return JaktInternal::LoopBreak {};
    if (_jakt_value.is_loop_continue())
        return JaktInternal::LoopContinue {};
    _jakt_value.release_value();
}),catch_all_marker_span.value());
}
Function<ErrorOr<void>(Jakt::ids::StructId)> const check_cover_overlap = [this, &type, &case_, &covered_cases](Jakt::ids::StructId id) -> ErrorOr<void> {{
{
JaktInternal::SetIterator<Jakt::ids::StructId> _magic = covered_cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::StructId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::StructId covered_case = _magic_value.value();
{
if (this->struct_inherits_from(id,covered_case,JaktInternal::OptionalNone())){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Type ‘{}’ used as a match case at this position is redundant"sv),TRY((this->type_name(type,false)))),case_.marker_span,__jakt_format(StringView::from_string_literal("Type ‘{}’ (a supertype of ‘{}’) has been covered by a case above"sv),this->get_struct(covered_case).name,TRY((this->type_name(type,false)))),case_.marker_span);
}
}

}
}

}
return {};
}
;
if (type.equals(subject_type_id)){
if (seen_catch_all){
this->error(ByteString::from_utf8_without_validation("Multiple catch-all cases in match are not allowed"sv),case_.marker_span);
}
else {
seen_catch_all = true;
catch_all_marker_span = case_.marker_span;
catch_all_matches_original_type = true;
TRY((check_cover_overlap(struct_to_match_on)));
}

}
else {
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *this->get_type(type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
if ((!this->struct_inherits_from(struct_to_match_on,id,struct_inheritance_chain)) && (!this->struct_inherits_from(id,struct_to_match_on,JaktInternal::OptionalNone()))){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Type ‘{}’ cannot be used as a match case for ‘{}’"sv),TRY((this->type_name(type,false))),TRY((this->type_name(subject_type_id,false)))),case_.marker_span,__jakt_format(StringView::from_string_literal("Neither ‘{}’ nor ‘{}’ are super types of the other"sv),TRY((this->type_name(type,false))),TRY((this->type_name(subject_type_id,false)))),case_.marker_span);
}
else {
TRY((check_cover_overlap(id)));
covered_cases.add(id);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
{
if ((!this->struct_inherits_from(struct_to_match_on,id,struct_inheritance_chain)) && (!this->struct_inherits_from(id,struct_to_match_on,JaktInternal::OptionalNone()))){
this->error_with_hint(__jakt_format(StringView::from_string_literal("Type ‘{}’ cannot be used as a match case for ‘{}’"sv),TRY((this->type_name(type,false))),TRY((this->type_name(subject_type_id,false)))),case_.marker_span,__jakt_format(StringView::from_string_literal("Neither ‘{}’ nor ‘{}’ are super types of the other"sv),TRY((this->type_name(type,false))),TRY((this->type_name(subject_type_id,false)))),case_.marker_span);
}
else {
TRY((check_cover_overlap(id)));
covered_cases.add(id);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
this->error(__jakt_format(StringView::from_string_literal("Type ‘{}’ cannot be used as a match case for ‘{}’"sv),TRY((this->type_name(type,false))),TRY((this->type_name(subject_type_id,false)))),case_.marker_span);
}
return JaktInternal::ExplicitValue<void>();
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

Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,__jakt_format(StringView::from_string_literal("class-variant({})"sv),names),true);
JaktInternal::Optional<Jakt::types::ClassInstanceRebind> rebind_name = JaktInternal::OptionalNone();
if (!variant_arguments.is_empty()){
if (variant_arguments.size() != static_cast<size_t>(1ULL)){
this->error(ByteString::from_utf8_without_validation("Class instance matches may only have one match argument (the name to rebind to)"sv),arguments_span);
}
Jakt::parser::EnumVariantPatternArgument const arg = variant_arguments.operator[](static_cast<i64>(0LL));
rebind_name = Jakt::types::ClassInstanceRebind(arg.name_in_enum(),arg.name_in_enum_span(),arg.is_mutable,arg.is_reference);
NonnullRefPtr<Jakt::types::Module> module = this->current_module();
Jakt::ids::VarId const variable_id = module->add_variable(Jakt::types::CheckedVariable::__jakt_create(rebind_name.value().name,type,rebind_name.value().is_mutable,rebind_name.value().name_span,case_.marker_span,Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()));
if (rebind_name.value().is_mutable && (!checked_expr->is_mutable(this->program))){
this->error(ByteString::from_utf8_without_validation("Cannot call mutating method on an immutable object instance"sv),span);
}
this->add_var_to_scope(new_scope_id,rebind_name.value().name,variable_id,rebind_name.value().name_span);
}
JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const checked_body_result_type_seen_none_ = TRY((this->typecheck_match_body(case_.body,new_scope_id,safety_mode,this->generic_inferences,final_result_type,case_.marker_span)));
Jakt::types::CheckedMatchBody const checked_body = checked_body_result_type_seen_none_.template get<0>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = checked_body_result_type_seen_none_.template get<1>();
bool const seen_none = checked_body_result_type_seen_none_.template get<2>();

last_checked_body = checked_body;
yielded_none |= seen_none;
final_result_type = result_type;
checked_patterns.push(Jakt::types::CheckedMatchPattern::ClassInstance(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),type,rebind_name,case_.marker_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
Jakt::utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if (seen_catch_all){
this->error(ByteString::from_utf8_without_validation("Multiple catch-all cases in match are not allowed"sv),case_.marker_span);
}
else {
seen_catch_all = true;
catch_all_marker_span = case_.marker_span;
Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,ByteString::from_utf8_without_validation("class-variant(else)"sv),true);
if (!variant_arguments.is_empty()){
this->error(ByteString::from_utf8_without_validation("Catch-all cases in class instance matches cannot have arguments"sv),arguments_span);
}
JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const checked_body_result_type_seen_none_ = TRY((this->typecheck_match_body(case_.body,new_scope_id,safety_mode,this->generic_inferences,final_result_type,case_.marker_span)));
Jakt::types::CheckedMatchBody const checked_body = checked_body_result_type_seen_none_.template get<0>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = checked_body_result_type_seen_none_.template get<1>();
bool const seen_none = checked_body_result_type_seen_none_.template get<2>();

last_checked_body = checked_body;
yielded_none |= seen_none;
final_result_type = result_type;
checked_patterns.push(Jakt::types::CheckedMatchPattern::CatchAll(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),false,case_.marker_span));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
this->error(ByteString::from_utf8_without_validation("Only named types and 'else' patterns are allowed in class instance match expressions"sv),case_.marker_span);
}
return JaktInternal::ExplicitValue<void>();
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
}

if (!seen_catch_all){
JaktInternal::Set<ByteString> missing = Set<ByteString>::create_with_values({});
{
JaktInternal::ArrayIterator<Jakt::ids::StructId> _magic = struct_inheritance_chain.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::StructId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::StructId struct_id = _magic_value.value();
{
if (!covered_cases.contains(struct_id)){
ByteString const struct_name = this->get_struct(struct_id).name;
missing.add(__jakt_format(StringView::from_string_literal("‘{}’"sv),struct_name));
}
}

}
}

if (!missing.is_empty()){
ByteStringBuilder builder = ByteStringBuilder::create();
builder.append(StringView::from_string_literal("Missing match cases for "sv));
bool first = true;
{
JaktInternal::SetIterator<ByteString> _magic = missing.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString name = _magic_value.value();
{
if (first){
first = false;
}
else {
builder.append(StringView::from_string_literal(", "sv));
}

builder.append(name);
}

}
}

this->error(builder.to_string(),span);
}
}
}
return JaktInternal::ExplicitValue<void>();
}else if (!__jakt_enum_value) {{
bool const is_boolean_match = type_to_match_on->__jakt_init_index() == 1 /* Bool */;
bool seen_true = false;
bool seen_false = false;
JaktInternal::Optional<Jakt::utility::Span> catch_all_span = JaktInternal::OptionalNone();
bool is_enum_match = false;
bool is_value_match = false;
bool seen_catch_all = false;
bool all_variants_constant = true;
size_t const case_count = cases.size();
size_t current_case_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMatchCase> _magic = cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMatchCase case_ = _magic_value.value();
{
JaktInternal::DynamicArray<Jakt::types::CheckedMatchPattern> checked_patterns = DynamicArray<Jakt::types::CheckedMatchPattern>::create_with({});
JaktInternal::Optional<Jakt::types::CheckedMatchBody> last_checked_body = JaktInternal::OptionalNone();
ScopeGuard __jakt_var_95([&] {
if (!checked_patterns.is_empty()){
checked_cases.push(Jakt::types::CheckedMatchCase(checked_patterns,last_checked_body.value()));
}
});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMatchPattern> _magic = case_.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::ParsedMatchPattern pattern = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span>> const& variant_names = __jakt_match_value.variant_names;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
Jakt::utility::Span const& arguments_span = __jakt_match_value.arguments_span;
{
if (is_value_match){
this->error(ByteString::from_utf8_without_validation("Cannot have an enum match case in a match expression containing value matches"sv),case_.marker_span);
}
if (variant_names.size() == static_cast<size_t>(0ULL)){
this->compiler->panic(ByteString::from_utf8_without_validation("typecheck_match - else - EnumVariant - variant_names.size() == 0"sv));
}
is_enum_match = true;
Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,__jakt_format(StringView::from_string_literal("catch-enum-variant({})"sv),variant_names),true);
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,Jakt::parser::ParsedPatternDefault> _magic = pattern.common.init_common.defaults.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> ___default___ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
ByteString const _ = jakt_____default___.template get<0>();
Jakt::parser::ParsedPatternDefault const default_ = jakt_____default___.template get<1>();

NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_var_decl = TRY((this->typecheck_var_decl(default_.variable,default_.value,new_scope_id,safety_mode,default_.variable.span)));
defaults.push(checked_var_decl);
}

}
}

JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const checked_body_result_type_seen_none_ = TRY((this->typecheck_match_body(case_.body,new_scope_id,safety_mode,this->generic_inferences,final_result_type,case_.marker_span)));
Jakt::types::CheckedMatchBody const checked_body = checked_body_result_type_seen_none_.template get<0>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = checked_body_result_type_seen_none_.template get<1>();
bool const seen_none = checked_body_result_type_seen_none_.template get<2>();

last_checked_body = checked_body;
yielded_none |= seen_none;
final_result_type = result_type;
Jakt::types::CheckedMatchPattern const checked_match_pattern = Jakt::types::CheckedMatchPattern::EnumVariant(defaults,variant_names.last().value().template get<0>(),variant_arguments,subject_type_id,static_cast<size_t>(0ULL),new_scope_id,case_.marker_span);
checked_patterns.push(checked_match_pattern);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& variant_arguments = __jakt_match_value.variant_arguments;
{
if (current_case_index != JaktInternal::checked_sub(case_count,static_cast<size_t>(1ULL))){
this->error(ByteString::from_utf8_without_validation("Match else case is only allowed as the last case"sv),case_.marker_span);
}
catch_all_span = case_.marker_span;
if (seen_catch_all){
this->error(ByteString::from_utf8_without_validation("Multiple catch-all cases in match are not allowed"sv),case_.marker_span);
}
else {
seen_catch_all = true;
}

if (variant_arguments.size() != static_cast<size_t>(0ULL)){
this->compiler->errors.push(Jakt::error::JaktError::Message(ByteString::from_utf8_without_validation("Bindings are not allowed on a generic else"sv),case_.marker_span));
}
Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,ByteString::from_utf8_without_validation("catch-all"sv),true);
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,Jakt::parser::ParsedPatternDefault> _magic = pattern.common.init_common.defaults.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> ___default___ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::parser::ParsedPatternDefault> const jakt_____default___ = ___default___;
ByteString const _ = jakt_____default___.template get<0>();
Jakt::parser::ParsedPatternDefault const default_ = jakt_____default___.template get<1>();

NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_var_decl = TRY((this->typecheck_var_decl(default_.variable,default_.value,new_scope_id,safety_mode,default_.variable.span)));
defaults.push(checked_var_decl);
}

}
}

JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const checked_body_result_type_seen_none_ = TRY((this->typecheck_match_body(case_.body,new_scope_id,safety_mode,this->generic_inferences,final_result_type,case_.marker_span)));
Jakt::types::CheckedMatchBody const checked_body = checked_body_result_type_seen_none_.template get<0>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = checked_body_result_type_seen_none_.template get<1>();
bool const seen_none = checked_body_result_type_seen_none_.template get<2>();

last_checked_body = checked_body;
yielded_none |= seen_none;
final_result_type = result_type;
Jakt::types::CheckedMatchPattern const checked_match_pattern = Jakt::types::CheckedMatchPattern::CatchAll(defaults,variant_arguments.size() != static_cast<size_t>(0ULL),case_.marker_span);
checked_patterns.push(checked_match_pattern);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.value;
{
if (is_enum_match){
this->error(ByteString::from_utf8_without_validation("Cannot have a value match case in a match expression containing enum matches"sv),case_.marker_span);
}
is_value_match = true;
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> pre_condition = DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>::create_with({});
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,JaktInternal::Optional<Jakt::parser::ParsedBlock>,JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>>> const new_condition_new_then_block__should_be_none_ = TRY((this->expand_context_for_bindings(expr,JaktInternal::OptionalNone(),pre_condition,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),scope_id,span)));
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const new_condition = new_condition_new_then_block__should_be_none_.template get<0>();
JaktInternal::Optional<Jakt::parser::ParsedBlock> const new_then_block = new_condition_new_then_block__should_be_none_.template get<1>();
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _should_be_none = new_condition_new_then_block__should_be_none_.template get<2>();

TRY(([](Jakt::typechecker::Typechecker& self, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const& unchecked, Jakt::ids::ScopeId scope_id, Jakt::types::SafetyMode safety_mode, Jakt::types::CheckedBlock& block) -> ErrorOr<void> {{
if (!unchecked.is_empty()){
block.statements.add_capacity(unchecked.size());
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = unchecked.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> stmt = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_stmt = TRY((self.typecheck_statement(stmt,scope_id,safety_mode,JaktInternal::OptionalNone())));
block.control_flow = block.control_flow.updated(checked_stmt->control_flow());
block.statements.push(checked_stmt);
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
((*this),pre_condition,scope_id,safety_mode,this->current_block)));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expression = TRY((this->typecheck_expression_and_dereference_if_needed(new_condition,scope_id,safety_mode,Jakt::typechecker::TypeHint::CouldBe(subject_type_id),span)));
if (is_boolean_match){
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp361 = checked_expression;
if (__jakt_tmp361->__jakt_init_index() == 0 /* Boolean */){
bool const val = __jakt_tmp361->as.Boolean.val;
if (val){
seen_true = true;
}
else {
seen_false = true;
}

}
}
if (!checked_expression->to_number_constant(this->program).has_value()){
all_variants_constant = false;
}
Jakt::ids::TypeId expression_type = checked_expression->type();
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp362 = checked_expression;
if (__jakt_tmp362->__jakt_init_index() == 9 /* Range */){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const from = __jakt_tmp362->as.Range.from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const to = __jakt_tmp362->as.Range.to;
if (from.has_value() || to.has_value()){
if (from.has_value()){
expression_type = from.value()->type();
}
else if (to.has_value()){
expression_type = to.value()->type();
}
}
else {
this->error(ByteString::from_utf8_without_validation("There has to be at least a 'from', or a 'to' in a range expression"sv),expr->span());
return JaktInternal::LoopContinue{};
}

}
TRY((this->check_types_for_compat(expression_type,subject_type_id,this->generic_inferences,case_.marker_span)));
if (!pattern.common.init_common.defaults.is_empty()){
this->error(ByteString::from_utf8_without_validation("Expression patterns cannot have default bindings"sv),case_.marker_span);
}
Jakt::ids::ScopeId const new_scope_id = this->create_scope(scope_id,this->get_scope(scope_id)->can_throw,__jakt_format(StringView::from_string_literal("catch-expression({})"sv),expr),true);
JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool> const checked_body_result_type_seen_none_ = TRY((this->typecheck_match_body(case_.body,new_scope_id,safety_mode,this->generic_inferences,final_result_type,case_.marker_span)));
Jakt::types::CheckedMatchBody const checked_body = checked_body_result_type_seen_none_.template get<0>();
JaktInternal::Optional<Jakt::ids::TypeId> const result_type = checked_body_result_type_seen_none_.template get<1>();
bool const seen_none = checked_body_result_type_seen_none_.template get<2>();

last_checked_body = checked_body;
yielded_none |= seen_none;
final_result_type = result_type;
Jakt::types::CheckedMatchPattern const checked_match_pattern = Jakt::types::CheckedMatchPattern::Expression(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),checked_expression,case_.marker_span);
checked_patterns.push(checked_match_pattern);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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

current_case_index++;
}

}
}

if (is_value_match && (!(seen_catch_all || ((is_boolean_match && seen_true) && seen_false)))){
this->error(ByteString::from_utf8_without_validation("Match expression is not exhaustive, a value match must contain an irrefutable 'else' pattern"sv),span);
}
if (is_value_match && (seen_catch_all && (is_boolean_match && (seen_true && seen_false)))){
this->error(ByteString::from_utf8_without_validation("All cases are covered, but an irrefutable pattern is also present"sv),catch_all_span.value());
}
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (yielded_none && final_result_type.has_value()){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp363 = this->get_type(final_result_type.value());
if (__jakt_tmp363->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp363->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp363->as.GenericInstance.args;
if ((!id.equals(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv)))))) && (!id.equals(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv))))))){
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got None"sv),TRY((this->type_name(final_result_type.value(),false)))),span);
}
}
else {
this->error(__jakt_format(StringView::from_string_literal("Type mismatch: expected ‘{}’, but got None"sv),TRY((this->type_name(final_result_type.value(),false)))),span);
}

}
return Jakt::types::CheckedExpression::Match(JaktInternal::OptionalNone(),checked_expr,checked_cases,span,final_result_type.value_or_lazy_evaluated([&] { return Jakt::types::void_type_id(); }),true);
}
}

ErrorOr<JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool>> Jakt::typechecker::Typechecker::typecheck_match_body(Jakt::parser::ParsedMatchBody const body,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,Jakt::types::GenericInferences& generic_inferences,JaktInternal::Optional<Jakt::ids::TypeId> const final_result_type,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::ids::TypeId> result_type = final_result_type;
bool seen_none = false;
Jakt::types::CheckedMatchBody const checked_match_body = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedMatchBody, ErrorOr<JaktInternal::Tuple<Jakt::types::CheckedMatchBody,JaktInternal::Optional<Jakt::ids::TypeId>,bool>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::parser::ParsedBlock const& block = __jakt_match_value.value;
{
JaktInternal::Optional<Jakt::typechecker::TypeHint> result_type_hint = JaktInternal::OptionalNone();
if (result_type.has_value()){
result_type_hint = Jakt::typechecker::TypeHint::CouldBe(result_type.value());
}
Jakt::types::CheckedBlock const checked_block = TRY((this->typecheck_block(block,scope_id,safety_mode,result_type_hint)));
if (checked_block.control_flow.may_return() || checked_block.yielded_type.has_value()){
Jakt::ids::TypeId const block_type_id = checked_block.yielded_type.value_or_lazy_evaluated([&] { return Jakt::types::void_type_id(); });
Jakt::utility::Span const yield_span = block.find_yield_span().value_or_lazy_evaluated([&] { return span; });
seen_none = checked_block.yielded_none;
if (result_type.has_value()){
result_type = TRY((this->choose_broader_type_id(result_type_hint.value().common.init_common.type_id,block_type_id,generic_inferences,yield_span)));
}
else {
result_type = block_type_id;
}

TRY((this->check_types_for_compat(result_type.value(),block_type_id,generic_inferences,yield_span)));
}
JaktInternal::Optional<Jakt::types::CheckedMatchBody> final_body = JaktInternal::OptionalNone();
if (checked_block.yielded_type.has_value() && (!checked_block.control_flow.never_returns())){
final_body = Jakt::types::CheckedMatchBody::Expression(Jakt::types::CheckedExpression::Block(JaktInternal::OptionalNone(),checked_block,span,checked_block.yielded_type.value()));
}
else {
final_body = Jakt::types::CheckedMatchBody::Block(checked_block);
}

return JaktInternal::ExplicitValue<Jakt::types::CheckedMatchBody>(final_body.value());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.value;
{
JaktInternal::Optional<Jakt::typechecker::TypeHint> result_type_hint = JaktInternal::OptionalNone();
if (result_type.has_value()){
result_type_hint = Jakt::typechecker::TypeHint::CouldBe(result_type.value());
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_expression = TRY((this->typecheck_expression(expr,scope_id,safety_mode,result_type_hint)));
if (checked_expression->__jakt_init_index() == 25 /* OptionalNone */){
seen_none = true;
}
if (result_type.has_value()){
result_type = TRY((this->choose_broader_type_id(result_type_hint.value().common.init_common.type_id,checked_expression->type(),generic_inferences,span)));
}
else {
result_type = checked_expression->type();
}

TRY((this->check_types_for_compat(result_type.value(),checked_expression->type(),generic_inferences,span)));
return JaktInternal::ExplicitValue<Jakt::types::CheckedMatchBody>(Jakt::types::CheckedMatchBody::Expression(checked_expression));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Tuple{checked_match_body, result_type, seen_none};
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_dictionary(JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const values,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint) {
{
Jakt::ids::StructId const dictionary_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Dictionary"sv))));
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> checked_kv_pairs = DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
Jakt::ids::TypeId key_type_id = Jakt::types::unknown_type_id();
JaktInternal::Optional<Jakt::utility::Span> key_type_span = JaktInternal::OptionalNone();
Jakt::ids::TypeId value_type_id = Jakt::types::unknown_type_id();
JaktInternal::Optional<Jakt::utility::Span> value_type_span = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::ids::TypeId> key_hint = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::ids::TypeId> value_hint = JaktInternal::OptionalNone();
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> type_hint_ids = JaktInternal::OptionalNone();
if (type_hint.has_value()){
type_hint_ids = TRY((this->get_type_ids_from_type_hint_if_struct_ids_match(type_hint.value().common.init_common.type_id,dictionary_struct_id)));
}
if (type_hint_ids.has_value()){
key_hint = type_hint_ids.value().operator[](static_cast<i64>(0LL));
value_hint = type_hint_ids.value().operator[](static_cast<i64>(1LL));
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> _magic = values.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> key__value__ = _magic_value.value();
{
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const jakt__key__value__ = key__value__;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const key = jakt__key__value__.template get<0>();
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const value = jakt__key__value__.template get<1>();

JaktInternal::Optional<Jakt::typechecker::TypeHint> type_hint = JaktInternal::OptionalNone();
if (key_hint.has_value()){
type_hint = Jakt::typechecker::TypeHint::MustBe(key_hint.value());
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_key = TRY((this->typecheck_expression(key,scope_id,safety_mode,type_hint)));
Jakt::ids::TypeId const current_key_type_id = checked_key->type();
if (value_hint.has_value()){
type_hint = Jakt::typechecker::TypeHint::MustBe(value_hint.value());
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_value = TRY((this->typecheck_expression(value,scope_id,safety_mode,type_hint)));
Jakt::ids::TypeId const current_value_type_id = checked_value->type();
Jakt::ids::TypeId const VOID_TYPE_ID = Jakt::types::builtin(Jakt::types::BuiltinType::Void());
if (key_type_id.equals(Jakt::types::unknown_type_id()) && value_type_id.equals(Jakt::types::unknown_type_id())){
if (current_key_type_id.equals(VOID_TYPE_ID)){
this->error(ByteString::from_utf8_without_validation("Can't create a dictionary with keys of type void"sv),key->span());
}
if (current_value_type_id.equals(VOID_TYPE_ID)){
this->error(ByteString::from_utf8_without_validation("Can't create a dictionary with values of type void"sv),value->span());
}
key_type_id = current_key_type_id;
key_type_span = static_cast<JaktInternal::Optional<Jakt::utility::Span>>(key->span());
value_type_id = current_value_type_id;
value_type_span = static_cast<JaktInternal::Optional<Jakt::utility::Span>>(value->span());
}
else {
if (!key_type_id.equals(current_key_type_id)){
ByteString const key_type_name = TRY((this->type_name(key_type_id,false)));
ByteString const current_key_type_name = TRY((this->type_name(current_key_type_id,false)));
this->error_with_hint(__jakt_format(StringView::from_string_literal("Type '{}' does not match type '{}' of previous keys in dictionary"sv),current_key_type_name,key_type_name),key->span(),__jakt_format(StringView::from_string_literal("Dictionary was inferred to store keys of type '{}' here"sv),key_type_name),key_type_span.value());
}
if (!value_type_id.equals(current_value_type_id)){
ByteString const value_type_name = TRY((this->type_name(value_type_id,false)));
ByteString const current_value_type_name = TRY((this->type_name(current_value_type_id,false)));
this->error_with_hint(__jakt_format(StringView::from_string_literal("Type '{}' does not match type '{}' of previous values in dictionary"sv),current_value_type_name,value_type_name),value->span(),__jakt_format(StringView::from_string_literal("Dictionary was inferred to store values of type '{}' here"sv),value_type_name),value_type_span.value());
}
}

checked_kv_pairs.push(Tuple{checked_key, checked_value});
}

}
}

if (key_type_id.equals(Jakt::types::unknown_type_id())){
if (key_hint.has_value()){
key_type_id = key_hint.value();
}
else {
this->error(ByteString::from_utf8_without_validation("Cannot infer key type for Dictionary<K, V>"sv),span);
}

}
if (!key_type_id.equals(Jakt::types::unknown_type_id())){
TRY((this->ensure_type_implements_trait(key_type_id,ByteString::from_utf8_without_validation("Hashable"sv),JaktInternal::OptionalNone(),scope_id,span)));
TRY((this->ensure_type_implements_trait(key_type_id,ByteString::from_utf8_without_validation("Equal"sv),DynamicArray<Jakt::ids::TypeId>::create_with({key_type_id}),scope_id,span)));
}
if (value_type_id.equals(Jakt::types::unknown_type_id())){
if (value_hint.has_value()){
value_type_id = value_hint.value();
}
else {
this->error(ByteString::from_utf8_without_validation("Cannot infer value type for Dictionary"sv),span);
}

}
if (value_hint.has_value()){
value_type_id = TRY((this->choose_broader_type_id(value_type_id,value_hint.value(),this->generic_inferences,span)));
}
if (key_hint.has_value()){
key_type_id = TRY((this->choose_broader_type_id(key_type_id,key_hint.value(),this->generic_inferences,span)));
}
Jakt::ids::TypeId const type_id = this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),dictionary_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({key_type_id, value_type_id})));
return Jakt::types::CheckedExpression::JaktDictionary(JaktInternal::OptionalNone(),checked_kv_pairs,span,type_id,key_type_id,value_type_id);
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::is_scope_directly_accessible_from(Jakt::ids::ScopeId const scope_id,Jakt::ids::ScopeId const from_scope_id) const {
{
return this->program->is_scope_directly_accessible_from(scope_id,from_scope_id,false);
}
}

ErrorOr<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> Jakt::typechecker::Typechecker::resolve_call(Jakt::parser::ParsedCall const call,JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> namespaces,Jakt::utility::Span const span,Jakt::ids::ScopeId const scope_id,bool const must_be_enum_constructor) {
{
Jakt::ids::ScopeId current_scope_id = scope_id;
JaktInternal::DynamicArray<bool> is_base_ns_alias_or_import = DynamicArray<bool>::filled(namespaces.size(), false);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(call.namespace_.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t namespace_index = _magic_value.value();
{
ByteString const scope_name = call.namespace_.operator[](namespace_index);
JaktInternal::Optional<Jakt::ids::StructId> const maybe_struct_scope = TRY((this->find_struct_in_scope(current_scope_id,scope_name,JaktInternal::OptionalNone())));
if (maybe_struct_scope.has_value()){
Jakt::types::CheckedStruct const structure = this->get_struct(maybe_struct_scope.value());
namespaces.operator[](namespace_index).external_name = structure.external_name;
current_scope_id = structure.scope_id;
continue;
}
JaktInternal::Optional<Jakt::ids::EnumId> const maybe_enum_scope = TRY((this->program->find_enum_in_scope(current_scope_id,scope_name,false,JaktInternal::OptionalNone())));
if (maybe_enum_scope.has_value()){
Jakt::types::CheckedEnum const enum_ = this->get_enum(maybe_enum_scope.value());
current_scope_id = enum_.scope_id;
continue;
}
JaktInternal::Optional<Jakt::ids::TypeId> __jakt_tmp364 = this->generic_inferences.find_and_map(scope_name,this->program);
if (__jakt_tmp364.has_value()){
Jakt::ids::TypeId const type_id = __jakt_tmp364.value();
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::DynamicArray<Jakt::ids::FunctionId>>>{
auto&& __jakt_match_variant = *this->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
current_scope_id = this->get_enum(enum_id).scope_id;
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
current_scope_id = this->get_enum(enum_id).scope_id;
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
current_scope_id = this->get_struct(struct_id).scope_id;
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
current_scope_id = this->get_struct(struct_id).scope_id;
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
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
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> const maybe_ns_scope = TRY((this->find_namespace_in_scope(current_scope_id,scope_name,false,JaktInternal::OptionalNone())));
if (maybe_ns_scope.has_value()){
JaktInternal::Tuple<Jakt::ids::ScopeId,bool> const scope_id_is_import_ = maybe_ns_scope.value();
Jakt::ids::ScopeId const scope_id = scope_id_is_import_.template get<0>();
bool const is_import = scope_id_is_import_.template get<1>();

if (is_import){
namespaces.operator[](namespace_index).name = this->program->modules.operator[](scope_id.module_id.id)->name;
}
namespaces.operator[](namespace_index).external_name = this->get_scope(scope_id)->external_name;
is_base_ns_alias_or_import.operator[](namespace_index) = TRY((this->find_namespace_in_scope(current_scope_id,scope_name,true,JaktInternal::OptionalNone()))).value().template get<1>();
current_scope_id = scope_id;
continue;
}
this->error(__jakt_format(StringView::from_string_literal("Not a namespace, enum, class, or struct: ‘{}’"sv),Jakt::utility::join(call.namespace_,ByteString::from_utf8_without_validation("::"sv))),span);
}

}
}

Jakt::ids::ScopeId initial_scope_id = current_scope_id;
JaktInternal::Optional<Jakt::ids::ScopeId> owning_scope = JaktInternal::OptionalNone();
ScopeGuard __jakt_var_96([&] {
{
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> resolved_namespaces = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
{
i64 ns_index = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedNamespace> _magic = namespaces.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedNamespace> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolvedNamespace ns = _magic_value.value();
{
ScopeGuard __jakt_var_97([&] {
ns_index += static_cast<i64>(1LL);
});
if (!is_base_ns_alias_or_import.operator[](ns_index)){
resolved_namespaces.push(ns);
}
}

}
}

}

if (!owning_scope.has_value()){
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> aliased_namespaces = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
for (;;){
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(current_scope_id);
if (scope->alias_path.has_value()){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(scope->alias_path.value().size()),static_cast<size_t>(static_cast<size_t>(0ULL))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
aliased_namespaces.push(scope->alias_path.value().operator[](JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))));
}

}
}

}
else if (scope->namespace_name.has_value()){
aliased_namespaces.push(Jakt::types::ResolvedNamespace(scope->namespace_name.value(),scope->external_name,JaktInternal::OptionalNone()));
}
if (MUST((this->is_scope_directly_accessible_from(current_scope_id,initial_scope_id)))){
break;
}
JaktInternal::Optional<Jakt::ids::ScopeId> const parent = scope->parent;
if (!parent.has_value()){
break;
}
current_scope_id = parent.value();
}
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(aliased_namespaces.size()),static_cast<size_t>(static_cast<size_t>(0ULL))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
resolved_namespaces.push(aliased_namespaces.operator[](JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))));
}

}
}

}
namespaces.shrink(static_cast<size_t>(0ULL));
namespaces.push_values(resolved_namespaces);
}

});
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>> const maybe_var = TRY((this->find_var_in_scope(current_scope_id,call.name,JaktInternal::OptionalNone())));
if (maybe_var.has_value()){
Jakt::ids::TypeId const inner_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<JaktInternal::DynamicArray<Jakt::ids::FunctionId>>>{
auto&& __jakt_match_variant = *this->get_type(maybe_var.value()->type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
default:return JaktInternal::ExplicitValue(maybe_var.value()->type_id);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp365 = this->get_type(inner_type);
if (__jakt_tmp365->__jakt_init_index() == 29 /* Function */){
Jakt::ids::FunctionId const pseudo_function_id = __jakt_tmp365->as.Function.pseudo_function_id;
return DynamicArray<Jakt::ids::FunctionId>::create_with({pseudo_function_id});
}
}
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>> const maybe_overload_set = TRY((this->find_scoped_functions_with_name_in_scope(current_scope_id,call.name,JaktInternal::OptionalNone())));
if (maybe_overload_set.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->get_function(maybe_overload_set.value().template get<0>().operator[](static_cast<i64>(0LL)));
if ((!must_be_enum_constructor) || (function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */)){
owning_scope = function->owner_scope;
current_scope_id = maybe_overload_set.value().template get<1>();
return maybe_overload_set.value().template get<0>();
}
}
if (must_be_enum_constructor){
this->error(__jakt_format(StringView::from_string_literal("No such enum constructor ‘{}’"sv),call.name),span);
return DynamicArray<Jakt::ids::FunctionId>::create_with({});
}
JaktInternal::Optional<Jakt::ids::StructId> const maybe_struct_id = TRY((this->find_struct_in_scope(current_scope_id,call.name,JaktInternal::OptionalNone())));
if (maybe_struct_id.has_value()){
Jakt::ids::StructId const struct_id = maybe_struct_id.value();
Jakt::types::CheckedStruct const structure = this->get_struct(struct_id);
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>> const maybe_function_id = TRY((this->find_scoped_functions_with_name_in_scope(structure.scope_id,structure.name,structure.scope_id)));
if (maybe_function_id.has_value()){
owning_scope = this->get_function(maybe_function_id.value().template get<0>().operator[](static_cast<i64>(0LL)))->owner_scope;
current_scope_id = maybe_function_id.value().template get<1>();
return maybe_function_id.value().template get<0>();
}
}
this->error(__jakt_format(StringView::from_string_literal("Call to unknown function: ‘{}’"sv),call.name),span);
return DynamicArray<Jakt::ids::FunctionId>::create_with({});
}
}

ErrorOr<Jakt::typechecker::FunctionMatchResult> Jakt::typechecker::Typechecker::match_function_and_resolve_args(Jakt::parser::ParsedCall const call,Jakt::ids::ScopeId const caller_scope_id,Jakt::ids::FunctionId const candidate,Jakt::types::SafetyMode const safety_mode,Jakt::utility::Span const span,JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const this_expr) {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> args = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
JaktInternal::Optional<Jakt::ids::TypeId> maybe_this_type_id = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<Jakt::error::JaktError> argument_errors = DynamicArray<Jakt::error::JaktError>::create_with({});
size_t const num_old_compiler_errors = this->compiler->errors.size();
NonnullRefPtr<Jakt::types::CheckedFunction> const callee_candidate = this->get_function(candidate);
Jakt::ids::ScopeId const scope_containing_callee = this->get_scope(callee_candidate->function_scope_id)->parent.value();
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const generic_inference_checkpoint = this->generic_inferences.perform_checkpoint(false);
if (callee_candidate->is_instantiated){
this->generic_inferences.perform_checkpoint(true);
}
ScopeGuard __jakt_var_98([&] {
{
this->generic_inferences.restore(generic_inference_checkpoint);
}

});
if (callee_candidate->type.__jakt_init_index() == 3 /* ImplicitConstructor */){
Jakt::types::CheckedStruct const struct_ = this->get_struct(callee_candidate->struct_id.value());
TRY((this->check_implicit_constructor_argument_access(caller_scope_id,call,struct_)));
}
else {
TRY((this->check_method_access(caller_scope_id,scope_containing_callee,callee_candidate,span)));
}

size_t type_arg_index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = call.type_args.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> parsed_type = _magic_value.value();
{
Jakt::ids::TypeId const checked_type = TRY((this->typecheck_typename(parsed_type,caller_scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if (callee_candidate->generics->params.size() <= type_arg_index){
this->error(ByteString::from_utf8_without_validation("Trying to access generic parameter out of bounds"sv),parsed_type->span());
continue;
}
Jakt::ids::TypeId const typevar_type_id = callee_candidate->generics->params.operator[](type_arg_index).type_id();
if (!typevar_type_id.equals(checked_type)){
this->generic_inferences.set(typevar_type_id,checked_type);
}
type_arg_index += static_cast<size_t>(1ULL);
}

}
}

size_t arg_offset = static_cast<size_t>(0ULL);
if (this_expr.has_value()){
Jakt::ids::TypeId const type_id = this_expr.value()->type();
maybe_this_type_id = type_id;
NonnullRefPtr<typename Jakt::types::Type> const param_type = this->get_type(type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp366 = param_type;
if (__jakt_tmp366->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp366->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp366->as.GenericInstance.args;
Jakt::types::CheckedStruct const structure = this->get_struct(id);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(structure.generic_parameters.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (structure.generic_parameters.operator[](i).type_id.equals(args.operator[](i))){
continue;
}
this->generic_inferences.set(structure.generic_parameters.operator[](i).type_id,args.operator[](i));
}

}
}

}
if (callee_candidate->is_static()){
this->error(ByteString::from_utf8_without_validation("Cannot call static method on an instance of an object"sv),span);
}
else {
arg_offset = static_cast<size_t>(1ULL);
}

if (callee_candidate->is_mutating() && (!this_expr.value()->is_mutable(this->program))){
this->error(ByteString::from_utf8_without_validation("Cannot call mutating method on an immutable object instance"sv),span);
}
}
else if (!callee_candidate->is_static()){
this->error_with_hint(ByteString::from_utf8_without_validation("Cannot call an instance method statically"sv),span,ByteString::from_utf8_without_validation("Add a dot before the method name to call an instance method"sv),span);
}
i64 total_function_specificity = static_cast<i64>(0LL);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const resolved_args = TRY((this->resolve_default_params(callee_candidate->generics->base_params,callee_candidate->has_varargs,call.args,caller_scope_id,safety_mode,arg_offset,span)));
JaktInternal::DynamicArray<Jakt::ids::TypeId> params_to_compare = DynamicArray<Jakt::ids::TypeId>::create_with({});
bool is_specialized_comptime_function = false;
if (callee_candidate->is_comptime){
JaktInternal::Optional<size_t> __jakt_tmp367 = callee_candidate->specialization_index;
if (__jakt_tmp367.has_value()){
size_t const index = __jakt_tmp367.value();
params_to_compare = callee_candidate->generics->specializations.operator[](index);
is_specialized_comptime_function = true;
}
else {
params_to_compare.ensure_capacity(callee_candidate->generics->base_params.size());
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = callee_candidate->generics->base_params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
params_to_compare.push(param.variable->type_id);
}

}
}

}

}
else {
params_to_compare.ensure_capacity(callee_candidate->generics->base_params.size());
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = callee_candidate->generics->base_params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
params_to_compare.push(param.variable->type_id);
}

}
}

}

if (params_to_compare.size() <= JaktInternal::checked_add(resolved_args.size(),arg_offset)){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(JaktInternal::checked_sub(params_to_compare.size(),arg_offset))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const name_span_checked_arg_ = resolved_args.operator[](i);
ByteString const name = name_span_checked_arg_.template get<0>();
Jakt::utility::Span const span = name_span_checked_arg_.template get<1>();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_arg = name_span_checked_arg_.template get<2>();

NonnullRefPtr<typename Jakt::types::Type> const type_to = this->get_type(params_to_compare.operator[](JaktInternal::checked_add(i,arg_offset)));
total_function_specificity += type_to->specificity(this->program,static_cast<i64>(1LL) << static_cast<i64>(31LL));
if (is_specialized_comptime_function){
TRY((this->check_types_for_compat(callee_candidate->generics->base_params.operator[](JaktInternal::checked_add(i,arg_offset)).variable->type_id,checked_arg->type(),this->generic_inferences,checked_arg->span())));
}
TRY((this->check_types_for_compat(params_to_compare.operator[](JaktInternal::checked_add(i,arg_offset)),checked_arg->type(),this->generic_inferences,checked_arg->span())));
args.push(checked_arg);
}

}
}

if ((params_to_compare.size() < JaktInternal::checked_add(resolved_args.size(),arg_offset)) && callee_candidate->has_varargs){
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = resolved_args.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(JaktInternal::checked_sub(params_to_compare.size(),arg_offset)),static_cast<size_t>(9223372036854775807LL)}).iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>> arg = _magic_value.value();
{
args.push(arg.template get<2>());
}

}
}

}
}
size_t const num_match_errors = JaktInternal::checked_sub(this->compiler->errors.size(),num_old_compiler_errors);
if (num_match_errors > static_cast<size_t>(0ULL)){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(num_match_errors)};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t error_index = _magic_value.value();
{
argument_errors.push(this->compiler->errors.pop().value());
}

}
}

return Jakt::typechecker::FunctionMatchResult::MatchError(argument_errors);
}
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const used_inferences = this->generic_inferences.perform_checkpoint(false);
if (is_specialized_comptime_function){
total_function_specificity += static_cast<i64>(1LL);
total_function_specificity *= static_cast<i64>(2LL);
}
return Jakt::typechecker::FunctionMatchResult::MatchSuccess(args,maybe_this_type_id,used_inferences,total_function_specificity);
}
}

ErrorOr<ByteString> Jakt::typechecker::Typechecker::stringify_function_prototype(Jakt::ids::FunctionId const function_id) {
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->get_function(function_id);
ByteStringBuilder builder = ByteStringBuilder::create();
builder.append(StringView::from_string_literal("fn "sv));
builder.append(function->name);
Function<ErrorOr<void>(Jakt::ids::TypeId)> const mapped = [this, &builder](Jakt::ids::TypeId t) -> ErrorOr<void> {{
ByteString const name = TRY((this->type_name(t,false)));
ByteString const mapped_name = TRY((this->type_name(this->generic_inferences.map(t),false)));
builder.append(name);
if ([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(name,mapped_name)){
builder.append(__jakt_format(StringView::from_string_literal(" `{}'"sv),mapped_name));
}
}
return {};
}
;
if (!function->generics->params.is_empty()){
builder.append(StringView::from_string_literal("<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::types::FunctionGenericParameter> _magic = function->generics->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::FunctionGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::FunctionGenericParameter param = _magic_value.value();
{
if (first){
first = false;
}
else {
builder.append(StringView::from_string_literal(", "sv));
}

TRY((mapped(param.type_id())));
}

}
}

builder.append(StringView::from_string_literal(">"sv));
}
builder.append(StringView::from_string_literal("("sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
if (first){
first = false;
}
else {
builder.append(StringView::from_string_literal(", "sv));
}

if (!param.requires_label){
builder.append(StringView::from_string_literal("anon "sv));
}
builder.append(param.variable->name);
builder.append(StringView::from_string_literal(": "sv));
TRY((mapped(param.variable->type_id)));
if (param.default_value_expression.has_value()){
builder.append(StringView::from_string_literal(" = ..."sv));
}
}

}
}

builder.append(StringView::from_string_literal(")"sv));
if (function->can_throw){
builder.append(StringView::from_string_literal(" throws"sv));
}
builder.append(StringView::from_string_literal(" -> "sv));
TRY((mapped(function->return_type_id)));
JaktInternal::Optional<size_t> __jakt_tmp368 = function->specialization_index;
if (__jakt_tmp368.has_value()){
size_t const index = __jakt_tmp368.value();
builder.appendff(ByteString::from_utf8_without_validation(" [specialization {}: <"sv),index);
JaktInternal::DynamicArray<Jakt::ids::TypeId> const type_ids = function->generics->specializations.operator[](index);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(type_ids.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (i != static_cast<size_t>(0ULL)){
builder.append(StringView::from_string_literal(", "sv));
}
TRY((mapped(type_ids.operator[](i))));
}

}
}

builder.append(StringView::from_string_literal(">]"sv));
}
return builder.to_string();
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::typechecker::Typechecker::typecheck_call(Jakt::parser::ParsedCall const call,Jakt::ids::ScopeId const caller_scope_id,Jakt::utility::Span const span,JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const this_expr,JaktInternal::Optional<Jakt::types::StructLikeId> const parent_id,Jakt::types::SafetyMode const safety_mode,JaktInternal::Optional<Jakt::typechecker::TypeHint> type_hint,bool const must_be_enum_constructor) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> args = DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
Jakt::ids::TypeId return_type = Jakt::types::builtin(Jakt::types::BuiltinType::Void());
JaktInternal::DynamicArray<Jakt::ids::TypeId> generic_arguments = DynamicArray<Jakt::ids::TypeId>::create_with({});
bool callee_throws = false;
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> resolved_namespaces = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
JaktInternal::DynamicArray<Jakt::ids::FunctionId> resolved_function_id_candidates = DynamicArray<Jakt::ids::FunctionId>::create_with({});
JaktInternal::Optional<Jakt::ids::FunctionId> resolved_function_id = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::ids::TypeId> maybe_this_type_id = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::ids::FunctionId> generic_checked_function_to_instantiate = JaktInternal::OptionalNone();
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_99([&] {
this->generic_inferences.restore(old_generic_inferences);
});
bool const is_print_like = call.namespace_.is_empty() && ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (call.name);
if ((__jakt_enum_value == ByteString::from_utf8_without_validation("print"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("println"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("eprintln"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("eprint"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("format"sv))) {return JaktInternal::ExplicitValue(true);
}else {return JaktInternal::ExplicitValue(false);
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
{
JaktInternal::ArrayIterator<ByteString> _magic = call.namespace_.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString name = _magic_value.value();
{
resolved_namespaces.push(Jakt::types::ResolvedNamespace(name,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()));
}

}
}

Jakt::ids::ScopeId callee_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (parent_id.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = parent_id.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct struct_ = this->get_struct(id);
Jakt::ids::ScopeId scope_id = struct_.scope_id;
while (resolved_function_id_candidates.is_empty()){
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
resolved_function_id_candidates = TRY((this->resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor)));
this->exit_ignore_error_mode(snapshot);
if (!resolved_function_id_candidates.is_empty()){
break;
}
if (struct_.super_struct_id.has_value()){
Jakt::ids::StructId const parent_struct_id = struct_.super_struct_id.value();
struct_ = this->get_struct(parent_struct_id);
scope_id = struct_.scope_id;
}
else {
this->error(__jakt_format(StringView::from_string_literal("Could not find ‘{}’"sv),call.name),span);
break;
}

}
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(scope_id);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
{
Jakt::ids::ScopeId const scope_id = this->get_enum(id).scope_id;
resolved_function_id_candidates = TRY((this->resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor)));
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(scope_id);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
{
Jakt::ids::ScopeId const scope_id = this->get_trait(id)->scope_id;
resolved_function_id_candidates = TRY((this->resolve_call(call,resolved_namespaces,span,scope_id,must_be_enum_constructor)));
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(scope_id);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}else {{
if (!is_print_like){
resolved_function_id_candidates = TRY((this->resolve_call(call,resolved_namespaces,span,caller_scope_id,must_be_enum_constructor)));
}
return JaktInternal::ExplicitValue<Jakt::ids::ScopeId>(caller_scope_id);
}
VERIFY_NOT_REACHED();
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> generic_inferences_from_parent = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
if (parent_id.has_value() && parent_id.value().common.init_common.generic_arguments.has_value()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const arguments = parent_id.value().common.init_common.generic_arguments.value();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const parameters = parent_id.value().generic_parameters(this->program);
size_t size = arguments.size();
if (size > parameters.size()){
size = parameters.size();
}
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(size)};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
generic_inferences_from_parent.set(parameters.operator[](i),arguments.operator[](i));
this->generic_inferences.set(parameters.operator[](i),arguments.operator[](i));
}

}
}

}
if (is_print_like){
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> _magic = call.args.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> arg = _magic_value.value();
{
JaktInternal::Optional<Jakt::typechecker::TypeHint> const type_hint = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::typechecker::TypeHint>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (first);
if (__jakt_enum_value) {{
first = false;
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::typechecker::TypeHint>>(static_cast<JaktInternal::Optional<Jakt::typechecker::TypeHint>>(Jakt::typechecker::TypeHint::MustBe(TRY((this->prelude_struct_type_named(ByteString::from_utf8_without_validation("StringView"sv)))))));
}
VERIFY_NOT_REACHED();
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_arg = TRY((this->typecheck_expression(arg.template get<2>(),caller_scope_id,safety_mode,type_hint)));
args.push(Tuple{call.name, checked_arg});
}

}
}

if (call.name == ByteString::from_utf8_without_validation("format"sv)){
return_type = TRY((this->prelude_struct_type_named(ByteString::from_utf8_without_validation("String"sv))));
}
}
else {
i64 max_found_specificity = -static_cast<i64>(1LL);
JaktInternal::DynamicArray<Jakt::error::JaktError> errors_while_trying_to_find_matching_function = DynamicArray<Jakt::error::JaktError>::create_with({});
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> generic_inferences_for_best_match = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = resolved_function_id_candidates.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId candidate = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = TRY((this->match_function_and_resolve_args(call,caller_scope_id,candidate,safety_mode,span,this_expr)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* MatchSuccess */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MatchSuccess;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& resolved_args = __jakt_match_value.args;
JaktInternal::Optional<Jakt::ids::TypeId> const& resolved_this_type_id = __jakt_match_value.maybe_this_type_id;
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const& used_generic_inferences = __jakt_match_value.used_generic_inferences;
i64 const& specificity = __jakt_match_value.specificity;
{
if (specificity > max_found_specificity){
resolved_function_id = candidate;
maybe_this_type_id = resolved_this_type_id;
max_found_specificity = specificity;
generic_inferences_for_best_match = used_generic_inferences;
args = DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = resolved_args.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> resolved_arg = _magic_value.value();
{
args.push(Tuple{call.name, resolved_arg});
}

}
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* MatchError */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MatchError;JaktInternal::DynamicArray<Jakt::error::JaktError> const& errors = __jakt_match_value.errors;
{
{
JaktInternal::ArrayIterator<Jakt::error::JaktError> _magic = errors.iterator();
for (;;){
JaktInternal::Optional<Jakt::error::JaktError> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::error::JaktError error = _magic_value.value();
{
errors_while_trying_to_find_matching_function.push(error);
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

if (!resolved_function_id.has_value()){
if (!resolved_function_id_candidates.is_empty()){
this->error(ByteString::from_utf8_without_validation("No function with matching signature found."sv),span);
{
JaktInternal::ArrayIterator<Jakt::error::JaktError> _magic = errors_while_trying_to_find_matching_function.iterator();
for (;;){
JaktInternal::Optional<Jakt::error::JaktError> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::error::JaktError match_error = _magic_value.value();
{
this->error(match_error);
}

}
}

{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = resolved_function_id_candidates.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId candidate = _magic_value.value();
{
this->error(__jakt_format(StringView::from_string_literal("Candidate: {}"sv),TRY((this->stringify_function_prototype(candidate)))),span);
}

}
}

}
JaktInternal::DynamicArray<Jakt::ids::TypeId> checked_type_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedType>> _magic = call.type_args.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedType>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedType> type_arg = _magic_value.value();
{
checked_type_args.push(TRY((this->typecheck_typename(type_arg,caller_scope_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
}

}
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> _magic = call.args.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> arg = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_arg = TRY((this->typecheck_expression(arg.template get<2>(),caller_scope_id,safety_mode,JaktInternal::OptionalNone())));
args.push(Tuple{call.name, checked_arg});
}

}
}

return Jakt::types::CheckedExpression::Call(this->generic_inferences.perform_checkpoint(false),Jakt::types::CheckedCall(resolved_namespaces,call.name,args,checked_type_args,JaktInternal::OptionalNone(),Jakt::types::builtin(Jakt::types::BuiltinType::Unknown()),callee_throws,JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default()),span,Jakt::types::builtin(Jakt::types::BuiltinType::Unknown()));
}
this->generic_inferences.restore(generic_inferences_for_best_match);
this->generic_inferences.set_from(generic_inferences_from_parent);
NonnullRefPtr<Jakt::types::CheckedFunction> const callee = this->get_function(resolved_function_id.value());
callee_throws = callee->can_throw;
return_type = callee->return_type_id;
if (callee->is_unsafe && (safety_mode.__jakt_init_index() == 0 /* Safe */)){
this->error(ByteString::from_utf8_without_validation("Cannot call unsafe function in safe context"sv),span);
}
if (type_hint.has_value() && (!type_hint.value().common.init_common.type_id.equals(Jakt::types::unknown_type_id()))){
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_100([&] {
this->exit_ignore_error_mode(snapshot);
});
TRY((this->check_types_for_compat(return_type,type_hint.value(),this->generic_inferences,span)));
}
return_type = TRY((this->substitute_typevars_in_type(return_type,this->generic_inferences)));
if (type_hint.has_value() && (!type_hint.value().common.init_common.type_id.equals(Jakt::types::unknown_type_id()))){
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(callee->is_instantiated);
ScopeGuard __jakt_var_101([&] {
this->exit_ignore_error_mode(snapshot);
});
TRY((this->check_types_for_compat(type_hint.value(),return_type,this->generic_inferences,span)));
}
{
JaktInternal::ArrayIterator<Jakt::types::FunctionGenericParameter> _magic = callee->generics->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::FunctionGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::FunctionGenericParameter generic_typevar = _magic_value.value();
{
if (generic_typevar.kind.__jakt_init_index() == 1 /* Parameter */){
JaktInternal::Optional<Jakt::ids::TypeId> const substitution = this->generic_inferences.get(generic_typevar.type_id());
if (substitution.has_value()){
generic_arguments.push(substitution.value());
}
else if (!this->in_comptime_function_call){
this->error(ByteString::from_utf8_without_validation("Not all generic parameters have known types"sv),span);
}
else {
generic_arguments.push(generic_typevar.type_id());
}

}
}

}
}

if ((!callee->is_instantiated) || ((!(callee->linkage.__jakt_init_index() == 1 /* External */)) && (!callee->generics->is_specialized_for_types(generic_arguments)))){
generic_checked_function_to_instantiate = static_cast<JaktInternal::Optional<Jakt::ids::FunctionId>>(resolved_function_id.value());
}
else if (callee->is_instantiated){
if (type_hint.has_value() && (!type_hint.value().common.init_common.type_id.equals(Jakt::types::unknown_type_id()))){
TRY((this->check_types_for_compat(type_hint.value(),return_type,this->generic_inferences,span)));
}
}
}

return_type = TRY((this->substitute_typevars_in_type(return_type,this->generic_inferences)));
if (callee_throws && (!this->get_scope(caller_scope_id)->can_throw)){
this->error(ByteString::from_utf8_without_validation("Call to function that may throw needs to be in a try statement or a function marked as throws"sv),span);
}
if (generic_checked_function_to_instantiate.has_value()){
if (maybe_this_type_id.has_value()){
maybe_this_type_id = TRY((this->substitute_typevars_in_type(maybe_this_type_id.value(),this->generic_inferences)));
}
resolved_function_id = TRY((this->typecheck_and_specialize_generic_function(generic_checked_function_to_instantiate.value(),generic_arguments,callee_scope_id,maybe_this_type_id,this->generic_inferences,call.type_args,span,args)));
}
if (this->dump_try_hints && callee_throws){
this->dump_try_hint(span);
}
JaktInternal::Optional<Jakt::parser::ExternalName> const external_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::parser::ExternalName>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (resolved_function_id.has_value());
if (__jakt_enum_value) {{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->get_function(resolved_function_id.value());
if (function->deprecated_message.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Call to deprecated function: {}"sv),function->deprecated_message.value()),span);
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::parser::ExternalName>>(function->external_name);
}
VERIFY_NOT_REACHED();
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (resolved_function_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->get_function(resolved_function_id.value());
if (function->stores_arguments.has_value()){
JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>> const argument_behaviour = function->stores_arguments.value();
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>> _magic = argument_behaviour.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel> index__level__ = _magic_value.value();
{
JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel> const jakt__index__level__ = index__level__;
size_t const index = jakt__index__level__.template get<0>();
Jakt::parser::ArgumentStoreLevel const level = jakt__index__level__.template get<1>();

Function<ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(size_t)> const resolve_arg = [&args, &this_expr, &function](size_t index) -> ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> {{
if (function->is_static()){
return args.operator[](index).template get<1>();
}
if (index == static_cast<size_t>(0ULL)){
return this_expr.value();
}
return args.operator[](JaktInternal::checked_sub(index,static_cast<size_t>(1ULL))).template get<1>();
}
}
;
JaktInternal::Optional<Jakt::ids::ScopeId> const arg_scope_id = TRY((this->required_scope_id_in_hierarchy_for(TRY((resolve_arg(index))),caller_scope_id))).template get<0>();
JaktInternal::Optional<Jakt::ids::ScopeId> const stored_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ids::ScopeId>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = level;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* InStaticStorage */:return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::ids::ScopeId>>(this->root_scope_id()));
case 0 /* InObject */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InObject;size_t const& argument_index = __jakt_match_value.argument_index;
return JaktInternal::ExplicitValue(TRY((this->required_scope_id_in_hierarchy_for(TRY((resolve_arg(argument_index))),caller_scope_id))).template get<0>());
};/*case end*/
case 1 /* InReturnValue */:return JaktInternal::ExplicitValue(caller_scope_id);
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
if (this->scope_lifetime_subsumes(stored_scope_id,arg_scope_id)){
this->error(ByteString::from_utf8_without_validation("Cannot pass this argument by reference, it is not guaranteed to outlive the object it will be stored in"sv),TRY((resolve_arg(index)))->span());
}
}

}
}

}
}
Jakt::parser::InlineState const force_inline = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::parser::InlineState,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>> {
auto __jakt_enum_value = (resolved_function_id.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(this->get_function(resolved_function_id.value())->force_inline);
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::parser::InlineState::Default());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::CheckedCall const function_call = Jakt::types::CheckedCall(resolved_namespaces,call.name,args,generic_arguments,resolved_function_id,return_type,callee_throws,external_name,force_inline);
NonnullRefPtr<typename Jakt::types::CheckedExpression> const checked_call = Jakt::types::CheckedExpression::Call(this->generic_inferences.perform_checkpoint(false),function_call,span,return_type);
bool const in_comptime_function = this->current_function_id.has_value() && this->get_function(this->current_function_id.value())->is_comptime;
if ((!in_comptime_function) && (resolved_function_id.has_value() && this->get_function(resolved_function_id.value())->is_comptime)){
NonnullRefPtr<Jakt::types::CheckedFunction> const resolved_function = this->get_function(resolved_function_id.value());
NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter = this->interpreter();
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(generic_checked_function_to_instantiate.value_or_lazy_evaluated([&] { return resolved_function_id.value(); }));
JaktInternal::DynamicArray<Jakt::types::Value> call_args = DynamicArray<Jakt::types::Value>::create_with({});
JaktInternal::Optional<Jakt::types::Value> this_argument = JaktInternal::OptionalNone();
NonnullRefPtr<Jakt::interpreter::InterpreterScope> eval_scope = Jakt::interpreter::InterpreterScope::from_runtime_scope(caller_scope_id,this->program,JaktInternal::OptionalNone());
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,Jakt::ids::TypeId> _magic = this->generic_inferences.iterator().iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> entry = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> const key_value_ = entry;
Jakt::ids::TypeId const key = key_value_.template get<0>();
Jakt::ids::TypeId const value = key_value_.template get<1>();

eval_scope->type_bindings.set(key,value);
}

}
}

if (this_expr.has_value()){
auto __jakt_var_102 = [&]() -> ErrorOr<void> {
{
Jakt::interpreter::StatementResult const evaluated_this = TRY((interpreter->execute_expression(this_expr.value(),eval_scope)));
Jakt::interpreter::StatementResult __jakt_tmp369 = evaluated_this;
Jakt::interpreter::StatementResult __jakt_tmp370 = evaluated_this;
if (__jakt_tmp369.__jakt_init_index() == 5 /* JustValue */){
Jakt::types::Value const value = __jakt_tmp369.as.JustValue.value;
this_argument = value;
}
else if (__jakt_tmp370.__jakt_init_index() == 1 /* Throw */){
Jakt::types::Value const value = __jakt_tmp370.as.Throw.value;
this->error(__jakt_format(StringView::from_string_literal("Error executing this expression (evaluation threw {})"sv),value),this_expr.value()->span());
}
else {
this->error(ByteString::from_utf8_without_validation("Invalid this expression"sv),this_expr.value()->span());
}

}

;
return ErrorOr<void> {};}();
if (__jakt_var_102.is_error()) {{
this->error(ByteString::from_utf8_without_validation("Error executing this expression"sv),this_expr.value()->span());
}
};
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = args.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> argument = _magic_value.value();
{
Jakt::interpreter::StatementResult const value = ({ Optional<Jakt::interpreter::StatementResult> __jakt_var_103;
auto __jakt_var_104 = [&]() -> ErrorOr<Jakt::interpreter::StatementResult> { return interpreter->execute_expression(argument.template get<1>(),eval_scope); }();
if (__jakt_var_104.is_error()) {{
this->error(ByteString::from_utf8_without_validation("Error in argument"sv),span);
continue;
}
} else {__jakt_var_103 = __jakt_var_104.release_value();
}
__jakt_var_103.release_value(); });
Jakt::interpreter::StatementResult __jakt_tmp371 = value;
if (__jakt_tmp371.__jakt_init_index() == 1 /* Throw */){
Jakt::types::Value const err = __jakt_tmp371.as.Throw.value;
this->error(TRY((Jakt::types::comptime_format_impl(ByteString::from_utf8_without_validation("Compiletime call failed: {}"sv),DynamicArray<Jakt::types::Value>::create_with({err}).operator[](JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}),this->program))),argument.template get<1>()->span());
break;
}
Jakt::types::Value const evaluated_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = value;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default:{
return Error::from_errno(static_cast<i32>(69));
}
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
call_args.push(evaluated_value);
}

}
}

JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> type_bindings = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(resolved_function->generics->params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::FunctionGenericParameter const param = resolved_function->generics->params.operator[](i);
if (function_call.type_args.size() <= i){
this->error(__jakt_format(StringView::from_string_literal("Missing type argument for generic parameter {}"sv),i),span);
break;
}
type_bindings.set(param.type_id(),function_call.type_args.operator[](i));
}

}
}

JaktInternal::Optional<Jakt::interpreter::ExecutionResult> result = JaktInternal::OptionalNone();
NonnullRefPtr<Jakt::interpreter::InterpreterScope> invocation_scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),eval_scope,type_bindings,this->compiler,caller_scope_id);
auto __jakt_var_105 = [&]() -> ErrorOr<void> {
{
result = TRY((interpreter->execute(resolved_function_id.value(),resolved_namespaces,this_argument,call_args,span,invocation_scope,false)));
}

;
return ErrorOr<void> {};}();
if (__jakt_var_105.is_error()) {auto error = __jakt_var_105.release_error();
{
this->error(__jakt_format(StringView::from_string_literal("Compiletime call failed: {}"sv),error),span);
return checked_call;
}
};
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = result.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::interpreter::value_to_checked_expression(x,interpreter))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& x = __jakt_match_value.value;
{
this->error(TRY((Jakt::types::comptime_format_impl(ByteString::from_utf8_without_validation("Compiletime call failed: {}"sv),DynamicArray<Jakt::types::Value>::create_with({x}).operator[](JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}),this->program))),x.span);
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(checked_call);
}
VERIFY_NOT_REACHED();
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

ErrorOr<void> Jakt::typechecker::Typechecker::check_implicit_constructor_argument_access(Jakt::ids::ScopeId const caller_scope_id,Jakt::parser::ParsedCall const call,Jakt::types::CheckedStruct const struct_) {
{
if (this->scope_can_access(caller_scope_id,struct_.scope_id)){
return {};
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> _magic = call.args.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> arg = _magic_value.value();
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = struct_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->get_variable(field->variable_id);
ByteString const name = this->get_argument_name(arg);
if ((variable->name == name) && (variable->visibility.__jakt_init_index() == 1 /* Private */)){
this->error(__jakt_format(StringView::from_string_literal("Can't access field '{}' when calling implicit constructor of '{}' because it is marked private"sv),variable->name,struct_.name),arg.template get<1>());
return {};
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

ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>> Jakt::typechecker::Typechecker::resolve_default_params(JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const params,bool const has_varargs,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const args,Jakt::ids::ScopeId const scope_id,Jakt::types::SafetyMode const safety_mode,size_t const arg_offset,Jakt::utility::Span const span) {
{
size_t params_with_default_value = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
if (param.default_value_expression.has_value()){
params_with_default_value++;
}
}

}
}

size_t const max_number_of_valid_arguments = JaktInternal::checked_sub(params.size(),arg_offset);
size_t const min_number_of_valid_arguments = JaktInternal::checked_sub(max_number_of_valid_arguments,params_with_default_value);
if ((args.size() >= min_number_of_valid_arguments) && ((args.size() <= max_number_of_valid_arguments) || has_varargs)){
size_t consumed_arg = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> resolved_args = DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
JaktInternal::Dictionary<size_t,JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,ByteString>>> invalid_considered_argument_uses = Dictionary<size_t, JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,ByteString>>>::create_with_entries({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(arg_offset),static_cast<size_t>(params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::CheckedParameter const param = params.operator[](i);
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> maybe_checked_expr = JaktInternal::OptionalNone();
if (!param.requires_label){
if (args.size() <= consumed_arg){
if (!param.default_value_expression.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Missing argument for function parameter {}"sv),param.variable->name),span);
continue;
}
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> __jakt_tmp372 = param.default_value_expression;
if (__jakt_tmp372.has_value()){
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId> const default_value = __jakt_tmp372.value();
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId> const expression_default_scope_id_ = default_value;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expression = expression_default_scope_id_.template get<0>();
Jakt::ids::ScopeId const default_scope_id = expression_default_scope_id_.template get<1>();

scope->resolution_mixins.push(Jakt::types::ResolutionMixin(default_scope_id,true,true,true,true,true,true,true,true,true));
ScopeGuard __jakt_var_106([&] {
scope->resolution_mixins.pop();
});
maybe_checked_expr = TRY((this->typecheck_expression(expression,scope_id,safety_mode,Jakt::typechecker::TypeHint::MustBe(param.variable->type_id))));
}
}
else {
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const name_span_expr_ = args.operator[](consumed_arg);
ByteString const name = name_span_expr_.template get<0>();
Jakt::utility::Span const span = name_span_expr_.template get<1>();
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr = name_span_expr_.template get<2>();

if ((!name.is_empty()) && [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(name,param.variable->name)){
this->error(__jakt_format(StringView::from_string_literal("Wrong parameter name in argument label (got '{}', expected '{}')"sv),name,param.variable->name),span);
}
maybe_checked_expr = TRY((this->typecheck_expression(expr,scope_id,safety_mode,Jakt::typechecker::TypeHint::MustBe(param.variable->type_id))));
consumed_arg++;
}

}
else {
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> __jakt_tmp373 = param.default_value_expression;
if (__jakt_tmp373.has_value()){
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId> const default_value = __jakt_tmp373.value();
NonnullRefPtr<Jakt::types::Scope> scope = this->get_scope(scope_id);
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId> const expression_default_scope_id_ = default_value;
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expression = expression_default_scope_id_.template get<0>();
Jakt::ids::ScopeId const default_scope_id = expression_default_scope_id_.template get<1>();

scope->resolution_mixins.push(Jakt::types::ResolutionMixin(default_scope_id,true,true,true,true,true,true,true,true,true));
ScopeGuard __jakt_var_107([&] {
scope->resolution_mixins.pop();
});
maybe_checked_expr = TRY((this->typecheck_expression(expression,scope_id,safety_mode,Jakt::typechecker::TypeHint::MustBe(param.variable->type_id))));
}
if (args.size() > consumed_arg){
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const name_span_expr_ = args.operator[](consumed_arg);
ByteString const name = name_span_expr_.template get<0>();
Jakt::utility::Span const span = name_span_expr_.template get<1>();
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr = name_span_expr_.template get<2>();

if (this->validate_argument_label(param,name,span,expr,maybe_checked_expr)){
maybe_checked_expr = TRY((this->typecheck_expression(expr,scope_id,safety_mode,Jakt::typechecker::TypeHint::MustBe(param.variable->type_id))));
consumed_arg++;
}
else {
ByteString const reason = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>>> {
auto __jakt_enum_value = (name.is_empty());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(__jakt_format(StringView::from_string_literal("Missing argument label (expected '{}:')"sv),param.variable->name));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(__jakt_format(StringView::from_string_literal("Wrong parameter name in argument label (got '{}', expected '{}')"sv),name,param.variable->name));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
if (!invalid_considered_argument_uses.contains(consumed_arg)){
invalid_considered_argument_uses.set(consumed_arg, DynamicArray<JaktInternal::Tuple<size_t,ByteString>>::create_with({}));
}
invalid_considered_argument_uses.operator[](consumed_arg).push(Tuple{i, reason});
}

}
else {
if (!param.default_value_expression.has_value()){
this->error(__jakt_format(StringView::from_string_literal("Missing argument for function parameter '{}'"sv),param.variable->name),span);
continue;
}
}

}

if (maybe_checked_expr.has_value()){
NonnullRefPtr<typename Jakt::types::CheckedExpression> checked_arg = maybe_checked_expr.value();
resolved_args.push(Tuple{param.variable->name, span, checked_arg});
}
}

}
}

if (!has_varargs){
while (consumed_arg < args.size()){
ScopeGuard __jakt_var_108([&] {
consumed_arg += static_cast<size_t>(1ULL);
});
if (invalid_considered_argument_uses.contains(consumed_arg)){
JaktInternal::Tuple<size_t,ByteString> const last_invalid_use = invalid_considered_argument_uses.operator[](consumed_arg).last().value();
this->error_with_hint(ByteString::from_utf8_without_validation("Invalid argument not used in call"sv),args.operator[](consumed_arg).template get<1>(),__jakt_format(StringView::from_string_literal("{} position{} considered for the argument, final rejection reason was: {}"sv),invalid_considered_argument_uses.operator[](consumed_arg).size(),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>>> {
auto __jakt_enum_value = (invalid_considered_argument_uses.operator[](consumed_arg).size());
if (__jakt_enum_value == static_cast<size_t>(1ULL)) {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation(""sv));
}else {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("s"sv));
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
}),last_invalid_use.template get<1>()),params.operator[](last_invalid_use.template get<0>()).variable->definition_span);
}
}
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> _magic = args.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(consumed_arg),static_cast<size_t>(9223372036854775807LL)}).iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> name__span__expr__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const jakt__name__span__expr__ = name__span__expr__;
ByteString const name = jakt__name__span__expr__.template get<0>();
Jakt::utility::Span const span = jakt__name__span__expr__.template get<1>();
NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr = jakt__name__span__expr__.template get<2>();

resolved_args.push(Tuple{name, span, TRY((this->typecheck_expression(expr,scope_id,safety_mode,JaktInternal::OptionalNone())))});
}

}
}

return resolved_args;
}
else {
this->error(ByteString::from_utf8_without_validation("Wrong number of arguments"sv),span);
return DynamicArray<JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
}

}
}

ErrorOr<Jakt::ids::TypeId> Jakt::typechecker::Typechecker::resolve_type_var(Jakt::ids::TypeId const type_var_type_id,Jakt::ids::ScopeId const scope_id) const {
{
Jakt::ids::TypeId current_type_id = type_var_type_id;
for (;;){
current_type_id = this->generic_inferences.map(current_type_id);
NonnullRefPtr<typename Jakt::types::Type> const type_var_type = this->get_type(current_type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp374 = type_var_type;
if (__jakt_tmp374->__jakt_init_index() == 18 /* TypeVariable */){
ByteString const type_name = __jakt_tmp374->as.TypeVariable.name;
JaktInternal::Optional<Jakt::ids::TypeId> const maybe_found_type_id = TRY((this->find_type_in_scope(scope_id,type_name)));
if (maybe_found_type_id.has_value()){
Jakt::ids::TypeId const found_type_id = maybe_found_type_id.value();
if (found_type_id.equals(current_type_id)){
return current_type_id;
}
current_type_id = found_type_id;
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

bool Jakt::typechecker::Typechecker::validate_argument_label(Jakt::types::CheckedParameter const param,ByteString const label,Jakt::utility::Span const span,NonnullRefPtr<typename Jakt::parser::ParsedExpression> const expr,JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const default_value) {
{
ByteString const name = this->get_argument_name(Tuple{label, span, expr});
if (name == param.variable->name){
return true;
}
if (!default_value.has_value()){
if (label.is_empty()){
this->error(__jakt_format(StringView::from_string_literal("Missing argument label (expected '{}:')"sv),param.variable->name),expr->span());
}
else {
this->error(__jakt_format(StringView::from_string_literal("Wrong parameter name in argument label (got '{}', expected '{}')"sv),label,param.variable->name),span);
}

}
return false;
}
}

ByteString Jakt::typechecker::Typechecker::get_argument_name(JaktInternal::Tuple<ByteString,Jakt::utility::Span,NonnullRefPtr<typename Jakt::parser::ParsedExpression>> const arg) const {
{
if (!arg.template get<0>().is_empty()){
return arg.template get<0>();
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ByteString>{
auto&& __jakt_match_variant = *arg.template get<2>();
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;ByteString const& name = __jakt_match_value.name;
{
return name;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::parser::ParsedExpression> const& expr = __jakt_match_value.expr;
Jakt::parser::UnaryOperator const& op = __jakt_match_value.op;
{
if (((op.__jakt_init_index() == 7 /* Reference */) || (op.__jakt_init_index() == 8 /* MutableReference */)) || (op.__jakt_init_index() == 5 /* Dereference */)){
NonnullRefPtr<typename Jakt::parser::ParsedExpression> __jakt_tmp375 = expr;
if (__jakt_tmp375->__jakt_init_index() == 9 /* Var */){
ByteString const name = __jakt_tmp375->as.Var.name;
return name;
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return ByteString::from_utf8_without_validation(""sv);
}
}

ErrorOr<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>> Jakt::typechecker::Typechecker::find_all_implementations_of_trait(Jakt::ids::TypeId const type_id,Jakt::ids::TraitId const trait_id,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const filter_for_generics) {
{
Function<ErrorOr<bool>(JaktInternal::DynamicArray<Jakt::ids::TypeId>)> const generics_match = [this, &filter_for_generics, &trait_id](JaktInternal::DynamicArray<Jakt::ids::TypeId> generics) -> ErrorOr<bool> {{
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = this->generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_109([&] {
this->generic_inferences.restore(old_generic_inferences);
});
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> __jakt_tmp376 = filter_for_generics;
if (__jakt_tmp376.has_value()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generics_to_match = __jakt_tmp376.value();
if (generics.size() >= generics_to_match.size()){
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_110([&] {
this->exit_ignore_error_mode(snapshot);
});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(generics_to_match.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::ids::TypeId const generic = generics.operator[](i);
Jakt::ids::TypeId const generic_to_match = generics_to_match.operator[](i);
if (!TRY((this->check_types_for_compat(generic,generic_to_match,this->generic_inferences,Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL)))))){
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
return true;
}

}
}
;
NonnullRefPtr<typename Jakt::types::Type> type = this->get_type(type_id);
if (type->is_builtin()){
type = this->get_type(this->get_struct(this->program->builtin_implementation_struct(type->as_builtin_type(),this->program->prelude_module_id())).type_id);
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>, ErrorOr<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
Jakt::types::CheckedStruct const struct_ = this->get_struct(struct_id);
this->generic_inferences.set_all(struct_.generic_parameters,args);
JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> implementations = DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> _magic = struct_.trait_implementations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> ___trait_descriptors__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const jakt_____trait_descriptors__ = ___trait_descriptors__;
ByteString const _ = jakt_____trait_descriptors__.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const trait_descriptors = jakt_____trait_descriptors__.template get<1>();

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> _magic = trait_descriptors.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> trait_descriptor = _magic_value.value();
{
if (trait_descriptor.template get<0>().equals(trait_id) && TRY((generics_match(trait_descriptor.template get<1>())))){
implementations.push(trait_descriptor.template get<1>());
}
}

}
}

}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>>(implementations);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedStruct const struct_ = this->get_struct(struct_id);
this->generic_inferences.set_all(struct_.generic_parameters,args);
JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> implementations = DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> _magic = struct_.trait_implementations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> ___trait_descriptors__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const jakt_____trait_descriptors__ = ___trait_descriptors__;
ByteString const _ = jakt_____trait_descriptors__.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const trait_descriptors = jakt_____trait_descriptors__.template get<1>();

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> _magic = trait_descriptors.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> trait_descriptor = _magic_value.value();
{
if (trait_descriptor.template get<0>().equals(trait_id) && TRY((generics_match(trait_descriptor.template get<1>())))){
implementations.push(trait_descriptor.template get<1>());
}
}

}
}

}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>>(implementations);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> implementations = DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> _magic = enum_.trait_implementations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> ___trait_descriptors__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const jakt_____trait_descriptors__ = ___trait_descriptors__;
ByteString const _ = jakt_____trait_descriptors__.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const trait_descriptors = jakt_____trait_descriptors__.template get<1>();

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> _magic = trait_descriptors.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> trait_descriptor = _magic_value.value();
{
if (trait_descriptor.template get<0>().equals(trait_id) && TRY((generics_match(trait_descriptor.template get<1>())))){
implementations.push(trait_descriptor.template get<1>());
}
}

}
}

}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>>(implementations);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> implementations = DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> _magic = enum_.trait_implementations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> ___trait_descriptors__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const jakt_____trait_descriptors__ = ___trait_descriptors__;
ByteString const _ = jakt_____trait_descriptors__.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const trait_descriptors = jakt_____trait_descriptors__.template get<1>();

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> _magic = trait_descriptors.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> trait_descriptor = _magic_value.value();
{
if (trait_descriptor.template get<0>().equals(trait_id) && TRY((generics_match(trait_descriptor.template get<1>())))){
implementations.push(trait_descriptor.template get<1>());
}
}

}
}

}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>>(implementations);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
{
if (id.equals(trait_id) && TRY((generics_match(DynamicArray<Jakt::ids::TypeId>::create_with({}))))){
return DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({DynamicArray<Jakt::ids::TypeId>::create_with({})});
}
return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>>(DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if ((!id.equals(trait_id)) || (!TRY((generics_match(args))))){
return DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({});
}
return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>>(DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({args}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return JaktInternal::ExplicitValue(DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({}));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::implements_trait(Jakt::ids::TypeId const type_id,Jakt::ids::TraitId const trait_id,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const generic_arguments) {
{
Jakt::utility::Span const empty_span = Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL));
Function<ErrorOr<bool>(JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>, Jakt::ids::TraitId, JaktInternal::DynamicArray<Jakt::ids::TypeId>, Jakt::typechecker::Typechecker&)> const has_matching_trait = [type_id, empty_span](JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> trait_implementations, Jakt::ids::TraitId trait_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> passed_generic_arguments, Jakt::typechecker::Typechecker& typechecker) -> ErrorOr<bool> {{
JaktInternal::Tuple<bool,bool> const snapshot = typechecker.enter_ignore_error_mode(true);
ScopeGuard __jakt_var_111([&] {
typechecker.exit_ignore_error_mode(snapshot);
});
bool found = false;
{
JaktInternal::ArrayIterator<JaktInternal::DynamicArray<Jakt::ids::TypeId>> _magic = trait_implementations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::DynamicArray<Jakt::ids::TypeId> implemented_generic_arguments = _magic_value.value();
{
if (implemented_generic_arguments.size() != passed_generic_arguments.size()){
continue;
}
bool ok = false;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(implemented_generic_arguments.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
ok = TRY((typechecker.check_types_for_compat(implemented_generic_arguments.operator[](i),passed_generic_arguments.operator[](i),typechecker.generic_inferences,empty_span)));
if (!ok){
break;
}
}

}
}

if (!ok){
continue;
}
found = true;
break;
}

}
}

return found;
}
}
;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<bool>>{
auto&& __jakt_match_variant = this->get_trait(trait_id)->requirements;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* ComptimeExpression */:{
JaktInternal::Tuple<bool,bool> const snapshot = this->enter_ignore_error_mode(true);
ScopeGuard __jakt_var_112([&] {
this->exit_ignore_error_mode(snapshot);
});
TRY((this->check_type_argument_requirements(type_id,DynamicArray<Jakt::ids::TraitId>::create_with({trait_id}),empty_span,Jakt::ids::ScopeId(this->current_module_id,static_cast<size_t>(1ULL)))));
return !this->had_an_error;
}
return JaktInternal::ExplicitValue<void>();
default:{
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::ids::TypeId> const empty = DynamicArray<Jakt::ids::TypeId>::create_with({});
return has_matching_trait(TRY((this->find_all_implementations_of_trait(type_id,trait_id,JaktInternal::OptionalNone()))),trait_id,generic_arguments.value_or_lazy_evaluated([&] { return empty; }),*this);
}
}

ErrorOr<JaktInternal::Tuple<bool,JaktInternal::DynamicArray<Jakt::error::JaktError>>> Jakt::typechecker::Typechecker::signatures_match(Jakt::ids::TypeId const self_type_id,NonnullRefPtr<Jakt::types::CheckedFunction> const first,NonnullRefPtr<Jakt::types::CheckedFunction> const second) {
{
size_t const starting_error_count = this->compiler->errors.size();
Function<ErrorOr<bool>(Jakt::typechecker::Typechecker&, Jakt::ids::TypeId, Jakt::ids::TypeId)> const types_match = [self_type_id](Jakt::typechecker::Typechecker& typechecker, Jakt::ids::TypeId a, Jakt::ids::TypeId b) -> ErrorOr<bool> {{
Jakt::ids::TypeId const mapped_a = typechecker.generic_inferences.map(a);
Jakt::ids::TypeId const mapped_b = typechecker.generic_inferences.map(b);
if (mapped_a.equals(mapped_b)){
return true;
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *typechecker.get_type(mapped_a);
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((typechecker.implements_trait(mapped_b,id,JaktInternal::OptionalNone()))));
};/*case end*/
case 30 /* Self */:return JaktInternal::ExplicitValue(TRY((typechecker.check_types_for_compat(self_type_id,mapped_b,typechecker.generic_inferences,Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))))));
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((typechecker.implements_trait(mapped_b,id,args))));
};/*case end*/
default:return JaktInternal::ExplicitValue(TRY((typechecker.check_types_for_compat(mapped_a,mapped_b,typechecker.generic_inferences,Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))))));
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
bool const result = TRY((this->signatures_match_impl(self_type_id,first,second,types_match)));
JaktInternal::DynamicArray<Jakt::error::JaktError> const errors = this->compiler->errors.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(starting_error_count),static_cast<size_t>(9223372036854775807LL)}).to_array();
this->compiler->errors = this->compiler->errors.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(starting_error_count)}).to_array();
return Tuple{result, errors};
}
}

ErrorOr<bool> Jakt::typechecker::Typechecker::signatures_match_impl(Jakt::ids::TypeId const self_type_id,NonnullRefPtr<Jakt::types::CheckedFunction> const first,NonnullRefPtr<Jakt::types::CheckedFunction> const second,Function<ErrorOr<bool>(Jakt::typechecker::Typechecker&, Jakt::ids::TypeId, Jakt::ids::TypeId)> const& types_match) {
{
if (TRY((types_match(*this,first->return_type_id,second->return_type_id)))){
if (first->can_throw == second->can_throw){
if (first->params.size() == second->params.size()){
size_t arg_start = static_cast<size_t>(0ULL);
if (first->is_static()){
if (second->is_static()){
}
else {
this->error(ByteString::from_utf8_without_validation("Function signatures don't match: one is static and the other isn't"sv),first->name_span);
return false;
}

}
else {
if (!second->is_static()){
if (first->is_mutating() == second->is_mutating()){
arg_start = static_cast<size_t>(1ULL);
}
else {
this->error(ByteString::from_utf8_without_validation("Function signatures don't match: one is mutating and the other isn't"sv),first->name_span);
return false;
}

}
else {
this->error(ByteString::from_utf8_without_validation("Function signatures don't match: one is static and the other isn't"sv),first->name_span);
return false;
}

}

{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(arg_start),static_cast<size_t>(first->params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (TRY((types_match(*this,first->params.operator[](i).variable->type_id,second->params.operator[](i).variable->type_id)))){
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
this->error(ByteString::from_utf8_without_validation("Function signatures don't match: different number of parameters"sv),first->name_span);
return false;
}

}
else {
this->error(ByteString::from_utf8_without_validation("Function signatures don't match: one can throw and the other can't"sv),first->name_span);
return false;
}

}
else {
return false;
}

}
}

Jakt::typechecker::Typechecker::Typechecker(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, NonnullRefPtr<Jakt::types::CheckedProgram> a_program, Jakt::ids::ModuleId a_current_module_id, JaktInternal::Optional<Jakt::ids::TypeId> a_current_struct_type_id, JaktInternal::Optional<Jakt::ids::FunctionId> a_current_function_id, Jakt::typechecker::BreakContinueLegalityTracker a_break_continue_tracker, Jakt::typechecker::ReturnLegalityTracker a_return_tracker, bool a_ignore_errors, bool a_dump_type_hints, bool a_dump_try_hints, u64 a_lambda_count, Jakt::types::GenericInferences a_generic_inferences, JaktInternal::Optional<Jakt::ids::TypeId> a_self_type_id, ByteString a_root_module_name, bool a_in_comptime_function_call, bool a_had_an_error, JaktInternal::Dictionary<ByteString,Jakt::ids::ScopeId> a_cpp_import_cache, JaktInternal::Optional<Jakt::cpp_import__none::CppImportProcessor> a_cpp_import_processor, u64 a_temp_var_count, Jakt::types::CheckedBlock a_current_block): compiler(move(a_compiler)), program(move(a_program)), current_module_id(move(a_current_module_id)), current_struct_type_id(move(a_current_struct_type_id)), current_function_id(move(a_current_function_id)), break_continue_tracker(move(a_break_continue_tracker)), return_tracker(move(a_return_tracker)), ignore_errors(move(a_ignore_errors)), dump_type_hints(move(a_dump_type_hints)), dump_try_hints(move(a_dump_try_hints)), lambda_count(move(a_lambda_count)), generic_inferences(move(a_generic_inferences)), self_type_id(move(a_self_type_id)), root_module_name(move(a_root_module_name)), in_comptime_function_call(move(a_in_comptime_function_call)), had_an_error(move(a_had_an_error)), cpp_import_cache(move(a_cpp_import_cache)), cpp_import_processor(move(a_cpp_import_processor)), temp_var_count(move(a_temp_var_count)), current_block(move(a_current_block)){}

ByteString Jakt::typechecker::AlreadyImplementedFor::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("AlreadyImplementedFor("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_name: \"{}\", ", trait_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("encounter_span: {}", encounter_span);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::typechecker::AlreadyImplementedFor::AlreadyImplementedFor(ByteString a_trait_name, Jakt::utility::Span a_encounter_span): trait_name(move(a_trait_name)), encounter_span(move(a_encounter_span)){}

ByteString Jakt::typechecker::TraitImplCheck::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("TraitImplCheck("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("missing_methods: {}, ", missing_methods);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("unmatched_signatures: {}, ", unmatched_signatures);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("private_matching_methods: {}, ", private_matching_methods);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("already_implemented_for: {}", already_implemented_for);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::typechecker::TraitImplCheck Jakt::typechecker::TraitImplCheck::make() {
{
return Jakt::typechecker::TraitImplCheck(Dictionary<Jakt::ids::TypeId, JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>>::create_with_entries({}),Dictionary<Jakt::ids::TypeId, JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::error::JaktError>>>>::create_with_entries({}),Dictionary<Jakt::ids::TypeId, JaktInternal::Dictionary<ByteString,Jakt::utility::Span>>::create_with_entries({}),Dictionary<ByteString, Jakt::typechecker::AlreadyImplementedFor>::create_with_entries({}));
}
}

void Jakt::typechecker::TraitImplCheck::ensure_capacity(size_t const count) {
{
this->missing_methods.ensure_capacity(count);
this->unmatched_signatures.ensure_capacity(count);
this->private_matching_methods.ensure_capacity(count);
this->already_implemented_for.ensure_capacity(count);
}
}

void Jakt::typechecker::TraitImplCheck::register_trait(Jakt::ids::TypeId const trait_type_id,ByteString const trait_name,Jakt::types::CheckedTraitRequirements const requirements) {
{
Jakt::types::CheckedTraitRequirements __jakt_tmp377 = requirements;
if (__jakt_tmp377.__jakt_init_index() == 1 /* Methods */){
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const trait_methods = __jakt_tmp377.as.Methods.value;
this->private_matching_methods.set(trait_type_id, Dictionary<ByteString, Jakt::utility::Span>::create_with_entries({}));
this->unmatched_signatures.set(trait_type_id, Dictionary<ByteString, JaktInternal::Tuple<Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::error::JaktError>>>::create_with_entries({}));
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> missing_methods = Dictionary<ByteString, Jakt::ids::FunctionId>::create_with_entries({});
missing_methods.ensure_capacity(trait_methods.size());
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::FunctionId> _magic = trait_methods.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> method_name__method_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> const jakt__method_name__method_id__ = method_name__method_id__;
ByteString const method_name = jakt__method_name__method_id__.template get<0>();
Jakt::ids::FunctionId const method_id = jakt__method_name__method_id__.template get<1>();

missing_methods.set(method_name,method_id);
}

}
}

this->missing_methods.set(trait_type_id,missing_methods);
}
else {
return;
}

}
}

ErrorOr<void> Jakt::typechecker::TraitImplCheck::throw_errors(Jakt::utility::Span const record_decl_span,Jakt::typechecker::Typechecker& typechecker) {
{
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> _magic = this->missing_methods.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> trait_type_id__missing_methods__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> const jakt__trait_type_id__missing_methods__ = trait_type_id__missing_methods__;
Jakt::ids::TypeId const trait_type_id = jakt__trait_type_id__missing_methods__.template get<0>();
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const missing_methods = jakt__trait_type_id__missing_methods__.template get<1>();

JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const trait_id_trait_generic_arguments_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>, ErrorOr<void>>{
auto&& __jakt_match_variant = *typechecker.get_type(trait_type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& trait_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Tuple{trait_id, args});
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& trait_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
return JaktInternal::ExplicitValue(Tuple{trait_id, args});
};/*case end*/
default:{
Jakt::abort();
}
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
Jakt::ids::TraitId const trait_id = trait_id_trait_generic_arguments_.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const trait_generic_arguments = trait_id_trait_generic_arguments_.template get<1>();

ByteString const trait_name = typechecker.get_trait(trait_id)->name;
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::error::JaktError>>> const unmatched_signatures = this->unmatched_signatures.operator[](trait_type_id);
JaktInternal::Dictionary<ByteString,Jakt::utility::Span> const private_matching_methods = this->private_matching_methods.operator[](trait_type_id);
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::FunctionId> _magic = missing_methods.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> method_name__trait_method_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::FunctionId> const jakt__method_name__trait_method_id__ = method_name__trait_method_id__;
ByteString const method_name = jakt__method_name__trait_method_id__.template get<0>();
Jakt::ids::FunctionId const trait_method_id = jakt__method_name__trait_method_id__.template get<1>();

JaktInternal::Optional<Jakt::typechecker::AlreadyImplementedFor> const already_implemented_for = this->already_implemented_for.get(method_name);
JaktInternal::Optional<JaktInternal::Tuple<Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::error::JaktError>>> const unmatched_signature = unmatched_signatures.get(method_name);
JaktInternal::Optional<Jakt::utility::Span> const private_matching_method = private_matching_methods.get(method_name);
if (already_implemented_for.has_value()){
typechecker.error(__jakt_format(StringView::from_string_literal("Cannot implement ‘{}’ for ‘{}’ because it's already implementing ‘{}’"sv),method_name,trait_name,already_implemented_for.value().trait_name),already_implemented_for.value().encounter_span);
}
else if (private_matching_method.has_value()){
Jakt::utility::Span const span = private_matching_method.value();
typechecker.error_with_hint(__jakt_format(StringView::from_string_literal("Implementation of ‘{}’ for trait ‘{}’ is valid but is not public"sv),method_name,trait_name),span,ByteString::from_utf8_without_validation("Consider adding ‘public’ to make the method accessible"sv),span);
}
else {
NonnullRefPtr<Jakt::types::CheckedFunction> const func = typechecker.get_function(trait_method_id);
if (!func->block.statements.is_empty()){
continue;
}
if (unmatched_signature.has_value()){
JaktInternal::Tuple<Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::error::JaktError>> const method_span_errors_ = unmatched_signature.value();
Jakt::utility::Span const method_span = method_span_errors_.template get<0>();
JaktInternal::DynamicArray<Jakt::error::JaktError> const errors = method_span_errors_.template get<1>();

typechecker.error_with_hint(__jakt_format(StringView::from_string_literal("Missing implementation for method ‘{}’ of trait ‘{}’ on type ‘{}’"sv),method_name,trait_name,TRY((typechecker.type_name(trait_type_id,false)))),record_decl_span,ByteString::from_utf8_without_validation("The method is declared here, but its signature doesn't match"sv),method_span);
typechecker.compiler->errors.push_values(errors);
}
else {
Jakt::utility::Span const trait_method_span = typechecker.get_function(trait_method_id)->name_span;
typechecker.error_with_hint(__jakt_format(StringView::from_string_literal("Missing implementation for method ‘{}’ of trait ‘{}’"sv),method_name,trait_name),record_decl_span,ByteString::from_utf8_without_validation("Consider implementing the method with the signature specified here"sv),trait_method_span);
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

ErrorOr<void> Jakt::typechecker::TraitImplCheck::register_method(Jakt::ids::TypeId const self_type_id,ByteString const method_name,Jakt::ids::FunctionId const method_id,Jakt::typechecker::Typechecker& typechecker) {
{
NonnullRefPtr<Jakt::types::CheckedFunction> const method = typechecker.get_function(method_id);
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> _magic = this->missing_methods.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> trait_type_id__methods__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> const jakt__trait_type_id__methods__ = trait_type_id__methods__;
Jakt::ids::TypeId const trait_type_id = jakt__trait_type_id__methods__.template get<0>();
JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> const methods = jakt__trait_type_id__methods__.template get<1>();

JaktInternal::Optional<Jakt::ids::FunctionId> const trait_method_id = methods.get(method_name);
if (trait_method_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const trait_method = typechecker.get_function(trait_method_id.value());
JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const trait_id_trait_generic_arguments_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>, ErrorOr<void>>{
auto&& __jakt_match_variant = *typechecker.get_type(trait_type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& trait_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Tuple{trait_id, args});
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& trait_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
return JaktInternal::ExplicitValue(Tuple{trait_id, args});
};/*case end*/
default:{
Jakt::abort();
}
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
Jakt::ids::TraitId const trait_id = trait_id_trait_generic_arguments_.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const trait_generic_arguments = trait_id_trait_generic_arguments_.template get<1>();

NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = typechecker.get_trait(trait_id);
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const old_generic_inferences = typechecker.generic_inferences.perform_checkpoint(false);
ScopeGuard __jakt_var_113([&] {
typechecker.generic_inferences.restore(old_generic_inferences);
});
if (trait_->generic_parameters.size() == trait_generic_arguments.size()){
typechecker.generic_inferences.set_all(trait_->generic_parameters,trait_generic_arguments);
JaktInternal::Tuple<bool,JaktInternal::DynamicArray<Jakt::error::JaktError>> const matches_errors_ = TRY((typechecker.signatures_match(self_type_id,trait_method,method)));
bool const matches = matches_errors_.template get<0>();
JaktInternal::DynamicArray<Jakt::error::JaktError> const errors = matches_errors_.template get<1>();

if (matches){
if (method->visibility.__jakt_init_index() == 0 /* Public */){
this->missing_methods.operator[](trait_type_id).remove(method_name);
this->already_implemented_for.set(method_name, Jakt::typechecker::AlreadyImplementedFor(trait_->name,method->name_span));
break;
}
else {
this->private_matching_methods.operator[](trait_type_id).set(method_name,method->name_span);
continue;
}

}
else {
this->unmatched_signatures.operator[](trait_type_id).set(method_name,Tuple{method->name_span, errors});
continue;
}

}
else {
this->unmatched_signatures.operator[](trait_type_id).set(method_name,Tuple{method->name_span, DynamicArray<Jakt::error::JaktError>::create_with({Jakt::error::JaktError::Message(__jakt_format(StringView::from_string_literal("Expected {} generic arguments, but got {}"sv),trait_->generic_parameters.size(),trait_generic_arguments.size()),method->name_span)})});
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

Jakt::typechecker::TraitImplCheck::TraitImplCheck(JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId>> a_missing_methods, JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::utility::Span,JaktInternal::DynamicArray<Jakt::error::JaktError>>>> a_unmatched_signatures, JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::Dictionary<ByteString,Jakt::utility::Span>> a_private_matching_methods, JaktInternal::Dictionary<ByteString,Jakt::typechecker::AlreadyImplementedFor> a_already_implemented_for): missing_methods(move(a_missing_methods)), unmatched_signatures(move(a_unmatched_signatures)), private_matching_methods(move(a_private_matching_methods)), already_implemented_for(move(a_already_implemented_for)){}

ByteString Jakt::typechecker::FunctionMatchResult::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* MatchSuccess */: {
builder.append("FunctionMatchResult::MatchSuccess"sv);
[[maybe_unused]] auto const& that = this->as.MatchSuccess;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}, ", that.args);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("maybe_this_type_id: {}, ", that.maybe_this_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("used_generic_inferences: {}, ", that.used_generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("specificity: {}", that.specificity);
}
builder.append(")"sv);
break;}
case 1 /* MatchError */: {
builder.append("FunctionMatchResult::MatchError"sv);
[[maybe_unused]] auto const& that = this->as.MatchError;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("errors: {}", that.errors);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] FunctionMatchResult FunctionMatchResult::MatchSuccess(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> args, JaktInternal::Optional<Jakt::ids::TypeId> maybe_this_type_id, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> used_generic_inferences, i64 specificity){
FunctionMatchResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.MatchSuccess.args) (decltype(args))(move(args));
new (&__jakt_uninit_enum.as.MatchSuccess.maybe_this_type_id) (decltype(maybe_this_type_id))(move(maybe_this_type_id));
new (&__jakt_uninit_enum.as.MatchSuccess.used_generic_inferences) (decltype(used_generic_inferences))(move(used_generic_inferences));
new (&__jakt_uninit_enum.as.MatchSuccess.specificity) (decltype(specificity))(move(specificity));
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionMatchResult FunctionMatchResult::MatchError(JaktInternal::DynamicArray<Jakt::error::JaktError> errors){
FunctionMatchResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.MatchError.errors) (decltype(errors))(move(errors));
return __jakt_uninit_enum;
}
FunctionMatchResult& FunctionMatchResult::operator=(FunctionMatchResult const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* MatchSuccess */:
new (&this->as.MatchSuccess.args) (decltype(this->as.MatchSuccess.args))(rhs.as.MatchSuccess.args);
new (&this->as.MatchSuccess.maybe_this_type_id) (decltype(this->as.MatchSuccess.maybe_this_type_id))(rhs.as.MatchSuccess.maybe_this_type_id);
new (&this->as.MatchSuccess.used_generic_inferences) (decltype(this->as.MatchSuccess.used_generic_inferences))(rhs.as.MatchSuccess.used_generic_inferences);
new (&this->as.MatchSuccess.specificity) (decltype(this->as.MatchSuccess.specificity))(rhs.as.MatchSuccess.specificity);
break;
case 1 /* MatchError */:
new (&this->as.MatchError.errors) (decltype(this->as.MatchError.errors))(rhs.as.MatchError.errors);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* MatchSuccess */:
this->as.MatchSuccess.args = rhs.as.MatchSuccess.args;
this->as.MatchSuccess.maybe_this_type_id = rhs.as.MatchSuccess.maybe_this_type_id;
this->as.MatchSuccess.used_generic_inferences = rhs.as.MatchSuccess.used_generic_inferences;
this->as.MatchSuccess.specificity = rhs.as.MatchSuccess.specificity;
break;
case 1 /* MatchError */:
this->as.MatchError.errors = rhs.as.MatchError.errors;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
FunctionMatchResult::FunctionMatchResult(FunctionMatchResult const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* MatchSuccess */:
new (&this->as.MatchSuccess.args) (decltype(this->as.MatchSuccess.args))(rhs.as.MatchSuccess.args);
new (&this->as.MatchSuccess.maybe_this_type_id) (decltype(this->as.MatchSuccess.maybe_this_type_id))(rhs.as.MatchSuccess.maybe_this_type_id);
new (&this->as.MatchSuccess.used_generic_inferences) (decltype(this->as.MatchSuccess.used_generic_inferences))(rhs.as.MatchSuccess.used_generic_inferences);
new (&this->as.MatchSuccess.specificity) (decltype(this->as.MatchSuccess.specificity))(rhs.as.MatchSuccess.specificity);
break;
case 1 /* MatchError */:
new (&this->as.MatchError.errors) (decltype(this->as.MatchError.errors))(rhs.as.MatchError.errors);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
FunctionMatchResult& FunctionMatchResult::operator=(FunctionMatchResult &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* MatchSuccess */:
new (&this->as.MatchSuccess.args) (decltype(this->as.MatchSuccess.args))(move(rhs.as.MatchSuccess.args));
new (&this->as.MatchSuccess.maybe_this_type_id) (decltype(this->as.MatchSuccess.maybe_this_type_id))(move(rhs.as.MatchSuccess.maybe_this_type_id));
new (&this->as.MatchSuccess.used_generic_inferences) (decltype(this->as.MatchSuccess.used_generic_inferences))(move(rhs.as.MatchSuccess.used_generic_inferences));
new (&this->as.MatchSuccess.specificity) (decltype(this->as.MatchSuccess.specificity))(move(rhs.as.MatchSuccess.specificity));
break;
case 1 /* MatchError */:
new (&this->as.MatchError.errors) (decltype(this->as.MatchError.errors))(move(rhs.as.MatchError.errors));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* MatchSuccess */:
this->as.MatchSuccess.args = move(rhs.as.MatchSuccess.args);
this->as.MatchSuccess.maybe_this_type_id = move(rhs.as.MatchSuccess.maybe_this_type_id);
this->as.MatchSuccess.used_generic_inferences = move(rhs.as.MatchSuccess.used_generic_inferences);
this->as.MatchSuccess.specificity = move(rhs.as.MatchSuccess.specificity);
break;
case 1 /* MatchError */:
this->as.MatchError.errors = move(rhs.as.MatchError.errors);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
FunctionMatchResult::FunctionMatchResult(FunctionMatchResult &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* MatchSuccess */:
new (&this->as.MatchSuccess.args) (decltype(this->as.MatchSuccess.args))(move(rhs.as.MatchSuccess.args));
new (&this->as.MatchSuccess.maybe_this_type_id) (decltype(this->as.MatchSuccess.maybe_this_type_id))(move(rhs.as.MatchSuccess.maybe_this_type_id));
new (&this->as.MatchSuccess.used_generic_inferences) (decltype(this->as.MatchSuccess.used_generic_inferences))(move(rhs.as.MatchSuccess.used_generic_inferences));
new (&this->as.MatchSuccess.specificity) (decltype(this->as.MatchSuccess.specificity))(move(rhs.as.MatchSuccess.specificity));
break;
case 1 /* MatchError */:
new (&this->as.MatchError.errors) (decltype(this->as.MatchError.errors))(move(rhs.as.MatchError.errors));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
FunctionMatchResult::~FunctionMatchResult(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void FunctionMatchResult::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* MatchSuccess */:this->as.MatchSuccess.args.~DynamicArray();
this->as.MatchSuccess.maybe_this_type_id.~Optional();
this->as.MatchSuccess.used_generic_inferences.~Dictionary();
break;
case 1 /* MatchError */:this->as.MatchError.errors.~DynamicArray();
break;
}
}
ByteString Jakt::typechecker::TypeHint::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* MustBe */: {
return ByteString("TypeHint::MustBe"sv);
break;}
case 1 /* CouldBe */: {
return ByteString("TypeHint::CouldBe"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] TypeHint TypeHint::MustBe(Jakt::ids::TypeId type_id){
TypeHint __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] TypeHint TypeHint::CouldBe(Jakt::ids::TypeId type_id){
TypeHint __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
TypeHint& TypeHint::operator=(TypeHint const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.type_id = rhs.common.init_common.type_id;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* MustBe */:
break;
case 1 /* CouldBe */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* MustBe */:
break;
case 1 /* CouldBe */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
TypeHint::TypeHint(TypeHint const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.type_id) (decltype(this->common.init_common.type_id))(rhs.common.init_common.type_id);
switch (rhs.__jakt_init_index()) {
case 0 /* MustBe */:
break;
case 1 /* CouldBe */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
TypeHint& TypeHint::operator=(TypeHint &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.type_id = move(rhs.common.init_common.type_id);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* MustBe */:
break;
case 1 /* CouldBe */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* MustBe */:
break;
case 1 /* CouldBe */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
TypeHint::TypeHint(TypeHint &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.type_id) (decltype(this->common.init_common.type_id))(move(rhs.common.init_common.type_id));
switch (rhs.__jakt_init_index()) {
case 0 /* MustBe */:
break;
case 1 /* CouldBe */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
TypeHint::~TypeHint(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.type_id.~TypeId();
this->__jakt_destroy_variant(); }
void TypeHint::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* MustBe */:break;
case 1 /* CouldBe */:break;
}
}
ByteString Jakt::typechecker::BreakContinueLegalityTracker::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* None */: {
return ByteString("BreakContinueLegalityTracker::None"sv);
break;}
case 1 /* AnyLoop */: {
return ByteString("BreakContinueLegalityTracker::AnyLoop"sv);
break;}
case 2 /* Defer */: {
return ByteString("BreakContinueLegalityTracker::Defer"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] BreakContinueLegalityTracker BreakContinueLegalityTracker::None(){
BreakContinueLegalityTracker __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] BreakContinueLegalityTracker BreakContinueLegalityTracker::AnyLoop(){
BreakContinueLegalityTracker __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] BreakContinueLegalityTracker BreakContinueLegalityTracker::Defer(){
BreakContinueLegalityTracker __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
BreakContinueLegalityTracker& BreakContinueLegalityTracker::operator=(BreakContinueLegalityTracker const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* AnyLoop */:
break;
case 2 /* Defer */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* AnyLoop */:
break;
case 2 /* Defer */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BreakContinueLegalityTracker::BreakContinueLegalityTracker(BreakContinueLegalityTracker const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* AnyLoop */:
break;
case 2 /* Defer */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
BreakContinueLegalityTracker& BreakContinueLegalityTracker::operator=(BreakContinueLegalityTracker &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* AnyLoop */:
break;
case 2 /* Defer */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* AnyLoop */:
break;
case 2 /* Defer */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BreakContinueLegalityTracker::BreakContinueLegalityTracker(BreakContinueLegalityTracker &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* AnyLoop */:
break;
case 2 /* Defer */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
BreakContinueLegalityTracker::~BreakContinueLegalityTracker(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void BreakContinueLegalityTracker::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* None */:break;
case 1 /* AnyLoop */:break;
case 2 /* Defer */:break;
}
}
ByteString Jakt::typechecker::ReturnLegalityTracker::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* None */: {
return ByteString("ReturnLegalityTracker::None"sv);
break;}
case 1 /* Lambda */: {
return ByteString("ReturnLegalityTracker::Lambda"sv);
break;}
case 2 /* Defer */: {
return ByteString("ReturnLegalityTracker::Defer"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] ReturnLegalityTracker ReturnLegalityTracker::None(){
ReturnLegalityTracker __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] ReturnLegalityTracker ReturnLegalityTracker::Lambda(){
ReturnLegalityTracker __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] ReturnLegalityTracker ReturnLegalityTracker::Defer(){
ReturnLegalityTracker __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
ReturnLegalityTracker& ReturnLegalityTracker::operator=(ReturnLegalityTracker const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Lambda */:
break;
case 2 /* Defer */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Lambda */:
break;
case 2 /* Defer */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ReturnLegalityTracker::ReturnLegalityTracker(ReturnLegalityTracker const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Lambda */:
break;
case 2 /* Defer */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ReturnLegalityTracker& ReturnLegalityTracker::operator=(ReturnLegalityTracker &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Lambda */:
break;
case 2 /* Defer */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Lambda */:
break;
case 2 /* Defer */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ReturnLegalityTracker::ReturnLegalityTracker(ReturnLegalityTracker &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* None */:
break;
case 1 /* Lambda */:
break;
case 2 /* Defer */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ReturnLegalityTracker::~ReturnLegalityTracker(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ReturnLegalityTracker::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* None */:break;
case 1 /* Lambda */:break;
case 2 /* Defer */:break;
}
}
ByteString Jakt::typechecker::NumericOrStringValue::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* StringValue */: {
builder.append("NumericOrStringValue::StringValue"sv);
[[maybe_unused]] auto const& that = this->as.StringValue;
builder.appendff("(\"{}\")", that.value);
break;}
case 1 /* SignedNumericValue */: {
builder.append("NumericOrStringValue::SignedNumericValue"sv);
[[maybe_unused]] auto const& that = this->as.SignedNumericValue;
builder.appendff("({})", that.value);
break;}
case 2 /* UnsignedNumericValue */: {
builder.append("NumericOrStringValue::UnsignedNumericValue"sv);
[[maybe_unused]] auto const& that = this->as.UnsignedNumericValue;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] NumericOrStringValue NumericOrStringValue::StringValue(ByteString value){
NumericOrStringValue __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.StringValue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericOrStringValue NumericOrStringValue::SignedNumericValue(i64 value){
NumericOrStringValue __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.SignedNumericValue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumericOrStringValue NumericOrStringValue::UnsignedNumericValue(u64 value){
NumericOrStringValue __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.UnsignedNumericValue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
NumericOrStringValue& NumericOrStringValue::operator=(NumericOrStringValue const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* StringValue */:
new (&this->as.StringValue.value) (decltype(this->as.StringValue.value))(rhs.as.StringValue.value);
break;
case 1 /* SignedNumericValue */:
new (&this->as.SignedNumericValue.value) (decltype(this->as.SignedNumericValue.value))(rhs.as.SignedNumericValue.value);
break;
case 2 /* UnsignedNumericValue */:
new (&this->as.UnsignedNumericValue.value) (decltype(this->as.UnsignedNumericValue.value))(rhs.as.UnsignedNumericValue.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* StringValue */:
this->as.StringValue.value = rhs.as.StringValue.value;
break;
case 1 /* SignedNumericValue */:
this->as.SignedNumericValue.value = rhs.as.SignedNumericValue.value;
break;
case 2 /* UnsignedNumericValue */:
this->as.UnsignedNumericValue.value = rhs.as.UnsignedNumericValue.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
NumericOrStringValue::NumericOrStringValue(NumericOrStringValue const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* StringValue */:
new (&this->as.StringValue.value) (decltype(this->as.StringValue.value))(rhs.as.StringValue.value);
break;
case 1 /* SignedNumericValue */:
new (&this->as.SignedNumericValue.value) (decltype(this->as.SignedNumericValue.value))(rhs.as.SignedNumericValue.value);
break;
case 2 /* UnsignedNumericValue */:
new (&this->as.UnsignedNumericValue.value) (decltype(this->as.UnsignedNumericValue.value))(rhs.as.UnsignedNumericValue.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
NumericOrStringValue& NumericOrStringValue::operator=(NumericOrStringValue &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* StringValue */:
new (&this->as.StringValue.value) (decltype(this->as.StringValue.value))(move(rhs.as.StringValue.value));
break;
case 1 /* SignedNumericValue */:
new (&this->as.SignedNumericValue.value) (decltype(this->as.SignedNumericValue.value))(move(rhs.as.SignedNumericValue.value));
break;
case 2 /* UnsignedNumericValue */:
new (&this->as.UnsignedNumericValue.value) (decltype(this->as.UnsignedNumericValue.value))(move(rhs.as.UnsignedNumericValue.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* StringValue */:
this->as.StringValue.value = move(rhs.as.StringValue.value);
break;
case 1 /* SignedNumericValue */:
this->as.SignedNumericValue.value = move(rhs.as.SignedNumericValue.value);
break;
case 2 /* UnsignedNumericValue */:
this->as.UnsignedNumericValue.value = move(rhs.as.UnsignedNumericValue.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
NumericOrStringValue::NumericOrStringValue(NumericOrStringValue &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* StringValue */:
new (&this->as.StringValue.value) (decltype(this->as.StringValue.value))(move(rhs.as.StringValue.value));
break;
case 1 /* SignedNumericValue */:
new (&this->as.SignedNumericValue.value) (decltype(this->as.SignedNumericValue.value))(move(rhs.as.SignedNumericValue.value));
break;
case 2 /* UnsignedNumericValue */:
new (&this->as.UnsignedNumericValue.value) (decltype(this->as.UnsignedNumericValue.value))(move(rhs.as.UnsignedNumericValue.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
NumericOrStringValue::~NumericOrStringValue(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void NumericOrStringValue::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* StringValue */:this->as.StringValue.value.~ByteString();
break;
case 1 /* SignedNumericValue */:break;
case 2 /* UnsignedNumericValue */:break;
}
}
}
} // namespace Jakt
