#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "codegen.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace codegen {
bool are_loop_exits_allowed(Jakt::codegen::AllowedControlExits const allowed_control_exits) {
{
return allowed_control_exits.__jakt_init_index() == 2 /* AtLoop */;
}
}

bool is_return_allowed(Jakt::codegen::AllowedControlExits const allowed_control_exits) {
{
return !(allowed_control_exits.__jakt_init_index() == 0 /* Nothing */);
}
}

bool pattern_has_bindings(Jakt::types::CheckedMatchPattern const& pattern) {
{
if (!pattern.common.init_common.defaults.is_empty()){
return true;
}
{auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
return !args.is_empty();};/*case end*/
case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;JaktInternal::Optional<Jakt::types::ClassInstanceRebind> const& rebind_name = __jakt_match_value.rebind_name;
return rebind_name.has_value();};/*case end*/
case 3 /* CatchAll */:case 1 /* Expression */:return false;default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

bool case_has_bindings(Jakt::types::CheckedMatchCase const& match_case) {
{
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchPattern> _magic = match_case.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchPattern pattern = _magic_value.value();
{
if (Jakt::codegen::pattern_has_bindings(pattern)){
return true;
}
}

}
}

return false;
}
}

size_t count_match_cases(JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const& cases) {
{
size_t count = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchCase case_ = _magic_value.value();
{
count += case_.patterns.size();
}

}
}

return count;
}
}

bool has_cpp_value(Jakt::ids::TypeId const type_id) {
{
return [](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(type_id,Jakt::types::void_type_id()) && [](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(type_id,Jakt::types::never_type_id());
}
}

bool has_control_flow(Jakt::types::CheckedMatchCase const match_case,bool const include_loop_control_flow) {
{
{auto&& __jakt_match_variant = match_case.body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& t = __jakt_match_value.value;
return Jakt::codegen::has_control_flow(t,include_loop_control_flow);};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& t = __jakt_match_value.value;
return Jakt::codegen::has_control_flow(t,include_loop_control_flow);};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

bool has_control_flow(Jakt::types::CheckedBlock const block,bool const include_loop_control_flow) {
{
return Jakt::codegen::has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(block.statements,include_loop_control_flow);
}
}

bool has_control_flow(NonnullRefPtr<typename Jakt::types::CheckedStatement> const stmt,bool const include_loop_control_flow) {
{
{auto&& __jakt_match_variant = *stmt;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 1 /* Defer */:case 11 /* Throw */:case 12 /* Yield */:case 14 /* Garbage */:return false;case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
return Jakt::codegen::has_control_flow(var_decl,include_loop_control_flow);};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& init = __jakt_match_value.init;
return Jakt::codegen::has_control_flow(init,include_loop_control_flow);};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return (Jakt::codegen::has_control_flow(condition,include_loop_control_flow) || Jakt::codegen::has_control_flow(then_block,include_loop_control_flow)) || Jakt::codegen::has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(else_statement,include_loop_control_flow);};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return Jakt::codegen::has_control_flow(block,include_loop_control_flow);};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return Jakt::codegen::has_control_flow(block,false);};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return Jakt::codegen::has_control_flow(condition,include_loop_control_flow) || Jakt::codegen::has_control_flow(block,false);};/*case end*/
case 8 /* Return */:case 13 /* InlineCpp */:return true;case 9 /* Break */:case 10 /* Continue */:return include_loop_control_flow;default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

bool has_control_flow(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,bool const include_loop_control_flow) {
{
{auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */:case 1 /* NumericConstant */:case 2 /* QuotedString */:case 3 /* ByteConstant */:case 4 /* CharacterConstant */:case 5 /* CCharacterConstant */:case 23 /* NamespacedVar */:case 24 /* Var */:case 25 /* OptionalNone */:case 29 /* Function */:case 30 /* DependentFunction */:case 34 /* Reflect */:case 35 /* Garbage */:return false;case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 31 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow);};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
return Jakt::codegen::has_control_flow(lhs,include_loop_control_flow) || Jakt::codegen::has_control_flow(rhs,include_loop_control_flow);};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& lhs = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& rhs = __jakt_match_value.index;
return Jakt::codegen::has_control_flow(lhs,include_loop_control_flow) || Jakt::codegen::has_control_flow(rhs,include_loop_control_flow);};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& lhs = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& rhs = __jakt_match_value.index;
return Jakt::codegen::has_control_flow(lhs,include_loop_control_flow) || Jakt::codegen::has_control_flow(rhs,include_loop_control_flow);};/*case end*/
case 18 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& lhs = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& rhs = __jakt_match_value.index;
return Jakt::codegen::has_control_flow(lhs,include_loop_control_flow) || Jakt::codegen::has_control_flow(rhs,include_loop_control_flow);};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return Jakt::codegen::has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(vals,include_loop_control_flow);};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return Jakt::codegen::has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(vals,include_loop_control_flow);};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return Jakt::codegen::has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(vals,include_loop_control_flow);};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& to = __jakt_match_value.to;
return Jakt::codegen::has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(from,include_loop_control_flow) || Jakt::codegen::has_control_flow<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(to,include_loop_control_flow);};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return Jakt::codegen::has_control_flow<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(vals,include_loop_control_flow);};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow) || Jakt::codegen::has_control_flow<Jakt::types::CheckedMatchCase>(match_cases,true);};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
return Jakt::codegen::has_control_flow<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(call.args,include_loop_control_flow);};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedCall const& call = __jakt_match_value.call;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow) || Jakt::codegen::has_control_flow<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>(call.args,include_loop_control_flow);};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return Jakt::codegen::has_control_flow(block,include_loop_control_flow);};/*case end*/
case 32 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<Jakt::types::CheckedBlock> const& catch_block = __jakt_match_value.catch_block;
return Jakt::codegen::has_control_flow(expr,include_loop_control_flow) || Jakt::codegen::has_control_flow<Jakt::types::CheckedBlock>(catch_block,include_loop_control_flow);};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
Jakt::types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
return Jakt::codegen::has_control_flow(stmt,include_loop_control_flow) || Jakt::codegen::has_control_flow(catch_block,include_loop_control_flow);};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

bool has_control_flow(JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const dict_pair,bool const include_loop_control_flow) {
{
return Jakt::codegen::has_control_flow(dict_pair.template get<0>(),include_loop_control_flow) || Jakt::codegen::has_control_flow(dict_pair.template get<1>(),include_loop_control_flow);
}
}

bool has_control_flow(JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const call_arg,bool const include_loop_control_flow) {
{
return Jakt::codegen::has_control_flow(call_arg.template get<1>(),include_loop_control_flow);
}
}

ByteString Jakt::codegen::ControlFlowState::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ControlFlowState("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("allowed_exits: {}, ", allowed_exits);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("passes_through_try: {}, ", passes_through_try);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("directly_inside_match: {}, ", directly_inside_match);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("indirectly_inside_match: {}, ", indirectly_inside_match);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("indirectly_inside_try_block: {}", indirectly_inside_try_block);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::codegen::ControlFlowState Jakt::codegen::ControlFlowState::no_control_flow() {
{
return Jakt::codegen::ControlFlowState(Jakt::codegen::AllowedControlExits::Nothing(),false,false,false,false);
}
}

Jakt::codegen::ControlFlowState Jakt::codegen::ControlFlowState::enter_function() const {
{
return Jakt::codegen::ControlFlowState(Jakt::codegen::AllowedControlExits::JustReturn(),false,false,false,false);
}
}

Jakt::codegen::ControlFlowState Jakt::codegen::ControlFlowState::enter_loop() const {
{
return Jakt::codegen::ControlFlowState(Jakt::codegen::AllowedControlExits::AtLoop(),this->passes_through_try,false,this->indirectly_inside_match,false);
}
}

Jakt::codegen::ControlFlowState Jakt::codegen::ControlFlowState::enter_match() const {
{
return Jakt::codegen::ControlFlowState(this->allowed_exits.allow_return(),this->passes_through_try,true,true,false);
}
}

ErrorOr<ByteString> Jakt::codegen::ControlFlowState::apply_control_flow_macro(ByteString const x,Jakt::ids::TypeId const func_return_type,bool const func_can_throw) const {
{
ByteString const handle_loop_controls = [&]() -> ByteString { auto __jakt_enum_value = Jakt::codegen::are_loop_exits_allowed(this->allowed_exits);
if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}else if (__jakt_enum_value) {{
JaktInternal::Tuple<ByteString,ByteString> const break_stmt_continue_stmt_ = [&]() -> JaktInternal::Tuple<ByteString,ByteString> { auto __jakt_enum_value = this->directly_inside_match;
if (__jakt_enum_value) {return Tuple{ByteString::from_utf8_without_validation("return JaktInternal::LoopBreak {}"sv), ByteString::from_utf8_without_validation("return JaktInternal::LoopContinue {}"sv)};}else if (!__jakt_enum_value) {return Tuple{ByteString::from_utf8_without_validation("break"sv), ByteString::from_utf8_without_validation("continue"sv)};}VERIFY_NOT_REACHED();
 
}();
ByteString const break_stmt = break_stmt_continue_stmt_.template get<0>();
ByteString const continue_stmt = break_stmt_continue_stmt_.template get<1>();

return __jakt_format(StringView::from_string_literal("if (_jakt_value.is_loop_break())\n        {};\n    if (_jakt_value.is_loop_continue())\n        {};\n    "sv),break_stmt,continue_stmt);
}
VERIFY_NOT_REACHED();
}VERIFY_NOT_REACHED();
 
}();
bool const cpp_func_returns_void = (!func_can_throw) && ((func_return_type.equals(Jakt::types::void_type_id()) || func_return_type.equals(Jakt::types::unknown_type_id())) || func_return_type.equals(Jakt::types::never_type_id()));
bool const substitute_naked_return = this->indirectly_inside_match && cpp_func_returns_void;
ByteString const forward_return_expr = [&]() -> ByteString { auto __jakt_enum_value = substitute_naked_return;
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("{}"sv);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation("_jakt_value.release_return()"sv);}VERIFY_NOT_REACHED();
 
}();
return __jakt_format(StringView::from_string_literal("({{\n    auto&& _jakt_value = {0};\n    if (_jakt_value.is_return())\n        return {1};\n    {2}_jakt_value.release_value();\n}})"sv),x,forward_return_expr,handle_loop_controls);
}
}

Jakt::codegen::ControlFlowState::ControlFlowState(Jakt::codegen::AllowedControlExits a_allowed_exits, bool a_passes_through_try, bool a_directly_inside_match, bool a_indirectly_inside_match, bool a_indirectly_inside_try_block): allowed_exits(move(a_allowed_exits)), passes_through_try(move(a_passes_through_try)), directly_inside_match(move(a_directly_inside_match)), indirectly_inside_match(move(a_indirectly_inside_match)), indirectly_inside_try_block(move(a_indirectly_inside_try_block)){}

ByteString Jakt::codegen::LineSpan::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("LineSpan("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("start: {}, ", start);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("end: {}", end);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::codegen::LineSpan::LineSpan(size_t a_start, size_t a_end): start(move(a_start)), end(move(a_end)){}

ByteString Jakt::codegen::CodegenDebugInfo::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CodegenDebugInfo("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("line_spans: {}, ", line_spans);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("statement_span_comments: {}", statement_span_comments);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<ByteString> Jakt::codegen::CodegenDebugInfo::span_to_source_location(Jakt::utility::Span const span) {
{
if (this->line_spans.is_empty()){
TRY((this->gather_line_spans()));
}
size_t const file_idx = span.file_id.id;
if (!this->line_spans.contains(file_idx)){
return ByteString::from_utf8_without_validation(""sv);
}
size_t line_index = static_cast<size_t>(0ULL);
while (line_index < this->line_spans.operator[](file_idx).size()){
if ((span.start >= this->line_spans.operator[](file_idx).operator[](line_index).start) && (span.start <= this->line_spans.operator[](file_idx).operator[](line_index).end)){
size_t const column_index = JaktInternal::checked_sub(span.start,this->line_spans.operator[](file_idx).operator[](line_index).start);
return __jakt_format(StringView::from_string_literal("{} \"{}\""sv),JaktInternal::checked_add(line_index,static_cast<size_t>(1ULL)),this->compiler->get_file_path(span.file_id).value().to_string());
}
line_index += static_cast<size_t>(1ULL);
}
Jakt::utility::panic(ByteString::from_utf8_without_validation("Reached end of file and could not find index"sv));
}
}

ErrorOr<void> Jakt::codegen::CodegenDebugInfo::gather_line_spans() {
{
{
JaktInternal::DictionaryIterator<ByteString,Jakt::utility::FileId> _magic = this->compiler->file_ids.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::utility::FileId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::utility::FileId> file = _magic_value.value();
{
if (file.template get<0>() == ByteString::from_utf8_without_validation("__prelude__"sv)){
continue;
}
TRY((this->compiler->set_current_file(file.template get<1>())));
size_t const file_idx = file.template get<1>().id;
JaktInternal::DynamicArray<Jakt::codegen::LineSpan> const empty_array = DynamicArray<Jakt::codegen::LineSpan>::create_with({});
this->line_spans.set(file_idx,empty_array);
size_t idx = static_cast<size_t>(0ULL);
size_t start = idx;
while (idx < this->compiler->current_file_contents.size()){
if (this->compiler->current_file_contents.operator[](idx) == static_cast<u8>(u8'\n')){
this->line_spans.operator[](file_idx).push(Jakt::codegen::LineSpan(start,idx));
start = JaktInternal::checked_add(idx,static_cast<size_t>(1ULL));
}
idx += static_cast<size_t>(1ULL);
}
if (start < idx){
this->line_spans.operator[](file_idx).push(Jakt::codegen::LineSpan(start,idx));
}
}

}
}

}
return {};
}

Jakt::codegen::CodegenDebugInfo::CodegenDebugInfo(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, JaktInternal::Dictionary<size_t,JaktInternal::DynamicArray<Jakt::codegen::LineSpan>> a_line_spans, bool a_statement_span_comments): compiler(move(a_compiler)), line_spans(move(a_line_spans)), statement_span_comments(move(a_statement_span_comments)){}

ByteString Jakt::codegen::CodeGenerator::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CodeGenerator("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("program: {}, ", *program);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("control_flow_state: {}, ", control_flow_state);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("entered_yieldable_blocks: {}, ", entered_yieldable_blocks);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("deferred_output: {}, ", deferred_output);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_function: {}, ", current_function);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inside_defer: {}, ", inside_defer);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("debug_info: {}, ", debug_info);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespace_stack: {}, ", namespace_stack);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fresh_var_counter: {}, ", fresh_var_counter);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fresh_label_counter: {}, ", fresh_label_counter);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("this_replacement: {}, ", this_replacement);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("used_modules: {}, ", used_modules);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("yield_method: {}, ", yield_method);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("yields_erroror: {}", yields_erroror);
}
builder.append(")"sv);return builder.to_string(); }
ByteString Jakt::codegen::CodeGenerator::current_error_handler(bool const forward_error_with_try) {
{
if (this->inside_defer || ((this->current_function.has_value() && this->current_function.value()->return_type_id.equals(Jakt::types::never_type_id())) && (!this->control_flow_state.passes_through_try))){
return ByteString::from_utf8_without_validation("MUST"sv);
}
this->yields_erroror = true;
if (forward_error_with_try){
if (this->control_flow_state.indirectly_inside_try_block){
return ByteString::from_utf8_without_validation("TRY_EXPLICIT"sv);
}
else {
return ByteString::from_utf8_without_validation("TRY"sv);
}

}
else {
return ByteString::from_utf8_without_validation(""sv);
}

}
}

ByteString Jakt::codegen::CodeGenerator::fresh_var() {
{
return __jakt_format(StringView::from_string_literal("__jakt_var_{}"sv),this->fresh_var_counter++);
}
}

ByteString Jakt::codegen::CodeGenerator::fresh_label() {
{
return __jakt_format(StringView::from_string_literal("__jakt_label_{}"sv),this->fresh_label_counter++);
}
}

JaktInternal::DynamicArray<Jakt::ids::ModuleId> Jakt::codegen::CodeGenerator::topologically_sort_modules() const {
{
JaktInternal::Dictionary<size_t,i64> in_degrees = Dictionary<size_t, i64>::create_with_entries({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::Module>> _magic = this->program->modules.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::Module>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::Module> module = _magic_value.value();
{
{
JaktInternal::ArrayIterator<Jakt::ids::ModuleId> _magic = module->imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId imported_module = _magic_value.value();
{
i64 const existing = in_degrees.get(imported_module.id).value_or_lazy_evaluated([&] { return static_cast<i64>(0LL); });
in_degrees.set(imported_module.id,JaktInternal::checked_add(existing,static_cast<i64>(1LL)));
}

}
}

if (!in_degrees.contains(module->id.id)){
in_degrees.set(module->id.id,static_cast<i64>(0LL));
}
}

}
}

JaktInternal::DynamicArray<Jakt::ids::ModuleId> stack = DynamicArray<Jakt::ids::ModuleId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::Module>> _magic = this->program->modules.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::Module>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::Module> module = _magic_value.value();
{
if (in_degrees.operator[](module->id.id) == static_cast<i64>(0LL)){
stack.push(module->id);
}
}

}
}

JaktInternal::DynamicArray<Jakt::ids::ModuleId> sorted_modules = DynamicArray<Jakt::ids::ModuleId>::create_with({});
while (!stack.is_empty()){
Jakt::ids::ModuleId const id = stack.pop().value();
sorted_modules.push(id);
{
JaktInternal::ArrayIterator<Jakt::ids::ModuleId> _magic = this->program->modules.operator[](id.id)->imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId imported_module = _magic_value.value();
{
i64 const module_in_degrees = in_degrees.operator[](imported_module.id);
in_degrees.set(imported_module.id,JaktInternal::checked_sub(module_in_degrees,static_cast<i64>(1LL)));
if (module_in_degrees == static_cast<i64>(1LL)){
stack.push(Jakt::ids::ModuleId(imported_module.id));
}
}

}
}

}
if (sorted_modules.size() == this->program->modules.size()){
return sorted_modules;
}
Jakt::utility::panic(ByteString::from_utf8_without_validation("Cyclic module imports"sv));
}
}

ErrorOr<JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>>> Jakt::codegen::CodeGenerator::generate(NonnullRefPtr<Jakt::compiler::Compiler> const compiler,NonnullRefPtr<Jakt::types::CheckedProgram> const program,bool const debug_info,JaktInternal::Dictionary<ByteString,ByteString>& exported_files) {
{
Jakt::codegen::CodeGenerator generator = Jakt::codegen::CodeGenerator(compiler,program,Jakt::codegen::ControlFlowState::no_control_flow(),DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({}),ByteStringBuilder::create(),JaktInternal::OptionalNone(),false,Jakt::codegen::CodegenDebugInfo(compiler,Dictionary<size_t, JaktInternal::DynamicArray<Jakt::codegen::LineSpan>>::create_with_entries({}),debug_info),DynamicArray<ByteString>::create_with({}),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Set<Jakt::ids::ModuleId>::create_with_values({}),JaktInternal::OptionalNone(),false);
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ByteString,ByteString>> result = Dictionary<ByteString, JaktInternal::Tuple<ByteString,ByteString>>::create_with_entries({});
ByteStringBuilder output = ByteStringBuilder::create();
JaktInternal::DynamicArray<Jakt::ids::ModuleId> const sorted_modules = generator.topologically_sort_modules();
JaktInternal::Dictionary<size_t,JaktInternal::Set<Jakt::ids::ModuleId>> modules_in_header = Dictionary<size_t, JaktInternal::Set<Jakt::ids::ModuleId>>::create_with_entries({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(sorted_modules.size()),static_cast<size_t>(static_cast<size_t>(0ULL))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t idx = _magic_value.value();
{
size_t const i = sorted_modules.operator[](JaktInternal::checked_sub(idx,static_cast<size_t>(1ULL))).id;
if (i == static_cast<size_t>(0ULL)){
continue;
}
NonnullRefPtr<Jakt::types::Module> const module = generator.program->modules.operator[](i);
generator.compiler->dbg_println(__jakt_format(StringView::from_string_literal("generate: module idx: {}, module.name {} - forward: {}"sv),i,module->name,true));
ByteString const header_name = __jakt_format(StringView::from_string_literal("{}.h"sv),module->name);
output.clear();
output.append(StringView::from_string_literal("#pragma once\n"sv));
output.append(StringView::from_string_literal("#include <lib.h>\n"sv));
size_t const main_id = [&]() -> size_t { auto __jakt_enum_value = module->id.id;
if (__jakt_enum_value == static_cast<size_t>(1ULL)) {return static_cast<size_t>(1ULL);}else {return static_cast<size_t>(0ULL);} 
}();
Jakt::ids::ScopeId const scope_id = Jakt::ids::ScopeId(module->id,main_id);
NonnullRefPtr<Jakt::types::Scope> const scope = generator.program->get_scope(scope_id);
{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child_scope_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::Scope> const scope = generator.program->get_scope(child_scope_id);
if (scope->import_path_if_extern.has_value()){
JaktInternal::Optional<ByteString> const name = scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_definition(); });
if (name.has_value()){
output.appendff(ByteString::from_utf8_without_validation("namespace {} {{\n"sv),name.value());
}
{
JaktInternal::ArrayIterator<Jakt::parser::IncludeAction> _magic = scope->before_extern_include.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::IncludeAction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::IncludeAction action = _magic_value.value();
{
{auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Define */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Define;ByteString const& name = __jakt_match_value.name;
ByteString const& value = __jakt_match_value.value;
{
output.appendff(ByteString::from_utf8_without_validation("#ifdef {}\n"sv),name);
output.appendff(ByteString::from_utf8_without_validation("#undef {}\n"sv),name);
output.append(StringView::from_string_literal("#endif\n"sv));
output.appendff(ByteString::from_utf8_without_validation("#define {} {}\n"sv),name,value);
}
goto __jakt_label_154;};/*case end*/
case 1 /* Undefine */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Undefine;ByteString const& name = __jakt_match_value.name;
{
output.appendff(ByteString::from_utf8_without_validation("#ifdef {}\n"sv),name);
output.appendff(ByteString::from_utf8_without_validation("#undef {}\n"sv),name);
output.append(StringView::from_string_literal("#endif\n"sv));
}
goto __jakt_label_154;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
break;}goto __jakt_label_154; __jakt_label_154:;;
}

}
}

output.appendff(ByteString::from_utf8_without_validation("#include <{}>\n"sv),scope->import_path_if_extern.value());
{
JaktInternal::ArrayIterator<Jakt::parser::IncludeAction> _magic = scope->after_extern_include.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::IncludeAction> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::IncludeAction action = _magic_value.value();
{
{auto&& __jakt_match_variant = action;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Define */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Define;ByteString const& name = __jakt_match_value.name;
ByteString const& value = __jakt_match_value.value;
{
output.appendff(ByteString::from_utf8_without_validation("#ifdef {}\n"sv),name);
output.appendff(ByteString::from_utf8_without_validation("#undef {}\n"sv),name);
output.append(StringView::from_string_literal("#endif\n"sv));
output.appendff(ByteString::from_utf8_without_validation("#define {} {}\n"sv),name,value);
}
goto __jakt_label_155;};/*case end*/
case 1 /* Undefine */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Undefine;ByteString const& name = __jakt_match_value.name;
{
output.appendff(ByteString::from_utf8_without_validation("#ifdef {}\n"sv),name);
output.appendff(ByteString::from_utf8_without_validation("#undef {}\n"sv),name);
output.append(StringView::from_string_literal("#endif\n"sv));
}
goto __jakt_label_155;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
break;}goto __jakt_label_155; __jakt_label_155:;;
}

}
}

if (name.has_value()){
output.append(StringView::from_string_literal(" } // namespace "sv));
output.append(name.value());
output.append(StringView::from_string_literal("\n"sv));
}
}
}

}
}

ByteStringBuilder after_headers = ByteStringBuilder::create();
after_headers.append(StringView::from_string_literal("namespace Jakt {\n"sv));
if (!module->is_root){
generator.namespace_stack.push(module->name);
}
JaktInternal::Set<Jakt::ids::ModuleId> const required_imports = TRY((generator.capturing_modules(module,[scope](Jakt::codegen::CodeGenerator& generator, NonnullRefPtr<Jakt::types::Module> module, ByteStringBuilder& output) -> ErrorOr<void> {{
TRY((generator.codegen_namespace_predecl(scope,module,output)));
TRY((generator.codegen_namespace_forward(scope,module,output)));
}
return {};
}
,after_headers)));
JaktInternal::DynamicArray<Jakt::ids::ModuleId> const ordered_imports = Jakt::codegen::CodeGenerator::get_topologically_sorted_modules(sorted_modules,required_imports);
modules_in_header.set(i,required_imports);
if (!module->is_root){
JaktInternal::Optional<ByteString> const dummy = generator.namespace_stack.pop();
}
{
JaktInternal::ArrayIterator<Jakt::ids::ModuleId> _magic = ordered_imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId id = _magic_value.value();
{
if ((id.id != static_cast<size_t>(0ULL)) && (id.id != module->id.id)){
NonnullRefPtr<Jakt::types::Module> const module = generator.program->modules.operator[](id.id);
output.appendff(ByteString::from_utf8_without_validation("#include \"{}.h\"\n"sv),module->name);
}
else {
continue;
}

}

}
}

output.append(after_headers.to_string());
output.append(StringView::from_string_literal("} // namespace Jakt\n"sv));
result.set(header_name,Tuple{output.to_string(), module->resolved_import_path});
}

}
}

{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(sorted_modules.size()),static_cast<size_t>(static_cast<size_t>(0ULL))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t idx = _magic_value.value();
{
size_t const i = sorted_modules.operator[](JaktInternal::checked_sub(idx,static_cast<size_t>(1ULL))).id;
if (i == static_cast<size_t>(0ULL)){
continue;
}
NonnullRefPtr<Jakt::types::Module> const module = generator.program->modules.operator[](i);
generator.compiler->dbg_println(__jakt_format(StringView::from_string_literal("generate: module idx: {}, module.name {} - forward: {}"sv),i,module->name,false));
ByteString const header_name = __jakt_format(StringView::from_string_literal("{}.h"sv),module->name);
ByteString const impl_name = __jakt_format(StringView::from_string_literal("{}.cpp"sv),module->name);
output.clear();
output.append(StringView::from_string_literal("#ifdef _WIN32\n"sv));
output.append(StringView::from_string_literal("extern \"C\" __cdecl int SetConsoleOutputCP(unsigned int code_page);\n"sv));
output.append(StringView::from_string_literal("#endif\n"sv));
size_t const main_id = [&]() -> size_t { auto __jakt_enum_value = module->id.id;
if (__jakt_enum_value == static_cast<size_t>(1ULL)) {return static_cast<size_t>(1ULL);}else {return static_cast<size_t>(0ULL);} 
}();
Jakt::ids::ScopeId const scope_id = Jakt::ids::ScopeId(module->id,main_id);
NonnullRefPtr<Jakt::types::Scope> const scope = generator.program->get_scope(scope_id);
if (!module->is_root){
generator.namespace_stack.push(module->name);
}
ByteStringBuilder inside_namespace = ByteStringBuilder::create();
JaktInternal::Set<Jakt::ids::ModuleId> required_imports = TRY((generator.capturing_modules(module,[scope](Jakt::codegen::CodeGenerator& gen, NonnullRefPtr<Jakt::types::Module> module, ByteStringBuilder& output) -> ErrorOr<void> {{
TRY((gen.codegen_namespace(scope,module,output)));
}
return {};
}
,inside_namespace)));
JaktInternal::Optional<JaktInternal::Set<Jakt::ids::ModuleId>> __jakt_tmp379 = modules_in_header.get(i);
if (__jakt_tmp379.has_value()){
JaktInternal::Set<Jakt::ids::ModuleId> const already_included = __jakt_tmp379.value();
{
JaktInternal::SetIterator<Jakt::ids::ModuleId> _magic = already_included.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId imported_by_header = _magic_value.value();
{
required_imports.remove(imported_by_header);
}

}
}

}
JaktInternal::DynamicArray<Jakt::ids::ModuleId> const ordered_imports = Jakt::codegen::CodeGenerator::get_topologically_sorted_modules(sorted_modules,required_imports);
if (!module->is_root){
JaktInternal::Optional<ByteString> const dummy = generator.namespace_stack.pop();
}
if (!inside_namespace.is_empty()){
if (i != static_cast<size_t>(0ULL)){
output.appendff(ByteString::from_utf8_without_validation("#include \"{}\"\n"sv),header_name);
}
{
JaktInternal::ArrayIterator<Jakt::ids::ModuleId> _magic = ordered_imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId id = _magic_value.value();
{
if (id.id == static_cast<size_t>(0ULL)){
continue;
}
NonnullRefPtr<Jakt::types::Module> const module = generator.program->modules.operator[](id.id);
output.appendff(ByteString::from_utf8_without_validation("#include \"{}.h\"\n"sv),module->name);
}

}
}

output.append(StringView::from_string_literal("namespace Jakt {\n"sv));
output.append(inside_namespace.to_string());
output.append(StringView::from_string_literal("} // namespace Jakt\n"sv));
}
else {
output.clear();
}

result.set(impl_name,Tuple{output.to_string(), module->resolved_import_path});
}

}
}

{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(sorted_modules.size()),static_cast<size_t>(static_cast<size_t>(0ULL))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t idx = _magic_value.value();
{
size_t const i = sorted_modules.operator[](JaktInternal::checked_sub(idx,static_cast<size_t>(1ULL))).id;
NonnullRefPtr<Jakt::types::Module> const module = generator.program->modules.operator[](i);
ByteString const header_name = __jakt_format(StringView::from_string_literal("{}.h"sv),module->name);
ByteString const impl_name = __jakt_format(StringView::from_string_literal("{}_specializations.cpp"sv),module->name);
size_t const main_id = [&]() -> size_t { auto __jakt_enum_value = module->id.id;
if (__jakt_enum_value == static_cast<size_t>(1ULL)) {return static_cast<size_t>(1ULL);}else {return static_cast<size_t>(0ULL);} 
}();
Jakt::ids::ScopeId const scope_id = Jakt::ids::ScopeId(module->id,main_id);
NonnullRefPtr<Jakt::types::Scope> const scope = generator.program->get_scope(scope_id);
ByteStringBuilder code_output = ByteStringBuilder::create();
if (!module->is_root){
generator.namespace_stack.push(module->name);
}
JaktInternal::Set<Jakt::ids::ModuleId> required_imports = TRY((generator.capturing_modules(module,[scope](Jakt::codegen::CodeGenerator& gen, NonnullRefPtr<Jakt::types::Module> module, ByteStringBuilder& output) -> ErrorOr<void> {{
TRY((gen.codegen_namespace_specializations(scope,module,output)));
}
return {};
}
,code_output)));
JaktInternal::Optional<JaktInternal::Set<Jakt::ids::ModuleId>> __jakt_tmp380 = modules_in_header.get(i);
if (__jakt_tmp380.has_value()){
JaktInternal::Set<Jakt::ids::ModuleId> const already_included = __jakt_tmp380.value();
{
JaktInternal::SetIterator<Jakt::ids::ModuleId> _magic = already_included.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId imported_by_header = _magic_value.value();
{
required_imports.remove(imported_by_header);
}

}
}

}
JaktInternal::DynamicArray<Jakt::ids::ModuleId> const ordered_imports = Jakt::codegen::CodeGenerator::get_topologically_sorted_modules(sorted_modules,required_imports);
if (!module->is_root){
JaktInternal::Optional<ByteString> const dummy = generator.namespace_stack.pop();
}
if (!code_output.is_empty()){
output = ByteStringBuilder::create();
if (i != static_cast<size_t>(0ULL)){
output.appendff(ByteString::from_utf8_without_validation("#include \"{}\"\n"sv),header_name);
}
{
JaktInternal::ArrayIterator<Jakt::ids::ModuleId> _magic = ordered_imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId id = _magic_value.value();
{
if (id.id == static_cast<size_t>(0ULL)){
continue;
}
NonnullRefPtr<Jakt::types::Module> const module = generator.program->modules.operator[](id.id);
output.appendff(ByteString::from_utf8_without_validation("#include \"{}.h\"\n"sv),module->name);
}

}
}

output.append(StringView::from_string_literal("namespace Jakt {\n"sv));
output.append(code_output.to_string());
output.append(StringView::from_string_literal("} // namespace Jakt\n"sv));
}
else {
output.clear();
}

result.set(impl_name,Tuple{output.to_string(), module->resolved_import_path});
}

}
}

