#include "repl.h"
namespace Jakt {
namespace repl {
ErrorOr<ByteString> serialize_unary_operation(types::CheckedUnaryOperator const op,ByteString const expr) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* PreIncrement */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("++"sv))) + (expr)))));
};/*case end*/
case 1 /* PostIncrement */: {
return JaktInternal::ExplicitValue(TRY((((expr) + ((ByteString::must_from_utf8("++"sv)))))));
};/*case end*/
case 2 /* PreDecrement */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("--"sv))) + (expr)))));
};/*case end*/
case 3 /* PostDecrement */: {
return JaktInternal::ExplicitValue(TRY((((expr) + ((ByteString::must_from_utf8("--"sv)))))));
};/*case end*/
case 4 /* Negate */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("-"sv))) + (expr)))));
};/*case end*/
case 5 /* Dereference */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("*"sv))) + (expr)))));
};/*case end*/
case 6 /* RawAddress */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("&raw "sv))) + (expr)))));
};/*case end*/
case 7 /* Reference */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("&"sv))) + (expr)))));
};/*case end*/
case 8 /* MutableReference */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("&mut "sv))) + (expr)))));
};/*case end*/
case 9 /* LogicalNot */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("not "sv))) + (expr)))));
};/*case end*/
case 10 /* BitwiseNot */: {
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("~"sv))) + (expr)))));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY((((TRY(((((ByteString::must_from_utf8("(<Unimplemented unary operator> "sv))) + (expr))))) + ((ByteString::must_from_utf8(")"sv)))))));
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

