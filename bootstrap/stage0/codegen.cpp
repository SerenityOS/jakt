#include "codegen.h"
namespace Jakt {
namespace codegen {
bool are_loop_exits_allowed(codegen::AllowedControlExits const allowed_control_exits) {
{
return (((allowed_control_exits).index() == 2 /* AtLoop */));
}
}

bool is_return_allowed(codegen::AllowedControlExits const allowed_control_exits) {
{
return ((!(((allowed_control_exits).index() == 0 /* Nothing */))));
}
}

ErrorOr<String> codegen::LineSpan::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("LineSpan("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("start: "));TRY(builder.appendff("{}, ", start));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("end: "));TRY(builder.appendff("{}", end));
}
TRY(builder.append(")"));return builder.to_string(); }
codegen::LineSpan::LineSpan(size_t a_start, size_t a_end) :start(a_start), end(a_end){}

ErrorOr<String> codegen::CodegenDebugInfo::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("CodegenDebugInfo("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("compiler: "));TRY(builder.appendff("{}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("line_spans: "));TRY(builder.appendff("{}, ", line_spans));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("statement_span_comments: "));TRY(builder.appendff("{}", statement_span_comments));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<void> codegen::CodegenDebugInfo::gather_line_spans() {
{
{
JaktInternal::DictionaryIterator<String,utility::FileId> _magic = ((((((*this).compiler))->file_ids)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,utility::FileId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,utility::FileId> file = (_magic_value.value());
{
if ((((file).get<0>()) == String("__prelude__"))){
continue;
}
((((*this).compiler))->set_current_file(((file).get<1>())));
size_t const file_idx = ((((file).get<1>())).id);
JaktInternal::Array<codegen::LineSpan> const empty_array = (TRY((Array<codegen::LineSpan>::create_with({}))));
TRY((((((*this).line_spans)).set(file_idx,empty_array))));
size_t idx = static_cast<size_t>(0ULL);
size_t start = idx;
while ((idx < ((((((*this).compiler))->current_file_contents)).size()))){
if ((((((((*this).compiler))->current_file_contents))[idx]) == '\n')){
TRY((((((((*this).line_spans))[file_idx])).push(codegen::LineSpan(start,idx)))));
(start = (JaktInternal::checked_add<size_t>(idx,static_cast<size_t>(1ULL))));
}
({auto& _jakt_ref = idx;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
if ((start < idx)){
TRY((((((((*this).line_spans))[file_idx])).push(codegen::LineSpan(start,idx)))));
}
}

}
}

}
return {};
}

ErrorOr<String> codegen::CodegenDebugInfo::span_to_source_location(utility::Span const span) {
{
if (((((*this).line_spans)).is_empty())){
TRY((((*this).gather_line_spans())));
}
size_t const file_idx = ((((span).file_id)).id);
if ((!(((((*this).line_spans)).contains(file_idx))))){
return (String(""));
}
size_t line_index = static_cast<size_t>(0ULL);
while ((line_index < ((((((*this).line_spans))[file_idx])).size()))){
if (((((span).start) >= ((((((((*this).line_spans))[file_idx]))[line_index])).start)) && (((span).start) <= ((((((((*this).line_spans))[file_idx]))[line_index])).end)))){
size_t const column_index = (JaktInternal::checked_sub<size_t>(((span).start),((((((((*this).line_spans))[file_idx]))[line_index])).start)));
return (TRY((String::formatted(String("{} \"{}\""),(JaktInternal::checked_add<size_t>(line_index,static_cast<size_t>(1ULL))),(((TRY((((((*this).compiler))->get_file_path(((span).file_id))))).value())).to_string())))));
}
({auto& _jakt_ref = line_index;_jakt_ref = JaktInternal::checked_add<size_t>(_jakt_ref, static_cast<size_t>(1ULL));});
}
utility::panic(String("Reached end of file and could not find index"));
}
}

codegen::CodegenDebugInfo::CodegenDebugInfo(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Dictionary<size_t,JaktInternal::Array<codegen::LineSpan>> a_line_spans, bool a_statement_span_comments) :compiler(a_compiler), line_spans(a_line_spans), statement_span_comments(a_statement_span_comments){}

ErrorOr<String> codegen::CodeGenerator::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("CodeGenerator("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("compiler: "));TRY(builder.appendff("{}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("program: "));TRY(builder.appendff("{}, ", *program));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("control_flow_state: "));TRY(builder.appendff("{}, ", control_flow_state));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("entered_yieldable_blocks: "));TRY(builder.appendff("{}, ", entered_yieldable_blocks));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("deferred_output: "));TRY(builder.appendff("\"{}\", ", deferred_output));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_function: "));TRY(builder.appendff("{}, ", current_function));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("inside_defer: "));TRY(builder.appendff("{}, ", inside_defer));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("debug_info: "));TRY(builder.appendff("{}, ", debug_info));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("namespace_stack: "));TRY(builder.appendff("{}, ", namespace_stack));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("fresh_var_counter: "));TRY(builder.appendff("{}, ", fresh_var_counter));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("fresh_label_counter: "));TRY(builder.appendff("{}", fresh_label_counter));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<String> codegen::CodeGenerator::codegen_function(NonnullRefPtr<types::CheckedFunction> const function_,bool const as_method) {
{
if (((function_)->is_comptime)){
return (String(""));
}
return (TRY((((*this).codegen_function_in_namespace(function_,JaktInternal::OptionalNone(),as_method)))));
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_generic_type_instance(types::StructId const id,JaktInternal::Array<types::TypeId> const args,bool const as_namespace) const {
{
String output = String("");
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((id).module)));
String namespace_ = String("");
if (((type_module)->is_prelude())){
(namespace_ += String("JaktInternal::"));
}
else if ((!(((type_module)->is_root)))){
(namespace_ += ((type_module)->name));
(namespace_ += String("::"));
}
JaktInternal::Optional<types::StructId> const inner_weak_ptr_struct_id = TRY((((((*this).program))->check_and_extract_weak_ptr(id,args))));
if (((inner_weak_ptr_struct_id).has_value())){
(output += String("WeakPtr<"));
(output += namespace_);
types::StructId const inner_struct_id = ((inner_weak_ptr_struct_id).value());
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(inner_struct_id));
(output += TRY((((*this).codegen_namespace_qualifier(((struct_).scope_id))))));
(output += ((struct_).name));
(output += String(">"));
}
else {
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
bool const acquired_by_ref = ((!(as_namespace)) && ((((struct_).record_type)).index() == 1 /* Class */));
if (acquired_by_ref){
(output += String("NonnullRefPtr<"));
}
(output += namespace_);
(output += TRY((((*this).codegen_namespace_qualifier(((struct_).scope_id))))));
(output += ((struct_).name));
(output += String("<"));
bool first = true;
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId type_id = (_magic_value.value());
{
if ((!(first))){
(output += String(","));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_type(type_id)))));
}

}
}

(output += String(">"));
if (acquired_by_ref){
(output += String(">"));
}
}

return (output);
}
}

ErrorOr<JaktInternal::Array<types::ModuleId>> codegen::CodeGenerator::topologically_sort_modules() const {
{
JaktInternal::Dictionary<size_t,i64> in_degrees = (TRY((Dictionary<size_t, i64>::create_with_entries({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = ((((((*this).program))->modules)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<types::ModuleId> _magic = ((((module)->imports)).iterator());
for (;;){
JaktInternal::Optional<types::ModuleId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ModuleId imported_module = (_magic_value.value());
{
i64 const existing = ((in_degrees).get(((imported_module).id))).value_or_lazy_evaluated([&] { return static_cast<i64>(0LL); });
TRY((((in_degrees).set(((imported_module).id),(JaktInternal::checked_add<i64>(existing,static_cast<i64>(1LL)))))));
}

}
}

if ((!(((in_degrees).contains(((((module)->id)).id)))))){
TRY((((in_degrees).set(((((module)->id)).id),static_cast<i64>(0LL)))));
}
}

}
}

JaktInternal::Array<types::ModuleId> stack = (TRY((Array<types::ModuleId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = ((((((*this).program))->modules)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
if ((((in_degrees)[((((module)->id)).id)]) == static_cast<i64>(0LL))){
TRY((((stack).push(((module)->id)))));
}
}

}
}

JaktInternal::Array<types::ModuleId> sorted_modules = (TRY((Array<types::ModuleId>::create_with({}))));
while ((!(((stack).is_empty())))){
types::ModuleId const id = (((stack).pop()).value());
TRY((((sorted_modules).push(id))));
{
JaktInternal::ArrayIterator<types::ModuleId> _magic = ((((((((((*this).program))->modules))[((id).id)]))->imports)).iterator());
for (;;){
JaktInternal::Optional<types::ModuleId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ModuleId imported_module = (_magic_value.value());
{
i64 const module_in_degrees = ((in_degrees)[((imported_module).id)]);
TRY((((in_degrees).set(((imported_module).id),(JaktInternal::checked_sub<i64>(module_in_degrees,static_cast<i64>(1LL)))))));
if ((module_in_degrees == static_cast<i64>(1LL))){
TRY((((stack).push(types::ModuleId(((imported_module).id))))));
}
}

}
}

}
if ((((sorted_modules).size()) == ((((((*this).program))->modules)).size()))){
return (sorted_modules);
}
utility::panic(String("Cyclic module imports"));
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_debug_description_getter(types::CheckedStruct const struct_,bool const is_inline) {
{
String output = String("");
if (((!(is_inline)) && (!(((((struct_).generic_parameters)).is_empty()))))){
(output += String("template <"));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(output += String(","));
}

(output += String("typename "));
(output += TRY((((*this).codegen_type(((param).type_id))))));
}

}
}

(output += String(">\n"));
}
(output += String("ErrorOr<String> "));
if ((!(is_inline))){
(output += TRY((((*this).codegen_type_possibly_as_namespace(((struct_).type_id),true)))));
(output += String("::"));
}
(output += String("debug_description() const { "));
(output += String("auto builder = MUST(StringBuilder::create());"));
(output += TRY((String::formatted(String("TRY(builder.append(\"{}(\"));"),((struct_).name)))));
(output += String("{\n"));
(output += String("JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};\n"));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const field_var = ((((*this).program))->get_variable(((field).variable_id)));
(output += String("TRY(JaktInternal::PrettyPrint::output_indentation(builder));"));
(output += TRY((String::formatted(String("TRY(builder.append(\"{}: \"));"),((field_var).name)))));
(output += String("TRY(builder.appendff(\""));
if (((((*this).program))->is_string(((field_var).type_id)))){
(output += String("\\\"{}\\\""));
}
else {
(output += String("{}"));
}

if ((i != (JaktInternal::checked_sub<size_t>(((((struct_).fields)).size()),static_cast<size_t>(1ULL))))){
(output += String(", "));
}
(output += String("\", "));
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((field_var).type_id)));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = ((((((*this).program))->get_struct(struct_id))).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();return JaktInternal::ExplicitValue(String("*"));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
)));
(output += (((field_var).name) + String("));\n")));
((i++));
}

}
}

(output += String("}\n"));
(output += String("TRY(builder.append(\")\"));"));
(output += String("return builder.to_string();"));
(output += String(" }\n"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_expression_and_deref_if_generic_and_needed(NonnullRefPtr<types::CheckedExpression> const expression) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((expression)->type())));
switch(__jakt_match_variant.index()) {
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_380; {
String const contents = TRY((((*this).codegen_expression(expression))));
__jakt_var_380 = TRY((String::formatted(String("(*([]<typename V>(V const& value) {{ if constexpr (IsSpecializationOf<V, NonnullRefPtr>) return &*value; else return &value; }})({}))"),contents))); goto __jakt_label_353;

}
__jakt_label_353:; __jakt_var_380.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_expression(expression)))));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_namespace(NonnullRefPtr<types::Scope> const scope,NonnullRefPtr<types::Module> const current_module,bool const as_forward) {
{
if (((((scope)->import_path_if_extern)).has_value())){
return (String(""));
}
JaktInternal::Set<String> seen_types = (TRY((Set<String>::create_with_values({}))));
if (as_forward){
String output = String("");
JaktInternal::Dictionary<String,JaktInternal::Array<String>> const encoded_dependency_graph = TRY((((*this).produce_codegen_dependency_graph(scope))));
{
JaktInternal::DictionaryIterator<String,JaktInternal::Array<String>> _magic = ((encoded_dependency_graph).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,JaktInternal::Array<String>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,JaktInternal::Array<String>> entry = (_magic_value.value());
{
JaktInternal::Array<types::TypeId> const traversal = (TRY((Array<types::TypeId>::create_with({}))));
TRY((((*this).postorder_traversal(((entry).get<0>()),seen_types,encoded_dependency_graph,traversal))));
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((traversal).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId type_id = (_magic_value.value());
{
NonnullRefPtr<types::Type> const type_ = ((((*this).program))->get_type(type_id));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
return JaktInternal::LoopContinue{};
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
String const enum_output = TRY((((*this).codegen_enum(enum_))));
if ((!(((enum_output).is_empty())))){
(output += enum_output);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
return JaktInternal::LoopContinue{};
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
String const struct_output = TRY((((*this).codegen_struct(struct_))));
if ((!(((struct_output).is_empty())))){
(output += struct_output);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY((String::formatted(String("Unexpected type in dependency graph: {}"),type_))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
TRY((((seen_types).add(TRY((((type_id).to_string())))))));
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
JaktInternal::Tuple<String,types::StructId> ___struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::StructId> const jakt_____struct_id__ = ___struct_id__;
String const _ = ((jakt_____struct_id__).get<0>());
types::StructId const struct_id = ((jakt_____struct_id__).get<1>());

if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if (((seen_types).contains(TRY((((((struct_).type_id)).to_string())))))){
continue;
}
(output += TRY((((*this).codegen_struct(struct_)))));
(output += String("\n"));
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
JaktInternal::Tuple<String,types::EnumId> ___enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::EnumId> const jakt_____enum_id__ = ___enum_id__;
String const _ = ((jakt_____enum_id__).get<0>());
types::EnumId const enum_id = ((jakt_____enum_id__).get<1>());

if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
if (((seen_types).contains(TRY((((((enum_).type_id)).to_string())))))){
continue;
}
(output += TRY((((*this).codegen_enum(enum_)))));
(output += String("\n"));
}

}
}

{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> ___function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt_____function_id__ = ___function_id__;
String const _ = ((jakt_____function_id__).get<0>());
types::FunctionId const function_id = ((jakt_____function_id__).get<1>());

if ((!(((((function_id).module)).equals(((current_module)->id)))))){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(function_id));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function_);
ScopeGuard __jakt_var_381([&] {
(((*this).current_function) = previous_function);
});
if (((((((function_)->linkage)).index() == 1 /* External */) || ((((function_)->type)).index() == 1 /* ImplicitConstructor */)) || ((((function_)->type)).index() == 2 /* ImplicitEnumConstructor */))){
continue;
}
if ((!(((((((function_)->generics))->params)).is_empty())))){
(output += TRY((((*this).codegen_function(function_,false)))));
(output += String("\n"));
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
types::ScopeId child_scope_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((((*this).program))->get_scope(child_scope_id))));
if (((((child_scope)->namespace_name)).has_value())){
String const name = (((child_scope)->namespace_name).value());
TRY((((((*this).namespace_stack)).push(name))));
(output += String("namespace "));
(output += name);
(output += String(" {\n"));
(output += TRY((((*this).codegen_namespace(child_scope,current_module,as_forward)))));
(output += String("}\n"));
JaktInternal::Optional<String> const dummy = ((((*this).namespace_stack)).pop());
}
}

}
}

return (output);
}
String output = String("");
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> ___function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt_____function_id__ = ___function_id__;
String const _ = ((jakt_____function_id__).get<0>());
types::FunctionId const function_id = ((jakt_____function_id__).get<1>());

if ((!(((((function_id).module)).equals(((current_module)->id)))))){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(function_id));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function_);
ScopeGuard __jakt_var_382([&] {
(((*this).current_function) = previous_function);
});
if (((((((function_)->linkage)).index() == 1 /* External */) || ((((function_)->type)).index() == 1 /* ImplicitConstructor */)) || ((((function_)->type)).index() == 2 /* ImplicitEnumConstructor */))){
continue;
}
if (((((((function_)->generics))->params)).is_empty())){
(output += TRY((((*this).codegen_function(function_,false)))));
(output += String("\n"));
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
JaktInternal::Tuple<String,types::StructId> ___struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::StructId> const jakt_____struct_id__ = ___struct_id__;
String const _ = ((jakt_____struct_id__).get<0>());
types::StructId const struct_id = ((jakt_____struct_id__).get<1>());

if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if (((((struct_).definition_linkage)).index() == 1 /* External */)){
continue;
}
if ((!(((((struct_).generic_parameters)).is_empty())))){
continue;
}
(output += TRY((((*this).codegen_debug_description_getter(struct_,false)))));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((struct_).scope_id)))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> ___function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt_____function_id__ = ___function_id__;
String const _ = ((jakt_____function_id__).get<0>());
types::FunctionId const function_id = ((jakt_____function_id__).get<1>());

NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(function_id));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function_);
ScopeGuard __jakt_var_383([&] {
(((*this).current_function) = previous_function);
});
if (((((function_)->type)).index() == 1 /* ImplicitConstructor */)){
(output += TRY((((*this).codegen_constructor(function_,false)))));
(output += String("\n"));
}
else if (((!(((((function_)->type)).index() == 2 /* ImplicitEnumConstructor */))) && ((!(((function_)->is_comptime))) && ((((((function_)->generics))->params)).is_empty())))){
(output += TRY((((*this).codegen_function_in_namespace(function_,((struct_).type_id),false)))));
(output += String("\n"));
}
}

}
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
JaktInternal::Tuple<String,types::EnumId> ___enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::EnumId> const jakt_____enum_id__ = ___enum_id__;
String const _ = ((jakt_____enum_id__).get<0>());
types::EnumId const enum_id = ((jakt_____enum_id__).get<1>());