Jakt::jakt__path::Path const export_dir = MUST((compiler->exports_dir.absolute()));
Jakt::jakt__path::Path const binary_dir = MUST((compiler->binary_dir.absolute()));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> _magic = generator.program->exports.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> file__exported_types__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> const jakt__file__exported_types__ = file__exported_types__;
ByteString const file = jakt__file__exported_types__.template get<0>();
JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>> const exported_types = jakt__file__exported_types__.template get<1>();

JaktInternal::Set<Jakt::ids::ModuleId> used_modules = Set<Jakt::ids::ModuleId>::create_with_values({});
ByteStringBuilder cpp_code = ByteStringBuilder::create();
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>> _magic = exported_types.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>> type_id__unprefixed_name__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>> const jakt__type_id__unprefixed_name__ = type_id__unprefixed_name__;
Jakt::ids::TypeId const type_id = jakt__type_id__unprefixed_name__.template get<0>();
JaktInternal::DynamicArray<Jakt::parser::ParsedName> const unprefixed_name = jakt__type_id__unprefixed_name__.template get<1>();

used_modules.add(type_id.module);
bool const should_be_namespaced = unprefixed_name.size() > static_cast<size_t>(1ULL);
if (should_be_namespaced){
cpp_code.appendff(ByteString::from_utf8_without_validation("namespace {}"sv),unprefixed_name.operator[](static_cast<i64>(0LL)).name);
if (unprefixed_name.size() > static_cast<size_t>(2ULL)){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(JaktInternal::checked_sub(unprefixed_name.size(),static_cast<size_t>(1ULL)))};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
cpp_code.append(__jakt_format(StringView::from_string_literal("::{}"sv),unprefixed_name.operator[](i).name));
}

}
}

}
cpp_code.append_code_point(static_cast<u32>(U'{'));
}
ByteString const name = unprefixed_name.last().value().name;
ByteString const qualifier = TRY((generator.codegen_namespace_qualifier(generator.program->find_type_scope_id(type_id),generator.program->get_module(type_id.module)->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
cpp_code.appendff(ByteString::from_utf8_without_validation("using {} = {}{};"sv),name,qualifier,name);
if (should_be_namespaced){
cpp_code.append_code_point(static_cast<u32>(U'}'));
}
}

}
}

output.clear();
output.append(StringView::from_string_literal("#pragma once\n"sv));
JaktInternal::DynamicArray<Jakt::ids::ModuleId> const ordered_imports = Jakt::codegen::CodeGenerator::get_topologically_sorted_modules(sorted_modules,used_modules);
{
JaktInternal::ArrayIterator<Jakt::ids::ModuleId> _magic = ordered_imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::Module> const module = generator.program->modules.operator[](id.id);
Jakt::jakt__path::Path const module_path = binary_dir.join(__jakt_format(StringView::from_string_literal("{}.h"sv),module->name));
Jakt::jakt__path::Path const module_path_relative = module_path.relative_to(export_dir);
output.appendff(ByteString::from_utf8_without_validation("#include \"{}\"\n"sv),module_path_relative.to_string());
}

}
}

output.append(cpp_code.to_string());
exported_files.set(file,output.to_string());
}

}
}

return result;
}
}

JaktInternal::DynamicArray<Jakt::ids::ModuleId> Jakt::codegen::CodeGenerator::get_topologically_sorted_modules(JaktInternal::DynamicArray<Jakt::ids::ModuleId> const& all_sorted_modules,JaktInternal::Set<Jakt::ids::ModuleId> const& dependencies) {
{
JaktInternal::DynamicArray<Jakt::ids::ModuleId> deps = DynamicArray<Jakt::ids::ModuleId>::create_with({});
deps.ensure_capacity(dependencies.size());
{
JaktInternal::ArrayIterator<Jakt::ids::ModuleId> _magic = all_sorted_modules.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId id = _magic_value.value();
{
if (dependencies.contains(id)){
deps.push(id);
}
}

}
}

return deps;
}
}

ErrorOr<JaktInternal::Set<Jakt::ids::ModuleId>> Jakt::codegen::CodeGenerator::capturing_modules(NonnullRefPtr<Jakt::types::Module> const module,Function<ErrorOr<void>(Jakt::codegen::CodeGenerator&, NonnullRefPtr<Jakt::types::Module>, ByteStringBuilder&)> const& gen,ByteStringBuilder& output) {
{
this->used_modules = Set<Jakt::ids::ModuleId>::create_with_values({});
this->used_modules.ensure_capacity(module->imports.size());
{
JaktInternal::ArrayIterator<Jakt::ids::ModuleId> _magic = module->imports.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ModuleId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ModuleId id = _magic_value.value();
{
this->used_modules.add(id);
}

}
}

this->deferred_output.clear();
TRY((gen(*this,module,output)));
output.append(this->deferred_output.to_string());
this->deferred_output.clear();
return this->used_modules;
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::postorder_traversal(Jakt::ids::TypeId const type_id,JaktInternal::Set<Jakt::ids::TypeId> visited,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const dependency_graph,JaktInternal::DynamicArray<Jakt::ids::TypeId> output) const {
{
if (visited.contains(type_id)){
return {};
}
visited.add(type_id);
if (dependency_graph.contains(type_id)){
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = dependency_graph.get(type_id).value().iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId dependency = _magic_value.value();
{
TRY((this->postorder_traversal(dependency,visited,dependency_graph,output)));
}

}
}

}
output.push(type_id);
}
return {};
}

ErrorOr<JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> Jakt::codegen::CodeGenerator::produce_codegen_dependency_graph(NonnullRefPtr<Jakt::types::Scope> const scope) const {
{
JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> dependency_graph = Dictionary<Jakt::ids::TypeId, JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with_entries({});
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::TypeId> _magic = scope->types.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::TypeId> type_ = _magic_value.value();
{
dependency_graph.set(type_.template get<1>(),this->extract_dependencies_from(type_.template get<1>(),dependency_graph,true));
}

}
}

return dependency_graph;
}
}

JaktInternal::DynamicArray<Jakt::ids::TypeId> Jakt::codegen::CodeGenerator::extract_dependencies_from(Jakt::ids::TypeId const type_id,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const dependency_graph,bool const top_level) const {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> dependencies = DynamicArray<Jakt::ids::TypeId>::create_with({});
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->program->get_type(type_id);
if ((!type_->is_boxed(this->program)) && dependency_graph.contains(type_id)){
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = dependency_graph.get(type_id).value().iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId dependency = _magic_value.value();
{
dependencies.push(dependency);
}

}
}

return dependencies;
}
JaktInternal::DynamicArray<Jakt::ids::TypeId> const inner_dependencies = [&]() -> JaktInternal::DynamicArray<Jakt::ids::TypeId> { auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
return this->extract_dependencies_from_enum(enum_id,dependency_graph,top_level);};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return this->extract_dependencies_from_enum(id,dependency_graph,top_level);};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return this->extract_dependencies_from_struct(id,dependency_graph,top_level,DynamicArray<Jakt::ids::TypeId>::create_with({}));};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return this->extract_dependencies_from_struct(id,dependency_graph,top_level,args);};/*case end*/
default:return DynamicArray<Jakt::ids::TypeId>::create_with({});}/*switch end*/
 
}();
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = inner_dependencies.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId dependency = _magic_value.value();
{
dependencies.push(dependency);
}

}
}

return dependencies;
}
}

JaktInternal::DynamicArray<Jakt::ids::TypeId> Jakt::codegen::CodeGenerator::extract_dependencies_from_enum(Jakt::ids::EnumId const enum_id,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const dependency_graph,bool const top_level) const {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> dependencies = DynamicArray<Jakt::ids::TypeId>::create_with({});
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_id);
if (enum_.definition_linkage.__jakt_init_index() == 1 /* External */){
return dependencies;
}
if (enum_.is_boxed && (!top_level)){
return dependencies;
}
dependencies.push(enum_.type_id);
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(enum_.underlying_type_id,Jakt::types::unknown_type_id())){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const inner_dependencies = this->extract_dependencies_from(enum_.underlying_type_id,dependency_graph,false);
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = inner_dependencies.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId dependency = _magic_value.value();
{
dependencies.push(dependency);
}

}
}

}
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
{auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const inner_dependencies = this->extract_dependencies_from(type_id,dependency_graph,false);
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = inner_dependencies.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId dependency = _magic_value.value();
{
dependencies.push(dependency);
}

}
}

}
goto __jakt_label_156;};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::VarId field = _magic_value.value();
{
Jakt::ids::TypeId const type_id = this->program->get_variable(field)->type_id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const inner_dependencies = this->extract_dependencies_from(type_id,dependency_graph,false);
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = inner_dependencies.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId dependency = _magic_value.value();
{
dependencies.push(dependency);
}

}
}

}

}
}

}
goto __jakt_label_156;};/*case end*/
default:{
}
goto __jakt_label_156;}/*switch end*/
break;}goto __jakt_label_156; __jakt_label_156:;;
}

}
}

return dependencies;
}
}

JaktInternal::DynamicArray<Jakt::ids::TypeId> Jakt::codegen::CodeGenerator::extract_dependencies_from_struct(Jakt::ids::StructId const struct_id,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const dependency_graph,bool const top_level,JaktInternal::DynamicArray<Jakt::ids::TypeId> const args) const {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> dependencies = DynamicArray<Jakt::ids::TypeId>::create_with({});
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(struct_id);
if ((struct_.definition_linkage.__jakt_init_index() == 1 /* External */) && [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(struct_.name,ByteString::from_utf8_without_validation("Optional"sv))){
return dependencies;
}
if ((struct_.record_type.__jakt_init_index() == 1 /* Class */) && (!top_level)){
return dependencies;
}
if (!args.is_empty()){
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId inner_type = _magic_value.value();
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const inner_dependencies = [&]() -> JaktInternal::DynamicArray<Jakt::ids::TypeId> { auto&& __jakt_match_variant = *this->program->get_type(inner_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */:case 23 /* Struct */:return this->extract_dependencies_from(inner_type,dependency_graph,false);default:return DynamicArray<Jakt::ids::TypeId>::create_with({});}/*switch end*/
 
}();
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = inner_dependencies.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId dependency = _magic_value.value();
{
dependencies.push(dependency);
}

}
}

}

}
}

}
JaktInternal::Optional<Jakt::ids::StructId> super_struct_id = struct_.super_struct_id;
while (super_struct_id.has_value()){
Jakt::types::CheckedStruct const super_struct = this->program->get_struct(super_struct_id.value());
JaktInternal::DynamicArray<Jakt::ids::TypeId> const super_dependencies = this->extract_dependencies_from_struct(super_struct_id.value(),dependency_graph,true,DynamicArray<Jakt::ids::TypeId>::create_with({}));
dependencies.push_values(super_dependencies);
super_struct_id = super_struct.super_struct_id;
}
dependencies.push(struct_.type_id);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = struct_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
Jakt::ids::TypeId const type_id = this->program->get_variable(field->variable_id)->type_id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const inner_dependencies = this->extract_dependencies_from(type_id,dependency_graph,false);
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = inner_dependencies.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId dependency = _magic_value.value();
{
dependencies.push(dependency);
}

}
}

}

}
}

return dependencies;
}
}

bool Jakt::codegen::CodeGenerator::is_full_respecialization(JaktInternal::DynamicArray<Jakt::ids::TypeId> const type_args) const {
{
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = type_args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId type_id = _magic_value.value();
{
if (this->program->get_type(type_id)->__jakt_init_index() == 18 /* TypeVariable */){
return false;
}
}

}
}

return true;
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_namespace_specialization(Jakt::ids::FunctionId const function_id,JaktInternal::Optional<Jakt::ids::TypeId> const containing_struct,NonnullRefPtr<Jakt::types::Scope> const scope,NonnullRefPtr<Jakt::types::Module> const current_module,bool const define_pass,ByteStringBuilder& output) {
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
if (!function->function_scope_id.module_id.equals(current_module->id)){
return {};
}
if (function->is_comptime){
return {};
}
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function = this->current_function;
this->current_function = function;
ScopeGuard __jakt_var_114([&] {
this->current_function = previous_function;
});
if ((((function->linkage.__jakt_init_index() == 1 /* External */) || (function->type.__jakt_init_index() == 3 /* ImplicitConstructor */)) || (function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */)) || (function->type.__jakt_init_index() == 2 /* Destructor */)){
return {};
}
if (function->generics->params.is_empty() || (!function->specialization_index.has_value())){
return {};
}
if (containing_struct.has_value() && (![&]() -> bool { auto&& __jakt_match_variant = *this->program->get_type(containing_struct.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
return this->program->get_struct(struct_id).generic_parameters.is_empty();};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& struct_id = __jakt_match_value.value;
return this->program->get_enum(struct_id).generic_parameters.is_empty();};/*case end*/
default:return false;}/*switch end*/
 
}())){
return {};
}
bool const is_full_respecialization = this->is_full_respecialization(function->generics->specializations.operator[](function->specialization_index.value()));
if (define_pass && is_full_respecialization){
output.append(StringView::from_string_literal("template<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = function->generics->specializations.operator[](function->specialization_index.value()).iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp381 = this->program->get_type(arg);
if (__jakt_tmp381->__jakt_init_index() == 18 /* TypeVariable */){
ByteString const name = __jakt_tmp381->as.TypeVariable.name;
if (first){
first = false;
}
else {
output.append(StringView::from_string_literal(", "sv));
}

output.appendff(ByteString::from_utf8_without_validation("typename {}"sv),name);
}
}

}
}

output.append(StringView::from_string_literal(">\n"sv));
TRY((this->codegen_function_in_namespace(function,containing_struct,false,true,function->generics->specializations.operator[](function->specialization_index.value()),output)));
}
else if (is_full_respecialization){
JaktInternal::DynamicArray<ByteString> args = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = function->generics->specializations.operator[](function->specialization_index.value()).iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
args.push(TRY((this->codegen_type(arg))));
}

}
}

output.appendff(ByteString::from_utf8_without_validation("\n/* specialisation {} of function {}: {} */"sv),function->specialization_index.value(),function->name,args);
output.append(StringView::from_string_literal("\ntemplate<> "sv));
if (function->return_type_id.equals(Jakt::types::never_type_id())){
output.append(StringView::from_string_literal("[[noreturn]] "sv));
}
output.append(TRY(([&]() -> ErrorOr<ByteString> { auto __jakt_enum_value = function->can_throw;
if (__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("ErrorOr<{}>"sv),TRY((this->codegen_type(function->return_type_id))));}else if (!__jakt_enum_value) {return this->codegen_type(function->return_type_id);}VERIFY_NOT_REACHED();
 
}())));
output.append(StringView::from_string_literal(" "sv));
ByteString const qualifier = TRY(([&]() -> ErrorOr<ByteString> { auto __jakt_enum_value = containing_struct.has_value();
if (__jakt_enum_value) {return this->codegen_type_possibly_as_namespace(containing_struct.value(),true);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}VERIFY_NOT_REACHED();
 
}()));
if (!qualifier.is_empty()){
output.append(qualifier);
output.append(StringView::from_string_literal("::"sv));
}
output.append(function->name_for_codegen().as_name_for_definition());
output.append(StringView::from_string_literal("<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = function->generics->specializations.operator[](function->specialization_index.value()).iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId type_id = _magic_value.value();
{
if (first){
first = false;
}
else {
output.append(StringView::from_string_literal(", "sv));
}

output.append(TRY((this->codegen_type(type_id))));
}

}
}

output.append(StringView::from_string_literal(">("sv));
first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = param.variable;
if (variable->name == ByteString::from_utf8_without_validation("this"sv)){
continue;
}
if (!first){
output.append(StringView::from_string_literal(","sv));
}
else {
first = false;
}

NonnullRefPtr<typename Jakt::types::Type> const variable_type = this->program->get_type(variable->type_id);
output.append(TRY((this->codegen_type(variable->type_id))));
output.append(StringView::from_string_literal(" "sv));
if ((!variable->is_mutable) && (!((variable_type->__jakt_init_index() == 27 /* Reference */) || (variable_type->__jakt_init_index() == 28 /* MutableReference */)))){
output.append(StringView::from_string_literal("const "sv));
}
output.append(variable->name_for_codegen().as_name_for_definition());
}

}
}

output.append(StringView::from_string_literal(")"sv));
if ((!function->is_static()) && (!function->is_mutating())){
output.append(StringView::from_string_literal(" const"sv));
}
output.append(StringView::from_string_literal(";\n"sv));
}
else {
output.appendff(ByteString::from_utf8_without_validation("\n/* specialisation {} of function {} omitted, not fully specialized: {} */\n"sv),function->specialization_index.value(),function->name,function->generics->specializations.operator[](function->specialization_index.value()));
}

}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_namespace_specializations(NonnullRefPtr<Jakt::types::Scope> const scope,NonnullRefPtr<Jakt::types::Module> const current_module,ByteStringBuilder& output) {
{
if (scope->alias_path.has_value() || scope->import_path_if_extern.has_value()){
return {};
}
JaktInternal::Set<Jakt::ids::TypeId> seen_types = Set<Jakt::ids::TypeId>::create_with_values({});
{
JaktInternal::ArrayIterator<bool> _magic = DynamicArray<bool>::create_with({false, true}).iterator();
for (;;){
JaktInternal::Optional<bool> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
bool define_pass = _magic_value.value();
{
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
TRY((this->codegen_namespace_specialization(function_id,JaktInternal::OptionalNone(),scope,current_module,define_pass,output)));
}

}
}

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

if (!struct_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(struct_id);
if (seen_types.contains(struct_.type_id)){
continue;
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(struct_.scope_id);
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
TRY((this->codegen_namespace_specialization(function_id,struct_.type_id,scope,current_module,define_pass,output)));
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
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::EnumId> _magic = scope->enums.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::EnumId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> ___enum_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> const jakt_____enum_id__ = ___enum_id__;
ByteString const _ = jakt_____enum_id__.template get<0>();
Jakt::ids::EnumId const enum_id = jakt_____enum_id__.template get<1>();

if (!enum_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_id);
if (seen_types.contains(enum_.type_id)){
continue;
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(enum_.scope_id);
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
TRY((this->codegen_namespace_specialization(function_id,enum_.type_id,scope,current_module,define_pass,output)));
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
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child_scope_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::Scope> const child_scope = this->program->get_scope(child_scope_id);
JaktInternal::Optional<ByteString> const name = child_scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_definition(); });
if (name.has_value()){
this->namespace_stack.push(name.value());
TRY((this->codegen_namespace_specializations(child_scope,current_module,output)));
JaktInternal::Optional<ByteString> const dummy = this->namespace_stack.pop();
}
}

}
}

JaktInternal::Optional<ByteString> const name = scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_definition(); });
if (name.has_value() && (!output.is_empty())){
ByteString const inside_namespace = output.to_string();
output.clear();
output.appendff(ByteString::from_utf8_without_validation("namespace {} {{\n"sv),name.value());
output.append(inside_namespace);
output.append(StringView::from_string_literal("}\n"sv));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_namespace_forward(NonnullRefPtr<Jakt::types::Scope> const scope,NonnullRefPtr<Jakt::types::Module> const current_module,ByteStringBuilder& output) {
{
if (scope->alias_path.has_value() || scope->import_path_if_extern.has_value()){
return {};
}
ByteStringBuilder inside_namespace = ByteStringBuilder::create();
JaktInternal::Set<Jakt::ids::TypeId> seen_types = Set<Jakt::ids::TypeId>::create_with_values({});
JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const dependency_graph = TRY((this->produce_codegen_dependency_graph(scope)));
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> _magic = dependency_graph.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::ids::TypeId>> entry = _magic_value.value();
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const traversal = DynamicArray<Jakt::ids::TypeId>::create_with({});
TRY((this->postorder_traversal(entry.template get<0>(),seen_types,dependency_graph,traversal)));
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = traversal.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId type_id = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->program->get_type(type_id);
{auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
if (!enum_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_id);
TRY((this->codegen_enum(enum_,inside_namespace)));
}
goto __jakt_label_157;};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
if (!struct_id.module.equals(current_module->id)){
continue;
}
TRY((this->codegen_struct(this->program->get_struct(struct_id),inside_namespace)));
}
goto __jakt_label_157;};/*case end*/
case 26 /* Trait */:{
}
goto __jakt_label_157;default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Unexpected type in dependency graph: {}"sv),type_));
}
goto __jakt_label_157;}/*switch end*/
break;}goto __jakt_label_157; __jakt_label_157:;;
seen_types.add(type_id);
}

}
}

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

if (!struct_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(struct_id);
if (seen_types.contains(struct_.type_id)){
continue;
}
TRY((this->codegen_struct(struct_,inside_namespace)));
output.append(StringView::from_string_literal("\n"sv));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::EnumId> _magic = scope->enums.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::EnumId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> ___enum_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> const jakt_____enum_id__ = ___enum_id__;
ByteString const _ = jakt_____enum_id__.template get<0>();
Jakt::ids::EnumId const enum_id = jakt_____enum_id__.template get<1>();

if (!enum_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_id);
if (seen_types.contains(enum_.type_id)){
continue;
}
TRY((this->codegen_enum(enum_,inside_namespace)));
output.append(StringView::from_string_literal("\n"sv));
}

}
}

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
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
if (!function->function_scope_id.module_id.equals(current_module->id)){
continue;
}
if (function->is_comptime){
continue;
}
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function = this->current_function;
this->current_function = function;
ScopeGuard __jakt_var_115([&] {
this->current_function = previous_function;
});
if ((((function->linkage.__jakt_init_index() == 1 /* External */) || (function->type.__jakt_init_index() == 3 /* ImplicitConstructor */)) || (function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */)) || (function->type.__jakt_init_index() == 2 /* Destructor */)){
continue;
}
if (function->generics->params.is_empty()){
continue;
}
if (!function->specialization_index.has_value()){
TRY((this->codegen_function_predecl(function,false,true,inside_namespace)));
}
}

}
}

}

}
}

{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child_scope_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::Scope> const child_scope = this->program->get_scope(child_scope_id);
JaktInternal::Optional<ByteString> const name = child_scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_definition(); });
if (name.has_value()){
this->namespace_stack.push(name.value());
TRY((this->codegen_namespace_forward(child_scope,current_module,inside_namespace)));
JaktInternal::Optional<ByteString> const dummy = this->namespace_stack.pop();
}
}

}
}

if (inside_namespace.length() != static_cast<size_t>(0ULL)){
JaktInternal::Optional<ByteString> const name = scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_definition(); });
if (name.has_value()){
output.append((ByteString::from_utf8_without_validation("namespace "sv) + name.value()) + ByteString::from_utf8_without_validation(" {\n"sv));
}
output.append(inside_namespace.to_string());
if (name.has_value()){
output.append(StringView::from_string_literal("}\n"sv));
}
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_namespace(NonnullRefPtr<Jakt::types::Scope> const scope,NonnullRefPtr<Jakt::types::Module> const current_module,ByteStringBuilder& output) {
{
if (scope->alias_path.has_value() || scope->import_path_if_extern.has_value()){
return {};
}
ByteStringBuilder inside_namespace = ByteStringBuilder::create();
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
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
if (!function->function_scope_id.module_id.equals(current_module->id)){
continue;
}
if (function->is_comptime){
continue;
}
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function = this->current_function;
this->current_function = function;
ScopeGuard __jakt_var_116([&] {
this->current_function = previous_function;
});
if ((((function->linkage.__jakt_init_index() == 1 /* External */) || (function->type.__jakt_init_index() == 3 /* ImplicitConstructor */)) || (function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */)) || (function->type.__jakt_init_index() == 2 /* Destructor */)){
continue;
}
if (function->generics->params.is_empty()){
TRY((this->codegen_function(function,false,inside_namespace)));
inside_namespace.append(StringView::from_string_literal("\n"sv));
}
}

}
}

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

if (!struct_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(struct_id);
if (struct_.definition_linkage.__jakt_init_index() == 1 /* External */){
continue;
}
if (!struct_.generic_parameters.is_empty()){
continue;
}
TRY((this->codegen_debug_description_getter(struct_,false,inside_namespace)));
NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(struct_.scope_id);
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
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
if (function->force_inline.__jakt_init_index() == 1 /* MakeDefinitionAvailable */){
continue;
}
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function = this->current_function;
this->current_function = function;
ScopeGuard __jakt_var_117([&] {
this->current_function = previous_function;
});
if (function->type.__jakt_init_index() == 3 /* ImplicitConstructor */){
TRY((this->codegen_constructor(function,false,inside_namespace)));
inside_namespace.append(StringView::from_string_literal("\n"sv));
}
else if (function->type.__jakt_init_index() == 2 /* Destructor */){
TRY((this->codegen_destructor(struct_,function,false,inside_namespace)));
inside_namespace.append(StringView::from_string_literal("\n"sv));
}
else if ((!(function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */)) && ((!function->is_comptime) && function->generics->params.is_empty())){
TRY((this->codegen_function_in_namespace(function,struct_.type_id,false,false,JaktInternal::OptionalNone(),inside_namespace)));
inside_namespace.append(StringView::from_string_literal("\n"sv));
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
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::EnumId> _magic = scope->enums.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::EnumId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> ___enum_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> const jakt_____enum_id__ = ___enum_id__;
ByteString const _ = jakt_____enum_id__.template get<0>();
Jakt::ids::EnumId const enum_id = jakt_____enum_id__.template get<1>();

if (!enum_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_id);
if (enum_.definition_linkage.__jakt_init_index() == 1 /* External */){
continue;
}
if (!enum_.generic_parameters.is_empty()){
continue;
}
if (enum_.underlying_type_id.equals(Jakt::types::void_type_id())){
TRY((this->codegen_enum_debug_description_getter(enum_,false,inside_namespace)));
JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>> const common_fields_variant_field_list_ = TRY((this->codegen_enum_field_lists(enum_)));
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields = common_fields_variant_field_list_.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const variant_field_list = common_fields_variant_field_list_.template get<1>();

this->codegen_enum_constructors(enum_,false,JaktInternal::OptionalNone(),variant_field_list,common_fields,inside_namespace);
inside_namespace.appendff(ByteString::from_utf8_without_validation("{0}::~{0}()"sv),enum_.name);
this->codegen_enum_destructor_body(enum_,inside_namespace);
inside_namespace.appendff(ByteString::from_utf8_without_validation("void {0}::__jakt_destroy_variant() {{\n"sv),enum_.name);
this->codegen_enum_destroy_variant(enum_,inside_namespace);
inside_namespace.append(StringView::from_string_literal("}\n"sv));
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(enum_.scope_id);
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
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function = this->current_function;
this->current_function = function;
ScopeGuard __jakt_var_118([&] {
this->current_function = previous_function;
});
if ((!(function->type.__jakt_init_index() == 3 /* ImplicitConstructor */)) && ((!(function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */)) && ((!(function->type.__jakt_init_index() == 2 /* Destructor */)) && ((!function->is_comptime) && function->generics->params.is_empty())))){
TRY((this->codegen_function_in_namespace(function,enum_.type_id,false,false,JaktInternal::OptionalNone(),inside_namespace)));
inside_namespace.append(StringView::from_string_literal("\n"sv));
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
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child_scope_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::Scope> const child_scope = this->program->get_scope(child_scope_id);
JaktInternal::Optional<ByteString> const name = child_scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_definition(); });
if (name.has_value()){
this->namespace_stack.push(name.value());
TRY((this->codegen_namespace(child_scope,current_module,inside_namespace)));
JaktInternal::Optional<ByteString> const dummy = this->namespace_stack.pop();
}
}

}
}

if (!inside_namespace.is_empty()){
JaktInternal::Optional<ByteString> const name = scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_definition(); });
if (name.has_value()){
output.appendff(ByteString::from_utf8_without_validation("namespace {} {{\n"sv),name.value());
output.append(inside_namespace.to_string());
output.append(StringView::from_string_literal("}\n"sv));
}
else {
output.append(inside_namespace.to_string());
}

}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_namespace_predecl(NonnullRefPtr<Jakt::types::Scope> const scope,NonnullRefPtr<Jakt::types::Module> const current_module,ByteStringBuilder& output) {
{
if (scope->alias_path.has_value() || scope->import_path_if_extern.has_value()){
return {};
}
JaktInternal::Optional<ByteString> const name = scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_definition(); });
if (name.has_value()){
output.append(StringView::from_string_literal("namespace "sv));
output.append(name.value());
output.append(StringView::from_string_literal(" {\n"sv));
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

if (!struct_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(struct_id);
TRY((this->codegen_struct_predecl(struct_,output)));
output.append(StringView::from_string_literal("\n"sv));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::EnumId> _magic = scope->enums.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::EnumId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> ___enum_id__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> const jakt_____enum_id__ = ___enum_id__;
ByteString const _ = jakt_____enum_id__.template get<0>();
Jakt::ids::EnumId const enum_id = jakt_____enum_id__.template get<1>();

if (!enum_id.module.equals(current_module->id)){
continue;
}
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_id);
TRY((this->codegen_enum_predecl(enum_,output)));
output.append(StringView::from_string_literal("\n"sv));
}

}
}

{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = scope->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child = _magic_value.value();
{
TRY((this->codegen_namespace_predecl(this->program->get_scope(child),current_module,output)));
}

}
}

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
if (!function_id.module.equals(current_module->id)){
continue;
}
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
if (function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */){
continue;
}
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function_id = this->current_function;
this->current_function = static_cast<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>>>(function);
ScopeGuard __jakt_var_119([&] {
this->current_function = previous_function_id;
});
if ((!(function->type.__jakt_init_index() == 3 /* ImplicitConstructor */)) && ((!(function->type.__jakt_init_index() == 2 /* Destructor */)) && ([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(function->name_for_codegen().as_name_for_use(),ByteString::from_utf8_without_validation("main"sv)) && function->generics->params.is_empty()))){
TRY((this->codegen_function_predecl(function,false,false,output)));
output.append(StringView::from_string_literal("\n"sv));
}
}

}
}

}

}
}

if (name.has_value()){
output.append(StringView::from_string_literal("}\n"sv));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<Jakt::types::FunctionGenericParameter> const parameters,JaktInternal::DynamicArray<ByteString>& names,ByteStringBuilder& output) {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> ids = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::FunctionGenericParameter> _magic = parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::FunctionGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::FunctionGenericParameter parameter = _magic_value.value();
{
ids.push(parameter.checked_parameter.type_id);
}

}
}

TRY((this->codegen_template_parameter_names(ids,names,output)));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<Jakt::types::FunctionGenericParameter> const parameters,ByteStringBuilder& output) {
{
JaktInternal::DynamicArray<ByteString> names = DynamicArray<ByteString>::create_with({});
TRY((this->codegen_template_parameter_names(parameters,names,output))); return {};
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const parameters,JaktInternal::DynamicArray<ByteString>& names,ByteStringBuilder& output) {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> ids = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter parameter = _magic_value.value();
{
ids.push(parameter.type_id);
}

}
}

