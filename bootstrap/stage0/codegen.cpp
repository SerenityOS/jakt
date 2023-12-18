#include "codegen.h"
namespace Jakt {
namespace codegen {
bool are_loop_exits_allowed(codegen::AllowedControlExits const allowed_control_exits) {
{
return ((allowed_control_exits).__jakt_init_index() == 2 /* AtLoop */);
}
}

bool is_return_allowed(codegen::AllowedControlExits const allowed_control_exits) {
{
return (!(((allowed_control_exits).__jakt_init_index() == 0 /* Nothing */)));
}
}

ErrorOr<ByteString> codegen::ControlFlowState::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("ControlFlowState("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("allowed_exits: {}, ", allowed_exits));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("passes_through_match: {}, ", passes_through_match));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("passes_through_try: {}, ", passes_through_try));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("match_nest_level: {}", match_nest_level));
}
TRY(builder.append(")"sv));return builder.to_string(); }
codegen::ControlFlowState codegen::ControlFlowState::enter_function() const {
{
return codegen::ControlFlowState(codegen::AllowedControlExits::JustReturn(),false,false,((*this).match_nest_level));
}
}

ErrorOr<ByteString> codegen::ControlFlowState::nested_release_return_expr(ids::TypeId const func_return_type,bool const func_can_throw,ByteString const cpp_match_result_type) {
{
bool const returns_void = ((((func_return_type).equals(types::void_type_id())) || ((func_return_type).equals(types::unknown_type_id()))) || ((func_return_type).equals(types::never_type_id())));
if ((returns_void && (!(func_can_throw)))){
return TRY((__jakt_format((StringView::from_string_literal("JaktInternal::ExplicitValueOrControlFlow<{}, void>()"sv)),cpp_match_result_type)));
}
else {
return TRY(ByteString::from_utf8("_jakt_value.release_return()"sv));
}

}
}

ErrorOr<ByteString> codegen::ControlFlowState::apply_control_flow_macro(ByteString const x,ids::TypeId const func_return_type,bool const func_can_throw,ByteString const cpp_match_result_type) const {
{
if (codegen::are_loop_exits_allowed(((*this).allowed_exits))){
if (((*this).is_match_nested())){
return TRY((__jakt_format((StringView::from_string_literal("({{\n    auto&& _jakt_value = {};\n    if (_jakt_value.is_return())\n        return {};\n    if (_jakt_value.is_loop_break())\n        return JaktInternal::LoopBreak {{}};\n    if (_jakt_value.is_loop_continue())\n        return JaktInternal::LoopContinue {{}};\n    _jakt_value.release_value();\n}})"sv)),x,TRY((codegen::ControlFlowState::nested_release_return_expr(func_return_type,func_can_throw,cpp_match_result_type))))));
}
return TRY((__jakt_format((StringView::from_string_literal("({{\n    auto&& _jakt_value = {};\n    if (_jakt_value.is_return())\n        return _jakt_value.release_return();\n    if (_jakt_value.is_loop_break())\n        break;\n    if (_jakt_value.is_loop_continue())\n        continue;\n    _jakt_value.release_value();\n}})"sv)),x)));
}
return TRY((__jakt_format((StringView::from_string_literal("({{\n    auto&& _jakt_value = {};\n    if (_jakt_value.is_return())\n        return {};\n    _jakt_value.release_value();\n}})"sv)),x,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((*this).is_match_nested()));
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("_jakt_value.release_return()"sv)));
}
else if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((codegen::ControlFlowState::nested_release_return_expr(func_return_type,func_can_throw,cpp_match_result_type))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
}

codegen::ControlFlowState codegen::ControlFlowState::enter_loop() const {
{
return codegen::ControlFlowState(codegen::AllowedControlExits::AtLoop(),false,((*this).passes_through_try),static_cast<size_t>(0ULL));
}
}

codegen::ControlFlowState codegen::ControlFlowState::no_control_flow() {
{
return codegen::ControlFlowState(codegen::AllowedControlExits::Nothing(),false,false,static_cast<size_t>(0ULL));
}
}

bool codegen::ControlFlowState::is_match_nested() const {
{
return ((((*this).match_nest_level)) != (static_cast<size_t>(0ULL)));
}
}

codegen::ControlFlowState codegen::ControlFlowState::enter_match() const {
{
size_t level = ((*this).match_nest_level);
if (((*this).passes_through_match)){
(level = JaktInternal::checked_add(((*this).match_nest_level),static_cast<size_t>(1ULL)));
}
return codegen::ControlFlowState(((((*this).allowed_exits)).allow_return()),true,((*this).passes_through_try),level);
}
}

codegen::ControlFlowState::ControlFlowState(codegen::AllowedControlExits a_allowed_exits, bool a_passes_through_match, bool a_passes_through_try, size_t a_match_nest_level): allowed_exits(move(a_allowed_exits)), passes_through_match(move(a_passes_through_match)), passes_through_try(move(a_passes_through_try)), match_nest_level(move(a_match_nest_level)){}

ErrorOr<ByteString> codegen::CodegenDebugInfo::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("CodegenDebugInfo("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("compiler: {}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("line_spans: {}, ", line_spans));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("statement_span_comments: {}", statement_span_comments));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> codegen::CodegenDebugInfo::gather_line_spans() {
{
{
JaktInternal::DictionaryIterator<ByteString,utility::FileId> _magic = ((((((*this).compiler))->file_ids)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,utility::FileId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,utility::FileId> file = (_magic_value.value());
{
if (((((file).template get<0>())) == (TRY(ByteString::from_utf8("__prelude__"sv))))){
continue;
}
TRY((((((*this).compiler))->set_current_file(((file).template get<1>())))));
size_t const file_idx = ((((file).template get<1>())).id);
JaktInternal::DynamicArray<codegen::LineSpan> const empty_array = (TRY((DynamicArray<codegen::LineSpan>::create_with({}))));
TRY((((((*this).line_spans)).set(file_idx,empty_array))));
size_t idx = static_cast<size_t>(0ULL);
size_t start = idx;
while ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(idx,((((((*this).compiler))->current_file_contents)).size()))){
if (((((((((*this).compiler))->current_file_contents))[idx])) == (static_cast<u8>(u8'\n')))){
TRY((((((((*this).line_spans))[file_idx])).push(codegen::LineSpan(start,idx)))));
(start = JaktInternal::checked_add(idx,static_cast<size_t>(1ULL)));
}
((idx) += (static_cast<size_t>(1ULL)));
}
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(start,idx)){
TRY((((((((*this).line_spans))[file_idx])).push(codegen::LineSpan(start,idx)))));
}
}

}
}

}
return {};
}

ErrorOr<ByteString> codegen::CodegenDebugInfo::span_to_source_location(utility::Span const span) {
{
if (((((*this).line_spans)).is_empty())){
TRY((((*this).gather_line_spans())));
}
size_t const file_idx = ((((span).file_id)).id);
if ((!(((((*this).line_spans)).contains(file_idx))))){
return TRY(ByteString::from_utf8(""sv));
}
size_t line_index = static_cast<size_t>(0ULL);
while ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(line_index,((((((*this).line_spans))[file_idx])).size()))){
if (([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(((span).start),((((((((*this).line_spans))[file_idx]))[line_index])).start)) && [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(((span).start),((((((((*this).line_spans))[file_idx]))[line_index])).end)))){
size_t const column_index = JaktInternal::checked_sub(((span).start),((((((((*this).line_spans))[file_idx]))[line_index])).start));
return TRY((__jakt_format((StringView::from_string_literal("{} \"{}\""sv)),JaktInternal::checked_add(line_index,static_cast<size_t>(1ULL)),(((TRY((((((*this).compiler))->get_file_path(((span).file_id))))).value())).to_string()))));
}
((line_index) += (static_cast<size_t>(1ULL)));
}
utility::panic(TRY(ByteString::from_utf8("Reached end of file and could not find index"sv)));
}
}

codegen::CodegenDebugInfo::CodegenDebugInfo(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::Dictionary<size_t,JaktInternal::DynamicArray<codegen::LineSpan>> a_line_spans, bool a_statement_span_comments): compiler(move(a_compiler)), line_spans(move(a_line_spans)), statement_span_comments(move(a_statement_span_comments)){}

ErrorOr<ByteString> codegen::LineSpan::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("LineSpan("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("start: {}, ", start));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("end: {}", end));
}
TRY(builder.append(")"sv));return builder.to_string(); }
codegen::LineSpan::LineSpan(size_t a_start, size_t a_end): start(move(a_start)), end(move(a_end)){}

ErrorOr<ByteString> codegen::CodeGenerator::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("CodeGenerator("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("compiler: {}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("program: {}, ", *program));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("control_flow_state: {}, ", control_flow_state));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("entered_yieldable_blocks: {}, ", entered_yieldable_blocks));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("deferred_output: \"{}\", ", deferred_output));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("current_function: {}, ", current_function));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("inside_defer: {}, ", inside_defer));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("debug_info: {}, ", debug_info));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("namespace_stack: {}, ", namespace_stack));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("fresh_var_counter: {}, ", fresh_var_counter));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("fresh_label_counter: {}, ", fresh_label_counter));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("this_replacement: {}, ", this_replacement));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generic_inferences: {}", generic_inferences));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> codegen::CodeGenerator::generate(NonnullRefPtr<compiler::Compiler> const compiler,NonnullRefPtr<types::CheckedProgram> const program,bool const debug_info) {
{
codegen::CodeGenerator generator = codegen::CodeGenerator(compiler,program,codegen::ControlFlowState(codegen::AllowedControlExits::Nothing(),false,false,static_cast<size_t>(0ULL)),(TRY((DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({})))),TRY(ByteString::from_utf8(""sv)),JaktInternal::OptionalNone(),false,codegen::CodegenDebugInfo(compiler,(TRY((Dictionary<size_t, JaktInternal::DynamicArray<codegen::LineSpan>>::create_with_entries({})))),debug_info),(TRY((DynamicArray<ByteString>::create_with({})))),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>> result = (TRY((Dictionary<ByteString, JaktInternal::Tuple<ByteString,ByteString>>::create_with_entries({}))));
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#pragma once\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#include <lib.h>\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#ifdef _WIN32\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("extern \"C\" __cdecl int SetConsoleOutputCP(unsigned int code_page);\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("const unsigned int CP_UTF8 = 65001;\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#endif\n"sv)))));
JaktInternal::DynamicArray<ids::ModuleId> const sorted_modules = TRY((((generator).topologically_sort_modules())));
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>> imported_paths = (TRY((Dictionary<ByteString, JaktInternal::Tuple<ByteString,ByteString>>::create_with_entries({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((sorted_modules).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t idx = (_magic_value.value());
{
ids::ModuleId const i = ((sorted_modules)[JaktInternal::checked_sub(idx,static_cast<size_t>(1ULL))]);
AK::Queue<ids::ScopeId> q = AK::Queue<ids::ScopeId>();
((q).enqueue(ids::ScopeId(i,static_cast<size_t>(0ULL))));
while ((!(((q).is_empty())))){
ids::ScopeId const scope_id = ((q).dequeue());
NonnullRefPtr<types::Scope> const scope = TRY((((((generator).program))->get_scope(scope_id))));
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
((q).enqueue(child));
}

}
}

if (((((scope)->import_path_if_extern)).has_value())){
ByteString const path = (((scope)->import_path_if_extern).value());
ByteString before = TRY(ByteString::from_utf8(""sv));
ByteString after = TRY(ByteString::from_utf8(""sv));
{
JaktInternal::ArrayIterator<parser::IncludeAction> _magic = ((((scope)->before_extern_include)).iterator());
for (;;){
JaktInternal::Optional<parser::IncludeAction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::IncludeAction action = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>>>>{
auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Define */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Define;ByteString const& name = __jakt_match_value.name;
ByteString const& value = __jakt_match_value.value;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(before,TRY((__jakt_format((StringView::from_string_literal("#ifdef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(before,TRY((__jakt_format((StringView::from_string_literal("#undef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(before,TRY(ByteString::from_utf8("#endif\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(before,TRY((__jakt_format((StringView::from_string_literal("#define {} {}\n"sv)),name,value))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Undefine */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Undefine;ByteString const& name = __jakt_match_value.name;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(before,TRY((__jakt_format((StringView::from_string_literal("#ifdef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(before,TRY((__jakt_format((StringView::from_string_literal("#undef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(before,TRY(ByteString::from_utf8("#endif\n"sv)))));
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
JaktInternal::ArrayIterator<parser::IncludeAction> _magic = ((((scope)->after_extern_include)).iterator());
for (;;){
JaktInternal::Optional<parser::IncludeAction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::IncludeAction action = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>>>>{
auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Define */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Define;ByteString const& name = __jakt_match_value.name;
ByteString const& value = __jakt_match_value.value;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(after,TRY((__jakt_format((StringView::from_string_literal("#ifdef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(after,TRY((__jakt_format((StringView::from_string_literal("#undef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(after,TRY(ByteString::from_utf8("#endif\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(after,TRY((__jakt_format((StringView::from_string_literal("#define {} {}\n"sv)),name,value))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Undefine */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Undefine;ByteString const& name = __jakt_match_value.name;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(after,TRY((__jakt_format((StringView::from_string_literal("#ifdef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(after,TRY((__jakt_format((StringView::from_string_literal("#undef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(after,TRY(ByteString::from_utf8("#endif\n"sv)))));
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

TRY((((imported_paths).set(path,(Tuple{before, after})))));
}
}
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Tuple<ByteString,ByteString>> _magic = ((imported_paths).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> path__actions__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::Tuple<ByteString,ByteString>> const jakt__path__actions__ = path__actions__;
ByteString const path = ((jakt__path__actions__).template get<0>());
JaktInternal::Tuple<ByteString,ByteString> const actions = ((jakt__path__actions__).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((actions).template get<0>()))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#include <{}>\n"sv)),path))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((actions).template get<1>()))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("namespace Jakt {\n"sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((sorted_modules).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t idx = (_magic_value.value());
{
size_t const i = ((((sorted_modules)[JaktInternal::checked_sub(idx,static_cast<size_t>(1ULL))])).id);
if (((i) == (static_cast<size_t>(0ULL)))){
continue;
}
NonnullRefPtr<types::Module> const module = ((((((generator).program))->modules))[i]);
TRY((((((generator).compiler))->dbg_println(TRY((__jakt_format((StringView::from_string_literal("generate: module idx: {}, module.name {}"sv)),i,((module)->name))))))));
ids::ScopeId const scope_id = ids::ScopeId(((module)->id),static_cast<size_t>(0ULL));
NonnullRefPtr<types::Scope> const scope = TRY((((((generator).program))->get_scope(scope_id))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((generator).codegen_namespace_predecl(scope,module)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("} // namespace Jakt\n"sv)))));
TRY((((result).set(TRY(ByteString::from_utf8("__unified_forward.h"sv)),(Tuple{output, (((((compiler)->current_file_path()).value())).to_string())})))));
{
JaktInternal::ArrayIterator<bool> _magic = (((TRY((DynamicArray<bool>::create_with({true, false}))))).iterator());
for (;;){
JaktInternal::Optional<bool> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
bool as_forward = (_magic_value.value());
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((sorted_modules).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t idx = (_magic_value.value());
{
size_t const i = ((((sorted_modules)[JaktInternal::checked_sub(idx,static_cast<size_t>(1ULL))])).id);
if (((i) == (static_cast<size_t>(0ULL)))){
continue;
}
NonnullRefPtr<types::Module> const module = ((((((generator).program))->modules))[i]);
TRY((((((generator).compiler))->dbg_println(TRY((__jakt_format((StringView::from_string_literal("generate: module idx: {}, module.name {} - forward: {}"sv)),i,((module)->name),as_forward)))))));
ByteString const header_name = TRY((__jakt_format((StringView::from_string_literal("{}.h"sv)),((module)->name))));
ByteString const impl_name = TRY((__jakt_format((StringView::from_string_literal("{}.cpp"sv)),((module)->name))));
if (as_forward){
(output = TRY(ByteString::from_utf8("#pragma once\n"sv)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#include \"__unified_forward.h\"\n"sv)))));
}
else {
(output = TRY((__jakt_format((StringView::from_string_literal("#include \"{}\"\n"sv)),header_name))));
}

ids::ScopeId const scope_id = ids::ScopeId(((module)->id),static_cast<size_t>(0ULL));
NonnullRefPtr<types::Scope> const scope = TRY((((((generator).program))->get_scope(scope_id))));
if (as_forward){
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child_scope_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const scope = TRY((((((generator).program))->get_scope(child_scope_id))));
if (((((scope)->import_path_if_extern)).has_value())){
bool const has_name = ((((scope)->namespace_name)).has_value());
if (has_name){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("namespace {} {{\n"sv)),(((scope)->namespace_name).value())))))));
}
{
JaktInternal::ArrayIterator<parser::IncludeAction> _magic = ((((scope)->before_extern_include)).iterator());
for (;;){
JaktInternal::Optional<parser::IncludeAction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::IncludeAction action = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>>>>{
auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Define */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Define;ByteString const& name = __jakt_match_value.name;
ByteString const& value = __jakt_match_value.value;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#ifdef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#undef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#endif\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#define {} {}\n"sv)),name,value))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Undefine */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Undefine;ByteString const& name = __jakt_match_value.name;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#ifdef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#undef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#endif\n"sv)))));
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

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#include <{}>\n"sv)),(((scope)->import_path_if_extern).value())))))));
{
JaktInternal::ArrayIterator<parser::IncludeAction> _magic = ((((scope)->after_extern_include)).iterator());
for (;;){
JaktInternal::Optional<parser::IncludeAction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::IncludeAction action = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>>>>{
auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Define */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Define;ByteString const& name = __jakt_match_value.name;
ByteString const& value = __jakt_match_value.value;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#ifdef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#undef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#endif\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#define {} {}\n"sv)),name,value))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Undefine */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Undefine;ByteString const& name = __jakt_match_value.name;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#ifdef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#undef {}\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("#endif\n"sv)))));
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

if (has_name){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY(ByteString::from_utf8(" } // namespace "sv))) + ((((scope)->namespace_name).value())))))) + (TRY(ByteString::from_utf8("\n"sv)))))))));
}
}
}

}
}

{
JaktInternal::ArrayIterator<ids::ModuleId> _magic = ((((module)->imports)).iterator());
for (;;){
JaktInternal::Optional<ids::ModuleId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ModuleId id = (_magic_value.value());
{
NonnullRefPtr<types::Module> const module = ((((((generator).program))->modules))[((id).id)]);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#include \"{}.h\"\n"sv)),((module)->name)))))));
}

}
}

}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("namespace Jakt {\n"sv)))));
if ((!(((module)->is_root)))){
TRY((((((generator).namespace_stack)).push(((module)->name)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((generator).codegen_namespace(scope,module,as_forward)))))));
if ((!(((module)->is_root)))){
JaktInternal::Optional<ByteString> const dummy = ((((generator).namespace_stack)).pop());
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((generator).deferred_output))));
(((generator).deferred_output) = TRY(ByteString::from_utf8(""sv)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("} // namespace Jakt\n"sv)))));
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

{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((sorted_modules).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t idx = (_magic_value.value());
{
size_t const i = ((((sorted_modules)[JaktInternal::checked_sub(idx,static_cast<size_t>(1ULL))])).id);
NonnullRefPtr<types::Module> const module = ((((((generator).program))->modules))[i]);
ByteString const header_name = TRY((__jakt_format((StringView::from_string_literal("{}.h"sv)),((module)->name))));
ByteString const impl_name = TRY((__jakt_format((StringView::from_string_literal("{}_specializations.cpp"sv)),((module)->name))));
if (((i) == (static_cast<size_t>(0ULL)))){
(output = TRY(ByteString::from_utf8(""sv)));
}
else {
(output = TRY((__jakt_format((StringView::from_string_literal("#include \"{}\"\n"sv)),header_name))));
}

{
JaktInternal::ArrayIterator<ids::ModuleId> _magic = ((sorted_modules).iterator());
for (;;){
JaktInternal::Optional<ids::ModuleId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ModuleId id = (_magic_value.value());
{
if (((((id).id)) == (static_cast<size_t>(0ULL)))){
continue;
}
NonnullRefPtr<types::Module> const module = ((((((generator).program))->modules))[((id).id)]);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("#include \"{}.h\"\n"sv)),((module)->name)))))));
}

}
}

ids::ScopeId const scope_id = ids::ScopeId(((module)->id),static_cast<size_t>(0ULL));
NonnullRefPtr<types::Scope> const scope = TRY((((((generator).program))->get_scope(scope_id))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("namespace Jakt {\n"sv)))));
if ((!(((module)->is_root)))){
TRY((((((generator).namespace_stack)).push(((module)->name)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((generator).codegen_namespace_specializations(scope,module)))))));
if ((!(((module)->is_root)))){
JaktInternal::Optional<ByteString> const dummy = ((((generator).namespace_stack)).pop());
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((generator).deferred_output))));
(((generator).deferred_output) = TRY(ByteString::from_utf8(""sv)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("} // namespace Jakt\n"sv)))));
TRY((((result).set(impl_name,(Tuple{output, ((module)->resolved_import_path)})))));
}

}
}

