#include "ide.h"
namespace Jakt {
namespace ide {
ErrorOr<JaktInternal::DynamicArray<ide::JaktSymbol>> find_symbols_in_namespace(parser::ParsedNamespace const namespace_) {
{
JaktInternal::DynamicArray<ide::JaktSymbol> symbols = DynamicArray<ide::JaktSymbol>::create_with({});
{
JaktInternal::ArrayIterator<parser::ParsedRecord> _magic = ((((namespace_).records)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedRecord> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedRecord record = (_magic_value.value());
{
((symbols).push(ide::record_to_symbol(record)));
}

}
}

{
JaktInternal::ArrayIterator<parser::ParsedFunction> _magic = ((((namespace_).functions)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedFunction> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedFunction function = (_magic_value.value());
{
((symbols).push(ide::function_to_symbol(function,(ByteString::from_utf8_without_validation("function"sv)))));
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
parser::ParsedNamespace sub_namespace = (_magic_value.value());
{
((symbols).push_values(((TRY((ide::find_symbols_in_namespace(sub_namespace)))))));
}

}
}

if ((((((namespace_).name_span)).has_value()) && ((((namespace_).name)).has_value()))){
utility::Span namespace_span = (((namespace_).name_span).value());
{
JaktInternal::ArrayIterator<ide::JaktSymbol> _magic = ((symbols).iterator());
for (;;){
JaktInternal::Optional<ide::JaktSymbol> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ide::JaktSymbol child = (_magic_value.value());
{
(namespace_span = parser::merge_spans((((namespace_).name_span).value()),((child).range)));
}

}
}

return DynamicArray<ide::JaktSymbol>::create_with({ide::JaktSymbol((((namespace_).name).value()),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("namespace"sv)),namespace_span,(((namespace_).name_span).value()),symbols)});
}
else {
return symbols;
}

}
}

ide::JaktSymbol record_to_symbol(parser::ParsedRecord const record) {
{
JaktInternal::DynamicArray<ide::JaktSymbol> children = DynamicArray<ide::JaktSymbol>::create_with({});
utility::Span record_span = ((record).name_span);
ByteString const record_kind = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ide::JaktSymbol>{
auto&& __jakt_match_variant = ((record).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_876; {
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField field = (_magic_value.value());
{
((children).push(ide::JaktSymbol(((((field).var_decl)).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("field"sv)),((((field).var_decl)).span),((((field).var_decl)).span),DynamicArray<ide::JaktSymbol>::create_with({}))));
}

}
}

__jakt_var_876 = (ByteString::from_utf8_without_validation("struct"sv)); goto __jakt_label_770;

}
__jakt_label_770:; __jakt_var_876.release_value(); }));
};/*case end*/
case 1 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<parser::ParsedField> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_877; {
{
JaktInternal::ArrayIterator<parser::ParsedField> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedField field = (_magic_value.value());
{
((children).push(ide::JaktSymbol(((((field).var_decl)).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("field"sv)),((((field).var_decl)).span),((((field).var_decl)).span),DynamicArray<ide::JaktSymbol>::create_with({}))));
}

}
}

__jakt_var_877 = (ByteString::from_utf8_without_validation("class"sv)); goto __jakt_label_771;

}
__jakt_label_771:; __jakt_var_877.release_value(); }));
};/*case end*/
case 2 /* ValueEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ValueEnum;JaktInternal::DynamicArray<parser::ValueEnumVariant> const& variants = __jakt_match_value.variants;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_878; {
{
JaktInternal::ArrayIterator<parser::ValueEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<parser::ValueEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ValueEnumVariant variant = (_magic_value.value());
{
((children).push(ide::JaktSymbol(((variant).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("enum-member"sv)),((variant).span),((variant).span),DynamicArray<ide::JaktSymbol>::create_with({}))));
}

}
}

__jakt_var_878 = (ByteString::from_utf8_without_validation("enum"sv)); goto __jakt_label_772;

}
__jakt_label_772:; __jakt_var_878.release_value(); }));
};/*case end*/
case 3 /* SumEnum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SumEnum;JaktInternal::DynamicArray<parser::SumEnumVariant> const& variants = __jakt_match_value.variants;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_879; {
{
JaktInternal::ArrayIterator<parser::SumEnumVariant> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<parser::SumEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::SumEnumVariant variant = (_magic_value.value());
{
JaktInternal::DynamicArray<ide::JaktSymbol> variant_children = DynamicArray<ide::JaktSymbol>::create_with({});
if (((((variant).params)).has_value())){
{
JaktInternal::ArrayIterator<parser::ParsedVarDecl> _magic = (((((variant).params).value())).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedVarDecl> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedVarDecl param = (_magic_value.value());
{
if ([](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(((param).name),(ByteString::from_utf8_without_validation(""sv)))){
((variant_children).push(ide::JaktSymbol(((param).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("field"sv)),((param).span),((param).span),DynamicArray<ide::JaktSymbol>::create_with({}))));
}
}

}
}

}
((children).push(ide::JaktSymbol(((variant).name),JaktInternal::OptionalNone(),(ByteString::from_utf8_without_validation("enum-member"sv)),((variant).span),((variant).span),variant_children)));
}

}
}

__jakt_var_879 = (ByteString::from_utf8_without_validation("enum"sv)); goto __jakt_label_773;

}
__jakt_label_773:; __jakt_var_879.release_value(); }));
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
JaktInternal::ArrayIterator<parser::ParsedMethod> _magic = ((((record).methods)).iterator());
for (;;){
JaktInternal::Optional<parser::ParsedMethod> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
parser::ParsedMethod method = (_magic_value.value());
{
ide::JaktSymbol const function_symbol = ide::function_to_symbol(((method).parsed_function),(ByteString::from_utf8_without_validation("method"sv)));
((children).push(function_symbol));
(record_span = parser::merge_spans(record_span,((function_symbol).range)));
}

}
}

return ide::JaktSymbol(((record).name),JaktInternal::OptionalNone(),record_kind,record_span,((record).name_span),children);
}
}

ide::JaktSymbol function_to_symbol(parser::ParsedFunction const function,ByteString const kind) {
{
utility::Span function_span = ((function).name_span);
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename parser::ParsedStatement>> _magic = ((((((function).block)).stmts)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename parser::ParsedStatement> stmt = (_magic_value.value());
{
(function_span = parser::merge_spans(function_span,((stmt)->span())));
}

}
}

return ide::JaktSymbol(((function).name),JaktInternal::OptionalNone(),kind,function_span,((function).name_span),DynamicArray<ide::JaktSymbol>::create_with({}));
}
}

ErrorOr<utility::Span> find_definition_in_program(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Variable;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;ids::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_function(function_id)))->name_span));
};/*case end*/
case 2 /* Typename */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typename;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 3 /* NameSet */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;utility::Span const& span = __jakt_match_value.span;
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