TRY((this->codegen_template_parameter_names(ids,names,output))); return {};
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const parameters,ByteStringBuilder& output) {
{
JaktInternal::DynamicArray<ByteString> names = DynamicArray<ByteString>::create_with({});
TRY((this->codegen_template_parameter_names(parameters,names,output))); return {};
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_template_parameter_names(JaktInternal::DynamicArray<Jakt::ids::TypeId> const parameters,JaktInternal::DynamicArray<ByteString>& names,ByteStringBuilder& output) {
{
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId id = _magic_value.value();
{
if (first){
first = false;
}
else {
output.append(StringView::from_string_literal(","sv));
}

NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp382 = this->program->get_type(id);
if (__jakt_tmp382->__jakt_init_index() == 18 /* TypeVariable */){
bool const is_value = __jakt_tmp382->as.TypeVariable.is_value;
if (is_value){
output.append(StringView::from_string_literal("auto "sv));
}
else {
output.append(StringView::from_string_literal("typename "sv));
}

}
else {
output.append(StringView::from_string_literal("typename "sv));
}

ByteString const name = TRY((this->codegen_type(id)));
output.append(name);
names.push(name);
}

}
}

}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_function_generic_parameters(NonnullRefPtr<Jakt::types::CheckedFunction> const function,ByteStringBuilder& output) {
{
if (!function->generics->params.is_empty()){
output.append(StringView::from_string_literal("template <"sv));
TRY((this->codegen_template_parameter_names(function->generics->params,output)));
output.append(StringView::from_string_literal(">\n"sv));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_function_predecl(NonnullRefPtr<Jakt::types::CheckedFunction> const function,bool const as_method,bool const allow_generics,ByteStringBuilder& output) {
{
if ((allow_generics || (!function->generics->params.is_empty())) && (function->linkage.__jakt_init_index() == 1 /* External */)){
return {};
}
if (function->is_comptime){
return {};
}
if (function->force_inline.__jakt_init_index() == 2 /* ForceInline */){
return {};
}
if (function->type.__jakt_init_index() == 3 /* ImplicitConstructor */){
return {};
}
if ((function->linkage.__jakt_init_index() == 1 /* External */) && (!as_method)){
output.append(StringView::from_string_literal("extern "sv));
}
TRY((this->codegen_function_generic_parameters(function,output)));
if (function->return_type_id.equals(Jakt::types::never_type_id())){
output.append(StringView::from_string_literal("[[noreturn]] "sv));
}
if (function->name_for_codegen().as_name_for_definition() == ByteString::from_utf8_without_validation("main"sv)){
output.append(StringView::from_string_literal("ErrorOr<int>"sv));
}
else {
if (as_method && function->is_static()){
output.append(StringView::from_string_literal("static "sv));
}
if (function->is_virtual){
output.append(StringView::from_string_literal("virtual "sv));
}
if ((!(function->type.__jakt_init_index() == 2 /* Destructor */)) && (!(function->type.__jakt_init_index() == 1 /* Constructor */))){
ByteString const naked_return_type = TRY((this->codegen_type(function->return_type_id)));
ByteString const return_type = [&]() -> ByteString { auto __jakt_enum_value = function->can_throw;
if (__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("ErrorOr<{}>"sv),naked_return_type);}else if (!__jakt_enum_value) {return naked_return_type;}VERIFY_NOT_REACHED();
 
}();
output.append(return_type);
}
}

output.append(StringView::from_string_literal(" "sv));
output.append(function->name_for_codegen().as_name_for_definition());
output.append(StringView::from_string_literal("("sv));
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
if (first && (param.variable->name == ByteString::from_utf8_without_validation("this"sv))){
continue;
}
if (first){
first = false;
}
else {
output.append(StringView::from_string_literal(", "sv));
}

NonnullRefPtr<typename Jakt::types::Type> const param_type = this->program->get_type(param.variable->type_id);
output.append(TRY((this->codegen_type(param.variable->type_id))));
output.append(StringView::from_string_literal(" "sv));
if ((!param.variable->is_mutable) && (!((param_type->__jakt_init_index() == 27 /* Reference */) || (param_type->__jakt_init_index() == 28 /* MutableReference */)))){
output.append(StringView::from_string_literal("const "sv));
}
output.append(param.variable->name_for_codegen().as_name_for_definition());
}

}
}

output.append(StringView::from_string_literal(")"sv));
if ((!function->is_static()) && (!function->is_mutating())){
output.append(StringView::from_string_literal(" const"sv));
}
if (function->is_override){
output.append(StringView::from_string_literal(" override"sv));
}
output.append(StringView::from_string_literal(";\n"sv));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_struct_predecl(Jakt::types::CheckedStruct const struct_,ByteStringBuilder& output) {
{
if (struct_.definition_linkage.__jakt_init_index() == 1 /* External */){
return {};
}
if (!struct_.generic_parameters.is_empty()){
output.append(StringView::from_string_literal("template <"sv));
TRY((this->codegen_template_parameter_names(struct_.generic_parameters,output)));
output.append(StringView::from_string_literal(">"sv));
}
output.append([&]() -> StringView { auto&& __jakt_match_variant = struct_.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */:return StringView::from_string_literal("class "sv);case 0 /* Struct */:return StringView::from_string_literal("struct "sv);default:return StringView::from_string_literal(""sv);}/*switch end*/
 
}());
output.append(struct_.name_for_codegen().as_name_for_definition());
output.append(StringView::from_string_literal(";"sv));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_struct(Jakt::types::CheckedStruct const struct_,ByteStringBuilder& output) {
{
if (struct_.definition_linkage.__jakt_init_index() == 1 /* External */){
return {};
}
bool struct_is_generic = false;
JaktInternal::DynamicArray<ByteString> generic_parameter_names = DynamicArray<ByteString>::create_with({});
ByteStringBuilder template_parameters_builder = ByteStringBuilder::create();
ByteString template_parameters = ByteString::from_utf8_without_validation(""sv);
if (!struct_.generic_parameters.is_empty()){
struct_is_generic = true;
TRY((this->codegen_template_parameter_names(struct_.generic_parameters,generic_parameter_names,template_parameters_builder)));
template_parameters = template_parameters_builder.to_string();
output.appendff(ByteString::from_utf8_without_validation("template <{}>"sv),template_parameters);
}
{auto&& __jakt_match_variant = struct_.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */:{
ByteString class_name_with_generics = ByteString::from_utf8_without_validation(""sv);
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,struct_.name_for_codegen().as_name_for_definition());
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = struct_.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter generic_parameter = _magic_value.value();
{
if (!first){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation(", "sv));
}
else {
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation("<"sv));
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,TRY((this->codegen_type(generic_parameter.type_id))));
}

}
}

if (!struct_.generic_parameters.is_empty()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation(">"sv));
}
output.appendff(ByteString::from_utf8_without_validation("class {} :"sv),struct_.name_for_codegen().as_name_for_definition());
if (struct_.super_struct_id.has_value()){
output.appendff(ByteString::from_utf8_without_validation("public {}"sv),TRY((this->codegen_struct_type(struct_.super_struct_id.value(),true))));
if (!(this->program->get_struct(struct_.super_struct_id.value()).record_type.__jakt_init_index() == 1 /* Class */)){
output.appendff(ByteString::from_utf8_without_validation(", public RefCounted<{}>, public Weakable<{}>"sv),class_name_with_generics,class_name_with_generics);
}
}
else {
output.appendff(ByteString::from_utf8_without_validation("public RefCounted<{}>, public Weakable<{}> "sv),class_name_with_generics,class_name_with_generics);
}

output.append(StringView::from_string_literal("{\n"sv));
NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(struct_.scope_id);
bool has_destructor = false;
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = scope->functions.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> ___function_ids__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const jakt_____function_ids__ = ___function_ids__;
ByteString const _ = jakt_____function_ids__.template get<0>();
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const function_ids = jakt_____function_ids__.template get<1>();

{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = function_ids.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId function_id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
if (function->type.__jakt_init_index() == 2 /* Destructor */){
has_destructor = true;
}
}

}
}

}

}
}

if (!has_destructor){
output.append(StringView::from_string_literal("  public:\n"sv));
output.appendff(ByteString::from_utf8_without_validation("virtual ~{}() = default;\n"sv),struct_.name_for_codegen().as_name_for_definition());
}
}
goto __jakt_label_158;case 0 /* Struct */:{
output.appendff(ByteString::from_utf8_without_validation("struct {}"sv),struct_.name_for_codegen().as_name_for_definition());
if (struct_.super_struct_id.has_value()){
output.appendff(ByteString::from_utf8_without_validation(": public {}"sv),TRY((this->codegen_struct_type(struct_.super_struct_id.value(),true))));
}
output.append(StringView::from_string_literal(" {\n"sv));
output.append(StringView::from_string_literal("  public:\n"sv));
}
goto __jakt_label_158;case 3 /* SumEnum */:{
Jakt::utility::todo(ByteString::from_utf8_without_validation("codegen_struct SumEnum"sv));
}
goto __jakt_label_158;case 2 /* ValueEnum */:{
Jakt::utility::todo(ByteString::from_utf8_without_validation("codegen_struct ValueEnum"sv));
}
goto __jakt_label_158;default:{
}
goto __jakt_label_158;}/*switch end*/
}goto __jakt_label_158; __jakt_label_158:;;
Function<ErrorOr<void>(Jakt::types::CheckedVisibility)> const set_access_level = [&output](Jakt::types::CheckedVisibility visibility) -> ErrorOr<void> {{
{auto&& __jakt_match_variant = visibility;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Restricted */:case 0 /* Public */:{
output.append(StringView::from_string_literal("public: "sv));
}
return {};case 1 /* Private */:{
output.append(StringView::from_string_literal("private: "sv));
}
return {};default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
return {};
}
;
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = struct_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->program->get_variable(field->variable_id);
TRY((set_access_level(variable->visibility)));
output.append(TRY((this->codegen_type(variable->type_id))));
output.append(StringView::from_string_literal(" "sv));
output.append(variable->name_for_codegen().as_name_for_definition());
output.append(StringView::from_string_literal(";"sv));
}

}
}

NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(struct_.scope_id);
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
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function_id = this->current_function;
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
TRY((set_access_level(function->visibility)));
this->current_function = static_cast<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>>>(function);
ScopeGuard __jakt_var_120([&] {
this->current_function = previous_function_id;
});
if (function->type.__jakt_init_index() == 2 /* Destructor */){
if (struct_.generic_parameters.is_empty()){
output.append(TRY((this->codegen_destructor_predecl(struct_))));
}
else {
TRY((this->codegen_destructor(struct_,function,true,output)));
}

output.append(StringView::from_string_literal("\n"sv));
}
else if (function->type.__jakt_init_index() == 3 /* ImplicitConstructor */){
if (struct_.generic_parameters.is_empty()){
TRY((this->codegen_constructor_predecl(function,output)));
}
else {
TRY((this->codegen_constructor(function,true,output)));
}

output.append(StringView::from_string_literal("\n"sv));
}
else if (function->force_inline.__jakt_init_index() == 1 /* MakeDefinitionAvailable */){
TRY((this->codegen_function(function,true,output)));
}
else if (struct_is_generic){
if (!function->specialization_index.has_value()){
TRY((this->codegen_function(function,true,output)));
}
}
else if (function->generics->params.is_empty() || (!function->specialization_index.has_value())){
TRY((this->codegen_function_predecl(function,true,false,output)));
}
}

}
}

}

}
}

TRY((set_access_level(Jakt::types::CheckedVisibility::Public())));
if (struct_.generic_parameters.is_empty()){
output.append(StringView::from_string_literal("ByteString debug_description() const;\n"sv));
}
else {
TRY((this->codegen_debug_description_getter(struct_,true,output)));
}

output.append(StringView::from_string_literal("};"sv));
this->codegen_ak_formatter(struct_.name_for_codegen().as_name_for_definition(),generic_parameter_names,template_parameters,this->deferred_output);
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_enum_predecl(Jakt::types::CheckedEnum const enum_,ByteStringBuilder& output) {
{
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(enum_.underlying_type_id,Jakt::types::void_type_id())){
if (this->program->is_integer(enum_.underlying_type_id)){
output.appendff(ByteString::from_utf8_without_validation("enum class {}: {};"sv),enum_.name,TRY((this->codegen_type(enum_.underlying_type_id))));
return {};
}
else {
Jakt::utility::todo(ByteString::from_utf8_without_validation("Enums with a non-integer underlying type"sv));
}

}
bool const is_generic = !enum_.generic_parameters.is_empty();
if (is_generic){
output.append(StringView::from_string_literal("template<"sv));
TRY((this->codegen_template_parameter_names(enum_.generic_parameters,output)));
output.append(StringView::from_string_literal(">\n"sv));
}
output.appendff(ByteString::from_utf8_without_validation("struct {};\n"sv),enum_.name);
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_enum(Jakt::types::CheckedEnum const enum_,ByteStringBuilder& output) {
{
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(enum_.underlying_type_id,Jakt::types::void_type_id())){
if (this->program->is_integer(enum_.underlying_type_id)){
output.appendff(ByteString::from_utf8_without_validation("enum class {} : {} {{\n"sv),enum_.name,TRY((this->codegen_type(enum_.underlying_type_id))));
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
Jakt::types::CheckedEnumVariant __jakt_tmp383 = variant;
if (__jakt_tmp383.__jakt_init_index() == 2 /* WithValue */){
ByteString const name = __jakt_tmp383.as.WithValue.name;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = __jakt_tmp383.as.WithValue.expr;
output.append(name);
output.append(StringView::from_string_literal(" = "sv));
TRY((this->codegen_expression(expr,output,true,false)));
output.append(StringView::from_string_literal(",\n"sv));
}
else {
Jakt::utility::todo(__jakt_format(StringView::from_string_literal("codegen_enum can't generate variant: {}"sv),variant));
}

}

}
}

output.append(StringView::from_string_literal("};\n"sv));
return {};
}
else {
Jakt::utility::todo(ByteString::from_utf8_without_validation("Enums with a non-integer underlying type"sv));
}

}
bool const is_generic = !enum_.generic_parameters.is_empty();
JaktInternal::DynamicArray<ByteString> generic_parameter_names = DynamicArray<ByteString>::create_with({});
ByteStringBuilder template_args_builder = ByteStringBuilder::create();
TRY((this->codegen_template_parameter_names(enum_.generic_parameters,generic_parameter_names,template_args_builder)));
ByteString const template_args = template_args_builder.to_string();
ByteString const generic_parameter_list = Jakt::utility::join(generic_parameter_names,ByteString::from_utf8_without_validation(", "sv));
if (is_generic){
output.append(StringView::from_string_literal("template<"sv));
output.append(template_args);
output.append(StringView::from_string_literal(">\n"sv));
}
output.appendff(ByteString::from_utf8_without_validation("struct {}"sv),enum_.name);
if (enum_.is_boxed){
output.appendff(ByteString::from_utf8_without_validation(": public RefCounted<{}"sv),enum_.name);
if (is_generic){
output.appendff(ByteString::from_utf8_without_validation("<{}>"sv),Jakt::utility::join(generic_parameter_names,ByteString::from_utf8_without_validation(", "sv)));
}
output.append(StringView::from_string_literal(">"sv));
}
output.append(StringView::from_string_literal(" {\n"sv));
size_t const max_index_value = enum_.variants.size();
ByteString const index_type = [&]() -> ByteString { auto __jakt_enum_value = max_index_value;
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&&__jakt_enum_value < static_cast<size_t>(256ULL)) {return ByteString::from_utf8_without_validation("u8"sv);}else if (__jakt_enum_value >= static_cast<size_t>(256ULL)&&__jakt_enum_value < static_cast<size_t>(65536ULL)) {return ByteString::from_utf8_without_validation("u16"sv);}else if (__jakt_enum_value >= static_cast<size_t>(65536ULL)&&__jakt_enum_value < static_cast<size_t>(4294967296ULL)) {return ByteString::from_utf8_without_validation("u32"sv);}else {return ByteString::from_utf8_without_validation("size_t"sv);} 
}();
JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>> const common_fields_variant_field_list_ = TRY((this->codegen_enum_field_lists(enum_)));
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields = common_fields_variant_field_list_.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const variant_field_list = common_fields_variant_field_list_.template get<1>();

output.appendff(ByteString::from_utf8_without_validation("{} __jakt_variant_index = 0;\n"sv),index_type,max_index_value);
if (!common_fields.is_empty()){
output.append(StringView::from_string_literal("union CommonData {\n"sv));
output.append(StringView::from_string_literal("u8 __jakt_uninit_common;\n"sv));
output.append(StringView::from_string_literal("struct {\n"sv));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = common_fields.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,ByteString> field_name__type__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,ByteString> const jakt__field_name__type__ = field_name__type__;
ByteString const field_name = jakt__field_name__type__.template get<0>();
ByteString const type = jakt__field_name__type__.template get<1>();

output.appendff(ByteString::from_utf8_without_validation("{} {};\n"sv),type,field_name);
}

}
}

output.append(StringView::from_string_literal("} init_common;\n"sv));
output.append(StringView::from_string_literal("constexpr CommonData() {}\n"sv));
output.append(StringView::from_string_literal("~CommonData() {}\n"sv));
output.append(StringView::from_string_literal("} common;\n"sv));
}
output.append(StringView::from_string_literal("union VariantData {\n"sv));
output.append(StringView::from_string_literal("u8 __jakt_uninit_value;\n"sv));
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enum_.variants.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t variant_index = _magic_value.value();
{
Jakt::types::CheckedEnumVariant const variant = enum_.variants.operator[](variant_index);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const fields = variant_field_list.operator[](variant_index).template get<1>();
if (!fields.is_empty()){
output.append(StringView::from_string_literal("struct {\n"sv));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,ByteString> field_name__field_type__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,ByteString> const jakt__field_name__field_type__ = field_name__field_type__;
ByteString const field_name = jakt__field_name__field_type__.template get<0>();
ByteString const field_type = jakt__field_name__field_type__.template get<1>();

output.appendff(ByteString::from_utf8_without_validation("{} {};\n"sv),field_type,field_name);
}

}
}

output.appendff(ByteString::from_utf8_without_validation("}} {};\n"sv),variant.name());
}
}

}
}

output.append(StringView::from_string_literal("constexpr VariantData() {}\n"sv));
output.append(StringView::from_string_literal("~VariantData() {}\n"sv));
output.append(StringView::from_string_literal("} as;\n"sv));
output.appendff(ByteString::from_utf8_without_validation("constexpr {} __jakt_init_index() const noexcept {{ return __jakt_variant_index - 1; }}"sv),index_type);
if (enum_.generic_parameters.is_empty()){
output.append(StringView::from_string_literal("ByteString debug_description() const;\n"sv));
}
else {
TRY((this->codegen_enum_debug_description_getter(enum_,true,output)));
}

if (is_generic){
this->codegen_enum_constructors(enum_,true,generic_parameter_list,variant_field_list,common_fields,output);
output.appendff(ByteString::from_utf8_without_validation("~{}()"sv),enum_.name);
this->codegen_enum_destructor_body(enum_,output);
output.append(StringView::from_string_literal("private: void __jakt_destroy_variant() {\n"sv));
this->codegen_enum_destroy_variant(enum_,output);
output.append(StringView::from_string_literal("}\n"sv));
output.append(StringView::from_string_literal("public:\n"sv));
}
else {
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> _magic = variant_field_list.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> variant_name__variant_fields__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> const jakt__variant_name__variant_fields__ = variant_name__variant_fields__;
ByteString const variant_name = jakt__variant_name__variant_fields__.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const variant_fields = jakt__variant_name__variant_fields__.template get<1>();

Jakt::codegen::CodeGenerator::codegen_enum_constructor_decl(enum_.name,variant_name,variant_fields,common_fields,true,Jakt::codegen::CodeGenerator::enum_constructor_result_type(enum_,JaktInternal::OptionalNone()),output);
output.append(StringView::from_string_literal(";\n"sv));
}

}
}

output.appendff(ByteString::from_utf8_without_validation("~{}();\n"sv),enum_.name);
output.appendff(ByteString::from_utf8_without_validation("{0}& operator=({0} const &);\n"sv),enum_.name);
output.appendff(ByteString::from_utf8_without_validation("{0}& operator=({0} &&);\n"sv),enum_.name);
output.appendff(ByteString::from_utf8_without_validation("{0}({0} const&);\n"sv),enum_.name);
output.appendff(ByteString::from_utf8_without_validation("{0}({0} &&);\n"sv),enum_.name);
output.append(StringView::from_string_literal("private: void __jakt_destroy_variant();\n"sv));
output.append(StringView::from_string_literal("public:\n"sv));
}

NonnullRefPtr<Jakt::types::Scope> const enum_scope = this->program->get_scope(enum_.scope_id);
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = enum_scope->functions.iterator();
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
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function_id = this->current_function;
this->current_function = static_cast<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>>>(function);
ScopeGuard __jakt_var_121([&] {
this->current_function = previous_function_id;
});
if (!(function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */)){
if (!enum_.generic_parameters.is_empty()){
TRY((this->codegen_function(function,true,output)));
}
else if (function->generics->params.is_empty() || (!function->specialization_index.has_value())){
TRY((this->codegen_function_predecl(function,true,false,output)));
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

output.appendff(ByteString::from_utf8_without_validation("private:\n{}() {{}};\n"sv),enum_.name);
output.append(StringView::from_string_literal("};\n"sv));
this->codegen_ak_formatter(enum_.name,generic_parameter_names,template_args,this->deferred_output);
}
return {};
}

void Jakt::codegen::CodeGenerator::codegen_enum_constructor_decl(ByteString const enum_name,ByteString const variant_name,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const variant_fields,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields,bool const is_inline,ByteString const ctor_result_type,ByteStringBuilder& output) {
{
output.append(StringView::from_string_literal("[[nodiscard]] "sv));
if (is_inline){
output.appendff(ByteString::from_utf8_without_validation("static {} {}("sv),ctor_result_type,variant_name);
}
else {
output.appendff(ByteString::from_utf8_without_validation("{} {}::{}("sv),ctor_result_type,enum_name,variant_name);
}

bool const has_common_fields = !common_fields.is_empty();
if (has_common_fields){
JaktInternal::Tuple<ByteString,ByteString> const first_name_first_type_ = common_fields.operator[](static_cast<i64>(0LL));
ByteString const first_name = first_name_first_type_.template get<0>();
ByteString const first_type = first_name_first_type_.template get<1>();

output.appendff(ByteString::from_utf8_without_validation("{} {}"sv),first_type,first_name);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(common_fields.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
JaktInternal::Tuple<ByteString,ByteString> const name_type_ = common_fields.operator[](i);
ByteString const name = name_type_.template get<0>();
ByteString const type = name_type_.template get<1>();

output.appendff(ByteString::from_utf8_without_validation(", {} {}"sv),type,name);
}

}
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = variant_fields.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,ByteString> name__type__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,ByteString> const jakt__name__type__ = name__type__;
ByteString const name = jakt__name__type__.template get<0>();
ByteString const type = jakt__name__type__.template get<1>();

output.appendff(ByteString::from_utf8_without_validation(", {} {}"sv),type,name);
}

}
}

}
else if (!variant_fields.is_empty()){
JaktInternal::Tuple<ByteString,ByteString> const first_name_first_type_ = variant_fields.operator[](static_cast<i64>(0LL));
ByteString const first_name = first_name_first_type_.template get<0>();
ByteString const first_type = first_name_first_type_.template get<1>();

output.appendff(ByteString::from_utf8_without_validation("{} {}"sv),first_type,first_name);
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(variant_fields.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
JaktInternal::Tuple<ByteString,ByteString> const name_type_ = variant_fields.operator[](i);
ByteString const name = name_type_.template get<0>();
ByteString const type = name_type_.template get<1>();

output.appendff(ByteString::from_utf8_without_validation(", {} {}"sv),type,name);
}

}
}

}
output.append(StringView::from_string_literal(")"sv));
}
}

void Jakt::codegen::CodeGenerator::codegen_for_enum_variants(Jakt::types::CheckedEnum const& enum_,Function<ByteString(ByteString)> const& stmt_fmt,ByteString const index_expr,ByteStringBuilder& builder) const {
{
builder.appendff(ByteString::from_utf8_without_validation("switch ({}) {{\n"sv),index_expr);
size_t const common_field_count = enum_.fields.size();
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enum_.variants.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t variant_index = _magic_value.value();
{
Jakt::types::CheckedEnumVariant const& variant = enum_.variants.operator[](variant_index);
ByteString const variant_name = variant.name();
builder.appendff(ByteString::from_utf8_without_validation("case {} /* {} */:\n"sv),variant_index,variant_name);
{auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */:case 2 /* WithValue */:{
}
goto __jakt_label_159;case 1 /* Typed */:{
builder.append(stmt_fmt(__jakt_format(StringView::from_string_literal("as.{}.value"sv),variant_name)));
}
goto __jakt_label_159;case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = fields.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(common_field_count),static_cast<size_t>(9223372036854775807LL)}).iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::VarId field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->program->get_variable(field);
ByteString const name = variable->name_for_codegen().as_name_for_use();
builder.append(stmt_fmt(__jakt_format(StringView::from_string_literal("as.{}.{}"sv),variant_name,name)));
}

}
}

}
goto __jakt_label_159;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
break;}goto __jakt_label_159; __jakt_label_159:;;
builder.append(StringView::from_string_literal("break;\n"sv));
}

}
}

builder.append(StringView::from_string_literal("}\n"sv));
}
}

ByteString Jakt::codegen::CodeGenerator::codegen_enum_assignment_body(Jakt::types::CheckedEnum const enum_,bool const is_constructor,bool const use_move) const {
{
ByteStringBuilder builder = ByteStringBuilder::create();
builder.append(StringView::from_string_literal("{"sv));
if (is_constructor){
builder.append(StringView::from_string_literal("VERIFY(rhs.__jakt_variant_index != 0);\n"sv));
}
else {
builder.append(StringView::from_string_literal("VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);\n"sv));
}

Function<ByteString(ByteString)> const assign = [use_move](ByteString accessor) -> ByteString {{
ByteString const rhs = [&]() -> ByteString { auto __jakt_enum_value = use_move;
if (__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("move(rhs.{})"sv),accessor);}else if (!__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("rhs.{}"sv),accessor);}VERIFY_NOT_REACHED();
 
}();
return __jakt_format(StringView::from_string_literal("this->{} = {};\n"sv),accessor,rhs);
}
}
;
Function<ByteString(ByteString)> const placement_new = [use_move](ByteString accessor) -> ByteString {{
ByteString const rhs = [&]() -> ByteString { auto __jakt_enum_value = use_move;
if (__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("move(rhs.{})"sv),accessor);}else if (!__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("rhs.{}"sv),accessor);}VERIFY_NOT_REACHED();
 
}();
return __jakt_format(StringView::from_string_literal("new (&this->{0}) (decltype(this->{0}))({1});\n"sv),accessor,rhs);
}
}
;
if (is_constructor){
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> common = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->program->get_variable(common->variable_id);
ByteString const name = variable->name_for_codegen().as_name_for_use();
builder.append(placement_new(__jakt_format(StringView::from_string_literal("common.init_common.{}"sv),name)));
}

}
}

}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> common = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->program->get_variable(common->variable_id);
ByteString const name = variable->name_for_codegen().as_name_for_use();
builder.append(assign(__jakt_format(StringView::from_string_literal("common.init_common.{}"sv),name)));
}

}
}

}

if (is_constructor){
this->codegen_for_enum_variants(enum_,placement_new,ByteString::from_utf8_without_validation("rhs.__jakt_init_index()"sv),builder);
}
else {
builder.append(StringView::from_string_literal("if (this->__jakt_variant_index != rhs.__jakt_variant_index) {\n"sv));
builder.append(StringView::from_string_literal("this->__jakt_destroy_variant();\n"sv));
this->codegen_for_enum_variants(enum_,placement_new,ByteString::from_utf8_without_validation("rhs.__jakt_init_index()"sv),builder);
builder.append(StringView::from_string_literal("} else {\n"sv));
this->codegen_for_enum_variants(enum_,assign,ByteString::from_utf8_without_validation("rhs.__jakt_init_index()"sv),builder);
builder.append(StringView::from_string_literal("}\n"sv));
}

builder.append(StringView::from_string_literal("this->__jakt_variant_index = rhs.__jakt_variant_index;\n"sv));
builder.append(StringView::from_string_literal("}\n"sv));
return builder.to_string();
}
}

void Jakt::codegen::CodeGenerator::codegen_enum_constructors(Jakt::types::CheckedEnum const enum_,bool const is_inside_struct,JaktInternal::Optional<ByteString> const generic_parameter_list,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> const variant_field_list,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const common_fields,ByteStringBuilder& output) const {
{
bool const is_generic = !enum_.generic_parameters.is_empty();
ByteString const ctor_result_type = Jakt::codegen::CodeGenerator::enum_constructor_result_type(enum_,generic_parameter_list);
ByteString const ctor_type = [&]() -> ByteString { auto __jakt_enum_value = is_generic;
if (__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("{}<{}>"sv),enum_.name,generic_parameter_list);}else if (!__jakt_enum_value) {return enum_.name;}VERIFY_NOT_REACHED();
 
}();
JaktInternal::Tuple<ByteString,ByteString> const declare_uninit_deref_uninit_ = [&]() -> JaktInternal::Tuple<ByteString,ByteString> { auto __jakt_enum_value = enum_.is_boxed;
if (__jakt_enum_value) {return Tuple{__jakt_format(StringView::from_string_literal("NonnullRefPtr<{0}> __jakt_uninit_enum = adopt_ref(*new {0});\n"sv),ctor_type), ByteString::from_utf8_without_validation("__jakt_uninit_enum->"sv)};}else if (!__jakt_enum_value) {return Tuple{__jakt_format(StringView::from_string_literal("{} __jakt_uninit_enum;\n"sv),enum_.name), ByteString::from_utf8_without_validation("__jakt_uninit_enum."sv)};}VERIFY_NOT_REACHED();
 
}();
ByteString const declare_uninit = declare_uninit_deref_uninit_.template get<0>();
ByteString const deref_uninit = declare_uninit_deref_uninit_.template get<1>();

if (is_inside_struct || (!is_generic)){
Function<ByteString(ByteString, ByteString)> const placement_new = [](ByteString target, ByteString name) -> ByteString {{
return __jakt_format(StringView::from_string_literal("new (&{0}) (decltype({1}))(move({1}));\n"sv),target,name);
}
}
;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(variant_field_list.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t variant_index = _magic_value.value();
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> const variant_name_variant_fields_ = variant_field_list.operator[](variant_index);
ByteString const variant_name = variant_name_variant_fields_.template get<0>();
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const variant_fields = variant_name_variant_fields_.template get<1>();

Jakt::codegen::CodeGenerator::codegen_enum_constructor_decl(enum_.name,variant_name,variant_fields,common_fields,is_inside_struct,ctor_result_type,output);
output.append(StringView::from_string_literal("{\n"sv));
output.append(declare_uninit);
output.appendff(ByteString::from_utf8_without_validation("{}__jakt_variant_index = {};\n"sv),deref_uninit,JaktInternal::checked_add(variant_index,static_cast<size_t>(1ULL)));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = common_fields.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,ByteString> field = _magic_value.value();
{
ByteString const name = field.template get<0>();
output.append(placement_new(__jakt_format(StringView::from_string_literal("{}common.init_common.{}"sv),deref_uninit,name),name));
}

}
}

{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,ByteString>> _magic = variant_fields.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ByteString>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,ByteString> field = _magic_value.value();
{
ByteString const name = field.template get<0>();
output.append(placement_new(__jakt_format(StringView::from_string_literal("{}as.{}.{}"sv),deref_uninit,variant_name,name),name));
}

}
}

output.append(StringView::from_string_literal("return __jakt_uninit_enum;\n"sv));
output.append(StringView::from_string_literal("}\n"sv));
}

}
}

if (is_inside_struct){
output.appendff(ByteString::from_utf8_without_validation("{0}& operator=({0} const &rhs)"sv),enum_.name);
}
else {
output.appendff(ByteString::from_utf8_without_validation("{0}& {0}::operator=({0} const &rhs)"sv),enum_.name);
}

output.append(StringView::from_string_literal("{\n"sv));
output.append(this->codegen_enum_assignment_body(enum_,false,false));
output.append(StringView::from_string_literal("return *this;\n"sv));
output.append(StringView::from_string_literal("}\n"sv));
if (is_inside_struct){
output.appendff(ByteString::from_utf8_without_validation("{0}({0} const &rhs)"sv),enum_.name);
}
else {
output.appendff(ByteString::from_utf8_without_validation("{0}::{0}({0} const &rhs)"sv),enum_.name);
}

output.append(this->codegen_enum_assignment_body(enum_,true,false));
if (is_inside_struct){
output.appendff(ByteString::from_utf8_without_validation("{0}& operator=({0} &&rhs)"sv),enum_.name);
}
else {
output.appendff(ByteString::from_utf8_without_validation("{0}& {0}::operator=({0} &&rhs)"sv),enum_.name);
}

output.append(StringView::from_string_literal("{\n"sv));
output.append(this->codegen_enum_assignment_body(enum_,false,true));
output.append(StringView::from_string_literal("return *this;\n"sv));
output.append(StringView::from_string_literal("}\n"sv));
if (is_inside_struct){
output.appendff(ByteString::from_utf8_without_validation("{0}({0} &&rhs)"sv),enum_.name);
}
else {
output.appendff(ByteString::from_utf8_without_validation("{0}::{0}({0} &&rhs)"sv),enum_.name);
}

output.append(StringView::from_string_literal("{\n"sv));
output.append(this->codegen_enum_assignment_body(enum_,true,true));
output.append(StringView::from_string_literal("}\n"sv));
}
else {
Jakt::utility::panic(ByteString::from_utf8_without_validation("Out of line constructor cannot be generated for generic enum"sv));
}

}
}