return result;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_destructor(types::CheckedStruct const& struct_,NonnullRefPtr<types::CheckedFunction> const& function,bool const is_inline) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
ByteString const qualified_name = TRY((((*this).codegen_type_possibly_as_namespace(((((struct_))).type_id),true))));
if (((!(is_inline)) && (!(((((((struct_))).generic_parameters)).is_empty()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("template <"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_template_parameter_names(((((struct_))).generic_parameters))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">\n"sv)))));
}
if (is_inline){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("~{}()"sv)),TRY((((((((struct_))).name_for_codegen())).as_name_for_definition())))))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{}::~{}()"sv)),qualified_name,TRY((((((((struct_))).name_for_codegen())).as_name_for_definition())))))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_block(((((function)))->block))))))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_unchecked_binary_op(NonnullRefPtr<typename types::CheckedExpression> const lhs,NonnullRefPtr<typename types::CheckedExpression> const rhs,parser::BinaryOperator const op,ids::TypeId const type_id) {
{
ByteString output = TRY(ByteString::from_utf8("static_cast<"sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(lhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" + "sv)));
};/*case end*/
case 1 /* Subtract */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" - "sv)));
};/*case end*/
case 2 /* Multiply */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" * "sv)));
};/*case end*/
case 3 /* Divide */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" / "sv)));
};/*case end*/
case 4 /* Modulo */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" % "sv)));
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Checked binary operation codegen is not supported for BinaryOperator::{}"sv)),op))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(rhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_namespace_qualifier(ids::ScopeId const scope_id,bool const skip_current,JaktInternal::Optional<ByteString> const possible_constructor_name,JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> const generic_mappings) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
JaktInternal::Optional<ids::ScopeId> current_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ids::ScopeId>,ErrorOr<ByteString>>{
auto __jakt_enum_value = (skip_current);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((TRY((((((*this).program))->get_scope(scope_id)))))->parent));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(scope_id);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool first = true;
while (((current_scope_id).has_value())){
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope((current_scope_id.value())))));
JaktInternal::Optional<ByteString> const name = TRY((((((scope)->namespace_name_for_codegen())).map([&](auto& _value) { return _value.as_name_for_use(); }))));
bool const is_constructor_call = (first && ((possible_constructor_name) == (name)));
ScopeGuard __jakt_var_612([&] {
{
if (((name).has_value())){
(first = false);
}
(current_scope_id = ((scope)->parent));
}

});
if (((name).has_value())){
if (is_constructor_call){
continue;
}
ByteString const args = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((((scope)->relevant_type_id)).has_value()));
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
else if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_613; {
JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>> const parameters = ((((((*this).program))->get_type((((scope)->relevant_type_id).value()))))->generic_parameters(((*this).program)));
ByteStringBuilder res = ByteStringBuilder::create();
if (((parameters).has_value())){
JaktInternal::DynamicArray<types::CheckedGenericParameter> const params = (parameters.value());
if (((generic_mappings).has_value())){
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const mappings = (generic_mappings.value());
if ((!(((params).is_empty())))){
TRY((((res).append((StringView::from_string_literal("<"sv))))));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter parameter = (_magic_value.value());
{
ids::TypeId const mapping = (((mappings).get(((parameter).type_id))).value());
if ((((((((*this).program))->get_type(mapping)))->__jakt_init_index() == 18 /* TypeVariable */) && ((((*this).map_type(mapping))).equals(mapping)))){
break;
}
if (first){
(first = false);
}
else {
TRY((((res).append((StringView::from_string_literal(", "sv))))));
}

TRY((((res).append(TRY((((*this).codegen_type(mapping))))))));
}

}
}

TRY((((res).append((StringView::from_string_literal(">"sv))))));
}
}
}
__jakt_var_613 = TRY((((res).to_string()))); goto __jakt_label_521;

}
__jakt_label_521:; __jakt_var_613.release_value(); }));
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
(output = TRY((__jakt_format((StringView::from_string_literal("{}{}::{}"sv)),(name.value()),args,output))));
}
}
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_checked_binary_op(NonnullRefPtr<typename types::CheckedExpression> const lhs,NonnullRefPtr<typename types::CheckedExpression> const rhs,parser::BinaryOperator const op,ids::TypeId const type_id) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("JaktInternal::"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_add"sv)));
};/*case end*/
case 1 /* Subtract */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_sub"sv)));
};/*case end*/
case 2 /* Multiply */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_mul"sv)));
};/*case end*/
case 3 /* Divide */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_div"sv)));
};/*case end*/
case 4 /* Modulo */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_mod"sv)));
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Checked binary operation codegen is not supported for BinaryOperator::{}"sv)),op))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(lhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(rhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_constructor_predecl(NonnullRefPtr<types::CheckedFunction> const function) {
{
ids::TypeId const type_id = ((function)->return_type_id);
NonnullRefPtr<typename types::Type> const type_ = ((((*this).program))->get_type(type_id));
if (((type_)->__jakt_init_index() == 24 /* Struct */)){
ids::StructId const struct_id = (type_)->as.Struct.value;
types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
if (((((structure).record_type)).__jakt_init_index() == 1 /* Class */)){
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("protected:\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("explicit {}("sv)),TRY((((((function)->name_for_codegen())).as_name_for_definition())))))))));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

ids::TypeId const param_type_id = ((((param).variable))->type_id);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(param_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" a_"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(");\n"sv)))));
ByteString class_name_with_generics = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY((((((structure).name_for_codegen())).as_name_for_definition()))))));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((structure).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8(", "sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8("<"sv)))));
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY((((*this).codegen_type(((generic_parameter).type_id))))))));
}

}
}

if ((!(((((structure).generic_parameters)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8(">"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("public:\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("static ErrorOr<NonnullRefPtr<{}>> __jakt_create"sv)),class_name_with_generics))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((((param).variable))->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(");\n"sv)))));
return output;
}
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((function)->name_for_codegen())).as_name_for_definition()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((((param).variable))->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" a_"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(");\n"sv)))));
return output;
}
else {
utility::panic(TRY(ByteString::from_utf8("internal error: call to a constructor, but not a struct/class type"sv)));
}

}
}

bool codegen::CodeGenerator::is_full_respecialization(JaktInternal::DynamicArray<ids::TypeId> const type_args) const {
{
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((type_args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId type_id = (_magic_value.value());
{
if (((((((*this).program))->get_type(type_id)))->__jakt_init_index() == 18 /* TypeVariable */)){
return false;
}
}

}
}

return true;
}
}

ErrorOr<JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>>> codegen::CodeGenerator::produce_codegen_dependency_graph(NonnullRefPtr<types::Scope> const scope) const {
{
JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> dependency_graph = (TRY((Dictionary<ids::TypeId, JaktInternal::DynamicArray<ids::TypeId>>::create_with_entries({}))));
{
JaktInternal::DictionaryIterator<ByteString,ids::TypeId> _magic = ((((scope)->types)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::TypeId> type_ = (_magic_value.value());
{
TRY((((dependency_graph).set(((type_).template get<1>()),TRY((((*this).extract_dependencies_from(((type_).template get<1>()),dependency_graph,true))))))));
}

}
}

return dependency_graph;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_statement(NonnullRefPtr<typename types::CheckedStatement> const statement) {
{
bool add_newline = true;
ByteString output = TRY(ByteString::from_utf8(""sv));
if ((((((*this).debug_info)).statement_span_comments) && (((((statement)->span())).has_value()) && add_newline))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("\n#line {}\n"sv)),TRY((((((*this).debug_info)).span_to_source_location((((statement)->span()).value())))))))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY(ByteString::from_utf8("return "sv))) + (TRY((((*this).codegen_expression(expr))))))))) + (TRY(ByteString::from_utf8(";"sv)))))));
};/*case end*/
case 10 /* Continue */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((((*this).control_flow_state)).passes_through_match));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("return JaktInternal::LoopContinue{};"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("continue;"sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 9 /* Break */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((((*this).control_flow_state)).passes_through_match));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("return JaktInternal::LoopBreak{};"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("break;"sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((TRY((((*this).codegen_expression(expr))))) + (TRY(ByteString::from_utf8(";"sv)))))));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename types::CheckedStatement> const& statement = __jakt_match_value.statement;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_614; {
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("ScopeGuard "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).fresh_var()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("([&] {\n"sv)))));
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
bool const old_inside_defer = ((*this).inside_defer);
(((((*this).control_flow_state)).passes_through_match) = false);
(((*this).inside_defer) = true);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(statement)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("});"sv)))));
(((*this).control_flow_state) = last_control_flow);
(((*this).inside_defer) = old_inside_defer);
__jakt_var_614 = output; goto __jakt_label_522;

}
__jakt_label_522:; __jakt_var_614.release_value(); }));
};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((val).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = ((((((*this).current_function).value()))->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_615; {
NonnullRefPtr<typename types::Type> const type = ((((*this).program))->get_type((((val.value()))->type())));
ByteString result = TRY(ByteString::from_utf8(""sv));
if ((((type)->__jakt_init_index() == 0 /* Void */) || ((type)->__jakt_init_index() == 17 /* Never */))){
(result = TRY((((TRY((((*this).codegen_expression((val.value())))))) + (TRY(ByteString::from_utf8("; return {}"sv)))))));
}
else {
(result = TRY((((TRY(ByteString::from_utf8("return "sv))) + (TRY((((*this).codegen_expression((val.value()))))))))));
}

__jakt_var_615 = TRY((((result) + (TRY(ByteString::from_utf8(";"sv)))))); goto __jakt_label_523;

}
__jakt_label_523:; __jakt_var_615.release_value(); }));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY(ByteString::from_utf8("return "sv))) + (TRY((((*this).codegen_expression((val.value())))))))))) + (TRY(ByteString::from_utf8(";"sv)))))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_616; {
__jakt_var_616 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = ((((((*this).current_function).value()))->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("return {};"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("return;"sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_524;

}
__jakt_label_524:; __jakt_var_616.release_value(); }));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_617; {
ByteString output = TRY(ByteString::from_utf8(""sv));
if ((((((*this).debug_info)).statement_span_comments) && ((((statement)->span())).has_value()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("\n#line {}\n"sv)),TRY((((((*this).debug_info)).span_to_source_location((((statement)->span()).value())))))))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("for (;;)"sv)))));
(add_newline = false);
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((last_control_flow).enter_loop()));
ByteString const block_str = TRY((((*this).codegen_block(block))));
(((*this).control_flow_state) = last_control_flow);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,block_str)));
__jakt_var_617 = output; goto __jakt_label_525;

}
__jakt_label_525:; __jakt_var_617.release_value(); }));
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_618; {
ByteString output = TRY(ByteString::from_utf8(""sv));
if ((((((*this).debug_info)).statement_span_comments) && ((((statement)->span())).has_value()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("\n#line {}\n"sv)),TRY((((((*this).debug_info)).span_to_source_location((((statement)->span()).value())))))))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("while ("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(condition)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
{
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((last_control_flow).enter_loop()));
ByteString const code = TRY((((*this).codegen_block(block))));
(((*this).control_flow_state) = last_control_flow);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,code)));
}

(add_newline = false);
__jakt_var_618 = output; goto __jakt_label_526;

}
__jakt_label_526:; __jakt_var_618.release_value(); }));
};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_block(block)))));
};/*case end*/
case 14 /* Garbage */: {
{
utility::panic(TRY(ByteString::from_utf8("Garbage statement in codegen"sv)));
}
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_619; {
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(var_decl)))))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> v = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(v)))))));
}

}
}

__jakt_var_619 = output; goto __jakt_label_527;

}
__jakt_label_527:; __jakt_var_619.release_value(); }));
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;ids::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<typename types::CheckedExpression> const& init = __jakt_match_value.init;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_620; {
NonnullRefPtr<types::CheckedVariable> const var = ((((*this).program))->get_variable(var_id));
ByteString output = TRY(ByteString::from_utf8(""sv));
NonnullRefPtr<typename types::Type> const var_type = ((((*this).program))->get_type(((var)->type_id)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((var)->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
if (((!(((var)->is_mutable))) && (!((((var_type)->__jakt_init_index() == 28 /* Reference */) || ((var_type)->__jakt_init_index() == 29 /* MutableReference */)))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("const "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((var)->name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(init)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";"sv)))));
__jakt_var_620 = output; goto __jakt_label_528;

}
__jakt_label_528:; __jakt_var_620.release_value(); }));
};/*case end*/
case 13 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;JaktInternal::DynamicArray<ByteString> const& lines = __jakt_match_value.lines;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_621; {
ByteString output = TRY(ByteString::from_utf8(""sv));
{
JaktInternal::ArrayIterator<ByteString> _magic = ((lines).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString line = (_magic_value.value());
{
ByteString escaped_line = line;
(escaped_line = ((escaped_line).replace(TRY(ByteString::from_utf8("\\\""sv)),TRY(ByteString::from_utf8("\""sv)))));
(escaped_line = ((escaped_line).replace(TRY(ByteString::from_utf8("\\\\"sv)),TRY(ByteString::from_utf8("\\"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,escaped_line)));
}

}
}

__jakt_var_621 = output; goto __jakt_label_529;

}
__jakt_label_529:; __jakt_var_621.release_value(); }));
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_622; {
ByteString output = TRY(ByteString::from_utf8(""sv));
if ((((((*this).debug_info)).statement_span_comments) && ((((statement)->span())).has_value()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("\n#line {}\n"sv)),TRY((((((*this).debug_info)).span_to_source_location((((statement)->span()).value())))))))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("if ("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(condition)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_block(then_block)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((else_statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((TRY(ByteString::from_utf8("else "sv))) + (TRY((((*this).codegen_statement((else_statement.value()))))))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
(add_newline = false);
__jakt_var_622 = output; goto __jakt_label_530;

}
__jakt_label_530:; __jakt_var_622.release_value(); }));
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_623; {
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((((((*this).entered_yieldable_blocks)).size())) == (static_cast<size_t>(0ULL)))){
utility::panic(TRY(ByteString::from_utf8("Must be in a block to yield"sv)));
}
JaktInternal::Tuple<ByteString,ByteString> const var_name_end_label_ = (((((*this).entered_yieldable_blocks)).last()).value());
ByteString const var_name = ((var_name_end_label_).template get<0>());
ByteString const end_label = ((var_name_end_label_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,var_name)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; goto "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,end_label)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";\n"sv)))));
__jakt_var_623 = output; goto __jakt_label_531;

}
__jakt_label_531:; __jakt_var_623.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
if (add_newline){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_function_generic_parameters(NonnullRefPtr<types::CheckedFunction> const function) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if ((!(((((((function)->generics))->params)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("template <"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_template_parameter_names(((((function)->generics))->params))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">\n"sv)))));
}
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_function_predecl(NonnullRefPtr<types::CheckedFunction> const function,bool const as_method,bool const allow_generics) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((allow_generics || (!(((((((function)->generics))->params)).is_empty())))) && ((((function)->linkage)).__jakt_init_index() == 1 /* External */))){
return TRY(ByteString::from_utf8(""sv));
}
if (((function)->is_comptime)){
return TRY(ByteString::from_utf8(""sv));
}
if (((((function)->force_inline)).__jakt_init_index() == 2 /* ForceInline */)){
return TRY(ByteString::from_utf8(""sv));
}
if (((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */)){
return TRY(ByteString::from_utf8(""sv));
}
if (((((function)->linkage)).__jakt_init_index() == 1 /* External */)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("extern "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_generic_parameters(function)))))));
if (((((function)->return_type_id)).equals(types::never_type_id()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("[[noreturn]] "sv)))));
}
if (((TRY((((((function)->name_for_codegen())).as_name_for_definition())))) == (TRY(ByteString::from_utf8("main"sv))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("ErrorOr<int>"sv)))));
}
else {
if ((as_method && TRY((((function)->is_static()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("static "sv)))));
}
if (((function)->is_virtual)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("virtual "sv)))));
}
ByteString const naked_return_type = TRY((((*this).codegen_type(((function)->return_type_id)))));
ByteString const return_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((function)->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("ErrorOr<{}>"sv)),naked_return_type))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(naked_return_type);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,return_type)));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((function)->name_for_codegen())).as_name_for_definition()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((first && ((((((param).variable))->name)) == (TRY(ByteString::from_utf8("this"sv)))))){
continue;
}
if (first){
(first = false);
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}

NonnullRefPtr<typename types::Type> const param_type = ((((*this).program))->get_type(((((param).variable))->type_id)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((((param).variable))->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
if (((!(((((param).variable))->is_mutable))) && (!((((param_type)->__jakt_init_index() == 28 /* Reference */) || ((param_type)->__jakt_init_index() == 29 /* MutableReference */)))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("const "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
if (((!(TRY((((function)->is_static()))))) && (!(TRY((((function)->is_mutating()))))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" const"sv)))));
}
if (((function)->is_override)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" override"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::enum_constructor_result_type(types::CheckedEnum const enum_,JaktInternal::Optional<ByteString> const generic_parameter_list) {
{
ByteString result = ((enum_).name);
if ((!(((((enum_).generic_parameters)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(result,TRY((__jakt_format((StringView::from_string_literal("<{}>"sv)),(generic_parameter_list.value())))))));
}
if (((enum_).is_boxed)){
(result = TRY((__jakt_format((StringView::from_string_literal("ErrorOr<NonnullRefPtr<{}>>"sv)),result))));
}
return result;
}
}

ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>>> codegen::CodeGenerator::codegen_enum_field_lists(types::CheckedEnum const enum_) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> common_fields = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({}))));
JaktInternal::Set<ByteString> common_field_names = (TRY((Set<ByteString>::create_with_values({}))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((((*this).program))->get_variable(((field).variable_id)));
ByteString const name = TRY((((((variable)->name_for_codegen())).as_name_for_definition())));
TRY((((common_fields).push((Tuple{name, TRY((((*this).codegen_type(((variable)->type_id)))))})))));
TRY((((common_field_names).add(name))));
}

}
}

JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> variant_field_list = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>::create_with({}))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).variants)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t variant_index = (_magic_value.value());
{
types::CheckedEnumVariant const variant = ((((enum_).variants))[variant_index]);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const fields = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>, ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue((TRY((DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({})))));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<ids::VarId> const& own_fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> __jakt_var_624; {
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> fields = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({}))));
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((own_fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((((*this).program))->get_variable(field));
if ((!(((common_field_names).contains(((variable)->name)))))){
TRY((((fields).push((Tuple{TRY((((((variable)->name_for_codegen())).as_name_for_definition()))), TRY((((*this).codegen_type(((variable)->type_id)))))})))));
}
}

}
}

__jakt_var_624 = fields; goto __jakt_label_532;

}
__jakt_label_532:; __jakt_var_624.release_value(); }));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> __jakt_var_625; {
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> fields = (TRY((DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({}))));
TRY((((fields).push((Tuple{TRY(ByteString::from_utf8("value"sv)), TRY((((*this).codegen_type(type_id))))})))));
__jakt_var_625 = fields; goto __jakt_label_533;

}
__jakt_label_533:; __jakt_var_625.release_value(); }));
};/*case end*/
default: {
{
utility::todo(TRY((__jakt_format((StringView::from_string_literal("codegen enum variant: {}"sv)),variant))));
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
TRY((((variant_field_list).push((Tuple{((variant).name()), fields})))));
}

}
}

return (Tuple{common_fields, variant_field_list});
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_match_body(types::CheckedMatchBody const body,ids::TypeId const return_type_id) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_block(block)))))));
if ((((return_type_id).equals(types::void_type_id())) || ((return_type_id).equals(types::unknown_type_id())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return JaktInternal::ExplicitValue<void>();\n"sv)))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
{
if (((((((expr)->type())).equals(types::void_type_id())) || ((((expr)->type())).equals(types::never_type_id()))) || (((((expr)->type())).equals(types::unknown_type_id())) && (!(((expr)->__jakt_init_index() == 25 /* OptionalNone */)))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return ("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("), JaktInternal::ExplicitValue<void>();\n"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return JaktInternal::ExplicitValue("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(");\n"sv)))));
}

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
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_ak_formatter(ByteString const name,JaktInternal::DynamicArray<ByteString> const generic_parameter_names,ByteString const template_args) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
ByteString const generic_type_args = TRY((utility::join(generic_parameter_names,TRY(ByteString::from_utf8(", "sv)))));
ByteString qualified_name = TRY(ByteString::from_utf8(""sv));
{
JaktInternal::ArrayIterator<ByteString> _magic = ((((*this).namespace_stack)).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString namespace_ = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(qualified_name,TRY((__jakt_format((StringView::from_string_literal("{}::"sv)),namespace_))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(qualified_name,name)));
if ((!(((generic_parameter_names).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(qualified_name,TRY((__jakt_format((StringView::from_string_literal("<{}>\n"sv)),generic_type_args))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("} // namespace Jakt\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("template<{}>"sv)),template_args))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("struct Jakt::Formatter<Jakt::{}> : Jakt::Formatter<Jakt::StringView>"sv)),qualified_name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::{} const& value) {{\n"sv)),qualified_name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, MUST(value.debug_description()));"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return format_error;"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("};\n"sv)))));
return TRY((((output) + (TRY(ByteString::from_utf8("namespace Jakt {\n"sv))))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<types::FunctionGenericParameter> const parameters,JaktInternal::DynamicArray<ByteString>& names) {
{
JaktInternal::DynamicArray<ids::TypeId> ids = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((parameters).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter parameter = (_magic_value.value());
{
TRY((((ids).push(((((parameter).checked_parameter)).type_id)))));
}

}
}

return TRY((((*this).codegen_template_parameter_names(ids,names))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<types::FunctionGenericParameter> const parameters) {
{
JaktInternal::DynamicArray<ByteString> names = (TRY((DynamicArray<ByteString>::create_with({}))));
return TRY((((*this).codegen_template_parameter_names(parameters,((names))))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters,JaktInternal::DynamicArray<ByteString>& names) {
{
JaktInternal::DynamicArray<ids::TypeId> ids = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((parameters).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter parameter = (_magic_value.value());
{
TRY((((ids).push(((parameter).type_id)))));
}

}
}

return TRY((((*this).codegen_template_parameter_names(ids,names))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters) {
{
JaktInternal::DynamicArray<ByteString> names = (TRY((DynamicArray<ByteString>::create_with({}))));
return TRY((((*this).codegen_template_parameter_names(parameters,((names))))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<ids::TypeId> const parameters,JaktInternal::DynamicArray<ByteString>& names) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((parameters).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId id = (_magic_value.value());
{
if (first){
(first = false);
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}

if (((((((*this).program))->get_type(id)))->__jakt_init_index() == 18 /* TypeVariable */)){
bool const is_value = (((((*this).program))->get_type(id)))->as.TypeVariable.is_value;
if (is_value){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto "sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("typename "sv)))));
}

}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("typename "sv)))));
}

ByteString const name = TRY((((*this).codegen_type(id))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,name)));
TRY((((((names))).push(name))));
}

}
}

return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_method_call(NonnullRefPtr<typename types::CheckedExpression> const expr,types::CheckedCall const call,bool const is_optional) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((call).callee_throws)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).current_error_handler()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("(("sv)))));
}
ByteString const object = TRY((((*this).codegen_expression_and_deref_if_generic_and_needed(expr))));
if ((((((call).function_id)).has_value()) && ((((call).force_inline)).__jakt_init_index() == 2 /* ForceInline */))){
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function((((call).function_id).value())));
bool const is_mutable = (((expr)->is_mutable(((*this).program))) && (((((((((function)->params)).first()).value())).variable))->is_mutable));
NonnullRefPtr<typename types::Type> const reference_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::Type>,ErrorOr<ByteString>>{
auto __jakt_enum_value = (is_mutable);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((types::Type::MutableReference(parser::CheckedQualifiers(false),((expr)->type())))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((types::Type::Reference(parser::CheckedQualifiers(false),((expr)->type())))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<types::CheckedVariable> const var = TRY((types::CheckedVariable::__jakt_create(TRY(ByteString::from_utf8("self"sv)),TRY((((((*this).program))->find_or_add_type_id(reference_type,((((expr)->type())).module),false)))),is_mutable,((expr)->span()),JaktInternal::OptionalNone(),types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
JaktInternal::DynamicArray<types::CheckedParameter> params = (TRY((DynamicArray<types::CheckedParameter>::create_with({types::CheckedParameter(false,var,JaktInternal::OptionalNone())}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((((function)->params))[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})])).iterator());
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

if (((((((function)->block)).statements)).is_empty())){
warnln((StringView::from_string_literal("Shit, block is empty in function ({}): {}"sv)),(((call).function_id).value()),function);
abort();
}
NonnullRefPtr<typename types::CheckedExpression> const lambda = TRY((types::CheckedExpression::Function(JaktInternal::OptionalNone(),(TRY((DynamicArray<types::CheckedCapture>::create_with({})))),params,((function)->can_throw),((function)->return_type_id),((function)->block),((expr)->span()),types::unknown_type_id(),((call).function_id),((function)->function_scope_id))));
JaktInternal::Optional<ByteString> const old_this_replacement = ((*this).this_replacement);
(((*this).this_replacement) = TRY(ByteString::from_utf8("self"sv)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(lambda)))))));
(((*this).this_replacement) = old_this_replacement);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,object)));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> ___arg__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const jakt_____arg__ = ___arg__;
ByteString const _ = ((jakt_____arg__).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const arg = ((jakt_____arg__).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(arg)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
if (((call).callee_throws)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("))"sv)))));
}
return output;
}
NonnullRefPtr<typename types::Type> const expression_type = ((((*this).program))->get_type(((expr)->type())));
parser::ExternalName const name = ((call).name_for_codegen());
ByteString const field_accessor = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = name;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Operator */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *expression_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* RawPtr */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("->"sv)));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = ((((((((((*this).program))->get_struct(id))).record_type)).__jakt_init_index() == 1 /* Class */) && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(object,TRY(ByteString::from_utf8("*this"sv)))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("->"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("."sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = ((((((((((*this).program))->get_struct(id))).record_type)).__jakt_init_index() == 1 /* Class */) && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(object,TRY(ByteString::from_utf8("*this"sv)))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("->"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("."sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = ((((((((*this).program))->get_enum(id))).is_boxed) && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(object,TRY(ByteString::from_utf8("*this"sv)))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("->"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("."sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = ((((expression_type)->is_builtin()) && (!(((expression_type)->__jakt_init_index() == 13 /* JaktString */)))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("."sv)));
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
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Function<ErrorOr<void>()> const generate_method_name = [this, &call, &name, &output]() -> ErrorOr<void> {
{
if (((name).__jakt_init_index() == 2 /* Operator */)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((name).as_name_for_use()))))));
return {};
}
JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = ((call).type_args);
if ((!(((generic_parameters).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("template "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((name).as_name_for_use()))))));
if ((!(((generic_parameters).is_empty())))){
JaktInternal::DynamicArray<ByteString> types = (TRY((DynamicArray<ByteString>::create_with({}))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((generic_parameters).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId gen_param = (_magic_value.value());
{
TRY((((types).push(TRY((((*this).codegen_type_possibly_as_namespace(gen_param,false))))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("<{}>"sv)),TRY((utility::join(types,TRY(ByteString::from_utf8(", "sv)))))))))));
}
}
return {};
}
;
bool const is_called_as_method = ((!(((name).is_prefix()))) && ((!(((field_accessor).is_empty()))) || ((!(is_optional)) && ((name).__jakt_init_index() == 2 /* Operator */))));
if (is_called_as_method){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("(("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,object)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,field_accessor)));
}
else {
TRY((generate_method_name()));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,object)));
}

if (is_optional){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("map([&](auto& _value) { return _value"sv)))));
ByteString access_operator = TRY(ByteString::from_utf8("."sv));
if (((expression_type)->__jakt_init_index() == 20 /* GenericInstance */)){
JaktInternal::DynamicArray<ids::TypeId> const args = (expression_type)->as.GenericInstance.args;
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((args).size()),static_cast<size_t>(0ULL))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((args)[static_cast<i64>(0LL)])));
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
{
if (((((((((*this).program))->get_struct(id))).record_type)).__jakt_init_index() == 1 /* Class */)){
(access_operator = TRY(ByteString::from_utf8("->"sv)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
{
if (((((((((*this).program))->get_struct(id))).record_type)).__jakt_init_index() == 1 /* Class */)){
(access_operator = TRY(ByteString::from_utf8("->"sv)));
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
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,access_operator)));
}
if (is_called_as_method){
TRY((generate_method_name()));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
}
bool first = is_called_as_method;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> ___expr__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const jakt_____expr__ = ___expr__;
ByteString const _ = ((jakt_____expr__).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const expr = ((jakt_____expr__).template get<1>());

if (first){
(first = false);
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
}

}
}

if (is_called_as_method){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
}
if (is_optional){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; })"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
if (((call).callee_throws)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("))"sv)))));
}
return output;
}
}