if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
if (((((enum_).definition_linkage)).index() == 1 /* External */)){
continue;
}
if ((!(((((enum_).generic_parameters)).is_empty())))){
continue;
}
if (((((enum_).underlying_type_id)).equals(types::void_type_id()))){
(output += TRY((((*this).codegen_enum_debug_description_getter(enum_,false)))));
}
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((enum_).scope_id)))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> ___function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt_____function_id__ = ___function_id__;
String const _ = ((jakt_____function_id__).get<0>());
types::FunctionId const function_id = ((jakt_____function_id__).get<1>());

NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(function_id));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function_);
ScopeGuard __jakt_var_384([&] {
(((*this).current_function) = previous_function);
});
if (((!(((((function_)->type)).index() == 1 /* ImplicitConstructor */))) && ((!(((((function_)->type)).index() == 2 /* ImplicitEnumConstructor */))) && (!(((function_)->is_comptime)))))){
(output += TRY((((*this).codegen_function_in_namespace(function_,((enum_).type_id),false)))));
(output += String("\n"));
}
}

}
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
types::ScopeId child_scope_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((((*this).program))->get_scope(child_scope_id))));
if (((((child_scope)->namespace_name)).has_value())){
String const name = (((child_scope)->namespace_name).value());
TRY((((((*this).namespace_stack)).push(name))));
(output += String("namespace "));
(output += name);
(output += String(" {\n"));
(output += TRY((((*this).codegen_namespace(child_scope,current_module,as_forward)))));
(output += String("}\n"));
JaktInternal::Optional<String> const dummy = ((((*this).namespace_stack)).pop());
}
}

}
}

return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_unchecked_binary_op(NonnullRefPtr<types::CheckedExpression> const lhs,NonnullRefPtr<types::CheckedExpression> const rhs,parser::BinaryOperator const op,types::TypeId const type_id) {
{
String output = String("static_cast<");
(output += TRY((((*this).codegen_type(type_id)))));
(output += String(">("));
(output += TRY((((*this).codegen_expression(lhs)))));
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Add>();
return JaktInternal::ExplicitValue(String(" + "));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Subtract>();
return JaktInternal::ExplicitValue(String(" - "));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Multiply>();
return JaktInternal::ExplicitValue(String(" * "));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Divide>();
return JaktInternal::ExplicitValue(String(" / "));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Modulo>();
return JaktInternal::ExplicitValue(String(" % "));
};/*case end*/
default: {
{
utility::panic(TRY((String::formatted(String("Checked binary operation codegen is not supported for BinaryOperator::{}"),op))));
}
};/*case end*/
}/*switch end*/
}()
)));
(output += TRY((((*this).codegen_expression(rhs)))));
(output += String(")"));
return (output);
}
}

ErrorOr<JaktInternal::Dictionary<String,JaktInternal::Array<String>>> codegen::CodeGenerator::produce_codegen_dependency_graph(NonnullRefPtr<types::Scope> const scope) const {
{
JaktInternal::Dictionary<String,JaktInternal::Array<String>> dependency_graph = (TRY((Dictionary<String, JaktInternal::Array<String>>::create_with_entries({}))));
{
JaktInternal::DictionaryIterator<String,types::TypeId> _magic = ((((scope)->types)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::TypeId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::TypeId> type_ = (_magic_value.value());
{
TRY((((dependency_graph).set(TRY((((((type_).get<1>())).to_string()))),TRY((((*this).extract_dependencies_from(((type_).get<1>()),dependency_graph,true))))))));
}

}
}

return (dependency_graph);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_unchecked_binary_op_assignment(NonnullRefPtr<types::CheckedExpression> const lhs,NonnullRefPtr<types::CheckedExpression> const rhs,parser::BinaryOperator const op,types::TypeId const type_id) {
{
String output = String("");
(output += String("{"));
(output += String("auto& _jakt_ref = "));
(output += TRY((((*this).codegen_expression(lhs)))));
(output += String(";"));
(output += String("_jakt_ref = static_cast<"));
(output += TRY((((*this).codegen_type(type_id)))));
(output += String(">(_jakt_ref "));
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::AddAssign>();
return JaktInternal::ExplicitValue(String(" + "));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::SubtractAssign>();
return JaktInternal::ExplicitValue(String(" - "));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::MultiplyAssign>();
return JaktInternal::ExplicitValue(String(" * "));
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::DivideAssign>();
return JaktInternal::ExplicitValue(String(" / "));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::ModuloAssign>();
return JaktInternal::ExplicitValue(String(" % "));
};/*case end*/
default: {
{
utility::panic(TRY((String::formatted(String("Checked binary operation assignment codegen is not supported for BinaryOperator::{}"),op))));
}
};/*case end*/
}/*switch end*/
}()
)));
(output += TRY((((*this).codegen_expression(rhs)))));
(output += String(");"));
(output += String("}"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_statement(NonnullRefPtr<types::CheckedStatement> const statement) {
{
bool add_newline = true;
String output = String("");
if ((((((*this).debug_info)).statement_span_comments) && (((((statement)->span())).has_value()) && add_newline))){
(output += TRY((String::formatted(String("\n#line {}\n"),TRY((((((*this).debug_info)).span_to_source_location((((statement)->span()).value())))))))));
}
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Throw>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((String("return ") + TRY((((*this).codegen_expression(expr))))) + String(";")));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Continue>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((((*this).control_flow_state)).passes_through_match));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("return JaktInternal::LoopContinue{};"));
}
else {
return JaktInternal::ExplicitValue(String("continue;"));
}
}()))
);
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Break>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((((*this).control_flow_state)).passes_through_match));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("return JaktInternal::LoopBreak{};"));
}
else {
return JaktInternal::ExplicitValue(String("break;"));
}
}()))
);
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Expression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue((TRY((((*this).codegen_expression(expr)))) + String(";")));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Defer>();NonnullRefPtr<types::CheckedStatement> const& statement = __jakt_match_value.statement;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_385; {
String output = String("");
(output += String("ScopeGuard "));
(output += TRY((((*this).fresh_var()))));
(output += String("([&] {\n"));
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
bool const old_inside_defer = ((*this).inside_defer);
(((((*this).control_flow_state)).passes_through_match) = false);
(((*this).inside_defer) = true);
(output += TRY((((*this).codegen_statement(statement)))));
(output += String("});"));
(((*this).control_flow_state) = last_control_flow);
(((*this).inside_defer) = old_inside_defer);
__jakt_var_385 = output; goto __jakt_label_354;

}
__jakt_label_354:; __jakt_var_385.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Return>();JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((val).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((String("return (") + TRY((((*this).codegen_expression((val.value())))))) + String(");")));
}
else {
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_386; {
__jakt_var_386 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = ((((((*this).current_function).value()))->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("return {};"));
}
else {
return JaktInternal::ExplicitValue(String("return;"));
}
}()))
; goto __jakt_label_355;

}
__jakt_label_355:; __jakt_var_386.release_value(); }));
}
}()))
);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Loop>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_387; {
String output = String("");
if ((((((*this).debug_info)).statement_span_comments) && ((((statement)->span())).has_value()))){
(output += TRY((String::formatted(String("\n#line {}\n"),TRY((((((*this).debug_info)).span_to_source_location((((statement)->span()).value())))))))));
}
(output += String("for (;;)"));
(add_newline = false);
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((last_control_flow).enter_loop()));
String const block_str = TRY((((*this).codegen_block(block))));
(((*this).control_flow_state) = last_control_flow);
(output += block_str);
__jakt_var_387 = output; goto __jakt_label_356;

}
__jakt_label_356:; __jakt_var_387.release_value(); }));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::While>();NonnullRefPtr<types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_388; {
String output = String("");
if ((((((*this).debug_info)).statement_span_comments) && ((((statement)->span())).has_value()))){
(output += TRY((String::formatted(String("\n#line {}\n"),TRY((((((*this).debug_info)).span_to_source_location((((statement)->span()).value())))))))));
}
(output += String("while ("));
(output += TRY((((*this).codegen_expression(condition)))));
(output += String(")"));
{
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((last_control_flow).enter_loop()));
String const code = TRY((((*this).codegen_block(block))));
(((*this).control_flow_state) = last_control_flow);
(output += code);
}

(add_newline = false);
__jakt_var_388 = output; goto __jakt_label_357;

}
__jakt_label_357:; __jakt_var_388.release_value(); }));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Block>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_block(block)))));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Garbage>();
{
utility::panic(String("Garbage statement in codegen"));
}
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::DestructuringAssignment>();JaktInternal::Array<NonnullRefPtr<types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_389; {
String output = String("");
(output += TRY((((*this).codegen_statement(var_decl)))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedStatement>> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedStatement> v = (_magic_value.value());
{
(output += TRY((((*this).codegen_statement(v)))));
}

}
}

__jakt_var_389 = output; goto __jakt_label_358;

}
__jakt_label_358:; __jakt_var_389.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::VarDecl>();types::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<types::CheckedExpression> const& init = __jakt_match_value.init;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_390; {
types::CheckedVariable const var = ((((*this).program))->get_variable(var_id));
String output = String("");
NonnullRefPtr<types::Type> const var_type = ((((*this).program))->get_type(((var).type_id)));
(output += TRY((((*this).codegen_type(((var).type_id))))));
(output += String(" "));
if (((!(((var).is_mutable))) && (!((((var_type)->index() == 27 /* Reference */) || ((var_type)->index() == 28 /* MutableReference */)))))){
(output += String("const "));
}
(output += ((var).name));
(output += String(" = "));
(output += TRY((((*this).codegen_expression(init)))));
(output += String(";"));
__jakt_var_390 = output; goto __jakt_label_359;

}
__jakt_label_359:; __jakt_var_390.release_value(); }));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::InlineCpp>();JaktInternal::Array<String> const& lines = __jakt_match_value.lines;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_391; {
String output = String("");
{
JaktInternal::ArrayIterator<String> _magic = ((lines).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String line = (_magic_value.value());
{
String escaped_line = line;
(escaped_line = TRY((((escaped_line).replace(String("\\\""),String("\""))))));
(escaped_line = TRY((((escaped_line).replace(String("\\\\"),String("\\"))))));
(output += escaped_line);
}

}
}

__jakt_var_391 = output; goto __jakt_label_360;

}
__jakt_label_360:; __jakt_var_391.release_value(); }));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::If>();NonnullRefPtr<types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_392; {
String output = String("");
if ((((((*this).debug_info)).statement_span_comments) && ((((statement)->span())).has_value()))){
(output += TRY((String::formatted(String("\n#line {}\n"),TRY((((((*this).debug_info)).span_to_source_location((((statement)->span()).value())))))))));
}
(output += String("if ("));
(output += TRY((((*this).codegen_expression(condition)))));
(output += String(")"));
(output += TRY((((*this).codegen_block(then_block)))));
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((else_statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((String("else ") + TRY((((*this).codegen_statement((else_statement.value())))))));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
);
(add_newline = false);
__jakt_var_392 = output; goto __jakt_label_361;

}
__jakt_label_361:; __jakt_var_392.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Yield>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_393; {
String output = String("");
if ((((((*this).entered_yieldable_blocks)).size()) == static_cast<size_t>(0ULL))){
utility::panic(String("Must be in a block to yield"));
}
JaktInternal::Tuple<String,String> const var_name_end_label_ = (((((*this).entered_yieldable_blocks)).last()).value());
String const var_name = ((var_name_end_label_).get<0>());
String const end_label = ((var_name_end_label_).get<1>());

(output += var_name);
(output += String(" = "));
(output += TRY((((*this).codegen_expression(expr)))));
(output += String("; goto "));
(output += end_label);
(output += String(";\n"));
__jakt_var_393 = output; goto __jakt_label_362;

}
__jakt_label_362:; __jakt_var_393.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
if (add_newline){
(output += String("\n"));
}
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_enum(types::CheckedEnum const enum_) {
{
String output = String("");
if ((!(((((enum_).underlying_type_id)).equals(types::void_type_id()))))){
if (((((*this).program))->is_integer(((enum_).underlying_type_id)))){
(output += ((((String("enum class ") + ((enum_).name)) + String(": ")) + TRY((((*this).codegen_type(((enum_).underlying_type_id)))))) + String(" {\n")));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();String const& name = __jakt_match_value.name;
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue((((name + String(" = ")) + TRY((((*this).codegen_expression(expr))))) + String(",\n")));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_394; {
utility::todo(TRY((String::formatted(String("codegen_enum can't generate variant: {}"),variant))));
__jakt_var_394 = String(""); goto __jakt_label_363;

}
__jakt_label_363:; __jakt_var_394.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
}

}
}

return ((output + String("};\n")));
}
else {
utility::todo(String("Enums with a non-integer underlying type"));
}

}
bool const is_generic = (!(((((enum_).generic_parameters)).is_empty())));
JaktInternal::Array<String> generic_parameter_names = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if (((((((*this).program))->get_type(((generic_parameter).type_id))))->index() == 18 /* TypeVariable */)){
String const name = (((((*this).program))->get_type(((generic_parameter).type_id)))->get<types::Type::TypeVariable>()).value;
TRY((((generic_parameter_names).push(name))));
}
}

}
}

String template_args = utility::join(TRY((utility::prepend_to_each(generic_parameter_names,String("typename ")))),String(", "));
JaktInternal::Array<JaktInternal::Tuple<String,String>> common_fields = (TRY((Array<JaktInternal::Tuple<String,String>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const variable = ((((*this).program))->get_variable(((field).variable_id)));
TRY((((common_fields).push((Tuple{((variable).name), TRY((((*this).codegen_type(((variable).type_id)))))})))));
}

}
}

(output += ((String("namespace ") + ((enum_).name)) + String("_Details {\n")));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
JaktInternal::Array<JaktInternal::Tuple<String,String>> const fields = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<JaktInternal::Tuple<String,String>>, ErrorOr<String>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,String>>> __jakt_var_395; {
if (is_generic){
(output += ((String("template<") + template_args) + String(">\n")));
}
(output += ((String("struct ") + name) + String(" {\n")));
__jakt_var_395 = common_fields; goto __jakt_label_364;

}
__jakt_label_364:; __jakt_var_395.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& name = __jakt_match_value.name;
JaktInternal::Array<types::VarId> const& own_fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,String>>> __jakt_var_396; {
JaktInternal::Array<JaktInternal::Tuple<String,String>> fields = (TRY((Array<JaktInternal::Tuple<String,String>>::create_with({}))));
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((own_fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
types::CheckedVariable const variable = ((((*this).program))->get_variable(field));
TRY((((fields).push((Tuple{((variable).name), TRY((((*this).codegen_type(((variable).type_id)))))})))));
}

}
}

if (is_generic){
(output += ((String("template<") + template_args) + String(">\n")));
}
(output += ((String("struct ") + name) + String(" {\n")));
__jakt_var_396 = fields; goto __jakt_label_365;

}
__jakt_label_365:; __jakt_var_396.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& name = __jakt_match_value.name;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,String>>> __jakt_var_397; {
JaktInternal::Array<JaktInternal::Tuple<String,String>> fields = (TRY((Array<JaktInternal::Tuple<String,String>>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,String>> _magic = ((common_fields).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,String>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,String> field = (_magic_value.value());
{
TRY((((fields).push(field))));
}

}
}

TRY((((fields).push((Tuple{String("value"), TRY((((*this).codegen_type(type_id))))})))));
if (is_generic){
(output += ((String("template<") + template_args) + String(">\n")));
}
(output += ((String("struct ") + name) + String("{\n")));
__jakt_var_397 = fields; goto __jakt_label_366;

}
__jakt_label_366:; __jakt_var_397.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Array<JaktInternal::Tuple<String,String>>> __jakt_var_398; {
utility::todo(TRY((String::formatted(String("codegen enum variant: {}"),variant))));
__jakt_var_398 = (TRY((Array<JaktInternal::Tuple<String,String>>::create_with({})))); goto __jakt_label_367;

}
__jakt_label_367:; __jakt_var_398.release_value(); }));
};/*case end*/
}/*switch end*/
}()
));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,String>> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,String>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,String> name__type__ = (_magic_value.value());
{
JaktInternal::Tuple<String,String> const jakt__name__type__ = name__type__;
String const name = ((jakt__name__type__).get<0>());
String const type = ((jakt__name__type__).get<1>());

(output += TRY((String::formatted(String("{} {};\n"),type,name))));
}

}
}

if ((!(((fields).is_empty())))){
(output += String("template<"));
JaktInternal::Array<String> generic_typenames = (TRY((Array<String>::create_with({}))));
JaktInternal::Array<String> generic_argument_types = (TRY((Array<String>::create_with({}))));
JaktInternal::Array<String> initializers = (TRY((Array<String>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((fields).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
TRY((((generic_typenames).push(TRY((String::formatted(String("typename _MemberT{}"),i)))))));
TRY((((generic_argument_types).push(TRY((String::formatted(String("_MemberT{}&& member_{}"),i,i)))))));
String initializer = (((((fields)[i])).get<0>()) + String("{ forward<_MemberT"));
(initializer += (TRY((String::formatted(String("{}>(member_{}"),i,i))) + String(")}")));
TRY((((initializers).push(initializer))));
}

}
}

(output += utility::join(generic_typenames,String(", ")));
(output += String(">\n"));
(output += (((((variant).name()) + String("(")) + utility::join(generic_argument_types,String(", "))) + String("):\n")));
(output += (utility::join(initializers,String(",\n")) + String("\n{}\n")));
}
(output += String("};\n"));
}

}
}

(output += String("}\n"));
if (is_generic){
(output += ((String("template<") + template_args) + String(">\n")));
}
JaktInternal::Array<String> variant_names = (TRY((Array<String>::create_with({}))));
JaktInternal::Array<String> variant_arguments_array = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
String argument = ((((enum_).name) + String("_Details::")) + ((variant).name()));
if (is_generic){
(argument += TRY((String::formatted(String("<{}>"),utility::join(generic_parameter_names,String(", "))))));
}
TRY((((variant_arguments_array).push(argument))));
TRY((((variant_names).push(((variant).name())))));
}

}
}

