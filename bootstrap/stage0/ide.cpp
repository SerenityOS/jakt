#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "ide.h"
#include "interpreter.h"
#include "lexer.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace ide {
ErrorOr<JaktInternal::DynamicArray<Jakt::ide::JaktSymbol>> find_symbols_in_namespace(Jakt::parser::ParsedNamespace const namespace_) {
{
JaktInternal::DynamicArray<Jakt::ide::JaktSymbol> symbols = DynamicArray<Jakt::ide::JaktSymbol>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedRecord> _magic = ((((namespace_).records)).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedRecord record = (_magic_value.value());
{
((symbols).push(Jakt::ide::record_to_symbol(record)));
}

}
}

{
JaktInternal::ArrayIterator<Jakt::parser::ParsedFunction> _magic = ((((namespace_).functions)).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedFunction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedFunction function = (_magic_value.value());
{
((symbols).push(Jakt::ide::function_to_symbol(function,(ByteString::from_utf8_without_validation("function"sv)))));
}

}
}

{
JaktInternal::ArrayIterator<Jakt::parser::ParsedNamespace> _magic = ((((namespace_).namespaces)).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedNamespace> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedNamespace sub_namespace = (_magic_value.value());
{
((symbols).push_values(((TRY((Jakt::ide::find_symbols_in_namespace(sub_namespace)))))));
}

}
}

if ((((((namespace_).name_span)).has_value()) && ((((namespace_).name)).has_value()))){
Jakt::utility::Span namespace_span = (((namespace_).name_span).value());
{
JaktInternal::ArrayIterator<Jakt::ide::JaktSymbol> _magic = ((symbols).iterator());
for (;;){
JaktInternal::Optional<Jakt::ide::JaktSymbol> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ide::JaktSymbol child = (_magic_value.value());
{
(namespace_span = Jakt::parser::merge_spans((((namespace_).name_span).value()),((child).range)));
}

}
}

return DynamicArray<Jakt::ide::JaktSymbol>::create_with({Jakt::ide::JaktSymbol((((namespace_).name).value()),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("namespace"sv)),namespace_span,(((namespace_).name_span).value()),symbols)});
}
else {
return symbols;
}

}
}

Jakt::ide::JaktSymbol record_to_symbol(Jakt::parser::ParsedRecord const record) {
{
JaktInternal::DynamicArray<Jakt::ide::JaktSymbol> children = DynamicArray<Jakt::ide::JaktSymbol>::create_with({});
Jakt::utility::Span record_span = ((record).name_span);
ByteString const record_kind = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, Jakt::ide::JaktSymbol>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::parser::ParsedField> const& fields = __jakt_match_value.fields;
{
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedField> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedField field = (_magic_value.value());
{
((children).push(Jakt::ide::JaktSymbol(((((field).var_decl)).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("field"sv)),((((field).var_decl)).span),((((field).var_decl)).span),DynamicArray<Jakt::ide::JaktSymbol>::create_with({}))));
}

}
}

return JaktInternal::ExplicitValue<ByteString>((ByteString::from_utf8_without_validation("struct"sv)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<Jakt::parser::ParsedField> const& fields = __jakt_match_value.fields;
{
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedField> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedField field = (_magic_value.value());
{
((children).push(Jakt::ide::JaktSymbol(((((field).var_decl)).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("field"sv)),((((field).var_decl)).span),((((field).var_decl)).span),DynamicArray<Jakt::ide::JaktSymbol>::create_with({}))));
}

}
}

return JaktInternal::ExplicitValue<ByteString>((ByteString::from_utf8_without_validation("class"sv)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* ValueEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ValueEnum;JaktInternal::DynamicArray<Jakt::parser::ValueEnumVariant> const& variants = __jakt_match_value.variants;
{
{
JaktInternal::ArrayIterator<Jakt::parser::ValueEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ValueEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ValueEnumVariant variant = (_magic_value.value());
{
((children).push(Jakt::ide::JaktSymbol(((variant).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("enum-member"sv)),((variant).span),((variant).span),DynamicArray<Jakt::ide::JaktSymbol>::create_with({}))));
}

}
}

return JaktInternal::ExplicitValue<ByteString>((ByteString::from_utf8_without_validation("enum"sv)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* SumEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SumEnum;JaktInternal::DynamicArray<Jakt::parser::SumEnumVariant> const& variants = __jakt_match_value.variants;
{
{
JaktInternal::ArrayIterator<Jakt::parser::SumEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::SumEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::SumEnumVariant variant = (_magic_value.value());
{
JaktInternal::DynamicArray<Jakt::ide::JaktSymbol> variant_children = DynamicArray<Jakt::ide::JaktSymbol>::create_with({});
if (((((variant).params)).has_value())){
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedVarDecl> _magic = (((((variant).params).value())).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedVarDecl> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedVarDecl param = (_magic_value.value());
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((param).name),(ByteString::from_utf8_without_validation(""sv)))){
((variant_children).push(Jakt::ide::JaktSymbol(((param).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("field"sv)),((param).span),((param).span),DynamicArray<Jakt::ide::JaktSymbol>::create_with({}))));
}
}

}
}

}
((children).push(Jakt::ide::JaktSymbol(((variant).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("enum-member"sv)),((variant).span),((variant).span),variant_children)));
}

}
}

return JaktInternal::ExplicitValue<ByteString>((ByteString::from_utf8_without_validation("enum"sv)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* Garbage */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("garbage"sv)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
{
JaktInternal::ArrayIterator<Jakt::parser::ParsedMethod> _magic = ((((record).methods)).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::ParsedMethod method = (_magic_value.value());
{
Jakt::ide::JaktSymbol const function_symbol = Jakt::ide::function_to_symbol(((method).parsed_function),(ByteString::from_utf8_without_validation("method"sv)));
((children).push(function_symbol));
(record_span = Jakt::parser::merge_spans(record_span,((function_symbol).range)));
}

}
}

return Jakt::ide::JaktSymbol(((record).name),JaktInternal::OptionalNone(),record_kind,record_span,((record).name_span),children);
}
}

Jakt::ide::JaktSymbol function_to_symbol(Jakt::parser::ParsedFunction const function,ByteString const kind) {
{
Jakt::utility::Span function_span = ((function).name_span);
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> _magic = ((((((function).block)).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::parser::ParsedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::parser::ParsedStatement> stmt = (_magic_value.value());
{
(function_span = Jakt::parser::merge_spans(function_span,((stmt)->span())));
}

}
}

return Jakt::ide::JaktSymbol(((function).name),JaktInternal::OptionalNone(),kind,function_span,((function).name_span),DynamicArray<Jakt::ide::JaktSymbol>::create_with({}));
}
}

ErrorOr<Jakt::utility::Span> find_definition_in_program(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::ide::Usage> const result = TRY((Jakt::ide::find_span_in_program(program,span)));
if (((result).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::utility::Span, ErrorOr<Jakt::utility::Span>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Variable;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::ids::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_function(function_id)))->name_span));
};/*case end*/
case 2 /* Typename */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typename;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 3 /* NameSet */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;Jakt::utility::Span const& span = __jakt_match_value.span;
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
else {
return span;
}

}
}

ErrorOr<Jakt::utility::Span> find_type_definition_for_type_id(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::ids::TypeId const type_id,Jakt::utility::Span const span) {
{
Jakt::ids::StructId const array_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
Jakt::ids::StructId const dictionary_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Dictionary"sv))))));
Jakt::ids::StructId const optional_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Optional"sv))))));
Jakt::ids::StructId const range_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Range"sv))))));
Jakt::ids::StructId const set_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Set"sv))))));
Jakt::ids::StructId const tuple_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Tuple"sv))))));
Jakt::ids::StructId const weak_ptr_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("WeakPtr"sv))))));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::utility::Span, ErrorOr<Jakt::utility::Span>>{
auto&& __jakt_match_variant = *((program)->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Never */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 0 /* Void */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29 /* Function */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_trait(id)))->name_span));
};/*case end*/
case 30 /* Self */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19 /* Dependent */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 31 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((value).span));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::utility::Span output = span;
if ((((((((struct_id).equals(array_struct_id)) || ((struct_id).equals(optional_struct_id))) || ((struct_id).equals(range_struct_id))) || ((struct_id).equals(set_struct_id))) || ((struct_id).equals(tuple_struct_id))) || ((struct_id).equals(weak_ptr_struct_id)))){
(output = TRY((Jakt::ide::find_type_definition_for_type_id(program,((args)[static_cast<i64>(0LL)]),span))));
}
else if (((struct_id).equals(dictionary_struct_id))){
(output = TRY((Jakt::ide::find_type_definition_for_type_id(program,((args)[static_cast<i64>(1LL)]),span))));
}
else {
(output = ((((program)->get_struct(struct_id))).name_span));
}

return JaktInternal::ExplicitValue<Jakt::utility::Span>(output);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_struct(struct_id))).name_span));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_enum(id))).name_span));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_trait(id)))->name_span));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_enum(id))).name_span));
};/*case end*/
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_type_definition_for_type_id(program,type_id,span))));
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