ErrorOr<void> codegen::CodeGenerator::codegen_for_enum_variants(types::CheckedEnum const& enum_,Function<ErrorOr<ByteString>(ByteString)> const& stmt_fmt,ByteString const index_expr,ByteStringBuilder& output) const {
{
TRY((((((output))).append(TRY((__jakt_format((StringView::from_string_literal("switch ({}) {{\n"sv)),index_expr)))))));
size_t const common_field_count = ((((((enum_))).fields)).size());
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((((enum_))).variants)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t variant_index = (_magic_value.value());
{
types::CheckedEnumVariant const& variant = ((((((((enum_))).variants))[variant_index])));
ByteString const variant_name = ((((variant))).name());
TRY((((((output))).append(TRY((__jakt_format((StringView::from_string_literal("case {} /* {} */:\n"sv)),variant_index,variant_name)))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = ((variant));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* WithValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
{
TRY((((((output))).append(TRY((stmt_fmt(TRY((__jakt_format((StringView::from_string_literal("as.{}.value"sv)),variant_name))))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
{
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((((fields)[(JaktInternal::Range<size_t>{static_cast<size_t>(common_field_count),static_cast<size_t>(9223372036854775807LL)})])).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((((*this).program))->get_variable(field));
ByteString const name = TRY((((((variable)->name_for_codegen())).as_name_for_use())));
TRY((((((output))).append(TRY((stmt_fmt(TRY((__jakt_format((StringView::from_string_literal("as.{}.{}"sv)),variant_name,name))))))))));
}

}
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
TRY((((((output))).append((StringView::from_string_literal("break;\n"sv))))));
}

}
}

TRY((((((output))).append((StringView::from_string_literal("}\n"sv))))));
}
return {};
}

ErrorOr<ByteString> codegen::CodeGenerator::fresh_label() {
{
return TRY((__jakt_format((StringView::from_string_literal("__jakt_label_{}"sv)),((((*this).fresh_label_counter)++)))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::fresh_var() {
{
return TRY((__jakt_format((StringView::from_string_literal("__jakt_var_{}"sv)),((((*this).fresh_var_counter)++)))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_call(types::CheckedCall const call) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if ((((((call).function_id)).has_value()) && ((((((*this).program))->get_function((((call).function_id).value()))))->is_comptime))){
return TRY((__jakt_format((StringView::from_string_literal("fail_comptime_call<{}, \"Comptime function {} called outside Jakt compiler\">()"sv)),TRY((((*this).codegen_type(((call).return_type))))),((call).name))));
}
if (((call).callee_throws)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).current_error_handler()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("(("sv)))));
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
{
ByteString const helper = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("out"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("outln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprint"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warn"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warnln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("format"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("__jakt_format"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,helper)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
ByteString const _ = ((__expr_).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const expr = ((__expr_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
if (((i) != (JaktInternal::checked_sub(((((call).args)).size()),static_cast<size_t>(1ULL))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
{
ByteString const helper = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("out"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("outln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprint"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warn"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warnln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("format"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("__jakt_format"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,helper)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
ByteString const _ = ((__expr_).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const expr = ((__expr_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
if (((i) != (JaktInternal::checked_sub(((((call).args)).size()),static_cast<size_t>(1ULL))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
{
ByteString const helper = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("out"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("outln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprint"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warn"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warnln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("format"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("__jakt_format"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,helper)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
ByteString const _ = ((__expr_).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const expr = ((__expr_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
if (((i) != (JaktInternal::checked_sub(((((call).args)).size()),static_cast<size_t>(1ULL))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprint"sv))) {
{
ByteString const helper = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("out"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("outln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprint"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warn"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warnln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("format"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("__jakt_format"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,helper)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
ByteString const _ = ((__expr_).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const expr = ((__expr_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
if (((i) != (JaktInternal::checked_sub(((((call).args)).size()),static_cast<size_t>(1ULL))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("format"sv))) {
{
ByteString const helper = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((call).name));
if (__jakt_enum_value == TRY(ByteString::from_utf8("print"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("out"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("println"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("outln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprint"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warn"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("eprintln"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("warnln"sv)));
}
else if (__jakt_enum_value == TRY(ByteString::from_utf8("format"sv))) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("__jakt_format"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,helper)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const __expr_ = ((((call).args))[i]);
ByteString const _ = ((__expr_).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const expr = ((__expr_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
if (((i) != (JaktInternal::checked_sub(((((call).args)).size()),static_cast<size_t>(1ULL))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
bool close_enum_type_wrapper = false;
if (((((call).function_id)).has_value())){
ids::FunctionId const function_id = (((call).function_id).value());
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((function_id).module)));
if ((((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */) || ((((function)->type)).__jakt_init_index() == 4 /* ExternalClassConstructor */))){
ids::TypeId const type_id = ((call).return_type);
NonnullRefPtr<typename types::Type> const type = ((((*this).program))->get_type(type_id));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_path(call)))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if (((((struct_).record_type)).__jakt_init_index() == 1 /* Class */)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((call).name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("::__jakt_create"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((call).name_for_codegen())).as_name_for_use()))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
{
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
if (((((struct_).record_type)).__jakt_init_index() == 1 /* Class */)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((struct_).name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(arg)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">::__jakt_create"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((call).name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(arg)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Should be unreachable"sv)));
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
else if (((((function)->type)).__jakt_init_index() == 3 /* ImplicitEnumConstructor */)){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((function)->return_type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
NonnullRefPtr<types::Module> const enum_type_module = ((((*this).program))->get_module(((enum_id).module)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type_possibly_as_namespace(((call).return_type),true)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY(ByteString::from_utf8("::"sv))) + (TRY((((((call).name_for_codegen())).as_name_for_use()))))))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
{
utility::todo(TRY(ByteString::from_utf8("codegen generic enum instance"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("constructor expected enum type"sv)));
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
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_path(call)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((call).name_for_codegen())).as_name_for_use()))))));
}

}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_path(call)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((call).name_for_codegen())).as_name_for_use()))))));
}

JaktInternal::DynamicArray<ids::TypeId> const generic_parameters = ((call).type_args);
if ((!(((generic_parameters).is_empty())))){
JaktInternal::DynamicArray<ByteString> types = (TRY((DynamicArray<ByteString>::create_with({}))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((generic_parameters).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId gen_param = (_magic_value.value());
{
TRY((((types).push(TRY((((*this).codegen_type_possibly_as_namespace(gen_param,false))))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("<{}>"sv)),TRY((utility::join(types,TRY(ByteString::from_utf8(", "sv)))))))))));
}
JaktInternal::DynamicArray<ByteString> arguments = (TRY((DynamicArray<ByteString>::create_with({}))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> arg = (_magic_value.value());
{
TRY((((arguments).push(TRY((((*this).codegen_expression(((arg).template get<1>())))))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("({})"sv)),TRY((utility::join(arguments,TRY(ByteString::from_utf8(","sv)))))))))));
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((call).callee_throws)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("))"sv)))));
}
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_namespace_predecl(NonnullRefPtr<types::Scope> const scope,NonnullRefPtr<types::Module> const current_module) {
{
if ((((((scope)->alias_path)).has_value()) || ((((scope)->import_path_if_extern)).has_value()))){
return TRY(ByteString::from_utf8(""sv));
}
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((((scope)->namespace_name)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("namespace "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,(((scope)->namespace_name).value()))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" {\n"sv)))));
}
{
JaktInternal::DictionaryIterator<ByteString,ids::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::StructId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::StructId> ___struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::StructId> const jakt_____struct_id__ = ___struct_id__;
ByteString const _ = ((jakt_____struct_id__).template get<0>());
ids::StructId const struct_id = ((jakt_____struct_id__).template get<1>());

if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_struct_predecl(struct_)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ids::EnumId> _magic = ((((scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::EnumId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::EnumId> ___enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::EnumId> const jakt_____enum_id__ = ___enum_id__;
ByteString const _ = ((jakt_____enum_id__).template get<0>());
ids::EnumId const enum_id = ((jakt_____enum_id__).template get<1>());

if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_predecl(enum_)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}

}
}

{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_predecl(TRY((((((*this).program))->get_scope(child)))),current_module)))))));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
if ((!(((((function_id).module)).equals(((current_module)->id)))))){
continue;
}
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
if (((((function)->type)).__jakt_init_index() == 3 /* ImplicitEnumConstructor */)){
continue;
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function_id = ((*this).current_function);
(((*this).current_function) = static_cast<JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>>>(function));
ScopeGuard __jakt_var_626([&] {
(((*this).current_function) = previous_function_id);
});
if (((!(((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */))) && ((!(((((function)->type)).__jakt_init_index() == 1 /* Destructor */))) && ([](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(TRY((((((function)->name_for_codegen())).as_name_for_use()))),TRY(ByteString::from_utf8("main"sv))) && ((((((function)->generics))->params)).is_empty()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_predecl(function,false,false)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
}

}
}

}

}
}

if (((((scope)->namespace_name)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return output;
}
}

ErrorOr<JaktInternal::DynamicArray<ids::ModuleId>> codegen::CodeGenerator::topologically_sort_modules() const {
{
JaktInternal::Dictionary<size_t,i64> in_degrees = (TRY((Dictionary<size_t, i64>::create_with_entries({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = ((((((*this).program))->modules)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
{
JaktInternal::ArrayIterator<ids::ModuleId> _magic = ((((module)->imports)).iterator());
for (;;){
JaktInternal::Optional<ids::ModuleId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ModuleId imported_module = (_magic_value.value());
{
i64 const existing = ((in_degrees).get(((imported_module).id))).value_or_lazy_evaluated([&] { return static_cast<i64>(0LL); });
TRY((((in_degrees).set(((imported_module).id),JaktInternal::checked_add(existing,static_cast<i64>(1LL))))));
}

}
}

if ((!(((in_degrees).contains(((((module)->id)).id)))))){
TRY((((in_degrees).set(((((module)->id)).id),static_cast<i64>(0LL)))));
}
}

}
}

JaktInternal::DynamicArray<ids::ModuleId> stack = (TRY((DynamicArray<ids::ModuleId>::create_with({}))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = ((((((*this).program))->modules)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
if (((((in_degrees)[((((module)->id)).id)])) == (static_cast<i64>(0LL)))){
TRY((((stack).push(((module)->id)))));
}
}

}
}

JaktInternal::DynamicArray<ids::ModuleId> sorted_modules = (TRY((DynamicArray<ids::ModuleId>::create_with({}))));
while ((!(((stack).is_empty())))){
ids::ModuleId const id = (((stack).pop()).value());
TRY((((sorted_modules).push(id))));
{
JaktInternal::ArrayIterator<ids::ModuleId> _magic = ((((((((((*this).program))->modules))[((id).id)]))->imports)).iterator());
for (;;){
JaktInternal::Optional<ids::ModuleId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ModuleId imported_module = (_magic_value.value());
{
i64 const module_in_degrees = ((in_degrees)[((imported_module).id)]);
TRY((((in_degrees).set(((imported_module).id),JaktInternal::checked_sub(module_in_degrees,static_cast<i64>(1LL))))));
if (((module_in_degrees) == (static_cast<i64>(1LL)))){
TRY((((stack).push(ids::ModuleId(((imported_module).id))))));
}
}

}
}

}
if (((((sorted_modules).size())) == (((((((*this).program))->modules)).size())))){
return sorted_modules;
}
utility::panic(TRY(ByteString::from_utf8("Cyclic module imports"sv)));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_block(types::CheckedBlock const block) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((((block).yielded_type)).has_value())){
ids::TypeId const yielded_type = (((block).yielded_type).value());
ByteString const type_output = TRY((((*this).codegen_type(yielded_type))));
ByteString const fresh_var = TRY((((*this).fresh_var())));
ByteString const fresh_label = TRY((((*this).fresh_label())));
TRY((((((*this).entered_yieldable_blocks)).push((Tuple{fresh_var, fresh_label})))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("({ Optional<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,type_output)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("> "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,fresh_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> statement = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(statement)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
if (((((block).yielded_type)).has_value())){
JaktInternal::Tuple<ByteString,ByteString> const var_label_ = (((((*this).entered_yieldable_blocks)).pop()).value());
ByteString const var = ((var_label_).template get<0>());
ByteString const label = ((var_label_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,label)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(":; "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,var)));
if ((!(((block).yielded_none)))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".release_value()"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; })"sv)))));
}
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_generic_match(NonnullRefPtr<typename types::CheckedExpression> const expr,JaktInternal::DynamicArray<types::CheckedMatchCase> const cases,ids::TypeId const return_type_id,bool const all_variants_constant) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
bool is_generic_enum = false;
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase case_ = (_magic_value.value());
{
if (((case_).__jakt_init_index() == 0 /* EnumVariant */)){
(is_generic_enum = true);
break;
}
}

}
}

bool const match_values_all_constant = (all_variants_constant && (!(is_generic_enum)));
ByteString const cpp_match_result_type = TRY((((*this).codegen_type(return_type_id))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((__jakt_format((StringView::from_string_literal("([&]() -> JaktInternal::ExplicitValueOrControlFlow<{},{}>"sv)),cpp_match_result_type,TRY((((*this).codegen_function_return_type((((*this).current_function).value()))))))))) + (TRY(ByteString::from_utf8("{\n"sv)))))))));
if (is_generic_enum){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer("sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto __jakt_enum_value = ("sv)))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(");\n"sv)))));
bool has_default = false;
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase case_ = (_magic_value.value());
{
JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> const defaults = ((case_).common.init_common.defaults);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = case_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
ids::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
types::CheckedMatchBody const& body = __jakt_match_value.body;
{
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(subject_type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Unexpected type in IsEnumVariant: {}"sv)),((((*this).program))->get_type(subject_type_id))))));
}
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
})));
i64 variant_index = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if (((((variant).name())) == (name))){
break;
}
((variant_index++));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("if (__jakt_enum_value.__jakt_init_index() == {} /* {} */) {{\n"sv)),variant_index,name))))));
ByteString variant_type_name = TRY(ByteString::from_utf8(""sv));
ByteString const qualifier = TRY((((*this).codegen_type_possibly_as_namespace(subject_type_id,true))));
if ((!(((qualifier).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(variant_type_name,TRY(ByteString::from_utf8("typename JaktInternal::RemoveRefPtr<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(variant_type_name,qualifier)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(variant_type_name,TRY(ByteString::from_utf8(">::"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(variant_type_name,name)));
if ((!(((args).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto& __jakt_match_value = __jakt_enum_value.as."sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((((((enum_).variants))[variant_index])).name()))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";\n"sv)))));
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument arg = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto& "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((arg).binding))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = __jakt_match_value."sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((arg).name).try_value_or_lazy_evaluated([&]() -> ErrorOr<ByteString> { return TRY(ByteString::from_utf8("value"sv)); }))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";\n"sv)))));
}

}
}

}
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((defaults).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> default_ = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(default_)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_match_body(body,return_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;bool const& has_arguments = __jakt_match_value.has_arguments;
types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
{
if (has_arguments){
utility::panic(TRY(ByteString::from_utf8("Bindings should not be present in a generic else"sv)));
}
(has_default = true);
if (first){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("else {\n"sv)))));
}

{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((defaults).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> default_ = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(default_)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_match_body(body,return_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expression = __jakt_match_value.expression;
types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("else "sv)))));
}
if (((expression)->__jakt_init_index() == 9 /* Range */)){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const from = (expression)->as.Range.from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const to = (expression)->as.Range.to;
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("if (__jakt_enum_value"sv)))));
if (((from).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" >= "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression((from.value()))))))));
}
if (((to).has_value())){
if (((from).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("&& __jakt_enum_value "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("< "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression((to.value()))))))));
}
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("if (__jakt_enum_value == "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expression)))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(") {\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_match_body(body,return_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;ids::TypeId const& type = __jakt_match_value.type;
types::CheckedMatchBody const& body = __jakt_match_value.body;
JaktInternal::Optional<types::ClassInstanceRebind> const& rebind_name = __jakt_match_value.rebind_name;
utility::Span const& marker_span = __jakt_match_value.marker_span;
{
ByteString const type_name = TRY((((*this).codegen_type_possibly_as_namespace(type,true))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("if (is<{}>(__jakt_enum_value.ptr())) {{\n"sv)),type_name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("auto {} = NonnullRefPtr {{ *static_cast<RawPtr<{}>>(__jakt_enum_value.ptr()) }};\n"sv)),TRY((((rebind_name).map([](auto& _value) { return _value.name; })).try_value_or_lazy_evaluated([&]() -> ErrorOr<ByteString> { return TRY(ByteString::from_utf8("__jakt_match_value"sv)); }))),type_name))))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((defaults).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> default_ = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(default_)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_match_body(body,return_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
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
(first = false);
}

}
}

if ((((return_type_id).equals(types::void_type_id())) || ((return_type_id).equals(types::unknown_type_id())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return JaktInternal::ExplicitValue<void>();\n"sv)))));
}
else if ((!(has_default))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("VERIFY_NOT_REACHED();\n"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}())"sv)))));
return TRY((((((*this).control_flow_state)).apply_control_flow_macro(output,(((((*this).current_function).value()))->return_type_id),(((((*this).current_function).value()))->can_throw),cpp_match_result_type))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_debug_description_getter(types::CheckedStruct const struct_,bool const is_inline) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((!(is_inline)) && (!(((((struct_).generic_parameters)).is_empty()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("template <"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_template_parameter_names(((struct_).generic_parameters))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">\n"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("ErrorOr<ByteString> "sv)))));
if ((!(is_inline))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type_possibly_as_namespace(((struct_).type_id),true)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("::"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("debug_description() const { "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto builder = ByteStringBuilder::create();"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("TRY(builder.append(\"{}(\"sv));"sv)),TRY((((((struct_).name_for_codegen())).as_name_for_use())))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};\n"sv)))));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const field_var = ((((*this).program))->get_variable(((field).variable_id)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("TRY(JaktInternal::PrettyPrint::output_indentation(builder));"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("TRY(builder.appendff(\"{}: "sv)),TRY((((((field_var)->name_for_codegen())).as_name_for_use())))))))));
if (TRY((((((*this).program))->is_string(((field_var)->type_id)))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\\\"{}\\\""sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{}"sv)))));
}

if (((i) != (JaktInternal::checked_sub(((((struct_).fields)).size()),static_cast<size_t>(1ULL))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\", "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((field_var)->type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((((((*this).program))->get_struct(struct_id))).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("*"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
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
}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
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
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((((field_var)->name_for_codegen())).as_name_for_use())))) + (TRY(ByteString::from_utf8("));\n"sv)))))))));
((i++));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("TRY(builder.append(\")\"sv));"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return builder.to_string();"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" }\n"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_lambda_block(bool const can_throw,types::CheckedBlock const block,ids::TypeId const return_type_id) {
{
ByteString output = TRY(ByteString::from_utf8("{\n"sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_block(block)))))));
if ((can_throw && ((return_type_id).equals(types::builtin(types::BuiltinType::Void()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return {};\n"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_match(NonnullRefPtr<typename types::CheckedExpression> const expr,JaktInternal::DynamicArray<types::CheckedMatchCase> const match_cases,ids::TypeId const type_id,bool const all_variants_constant) {
{
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((((*this).control_flow_state)).enter_match()));
ByteString output = TRY(ByteString::from_utf8(""sv));
NonnullRefPtr<typename types::Type> const expr_type = ((((*this).program))->get_type(((expr)->type())));
if (((expr_type)->__jakt_init_index() == 25 /* Enum */)){
ids::EnumId const enum_id = (expr_type)->as.Enum.value;
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_match(((((*this).program))->get_enum(enum_id)),expr,match_cases,type_id,all_variants_constant)))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_generic_match(expr,match_cases,type_id,all_variants_constant)))))));
}

(((*this).control_flow_state) = last_control_flow);
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_namespace_specializations(NonnullRefPtr<types::Scope> const scope,NonnullRefPtr<types::Module> const current_module) {
{
if ((((((scope)->alias_path)).has_value()) || ((((scope)->import_path_if_extern)).has_value()))){
return TRY(ByteString::from_utf8(""sv));
}
JaktInternal::Set<ids::TypeId> seen_types = (TRY((Set<ids::TypeId>::create_with_values({}))));
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((((scope)->namespace_name)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY(ByteString::from_utf8("namespace "sv))) + ((((scope)->namespace_name).value())))))) + (TRY(ByteString::from_utf8(" {\n"sv)))))))));
}
{
JaktInternal::ArrayIterator<bool> _magic = (((TRY((DynamicArray<bool>::create_with({false, true}))))).iterator());
for (;;){
JaktInternal::Optional<bool> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
bool define_pass = (_magic_value.value());
{
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
JaktInternal::Optional<ByteString> const value = TRY((((*this).codegen_namespace_specialization(function_id,JaktInternal::OptionalNone(),scope,current_module,define_pass))));
if (((value).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,(value.value()))));
}
}

}
}

}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ids::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::StructId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::StructId> ___struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::StructId> const jakt_____struct_id__ = ___struct_id__;
ByteString const _ = ((jakt_____struct_id__).template get<0>());
ids::StructId const struct_id = ((jakt_____struct_id__).template get<1>());