ErrorOr<utility::Span> find_type_definition_for_type_id(NonnullRefPtr<types::CheckedProgram> const program,ids::TypeId const type_id,utility::Span const span) {
{
ids::StructId const array_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
ids::StructId const dictionary_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Dictionary"sv))))));
ids::StructId const optional_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Optional"sv))))));
ids::StructId const range_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Range"sv))))));
ids::StructId const set_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Set"sv))))));
ids::StructId const tuple_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Tuple"sv))))));
ids::StructId const weak_ptr_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("WeakPtr"sv))))));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
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
case 30 /* Function */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_trait(id)))->name_span));
};/*case end*/
case 31 /* Self */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19 /* Dependent */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 32 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((value).span));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_880; {
utility::Span output = span;
if ((((((((struct_id).equals(array_struct_id)) || ((struct_id).equals(optional_struct_id))) || ((struct_id).equals(range_struct_id))) || ((struct_id).equals(set_struct_id))) || ((struct_id).equals(tuple_struct_id))) || ((struct_id).equals(weak_ptr_struct_id)))){
(output = TRY((ide::find_type_definition_for_type_id(program,((args)[static_cast<i64>(0LL)]),span))));
}
else if (((struct_id).equals(dictionary_struct_id))){
(output = TRY((ide::find_type_definition_for_type_id(program,((args)[static_cast<i64>(1LL)]),span))));
}
else {
(output = ((((program)->get_struct(struct_id))).name_span));
}

__jakt_var_880 = output; goto __jakt_label_774;

}
__jakt_label_774:; __jakt_var_880.release_value(); }));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_struct(struct_id))).name_span));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_enum(id))).name_span));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_trait(id)))->name_span));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_enum(id))).name_span));
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_struct(id))).name_span));
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_type_definition_for_type_id(program,type_id,span))));
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

ErrorOr<utility::Span> find_type_definition_in_program(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, ErrorOr<utility::Span>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Variable;utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_881; {
__jakt_var_881 = TRY((ide::find_type_definition_for_type_id(program,type_id,span))); goto __jakt_label_775;

}
__jakt_label_775:; __jakt_var_881.release_value(); }));
};/*case end*/
case 1 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;ids::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_882; {
__jakt_var_882 = ((((program)->get_function(function_id)))->name_span); goto __jakt_label_776;

}
__jakt_label_776:; __jakt_var_882.release_value(); }));
};/*case end*/
case 2 /* Typename */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typename;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<utility::Span> __jakt_var_883; {
__jakt_var_883 = TRY((ide::find_type_definition_for_type_id(program,type_id,span))); goto __jakt_label_777;

}
__jakt_label_777:; __jakt_var_883.release_value(); }));
};/*case end*/
case 3 /* NameSet */: {
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;utility::Span const& span = __jakt_match_value.span;
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

ErrorOr<JaktInternal::Optional<ByteString>> find_typename_in_program(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ByteString>, ErrorOr<JaktInternal::Optional<ByteString>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Variable;ByteString const& name = __jakt_match_value.name;
ids::TypeId const& type_id = __jakt_match_value.type_id;
ide::Mutability const& mutability = __jakt_match_value.mutability;
ide::VarType const& var_type = __jakt_match_value.var_type;
ide::VarVisibility const& visibility = __jakt_match_value.visibility;
JaktInternal::Optional<ids::TypeId> const& struct_type_id = __jakt_match_value.struct_type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_884; {
ByteString const result = TRY((ide::get_var_signature(program,name,type_id,mutability,var_type,visibility,struct_type_id)));
__jakt_var_884 = static_cast<JaktInternal::Optional<ByteString>>(result); goto __jakt_label_778;

}
__jakt_label_778:; __jakt_var_884.release_value(); }));
};/*case end*/
case 1 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;ids::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_885; {
ByteString const result = TRY((ide::get_function_signature(program,function_id)));
__jakt_var_885 = static_cast<JaktInternal::Optional<ByteString>>(result); goto __jakt_label_779;

}
__jakt_label_779:; __jakt_var_885.release_value(); }));
};/*case end*/
case 2 /* Typename */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typename;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_886; {
ByteString const result = TRY((ide::get_type_signature(program,type_id)));
__jakt_var_886 = static_cast<JaktInternal::Optional<ByteString>>(result); goto __jakt_label_780;

}
__jakt_label_780:; __jakt_var_886.release_value(); }));
};/*case end*/
case 3 /* NameSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NameSet;JaktInternal::DynamicArray<ByteString> const& names = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_887; {
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
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(" | "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,name);
}

}
}

__jakt_var_887 = static_cast<JaktInternal::Optional<ByteString>>(output); goto __jakt_label_781;

}
__jakt_label_781:; __jakt_var_887.release_value(); }));
};/*case end*/
case 4 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
ids::TypeId const& type_id = __jakt_match_value.type_id;
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const& variants = __jakt_match_value.variants;
JaktInternal::Optional<types::NumberConstant> const& number_constant = __jakt_match_value.number_constant;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ByteString>> __jakt_var_888; {
ByteString const result = TRY((ide::get_enum_variant_signature(program,name,type_id,variants,number_constant)));
__jakt_var_888 = static_cast<JaktInternal::Optional<ByteString>>(result); goto __jakt_label_782;

}
__jakt_label_782:; __jakt_var_888.release_value(); }));
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