ErrorOr<Jakt::utility::Span> find_type_definition_in_program(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::ide::Usage> const result = TRY((Jakt::ide::find_span_in_program(program,span)));
if (((result).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::utility::Span, ErrorOr<Jakt::utility::Span>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Variable;Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
return JaktInternal::ExplicitValue<Jakt::utility::Span>(TRY((Jakt::ide::find_type_definition_for_type_id(program,type_id,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::ids::FunctionId const& function_id = __jakt_match_value.value;
{
return JaktInternal::ExplicitValue<Jakt::utility::Span>(((((program)->get_function(function_id)))->name_span));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* Typename */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typename;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
return JaktInternal::ExplicitValue<Jakt::utility::Span>(TRY((Jakt::ide::find_type_definition_for_type_id(program,type_id,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* NameSet */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;Jakt::utility::Span const& span = __jakt_match_value.span;
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
else {
return span;
}

}
}

ErrorOr<JaktInternal::Optional<ByteString>> find_typename_in_program(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::ide::Usage> const result = TRY((Jakt::ide::find_span_in_program(program,span)));
if (((result).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>, ErrorOr<JaktInternal::Optional<ByteString>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Variable;ByteString const& name = __jakt_match_value.name;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::ide::Mutability const& mutability = __jakt_match_value.mutability;
Jakt::ide::VarType const& var_type = __jakt_match_value.var_type;
Jakt::ide::VarVisibility const& visibility = __jakt_match_value.visibility;
JaktInternal::Optional<Jakt::ids::TypeId> const& struct_type_id = __jakt_match_value.struct_type_id;
{
ByteString const result = TRY((Jakt::ide::get_var_signature(program,name,type_id,mutability,var_type,visibility,struct_type_id)));
return JaktInternal::ExplicitValue<JaktInternal::Optional<ByteString>>(static_cast<JaktInternal::Optional<ByteString>>(result));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::ids::FunctionId const& function_id = __jakt_match_value.value;
{
ByteString const result = TRY((Jakt::ide::get_function_signature(program,function_id)));
return JaktInternal::ExplicitValue<JaktInternal::Optional<ByteString>>(static_cast<JaktInternal::Optional<ByteString>>(result));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* Typename */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typename;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
ByteString const result = TRY((Jakt::ide::get_type_signature(program,type_id)));
return JaktInternal::ExplicitValue<JaktInternal::Optional<ByteString>>(static_cast<JaktInternal::Optional<ByteString>>(result));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* NameSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NameSet;JaktInternal::DynamicArray<ByteString> const& names = __jakt_match_value.value;
{
ByteString output = (ByteString::from_utf8_without_validation(""sv));
bool first = true;
{
JaktInternal::ArrayIterator<ByteString> _magic = ((names).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString name = (_magic_value.value());
{
if ((!(first))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(" | "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,name);
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<ByteString>>(static_cast<JaktInternal::Optional<ByteString>>(output));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const& variants = __jakt_match_value.variants;
JaktInternal::Optional<Jakt::types::NumberConstant> const& number_constant = __jakt_match_value.number_constant;
{
ByteString const result = TRY((Jakt::ide::get_enum_variant_signature(program,name,type_id,variants,number_constant)));
return JaktInternal::ExplicitValue<JaktInternal::Optional<ByteString>>(static_cast<JaktInternal::Optional<ByteString>>(result));
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
else {
return JaktInternal::OptionalNone();
}

}
}

ErrorOr<JaktInternal::DynamicArray<ByteString>> completions_for_type_id(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::ids::TypeId const type_id) {
{
JaktInternal::Set<ByteString> output = Set<ByteString>::create_with_values({});
NonnullRefPtr<typename Jakt::types::Type> const ty = ((program)->get_type(type_id));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::DynamicArray<ByteString>>>{
auto&& __jakt_match_variant = *ty;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
NonnullRefPtr<Jakt::types::Scope> const scope = ((program)->get_scope(((enum_).scope_id)));
{
JaktInternal::ArrayIterator<ByteString> _magic = ((TRY((Jakt::ide::find_function_completions_in_scope(scope,program)))).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString entry = (_magic_value.value());
{
((output).add(entry));
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
JaktInternal::DynamicArray<Jakt::types::CheckedStruct> structs = DynamicArray<Jakt::types::CheckedStruct>::create_with({((program)->get_struct(struct_id))});
for (;;){
JaktInternal::Optional<Jakt::ids::StructId> __jakt_tmp389 = (((((structs).last()).value())).super_struct_id);
if (((__jakt_tmp389).has_value())){
Jakt::ids::StructId const x = (__jakt_tmp389.value());
((structs).push(((program)->get_struct(x))));
}
else {
break;
}

}
{
JaktInternal::ArrayIterator<Jakt::types::CheckedStruct> _magic = ((structs).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedStruct> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedStruct structure = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((program)->get_scope(((structure).scope_id)));
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const field_var = ((program)->get_variable(((field)->variable_id)));
((output).add(((field_var)->name)));
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = ((TRY((Jakt::ide::find_function_completions_in_scope(scope,program)))).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString entry = (_magic_value.value());
{
((output).add(entry));
}

}
}

}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
JaktInternal::DynamicArray<Jakt::types::CheckedStruct> structs = DynamicArray<Jakt::types::CheckedStruct>::create_with({((program)->get_struct(struct_id))});
for (;;){
JaktInternal::Optional<Jakt::ids::StructId> __jakt_tmp390 = (((((structs).last()).value())).super_struct_id);
if (((__jakt_tmp390).has_value())){
Jakt::ids::StructId const x = (__jakt_tmp390.value());
((structs).push(((program)->get_struct(x))));
}
else {
break;
}

}
{
JaktInternal::ArrayIterator<Jakt::types::CheckedStruct> _magic = ((structs).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedStruct> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedStruct structure = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((program)->get_scope(((structure).scope_id)));
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const field_var = ((program)->get_variable(((field)->variable_id)));
((output).add(((field_var)->name)));
}

}
}

{
JaktInternal::ArrayIterator<ByteString> _magic = ((TRY((Jakt::ide::find_function_completions_in_scope(scope,program)))).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString entry = (_magic_value.value());
{
((output).add(entry));
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
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<ByteString> result = DynamicArray<ByteString>::create_with({});
{
JaktInternal::SetIterator<ByteString> _magic = ((output).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString entry = (_magic_value.value());
{
((result).push(entry));
}

}
}

return result;
}
}

ErrorOr<JaktInternal::DynamicArray<ByteString>> find_function_completions_in_scope(NonnullRefPtr<Jakt::types::Scope> const scope,NonnullRefPtr<Jakt::types::CheckedProgram> const program) {
{
JaktInternal::DynamicArray<ByteString> output = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = ((((((scope)->functions)).keys())).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString function_name = (_magic_value.value());
{
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set = (((((scope)->functions)).get(function_name)).value());
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
if (((((((checked_function)->params)).first())).has_value())){
Jakt::types::CheckedParameter const param = (((((checked_function)->params)).first()).value());
if (((((((param).variable))->name)) == ((ByteString::from_utf8_without_validation("this"sv))))){
ByteString full_call = ((checked_function)->name);
bool first = true;
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(full_call,(ByteString::from_utf8_without_validation("("sv)));
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> iter = ((((checked_function)->params)).iterator());
JaktInternal::Optional<Jakt::types::CheckedParameter> const dummy = ((iter).next());
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = iter;
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(full_call,(ByteString::from_utf8_without_validation(", "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(full_call,((((param).variable))->name));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(full_call,(ByteString::from_utf8_without_validation(")"sv)));
((output).push(full_call));
}
}
else {
((output).push(__jakt_format((StringView::from_string_literal("{}()"sv)),((checked_function)->name))));
}

}

}
}

}

}
}

return output;
}
}

ErrorOr<JaktInternal::DynamicArray<ByteString>> find_dot_completions(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::ide::Usage> const result = TRY((Jakt::ide::find_span_in_program(program,span)));
if (((result).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ByteString>, ErrorOr<JaktInternal::DynamicArray<ByteString>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Variable;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<ByteString>>(TRY((Jakt::ide::completions_for_type_id(program,type_id))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::ids::FunctionId const& function_id = __jakt_match_value.value;
{
Jakt::ids::TypeId const result_type_id = ((((program)->get_function(function_id)))->return_type_id);
return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<ByteString>>(TRY((Jakt::ide::completions_for_type_id(program,result_type_id))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<ByteString>::create_with({}));
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
return DynamicArray<ByteString>::create_with({});
}

}
}

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_program(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::utility::Span const span) {
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::Module>> iterator = ((((program)->modules)).iterator());
JaktInternal::Optional<NonnullRefPtr<Jakt::types::Module>> const dummy = ((iterator).next());
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::Module>> _magic = iterator;
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::Module>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::Module> module = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((program)->get_scope(Jakt::ids::ScopeId(((module)->id),static_cast<size_t>(0ULL))));
return ((Jakt::ide::find_span_in_scope(program,scope,span)));
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_scope(NonnullRefPtr<Jakt::types::CheckedProgram> const program,NonnullRefPtr<Jakt::types::Scope> const scope,Jakt::utility::Span const span) {
{
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::VarId> _magic = ((((scope)->vars)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::VarId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::VarId> scope_var = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const var = ((program)->get_variable(((scope_var).template get<1>())));
if (((((var)->definition_span)).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Typename(((var)->type_id)));
}
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> ___overload_set__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const jakt_____overload_set__ = ___overload_set__;
ByteString const _ = ((jakt_____overload_set__).template get<0>());
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set = ((jakt_____overload_set__).template get<1>());

{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
JaktInternal::Optional<Jakt::ide::Usage> const usage = TRY((Jakt::ide::find_span_in_function(program,checked_function,span)));
if (((usage).has_value())){
return (usage.value());
}
}

}
}

}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::StructId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::StructId> struct_id = (_magic_value.value());
{
Jakt::types::CheckedStruct const checked_struct = ((program)->get_struct(((struct_id).template get<1>())));
JaktInternal::Optional<Jakt::ide::Usage> const usage = TRY((Jakt::ide::find_span_in_struct(program,checked_struct,span)));
if (((usage).has_value())){
return (usage.value());
}
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::EnumId> _magic = ((((scope)->enums)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::EnumId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::EnumId> enum_id = (_magic_value.value());
{
Jakt::types::CheckedEnum const checked_enum = ((program)->get_enum(((enum_id).template get<1>())));
JaktInternal::Optional<Jakt::ide::Usage> const usage = TRY((Jakt::ide::find_span_in_enum(program,checked_enum,span)));
if (((usage).has_value())){
return (usage.value());
}
}

}
}

{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::ScopeId child = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((program)->get_scope(child));
JaktInternal::Optional<Jakt::ide::Usage> const usage = TRY((Jakt::ide::find_span_in_scope(program,scope,span)));
if (((usage).has_value())){
return (usage.value());
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_enum(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::types::CheckedEnum const checked_enum,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((program)->get_scope(((checked_enum).scope_id)));
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((checked_enum).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
Jakt::utility::Span const& variant_span = __jakt_match_value.span;
{
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId field = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const var = ((program)->get_variable(field));
if (((((var)->definition_span)).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Typename(((var)->type_id)));
}
}

}
}

if (((variant_span).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::EnumVariant(span,name,((checked_enum).type_id),DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>::create_with({}),JaktInternal::OptionalNone()));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
Jakt::utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),Jakt::ide::enum_variant_fields(program,variant),JaktInternal::OptionalNone()));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
Jakt::utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>::create_with({}),JaktInternal::OptionalNone()));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& name = __jakt_match_value.name;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),Jakt::ide::enum_variant_fields(program,variant),((expr)->to_number_constant(program))));
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

JaktInternal::Optional<Jakt::ide::Usage> const usage = TRY((Jakt::ide::find_span_in_scope(program,scope,span)));
return usage;
}
}

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_struct(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::types::CheckedStruct const checked_struct,Jakt::utility::Span const span) {
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((program)->get_scope(((checked_struct).scope_id)));
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((checked_struct).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = ((program)->get_variable(((field)->variable_id)));
if (((((variable)->definition_span)).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Typename(((variable)->type_id)));
}
}

}
}

JaktInternal::Optional<Jakt::ide::Usage> const usage = TRY((Jakt::ide::find_span_in_scope(program,scope,span)));
return usage;
}
}

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_function(NonnullRefPtr<Jakt::types::CheckedProgram> const program,NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function,Jakt::utility::Span const span) {
{
if (((((checked_function)->return_type_span)).has_value())){
if ((((((checked_function)->return_type_span).value())).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Typename(((checked_function)->return_type_id)));
}
}
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedParameter param = (_magic_value.value());
{
if (((((((param).variable))->definition_span)).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Typename(((((param).variable))->type_id)));
}
}

}
}

return ((Jakt::ide::find_span_in_block(program,((checked_function)->block),span)));
}
}

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_block(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::types::CheckedBlock const block,Jakt::utility::Span const span) {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> statement = (_magic_value.value());
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_statement(program,statement,span)));
if (((found).has_value())){
return found;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_statement(NonnullRefPtr<Jakt::types::CheckedProgram> const program,NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::ide::Usage> const none = JaktInternal::OptionalNone();
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_block(program,block,span))));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& statement = __jakt_match_value.statement;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_statement(program,statement,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
{
JaktInternal::Optional<Jakt::ide::Usage> found = TRY((Jakt::ide::find_span_in_expression(program,condition,span)));
if (((found).has_value())){
return found;
}
(found = TRY((Jakt::ide::find_span_in_block(program,then_block,span))));
if (((found).has_value())){
return found;
}
if (((else_statement).has_value())){
return ((Jakt::ide::find_span_in_statement(program,(else_statement.value()),span)));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 13 /* InlineCpp */: {
{
JaktInternal::Optional<Jakt::ide::Usage> const output = JaktInternal::OptionalNone();
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(output);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_block(program,block,span))));
};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>,ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>> {
auto __jakt_enum_value = (((val).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,(val.value()),span))));
}
else {
return JaktInternal::ExplicitValue(none);
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 11 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;Jakt::ids::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& init = __jakt_match_value.init;
{
NonnullRefPtr<Jakt::types::CheckedVariable> const checked_var = ((program)->get_variable(var_id));
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,init,span)));
if (((found).has_value())){
return found;
}
if (((((checked_var)->type_span)).has_value())){
Jakt::utility::Span const type_span = (((checked_var)->type_span).value());
if (((type_span).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Typename(((checked_var)->type_id)));
}
}
if (((((checked_var)->definition_span)).contains(span))){
Jakt::ide::Mutability const mutability = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ide::Mutability,ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>> {
auto __jakt_enum_value = (((checked_var)->is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::ide::Mutability::Mutable());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::ide::Mutability::Immutable());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Variable(((checked_var)->definition_span),((checked_var)->name),((checked_var)->type_id),mutability,Jakt::ide::VarType::Variable(),Jakt::ide::VarVisibility::DoesNotApply(),JaktInternal::OptionalNone()));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,condition,span)));
if (((found).has_value())){
return found;
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(TRY((Jakt::ide::find_span_in_block(program,block,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename Jakt::types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> var = (_magic_value.value());
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_statement(program,var,span)));
if (((found).has_value())){
return found;
}
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(TRY((Jakt::ide::find_span_in_statement(program,var_decl,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>,ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>> {
auto __jakt_enum_value = (((expr).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,(expr.value()),span))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(none);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 9 /* Break */: {
return JaktInternal::ExplicitValue(none);
};/*case end*/
case 10 /* Continue */: {
return JaktInternal::ExplicitValue(none);
};/*case end*/
case 14 /* Garbage */: {
return JaktInternal::ExplicitValue(none);
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

ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>> find_span_in_expression(NonnullRefPtr<Jakt::types::CheckedProgram> const program,NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,Jakt::utility::Span const span) {
{
JaktInternal::Optional<Jakt::ide::Usage> const none = JaktInternal::OptionalNone();
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
Jakt::types::CheckedBinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,lhs,span)));
if (((found).has_value())){
return found;
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(TRY((Jakt::ide::find_span_in_expression(program,rhs,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = (_magic_value.value());
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,val,span)));
if (((found).has_value())){
return found;
}
}

}
}

if (((repeat).has_value())){
return ((Jakt::ide::find_span_in_expression(program,(repeat.value()),span)));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_block(program,block,span))));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
Jakt::utility::Span const& call_span = __jakt_match_value.span;
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> ___expr__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt_____expr__ = ___expr__;
ByteString const _ = ((jakt_____expr__).template get<0>());
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = ((jakt_____expr__).template get<1>());

JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
}

}
}

if ((((((call).function_id)).has_value()) && ((call_span).contains(span)))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Call((((call).function_id).value())));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
{
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> key__value__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt__key__value__ = key__value__;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const key = ((jakt__key__value__).template get<0>());
NonnullRefPtr<typename Jakt::types::CheckedExpression> const value = ((jakt__key__value__).template get<1>());

JaktInternal::Optional<Jakt::ide::Usage> found = TRY((Jakt::ide::find_span_in_expression(program,key,span)));
if (((found).has_value())){
return found;
}
(found = TRY((Jakt::ide::find_span_in_expression(program,value,span))));
if (((found).has_value())){
return found;
}
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& index = __jakt_match_value.index;
{
JaktInternal::Optional<Jakt::ide::Usage> found = TRY((Jakt::ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
(found = TRY((Jakt::ide::find_span_in_expression(program,index,span))));
if (((found).has_value())){
return found;
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& name = __jakt_match_value.name;
Jakt::utility::Span const& index_span = __jakt_match_value.span;
Jakt::ids::TypeId const& known_type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
if (((index_span).contains(span))){
Jakt::ids::TypeId const type_id = ((expr)->type());
JaktInternal::Optional<Jakt::ids::TypeId> result_type = JaktInternal::OptionalNone();
if ((!(((known_type_id).equals(Jakt::types::unknown_type_id()))))){
(result_type = static_cast<JaktInternal::Optional<Jakt::ids::TypeId>>(known_type_id));
}
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp391 = ((program)->get_type(type_id));
if (((__jakt_tmp391)->__jakt_init_index() == 23 /* Struct */)){
Jakt::ids::StructId const struct_id = (__jakt_tmp391)->as.Struct.value;
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((((program)->get_struct(struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const var = ((program)->get_variable(((field)->variable_id)));
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(name,((var)->name))){
continue;
}
return Jakt::ide::Usage::Variable(((var)->definition_span),name,result_type.value_or_lazy_evaluated([&] { return ((var)->type_id); }),Jakt::ide::Mutability::DoesNotApply(),Jakt::ide::VarType::Field(),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ide::VarVisibility, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = ((var)->visibility);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Public */: {
return JaktInternal::ExplicitValue(Jakt::ide::VarVisibility::Public());
};/*case end*/
case 1 /* Private */: {
return JaktInternal::ExplicitValue(Jakt::ide::VarVisibility::Private());
};/*case end*/
case 2 /* Restricted */: {
return JaktInternal::ExplicitValue(Jakt::ide::VarVisibility::Restricted());
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
}),type_id);
}

}
}

}
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& index = __jakt_match_value.index;
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(TRY((Jakt::ide::find_span_in_expression(program,index,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
Jakt::utility::Span const& match_span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedMatchCase match_case = (_magic_value.value());
{
JaktInternal::Optional<Jakt::ide::Usage> const found = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
Jakt::ids::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
size_t const& index = __jakt_match_value.index;
Jakt::ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
Jakt::types::CheckedMatchBody const& body = __jakt_match_value.body;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
if (((marker_span).contains(span))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::get_enum_variant_usage_from_type_id_and_name(program,subject_type_id,name));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
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
};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expression;
Jakt::types::CheckedMatchBody const& body = __jakt_match_value.body;
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
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
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;Jakt::types::CheckedMatchBody const& body = __jakt_match_value.body;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>,ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>> {
auto __jakt_enum_value = (((marker_span).contains(span)));
if (__jakt_enum_value == true) {
{
JaktInternal::Set<ByteString> const all_cases = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Set<ByteString>, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = *((program)->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
JaktInternal::Set<ByteString> names = Set<ByteString>::create_with_values({});
Jakt::types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
((names).add(((variant).name())));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Set<ByteString>>(names);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
JaktInternal::Set<ByteString> names = Set<ByteString>::create_with_values({});
Jakt::types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
((names).add(((variant).name())));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Set<ByteString>>(names);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
return JaktInternal::ExplicitValue<JaktInternal::Set<ByteString>>(Set<ByteString>::create_with_values({__jakt_format((StringView::from_string_literal("else ({})"sv)),TRY((((program)->type_name(type_id,false)))))}));
}
VERIFY_NOT_REACHED();
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
JaktInternal::Set<ByteString> remaining_cases = all_cases;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedMatchCase other_case = (_magic_value.value());
{
Jakt::types::CheckedMatchCase __jakt_tmp392 = other_case;
if (((__jakt_tmp392).__jakt_init_index() == 0 /* EnumVariant */)){
ByteString const name = (__jakt_tmp392).as.EnumVariant.name;
((remaining_cases).remove(name));
}
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>,ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>> {
auto __jakt_enum_value = (((remaining_cases).is_empty()));
if (__jakt_enum_value == false) {
{
JaktInternal::DynamicArray<ByteString> cases_array = DynamicArray<ByteString>::create_with({});
((cases_array).ensure_capacity(((remaining_cases).size())));
{
JaktInternal::SetIterator<ByteString> _magic = ((remaining_cases).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString name = (_magic_value.value());
{
((cases_array).push(name));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::NameSet(cases_array)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
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
}
VERIFY_NOT_REACHED();
}
else {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
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
case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;Jakt::types::CheckedMatchBody const& body = __jakt_match_value.body;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>,ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>> {
auto __jakt_enum_value = (((marker_span).contains(span)));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
else {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>, ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
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
if (((found).has_value())){
return found;
}
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedCall const& call = __jakt_match_value.call;
Jakt::utility::Span const& method_span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<Jakt::ide::Usage> found = TRY((Jakt::ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> ___expr__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt_____expr__ = ___expr__;
ByteString const _ = ((jakt_____expr__).template get<0>());
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = ((jakt_____expr__).template get<1>());

(found = TRY((Jakt::ide::find_span_in_expression(program,expr,span))));
if (((found).has_value())){
return found;
}
}

}
}

if ((((((call).function_id)).has_value()) && ((method_span).contains(span)))){
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Call((((call).function_id).value())));
}
return none;
}
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
Jakt::utility::Span const& var_span = __jakt_match_value.span;
{
JaktInternal::Optional<Jakt::ids::TypeId> const none_type_id = JaktInternal::OptionalNone();
if (((var_span).contains(span))){
Jakt::ide::Mutability const mutability = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ide::Mutability,ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>> {
auto __jakt_enum_value = (((var)->is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::ide::Mutability::Mutable());
}
else {
return JaktInternal::ExplicitValue(Jakt::ide::Mutability::Immutable());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::Usage::Variable(((var)->definition_span),((var)->name),((var)->type_id),mutability,Jakt::ide::VarType::Variable(),Jakt::ide::VarVisibility::DoesNotApply(),none_type_id));
}
return none;
}
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;JaktInternal::DynamicArray<Jakt::types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
Jakt::utility::Span const& var_span = __jakt_match_value.span;
{
if ((((var_span).contains(span)) && (!(((namespaces).is_empty()))))){
Jakt::types::CheckedNamespace const last_ns = (((namespaces).last()).value());
if (((((((program)->get_scope(((last_ns).scope))))->namespace_name)).has_value())){
JaktInternal::Optional<Jakt::ids::EnumId> const enum_id = TRY((((program)->find_enum_in_scope(((last_ns).scope),((last_ns).name),false,JaktInternal::OptionalNone()))));
if (((enum_id).has_value())){
Jakt::types::CheckedEnum const enum_ = ((program)->get_enum((enum_id.value())));
return static_cast<JaktInternal::Optional<Jakt::ide::Usage>>(Jakt::ide::get_enum_variant_usage_from_type_id_and_name(program,((enum_).type_id),((var)->name)));
}
}
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
ByteString const& error_name = __jakt_match_value.error_name;
Jakt::types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_statement(program,stmt,span)));
if (((found).has_value())){
return found;
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(TRY((Jakt::ide::find_span_in_block(program,catch_block,span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 32 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<Jakt::types::CheckedBlock> const& catch_block = __jakt_match_value.catch_block;
{
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ide::Usage>,ErrorOr<JaktInternal::Optional<Jakt::ide::Usage>>> {
auto __jakt_enum_value = (((catch_block).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((Jakt::ide::find_span_in_block(program,(catch_block.value()),span))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(none);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& to = __jakt_match_value.to;
{
if (((from).has_value())){
JaktInternal::Optional<Jakt::ide::Usage> const found = TRY((Jakt::ide::find_span_in_expression(program,(from.value()),span)));
if (((found).has_value())){
return found;
}
}
if (((to).has_value())){
return ((Jakt::ide::find_span_in_expression(program,(to.value()),span)));
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::ide::Usage>>(none);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(none);
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

ErrorOr<ByteString> get_function_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::ids::FunctionId const function_id) {
{
NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((checked_function)->type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* ImplicitEnumConstructor */: {
{
Jakt::ids::TypeId const type_id = ((checked_function)->return_type_id);
ByteString const name = ((checked_function)->name);
return ((Jakt::ide::get_enum_variant_signature_from_type_id_and_name(program,type_id,name)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* ImplicitConstructor */: {
{
return ((Jakt::ide::get_constructor_signature(program,function_id)));
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
ByteString generic_parameters = (ByteString::from_utf8_without_validation(""sv));
bool is_first_param = true;
if ((!(((((((checked_function)->generics))->params)).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(generic_parameters,(ByteString::from_utf8_without_validation("<"sv)));
{
JaktInternal::ArrayIterator<Jakt::types::FunctionGenericParameter> _magic = ((((((checked_function)->generics))->params)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::FunctionGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::FunctionGenericParameter parameter = (_magic_value.value());
{
ByteString const generic_type = TRY((((program)->type_name(((parameter).type_id()),false))));
ByteString const separator = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (is_first_param);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(", "sv)));
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
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(generic_parameters,__jakt_format((StringView::from_string_literal("{}{}"sv)),separator,generic_type));
(is_first_param = false);
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(generic_parameters,(ByteString::from_utf8_without_validation(">"sv)));
}
ByteString parameters = (ByteString::from_utf8_without_validation(""sv));
(is_first_param = true);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedParameter param = (_magic_value.value());
{
ByteString const anon_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (((param).requires_label));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("anon "sv)));
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
ByteString const is_mutable = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (((((param).variable))->is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("mut "sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
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
ByteString variable_type = TRY((((program)->type_name(((((param).variable))->type_id),false))));
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(variable_type,(ByteString::from_utf8_without_validation("void"sv)))){
(variable_type = (((ByteString::from_utf8_without_validation(": "sv))) + (variable_type)));
}
else {
(variable_type = (ByteString::from_utf8_without_validation(""sv)));
}

ByteString const separator = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (is_first_param);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(", "sv)));
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
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(parameters,__jakt_format((StringView::from_string_literal("{}{}{}{}{}"sv)),separator,anon_value,is_mutable,((((param).variable))->name),variable_type));
(is_first_param = false);
}

}
}

if (((checked_function)->has_varargs)){
if (is_first_param){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(parameters,(ByteString::from_utf8_without_validation(".."sv)));
}
else {
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(parameters,(ByteString::from_utf8_without_validation(", .."sv)));
}

}
ByteString const throws_str = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (((checked_function)->can_throw));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(" throws"sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString returns = TRY((((program)->type_name(((checked_function)->return_type_id),false))));
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(returns,(ByteString::from_utf8_without_validation("void"sv)))){
(returns = (((ByteString::from_utf8_without_validation(" -> "sv))) + (returns)));
}
else {
(returns = (ByteString::from_utf8_without_validation(""sv)));
}

return __jakt_format((StringView::from_string_literal("fn {}{}({}){}{}"sv)),((checked_function)->name),generic_parameters,parameters,throws_str,returns);
}
}

ErrorOr<ByteString> get_var_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program,ByteString const name,Jakt::ids::TypeId const var_type_id,Jakt::ide::Mutability const mutability,Jakt::ide::VarType const var_type,Jakt::ide::VarVisibility const visibility,JaktInternal::Optional<Jakt::ids::TypeId> const struct_type_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = var_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
{
ByteString const mut_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = mutability;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Mutable */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("mut"sv)));
};/*case end*/
case 1 /* Immutable */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("let"sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const type_name = TRY((Jakt::ide::get_type_signature(program,var_type_id)));
return JaktInternal::ExplicitValue<ByteString>(__jakt_format((StringView::from_string_literal("{} {}: {}"sv)),mut_string,name,type_name));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Field */: {
{
ByteString record_string = (ByteString::from_utf8_without_validation(""sv));
if (((struct_type_id).has_value())){
(record_string = TRY((Jakt::ide::get_type_signature(program,(struct_type_id.value())))));
}
ByteString const visibility_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = visibility;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Public */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("public "sv)));
};/*case end*/
case 2 /* Private */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("private "sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const type_name = TRY((Jakt::ide::get_type_signature(program,var_type_id)));
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(record_string,(ByteString::from_utf8_without_validation(""sv)))){
return __jakt_format((StringView::from_string_literal("{}\\n\\t{}{}: {}"sv)),record_string,visibility_string,name,type_name);
}
else {
return __jakt_format((StringView::from_string_literal("{}{}: {}"sv)),visibility_string,name,type_name);
}

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

ErrorOr<ByteString> get_type_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::ids::TypeId const type_id) {
{
Jakt::ids::StructId const array_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
Jakt::ids::StructId const dictionary_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Dictionary"sv))))));
Jakt::ids::StructId const optional_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Optional"sv))))));
Jakt::ids::StructId const range_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Range"sv))))));
Jakt::ids::StructId const set_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Set"sv))))));
Jakt::ids::StructId const tuple_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Tuple"sv))))));
Jakt::ids::StructId const weak_ptr_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("WeakPtr"sv))))));
NonnullRefPtr<typename Jakt::types::Type> const type = ((program)->get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Never */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("never"sv)));
};/*case end*/
case 0 /* Void */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("void"sv)));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("bool"sv)));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("u8"sv)));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("u16"sv)));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("u32"sv)));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("u64"sv)));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("i8"sv)));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("i16"sv)));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("i32"sv)));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("i64"sv)));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("f32"sv)));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("f64"sv)));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("usize"sv)));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("String"sv)));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("c_int"sv)));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("c_char"sv)));
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
};/*case end*/
case 30 /* Self */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Self"sv)));
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_trait(trait_id)))->name));
};/*case end*/
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;Jakt::ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}::{}"sv)),TRY((((program)->type_name(namespace_type,false)))),name));
};/*case end*/
case 31 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::types::comptime_format_impl((ByteString::from_utf8_without_validation("const {}"sv)),((DynamicArray<Jakt::types::Value>::create_with({value}))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})]),((program))))));
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& params = __jakt_match_value.params;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
{
JaktInternal::DynamicArray<ByteString> param_names = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::TypeId x = (_magic_value.value());
{
((param_names).push(TRY((((program)->type_name(x,false))))));
}

}
}