if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if (((seen_types).contains(((struct_).type_id)))){
continue;
}
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((struct_).scope_id)))));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
JaktInternal::Optional<ByteString> const value = TRY((((*this).codegen_namespace_specialization(function_id,((struct_).type_id),scope,current_module,define_pass))));
if (((value).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,(value.value()))));
}
}

}
}

}

}
}

}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ids::EnumId> _magic = ((((scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::EnumId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::EnumId> ___enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::EnumId> const jakt_____enum_id__ = ___enum_id__;
ByteString const _ = ((jakt_____enum_id__).template get<0>());
ids::EnumId const enum_id = ((jakt_____enum_id__).template get<1>());

if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
if (((seen_types).contains(((enum_).type_id)))){
continue;
}
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((enum_).scope_id)))));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
JaktInternal::Optional<ByteString> const value = TRY((((*this).codegen_namespace_specialization(function_id,((enum_).type_id),scope,current_module,define_pass))));
if (((value).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,(value.value()))));
}
}

}
}

}

}
}

}

}
}

}

}
}

{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child_scope_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((((*this).program))->get_scope(child_scope_id))));
if (((((child_scope)->namespace_name)).has_value())){
ByteString const name = (((child_scope)->namespace_name).value());
TRY((((((*this).namespace_stack)).push(name))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_specializations(child_scope,current_module)))))));
JaktInternal::Optional<ByteString> const dummy = ((((*this).namespace_stack)).pop());
}
}

}
}

if (((((scope)->namespace_name)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return output;
}
}

ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> codegen::CodeGenerator::extract_dependencies_from_struct(ids::StructId const struct_id,JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph,bool const top_level,JaktInternal::DynamicArray<ids::TypeId> const args) const {
{
JaktInternal::DynamicArray<ids::TypeId> dependencies = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if ((((((struct_).definition_linkage)).__jakt_init_index() == 1 /* External */) && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(((struct_).name),TRY(ByteString::from_utf8("Optional"sv))))){
return dependencies;
}
if ((((((struct_).record_type)).__jakt_init_index() == 1 /* Class */) && (!(top_level)))){
return dependencies;
}
if ((!(((args).is_empty())))){
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId inner_type = (_magic_value.value());
{
JaktInternal::DynamicArray<ids::TypeId> const inner_dependencies = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ids::TypeId>, ErrorOr<JaktInternal::DynamicArray<ids::TypeId>>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(inner_type));
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from(inner_type,dependency_graph,false)))));
};/*case end*/
case 24 /* Struct */: {
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from(inner_type,dependency_graph,false)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<ids::TypeId>::create_with({})))));
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
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

}

}
}

}
JaktInternal::Optional<ids::StructId> super_struct_id = ((struct_).super_struct_id);
while (((super_struct_id).has_value())){
types::CheckedStruct const super_struct = ((((*this).program))->get_struct((super_struct_id.value())));
JaktInternal::DynamicArray<ids::TypeId> const super_dependencies = TRY((((*this).extract_dependencies_from_struct((super_struct_id.value()),dependency_graph,true,(TRY((DynamicArray<ids::TypeId>::create_with({}))))))));
TRY((((dependencies).push_values(((super_dependencies))))));
(super_struct_id = ((super_struct).super_struct_id));
}
TRY((((dependencies).push(((struct_).type_id)))));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
ids::TypeId const type_id = ((((((*this).program))->get_variable(((field).variable_id))))->type_id);
JaktInternal::DynamicArray<ids::TypeId> const inner_dependencies = TRY((((*this).extract_dependencies_from(type_id,dependency_graph,false))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

}

}
}

return dependencies;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_enum_type(ids::EnumId const id,bool const as_namespace) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((id).module)));
types::CheckedEnum const checked_enum = ((((*this).program))->get_enum(id));
if (((!(as_namespace)) && ((checked_enum).is_boxed))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("NonnullRefPtr<"sv)))));
ByteString const qualifier = TRY((((*this).codegen_namespace_qualifier(((checked_enum).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
if ((!(((qualifier).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("typename "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,qualifier)));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((checked_enum).name))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
else {
ByteString const qualifier = TRY((((*this).codegen_namespace_qualifier(((checked_enum).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
if ((!(((qualifier).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,qualifier)));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((checked_enum).name))));
}

return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_expression_and_deref_if_generic_and_needed(NonnullRefPtr<typename types::CheckedExpression> const expression) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((expression)->type())));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_627; {
ByteString const contents = TRY((((*this).codegen_expression(expression))));
__jakt_var_627 = TRY((__jakt_format((StringView::from_string_literal("(*([]<typename V>(V&& value) {{ if constexpr (IsSpecializationOf<V, NonnullRefPtr>) return &*value; else return &value; }})({}))"sv)),contents))); goto __jakt_label_534;

}
__jakt_label_534:; __jakt_var_627.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_expression(expression)))));
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

ErrorOr<ByteString> codegen::CodeGenerator::codegen_checked_binary_op_assignment(NonnullRefPtr<typename types::CheckedExpression> const lhs,NonnullRefPtr<typename types::CheckedExpression> const rhs,parser::BinaryOperator const op,ids::TypeId const type_id) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto& _jakt_ref = "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(lhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("_jakt_ref = JaktInternal::"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* AddAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_add"sv)));
};/*case end*/
case 28 /* SubtractAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_sub"sv)));
};/*case end*/
case 29 /* MultiplyAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_mul"sv)));
};/*case end*/
case 31 /* DivideAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_div"sv)));
};/*case end*/
case 30 /* ModuloAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("checked_mod"sv)));
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Checked binary operation assignment codegen is not supported for BinaryOperator::{}"sv)),op))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">(_jakt_ref, "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(rhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(");"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_struct(types::CheckedStruct const struct_) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((((struct_).definition_linkage)).__jakt_init_index() == 1 /* External */)){
return TRY(ByteString::from_utf8(""sv));
}
bool struct_is_generic = false;
JaktInternal::DynamicArray<ByteString> generic_parameter_names = (TRY((DynamicArray<ByteString>::create_with({}))));
ByteString template_parameters = TRY(ByteString::from_utf8(""sv));
if ((!(((((struct_).generic_parameters)).is_empty())))){
(struct_is_generic = true);
(template_parameters = TRY((((*this).codegen_template_parameter_names(((struct_).generic_parameters),((generic_parameter_names)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("template <{}>"sv)),template_parameters))))));
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */: {
{
ByteString class_name_with_generics = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY((((((struct_).name_for_codegen())).as_name_for_definition()))))));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8(", "sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8("<"sv)))));
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY((((*this).codegen_type(((generic_parameter).type_id))))))));
}

}
}

if ((!(((((struct_).generic_parameters)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8(">"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("class {} :"sv)),TRY((((((struct_).name_for_codegen())).as_name_for_definition())))))))));
if (((((struct_).super_struct_id)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("public {}"sv)),TRY((((*this).codegen_struct_type((((struct_).super_struct_id).value()),true))))))))));
if ((!(((((((((*this).program))->get_struct((((struct_).super_struct_id).value())))).record_type)).__jakt_init_index() == 1 /* Class */)))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal(", public RefCounted<{}>, public Weakable<{}>"sv)),class_name_with_generics,class_name_with_generics))))));
}
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("public RefCounted<{}>, public Weakable<{}> "sv)),class_name_with_generics,class_name_with_generics))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((struct_).scope_id)))));
bool has_destructor = false;
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___function_ids__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____function_ids__ = ___function_ids__;
ByteString const _ = ((jakt_____function_ids__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const function_ids = ((jakt_____function_ids__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((function_ids).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
if (((((function)->type)).__jakt_init_index() == 1 /* Destructor */)){
(has_destructor = true);
}
}

}
}

}

}
}

if ((!(has_destructor))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("  public:\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("virtual ~{}() = default;\n"sv)),TRY((((((struct_).name_for_codegen())).as_name_for_definition())))))))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Struct */: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("struct {}"sv)),TRY((((((struct_).name_for_codegen())).as_name_for_definition())))))))));
if (((((struct_).super_struct_id)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal(": public {}"sv)),TRY((((*this).codegen_struct_type((((struct_).super_struct_id).value()),true))))))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" {\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("  public:\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* SumEnum */: {
{
utility::todo(TRY(ByteString::from_utf8("codegen_struct SumEnum"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* ValueEnum */: {
{
utility::todo(TRY(ByteString::from_utf8("codegen_struct ValueEnum"sv)));
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
Function<ErrorOr<void>(types::CheckedVisibility)> const set_access_level = [&output](types::CheckedVisibility visibility) -> ErrorOr<void> {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = visibility;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Restricted */: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("public: "sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Public */: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("public: "sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Private */: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("private: "sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); return {};
}
return {};
}
;
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((((*this).program))->get_variable(((field).variable_id)));
TRY((set_access_level(((variable)->visibility))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((variable)->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((variable)->name_for_codegen())).as_name_for_definition()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";"sv)))));
}

}
}

NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((struct_).scope_id)))));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function_id = ((*this).current_function);
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
TRY((set_access_level(((function)->visibility))));
(((*this).current_function) = static_cast<JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>>>(function));
ScopeGuard __jakt_var_628([&] {
(((*this).current_function) = previous_function_id);
});
if (((((function)->type)).__jakt_init_index() == 1 /* Destructor */)){
if (((((struct_).generic_parameters)).is_empty())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_destructor_predecl(((struct_)))))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_destructor(((struct_)),((function)),true)))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
else if (((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */)){
if (((((struct_).generic_parameters)).is_empty())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_constructor_predecl(function)))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_constructor(function,true)))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
else if (((((function)->force_inline)).__jakt_init_index() == 1 /* MakeDefinitionAvailable */)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function(function,true)))))));
}
else if (struct_is_generic){
if ((!(((((function)->specialization_index)).has_value())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function(function,true)))))));
}
}
else if ((((((((function)->generics))->params)).is_empty()) || (!(((((function)->specialization_index)).has_value()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_predecl(function,true,false)))))));
}
}

}
}

}

}
}

TRY((set_access_level(types::CheckedVisibility::Public())));
if (((((struct_).generic_parameters)).is_empty())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("ErrorOr<ByteString> debug_description() const;\n"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_debug_description_getter(struct_,true)))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("};"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((*this).deferred_output),TRY((((*this).codegen_ak_formatter(TRY((((((struct_).name_for_codegen())).as_name_for_definition()))),generic_parameter_names,template_parameters)))))));
return output;
}
}

codegen::CodeGenerator::CodeGenerator(NonnullRefPtr<compiler::Compiler> a_compiler, NonnullRefPtr<types::CheckedProgram> a_program, codegen::ControlFlowState a_control_flow_state, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> a_entered_yieldable_blocks, ByteString a_deferred_output, JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> a_current_function, bool a_inside_defer, codegen::CodegenDebugInfo a_debug_info, JaktInternal::DynamicArray<ByteString> a_namespace_stack, size_t a_fresh_var_counter, size_t a_fresh_label_counter, JaktInternal::Optional<ByteString> a_this_replacement, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> a_generic_inferences): compiler(move(a_compiler)), program(move(a_program)), control_flow_state(move(a_control_flow_state)), entered_yieldable_blocks(move(a_entered_yieldable_blocks)), deferred_output(move(a_deferred_output)), current_function(move(a_current_function)), inside_defer(move(a_inside_defer)), debug_info(move(a_debug_info)), namespace_stack(move(a_namespace_stack)), fresh_var_counter(move(a_fresh_var_counter)), fresh_label_counter(move(a_fresh_label_counter)), this_replacement(move(a_this_replacement)), generic_inferences(move(a_generic_inferences)){}

ids::TypeId codegen::CodeGenerator::map_type(ids::TypeId const type_id) const {
{
if (((((*this).generic_inferences)).has_value())){
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const mapping = (((*this).generic_inferences).value());
return ((mapping).get(type_id)).value_or_lazy_evaluated([&] { return type_id; });
}
return type_id;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_function(NonnullRefPtr<types::CheckedFunction> const function,bool const as_method) {
{
if (((function)->is_comptime)){
return TRY(ByteString::from_utf8(""sv));
}
return TRY((((*this).codegen_function_in_namespace(function,JaktInternal::OptionalNone(),as_method,false,JaktInternal::OptionalNone()))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_generic_type_instance(ids::StructId const id,JaktInternal::DynamicArray<ids::TypeId> const args,bool const as_namespace) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((id).module)));
ByteString namespace_ = TRY(ByteString::from_utf8(""sv));
if (((type_module)->is_prelude())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(namespace_,TRY(ByteString::from_utf8("JaktInternal::"sv)))));
}
JaktInternal::Optional<ids::StructId> const inner_weak_ptr_struct_id = TRY((((((*this).program))->check_and_extract_weak_ptr(id,args))));
if (((inner_weak_ptr_struct_id).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("WeakPtr<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,namespace_)));
ids::StructId const inner_struct_id = ((inner_weak_ptr_struct_id).value());
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(inner_struct_id));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_qualifier(((struct_).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((struct_).name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
else {
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
bool const acquired_by_ref = ((!(as_namespace)) && ((((struct_).record_type)).__jakt_init_index() == 1 /* Class */));
if (acquired_by_ref){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("NonnullRefPtr<"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,namespace_)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_qualifier(((struct_).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((struct_).name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId type_id = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type_id)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
if (acquired_by_ref){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
}

return output;
}
}

ErrorOr<JaktInternal::Optional<ByteString>> codegen::CodeGenerator::destructor_name(ids::TypeId const id) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>, ErrorOr<JaktInternal::Optional<ByteString>>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("ByteString"sv)));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_629; {
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
__jakt_var_629 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>,ErrorOr<JaktInternal::Optional<ByteString>>>{
auto __jakt_enum_value = (((((struct_).record_type)).__jakt_init_index() == 1 /* Class */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("NonnullRefPtr"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((((struct_).name_for_codegen())).as_name_for_use()))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_535;

}
__jakt_label_535:; __jakt_var_629.release_value(); }));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_630; {
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
__jakt_var_630 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>,ErrorOr<JaktInternal::Optional<ByteString>>>{
auto __jakt_enum_value = (((((struct_).record_type)).__jakt_init_index() == 1 /* Class */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("NonnullRefPtr"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((((struct_).name_for_codegen())).as_name_for_use()))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_536;

}
__jakt_label_536:; __jakt_var_630.release_value(); }));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_631; {
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
__jakt_var_631 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>,ErrorOr<JaktInternal::Optional<ByteString>>>{
auto __jakt_enum_value = (((((struct_).record_type)).__jakt_init_index() == 1 /* Class */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("NonnullRefPtr"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((((struct_).name_for_codegen())).as_name_for_use()))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_537;

}
__jakt_label_537:; __jakt_var_631.release_value(); }));
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_632; {
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(id));
__jakt_var_632 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>,ErrorOr<JaktInternal::Optional<ByteString>>>{
auto __jakt_enum_value = (((enum_).is_boxed));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("NonnullRefPtr"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(((enum_).name));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_538;

}
__jakt_label_538:; __jakt_var_632.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_633; {
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(id));
__jakt_var_633 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>,ErrorOr<JaktInternal::Optional<ByteString>>>{
auto __jakt_enum_value = (((enum_).is_boxed));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("NonnullRefPtr"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(((enum_).name));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_539;

}
__jakt_label_539:; __jakt_var_633.release_value(); }));
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

ErrorOr<ByteString> codegen::CodeGenerator::codegen_enum_debug_description_getter(types::CheckedEnum const enum_,bool const is_inline) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((!(is_inline)) && (!(((((enum_).generic_parameters)).is_empty()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("template <"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_template_parameter_names(((enum_).generic_parameters))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">\n"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("ErrorOr<ByteString> "sv)))));
if ((!(is_inline))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type_possibly_as_namespace(((enum_).type_id),true)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("::"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("debug_description() const {\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto builder = ByteStringBuilder::create();\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("switch (this->__jakt_init_index()) {"sv)))));
size_t const common_field_count = ((((enum_).fields)).size());
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).variants)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedEnumVariant const variant = ((((enum_).variants))[i]);
ByteString const name = ((variant).name());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("case {} /* {} */: {{\n"sv)),i,name))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("TRY(builder.append(\"{}::{}\"sv));\n"sv)),((enum_).name),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("[[maybe_unused]] auto const& that = this->as.{};\n"sv)),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("TRY(builder.append(\"(\"sv));\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};\n"sv)))));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("TRY(JaktInternal::PrettyPrint::output_indentation(builder));\n"sv)))));
NonnullRefPtr<types::CheckedVariable> const var = ((((*this).program))->get_variable(field));
if (TRY((((((*this).program))->is_string(((var)->type_id)))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("TRY(builder.appendff(\"{}: \\\"{{}}\\\""sv)),TRY((((((var)->name_for_codegen())).as_name_for_use())))))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("TRY(builder.appendff(\"{}: {{}}"sv)),TRY((((((var)->name_for_codegen())).as_name_for_use())))))))));
}

if (((i) != (JaktInternal::checked_sub(((fields).size()),static_cast<size_t>(1ULL))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,common_field_count)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("\", this->common.init_common.{}));\n"sv)),TRY((((((var)->name_for_codegen())).as_name_for_use())))))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("\", that.{}));\n"sv)),TRY((((((var)->name_for_codegen())).as_name_for_use())))))))));
}

