#include "repl.h"
namespace Jakt {
namespace repl {
String serialize_unary_operation(types::CheckedUnaryOperator const op,String const expr) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, String>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PreIncrement>();
return JaktInternal::ExplicitValue((Jakt::String("++") + expr));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PostIncrement>();
return JaktInternal::ExplicitValue((expr + Jakt::String("++")));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PreDecrement>();
return JaktInternal::ExplicitValue((Jakt::String("--") + expr));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::PostDecrement>();
return JaktInternal::ExplicitValue((expr + Jakt::String("--")));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Negate>();
return JaktInternal::ExplicitValue((Jakt::String("-") + expr));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Dereference>();
return JaktInternal::ExplicitValue((Jakt::String("*") + expr));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::RawAddress>();
return JaktInternal::ExplicitValue((Jakt::String("&raw ") + expr));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::Reference>();
return JaktInternal::ExplicitValue((Jakt::String("&") + expr));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::MutableReference>();
return JaktInternal::ExplicitValue((Jakt::String("&mut ") + expr));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::LogicalNot>();
return JaktInternal::ExplicitValue((Jakt::String("not ") + expr));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedUnaryOperator::BitwiseNot>();
return JaktInternal::ExplicitValue((Jakt::String("~") + expr));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((Jakt::String("(<Unimplemented unary operator> ") + expr) + Jakt::String(")")));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<String> serialize_ast_node(NonnullRefPtr<types::CheckedExpression> const node) {
{
return (JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = *node;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Boolean>();bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}"),val))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NumericConstant>();types::CheckedNumericConstant const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<String>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I8>();
i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}i8"),value))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I16>();
i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}i16"),value))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I32>();
i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}i32"),value))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I64>();
i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}i64"),value))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U8>();
u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}u8"),value))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U16>();
u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}u16"),value))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U32>();
u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}u32"),value))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U64>();
u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}u64"),value))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::F32>();
f32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}f32"),value))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::F64>();
f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}f64"),value))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::USize>();
u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}uz"),value))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
)));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::QuotedString>();types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_RETURN_ONLY(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String,ErrorOr<String>>{
auto __jakt_enum_value = (((((val).type_id)).equals(types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("\"{}\""),((val).to_string())))));
}
else {
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("(overloaded) \"{}\""),((val).to_string())))));
}
}()))
);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ByteConstant>();String const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("b'{}'"),val))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::CharacterConstant>();String const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("'{}'"),val))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(repl::serialize_unary_operation(op,TRY((repl::serialize_ast_node(expr)))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktTuple>();JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_649; {
StringBuilder builder = TRY((StringBuilder::create()));
TRY((((builder).append_string(Jakt::String("(")))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vals).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((i != static_cast<size_t>(0ULL))){
TRY((((builder).append_string(Jakt::String(", ")))));
}
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((vals)[i]))))))));
}

}
}

TRY((((builder).append_string(Jakt::String(")")))));
__jakt_var_649 = TRY((((builder).to_string()))); goto __jakt_label_603;

}
__jakt_label_603:; __jakt_var_649.release_value(); }));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Range>();JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<types::CheckedExpression>> const& to = __jakt_match_value.to;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_650; {
String from_output = Jakt::String("");
if (((from).has_value())){
(from_output = TRY((repl::serialize_ast_node((from.value())))));
}
String to_output = Jakt::String("");
if (((to).has_value())){
(to_output = TRY((repl::serialize_ast_node((to.value())))));
}
__jakt_var_650 = TRY((String::formatted(Jakt::String("{}..{}"),from_output,to_output))); goto __jakt_label_604;

}
__jakt_label_604:; __jakt_var_650.release_value(); }));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktArray>();JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_651; {
StringBuilder builder = TRY((StringBuilder::create()));
TRY((((builder).append_string(Jakt::String("[")))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vals).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((i != static_cast<size_t>(0ULL))){
TRY((((builder).append_string(Jakt::String(", ")))));
}
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((vals)[i]))))))));
}

}
}

TRY((((builder).append_string(Jakt::String("]")))));
__jakt_var_651 = TRY((((builder).to_string()))); goto __jakt_label_605;

}
__jakt_label_605:; __jakt_var_651.release_value(); }));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktSet>();JaktInternal::Array<NonnullRefPtr<types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_652; {
StringBuilder builder = TRY((StringBuilder::create()));
TRY((((builder).append_string(Jakt::String("{")))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vals).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((i != static_cast<size_t>(0ULL))){
TRY((((builder).append_string(Jakt::String(", ")))));
}
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((vals)[i]))))))));
}

}
}