ByteString const return_type = TRY((((program)->type_name(return_type_id,false))));
return JaktInternal::ExplicitValue<ByteString>(__jakt_format((StringView::from_string_literal("fn({}) -> {}"sv)),Jakt::utility::join(param_names,(ByteString::from_utf8_without_validation(", "sv))),return_type));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("raw "sv))) + (TRY((Jakt::ide::get_type_signature(program,type_id))))));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = ((program)->get_enum(id));
return JaktInternal::ExplicitValue<ByteString>(((((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (((enum_).is_boxed));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("boxed "sv)));
}
else {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})) + ((ByteString::from_utf8_without_validation("enum "sv))))) + (((enum_).name))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const struct_ = ((program)->get_struct(id));
return JaktInternal::ExplicitValue<ByteString>(((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("class "sv)));
};/*case end*/
case 0 /* Struct */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("struct "sv)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("unreachable: should've been struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})) + (((struct_).name))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedEnum const enum_ = ((program)->get_enum(id));
ByteString output = (ByteString::from_utf8_without_validation(""sv));
if (((enum_).is_boxed)){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("boxed "sv)));
}
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("enum "sv)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,((enum_).name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((Jakt::ide::get_type_signature(program,((args)[i])))));
}

}
}

}
return JaktInternal::ExplicitValue<ByteString>(((output) + ((ByteString::from_utf8_without_validation(">"sv)))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
NonnullRefPtr<Jakt::types::CheckedTrait> const trait_ = ((program)->get_trait(id));
ByteString output = (ByteString::from_utf8_without_validation(""sv));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("trait "sv)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,((trait_)->name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((Jakt::ide::get_type_signature(program,((args)[i])))));
}

}
}

}
return JaktInternal::ExplicitValue<ByteString>(((output) + ((ByteString::from_utf8_without_validation(">"sv)))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if (((id).equals(array_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation("[]"sv));
}
return __jakt_format((StringView::from_string_literal("[{}]"sv)),TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
}
if (((id).equals(dictionary_struct_id))){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((args).size()),static_cast<size_t>(2ULL))){
return (ByteString::from_utf8_without_validation("[:]"sv));
}
return __jakt_format((StringView::from_string_literal("[{}: {}]"sv)),TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))),TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(1LL)])))));
}
if (((id).equals(optional_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation(""sv));
}
return __jakt_format((StringView::from_string_literal("{}?"sv)),TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
}
if (((id).equals(range_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation(""sv));
}
return __jakt_format((StringView::from_string_literal("{}..{}"sv)),TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))),TRY((((program)->type_name(((args)[static_cast<i64>(0LL)]),false)))));
}
if (((id).equals(set_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation(""sv));
}
return __jakt_format((StringView::from_string_literal("{{{}}}"sv)),TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
}
if (((id).equals(tuple_struct_id))){
ByteString output = (ByteString::from_utf8_without_validation("("sv));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((Jakt::ide::get_type_signature(program,((args)[i])))));
}

}
}

}
return ((output) + ((ByteString::from_utf8_without_validation(")"sv))));
}
if (((id).equals(weak_ptr_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation(""sv));
}
return __jakt_format((StringView::from_string_literal("weak {}"sv)),TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
}
Jakt::types::CheckedStruct const record = ((program)->get_struct(id));
ByteString output = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Class */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("class "sv)));
};/*case end*/
case 0 /* Struct */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("struct "sv)));
};/*case end*/
case 2 /* ValueEnum */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("unreachable: can't be an enum"sv)));
}
};/*case end*/
case 3 /* SumEnum */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("unreachable: can't be an enum"sv)));
}
};/*case end*/
case 4 /* Garbage */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,((record).name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((Jakt::ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((Jakt::ide::get_type_signature(program,((args)[i])))));
}

}
}

}
return JaktInternal::ExplicitValue<ByteString>(((output) + ((ByteString::from_utf8_without_validation(">"sv)))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("&{}"sv)),TRY((((program)->type_name(type_id,false))))));
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("&mut {}"sv)),TRY((((program)->type_name(type_id,false))))));
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