((i++));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("TRY(builder.append(\")\"sv));\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("TRY(builder.append(\"{}::{}\"sv));\n"sv)),((enum_).name),name))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("[[maybe_unused]] auto const& that = this->as.{};\n"sv)),name))))));
if (TRY((((((*this).program))->is_string(type_id))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("TRY(builder.appendff(\"(\\\"{}\\\")\", that.value));\n"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("TRY(builder.appendff(\"({})\", that.value));\n"sv)))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("return ByteString(\"{}::{}\"sv);\n"sv)),((enum_).name),name))))));
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
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("break;}\n"sv)))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\nreturn builder.to_string();\n}\n"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_expression(NonnullRefPtr<typename types::CheckedExpression> const expression) {
{
(((*this).generic_inferences) = ((expression)->common.init_common.generic_inferences).value_or_lazy_evaluated_optional([&] { return ((*this).generic_inferences); }));
ScopeGuard __jakt_var_634([&] {
(((*this).generic_inferences) = JaktInternal::OptionalNone());
});
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 33 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.span;
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Unexpected reflect expression at {}"sv)),span))));
}
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& to = __jakt_match_value.to;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_635; {
ByteString output = TRY(ByteString::from_utf8(""sv));
NonnullRefPtr<typename types::Type> const type = ((((*this).program))->get_type(type_id));
ids::TypeId const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Internal error: range expression doesn't have Range type"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("static_cast<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(index_type)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">("sv)))));
if (((from).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression((from.value()))))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("0LL"sv)))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("),static_cast<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(index_type)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">("sv)))));
if (((to).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression((to.value()))))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("9223372036854775807LL"sv)))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")})"sv)))));
__jakt_var_635 = output; goto __jakt_label_540;

}
__jakt_label_540:; __jakt_var_635.release_value(); }));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("JaktInternal::OptionalNone()"sv)));
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY((((TRY(ByteString::from_utf8("static_cast<"sv))) + (TRY((((*this).codegen_type(type_id))))))))) + (TRY(ByteString::from_utf8(">("sv))))))) + (TRY((((*this).codegen_expression(expr))))))))) + (TRY(ByteString::from_utf8(")"sv)))))));
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_expression(expr))))))))) + (TRY(ByteString::from_utf8(".value())"sv)))))));
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_636; {
ByteString const original_string = ((val).to_string());
ByteString const escaped_value = ((original_string).replace(TRY(ByteString::from_utf8("\n"sv)),TRY(ByteString::from_utf8("\\n"sv))));
__jakt_var_636 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((((val).type_id)).equals(types::builtin(types::BuiltinType::JaktString()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY(ByteString::from_utf8("Jakt::ByteString(\""sv))) + (escaped_value))))) + (TRY(ByteString::from_utf8("\"sv)"sv)))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_637; {
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const ids = TRY((((((*this).program))->find_functions_with_name_in_scope(TRY((((((*this).program))->find_type_scope_id(((val).type_id))))),TRY(ByteString::from_utf8("from_string_literal"sv)),false,JaktInternal::OptionalNone()))));
if (((!(((ids).has_value()))) || (((ids.value())).is_empty()))){
utility::panic(TRY(ByteString::from_utf8("Internal error: couldn't find a 'from_string_literal' function despite passing typecheck"sv)));
}
ByteString const name = TRY((((((((((*this).program))->get_function((((ids.value()))[static_cast<i64>(0LL)]))))->name_for_codegen())).as_name_for_use())));
ByteString const error_handler = "";
/*
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((val).may_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((*this).current_error_handler()))));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
*/
__jakt_var_637 = TRY((__jakt_format((StringView::from_string_literal("{}({}::{}(\"{}\"sv))"sv)),error_handler,TRY((((*this).codegen_type(((val).type_id))))),name,escaped_value))); goto __jakt_label_542;

}
__jakt_label_542:; __jakt_var_637.release_value(); }));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_541;

}
__jakt_label_541:; __jakt_var_636.release_value(); }));
};/*case end*/
case 3 /* ByteConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ByteConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY(ByteString::from_utf8("static_cast<u8>(u8'"sv))) + (val))))) + (TRY(ByteString::from_utf8("')"sv)))))));
};/*case end*/
case 5 /* CCharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CCharacterConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY(ByteString::from_utf8("'"sv))) + (val))))) + (TRY(ByteString::from_utf8("'"sv)))))));
};/*case end*/
case 4 /* CharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CharacterConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY(ByteString::from_utf8("static_cast<u32>(U'"sv))) + (val))))) + (TRY(ByteString::from_utf8("')"sv)))))));
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_638; {
ByteString const name = TRY((((((var)->name_for_codegen())).as_name_for_use())));
__jakt_var_638 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (name);
if (__jakt_enum_value == TRY(ByteString::from_utf8("this"sv))) {
return JaktInternal::ExplicitValue(TRY((((*this).this_replacement).try_value_or_lazy_evaluated([&]() -> ErrorOr<ByteString> { return TRY(ByteString::from_utf8("*this"sv)); }))));
}
else {
return JaktInternal::ExplicitValue(name);
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_543;

}
__jakt_label_543:; __jakt_var_638.release_value(); }));
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY((((TRY(ByteString::from_utf8("(("sv))) + (TRY((((*this).codegen_expression(expr))))))))) + (TRY(ByteString::from_utf8(")["sv))))))) + (TRY((((*this).codegen_expression(index))))))))) + (TRY(ByteString::from_utf8("])"sv)))))));
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY((((TRY(ByteString::from_utf8("(("sv))) + (TRY((((*this).codegen_expression(expr))))))))) + (TRY(ByteString::from_utf8(")["sv))))))) + (TRY((((*this).codegen_expression(index))))))))) + (TRY(ByteString::from_utf8("])"sv)))))));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("(({}).map([](auto& _value) {{ return _value.template get<{}>(); }}))"sv)),TRY((((*this).codegen_expression(expr)))),index))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("(({}).template get<{}>())"sv)),TRY((((*this).codegen_expression(expr)))),index))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& name = __jakt_match_value.name;
JaktInternal::Optional<ids::VarId> const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_639; {
ByteString output = TRY(ByteString::from_utf8(""sv));
ByteString const object = TRY((((*this).codegen_expression(expr))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("(("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,object)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
ByteString const var_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((index).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((((((((*this).program))->get_variable((index.value()))))->name_for_codegen())).as_name_for_use()))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(name);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
NonnullRefPtr<typename types::Type> const expression_type = ((((*this).program))->get_type(((expr)->type())));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *expression_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* RawPtr */: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("->"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
{
types::CheckedStruct const structure = ((((*this).program))->get_struct(id));
if ((((((structure).record_type)).__jakt_init_index() == 1 /* Class */) && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(object,TRY(ByteString::from_utf8("*this"sv))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("->"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("."sv)))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
{
types::CheckedStruct const structure = ((((*this).program))->get_struct(id));
if ((((((structure).record_type)).__jakt_init_index() == 1 /* Class */) && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(object,TRY(ByteString::from_utf8("*this"sv))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("->"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("."sv)))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("."sv)))));
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
if (is_optional){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("map([](auto& _value) { return _value"sv)))));
ByteString access_operator = TRY(ByteString::from_utf8("."sv));
if (((expression_type)->__jakt_init_index() == 20 /* GenericInstance */)){
JaktInternal::DynamicArray<ids::TypeId> const args = (expression_type)->as.GenericInstance.args;
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((args).size()),static_cast<size_t>(0ULL))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((args)[static_cast<i64>(0LL)])));
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
{
if (((((((((*this).program))->get_struct(id))).record_type)).__jakt_init_index() == 1 /* Class */)){
(access_operator = TRY(ByteString::from_utf8("->"sv)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
{
if (((((((((*this).program))->get_struct(id))).record_type)).__jakt_init_index() == 1 /* Class */)){
(access_operator = TRY(ByteString::from_utf8("->"sv)));
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
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,access_operator)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,var_name)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; })"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,var_name)));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
__jakt_var_639 = output; goto __jakt_label_544;

}
__jakt_label_544:; __jakt_var_639.release_value(); }));
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_640; {
ByteString output = TRY(ByteString::from_utf8(""sv));
ByteString const object = TRY((((*this).codegen_expression(expr))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("(("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,object)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((expr)->type())));
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* RawPtr */: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("->"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
{
types::CheckedEnum const structure = ((((*this).program))->get_enum(id));
if (((((structure).record_type)).__jakt_init_index() == 3 /* SumEnum */)){
bool const is_boxed = (((structure).record_type)).as.SumEnum.is_boxed;
if ((is_boxed && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(object,TRY(ByteString::from_utf8("*this"sv))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("->common.init_common."sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".common.init_common."sv)))));
}

}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".common.init_common."sv)))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
{
types::CheckedEnum const structure = ((((*this).program))->get_enum(id));
if (((((structure).record_type)).__jakt_init_index() == 3 /* SumEnum */)){
bool const is_boxed = (((structure).record_type)).as.SumEnum.is_boxed;
if ((is_boxed && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(object,TRY(ByteString::from_utf8("*this"sv))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("->common.init_common."sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".common.init_common."sv)))));
}

}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".common.init_common."sv)))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("."sv)))));
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
if (is_optional){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("map([](auto& _value) { return _value."sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,index)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; })"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,index)));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
__jakt_var_640 = output; goto __jakt_label_545;

}
__jakt_label_545:; __jakt_var_640.release_value(); }));
};/*case end*/
case 18 /* ComptimeIndex */: {
{
utility::panic(TRY(ByteString::from_utf8("Internal error: ComptimeIndex should have been replaced by now"sv)));
}
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_block(block)))));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_call(call)))));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedCall const& call = __jakt_match_value.call;
bool const& is_optional = __jakt_match_value.is_optional;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_method_call(expr,call,is_optional)))));
};/*case end*/
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (val);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("true"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("false"sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_641; {
ByteString output = TRY(ByteString::from_utf8("("sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* PreIncrement */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("++"sv)));
};/*case end*/
case 2 /* PreDecrement */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("--"sv)));
};/*case end*/
case 4 /* Negate */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("-"sv)));
};/*case end*/
case 5 /* Dereference */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((expr)->type())));
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* RawPtr */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("*"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6 /* RawAddress */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((((((*this).program))->get_type(((expr)->type()))))->is_boxed(((*this).program))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY(ByteString::from_utf8("const_cast<"sv))) + (TRY((((*this).codegen_type_possibly_as_namespace(type_id,true))))))))) + (TRY(ByteString::from_utf8(">("sv))))))) + (TRY(ByteString::from_utf8("&*"sv)))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((TRY(ByteString::from_utf8("const_cast<"sv))) + (TRY((((*this).codegen_type(type_id))))))))) + (TRY(ByteString::from_utf8(">("sv))))))) + (TRY(ByteString::from_utf8("&"sv)))))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 9 /* LogicalNot */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("!"sv)));
};/*case end*/
case 10 /* BitwiseNot */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("~"sv)));
};/*case end*/
case 16 /* Sizeof */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("sizeof"sv)));
};/*case end*/
case 12 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_642; {
ByteString const is_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_643; {
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(id));
__jakt_var_643 = TRY((((TRY((((*this).codegen_namespace_qualifier(((struct_).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))))) + (TRY((((((struct_).name_for_codegen())).as_name_for_use()))))))); goto __jakt_label_548;

}
__jakt_label_548:; __jakt_var_643.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(type_id)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_642 = TRY((((TRY((((TRY(ByteString::from_utf8("is<"sv))) + (is_type))))) + (TRY(ByteString::from_utf8(">("sv)))))); goto __jakt_label_547;

}
__jakt_label_547:; __jakt_var_642.release_value(); }));
};/*case end*/
case 15 /* IsNone */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("!"sv)));
};/*case end*/
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;types::CheckedTypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_644; {
ids::TypeId final_type_id = ((cast).type_id());
NonnullRefPtr<typename types::Type> const type = ((((*this).program))->get_type(final_type_id));
ByteString const cast_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Fallible */: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_645; {
ids::TypeId const type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Fallible type cast must have Optional result."sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString cast_type = TRY(ByteString::from_utf8("dynamic_cast"sv));
if (((((((*this).program))->get_type(type_id)))->__jakt_init_index() == 24 /* Struct */)){
ids::StructId const struct_id = (((((*this).program))->get_type(type_id)))->as.Struct.value;
if (((((((((*this).program))->get_struct(struct_id))).record_type)).__jakt_init_index() == 1 /* Class */)){
(final_type_id = type_id);
(cast_type = TRY(ByteString::from_utf8("fallible_class_cast"sv)));
}
else if (((((*this).program))->is_integer(type_id))){
(final_type_id = type_id);
(cast_type = TRY(ByteString::from_utf8("fallible_integer_cast"sv)));
}
}
else if (((((*this).program))->is_integer(type_id))){
(final_type_id = type_id);
(cast_type = TRY(ByteString::from_utf8("fallible_integer_cast"sv)));
}
__jakt_var_645 = cast_type; goto __jakt_label_550;

}
__jakt_label_550:; __jakt_var_645.release_value(); }));
};/*case end*/
case 1 /* Infallible */: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_646; {
ByteString cast_type = TRY(ByteString::from_utf8("verify_cast"sv));
if (((((expr)->type())).equals(types::unknown_type_id()))){
(cast_type = TRY(ByteString::from_utf8("assert_type"sv)));
}
else if (((type)->is_boxed(((*this).program)))){
(cast_type = TRY(ByteString::from_utf8("infallible_class_cast"sv)));
}
else if (((((*this).program))->is_integer(type_id))){
(cast_type = TRY(ByteString::from_utf8("infallible_integer_cast"sv)));
}
else if (((type)->__jakt_init_index() == 25 /* Enum */)){
ids::EnumId const enum_id = (type)->as.Enum.value;
if (((((*this).program))->is_integer(((((((*this).program))->get_enum(enum_id))).underlying_type_id)))){
(cast_type = TRY(ByteString::from_utf8("infallible_enum_cast"sv)));
}
else if (((type)->__jakt_init_index() == 26 /* RawPtr */)){
ids::TypeId const inner = (type)->as.RawPtr.value;
(cast_type = TRY(ByteString::from_utf8("reinterpret_cast"sv)));
}
}
else if (((type)->__jakt_init_index() == 26 /* RawPtr */)){
ids::TypeId const inner = (type)->as.RawPtr.value;
(cast_type = TRY(ByteString::from_utf8("reinterpret_cast"sv)));
}
__jakt_var_646 = cast_type; goto __jakt_label_551;

}
__jakt_label_551:; __jakt_var_646.release_value(); }));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_644 = TRY((((TRY((((TRY((((cast_type) + (TRY(ByteString::from_utf8("<"sv))))))) + (TRY((((*this).codegen_type(final_type_id))))))))) + (TRY(ByteString::from_utf8(">("sv)))))); goto __jakt_label_549;

}
__jakt_label_549:; __jakt_var_644.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
ByteString const object = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(type_id)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_expression(expr)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,object)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* PostIncrement */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("++)"sv)));
};/*case end*/
case 3 /* PostDecrement */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("--)"sv)));
};/*case end*/
case 11 /* TypeCast */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("))"sv)));
};/*case end*/
case 12 /* Is */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("))"sv)));
};/*case end*/
case 13 /* IsEnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IsEnumVariant;types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
ids::TypeId const& enum_type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_647; {
ByteString const name = ((enum_variant).name());
ByteString suffix = TRY(ByteString::from_utf8(")"sv));
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(enum_type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Unexpected type in IsEnumVariant: {}"sv)),((((*this).program))->get_type(enum_type_id))))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((enum_).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* SumEnum */: {
{
bool const is_boxed = ((enum_).is_boxed);
if ((is_boxed && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(object,TRY(ByteString::from_utf8("*this"sv))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(suffix,TRY(ByteString::from_utf8("->"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(suffix,TRY(ByteString::from_utf8("."sv)))));
}

i64 variant_index = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
if (((((variant).name())) == (name))){
break;
}
((variant_index++));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(suffix,TRY((__jakt_format((StringView::from_string_literal("__jakt_init_index() == {} /* {} */"sv)),variant_index,name))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* ValueEnum */: {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(suffix,TRY((__jakt_format((StringView::from_string_literal("== {}{}::{}"sv)),TRY((((*this).codegen_namespace_qualifier(((enum_).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))),((enum_).name),name))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Unexpected enum record type in IsEnumVariant: {}"sv)),((enum_).record_type)))));
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
__jakt_var_647 = suffix; goto __jakt_label_552;

}
__jakt_label_552:; __jakt_var_647.release_value(); }));
};/*case end*/
case 14 /* IsSome */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(").has_value()"sv)));
};/*case end*/
case 15 /* IsNone */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(").has_value()"sv)));
};/*case end*/
case 6 /* RawAddress */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("))"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(")"sv)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
__jakt_var_641 = output; goto __jakt_label_546;

}
__jakt_label_546:; __jakt_var_641.release_value(); }));
};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
NonnullRefPtr<typename types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
types::CheckedBinaryOperator const& op = __jakt_match_value.op;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_binary_expression(expression,type_id,lhs,rhs,op)))));
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;types::CheckedNumericConstant const& val = __jakt_match_value.val;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_648; {
ByteString const suffix = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* I64 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("LL"sv)));
};/*case end*/
case 7 /* U64 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("ULL"sv)));
};/*case end*/
case 8 /* USize */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("ULL"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const type_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* USize */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("size_t"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(type_id)))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
__jakt_var_648 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("static_cast<{}>({}{})"sv)),type_name,val,suffix))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_553;

}
__jakt_label_553:; __jakt_var_648.release_value(); }));
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;JaktInternal::DynamicArray<types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_649; {
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((((var)->name_for_codegen())).is_scopable())){
if (((((var)->owner_scope)).has_value())){
(output = TRY((((*this).codegen_namespace_qualifier((((var)->owner_scope).value()),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))));
}
else {
{
JaktInternal::ArrayIterator<types::CheckedNamespace> _magic = ((namespaces).iterator());
for (;;){
JaktInternal::Optional<types::CheckedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedNamespace ns = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((ns).name)) + (TRY(ByteString::from_utf8("::"sv)))))))));
}

}
}

}

}
__jakt_var_649 = TRY((((output) + (TRY((((((var)->name_for_codegen())).as_name_for_use()))))))); goto __jakt_label_554;

}
__jakt_label_554:; __jakt_var_649.release_value(); }));
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
ids::TypeId const& type_id = __jakt_match_value.type_id;
bool const& all_variants_constant = __jakt_match_value.all_variants_constant;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_match(expr,match_cases,type_id,all_variants_constant)))));
};/*case end*/
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedEnumVariantBinding const& arg = __jakt_match_value.arg;
types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_650; {
ByteString const var_name = TRY((((*this).codegen_expression(expr))));
ByteString const enum_type = TRY((((*this).codegen_type_possibly_as_namespace(((expr)->type()),true))));
ByteString const variant_name = ((enum_variant).name());
ByteString arg_name = TRY(ByteString::from_utf8("value"sv));
if (((enum_variant).__jakt_init_index() == 3 /* StructLike */)){
(arg_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); }));
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(((enum_variant).enum_id())));
ByteString const cpp_deref_operator = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((enum_).is_boxed));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("->"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("."sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString section = TRY((__jakt_format((StringView::from_string_literal("as.{}"sv)),variant_name)));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
ByteString const field_name = TRY((((((((((*this).program))->get_variable(((field).variable_id))))->name_for_codegen())).as_name_for_use())));
if (((field_name) == (arg_name))){
(section = TRY(ByteString::from_utf8("common.init_common"sv)));
}
}

}
}

__jakt_var_650 = TRY((__jakt_format((StringView::from_string_literal("({}){}{}.{}"sv)),var_name,cpp_deref_operator,section,arg_name))); goto __jakt_label_555;

}
__jakt_label_555:; __jakt_var_650.release_value(); }));
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
ids::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_651; {
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((repeat).has_value())){
NonnullRefPtr<typename types::CheckedExpression> const repeat_val = ((repeat).value());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).current_error_handler()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("((DynamicArray<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(inner_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">::filled("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(repeat_val)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(((vals)[static_cast<i64>(0LL)]))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("))))"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).current_error_handler()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("((DynamicArray<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(inner_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">::create_with({"sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(val)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}))))"sv)))));
}

__jakt_var_651 = output; goto __jakt_label_556;

}
__jakt_label_556:; __jakt_var_651.release_value(); }));
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
ids::TypeId const& key_type_id = __jakt_match_value.key_type_id;
ids::TypeId const& value_type_id = __jakt_match_value.value_type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_652; {
ByteString output = TRY((__jakt_format((StringView::from_string_literal("({}((Dictionary<{}, {}>::create_with_entries({{"sv)),TRY((((*this).current_error_handler()))),TRY((((*this).codegen_type(key_type_id)))),TRY((((*this).codegen_type(value_type_id)))))));
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> key__value__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> const jakt__key__value__ = key__value__;
NonnullRefPtr<typename types::CheckedExpression> const key = ((jakt__key__value__).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const value = ((jakt__key__value__).template get<1>());

if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(key)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(value)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}"sv)))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}))))"sv)))));
__jakt_var_652 = output; goto __jakt_label_557;

}
__jakt_label_557:; __jakt_var_652.release_value(); }));
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
ids::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_653; {
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("({}((Set<{}>::create_with_values({{"sv)),TRY((((*this).current_error_handler()))),TRY((((*this).codegen_type(inner_type_id))))))))));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> value = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(value)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}))))"sv)))));
__jakt_var_653 = output; goto __jakt_label_558;

}
__jakt_label_558:; __jakt_var_653.release_value(); }));
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_654; {
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("(Tuple{"sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(val)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("})"sv)))));
__jakt_var_654 = output; goto __jakt_label_559;

}
__jakt_label_559:; __jakt_var_654.release_value(); }));
};/*case end*/
case 30 /* DependentFunction */: {
{
TRY((((((*this).compiler))->panic(TRY(ByteString::from_utf8("Dependent functions should have been resolved by now"sv))))));
}
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<types::CheckedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<types::CheckedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
types::CheckedBlock const& block = __jakt_match_value.block;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
JaktInternal::Optional<ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_655; {
JaktInternal::DynamicArray<ByteString> generated_captures = (TRY((DynamicArray<ByteString>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<types::CheckedCapture> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedCapture capture = (_magic_value.value());
{
TRY((((generated_captures).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = capture;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* ByValue */: {
return JaktInternal::ExplicitValue(((capture).common.init_common.name));
};/*case end*/
case 4 /* AllByReference */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("&"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("&{}"sv)),((capture).common.init_common.name)))));
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
})))));
}

}
}

JaktInternal::DynamicArray<ByteString> generated_params = (TRY((DynamicArray<ByteString>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((generated_params).push(TRY((__jakt_format((StringView::from_string_literal("{} {}"sv)),TRY((((*this).codegen_type(((((param).variable))->type_id))))),TRY((((((((param).variable))->name_for_codegen())).as_name_for_definition()))))))))));
}

}
}

ByteString const return_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (can_throw);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("ErrorOr<{}>"sv)),TRY((((*this).codegen_type(return_type_id))))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(return_type_id)))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((last_control_flow).enter_function()));
ScopeGuard __jakt_var_656([&] {
(((*this).control_flow_state) = last_control_flow);
});
ByteString block_output = TRY(ByteString::from_utf8(""sv));
if (((pseudo_function_id).has_value())){
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function((pseudo_function_id.value())));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function);
ScopeGuard __jakt_var_657([&] {
(((*this).current_function) = previous_function);
});
(block_output = TRY((((*this).codegen_lambda_block(can_throw,block,return_type_id)))));
}
else {
(block_output = TRY((((*this).codegen_lambda_block(can_throw,block,return_type_id)))));
}

__jakt_var_655 = TRY((__jakt_format((StringView::from_string_literal("[{}]({}) -> {} {}"sv)),TRY((utility::join(generated_captures,TRY(ByteString::from_utf8(", "sv))))),TRY((utility::join(generated_params,TRY(ByteString::from_utf8(", "sv))))),return_type,block_output))); goto __jakt_label_560;

}
__jakt_label_560:; __jakt_var_655.release_value(); }));
};/*case end*/
case 32 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
ByteString const& error_name = __jakt_match_value.error_name;
types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_658; {
ByteString output = TRY(ByteString::from_utf8(""sv));
ByteString const try_var = TRY((((*this).fresh_var())));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = [&]() -> ErrorOr<void> {"sv)))));
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((((*this).control_flow_state)).passes_through_match) = false);
(((((*this).control_flow_state)).passes_through_try) = true);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(stmt)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return {};"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}();\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("if ("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".is_error()) {"sv)))));
if ((!(((error_name).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,error_name)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".release_error();"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_block(catch_block)))))));
(((*this).control_flow_state) = last_control_flow);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}"sv)))));
__jakt_var_658 = output; goto __jakt_label_561;

}
__jakt_label_561:; __jakt_var_658.release_value(); }));
};/*case end*/
case 31 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<types::CheckedBlock> const& catch_block = __jakt_match_value.catch_block;
JaktInternal::Optional<ByteString> const& catch_name = __jakt_match_value.catch_name;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
ids::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_659; {
ByteString output = TRY(ByteString::from_utf8(""sv));
ByteString const fresh_var = TRY((((*this).fresh_var())));
bool const is_void = ((inner_type_id).equals(types::void_type_id()));
ByteString const try_var = TRY((((*this).fresh_var())));
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((((*this).control_flow_state)).passes_through_match) = false);
(((((*this).control_flow_state)).passes_through_try) = true);
ScopeGuard __jakt_var_660([&] {
{
(((*this).control_flow_state) = last_control_flow);
}

});
if ((!(is_void))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("({ Optional<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(inner_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("> "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,fresh_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";\n"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = [&]() -> ErrorOr<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(inner_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("> { return "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(expr)))))));
if (is_void){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", ErrorOr<void>{}"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; }();\n"sv)))));
if (((catch_block).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("if ("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".is_error()) {"sv)))));
if (((catch_name).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,(catch_name.value()))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".release_error();\n"sv)))));
}
if ((((((catch_block.value())).yielded_type)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,fresh_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = ("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_block((catch_block.value()))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(");\n"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_block((catch_block.value()))))))));
}

if ((!(is_void))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("} else {"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,fresh_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".release_value();\n"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
else if ((!(is_void))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("if (!"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".is_error()) "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,fresh_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,try_var)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".release_value();\n"sv)))));
}
if ((!(is_void))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,fresh_var)));
if (((catch_block).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".release_value()"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; })"sv)))));
}
__jakt_var_659 = output; goto __jakt_label_562;

}
__jakt_label_562:; __jakt_var_659.release_value(); }));
};/*case end*/
case 34 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.span;
{
utility::todo(TRY((__jakt_format((StringView::from_string_literal("codegen_expression of bad AST node in {} at {}..{}"sv)),TRY((((((*this).compiler))->get_file_path(((span).file_id))))),((span).start),((span).end)))));
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

ErrorOr<ByteString> codegen::CodeGenerator::codegen_binary_expression(NonnullRefPtr<typename types::CheckedExpression> const expression,ids::TypeId const type_id,NonnullRefPtr<typename types::CheckedExpression> const lhs,NonnullRefPtr<typename types::CheckedExpression> const rhs,types::CheckedBinaryOperator const op) {
{
if (((((op).trait_implementation)).has_value())){
types::OperatorTraitImplementation const implementation = (((op).trait_implementation).value());
return TRY((((*this).codegen_method_call(lhs,((implementation).call_expression),false))));
}
if (((((op).op)).__jakt_init_index() == 20 /* NoneCoalescing */)){
ids::TypeId const rhs_type_id = ((rhs)->type());
NonnullRefPtr<typename types::Type> const rhs_type = ((((*this).program))->get_type(rhs_type_id));
bool const rhs_can_throw = ((rhs)->can_throw());
ByteString output = TRY(ByteString::from_utf8(""sv));
if (rhs_can_throw){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).current_error_handler()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("(("sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(lhs)))))));
if (((rhs_type)->__jakt_init_index() == 20 /* GenericInstance */)){
ids::StructId const id = (rhs_type)->as.GenericInstance.id;
if (((TRY((((((((((*this).program))->get_struct(id))).name_for_codegen())).as_name_for_definition())))) == (TRY(ByteString::from_utf8("Optional"sv))))){
if (rhs_can_throw){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".try_value_or_lazy_evaluated_optional"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".value_or_lazy_evaluated_optional"sv)))));
}

}
else {
if (rhs_can_throw){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".try_value_or_lazy_evaluated"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".value_or_lazy_evaluated"sv)))));
}

}

}
else {
if (rhs_can_throw){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".try_value_or_lazy_evaluated"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(".value_or_lazy_evaluated"sv)))));
}

}