ErrorOr<JaktInternal::DynamicArray<ByteString>> completions_for_type_id(NonnullRefPtr<types::CheckedProgram> const program,ids::TypeId const type_id) {
{
JaktInternal::DynamicArray<ByteString> output = DynamicArray<ByteString>::create_with({});
NonnullRefPtr<typename types::Type> const ty = ((program)->get_type(type_id));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::DynamicArray<ByteString>>>{
auto&& __jakt_match_variant = *ty;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
NonnullRefPtr<types::Scope> const scope = ((program)->get_scope(((enum_).scope_id)));
((output).push_values(((TRY((ide::find_function_completions_in_scope(scope,program)))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const structure = ((program)->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const field_var = ((program)->get_variable(((field).variable_id)));
((output).push(((field_var)->name)));
}

}
}

NonnullRefPtr<types::Scope> const scope = ((program)->get_scope(((structure).scope_id)));
((output).push_values(((TRY((ide::find_function_completions_in_scope(scope,program)))))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
{
types::CheckedStruct const structure = ((program)->get_struct(struct_id));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const field_var = ((program)->get_variable(((field).variable_id)));
((output).push(((field_var)->name)));
}

}
}

NonnullRefPtr<types::Scope> const scope = ((program)->get_scope(((structure).scope_id)));
((output).push_values(((TRY((ide::find_function_completions_in_scope(scope,program)))))));
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
return output;
}
}

ErrorOr<JaktInternal::DynamicArray<ByteString>> find_function_completions_in_scope(NonnullRefPtr<types::Scope> const scope,NonnullRefPtr<types::CheckedProgram> const program) {
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
JaktInternal::DynamicArray<ids::FunctionId> const overload_set = (((((scope)->functions)).get(function_name)).value());
{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId function_id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
if (((((((checked_function)->params)).first())).has_value())){
types::CheckedParameter const param = (((((checked_function)->params)).first()).value());
if (((((((param).variable))->name)) == ((ByteString::from_utf8_without_validation("this"sv))))){
ByteString full_call = ((checked_function)->name);
bool first = true;
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(full_call,(ByteString::from_utf8_without_validation("("sv)));
JaktInternal::ArrayIterator<types::CheckedParameter> iter = ((((checked_function)->params)).iterator());
JaktInternal::Optional<types::CheckedParameter> const dummy = ((iter).next());
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = iter;
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if ((!(first))){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(full_call,(ByteString::from_utf8_without_validation(", "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(full_call,((((param).variable))->name));
}

}
}

[](ByteString& self, ByteString rhs) -> void {
{
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

ErrorOr<JaktInternal::DynamicArray<ByteString>> find_dot_completions(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const result = TRY((ide::find_span_in_program(program,span)));
if (((result).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<ByteString>, ErrorOr<JaktInternal::DynamicArray<ByteString>>>{
auto&& __jakt_match_variant = (result.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Variable;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<ByteString>> __jakt_var_889; {
__jakt_var_889 = TRY((ide::completions_for_type_id(program,type_id))); goto __jakt_label_783;

}
__jakt_label_783:; __jakt_var_889.release_value(); }));
};/*case end*/
case 1 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;ids::FunctionId const& function_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<ByteString>> __jakt_var_890; {
ids::TypeId const result_type_id = ((((program)->get_function(function_id)))->return_type_id);
__jakt_var_890 = TRY((ide::completions_for_type_id(program,result_type_id))); goto __jakt_label_784;

}
__jakt_label_784:; __jakt_var_890.release_value(); }));
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

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_program(NonnullRefPtr<types::CheckedProgram> const program,utility::Span const span) {
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> iterator = ((((program)->modules)).iterator());
JaktInternal::Optional<NonnullRefPtr<types::Module>> const dummy = ((iterator).next());
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = iterator;
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const scope = ((program)->get_scope(ids::ScopeId(((module)->id),static_cast<size_t>(0ULL))));
return TRY((ide::find_span_in_scope(program,scope,span)));
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_scope(NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<types::Scope> const scope,utility::Span const span) {
{
{
JaktInternal::DictionaryIterator<ByteString,ids::VarId> _magic = ((((scope)->vars)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::VarId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::VarId> scope_var = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const var = ((program)->get_variable(((scope_var).template get<1>())));
if (((((var)->definition_span)).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Typename(((var)->type_id)));
}
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
NonnullRefPtr<types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_function(program,checked_function,span)));
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
JaktInternal::DictionaryIterator<ByteString,ids::StructId> _magic = ((((scope)->structs)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::StructId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::StructId> struct_id = (_magic_value.value());
{
types::CheckedStruct const checked_struct = ((program)->get_struct(((struct_id).template get<1>())));
JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_struct(program,checked_struct,span)));
if (((usage).has_value())){
return (usage.value());
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
JaktInternal::Tuple<ByteString,ids::EnumId> enum_id = (_magic_value.value());
{
types::CheckedEnum const checked_enum = ((program)->get_enum(((enum_id).template get<1>())));
JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_enum(program,checked_enum,span)));
if (((usage).has_value())){
return (usage.value());
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
ids::ScopeId child = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const scope = ((program)->get_scope(child));
JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_scope(program,scope,span)));
if (((usage).has_value())){
return (usage.value());
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_enum(NonnullRefPtr<types::CheckedProgram> const program,types::CheckedEnum const checked_enum,utility::Span const span) {
{
NonnullRefPtr<types::Scope> const scope = ((program)->get_scope(((checked_enum).scope_id)));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((checked_enum).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
utility::Span const& variant_span = __jakt_match_value.span;
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
NonnullRefPtr<types::CheckedVariable> const var = ((program)->get_variable(field));
if (((((var)->definition_span)).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Typename(((var)->type_id)));
}
}

}
}

if (((variant_span).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::EnumVariant(span,name,((checked_enum).type_id),DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>::create_with({}),JaktInternal::OptionalNone()));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),ide::enum_variant_fields(program,variant),JaktInternal::OptionalNone()));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>::create_with({}),JaktInternal::OptionalNone()));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& name = __jakt_match_value.name;
NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
utility::Span const& variant_span = __jakt_match_value.span;
{
if (((variant_span).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::EnumVariant(variant_span,name,((checked_enum).type_id),ide::enum_variant_fields(program,variant),((expr)->to_number_constant(program))));
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

JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_scope(program,scope,span)));
return usage;
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_struct(NonnullRefPtr<types::CheckedProgram> const program,types::CheckedStruct const checked_struct,utility::Span const span) {
{
NonnullRefPtr<types::Scope> const scope = ((program)->get_scope(((checked_struct).scope_id)));
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((checked_struct).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((program)->get_variable(((field).variable_id)));
if (((((variable)->definition_span)).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Typename(((variable)->type_id)));
}
}

}
}

JaktInternal::Optional<ide::Usage> const usage = TRY((ide::find_span_in_scope(program,scope,span)));
return usage;
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_function(NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<types::CheckedFunction> const checked_function,utility::Span const span) {
{
if (((((checked_function)->return_type_span)).has_value())){
if ((((((checked_function)->return_type_span).value())).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Typename(((checked_function)->return_type_id)));
}
}
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
if (((((((param).variable))->definition_span)).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Typename(((((param).variable))->type_id)));
}
}

}
}

return TRY((ide::find_span_in_block(program,((checked_function)->block),span)));
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_block(NonnullRefPtr<types::CheckedProgram> const program,types::CheckedBlock const block,utility::Span const span) {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> statement = (_magic_value.value());
{
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_statement(program,statement,span)));
if (((found).has_value())){
return found;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_statement(NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<typename types::CheckedStatement> const statement,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const none = JaktInternal::OptionalNone();
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename types::CheckedStatement> const& statement = __jakt_match_value.statement;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_statement(program,statement,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_891; {
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,condition,span)));
if (((found).has_value())){
return found;
}
(found = TRY((ide::find_span_in_block(program,then_block,span))));
if (((found).has_value())){
return found;
}
if (((else_statement).has_value())){
return TRY((ide::find_span_in_statement(program,(else_statement.value()),span)));
}
__jakt_var_891 = none; goto __jakt_label_785;

}
__jakt_label_785:; __jakt_var_891.release_value(); }));
};/*case end*/
case 13 /* InlineCpp */: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_892; {
JaktInternal::Optional<ide::Usage> const output = JaktInternal::OptionalNone();
__jakt_var_892 = output; goto __jakt_label_786;

}
__jakt_label_786:; __jakt_var_892.release_value(); }));
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((val).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,(val.value()),span))));
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
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;ids::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<typename types::CheckedExpression> const& init = __jakt_match_value.init;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_893; {
NonnullRefPtr<types::CheckedVariable> const checked_var = ((program)->get_variable(var_id));
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,init,span)));
if (((found).has_value())){
return found;
}
if (((((checked_var)->type_span)).has_value())){
utility::Span const type_span = (((checked_var)->type_span).value());
if (((type_span).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Typename(((checked_var)->type_id)));
}
}
if (((((checked_var)->definition_span)).contains(span))){
ide::Mutability const mutability = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::Mutability,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((checked_var)->is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(ide::Mutability::Mutable());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(ide::Mutability::Immutable());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Variable(((checked_var)->definition_span),((checked_var)->name),((checked_var)->type_id),mutability,ide::VarType::Variable(),ide::VarVisibility::DoesNotApply(),JaktInternal::OptionalNone()));
}
__jakt_var_893 = none; goto __jakt_label_787;

}
__jakt_label_787:; __jakt_var_893.release_value(); }));
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename types::CheckedExpression> const& condition = __jakt_match_value.condition;
types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_894; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,condition,span)));
if (((found).has_value())){
return found;
}
__jakt_var_894 = TRY((ide::find_span_in_block(program,block,span))); goto __jakt_label_788;

}
__jakt_label_788:; __jakt_var_894.release_value(); }));
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_895; {
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedStatement>> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedStatement> var = (_magic_value.value());
{
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_statement(program,var,span)));
if (((found).has_value())){
return found;
}
}

}
}