String const variant_args = utility::join(variant_arguments_array,String(", "));
(output += TRY((String::formatted(String("struct {} : public Variant<{}>"),((enum_).name),variant_args))));
if (((enum_).is_boxed)){
(output += TRY((String::formatted(String(", public RefCounted<{}"),((enum_).name)))));
if (is_generic){
(output += TRY((String::formatted(String("<{}>"),utility::join(generic_parameter_names,String(", "))))));
}
(output += String(">"));
}
(output += String(" {\n"));
(output += ((String("using Variant<") + variant_args) + String(">::Variant;\n")));
{
JaktInternal::ArrayIterator<String> _magic = ((variant_names).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String name = (_magic_value.value());
{
(output += (((((String("    using ") + name) + String(" = ")) + ((enum_).name)) + String("_Details::")) + name));
if (is_generic){
(output += String("<"));
(output += utility::join(generic_parameter_names,String(", ")));
(output += String(">"));
}
(output += String(";\n"));
}

}
}

if (((enum_).is_boxed)){
String fully_instantiated_name = ((enum_).name);
if (is_generic){
(fully_instantiated_name += TRY((String::formatted(String("<{}>"),utility::join(generic_parameter_names,String(", "))))));
}
(output += String("template<typename V, typename... Args> static auto create(Args&&... args) {\n"));
(output += TRY((String::formatted(String("return adopt_nonnull_ref_or_enomem(new (nothrow) {}(V(forward<Args>(args)...)));\n"),fully_instantiated_name))));
(output += String("}\n"));
}
if (((((enum_).generic_parameters)).is_empty())){
(output += String("ErrorOr<String> debug_description() const;\n"));
}
else {
(output += TRY((((*this).codegen_enum_debug_description_getter(enum_,true)))));
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,String>> _magic = ((common_fields).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,String>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,String> field_name__type__ = (_magic_value.value());
{
JaktInternal::Tuple<String,String> const jakt__field_name__type__ = field_name__type__;
String const field_name = ((jakt__field_name__type__).get<0>());
String const type = ((jakt__field_name__type__).get<1>());

(output += TRY((String::formatted(String("{} const& {}() const {{ switch(this->index()) {{"),type,field_name))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).variants)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedEnumVariant const variant = ((((enum_).variants))[i]);
String const name = ((variant).name());
(output += TRY((String::formatted(String("case {} /* {} */: "),i,name))));
(output += TRY((String::formatted(String("return this->template get<{}::{}>().{};\n"),((enum_).name),name,field_name))));
}

}
}

(output += String("default: VERIFY_NOT_REACHED();\n"));
(output += String("}\n}\n"));
}

}
}

NonnullRefPtr<types::Scope> const enum_scope = TRY((((((*this).program))->get_scope(((enum_).scope_id)))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((enum_scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> function_item = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(((function_item).get<1>())));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function_id = ((*this).current_function);
(((*this).current_function) = static_cast<JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>>>(function_));
ScopeGuard __jakt_var_399([&] {
(((*this).current_function) = previous_function_id);
});
if ((!(((((function_)->type)).index() == 2 /* ImplicitEnumConstructor */)))){
if ((((((enum_).generic_parameters)).is_empty()) && ((((((function_)->generics))->params)).is_empty()))){
(output += TRY((((*this).codegen_function_predecl(function_,true)))));
}
else {
(output += TRY((((*this).codegen_function(function_,true)))));
}

}
}

}
}

(output += String("};\n"));
(((*this).deferred_output) += TRY((((*this).codegen_ak_formatter(((enum_).name),generic_parameter_names)))));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_struct_type(types::StructId const id,bool const as_namespace) const {
{
String output = String("");
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((id).module)));
types::CheckedStruct const checked_struct = ((((*this).program))->get_struct(id));
if (((!(as_namespace)) && ((((checked_struct).record_type)).index() == 1 /* Class */))){
(output += String("NonnullRefPtr<"));
if (((!(((type_module)->is_root))) && (!(((((type_module)->id)).equals(types::ModuleId(static_cast<size_t>(0ULL)))))))){
(output += ((type_module)->name));
(output += String("::"));
}
(output += TRY((((*this).codegen_namespace_qualifier(((checked_struct).scope_id))))));
(output += ((checked_struct).name));
(output += String(">"));
}
else {
if ((!(((((type_module)->is_root) || ((((type_module)->id)).equals(types::ModuleId(static_cast<size_t>(0ULL))))) || ((((checked_struct).definition_linkage)).index() == 1 /* External */))))){
(output += ((type_module)->name));
(output += String("::"));
}
(output += TRY((((*this).codegen_namespace_qualifier(((checked_struct).scope_id))))));
(output += ((checked_struct).name));
}

return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_struct_predecl(types::CheckedStruct const struct_) {
{
if (((((struct_).definition_linkage)).index() == 1 /* External */)){
return (String(""));
}
String output = String("");
if ((!(((((struct_).generic_parameters)).is_empty())))){
(output += String("template <"));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(output += String(","));
}

(output += String("typename "));
(output += TRY((((*this).codegen_type(((generic_parameter).type_id))))));
}

}
}

(output += String(">"));
}
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();return JaktInternal::ExplicitValue(String("class "));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();return JaktInternal::ExplicitValue(String("struct "));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
)));
(output += ((struct_).name));
(output += String(";"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_generic_match(NonnullRefPtr<types::CheckedExpression> const expr,JaktInternal::Array<types::CheckedMatchCase> const cases,types::TypeId const return_type_id,bool const all_variants_constant) {
{
String output = String("");
bool is_generic_enum = false;
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase case_ = (_magic_value.value());
{
if (((case_).index() == 0 /* EnumVariant */)){
(is_generic_enum = true);
break;
}
}

}
}

bool const match_values_all_constant = (all_variants_constant && (!(is_generic_enum)));
(output += ((((*this).control_flow_state)).choose_control_flow_macro()));
(output += (TRY((String::formatted(String("(([&]() -> JaktInternal::ExplicitValueOrControlFlow<{},{}>"),TRY((((*this).codegen_type(return_type_id)))),TRY((((*this).codegen_function_return_type((((*this).current_function).value())))))))) + String("{\n")));
if (is_generic_enum){
(output += String("auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer("));
}
else {
(output += String("auto __jakt_enum_value = ("));
}

(output += TRY((((*this).codegen_expression(expr)))));
(output += String(");\n"));
bool has_default = false;
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase case_ = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = case_;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::EnumVariant>();String const& name = __jakt_match_value.name;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
types::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
types::ScopeId const& scope_id = __jakt_match_value.scope_id;
types::CheckedMatchBody const& body = __jakt_match_value.body;
{
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::EnumId, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(subject_type_id));
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY((String::formatted(String("Unexpected type in IsEnumVariant: {}"),((((*this).program))->get_type(subject_type_id))))));
}
};/*case end*/
}/*switch end*/
}()
))));
i64 variant_index = static_cast<i64>(0LL);
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
break;
}
((variant_index++));
}

}
}

(output += TRY((String::formatted(String("if (__jakt_enum_value.index() == {} /* {} */) {{\n"),variant_index,name))));
String variant_type_name = String("");
String const qualifier = TRY((((*this).codegen_type_possibly_as_namespace(subject_type_id,true))));
if ((!(((qualifier).is_empty())))){
(variant_type_name += String("typename JaktInternal::RemoveRefPtr<"));
(variant_type_name += qualifier);
(variant_type_name += String(">::"));
}
(variant_type_name += name);
(output += String("auto& __jakt_match_value = __jakt_enum_value.template get<"));
(output += variant_type_name);
(output += String(">();\n"));
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument arg = (_magic_value.value());
{
(output += String("auto& "));
(output += ((arg).binding));
(output += String(" = __jakt_match_value."));
(output += ((arg).name).value_or_lazy_evaluated([&] { return String("value"); }));
(output += String(";\n"));
}

}
}

(output += TRY((((*this).codegen_match_body(body,return_type_id)))));
(output += String("}\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::CatchAll>();bool const& has_arguments = __jakt_match_value.has_arguments;
types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
{
if (has_arguments){
utility::panic(String("Bindings aren't allowed in generic else"));
}
(has_default = true);
if (first){
(output += String("{"));
}
else {
(output += String("else {\n"));
}

(output += TRY((((*this).codegen_match_body(body,return_type_id)))));
(output += String("}\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::Expression>();NonnullRefPtr<types::CheckedExpression> const& expression = __jakt_match_value.expression;
types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
{
if ((!(first))){
(output += String("else "));
}
if (((expression)->index() == 8 /* Range */)){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const from = (expression->get<types::CheckedExpression::Range>()).from;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const to = (expression->get<types::CheckedExpression::Range>()).to;
(output += String("if (__jakt_enum_value"));
if (((from).has_value())){
(output += String(" >= "));
(output += TRY((((*this).codegen_expression((from.value()))))));
}
if (((to).has_value())){
if (((from).has_value())){
(output += String("&& __jakt_enum_value "));
}
(output += String("< "));
(output += TRY((((*this).codegen_expression((to.value()))))));
}
}
else {
(output += String("if (__jakt_enum_value == "));
(output += TRY((((*this).codegen_expression(expression)))));
}

(output += String(") {\n"));
(output += TRY((((*this).codegen_match_body(body,return_type_id)))));
(output += String("}\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
(first = false);
}

}
}

if ((((return_type_id).equals(types::void_type_id())) || ((return_type_id).equals(types::unknown_type_id())))){
(output += String("return JaktInternal::ExplicitValue<void>();\n"));
}
else if ((!(has_default))){
(output += String("VERIFY_NOT_REACHED();\n"));
}
(output += String("}()))\n"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_checked_binary_op(NonnullRefPtr<types::CheckedExpression> const lhs,NonnullRefPtr<types::CheckedExpression> const rhs,parser::BinaryOperator const op,types::TypeId const type_id) {
{
String output = String("");
(output += String("JaktInternal::"));
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Add>();
return JaktInternal::ExplicitValue(String("checked_add"));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Subtract>();
return JaktInternal::ExplicitValue(String("checked_sub"));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Multiply>();
return JaktInternal::ExplicitValue(String("checked_mul"));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Divide>();
return JaktInternal::ExplicitValue(String("checked_div"));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Modulo>();
return JaktInternal::ExplicitValue(String("checked_mod"));
};/*case end*/
default: {
{
utility::panic(TRY((String::formatted(String("Checked binary operation codegen is not supported for BinaryOperator::{}"),op))));
}
};/*case end*/
}/*switch end*/
}()
)));
(output += String("<"));
(output += TRY((((*this).codegen_type(type_id)))));
(output += String(">("));
(output += TRY((((*this).codegen_expression(lhs)))));
(output += String(","));
(output += TRY((((*this).codegen_expression(rhs)))));
(output += String(")"));
return (output);
}
}

ErrorOr<JaktInternal::Array<String>> codegen::CodeGenerator::extract_dependencies_from_enum(types::EnumId const enum_id,JaktInternal::Dictionary<String,JaktInternal::Array<String>> const dependency_graph,bool const top_level) const {
{
JaktInternal::Array<String> dependencies = (TRY((Array<String>::create_with({}))));
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
if (((((enum_).definition_linkage)).index() == 1 /* External */)){
return (dependencies);
}
if ((((enum_).is_boxed) && (!(top_level)))){
return (dependencies);
}
TRY((((dependencies).push(TRY((((((enum_).type_id)).to_string())))))));
if ((!(((((enum_).underlying_type_id)).equals(types::unknown_type_id()))))){
JaktInternal::Array<String> const inner_dependencies = TRY((((*this).extract_dependencies_from(((enum_).underlying_type_id),dependency_graph,false))));
{
JaktInternal::ArrayIterator<String> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

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
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Array<String>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();types::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Array<String> const inner_dependencies = TRY((((*this).extract_dependencies_from(type_id,dependency_graph,false))));
{
JaktInternal::ArrayIterator<String> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();JaktInternal::Array<types::VarId> const& fields = __jakt_match_value.fields;
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
types::TypeId const type_id = ((((((*this).program))->get_variable(field))).type_id);
JaktInternal::Array<String> const inner_dependencies = TRY((((*this).extract_dependencies_from(type_id,dependency_graph,false))));
{
JaktInternal::ArrayIterator<String> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

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

}
}

return (dependencies);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_expression(NonnullRefPtr<types::CheckedExpression> const expression) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *expression;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Range>();JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& to = __jakt_match_value.to;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_400; {
String output = String("");
NonnullRefPtr<types::Type> const type = ((((*this).program))->get_type(type_id));
types::TypeId const index_type = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<String>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
default: {
{
utility::panic(String("Internal error: range expression doesn't have Range type"));
}
};/*case end*/
}/*switch end*/
}()
));
(output += String("("));
(output += TRY((((*this).codegen_type(type_id)))));
(output += String("{"));
(output += String("static_cast<"));
(output += TRY((((*this).codegen_type(index_type)))));
(output += String(">("));
if (((from).has_value())){
(output += TRY((((*this).codegen_expression((from.value()))))));
}
else {
(output += String("0LL"));
}

(output += String("),static_cast<"));
(output += TRY((((*this).codegen_type(index_type)))));
(output += String(">("));
if (((to).has_value())){
(output += TRY((((*this).codegen_expression((to.value()))))));
}
else {
(output += String("9223372036854775807LL"));
}

(output += String(")})"));
__jakt_var_400 = output; goto __jakt_label_368;

}
__jakt_label_368:; __jakt_var_400.release_value(); }));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::OptionalNone>();return JaktInternal::ExplicitValue(String("JaktInternal::OptionalNone()"));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::OptionalSome>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(((((String("static_cast<") + TRY((((*this).codegen_type(type_id))))) + String(">(")) + TRY((((*this).codegen_expression(expr))))) + String(")")));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ForcedUnwrap>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(((String("(") + TRY((((*this).codegen_expression(expr))))) + String(".value())")));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::QuotedString>();String const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_401; {
String const escaped_value = TRY((((val).replace(String("\n"),String("\\n")))));
__jakt_var_401 = ((String("String(\"") + escaped_value) + String("\")")); goto __jakt_label_369;

}
__jakt_label_369:; __jakt_var_401.release_value(); }));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ByteConstant>();String const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(((String("'") + val) + String("'")));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::CharacterConstant>();String const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(((String("'") + val) + String("'")));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Var>();types::CheckedVariable const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((var).name));
if (__jakt_enum_value == String("this")) {
return JaktInternal::ExplicitValue(String("*this"));
}
else {
return JaktInternal::ExplicitValue(((var).name));
}
}()))
);
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedExpression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(((((String("((") + TRY((((*this).codegen_expression(expr))))) + String(")[")) + TRY((((*this).codegen_expression(index))))) + String("])")));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedDictionary>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(((((String("((") + TRY((((*this).codegen_expression(expr))))) + String(")[")) + TRY((((*this).codegen_expression(index))))) + String("])")));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedTuple>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((String::formatted(String("(({}).map([](auto& _value) {{ return _value.template get<{}>(); }}))"),TRY((((*this).codegen_expression(expr)))),index))));
}
else {
return JaktInternal::ExplicitValue(TRY((String::formatted(String("(({}).get<{}>())"),TRY((((*this).codegen_expression(expr)))),index))));
}
}()))
);
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedStruct>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
String const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_402; {
String output = String("");
String const object = TRY((((*this).codegen_expression(expr))));
(output += String("(("));
(output += object);
(output += String(")"));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((expr)->type())));
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
{
(output += String("->"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
{
types::CheckedStruct const structure = ((((*this).program))->get_struct(id));
if ((((((structure).record_type)).index() == 1 /* Class */) && (object != String("*this")))){
(output += String("->"));
}
else {
(output += String("."));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
{
types::CheckedStruct const structure = ((((*this).program))->get_struct(id));
if ((((((structure).record_type)).index() == 1 /* Class */) && (object != String("*this")))){
(output += String("->"));
}
else {
(output += String("."));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(output += String("."));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
if (is_optional){
(output += String("map([](auto& _value) { return _value."));
(output += index);
(output += String("; })"));
}
else {
(output += index);
}

(output += String(")"));
__jakt_var_402 = output; goto __jakt_label_370;

}
__jakt_label_370:; __jakt_var_402.release_value(); }));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedCommonEnumMember>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
String const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_403; {
String output = String("");
String const object = TRY((((*this).codegen_expression(expr))));
(output += String("(("));
(output += object);
(output += String(")"));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((expr)->type())));
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
{
(output += String("->"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
{
types::CheckedEnum const structure = ((((*this).program))->get_enum(id));
if (((((structure).record_type)).index() == 3 /* SumEnum */)){
bool const is_boxed = (((structure).record_type).get<parser::RecordType::SumEnum>()).is_boxed;
if ((is_boxed && (object != String("*this")))){
(output += String("->"));
}
else {
(output += String("."));
}

}
else {
(output += String("."));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
{
types::CheckedEnum const structure = ((((*this).program))->get_enum(id));
if (((((structure).record_type)).index() == 3 /* SumEnum */)){
bool const is_boxed = (((structure).record_type).get<parser::RecordType::SumEnum>()).is_boxed;
if ((is_boxed && (object != String("*this")))){
(output += String("->"));
}
else {
(output += String("."));
}

}
else {
(output += String("."));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(output += String("."));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
if (is_optional){
(output += String("map([](auto& _value) { return _value."));
(output += index);
(output += String("(); })"));
}
else {
(output += (index + String("()")));
}

(output += String(")"));
__jakt_var_403 = output; goto __jakt_label_371;

}
__jakt_label_371:; __jakt_var_403.release_value(); }));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Block>();types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_block(block)))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_call(call)))));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedCall const& call = __jakt_match_value.call;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_method_call(expr,call,is_optional)))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Boolean>();bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (val);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("true"));
}
else {
return JaktInternal::ExplicitValue(String("false"));
}
}()))
);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_404; {
String output = String("(");
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PreIncrement>();
return JaktInternal::ExplicitValue(String("++"));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PreDecrement>();
return JaktInternal::ExplicitValue(String("--"));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Negate>();
return JaktInternal::ExplicitValue(String("-"));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Dereference>();
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((expr)->type())));
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
return JaktInternal::ExplicitValue(String("*"));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
)));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::RawAddress>();
return JaktInternal::ExplicitValue(String("&"));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::LogicalNot>();
return JaktInternal::ExplicitValue(String("!"));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::BitwiseNot>();
return JaktInternal::ExplicitValue(String("~"));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Is>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_405; {
String const is_type = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_406; {
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((id).module)));
__jakt_var_406 = ((((((*this).program))->get_struct(id))).name); goto __jakt_label_374;

}
__jakt_label_374:; __jakt_var_406.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(type_id)))));
};/*case end*/
}/*switch end*/
}()
));
__jakt_var_405 = ((String("is<") + is_type) + String(">(")); goto __jakt_label_373;

}
__jakt_label_373:; __jakt_var_405.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::TypeCast>();
types::CheckedTypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_407; {
types::TypeId final_type_id = ((cast).type_id());
String const cast_type = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedTypeCast::Fallible>();
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_408; {
NonnullRefPtr<types::Type> const ty = ((((*this).program))->get_type(((cast).type_id())));
types::TypeId const type_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::TypeId, ErrorOr<String>>{
auto&& __jakt_match_variant = *ty;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
default: {
{
utility::panic(String("Fallible type cast must have Optional result."));
}
};/*case end*/
}/*switch end*/
}()
));
String cast_type = String("dynamic_cast");
if (((((*this).program))->is_integer(type_id))){
(final_type_id = type_id);
(cast_type = String("fallible_integer_cast"));
}
__jakt_var_408 = cast_type; goto __jakt_label_376;

}
__jakt_label_376:; __jakt_var_408.release_value(); }));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedTypeCast::Infallible>();
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_409; {
String cast_type = String("verify_cast");
if (((((*this).program))->is_integer(type_id))){
(cast_type = String("infallible_integer_cast"));
}
__jakt_var_409 = cast_type; goto __jakt_label_377;

}
__jakt_label_377:; __jakt_var_409.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
__jakt_var_407 = (((cast_type + String("<")) + TRY((((*this).codegen_type(final_type_id))))) + String(">(")); goto __jakt_label_375;

}
__jakt_label_375:; __jakt_var_407.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
)));
(output += String("("));
String const object = TRY((((*this).codegen_expression(expr))));
(output += object);
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PostIncrement>();
return JaktInternal::ExplicitValue(String("++)"));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PostDecrement>();
return JaktInternal::ExplicitValue(String("--)"));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::TypeCast>();
return JaktInternal::ExplicitValue(String("))"));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Is>();
return JaktInternal::ExplicitValue(String("))"));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedUnaryOperator::IsEnumVariant>();types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
types::TypeId const& enum_type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_410; {
String const name = ((enum_variant).name());
String suffix = String(")");
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::EnumId, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(enum_type_id));
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY((String::formatted(String("Unexpected type in IsEnumVariant: {}"),((((*this).program))->get_type(enum_type_id))))));
}
};/*case end*/
}/*switch end*/
}()
))));
bool const is_boxed = ((enum_).is_boxed);
if ((is_boxed && (object != String("*this")))){
(suffix += String("->"));
}
else {
(suffix += String("."));
}

