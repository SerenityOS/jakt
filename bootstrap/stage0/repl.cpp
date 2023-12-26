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
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("++"sv))) + (expr)));
};/*case end*/
case 1 /* PostIncrement */: {
return JaktInternal::ExplicitValue(((expr) + ((ByteString::from_utf8_without_validation("++"sv)))));
};/*case end*/
case 2 /* PreDecrement */: {
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("--"sv))) + (expr)));
};/*case end*/
case 3 /* PostDecrement */: {
return JaktInternal::ExplicitValue(((expr) + ((ByteString::from_utf8_without_validation("--"sv)))));
};/*case end*/
case 4 /* Negate */: {
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("-"sv))) + (expr)));
};/*case end*/
case 5 /* Dereference */: {
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("*"sv))) + (expr)));
};/*case end*/
case 6 /* RawAddress */: {
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("&raw "sv))) + (expr)));
};/*case end*/
case 7 /* Reference */: {
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("&"sv))) + (expr)));
};/*case end*/
case 8 /* MutableReference */: {
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("&mut "sv))) + (expr)));
};/*case end*/
case 9 /* LogicalNot */: {
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("not "sv))) + (expr)));
};/*case end*/
case 10 /* BitwiseNot */: {
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("~"sv))) + (expr)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((((((ByteString::from_utf8_without_validation("(<Unimplemented unary operator> "sv))) + (expr))) + ((ByteString::from_utf8_without_validation(")"sv)))));
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
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}"sv)),val));
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;types::CheckedNumericConstant const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}i8"sv)),value));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}i16"sv)),value));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}i32"sv)),value));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}i64"sv)),value));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}u8"sv)),value));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}u16"sv)),value));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}u32"sv)),value));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}u64"sv)),value));
};/*case end*/
case 9 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}f32"sv)),value));
};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}f64"sv)),value));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}uz"sv)),value));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (((((val).type_id)).equals(types::builtin(types::BuiltinType::JaktString()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("\"{}\""sv)),((val).to_string())));
}
else {
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("(overloaded) \"{}\""sv)),((val).to_string())));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* ByteConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ByteConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("b'{}'"sv)),val));
};/*case end*/
case 4 /* CharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CharacterConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("'{}'"sv)),val));
};/*case end*/
case 5 /* CCharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CCharacterConstant;ByteString const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("c'{}'"sv)),val));
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(TRY((repl::serialize_unary_operation(op,TRY((repl::serialize_ast_node(expr)))))));
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_906; {
ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append((StringView::from_string_literal("("sv))));
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
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(TRY((repl::serialize_ast_node(((vals)[i]))))));
}

}
}

((builder).append((StringView::from_string_literal(")"sv))));
__jakt_var_906 = ((builder).to_string()); goto __jakt_label_798;

}
__jakt_label_798:; __jakt_var_906.release_value(); }));
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& to = __jakt_match_value.to;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_907; {
ByteString from_output = (ByteString::from_utf8_without_validation(""sv));
if (((from).has_value())){
(from_output = TRY((repl::serialize_ast_node((from.value())))));
}
ByteString to_output = (ByteString::from_utf8_without_validation(""sv));
if (((to).has_value())){
(to_output = TRY((repl::serialize_ast_node((to.value())))));
}
__jakt_var_907 = __jakt_format((StringView::from_string_literal("{}..{}"sv)),from_output,to_output); goto __jakt_label_799;

}
__jakt_label_799:; __jakt_var_907.release_value(); }));
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_908; {
ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append((StringView::from_string_literal("["sv))));
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
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(TRY((repl::serialize_ast_node(((vals)[i]))))));
}

}
}

((builder).append((StringView::from_string_literal("]"sv))));
__jakt_var_908 = ((builder).to_string()); goto __jakt_label_800;

}
__jakt_label_800:; __jakt_var_908.release_value(); }));
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_909; {
ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append((StringView::from_string_literal("{"sv))));
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
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(TRY((repl::serialize_ast_node(((vals)[i]))))));
}

}
}

((builder).append((StringView::from_string_literal("}"sv))));
__jakt_var_909 = ((builder).to_string()); goto __jakt_label_801;

}
__jakt_label_801:; __jakt_var_909.release_value(); }));
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_910; {
ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append((StringView::from_string_literal("["sv))));
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
((builder).append((StringView::from_string_literal(", "sv))));
}
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> const val = ((vals)[i]);
((builder).append(TRY((repl::serialize_ast_node(((val).template get<0>()))))));
((builder).append((StringView::from_string_literal(": "sv))));
((builder).append(TRY((repl::serialize_ast_node(((val).template get<1>()))))));
}

}
}

((builder).append((StringView::from_string_literal("]"sv))));
__jakt_var_910 = ((builder).to_string()); goto __jakt_label_802;

}
__jakt_label_802:; __jakt_var_910.release_value(); }));
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}[{}]"sv)),TRY((repl::serialize_ast_node(expr))),TRY((repl::serialize_ast_node(index)))));
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}[{}]"sv)),TRY((repl::serialize_ast_node(expr))),TRY((repl::serialize_ast_node(index)))));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}.{}"sv)),TRY((repl::serialize_ast_node(expr))),index));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<ids::VarId> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}.{}"sv)),TRY((repl::serialize_ast_node(expr))),index));
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;JaktInternal::DynamicArray<types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_911; {
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
((builder).append(((namespace_).name)));
((builder).append((StringView::from_string_literal("::"sv))));
}

}
}

((builder).append(((var)->name)));
__jakt_var_911 = ((builder).to_string()); goto __jakt_label_803;

}
__jakt_label_803:; __jakt_var_911.release_value(); }));
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->name));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("None"sv)));
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("Some({})"sv)),TRY((repl::serialize_ast_node(expr)))));
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}!"sv)),TRY((repl::serialize_ast_node(expr)))));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_912; {
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
((builder).append(((namespace_).name)));
((builder).append((StringView::from_string_literal("::"sv))));
}

}
}

((builder).append(((call).name)));
((builder).append((StringView::from_string_literal("("sv))));
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
((builder).append((StringView::from_string_literal(", "sv))));
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>> const arg = ((((call).args))[i]);
if ((!(((((arg).template get<0>())).is_empty())))){
((builder).append(((arg).template get<0>())));
((builder).append((StringView::from_string_literal(": "sv))));
}
((builder).append(TRY((repl::serialize_ast_node(((arg).template get<1>()))))));
}

}
}

((builder).append((StringView::from_string_literal(")"sv))));
__jakt_var_912 = ((builder).to_string()); goto __jakt_label_804;

}
__jakt_label_804:; __jakt_var_912.release_value(); }));
};/*case end*/
case 35 /* Garbage */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("<Garbage>"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("<Unimplemented>"sv)));
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