ErrorOr<JaktInternal::Tuple<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>>> Jakt::codegen::CodeGenerator::codegen_enum_field_lists(Jakt::types::CheckedEnum const enum_) {
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> common_fields = DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({});
JaktInternal::Set<ByteString> common_field_names = Set<ByteString>::create_with_values({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->program->get_variable(field->variable_id);
ByteString const name = variable->name_for_codegen().as_name_for_definition();
common_fields.push(Tuple{name, TRY((this->codegen_type(variable->type_id)))});
common_field_names.add(name);
}

}
}

JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>> variant_field_list = DynamicArray<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>>>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enum_.variants.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t variant_index = _magic_value.value();
{
Jakt::types::CheckedEnumVariant const variant = enum_.variants.operator[](variant_index);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> const fields = TRY(([&]() -> ErrorOr<JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>> { auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
return DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({});};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::VarId> const& own_fields = __jakt_match_value.fields;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> fields = DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = own_fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::VarId field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->program->get_variable(field);
if (!common_field_names.contains(variable->name)){
fields.push(Tuple{variable->name_for_codegen().as_name_for_definition(), TRY((this->codegen_type(variable->type_id)))});
}
}

}
}

return fields;
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> fields = DynamicArray<JaktInternal::Tuple<ByteString,ByteString>>::create_with({});
fields.push(Tuple{ByteString::from_utf8_without_validation("value"sv), TRY((this->codegen_type(type_id)))});
return fields;
}
VERIFY_NOT_REACHED();
};/*case end*/
default:{
Jakt::utility::todo(__jakt_format(StringView::from_string_literal("codegen enum variant: {}"sv),variant));
}
}/*switch end*/
 
}()));
variant_field_list.push(Tuple{variant.name(), fields});
}

}
}

return Tuple{common_fields, variant_field_list};
}
}

JaktInternal::Optional<ByteString> Jakt::codegen::CodeGenerator::destructor_name(Jakt::ids::TypeId const id) const {
{
{auto&& __jakt_match_variant = *this->program->get_type(id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */:return ByteString::from_utf8_without_validation("ByteString"sv);case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
{
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(id);
{auto __jakt_enum_value = struct_.record_type.__jakt_init_index() == 1 /* Class */;
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("NonnullRefPtr"sv);}else if (!__jakt_enum_value) {return struct_.name_for_codegen().as_name_for_use();}VERIFY_NOT_REACHED();
}
}
VERIFY_NOT_REACHED();
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(id);
{auto __jakt_enum_value = struct_.record_type.__jakt_init_index() == 1 /* Class */;
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("NonnullRefPtr"sv);}else if (!__jakt_enum_value) {return struct_.name_for_codegen().as_name_for_use();}VERIFY_NOT_REACHED();
}
}
VERIFY_NOT_REACHED();
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return name;};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(id);
{auto __jakt_enum_value = enum_.is_boxed;
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("NonnullRefPtr"sv);}else if (!__jakt_enum_value) {return enum_.name;}VERIFY_NOT_REACHED();
}
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
{
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(id);
{auto __jakt_enum_value = enum_.is_boxed;
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("NonnullRefPtr"sv);}else if (!__jakt_enum_value) {return enum_.name;}VERIFY_NOT_REACHED();
}
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return JaktInternal::OptionalNone();}/*switch end*/
}
}
}

ByteString Jakt::codegen::CodeGenerator::enum_constructor_result_type(Jakt::types::CheckedEnum const enum_,JaktInternal::Optional<ByteString> const generic_parameter_list) {
{
ByteString result = enum_.name;
if (!enum_.generic_parameters.is_empty()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(result,__jakt_format(StringView::from_string_literal("<{}>"sv),generic_parameter_list.value()));
}
if (enum_.is_boxed){
result = __jakt_format(StringView::from_string_literal("NonnullRefPtr<{}>"sv),result);
}
return result;
}
}

void Jakt::codegen::CodeGenerator::codegen_enum_destroy_variant(Jakt::types::CheckedEnum const enum_,ByteStringBuilder& output) const {
{
size_t const common_field_count = enum_.fields.size();
output.append(StringView::from_string_literal("switch (this->__jakt_init_index()) {\n"sv));
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enum_.variants.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t variant_index = _magic_value.value();
{
Jakt::types::CheckedEnumVariant const variant = enum_.variants.operator[](variant_index);
ByteString const variant_name = variant.name();
output.appendff(ByteString::from_utf8_without_validation("case {} /* {} */:"sv),variant_index,variant_name);
{auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */:case 2 /* WithValue */:{
}
goto __jakt_label_160;case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<ByteString> const ds_name = this->destructor_name(type_id);
JaktInternal::Optional<ByteString> __jakt_tmp384 = ds_name;
if (__jakt_tmp384.has_value()){
ByteString const name = __jakt_tmp384.value();
output.appendff(ByteString::from_utf8_without_validation("this->as.{}.value.~{}();\n"sv),variant_name,name);
}
}
goto __jakt_label_160;};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = fields.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(common_field_count),static_cast<size_t>(9223372036854775807LL)}).iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::VarId field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->program->get_variable(field);
JaktInternal::Optional<ByteString> const ds = this->destructor_name(variable->type_id);
JaktInternal::Optional<ByteString> __jakt_tmp385 = ds;
if (__jakt_tmp385.has_value()){
ByteString const name = __jakt_tmp385.value();
output.appendff(ByteString::from_utf8_without_validation("this->as.{}.{}.~{}();\n"sv),variant_name,variable->name_for_codegen().as_name_for_use(),name);
}
}

}
}

}
goto __jakt_label_160;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
break;}goto __jakt_label_160; __jakt_label_160:;;
output.append(StringView::from_string_literal("break;\n"sv));
}

}
}

output.append(StringView::from_string_literal("}\n"sv));
}
}

void Jakt::codegen::CodeGenerator::codegen_enum_destructor_body(Jakt::types::CheckedEnum const enum_,ByteStringBuilder& output) const {
{
output.append(StringView::from_string_literal("{ if (this->__jakt_variant_index == 0) return;\n"sv));
size_t const common_field_count = enum_.fields.size();
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> common_field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = this->program->get_variable(common_field->variable_id);
JaktInternal::Optional<ByteString> const ds = this->destructor_name(variable->type_id);
JaktInternal::Optional<ByteString> __jakt_tmp386 = ds;
if (__jakt_tmp386.has_value()){
ByteString const name = __jakt_tmp386.value();
output.appendff(ByteString::from_utf8_without_validation("this->common.init_common.{}.~{}();\n"sv),variable->name_for_codegen().as_name_for_use(),name);
}
}

}
}

output.append(StringView::from_string_literal("this->__jakt_destroy_variant(); }\n"sv));
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_debug_description_getter(Jakt::types::CheckedStruct const struct_,bool const is_inline,ByteStringBuilder& output) {
{
if ((!is_inline) && (!struct_.generic_parameters.is_empty())){
output.append(StringView::from_string_literal("template <"sv));
TRY((this->codegen_template_parameter_names(struct_.generic_parameters,output)));
output.append(StringView::from_string_literal(">\n"sv));
}
output.append(StringView::from_string_literal("ByteString "sv));
if (!is_inline){
output.append(TRY((this->codegen_type_possibly_as_namespace(struct_.type_id,true))));
output.append(StringView::from_string_literal("::"sv));
}
output.append(StringView::from_string_literal("debug_description() const { "sv));
output.append(StringView::from_string_literal("auto builder = ByteStringBuilder::create();"sv));
output.appendff(ByteString::from_utf8_without_validation("builder.append(\"{}(\"sv);"sv),struct_.name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal("{\n"sv));
output.append(StringView::from_string_literal("JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};\n"sv));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = struct_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const field_var = this->program->get_variable(field->variable_id);
output.append(StringView::from_string_literal("JaktInternal::PrettyPrint::must_output_indentation(builder);\n"sv));
output.appendff(ByteString::from_utf8_without_validation("builder.appendff(\"{}: "sv),field_var->name_for_codegen().as_name_for_use());
if (TRY((this->program->is_string(field_var->type_id)))){
output.append(StringView::from_string_literal("\\\"{}\\\""sv));
}
else {
output.append(StringView::from_string_literal("{}"sv));
}

if (i != JaktInternal::checked_sub(struct_.fields.size(),static_cast<size_t>(1ULL))){
output.append(StringView::from_string_literal(", "sv));
}
output.append(StringView::from_string_literal("\", "sv));
output.append([&]() -> StringView { auto&& __jakt_match_variant = *this->program->get_type(field_var->type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{auto&& __jakt_match_variant = this->program->get_struct(struct_id).record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */:return StringView::from_string_literal("*"sv);default:return StringView::from_string_literal(""sv);}/*switch end*/
}};/*case end*/
default:return StringView::from_string_literal(""sv);}/*switch end*/
 
}());
output.append(field_var->name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal(");\n"sv));
i++;
}

}
}

output.append(StringView::from_string_literal("}\n"sv));
output.append(StringView::from_string_literal("builder.append(\")\"sv);"sv));
output.append(StringView::from_string_literal("return builder.to_string();"sv));
output.append(StringView::from_string_literal(" }\n"sv));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_enum_debug_description_getter(Jakt::types::CheckedEnum const enum_,bool const is_inline,ByteStringBuilder& output) {
{
if ((!is_inline) && (!enum_.generic_parameters.is_empty())){
output.append(StringView::from_string_literal("template <"sv));
TRY((this->codegen_template_parameter_names(enum_.generic_parameters,output)));
output.append(StringView::from_string_literal(">\n"sv));
}
output.append(StringView::from_string_literal("ByteString "sv));
if (!is_inline){
output.append(TRY((this->codegen_type_possibly_as_namespace(enum_.type_id,true))));
output.append(StringView::from_string_literal("::"sv));
}
output.append(StringView::from_string_literal("debug_description() const {\n"sv));
output.append(StringView::from_string_literal("auto builder = ByteStringBuilder::create();\n"sv));
output.append(StringView::from_string_literal("switch (this->__jakt_init_index()) {"sv));
size_t const common_field_count = enum_.fields.size();
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(enum_.variants.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::CheckedEnumVariant const variant = enum_.variants.operator[](i);
ByteString const name = variant.name();
output.appendff(ByteString::from_utf8_without_validation("case {} /* {} */: {{\n"sv),i,name);
{auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
output.appendff(ByteString::from_utf8_without_validation("builder.append(\"{}::{}\"sv);\n"sv),enum_.name,name);
output.appendff(ByteString::from_utf8_without_validation("[[maybe_unused]] auto const& that = this->as.{};\n"sv),name);
output.append(StringView::from_string_literal("builder.append(\"(\"sv);\n"sv));
output.append(StringView::from_string_literal("{\n"sv));
output.append(StringView::from_string_literal("JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};\n"sv));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::VarId field = _magic_value.value();
{
output.append(StringView::from_string_literal("JaktInternal::PrettyPrint::must_output_indentation(builder);\n"sv));
NonnullRefPtr<Jakt::types::CheckedVariable> const var = this->program->get_variable(field);
if (TRY((this->program->is_string(var->type_id)))){
output.appendff(ByteString::from_utf8_without_validation("builder.appendff(\"{}: \\\"{{}}\\\""sv),var->name_for_codegen().as_name_for_use());
}
else {
output.appendff(ByteString::from_utf8_without_validation("builder.appendff(\"{}: {{}}"sv),var->name_for_codegen().as_name_for_use());
}

if (i != JaktInternal::checked_sub(fields.size(),static_cast<size_t>(1ULL))){
output.append(StringView::from_string_literal(", "sv));
}
if (i < common_field_count){
output.appendff(ByteString::from_utf8_without_validation("\", this->common.init_common.{});\n"sv),var->name_for_codegen().as_name_for_use());
}
else {
output.appendff(ByteString::from_utf8_without_validation("\", that.{});\n"sv),var->name_for_codegen().as_name_for_use());
}

i++;
}

}
}

output.append(StringView::from_string_literal("}\n"sv));
output.append(StringView::from_string_literal("builder.append(\")\"sv);\n"sv));
}
goto __jakt_label_161;};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
output.appendff(ByteString::from_utf8_without_validation("builder.append(\"{}::{}\"sv);\n"sv),enum_.name,name);
output.appendff(ByteString::from_utf8_without_validation("[[maybe_unused]] auto const& that = this->as.{};\n"sv),name);
if (TRY((this->program->is_string(type_id)))){
output.append(StringView::from_string_literal("builder.appendff(\"(\\\"{}\\\")\", that.value);\n"sv));
}
else {
output.append(StringView::from_string_literal("builder.appendff(\"({})\", that.value);\n"sv));
}

}
goto __jakt_label_161;};/*case end*/
default:{
output.appendff(ByteString::from_utf8_without_validation("return ByteString(\"{}::{}\"sv);\n"sv),enum_.name,name);
}
goto __jakt_label_161;}/*switch end*/
break;}goto __jakt_label_161; __jakt_label_161:;;
output.append(StringView::from_string_literal("break;}\n"sv));
}

}
}

output.append(StringView::from_string_literal("}\nreturn builder.to_string();\n}\n"sv));
}
return {};
}

void Jakt::codegen::CodeGenerator::codegen_ak_formatter(ByteString const name,JaktInternal::DynamicArray<ByteString> const generic_parameter_names,ByteString const template_args,ByteStringBuilder& output) {
{
ByteString const generic_type_args = Jakt::utility::join(generic_parameter_names,ByteString::from_utf8_without_validation(", "sv));
ByteString qualified_name = ByteString::from_utf8_without_validation(""sv);
{
JaktInternal::ArrayIterator<ByteString> _magic = this->namespace_stack.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString namespace_ = _magic_value.value();
{
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(qualified_name,__jakt_format(StringView::from_string_literal("{}::"sv),namespace_));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(qualified_name,name);
if (!generic_parameter_names.is_empty()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(qualified_name,__jakt_format(StringView::from_string_literal("<{}>\n"sv),generic_type_args));
}
output.append(StringView::from_string_literal("} // namespace Jakt\n"sv));
output.appendff(ByteString::from_utf8_without_validation("template<{}>"sv),template_args);
output.appendff(ByteString::from_utf8_without_validation("struct Jakt::Formatter<Jakt::{}> : Jakt::Formatter<Jakt::StringView>"sv),qualified_name);
output.append(StringView::from_string_literal("{\n"sv));
output.appendff(ByteString::from_utf8_without_validation("Jakt::ErrorOr<void> format(Jakt::FormatBuilder& builder, Jakt::{} const& value) {{\n"sv),qualified_name);
output.append(StringView::from_string_literal("JaktInternal::PrettyPrint::ScopedEnable pretty_print_enable { m_alternative_form };"sv));
output.append(StringView::from_string_literal("Jakt::ErrorOr<void> format_error = Jakt::Formatter<Jakt::StringView>::format(builder, value.debug_description());"sv));
output.append(StringView::from_string_literal("return format_error;"sv));
output.append(StringView::from_string_literal("}\n"sv));
output.append(StringView::from_string_literal("};\n"sv));
output.append(StringView::from_string_literal("namespace Jakt {\n"sv));
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_expression_and_deref_if_generic_and_needed(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expression,ByteStringBuilder& output,bool const syntactically_self_contained) {
{
if (this->program->get_type(expression->type())->__jakt_init_index() == 18 /* TypeVariable */){
output.append(StringView::from_string_literal("(*([]<typename V>(V&& value) {{ if constexpr (IsSpecializationOf<V, NonnullRefPtr>) return &*value; else return &value; }})("sv));
TRY((this->codegen_expression(expression,output,true,false)));
output.append(StringView::from_string_literal("))"sv));
return {};
}
TRY((this->codegen_expression(expression,output,true,true)));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expression,ByteStringBuilder& output,bool const forward_error_with_try,bool const syntactically_self_contained) {
{
this->generic_inferences = expression->common.init_common.generic_inferences.value_or_lazy_evaluated_optional([&] { return this->generic_inferences; });
ScopeGuard __jakt_var_122([&] {
this->generic_inferences = JaktInternal::OptionalNone();
});
{auto&& __jakt_match_variant = *expression;
switch(__jakt_match_variant.__jakt_init_index()) {
case 34 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Unexpected reflect expression at {}"sv),span));
}
goto __jakt_label_162;};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& to = __jakt_match_value.to;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
NonnullRefPtr<typename Jakt::types::Type> const type = this->program->get_type(type_id);
Jakt::ids::TypeId const index_type = [&]() -> Jakt::ids::TypeId { auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return args.operator[](static_cast<i64>(0LL));};/*case end*/
default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Internal error: range expression doesn't have Range type"sv));
}
}/*switch end*/
 
}();
output.append(TRY((this->codegen_type(type_id))));
output.append(StringView::from_string_literal("{"sv));
output.append(StringView::from_string_literal("static_cast<"sv));
output.append(TRY((this->codegen_type(index_type))));
output.append(StringView::from_string_literal(">("sv));
if (from.has_value()){
TRY((this->codegen_expression(from.value(),output,true,false)));
}
else {
output.append(StringView::from_string_literal("0LL"sv));
}

output.append(StringView::from_string_literal("),static_cast<"sv));
output.append(TRY((this->codegen_type(index_type))));
output.append(StringView::from_string_literal(">("sv));
if (to.has_value()){
TRY((this->codegen_expression(to.value(),output,true,false)));
}
else {
output.append(StringView::from_string_literal("9223372036854775807LL"sv));
}

output.append(StringView::from_string_literal(")}"sv));
}
goto __jakt_label_162;};/*case end*/
case 25 /* OptionalNone */:{
output.append(StringView::from_string_literal("JaktInternal::OptionalNone()"sv));
}
goto __jakt_label_162;case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
output.append(StringView::from_string_literal("static_cast<"sv));
output.append(TRY((this->codegen_type(type_id))));
output.append(StringView::from_string_literal(">("sv));
TRY((this->codegen_expression(expr,output,true,false)));
output.append(StringView::from_string_literal(")"sv));
}
goto __jakt_label_162;};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
TRY((this->codegen_expression(expr,output,true,true)));
output.append(StringView::from_string_literal(".value()"sv));
}
goto __jakt_label_162;};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;Jakt::types::CheckedStringLiteral const& val = __jakt_match_value.val;
{
ByteString const original_string = val.to_string();
ByteString const escaped_value = original_string.replace(ByteString::from_utf8_without_validation("\n"sv),ByteString::from_utf8_without_validation("\\n"sv));
if (val.type_id.equals(Jakt::types::builtin(Jakt::types::BuiltinType::JaktString()))){
output.append(StringView::from_string_literal("Jakt::ByteString(\""sv));
output.append(escaped_value);
output.append(StringView::from_string_literal("\"sv)"sv));
}
else {
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const ids = TRY((this->program->find_functions_with_name_in_scope(this->program->find_type_scope_id(val.type_id),ByteString::from_utf8_without_validation("from_string_literal"sv),false,JaktInternal::OptionalNone())));
if ((!ids.has_value()) || ids.value().is_empty()){
Jakt::utility::panic(ByteString::from_utf8_without_validation("Internal error: couldn't find a 'from_string_literal' function despite passing typecheck"sv));
}
ByteString const name = this->program->get_function(ids.value().operator[](static_cast<i64>(0LL)))->name_for_codegen().as_name_for_use();
ByteString const error_handler = [&]() -> ByteString { auto __jakt_enum_value = val.may_throw;
if (__jakt_enum_value) {return this->current_error_handler(forward_error_with_try);}else {return ByteString::from_utf8_without_validation(""sv);} 
}();
output.append(error_handler);
if (!error_handler.is_empty()){
output.append_code_point(static_cast<u32>(U'('));
}
output.appendff(ByteString::from_utf8_without_validation("{}::{}(\"{}\"sv)"sv),TRY((this->codegen_type_possibly_as_namespace(val.type_id,true))),name,escaped_value);
if (!error_handler.is_empty()){
output.append_code_point(static_cast<u32>(U')'));
}
}

}
goto __jakt_label_162;};/*case end*/
case 3 /* ByteConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ByteConstant;ByteString const& val = __jakt_match_value.val;
{
output.append(StringView::from_string_literal("static_cast<u8>(u8'"sv));
output.append(val);
output.append(StringView::from_string_literal("')"sv));
}
goto __jakt_label_162;};/*case end*/
case 5 /* CCharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CCharacterConstant;ByteString const& val = __jakt_match_value.val;
{
output.append(StringView::from_string_literal("'"sv));
output.append(val);
output.append(StringView::from_string_literal("'"sv));
}
goto __jakt_label_162;};/*case end*/
case 4 /* CharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CharacterConstant;ByteString const& val = __jakt_match_value.val;
{
output.append(StringView::from_string_literal("static_cast<u32>(U'"sv));
output.append(val);
output.append(StringView::from_string_literal("')"sv));
}
goto __jakt_label_162;};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
{
ByteString const name = var->name_for_codegen().as_name_for_use();
if (name == ByteString::from_utf8_without_validation("this"sv)){
JaktInternal::Optional<ByteString> __jakt_tmp387 = this->this_replacement;
if (__jakt_tmp387.has_value()){
ByteString const replacement = __jakt_tmp387.value();
output.append(replacement);
}
else {
if (syntactically_self_contained){
output.append(StringView::from_string_literal("(*this)"sv));
}
else {
output.append(StringView::from_string_literal("*this"sv));
}

}

}
else {
output.append(name);
}

}
goto __jakt_label_162;};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& index = __jakt_match_value.index;
JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> const& trait_implementation = __jakt_match_value.trait_implementation;
{
JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> __jakt_tmp388 = trait_implementation;
if (__jakt_tmp388.has_value()){
Jakt::types::OperatorTraitImplementation const implementation = __jakt_tmp388.value();
TRY((this->codegen_method_call(expr,implementation.call_expression,false,output,forward_error_with_try,syntactically_self_contained)));
}
else {
Jakt::utility::panic(ByteString::from_utf8_without_validation("Internal error: array indexing without trait implementation"sv));
}

}
goto __jakt_label_162;};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& index = __jakt_match_value.index;
JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> const& trait_implementation = __jakt_match_value.trait_implementation;
{
JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> __jakt_tmp389 = trait_implementation;
if (__jakt_tmp389.has_value()){
Jakt::types::OperatorTraitImplementation const implementation = __jakt_tmp389.value();
TRY((this->codegen_method_call(expr,implementation.call_expression,false,output,forward_error_with_try,syntactically_self_contained)));
}
else {
Jakt::utility::panic(ByteString::from_utf8_without_validation("Internal error: dictionary indexing without trait implementation"sv));
}

}
goto __jakt_label_162;};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
{
if (is_optional){
TRY((this->codegen_expression(expr,output,true,true)));
output.appendff(ByteString::from_utf8_without_validation(".map([](auto& _value) {{ return _value.template get<{}>(); }})"sv),index);
}
else {
if (this->expr_codegens_to_this_pointer(expr)){
output.append(StringView::from_string_literal("this->"sv));
}
else {
TRY((this->codegen_expression(expr,output,true,true)));
output.append_code_point(static_cast<u32>(U'.'));
}

output.appendff(ByteString::from_utf8_without_validation("template get<{}>()"sv),index);
}

}
goto __jakt_label_162;};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& name = __jakt_match_value.name;
JaktInternal::Optional<Jakt::ids::VarId> const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
{
ByteString const var_name = [&]() -> ByteString { auto __jakt_enum_value = index.has_value();
if (__jakt_enum_value) {return this->program->get_variable(index.value())->name_for_codegen().as_name_for_use();}else if (!__jakt_enum_value) {return name;}VERIFY_NOT_REACHED();
 
}();
NonnullRefPtr<typename Jakt::types::Type> const expression_type = this->program->get_type(expr->type());
{auto&& __jakt_match_variant = *expression_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* RawPtr */:{
TRY((this->codegen_expression(expr,output,true,true)));
output.append(StringView::from_string_literal("->"sv));
}
goto __jakt_label_163;case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
bool const expr_is_thisptr = this->expr_codegens_to_this_pointer(expr);
if ((!is_optional) && expr_is_thisptr){
output.append(StringView::from_string_literal("this->"sv));
}
else {
TRY((this->codegen_expression(expr,output,true,true)));
Jakt::types::CheckedStruct const structure = this->program->get_struct(id);
if ((structure.record_type.__jakt_init_index() == 1 /* Class */) && (!expr_is_thisptr)){
output.append(StringView::from_string_literal("->"sv));
}
else {
output.append(StringView::from_string_literal("."sv));
}

}

}
goto __jakt_label_163;};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
{
bool const expr_is_thisptr = this->expr_codegens_to_this_pointer(expr);
if ((!is_optional) && expr_is_thisptr){
output.append(StringView::from_string_literal("this->"sv));
}
else {
TRY((this->codegen_expression(expr,output,true,true)));
Jakt::types::CheckedStruct const structure = this->program->get_struct(id);
if ((structure.record_type.__jakt_init_index() == 1 /* Class */) && (!expr_is_thisptr)){
output.append(StringView::from_string_literal("->"sv));
}
else {
output.append(StringView::from_string_literal("."sv));
}

}

}
goto __jakt_label_163;};/*case end*/
default:{
if ((!is_optional) && this->expr_codegens_to_this_pointer(expr)){
output.append(StringView::from_string_literal("this->"sv));
}
else {
TRY((this->codegen_expression(expr,output,true,true)));
output.append(StringView::from_string_literal("."sv));
}

}
goto __jakt_label_163;}/*switch end*/
}goto __jakt_label_163; __jakt_label_163:;;
if (is_optional){
output.append(StringView::from_string_literal("map([](auto& _value) { return _value"sv));
ByteString access_operator = ByteString::from_utf8_without_validation("."sv);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp390 = expression_type;
if (__jakt_tmp390->__jakt_init_index() == 20 /* GenericInstance */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp390->as.GenericInstance.args;
if (args.size() > static_cast<size_t>(0ULL)){
{auto&& __jakt_match_variant = *this->program->get_type(args.operator[](static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
if (this->program->get_struct(id).record_type.__jakt_init_index() == 1 /* Class */){
access_operator = ByteString::from_utf8_without_validation("->"sv);
}
}
goto __jakt_label_164;};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
{
if (this->program->get_struct(id).record_type.__jakt_init_index() == 1 /* Class */){
access_operator = ByteString::from_utf8_without_validation("->"sv);
}
}
goto __jakt_label_164;};/*case end*/
default:{
}
goto __jakt_label_164;}/*switch end*/
}goto __jakt_label_164; __jakt_label_164:;;
}
}
output.append(access_operator);
output.append(var_name);
output.append(StringView::from_string_literal("; })"sv));
}
else {
output.append(var_name);
}

}
goto __jakt_label_162;};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
{
{auto&& __jakt_match_variant = *this->program->get_type(expr->type());
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* RawPtr */:{
TRY((this->codegen_expression(expr,output,true,true)));
output.append(StringView::from_string_literal("->"sv));
}
goto __jakt_label_165;case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
{
bool const expr_is_thisptr = this->expr_codegens_to_this_pointer(expr);
if ((!is_optional) && expr_is_thisptr){
output.append(StringView::from_string_literal("this->common.init_common."sv));
}
else {
TRY((this->codegen_expression(expr,output,true,true)));
Jakt::types::CheckedEnum const structure = this->program->get_enum(id);
Jakt::parser::RecordType __jakt_tmp392 = structure.record_type;
if (__jakt_tmp392.__jakt_init_index() == 3 /* SumEnum */){
bool const is_boxed = __jakt_tmp392.as.SumEnum.is_boxed;
if (is_boxed && (!this->expr_codegens_to_this_pointer(expr))){
output.append(StringView::from_string_literal("->common.init_common."sv));
}
else {
output.append(StringView::from_string_literal(".common.init_common."sv));
}

}
else {
output.append(StringView::from_string_literal(".common.init_common."sv));
}

}

}
goto __jakt_label_165;};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
{
bool const expr_is_thisptr = this->expr_codegens_to_this_pointer(expr);
if ((!is_optional) && expr_is_thisptr){
output.append(StringView::from_string_literal("this->common.init_common."sv));
}
else {
TRY((this->codegen_expression(expr,output,true,true)));
Jakt::types::CheckedEnum const structure = this->program->get_enum(id);
Jakt::parser::RecordType __jakt_tmp392 = structure.record_type;
if (__jakt_tmp392.__jakt_init_index() == 3 /* SumEnum */){
bool const is_boxed = __jakt_tmp392.as.SumEnum.is_boxed;
if (is_boxed && (!this->expr_codegens_to_this_pointer(expr))){
output.append(StringView::from_string_literal("->common.init_common."sv));
}
else {
output.append(StringView::from_string_literal(".common.init_common."sv));
}

}
else {
output.append(StringView::from_string_literal(".common.init_common."sv));
}

}

}
goto __jakt_label_165;};/*case end*/
default:{
if ((!is_optional) && this->expr_codegens_to_this_pointer(expr)){
output.append(StringView::from_string_literal("this->"sv));
}
else {
TRY((this->codegen_expression(expr,output,true,true)));
output.append(StringView::from_string_literal("."sv));
}

}
goto __jakt_label_165;}/*switch end*/
}goto __jakt_label_165; __jakt_label_165:;;
if (is_optional){
output.append(StringView::from_string_literal("map([](auto& _value) { return _value."sv));
output.append(index);
output.append(StringView::from_string_literal("; })"sv));
}
else {
output.append(index);
}

}
goto __jakt_label_162;};/*case end*/
case 18 /* ComptimeIndex */:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Internal error: ComptimeIndex should have been replaced by now"sv));
}
goto __jakt_label_162;case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
{
TRY((this->codegen_block(block,output)));
}
goto __jakt_label_162;};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
{
TRY((this->codegen_call(call,output,forward_error_with_try)));
}
goto __jakt_label_162;};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedCall const& call = __jakt_match_value.call;
bool const& is_optional = __jakt_match_value.is_optional;
{
TRY((this->codegen_method_call(expr,call,is_optional,output,forward_error_with_try,syntactically_self_contained)));
}
goto __jakt_label_162;};/*case end*/
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
{
output.append([&]() -> StringView { auto __jakt_enum_value = val;
if (__jakt_enum_value) {return StringView::from_string_literal("true"sv);}else {return StringView::from_string_literal("false"sv);} 
}());
}
goto __jakt_label_162;};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedUnaryOperator const& op = __jakt_match_value.op;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
{auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* PreIncrement */:TRY((this->codegen_prefix_unary(expr,StringView::from_string_literal("++"sv),output,syntactically_self_contained)));goto __jakt_label_166;case 2 /* PreDecrement */:TRY((this->codegen_prefix_unary(expr,StringView::from_string_literal("--"sv),output,syntactically_self_contained)));goto __jakt_label_166;case 4 /* Negate */:TRY((this->codegen_prefix_unary(expr,StringView::from_string_literal("-"sv),output,syntactically_self_contained)));goto __jakt_label_166;case 9 /* LogicalNot */:TRY((this->codegen_prefix_unary(expr,StringView::from_string_literal("!"sv),output,syntactically_self_contained)));goto __jakt_label_166;case 10 /* BitwiseNot */:TRY((this->codegen_prefix_unary(expr,StringView::from_string_literal("~"sv),output,syntactically_self_contained)));goto __jakt_label_166;case 1 /* PostIncrement */:TRY((this->codegen_postfix_unary(expr,StringView::from_string_literal("++"sv),output,syntactically_self_contained)));goto __jakt_label_166;case 3 /* PostDecrement */:TRY((this->codegen_postfix_unary(expr,StringView::from_string_literal("--"sv),output,syntactically_self_contained)));goto __jakt_label_166;case 5 /* Dereference */:{auto&& __jakt_match_variant = *this->program->get_type(expr->type());
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* RawPtr */:TRY((this->codegen_prefix_unary(expr,StringView::from_string_literal("*"sv),output,syntactically_self_contained)));goto __jakt_label_167;default:TRY((this->codegen_expression(expr,output,true,syntactically_self_contained)));goto __jakt_label_167;}/*switch end*/
}goto __jakt_label_167; __jakt_label_167:;;goto __jakt_label_166;case 7 /* Reference */:case 8 /* MutableReference */:TRY((this->codegen_expression(expr,output,true,syntactically_self_contained)));goto __jakt_label_166;case 6 /* RawAddress */:{
bool const is_boxed = this->program->get_type(expr->type())->is_boxed(this->program);
output.appendff(ByteString::from_utf8_without_validation("const_cast<{}>(&"sv),TRY((this->codegen_type_possibly_as_namespace(type_id,is_boxed))));
if (is_boxed){
output.append_code_point(static_cast<u32>(U'*'));
}
TRY((this->codegen_expression(expr,output,true,true)));
output.append_code_point(static_cast<u32>(U')'));
}
goto __jakt_label_166;case 16 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
output.appendff(ByteString::from_utf8_without_validation("sizeof({})"sv),TRY((this->codegen_type(type_id))));goto __jakt_label_166;};/*case end*/
case 12 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
ByteString const is_type = TRY(([&]() -> ErrorOr<ByteString> { auto&& __jakt_match_variant = *this->program->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(id);
return TRY((this->codegen_namespace_qualifier(struct_.scope_id,this->program->get_module(id.module)->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))) + struct_.name_for_codegen().as_name_for_use();
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return this->codegen_type(type_id);}/*switch end*/
 
}()));
output.appendff(ByteString::from_utf8_without_validation("JaktInternal::lenient_is<{}>("sv),is_type);
TRY((this->codegen_expression(expr,output,true,false)));
output.append_code_point(static_cast<u32>(U')'));
}
goto __jakt_label_166;};/*case end*/
case 15 /* IsNone */:{
output.append_code_point(static_cast<u32>(U'!'));
TRY((this->codegen_expression(expr,output,true,true)));
output.append(StringView::from_string_literal(".has_value()"sv));
}
goto __jakt_label_166;case 14 /* IsSome */:{
TRY((this->codegen_expression(expr,output,true,true)));
output.append(StringView::from_string_literal(".has_value()"sv));
}
goto __jakt_label_166;case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;Jakt::types::CheckedTypeCast const& cast = __jakt_match_value.value;
{
Jakt::ids::TypeId final_type_id = cast.type_id();
NonnullRefPtr<typename Jakt::types::Type> const type = this->program->get_type(final_type_id);
ByteString const cast_type = [&]() -> ByteString { auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Fallible */:{
Jakt::ids::TypeId const type_id = [&]() -> Jakt::ids::TypeId { auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return args.operator[](static_cast<i64>(0LL));};/*case end*/
default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Fallible type cast must have Optional result."sv));
}
}/*switch end*/
 
}();
ByteString cast_type = ByteString::from_utf8_without_validation("dynamic_cast"sv);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp393 = this->program->get_type(type_id);
if (__jakt_tmp393->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp393->as.Struct.value;
if (this->program->get_struct(struct_id).record_type.__jakt_init_index() == 1 /* Class */){
final_type_id = type_id;
cast_type = ByteString::from_utf8_without_validation("fallible_class_cast"sv);
}
else if (this->program->is_integer(type_id)){
final_type_id = type_id;
cast_type = ByteString::from_utf8_without_validation("fallible_integer_cast"sv);
}
else if (this->program->is_floating(type_id)){
final_type_id = type_id;
cast_type = ByteString::from_utf8_without_validation("fallible_float_cast"sv);
}
}
else if (this->program->is_integer(type_id)){
final_type_id = type_id;
cast_type = ByteString::from_utf8_without_validation("fallible_integer_cast"sv);
}
else if (this->program->is_floating(type_id)){
final_type_id = type_id;
cast_type = ByteString::from_utf8_without_validation("fallible_float_cast"sv);
}
return cast_type;
}
VERIFY_NOT_REACHED();
case 1 /* Infallible */:{
ByteString cast_type = ByteString::from_utf8_without_validation("verify_cast"sv);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp394 = type;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp396 = type;
if (expr->type().equals(Jakt::types::unknown_type_id())){
cast_type = ByteString::from_utf8_without_validation("assert_type"sv);
}
else if (type->is_boxed(this->program)){
cast_type = ByteString::from_utf8_without_validation("infallible_class_cast"sv);
}
else if (((this->program->is_integer(expr->type()) && this->program->is_floating(type_id)) || (this->program->is_floating(expr->type()) && this->program->is_integer(type_id))) || (this->program->is_floating(expr->type()) && this->program->is_floating(type_id))){
cast_type = ByteString::from_utf8_without_validation("infallible_float_cast"sv);
}
else if (this->program->is_integer(type_id)){
cast_type = ByteString::from_utf8_without_validation("infallible_integer_cast"sv);
}
else if (__jakt_tmp394->__jakt_init_index() == 24 /* Enum */){
Jakt::ids::EnumId const enum_id = __jakt_tmp394->as.Enum.value;
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp395 = type;
if (this->program->is_integer(this->program->get_enum(enum_id).underlying_type_id)){
cast_type = ByteString::from_utf8_without_validation("infallible_enum_cast"sv);
}
else if (__jakt_tmp395->__jakt_init_index() == 25 /* RawPtr */){
Jakt::ids::TypeId const inner = __jakt_tmp395->as.RawPtr.value;
cast_type = ByteString::from_utf8_without_validation("reinterpret_cast"sv);
}
}
else if (__jakt_tmp396->__jakt_init_index() == 25 /* RawPtr */){
Jakt::ids::TypeId const inner = __jakt_tmp396->as.RawPtr.value;
cast_type = ByteString::from_utf8_without_validation("reinterpret_cast"sv);
}
return cast_type;
}
VERIFY_NOT_REACHED();
case 2 /* Identity */:return ByteString::from_utf8_without_validation("static_cast"sv);default: VERIFY_NOT_REACHED();}/*switch end*/
 
}();
output.appendff(ByteString::from_utf8_without_validation("{}<{}>("sv),cast_type,TRY((this->codegen_type(final_type_id))));
TRY((this->codegen_expression(expr,output,true,false)));
output.append_code_point(static_cast<u32>(U')'));
}
goto __jakt_label_166;};/*case end*/
case 13 /* IsEnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IsEnumVariant;Jakt::types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
Jakt::ids::TypeId const& enum_type_id = __jakt_match_value.type_id;
{
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U'('));
}
ScopeGuard __jakt_var_123([&] {
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U')'));
}
});
ByteString const name = enum_variant.name();
Jakt::ids::EnumId const enum_id = [&]() -> Jakt::ids::EnumId { auto&& __jakt_match_variant = *this->program->get_type(enum_type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
return enum_id;};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return id;};/*case end*/
default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Unexpected type in IsEnumVariant: {}"sv),this->program->get_type(enum_type_id)));
}
}/*switch end*/
 
}();
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_id);
{auto&& __jakt_match_variant = enum_.record_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* SumEnum */:{
bool const is_boxed = enum_.is_boxed;
if (this->expr_codegens_to_this_pointer(expr)){
output.append(StringView::from_string_literal("this->"sv));
}
else {
TRY((this->codegen_expression(expr,output,true,true)));
if (is_boxed){
output.append(StringView::from_string_literal("->"sv));
}
else {
output.append(StringView::from_string_literal("."sv));
}

}

i64 variant_index = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = enum_.variants.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedEnumVariant variant = _magic_value.value();
{
if (variant.name() == name){
break;
}
variant_index++;
}

}
}