i64 variant_index = static_cast<i64>(0LL);
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
break;
}
((variant_index++));
}

}
}

(suffix += TRY((String::formatted(String("index() == {} /* {} */"),variant_index,name))));
__jakt_var_410 = suffix; goto __jakt_label_378;

}
__jakt_label_378:; __jakt_var_410.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(")"));
};/*case end*/
}/*switch end*/
}()
)));
(output += String(")"));
__jakt_var_404 = output; goto __jakt_label_372;

}
__jakt_label_372:; __jakt_var_404.release_value(); }));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::BinaryOp>();NonnullRefPtr<types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
NonnullRefPtr<types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
parser::BinaryOperator const& op = __jakt_match_value.op;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_binary_expression(expression,type_id,lhs,rhs,op)))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NumericConstant>();types::CheckedNumericConstant const& val = __jakt_match_value.val;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_411; {
String const suffix = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I64>();
return JaktInternal::ExplicitValue(String("LL"));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U64>();
return JaktInternal::ExplicitValue(String("ULL"));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::USize>();
return JaktInternal::ExplicitValue(String("ULL"));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(String(""));
};/*case end*/
}/*switch end*/
}()
));
String const type_name = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::USize>();
return JaktInternal::ExplicitValue(String("size_t"));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(type_id)))));
};/*case end*/
}/*switch end*/
}()
));
__jakt_var_411 = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.index()) {
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::F32>();
f32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::F64>();
f64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I8>();
i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I16>();
i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I32>();
i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I64>();
i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U8>();
u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U16>();
u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U32>();
u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U64>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::USize>();
u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(String("static_cast<{}>({}{})"),type_name,val,suffix))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)); goto __jakt_label_379;

}
__jakt_label_379:; __jakt_var_411.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NamespacedVar>();JaktInternal::Array<types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
types::CheckedVariable const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_412; {
String output = String("");
{
JaktInternal::ArrayIterator<types::CheckedNamespace> _magic = ((namespaces).iterator());
for (;;){
JaktInternal::Optional<types::CheckedNamespace> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedNamespace ns = (_magic_value.value());
{
(output += (((ns).name) + String("::")));
}

}
}

__jakt_var_412 = (output + ((var).name)); goto __jakt_label_380;

}
__jakt_label_380:; __jakt_var_412.release_value(); }));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Match>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Array<types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
types::TypeId const& type_id = __jakt_match_value.type_id;
bool const& all_variants_constant = __jakt_match_value.all_variants_constant;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_match(expr,match_cases,type_id,all_variants_constant)))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::EnumVariantArg>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedEnumVariantBinding const& arg = __jakt_match_value.arg;
types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_413; {
String const var_name = TRY((((*this).codegen_expression(expr))));
String const enum_type = TRY((((*this).codegen_type_possibly_as_namespace(((expr)->type()),true))));
String const variant_name = ((enum_variant).name());
String arg_name = String("value");
if (((enum_variant).index() == 3 /* StructLike */)){
(arg_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); }));
}
String const cpp_deref_operator = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((((((*this).program))->get_enum(((enum_variant).enum_id())))).is_boxed));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String("->"));
}
else {
return JaktInternal::ExplicitValue(String("."));
}
}()))
;
__jakt_var_413 = TRY((String::formatted(String("({}{}get<{}::{}>()).{}"),var_name,cpp_deref_operator,enum_type,variant_name,arg_name))); goto __jakt_label_381;

}
__jakt_label_381:; __jakt_var_413.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktArray>();JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
utility::Span const& span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
types::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_414; {
String output = String("");
if (((repeat).has_value())){
NonnullRefPtr<types::CheckedExpression> const repeat_val = ((repeat).value());
(output += String("("));
(output += TRY((((*this).current_error_handler()))));
(output += String("((Array<"));
(output += TRY((((*this).codegen_type(inner_type_id)))));
(output += String(">::filled("));
(output += TRY((((*this).codegen_expression(repeat_val)))));
(output += String(", "));
(output += TRY((((*this).codegen_expression(((vals)[static_cast<i64>(0LL)]))))));
(output += String("))))"));
}
else {
(output += String("("));
(output += TRY((((*this).current_error_handler()))));
(output += String("((Array<"));
(output += TRY((((*this).codegen_type(inner_type_id)))));
(output += String(">::create_with({"));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedExpression> val = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_expression(val)))));
}

}
}

(output += String("}))))"));
}

__jakt_var_414 = output; goto __jakt_label_382;

}
__jakt_label_382:; __jakt_var_414.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktDictionary>();JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
types::TypeId const& key_type_id = __jakt_match_value.key_type_id;
types::TypeId const& value_type_id = __jakt_match_value.value_type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_415; {
String output = TRY((String::formatted(String("({}((Dictionary<{}, {}>::create_with_entries({{"),TRY((((*this).current_error_handler()))),TRY((((*this).codegen_type(key_type_id)))),TRY((((*this).codegen_type(value_type_id)))))));
bool first = true;
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

if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += String("{"));
(output += TRY((((*this).codegen_expression(key)))));
(output += String(", "));
(output += TRY((((*this).codegen_expression(value)))));
(output += String("}"));
}

}
}

(output += String("}))))"));
__jakt_var_415 = output; goto __jakt_label_383;

}
__jakt_label_383:; __jakt_var_415.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktSet>();JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
types::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_416; {
String output = String("");
(output += TRY((String::formatted(String("({}((Set<{}>::create_with_values({{"),TRY((((*this).current_error_handler()))),TRY((((*this).codegen_type(inner_type_id))))))));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedExpression> value = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_expression(value)))));
}

}
}

(output += String("}))))"));
__jakt_var_416 = output; goto __jakt_label_384;

}
__jakt_label_384:; __jakt_var_416.release_value(); }));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktTuple>();JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_417; {
String output = String("");
(output += String("(Tuple{"));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedExpression> val = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_expression(val)))));
}

}
}

(output += String("})"));
__jakt_var_417 = output; goto __jakt_label_385;

}
__jakt_label_385:; __jakt_var_417.release_value(); }));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Function>();JaktInternal::Array<types::CheckedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::Array<types::CheckedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
types::CheckedBlock const& block = __jakt_match_value.block;
types::TypeId const& return_type_id = __jakt_match_value.return_type_id;
JaktInternal::Optional<types::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_418; {
JaktInternal::Array<String> generated_captures = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<types::CheckedCapture> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedCapture capture = (_magic_value.value());
{
TRY((((generated_captures).push(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = capture;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedCapture::ByValue>();return JaktInternal::ExplicitValue(((capture).name()));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedCapture::ByReference>();return JaktInternal::ExplicitValue(TRY((String::formatted(String("&{}"),((capture).name())))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedCapture::ByMutableReference>();return JaktInternal::ExplicitValue(TRY((String::formatted(String("&{}"),((capture).name())))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
))))));
}

}
}

JaktInternal::Array<String> generated_params = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((generated_params).push(TRY((String::formatted(String("{} {}"),TRY((((*this).codegen_type(((((param).variable)).type_id))))),((((param).variable)).name))))))));
}

}
}

String const return_type = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (can_throw);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((String::formatted(String("ErrorOr<{}>"),TRY((((*this).codegen_type(return_type_id))))))));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(return_type_id)))));
}
}()))
;
String block_output = String("");
if (((pseudo_function_id).has_value())){
NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function((pseudo_function_id.value())));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function_);
ScopeGuard __jakt_var_419([&] {
(((*this).current_function) = previous_function);
});
(block_output = TRY((((*this).codegen_block(block)))));
}
else {
(block_output = TRY((((*this).codegen_block(block)))));
}

__jakt_var_418 = TRY((String::formatted(String("[{}]({}) -> {} {}"),utility::join(generated_captures,String(", ")),utility::join(generated_params,String(", ")),return_type,block_output))); goto __jakt_label_386;

}
__jakt_label_386:; __jakt_var_418.release_value(); }));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::TryBlock>();NonnullRefPtr<types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
String const& error_name = __jakt_match_value.error_name;
types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_420; {
String output = String("");
String const try_var = TRY((((*this).fresh_var())));
(output += String("auto "));
(output += try_var);
(output += String(" = [&]() -> ErrorOr<void> {"));
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((((*this).control_flow_state)).passes_through_match) = false);
(((((*this).control_flow_state)).passes_through_try) = true);
(output += TRY((((*this).codegen_statement(stmt)))));
(output += String(";"));
(output += String("return {};"));
(output += String("}();\n"));
(output += String("if ("));
(output += try_var);
(output += String(".is_error()) {"));
if ((!(((error_name).is_empty())))){
(output += String("auto "));
(output += error_name);
(output += String(" = "));
(output += try_var);
(output += String(".release_error();"));
}
(output += TRY((((*this).codegen_block(catch_block)))));
(((*this).control_flow_state) = last_control_flow);
(output += String("}"));
__jakt_var_420 = output; goto __jakt_label_387;

}
__jakt_label_387:; __jakt_var_420.release_value(); }));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Try>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<types::CheckedBlock> const& catch_block = __jakt_match_value.catch_block;
JaktInternal::Optional<String> const& catch_name = __jakt_match_value.catch_name;
utility::Span const& span = __jakt_match_value.span;
types::TypeId const& type_id = __jakt_match_value.type_id;
types::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_421; {
String output = String("");
String const fresh_var = TRY((((*this).fresh_var())));
bool const is_void = ((inner_type_id).equals(types::void_type_id()));
String const try_var = TRY((((*this).fresh_var())));
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((((*this).control_flow_state)).passes_through_match) = false);
(((((*this).control_flow_state)).passes_through_try) = true);
ScopeGuard __jakt_var_422([&] {
{
(((*this).control_flow_state) = last_control_flow);
}

});
if ((!(is_void))){
(output += String("({ Optional<"));
(output += TRY((((*this).codegen_type(inner_type_id)))));
(output += String("> "));
(output += fresh_var);
(output += String(";\n"));
}
(output += String("auto "));
(output += try_var);
(output += String(" = [&]() -> ErrorOr<"));
(output += TRY((((*this).codegen_type(inner_type_id)))));
(output += String("> { return "));
(output += TRY((((*this).codegen_expression(expr)))));
if (is_void){
(output += String(", ErrorOr<void>{}"));
}
(output += String("; }();\n"));
if (((catch_block).has_value())){
(output += String("if ("));
(output += try_var);
(output += String(".is_error()) {"));
if (((catch_name).has_value())){
(output += String("auto "));
(output += (catch_name.value()));
(output += String(" = "));
(output += try_var);
(output += String(".release_error();\n"));
}
if ((((((catch_block.value())).yielded_type)).has_value())){
(output += fresh_var);
(output += String(" = ("));
(output += TRY((((*this).codegen_block((catch_block.value()))))));
(output += String(");\n"));
}
else {
(output += TRY((((*this).codegen_block((catch_block.value()))))));
}

if ((!(is_void))){
(output += String("} else {"));
(output += fresh_var);
(output += String(" = "));
(output += try_var);
(output += String(".release_value();\n"));
}
(output += String("}\n"));
}
else if ((!(is_void))){
(output += String("if (!"));
(output += try_var);
(output += String(".is_error()) "));
(output += fresh_var);
(output += String(" = "));
(output += try_var);
(output += String(".release_value();\n"));
}
if ((!(is_void))){
(output += fresh_var);
if (((catch_block).has_value())){
(output += String(".release_value()"));
}
(output += String("; })"));
}
__jakt_var_421 = output; goto __jakt_label_388;

}
__jakt_label_388:; __jakt_var_421.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_423; {
utility::todo(TRY((String::formatted(String("codegen_expression else: {}"),expression))));
__jakt_var_423 = String(""); goto __jakt_label_389;

}
__jakt_label_389:; __jakt_var_423.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Array<String>> codegen::CodeGenerator::extract_dependencies_from_struct(types::StructId const struct_id,JaktInternal::Dictionary<String,JaktInternal::Array<String>> const dependency_graph,bool const top_level,JaktInternal::Array<types::TypeId> const args) const {
{
JaktInternal::Array<String> dependencies = (TRY((Array<String>::create_with({}))));
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if ((((((struct_).definition_linkage)).index() == 1 /* External */) && (((struct_).name) != String("Optional")))){
return (dependencies);
}
if ((((((struct_).record_type)).index() == 1 /* Class */) && (!(top_level)))){
return (dependencies);
}
if ((!(((args).is_empty())))){
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId inner_type = (_magic_value.value());
{
JaktInternal::Array<String> const inner_dependencies = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<String>, ErrorOr<JaktInternal::Array<String>>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(inner_type));
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from(inner_type,dependency_graph,false)))));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from(inner_type,dependency_graph,false)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
));
{
JaktInternal::ArrayIterator<String> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

}

}
}

}
JaktInternal::Optional<types::StructId> super_struct_id = ((struct_).super_struct_id);
while (((super_struct_id).has_value())){
types::CheckedStruct const super_struct = ((((*this).program))->get_struct((super_struct_id.value())));
TRY((((dependencies).push(TRY((((((super_struct).type_id)).to_string())))))));
(super_struct_id = ((super_struct).super_struct_id));
}
TRY((((dependencies).push(TRY((((((struct_).type_id)).to_string())))))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::TypeId const type_id = ((((((*this).program))->get_variable(((field).variable_id)))).type_id);
JaktInternal::Array<String> const inner_dependencies = TRY((((*this).extract_dependencies_from(type_id,dependency_graph,false))));
{
JaktInternal::ArrayIterator<String> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

}

}
}

return (dependencies);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_function_in_namespace(NonnullRefPtr<types::CheckedFunction> const function_,JaktInternal::Optional<types::TypeId> const containing_struct,bool const as_method) {
{
if ((!(((((((function_)->generics))->params)).is_empty())))){
if (((((function_)->linkage)).index() == 1 /* External */)){
return (String(""));
}
}
String output = String("");
(output += TRY((((*this).codegen_function_generic_parameters(function_)))));
bool const is_main = ((((function_)->name) == String("main")) && (!(((containing_struct).has_value()))));
if (((((function_)->return_type_id)).equals(types::never_type_id()))){
(output += String("[[noreturn]] "));
}
if (is_main){
(output += String("ErrorOr<int>"));
}
else {
if ((as_method && ((function_)->is_static()))){
(output += String("static "));
}
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((function_)->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((String::formatted(String("ErrorOr<{}>"),TRY((((*this).codegen_type(((function_)->return_type_id)))))))));
}
else {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(((function_)->return_type_id))))));
}
}()))
);
}

(output += String(" "));
if (is_main){
(output += String("main"));
}
else {
String const qualifier = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((containing_struct).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type_possibly_as_namespace((containing_struct.value()),true)))));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
if ((!(((qualifier).is_empty())))){
(output += qualifier);
(output += String("::"));
}
(output += ((function_)->name));
}