ErrorOr<ByteString> serialize_ast_node(NonnullRefPtr<typename types::CheckedExpression> const node) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *node;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}"sv)),val))));
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;types::CheckedNumericConstant const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}i8"sv)),value))));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}i16"sv)),value))));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}i32"sv)),value))));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}i64"sv)),value))));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}u8"sv)),value))));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}u16"sv)),value))));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}u32"sv)),value))));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}u64"sv)),value))));
};/*case end*/
case 9 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}f32"sv)),value))));
};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}f64"sv)),value))));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}uz"sv)),value))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
auto __jakt_enum_value = (((((val).type_id)).equals(types::builtin(types::BuiltinType::JaktString()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("\"{}\""sv)),((val).to_string())))));
}
else {
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("(overloaded) \"{}\""sv)),((val).to_string())))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* ByteConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ByteConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("b'{}'"sv)),val))));
};/*case end*/
case 4 /* CharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CharacterConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("'{}'"sv)),val))));
};/*case end*/
case 5 /* CCharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CCharacterConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("c'{}'"sv)),val))));
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(TRY((repl::serialize_unary_operation(op,TRY((repl::serialize_ast_node(expr)))))));
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_928; {
ByteStringBuilder builder = ByteStringBuilder::create();
TRY((((builder).append_string((ByteString::must_from_utf8("("sv))))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vals).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((i) != (static_cast<size_t>(0ULL)))){
TRY((((builder).append_string((ByteString::must_from_utf8(", "sv))))));
}
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((vals)[i]))))))));
}

}
}

TRY((((builder).append_string((ByteString::must_from_utf8(")"sv))))));
__jakt_var_928 = TRY((((builder).to_string()))); goto __jakt_label_822;

}
__jakt_label_822:; __jakt_var_928.release_value(); }));
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& to = __jakt_match_value.to;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_929; {
ByteString from_output = (ByteString::must_from_utf8(""sv));
if (((from).has_value())){
(from_output = TRY((repl::serialize_ast_node((from.value())))));
}
ByteString to_output = (ByteString::must_from_utf8(""sv));
if (((to).has_value())){
(to_output = TRY((repl::serialize_ast_node((to.value())))));
}
__jakt_var_929 = TRY((__jakt_format((StringView::from_string_literal("{}..{}"sv)),from_output,to_output))); goto __jakt_label_823;

}
__jakt_label_823:; __jakt_var_929.release_value(); }));
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_930; {
ByteStringBuilder builder = ByteStringBuilder::create();
TRY((((builder).append_string((ByteString::must_from_utf8("["sv))))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vals).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((i) != (static_cast<size_t>(0ULL)))){
TRY((((builder).append_string((ByteString::must_from_utf8(", "sv))))));
}
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((vals)[i]))))))));
}

}
}

TRY((((builder).append_string((ByteString::must_from_utf8("]"sv))))));
__jakt_var_930 = TRY((((builder).to_string()))); goto __jakt_label_824;

}
__jakt_label_824:; __jakt_var_930.release_value(); }));
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_931; {
ByteStringBuilder builder = ByteStringBuilder::create();
TRY((((builder).append_string((ByteString::must_from_utf8("{"sv))))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vals).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((i) != (static_cast<size_t>(0ULL)))){
TRY((((builder).append_string((ByteString::must_from_utf8(", "sv))))));
}
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((vals)[i]))))))));
}

}
}

TRY((((builder).append_string((ByteString::must_from_utf8("}"sv))))));
__jakt_var_931 = TRY((((builder).to_string()))); goto __jakt_label_825;

}
__jakt_label_825:; __jakt_var_931.release_value(); }));
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_932; {
ByteStringBuilder builder = ByteStringBuilder::create();
TRY((((builder).append_string((ByteString::must_from_utf8("["sv))))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((vals).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((i) != (static_cast<size_t>(0ULL)))){
TRY((((builder).append_string((ByteString::must_from_utf8(", "sv))))));
}
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> const val = ((vals)[i]);
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((val).template get<0>()))))))));
TRY((((builder).append_string((ByteString::must_from_utf8(": "sv))))));
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((val).template get<1>()))))))));
}

}
}

TRY((((builder).append_string((ByteString::must_from_utf8("]"sv))))));
__jakt_var_932 = TRY((((builder).to_string()))); goto __jakt_label_826;

}
__jakt_label_826:; __jakt_var_932.release_value(); }));
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}[{}]"sv)),TRY((repl::serialize_ast_node(expr))),TRY((repl::serialize_ast_node(index)))))));
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}[{}]"sv)),TRY((repl::serialize_ast_node(expr))),TRY((repl::serialize_ast_node(index)))))));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}.{}"sv)),TRY((repl::serialize_ast_node(expr))),index))));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<ids::VarId> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}.{}"sv)),TRY((repl::serialize_ast_node(expr))),index))));
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;JaktInternal::DynamicArray<types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_933; {
ByteStringBuilder builder = ByteStringBuilder::create();
{
JaktInternal::ArrayIterator<types::CheckedNamespace> _magic = ((namespaces).iterator());
for (;;){
JaktInternal::Optional<types::CheckedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedNamespace namespace_ = (_magic_value.value());
{
TRY((((builder).append_string(((namespace_).name)))));
TRY((((builder).append_string((ByteString::must_from_utf8("::"sv))))));
}

}
}

TRY((((builder).append_string(((var)->name)))));
__jakt_var_933 = TRY((((builder).to_string()))); goto __jakt_label_827;

}
__jakt_label_827:; __jakt_var_933.release_value(); }));
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->name));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue((ByteString::must_from_utf8("None"sv)));
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("Some({})"sv)),TRY((repl::serialize_ast_node(expr)))))));
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}!"sv)),TRY((repl::serialize_ast_node(expr)))))));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_934; {
ByteStringBuilder builder = ByteStringBuilder::create();
{
JaktInternal::ArrayIterator<types::ResolvedNamespace> _magic = ((((call).namespace_)).iterator());
for (;;){
JaktInternal::Optional<types::ResolvedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ResolvedNamespace namespace_ = (_magic_value.value());
{
TRY((((builder).append_string(((namespace_).name)))));
TRY((((builder).append_string((ByteString::must_from_utf8("::"sv))))));
}

}
}

TRY((((builder).append_string(((call).name)))));
TRY((((builder).append_string((ByteString::must_from_utf8("("sv))))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((call).args)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((i) != (static_cast<size_t>(0ULL)))){
TRY((((builder).append_string((ByteString::must_from_utf8(", "sv))))));
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const arg = ((((call).args))[i]);
if ((!(((((arg).template get<0>())).is_empty())))){
TRY((((builder).append_string(((arg).template get<0>())))));
TRY((((builder).append_string((ByteString::must_from_utf8(": "sv))))));
}
TRY((((builder).append_string(TRY((repl::serialize_ast_node(((arg).template get<1>()))))))));
}

}
}

TRY((((builder).append_string((ByteString::must_from_utf8(")"sv))))));
__jakt_var_934 = TRY((((builder).to_string()))); goto __jakt_label_828;

}
__jakt_label_828:; __jakt_var_934.release_value(); }));
};/*case end*/
case 34 /* Garbage */: {
return JaktInternal::ExplicitValue((ByteString::must_from_utf8("<Garbage>"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((ByteString::must_from_utf8("<Unimplemented>"sv)));
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

ErrorOr<ByteString> repl::REPL::debug_description() const { auto builder = ByteStringBuilder::create();TRY(builder.append("REPL("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("compiler: {}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("typechecker: {}, ", typechecker));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("root_scope_id: {}, ", root_scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("root_interpreter_scope: {}, ", *root_interpreter_scope));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("file_id: {}", file_id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<repl::REPL> repl::REPL::create(jakt__path::Path const runtime_path,JaktInternal::Optional<ByteString> const target_triple,JaktInternal::Dictionary<ByteString,ByteString> const user_configuration) {
{
NonnullRefPtr<compiler::Compiler> compiler = TRY((compiler::Compiler::__jakt_create((TRY((DynamicArray<jakt__path::Path>::create_with({})))),(TRY((Dictionary<ByteString, utility::FileId>::create_with_entries({})))),(TRY((DynamicArray<error::JaktError>::create_with({})))),JaktInternal::OptionalNone(),(TRY((DynamicArray<u8>::create_with({})))),false,false,false,false,runtime_path,(TRY((DynamicArray<ByteString>::create_with({})))),false,false,false,false,target_triple,user_configuration,TRY((jakt__path::Path::from_string((ByteString::must_from_utf8("build"sv))))),TRY((jakt__path::Path::from_string((ByteString::must_from_utf8("repl.jakt"sv))))))));
TRY((((compiler)->load_prelude())));
utility::FileId const file_id = TRY((((compiler)->get_file_id_or_register(TRY((jakt__path::Path::from_string((ByteString::must_from_utf8("<repl>"sv)))))))));
ids::ModuleId const placeholder_module_id = ids::ModuleId(static_cast<size_t>(0ULL));
ByteString const root_module_name = (ByteString::must_from_utf8("repl"sv));
typechecker::Typechecker typechecker = typechecker::Typechecker(compiler,TRY((types::CheckedProgram::__jakt_create(compiler,(TRY((DynamicArray<NonnullRefPtr<types::Module>>::create_with({})))),(TRY((Dictionary<ByteString, types::LoadedModule>::create_with_entries({}))))))),placeholder_module_id,ids::TypeId::none(),JaktInternal::OptionalNone(),false,static_cast<size_t>(0ULL),false,((compiler)->dump_type_hints),((compiler)->dump_try_hints),static_cast<u64>(0ULL),types::GenericInferences((TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}))))),JaktInternal::OptionalNone(),root_module_name,false,false,(TRY((Dictionary<ByteString, ids::ScopeId>::create_with_entries({})))),JaktInternal::OptionalNone());
(((compiler)->current_file) = file_id);
TRY((((typechecker).include_prelude())));
ids::ModuleId const root_module_id = TRY((((typechecker).create_module(root_module_name,true,JaktInternal::OptionalNone()))));
(((typechecker).current_module_id) = root_module_id);
TRY((((((typechecker).program))->set_loaded_module(root_module_name,types::LoadedModule(root_module_id,file_id)))));
ids::ScopeId const PRELUDE_SCOPE_ID = ((typechecker).prelude_scope_id());
ids::ScopeId const root_scope_id = TRY((((typechecker).create_scope(PRELUDE_SCOPE_ID,true,(ByteString::must_from_utf8("root"sv)),true))));
TRY((((typechecker).typecheck_module_import(parser::ParsedModuleImport(parser::ImportName::Literal((ByteString::must_from_utf8("jakt::prelude::prelude"sv)),utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))),JaktInternal::OptionalNone(),parser::ImportList::All(),false,static_cast<size_t>(0ULL)),root_scope_id))));
NonnullRefPtr<interpreter::InterpreterScope> const root_interpreter_scope = TRY((interpreter::InterpreterScope::create((TRY((Dictionary<ByteString, types::Value>::create_with_entries({})))),JaktInternal::OptionalNone(),(TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))))));
return repl::REPL(compiler,typechecker,root_scope_id,root_interpreter_scope,file_id);
}
}