ByteString repl::REPL::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("REPL("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("typechecker: {}, ", typechecker);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("root_scope_id: {}, ", root_scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("root_interpreter_scope: {}, ", *root_interpreter_scope);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("file_id: {}", file_id);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<repl::REPL> repl::REPL::create(jakt__path::Path const runtime_path,JaktInternal::Optional<ByteString> const target_triple,JaktInternal::Dictionary<ByteString,ByteString> const user_configuration) {
{
NonnullRefPtr<compiler::Compiler> compiler = compiler::Compiler::__jakt_create(DynamicArray<jakt__path::Path>::create_with({}),Dictionary<ByteString, utility::FileId>::create_with_entries({}),DynamicArray<error::JaktError>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<u8>::create_with({}),false,false,false,false,runtime_path,DynamicArray<ByteString>::create_with({}),false,false,false,false,target_triple,user_configuration,jakt__path::Path::from_string((ByteString::from_utf8_without_validation("build"sv))),jakt__path::Path::from_string((ByteString::from_utf8_without_validation("repl.jakt"sv))));
TRY((((compiler)->load_prelude())));
utility::FileId const file_id = ((compiler)->get_file_id_or_register(jakt__path::Path::from_string((ByteString::from_utf8_without_validation("<repl>"sv)))));
ids::ModuleId const placeholder_module_id = ids::ModuleId(static_cast<size_t>(0ULL));
ByteString const root_module_name = (ByteString::from_utf8_without_validation("repl"sv));
typechecker::Typechecker typechecker = typechecker::Typechecker(compiler,types::CheckedProgram::__jakt_create(compiler,DynamicArray<NonnullRefPtr<types::Module>>::create_with({}),Dictionary<ByteString, types::LoadedModule>::create_with_entries({})),placeholder_module_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,false,((compiler)->dump_type_hints),((compiler)->dump_try_hints),static_cast<u64>(0ULL),types::GenericInferences(Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})),JaktInternal::OptionalNone(),root_module_name,false,false,Dictionary<ByteString, ids::ScopeId>::create_with_entries({}),JaktInternal::OptionalNone());
(((compiler)->current_file) = file_id);
TRY((((typechecker).include_prelude())));
ids::ModuleId const root_module_id = ((typechecker).create_module(root_module_name,true,JaktInternal::OptionalNone()));
(((typechecker).current_module_id) = root_module_id);
((((typechecker).program))->set_loaded_module(root_module_name,types::LoadedModule(root_module_id,file_id)));
ids::ScopeId const PRELUDE_SCOPE_ID = ((typechecker).prelude_scope_id());
ids::ScopeId const root_scope_id = ((typechecker).create_scope(PRELUDE_SCOPE_ID,true,(ByteString::from_utf8_without_validation("root"sv)),true));
TRY((((typechecker).typecheck_module_import(parser::ParsedModuleImport(parser::ImportName::Literal((ByteString::from_utf8_without_validation("jakt::prelude::prelude"sv)),utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))),JaktInternal::OptionalNone(),parser::ImportList::All(),false,static_cast<size_t>(0ULL)),root_scope_id))));
NonnullRefPtr<interpreter::InterpreterScope> const root_interpreter_scope = interpreter::InterpreterScope::create(Dictionary<ByteString, types::Value>::create_with_entries({}),JaktInternal::OptionalNone(),Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}));
return repl::REPL(compiler,typechecker,root_scope_id,root_interpreter_scope,file_id);
}
}