TRY((((builder).append_string(Jakt::String("}")))));
__jakt_var_652 = TRY((((builder).to_string()))); goto __jakt_label_606;

}
__jakt_label_606:; __jakt_var_652.release_value(); }));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktDictionary>();JaktInternal::Array<JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_653; {
StringBuilder builder = TRY((StringBuilder::create()));
TRY((((builder).append_string(Jakt::String("[")))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vals).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((i != static_cast<size_t>(0ULL))){
TRY((((builder).append_string(Jakt::String(", ")))));
}
JaktInternal::Tuple<NonnullRefPtr<types::CheckedExpression>,NonnullRefPtr<types::CheckedExpression>> const val = ((vals)[i]);
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((val).template get<0>()))))))));
TRY((((builder).append_string(Jakt::String(": ")))));
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((val).template get<1>()))))))));
}

}
}

TRY((((builder).append_string(Jakt::String("]")))));
__jakt_var_653 = TRY((((builder).to_string()))); goto __jakt_label_607;

}
__jakt_label_607:; __jakt_var_653.release_value(); }));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedExpression>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}[{}]"),TRY((repl::serialize_ast_node(expr))),TRY((repl::serialize_ast_node(index)))))));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedDictionary>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}[{}]"),TRY((repl::serialize_ast_node(expr))),TRY((repl::serialize_ast_node(index)))))));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedTuple>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}.{}"),TRY((repl::serialize_ast_node(expr))),index))));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedStruct>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
String const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}.{}"),TRY((repl::serialize_ast_node(expr))),index))));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NamespacedVar>();JaktInternal::Array<types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
types::CheckedVariable const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_654; {
StringBuilder builder = TRY((StringBuilder::create()));
{
JaktInternal::ArrayIterator<types::CheckedNamespace> _magic = ((namespaces).iterator());
for (;;){
JaktInternal::Optional<types::CheckedNamespace> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedNamespace namespace_ = (_magic_value.value());
{
TRY((((builder).append_string(((namespace_).name)))));
TRY((((builder).append_string(Jakt::String("::")))));
}

}
}

TRY((((builder).append_string(((var).name)))));
__jakt_var_654 = TRY((((builder).to_string()))); goto __jakt_label_608;

}
__jakt_label_608:; __jakt_var_654.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Var>();types::CheckedVariable const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var).name));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::OptionalNone>();return JaktInternal::ExplicitValue(Jakt::String("None"));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::OptionalSome>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("Some({})"),TRY((repl::serialize_ast_node(expr)))))));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ForcedUnwrap>();NonnullRefPtr<types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((String::formatted(Jakt::String("{}!"),TRY((repl::serialize_ast_node(expr)))))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(({ Optional<String> __jakt_var_655; {
StringBuilder builder = TRY((StringBuilder::create()));
{
JaktInternal::ArrayIterator<types::ResolvedNamespace> _magic = ((((call).namespace_)).iterator());
for (;;){
JaktInternal::Optional<types::ResolvedNamespace> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ResolvedNamespace namespace_ = (_magic_value.value());
{
TRY((((builder).append_string(((namespace_).name)))));
TRY((((builder).append_string(Jakt::String("::")))));
}

}
}

TRY((((builder).append_string(((call).name)))));
TRY((((builder).append_string(Jakt::String("(")))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((i != static_cast<size_t>(0ULL))){
TRY((((builder).append_string(Jakt::String(", ")))));
}
JaktInternal::Tuple<String,NonnullRefPtr<types::CheckedExpression>> const arg = ((((call).args))[i]);
if ((!(((((arg).template get<0>())).is_empty())))){
TRY((((builder).append_string(((arg).template get<0>())))));
TRY((((builder).append_string(Jakt::String(": ")))));
}
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((arg).template get<1>()))))))));
}

}
}

TRY((((builder).append_string(Jakt::String(")")))));
__jakt_var_655 = TRY((((builder).to_string()))); goto __jakt_label_609;

}
__jakt_label_609:; __jakt_var_655.release_value(); }));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedExpression::Garbage>();
return JaktInternal::ExplicitValue(Jakt::String("<Garbage>"));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::String("<Unimplemented>"));
};/*case end*/
}/*switch end*/
}()
)));
}
}