(output += String("("));
if ((is_main && ((((function_)->params)).is_empty()))){
(output += String("Array<String>"));
}
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
types::CheckedVariable const variable = ((param).variable);
if ((((variable).name) == String("this"))){
continue;
}
if ((!(first))){
(output += String(","));
}
else {
(first = false);
}

NonnullRefPtr<types::Type> const variable_type = ((((*this).program))->get_type(((variable).type_id)));
(output += TRY((((*this).codegen_type(((variable).type_id))))));
(output += String(" "));
if (((!(((variable).is_mutable))) && (!((((variable_type)->index() == 27 /* Reference */) || ((variable_type)->index() == 28 /* MutableReference */)))))){
(output += String("const "));
}
(output += ((variable).name));
}

}
}

(output += String(")"));
if (((!(((function_)->is_static()))) && (!(((function_)->is_mutating()))))){
(output += String(" const"));
}
(output += String(" {\n"));
if (is_main){
(output += String("\n\n            #ifdef _WIN32\n            SetConsoleOutputCP(CP_UTF8);\n            // Enable buffering to prevent VS from chopping up UTF-8 byte sequences\n            setvbuf(stdout, nullptr, _IOFBF, 1000);\n            #endif\n"));
}
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((last_control_flow).enter_function()));
String const block = TRY((((*this).codegen_block(((function_)->block)))));
(((*this).control_flow_state) = last_control_flow);
(output += block);
if (is_main){
(output += String("return 0;\n"));
}
else {
if ((((function_)->can_throw) && ((((function_)->return_type_id)).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } ))))){
(output += String("return {};\n"));
}
}

(output += String("}\n"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_method_call(NonnullRefPtr<types::CheckedExpression> const expr,types::CheckedCall const call,bool const is_optional) {
{
String output = String("");
if (((call).callee_throws)){
(output += TRY((((*this).current_error_handler()))));
(output += String("(("));
}
String const object = TRY((((*this).codegen_expression_and_deref_if_generic_and_needed(expr))));
(output += String("(("));
(output += object);
(output += String(")"));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((expr)->type())));
switch(__jakt_match_variant.index()) {
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
{
(output += String("->"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
{
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
if ((((((struct_).record_type)).index() == 1 /* Class */) && (object != String("*this")))){
(output += String("->"));
}
else {
(output += String("."));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
{
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
if ((((((struct_).record_type)).index() == 1 /* Class */) && (object != String("*this")))){
(output += String("->"));
}
else {
(output += String("."));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(id));
if ((((enum_).is_boxed) && (object != String("*this")))){
(output += String("->"));
}
else {
(output += String("."));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
(output += String("."));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
if (is_optional){
(output += String("map([&](auto& _value) { return _value."));
}
(output += ((call).name));
(output += String("("));
bool first = true;
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

if (first){
(first = false);
}
else {
(output += String(","));
}

(output += TRY((((*this).codegen_expression(expr)))));
}

}
}

(output += String(")"));
if (is_optional){
(output += String("; })"));
}
(output += String(")"));
if (((call).callee_throws)){
(output += String("))"));
}
return (output);
}
}

codegen::CodeGenerator::CodeGenerator(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, codegen::ControlFlowState a_control_flow_state, JaktInternal::Array<JaktInternal::Tuple<String,String>> a_entered_yieldable_blocks, String a_deferred_output, JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> a_current_function, bool a_inside_defer, codegen::CodegenDebugInfo a_debug_info, JaktInternal::Array<String> a_namespace_stack, size_t a_fresh_var_counter, size_t a_fresh_label_counter) :compiler(a_compiler), program(a_program), control_flow_state(a_control_flow_state), entered_yieldable_blocks(a_entered_yieldable_blocks), deferred_output(a_deferred_output), current_function(a_current_function), inside_defer(a_inside_defer), debug_info(a_debug_info), namespace_stack(a_namespace_stack), fresh_var_counter(a_fresh_var_counter), fresh_label_counter(a_fresh_label_counter){}

ErrorOr<String> codegen::CodeGenerator::codegen_struct(types::CheckedStruct const struct_) {
{
String output = String("");
if (((((struct_).definition_linkage)).index() == 1 /* External */)){
return (String(""));
}
JaktInternal::Array<String> generic_parameter_names = (TRY((Array<String>::create_with({}))));
if ((!(((((struct_).generic_parameters)).is_empty())))){
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
TRY((((generic_parameter_names).push(TRY((((*this).codegen_type(((generic_parameter).type_id)))))))));
}

}
}

(output += TRY((String::formatted(String("template <{}>"),utility::join(TRY((utility::prepend_to_each(generic_parameter_names,String("typename ")))),String(", "))))));
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Class>();{
String class_name_with_generics = String("");
(class_name_with_generics += ((struct_).name));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if ((!(first))){
(class_name_with_generics += String(", "));
}
else {
(class_name_with_generics += String("<"));
(first = false);
}

(class_name_with_generics += TRY((((*this).codegen_type(((generic_parameter).type_id))))));
}

}
}

if ((!(((((struct_).generic_parameters)).is_empty())))){
(class_name_with_generics += String(">"));
}
if (((((struct_).super_struct_id)).has_value())){
types::CheckedStruct const super_struct = ((((*this).program))->get_struct((((struct_).super_struct_id).value())));
(output += TRY((String::formatted(String("class {}: public {} {{\n"),((struct_).name),((super_struct).name)))));
}
else {
(output += TRY((String::formatted(String("class {} : public RefCounted<{}>, public Weakable<{}> {{\n"),((struct_).name),class_name_with_generics,class_name_with_generics))));
}

(output += String("  public:\n"));
(output += TRY((String::formatted(String("virtual ~{}() = default;\n"),((struct_).name)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::Struct>();{
(output += TRY((String::formatted(String("struct {}"),((struct_).name)))));
(output += String(" {\n"));
(output += String("  public:\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::SumEnum>();{
utility::todo(String("codegen_struct SumEnum"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::RecordType::ValueEnum>();{
utility::todo(String("codegen_struct ValueEnum"));
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
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
types::CheckedVariable const variable = ((((*this).program))->get_variable(((field).variable_id)));
(output += TRY((((*this).codegen_type(((variable).type_id))))));
(output += String(" "));
(output += ((variable).name));
(output += String(";"));
}

}
}

NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((struct_).scope_id)))));
{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> fn = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(((fn).get<1>())));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function_id = ((*this).current_function);
(((*this).current_function) = static_cast<JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>>>(function_));
ScopeGuard __jakt_var_424([&] {
(((*this).current_function) = previous_function_id);
});
if (((((function_)->type)).index() == 1 /* ImplicitConstructor */)){
if (((((struct_).generic_parameters)).is_empty())){
(output += TRY((((*this).codegen_constructor_predecl(function_)))));
}
else {
(output += TRY((((*this).codegen_constructor(function_,true)))));
}

(output += String("\n"));
}
else {
if ((((((struct_).generic_parameters)).is_empty()) && ((((((function_)->generics))->params)).is_empty()))){
(output += TRY((((*this).codegen_function_predecl(function_,true)))));
}
else {
(output += TRY((((*this).codegen_function(function_,true)))));
}

}

}

}
}

if (((((struct_).generic_parameters)).is_empty())){
(output += String("ErrorOr<String> debug_description() const;\n"));
}
else {
(output += TRY((((*this).codegen_debug_description_getter(struct_,true)))));
}

(output += String("};"));
(((*this).deferred_output) += TRY((((*this).codegen_ak_formatter(((struct_).name),generic_parameter_names)))));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_enum_predecl(types::CheckedEnum const enum_) {
{
String output = String("");
if ((!(((((enum_).underlying_type_id)).equals(types::void_type_id()))))){
if (((((*this).program))->is_integer(((enum_).underlying_type_id)))){
return (TRY((String::formatted(String("enum class {}: {};"),((enum_).name),TRY((((*this).codegen_type(((enum_).underlying_type_id)))))))));
}
else {
utility::todo(String("Enums with a non-integer underlying type"));
}

}
bool const is_generic = (!(((((enum_).generic_parameters)).is_empty())));
JaktInternal::Array<String> template_args_array = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if (((((((*this).program))->get_type(((generic_parameter).type_id))))->index() == 18 /* TypeVariable */)){
String const name = (((((*this).program))->get_type(((generic_parameter).type_id)))->get<types::Type::TypeVariable>()).value;
TRY((((template_args_array).push((String("typename ") + name)))));
}
}

}
}

String template_args = utility::join(template_args_array,String(", "));
(output += (TRY((String::formatted(String("namespace {}_Details"),((enum_).name)))) + String(" {\n")));
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
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& name = __jakt_match_value.name;
{
if (is_generic){
(output += TRY((String::formatted(String("template<{}>\n"),template_args))));
}
(output += TRY((String::formatted(String("struct {};\n"),name))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& name = __jakt_match_value.name;
{
if (is_generic){
(output += TRY((String::formatted(String("template<{}>\n"),template_args))));
}
(output += TRY((String::formatted(String("struct {};\n"),name))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& name = __jakt_match_value.name;
{
if (is_generic){
(output += TRY((String::formatted(String("template<{}>\n"),template_args))));
}
(output += TRY((String::formatted(String("struct {};\n"),name))));
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

(output += String("}\n"));
if (is_generic){
(output += TRY((String::formatted(String("template<{}>\n"),template_args))));
}
(output += TRY((String::formatted(String("struct {};\n"),((enum_).name)))));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_binary_expression(NonnullRefPtr<types::CheckedExpression> const expression,types::TypeId const type_id,NonnullRefPtr<types::CheckedExpression> const lhs,NonnullRefPtr<types::CheckedExpression> const rhs,parser::BinaryOperator const op) {
{
if (((op).index() == 20 /* NoneCoalescing */)){
types::TypeId const rhs_type_id = ((rhs)->type());
NonnullRefPtr<types::Type> const rhs_type = ((((*this).program))->get_type(rhs_type_id));
bool const rhs_can_throw = ((rhs)->can_throw());
String output = String("");
if (rhs_can_throw){
(output += TRY((((*this).current_error_handler()))));
(output += String("(("));
}
(output += TRY((((*this).codegen_expression(lhs)))));
if (((rhs_type)->index() == 19 /* GenericInstance */)){
types::StructId const id = (rhs_type->get<types::Type::GenericInstance>()).id;
if ((((((((*this).program))->get_struct(id))).name) == String("Optional"))){
if (rhs_can_throw){
(output += String(".try_value_or_lazy_evaluated_optional"));
}
else {
(output += String(".value_or_lazy_evaluated_optional"));
}

}
else {
if (rhs_can_throw){
(output += String(".try_value_or_lazy_evaluated"));
}
else {
(output += String(".value_or_lazy_evaluated"));
}

}

}
else {
if (rhs_can_throw){
(output += String(".try_value_or_lazy_evaluated"));
}
else {
(output += String(".value_or_lazy_evaluated"));
}

}

if (rhs_can_throw){
(output += String("([&]() -> ErrorOr<"));
(output += TRY((((*this).codegen_type(rhs_type_id)))));
(output += String("> { return "));
}
else {
(output += String("([&] { return "));
}

(output += TRY((((*this).codegen_expression(rhs)))));
(output += String("; })"));
if (rhs_can_throw){
(output += String("))"));
}
return (output);
}
if (((op).index() == 32 /* NoneCoalescingAssign */)){
String output = TRY((((*this).codegen_expression(lhs))));
(output += String(".lazy_emplace([&] { return "));
(output += TRY((((*this).codegen_expression(rhs)))));
(output += String("; })"));
return (output);
}
if (((op).index() == 17 /* ArithmeticRightShift */)){
String output = String("JaktInternal::arithmetic_shift_right(");
(output += TRY((((*this).codegen_expression(lhs)))));
(output += String(","));
(output += TRY((((*this).codegen_expression(rhs)))));
(output += String(")"));
return (output);
}
if ((((op).index() == 21 /* Assign */) && ((lhs)->index() == 13 /* IndexedDictionary */))){
NonnullRefPtr<types::CheckedExpression> const expr = (lhs->get<types::CheckedExpression::IndexedDictionary>()).expr;
NonnullRefPtr<types::CheckedExpression> const index = (lhs->get<types::CheckedExpression::IndexedDictionary>()).index;
return (TRY((String::formatted(String("{}({}.set({}, {}))"),TRY((((*this).current_error_handler()))),TRY((((*this).codegen_expression(expr)))),TRY((((*this).codegen_expression(index)))),TRY((((*this).codegen_expression(rhs))))))));
}
if (((((*this).program))->is_integer(type_id))){
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Add>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Subtract>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Multiply>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Divide>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Modulo>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::AddAssign>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::SubtractAssign>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::MultiplyAssign>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::DivideAssign>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::ModuloAssign>();
{
if (((((*this).compiler))->optimize)){
return (((String("(") + TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
}
else {
return (((String("(") + TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,op,type_id))))) + String(")")));
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
String output = String("(");
(output += TRY((((*this).codegen_expression(lhs)))));
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Add>();
return JaktInternal::ExplicitValue(String(" + "));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Subtract>();
return JaktInternal::ExplicitValue(String(" - "));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Multiply>();
return JaktInternal::ExplicitValue(String(" * "));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Modulo>();
return JaktInternal::ExplicitValue(String(" % "));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Divide>();
return JaktInternal::ExplicitValue(String(" / "));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Assign>();
return JaktInternal::ExplicitValue(String(" = "));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::AddAssign>();
return JaktInternal::ExplicitValue(String(" += "));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::SubtractAssign>();
return JaktInternal::ExplicitValue(String(" -= "));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::MultiplyAssign>();
return JaktInternal::ExplicitValue(String(" *= "));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::ModuloAssign>();
return JaktInternal::ExplicitValue(String(" %= "));
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::DivideAssign>();
return JaktInternal::ExplicitValue(String(" /= "));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseAndAssign>();
return JaktInternal::ExplicitValue(String(" &= "));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseOrAssign>();
return JaktInternal::ExplicitValue(String(" |= "));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseXorAssign>();
return JaktInternal::ExplicitValue(String(" ^= "));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseLeftShiftAssign>();
return JaktInternal::ExplicitValue(String(" <<= "));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseRightShiftAssign>();
return JaktInternal::ExplicitValue(String(" >>= "));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::Equal>();
return JaktInternal::ExplicitValue(String(" == "));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::NotEqual>();
return JaktInternal::ExplicitValue(String(" != "));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::LessThan>();
return JaktInternal::ExplicitValue(String(" < "));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::LessThanOrEqual>();
return JaktInternal::ExplicitValue(String(" <= "));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::GreaterThan>();
return JaktInternal::ExplicitValue(String(" > "));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::GreaterThanOrEqual>();
return JaktInternal::ExplicitValue(String(" >= "));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::LogicalAnd>();
return JaktInternal::ExplicitValue(String(" && "));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::LogicalOr>();
return JaktInternal::ExplicitValue(String(" || "));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseAnd>();
return JaktInternal::ExplicitValue(String(" & "));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseOr>();
return JaktInternal::ExplicitValue(String(" | "));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseXor>();
return JaktInternal::ExplicitValue(String(" ^ "));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::ArithmeticLeftShift>();
return JaktInternal::ExplicitValue(String(" << "));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseLeftShift>();
return JaktInternal::ExplicitValue(String(" << "));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::BitwiseRightShift>();
return JaktInternal::ExplicitValue(String(" >> "));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_425; {
utility::todo(TRY((String::formatted(String("codegen_binary_expression {}"),op))));
__jakt_var_425 = String(""); goto __jakt_label_390;

}
__jakt_label_390:; __jakt_var_425.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
(output += TRY((((*this).codegen_expression(rhs)))));
(output += String(")"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_namespace_predecl(NonnullRefPtr<types::Scope> const scope,NonnullRefPtr<types::Module> const current_module) {
{
if (((((scope)->import_path_if_extern)).has_value())){
return (String(""));
}
String output = String("");
if (((((scope)->namespace_name)).has_value())){
(output += String("namespace "));
(output += (((scope)->namespace_name).value()));
(output += String(" {\n"));
}
{
JaktInternal::DictionaryIterator<String,types::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::StructId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::StructId> ___struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::StructId> const jakt_____struct_id__ = ___struct_id__;
String const _ = ((jakt_____struct_id__).get<0>());
types::StructId const struct_id = ((jakt_____struct_id__).get<1>());

if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
(output += TRY((((*this).codegen_struct_predecl(struct_)))));
(output += String("\n"));
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
JaktInternal::Tuple<String,types::EnumId> ___enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::EnumId> const jakt_____enum_id__ = ___enum_id__;
String const _ = ((jakt_____enum_id__).get<0>());
types::EnumId const enum_id = ((jakt_____enum_id__).get<1>());

if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
(output += TRY((((*this).codegen_enum_predecl(enum_)))));
(output += String("\n"));
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
(output += TRY((((*this).codegen_namespace_predecl(TRY((((((*this).program))->get_scope(child)))),current_module)))));
}

}
}

{
JaktInternal::DictionaryIterator<String,types::FunctionId> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,types::FunctionId>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,types::FunctionId> ___function_id__ = (_magic_value.value());
{
JaktInternal::Tuple<String,types::FunctionId> const jakt_____function_id__ = ___function_id__;
String const _ = ((jakt_____function_id__).get<0>());
types::FunctionId const function_id = ((jakt_____function_id__).get<1>());

if ((!(((((function_id).module)).equals(((current_module)->id)))))){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(function_id));
if (((((function_)->type)).index() == 2 /* ImplicitEnumConstructor */)){
continue;
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function_id = ((*this).current_function);
(((*this).current_function) = static_cast<JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>>>(function_));
ScopeGuard __jakt_var_426([&] {
(((*this).current_function) = previous_function_id);
});
if (((!(((((function_)->type)).index() == 1 /* ImplicitConstructor */))) && (((function_)->name) != String("main")))){
(output += TRY((((*this).codegen_function_predecl(function_,false)))));
(output += String("\n"));
}
}

}
}

if (((((scope)->namespace_name)).has_value())){
(output += String("}\n"));
}
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::current_error_handler() const {
{
if ((((*this).inside_defer) || ((((((*this).current_function)).has_value()) && (((((((*this).current_function).value()))->return_type_id)).equals(types::never_type_id()))) && (!(((((*this).control_flow_state)).passes_through_try)))))){
return (String("MUST"));
}
return (String("TRY"));
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_namespace_qualifier(types::ScopeId const scope_id) const {
{
String output = String("");
JaktInternal::Optional<types::ScopeId> current_scope_id = ((TRY((((((*this).program))->get_scope(scope_id)))))->parent);
while (((current_scope_id).has_value())){
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope((current_scope_id.value())))));
if (((((scope)->namespace_name)).has_value())){
String const namespace_name = (((scope)->namespace_name).value());
(output = TRY((String::formatted(String("{}::{}"),namespace_name,output))));
}
(current_scope_id = ((scope)->parent));
}
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_namespace_path(types::CheckedCall const call) const {
{
String output = String("");
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::ResolvedNamespace> _magic = ((((call).namespace_)).iterator());
for (;;){
JaktInternal::Optional<types::ResolvedNamespace> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ResolvedNamespace namespace_ = (_magic_value.value());
{
if (((index == (JaktInternal::checked_sub<size_t>(((((call).namespace_)).size()),static_cast<size_t>(1ULL)))) && (((namespace_).name) == ((call).name)))){
break;
}
(output += ((namespace_).name));
if (((((namespace_).generic_parameters)).has_value())){
(output += String("<"));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::TypeId> _magic = (((((namespace_).generic_parameters).value())).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId param = (_magic_value.value());
{
(output += TRY((((*this).codegen_type(param)))));
if ((i != (JaktInternal::checked_sub<size_t>((((((namespace_).generic_parameters).value())).size()),static_cast<size_t>(1ULL))))){
(output += String(","));
}
(++(i));
}

}
}

(output += String(">"));
}
(output += String("::"));
(++(index));
}

}
}

return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_type_possibly_as_namespace(types::TypeId const type_id,bool const as_namespace) const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.index()) {
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
return JaktInternal::ExplicitValue(String("size_t"));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::JaktString>();
return JaktInternal::ExplicitValue(String("String"));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CChar>();
return JaktInternal::ExplicitValue(String("char"));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::CInt>();
return JaktInternal::ExplicitValue(String("int"));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Never>();
return JaktInternal::ExplicitValue(String("void"));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((TRY((((*this).codegen_type(type_id)))) + String("*")));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((TRY((((*this).codegen_type(type_id)))) + String(" const&")));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
types::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((TRY((((*this).codegen_type(type_id)))) + String("&")));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_generic_type_instance(id,args,as_namespace)))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_generic_type_instance(id,args,as_namespace)))));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_struct_type(id,as_namespace)))));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_enum_type(id,as_namespace)))));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_generic_enum_instance(id,args,as_namespace)))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::TypeVariable>();
String const& name = __jakt_match_value.value;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::Array<types::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
types::TypeId const& return_type_id = __jakt_match_value.return_type_id;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_427; {
String output = String("Function<");
if (can_throw){
(output += String("ErrorOr<"));
}
(output += TRY((((*this).codegen_type(return_type_id)))));
if (can_throw){
(output += String(">"));
}
(output += String("("));
bool first = true;
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId param = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(output += String(", "));
}