__jakt_var_895 = TRY((ide::find_span_in_statement(program,var_decl,span))); goto __jakt_label_789;

}
__jakt_label_789:; __jakt_var_895.release_value(); }));
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
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

ErrorOr<JaktInternal::Optional<ide::Usage>> find_span_in_expression(NonnullRefPtr<types::CheckedProgram> const program,NonnullRefPtr<typename types::CheckedExpression> const expr,utility::Span const span) {
{
JaktInternal::Optional<ide::Usage> const none = JaktInternal::OptionalNone();
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
types::CheckedBinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_896; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,lhs,span)));
if (((found).has_value())){
return found;
}
__jakt_var_896 = TRY((ide::find_span_in_expression(program,rhs,span))); goto __jakt_label_790;

}
__jakt_label_790:; __jakt_var_896.release_value(); }));
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_897; {
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,val,span)));
if (((found).has_value())){
return found;
}
}

}
}

if (((repeat).has_value())){
return TRY((ide::find_span_in_expression(program,(repeat.value()),span)));
}
__jakt_var_897 = none; goto __jakt_label_791;

}
__jakt_label_791:; __jakt_var_897.release_value(); }));
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& call_span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_898; {
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

JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
}

}
}

if ((((((call).function_id)).has_value()) && ((call_span).contains(span)))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Call((((call).function_id).value())));
}
__jakt_var_898 = none; goto __jakt_label_792;

}
__jakt_label_792:; __jakt_var_898.release_value(); }));
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_899; {
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

JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,key,span)));
if (((found).has_value())){
return found;
}
(found = TRY((ide::find_span_in_expression(program,value,span))));
if (((found).has_value())){
return found;
}
}

}
}

__jakt_var_899 = none; goto __jakt_label_793;

}
__jakt_label_793:; __jakt_var_899.release_value(); }));
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_900; {
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
(found = TRY((ide::find_span_in_expression(program,index,span))));
if (((found).has_value())){
return found;
}
__jakt_var_900 = none; goto __jakt_label_794;

}
__jakt_label_794:; __jakt_var_900.release_value(); }));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& name = __jakt_match_value.name;
utility::Span const& index_span = __jakt_match_value.span;
ids::TypeId const& known_type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_901; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
if (((index_span).contains(span))){
ids::TypeId const type_id = ((expr)->type());
JaktInternal::Optional<ids::TypeId> result_type = JaktInternal::OptionalNone();
if ((!(((known_type_id).equals(types::unknown_type_id()))))){
(result_type = static_cast<JaktInternal::Optional<ids::TypeId>>(known_type_id));
}
if (((((program)->get_type(type_id)))->__jakt_init_index() == 24 /* Struct */)){
ids::StructId const struct_id = (((program)->get_type(type_id)))->as.Struct.value;
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((((program)->get_struct(struct_id))).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const var = ((program)->get_variable(((field).variable_id)));
if ([](ByteString const& self, ByteString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(name,((var)->name))){
continue;
}
return ide::Usage::Variable(((var)->definition_span),name,result_type.value_or_lazy_evaluated([&] { return ((var)->type_id); }),ide::Mutability::DoesNotApply(),ide::VarType::Field(),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::VarVisibility, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = ((var)->visibility);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Public */: {
return JaktInternal::ExplicitValue(ide::VarVisibility::Public());
};/*case end*/
case 1 /* Private */: {
return JaktInternal::ExplicitValue(ide::VarVisibility::Private());
};/*case end*/
case 2 /* Restricted */: {
return JaktInternal::ExplicitValue(ide::VarVisibility::Restricted());
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
__jakt_var_901 = none; goto __jakt_label_795;

}
__jakt_label_795:; __jakt_var_901.release_value(); }));
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename types::CheckedExpression> const& index = __jakt_match_value.index;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_902; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
__jakt_var_902 = TRY((ide::find_span_in_expression(program,index,span))); goto __jakt_label_796;

}
__jakt_label_796:; __jakt_var_902.release_value(); }));
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
utility::Span const& match_span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_903; {
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase match_case = (_magic_value.value());
{
JaktInternal::Optional<ide::Usage> const found = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
ids::TypeId const& subject_type_id = __jakt_match_value.subject_type_id;
size_t const& index = __jakt_match_value.index;
ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_904; {
if (((marker_span).contains(span))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::get_enum_variant_usage_from_type_id_and_name(program,subject_type_id,name));
}
__jakt_var_904 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
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
}); goto __jakt_label_798;

}
__jakt_label_798:; __jakt_var_904.release_value(); }));
};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expression;
types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_905; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
__jakt_var_905 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
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
}); goto __jakt_label_799;

}
__jakt_label_799:; __jakt_var_905.release_value(); }));
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((marker_span).contains(span)));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_906; {
JaktInternal::Set<ByteString> const all_cases = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Set<ByteString>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = *((program)->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<ByteString>> __jakt_var_907; {
JaktInternal::Set<ByteString> names = Set<ByteString>::create_with_values({});
types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
((names).add(((variant).name())));
}

}
}