output.appendff(ByteString::from_utf8_without_validation("__jakt_init_index() == {} /* {} */"sv),variant_index,name);
}
goto __jakt_label_168;case 2 /* ValueEnum */:{
TRY((this->codegen_expression(expr,output,true,true)));
output.appendff(ByteString::from_utf8_without_validation("== {}{}::{}"sv),TRY((this->codegen_namespace_qualifier(enum_.scope_id,this->program->get_module(enum_id.module)->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))),enum_.name,name);
}
goto __jakt_label_168;default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Unexpected enum record type in IsEnumVariant: {}"sv),enum_.record_type));
}
goto __jakt_label_168;}/*switch end*/
}goto __jakt_label_168; __jakt_label_168:;;
}
goto __jakt_label_166;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_166; __jakt_label_166:;;
}
goto __jakt_label_162;};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
Jakt::types::CheckedBinaryOperator const& op = __jakt_match_value.op;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
TRY((this->codegen_binary_expression(expression,type_id,lhs,rhs,op,output,forward_error_with_try,syntactically_self_contained)));
}
goto __jakt_label_162;};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;Jakt::types::CheckedNumericConstant const& val = __jakt_match_value.val;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
ByteString const suffix = [&]() -> ByteString { auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* I64 */:return ByteString::from_utf8_without_validation("LL"sv);case 7 /* U64 */:case 8 /* USize */:return ByteString::from_utf8_without_validation("ULL"sv);default:return ByteString::from_utf8_without_validation(""sv);}/*switch end*/
 
}();
ByteString const type_name = TRY(([&]() -> ErrorOr<ByteString> { auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* USize */:return ByteString::from_utf8_without_validation("size_t"sv);default:return this->codegen_type(type_id);}/*switch end*/
 
}()));
output.append([&]() -> ByteString { auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& val = __jakt_match_value.value;
return __jakt_format(StringView::from_string_literal("static_cast<{}>({}{})"sv),type_name,val,suffix);};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
 
}());
}
goto __jakt_label_162;};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;JaktInternal::DynamicArray<Jakt::types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
{
if (var->name_for_codegen().is_scopable()){
if (var->owner_scope.has_value()){
output.append(TRY((this->codegen_namespace_qualifier(var->owner_scope.value(),false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
}
else {
{
JaktInternal::ArrayIterator<Jakt::types::CheckedNamespace> _magic = namespaces.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedNamespace> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedNamespace ns = _magic_value.value();
{
output.append(ns.name);
output.append(StringView::from_string_literal("::"sv));
}

}
}

}

}
output.append(var->name_for_codegen().as_name_for_use());
}
goto __jakt_label_162;};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
bool const& all_variants_constant = __jakt_match_value.all_variants_constant;
{
TRY((this->codegen_match(expr,match_cases,type_id,all_variants_constant,forward_error_with_try,output)));
}
goto __jakt_label_162;};/*case end*/
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedEnumVariantBinding const& arg = __jakt_match_value.arg;
Jakt::types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
{
ByteString const variant_name = enum_variant.name();
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_variant.enum_id());
ByteString const cpp_deref_operator = [&]() -> ByteString { auto __jakt_enum_value = enum_.is_boxed;
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("->"sv);}else {return ByteString::from_utf8_without_validation("."sv);} 
}();
ByteString section = __jakt_format(StringView::from_string_literal("as.{}"sv),variant_name);
bool is_common_field = false;
ByteString field_name = arg.name.value_or_lazy_evaluated([&] { return arg.binding; });
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
ByteString const var_name = this->program->get_variable(field->variable_id)->name_for_codegen().as_name_for_use();
if (var_name == field_name){
section = ByteString::from_utf8_without_validation("common.init_common"sv);
is_common_field = true;
break;
}
}

}
}

if ((!is_common_field) && (!(enum_variant.__jakt_init_index() == 3 /* StructLike */))){
field_name = ByteString::from_utf8_without_validation("value"sv);
}
TRY((this->codegen_expression(expr,output,true,true)));
output.append(cpp_deref_operator);
output.append(section);
output.append(StringView::from_string_literal("."sv));
output.append(field_name);
}
goto __jakt_label_162;};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::ids::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
{
if (repeat.has_value()){
NonnullRefPtr<typename Jakt::types::CheckedExpression> const repeat_val = repeat.value();
output.append(StringView::from_string_literal("DynamicArray<"sv));
output.append(TRY((this->codegen_type(inner_type_id))));
output.append(StringView::from_string_literal(">::filled("sv));
TRY((this->codegen_expression(repeat_val,output,true,false)));
output.append(StringView::from_string_literal(", "sv));
TRY((this->codegen_expression(vals.operator[](static_cast<i64>(0LL)),output,true,false)));
output.append(StringView::from_string_literal(")"sv));
}
else {
output.append(StringView::from_string_literal("DynamicArray<"sv));
output.append(TRY((this->codegen_type(inner_type_id))));
output.append(StringView::from_string_literal(">::create_with({"sv));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

TRY((this->codegen_expression(val,output,true,false)));
}

}
}

output.append(StringView::from_string_literal("})"sv));
}

}
goto __jakt_label_162;};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::ids::TypeId const& key_type_id = __jakt_match_value.key_type_id;
Jakt::ids::TypeId const& value_type_id = __jakt_match_value.value_type_id;
{
output.appendff(ByteString::from_utf8_without_validation("Dictionary<{}, {}>::create_with_entries({{"sv),TRY((this->codegen_type(key_type_id))),TRY((this->codegen_type(value_type_id))));
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> key__value__ = _magic_value.value();
{
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt__key__value__ = key__value__;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const key = jakt__key__value__.template get<0>();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const value = jakt__key__value__.template get<1>();

if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(StringView::from_string_literal("{"sv));
TRY((this->codegen_expression(key,output,true,false)));
output.append(StringView::from_string_literal(", "sv));
TRY((this->codegen_expression(value,output,true,false)));
output.append(StringView::from_string_literal("}"sv));
}

}
}

output.append(StringView::from_string_literal("})"sv));
}
goto __jakt_label_162;};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::ids::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
{
output.appendff(ByteString::from_utf8_without_validation("Set<{}>::create_with_values({{"sv),TRY((this->codegen_type(inner_type_id))));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> value = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

TRY((this->codegen_expression(value,output,true,false)));
}

}
}

output.append(StringView::from_string_literal("})"sv));
}
goto __jakt_label_162;};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
output.append(StringView::from_string_literal("Tuple{"sv));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

TRY((this->codegen_expression(val,output,true,false)));
}

}
}

output.append(StringView::from_string_literal("}"sv));
}
goto __jakt_label_162;};/*case end*/
case 30 /* DependentFunction */:{
this->compiler->panic(ByteString::from_utf8_without_validation("Dependent functions should have been resolved by now"sv));
}
goto __jakt_label_162;case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::types::CheckedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
{
JaktInternal::DynamicArray<ByteString> generated_captures = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedCapture> _magic = captures.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedCapture> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedCapture capture = _magic_value.value();
{
generated_captures.push([&]() -> ByteString { auto&& __jakt_match_variant = capture;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* ByValue */:return capture.common.init_common.name;case 4 /* AllByReference */:return ByteString::from_utf8_without_validation("&"sv);default:return __jakt_format(StringView::from_string_literal("&{}"sv),capture.common.init_common.name);}/*switch end*/
 
}());
}

}
}

JaktInternal::DynamicArray<ByteString> generated_params = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
generated_params.push(__jakt_format(StringView::from_string_literal("{} {}"sv),TRY((this->codegen_type(param.variable->type_id))),param.variable->name_for_codegen().as_name_for_definition()));
}

}
}

ByteString const return_type = TRY(([&]() -> ErrorOr<ByteString> { auto __jakt_enum_value = can_throw;
if (__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("ErrorOr<{}>"sv),TRY((this->codegen_type(return_type_id))));}else if (!__jakt_enum_value) {return this->codegen_type(return_type_id);}VERIFY_NOT_REACHED();
 
}()));
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
this->control_flow_state = last_control_flow.enter_function();
ScopeGuard __jakt_var_124([&] {
this->control_flow_state = last_control_flow;
});
output.appendff(ByteString::from_utf8_without_validation("[{}]({}) -> {} "sv),Jakt::utility::join(generated_captures,ByteString::from_utf8_without_validation(", "sv)),Jakt::utility::join(generated_params,ByteString::from_utf8_without_validation(", "sv)),return_type);
if (pseudo_function_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(pseudo_function_id.value());
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> const previous_function = this->current_function;
this->current_function = function;
ScopeGuard __jakt_var_125([&] {
this->current_function = previous_function;
});
TRY((this->codegen_lambda_block(can_throw,block,return_type_id,output)));
}
else {
TRY((this->codegen_lambda_block(can_throw,block,return_type_id,output)));
}

}
goto __jakt_label_162;};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
ByteString const& error_name = __jakt_match_value.error_name;
Jakt::types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
ByteString const try_var = this->fresh_var();
bool const can_affect_loop = [&]() -> bool { auto&& __jakt_match_variant = stmt->control_flow();
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* MayReturn */:return false;default:return true;}/*switch end*/
 
}();
ByteStringBuilder builder = ByteStringBuilder::create();
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
if (can_affect_loop){
this->control_flow_state.indirectly_inside_try_block = true;
builder.append(__jakt_format(StringView::from_string_literal("[&]() -> JaktInternal::ExplicitValueOrControlFlow<ErrorOr<void>, {}> {{\n"sv),TRY((this->codegen_function_return_type(this->current_function.value())))));
}
else {
builder.append(StringView::from_string_literal("auto "sv));
builder.append(try_var);
builder.append(StringView::from_string_literal(" = [&]() -> ErrorOr<void> {\n"sv));
this->control_flow_state.directly_inside_match = false;
this->control_flow_state.indirectly_inside_match = false;
}

this->control_flow_state.passes_through_try = true;
TRY((this->codegen_statement(stmt,builder)));
builder.append(StringView::from_string_literal(";\n"sv));
if (can_affect_loop){
builder.append(StringView::from_string_literal("return JaktInternal::ExplicitValue<ErrorOr<void>>({});"sv));
}
else {
builder.append(StringView::from_string_literal("return ErrorOr<void> {};"sv));
}

builder.append(StringView::from_string_literal("}();\n"sv));
if (can_affect_loop){
output.append(StringView::from_string_literal("auto "sv));
output.append(try_var);
output.append(StringView::from_string_literal(" = "sv));
output.append(TRY((this->control_flow_state.apply_control_flow_macro(builder.to_string(),this->current_function.value()->return_type_id,this->current_function.value()->can_throw))));
output.append(StringView::from_string_literal(";\n"sv));
}
else {
output.append(builder.to_string());
}

output.append(StringView::from_string_literal("if ("sv));
output.append(try_var);
output.append(StringView::from_string_literal(".is_error()) {"sv));
if (!error_name.is_empty()){
output.append(StringView::from_string_literal("auto "sv));
output.append(error_name);
output.append(StringView::from_string_literal(" = "sv));
output.append(try_var);
output.append(StringView::from_string_literal(".release_error();\n"sv));
}
TRY((this->codegen_block(catch_block,output)));
this->control_flow_state = last_control_flow;
output.append(StringView::from_string_literal("}"sv));
}
goto __jakt_label_162;};/*case end*/
case 32 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<Jakt::types::CheckedBlock> const& catch_block = __jakt_match_value.catch_block;
JaktInternal::Optional<ByteString> const& catch_name = __jakt_match_value.catch_name;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::ids::TypeId const& inner_type_id = __jakt_match_value.inner_type_id;
{
ByteString const fresh_var = this->fresh_var();
bool const is_void = inner_type_id.equals(Jakt::types::void_type_id());
ByteString const try_var = this->fresh_var();
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
this->control_flow_state.directly_inside_match = false;
this->control_flow_state.indirectly_inside_match = false;
this->control_flow_state.passes_through_try = true;
ScopeGuard __jakt_var_126([&] {
{
this->control_flow_state = last_control_flow;
}

});
if (!is_void){
output.append(StringView::from_string_literal("({ Optional<"sv));
output.append(TRY((this->codegen_type(inner_type_id))));
output.append(StringView::from_string_literal("> "sv));
output.append(fresh_var);
output.append(StringView::from_string_literal(";\n"sv));
}
output.append(StringView::from_string_literal("auto "sv));
output.append(try_var);
output.append(StringView::from_string_literal(" = [&]() -> ErrorOr<"sv));
output.append(TRY((this->codegen_type(inner_type_id))));
output.append(StringView::from_string_literal("> { return "sv));
TRY((this->codegen_expression(expr,output,is_void,false)));
if (is_void){
output.append(StringView::from_string_literal(", ErrorOr<void>{}"sv));
}
output.append(StringView::from_string_literal("; }();\n"sv));
if (catch_block.has_value()){
this->control_flow_state.indirectly_inside_match = last_control_flow.indirectly_inside_match;
this->control_flow_state.directly_inside_match = last_control_flow.directly_inside_match;
output.append(StringView::from_string_literal("if ("sv));
output.append(try_var);
output.append(StringView::from_string_literal(".is_error()) {"sv));
if (catch_name.has_value()){
output.append(StringView::from_string_literal("auto "sv));
output.append(catch_name.value());
output.append(StringView::from_string_literal(" = "sv));
output.append(try_var);
output.append(StringView::from_string_literal(".release_error();\n"sv));
}
if (catch_block.value().yielded_type.has_value()){
ByteString const label = this->fresh_label();
JaktInternal::Optional<Jakt::codegen::YieldMethod> const old_yield_method = this->yield_method;
this->yield_method = Jakt::codegen::YieldMethod::AssignAndGoto(fresh_var,label);
ScopeGuard __jakt_var_127([&] {
this->yield_method = old_yield_method;
});
TRY((this->codegen_block(catch_block.value(),output)));
output.append(label);
output.append(StringView::from_string_literal(":;\n"sv));
}
else {
TRY((this->codegen_block(catch_block.value(),output)));
}

if (!is_void){
output.append(StringView::from_string_literal("} else {"sv));
output.append(fresh_var);
output.append(StringView::from_string_literal(" = "sv));
output.append(try_var);
output.append(StringView::from_string_literal(".release_value();\n"sv));
}
output.append(StringView::from_string_literal("}\n"sv));
}
else if (!is_void){
output.append(StringView::from_string_literal("if (!"sv));
output.append(try_var);
output.append(StringView::from_string_literal(".is_error()) "sv));
output.append(fresh_var);
output.append(StringView::from_string_literal(" = "sv));
output.append(try_var);
output.append(StringView::from_string_literal(".release_value();\n"sv));
}
if (!is_void){
output.append(fresh_var);
if (catch_block.has_value()){
output.append(StringView::from_string_literal(".release_value()"sv));
}
output.append(StringView::from_string_literal("; })"sv));
}
}
goto __jakt_label_162;};/*case end*/
case 31 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
this->control_flow_state.directly_inside_match = false;
this->control_flow_state.indirectly_inside_match = false;
this->control_flow_state.passes_through_try = true;
ScopeGuard __jakt_var_128([&] {
{
this->control_flow_state = last_control_flow;
}

});
output.append(StringView::from_string_literal("MUST(("sv));
TRY((this->codegen_expression(expr,output,false,false)));
output.append(StringView::from_string_literal("))"sv));
}
goto __jakt_label_162;};/*case end*/
case 35 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::utility::todo(__jakt_format(StringView::from_string_literal("codegen_expression of bad AST node in {} at {}..{}"sv),this->compiler->get_file_path(span.file_id),span.start,span.end));
}
goto __jakt_label_162;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_162; __jakt_label_162:;;
}
return {};
}

bool Jakt::codegen::CodeGenerator::expr_codegens_to_this_pointer(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr) const {
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp397 = expr;
if (__jakt_tmp397->__jakt_init_index() == 24 /* Var */){
NonnullRefPtr<Jakt::types::CheckedVariable> const var = __jakt_tmp397->as.Var.var;
return (var->name == ByteString::from_utf8_without_validation("this"sv)) && !this->this_replacement.has_value();
}
else {
return false;
}

}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_prefix_unary(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,StringView const cpp_operator,ByteStringBuilder& output,bool const syntactically_self_contained) {
{
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U'('));
}
output.append(cpp_operator);
TRY((this->codegen_expression(expr,output,true,true)));
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U')'));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_postfix_unary(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,StringView const cpp_operator,ByteStringBuilder& output,bool const syntactically_self_contained) {
{
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U'('));
}
TRY((this->codegen_expression(expr,output,true,true)));
output.append(cpp_operator);
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U')'));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_match(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const match_cases,Jakt::ids::TypeId const type_id,bool const all_variants_constant,bool const forward_error_with_try,ByteStringBuilder& output) {
{
if (!Jakt::codegen::has_cpp_value(type_id)){
TRY((this->codegen_void_match(expr,match_cases,type_id,output))); return {};
}
if (!Jakt::codegen::has_control_flow<Jakt::types::CheckedMatchCase>(match_cases,true)){
TRY((this->codegen_value_match(expr,match_cases,type_id,forward_error_with_try,output))); return {};
}
ByteStringBuilder builder = ByteStringBuilder::create();
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
this->control_flow_state = this->control_flow_state.enter_match();
ByteString const cpp_match_result_type = TRY((this->codegen_type(type_id)));
NonnullRefPtr<typename Jakt::types::Type> const expr_type = this->program->get_type(expr->type());
JaktInternal::Optional<Jakt::codegen::YieldMethod> const old_yield_method = this->yield_method;
this->yield_method = Jakt::codegen::YieldMethod::ReturnExplicitValue(__jakt_format(StringView::from_string_literal("JaktInternal::ExplicitValue<{}>"sv),cpp_match_result_type));
ScopeGuard __jakt_var_129([&] {
this->yield_method = old_yield_method;
});
builder.append(StringView::from_string_literal("([&]() -> JaktInternal::ExplicitValueOrControlFlow<"sv));
builder.append(cpp_match_result_type);
builder.append(StringView::from_string_literal(", "sv));
builder.append(TRY((this->codegen_function_return_type(this->current_function.value()))));
builder.append(StringView::from_string_literal(">{\n"sv));
TRY((this->codegen_inner_match(expr,match_cases,type_id,builder)));
builder.append(StringView::from_string_literal("}()\n)"sv));
this->control_flow_state = last_control_flow;
output.append(TRY((this->control_flow_state.apply_control_flow_macro(builder.to_string(),this->current_function.value()->return_type_id,this->current_function.value()->can_throw))));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_value_match(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const match_cases,Jakt::ids::TypeId const type_id,bool const forward_error_with_try,ByteStringBuilder& output) {
{
bool const old_yields_erroror = this->yields_erroror;
this->yields_erroror = false;
ByteStringBuilder inner = ByteStringBuilder::create();
{
JaktInternal::Optional<Jakt::codegen::YieldMethod> const old_yield_method = this->yield_method;
Jakt::codegen::ControlFlowState const old_cf = this->control_flow_state;
ScopeGuard __jakt_var_130([&] {
this->yield_method = old_yield_method;
});
ScopeGuard __jakt_var_131([&] {
this->control_flow_state = old_cf;
});
this->control_flow_state = this->control_flow_state.enter_match();
this->control_flow_state.allowed_exits = Jakt::codegen::AllowedControlExits::JustReturn();
this->yield_method = Jakt::codegen::YieldMethod::Return();
TRY((this->codegen_inner_match(expr,match_cases,type_id,inner)));
}

ByteString const handler = [&]() -> ByteString { auto __jakt_enum_value = this->yields_erroror;
if (__jakt_enum_value) {return this->current_error_handler(forward_error_with_try);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}VERIFY_NOT_REACHED();
 
}();
this->yields_erroror |= old_yields_erroror;
if (!handler.is_empty()){
output.appendff(ByteString::from_utf8_without_validation("{}(([&]() -> ErrorOr<{}> {{ {} \n}}()))"sv),handler,TRY((this->codegen_type(type_id))),inner.to_string());
}
else {
output.appendff(ByteString::from_utf8_without_validation("[&]() -> {} {{ {} \n}}()"sv),TRY((this->codegen_type(type_id))),inner.to_string());
}

}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_inner_match(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const match_cases,Jakt::ids::TypeId const type_id,ByteStringBuilder& output) {
{
{auto&& __jakt_match_variant = *this->program->get_type(expr->type());
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
TRY((this->codegen_enum_match(this->program->get_enum(enum_id),expr,match_cases,type_id,output)));
}
return {};};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
TRY((this->codegen_enum_match(this->program->get_enum(enum_id),expr,match_cases,type_id,output)));
}
return {};};/*case end*/
default:{
TRY((this->codegen_generic_match(expr,match_cases,type_id,output)));
}
return {};}/*switch end*/
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_void_match(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const match_cases,Jakt::ids::TypeId const type_id,ByteStringBuilder& output) {
{
JaktInternal::Optional<Jakt::codegen::YieldMethod> const old_yield_method = this->yield_method;
ByteString const label = this->fresh_label();
ScopeGuard __jakt_var_132([&] {
this->yield_method = old_yield_method;
});
this->yield_method = Jakt::codegen::YieldMethod::AssignAndGoto(ByteString::from_utf8_without_validation("__VOID_MATCH_HAS_NO_VALUE"sv),label);
output.append_code_point(static_cast<u32>(U'{'));
TRY((this->codegen_inner_match(expr,match_cases,type_id,output)));
output.append_code_point(static_cast<u32>(U'}'));
output.appendff(ByteString::from_utf8_without_validation("goto {0}; {0}:;"sv),label);
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_returned_match(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const match_cases,Jakt::ids::TypeId const type_id,ByteStringBuilder& output) {
{
JaktInternal::Optional<Jakt::codegen::YieldMethod> const old_yield_method = this->yield_method;
ScopeGuard __jakt_var_133([&] {
this->yield_method = old_yield_method;
});
this->yield_method = Jakt::codegen::YieldMethod::Return();
output.append_code_point(static_cast<u32>(U'{'));
TRY((this->codegen_inner_match(expr,match_cases,type_id,output)));
output.append_code_point(static_cast<u32>(U'}'));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_generic_match(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const cases,Jakt::ids::TypeId const return_type_id,ByteStringBuilder& output) {
{
Jakt::ids::TypeId const byte_string_type_id = this->program->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),TRY((this->program->find_struct_in_prelude(ByteString::from_utf8_without_validation("String"sv))))),this->program->prelude_module_id(),false);
output.append(StringView::from_string_literal("auto __jakt_enum_value = "sv));
TRY((this->codegen_expression(expr,output,true,false)));
output.append(StringView::from_string_literal(";\n"sv));
bool first = true;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> cases_with_bindings = DynamicArray<Jakt::types::CheckedMatchCase>::create_with({});
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>,Jakt::types::CheckedMatchBody>> deferred_catch_all = JaktInternal::OptionalNone();
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(cases.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t case_index = _magic_value.value();
{
Jakt::types::CheckedMatchCase const match_case = cases.operator[](case_index);
if (match_case.patterns.size() == static_cast<size_t>(1ULL)){
Jakt::types::CheckedMatchPattern __jakt_tmp398 = match_case.patterns.operator[](static_cast<i64>(0LL));
if (__jakt_tmp398.__jakt_init_index() == 3 /* CatchAll */){
bool const has_arguments = __jakt_tmp398.as.CatchAll.has_arguments;
if (!has_arguments){
deferred_catch_all = Tuple{match_case.patterns.operator[](static_cast<i64>(0LL)).common.init_common.defaults, match_case.body};
continue;
}
else {
Jakt::utility::panic(ByteString::from_utf8_without_validation("Bindings should not be present in a generic else"sv));
}

}
}
if (!Jakt::codegen::case_has_bindings(match_case)){
if (!first){
output.append(StringView::from_string_literal("else "sv));
}
first = false;
output.append(StringView::from_string_literal("if ("sv));
bool first_pat = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchPattern> _magic = match_case.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchPattern pattern = _magic_value.value();
{
ScopeGuard __jakt_var_134([&] {
first_pat = false;
});
if (!first_pat){
output.append(StringView::from_string_literal("||"sv));
}
TRY((this->codegen_generic_pattern_condition(pattern,match_case.patterns.size() == static_cast<size_t>(1ULL),output)));
}

}
}

output.append(StringView::from_string_literal(") {"sv));
TRY((this->codegen_match_body(match_case.body,return_type_id,output)));
output.append_code_point(static_cast<u32>(U'}'));
}
else {
cases_with_bindings.push(match_case);
continue;
}

}

}
}

{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = cases_with_bindings.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchCase case_ = _magic_value.value();
{
Jakt::types::CheckedMatchBody const body = case_.body;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchPattern> _magic = case_.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchPattern pattern = _magic_value.value();
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const defaults = pattern.common.init_common.defaults;
ScopeGuard __jakt_var_135([&] {
first = false;
});
if (!first){
output.append(StringView::from_string_literal("else "sv));
}
output.append(StringView::from_string_literal("if ("sv));
TRY((this->codegen_generic_pattern_condition(pattern,true,output)));
output.append(StringView::from_string_literal(") {"sv));
ScopeGuard __jakt_var_136([&] {
output.append_code_point(static_cast<u32>(U'}'));
});
{auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
Jakt::ids::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
size_t const& variant_index = __jakt_match_value.index;
Jakt::ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
{
Jakt::types::CheckedEnum const enum_ = this->program->get_enum([&]() -> Jakt::ids::EnumId { auto&& __jakt_match_variant = *this->program->get_type(subject_type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
return enum_id;};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return id;};/*case end*/
default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Unexpected type in IsEnumVariant: {}"sv),this->program->get_type(subject_type_id)));
}
}/*switch end*/
 
}());
if (!args.is_empty()){
output.append(StringView::from_string_literal("auto& __jakt_match_value = __jakt_enum_value.as."sv));
output.append(enum_.variants.operator[](variant_index).name());
output.append(StringView::from_string_literal(";\n"sv));
{
JaktInternal::ArrayIterator<Jakt::parser::EnumVariantPatternArgument> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::EnumVariantPatternArgument> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::EnumVariantPatternArgument arg = _magic_value.value();
{
output.append(StringView::from_string_literal("auto& "sv));
output.append(arg.binding);
bool is_common_member = false;
JaktInternal::Optional<ByteString> __jakt_tmp399 = arg.name;
if (__jakt_tmp399.has_value()){
ByteString const name = __jakt_tmp399.value();
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const var = this->program->get_variable(field->variable_id);
if (var->name == name){
is_common_member = true;
break;
}
}

}
}

}
if (is_common_member){
output.append(StringView::from_string_literal(" = __jakt_enum_value.common.init_common."sv));
output.append(arg.name.value());
}
else {
output.append(StringView::from_string_literal(" = __jakt_match_value."sv));
output.append(arg.name.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("value"sv); }));
}

