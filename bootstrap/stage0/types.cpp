#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "types.h"
namespace Jakt {
namespace types {
Jakt::ids::TypeId unknown_type_id() {
{
return Jakt::types::builtin(Jakt::types::BuiltinType::Unknown());
}
}

Jakt::ids::TypeId void_type_id() {
{
return Jakt::types::builtin(Jakt::types::BuiltinType::Void());
}
}

Jakt::ids::TypeId never_type_id() {
{
return Jakt::types::builtin(Jakt::types::BuiltinType::Never());
}
}

Jakt::ids::TypeId builtin(Jakt::types::BuiltinType const builtin) {
{
return Jakt::ids::TypeId(Jakt::ids::ModuleId(static_cast<size_t>(0ULL)),builtin.id());
}
}

ErrorOr<ByteString> format_value_impl(ByteString const format_string,Jakt::types::Value const value,NonnullRefPtr<Jakt::types::CheckedProgram> const& program) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *value.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(ByteString::formatted(format_string,v));
};/*case end*/
case 0 /* Void */:return JaktInternal::ExplicitValue(ByteString::formatted(format_string,ByteString::from_utf8_without_validation("(void)"sv)));
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
Jakt::types::CheckedStruct const structure = program->get_struct(struct_id);
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::DynamicArray<ByteString> field_names = DynamicArray<ByteString>::create_with({});
builder.append(structure.name);
if (constructor.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const function = program->get_function(constructor.value());
builder.append(StringView::from_string_literal("::"sv));
builder.append(function->name);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter parameter = _magic_value.value();
{
field_names.push(parameter.variable->name);
}

}
}

}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = structure.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
field_names.push(program->get_variable(field->variable_id)->name);
}

}
}

}

builder.append_code_point(static_cast<u32>(U'('));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value field = _magic_value.value();
{
if (index > static_cast<size_t>(0ULL)){
builder.append(StringView::from_string_literal(", "sv));
}
builder.append(field_names.operator[](index));
builder.append(StringView::from_string_literal(": "sv));
builder.append(TRY((Jakt::types::format_value_impl(format_string,field,program))));
index += static_cast<size_t>(1ULL);
}

}
}

builder.append_code_point(static_cast<u32>(U')'));
return JaktInternal::ExplicitValue<ByteString>(builder.to_string());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
Jakt::types::CheckedStruct const structure = program->get_struct(struct_id);
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::DynamicArray<ByteString> field_names = DynamicArray<ByteString>::create_with({});
builder.append(structure.name);
if (constructor.has_value()){
NonnullRefPtr<Jakt::types::CheckedFunction> const function = program->get_function(constructor.value());
builder.append(StringView::from_string_literal("::"sv));
builder.append(function->name);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter parameter = _magic_value.value();
{
field_names.push(parameter.variable->name);
}

}
}

}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = structure.fields.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = _magic_value.value();
{
field_names.push(program->get_variable(field->variable_id)->name);
}

}
}

}

builder.append_code_point(static_cast<u32>(U'('));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value field = _magic_value.value();
{
if (index > static_cast<size_t>(0ULL)){
builder.append(StringView::from_string_literal(", "sv));
}
builder.append(field_names.operator[](index));
builder.append(StringView::from_string_literal(": "sv));
builder.append(TRY((Jakt::types::format_value_impl(format_string,field,program))));
index += static_cast<size_t>(1ULL);
}

}
}

builder.append_code_point(static_cast<u32>(U')'));
return JaktInternal::ExplicitValue<ByteString>(builder.to_string());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
Jakt::ids::FunctionId const& constructor = __jakt_match_value.constructor;
{
Jakt::types::CheckedEnum const enum_ = program->get_enum(enum_id);
NonnullRefPtr<Jakt::types::CheckedFunction> const function = program->get_function(constructor);
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::DynamicArray<ByteString> field_names = DynamicArray<ByteString>::create_with({});
builder.append(enum_.name);
builder.append(StringView::from_string_literal("::"sv));
builder.append(function->name);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = function->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter parameter = _magic_value.value();
{
field_names.push(parameter.variable->name);
}

}
}

builder.append_code_point(static_cast<u32>(U'('));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value field = _magic_value.value();
{
if (index > static_cast<size_t>(0ULL)){
builder.append(StringView::from_string_literal(", "sv));
}
builder.append(field_names.operator[](index));
builder.append(StringView::from_string_literal(": "sv));
builder.append(TRY((Jakt::types::format_value_impl(format_string,field,program))));
index += static_cast<size_t>(1ULL);
}

}
}

builder.append_code_point(static_cast<u32>(U')'));
return JaktInternal::ExplicitValue<ByteString>(builder.to_string());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::types::format_value_impl(__jakt_format(StringView::from_string_literal("Some({})"sv),format_string),value,program))));
};/*case end*/
case 25 /* OptionalNone */:return JaktInternal::ExplicitValue(ByteString::formatted(format_string,ByteString::from_utf8_without_validation("None"sv)));
case 26 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
{
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *value.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* JaktTuple */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')});
case 20 /* JaktArray */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')});
case 22 /* JaktSet */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'{'), static_cast<u32>(U'}')});
default:{
Jakt::abort();
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
builder.append_code_point(surrounding.template get<0>());
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value field = _magic_value.value();
{
if (index > static_cast<size_t>(0ULL)){
builder.append(StringView::from_string_literal(", "sv));
}
builder.append(TRY((Jakt::types::format_value_impl(format_string,field,program))));
index += static_cast<size_t>(1ULL);
}

}
}

builder.append_code_point(surrounding.template get<1>());
return JaktInternal::ExplicitValue<ByteString>(builder.to_string());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.values;
{
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *value.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* JaktTuple */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')});
case 20 /* JaktArray */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')});
case 22 /* JaktSet */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'{'), static_cast<u32>(U'}')});
default:{
Jakt::abort();
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
builder.append_code_point(surrounding.template get<0>());
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value field = _magic_value.value();
{
if (index > static_cast<size_t>(0ULL)){
builder.append(StringView::from_string_literal(", "sv));
}
builder.append(TRY((Jakt::types::format_value_impl(format_string,field,program))));
index += static_cast<size_t>(1ULL);
}

}
}

builder.append_code_point(surrounding.template get<1>());
return JaktInternal::ExplicitValue<ByteString>(builder.to_string());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.values;
{
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *value.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* JaktTuple */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')});
case 20 /* JaktArray */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')});
case 22 /* JaktSet */:return JaktInternal::ExplicitValue(Tuple{static_cast<u32>(U'{'), static_cast<u32>(U'}')});
default:{
Jakt::abort();
}
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
builder.append_code_point(surrounding.template get<0>());
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value field = _magic_value.value();
{
if (index > static_cast<size_t>(0ULL)){
builder.append(StringView::from_string_literal(", "sv));
}
builder.append(TRY((Jakt::types::format_value_impl(format_string,field,program))));
index += static_cast<size_t>(1ULL);
}

}
}

builder.append_code_point(surrounding.template get<1>());
return JaktInternal::ExplicitValue<ByteString>(builder.to_string());
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
ByteStringBuilder builder = ByteStringBuilder::create();
builder.append_code_point(static_cast<u32>(U'['));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = keys.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value key = _magic_value.value();
{
if (index > static_cast<size_t>(0ULL)){
builder.append(StringView::from_string_literal(", "sv));
}
builder.append(TRY((Jakt::types::format_value_impl(format_string,key,program))));
builder.append(StringView::from_string_literal(": "sv));
builder.append(TRY((Jakt::types::format_value_impl(format_string,values.operator[](index),program))));
index += static_cast<size_t>(1ULL);
}

}
}

builder.append_code_point(static_cast<u32>(U']'));
return JaktInternal::ExplicitValue<ByteString>(builder.to_string());
}
VERIFY_NOT_REACHED();
};/*case end*/
default:{
warnln(StringView::from_string_literal("Cannot format value {}"sv),value.impl);
return Error::__jakt_from_string_literal(StringView::from_string_literal("Cannot format value of this type"sv));
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

ErrorOr<ByteString> comptime_format_impl(ByteString const format_string,JaktInternal::ArraySlice<Jakt::types::Value> const arguments,NonnullRefPtr<Jakt::types::CheckedProgram> const& program) {
{
ByteStringBuilder builder = ByteStringBuilder::create();
size_t current_argument_index = static_cast<size_t>(0ULL);
ByteStringBuilder format_field_builder = ByteStringBuilder::create();
JaktInternal::Optional<size_t> index_in_field = JaktInternal::OptionalNone();
bool expect_close_brace = false;
Function<JaktInternal::Tuple<JaktInternal::Optional<size_t>,ByteString>(ByteString)> const argument_and_index = [](ByteString str) -> JaktInternal::Tuple<JaktInternal::Optional<size_t>,ByteString> {{
size_t slice_end = static_cast<size_t>(0ULL);
bool has_index = false;
{
DeprecatedStringCodePointIterator _magic = str.code_points();
for (;;){
JaktInternal::Optional<u32> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
u32 code_point = _magic_value.value();
{
if ((code_point >= static_cast<u32>(U'0')) && (code_point <= static_cast<u32>(U'9'))){
slice_end += static_cast<size_t>(1ULL);
has_index = true;
}
else {
break;
}

}

}
}

if (has_index){
ByteString const index_str = str.substring(static_cast<size_t>(0ULL),slice_end);
JaktInternal::Optional<u32> const index = index_str.template to_number<u32>();
if (index.has_value()){
return Tuple{static_cast<JaktInternal::Optional<size_t>>(infallible_integer_cast<size_t>(index.value())), str.substring(slice_end,JaktInternal::checked_sub(str.length(),slice_end))};
}
}
return Tuple{static_cast<JaktInternal::Optional<size_t>>(JaktInternal::OptionalNone()), str};
}
}
;
{
DeprecatedStringCodePointIterator _magic = format_string.code_points();
for (;;){
JaktInternal::Optional<u32> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
u32 code_point = _magic_value.value();
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<ByteString>> {
auto __jakt_enum_value = (code_point);
if (__jakt_enum_value == static_cast<u32>(U'{')) {{
if (index_in_field.has_value() && (index_in_field.value() == static_cast<size_t>(0ULL))){
builder.append_code_point(static_cast<u32>(U'{'));
index_in_field = JaktInternal::OptionalNone();
}
else if (index_in_field.has_value()){
format_field_builder.append_code_point(static_cast<u32>(U'{'));
index_in_field = JaktInternal::checked_add(index_in_field.value(),static_cast<size_t>(1ULL));
}
else {
index_in_field = static_cast<size_t>(0ULL);
}

}
return JaktInternal::ExplicitValue<void>();
}else if (__jakt_enum_value == static_cast<u32>(U'}')) {{
if (expect_close_brace){
builder.append_code_point(static_cast<u32>(U'}'));
expect_close_brace = false;
}
else if (!index_in_field.has_value()){
expect_close_brace = true;
}
else {
index_in_field = JaktInternal::OptionalNone();
ByteString const fmt_string = format_field_builder.to_string();
format_field_builder.clear();
JaktInternal::Tuple<JaktInternal::Optional<size_t>,ByteString> const index_format_string_ = argument_and_index(fmt_string);
JaktInternal::Optional<size_t> const index = index_format_string_.template get<0>();
ByteString const format_string = index_format_string_.template get<1>();

size_t const effective_index = index.value_or_lazy_evaluated([&] { return current_argument_index++; });
if (effective_index >= arguments.size()){
return Error::__jakt_from_string_literal(StringView::from_string_literal("Not enough arguments for format string"sv));
}
ByteString const effective_format_string = __jakt_format(StringView::from_string_literal("{{{}}}"sv),format_string);
builder.append(TRY((Jakt::types::format_value_impl(effective_format_string,arguments.operator[](effective_index),program))));
}

}
return JaktInternal::ExplicitValue<void>();
}else {{
if (index_in_field.has_value()){
format_field_builder.append_code_point(code_point);
}
else {
builder.append_code_point(code_point);
}

}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
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

return builder.to_string();
}
}

ByteString Jakt::types::GenericInferences::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("GenericInferences("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}", values);
}
builder.append(")"sv);return builder.to_string(); }
void Jakt::types::GenericInferences::set(Jakt::ids::TypeId const key,Jakt::ids::TypeId const value) {
{
if (key.equals(value)){
return;
}
Jakt::ids::TypeId const mapped_value = this->map(value);
if (key.equals(mapped_value)){
return;
}
this->values.set(key, mapped_value);
}
}

void Jakt::types::GenericInferences::set_all(JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const keys,JaktInternal::DynamicArray<Jakt::ids::TypeId> const values) {
{
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(keys.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (i >= values.size()){
break;
}
Jakt::ids::TypeId const key = keys.operator[](i).type_id;
Jakt::ids::TypeId const value = values.operator[](i);
this->set(key,value);
}

}
}

}
}

JaktInternal::Optional<Jakt::ids::TypeId> Jakt::types::GenericInferences::get(Jakt::ids::TypeId const key) const {
{
return this->values.get(key);
}
}

Jakt::ids::TypeId Jakt::types::GenericInferences::map(Jakt::ids::TypeId const type) const {
{
JaktInternal::Optional<Jakt::ids::TypeId> mapped = this->values.get(type);
JaktInternal::Optional<Jakt::ids::TypeId> final_mapped_result = mapped;
while (mapped.has_value()){
final_mapped_result = mapped;
mapped = this->values.get(mapped.value());
}
return final_mapped_result.value_or_lazy_evaluated([&] { return type; });
}
}

ErrorOr<JaktInternal::DynamicArray<Jakt::ids::TypeId>> Jakt::types::GenericInferences::map(JaktInternal::DynamicArray<Jakt::ids::TypeId> const types) const {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> result = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = types.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId type = _magic_value.value();
{
JaktInternal::Optional<Jakt::ids::TypeId> mapped = this->values.get(type);
JaktInternal::Optional<Jakt::ids::TypeId> final_mapped_result = mapped;
while (mapped.has_value()){
final_mapped_result = mapped;
mapped = this->values.get(mapped.value());
}
result.push(final_mapped_result.value_or_lazy_evaluated([&] { return type; }));
}

}
}

return result;
}
}

JaktInternal::Optional<Jakt::ids::TypeId> Jakt::types::GenericInferences::find_and_map(ByteString const name,NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const {
{
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,Jakt::ids::TypeId> _magic = this->values.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> type_id__v__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> const jakt__type_id__v__ = type_id__v__;
Jakt::ids::TypeId const type_id = jakt__type_id__v__.template get<0>();
Jakt::ids::TypeId const v = jakt__type_id__v__.template get<1>();

NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp44 = program->get_type(type_id);
if (__jakt_tmp44->__jakt_init_index() == 18 /* TypeVariable */){
ByteString const var_name = __jakt_tmp44->as.TypeVariable.name;
if (var_name == name){
return this->map(v);
}
}
}

}
}

return JaktInternal::OptionalNone();
}
}

JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> Jakt::types::GenericInferences::iterator() const {
{
return this->values;
}
}

JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> Jakt::types::GenericInferences::perform_checkpoint(bool const reset) {
{
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const result = this->values;
this->values = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
if (!reset){
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,Jakt::ids::TypeId> _magic = result.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> key__value__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> const jakt__key__value__ = key__value__;
Jakt::ids::TypeId const key = jakt__key__value__.template get<0>();
Jakt::ids::TypeId const value = jakt__key__value__.template get<1>();

this->values.set(key, value);
}

}
}

}
return result;
}
}

void Jakt::types::GenericInferences::restore(JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint) {
{
this->values = checkpoint;
}
}

void Jakt::types::GenericInferences::set_from(JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const checkpoint) {
{
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,Jakt::ids::TypeId> _magic = checkpoint.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> key__value__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> const jakt__key__value__ = key__value__;
Jakt::ids::TypeId const key = jakt__key__value__.template get<0>();
Jakt::ids::TypeId const value = jakt__key__value__.template get<1>();

this->set(key,value);
}

}
}

}
}

ErrorOr<void> Jakt::types::GenericInferences::debug_description(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const {
{
warnln(StringView::from_string_literal("Generic inferences:"sv));
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,Jakt::ids::TypeId> _magic = this->values.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> key__value__ = _magic_value.value();
{
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> const jakt__key__value__ = key__value__;
Jakt::ids::TypeId const key = jakt__key__value__.template get<0>();
Jakt::ids::TypeId const value = jakt__key__value__.template get<1>();

warnln(StringView::from_string_literal("  {} => {}"sv),TRY((program->type_name(key,true))),TRY((program->type_name(value,true))));
}

}
}

}
return {};
}

Jakt::types::GenericInferences::GenericInferences(JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> a_values): values(move(a_values)){}

ByteString Jakt::types::SpecializedType::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("SpecializedType("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("base_type_id: {}, ", base_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arguments: {}, ", arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", type_id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::SpecializedType::SpecializedType(Jakt::ids::TypeId a_base_type_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> a_arguments, Jakt::ids::TypeId a_type_id): base_type_id(move(a_base_type_id)), arguments(move(a_arguments)), type_id(move(a_type_id)){}

ByteString Jakt::types::ResolutionMixin::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ResolutionMixin("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}, ", scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_vars: {}, ", mixin_vars);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_bindings: {}, ", mixin_bindings);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_structs: {}, ", mixin_structs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_functions: {}, ", mixin_functions);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_enums: {}, ", mixin_enums);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_types: {}, ", mixin_types);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_traits: {}, ", mixin_traits);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_imports: {}, ", mixin_imports);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("mixin_aliases: {}", mixin_aliases);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::ResolutionMixin::ResolutionMixin(Jakt::ids::ScopeId a_scope_id, bool a_mixin_vars, bool a_mixin_bindings, bool a_mixin_structs, bool a_mixin_functions, bool a_mixin_enums, bool a_mixin_types, bool a_mixin_traits, bool a_mixin_imports, bool a_mixin_aliases): scope_id(move(a_scope_id)), mixin_vars(move(a_mixin_vars)), mixin_bindings(move(a_mixin_bindings)), mixin_structs(move(a_mixin_structs)), mixin_functions(move(a_mixin_functions)), mixin_enums(move(a_mixin_enums)), mixin_types(move(a_mixin_types)), mixin_traits(move(a_mixin_traits)), mixin_imports(move(a_mixin_imports)), mixin_aliases(move(a_mixin_aliases)){}

ByteString Jakt::types::Scope::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Scope("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parent: {}, ", parent);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("debug_name: \"{}\", ", debug_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_block_scope: {}, ", is_block_scope);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_from_generated_code: {}, ", is_from_generated_code);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespace_name: {}, ", namespace_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module_namespace_name: {}, ", module_namespace_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}, ", external_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("vars: {}, ", vars);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("comptime_bindings: {}, ", comptime_bindings);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("structs: {}, ", structs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("functions: {}, ", functions);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enums: {}, ", enums);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("types: {}, ", types);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("traits: {}, ", traits);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("imports: {}, ", imports);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("aliases: {}, ", aliases);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("alias_scope: {}, ", alias_scope);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("children: {}, ", children);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("import_path_if_extern: {}, ", import_path_if_extern);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("alias_path: {}, ", alias_path);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("after_extern_include: {}, ", after_extern_include);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("before_extern_include: {}, ", before_extern_include);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("resolution_mixins: {}, ", resolution_mixins);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("relevant_type_id: {}, ", relevant_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("resolved_forall_chunks: {}, ", resolved_forall_chunks);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("explicitly_specialized_types: {}", explicitly_specialized_types);
}
builder.append(")"sv);return builder.to_string(); }
JaktInternal::Optional<Jakt::parser::ExternalName> Jakt::types::Scope::namespace_name_for_codegen() const {
{
if (this->external_name.has_value()){
return this->external_name;
}
if (this->namespace_name.has_value()){
return Jakt::parser::ExternalName::Plain(this->namespace_name.value());
}
if (this->module_namespace_name.has_value()){
return Jakt::parser::ExternalName::Plain(this->module_namespace_name.value());
}
return JaktInternal::OptionalNone();
}
}

Jakt::types::Scope::Scope(JaktInternal::Optional<Jakt::ids::ScopeId> a_parent, bool a_can_throw, ByteString a_debug_name, bool a_is_block_scope, bool a_is_from_generated_code, JaktInternal::Optional<ByteString> a_namespace_name, JaktInternal::Optional<ByteString> a_module_namespace_name, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Dictionary<ByteString,Jakt::ids::VarId> a_vars, JaktInternal::Dictionary<ByteString,Jakt::types::Value> a_comptime_bindings, JaktInternal::Dictionary<ByteString,Jakt::ids::StructId> a_structs, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> a_functions, JaktInternal::Dictionary<ByteString,Jakt::ids::EnumId> a_enums, JaktInternal::Dictionary<ByteString,Jakt::ids::TypeId> a_types, JaktInternal::Dictionary<ByteString,Jakt::ids::TraitId> a_traits, JaktInternal::Dictionary<ByteString,Jakt::ids::ModuleId> a_imports, JaktInternal::Dictionary<ByteString,Jakt::ids::ScopeId> a_aliases, JaktInternal::Optional<Jakt::ids::ScopeId> a_alias_scope, JaktInternal::DynamicArray<Jakt::ids::ScopeId> a_children, JaktInternal::Optional<ByteString> a_import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>> a_alias_path, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> a_after_extern_include, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> a_before_extern_include, JaktInternal::DynamicArray<Jakt::types::ResolutionMixin> a_resolution_mixins, JaktInternal::Optional<Jakt::ids::TypeId> a_relevant_type_id, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> a_resolved_forall_chunks, JaktInternal::Dictionary<ByteString,Jakt::types::SpecializedType> a_explicitly_specialized_types): parent(move(a_parent)), can_throw(move(a_can_throw)), debug_name(move(a_debug_name)), is_block_scope(move(a_is_block_scope)), is_from_generated_code(move(a_is_from_generated_code)), namespace_name(move(a_namespace_name)), module_namespace_name(move(a_module_namespace_name)), external_name(move(a_external_name)), vars(move(a_vars)), comptime_bindings(move(a_comptime_bindings)), structs(move(a_structs)), functions(move(a_functions)), enums(move(a_enums)), types(move(a_types)), traits(move(a_traits)), imports(move(a_imports)), aliases(move(a_aliases)), alias_scope(move(a_alias_scope)), children(move(a_children)), import_path_if_extern(move(a_import_path_if_extern)), alias_path(move(a_alias_path)), after_extern_include(move(a_after_extern_include)), before_extern_include(move(a_before_extern_include)), resolution_mixins(move(a_resolution_mixins)), relevant_type_id(move(a_relevant_type_id)), resolved_forall_chunks(move(a_resolved_forall_chunks)), explicitly_specialized_types(move(a_explicitly_specialized_types)){}
NonnullRefPtr<Scope> Jakt::types::Scope::__jakt_create(JaktInternal::Optional<Jakt::ids::ScopeId> parent, bool can_throw, ByteString debug_name, bool is_block_scope, bool is_from_generated_code, JaktInternal::Optional<ByteString> namespace_name, JaktInternal::Optional<ByteString> module_namespace_name, JaktInternal::Optional<Jakt::parser::ExternalName> external_name, JaktInternal::Dictionary<ByteString,Jakt::ids::VarId> vars, JaktInternal::Dictionary<ByteString,Jakt::types::Value> comptime_bindings, JaktInternal::Dictionary<ByteString,Jakt::ids::StructId> structs, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> functions, JaktInternal::Dictionary<ByteString,Jakt::ids::EnumId> enums, JaktInternal::Dictionary<ByteString,Jakt::ids::TypeId> types, JaktInternal::Dictionary<ByteString,Jakt::ids::TraitId> traits, JaktInternal::Dictionary<ByteString,Jakt::ids::ModuleId> imports, JaktInternal::Dictionary<ByteString,Jakt::ids::ScopeId> aliases, JaktInternal::Optional<Jakt::ids::ScopeId> alias_scope, JaktInternal::DynamicArray<Jakt::ids::ScopeId> children, JaktInternal::Optional<ByteString> import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>> alias_path, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> after_extern_include, JaktInternal::DynamicArray<Jakt::parser::IncludeAction> before_extern_include, JaktInternal::DynamicArray<Jakt::types::ResolutionMixin> resolution_mixins, JaktInternal::Optional<Jakt::ids::TypeId> relevant_type_id, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedForallChunk>> resolved_forall_chunks, JaktInternal::Dictionary<ByteString,Jakt::types::SpecializedType> explicitly_specialized_types) { auto o = adopt_ref(*new Scope (move(parent), move(can_throw), move(debug_name), move(is_block_scope), move(is_from_generated_code), move(namespace_name), move(module_namespace_name), move(external_name), move(vars), move(comptime_bindings), move(structs), move(functions), move(enums), move(types), move(traits), move(imports), move(aliases), move(alias_scope), move(children), move(import_path_if_extern), move(alias_path), move(after_extern_include), move(before_extern_include), move(resolution_mixins), move(relevant_type_id), move(resolved_forall_chunks), move(explicitly_specialized_types))); return o; }
ByteString Jakt::types::ResolvedForallChunk::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ResolvedForallChunk("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parameters: {}, ", parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parsed_namespace: {}, ", parsed_namespace);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generated_scopes: {}", generated_scopes);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::ResolvedForallChunk::ResolvedForallChunk(JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::utility::Span,Jakt::ids::TypeId>>> a_parameters, Jakt::parser::ParsedNamespace a_parsed_namespace, JaktInternal::DynamicArray<Jakt::ids::ScopeId> a_generated_scopes): parameters(move(a_parameters)), parsed_namespace(move(a_parsed_namespace)), generated_scopes(move(a_generated_scopes)){}

ByteString Jakt::types::Module::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Module("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}, ", id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("types: {}, ", types);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("resolved_import_path: \"{}\", ", resolved_import_path);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_root: {}, ", is_root);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("functions: {}, ", functions);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("structures: {}, ", structures);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enums: {}, ", enums);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scopes: {}, ", scopes);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("traits: {}, ", traits);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variables: {}, ", variables);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("imports: {}, ", imports);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("builtin_implementation_structs: {}", builtin_implementation_structs);
}
builder.append(")"sv);return builder.to_string(); }
bool Jakt::types::Module::is_prelude() const {
{
return this->id.id == static_cast<size_t>(0ULL);
}
}

Jakt::ids::TypeId Jakt::types::Module::new_type_variable(JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const implemented_traits) {
{
size_t const new_id = this->types.size();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const empty_implementation = DynamicArray<Jakt::ids::TypeId>::create_with({});
JaktInternal::DynamicArray<Jakt::ids::TypeId> const trait_implementations = implemented_traits.value_or_lazy_evaluated([&] { return empty_implementation; });
this->types.push(Jakt::types::Type::TypeVariable(Jakt::parser::CheckedQualifiers(false),__jakt_format(StringView::from_string_literal("T{}"sv),new_id),trait_implementations,false));
return Jakt::ids::TypeId(this->id,new_id);
}
}

Jakt::ids::FunctionId Jakt::types::Module::next_function_id() const {
{
return Jakt::ids::FunctionId(this->id,this->functions.size());
}
}

Jakt::ids::FunctionId Jakt::types::Module::add_function(NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function) {
{
Jakt::ids::FunctionId const new_id = this->next_function_id();
this->functions.push(checked_function);
return new_id;
}
}

Jakt::ids::VarId Jakt::types::Module::add_variable(NonnullRefPtr<Jakt::types::CheckedVariable> const checked_variable) {
{
size_t const new_id = this->variables.size();
this->variables.push(checked_variable);
return Jakt::ids::VarId(this->id,new_id);
}
}

Jakt::types::Module::Module(Jakt::ids::ModuleId a_id, ByteString a_name, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::Type>> a_types, ByteString a_resolved_import_path, bool a_is_root, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>> a_functions, JaktInternal::DynamicArray<Jakt::types::CheckedStruct> a_structures, JaktInternal::DynamicArray<Jakt::types::CheckedEnum> a_enums, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Scope>> a_scopes, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedTrait>> a_traits, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>> a_variables, JaktInternal::DynamicArray<Jakt::ids::ModuleId> a_imports, JaktInternal::Dictionary<size_t,Jakt::ids::StructId> a_builtin_implementation_structs): id(move(a_id)), name(move(a_name)), types(move(a_types)), resolved_import_path(move(a_resolved_import_path)), is_root(move(a_is_root)), functions(move(a_functions)), structures(move(a_structures)), enums(move(a_enums)), scopes(move(a_scopes)), traits(move(a_traits)), variables(move(a_variables)), imports(move(a_imports)), builtin_implementation_structs(move(a_builtin_implementation_structs)){}
NonnullRefPtr<Module> Jakt::types::Module::__jakt_create(Jakt::ids::ModuleId id, ByteString name, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::Type>> types, ByteString resolved_import_path, bool is_root, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>> functions, JaktInternal::DynamicArray<Jakt::types::CheckedStruct> structures, JaktInternal::DynamicArray<Jakt::types::CheckedEnum> enums, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Scope>> scopes, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedTrait>> traits, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>> variables, JaktInternal::DynamicArray<Jakt::ids::ModuleId> imports, JaktInternal::Dictionary<size_t,Jakt::ids::StructId> builtin_implementation_structs) { auto o = adopt_ref(*new Module (move(id), move(name), move(types), move(resolved_import_path), move(is_root), move(functions), move(structures), move(enums), move(scopes), move(traits), move(variables), move(imports), move(builtin_implementation_structs))); return o; }
ByteString Jakt::types::CheckedTrait::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedTrait("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("requirements: {}, ", requirements);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}, ", generic_parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}", scope_id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedTrait::CheckedTrait(ByteString a_name, Jakt::utility::Span a_name_span, Jakt::types::CheckedTraitRequirements a_requirements, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> a_generic_parameters, Jakt::ids::ScopeId a_scope_id): name(move(a_name)), name_span(move(a_name_span)), requirements(move(a_requirements)), generic_parameters(move(a_generic_parameters)), scope_id(move(a_scope_id)){}
NonnullRefPtr<CheckedTrait> Jakt::types::CheckedTrait::__jakt_create(ByteString name, Jakt::utility::Span name_span, Jakt::types::CheckedTraitRequirements requirements, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> generic_parameters, Jakt::ids::ScopeId scope_id) { auto o = adopt_ref(*new CheckedTrait (move(name), move(name_span), move(requirements), move(generic_parameters), move(scope_id))); return o; }
ByteString Jakt::types::LoadedModule::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("LoadedModule("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module_id: {}, ", module_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("file_id: {}", file_id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::LoadedModule::LoadedModule(Jakt::ids::ModuleId a_module_id, Jakt::utility::FileId a_file_id): module_id(move(a_module_id)), file_id(move(a_file_id)){}

ByteString Jakt::types::CheckedNamespace::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedNamespace("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope: {}", scope);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedNamespace::CheckedNamespace(ByteString a_name, Jakt::ids::ScopeId a_scope): name(move(a_name)), scope(move(a_scope)){}

ByteString Jakt::types::CheckedFunction::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedFunction("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("visibility: {}, ", visibility);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type_id: {}, ", return_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type_span: {}, ", return_type_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generics: {}, ", *generics);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type: {}, ", type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("linkage: {}, ", linkage);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("function_scope_id: {}, ", function_scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("struct_id: {}, ", struct_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_instantiated: {}, ", is_instantiated);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parsed_function: {}, ", parsed_function);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_comptime: {}, ", is_comptime);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_virtual: {}, ", is_virtual);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_override: {}, ", is_override);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_unsafe: {}, ", is_unsafe);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("has_varargs: {}, ", has_varargs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("specialization_index: {}, ", specialization_index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("owner_scope: {}, ", owner_scope);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("owner_scope_generics: {}, ", owner_scope_generics);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_fully_checked: {}, ", is_fully_checked);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}, ", external_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("deprecated_message: {}, ", deprecated_message);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("stores_arguments: {}, ", stores_arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("force_inline: {}, ", force_inline);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_raw_constructor: {}", is_raw_constructor);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::parser::ExternalName Jakt::types::CheckedFunction::name_for_codegen() const {
{
return this->external_name.value_or_lazy_evaluated([&] { return Jakt::parser::ExternalName::Plain(this->name); });
}
}

ErrorOr<void> Jakt::types::CheckedFunction::map_types(Function<ErrorOr<Jakt::ids::TypeId>(Jakt::ids::TypeId)> const& map) {
{
this->return_type_id = TRY((map(this->return_type_id)));
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> changed_params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = this->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedParameter param = _magic_value.value();
{
changed_params.push(TRY((param.map_types(map))));
}

}
}

this->params = changed_params;
}
return {};
}

NonnullRefPtr<Jakt::types::CheckedFunction> Jakt::types::CheckedFunction::copy() const {
{
return Jakt::types::CheckedFunction::__jakt_create(this->name,this->name_span,this->visibility,this->return_type_id,this->return_type_span,this->params,this->generics,this->block,this->can_throw,this->type,this->linkage,this->function_scope_id,this->struct_id,this->is_instantiated,this->parsed_function,this->is_comptime,this->is_virtual,this->is_override,this->is_unsafe,this->has_varargs,this->specialization_index,this->owner_scope,this->owner_scope_generics,this->is_fully_checked,this->external_name,this->deprecated_message,this->stores_arguments,Jakt::parser::InlineState::Default(),false);
}
}

bool Jakt::types::CheckedFunction::signature_matches(NonnullRefPtr<Jakt::types::CheckedFunction> const other,bool const ignore_this) const {
{
if ((([](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(this->name,other->name) || (this->can_throw != other->can_throw)) || (this->is_comptime != other->is_comptime)) || (this->has_varargs != other->has_varargs)){
return false;
}
if (this->params.size() != other->params.size()){
return false;
}
if (this->generics->params.size() != other->generics->params.size()){
return false;
}
JaktInternal::Set<Jakt::ids::TypeId> lhs_generic_type_ids = Set<Jakt::ids::TypeId>::create_with_values({});
JaktInternal::Set<Jakt::ids::TypeId> rhs_generic_type_ids = Set<Jakt::ids::TypeId>::create_with_values({});
{
JaktInternal::ArrayIterator<Jakt::types::FunctionGenericParameter> _magic = this->generics->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::FunctionGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::FunctionGenericParameter param = _magic_value.value();
{
Jakt::ids::TypeId const type_id = param.type_id();
lhs_generic_type_ids.add(type_id);
}

}
}

{
JaktInternal::ArrayIterator<Jakt::types::FunctionGenericParameter> _magic = other->generics->params.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::FunctionGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::FunctionGenericParameter param = _magic_value.value();
{
Jakt::ids::TypeId const type_id = param.type_id();
rhs_generic_type_ids.add(type_id);
}

}
}

{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(this->params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t param_index = _magic_value.value();
{
Jakt::types::CheckedParameter const lhs_param = this->params.operator[](param_index);
Jakt::types::CheckedParameter const rhs_param = other->params.operator[](param_index);
Jakt::ids::TypeId const lhs_param_id = lhs_param.variable->type_id;
Jakt::ids::TypeId const rhs_param_id = rhs_param.variable->type_id;
if ((!lhs_param.variable->type_id.equals(rhs_param.variable->type_id)) && (!(lhs_generic_type_ids.contains(lhs_param_id) && rhs_generic_type_ids.contains(rhs_param_id)))){
return false;
}
}

}
}

return true;
}
}

bool Jakt::types::CheckedFunction::is_static() const {
{
if (this->params.size() < static_cast<size_t>(1ULL)){
return true;
}
return [](ByteString const& self, ByteString rhs) -> bool {{
return !(self == rhs);
}
}
(this->params.operator[](static_cast<i64>(0LL)).variable->name,ByteString::from_utf8_without_validation("this"sv));
}
}

bool Jakt::types::CheckedFunction::is_mutating() const {
{
if (this->params.size() < static_cast<size_t>(1ULL)){
return false;
}
NonnullRefPtr<Jakt::types::CheckedVariable> const first_param_variable = this->params.operator[](static_cast<i64>(0LL)).variable;
return (first_param_variable->name == ByteString::from_utf8_without_validation("this"sv)) && first_param_variable->is_mutable;
}
}

void Jakt::types::CheckedFunction::add_param(Jakt::types::CheckedParameter const checked_param) {
{
this->params.push(checked_param);
this->generics->base_params.push(checked_param);
}
}

void Jakt::types::CheckedFunction::set_params(JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const checked_params) {
{
this->params = checked_params;
this->generics->base_params = checked_params;
}
}

bool Jakt::types::CheckedFunction::is_specialized_for_types(JaktInternal::DynamicArray<Jakt::ids::TypeId> const types) const {
{
return this->generics->is_specialized_for_types(types);
}
}

Jakt::parser::ParsedFunction Jakt::types::CheckedFunction::to_parsed_function() const {
{
if (!this->parsed_function.has_value()){
Jakt::utility::panic(ByteString::from_utf8_without_validation("to_parsed_function() called on a synthetic function"sv));
}
return this->parsed_function.value();
}
}

Jakt::types::CheckedFunction::CheckedFunction(ByteString a_name, Jakt::utility::Span a_name_span, Jakt::types::CheckedVisibility a_visibility, Jakt::ids::TypeId a_return_type_id, JaktInternal::Optional<Jakt::utility::Span> a_return_type_span, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> a_params, NonnullRefPtr<Jakt::types::FunctionGenerics> a_generics, Jakt::types::CheckedBlock a_block, bool a_can_throw, Jakt::parser::FunctionType a_type, Jakt::parser::FunctionLinkage a_linkage, Jakt::ids::ScopeId a_function_scope_id, JaktInternal::Optional<Jakt::ids::StructId> a_struct_id, bool a_is_instantiated, JaktInternal::Optional<Jakt::parser::ParsedFunction> a_parsed_function, bool a_is_comptime, bool a_is_virtual, bool a_is_override, bool a_is_unsafe, bool a_has_varargs, JaktInternal::Optional<size_t> a_specialization_index, JaktInternal::Optional<Jakt::ids::ScopeId> a_owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> a_owner_scope_generics, bool a_is_fully_checked, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Optional<ByteString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>>> a_stores_arguments, Jakt::parser::InlineState a_force_inline, bool a_is_raw_constructor): name(move(a_name)), name_span(move(a_name_span)), visibility(move(a_visibility)), return_type_id(move(a_return_type_id)), return_type_span(move(a_return_type_span)), params(move(a_params)), generics(move(a_generics)), block(move(a_block)), can_throw(move(a_can_throw)), type(move(a_type)), linkage(move(a_linkage)), function_scope_id(move(a_function_scope_id)), struct_id(move(a_struct_id)), is_instantiated(move(a_is_instantiated)), parsed_function(move(a_parsed_function)), is_comptime(move(a_is_comptime)), is_virtual(move(a_is_virtual)), is_override(move(a_is_override)), is_unsafe(move(a_is_unsafe)), has_varargs(move(a_has_varargs)), specialization_index(move(a_specialization_index)), owner_scope(move(a_owner_scope)), owner_scope_generics(move(a_owner_scope_generics)), is_fully_checked(move(a_is_fully_checked)), external_name(move(a_external_name)), deprecated_message(move(a_deprecated_message)), stores_arguments(move(a_stores_arguments)), force_inline(move(a_force_inline)), is_raw_constructor(move(a_is_raw_constructor)){}
NonnullRefPtr<CheckedFunction> Jakt::types::CheckedFunction::__jakt_create(ByteString name, Jakt::utility::Span name_span, Jakt::types::CheckedVisibility visibility, Jakt::ids::TypeId return_type_id, JaktInternal::Optional<Jakt::utility::Span> return_type_span, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params, NonnullRefPtr<Jakt::types::FunctionGenerics> generics, Jakt::types::CheckedBlock block, bool can_throw, Jakt::parser::FunctionType type, Jakt::parser::FunctionLinkage linkage, Jakt::ids::ScopeId function_scope_id, JaktInternal::Optional<Jakt::ids::StructId> struct_id, bool is_instantiated, JaktInternal::Optional<Jakt::parser::ParsedFunction> parsed_function, bool is_comptime, bool is_virtual, bool is_override, bool is_unsafe, bool has_varargs, JaktInternal::Optional<size_t> specialization_index, JaktInternal::Optional<Jakt::ids::ScopeId> owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> owner_scope_generics, bool is_fully_checked, JaktInternal::Optional<Jakt::parser::ExternalName> external_name, JaktInternal::Optional<ByteString> deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,Jakt::parser::ArgumentStoreLevel>>> stores_arguments, Jakt::parser::InlineState force_inline, bool is_raw_constructor) { auto o = adopt_ref(*new CheckedFunction (move(name), move(name_span), move(visibility), move(return_type_id), move(return_type_span), move(params), move(generics), move(block), move(can_throw), move(type), move(linkage), move(function_scope_id), move(struct_id), move(is_instantiated), move(parsed_function), move(is_comptime), move(is_virtual), move(is_override), move(is_unsafe), move(has_varargs), move(specialization_index), move(owner_scope), move(owner_scope_generics), move(is_fully_checked), move(external_name), move(deprecated_message), move(stores_arguments), move(force_inline), move(is_raw_constructor))); return o; }
ByteString Jakt::types::FunctionGenerics::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FunctionGenerics("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("base_scope_id: {}, ", base_scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("base_params: {}, ", base_params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("specializations: {}", specializations);
}
builder.append(")"sv);return builder.to_string(); }
bool Jakt::types::FunctionGenerics::is_specialized_for_types(JaktInternal::DynamicArray<Jakt::ids::TypeId> const types) const {
{
if (types.size() == static_cast<size_t>(0ULL)){
return true;
}
{
JaktInternal::ArrayIterator<JaktInternal::DynamicArray<Jakt::ids::TypeId>> _magic = this->specializations.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::DynamicArray<Jakt::ids::TypeId> specialization = _magic_value.value();
{
bool matched = true;
if (types.size() == specialization.size()){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(types.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (!types.operator[](i).equals(specialization.operator[](i))){
matched = false;
break;
}
}

}
}

}
if (matched){
return true;
}
}

}
}

return false;
}
}

Jakt::types::FunctionGenerics::FunctionGenerics(Jakt::ids::ScopeId a_base_scope_id, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> a_base_params, JaktInternal::DynamicArray<Jakt::types::FunctionGenericParameter> a_params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> a_specializations): base_scope_id(move(a_base_scope_id)), base_params(move(a_base_params)), params(move(a_params)), specializations(move(a_specializations)){}
NonnullRefPtr<FunctionGenerics> Jakt::types::FunctionGenerics::__jakt_create(Jakt::ids::ScopeId base_scope_id, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> base_params, JaktInternal::DynamicArray<Jakt::types::FunctionGenericParameter> params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>> specializations) { auto o = adopt_ref(*new FunctionGenerics (move(base_scope_id), move(base_params), move(params), move(specializations))); return o; }
ByteString Jakt::types::CheckedParameter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedParameter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("requires_label: {}, ", requires_label);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variable: {}, ", *variable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("default_value_expression: {}", default_value_expression);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<Jakt::types::CheckedParameter> Jakt::types::CheckedParameter::map_types(Function<ErrorOr<Jakt::ids::TypeId>(Jakt::ids::TypeId)> const& map) const {
{
return Jakt::types::CheckedParameter(this->requires_label,TRY((this->variable->map_types(map))),this->default_value_expression);
}
}

Jakt::types::CheckedParameter::CheckedParameter(bool a_requires_label, NonnullRefPtr<Jakt::types::CheckedVariable> a_variable, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> a_default_value_expression): requires_label(move(a_requires_label)), variable(move(a_variable)), default_value_expression(move(a_default_value_expression)){}

ByteString Jakt::types::FunctionGenericParameter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FunctionGenericParameter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("kind: {}, ", kind);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("checked_parameter: {}", checked_parameter);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::TypeId Jakt::types::FunctionGenericParameter::type_id() const {
{
return this->checked_parameter.type_id;
}
}

Jakt::types::FunctionGenericParameter Jakt::types::FunctionGenericParameter::parameter(Jakt::ids::TypeId const type_id,Jakt::utility::Span const span) {
{
return Jakt::types::FunctionGenericParameter(Jakt::types::FunctionGenericParameterKind::Parameter(),Jakt::types::CheckedGenericParameter::make(type_id,span));
}
}

Jakt::types::FunctionGenericParameter::FunctionGenericParameter(Jakt::types::FunctionGenericParameterKind a_kind, Jakt::types::CheckedGenericParameter a_checked_parameter): kind(move(a_kind)), checked_parameter(move(a_checked_parameter)){}

ByteString Jakt::types::CheckedVariable::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedVariable("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_mutable: {}, ", is_mutable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("definition_span: {}, ", definition_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_span: {}, ", type_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("visibility: {}, ", visibility);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("owner_scope: {}, ", owner_scope);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("owner_scope_generics: {}, ", owner_scope_generics);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}", external_name);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<NonnullRefPtr<Jakt::types::CheckedVariable>> Jakt::types::CheckedVariable::map_types(Function<ErrorOr<Jakt::ids::TypeId>(Jakt::ids::TypeId)> const& map) const {
{
return Jakt::types::CheckedVariable::__jakt_create(this->name,TRY((map(this->type_id))),this->is_mutable,this->definition_span,this->type_span,this->visibility,this->owner_scope,this->owner_scope_generics,this->external_name);
}
}

Jakt::parser::ExternalName Jakt::types::CheckedVariable::name_for_codegen() const {
{
return this->external_name.value_or_lazy_evaluated([&] { return Jakt::parser::ExternalName::Plain(this->name); });
}
}

Jakt::types::CheckedVariable::CheckedVariable(ByteString a_name, Jakt::ids::TypeId a_type_id, bool a_is_mutable, Jakt::utility::Span a_definition_span, JaktInternal::Optional<Jakt::utility::Span> a_type_span, Jakt::types::CheckedVisibility a_visibility, JaktInternal::Optional<Jakt::ids::ScopeId> a_owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> a_owner_scope_generics, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name): name(move(a_name)), type_id(move(a_type_id)), is_mutable(move(a_is_mutable)), definition_span(move(a_definition_span)), type_span(move(a_type_span)), visibility(move(a_visibility)), owner_scope(move(a_owner_scope)), owner_scope_generics(move(a_owner_scope_generics)), external_name(move(a_external_name)){}
NonnullRefPtr<CheckedVariable> Jakt::types::CheckedVariable::__jakt_create(ByteString name, Jakt::ids::TypeId type_id, bool is_mutable, Jakt::utility::Span definition_span, JaktInternal::Optional<Jakt::utility::Span> type_span, Jakt::types::CheckedVisibility visibility, JaktInternal::Optional<Jakt::ids::ScopeId> owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> owner_scope_generics, JaktInternal::Optional<Jakt::parser::ExternalName> external_name) { auto o = adopt_ref(*new CheckedVariable (move(name), move(type_id), move(is_mutable), move(definition_span), move(type_span), move(visibility), move(owner_scope), move(owner_scope_generics), move(external_name))); return o; }
ByteString Jakt::types::CheckedVarDecl::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedVarDecl("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_mutable: {}, ", is_mutable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", type_id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedVarDecl::CheckedVarDecl(ByteString a_name, bool a_is_mutable, Jakt::utility::Span a_span, Jakt::ids::TypeId a_type_id): name(move(a_name)), is_mutable(move(a_is_mutable)), span(move(a_span)), type_id(move(a_type_id)){}

ByteString Jakt::types::CheckedBlock::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedBlock("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("statements: {}, ", statements);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}, ", scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("control_flow: {}, ", control_flow);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("yielded_type: {}, ", yielded_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("yielded_none: {}", yielded_none);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedBlock::CheckedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> a_statements, Jakt::ids::ScopeId a_scope_id, Jakt::types::BlockControlFlow a_control_flow, JaktInternal::Optional<Jakt::ids::TypeId> a_yielded_type, bool a_yielded_none): statements(move(a_statements)), scope_id(move(a_scope_id)), control_flow(move(a_control_flow)), yielded_type(move(a_yielded_type)), yielded_none(move(a_yielded_none)){}

ByteString Jakt::types::FieldRecord::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FieldRecord("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("struct_id: {}, ", struct_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("field_id: {}", field_id);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::FieldRecord::FieldRecord(Jakt::ids::StructId a_struct_id, Jakt::ids::VarId a_field_id): struct_id(move(a_struct_id)), field_id(move(a_field_id)){}

ByteString Jakt::types::CheckedField::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedField("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variable_id: {}, ", variable_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("default_value_expression: {}, ", default_value_expression);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("default_value_in_definition_scope: {}", default_value_in_definition_scope);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedField::CheckedField(Jakt::ids::VarId a_variable_id, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> a_default_value_expression, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> a_default_value_in_definition_scope): variable_id(move(a_variable_id)), default_value_expression(move(a_default_value_expression)), default_value_in_definition_scope(move(a_default_value_in_definition_scope)){}
NonnullRefPtr<CheckedField> Jakt::types::CheckedField::__jakt_create(Jakt::ids::VarId variable_id, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> default_value_expression, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> default_value_in_definition_scope) { auto o = adopt_ref(*new CheckedField (move(variable_id), move(default_value_expression), move(default_value_in_definition_scope))); return o; }
ByteString Jakt::types::CheckedStruct::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedStruct("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}, ", generic_parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameter_defaults: {}, ", generic_parameter_defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}, ", scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("definition_linkage: {}, ", definition_linkage);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_implementations: {}, ", trait_implementations);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("record_type: {}, ", record_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("super_struct_id: {}, ", super_struct_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}, ", external_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("implements_type: {}, ", implements_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("create_function_name: {}", create_function_name);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::parser::ExternalName Jakt::types::CheckedStruct::name_for_codegen() const {
{
return this->external_name.value_or_lazy_evaluated([&] { return Jakt::parser::ExternalName::Plain(this->name); });
}
}

Jakt::types::CheckedStruct::CheckedStruct(ByteString a_name, Jakt::utility::Span a_name_span, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> a_generic_parameters, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>> a_generic_parameter_defaults, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> a_fields, Jakt::ids::ScopeId a_scope_id, Jakt::parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> a_trait_implementations, Jakt::parser::RecordType a_record_type, Jakt::ids::TypeId a_type_id, JaktInternal::Optional<Jakt::ids::StructId> a_super_struct_id, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Optional<Jakt::ids::TypeId> a_implements_type, JaktInternal::Optional<ByteString> a_create_function_name): name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)), generic_parameter_defaults(move(a_generic_parameter_defaults)), fields(move(a_fields)), scope_id(move(a_scope_id)), definition_linkage(move(a_definition_linkage)), trait_implementations(move(a_trait_implementations)), record_type(move(a_record_type)), type_id(move(a_type_id)), super_struct_id(move(a_super_struct_id)), external_name(move(a_external_name)), implements_type(move(a_implements_type)), create_function_name(move(a_create_function_name)){}

ByteString Jakt::types::CheckedEnum::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedEnum("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}, ", generic_parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variants: {}, ", variants);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}, ", scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("definition_linkage: {}, ", definition_linkage);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_implementations: {}, ", trait_implementations);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("record_type: {}, ", record_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("underlying_type_id: {}, ", underlying_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_boxed: {}", is_boxed);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedEnum::CheckedEnum(ByteString a_name, Jakt::utility::Span a_name_span, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> a_generic_parameters, JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariant> a_variants, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> a_fields, Jakt::ids::ScopeId a_scope_id, Jakt::parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> a_trait_implementations, Jakt::parser::RecordType a_record_type, Jakt::ids::TypeId a_underlying_type_id, Jakt::ids::TypeId a_type_id, bool a_is_boxed): name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)), variants(move(a_variants)), fields(move(a_fields)), scope_id(move(a_scope_id)), definition_linkage(move(a_definition_linkage)), trait_implementations(move(a_trait_implementations)), record_type(move(a_record_type)), underlying_type_id(move(a_underlying_type_id)), type_id(move(a_type_id)), is_boxed(move(a_is_boxed)){}

ByteString Jakt::types::CheckedGenericParameter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedGenericParameter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("constraints: {}, ", constraints);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedGenericParameter Jakt::types::CheckedGenericParameter::make(Jakt::ids::TypeId const type_id,Jakt::utility::Span const span) {
{
return Jakt::types::CheckedGenericParameter(type_id,DynamicArray<Jakt::ids::TraitId>::create_with({}),span);
}
}

Jakt::types::CheckedGenericParameter::CheckedGenericParameter(Jakt::ids::TypeId a_type_id, JaktInternal::DynamicArray<Jakt::ids::TraitId> a_constraints, Jakt::utility::Span a_span): type_id(move(a_type_id)), constraints(move(a_constraints)), span(move(a_span)){}

ByteString Jakt::types::CheckedEnumVariantBinding::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedEnumVariantBinding("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: {}, ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("binding: \"{}\", ", binding);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedEnumVariantBinding::CheckedEnumVariantBinding(JaktInternal::Optional<ByteString> a_name, ByteString a_binding, Jakt::ids::TypeId a_type_id, Jakt::utility::Span a_span): name(move(a_name)), binding(move(a_binding)), type_id(move(a_type_id)), span(move(a_span)){}

ByteString Jakt::types::CheckedStringLiteral::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedStringLiteral("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("value: {}, ", value);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("may_throw: {}", may_throw);
}
builder.append(")"sv);return builder.to_string(); }
ByteString Jakt::types::CheckedStringLiteral::to_string() const {
{
return this->value.to_string();
}
}

Jakt::types::CheckedStringLiteral::CheckedStringLiteral(Jakt::types::StringLiteral a_value, Jakt::ids::TypeId a_type_id, bool a_may_throw): value(move(a_value)), type_id(move(a_type_id)), may_throw(move(a_may_throw)){}

ByteString Jakt::types::ClassInstanceRebind::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ClassInstanceRebind("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name_span: {}, ", name_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_mutable: {}, ", is_mutable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_reference: {}", is_reference);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::ClassInstanceRebind::ClassInstanceRebind(ByteString a_name, Jakt::utility::Span a_name_span, bool a_is_mutable, bool a_is_reference): name(move(a_name)), name_span(move(a_name_span)), is_mutable(move(a_is_mutable)), is_reference(move(a_is_reference)){}

ByteString Jakt::types::CheckedMatchCase::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedMatchCase("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("patterns: {}, ", patterns);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("body: {}", body);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedMatchCase::CheckedMatchCase(JaktInternal::DynamicArray<Jakt::types::CheckedMatchPattern> a_patterns, Jakt::types::CheckedMatchBody a_body): patterns(move(a_patterns)), body(move(a_body)){}

ByteString Jakt::types::OperatorTraitImplementation::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("OperatorTraitImplementation("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_id: {}, ", trait_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_generic_arguments: {}, ", trait_generic_arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("call_expression: {}", call_expression);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::OperatorTraitImplementation::OperatorTraitImplementation(Jakt::ids::TraitId a_trait_id, JaktInternal::DynamicArray<Jakt::ids::TypeId> a_trait_generic_arguments, Jakt::types::CheckedCall a_call_expression): trait_id(move(a_trait_id)), trait_generic_arguments(move(a_trait_generic_arguments)), call_expression(move(a_call_expression)){}

ByteString Jakt::types::CheckedBinaryOperator::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedBinaryOperator("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("op: {}, ", op);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_implementation: {}", trait_implementation);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::CheckedBinaryOperator::CheckedBinaryOperator(Jakt::parser::BinaryOperator a_op, JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> a_trait_implementation): op(move(a_op)), trait_implementation(move(a_trait_implementation)){}

ByteString Jakt::types::ResolvedNamespace::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ResolvedNamespace("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}, ", external_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}", generic_parameters);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::parser::ExternalName Jakt::types::ResolvedNamespace::name_for_codegen() const {
{
return this->external_name.value_or_lazy_evaluated([&] { return Jakt::parser::ExternalName::Plain(this->name); });
}
}

Jakt::types::ResolvedNamespace::ResolvedNamespace(ByteString a_name, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> a_generic_parameters): name(move(a_name)), external_name(move(a_external_name)), generic_parameters(move(a_generic_parameters)){}

ByteString Jakt::types::CheckedCall::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedCall("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespace_: {}, ", namespace_);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}, ", args);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_args: {}, ", type_args);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("function_id: {}, ", function_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type: {}, ", return_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("callee_throws: {}, ", callee_throws);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}, ", external_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("force_inline: {}", force_inline);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::parser::ExternalName Jakt::types::CheckedCall::name_for_codegen() const {
{
return this->external_name.value_or_lazy_evaluated([&] { return Jakt::parser::ExternalName::Plain(this->name); });
}
}

Jakt::types::CheckedCall::CheckedCall(JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> a_namespace_, ByteString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> a_args, JaktInternal::DynamicArray<Jakt::ids::TypeId> a_type_args, JaktInternal::Optional<Jakt::ids::FunctionId> a_function_id, Jakt::ids::TypeId a_return_type, bool a_callee_throws, JaktInternal::Optional<Jakt::parser::ExternalName> a_external_name, Jakt::parser::InlineState a_force_inline): namespace_(move(a_namespace_)), name(move(a_name)), args(move(a_args)), type_args(move(a_type_args)), function_id(move(a_function_id)), return_type(move(a_return_type)), callee_throws(move(a_callee_throws)), external_name(move(a_external_name)), force_inline(move(a_force_inline)){}

ByteString Jakt::types::CheckedProgram::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedProgram("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("modules: {}, ", modules);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("exports: {}, ", exports);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("loaded_modules: {}", loaded_modules);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::ids::ModuleId Jakt::types::CheckedProgram::create_module(ByteString const name,bool const is_root,JaktInternal::Optional<ByteString> const path) {
{
size_t const new_id = this->modules.size();
Jakt::ids::ModuleId const module_id = Jakt::ids::ModuleId(new_id);
NonnullRefPtr<Jakt::types::Module> const module = Jakt::types::Module::__jakt_create(module_id,name,DynamicArray<NonnullRefPtr<typename Jakt::types::Type>>::create_with({Jakt::types::Type::Void(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::Bool(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::U8(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::U16(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::U32(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::U64(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::I8(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::I16(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::I32(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::I64(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::F32(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::F64(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::Usize(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::JaktString(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::CChar(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::CInt(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::Unknown(Jakt::parser::CheckedQualifiers(false)), Jakt::types::Type::Never(Jakt::parser::CheckedQualifiers(false))}),path.value_or_lazy_evaluated([&] { return this->compiler->current_file_path().value().to_string(); }),is_root,DynamicArray<NonnullRefPtr<Jakt::types::CheckedFunction>>::create_with({}),DynamicArray<Jakt::types::CheckedStruct>::create_with({}),DynamicArray<Jakt::types::CheckedEnum>::create_with({}),DynamicArray<NonnullRefPtr<Jakt::types::Scope>>::create_with({}),DynamicArray<NonnullRefPtr<Jakt::types::CheckedTrait>>::create_with({}),DynamicArray<NonnullRefPtr<Jakt::types::CheckedVariable>>::create_with({}),DynamicArray<Jakt::ids::ModuleId>::create_with({}),Dictionary<size_t, Jakt::ids::StructId>::create_with_entries({}));
this->modules.push(module);
return module_id;
}
}

ByteString Jakt::types::CheckedProgram::debug_description_of(Jakt::ids::ScopeId const scope_id) const {
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

Jakt::ids::ScopeId Jakt::types::CheckedProgram::create_scope(JaktInternal::Optional<Jakt::ids::ScopeId> const parent_scope_id,bool const can_throw,ByteString const debug_name,Jakt::ids::ModuleId const module_id,bool const for_block) {
{
bool is_from_generated_code = false;
if (parent_scope_id.has_value()){
if (parent_scope_id.value().module_id.id >= this->modules.size()){
this->compiler->panic(__jakt_format(StringView::from_string_literal("create_scope: parent_scope_id.module is invalid! No module with id {}."sv),parent_scope_id.value().module_id.id));
}
if (parent_scope_id.value().id >= this->modules.operator[](parent_scope_id.value().module_id.id)->scopes.size()){
this->compiler->panic(__jakt_format(StringView::from_string_literal("create_scope: parent_scope_id.id is invalid! Module {} does not have a scope with id {}."sv),parent_scope_id.value().module_id.id,parent_scope_id.value().id));
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(parent_scope_id.value());
is_from_generated_code = scope->is_from_generated_code;
}
NonnullRefPtr<Jakt::types::Scope> const scope = Jakt::types::Scope::__jakt_create(parent_scope_id,can_throw,debug_name,for_block,is_from_generated_code,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Dictionary<ByteString, Jakt::ids::VarId>::create_with_entries({}),Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),Dictionary<ByteString, Jakt::ids::StructId>::create_with_entries({}),Dictionary<ByteString, JaktInternal::DynamicArray<Jakt::ids::FunctionId>>::create_with_entries({}),Dictionary<ByteString, Jakt::ids::EnumId>::create_with_entries({}),Dictionary<ByteString, Jakt::ids::TypeId>::create_with_entries({}),Dictionary<ByteString, Jakt::ids::TraitId>::create_with_entries({}),Dictionary<ByteString, Jakt::ids::ModuleId>::create_with_entries({}),Dictionary<ByteString, Jakt::ids::ScopeId>::create_with_entries({}),JaktInternal::OptionalNone(),DynamicArray<Jakt::ids::ScopeId>::create_with({}),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),DynamicArray<Jakt::parser::IncludeAction>::create_with({}),DynamicArray<Jakt::parser::IncludeAction>::create_with({}),DynamicArray<Jakt::types::ResolutionMixin>::create_with({}),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Dictionary<ByteString, Jakt::types::SpecializedType>::create_with_entries({}));
this->modules.operator[](module_id.id)->scopes.push(scope);
return Jakt::ids::ScopeId(module_id,JaktInternal::checked_sub(this->modules.operator[](module_id.id)->scopes.size(),static_cast<size_t>(1ULL)));
}
}

Jakt::ids::TypeId Jakt::types::CheckedProgram::apply_qualifiers_to_type(Jakt::parser::CheckedQualifiers const qualifiers,Jakt::ids::TypeId const type_id) {
{
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(type_id);
if ([](Jakt::parser::CheckedQualifiers const& self, Jakt::parser::CheckedQualifiers rhs) -> bool {{
return !self.equals(rhs);
}
}
(qualifiers,type->common.init_common.qualifiers)){
return this->find_or_add_type_id(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::Type>, Jakt::ids::TypeId>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(Jakt::types::Type::Void(qualifiers));
case 1 /* Bool */:return JaktInternal::ExplicitValue(Jakt::types::Type::Bool(qualifiers));
case 2 /* U8 */:return JaktInternal::ExplicitValue(Jakt::types::Type::U8(qualifiers));
case 3 /* U16 */:return JaktInternal::ExplicitValue(Jakt::types::Type::U16(qualifiers));
case 4 /* U32 */:return JaktInternal::ExplicitValue(Jakt::types::Type::U32(qualifiers));
case 5 /* U64 */:return JaktInternal::ExplicitValue(Jakt::types::Type::U64(qualifiers));
case 6 /* I8 */:return JaktInternal::ExplicitValue(Jakt::types::Type::I8(qualifiers));
case 7 /* I16 */:return JaktInternal::ExplicitValue(Jakt::types::Type::I16(qualifiers));
case 8 /* I32 */:return JaktInternal::ExplicitValue(Jakt::types::Type::I32(qualifiers));
case 9 /* I64 */:return JaktInternal::ExplicitValue(Jakt::types::Type::I64(qualifiers));
case 10 /* F32 */:return JaktInternal::ExplicitValue(Jakt::types::Type::F32(qualifiers));
case 11 /* F64 */:return JaktInternal::ExplicitValue(Jakt::types::Type::F64(qualifiers));
case 12 /* Usize */:return JaktInternal::ExplicitValue(Jakt::types::Type::Usize(qualifiers));
case 13 /* JaktString */:return JaktInternal::ExplicitValue(Jakt::types::Type::JaktString(qualifiers));
case 14 /* CChar */:return JaktInternal::ExplicitValue(Jakt::types::Type::CChar(qualifiers));
case 15 /* CInt */:return JaktInternal::ExplicitValue(Jakt::types::Type::CInt(qualifiers));
case 16 /* Unknown */:return JaktInternal::ExplicitValue(Jakt::types::Type::Unknown(Jakt::parser::CheckedQualifiers(false)));
case 17 /* Never */:return JaktInternal::ExplicitValue(Jakt::types::Type::Never(Jakt::parser::CheckedQualifiers(false)));
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& trait_implementations = __jakt_match_value.trait_implementations;
bool const& is_value = __jakt_match_value.is_value;
return JaktInternal::ExplicitValue(Jakt::types::Type::TypeVariable(qualifiers,name,trait_implementations,is_value));
};/*case end*/
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;Jakt::ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Jakt::types::Type::Dependent(qualifiers,namespace_type,name,args));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Jakt::types::Type::GenericInstance(qualifiers,id,args));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Jakt::types::Type::GenericEnumInstance(qualifiers,id,args));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Jakt::types::Type::GenericTraitInstance(qualifiers,id,args));
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Type::Struct(qualifiers,id));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Type::Enum(qualifiers,id));
};/*case end*/
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Type::RawPtr(qualifiers,id));
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Type::Trait(qualifiers,id));
};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Type::Reference(qualifiers,id));
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Type::MutableReference(qualifiers,id));
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
Jakt::ids::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(Jakt::types::Type::Function(qualifiers,params,can_throw,return_type_id,pseudo_function_id));
};/*case end*/
case 30 /* Self */:return JaktInternal::ExplicitValue(Jakt::types::Type::Self(qualifiers));
case 31 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Type::Const(qualifiers,value));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),type_id.module,true);
}
else {
return type_id;
}

}
}

Jakt::ids::StructId Jakt::types::CheckedProgram::builtin_implementation_struct(Jakt::types::BuiltinType const builtin,Jakt::ids::ModuleId const for_module) {
{
size_t const id = builtin.id();
NonnullRefPtr<Jakt::types::Module> module = this->modules.operator[](for_module.id);
if (module->builtin_implementation_structs.contains(id)){
return module->builtin_implementation_structs.operator[](id);
}
Jakt::ids::ScopeId const scope_id = this->create_scope(JaktInternal::OptionalNone(),false,__jakt_format(StringView::from_string_literal("builtin({})"sv),builtin.constructor_name()),for_module,false);
JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>> const trait_implementations = Dictionary<ByteString, JaktInternal::DynamicArray<JaktInternal::Tuple<Jakt::ids::TraitId,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>::create_with_entries({});
Jakt::utility::Span const name_span = Jakt::utility::Span(Jakt::utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL));
Jakt::ids::StructId const struct_id = Jakt::ids::StructId(for_module,module->structures.size());
Jakt::ids::TypeId const struct_type_id = this->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id),for_module,false);
Jakt::types::CheckedStruct const struct_ = Jakt::types::CheckedStruct(__jakt_format(StringView::from_string_literal("Builtin_{}"sv),builtin.constructor_name()),name_span,DynamicArray<Jakt::types::CheckedGenericParameter>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>>::create_with({}),scope_id,Jakt::parser::DefinitionLinkage::External(),trait_implementations,Jakt::parser::RecordType::Struct(DynamicArray<Jakt::parser::ParsedField>::create_with({}),JaktInternal::OptionalNone()),struct_type_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::types::builtin(builtin),JaktInternal::OptionalNone());
module->structures.push(struct_);
module->builtin_implementation_structs.set(id, struct_id);
return struct_id;
}
}

NonnullRefPtr<Jakt::types::Module> Jakt::types::CheckedProgram::get_module(Jakt::ids::ModuleId const id) const {
{
return this->modules.operator[](id.id);
}
}

NonnullRefPtr<Jakt::types::CheckedFunction> Jakt::types::CheckedProgram::get_function(Jakt::ids::FunctionId const id) const {
{
return this->modules.operator[](id.module.id)->functions.operator[](id.id);
}
}

NonnullRefPtr<Jakt::types::CheckedVariable> Jakt::types::CheckedProgram::get_variable(Jakt::ids::VarId const id) const {
{
return this->modules.operator[](id.module.id)->variables.operator[](id.id);
}
}

NonnullRefPtr<typename Jakt::types::Type> Jakt::types::CheckedProgram::get_type(Jakt::ids::TypeId const id) const {
{
return this->modules.operator[](id.module.id)->types.operator[](id.id);
}
}

Jakt::types::CheckedEnum Jakt::types::CheckedProgram::get_enum(Jakt::ids::EnumId const id) const {
{
return this->modules.operator[](id.module.id)->enums.operator[](id.id);
}
}

Jakt::types::CheckedStruct Jakt::types::CheckedProgram::get_struct(Jakt::ids::StructId const id) const {
{
return this->modules.operator[](id.module.id)->structures.operator[](id.id);
}
}

NonnullRefPtr<Jakt::types::Scope> Jakt::types::CheckedProgram::get_scope(Jakt::ids::ScopeId const id) const {
{
return this->modules.operator[](id.module_id.id)->scopes.operator[](id.id);
}
}

NonnullRefPtr<Jakt::types::CheckedTrait> Jakt::types::CheckedProgram::get_trait(Jakt::ids::TraitId const id) const {
{
return this->modules.operator[](id.module.id)->traits.operator[](id.id);
}
}

Jakt::ids::ScopeId Jakt::types::CheckedProgram::prelude_scope_id() const {
{
return Jakt::ids::ScopeId(Jakt::ids::ModuleId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL));
}
}

Jakt::ids::ModuleId Jakt::types::CheckedProgram::prelude_module_id() const {
{
return Jakt::ids::ModuleId(static_cast<size_t>(0ULL));
}
}

void Jakt::types::CheckedProgram::set_loaded_module(ByteString const module_name,Jakt::types::LoadedModule const loaded_module) {
{
this->loaded_modules.set(module_name,loaded_module);
}
}

JaktInternal::Optional<Jakt::types::LoadedModule> Jakt::types::CheckedProgram::get_loaded_module(ByteString const module_name) const {
{
return this->loaded_modules.get(module_name);
}
}

void Jakt::types::CheckedProgram::set_owner_scope_if_needed(Jakt::ids::ScopeId const parent_scope_id,JaktInternal::DynamicArray<Jakt::ids::FunctionId> const overload_set,Jakt::utility::Span const span) {
{
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = overload_set.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId overload = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> function = this->get_function(overload);
if (!function->owner_scope.has_value()){
function->owner_scope = parent_scope_id;
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(parent_scope_id);
JaktInternal::Optional<Jakt::ids::TypeId> __jakt_tmp61 = scope->relevant_type_id;
if (__jakt_tmp61.has_value()){
Jakt::ids::TypeId const type_id = __jakt_tmp61.value();
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>> const no_defaults = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const no_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> const maybe_generics = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>, void>{
auto&& __jakt_match_variant = *this->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedStruct const struct_ = this->get_struct(id);
return JaktInternal::ExplicitValue<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>(Tuple{struct_.generic_parameters, struct_.generic_parameter_defaults, args}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const struct_ = this->get_struct(id);
return JaktInternal::ExplicitValue<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>(Tuple{struct_.generic_parameters, struct_.generic_parameter_defaults, no_args}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>(Tuple{this->get_enum(id).generic_parameters, no_defaults, args}));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>(Tuple{this->get_enum(id).generic_parameters, no_defaults, no_args}));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>(Tuple{this->get_trait(id)->generic_parameters, no_defaults, args}));
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>>>(Tuple{this->get_trait(id)->generic_parameters, no_defaults, no_args}));
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
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>>> __jakt_tmp62 = maybe_generics;
if (__jakt_tmp62.has_value()){
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const generics = __jakt_tmp62.value();
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> inferences = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>>,JaktInternal::DynamicArray<Jakt::ids::TypeId>> const parameters_declared_defaults_args_ = generics;
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const parameters = parameters_declared_defaults_args_.template get<0>();
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>> const declared_defaults = parameters_declared_defaults_args_.template get<1>();
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = parameters_declared_defaults_args_.template get<2>();

JaktInternal::Optional<Jakt::ids::TypeId> const no_type_id = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>> const empty_defaults = DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>>::filled(parameters.size(), no_type_id);
JaktInternal::DynamicArray<JaktInternal::Optional<Jakt::ids::TypeId>> const defaults = declared_defaults.value_or_lazy_evaluated([&] { return empty_defaults; });
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(parameters.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::CheckedGenericParameter const& parameter = parameters.operator[](i);
Jakt::ids::TypeId const arg = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ids::TypeId>,void> {
auto __jakt_enum_value = (i < args.size());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::ids::TypeId>>(args.operator[](i)));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(defaults.operator[](i));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
}).value_or_lazy_evaluated([&] { return parameter.type_id; });
inferences.set(parameter.type_id,arg);
}

}
}

function->owner_scope_generics = inferences;
}
else {
return;
}

}
}
}

}
}

}
}

void Jakt::types::CheckedProgram::set_owner_scope_if_needed(Jakt::ids::ScopeId const parent_scope_id,Jakt::ids::VarId const var_id) {
{
NonnullRefPtr<Jakt::types::CheckedVariable> variable = this->get_variable(var_id);
if (!variable->owner_scope.has_value()){
variable->owner_scope = parent_scope_id;
}
}
}

ErrorOr<JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedVariable>>> Jakt::types::CheckedProgram::find_var_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const var,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->template for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<Jakt::types::CheckedVariable>>(scope_id,[var, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<NonnullRefPtr<Jakt::types::CheckedVariable>>> {{
if (!mixin.mixin_vars){
return Jakt::utility::IterationDecision<NonnullRefPtr<Jakt::types::CheckedVariable>>::Continue();
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(mixin.scope_id);
JaktInternal::Optional<Jakt::ids::VarId> const maybe_var = scope->vars.get(var);
if (maybe_var.has_value()){
return Jakt::utility::IterationDecision<NonnullRefPtr<Jakt::types::CheckedVariable>>::Break(this->get_variable(maybe_var.value()));
}
return Jakt::utility::IterationDecision<NonnullRefPtr<Jakt::types::CheckedVariable>>::Continue();
}
}
,ignore_mixin_scopes,root_scope);
}
}

ErrorOr<JaktInternal::Optional<Jakt::types::Value>> Jakt::types::CheckedProgram::find_comptime_binding_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->template for_each_scope_accessible_unqualified_from_scope<Jakt::types::Value>(scope_id,[name, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<Jakt::types::Value>> {{
if (!mixin.mixin_bindings){
return Jakt::utility::IterationDecision<Jakt::types::Value>::Continue();
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(mixin.scope_id);
JaktInternal::Optional<Jakt::types::Value> const maybe_binding = scope->comptime_bindings.get(name);
if (maybe_binding.has_value()){
return Jakt::utility::IterationDecision<Jakt::types::Value>::Break(maybe_binding.value());
}
return Jakt::utility::IterationDecision<Jakt::types::Value>::Continue();
}
}
,ignore_mixin_scopes,root_scope);
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>> Jakt::types::CheckedProgram::find_type_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>(scope_id,[name, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>> {{
if (!mixin.mixin_types){
return Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>::Continue();
}
JaktInternal::Optional<Jakt::ids::TypeId> const maybe_type = this->get_scope(mixin.scope_id)->types.get(name);
if (maybe_type.has_value()){
return Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>::Break(Tuple{maybe_type.value(), mixin.scope_id});
}
return Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::ScopeId>>::Continue();
}
}
,ignore_mixin_scopes,root_scope);
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::TypeId>> Jakt::types::CheckedProgram::find_type_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return TRY((this->find_type_scope(scope_id,name,ignore_mixin_scopes,root_scope))).map([](auto& _value) { return _value.template get<0>(); });
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::EnumId>> Jakt::types::CheckedProgram::find_enum_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->template for_each_scope_accessible_unqualified_from_scope<Jakt::ids::EnumId>(scope_id,[name, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::EnumId>> {{
if (!mixin.mixin_enums){
return Jakt::utility::IterationDecision<Jakt::ids::EnumId>::Continue();
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(mixin.scope_id);
JaktInternal::Optional<Jakt::ids::EnumId> const maybe_enum = scope->enums.get(name);
if (maybe_enum.has_value()){
return Jakt::utility::IterationDecision<Jakt::ids::EnumId>::Break(maybe_enum.value());
}
return Jakt::utility::IterationDecision<Jakt::ids::EnumId>::Continue();
}
}
,ignore_mixin_scopes,root_scope);
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::TraitId>> Jakt::types::CheckedProgram::find_trait_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->template for_each_scope_accessible_unqualified_from_scope<Jakt::ids::TraitId>(scope_id,[name, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::TraitId>> {{
if (!mixin.mixin_traits){
return Jakt::utility::IterationDecision<Jakt::ids::TraitId>::Continue();
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(mixin.scope_id);
JaktInternal::Optional<Jakt::ids::TraitId> const maybe_trait = scope->traits.get(name);
if (maybe_trait.has_value()){
return Jakt::utility::IterationDecision<Jakt::ids::TraitId>::Break(maybe_trait.value());
}
return Jakt::utility::IterationDecision<Jakt::ids::TraitId>::Continue();
}
}
,ignore_mixin_scopes,root_scope);
}
}

bool Jakt::types::CheckedProgram::is_integer(Jakt::ids::TypeId const type_id) const {
{
return this->get_type(type_id)->is_integer();
}
}

bool Jakt::types::CheckedProgram::is_floating(Jakt::ids::TypeId const type_id) const {
{
return this->get_type(type_id)->is_floating();
}
}

bool Jakt::types::CheckedProgram::is_numeric(Jakt::ids::TypeId const type_id) const {
{
return this->is_integer(type_id) || this->is_floating(type_id);
}
}

ErrorOr<bool> Jakt::types::CheckedProgram::is_string(Jakt::ids::TypeId const type_id) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *this->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */:return JaktInternal::ExplicitValue(true);
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("String"sv)))).equals(struct_id));
};/*case end*/
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

i64 Jakt::types::CheckedProgram::get_bits(Jakt::ids::TypeId const type_id) const {
{
return this->get_type(type_id)->get_bits();
}
}

bool Jakt::types::CheckedProgram::is_signed(Jakt::ids::TypeId const type_id) const {
{
return this->get_type(type_id)->is_signed();
}
}

ErrorOr<JaktInternal::Optional<bool>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope_direct_chain(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<bool>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
AK::Queue<Jakt::types::ResolutionMixin> scopes_to_check = AK::Queue<Jakt::types::ResolutionMixin>();
JaktInternal::Set<Jakt::ids::ScopeId> seen = Set<Jakt::ids::ScopeId>::create_with_values({});
scopes_to_check.enqueue(Jakt::types::ResolutionMixin(scope_id,true,true,true,true,true,true,true,true,true));
{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = this->get_scope(scope_id)->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child = _magic_value.value();
{
scopes_to_check.enqueue(Jakt::types::ResolutionMixin(child,true,true,true,true,true,true,true,true,true));
}

}
}

while (!scopes_to_check.is_empty()){
Jakt::types::ResolutionMixin const mixin = scopes_to_check.dequeue();
Jakt::ids::ScopeId const scope_id = mixin.scope_id;
if (seen.contains(scope_id)){
continue;
}
seen.add(scope_id);
typename Jakt::utility::IterationDecision<bool> const res = TRY((callback(mixin,JaktInternal::OptionalNone(),false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
return static_cast<JaktInternal::Optional<bool>>(value);
}
return JaktInternal::ExplicitValue<void>();
}else {{
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(scope_id);
if ((!(root_scope.has_value() && scope_id.equals(root_scope.value()))) && scope->parent.has_value()){
scopes_to_check.enqueue(Jakt::types::ResolutionMixin(scope->parent.value(),true,true,true,true,true,true,true,true,true));
}
if (scope->namespace_name.has_value()){
continue;
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
scopes_to_check.enqueue(Jakt::types::ResolutionMixin(child,true,true,true,true,true,true,true,true,true));
}

}
}

}
return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<bool>> Jakt::types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope_impl(Jakt::ids::ScopeId const scope_id,Function<ErrorOr<typename Jakt::utility::IterationDecision<bool>>(Jakt::types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
if (ignore_mixin_scopes){
return this->for_each_scope_accessible_unqualified_from_scope_direct_chain(scope_id,callback,root_scope);
}
AK::Queue<Jakt::types::ResolutionMixin> scopes_to_check = AK::Queue<Jakt::types::ResolutionMixin>();
JaktInternal::Set<Jakt::ids::ScopeId> seen = Set<Jakt::ids::ScopeId>::create_with_values({});
scopes_to_check.enqueue(Jakt::types::ResolutionMixin(scope_id,true,true,true,true,true,true,true,true,true));
{
JaktInternal::ArrayIterator<Jakt::ids::ScopeId> _magic = this->get_scope(scope_id)->children.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::ScopeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::ScopeId child = _magic_value.value();
{
scopes_to_check.enqueue(Jakt::types::ResolutionMixin(child,true,true,true,true,true,true,true,true,true));
}

}
}

while (!scopes_to_check.is_empty()){
Jakt::types::ResolutionMixin const mixin = scopes_to_check.dequeue();
Jakt::ids::ScopeId const scope_id = mixin.scope_id;
if (seen.contains(scope_id)){
continue;
}
seen.add(scope_id);
typename Jakt::utility::IterationDecision<bool> const res = TRY((callback(mixin,JaktInternal::OptionalNone(),false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
return static_cast<JaktInternal::Optional<bool>>(value);
}
return JaktInternal::ExplicitValue<void>();
}else {{
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(scope_id);
if ((!(root_scope.has_value() && scope_id.equals(root_scope.value()))) && scope->parent.has_value()){
scopes_to_check.enqueue(Jakt::types::ResolutionMixin(scope->parent.value(),true,true,true,true,true,true,true,true,true));
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
if (!this->get_scope(child)->namespace_name.has_value()){
scopes_to_check.enqueue(Jakt::types::ResolutionMixin(child,true,true,true,true,true,true,true,true,true));
}
}

}
}

{
JaktInternal::ArrayIterator<Jakt::types::ResolutionMixin> _magic = scope->resolution_mixins.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::ResolutionMixin> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::ResolutionMixin entry = _magic_value.value();
{
scopes_to_check.enqueue(entry);
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::ScopeId> _magic = scope->aliases.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId> name__alias__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::ScopeId> const jakt__name__alias__ = name__alias__;
ByteString const name = jakt__name__alias__.template get<0>();
Jakt::ids::ScopeId const alias = jakt__name__alias__.template get<1>();

typename Jakt::utility::IterationDecision<bool> const res = TRY((callback(Jakt::types::ResolutionMixin(alias,true,true,true,true,true,true,true,true,true),name,true)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
return static_cast<JaktInternal::Optional<bool>>(value);
}
return JaktInternal::ExplicitValue<void>();
}else {{
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
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
JaktInternal::Optional<Jakt::ids::ScopeId> search_scope_id = scope_id;
while (search_scope_id.has_value()){
NonnullRefPtr<Jakt::types::Scope> const search_scope = this->get_scope(search_scope_id.value());
{
JaktInternal::DictionaryIterator<ByteString,Jakt::ids::ModuleId> _magic = search_scope->imports.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::ids::ModuleId>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<ByteString,Jakt::ids::ModuleId> name__module__ = _magic_value.value();
{
JaktInternal::Tuple<ByteString,Jakt::ids::ModuleId> const jakt__name__module__ = name__module__;
ByteString const name = jakt__name__module__.template get<0>();
Jakt::ids::ModuleId const module = jakt__name__module__.template get<1>();

Jakt::ids::ScopeId const import_scope_id = Jakt::ids::ScopeId(module,static_cast<size_t>(0ULL));
typename Jakt::utility::IterationDecision<bool> const res = TRY((callback(Jakt::types::ResolutionMixin(import_scope_id,true,true,true,true,true,true,true,true,true),name,false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
return static_cast<JaktInternal::Optional<bool>>(value);
}
return JaktInternal::ExplicitValue<void>();
}else {{
}
return JaktInternal::ExplicitValue<void>();
}return JaktInternal::ExplicitValue<void>();
}());
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

search_scope_id = search_scope->parent;
}
return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::StructId>> Jakt::types::CheckedProgram::find_struct_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->template for_each_scope_accessible_unqualified_from_scope<Jakt::ids::StructId>(scope_id,[name, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<Jakt::ids::StructId>> {{
if (!mixin.mixin_structs){
return Jakt::utility::IterationDecision<Jakt::ids::StructId>::Continue();
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(mixin.scope_id);
JaktInternal::Optional<Jakt::ids::StructId> const maybe_struct = scope->structs.get(name);
if (maybe_struct.has_value()){
return Jakt::utility::IterationDecision<Jakt::ids::StructId>::Break(maybe_struct.value());
}
return Jakt::utility::IterationDecision<Jakt::ids::StructId>::Continue();
}
}
,ignore_mixin_scopes,root_scope);
}
}

ErrorOr<Jakt::ids::StructId> Jakt::types::CheckedProgram::find_struct_in_prelude(ByteString const name) const {
{
Jakt::ids::ScopeId const scope_id = this->prelude_scope_id();
JaktInternal::Optional<Jakt::ids::StructId> const struct_id = TRY((this->find_struct_in_scope(scope_id,name,true,JaktInternal::OptionalNone())));
if (struct_id.has_value()){
return struct_id.value();
}
this->compiler->panic(__jakt_format(StringView::from_string_literal("internal error: {} builtin definition not found"sv),name));
}
}

ErrorOr<bool> Jakt::types::CheckedProgram::is_scope_directly_accessible_from(Jakt::ids::ScopeId const check_scope_id,Jakt::ids::ScopeId const scope_id,bool const ignore_mixin_scopes) const {
{
return TRY((this->template for_each_scope_accessible_unqualified_from_scope<bool>(scope_id,[check_scope_id](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<bool>> {{
if (check_scope_id.equals(mixin.scope_id)){
return Jakt::utility::IterationDecision<bool>::Break(true);
}
return Jakt::utility::IterationDecision<bool>::Continue();
}
}
,ignore_mixin_scopes,JaktInternal::OptionalNone()))).value_or_lazy_evaluated([&] { return false; });
}
}

ErrorOr<Jakt::types::StructOrEnumId> Jakt::types::CheckedProgram::find_reflected_primitive(ByteString const primitive) const {
{
Jakt::ids::ScopeId const scope_id = this->prelude_scope_id();
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> const maybe_namespace = TRY((this->find_namespace_in_scope(scope_id,ByteString::from_utf8_without_validation("Reflect"sv),false,true,JaktInternal::OptionalNone())));
if (!maybe_namespace.has_value()){
this->compiler->panic(__jakt_format(StringView::from_string_literal("internal error: builtin namespace 'Reflect' not found"sv)));
}
Jakt::ids::ScopeId const reflect_namespace_scope_id = maybe_namespace.value().template get<0>();
JaktInternal::Optional<Jakt::ids::EnumId> const enum_id = TRY((this->find_enum_in_scope(reflect_namespace_scope_id,primitive,false,JaktInternal::OptionalNone())));
if (enum_id.has_value()){
return Jakt::types::StructOrEnumId::Enum(enum_id.value());
}
JaktInternal::Optional<Jakt::ids::StructId> const struct_id = TRY((this->find_struct_in_scope(reflect_namespace_scope_id,primitive,false,JaktInternal::OptionalNone())));
if (struct_id.has_value()){
return Jakt::types::StructOrEnumId::Struct(struct_id.value());
}
this->compiler->panic(__jakt_format(StringView::from_string_literal("internal error: definition for reflect builtin '{}' not found"sv),primitive));
}
}

Jakt::ids::ScopeId Jakt::types::CheckedProgram::find_type_scope_id(Jakt::ids::TypeId const type_id) {
{
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(type_id);
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId, Jakt::ids::ScopeId>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_struct(struct_id).scope_id);
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_struct(struct_id).scope_id);
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_enum(enum_id).scope_id);
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_enum(enum_id).scope_id);
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_trait(trait_id)->scope_id);
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& trait_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->get_trait(trait_id)->scope_id);
};/*case end*/
default:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId,Jakt::ids::ScopeId> {
auto __jakt_enum_value = (type->is_builtin());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(this->get_struct(this->builtin_implementation_struct(type->as_builtin_type(),this->prelude_module_id())).scope_id);
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(this->prelude_scope_id());
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
}
}

JaktInternal::Optional<Jakt::ids::ScopeId> Jakt::types::CheckedProgram::find_namespace_in_immediate_children_of_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const treat_aliases_as_imports) const {
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
NonnullRefPtr<Jakt::types::Scope> const child_scope = this->get_scope(child);
if (child_scope->namespace_name.has_value() && (child_scope->namespace_name.value() == name)){
return child;
}
}

}
}

if (treat_aliases_as_imports){
if (scope->aliases.contains(name)){
return scope->aliases.get(name);
}
}
return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>> Jakt::types::CheckedProgram::find_namespace_in_scope(Jakt::ids::ScopeId const scope_id,ByteString const name,bool const treat_aliases_as_imports,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return this->template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>(scope_id,[name, treat_aliases_as_imports, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>> {{
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(mixin.scope_id);
JaktInternal::Optional<ByteString> const effective_name = name_override.value_or_lazy_evaluated_optional([&] { return scope->namespace_name; });
bool const is_import = name_override.has_value() && (!is_alias);
if (effective_name.has_value() && (effective_name.value() == name)){
return Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>::Break(Tuple{mixin.scope_id, is_import || (is_alias && treat_aliases_as_imports)});
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
NonnullRefPtr<Jakt::types::Scope> const child_scope = this->get_scope(child);
JaktInternal::Optional<ByteString> const effective_name = name_override.value_or_lazy_evaluated_optional([&] { return child_scope->namespace_name; });
if (effective_name.has_value() && (effective_name.value() == name)){
return Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>::Break(Tuple{child, false});
}
}

}
}

return Jakt::utility::IterationDecision<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>>::Continue();
}
}
,ignore_mixin_scopes,root_scope);
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> Jakt::types::CheckedProgram::find_function_in_scope(Jakt::ids::ScopeId const parent_scope_id,ByteString const function_name,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const results = TRY((this->find_functions_with_name_in_scope(parent_scope_id,function_name,false,root_scope)));
if (!results.has_value()){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const functions = results.value();
if (functions.size() != static_cast<size_t>(1ULL)){
this->compiler->panic(__jakt_format(StringView::from_string_literal("internal error: found {} functions with name '{}', but expected 1"sv),functions.size(),function_name));
}
return functions.operator[](static_cast<i64>(0LL));
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::FunctionId>> Jakt::types::CheckedProgram::find_default_constructors_in_scope(Jakt::ids::ScopeId const parent_scope_id,ByteString const function_name,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const results = TRY((this->find_functions_with_name_in_scope(parent_scope_id,function_name,false,root_scope)));
if (!results.has_value()){
return JaktInternal::OptionalNone();
}
{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = results.value().iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::FunctionId id = _magic_value.value();
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = this->get_function(id);
if (function->type.__jakt_init_index() == 3 /* ImplicitConstructor */){
return id;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> Jakt::types::CheckedProgram::find_functions_with_name_in_scope(Jakt::ids::ScopeId const parent_scope_id,ByteString const function_name,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
return TRY((this->find_scoped_functions_with_name_in_scope(parent_scope_id,function_name,ignore_mixin_scopes,root_scope))).map([](auto& _value) { return _value.template get<0>(); });
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>> Jakt::types::CheckedProgram::find_scoped_functions_with_name_in_scope(Jakt::ids::ScopeId const parent_scope_id,ByteString const function_name,bool const ignore_mixin_scopes,JaktInternal::Optional<Jakt::ids::ScopeId> const root_scope) const {
{
JaktInternal::DynamicArray<Jakt::ids::FunctionId> result_ids = DynamicArray<Jakt::ids::FunctionId>::create_with({});
JaktInternal::Optional<Jakt::ids::ScopeId> result_scope = JaktInternal::OptionalNone();
TRY((this->template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>(parent_scope_id,[function_name, &result_ids, &result_scope, this](Jakt::types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename Jakt::utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>> {{
if (!mixin.mixin_functions){
return Jakt::utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>::Continue();
}
NonnullRefPtr<Jakt::types::Scope> const scope = this->get_scope(mixin.scope_id);
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const maybe_functions = scope->functions.get(function_name);
if (maybe_functions.has_value()){
result_ids.push_values(maybe_functions.value());
if (!result_scope.has_value()){
result_scope = mixin.scope_id;
}
}
return Jakt::utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::ids::FunctionId>,Jakt::ids::ScopeId>>::Continue();
}
}
,ignore_mixin_scopes,root_scope)));
if (!result_scope.has_value()){
return JaktInternal::OptionalNone();
}
return Tuple{result_ids, result_scope.value()};
}
}

ErrorOr<JaktInternal::Optional<Jakt::ids::StructId>> Jakt::types::CheckedProgram::check_and_extract_weak_ptr(Jakt::ids::StructId const struct_id,JaktInternal::DynamicArray<Jakt::ids::TypeId> const args) const {
{
Jakt::ids::StructId const weak_ptr_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv))));
if (struct_id.equals(weak_ptr_struct_id)){
if (args.size() != static_cast<size_t>(1ULL)){
this->compiler->panic(__jakt_format(StringView::from_string_literal("Internal error: Generic type is WeakPtr but there are not exactly 1 type parameter. There are {} parameters."sv),args.size()));
}
Jakt::ids::TypeId const inner_type_id = args.operator[](static_cast<i64>(0LL));
NonnullRefPtr<typename Jakt::types::Type> const inner_type = this->get_type(inner_type_id);
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp63 = inner_type;
if (__jakt_tmp63->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const inner_struct_id = __jakt_tmp63->as.Struct.value;
return inner_struct_id;
}
Jakt::utility::panic(__jakt_format(StringView::from_string_literal("Internal error: Inner type of WeakPtr is not a struct. It is {}."sv),inner_type));
}
else {
return JaktInternal::OptionalNone();
}

}
}

ErrorOr<ByteString> Jakt::types::CheckedProgram::type_name(Jakt::ids::TypeId const type_id,bool const debug_mode) const {
{
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(type_id);
return (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (type->common.init_common.qualifiers.is_immutable);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("const "sv));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation(""sv));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}) + ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (debug_mode);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(__jakt_format(StringView::from_string_literal("({}@{}) "sv),type_id.id,type_id.module.id) + ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("var "sv));
default:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation(""sv));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}else {return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation(""sv));
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})) + ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Never */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("never"sv));
case 10 /* F32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("f32"sv));
case 11 /* F64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("f64"sv));
case 6 /* I8 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("i8"sv));
case 7 /* I16 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("i16"sv));
case 8 /* I32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("i32"sv));
case 9 /* I64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("i64"sv));
case 2 /* U8 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("u8"sv));
case 3 /* U16 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("u16"sv));
case 4 /* U32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("u32"sv));
case 5 /* U64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("u64"sv));
case 12 /* Usize */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("usize"sv));
case 14 /* CChar */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("c_char"sv));
case 15 /* CInt */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("c_int"sv));
case 1 /* Bool */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("bool"sv));
case 0 /* Void */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("void"sv));
case 16 /* Unknown */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("unknown"sv));
case 13 /* JaktString */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("builtin(String)"sv));
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;Jakt::ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(__jakt_format(StringView::from_string_literal("{}::{}"sv),TRY((this->type_name(namespace_type,debug_mode))),name));
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_trait(id)->name);
};/*case end*/
case 30 /* Self */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Self"sv));
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& params = __jakt_match_value.params;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
{
JaktInternal::DynamicArray<ByteString> param_names = DynamicArray<ByteString>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId x = _magic_value.value();
{
param_names.push(TRY((this->type_name(x,debug_mode))));
}

}
}

ByteString const return_type = TRY((this->type_name(return_type_id,debug_mode)));
return JaktInternal::ExplicitValue<ByteString>(__jakt_format(StringView::from_string_literal("fn({}) -> {}"sv),Jakt::utility::join(param_names,ByteString::from_utf8_without_validation(", "sv)),return_type));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_enum(id).name);
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->get_struct(id).name);
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
ByteString output = __jakt_format(StringView::from_string_literal("enum {}"sv),this->get_enum(id).name);
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
Jakt::ids::TypeId arg = _magic_value.value();
{
if (!first){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(", "sv));
}
else {
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,TRY((this->type_name(arg,debug_mode))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(">"sv));
return JaktInternal::ExplicitValue<ByteString>(output);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
ByteString output = __jakt_format(StringView::from_string_literal("trait {}"sv),this->get_trait(id)->name);
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
Jakt::ids::TypeId arg = _magic_value.value();
{
if (!first){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(", "sv));
}
else {
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,TRY((this->type_name(arg,debug_mode))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(">"sv));
return JaktInternal::ExplicitValue<ByteString>(output);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::ids::StructId const array_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Array"sv))));
Jakt::ids::StructId const dictionary_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Dictionary"sv))));
Jakt::ids::StructId const optional_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Optional"sv))));
Jakt::ids::StructId const range_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Range"sv))));
Jakt::ids::StructId const set_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Set"sv))));
Jakt::ids::StructId const tuple_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("Tuple"sv))));
Jakt::ids::StructId const weak_ptr_struct_id = TRY((this->find_struct_in_prelude(ByteString::from_utf8_without_validation("WeakPtr"sv))));
ByteString output = ByteString::from_utf8_without_validation(""sv);
if (id.equals(array_struct_id)){
output = __jakt_format(StringView::from_string_literal("[{}]"sv),TRY((this->type_name(args.operator[](static_cast<i64>(0LL)),debug_mode))));
}
else if (id.equals(dictionary_struct_id)){
output = __jakt_format(StringView::from_string_literal("[{}:{}]"sv),TRY((this->type_name(args.operator[](static_cast<i64>(0LL)),debug_mode))),TRY((this->type_name(args.operator[](static_cast<i64>(1LL)),debug_mode))));
}
else if (id.equals(optional_struct_id)){
output = __jakt_format(StringView::from_string_literal("{}?"sv),TRY((this->type_name(args.operator[](static_cast<i64>(0LL)),debug_mode))));
}
else if (id.equals(range_struct_id)){
output = __jakt_format(StringView::from_string_literal("{}..{}"sv),TRY((this->type_name(args.operator[](static_cast<i64>(0LL)),debug_mode))),TRY((this->type_name(args.operator[](static_cast<i64>(0LL)),debug_mode))));
}
else if (id.equals(set_struct_id)){
output = __jakt_format(StringView::from_string_literal("{{{}}}"sv),TRY((this->type_name(args.operator[](static_cast<i64>(0LL)),debug_mode))));
}
else if (id.equals(tuple_struct_id)){
output = ByteString::from_utf8_without_validation("("sv);
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
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(", "sv));
}
else {
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,TRY((this->type_name(arg,debug_mode))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(")"sv));
}
else if (id.equals(weak_ptr_struct_id)){
output = __jakt_format(StringView::from_string_literal("weak {}"sv),TRY((this->type_name(args.operator[](static_cast<i64>(0LL)),debug_mode))));
}
else {
Jakt::types::CheckedStruct const structure = this->get_struct(id);
output = structure.name;
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
Jakt::ids::TypeId arg = _magic_value.value();
{
if (!first){
[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(", "sv));
}
else {
first = false;
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,TRY((this->type_name(arg,debug_mode))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
self = (self + rhs);
}
}
(output,ByteString::from_utf8_without_validation(">"sv));
}

return JaktInternal::ExplicitValue<ByteString>(output);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(StringView::from_string_literal("raw {}"sv),TRY((this->type_name(type_id,debug_mode)))));
};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(StringView::from_string_literal("&{}"sv),TRY((this->type_name(type_id,debug_mode)))));
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(StringView::from_string_literal("&mut {}"sv),TRY((this->type_name(type_id,debug_mode)))));
};/*case end*/
case 31 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((Jakt::types::comptime_format_impl(ByteString::from_utf8_without_validation("comptime {}"sv),DynamicArray<Jakt::types::Value>::create_with({value}).operator[](JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)}),*this))));
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

Jakt::ids::TypeId Jakt::types::CheckedProgram::find_or_add_type_id(NonnullRefPtr<typename Jakt::types::Type> const type,Jakt::ids::ModuleId const module_id,bool const only_in_current_module) {
{
if (only_in_current_module){
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::Type>> const& types = this->get_module(module_id)->types;
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(types.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t id = _magic_value.value();
{
if (types.operator[](id)->equals(type)){
return Jakt::ids::TypeId(module_id,id);
}
}

}
}

}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::Module>> _magic = this->modules.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::Module>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<Jakt::types::Module> module = _magic_value.value();
{
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(module->types.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t id = _magic_value.value();
{
if (module->types.operator[](id)->equals(type)){
return Jakt::ids::TypeId(module->id,id);
}
}

}
}

}

}
}

}

this->modules.operator[](module_id.id)->types.push(type);
return Jakt::ids::TypeId(module_id,JaktInternal::checked_sub(this->modules.operator[](module_id.id)->types.size(),static_cast<size_t>(1ULL)));
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::types::CheckedProgram::substitute_typevars_in_type(Jakt::ids::TypeId const type_id,Jakt::types::GenericInferences const generic_inferences,Jakt::ids::ModuleId const module_id) {
{
Jakt::ids::TypeId result = TRY((this->substitute_typevars_in_type_helper(type_id,generic_inferences,module_id)));
for (;;){
Jakt::ids::TypeId const fixed_point = TRY((this->substitute_typevars_in_type_helper(type_id,generic_inferences,module_id)));
if (fixed_point.equals(result)){
break;
}
else {
result = fixed_point;
}

}
return result;
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::types::CheckedProgram::specialize_type_id(Jakt::ids::TypeId const type_id,JaktInternal::DynamicArray<Jakt::ids::TypeId> const new_args,bool const replace_args,Jakt::ids::ModuleId const module_id) {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> final_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(type_id);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::ids::TypeId>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if (!replace_args){
final_args.ensure_capacity(JaktInternal::checked_add(args.size(),new_args.size()));
final_args.push_values(args);
}
final_args.push_values(new_args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if (!replace_args){
final_args.ensure_capacity(JaktInternal::checked_add(args.size(),new_args.size()));
final_args.push_values(args);
}
final_args.push_values(new_args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
if (!replace_args){
final_args.ensure_capacity(JaktInternal::checked_add(args.size(),new_args.size()));
final_args.push_values(args);
}
final_args.push_values(new_args);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
final_args.push_values(new_args);
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<Jakt::ids::TypeId>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),id,final_args),module_id,false));
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),id,final_args),module_id,false));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->find_or_add_type_id(Jakt::types::Type::GenericEnumInstance(Jakt::parser::CheckedQualifiers(false),id,final_args),module_id,false));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->find_or_add_type_id(Jakt::types::Type::GenericEnumInstance(Jakt::parser::CheckedQualifiers(false),id,final_args),module_id,false));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(this->find_or_add_type_id(Jakt::types::Type::GenericTraitInstance(Jakt::parser::CheckedQualifiers(false),id,final_args),module_id,false));
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(this->find_or_add_type_id(Jakt::types::Type::GenericTraitInstance(Jakt::parser::CheckedQualifiers(false),id,final_args),module_id,false));
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

ErrorOr<Jakt::ids::TypeId> Jakt::types::CheckedProgram::substitute_typevars_in_type_helper(Jakt::ids::TypeId const type_id,Jakt::types::GenericInferences const generic_inferences,Jakt::ids::ModuleId const module_id) {
{
NonnullRefPtr<typename Jakt::types::Type> const type_ = this->get_type(type_id);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::ids::TypeId>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */:{
JaktInternal::Optional<Jakt::ids::TypeId> const replacement_type_id = generic_inferences.get(type_id);
if (replacement_type_id.has_value()){
return replacement_type_id.value();
}
}
return JaktInternal::ExplicitValue<void>();
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;Jakt::ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::ids::TypeId const mapped_type_id = TRY((this->substitute_typevars_in_type(namespace_type,generic_inferences,module_id)));
NonnullRefPtr<typename Jakt::types::Type> const type = this->get_type(mapped_type_id);
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
new_args.ensure_capacity(args.size());
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
new_args.push(TRY((this->substitute_typevars_in_type(arg,generic_inferences,module_id))));
}

}
}

if (type->__jakt_init_index() == 18 /* TypeVariable */){
return this->find_or_add_type_id(Jakt::types::Type::Dependent(Jakt::parser::CheckedQualifiers(false),mapped_type_id,name,new_args),module_id,false);
}
Jakt::ids::TypeId const specialized_mapped_type_id = TRY((this->specialize_type_id(mapped_type_id,new_args,true,module_id)));
JaktInternal::Optional<Jakt::types::StructLikeId> const struct_like_id = Jakt::types::StructLikeId::from_type_id(specialized_mapped_type_id,*this);
if (struct_like_id.has_value()){
Jakt::ids::ScopeId const scope_id = struct_like_id.value().associated_scope_id(*this);
JaktInternal::Optional<Jakt::ids::TypeId> const found_type = TRY((this->find_type_in_scope(scope_id,name,false,JaktInternal::OptionalNone())));
if (found_type.has_value()){
Jakt::types::GenericInferences copied_inferences = generic_inferences;
if (struct_like_id.value().common.init_common.generic_arguments.has_value()){
copied_inferences.set_all(struct_like_id.value().generic_parameters_as_checked(*this),struct_like_id.value().common.init_common.generic_arguments.value());
}
return this->substitute_typevars_in_type(found_type.value(),copied_inferences,module_id);
}
return type_id;
}
else {
return type_id;
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
new_args.ensure_capacity(args.size());
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
new_args.push(TRY((this->substitute_typevars_in_type(arg,generic_inferences,module_id))));
}

}
}

return this->find_or_add_type_id(Jakt::types::Type::GenericTraitInstance(Jakt::parser::CheckedQualifiers(false),id,new_args),module_id,false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
new_args.ensure_capacity(args.size());
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
new_args.push(TRY((this->substitute_typevars_in_type(arg,generic_inferences,module_id))));
}

}
}

return this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),id,new_args),module_id,false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
new_args.ensure_capacity(args.size());
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId arg = _magic_value.value();
{
new_args.push(TRY((this->substitute_typevars_in_type(arg,generic_inferences,module_id))));
}

}
}

return this->find_or_add_type_id(Jakt::types::Type::GenericEnumInstance(Jakt::parser::CheckedQualifiers(false),id,new_args),module_id,false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const struct_ = this->get_struct(struct_id);
if (!struct_.generic_parameters.is_empty()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
new_args.ensure_capacity(struct_.generic_parameters.size());
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = struct_.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter arg = _magic_value.value();
{
new_args.push(TRY((this->substitute_typevars_in_type(arg.type_id,generic_inferences,module_id))));
}

}
}

return this->find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),struct_id,new_args),module_id,false);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = this->get_enum(enum_id);
if (!enum_.generic_parameters.is_empty()){
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_args = DynamicArray<Jakt::ids::TypeId>::create_with({});
new_args.ensure_capacity(enum_.generic_parameters.size());
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = enum_.generic_parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter arg = _magic_value.value();
{
new_args.push(TRY((this->substitute_typevars_in_type(arg.type_id,generic_inferences,module_id))));
}

}
}

return this->find_or_add_type_id(Jakt::types::Type::GenericEnumInstance(Jakt::parser::CheckedQualifiers(false),enum_id,new_args),module_id,false);
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& rawptr_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> const rawptr_type = Jakt::types::Type::RawPtr(Jakt::parser::CheckedQualifiers(false),TRY((this->substitute_typevars_in_type(rawptr_type_id,generic_inferences,module_id))));
return this->find_or_add_type_id(rawptr_type,module_id,false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& ref_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> const ref_type = Jakt::types::Type::Reference(Jakt::parser::CheckedQualifiers(false),TRY((this->substitute_typevars_in_type(ref_type_id,generic_inferences,module_id))));
return this->find_or_add_type_id(ref_type,module_id,false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& ref_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> const ref_type = Jakt::types::Type::MutableReference(Jakt::parser::CheckedQualifiers(false),TRY((this->substitute_typevars_in_type(ref_type_id,generic_inferences,module_id))));
return this->find_or_add_type_id(ref_type,module_id,false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
Jakt::ids::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> new_params = DynamicArray<Jakt::ids::TypeId>::create_with({});
new_params.ensure_capacity(params.size());
bool is_different = false;
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId param = _magic_value.value();
{
Jakt::ids::TypeId const new_param = TRY((this->substitute_typevars_in_type(param,generic_inferences,module_id)));
is_different = (is_different || (!new_param.equals(param)));
new_params.push(new_param);
}

}
}

Jakt::ids::TypeId const return_type_substitute = TRY((this->substitute_typevars_in_type(return_type_id,generic_inferences,module_id)));
is_different = (is_different || (!return_type_substitute.equals(return_type_id)));
if (!is_different){
return type_id;
}
NonnullRefPtr<Jakt::types::CheckedFunction> const previous_function = this->get_function(pseudo_function_id);
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> replacement_params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(previous_function->params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
Jakt::types::CheckedParameter const param = previous_function->params.operator[](i);
Jakt::types::CheckedParameter const new_param = Jakt::types::CheckedParameter(param.requires_label,Jakt::types::CheckedVariable::__jakt_create(param.variable->name,new_params.operator[](i),param.variable->is_mutable,param.variable->definition_span,param.variable->type_span,param.variable->visibility,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()),param.default_value_expression);
replacement_params.push(new_param);
}

}
}

NonnullRefPtr<Jakt::types::CheckedFunction> const new_function = Jakt::types::CheckedFunction::__jakt_create(previous_function->name,previous_function->name_span,previous_function->visibility,return_type_substitute,previous_function->return_type_span,replacement_params,previous_function->generics,previous_function->block,can_throw,previous_function->type,previous_function->linkage,previous_function->function_scope_id,previous_function->struct_id,previous_function->is_instantiated,previous_function->parsed_function,previous_function->is_comptime,previous_function->is_virtual,previous_function->is_override,previous_function->is_unsafe,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default(),false);
Jakt::ids::FunctionId const new_function_id = this->modules.operator[](module_id.id)->add_function(new_function);
return this->find_or_add_type_id(Jakt::types::Type::Function(Jakt::parser::CheckedQualifiers(false),new_params,can_throw,return_type_substitute,new_function_id),module_id,false);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default:{
return type_id;
}
return JaktInternal::ExplicitValue<void>();
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return type_id;
}
}

Jakt::types::CheckedProgram::CheckedProgram(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Module>> a_modules, JaktInternal::Dictionary<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> a_exports, JaktInternal::Dictionary<ByteString,Jakt::types::LoadedModule> a_loaded_modules): compiler(move(a_compiler)), modules(move(a_modules)), exports(move(a_exports)), loaded_modules(move(a_loaded_modules)){}
NonnullRefPtr<CheckedProgram> Jakt::types::CheckedProgram::__jakt_create(NonnullRefPtr<Jakt::compiler::Compiler> compiler, JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::Module>> modules, JaktInternal::Dictionary<ByteString,JaktInternal::Dictionary<Jakt::ids::TypeId,JaktInternal::DynamicArray<Jakt::parser::ParsedName>>> exports, JaktInternal::Dictionary<ByteString,Jakt::types::LoadedModule> loaded_modules) { auto o = adopt_ref(*new CheckedProgram (move(compiler), move(modules), move(exports), move(loaded_modules))); return o; }
ByteString Jakt::types::Value::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Value("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("impl: {}, ", impl);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::Value Jakt::types::Value::copy() const {
{
return Jakt::types::Value(this->impl->copy(),this->span);
}
}

ByteString Jakt::types::Value::type_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this->impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("void"sv));
case 1 /* Bool */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("bool"sv));
case 2 /* U8 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("u8"sv));
case 3 /* U16 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("u16"sv));
case 4 /* U32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("u32"sv));
case 5 /* U64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("u64"sv));
case 6 /* I8 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("i18"sv));
case 7 /* I16 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("i16"sv));
case 8 /* I32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("i32"sv));
case 9 /* I64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("i64"sv));
case 10 /* F32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("f32"sv));
case 11 /* F64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("f64"sv));
case 12 /* USize */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("usize"sv));
case 13 /* JaktString */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("String"sv));
case 14 /* StringView */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("StringView"sv));
case 15 /* CChar */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("c_char"sv));
case 16 /* CInt */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("c_int"sv));
case 17 /* Struct */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("struct <T>"sv));
case 18 /* Class */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("class <T>"sv));
case 19 /* Enum */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("enum <T>"sv));
case 20 /* JaktArray */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Array"sv));
case 21 /* JaktDictionary */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Dictionary"sv));
case 22 /* JaktSet */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Set"sv));
case 23 /* RawPtr */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("raw <T>"sv));
case 24 /* OptionalSome */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Some"sv));
case 25 /* OptionalNone */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("None"sv));
case 26 /* JaktTuple */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Tuple"sv));
case 27 /* Function */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Function"sv));
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

Jakt::types::Value Jakt::types::Value::cast(Jakt::types::Value const expected,Jakt::utility::Span const span) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *this->impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U16(infallible_integer_cast<u16>(value)),span));
case 4 /* U32 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U32(infallible_integer_cast<u32>(value)),span));
case 5 /* U64 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64(infallible_integer_cast<u64>(value)),span));
case 12 /* USize */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(infallible_integer_cast<size_t>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U32(infallible_integer_cast<u32>(value)),span));
case 5 /* U64 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64(infallible_integer_cast<u64>(value)),span));
case 12 /* USize */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(infallible_integer_cast<size_t>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64(infallible_integer_cast<u64>(value)),span));
case 12 /* USize */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(infallible_integer_cast<size_t>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(infallible_integer_cast<size_t>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I16(infallible_integer_cast<i16>(value)),span));
case 8 /* I32 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I32(infallible_integer_cast<i32>(value)),span));
case 9 /* I64 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I64(infallible_integer_cast<i64>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I32(infallible_integer_cast<i32>(value)),span));
case 9 /* I64 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I64(infallible_integer_cast<i64>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I64(infallible_integer_cast<i64>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(infallible_integer_cast<size_t>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64(infallible_integer_cast<u64>(value)),span));
case 16 /* CInt */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::CInt(infallible_integer_cast<int>(value)),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 24 /* OptionalSome */:return JaktInternal::ExplicitValue(*this);
default:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, Jakt::types::Value>{
auto&& __jakt_match_variant = *expected.impl;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */:case 25 /* OptionalNone */:return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(*this),span));
default:return JaktInternal::ExplicitValue(*this);
}/*switch end*/
}()
);
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
}
}

Jakt::types::Value::Value(NonnullRefPtr<typename Jakt::types::ValueImpl> a_impl, Jakt::utility::Span a_span): impl(move(a_impl)), span(move(a_span)){}

ByteString Jakt::types::TypecheckFunctions::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("TypecheckFunctions("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("register_function: {}", register_function);
}
builder.append(")"sv);return builder.to_string(); }
Jakt::types::TypecheckFunctions::TypecheckFunctions(Function<ErrorOr<Jakt::types::CheckedBlock>(Jakt::parser::ParsedBlock, Jakt::ids::ScopeId, Jakt::types::SafetyMode, JaktInternal::Optional<Jakt::ids::TypeId>, JaktInternal::Optional<Jakt::ids::FunctionId>)> a_block, Function<ErrorOr<Jakt::ids::FunctionId>(NonnullRefPtr<Jakt::types::CheckedFunction>)> a_register_function): block(move(a_block)), register_function(move(a_register_function)){}
NonnullRefPtr<TypecheckFunctions> Jakt::types::TypecheckFunctions::__jakt_create(Function<ErrorOr<Jakt::types::CheckedBlock>(Jakt::parser::ParsedBlock, Jakt::ids::ScopeId, Jakt::types::SafetyMode, JaktInternal::Optional<Jakt::ids::TypeId>, JaktInternal::Optional<Jakt::ids::FunctionId>)> block, Function<ErrorOr<Jakt::ids::FunctionId>(NonnullRefPtr<Jakt::types::CheckedFunction>)> register_function) { auto o = adopt_ref(*new TypecheckFunctions (move(block), move(register_function))); return o; }
ByteString Jakt::types::StructOrEnumId::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Struct */: {
builder.append("StructOrEnumId::Struct"sv);
[[maybe_unused]] auto const& that = this->as.Struct;
builder.appendff("({})", that.value);
break;}
case 1 /* Enum */: {
builder.append("StructOrEnumId::Enum"sv);
[[maybe_unused]] auto const& that = this->as.Enum;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] StructOrEnumId StructOrEnumId::Struct(Jakt::ids::StructId value){
StructOrEnumId __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Struct.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StructOrEnumId StructOrEnumId::Enum(Jakt::ids::EnumId value){
StructOrEnumId __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Enum.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
StructOrEnumId& StructOrEnumId::operator=(StructOrEnumId const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 1 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
this->as.Struct.value = rhs.as.Struct.value;
break;
case 1 /* Enum */:
this->as.Enum.value = rhs.as.Enum.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
StructOrEnumId::StructOrEnumId(StructOrEnumId const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 1 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
StructOrEnumId& StructOrEnumId::operator=(StructOrEnumId &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 1 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
this->as.Struct.value = move(rhs.as.Struct.value);
break;
case 1 /* Enum */:
this->as.Enum.value = move(rhs.as.Enum.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
StructOrEnumId::StructOrEnumId(StructOrEnumId &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 1 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
StructOrEnumId::~StructOrEnumId(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void StructOrEnumId::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Struct */:this->as.Struct.value.~StructId();
break;
case 1 /* Enum */:this->as.Enum.value.~EnumId();
break;
}
}
ByteString Jakt::types::StructLikeId::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Struct */: {
builder.append("StructLikeId::Struct"sv);
[[maybe_unused]] auto const& that = this->as.Struct;
builder.appendff("({})", that.value);
break;}
case 1 /* Enum */: {
builder.append("StructLikeId::Enum"sv);
[[maybe_unused]] auto const& that = this->as.Enum;
builder.appendff("({})", that.value);
break;}
case 2 /* Trait */: {
builder.append("StructLikeId::Trait"sv);
[[maybe_unused]] auto const& that = this->as.Trait;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] StructLikeId StructLikeId::Struct(JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> generic_arguments, Jakt::ids::StructId value){
StructLikeId __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.generic_arguments) (decltype(generic_arguments))(move(generic_arguments));
new (&__jakt_uninit_enum.as.Struct.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StructLikeId StructLikeId::Enum(JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> generic_arguments, Jakt::ids::EnumId value){
StructLikeId __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.generic_arguments) (decltype(generic_arguments))(move(generic_arguments));
new (&__jakt_uninit_enum.as.Enum.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StructLikeId StructLikeId::Trait(JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::TypeId>> generic_arguments, Jakt::ids::TraitId value){
StructLikeId __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.common.init_common.generic_arguments) (decltype(generic_arguments))(move(generic_arguments));
new (&__jakt_uninit_enum.as.Trait.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
StructLikeId& StructLikeId::operator=(StructLikeId const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.generic_arguments = rhs.common.init_common.generic_arguments;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 1 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 2 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
this->as.Struct.value = rhs.as.Struct.value;
break;
case 1 /* Enum */:
this->as.Enum.value = rhs.as.Enum.value;
break;
case 2 /* Trait */:
this->as.Trait.value = rhs.as.Trait.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
StructLikeId::StructLikeId(StructLikeId const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.generic_arguments) (decltype(this->common.init_common.generic_arguments))(rhs.common.init_common.generic_arguments);
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 1 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 2 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
StructLikeId& StructLikeId::operator=(StructLikeId &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.generic_arguments = move(rhs.common.init_common.generic_arguments);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 1 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 2 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
this->as.Struct.value = move(rhs.as.Struct.value);
break;
case 1 /* Enum */:
this->as.Enum.value = move(rhs.as.Enum.value);
break;
case 2 /* Trait */:
this->as.Trait.value = move(rhs.as.Trait.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
StructLikeId::StructLikeId(StructLikeId &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.generic_arguments) (decltype(this->common.init_common.generic_arguments))(move(rhs.common.init_common.generic_arguments));
switch (rhs.__jakt_init_index()) {
case 0 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 1 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 2 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
StructLikeId::~StructLikeId(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.generic_arguments.~Optional();
this->__jakt_destroy_variant(); }
void StructLikeId::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Struct */:this->as.Struct.value.~StructId();
break;
case 1 /* Enum */:this->as.Enum.value.~EnumId();
break;
case 2 /* Trait */:this->as.Trait.value.~TraitId();
break;
}
}
JaktInternal::DynamicArray<Jakt::ids::TypeId> Jakt::types::StructLikeId::generic_parameters(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const {
{
JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> const parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>, JaktInternal::DynamicArray<Jakt::ids::TypeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_struct(id).generic_parameters);
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_enum(id).generic_parameters);
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_trait(id)->generic_parameters);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::ids::TypeId> result = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = parameters.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedGenericParameter parameter = _magic_value.value();
{
result.push(parameter.type_id);
}

}
}

return result;
}
}

JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter> Jakt::types::StructLikeId::generic_parameters_as_checked(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>, JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_struct(id).generic_parameters);
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_enum(id).generic_parameters);
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_trait(id)->generic_parameters);
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

Jakt::ids::ScopeId Jakt::types::StructLikeId::scope_id(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId, Jakt::ids::ScopeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_struct(id).scope_id);
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_enum(id).scope_id);
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_trait(id)->scope_id);
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

Jakt::ids::TypeId Jakt::types::StructLikeId::specialized_by(JaktInternal::DynamicArray<Jakt::ids::TypeId> const arguments,NonnullRefPtr<Jakt::types::CheckedProgram>& program,Jakt::ids::ModuleId const module_id,Jakt::parser::CheckedQualifiers const qualifiers) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, Jakt::ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->find_or_add_type_id(Jakt::types::Type::GenericInstance(qualifiers,id,arguments),module_id,false));
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->find_or_add_type_id(Jakt::types::Type::GenericEnumInstance(qualifiers,id,arguments),module_id,false));
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->find_or_add_type_id(Jakt::types::Type::GenericTraitInstance(qualifiers,id,arguments),module_id,false));
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

JaktInternal::Optional<Jakt::types::StructLikeId> Jakt::types::StructLikeId::from_type_id(Jakt::ids::TypeId const type_id,NonnullRefPtr<Jakt::types::CheckedProgram> const& program) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::StructLikeId>, JaktInternal::Optional<Jakt::types::StructLikeId>>{
auto&& __jakt_match_variant = *program->get_type(type_id);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Struct(args,struct_id));
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Struct(args,struct_id));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Enum(args,enum_id));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Enum(args,enum_id));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& trait_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Trait(args,trait_id));
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& trait_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
return JaktInternal::ExplicitValue(Jakt::types::StructLikeId::Trait(args,trait_id));
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

Jakt::ids::ScopeId Jakt::types::StructLikeId::associated_scope_id(NonnullRefPtr<Jakt::types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::ScopeId, Jakt::ids::ScopeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_struct(id).scope_id);
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_enum(id).scope_id);
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_trait(id)->scope_id);
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

ByteString Jakt::types::SafetyMode::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Safe */: {
return ByteString("SafetyMode::Safe"sv);
break;}
case 1 /* Unsafe */: {
return ByteString("SafetyMode::Unsafe"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] SafetyMode SafetyMode::Safe(){
SafetyMode __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] SafetyMode SafetyMode::Unsafe(){
SafetyMode __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
SafetyMode& SafetyMode::operator=(SafetyMode const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Safe */:
break;
case 1 /* Unsafe */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Safe */:
break;
case 1 /* Unsafe */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
SafetyMode::SafetyMode(SafetyMode const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Safe */:
break;
case 1 /* Unsafe */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
SafetyMode& SafetyMode::operator=(SafetyMode &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Safe */:
break;
case 1 /* Unsafe */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Safe */:
break;
case 1 /* Unsafe */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
SafetyMode::SafetyMode(SafetyMode &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Safe */:
break;
case 1 /* Unsafe */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
SafetyMode::~SafetyMode(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void SafetyMode::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Safe */:break;
case 1 /* Unsafe */:break;
}
}
ByteString Jakt::types::BuiltinType::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Void */: {
return ByteString("BuiltinType::Void"sv);
break;}
case 1 /* Bool */: {
return ByteString("BuiltinType::Bool"sv);
break;}
case 2 /* U8 */: {
return ByteString("BuiltinType::U8"sv);
break;}
case 3 /* U16 */: {
return ByteString("BuiltinType::U16"sv);
break;}
case 4 /* U32 */: {
return ByteString("BuiltinType::U32"sv);
break;}
case 5 /* U64 */: {
return ByteString("BuiltinType::U64"sv);
break;}
case 6 /* I8 */: {
return ByteString("BuiltinType::I8"sv);
break;}
case 7 /* I16 */: {
return ByteString("BuiltinType::I16"sv);
break;}
case 8 /* I32 */: {
return ByteString("BuiltinType::I32"sv);
break;}
case 9 /* I64 */: {
return ByteString("BuiltinType::I64"sv);
break;}
case 10 /* F32 */: {
return ByteString("BuiltinType::F32"sv);
break;}
case 11 /* F64 */: {
return ByteString("BuiltinType::F64"sv);
break;}
case 12 /* Usize */: {
return ByteString("BuiltinType::Usize"sv);
break;}
case 13 /* JaktString */: {
return ByteString("BuiltinType::JaktString"sv);
break;}
case 14 /* CChar */: {
return ByteString("BuiltinType::CChar"sv);
break;}
case 15 /* CInt */: {
return ByteString("BuiltinType::CInt"sv);
break;}
case 16 /* Unknown */: {
return ByteString("BuiltinType::Unknown"sv);
break;}
case 17 /* Never */: {
return ByteString("BuiltinType::Never"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] BuiltinType BuiltinType::Void(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::Bool(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::U8(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::U16(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::U32(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::U64(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::I8(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::I16(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::I32(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::I64(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::F32(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::F64(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::Usize(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::JaktString(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 14;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::CChar(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 15;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::CInt(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 16;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::Unknown(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 17;
return __jakt_uninit_enum;
}
[[nodiscard]] BuiltinType BuiltinType::Never(){
BuiltinType __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 18;
return __jakt_uninit_enum;
}
BuiltinType& BuiltinType::operator=(BuiltinType const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BuiltinType::BuiltinType(BuiltinType const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
BuiltinType& BuiltinType::operator=(BuiltinType &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BuiltinType::BuiltinType(BuiltinType &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
BuiltinType::~BuiltinType(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void BuiltinType::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Void */:break;
case 1 /* Bool */:break;
case 2 /* U8 */:break;
case 3 /* U16 */:break;
case 4 /* U32 */:break;
case 5 /* U64 */:break;
case 6 /* I8 */:break;
case 7 /* I16 */:break;
case 8 /* I32 */:break;
case 9 /* I64 */:break;
case 10 /* F32 */:break;
case 11 /* F64 */:break;
case 12 /* Usize */:break;
case 13 /* JaktString */:break;
case 14 /* CChar */:break;
case 15 /* CInt */:break;
case 16 /* Unknown */:break;
case 17 /* Never */:break;
}
}
size_t Jakt::types::BuiltinType::id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
case 1 /* Bool */:return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
case 2 /* U8 */:return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
case 3 /* U16 */:return JaktInternal::ExplicitValue(static_cast<size_t>(3ULL));
case 4 /* U32 */:return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
case 5 /* U64 */:return JaktInternal::ExplicitValue(static_cast<size_t>(5ULL));
case 6 /* I8 */:return JaktInternal::ExplicitValue(static_cast<size_t>(6ULL));
case 7 /* I16 */:return JaktInternal::ExplicitValue(static_cast<size_t>(7ULL));
case 8 /* I32 */:return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
case 9 /* I64 */:return JaktInternal::ExplicitValue(static_cast<size_t>(9ULL));
case 10 /* F32 */:return JaktInternal::ExplicitValue(static_cast<size_t>(10ULL));
case 11 /* F64 */:return JaktInternal::ExplicitValue(static_cast<size_t>(11ULL));
case 12 /* Usize */:return JaktInternal::ExplicitValue(static_cast<size_t>(12ULL));
case 13 /* JaktString */:return JaktInternal::ExplicitValue(static_cast<size_t>(13ULL));
case 14 /* CChar */:return JaktInternal::ExplicitValue(static_cast<size_t>(14ULL));
case 15 /* CInt */:return JaktInternal::ExplicitValue(static_cast<size_t>(15ULL));
case 16 /* Unknown */:return JaktInternal::ExplicitValue(static_cast<size_t>(16ULL));
case 17 /* Never */:return JaktInternal::ExplicitValue(static_cast<size_t>(17ULL));
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ByteString Jakt::types::BuiltinType::constructor_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Void"sv));
case 1 /* Bool */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Bool"sv));
case 2 /* U8 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("U8"sv));
case 3 /* U16 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("U16"sv));
case 4 /* U32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("U32"sv));
case 5 /* U64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("U64"sv));
case 6 /* I8 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("I8"sv));
case 7 /* I16 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("I16"sv));
case 8 /* I32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("I32"sv));
case 9 /* I64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("I64"sv));
case 10 /* F32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("F32"sv));
case 11 /* F64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("F64"sv));
case 12 /* Usize */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Usize"sv));
case 13 /* JaktString */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("JaktString"sv));
case 14 /* CChar */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("CChar"sv));
case 15 /* CInt */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("CInt"sv));
case 16 /* Unknown */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Unknown"sv));
case 17 /* Never */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Never"sv));
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ByteString Jakt::types::Type::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Void */: {
return ByteString("Type::Void"sv);
break;}
case 1 /* Bool */: {
return ByteString("Type::Bool"sv);
break;}
case 2 /* U8 */: {
return ByteString("Type::U8"sv);
break;}
case 3 /* U16 */: {
return ByteString("Type::U16"sv);
break;}
case 4 /* U32 */: {
return ByteString("Type::U32"sv);
break;}
case 5 /* U64 */: {
return ByteString("Type::U64"sv);
break;}
case 6 /* I8 */: {
return ByteString("Type::I8"sv);
break;}
case 7 /* I16 */: {
return ByteString("Type::I16"sv);
break;}
case 8 /* I32 */: {
return ByteString("Type::I32"sv);
break;}
case 9 /* I64 */: {
return ByteString("Type::I64"sv);
break;}
case 10 /* F32 */: {
return ByteString("Type::F32"sv);
break;}
case 11 /* F64 */: {
return ByteString("Type::F64"sv);
break;}
case 12 /* Usize */: {
return ByteString("Type::Usize"sv);
break;}
case 13 /* JaktString */: {
return ByteString("Type::JaktString"sv);
break;}
case 14 /* CChar */: {
return ByteString("Type::CChar"sv);
break;}
case 15 /* CInt */: {
return ByteString("Type::CInt"sv);
break;}
case 16 /* Unknown */: {
return ByteString("Type::Unknown"sv);
break;}
case 17 /* Never */: {
return ByteString("Type::Never"sv);
break;}
case 18 /* TypeVariable */: {
builder.append("Type::TypeVariable"sv);
[[maybe_unused]] auto const& that = this->as.TypeVariable;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_implementations: {}, ", that.trait_implementations);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_value: {}", that.is_value);
}
builder.append(")"sv);
break;}
case 19 /* Dependent */: {
builder.append("Type::Dependent"sv);
[[maybe_unused]] auto const& that = this->as.Dependent;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespace_type: {}, ", that.namespace_type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}", that.args);
}
builder.append(")"sv);
break;}
case 20 /* GenericInstance */: {
builder.append("Type::GenericInstance"sv);
[[maybe_unused]] auto const& that = this->as.GenericInstance;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}, ", that.id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}", that.args);
}
builder.append(")"sv);
break;}
case 21 /* GenericEnumInstance */: {
builder.append("Type::GenericEnumInstance"sv);
[[maybe_unused]] auto const& that = this->as.GenericEnumInstance;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}, ", that.id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}", that.args);
}
builder.append(")"sv);
break;}
case 22 /* GenericTraitInstance */: {
builder.append("Type::GenericTraitInstance"sv);
[[maybe_unused]] auto const& that = this->as.GenericTraitInstance;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("id: {}, ", that.id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}", that.args);
}
builder.append(")"sv);
break;}
case 23 /* Struct */: {
builder.append("Type::Struct"sv);
[[maybe_unused]] auto const& that = this->as.Struct;
builder.appendff("({})", that.value);
break;}
case 24 /* Enum */: {
builder.append("Type::Enum"sv);
[[maybe_unused]] auto const& that = this->as.Enum;
builder.appendff("({})", that.value);
break;}
case 25 /* RawPtr */: {
builder.append("Type::RawPtr"sv);
[[maybe_unused]] auto const& that = this->as.RawPtr;
builder.appendff("({})", that.value);
break;}
case 26 /* Trait */: {
builder.append("Type::Trait"sv);
[[maybe_unused]] auto const& that = this->as.Trait;
builder.appendff("({})", that.value);
break;}
case 27 /* Reference */: {
builder.append("Type::Reference"sv);
[[maybe_unused]] auto const& that = this->as.Reference;
builder.appendff("({})", that.value);
break;}
case 28 /* MutableReference */: {
builder.append("Type::MutableReference"sv);
[[maybe_unused]] auto const& that = this->as.MutableReference;
builder.appendff("({})", that.value);
break;}
case 29 /* Function */: {
builder.append("Type::Function"sv);
[[maybe_unused]] auto const& that = this->as.Function;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("qualifiers: {}, ", this->common.init_common.qualifiers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", that.params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", that.can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type_id: {}, ", that.return_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("pseudo_function_id: {}", that.pseudo_function_id);
}
builder.append(")"sv);
break;}
case 30 /* Self */: {
return ByteString("Type::Self"sv);
break;}
case 31 /* Const */: {
builder.append("Type::Const"sv);
[[maybe_unused]] auto const& that = this->as.Const;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<Type> Type::Void(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Bool(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::U8(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::U16(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::U32(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::U64(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::I8(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::I16(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::I32(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::I64(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::F32(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::F64(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Usize(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::JaktString(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::CChar(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::CInt(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 16;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Unknown(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 17;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Never(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 18;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::TypeVariable(Jakt::parser::CheckedQualifiers qualifiers, ByteString name, JaktInternal::DynamicArray<Jakt::ids::TypeId> trait_implementations, bool is_value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 19;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.TypeVariable.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.TypeVariable.trait_implementations) (decltype(trait_implementations))(move(trait_implementations));
new (&__jakt_uninit_enum->as.TypeVariable.is_value) (decltype(is_value))(move(is_value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Dependent(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TypeId namespace_type, ByteString name, JaktInternal::DynamicArray<Jakt::ids::TypeId> args){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 20;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Dependent.namespace_type) (decltype(namespace_type))(move(namespace_type));
new (&__jakt_uninit_enum->as.Dependent.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.Dependent.args) (decltype(args))(move(args));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::GenericInstance(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::StructId id, JaktInternal::DynamicArray<Jakt::ids::TypeId> args){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 21;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.GenericInstance.id) (decltype(id))(move(id));
new (&__jakt_uninit_enum->as.GenericInstance.args) (decltype(args))(move(args));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::GenericEnumInstance(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::EnumId id, JaktInternal::DynamicArray<Jakt::ids::TypeId> args){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 22;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.GenericEnumInstance.id) (decltype(id))(move(id));
new (&__jakt_uninit_enum->as.GenericEnumInstance.args) (decltype(args))(move(args));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::GenericTraitInstance(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TraitId id, JaktInternal::DynamicArray<Jakt::ids::TypeId> args){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 23;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.GenericTraitInstance.id) (decltype(id))(move(id));
new (&__jakt_uninit_enum->as.GenericTraitInstance.args) (decltype(args))(move(args));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Struct(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::StructId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 24;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Struct.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Enum(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::EnumId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 25;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Enum.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::RawPtr(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TypeId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 26;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.RawPtr.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Trait(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TraitId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 27;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Trait.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Reference(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TypeId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 28;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Reference.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::MutableReference(Jakt::parser::CheckedQualifiers qualifiers, Jakt::ids::TypeId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 29;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.MutableReference.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Function(Jakt::parser::CheckedQualifiers qualifiers, JaktInternal::DynamicArray<Jakt::ids::TypeId> params, bool can_throw, Jakt::ids::TypeId return_type_id, Jakt::ids::FunctionId pseudo_function_id){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 30;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Function.params) (decltype(params))(move(params));
new (&__jakt_uninit_enum->as.Function.can_throw) (decltype(can_throw))(move(can_throw));
new (&__jakt_uninit_enum->as.Function.return_type_id) (decltype(return_type_id))(move(return_type_id));
new (&__jakt_uninit_enum->as.Function.pseudo_function_id) (decltype(pseudo_function_id))(move(pseudo_function_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Self(Jakt::parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 31;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Const(Jakt::parser::CheckedQualifiers qualifiers, Jakt::types::Value value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 32;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Const.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
Type& Type::operator=(Type const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.qualifiers = rhs.common.init_common.qualifiers;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
case 18 /* TypeVariable */:
new (&this->as.TypeVariable.name) (decltype(this->as.TypeVariable.name))(rhs.as.TypeVariable.name);
new (&this->as.TypeVariable.trait_implementations) (decltype(this->as.TypeVariable.trait_implementations))(rhs.as.TypeVariable.trait_implementations);
new (&this->as.TypeVariable.is_value) (decltype(this->as.TypeVariable.is_value))(rhs.as.TypeVariable.is_value);
break;
case 19 /* Dependent */:
new (&this->as.Dependent.namespace_type) (decltype(this->as.Dependent.namespace_type))(rhs.as.Dependent.namespace_type);
new (&this->as.Dependent.name) (decltype(this->as.Dependent.name))(rhs.as.Dependent.name);
new (&this->as.Dependent.args) (decltype(this->as.Dependent.args))(rhs.as.Dependent.args);
break;
case 20 /* GenericInstance */:
new (&this->as.GenericInstance.id) (decltype(this->as.GenericInstance.id))(rhs.as.GenericInstance.id);
new (&this->as.GenericInstance.args) (decltype(this->as.GenericInstance.args))(rhs.as.GenericInstance.args);
break;
case 21 /* GenericEnumInstance */:
new (&this->as.GenericEnumInstance.id) (decltype(this->as.GenericEnumInstance.id))(rhs.as.GenericEnumInstance.id);
new (&this->as.GenericEnumInstance.args) (decltype(this->as.GenericEnumInstance.args))(rhs.as.GenericEnumInstance.args);
break;
case 22 /* GenericTraitInstance */:
new (&this->as.GenericTraitInstance.id) (decltype(this->as.GenericTraitInstance.id))(rhs.as.GenericTraitInstance.id);
new (&this->as.GenericTraitInstance.args) (decltype(this->as.GenericTraitInstance.args))(rhs.as.GenericTraitInstance.args);
break;
case 23 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 24 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 25 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(rhs.as.RawPtr.value);
break;
case 26 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
case 27 /* Reference */:
new (&this->as.Reference.value) (decltype(this->as.Reference.value))(rhs.as.Reference.value);
break;
case 28 /* MutableReference */:
new (&this->as.MutableReference.value) (decltype(this->as.MutableReference.value))(rhs.as.MutableReference.value);
break;
case 29 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(rhs.as.Function.return_type_id);
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(rhs.as.Function.pseudo_function_id);
break;
case 30 /* Self */:
break;
case 31 /* Const */:
new (&this->as.Const.value) (decltype(this->as.Const.value))(rhs.as.Const.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
case 18 /* TypeVariable */:
this->as.TypeVariable.name = rhs.as.TypeVariable.name;
this->as.TypeVariable.trait_implementations = rhs.as.TypeVariable.trait_implementations;
this->as.TypeVariable.is_value = rhs.as.TypeVariable.is_value;
break;
case 19 /* Dependent */:
this->as.Dependent.namespace_type = rhs.as.Dependent.namespace_type;
this->as.Dependent.name = rhs.as.Dependent.name;
this->as.Dependent.args = rhs.as.Dependent.args;
break;
case 20 /* GenericInstance */:
this->as.GenericInstance.id = rhs.as.GenericInstance.id;
this->as.GenericInstance.args = rhs.as.GenericInstance.args;
break;
case 21 /* GenericEnumInstance */:
this->as.GenericEnumInstance.id = rhs.as.GenericEnumInstance.id;
this->as.GenericEnumInstance.args = rhs.as.GenericEnumInstance.args;
break;
case 22 /* GenericTraitInstance */:
this->as.GenericTraitInstance.id = rhs.as.GenericTraitInstance.id;
this->as.GenericTraitInstance.args = rhs.as.GenericTraitInstance.args;
break;
case 23 /* Struct */:
this->as.Struct.value = rhs.as.Struct.value;
break;
case 24 /* Enum */:
this->as.Enum.value = rhs.as.Enum.value;
break;
case 25 /* RawPtr */:
this->as.RawPtr.value = rhs.as.RawPtr.value;
break;
case 26 /* Trait */:
this->as.Trait.value = rhs.as.Trait.value;
break;
case 27 /* Reference */:
this->as.Reference.value = rhs.as.Reference.value;
break;
case 28 /* MutableReference */:
this->as.MutableReference.value = rhs.as.MutableReference.value;
break;
case 29 /* Function */:
this->as.Function.params = rhs.as.Function.params;
this->as.Function.can_throw = rhs.as.Function.can_throw;
this->as.Function.return_type_id = rhs.as.Function.return_type_id;
this->as.Function.pseudo_function_id = rhs.as.Function.pseudo_function_id;
break;
case 30 /* Self */:
break;
case 31 /* Const */:
this->as.Const.value = rhs.as.Const.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Type::Type(Type const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.qualifiers) (decltype(this->common.init_common.qualifiers))(rhs.common.init_common.qualifiers);
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
case 18 /* TypeVariable */:
new (&this->as.TypeVariable.name) (decltype(this->as.TypeVariable.name))(rhs.as.TypeVariable.name);
new (&this->as.TypeVariable.trait_implementations) (decltype(this->as.TypeVariable.trait_implementations))(rhs.as.TypeVariable.trait_implementations);
new (&this->as.TypeVariable.is_value) (decltype(this->as.TypeVariable.is_value))(rhs.as.TypeVariable.is_value);
break;
case 19 /* Dependent */:
new (&this->as.Dependent.namespace_type) (decltype(this->as.Dependent.namespace_type))(rhs.as.Dependent.namespace_type);
new (&this->as.Dependent.name) (decltype(this->as.Dependent.name))(rhs.as.Dependent.name);
new (&this->as.Dependent.args) (decltype(this->as.Dependent.args))(rhs.as.Dependent.args);
break;
case 20 /* GenericInstance */:
new (&this->as.GenericInstance.id) (decltype(this->as.GenericInstance.id))(rhs.as.GenericInstance.id);
new (&this->as.GenericInstance.args) (decltype(this->as.GenericInstance.args))(rhs.as.GenericInstance.args);
break;
case 21 /* GenericEnumInstance */:
new (&this->as.GenericEnumInstance.id) (decltype(this->as.GenericEnumInstance.id))(rhs.as.GenericEnumInstance.id);
new (&this->as.GenericEnumInstance.args) (decltype(this->as.GenericEnumInstance.args))(rhs.as.GenericEnumInstance.args);
break;
case 22 /* GenericTraitInstance */:
new (&this->as.GenericTraitInstance.id) (decltype(this->as.GenericTraitInstance.id))(rhs.as.GenericTraitInstance.id);
new (&this->as.GenericTraitInstance.args) (decltype(this->as.GenericTraitInstance.args))(rhs.as.GenericTraitInstance.args);
break;
case 23 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 24 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 25 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(rhs.as.RawPtr.value);
break;
case 26 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
case 27 /* Reference */:
new (&this->as.Reference.value) (decltype(this->as.Reference.value))(rhs.as.Reference.value);
break;
case 28 /* MutableReference */:
new (&this->as.MutableReference.value) (decltype(this->as.MutableReference.value))(rhs.as.MutableReference.value);
break;
case 29 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(rhs.as.Function.return_type_id);
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(rhs.as.Function.pseudo_function_id);
break;
case 30 /* Self */:
break;
case 31 /* Const */:
new (&this->as.Const.value) (decltype(this->as.Const.value))(rhs.as.Const.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Type& Type::operator=(Type &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.qualifiers = move(rhs.common.init_common.qualifiers);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
case 18 /* TypeVariable */:
new (&this->as.TypeVariable.name) (decltype(this->as.TypeVariable.name))(move(rhs.as.TypeVariable.name));
new (&this->as.TypeVariable.trait_implementations) (decltype(this->as.TypeVariable.trait_implementations))(move(rhs.as.TypeVariable.trait_implementations));
new (&this->as.TypeVariable.is_value) (decltype(this->as.TypeVariable.is_value))(move(rhs.as.TypeVariable.is_value));
break;
case 19 /* Dependent */:
new (&this->as.Dependent.namespace_type) (decltype(this->as.Dependent.namespace_type))(move(rhs.as.Dependent.namespace_type));
new (&this->as.Dependent.name) (decltype(this->as.Dependent.name))(move(rhs.as.Dependent.name));
new (&this->as.Dependent.args) (decltype(this->as.Dependent.args))(move(rhs.as.Dependent.args));
break;
case 20 /* GenericInstance */:
new (&this->as.GenericInstance.id) (decltype(this->as.GenericInstance.id))(move(rhs.as.GenericInstance.id));
new (&this->as.GenericInstance.args) (decltype(this->as.GenericInstance.args))(move(rhs.as.GenericInstance.args));
break;
case 21 /* GenericEnumInstance */:
new (&this->as.GenericEnumInstance.id) (decltype(this->as.GenericEnumInstance.id))(move(rhs.as.GenericEnumInstance.id));
new (&this->as.GenericEnumInstance.args) (decltype(this->as.GenericEnumInstance.args))(move(rhs.as.GenericEnumInstance.args));
break;
case 22 /* GenericTraitInstance */:
new (&this->as.GenericTraitInstance.id) (decltype(this->as.GenericTraitInstance.id))(move(rhs.as.GenericTraitInstance.id));
new (&this->as.GenericTraitInstance.args) (decltype(this->as.GenericTraitInstance.args))(move(rhs.as.GenericTraitInstance.args));
break;
case 23 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 24 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 25 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(move(rhs.as.RawPtr.value));
break;
case 26 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
case 27 /* Reference */:
new (&this->as.Reference.value) (decltype(this->as.Reference.value))(move(rhs.as.Reference.value));
break;
case 28 /* MutableReference */:
new (&this->as.MutableReference.value) (decltype(this->as.MutableReference.value))(move(rhs.as.MutableReference.value));
break;
case 29 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(move(rhs.as.Function.return_type_id));
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(move(rhs.as.Function.pseudo_function_id));
break;
case 30 /* Self */:
break;
case 31 /* Const */:
new (&this->as.Const.value) (decltype(this->as.Const.value))(move(rhs.as.Const.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
case 18 /* TypeVariable */:
this->as.TypeVariable.name = move(rhs.as.TypeVariable.name);
this->as.TypeVariable.trait_implementations = move(rhs.as.TypeVariable.trait_implementations);
this->as.TypeVariable.is_value = move(rhs.as.TypeVariable.is_value);
break;
case 19 /* Dependent */:
this->as.Dependent.namespace_type = move(rhs.as.Dependent.namespace_type);
this->as.Dependent.name = move(rhs.as.Dependent.name);
this->as.Dependent.args = move(rhs.as.Dependent.args);
break;
case 20 /* GenericInstance */:
this->as.GenericInstance.id = move(rhs.as.GenericInstance.id);
this->as.GenericInstance.args = move(rhs.as.GenericInstance.args);
break;
case 21 /* GenericEnumInstance */:
this->as.GenericEnumInstance.id = move(rhs.as.GenericEnumInstance.id);
this->as.GenericEnumInstance.args = move(rhs.as.GenericEnumInstance.args);
break;
case 22 /* GenericTraitInstance */:
this->as.GenericTraitInstance.id = move(rhs.as.GenericTraitInstance.id);
this->as.GenericTraitInstance.args = move(rhs.as.GenericTraitInstance.args);
break;
case 23 /* Struct */:
this->as.Struct.value = move(rhs.as.Struct.value);
break;
case 24 /* Enum */:
this->as.Enum.value = move(rhs.as.Enum.value);
break;
case 25 /* RawPtr */:
this->as.RawPtr.value = move(rhs.as.RawPtr.value);
break;
case 26 /* Trait */:
this->as.Trait.value = move(rhs.as.Trait.value);
break;
case 27 /* Reference */:
this->as.Reference.value = move(rhs.as.Reference.value);
break;
case 28 /* MutableReference */:
this->as.MutableReference.value = move(rhs.as.MutableReference.value);
break;
case 29 /* Function */:
this->as.Function.params = move(rhs.as.Function.params);
this->as.Function.can_throw = move(rhs.as.Function.can_throw);
this->as.Function.return_type_id = move(rhs.as.Function.return_type_id);
this->as.Function.pseudo_function_id = move(rhs.as.Function.pseudo_function_id);
break;
case 30 /* Self */:
break;
case 31 /* Const */:
this->as.Const.value = move(rhs.as.Const.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Type::Type(Type &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.qualifiers) (decltype(this->common.init_common.qualifiers))(move(rhs.common.init_common.qualifiers));
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
break;
case 2 /* U8 */:
break;
case 3 /* U16 */:
break;
case 4 /* U32 */:
break;
case 5 /* U64 */:
break;
case 6 /* I8 */:
break;
case 7 /* I16 */:
break;
case 8 /* I32 */:
break;
case 9 /* I64 */:
break;
case 10 /* F32 */:
break;
case 11 /* F64 */:
break;
case 12 /* Usize */:
break;
case 13 /* JaktString */:
break;
case 14 /* CChar */:
break;
case 15 /* CInt */:
break;
case 16 /* Unknown */:
break;
case 17 /* Never */:
break;
case 18 /* TypeVariable */:
new (&this->as.TypeVariable.name) (decltype(this->as.TypeVariable.name))(move(rhs.as.TypeVariable.name));
new (&this->as.TypeVariable.trait_implementations) (decltype(this->as.TypeVariable.trait_implementations))(move(rhs.as.TypeVariable.trait_implementations));
new (&this->as.TypeVariable.is_value) (decltype(this->as.TypeVariable.is_value))(move(rhs.as.TypeVariable.is_value));
break;
case 19 /* Dependent */:
new (&this->as.Dependent.namespace_type) (decltype(this->as.Dependent.namespace_type))(move(rhs.as.Dependent.namespace_type));
new (&this->as.Dependent.name) (decltype(this->as.Dependent.name))(move(rhs.as.Dependent.name));
new (&this->as.Dependent.args) (decltype(this->as.Dependent.args))(move(rhs.as.Dependent.args));
break;
case 20 /* GenericInstance */:
new (&this->as.GenericInstance.id) (decltype(this->as.GenericInstance.id))(move(rhs.as.GenericInstance.id));
new (&this->as.GenericInstance.args) (decltype(this->as.GenericInstance.args))(move(rhs.as.GenericInstance.args));
break;
case 21 /* GenericEnumInstance */:
new (&this->as.GenericEnumInstance.id) (decltype(this->as.GenericEnumInstance.id))(move(rhs.as.GenericEnumInstance.id));
new (&this->as.GenericEnumInstance.args) (decltype(this->as.GenericEnumInstance.args))(move(rhs.as.GenericEnumInstance.args));
break;
case 22 /* GenericTraitInstance */:
new (&this->as.GenericTraitInstance.id) (decltype(this->as.GenericTraitInstance.id))(move(rhs.as.GenericTraitInstance.id));
new (&this->as.GenericTraitInstance.args) (decltype(this->as.GenericTraitInstance.args))(move(rhs.as.GenericTraitInstance.args));
break;
case 23 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 24 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 25 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(move(rhs.as.RawPtr.value));
break;
case 26 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
case 27 /* Reference */:
new (&this->as.Reference.value) (decltype(this->as.Reference.value))(move(rhs.as.Reference.value));
break;
case 28 /* MutableReference */:
new (&this->as.MutableReference.value) (decltype(this->as.MutableReference.value))(move(rhs.as.MutableReference.value));
break;
case 29 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(move(rhs.as.Function.return_type_id));
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(move(rhs.as.Function.pseudo_function_id));
break;
case 30 /* Self */:
break;
case 31 /* Const */:
new (&this->as.Const.value) (decltype(this->as.Const.value))(move(rhs.as.Const.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Type::~Type(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.qualifiers.~CheckedQualifiers();
this->__jakt_destroy_variant(); }
void Type::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Void */:break;
case 1 /* Bool */:break;
case 2 /* U8 */:break;
case 3 /* U16 */:break;
case 4 /* U32 */:break;
case 5 /* U64 */:break;
case 6 /* I8 */:break;
case 7 /* I16 */:break;
case 8 /* I32 */:break;
case 9 /* I64 */:break;
case 10 /* F32 */:break;
case 11 /* F64 */:break;
case 12 /* Usize */:break;
case 13 /* JaktString */:break;
case 14 /* CChar */:break;
case 15 /* CInt */:break;
case 16 /* Unknown */:break;
case 17 /* Never */:break;
case 18 /* TypeVariable */:this->as.TypeVariable.name.~ByteString();
this->as.TypeVariable.trait_implementations.~DynamicArray();
break;
case 19 /* Dependent */:this->as.Dependent.namespace_type.~TypeId();
this->as.Dependent.name.~ByteString();
this->as.Dependent.args.~DynamicArray();
break;
case 20 /* GenericInstance */:this->as.GenericInstance.id.~StructId();
this->as.GenericInstance.args.~DynamicArray();
break;
case 21 /* GenericEnumInstance */:this->as.GenericEnumInstance.id.~EnumId();
this->as.GenericEnumInstance.args.~DynamicArray();
break;
case 22 /* GenericTraitInstance */:this->as.GenericTraitInstance.id.~TraitId();
this->as.GenericTraitInstance.args.~DynamicArray();
break;
case 23 /* Struct */:this->as.Struct.value.~StructId();
break;
case 24 /* Enum */:this->as.Enum.value.~EnumId();
break;
case 25 /* RawPtr */:this->as.RawPtr.value.~TypeId();
break;
case 26 /* Trait */:this->as.Trait.value.~TraitId();
break;
case 27 /* Reference */:this->as.Reference.value.~TypeId();
break;
case 28 /* MutableReference */:this->as.MutableReference.value.~TypeId();
break;
case 29 /* Function */:this->as.Function.params.~DynamicArray();
this->as.Function.return_type_id.~TypeId();
this->as.Function.pseudo_function_id.~FunctionId();
break;
case 30 /* Self */:break;
case 31 /* Const */:this->as.Const.value.~Value();
break;
}
}
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>> Jakt::types::Type::generic_parameters(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>, JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>>(program->get_struct(id).generic_parameters));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>>(program->get_struct(id).generic_parameters));
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>>(program->get_enum(id).generic_parameters));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>>(program->get_enum(id).generic_parameters));
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>>(program->get_trait(id)->generic_parameters));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::CheckedGenericParameter>>>(program->get_trait(id)->generic_parameters));
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool Jakt::types::Type::is_boxed(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_struct(struct_id).record_type.__jakt_init_index() == 1 /* Class */);
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(program->get_struct(struct_id).record_type.__jakt_init_index() == 1 /* Class */);
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(program->get_enum(enum_id).is_boxed);
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(program->get_enum(enum_id).is_boxed);
};/*case end*/
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

bool Jakt::types::Type::is_concrete() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */:case 30 /* Self */:case 19 /* Dependent */:case 26 /* Trait */:case 22 /* GenericTraitInstance */:case 16 /* Unknown */:return JaktInternal::ExplicitValue(false);
default:return JaktInternal::ExplicitValue(true);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

i64 Jakt::types::Type::specificity(NonnullRefPtr<Jakt::types::CheckedProgram> const program,i64 const base_specificity) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */:return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
i64 specificity = JaktInternal::checked_div(base_specificity,static_cast<i64>(2LL));
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId subtype_id = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::Type> const subtype = program->get_type(subtype_id);
specificity += subtype->specificity(program,JaktInternal::checked_div(base_specificity,static_cast<i64>(4LL)));
}

}
}

return JaktInternal::ExplicitValue<i64>(specificity);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 31 /* Const */:return JaktInternal::ExplicitValue(base_specificity);
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
i64 specificity = JaktInternal::checked_div(base_specificity,static_cast<i64>(2LL));
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId subtype_id = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::Type> const subtype = program->get_type(subtype_id);
specificity += subtype->specificity(program,JaktInternal::checked_div(base_specificity,static_cast<i64>(4LL)));
}

}
}

return JaktInternal::ExplicitValue<i64>(specificity);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
i64 specificity = JaktInternal::checked_div(base_specificity,static_cast<i64>(2LL));
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = args.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId subtype_id = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::Type> const subtype = program->get_type(subtype_id);
specificity += subtype->specificity(program,JaktInternal::checked_div(base_specificity,static_cast<i64>(4LL)));
}

}
}

return JaktInternal::ExplicitValue<i64>(specificity);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& params = __jakt_match_value.params;
{
i64 specificity = JaktInternal::checked_div(base_specificity,static_cast<i64>(2LL));
{
JaktInternal::ArrayIterator<Jakt::ids::TypeId> _magic = params.iterator();
for (;;){
JaktInternal::Optional<Jakt::ids::TypeId> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::ids::TypeId subtype_id = _magic_value.value();
{
NonnullRefPtr<typename Jakt::types::Type> const subtype = program->get_type(subtype_id);
specificity += subtype->specificity(program,JaktInternal::checked_div(base_specificity,static_cast<i64>(4LL)));
}

}
}

return JaktInternal::ExplicitValue<i64>(specificity);
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return JaktInternal::ExplicitValue(base_specificity);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ByteString Jakt::types::Type::constructor_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Void"sv));
case 1 /* Bool */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Bool"sv));
case 2 /* U8 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("U8"sv));
case 3 /* U16 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("U16"sv));
case 4 /* U32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("U32"sv));
case 5 /* U64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("U64"sv));
case 6 /* I8 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("I8"sv));
case 7 /* I16 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("I16"sv));
case 8 /* I32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("I32"sv));
case 9 /* I64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("I64"sv));
case 10 /* F32 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("F32"sv));
case 11 /* F64 */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("F64"sv));
case 12 /* Usize */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Usize"sv));
case 13 /* JaktString */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("JaktString"sv));
case 14 /* CChar */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("CChar"sv));
case 15 /* CInt */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("CInt"sv));
case 16 /* Unknown */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Unknown"sv));
case 17 /* Never */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Never"sv));
case 18 /* TypeVariable */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("TypeVariable"sv));
case 19 /* Dependent */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Dependent"sv));
case 20 /* GenericInstance */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("GenericInstance"sv));
case 21 /* GenericEnumInstance */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("GenericEnumInstance"sv));
case 22 /* GenericTraitInstance */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("GenericTraitInstance"sv));
case 23 /* Struct */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Struct"sv));
case 24 /* Enum */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Enum"sv));
case 25 /* RawPtr */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("RawPtr"sv));
case 26 /* Trait */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Trait"sv));
case 27 /* Reference */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Reference"sv));
case 28 /* MutableReference */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("MutableReference"sv));
case 29 /* Function */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Function"sv));
case 30 /* Self */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Self"sv));
case 31 /* Const */:return JaktInternal::ExplicitValue(ByteString::from_utf8_without_validation("Const"sv));
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool Jakt::types::Type::equals(NonnullRefPtr<typename Jakt::types::Type> const rhs) const {
{
return rhs->common.init_common.qualifiers.equals(this->common.init_common.qualifiers) && ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 0 /* Void */);
case 1 /* Bool */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 1 /* Bool */);
case 2 /* U8 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 2 /* U8 */);
case 3 /* U16 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 3 /* U16 */);
case 4 /* U32 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 4 /* U32 */);
case 5 /* U64 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 5 /* U64 */);
case 6 /* I8 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 6 /* I8 */);
case 7 /* I16 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 7 /* I16 */);
case 8 /* I32 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 8 /* I32 */);
case 9 /* I64 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 9 /* I64 */);
case 10 /* F32 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 10 /* F32 */);
case 11 /* F64 */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 11 /* F64 */);
case 12 /* Usize */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 12 /* Usize */);
case 13 /* JaktString */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 13 /* JaktString */);
case 14 /* CChar */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 14 /* CChar */);
case 15 /* CInt */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 15 /* CInt */);
case 30 /* Self */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 30 /* Self */);
case 16 /* Unknown */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 16 /* Unknown */);
case 17 /* Never */:return JaktInternal::ExplicitValue(rhs->__jakt_init_index() == 17 /* Never */);
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& lhs_name = __jakt_match_value.name;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp45 = rhs;
if (__jakt_tmp45->__jakt_init_index() == 18 /* TypeVariable */){
ByteString const rhs_name = __jakt_tmp45->as.TypeVariable.name;
return lhs_name == rhs_name;
}
return JaktInternal::ExplicitValue<bool>(false);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;Jakt::ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp46 = rhs;
if (__jakt_tmp46->__jakt_init_index() == 19 /* Dependent */){
Jakt::ids::TypeId const rhs_namespace_type = __jakt_tmp46->as.Dependent.namespace_type;
ByteString const rhs_name = __jakt_tmp46->as.Dependent.name;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const rhs_args = __jakt_tmp46->as.Dependent.args;
if (namespace_type.equals(rhs_namespace_type) && (name == rhs_name)){
if (args.size() == rhs_args.size()){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(args.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t idx = _magic_value.value();
{
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(args.operator[](idx),rhs_args.operator[](idx))){
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
return false;
}

}
return JaktInternal::ExplicitValue<bool>(false);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 31 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;Jakt::types::Value const& lhs_value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs;
switch(__jakt_match_variant.__jakt_init_index()) {
case 31 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;Jakt::types::Value const& rhs_value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(lhs_value.impl->equals(rhs_value.impl));
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp47 = rhs;
if (__jakt_tmp47->__jakt_init_index() == 20 /* GenericInstance */){
Jakt::ids::StructId const rhs_id = __jakt_tmp47->as.GenericInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const rhs_args = __jakt_tmp47->as.GenericInstance.args;
if (lhs_id.equals(rhs_id) && (lhs_args.size() == rhs_args.size())){
size_t idx = static_cast<size_t>(0ULL);
while (idx < lhs_args.size()){
if ([](Jakt::ids::TypeId const& self, Jakt::ids::TypeId rhs) -> bool {{
return !self.equals(rhs);
}
}
(lhs_args.operator[](idx),rhs_args.operator[](idx))){
return false;
}
idx++;
}
return true;
}
else {
return false;
}

}
else {
return false;
}

}
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;Jakt::ids::TraitId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp48 = rhs;
if (__jakt_tmp48->__jakt_init_index() == 22 /* GenericTraitInstance */){
Jakt::ids::TraitId const rhs_id = __jakt_tmp48->as.GenericTraitInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const rhs_args = __jakt_tmp48->as.GenericTraitInstance.args;
if (lhs_id.equals(rhs_id) && (lhs_args.size() == rhs_args.size())){
size_t idx = static_cast<size_t>(0ULL);
while (idx < lhs_args.size()){
if (!lhs_args.operator[](idx).equals(rhs_args.operator[](idx))){
return false;
}
idx++;
}
return true;
}
else {
return false;
}

}
else {
return false;
}

}
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp49 = rhs;
if (__jakt_tmp49->__jakt_init_index() == 21 /* GenericEnumInstance */){
Jakt::ids::EnumId const rhs_id = __jakt_tmp49->as.GenericEnumInstance.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const rhs_args = __jakt_tmp49->as.GenericEnumInstance.args;
if (lhs_id.equals(rhs_id) && (lhs_args.size() == rhs_args.size())){
size_t idx = static_cast<size_t>(0ULL);
while (idx < lhs_args.size()){
if (!lhs_args.operator[](idx).equals(rhs_args.operator[](idx))){
return false;
}
idx++;
}
return true;
}
else {
return false;
}

}
else {
return false;
}

}
};/*case end*/
case 23 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& lhs_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp50 = rhs;
if (__jakt_tmp50->__jakt_init_index() == 23 /* Struct */){
Jakt::ids::StructId const rhs_id = __jakt_tmp50->as.Struct.value;
return lhs_id.equals(rhs_id);
}
return false;
}
};/*case end*/
case 24 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& lhs_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp51 = rhs;
if (__jakt_tmp51->__jakt_init_index() == 24 /* Enum */){
Jakt::ids::EnumId const rhs_id = __jakt_tmp51->as.Enum.value;
return lhs_id.equals(rhs_id);
}
return false;
}
};/*case end*/
case 25 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& lhs_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp52 = rhs;
if (__jakt_tmp52->__jakt_init_index() == 25 /* RawPtr */){
Jakt::ids::TypeId const rhs_id = __jakt_tmp52->as.RawPtr.value;
return lhs_id.equals(rhs_id);
}
return false;
}
};/*case end*/
case 27 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& lhs_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp53 = rhs;
if (__jakt_tmp53->__jakt_init_index() == 27 /* Reference */){
Jakt::ids::TypeId const rhs_id = __jakt_tmp53->as.Reference.value;
return lhs_id.equals(rhs_id);
}
return false;
}
};/*case end*/
case 28 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& lhs_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp54 = rhs;
if (__jakt_tmp54->__jakt_init_index() == 28 /* MutableReference */){
Jakt::ids::TypeId const rhs_id = __jakt_tmp54->as.MutableReference.value;
return lhs_id.equals(rhs_id);
}
return false;
}
};/*case end*/
case 26 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;Jakt::ids::TraitId const& lhs_id = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp55 = rhs;
if (__jakt_tmp55->__jakt_init_index() == 26 /* Trait */){
Jakt::ids::TraitId const rhs_id = __jakt_tmp55->as.Trait.value;
return lhs_id.equals(rhs_id);
}
return false;
}
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
{
NonnullRefPtr<typename Jakt::types::Type> __jakt_tmp56 = rhs;
if (__jakt_tmp56->__jakt_init_index() == 29 /* Function */){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const rhs_params = __jakt_tmp56->as.Function.params;
bool const rhs_can_throw = __jakt_tmp56->as.Function.can_throw;
Jakt::ids::TypeId const rhs_return_type_id = __jakt_tmp56->as.Function.return_type_id;
if ((params.size() == rhs_params.size()) && (return_type_id.equals(rhs_return_type_id) && (can_throw == rhs_can_throw))){
{
JaktInternal::Range<size_t> _magic = JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(params.size())};
for (;;){
JaktInternal::Optional<size_t> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
size_t i = _magic_value.value();
{
if (!params.operator[](i).equals(rhs_params.operator[](i))){
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
return false;
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

bool Jakt::types::Type::is_builtin() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:case 1 /* Bool */:case 2 /* U8 */:case 3 /* U16 */:case 4 /* U32 */:case 5 /* U64 */:case 6 /* I8 */:case 7 /* I16 */:case 8 /* I32 */:case 9 /* I64 */:case 10 /* F32 */:case 11 /* F64 */:case 12 /* Usize */:case 13 /* JaktString */:case 14 /* CChar */:case 15 /* CInt */:return JaktInternal::ExplicitValue(true);
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

bool Jakt::types::Type::is_integer() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */:case 3 /* U16 */:case 4 /* U32 */:case 5 /* U64 */:case 6 /* I8 */:case 7 /* I16 */:case 8 /* I32 */:case 9 /* I64 */:case 14 /* CChar */:case 15 /* CInt */:case 12 /* Usize */:return JaktInternal::ExplicitValue(true);
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

bool Jakt::types::Type::is_floating() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */:case 11 /* F64 */:return JaktInternal::ExplicitValue(true);
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

bool Jakt::types::Type::is_numeric() const {
{
return this->is_integer() || this->is_floating();
}
}

Jakt::types::BuiltinType Jakt::types::Type::as_builtin_type() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BuiltinType, Jakt::types::BuiltinType>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::Void());
case 1 /* Bool */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::Bool());
case 2 /* U8 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::U8());
case 3 /* U16 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::U16());
case 4 /* U32 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::U32());
case 5 /* U64 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::U64());
case 6 /* I8 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::I8());
case 7 /* I16 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::I16());
case 8 /* I32 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::I32());
case 9 /* I64 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::I64());
case 10 /* F32 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::F32());
case 11 /* F64 */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::F64());
case 12 /* Usize */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::Usize());
case 13 /* JaktString */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::JaktString());
case 14 /* CChar */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::CChar());
case 15 /* CInt */:return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::CInt());
default:{
warnln(StringView::from_string_literal("Type.as_builtin_type: Not a builtin type: {}"sv),*this);
Jakt::abort();
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

i64 Jakt::types::Type::get_bits() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */:case 6 /* I8 */:case 14 /* CChar */:return JaktInternal::ExplicitValue(static_cast<i64>(8LL));
case 3 /* U16 */:case 7 /* I16 */:return JaktInternal::ExplicitValue(static_cast<i64>(16LL));
case 4 /* U32 */:case 8 /* I32 */:case 15 /* CInt */:return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
case 5 /* U64 */:case 9 /* I64 */:case 12 /* Usize */:return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
case 10 /* F32 */:return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
case 11 /* F64 */:return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
default:return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool Jakt::types::Type::is_signed() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */:case 7 /* I16 */:case 8 /* I32 */:case 9 /* I64 */:case 14 /* CChar */:case 15 /* CInt */:return JaktInternal::ExplicitValue(true);
case 2 /* U8 */:case 3 /* U16 */:case 4 /* U32 */:case 5 /* U64 */:case 12 /* Usize */:return JaktInternal::ExplicitValue(false);
case 10 /* F32 */:case 11 /* F64 */:return JaktInternal::ExplicitValue(true);
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

i64 Jakt::types::Type::min() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* CChar */:return JaktInternal::ExplicitValue(-static_cast<i64>(128LL));
case 15 /* CInt */:return JaktInternal::ExplicitValue(-static_cast<i64>(2147483648LL));
case 6 /* I8 */:return JaktInternal::ExplicitValue(-static_cast<i64>(128LL));
case 7 /* I16 */:return JaktInternal::ExplicitValue(-static_cast<i64>(32768LL));
case 8 /* I32 */:return JaktInternal::ExplicitValue(-static_cast<i64>(2147483648LL));
case 9 /* I64 */:return JaktInternal::ExplicitValue(JaktInternal::checked_sub((-static_cast<i64>(9223372036854775807LL)),static_cast<i64>(1LL)));
case 2 /* U8 */:case 3 /* U16 */:case 4 /* U32 */:case 5 /* U64 */:case 12 /* Usize */:return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
default:return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

u64 Jakt::types::Type::max() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, u64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* CChar */:return JaktInternal::ExplicitValue(static_cast<u64>(127ULL));
case 15 /* CInt */:return JaktInternal::ExplicitValue(static_cast<u64>(2147483647ULL));
case 6 /* I8 */:return JaktInternal::ExplicitValue(static_cast<u64>(127ULL));
case 7 /* I16 */:return JaktInternal::ExplicitValue(static_cast<u64>(32767ULL));
case 8 /* I32 */:return JaktInternal::ExplicitValue(static_cast<u64>(2147483647ULL));
case 9 /* I64 */:return JaktInternal::ExplicitValue(static_cast<u64>(9223372036854775807ULL));
case 2 /* U8 */:return JaktInternal::ExplicitValue(static_cast<u64>(255ULL));
case 3 /* U16 */:return JaktInternal::ExplicitValue(static_cast<u64>(65535ULL));
case 4 /* U32 */:return JaktInternal::ExplicitValue(static_cast<u64>(4294967295ULL));
case 5 /* U64 */:return JaktInternal::ExplicitValue(static_cast<u64>(18446744073709551615ULL));
case 12 /* Usize */:return JaktInternal::ExplicitValue(static_cast<u64>(18446744073709551615ULL));
default:return JaktInternal::ExplicitValue(static_cast<u64>(0ULL));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

Jakt::ids::TypeId Jakt::types::Type::flip_signedness() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, Jakt::ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U8()));
case 7 /* I16 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U16()));
case 8 /* I32 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U32()));
case 9 /* I64 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U64()));
case 2 /* U8 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I8()));
case 3 /* U16 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I16()));
case 4 /* U32 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I32()));
case 5 /* U64 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I64()));
default:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Unknown()));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ByteString Jakt::types::CheckedTraitRequirements::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Nothing */: {
return ByteString("CheckedTraitRequirements::Nothing"sv);
break;}
case 1 /* Methods */: {
builder.append("CheckedTraitRequirements::Methods"sv);
[[maybe_unused]] auto const& that = this->as.Methods;
builder.appendff("({})", that.value);
break;}
case 2 /* ComptimeExpression */: {
builder.append("CheckedTraitRequirements::ComptimeExpression"sv);
[[maybe_unused]] auto const& that = this->as.ComptimeExpression;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedTraitRequirements CheckedTraitRequirements::Nothing(){
CheckedTraitRequirements __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedTraitRequirements CheckedTraitRequirements::Methods(JaktInternal::Dictionary<ByteString,Jakt::ids::FunctionId> value){
CheckedTraitRequirements __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Methods.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedTraitRequirements CheckedTraitRequirements::ComptimeExpression(NonnullRefPtr<typename Jakt::types::CheckedExpression> value){
CheckedTraitRequirements __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.ComptimeExpression.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
CheckedTraitRequirements& CheckedTraitRequirements::operator=(CheckedTraitRequirements const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
new (&this->as.Methods.value) (decltype(this->as.Methods.value))(rhs.as.Methods.value);
break;
case 2 /* ComptimeExpression */:
new (&this->as.ComptimeExpression.value) (decltype(this->as.ComptimeExpression.value))(rhs.as.ComptimeExpression.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
this->as.Methods.value = rhs.as.Methods.value;
break;
case 2 /* ComptimeExpression */:
this->as.ComptimeExpression.value = rhs.as.ComptimeExpression.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedTraitRequirements::CheckedTraitRequirements(CheckedTraitRequirements const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
new (&this->as.Methods.value) (decltype(this->as.Methods.value))(rhs.as.Methods.value);
break;
case 2 /* ComptimeExpression */:
new (&this->as.ComptimeExpression.value) (decltype(this->as.ComptimeExpression.value))(rhs.as.ComptimeExpression.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedTraitRequirements& CheckedTraitRequirements::operator=(CheckedTraitRequirements &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
new (&this->as.Methods.value) (decltype(this->as.Methods.value))(move(rhs.as.Methods.value));
break;
case 2 /* ComptimeExpression */:
new (&this->as.ComptimeExpression.value) (decltype(this->as.ComptimeExpression.value))(move(rhs.as.ComptimeExpression.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
this->as.Methods.value = move(rhs.as.Methods.value);
break;
case 2 /* ComptimeExpression */:
this->as.ComptimeExpression.value = move(rhs.as.ComptimeExpression.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedTraitRequirements::CheckedTraitRequirements(CheckedTraitRequirements &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Nothing */:
break;
case 1 /* Methods */:
new (&this->as.Methods.value) (decltype(this->as.Methods.value))(move(rhs.as.Methods.value));
break;
case 2 /* ComptimeExpression */:
new (&this->as.ComptimeExpression.value) (decltype(this->as.ComptimeExpression.value))(move(rhs.as.ComptimeExpression.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedTraitRequirements::~CheckedTraitRequirements(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void CheckedTraitRequirements::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Nothing */:break;
case 1 /* Methods */:this->as.Methods.value.~Dictionary();
break;
case 2 /* ComptimeExpression */:this->as.ComptimeExpression.value.~NonnullRefPtr();
break;
}
}
ByteString Jakt::types::MaybeResolvedScope::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Resolved */: {
builder.append("MaybeResolvedScope::Resolved"sv);
[[maybe_unused]] auto const& that = this->as.Resolved;
builder.appendff("({})", that.value);
break;}
case 1 /* Unresolved */: {
builder.append("MaybeResolvedScope::Unresolved"sv);
[[maybe_unused]] auto const& that = this->as.Unresolved;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parent_scope: {}, ", that.parent_scope);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("relative_name: \"{}\"", that.relative_name);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<MaybeResolvedScope> MaybeResolvedScope::Resolved(Jakt::ids::ScopeId value){
NonnullRefPtr<MaybeResolvedScope> __jakt_uninit_enum = adopt_ref(*new MaybeResolvedScope);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->as.Resolved.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<MaybeResolvedScope> MaybeResolvedScope::Unresolved(NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> parent_scope, ByteString relative_name){
NonnullRefPtr<MaybeResolvedScope> __jakt_uninit_enum = adopt_ref(*new MaybeResolvedScope);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->as.Unresolved.parent_scope) (decltype(parent_scope))(move(parent_scope));
new (&__jakt_uninit_enum->as.Unresolved.relative_name) (decltype(relative_name))(move(relative_name));
return __jakt_uninit_enum;
}
MaybeResolvedScope& MaybeResolvedScope::operator=(MaybeResolvedScope const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Resolved */:
new (&this->as.Resolved.value) (decltype(this->as.Resolved.value))(rhs.as.Resolved.value);
break;
case 1 /* Unresolved */:
new (&this->as.Unresolved.parent_scope) (decltype(this->as.Unresolved.parent_scope))(rhs.as.Unresolved.parent_scope);
new (&this->as.Unresolved.relative_name) (decltype(this->as.Unresolved.relative_name))(rhs.as.Unresolved.relative_name);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Resolved */:
this->as.Resolved.value = rhs.as.Resolved.value;
break;
case 1 /* Unresolved */:
this->as.Unresolved.parent_scope = rhs.as.Unresolved.parent_scope;
this->as.Unresolved.relative_name = rhs.as.Unresolved.relative_name;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
MaybeResolvedScope::MaybeResolvedScope(MaybeResolvedScope const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Resolved */:
new (&this->as.Resolved.value) (decltype(this->as.Resolved.value))(rhs.as.Resolved.value);
break;
case 1 /* Unresolved */:
new (&this->as.Unresolved.parent_scope) (decltype(this->as.Unresolved.parent_scope))(rhs.as.Unresolved.parent_scope);
new (&this->as.Unresolved.relative_name) (decltype(this->as.Unresolved.relative_name))(rhs.as.Unresolved.relative_name);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
MaybeResolvedScope& MaybeResolvedScope::operator=(MaybeResolvedScope &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Resolved */:
new (&this->as.Resolved.value) (decltype(this->as.Resolved.value))(move(rhs.as.Resolved.value));
break;
case 1 /* Unresolved */:
new (&this->as.Unresolved.parent_scope) (decltype(this->as.Unresolved.parent_scope))(move(rhs.as.Unresolved.parent_scope));
new (&this->as.Unresolved.relative_name) (decltype(this->as.Unresolved.relative_name))(move(rhs.as.Unresolved.relative_name));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Resolved */:
this->as.Resolved.value = move(rhs.as.Resolved.value);
break;
case 1 /* Unresolved */:
this->as.Unresolved.parent_scope = move(rhs.as.Unresolved.parent_scope);
this->as.Unresolved.relative_name = move(rhs.as.Unresolved.relative_name);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
MaybeResolvedScope::MaybeResolvedScope(MaybeResolvedScope &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Resolved */:
new (&this->as.Resolved.value) (decltype(this->as.Resolved.value))(move(rhs.as.Resolved.value));
break;
case 1 /* Unresolved */:
new (&this->as.Unresolved.parent_scope) (decltype(this->as.Unresolved.parent_scope))(move(rhs.as.Unresolved.parent_scope));
new (&this->as.Unresolved.relative_name) (decltype(this->as.Unresolved.relative_name))(move(rhs.as.Unresolved.relative_name));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
MaybeResolvedScope::~MaybeResolvedScope(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void MaybeResolvedScope::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Resolved */:this->as.Resolved.value.~ScopeId();
break;
case 1 /* Unresolved */:this->as.Unresolved.parent_scope.~NonnullRefPtr();
this->as.Unresolved.relative_name.~ByteString();
break;
}
}
ErrorOr<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> Jakt::types::MaybeResolvedScope::try_resolve(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>, ErrorOr<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Resolved */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Resolved;Jakt::ids::ScopeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::MaybeResolvedScope::Resolved(id));
};/*case end*/
case 1 /* Unresolved */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unresolved;NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> const& parent_scope = __jakt_match_value.parent_scope;
ByteString const& relative_name = __jakt_match_value.relative_name;
{
NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> parent = TRY((parent_scope->try_resolve(program)));
NonnullRefPtr<typename Jakt::types::MaybeResolvedScope> __jakt_tmp57 = parent;
if (__jakt_tmp57->__jakt_init_index() == 0 /* Resolved */){
Jakt::ids::ScopeId const parent_scope_id = __jakt_tmp57->as.Resolved.value;
Jakt::ids::ScopeId const scope = parent_scope_id;
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = JaktInternal::OptionalNone();
if (!scope_id.has_value()){
JaktInternal::Optional<Jakt::ids::StructId> const struct_ = TRY((program->find_struct_in_scope(scope,relative_name,false,JaktInternal::OptionalNone())));
if (struct_.has_value()){
scope_id = program->get_struct(struct_.value()).scope_id;
}
}
if (!scope_id.has_value()){
JaktInternal::Optional<Jakt::ids::EnumId> const enum_ = TRY((program->find_enum_in_scope(scope,relative_name,false,JaktInternal::OptionalNone())));
if (enum_.has_value()){
scope_id = program->get_enum(enum_.value()).scope_id;
}
}
if (!scope_id.has_value()){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::ScopeId,bool>> const ns = TRY((program->find_namespace_in_scope(scope,relative_name,false,false,JaktInternal::OptionalNone())));
if (ns.has_value()){
scope_id = ns.value().template get<0>();
}
}
if (!scope_id.has_value()){
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const ids = TRY((program->find_functions_with_name_in_scope(scope,relative_name,false,JaktInternal::OptionalNone())));
if (ids.has_value()){
scope_id = program->get_function(ids.value().operator[](static_cast<i64>(0LL)))->function_scope_id;
}
}
if (scope_id.has_value()){
return Jakt::types::MaybeResolvedScope::Resolved(scope_id.value());
}
}
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>>(Jakt::types::MaybeResolvedScope::Unresolved(parent,relative_name));
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

ByteString Jakt::types::CheckedVisibility::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Public */: {
return ByteString("CheckedVisibility::Public"sv);
break;}
case 1 /* Private */: {
return ByteString("CheckedVisibility::Private"sv);
break;}
case 2 /* Restricted */: {
builder.append("CheckedVisibility::Restricted"sv);
[[maybe_unused]] auto const& that = this->as.Restricted;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scopes: {}, ", that.scopes);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedVisibility CheckedVisibility::Public(){
CheckedVisibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedVisibility CheckedVisibility::Private(){
CheckedVisibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedVisibility CheckedVisibility::Restricted(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::MaybeResolvedScope>> scopes, Jakt::utility::Span span){
CheckedVisibility __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Restricted.scopes) (decltype(scopes))(move(scopes));
new (&__jakt_uninit_enum.as.Restricted.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
CheckedVisibility& CheckedVisibility::operator=(CheckedVisibility const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
new (&this->as.Restricted.scopes) (decltype(this->as.Restricted.scopes))(rhs.as.Restricted.scopes);
new (&this->as.Restricted.span) (decltype(this->as.Restricted.span))(rhs.as.Restricted.span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
this->as.Restricted.scopes = rhs.as.Restricted.scopes;
this->as.Restricted.span = rhs.as.Restricted.span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedVisibility::CheckedVisibility(CheckedVisibility const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
new (&this->as.Restricted.scopes) (decltype(this->as.Restricted.scopes))(rhs.as.Restricted.scopes);
new (&this->as.Restricted.span) (decltype(this->as.Restricted.span))(rhs.as.Restricted.span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedVisibility& CheckedVisibility::operator=(CheckedVisibility &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
new (&this->as.Restricted.scopes) (decltype(this->as.Restricted.scopes))(move(rhs.as.Restricted.scopes));
new (&this->as.Restricted.span) (decltype(this->as.Restricted.span))(move(rhs.as.Restricted.span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
this->as.Restricted.scopes = move(rhs.as.Restricted.scopes);
this->as.Restricted.span = move(rhs.as.Restricted.span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedVisibility::CheckedVisibility(CheckedVisibility &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Public */:
break;
case 1 /* Private */:
break;
case 2 /* Restricted */:
new (&this->as.Restricted.scopes) (decltype(this->as.Restricted.scopes))(move(rhs.as.Restricted.scopes));
new (&this->as.Restricted.span) (decltype(this->as.Restricted.span))(move(rhs.as.Restricted.span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedVisibility::~CheckedVisibility(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void CheckedVisibility::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Public */:break;
case 1 /* Private */:break;
case 2 /* Restricted */:this->as.Restricted.scopes.~DynamicArray();
this->as.Restricted.span.~Span();
break;
}
}
ByteString Jakt::types::CheckedCapture::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* ByValue */: {
return ByteString("CheckedCapture::ByValue"sv);
break;}
case 1 /* ByReference */: {
return ByteString("CheckedCapture::ByReference"sv);
break;}
case 2 /* ByMutableReference */: {
return ByteString("CheckedCapture::ByMutableReference"sv);
break;}
case 3 /* ByComptimeDependency */: {
return ByteString("CheckedCapture::ByComptimeDependency"sv);
break;}
case 4 /* AllByReference */: {
return ByteString("CheckedCapture::AllByReference"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedCapture CheckedCapture::ByValue(ByteString name, Jakt::utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedCapture CheckedCapture::ByReference(ByteString name, Jakt::utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedCapture CheckedCapture::ByMutableReference(ByteString name, Jakt::utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedCapture CheckedCapture::ByComptimeDependency(ByteString name, Jakt::utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedCapture CheckedCapture::AllByReference(ByteString name, Jakt::utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
CheckedCapture& CheckedCapture::operator=(CheckedCapture const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.name = rhs.common.init_common.name;
this->common.init_common.span = rhs.common.init_common.span;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedCapture::CheckedCapture(CheckedCapture const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.name) (decltype(this->common.init_common.name))(rhs.common.init_common.name);
new (&this->common.init_common.span) (decltype(this->common.init_common.span))(rhs.common.init_common.span);
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedCapture& CheckedCapture::operator=(CheckedCapture &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.name = move(rhs.common.init_common.name);
this->common.init_common.span = move(rhs.common.init_common.span);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedCapture::CheckedCapture(CheckedCapture &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.name) (decltype(this->common.init_common.name))(move(rhs.common.init_common.name));
new (&this->common.init_common.span) (decltype(this->common.init_common.span))(move(rhs.common.init_common.span));
switch (rhs.__jakt_init_index()) {
case 0 /* ByValue */:
break;
case 1 /* ByReference */:
break;
case 2 /* ByMutableReference */:
break;
case 3 /* ByComptimeDependency */:
break;
case 4 /* AllByReference */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedCapture::~CheckedCapture(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.name.~ByteString();
this->common.init_common.span.~Span();
this->__jakt_destroy_variant(); }
void CheckedCapture::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* ByValue */:break;
case 1 /* ByReference */:break;
case 2 /* ByMutableReference */:break;
case 3 /* ByComptimeDependency */:break;
case 4 /* AllByReference */:break;
}
}
ByteString Jakt::types::FunctionGenericParameterKind::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* InferenceGuide */: {
return ByteString("FunctionGenericParameterKind::InferenceGuide"sv);
break;}
case 1 /* Parameter */: {
return ByteString("FunctionGenericParameterKind::Parameter"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] FunctionGenericParameterKind FunctionGenericParameterKind::InferenceGuide(){
FunctionGenericParameterKind __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] FunctionGenericParameterKind FunctionGenericParameterKind::Parameter(){
FunctionGenericParameterKind __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
FunctionGenericParameterKind& FunctionGenericParameterKind::operator=(FunctionGenericParameterKind const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* InferenceGuide */:
break;
case 1 /* Parameter */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* InferenceGuide */:
break;
case 1 /* Parameter */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
FunctionGenericParameterKind::FunctionGenericParameterKind(FunctionGenericParameterKind const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* InferenceGuide */:
break;
case 1 /* Parameter */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
FunctionGenericParameterKind& FunctionGenericParameterKind::operator=(FunctionGenericParameterKind &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* InferenceGuide */:
break;
case 1 /* Parameter */:
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* InferenceGuide */:
break;
case 1 /* Parameter */:
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
FunctionGenericParameterKind::FunctionGenericParameterKind(FunctionGenericParameterKind &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* InferenceGuide */:
break;
case 1 /* Parameter */:
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
FunctionGenericParameterKind::~FunctionGenericParameterKind(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void FunctionGenericParameterKind::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* InferenceGuide */:break;
case 1 /* Parameter */:break;
}
}
ByteString Jakt::types::BlockControlFlow::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* AlwaysReturns */: {
return ByteString("BlockControlFlow::AlwaysReturns"sv);
break;}
case 1 /* AlwaysTransfersControl */: {
builder.append("BlockControlFlow::AlwaysTransfersControl"sv);
[[maybe_unused]] auto const& that = this->as.AlwaysTransfersControl;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("might_break: {}", that.might_break);
}
builder.append(")"sv);
break;}
case 2 /* NeverReturns */: {
return ByteString("BlockControlFlow::NeverReturns"sv);
break;}
case 3 /* MayReturn */: {
return ByteString("BlockControlFlow::MayReturn"sv);
break;}
case 4 /* PartialAlwaysReturns */: {
builder.append("BlockControlFlow::PartialAlwaysReturns"sv);
[[maybe_unused]] auto const& that = this->as.PartialAlwaysReturns;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("might_break: {}", that.might_break);
}
builder.append(")"sv);
break;}
case 5 /* PartialAlwaysTransfersControl */: {
builder.append("BlockControlFlow::PartialAlwaysTransfersControl"sv);
[[maybe_unused]] auto const& that = this->as.PartialAlwaysTransfersControl;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("might_break: {}", that.might_break);
}
builder.append(")"sv);
break;}
case 6 /* PartialNeverReturns */: {
builder.append("BlockControlFlow::PartialNeverReturns"sv);
[[maybe_unused]] auto const& that = this->as.PartialNeverReturns;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("might_break: {}", that.might_break);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] BlockControlFlow BlockControlFlow::AlwaysReturns(){
BlockControlFlow __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] BlockControlFlow BlockControlFlow::AlwaysTransfersControl(bool might_break){
BlockControlFlow __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.AlwaysTransfersControl.might_break) (decltype(might_break))(move(might_break));
return __jakt_uninit_enum;
}
[[nodiscard]] BlockControlFlow BlockControlFlow::NeverReturns(){
BlockControlFlow __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] BlockControlFlow BlockControlFlow::MayReturn(){
BlockControlFlow __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] BlockControlFlow BlockControlFlow::PartialAlwaysReturns(bool might_break){
BlockControlFlow __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.as.PartialAlwaysReturns.might_break) (decltype(might_break))(move(might_break));
return __jakt_uninit_enum;
}
[[nodiscard]] BlockControlFlow BlockControlFlow::PartialAlwaysTransfersControl(bool might_break){
BlockControlFlow __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
new (&__jakt_uninit_enum.as.PartialAlwaysTransfersControl.might_break) (decltype(might_break))(move(might_break));
return __jakt_uninit_enum;
}
[[nodiscard]] BlockControlFlow BlockControlFlow::PartialNeverReturns(bool might_break){
BlockControlFlow __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
new (&__jakt_uninit_enum.as.PartialNeverReturns.might_break) (decltype(might_break))(move(might_break));
return __jakt_uninit_enum;
}
BlockControlFlow& BlockControlFlow::operator=(BlockControlFlow const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* AlwaysReturns */:
break;
case 1 /* AlwaysTransfersControl */:
new (&this->as.AlwaysTransfersControl.might_break) (decltype(this->as.AlwaysTransfersControl.might_break))(rhs.as.AlwaysTransfersControl.might_break);
break;
case 2 /* NeverReturns */:
break;
case 3 /* MayReturn */:
break;
case 4 /* PartialAlwaysReturns */:
new (&this->as.PartialAlwaysReturns.might_break) (decltype(this->as.PartialAlwaysReturns.might_break))(rhs.as.PartialAlwaysReturns.might_break);
break;
case 5 /* PartialAlwaysTransfersControl */:
new (&this->as.PartialAlwaysTransfersControl.might_break) (decltype(this->as.PartialAlwaysTransfersControl.might_break))(rhs.as.PartialAlwaysTransfersControl.might_break);
break;
case 6 /* PartialNeverReturns */:
new (&this->as.PartialNeverReturns.might_break) (decltype(this->as.PartialNeverReturns.might_break))(rhs.as.PartialNeverReturns.might_break);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* AlwaysReturns */:
break;
case 1 /* AlwaysTransfersControl */:
this->as.AlwaysTransfersControl.might_break = rhs.as.AlwaysTransfersControl.might_break;
break;
case 2 /* NeverReturns */:
break;
case 3 /* MayReturn */:
break;
case 4 /* PartialAlwaysReturns */:
this->as.PartialAlwaysReturns.might_break = rhs.as.PartialAlwaysReturns.might_break;
break;
case 5 /* PartialAlwaysTransfersControl */:
this->as.PartialAlwaysTransfersControl.might_break = rhs.as.PartialAlwaysTransfersControl.might_break;
break;
case 6 /* PartialNeverReturns */:
this->as.PartialNeverReturns.might_break = rhs.as.PartialNeverReturns.might_break;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BlockControlFlow::BlockControlFlow(BlockControlFlow const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* AlwaysReturns */:
break;
case 1 /* AlwaysTransfersControl */:
new (&this->as.AlwaysTransfersControl.might_break) (decltype(this->as.AlwaysTransfersControl.might_break))(rhs.as.AlwaysTransfersControl.might_break);
break;
case 2 /* NeverReturns */:
break;
case 3 /* MayReturn */:
break;
case 4 /* PartialAlwaysReturns */:
new (&this->as.PartialAlwaysReturns.might_break) (decltype(this->as.PartialAlwaysReturns.might_break))(rhs.as.PartialAlwaysReturns.might_break);
break;
case 5 /* PartialAlwaysTransfersControl */:
new (&this->as.PartialAlwaysTransfersControl.might_break) (decltype(this->as.PartialAlwaysTransfersControl.might_break))(rhs.as.PartialAlwaysTransfersControl.might_break);
break;
case 6 /* PartialNeverReturns */:
new (&this->as.PartialNeverReturns.might_break) (decltype(this->as.PartialNeverReturns.might_break))(rhs.as.PartialNeverReturns.might_break);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
BlockControlFlow& BlockControlFlow::operator=(BlockControlFlow &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* AlwaysReturns */:
break;
case 1 /* AlwaysTransfersControl */:
new (&this->as.AlwaysTransfersControl.might_break) (decltype(this->as.AlwaysTransfersControl.might_break))(move(rhs.as.AlwaysTransfersControl.might_break));
break;
case 2 /* NeverReturns */:
break;
case 3 /* MayReturn */:
break;
case 4 /* PartialAlwaysReturns */:
new (&this->as.PartialAlwaysReturns.might_break) (decltype(this->as.PartialAlwaysReturns.might_break))(move(rhs.as.PartialAlwaysReturns.might_break));
break;
case 5 /* PartialAlwaysTransfersControl */:
new (&this->as.PartialAlwaysTransfersControl.might_break) (decltype(this->as.PartialAlwaysTransfersControl.might_break))(move(rhs.as.PartialAlwaysTransfersControl.might_break));
break;
case 6 /* PartialNeverReturns */:
new (&this->as.PartialNeverReturns.might_break) (decltype(this->as.PartialNeverReturns.might_break))(move(rhs.as.PartialNeverReturns.might_break));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* AlwaysReturns */:
break;
case 1 /* AlwaysTransfersControl */:
this->as.AlwaysTransfersControl.might_break = move(rhs.as.AlwaysTransfersControl.might_break);
break;
case 2 /* NeverReturns */:
break;
case 3 /* MayReturn */:
break;
case 4 /* PartialAlwaysReturns */:
this->as.PartialAlwaysReturns.might_break = move(rhs.as.PartialAlwaysReturns.might_break);
break;
case 5 /* PartialAlwaysTransfersControl */:
this->as.PartialAlwaysTransfersControl.might_break = move(rhs.as.PartialAlwaysTransfersControl.might_break);
break;
case 6 /* PartialNeverReturns */:
this->as.PartialNeverReturns.might_break = move(rhs.as.PartialNeverReturns.might_break);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
BlockControlFlow::BlockControlFlow(BlockControlFlow &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* AlwaysReturns */:
break;
case 1 /* AlwaysTransfersControl */:
new (&this->as.AlwaysTransfersControl.might_break) (decltype(this->as.AlwaysTransfersControl.might_break))(move(rhs.as.AlwaysTransfersControl.might_break));
break;
case 2 /* NeverReturns */:
break;
case 3 /* MayReturn */:
break;
case 4 /* PartialAlwaysReturns */:
new (&this->as.PartialAlwaysReturns.might_break) (decltype(this->as.PartialAlwaysReturns.might_break))(move(rhs.as.PartialAlwaysReturns.might_break));
break;
case 5 /* PartialAlwaysTransfersControl */:
new (&this->as.PartialAlwaysTransfersControl.might_break) (decltype(this->as.PartialAlwaysTransfersControl.might_break))(move(rhs.as.PartialAlwaysTransfersControl.might_break));
break;
case 6 /* PartialNeverReturns */:
new (&this->as.PartialNeverReturns.might_break) (decltype(this->as.PartialNeverReturns.might_break))(move(rhs.as.PartialNeverReturns.might_break));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
BlockControlFlow::~BlockControlFlow(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void BlockControlFlow::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* AlwaysReturns */:break;
case 1 /* AlwaysTransfersControl */:break;
case 2 /* NeverReturns */:break;
case 3 /* MayReturn */:break;
case 4 /* PartialAlwaysReturns */:break;
case 5 /* PartialAlwaysTransfersControl */:break;
case 6 /* PartialNeverReturns */:break;
}
}
Jakt::types::BlockControlFlow Jakt::types::BlockControlFlow::unify_with(Jakt::types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(second);
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
case 4 /* PartialAlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs));
default:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(might_break));
};/*case end*/
default:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(lhs || might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 0 /* AlwaysReturns */:case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(lhs));
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(lhs || might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(lhs || might_break));
};/*case end*/
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(lhs));
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::NeverReturns());
default: VERIFY_NOT_REACHED();}/*switch end*/
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
});
}
}

Jakt::types::BlockControlFlow Jakt::types::BlockControlFlow::branch_unify_with(Jakt::types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(second);
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(this_might_break));
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(this_might_break));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(might_break || this_might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(might_break || this_might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(this_might_break));
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(this_might_break));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(might_break || this_might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(might_break || this_might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break));
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(this_might_break));
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break));
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(might_break || this_might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(might_break || this_might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break || this_might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
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
});
}
}

Jakt::types::BlockControlFlow Jakt::types::BlockControlFlow::updated(Jakt::types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::NeverReturns());
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(second);
case 5 /* PartialAlwaysTransfersControl */:case 4 /* PartialAlwaysReturns */:case 6 /* PartialNeverReturns */:return JaktInternal::ExplicitValue(this->unify_with(second));
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

Jakt::types::BlockControlFlow Jakt::types::BlockControlFlow::partial() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(false));
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(false));
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialAlwaysReturns(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::PartialNeverReturns(might_break));
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

Jakt::types::BlockControlFlow Jakt::types::BlockControlFlow::definitive() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::NeverReturns());
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
default:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

bool Jakt::types::BlockControlFlow::always_transfers_control() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* AlwaysReturns */:case 1 /* AlwaysTransfersControl */:return JaktInternal::ExplicitValue(true);
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

bool Jakt::types::BlockControlFlow::never_returns() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(true);
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

bool Jakt::types::BlockControlFlow::always_returns() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(true);
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

bool Jakt::types::BlockControlFlow::may_return() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* MayReturn */:case 4 /* PartialAlwaysReturns */:case 5 /* PartialAlwaysTransfersControl */:case 6 /* PartialNeverReturns */:return JaktInternal::ExplicitValue(true);
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

bool Jakt::types::BlockControlFlow::may_break() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(might_break);
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(might_break);
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(might_break);
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(might_break);
};/*case end*/
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

bool Jakt::types::BlockControlFlow::is_reachable() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */:case 0 /* AlwaysReturns */:case 1 /* AlwaysTransfersControl */:return JaktInternal::ExplicitValue(false);
default:return JaktInternal::ExplicitValue(true);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ByteString Jakt::types::CheckedEnumVariant::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Untyped */: {
builder.append("CheckedEnumVariant::Untyped"sv);
[[maybe_unused]] auto const& that = this->as.Untyped;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enum_id: {}, ", that.enum_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* Typed */: {
builder.append("CheckedEnumVariant::Typed"sv);
[[maybe_unused]] auto const& that = this->as.Typed;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enum_id: {}, ", that.enum_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 2 /* WithValue */: {
builder.append("CheckedEnumVariant::WithValue"sv);
[[maybe_unused]] auto const& that = this->as.WithValue;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enum_id: {}, ", that.enum_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 3 /* StructLike */: {
builder.append("CheckedEnumVariant::StructLike"sv);
[[maybe_unused]] auto const& that = this->as.StructLike;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enum_id: {}, ", that.enum_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", that.fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedEnumVariant CheckedEnumVariant::Untyped(Jakt::ids::EnumId enum_id, ByteString name, Jakt::utility::Span span){
CheckedEnumVariant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Untyped.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum.as.Untyped.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Untyped.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedEnumVariant CheckedEnumVariant::Typed(Jakt::ids::EnumId enum_id, ByteString name, Jakt::ids::TypeId type_id, Jakt::utility::Span span){
CheckedEnumVariant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Typed.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum.as.Typed.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Typed.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum.as.Typed.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedEnumVariant CheckedEnumVariant::WithValue(Jakt::ids::EnumId enum_id, ByteString name, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span){
CheckedEnumVariant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.WithValue.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum.as.WithValue.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.WithValue.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum.as.WithValue.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedEnumVariant CheckedEnumVariant::StructLike(Jakt::ids::EnumId enum_id, ByteString name, JaktInternal::DynamicArray<Jakt::ids::VarId> fields, Jakt::utility::Span span){
CheckedEnumVariant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.StructLike.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum.as.StructLike.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.StructLike.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum.as.StructLike.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
CheckedEnumVariant& CheckedEnumVariant::operator=(CheckedEnumVariant const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Untyped */:
new (&this->as.Untyped.enum_id) (decltype(this->as.Untyped.enum_id))(rhs.as.Untyped.enum_id);
new (&this->as.Untyped.name) (decltype(this->as.Untyped.name))(rhs.as.Untyped.name);
new (&this->as.Untyped.span) (decltype(this->as.Untyped.span))(rhs.as.Untyped.span);
break;
case 1 /* Typed */:
new (&this->as.Typed.enum_id) (decltype(this->as.Typed.enum_id))(rhs.as.Typed.enum_id);
new (&this->as.Typed.name) (decltype(this->as.Typed.name))(rhs.as.Typed.name);
new (&this->as.Typed.type_id) (decltype(this->as.Typed.type_id))(rhs.as.Typed.type_id);
new (&this->as.Typed.span) (decltype(this->as.Typed.span))(rhs.as.Typed.span);
break;
case 2 /* WithValue */:
new (&this->as.WithValue.enum_id) (decltype(this->as.WithValue.enum_id))(rhs.as.WithValue.enum_id);
new (&this->as.WithValue.name) (decltype(this->as.WithValue.name))(rhs.as.WithValue.name);
new (&this->as.WithValue.expr) (decltype(this->as.WithValue.expr))(rhs.as.WithValue.expr);
new (&this->as.WithValue.span) (decltype(this->as.WithValue.span))(rhs.as.WithValue.span);
break;
case 3 /* StructLike */:
new (&this->as.StructLike.enum_id) (decltype(this->as.StructLike.enum_id))(rhs.as.StructLike.enum_id);
new (&this->as.StructLike.name) (decltype(this->as.StructLike.name))(rhs.as.StructLike.name);
new (&this->as.StructLike.fields) (decltype(this->as.StructLike.fields))(rhs.as.StructLike.fields);
new (&this->as.StructLike.span) (decltype(this->as.StructLike.span))(rhs.as.StructLike.span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Untyped */:
this->as.Untyped.enum_id = rhs.as.Untyped.enum_id;
this->as.Untyped.name = rhs.as.Untyped.name;
this->as.Untyped.span = rhs.as.Untyped.span;
break;
case 1 /* Typed */:
this->as.Typed.enum_id = rhs.as.Typed.enum_id;
this->as.Typed.name = rhs.as.Typed.name;
this->as.Typed.type_id = rhs.as.Typed.type_id;
this->as.Typed.span = rhs.as.Typed.span;
break;
case 2 /* WithValue */:
this->as.WithValue.enum_id = rhs.as.WithValue.enum_id;
this->as.WithValue.name = rhs.as.WithValue.name;
this->as.WithValue.expr = rhs.as.WithValue.expr;
this->as.WithValue.span = rhs.as.WithValue.span;
break;
case 3 /* StructLike */:
this->as.StructLike.enum_id = rhs.as.StructLike.enum_id;
this->as.StructLike.name = rhs.as.StructLike.name;
this->as.StructLike.fields = rhs.as.StructLike.fields;
this->as.StructLike.span = rhs.as.StructLike.span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedEnumVariant::CheckedEnumVariant(CheckedEnumVariant const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Untyped */:
new (&this->as.Untyped.enum_id) (decltype(this->as.Untyped.enum_id))(rhs.as.Untyped.enum_id);
new (&this->as.Untyped.name) (decltype(this->as.Untyped.name))(rhs.as.Untyped.name);
new (&this->as.Untyped.span) (decltype(this->as.Untyped.span))(rhs.as.Untyped.span);
break;
case 1 /* Typed */:
new (&this->as.Typed.enum_id) (decltype(this->as.Typed.enum_id))(rhs.as.Typed.enum_id);
new (&this->as.Typed.name) (decltype(this->as.Typed.name))(rhs.as.Typed.name);
new (&this->as.Typed.type_id) (decltype(this->as.Typed.type_id))(rhs.as.Typed.type_id);
new (&this->as.Typed.span) (decltype(this->as.Typed.span))(rhs.as.Typed.span);
break;
case 2 /* WithValue */:
new (&this->as.WithValue.enum_id) (decltype(this->as.WithValue.enum_id))(rhs.as.WithValue.enum_id);
new (&this->as.WithValue.name) (decltype(this->as.WithValue.name))(rhs.as.WithValue.name);
new (&this->as.WithValue.expr) (decltype(this->as.WithValue.expr))(rhs.as.WithValue.expr);
new (&this->as.WithValue.span) (decltype(this->as.WithValue.span))(rhs.as.WithValue.span);
break;
case 3 /* StructLike */:
new (&this->as.StructLike.enum_id) (decltype(this->as.StructLike.enum_id))(rhs.as.StructLike.enum_id);
new (&this->as.StructLike.name) (decltype(this->as.StructLike.name))(rhs.as.StructLike.name);
new (&this->as.StructLike.fields) (decltype(this->as.StructLike.fields))(rhs.as.StructLike.fields);
new (&this->as.StructLike.span) (decltype(this->as.StructLike.span))(rhs.as.StructLike.span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedEnumVariant& CheckedEnumVariant::operator=(CheckedEnumVariant &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Untyped */:
new (&this->as.Untyped.enum_id) (decltype(this->as.Untyped.enum_id))(move(rhs.as.Untyped.enum_id));
new (&this->as.Untyped.name) (decltype(this->as.Untyped.name))(move(rhs.as.Untyped.name));
new (&this->as.Untyped.span) (decltype(this->as.Untyped.span))(move(rhs.as.Untyped.span));
break;
case 1 /* Typed */:
new (&this->as.Typed.enum_id) (decltype(this->as.Typed.enum_id))(move(rhs.as.Typed.enum_id));
new (&this->as.Typed.name) (decltype(this->as.Typed.name))(move(rhs.as.Typed.name));
new (&this->as.Typed.type_id) (decltype(this->as.Typed.type_id))(move(rhs.as.Typed.type_id));
new (&this->as.Typed.span) (decltype(this->as.Typed.span))(move(rhs.as.Typed.span));
break;
case 2 /* WithValue */:
new (&this->as.WithValue.enum_id) (decltype(this->as.WithValue.enum_id))(move(rhs.as.WithValue.enum_id));
new (&this->as.WithValue.name) (decltype(this->as.WithValue.name))(move(rhs.as.WithValue.name));
new (&this->as.WithValue.expr) (decltype(this->as.WithValue.expr))(move(rhs.as.WithValue.expr));
new (&this->as.WithValue.span) (decltype(this->as.WithValue.span))(move(rhs.as.WithValue.span));
break;
case 3 /* StructLike */:
new (&this->as.StructLike.enum_id) (decltype(this->as.StructLike.enum_id))(move(rhs.as.StructLike.enum_id));
new (&this->as.StructLike.name) (decltype(this->as.StructLike.name))(move(rhs.as.StructLike.name));
new (&this->as.StructLike.fields) (decltype(this->as.StructLike.fields))(move(rhs.as.StructLike.fields));
new (&this->as.StructLike.span) (decltype(this->as.StructLike.span))(move(rhs.as.StructLike.span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Untyped */:
this->as.Untyped.enum_id = move(rhs.as.Untyped.enum_id);
this->as.Untyped.name = move(rhs.as.Untyped.name);
this->as.Untyped.span = move(rhs.as.Untyped.span);
break;
case 1 /* Typed */:
this->as.Typed.enum_id = move(rhs.as.Typed.enum_id);
this->as.Typed.name = move(rhs.as.Typed.name);
this->as.Typed.type_id = move(rhs.as.Typed.type_id);
this->as.Typed.span = move(rhs.as.Typed.span);
break;
case 2 /* WithValue */:
this->as.WithValue.enum_id = move(rhs.as.WithValue.enum_id);
this->as.WithValue.name = move(rhs.as.WithValue.name);
this->as.WithValue.expr = move(rhs.as.WithValue.expr);
this->as.WithValue.span = move(rhs.as.WithValue.span);
break;
case 3 /* StructLike */:
this->as.StructLike.enum_id = move(rhs.as.StructLike.enum_id);
this->as.StructLike.name = move(rhs.as.StructLike.name);
this->as.StructLike.fields = move(rhs.as.StructLike.fields);
this->as.StructLike.span = move(rhs.as.StructLike.span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedEnumVariant::CheckedEnumVariant(CheckedEnumVariant &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Untyped */:
new (&this->as.Untyped.enum_id) (decltype(this->as.Untyped.enum_id))(move(rhs.as.Untyped.enum_id));
new (&this->as.Untyped.name) (decltype(this->as.Untyped.name))(move(rhs.as.Untyped.name));
new (&this->as.Untyped.span) (decltype(this->as.Untyped.span))(move(rhs.as.Untyped.span));
break;
case 1 /* Typed */:
new (&this->as.Typed.enum_id) (decltype(this->as.Typed.enum_id))(move(rhs.as.Typed.enum_id));
new (&this->as.Typed.name) (decltype(this->as.Typed.name))(move(rhs.as.Typed.name));
new (&this->as.Typed.type_id) (decltype(this->as.Typed.type_id))(move(rhs.as.Typed.type_id));
new (&this->as.Typed.span) (decltype(this->as.Typed.span))(move(rhs.as.Typed.span));
break;
case 2 /* WithValue */:
new (&this->as.WithValue.enum_id) (decltype(this->as.WithValue.enum_id))(move(rhs.as.WithValue.enum_id));
new (&this->as.WithValue.name) (decltype(this->as.WithValue.name))(move(rhs.as.WithValue.name));
new (&this->as.WithValue.expr) (decltype(this->as.WithValue.expr))(move(rhs.as.WithValue.expr));
new (&this->as.WithValue.span) (decltype(this->as.WithValue.span))(move(rhs.as.WithValue.span));
break;
case 3 /* StructLike */:
new (&this->as.StructLike.enum_id) (decltype(this->as.StructLike.enum_id))(move(rhs.as.StructLike.enum_id));
new (&this->as.StructLike.name) (decltype(this->as.StructLike.name))(move(rhs.as.StructLike.name));
new (&this->as.StructLike.fields) (decltype(this->as.StructLike.fields))(move(rhs.as.StructLike.fields));
new (&this->as.StructLike.span) (decltype(this->as.StructLike.span))(move(rhs.as.StructLike.span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedEnumVariant::~CheckedEnumVariant(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void CheckedEnumVariant::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Untyped */:this->as.Untyped.enum_id.~EnumId();
this->as.Untyped.name.~ByteString();
this->as.Untyped.span.~Span();
break;
case 1 /* Typed */:this->as.Typed.enum_id.~EnumId();
this->as.Typed.name.~ByteString();
this->as.Typed.type_id.~TypeId();
this->as.Typed.span.~Span();
break;
case 2 /* WithValue */:this->as.WithValue.enum_id.~EnumId();
this->as.WithValue.name.~ByteString();
this->as.WithValue.expr.~NonnullRefPtr();
this->as.WithValue.span.~Span();
break;
case 3 /* StructLike */:this->as.StructLike.enum_id.~EnumId();
this->as.StructLike.name.~ByteString();
this->as.StructLike.fields.~DynamicArray();
this->as.StructLike.span.~Span();
break;
}
}
bool Jakt::types::CheckedEnumVariant::equals(Jakt::types::CheckedEnumVariant const other) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& this_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& other_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(this_name == other_name);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
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

Jakt::ids::EnumId Jakt::types::CheckedEnumVariant::enum_id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, Jakt::ids::EnumId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
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

Jakt::utility::Span Jakt::types::CheckedEnumVariant::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::utility::Span, Jakt::utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;Jakt::utility::Span const& span = __jakt_match_value.span;
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
}

ByteString Jakt::types::CheckedEnumVariant::name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
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

ByteString Jakt::types::CheckedStatement::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Expression */: {
builder.append("CheckedStatement::Expression"sv);
[[maybe_unused]] auto const& that = this->as.Expression;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* Defer */: {
builder.append("CheckedStatement::Defer"sv);
[[maybe_unused]] auto const& that = this->as.Defer;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("statement: {}, ", that.statement);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 2 /* DestructuringAssignment */: {
builder.append("CheckedStatement::DestructuringAssignment"sv);
[[maybe_unused]] auto const& that = this->as.DestructuringAssignment;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("vars: {}, ", that.vars);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var_decl: {}, ", that.var_decl);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 3 /* VarDecl */: {
builder.append("CheckedStatement::VarDecl"sv);
[[maybe_unused]] auto const& that = this->as.VarDecl;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var_id: {}, ", that.var_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("init: {}, ", that.init);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 4 /* If */: {
builder.append("CheckedStatement::If"sv);
[[maybe_unused]] auto const& that = this->as.If;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("condition: {}, ", that.condition);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("then_block: {}, ", that.then_block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("else_statement: {}, ", that.else_statement);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 5 /* Block */: {
builder.append("CheckedStatement::Block"sv);
[[maybe_unused]] auto const& that = this->as.Block;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 6 /* Loop */: {
builder.append("CheckedStatement::Loop"sv);
[[maybe_unused]] auto const& that = this->as.Loop;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 7 /* While */: {
builder.append("CheckedStatement::While"sv);
[[maybe_unused]] auto const& that = this->as.While;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("condition: {}, ", that.condition);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 8 /* Return */: {
builder.append("CheckedStatement::Return"sv);
[[maybe_unused]] auto const& that = this->as.Return;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: {}, ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 9 /* Break */: {
builder.append("CheckedStatement::Break"sv);
[[maybe_unused]] auto const& that = this->as.Break;
builder.appendff("({})", that.value);
break;}
case 10 /* Continue */: {
builder.append("CheckedStatement::Continue"sv);
[[maybe_unused]] auto const& that = this->as.Continue;
builder.appendff("({})", that.value);
break;}
case 11 /* Throw */: {
builder.append("CheckedStatement::Throw"sv);
[[maybe_unused]] auto const& that = this->as.Throw;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 12 /* Yield */: {
builder.append("CheckedStatement::Yield"sv);
[[maybe_unused]] auto const& that = this->as.Yield;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 13 /* InlineCpp */: {
builder.append("CheckedStatement::InlineCpp"sv);
[[maybe_unused]] auto const& that = this->as.InlineCpp;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("lines: {}, ", that.lines);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 14 /* Garbage */: {
builder.append("CheckedStatement::Garbage"sv);
[[maybe_unused]] auto const& that = this->as.Garbage;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->as.Expression.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Expression.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Defer(NonnullRefPtr<typename Jakt::types::CheckedStatement> statement, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->as.Defer.statement) (decltype(statement))(move(statement));
new (&__jakt_uninit_enum->as.Defer.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::DestructuringAssignment(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> vars, NonnullRefPtr<typename Jakt::types::CheckedStatement> var_decl, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->as.DestructuringAssignment.vars) (decltype(vars))(move(vars));
new (&__jakt_uninit_enum->as.DestructuringAssignment.var_decl) (decltype(var_decl))(move(var_decl));
new (&__jakt_uninit_enum->as.DestructuringAssignment.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::VarDecl(Jakt::ids::VarId var_id, NonnullRefPtr<typename Jakt::types::CheckedExpression> init, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->as.VarDecl.var_id) (decltype(var_id))(move(var_id));
new (&__jakt_uninit_enum->as.VarDecl.init) (decltype(init))(move(init));
new (&__jakt_uninit_enum->as.VarDecl.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::If(NonnullRefPtr<typename Jakt::types::CheckedExpression> condition, Jakt::types::CheckedBlock then_block, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> else_statement, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->as.If.condition) (decltype(condition))(move(condition));
new (&__jakt_uninit_enum->as.If.then_block) (decltype(then_block))(move(then_block));
new (&__jakt_uninit_enum->as.If.else_statement) (decltype(else_statement))(move(else_statement));
new (&__jakt_uninit_enum->as.If.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Block(Jakt::types::CheckedBlock block, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->as.Block.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Block.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Loop(Jakt::types::CheckedBlock block, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->as.Loop.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Loop.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::While(NonnullRefPtr<typename Jakt::types::CheckedExpression> condition, Jakt::types::CheckedBlock block, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->as.While.condition) (decltype(condition))(move(condition));
new (&__jakt_uninit_enum->as.While.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.While.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Return(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> val, JaktInternal::Optional<Jakt::utility::Span> span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->as.Return.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.Return.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Break(Jakt::utility::Span value){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->as.Break.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Continue(Jakt::utility::Span value){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->as.Continue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Throw(NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->as.Throw.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Throw.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Yield(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> expr, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->as.Yield.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Yield.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::InlineCpp(JaktInternal::DynamicArray<ByteString> lines, Jakt::utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->as.InlineCpp.lines) (decltype(lines))(move(lines));
new (&__jakt_uninit_enum->as.InlineCpp.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Garbage(Jakt::utility::Span value){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->as.Garbage.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
CheckedStatement& CheckedStatement::operator=(CheckedStatement const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.expr) (decltype(this->as.Expression.expr))(rhs.as.Expression.expr);
new (&this->as.Expression.span) (decltype(this->as.Expression.span))(rhs.as.Expression.span);
break;
case 1 /* Defer */:
new (&this->as.Defer.statement) (decltype(this->as.Defer.statement))(rhs.as.Defer.statement);
new (&this->as.Defer.span) (decltype(this->as.Defer.span))(rhs.as.Defer.span);
break;
case 2 /* DestructuringAssignment */:
new (&this->as.DestructuringAssignment.vars) (decltype(this->as.DestructuringAssignment.vars))(rhs.as.DestructuringAssignment.vars);
new (&this->as.DestructuringAssignment.var_decl) (decltype(this->as.DestructuringAssignment.var_decl))(rhs.as.DestructuringAssignment.var_decl);
new (&this->as.DestructuringAssignment.span) (decltype(this->as.DestructuringAssignment.span))(rhs.as.DestructuringAssignment.span);
break;
case 3 /* VarDecl */:
new (&this->as.VarDecl.var_id) (decltype(this->as.VarDecl.var_id))(rhs.as.VarDecl.var_id);
new (&this->as.VarDecl.init) (decltype(this->as.VarDecl.init))(rhs.as.VarDecl.init);
new (&this->as.VarDecl.span) (decltype(this->as.VarDecl.span))(rhs.as.VarDecl.span);
break;
case 4 /* If */:
new (&this->as.If.condition) (decltype(this->as.If.condition))(rhs.as.If.condition);
new (&this->as.If.then_block) (decltype(this->as.If.then_block))(rhs.as.If.then_block);
new (&this->as.If.else_statement) (decltype(this->as.If.else_statement))(rhs.as.If.else_statement);
new (&this->as.If.span) (decltype(this->as.If.span))(rhs.as.If.span);
break;
case 5 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(rhs.as.Block.block);
new (&this->as.Block.span) (decltype(this->as.Block.span))(rhs.as.Block.span);
break;
case 6 /* Loop */:
new (&this->as.Loop.block) (decltype(this->as.Loop.block))(rhs.as.Loop.block);
new (&this->as.Loop.span) (decltype(this->as.Loop.span))(rhs.as.Loop.span);
break;
case 7 /* While */:
new (&this->as.While.condition) (decltype(this->as.While.condition))(rhs.as.While.condition);
new (&this->as.While.block) (decltype(this->as.While.block))(rhs.as.While.block);
new (&this->as.While.span) (decltype(this->as.While.span))(rhs.as.While.span);
break;
case 8 /* Return */:
new (&this->as.Return.val) (decltype(this->as.Return.val))(rhs.as.Return.val);
new (&this->as.Return.span) (decltype(this->as.Return.span))(rhs.as.Return.span);
break;
case 9 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(rhs.as.Break.value);
break;
case 10 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(rhs.as.Continue.value);
break;
case 11 /* Throw */:
new (&this->as.Throw.expr) (decltype(this->as.Throw.expr))(rhs.as.Throw.expr);
new (&this->as.Throw.span) (decltype(this->as.Throw.span))(rhs.as.Throw.span);
break;
case 12 /* Yield */:
new (&this->as.Yield.expr) (decltype(this->as.Yield.expr))(rhs.as.Yield.expr);
new (&this->as.Yield.span) (decltype(this->as.Yield.span))(rhs.as.Yield.span);
break;
case 13 /* InlineCpp */:
new (&this->as.InlineCpp.lines) (decltype(this->as.InlineCpp.lines))(rhs.as.InlineCpp.lines);
new (&this->as.InlineCpp.span) (decltype(this->as.InlineCpp.span))(rhs.as.InlineCpp.span);
break;
case 14 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(rhs.as.Garbage.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.expr = rhs.as.Expression.expr;
this->as.Expression.span = rhs.as.Expression.span;
break;
case 1 /* Defer */:
this->as.Defer.statement = rhs.as.Defer.statement;
this->as.Defer.span = rhs.as.Defer.span;
break;
case 2 /* DestructuringAssignment */:
this->as.DestructuringAssignment.vars = rhs.as.DestructuringAssignment.vars;
this->as.DestructuringAssignment.var_decl = rhs.as.DestructuringAssignment.var_decl;
this->as.DestructuringAssignment.span = rhs.as.DestructuringAssignment.span;
break;
case 3 /* VarDecl */:
this->as.VarDecl.var_id = rhs.as.VarDecl.var_id;
this->as.VarDecl.init = rhs.as.VarDecl.init;
this->as.VarDecl.span = rhs.as.VarDecl.span;
break;
case 4 /* If */:
this->as.If.condition = rhs.as.If.condition;
this->as.If.then_block = rhs.as.If.then_block;
this->as.If.else_statement = rhs.as.If.else_statement;
this->as.If.span = rhs.as.If.span;
break;
case 5 /* Block */:
this->as.Block.block = rhs.as.Block.block;
this->as.Block.span = rhs.as.Block.span;
break;
case 6 /* Loop */:
this->as.Loop.block = rhs.as.Loop.block;
this->as.Loop.span = rhs.as.Loop.span;
break;
case 7 /* While */:
this->as.While.condition = rhs.as.While.condition;
this->as.While.block = rhs.as.While.block;
this->as.While.span = rhs.as.While.span;
break;
case 8 /* Return */:
this->as.Return.val = rhs.as.Return.val;
this->as.Return.span = rhs.as.Return.span;
break;
case 9 /* Break */:
this->as.Break.value = rhs.as.Break.value;
break;
case 10 /* Continue */:
this->as.Continue.value = rhs.as.Continue.value;
break;
case 11 /* Throw */:
this->as.Throw.expr = rhs.as.Throw.expr;
this->as.Throw.span = rhs.as.Throw.span;
break;
case 12 /* Yield */:
this->as.Yield.expr = rhs.as.Yield.expr;
this->as.Yield.span = rhs.as.Yield.span;
break;
case 13 /* InlineCpp */:
this->as.InlineCpp.lines = rhs.as.InlineCpp.lines;
this->as.InlineCpp.span = rhs.as.InlineCpp.span;
break;
case 14 /* Garbage */:
this->as.Garbage.value = rhs.as.Garbage.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedStatement::CheckedStatement(CheckedStatement const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.expr) (decltype(this->as.Expression.expr))(rhs.as.Expression.expr);
new (&this->as.Expression.span) (decltype(this->as.Expression.span))(rhs.as.Expression.span);
break;
case 1 /* Defer */:
new (&this->as.Defer.statement) (decltype(this->as.Defer.statement))(rhs.as.Defer.statement);
new (&this->as.Defer.span) (decltype(this->as.Defer.span))(rhs.as.Defer.span);
break;
case 2 /* DestructuringAssignment */:
new (&this->as.DestructuringAssignment.vars) (decltype(this->as.DestructuringAssignment.vars))(rhs.as.DestructuringAssignment.vars);
new (&this->as.DestructuringAssignment.var_decl) (decltype(this->as.DestructuringAssignment.var_decl))(rhs.as.DestructuringAssignment.var_decl);
new (&this->as.DestructuringAssignment.span) (decltype(this->as.DestructuringAssignment.span))(rhs.as.DestructuringAssignment.span);
break;
case 3 /* VarDecl */:
new (&this->as.VarDecl.var_id) (decltype(this->as.VarDecl.var_id))(rhs.as.VarDecl.var_id);
new (&this->as.VarDecl.init) (decltype(this->as.VarDecl.init))(rhs.as.VarDecl.init);
new (&this->as.VarDecl.span) (decltype(this->as.VarDecl.span))(rhs.as.VarDecl.span);
break;
case 4 /* If */:
new (&this->as.If.condition) (decltype(this->as.If.condition))(rhs.as.If.condition);
new (&this->as.If.then_block) (decltype(this->as.If.then_block))(rhs.as.If.then_block);
new (&this->as.If.else_statement) (decltype(this->as.If.else_statement))(rhs.as.If.else_statement);
new (&this->as.If.span) (decltype(this->as.If.span))(rhs.as.If.span);
break;
case 5 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(rhs.as.Block.block);
new (&this->as.Block.span) (decltype(this->as.Block.span))(rhs.as.Block.span);
break;
case 6 /* Loop */:
new (&this->as.Loop.block) (decltype(this->as.Loop.block))(rhs.as.Loop.block);
new (&this->as.Loop.span) (decltype(this->as.Loop.span))(rhs.as.Loop.span);
break;
case 7 /* While */:
new (&this->as.While.condition) (decltype(this->as.While.condition))(rhs.as.While.condition);
new (&this->as.While.block) (decltype(this->as.While.block))(rhs.as.While.block);
new (&this->as.While.span) (decltype(this->as.While.span))(rhs.as.While.span);
break;
case 8 /* Return */:
new (&this->as.Return.val) (decltype(this->as.Return.val))(rhs.as.Return.val);
new (&this->as.Return.span) (decltype(this->as.Return.span))(rhs.as.Return.span);
break;
case 9 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(rhs.as.Break.value);
break;
case 10 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(rhs.as.Continue.value);
break;
case 11 /* Throw */:
new (&this->as.Throw.expr) (decltype(this->as.Throw.expr))(rhs.as.Throw.expr);
new (&this->as.Throw.span) (decltype(this->as.Throw.span))(rhs.as.Throw.span);
break;
case 12 /* Yield */:
new (&this->as.Yield.expr) (decltype(this->as.Yield.expr))(rhs.as.Yield.expr);
new (&this->as.Yield.span) (decltype(this->as.Yield.span))(rhs.as.Yield.span);
break;
case 13 /* InlineCpp */:
new (&this->as.InlineCpp.lines) (decltype(this->as.InlineCpp.lines))(rhs.as.InlineCpp.lines);
new (&this->as.InlineCpp.span) (decltype(this->as.InlineCpp.span))(rhs.as.InlineCpp.span);
break;
case 14 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(rhs.as.Garbage.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedStatement& CheckedStatement::operator=(CheckedStatement &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.expr) (decltype(this->as.Expression.expr))(move(rhs.as.Expression.expr));
new (&this->as.Expression.span) (decltype(this->as.Expression.span))(move(rhs.as.Expression.span));
break;
case 1 /* Defer */:
new (&this->as.Defer.statement) (decltype(this->as.Defer.statement))(move(rhs.as.Defer.statement));
new (&this->as.Defer.span) (decltype(this->as.Defer.span))(move(rhs.as.Defer.span));
break;
case 2 /* DestructuringAssignment */:
new (&this->as.DestructuringAssignment.vars) (decltype(this->as.DestructuringAssignment.vars))(move(rhs.as.DestructuringAssignment.vars));
new (&this->as.DestructuringAssignment.var_decl) (decltype(this->as.DestructuringAssignment.var_decl))(move(rhs.as.DestructuringAssignment.var_decl));
new (&this->as.DestructuringAssignment.span) (decltype(this->as.DestructuringAssignment.span))(move(rhs.as.DestructuringAssignment.span));
break;
case 3 /* VarDecl */:
new (&this->as.VarDecl.var_id) (decltype(this->as.VarDecl.var_id))(move(rhs.as.VarDecl.var_id));
new (&this->as.VarDecl.init) (decltype(this->as.VarDecl.init))(move(rhs.as.VarDecl.init));
new (&this->as.VarDecl.span) (decltype(this->as.VarDecl.span))(move(rhs.as.VarDecl.span));
break;
case 4 /* If */:
new (&this->as.If.condition) (decltype(this->as.If.condition))(move(rhs.as.If.condition));
new (&this->as.If.then_block) (decltype(this->as.If.then_block))(move(rhs.as.If.then_block));
new (&this->as.If.else_statement) (decltype(this->as.If.else_statement))(move(rhs.as.If.else_statement));
new (&this->as.If.span) (decltype(this->as.If.span))(move(rhs.as.If.span));
break;
case 5 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(move(rhs.as.Block.block));
new (&this->as.Block.span) (decltype(this->as.Block.span))(move(rhs.as.Block.span));
break;
case 6 /* Loop */:
new (&this->as.Loop.block) (decltype(this->as.Loop.block))(move(rhs.as.Loop.block));
new (&this->as.Loop.span) (decltype(this->as.Loop.span))(move(rhs.as.Loop.span));
break;
case 7 /* While */:
new (&this->as.While.condition) (decltype(this->as.While.condition))(move(rhs.as.While.condition));
new (&this->as.While.block) (decltype(this->as.While.block))(move(rhs.as.While.block));
new (&this->as.While.span) (decltype(this->as.While.span))(move(rhs.as.While.span));
break;
case 8 /* Return */:
new (&this->as.Return.val) (decltype(this->as.Return.val))(move(rhs.as.Return.val));
new (&this->as.Return.span) (decltype(this->as.Return.span))(move(rhs.as.Return.span));
break;
case 9 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(move(rhs.as.Break.value));
break;
case 10 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(move(rhs.as.Continue.value));
break;
case 11 /* Throw */:
new (&this->as.Throw.expr) (decltype(this->as.Throw.expr))(move(rhs.as.Throw.expr));
new (&this->as.Throw.span) (decltype(this->as.Throw.span))(move(rhs.as.Throw.span));
break;
case 12 /* Yield */:
new (&this->as.Yield.expr) (decltype(this->as.Yield.expr))(move(rhs.as.Yield.expr));
new (&this->as.Yield.span) (decltype(this->as.Yield.span))(move(rhs.as.Yield.span));
break;
case 13 /* InlineCpp */:
new (&this->as.InlineCpp.lines) (decltype(this->as.InlineCpp.lines))(move(rhs.as.InlineCpp.lines));
new (&this->as.InlineCpp.span) (decltype(this->as.InlineCpp.span))(move(rhs.as.InlineCpp.span));
break;
case 14 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(move(rhs.as.Garbage.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.expr = move(rhs.as.Expression.expr);
this->as.Expression.span = move(rhs.as.Expression.span);
break;
case 1 /* Defer */:
this->as.Defer.statement = move(rhs.as.Defer.statement);
this->as.Defer.span = move(rhs.as.Defer.span);
break;
case 2 /* DestructuringAssignment */:
this->as.DestructuringAssignment.vars = move(rhs.as.DestructuringAssignment.vars);
this->as.DestructuringAssignment.var_decl = move(rhs.as.DestructuringAssignment.var_decl);
this->as.DestructuringAssignment.span = move(rhs.as.DestructuringAssignment.span);
break;
case 3 /* VarDecl */:
this->as.VarDecl.var_id = move(rhs.as.VarDecl.var_id);
this->as.VarDecl.init = move(rhs.as.VarDecl.init);
this->as.VarDecl.span = move(rhs.as.VarDecl.span);
break;
case 4 /* If */:
this->as.If.condition = move(rhs.as.If.condition);
this->as.If.then_block = move(rhs.as.If.then_block);
this->as.If.else_statement = move(rhs.as.If.else_statement);
this->as.If.span = move(rhs.as.If.span);
break;
case 5 /* Block */:
this->as.Block.block = move(rhs.as.Block.block);
this->as.Block.span = move(rhs.as.Block.span);
break;
case 6 /* Loop */:
this->as.Loop.block = move(rhs.as.Loop.block);
this->as.Loop.span = move(rhs.as.Loop.span);
break;
case 7 /* While */:
this->as.While.condition = move(rhs.as.While.condition);
this->as.While.block = move(rhs.as.While.block);
this->as.While.span = move(rhs.as.While.span);
break;
case 8 /* Return */:
this->as.Return.val = move(rhs.as.Return.val);
this->as.Return.span = move(rhs.as.Return.span);
break;
case 9 /* Break */:
this->as.Break.value = move(rhs.as.Break.value);
break;
case 10 /* Continue */:
this->as.Continue.value = move(rhs.as.Continue.value);
break;
case 11 /* Throw */:
this->as.Throw.expr = move(rhs.as.Throw.expr);
this->as.Throw.span = move(rhs.as.Throw.span);
break;
case 12 /* Yield */:
this->as.Yield.expr = move(rhs.as.Yield.expr);
this->as.Yield.span = move(rhs.as.Yield.span);
break;
case 13 /* InlineCpp */:
this->as.InlineCpp.lines = move(rhs.as.InlineCpp.lines);
this->as.InlineCpp.span = move(rhs.as.InlineCpp.span);
break;
case 14 /* Garbage */:
this->as.Garbage.value = move(rhs.as.Garbage.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedStatement::CheckedStatement(CheckedStatement &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.expr) (decltype(this->as.Expression.expr))(move(rhs.as.Expression.expr));
new (&this->as.Expression.span) (decltype(this->as.Expression.span))(move(rhs.as.Expression.span));
break;
case 1 /* Defer */:
new (&this->as.Defer.statement) (decltype(this->as.Defer.statement))(move(rhs.as.Defer.statement));
new (&this->as.Defer.span) (decltype(this->as.Defer.span))(move(rhs.as.Defer.span));
break;
case 2 /* DestructuringAssignment */:
new (&this->as.DestructuringAssignment.vars) (decltype(this->as.DestructuringAssignment.vars))(move(rhs.as.DestructuringAssignment.vars));
new (&this->as.DestructuringAssignment.var_decl) (decltype(this->as.DestructuringAssignment.var_decl))(move(rhs.as.DestructuringAssignment.var_decl));
new (&this->as.DestructuringAssignment.span) (decltype(this->as.DestructuringAssignment.span))(move(rhs.as.DestructuringAssignment.span));
break;
case 3 /* VarDecl */:
new (&this->as.VarDecl.var_id) (decltype(this->as.VarDecl.var_id))(move(rhs.as.VarDecl.var_id));
new (&this->as.VarDecl.init) (decltype(this->as.VarDecl.init))(move(rhs.as.VarDecl.init));
new (&this->as.VarDecl.span) (decltype(this->as.VarDecl.span))(move(rhs.as.VarDecl.span));
break;
case 4 /* If */:
new (&this->as.If.condition) (decltype(this->as.If.condition))(move(rhs.as.If.condition));
new (&this->as.If.then_block) (decltype(this->as.If.then_block))(move(rhs.as.If.then_block));
new (&this->as.If.else_statement) (decltype(this->as.If.else_statement))(move(rhs.as.If.else_statement));
new (&this->as.If.span) (decltype(this->as.If.span))(move(rhs.as.If.span));
break;
case 5 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(move(rhs.as.Block.block));
new (&this->as.Block.span) (decltype(this->as.Block.span))(move(rhs.as.Block.span));
break;
case 6 /* Loop */:
new (&this->as.Loop.block) (decltype(this->as.Loop.block))(move(rhs.as.Loop.block));
new (&this->as.Loop.span) (decltype(this->as.Loop.span))(move(rhs.as.Loop.span));
break;
case 7 /* While */:
new (&this->as.While.condition) (decltype(this->as.While.condition))(move(rhs.as.While.condition));
new (&this->as.While.block) (decltype(this->as.While.block))(move(rhs.as.While.block));
new (&this->as.While.span) (decltype(this->as.While.span))(move(rhs.as.While.span));
break;
case 8 /* Return */:
new (&this->as.Return.val) (decltype(this->as.Return.val))(move(rhs.as.Return.val));
new (&this->as.Return.span) (decltype(this->as.Return.span))(move(rhs.as.Return.span));
break;
case 9 /* Break */:
new (&this->as.Break.value) (decltype(this->as.Break.value))(move(rhs.as.Break.value));
break;
case 10 /* Continue */:
new (&this->as.Continue.value) (decltype(this->as.Continue.value))(move(rhs.as.Continue.value));
break;
case 11 /* Throw */:
new (&this->as.Throw.expr) (decltype(this->as.Throw.expr))(move(rhs.as.Throw.expr));
new (&this->as.Throw.span) (decltype(this->as.Throw.span))(move(rhs.as.Throw.span));
break;
case 12 /* Yield */:
new (&this->as.Yield.expr) (decltype(this->as.Yield.expr))(move(rhs.as.Yield.expr));
new (&this->as.Yield.span) (decltype(this->as.Yield.span))(move(rhs.as.Yield.span));
break;
case 13 /* InlineCpp */:
new (&this->as.InlineCpp.lines) (decltype(this->as.InlineCpp.lines))(move(rhs.as.InlineCpp.lines));
new (&this->as.InlineCpp.span) (decltype(this->as.InlineCpp.span))(move(rhs.as.InlineCpp.span));
break;
case 14 /* Garbage */:
new (&this->as.Garbage.value) (decltype(this->as.Garbage.value))(move(rhs.as.Garbage.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedStatement::~CheckedStatement(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void CheckedStatement::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Expression */:this->as.Expression.expr.~NonnullRefPtr();
this->as.Expression.span.~Span();
break;
case 1 /* Defer */:this->as.Defer.statement.~NonnullRefPtr();
this->as.Defer.span.~Span();
break;
case 2 /* DestructuringAssignment */:this->as.DestructuringAssignment.vars.~DynamicArray();
this->as.DestructuringAssignment.var_decl.~NonnullRefPtr();
this->as.DestructuringAssignment.span.~Span();
break;
case 3 /* VarDecl */:this->as.VarDecl.var_id.~VarId();
this->as.VarDecl.init.~NonnullRefPtr();
this->as.VarDecl.span.~Span();
break;
case 4 /* If */:this->as.If.condition.~NonnullRefPtr();
this->as.If.then_block.~CheckedBlock();
this->as.If.else_statement.~Optional();
this->as.If.span.~Span();
break;
case 5 /* Block */:this->as.Block.block.~CheckedBlock();
this->as.Block.span.~Span();
break;
case 6 /* Loop */:this->as.Loop.block.~CheckedBlock();
this->as.Loop.span.~Span();
break;
case 7 /* While */:this->as.While.condition.~NonnullRefPtr();
this->as.While.block.~CheckedBlock();
this->as.While.span.~Span();
break;
case 8 /* Return */:this->as.Return.val.~Optional();
this->as.Return.span.~Optional();
break;
case 9 /* Break */:this->as.Break.value.~Span();
break;
case 10 /* Continue */:this->as.Continue.value.~Span();
break;
case 11 /* Throw */:this->as.Throw.expr.~NonnullRefPtr();
this->as.Throw.span.~Span();
break;
case 12 /* Yield */:this->as.Yield.expr.~Optional();
this->as.Yield.span.~Span();
break;
case 13 /* InlineCpp */:this->as.InlineCpp.lines.~DynamicArray();
this->as.InlineCpp.span.~Span();
break;
case 14 /* Garbage */:this->as.Garbage.value.~Span();
break;
}
}
JaktInternal::Optional<Jakt::utility::Span> Jakt::types::CheckedStatement::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::utility::Span>, JaktInternal::Optional<Jakt::utility::Span>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::utility::Span>>(span));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<Jakt::utility::Span> const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;Jakt::utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;Jakt::utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;Jakt::utility::Span const& span = __jakt_match_value.value;
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
}

JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::types::CheckedStatement::none() {
{
return JaktInternal::OptionalNone();
}
}

Jakt::types::BlockControlFlow Jakt::types::CheckedStatement::maybe_control_flow(JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const statement,Jakt::types::BlockControlFlow const other_branch) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (statement.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(statement.value()->control_flow());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(other_branch.partial());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

Jakt::types::BlockControlFlow Jakt::types::CheckedStatement::control_flow() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* Return */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 11 /* Throw */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 9 /* Break */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(true));
case 10 /* Continue */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(false));
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (expr.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(expr.value()->control_flow().updated(Jakt::types::BlockControlFlow::AlwaysTransfersControl(false)));
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(false));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (val);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(then_block.control_flow);
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (else_statement.has_value());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(else_statement.value()->control_flow());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default:return JaktInternal::ExplicitValue(then_block.control_flow.branch_unify_with(Jakt::types::CheckedStatement::maybe_control_flow(else_statement,then_block.control_flow)));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(block.control_flow);
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *condition;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (val);
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = block.control_flow;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::NeverReturns());
default:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}else {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = block.control_flow;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (might_break);
if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
}else if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 2 /* NeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::NeverReturns());
case 0 /* AlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 3 /* MayReturn */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
default:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (block.control_flow.may_break());
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = block.control_flow;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* PartialAlwaysReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysReturns());
case 6 /* PartialNeverReturns */:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::NeverReturns());
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
default:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
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
}));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(expr->control_flow());
};/*case end*/
default:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ByteString Jakt::types::NumberConstant::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Signed */: {
builder.append("NumberConstant::Signed"sv);
[[maybe_unused]] auto const& that = this->as.Signed;
builder.appendff("({})", that.value);
break;}
case 1 /* Unsigned */: {
builder.append("NumberConstant::Unsigned"sv);
[[maybe_unused]] auto const& that = this->as.Unsigned;
builder.appendff("({})", that.value);
break;}
case 2 /* Floating */: {
builder.append("NumberConstant::Floating"sv);
[[maybe_unused]] auto const& that = this->as.Floating;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] NumberConstant NumberConstant::Signed(i64 value){
NumberConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Signed.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumberConstant NumberConstant::Unsigned(u64 value){
NumberConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Unsigned.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NumberConstant NumberConstant::Floating(f64 value){
NumberConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Floating.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
NumberConstant& NumberConstant::operator=(NumberConstant const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Signed */:
new (&this->as.Signed.value) (decltype(this->as.Signed.value))(rhs.as.Signed.value);
break;
case 1 /* Unsigned */:
new (&this->as.Unsigned.value) (decltype(this->as.Unsigned.value))(rhs.as.Unsigned.value);
break;
case 2 /* Floating */:
new (&this->as.Floating.value) (decltype(this->as.Floating.value))(rhs.as.Floating.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Signed */:
this->as.Signed.value = rhs.as.Signed.value;
break;
case 1 /* Unsigned */:
this->as.Unsigned.value = rhs.as.Unsigned.value;
break;
case 2 /* Floating */:
this->as.Floating.value = rhs.as.Floating.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
NumberConstant::NumberConstant(NumberConstant const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Signed */:
new (&this->as.Signed.value) (decltype(this->as.Signed.value))(rhs.as.Signed.value);
break;
case 1 /* Unsigned */:
new (&this->as.Unsigned.value) (decltype(this->as.Unsigned.value))(rhs.as.Unsigned.value);
break;
case 2 /* Floating */:
new (&this->as.Floating.value) (decltype(this->as.Floating.value))(rhs.as.Floating.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
NumberConstant& NumberConstant::operator=(NumberConstant &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Signed */:
new (&this->as.Signed.value) (decltype(this->as.Signed.value))(move(rhs.as.Signed.value));
break;
case 1 /* Unsigned */:
new (&this->as.Unsigned.value) (decltype(this->as.Unsigned.value))(move(rhs.as.Unsigned.value));
break;
case 2 /* Floating */:
new (&this->as.Floating.value) (decltype(this->as.Floating.value))(move(rhs.as.Floating.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Signed */:
this->as.Signed.value = move(rhs.as.Signed.value);
break;
case 1 /* Unsigned */:
this->as.Unsigned.value = move(rhs.as.Unsigned.value);
break;
case 2 /* Floating */:
this->as.Floating.value = move(rhs.as.Floating.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
NumberConstant::NumberConstant(NumberConstant &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Signed */:
new (&this->as.Signed.value) (decltype(this->as.Signed.value))(move(rhs.as.Signed.value));
break;
case 1 /* Unsigned */:
new (&this->as.Unsigned.value) (decltype(this->as.Unsigned.value))(move(rhs.as.Unsigned.value));
break;
case 2 /* Floating */:
new (&this->as.Floating.value) (decltype(this->as.Floating.value))(move(rhs.as.Floating.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
NumberConstant::~NumberConstant(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void NumberConstant::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Signed */:break;
case 1 /* Unsigned */:break;
case 2 /* Floating */:break;
}
}
bool Jakt::types::NumberConstant::can_fit_number(Jakt::ids::TypeId const type_id,NonnullRefPtr<Jakt::types::CheckedProgram> const program) const {
{
NonnullRefPtr<typename Jakt::types::Type> const type_ = program->get_type(type_id);
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Signed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Signed;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */:return JaktInternal::ExplicitValue(true);
case 5 /* U64 */:case 12 /* Usize */:return JaktInternal::ExplicitValue(value >= static_cast<i64>(0LL));
default:return JaktInternal::ExplicitValue((program->is_integer(type_id) && (value >= type_->min())) && (value <= infallible_integer_cast<i64>(type_->max())));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 1 /* Unsigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsigned;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */:case 12 /* Usize */:return JaktInternal::ExplicitValue(true);
default:return JaktInternal::ExplicitValue(program->is_integer(type_id) && (value <= type_->max()));
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 2 /* Floating */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Floating;f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */:{
Jakt::utility::todo(ByteString::from_utf8_without_validation("Implement casting f32 to f64"sv));
}
case 11 /* F64 */:return JaktInternal::ExplicitValue(true);
default:return JaktInternal::ExplicitValue(false);
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
});
}
}

size_t Jakt::types::NumberConstant::to_usize() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Signed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Signed;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(infallible_integer_cast<size_t>(value));
};/*case end*/
case 1 /* Unsigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsigned;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(infallible_integer_cast<size_t>(value));
};/*case end*/
case 2 /* Floating */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Floating;f64 const& value = __jakt_match_value.value;
{
Jakt::utility::panic(ByteString::from_utf8_without_validation("to_usize on a floating point constant"sv));
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

ByteString Jakt::types::CheckedNumericConstant::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* I8 */: {
builder.append("CheckedNumericConstant::I8"sv);
[[maybe_unused]] auto const& that = this->as.I8;
builder.appendff("({})", that.value);
break;}
case 1 /* I16 */: {
builder.append("CheckedNumericConstant::I16"sv);
[[maybe_unused]] auto const& that = this->as.I16;
builder.appendff("({})", that.value);
break;}
case 2 /* I32 */: {
builder.append("CheckedNumericConstant::I32"sv);
[[maybe_unused]] auto const& that = this->as.I32;
builder.appendff("({})", that.value);
break;}
case 3 /* I64 */: {
builder.append("CheckedNumericConstant::I64"sv);
[[maybe_unused]] auto const& that = this->as.I64;
builder.appendff("({})", that.value);
break;}
case 4 /* U8 */: {
builder.append("CheckedNumericConstant::U8"sv);
[[maybe_unused]] auto const& that = this->as.U8;
builder.appendff("({})", that.value);
break;}
case 5 /* U16 */: {
builder.append("CheckedNumericConstant::U16"sv);
[[maybe_unused]] auto const& that = this->as.U16;
builder.appendff("({})", that.value);
break;}
case 6 /* U32 */: {
builder.append("CheckedNumericConstant::U32"sv);
[[maybe_unused]] auto const& that = this->as.U32;
builder.appendff("({})", that.value);
break;}
case 7 /* U64 */: {
builder.append("CheckedNumericConstant::U64"sv);
[[maybe_unused]] auto const& that = this->as.U64;
builder.appendff("({})", that.value);
break;}
case 8 /* USize */: {
builder.append("CheckedNumericConstant::USize"sv);
[[maybe_unused]] auto const& that = this->as.USize;
builder.appendff("({})", that.value);
break;}
case 9 /* F32 */: {
builder.append("CheckedNumericConstant::F32"sv);
[[maybe_unused]] auto const& that = this->as.F32;
builder.appendff("({})", that.value);
break;}
case 10 /* F64 */: {
builder.append("CheckedNumericConstant::F64"sv);
[[maybe_unused]] auto const& that = this->as.F64;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::I8(i8 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.I8.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::I16(i16 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.I16.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::I32(i32 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.I32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::I64(i64 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.as.I64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::U8(u8 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
new (&__jakt_uninit_enum.as.U8.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::U16(u16 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
new (&__jakt_uninit_enum.as.U16.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::U32(u32 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
new (&__jakt_uninit_enum.as.U32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::U64(u64 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
new (&__jakt_uninit_enum.as.U64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::USize(u64 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
new (&__jakt_uninit_enum.as.USize.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::F32(f32 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
new (&__jakt_uninit_enum.as.F32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedNumericConstant CheckedNumericConstant::F64(f64 value){
CheckedNumericConstant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
new (&__jakt_uninit_enum.as.F64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
CheckedNumericConstant& CheckedNumericConstant::operator=(CheckedNumericConstant const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(rhs.as.I8.value);
break;
case 1 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(rhs.as.I16.value);
break;
case 2 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(rhs.as.I32.value);
break;
case 3 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(rhs.as.I64.value);
break;
case 4 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(rhs.as.U8.value);
break;
case 5 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(rhs.as.U16.value);
break;
case 6 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(rhs.as.U32.value);
break;
case 7 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(rhs.as.U64.value);
break;
case 8 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(rhs.as.USize.value);
break;
case 9 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(rhs.as.F32.value);
break;
case 10 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(rhs.as.F64.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
this->as.I8.value = rhs.as.I8.value;
break;
case 1 /* I16 */:
this->as.I16.value = rhs.as.I16.value;
break;
case 2 /* I32 */:
this->as.I32.value = rhs.as.I32.value;
break;
case 3 /* I64 */:
this->as.I64.value = rhs.as.I64.value;
break;
case 4 /* U8 */:
this->as.U8.value = rhs.as.U8.value;
break;
case 5 /* U16 */:
this->as.U16.value = rhs.as.U16.value;
break;
case 6 /* U32 */:
this->as.U32.value = rhs.as.U32.value;
break;
case 7 /* U64 */:
this->as.U64.value = rhs.as.U64.value;
break;
case 8 /* USize */:
this->as.USize.value = rhs.as.USize.value;
break;
case 9 /* F32 */:
this->as.F32.value = rhs.as.F32.value;
break;
case 10 /* F64 */:
this->as.F64.value = rhs.as.F64.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedNumericConstant::CheckedNumericConstant(CheckedNumericConstant const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(rhs.as.I8.value);
break;
case 1 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(rhs.as.I16.value);
break;
case 2 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(rhs.as.I32.value);
break;
case 3 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(rhs.as.I64.value);
break;
case 4 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(rhs.as.U8.value);
break;
case 5 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(rhs.as.U16.value);
break;
case 6 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(rhs.as.U32.value);
break;
case 7 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(rhs.as.U64.value);
break;
case 8 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(rhs.as.USize.value);
break;
case 9 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(rhs.as.F32.value);
break;
case 10 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(rhs.as.F64.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedNumericConstant& CheckedNumericConstant::operator=(CheckedNumericConstant &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(move(rhs.as.I8.value));
break;
case 1 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(move(rhs.as.I16.value));
break;
case 2 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(move(rhs.as.I32.value));
break;
case 3 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(move(rhs.as.I64.value));
break;
case 4 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(move(rhs.as.U8.value));
break;
case 5 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(move(rhs.as.U16.value));
break;
case 6 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(move(rhs.as.U32.value));
break;
case 7 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(move(rhs.as.U64.value));
break;
case 8 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(move(rhs.as.USize.value));
break;
case 9 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(move(rhs.as.F32.value));
break;
case 10 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(move(rhs.as.F64.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
this->as.I8.value = move(rhs.as.I8.value);
break;
case 1 /* I16 */:
this->as.I16.value = move(rhs.as.I16.value);
break;
case 2 /* I32 */:
this->as.I32.value = move(rhs.as.I32.value);
break;
case 3 /* I64 */:
this->as.I64.value = move(rhs.as.I64.value);
break;
case 4 /* U8 */:
this->as.U8.value = move(rhs.as.U8.value);
break;
case 5 /* U16 */:
this->as.U16.value = move(rhs.as.U16.value);
break;
case 6 /* U32 */:
this->as.U32.value = move(rhs.as.U32.value);
break;
case 7 /* U64 */:
this->as.U64.value = move(rhs.as.U64.value);
break;
case 8 /* USize */:
this->as.USize.value = move(rhs.as.USize.value);
break;
case 9 /* F32 */:
this->as.F32.value = move(rhs.as.F32.value);
break;
case 10 /* F64 */:
this->as.F64.value = move(rhs.as.F64.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedNumericConstant::CheckedNumericConstant(CheckedNumericConstant &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(move(rhs.as.I8.value));
break;
case 1 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(move(rhs.as.I16.value));
break;
case 2 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(move(rhs.as.I32.value));
break;
case 3 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(move(rhs.as.I64.value));
break;
case 4 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(move(rhs.as.U8.value));
break;
case 5 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(move(rhs.as.U16.value));
break;
case 6 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(move(rhs.as.U32.value));
break;
case 7 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(move(rhs.as.U64.value));
break;
case 8 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(move(rhs.as.USize.value));
break;
case 9 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(move(rhs.as.F32.value));
break;
case 10 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(move(rhs.as.F64.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedNumericConstant::~CheckedNumericConstant(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void CheckedNumericConstant::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* I8 */:break;
case 1 /* I16 */:break;
case 2 /* I32 */:break;
case 3 /* I64 */:break;
case 4 /* U8 */:break;
case 5 /* U16 */:break;
case 6 /* U32 */:break;
case 7 /* U64 */:break;
case 8 /* USize */:break;
case 9 /* F32 */:break;
case 10 /* F64 */:break;
}
}
JaktInternal::Optional<Jakt::types::NumberConstant> Jakt::types::CheckedNumericConstant::number_constant() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::NumberConstant>, JaktInternal::Optional<Jakt::types::NumberConstant>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Signed(infallible_integer_cast<i64>(value)));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Signed(infallible_integer_cast<i64>(value)));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Signed(infallible_integer_cast<i64>(value)));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Signed(static_cast<i64>(value)));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Unsigned(infallible_integer_cast<u64>(value)));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Unsigned(infallible_integer_cast<u64>(value)));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Unsigned(infallible_integer_cast<u64>(value)));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Unsigned(static_cast<u64>(value)));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Unsigned(static_cast<u64>(value)));
};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumberConstant::Floating(value));
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ByteString Jakt::types::StringLiteral::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Static */: {
builder.append("StringLiteral::Static"sv);
[[maybe_unused]] auto const& that = this->as.Static;
builder.appendff("(\"{}\")", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] StringLiteral StringLiteral::Static(ByteString value){
StringLiteral __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Static.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
StringLiteral& StringLiteral::operator=(StringLiteral const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Static */:
new (&this->as.Static.value) (decltype(this->as.Static.value))(rhs.as.Static.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Static */:
this->as.Static.value = rhs.as.Static.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
StringLiteral::StringLiteral(StringLiteral const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Static */:
new (&this->as.Static.value) (decltype(this->as.Static.value))(rhs.as.Static.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
StringLiteral& StringLiteral::operator=(StringLiteral &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Static */:
new (&this->as.Static.value) (decltype(this->as.Static.value))(move(rhs.as.Static.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Static */:
this->as.Static.value = move(rhs.as.Static.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
StringLiteral::StringLiteral(StringLiteral &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Static */:
new (&this->as.Static.value) (decltype(this->as.Static.value))(move(rhs.as.Static.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
StringLiteral::~StringLiteral(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void StringLiteral::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Static */:this->as.Static.value.~ByteString();
break;
}
}
ByteString Jakt::types::StringLiteral::to_string() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Static */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Static;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
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

ByteString Jakt::types::CheckedTypeCast::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Fallible */: {
builder.append("CheckedTypeCast::Fallible"sv);
[[maybe_unused]] auto const& that = this->as.Fallible;
builder.appendff("({})", that.value);
break;}
case 1 /* Infallible */: {
builder.append("CheckedTypeCast::Infallible"sv);
[[maybe_unused]] auto const& that = this->as.Infallible;
builder.appendff("({})", that.value);
break;}
case 2 /* Identity */: {
builder.append("CheckedTypeCast::Identity"sv);
[[maybe_unused]] auto const& that = this->as.Identity;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedTypeCast CheckedTypeCast::Fallible(Jakt::ids::TypeId value){
CheckedTypeCast __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Fallible.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedTypeCast CheckedTypeCast::Infallible(Jakt::ids::TypeId value){
CheckedTypeCast __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Infallible.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedTypeCast CheckedTypeCast::Identity(Jakt::ids::TypeId value){
CheckedTypeCast __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Identity.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
CheckedTypeCast& CheckedTypeCast::operator=(CheckedTypeCast const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
new (&this->as.Fallible.value) (decltype(this->as.Fallible.value))(rhs.as.Fallible.value);
break;
case 1 /* Infallible */:
new (&this->as.Infallible.value) (decltype(this->as.Infallible.value))(rhs.as.Infallible.value);
break;
case 2 /* Identity */:
new (&this->as.Identity.value) (decltype(this->as.Identity.value))(rhs.as.Identity.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
this->as.Fallible.value = rhs.as.Fallible.value;
break;
case 1 /* Infallible */:
this->as.Infallible.value = rhs.as.Infallible.value;
break;
case 2 /* Identity */:
this->as.Identity.value = rhs.as.Identity.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedTypeCast::CheckedTypeCast(CheckedTypeCast const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
new (&this->as.Fallible.value) (decltype(this->as.Fallible.value))(rhs.as.Fallible.value);
break;
case 1 /* Infallible */:
new (&this->as.Infallible.value) (decltype(this->as.Infallible.value))(rhs.as.Infallible.value);
break;
case 2 /* Identity */:
new (&this->as.Identity.value) (decltype(this->as.Identity.value))(rhs.as.Identity.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedTypeCast& CheckedTypeCast::operator=(CheckedTypeCast &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
new (&this->as.Fallible.value) (decltype(this->as.Fallible.value))(move(rhs.as.Fallible.value));
break;
case 1 /* Infallible */:
new (&this->as.Infallible.value) (decltype(this->as.Infallible.value))(move(rhs.as.Infallible.value));
break;
case 2 /* Identity */:
new (&this->as.Identity.value) (decltype(this->as.Identity.value))(move(rhs.as.Identity.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
this->as.Fallible.value = move(rhs.as.Fallible.value);
break;
case 1 /* Infallible */:
this->as.Infallible.value = move(rhs.as.Infallible.value);
break;
case 2 /* Identity */:
this->as.Identity.value = move(rhs.as.Identity.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedTypeCast::CheckedTypeCast(CheckedTypeCast &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Fallible */:
new (&this->as.Fallible.value) (decltype(this->as.Fallible.value))(move(rhs.as.Fallible.value));
break;
case 1 /* Infallible */:
new (&this->as.Infallible.value) (decltype(this->as.Infallible.value))(move(rhs.as.Infallible.value));
break;
case 2 /* Identity */:
new (&this->as.Identity.value) (decltype(this->as.Identity.value))(move(rhs.as.Identity.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedTypeCast::~CheckedTypeCast(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void CheckedTypeCast::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Fallible */:this->as.Fallible.value.~TypeId();
break;
case 1 /* Infallible */:this->as.Infallible.value.~TypeId();
break;
case 2 /* Identity */:this->as.Identity.value.~TypeId();
break;
}
}
Jakt::ids::TypeId Jakt::types::CheckedTypeCast::type_id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, Jakt::ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Fallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fallible;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 1 /* Infallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Infallible;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 2 /* Identity */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identity;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
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

ByteString Jakt::types::CheckedUnaryOperator::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* PreIncrement */: {
return ByteString("CheckedUnaryOperator::PreIncrement"sv);
break;}
case 1 /* PostIncrement */: {
return ByteString("CheckedUnaryOperator::PostIncrement"sv);
break;}
case 2 /* PreDecrement */: {
return ByteString("CheckedUnaryOperator::PreDecrement"sv);
break;}
case 3 /* PostDecrement */: {
return ByteString("CheckedUnaryOperator::PostDecrement"sv);
break;}
case 4 /* Negate */: {
return ByteString("CheckedUnaryOperator::Negate"sv);
break;}
case 5 /* Dereference */: {
return ByteString("CheckedUnaryOperator::Dereference"sv);
break;}
case 6 /* RawAddress */: {
return ByteString("CheckedUnaryOperator::RawAddress"sv);
break;}
case 7 /* Reference */: {
return ByteString("CheckedUnaryOperator::Reference"sv);
break;}
case 8 /* MutableReference */: {
return ByteString("CheckedUnaryOperator::MutableReference"sv);
break;}
case 9 /* LogicalNot */: {
return ByteString("CheckedUnaryOperator::LogicalNot"sv);
break;}
case 10 /* BitwiseNot */: {
return ByteString("CheckedUnaryOperator::BitwiseNot"sv);
break;}
case 11 /* TypeCast */: {
builder.append("CheckedUnaryOperator::TypeCast"sv);
[[maybe_unused]] auto const& that = this->as.TypeCast;
builder.appendff("({})", that.value);
break;}
case 12 /* Is */: {
builder.append("CheckedUnaryOperator::Is"sv);
[[maybe_unused]] auto const& that = this->as.Is;
builder.appendff("({})", that.value);
break;}
case 13 /* IsEnumVariant */: {
builder.append("CheckedUnaryOperator::IsEnumVariant"sv);
[[maybe_unused]] auto const& that = this->as.IsEnumVariant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enum_variant: {}, ", that.enum_variant);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("bindings: {}, ", that.bindings);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 14 /* IsSome */: {
return ByteString("CheckedUnaryOperator::IsSome"sv);
break;}
case 15 /* IsNone */: {
return ByteString("CheckedUnaryOperator::IsNone"sv);
break;}
case 16 /* Sizeof */: {
builder.append("CheckedUnaryOperator::Sizeof"sv);
[[maybe_unused]] auto const& that = this->as.Sizeof;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::PreIncrement(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::PostIncrement(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::PreDecrement(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::PostDecrement(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::Negate(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::Dereference(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::RawAddress(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 7;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::Reference(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 8;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::MutableReference(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 9;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::LogicalNot(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 10;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::BitwiseNot(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 11;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::TypeCast(Jakt::types::CheckedTypeCast value){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
new (&__jakt_uninit_enum.as.TypeCast.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::Is(Jakt::ids::TypeId value){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
new (&__jakt_uninit_enum.as.Is.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::IsEnumVariant(Jakt::types::CheckedEnumVariant enum_variant, JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding> bindings, Jakt::ids::TypeId type_id){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 14;
new (&__jakt_uninit_enum.as.IsEnumVariant.enum_variant) (decltype(enum_variant))(move(enum_variant));
new (&__jakt_uninit_enum.as.IsEnumVariant.bindings) (decltype(bindings))(move(bindings));
new (&__jakt_uninit_enum.as.IsEnumVariant.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::IsSome(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 15;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::IsNone(){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 16;
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::Sizeof(Jakt::ids::TypeId value){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 17;
new (&__jakt_uninit_enum.as.Sizeof.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
CheckedUnaryOperator& CheckedUnaryOperator::operator=(CheckedUnaryOperator const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
new (&this->as.TypeCast.value) (decltype(this->as.TypeCast.value))(rhs.as.TypeCast.value);
break;
case 12 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(rhs.as.Is.value);
break;
case 13 /* IsEnumVariant */:
new (&this->as.IsEnumVariant.enum_variant) (decltype(this->as.IsEnumVariant.enum_variant))(rhs.as.IsEnumVariant.enum_variant);
new (&this->as.IsEnumVariant.bindings) (decltype(this->as.IsEnumVariant.bindings))(rhs.as.IsEnumVariant.bindings);
new (&this->as.IsEnumVariant.type_id) (decltype(this->as.IsEnumVariant.type_id))(rhs.as.IsEnumVariant.type_id);
break;
case 14 /* IsSome */:
break;
case 15 /* IsNone */:
break;
case 16 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(rhs.as.Sizeof.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
this->as.TypeCast.value = rhs.as.TypeCast.value;
break;
case 12 /* Is */:
this->as.Is.value = rhs.as.Is.value;
break;
case 13 /* IsEnumVariant */:
this->as.IsEnumVariant.enum_variant = rhs.as.IsEnumVariant.enum_variant;
this->as.IsEnumVariant.bindings = rhs.as.IsEnumVariant.bindings;
this->as.IsEnumVariant.type_id = rhs.as.IsEnumVariant.type_id;
break;
case 14 /* IsSome */:
break;
case 15 /* IsNone */:
break;
case 16 /* Sizeof */:
this->as.Sizeof.value = rhs.as.Sizeof.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedUnaryOperator::CheckedUnaryOperator(CheckedUnaryOperator const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
new (&this->as.TypeCast.value) (decltype(this->as.TypeCast.value))(rhs.as.TypeCast.value);
break;
case 12 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(rhs.as.Is.value);
break;
case 13 /* IsEnumVariant */:
new (&this->as.IsEnumVariant.enum_variant) (decltype(this->as.IsEnumVariant.enum_variant))(rhs.as.IsEnumVariant.enum_variant);
new (&this->as.IsEnumVariant.bindings) (decltype(this->as.IsEnumVariant.bindings))(rhs.as.IsEnumVariant.bindings);
new (&this->as.IsEnumVariant.type_id) (decltype(this->as.IsEnumVariant.type_id))(rhs.as.IsEnumVariant.type_id);
break;
case 14 /* IsSome */:
break;
case 15 /* IsNone */:
break;
case 16 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(rhs.as.Sizeof.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedUnaryOperator& CheckedUnaryOperator::operator=(CheckedUnaryOperator &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
new (&this->as.TypeCast.value) (decltype(this->as.TypeCast.value))(move(rhs.as.TypeCast.value));
break;
case 12 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(move(rhs.as.Is.value));
break;
case 13 /* IsEnumVariant */:
new (&this->as.IsEnumVariant.enum_variant) (decltype(this->as.IsEnumVariant.enum_variant))(move(rhs.as.IsEnumVariant.enum_variant));
new (&this->as.IsEnumVariant.bindings) (decltype(this->as.IsEnumVariant.bindings))(move(rhs.as.IsEnumVariant.bindings));
new (&this->as.IsEnumVariant.type_id) (decltype(this->as.IsEnumVariant.type_id))(move(rhs.as.IsEnumVariant.type_id));
break;
case 14 /* IsSome */:
break;
case 15 /* IsNone */:
break;
case 16 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(move(rhs.as.Sizeof.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
this->as.TypeCast.value = move(rhs.as.TypeCast.value);
break;
case 12 /* Is */:
this->as.Is.value = move(rhs.as.Is.value);
break;
case 13 /* IsEnumVariant */:
this->as.IsEnumVariant.enum_variant = move(rhs.as.IsEnumVariant.enum_variant);
this->as.IsEnumVariant.bindings = move(rhs.as.IsEnumVariant.bindings);
this->as.IsEnumVariant.type_id = move(rhs.as.IsEnumVariant.type_id);
break;
case 14 /* IsSome */:
break;
case 15 /* IsNone */:
break;
case 16 /* Sizeof */:
this->as.Sizeof.value = move(rhs.as.Sizeof.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedUnaryOperator::CheckedUnaryOperator(CheckedUnaryOperator &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* PreIncrement */:
break;
case 1 /* PostIncrement */:
break;
case 2 /* PreDecrement */:
break;
case 3 /* PostDecrement */:
break;
case 4 /* Negate */:
break;
case 5 /* Dereference */:
break;
case 6 /* RawAddress */:
break;
case 7 /* Reference */:
break;
case 8 /* MutableReference */:
break;
case 9 /* LogicalNot */:
break;
case 10 /* BitwiseNot */:
break;
case 11 /* TypeCast */:
new (&this->as.TypeCast.value) (decltype(this->as.TypeCast.value))(move(rhs.as.TypeCast.value));
break;
case 12 /* Is */:
new (&this->as.Is.value) (decltype(this->as.Is.value))(move(rhs.as.Is.value));
break;
case 13 /* IsEnumVariant */:
new (&this->as.IsEnumVariant.enum_variant) (decltype(this->as.IsEnumVariant.enum_variant))(move(rhs.as.IsEnumVariant.enum_variant));
new (&this->as.IsEnumVariant.bindings) (decltype(this->as.IsEnumVariant.bindings))(move(rhs.as.IsEnumVariant.bindings));
new (&this->as.IsEnumVariant.type_id) (decltype(this->as.IsEnumVariant.type_id))(move(rhs.as.IsEnumVariant.type_id));
break;
case 14 /* IsSome */:
break;
case 15 /* IsNone */:
break;
case 16 /* Sizeof */:
new (&this->as.Sizeof.value) (decltype(this->as.Sizeof.value))(move(rhs.as.Sizeof.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedUnaryOperator::~CheckedUnaryOperator(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void CheckedUnaryOperator::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* PreIncrement */:break;
case 1 /* PostIncrement */:break;
case 2 /* PreDecrement */:break;
case 3 /* PostDecrement */:break;
case 4 /* Negate */:break;
case 5 /* Dereference */:break;
case 6 /* RawAddress */:break;
case 7 /* Reference */:break;
case 8 /* MutableReference */:break;
case 9 /* LogicalNot */:break;
case 10 /* BitwiseNot */:break;
case 11 /* TypeCast */:this->as.TypeCast.value.~CheckedTypeCast();
break;
case 12 /* Is */:this->as.Is.value.~TypeId();
break;
case 13 /* IsEnumVariant */:this->as.IsEnumVariant.enum_variant.~CheckedEnumVariant();
this->as.IsEnumVariant.bindings.~DynamicArray();
this->as.IsEnumVariant.type_id.~TypeId();
break;
case 14 /* IsSome */:break;
case 15 /* IsNone */:break;
case 16 /* Sizeof */:this->as.Sizeof.value.~TypeId();
break;
}
}
ByteString Jakt::types::CheckedMatchBody::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Expression */: {
builder.append("CheckedMatchBody::Expression"sv);
[[maybe_unused]] auto const& that = this->as.Expression;
builder.appendff("({})", that.value);
break;}
case 1 /* Block */: {
builder.append("CheckedMatchBody::Block"sv);
[[maybe_unused]] auto const& that = this->as.Block;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedMatchBody CheckedMatchBody::Expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> value){
CheckedMatchBody __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Expression.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedMatchBody CheckedMatchBody::Block(Jakt::types::CheckedBlock value){
CheckedMatchBody __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Block.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
CheckedMatchBody& CheckedMatchBody::operator=(CheckedMatchBody const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(rhs.as.Expression.value);
break;
case 1 /* Block */:
new (&this->as.Block.value) (decltype(this->as.Block.value))(rhs.as.Block.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.value = rhs.as.Expression.value;
break;
case 1 /* Block */:
this->as.Block.value = rhs.as.Block.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedMatchBody::CheckedMatchBody(CheckedMatchBody const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(rhs.as.Expression.value);
break;
case 1 /* Block */:
new (&this->as.Block.value) (decltype(this->as.Block.value))(rhs.as.Block.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedMatchBody& CheckedMatchBody::operator=(CheckedMatchBody &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(move(rhs.as.Expression.value));
break;
case 1 /* Block */:
new (&this->as.Block.value) (decltype(this->as.Block.value))(move(rhs.as.Block.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.value = move(rhs.as.Expression.value);
break;
case 1 /* Block */:
this->as.Block.value = move(rhs.as.Block.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedMatchBody::CheckedMatchBody(CheckedMatchBody &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(move(rhs.as.Expression.value));
break;
case 1 /* Block */:
new (&this->as.Block.value) (decltype(this->as.Block.value))(move(rhs.as.Block.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedMatchBody::~CheckedMatchBody(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void CheckedMatchBody::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Expression */:this->as.Expression.value.~NonnullRefPtr();
break;
case 1 /* Block */:this->as.Block.value.~CheckedBlock();
break;
}
}
ByteString Jakt::types::CheckedMatchPattern::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* EnumVariant */: {
builder.append("CheckedMatchPattern::EnumVariant"sv);
[[maybe_unused]] auto const& that = this->as.EnumVariant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("args: {}, ", that.args);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("subject_type_id: {}, ", that.subject_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}, ", that.scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
case 1 /* Expression */: {
builder.append("CheckedMatchPattern::Expression"sv);
[[maybe_unused]] auto const& that = this->as.Expression;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expression: {}, ", that.expression);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
case 2 /* ClassInstance */: {
builder.append("CheckedMatchPattern::ClassInstance"sv);
[[maybe_unused]] auto const& that = this->as.ClassInstance;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type: {}, ", that.type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("rebind_name: {}, ", that.rebind_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
case 3 /* CatchAll */: {
builder.append("CheckedMatchPattern::CatchAll"sv);
[[maybe_unused]] auto const& that = this->as.CatchAll;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("has_arguments: {}, ", that.has_arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedMatchPattern CheckedMatchPattern::EnumVariant(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults, ByteString name, JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> args, Jakt::ids::TypeId subject_type_id, size_t index, Jakt::ids::ScopeId scope_id, Jakt::utility::Span marker_span){
CheckedMatchPattern __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.EnumVariant.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.EnumVariant.args) (decltype(args))(move(args));
new (&__jakt_uninit_enum.as.EnumVariant.subject_type_id) (decltype(subject_type_id))(move(subject_type_id));
new (&__jakt_uninit_enum.as.EnumVariant.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum.as.EnumVariant.scope_id) (decltype(scope_id))(move(scope_id));
new (&__jakt_uninit_enum.as.EnumVariant.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedMatchPattern CheckedMatchPattern::Expression(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults, NonnullRefPtr<typename Jakt::types::CheckedExpression> expression, Jakt::utility::Span marker_span){
CheckedMatchPattern __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.Expression.expression) (decltype(expression))(move(expression));
new (&__jakt_uninit_enum.as.Expression.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedMatchPattern CheckedMatchPattern::ClassInstance(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults, Jakt::ids::TypeId type, JaktInternal::Optional<Jakt::types::ClassInstanceRebind> rebind_name, Jakt::utility::Span marker_span){
CheckedMatchPattern __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.ClassInstance.type) (decltype(type))(move(type));
new (&__jakt_uninit_enum.as.ClassInstance.rebind_name) (decltype(rebind_name))(move(rebind_name));
new (&__jakt_uninit_enum.as.ClassInstance.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedMatchPattern CheckedMatchPattern::CatchAll(JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> defaults, bool has_arguments, Jakt::utility::Span marker_span){
CheckedMatchPattern __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.CatchAll.has_arguments) (decltype(has_arguments))(move(has_arguments));
new (&__jakt_uninit_enum.as.CatchAll.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
CheckedMatchPattern& CheckedMatchPattern::operator=(CheckedMatchPattern const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.defaults = rhs.common.init_common.defaults;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(rhs.as.EnumVariant.name);
new (&this->as.EnumVariant.args) (decltype(this->as.EnumVariant.args))(rhs.as.EnumVariant.args);
new (&this->as.EnumVariant.subject_type_id) (decltype(this->as.EnumVariant.subject_type_id))(rhs.as.EnumVariant.subject_type_id);
new (&this->as.EnumVariant.index) (decltype(this->as.EnumVariant.index))(rhs.as.EnumVariant.index);
new (&this->as.EnumVariant.scope_id) (decltype(this->as.EnumVariant.scope_id))(rhs.as.EnumVariant.scope_id);
new (&this->as.EnumVariant.marker_span) (decltype(this->as.EnumVariant.marker_span))(rhs.as.EnumVariant.marker_span);
break;
case 1 /* Expression */:
new (&this->as.Expression.expression) (decltype(this->as.Expression.expression))(rhs.as.Expression.expression);
new (&this->as.Expression.marker_span) (decltype(this->as.Expression.marker_span))(rhs.as.Expression.marker_span);
break;
case 2 /* ClassInstance */:
new (&this->as.ClassInstance.type) (decltype(this->as.ClassInstance.type))(rhs.as.ClassInstance.type);
new (&this->as.ClassInstance.rebind_name) (decltype(this->as.ClassInstance.rebind_name))(rhs.as.ClassInstance.rebind_name);
new (&this->as.ClassInstance.marker_span) (decltype(this->as.ClassInstance.marker_span))(rhs.as.ClassInstance.marker_span);
break;
case 3 /* CatchAll */:
new (&this->as.CatchAll.has_arguments) (decltype(this->as.CatchAll.has_arguments))(rhs.as.CatchAll.has_arguments);
new (&this->as.CatchAll.marker_span) (decltype(this->as.CatchAll.marker_span))(rhs.as.CatchAll.marker_span);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
this->as.EnumVariant.name = rhs.as.EnumVariant.name;
this->as.EnumVariant.args = rhs.as.EnumVariant.args;
this->as.EnumVariant.subject_type_id = rhs.as.EnumVariant.subject_type_id;
this->as.EnumVariant.index = rhs.as.EnumVariant.index;
this->as.EnumVariant.scope_id = rhs.as.EnumVariant.scope_id;
this->as.EnumVariant.marker_span = rhs.as.EnumVariant.marker_span;
break;
case 1 /* Expression */:
this->as.Expression.expression = rhs.as.Expression.expression;
this->as.Expression.marker_span = rhs.as.Expression.marker_span;
break;
case 2 /* ClassInstance */:
this->as.ClassInstance.type = rhs.as.ClassInstance.type;
this->as.ClassInstance.rebind_name = rhs.as.ClassInstance.rebind_name;
this->as.ClassInstance.marker_span = rhs.as.ClassInstance.marker_span;
break;
case 3 /* CatchAll */:
this->as.CatchAll.has_arguments = rhs.as.CatchAll.has_arguments;
this->as.CatchAll.marker_span = rhs.as.CatchAll.marker_span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedMatchPattern::CheckedMatchPattern(CheckedMatchPattern const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.defaults) (decltype(this->common.init_common.defaults))(rhs.common.init_common.defaults);
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(rhs.as.EnumVariant.name);
new (&this->as.EnumVariant.args) (decltype(this->as.EnumVariant.args))(rhs.as.EnumVariant.args);
new (&this->as.EnumVariant.subject_type_id) (decltype(this->as.EnumVariant.subject_type_id))(rhs.as.EnumVariant.subject_type_id);
new (&this->as.EnumVariant.index) (decltype(this->as.EnumVariant.index))(rhs.as.EnumVariant.index);
new (&this->as.EnumVariant.scope_id) (decltype(this->as.EnumVariant.scope_id))(rhs.as.EnumVariant.scope_id);
new (&this->as.EnumVariant.marker_span) (decltype(this->as.EnumVariant.marker_span))(rhs.as.EnumVariant.marker_span);
break;
case 1 /* Expression */:
new (&this->as.Expression.expression) (decltype(this->as.Expression.expression))(rhs.as.Expression.expression);
new (&this->as.Expression.marker_span) (decltype(this->as.Expression.marker_span))(rhs.as.Expression.marker_span);
break;
case 2 /* ClassInstance */:
new (&this->as.ClassInstance.type) (decltype(this->as.ClassInstance.type))(rhs.as.ClassInstance.type);
new (&this->as.ClassInstance.rebind_name) (decltype(this->as.ClassInstance.rebind_name))(rhs.as.ClassInstance.rebind_name);
new (&this->as.ClassInstance.marker_span) (decltype(this->as.ClassInstance.marker_span))(rhs.as.ClassInstance.marker_span);
break;
case 3 /* CatchAll */:
new (&this->as.CatchAll.has_arguments) (decltype(this->as.CatchAll.has_arguments))(rhs.as.CatchAll.has_arguments);
new (&this->as.CatchAll.marker_span) (decltype(this->as.CatchAll.marker_span))(rhs.as.CatchAll.marker_span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedMatchPattern& CheckedMatchPattern::operator=(CheckedMatchPattern &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.defaults = move(rhs.common.init_common.defaults);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(move(rhs.as.EnumVariant.name));
new (&this->as.EnumVariant.args) (decltype(this->as.EnumVariant.args))(move(rhs.as.EnumVariant.args));
new (&this->as.EnumVariant.subject_type_id) (decltype(this->as.EnumVariant.subject_type_id))(move(rhs.as.EnumVariant.subject_type_id));
new (&this->as.EnumVariant.index) (decltype(this->as.EnumVariant.index))(move(rhs.as.EnumVariant.index));
new (&this->as.EnumVariant.scope_id) (decltype(this->as.EnumVariant.scope_id))(move(rhs.as.EnumVariant.scope_id));
new (&this->as.EnumVariant.marker_span) (decltype(this->as.EnumVariant.marker_span))(move(rhs.as.EnumVariant.marker_span));
break;
case 1 /* Expression */:
new (&this->as.Expression.expression) (decltype(this->as.Expression.expression))(move(rhs.as.Expression.expression));
new (&this->as.Expression.marker_span) (decltype(this->as.Expression.marker_span))(move(rhs.as.Expression.marker_span));
break;
case 2 /* ClassInstance */:
new (&this->as.ClassInstance.type) (decltype(this->as.ClassInstance.type))(move(rhs.as.ClassInstance.type));
new (&this->as.ClassInstance.rebind_name) (decltype(this->as.ClassInstance.rebind_name))(move(rhs.as.ClassInstance.rebind_name));
new (&this->as.ClassInstance.marker_span) (decltype(this->as.ClassInstance.marker_span))(move(rhs.as.ClassInstance.marker_span));
break;
case 3 /* CatchAll */:
new (&this->as.CatchAll.has_arguments) (decltype(this->as.CatchAll.has_arguments))(move(rhs.as.CatchAll.has_arguments));
new (&this->as.CatchAll.marker_span) (decltype(this->as.CatchAll.marker_span))(move(rhs.as.CatchAll.marker_span));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
this->as.EnumVariant.name = move(rhs.as.EnumVariant.name);
this->as.EnumVariant.args = move(rhs.as.EnumVariant.args);
this->as.EnumVariant.subject_type_id = move(rhs.as.EnumVariant.subject_type_id);
this->as.EnumVariant.index = move(rhs.as.EnumVariant.index);
this->as.EnumVariant.scope_id = move(rhs.as.EnumVariant.scope_id);
this->as.EnumVariant.marker_span = move(rhs.as.EnumVariant.marker_span);
break;
case 1 /* Expression */:
this->as.Expression.expression = move(rhs.as.Expression.expression);
this->as.Expression.marker_span = move(rhs.as.Expression.marker_span);
break;
case 2 /* ClassInstance */:
this->as.ClassInstance.type = move(rhs.as.ClassInstance.type);
this->as.ClassInstance.rebind_name = move(rhs.as.ClassInstance.rebind_name);
this->as.ClassInstance.marker_span = move(rhs.as.ClassInstance.marker_span);
break;
case 3 /* CatchAll */:
this->as.CatchAll.has_arguments = move(rhs.as.CatchAll.has_arguments);
this->as.CatchAll.marker_span = move(rhs.as.CatchAll.marker_span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedMatchPattern::CheckedMatchPattern(CheckedMatchPattern &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.defaults) (decltype(this->common.init_common.defaults))(move(rhs.common.init_common.defaults));
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(move(rhs.as.EnumVariant.name));
new (&this->as.EnumVariant.args) (decltype(this->as.EnumVariant.args))(move(rhs.as.EnumVariant.args));
new (&this->as.EnumVariant.subject_type_id) (decltype(this->as.EnumVariant.subject_type_id))(move(rhs.as.EnumVariant.subject_type_id));
new (&this->as.EnumVariant.index) (decltype(this->as.EnumVariant.index))(move(rhs.as.EnumVariant.index));
new (&this->as.EnumVariant.scope_id) (decltype(this->as.EnumVariant.scope_id))(move(rhs.as.EnumVariant.scope_id));
new (&this->as.EnumVariant.marker_span) (decltype(this->as.EnumVariant.marker_span))(move(rhs.as.EnumVariant.marker_span));
break;
case 1 /* Expression */:
new (&this->as.Expression.expression) (decltype(this->as.Expression.expression))(move(rhs.as.Expression.expression));
new (&this->as.Expression.marker_span) (decltype(this->as.Expression.marker_span))(move(rhs.as.Expression.marker_span));
break;
case 2 /* ClassInstance */:
new (&this->as.ClassInstance.type) (decltype(this->as.ClassInstance.type))(move(rhs.as.ClassInstance.type));
new (&this->as.ClassInstance.rebind_name) (decltype(this->as.ClassInstance.rebind_name))(move(rhs.as.ClassInstance.rebind_name));
new (&this->as.ClassInstance.marker_span) (decltype(this->as.ClassInstance.marker_span))(move(rhs.as.ClassInstance.marker_span));
break;
case 3 /* CatchAll */:
new (&this->as.CatchAll.has_arguments) (decltype(this->as.CatchAll.has_arguments))(move(rhs.as.CatchAll.has_arguments));
new (&this->as.CatchAll.marker_span) (decltype(this->as.CatchAll.marker_span))(move(rhs.as.CatchAll.marker_span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedMatchPattern::~CheckedMatchPattern(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.defaults.~DynamicArray();
this->__jakt_destroy_variant(); }
void CheckedMatchPattern::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* EnumVariant */:this->as.EnumVariant.name.~ByteString();
this->as.EnumVariant.args.~DynamicArray();
this->as.EnumVariant.subject_type_id.~TypeId();
this->as.EnumVariant.scope_id.~ScopeId();
this->as.EnumVariant.marker_span.~Span();
break;
case 1 /* Expression */:this->as.Expression.expression.~NonnullRefPtr();
this->as.Expression.marker_span.~Span();
break;
case 2 /* ClassInstance */:this->as.ClassInstance.type.~TypeId();
this->as.ClassInstance.rebind_name.~Optional();
this->as.ClassInstance.marker_span.~Span();
break;
case 3 /* CatchAll */:this->as.CatchAll.marker_span.~Span();
break;
}
}
ByteString Jakt::types::CheckedExpression::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Boolean */: {
builder.append("CheckedExpression::Boolean"sv);
[[maybe_unused]] auto const& that = this->as.Boolean;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: {}, ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 1 /* NumericConstant */: {
builder.append("CheckedExpression::NumericConstant"sv);
[[maybe_unused]] auto const& that = this->as.NumericConstant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: {}, ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 2 /* QuotedString */: {
builder.append("CheckedExpression::QuotedString"sv);
[[maybe_unused]] auto const& that = this->as.QuotedString;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: {}, ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 3 /* ByteConstant */: {
builder.append("CheckedExpression::ByteConstant"sv);
[[maybe_unused]] auto const& that = this->as.ByteConstant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: \"{}\", ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 4 /* CharacterConstant */: {
builder.append("CheckedExpression::CharacterConstant"sv);
[[maybe_unused]] auto const& that = this->as.CharacterConstant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: \"{}\", ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 5 /* CCharacterConstant */: {
builder.append("CheckedExpression::CCharacterConstant"sv);
[[maybe_unused]] auto const& that = this->as.CCharacterConstant;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("val: \"{}\", ", that.val);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 6 /* UnaryOp */: {
builder.append("CheckedExpression::UnaryOp"sv);
[[maybe_unused]] auto const& that = this->as.UnaryOp;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("op: {}, ", that.op);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 7 /* BinaryOp */: {
builder.append("CheckedExpression::BinaryOp"sv);
[[maybe_unused]] auto const& that = this->as.BinaryOp;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("lhs: {}, ", that.lhs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("op: {}, ", that.op);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("rhs: {}, ", that.rhs);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 8 /* JaktTuple */: {
builder.append("CheckedExpression::JaktTuple"sv);
[[maybe_unused]] auto const& that = this->as.JaktTuple;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("vals: {}, ", that.vals);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 9 /* Range */: {
builder.append("CheckedExpression::Range"sv);
[[maybe_unused]] auto const& that = this->as.Range;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("from: {}, ", that.from);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("to: {}, ", that.to);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 10 /* JaktArray */: {
builder.append("CheckedExpression::JaktArray"sv);
[[maybe_unused]] auto const& that = this->as.JaktArray;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("vals: {}, ", that.vals);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("repeat: {}, ", that.repeat);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner_type_id: {}", that.inner_type_id);
}
builder.append(")"sv);
break;}
case 11 /* JaktSet */: {
builder.append("CheckedExpression::JaktSet"sv);
[[maybe_unused]] auto const& that = this->as.JaktSet;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("vals: {}, ", that.vals);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner_type_id: {}", that.inner_type_id);
}
builder.append(")"sv);
break;}
case 12 /* JaktDictionary */: {
builder.append("CheckedExpression::JaktDictionary"sv);
[[maybe_unused]] auto const& that = this->as.JaktDictionary;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("vals: {}, ", that.vals);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("key_type_id: {}, ", that.key_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("value_type_id: {}", that.value_type_id);
}
builder.append(")"sv);
break;}
case 13 /* IndexedExpression */: {
builder.append("CheckedExpression::IndexedExpression"sv);
[[maybe_unused]] auto const& that = this->as.IndexedExpression;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_implementation: {}, ", that.trait_implementation);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 14 /* IndexedDictionary */: {
builder.append("CheckedExpression::IndexedDictionary"sv);
[[maybe_unused]] auto const& that = this->as.IndexedDictionary;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_implementation: {}, ", that.trait_implementation);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 15 /* IndexedTuple */: {
builder.append("CheckedExpression::IndexedTuple"sv);
[[maybe_unused]] auto const& that = this->as.IndexedTuple;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 16 /* IndexedStruct */: {
builder.append("CheckedExpression::IndexedStruct"sv);
[[maybe_unused]] auto const& that = this->as.IndexedStruct;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", that.name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 17 /* IndexedCommonEnumMember */: {
builder.append("CheckedExpression::IndexedCommonEnumMember"sv);
[[maybe_unused]] auto const& that = this->as.IndexedCommonEnumMember;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: \"{}\", ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 18 /* ComptimeIndex */: {
builder.append("CheckedExpression::ComptimeIndex"sv);
[[maybe_unused]] auto const& that = this->as.ComptimeIndex;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("index: {}, ", that.index);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 19 /* Match */: {
builder.append("CheckedExpression::Match"sv);
[[maybe_unused]] auto const& that = this->as.Match;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("match_cases: {}, ", that.match_cases);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("all_variants_constant: {}", that.all_variants_constant);
}
builder.append(")"sv);
break;}
case 20 /* EnumVariantArg */: {
builder.append("CheckedExpression::EnumVariantArg"sv);
[[maybe_unused]] auto const& that = this->as.EnumVariantArg;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arg: {}, ", that.arg);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enum_variant: {}, ", that.enum_variant);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 21 /* Call */: {
builder.append("CheckedExpression::Call"sv);
[[maybe_unused]] auto const& that = this->as.Call;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("call: {}, ", that.call);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 22 /* MethodCall */: {
builder.append("CheckedExpression::MethodCall"sv);
[[maybe_unused]] auto const& that = this->as.MethodCall;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("call: {}, ", that.call);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("is_optional: {}, ", that.is_optional);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 23 /* NamespacedVar */: {
builder.append("CheckedExpression::NamespacedVar"sv);
[[maybe_unused]] auto const& that = this->as.NamespacedVar;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("namespaces: {}, ", that.namespaces);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var: {}, ", that.var);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 24 /* Var */: {
builder.append("CheckedExpression::Var"sv);
[[maybe_unused]] auto const& that = this->as.Var;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("var: {}, ", that.var);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", that.span);
}
builder.append(")"sv);
break;}
case 25 /* OptionalNone */: {
builder.append("CheckedExpression::OptionalNone"sv);
[[maybe_unused]] auto const& that = this->as.OptionalNone;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 26 /* OptionalSome */: {
builder.append("CheckedExpression::OptionalSome"sv);
[[maybe_unused]] auto const& that = this->as.OptionalSome;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 27 /* ForcedUnwrap */: {
builder.append("CheckedExpression::ForcedUnwrap"sv);
[[maybe_unused]] auto const& that = this->as.ForcedUnwrap;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 28 /* Block */: {
builder.append("CheckedExpression::Block"sv);
[[maybe_unused]] auto const& that = this->as.Block;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 29 /* Function */: {
builder.append("CheckedExpression::Function"sv);
[[maybe_unused]] auto const& that = this->as.Function;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("captures: {}, ", that.captures);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", that.params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", that.can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type_id: {}, ", that.return_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("pseudo_function_id: {}, ", that.pseudo_function_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}", that.scope_id);
}
builder.append(")"sv);
break;}
case 30 /* DependentFunction */: {
builder.append("CheckedExpression::DependentFunction"sv);
[[maybe_unused]] auto const& that = this->as.DependentFunction;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("captures: {}, ", that.captures);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", that.params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", that.can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type_id: {}, ", that.return_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("pseudo_function_id: {}, ", that.pseudo_function_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}", that.scope_id);
}
builder.append(")"sv);
break;}
case 31 /* Must */: {
builder.append("CheckedExpression::Must"sv);
[[maybe_unused]] auto const& that = this->as.Must;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 32 /* Try */: {
builder.append("CheckedExpression::Try"sv);
[[maybe_unused]] auto const& that = this->as.Try;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expr: {}, ", that.expr);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("catch_block: {}, ", that.catch_block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("catch_span: {}, ", that.catch_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("catch_name: {}, ", that.catch_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("inner_type_id: {}", that.inner_type_id);
}
builder.append(")"sv);
break;}
case 33 /* TryBlock */: {
builder.append("CheckedExpression::TryBlock"sv);
[[maybe_unused]] auto const& that = this->as.TryBlock;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("stmt: {}, ", that.stmt);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("catch_block: {}, ", that.catch_block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("error_name: \"{}\", ", that.error_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("error_span: {}, ", that.error_span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 34 /* Reflect */: {
builder.append("CheckedExpression::Reflect"sv);
[[maybe_unused]] auto const& that = this->as.Reflect;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type: {}, ", that.type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 35 /* Garbage */: {
builder.append("CheckedExpression::Garbage"sv);
[[maybe_unused]] auto const& that = this->as.Garbage;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_inferences: {}, ", this->common.init_common.generic_inferences);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}, ", that.span);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Boolean(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, bool val, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Boolean.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.Boolean.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::NumericConstant(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::types::CheckedNumericConstant val, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.NumericConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.NumericConstant.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.NumericConstant.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::QuotedString(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::types::CheckedStringLiteral val, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.QuotedString.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.QuotedString.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::ByteConstant(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, ByteString val, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.ByteConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.ByteConstant.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::CharacterConstant(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, ByteString val, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.CharacterConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.CharacterConstant.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::CCharacterConstant(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, ByteString val, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.CCharacterConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.CCharacterConstant.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::UnaryOp(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::types::CheckedUnaryOperator op, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.UnaryOp.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.UnaryOp.op) (decltype(op))(move(op));
new (&__jakt_uninit_enum->as.UnaryOp.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.UnaryOp.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::BinaryOp(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> lhs, Jakt::types::CheckedBinaryOperator op, NonnullRefPtr<typename Jakt::types::CheckedExpression> rhs, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.BinaryOp.lhs) (decltype(lhs))(move(lhs));
new (&__jakt_uninit_enum->as.BinaryOp.op) (decltype(op))(move(op));
new (&__jakt_uninit_enum->as.BinaryOp.rhs) (decltype(rhs))(move(rhs));
new (&__jakt_uninit_enum->as.BinaryOp.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.BinaryOp.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::JaktTuple(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.JaktTuple.vals) (decltype(vals))(move(vals));
new (&__jakt_uninit_enum->as.JaktTuple.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.JaktTuple.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Range(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> from, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> to, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Range.from) (decltype(from))(move(from));
new (&__jakt_uninit_enum->as.Range.to) (decltype(to))(move(to));
new (&__jakt_uninit_enum->as.Range.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Range.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::JaktArray(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals, JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> repeat, Jakt::utility::Span span, Jakt::ids::TypeId type_id, Jakt::ids::TypeId inner_type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.JaktArray.vals) (decltype(vals))(move(vals));
new (&__jakt_uninit_enum->as.JaktArray.repeat) (decltype(repeat))(move(repeat));
new (&__jakt_uninit_enum->as.JaktArray.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.JaktArray.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.JaktArray.inner_type_id) (decltype(inner_type_id))(move(inner_type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::JaktSet(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals, Jakt::utility::Span span, Jakt::ids::TypeId type_id, Jakt::ids::TypeId inner_type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.JaktSet.vals) (decltype(vals))(move(vals));
new (&__jakt_uninit_enum->as.JaktSet.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.JaktSet.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.JaktSet.inner_type_id) (decltype(inner_type_id))(move(inner_type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::JaktDictionary(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> vals, Jakt::utility::Span span, Jakt::ids::TypeId type_id, Jakt::ids::TypeId key_type_id, Jakt::ids::TypeId value_type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.JaktDictionary.vals) (decltype(vals))(move(vals));
new (&__jakt_uninit_enum->as.JaktDictionary.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.JaktDictionary.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.JaktDictionary.key_type_id) (decltype(key_type_id))(move(key_type_id));
new (&__jakt_uninit_enum->as.JaktDictionary.value_type_id) (decltype(value_type_id))(move(value_type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedExpression(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, NonnullRefPtr<typename Jakt::types::CheckedExpression> index, JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> trait_implementation, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.IndexedExpression.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedExpression.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedExpression.trait_implementation) (decltype(trait_implementation))(move(trait_implementation));
new (&__jakt_uninit_enum->as.IndexedExpression.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.IndexedExpression.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedDictionary(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, NonnullRefPtr<typename Jakt::types::CheckedExpression> index, JaktInternal::Optional<Jakt::types::OperatorTraitImplementation> trait_implementation, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.IndexedDictionary.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedDictionary.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedDictionary.trait_implementation) (decltype(trait_implementation))(move(trait_implementation));
new (&__jakt_uninit_enum->as.IndexedDictionary.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.IndexedDictionary.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedTuple(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, size_t index, Jakt::utility::Span span, bool is_optional, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 16;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.IndexedTuple.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedTuple.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedTuple.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.IndexedTuple.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.IndexedTuple.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedStruct(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, ByteString name, JaktInternal::Optional<Jakt::ids::VarId> index, Jakt::utility::Span span, bool is_optional, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 17;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.IndexedStruct.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedStruct.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.IndexedStruct.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedStruct.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.IndexedStruct.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.IndexedStruct.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedCommonEnumMember(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, ByteString index, Jakt::utility::Span span, bool is_optional, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 18;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.IndexedCommonEnumMember.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedCommonEnumMember.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedCommonEnumMember.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.IndexedCommonEnumMember.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.IndexedCommonEnumMember.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::ComptimeIndex(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, NonnullRefPtr<typename Jakt::types::CheckedExpression> index, bool is_optional, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 19;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.ComptimeIndex.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.ComptimeIndex.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.ComptimeIndex.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.ComptimeIndex.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Match(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> match_cases, Jakt::utility::Span span, Jakt::ids::TypeId type_id, bool all_variants_constant){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 20;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Match.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Match.match_cases) (decltype(match_cases))(move(match_cases));
new (&__jakt_uninit_enum->as.Match.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Match.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.Match.all_variants_constant) (decltype(all_variants_constant))(move(all_variants_constant));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::EnumVariantArg(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::types::CheckedEnumVariantBinding arg, Jakt::types::CheckedEnumVariant enum_variant, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 21;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.EnumVariantArg.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.EnumVariantArg.arg) (decltype(arg))(move(arg));
new (&__jakt_uninit_enum->as.EnumVariantArg.enum_variant) (decltype(enum_variant))(move(enum_variant));
new (&__jakt_uninit_enum->as.EnumVariantArg.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Call(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::types::CheckedCall call, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 22;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Call.call) (decltype(call))(move(call));
new (&__jakt_uninit_enum->as.Call.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Call.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::MethodCall(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::types::CheckedCall call, Jakt::utility::Span span, bool is_optional, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 23;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.MethodCall.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.MethodCall.call) (decltype(call))(move(call));
new (&__jakt_uninit_enum->as.MethodCall.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.MethodCall.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.MethodCall.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::NamespacedVar(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<Jakt::types::CheckedNamespace> namespaces, NonnullRefPtr<Jakt::types::CheckedVariable> var, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 24;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.NamespacedVar.namespaces) (decltype(namespaces))(move(namespaces));
new (&__jakt_uninit_enum->as.NamespacedVar.var) (decltype(var))(move(var));
new (&__jakt_uninit_enum->as.NamespacedVar.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Var(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<Jakt::types::CheckedVariable> var, Jakt::utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 25;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Var.var) (decltype(var))(move(var));
new (&__jakt_uninit_enum->as.Var.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::OptionalNone(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 26;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.OptionalNone.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.OptionalNone.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::OptionalSome(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 27;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.OptionalSome.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.OptionalSome.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.OptionalSome.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::ForcedUnwrap(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 28;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.ForcedUnwrap.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.ForcedUnwrap.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.ForcedUnwrap.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Block(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::types::CheckedBlock block, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 29;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Block.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Block.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Block.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Function(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<Jakt::types::CheckedCapture> captures, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params, bool can_throw, Jakt::ids::TypeId return_type_id, Jakt::types::CheckedBlock block, Jakt::utility::Span span, Jakt::ids::TypeId type_id, JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id, Jakt::ids::ScopeId scope_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 30;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Function.captures) (decltype(captures))(move(captures));
new (&__jakt_uninit_enum->as.Function.params) (decltype(params))(move(params));
new (&__jakt_uninit_enum->as.Function.can_throw) (decltype(can_throw))(move(can_throw));
new (&__jakt_uninit_enum->as.Function.return_type_id) (decltype(return_type_id))(move(return_type_id));
new (&__jakt_uninit_enum->as.Function.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Function.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Function.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.Function.pseudo_function_id) (decltype(pseudo_function_id))(move(pseudo_function_id));
new (&__jakt_uninit_enum->as.Function.scope_id) (decltype(scope_id))(move(scope_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::DependentFunction(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<Jakt::types::CheckedCapture> captures, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> params, bool can_throw, Jakt::ids::TypeId return_type_id, Jakt::parser::ParsedBlock block, Jakt::utility::Span span, Jakt::ids::TypeId type_id, JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id, Jakt::ids::ScopeId scope_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 31;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.DependentFunction.captures) (decltype(captures))(move(captures));
new (&__jakt_uninit_enum->as.DependentFunction.params) (decltype(params))(move(params));
new (&__jakt_uninit_enum->as.DependentFunction.can_throw) (decltype(can_throw))(move(can_throw));
new (&__jakt_uninit_enum->as.DependentFunction.return_type_id) (decltype(return_type_id))(move(return_type_id));
new (&__jakt_uninit_enum->as.DependentFunction.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.DependentFunction.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.DependentFunction.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.DependentFunction.pseudo_function_id) (decltype(pseudo_function_id))(move(pseudo_function_id));
new (&__jakt_uninit_enum->as.DependentFunction.scope_id) (decltype(scope_id))(move(scope_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Must(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 32;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Must.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Must.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Must.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Try(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedExpression> expr, JaktInternal::Optional<Jakt::types::CheckedBlock> catch_block, JaktInternal::Optional<Jakt::utility::Span> catch_span, JaktInternal::Optional<ByteString> catch_name, Jakt::utility::Span span, Jakt::ids::TypeId type_id, Jakt::ids::TypeId inner_type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 33;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Try.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Try.catch_block) (decltype(catch_block))(move(catch_block));
new (&__jakt_uninit_enum->as.Try.catch_span) (decltype(catch_span))(move(catch_span));
new (&__jakt_uninit_enum->as.Try.catch_name) (decltype(catch_name))(move(catch_name));
new (&__jakt_uninit_enum->as.Try.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Try.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.Try.inner_type_id) (decltype(inner_type_id))(move(inner_type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::TryBlock(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, NonnullRefPtr<typename Jakt::types::CheckedStatement> stmt, Jakt::types::CheckedBlock catch_block, ByteString error_name, Jakt::utility::Span error_span, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 34;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.TryBlock.stmt) (decltype(stmt))(move(stmt));
new (&__jakt_uninit_enum->as.TryBlock.catch_block) (decltype(catch_block))(move(catch_block));
new (&__jakt_uninit_enum->as.TryBlock.error_name) (decltype(error_name))(move(error_name));
new (&__jakt_uninit_enum->as.TryBlock.error_span) (decltype(error_span))(move(error_span));
new (&__jakt_uninit_enum->as.TryBlock.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.TryBlock.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Reflect(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::ids::TypeId type, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 35;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Reflect.type) (decltype(type))(move(type));
new (&__jakt_uninit_enum->as.Reflect.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Reflect.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Garbage(JaktInternal::Optional<JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>> generic_inferences, Jakt::utility::Span span, Jakt::ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 36;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Garbage.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Garbage.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
CheckedExpression& CheckedExpression::operator=(CheckedExpression const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.generic_inferences = rhs.common.init_common.generic_inferences;
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
new (&this->as.Boolean.val) (decltype(this->as.Boolean.val))(rhs.as.Boolean.val);
new (&this->as.Boolean.span) (decltype(this->as.Boolean.span))(rhs.as.Boolean.span);
break;
case 1 /* NumericConstant */:
new (&this->as.NumericConstant.val) (decltype(this->as.NumericConstant.val))(rhs.as.NumericConstant.val);
new (&this->as.NumericConstant.span) (decltype(this->as.NumericConstant.span))(rhs.as.NumericConstant.span);
new (&this->as.NumericConstant.type_id) (decltype(this->as.NumericConstant.type_id))(rhs.as.NumericConstant.type_id);
break;
case 2 /* QuotedString */:
new (&this->as.QuotedString.val) (decltype(this->as.QuotedString.val))(rhs.as.QuotedString.val);
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(rhs.as.QuotedString.span);
break;
case 3 /* ByteConstant */:
new (&this->as.ByteConstant.val) (decltype(this->as.ByteConstant.val))(rhs.as.ByteConstant.val);
new (&this->as.ByteConstant.span) (decltype(this->as.ByteConstant.span))(rhs.as.ByteConstant.span);
break;
case 4 /* CharacterConstant */:
new (&this->as.CharacterConstant.val) (decltype(this->as.CharacterConstant.val))(rhs.as.CharacterConstant.val);
new (&this->as.CharacterConstant.span) (decltype(this->as.CharacterConstant.span))(rhs.as.CharacterConstant.span);
break;
case 5 /* CCharacterConstant */:
new (&this->as.CCharacterConstant.val) (decltype(this->as.CCharacterConstant.val))(rhs.as.CCharacterConstant.val);
new (&this->as.CCharacterConstant.span) (decltype(this->as.CCharacterConstant.span))(rhs.as.CCharacterConstant.span);
break;
case 6 /* UnaryOp */:
new (&this->as.UnaryOp.expr) (decltype(this->as.UnaryOp.expr))(rhs.as.UnaryOp.expr);
new (&this->as.UnaryOp.op) (decltype(this->as.UnaryOp.op))(rhs.as.UnaryOp.op);
new (&this->as.UnaryOp.span) (decltype(this->as.UnaryOp.span))(rhs.as.UnaryOp.span);
new (&this->as.UnaryOp.type_id) (decltype(this->as.UnaryOp.type_id))(rhs.as.UnaryOp.type_id);
break;
case 7 /* BinaryOp */:
new (&this->as.BinaryOp.lhs) (decltype(this->as.BinaryOp.lhs))(rhs.as.BinaryOp.lhs);
new (&this->as.BinaryOp.op) (decltype(this->as.BinaryOp.op))(rhs.as.BinaryOp.op);
new (&this->as.BinaryOp.rhs) (decltype(this->as.BinaryOp.rhs))(rhs.as.BinaryOp.rhs);
new (&this->as.BinaryOp.span) (decltype(this->as.BinaryOp.span))(rhs.as.BinaryOp.span);
new (&this->as.BinaryOp.type_id) (decltype(this->as.BinaryOp.type_id))(rhs.as.BinaryOp.type_id);
break;
case 8 /* JaktTuple */:
new (&this->as.JaktTuple.vals) (decltype(this->as.JaktTuple.vals))(rhs.as.JaktTuple.vals);
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(rhs.as.JaktTuple.span);
new (&this->as.JaktTuple.type_id) (decltype(this->as.JaktTuple.type_id))(rhs.as.JaktTuple.type_id);
break;
case 9 /* Range */:
new (&this->as.Range.from) (decltype(this->as.Range.from))(rhs.as.Range.from);
new (&this->as.Range.to) (decltype(this->as.Range.to))(rhs.as.Range.to);
new (&this->as.Range.span) (decltype(this->as.Range.span))(rhs.as.Range.span);
new (&this->as.Range.type_id) (decltype(this->as.Range.type_id))(rhs.as.Range.type_id);
break;
case 10 /* JaktArray */:
new (&this->as.JaktArray.vals) (decltype(this->as.JaktArray.vals))(rhs.as.JaktArray.vals);
new (&this->as.JaktArray.repeat) (decltype(this->as.JaktArray.repeat))(rhs.as.JaktArray.repeat);
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(rhs.as.JaktArray.span);
new (&this->as.JaktArray.type_id) (decltype(this->as.JaktArray.type_id))(rhs.as.JaktArray.type_id);
new (&this->as.JaktArray.inner_type_id) (decltype(this->as.JaktArray.inner_type_id))(rhs.as.JaktArray.inner_type_id);
break;
case 11 /* JaktSet */:
new (&this->as.JaktSet.vals) (decltype(this->as.JaktSet.vals))(rhs.as.JaktSet.vals);
new (&this->as.JaktSet.span) (decltype(this->as.JaktSet.span))(rhs.as.JaktSet.span);
new (&this->as.JaktSet.type_id) (decltype(this->as.JaktSet.type_id))(rhs.as.JaktSet.type_id);
new (&this->as.JaktSet.inner_type_id) (decltype(this->as.JaktSet.inner_type_id))(rhs.as.JaktSet.inner_type_id);
break;
case 12 /* JaktDictionary */:
new (&this->as.JaktDictionary.vals) (decltype(this->as.JaktDictionary.vals))(rhs.as.JaktDictionary.vals);
new (&this->as.JaktDictionary.span) (decltype(this->as.JaktDictionary.span))(rhs.as.JaktDictionary.span);
new (&this->as.JaktDictionary.type_id) (decltype(this->as.JaktDictionary.type_id))(rhs.as.JaktDictionary.type_id);
new (&this->as.JaktDictionary.key_type_id) (decltype(this->as.JaktDictionary.key_type_id))(rhs.as.JaktDictionary.key_type_id);
new (&this->as.JaktDictionary.value_type_id) (decltype(this->as.JaktDictionary.value_type_id))(rhs.as.JaktDictionary.value_type_id);
break;
case 13 /* IndexedExpression */:
new (&this->as.IndexedExpression.expr) (decltype(this->as.IndexedExpression.expr))(rhs.as.IndexedExpression.expr);
new (&this->as.IndexedExpression.index) (decltype(this->as.IndexedExpression.index))(rhs.as.IndexedExpression.index);
new (&this->as.IndexedExpression.trait_implementation) (decltype(this->as.IndexedExpression.trait_implementation))(rhs.as.IndexedExpression.trait_implementation);
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(rhs.as.IndexedExpression.span);
new (&this->as.IndexedExpression.type_id) (decltype(this->as.IndexedExpression.type_id))(rhs.as.IndexedExpression.type_id);
break;
case 14 /* IndexedDictionary */:
new (&this->as.IndexedDictionary.expr) (decltype(this->as.IndexedDictionary.expr))(rhs.as.IndexedDictionary.expr);
new (&this->as.IndexedDictionary.index) (decltype(this->as.IndexedDictionary.index))(rhs.as.IndexedDictionary.index);
new (&this->as.IndexedDictionary.trait_implementation) (decltype(this->as.IndexedDictionary.trait_implementation))(rhs.as.IndexedDictionary.trait_implementation);
new (&this->as.IndexedDictionary.span) (decltype(this->as.IndexedDictionary.span))(rhs.as.IndexedDictionary.span);
new (&this->as.IndexedDictionary.type_id) (decltype(this->as.IndexedDictionary.type_id))(rhs.as.IndexedDictionary.type_id);
break;
case 15 /* IndexedTuple */:
new (&this->as.IndexedTuple.expr) (decltype(this->as.IndexedTuple.expr))(rhs.as.IndexedTuple.expr);
new (&this->as.IndexedTuple.index) (decltype(this->as.IndexedTuple.index))(rhs.as.IndexedTuple.index);
new (&this->as.IndexedTuple.span) (decltype(this->as.IndexedTuple.span))(rhs.as.IndexedTuple.span);
new (&this->as.IndexedTuple.is_optional) (decltype(this->as.IndexedTuple.is_optional))(rhs.as.IndexedTuple.is_optional);
new (&this->as.IndexedTuple.type_id) (decltype(this->as.IndexedTuple.type_id))(rhs.as.IndexedTuple.type_id);
break;
case 16 /* IndexedStruct */:
new (&this->as.IndexedStruct.expr) (decltype(this->as.IndexedStruct.expr))(rhs.as.IndexedStruct.expr);
new (&this->as.IndexedStruct.name) (decltype(this->as.IndexedStruct.name))(rhs.as.IndexedStruct.name);
new (&this->as.IndexedStruct.index) (decltype(this->as.IndexedStruct.index))(rhs.as.IndexedStruct.index);
new (&this->as.IndexedStruct.span) (decltype(this->as.IndexedStruct.span))(rhs.as.IndexedStruct.span);
new (&this->as.IndexedStruct.is_optional) (decltype(this->as.IndexedStruct.is_optional))(rhs.as.IndexedStruct.is_optional);
new (&this->as.IndexedStruct.type_id) (decltype(this->as.IndexedStruct.type_id))(rhs.as.IndexedStruct.type_id);
break;
case 17 /* IndexedCommonEnumMember */:
new (&this->as.IndexedCommonEnumMember.expr) (decltype(this->as.IndexedCommonEnumMember.expr))(rhs.as.IndexedCommonEnumMember.expr);
new (&this->as.IndexedCommonEnumMember.index) (decltype(this->as.IndexedCommonEnumMember.index))(rhs.as.IndexedCommonEnumMember.index);
new (&this->as.IndexedCommonEnumMember.span) (decltype(this->as.IndexedCommonEnumMember.span))(rhs.as.IndexedCommonEnumMember.span);
new (&this->as.IndexedCommonEnumMember.is_optional) (decltype(this->as.IndexedCommonEnumMember.is_optional))(rhs.as.IndexedCommonEnumMember.is_optional);
new (&this->as.IndexedCommonEnumMember.type_id) (decltype(this->as.IndexedCommonEnumMember.type_id))(rhs.as.IndexedCommonEnumMember.type_id);
break;
case 18 /* ComptimeIndex */:
new (&this->as.ComptimeIndex.expr) (decltype(this->as.ComptimeIndex.expr))(rhs.as.ComptimeIndex.expr);
new (&this->as.ComptimeIndex.index) (decltype(this->as.ComptimeIndex.index))(rhs.as.ComptimeIndex.index);
new (&this->as.ComptimeIndex.is_optional) (decltype(this->as.ComptimeIndex.is_optional))(rhs.as.ComptimeIndex.is_optional);
new (&this->as.ComptimeIndex.span) (decltype(this->as.ComptimeIndex.span))(rhs.as.ComptimeIndex.span);
break;
case 19 /* Match */:
new (&this->as.Match.expr) (decltype(this->as.Match.expr))(rhs.as.Match.expr);
new (&this->as.Match.match_cases) (decltype(this->as.Match.match_cases))(rhs.as.Match.match_cases);
new (&this->as.Match.span) (decltype(this->as.Match.span))(rhs.as.Match.span);
new (&this->as.Match.type_id) (decltype(this->as.Match.type_id))(rhs.as.Match.type_id);
new (&this->as.Match.all_variants_constant) (decltype(this->as.Match.all_variants_constant))(rhs.as.Match.all_variants_constant);
break;
case 20 /* EnumVariantArg */:
new (&this->as.EnumVariantArg.expr) (decltype(this->as.EnumVariantArg.expr))(rhs.as.EnumVariantArg.expr);
new (&this->as.EnumVariantArg.arg) (decltype(this->as.EnumVariantArg.arg))(rhs.as.EnumVariantArg.arg);
new (&this->as.EnumVariantArg.enum_variant) (decltype(this->as.EnumVariantArg.enum_variant))(rhs.as.EnumVariantArg.enum_variant);
new (&this->as.EnumVariantArg.span) (decltype(this->as.EnumVariantArg.span))(rhs.as.EnumVariantArg.span);
break;
case 21 /* Call */:
new (&this->as.Call.call) (decltype(this->as.Call.call))(rhs.as.Call.call);
new (&this->as.Call.span) (decltype(this->as.Call.span))(rhs.as.Call.span);
new (&this->as.Call.type_id) (decltype(this->as.Call.type_id))(rhs.as.Call.type_id);
break;
case 22 /* MethodCall */:
new (&this->as.MethodCall.expr) (decltype(this->as.MethodCall.expr))(rhs.as.MethodCall.expr);
new (&this->as.MethodCall.call) (decltype(this->as.MethodCall.call))(rhs.as.MethodCall.call);
new (&this->as.MethodCall.span) (decltype(this->as.MethodCall.span))(rhs.as.MethodCall.span);
new (&this->as.MethodCall.is_optional) (decltype(this->as.MethodCall.is_optional))(rhs.as.MethodCall.is_optional);
new (&this->as.MethodCall.type_id) (decltype(this->as.MethodCall.type_id))(rhs.as.MethodCall.type_id);
break;
case 23 /* NamespacedVar */:
new (&this->as.NamespacedVar.namespaces) (decltype(this->as.NamespacedVar.namespaces))(rhs.as.NamespacedVar.namespaces);
new (&this->as.NamespacedVar.var) (decltype(this->as.NamespacedVar.var))(rhs.as.NamespacedVar.var);
new (&this->as.NamespacedVar.span) (decltype(this->as.NamespacedVar.span))(rhs.as.NamespacedVar.span);
break;
case 24 /* Var */:
new (&this->as.Var.var) (decltype(this->as.Var.var))(rhs.as.Var.var);
new (&this->as.Var.span) (decltype(this->as.Var.span))(rhs.as.Var.span);
break;
case 25 /* OptionalNone */:
new (&this->as.OptionalNone.span) (decltype(this->as.OptionalNone.span))(rhs.as.OptionalNone.span);
new (&this->as.OptionalNone.type_id) (decltype(this->as.OptionalNone.type_id))(rhs.as.OptionalNone.type_id);
break;
case 26 /* OptionalSome */:
new (&this->as.OptionalSome.expr) (decltype(this->as.OptionalSome.expr))(rhs.as.OptionalSome.expr);
new (&this->as.OptionalSome.span) (decltype(this->as.OptionalSome.span))(rhs.as.OptionalSome.span);
new (&this->as.OptionalSome.type_id) (decltype(this->as.OptionalSome.type_id))(rhs.as.OptionalSome.type_id);
break;
case 27 /* ForcedUnwrap */:
new (&this->as.ForcedUnwrap.expr) (decltype(this->as.ForcedUnwrap.expr))(rhs.as.ForcedUnwrap.expr);
new (&this->as.ForcedUnwrap.span) (decltype(this->as.ForcedUnwrap.span))(rhs.as.ForcedUnwrap.span);
new (&this->as.ForcedUnwrap.type_id) (decltype(this->as.ForcedUnwrap.type_id))(rhs.as.ForcedUnwrap.type_id);
break;
case 28 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(rhs.as.Block.block);
new (&this->as.Block.span) (decltype(this->as.Block.span))(rhs.as.Block.span);
new (&this->as.Block.type_id) (decltype(this->as.Block.type_id))(rhs.as.Block.type_id);
break;
case 29 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(rhs.as.Function.captures);
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(rhs.as.Function.return_type_id);
new (&this->as.Function.block) (decltype(this->as.Function.block))(rhs.as.Function.block);
new (&this->as.Function.span) (decltype(this->as.Function.span))(rhs.as.Function.span);
new (&this->as.Function.type_id) (decltype(this->as.Function.type_id))(rhs.as.Function.type_id);
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(rhs.as.Function.pseudo_function_id);
new (&this->as.Function.scope_id) (decltype(this->as.Function.scope_id))(rhs.as.Function.scope_id);
break;
case 30 /* DependentFunction */:
new (&this->as.DependentFunction.captures) (decltype(this->as.DependentFunction.captures))(rhs.as.DependentFunction.captures);
new (&this->as.DependentFunction.params) (decltype(this->as.DependentFunction.params))(rhs.as.DependentFunction.params);
new (&this->as.DependentFunction.can_throw) (decltype(this->as.DependentFunction.can_throw))(rhs.as.DependentFunction.can_throw);
new (&this->as.DependentFunction.return_type_id) (decltype(this->as.DependentFunction.return_type_id))(rhs.as.DependentFunction.return_type_id);
new (&this->as.DependentFunction.block) (decltype(this->as.DependentFunction.block))(rhs.as.DependentFunction.block);
new (&this->as.DependentFunction.span) (decltype(this->as.DependentFunction.span))(rhs.as.DependentFunction.span);
new (&this->as.DependentFunction.type_id) (decltype(this->as.DependentFunction.type_id))(rhs.as.DependentFunction.type_id);
new (&this->as.DependentFunction.pseudo_function_id) (decltype(this->as.DependentFunction.pseudo_function_id))(rhs.as.DependentFunction.pseudo_function_id);
new (&this->as.DependentFunction.scope_id) (decltype(this->as.DependentFunction.scope_id))(rhs.as.DependentFunction.scope_id);
break;
case 31 /* Must */:
new (&this->as.Must.expr) (decltype(this->as.Must.expr))(rhs.as.Must.expr);
new (&this->as.Must.span) (decltype(this->as.Must.span))(rhs.as.Must.span);
new (&this->as.Must.type_id) (decltype(this->as.Must.type_id))(rhs.as.Must.type_id);
break;
case 32 /* Try */:
new (&this->as.Try.expr) (decltype(this->as.Try.expr))(rhs.as.Try.expr);
new (&this->as.Try.catch_block) (decltype(this->as.Try.catch_block))(rhs.as.Try.catch_block);
new (&this->as.Try.catch_span) (decltype(this->as.Try.catch_span))(rhs.as.Try.catch_span);
new (&this->as.Try.catch_name) (decltype(this->as.Try.catch_name))(rhs.as.Try.catch_name);
new (&this->as.Try.span) (decltype(this->as.Try.span))(rhs.as.Try.span);
new (&this->as.Try.type_id) (decltype(this->as.Try.type_id))(rhs.as.Try.type_id);
new (&this->as.Try.inner_type_id) (decltype(this->as.Try.inner_type_id))(rhs.as.Try.inner_type_id);
break;
case 33 /* TryBlock */:
new (&this->as.TryBlock.stmt) (decltype(this->as.TryBlock.stmt))(rhs.as.TryBlock.stmt);
new (&this->as.TryBlock.catch_block) (decltype(this->as.TryBlock.catch_block))(rhs.as.TryBlock.catch_block);
new (&this->as.TryBlock.error_name) (decltype(this->as.TryBlock.error_name))(rhs.as.TryBlock.error_name);
new (&this->as.TryBlock.error_span) (decltype(this->as.TryBlock.error_span))(rhs.as.TryBlock.error_span);
new (&this->as.TryBlock.span) (decltype(this->as.TryBlock.span))(rhs.as.TryBlock.span);
new (&this->as.TryBlock.type_id) (decltype(this->as.TryBlock.type_id))(rhs.as.TryBlock.type_id);
break;
case 34 /* Reflect */:
new (&this->as.Reflect.type) (decltype(this->as.Reflect.type))(rhs.as.Reflect.type);
new (&this->as.Reflect.span) (decltype(this->as.Reflect.span))(rhs.as.Reflect.span);
new (&this->as.Reflect.type_id) (decltype(this->as.Reflect.type_id))(rhs.as.Reflect.type_id);
break;
case 35 /* Garbage */:
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(rhs.as.Garbage.span);
new (&this->as.Garbage.type_id) (decltype(this->as.Garbage.type_id))(rhs.as.Garbage.type_id);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
this->as.Boolean.val = rhs.as.Boolean.val;
this->as.Boolean.span = rhs.as.Boolean.span;
break;
case 1 /* NumericConstant */:
this->as.NumericConstant.val = rhs.as.NumericConstant.val;
this->as.NumericConstant.span = rhs.as.NumericConstant.span;
this->as.NumericConstant.type_id = rhs.as.NumericConstant.type_id;
break;
case 2 /* QuotedString */:
this->as.QuotedString.val = rhs.as.QuotedString.val;
this->as.QuotedString.span = rhs.as.QuotedString.span;
break;
case 3 /* ByteConstant */:
this->as.ByteConstant.val = rhs.as.ByteConstant.val;
this->as.ByteConstant.span = rhs.as.ByteConstant.span;
break;
case 4 /* CharacterConstant */:
this->as.CharacterConstant.val = rhs.as.CharacterConstant.val;
this->as.CharacterConstant.span = rhs.as.CharacterConstant.span;
break;
case 5 /* CCharacterConstant */:
this->as.CCharacterConstant.val = rhs.as.CCharacterConstant.val;
this->as.CCharacterConstant.span = rhs.as.CCharacterConstant.span;
break;
case 6 /* UnaryOp */:
this->as.UnaryOp.expr = rhs.as.UnaryOp.expr;
this->as.UnaryOp.op = rhs.as.UnaryOp.op;
this->as.UnaryOp.span = rhs.as.UnaryOp.span;
this->as.UnaryOp.type_id = rhs.as.UnaryOp.type_id;
break;
case 7 /* BinaryOp */:
this->as.BinaryOp.lhs = rhs.as.BinaryOp.lhs;
this->as.BinaryOp.op = rhs.as.BinaryOp.op;
this->as.BinaryOp.rhs = rhs.as.BinaryOp.rhs;
this->as.BinaryOp.span = rhs.as.BinaryOp.span;
this->as.BinaryOp.type_id = rhs.as.BinaryOp.type_id;
break;
case 8 /* JaktTuple */:
this->as.JaktTuple.vals = rhs.as.JaktTuple.vals;
this->as.JaktTuple.span = rhs.as.JaktTuple.span;
this->as.JaktTuple.type_id = rhs.as.JaktTuple.type_id;
break;
case 9 /* Range */:
this->as.Range.from = rhs.as.Range.from;
this->as.Range.to = rhs.as.Range.to;
this->as.Range.span = rhs.as.Range.span;
this->as.Range.type_id = rhs.as.Range.type_id;
break;
case 10 /* JaktArray */:
this->as.JaktArray.vals = rhs.as.JaktArray.vals;
this->as.JaktArray.repeat = rhs.as.JaktArray.repeat;
this->as.JaktArray.span = rhs.as.JaktArray.span;
this->as.JaktArray.type_id = rhs.as.JaktArray.type_id;
this->as.JaktArray.inner_type_id = rhs.as.JaktArray.inner_type_id;
break;
case 11 /* JaktSet */:
this->as.JaktSet.vals = rhs.as.JaktSet.vals;
this->as.JaktSet.span = rhs.as.JaktSet.span;
this->as.JaktSet.type_id = rhs.as.JaktSet.type_id;
this->as.JaktSet.inner_type_id = rhs.as.JaktSet.inner_type_id;
break;
case 12 /* JaktDictionary */:
this->as.JaktDictionary.vals = rhs.as.JaktDictionary.vals;
this->as.JaktDictionary.span = rhs.as.JaktDictionary.span;
this->as.JaktDictionary.type_id = rhs.as.JaktDictionary.type_id;
this->as.JaktDictionary.key_type_id = rhs.as.JaktDictionary.key_type_id;
this->as.JaktDictionary.value_type_id = rhs.as.JaktDictionary.value_type_id;
break;
case 13 /* IndexedExpression */:
this->as.IndexedExpression.expr = rhs.as.IndexedExpression.expr;
this->as.IndexedExpression.index = rhs.as.IndexedExpression.index;
this->as.IndexedExpression.trait_implementation = rhs.as.IndexedExpression.trait_implementation;
this->as.IndexedExpression.span = rhs.as.IndexedExpression.span;
this->as.IndexedExpression.type_id = rhs.as.IndexedExpression.type_id;
break;
case 14 /* IndexedDictionary */:
this->as.IndexedDictionary.expr = rhs.as.IndexedDictionary.expr;
this->as.IndexedDictionary.index = rhs.as.IndexedDictionary.index;
this->as.IndexedDictionary.trait_implementation = rhs.as.IndexedDictionary.trait_implementation;
this->as.IndexedDictionary.span = rhs.as.IndexedDictionary.span;
this->as.IndexedDictionary.type_id = rhs.as.IndexedDictionary.type_id;
break;
case 15 /* IndexedTuple */:
this->as.IndexedTuple.expr = rhs.as.IndexedTuple.expr;
this->as.IndexedTuple.index = rhs.as.IndexedTuple.index;
this->as.IndexedTuple.span = rhs.as.IndexedTuple.span;
this->as.IndexedTuple.is_optional = rhs.as.IndexedTuple.is_optional;
this->as.IndexedTuple.type_id = rhs.as.IndexedTuple.type_id;
break;
case 16 /* IndexedStruct */:
this->as.IndexedStruct.expr = rhs.as.IndexedStruct.expr;
this->as.IndexedStruct.name = rhs.as.IndexedStruct.name;
this->as.IndexedStruct.index = rhs.as.IndexedStruct.index;
this->as.IndexedStruct.span = rhs.as.IndexedStruct.span;
this->as.IndexedStruct.is_optional = rhs.as.IndexedStruct.is_optional;
this->as.IndexedStruct.type_id = rhs.as.IndexedStruct.type_id;
break;
case 17 /* IndexedCommonEnumMember */:
this->as.IndexedCommonEnumMember.expr = rhs.as.IndexedCommonEnumMember.expr;
this->as.IndexedCommonEnumMember.index = rhs.as.IndexedCommonEnumMember.index;
this->as.IndexedCommonEnumMember.span = rhs.as.IndexedCommonEnumMember.span;
this->as.IndexedCommonEnumMember.is_optional = rhs.as.IndexedCommonEnumMember.is_optional;
this->as.IndexedCommonEnumMember.type_id = rhs.as.IndexedCommonEnumMember.type_id;
break;
case 18 /* ComptimeIndex */:
this->as.ComptimeIndex.expr = rhs.as.ComptimeIndex.expr;
this->as.ComptimeIndex.index = rhs.as.ComptimeIndex.index;
this->as.ComptimeIndex.is_optional = rhs.as.ComptimeIndex.is_optional;
this->as.ComptimeIndex.span = rhs.as.ComptimeIndex.span;
break;
case 19 /* Match */:
this->as.Match.expr = rhs.as.Match.expr;
this->as.Match.match_cases = rhs.as.Match.match_cases;
this->as.Match.span = rhs.as.Match.span;
this->as.Match.type_id = rhs.as.Match.type_id;
this->as.Match.all_variants_constant = rhs.as.Match.all_variants_constant;
break;
case 20 /* EnumVariantArg */:
this->as.EnumVariantArg.expr = rhs.as.EnumVariantArg.expr;
this->as.EnumVariantArg.arg = rhs.as.EnumVariantArg.arg;
this->as.EnumVariantArg.enum_variant = rhs.as.EnumVariantArg.enum_variant;
this->as.EnumVariantArg.span = rhs.as.EnumVariantArg.span;
break;
case 21 /* Call */:
this->as.Call.call = rhs.as.Call.call;
this->as.Call.span = rhs.as.Call.span;
this->as.Call.type_id = rhs.as.Call.type_id;
break;
case 22 /* MethodCall */:
this->as.MethodCall.expr = rhs.as.MethodCall.expr;
this->as.MethodCall.call = rhs.as.MethodCall.call;
this->as.MethodCall.span = rhs.as.MethodCall.span;
this->as.MethodCall.is_optional = rhs.as.MethodCall.is_optional;
this->as.MethodCall.type_id = rhs.as.MethodCall.type_id;
break;
case 23 /* NamespacedVar */:
this->as.NamespacedVar.namespaces = rhs.as.NamespacedVar.namespaces;
this->as.NamespacedVar.var = rhs.as.NamespacedVar.var;
this->as.NamespacedVar.span = rhs.as.NamespacedVar.span;
break;
case 24 /* Var */:
this->as.Var.var = rhs.as.Var.var;
this->as.Var.span = rhs.as.Var.span;
break;
case 25 /* OptionalNone */:
this->as.OptionalNone.span = rhs.as.OptionalNone.span;
this->as.OptionalNone.type_id = rhs.as.OptionalNone.type_id;
break;
case 26 /* OptionalSome */:
this->as.OptionalSome.expr = rhs.as.OptionalSome.expr;
this->as.OptionalSome.span = rhs.as.OptionalSome.span;
this->as.OptionalSome.type_id = rhs.as.OptionalSome.type_id;
break;
case 27 /* ForcedUnwrap */:
this->as.ForcedUnwrap.expr = rhs.as.ForcedUnwrap.expr;
this->as.ForcedUnwrap.span = rhs.as.ForcedUnwrap.span;
this->as.ForcedUnwrap.type_id = rhs.as.ForcedUnwrap.type_id;
break;
case 28 /* Block */:
this->as.Block.block = rhs.as.Block.block;
this->as.Block.span = rhs.as.Block.span;
this->as.Block.type_id = rhs.as.Block.type_id;
break;
case 29 /* Function */:
this->as.Function.captures = rhs.as.Function.captures;
this->as.Function.params = rhs.as.Function.params;
this->as.Function.can_throw = rhs.as.Function.can_throw;
this->as.Function.return_type_id = rhs.as.Function.return_type_id;
this->as.Function.block = rhs.as.Function.block;
this->as.Function.span = rhs.as.Function.span;
this->as.Function.type_id = rhs.as.Function.type_id;
this->as.Function.pseudo_function_id = rhs.as.Function.pseudo_function_id;
this->as.Function.scope_id = rhs.as.Function.scope_id;
break;
case 30 /* DependentFunction */:
this->as.DependentFunction.captures = rhs.as.DependentFunction.captures;
this->as.DependentFunction.params = rhs.as.DependentFunction.params;
this->as.DependentFunction.can_throw = rhs.as.DependentFunction.can_throw;
this->as.DependentFunction.return_type_id = rhs.as.DependentFunction.return_type_id;
this->as.DependentFunction.block = rhs.as.DependentFunction.block;
this->as.DependentFunction.span = rhs.as.DependentFunction.span;
this->as.DependentFunction.type_id = rhs.as.DependentFunction.type_id;
this->as.DependentFunction.pseudo_function_id = rhs.as.DependentFunction.pseudo_function_id;
this->as.DependentFunction.scope_id = rhs.as.DependentFunction.scope_id;
break;
case 31 /* Must */:
this->as.Must.expr = rhs.as.Must.expr;
this->as.Must.span = rhs.as.Must.span;
this->as.Must.type_id = rhs.as.Must.type_id;
break;
case 32 /* Try */:
this->as.Try.expr = rhs.as.Try.expr;
this->as.Try.catch_block = rhs.as.Try.catch_block;
this->as.Try.catch_span = rhs.as.Try.catch_span;
this->as.Try.catch_name = rhs.as.Try.catch_name;
this->as.Try.span = rhs.as.Try.span;
this->as.Try.type_id = rhs.as.Try.type_id;
this->as.Try.inner_type_id = rhs.as.Try.inner_type_id;
break;
case 33 /* TryBlock */:
this->as.TryBlock.stmt = rhs.as.TryBlock.stmt;
this->as.TryBlock.catch_block = rhs.as.TryBlock.catch_block;
this->as.TryBlock.error_name = rhs.as.TryBlock.error_name;
this->as.TryBlock.error_span = rhs.as.TryBlock.error_span;
this->as.TryBlock.span = rhs.as.TryBlock.span;
this->as.TryBlock.type_id = rhs.as.TryBlock.type_id;
break;
case 34 /* Reflect */:
this->as.Reflect.type = rhs.as.Reflect.type;
this->as.Reflect.span = rhs.as.Reflect.span;
this->as.Reflect.type_id = rhs.as.Reflect.type_id;
break;
case 35 /* Garbage */:
this->as.Garbage.span = rhs.as.Garbage.span;
this->as.Garbage.type_id = rhs.as.Garbage.type_id;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedExpression::CheckedExpression(CheckedExpression const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.generic_inferences) (decltype(this->common.init_common.generic_inferences))(rhs.common.init_common.generic_inferences);
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
new (&this->as.Boolean.val) (decltype(this->as.Boolean.val))(rhs.as.Boolean.val);
new (&this->as.Boolean.span) (decltype(this->as.Boolean.span))(rhs.as.Boolean.span);
break;
case 1 /* NumericConstant */:
new (&this->as.NumericConstant.val) (decltype(this->as.NumericConstant.val))(rhs.as.NumericConstant.val);
new (&this->as.NumericConstant.span) (decltype(this->as.NumericConstant.span))(rhs.as.NumericConstant.span);
new (&this->as.NumericConstant.type_id) (decltype(this->as.NumericConstant.type_id))(rhs.as.NumericConstant.type_id);
break;
case 2 /* QuotedString */:
new (&this->as.QuotedString.val) (decltype(this->as.QuotedString.val))(rhs.as.QuotedString.val);
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(rhs.as.QuotedString.span);
break;
case 3 /* ByteConstant */:
new (&this->as.ByteConstant.val) (decltype(this->as.ByteConstant.val))(rhs.as.ByteConstant.val);
new (&this->as.ByteConstant.span) (decltype(this->as.ByteConstant.span))(rhs.as.ByteConstant.span);
break;
case 4 /* CharacterConstant */:
new (&this->as.CharacterConstant.val) (decltype(this->as.CharacterConstant.val))(rhs.as.CharacterConstant.val);
new (&this->as.CharacterConstant.span) (decltype(this->as.CharacterConstant.span))(rhs.as.CharacterConstant.span);
break;
case 5 /* CCharacterConstant */:
new (&this->as.CCharacterConstant.val) (decltype(this->as.CCharacterConstant.val))(rhs.as.CCharacterConstant.val);
new (&this->as.CCharacterConstant.span) (decltype(this->as.CCharacterConstant.span))(rhs.as.CCharacterConstant.span);
break;
case 6 /* UnaryOp */:
new (&this->as.UnaryOp.expr) (decltype(this->as.UnaryOp.expr))(rhs.as.UnaryOp.expr);
new (&this->as.UnaryOp.op) (decltype(this->as.UnaryOp.op))(rhs.as.UnaryOp.op);
new (&this->as.UnaryOp.span) (decltype(this->as.UnaryOp.span))(rhs.as.UnaryOp.span);
new (&this->as.UnaryOp.type_id) (decltype(this->as.UnaryOp.type_id))(rhs.as.UnaryOp.type_id);
break;
case 7 /* BinaryOp */:
new (&this->as.BinaryOp.lhs) (decltype(this->as.BinaryOp.lhs))(rhs.as.BinaryOp.lhs);
new (&this->as.BinaryOp.op) (decltype(this->as.BinaryOp.op))(rhs.as.BinaryOp.op);
new (&this->as.BinaryOp.rhs) (decltype(this->as.BinaryOp.rhs))(rhs.as.BinaryOp.rhs);
new (&this->as.BinaryOp.span) (decltype(this->as.BinaryOp.span))(rhs.as.BinaryOp.span);
new (&this->as.BinaryOp.type_id) (decltype(this->as.BinaryOp.type_id))(rhs.as.BinaryOp.type_id);
break;
case 8 /* JaktTuple */:
new (&this->as.JaktTuple.vals) (decltype(this->as.JaktTuple.vals))(rhs.as.JaktTuple.vals);
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(rhs.as.JaktTuple.span);
new (&this->as.JaktTuple.type_id) (decltype(this->as.JaktTuple.type_id))(rhs.as.JaktTuple.type_id);
break;
case 9 /* Range */:
new (&this->as.Range.from) (decltype(this->as.Range.from))(rhs.as.Range.from);
new (&this->as.Range.to) (decltype(this->as.Range.to))(rhs.as.Range.to);
new (&this->as.Range.span) (decltype(this->as.Range.span))(rhs.as.Range.span);
new (&this->as.Range.type_id) (decltype(this->as.Range.type_id))(rhs.as.Range.type_id);
break;
case 10 /* JaktArray */:
new (&this->as.JaktArray.vals) (decltype(this->as.JaktArray.vals))(rhs.as.JaktArray.vals);
new (&this->as.JaktArray.repeat) (decltype(this->as.JaktArray.repeat))(rhs.as.JaktArray.repeat);
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(rhs.as.JaktArray.span);
new (&this->as.JaktArray.type_id) (decltype(this->as.JaktArray.type_id))(rhs.as.JaktArray.type_id);
new (&this->as.JaktArray.inner_type_id) (decltype(this->as.JaktArray.inner_type_id))(rhs.as.JaktArray.inner_type_id);
break;
case 11 /* JaktSet */:
new (&this->as.JaktSet.vals) (decltype(this->as.JaktSet.vals))(rhs.as.JaktSet.vals);
new (&this->as.JaktSet.span) (decltype(this->as.JaktSet.span))(rhs.as.JaktSet.span);
new (&this->as.JaktSet.type_id) (decltype(this->as.JaktSet.type_id))(rhs.as.JaktSet.type_id);
new (&this->as.JaktSet.inner_type_id) (decltype(this->as.JaktSet.inner_type_id))(rhs.as.JaktSet.inner_type_id);
break;
case 12 /* JaktDictionary */:
new (&this->as.JaktDictionary.vals) (decltype(this->as.JaktDictionary.vals))(rhs.as.JaktDictionary.vals);
new (&this->as.JaktDictionary.span) (decltype(this->as.JaktDictionary.span))(rhs.as.JaktDictionary.span);
new (&this->as.JaktDictionary.type_id) (decltype(this->as.JaktDictionary.type_id))(rhs.as.JaktDictionary.type_id);
new (&this->as.JaktDictionary.key_type_id) (decltype(this->as.JaktDictionary.key_type_id))(rhs.as.JaktDictionary.key_type_id);
new (&this->as.JaktDictionary.value_type_id) (decltype(this->as.JaktDictionary.value_type_id))(rhs.as.JaktDictionary.value_type_id);
break;
case 13 /* IndexedExpression */:
new (&this->as.IndexedExpression.expr) (decltype(this->as.IndexedExpression.expr))(rhs.as.IndexedExpression.expr);
new (&this->as.IndexedExpression.index) (decltype(this->as.IndexedExpression.index))(rhs.as.IndexedExpression.index);
new (&this->as.IndexedExpression.trait_implementation) (decltype(this->as.IndexedExpression.trait_implementation))(rhs.as.IndexedExpression.trait_implementation);
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(rhs.as.IndexedExpression.span);
new (&this->as.IndexedExpression.type_id) (decltype(this->as.IndexedExpression.type_id))(rhs.as.IndexedExpression.type_id);
break;
case 14 /* IndexedDictionary */:
new (&this->as.IndexedDictionary.expr) (decltype(this->as.IndexedDictionary.expr))(rhs.as.IndexedDictionary.expr);
new (&this->as.IndexedDictionary.index) (decltype(this->as.IndexedDictionary.index))(rhs.as.IndexedDictionary.index);
new (&this->as.IndexedDictionary.trait_implementation) (decltype(this->as.IndexedDictionary.trait_implementation))(rhs.as.IndexedDictionary.trait_implementation);
new (&this->as.IndexedDictionary.span) (decltype(this->as.IndexedDictionary.span))(rhs.as.IndexedDictionary.span);
new (&this->as.IndexedDictionary.type_id) (decltype(this->as.IndexedDictionary.type_id))(rhs.as.IndexedDictionary.type_id);
break;
case 15 /* IndexedTuple */:
new (&this->as.IndexedTuple.expr) (decltype(this->as.IndexedTuple.expr))(rhs.as.IndexedTuple.expr);
new (&this->as.IndexedTuple.index) (decltype(this->as.IndexedTuple.index))(rhs.as.IndexedTuple.index);
new (&this->as.IndexedTuple.span) (decltype(this->as.IndexedTuple.span))(rhs.as.IndexedTuple.span);
new (&this->as.IndexedTuple.is_optional) (decltype(this->as.IndexedTuple.is_optional))(rhs.as.IndexedTuple.is_optional);
new (&this->as.IndexedTuple.type_id) (decltype(this->as.IndexedTuple.type_id))(rhs.as.IndexedTuple.type_id);
break;
case 16 /* IndexedStruct */:
new (&this->as.IndexedStruct.expr) (decltype(this->as.IndexedStruct.expr))(rhs.as.IndexedStruct.expr);
new (&this->as.IndexedStruct.name) (decltype(this->as.IndexedStruct.name))(rhs.as.IndexedStruct.name);
new (&this->as.IndexedStruct.index) (decltype(this->as.IndexedStruct.index))(rhs.as.IndexedStruct.index);
new (&this->as.IndexedStruct.span) (decltype(this->as.IndexedStruct.span))(rhs.as.IndexedStruct.span);
new (&this->as.IndexedStruct.is_optional) (decltype(this->as.IndexedStruct.is_optional))(rhs.as.IndexedStruct.is_optional);
new (&this->as.IndexedStruct.type_id) (decltype(this->as.IndexedStruct.type_id))(rhs.as.IndexedStruct.type_id);
break;
case 17 /* IndexedCommonEnumMember */:
new (&this->as.IndexedCommonEnumMember.expr) (decltype(this->as.IndexedCommonEnumMember.expr))(rhs.as.IndexedCommonEnumMember.expr);
new (&this->as.IndexedCommonEnumMember.index) (decltype(this->as.IndexedCommonEnumMember.index))(rhs.as.IndexedCommonEnumMember.index);
new (&this->as.IndexedCommonEnumMember.span) (decltype(this->as.IndexedCommonEnumMember.span))(rhs.as.IndexedCommonEnumMember.span);
new (&this->as.IndexedCommonEnumMember.is_optional) (decltype(this->as.IndexedCommonEnumMember.is_optional))(rhs.as.IndexedCommonEnumMember.is_optional);
new (&this->as.IndexedCommonEnumMember.type_id) (decltype(this->as.IndexedCommonEnumMember.type_id))(rhs.as.IndexedCommonEnumMember.type_id);
break;
case 18 /* ComptimeIndex */:
new (&this->as.ComptimeIndex.expr) (decltype(this->as.ComptimeIndex.expr))(rhs.as.ComptimeIndex.expr);
new (&this->as.ComptimeIndex.index) (decltype(this->as.ComptimeIndex.index))(rhs.as.ComptimeIndex.index);
new (&this->as.ComptimeIndex.is_optional) (decltype(this->as.ComptimeIndex.is_optional))(rhs.as.ComptimeIndex.is_optional);
new (&this->as.ComptimeIndex.span) (decltype(this->as.ComptimeIndex.span))(rhs.as.ComptimeIndex.span);
break;
case 19 /* Match */:
new (&this->as.Match.expr) (decltype(this->as.Match.expr))(rhs.as.Match.expr);
new (&this->as.Match.match_cases) (decltype(this->as.Match.match_cases))(rhs.as.Match.match_cases);
new (&this->as.Match.span) (decltype(this->as.Match.span))(rhs.as.Match.span);
new (&this->as.Match.type_id) (decltype(this->as.Match.type_id))(rhs.as.Match.type_id);
new (&this->as.Match.all_variants_constant) (decltype(this->as.Match.all_variants_constant))(rhs.as.Match.all_variants_constant);
break;
case 20 /* EnumVariantArg */:
new (&this->as.EnumVariantArg.expr) (decltype(this->as.EnumVariantArg.expr))(rhs.as.EnumVariantArg.expr);
new (&this->as.EnumVariantArg.arg) (decltype(this->as.EnumVariantArg.arg))(rhs.as.EnumVariantArg.arg);
new (&this->as.EnumVariantArg.enum_variant) (decltype(this->as.EnumVariantArg.enum_variant))(rhs.as.EnumVariantArg.enum_variant);
new (&this->as.EnumVariantArg.span) (decltype(this->as.EnumVariantArg.span))(rhs.as.EnumVariantArg.span);
break;
case 21 /* Call */:
new (&this->as.Call.call) (decltype(this->as.Call.call))(rhs.as.Call.call);
new (&this->as.Call.span) (decltype(this->as.Call.span))(rhs.as.Call.span);
new (&this->as.Call.type_id) (decltype(this->as.Call.type_id))(rhs.as.Call.type_id);
break;
case 22 /* MethodCall */:
new (&this->as.MethodCall.expr) (decltype(this->as.MethodCall.expr))(rhs.as.MethodCall.expr);
new (&this->as.MethodCall.call) (decltype(this->as.MethodCall.call))(rhs.as.MethodCall.call);
new (&this->as.MethodCall.span) (decltype(this->as.MethodCall.span))(rhs.as.MethodCall.span);
new (&this->as.MethodCall.is_optional) (decltype(this->as.MethodCall.is_optional))(rhs.as.MethodCall.is_optional);
new (&this->as.MethodCall.type_id) (decltype(this->as.MethodCall.type_id))(rhs.as.MethodCall.type_id);
break;
case 23 /* NamespacedVar */:
new (&this->as.NamespacedVar.namespaces) (decltype(this->as.NamespacedVar.namespaces))(rhs.as.NamespacedVar.namespaces);
new (&this->as.NamespacedVar.var) (decltype(this->as.NamespacedVar.var))(rhs.as.NamespacedVar.var);
new (&this->as.NamespacedVar.span) (decltype(this->as.NamespacedVar.span))(rhs.as.NamespacedVar.span);
break;
case 24 /* Var */:
new (&this->as.Var.var) (decltype(this->as.Var.var))(rhs.as.Var.var);
new (&this->as.Var.span) (decltype(this->as.Var.span))(rhs.as.Var.span);
break;
case 25 /* OptionalNone */:
new (&this->as.OptionalNone.span) (decltype(this->as.OptionalNone.span))(rhs.as.OptionalNone.span);
new (&this->as.OptionalNone.type_id) (decltype(this->as.OptionalNone.type_id))(rhs.as.OptionalNone.type_id);
break;
case 26 /* OptionalSome */:
new (&this->as.OptionalSome.expr) (decltype(this->as.OptionalSome.expr))(rhs.as.OptionalSome.expr);
new (&this->as.OptionalSome.span) (decltype(this->as.OptionalSome.span))(rhs.as.OptionalSome.span);
new (&this->as.OptionalSome.type_id) (decltype(this->as.OptionalSome.type_id))(rhs.as.OptionalSome.type_id);
break;
case 27 /* ForcedUnwrap */:
new (&this->as.ForcedUnwrap.expr) (decltype(this->as.ForcedUnwrap.expr))(rhs.as.ForcedUnwrap.expr);
new (&this->as.ForcedUnwrap.span) (decltype(this->as.ForcedUnwrap.span))(rhs.as.ForcedUnwrap.span);
new (&this->as.ForcedUnwrap.type_id) (decltype(this->as.ForcedUnwrap.type_id))(rhs.as.ForcedUnwrap.type_id);
break;
case 28 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(rhs.as.Block.block);
new (&this->as.Block.span) (decltype(this->as.Block.span))(rhs.as.Block.span);
new (&this->as.Block.type_id) (decltype(this->as.Block.type_id))(rhs.as.Block.type_id);
break;
case 29 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(rhs.as.Function.captures);
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(rhs.as.Function.return_type_id);
new (&this->as.Function.block) (decltype(this->as.Function.block))(rhs.as.Function.block);
new (&this->as.Function.span) (decltype(this->as.Function.span))(rhs.as.Function.span);
new (&this->as.Function.type_id) (decltype(this->as.Function.type_id))(rhs.as.Function.type_id);
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(rhs.as.Function.pseudo_function_id);
new (&this->as.Function.scope_id) (decltype(this->as.Function.scope_id))(rhs.as.Function.scope_id);
break;
case 30 /* DependentFunction */:
new (&this->as.DependentFunction.captures) (decltype(this->as.DependentFunction.captures))(rhs.as.DependentFunction.captures);
new (&this->as.DependentFunction.params) (decltype(this->as.DependentFunction.params))(rhs.as.DependentFunction.params);
new (&this->as.DependentFunction.can_throw) (decltype(this->as.DependentFunction.can_throw))(rhs.as.DependentFunction.can_throw);
new (&this->as.DependentFunction.return_type_id) (decltype(this->as.DependentFunction.return_type_id))(rhs.as.DependentFunction.return_type_id);
new (&this->as.DependentFunction.block) (decltype(this->as.DependentFunction.block))(rhs.as.DependentFunction.block);
new (&this->as.DependentFunction.span) (decltype(this->as.DependentFunction.span))(rhs.as.DependentFunction.span);
new (&this->as.DependentFunction.type_id) (decltype(this->as.DependentFunction.type_id))(rhs.as.DependentFunction.type_id);
new (&this->as.DependentFunction.pseudo_function_id) (decltype(this->as.DependentFunction.pseudo_function_id))(rhs.as.DependentFunction.pseudo_function_id);
new (&this->as.DependentFunction.scope_id) (decltype(this->as.DependentFunction.scope_id))(rhs.as.DependentFunction.scope_id);
break;
case 31 /* Must */:
new (&this->as.Must.expr) (decltype(this->as.Must.expr))(rhs.as.Must.expr);
new (&this->as.Must.span) (decltype(this->as.Must.span))(rhs.as.Must.span);
new (&this->as.Must.type_id) (decltype(this->as.Must.type_id))(rhs.as.Must.type_id);
break;
case 32 /* Try */:
new (&this->as.Try.expr) (decltype(this->as.Try.expr))(rhs.as.Try.expr);
new (&this->as.Try.catch_block) (decltype(this->as.Try.catch_block))(rhs.as.Try.catch_block);
new (&this->as.Try.catch_span) (decltype(this->as.Try.catch_span))(rhs.as.Try.catch_span);
new (&this->as.Try.catch_name) (decltype(this->as.Try.catch_name))(rhs.as.Try.catch_name);
new (&this->as.Try.span) (decltype(this->as.Try.span))(rhs.as.Try.span);
new (&this->as.Try.type_id) (decltype(this->as.Try.type_id))(rhs.as.Try.type_id);
new (&this->as.Try.inner_type_id) (decltype(this->as.Try.inner_type_id))(rhs.as.Try.inner_type_id);
break;
case 33 /* TryBlock */:
new (&this->as.TryBlock.stmt) (decltype(this->as.TryBlock.stmt))(rhs.as.TryBlock.stmt);
new (&this->as.TryBlock.catch_block) (decltype(this->as.TryBlock.catch_block))(rhs.as.TryBlock.catch_block);
new (&this->as.TryBlock.error_name) (decltype(this->as.TryBlock.error_name))(rhs.as.TryBlock.error_name);
new (&this->as.TryBlock.error_span) (decltype(this->as.TryBlock.error_span))(rhs.as.TryBlock.error_span);
new (&this->as.TryBlock.span) (decltype(this->as.TryBlock.span))(rhs.as.TryBlock.span);
new (&this->as.TryBlock.type_id) (decltype(this->as.TryBlock.type_id))(rhs.as.TryBlock.type_id);
break;
case 34 /* Reflect */:
new (&this->as.Reflect.type) (decltype(this->as.Reflect.type))(rhs.as.Reflect.type);
new (&this->as.Reflect.span) (decltype(this->as.Reflect.span))(rhs.as.Reflect.span);
new (&this->as.Reflect.type_id) (decltype(this->as.Reflect.type_id))(rhs.as.Reflect.type_id);
break;
case 35 /* Garbage */:
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(rhs.as.Garbage.span);
new (&this->as.Garbage.type_id) (decltype(this->as.Garbage.type_id))(rhs.as.Garbage.type_id);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedExpression& CheckedExpression::operator=(CheckedExpression &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
this->common.init_common.generic_inferences = move(rhs.common.init_common.generic_inferences);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
new (&this->as.Boolean.val) (decltype(this->as.Boolean.val))(move(rhs.as.Boolean.val));
new (&this->as.Boolean.span) (decltype(this->as.Boolean.span))(move(rhs.as.Boolean.span));
break;
case 1 /* NumericConstant */:
new (&this->as.NumericConstant.val) (decltype(this->as.NumericConstant.val))(move(rhs.as.NumericConstant.val));
new (&this->as.NumericConstant.span) (decltype(this->as.NumericConstant.span))(move(rhs.as.NumericConstant.span));
new (&this->as.NumericConstant.type_id) (decltype(this->as.NumericConstant.type_id))(move(rhs.as.NumericConstant.type_id));
break;
case 2 /* QuotedString */:
new (&this->as.QuotedString.val) (decltype(this->as.QuotedString.val))(move(rhs.as.QuotedString.val));
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(move(rhs.as.QuotedString.span));
break;
case 3 /* ByteConstant */:
new (&this->as.ByteConstant.val) (decltype(this->as.ByteConstant.val))(move(rhs.as.ByteConstant.val));
new (&this->as.ByteConstant.span) (decltype(this->as.ByteConstant.span))(move(rhs.as.ByteConstant.span));
break;
case 4 /* CharacterConstant */:
new (&this->as.CharacterConstant.val) (decltype(this->as.CharacterConstant.val))(move(rhs.as.CharacterConstant.val));
new (&this->as.CharacterConstant.span) (decltype(this->as.CharacterConstant.span))(move(rhs.as.CharacterConstant.span));
break;
case 5 /* CCharacterConstant */:
new (&this->as.CCharacterConstant.val) (decltype(this->as.CCharacterConstant.val))(move(rhs.as.CCharacterConstant.val));
new (&this->as.CCharacterConstant.span) (decltype(this->as.CCharacterConstant.span))(move(rhs.as.CCharacterConstant.span));
break;
case 6 /* UnaryOp */:
new (&this->as.UnaryOp.expr) (decltype(this->as.UnaryOp.expr))(move(rhs.as.UnaryOp.expr));
new (&this->as.UnaryOp.op) (decltype(this->as.UnaryOp.op))(move(rhs.as.UnaryOp.op));
new (&this->as.UnaryOp.span) (decltype(this->as.UnaryOp.span))(move(rhs.as.UnaryOp.span));
new (&this->as.UnaryOp.type_id) (decltype(this->as.UnaryOp.type_id))(move(rhs.as.UnaryOp.type_id));
break;
case 7 /* BinaryOp */:
new (&this->as.BinaryOp.lhs) (decltype(this->as.BinaryOp.lhs))(move(rhs.as.BinaryOp.lhs));
new (&this->as.BinaryOp.op) (decltype(this->as.BinaryOp.op))(move(rhs.as.BinaryOp.op));
new (&this->as.BinaryOp.rhs) (decltype(this->as.BinaryOp.rhs))(move(rhs.as.BinaryOp.rhs));
new (&this->as.BinaryOp.span) (decltype(this->as.BinaryOp.span))(move(rhs.as.BinaryOp.span));
new (&this->as.BinaryOp.type_id) (decltype(this->as.BinaryOp.type_id))(move(rhs.as.BinaryOp.type_id));
break;
case 8 /* JaktTuple */:
new (&this->as.JaktTuple.vals) (decltype(this->as.JaktTuple.vals))(move(rhs.as.JaktTuple.vals));
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(move(rhs.as.JaktTuple.span));
new (&this->as.JaktTuple.type_id) (decltype(this->as.JaktTuple.type_id))(move(rhs.as.JaktTuple.type_id));
break;
case 9 /* Range */:
new (&this->as.Range.from) (decltype(this->as.Range.from))(move(rhs.as.Range.from));
new (&this->as.Range.to) (decltype(this->as.Range.to))(move(rhs.as.Range.to));
new (&this->as.Range.span) (decltype(this->as.Range.span))(move(rhs.as.Range.span));
new (&this->as.Range.type_id) (decltype(this->as.Range.type_id))(move(rhs.as.Range.type_id));
break;
case 10 /* JaktArray */:
new (&this->as.JaktArray.vals) (decltype(this->as.JaktArray.vals))(move(rhs.as.JaktArray.vals));
new (&this->as.JaktArray.repeat) (decltype(this->as.JaktArray.repeat))(move(rhs.as.JaktArray.repeat));
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(move(rhs.as.JaktArray.span));
new (&this->as.JaktArray.type_id) (decltype(this->as.JaktArray.type_id))(move(rhs.as.JaktArray.type_id));
new (&this->as.JaktArray.inner_type_id) (decltype(this->as.JaktArray.inner_type_id))(move(rhs.as.JaktArray.inner_type_id));
break;
case 11 /* JaktSet */:
new (&this->as.JaktSet.vals) (decltype(this->as.JaktSet.vals))(move(rhs.as.JaktSet.vals));
new (&this->as.JaktSet.span) (decltype(this->as.JaktSet.span))(move(rhs.as.JaktSet.span));
new (&this->as.JaktSet.type_id) (decltype(this->as.JaktSet.type_id))(move(rhs.as.JaktSet.type_id));
new (&this->as.JaktSet.inner_type_id) (decltype(this->as.JaktSet.inner_type_id))(move(rhs.as.JaktSet.inner_type_id));
break;
case 12 /* JaktDictionary */:
new (&this->as.JaktDictionary.vals) (decltype(this->as.JaktDictionary.vals))(move(rhs.as.JaktDictionary.vals));
new (&this->as.JaktDictionary.span) (decltype(this->as.JaktDictionary.span))(move(rhs.as.JaktDictionary.span));
new (&this->as.JaktDictionary.type_id) (decltype(this->as.JaktDictionary.type_id))(move(rhs.as.JaktDictionary.type_id));
new (&this->as.JaktDictionary.key_type_id) (decltype(this->as.JaktDictionary.key_type_id))(move(rhs.as.JaktDictionary.key_type_id));
new (&this->as.JaktDictionary.value_type_id) (decltype(this->as.JaktDictionary.value_type_id))(move(rhs.as.JaktDictionary.value_type_id));
break;
case 13 /* IndexedExpression */:
new (&this->as.IndexedExpression.expr) (decltype(this->as.IndexedExpression.expr))(move(rhs.as.IndexedExpression.expr));
new (&this->as.IndexedExpression.index) (decltype(this->as.IndexedExpression.index))(move(rhs.as.IndexedExpression.index));
new (&this->as.IndexedExpression.trait_implementation) (decltype(this->as.IndexedExpression.trait_implementation))(move(rhs.as.IndexedExpression.trait_implementation));
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(move(rhs.as.IndexedExpression.span));
new (&this->as.IndexedExpression.type_id) (decltype(this->as.IndexedExpression.type_id))(move(rhs.as.IndexedExpression.type_id));
break;
case 14 /* IndexedDictionary */:
new (&this->as.IndexedDictionary.expr) (decltype(this->as.IndexedDictionary.expr))(move(rhs.as.IndexedDictionary.expr));
new (&this->as.IndexedDictionary.index) (decltype(this->as.IndexedDictionary.index))(move(rhs.as.IndexedDictionary.index));
new (&this->as.IndexedDictionary.trait_implementation) (decltype(this->as.IndexedDictionary.trait_implementation))(move(rhs.as.IndexedDictionary.trait_implementation));
new (&this->as.IndexedDictionary.span) (decltype(this->as.IndexedDictionary.span))(move(rhs.as.IndexedDictionary.span));
new (&this->as.IndexedDictionary.type_id) (decltype(this->as.IndexedDictionary.type_id))(move(rhs.as.IndexedDictionary.type_id));
break;
case 15 /* IndexedTuple */:
new (&this->as.IndexedTuple.expr) (decltype(this->as.IndexedTuple.expr))(move(rhs.as.IndexedTuple.expr));
new (&this->as.IndexedTuple.index) (decltype(this->as.IndexedTuple.index))(move(rhs.as.IndexedTuple.index));
new (&this->as.IndexedTuple.span) (decltype(this->as.IndexedTuple.span))(move(rhs.as.IndexedTuple.span));
new (&this->as.IndexedTuple.is_optional) (decltype(this->as.IndexedTuple.is_optional))(move(rhs.as.IndexedTuple.is_optional));
new (&this->as.IndexedTuple.type_id) (decltype(this->as.IndexedTuple.type_id))(move(rhs.as.IndexedTuple.type_id));
break;
case 16 /* IndexedStruct */:
new (&this->as.IndexedStruct.expr) (decltype(this->as.IndexedStruct.expr))(move(rhs.as.IndexedStruct.expr));
new (&this->as.IndexedStruct.name) (decltype(this->as.IndexedStruct.name))(move(rhs.as.IndexedStruct.name));
new (&this->as.IndexedStruct.index) (decltype(this->as.IndexedStruct.index))(move(rhs.as.IndexedStruct.index));
new (&this->as.IndexedStruct.span) (decltype(this->as.IndexedStruct.span))(move(rhs.as.IndexedStruct.span));
new (&this->as.IndexedStruct.is_optional) (decltype(this->as.IndexedStruct.is_optional))(move(rhs.as.IndexedStruct.is_optional));
new (&this->as.IndexedStruct.type_id) (decltype(this->as.IndexedStruct.type_id))(move(rhs.as.IndexedStruct.type_id));
break;
case 17 /* IndexedCommonEnumMember */:
new (&this->as.IndexedCommonEnumMember.expr) (decltype(this->as.IndexedCommonEnumMember.expr))(move(rhs.as.IndexedCommonEnumMember.expr));
new (&this->as.IndexedCommonEnumMember.index) (decltype(this->as.IndexedCommonEnumMember.index))(move(rhs.as.IndexedCommonEnumMember.index));
new (&this->as.IndexedCommonEnumMember.span) (decltype(this->as.IndexedCommonEnumMember.span))(move(rhs.as.IndexedCommonEnumMember.span));
new (&this->as.IndexedCommonEnumMember.is_optional) (decltype(this->as.IndexedCommonEnumMember.is_optional))(move(rhs.as.IndexedCommonEnumMember.is_optional));
new (&this->as.IndexedCommonEnumMember.type_id) (decltype(this->as.IndexedCommonEnumMember.type_id))(move(rhs.as.IndexedCommonEnumMember.type_id));
break;
case 18 /* ComptimeIndex */:
new (&this->as.ComptimeIndex.expr) (decltype(this->as.ComptimeIndex.expr))(move(rhs.as.ComptimeIndex.expr));
new (&this->as.ComptimeIndex.index) (decltype(this->as.ComptimeIndex.index))(move(rhs.as.ComptimeIndex.index));
new (&this->as.ComptimeIndex.is_optional) (decltype(this->as.ComptimeIndex.is_optional))(move(rhs.as.ComptimeIndex.is_optional));
new (&this->as.ComptimeIndex.span) (decltype(this->as.ComptimeIndex.span))(move(rhs.as.ComptimeIndex.span));
break;
case 19 /* Match */:
new (&this->as.Match.expr) (decltype(this->as.Match.expr))(move(rhs.as.Match.expr));
new (&this->as.Match.match_cases) (decltype(this->as.Match.match_cases))(move(rhs.as.Match.match_cases));
new (&this->as.Match.span) (decltype(this->as.Match.span))(move(rhs.as.Match.span));
new (&this->as.Match.type_id) (decltype(this->as.Match.type_id))(move(rhs.as.Match.type_id));
new (&this->as.Match.all_variants_constant) (decltype(this->as.Match.all_variants_constant))(move(rhs.as.Match.all_variants_constant));
break;
case 20 /* EnumVariantArg */:
new (&this->as.EnumVariantArg.expr) (decltype(this->as.EnumVariantArg.expr))(move(rhs.as.EnumVariantArg.expr));
new (&this->as.EnumVariantArg.arg) (decltype(this->as.EnumVariantArg.arg))(move(rhs.as.EnumVariantArg.arg));
new (&this->as.EnumVariantArg.enum_variant) (decltype(this->as.EnumVariantArg.enum_variant))(move(rhs.as.EnumVariantArg.enum_variant));
new (&this->as.EnumVariantArg.span) (decltype(this->as.EnumVariantArg.span))(move(rhs.as.EnumVariantArg.span));
break;
case 21 /* Call */:
new (&this->as.Call.call) (decltype(this->as.Call.call))(move(rhs.as.Call.call));
new (&this->as.Call.span) (decltype(this->as.Call.span))(move(rhs.as.Call.span));
new (&this->as.Call.type_id) (decltype(this->as.Call.type_id))(move(rhs.as.Call.type_id));
break;
case 22 /* MethodCall */:
new (&this->as.MethodCall.expr) (decltype(this->as.MethodCall.expr))(move(rhs.as.MethodCall.expr));
new (&this->as.MethodCall.call) (decltype(this->as.MethodCall.call))(move(rhs.as.MethodCall.call));
new (&this->as.MethodCall.span) (decltype(this->as.MethodCall.span))(move(rhs.as.MethodCall.span));
new (&this->as.MethodCall.is_optional) (decltype(this->as.MethodCall.is_optional))(move(rhs.as.MethodCall.is_optional));
new (&this->as.MethodCall.type_id) (decltype(this->as.MethodCall.type_id))(move(rhs.as.MethodCall.type_id));
break;
case 23 /* NamespacedVar */:
new (&this->as.NamespacedVar.namespaces) (decltype(this->as.NamespacedVar.namespaces))(move(rhs.as.NamespacedVar.namespaces));
new (&this->as.NamespacedVar.var) (decltype(this->as.NamespacedVar.var))(move(rhs.as.NamespacedVar.var));
new (&this->as.NamespacedVar.span) (decltype(this->as.NamespacedVar.span))(move(rhs.as.NamespacedVar.span));
break;
case 24 /* Var */:
new (&this->as.Var.var) (decltype(this->as.Var.var))(move(rhs.as.Var.var));
new (&this->as.Var.span) (decltype(this->as.Var.span))(move(rhs.as.Var.span));
break;
case 25 /* OptionalNone */:
new (&this->as.OptionalNone.span) (decltype(this->as.OptionalNone.span))(move(rhs.as.OptionalNone.span));
new (&this->as.OptionalNone.type_id) (decltype(this->as.OptionalNone.type_id))(move(rhs.as.OptionalNone.type_id));
break;
case 26 /* OptionalSome */:
new (&this->as.OptionalSome.expr) (decltype(this->as.OptionalSome.expr))(move(rhs.as.OptionalSome.expr));
new (&this->as.OptionalSome.span) (decltype(this->as.OptionalSome.span))(move(rhs.as.OptionalSome.span));
new (&this->as.OptionalSome.type_id) (decltype(this->as.OptionalSome.type_id))(move(rhs.as.OptionalSome.type_id));
break;
case 27 /* ForcedUnwrap */:
new (&this->as.ForcedUnwrap.expr) (decltype(this->as.ForcedUnwrap.expr))(move(rhs.as.ForcedUnwrap.expr));
new (&this->as.ForcedUnwrap.span) (decltype(this->as.ForcedUnwrap.span))(move(rhs.as.ForcedUnwrap.span));
new (&this->as.ForcedUnwrap.type_id) (decltype(this->as.ForcedUnwrap.type_id))(move(rhs.as.ForcedUnwrap.type_id));
break;
case 28 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(move(rhs.as.Block.block));
new (&this->as.Block.span) (decltype(this->as.Block.span))(move(rhs.as.Block.span));
new (&this->as.Block.type_id) (decltype(this->as.Block.type_id))(move(rhs.as.Block.type_id));
break;
case 29 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(move(rhs.as.Function.captures));
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(move(rhs.as.Function.return_type_id));
new (&this->as.Function.block) (decltype(this->as.Function.block))(move(rhs.as.Function.block));
new (&this->as.Function.span) (decltype(this->as.Function.span))(move(rhs.as.Function.span));
new (&this->as.Function.type_id) (decltype(this->as.Function.type_id))(move(rhs.as.Function.type_id));
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(move(rhs.as.Function.pseudo_function_id));
new (&this->as.Function.scope_id) (decltype(this->as.Function.scope_id))(move(rhs.as.Function.scope_id));
break;
case 30 /* DependentFunction */:
new (&this->as.DependentFunction.captures) (decltype(this->as.DependentFunction.captures))(move(rhs.as.DependentFunction.captures));
new (&this->as.DependentFunction.params) (decltype(this->as.DependentFunction.params))(move(rhs.as.DependentFunction.params));
new (&this->as.DependentFunction.can_throw) (decltype(this->as.DependentFunction.can_throw))(move(rhs.as.DependentFunction.can_throw));
new (&this->as.DependentFunction.return_type_id) (decltype(this->as.DependentFunction.return_type_id))(move(rhs.as.DependentFunction.return_type_id));
new (&this->as.DependentFunction.block) (decltype(this->as.DependentFunction.block))(move(rhs.as.DependentFunction.block));
new (&this->as.DependentFunction.span) (decltype(this->as.DependentFunction.span))(move(rhs.as.DependentFunction.span));
new (&this->as.DependentFunction.type_id) (decltype(this->as.DependentFunction.type_id))(move(rhs.as.DependentFunction.type_id));
new (&this->as.DependentFunction.pseudo_function_id) (decltype(this->as.DependentFunction.pseudo_function_id))(move(rhs.as.DependentFunction.pseudo_function_id));
new (&this->as.DependentFunction.scope_id) (decltype(this->as.DependentFunction.scope_id))(move(rhs.as.DependentFunction.scope_id));
break;
case 31 /* Must */:
new (&this->as.Must.expr) (decltype(this->as.Must.expr))(move(rhs.as.Must.expr));
new (&this->as.Must.span) (decltype(this->as.Must.span))(move(rhs.as.Must.span));
new (&this->as.Must.type_id) (decltype(this->as.Must.type_id))(move(rhs.as.Must.type_id));
break;
case 32 /* Try */:
new (&this->as.Try.expr) (decltype(this->as.Try.expr))(move(rhs.as.Try.expr));
new (&this->as.Try.catch_block) (decltype(this->as.Try.catch_block))(move(rhs.as.Try.catch_block));
new (&this->as.Try.catch_span) (decltype(this->as.Try.catch_span))(move(rhs.as.Try.catch_span));
new (&this->as.Try.catch_name) (decltype(this->as.Try.catch_name))(move(rhs.as.Try.catch_name));
new (&this->as.Try.span) (decltype(this->as.Try.span))(move(rhs.as.Try.span));
new (&this->as.Try.type_id) (decltype(this->as.Try.type_id))(move(rhs.as.Try.type_id));
new (&this->as.Try.inner_type_id) (decltype(this->as.Try.inner_type_id))(move(rhs.as.Try.inner_type_id));
break;
case 33 /* TryBlock */:
new (&this->as.TryBlock.stmt) (decltype(this->as.TryBlock.stmt))(move(rhs.as.TryBlock.stmt));
new (&this->as.TryBlock.catch_block) (decltype(this->as.TryBlock.catch_block))(move(rhs.as.TryBlock.catch_block));
new (&this->as.TryBlock.error_name) (decltype(this->as.TryBlock.error_name))(move(rhs.as.TryBlock.error_name));
new (&this->as.TryBlock.error_span) (decltype(this->as.TryBlock.error_span))(move(rhs.as.TryBlock.error_span));
new (&this->as.TryBlock.span) (decltype(this->as.TryBlock.span))(move(rhs.as.TryBlock.span));
new (&this->as.TryBlock.type_id) (decltype(this->as.TryBlock.type_id))(move(rhs.as.TryBlock.type_id));
break;
case 34 /* Reflect */:
new (&this->as.Reflect.type) (decltype(this->as.Reflect.type))(move(rhs.as.Reflect.type));
new (&this->as.Reflect.span) (decltype(this->as.Reflect.span))(move(rhs.as.Reflect.span));
new (&this->as.Reflect.type_id) (decltype(this->as.Reflect.type_id))(move(rhs.as.Reflect.type_id));
break;
case 35 /* Garbage */:
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(move(rhs.as.Garbage.span));
new (&this->as.Garbage.type_id) (decltype(this->as.Garbage.type_id))(move(rhs.as.Garbage.type_id));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
this->as.Boolean.val = move(rhs.as.Boolean.val);
this->as.Boolean.span = move(rhs.as.Boolean.span);
break;
case 1 /* NumericConstant */:
this->as.NumericConstant.val = move(rhs.as.NumericConstant.val);
this->as.NumericConstant.span = move(rhs.as.NumericConstant.span);
this->as.NumericConstant.type_id = move(rhs.as.NumericConstant.type_id);
break;
case 2 /* QuotedString */:
this->as.QuotedString.val = move(rhs.as.QuotedString.val);
this->as.QuotedString.span = move(rhs.as.QuotedString.span);
break;
case 3 /* ByteConstant */:
this->as.ByteConstant.val = move(rhs.as.ByteConstant.val);
this->as.ByteConstant.span = move(rhs.as.ByteConstant.span);
break;
case 4 /* CharacterConstant */:
this->as.CharacterConstant.val = move(rhs.as.CharacterConstant.val);
this->as.CharacterConstant.span = move(rhs.as.CharacterConstant.span);
break;
case 5 /* CCharacterConstant */:
this->as.CCharacterConstant.val = move(rhs.as.CCharacterConstant.val);
this->as.CCharacterConstant.span = move(rhs.as.CCharacterConstant.span);
break;
case 6 /* UnaryOp */:
this->as.UnaryOp.expr = move(rhs.as.UnaryOp.expr);
this->as.UnaryOp.op = move(rhs.as.UnaryOp.op);
this->as.UnaryOp.span = move(rhs.as.UnaryOp.span);
this->as.UnaryOp.type_id = move(rhs.as.UnaryOp.type_id);
break;
case 7 /* BinaryOp */:
this->as.BinaryOp.lhs = move(rhs.as.BinaryOp.lhs);
this->as.BinaryOp.op = move(rhs.as.BinaryOp.op);
this->as.BinaryOp.rhs = move(rhs.as.BinaryOp.rhs);
this->as.BinaryOp.span = move(rhs.as.BinaryOp.span);
this->as.BinaryOp.type_id = move(rhs.as.BinaryOp.type_id);
break;
case 8 /* JaktTuple */:
this->as.JaktTuple.vals = move(rhs.as.JaktTuple.vals);
this->as.JaktTuple.span = move(rhs.as.JaktTuple.span);
this->as.JaktTuple.type_id = move(rhs.as.JaktTuple.type_id);
break;
case 9 /* Range */:
this->as.Range.from = move(rhs.as.Range.from);
this->as.Range.to = move(rhs.as.Range.to);
this->as.Range.span = move(rhs.as.Range.span);
this->as.Range.type_id = move(rhs.as.Range.type_id);
break;
case 10 /* JaktArray */:
this->as.JaktArray.vals = move(rhs.as.JaktArray.vals);
this->as.JaktArray.repeat = move(rhs.as.JaktArray.repeat);
this->as.JaktArray.span = move(rhs.as.JaktArray.span);
this->as.JaktArray.type_id = move(rhs.as.JaktArray.type_id);
this->as.JaktArray.inner_type_id = move(rhs.as.JaktArray.inner_type_id);
break;
case 11 /* JaktSet */:
this->as.JaktSet.vals = move(rhs.as.JaktSet.vals);
this->as.JaktSet.span = move(rhs.as.JaktSet.span);
this->as.JaktSet.type_id = move(rhs.as.JaktSet.type_id);
this->as.JaktSet.inner_type_id = move(rhs.as.JaktSet.inner_type_id);
break;
case 12 /* JaktDictionary */:
this->as.JaktDictionary.vals = move(rhs.as.JaktDictionary.vals);
this->as.JaktDictionary.span = move(rhs.as.JaktDictionary.span);
this->as.JaktDictionary.type_id = move(rhs.as.JaktDictionary.type_id);
this->as.JaktDictionary.key_type_id = move(rhs.as.JaktDictionary.key_type_id);
this->as.JaktDictionary.value_type_id = move(rhs.as.JaktDictionary.value_type_id);
break;
case 13 /* IndexedExpression */:
this->as.IndexedExpression.expr = move(rhs.as.IndexedExpression.expr);
this->as.IndexedExpression.index = move(rhs.as.IndexedExpression.index);
this->as.IndexedExpression.trait_implementation = move(rhs.as.IndexedExpression.trait_implementation);
this->as.IndexedExpression.span = move(rhs.as.IndexedExpression.span);
this->as.IndexedExpression.type_id = move(rhs.as.IndexedExpression.type_id);
break;
case 14 /* IndexedDictionary */:
this->as.IndexedDictionary.expr = move(rhs.as.IndexedDictionary.expr);
this->as.IndexedDictionary.index = move(rhs.as.IndexedDictionary.index);
this->as.IndexedDictionary.trait_implementation = move(rhs.as.IndexedDictionary.trait_implementation);
this->as.IndexedDictionary.span = move(rhs.as.IndexedDictionary.span);
this->as.IndexedDictionary.type_id = move(rhs.as.IndexedDictionary.type_id);
break;
case 15 /* IndexedTuple */:
this->as.IndexedTuple.expr = move(rhs.as.IndexedTuple.expr);
this->as.IndexedTuple.index = move(rhs.as.IndexedTuple.index);
this->as.IndexedTuple.span = move(rhs.as.IndexedTuple.span);
this->as.IndexedTuple.is_optional = move(rhs.as.IndexedTuple.is_optional);
this->as.IndexedTuple.type_id = move(rhs.as.IndexedTuple.type_id);
break;
case 16 /* IndexedStruct */:
this->as.IndexedStruct.expr = move(rhs.as.IndexedStruct.expr);
this->as.IndexedStruct.name = move(rhs.as.IndexedStruct.name);
this->as.IndexedStruct.index = move(rhs.as.IndexedStruct.index);
this->as.IndexedStruct.span = move(rhs.as.IndexedStruct.span);
this->as.IndexedStruct.is_optional = move(rhs.as.IndexedStruct.is_optional);
this->as.IndexedStruct.type_id = move(rhs.as.IndexedStruct.type_id);
break;
case 17 /* IndexedCommonEnumMember */:
this->as.IndexedCommonEnumMember.expr = move(rhs.as.IndexedCommonEnumMember.expr);
this->as.IndexedCommonEnumMember.index = move(rhs.as.IndexedCommonEnumMember.index);
this->as.IndexedCommonEnumMember.span = move(rhs.as.IndexedCommonEnumMember.span);
this->as.IndexedCommonEnumMember.is_optional = move(rhs.as.IndexedCommonEnumMember.is_optional);
this->as.IndexedCommonEnumMember.type_id = move(rhs.as.IndexedCommonEnumMember.type_id);
break;
case 18 /* ComptimeIndex */:
this->as.ComptimeIndex.expr = move(rhs.as.ComptimeIndex.expr);
this->as.ComptimeIndex.index = move(rhs.as.ComptimeIndex.index);
this->as.ComptimeIndex.is_optional = move(rhs.as.ComptimeIndex.is_optional);
this->as.ComptimeIndex.span = move(rhs.as.ComptimeIndex.span);
break;
case 19 /* Match */:
this->as.Match.expr = move(rhs.as.Match.expr);
this->as.Match.match_cases = move(rhs.as.Match.match_cases);
this->as.Match.span = move(rhs.as.Match.span);
this->as.Match.type_id = move(rhs.as.Match.type_id);
this->as.Match.all_variants_constant = move(rhs.as.Match.all_variants_constant);
break;
case 20 /* EnumVariantArg */:
this->as.EnumVariantArg.expr = move(rhs.as.EnumVariantArg.expr);
this->as.EnumVariantArg.arg = move(rhs.as.EnumVariantArg.arg);
this->as.EnumVariantArg.enum_variant = move(rhs.as.EnumVariantArg.enum_variant);
this->as.EnumVariantArg.span = move(rhs.as.EnumVariantArg.span);
break;
case 21 /* Call */:
this->as.Call.call = move(rhs.as.Call.call);
this->as.Call.span = move(rhs.as.Call.span);
this->as.Call.type_id = move(rhs.as.Call.type_id);
break;
case 22 /* MethodCall */:
this->as.MethodCall.expr = move(rhs.as.MethodCall.expr);
this->as.MethodCall.call = move(rhs.as.MethodCall.call);
this->as.MethodCall.span = move(rhs.as.MethodCall.span);
this->as.MethodCall.is_optional = move(rhs.as.MethodCall.is_optional);
this->as.MethodCall.type_id = move(rhs.as.MethodCall.type_id);
break;
case 23 /* NamespacedVar */:
this->as.NamespacedVar.namespaces = move(rhs.as.NamespacedVar.namespaces);
this->as.NamespacedVar.var = move(rhs.as.NamespacedVar.var);
this->as.NamespacedVar.span = move(rhs.as.NamespacedVar.span);
break;
case 24 /* Var */:
this->as.Var.var = move(rhs.as.Var.var);
this->as.Var.span = move(rhs.as.Var.span);
break;
case 25 /* OptionalNone */:
this->as.OptionalNone.span = move(rhs.as.OptionalNone.span);
this->as.OptionalNone.type_id = move(rhs.as.OptionalNone.type_id);
break;
case 26 /* OptionalSome */:
this->as.OptionalSome.expr = move(rhs.as.OptionalSome.expr);
this->as.OptionalSome.span = move(rhs.as.OptionalSome.span);
this->as.OptionalSome.type_id = move(rhs.as.OptionalSome.type_id);
break;
case 27 /* ForcedUnwrap */:
this->as.ForcedUnwrap.expr = move(rhs.as.ForcedUnwrap.expr);
this->as.ForcedUnwrap.span = move(rhs.as.ForcedUnwrap.span);
this->as.ForcedUnwrap.type_id = move(rhs.as.ForcedUnwrap.type_id);
break;
case 28 /* Block */:
this->as.Block.block = move(rhs.as.Block.block);
this->as.Block.span = move(rhs.as.Block.span);
this->as.Block.type_id = move(rhs.as.Block.type_id);
break;
case 29 /* Function */:
this->as.Function.captures = move(rhs.as.Function.captures);
this->as.Function.params = move(rhs.as.Function.params);
this->as.Function.can_throw = move(rhs.as.Function.can_throw);
this->as.Function.return_type_id = move(rhs.as.Function.return_type_id);
this->as.Function.block = move(rhs.as.Function.block);
this->as.Function.span = move(rhs.as.Function.span);
this->as.Function.type_id = move(rhs.as.Function.type_id);
this->as.Function.pseudo_function_id = move(rhs.as.Function.pseudo_function_id);
this->as.Function.scope_id = move(rhs.as.Function.scope_id);
break;
case 30 /* DependentFunction */:
this->as.DependentFunction.captures = move(rhs.as.DependentFunction.captures);
this->as.DependentFunction.params = move(rhs.as.DependentFunction.params);
this->as.DependentFunction.can_throw = move(rhs.as.DependentFunction.can_throw);
this->as.DependentFunction.return_type_id = move(rhs.as.DependentFunction.return_type_id);
this->as.DependentFunction.block = move(rhs.as.DependentFunction.block);
this->as.DependentFunction.span = move(rhs.as.DependentFunction.span);
this->as.DependentFunction.type_id = move(rhs.as.DependentFunction.type_id);
this->as.DependentFunction.pseudo_function_id = move(rhs.as.DependentFunction.pseudo_function_id);
this->as.DependentFunction.scope_id = move(rhs.as.DependentFunction.scope_id);
break;
case 31 /* Must */:
this->as.Must.expr = move(rhs.as.Must.expr);
this->as.Must.span = move(rhs.as.Must.span);
this->as.Must.type_id = move(rhs.as.Must.type_id);
break;
case 32 /* Try */:
this->as.Try.expr = move(rhs.as.Try.expr);
this->as.Try.catch_block = move(rhs.as.Try.catch_block);
this->as.Try.catch_span = move(rhs.as.Try.catch_span);
this->as.Try.catch_name = move(rhs.as.Try.catch_name);
this->as.Try.span = move(rhs.as.Try.span);
this->as.Try.type_id = move(rhs.as.Try.type_id);
this->as.Try.inner_type_id = move(rhs.as.Try.inner_type_id);
break;
case 33 /* TryBlock */:
this->as.TryBlock.stmt = move(rhs.as.TryBlock.stmt);
this->as.TryBlock.catch_block = move(rhs.as.TryBlock.catch_block);
this->as.TryBlock.error_name = move(rhs.as.TryBlock.error_name);
this->as.TryBlock.error_span = move(rhs.as.TryBlock.error_span);
this->as.TryBlock.span = move(rhs.as.TryBlock.span);
this->as.TryBlock.type_id = move(rhs.as.TryBlock.type_id);
break;
case 34 /* Reflect */:
this->as.Reflect.type = move(rhs.as.Reflect.type);
this->as.Reflect.span = move(rhs.as.Reflect.span);
this->as.Reflect.type_id = move(rhs.as.Reflect.type_id);
break;
case 35 /* Garbage */:
this->as.Garbage.span = move(rhs.as.Garbage.span);
this->as.Garbage.type_id = move(rhs.as.Garbage.type_id);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedExpression::CheckedExpression(CheckedExpression &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.generic_inferences) (decltype(this->common.init_common.generic_inferences))(move(rhs.common.init_common.generic_inferences));
switch (rhs.__jakt_init_index()) {
case 0 /* Boolean */:
new (&this->as.Boolean.val) (decltype(this->as.Boolean.val))(move(rhs.as.Boolean.val));
new (&this->as.Boolean.span) (decltype(this->as.Boolean.span))(move(rhs.as.Boolean.span));
break;
case 1 /* NumericConstant */:
new (&this->as.NumericConstant.val) (decltype(this->as.NumericConstant.val))(move(rhs.as.NumericConstant.val));
new (&this->as.NumericConstant.span) (decltype(this->as.NumericConstant.span))(move(rhs.as.NumericConstant.span));
new (&this->as.NumericConstant.type_id) (decltype(this->as.NumericConstant.type_id))(move(rhs.as.NumericConstant.type_id));
break;
case 2 /* QuotedString */:
new (&this->as.QuotedString.val) (decltype(this->as.QuotedString.val))(move(rhs.as.QuotedString.val));
new (&this->as.QuotedString.span) (decltype(this->as.QuotedString.span))(move(rhs.as.QuotedString.span));
break;
case 3 /* ByteConstant */:
new (&this->as.ByteConstant.val) (decltype(this->as.ByteConstant.val))(move(rhs.as.ByteConstant.val));
new (&this->as.ByteConstant.span) (decltype(this->as.ByteConstant.span))(move(rhs.as.ByteConstant.span));
break;
case 4 /* CharacterConstant */:
new (&this->as.CharacterConstant.val) (decltype(this->as.CharacterConstant.val))(move(rhs.as.CharacterConstant.val));
new (&this->as.CharacterConstant.span) (decltype(this->as.CharacterConstant.span))(move(rhs.as.CharacterConstant.span));
break;
case 5 /* CCharacterConstant */:
new (&this->as.CCharacterConstant.val) (decltype(this->as.CCharacterConstant.val))(move(rhs.as.CCharacterConstant.val));
new (&this->as.CCharacterConstant.span) (decltype(this->as.CCharacterConstant.span))(move(rhs.as.CCharacterConstant.span));
break;
case 6 /* UnaryOp */:
new (&this->as.UnaryOp.expr) (decltype(this->as.UnaryOp.expr))(move(rhs.as.UnaryOp.expr));
new (&this->as.UnaryOp.op) (decltype(this->as.UnaryOp.op))(move(rhs.as.UnaryOp.op));
new (&this->as.UnaryOp.span) (decltype(this->as.UnaryOp.span))(move(rhs.as.UnaryOp.span));
new (&this->as.UnaryOp.type_id) (decltype(this->as.UnaryOp.type_id))(move(rhs.as.UnaryOp.type_id));
break;
case 7 /* BinaryOp */:
new (&this->as.BinaryOp.lhs) (decltype(this->as.BinaryOp.lhs))(move(rhs.as.BinaryOp.lhs));
new (&this->as.BinaryOp.op) (decltype(this->as.BinaryOp.op))(move(rhs.as.BinaryOp.op));
new (&this->as.BinaryOp.rhs) (decltype(this->as.BinaryOp.rhs))(move(rhs.as.BinaryOp.rhs));
new (&this->as.BinaryOp.span) (decltype(this->as.BinaryOp.span))(move(rhs.as.BinaryOp.span));
new (&this->as.BinaryOp.type_id) (decltype(this->as.BinaryOp.type_id))(move(rhs.as.BinaryOp.type_id));
break;
case 8 /* JaktTuple */:
new (&this->as.JaktTuple.vals) (decltype(this->as.JaktTuple.vals))(move(rhs.as.JaktTuple.vals));
new (&this->as.JaktTuple.span) (decltype(this->as.JaktTuple.span))(move(rhs.as.JaktTuple.span));
new (&this->as.JaktTuple.type_id) (decltype(this->as.JaktTuple.type_id))(move(rhs.as.JaktTuple.type_id));
break;
case 9 /* Range */:
new (&this->as.Range.from) (decltype(this->as.Range.from))(move(rhs.as.Range.from));
new (&this->as.Range.to) (decltype(this->as.Range.to))(move(rhs.as.Range.to));
new (&this->as.Range.span) (decltype(this->as.Range.span))(move(rhs.as.Range.span));
new (&this->as.Range.type_id) (decltype(this->as.Range.type_id))(move(rhs.as.Range.type_id));
break;
case 10 /* JaktArray */:
new (&this->as.JaktArray.vals) (decltype(this->as.JaktArray.vals))(move(rhs.as.JaktArray.vals));
new (&this->as.JaktArray.repeat) (decltype(this->as.JaktArray.repeat))(move(rhs.as.JaktArray.repeat));
new (&this->as.JaktArray.span) (decltype(this->as.JaktArray.span))(move(rhs.as.JaktArray.span));
new (&this->as.JaktArray.type_id) (decltype(this->as.JaktArray.type_id))(move(rhs.as.JaktArray.type_id));
new (&this->as.JaktArray.inner_type_id) (decltype(this->as.JaktArray.inner_type_id))(move(rhs.as.JaktArray.inner_type_id));
break;
case 11 /* JaktSet */:
new (&this->as.JaktSet.vals) (decltype(this->as.JaktSet.vals))(move(rhs.as.JaktSet.vals));
new (&this->as.JaktSet.span) (decltype(this->as.JaktSet.span))(move(rhs.as.JaktSet.span));
new (&this->as.JaktSet.type_id) (decltype(this->as.JaktSet.type_id))(move(rhs.as.JaktSet.type_id));
new (&this->as.JaktSet.inner_type_id) (decltype(this->as.JaktSet.inner_type_id))(move(rhs.as.JaktSet.inner_type_id));
break;
case 12 /* JaktDictionary */:
new (&this->as.JaktDictionary.vals) (decltype(this->as.JaktDictionary.vals))(move(rhs.as.JaktDictionary.vals));
new (&this->as.JaktDictionary.span) (decltype(this->as.JaktDictionary.span))(move(rhs.as.JaktDictionary.span));
new (&this->as.JaktDictionary.type_id) (decltype(this->as.JaktDictionary.type_id))(move(rhs.as.JaktDictionary.type_id));
new (&this->as.JaktDictionary.key_type_id) (decltype(this->as.JaktDictionary.key_type_id))(move(rhs.as.JaktDictionary.key_type_id));
new (&this->as.JaktDictionary.value_type_id) (decltype(this->as.JaktDictionary.value_type_id))(move(rhs.as.JaktDictionary.value_type_id));
break;
case 13 /* IndexedExpression */:
new (&this->as.IndexedExpression.expr) (decltype(this->as.IndexedExpression.expr))(move(rhs.as.IndexedExpression.expr));
new (&this->as.IndexedExpression.index) (decltype(this->as.IndexedExpression.index))(move(rhs.as.IndexedExpression.index));
new (&this->as.IndexedExpression.trait_implementation) (decltype(this->as.IndexedExpression.trait_implementation))(move(rhs.as.IndexedExpression.trait_implementation));
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(move(rhs.as.IndexedExpression.span));
new (&this->as.IndexedExpression.type_id) (decltype(this->as.IndexedExpression.type_id))(move(rhs.as.IndexedExpression.type_id));
break;
case 14 /* IndexedDictionary */:
new (&this->as.IndexedDictionary.expr) (decltype(this->as.IndexedDictionary.expr))(move(rhs.as.IndexedDictionary.expr));
new (&this->as.IndexedDictionary.index) (decltype(this->as.IndexedDictionary.index))(move(rhs.as.IndexedDictionary.index));
new (&this->as.IndexedDictionary.trait_implementation) (decltype(this->as.IndexedDictionary.trait_implementation))(move(rhs.as.IndexedDictionary.trait_implementation));
new (&this->as.IndexedDictionary.span) (decltype(this->as.IndexedDictionary.span))(move(rhs.as.IndexedDictionary.span));
new (&this->as.IndexedDictionary.type_id) (decltype(this->as.IndexedDictionary.type_id))(move(rhs.as.IndexedDictionary.type_id));
break;
case 15 /* IndexedTuple */:
new (&this->as.IndexedTuple.expr) (decltype(this->as.IndexedTuple.expr))(move(rhs.as.IndexedTuple.expr));
new (&this->as.IndexedTuple.index) (decltype(this->as.IndexedTuple.index))(move(rhs.as.IndexedTuple.index));
new (&this->as.IndexedTuple.span) (decltype(this->as.IndexedTuple.span))(move(rhs.as.IndexedTuple.span));
new (&this->as.IndexedTuple.is_optional) (decltype(this->as.IndexedTuple.is_optional))(move(rhs.as.IndexedTuple.is_optional));
new (&this->as.IndexedTuple.type_id) (decltype(this->as.IndexedTuple.type_id))(move(rhs.as.IndexedTuple.type_id));
break;
case 16 /* IndexedStruct */:
new (&this->as.IndexedStruct.expr) (decltype(this->as.IndexedStruct.expr))(move(rhs.as.IndexedStruct.expr));
new (&this->as.IndexedStruct.name) (decltype(this->as.IndexedStruct.name))(move(rhs.as.IndexedStruct.name));
new (&this->as.IndexedStruct.index) (decltype(this->as.IndexedStruct.index))(move(rhs.as.IndexedStruct.index));
new (&this->as.IndexedStruct.span) (decltype(this->as.IndexedStruct.span))(move(rhs.as.IndexedStruct.span));
new (&this->as.IndexedStruct.is_optional) (decltype(this->as.IndexedStruct.is_optional))(move(rhs.as.IndexedStruct.is_optional));
new (&this->as.IndexedStruct.type_id) (decltype(this->as.IndexedStruct.type_id))(move(rhs.as.IndexedStruct.type_id));
break;
case 17 /* IndexedCommonEnumMember */:
new (&this->as.IndexedCommonEnumMember.expr) (decltype(this->as.IndexedCommonEnumMember.expr))(move(rhs.as.IndexedCommonEnumMember.expr));
new (&this->as.IndexedCommonEnumMember.index) (decltype(this->as.IndexedCommonEnumMember.index))(move(rhs.as.IndexedCommonEnumMember.index));
new (&this->as.IndexedCommonEnumMember.span) (decltype(this->as.IndexedCommonEnumMember.span))(move(rhs.as.IndexedCommonEnumMember.span));
new (&this->as.IndexedCommonEnumMember.is_optional) (decltype(this->as.IndexedCommonEnumMember.is_optional))(move(rhs.as.IndexedCommonEnumMember.is_optional));
new (&this->as.IndexedCommonEnumMember.type_id) (decltype(this->as.IndexedCommonEnumMember.type_id))(move(rhs.as.IndexedCommonEnumMember.type_id));
break;
case 18 /* ComptimeIndex */:
new (&this->as.ComptimeIndex.expr) (decltype(this->as.ComptimeIndex.expr))(move(rhs.as.ComptimeIndex.expr));
new (&this->as.ComptimeIndex.index) (decltype(this->as.ComptimeIndex.index))(move(rhs.as.ComptimeIndex.index));
new (&this->as.ComptimeIndex.is_optional) (decltype(this->as.ComptimeIndex.is_optional))(move(rhs.as.ComptimeIndex.is_optional));
new (&this->as.ComptimeIndex.span) (decltype(this->as.ComptimeIndex.span))(move(rhs.as.ComptimeIndex.span));
break;
case 19 /* Match */:
new (&this->as.Match.expr) (decltype(this->as.Match.expr))(move(rhs.as.Match.expr));
new (&this->as.Match.match_cases) (decltype(this->as.Match.match_cases))(move(rhs.as.Match.match_cases));
new (&this->as.Match.span) (decltype(this->as.Match.span))(move(rhs.as.Match.span));
new (&this->as.Match.type_id) (decltype(this->as.Match.type_id))(move(rhs.as.Match.type_id));
new (&this->as.Match.all_variants_constant) (decltype(this->as.Match.all_variants_constant))(move(rhs.as.Match.all_variants_constant));
break;
case 20 /* EnumVariantArg */:
new (&this->as.EnumVariantArg.expr) (decltype(this->as.EnumVariantArg.expr))(move(rhs.as.EnumVariantArg.expr));
new (&this->as.EnumVariantArg.arg) (decltype(this->as.EnumVariantArg.arg))(move(rhs.as.EnumVariantArg.arg));
new (&this->as.EnumVariantArg.enum_variant) (decltype(this->as.EnumVariantArg.enum_variant))(move(rhs.as.EnumVariantArg.enum_variant));
new (&this->as.EnumVariantArg.span) (decltype(this->as.EnumVariantArg.span))(move(rhs.as.EnumVariantArg.span));
break;
case 21 /* Call */:
new (&this->as.Call.call) (decltype(this->as.Call.call))(move(rhs.as.Call.call));
new (&this->as.Call.span) (decltype(this->as.Call.span))(move(rhs.as.Call.span));
new (&this->as.Call.type_id) (decltype(this->as.Call.type_id))(move(rhs.as.Call.type_id));
break;
case 22 /* MethodCall */:
new (&this->as.MethodCall.expr) (decltype(this->as.MethodCall.expr))(move(rhs.as.MethodCall.expr));
new (&this->as.MethodCall.call) (decltype(this->as.MethodCall.call))(move(rhs.as.MethodCall.call));
new (&this->as.MethodCall.span) (decltype(this->as.MethodCall.span))(move(rhs.as.MethodCall.span));
new (&this->as.MethodCall.is_optional) (decltype(this->as.MethodCall.is_optional))(move(rhs.as.MethodCall.is_optional));
new (&this->as.MethodCall.type_id) (decltype(this->as.MethodCall.type_id))(move(rhs.as.MethodCall.type_id));
break;
case 23 /* NamespacedVar */:
new (&this->as.NamespacedVar.namespaces) (decltype(this->as.NamespacedVar.namespaces))(move(rhs.as.NamespacedVar.namespaces));
new (&this->as.NamespacedVar.var) (decltype(this->as.NamespacedVar.var))(move(rhs.as.NamespacedVar.var));
new (&this->as.NamespacedVar.span) (decltype(this->as.NamespacedVar.span))(move(rhs.as.NamespacedVar.span));
break;
case 24 /* Var */:
new (&this->as.Var.var) (decltype(this->as.Var.var))(move(rhs.as.Var.var));
new (&this->as.Var.span) (decltype(this->as.Var.span))(move(rhs.as.Var.span));
break;
case 25 /* OptionalNone */:
new (&this->as.OptionalNone.span) (decltype(this->as.OptionalNone.span))(move(rhs.as.OptionalNone.span));
new (&this->as.OptionalNone.type_id) (decltype(this->as.OptionalNone.type_id))(move(rhs.as.OptionalNone.type_id));
break;
case 26 /* OptionalSome */:
new (&this->as.OptionalSome.expr) (decltype(this->as.OptionalSome.expr))(move(rhs.as.OptionalSome.expr));
new (&this->as.OptionalSome.span) (decltype(this->as.OptionalSome.span))(move(rhs.as.OptionalSome.span));
new (&this->as.OptionalSome.type_id) (decltype(this->as.OptionalSome.type_id))(move(rhs.as.OptionalSome.type_id));
break;
case 27 /* ForcedUnwrap */:
new (&this->as.ForcedUnwrap.expr) (decltype(this->as.ForcedUnwrap.expr))(move(rhs.as.ForcedUnwrap.expr));
new (&this->as.ForcedUnwrap.span) (decltype(this->as.ForcedUnwrap.span))(move(rhs.as.ForcedUnwrap.span));
new (&this->as.ForcedUnwrap.type_id) (decltype(this->as.ForcedUnwrap.type_id))(move(rhs.as.ForcedUnwrap.type_id));
break;
case 28 /* Block */:
new (&this->as.Block.block) (decltype(this->as.Block.block))(move(rhs.as.Block.block));
new (&this->as.Block.span) (decltype(this->as.Block.span))(move(rhs.as.Block.span));
new (&this->as.Block.type_id) (decltype(this->as.Block.type_id))(move(rhs.as.Block.type_id));
break;
case 29 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(move(rhs.as.Function.captures));
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(move(rhs.as.Function.return_type_id));
new (&this->as.Function.block) (decltype(this->as.Function.block))(move(rhs.as.Function.block));
new (&this->as.Function.span) (decltype(this->as.Function.span))(move(rhs.as.Function.span));
new (&this->as.Function.type_id) (decltype(this->as.Function.type_id))(move(rhs.as.Function.type_id));
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(move(rhs.as.Function.pseudo_function_id));
new (&this->as.Function.scope_id) (decltype(this->as.Function.scope_id))(move(rhs.as.Function.scope_id));
break;
case 30 /* DependentFunction */:
new (&this->as.DependentFunction.captures) (decltype(this->as.DependentFunction.captures))(move(rhs.as.DependentFunction.captures));
new (&this->as.DependentFunction.params) (decltype(this->as.DependentFunction.params))(move(rhs.as.DependentFunction.params));
new (&this->as.DependentFunction.can_throw) (decltype(this->as.DependentFunction.can_throw))(move(rhs.as.DependentFunction.can_throw));
new (&this->as.DependentFunction.return_type_id) (decltype(this->as.DependentFunction.return_type_id))(move(rhs.as.DependentFunction.return_type_id));
new (&this->as.DependentFunction.block) (decltype(this->as.DependentFunction.block))(move(rhs.as.DependentFunction.block));
new (&this->as.DependentFunction.span) (decltype(this->as.DependentFunction.span))(move(rhs.as.DependentFunction.span));
new (&this->as.DependentFunction.type_id) (decltype(this->as.DependentFunction.type_id))(move(rhs.as.DependentFunction.type_id));
new (&this->as.DependentFunction.pseudo_function_id) (decltype(this->as.DependentFunction.pseudo_function_id))(move(rhs.as.DependentFunction.pseudo_function_id));
new (&this->as.DependentFunction.scope_id) (decltype(this->as.DependentFunction.scope_id))(move(rhs.as.DependentFunction.scope_id));
break;
case 31 /* Must */:
new (&this->as.Must.expr) (decltype(this->as.Must.expr))(move(rhs.as.Must.expr));
new (&this->as.Must.span) (decltype(this->as.Must.span))(move(rhs.as.Must.span));
new (&this->as.Must.type_id) (decltype(this->as.Must.type_id))(move(rhs.as.Must.type_id));
break;
case 32 /* Try */:
new (&this->as.Try.expr) (decltype(this->as.Try.expr))(move(rhs.as.Try.expr));
new (&this->as.Try.catch_block) (decltype(this->as.Try.catch_block))(move(rhs.as.Try.catch_block));
new (&this->as.Try.catch_span) (decltype(this->as.Try.catch_span))(move(rhs.as.Try.catch_span));
new (&this->as.Try.catch_name) (decltype(this->as.Try.catch_name))(move(rhs.as.Try.catch_name));
new (&this->as.Try.span) (decltype(this->as.Try.span))(move(rhs.as.Try.span));
new (&this->as.Try.type_id) (decltype(this->as.Try.type_id))(move(rhs.as.Try.type_id));
new (&this->as.Try.inner_type_id) (decltype(this->as.Try.inner_type_id))(move(rhs.as.Try.inner_type_id));
break;
case 33 /* TryBlock */:
new (&this->as.TryBlock.stmt) (decltype(this->as.TryBlock.stmt))(move(rhs.as.TryBlock.stmt));
new (&this->as.TryBlock.catch_block) (decltype(this->as.TryBlock.catch_block))(move(rhs.as.TryBlock.catch_block));
new (&this->as.TryBlock.error_name) (decltype(this->as.TryBlock.error_name))(move(rhs.as.TryBlock.error_name));
new (&this->as.TryBlock.error_span) (decltype(this->as.TryBlock.error_span))(move(rhs.as.TryBlock.error_span));
new (&this->as.TryBlock.span) (decltype(this->as.TryBlock.span))(move(rhs.as.TryBlock.span));
new (&this->as.TryBlock.type_id) (decltype(this->as.TryBlock.type_id))(move(rhs.as.TryBlock.type_id));
break;
case 34 /* Reflect */:
new (&this->as.Reflect.type) (decltype(this->as.Reflect.type))(move(rhs.as.Reflect.type));
new (&this->as.Reflect.span) (decltype(this->as.Reflect.span))(move(rhs.as.Reflect.span));
new (&this->as.Reflect.type_id) (decltype(this->as.Reflect.type_id))(move(rhs.as.Reflect.type_id));
break;
case 35 /* Garbage */:
new (&this->as.Garbage.span) (decltype(this->as.Garbage.span))(move(rhs.as.Garbage.span));
new (&this->as.Garbage.type_id) (decltype(this->as.Garbage.type_id))(move(rhs.as.Garbage.type_id));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedExpression::~CheckedExpression(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.generic_inferences.~Optional();
this->__jakt_destroy_variant(); }
void CheckedExpression::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Boolean */:this->as.Boolean.span.~Span();
break;
case 1 /* NumericConstant */:this->as.NumericConstant.val.~CheckedNumericConstant();
this->as.NumericConstant.span.~Span();
this->as.NumericConstant.type_id.~TypeId();
break;
case 2 /* QuotedString */:this->as.QuotedString.val.~CheckedStringLiteral();
this->as.QuotedString.span.~Span();
break;
case 3 /* ByteConstant */:this->as.ByteConstant.val.~ByteString();
this->as.ByteConstant.span.~Span();
break;
case 4 /* CharacterConstant */:this->as.CharacterConstant.val.~ByteString();
this->as.CharacterConstant.span.~Span();
break;
case 5 /* CCharacterConstant */:this->as.CCharacterConstant.val.~ByteString();
this->as.CCharacterConstant.span.~Span();
break;
case 6 /* UnaryOp */:this->as.UnaryOp.expr.~NonnullRefPtr();
this->as.UnaryOp.op.~CheckedUnaryOperator();
this->as.UnaryOp.span.~Span();
this->as.UnaryOp.type_id.~TypeId();
break;
case 7 /* BinaryOp */:this->as.BinaryOp.lhs.~NonnullRefPtr();
this->as.BinaryOp.op.~CheckedBinaryOperator();
this->as.BinaryOp.rhs.~NonnullRefPtr();
this->as.BinaryOp.span.~Span();
this->as.BinaryOp.type_id.~TypeId();
break;
case 8 /* JaktTuple */:this->as.JaktTuple.vals.~DynamicArray();
this->as.JaktTuple.span.~Span();
this->as.JaktTuple.type_id.~TypeId();
break;
case 9 /* Range */:this->as.Range.from.~Optional();
this->as.Range.to.~Optional();
this->as.Range.span.~Span();
this->as.Range.type_id.~TypeId();
break;
case 10 /* JaktArray */:this->as.JaktArray.vals.~DynamicArray();
this->as.JaktArray.repeat.~Optional();
this->as.JaktArray.span.~Span();
this->as.JaktArray.type_id.~TypeId();
this->as.JaktArray.inner_type_id.~TypeId();
break;
case 11 /* JaktSet */:this->as.JaktSet.vals.~DynamicArray();
this->as.JaktSet.span.~Span();
this->as.JaktSet.type_id.~TypeId();
this->as.JaktSet.inner_type_id.~TypeId();
break;
case 12 /* JaktDictionary */:this->as.JaktDictionary.vals.~DynamicArray();
this->as.JaktDictionary.span.~Span();
this->as.JaktDictionary.type_id.~TypeId();
this->as.JaktDictionary.key_type_id.~TypeId();
this->as.JaktDictionary.value_type_id.~TypeId();
break;
case 13 /* IndexedExpression */:this->as.IndexedExpression.expr.~NonnullRefPtr();
this->as.IndexedExpression.index.~NonnullRefPtr();
this->as.IndexedExpression.trait_implementation.~Optional();
this->as.IndexedExpression.span.~Span();
this->as.IndexedExpression.type_id.~TypeId();
break;
case 14 /* IndexedDictionary */:this->as.IndexedDictionary.expr.~NonnullRefPtr();
this->as.IndexedDictionary.index.~NonnullRefPtr();
this->as.IndexedDictionary.trait_implementation.~Optional();
this->as.IndexedDictionary.span.~Span();
this->as.IndexedDictionary.type_id.~TypeId();
break;
case 15 /* IndexedTuple */:this->as.IndexedTuple.expr.~NonnullRefPtr();
this->as.IndexedTuple.span.~Span();
this->as.IndexedTuple.type_id.~TypeId();
break;
case 16 /* IndexedStruct */:this->as.IndexedStruct.expr.~NonnullRefPtr();
this->as.IndexedStruct.name.~ByteString();
this->as.IndexedStruct.index.~Optional();
this->as.IndexedStruct.span.~Span();
this->as.IndexedStruct.type_id.~TypeId();
break;
case 17 /* IndexedCommonEnumMember */:this->as.IndexedCommonEnumMember.expr.~NonnullRefPtr();
this->as.IndexedCommonEnumMember.index.~ByteString();
this->as.IndexedCommonEnumMember.span.~Span();
this->as.IndexedCommonEnumMember.type_id.~TypeId();
break;
case 18 /* ComptimeIndex */:this->as.ComptimeIndex.expr.~NonnullRefPtr();
this->as.ComptimeIndex.index.~NonnullRefPtr();
this->as.ComptimeIndex.span.~Span();
break;
case 19 /* Match */:this->as.Match.expr.~NonnullRefPtr();
this->as.Match.match_cases.~DynamicArray();
this->as.Match.span.~Span();
this->as.Match.type_id.~TypeId();
break;
case 20 /* EnumVariantArg */:this->as.EnumVariantArg.expr.~NonnullRefPtr();
this->as.EnumVariantArg.arg.~CheckedEnumVariantBinding();
this->as.EnumVariantArg.enum_variant.~CheckedEnumVariant();
this->as.EnumVariantArg.span.~Span();
break;
case 21 /* Call */:this->as.Call.call.~CheckedCall();
this->as.Call.span.~Span();
this->as.Call.type_id.~TypeId();
break;
case 22 /* MethodCall */:this->as.MethodCall.expr.~NonnullRefPtr();
this->as.MethodCall.call.~CheckedCall();
this->as.MethodCall.span.~Span();
this->as.MethodCall.type_id.~TypeId();
break;
case 23 /* NamespacedVar */:this->as.NamespacedVar.namespaces.~DynamicArray();
this->as.NamespacedVar.var.~NonnullRefPtr();
this->as.NamespacedVar.span.~Span();
break;
case 24 /* Var */:this->as.Var.var.~NonnullRefPtr();
this->as.Var.span.~Span();
break;
case 25 /* OptionalNone */:this->as.OptionalNone.span.~Span();
this->as.OptionalNone.type_id.~TypeId();
break;
case 26 /* OptionalSome */:this->as.OptionalSome.expr.~NonnullRefPtr();
this->as.OptionalSome.span.~Span();
this->as.OptionalSome.type_id.~TypeId();
break;
case 27 /* ForcedUnwrap */:this->as.ForcedUnwrap.expr.~NonnullRefPtr();
this->as.ForcedUnwrap.span.~Span();
this->as.ForcedUnwrap.type_id.~TypeId();
break;
case 28 /* Block */:this->as.Block.block.~CheckedBlock();
this->as.Block.span.~Span();
this->as.Block.type_id.~TypeId();
break;
case 29 /* Function */:this->as.Function.captures.~DynamicArray();
this->as.Function.params.~DynamicArray();
this->as.Function.return_type_id.~TypeId();
this->as.Function.block.~CheckedBlock();
this->as.Function.span.~Span();
this->as.Function.type_id.~TypeId();
this->as.Function.pseudo_function_id.~Optional();
this->as.Function.scope_id.~ScopeId();
break;
case 30 /* DependentFunction */:this->as.DependentFunction.captures.~DynamicArray();
this->as.DependentFunction.params.~DynamicArray();
this->as.DependentFunction.return_type_id.~TypeId();
this->as.DependentFunction.block.~ParsedBlock();
this->as.DependentFunction.span.~Span();
this->as.DependentFunction.type_id.~TypeId();
this->as.DependentFunction.pseudo_function_id.~Optional();
this->as.DependentFunction.scope_id.~ScopeId();
break;
case 31 /* Must */:this->as.Must.expr.~NonnullRefPtr();
this->as.Must.span.~Span();
this->as.Must.type_id.~TypeId();
break;
case 32 /* Try */:this->as.Try.expr.~NonnullRefPtr();
this->as.Try.catch_block.~Optional();
this->as.Try.catch_span.~Optional();
this->as.Try.catch_name.~Optional();
this->as.Try.span.~Span();
this->as.Try.type_id.~TypeId();
this->as.Try.inner_type_id.~TypeId();
break;
case 33 /* TryBlock */:this->as.TryBlock.stmt.~NonnullRefPtr();
this->as.TryBlock.catch_block.~CheckedBlock();
this->as.TryBlock.error_name.~ByteString();
this->as.TryBlock.error_span.~Span();
this->as.TryBlock.span.~Span();
this->as.TryBlock.type_id.~TypeId();
break;
case 34 /* Reflect */:this->as.Reflect.type.~TypeId();
this->as.Reflect.span.~Span();
this->as.Reflect.type_id.~TypeId();
break;
case 35 /* Garbage */:this->as.Garbage.span.~Span();
this->as.Garbage.type_id.~TypeId();
break;
}
}
JaktInternal::Optional<Jakt::types::NumberConstant> Jakt::types::CheckedExpression::to_number_constant(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::NumberConstant>, JaktInternal::Optional<Jakt::types::NumberConstant>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;Jakt::types::CheckedNumericConstant const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(val.number_constant());
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedUnaryOperator const& op = __jakt_match_value.op;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::Optional<Jakt::types::NumberConstant> result = JaktInternal::OptionalNone();
Jakt::types::CheckedUnaryOperator __jakt_tmp58 = op;
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::types::NumberConstant>>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::NumberConstant>,JaktInternal::Optional<Jakt::types::NumberConstant>> {
auto __jakt_enum_value = (__jakt_tmp58.__jakt_init_index() == 11 /* TypeCast */);
if (__jakt_enum_value) {{
Jakt::types::CheckedTypeCast const cast = __jakt_tmp58.as.TypeCast.value;
if (!(cast.__jakt_init_index() == 1 /* Infallible */)){
result = JaktInternal::OptionalNone();
}
if ((!program->is_integer(type_id)) && (!program->is_floating(type_id))){
result = JaktInternal::OptionalNone();
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> __jakt_tmp59 = expr;
if (__jakt_tmp59->__jakt_init_index() == 1 /* NumericConstant */){
Jakt::types::CheckedNumericConstant const val = __jakt_tmp59->as.NumericConstant.val;
result = val.number_constant();
}
return JaktInternal::ExplicitValue<JaktInternal::Optional<Jakt::types::NumberConstant>>(result);
}
VERIFY_NOT_REACHED();
}else {{
return JaktInternal::OptionalNone();
}
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

Jakt::utility::Span Jakt::types::CheckedExpression::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::utility::Span, Jakt::utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* ByteConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ByteConstant;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* CharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CharacterConstant;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* CCharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CCharacterConstant;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 18 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 25 /* OptionalNone */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalNone;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 30 /* DependentFunction */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentFunction;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 31 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 32 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 34 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 35 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;Jakt::utility::Span const& span = __jakt_match_value.span;
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
}

bool Jakt::types::CheckedExpression::is_mutable(NonnullRefPtr<Jakt::types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */:case 1 /* NumericConstant */:case 2 /* QuotedString */:case 3 /* ByteConstant */:case 4 /* CharacterConstant */:case 5 /* CCharacterConstant */:return JaktInternal::ExplicitValue(true);
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(var->is_mutable);
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(expr->is_mutable(program));
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(expr->is_mutable(program));
};/*case end*/
case 18 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(expr->is_mutable(program));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(expr->is_mutable(program));
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(expr->is_mutable(program));
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(expr->is_mutable(program));
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
{
bool result = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = _magic_value.value();
{
if (val->is_mutable(program)){
result = true;
break;
}
}

}
}

return JaktInternal::ExplicitValue<bool>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
{
bool result = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = _magic_value.value();
{
if (val->is_mutable(program)){
result = true;
break;
}
}

}
}

return JaktInternal::ExplicitValue<bool>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
{
bool result = false;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = vals.iterator();
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> ___val__ = _magic_value.value();
{
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt_____val__ = ___val__;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const _ = jakt_____val__.template get<0>();
NonnullRefPtr<typename Jakt::types::CheckedExpression> const val = jakt_____val__.template get<1>();

if (val->is_mutable(program)){
result = true;
break;
}
}

}
}

return JaktInternal::ExplicitValue<bool>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedUnaryOperator const& op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Dereference */:return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *program->get_type(expr->type());
switch(__jakt_match_variant.__jakt_init_index()) {
case 28 /* MutableReference */:return JaktInternal::ExplicitValue(true);
case 25 /* RawPtr */:return JaktInternal::ExplicitValue(expr->is_mutable(program));
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(expr->is_mutable(program));
};/*case end*/
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

bool Jakt::types::CheckedExpression::can_throw() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(call.callee_throws);
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(call.callee_throws);
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;Jakt::types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(val.may_throw);
};/*case end*/
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

Jakt::ids::TypeId Jakt::types::CheckedExpression::type() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, Jakt::ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()));
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;Jakt::types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(val.type_id);
};/*case end*/
case 3 /* ByteConstant */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U8()));
case 5 /* CCharacterConstant */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::CChar()));
case 4 /* CharacterConstant */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U32()));
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;Jakt::types::CheckedEnumVariantBinding const& arg = __jakt_match_value.arg;
return JaktInternal::ExplicitValue(arg.type_id);
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(var->type_id);
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(var->type_id);
};/*case end*/
case 18 /* ComptimeIndex */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Unknown()));
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 25 /* OptionalNone */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalNone;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 30 /* DependentFunction */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentFunction;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 31 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 32 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 34 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 35 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
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

Jakt::types::BlockControlFlow Jakt::types::CheckedExpression::control_flow() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
bool const& all_variants_constant = __jakt_match_value.all_variants_constant;
{
JaktInternal::Optional<Jakt::types::BlockControlFlow> control_flow = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = match_cases.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::CheckedMatchCase case_ = _magic_value.value();
{
Jakt::types::BlockControlFlow const case_control_flow = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow, Jakt::types::BlockControlFlow>{
auto&& __jakt_match_variant = case_.body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(block.control_flow);
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(expr->control_flow());
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
if (control_flow.has_value()){
control_flow = control_flow.value().branch_unify_with(case_control_flow);
}
else {
control_flow = case_control_flow;
}

}

}
}

return JaktInternal::ExplicitValue<Jakt::types::BlockControlFlow>(control_flow.value_or_lazy_evaluated([&] { return Jakt::types::BlockControlFlow::MayReturn(); }));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (type_id.equals(Jakt::types::never_type_id()));
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::NeverReturns());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (type_id.equals(Jakt::types::never_type_id()));
if (__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::NeverReturns());
}else if (!__jakt_enum_value) {return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
Jakt::types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
{
NonnullRefPtr<typename Jakt::types::CheckedStatement> __jakt_tmp60 = stmt;
return JaktInternal::ExplicitValue<Jakt::types::BlockControlFlow>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BlockControlFlow,Jakt::types::BlockControlFlow> {
auto __jakt_enum_value = (__jakt_tmp60->__jakt_init_index() == 5 /* Block */);
if (__jakt_enum_value) {{
Jakt::types::CheckedBlock const block = __jakt_tmp60->as.Block.block;
return JaktInternal::ExplicitValue<Jakt::types::BlockControlFlow>(block.control_flow.branch_unify_with(catch_block.control_flow));
}
VERIFY_NOT_REACHED();
}else {{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Try block doesn't have a block"sv));
}
}}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default:return JaktInternal::ExplicitValue(Jakt::types::BlockControlFlow::MayReturn());
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ByteString Jakt::types::ValueImpl::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Void */: {
return ByteString("ValueImpl::Void"sv);
break;}
case 1 /* Bool */: {
builder.append("ValueImpl::Bool"sv);
[[maybe_unused]] auto const& that = this->as.Bool;
builder.appendff("({})", that.value);
break;}
case 2 /* U8 */: {
builder.append("ValueImpl::U8"sv);
[[maybe_unused]] auto const& that = this->as.U8;
builder.appendff("({})", that.value);
break;}
case 3 /* U16 */: {
builder.append("ValueImpl::U16"sv);
[[maybe_unused]] auto const& that = this->as.U16;
builder.appendff("({})", that.value);
break;}
case 4 /* U32 */: {
builder.append("ValueImpl::U32"sv);
[[maybe_unused]] auto const& that = this->as.U32;
builder.appendff("({})", that.value);
break;}
case 5 /* U64 */: {
builder.append("ValueImpl::U64"sv);
[[maybe_unused]] auto const& that = this->as.U64;
builder.appendff("({})", that.value);
break;}
case 6 /* I8 */: {
builder.append("ValueImpl::I8"sv);
[[maybe_unused]] auto const& that = this->as.I8;
builder.appendff("({})", that.value);
break;}
case 7 /* I16 */: {
builder.append("ValueImpl::I16"sv);
[[maybe_unused]] auto const& that = this->as.I16;
builder.appendff("({})", that.value);
break;}
case 8 /* I32 */: {
builder.append("ValueImpl::I32"sv);
[[maybe_unused]] auto const& that = this->as.I32;
builder.appendff("({})", that.value);
break;}
case 9 /* I64 */: {
builder.append("ValueImpl::I64"sv);
[[maybe_unused]] auto const& that = this->as.I64;
builder.appendff("({})", that.value);
break;}
case 10 /* F32 */: {
builder.append("ValueImpl::F32"sv);
[[maybe_unused]] auto const& that = this->as.F32;
builder.appendff("({})", that.value);
break;}
case 11 /* F64 */: {
builder.append("ValueImpl::F64"sv);
[[maybe_unused]] auto const& that = this->as.F64;
builder.appendff("({})", that.value);
break;}
case 12 /* USize */: {
builder.append("ValueImpl::USize"sv);
[[maybe_unused]] auto const& that = this->as.USize;
builder.appendff("({})", that.value);
break;}
case 13 /* JaktString */: {
builder.append("ValueImpl::JaktString"sv);
[[maybe_unused]] auto const& that = this->as.JaktString;
builder.appendff("(\"{}\")", that.value);
break;}
case 14 /* StringView */: {
builder.append("ValueImpl::StringView"sv);
[[maybe_unused]] auto const& that = this->as.StringView;
builder.appendff("(\"{}\")", that.value);
break;}
case 15 /* CChar */: {
builder.append("ValueImpl::CChar"sv);
[[maybe_unused]] auto const& that = this->as.CChar;
builder.appendff("({})", that.value);
break;}
case 16 /* CInt */: {
builder.append("ValueImpl::CInt"sv);
[[maybe_unused]] auto const& that = this->as.CInt;
builder.appendff("({})", that.value);
break;}
case 17 /* Struct */: {
builder.append("ValueImpl::Struct"sv);
[[maybe_unused]] auto const& that = this->as.Struct;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", that.fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("struct_id: {}, ", that.struct_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("constructor: {}", that.constructor);
}
builder.append(")"sv);
break;}
case 18 /* Class */: {
builder.append("ValueImpl::Class"sv);
[[maybe_unused]] auto const& that = this->as.Class;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", that.fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("struct_id: {}, ", that.struct_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("constructor: {}", that.constructor);
}
builder.append(")"sv);
break;}
case 19 /* Enum */: {
builder.append("ValueImpl::Enum"sv);
[[maybe_unused]] auto const& that = this->as.Enum;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", that.fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("enum_id: {}, ", that.enum_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("constructor: {}", that.constructor);
}
builder.append(")"sv);
break;}
case 20 /* JaktArray */: {
builder.append("ValueImpl::JaktArray"sv);
[[maybe_unused]] auto const& that = this->as.JaktArray;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}, ", that.values);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 21 /* JaktDictionary */: {
builder.append("ValueImpl::JaktDictionary"sv);
[[maybe_unused]] auto const& that = this->as.JaktDictionary;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("keys: {}, ", that.keys);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}, ", that.values);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 22 /* JaktSet */: {
builder.append("ValueImpl::JaktSet"sv);
[[maybe_unused]] auto const& that = this->as.JaktSet;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}, ", that.values);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 23 /* RawPtr */: {
builder.append("ValueImpl::RawPtr"sv);
[[maybe_unused]] auto const& that = this->as.RawPtr;
builder.appendff("({})", that.value);
break;}
case 24 /* OptionalSome */: {
builder.append("ValueImpl::OptionalSome"sv);
[[maybe_unused]] auto const& that = this->as.OptionalSome;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("value: {}", that.value);
}
builder.append(")"sv);
break;}
case 25 /* OptionalNone */: {
return ByteString("ValueImpl::OptionalNone"sv);
break;}
case 26 /* JaktTuple */: {
builder.append("ValueImpl::JaktTuple"sv);
[[maybe_unused]] auto const& that = this->as.JaktTuple;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("fields: {}, ", that.fields);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", that.type_id);
}
builder.append(")"sv);
break;}
case 27 /* Function */: {
builder.append("ValueImpl::Function"sv);
[[maybe_unused]] auto const& that = this->as.Function;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("captures: {}, ", that.captures);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("params: {}, ", that.params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("return_type_id: {}, ", that.return_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", that.type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", that.block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("can_throw: {}, ", that.can_throw);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("checked_params: {}, ", that.checked_params);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope_id: {}, ", that.scope_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("pseudo_function_id: {}", that.pseudo_function_id);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Void(){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 1;
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Bool(bool value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->as.Bool.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::U8(u8 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->as.U8.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::U16(u16 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->as.U16.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::U32(u32 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->as.U32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::U64(u64 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->as.U64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::I8(i8 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->as.I8.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::I16(i16 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->as.I16.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::I32(i32 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->as.I32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::I64(i64 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->as.I64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::F32(f32 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->as.F32.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::F64(f64 value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->as.F64.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::USize(size_t value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->as.USize.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktString(ByteString value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->as.JaktString.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::StringView(ByteString value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->as.StringView.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::CChar(char value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 16;
new (&__jakt_uninit_enum->as.CChar.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::CInt(int value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 17;
new (&__jakt_uninit_enum->as.CInt.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Struct(JaktInternal::DynamicArray<Jakt::types::Value> fields, Jakt::ids::StructId struct_id, JaktInternal::Optional<Jakt::ids::FunctionId> constructor){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 18;
new (&__jakt_uninit_enum->as.Struct.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum->as.Struct.struct_id) (decltype(struct_id))(move(struct_id));
new (&__jakt_uninit_enum->as.Struct.constructor) (decltype(constructor))(move(constructor));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Class(JaktInternal::DynamicArray<Jakt::types::Value> fields, Jakt::ids::StructId struct_id, JaktInternal::Optional<Jakt::ids::FunctionId> constructor){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 19;
new (&__jakt_uninit_enum->as.Class.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum->as.Class.struct_id) (decltype(struct_id))(move(struct_id));
new (&__jakt_uninit_enum->as.Class.constructor) (decltype(constructor))(move(constructor));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Enum(JaktInternal::DynamicArray<Jakt::types::Value> fields, Jakt::ids::EnumId enum_id, Jakt::ids::FunctionId constructor){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 20;
new (&__jakt_uninit_enum->as.Enum.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum->as.Enum.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum->as.Enum.constructor) (decltype(constructor))(move(constructor));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktArray(JaktInternal::DynamicArray<Jakt::types::Value> values, Jakt::ids::TypeId type_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 21;
new (&__jakt_uninit_enum->as.JaktArray.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktArray.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktDictionary(JaktInternal::DynamicArray<Jakt::types::Value> keys, JaktInternal::DynamicArray<Jakt::types::Value> values, Jakt::ids::TypeId type_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 22;
new (&__jakt_uninit_enum->as.JaktDictionary.keys) (decltype(keys))(move(keys));
new (&__jakt_uninit_enum->as.JaktDictionary.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktDictionary.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktSet(JaktInternal::DynamicArray<Jakt::types::Value> values, Jakt::ids::TypeId type_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 23;
new (&__jakt_uninit_enum->as.JaktSet.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktSet.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::RawPtr(NonnullRefPtr<typename Jakt::types::ValueImpl> value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 24;
new (&__jakt_uninit_enum->as.RawPtr.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::OptionalSome(Jakt::types::Value value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 25;
new (&__jakt_uninit_enum->as.OptionalSome.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::OptionalNone(){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 26;
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktTuple(JaktInternal::DynamicArray<Jakt::types::Value> fields, Jakt::ids::TypeId type_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 27;
new (&__jakt_uninit_enum->as.JaktTuple.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum->as.JaktTuple.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Function(JaktInternal::Dictionary<ByteString,Jakt::types::Value> captures, JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>> params, Jakt::ids::TypeId return_type_id, Jakt::ids::TypeId type_id, Jakt::types::CheckedBlock block, bool can_throw, JaktInternal::DynamicArray<Jakt::types::CheckedParameter> checked_params, Jakt::ids::ScopeId scope_id, JaktInternal::Optional<Jakt::ids::FunctionId> pseudo_function_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 28;
new (&__jakt_uninit_enum->as.Function.captures) (decltype(captures))(move(captures));
new (&__jakt_uninit_enum->as.Function.params) (decltype(params))(move(params));
new (&__jakt_uninit_enum->as.Function.return_type_id) (decltype(return_type_id))(move(return_type_id));
new (&__jakt_uninit_enum->as.Function.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.Function.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Function.can_throw) (decltype(can_throw))(move(can_throw));
new (&__jakt_uninit_enum->as.Function.checked_params) (decltype(checked_params))(move(checked_params));
new (&__jakt_uninit_enum->as.Function.scope_id) (decltype(scope_id))(move(scope_id));
new (&__jakt_uninit_enum->as.Function.pseudo_function_id) (decltype(pseudo_function_id))(move(pseudo_function_id));
return __jakt_uninit_enum;
}
ValueImpl& ValueImpl::operator=(ValueImpl const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
new (&this->as.Bool.value) (decltype(this->as.Bool.value))(rhs.as.Bool.value);
break;
case 2 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(rhs.as.U8.value);
break;
case 3 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(rhs.as.U16.value);
break;
case 4 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(rhs.as.U32.value);
break;
case 5 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(rhs.as.U64.value);
break;
case 6 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(rhs.as.I8.value);
break;
case 7 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(rhs.as.I16.value);
break;
case 8 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(rhs.as.I32.value);
break;
case 9 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(rhs.as.I64.value);
break;
case 10 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(rhs.as.F32.value);
break;
case 11 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(rhs.as.F64.value);
break;
case 12 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(rhs.as.USize.value);
break;
case 13 /* JaktString */:
new (&this->as.JaktString.value) (decltype(this->as.JaktString.value))(rhs.as.JaktString.value);
break;
case 14 /* StringView */:
new (&this->as.StringView.value) (decltype(this->as.StringView.value))(rhs.as.StringView.value);
break;
case 15 /* CChar */:
new (&this->as.CChar.value) (decltype(this->as.CChar.value))(rhs.as.CChar.value);
break;
case 16 /* CInt */:
new (&this->as.CInt.value) (decltype(this->as.CInt.value))(rhs.as.CInt.value);
break;
case 17 /* Struct */:
new (&this->as.Struct.fields) (decltype(this->as.Struct.fields))(rhs.as.Struct.fields);
new (&this->as.Struct.struct_id) (decltype(this->as.Struct.struct_id))(rhs.as.Struct.struct_id);
new (&this->as.Struct.constructor) (decltype(this->as.Struct.constructor))(rhs.as.Struct.constructor);
break;
case 18 /* Class */:
new (&this->as.Class.fields) (decltype(this->as.Class.fields))(rhs.as.Class.fields);
new (&this->as.Class.struct_id) (decltype(this->as.Class.struct_id))(rhs.as.Class.struct_id);
new (&this->as.Class.constructor) (decltype(this->as.Class.constructor))(rhs.as.Class.constructor);
break;
case 19 /* Enum */:
new (&this->as.Enum.fields) (decltype(this->as.Enum.fields))(rhs.as.Enum.fields);
new (&this->as.Enum.enum_id) (decltype(this->as.Enum.enum_id))(rhs.as.Enum.enum_id);
new (&this->as.Enum.constructor) (decltype(this->as.Enum.constructor))(rhs.as.Enum.constructor);
break;
case 20 /* JaktArray */:
new (&this->as.JaktArray.values) (decltype(this->as.JaktArray.values))(rhs.as.JaktArray.values);
new (&this->as.JaktArray.type_id) (decltype(this->as.JaktArray.type_id))(rhs.as.JaktArray.type_id);
break;
case 21 /* JaktDictionary */:
new (&this->as.JaktDictionary.keys) (decltype(this->as.JaktDictionary.keys))(rhs.as.JaktDictionary.keys);
new (&this->as.JaktDictionary.values) (decltype(this->as.JaktDictionary.values))(rhs.as.JaktDictionary.values);
new (&this->as.JaktDictionary.type_id) (decltype(this->as.JaktDictionary.type_id))(rhs.as.JaktDictionary.type_id);
break;
case 22 /* JaktSet */:
new (&this->as.JaktSet.values) (decltype(this->as.JaktSet.values))(rhs.as.JaktSet.values);
new (&this->as.JaktSet.type_id) (decltype(this->as.JaktSet.type_id))(rhs.as.JaktSet.type_id);
break;
case 23 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(rhs.as.RawPtr.value);
break;
case 24 /* OptionalSome */:
new (&this->as.OptionalSome.value) (decltype(this->as.OptionalSome.value))(rhs.as.OptionalSome.value);
break;
case 25 /* OptionalNone */:
break;
case 26 /* JaktTuple */:
new (&this->as.JaktTuple.fields) (decltype(this->as.JaktTuple.fields))(rhs.as.JaktTuple.fields);
new (&this->as.JaktTuple.type_id) (decltype(this->as.JaktTuple.type_id))(rhs.as.JaktTuple.type_id);
break;
case 27 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(rhs.as.Function.captures);
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(rhs.as.Function.return_type_id);
new (&this->as.Function.type_id) (decltype(this->as.Function.type_id))(rhs.as.Function.type_id);
new (&this->as.Function.block) (decltype(this->as.Function.block))(rhs.as.Function.block);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.checked_params) (decltype(this->as.Function.checked_params))(rhs.as.Function.checked_params);
new (&this->as.Function.scope_id) (decltype(this->as.Function.scope_id))(rhs.as.Function.scope_id);
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(rhs.as.Function.pseudo_function_id);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
this->as.Bool.value = rhs.as.Bool.value;
break;
case 2 /* U8 */:
this->as.U8.value = rhs.as.U8.value;
break;
case 3 /* U16 */:
this->as.U16.value = rhs.as.U16.value;
break;
case 4 /* U32 */:
this->as.U32.value = rhs.as.U32.value;
break;
case 5 /* U64 */:
this->as.U64.value = rhs.as.U64.value;
break;
case 6 /* I8 */:
this->as.I8.value = rhs.as.I8.value;
break;
case 7 /* I16 */:
this->as.I16.value = rhs.as.I16.value;
break;
case 8 /* I32 */:
this->as.I32.value = rhs.as.I32.value;
break;
case 9 /* I64 */:
this->as.I64.value = rhs.as.I64.value;
break;
case 10 /* F32 */:
this->as.F32.value = rhs.as.F32.value;
break;
case 11 /* F64 */:
this->as.F64.value = rhs.as.F64.value;
break;
case 12 /* USize */:
this->as.USize.value = rhs.as.USize.value;
break;
case 13 /* JaktString */:
this->as.JaktString.value = rhs.as.JaktString.value;
break;
case 14 /* StringView */:
this->as.StringView.value = rhs.as.StringView.value;
break;
case 15 /* CChar */:
this->as.CChar.value = rhs.as.CChar.value;
break;
case 16 /* CInt */:
this->as.CInt.value = rhs.as.CInt.value;
break;
case 17 /* Struct */:
this->as.Struct.fields = rhs.as.Struct.fields;
this->as.Struct.struct_id = rhs.as.Struct.struct_id;
this->as.Struct.constructor = rhs.as.Struct.constructor;
break;
case 18 /* Class */:
this->as.Class.fields = rhs.as.Class.fields;
this->as.Class.struct_id = rhs.as.Class.struct_id;
this->as.Class.constructor = rhs.as.Class.constructor;
break;
case 19 /* Enum */:
this->as.Enum.fields = rhs.as.Enum.fields;
this->as.Enum.enum_id = rhs.as.Enum.enum_id;
this->as.Enum.constructor = rhs.as.Enum.constructor;
break;
case 20 /* JaktArray */:
this->as.JaktArray.values = rhs.as.JaktArray.values;
this->as.JaktArray.type_id = rhs.as.JaktArray.type_id;
break;
case 21 /* JaktDictionary */:
this->as.JaktDictionary.keys = rhs.as.JaktDictionary.keys;
this->as.JaktDictionary.values = rhs.as.JaktDictionary.values;
this->as.JaktDictionary.type_id = rhs.as.JaktDictionary.type_id;
break;
case 22 /* JaktSet */:
this->as.JaktSet.values = rhs.as.JaktSet.values;
this->as.JaktSet.type_id = rhs.as.JaktSet.type_id;
break;
case 23 /* RawPtr */:
this->as.RawPtr.value = rhs.as.RawPtr.value;
break;
case 24 /* OptionalSome */:
this->as.OptionalSome.value = rhs.as.OptionalSome.value;
break;
case 25 /* OptionalNone */:
break;
case 26 /* JaktTuple */:
this->as.JaktTuple.fields = rhs.as.JaktTuple.fields;
this->as.JaktTuple.type_id = rhs.as.JaktTuple.type_id;
break;
case 27 /* Function */:
this->as.Function.captures = rhs.as.Function.captures;
this->as.Function.params = rhs.as.Function.params;
this->as.Function.return_type_id = rhs.as.Function.return_type_id;
this->as.Function.type_id = rhs.as.Function.type_id;
this->as.Function.block = rhs.as.Function.block;
this->as.Function.can_throw = rhs.as.Function.can_throw;
this->as.Function.checked_params = rhs.as.Function.checked_params;
this->as.Function.scope_id = rhs.as.Function.scope_id;
this->as.Function.pseudo_function_id = rhs.as.Function.pseudo_function_id;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ValueImpl::ValueImpl(ValueImpl const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
new (&this->as.Bool.value) (decltype(this->as.Bool.value))(rhs.as.Bool.value);
break;
case 2 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(rhs.as.U8.value);
break;
case 3 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(rhs.as.U16.value);
break;
case 4 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(rhs.as.U32.value);
break;
case 5 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(rhs.as.U64.value);
break;
case 6 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(rhs.as.I8.value);
break;
case 7 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(rhs.as.I16.value);
break;
case 8 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(rhs.as.I32.value);
break;
case 9 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(rhs.as.I64.value);
break;
case 10 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(rhs.as.F32.value);
break;
case 11 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(rhs.as.F64.value);
break;
case 12 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(rhs.as.USize.value);
break;
case 13 /* JaktString */:
new (&this->as.JaktString.value) (decltype(this->as.JaktString.value))(rhs.as.JaktString.value);
break;
case 14 /* StringView */:
new (&this->as.StringView.value) (decltype(this->as.StringView.value))(rhs.as.StringView.value);
break;
case 15 /* CChar */:
new (&this->as.CChar.value) (decltype(this->as.CChar.value))(rhs.as.CChar.value);
break;
case 16 /* CInt */:
new (&this->as.CInt.value) (decltype(this->as.CInt.value))(rhs.as.CInt.value);
break;
case 17 /* Struct */:
new (&this->as.Struct.fields) (decltype(this->as.Struct.fields))(rhs.as.Struct.fields);
new (&this->as.Struct.struct_id) (decltype(this->as.Struct.struct_id))(rhs.as.Struct.struct_id);
new (&this->as.Struct.constructor) (decltype(this->as.Struct.constructor))(rhs.as.Struct.constructor);
break;
case 18 /* Class */:
new (&this->as.Class.fields) (decltype(this->as.Class.fields))(rhs.as.Class.fields);
new (&this->as.Class.struct_id) (decltype(this->as.Class.struct_id))(rhs.as.Class.struct_id);
new (&this->as.Class.constructor) (decltype(this->as.Class.constructor))(rhs.as.Class.constructor);
break;
case 19 /* Enum */:
new (&this->as.Enum.fields) (decltype(this->as.Enum.fields))(rhs.as.Enum.fields);
new (&this->as.Enum.enum_id) (decltype(this->as.Enum.enum_id))(rhs.as.Enum.enum_id);
new (&this->as.Enum.constructor) (decltype(this->as.Enum.constructor))(rhs.as.Enum.constructor);
break;
case 20 /* JaktArray */:
new (&this->as.JaktArray.values) (decltype(this->as.JaktArray.values))(rhs.as.JaktArray.values);
new (&this->as.JaktArray.type_id) (decltype(this->as.JaktArray.type_id))(rhs.as.JaktArray.type_id);
break;
case 21 /* JaktDictionary */:
new (&this->as.JaktDictionary.keys) (decltype(this->as.JaktDictionary.keys))(rhs.as.JaktDictionary.keys);
new (&this->as.JaktDictionary.values) (decltype(this->as.JaktDictionary.values))(rhs.as.JaktDictionary.values);
new (&this->as.JaktDictionary.type_id) (decltype(this->as.JaktDictionary.type_id))(rhs.as.JaktDictionary.type_id);
break;
case 22 /* JaktSet */:
new (&this->as.JaktSet.values) (decltype(this->as.JaktSet.values))(rhs.as.JaktSet.values);
new (&this->as.JaktSet.type_id) (decltype(this->as.JaktSet.type_id))(rhs.as.JaktSet.type_id);
break;
case 23 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(rhs.as.RawPtr.value);
break;
case 24 /* OptionalSome */:
new (&this->as.OptionalSome.value) (decltype(this->as.OptionalSome.value))(rhs.as.OptionalSome.value);
break;
case 25 /* OptionalNone */:
break;
case 26 /* JaktTuple */:
new (&this->as.JaktTuple.fields) (decltype(this->as.JaktTuple.fields))(rhs.as.JaktTuple.fields);
new (&this->as.JaktTuple.type_id) (decltype(this->as.JaktTuple.type_id))(rhs.as.JaktTuple.type_id);
break;
case 27 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(rhs.as.Function.captures);
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(rhs.as.Function.return_type_id);
new (&this->as.Function.type_id) (decltype(this->as.Function.type_id))(rhs.as.Function.type_id);
new (&this->as.Function.block) (decltype(this->as.Function.block))(rhs.as.Function.block);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.checked_params) (decltype(this->as.Function.checked_params))(rhs.as.Function.checked_params);
new (&this->as.Function.scope_id) (decltype(this->as.Function.scope_id))(rhs.as.Function.scope_id);
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(rhs.as.Function.pseudo_function_id);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ValueImpl& ValueImpl::operator=(ValueImpl &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
new (&this->as.Bool.value) (decltype(this->as.Bool.value))(move(rhs.as.Bool.value));
break;
case 2 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(move(rhs.as.U8.value));
break;
case 3 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(move(rhs.as.U16.value));
break;
case 4 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(move(rhs.as.U32.value));
break;
case 5 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(move(rhs.as.U64.value));
break;
case 6 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(move(rhs.as.I8.value));
break;
case 7 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(move(rhs.as.I16.value));
break;
case 8 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(move(rhs.as.I32.value));
break;
case 9 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(move(rhs.as.I64.value));
break;
case 10 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(move(rhs.as.F32.value));
break;
case 11 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(move(rhs.as.F64.value));
break;
case 12 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(move(rhs.as.USize.value));
break;
case 13 /* JaktString */:
new (&this->as.JaktString.value) (decltype(this->as.JaktString.value))(move(rhs.as.JaktString.value));
break;
case 14 /* StringView */:
new (&this->as.StringView.value) (decltype(this->as.StringView.value))(move(rhs.as.StringView.value));
break;
case 15 /* CChar */:
new (&this->as.CChar.value) (decltype(this->as.CChar.value))(move(rhs.as.CChar.value));
break;
case 16 /* CInt */:
new (&this->as.CInt.value) (decltype(this->as.CInt.value))(move(rhs.as.CInt.value));
break;
case 17 /* Struct */:
new (&this->as.Struct.fields) (decltype(this->as.Struct.fields))(move(rhs.as.Struct.fields));
new (&this->as.Struct.struct_id) (decltype(this->as.Struct.struct_id))(move(rhs.as.Struct.struct_id));
new (&this->as.Struct.constructor) (decltype(this->as.Struct.constructor))(move(rhs.as.Struct.constructor));
break;
case 18 /* Class */:
new (&this->as.Class.fields) (decltype(this->as.Class.fields))(move(rhs.as.Class.fields));
new (&this->as.Class.struct_id) (decltype(this->as.Class.struct_id))(move(rhs.as.Class.struct_id));
new (&this->as.Class.constructor) (decltype(this->as.Class.constructor))(move(rhs.as.Class.constructor));
break;
case 19 /* Enum */:
new (&this->as.Enum.fields) (decltype(this->as.Enum.fields))(move(rhs.as.Enum.fields));
new (&this->as.Enum.enum_id) (decltype(this->as.Enum.enum_id))(move(rhs.as.Enum.enum_id));
new (&this->as.Enum.constructor) (decltype(this->as.Enum.constructor))(move(rhs.as.Enum.constructor));
break;
case 20 /* JaktArray */:
new (&this->as.JaktArray.values) (decltype(this->as.JaktArray.values))(move(rhs.as.JaktArray.values));
new (&this->as.JaktArray.type_id) (decltype(this->as.JaktArray.type_id))(move(rhs.as.JaktArray.type_id));
break;
case 21 /* JaktDictionary */:
new (&this->as.JaktDictionary.keys) (decltype(this->as.JaktDictionary.keys))(move(rhs.as.JaktDictionary.keys));
new (&this->as.JaktDictionary.values) (decltype(this->as.JaktDictionary.values))(move(rhs.as.JaktDictionary.values));
new (&this->as.JaktDictionary.type_id) (decltype(this->as.JaktDictionary.type_id))(move(rhs.as.JaktDictionary.type_id));
break;
case 22 /* JaktSet */:
new (&this->as.JaktSet.values) (decltype(this->as.JaktSet.values))(move(rhs.as.JaktSet.values));
new (&this->as.JaktSet.type_id) (decltype(this->as.JaktSet.type_id))(move(rhs.as.JaktSet.type_id));
break;
case 23 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(move(rhs.as.RawPtr.value));
break;
case 24 /* OptionalSome */:
new (&this->as.OptionalSome.value) (decltype(this->as.OptionalSome.value))(move(rhs.as.OptionalSome.value));
break;
case 25 /* OptionalNone */:
break;
case 26 /* JaktTuple */:
new (&this->as.JaktTuple.fields) (decltype(this->as.JaktTuple.fields))(move(rhs.as.JaktTuple.fields));
new (&this->as.JaktTuple.type_id) (decltype(this->as.JaktTuple.type_id))(move(rhs.as.JaktTuple.type_id));
break;
case 27 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(move(rhs.as.Function.captures));
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(move(rhs.as.Function.return_type_id));
new (&this->as.Function.type_id) (decltype(this->as.Function.type_id))(move(rhs.as.Function.type_id));
new (&this->as.Function.block) (decltype(this->as.Function.block))(move(rhs.as.Function.block));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.checked_params) (decltype(this->as.Function.checked_params))(move(rhs.as.Function.checked_params));
new (&this->as.Function.scope_id) (decltype(this->as.Function.scope_id))(move(rhs.as.Function.scope_id));
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(move(rhs.as.Function.pseudo_function_id));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
this->as.Bool.value = move(rhs.as.Bool.value);
break;
case 2 /* U8 */:
this->as.U8.value = move(rhs.as.U8.value);
break;
case 3 /* U16 */:
this->as.U16.value = move(rhs.as.U16.value);
break;
case 4 /* U32 */:
this->as.U32.value = move(rhs.as.U32.value);
break;
case 5 /* U64 */:
this->as.U64.value = move(rhs.as.U64.value);
break;
case 6 /* I8 */:
this->as.I8.value = move(rhs.as.I8.value);
break;
case 7 /* I16 */:
this->as.I16.value = move(rhs.as.I16.value);
break;
case 8 /* I32 */:
this->as.I32.value = move(rhs.as.I32.value);
break;
case 9 /* I64 */:
this->as.I64.value = move(rhs.as.I64.value);
break;
case 10 /* F32 */:
this->as.F32.value = move(rhs.as.F32.value);
break;
case 11 /* F64 */:
this->as.F64.value = move(rhs.as.F64.value);
break;
case 12 /* USize */:
this->as.USize.value = move(rhs.as.USize.value);
break;
case 13 /* JaktString */:
this->as.JaktString.value = move(rhs.as.JaktString.value);
break;
case 14 /* StringView */:
this->as.StringView.value = move(rhs.as.StringView.value);
break;
case 15 /* CChar */:
this->as.CChar.value = move(rhs.as.CChar.value);
break;
case 16 /* CInt */:
this->as.CInt.value = move(rhs.as.CInt.value);
break;
case 17 /* Struct */:
this->as.Struct.fields = move(rhs.as.Struct.fields);
this->as.Struct.struct_id = move(rhs.as.Struct.struct_id);
this->as.Struct.constructor = move(rhs.as.Struct.constructor);
break;
case 18 /* Class */:
this->as.Class.fields = move(rhs.as.Class.fields);
this->as.Class.struct_id = move(rhs.as.Class.struct_id);
this->as.Class.constructor = move(rhs.as.Class.constructor);
break;
case 19 /* Enum */:
this->as.Enum.fields = move(rhs.as.Enum.fields);
this->as.Enum.enum_id = move(rhs.as.Enum.enum_id);
this->as.Enum.constructor = move(rhs.as.Enum.constructor);
break;
case 20 /* JaktArray */:
this->as.JaktArray.values = move(rhs.as.JaktArray.values);
this->as.JaktArray.type_id = move(rhs.as.JaktArray.type_id);
break;
case 21 /* JaktDictionary */:
this->as.JaktDictionary.keys = move(rhs.as.JaktDictionary.keys);
this->as.JaktDictionary.values = move(rhs.as.JaktDictionary.values);
this->as.JaktDictionary.type_id = move(rhs.as.JaktDictionary.type_id);
break;
case 22 /* JaktSet */:
this->as.JaktSet.values = move(rhs.as.JaktSet.values);
this->as.JaktSet.type_id = move(rhs.as.JaktSet.type_id);
break;
case 23 /* RawPtr */:
this->as.RawPtr.value = move(rhs.as.RawPtr.value);
break;
case 24 /* OptionalSome */:
this->as.OptionalSome.value = move(rhs.as.OptionalSome.value);
break;
case 25 /* OptionalNone */:
break;
case 26 /* JaktTuple */:
this->as.JaktTuple.fields = move(rhs.as.JaktTuple.fields);
this->as.JaktTuple.type_id = move(rhs.as.JaktTuple.type_id);
break;
case 27 /* Function */:
this->as.Function.captures = move(rhs.as.Function.captures);
this->as.Function.params = move(rhs.as.Function.params);
this->as.Function.return_type_id = move(rhs.as.Function.return_type_id);
this->as.Function.type_id = move(rhs.as.Function.type_id);
this->as.Function.block = move(rhs.as.Function.block);
this->as.Function.can_throw = move(rhs.as.Function.can_throw);
this->as.Function.checked_params = move(rhs.as.Function.checked_params);
this->as.Function.scope_id = move(rhs.as.Function.scope_id);
this->as.Function.pseudo_function_id = move(rhs.as.Function.pseudo_function_id);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ValueImpl::ValueImpl(ValueImpl &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Void */:
break;
case 1 /* Bool */:
new (&this->as.Bool.value) (decltype(this->as.Bool.value))(move(rhs.as.Bool.value));
break;
case 2 /* U8 */:
new (&this->as.U8.value) (decltype(this->as.U8.value))(move(rhs.as.U8.value));
break;
case 3 /* U16 */:
new (&this->as.U16.value) (decltype(this->as.U16.value))(move(rhs.as.U16.value));
break;
case 4 /* U32 */:
new (&this->as.U32.value) (decltype(this->as.U32.value))(move(rhs.as.U32.value));
break;
case 5 /* U64 */:
new (&this->as.U64.value) (decltype(this->as.U64.value))(move(rhs.as.U64.value));
break;
case 6 /* I8 */:
new (&this->as.I8.value) (decltype(this->as.I8.value))(move(rhs.as.I8.value));
break;
case 7 /* I16 */:
new (&this->as.I16.value) (decltype(this->as.I16.value))(move(rhs.as.I16.value));
break;
case 8 /* I32 */:
new (&this->as.I32.value) (decltype(this->as.I32.value))(move(rhs.as.I32.value));
break;
case 9 /* I64 */:
new (&this->as.I64.value) (decltype(this->as.I64.value))(move(rhs.as.I64.value));
break;
case 10 /* F32 */:
new (&this->as.F32.value) (decltype(this->as.F32.value))(move(rhs.as.F32.value));
break;
case 11 /* F64 */:
new (&this->as.F64.value) (decltype(this->as.F64.value))(move(rhs.as.F64.value));
break;
case 12 /* USize */:
new (&this->as.USize.value) (decltype(this->as.USize.value))(move(rhs.as.USize.value));
break;
case 13 /* JaktString */:
new (&this->as.JaktString.value) (decltype(this->as.JaktString.value))(move(rhs.as.JaktString.value));
break;
case 14 /* StringView */:
new (&this->as.StringView.value) (decltype(this->as.StringView.value))(move(rhs.as.StringView.value));
break;
case 15 /* CChar */:
new (&this->as.CChar.value) (decltype(this->as.CChar.value))(move(rhs.as.CChar.value));
break;
case 16 /* CInt */:
new (&this->as.CInt.value) (decltype(this->as.CInt.value))(move(rhs.as.CInt.value));
break;
case 17 /* Struct */:
new (&this->as.Struct.fields) (decltype(this->as.Struct.fields))(move(rhs.as.Struct.fields));
new (&this->as.Struct.struct_id) (decltype(this->as.Struct.struct_id))(move(rhs.as.Struct.struct_id));
new (&this->as.Struct.constructor) (decltype(this->as.Struct.constructor))(move(rhs.as.Struct.constructor));
break;
case 18 /* Class */:
new (&this->as.Class.fields) (decltype(this->as.Class.fields))(move(rhs.as.Class.fields));
new (&this->as.Class.struct_id) (decltype(this->as.Class.struct_id))(move(rhs.as.Class.struct_id));
new (&this->as.Class.constructor) (decltype(this->as.Class.constructor))(move(rhs.as.Class.constructor));
break;
case 19 /* Enum */:
new (&this->as.Enum.fields) (decltype(this->as.Enum.fields))(move(rhs.as.Enum.fields));
new (&this->as.Enum.enum_id) (decltype(this->as.Enum.enum_id))(move(rhs.as.Enum.enum_id));
new (&this->as.Enum.constructor) (decltype(this->as.Enum.constructor))(move(rhs.as.Enum.constructor));
break;
case 20 /* JaktArray */:
new (&this->as.JaktArray.values) (decltype(this->as.JaktArray.values))(move(rhs.as.JaktArray.values));
new (&this->as.JaktArray.type_id) (decltype(this->as.JaktArray.type_id))(move(rhs.as.JaktArray.type_id));
break;
case 21 /* JaktDictionary */:
new (&this->as.JaktDictionary.keys) (decltype(this->as.JaktDictionary.keys))(move(rhs.as.JaktDictionary.keys));
new (&this->as.JaktDictionary.values) (decltype(this->as.JaktDictionary.values))(move(rhs.as.JaktDictionary.values));
new (&this->as.JaktDictionary.type_id) (decltype(this->as.JaktDictionary.type_id))(move(rhs.as.JaktDictionary.type_id));
break;
case 22 /* JaktSet */:
new (&this->as.JaktSet.values) (decltype(this->as.JaktSet.values))(move(rhs.as.JaktSet.values));
new (&this->as.JaktSet.type_id) (decltype(this->as.JaktSet.type_id))(move(rhs.as.JaktSet.type_id));
break;
case 23 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(move(rhs.as.RawPtr.value));
break;
case 24 /* OptionalSome */:
new (&this->as.OptionalSome.value) (decltype(this->as.OptionalSome.value))(move(rhs.as.OptionalSome.value));
break;
case 25 /* OptionalNone */:
break;
case 26 /* JaktTuple */:
new (&this->as.JaktTuple.fields) (decltype(this->as.JaktTuple.fields))(move(rhs.as.JaktTuple.fields));
new (&this->as.JaktTuple.type_id) (decltype(this->as.JaktTuple.type_id))(move(rhs.as.JaktTuple.type_id));
break;
case 27 /* Function */:
new (&this->as.Function.captures) (decltype(this->as.Function.captures))(move(rhs.as.Function.captures));
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(move(rhs.as.Function.return_type_id));
new (&this->as.Function.type_id) (decltype(this->as.Function.type_id))(move(rhs.as.Function.type_id));
new (&this->as.Function.block) (decltype(this->as.Function.block))(move(rhs.as.Function.block));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.checked_params) (decltype(this->as.Function.checked_params))(move(rhs.as.Function.checked_params));
new (&this->as.Function.scope_id) (decltype(this->as.Function.scope_id))(move(rhs.as.Function.scope_id));
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(move(rhs.as.Function.pseudo_function_id));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ValueImpl::~ValueImpl(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ValueImpl::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Void */:break;
case 1 /* Bool */:break;
case 2 /* U8 */:break;
case 3 /* U16 */:break;
case 4 /* U32 */:break;
case 5 /* U64 */:break;
case 6 /* I8 */:break;
case 7 /* I16 */:break;
case 8 /* I32 */:break;
case 9 /* I64 */:break;
case 10 /* F32 */:break;
case 11 /* F64 */:break;
case 12 /* USize */:break;
case 13 /* JaktString */:this->as.JaktString.value.~ByteString();
break;
case 14 /* StringView */:this->as.StringView.value.~ByteString();
break;
case 15 /* CChar */:break;
case 16 /* CInt */:break;
case 17 /* Struct */:this->as.Struct.fields.~DynamicArray();
this->as.Struct.struct_id.~StructId();
this->as.Struct.constructor.~Optional();
break;
case 18 /* Class */:this->as.Class.fields.~DynamicArray();
this->as.Class.struct_id.~StructId();
this->as.Class.constructor.~Optional();
break;
case 19 /* Enum */:this->as.Enum.fields.~DynamicArray();
this->as.Enum.enum_id.~EnumId();
this->as.Enum.constructor.~FunctionId();
break;
case 20 /* JaktArray */:this->as.JaktArray.values.~DynamicArray();
this->as.JaktArray.type_id.~TypeId();
break;
case 21 /* JaktDictionary */:this->as.JaktDictionary.keys.~DynamicArray();
this->as.JaktDictionary.values.~DynamicArray();
this->as.JaktDictionary.type_id.~TypeId();
break;
case 22 /* JaktSet */:this->as.JaktSet.values.~DynamicArray();
this->as.JaktSet.type_id.~TypeId();
break;
case 23 /* RawPtr */:this->as.RawPtr.value.~NonnullRefPtr();
break;
case 24 /* OptionalSome */:this->as.OptionalSome.value.~Value();
break;
case 25 /* OptionalNone */:break;
case 26 /* JaktTuple */:this->as.JaktTuple.fields.~DynamicArray();
this->as.JaktTuple.type_id.~TypeId();
break;
case 27 /* Function */:this->as.Function.captures.~Dictionary();
this->as.Function.params.~Dictionary();
this->as.Function.return_type_id.~TypeId();
this->as.Function.type_id.~TypeId();
this->as.Function.block.~CheckedBlock();
this->as.Function.checked_params.~DynamicArray();
this->as.Function.scope_id.~ScopeId();
this->as.Function.pseudo_function_id.~Optional();
break;
}
}
ErrorOr<Jakt::ids::TypeId> Jakt::types::ValueImpl::type_id(NonnullRefPtr<Jakt::types::CheckedProgram>& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<Jakt::ids::TypeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(Jakt::types::void_type_id());
case 1 /* Bool */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Bool()));
case 2 /* U8 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U8()));
case 3 /* U16 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U16()));
case 4 /* U32 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U32()));
case 5 /* U64 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::U64()));
case 6 /* I8 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I8()));
case 7 /* I16 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I16()));
case 8 /* I32 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I32()));
case 9 /* I64 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::I64()));
case 10 /* F32 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::F32()));
case 11 /* F64 */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::F64()));
case 12 /* USize */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Usize()));
case 13 /* JaktString */:return JaktInternal::ExplicitValue(TRY((program->find_type_in_scope(program->prelude_scope_id(),ByteString::from_utf8_without_validation("String"sv),false,JaktInternal::OptionalNone()))).value());
case 14 /* StringView */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::JaktString()));
case 15 /* CChar */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::CChar()));
case 16 /* CInt */:return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::CInt()));
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue(program->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id),struct_id.module,false));
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue(program->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),struct_id),struct_id.module,false));
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(program->find_or_add_type_id(Jakt::types::Type::Enum(Jakt::parser::CheckedQualifiers(false),enum_id),enum_id.module,false));
};/*case end*/
default:{
Jakt::utility::panic(ByteString::from_utf8_without_validation("Reflected value type not implemented"sv));
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

NonnullRefPtr<typename Jakt::types::ValueImpl> Jakt::types::ValueImpl::copy() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, NonnullRefPtr<typename Jakt::types::ValueImpl>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Void());
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(x));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8(x));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16(x));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32(x));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64(x));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8(x));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16(x));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32(x));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64(x));
};/*case end*/
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F32(x));
};/*case end*/
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F64(x));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize(x));
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::JaktString(x));
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::StringView(x));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::CChar(x));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::CInt(x));
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
JaktInternal::DynamicArray<Jakt::types::Value> fields_copy = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value field = _magic_value.value();
{
fields_copy.push(field.copy());
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::ValueImpl>>(Jakt::types::ValueImpl::Struct(fields_copy,struct_id,constructor));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Class(fields,struct_id,constructor));
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
Jakt::ids::FunctionId const& constructor = __jakt_match_value.constructor;
{
JaktInternal::DynamicArray<Jakt::types::Value> fields_copy = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value field = _magic_value.value();
{
fields_copy.push(field.copy());
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::ValueImpl>>(Jakt::types::ValueImpl::Enum(fields_copy,enum_id,constructor));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::types::Value> values_copy = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = values.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value value = _magic_value.value();
{
values_copy.push(value.copy());
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::ValueImpl>>(Jakt::types::ValueImpl::JaktArray(values_copy,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::types::Value> values_copy = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = values.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value value = _magic_value.value();
{
values_copy.push(value.copy());
}

}
}

JaktInternal::DynamicArray<Jakt::types::Value> keys_copy = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = keys.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value key = _magic_value.value();
{
keys_copy.push(key.copy());
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::ValueImpl>>(Jakt::types::ValueImpl::JaktDictionary(keys_copy,values_copy,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::types::Value> values_copy = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = values.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value value = _magic_value.value();
{
values_copy.push(value.copy());
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::ValueImpl>>(Jakt::types::ValueImpl::JaktSet(values_copy,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 23 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;NonnullRefPtr<typename Jakt::types::ValueImpl> const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::RawPtr(value));
};/*case end*/
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::OptionalSome(value.copy()));
};/*case end*/
case 25 /* OptionalNone */:return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::OptionalNone());
case 26 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::types::Value> values_copy = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = fields.iterator();
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = _magic.next();
if (!_magic_value.has_value()){
break;
}
Jakt::types::Value value = _magic_value.value();
{
values_copy.push(value.copy());
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::ValueImpl>>(Jakt::types::ValueImpl::JaktTuple(values_copy,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 27 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::Dictionary<ByteString,Jakt::types::Value> const& captures = __jakt_match_value.captures;
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const& checked_params = __jakt_match_value.checked_params;
Jakt::ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Function(captures,params,return_type_id,type_id,block,can_throw,checked_params,scope_id,pseudo_function_id));
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

bool Jakt::types::ValueImpl::equals(NonnullRefPtr<typename Jakt::types::ValueImpl> const other) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */:return JaktInternal::ExplicitValue(other->__jakt_init_index() == 0 /* Void */);
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x == y);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x == y);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(y == x);
};/*case end*/
default:return JaktInternal::ExplicitValue(false);
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
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

ByteString Jakt::types::NumericOrStringValue::debug_description() const {
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
