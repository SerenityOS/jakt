#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "repl.h"
#include "repl_backend__common.h"
#include "codegen.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace repl {
ErrorOr<ByteString> serialize_unary_operation(Jakt::types::CheckedUnaryOperator const op,ByteString const expr) {
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

ErrorOr<ByteString> serialize_ast_node(NonnullRefPtr<typename Jakt::types::CheckedExpression> const node) {
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
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;Jakt::types::CheckedNumericConstant const& val = __jakt_match_value.val;
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
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;Jakt::types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (((((val).type_id)).equals(Jakt::types::builtin(Jakt::types::BuiltinType::JaktString()))));
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
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedUnaryOperator const& op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(TRY((Jakt::repl::serialize_unary_operation(op,TRY((Jakt::repl::serialize_ast_node(expr)))))));
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
{
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
((builder).append(TRY((Jakt::repl::serialize_ast_node(((vals)[i]))))));
}

}
}

((builder).append((StringView::from_string_literal(")"sv))));
return JaktInternal::ExplicitValue<ByteString>(((builder).to_string()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& to = __jakt_match_value.to;
{
ByteString from_output = (ByteString::from_utf8_without_validation(""sv));
if (((from).has_value())){
(from_output = TRY((Jakt::repl::serialize_ast_node((from.value())))));
}
ByteString to_output = (ByteString::from_utf8_without_validation(""sv));
if (((to).has_value())){
(to_output = TRY((Jakt::repl::serialize_ast_node((to.value())))));
}
return JaktInternal::ExplicitValue<ByteString>(__jakt_format((StringView::from_string_literal("{}..{}"sv)),from_output,to_output));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
{
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
((builder).append(TRY((Jakt::repl::serialize_ast_node(((vals)[i]))))));
}

}
}

((builder).append((StringView::from_string_literal("]"sv))));
return JaktInternal::ExplicitValue<ByteString>(((builder).to_string()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
{
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
((builder).append(TRY((Jakt::repl::serialize_ast_node(((vals)[i]))))));
}

}
}

((builder).append((StringView::from_string_literal("}"sv))));
return JaktInternal::ExplicitValue<ByteString>(((builder).to_string()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
{
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
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const val = ((vals)[i]);
((builder).append(TRY((Jakt::repl::serialize_ast_node(((val).template get<0>()))))));
((builder).append((StringView::from_string_literal(": "sv))));
((builder).append(TRY((Jakt::repl::serialize_ast_node(((val).template get<1>()))))));
}

}
}

((builder).append((StringView::from_string_literal("]"sv))));
return JaktInternal::ExplicitValue<ByteString>(((builder).to_string()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}[{}]"sv)),TRY((Jakt::repl::serialize_ast_node(expr))),TRY((Jakt::repl::serialize_ast_node(index)))));
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}[{}]"sv)),TRY((Jakt::repl::serialize_ast_node(expr))),TRY((Jakt::repl::serialize_ast_node(index)))));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}.{}"sv)),TRY((Jakt::repl::serialize_ast_node(expr))),index));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<Jakt::ids::VarId> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}.{}"sv)),TRY((Jakt::repl::serialize_ast_node(expr))),index));
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;JaktInternal::DynamicArray<Jakt::types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
{
ByteStringBuilder builder = ByteStringBuilder::create();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedNamespace> _magic = ((namespaces).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedNamespace namespace_ = (_magic_value.value());
{
((builder).append(((namespace_).name)));
((builder).append((StringView::from_string_literal("::"sv))));
}

}
}

((builder).append(((var)->name)));
return JaktInternal::ExplicitValue<ByteString>(((builder).to_string()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->name));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("None"sv)));
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("Some({})"sv)),TRY((Jakt::repl::serialize_ast_node(expr)))));
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}!"sv)),TRY((Jakt::repl::serialize_ast_node(expr)))));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
{
ByteStringBuilder builder = ByteStringBuilder::create();
{
JaktInternal::ArrayIterator<Jakt::types::ResolvedNamespace> _magic = ((((call).namespace_)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::ResolvedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::ResolvedNamespace namespace_ = (_magic_value.value());
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
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const arg = ((((call).args))[i]);
if ((!(((((arg).template get<0>())).is_empty())))){
((builder).append(((arg).template get<0>())));
((builder).append((StringView::from_string_literal(": "sv))));
}
((builder).append(TRY((Jakt::repl::serialize_ast_node(((arg).template get<1>()))))));
}

}
}

((builder).append((StringView::from_string_literal(")"sv))));
return JaktInternal::ExplicitValue<ByteString>(((builder).to_string()));
}
VERIFY_NOT_REACHED();
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