output.append(StringView::from_string_literal(";\n"sv));
}

}
}

}
}
goto __jakt_label_169;};/*case end*/
case 3 /* CatchAll */:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("unreachable"sv));
}
goto __jakt_label_169;case 1 /* Expression */:{
}
goto __jakt_label_169;case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;Jakt::ids::TypeId const& type = __jakt_match_value.type;
JaktInternal::Optional<Jakt::types::ClassInstanceRebind> const& rebind_name = __jakt_match_value.rebind_name;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
JaktInternal::Optional<Jakt::types::ClassInstanceRebind> __jakt_tmp400 = rebind_name;
if (__jakt_tmp400.has_value()){
Jakt::types::ClassInstanceRebind const rebind = __jakt_tmp400.value();
output.appendff(ByteString::from_utf8_without_validation("auto {} = NonnullRefPtr {{ *static_cast<RawPtr<{}>>(__jakt_enum_value.ptr()) }};\n"sv),rebind.name,TRY((this->codegen_type_possibly_as_namespace(type,true))));
}
}
goto __jakt_label_169;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
break;}goto __jakt_label_169; __jakt_label_169:;;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = defaults.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> default_ = _magic_value.value();
{
TRY((this->codegen_statement(default_,output)));
}

}
}

TRY((this->codegen_match_body(body,return_type_id,output)));
}

}
}

}

}
}

JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>,Jakt::types::CheckedMatchBody>> __jakt_tmp401 = deferred_catch_all;
if (__jakt_tmp401.has_value()){
JaktInternal::Tuple<JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>,Jakt::types::CheckedMatchBody> const catch_all_case = __jakt_tmp401.value();
JaktInternal::Tuple<JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>,Jakt::types::CheckedMatchBody> const defaults_body_ = catch_all_case;
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const defaults = defaults_body_.template get<0>();
Jakt::types::CheckedMatchBody const body = defaults_body_.template get<1>();

if (!first){
output.append(StringView::from_string_literal("else "sv));
}
output.append_code_point(static_cast<u32>(U'{'));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = defaults.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> default_ = _magic_value.value();
{
TRY((this->codegen_statement(default_,output)));
}

}
}

TRY((this->codegen_match_body(body,return_type_id,output)));
output.append_code_point(static_cast<u32>(U'}'));
}
if ((Jakt::codegen::has_cpp_value(return_type_id) || (!(this->yield_method.value().__jakt_init_index() == 0 /* ReturnExplicitValue */))) && !deferred_catch_all.has_value()){
output.append(StringView::from_string_literal("VERIFY_NOT_REACHED();\n"sv));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_generic_pattern_condition(Jakt::types::CheckedMatchPattern const& pattern,bool const is_parenthesized,ByteStringBuilder& output) {
{
{auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
size_t const& variant_index = __jakt_match_value.index;
{
output.appendff(ByteString::from_utf8_without_validation("__jakt_enum_value.__jakt_init_index() == {} /* {} */"sv),variant_index,name);
}
goto __jakt_label_170;};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expression;
{auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& to = __jakt_match_value.to;
{
bool const has_and = from.has_value() && to.has_value();
if (has_and && (!is_parenthesized)){
output.append_code_point(static_cast<u32>(U'('));
}
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> __jakt_tmp402 = from;
if (__jakt_tmp402.has_value()){
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = __jakt_tmp402.value();
output.append(StringView::from_string_literal("__jakt_enum_value >= "sv));
TRY((this->codegen_expression(expr,output,true,true)));
}
if (has_and){
output.append(StringView::from_string_literal("&&"sv));
}
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> __jakt_tmp403 = to;
if (__jakt_tmp403.has_value()){
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = __jakt_tmp403.value();
output.append(StringView::from_string_literal("__jakt_enum_value < "sv));
TRY((this->codegen_expression(expr,output,true,true)));
}
if (has_and && (!is_parenthesized)){
output.append_code_point(static_cast<u32>(U')'));
}
}
goto __jakt_label_171;};/*case end*/
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
{
if (!val){
output.append_code_point(static_cast<u32>(U'!'));
}
output.append(StringView::from_string_literal("__jakt_enum_value"sv));
}
goto __jakt_label_171;};/*case end*/
default:{
if (!is_parenthesized){
output.append_code_point(static_cast<u32>(U'('));
}
output.append(StringView::from_string_literal("__jakt_enum_value == "sv));
TRY((this->codegen_expression(expr,output,true,true)));
if (!is_parenthesized){
output.append_code_point(static_cast<u32>(U')'));
}
}
goto __jakt_label_171;}/*switch end*/
}goto __jakt_label_171; __jakt_label_171:;;goto __jakt_label_170;};/*case end*/
case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;Jakt::ids::TypeId const& type_id = __jakt_match_value.type;
{
output.appendff(ByteString::from_utf8_without_validation("JaktInternal::lenient_is<{}>(__jakt_enum_value.ptr())"sv),TRY((this->codegen_type_possibly_as_namespace(type_id,true))));
}
goto __jakt_label_170;};/*case end*/
case 3 /* CatchAll */:{
this->compiler->panic(ByteString::from_utf8_without_validation("catch all has no condition, should be emitted separately"sv));
}
goto __jakt_label_170;default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_170; __jakt_label_170:;;
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_enum_match(Jakt::types::CheckedEnum const enum_,NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const match_cases,Jakt::ids::TypeId const type_id,ByteStringBuilder& output) {
{
ByteStringBuilder subject_builder = ByteStringBuilder::create();
TRY((this->codegen_expression(expr,subject_builder,true,false)));
ByteString const subject = subject_builder.to_string();
bool const needs_deref = enum_.is_boxed && [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(subject,ByteString::from_utf8_without_validation("*this"sv));
if (enum_.underlying_type_id.equals(Jakt::types::void_type_id())){
output.append(StringView::from_string_literal("auto&& __jakt_match_variant = "sv));
if (needs_deref){
output.append(StringView::from_string_literal("*"sv));
}
TRY((this->codegen_expression(expr,output,true,false)));
output.append(StringView::from_string_literal(";\n"sv));
output.append(StringView::from_string_literal("switch(__jakt_match_variant.__jakt_init_index()) {\n"sv));
bool has_default = false;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = match_cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchCase match_case = _magic_value.value();
{
Jakt::types::CheckedMatchBody const body = match_case.body;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchPattern> patterns_without_bindings = DynamicArray<Jakt::types::CheckedMatchPattern>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchPattern> _magic = match_case.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchPattern pattern = _magic_value.value();
{
if (!Jakt::codegen::pattern_has_bindings(pattern)){
patterns_without_bindings.push(pattern);
continue;
}
{auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
Jakt::ids::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
size_t const& index = __jakt_match_value.index;
Jakt::ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
{
NonnullRefPtr<typename Jakt::types::Type> const enum_type = this->program->get_type(subject_type_id);
Jakt::ids::EnumId const enum_id = [&]() -> Jakt::ids::EnumId { auto&& __jakt_match_variant = *enum_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return id;};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return id;};/*case end*/
default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Expected enum type"sv));
}
}/*switch end*/
 
}();
Jakt::types::CheckedEnum const match_case_enum = this->program->get_enum(enum_id);
Jakt::types::CheckedEnumVariant const variant = match_case_enum.variants.operator[](index);
output.appendff(ByteString::from_utf8_without_validation("case {} /* {} */: {{\n"sv),index,variant.name());
{auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
{
}
goto __jakt_label_173;};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
if (!args.is_empty()){
output.appendff(ByteString::from_utf8_without_validation("auto&& __jakt_match_value = __jakt_match_variant.as.{};"sv),name);
Jakt::parser::EnumVariantPatternArgument const arg = args.operator[](static_cast<i64>(0LL));
NonnullRefPtr<Jakt::types::CheckedVariable> const var = TRY((this->program->find_var_in_scope(scope_id,arg.binding,false,JaktInternal::OptionalNone()))).value();
output.append(TRY((this->codegen_type(var->type_id))));
if (!var->is_mutable){
output.append(StringView::from_string_literal(" const"sv));
}
output.append(StringView::from_string_literal("& "sv));
output.append(arg.binding);
output.append(StringView::from_string_literal(" = __jakt_match_value.value;\n"sv));
}
}
goto __jakt_label_173;};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
if (!args.is_empty()){
output.appendff(ByteString::from_utf8_without_validation("auto&& __jakt_match_value = __jakt_match_variant.as.{};"sv),name);
{
JaktInternal::ArrayIterator<Jakt::parser::EnumVariantPatternArgument> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::parser::EnumVariantPatternArgument> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::parser::EnumVariantPatternArgument arg = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const var = TRY((this->program->find_var_in_scope(scope_id,arg.binding,false,JaktInternal::OptionalNone()))).value();
output.append(TRY((this->codegen_type(var->type_id))));
if (!var->is_mutable){
output.append(StringView::from_string_literal(" const"sv));
}
output.append(StringView::from_string_literal("& "sv));
output.append(arg.binding);
ByteString const accessor = arg.name.value_or_lazy_evaluated([&] { return arg.binding; });
bool is_common_member = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = enum_.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedVariable> const var = this->program->get_variable(field->variable_id);
if (var->name == accessor){
is_common_member = true;
break;
}
}

}
}

if (is_common_member){
output.append(StringView::from_string_literal(" = __jakt_match_variant.common.init_common."sv));
output.append(accessor);
}
else {
output.append(StringView::from_string_literal(" = __jakt_match_value."sv));
output.append(accessor);
}

output.append(StringView::from_string_literal(";\n"sv));
}

}
}

}
}
goto __jakt_label_173;};/*case end*/
default:{
Jakt::utility::todo(__jakt_format(StringView::from_string_literal("codegen_enum_match match variant else: {}"sv),variant));
}
goto __jakt_label_173;}/*switch end*/
break;}goto __jakt_label_173; __jakt_label_173:;;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = pattern.common.init_common.defaults.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> default_ = _magic_value.value();
{
TRY((this->codegen_statement(default_,output)));
}

}
}

TRY((this->codegen_match_body(body,type_id,output)));
output.append(StringView::from_string_literal("};/*case end*/\n"sv));
}
goto __jakt_label_172;};/*case end*/
case 3 /* CatchAll */:{
has_default = true;
output.append(StringView::from_string_literal("default: {\n"sv));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = pattern.common.init_common.defaults.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> default_ = _magic_value.value();
{
TRY((this->codegen_statement(default_,output)));
}

}
}

TRY((this->codegen_match_body(body,type_id,output)));
output.append(StringView::from_string_literal("};/*case end*/\n"sv));
}
goto __jakt_label_172;default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Matching enum subject with non-enum value"sv));
}
goto __jakt_label_172;}/*switch end*/
break;}goto __jakt_label_172; __jakt_label_172:;;
}

}
}

if (!patterns_without_bindings.is_empty()){
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchPattern> _magic = patterns_without_bindings.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchPattern pattern = _magic_value.value();
{
{auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
size_t const& index = __jakt_match_value.index;
{
output.appendff(ByteString::from_utf8_without_validation("case {} /* {} */:"sv),index,name);
}
goto __jakt_label_174;};/*case end*/
case 3 /* CatchAll */:{
has_default = true;
output.append(StringView::from_string_literal("default:"sv));
}
goto __jakt_label_174;default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Matching enum subject with non-enum value"sv));
}
goto __jakt_label_174;}/*switch end*/
break;}goto __jakt_label_174; __jakt_label_174:;;
}

}
}

TRY((this->codegen_match_body(body,type_id,output)));
}
}

}
}

if (!has_default){
if (enum_.variants.size() != Jakt::codegen::count_match_cases(match_cases)){
Jakt::utility::panic(ByteString::from_utf8_without_validation("Inexhaustive match statement"sv));
}
output.append(StringView::from_string_literal("default: VERIFY_NOT_REACHED();"sv));
}
output.append(StringView::from_string_literal("}/*switch end*/\n"sv));
}
else {
output.append(StringView::from_string_literal("switch ("sv));
TRY((this->codegen_expression(expr,output,true,false)));
output.append(StringView::from_string_literal(") {\n"sv));
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = match_cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchCase match_case = _magic_value.value();
{
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchPattern> _magic = match_case.patterns.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchPattern> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchPattern pattern = _magic_value.value();
{
{auto&& __jakt_match_variant = pattern;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
{
output.appendff(ByteString::from_utf8_without_validation("case {}::{}:"sv),enum_.name,name);
}
goto __jakt_label_175;};/*case end*/
case 3 /* CatchAll */:{
output.append(StringView::from_string_literal("default:"sv));
}
goto __jakt_label_175;default:{
Jakt::utility::todo(__jakt_format(StringView::from_string_literal("underlying type enum match, match_case: {}"sv),match_case));
}
goto __jakt_label_175;}/*switch end*/
break;}goto __jakt_label_175; __jakt_label_175:;;
}

}
}

TRY((this->codegen_match_body(match_case.body,type_id,output)));
}

}
}

output.append(StringView::from_string_literal("}/*switch end*/\n"sv));
}

if (Jakt::codegen::are_loop_exits_allowed(this->control_flow_state.allowed_exits)){
{auto&& __jakt_match_variant = this->yield_method.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Return */:case 1 /* AssignAndGoto */:output.append(this->break_statement());goto __jakt_label_176;case 0 /* ReturnExplicitValue */:{
}
goto __jakt_label_176;default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_176; __jakt_label_176:;;
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_match_body(Jakt::types::CheckedMatchBody const body,Jakt::ids::TypeId const return_type_id,ByteStringBuilder& output) {
{
{auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.value;
{
TRY((this->codegen_block(block,output)));
if (!Jakt::codegen::has_cpp_value(return_type_id)){
{auto&& __jakt_match_variant = this->yield_method.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Return */:TRY((this->codegen_return(JaktInternal::OptionalNone(),output)));goto __jakt_label_178;case 0 /* ReturnExplicitValue */:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Void match should not be using ExplicitValue"sv));
}
goto __jakt_label_178;case 1 /* AssignAndGoto */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AssignAndGoto;ByteString const& label = __jakt_match_value.label;
output.appendff(ByteString::from_utf8_without_validation("goto {};"sv),label);goto __jakt_label_178;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_178; __jakt_label_178:;;
}
}
goto __jakt_label_177;};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp404 = expr;
if (__jakt_tmp404->__jakt_init_index() == 28 /* Block */){
Jakt::types::CheckedBlock const block = __jakt_tmp404->as.Block.block;
TRY((this->codegen_block(block,output)));
output.append(StringView::from_string_literal("VERIFY_NOT_REACHED();\n"sv));
}
else {
{auto&& __jakt_match_variant = this->yield_method.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Return */:TRY((this->codegen_value_return(expr,output)));goto __jakt_label_179;case 0 /* ReturnExplicitValue */:{
if ((expr->type().equals(Jakt::types::void_type_id()) || expr->type().equals(Jakt::types::never_type_id())) || (expr->type().equals(Jakt::types::unknown_type_id()) && (!(expr->__jakt_init_index() == 25 /* OptionalNone */)))){
Jakt::utility::panic(ByteString::from_utf8_without_validation("Void match should not be using ExplicitValue"sv));
}
else {
output.append(StringView::from_string_literal("return JaktInternal::ExplicitValue("sv));
TRY((this->codegen_expression(expr,output,true,false)));
output.append(StringView::from_string_literal(");\n"sv));
}

}
goto __jakt_label_179;case 1 /* AssignAndGoto */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AssignAndGoto;ByteString const& label = __jakt_match_value.label;
{
if (!Jakt::codegen::has_cpp_value(expr->type())){
TRY((this->codegen_expression(expr,output,true,false)));
output.appendff(ByteString::from_utf8_without_validation(";goto {};"sv),label);
}
else {
Jakt::utility::panic(ByteString::from_utf8_without_validation("Only matches yielding void can use AssignAndGoto"sv));
}

}
goto __jakt_label_179;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_179; __jakt_label_179:;;
}

}
goto __jakt_label_177;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_177; __jakt_label_177:;;
}
return {};
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_function_return_type(NonnullRefPtr<Jakt::types::CheckedFunction> const function) {
{
if (function->is_static() && (function->name_for_codegen().as_name_for_use() == ByteString::from_utf8_without_validation("main"sv))){
return ByteString::from_utf8_without_validation("ErrorOr<int>"sv);
}
ByteString const type_name = TRY((this->codegen_type(function->return_type_id)));
if (function->can_throw){
return __jakt_format(StringView::from_string_literal("ErrorOr<{}>"sv),type_name);
}
return type_name;
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_binary_expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expression,Jakt::ids::TypeId const type_id,NonnullRefPtr<typename Jakt::types::CheckedExpression> const lhs,NonnullRefPtr<typename Jakt::types::CheckedExpression> const rhs,Jakt::types::CheckedBinaryOperator const op,ByteStringBuilder& output,bool const forward_error_with_try,bool const syntactically_self_contained) {
{
JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> __jakt_tmp405 = op.trait_implementation;
if (__jakt_tmp405.has_value()){
Jakt::types::OperatorTraitImplementation const implementation = __jakt_tmp405.value();
TRY((this->codegen_method_call(lhs,implementation.call_expression,false,output,forward_error_with_try,syntactically_self_contained)));
return {};
}
if (op.op.__jakt_init_index() == 20 /* NoneCoalescing */){
Jakt::ids::TypeId const rhs_type_id = rhs->type();
NonnullRefPtr<typename Jakt::types::Type> const rhs_type = this->program->get_type(rhs_type_id);
bool const rhs_can_throw = rhs->can_throw();
if (rhs_can_throw){
output.append(this->current_error_handler(true));
output.append(StringView::from_string_literal("(("sv));
}
TRY((this->codegen_expression(lhs,output,true,true)));
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp406 = rhs_type;
if (__jakt_tmp406->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const id = __jakt_tmp406->as.GenericInstance.id;
if (this->program->get_struct(id).name_for_codegen().as_name_for_definition() == ByteString::from_utf8_without_validation("Optional"sv)){
if (rhs_can_throw){
output.append(StringView::from_string_literal(".try_value_or_lazy_evaluated_optional"sv));
}
else {
output.append(StringView::from_string_literal(".value_or_lazy_evaluated_optional"sv));
}

}
else {
if (rhs_can_throw){
output.append(StringView::from_string_literal(".try_value_or_lazy_evaluated"sv));
}
else {
output.append(StringView::from_string_literal(".value_or_lazy_evaluated"sv));
}

}

}
else {
if (rhs_can_throw){
output.append(StringView::from_string_literal(".try_value_or_lazy_evaluated"sv));
}
else {
output.append(StringView::from_string_literal(".value_or_lazy_evaluated"sv));
}

}

if (rhs_can_throw){
output.append(StringView::from_string_literal("([&]() -> ErrorOr<"sv));
output.append(TRY((this->codegen_type(rhs_type_id))));
output.append(StringView::from_string_literal("> { return "sv));
}
else {
output.append(StringView::from_string_literal("([&] { return "sv));
}

TRY((this->codegen_expression(rhs,output,true,false)));
output.append(StringView::from_string_literal("; })"sv));
if (rhs_can_throw){
output.append(StringView::from_string_literal("))"sv));
}
return {};
}
if (op.op.__jakt_init_index() == 32 /* NoneCoalescingAssign */){
ByteStringBuilder lhs_builder = ByteStringBuilder::create();
ByteStringBuilder rhs_builder = ByteStringBuilder::create();
TRY((this->codegen_expression(lhs,lhs_builder,true,false)));
TRY((this->codegen_expression(rhs,rhs_builder,true,false)));
ByteString const lhs_string = lhs_builder.to_string();
ByteString const rhs_string = rhs_builder.to_string();
ByteString const var = this->fresh_var();
output.appendff(ByteString::from_utf8_without_validation("({{ auto&& {0} = {1}; if (!{0}.has_value()) {0} = {2}; }})"sv),var,lhs_string,rhs_string);
return {};
}
if (op.op.__jakt_init_index() == 17 /* ArithmeticRightShift */){
output.append(StringView::from_string_literal("JaktInternal::arithmetic_shift_right("sv));
TRY((this->codegen_expression(lhs,output,true,false)));
output.append(StringView::from_string_literal(","sv));
TRY((this->codegen_expression(rhs,output,true,false)));
output.append(StringView::from_string_literal(")"sv));
return {};
}
if (op.op.__jakt_init_index() == 21 /* Assign */){
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp407 = lhs;
if (__jakt_tmp407->__jakt_init_index() == 14 /* IndexedDictionary */){
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = __jakt_tmp407->as.IndexedDictionary.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const index = __jakt_tmp407->as.IndexedDictionary.index;
TRY((this->codegen_expression(expr,output,true,true)));
output.append(StringView::from_string_literal(".set("sv));
TRY((this->codegen_expression(index,output,true,false)));
output.append(StringView::from_string_literal(", "sv));
TRY((this->codegen_expression(rhs,output,true,false)));
output.append(StringView::from_string_literal(")"sv));
return {};
}
}
if (this->program->is_integer(type_id)){
{auto&& __jakt_match_variant = op.op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */:case 1 /* Subtract */:case 2 /* Multiply */:case 3 /* Divide */:case 4 /* Modulo */:{
if (this->compiler->optimize){
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U'('));
}
TRY((this->codegen_unchecked_binary_op(lhs,rhs,op.op,type_id,output)));
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U')'));
}
}
else {
TRY((this->codegen_checked_binary_op(lhs,rhs,op.op,type_id,output)));
}

return {};
}
goto __jakt_label_180;case 27 /* AddAssign */:case 28 /* SubtractAssign */:case 29 /* MultiplyAssign */:case 31 /* DivideAssign */:case 30 /* ModuloAssign */:{
if (this->compiler->optimize){
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U'('));
}
TRY((this->codegen_unchecked_binary_op_assignment(lhs,rhs,op.op,type_id,output)));
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U')'));
}
}
else {
TRY((this->codegen_checked_binary_op_assignment(lhs,rhs,op.op,type_id,output)));
}

}
goto __jakt_label_180;default:{
}
goto __jakt_label_180;}/*switch end*/
}goto __jakt_label_180; __jakt_label_180:;;
}
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U'('));
}
TRY((this->codegen_expression(lhs,output,true,true)));
output.append([&]() -> StringView { auto&& __jakt_match_variant = op.op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */:return StringView::from_string_literal(" + "sv);case 1 /* Subtract */:return StringView::from_string_literal(" - "sv);case 2 /* Multiply */:return StringView::from_string_literal(" * "sv);case 4 /* Modulo */:return StringView::from_string_literal(" % "sv);case 3 /* Divide */:return StringView::from_string_literal(" / "sv);case 21 /* Assign */:return StringView::from_string_literal(" = "sv);case 27 /* AddAssign */:return StringView::from_string_literal(" += "sv);case 28 /* SubtractAssign */:return StringView::from_string_literal(" -= "sv);case 29 /* MultiplyAssign */:return StringView::from_string_literal(" *= "sv);case 30 /* ModuloAssign */:return StringView::from_string_literal(" %= "sv);case 31 /* DivideAssign */:return StringView::from_string_literal(" /= "sv);case 22 /* BitwiseAndAssign */:return StringView::from_string_literal(" &= "sv);case 23 /* BitwiseOrAssign */:return StringView::from_string_literal(" |= "sv);case 24 /* BitwiseXorAssign */:return StringView::from_string_literal(" ^= "sv);case 25 /* BitwiseLeftShiftAssign */:return StringView::from_string_literal(" <<= "sv);case 26 /* BitwiseRightShiftAssign */:return StringView::from_string_literal(" >>= "sv);case 9 /* Equal */:return StringView::from_string_literal(" == "sv);case 10 /* NotEqual */:return StringView::from_string_literal(" != "sv);case 5 /* LessThan */:return StringView::from_string_literal(" < "sv);case 6 /* LessThanOrEqual */:return StringView::from_string_literal(" <= "sv);case 7 /* GreaterThan */:return StringView::from_string_literal(" > "sv);case 8 /* GreaterThanOrEqual */:return StringView::from_string_literal(" >= "sv);case 18 /* LogicalAnd */:return StringView::from_string_literal(" && "sv);case 19 /* LogicalOr */:return StringView::from_string_literal(" || "sv);case 11 /* BitwiseAnd */:return StringView::from_string_literal(" & "sv);case 13 /* BitwiseOr */:return StringView::from_string_literal(" | "sv);case 12 /* BitwiseXor */:return StringView::from_string_literal(" ^ "sv);case 16 /* ArithmeticLeftShift */:return StringView::from_string_literal(" << "sv);case 14 /* BitwiseLeftShift */:return StringView::from_string_literal(" << "sv);case 15 /* BitwiseRightShift */:return StringView::from_string_literal(" >> "sv);default:{
Jakt::utility::todo(__jakt_format(StringView::from_string_literal("codegen_binary_expression {}"sv),op));
}
}/*switch end*/
 
}());
TRY((this->codegen_expression(rhs,output,true,true)));
if (syntactically_self_contained){
output.append_code_point(static_cast<u32>(U')'));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_unchecked_binary_op(NonnullRefPtr<typename Jakt::types::CheckedExpression> const lhs,NonnullRefPtr<typename Jakt::types::CheckedExpression> const rhs,Jakt::parser::BinaryOperator const op,Jakt::ids::TypeId const type_id,ByteStringBuilder& output) {
{
output.append(StringView::from_string_literal("static_cast<"sv));
output.append(TRY((this->codegen_type(type_id))));
output.append(StringView::from_string_literal(">("sv));
TRY((this->codegen_expression(lhs,output,true,false)));
output.append([&]() -> StringView { auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */:return StringView::from_string_literal(" + "sv);case 1 /* Subtract */:return StringView::from_string_literal(" - "sv);case 2 /* Multiply */:return StringView::from_string_literal(" * "sv);case 3 /* Divide */:return StringView::from_string_literal(" / "sv);case 4 /* Modulo */:return StringView::from_string_literal(" % "sv);default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Checked binary operation codegen is not supported for BinaryOperator::{}"sv),op));
}
}/*switch end*/
 
}());
TRY((this->codegen_expression(rhs,output,true,false)));
output.append(StringView::from_string_literal(")"sv));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_checked_binary_op(NonnullRefPtr<typename Jakt::types::CheckedExpression> const lhs,NonnullRefPtr<typename Jakt::types::CheckedExpression> const rhs,Jakt::parser::BinaryOperator const op,Jakt::ids::TypeId const type_id,ByteStringBuilder& output) {
{
output.append(StringView::from_string_literal("JaktInternal::"sv));
output.append([&]() -> StringView { auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */:return StringView::from_string_literal("checked_add"sv);case 1 /* Subtract */:return StringView::from_string_literal("checked_sub"sv);case 2 /* Multiply */:return StringView::from_string_literal("checked_mul"sv);case 3 /* Divide */:return StringView::from_string_literal("checked_div"sv);case 4 /* Modulo */:return StringView::from_string_literal("checked_mod"sv);default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Checked binary operation codegen is not supported for BinaryOperator::{}"sv),op));
}
}/*switch end*/
 
}());
output.append(StringView::from_string_literal("<"sv));
output.append(TRY((this->codegen_type(type_id))));
output.append(StringView::from_string_literal(">("sv));
TRY((this->codegen_expression(lhs,output,true,false)));
output.append(StringView::from_string_literal(","sv));
TRY((this->codegen_expression(rhs,output,true,false)));
output.append(StringView::from_string_literal(")"sv));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_unchecked_binary_op_assignment(NonnullRefPtr<typename Jakt::types::CheckedExpression> const lhs,NonnullRefPtr<typename Jakt::types::CheckedExpression> const rhs,Jakt::parser::BinaryOperator const op,Jakt::ids::TypeId const type_id,ByteStringBuilder& output) {
{
output.append(StringView::from_string_literal("{"sv));
output.append(StringView::from_string_literal("auto& _jakt_ref = "sv));
TRY((this->codegen_expression(lhs,output,true,false)));
output.append(StringView::from_string_literal(";"sv));
output.append(StringView::from_string_literal("_jakt_ref = static_cast<"sv));
output.append(TRY((this->codegen_type(type_id))));
output.append(StringView::from_string_literal(">(_jakt_ref "sv));
output.append([&]() -> StringView { auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* AddAssign */:return StringView::from_string_literal(" + "sv);case 28 /* SubtractAssign */:return StringView::from_string_literal(" - "sv);case 29 /* MultiplyAssign */:return StringView::from_string_literal(" * "sv);case 31 /* DivideAssign */:return StringView::from_string_literal(" / "sv);case 30 /* ModuloAssign */:return StringView::from_string_literal(" % "sv);default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Checked binary operation assignment codegen is not supported for BinaryOperator::{}"sv),op));
}
}/*switch end*/
 
}());
TRY((this->codegen_expression(rhs,output,true,false)));
output.append(StringView::from_string_literal(");"sv));
output.append(StringView::from_string_literal("}"sv));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_checked_binary_op_assignment(NonnullRefPtr<typename Jakt::types::CheckedExpression> const lhs,NonnullRefPtr<typename Jakt::types::CheckedExpression> const rhs,Jakt::parser::BinaryOperator const op,Jakt::ids::TypeId const type_id,ByteStringBuilder& output) {
{
output.append(StringView::from_string_literal("{"sv));
output.append(StringView::from_string_literal("auto& _jakt_ref = "sv));
TRY((this->codegen_expression(lhs,output,true,false)));
output.append(StringView::from_string_literal(";"sv));
output.append(StringView::from_string_literal("_jakt_ref = JaktInternal::"sv));
output.append([&]() -> StringView { auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 27 /* AddAssign */:return StringView::from_string_literal("checked_add"sv);case 28 /* SubtractAssign */:return StringView::from_string_literal("checked_sub"sv);case 29 /* MultiplyAssign */:return StringView::from_string_literal("checked_mul"sv);case 31 /* DivideAssign */:return StringView::from_string_literal("checked_div"sv);case 30 /* ModuloAssign */:return StringView::from_string_literal("checked_mod"sv);default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Checked binary operation assignment codegen is not supported for BinaryOperator::{}"sv),op));
}
}/*switch end*/
 
}());
output.append(StringView::from_string_literal("<"sv));
output.append(TRY((this->codegen_type(type_id))));
output.append(StringView::from_string_literal(">(_jakt_ref, "sv));
TRY((this->codegen_expression(rhs,output,true,false)));
output.append(StringView::from_string_literal(");"sv));
output.append(StringView::from_string_literal("}"sv));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_method_call(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,Jakt::types::CheckedCall const call,bool const is_optional,ByteStringBuilder& output,bool const forward_error_with_try,bool const syntactically_self_contained) {
{
ByteString const error_handler = [&]() -> ByteString { auto __jakt_enum_value = call.callee_throws;
if (__jakt_enum_value) {return this->current_error_handler(forward_error_with_try);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}VERIFY_NOT_REACHED();
 
}();
if (!error_handler.is_empty()){
output.appendff(ByteString::from_utf8_without_validation("{}(("sv),error_handler);
}
TRY((this->codegen_method_call_unwrapped(expr,call,is_optional,output,syntactically_self_contained && error_handler.is_empty())));
if (!error_handler.is_empty()){
output.append(StringView::from_string_literal("))"sv));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_method_call_unwrapped(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,Jakt::types::CheckedCall const call,bool const is_optional,ByteStringBuilder& output,bool const syntactically_self_contained) {
{
Function<ErrorOr<void>(ByteStringBuilder&, bool)> const generate_object = [this, &expr](ByteStringBuilder& output, bool syntactically_self_contained) -> ErrorOr<void> {{
TRY((this->codegen_expression_and_deref_if_generic_and_needed(expr,output,syntactically_self_contained)));
}
return {};
}
;
if (call.function_id.has_value() && (call.force_inline.__jakt_init_index() == 2 /* ForceInline */)){
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(call.function_id.value());
bool const is_mutable = expr->is_mutable(this->program) && function->params.first().value().variable->is_mutable;
NonnullRefPtr<typename Jakt::types::Type> const reference_type = [&]() -> NonnullRefPtr<typename Jakt::types::Type> { auto __jakt_enum_value = is_mutable;
if (__jakt_enum_value) {return Jakt::types::Type::MutableReference(Jakt::parser::CheckedQualifiers(false),expr->type());}else if (!__jakt_enum_value) {return Jakt::types::Type::Reference(Jakt::parser::CheckedQualifiers(false),expr->type());}VERIFY_NOT_REACHED();
 
}();
NonnullRefPtr<Jakt::types::CheckedVariable> const var = Jakt::types::CheckedVariable::__jakt_create(ByteString::from_utf8_without_validation("self"sv),this->program->find_or_add_type_id(reference_type,expr->type().module,false),is_mutable,expr->span(),JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone());
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params = DynamicArray<Jakt::types::CheckedParameter>::create_with({Jakt::types::CheckedParameter(false,var,JaktInternal::OptionalNone())});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.operator[](JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)}).iterator();
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

if (function->block.statements.is_empty()){
warnln(StringView::from_string_literal("Shit, block is empty in function ({}): {}"sv),call.function_id.value(),function);
Jakt::abort();
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> const lambda = Jakt::types::CheckedExpression::Function(JaktInternal::OptionalNone(),DynamicArray<Jakt::types::CheckedCapture>::create_with({}),params,function->can_throw,function->return_type_id,function->block,expr->span(),Jakt::types::unknown_type_id(),call.function_id,function->function_scope_id);
JaktInternal::Optional<ByteString> const old_this_replacement = this->this_replacement;
this->this_replacement = ByteString::from_utf8_without_validation("self"sv);
TRY((this->codegen_expression(lambda,output,true,false)));
this->this_replacement = old_this_replacement;
output.append(StringView::from_string_literal("("sv));
TRY((generate_object(output,false)));
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = call.args.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> ___arg__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt_____arg__ = ___arg__;
ByteString const _ = jakt_____arg__.template get<0>();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const arg = jakt_____arg__.template get<1>();

output.append(StringView::from_string_literal(","sv));
TRY((this->codegen_expression(arg,output,true,false)));
}

}
}

output.append(StringView::from_string_literal(")"sv));
return {};
}
NonnullRefPtr<typename Jakt::types::Type> const expression_type = this->program->get_type(expr->type());
Jakt::parser::ExternalName const name = call.name_for_codegen();
bool const object_is_this = this->expr_codegens_to_this_pointer(expr);
ByteString const field_accessor = [&]() -> ByteString { auto&& __jakt_match_variant = name;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Operator */:return ByteString::from_utf8_without_validation(""sv);default:{auto&& __jakt_match_variant = *expression_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* RawPtr */:return ByteString::from_utf8_without_validation("->"sv);case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{auto __jakt_enum_value = (this->program->get_struct(id).record_type.__jakt_init_index() == 1 /* Class */) && (!object_is_this);
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("->"sv);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation("."sv);}VERIFY_NOT_REACHED();
}};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
{auto __jakt_enum_value = (this->program->get_struct(id).record_type.__jakt_init_index() == 1 /* Class */) && (!object_is_this);
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("->"sv);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation("."sv);}VERIFY_NOT_REACHED();
}};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
{auto __jakt_enum_value = this->program->get_enum(id).is_boxed && (!object_is_this);
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation("->"sv);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation("."sv);}VERIFY_NOT_REACHED();
}};/*case end*/
default:{auto __jakt_enum_value = expression_type->is_builtin() && (!(expression_type->__jakt_init_index() == 13 /* JaktString */));
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation("."sv);}VERIFY_NOT_REACHED();
}}/*switch end*/
}}/*switch end*/
 
}();
Function<ErrorOr<void>()> const generate_method_name = [this, &call, &name, &output]() -> ErrorOr<void> {{
if (name.is_prefix()){
output.append(name.as_name_for_use());
return {};
}
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = call.type_args;
if (!generic_parameters.is_empty()){
output.append(StringView::from_string_literal("template "sv));
}
output.append(name.as_name_for_use());
if (!generic_parameters.is_empty()){
JaktInternal::DynamicArray<ByteString> types = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId gen_param = _magic_value.value();
{
types.push(TRY((this->codegen_type_possibly_as_namespace(gen_param,false))));
}

}
}

output.appendff(ByteString::from_utf8_without_validation("<{}>"sv),Jakt::utility::join(types,ByteString::from_utf8_without_validation(", "sv)));
}
}
return {};
}
;
bool const is_called_as_method = (!name.is_prefix()) && ((!field_accessor.is_empty()) || ((!is_optional) && (name.__jakt_init_index() == 2 /* Operator */)));
bool const needs_wrapping_parens = ((syntactically_self_contained && (name.__jakt_init_index() == 2 /* Operator */)) && (!is_optional)) && (!call.callee_throws);
if (needs_wrapping_parens){
output.append_code_point(static_cast<u32>(U'('));
}
ScopeGuard __jakt_var_137([&] {
if (needs_wrapping_parens){
output.append_code_point(static_cast<u32>(U')'));
}
});
if (is_called_as_method){
if (object_is_this && ((!(name.__jakt_init_index() == 2 /* Operator */)) && [&]() -> bool { auto&& __jakt_match_variant = *expression_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */:case 20 /* GenericInstance */:case 24 /* Enum */:case 21 /* GenericEnumInstance */:return true;default:return false;}/*switch end*/
 
}())){
output.append(StringView::from_string_literal("this->"sv));
}
else {
TRY((generate_object(output,true)));
output.append(field_accessor);
}

}
else {
TRY((generate_method_name()));
if (!(name.__jakt_init_index() == 2 /* Operator */)){
output.append(StringView::from_string_literal("("sv));
}
TRY((generate_object(output,true)));
}