if (rhs_can_throw){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("([&]() -> ErrorOr<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(rhs_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("> { return "sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("([&] { return "sv)))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(rhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("; })"sv)))));
if (rhs_can_throw){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("))"sv)))));
}
return output;
}
if (((((op).op)).__jakt_init_index() == 32 /* NoneCoalescingAssign */)){
ByteString const var = TRY((((*this).fresh_var())));
return TRY((__jakt_format((StringView::from_string_literal("({{ auto&& {0} = {1}; if (!{0}.has_value()) {0} = {2}; }})"sv)),var,TRY((((*this).codegen_expression(lhs)))),TRY((((*this).codegen_expression(rhs)))))));
}
if (((((op).op)).__jakt_init_index() == 17 /* ArithmeticRightShift */)){
ByteString output = TRY(ByteString::from_utf8("JaktInternal::arithmetic_shift_right("sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(lhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(rhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
return output;
}
if ((((((op).op)).__jakt_init_index() == 21 /* Assign */) && ((lhs)->__jakt_init_index() == 14 /* IndexedDictionary */))){
NonnullRefPtr<typename types::CheckedExpression> const expr = (lhs)->as.IndexedDictionary.expr;
NonnullRefPtr<typename types::CheckedExpression> const index = (lhs)->as.IndexedDictionary.index;
return TRY((__jakt_format((StringView::from_string_literal("{}({}.set({}, {}))"sv)),TRY((((*this).current_error_handler()))),TRY((((*this).codegen_expression(expr)))),TRY((((*this).codegen_expression(index)))),TRY((((*this).codegen_expression(rhs)))))));
}
if (((((*this).program))->is_integer(type_id))){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((op).op);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Subtract */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Multiply */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Divide */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Modulo */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* AddAssign */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* SubtractAssign */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* MultiplyAssign */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31 /* DivideAssign */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* ModuloAssign */: {
{
if (((((*this).compiler))->optimize)){
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_unchecked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
}
else {
return TRY((((TRY((((TRY(ByteString::from_utf8("("sv))) + (TRY((((*this).codegen_checked_binary_op_assignment(lhs,rhs,((op).op),type_id))))))))) + (TRY(ByteString::from_utf8(")"sv))))));
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
ByteString output = TRY(ByteString::from_utf8("("sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(lhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((op).op);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" + "sv)));
};/*case end*/
case 1 /* Subtract */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" - "sv)));
};/*case end*/
case 2 /* Multiply */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" * "sv)));
};/*case end*/
case 4 /* Modulo */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" % "sv)));
};/*case end*/
case 3 /* Divide */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" / "sv)));
};/*case end*/
case 21 /* Assign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" = "sv)));
};/*case end*/
case 27 /* AddAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" += "sv)));
};/*case end*/
case 28 /* SubtractAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" -= "sv)));
};/*case end*/
case 29 /* MultiplyAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" *= "sv)));
};/*case end*/
case 30 /* ModuloAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" %= "sv)));
};/*case end*/
case 31 /* DivideAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" /= "sv)));
};/*case end*/
case 22 /* BitwiseAndAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" &= "sv)));
};/*case end*/
case 23 /* BitwiseOrAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" |= "sv)));
};/*case end*/
case 24 /* BitwiseXorAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" ^= "sv)));
};/*case end*/
case 25 /* BitwiseLeftShiftAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" <<= "sv)));
};/*case end*/
case 26 /* BitwiseRightShiftAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" >>= "sv)));
};/*case end*/
case 9 /* Equal */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" == "sv)));
};/*case end*/
case 10 /* NotEqual */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" != "sv)));
};/*case end*/
case 5 /* LessThan */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" < "sv)));
};/*case end*/
case 6 /* LessThanOrEqual */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" <= "sv)));
};/*case end*/
case 7 /* GreaterThan */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" > "sv)));
};/*case end*/
case 8 /* GreaterThanOrEqual */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" >= "sv)));
};/*case end*/
case 18 /* LogicalAnd */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" && "sv)));
};/*case end*/
case 19 /* LogicalOr */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" || "sv)));
};/*case end*/
case 11 /* BitwiseAnd */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" & "sv)));
};/*case end*/
case 13 /* BitwiseOr */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" | "sv)));
};/*case end*/
case 12 /* BitwiseXor */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" ^ "sv)));
};/*case end*/
case 16 /* ArithmeticLeftShift */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" << "sv)));
};/*case end*/
case 14 /* BitwiseLeftShift */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" << "sv)));
};/*case end*/
case 15 /* BitwiseRightShift */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" >> "sv)));
};/*case end*/
default: {
{
utility::todo(TRY((__jakt_format((StringView::from_string_literal("codegen_binary_expression {}"sv)),op))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(rhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::current_error_handler() const {
{
if ((((*this).inside_defer) || ((((((*this).current_function)).has_value()) && (((((((*this).current_function).value()))->return_type_id)).equals(types::never_type_id()))) && (!(((((*this).control_flow_state)).passes_through_try)))))){
return TRY(ByteString::from_utf8("MUST"sv));
}
return TRY(ByteString::from_utf8("TRY"sv));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_enum_match(types::CheckedEnum const enum_,NonnullRefPtr<typename types::CheckedExpression> const expr,JaktInternal::DynamicArray<types::CheckedMatchCase> const match_cases,ids::TypeId const type_id,bool const all_variants_constant) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
ByteString const subject = TRY((((*this).codegen_expression(expr))));
bool const needs_deref = (((enum_).is_boxed) && [](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(subject,TRY(ByteString::from_utf8("*this"sv))));
ByteString const cpp_match_result_type = TRY((((*this).codegen_type(type_id))));
if (((((enum_).underlying_type_id)).equals(types::void_type_id()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("([&]() -> JaktInternal::ExplicitValueOrControlFlow<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,cpp_match_result_type)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_return_type((((*this).current_function).value()))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto&& __jakt_match_variant = "sv)))));
if (needs_deref){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("*"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((*this).codegen_expression(expr))))) + (TRY(ByteString::from_utf8(";\n"sv)))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("switch(__jakt_match_variant.__jakt_init_index()) {\n"sv)))));
bool has_default = false;
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase match_case = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
ids::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
size_t const& index = __jakt_match_value.index;
ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
types::CheckedMatchBody const& body = __jakt_match_value.body;
{
NonnullRefPtr<typename types::Type> const enum_type = ((((*this).program))->get_type(subject_type_id));
ids::EnumId const enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *enum_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Expected enum type"sv)));
}
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
types::CheckedEnum const match_case_enum = ((((*this).program))->get_enum(enum_id));
types::CheckedEnumVariant const variant = ((((match_case_enum).variants))[index]);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((__jakt_format((StringView::from_string_literal("case {} /* {} */: "sv)),index,((variant).name()))))) + (TRY(ByteString::from_utf8("{\n"sv)))))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
ids::TypeId const& type_id = __jakt_match_value.type_id;
{
if ((!(((args).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("auto&& __jakt_match_value = __jakt_match_variant.as.{};"sv)),name))))));
parser::EnumVariantPatternArgument const arg = ((args)[static_cast<i64>(0LL)]);
NonnullRefPtr<types::CheckedVariable> const var = (TRY((((((*this).program))->find_var_in_scope(scope_id,((arg).binding),false,JaktInternal::OptionalNone())))).value());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((var)->type_id))))))));
if ((!(((var)->is_mutable)))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" const"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("& "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((arg).binding))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = __jakt_match_value.value;\n"sv)))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
{
if ((!(((args).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("auto&& __jakt_match_value = __jakt_match_variant.as.{};"sv)),name))))));
{
JaktInternal::ArrayIterator<parser::EnumVariantPatternArgument> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<parser::EnumVariantPatternArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::EnumVariantPatternArgument arg = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const var = (TRY((((((*this).program))->find_var_in_scope(scope_id,((arg).binding),false,JaktInternal::OptionalNone())))).value());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((var)->type_id))))))));
if ((!(((var)->is_mutable)))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" const"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("& "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((arg).binding))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" = __jakt_match_value."sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((((arg).name)).value_or(((arg).binding))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";\n"sv)))));
}

}
}

}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::todo(TRY((__jakt_format((StringView::from_string_literal("codegen_enum_match match variant else: {}"sv)),variant))));
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
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((match_case).common.init_common.defaults)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> default_ = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(default_)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_match_body(body,type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("};/*case end*/\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;types::CheckedMatchBody const& body = __jakt_match_value.body;
{
(has_default = true);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("default: {\n"sv)))));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((match_case).common.init_common.defaults)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> default_ = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_statement(default_)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_match_body(body,type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("};/*case end*/\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY(ByteString::from_utf8("Matching enum subject with non-enum value"sv)));
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

if ((!(has_default))){
if (((((((enum_).variants)).size())) != (((match_cases).size())))){
utility::panic(TRY(ByteString::from_utf8("Inexhaustive match statement"sv)));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("default: VERIFY_NOT_REACHED();"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}/*switch end*/\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}()\n)"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("([&]() -> JaktInternal::ExplicitValueOrControlFlow<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,cpp_match_result_type)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_return_type((((*this).current_function).value()))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY(ByteString::from_utf8("switch ("sv))) + (TRY((((*this).codegen_expression(expr))))))))) + (TRY(ByteString::from_utf8(") {\n"sv)))))))));
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase match_case = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
types::CheckedMatchBody const& body = __jakt_match_value.body;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY((((TRY((((TRY(ByteString::from_utf8("case "sv))) + (((enum_).name)))))) + (TRY(ByteString::from_utf8("::"sv))))))) + (name))))) + (TRY(ByteString::from_utf8(": {\n"sv)))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_match_body(body,type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;types::CheckedMatchBody const& body = __jakt_match_value.body;
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("default: {\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_match_body(body,type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::todo(TRY((__jakt_format((StringView::from_string_literal("underlying type enum match, match_case: {}"sv)),match_case))));
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

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}/*switch end*/\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}()\n)"sv)))));
}

return TRY((((((*this).control_flow_state)).apply_control_flow_macro(output,(((((*this).current_function).value()))->return_type_id),(((((*this).current_function).value()))->can_throw),cpp_match_result_type))));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_namespace_path(types::CheckedCall const call) {
{
if (((((call).function_id)).has_value())){
NonnullRefPtr<types::CheckedFunction> const func = ((((*this).program))->get_function((((call).function_id).value())));
if (((((func)->owner_scope)).has_value())){
return TRY((((*this).codegen_namespace_qualifier((((func)->owner_scope).value()),false,TRY((((((call).name_for_codegen())).as_name_for_use()))),((func)->owner_scope_generics)))));
}
}
ByteString output = TRY(ByteString::from_utf8(""sv));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::ResolvedNamespace> _magic = ((((call).namespace_)).iterator());
for (;;){
JaktInternal::Optional<types::ResolvedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ResolvedNamespace namespace_ = (_magic_value.value());
{
if ((((index) == (JaktInternal::checked_sub(((((call).namespace_)).size()),static_cast<size_t>(1ULL)))) && ((((namespace_).name)) == (TRY((((((call).name_for_codegen())).as_name_for_use()))))))){
break;
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((namespace_).name_for_codegen())).as_name_for_use()))))));
if (((((namespace_).generic_parameters)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = (((((namespace_).generic_parameters).value())).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId param = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(param)))))));
if (((i) != (JaktInternal::checked_sub((((((namespace_).generic_parameters).value())).size()),static_cast<size_t>(1ULL))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
(++(i));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("::"sv)))));
(++(index));
}

}
}

return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_enum_assignment_body(types::CheckedEnum const enum_,bool const is_constructor,bool const use_move) const {
{
ByteStringBuilder output = ByteStringBuilder::create();
TRY((((output).append((StringView::from_string_literal("{"sv))))));
if (is_constructor){
TRY((((output).append((StringView::from_string_literal("VERIFY(rhs.__jakt_variant_index != 0);\n"sv))))));
}
else {
TRY((((output).append((StringView::from_string_literal("VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);\n"sv))))));
}

Function<ErrorOr<ByteString>(ByteString)> const assign = [use_move](ByteString accessor) -> ErrorOr<ByteString> {
{
ByteString const rhs = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (use_move);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("move(rhs.{})"sv)),accessor))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("rhs.{}"sv)),accessor))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return TRY((__jakt_format((StringView::from_string_literal("this->{} = {};\n"sv)),accessor,rhs)));
}
}
;
Function<ErrorOr<ByteString>(ByteString)> const placement_new = [use_move](ByteString accessor) -> ErrorOr<ByteString> {
{
ByteString const rhs = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (use_move);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("move(rhs.{})"sv)),accessor))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("rhs.{}"sv)),accessor))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return TRY((__jakt_format((StringView::from_string_literal("new (&this->{0}) (decltype(this->{0}))({1});\n"sv)),accessor,rhs)));
}
}
;
if (is_constructor){
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField common = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((((*this).program))->get_variable(((common).variable_id)));
ByteString const name = TRY((((((variable)->name_for_codegen())).as_name_for_use())));
TRY((((output).append(TRY((placement_new(TRY((__jakt_format((StringView::from_string_literal("common.init_common.{}"sv)),name))))))))));
}

}
}

}
else {
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField common = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((((*this).program))->get_variable(((common).variable_id)));
ByteString const name = TRY((((((variable)->name_for_codegen())).as_name_for_use())));
TRY((((output).append(TRY((assign(TRY((__jakt_format((StringView::from_string_literal("common.init_common.{}"sv)),name))))))))));
}

}
}

}

if (is_constructor){
TRY((((*this).codegen_for_enum_variants(((enum_)),((placement_new)),TRY(ByteString::from_utf8("rhs.__jakt_init_index()"sv)),((output))))));
}
else {
TRY((((output).append((StringView::from_string_literal("if (this->__jakt_variant_index != rhs.__jakt_variant_index) {\n"sv))))));
TRY((((output).append((StringView::from_string_literal("this->__jakt_destroy_variant();\n"sv))))));
TRY((((*this).codegen_for_enum_variants(((enum_)),((placement_new)),TRY(ByteString::from_utf8("rhs.__jakt_init_index()"sv)),((output))))));
TRY((((output).append((StringView::from_string_literal("} else {\n"sv))))));
TRY((((*this).codegen_for_enum_variants(((enum_)),((assign)),TRY(ByteString::from_utf8("rhs.__jakt_init_index()"sv)),((output))))));
TRY((((output).append((StringView::from_string_literal("}\n"sv))))));
}

TRY((((output).append((StringView::from_string_literal("this->__jakt_variant_index = rhs.__jakt_variant_index;\n"sv))))));
TRY((((output).append((StringView::from_string_literal("}\n"sv))))));
return TRY((((output).to_string())));
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_enum(types::CheckedEnum const enum_) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if ([](ids::TypeId const& self, ids::TypeId rhs) -> bool {
{
return (!(((self).equals(rhs))));
}
}
(((enum_).underlying_type_id),types::void_type_id())){
if (((((*this).program))->is_integer(((enum_).underlying_type_id)))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY((((TRY((((TRY(ByteString::from_utf8("enum class "sv))) + (((enum_).name)))))) + (TRY(ByteString::from_utf8(": "sv))))))) + (TRY((((*this).codegen_type(((enum_).underlying_type_id)))))))))) + (TRY(ByteString::from_utf8(" {\n"sv)))))))));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& name = __jakt_match_value.name;
NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((((TRY((((TRY((((name) + (TRY(ByteString::from_utf8(" = "sv))))))) + (TRY((((*this).codegen_expression(expr))))))))) + (TRY(ByteString::from_utf8(",\n"sv)))))));
};/*case end*/
default: {
{
utility::todo(TRY((__jakt_format((StringView::from_string_literal("codegen_enum can't generate variant: {}"sv)),variant))));
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
}))));
}

}
}

return TRY((((output) + (TRY(ByteString::from_utf8("};\n"sv))))));
}
else {
utility::todo(TRY(ByteString::from_utf8("Enums with a non-integer underlying type"sv)));
}

}
bool const is_generic = (!(((((enum_).generic_parameters)).is_empty())));
JaktInternal::DynamicArray<ByteString> generic_parameter_names = (TRY((DynamicArray<ByteString>::create_with({}))));
ByteString template_args = TRY((((*this).codegen_template_parameter_names(((enum_).generic_parameters),((generic_parameter_names))))));
ByteString const generic_parameter_list = TRY((utility::join(generic_parameter_names,TRY(ByteString::from_utf8(", "sv)))));
if (is_generic){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY(ByteString::from_utf8("template<"sv))) + (template_args))))) + (TRY(ByteString::from_utf8(">\n"sv)))))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("struct {}"sv)),((enum_).name)))))));
if (((enum_).is_boxed)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal(": public RefCounted<{}"sv)),((enum_).name)))))));
if (is_generic){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("<{}>"sv)),TRY((utility::join(generic_parameter_names,TRY(ByteString::from_utf8(", "sv)))))))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" {\n"sv)))));
size_t const max_index_value = ((((enum_).variants)).size());
ByteString const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (max_index_value);
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("u8"sv)));
}
else if (__jakt_enum_value >= static_cast<size_t>(256ULL)&& __jakt_enum_value < static_cast<size_t>(65536ULL)) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("u16"sv)));
}
else if (__jakt_enum_value >= static_cast<size_t>(65536ULL)&& __jakt_enum_value < static_cast<size_t>(4294967296ULL)) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("u32"sv)));
}
else {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("size_t"sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>> const common_fields_variant_field_list_ = TRY((((*this).codegen_enum_field_lists(enum_))));
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields = ((common_fields_variant_field_list_).template get<0>());
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const variant_field_list = ((common_fields_variant_field_list_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{} __jakt_variant_index = 0;\n"sv)),index_type,max_index_value))))));
if ((!(((common_fields).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("union CommonData {\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("u8 __jakt_uninit_common;\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("struct {\n"sv)))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = ((common_fields).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ByteString> field_name__type__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ByteString> const jakt__field_name__type__ = field_name__type__;
ByteString const field_name = ((jakt__field_name__type__).template get<0>());
ByteString const type = ((jakt__field_name__type__).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{} {};\n"sv)),type,field_name))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("} init_common;\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("constexpr CommonData() {}\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("~CommonData() {}\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("} common;\n"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("union VariantData {\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("u8 __jakt_uninit_value;\n"sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).variants)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t variant_index = (_magic_value.value());
{
types::CheckedEnumVariant const variant = ((((enum_).variants))[variant_index]);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const fields = ((((variant_field_list)[variant_index])).template get<1>());
if ((!(((fields).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("struct {\n"sv)))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ByteString> field_name__field_type__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ByteString> const jakt__field_name__field_type__ = field_name__field_type__;
ByteString const field_name = ((jakt__field_name__field_type__).template get<0>());
ByteString const field_type = ((jakt__field_name__field_type__).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{} {};\n"sv)),field_type,field_name))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("}} {};\n"sv)),((variant).name())))))));
}
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("constexpr VariantData() {}\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("~VariantData() {}\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("} as;\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("constexpr {} __jakt_init_index() const noexcept {{ return __jakt_variant_index - 1; }}"sv)),index_type))))));
if (((((enum_).generic_parameters)).is_empty())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("ErrorOr<ByteString> debug_description() const;\n"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_debug_description_getter(enum_,true)))))));
}

if (is_generic){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_constructors(enum_,true,generic_parameter_list,variant_field_list,common_fields)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("~{}()"sv)),((enum_).name)))))));
TRY((((*this).codegen_enum_destructor_body(enum_,((output))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("private: void __jakt_destroy_variant() {\n"sv)))));
TRY((((*this).codegen_enum_destroy_variant(enum_,((output))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("public:\n"sv)))));
}
else {
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> _magic = ((variant_field_list).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> variant_name__variant_fields__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> const jakt__variant_name__variant_fields__ = variant_name__variant_fields__;
ByteString const variant_name = ((jakt__variant_name__variant_fields__).template get<0>());
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const variant_fields = ((jakt__variant_name__variant_fields__).template get<1>());

TRY((codegen::CodeGenerator::codegen_enum_constructor_decl(((enum_).name),variant_name,variant_fields,common_fields,true,TRY((codegen::CodeGenerator::enum_constructor_result_type(enum_,JaktInternal::OptionalNone()))),((output)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";\n"sv)))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("~{}();\n"sv)),((enum_).name)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}& operator=({0} const &);\n"sv)),((enum_).name)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}& operator=({0} &&);\n"sv)),((enum_).name)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}({0} const&);\n"sv)),((enum_).name)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}({0} &&);\n"sv)),((enum_).name)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("private: void __jakt_destroy_variant();\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("public:\n"sv)))));
}