ByteString Jakt::repl::REPL::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("REPL("sv);{
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
ErrorOr<Jakt::repl::REPL> Jakt::repl::REPL::create(Jakt::jakt__path::Path const std_include_path,Jakt::jakt__path::Path const prelude_path,JaktInternal::Optional<ByteString> const target_triple,JaktInternal::Dictionary<ByteString,ByteString> const user_configuration) {
{
NonnullRefPtr<Jakt::compiler::Compiler> compiler = Jakt::compiler::Compiler::__jakt_create(DynamicArray<Jakt::jakt__path::Path>::create_with({}),Dictionary<ByteString, Jakt::utility::FileId>::create_with_entries({}),DynamicArray<Jakt::error::JaktError>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<u8>::create_with({}),false,false,false,false,std_include_path,prelude_path,DynamicArray<ByteString>::create_with({}),false,false,false,false,target_triple,user_configuration,Jakt::jakt__path::Path::from_string((ByteString::from_utf8_without_validation("build"sv))),Jakt::jakt__path::Path::from_string((ByteString::from_utf8_without_validation("build/exports"sv))),Jakt::jakt__path::Path::from_string((ByteString::from_utf8_without_validation("repl.jakt"sv))));
TRY((((compiler)->load_prelude())));
Jakt::utility::FileId const file_id = ((compiler)->get_file_id_or_register(Jakt::jakt__path::Path::from_string((ByteString::from_utf8_without_validation("<repl>"sv)))));
Jakt::ids::ModuleId const placeholder_module_id = Jakt::ids::ModuleId(static_cast<size_t>(0ULL));
ByteString const root_module_name = (ByteString::from_utf8_without_validation("repl"sv));
Jakt::typechecker::Typechecker typechecker = Jakt::typechecker::Typechecker(compiler,Jakt::types::CheckedProgram::__jakt_create(compiler,DynamicArray<NonnullRefPtr<Jakt::types::Module>>::create_with({}),Dictionary<ByteString, JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>>::create_with_entries({}),Dictionary<ByteString, Jakt::types::LoadedModule>::create_with_entries({})),placeholder_module_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::typechecker::BreakContinueLegalityTracker::None(),Jakt::typechecker::ReturnLegalityTracker::None(),false,((compiler)->dump_type_hints),((compiler)->dump_try_hints),static_cast<u64>(0ULL),Jakt::types::GenericInferences(Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({})),JaktInternal::OptionalNone(),root_module_name,false,false,Dictionary<ByteString, Jakt::ids::ScopeId>::create_with_entries({}),JaktInternal::OptionalNone(),static_cast<u64>(0ULL),Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({}),Jakt::ids::ScopeId(Jakt::ids::ModuleId(static_cast<size_t>(18446744073709551615ULL)),static_cast<size_t>(18446744073709551615ULL)),Jakt::types::BlockControlFlow::NeverReturns(),JaktInternal::OptionalNone(),false));
(((compiler)->current_file) = file_id);
TRY((((typechecker).include_prelude())));
Jakt::ids::ModuleId const root_module_id = ((typechecker).create_module(root_module_name,true,JaktInternal::OptionalNone()));
(((typechecker).current_module_id) = root_module_id);
((((typechecker).program))->set_loaded_module(root_module_name,Jakt::types::LoadedModule(root_module_id,file_id)));
Jakt::ids::ScopeId const PRELUDE_SCOPE_ID = ((typechecker).prelude_scope_id());
Jakt::ids::ScopeId const root_scope_id = ((typechecker).create_scope(PRELUDE_SCOPE_ID,true,(ByteString::from_utf8_without_validation("root"sv)),true));
TRY((((typechecker).typecheck_module_import(Jakt::parser::ParsedModuleImport(Jakt::parser::ImportName::Literal((ByteString::from_utf8_without_validation("jakt::prelude::prelude"sv)),Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL))),JaktInternal::OptionalNone(),Jakt::parser::ImportList::All(),false,static_cast<size_t>(0ULL)),root_scope_id))));
NonnullRefPtr<Jakt::interpreter::InterpreterScope> const root_interpreter_scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),JaktInternal::OptionalNone(),Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),compiler,root_scope_id);
return Jakt::repl::REPL(compiler,typechecker,root_scope_id,root_interpreter_scope,file_id);
}
}