ErrorOr<JaktInternal::DynamicArray<u8>> repl::REPL::line_to_bytes(ByteString const line) {
{
size_t pos = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<u8> bytes_ = (TRY((DynamicArray<u8>::create_with({}))));
TRY((((bytes_).ensure_capacity(((line).length())))));
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
(pos,((line).length()))){
TRY((((bytes_).push(((line).byte_at(pos))))));
(++(pos));
}
return bytes_;
}
}

ErrorOr<void> repl::REPL::run() {
{
Function<ErrorOr<void>(repl_backend__default::Editor&)> const syntax_highlight_handler = [this](repl_backend__default::Editor& editor) -> ErrorOr<void> {
{
ByteString const line = TRY((((((editor))).get_active_buffer())));
size_t pos = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<u8> bytes_ = (TRY((DynamicArray<u8>::create_with({}))));
TRY((((bytes_).ensure_capacity(((line).length())))));
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
(pos,((line).length()))){
TRY((((bytes_).push(((line).byte_at(pos))))));
(++(pos));
}
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = bytes_);
ScopeGuard __jakt_var_935([&] {
{
JaktInternal::DynamicArray<error::JaktError> const arr = (MUST((DynamicArray<error::JaktError>::create_with({}))));
(((((*this).compiler))->errors) = arr);
}

});
{
JaktInternal::ArrayIterator<lexer::Token> _magic = ((({ Optional<JaktInternal::DynamicArray<lexer::Token>> __jakt_var_936;
auto __jakt_var_937 = [&]() -> ErrorOr<JaktInternal::DynamicArray<lexer::Token>> { return TRY((lexer::Lexer::lex(((*this).compiler)))); }();
if (__jakt_var_937.is_error()) {{
return {};
}
} else {__jakt_var_936 = __jakt_var_937.release_value();
}
__jakt_var_936.release_value(); })).iterator());
for (;;){
JaktInternal::Optional<lexer::Token> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;utility::Span const& span = __jakt_match_value.span;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Green()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;utility::Span const& span = __jakt_match_value.span;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Green()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;utility::Span const& span = __jakt_match_value.span;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Blue()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59 /* And */: {
auto&& __jakt_match_value = __jakt_match_variant.as.And;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60 /* Anon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Anon;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 61 /* As */: {
auto&& __jakt_match_value = __jakt_match_variant.as.As;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boxed;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 63 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 64 /* Catch */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Catch;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 66 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 67 /* Cpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Cpp;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 68 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 69 /* Destructor */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Destructor;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 70 /* Else */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Else;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 72 /* Extern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Extern;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 73 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 74 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* Fn */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fn;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 77 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 78 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 80 /* In */: {
auto&& __jakt_match_value = __jakt_match_variant.as.In;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 81 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 82 /* Let */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Let;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 83 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 84 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 85 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 86 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 88 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 89 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 93 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 94 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 95 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 97 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 100 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 101 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 102 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 103 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 104 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 106 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 107 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 108 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 109 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 110 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 111 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 54 /* DotDot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DotDot;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Cyan()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;utility::Span const& span = __jakt_match_value.span;
JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
{
if (((comment).has_value())){
TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::Components(static_cast<u8>(128),static_cast<u8>(128),static_cast<u8>(128)),JaktInternal::OptionalNone())))));
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
return {};
}
;
repl_backend__default::Editor editor = TRY((repl_backend__default::Editor::create((ByteString::must_from_utf8("> "sv)),((syntax_highlight_handler)))));
ScopeGuard __jakt_var_938([&] {
((editor).destroy());
});
for (;;){
if ((!(((((((*this).compiler))->errors)).is_empty())))){
TRY((((((*this).compiler))->print_errors())));
JaktInternal::DynamicArray<error::JaktError> const arr = (TRY((DynamicArray<error::JaktError>::create_with({}))));
(((((*this).compiler))->errors) = arr);
}
repl_backend__common::LineResult const line_result = ({ Optional<repl_backend__common::LineResult> __jakt_var_939;
auto __jakt_var_940 = [&]() -> ErrorOr<repl_backend__common::LineResult> { return TRY((((editor).get_line(JaktInternal::OptionalNone())))); }();
if (__jakt_var_940.is_error()) {auto error = __jakt_var_940.release_error();
{
return {};
}
} else {__jakt_var_939 = __jakt_var_940.release_value();
}
__jakt_var_939.release_value(); });
if (((line_result).__jakt_init_index() == 0 /* Line */)){
ByteString const line = (line_result).as.Line.value;
if (((line) == ((ByteString::must_from_utf8("\n"sv))))){
continue;
}
if (((line) == ((ByteString::must_from_utf8(".exit\n"sv))))){
break;
}
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = TRY((repl::REPL::line_to_bytes(line))));
JaktInternal::DynamicArray<lexer::Token> tokens = ({ Optional<JaktInternal::DynamicArray<lexer::Token>> __jakt_var_941;
auto __jakt_var_942 = [&]() -> ErrorOr<JaktInternal::DynamicArray<lexer::Token>> { return TRY((lexer::Lexer::lex(((*this).compiler)))); }();
if (__jakt_var_942.is_error()) {{
continue;
}
} else {__jakt_var_941 = __jakt_var_942.release_value();
}
__jakt_var_941.release_value(); });
if (((tokens).is_empty())){
continue;
}
if ((!(repl::REPL::check_parens(tokens)))){
ByteStringBuilder sb = ByteStringBuilder::create();
TRY((((sb).append_string(line))));
while ((!(repl::REPL::check_parens(tokens)))){
repl_backend__common::LineResult const line_result = ({ Optional<repl_backend__common::LineResult> __jakt_var_943;
auto __jakt_var_944 = [&]() -> ErrorOr<repl_backend__common::LineResult> { return TRY((((editor).get_line((ByteString::must_from_utf8(".."sv)))))); }();
if (__jakt_var_944.is_error()) {auto error = __jakt_var_944.release_error();
{
return {};
}
} else {__jakt_var_943 = __jakt_var_944.release_value();
}
__jakt_var_943.release_value(); });
if (((line_result).__jakt_init_index() == 0 /* Line */)){
ByteString const line = (line_result).as.Line.value;
TRY((((sb).append_string(line))));
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = TRY((repl::REPL::line_to_bytes(TRY((((sb).to_string())))))));
(tokens = ({ Optional<JaktInternal::DynamicArray<lexer::Token>> __jakt_var_945;
auto __jakt_var_946 = [&]() -> ErrorOr<JaktInternal::DynamicArray<lexer::Token>> { return TRY((lexer::Lexer::lex(((*this).compiler)))); }();
if (__jakt_var_946.is_error()) {{
continue;
}
} else {__jakt_var_945 = __jakt_var_946.release_value();
}
__jakt_var_945.release_value(); }));
}
else {
return {};
}

}
}
parser::Parser parser = parser::Parser(static_cast<size_t>(0ULL),tokens,((*this).compiler),true,static_cast<size_t>(0ULL));
lexer::Token const first_token = (((tokens).first()).value());
if (((((((((((first_token).__jakt_init_index() == 75 /* Fn */) || ((first_token).__jakt_init_index() == 76 /* Comptime */)) || ((first_token).__jakt_init_index() == 97 /* Struct */)) || ((first_token).__jakt_init_index() == 65 /* Class */)) || ((first_token).__jakt_init_index() == 71 /* Enum */)) || ((first_token).__jakt_init_index() == 62 /* Boxed */)) || ((first_token).__jakt_init_index() == 86 /* Namespace */)) || ((first_token).__jakt_init_index() == 78 /* Import */)) || ((first_token).__jakt_init_index() == 111 /* Trait */))){
parser::ParsedNamespace const parsed_namespace = ({ Optional<parser::ParsedNamespace> __jakt_var_947;
auto __jakt_var_948 = [&]() -> ErrorOr<parser::ParsedNamespace> { return TRY((((parser).parse_namespace(false)))); }();
if (__jakt_var_948.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_947 = __jakt_var_948.release_value();
}
__jakt_var_947.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
auto __jakt_var_950 = [&]() -> ErrorOr<void> { return TRY((((((*this).typechecker)).typecheck_module(parsed_namespace,((*this).root_scope_id))))), ErrorOr<void>{}; }();
if (__jakt_var_950.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
}
;
TRY((((*this).handle_possible_error())));
continue;
}
NonnullRefPtr<typename parser::ParsedStatement> const parsed_statement = ({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_951;
auto __jakt_var_952 = [&]() -> ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> { return TRY((((parser).parse_statement(true)))); }();
if (__jakt_var_952.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_951 = __jakt_var_952.release_value();
}
__jakt_var_951.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
NonnullRefPtr<typename types::CheckedStatement> const checked_statement = ({ Optional<NonnullRefPtr<typename types::CheckedStatement>> __jakt_var_953;
auto __jakt_var_954 = [&]() -> ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> { return TRY((((((*this).typechecker)).typecheck_statement(parsed_statement,((*this).root_scope_id),types::SafetyMode::Safe(),JaktInternal::OptionalNone())))); }();
if (__jakt_var_954.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_953 = __jakt_var_954.release_value();
}
__jakt_var_953.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
NonnullRefPtr<interpreter::Interpreter> interpreter = TRY((((((*this).typechecker)).interpreter())));
interpreter::StatementResult const result = ({ Optional<interpreter::StatementResult> __jakt_var_955;
auto __jakt_var_956 = [&]() -> ErrorOr<interpreter::StatementResult> { return TRY((((interpreter)->execute_statement(checked_statement,((*this).root_interpreter_scope),utility::Span(((*this).file_id),static_cast<size_t>(0ULL),((line).length())))))); }();
if (__jakt_var_956.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_955 = __jakt_var_956.release_value();
}
__jakt_var_955.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
{
if (((((value).impl))->__jakt_init_index() == 0 /* Void */)){
return JaktInternal::LoopContinue{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
{
if (((((value).impl))->__jakt_init_index() == 0 /* Void */)){
return JaktInternal::LoopContinue{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
{
if (((((value).impl))->__jakt_init_index() == 0 /* Void */)){
return JaktInternal::LoopContinue{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
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
ByteString const output = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((repl::serialize_ast_node(TRY((interpreter::value_to_checked_expression(value,interpreter)))))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((repl::serialize_ast_node(TRY((interpreter::value_to_checked_expression(value,interpreter)))))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY(((((ByteString::must_from_utf8("throw "sv))) + (TRY((repl::serialize_ast_node(TRY((interpreter::value_to_checked_expression(value,interpreter)))))))))));
};/*case end*/
case 4 /* Break */: {
{
return JaktInternal::LoopContinue{};
}
};/*case end*/
case 3 /* Continue */: {
{
return JaktInternal::LoopContinue{};
}
};/*case end*/
case 2 /* Yield */: {
{
return JaktInternal::LoopContinue{};
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
});
outln((StringView::from_string_literal("= {}"sv)),output);
}
else {
break;
}

}
}
return {};
}

repl::REPL::REPL(NonnullRefPtr<compiler::Compiler> a_compiler, typechecker::Typechecker a_typechecker, ids::ScopeId a_root_scope_id, NonnullRefPtr<interpreter::InterpreterScope> a_root_interpreter_scope, utility::FileId a_file_id): compiler(move(a_compiler)), typechecker(move(a_typechecker)), root_scope_id(move(a_root_scope_id)), root_interpreter_scope(move(a_root_interpreter_scope)), file_id(move(a_file_id)){}

ErrorOr<bool> repl::REPL::handle_possible_error() {
{
TRY((((((*this).compiler))->print_errors())));
bool const has_error = [](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((((*this).compiler))->errors)).size()),static_cast<size_t>(0ULL));
JaktInternal::DynamicArray<error::JaktError> const arr = (TRY((DynamicArray<error::JaktError>::create_with({}))));
(((((*this).compiler))->errors) = arr);
return has_error;
}
}

bool repl::REPL::check_parens(JaktInternal::DynamicArray<lexer::Token> const tokens) {
{
i64 unmatched_parens = static_cast<i64>(0LL);
i64 unmatched_brackets = static_cast<i64>(0LL);
i64 unmatched_curlies = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<lexer::Token> _magic = ((tokens).iterator());
for (;;){
JaktInternal::Optional<lexer::Token> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
lexer::Token token = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, bool>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* LParen */: {
{
((unmatched_parens) += (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* RParen */: {
{
((unmatched_parens) -= (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* LSquare */: {
{
((unmatched_brackets) += (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* RSquare */: {
{
((unmatched_brackets) -= (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* LCurly */: {
{
((unmatched_curlies) += (static_cast<i64>(1LL)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* RCurly */: {
{
((unmatched_curlies) -= (static_cast<i64>(1LL)));
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

return (((unmatched_parens) == (static_cast<i64>(0LL))) && (((unmatched_brackets) == (static_cast<i64>(0LL))) && ((unmatched_curlies) == (static_cast<i64>(0LL)))));
}
}

}
} // namespace Jakt