(output += TRY((((*this).codegen_type(param)))));
}

}
}

(output += String(")>"));
__jakt_var_427 = output; goto __jakt_label_391;

}
__jakt_label_391:; __jakt_var_427.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();{
utility::panic(String("Generic trait instance in codegen"));
}
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_428; {
__jakt_var_428 = String("auto"); goto __jakt_label_392;

}
__jakt_label_392:; __jakt_var_428.release_value(); }));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<JaktInternal::Array<String>> codegen::CodeGenerator::extract_dependencies_from(types::TypeId const type_id,JaktInternal::Dictionary<String,JaktInternal::Array<String>> const dependency_graph,bool const top_level) const {
{
JaktInternal::Array<String> dependencies = (TRY((Array<String>::create_with({}))));
if (((dependency_graph).contains(TRY((((type_id).to_string())))))){
{
JaktInternal::ArrayIterator<String> _magic = (((((dependency_graph).get(TRY((((type_id).to_string()))))).value())).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

return (dependencies);
}
NonnullRefPtr<types::Type> const type_ = ((((*this).program))->get_type(type_id));
JaktInternal::Array<String> const inner_dependencies = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Array<String>, ErrorOr<JaktInternal::Array<String>>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from_enum(enum_id,dependency_graph,top_level)))));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from_enum(id,dependency_graph,top_level)))));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from_struct(id,dependency_graph,top_level,(TRY((Array<types::TypeId>::create_with({})))))))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from_struct(id,dependency_graph,top_level,args)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((Array<String>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
));
{
JaktInternal::ArrayIterator<String> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

return (dependencies);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_match_body(types::CheckedMatchBody const body,types::TypeId const return_type_id) {
{
String output = String("");
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
{
(output += TRY((((*this).codegen_block(block)))));
if ((((return_type_id).equals(types::void_type_id())) || ((return_type_id).equals(types::unknown_type_id())))){
(output += String("return JaktInternal::ExplicitValue<void>();\n"));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.value;
{
if ((((((expr)->type())).equals(types::void_type_id())) || (((((expr)->type())).equals(types::unknown_type_id())) && (!(((expr)->index() == 23 /* OptionalNone */)))))){
(output += String("return ("));
(output += TRY((((*this).codegen_expression(expr)))));
(output += String("), JaktInternal::ExplicitValue<void>();\n"));
}
else {
(output += String("return JaktInternal::ExplicitValue("));
(output += TRY((((*this).codegen_expression(expr)))));
(output += String(");\n"));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_function_predecl(NonnullRefPtr<types::CheckedFunction> const function_,bool const as_method) {
{
String output = String("");
if (((!(((((((function_)->generics))->params)).is_empty()))) && ((((function_)->linkage)).index() == 1 /* External */))){
return (String(""));
}
if (((function_)->is_comptime)){
return (String(""));
}
if (((((function_)->type)).index() == 1 /* ImplicitConstructor */)){
return (String(""));
}
if (((((function_)->linkage)).index() == 1 /* External */)){
(output += String("extern "));
}
(output += TRY((((*this).codegen_function_generic_parameters(function_)))));
if (((((function_)->return_type_id)).equals(types::never_type_id()))){
(output += String("[[noreturn]] "));
}
if ((((function_)->name) == String("main"))){
(output += String("ErrorOr<int>"));
}
else {
if ((as_method && ((function_)->is_static()))){
(output += String("static "));
}
if (((function_)->is_virtual)){
(output += String("virtual "));
}
String const naked_return_type = TRY((((*this).codegen_type(((function_)->return_type_id)))));
String const return_type = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((function_)->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((String::formatted(String("ErrorOr<{}>"),naked_return_type))));
}
else {
return JaktInternal::ExplicitValue(naked_return_type);
}
}()))
;
(output += return_type);
}

(output += String(" "));
(output += ((function_)->name));
(output += String("("));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((first && (((((param).variable)).name) == String("this")))){
continue;
}
if (first){
(first = false);
}
else {
(output += String(", "));
}

NonnullRefPtr<types::Type> const param_type = ((((*this).program))->get_type(((((param).variable)).type_id)));
(output += TRY((((*this).codegen_type(((((param).variable)).type_id))))));
(output += String(" "));
if (((!(((((param).variable)).is_mutable))) && (!((((param_type)->index() == 27 /* Reference */) || ((param_type)->index() == 28 /* MutableReference */)))))){
(output += String("const "));
}
(output += ((((param).variable)).name));
}

}
}

(output += String(")"));
if (((!(((function_)->is_static()))) && (!(((function_)->is_mutating()))))){
(output += String(" const"));
}
if (((function_)->is_override)){
(output += String(" override"));
}
(output += String(";"));
(output += String("\n"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::fresh_var() {
{
return (TRY((String::formatted(String("__jakt_var_{}"),((((*this).fresh_var_counter)++))))));
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_block(types::CheckedBlock const block) {
{
String output = String("");
if (((((block).yielded_type)).has_value())){
types::TypeId const yielded_type = (((block).yielded_type).value());
String const type_output = TRY((((*this).codegen_type(yielded_type))));
String const fresh_var = TRY((((*this).fresh_var())));
String const fresh_label = TRY((((*this).fresh_label())));
TRY((((((*this).entered_yieldable_blocks)).push((Tuple{fresh_var, fresh_label})))));
(output += String("({ Optional<"));
(output += type_output);
(output += String("> "));
(output += fresh_var);
(output += String("; "));
}
(output += String("{\n"));
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::CheckedStatement>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::CheckedStatement> statement = (_magic_value.value());
{
(output += TRY((((*this).codegen_statement(statement)))));
}

}
}

(output += String("}\n"));
if (((((block).yielded_type)).has_value())){
JaktInternal::Tuple<String,String> const var_label_ = (((((*this).entered_yieldable_blocks)).pop()).value());
String const var = ((var_label_).get<0>());
String const label = ((var_label_).get<1>());

(output += label);
(output += String(":; "));
(output += var);
if ((!(((block).yielded_none)))){
(output += String(".release_value()"));
}
(output += String("; })"));
}
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_checked_binary_op_assignment(NonnullRefPtr<types::CheckedExpression> const lhs,NonnullRefPtr<types::CheckedExpression> const rhs,parser::BinaryOperator const op,types::TypeId const type_id) {
{
String output = String("");
(output += String("{"));
(output += String("auto& _jakt_ref = "));
(output += TRY((((*this).codegen_expression(lhs)))));
(output += String(";"));
(output += String("_jakt_ref = JaktInternal::"));
(output += JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::AddAssign>();
return JaktInternal::ExplicitValue(String("checked_add"));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::SubtractAssign>();
return JaktInternal::ExplicitValue(String("checked_sub"));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::MultiplyAssign>();
return JaktInternal::ExplicitValue(String("checked_mul"));
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::DivideAssign>();
return JaktInternal::ExplicitValue(String("checked_div"));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename parser::BinaryOperator::ModuloAssign>();
return JaktInternal::ExplicitValue(String("checked_mod"));
};/*case end*/
default: {
{
utility::panic(TRY((String::formatted(String("Checked binary operation assignment codegen is not supported for BinaryOperator::{}"),op))));
}
};/*case end*/
}/*switch end*/
}()
)));
(output += String("<"));
(output += TRY((((*this).codegen_type(type_id)))));
(output += String(">(_jakt_ref, "));
(output += TRY((((*this).codegen_expression(rhs)))));
(output += String(");"));
(output += String("}"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_enum_type(types::EnumId const id,bool const as_namespace) const {
{
String output = String("");
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((id).module)));
types::CheckedEnum const checked_enum = ((((*this).program))->get_enum(id));
if (((!(as_namespace)) && ((checked_enum).is_boxed))){
(output += String("NonnullRefPtr<"));
if ((!((((type_module)->is_root) || ((((type_module)->id)).equals(types::ModuleId(static_cast<size_t>(0ULL)))))))){
(output += ((type_module)->name));
(output += String("::"));
}
String const qualifier = TRY((((*this).codegen_namespace_qualifier(((checked_enum).scope_id)))));
if ((!(((qualifier).is_empty())))){
(output += String("typename "));
(output += qualifier);
}
(output += ((checked_enum).name));
(output += String(">"));
}
else {
if ((!((((type_module)->is_root) || ((((type_module)->id)).equals(types::ModuleId(static_cast<size_t>(0ULL)))))))){
(output += ((type_module)->name));
(output += String("::"));
}
String const qualifier = TRY((((*this).codegen_namespace_qualifier(((checked_enum).scope_id)))));
if ((!(((qualifier).is_empty())))){
(output += qualifier);
}
(output += ((checked_enum).name));
}

return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_constructor(NonnullRefPtr<types::CheckedFunction> const function_,bool const is_inline) {
{
types::TypeId const type_id = ((function_)->return_type_id);
NonnullRefPtr<types::Type> const type_ = ((((*this).program))->get_type(type_id));
if (((type_)->index() == 23 /* Struct */)){
types::StructId const struct_id = (type_->get<types::Type::Struct>()).value;
types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
String const qualified_name = TRY((((*this).codegen_type_possibly_as_namespace(type_id,true))));
String output = String("");
if (((!(is_inline)) && (!(((((structure).generic_parameters)).is_empty()))))){
(output += String("template <"));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((structure).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(output += String(","));
}

(output += String("typename "));
(output += TRY((((*this).codegen_type(((param).type_id))))));
}

}
}

(output += String(">\n"));
}
if (((((structure).record_type)).index() == 1 /* Class */)){
if (is_inline){
(output += ((function_)->name));
(output += String("("));
}
else {
(output += TRY((String::formatted(String("{}::{}("),qualified_name,((function_)->name)))));
}

bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

types::TypeId const param_type_id = ((((param).variable)).type_id);
(output += TRY((((*this).codegen_type(param_type_id)))));
(output += String("&& a_"));
(output += ((((param).variable)).name));
}

}
}

(output += String(")"));
if ((!(((((function_)->params)).is_empty())))){
(output += String(": "));
JaktInternal::Array<String> initializers = (TRY((Array<String>::create_with({}))));
size_t const parent_constructor_parameter_count = (JaktInternal::checked_sub<size_t>(((((function_)->params)).size()),((((structure).fields)).size())));
if ((parent_constructor_parameter_count > static_cast<size_t>(0ULL))){
String parent_initializer = String("");
(parent_initializer += ((((((*this).program))->get_struct((((structure).super_struct_id).value())))).name));
(parent_initializer += String("("));
JaktInternal::Array<String> strings = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((((function_)->params))[(JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parent_constructor_parameter_count)})])).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((strings).push(((String("move(a_") + ((((param).variable)).name)) + String(")"))))));
}

}
}

(parent_initializer += utility::join(strings,String(", ")));
(parent_initializer += String(")"));
TRY((((initializers).push(parent_initializer))));
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(parent_constructor_parameter_count),static_cast<size_t>(((((function_)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedParameter const param = ((((function_)->params))[i]);
TRY((((initializers).push((((((((param).variable)).name) + String("(move(a_")) + ((((param).variable)).name)) + String("))"))))));
}

}
}

(output += utility::join(initializers,String(", ")));
}
(output += String("{}\n"));
String class_name_with_generics = String("");
(class_name_with_generics += ((structure).name));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((structure).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if ((!(first))){
(class_name_with_generics += String(", "));
}
else {
(class_name_with_generics += String("<"));
(first = false);
}

(class_name_with_generics += TRY((((*this).codegen_type(((generic_parameter).type_id))))));
}

}
}

if ((!(((((structure).generic_parameters)).is_empty())))){
(class_name_with_generics += String(">"));
}
if (is_inline){
(output += String("static "));
}
String const qualified_namespace = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (is_inline);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(String(""));
}
else {
return JaktInternal::ExplicitValue((qualified_name + String("::")));
}
}()))
;
(output += TRY((String::formatted(String("ErrorOr<NonnullRefPtr<{}>> {}create"),class_name_with_generics,qualified_namespace))));
(output += String("("));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_type(((((param).variable)).type_id))))));
(output += String(" "));
(output += ((((param).variable)).name));
}

}
}

(output += TRY((String::formatted(String(") {{ auto o = {}(adopt_nonnull_ref_or_enomem(new (nothrow) {} ("),TRY((((*this).current_error_handler()))),class_name_with_generics))));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += String("move("));
(output += ((((param).variable)).name));
(output += String(")"));
}

}
}

(output += String("))); return o; }"));
return (output);
}
if ((!(is_inline))){
(output += qualified_name);
(output += String("::"));
}
(output += ((function_)->name));
(output += String("("));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_type(((((param).variable)).type_id))))));
(output += String(" a_"));
(output += ((((param).variable)).name));
}

}
}

(output += String(") "));
if ((!(((((function_)->params)).is_empty())))){
(output += String(":"));
}
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += ((((param).variable)).name));
(output += String("(a_"));
(output += ((((param).variable)).name));
(output += String(")"));
}

}
}

(output += String("{}\n"));
return (output);
}
else {
utility::panic(String("internal error: call to a constructor, but not a struct/class type"));
}

}
}

ErrorOr<String> codegen::CodeGenerator::codegen_enum_debug_description_getter(types::CheckedEnum const enum_,bool const is_inline) {
{
String output = String("");
if (((!(is_inline)) && (!(((((enum_).generic_parameters)).is_empty()))))){
(output += String("template <"));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter param = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(output += String(","));
}

(output += String("typename "));
(output += TRY((((*this).codegen_type(((param).type_id))))));
}

}
}