if (is_optional){
output.append(StringView::from_string_literal("map([&](auto& _value) { return _value"sv));
ByteString access_operator = ByteString::from_utf8_without_validation("."sv);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp408 = expression_type;
if (__jakt_tmp408->__jakt_init_index() == 20 /* GenericInstance */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = __jakt_tmp408->as.GenericInstance.args;
if (args.size() > static_cast<size_t>(0ULL)){
{auto&& __jakt_match_variant = *this->program->get_type(args.operator[](static_cast<i64>(0LL)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
if (this->program->get_struct(id).record_type.__jakt_init_index() == 1 /* Class */){
access_operator = ByteString::from_utf8_without_validation("->"sv);
}
}
goto __jakt_label_181;};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
{
if (this->program->get_struct(id).record_type.__jakt_init_index() == 1 /* Class */){
access_operator = ByteString::from_utf8_without_validation("->"sv);
}
}
goto __jakt_label_181;};/*case end*/
default:{
}
goto __jakt_label_181;}/*switch end*/
}goto __jakt_label_181; __jakt_label_181:;;
}
}
output.append(access_operator);
}
if (is_called_as_method){
TRY((generate_method_name()));
if (!(name.__jakt_init_index() == 2 /* Operator */)){
output.append(StringView::from_string_literal("("sv));
}
}
bool first = is_called_as_method;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = call.args.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> ___expr__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt_____expr__ = ___expr__;
ByteString const _ = jakt_____expr__.template get<0>();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = jakt_____expr__.template get<1>();

if (first){
first = false;
}
else {
output.append(StringView::from_string_literal(","sv));
}

TRY((this->codegen_expression(expr,output,true,first && (name.__jakt_init_index() == 2 /* Operator */))));
}

}
}

if (!(name.__jakt_init_index() == 2 /* Operator */)){
output.append_code_point(static_cast<u32>(U')'));
}
if (is_optional){
output.append(StringView::from_string_literal("; })"sv));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_call(Jakt::types::CheckedCall const call,ByteStringBuilder& output,bool const forward_error_with_try) {
{
ByteString const error_handler = [&]() -> ByteString { auto __jakt_enum_value = call.callee_throws;
if (__jakt_enum_value) {return this->current_error_handler(forward_error_with_try);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}VERIFY_NOT_REACHED();
 
}();
if (!error_handler.is_empty()){
output.appendff(ByteString::from_utf8_without_validation("{}(("sv),error_handler);
}
TRY((this->codegen_call_unwrapped(call,output)));
if (!error_handler.is_empty()){
output.append(StringView::from_string_literal("))"sv));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_call_unwrapped(Jakt::types::CheckedCall const call,ByteStringBuilder& output) {
{
if (call.function_id.has_value() && this->program->get_function(call.function_id.value())->is_comptime){
output.appendff(ByteString::from_utf8_without_validation("fail_comptime_call<{}, \"Comptime function {} called outside Jakt compiler\">()"sv),TRY((this->codegen_type(call.return_type))),call.name);
return {};
}
{auto __jakt_enum_value = call.name;
if ((__jakt_enum_value == ByteString::from_utf8_without_validation("print"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("println"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("eprintln"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("eprint"sv))||(__jakt_enum_value == ByteString::from_utf8_without_validation("format"sv))) {{
ByteString const helper = [&]() -> ByteString { auto __jakt_enum_value = call.name;
if (__jakt_enum_value == ByteString::from_utf8_without_validation("print"sv)) {return ByteString::from_utf8_without_validation("out"sv);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("println"sv)) {return ByteString::from_utf8_without_validation("outln"sv);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("eprint"sv)) {return ByteString::from_utf8_without_validation("warn"sv);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("eprintln"sv)) {return ByteString::from_utf8_without_validation("warnln"sv);}else if (__jakt_enum_value == ByteString::from_utf8_without_validation("format"sv)) {return ByteString::from_utf8_without_validation("__jakt_format"sv);}else {return ByteString::from_utf8_without_validation(""sv);} 
}();
output.append(helper);
output.append(StringView::from_string_literal("("sv));
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(call.args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const __expr_ = call.args.operator[](i);
ByteString const _ = __expr_.template get<0>();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = __expr_.template get<1>();

TRY((this->codegen_expression(expr,output,true,false)));
if (i != JaktInternal::checked_sub(call.args.size(),static_cast<size_t>(1ULL))){
output.append(StringView::from_string_literal(","sv));
}
}

}
}

output.append(StringView::from_string_literal(")"sv));
}
goto __jakt_label_182;}else {{
bool close_enum_type_wrapper = false;
if (call.function_id.has_value()){
Jakt::ids::FunctionId const function_id = call.function_id.value();
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->program->get_function(function_id);
NonnullRefPtr<Jakt::types::Module> const type_module = this->program->get_module(function_id.module);
this->used_modules.add(function_id.module);
if ((function->type.__jakt_init_index() == 3 /* ImplicitConstructor */) || (function->type.__jakt_init_index() == 5 /* ExternalClassConstructor */)){
Jakt::ids::TypeId const type_id = call.return_type;
NonnullRefPtr<typename Jakt::types::Type> const type = this->program->get_type(type_id);
Jakt::parser::ExternalName const name = call.name_for_codegen();
if ((!name.is_prefix()) && name.is_scopable()){
output.append(TRY((this->codegen_namespace_path(call))));
}
{auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(struct_id);
if (struct_.record_type.__jakt_init_index() == 1 /* Class */){
output.append(call.name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal("::"sv));
output.append(struct_.create_function_name.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("__jakt_create"sv); }));
}
else {
output.append(call.name_for_codegen().as_name_for_use());
}

}
goto __jakt_label_183;};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(id);
if (struct_.record_type.__jakt_init_index() == 1 /* Class */){
output.append(struct_.name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal("<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(TRY((this->codegen_type(arg))));
}

}
}

output.append(StringView::from_string_literal(">::"sv));
output.append(struct_.create_function_name.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("__jakt_create"sv); }));
}
else {
output.append(call.name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal("<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(TRY((this->codegen_type(arg))));
}

}
}

output.append(StringView::from_string_literal(">"sv));
}

}
goto __jakt_label_183;};/*case end*/
default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Should be unreachable"sv));
}
goto __jakt_label_183;}/*switch end*/
}goto __jakt_label_183; __jakt_label_183:;;
}
else if (function->type.__jakt_init_index() == 4 /* ImplicitEnumConstructor */){
{auto&& __jakt_match_variant = *this->program->get_type(function->return_type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(enum_id);
NonnullRefPtr<Jakt::types::Module> const enum_type_module = this->program->get_module(enum_id.module);
output.append(TRY((this->codegen_type_possibly_as_namespace(call.return_type,true))));
output.append(StringView::from_string_literal("::"sv));
output.append(call.name_for_codegen().as_name_for_use());
}
goto __jakt_label_184;};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
{
Jakt::utility::todo(ByteString::from_utf8_without_validation("codegen generic enum instance"sv));
}
goto __jakt_label_184;};/*case end*/
default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("constructor expected enum type"sv));
}
goto __jakt_label_184;}/*switch end*/
}goto __jakt_label_184; __jakt_label_184:;;
}
else {
Jakt::parser::ExternalName const name = call.name_for_codegen();
if ((!name.is_prefix()) && name.is_scopable()){
output.append(TRY((this->codegen_namespace_path(call))));
}
output.append(call.name_for_codegen().as_name_for_use());
}

}
else {
Jakt::parser::ExternalName const name = call.name_for_codegen();
if ((!name.is_prefix()) && name.is_scopable()){
output.append(TRY((this->codegen_namespace_path(call))));
}
output.append(call.name_for_codegen().as_name_for_use());
}

JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = call.type_args;
if (!generic_parameters.is_empty()){
JaktInternal::DynamicArray<ByteString> types = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId gen_param = _magic_value.value();
{
types.push(TRY((this->codegen_type_possibly_as_namespace(gen_param,false))));
}

}
}

output.appendff(ByteString::from_utf8_without_validation("<{}>"sv),Jakt::utility::join(types,ByteString::from_utf8_without_validation(", "sv)));
}
JaktInternal::DynamicArray<ByteString> arguments = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = call.args.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> arg = _magic_value.value();
{
ByteStringBuilder builder = ByteStringBuilder::create();
TRY((this->codegen_expression(arg.template get<1>(),builder,true,false)));
arguments.push(builder.to_string());
}

}
}

output.appendff(ByteString::from_utf8_without_validation("({})"sv),Jakt::utility::join(arguments,ByteString::from_utf8_without_validation(","sv)));
}
goto __jakt_label_182;}}goto __jakt_label_182; __jakt_label_182:;;
}
return {};
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_namespace_path(Jakt::types::CheckedCall const call) {
{
if (call.function_id.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const func = this->program->get_function(call.function_id.value());
if (func->owner_scope.has_value()){
bool is_prelude = false;
NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(func->owner_scope.value());
if (scope->relevant_type_id.has_value()){
{auto&& __jakt_match_variant = *this->program->get_type(scope->relevant_type_id.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
is_prelude = this->program->get_module(id.module)->is_prelude();
}
goto __jakt_label_185;};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
{
is_prelude = this->program->get_module(id.module)->is_prelude();
}
goto __jakt_label_185;};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
{
is_prelude = this->program->get_module(id.module)->is_prelude();
}
goto __jakt_label_185;};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
{
is_prelude = this->program->get_module(id.module)->is_prelude();
}
goto __jakt_label_185;};/*case end*/
default:{
}
goto __jakt_label_185;}/*switch end*/
}goto __jakt_label_185; __jakt_label_185:;;
}
return this->codegen_namespace_qualifier(func->owner_scope.value(),is_prelude,false,call.name_for_codegen().as_name_for_use(),func->owner_scope_generics);
}
}
ByteString output = ByteString::from_utf8_without_validation(""sv);
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedNamespace> _magic = call.namespace_.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedNamespace> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolvedNamespace namespace_ = _magic_value.value();
{
if ((index == JaktInternal::checked_sub(call.namespace_.size(),static_cast<size_t>(1ULL))) && (namespace_.name == call.name_for_codegen().as_name_for_use())){
break;
}
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,namespace_.name_for_codegen().as_name_for_use());
if (namespace_.generic_parameters.has_value()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("<"sv));
size_t i = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = namespace_.generic_parameters.value().iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId param = _magic_value.value();
{
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,TRY((this->codegen_type(param))));
if (i != JaktInternal::checked_sub(namespace_.generic_parameters.value().size(),static_cast<size_t>(1ULL))){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(","sv));
}
++i;
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(">"sv));
}
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("::"sv));
++index;
}

}
}

return output;
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_block(Jakt::types::CheckedBlock const block,ByteStringBuilder& output) {
{
output.append(StringView::from_string_literal("{\n"sv));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = block.statements.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> statement = _magic_value.value();
{
TRY((this->codegen_statement(statement,output)));
}

}
}

output.append(StringView::from_string_literal("}\n"sv));
}
return {};
}