ErrorOr<bool> repl::REPL::handle_possible_error() {
{
TRY((((((*this).compiler))->print_errors())));
bool const has_error = [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((((*this).compiler))->errors)).size()),static_cast<size_t>(0ULL));
JaktInternal::DynamicArray<error::JaktError> const arr = DynamicArray<error::JaktError>::create_with({});
(((((*this).compiler))->errors) = arr);
return has_error;
}
}

JaktInternal::DynamicArray<u8> repl::REPL::line_to_bytes(ByteString const line) {
{
size_t pos = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<u8> bytes_ = DynamicArray<u8>::create_with({});
((bytes_).ensure_capacity(((line).length())));
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(pos,((line).length()))){
((bytes_).push(((line).byte_at(pos))));
(++(pos));
}
return bytes_;
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

ErrorOr<void> repl::REPL::run() {
{
Function<ErrorOr<void>(repl_backend__default::Editor&)> const syntax_highlight_handler = [this](repl_backend__default::Editor& editor) -> ErrorOr<void> {{
ByteString const line = TRY((((((editor))).get_active_buffer())));
size_t pos = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<u8> bytes_ = DynamicArray<u8>::create_with({});
((bytes_).ensure_capacity(((line).length())));
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(pos,((line).length()))){
((bytes_).push(((line).byte_at(pos))));
(++(pos));
}
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = bytes_);
ScopeGuard __jakt_var_913([&] {
{
JaktInternal::DynamicArray<error::JaktError> const arr = DynamicArray<error::JaktError>::create_with({});
(((((*this).compiler))->errors) = arr);
}

});
{
JaktInternal::ArrayIterator<lexer::Token> _magic = ((({ Optional<JaktInternal::DynamicArray<lexer::Token>> __jakt_var_914;
auto __jakt_var_915 = [&]() -> ErrorOr<JaktInternal::DynamicArray<lexer::Token>> { return lexer::Lexer::lex(((*this).compiler)); }();
if (__jakt_var_915.is_error()) {{
return {};
}
} else {__jakt_var_914 = __jakt_var_915.release_value();
}
__jakt_var_914.release_value(); })).iterator());
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
case 86 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 88 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 89 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 93 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 94 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 95 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 97 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 100 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 101 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 102 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 103 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 104 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 106 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 107 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 108 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 109 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 110 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 111 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;utility::Span const& span = __jakt_match_value.value;
return (TRY((((((editor))).highlight(span,repl_backend__common::Style(repl_backend__common::Color::XTerm(repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))))), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 112 /* Trait */: {
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
repl_backend__default::Editor editor = TRY((repl_backend__default::Editor::create((ByteString::from_utf8_without_validation("> "sv)),((syntax_highlight_handler)))));
ScopeGuard __jakt_var_916([&] {
((editor).destroy());
});
for (;;){
if ((!(((((((*this).compiler))->errors)).is_empty())))){
TRY((((((*this).compiler))->print_errors())));
JaktInternal::DynamicArray<error::JaktError> const arr = DynamicArray<error::JaktError>::create_with({});
(((((*this).compiler))->errors) = arr);
}
repl_backend__common::LineResult const line_result = ({ Optional<repl_backend__common::LineResult> __jakt_var_917;
auto __jakt_var_918 = [&]() -> ErrorOr<repl_backend__common::LineResult> { return TRY((((editor).get_line(JaktInternal::OptionalNone())))); }();
if (__jakt_var_918.is_error()) {auto error = __jakt_var_918.release_error();
{
return {};
}
} else {__jakt_var_917 = __jakt_var_918.release_value();
}
__jakt_var_917.release_value(); });
if (((line_result).__jakt_init_index() == 0 /* Line */)){
ByteString const line = (line_result).as.Line.value;
if (((line) == ((ByteString::from_utf8_without_validation("\n"sv))))){
continue;
}
if (((line) == ((ByteString::from_utf8_without_validation(".exit\n"sv))))){
break;
}
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = repl::REPL::line_to_bytes(line));
JaktInternal::DynamicArray<lexer::Token> tokens = ({ Optional<JaktInternal::DynamicArray<lexer::Token>> __jakt_var_919;
auto __jakt_var_920 = [&]() -> ErrorOr<JaktInternal::DynamicArray<lexer::Token>> { return lexer::Lexer::lex(((*this).compiler)); }();
if (__jakt_var_920.is_error()) {{
continue;
}
} else {__jakt_var_919 = __jakt_var_920.release_value();
}
__jakt_var_919.release_value(); });
if (((tokens).is_empty())){
continue;
}
if ((!(repl::REPL::check_parens(tokens)))){
ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append(line));
while ((!(repl::REPL::check_parens(tokens)))){
repl_backend__common::LineResult const line_result = ({ Optional<repl_backend__common::LineResult> __jakt_var_921;
auto __jakt_var_922 = [&]() -> ErrorOr<repl_backend__common::LineResult> { return TRY((((editor).get_line((ByteString::from_utf8_without_validation(".."sv)))))); }();
if (__jakt_var_922.is_error()) {auto error = __jakt_var_922.release_error();
{
return {};
}
} else {__jakt_var_921 = __jakt_var_922.release_value();
}
__jakt_var_921.release_value(); });
if (((line_result).__jakt_init_index() == 0 /* Line */)){
ByteString const line = (line_result).as.Line.value;
((builder).append(line));
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = repl::REPL::line_to_bytes(((builder).to_string())));
(tokens = ({ Optional<JaktInternal::DynamicArray<lexer::Token>> __jakt_var_923;
auto __jakt_var_924 = [&]() -> ErrorOr<JaktInternal::DynamicArray<lexer::Token>> { return lexer::Lexer::lex(((*this).compiler)); }();
if (__jakt_var_924.is_error()) {{
continue;
}
} else {__jakt_var_923 = __jakt_var_924.release_value();
}
__jakt_var_923.release_value(); }));
}
else {
return {};
}

}
}
parser::Parser parser = parser::Parser(static_cast<size_t>(0ULL),tokens,((*this).compiler),true,static_cast<size_t>(0ULL));
lexer::Token const first_token = (((tokens).first()).value());
if (((((((((((first_token).__jakt_init_index() == 75 /* Fn */) || ((first_token).__jakt_init_index() == 76 /* Comptime */)) || ((first_token).__jakt_init_index() == 98 /* Struct */)) || ((first_token).__jakt_init_index() == 65 /* Class */)) || ((first_token).__jakt_init_index() == 71 /* Enum */)) || ((first_token).__jakt_init_index() == 62 /* Boxed */)) || ((first_token).__jakt_init_index() == 87 /* Namespace */)) || ((first_token).__jakt_init_index() == 78 /* Import */)) || ((first_token).__jakt_init_index() == 112 /* Trait */))){
parser::ParsedNamespace const parsed_namespace = ({ Optional<parser::ParsedNamespace> __jakt_var_925;
auto __jakt_var_926 = [&]() -> ErrorOr<parser::ParsedNamespace> { return ((parser).parse_namespace(false)); }();
if (__jakt_var_926.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_925 = __jakt_var_926.release_value();
}
__jakt_var_925.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
auto __jakt_var_928 = [&]() -> ErrorOr<void> { return TRY((((((*this).typechecker)).typecheck_module(parsed_namespace,((*this).root_scope_id))))), ErrorOr<void>{}; }();
if (__jakt_var_928.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
}
;
TRY((((*this).handle_possible_error())));
continue;
}
NonnullRefPtr<typename parser::ParsedStatement> const parsed_statement = ({ Optional<NonnullRefPtr<typename parser::ParsedStatement>> __jakt_var_929;
auto __jakt_var_930 = [&]() -> ErrorOr<NonnullRefPtr<typename parser::ParsedStatement>> { return ((parser).parse_statement(true)); }();
if (__jakt_var_930.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_929 = __jakt_var_930.release_value();
}
__jakt_var_929.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
NonnullRefPtr<typename types::CheckedStatement> const checked_statement = ({ Optional<NonnullRefPtr<typename types::CheckedStatement>> __jakt_var_931;
auto __jakt_var_932 = [&]() -> ErrorOr<NonnullRefPtr<typename types::CheckedStatement>> { return TRY((((((*this).typechecker)).typecheck_statement(parsed_statement,((*this).root_scope_id),types::SafetyMode::Safe(),JaktInternal::OptionalNone())))); }();
if (__jakt_var_932.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_931 = __jakt_var_932.release_value();
}
__jakt_var_931.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
NonnullRefPtr<interpreter::Interpreter> interpreter = ((((*this).typechecker)).interpreter());
interpreter::StatementResult const result = ({ Optional<interpreter::StatementResult> __jakt_var_933;
auto __jakt_var_934 = [&]() -> ErrorOr<interpreter::StatementResult> { return TRY((((interpreter)->execute_statement(checked_statement,((*this).root_interpreter_scope),utility::Span(((*this).file_id),static_cast<size_t>(0ULL),((line).length())))))); }();
if (__jakt_var_934.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_933 = __jakt_var_934.release_value();
}
__jakt_var_933.release_value(); });
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
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("throw "sv))) + (TRY((repl::serialize_ast_node(TRY((interpreter::value_to_checked_expression(value,interpreter)))))))));
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

}
} // namespace Jakt