(output += String(">\n"));
}
(output += String("ErrorOr<String> "));
if ((!(is_inline))){
(output += TRY((((*this).codegen_type_possibly_as_namespace(((enum_).type_id),true)))));
(output += String("::"));
}
(output += String("debug_description() const {\n"));
(output += String("auto builder = TRY(StringBuilder::create());\n"));
(output += String("switch (this->index()) {"));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).variants)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedEnumVariant const variant = ((((enum_).variants))[i]);
String const name = ((variant).name());
(output += TRY((String::formatted(String("case {} /* {} */: {{\n"),i,name))));
(output += TRY((String::formatted(String("[[maybe_unused]] auto const& that = this->template get<{}::{}>();\n"),((enum_).name),name))));
(output += TRY((String::formatted(String("TRY(builder.append(\"{}::{}\"));\n"),((enum_).name),name))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();JaktInternal::Array<types::VarId> const& fields = __jakt_match_value.fields;
{
(output += String("TRY(builder.append(\"(\"));\n"));
(output += String("{\n"));
(output += String("JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};\n"));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::VarId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::VarId field = (_magic_value.value());
{
(output += String("TRY(JaktInternal::PrettyPrint::output_indentation(builder));\n"));
types::CheckedVariable const var = ((((*this).program))->get_variable(field));
if (((((*this).program))->is_string(((var).type_id)))){
(output += TRY((String::formatted(String("TRY(builder.appendff(\"{}: \\\"{{}}\\\"\", that.{}));\n"),((var).name),((var).name)))));
}
else {
(output += TRY((String::formatted(String("TRY(builder.appendff(\"{}: {{}}\", that.{}));\n"),((var).name),((var).name)))));
}

if ((i != (JaktInternal::checked_sub<size_t>(((fields).size()),static_cast<size_t>(1ULL))))){
(output += String("TRY(builder.append(\", \"));\n"));
}
((i++));
}

}
}

(output += String("}\n"));
(output += String("TRY(builder.append(\")\"));\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();types::TypeId const& type_id = __jakt_match_value.type_id;
{
if (((((*this).program))->is_string(type_id))){
(output += String("TRY(builder.appendff(\"(\\\"{}\\\")\", that.value));\n"));
}
else {
(output += String("TRY(builder.appendff(\"({})\", that.value));\n"));
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
(output += String("break;}\n"));
}

}
}

(output += String("}\nreturn builder.to_string();\n}\n"));
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_enum_match(types::CheckedEnum const enum_,NonnullRefPtr<types::CheckedExpression> const expr,JaktInternal::Array<types::CheckedMatchCase> const match_cases,types::TypeId const type_id,bool const all_variants_constant) {
{
String output = String("");
(output += ((((*this).control_flow_state)).choose_control_flow_macro()));
String const subject = TRY((((*this).codegen_expression(expr))));
bool const needs_deref = (((enum_).is_boxed) && (subject != String("*this")));
if (((((enum_).underlying_type_id)).equals(types::void_type_id()))){
(output += String("(([&]() -> JaktInternal::ExplicitValueOrControlFlow<"));
(output += TRY((((*this).codegen_type(type_id)))));
(output += String(", "));
(output += TRY((((*this).codegen_function_return_type((((*this).current_function).value()))))));
(output += String(">{\n"));
(output += String("auto&& __jakt_match_variant = "));
if (needs_deref){
(output += String("*"));
}
(output += (TRY((((*this).codegen_expression(expr)))) + String(";\n")));
(output += String("switch(__jakt_match_variant.index()) {\n"));
bool has_default = false;
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase match_case = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::EnumVariant>();String const& name = __jakt_match_value.name;
JaktInternal::Array<parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
types::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
size_t const& index = __jakt_match_value.index;
types::ScopeId const& scope_id = __jakt_match_value.scope_id;
types::CheckedMatchBody const& body = __jakt_match_value.body;
{
NonnullRefPtr<types::Type> const enum_type = ((((*this).program))->get_type(subject_type_id));
types::EnumId const enum_id = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::EnumId, ErrorOr<String>>{
auto&& __jakt_match_variant = *enum_type;
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(String("Expected enum type"));
}
};/*case end*/
}/*switch end*/
}()
));
types::CheckedEnum const match_case_enum = ((((*this).program))->get_enum(enum_id));
types::CheckedEnumVariant const variant = ((((match_case_enum).variants))[index]);
(output += (TRY((String::formatted(String("case {}: "),index))) + String("{\n")));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();String const& name = __jakt_match_value.name;
{
(output += TRY((String::formatted(String("auto&& __jakt_match_value = __jakt_match_variant.template get<typename {}::{}>();\n"),TRY((((*this).codegen_type_possibly_as_namespace(subject_type_id,true)))),name))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();String const& name = __jakt_match_value.name;
types::TypeId const& type_id = __jakt_match_value.type_id;
{
(output += TRY((String::formatted(String("auto&& __jakt_match_value = __jakt_match_variant.template get<typename {}::{}>();\n"),TRY((((*this).codegen_type_possibly_as_namespace(subject_type_id,true)))),name))));
if ((!(((args).is_empty())))){
parser::EnumVariantPatternArgument const arg = ((args)[static_cast<i64>(0LL)]);
types::CheckedVariable const var = (TRY((((((*this).program))->find_var_in_scope(scope_id,((arg).binding))))).value());
(output += TRY((String::formatted(String("{} const& {} = __jakt_match_value.value;\n"),TRY((((*this).codegen_type(((var).type_id))))),((arg).binding)))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();String const& name = __jakt_match_value.name;
JaktInternal::Array<types::VarId> const& fields = __jakt_match_value.fields;
{
(output += TRY((String::formatted(String("auto&& __jakt_match_value = __jakt_match_variant.template get<{}::{}>();"),TRY((((*this).codegen_type_possibly_as_namespace(subject_type_id,true)))),name))));
if ((!(((args).is_empty())))){
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument arg = (_magic_value.value());
{
types::CheckedVariable const var = (TRY((((((*this).program))->find_var_in_scope(scope_id,((arg).binding))))).value());
(output += TRY((((*this).codegen_type(((var).type_id))))));
(output += String(" const& "));
(output += ((arg).binding));
(output += String(" = __jakt_match_value."));
(output += ((((arg).name)).value_or(((arg).binding))));
(output += String(";\n"));
}

}
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::todo(TRY((String::formatted(String("codegen_enum_match match variant else: {}"),variant))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
(output += TRY((((*this).codegen_match_body(body,type_id)))));
(output += String("};/*case end*/\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::CatchAll>();types::CheckedMatchBody const& body = __jakt_match_value.body;
{
(has_default = true);
(output += String("default: {\n"));
(output += TRY((((*this).codegen_match_body(body,type_id)))));
(output += String("};/*case end*/\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(String("Matching enum subject with non-enum value"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}

}
}

if ((!(has_default))){
if ((((((enum_).variants)).size()) != ((match_cases).size()))){
utility::panic(String("Inexhaustive match statement"));
}
(output += String("default: VERIFY_NOT_REACHED();"));
}
(output += String("}/*switch end*/\n"));
(output += String("}()\n))"));
}
else {
utility::todo(String("underlying type enum match"));
}

return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_match(NonnullRefPtr<types::CheckedExpression> const expr,JaktInternal::Array<types::CheckedMatchCase> const match_cases,types::TypeId const type_id,bool const all_variants_constant) {
{
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((((*this).control_flow_state)).enter_match()));
String output = String("");
NonnullRefPtr<types::Type> const expr_type = ((((*this).program))->get_type(((expr)->type())));
if (((expr_type)->index() == 24 /* Enum */)){
types::EnumId const enum_id = (expr_type->get<types::Type::Enum>()).value;
(output += TRY((((*this).codegen_enum_match(((((*this).program))->get_enum(enum_id)),expr,match_cases,type_id,all_variants_constant)))));
}
else {
(output += TRY((((*this).codegen_generic_match(expr,match_cases,type_id,all_variants_constant)))));
}

(((*this).control_flow_state) = last_control_flow);
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_function_return_type(NonnullRefPtr<types::CheckedFunction> const function_) {
{
if ((((function_)->is_static()) && (((function_)->name) == String("main")))){
return (String("ErrorOr<int>"));
}
String const type_name = TRY((((*this).codegen_type(((function_)->return_type_id)))));
if (((function_)->can_throw)){
return (TRY((String::formatted(String("ErrorOr<{}>"),type_name))));
}
return (type_name);
}
}

ErrorOr<JaktInternal::Dictionary<String,JaktInternal::Tuple<String,String>>> codegen::CodeGenerator::generate(NonnullRefPtr<compiler::Compiler> const compiler,NonnullRefPtr<types::CheckedProgram> const program,bool const debug_info) {
{
codegen::CodeGenerator generator = codegen::CodeGenerator(compiler,program,codegen::ControlFlowState( codegen::AllowedControlExits { typename codegen::AllowedControlExits::Nothing() } ,false,false,static_cast<size_t>(0ULL)),(TRY((Array<JaktInternal::Tuple<String,String>>::create_with({})))),String(""),JaktInternal::OptionalNone(),false,codegen::CodegenDebugInfo(compiler,(TRY((Dictionary<size_t, JaktInternal::Array<codegen::LineSpan>>::create_with_entries({})))),debug_info),(TRY((Array<String>::create_with({})))),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL));
JaktInternal::Dictionary<String,JaktInternal::Tuple<String,String>> result = (TRY((Dictionary<String, JaktInternal::Tuple<String,String>>::create_with_entries({}))));
String output = String("");
(output += String("#pragma once\n"));
(output += String("#include <lib.h>\n"));
(output += String("#ifdef _WIN32\n"));
(output += String("extern \"C\" __cdecl int SetConsoleOutputCP(unsigned int code_page);\n"));
(output += String("const unsigned int CP_UTF8 = 65001;\n"));
(output += String("#endif\n"));
JaktInternal::Array<types::ModuleId> const sorted_modules = TRY((((generator).topologically_sort_modules())));
(output += String("namespace Jakt {\n"));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((sorted_modules).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t idx = (_magic_value.value());
{
size_t const i = ((((sorted_modules)[(JaktInternal::checked_sub<size_t>(idx,static_cast<size_t>(1ULL)))])).id);
if ((i == static_cast<size_t>(0ULL))){
continue;
}
NonnullRefPtr<types::Module> const module = ((((((generator).program))->modules))[i]);
((((generator).compiler))->dbg_println(TRY((String::formatted(String("generate: module idx: {}, module.name {}"),i,((module)->name))))));
if ((!(((module)->is_root)))){
(output += String("namespace "));
(output += ((module)->name));
(output += String(" {\n"));
}
types::ScopeId const scope_id = types::ScopeId(((module)->id),static_cast<size_t>(0ULL));
NonnullRefPtr<types::Scope> const scope = TRY((((((generator).program))->get_scope(scope_id))));
(output += TRY((((generator).codegen_namespace_predecl(scope,module)))));
if ((!(((module)->is_root)))){
(output += String("}\n"));
}
}

}
}

(output += String("} // namespace Jakt\n"));
TRY((((result).set(String("__unified_forward.h"),(Tuple{output, (((((compiler)->current_file_path()).value())).to_string())})))));
{
JaktInternal::ArrayIterator<bool> _magic = (((TRY((Array<bool>::create_with({true, false}))))).iterator());
for (;;){
JaktInternal::Optional<bool> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
bool as_forward = (_magic_value.value());
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((sorted_modules).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t idx = (_magic_value.value());
{
size_t const i = ((((sorted_modules)[(JaktInternal::checked_sub<size_t>(idx,static_cast<size_t>(1ULL)))])).id);
if ((i == static_cast<size_t>(0ULL))){
continue;
}
NonnullRefPtr<types::Module> const module = ((((((generator).program))->modules))[i]);
((((generator).compiler))->dbg_println(TRY((String::formatted(String("generate: module idx: {}, module.name {} - forward: {}"),i,((module)->name),as_forward)))));
String const header_name = TRY((String::formatted(String("{}.h"),((module)->name))));
String const impl_name = TRY((String::formatted(String("{}.cpp"),((module)->name))));
if (as_forward){
(output = String("#pragma once\n"));
(output += String("#include \"__unified_forward.h\"\n"));
}
else {
(output = TRY((String::formatted(String("#include \"{}\"\n"),header_name))));
}

types::ScopeId const scope_id = types::ScopeId(((module)->id),static_cast<size_t>(0ULL));
NonnullRefPtr<types::Scope> const scope = TRY((((((generator).program))->get_scope(scope_id))));
if (as_forward){
{
JaktInternal::ArrayIterator<types::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<types::ScopeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ScopeId child_scope = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const scope = TRY((((((generator).program))->get_scope(child_scope))));
if (((((scope)->import_path_if_extern)).has_value())){
bool const has_name = ((((scope)->namespace_name)).has_value());
if (has_name){
(output += TRY((String::formatted(String("namespace {} {{\n"),(((scope)->namespace_name).value())))));
}
{
JaktInternal::ArrayIterator<parser::IncludeAction> _magic = ((((scope)->before_extern_include)).iterator());
for (;;){
JaktInternal::Optional<parser::IncludeAction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::IncludeAction action = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Dictionary<String,JaktInternal::Tuple<String,String>>>>{
auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::IncludeAction::Define>();String const& name = __jakt_match_value.name;
String const& value = __jakt_match_value.value;
{
(output += TRY((String::formatted(String("#ifdef {}\n"),name))));
(output += TRY((String::formatted(String("#undef {}\n"),name))));
(output += String("#endif\n"));
(output += TRY((String::formatted(String("#define {} {}\n"),name,value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::IncludeAction::Undefine>();String const& name = __jakt_match_value.name;
{
(output += TRY((String::formatted(String("#ifdef {}\n"),name))));
(output += TRY((String::formatted(String("#undef {}\n"),name))));
(output += String("#endif\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}

}
}

(output += TRY((String::formatted(String("#include <{}>\n"),(((scope)->import_path_if_extern).value())))));
{
JaktInternal::ArrayIterator<parser::IncludeAction> _magic = ((((scope)->after_extern_include)).iterator());
for (;;){
JaktInternal::Optional<parser::IncludeAction> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::IncludeAction action = (_magic_value.value());
{
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Dictionary<String,JaktInternal::Tuple<String,String>>>>{
auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::IncludeAction::Define>();String const& name = __jakt_match_value.name;
String const& value = __jakt_match_value.value;
{
(output += TRY((String::formatted(String("#ifdef {}\n"),name))));
(output += TRY((String::formatted(String("#undef {}\n"),name))));
(output += String("#endif\n"));
(output += TRY((String::formatted(String("#define {} {}\n"),name,value))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<parser::IncludeAction::Undefine>();String const& name = __jakt_match_value.name;
{
(output += TRY((String::formatted(String("#ifdef {}\n"),name))));
(output += TRY((String::formatted(String("#undef {}\n"),name))));
(output += String("#endif\n"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
}

}
}

if (has_name){
(output += ((String(" } // namespace ") + (((scope)->namespace_name).value())) + String("\n")));
}
}
}

}
}

{
JaktInternal::ArrayIterator<types::ModuleId> _magic = ((((module)->imports)).iterator());
for (;;){
JaktInternal::Optional<types::ModuleId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ModuleId id = (_magic_value.value());
{
NonnullRefPtr<types::Module> const module = ((((((generator).program))->modules))[((id).id)]);
(output += TRY((String::formatted(String("#include \"{}.h\"\n"),((module)->name)))));
}

}
}

}
(output += String("namespace Jakt {\n"));
if ((!(((module)->is_root)))){
(output += String("namespace "));
(output += ((module)->name));
(output += String(" {\n"));
TRY((((((generator).namespace_stack)).push(((module)->name)))));
}
(output += TRY((((generator).codegen_namespace(scope,module,as_forward)))));
if ((!(((module)->is_root)))){
JaktInternal::Optional<String> const dummy = ((((generator).namespace_stack)).pop());
}
if ((!(((module)->is_root)))){
(output += String("}\n"));
}
(output += ((generator).deferred_output));
(((generator).deferred_output) = String(""));
(output += String("} // namespace Jakt\n"));
if (as_forward){
TRY((((result).set(header_name,(Tuple{output, ((module)->resolved_import_path)})))));
}
else {
TRY((((result).set(impl_name,(Tuple{output, ((module)->resolved_import_path)})))));
}

}

}
}

}

}
}

return (result);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_call(types::CheckedCall const call) {
{
String output = String("");
if (((call).callee_throws)){
(output += TRY((((*this).current_error_handler()))));
(output += String("(("));
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<String>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == String("print")) {
{
String const helper = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == String("print")) {
return JaktInternal::ExplicitValue(String("out"));
}
else if (__jakt_enum_value == String("println")) {
return JaktInternal::ExplicitValue(String("outln"));
}
else if (__jakt_enum_value == String("eprint")) {
return JaktInternal::ExplicitValue(String("warn"));
}
else if (__jakt_enum_value == String("eprintln")) {
return JaktInternal::ExplicitValue(String("warnln"));
}
else if (__jakt_enum_value == String("format")) {
return JaktInternal::ExplicitValue(String("String::formatted"));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
(output += helper);
(output += String("("));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
String const _ = ((__expr_).get<0>());
NonnullRefPtr<types::CheckedExpression> const expr = ((__expr_).get<1>());

(output += TRY((((*this).codegen_expression(expr)))));
if ((i != (JaktInternal::checked_sub<size_t>(((((call).args)).size()),static_cast<size_t>(1ULL))))){
(output += String(","));
}
}

}
}

(output += String(")"));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("println")) {
{
String const helper = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == String("print")) {
return JaktInternal::ExplicitValue(String("out"));
}
else if (__jakt_enum_value == String("println")) {
return JaktInternal::ExplicitValue(String("outln"));
}
else if (__jakt_enum_value == String("eprint")) {
return JaktInternal::ExplicitValue(String("warn"));
}
else if (__jakt_enum_value == String("eprintln")) {
return JaktInternal::ExplicitValue(String("warnln"));
}
else if (__jakt_enum_value == String("format")) {
return JaktInternal::ExplicitValue(String("String::formatted"));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
(output += helper);
(output += String("("));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
String const _ = ((__expr_).get<0>());
NonnullRefPtr<types::CheckedExpression> const expr = ((__expr_).get<1>());

(output += TRY((((*this).codegen_expression(expr)))));
if ((i != (JaktInternal::checked_sub<size_t>(((((call).args)).size()),static_cast<size_t>(1ULL))))){
(output += String(","));
}
}

}
}

(output += String(")"));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("eprintln")) {
{
String const helper = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == String("print")) {
return JaktInternal::ExplicitValue(String("out"));
}
else if (__jakt_enum_value == String("println")) {
return JaktInternal::ExplicitValue(String("outln"));
}
else if (__jakt_enum_value == String("eprint")) {
return JaktInternal::ExplicitValue(String("warn"));
}
else if (__jakt_enum_value == String("eprintln")) {
return JaktInternal::ExplicitValue(String("warnln"));
}
else if (__jakt_enum_value == String("format")) {
return JaktInternal::ExplicitValue(String("String::formatted"));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
(output += helper);
(output += String("("));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
String const _ = ((__expr_).get<0>());
NonnullRefPtr<types::CheckedExpression> const expr = ((__expr_).get<1>());

(output += TRY((((*this).codegen_expression(expr)))));
if ((i != (JaktInternal::checked_sub<size_t>(((((call).args)).size()),static_cast<size_t>(1ULL))))){
(output += String(","));
}
}

}
}

(output += String(")"));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("eprint")) {
{
String const helper = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == String("print")) {
return JaktInternal::ExplicitValue(String("out"));
}
else if (__jakt_enum_value == String("println")) {
return JaktInternal::ExplicitValue(String("outln"));
}
else if (__jakt_enum_value == String("eprint")) {
return JaktInternal::ExplicitValue(String("warn"));
}
else if (__jakt_enum_value == String("eprintln")) {
return JaktInternal::ExplicitValue(String("warnln"));
}
else if (__jakt_enum_value == String("format")) {
return JaktInternal::ExplicitValue(String("String::formatted"));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
(output += helper);
(output += String("("));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
String const _ = ((__expr_).get<0>());
NonnullRefPtr<types::CheckedExpression> const expr = ((__expr_).get<1>());

(output += TRY((((*this).codegen_expression(expr)))));
if ((i != (JaktInternal::checked_sub<size_t>(((((call).args)).size()),static_cast<size_t>(1ULL))))){
(output += String(","));
}
}

}
}

(output += String(")"));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == String("format")) {
{
String const helper = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == String("print")) {
return JaktInternal::ExplicitValue(String("out"));
}
else if (__jakt_enum_value == String("println")) {
return JaktInternal::ExplicitValue(String("outln"));
}
else if (__jakt_enum_value == String("eprint")) {
return JaktInternal::ExplicitValue(String("warn"));
}
else if (__jakt_enum_value == String("eprintln")) {
return JaktInternal::ExplicitValue(String("warnln"));
}
else if (__jakt_enum_value == String("format")) {
return JaktInternal::ExplicitValue(String("String::formatted"));
}
else {
return JaktInternal::ExplicitValue(String(""));
}
}()))
;
(output += helper);
(output += String("("));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
String const _ = ((__expr_).get<0>());
NonnullRefPtr<types::CheckedExpression> const expr = ((__expr_).get<1>());

(output += TRY((((*this).codegen_expression(expr)))));
if ((i != (JaktInternal::checked_sub<size_t>(((((call).args)).size()),static_cast<size_t>(1ULL))))){
(output += String(","));
}
}

}
}

(output += String(")"));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
bool close_enum_type_wrapper = false;
if (((((call).function_id)).has_value())){
types::FunctionId const function_id = (((call).function_id).value());
NonnullRefPtr<types::CheckedFunction> const function_ = ((((*this).program))->get_function(function_id));
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((function_id).module)));
if ((((((function_)->type)).index() == 1 /* ImplicitConstructor */) || ((((function_)->type)).index() == 3 /* ExternalClassConstructor */))){
types::TypeId const type_id = ((call).return_type);
NonnullRefPtr<types::Type> const type = ((((*this).program))->get_type(type_id));
if ((!((((((((type_module)->is_root) || ((type_module)->is_prelude())) || ((((function_)->linkage)).index() == 1 /* External */)) || ((((function_)->type)).index() == 4 /* Expression */)) || ((((function_)->type)).index() == 5 /* Closure */)) || ((!(((((call).namespace_)).is_empty()))) && (((((((call).namespace_))[static_cast<i64>(0LL)])).name) == ((type_module)->name))))))){
(output += ((type_module)->name));
(output += String("::"));
}
(output += TRY((((*this).codegen_namespace_path(call)))));
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
types::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if (((((struct_).record_type)).index() == 1 /* Class */)){
(output += ((call).name));
(output += String("::"));
(output += String("create"));
}
else {
(output += ((call).name));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();types::StructId const& id = __jakt_match_value.id;
JaktInternal::Array<types::TypeId> const& args = __jakt_match_value.args;
{
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
if (((((struct_).record_type)).index() == 1 /* Class */)){
(output += TRY((((*this).codegen_namespace_qualifier(((struct_).scope_id))))));
(output += ((struct_).name));
(output += String("<"));
bool first = true;
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId arg = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_type(arg)))));
}

}
}

(output += String(">::create"));
}
else {
(output += ((call).name));
(output += String("<"));
bool first = true;
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId arg = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_type(arg)))));
}

}
}

(output += String(">"));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(String("Should be unreachable"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
else if (((((function_)->type)).index() == 2 /* ImplicitEnumConstructor */)){
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<String>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((function_)->return_type_id)));
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
types::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
NonnullRefPtr<types::Module> const enum_type_module = ((((*this).program))->get_module(((enum_id).module)));
if (((enum_).is_boxed)){
if ((!((((((((type_module)->is_root) || ((type_module)->is_prelude())) || ((((function_)->linkage)).index() == 1 /* External */)) || ((((function_)->type)).index() == 4 /* Expression */)) || ((((function_)->type)).index() == 5 /* Closure */)) || ((!(((((call).namespace_)).is_empty()))) && (((((((call).namespace_))[static_cast<i64>(0LL)])).name) == ((type_module)->name))))))){
(output += ((type_module)->name));
(output += String("::"));
}
(output += TRY((((*this).codegen_namespace_path(call)))));
(output += String("template create<typename "));
(output += TRY((((*this).codegen_type_possibly_as_namespace(((call).return_type),true)))));
(output += ((String("::") + ((call).name)) + String(">")));
}
else {
(output += (String(" ") + TRY((((*this).codegen_type(((call).return_type)))))));
(output += String(" { "));
(output += String("typename "));
(output += TRY((((*this).codegen_type(((call).return_type))))));
(output += String("::"));
(output += ((call).name));
(close_enum_type_wrapper = true);
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();types::EnumId const& id = __jakt_match_value.id;
{
utility::todo(String("codegen generic enum instance"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(String("constructor expected enum type"));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
));
}
else {
if ((!((((((((type_module)->is_root) || ((type_module)->is_prelude())) || ((((function_)->linkage)).index() == 1 /* External */)) || ((((function_)->type)).index() == 4 /* Expression */)) || ((((function_)->type)).index() == 5 /* Closure */)) || ((!(((((call).namespace_)).is_empty()))) && (((((((call).namespace_))[static_cast<i64>(0LL)])).name) == ((type_module)->name))))))){
(output += ((type_module)->name));
(output += String("::"));
}
(output += TRY((((*this).codegen_namespace_path(call)))));
if ((((function_)->is_static()) && (((((function_)->struct_id)).has_value()) && (((((function_)->type)).index() == 0 /* Normal */) && ((((function_)->linkage)).index() == 0 /* Internal */))))){
types::CheckedStruct const struct_ = ((((*this).program))->get_struct((((function_)->struct_id).value())));
(output += ((struct_).name));
(output += String("::"));
}
(output += ((call).name));
}

}
else {
(output += TRY((((*this).codegen_namespace_path(call)))));
(output += ((call).name));
}

JaktInternal::Array<types::TypeId> const generic_parameters = ((call).type_args);
if ((!(((generic_parameters).is_empty())))){
JaktInternal::Array<String> types = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((generic_parameters).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId gen_param = (_magic_value.value());
{
TRY((((types).push(TRY((((*this).codegen_type_possibly_as_namespace(gen_param,false))))))));
}

}
}

(output += TRY((String::formatted(String("<{}>"),utility::join(types,String(", "))))));
}
JaktInternal::Array<String> arguments = (TRY((Array<String>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>>> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> arg = (_magic_value.value());
{
TRY((((arguments).push(TRY((((*this).codegen_expression(((arg).get<1>())))))))));
}

}
}

(output += TRY((String::formatted(String("({})"),utility::join(arguments,String(","))))));
if (close_enum_type_wrapper){
(output += String(" } "));
}
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}()))
;
if (((call).callee_throws)){
(output += String("))"));
}
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_generic_enum_instance(types::EnumId const id,JaktInternal::Array<types::TypeId> const args,bool const as_namespace) const {
{
String output = String("");
bool close_tag = false;
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(id));
if (((!(as_namespace)) && ((enum_).is_boxed))){
(output += String("NonnullRefPtr<"));
String const qualifier = TRY((((*this).codegen_namespace_qualifier(((enum_).scope_id)))));
if ((!(((qualifier).is_empty())))){
(output += String("typename "));
(output += qualifier);
}
(output += ((enum_).name));
(close_tag = true);
}
else {
String const qualifier = TRY((((*this).codegen_namespace_qualifier(((enum_).scope_id)))));
if ((!(((qualifier).is_empty())))){
(output += String("typename "));
(output += qualifier);
}
(output += ((enum_).name));
}

(output += String("<"));
bool first = true;
{
JaktInternal::ArrayIterator<types::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<types::TypeId> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::TypeId type_id = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_type(type_id)))));
}

}
}