StringView Jakt::codegen::CodeGenerator::break_statement() const {
{
{auto __jakt_enum_value = this->control_flow_state.directly_inside_match;
if (__jakt_enum_value) {return StringView::from_string_literal("return JaktInternal::LoopBreak{};"sv);}else if (!__jakt_enum_value) {return StringView::from_string_literal("break;"sv);}VERIFY_NOT_REACHED();
}
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_statement(NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement,ByteStringBuilder& output) {
{
bool add_newline = true;
if (this->debug_info.statement_span_comments && (statement->span().has_value() && add_newline)){
output.appendff(ByteString::from_utf8_without_validation("\n#line {}\n"sv),TRY((this->debug_info.span_to_source_location(statement->span().value()))));
}
{auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
{
this->yields_erroror = true;
output.append(StringView::from_string_literal("return "sv));
TRY((this->codegen_expression(expr,output,true,false)));
output.append(StringView::from_string_literal(";"sv));
}
goto __jakt_label_186;};/*case end*/
case 10 /* Continue */:{
output.append([&]() -> StringView { auto __jakt_enum_value = this->control_flow_state.directly_inside_match;
if (__jakt_enum_value) {return StringView::from_string_literal("return JaktInternal::LoopContinue{};"sv);}else if (!__jakt_enum_value) {return StringView::from_string_literal("continue;"sv);}VERIFY_NOT_REACHED();
 
}());
}
goto __jakt_label_186;case 9 /* Break */:{
output.append(this->break_statement());
}
goto __jakt_label_186;case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
{
TRY((this->codegen_expression(expr,output,true,false)));
output.append(StringView::from_string_literal(";"sv));
}
goto __jakt_label_186;};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& statement = __jakt_match_value.statement;
{
output.append(StringView::from_string_literal("ScopeGuard "sv));
output.append(this->fresh_var());
output.append(StringView::from_string_literal("([&] {\n"sv));
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
bool const old_inside_defer = this->inside_defer;
this->control_flow_state.directly_inside_match = false;
this->control_flow_state.indirectly_inside_match = false;
this->inside_defer = true;
TRY((this->codegen_statement(statement,output)));
output.append(StringView::from_string_literal("});"sv));
this->control_flow_state = last_control_flow;
this->inside_defer = old_inside_defer;
}
goto __jakt_label_186;};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& val = __jakt_match_value.val;
TRY((this->codegen_return(val,output)));goto __jakt_label_186;};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
{
if (this->debug_info.statement_span_comments && statement->span().has_value()){
output.appendff(ByteString::from_utf8_without_validation("\n#line {}\n"sv),TRY((this->debug_info.span_to_source_location(statement->span().value()))));
}
output.append(StringView::from_string_literal("for (;;)"sv));
add_newline = false;
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
this->control_flow_state = last_control_flow.enter_loop();
TRY((this->codegen_block(block,output)));
this->control_flow_state = last_control_flow;
}
goto __jakt_label_186;};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
{
if (this->debug_info.statement_span_comments && statement->span().has_value()){
output.appendff(ByteString::from_utf8_without_validation("\n#line {}\n"sv),TRY((this->debug_info.span_to_source_location(statement->span().value()))));
}
output.append(StringView::from_string_literal("while ("sv));
TRY((this->codegen_expression(condition,output,true,false)));
output.append(StringView::from_string_literal(")"sv));
{
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
this->control_flow_state = last_control_flow.enter_loop();
TRY((this->codegen_block(block,output)));
this->control_flow_state = last_control_flow;
}

add_newline = false;
}
goto __jakt_label_186;};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
{
TRY((this->codegen_block(block,output)));
}
goto __jakt_label_186;};/*case end*/
case 14 /* Garbage */:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Garbage statement in codegen"sv));
}
goto __jakt_label_186;case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename Jakt::types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
{
TRY((this->codegen_statement(var_decl,output)));
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = vars.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> v = _magic_value.value();
{
TRY((this->codegen_statement(v,output)));
}

}
}

}
goto __jakt_label_186;};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;Jakt::ids::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& init = __jakt_match_value.init;
{
NonnullRefPtr<Jakt::types::CheckedVariable> const var = this->program->get_variable(var_id);
NonnullRefPtr<typename Jakt::types::Type> const var_type = this->program->get_type(var->type_id);
output.append(TRY((this->codegen_type(var->type_id))));
output.append(StringView::from_string_literal(" "sv));
if ((!var->is_mutable) && (!((var_type->__jakt_init_index() == 27 /* Reference */) || (var_type->__jakt_init_index() == 28 /* MutableReference */)))){
output.append(StringView::from_string_literal("const "sv));
}
output.append(var->name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal(" = "sv));
TRY((this->codegen_expression(init,output,true,false)));
output.append(StringView::from_string_literal(";"sv));
}
goto __jakt_label_186;};/*case end*/
case 13 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;JaktInternal::DynamicArray<ByteString> const& lines = __jakt_match_value.lines;
{
{
JaktInternal::ArrayIterator<ByteString> _magic = lines.iterator();
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
ByteString line = _magic_value.value();
{
ByteString escaped_line = line;
escaped_line = escaped_line.replace(ByteString::from_utf8_without_validation("\\\""sv),ByteString::from_utf8_without_validation("\""sv));
escaped_line = escaped_line.replace(ByteString::from_utf8_without_validation("\\\\"sv),ByteString::from_utf8_without_validation("\\"sv));
output.append(escaped_line);
}

}
}

}
goto __jakt_label_186;};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
{
if (this->debug_info.statement_span_comments && statement->span().has_value()){
output.appendff(ByteString::from_utf8_without_validation("\n#line {}\n"sv),TRY((this->debug_info.span_to_source_location(statement->span().value()))));
}
output.append(StringView::from_string_literal("if ("sv));
TRY((this->codegen_expression(condition,output,true,false)));
output.append(StringView::from_string_literal(")"sv));
TRY((this->codegen_block(then_block,output)));
if (else_statement.has_value()){
output.append(StringView::from_string_literal("else "sv));
TRY((this->codegen_statement(else_statement.value(),output)));
}
add_newline = false;
}
goto __jakt_label_186;};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
bool const is_void = expr.has_value() && expr.value()->type().equals(Jakt::types::void_type_id());
{auto&& __jakt_match_variant = this->yield_method.value();
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Return */:{
TRY((this->codegen_return(expr,output)));
}
goto __jakt_label_187;case 0 /* ReturnExplicitValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ReturnExplicitValue;ByteString const& ctor = __jakt_match_value.ctor;
{
if (is_void){
TRY((this->codegen_statement(Jakt::types::CheckedStatement::Expression(expr.value(),span),output)));
}
output.append(StringView::from_string_literal("return "sv));
output.append(ctor);
output.append_code_point(static_cast<u32>(U'('));
if (!is_void){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> __jakt_tmp409 = expr;
if (__jakt_tmp409.has_value()){
NonnullRefPtr<typename Jakt::types::CheckedExpression> const value = __jakt_tmp409.value();
TRY((this->codegen_expression(value,output,true,false)));
}
}
output.append(StringView::from_string_literal(");"sv));
}
goto __jakt_label_187;};/*case end*/
case 1 /* AssignAndGoto */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AssignAndGoto;ByteString const& name = __jakt_match_value.name;
ByteString const& label = __jakt_match_value.label;
{
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> __jakt_tmp410 = expr;
if (__jakt_tmp410.has_value()){
NonnullRefPtr<typename Jakt::types::CheckedExpression> const val = __jakt_tmp410.value();
if (is_void){
TRY((this->codegen_expression(val,output,true,false)));
output.append_code_point(static_cast<u32>(U';'));
}
else {
output.appendff(ByteString::from_utf8_without_validation("{}.emplace("sv),name);
TRY((this->codegen_expression(val,output,true,false)));
output.append(StringView::from_string_literal(");"sv));
}

}
output.append(StringView::from_string_literal("goto "sv));
output.append(label);
output.append(StringView::from_string_literal(";\n"sv));
}
goto __jakt_label_187;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_187; __jakt_label_187:;;
}
goto __jakt_label_186;};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}goto __jakt_label_186; __jakt_label_186:;;
if (add_newline){
output.append(StringView::from_string_literal("\n"sv));
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_return(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const val,ByteStringBuilder& output) {
{
{auto __jakt_enum_value = val.has_value();
if (__jakt_enum_value) {TRY((this->codegen_value_return(val.value(),output))); return {};}else if (!__jakt_enum_value) {{
output.append([&]() -> StringView { auto __jakt_enum_value = this->current_function.value()->can_throw || this->control_flow_state.indirectly_inside_match;
if (__jakt_enum_value) {return StringView::from_string_literal("return {};"sv);}else if (!__jakt_enum_value) {return StringView::from_string_literal("return;"sv);}VERIFY_NOT_REACHED();
 
}());
}
return {};}VERIFY_NOT_REACHED();
}
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_value_return(NonnullRefPtr<typename Jakt::types::CheckedExpression> const val,ByteStringBuilder& output) {
{
{auto&& __jakt_match_variant = *val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
TRY((this->codegen_returned_match(expr,match_cases,type_id,output))); return {};};/*case end*/
default:{auto __jakt_enum_value = this->current_function.value()->can_throw;
if (__jakt_enum_value) {{
NonnullRefPtr<typename Jakt::types::Type> const type = this->program->get_type(val->type());
ByteString result = ByteString::from_utf8_without_validation(""sv);
if ((type->__jakt_init_index() == 0 /* Void */) || (type->__jakt_init_index() == 17 /* Never */)){
TRY((this->codegen_expression(val,output,true,false)));
output.append(StringView::from_string_literal("; return {}"sv));
}
else {
output.append(StringView::from_string_literal("return "sv));
TRY((this->codegen_expression(val,output,false,false)));
}

output.append(StringView::from_string_literal(";"sv));
}
return {};}else if (!__jakt_enum_value) {{
output.append(StringView::from_string_literal("return "sv));
TRY((this->codegen_expression(val,output,true,false)));
output.append(StringView::from_string_literal(";"sv));
}
return {};}VERIFY_NOT_REACHED();
}}/*switch end*/
}
}
return {};
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_type(Jakt::ids::TypeId const type_id) {
{
return this->codegen_type_possibly_as_namespace(type_id,false);
}
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_type_possibly_as_namespace(Jakt::ids::TypeId const type_id,bool const as_namespace) {
{
this->used_modules.add(type_id.module);
ByteString qualifiers = ByteString::from_utf8_without_validation(""sv);
if ((!as_namespace) && this->program->get_type(type_id)->common.init_common.qualifiers.is_immutable){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(qualifiers,ByteString::from_utf8_without_validation(" const"sv));
}
JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> __jakt_tmp411 = this->generic_inferences;
if (__jakt_tmp411.has_value()){
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const mappings = __jakt_tmp411.value();
JaktInternal::Optional<Jakt::ids::TypeId> __jakt_tmp412 = mappings.get(type_id);
if (__jakt_tmp412.has_value()){
Jakt::ids::TypeId const id = __jakt_tmp412.value();
return TRY((this->codegen_type_possibly_as_namespace(id,as_namespace))) + qualifiers;
}
}
return TRY(([&]() -> ErrorOr<ByteString> { auto&& __jakt_match_variant = *this->program->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return ByteString::from_utf8_without_validation("void"sv);case 1 /* Bool */:return ByteString::from_utf8_without_validation("bool"sv);case 2 /* U8 */:return ByteString::from_utf8_without_validation("u8"sv);case 3 /* U16 */:return ByteString::from_utf8_without_validation("u16"sv);case 4 /* U32 */:return ByteString::from_utf8_without_validation("u32"sv);case 5 /* U64 */:return ByteString::from_utf8_without_validation("u64"sv);case 6 /* I8 */:return ByteString::from_utf8_without_validation("i8"sv);case 7 /* I16 */:return ByteString::from_utf8_without_validation("i16"sv);case 8 /* I32 */:return ByteString::from_utf8_without_validation("i32"sv);case 9 /* I64 */:return ByteString::from_utf8_without_validation("i64"sv);case 10 /* F32 */:return ByteString::from_utf8_without_validation("f32"sv);case 11 /* F64 */:return ByteString::from_utf8_without_validation("f64"sv);case 12 /* Usize */:return ByteString::from_utf8_without_validation("size_t"sv);case 13 /* JaktString */:return ByteString::from_utf8_without_validation("ByteString"sv);case 14 /* CChar */:return ByteString::from_utf8_without_validation("char"sv);case 15 /* CInt */:return ByteString::from_utf8_without_validation("int"sv);case 17 /* Never */:return ByteString::from_utf8_without_validation("void"sv);case 31 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;Jakt::types::Value const& value = __jakt_match_value.value;
{
NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter = Jakt::interpreter::Interpreter::create(this->compiler,this->program,Jakt::types::TypecheckFunctions::__jakt_create([](Jakt::parser::ParsedBlock parsed_block, Jakt::ids::ScopeId parent_scope_id, Jakt::types::SafetyMode safety_mode, JaktInternal::Optional<Jakt::ids::TypeId> yield_type_hint, JaktInternal::Optional<Jakt::ids::FunctionId> containing_function_id) -> ErrorOr<Jakt::types::CheckedBlock> {{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Cannot typecheck a const block"sv));
}
}
,[](NonnullRefPtr<Jakt::types::CheckedFunction> function) -> ErrorOr<Jakt::ids::FunctionId> {{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Cannot typecheck a const function"sv));
}
}
),DynamicArray<Jakt::utility::Span>::create_with({}));
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = TRY((Jakt::interpreter::value_to_checked_expression(value,interpreter)));
ByteStringBuilder builder = ByteStringBuilder::create();
TRY((this->codegen_expression(expr,builder,true,false)));
return builder.to_string();
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{auto __jakt_enum_value = this->program->get_type(type_id)->is_boxed(this->program);
if (__jakt_enum_value) {return TRY((this->codegen_type_possibly_as_namespace(type_id,true))) + ByteString::from_utf8_without_validation("*"sv);}else if (!__jakt_enum_value) {return TRY((this->codegen_type(type_id))) + ByteString::from_utf8_without_validation("*"sv);}VERIFY_NOT_REACHED();
}};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{auto __jakt_enum_value = this->program->get_type(type_id)->common.init_common.qualifiers.is_immutable;
if (__jakt_enum_value) {return TRY((this->codegen_type(type_id))) + ByteString::from_utf8_without_validation("&"sv);}else if (!__jakt_enum_value) {return TRY((this->codegen_type(type_id))) + ByteString::from_utf8_without_validation(" const&"sv);}VERIFY_NOT_REACHED();
}};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return TRY((this->codegen_type(type_id))) + ByteString::from_utf8_without_validation("&"sv);};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return this->codegen_generic_type_instance(id,args,as_namespace);};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
JaktInternal::Optional<Jakt::ids::TypeId> const implements_type = this->program->get_struct(id).implements_type;
{auto __jakt_enum_value = implements_type.has_value();
if (__jakt_enum_value) {return this->codegen_type_possibly_as_namespace(implements_type.value(),as_namespace);}else if (!__jakt_enum_value) {return this->codegen_struct_type(id,as_namespace);}VERIFY_NOT_REACHED();
}
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return this->codegen_enum_type(id,as_namespace);};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
ByteStringBuilder builder = ByteStringBuilder::create();
TRY((this->codegen_generic_enum_instance(id,args,as_namespace,builder)));
return builder.to_string();
}
VERIFY_NOT_REACHED();
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return name;};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
{
ByteStringBuilder builder = ByteStringBuilder::create();
builder.append(StringView::from_string_literal("Function<"sv));
if (can_throw){
builder.append(StringView::from_string_literal("ErrorOr<"sv));
}
builder.append(TRY((this->codegen_type(return_type_id))));
if (can_throw){
builder.append(StringView::from_string_literal(">"sv));
}
builder.append(StringView::from_string_literal("("sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId param = _magic_value.value();
{
if (first){
first = false;
}
else {
builder.append(StringView::from_string_literal(", "sv));
}

builder.append(TRY((this->codegen_type(param))));
}

}
}

builder.append(StringView::from_string_literal(")>"sv));
return builder.to_string();
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* GenericTraitInstance */:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Generic trait instance in codegen"sv));
}
default:{
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Invalid type in codegen_type({})"sv),TRY((this->program->type_name(type_id,true)))));
}
}/*switch end*/
 
}())) + qualifiers;
}
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_generic_type_instance(Jakt::ids::StructId const id,JaktInternal::DynamicArray<Jakt::ids::TypeId> const args,bool const as_namespace) {
{
ByteString output = ByteString::from_utf8_without_validation(""sv);
NonnullRefPtr<Jakt::types::Module> const type_module = this->program->get_module(id.module);
ByteString namespace_ = ByteString::from_utf8_without_validation(""sv);
if (type_module->is_prelude()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(namespace_,ByteString::from_utf8_without_validation("JaktInternal::"sv));
}
JaktInternal::Optional<Jakt::ids::StructId> const inner_weak_ptr_struct_id = TRY((this->program->check_and_extract_weak_ptr(id,args)));
if (inner_weak_ptr_struct_id.has_value()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("WeakPtr<"sv));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,namespace_);
Jakt::ids::StructId const inner_struct_id = inner_weak_ptr_struct_id.value();
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(inner_struct_id);
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,TRY((this->codegen_namespace_qualifier(struct_.scope_id,type_module->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,struct_.name_for_codegen().as_name_for_use());
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(">"sv));
}
else {
Jakt::types::CheckedStruct const struct_ = this->program->get_struct(id);
bool const acquired_by_ref = (!as_namespace) && (struct_.record_type.__jakt_init_index() == 1 /* Class */);
if (acquired_by_ref){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("NonnullRefPtr<"sv));
}
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,namespace_);
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,TRY((this->codegen_namespace_qualifier(struct_.scope_id,type_module->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,struct_.name_for_codegen().as_name_for_use());
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation("<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId type_id = _magic_value.value();
{
if (!first){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(","sv));
}
else {
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,TRY((this->codegen_type(type_id))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(">"sv));
if (acquired_by_ref){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(">"sv));
}
}

return output;
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_generic_enum_instance(Jakt::ids::EnumId const id,JaktInternal::DynamicArray<Jakt::ids::TypeId> const args,bool const as_namespace,ByteStringBuilder& output) {
{
bool close_tag = false;
Jakt::types::CheckedEnum const enum_ = this->program->get_enum(id);
if ((!as_namespace) && enum_.is_boxed){
output.append(StringView::from_string_literal("NonnullRefPtr<"sv));
ByteString const qualifier = TRY((this->codegen_namespace_qualifier(enum_.scope_id,this->program->get_module(id.module)->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if (!qualifier.is_empty()){
output.append(StringView::from_string_literal("typename "sv));
output.append(qualifier);
}
output.append(enum_.name);
close_tag = true;
}
else {
ByteString const qualifier = TRY((this->codegen_namespace_qualifier(enum_.scope_id,this->program->get_module(id.module)->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if (!qualifier.is_empty()){
if (!as_namespace){
output.append(StringView::from_string_literal("typename "sv));
}
output.append(qualifier);
}
output.append(enum_.name);
}

output.append(StringView::from_string_literal("<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId type_id = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(TRY((this->codegen_type(type_id))));
}

}
}

output.append(StringView::from_string_literal(">"sv));
if (close_tag){
output.append(StringView::from_string_literal(">"sv));
}
}
return {};
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_namespace_qualifier(Jakt::ids::ScopeId const scope_id,bool const is_prelude,bool const skip_current,JaktInternal::Optional<ByteString> const possible_constructor_name,JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> const generic_mappings) {
{
ByteString output = ByteString::from_utf8_without_validation(""sv);
JaktInternal::Optional<Jakt::ids::ScopeId> current_scope_id = [&]() -> JaktInternal::Optional<Jakt::ids::ScopeId> { auto __jakt_enum_value = skip_current;
if (__jakt_enum_value) {return this->program->get_scope(scope_id)->parent;}else if (!__jakt_enum_value) {return scope_id;}VERIFY_NOT_REACHED();
 
}();
bool is_extern_import = false;
bool first = true;
while (current_scope_id.has_value()){
NonnullRefPtr<Jakt::types::Scope> const scope = this->program->get_scope(current_scope_id.value());
JaktInternal::Optional<ByteString> const name = scope->namespace_name_for_codegen().map([&](auto& _value) { return _value.as_name_for_use(); });
bool const is_constructor_call = first && (possible_constructor_name == name);
is_extern_import = (is_extern_import || scope->import_path_if_extern.has_value());
ScopeGuard __jakt_var_138([&] {
{
if (name.has_value()){
first = false;
}
current_scope_id = scope->parent;
}

});
if (name.has_value()){
if (is_constructor_call){
continue;
}
ByteString const args = TRY(([&]() -> ErrorOr<ByteString> { auto __jakt_enum_value = scope->relevant_type_id.has_value();
if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}else if (__jakt_enum_value) {{
this->used_modules.add(scope->relevant_type_id.value().module);
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>> const parameters = this->program->get_type(scope->relevant_type_id.value())->generic_parameters(this->program);
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>> __jakt_tmp414 = parameters;
if (__jakt_tmp414.has_value()){
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const params = __jakt_tmp414.value();
JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> __jakt_tmp413 = generic_mappings;
if (__jakt_tmp413.has_value()){
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const mappings = __jakt_tmp413.value();
if (!params.is_empty()){
builder.append(StringView::from_string_literal("<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter parameter = _magic_value.value();
{
Jakt::ids::TypeId const mapping = mappings.get(parameter.type_id).value();
if ((this->program->get_type(mapping)->__jakt_init_index() == 18 /* TypeVariable */) && this->map_type(mapping).equals(mapping)){
break;
}
if (first){
first = false;
}
else {
builder.append(StringView::from_string_literal(", "sv));
}

builder.append(TRY((this->codegen_type(mapping))));
}

}
}

builder.append(StringView::from_string_literal(">"sv));
}
}
}
return builder.to_string();
}
VERIFY_NOT_REACHED();
}VERIFY_NOT_REACHED();
 
}()));
output = __jakt_format(StringView::from_string_literal("{}{}::{}"sv),name.value(),args,output);
}
}
if (is_extern_import || is_prelude){
return output;
}
else {
return __jakt_format(StringView::from_string_literal("Jakt::{}"sv),output);
}

}
}

Jakt::ids::TypeId Jakt::codegen::CodeGenerator::map_type(Jakt::ids::TypeId const type_id) const {
{
JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> __jakt_tmp415 = this->generic_inferences;
if (__jakt_tmp415.has_value()){
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const mapping = __jakt_tmp415.value();
return mapping.get(type_id).value_or_lazy_evaluated([&] { return type_id; });
}
return type_id;
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_function(NonnullRefPtr<Jakt::types::CheckedFunction> const function,bool const as_method,ByteStringBuilder& output) {
{
if (function->is_comptime){
return {};
}
TRY((this->codegen_function_in_namespace(function,JaktInternal::OptionalNone(),as_method,false,JaktInternal::OptionalNone(),output)));
}
return {};
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_struct_type(Jakt::ids::StructId const id,bool const as_namespace) {
{
ByteStringBuilder output = ByteStringBuilder::create();
NonnullRefPtr<Jakt::types::Module> const type_module = this->program->get_module(id.module);
Jakt::types::CheckedStruct const checked_struct = this->program->get_struct(id);
if ((!as_namespace) && (checked_struct.record_type.__jakt_init_index() == 1 /* Class */)){
output.append(StringView::from_string_literal("NonnullRefPtr<"sv));
output.append(TRY((this->codegen_namespace_qualifier(checked_struct.scope_id,type_module->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
output.append(checked_struct.name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal(">"sv));
}
else {
output.append(TRY((this->codegen_namespace_qualifier(checked_struct.scope_id,type_module->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))));
output.append(checked_struct.name_for_codegen().as_name_for_use());
}

return output.to_string();
}
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_enum_type(Jakt::ids::EnumId const id,bool const as_namespace) {
{
ByteStringBuilder output = ByteStringBuilder::create();
NonnullRefPtr<Jakt::types::Module> const type_module = this->program->get_module(id.module);
Jakt::types::CheckedEnum const checked_enum = this->program->get_enum(id);
if ((!as_namespace) && checked_enum.is_boxed){
output.append(StringView::from_string_literal("NonnullRefPtr<"sv));
ByteString const qualifier = TRY((this->codegen_namespace_qualifier(checked_enum.scope_id,type_module->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if (!qualifier.is_empty()){
output.append(StringView::from_string_literal("typename "sv));
output.append(qualifier);
}
output.append(checked_enum.name);
output.append(StringView::from_string_literal(">"sv));
}
else {
ByteString const qualifier = TRY((this->codegen_namespace_qualifier(checked_enum.scope_id,type_module->is_prelude(),true,JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
if (!qualifier.is_empty()){
output.append(qualifier);
}
output.append(checked_enum.name);
}

return output.to_string();
}
}

ErrorOr<ByteString> Jakt::codegen::CodeGenerator::codegen_destructor_predecl(Jakt::types::CheckedStruct const& struct_) {
{
ByteStringBuilder output = ByteStringBuilder::create();
output.append(StringView::from_string_literal("public:\n"sv));
output.append(StringView::from_string_literal("    ~"sv));
output.append(struct_.name_for_codegen().as_name_for_definition());
output.append(StringView::from_string_literal("();\n"sv));
return output.to_string();
}
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_destructor(Jakt::types::CheckedStruct const& struct_,NonnullRefPtr<Jakt::types::CheckedFunction> const& function,bool const is_inline,ByteStringBuilder& output) {
{
ByteString const qualified_name = TRY((this->codegen_type_possibly_as_namespace(struct_.type_id,true)));
if ((!is_inline) && (!struct_.generic_parameters.is_empty())){
output.append(StringView::from_string_literal("template <"sv));
TRY((this->codegen_template_parameter_names(struct_.generic_parameters,output)));
output.append(StringView::from_string_literal(">\n"sv));
}
if (is_inline){
output.appendff(ByteString::from_utf8_without_validation("~{}()"sv),struct_.name_for_codegen().as_name_for_definition());
}
else {
output.appendff(ByteString::from_utf8_without_validation("{}::~{}()"sv),qualified_name,struct_.name_for_codegen().as_name_for_definition());
}

TRY((this->codegen_block(function->block,output)));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_constructor_predecl(NonnullRefPtr<Jakt::types::CheckedFunction> const function,ByteStringBuilder& output) {
{
Jakt::ids::TypeId const type_id = function->return_type_id;
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->program->get_type(type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp416 = type_;
if (__jakt_tmp416->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp416->as.Struct.value;
Jakt::types::CheckedStruct const structure = this->program->get_struct(struct_id);
if (structure.record_type.__jakt_init_index() == 1 /* Class */){
output.append(StringView::from_string_literal("protected:\n"sv));
output.appendff(ByteString::from_utf8_without_validation("explicit {}("sv),function->name_for_codegen().as_name_for_definition());
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
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

Jakt::ids::TypeId const param_type_id = param.variable->type_id;
output.append(TRY((this->codegen_type(param_type_id))));
output.append(StringView::from_string_literal(" a_"sv));
output.append(param.variable->name_for_codegen().as_name_for_definition());
}

}
}

output.append(StringView::from_string_literal(");\n"sv));
ByteString class_name_with_generics = ByteString::from_utf8_without_validation(""sv);
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,structure.name_for_codegen().as_name_for_definition());
first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = structure.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter generic_parameter = _magic_value.value();
{
if (!first){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation(", "sv));
}
else {
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation("<"sv));
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,TRY((this->codegen_type(generic_parameter.type_id))));
}

}
}

if (!structure.generic_parameters.is_empty()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation(">"sv));
}
output.append(StringView::from_string_literal("public:\n"sv));
output.appendff(ByteString::from_utf8_without_validation("static NonnullRefPtr<{}> {}"sv),class_name_with_generics,structure.create_function_name.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("__jakt_create"sv); }));
output.append(StringView::from_string_literal("("sv));
first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(TRY((this->codegen_type(param.variable->type_id))));
output.append(StringView::from_string_literal(" "sv));
output.append(param.variable->name_for_codegen().as_name_for_definition());
}

}
}

output.append(StringView::from_string_literal(");\n"sv));
return {};
}
output.append(function->name_for_codegen().as_name_for_definition());
output.append(StringView::from_string_literal("("sv));
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
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(TRY((this->codegen_type(param.variable->type_id))));
output.append(StringView::from_string_literal(" a_"sv));
output.append(param.variable->name_for_codegen().as_name_for_definition());
}

}
}

output.append(StringView::from_string_literal(");\n"sv));
}
else {
Jakt::utility::panic(ByteString::from_utf8_without_validation("internal error: call to a constructor, but not a struct/class type"sv));
}

}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_constructor(NonnullRefPtr<Jakt::types::CheckedFunction> const function,bool const is_inline,ByteStringBuilder& output) {
{
Jakt::ids::TypeId const type_id = function->return_type_id;
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->program->get_type(type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp417 = type_;
if (__jakt_tmp417->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp417->as.Struct.value;
Jakt::types::CheckedStruct const structure = this->program->get_struct(struct_id);
ByteString const qualified_name = TRY((this->codegen_type_possibly_as_namespace(type_id,true)));
if ((!is_inline) && (!structure.generic_parameters.is_empty())){
output.append(StringView::from_string_literal("template <"sv));
TRY((this->codegen_template_parameter_names(structure.generic_parameters,output)));
output.append(StringView::from_string_literal(">\n"sv));
}
if ((structure.record_type.__jakt_init_index() == 1 /* Class */) || (structure.record_type.__jakt_init_index() == 0 /* Struct */)){
if (is_inline){
output.append(function->name_for_codegen().as_name_for_definition());
output.append(StringView::from_string_literal("("sv));
}
else {
output.appendff(ByteString::from_utf8_without_validation("{}::{}("sv),qualified_name,function->name_for_codegen().as_name_for_definition());
}

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
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

Jakt::ids::TypeId const param_type_id = param.variable->type_id;
output.append(TRY((this->codegen_type(param_type_id))));
output.append(StringView::from_string_literal(" a_"sv));
output.append(param.variable->name_for_codegen().as_name_for_definition());
}

}
}

output.append(StringView::from_string_literal(")"sv));
if (!function->params.is_empty()){
output.append(StringView::from_string_literal(": "sv));
JaktInternal::DynamicArray<ByteString> initializers = DynamicArray<ByteString>::create_with({});
size_t const parent_constructor_parameter_count = JaktInternal::checked_sub(function->params.size(),structure.fields.size());
if (parent_constructor_parameter_count > static_cast<size_t>(0ULL)){
ByteString parent_initializer = ByteString::from_utf8_without_validation(""sv);
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(parent_initializer,this->program->get_struct(structure.super_struct_id.value()).name_for_codegen().as_name_for_definition());
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(parent_initializer,ByteString::from_utf8_without_validation("("sv));
JaktInternal::DynamicArray<ByteString> strings = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.operator[](JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parent_constructor_parameter_count)}).iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
strings.push((ByteString::from_utf8_without_validation("move(a_"sv) + param.variable->name_for_codegen().as_name_for_use()) + ByteString::from_utf8_without_validation(")"sv));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(parent_initializer,Jakt::utility::join(strings,ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(parent_initializer,ByteString::from_utf8_without_validation(")"sv));
initializers.push(parent_initializer);
}
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(parent_constructor_parameter_count),static_cast<size_t>(function->params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::CheckedParameter const param = function->params.operator[](i);
initializers.push(((param.variable->name_for_codegen().as_name_for_use() + ByteString::from_utf8_without_validation("(move(a_"sv)) + param.variable->name_for_codegen().as_name_for_use()) + ByteString::from_utf8_without_validation("))"sv));
}

}
}

output.append(Jakt::utility::join(initializers,ByteString::from_utf8_without_validation(", "sv)));
}
output.append(StringView::from_string_literal("{}\n"sv));
if (structure.record_type.__jakt_init_index() == 1 /* Class */){
ByteString class_name_with_generics = ByteString::from_utf8_without_validation(""sv);
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,structure.name_for_codegen().as_name_for_definition());
first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = structure.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter generic_parameter = _magic_value.value();
{
if (!first){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation(", "sv));
}
else {
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation("<"sv));
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,TRY((this->codegen_type(generic_parameter.type_id))));
}

}
}

if (!structure.generic_parameters.is_empty()){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(class_name_with_generics,ByteString::from_utf8_without_validation(">"sv));
}
if (is_inline){
output.append(StringView::from_string_literal("static "sv));
}
ByteString const qualified_namespace = [&]() -> ByteString { auto __jakt_enum_value = is_inline;
if (__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}else if (!__jakt_enum_value) {return qualified_name + ByteString::from_utf8_without_validation("::"sv);}VERIFY_NOT_REACHED();
 
}();
output.appendff(ByteString::from_utf8_without_validation("NonnullRefPtr<{}> {}{}"sv),class_name_with_generics,qualified_namespace,structure.create_function_name.value_or_lazy_evaluated([&] { return ByteString::from_utf8_without_validation("__jakt_create"sv); }));
output.append(StringView::from_string_literal("("sv));
first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(TRY((this->codegen_type(param.variable->type_id))));
output.append(StringView::from_string_literal(" "sv));
output.append(param.variable->name_for_codegen().as_name_for_definition());
}

}
}

output.appendff(ByteString::from_utf8_without_validation(") {{ auto o = adopt_ref(*new {} ("sv),class_name_with_generics);
first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(StringView::from_string_literal("move("sv));
output.append(param.variable->name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal(")"sv));
}

}
}

output.append(StringView::from_string_literal(")); return o; }"sv));
}
return {};
}
if (!is_inline){
output.append(qualified_name);
output.append(StringView::from_string_literal("::"sv));
}
output.append(function->name_for_codegen().as_name_for_definition());
output.append(StringView::from_string_literal("("sv));
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
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(TRY((this->codegen_type(param.variable->type_id))));
output.append(StringView::from_string_literal(" a_"sv));
output.append(param.variable->name_for_codegen().as_name_for_definition());
}

}
}

output.append(StringView::from_string_literal(") "sv));
if (!function->params.is_empty()){
output.append(StringView::from_string_literal(":"sv));
}
first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(param.variable->name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal("(move(a_"sv));
output.append(param.variable->name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal("))"sv));
}

}
}

output.append(StringView::from_string_literal("{}\n"sv));
}
else {
Jakt::utility::panic(ByteString::from_utf8_without_validation("internal error: call to a constructor, but not a struct/class type"sv));
}

}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_function_in_namespace(NonnullRefPtr<Jakt::types::CheckedFunction> const function,JaktInternal::Optional<Jakt::ids::TypeId> const containing_struct,bool const as_method,bool const skip_template,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const explicit_generic_instantiation,ByteStringBuilder& output) {
{
if (function->linkage.__jakt_init_index() == 1 /* External */){
return {};
}
if (function->force_inline.__jakt_init_index() == 2 /* ForceInline */){
return {};
}
if (!skip_template){
TRY((this->codegen_function_generic_parameters(function,output)));
}
bool const is_main = (function->name_for_codegen().as_name_for_use() == ByteString::from_utf8_without_validation("main"sv)) && (!containing_struct.has_value());
if (function->force_inline.__jakt_init_index() == 1 /* MakeDefinitionAvailable */){
output.append(StringView::from_string_literal("__attribute__((always_inline)) inline "sv));
}
if (function->return_type_id.equals(Jakt::types::never_type_id())){
output.append(StringView::from_string_literal("[[noreturn]] "sv));
}
if (is_main){
output.append(StringView::from_string_literal("ErrorOr<int>"sv));
}
else {
if (as_method && function->is_static()){
output.append(StringView::from_string_literal("static "sv));
}
if ((!(function->type.__jakt_init_index() == 2 /* Destructor */)) && (!(function->type.__jakt_init_index() == 1 /* Constructor */))){
output.append(TRY(([&]() -> ErrorOr<ByteString> { auto __jakt_enum_value = function->can_throw;
if (__jakt_enum_value) {return __jakt_format(StringView::from_string_literal("ErrorOr<{}>"sv),TRY((this->codegen_type(function->return_type_id))));}else if (!__jakt_enum_value) {return this->codegen_type(function->return_type_id);}VERIFY_NOT_REACHED();
 
}())));
}
}

output.append(StringView::from_string_literal(" "sv));
if (is_main){
output.append(StringView::from_string_literal("main"sv));
}
else {
ByteString const qualifier = TRY(([&]() -> ErrorOr<ByteString> { auto __jakt_enum_value = containing_struct.has_value();
if (__jakt_enum_value) {return this->codegen_type_possibly_as_namespace(containing_struct.value(),true);}else if (!__jakt_enum_value) {return ByteString::from_utf8_without_validation(""sv);}VERIFY_NOT_REACHED();
 
}()));
if (!qualifier.is_empty()){
output.append(qualifier);
output.append(StringView::from_string_literal("::"sv));
}
if (function->type.__jakt_init_index() == 2 /* Destructor */){
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp418 = this->program->get_type(containing_struct.value());
if (__jakt_tmp418->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const struct_id = __jakt_tmp418->as.Struct.value;
output.append(ByteString::from_utf8_without_validation("~"sv) + this->program->get_struct(struct_id).name_for_codegen().as_name_for_definition());
}
else {
Jakt::utility::panic(ByteString::from_utf8_without_validation("Destructor doesn't have a containing struct"sv));
}

}
else {
output.append(function->name_for_codegen().as_name_for_definition());
}

}

if (explicit_generic_instantiation.has_value()){
output.append(StringView::from_string_literal("<"sv));
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = explicit_generic_instantiation.value().iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId type = _magic_value.value();
{
if (!first){
output.append(StringView::from_string_literal(", "sv));
}
else {
first = false;
}

output.append(TRY((this->codegen_type(type))));
}

}
}

output.append(StringView::from_string_literal(">"sv));
}
output.append(StringView::from_string_literal("("sv));
if (is_main && function->params.is_empty()){
output.append(StringView::from_string_literal("DynamicArray<ByteString>"sv));
}
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
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = param.variable;
if (variable->name == ByteString::from_utf8_without_validation("this"sv)){
continue;
}
if (!first){
output.append(StringView::from_string_literal(","sv));
}
else {
first = false;
}

NonnullRefPtr<typename Jakt::types::Type> const variable_type = this->program->get_type(variable->type_id);
output.append(TRY((this->codegen_type(variable->type_id))));
output.append(StringView::from_string_literal(" "sv));
if ((!variable->is_mutable) && (!((variable_type->__jakt_init_index() == 27 /* Reference */) || (variable_type->__jakt_init_index() == 28 /* MutableReference */)))){
output.append(StringView::from_string_literal("const "sv));
}
output.append(variable->name_for_codegen().as_name_for_definition());
}

}
}

output.append(StringView::from_string_literal(")"sv));
if ((!function->is_static()) && (!function->is_mutating())){
output.append(StringView::from_string_literal(" const"sv));
}
if (function->is_raw_constructor){
output.append(StringView::from_string_literal(" : "sv));
bool first = true;
Jakt::types::CheckedStruct const struct_ = [&]() -> Jakt::types::CheckedStruct { auto&& __jakt_match_variant = *this->program->get_type(containing_struct.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return this->program->get_struct(id);};/*case end*/
default:{
this->compiler->panic(ByteString::from_utf8_without_validation("Expected a struct"sv));
}
}/*switch end*/
 
}();
if (struct_.super_struct_id.has_value()){
Jakt::types::CheckedStruct const super_struct = this->program->get_struct(struct_.super_struct_id.value());
output.append(super_struct.name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal("()"sv));
first = false;
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
if (!first){
output.append(StringView::from_string_literal(",\n"sv));
}
else {
first = false;
}

NonnullRefPtr<Jakt::types::CheckedVariable> const var = this->program->get_variable(field->variable_id);
output.append(var->name_for_codegen().as_name_for_use());
output.append(StringView::from_string_literal("("sv));
TRY((this->codegen_expression(field->default_value_in_definition_scope.value(),output,false,false)));
output.append(StringView::from_string_literal(")"sv));
}

}
}

}
output.append(StringView::from_string_literal(" {\n"sv));
if (is_main){
output.append(StringView::from_string_literal("\n\n            #ifdef _WIN32\n            #ifndef CP_UTF8\n            static constexpr unsigned int CP_UTF8 = 65001;\n            #endif\n            SetConsoleOutputCP(CP_UTF8);\n            // Enable buffering to prevent VS from chopping up UTF-8 byte sequences\n            setvbuf(stdout, nullptr, _IOFBF, 1000);\n            #endif\n"sv));
}
Jakt::codegen::ControlFlowState const last_control_flow = this->control_flow_state;
this->control_flow_state = last_control_flow.enter_function();
TRY((this->codegen_block(function->block,output)));
this->control_flow_state = last_control_flow;
if (is_main){
output.append(StringView::from_string_literal("return 0;\n"sv));
}
else {
if (function->can_throw && function->return_type_id.equals(Jakt::types::builtin(Jakt::types::BuiltinType::Void()))){
output.append(StringView::from_string_literal("return {};\n"sv));
}
}

output.append(StringView::from_string_literal("}\n"sv));
}
return {};
}

ErrorOr<void> Jakt::codegen::CodeGenerator::codegen_lambda_block(bool const can_throw,Jakt::types::CheckedBlock const block,Jakt::ids::TypeId const return_type_id,ByteStringBuilder& output) {
{
output.append(StringView::from_string_literal("{"sv));
TRY((this->codegen_block(block,output)));
if (can_throw && return_type_id.equals(Jakt::types::builtin(Jakt::types::BuiltinType::Void()))){
output.append(StringView::from_string_literal("return {};\n"sv));
}
output.append(StringView::from_string_literal("}\n"sv));
}
return {};
}

Jakt::codegen::CodeGenerator::CodeGenerator(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, NonnullRefPtr<Jakt::types::CheckedProgram> a_program, Jakt::codegen::ControlFlowState a_control_flow_state, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,ByteString>> a_entered_yieldable_blocks, ByteStringBuilder a_deferred_output, JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedFunction>> a_current_function, bool a_inside_defer, Jakt::codegen::CodegenDebugInfo a_debug_info, JaktInternal::DynamicArray<ByteString> a_namespace_stack, size_t a_fresh_var_counter, size_t a_fresh_label_counter, JaktInternal::Optional<ByteString> a_this_replacement, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> a_generic_inferences, JaktInternal::Set<Jakt::ids::ModuleId> a_used_modules, JaktInternal::Optional<Jakt::codegen::YieldMethod> a_yield_method, bool a_yields_erroror): compiler(move(a_compiler)), program(move(a_program)), control_flow_state(move(a_control_flow_state)), entered_yieldable_blocks(move(a_entered_yieldable_blocks)), deferred_output(move(a_deferred_output)), current_function(move(a_current_function)), inside_defer(move(a_inside_defer)), debug_info(move(a_debug_info)), namespace_stack(move(a_namespace_stack)), fresh_var_counter(move(a_fresh_var_counter)), fresh_label_counter(move(a_fresh_label_counter)), this_replacement(move(a_this_replacement)), generic_inferences(move(a_generic_inferences)), used_modules(move(a_used_modules)), yield_method(move(a_yield_method)), yields_erroror(move(a_yields_erroror)){}

ByteString Jakt::codegen::AllowedControlExits::debug_description() const {
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
AllowedControlExits::~AllowedControlExits(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void AllowedControlExits::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Nothing */:break;
case 1 /* JustReturn */:break;
case 2 /* AtLoop */:break;
}
}
Jakt::codegen::AllowedControlExits Jakt::codegen::AllowedControlExits::allow_return() const {
{
{auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Nothing */:case 1 /* JustReturn */:return Jakt::codegen::AllowedControlExits::JustReturn();case 2 /* AtLoop */:return Jakt::codegen::AllowedControlExits::AtLoop();default: VERIFY_NOT_REACHED();}/*switch end*/
}
}
}

ByteString Jakt::codegen::YieldMethod::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* ReturnExplicitValue */: {
builder.append("YieldMethod::ReturnExplicitValue"sv);
[[maybe_unused]] auto const& that = this->as.ReturnExplicitValue;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("ctor: \"{}\"", that.ctor);
}
builder.append(")"sv);
break;}
case 1 /* AssignAndGoto */: {
builder.append("YieldMethod::AssignAndGoto"sv);
[[maybe_unused]] auto const& that = this->as.AssignAndGoto;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("label: \"{}\"", that.label);
}
builder.append(")"sv);
break;}
case 2 /* Return */: {
return ByteString("YieldMethod::Return"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] YieldMethod YieldMethod::ReturnExplicitValue(ByteString ctor){
YieldMethod __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.ReturnExplicitValue.ctor) (decltype(ctor))(move(ctor));
return __jakt_uninit_enum;
}
[[nodiscard]] YieldMethod YieldMethod::AssignAndGoto(ByteString name, ByteString label){
YieldMethod __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.AssignAndGoto.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.AssignAndGoto.label) (decltype(label))(move(label));
return __jakt_uninit_enum;
}
[[nodiscard]] YieldMethod YieldMethod::Return(){
YieldMethod __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
YieldMethod& YieldMethod::operator=(YieldMethod const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* ReturnExplicitValue */:
new (&this->as.ReturnExplicitValue.ctor) (decltype(this->as.ReturnExplicitValue.ctor))(rhs.as.ReturnExplicitValue.ctor);
break;
case 1 /* AssignAndGoto */:
new (&this->as.AssignAndGoto.name) (decltype(this->as.AssignAndGoto.name))(rhs.as.AssignAndGoto.name);
new (&this->as.AssignAndGoto.label) (decltype(this->as.AssignAndGoto.label))(rhs.as.AssignAndGoto.label);
break;
case 2 /* Return */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* ReturnExplicitValue */:
this->as.ReturnExplicitValue.ctor = rhs.as.ReturnExplicitValue.ctor;
break;
case 1 /* AssignAndGoto */:
this->as.AssignAndGoto.name = rhs.as.AssignAndGoto.name;
this->as.AssignAndGoto.label = rhs.as.AssignAndGoto.label;
break;
case 2 /* Return */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
YieldMethod::YieldMethod(YieldMethod const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* ReturnExplicitValue */:
new (&this->as.ReturnExplicitValue.ctor) (decltype(this->as.ReturnExplicitValue.ctor))(rhs.as.ReturnExplicitValue.ctor);
break;
case 1 /* AssignAndGoto */:
new (&this->as.AssignAndGoto.name) (decltype(this->as.AssignAndGoto.name))(rhs.as.AssignAndGoto.name);
new (&this->as.AssignAndGoto.label) (decltype(this->as.AssignAndGoto.label))(rhs.as.AssignAndGoto.label);
break;
case 2 /* Return */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
YieldMethod& YieldMethod::operator=(YieldMethod &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* ReturnExplicitValue */:
new (&this->as.ReturnExplicitValue.ctor) (decltype(this->as.ReturnExplicitValue.ctor))(move(rhs.as.ReturnExplicitValue.ctor));
break;
case 1 /* AssignAndGoto */:
new (&this->as.AssignAndGoto.name) (decltype(this->as.AssignAndGoto.name))(move(rhs.as.AssignAndGoto.name));
new (&this->as.AssignAndGoto.label) (decltype(this->as.AssignAndGoto.label))(move(rhs.as.AssignAndGoto.label));
break;
case 2 /* Return */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* ReturnExplicitValue */:
this->as.ReturnExplicitValue.ctor = move(rhs.as.ReturnExplicitValue.ctor);
break;
case 1 /* AssignAndGoto */:
this->as.AssignAndGoto.name = move(rhs.as.AssignAndGoto.name);
this->as.AssignAndGoto.label = move(rhs.as.AssignAndGoto.label);
break;
case 2 /* Return */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
YieldMethod::YieldMethod(YieldMethod &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* ReturnExplicitValue */:
new (&this->as.ReturnExplicitValue.ctor) (decltype(this->as.ReturnExplicitValue.ctor))(move(rhs.as.ReturnExplicitValue.ctor));
break;
case 1 /* AssignAndGoto */:
new (&this->as.AssignAndGoto.name) (decltype(this->as.AssignAndGoto.name))(move(rhs.as.AssignAndGoto.name));
new (&this->as.AssignAndGoto.label) (decltype(this->as.AssignAndGoto.label))(move(rhs.as.AssignAndGoto.label));
break;
case 2 /* Return */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
YieldMethod::~YieldMethod(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void YieldMethod::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* ReturnExplicitValue */:this->as.ReturnExplicitValue.ctor.~ByteString();
break;
case 1 /* AssignAndGoto */:this->as.AssignAndGoto.name.~ByteString();
this->as.AssignAndGoto.label.~ByteString();
break;
case 2 /* Return */:break;
}
}
}
} // namespace Jakt