ErrorOr<String> repl::Editor::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("Editor("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("standard_input_file: "));TRY(builder.appendff("{}, ", standard_input_file));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("line_pointer: "));TRY(builder.appendff("{}, ", line_pointer));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("prompt: "));TRY(builder.appendff("\"{}\"", prompt));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<repl::Editor> repl::Editor::create(String const prompt) {
{
FILE* std_in = fopen(((Jakt::String("/dev/stdin")).c_string()),((Jakt::String("r")).c_string()));
if ((std_in == utility::null<FILE>())){
warnln(Jakt::String("Could not open /dev/stdin for reading"));
return Error::from_errno(static_cast<i32>(42));
}
repl::Editor const editor = repl::Editor(std_in,utility::allocate<char>(static_cast<size_t>(4096ULL)),prompt);
return (editor);
}
}

void repl::Editor::destroy() {
{
fclose(((*this).standard_input_file));
{
free(line_pointer);
}

}
}

repl::Editor::Editor(FILE* a_standard_input_file, char* a_line_pointer, String a_prompt) :standard_input_file(a_standard_input_file), line_pointer(a_line_pointer), prompt(a_prompt){}

ErrorOr<repl::LineResult> repl::Editor::get_line() {
{
warn(Jakt::String("{}"),((*this).prompt));
StringBuilder builder = TRY((StringBuilder::create()));
{
char* const c_string = fgets(((*this).line_pointer),static_cast<size_t>(4096ULL),((*this).standard_input_file));
if ((c_string == utility::null<char>())){
return ( repl::LineResult { typename repl::LineResult::Eof() } );
}
TRY((((builder).append_c_string(c_string))));
}

return ( repl::LineResult { typename repl::LineResult::Line(TRY((((builder).to_string())))) } );
}
}