(output += String(">"));
if (close_tag){
(output += String(">"));
}
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_function_generic_parameters(NonnullRefPtr<types::CheckedFunction> const function_) {
{
String output = String("");
if ((!(((((((function_)->generics))->params)).is_empty())))){
(output += String("template <"));
bool first = true;
{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((((((function_)->generics))->params)).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter generic_parameter = (_magic_value.value());
{
if (first){
(first = false);
}
else {
(output += String(","));
}

(output += String("typename "));
(output += TRY((((*this).codegen_type(((generic_parameter).type_id()))))));
}

}
}

(output += String(">\n"));
}
return (output);
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_ak_formatter(String const name,JaktInternal::Array<String> const generic_parameter_names) {
{
String output = String("");
String const template_args = utility::join(TRY((utility::prepend_to_each(generic_parameter_names,String("typename ")))),String(", "));
String const generic_type_args = utility::join(generic_parameter_names,String(", "));
String qualified_name = String("");
{
JaktInternal::ArrayIterator<String> _magic = ((((*this).namespace_stack)).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String namespace_ = (_magic_value.value());
{
(qualified_name += TRY((String::formatted(String("{}::"),namespace_))));
}

}
}

(qualified_name += name);
if ((!(((generic_parameter_names).is_empty())))){
(qualified_name += TRY((String::formatted(String("<{}>\n"),generic_type_args))));
}
(output += TRY((String::formatted(String("template<{}>"),template_args))));
(output += TRY((String::formatted(String("struct Formatter<{}> : Formatter<StringView>"),qualified_name))));
(output += String("{\n"));
(output += TRY((String::formatted(String("ErrorOr<void> format(FormatBuilder& builder, {} const& value) {{\n"),qualified_name))));
(output += String("JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };"));
(output += String("ErrorOr<void> format_error = Formatter<StringView>::format(builder, MUST(value.debug_description()));"));
(output += String("return format_error; }"));
return ((output + String("};\n")));
}
}

ErrorOr<String> codegen::CodeGenerator::codegen_constructor_predecl(NonnullRefPtr<types::CheckedFunction> const function_) {
{
types::TypeId const type_id = ((function_)->return_type_id);
NonnullRefPtr<types::Type> const type_ = ((((*this).program))->get_type(type_id));
if (((type_)->index() == 23 /* Struct */)){
types::StructId const struct_id = (type_->get<types::Type::Struct>()).value;
types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
if (((((structure).record_type)).index() == 1 /* Class */)){
String output = String("");
(output += String("protected:\n"));
(output += TRY((String::formatted(String("explicit {}("),((function_)->name)))));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

types::TypeId const param_type_id = ((((param).variable)).type_id);
(output += TRY((((*this).codegen_type(param_type_id)))));
(output += String("&& a_"));
(output += ((((param).variable)).name));
}

}
}

(output += String(");\n"));
String class_name_with_generics = String("");
(class_name_with_generics += ((structure).name));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((structure).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if ((!(first))){
(class_name_with_generics += String(", "));
}
else {
(class_name_with_generics += String("<"));
(first = false);
}

(class_name_with_generics += TRY((((*this).codegen_type(((generic_parameter).type_id))))));
}

}
}

if ((!(((((structure).generic_parameters)).is_empty())))){
(class_name_with_generics += String(">"));
}
(output += String("public:\n"));
(output += TRY((String::formatted(String("static ErrorOr<NonnullRefPtr<{}>> create"),class_name_with_generics))));
(output += String("("));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_type(((((param).variable)).type_id))))));
(output += String(" "));
(output += ((((param).variable)).name));
}

}
}

(output += String(");\n"));
return (output);
}
String output = String("");
(output += ((function_)->name));
(output += String("("));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function_)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
(output += String(", "));
}
else {
(first = false);
}

(output += TRY((((*this).codegen_type(((((param).variable)).type_id))))));
(output += String(" a_"));
(output += ((((param).variable)).name));
}

}
}

(output += String(");\n"));
return (output);
}
else {
utility::panic(String("internal error: call to a constructor, but not a struct/class type"));
}

}
}

ErrorOr<String> codegen::CodeGenerator::codegen_type(types::TypeId const type_id) const {
{
return (TRY((((*this).codegen_type_possibly_as_namespace(type_id,false)))));
}
}

ErrorOr<void> codegen::CodeGenerator::postorder_traversal(String const encoded_type_id,JaktInternal::Set<String> visited,JaktInternal::Dictionary<String,JaktInternal::Array<String>> const encoded_dependency_graph,JaktInternal::Array<types::TypeId> output) const {
{
types::TypeId const type_id = TRY((types::TypeId::TypeId::from_string(encoded_type_id)));
if (((visited).contains(TRY((((type_id).to_string())))))){
return {};
}
TRY((((visited).add(TRY((((type_id).to_string())))))));
if (((encoded_dependency_graph).contains(encoded_type_id))){
{
JaktInternal::ArrayIterator<String> _magic = (((((encoded_dependency_graph).get(encoded_type_id)).value())).iterator());
for (;;){
JaktInternal::Optional<String> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
String dependency = (_magic_value.value());
{
TRY((((*this).postorder_traversal(dependency,visited,encoded_dependency_graph,output))));
}

}
}

}
TRY((((output).push(type_id))));
}
return {};
}

ErrorOr<String> codegen::CodeGenerator::fresh_label() {
{
return (TRY((String::formatted(String("__jakt_label_{}"),((((*this).fresh_label_counter)++))))));
}
}

ErrorOr<String> codegen::ControlFlowState::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("ControlFlowState("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("allowed_exits: "));TRY(builder.appendff("{}, ", allowed_exits));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("passes_through_match: "));TRY(builder.appendff("{}, ", passes_through_match));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("passes_through_try: "));TRY(builder.appendff("{}, ", passes_through_try));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("match_nest_level: "));TRY(builder.appendff("{}", match_nest_level));
}
TRY(builder.append(")"));return builder.to_string(); }
codegen::ControlFlowState codegen::ControlFlowState::enter_function() const {
{
return (codegen::ControlFlowState( codegen::AllowedControlExits { typename codegen::AllowedControlExits::JustReturn() } ,false,false,((*this).match_nest_level)));
}
}

codegen::ControlFlowState codegen::ControlFlowState::enter_loop() const {
{
return (codegen::ControlFlowState( codegen::AllowedControlExits { typename codegen::AllowedControlExits::AtLoop() } ,false,((*this).passes_through_try),static_cast<size_t>(0ULL)));
}
}

codegen::ControlFlowState codegen::ControlFlowState::no_control_flow() {
{
return (codegen::ControlFlowState( codegen::AllowedControlExits { typename codegen::AllowedControlExits::Nothing() } ,false,false,static_cast<size_t>(0ULL)));
}
}

bool codegen::ControlFlowState::is_match_nested() const {
{
return ((((*this).match_nest_level) != static_cast<size_t>(0ULL)));
}
}

String codegen::ControlFlowState::choose_control_flow_macro() const {
{
if (codegen::are_loop_exits_allowed(((*this).allowed_exits))){
if (((*this).is_match_nested())){
return (String("JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP_NESTED_MATCH"));
}
return (String("JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP"));
}
return (String("JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY"));
}
}

codegen::ControlFlowState codegen::ControlFlowState::enter_match() const {
{
size_t level = ((*this).match_nest_level);
if (((*this).passes_through_match)){
(level = (JaktInternal::checked_add<size_t>(((*this).match_nest_level),static_cast<size_t>(1ULL))));
}
return (codegen::ControlFlowState(((((*this).allowed_exits)).allow_return()),true,((*this).passes_through_try),level));
}
}

codegen::ControlFlowState::ControlFlowState(codegen::AllowedControlExits a_allowed_exits, bool a_passes_through_match, bool a_passes_through_try, size_t a_match_nest_level) :allowed_exits(a_allowed_exits), passes_through_match(a_passes_through_match), passes_through_try(a_passes_through_try), match_nest_level(a_match_nest_level){}

ErrorOr<String> codegen::AllowedControlExits::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Nothing */: {
[[maybe_unused]] auto const& that = this->template get<AllowedControlExits::Nothing>();
TRY(builder.append("AllowedControlExits::Nothing"));
break;}
case 1 /* JustReturn */: {
[[maybe_unused]] auto const& that = this->template get<AllowedControlExits::JustReturn>();
TRY(builder.append("AllowedControlExits::JustReturn"));
break;}
case 2 /* AtLoop */: {
[[maybe_unused]] auto const& that = this->template get<AllowedControlExits::AtLoop>();
TRY(builder.append("AllowedControlExits::AtLoop"));
break;}
}
return builder.to_string();
}
codegen::AllowedControlExits codegen::AllowedControlExits::allow_return() const {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<codegen::AllowedControlExits, codegen::AllowedControlExits>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename codegen::AllowedControlExits::Nothing>();
return JaktInternal::ExplicitValue( codegen::AllowedControlExits { typename codegen::AllowedControlExits::JustReturn() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename codegen::AllowedControlExits::JustReturn>();
return JaktInternal::ExplicitValue( codegen::AllowedControlExits { typename codegen::AllowedControlExits::JustReturn() } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename codegen::AllowedControlExits::AtLoop>();
return JaktInternal::ExplicitValue( codegen::AllowedControlExits { typename codegen::AllowedControlExits::AtLoop() } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
}
}

}
} // namespace Jakt