ErrorOr<bool> Jakt::repl::REPL::handle_possible_error() {
{
TRY((((((*this).compiler))->print_errors())));
bool const has_error = [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((((((*this).compiler))->errors)).size()),static_cast<size_t>(0ULL));
JaktInternal::DynamicArray<Jakt::error::JaktError> const arr = DynamicArray<Jakt::error::JaktError>::create_with({});
(((((*this).compiler))->errors) = arr);
return has_error;
}
}

JaktInternal::DynamicArray<u8> Jakt::repl::REPL::line_to_bytes(ByteString const line) {
{
size_t pos = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<u8> bytes_ = DynamicArray<u8>::create_with({});
((bytes_).ensure_capacity(((line).length())));
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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

bool Jakt::repl::REPL::check_parens(JaktInternal::DynamicArray<Jakt::lexer::Token> const tokens) {
{
i64 unmatched_parens = static_cast<i64>(0LL);
i64 unmatched_brackets = static_cast<i64>(0LL);
i64 unmatched_curlies = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::lexer::Token> _magic = ((tokens).iterator());
for (;;){
JaktInternal::Optional<Jakt::lexer::Token> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::lexer::Token token = (_magic_value.value());
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

ErrorOr<void> Jakt::repl::REPL::run() {
{
Function<ErrorOr<void>(Jakt::repl_backend__default::Editor&)> const syntax_highlight_handler = [this](Jakt::repl_backend__default::Editor& editor) -> ErrorOr<void> {{
ByteString const line = TRY((((((editor))).get_active_buffer())));
size_t pos = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<u8> bytes_ = DynamicArray<u8>::create_with({});
((bytes_).ensure_capacity(((line).length())));
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
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
ScopeGuard __jakt_var_120([&] {
{
JaktInternal::DynamicArray<Jakt::error::JaktError> const arr = DynamicArray<Jakt::error::JaktError>::create_with({});
(((((*this).compiler))->errors) = arr);
}

});
{
JaktInternal::ArrayIterator<Jakt::lexer::Token> _magic = ((({ Optional<JaktInternal::DynamicArray<Jakt::lexer::Token>> __jakt_var_121;
auto __jakt_var_122 = [&]() -> ErrorOr<JaktInternal::DynamicArray<Jakt::lexer::Token>> { return Jakt::lexer::Lexer::lex(((*this).compiler)); }();
if (__jakt_var_122.is_error()) {{
return {};
}
} else {__jakt_var_121 = __jakt_var_122.release_value();
}
__jakt_var_121.release_value(); })).iterator());
for (;;){
JaktInternal::Optional<Jakt::lexer::Token> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::lexer::Token token = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = token;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* SingleQuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SingleQuotedString;Jakt::utility::Span const& span = __jakt_match_value.span;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Green()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;Jakt::utility::Span const& span = __jakt_match_value.span;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Green()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Number */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Number;Jakt::utility::Span const& span = __jakt_match_value.span;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Blue()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 59 /* And */: {
auto&& __jakt_match_value = __jakt_match_variant.as.And;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 60 /* Anon */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Anon;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 61 /* As */: {
auto&& __jakt_match_value = __jakt_match_variant.as.As;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 62 /* Boxed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boxed;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 63 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 64 /* Catch */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Catch;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 65 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 66 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 67 /* Cpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Cpp;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 68 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 69 /* Destructor */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Destructor;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 70 /* Else */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Else;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 71 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 72 /* Extern */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Extern;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 74 /* False */: {
auto&& __jakt_match_value = __jakt_match_variant.as.False;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 75 /* For */: {
auto&& __jakt_match_value = __jakt_match_variant.as.For;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 76 /* Fn */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fn;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 77 /* Comptime */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Comptime;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 78 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 79 /* Import */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Import;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 81 /* In */: {
auto&& __jakt_match_value = __jakt_match_variant.as.In;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 82 /* Is */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Is;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 83 /* Let */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Let;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 84 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 85 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 87 /* Mut */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Mut;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 88 /* Namespace */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Namespace;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 89 /* Not */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Not;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 90 /* Or */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Or;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 91 /* Override */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Override;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 92 /* Private */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Private;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 93 /* Public */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Public;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 94 /* Raw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Raw;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 95 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 96 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 97 /* Restricted */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Restricted;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 98 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 99 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 100 /* This */: {
auto&& __jakt_match_value = __jakt_match_variant.as.This;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 53 /* Dot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dot;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 101 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 102 /* Throws */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throws;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 103 /* True */: {
auto&& __jakt_match_value = __jakt_match_variant.as.True;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 104 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 105 /* Unsafe */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsafe;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 106 /* Virtual */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Virtual;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 107 /* Weak */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Weak;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 108 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 109 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 110 /* Guard */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Guard;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 111 /* Implements */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Implements;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 112 /* Requires */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Requires;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 113 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Yellow()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 54 /* DotDot */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DotDot;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::XTerm(Jakt::repl_backend__common::XTermColor::Cyan()),JaktInternal::OptionalNone())))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 55 /* Eol */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Eol;Jakt::utility::Span const& span = __jakt_match_value.span;
JaktInternal::Optional<ByteString> const& comment = __jakt_match_value.comment;
{
if (((comment).has_value())){
TRY((((((editor))).highlight(span,Jakt::repl_backend__common::Style(Jakt::repl_backend__common::Color::Components(static_cast<u8>(128),static_cast<u8>(128),static_cast<u8>(128)),JaktInternal::OptionalNone())))));
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
Jakt::repl_backend__default::Editor editor = TRY((Jakt::repl_backend__default::Editor::create((ByteString::from_utf8_without_validation("> "sv)),((syntax_highlight_handler)))));
ScopeGuard __jakt_var_123([&] {
((editor).destroy());
});
for (;;){
if ((!(((((((*this).compiler))->errors)).is_empty())))){
TRY((((((*this).compiler))->print_errors())));
JaktInternal::DynamicArray<Jakt::error::JaktError> const arr = DynamicArray<Jakt::error::JaktError>::create_with({});
(((((*this).compiler))->errors) = arr);
}
Jakt::repl_backend__common::LineResult const line_result = ({ Optional<Jakt::repl_backend__common::LineResult> __jakt_var_124;
auto __jakt_var_125 = [&]() -> ErrorOr<Jakt::repl_backend__common::LineResult> { return ((((editor).get_line(JaktInternal::OptionalNone())))); }();
if (__jakt_var_125.is_error()) {auto error = __jakt_var_125.release_error();
{
return {};
}
} else {__jakt_var_124 = __jakt_var_125.release_value();
}
__jakt_var_124.release_value(); });
Jakt::repl_backend__common::LineResult __jakt_tmp393 = line_result;
if (((__jakt_tmp393).__jakt_init_index() == 0 /* Line */)){
ByteString const line = (__jakt_tmp393).as.Line.value;
if (((line) == ((ByteString::from_utf8_without_validation("\n"sv))))){
continue;
}
if (((line) == ((ByteString::from_utf8_without_validation(".exit\n"sv))))){
break;
}
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = Jakt::repl::REPL::line_to_bytes(line));
JaktInternal::DynamicArray<Jakt::lexer::Token> tokens = ({ Optional<JaktInternal::DynamicArray<Jakt::lexer::Token>> __jakt_var_126;
auto __jakt_var_127 = [&]() -> ErrorOr<JaktInternal::DynamicArray<Jakt::lexer::Token>> { return Jakt::lexer::Lexer::lex(((*this).compiler)); }();
if (__jakt_var_127.is_error()) {{
continue;
}
} else {__jakt_var_126 = __jakt_var_127.release_value();
}
__jakt_var_126.release_value(); });
if (((tokens).is_empty())){
continue;
}
if ((!(Jakt::repl::REPL::check_parens(tokens)))){
ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append(line));
while ((!(Jakt::repl::REPL::check_parens(tokens)))){
Jakt::repl_backend__common::LineResult const line_result = ({ Optional<Jakt::repl_backend__common::LineResult> __jakt_var_128;
auto __jakt_var_129 = [&]() -> ErrorOr<Jakt::repl_backend__common::LineResult> { return ((((editor).get_line((ByteString::from_utf8_without_validation(".."sv)))))); }();
if (__jakt_var_129.is_error()) {auto error = __jakt_var_129.release_error();
{
return {};
}
} else {__jakt_var_128 = __jakt_var_129.release_value();
}
__jakt_var_128.release_value(); });
Jakt::repl_backend__common::LineResult __jakt_tmp394 = line_result;
if (((__jakt_tmp394).__jakt_init_index() == 0 /* Line */)){
ByteString const line = (__jakt_tmp394).as.Line.value;
((builder).append(line));
(((((*this).compiler))->current_file) = ((*this).file_id));
(((((*this).compiler))->current_file_contents) = Jakt::repl::REPL::line_to_bytes(((builder).to_string())));
(tokens = ({ Optional<JaktInternal::DynamicArray<Jakt::lexer::Token>> __jakt_var_130;
auto __jakt_var_131 = [&]() -> ErrorOr<JaktInternal::DynamicArray<Jakt::lexer::Token>> { return Jakt::lexer::Lexer::lex(((*this).compiler)); }();
if (__jakt_var_131.is_error()) {{
continue;
}
} else {__jakt_var_130 = __jakt_var_131.release_value();
}
__jakt_var_130.release_value(); }));
}
else {
return {};
}

}
}
Jakt::parser::Parser parser = Jakt::parser::Parser(static_cast<size_t>(0ULL),tokens,((*this).compiler),true,static_cast<size_t>(0ULL));
Jakt::lexer::Token const first_token = (((tokens).first()).value());
if (((((((((((first_token).__jakt_init_index() == 76 /* Fn */) || ((first_token).__jakt_init_index() == 77 /* Comptime */)) || ((first_token).__jakt_init_index() == 99 /* Struct */)) || ((first_token).__jakt_init_index() == 65 /* Class */)) || ((first_token).__jakt_init_index() == 71 /* Enum */)) || ((first_token).__jakt_init_index() == 62 /* Boxed */)) || ((first_token).__jakt_init_index() == 88 /* Namespace */)) || ((first_token).__jakt_init_index() == 79 /* Import */)) || ((first_token).__jakt_init_index() == 113 /* Trait */))){
Jakt::parser::ParsedNamespace const parsed_namespace = ({ Optional<Jakt::parser::ParsedNamespace> __jakt_var_132;
auto __jakt_var_133 = [&]() -> ErrorOr<Jakt::parser::ParsedNamespace> { return ((parser).parse_namespace(false)); }();
if (__jakt_var_133.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_132 = __jakt_var_133.release_value();
}
__jakt_var_132.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
auto __jakt_var_135 = [&]() -> ErrorOr<void> { return TRY((((((*this).typechecker)).typecheck_module(parsed_namespace,((*this).root_scope_id))))), ErrorOr<void>{}; }();
if (__jakt_var_135.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
}
;
TRY((((*this).handle_possible_error())));
continue;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> const parsed_statement = ({ Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> __jakt_var_136;
auto __jakt_var_137 = [&]() -> ErrorOr<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> { return ((parser).parse_statement(true)); }();
if (__jakt_var_137.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_136 = __jakt_var_137.release_value();
}
__jakt_var_136.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> const checked_statement = ({ Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> __jakt_var_138;
auto __jakt_var_139 = [&]() -> ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> { return ((((((*this).typechecker)).typecheck_statement(parsed_statement,((*this).root_scope_id),Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone())))); }();
if (__jakt_var_139.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_138 = __jakt_var_139.release_value();
}
__jakt_var_138.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter = ((((*this).typechecker)).interpreter());
Jakt::interpreter::StatementResult const result = ({ Optional<Jakt::interpreter::StatementResult> __jakt_var_140;
auto __jakt_var_141 = [&]() -> ErrorOr<Jakt::interpreter::StatementResult> { return ((((interpreter)->execute_statement(checked_statement,((*this).root_interpreter_scope),Jakt::utility::Span(((*this).file_id),static_cast<size_t>(0ULL),((line).length())))))); }();
if (__jakt_var_141.is_error()) {{
TRY((((*this).handle_possible_error())));
continue;
}
} else {__jakt_var_140 = __jakt_var_141.release_value();
}
__jakt_var_140.release_value(); });
if (TRY((((*this).handle_possible_error())))){
continue;
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
if (((((value).impl))->__jakt_init_index() == 0 /* Void */)){
return JaktInternal::LoopContinue{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
{
if (((((value).impl))->__jakt_init_index() == 0 /* Void */)){
return JaktInternal::LoopContinue{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
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
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::repl::serialize_ast_node(TRY((Jakt::interpreter::value_to_checked_expression(value,interpreter)))))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::repl::serialize_ast_node(TRY((Jakt::interpreter::value_to_checked_expression(value,interpreter)))))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("throw "sv))) + (TRY((Jakt::repl::serialize_ast_node(TRY((Jakt::interpreter::value_to_checked_expression(value,interpreter)))))))));
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

Jakt::repl::REPL::REPL(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, Jakt::typechecker::Typechecker a_typechecker, Jakt::ids::ScopeId a_root_scope_id, NonnullRefPtr<Jakt::interpreter::InterpreterScope> a_root_interpreter_scope, Jakt::utility::FileId a_file_id): compiler(move(a_compiler)), typechecker(move(a_typechecker)), root_scope_id(move(a_root_scope_id)), root_interpreter_scope(move(a_root_interpreter_scope)), file_id(move(a_file_id)){}

}
} // namespace Jakt