NonnullRefPtr<types::Scope> const enum_scope = TRY((((((*this).program))->get_scope(((enum_).scope_id)))));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((enum_scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function_id = ((*this).current_function);
(((*this).current_function) = static_cast<JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>>>(function));
ScopeGuard __jakt_var_661([&] {
(((*this).current_function) = previous_function_id);
});
if ((!(((((function)->type)).__jakt_init_index() == 3 /* ImplicitEnumConstructor */)))){
if ((!(((((enum_).generic_parameters)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function(function,true)))))));
}
else if ((((((((function)->generics))->params)).is_empty()) || (!(((((function)->specialization_index)).has_value()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_predecl(function,true,false)))))));
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

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("private:\n{}() {{}};\n"sv)),((enum_).name)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("};\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((*this).deferred_output),TRY((((*this).codegen_ak_formatter(((enum_).name),generic_parameter_names,template_args)))))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_struct_type(ids::StructId const id,bool const as_namespace) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
NonnullRefPtr<types::Module> const type_module = ((((*this).program))->get_module(((id).module)));
types::CheckedStruct const checked_struct = ((((*this).program))->get_struct(id));
if (((!(as_namespace)) && ((((checked_struct).record_type)).__jakt_init_index() == 1 /* Class */))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("NonnullRefPtr<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_qualifier(((checked_struct).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((checked_struct).name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace_qualifier(((checked_struct).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((checked_struct).name_for_codegen())).as_name_for_use()))))));
}

return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_enum_predecl(types::CheckedEnum const enum_) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
if ([](ids::TypeId const& self, ids::TypeId rhs) -> bool {
{
return (!(((self).equals(rhs))));
}
}
(((enum_).underlying_type_id),types::void_type_id())){
if (((((*this).program))->is_integer(((enum_).underlying_type_id)))){
return TRY((__jakt_format((StringView::from_string_literal("enum class {}: {};"sv)),((enum_).name),TRY((((*this).codegen_type(((enum_).underlying_type_id))))))));
}
else {
utility::todo(TRY(ByteString::from_utf8("Enums with a non-integer underlying type"sv)));
}

}
bool const is_generic = (!(((((enum_).generic_parameters)).is_empty())));
ByteString template_args = TRY((((*this).codegen_template_parameter_names(((enum_).generic_parameters)))));
if (is_generic){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("template<{}>\n"sv)),template_args))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("struct {};\n"sv)),((enum_).name)))))));
return output;
}
}

ErrorOr<void> codegen::CodeGenerator::postorder_traversal(ids::TypeId const type_id,JaktInternal::Set<ids::TypeId> visited,JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph,JaktInternal::DynamicArray<ids::TypeId> output) const {
{
if (((visited).contains(type_id))){
return {};
}
TRY((((visited).add(type_id))));
if (((dependency_graph).contains(type_id))){
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = (((((dependency_graph).get(type_id)).value())).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId dependency = (_magic_value.value());
{
TRY((((*this).postorder_traversal(dependency,visited,dependency_graph,output))));
}

}
}

}
TRY((((output).push(type_id))));
}
return {};
}

ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> codegen::CodeGenerator::extract_dependencies_from_enum(ids::EnumId const enum_id,JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph,bool const top_level) const {
{
JaktInternal::DynamicArray<ids::TypeId> dependencies = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
if (((((enum_).definition_linkage)).__jakt_init_index() == 1 /* External */)){
return dependencies;
}
if ((((enum_).is_boxed) && (!(top_level)))){
return dependencies;
}
TRY((((dependencies).push(((enum_).type_id)))));
if ([](ids::TypeId const& self, ids::TypeId rhs) -> bool {
{
return (!(((self).equals(rhs))));
}
}
(((enum_).underlying_type_id),types::unknown_type_id())){
JaktInternal::DynamicArray<ids::TypeId> const inner_dependencies = TRY((((*this).extract_dependencies_from(((enum_).underlying_type_id),dependency_graph,false))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

}
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::DynamicArray<ids::TypeId>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<ids::TypeId> const inner_dependencies = TRY((((*this).extract_dependencies_from(type_id,dependency_graph,false))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
{
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
ids::TypeId const type_id = ((((((*this).program))->get_variable(field)))->type_id);
JaktInternal::DynamicArray<ids::TypeId> const inner_dependencies = TRY((((*this).extract_dependencies_from(type_id,dependency_graph,false))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId dependency = (_magic_value.value());
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

return dependencies;
}
}

ErrorOr<void> codegen::CodeGenerator::codegen_enum_constructor_decl(ByteString const enum_name,ByteString const variant_name,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const variant_fields,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields,bool const is_inline,ByteString const ctor_result_type,ByteString& output) {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8("[[nodiscard]] "sv)))));
if (is_inline){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal("static {} {}("sv)),ctor_result_type,variant_name))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal("{} {}::{}("sv)),ctor_result_type,enum_name,variant_name))))));
}

bool const has_common_fields = (!(((common_fields).is_empty())));
if (has_common_fields){
JaktInternal::Tuple<ByteString,ByteString> const first_name_first_type_ = ((common_fields)[static_cast<i64>(0LL)]);
ByteString const first_name = ((first_name_first_type_).template get<0>());
ByteString const first_type = ((first_name_first_type_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal("{} {}"sv)),first_type,first_name))))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((common_fields).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ByteString> const name_type_ = ((common_fields)[i]);
ByteString const name = ((name_type_).template get<0>());
ByteString const type = ((name_type_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal(", {} {}"sv)),type,name))))));
}

}
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = ((variant_fields).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ByteString> name__type__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ByteString> const jakt__name__type__ = name__type__;
ByteString const name = ((jakt__name__type__).template get<0>());
ByteString const type = ((jakt__name__type__).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal(", {} {}"sv)),type,name))))));
}

}
}

}
else if ((!(((variant_fields).is_empty())))){
JaktInternal::Tuple<ByteString,ByteString> const first_name_first_type_ = ((variant_fields)[static_cast<i64>(0LL)]);
ByteString const first_name = ((first_name_first_type_).template get<0>());
ByteString const first_type = ((first_name_first_type_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal("{} {}"sv)),first_type,first_name))))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((variant_fields).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ByteString> const name_type_ = ((variant_fields)[i]);
ByteString const name = ((name_type_).template get<0>());
ByteString const type = ((name_type_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal(", {} {}"sv)),type,name))))));
}

}
}

}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8(")"sv)))));
}
return {};
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_generic_enum_instance(ids::EnumId const id,JaktInternal::DynamicArray<ids::TypeId> const args,bool const as_namespace) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
bool close_tag = false;
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(id));
if (((!(as_namespace)) && ((enum_).is_boxed))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("NonnullRefPtr<"sv)))));
ByteString const qualifier = TRY((((*this).codegen_namespace_qualifier(((enum_).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
if ((!(((qualifier).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("typename "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,qualifier)));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((enum_).name))));
(close_tag = true);
}
else {
ByteString const qualifier = TRY((((*this).codegen_namespace_qualifier(((enum_).scope_id),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
if ((!(((qualifier).is_empty())))){
if ((!(as_namespace))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("typename "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,qualifier)));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,((enum_).name))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId type_id = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type_id)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
if (close_tag){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_enum_constructors(types::CheckedEnum const enum_,bool const is_inside_struct,JaktInternal::Optional<ByteString> const generic_parameter_list,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const variant_field_list,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields) const {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
bool const is_generic = (!(((((enum_).generic_parameters)).is_empty())));
ByteString const ctor_result_type = TRY((codegen::CodeGenerator::enum_constructor_result_type(enum_,generic_parameter_list)));
ByteString const ctor_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (is_generic);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}<{}>"sv)),((enum_).name),generic_parameter_list))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(((enum_).name));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Tuple<ByteString,ByteString> const declare_uninit_deref_uninit_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<ByteString,ByteString>,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((enum_).is_boxed));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((Tuple{TRY((__jakt_format((StringView::from_string_literal("NonnullRefPtr<{0}> __jakt_uninit_enum = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) {0}));\n"sv)),ctor_type))), TRY(ByteString::from_utf8("__jakt_uninit_enum->"sv))}));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue((Tuple{TRY((__jakt_format((StringView::from_string_literal("{} __jakt_uninit_enum;\n"sv)),((enum_).name)))), TRY(ByteString::from_utf8("__jakt_uninit_enum."sv))}));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const declare_uninit = ((declare_uninit_deref_uninit_).template get<0>());
ByteString const deref_uninit = ((declare_uninit_deref_uninit_).template get<1>());

if ((is_inside_struct || (!(is_generic)))){
Function<ErrorOr<ByteString>(ByteString, ByteString)> const placement_new = [](ByteString target, ByteString name) -> ErrorOr<ByteString> {
{
return TRY((__jakt_format((StringView::from_string_literal("new (&{0}) (decltype({1}))(move({1}));\n"sv)),target,name)));
}
}
;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((variant_field_list).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t variant_index = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> const variant_name_variant_fields_ = ((variant_field_list)[variant_index]);
ByteString const variant_name = ((variant_name_variant_fields_).template get<0>());
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const variant_fields = ((variant_name_variant_fields_).template get<1>());

TRY((codegen::CodeGenerator::codegen_enum_constructor_decl(((enum_).name),variant_name,variant_fields,common_fields,is_inside_struct,ctor_result_type,((output)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,declare_uninit)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{}__jakt_variant_index = {};\n"sv)),deref_uninit,JaktInternal::checked_add(variant_index,static_cast<size_t>(1ULL))))))));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = ((common_fields).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ByteString> field = (_magic_value.value());
{
ByteString const name = ((field).template get<0>());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((placement_new(TRY((__jakt_format((StringView::from_string_literal("{}common.init_common.{}"sv)),deref_uninit,name))),name))))));
}

}
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = ((variant_fields).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ByteString> field = (_magic_value.value());
{
ByteString const name = ((field).template get<0>());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((placement_new(TRY((__jakt_format((StringView::from_string_literal("{}as.{}.{}"sv)),deref_uninit,variant_name,name))),name))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return __jakt_uninit_enum;\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}

}
}

if (is_inside_struct){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}& operator=({0} const &rhs)"sv)),((enum_).name)))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}& {0}::operator=({0} const &rhs)"sv)),((enum_).name)))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_assignment_body(enum_,false,false)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return *this;\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
if (is_inside_struct){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}({0} const &rhs)"sv)),((enum_).name)))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}::{0}({0} const &rhs)"sv)),((enum_).name)))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_assignment_body(enum_,true,false)))))));
if (is_inside_struct){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}& operator=({0} &&rhs)"sv)),((enum_).name)))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}& {0}::operator=({0} &&rhs)"sv)),((enum_).name)))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_assignment_body(enum_,false,true)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return *this;\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
if (is_inside_struct){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}({0} &&rhs)"sv)),((enum_).name)))))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}::{0}({0} &&rhs)"sv)),((enum_).name)))))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_assignment_body(enum_,true,true)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
return output;
}
else {
utility::panic(TRY(ByteString::from_utf8("Out of line constructor cannot be generated for generic enum"sv)));
}

}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_function_return_type(NonnullRefPtr<types::CheckedFunction> const function) {
{
if ((TRY((((function)->is_static()))) && ((TRY((((((function)->name_for_codegen())).as_name_for_use())))) == (TRY(ByteString::from_utf8("main"sv)))))){
return TRY(ByteString::from_utf8("ErrorOr<int>"sv));
}
ByteString const type_name = TRY((((*this).codegen_type(((function)->return_type_id)))));
if (((function)->can_throw)){
return TRY((__jakt_format((StringView::from_string_literal("ErrorOr<{}>"sv)),type_name)));
}
return type_name;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_function_in_namespace(NonnullRefPtr<types::CheckedFunction> const function,JaktInternal::Optional<ids::TypeId> const containing_struct,bool const as_method,bool const skip_template,JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const explicit_generic_instantiation) {
{
if ((!(((((((function)->generics))->params)).is_empty())))){
if (((((function)->linkage)).__jakt_init_index() == 1 /* External */)){
return TRY(ByteString::from_utf8(""sv));
}
}
if (((((function)->force_inline)).__jakt_init_index() == 2 /* ForceInline */)){
return TRY(ByteString::from_utf8(""sv));
}
ByteString output = TRY(ByteString::from_utf8(""sv));
if ((!(skip_template))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_generic_parameters(function)))))));
}
bool const is_main = (((TRY((((((function)->name_for_codegen())).as_name_for_use())))) == (TRY(ByteString::from_utf8("main"sv)))) && (!(((containing_struct).has_value()))));
if (((((function)->force_inline)).__jakt_init_index() == 1 /* MakeDefinitionAvailable */)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("__attribute__((always_inline)) inline "sv)))));
}
if (((((function)->return_type_id)).equals(types::never_type_id()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("[[noreturn]] "sv)))));
}
if (is_main){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("ErrorOr<int>"sv)))));
}
else {
if ((as_method && TRY((((function)->is_static()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("static "sv)))));
}
if ((!(((((function)->type)).__jakt_init_index() == 1 /* Destructor */)))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((function)->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("ErrorOr<{}>"sv)),TRY((((*this).codegen_type(((function)->return_type_id)))))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(((function)->return_type_id))))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
if (is_main){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("main"sv)))));
}
else {
ByteString const qualifier = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((containing_struct).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type_possibly_as_namespace((containing_struct.value()),true)))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((!(((qualifier).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,qualifier)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("::"sv)))));
}
if (((((function)->type)).__jakt_init_index() == 1 /* Destructor */)){
if (((((((*this).program))->get_type((containing_struct.value()))))->__jakt_init_index() == 24 /* Struct */)){
ids::StructId const struct_id = (((((*this).program))->get_type((containing_struct.value()))))->as.Struct.value;
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY(ByteString::from_utf8("~"sv))) + (TRY((((((((((*this).program))->get_struct(struct_id))).name_for_codegen())).as_name_for_definition()))))))))));
}
else {
utility::panic(TRY(ByteString::from_utf8("Destructor doesn't have a containing struct"sv)));
}

}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((function)->name_for_codegen())).as_name_for_definition()))))));
}

}

if (((explicit_generic_instantiation).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = (((explicit_generic_instantiation.value())).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId type = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
if ((is_main && ((((function)->params)).is_empty()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("DynamicArray<ByteString>"sv)))));
}
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((param).variable);
if (((((variable)->name)) == (TRY(ByteString::from_utf8("this"sv))))){
continue;
}
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
else {
(first = false);
}

NonnullRefPtr<typename types::Type> const variable_type = ((((*this).program))->get_type(((variable)->type_id)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((variable)->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
if (((!(((variable)->is_mutable))) && (!((((variable_type)->__jakt_init_index() == 28 /* Reference */) || ((variable_type)->__jakt_init_index() == 29 /* MutableReference */)))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("const "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((variable)->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
if (((!(TRY((((function)->is_static()))))) && (!(TRY((((function)->is_mutating()))))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" const"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" {\n"sv)))));
if (is_main){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n\n            #ifdef _WIN32\n            SetConsoleOutputCP(CP_UTF8);\n            // Enable buffering to prevent VS from chopping up UTF-8 byte sequences\n            setvbuf(stdout, nullptr, _IOFBF, 1000);\n            #endif\n"sv)))));
}
codegen::ControlFlowState const last_control_flow = ((*this).control_flow_state);
(((*this).control_flow_state) = ((last_control_flow).enter_function()));
ByteString const block = TRY((((*this).codegen_block(((function)->block)))));
(((*this).control_flow_state) = last_control_flow);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,block)));
if (is_main){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return 0;\n"sv)))));
}
else {
if ((((function)->can_throw) && ((((function)->return_type_id)).equals(types::builtin(types::BuiltinType::Void()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("return {};\n"sv)))));
}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
return output;
}
}

ErrorOr<void> codegen::CodeGenerator::codegen_enum_destroy_variant(types::CheckedEnum const enum_,ByteString& output) const {
{
size_t const common_field_count = ((((enum_).fields)).size());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8("switch (this->__jakt_init_index()) {\n"sv)))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((enum_).variants)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t variant_index = (_magic_value.value());
{
types::CheckedEnumVariant const variant = ((((enum_).variants))[variant_index]);
ByteString const variant_name = ((variant).name());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal("case {} /* {} */:"sv)),variant_index,variant_name))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* WithValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<ByteString> const ds_name = TRY((((*this).destructor_name(type_id))));
if (((ds_name).has_value())){
ByteString const name = (ds_name.value());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal("this->as.{}.value.~{}();\n"sv)),variant_name,name))))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
{
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((((fields)[(JaktInternal::Range<size_t>{static_cast<size_t>(common_field_count),static_cast<size_t>(9223372036854775807LL)})])).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((((*this).program))->get_variable(field));
JaktInternal::Optional<ByteString> const ds = TRY((((*this).destructor_name(((variable)->type_id)))));
if (((ds).has_value())){
ByteString const name = (ds.value());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal("this->as.{}.{}.~{}();\n"sv)),variant_name,TRY((((((variable)->name_for_codegen())).as_name_for_use()))),name))))));
}
}

}
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
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8("break;\n"sv)))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8("}\n"sv)))));
}
return {};
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_type(ids::TypeId const type_id) {
{
return TRY((((*this).codegen_type_possibly_as_namespace(type_id,false))));
}
}

ErrorOr<JaktInternal::Optional<ByteString>> codegen::CodeGenerator::codegen_namespace_specialization(ids::FunctionId const function_id,JaktInternal::Optional<ids::TypeId> const containing_struct,NonnullRefPtr<types::Scope> const scope,NonnullRefPtr<types::Module> const current_module,bool const define_pass) {
{
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
if ((!(((((((function)->function_scope_id)).module_id)).equals(((current_module)->id)))))){
return JaktInternal::OptionalNone();
}
if (((function)->is_comptime)){
return JaktInternal::OptionalNone();
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function);
ScopeGuard __jakt_var_662([&] {
(((*this).current_function) = previous_function);
});
if ((((((((function)->linkage)).__jakt_init_index() == 1 /* External */) || ((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */)) || ((((function)->type)).__jakt_init_index() == 3 /* ImplicitEnumConstructor */)) || ((((function)->type)).__jakt_init_index() == 1 /* Destructor */))){
return JaktInternal::OptionalNone();
}
if ((((((((function)->generics))->params)).is_empty()) || (!(((((function)->specialization_index)).has_value()))))){
return JaktInternal::OptionalNone();
}
if ((((containing_struct).has_value()) && (!(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<JaktInternal::Optional<ByteString>>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type((containing_struct.value())));
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((((*this).program))->get_struct(struct_id))).generic_parameters)).is_empty()));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((((*this).program))->get_enum(struct_id))).generic_parameters)).is_empty()));
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
}))))){
return JaktInternal::OptionalNone();
}
ByteString output = TRY(ByteString::from_utf8(""sv));
bool const is_full_respecialization = ((*this).is_full_respecialization(((((((function)->generics))->specializations))[(((function)->specialization_index).value())])));
if ((define_pass && is_full_respecialization)){
(output = TRY(ByteString::from_utf8("template<"sv)));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((((((((function)->generics))->specializations))[(((function)->specialization_index).value())])).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
if (((((((*this).program))->get_type(arg)))->__jakt_init_index() == 18 /* TypeVariable */)){
ByteString const name = (((((*this).program))->get_type(arg)))->as.TypeVariable.name;
if (first){
(first = false);
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("typename {}"sv)),name))))));
}
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_in_namespace(function,containing_struct,false,true,((((((function)->generics))->specializations))[(((function)->specialization_index).value())]))))))));
}
else if (is_full_respecialization){
JaktInternal::DynamicArray<ByteString> args = (TRY((DynamicArray<ByteString>::create_with({}))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((((((((function)->generics))->specializations))[(((function)->specialization_index).value())])).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
TRY((((args).push(TRY((((*this).codegen_type(arg))))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("\n/* specialisation {} of function {}: {} */"sv)),(((function)->specialization_index).value()),((function)->name),args))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\ntemplate<> "sv)))));
if (((((function)->return_type_id)).equals(types::never_type_id()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("[[noreturn]] "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<JaktInternal::Optional<ByteString>>>{
auto __jakt_enum_value = (((function)->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("ErrorOr<{}>"sv)),TRY((((*this).codegen_type(((function)->return_type_id)))))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type(((function)->return_type_id))))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
ByteString const qualifier = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<JaktInternal::Optional<ByteString>>>{
auto __jakt_enum_value = (((containing_struct).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type_possibly_as_namespace((containing_struct.value()),true)))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ((!(((qualifier).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,qualifier)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("::"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((function)->name_for_codegen())).as_name_for_definition()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("<"sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((((((((function)->generics))->specializations))[(((function)->specialization_index).value())])).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId type_id = (_magic_value.value());
{
if (first){
(first = false);
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type_id)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">("sv)))));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((param).variable);
if (((((variable)->name)) == (TRY(ByteString::from_utf8("this"sv))))){
continue;
}
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(","sv)))));
}
else {
(first = false);
}

NonnullRefPtr<typename types::Type> const variable_type = ((((*this).program))->get_type(((variable)->type_id)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((variable)->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
if (((!(((variable)->is_mutable))) && (!((((variable_type)->__jakt_init_index() == 28 /* Reference */) || ((variable_type)->__jakt_init_index() == 29 /* MutableReference */)))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("const "sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((variable)->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
if (((!(TRY((((function)->is_static()))))) && (!(TRY((((function)->is_mutating()))))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" const"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";\n"sv)))));
}
else {
(output = TRY((__jakt_format((StringView::from_string_literal("\n/* specialisation {} of function {} omitted, not fully specialized: {} */\n"sv)),(((function)->specialization_index).value()),((function)->name),((((((function)->generics))->specializations))[(((function)->specialization_index).value())])))));
}

return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_destructor_predecl(types::CheckedStruct const& struct_) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("public:\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY(ByteString::from_utf8("    ~"sv))) + (TRY((((((((struct_))).name_for_codegen())).as_name_for_definition())))))))) + (TRY(ByteString::from_utf8("();\n"sv)))))))));
return output;
}
}

ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> codegen::CodeGenerator::extract_dependencies_from(ids::TypeId const type_id,JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph,bool const top_level) const {
{
JaktInternal::DynamicArray<ids::TypeId> dependencies = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
NonnullRefPtr<typename types::Type> const type_ = ((((*this).program))->get_type(type_id));
if (((!(((type_)->is_boxed(((*this).program))))) && ((dependency_graph).contains(type_id)))){
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = (((((dependency_graph).get(type_id)).value())).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

return dependencies;
}
JaktInternal::DynamicArray<ids::TypeId> const inner_dependencies = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ids::TypeId>, ErrorOr<JaktInternal::DynamicArray<ids::TypeId>>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from_enum(enum_id,dependency_graph,top_level)))));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from_enum(id,dependency_graph,top_level)))));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from_struct(id,dependency_graph,top_level,(TRY((DynamicArray<ids::TypeId>::create_with({})))))))));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((*this).extract_dependencies_from_struct(id,dependency_graph,top_level,args)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((TRY((DynamicArray<ids::TypeId>::create_with({})))));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((inner_dependencies).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId dependency = (_magic_value.value());
{
TRY((((dependencies).push(dependency))));
}

}
}

return dependencies;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_namespace(NonnullRefPtr<types::Scope> const scope,NonnullRefPtr<types::Module> const current_module,bool const as_forward) {
{
if ((((((scope)->alias_path)).has_value()) || ((((scope)->import_path_if_extern)).has_value()))){
return TRY(ByteString::from_utf8(""sv));
}
JaktInternal::Set<ids::TypeId> seen_types = (TRY((Set<ids::TypeId>::create_with_values({}))));
if (as_forward){
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((((scope)->namespace_name)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY(ByteString::from_utf8("namespace "sv))) + ((((scope)->namespace_name).value())))))) + (TRY(ByteString::from_utf8(" {\n"sv)))))))));
}
JaktInternal::Dictionary<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> const dependency_graph = TRY((((*this).produce_codegen_dependency_graph(scope))));
{
JaktInternal::DictionaryIterator<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> _magic = ((dependency_graph).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ids::TypeId,JaktInternal::DynamicArray<ids::TypeId>> entry = (_magic_value.value());
{
JaktInternal::DynamicArray<ids::TypeId> const traversal = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((*this).postorder_traversal(((entry).template get<0>()),seen_types,dependency_graph,traversal))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((traversal).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId type_id = (_magic_value.value());
{
NonnullRefPtr<typename types::Type> const type_ = ((((*this).program))->get_type(type_id));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
{
if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
return JaktInternal::LoopContinue{};
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
ByteString const enum_output = TRY((((*this).codegen_enum(enum_))));
if ((!(((enum_output).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,enum_output)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
{
if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
return JaktInternal::LoopContinue{};
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
ByteString const struct_output = TRY((((*this).codegen_struct(struct_))));
if ((!(((struct_output).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,struct_output)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* Trait */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Unexpected type in dependency graph: {}"sv)),type_))));
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
TRY((((seen_types).add(type_id))));
}

}
}

}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ids::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::StructId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::StructId> ___struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::StructId> const jakt_____struct_id__ = ___struct_id__;
ByteString const _ = ((jakt_____struct_id__).template get<0>());
ids::StructId const struct_id = ((jakt_____struct_id__).template get<1>());

if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if (((seen_types).contains(((struct_).type_id)))){
continue;
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_struct(struct_)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ids::EnumId> _magic = ((((scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::EnumId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::EnumId> ___enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::EnumId> const jakt_____enum_id__ = ___enum_id__;
ByteString const _ = ((jakt_____enum_id__).template get<0>());
ids::EnumId const enum_id = ((jakt_____enum_id__).template get<1>());

if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
if (((seen_types).contains(((enum_).type_id)))){
continue;
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum(enum_)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
if ((!(((((((function)->function_scope_id)).module_id)).equals(((current_module)->id)))))){
continue;
}
if (((function)->is_comptime)){
continue;
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function);
ScopeGuard __jakt_var_663([&] {
(((*this).current_function) = previous_function);
});
if ((((((((function)->linkage)).__jakt_init_index() == 1 /* External */) || ((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */)) || ((((function)->type)).__jakt_init_index() == 3 /* ImplicitEnumConstructor */)) || ((((function)->type)).__jakt_init_index() == 1 /* Destructor */))){
continue;
}
if (((((((function)->generics))->params)).is_empty())){
continue;
}
if ((!(((((function)->specialization_index)).has_value())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_predecl(function,false,true)))))));
}
}

}
}

}

}
}

{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child_scope_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((((*this).program))->get_scope(child_scope_id))));
if (((((child_scope)->namespace_name)).has_value())){
ByteString const name = (((child_scope)->namespace_name).value());
TRY((((((*this).namespace_stack)).push(name))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace(child_scope,current_module,as_forward)))))));
JaktInternal::Optional<ByteString> const dummy = ((((*this).namespace_stack)).pop());
}
}

}
}