ErrorOr<String> repl::REPL::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("REPL("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("compiler: "));TRY(builder.appendff("{}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("typechecker: "));TRY(builder.appendff("{}, ", typechecker));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("root_scope_id: "));TRY(builder.appendff("{}, ", root_scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("root_interpreter_scope: "));TRY(builder.appendff("{}, ", *root_interpreter_scope));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("file_id: "));TRY(builder.appendff("{}", file_id));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<repl::REPL> repl::REPL::create(path::Path const runtime_path,JaktInternal::Optional<String> const target_triple) {
{
NonnullRefPtr<compiler::Compiler> compiler = TRY((compiler::Compiler::create((TRY((Array<path::Path>::create_with({})))),(TRY((Dictionary<String, utility::FileId>::create_with_entries({})))),(TRY((Array<error::JaktError>::create_with({})))),JaktInternal::OptionalNone(),(TRY((Array<u8>::create_with({})))),false,false,false,false,runtime_path,(TRY((Array<String>::create_with({})))),false,false,false,false,target_triple)));
TRY((((compiler)->load_prelude())));
utility::FileId const file_id = TRY((((compiler)->get_file_id_or_register(TRY((path::Path::Path::from_string(Jakt::String("<repl>"))))))));
types::ModuleId const placeholder_module_id = types::ModuleId(static_cast<size_t>(0ULL));
typechecker::Typechecker typechecker = typechecker::Typechecker(compiler,TRY((types::CheckedProgram::create(compiler,(TRY((Array<NonnullRefPtr<types::Module>>::create_with({})))),(TRY((Dictionary<String, types::LoadedModule>::create_with_entries({}))))))),placeholder_module_id,types::TypeId::TypeId::none(),JaktInternal::OptionalNone(),false,static_cast<size_t>(0ULL),false,((compiler)->dump_type_hints),((compiler)->dump_try_hints),static_cast<u64>(0ULL),types::GenericInferences((TRY((Dictionary<String, String>::create_with_entries({}))))));
(((compiler)->current_file) = file_id);
TRY((((typechecker).include_prelude())));
String const root_module_name = Jakt::String("<repl>");
types::ModuleId const root_module_id = TRY((((typechecker).create_module(root_module_name,true,JaktInternal::OptionalNone()))));
(((typechecker).current_module_id) = root_module_id);
TRY((((((typechecker).program))->set_loaded_module(root_module_name,types::LoadedModule(root_module_id,file_id)))));
types::ScopeId const PRELUDE_SCOPE_ID = ((typechecker).prelude_scope_id());
types::ScopeId const root_scope_id = TRY((((typechecker).create_scope(PRELUDE_SCOPE_ID,true,Jakt::String("root")))));
NonnullRefPtr<interpreter::InterpreterScope> const root_interpreter_scope = TRY((interpreter::InterpreterScope::InterpreterScope::create((TRY((Dictionary<String, types::Value>::create_with_entries({})))),JaktInternal::OptionalNone(),(TRY((Dictionary<String, types::TypeId>::create_with_entries({})))))));
return (repl::REPL(compiler,typechecker,root_scope_id,root_interpreter_scope,file_id));
}
}

ErrorOr<void> repl::REPL::run() {
{
repl::Editor editor = TRY((repl::Editor::Editor::create(Jakt::String("> "))));
ScopeGuard __jakt_var_656([&] {
((editor).destroy());
});
for (;;){
if ((!(((((((*this).compiler))->errors)).is_empty())))){
TRY((((((*this).compiler))->print_errors())));
JaktInternal::Array<error::JaktError> const arr = (TRY((Array<error::JaktError>::create_with({}))));
(((((*this).compiler))->errors) = arr);
}
repl::LineResult const line_result = ({ Optional<repl::LineResult> __jakt_var_657;
auto __jakt_var_658 = [&]() -> ErrorOr<repl::LineResult> { return TRY((((editor).get_line()))); }();
if (__jakt_var_658.is_error()) {auto error = __jakt_var_658.release_error();
{
return {};
}
} else {__jakt_var_657 = __jakt_var_658.release_value();
}
__jakt_var_657.release_value(); });
if (((line_result).index() == 0 /* Line */)){
String const line = ((line_result).get<repl::LineResult::Line>()).value;
if ((line == Jakt::String(".exit\n"))){
break;
}
size_t pos = static_cast<size_t>(0ULL);
JaktInternal::Array<u8> bytes_ = (TRY((Array<u8>::create_with({}))));
TRY((((bytes_).ensure_capacity(((line).length())))));
while ((pos < ((line).length()))){
TRY((((bytes_).push(((line).byte_at(pos))))));
(++(pos));
}
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = bytes_);
JaktInternal::Array<lexer::Token> const tokens = ({ Optional<JaktInternal::Array<lexer::Token>> __jakt_var_659;
auto __jakt_var_660 = [&]() -> ErrorOr<JaktInternal::Array<lexer::Token>> { return TRY((lexer::Lexer::Lexer::lex(((*this).compiler)))); }();
if (__jakt_var_660.is_error()) {{
continue;
}
} else {__jakt_var_659 = __jakt_var_660.release_value();
}
__jakt_var_659.release_value(); });
if (((tokens).is_empty())){
continue;
}
parser::Parser parser = parser::Parser(static_cast<size_t>(0ULL),tokens,((*this).compiler));
lexer::Token const first_token = (((tokens).first()).value());
if (((((((((((first_token).index() == 75 /* Function */) || ((first_token).index() == 76 /* Comptime */)) || ((first_token).index() == 94 /* Struct */)) || ((first_token).index() == 66 /* Class */)) || ((first_token).index() == 71 /* Enum */)) || ((first_token).index() == 63 /* Boxed */)) || ((first_token).index() == 85 /* Namespace */)) || ((first_token).index() == 78 /* Import */)) || ((first_token).index() == 108 /* Trait */))){
parser::ParsedNamespace const parsed_namespace = ({ Optional<parser::ParsedNamespace> __jakt_var_661;
auto __jakt_var_662 = [&]() -> ErrorOr<parser::ParsedNamespace> { return TRY((((parser).parse_namespace()))); }();
if (__jakt_var_662.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_661 = __jakt_var_662.release_value();
}
__jakt_var_661.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
auto __jakt_var_664 = [&]() -> ErrorOr<void> { return TRY((((((*this).typechecker)).typecheck_module(parsed_namespace,((*this).root_scope_id))))), ErrorOr<void>{}; }();
if (__jakt_var_664.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
}
;
TRY((((*this).handle_possible_error())));
continue;
}
NonnullRefPtr<parser::ParsedStatement> const parsed_statement = ({ Optional<NonnullRefPtr<parser::ParsedStatement>> __jakt_var_665;
auto __jakt_var_666 = [&]() -> ErrorOr<NonnullRefPtr<parser::ParsedStatement>> { return TRY((((parser).parse_statement(true)))); }();
if (__jakt_var_666.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_665 = __jakt_var_666.release_value();
}
__jakt_var_665.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
NonnullRefPtr<types::CheckedStatement> const checked_statement = ({ Optional<NonnullRefPtr<types::CheckedStatement>> __jakt_var_667;
auto __jakt_var_668 = [&]() -> ErrorOr<NonnullRefPtr<types::CheckedStatement>> { return TRY((((((*this).typechecker)).typecheck_statement(parsed_statement,((*this).root_scope_id), types::SafetyMode { typename types::SafetyMode::Safe() } ,JaktInternal::OptionalNone())))); }();
if (__jakt_var_668.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_667 = __jakt_var_668.release_value();
}
__jakt_var_667.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((interpreter::Interpreter::Interpreter::create(((*this).compiler),((((*this).typechecker)).program),(TRY((Array<utility::Span>::create_with({})))))));
interpreter::StatementResult const result = ({ Optional<interpreter::StatementResult> __jakt_var_669;
auto __jakt_var_670 = [&]() -> ErrorOr<interpreter::StatementResult> { return TRY((((interpreter)->execute_statement(checked_statement,((*this).root_interpreter_scope),utility::Span(((*this).file_id),static_cast<size_t>(0ULL),((line).length())))))); }();
if (__jakt_var_670.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_669 = __jakt_var_670.release_value();
}
__jakt_var_669.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Return>();
types::Value const& value = __jakt_match_value.value;
{
if (((((value).impl))->index() == 0 /* Void */)){
return JaktInternal::LoopContinue{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::JustValue>();
types::Value const& value = __jakt_match_value.value;
{
if (((((value).impl))->index() == 0 /* Void */)){
return JaktInternal::LoopContinue{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Throw>();
types::Value const& value = __jakt_match_value.value;
{
if (((((value).impl))->index() == 0 /* Void */)){
return JaktInternal::LoopContinue{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Break>();
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Continue>();
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Yield>();
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
String const output = JAKT_RESOLVE_EXPLICIT_VALUE_OR_CONTROL_FLOW_AT_LOOP(([&]() -> JaktInternal::ExplicitValueOrControlFlow<String, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Return>();
types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((repl::serialize_ast_node(TRY((interpreter::value_to_checked_expression(value,interpreter)))))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::JustValue>();
types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((repl::serialize_ast_node(TRY((interpreter::value_to_checked_expression(value,interpreter)))))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Throw>();
types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Jakt::String("throw ") + TRY((repl::serialize_ast_node(TRY((interpreter::value_to_checked_expression(value,interpreter))))))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Break>();
{
return JaktInternal::LoopContinue{};
}
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Continue>();
{
return JaktInternal::LoopContinue{};
}
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename interpreter::StatementResult::Yield>();
{
return JaktInternal::LoopContinue{};
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
));
outln(Jakt::String("= {}"),output);
}
else {
break;
}

}
}
return {};
}

repl::REPL::REPL(NonnullRefPtr<compiler::Compiler> a_compiler, typechecker::Typechecker a_typechecker, types::ScopeId a_root_scope_id, NonnullRefPtr<interpreter::InterpreterScope> a_root_interpreter_scope, utility::FileId a_file_id) :compiler(a_compiler), typechecker(a_typechecker), root_scope_id(a_root_scope_id), root_interpreter_scope(a_root_interpreter_scope), file_id(a_file_id){}

ErrorOr<bool> repl::REPL::handle_possible_error() {
{
TRY((((((*this).compiler))->print_errors())));
bool const has_error = (((((((*this).compiler))->errors)).size()) > static_cast<size_t>(0ULL));
JaktInternal::Array<error::JaktError> const arr = (TRY((Array<error::JaktError>::create_with({}))));
(((((*this).compiler))->errors) = arr);
return (has_error);
}
}

ErrorOr<String> repl::LineResult::debug_description() const {
auto builder = TRY(StringBuilder::create());
switch (this->index()) {case 0 /* Line */: {
[[maybe_unused]] auto const& that = this->template get<LineResult::Line>();
TRY(builder.append("LineResult::Line"));
TRY(builder.appendff("(\"{}\")", that.value));
break;}
case 1 /* Eof */: {
[[maybe_unused]] auto const& that = this->template get<LineResult::Eof>();
TRY(builder.append("LineResult::Eof"));
break;}
}
return builder.to_string();
}
}
} // namespace Jakt