ErrorOr<ByteString> get_enum_variant_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program,ByteString const name,Jakt::ids::TypeId const type_id,JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const variants,JaktInternal::Optional<Jakt::types::NumberConstant> const number_constant) {
{
ByteString output = TRY((Jakt::ide::get_type_signature(program,type_id)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("::"sv)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,name);
if ((!(((variants).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("("sv)));
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId> variant_name__variant_type_id__ = (_magic_value.value());
{
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId> const jakt__variant_name__variant_type_id__ = variant_name__variant_type_id__;
JaktInternal::Optional<ByteString> const variant_name = ((jakt__variant_name__variant_type_id__).template get<0>());
Jakt::ids::TypeId const variant_type_id = ((jakt__variant_name__variant_type_id__).template get<1>());

if (first){
(first = false);
}
else {
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}

if (((variant_name).has_value())){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(variant_name.value()));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(": "sv)));
}
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((((program)->type_name(variant_type_id,false)))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(")"sv)));
}
if (((number_constant).has_value())){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(" = "sv)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = (number_constant.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Signed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Signed;i64 const& value = __jakt_match_value.value;
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,__jakt_format((StringView::from_string_literal("{}"sv)),value));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Unsigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsigned;u64 const& value = __jakt_match_value.value;
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,__jakt_format((StringView::from_string_literal("{}"sv)),value));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Floating */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Floating;f64 const& value = __jakt_match_value.value;
{
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,__jakt_format((StringView::from_string_literal("{}"sv)),value));
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
return output;
}
}