__jakt_var_907 = names; goto __jakt_label_801;

}
__jakt_label_801:; __jakt_var_907.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<ByteString>> __jakt_var_908; {
JaktInternal::Set<ByteString> names = Set<ByteString>::create_with_values({});
types::CheckedEnum const enum_ = ((program)->get_enum(enum_id));
{
JaktInternal::ArrayIterator<types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnumVariant variant = (_magic_value.value());
{
((names).add(((variant).name())));
}

}
}

__jakt_var_908 = names; goto __jakt_label_802;

}
__jakt_label_802:; __jakt_var_908.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Set<ByteString>> __jakt_var_909; {
__jakt_var_909 = Set<ByteString>::create_with_values({__jakt_format((StringView::from_string_literal("else ({})"sv)),TRY((((program)->type_name(type_id,false)))))}); goto __jakt_label_803;

}
__jakt_label_803:; __jakt_var_909.release_value(); }));
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
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase other_case = (_magic_value.value());
{
if (((other_case).__jakt_init_index() == 0 /* EnumVariant */)){
ByteString const name = (other_case).as.EnumVariant.name;
((remaining_cases).remove(name));
}
}

}
}

__jakt_var_906 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((remaining_cases).is_empty()));
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_910; {
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

__jakt_var_910 = static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::NameSet(cases_array)); goto __jakt_label_804;

}
__jakt_label_804:; __jakt_var_910.release_value(); }));
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
}); goto __jakt_label_800;

}
__jakt_label_800:; __jakt_var_906.release_value(); }));
}
else {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
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
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;types::CheckedMatchBody const& body = __jakt_match_value.body;
utility::Span const& marker_span = __jakt_match_value.marker_span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((marker_span).contains(span)));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
else {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>, ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,block,span))));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
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

__jakt_var_903 = TRY((ide::find_span_in_expression(program,expr,span))); goto __jakt_label_797;

}
__jakt_label_797:; __jakt_var_903.release_value(); }));
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_expression(program,expr,span))));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedCall const& call = __jakt_match_value.call;
utility::Span const& method_span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<ide::Usage> found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
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

(found = TRY((ide::find_span_in_expression(program,expr,span))));
if (((found).has_value())){
return found;
}
}

}
}

if ((((((call).function_id)).has_value()) && ((method_span).contains(span)))){
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Call((((call).function_id).value())));
}
return none;
}
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
utility::Span const& var_span = __jakt_match_value.span;
{
JaktInternal::Optional<ids::TypeId> const none_type_id = JaktInternal::OptionalNone();
if (((var_span).contains(span))){
ide::Mutability const mutability = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ide::Mutability,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((var)->is_mutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(ide::Mutability::Mutable());
}
else {
return JaktInternal::ExplicitValue(ide::Mutability::Immutable());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::Usage::Variable(((var)->definition_span),((var)->name),((var)->type_id),mutability,ide::VarType::Variable(),ide::VarVisibility::DoesNotApply(),none_type_id));
}
return none;
}
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;JaktInternal::DynamicArray<types::CheckedNamespace> const& namespaces = __jakt_match_value.namespaces;
NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
utility::Span const& var_span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_911; {
if ((((var_span).contains(span)) && (!(((namespaces).is_empty()))))){
types::CheckedNamespace const last_ns = (((namespaces).last()).value());
if (((((((program)->get_scope(((last_ns).scope))))->namespace_name)).has_value())){
JaktInternal::Optional<ids::EnumId> const enum_id = TRY((((program)->find_enum_in_scope(((last_ns).scope),((last_ns).name),false,JaktInternal::OptionalNone()))));
if (((enum_id).has_value())){
types::CheckedEnum const enum_ = ((program)->get_enum((enum_id.value())));
return static_cast<JaktInternal::Optional<ide::Usage>>(ide::get_enum_variant_usage_from_type_id_and_name(program,((enum_).type_id),((var)->name)));
}
}
}
__jakt_var_911 = none; goto __jakt_label_805;

}
__jakt_label_805:; __jakt_var_911.release_value(); }));
};/*case end*/
case 32 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
ByteString const& error_name = __jakt_match_value.error_name;
types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_912; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_statement(program,stmt,span)));
if (((found).has_value())){
return found;
}
__jakt_var_912 = TRY((ide::find_span_in_block(program,catch_block,span))); goto __jakt_label_806;

}
__jakt_label_806:; __jakt_var_912.release_value(); }));
};/*case end*/
case 31 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::Optional<types::CheckedBlock> const& catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_913; {
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,expr,span)));
if (((found).has_value())){
return found;
}
__jakt_var_913 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ide::Usage>,ErrorOr<JaktInternal::Optional<ide::Usage>>>{
auto __jakt_enum_value = (((catch_block).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((ide::find_span_in_block(program,(catch_block.value()),span))));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(none);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_807;

}
__jakt_label_807:; __jakt_var_913.release_value(); }));
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const& to = __jakt_match_value.to;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<ide::Usage>> __jakt_var_914; {
if (((from).has_value())){
JaktInternal::Optional<ide::Usage> const found = TRY((ide::find_span_in_expression(program,(from.value()),span)));
if (((found).has_value())){
return found;
}
}
if (((to).has_value())){
return TRY((ide::find_span_in_expression(program,(to.value()),span)));
}
__jakt_var_914 = none; goto __jakt_label_808;

}
__jakt_label_808:; __jakt_var_914.release_value(); }));
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