if (((((scope)->namespace_name)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return output;
}
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((((scope)->namespace_name)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((TRY((((TRY(ByteString::from_utf8("namespace "sv))) + ((((scope)->namespace_name).value())))))) + (TRY(ByteString::from_utf8(" {\n"sv)))))))));
}
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
if ((!(((((((function)->function_scope_id)).module_id)).equals(((current_module)->id)))))){
continue;
}
if (((function)->is_comptime)){
continue;
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function);
ScopeGuard __jakt_var_664([&] {
(((*this).current_function) = previous_function);
});
if ((((((((function)->linkage)).__jakt_init_index() == 1 /* External */) || ((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */)) || ((((function)->type)).__jakt_init_index() == 3 /* ImplicitEnumConstructor */)) || ((((function)->type)).__jakt_init_index() == 1 /* Destructor */))){
continue;
}
if (((((((function)->generics))->params)).is_empty())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function(function,false)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
}

}
}

}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ids::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::StructId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::StructId> ___struct_id__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::StructId> const jakt_____struct_id__ = ___struct_id__;
ByteString const _ = ((jakt_____struct_id__).template get<0>());
ids::StructId const struct_id = ((jakt_____struct_id__).template get<1>());

if ((!(((((struct_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
if (((((struct_).definition_linkage)).__jakt_init_index() == 1 /* External */)){
continue;
}
if ((!(((((struct_).generic_parameters)).is_empty())))){
continue;
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_debug_description_getter(struct_,false)))))));
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((struct_).scope_id)))));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
if (((((function)->force_inline)).__jakt_init_index() == 1 /* MakeDefinitionAvailable */)){
continue;
}
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function);
ScopeGuard __jakt_var_665([&] {
(((*this).current_function) = previous_function);
});
if (((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_constructor(function,false)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
else if (((((function)->type)).__jakt_init_index() == 1 /* Destructor */)){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_destructor(((struct_)),((function)),false)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
else if (((!(((((function)->type)).__jakt_init_index() == 3 /* ImplicitEnumConstructor */))) && ((!(((function)->is_comptime))) && ((((((function)->generics))->params)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_in_namespace(function,((struct_).type_id),false,false,JaktInternal::OptionalNone())))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
}

}
}

}

}
}

}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ids::EnumId> _magic = ((((scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::EnumId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::EnumId> ___enum_id__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::EnumId> const jakt_____enum_id__ = ___enum_id__;
ByteString const _ = ((jakt_____enum_id__).template get<0>());
ids::EnumId const enum_id = ((jakt_____enum_id__).template get<1>());

if ((!(((((enum_id).module)).equals(((current_module)->id)))))){
continue;
}
types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
if (((((enum_).definition_linkage)).__jakt_init_index() == 1 /* External */)){
continue;
}
if ((!(((((enum_).generic_parameters)).is_empty())))){
continue;
}
if (((((enum_).underlying_type_id)).equals(types::void_type_id()))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_debug_description_getter(enum_,false)))))));
JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>> const common_fields_variant_field_list_ = TRY((((*this).codegen_enum_field_lists(enum_))));
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields = ((common_fields_variant_field_list_).template get<0>());
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const variant_field_list = ((common_fields_variant_field_list_).template get<1>());

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_enum_constructors(enum_,false,JaktInternal::OptionalNone(),variant_field_list,common_fields)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{0}::~{0}()"sv)),((enum_).name)))))));
TRY((((*this).codegen_enum_destructor_body(enum_,((output))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("void {0}::__jakt_destroy_variant() {{\n"sv)),((enum_).name)))))));
TRY((((*this).codegen_enum_destroy_variant(enum_,((output))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
NonnullRefPtr<types::Scope> const scope = TRY((((((*this).program))->get_scope(((enum_).scope_id)))));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((((*this).program))->get_function(function_id));
JaktInternal::Optional<NonnullRefPtr<types::CheckedFunction>> const previous_function = ((*this).current_function);
(((*this).current_function) = function);
ScopeGuard __jakt_var_666([&] {
(((*this).current_function) = previous_function);
});
if (((!(((((function)->type)).__jakt_init_index() == 2 /* ImplicitConstructor */))) && ((!(((((function)->type)).__jakt_init_index() == 3 /* ImplicitEnumConstructor */))) && ((!(((((function)->type)).__jakt_init_index() == 1 /* Destructor */))) && ((!(((function)->is_comptime))) && ((((((function)->generics))->params)).is_empty())))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_function_in_namespace(function,((enum_).type_id),false,false,JaktInternal::OptionalNone())))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("\n"sv)))));
}
}

}
}

}

}
}

}

}
}

{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child_scope_id = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((((*this).program))->get_scope(child_scope_id))));
if (((((child_scope)->namespace_name)).has_value())){
ByteString const name = (((child_scope)->namespace_name).value());
TRY((((((*this).namespace_stack)).push(name))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_namespace(child_scope,current_module,as_forward)))))));
JaktInternal::Optional<ByteString> const dummy = ((((*this).namespace_stack)).pop());
}
}

}
}

if (((((scope)->namespace_name)).has_value())){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}\n"sv)))));
}
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_unchecked_binary_op_assignment(NonnullRefPtr<typename types::CheckedExpression> const lhs,NonnullRefPtr<typename types::CheckedExpression> const rhs,parser::BinaryOperator const op,ids::TypeId const type_id) {
{
ByteString output = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("auto& _jakt_ref = "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(lhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("_jakt_ref = static_cast<"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">(_jakt_ref "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* AddAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" + "sv)));
};/*case end*/
case 28 /* SubtractAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" - "sv)));
};/*case end*/
case 29 /* MultiplyAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" * "sv)));
};/*case end*/
case 31 /* DivideAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" / "sv)));
};/*case end*/
case 30 /* ModuloAssign */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(" % "sv)));
};/*case end*/
default: {
{
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Checked binary operation assignment codegen is not supported for BinaryOperator::{}"sv)),op))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_expression(rhs)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(");"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("}"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_constructor(NonnullRefPtr<types::CheckedFunction> const function,bool const is_inline) {
{
ids::TypeId const type_id = ((function)->return_type_id);
NonnullRefPtr<typename types::Type> const type_ = ((((*this).program))->get_type(type_id));
if (((type_)->__jakt_init_index() == 24 /* Struct */)){
ids::StructId const struct_id = (type_)->as.Struct.value;
types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
ByteString const qualified_name = TRY((((*this).codegen_type_possibly_as_namespace(type_id,true))));
ByteString output = TRY(ByteString::from_utf8(""sv));
if (((!(is_inline)) && (!(((((structure).generic_parameters)).is_empty()))))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("template <"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_template_parameter_names(((structure).generic_parameters))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">\n"sv)))));
}
if ((((((structure).record_type)).__jakt_init_index() == 1 /* Class */) || ((((structure).record_type)).__jakt_init_index() == 0 /* Struct */))){
if (is_inline){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((function)->name_for_codegen())).as_name_for_definition()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("{}::{}("sv)),qualified_name,TRY((((((function)->name_for_codegen())).as_name_for_definition())))))))));
}

bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

ids::TypeId const param_type_id = ((((param).variable))->type_id);
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(param_type_id)))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" a_"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
if ((!(((((function)->params)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(": "sv)))));
JaktInternal::DynamicArray<ByteString> initializers = (TRY((DynamicArray<ByteString>::create_with({}))));
size_t const parent_constructor_parameter_count = JaktInternal::checked_sub(((((function)->params)).size()),((((structure).fields)).size()));
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(parent_constructor_parameter_count,static_cast<size_t>(0ULL))){
ByteString parent_initializer = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(parent_initializer,TRY((((((((((*this).program))->get_struct((((structure).super_struct_id).value())))).name_for_codegen())).as_name_for_definition()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(parent_initializer,TRY(ByteString::from_utf8("("sv)))));
JaktInternal::DynamicArray<ByteString> strings = (TRY((DynamicArray<ByteString>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((((function)->params))[(JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parent_constructor_parameter_count)})])).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((strings).push(TRY((((TRY((((TRY(ByteString::from_utf8("move(a_"sv))) + (TRY((((((((param).variable))->name_for_codegen())).as_name_for_use())))))))) + (TRY(ByteString::from_utf8(")"sv))))))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(parent_initializer,TRY((utility::join(strings,TRY(ByteString::from_utf8(", "sv))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(parent_initializer,TRY(ByteString::from_utf8(")"sv)))));
TRY((((initializers).push(parent_initializer))));
}
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(parent_constructor_parameter_count),static_cast<size_t>(((((function)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedParameter const param = ((((function)->params))[i]);
TRY((((initializers).push(TRY((((TRY((((TRY((((TRY((((((((param).variable))->name_for_codegen())).as_name_for_use())))) + (TRY(ByteString::from_utf8("(move(a_"sv))))))) + (TRY((((((((param).variable))->name_for_codegen())).as_name_for_use())))))))) + (TRY(ByteString::from_utf8("))"sv))))))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((utility::join(initializers,TRY(ByteString::from_utf8(", "sv))))))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{}\n"sv)))));
if (((((structure).record_type)).__jakt_init_index() == 1 /* Class */)){
ByteString class_name_with_generics = TRY(ByteString::from_utf8(""sv));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY((((((structure).name_for_codegen())).as_name_for_definition()))))));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((structure).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8(", "sv)))));
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8("<"sv)))));
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY((((*this).codegen_type(((generic_parameter).type_id))))))));
}

}
}

if ((!(((((structure).generic_parameters)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(class_name_with_generics,TRY(ByteString::from_utf8(">"sv)))));
}
if (is_inline){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("static "sv)))));
}
ByteString const qualified_namespace = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (is_inline);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((qualified_name) + (TRY(ByteString::from_utf8("::"sv)))))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal("ErrorOr<NonnullRefPtr<{}>> {}__jakt_create"sv)),class_name_with_generics,qualified_namespace))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((((param).variable))->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" "sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((__jakt_format((StringView::from_string_literal(") {{ auto o = {}(adopt_nonnull_ref_or_enomem(new (nothrow) {} ("sv)),TRY((((*this).current_error_handler()))),class_name_with_generics))))));
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("move("sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")"sv)))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("))); return o; }"sv)))));
}
return output;
}
if ((!(is_inline))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,qualified_name)));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("::"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((function)->name_for_codegen())).as_name_for_definition()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(((((param).variable))->type_id))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(" a_"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_definition()))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(") "sv)))));
if ((!(((((function)->params)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(":"sv)))));
}
(first = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("(move(a_"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((((param).variable))->name_for_codegen())).as_name_for_use()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("))"sv)))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("{}\n"sv)))));
return output;
}
else {
utility::panic(TRY(ByteString::from_utf8("internal error: call to a constructor, but not a struct/class type"sv)));
}

}
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_type_possibly_as_namespace(ids::TypeId const type_id,bool const as_namespace) {
{
ByteString qualifiers = TRY(ByteString::from_utf8(""sv));
if (((!(as_namespace)) && ((((((((*this).program))->get_type(type_id)))->common.init_common.qualifiers)).is_immutable))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(qualifiers,TRY(ByteString::from_utf8(" const"sv)))));
}
if (((((*this).generic_inferences)).has_value())){
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const mappings = (((*this).generic_inferences).value());
if (((((mappings).get(type_id))).has_value())){
ids::TypeId const id = (((mappings).get(type_id)).value());
return TRY((((TRY((((*this).codegen_type_possibly_as_namespace(id,as_namespace))))) + (qualifiers))));
}
}
return TRY((((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("void"sv)));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("bool"sv)));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("u8"sv)));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("u16"sv)));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("u32"sv)));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("u64"sv)));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("i8"sv)));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("i16"sv)));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("i32"sv)));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("i64"sv)));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("f32"sv)));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("f64"sv)));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("size_t"sv)));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("ByteString"sv)));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("char"sv)));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("int"sv)));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("void"sv)));
};/*case end*/
case 32 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_667; {
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((interpreter::Interpreter::create(((*this).compiler),((*this).program),TRY((types::TypecheckFunctions::__jakt_create([](parser::ParsedBlock parsed_block, ids::ScopeId parent_scope_id, types::SafetyMode safety_mode, JaktInternal::Optional<ids::TypeId> yield_type_hint, JaktInternal::Optional<ids::FunctionId> containing_function_id) -> ErrorOr<types::CheckedBlock> {
{
return Error::__jakt_from_string_literal((StringView::from_string_literal("Cannot typecheck a const block"sv)));
}
}
,[](NonnullRefPtr<types::CheckedFunction> function) -> ErrorOr<ids::FunctionId> {
{
return Error::__jakt_from_string_literal((StringView::from_string_literal("Cannot typecheck a const function"sv)));
}
}
))),(TRY((DynamicArray<utility::Span>::create_with({})))))));
NonnullRefPtr<typename types::CheckedExpression> const expr = TRY((interpreter::value_to_checked_expression(value,interpreter)));
__jakt_var_667 = TRY((((*this).codegen_expression(expr)))); goto __jakt_label_563;

}
__jakt_label_563:; __jakt_var_667.release_value(); }));
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((((((*this).program))->get_type(type_id)))->is_boxed(((*this).program))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((TRY((((*this).codegen_type_possibly_as_namespace(type_id,true))))) + (TRY(ByteString::from_utf8("*"sv)))))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((TRY((((*this).codegen_type(type_id))))) + (TRY(ByteString::from_utf8("*"sv)))))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((TRY((((*this).codegen_type(type_id))))) + (TRY(ByteString::from_utf8(" const&"sv)))))));
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((TRY((((*this).codegen_type(type_id))))) + (TRY(ByteString::from_utf8("&"sv)))))));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_generic_type_instance(id,args,as_namespace)))));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_generic_type_instance(id,args,as_namespace)))));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_668; {
JaktInternal::Optional<ids::TypeId> const implements_type = ((((((*this).program))->get_struct(id))).implements_type);
__jakt_var_668 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((implements_type).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_type_possibly_as_namespace((implements_type.value()),as_namespace)))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((*this).codegen_struct_type(id,as_namespace)))));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_564;

}
__jakt_label_564:; __jakt_var_668.release_value(); }));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_enum_type(id,as_namespace)))));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((((*this).codegen_generic_enum_instance(id,args,as_namespace)))));
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 30 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_669; {
ByteString output = TRY(ByteString::from_utf8("Function<"sv));
if (can_throw){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("ErrorOr<"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(return_type_id)))))));
if (can_throw){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("("sv)))));
bool first = true;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId param = (_magic_value.value());
{
if (first){
(first = false);
}
else {
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(", "sv)))));
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_type(param)))))));
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(")>"sv)))));
__jakt_var_669 = output; goto __jakt_label_565;

}
__jakt_label_565:; __jakt_var_669.release_value(); }));
};/*case end*/
case 22 /* GenericTraitInstance */: {
{
utility::panic(TRY(ByteString::from_utf8("Generic trait instance in codegen"sv)));
}
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_670; {
__jakt_var_670 = TRY(ByteString::from_utf8("auto"sv)); goto __jakt_label_566;

}
__jakt_label_566:; __jakt_var_670.release_value(); }));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})) + (qualifiers))));
}
}

ErrorOr<void> codegen::CodeGenerator::codegen_enum_destructor_body(types::CheckedEnum const enum_,ByteString& output) const {
{
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8("{\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8("if (this->__jakt_variant_index == 0) return;\n"sv)))));
size_t const common_field_count = ((((enum_).fields)).size());
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField common_field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((((*this).program))->get_variable(((common_field).variable_id)));
JaktInternal::Optional<ByteString> const ds = TRY((((*this).destructor_name(((variable)->type_id)))));
if (((ds).has_value())){
ByteString const name = (ds.value());
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY((__jakt_format((StringView::from_string_literal("this->common.init_common.{}.~{}();\n"sv)),TRY((((((variable)->name_for_codegen())).as_name_for_use()))),name))))));
}
}

}
}

TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8("this->__jakt_destroy_variant();\n"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(((output)),TRY(ByteString::from_utf8("}\n"sv)))));
}
return {};
}

ErrorOr<ByteString> codegen::CodeGenerator::codegen_struct_predecl(types::CheckedStruct const struct_) {
{
if (((((struct_).definition_linkage)).__jakt_init_index() == 1 /* External */)){
return TRY(ByteString::from_utf8(""sv));
}
ByteString output = TRY(ByteString::from_utf8(""sv));
if ((!(((((struct_).generic_parameters)).is_empty())))){
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8("template <"sv)))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).codegen_template_parameter_names(((struct_).generic_parameters))))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(">"sv)))));
}
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("class "sv)));
};/*case end*/
case 0 /* Struct */: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8("struct "sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY(ByteString::from_utf8(""sv)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((((struct_).name_for_codegen())).as_name_for_definition()))))));
TRY(([](ByteString& self, ByteString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(ByteString::from_utf8(";"sv)))));
return output;
}
}

ErrorOr<ByteString> codegen::AllowedControlExits::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Nothing */: {
return ByteString("AllowedControlExits::Nothing"sv);
break;}
case 1 /* JustReturn */: {
return ByteString("AllowedControlExits::JustReturn"sv);
break;}
case 2 /* AtLoop */: {
return ByteString("AllowedControlExits::AtLoop"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] AllowedControlExits AllowedControlExits::Nothing(){
AllowedControlExits __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] AllowedControlExits AllowedControlExits::JustReturn(){
AllowedControlExits __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] AllowedControlExits AllowedControlExits::AtLoop(){
AllowedControlExits __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
AllowedControlExits& AllowedControlExits::operator=(AllowedControlExits const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* JustReturn */:
break;
case 2 /* AtLoop */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* JustReturn */:
break;
case 2 /* AtLoop */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
AllowedControlExits::AllowedControlExits(AllowedControlExits const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* JustReturn */:
break;
case 2 /* AtLoop */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
AllowedControlExits& AllowedControlExits::operator=(AllowedControlExits &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* JustReturn */:
break;
case 2 /* AtLoop */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* JustReturn */:
break;
case 2 /* AtLoop */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
AllowedControlExits::AllowedControlExits(AllowedControlExits &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* JustReturn */:
break;
case 2 /* AtLoop */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
AllowedControlExits::~AllowedControlExits(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void AllowedControlExits::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Nothing */:break;
case 1 /* JustReturn */:break;
case 2 /* AtLoop */:break;
}
}
codegen::AllowedControlExits codegen::AllowedControlExits::allow_return() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<codegen::AllowedControlExits, codegen::AllowedControlExits>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Nothing */: {
return JaktInternal::ExplicitValue(codegen::AllowedControlExits::JustReturn());
};/*case end*/
case 1 /* JustReturn */: {
return JaktInternal::ExplicitValue(codegen::AllowedControlExits::JustReturn());
};/*case end*/
case 2 /* AtLoop */: {
return JaktInternal::ExplicitValue(codegen::AllowedControlExits::AtLoop());
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

}
} // namespace Jakt