ErrorOr<ByteString> get_enum_variant_signature_from_type_id_and_name(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::ids::TypeId const type_id,ByteString const name) {
{
NonnullRefPtr<Jakt::types::Module> const mod = ((((program)->modules))[((((type_id).module)).id)]);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnum> _magic = ((((mod)->enums)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnum> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnum enum_ = (_magic_value.value());
{
if (((((enum_).type_id)).equals(type_id))){
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& v_name = __jakt_match_value.name;
{
if (((v_name) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const params = Jakt::ide::enum_variant_fields(program,variant);
JaktInternal::Optional<Jakt::types::NumberConstant> const none = JaktInternal::OptionalNone();
return ((Jakt::ide::get_enum_variant_signature(program,name,type_id,params,none)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& v_name = __jakt_match_value.name;
{
if (((v_name) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const params = Jakt::ide::enum_variant_fields(program,variant);
JaktInternal::Optional<Jakt::types::NumberConstant> const none = JaktInternal::OptionalNone();
return ((Jakt::ide::get_enum_variant_signature(program,name,type_id,params,none)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& v_name = __jakt_match_value.name;
{
if (((v_name) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const params = Jakt::ide::enum_variant_fields(program,variant);
JaktInternal::Optional<Jakt::types::NumberConstant> const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::NumberConstant>, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
{
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::types::NumberConstant>>(((expr)->to_number_constant(program)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
JaktInternal::Optional<Jakt::types::NumberConstant> const none = JaktInternal::OptionalNone();
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::types::NumberConstant>>(none);
}
VERIFY_NOT_REACHED();
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
return ((Jakt::ide::get_enum_variant_signature(program,name,type_id,params,value)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& v_name = __jakt_match_value.name;
{
if (((v_name) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const params = Jakt::ide::enum_variant_fields(program,variant);
JaktInternal::Optional<Jakt::types::NumberConstant> const none = JaktInternal::OptionalNone();
return ((Jakt::ide::get_enum_variant_signature(program,name,type_id,params,none)));
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
}

}
}

return (ByteString::from_utf8_without_validation(""sv));
}
}

Jakt::ide::Usage get_enum_variant_usage_from_type_id_and_name(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::ids::TypeId const type_id,ByteString const name) {
{
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnum> _magic = ((((((program)->get_module(((type_id).module))))->enums)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnum> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnum enum_ = (_magic_value.value());
{
if ((!(((((enum_).type_id)).equals(type_id))))){
continue;
}
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
if (((((variant).name())) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> const variants = Jakt::ide::enum_variant_fields(program,variant);
JaktInternal::Optional<Jakt::types::NumberConstant> const number_constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::NumberConstant>, Jakt::ide::Usage>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& name = __jakt_match_value.name;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->to_number_constant(program)));
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
Jakt::utility::Span const span = ((variant).span());
return Jakt::ide::Usage::EnumVariant(span,name,type_id,variants,number_constant);
}
}

}
}

Jakt::utility::panic((ByteString::from_utf8_without_validation("unreachable: should have found variant"sv)));
}

}
}

Jakt::utility::panic((ByteString::from_utf8_without_validation("unreachable: should have found variant"sv)));
}
}

JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> enum_variant_fields(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::types::CheckedEnumVariant const checked_enum_variant) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>>{
auto&& __jakt_match_variant = checked_enum_variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> output = DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId field = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const variable = ((program)->get_variable(field));
JaktInternal::Optional<ByteString> const var_name = static_cast<JaktInternal::Optional<ByteString>>(((variable)->name));
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId> const o = (Tuple{var_name, ((variable)->type_id)});
((output).push(o));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>>(output);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<ByteString> const string_none = JaktInternal::OptionalNone();
return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>>(DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>::create_with({(Tuple{string_none, type_id})}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>>::create_with({}));
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

ErrorOr<ByteString> get_constructor_signature(NonnullRefPtr<Jakt::types::CheckedProgram> const program,Jakt::ids::FunctionId const function_id) {
{
NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
Jakt::ids::TypeId const type_id = ((checked_function)->return_type_id);
NonnullRefPtr<Jakt::types::Module> const mod = ((((program)->modules))[((((type_id).module)).id)]);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedStruct> _magic = ((((mod)->structures)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedStruct> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedStruct struct_ = (_magic_value.value());
{
if (((((struct_).type_id)).equals(type_id))){
ByteString output = TRY((Jakt::ide::get_type_signature(program,type_id)));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("("sv)));
bool first = true;
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
if (first){
(first = false);
}
else {
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}

NonnullRefPtr<Jakt::types::CheckedVariable> const variable = ((program)->get_variable(((field)->variable_id)));
if (((variable)->is_mutable)){
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("mut "sv)));
}
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,__jakt_format((StringView::from_string_literal("{}: {}"sv)),((variable)->name),TRY((((program)->type_name(((variable)->type_id),false))))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(")"sv)));
return output;
}
}

}
}

return (ByteString::from_utf8_without_validation(""sv));
}
}

ByteString Jakt::ide::JaktSymbol::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("JaktSymbol("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("detail: {}, ", detail);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("kind: \"{}\", ", kind);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("range: {}, ", range);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("selection_range: {}, ", selection_range);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("children: {}", children);
}
builder.append(")"sv);return builder.to_string(); }
ByteString Jakt::ide::JaktSymbol::to_json() const {
{
ByteStringBuilder json_builder = ByteStringBuilder::create();
((json_builder).append((StringView::from_string_literal("{"sv))));
((json_builder).appendff((ByteString::from_utf8_without_validation("\"name\": \"{}\","sv)),((*this).name)));
if (((((*this).detail)).has_value())){
((json_builder).appendff((ByteString::from_utf8_without_validation("\"detail\": \"{}\","sv)),((*this).detail)));
}
((json_builder).appendff((ByteString::from_utf8_without_validation("\"kind\": \"{}\","sv)),((*this).kind)));
((json_builder).appendff((ByteString::from_utf8_without_validation("\"range\": {{\"start\": {}, \"end\": {}}},"sv)),((((*this).range)).start),((((*this).range)).end)));
((json_builder).appendff((ByteString::from_utf8_without_validation("\"selection_range\": {{\"start\": {}, \"end\": {}}},"sv)),((((*this).selection_range)).start),((((*this).selection_range)).end)));
JaktInternal::DynamicArray<ByteString> child_symbols = DynamicArray<ByteString>::create_with({});
((child_symbols).ensure_capacity(((((*this).children)).size())));
{
JaktInternal::ArrayIterator<Jakt::ide::JaktSymbol> _magic = ((((*this).children)).iterator());
for (;;){
JaktInternal::Optional<Jakt::ide::JaktSymbol> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ide::JaktSymbol child = (_magic_value.value());
{
((child_symbols).push(((child).to_json())));
}

}
}

((json_builder).appendff((ByteString::from_utf8_without_validation("\"children\": [{}]"sv)),Jakt::utility::join(child_symbols,(ByteString::from_utf8_without_validation(","sv)))));
((json_builder).append((StringView::from_string_literal("}"sv))));
return ((json_builder).to_string());
}
}

Jakt::ide::JaktSymbol::JaktSymbol(ByteString a_name, JaktInternal::Optional<ByteString> a_detail, ByteString a_kind, Jakt::utility::Span a_range, Jakt::utility::Span a_selection_range, JaktInternal::DynamicArray<Jakt::ide::JaktSymbol> a_children): name(move(a_name)), detail(move(a_detail)), kind(move(a_kind)), range(move(a_range)), selection_range(move(a_selection_range)), children(move(a_children)){}

ByteString Jakt::ide::Mutability::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* DoesNotApply */: {
return ByteString("Mutability::DoesNotApply"sv);
break;}
case 1 /* Immutable */: {
return ByteString("Mutability::Immutable"sv);
break;}
case 2 /* Mutable */: {
return ByteString("Mutability::Mutable"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] Mutability Mutability::DoesNotApply(){
Mutability __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] Mutability Mutability::Immutable(){
Mutability __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] Mutability Mutability::Mutable(){
Mutability __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
Mutability& Mutability::operator=(Mutability const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Immutable */:
break;
case 2 /* Mutable */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Immutable */:
break;
case 2 /* Mutable */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Mutability::Mutability(Mutability const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Immutable */:
break;
case 2 /* Mutable */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Mutability& Mutability::operator=(Mutability &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Immutable */:
break;
case 2 /* Mutable */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Immutable */:
break;
case 2 /* Mutable */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Mutability::Mutability(Mutability &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Immutable */:
break;
case 2 /* Mutable */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Mutability::~Mutability(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void Mutability::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* DoesNotApply */:break;
case 1 /* Immutable */:break;
case 2 /* Mutable */:break;
}
}
ByteString Jakt::ide::VarType::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Variable */: {
return ByteString("VarType::Variable"sv);
break;}
case 1 /* Field */: {
return ByteString("VarType::Field"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] VarType VarType::Variable(){
VarType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] VarType VarType::Field(){
VarType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
VarType& VarType::operator=(VarType const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
break;
case 1 /* Field */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
break;
case 1 /* Field */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
VarType::VarType(VarType const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
break;
case 1 /* Field */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
VarType& VarType::operator=(VarType &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
break;
case 1 /* Field */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
break;
case 1 /* Field */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
VarType::VarType(VarType &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
break;
case 1 /* Field */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
VarType::~VarType(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void VarType::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Variable */:break;
case 1 /* Field */:break;
}
}
ByteString Jakt::ide::VarVisibility::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* DoesNotApply */: {
return ByteString("VarVisibility::DoesNotApply"sv);
break;}
case 1 /* Public */: {
return ByteString("VarVisibility::Public"sv);
break;}
case 2 /* Private */: {
return ByteString("VarVisibility::Private"sv);
break;}
case 3 /* Restricted */: {
return ByteString("VarVisibility::Restricted"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] VarVisibility VarVisibility::DoesNotApply(){
VarVisibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] VarVisibility VarVisibility::Public(){
VarVisibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] VarVisibility VarVisibility::Private(){
VarVisibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] VarVisibility VarVisibility::Restricted(){
VarVisibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
VarVisibility& VarVisibility::operator=(VarVisibility const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Public */:
break;
case 2 /* Private */:
break;
case 3 /* Restricted */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Public */:
break;
case 2 /* Private */:
break;
case 3 /* Restricted */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
VarVisibility::VarVisibility(VarVisibility const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Public */:
break;
case 2 /* Private */:
break;
case 3 /* Restricted */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
VarVisibility& VarVisibility::operator=(VarVisibility &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Public */:
break;
case 2 /* Private */:
break;
case 3 /* Restricted */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Public */:
break;
case 2 /* Private */:
break;
case 3 /* Restricted */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
VarVisibility::VarVisibility(VarVisibility &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* DoesNotApply */:
break;
case 1 /* Public */:
break;
case 2 /* Private */:
break;
case 3 /* Restricted */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
VarVisibility::~VarVisibility(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void VarVisibility::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* DoesNotApply */:break;
case 1 /* Public */:break;
case 2 /* Private */:break;
case 3 /* Restricted */:break;
}
}
ByteString Jakt::ide::Usage::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Variable */: {
builder.append("Usage::Variable"sv);
[[maybe_unused]] auto const& that = this->as.Variable;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mutability: {}, ", that.mutability);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var_type: {}, ", that.var_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("visibility: {}, ", that.visibility);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("struct_type_id: {}", that.struct_type_id);
}
builder.append(")"sv);
break;}
case 1 /* Call */: {
builder.append("Usage::Call"sv);
[[maybe_unused]] auto const& that = this->as.Call;
builder.appendff("({})", that.value);
break;}
case 2 /* Typename */: {
builder.append("Usage::Typename"sv);
[[maybe_unused]] auto const& that = this->as.Typename;
builder.appendff("({})", that.value);
break;}
case 3 /* NameSet */: {
builder.append("Usage::NameSet"sv);
[[maybe_unused]] auto const& that = this->as.NameSet;
builder.appendff("({})", that.value);
break;}
case 4 /* EnumVariant */: {
builder.append("Usage::EnumVariant"sv);
[[maybe_unused]] auto const& that = this->as.EnumVariant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variants: {}, ", that.variants);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("number_constant: {}", that.number_constant);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] Usage Usage::Variable(Jakt::utility::Span span, ByteString name, Jakt::ids::TypeId type_id, Jakt::ide::Mutability mutability, Jakt::ide::VarType var_type, Jakt::ide::VarVisibility visibility, JaktInternal::Optional<Jakt::ids::TypeId> struct_type_id){
Usage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Variable.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum.as.Variable.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Variable.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum.as.Variable.mutability) (decltype(mutability))(move(mutability));
new (&__jakt_uninit_enum.as.Variable.var_type) (decltype(var_type))(move(var_type));
new (&__jakt_uninit_enum.as.Variable.visibility) (decltype(visibility))(move(visibility));
new (&__jakt_uninit_enum.as.Variable.struct_type_id) (decltype(struct_type_id))(move(struct_type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] Usage Usage::Call(Jakt::ids::FunctionId value){
Usage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Call.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Usage Usage::Typename(Jakt::ids::TypeId value){
Usage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Typename.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Usage Usage::NameSet(JaktInternal::DynamicArray<ByteString> value){
Usage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.NameSet.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Usage Usage::EnumVariant(Jakt::utility::Span span, ByteString name, Jakt::ids::TypeId type_id, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,Jakt::ids::TypeId>> variants, JaktInternal::Optional<Jakt::types::NumberConstant> number_constant){
Usage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.as.EnumVariant.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum.as.EnumVariant.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.EnumVariant.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum.as.EnumVariant.variants) (decltype(variants))(move(variants));
new (&__jakt_uninit_enum.as.EnumVariant.number_constant) (decltype(number_constant))(move(number_constant));
return __jakt_uninit_enum;
}
Usage& Usage::operator=(Usage const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
new (&this->as.Variable.span) (decltype(this->as.Variable.span))(rhs.as.Variable.span);
new (&this->as.Variable.name) (decltype(this->as.Variable.name))(rhs.as.Variable.name);
new (&this->as.Variable.type_id) (decltype(this->as.Variable.type_id))(rhs.as.Variable.type_id);
new (&this->as.Variable.mutability) (decltype(this->as.Variable.mutability))(rhs.as.Variable.mutability);
new (&this->as.Variable.var_type) (decltype(this->as.Variable.var_type))(rhs.as.Variable.var_type);
new (&this->as.Variable.visibility) (decltype(this->as.Variable.visibility))(rhs.as.Variable.visibility);
new (&this->as.Variable.struct_type_id) (decltype(this->as.Variable.struct_type_id))(rhs.as.Variable.struct_type_id);
break;
case 1 /* Call */:
new (&this->as.Call.value) (decltype(this->as.Call.value))(rhs.as.Call.value);
break;
case 2 /* Typename */:
new (&this->as.Typename.value) (decltype(this->as.Typename.value))(rhs.as.Typename.value);
break;
case 3 /* NameSet */:
new (&this->as.NameSet.value) (decltype(this->as.NameSet.value))(rhs.as.NameSet.value);
break;
case 4 /* EnumVariant */:
new (&this->as.EnumVariant.span) (decltype(this->as.EnumVariant.span))(rhs.as.EnumVariant.span);
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(rhs.as.EnumVariant.name);
new (&this->as.EnumVariant.type_id) (decltype(this->as.EnumVariant.type_id))(rhs.as.EnumVariant.type_id);
new (&this->as.EnumVariant.variants) (decltype(this->as.EnumVariant.variants))(rhs.as.EnumVariant.variants);
new (&this->as.EnumVariant.number_constant) (decltype(this->as.EnumVariant.number_constant))(rhs.as.EnumVariant.number_constant);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
this->as.Variable.span = rhs.as.Variable.span;
this->as.Variable.name = rhs.as.Variable.name;
this->as.Variable.type_id = rhs.as.Variable.type_id;
this->as.Variable.mutability = rhs.as.Variable.mutability;
this->as.Variable.var_type = rhs.as.Variable.var_type;
this->as.Variable.visibility = rhs.as.Variable.visibility;
this->as.Variable.struct_type_id = rhs.as.Variable.struct_type_id;
break;
case 1 /* Call */:
this->as.Call.value = rhs.as.Call.value;
break;
case 2 /* Typename */:
this->as.Typename.value = rhs.as.Typename.value;
break;
case 3 /* NameSet */:
this->as.NameSet.value = rhs.as.NameSet.value;
break;
case 4 /* EnumVariant */:
this->as.EnumVariant.span = rhs.as.EnumVariant.span;
this->as.EnumVariant.name = rhs.as.EnumVariant.name;
this->as.EnumVariant.type_id = rhs.as.EnumVariant.type_id;
this->as.EnumVariant.variants = rhs.as.EnumVariant.variants;
this->as.EnumVariant.number_constant = rhs.as.EnumVariant.number_constant;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Usage::Usage(Usage const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
new (&this->as.Variable.span) (decltype(this->as.Variable.span))(rhs.as.Variable.span);
new (&this->as.Variable.name) (decltype(this->as.Variable.name))(rhs.as.Variable.name);
new (&this->as.Variable.type_id) (decltype(this->as.Variable.type_id))(rhs.as.Variable.type_id);
new (&this->as.Variable.mutability) (decltype(this->as.Variable.mutability))(rhs.as.Variable.mutability);
new (&this->as.Variable.var_type) (decltype(this->as.Variable.var_type))(rhs.as.Variable.var_type);
new (&this->as.Variable.visibility) (decltype(this->as.Variable.visibility))(rhs.as.Variable.visibility);
new (&this->as.Variable.struct_type_id) (decltype(this->as.Variable.struct_type_id))(rhs.as.Variable.struct_type_id);
break;
case 1 /* Call */:
new (&this->as.Call.value) (decltype(this->as.Call.value))(rhs.as.Call.value);
break;
case 2 /* Typename */:
new (&this->as.Typename.value) (decltype(this->as.Typename.value))(rhs.as.Typename.value);
break;
case 3 /* NameSet */:
new (&this->as.NameSet.value) (decltype(this->as.NameSet.value))(rhs.as.NameSet.value);
break;
case 4 /* EnumVariant */:
new (&this->as.EnumVariant.span) (decltype(this->as.EnumVariant.span))(rhs.as.EnumVariant.span);
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(rhs.as.EnumVariant.name);
new (&this->as.EnumVariant.type_id) (decltype(this->as.EnumVariant.type_id))(rhs.as.EnumVariant.type_id);
new (&this->as.EnumVariant.variants) (decltype(this->as.EnumVariant.variants))(rhs.as.EnumVariant.variants);
new (&this->as.EnumVariant.number_constant) (decltype(this->as.EnumVariant.number_constant))(rhs.as.EnumVariant.number_constant);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Usage& Usage::operator=(Usage &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
new (&this->as.Variable.span) (decltype(this->as.Variable.span))(move(rhs.as.Variable.span));
new (&this->as.Variable.name) (decltype(this->as.Variable.name))(move(rhs.as.Variable.name));
new (&this->as.Variable.type_id) (decltype(this->as.Variable.type_id))(move(rhs.as.Variable.type_id));
new (&this->as.Variable.mutability) (decltype(this->as.Variable.mutability))(move(rhs.as.Variable.mutability));
new (&this->as.Variable.var_type) (decltype(this->as.Variable.var_type))(move(rhs.as.Variable.var_type));
new (&this->as.Variable.visibility) (decltype(this->as.Variable.visibility))(move(rhs.as.Variable.visibility));
new (&this->as.Variable.struct_type_id) (decltype(this->as.Variable.struct_type_id))(move(rhs.as.Variable.struct_type_id));
break;
case 1 /* Call */:
new (&this->as.Call.value) (decltype(this->as.Call.value))(move(rhs.as.Call.value));
break;
case 2 /* Typename */:
new (&this->as.Typename.value) (decltype(this->as.Typename.value))(move(rhs.as.Typename.value));
break;
case 3 /* NameSet */:
new (&this->as.NameSet.value) (decltype(this->as.NameSet.value))(move(rhs.as.NameSet.value));
break;
case 4 /* EnumVariant */:
new (&this->as.EnumVariant.span) (decltype(this->as.EnumVariant.span))(move(rhs.as.EnumVariant.span));
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(move(rhs.as.EnumVariant.name));
new (&this->as.EnumVariant.type_id) (decltype(this->as.EnumVariant.type_id))(move(rhs.as.EnumVariant.type_id));
new (&this->as.EnumVariant.variants) (decltype(this->as.EnumVariant.variants))(move(rhs.as.EnumVariant.variants));
new (&this->as.EnumVariant.number_constant) (decltype(this->as.EnumVariant.number_constant))(move(rhs.as.EnumVariant.number_constant));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
this->as.Variable.span = move(rhs.as.Variable.span);
this->as.Variable.name = move(rhs.as.Variable.name);
this->as.Variable.type_id = move(rhs.as.Variable.type_id);
this->as.Variable.mutability = move(rhs.as.Variable.mutability);
this->as.Variable.var_type = move(rhs.as.Variable.var_type);
this->as.Variable.visibility = move(rhs.as.Variable.visibility);
this->as.Variable.struct_type_id = move(rhs.as.Variable.struct_type_id);
break;
case 1 /* Call */:
this->as.Call.value = move(rhs.as.Call.value);
break;
case 2 /* Typename */:
this->as.Typename.value = move(rhs.as.Typename.value);
break;
case 3 /* NameSet */:
this->as.NameSet.value = move(rhs.as.NameSet.value);
break;
case 4 /* EnumVariant */:
this->as.EnumVariant.span = move(rhs.as.EnumVariant.span);
this->as.EnumVariant.name = move(rhs.as.EnumVariant.name);
this->as.EnumVariant.type_id = move(rhs.as.EnumVariant.type_id);
this->as.EnumVariant.variants = move(rhs.as.EnumVariant.variants);
this->as.EnumVariant.number_constant = move(rhs.as.EnumVariant.number_constant);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Usage::Usage(Usage &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Variable */:
new (&this->as.Variable.span) (decltype(this->as.Variable.span))(move(rhs.as.Variable.span));
new (&this->as.Variable.name) (decltype(this->as.Variable.name))(move(rhs.as.Variable.name));
new (&this->as.Variable.type_id) (decltype(this->as.Variable.type_id))(move(rhs.as.Variable.type_id));
new (&this->as.Variable.mutability) (decltype(this->as.Variable.mutability))(move(rhs.as.Variable.mutability));
new (&this->as.Variable.var_type) (decltype(this->as.Variable.var_type))(move(rhs.as.Variable.var_type));
new (&this->as.Variable.visibility) (decltype(this->as.Variable.visibility))(move(rhs.as.Variable.visibility));
new (&this->as.Variable.struct_type_id) (decltype(this->as.Variable.struct_type_id))(move(rhs.as.Variable.struct_type_id));
break;
case 1 /* Call */:
new (&this->as.Call.value) (decltype(this->as.Call.value))(move(rhs.as.Call.value));
break;
case 2 /* Typename */:
new (&this->as.Typename.value) (decltype(this->as.Typename.value))(move(rhs.as.Typename.value));
break;
case 3 /* NameSet */:
new (&this->as.NameSet.value) (decltype(this->as.NameSet.value))(move(rhs.as.NameSet.value));
break;
case 4 /* EnumVariant */:
new (&this->as.EnumVariant.span) (decltype(this->as.EnumVariant.span))(move(rhs.as.EnumVariant.span));
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(move(rhs.as.EnumVariant.name));
new (&this->as.EnumVariant.type_id) (decltype(this->as.EnumVariant.type_id))(move(rhs.as.EnumVariant.type_id));
new (&this->as.EnumVariant.variants) (decltype(this->as.EnumVariant.variants))(move(rhs.as.EnumVariant.variants));
new (&this->as.EnumVariant.number_constant) (decltype(this->as.EnumVariant.number_constant))(move(rhs.as.EnumVariant.number_constant));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Usage::~Usage(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void Usage::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Variable */:this->as.Variable.span.~Span();
this->as.Variable.name.~ByteString();
this->as.Variable.type_id.~TypeId();
this->as.Variable.mutability.~Mutability();
this->as.Variable.var_type.~VarType();
this->as.Variable.visibility.~VarVisibility();
this->as.Variable.struct_type_id.~Optional();
break;
case 1 /* Call */:this->as.Call.value.~FunctionId();
break;
case 2 /* Typename */:this->as.Typename.value.~TypeId();
break;
case 3 /* NameSet */:this->as.NameSet.value.~DynamicArray();
break;
case 4 /* EnumVariant */:this->as.EnumVariant.span.~Span();
this->as.EnumVariant.name.~ByteString();
this->as.EnumVariant.type_id.~TypeId();
this->as.EnumVariant.variants.~DynamicArray();
this->as.EnumVariant.number_constant.~Optional();
break;
}
}
}
} // namespace Jakt