ErrorOr<ByteString> get_function_signature(NonnullRefPtr<types::CheckedProgram> const program,ids::FunctionId const function_id) {
{
NonnullRefPtr<types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = ((checked_function)->type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* ImplicitEnumConstructor */: {
{
ids::TypeId const type_id = ((checked_function)->return_type_id);
ByteString const name = ((checked_function)->name);
return TRY((ide::get_enum_variant_signature_from_type_id_and_name(program,type_id,name)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* ImplicitConstructor */: {
{
return TRY((ide::get_constructor_signature(program,function_id)));
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
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(generic_parameters,(ByteString::from_utf8_without_validation("<"sv)));
{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((((((checked_function)->generics))->params)).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter parameter = (_magic_value.value());
{
ByteString const generic_type = TRY((((program)->type_name(((parameter).type_id()),false))));
ByteString const separator = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
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
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(generic_parameters,__jakt_format((StringView::from_string_literal("{}{}"sv)),separator,generic_type));
(is_first_param = false);
}

}
}

[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(generic_parameters,(ByteString::from_utf8_without_validation(">"sv)));
}
ByteString parameters = (ByteString::from_utf8_without_validation(""sv));
(is_first_param = true);
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((checked_function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
ByteString const anon_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
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
if ([](ByteString const& self, ByteString rhs) -> bool {
{
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
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
[](ByteString& self, ByteString rhs) -> void {
{
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
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(parameters,(ByteString::from_utf8_without_validation(".."sv)));
}
else {
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(parameters,(ByteString::from_utf8_without_validation(", .."sv)));
}

}
ByteString const throws_str = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
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
if ([](ByteString const& self, ByteString rhs) -> bool {
{
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

ErrorOr<ByteString> get_var_signature(NonnullRefPtr<types::CheckedProgram> const program,ByteString const name,ids::TypeId const var_type_id,ide::Mutability const mutability,ide::VarType const var_type,ide::VarVisibility const visibility,JaktInternal::Optional<ids::TypeId> const struct_type_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = var_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Variable */: {
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_915; {
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
ByteString const type_name = TRY((ide::get_type_signature(program,var_type_id)));
__jakt_var_915 = __jakt_format((StringView::from_string_literal("{} {}: {}"sv)),mut_string,name,type_name); goto __jakt_label_809;

}
__jakt_label_809:; __jakt_var_915.release_value(); }));
};/*case end*/
case 1 /* Field */: {
{
ByteString record_string = (ByteString::from_utf8_without_validation(""sv));
if (((struct_type_id).has_value())){
(record_string = TRY((ide::get_type_signature(program,(struct_type_id.value())))));
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
ByteString const type_name = TRY((ide::get_type_signature(program,var_type_id)));
if ([](ByteString const& self, ByteString rhs) -> bool {
{
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

ErrorOr<ByteString> get_type_signature(NonnullRefPtr<types::CheckedProgram> const program,ids::TypeId const type_id) {
{
ids::StructId const array_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
ids::StructId const dictionary_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Dictionary"sv))))));
ids::StructId const optional_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Optional"sv))))));
ids::StructId const range_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Range"sv))))));
ids::StructId const set_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Set"sv))))));
ids::StructId const tuple_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("Tuple"sv))))));
ids::StructId const weak_ptr_struct_id = TRY((((program)->find_struct_in_prelude((ByteString::from_utf8_without_validation("WeakPtr"sv))))));
NonnullRefPtr<typename types::Type> const type = ((program)->get_type(type_id));
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
case 31 /* Self */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Self"sv)));
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_trait(trait_id)))->name));
};/*case end*/
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}::{}"sv)),TRY((((program)->type_name(namespace_type,false)))),name));
};/*case end*/
case 32 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::comptime_format_impl((ByteString::from_utf8_without_validation("const {}"sv)),((DynamicArray<types::Value>::create_with({value}))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})]),((program))))));
};/*case end*/
case 30 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_916; {
JaktInternal::DynamicArray<ByteString> param_names = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId x = (_magic_value.value());
{
((param_names).push(TRY((((program)->type_name(x,false))))));
}

}
}

ByteString const return_type = TRY((((program)->type_name(return_type_id,false))));
__jakt_var_916 = __jakt_format((StringView::from_string_literal("fn({}) -> {}"sv)),utility::join(param_names,(ByteString::from_utf8_without_validation(", "sv))),return_type); goto __jakt_label_810;

}
__jakt_label_810:; __jakt_var_916.release_value(); }));
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue((((ByteString::from_utf8_without_validation("raw "sv))) + (TRY((ide::get_type_signature(program,type_id))))));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_917; {
types::CheckedEnum const enum_ = ((program)->get_enum(id));
__jakt_var_917 = ((((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>>{
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
})) + ((ByteString::from_utf8_without_validation("enum "sv))))) + (((enum_).name))); goto __jakt_label_811;

}
__jakt_label_811:; __jakt_var_917.release_value(); }));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_918; {
types::CheckedStruct const struct_ = ((program)->get_struct(id));
__jakt_var_918 = ((({
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
utility::panic((ByteString::from_utf8_without_validation("unreachable: should've been struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})) + (((struct_).name))); goto __jakt_label_812;

}
__jakt_label_812:; __jakt_var_918.release_value(); }));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_919; {
types::CheckedStruct const record = ((program)->get_struct(id));
ByteString output = ((record).name);
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_919 = ((output) + ((ByteString::from_utf8_without_validation(">"sv)))); goto __jakt_label_813;

}
__jakt_label_813:; __jakt_var_919.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_920; {
types::CheckedEnum const enum_ = ((program)->get_enum(id));
ByteString output = (ByteString::from_utf8_without_validation(""sv));
if (((enum_).is_boxed)){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("boxed "sv)));
}
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("enum "sv)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,((enum_).name));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_920 = ((output) + ((ByteString::from_utf8_without_validation(">"sv)))); goto __jakt_label_814;

}
__jakt_label_814:; __jakt_var_920.release_value(); }));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_921; {
NonnullRefPtr<types::CheckedTrait> const trait_ = ((program)->get_trait(id));
ByteString output = (ByteString::from_utf8_without_validation(""sv));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("trait "sv)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,((trait_)->name));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_921 = ((output) + ((ByteString::from_utf8_without_validation(">"sv)))); goto __jakt_label_815;

}
__jakt_label_815:; __jakt_var_921.release_value(); }));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_922; {
if (((id).equals(array_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation("[]"sv));
}
return __jakt_format((StringView::from_string_literal("[{}]"sv)),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
}
if (((id).equals(dictionary_struct_id))){
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
(((args).size()),static_cast<size_t>(2ULL))){
return (ByteString::from_utf8_without_validation("[:]"sv));
}
return __jakt_format((StringView::from_string_literal("[{}: {}]"sv)),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(1LL)])))));
}
if (((id).equals(optional_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation(""sv));
}
return __jakt_format((StringView::from_string_literal("{}?"sv)),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
}
if (((id).equals(range_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation(""sv));
}
return __jakt_format((StringView::from_string_literal("{}..{}"sv)),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))),TRY((((program)->type_name(((args)[static_cast<i64>(0LL)]),false)))));
}
if (((id).equals(set_struct_id))){
if (((args).is_empty())){
return (ByteString::from_utf8_without_validation(""sv));
}
return __jakt_format((StringView::from_string_literal("{{{}}}"sv)),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
}
if (((id).equals(tuple_struct_id))){
ByteString output = (ByteString::from_utf8_without_validation("("sv));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[i])))));
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
return __jakt_format((StringView::from_string_literal("weak {}"sv)),TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
}
types::CheckedStruct const record = ((program)->get_struct(id));
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
utility::panic((ByteString::from_utf8_without_validation("unreachable: can't be an enum"sv)));
}
};/*case end*/
case 3 /* SumEnum */: {
{
utility::panic((ByteString::from_utf8_without_validation("unreachable: can't be an enum"sv)));
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
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,((record).name));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
if ((!(((args).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[static_cast<i64>(0LL)])))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(1ULL)),static_cast<size_t>(((args).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((ide::get_type_signature(program,((args)[i])))));
}

}
}

}
__jakt_var_922 = ((output) + ((ByteString::from_utf8_without_validation(">"sv)))); goto __jakt_label_816;

}
__jakt_label_816:; __jakt_var_922.release_value(); }));
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("&{}"sv)),TRY((((program)->type_name(type_id,false))))));
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;ids::TypeId const& type_id = __jakt_match_value.value;
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

ErrorOr<ByteString> get_enum_variant_signature(NonnullRefPtr<types::CheckedProgram> const program,ByteString const name,ids::TypeId const type_id,JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const variants,JaktInternal::Optional<types::NumberConstant> const number_constant) {
{
ByteString output = TRY((ide::get_type_signature(program,type_id)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("::"sv)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,name);
if ((!(((variants).is_empty())))){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("("sv)));
bool first = true;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> _magic = ((variants).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId> variant_name__variant_type_id__ = (_magic_value.value());
{
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId> const jakt__variant_name__variant_type_id__ = variant_name__variant_type_id__;
JaktInternal::Optional<ByteString> const variant_name = ((jakt__variant_name__variant_type_id__).template get<0>());
ids::TypeId const variant_type_id = ((jakt__variant_name__variant_type_id__).template get<1>());

if (first){
(first = false);
}
else {
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}

if (((variant_name).has_value())){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(variant_name.value()));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(": "sv)));
}
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,TRY((((program)->type_name(variant_type_id,false)))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(")"sv)));
}
if (((number_constant).has_value())){
[](ByteString& self, ByteString rhs) -> void {
{
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
[](ByteString& self, ByteString rhs) -> void {
{
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
[](ByteString& self, ByteString rhs) -> void {
{
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
[](ByteString& self, ByteString rhs) -> void {
{
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

ErrorOr<ByteString> get_enum_variant_signature_from_type_id_and_name(NonnullRefPtr<types::CheckedProgram> const program,ids::TypeId const type_id,ByteString const name) {
{
NonnullRefPtr<types::Module> const mod = ((((program)->modules))[((((type_id).module)).id)]);
{
JaktInternal::ArrayIterator<types::CheckedEnum> _magic = ((((mod)->enums)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnum> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnum enum_ = (_magic_value.value());
{
if (((((enum_).type_id)).equals(type_id))){
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& v_name = __jakt_match_value.name;
{
if (((v_name) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const params = ide::enum_variant_fields(program,variant);
JaktInternal::Optional<types::NumberConstant> const none = JaktInternal::OptionalNone();
return TRY((ide::get_enum_variant_signature(program,name,type_id,params,none)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& v_name = __jakt_match_value.name;
{
if (((v_name) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const params = ide::enum_variant_fields(program,variant);
JaktInternal::Optional<types::NumberConstant> const none = JaktInternal::OptionalNone();
return TRY((ide::get_enum_variant_signature(program,name,type_id,params,none)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& v_name = __jakt_match_value.name;
{
if (((v_name) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const params = ide::enum_variant_fields(program,variant);
JaktInternal::Optional<types::NumberConstant> const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_923; {
__jakt_var_923 = ((expr)->to_number_constant(program)); goto __jakt_label_817;

}
__jakt_label_817:; __jakt_var_923.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_924; {
JaktInternal::Optional<types::NumberConstant> const none = JaktInternal::OptionalNone();
__jakt_var_924 = none; goto __jakt_label_818;

}
__jakt_label_818:; __jakt_var_924.release_value(); }));
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
return TRY((ide::get_enum_variant_signature(program,name,type_id,params,value)));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& v_name = __jakt_match_value.name;
{
if (((v_name) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const params = ide::enum_variant_fields(program,variant);
JaktInternal::Optional<types::NumberConstant> const none = JaktInternal::OptionalNone();
return TRY((ide::get_enum_variant_signature(program,name,type_id,params,none)));
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

ide::Usage get_enum_variant_usage_from_type_id_and_name(NonnullRefPtr<types::CheckedProgram> const program,ids::TypeId const type_id,ByteString const name) {
{
{
JaktInternal::ArrayIterator<types::CheckedEnum> _magic = ((((((program)->get_module(((type_id).module))))->enums)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedEnum> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedEnum enum_ = (_magic_value.value());
{
if ((!(((((enum_).type_id)).equals(type_id))))){
continue;
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
if (((((variant).name())) == (name))){
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> const variants = ide::enum_variant_fields(program,variant);
JaktInternal::Optional<types::NumberConstant> const number_constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, ide::Usage>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& name = __jakt_match_value.name;
NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
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
utility::Span const span = ((variant).span());
return ide::Usage::EnumVariant(span,name,type_id,variants,number_constant);
}
}

}
}

utility::panic((ByteString::from_utf8_without_validation("unreachable: should have found variant"sv)));
}

}
}

utility::panic((ByteString::from_utf8_without_validation("unreachable: should have found variant"sv)));
}
}

JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> enum_variant_fields(NonnullRefPtr<types::CheckedProgram> const program,types::CheckedEnumVariant const checked_enum_variant) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>>{
auto&& __jakt_match_variant = checked_enum_variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<ids::VarId> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>> __jakt_var_925; {
JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> output = DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>::create_with({});
{
JaktInternal::ArrayIterator<ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::VarId field = (_magic_value.value());
{
NonnullRefPtr<types::CheckedVariable> const variable = ((program)->get_variable(field));
JaktInternal::Optional<ByteString> const var_name = static_cast<JaktInternal::Optional<ByteString>>(((variable)->name));
JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId> const o = (Tuple{var_name, ((variable)->type_id)});
((output).push(o));
}

}
}

__jakt_var_925 = output; goto __jakt_label_819;

}
__jakt_label_819:; __jakt_var_925.release_value(); }));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>> __jakt_var_926; {
JaktInternal::Optional<ByteString> const string_none = JaktInternal::OptionalNone();
__jakt_var_926 = DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>::create_with({(Tuple{string_none, type_id})}); goto __jakt_label_820;

}
__jakt_label_820:; __jakt_var_926.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>>::create_with({}));
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

ErrorOr<ByteString> get_constructor_signature(NonnullRefPtr<types::CheckedProgram> const program,ids::FunctionId const function_id) {
{
NonnullRefPtr<types::CheckedFunction> const checked_function = ((program)->get_function(function_id));
ids::TypeId const type_id = ((checked_function)->return_type_id);
NonnullRefPtr<types::Module> const mod = ((((program)->modules))[((((type_id).module)).id)]);
{
JaktInternal::ArrayIterator<types::CheckedStruct> _magic = ((((mod)->structures)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedStruct> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedStruct struct_ = (_magic_value.value());
{
if (((((struct_).type_id)).equals(type_id))){
ByteString output = TRY((ide::get_type_signature(program,type_id)));
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("("sv)));
bool first = true;
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
if (first){
(first = false);
}
else {
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}

NonnullRefPtr<types::CheckedVariable> const variable = ((program)->get_variable(((field).variable_id)));
if (((variable)->is_mutable)){
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("mut "sv)));
}
[](ByteString& self, ByteString rhs) -> void {
{
(self = ((self) + (rhs)));
}
}
(output,__jakt_format((StringView::from_string_literal("{}: {}"sv)),((variable)->name),TRY((((program)->type_name(((variable)->type_id),false))))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {
{
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

ByteString ide::JaktSymbol::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("JaktSymbol("sv);{
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
ByteString ide::JaktSymbol::to_json() const {
{
ByteStringBuilder json_builder = ByteStringBuilder::create();
((json_builder).append((StringView::from_string_literal("{"sv))));
((json_builder).append(__jakt_format((StringView::from_string_literal("\"name\": \"{}\","sv)),((*this).name))));
if (((((*this).detail)).has_value())){
((json_builder).append(__jakt_format((StringView::from_string_literal("\"detail\": \"{}\","sv)),((*this).detail))));
}
((json_builder).append(__jakt_format((StringView::from_string_literal("\"kind\": \"{}\","sv)),((*this).kind))));
((json_builder).append(__jakt_format((StringView::from_string_literal("\"range\": {{\"start\": {}, \"end\": {}}},"sv)),((((*this).range)).start),((((*this).range)).end))));
((json_builder).append(__jakt_format((StringView::from_string_literal("\"selection_range\": {{\"start\": {}, \"end\": {}}},"sv)),((((*this).selection_range)).start),((((*this).selection_range)).end))));
JaktInternal::DynamicArray<ByteString> child_symbols = DynamicArray<ByteString>::create_with({});
((child_symbols).ensure_capacity(((((*this).children)).size())));
{
JaktInternal::ArrayIterator<ide::JaktSymbol> _magic = ((((*this).children)).iterator());
for (;;){
JaktInternal::Optional<ide::JaktSymbol> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ide::JaktSymbol child = (_magic_value.value());
{
((child_symbols).push(((child).to_json())));
}

}
}

((json_builder).append(__jakt_format((StringView::from_string_literal("\"children\": [{}]"sv)),utility::join(child_symbols,(ByteString::from_utf8_without_validation(","sv))))));
((json_builder).append((StringView::from_string_literal("}"sv))));
return ((json_builder).to_string());
}
}

ide::JaktSymbol::JaktSymbol(ByteString a_name, JaktInternal::Optional<ByteString> a_detail, ByteString a_kind, utility::Span a_range, utility::Span a_selection_range, JaktInternal::DynamicArray<ide::JaktSymbol> a_children): name(move(a_name)), detail(move(a_detail)), kind(move(a_kind)), range(move(a_range)), selection_range(move(a_selection_range)), children(move(a_children)){}

ByteString ide::Mutability::debug_description() const {
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
Mutability::~Mutability(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void Mutability::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* DoesNotApply */:break;
case 1 /* Immutable */:break;
case 2 /* Mutable */:break;
}
}
ByteString ide::VarType::debug_description() const {
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
VarType::~VarType(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void VarType::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Variable */:break;
case 1 /* Field */:break;
}
}
ByteString ide::VarVisibility::debug_description() const {
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
VarVisibility::~VarVisibility(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
void VarVisibility::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* DoesNotApply */:break;
case 1 /* Public */:break;
case 2 /* Private */:break;
case 3 /* Restricted */:break;
}
}
ByteString ide::Usage::debug_description() const {
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
[[nodiscard]] Usage Usage::Variable(utility::Span span, ByteString name, ids::TypeId type_id, ide::Mutability mutability, ide::VarType var_type, ide::VarVisibility visibility, JaktInternal::Optional<ids::TypeId> struct_type_id){
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
[[nodiscard]] Usage Usage::Call(ids::FunctionId value){
Usage __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Call.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Usage Usage::Typename(ids::TypeId value){
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
[[nodiscard]] Usage Usage::EnumVariant(utility::Span span, ByteString name, ids::TypeId type_id, JaktInternal::DynamicArray<JaktInternal::Tuple<JaktInternal::Optional<ByteString>,ids::TypeId>> variants, JaktInternal::Optional<types::NumberConstant> number_constant){
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
Usage::~Usage(){
if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant();
}
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
