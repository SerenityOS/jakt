#include "types.h"
namespace Jakt {
namespace types {
ids::TypeId unknown_type_id() {
{
return types::builtin(types::BuiltinType::Unknown());
}
}

ids::TypeId void_type_id() {
{
return types::builtin(types::BuiltinType::Void());
}
}

ids::TypeId never_type_id() {
{
return types::builtin(types::BuiltinType::Never());
}
}

ids::TypeId builtin(types::BuiltinType const builtin) {
{
return ids::TypeId(ids::ModuleId(static_cast<size_t>(0ULL)),((builtin).id()));
}
}

ErrorOr<ByteString> format_value_impl(ByteString const format_string,types::Value const value,NonnullRefPtr<types::CheckedProgram> const& program) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format(format_string,v));
};/*case end*/
case 0 /* Void */: {
return JaktInternal::ExplicitValue(__jakt_format(format_string,(ByteString::from_utf8_without_validation("(void)"sv))));
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_136; {
types::CheckedStruct const structure = ((((program)))->get_struct(struct_id));
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::DynamicArray<ByteString> field_names = DynamicArray<ByteString>::create_with({});
((builder).append(((structure).name)));
if (((constructor).has_value())){
NonnullRefPtr<types::CheckedFunction> const function = ((((program)))->get_function((constructor.value())));
((builder).append((StringView::from_string_literal("::"sv))));
((builder).append(((function)->name)));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter parameter = (_magic_value.value());
{
((field_names).push(((((parameter).variable))->name)));
}

}
}

}
else {
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
((field_names).push(((((((program)))->get_variable(((field).variable_id))))->name)));
}

}
}

}

((builder).append_code_point(static_cast<u32>(U'(')));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index,static_cast<size_t>(0ULL))){
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(((field_names)[index])));
((builder).append((StringView::from_string_literal(": "sv))));
((builder).append(TRY((types::format_value_impl(format_string,field,program)))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

((builder).append_code_point(static_cast<u32>(U')')));
__jakt_var_136 = ((builder).to_string()); goto __jakt_label_130;

}
__jakt_label_130:; __jakt_var_136.release_value(); }));
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_137; {
types::CheckedStruct const structure = ((((program)))->get_struct(struct_id));
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::DynamicArray<ByteString> field_names = DynamicArray<ByteString>::create_with({});
((builder).append(((structure).name)));
if (((constructor).has_value())){
NonnullRefPtr<types::CheckedFunction> const function = ((((program)))->get_function((constructor.value())));
((builder).append((StringView::from_string_literal("::"sv))));
((builder).append(((function)->name)));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter parameter = (_magic_value.value());
{
((field_names).push(((((parameter).variable))->name)));
}

}
}

}
else {
{
JaktInternal::ArrayIterator<types::CheckedField> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedField> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedField field = (_magic_value.value());
{
((field_names).push(((((((program)))->get_variable(((field).variable_id))))->name)));
}

}
}

}

((builder).append_code_point(static_cast<u32>(U'(')));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index,static_cast<size_t>(0ULL))){
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(((field_names)[index])));
((builder).append((StringView::from_string_literal(": "sv))));
((builder).append(TRY((types::format_value_impl(format_string,field,program)))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

((builder).append_code_point(static_cast<u32>(U')')));
__jakt_var_137 = ((builder).to_string()); goto __jakt_label_131;

}
__jakt_label_131:; __jakt_var_137.release_value(); }));
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
ids::FunctionId const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_138; {
types::CheckedEnum const enum_ = ((((program)))->get_enum(enum_id));
NonnullRefPtr<types::CheckedFunction> const function = ((((program)))->get_function(constructor));
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::DynamicArray<ByteString> field_names = DynamicArray<ByteString>::create_with({});
((builder).append(((enum_).name)));
((builder).append((StringView::from_string_literal("::"sv))));
((builder).append(((function)->name)));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter parameter = (_magic_value.value());
{
((field_names).push(((((parameter).variable))->name)));
}

}
}

((builder).append_code_point(static_cast<u32>(U'(')));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index,static_cast<size_t>(0ULL))){
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(((field_names)[index])));
((builder).append((StringView::from_string_literal(": "sv))));
((builder).append(TRY((types::format_value_impl(format_string,field,program)))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

((builder).append_code_point(static_cast<u32>(U')')));
__jakt_var_138 = ((builder).to_string()); goto __jakt_label_132;

}
__jakt_label_132:; __jakt_var_138.release_value(); }));
};/*case end*/
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::format_value_impl(__jakt_format((StringView::from_string_literal("Some({})"sv)),format_string),value,program))));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(__jakt_format(format_string,(ByteString::from_utf8_without_validation("None"sv))));
};/*case end*/
case 26 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_139; {
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* JaktTuple */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')}));
};/*case end*/
case 20 /* JaktArray */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')}));
};/*case end*/
case 22 /* JaktSet */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'{'), static_cast<u32>(U'}')}));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((builder).append_code_point(((surrounding).template get<0>())));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index,static_cast<size_t>(0ULL))){
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(TRY((types::format_value_impl(format_string,field,program)))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

((builder).append_code_point(((surrounding).template get<1>())));
__jakt_var_139 = ((builder).to_string()); goto __jakt_label_133;

}
__jakt_label_133:; __jakt_var_139.release_value(); }));
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_140; {
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* JaktTuple */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')}));
};/*case end*/
case 20 /* JaktArray */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')}));
};/*case end*/
case 22 /* JaktSet */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'{'), static_cast<u32>(U'}')}));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((builder).append_code_point(((surrounding).template get<0>())));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index,static_cast<size_t>(0ULL))){
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(TRY((types::format_value_impl(format_string,field,program)))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

((builder).append_code_point(((surrounding).template get<1>())));
__jakt_var_140 = ((builder).to_string()); goto __jakt_label_134;

}
__jakt_label_134:; __jakt_var_140.release_value(); }));
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_141; {
ByteStringBuilder builder = ByteStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 26 /* JaktTuple */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')}));
};/*case end*/
case 20 /* JaktArray */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')}));
};/*case end*/
case 22 /* JaktSet */: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'{'), static_cast<u32>(U'}')}));
};/*case end*/
default: {
{
abort();
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((builder).append_code_point(((surrounding).template get<0>())));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index,static_cast<size_t>(0ULL))){
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(TRY((types::format_value_impl(format_string,field,program)))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

((builder).append_code_point(((surrounding).template get<1>())));
__jakt_var_141 = ((builder).to_string()); goto __jakt_label_135;

}
__jakt_label_135:; __jakt_var_141.release_value(); }));
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_142; {
ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append_code_point(static_cast<u32>(U'[')));
size_t index = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<types::Value> _magic = ((keys).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value key = (_magic_value.value());
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index,static_cast<size_t>(0ULL))){
((builder).append((StringView::from_string_literal(", "sv))));
}
((builder).append(TRY((types::format_value_impl(format_string,key,program)))));
((builder).append((StringView::from_string_literal(": "sv))));
((builder).append(TRY((types::format_value_impl(format_string,((values)[index]),program)))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

((builder).append_code_point(static_cast<u32>(U']')));
__jakt_var_142 = ((builder).to_string()); goto __jakt_label_136;

}
__jakt_label_136:; __jakt_var_142.release_value(); }));
};/*case end*/
default: {
{
warnln((StringView::from_string_literal("Cannot format value {}"sv)),((value).impl));
return Error::__jakt_from_string_literal((StringView::from_string_literal("Cannot format value of this type"sv)));
}
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

ErrorOr<ByteString> comptime_format_impl(ByteString const format_string,JaktInternal::ArraySlice<types::Value> const arguments,NonnullRefPtr<types::CheckedProgram> const& program) {
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
DeprecatedStringCodePointIterator _magic = ((str).code_points());
for (;;){
JaktInternal::Optional<u32> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u32 code_point = (_magic_value.value());
{
if (([](u32 const& self, u32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(code_point,static_cast<u32>(U'0')) && [](u32 const& self, u32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(code_point,static_cast<u32>(U'9')))){
((slice_end) += (static_cast<size_t>(1ULL)));
(has_index = true);
}
else {
break;
}

}

}
}

if (has_index){
ByteString const index_str = ((str).substring(static_cast<size_t>(0ULL),slice_end));
JaktInternal::Optional<u32> const index = ((index_str).template to_number<u32>());
if (((index).has_value())){
return (Tuple{static_cast<JaktInternal::Optional<size_t>>((infallible_integer_cast<size_t>(((index.value()))))), ((str).substring(slice_end,JaktInternal::checked_sub(((str).length()),slice_end)))});
}
}
return (Tuple{static_cast<JaktInternal::Optional<size_t>>(JaktInternal::OptionalNone()), str});
}
}
;
{
DeprecatedStringCodePointIterator _magic = ((format_string).code_points());
for (;;){
JaktInternal::Optional<u32> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u32 code_point = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<ByteString>> {
auto __jakt_enum_value = (code_point);
if (__jakt_enum_value == static_cast<u32>(U'{')) {
{
if ((((index_in_field).has_value()) && (((index_in_field.value())) == (static_cast<size_t>(0ULL))))){
((builder).append_code_point(static_cast<u32>(U'{')));
(index_in_field = JaktInternal::OptionalNone());
}
else if (((index_in_field).has_value())){
((format_field_builder).append_code_point(static_cast<u32>(U'{')));
(index_in_field = JaktInternal::checked_add((index_in_field.value()),static_cast<size_t>(1ULL)));
}
else {
(index_in_field = static_cast<size_t>(0ULL));
}

}
return JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == static_cast<u32>(U'}')) {
{
if (expect_close_brace){
((builder).append_code_point(static_cast<u32>(U'}')));
(expect_close_brace = false);
}
else if ((!(((index_in_field).has_value())))){
(expect_close_brace = true);
}
else {
(index_in_field = JaktInternal::OptionalNone());
ByteString const fmt_string = ((format_field_builder).to_string());
((format_field_builder).clear());
JaktInternal::Tuple<JaktInternal::Optional<size_t>,ByteString> const index_format_string_ = argument_and_index(fmt_string);
JaktInternal::Optional<size_t> const index = ((index_format_string_).template get<0>());
ByteString const format_string = ((index_format_string_).template get<1>());

size_t const effective_index = index.value_or_lazy_evaluated([&] { return ((current_argument_index++)); });
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(effective_index,((arguments).size()))){
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not enough arguments for format string"sv)));
}
ByteString const effective_format_string = __jakt_format((StringView::from_string_literal("{{{}}}"sv)),format_string);
((builder).append(TRY((types::format_value_impl(effective_format_string,((arguments)[effective_index]),program)))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
if (((index_in_field).has_value())){
((format_field_builder).append_code_point(code_point));
}
else {
((builder).append_code_point(code_point));
}

}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
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

return ((builder).to_string());
}
}

ByteString types::GenericInferences::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("GenericInferences("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("values: {}", values);
}
builder.append(")"sv);return builder.to_string(); }
void types::GenericInferences::set(ids::TypeId const key,ids::TypeId const value) {
{
if (((key).equals(value))){
return;
}
ids::TypeId const mapped_value = ((*this).map(value));
if (((key).equals(mapped_value))){
return;
}
((*this).values).set(key, mapped_value);
}
}

void types::GenericInferences::set_all(JaktInternal::DynamicArray<types::CheckedGenericParameter> const keys,JaktInternal::DynamicArray<ids::TypeId> const values) {
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
ids::TypeId const key = ((((keys)[i])).type_id);
ids::TypeId const value = ((values)[i]);
((*this).set(key,value));
}

}
}

}
}

JaktInternal::Optional<ids::TypeId> types::GenericInferences::get(ids::TypeId const key) const {
{
return ((((*this).values)).get(key));
}
}

ids::TypeId types::GenericInferences::map(ids::TypeId const type) const {
{
JaktInternal::Optional<ids::TypeId> mapped = ((((*this).values)).get(type));
JaktInternal::Optional<ids::TypeId> final_mapped_result = mapped;
while (((mapped).has_value())){
(final_mapped_result = mapped);
(mapped = ((((*this).values)).get((mapped.value()))));
}
return final_mapped_result.value_or_lazy_evaluated([&] { return type; });
}
}

JaktInternal::Optional<ids::TypeId> types::GenericInferences::find_and_map(ByteString const name,NonnullRefPtr<types::CheckedProgram> const& program) const {
{
{
JaktInternal::DictionaryIterator<ids::TypeId,ids::TypeId> _magic = ((((*this).values)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ids::TypeId,ids::TypeId> type_id__v__ = (_magic_value.value());
{
JaktInternal::Tuple<ids::TypeId,ids::TypeId> const jakt__type_id__v__ = type_id__v__;
ids::TypeId const type_id = ((jakt__type_id__v__).template get<0>());
ids::TypeId const v = ((jakt__type_id__v__).template get<1>());

if (((((((program)))->get_type(type_id)))->__jakt_init_index() == 18 /* TypeVariable */)){
ByteString const var_name = (((((program)))->get_type(type_id)))->as.TypeVariable.name;
if (((var_name) == (name))){
return ((*this).map(v));
}
}
}

}
}

return JaktInternal::OptionalNone();
}
}

JaktInternal::Dictionary<ids::TypeId,ids::TypeId> types::GenericInferences::iterator() const {
{
return ((*this).values);
}
}

JaktInternal::Dictionary<ids::TypeId,ids::TypeId> types::GenericInferences::perform_checkpoint(bool const reset) {
{
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const result = ((*this).values);
(((*this).values) = Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({}));
if ((!(reset))){
{
JaktInternal::DictionaryIterator<ids::TypeId,ids::TypeId> _magic = ((result).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ids::TypeId,ids::TypeId> key__value__ = (_magic_value.value());
{
JaktInternal::Tuple<ids::TypeId,ids::TypeId> const jakt__key__value__ = key__value__;
ids::TypeId const key = ((jakt__key__value__).template get<0>());
ids::TypeId const value = ((jakt__key__value__).template get<1>());

((*this).values).set(key, value);
}

}
}

}
return result;
}
}

void types::GenericInferences::restore(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const checkpoint) {
{
(((*this).values) = checkpoint);
}
}

void types::GenericInferences::set_from(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const checkpoint) {
{
{
JaktInternal::DictionaryIterator<ids::TypeId,ids::TypeId> _magic = ((checkpoint).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ids::TypeId,ids::TypeId> key__value__ = (_magic_value.value());
{
JaktInternal::Tuple<ids::TypeId,ids::TypeId> const jakt__key__value__ = key__value__;
ids::TypeId const key = ((jakt__key__value__).template get<0>());
ids::TypeId const value = ((jakt__key__value__).template get<1>());

((*this).set(key,value));
}

}
}

}
}

ErrorOr<void> types::GenericInferences::debug_description(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
warnln((StringView::from_string_literal("Generic inferences:"sv)));
{
JaktInternal::DictionaryIterator<ids::TypeId,ids::TypeId> _magic = ((((*this).values)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ids::TypeId,ids::TypeId> key__value__ = (_magic_value.value());
{
JaktInternal::Tuple<ids::TypeId,ids::TypeId> const jakt__key__value__ = key__value__;
ids::TypeId const key = ((jakt__key__value__).template get<0>());
ids::TypeId const value = ((jakt__key__value__).template get<1>());

warnln((StringView::from_string_literal("  {} => {}"sv)),TRY((((((program)))->type_name(key,true)))),TRY((((((program)))->type_name(value,true)))));
}

}
}

}
return {};
}

types::GenericInferences::GenericInferences(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> a_values): values(move(a_values)){}

ByteString types::SpecializedType::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("SpecializedType("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("base_type_id: {}, ", base_type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("arguments: {}, ", arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}", type_id);
}
builder.append(")"sv);return builder.to_string(); }
types::SpecializedType::SpecializedType(ids::TypeId a_base_type_id, JaktInternal::DynamicArray<ids::TypeId> a_arguments, ids::TypeId a_type_id): base_type_id(move(a_base_type_id)), arguments(move(a_arguments)), type_id(move(a_type_id)){}

ByteString types::ResolutionMixin::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ResolutionMixin("sv);{
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
types::ResolutionMixin::ResolutionMixin(ids::ScopeId a_scope_id, bool a_mixin_vars, bool a_mixin_bindings, bool a_mixin_structs, bool a_mixin_functions, bool a_mixin_enums, bool a_mixin_types, bool a_mixin_traits, bool a_mixin_imports, bool a_mixin_aliases): scope_id(move(a_scope_id)), mixin_vars(move(a_mixin_vars)), mixin_bindings(move(a_mixin_bindings)), mixin_structs(move(a_mixin_structs)), mixin_functions(move(a_mixin_functions)), mixin_enums(move(a_mixin_enums)), mixin_types(move(a_mixin_types)), mixin_traits(move(a_mixin_traits)), mixin_imports(move(a_mixin_imports)), mixin_aliases(move(a_mixin_aliases)){}

ByteString types::Scope::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Scope("sv);{
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
JaktInternal::Optional<parser::ExternalName> types::Scope::namespace_name_for_codegen() const {
{
if (((((*this).external_name)).has_value())){
return ((*this).external_name);
}
if (((((*this).namespace_name)).has_value())){
return parser::ExternalName::Plain((((*this).namespace_name).value()));
}
return JaktInternal::OptionalNone();
}
}

types::Scope::Scope(JaktInternal::Optional<ids::ScopeId> a_parent, bool a_can_throw, ByteString a_debug_name, bool a_is_block_scope, bool a_is_from_generated_code, JaktInternal::Optional<ByteString> a_namespace_name, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Dictionary<ByteString,ids::VarId> a_vars, JaktInternal::Dictionary<ByteString,types::Value> a_comptime_bindings, JaktInternal::Dictionary<ByteString,ids::StructId> a_structs, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> a_functions, JaktInternal::Dictionary<ByteString,ids::EnumId> a_enums, JaktInternal::Dictionary<ByteString,ids::TypeId> a_types, JaktInternal::Dictionary<ByteString,ids::TraitId> a_traits, JaktInternal::Dictionary<ByteString,ids::ModuleId> a_imports, JaktInternal::Dictionary<ByteString,ids::ScopeId> a_aliases, JaktInternal::Optional<ids::ScopeId> a_alias_scope, JaktInternal::DynamicArray<ids::ScopeId> a_children, JaktInternal::Optional<ByteString> a_import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> a_alias_path, JaktInternal::DynamicArray<parser::IncludeAction> a_after_extern_include, JaktInternal::DynamicArray<parser::IncludeAction> a_before_extern_include, JaktInternal::DynamicArray<types::ResolutionMixin> a_resolution_mixins, JaktInternal::Optional<ids::TypeId> a_relevant_type_id, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> a_resolved_forall_chunks, JaktInternal::Dictionary<ByteString,types::SpecializedType> a_explicitly_specialized_types): parent(move(a_parent)), can_throw(move(a_can_throw)), debug_name(move(a_debug_name)), is_block_scope(move(a_is_block_scope)), is_from_generated_code(move(a_is_from_generated_code)), namespace_name(move(a_namespace_name)), external_name(move(a_external_name)), vars(move(a_vars)), comptime_bindings(move(a_comptime_bindings)), structs(move(a_structs)), functions(move(a_functions)), enums(move(a_enums)), types(move(a_types)), traits(move(a_traits)), imports(move(a_imports)), aliases(move(a_aliases)), alias_scope(move(a_alias_scope)), children(move(a_children)), import_path_if_extern(move(a_import_path_if_extern)), alias_path(move(a_alias_path)), after_extern_include(move(a_after_extern_include)), before_extern_include(move(a_before_extern_include)), resolution_mixins(move(a_resolution_mixins)), relevant_type_id(move(a_relevant_type_id)), resolved_forall_chunks(move(a_resolved_forall_chunks)), explicitly_specialized_types(move(a_explicitly_specialized_types)){}
NonnullRefPtr<Scope> types::Scope::__jakt_create(JaktInternal::Optional<ids::ScopeId> parent, bool can_throw, ByteString debug_name, bool is_block_scope, bool is_from_generated_code, JaktInternal::Optional<ByteString> namespace_name, JaktInternal::Optional<parser::ExternalName> external_name, JaktInternal::Dictionary<ByteString,ids::VarId> vars, JaktInternal::Dictionary<ByteString,types::Value> comptime_bindings, JaktInternal::Dictionary<ByteString,ids::StructId> structs, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<ids::FunctionId>> functions, JaktInternal::Dictionary<ByteString,ids::EnumId> enums, JaktInternal::Dictionary<ByteString,ids::TypeId> types, JaktInternal::Dictionary<ByteString,ids::TraitId> traits, JaktInternal::Dictionary<ByteString,ids::ModuleId> imports, JaktInternal::Dictionary<ByteString,ids::ScopeId> aliases, JaktInternal::Optional<ids::ScopeId> alias_scope, JaktInternal::DynamicArray<ids::ScopeId> children, JaktInternal::Optional<ByteString> import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> alias_path, JaktInternal::DynamicArray<parser::IncludeAction> after_extern_include, JaktInternal::DynamicArray<parser::IncludeAction> before_extern_include, JaktInternal::DynamicArray<types::ResolutionMixin> resolution_mixins, JaktInternal::Optional<ids::TypeId> relevant_type_id, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> resolved_forall_chunks, JaktInternal::Dictionary<ByteString,types::SpecializedType> explicitly_specialized_types) { auto o = adopt_ref(*new Scope (move(parent), move(can_throw), move(debug_name), move(is_block_scope), move(is_from_generated_code), move(namespace_name), move(external_name), move(vars), move(comptime_bindings), move(structs), move(functions), move(enums), move(types), move(traits), move(imports), move(aliases), move(alias_scope), move(children), move(import_path_if_extern), move(alias_path), move(after_extern_include), move(before_extern_include), move(resolution_mixins), move(relevant_type_id), move(resolved_forall_chunks), move(explicitly_specialized_types))); return o; }
ByteString types::ResolvedForallChunk::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ResolvedForallChunk("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parameters: {}, ", parameters);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parsed_namespace: {}, ", parsed_namespace);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generated_scopes: {}", generated_scopes);
}
builder.append(")"sv);return builder.to_string(); }
types::ResolvedForallChunk::ResolvedForallChunk(JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> a_parameters, parser::ParsedNamespace a_parsed_namespace, JaktInternal::DynamicArray<ids::ScopeId> a_generated_scopes): parameters(move(a_parameters)), parsed_namespace(move(a_parsed_namespace)), generated_scopes(move(a_generated_scopes)){}

ByteString types::Module::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Module("sv);{
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
bool types::Module::is_prelude() const {
{
return ((((((*this).id)).id)) == (static_cast<size_t>(0ULL)));
}
}

ids::TypeId types::Module::new_type_variable(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const implemented_traits) {
{
size_t const new_id = ((((*this).types)).size());
JaktInternal::DynamicArray<ids::TypeId> const empty_implementation = DynamicArray<ids::TypeId>::create_with({});
JaktInternal::DynamicArray<ids::TypeId> const trait_implementations = implemented_traits.value_or_lazy_evaluated([&] { return empty_implementation; });
((((*this).types)).push(types::Type::TypeVariable(parser::CheckedQualifiers(false),__jakt_format((StringView::from_string_literal("T{}"sv)),new_id),trait_implementations,false)));
return ids::TypeId(((*this).id),new_id);
}
}

ids::FunctionId types::Module::next_function_id() const {
{
return ids::FunctionId(((*this).id),((((*this).functions)).size()));
}
}

ids::FunctionId types::Module::add_function(NonnullRefPtr<types::CheckedFunction> const checked_function) {
{
ids::FunctionId const new_id = ((*this).next_function_id());
((((*this).functions)).push(checked_function));
return new_id;
}
}

ids::VarId types::Module::add_variable(NonnullRefPtr<types::CheckedVariable> const checked_variable) {
{
size_t const new_id = ((((*this).variables)).size());
((((*this).variables)).push(checked_variable));
return ids::VarId(((*this).id),new_id);
}
}

types::Module::Module(ids::ModuleId a_id, ByteString a_name, JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> a_types, ByteString a_resolved_import_path, bool a_is_root, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> a_functions, JaktInternal::DynamicArray<types::CheckedStruct> a_structures, JaktInternal::DynamicArray<types::CheckedEnum> a_enums, JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> a_scopes, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> a_traits, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> a_variables, JaktInternal::DynamicArray<ids::ModuleId> a_imports, JaktInternal::Dictionary<size_t,ids::StructId> a_builtin_implementation_structs): id(move(a_id)), name(move(a_name)), types(move(a_types)), resolved_import_path(move(a_resolved_import_path)), is_root(move(a_is_root)), functions(move(a_functions)), structures(move(a_structures)), enums(move(a_enums)), scopes(move(a_scopes)), traits(move(a_traits)), variables(move(a_variables)), imports(move(a_imports)), builtin_implementation_structs(move(a_builtin_implementation_structs)){}
NonnullRefPtr<Module> types::Module::__jakt_create(ids::ModuleId id, ByteString name, JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> types, ByteString resolved_import_path, bool is_root, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> functions, JaktInternal::DynamicArray<types::CheckedStruct> structures, JaktInternal::DynamicArray<types::CheckedEnum> enums, JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> scopes, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> traits, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> variables, JaktInternal::DynamicArray<ids::ModuleId> imports, JaktInternal::Dictionary<size_t,ids::StructId> builtin_implementation_structs) { auto o = adopt_ref(*new Module (move(id), move(name), move(types), move(resolved_import_path), move(is_root), move(functions), move(structures), move(enums), move(scopes), move(traits), move(variables), move(imports), move(builtin_implementation_structs))); return o; }
ByteString types::CheckedTrait::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedTrait("sv);{
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
types::CheckedTrait::CheckedTrait(ByteString a_name, utility::Span a_name_span, types::CheckedTraitRequirements a_requirements, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, ids::ScopeId a_scope_id): name(move(a_name)), name_span(move(a_name_span)), requirements(move(a_requirements)), generic_parameters(move(a_generic_parameters)), scope_id(move(a_scope_id)){}
NonnullRefPtr<CheckedTrait> types::CheckedTrait::__jakt_create(ByteString name, utility::Span name_span, types::CheckedTraitRequirements requirements, JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters, ids::ScopeId scope_id) { auto o = adopt_ref(*new CheckedTrait (move(name), move(name_span), move(requirements), move(generic_parameters), move(scope_id))); return o; }
ByteString types::LoadedModule::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("LoadedModule("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("module_id: {}, ", module_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("file_id: {}", file_id);
}
builder.append(")"sv);return builder.to_string(); }
types::LoadedModule::LoadedModule(ids::ModuleId a_module_id, utility::FileId a_file_id): module_id(move(a_module_id)), file_id(move(a_file_id)){}

ByteString types::CheckedNamespace::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedNamespace("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("scope: {}", scope);
}
builder.append(")"sv);return builder.to_string(); }
types::CheckedNamespace::CheckedNamespace(ByteString a_name, ids::ScopeId a_scope): name(move(a_name)), scope(move(a_scope)){}

ByteString types::CheckedFunction::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedFunction("sv);{
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
builder.appendff("force_inline: {}", force_inline);
}
builder.append(")"sv);return builder.to_string(); }
parser::ExternalName types::CheckedFunction::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return parser::ExternalName::Plain(((*this).name)); });
}
}

ErrorOr<void> types::CheckedFunction::map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) {
{
(((*this).return_type_id) = TRY((map(((*this).return_type_id)))));
JaktInternal::DynamicArray<types::CheckedParameter> changed_params = DynamicArray<types::CheckedParameter>::create_with({});
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((*this).params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
((changed_params).push(TRY((((param).map_types(map))))));
}

}
}

(((*this).params) = changed_params);
}
return {};
}

NonnullRefPtr<types::CheckedFunction> types::CheckedFunction::copy() const {
{
return types::CheckedFunction::__jakt_create(((*this).name),((*this).name_span),((*this).visibility),((*this).return_type_id),((*this).return_type_span),((*this).params),((*this).generics),((*this).block),((*this).can_throw),((*this).type),((*this).linkage),((*this).function_scope_id),((*this).struct_id),((*this).is_instantiated),((*this).parsed_function),((*this).is_comptime),((*this).is_virtual),((*this).is_override),((*this).is_unsafe),((*this).has_varargs),((*this).specialization_index),((*this).owner_scope),((*this).owner_scope_generics),((*this).is_fully_checked),((*this).external_name),((*this).deprecated_message),((*this).stores_arguments),parser::InlineState::Default());
}
}

bool types::CheckedFunction::signature_matches(NonnullRefPtr<types::CheckedFunction> const other,bool const ignore_this) const {
{
if (((([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((*this).name),((other)->name)) || ((((*this).can_throw)) != (((other)->can_throw)))) || ((((*this).is_comptime)) != (((other)->is_comptime)))) || ((((*this).has_varargs)) != (((other)->has_varargs))))){
return false;
}
if (((((((*this).params)).size())) != (((((other)->params)).size())))){
return false;
}
if (((((((((*this).generics))->params)).size())) != (((((((other)->generics))->params)).size())))){
return false;
}
JaktInternal::Set<ids::TypeId> lhs_generic_type_ids = Set<ids::TypeId>::create_with_values({});
JaktInternal::Set<ids::TypeId> rhs_generic_type_ids = Set<ids::TypeId>::create_with_values({});
{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((((((*this).generics))->params)).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter param = (_magic_value.value());
{
ids::TypeId const type_id = ((param).type_id());
((lhs_generic_type_ids).add(type_id));
}

}
}

{
JaktInternal::ArrayIterator<types::FunctionGenericParameter> _magic = ((((((other)->generics))->params)).iterator());
for (;;){
JaktInternal::Optional<types::FunctionGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::FunctionGenericParameter param = (_magic_value.value());
{
ids::TypeId const type_id = ((param).type_id());
((rhs_generic_type_ids).add(type_id));
}

}
}

{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((*this).params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t param_index = (_magic_value.value());
{
types::CheckedParameter const lhs_param = ((((*this).params))[param_index]);
types::CheckedParameter const rhs_param = ((((other)->params))[param_index]);
ids::TypeId const lhs_param_id = ((((lhs_param).variable))->type_id);
ids::TypeId const rhs_param_id = ((((rhs_param).variable))->type_id);
if (((!(((((((lhs_param).variable))->type_id)).equals(((((rhs_param).variable))->type_id))))) && (!((((lhs_generic_type_ids).contains(lhs_param_id)) && ((rhs_generic_type_ids).contains(rhs_param_id))))))){
return false;
}
}

}
}

return true;
}
}

bool types::CheckedFunction::is_static() const {
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((((*this).params)).size()),static_cast<size_t>(1ULL))){
return true;
}
return [](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((((((((*this).params))[static_cast<i64>(0LL)])).variable))->name),(ByteString::from_utf8_without_validation("this"sv)));
}
}

bool types::CheckedFunction::is_mutating() const {
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((((*this).params)).size()),static_cast<size_t>(1ULL))){
return false;
}
NonnullRefPtr<types::CheckedVariable> const first_param_variable = ((((((*this).params))[static_cast<i64>(0LL)])).variable);
return (((((first_param_variable)->name)) == ((ByteString::from_utf8_without_validation("this"sv)))) && ((first_param_variable)->is_mutable));
}
}

void types::CheckedFunction::add_param(types::CheckedParameter const checked_param) {
{
((((*this).params)).push(checked_param));
((((((*this).generics))->base_params)).push(checked_param));
}
}

void types::CheckedFunction::set_params(JaktInternal::DynamicArray<types::CheckedParameter> const checked_params) {
{
(((*this).params) = checked_params);
(((((*this).generics))->base_params) = checked_params);
}
}

bool types::CheckedFunction::is_specialized_for_types(JaktInternal::DynamicArray<ids::TypeId> const types) const {
{
return ((((*this).generics))->is_specialized_for_types(types));
}
}

parser::ParsedFunction types::CheckedFunction::to_parsed_function() const {
{
if ((!(((((*this).parsed_function)).has_value())))){
utility::panic((ByteString::from_utf8_without_validation("to_parsed_function() called on a synthetic function"sv)));
}
return (((*this).parsed_function).value());
}
}

types::CheckedFunction::CheckedFunction(ByteString a_name, utility::Span a_name_span, types::CheckedVisibility a_visibility, ids::TypeId a_return_type_id, JaktInternal::Optional<utility::Span> a_return_type_span, JaktInternal::DynamicArray<types::CheckedParameter> a_params, NonnullRefPtr<types::FunctionGenerics> a_generics, types::CheckedBlock a_block, bool a_can_throw, parser::FunctionType a_type, parser::FunctionLinkage a_linkage, ids::ScopeId a_function_scope_id, JaktInternal::Optional<ids::StructId> a_struct_id, bool a_is_instantiated, JaktInternal::Optional<parser::ParsedFunction> a_parsed_function, bool a_is_comptime, bool a_is_virtual, bool a_is_override, bool a_is_unsafe, bool a_has_varargs, JaktInternal::Optional<size_t> a_specialization_index, JaktInternal::Optional<ids::ScopeId> a_owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> a_owner_scope_generics, bool a_is_fully_checked, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<ByteString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> a_stores_arguments, parser::InlineState a_force_inline): name(move(a_name)), name_span(move(a_name_span)), visibility(move(a_visibility)), return_type_id(move(a_return_type_id)), return_type_span(move(a_return_type_span)), params(move(a_params)), generics(move(a_generics)), block(move(a_block)), can_throw(move(a_can_throw)), type(move(a_type)), linkage(move(a_linkage)), function_scope_id(move(a_function_scope_id)), struct_id(move(a_struct_id)), is_instantiated(move(a_is_instantiated)), parsed_function(move(a_parsed_function)), is_comptime(move(a_is_comptime)), is_virtual(move(a_is_virtual)), is_override(move(a_is_override)), is_unsafe(move(a_is_unsafe)), has_varargs(move(a_has_varargs)), specialization_index(move(a_specialization_index)), owner_scope(move(a_owner_scope)), owner_scope_generics(move(a_owner_scope_generics)), is_fully_checked(move(a_is_fully_checked)), external_name(move(a_external_name)), deprecated_message(move(a_deprecated_message)), stores_arguments(move(a_stores_arguments)), force_inline(move(a_force_inline)){}
NonnullRefPtr<CheckedFunction> types::CheckedFunction::__jakt_create(ByteString name, utility::Span name_span, types::CheckedVisibility visibility, ids::TypeId return_type_id, JaktInternal::Optional<utility::Span> return_type_span, JaktInternal::DynamicArray<types::CheckedParameter> params, NonnullRefPtr<types::FunctionGenerics> generics, types::CheckedBlock block, bool can_throw, parser::FunctionType type, parser::FunctionLinkage linkage, ids::ScopeId function_scope_id, JaktInternal::Optional<ids::StructId> struct_id, bool is_instantiated, JaktInternal::Optional<parser::ParsedFunction> parsed_function, bool is_comptime, bool is_virtual, bool is_override, bool is_unsafe, bool has_varargs, JaktInternal::Optional<size_t> specialization_index, JaktInternal::Optional<ids::ScopeId> owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> owner_scope_generics, bool is_fully_checked, JaktInternal::Optional<parser::ExternalName> external_name, JaktInternal::Optional<ByteString> deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> stores_arguments, parser::InlineState force_inline) { auto o = adopt_ref(*new CheckedFunction (move(name), move(name_span), move(visibility), move(return_type_id), move(return_type_span), move(params), move(generics), move(block), move(can_throw), move(type), move(linkage), move(function_scope_id), move(struct_id), move(is_instantiated), move(parsed_function), move(is_comptime), move(is_virtual), move(is_override), move(is_unsafe), move(has_varargs), move(specialization_index), move(owner_scope), move(owner_scope_generics), move(is_fully_checked), move(external_name), move(deprecated_message), move(stores_arguments), move(force_inline))); return o; }
ByteString types::FunctionGenerics::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FunctionGenerics("sv);{
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
bool types::FunctionGenerics::is_specialized_for_types(JaktInternal::DynamicArray<ids::TypeId> const types) const {
{
if (((((types).size())) == (static_cast<size_t>(0ULL)))){
return true;
}
{
JaktInternal::ArrayIterator<JaktInternal::DynamicArray<ids::TypeId>> _magic = ((((*this).specializations)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::DynamicArray<ids::TypeId> specialization = (_magic_value.value());
{
bool matched = true;
if (((((types).size())) == (((specialization).size())))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(0LL),static_cast<size_t>(((types).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((types)[i])).equals(((specialization)[i])))))){
(matched = false);
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

types::FunctionGenerics::FunctionGenerics(ids::ScopeId a_base_scope_id, JaktInternal::DynamicArray<types::CheckedParameter> a_base_params, JaktInternal::DynamicArray<types::FunctionGenericParameter> a_params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> a_specializations): base_scope_id(move(a_base_scope_id)), base_params(move(a_base_params)), params(move(a_params)), specializations(move(a_specializations)){}
NonnullRefPtr<FunctionGenerics> types::FunctionGenerics::__jakt_create(ids::ScopeId base_scope_id, JaktInternal::DynamicArray<types::CheckedParameter> base_params, JaktInternal::DynamicArray<types::FunctionGenericParameter> params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> specializations) { auto o = adopt_ref(*new FunctionGenerics (move(base_scope_id), move(base_params), move(params), move(specializations))); return o; }
ByteString types::CheckedParameter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedParameter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("requires_label: {}, ", requires_label);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variable: {}, ", *variable);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("default_value_expression: {}", default_value_expression);
}
builder.append(")"sv);return builder.to_string(); }
ErrorOr<types::CheckedParameter> types::CheckedParameter::map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) const {
{
return types::CheckedParameter(((*this).requires_label),TRY((((((*this).variable))->map_types(map)))),((*this).default_value_expression));
}
}

types::CheckedParameter::CheckedParameter(bool a_requires_label, NonnullRefPtr<types::CheckedVariable> a_variable, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>> a_default_value_expression): requires_label(move(a_requires_label)), variable(move(a_variable)), default_value_expression(move(a_default_value_expression)){}

ByteString types::FunctionGenericParameter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FunctionGenericParameter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("kind: {}, ", kind);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("checked_parameter: {}", checked_parameter);
}
builder.append(")"sv);return builder.to_string(); }
ids::TypeId types::FunctionGenericParameter::type_id() const {
{
return ((((*this).checked_parameter)).type_id);
}
}

types::FunctionGenericParameter types::FunctionGenericParameter::parameter(ids::TypeId const type_id,utility::Span const span) {
{
return types::FunctionGenericParameter(types::FunctionGenericParameterKind::Parameter(),types::CheckedGenericParameter::make(type_id,span));
}
}

types::FunctionGenericParameter::FunctionGenericParameter(types::FunctionGenericParameterKind a_kind, types::CheckedGenericParameter a_checked_parameter): kind(move(a_kind)), checked_parameter(move(a_checked_parameter)){}

ByteString types::CheckedVariable::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedVariable("sv);{
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
ErrorOr<NonnullRefPtr<types::CheckedVariable>> types::CheckedVariable::map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) const {
{
return types::CheckedVariable::__jakt_create(((*this).name),TRY((map(((*this).type_id)))),((*this).is_mutable),((*this).definition_span),((*this).type_span),((*this).visibility),((*this).owner_scope),((*this).owner_scope_generics),((*this).external_name));
}
}

parser::ExternalName types::CheckedVariable::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return parser::ExternalName::Plain(((*this).name)); });
}
}

types::CheckedVariable::CheckedVariable(ByteString a_name, ids::TypeId a_type_id, bool a_is_mutable, utility::Span a_definition_span, JaktInternal::Optional<utility::Span> a_type_span, types::CheckedVisibility a_visibility, JaktInternal::Optional<ids::ScopeId> a_owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> a_owner_scope_generics, JaktInternal::Optional<parser::ExternalName> a_external_name): name(move(a_name)), type_id(move(a_type_id)), is_mutable(move(a_is_mutable)), definition_span(move(a_definition_span)), type_span(move(a_type_span)), visibility(move(a_visibility)), owner_scope(move(a_owner_scope)), owner_scope_generics(move(a_owner_scope_generics)), external_name(move(a_external_name)){}
NonnullRefPtr<CheckedVariable> types::CheckedVariable::__jakt_create(ByteString name, ids::TypeId type_id, bool is_mutable, utility::Span definition_span, JaktInternal::Optional<utility::Span> type_span, types::CheckedVisibility visibility, JaktInternal::Optional<ids::ScopeId> owner_scope, JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> owner_scope_generics, JaktInternal::Optional<parser::ExternalName> external_name) { auto o = adopt_ref(*new CheckedVariable (move(name), move(type_id), move(is_mutable), move(definition_span), move(type_span), move(visibility), move(owner_scope), move(owner_scope_generics), move(external_name))); return o; }
ByteString types::CheckedVarDecl::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedVarDecl("sv);{
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
types::CheckedVarDecl::CheckedVarDecl(ByteString a_name, bool a_is_mutable, utility::Span a_span, ids::TypeId a_type_id): name(move(a_name)), is_mutable(move(a_is_mutable)), span(move(a_span)), type_id(move(a_type_id)){}

ByteString types::CheckedBlock::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedBlock("sv);{
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
types::CheckedBlock::CheckedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> a_statements, ids::ScopeId a_scope_id, types::BlockControlFlow a_control_flow, JaktInternal::Optional<ids::TypeId> a_yielded_type, bool a_yielded_none): statements(move(a_statements)), scope_id(move(a_scope_id)), control_flow(move(a_control_flow)), yielded_type(move(a_yielded_type)), yielded_none(move(a_yielded_none)){}

ByteString types::FieldRecord::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("FieldRecord("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("struct_id: {}, ", struct_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("field_id: {}", field_id);
}
builder.append(")"sv);return builder.to_string(); }
types::FieldRecord::FieldRecord(ids::StructId a_struct_id, ids::VarId a_field_id): struct_id(move(a_struct_id)), field_id(move(a_field_id)){}

ByteString types::CheckedField::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedField("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("variable_id: {}, ", variable_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("default_value_expression: {}", default_value_expression);
}
builder.append(")"sv);return builder.to_string(); }
types::CheckedField::CheckedField(ids::VarId a_variable_id, JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>> a_default_value_expression): variable_id(move(a_variable_id)), default_value_expression(move(a_default_value_expression)){}

ByteString types::CheckedStruct::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedStruct("sv);{
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
parser::ExternalName types::CheckedStruct::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return parser::ExternalName::Plain(((*this).name)); });
}
}

types::CheckedStruct::CheckedStruct(ByteString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>> a_generic_parameter_defaults, JaktInternal::DynamicArray<types::CheckedField> a_fields, ids::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> a_trait_implementations, parser::RecordType a_record_type, ids::TypeId a_type_id, JaktInternal::Optional<ids::StructId> a_super_struct_id, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<ids::TypeId> a_implements_type, JaktInternal::Optional<ByteString> a_create_function_name): name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)), generic_parameter_defaults(move(a_generic_parameter_defaults)), fields(move(a_fields)), scope_id(move(a_scope_id)), definition_linkage(move(a_definition_linkage)), trait_implementations(move(a_trait_implementations)), record_type(move(a_record_type)), type_id(move(a_type_id)), super_struct_id(move(a_super_struct_id)), external_name(move(a_external_name)), implements_type(move(a_implements_type)), create_function_name(move(a_create_function_name)){}

ByteString types::CheckedEnum::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedEnum("sv);{
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
types::CheckedEnum::CheckedEnum(ByteString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, JaktInternal::DynamicArray<types::CheckedEnumVariant> a_variants, JaktInternal::DynamicArray<types::CheckedField> a_fields, ids::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> a_trait_implementations, parser::RecordType a_record_type, ids::TypeId a_underlying_type_id, ids::TypeId a_type_id, bool a_is_boxed): name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)), variants(move(a_variants)), fields(move(a_fields)), scope_id(move(a_scope_id)), definition_linkage(move(a_definition_linkage)), trait_implementations(move(a_trait_implementations)), record_type(move(a_record_type)), underlying_type_id(move(a_underlying_type_id)), type_id(move(a_type_id)), is_boxed(move(a_is_boxed)){}

ByteString types::CheckedGenericParameter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedGenericParameter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("constraints: {}, ", constraints);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
types::CheckedGenericParameter types::CheckedGenericParameter::make(ids::TypeId const type_id,utility::Span const span) {
{
return types::CheckedGenericParameter(type_id,DynamicArray<ids::TraitId>::create_with({}),span);
}
}

types::CheckedGenericParameter::CheckedGenericParameter(ids::TypeId a_type_id, JaktInternal::DynamicArray<ids::TraitId> a_constraints, utility::Span a_span): type_id(move(a_type_id)), constraints(move(a_constraints)), span(move(a_span)){}

ByteString types::CheckedEnumVariantBinding::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedEnumVariantBinding("sv);{
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
types::CheckedEnumVariantBinding::CheckedEnumVariantBinding(JaktInternal::Optional<ByteString> a_name, ByteString a_binding, ids::TypeId a_type_id, utility::Span a_span): name(move(a_name)), binding(move(a_binding)), type_id(move(a_type_id)), span(move(a_span)){}

ByteString types::CheckedStringLiteral::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedStringLiteral("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("value: {}, ", value);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_id: {}, ", type_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("may_throw: {}", may_throw);
}
builder.append(")"sv);return builder.to_string(); }
ByteString types::CheckedStringLiteral::to_string() const {
{
return ((((*this).value)).to_string());
}
}

types::CheckedStringLiteral::CheckedStringLiteral(types::StringLiteral a_value, ids::TypeId a_type_id, bool a_may_throw): value(move(a_value)), type_id(move(a_type_id)), may_throw(move(a_may_throw)){}

ByteString types::ClassInstanceRebind::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ClassInstanceRebind("sv);{
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
types::ClassInstanceRebind::ClassInstanceRebind(ByteString a_name, utility::Span a_name_span, bool a_is_mutable, bool a_is_reference): name(move(a_name)), name_span(move(a_name_span)), is_mutable(move(a_is_mutable)), is_reference(move(a_is_reference)){}

ByteString types::OperatorTraitImplementation::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("OperatorTraitImplementation("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_id: {}, ", trait_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_generic_arguments: {}, ", trait_generic_arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("call_expression: {}", call_expression);
}
builder.append(")"sv);return builder.to_string(); }
types::OperatorTraitImplementation::OperatorTraitImplementation(ids::TraitId a_trait_id, JaktInternal::DynamicArray<ids::TypeId> a_trait_generic_arguments, types::CheckedCall a_call_expression): trait_id(move(a_trait_id)), trait_generic_arguments(move(a_trait_generic_arguments)), call_expression(move(a_call_expression)){}

ByteString types::CheckedBinaryOperator::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedBinaryOperator("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("op: {}, ", op);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("trait_implementation: {}", trait_implementation);
}
builder.append(")"sv);return builder.to_string(); }
types::CheckedBinaryOperator::CheckedBinaryOperator(parser::BinaryOperator a_op, JaktInternal::Optional<types::OperatorTraitImplementation> a_trait_implementation): op(move(a_op)), trait_implementation(move(a_trait_implementation)){}

ByteString types::ResolvedNamespace::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("ResolvedNamespace("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("name: \"{}\", ", name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("external_name: {}, ", external_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("generic_parameters: {}", generic_parameters);
}
builder.append(")"sv);return builder.to_string(); }
parser::ExternalName types::ResolvedNamespace::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return parser::ExternalName::Plain(((*this).name)); });
}
}

types::ResolvedNamespace::ResolvedNamespace(ByteString a_name, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> a_generic_parameters): name(move(a_name)), external_name(move(a_external_name)), generic_parameters(move(a_generic_parameters)){}

ByteString types::CheckedCall::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedCall("sv);{
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
parser::ExternalName types::CheckedCall::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return parser::ExternalName::Plain(((*this).name)); });
}
}

types::CheckedCall::CheckedCall(JaktInternal::DynamicArray<types::ResolvedNamespace> a_namespace_, ByteString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename types::CheckedExpression>>> a_args, JaktInternal::DynamicArray<ids::TypeId> a_type_args, JaktInternal::Optional<ids::FunctionId> a_function_id, ids::TypeId a_return_type, bool a_callee_throws, JaktInternal::Optional<parser::ExternalName> a_external_name, parser::InlineState a_force_inline): namespace_(move(a_namespace_)), name(move(a_name)), args(move(a_args)), type_args(move(a_type_args)), function_id(move(a_function_id)), return_type(move(a_return_type)), callee_throws(move(a_callee_throws)), external_name(move(a_external_name)), force_inline(move(a_force_inline)){}

ByteString types::CheckedProgram::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("CheckedProgram("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("modules: {}, ", modules);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("loaded_modules: {}", loaded_modules);
}
builder.append(")"sv);return builder.to_string(); }
ids::ModuleId types::CheckedProgram::create_module(ByteString const name,bool const is_root,JaktInternal::Optional<ByteString> const path) {
{
size_t const new_id = ((((*this).modules)).size());
ids::ModuleId const module_id = ids::ModuleId(new_id);
NonnullRefPtr<types::Module> const module = types::Module::__jakt_create(module_id,name,DynamicArray<NonnullRefPtr<typename types::Type>>::create_with({types::Type::Void(parser::CheckedQualifiers(false)), types::Type::Bool(parser::CheckedQualifiers(false)), types::Type::U8(parser::CheckedQualifiers(false)), types::Type::U16(parser::CheckedQualifiers(false)), types::Type::U32(parser::CheckedQualifiers(false)), types::Type::U64(parser::CheckedQualifiers(false)), types::Type::I8(parser::CheckedQualifiers(false)), types::Type::I16(parser::CheckedQualifiers(false)), types::Type::I32(parser::CheckedQualifiers(false)), types::Type::I64(parser::CheckedQualifiers(false)), types::Type::F32(parser::CheckedQualifiers(false)), types::Type::F64(parser::CheckedQualifiers(false)), types::Type::Usize(parser::CheckedQualifiers(false)), types::Type::JaktString(parser::CheckedQualifiers(false)), types::Type::CChar(parser::CheckedQualifiers(false)), types::Type::CInt(parser::CheckedQualifiers(false)), types::Type::Unknown(parser::CheckedQualifiers(false)), types::Type::Never(parser::CheckedQualifiers(false))}),path.value_or_lazy_evaluated([&] { return (((((((*this).compiler))->current_file_path()).value())).to_string()); }),is_root,DynamicArray<NonnullRefPtr<types::CheckedFunction>>::create_with({}),DynamicArray<types::CheckedStruct>::create_with({}),DynamicArray<types::CheckedEnum>::create_with({}),DynamicArray<NonnullRefPtr<types::Scope>>::create_with({}),DynamicArray<NonnullRefPtr<types::CheckedTrait>>::create_with({}),DynamicArray<NonnullRefPtr<types::CheckedVariable>>::create_with({}),DynamicArray<ids::ModuleId>::create_with({}),Dictionary<size_t, ids::StructId>::create_with_entries({}));
((((*this).modules)).push(module));
return module_id;
}
}

ByteString types::CheckedProgram::debug_description_of(ids::ScopeId const scope_id) const {
{
JaktInternal::DynamicArray<ByteString> ss = DynamicArray<ByteString>::create_with({});
ids::ScopeId current_scope_id = scope_id;
for (;;){
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(current_scope_id));
ByteString const d = __jakt_format((StringView::from_string_literal("{} (named {})"sv)),((scope)->debug_name),((scope)->namespace_name));
((ss).insert(static_cast<size_t>(0ULL),d));
if (((((scope)->parent)).has_value())){
(current_scope_id = (((scope)->parent).value()));
}
else {
break;
}

}
return utility::join(ss,(ByteString::from_utf8_without_validation(" -> "sv)));
}
}

ids::ScopeId types::CheckedProgram::create_scope(JaktInternal::Optional<ids::ScopeId> const parent_scope_id,bool const can_throw,ByteString const debug_name,ids::ModuleId const module_id,bool const for_block) {
{
bool is_from_generated_code = false;
if (((parent_scope_id).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
((((((parent_scope_id.value())).module_id)).id),((((*this).modules)).size()))){
((((*this).compiler))->panic(__jakt_format((StringView::from_string_literal("create_scope: parent_scope_id.module is invalid! No module with id {}."sv)),(((((parent_scope_id.value())).module_id)).id))));
}
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
((((parent_scope_id.value())).id),((((((((*this).modules))[(((((parent_scope_id.value())).module_id)).id)]))->scopes)).size()))){
((((*this).compiler))->panic(__jakt_format((StringView::from_string_literal("create_scope: parent_scope_id.id is invalid! Module {} does not have a scope with id {}."sv)),(((((parent_scope_id.value())).module_id)).id),(((parent_scope_id.value())).id))));
}
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope((parent_scope_id.value())));
(is_from_generated_code = ((scope)->is_from_generated_code));
}
NonnullRefPtr<types::Scope> const scope = types::Scope::__jakt_create(parent_scope_id,can_throw,debug_name,for_block,is_from_generated_code,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Dictionary<ByteString, ids::VarId>::create_with_entries({}),Dictionary<ByteString, types::Value>::create_with_entries({}),Dictionary<ByteString, ids::StructId>::create_with_entries({}),Dictionary<ByteString, JaktInternal::DynamicArray<ids::FunctionId>>::create_with_entries({}),Dictionary<ByteString, ids::EnumId>::create_with_entries({}),Dictionary<ByteString, ids::TypeId>::create_with_entries({}),Dictionary<ByteString, ids::TraitId>::create_with_entries({}),Dictionary<ByteString, ids::ModuleId>::create_with_entries({}),Dictionary<ByteString, ids::ScopeId>::create_with_entries({}),JaktInternal::OptionalNone(),DynamicArray<ids::ScopeId>::create_with({}),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),DynamicArray<parser::IncludeAction>::create_with({}),DynamicArray<parser::IncludeAction>::create_with({}),DynamicArray<types::ResolutionMixin>::create_with({}),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Dictionary<ByteString, types::SpecializedType>::create_with_entries({}));
((((((((*this).modules))[((module_id).id)]))->scopes)).push(scope));
return ids::ScopeId(module_id,JaktInternal::checked_sub(((((((((*this).modules))[((module_id).id)]))->scopes)).size()),static_cast<size_t>(1ULL)));
}
}

ids::TypeId types::CheckedProgram::apply_qualifiers_to_type(parser::CheckedQualifiers const qualifiers,ids::TypeId const type_id) {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
if ([](parser::CheckedQualifiers const& self, parser::CheckedQualifiers rhs) -> bool {{
return (!(((self).equals(rhs))));
}
}
(qualifiers,((type)->common.init_common.qualifiers))){
return ((*this).find_or_add_type_id(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::Type>, ids::TypeId>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(types::Type::Void(qualifiers));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(types::Type::Bool(qualifiers));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(types::Type::U8(qualifiers));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(types::Type::U16(qualifiers));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(types::Type::U32(qualifiers));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(types::Type::U64(qualifiers));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(types::Type::I8(qualifiers));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(types::Type::I16(qualifiers));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(types::Type::I32(qualifiers));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(types::Type::I64(qualifiers));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(types::Type::F32(qualifiers));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(types::Type::F64(qualifiers));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(types::Type::Usize(qualifiers));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(types::Type::JaktString(qualifiers));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(types::Type::CChar(qualifiers));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(types::Type::CInt(qualifiers));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue(types::Type::Unknown(parser::CheckedQualifiers(false)));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue(types::Type::Never(parser::CheckedQualifiers(false)));
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<ids::TypeId> const& trait_implementations = __jakt_match_value.trait_implementations;
bool const& is_value = __jakt_match_value.is_value;
return JaktInternal::ExplicitValue(types::Type::TypeVariable(qualifiers,name,trait_implementations,is_value));
};/*case end*/
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(types::Type::Dependent(qualifiers,namespace_type,name));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(types::Type::GenericInstance(qualifiers,id,args));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(types::Type::GenericEnumInstance(qualifiers,id,args));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(types::Type::GenericTraitInstance(qualifiers,id,args));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(types::Type::GenericResolvedType(qualifiers,id,args));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Type::Struct(qualifiers,id));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Type::Enum(qualifiers,id));
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Type::RawPtr(qualifiers,id));
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Type::Trait(qualifiers,id));
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Type::Reference(qualifiers,id));
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Type::MutableReference(qualifiers,id));
};/*case end*/
case 30 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(types::Type::Function(qualifiers,params,can_throw,return_type_id,pseudo_function_id));
};/*case end*/
case 31 /* Self */: {
return JaktInternal::ExplicitValue(types::Type::Self(qualifiers));
};/*case end*/
case 32 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::Type::Const(qualifiers,value));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),((type_id).module),true));
}
else {
return type_id;
}

}
}

ids::StructId types::CheckedProgram::builtin_implementation_struct(types::BuiltinType const builtin,ids::ModuleId const for_module) {
{
size_t const id = ((builtin).id());
NonnullRefPtr<types::Module> module = ((((*this).modules))[((for_module).id)]);
if (((((module)->builtin_implementation_structs)).contains(id))){
return ((((module)->builtin_implementation_structs))[id]);
}
ids::ScopeId const scope_id = ((*this).create_scope(JaktInternal::OptionalNone(),false,__jakt_format((StringView::from_string_literal("builtin({})"sv)),((builtin).constructor_name())),for_module,false));
JaktInternal::Dictionary<ByteString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> const trait_implementations = Dictionary<ByteString, JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>>::create_with_entries({});
utility::Span const name_span = utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL));
ids::StructId const struct_id = ids::StructId(for_module,((((module)->structures)).size()));
ids::TypeId const struct_type_id = ((*this).find_or_add_type_id(types::Type::Struct(parser::CheckedQualifiers(false),struct_id),for_module,false));
types::CheckedStruct const struct_ = types::CheckedStruct(__jakt_format((StringView::from_string_literal("Builtin_{}"sv)),((builtin).constructor_name())),name_span,DynamicArray<types::CheckedGenericParameter>::create_with({}),JaktInternal::OptionalNone(),DynamicArray<types::CheckedField>::create_with({}),scope_id,parser::DefinitionLinkage::External(),trait_implementations,parser::RecordType::Struct(DynamicArray<parser::ParsedField>::create_with({}),JaktInternal::OptionalNone()),struct_type_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),types::builtin(builtin),JaktInternal::OptionalNone());
((((module)->structures)).push(struct_));
((module)->builtin_implementation_structs).set(id, struct_id);
return struct_id;
}
}

NonnullRefPtr<types::Module> types::CheckedProgram::get_module(ids::ModuleId const id) const {
{
return ((((*this).modules))[((id).id)]);
}
}

NonnullRefPtr<types::CheckedFunction> types::CheckedProgram::get_function(ids::FunctionId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->functions))[((id).id)]);
}
}

NonnullRefPtr<types::CheckedVariable> types::CheckedProgram::get_variable(ids::VarId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->variables))[((id).id)]);
}
}

NonnullRefPtr<typename types::Type> types::CheckedProgram::get_type(ids::TypeId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->types))[((id).id)]);
}
}

types::CheckedEnum types::CheckedProgram::get_enum(ids::EnumId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->enums))[((id).id)]);
}
}

types::CheckedStruct types::CheckedProgram::get_struct(ids::StructId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->structures))[((id).id)]);
}
}

NonnullRefPtr<types::Scope> types::CheckedProgram::get_scope(ids::ScopeId const id) const {
{
return ((((((((*this).modules))[((((id).module_id)).id)]))->scopes))[((id).id)]);
}
}

NonnullRefPtr<types::CheckedTrait> types::CheckedProgram::get_trait(ids::TraitId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->traits))[((id).id)]);
}
}

ids::ScopeId types::CheckedProgram::prelude_scope_id() const {
{
return ids::ScopeId(ids::ModuleId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL));
}
}

ids::ModuleId types::CheckedProgram::prelude_module_id() const {
{
return ids::ModuleId(static_cast<size_t>(0ULL));
}
}

void types::CheckedProgram::set_loaded_module(ByteString const module_name,types::LoadedModule const loaded_module) {
{
((((*this).loaded_modules)).set(module_name,loaded_module));
}
}

JaktInternal::Optional<types::LoadedModule> types::CheckedProgram::get_loaded_module(ByteString const module_name) const {
{
return ((((*this).loaded_modules)).get(module_name));
}
}

void types::CheckedProgram::set_owner_scope_if_needed(ids::ScopeId const parent_scope_id,JaktInternal::DynamicArray<ids::FunctionId> const overload_set,utility::Span const span) {
{
{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((overload_set).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId overload = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> function = ((*this).get_function(overload));
if ((!(((((function)->owner_scope)).has_value())))){
(((function)->owner_scope) = parent_scope_id);
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(parent_scope_id));
if (((((scope)->relevant_type_id)).has_value())){
ids::TypeId const type_id = (((scope)->relevant_type_id).value());
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>> const no_defaults = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<ids::TypeId> const no_args = DynamicArray<ids::TypeId>::create_with({});
JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>> const maybe_generics = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>, void>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>> __jakt_var_143; {
types::CheckedStruct const struct_ = ((*this).get_struct(id));
__jakt_var_143 = static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>>((Tuple{((struct_).generic_parameters), ((struct_).generic_parameter_defaults), args})); goto __jakt_label_137;

}
__jakt_label_137:; __jakt_var_143.release_value(); }));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>> __jakt_var_144; {
types::CheckedStruct const struct_ = ((*this).get_struct(id));
__jakt_var_144 = static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>>((Tuple{((struct_).generic_parameters), ((struct_).generic_parameter_defaults), args})); goto __jakt_label_138;

}
__jakt_label_138:; __jakt_var_144.release_value(); }));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>> __jakt_var_145; {
types::CheckedStruct const struct_ = ((*this).get_struct(id));
__jakt_var_145 = static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>>((Tuple{((struct_).generic_parameters), ((struct_).generic_parameter_defaults), no_args})); goto __jakt_label_139;

}
__jakt_label_139:; __jakt_var_145.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>>((Tuple{((((*this).get_enum(id))).generic_parameters), no_defaults, args})));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>>((Tuple{((((*this).get_enum(id))).generic_parameters), no_defaults, no_args})));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>>((Tuple{((((*this).get_trait(id)))->generic_parameters), no_defaults, args})));
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>>>>((Tuple{((((*this).get_trait(id)))->generic_parameters), no_defaults, no_args})));
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
if (((maybe_generics).has_value())){
JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>> const generics = (maybe_generics.value());
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> inferences = Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({});
JaktInternal::Tuple<JaktInternal::DynamicArray<types::CheckedGenericParameter>,JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>>,JaktInternal::DynamicArray<ids::TypeId>> const parameters_declared_defaults_args_ = generics;
JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters = ((parameters_declared_defaults_args_).template get<0>());
JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>> const declared_defaults = ((parameters_declared_defaults_args_).template get<1>());
JaktInternal::DynamicArray<ids::TypeId> const args = ((parameters_declared_defaults_args_).template get<2>());

JaktInternal::Optional<ids::TypeId> const no_type_id = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>> const empty_defaults = DynamicArray<JaktInternal::Optional<ids::TypeId>>::filled(((parameters).size()), no_type_id);
JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>> const defaults = declared_defaults.value_or_lazy_evaluated([&] { return empty_defaults; });
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((parameters).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedGenericParameter const& parameter = ((((parameters)[i])));
ids::TypeId const arg = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<ids::TypeId>,void> {
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,((args).size())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<ids::TypeId>>(((args)[i])));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(((defaults)[i]));
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
}).value_or_lazy_evaluated([&] { return ((((parameter))).type_id); });
((inferences).set(((((parameter))).type_id),arg));
}

}
}

(((function)->owner_scope_generics) = inferences);
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

void types::CheckedProgram::set_owner_scope_if_needed(ids::ScopeId const parent_scope_id,ids::VarId const var_id) {
{
NonnullRefPtr<types::CheckedVariable> variable = ((*this).get_variable(var_id));
if ((!(((((variable)->owner_scope)).has_value())))){
(((variable)->owner_scope) = parent_scope_id);
}
}
}

ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> types::CheckedProgram::find_var_in_scope(ids::ScopeId const scope_id,ByteString const var,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<types::CheckedVariable>>(scope_id,(([var, this](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>> {{
if ((!(((mixin).mixin_vars)))){
return utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>::Continue();
}
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(((mixin).scope_id)));
JaktInternal::Optional<ids::VarId> const maybe_var = ((((scope)->vars)).get(var));
if (((maybe_var).has_value())){
return utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>::Break(((*this).get_variable((maybe_var.value()))));
}
return utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>::Continue();
}
}
)),ignore_mixin_scopes,root_scope))));
}
}

ErrorOr<JaktInternal::Optional<types::Value>> types::CheckedProgram::find_comptime_binding_in_scope(ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<types::Value>(scope_id,(([name, this](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<types::Value>> {{
if ((!(((mixin).mixin_bindings)))){
return utility::IterationDecision<types::Value>::Continue();
}
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(((mixin).scope_id)));
JaktInternal::Optional<types::Value> const maybe_binding = ((((scope)->comptime_bindings)).get(name));
if (((maybe_binding).has_value())){
return utility::IterationDecision<types::Value>::Break((maybe_binding.value()));
}
return utility::IterationDecision<types::Value>::Continue();
}
}
)),ignore_mixin_scopes,root_scope))));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> types::CheckedProgram::find_type_scope(ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>(scope_id,(([name, this](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> {{
if ((!(((mixin).mixin_types)))){
return utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>::Continue();
}
JaktInternal::Optional<ids::TypeId> const maybe_type = ((((((*this).get_scope(((mixin).scope_id))))->types)).get(name));
if (((maybe_type).has_value())){
return utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>::Break((Tuple{(maybe_type.value()), ((mixin).scope_id)}));
}
return utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>::Continue();
}
}
)),ignore_mixin_scopes,root_scope))));
}
}

ErrorOr<JaktInternal::Optional<ids::TypeId>> types::CheckedProgram::find_type_in_scope(ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return ((TRY((((*this).find_type_scope(scope_id,name,ignore_mixin_scopes,root_scope))))).map([](auto& _value) { return _value.template get<0>(); }));
}
}

ErrorOr<JaktInternal::Optional<ids::EnumId>> types::CheckedProgram::find_enum_in_scope(ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<ids::EnumId>(scope_id,(([name, this](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<ids::EnumId>> {{
if ((!(((mixin).mixin_enums)))){
return utility::IterationDecision<ids::EnumId>::Continue();
}
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(((mixin).scope_id)));
JaktInternal::Optional<ids::EnumId> const maybe_enum = ((((scope)->enums)).get(name));
if (((maybe_enum).has_value())){
return utility::IterationDecision<ids::EnumId>::Break((maybe_enum.value()));
}
return utility::IterationDecision<ids::EnumId>::Continue();
}
}
)),ignore_mixin_scopes,root_scope))));
}
}

ErrorOr<JaktInternal::Optional<ids::TraitId>> types::CheckedProgram::find_trait_in_scope(ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<ids::TraitId>(scope_id,(([name, this](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<ids::TraitId>> {{
if ((!(((mixin).mixin_traits)))){
return utility::IterationDecision<ids::TraitId>::Continue();
}
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(((mixin).scope_id)));
JaktInternal::Optional<ids::TraitId> const maybe_trait = ((((scope)->traits)).get(name));
if (((maybe_trait).has_value())){
return utility::IterationDecision<ids::TraitId>::Break((maybe_trait.value()));
}
return utility::IterationDecision<ids::TraitId>::Continue();
}
}
)),ignore_mixin_scopes,root_scope))));
}
}

bool types::CheckedProgram::is_integer(ids::TypeId const type_id) const {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(true);
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
});
}
}

bool types::CheckedProgram::is_floating(ids::TypeId const type_id) const {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(true);
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
});
}
}

bool types::CheckedProgram::is_numeric(ids::TypeId const type_id) const {
{
return (((*this).is_integer(type_id)) || ((*this).is_floating(type_id)));
}
}

ErrorOr<bool> types::CheckedProgram::is_string(ids::TypeId const type_id) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("String"sv))))))).equals(struct_id)));
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
});
}
}

i64 types::CheckedProgram::get_bits(ids::TypeId const type_id) const {
{
return ((((*this).get_type(type_id)))->get_bits());
}
}

bool types::CheckedProgram::is_signed(ids::TypeId const type_id) const {
{
return ((((*this).get_type(type_id)))->is_signed());
}
}

ErrorOr<JaktInternal::Optional<bool>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope_direct_chain(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<bool>>(types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
AK::Queue<types::ResolutionMixin> scopes_to_check = AK::Queue<types::ResolutionMixin>();
JaktInternal::Set<ids::ScopeId> seen = Set<ids::ScopeId>::create_with_values({});
((scopes_to_check).enqueue(types::ResolutionMixin(scope_id,true,true,true,true,true,true,true,true,true)));
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((((*this).get_scope(scope_id)))->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
((scopes_to_check).enqueue(types::ResolutionMixin(child,true,true,true,true,true,true,true,true,true)));
}

}
}

while ((!(((scopes_to_check).is_empty())))){
types::ResolutionMixin const mixin = ((scopes_to_check).dequeue());
ids::ScopeId const scope_id = ((mixin).scope_id);
if (((seen).contains(scope_id))){
continue;
}
((seen).add(scope_id));
typename utility::IterationDecision<bool> const res = TRY((callback(mixin,JaktInternal::OptionalNone(),false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
return static_cast<JaktInternal::Optional<bool>>(value);
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(scope_id));
if (((!((((root_scope).has_value()) && ((scope_id).equals((root_scope.value())))))) && ((((scope)->parent)).has_value()))){
((scopes_to_check).enqueue(types::ResolutionMixin((((scope)->parent).value()),true,true,true,true,true,true,true,true,true)));
}
if (((((scope)->namespace_name)).has_value())){
continue;
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
((scopes_to_check).enqueue(types::ResolutionMixin(child,true,true,true,true,true,true,true,true,true)));
}

}
}

}
return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<bool>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope_impl(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<bool>>(types::ResolutionMixin, JaktInternal::Optional<ByteString>, bool)> const& callback,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
if (ignore_mixin_scopes){
return TRY((((*this).for_each_scope_accessible_unqualified_from_scope_direct_chain(scope_id,callback,root_scope))));
}
AK::Queue<types::ResolutionMixin> scopes_to_check = AK::Queue<types::ResolutionMixin>();
JaktInternal::Set<ids::ScopeId> seen = Set<ids::ScopeId>::create_with_values({});
((scopes_to_check).enqueue(types::ResolutionMixin(scope_id,true,true,true,true,true,true,true,true,true)));
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((((*this).get_scope(scope_id)))->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
((scopes_to_check).enqueue(types::ResolutionMixin(child,true,true,true,true,true,true,true,true,true)));
}

}
}

while ((!(((scopes_to_check).is_empty())))){
types::ResolutionMixin const mixin = ((scopes_to_check).dequeue());
ids::ScopeId const scope_id = ((mixin).scope_id);
if (((seen).contains(scope_id))){
continue;
}
((seen).add(scope_id));
typename utility::IterationDecision<bool> const res = TRY((callback(mixin,JaktInternal::OptionalNone(),false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
return static_cast<JaktInternal::Optional<bool>>(value);
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    if (_jakt_value.is_loop_break())
        break;
    if (_jakt_value.is_loop_continue())
        continue;
    _jakt_value.release_value();
});
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(scope_id));
if (((!((((root_scope).has_value()) && ((scope_id).equals((root_scope.value())))))) && ((((scope)->parent)).has_value()))){
((scopes_to_check).enqueue(types::ResolutionMixin((((scope)->parent).value()),true,true,true,true,true,true,true,true,true)));
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
if ((!(((((((*this).get_scope(child)))->namespace_name)).has_value())))){
((scopes_to_check).enqueue(types::ResolutionMixin(child,true,true,true,true,true,true,true,true,true)));
}
}

}
}

{
JaktInternal::ArrayIterator<types::ResolutionMixin> _magic = ((((scope)->resolution_mixins)).iterator());
for (;;){
JaktInternal::Optional<types::ResolutionMixin> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::ResolutionMixin entry = (_magic_value.value());
{
((scopes_to_check).enqueue(entry));
}

}
}

{
JaktInternal::DictionaryIterator<ByteString,ids::ScopeId> _magic = ((((scope)->aliases)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::ScopeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::ScopeId> name__alias__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::ScopeId> const jakt__name__alias__ = name__alias__;
ByteString const name = ((jakt__name__alias__).template get<0>());
ids::ScopeId const alias = ((jakt__name__alias__).template get<1>());

typename utility::IterationDecision<bool> const res = TRY((callback(types::ResolutionMixin(alias,true,true,true,true,true,true,true,true,true),name,true)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
return static_cast<JaktInternal::Optional<bool>>(value);
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
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
ids::ModuleId const module_id = ((scope_id).module_id);
ids::ScopeId const search_scope_id = ids::ScopeId(module_id,static_cast<size_t>(0ULL));
NonnullRefPtr<types::Scope> const search_scope = ((*this).get_scope(search_scope_id));
{
JaktInternal::DictionaryIterator<ByteString,ids::ModuleId> _magic = ((((search_scope)->imports)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,ids::ModuleId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,ids::ModuleId> name__module__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,ids::ModuleId> const jakt__name__module__ = name__module__;
ByteString const name = ((jakt__name__module__).template get<0>());
ids::ModuleId const module = ((jakt__name__module__).template get<1>());

ids::ScopeId const import_scope_id = ids::ScopeId(module,static_cast<size_t>(0ULL));
typename utility::IterationDecision<bool> const res = TRY((callback(types::ResolutionMixin(import_scope_id,true,true,true,true,true,true,true,true,true),name,false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>> {
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.__jakt_init_index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.as.Break;
auto& value = __jakt_match_value.value;
{
return static_cast<JaktInternal::Optional<bool>>(value);
}
return JaktInternal::ExplicitValue<void>();
}
else {
{
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
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

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<ids::StructId>> types::CheckedProgram::find_struct_in_scope(ids::ScopeId const scope_id,ByteString const name,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<ids::StructId>(scope_id,(([name, this](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<ids::StructId>> {{
if ((!(((mixin).mixin_structs)))){
return utility::IterationDecision<ids::StructId>::Continue();
}
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(((mixin).scope_id)));
JaktInternal::Optional<ids::StructId> const maybe_struct = ((((scope)->structs)).get(name));
if (((maybe_struct).has_value())){
return utility::IterationDecision<ids::StructId>::Break((maybe_struct.value()));
}
return utility::IterationDecision<ids::StructId>::Continue();
}
}
)),ignore_mixin_scopes,root_scope))));
}
}

ErrorOr<ids::StructId> types::CheckedProgram::find_struct_in_prelude(ByteString const name) const {
{
ids::ScopeId const scope_id = ((*this).prelude_scope_id());
JaktInternal::Optional<ids::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,name,true,JaktInternal::OptionalNone()))));
if (((struct_id).has_value())){
return ((struct_id).value());
}
((((*this).compiler))->panic(__jakt_format((StringView::from_string_literal("internal error: {} builtin definition not found"sv)),name)));
}
}

ErrorOr<bool> types::CheckedProgram::is_scope_directly_accessible_from(ids::ScopeId const check_scope_id,ids::ScopeId const scope_id,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<bool>(scope_id,(([check_scope_id](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {{
if (((check_scope_id).equals(((mixin).scope_id)))){
return utility::IterationDecision<bool>::Break(true);
}
return utility::IterationDecision<bool>::Continue();
}
}
)),ignore_mixin_scopes,JaktInternal::OptionalNone())))).value_or_lazy_evaluated([&] { return false; });
}
}

ErrorOr<types::StructOrEnumId> types::CheckedProgram::find_reflected_primitive(ByteString const primitive) const {
{
ids::ScopeId const scope_id = ((*this).prelude_scope_id());
JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>> const maybe_namespace = TRY((((*this).find_namespace_in_scope(scope_id,(ByteString::from_utf8_without_validation("Reflect"sv)),false,true,JaktInternal::OptionalNone()))));
if ((!(((maybe_namespace).has_value())))){
((((*this).compiler))->panic(__jakt_format((StringView::from_string_literal("internal error: builtin namespace 'Reflect' not found"sv)))));
}
ids::ScopeId const reflect_namespace_scope_id = (((maybe_namespace.value())).template get<0>());
JaktInternal::Optional<ids::EnumId> const enum_id = TRY((((*this).find_enum_in_scope(reflect_namespace_scope_id,primitive,false,JaktInternal::OptionalNone()))));
if (((enum_id).has_value())){
return types::StructOrEnumId::Enum((enum_id.value()));
}
JaktInternal::Optional<ids::StructId> const struct_id = TRY((((*this).find_struct_in_scope(reflect_namespace_scope_id,primitive,false,JaktInternal::OptionalNone()))));
if (((struct_id).has_value())){
return types::StructOrEnumId::Struct((struct_id.value()));
}
((((*this).compiler))->panic(__jakt_format((StringView::from_string_literal("internal error: definition for reflect builtin '{}' not found"sv)),primitive)));
}
}

ids::ScopeId types::CheckedProgram::find_type_scope_id(ids::TypeId const type_id) {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::ScopeId, ids::ScopeId>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_struct(struct_id))).scope_id));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_struct(struct_id))).scope_id));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_enum(enum_id))).scope_id));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_enum(enum_id))).scope_id));
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_trait(trait_id)))->scope_id));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& trait_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_trait(trait_id)))->scope_id));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::ScopeId,ids::ScopeId> {
auto __jakt_enum_value = (((type)->is_builtin()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((((*this).get_struct(((*this).builtin_implementation_struct(((type)->as_builtin_type()),((*this).prelude_module_id())))))).scope_id));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(((*this).prelude_scope_id()));
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
});
}
}

JaktInternal::Optional<ids::ScopeId> types::CheckedProgram::find_namespace_in_immediate_children_of_scope(ids::ScopeId const scope_id,ByteString const name,bool const treat_aliases_as_imports) const {
{
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(scope_id));
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = ((*this).get_scope(child));
if ((((((child_scope)->namespace_name)).has_value()) && (((((child_scope)->namespace_name).value())) == (name)))){
return child;
}
}

}
}

if (treat_aliases_as_imports){
if (((((scope)->aliases)).contains(name))){
return ((((scope)->aliases)).get(name));
}
}
return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>>> types::CheckedProgram::find_namespace_in_scope(ids::ScopeId const scope_id,ByteString const name,bool const treat_aliases_as_imports,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<ids::ScopeId,bool>>(scope_id,(([name, treat_aliases_as_imports, this](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>> {{
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(((mixin).scope_id)));
JaktInternal::Optional<ByteString> const effective_name = name_override.value_or_lazy_evaluated_optional([&] { return ((scope)->namespace_name); });
bool const is_import = (((name_override).has_value()) && (!(is_alias)));
if ((((effective_name).has_value()) && (((effective_name.value())) == (name)))){
return utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>::Break((Tuple{((mixin).scope_id), (is_import || (is_alias && treat_aliases_as_imports))}));
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
NonnullRefPtr<types::Scope> const child_scope = ((*this).get_scope(child));
JaktInternal::Optional<ByteString> const effective_name = name_override.value_or_lazy_evaluated_optional([&] { return ((child_scope)->namespace_name); });
if ((((effective_name).has_value()) && (((effective_name.value())) == (name)))){
return utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>::Break((Tuple{child, false}));
}
}

}
}

return utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>::Continue();
}
}
)),ignore_mixin_scopes,root_scope))));
}
}

ErrorOr<JaktInternal::Optional<ids::FunctionId>> types::CheckedProgram::find_function_in_scope(ids::ScopeId const parent_scope_id,ByteString const function_name,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const results = TRY((((*this).find_functions_with_name_in_scope(parent_scope_id,function_name,false,root_scope))));
if ((!(((results).has_value())))){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<ids::FunctionId> const functions = ((results).value());
if (((((functions).size())) != (static_cast<size_t>(1ULL)))){
((((*this).compiler))->panic(__jakt_format((StringView::from_string_literal("internal error: found {} functions with name '{}', but expected 1"sv)),((functions).size()),function_name)));
}
return ((functions)[static_cast<i64>(0LL)]);
}
}

ErrorOr<JaktInternal::Optional<ids::FunctionId>> types::CheckedProgram::find_default_constructors_in_scope(ids::ScopeId const parent_scope_id,ByteString const function_name,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const results = TRY((((*this).find_functions_with_name_in_scope(parent_scope_id,function_name,false,root_scope))));
if ((!(((results).has_value())))){
return JaktInternal::OptionalNone();
}
{
JaktInternal::ArrayIterator<ids::FunctionId> _magic = ((((results).value())).iterator());
for (;;){
JaktInternal::Optional<ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::FunctionId id = (_magic_value.value());
{
NonnullRefPtr<types::CheckedFunction> const function = ((*this).get_function(id));
if (((((function)->type)).__jakt_init_index() == 3 /* ImplicitConstructor */)){
return id;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>>> types::CheckedProgram::find_functions_with_name_in_scope(ids::ScopeId const parent_scope_id,ByteString const function_name,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
return ((TRY((((*this).find_scoped_functions_with_name_in_scope(parent_scope_id,function_name,ignore_mixin_scopes,root_scope))))).map([](auto& _value) { return _value.template get<0>(); }));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> types::CheckedProgram::find_scoped_functions_with_name_in_scope(ids::ScopeId const parent_scope_id,ByteString const function_name,bool const ignore_mixin_scopes,JaktInternal::Optional<ids::ScopeId> const root_scope) const {
{
JaktInternal::DynamicArray<ids::FunctionId> result_ids = DynamicArray<ids::FunctionId>::create_with({});
JaktInternal::Optional<ids::ScopeId> result_scope = JaktInternal::OptionalNone();
TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>(parent_scope_id,(([function_name, &result_ids, &result_scope, this](types::ResolutionMixin mixin, JaktInternal::Optional<ByteString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> {{
if ((!(((mixin).mixin_functions)))){
return utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>::Continue();
}
NonnullRefPtr<types::Scope> const scope = ((*this).get_scope(((mixin).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const maybe_functions = ((((scope)->functions)).get(function_name));
if (((maybe_functions).has_value())){
((result_ids).push_values((((maybe_functions.value())))));
if ((!(((result_scope).has_value())))){
(result_scope = ((mixin).scope_id));
}
}
return utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>::Continue();
}
}
)),ignore_mixin_scopes,root_scope))));
if ((!(result_scope).has_value())){
return JaktInternal::OptionalNone();
}
return (Tuple{result_ids, (result_scope.value())});
}
}

ErrorOr<JaktInternal::Optional<ids::StructId>> types::CheckedProgram::check_and_extract_weak_ptr(ids::StructId const struct_id,JaktInternal::DynamicArray<ids::TypeId> const args) const {
{
ids::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("WeakPtr"sv))))));
if (((struct_id).equals(weak_ptr_struct_id))){
if (((((args).size())) != (static_cast<size_t>(1ULL)))){
((((*this).compiler))->panic(__jakt_format((StringView::from_string_literal("Internal error: Generic type is WeakPtr but there are not exactly 1 type parameter. There are {} parameters."sv)),((args).size()))));
}
ids::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
NonnullRefPtr<typename types::Type> const inner_type = ((*this).get_type(inner_type_id));
if (((inner_type)->__jakt_init_index() == 24 /* Struct */)){
ids::StructId const inner_struct_id = (inner_type)->as.Struct.value;
return inner_struct_id;
}
utility::panic(__jakt_format((StringView::from_string_literal("Internal error: Inner type of WeakPtr is not a struct. It is {}."sv)),inner_type));
}
else {
return JaktInternal::OptionalNone();
}

}
}

ErrorOr<ByteString> types::CheckedProgram::type_name(ids::TypeId const type_id,bool const debug_mode) const {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return ((((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (((((type)->common.init_common.qualifiers)).is_immutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("const "sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})) + (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<ByteString>> {
auto __jakt_enum_value = (debug_mode);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((__jakt_format((StringView::from_string_literal("({}@{}) "sv)),((type_id).id),((((type_id).module)).id))) + (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("var "sv)));
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
}))));
}
else {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))) + (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Never */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("never"sv)));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("f32"sv)));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("f64"sv)));
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
case 12 /* Usize */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("usize"sv)));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("c_char"sv)));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("c_int"sv)));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("bool"sv)));
};/*case end*/
case 0 /* Void */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("void"sv)));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("unknown"sv)));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("builtin(String)"sv)));
};/*case end*/
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("{}::{}"sv)),TRY((((*this).type_name(namespace_type,debug_mode)))),name));
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_trait(id)))->name));
};/*case end*/
case 31 /* Self */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Self"sv)));
};/*case end*/
case 30 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_146; {
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
((param_names).push(TRY((((*this).type_name(x,debug_mode))))));
}

}
}

ByteString const return_type = TRY((((*this).type_name(return_type_id,debug_mode))));
__jakt_var_146 = __jakt_format((StringView::from_string_literal("fn({}) -> {}"sv)),utility::join(param_names,(ByteString::from_utf8_without_validation(", "sv))),return_type); goto __jakt_label_140;

}
__jakt_label_140:; __jakt_var_146.release_value(); }));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_enum(id))).name));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_struct(id))).name));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_147; {
ByteString output = __jakt_format((StringView::from_string_literal("enum {}"sv)),((((*this).get_enum(id))).name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
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
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((((*this).type_name(arg,debug_mode)))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(">"sv)));
__jakt_var_147 = output; goto __jakt_label_141;

}
__jakt_label_141:; __jakt_var_147.release_value(); }));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_148; {
ByteString output = __jakt_format((StringView::from_string_literal("trait {}"sv)),((((*this).get_trait(id)))->name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
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
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((((*this).type_name(arg,debug_mode)))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(">"sv)));
__jakt_var_148 = output; goto __jakt_label_142;

}
__jakt_label_142:; __jakt_var_148.release_value(); }));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_149; {
ids::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
ids::StructId const dictionary_struct_id = TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("Dictionary"sv))))));
ids::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("Optional"sv))))));
ids::StructId const range_struct_id = TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("Range"sv))))));
ids::StructId const set_struct_id = TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("Set"sv))))));
ids::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("Tuple"sv))))));
ids::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude((ByteString::from_utf8_without_validation("WeakPtr"sv))))));
ByteString output = (ByteString::from_utf8_without_validation(""sv));
if (((id).equals(array_struct_id))){
(output = __jakt_format((StringView::from_string_literal("[{}]"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))));
}
else if (((id).equals(dictionary_struct_id))){
(output = __jakt_format((StringView::from_string_literal("[{}:{}]"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode)))),TRY((((*this).type_name(((args)[static_cast<i64>(1LL)]),debug_mode))))));
}
else if (((id).equals(optional_struct_id))){
(output = __jakt_format((StringView::from_string_literal("{}?"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))));
}
else if (((id).equals(range_struct_id))){
(output = __jakt_format((StringView::from_string_literal("{}..{}"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode)))),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))));
}
else if (((id).equals(set_struct_id))){
(output = __jakt_format((StringView::from_string_literal("{{{}}}"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))));
}
else if (((id).equals(tuple_struct_id))){
(output = (ByteString::from_utf8_without_validation("("sv)));
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
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((((*this).type_name(arg,debug_mode)))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(")"sv)));
}
else if (((id).equals(weak_ptr_struct_id))){
(output = __jakt_format((StringView::from_string_literal("weak {}"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))));
}
else {
types::CheckedStruct const structure = ((*this).get_struct(id));
(output = ((structure).name));
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
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
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((((*this).type_name(arg,debug_mode)))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(">"sv)));
}

__jakt_var_149 = output; goto __jakt_label_143;

}
__jakt_label_143:; __jakt_var_149.release_value(); }));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<ByteString> __jakt_var_150; {
ByteString output = ((((*this).get_struct(id))).name);
bool first = true;
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation("<"sv)));
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
[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(", "sv)));
}
else {
(first = false);
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,TRY((((*this).type_name(type_id,debug_mode)))));
}

}
}

[](ByteString& self, ByteString rhs) -> void {{
(self = ((self) + (rhs)));
}
}
(output,(ByteString::from_utf8_without_validation(">"sv)));
__jakt_var_150 = output; goto __jakt_label_144;

}
__jakt_label_144:; __jakt_var_150.release_value(); }));
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("raw {}"sv)),TRY((((*this).type_name(type_id,debug_mode))))));
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("&{}"sv)),TRY((((*this).type_name(type_id,debug_mode))))));
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(__jakt_format((StringView::from_string_literal("&mut {}"sv)),TRY((((*this).type_name(type_id,debug_mode))))));
};/*case end*/
case 32 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::comptime_format_impl((ByteString::from_utf8_without_validation("comptime {}"sv)),((DynamicArray<types::Value>::create_with({value}))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})]),((*this))))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
}
}

ids::TypeId types::CheckedProgram::find_or_add_type_id(NonnullRefPtr<typename types::Type> const type,ids::ModuleId const module_id,bool const only_in_current_module) {
{
if (only_in_current_module){
JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> const& types = ((((((*this).get_module(module_id)))->types)));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((types))).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t id = (_magic_value.value());
{
if (((((((types)))[id]))->equals(type))){
return ids::TypeId(module_id,id);
}
}

}
}

}
else {
{
JaktInternal::ArrayIterator<NonnullRefPtr<types::Module>> _magic = ((((*this).modules)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<types::Module>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<types::Module> module = (_magic_value.value());
{
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((module)->types)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t id = (_magic_value.value());
{
if (((((((module)->types))[id]))->equals(type))){
return ids::TypeId(((module)->id),id);
}
}

}
}

}

}
}

}

((((((((*this).modules))[((module_id).id)]))->types)).push(type));
return ids::TypeId(module_id,JaktInternal::checked_sub(((((((((*this).modules))[((module_id).id)]))->types)).size()),static_cast<size_t>(1ULL)));
}
}

ErrorOr<ids::TypeId> types::CheckedProgram::substitute_typevars_in_type(ids::TypeId const type_id,types::GenericInferences const generic_inferences,ids::ModuleId const module_id) {
{
ids::TypeId result = TRY((((*this).substitute_typevars_in_type_helper(type_id,generic_inferences,module_id))));
for (;;){
ids::TypeId const fixed_point = TRY((((*this).substitute_typevars_in_type_helper(type_id,generic_inferences,module_id))));
if (((fixed_point).equals(result))){
break;
}
else {
(result = fixed_point);
}

}
return result;
}
}

ErrorOr<ids::TypeId> types::CheckedProgram::substitute_typevars_in_type_helper(ids::TypeId const type_id,types::GenericInferences const generic_inferences,ids::ModuleId const module_id) {
{
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(type_id));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ids::TypeId>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
{
JaktInternal::Optional<ids::TypeId> const replacement_type_id = ((generic_inferences).get(type_id));
if (((replacement_type_id).has_value())){
return (replacement_type_id.value());
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
{
ids::TypeId const mapped_type_id = TRY((((*this).substitute_typevars_in_type(namespace_type,generic_inferences,module_id))));
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(mapped_type_id));
if (((type)->__jakt_init_index() == 18 /* TypeVariable */)){
return ((*this).find_or_add_type_id(types::Type::Dependent(parser::CheckedQualifiers(false),mapped_type_id,name),module_id,false));
}
JaktInternal::Optional<types::StructLikeId> const struct_like_id = types::StructLikeId::from_type_id(mapped_type_id,((*this)));
if (((struct_like_id).has_value())){
ids::ScopeId const scope_id = (((struct_like_id.value())).associated_scope_id(((*this))));
JaktInternal::Optional<ids::TypeId> const found_type = TRY((((*this).find_type_in_scope(scope_id,name,false,JaktInternal::OptionalNone()))));
if (((found_type).has_value())){
types::GenericInferences copied_inferences = generic_inferences;
if ((((((struct_like_id.value())).common.init_common.generic_arguments)).has_value())){
((copied_inferences).set_all((((struct_like_id.value())).generic_parameters_as_checked(((*this)))),((((struct_like_id.value())).common.init_common.generic_arguments).value())));
}
return TRY((((*this).substitute_typevars_in_type((found_type.value()),copied_inferences,module_id))));
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
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<ids::TypeId> new_args = DynamicArray<ids::TypeId>::create_with({});
((new_args).ensure_capacity(((args).size())));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
((new_args).push(TRY((((*this).substitute_typevars_in_type(arg,generic_inferences,module_id))))));
}

}
}

return ((*this).find_or_add_type_id(types::Type::GenericTraitInstance(parser::CheckedQualifiers(false),id,new_args),module_id,false));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<ids::TypeId> new_args = DynamicArray<ids::TypeId>::create_with({});
((new_args).ensure_capacity(((args).size())));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
((new_args).push(TRY((((*this).substitute_typevars_in_type(arg,generic_inferences,module_id))))));
}

}
}

return ((*this).find_or_add_type_id(types::Type::GenericInstance(parser::CheckedQualifiers(false),id,new_args),module_id,false));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<ids::TypeId> new_args = DynamicArray<ids::TypeId>::create_with({});
((new_args).ensure_capacity(((args).size())));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
((new_args).push(TRY((((*this).substitute_typevars_in_type(arg,generic_inferences,module_id))))));
}

}
}

return ((*this).find_or_add_type_id(types::Type::GenericEnumInstance(parser::CheckedQualifiers(false),id,new_args),module_id,false));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const struct_ = ((*this).get_struct(struct_id));
if ((!(((((struct_).generic_parameters)).is_empty())))){
JaktInternal::DynamicArray<ids::TypeId> new_args = DynamicArray<ids::TypeId>::create_with({});
((new_args).ensure_capacity(((((struct_).generic_parameters)).size())));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter arg = (_magic_value.value());
{
((new_args).push(TRY((((*this).substitute_typevars_in_type(((arg).type_id),generic_inferences,module_id))))));
}

}
}

return ((*this).find_or_add_type_id(types::Type::GenericInstance(parser::CheckedQualifiers(false),struct_id,new_args),module_id,false));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
if ((!(((((enum_).generic_parameters)).is_empty())))){
JaktInternal::DynamicArray<ids::TypeId> new_args = DynamicArray<ids::TypeId>::create_with({});
((new_args).ensure_capacity(((((enum_).generic_parameters)).size())));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter arg = (_magic_value.value());
{
((new_args).push(TRY((((*this).substitute_typevars_in_type(((arg).type_id),generic_inferences,module_id))))));
}

}
}

return ((*this).find_or_add_type_id(types::Type::GenericEnumInstance(parser::CheckedQualifiers(false),enum_id,new_args),module_id,false));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;ids::TypeId const& rawptr_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename types::Type> const rawptr_type = types::Type::RawPtr(parser::CheckedQualifiers(false),TRY((((*this).substitute_typevars_in_type(rawptr_type_id,generic_inferences,module_id)))));
return ((*this).find_or_add_type_id(rawptr_type,module_id,false));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;ids::TypeId const& ref_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename types::Type> const ref_type = types::Type::Reference(parser::CheckedQualifiers(false),TRY((((*this).substitute_typevars_in_type(ref_type_id,generic_inferences,module_id)))));
return ((*this).find_or_add_type_id(ref_type,module_id,false));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;ids::TypeId const& ref_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename types::Type> const ref_type = types::Type::MutableReference(parser::CheckedQualifiers(false),TRY((((*this).substitute_typevars_in_type(ref_type_id,generic_inferences,module_id)))));
return ((*this).find_or_add_type_id(ref_type,module_id,false));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
{
JaktInternal::DynamicArray<ids::TypeId> new_params = DynamicArray<ids::TypeId>::create_with({});
((new_params).ensure_capacity(((params).size())));
bool is_different = false;
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId param = (_magic_value.value());
{
ids::TypeId const new_param = TRY((((*this).substitute_typevars_in_type(param,generic_inferences,module_id))));
(is_different = (is_different || (!(((new_param).equals(param))))));
((new_params).push(new_param));
}

}
}

ids::TypeId const return_type_substitute = TRY((((*this).substitute_typevars_in_type(return_type_id,generic_inferences,module_id))));
(is_different = (is_different || (!(((return_type_substitute).equals(return_type_id))))));
if ((!(is_different))){
return type_id;
}
NonnullRefPtr<types::CheckedFunction> const previous_function = ((*this).get_function(pseudo_function_id));
JaktInternal::DynamicArray<types::CheckedParameter> replacement_params = DynamicArray<types::CheckedParameter>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((previous_function)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
types::CheckedParameter const param = ((((previous_function)->params))[i]);
types::CheckedParameter const new_param = types::CheckedParameter(((param).requires_label),types::CheckedVariable::__jakt_create(((((param).variable))->name),((new_params)[i]),((((param).variable))->is_mutable),((((param).variable))->definition_span),((((param).variable))->type_span),((((param).variable))->visibility),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()),((param).default_value_expression));
((replacement_params).push(new_param));
}

}
}

NonnullRefPtr<types::CheckedFunction> const new_function = types::CheckedFunction::__jakt_create(((previous_function)->name),((previous_function)->name_span),((previous_function)->visibility),return_type_substitute,((previous_function)->return_type_span),replacement_params,((previous_function)->generics),((previous_function)->block),can_throw,((previous_function)->type),((previous_function)->linkage),((previous_function)->function_scope_id),((previous_function)->struct_id),((previous_function)->is_instantiated),((previous_function)->parsed_function),((previous_function)->is_comptime),((previous_function)->is_virtual),((previous_function)->is_override),((previous_function)->is_unsafe),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),parser::InlineState::Default());
ids::FunctionId const new_function_id = ((((((*this).modules))[((module_id).id)]))->add_function(new_function));
return ((*this).find_or_add_type_id(types::Type::Function(parser::CheckedQualifiers(false),new_params,can_throw,return_type_substitute,new_function_id),module_id,false));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
return type_id;
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
return type_id;
}
}

types::CheckedProgram::CheckedProgram(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> a_modules, JaktInternal::Dictionary<ByteString,types::LoadedModule> a_loaded_modules): compiler(move(a_compiler)), modules(move(a_modules)), loaded_modules(move(a_loaded_modules)){}
NonnullRefPtr<CheckedProgram> types::CheckedProgram::__jakt_create(NonnullRefPtr<compiler::Compiler> compiler, JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> modules, JaktInternal::Dictionary<ByteString,types::LoadedModule> loaded_modules) { auto o = adopt_ref(*new CheckedProgram (move(compiler), move(modules), move(loaded_modules))); return o; }
ByteString types::Value::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Value("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("impl: {}, ", impl);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("span: {}", span);
}
builder.append(")"sv);return builder.to_string(); }
types::Value types::Value::copy() const {
{
return types::Value(((((*this).impl))->copy()),((*this).span));
}
}

ByteString types::Value::type_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *((*this).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
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
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("i18"sv)));
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
case 12 /* USize */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("usize"sv)));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("String"sv)));
};/*case end*/
case 14 /* StringView */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("StringView"sv)));
};/*case end*/
case 15 /* CChar */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("c_char"sv)));
};/*case end*/
case 16 /* CInt */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("c_int"sv)));
};/*case end*/
case 17 /* Struct */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("struct <T>"sv)));
};/*case end*/
case 18 /* Class */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("class <T>"sv)));
};/*case end*/
case 19 /* Enum */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("enum <T>"sv)));
};/*case end*/
case 20 /* JaktArray */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Array"sv)));
};/*case end*/
case 21 /* JaktDictionary */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Dictionary"sv)));
};/*case end*/
case 22 /* JaktSet */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Set"sv)));
};/*case end*/
case 23 /* RawPtr */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("raw <T>"sv)));
};/*case end*/
case 24 /* OptionalSome */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Some"sv)));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("None"sv)));
};/*case end*/
case 26 /* JaktTuple */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Tuple"sv)));
};/*case end*/
case 27 /* Function */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Function"sv)));
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

types::Value types::Value::cast(types::Value const expected,utility::Span const span) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((*this).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::U16((infallible_integer_cast<u16>((value)))),span));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::U32((infallible_integer_cast<u32>((value)))),span));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::U64((infallible_integer_cast<u64>((value)))),span));
};/*case end*/
case 12 /* USize */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::USize((infallible_integer_cast<size_t>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::U32((infallible_integer_cast<u32>((value)))),span));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::U64((infallible_integer_cast<u64>((value)))),span));
};/*case end*/
case 12 /* USize */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::USize((infallible_integer_cast<size_t>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::U64((infallible_integer_cast<u64>((value)))),span));
};/*case end*/
case 12 /* USize */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::USize((infallible_integer_cast<size_t>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::USize((infallible_integer_cast<size_t>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::I16((infallible_integer_cast<i16>((value)))),span));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::I32((infallible_integer_cast<i32>((value)))),span));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::I64((infallible_integer_cast<i64>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::I32((infallible_integer_cast<i32>((value)))),span));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::I64((infallible_integer_cast<i64>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::I64((infallible_integer_cast<i64>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::USize((infallible_integer_cast<size_t>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::U64((infallible_integer_cast<u64>((value)))),span));
};/*case end*/
case 16 /* CInt */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::CInt((infallible_integer_cast<int>((value)))),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 24 /* OptionalSome */: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, types::Value>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::OptionalSome(*this),span));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(types::Value(types::ValueImpl::OptionalSome(*this),span));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(*this);
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
}
}

types::Value::Value(NonnullRefPtr<typename types::ValueImpl> a_impl, utility::Span a_span): impl(move(a_impl)), span(move(a_span)){}

ByteString types::TypecheckFunctions::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("TypecheckFunctions("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("block: {}, ", block);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("register_function: {}", register_function);
}
builder.append(")"sv);return builder.to_string(); }
types::TypecheckFunctions::TypecheckFunctions(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>, JaktInternal::Optional<ids::FunctionId>)> a_block, Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> a_register_function): block(move(a_block)), register_function(move(a_register_function)){}
NonnullRefPtr<TypecheckFunctions> types::TypecheckFunctions::__jakt_create(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>, JaktInternal::Optional<ids::FunctionId>)> block, Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> register_function) { auto o = adopt_ref(*new TypecheckFunctions (move(block), move(register_function))); return o; }
ByteString types::StructOrEnumId::debug_description() const {
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
[[nodiscard]] StructOrEnumId StructOrEnumId::Struct(ids::StructId value){
StructOrEnumId __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Struct.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StructOrEnumId StructOrEnumId::Enum(ids::EnumId value){
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
ByteString types::StructLikeId::debug_description() const {
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
[[nodiscard]] StructLikeId StructLikeId::Struct(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments, ids::StructId value){
StructLikeId __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.generic_arguments) (decltype(generic_arguments))(move(generic_arguments));
new (&__jakt_uninit_enum.as.Struct.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StructLikeId StructLikeId::Enum(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments, ids::EnumId value){
StructLikeId __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.generic_arguments) (decltype(generic_arguments))(move(generic_arguments));
new (&__jakt_uninit_enum.as.Enum.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StructLikeId StructLikeId::Trait(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> generic_arguments, ids::TraitId value){
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
JaktInternal::DynamicArray<ids::TypeId> types::StructLikeId::generic_parameters(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::CheckedGenericParameter>, JaktInternal::DynamicArray<ids::TypeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_struct(id))).generic_parameters));
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_enum(id))).generic_parameters));
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_trait(id)))->generic_parameters));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<ids::TypeId> result = DynamicArray<ids::TypeId>::create_with({});
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((parameters).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter parameter = (_magic_value.value());
{
((result).push(((parameter).type_id)));
}

}
}

return result;
}
}

JaktInternal::DynamicArray<types::CheckedGenericParameter> types::StructLikeId::generic_parameters_as_checked(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::CheckedGenericParameter>, JaktInternal::DynamicArray<types::CheckedGenericParameter>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_struct(id))).generic_parameters));
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_enum(id))).generic_parameters));
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_trait(id)))->generic_parameters));
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

ids::ScopeId types::StructLikeId::scope_id(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::ScopeId, ids::ScopeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_struct(id))).scope_id));
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_enum(id))).scope_id));
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_trait(id)))->scope_id));
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

ids::TypeId types::StructLikeId::specialized_by(JaktInternal::DynamicArray<ids::TypeId> const arguments,NonnullRefPtr<types::CheckedProgram>& program,ids::ModuleId const module_id,parser::CheckedQualifiers const qualifiers) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)))->find_or_add_type_id(types::Type::GenericInstance(qualifiers,id,arguments),module_id,false)));
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)))->find_or_add_type_id(types::Type::GenericEnumInstance(qualifiers,id,arguments),module_id,false)));
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)))->find_or_add_type_id(types::Type::GenericTraitInstance(qualifiers,id,arguments),module_id,false)));
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

JaktInternal::Optional<types::StructLikeId> types::StructLikeId::from_type_id(ids::TypeId const type_id,NonnullRefPtr<types::CheckedProgram> const& program) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructLikeId>, JaktInternal::Optional<types::StructLikeId>>{
auto&& __jakt_match_variant = *((((program)))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(types::StructLikeId::Struct(args,struct_id));
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = DynamicArray<ids::TypeId>::create_with({});
return JaktInternal::ExplicitValue(types::StructLikeId::Struct(args,struct_id));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(types::StructLikeId::Enum(args,enum_id));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = DynamicArray<ids::TypeId>::create_with({});
return JaktInternal::ExplicitValue(types::StructLikeId::Enum(args,enum_id));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& trait_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(types::StructLikeId::Trait(args,trait_id));
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& trait_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = DynamicArray<ids::TypeId>::create_with({});
return JaktInternal::ExplicitValue(types::StructLikeId::Trait(args,trait_id));
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

ids::ScopeId types::StructLikeId::associated_scope_id(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::ScopeId, ids::ScopeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_struct(id))).scope_id));
};/*case end*/
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_enum(id))).scope_id));
};/*case end*/
case 2 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_trait(id)))->scope_id));
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

ByteString types::SafetyMode::debug_description() const {
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
ByteString types::BuiltinType::debug_description() const {
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
size_t types::BuiltinType::id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(3ULL));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(5ULL));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(6ULL));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(7ULL));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(9ULL));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(10ULL));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(11ULL));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(12ULL));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(13ULL));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(14ULL));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(15ULL));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(16ULL));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(17ULL));
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

ByteString types::BuiltinType::constructor_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Void"sv)));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Bool"sv)));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("U8"sv)));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("U16"sv)));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("U32"sv)));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("U64"sv)));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("I8"sv)));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("I16"sv)));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("I32"sv)));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("I64"sv)));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("F32"sv)));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("F64"sv)));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Usize"sv)));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("JaktString"sv)));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("CChar"sv)));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("CInt"sv)));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Unknown"sv)));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Never"sv)));
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

ByteString types::Type::debug_description() const {
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
builder.appendff("name: \"{}\"", that.name);
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
case 23 /* GenericResolvedType */: {
builder.append("Type::GenericResolvedType"sv);
[[maybe_unused]] auto const& that = this->as.GenericResolvedType;
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
case 24 /* Struct */: {
builder.append("Type::Struct"sv);
[[maybe_unused]] auto const& that = this->as.Struct;
builder.appendff("({})", that.value);
break;}
case 25 /* Enum */: {
builder.append("Type::Enum"sv);
[[maybe_unused]] auto const& that = this->as.Enum;
builder.appendff("({})", that.value);
break;}
case 26 /* RawPtr */: {
builder.append("Type::RawPtr"sv);
[[maybe_unused]] auto const& that = this->as.RawPtr;
builder.appendff("({})", that.value);
break;}
case 27 /* Trait */: {
builder.append("Type::Trait"sv);
[[maybe_unused]] auto const& that = this->as.Trait;
builder.appendff("({})", that.value);
break;}
case 28 /* Reference */: {
builder.append("Type::Reference"sv);
[[maybe_unused]] auto const& that = this->as.Reference;
builder.appendff("({})", that.value);
break;}
case 29 /* MutableReference */: {
builder.append("Type::MutableReference"sv);
[[maybe_unused]] auto const& that = this->as.MutableReference;
builder.appendff("({})", that.value);
break;}
case 30 /* Function */: {
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
case 31 /* Self */: {
return ByteString("Type::Self"sv);
break;}
case 32 /* Const */: {
builder.append("Type::Const"sv);
[[maybe_unused]] auto const& that = this->as.Const;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] NonnullRefPtr<Type> Type::Void(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Bool(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::U8(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::U16(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::U32(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::U64(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::I8(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::I16(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::I32(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::I64(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::F32(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::F64(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Usize(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::JaktString(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::CChar(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::CInt(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 16;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Unknown(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 17;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Never(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 18;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::TypeVariable(parser::CheckedQualifiers qualifiers, ByteString name, JaktInternal::DynamicArray<ids::TypeId> trait_implementations, bool is_value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 19;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.TypeVariable.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum->as.TypeVariable.trait_implementations) (decltype(trait_implementations))(move(trait_implementations));
new (&__jakt_uninit_enum->as.TypeVariable.is_value) (decltype(is_value))(move(is_value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Dependent(parser::CheckedQualifiers qualifiers, ids::TypeId namespace_type, ByteString name){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 20;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Dependent.namespace_type) (decltype(namespace_type))(move(namespace_type));
new (&__jakt_uninit_enum->as.Dependent.name) (decltype(name))(move(name));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::GenericInstance(parser::CheckedQualifiers qualifiers, ids::StructId id, JaktInternal::DynamicArray<ids::TypeId> args){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 21;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.GenericInstance.id) (decltype(id))(move(id));
new (&__jakt_uninit_enum->as.GenericInstance.args) (decltype(args))(move(args));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::GenericEnumInstance(parser::CheckedQualifiers qualifiers, ids::EnumId id, JaktInternal::DynamicArray<ids::TypeId> args){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 22;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.GenericEnumInstance.id) (decltype(id))(move(id));
new (&__jakt_uninit_enum->as.GenericEnumInstance.args) (decltype(args))(move(args));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::GenericTraitInstance(parser::CheckedQualifiers qualifiers, ids::TraitId id, JaktInternal::DynamicArray<ids::TypeId> args){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 23;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.GenericTraitInstance.id) (decltype(id))(move(id));
new (&__jakt_uninit_enum->as.GenericTraitInstance.args) (decltype(args))(move(args));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::GenericResolvedType(parser::CheckedQualifiers qualifiers, ids::StructId id, JaktInternal::DynamicArray<ids::TypeId> args){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 24;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.GenericResolvedType.id) (decltype(id))(move(id));
new (&__jakt_uninit_enum->as.GenericResolvedType.args) (decltype(args))(move(args));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Struct(parser::CheckedQualifiers qualifiers, ids::StructId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 25;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Struct.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Enum(parser::CheckedQualifiers qualifiers, ids::EnumId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 26;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Enum.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::RawPtr(parser::CheckedQualifiers qualifiers, ids::TypeId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 27;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.RawPtr.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Trait(parser::CheckedQualifiers qualifiers, ids::TraitId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 28;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Trait.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Reference(parser::CheckedQualifiers qualifiers, ids::TypeId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 29;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Reference.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::MutableReference(parser::CheckedQualifiers qualifiers, ids::TypeId value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 30;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.MutableReference.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Function(parser::CheckedQualifiers qualifiers, JaktInternal::DynamicArray<ids::TypeId> params, bool can_throw, ids::TypeId return_type_id, ids::FunctionId pseudo_function_id){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 31;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
new (&__jakt_uninit_enum->as.Function.params) (decltype(params))(move(params));
new (&__jakt_uninit_enum->as.Function.can_throw) (decltype(can_throw))(move(can_throw));
new (&__jakt_uninit_enum->as.Function.return_type_id) (decltype(return_type_id))(move(return_type_id));
new (&__jakt_uninit_enum->as.Function.pseudo_function_id) (decltype(pseudo_function_id))(move(pseudo_function_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Self(parser::CheckedQualifiers qualifiers){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 32;
new (&__jakt_uninit_enum->common.init_common.qualifiers) (decltype(qualifiers))(move(qualifiers));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<Type> Type::Const(parser::CheckedQualifiers qualifiers, types::Value value){
NonnullRefPtr<Type> __jakt_uninit_enum = adopt_ref(*new Type);
__jakt_uninit_enum->__jakt_variant_index = 33;
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
case 23 /* GenericResolvedType */:
new (&this->as.GenericResolvedType.id) (decltype(this->as.GenericResolvedType.id))(rhs.as.GenericResolvedType.id);
new (&this->as.GenericResolvedType.args) (decltype(this->as.GenericResolvedType.args))(rhs.as.GenericResolvedType.args);
break;
case 24 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 25 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 26 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(rhs.as.RawPtr.value);
break;
case 27 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
case 28 /* Reference */:
new (&this->as.Reference.value) (decltype(this->as.Reference.value))(rhs.as.Reference.value);
break;
case 29 /* MutableReference */:
new (&this->as.MutableReference.value) (decltype(this->as.MutableReference.value))(rhs.as.MutableReference.value);
break;
case 30 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(rhs.as.Function.return_type_id);
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(rhs.as.Function.pseudo_function_id);
break;
case 31 /* Self */:
break;
case 32 /* Const */:
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
case 23 /* GenericResolvedType */:
this->as.GenericResolvedType.id = rhs.as.GenericResolvedType.id;
this->as.GenericResolvedType.args = rhs.as.GenericResolvedType.args;
break;
case 24 /* Struct */:
this->as.Struct.value = rhs.as.Struct.value;
break;
case 25 /* Enum */:
this->as.Enum.value = rhs.as.Enum.value;
break;
case 26 /* RawPtr */:
this->as.RawPtr.value = rhs.as.RawPtr.value;
break;
case 27 /* Trait */:
this->as.Trait.value = rhs.as.Trait.value;
break;
case 28 /* Reference */:
this->as.Reference.value = rhs.as.Reference.value;
break;
case 29 /* MutableReference */:
this->as.MutableReference.value = rhs.as.MutableReference.value;
break;
case 30 /* Function */:
this->as.Function.params = rhs.as.Function.params;
this->as.Function.can_throw = rhs.as.Function.can_throw;
this->as.Function.return_type_id = rhs.as.Function.return_type_id;
this->as.Function.pseudo_function_id = rhs.as.Function.pseudo_function_id;
break;
case 31 /* Self */:
break;
case 32 /* Const */:
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
case 23 /* GenericResolvedType */:
new (&this->as.GenericResolvedType.id) (decltype(this->as.GenericResolvedType.id))(rhs.as.GenericResolvedType.id);
new (&this->as.GenericResolvedType.args) (decltype(this->as.GenericResolvedType.args))(rhs.as.GenericResolvedType.args);
break;
case 24 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(rhs.as.Struct.value);
break;
case 25 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(rhs.as.Enum.value);
break;
case 26 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(rhs.as.RawPtr.value);
break;
case 27 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(rhs.as.Trait.value);
break;
case 28 /* Reference */:
new (&this->as.Reference.value) (decltype(this->as.Reference.value))(rhs.as.Reference.value);
break;
case 29 /* MutableReference */:
new (&this->as.MutableReference.value) (decltype(this->as.MutableReference.value))(rhs.as.MutableReference.value);
break;
case 30 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(rhs.as.Function.params);
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(rhs.as.Function.can_throw);
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(rhs.as.Function.return_type_id);
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(rhs.as.Function.pseudo_function_id);
break;
case 31 /* Self */:
break;
case 32 /* Const */:
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
case 23 /* GenericResolvedType */:
new (&this->as.GenericResolvedType.id) (decltype(this->as.GenericResolvedType.id))(move(rhs.as.GenericResolvedType.id));
new (&this->as.GenericResolvedType.args) (decltype(this->as.GenericResolvedType.args))(move(rhs.as.GenericResolvedType.args));
break;
case 24 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 25 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 26 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(move(rhs.as.RawPtr.value));
break;
case 27 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
case 28 /* Reference */:
new (&this->as.Reference.value) (decltype(this->as.Reference.value))(move(rhs.as.Reference.value));
break;
case 29 /* MutableReference */:
new (&this->as.MutableReference.value) (decltype(this->as.MutableReference.value))(move(rhs.as.MutableReference.value));
break;
case 30 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(move(rhs.as.Function.return_type_id));
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(move(rhs.as.Function.pseudo_function_id));
break;
case 31 /* Self */:
break;
case 32 /* Const */:
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
case 23 /* GenericResolvedType */:
this->as.GenericResolvedType.id = move(rhs.as.GenericResolvedType.id);
this->as.GenericResolvedType.args = move(rhs.as.GenericResolvedType.args);
break;
case 24 /* Struct */:
this->as.Struct.value = move(rhs.as.Struct.value);
break;
case 25 /* Enum */:
this->as.Enum.value = move(rhs.as.Enum.value);
break;
case 26 /* RawPtr */:
this->as.RawPtr.value = move(rhs.as.RawPtr.value);
break;
case 27 /* Trait */:
this->as.Trait.value = move(rhs.as.Trait.value);
break;
case 28 /* Reference */:
this->as.Reference.value = move(rhs.as.Reference.value);
break;
case 29 /* MutableReference */:
this->as.MutableReference.value = move(rhs.as.MutableReference.value);
break;
case 30 /* Function */:
this->as.Function.params = move(rhs.as.Function.params);
this->as.Function.can_throw = move(rhs.as.Function.can_throw);
this->as.Function.return_type_id = move(rhs.as.Function.return_type_id);
this->as.Function.pseudo_function_id = move(rhs.as.Function.pseudo_function_id);
break;
case 31 /* Self */:
break;
case 32 /* Const */:
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
case 23 /* GenericResolvedType */:
new (&this->as.GenericResolvedType.id) (decltype(this->as.GenericResolvedType.id))(move(rhs.as.GenericResolvedType.id));
new (&this->as.GenericResolvedType.args) (decltype(this->as.GenericResolvedType.args))(move(rhs.as.GenericResolvedType.args));
break;
case 24 /* Struct */:
new (&this->as.Struct.value) (decltype(this->as.Struct.value))(move(rhs.as.Struct.value));
break;
case 25 /* Enum */:
new (&this->as.Enum.value) (decltype(this->as.Enum.value))(move(rhs.as.Enum.value));
break;
case 26 /* RawPtr */:
new (&this->as.RawPtr.value) (decltype(this->as.RawPtr.value))(move(rhs.as.RawPtr.value));
break;
case 27 /* Trait */:
new (&this->as.Trait.value) (decltype(this->as.Trait.value))(move(rhs.as.Trait.value));
break;
case 28 /* Reference */:
new (&this->as.Reference.value) (decltype(this->as.Reference.value))(move(rhs.as.Reference.value));
break;
case 29 /* MutableReference */:
new (&this->as.MutableReference.value) (decltype(this->as.MutableReference.value))(move(rhs.as.MutableReference.value));
break;
case 30 /* Function */:
new (&this->as.Function.params) (decltype(this->as.Function.params))(move(rhs.as.Function.params));
new (&this->as.Function.can_throw) (decltype(this->as.Function.can_throw))(move(rhs.as.Function.can_throw));
new (&this->as.Function.return_type_id) (decltype(this->as.Function.return_type_id))(move(rhs.as.Function.return_type_id));
new (&this->as.Function.pseudo_function_id) (decltype(this->as.Function.pseudo_function_id))(move(rhs.as.Function.pseudo_function_id));
break;
case 31 /* Self */:
break;
case 32 /* Const */:
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
case 23 /* GenericResolvedType */:this->as.GenericResolvedType.id.~StructId();
this->as.GenericResolvedType.args.~DynamicArray();
break;
case 24 /* Struct */:this->as.Struct.value.~StructId();
break;
case 25 /* Enum */:this->as.Enum.value.~EnumId();
break;
case 26 /* RawPtr */:this->as.RawPtr.value.~TypeId();
break;
case 27 /* Trait */:this->as.Trait.value.~TraitId();
break;
case 28 /* Reference */:this->as.Reference.value.~TypeId();
break;
case 29 /* MutableReference */:this->as.MutableReference.value.~TypeId();
break;
case 30 /* Function */:this->as.Function.params.~DynamicArray();
this->as.Function.return_type_id.~TypeId();
this->as.Function.pseudo_function_id.~FunctionId();
break;
case 31 /* Self */:break;
case 32 /* Const */:this->as.Const.value.~Value();
break;
}
}
JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>> types::Type::generic_parameters(NonnullRefPtr<types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>, JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>(((((program)->get_struct(id))).generic_parameters)));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>(((((program)->get_struct(id))).generic_parameters)));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>(((((program)->get_struct(id))).generic_parameters)));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>(((((program)->get_enum(id))).generic_parameters)));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>(((((program)->get_enum(id))).generic_parameters)));
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>(((((program)->get_trait(id)))->generic_parameters)));
};/*case end*/
case 22 /* GenericTraitInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>(((((program)->get_trait(id)))->generic_parameters)));
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

bool types::Type::is_boxed(NonnullRefPtr<types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)->get_struct(struct_id))).record_type)).__jakt_init_index() == 1 /* Class */));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((((program)->get_struct(struct_id))).record_type)).__jakt_init_index() == 1 /* Class */));
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_enum(enum_id))).is_boxed));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((program)->get_enum(enum_id))).is_boxed));
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
});
}
}

bool types::Type::is_concrete() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 31 /* Self */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 19 /* Dependent */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(true);
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

i64 types::Type::specificity(NonnullRefPtr<types::CheckedProgram> const program,i64 const base_specificity) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 19 /* Dependent */: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 32 /* Const */: {
return JaktInternal::ExplicitValue(base_specificity);
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<i64> __jakt_var_151; {
i64 specificity = JaktInternal::checked_div(base_specificity,static_cast<i64>(2LL));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId subtype_id = (_magic_value.value());
{
NonnullRefPtr<typename types::Type> const subtype = ((program)->get_type(subtype_id));
((specificity) += (((subtype)->specificity(program,JaktInternal::checked_div(base_specificity,static_cast<i64>(4LL))))));
}

}
}

__jakt_var_151 = specificity; goto __jakt_label_145;

}
__jakt_label_145:; __jakt_var_151.release_value(); }));
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<i64> __jakt_var_152; {
i64 specificity = JaktInternal::checked_div(base_specificity,static_cast<i64>(2LL));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId subtype_id = (_magic_value.value());
{
NonnullRefPtr<typename types::Type> const subtype = ((program)->get_type(subtype_id));
((specificity) += (((subtype)->specificity(program,JaktInternal::checked_div(base_specificity,static_cast<i64>(4LL))))));
}

}
}

__jakt_var_152 = specificity; goto __jakt_label_146;

}
__jakt_label_146:; __jakt_var_152.release_value(); }));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<i64> __jakt_var_153; {
i64 specificity = JaktInternal::checked_div(base_specificity,static_cast<i64>(2LL));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId subtype_id = (_magic_value.value());
{
NonnullRefPtr<typename types::Type> const subtype = ((program)->get_type(subtype_id));
((specificity) += (((subtype)->specificity(program,JaktInternal::checked_div(base_specificity,static_cast<i64>(4LL))))));
}

}
}

__jakt_var_153 = specificity; goto __jakt_label_147;

}
__jakt_label_147:; __jakt_var_153.release_value(); }));
};/*case end*/
case 30 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
return JaktInternal::ExplicitValue(({ Optional<i64> __jakt_var_154; {
i64 specificity = JaktInternal::checked_div(base_specificity,static_cast<i64>(2LL));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId subtype_id = (_magic_value.value());
{
NonnullRefPtr<typename types::Type> const subtype = ((program)->get_type(subtype_id));
((specificity) += (((subtype)->specificity(program,JaktInternal::checked_div(base_specificity,static_cast<i64>(4LL))))));
}

}
}

__jakt_var_154 = specificity; goto __jakt_label_148;

}
__jakt_label_148:; __jakt_var_154.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(base_specificity);
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

ByteString types::Type::constructor_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ByteString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Void"sv)));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Bool"sv)));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("U8"sv)));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("U16"sv)));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("U32"sv)));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("U64"sv)));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("I8"sv)));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("I16"sv)));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("I32"sv)));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("I64"sv)));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("F32"sv)));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("F64"sv)));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Usize"sv)));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("JaktString"sv)));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("CChar"sv)));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("CInt"sv)));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Unknown"sv)));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Never"sv)));
};/*case end*/
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("TypeVariable"sv)));
};/*case end*/
case 19 /* Dependent */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Dependent"sv)));
};/*case end*/
case 20 /* GenericInstance */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("GenericInstance"sv)));
};/*case end*/
case 21 /* GenericEnumInstance */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("GenericEnumInstance"sv)));
};/*case end*/
case 22 /* GenericTraitInstance */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("GenericTraitInstance"sv)));
};/*case end*/
case 23 /* GenericResolvedType */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("GenericResolvedType"sv)));
};/*case end*/
case 24 /* Struct */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Struct"sv)));
};/*case end*/
case 25 /* Enum */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Enum"sv)));
};/*case end*/
case 26 /* RawPtr */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("RawPtr"sv)));
};/*case end*/
case 27 /* Trait */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Trait"sv)));
};/*case end*/
case 28 /* Reference */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Reference"sv)));
};/*case end*/
case 29 /* MutableReference */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("MutableReference"sv)));
};/*case end*/
case 30 /* Function */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Function"sv)));
};/*case end*/
case 31 /* Self */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Self"sv)));
};/*case end*/
case 32 /* Const */: {
return JaktInternal::ExplicitValue((ByteString::from_utf8_without_validation("Const"sv)));
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

bool types::Type::equals(NonnullRefPtr<typename types::Type> const rhs) const {
{
return (((((rhs)->common.init_common.qualifiers)).equals(((*this).common.init_common.qualifiers))) && ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 0 /* Void */));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 1 /* Bool */));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 2 /* U8 */));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 3 /* U16 */));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 4 /* U32 */));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 5 /* U64 */));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 6 /* I8 */));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 7 /* I16 */));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 8 /* I32 */));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 9 /* I64 */));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 10 /* F32 */));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 11 /* F64 */));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 12 /* Usize */));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 13 /* JaktString */));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 14 /* CChar */));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 15 /* CInt */));
};/*case end*/
case 31 /* Self */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 31 /* Self */));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 16 /* Unknown */));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue(((rhs)->__jakt_init_index() == 17 /* Never */));
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& lhs_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_155; {
if (((rhs)->__jakt_init_index() == 18 /* TypeVariable */)){
ByteString const rhs_name = (rhs)->as.TypeVariable.name;
return ((lhs_name) == (rhs_name));
}
__jakt_var_155 = false; goto __jakt_label_149;

}
__jakt_label_149:; __jakt_var_155.release_value(); }));
};/*case end*/
case 19 /* Dependent */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Dependent;ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_156; {
if (((rhs)->__jakt_init_index() == 19 /* Dependent */)){
ids::TypeId const rhs_namespace_type = (rhs)->as.Dependent.namespace_type;
ByteString const rhs_name = (rhs)->as.Dependent.name;
return (((namespace_type).equals(rhs_namespace_type)) && ((name) == (rhs_name)));
}
__jakt_var_156 = false; goto __jakt_label_150;

}
__jakt_label_150:; __jakt_var_156.release_value(); }));
};/*case end*/
case 32 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;types::Value const& lhs_value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs;
switch(__jakt_match_variant.__jakt_init_index()) {
case 32 /* Const */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Const;types::Value const& rhs_value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((lhs_value).impl))->equals(((rhs_value).impl))));
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
}));
};/*case end*/
case 23 /* GenericResolvedType */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericResolvedType;ids::StructId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs)->__jakt_init_index() == 20 /* GenericInstance */)){
ids::StructId const rhs_id = (rhs)->as.GenericInstance.id;
JaktInternal::DynamicArray<ids::TypeId> const rhs_args = (rhs)->as.GenericInstance.args;
if ((((lhs_id).equals(rhs_id)) && ((((lhs_args).size())) == (((rhs_args).size()))))){
size_t idx = static_cast<size_t>(0ULL);
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(idx,((lhs_args).size()))){
if ((!(((((lhs_args)[idx])).equals(((rhs_args)[idx])))))){
return false;
}
((idx++));
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
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;ids::StructId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs)->__jakt_init_index() == 20 /* GenericInstance */)){
ids::StructId const rhs_id = (rhs)->as.GenericInstance.id;
JaktInternal::DynamicArray<ids::TypeId> const rhs_args = (rhs)->as.GenericInstance.args;
if ((((lhs_id).equals(rhs_id)) && ((((lhs_args).size())) == (((rhs_args).size()))))){
size_t idx = static_cast<size_t>(0ULL);
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(idx,((lhs_args).size()))){
if ((!(((((lhs_args)[idx])).equals(((rhs_args)[idx])))))){
return false;
}
((idx++));
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
auto&& __jakt_match_value = __jakt_match_variant.as.GenericTraitInstance;ids::TraitId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs)->__jakt_init_index() == 22 /* GenericTraitInstance */)){
ids::TraitId const rhs_id = (rhs)->as.GenericTraitInstance.id;
JaktInternal::DynamicArray<ids::TypeId> const rhs_args = (rhs)->as.GenericTraitInstance.args;
if ((((lhs_id).equals(rhs_id)) && ((((lhs_args).size())) == (((rhs_args).size()))))){
size_t idx = static_cast<size_t>(0ULL);
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(idx,((lhs_args).size()))){
if ((!(((((lhs_args)[idx])).equals(((rhs_args)[idx])))))){
return false;
}
((idx++));
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
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;ids::EnumId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs)->__jakt_init_index() == 21 /* GenericEnumInstance */)){
ids::EnumId const rhs_id = (rhs)->as.GenericEnumInstance.id;
JaktInternal::DynamicArray<ids::TypeId> const rhs_args = (rhs)->as.GenericEnumInstance.args;
if ((((lhs_id).equals(rhs_id)) && ((((lhs_args).size())) == (((rhs_args).size()))))){
size_t idx = static_cast<size_t>(0ULL);
while ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(idx,((lhs_args).size()))){
if ((!(((((lhs_args)[idx])).equals(((rhs_args)[idx])))))){
return false;
}
((idx++));
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
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->__jakt_init_index() == 24 /* Struct */)){
ids::StructId const rhs_id = (rhs)->as.Struct.value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->__jakt_init_index() == 25 /* Enum */)){
ids::EnumId const rhs_id = (rhs)->as.Enum.value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;ids::TypeId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->__jakt_init_index() == 26 /* RawPtr */)){
ids::TypeId const rhs_id = (rhs)->as.RawPtr.value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;ids::TypeId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->__jakt_init_index() == 28 /* Reference */)){
ids::TypeId const rhs_id = (rhs)->as.Reference.value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;ids::TypeId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->__jakt_init_index() == 29 /* MutableReference */)){
ids::TypeId const rhs_id = (rhs)->as.MutableReference.value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 27 /* Trait */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Trait;ids::TraitId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->__jakt_init_index() == 27 /* Trait */)){
ids::TraitId const rhs_id = (rhs)->as.Trait.value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 30 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
{
if (((rhs)->__jakt_init_index() == 30 /* Function */)){
JaktInternal::DynamicArray<ids::TypeId> const rhs_params = (rhs)->as.Function.params;
bool const rhs_can_throw = (rhs)->as.Function.can_throw;
ids::TypeId const rhs_return_type_id = (rhs)->as.Function.return_type_id;
if ((((((params).size())) == (((rhs_params).size()))) && (((return_type_id).equals(rhs_return_type_id)) && ((can_throw) == (rhs_can_throw))))){
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((params).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((!(((((params)[i])).equals(((rhs_params)[i])))))){
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
}));
}
}

bool types::Type::is_builtin() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(true);
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
});
}
}

types::BuiltinType types::Type::as_builtin_type() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BuiltinType, types::BuiltinType>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(types::BuiltinType::Void());
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(types::BuiltinType::Bool());
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::U8());
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::U16());
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::U32());
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::U64());
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::I8());
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::I16());
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::I32());
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::I64());
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::F32());
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(types::BuiltinType::F64());
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(types::BuiltinType::Usize());
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(types::BuiltinType::JaktString());
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(types::BuiltinType::CChar());
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(types::BuiltinType::CInt());
};/*case end*/
default: {
{
warnln((StringView::from_string_literal("Type.as_builtin_type: Not a builtin type: {}"sv)),*this);
abort();
}
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

i64 types::Type::get_bits() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(8LL));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(8LL));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(static_cast<i64>(8LL));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(16LL));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(16LL));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
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

bool types::Type::is_signed() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(true);
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
});
}
}

i64 types::Type::min() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* CChar */: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(128LL))));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(2147483648LL))));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(128LL))));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(32768LL))));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(2147483648LL))));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(JaktInternal::checked_sub((-(static_cast<i64>(9223372036854775807LL))),static_cast<i64>(1LL)));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
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

u64 types::Type::max() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, u64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(static_cast<u64>(127ULL));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(static_cast<u64>(2147483647ULL));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(static_cast<u64>(127ULL));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(static_cast<u64>(32767ULL));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(static_cast<u64>(2147483647ULL));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(static_cast<u64>(9223372036854775807ULL));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(static_cast<u64>(255ULL));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(static_cast<u64>(65535ULL));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(static_cast<u64>(4294967295ULL));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(static_cast<u64>(18446744073709551615ULL));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(static_cast<u64>(18446744073709551615ULL));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(static_cast<u64>(0ULL));
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

ids::TypeId types::Type::flip_signedness() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U8()));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U16()));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U32()));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U64()));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::I8()));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::I16()));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::I32()));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::I64()));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Unknown()));
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

ByteString types::CheckedTraitRequirements::debug_description() const {
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
[[nodiscard]] CheckedTraitRequirements CheckedTraitRequirements::Methods(JaktInternal::Dictionary<ByteString,ids::FunctionId> value){
CheckedTraitRequirements __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Methods.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedTraitRequirements CheckedTraitRequirements::ComptimeExpression(NonnullRefPtr<typename types::CheckedExpression> value){
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
ByteString types::MaybeResolvedScope::debug_description() const {
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
[[nodiscard]] NonnullRefPtr<MaybeResolvedScope> MaybeResolvedScope::Resolved(ids::ScopeId value){
NonnullRefPtr<MaybeResolvedScope> __jakt_uninit_enum = adopt_ref(*new MaybeResolvedScope);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->as.Resolved.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<MaybeResolvedScope> MaybeResolvedScope::Unresolved(NonnullRefPtr<typename types::MaybeResolvedScope> parent_scope, ByteString relative_name){
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
ErrorOr<NonnullRefPtr<typename types::MaybeResolvedScope>> types::MaybeResolvedScope::try_resolve(NonnullRefPtr<types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::MaybeResolvedScope>, ErrorOr<NonnullRefPtr<typename types::MaybeResolvedScope>>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Resolved */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Resolved;ids::ScopeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::MaybeResolvedScope::Resolved(id));
};/*case end*/
case 1 /* Unresolved */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unresolved;NonnullRefPtr<typename types::MaybeResolvedScope> const& parent_scope = __jakt_match_value.parent_scope;
ByteString const& relative_name = __jakt_match_value.relative_name;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::MaybeResolvedScope>> __jakt_var_157; {
NonnullRefPtr<typename types::MaybeResolvedScope> parent = TRY((((parent_scope)->try_resolve(program))));
if (((parent)->__jakt_init_index() == 0 /* Resolved */)){
ids::ScopeId const parent_scope_id = (parent)->as.Resolved.value;
ids::ScopeId const scope = parent_scope_id;
JaktInternal::Optional<ids::ScopeId> scope_id = JaktInternal::OptionalNone();
if ((!(((scope_id).has_value())))){
JaktInternal::Optional<ids::StructId> const struct_ = TRY((((program)->find_struct_in_scope(scope,relative_name,false,JaktInternal::OptionalNone()))));
if (((struct_).has_value())){
(scope_id = ((((program)->get_struct((struct_.value())))).scope_id));
}
}
if ((!(((scope_id).has_value())))){
JaktInternal::Optional<ids::EnumId> const enum_ = TRY((((program)->find_enum_in_scope(scope,relative_name,false,JaktInternal::OptionalNone()))));
if (((enum_).has_value())){
(scope_id = ((((program)->get_enum((enum_.value())))).scope_id));
}
}
if ((!(((scope_id).has_value())))){
JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>> const ns = TRY((((program)->find_namespace_in_scope(scope,relative_name,false,false,JaktInternal::OptionalNone()))));
if (((ns).has_value())){
(scope_id = (((ns.value())).template get<0>()));
}
}
if ((!(((scope_id).has_value())))){
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const ids = TRY((((program)->find_functions_with_name_in_scope(scope,relative_name,false,JaktInternal::OptionalNone()))));
if (((ids).has_value())){
(scope_id = ((((program)->get_function((((ids.value()))[static_cast<i64>(0LL)]))))->function_scope_id));
}
}
if (((scope_id).has_value())){
return types::MaybeResolvedScope::Resolved((scope_id.value()));
}
}
__jakt_var_157 = types::MaybeResolvedScope::Unresolved(parent,relative_name); goto __jakt_label_151;

}
__jakt_label_151:; __jakt_var_157.release_value(); }));
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

ByteString types::CheckedVisibility::debug_description() const {
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
[[nodiscard]] CheckedVisibility CheckedVisibility::Restricted(JaktInternal::DynamicArray<NonnullRefPtr<typename types::MaybeResolvedScope>> scopes, utility::Span span){
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
ByteString types::CheckedCapture::debug_description() const {
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
[[nodiscard]] CheckedCapture CheckedCapture::ByValue(ByteString name, utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedCapture CheckedCapture::ByReference(ByteString name, utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedCapture CheckedCapture::ByMutableReference(ByteString name, utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedCapture CheckedCapture::ByComptimeDependency(ByteString name, utility::Span span){
CheckedCapture __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.common.init_common.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.common.init_common.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedCapture CheckedCapture::AllByReference(ByteString name, utility::Span span){
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
ByteString types::FunctionGenericParameterKind::debug_description() const {
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
ByteString types::BlockControlFlow::debug_description() const {
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
types::BlockControlFlow types::BlockControlFlow::unify_with(types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(second);
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysReturns());
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysReturns());
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysReturns());
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(might_break));
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
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(lhs));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(lhs));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(lhs));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(lhs));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns(might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(might_break));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns((lhs || might_break)));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysReturns());
};/*case end*/
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(lhs));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
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
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(lhs));
};/*case end*/
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(lhs));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(lhs));
};/*case end*/
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns((lhs || might_break)));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(lhs));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl((lhs || might_break)));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(lhs));
};/*case end*/
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::NeverReturns());
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

types::BlockControlFlow types::BlockControlFlow::branch_unify_with(types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(second);
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysReturns());
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysReturns());
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns(might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns(might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(this_might_break));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(this_might_break));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(this_might_break));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns((might_break || this_might_break)));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns((might_break || this_might_break)));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns(this_might_break));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns(this_might_break));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns(this_might_break));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns((might_break || this_might_break)));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns((might_break || this_might_break)));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(this_might_break));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(this_might_break));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break));
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl((might_break || this_might_break)));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns((might_break || this_might_break)));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns((might_break || this_might_break)));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)));
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

types::BlockControlFlow types::BlockControlFlow::updated(types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::NeverReturns());
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysReturns());
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(second);
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
return JaktInternal::ExplicitValue(((*this).unify_with(second)));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
return JaktInternal::ExplicitValue(((*this).unify_with(second)));
};/*case end*/
case 6 /* PartialNeverReturns */: {
return JaktInternal::ExplicitValue(((*this).unify_with(second)));
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

types::BlockControlFlow types::BlockControlFlow::partial() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(false));
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns(false));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysTransfersControl(might_break));
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialAlwaysReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialAlwaysReturns(might_break));
};/*case end*/
case 6 /* PartialNeverReturns */: {
auto&& __jakt_match_value = __jakt_match_variant.as.PartialNeverReturns;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::PartialNeverReturns(might_break));
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

types::BlockControlFlow types::BlockControlFlow::definitive() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::NeverReturns());
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysReturns());
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.AlwaysTransfersControl;bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(types::BlockControlFlow::AlwaysTransfersControl(might_break));
};/*case end*/
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
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

bool types::BlockControlFlow::always_transfers_control() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
return JaktInternal::ExplicitValue(true);
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
});
}
}

bool types::BlockControlFlow::never_returns() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(true);
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
});
}
}

bool types::BlockControlFlow::always_returns() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(true);
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
});
}
}

bool types::BlockControlFlow::may_return() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* MayReturn */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 4 /* PartialAlwaysReturns */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5 /* PartialAlwaysTransfersControl */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 6 /* PartialNeverReturns */: {
return JaktInternal::ExplicitValue(true);
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
});
}
}

bool types::BlockControlFlow::may_break() const {
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
default: {
return JaktInternal::ExplicitValue(false);
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

bool types::BlockControlFlow::is_reachable() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* NeverReturns */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 0 /* AlwaysReturns */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 1 /* AlwaysTransfersControl */: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(true);
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

ByteString types::CheckedEnumVariant::debug_description() const {
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
[[nodiscard]] CheckedEnumVariant CheckedEnumVariant::Untyped(ids::EnumId enum_id, ByteString name, utility::Span span){
CheckedEnumVariant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Untyped.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum.as.Untyped.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Untyped.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedEnumVariant CheckedEnumVariant::Typed(ids::EnumId enum_id, ByteString name, ids::TypeId type_id, utility::Span span){
CheckedEnumVariant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Typed.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum.as.Typed.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.Typed.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum.as.Typed.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedEnumVariant CheckedEnumVariant::WithValue(ids::EnumId enum_id, ByteString name, NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span){
CheckedEnumVariant __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.WithValue.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum.as.WithValue.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.WithValue.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum.as.WithValue.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedEnumVariant CheckedEnumVariant::StructLike(ids::EnumId enum_id, ByteString name, JaktInternal::DynamicArray<ids::VarId> fields, utility::Span span){
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
bool types::CheckedEnumVariant::equals(types::CheckedEnumVariant const other) const {
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
return JaktInternal::ExplicitValue(((this_name) == (other_name)));
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
}));
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
});
}
}

ids::EnumId types::CheckedEnumVariant::enum_id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ids::EnumId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ids::EnumId const& enum_id = __jakt_match_value.enum_id;
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

utility::Span types::CheckedEnumVariant::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* WithValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.WithValue;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;utility::Span const& span = __jakt_match_value.span;
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

ByteString types::CheckedEnumVariant::name() const {
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

ByteString types::CheckedStatement::debug_description() const {
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
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Expression(NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->as.Expression.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Expression.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Defer(NonnullRefPtr<typename types::CheckedStatement> statement, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->as.Defer.statement) (decltype(statement))(move(statement));
new (&__jakt_uninit_enum->as.Defer.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::DestructuringAssignment(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> vars, NonnullRefPtr<typename types::CheckedStatement> var_decl, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->as.DestructuringAssignment.vars) (decltype(vars))(move(vars));
new (&__jakt_uninit_enum->as.DestructuringAssignment.var_decl) (decltype(var_decl))(move(var_decl));
new (&__jakt_uninit_enum->as.DestructuringAssignment.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::VarDecl(ids::VarId var_id, NonnullRefPtr<typename types::CheckedExpression> init, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->as.VarDecl.var_id) (decltype(var_id))(move(var_id));
new (&__jakt_uninit_enum->as.VarDecl.init) (decltype(init))(move(init));
new (&__jakt_uninit_enum->as.VarDecl.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::If(NonnullRefPtr<typename types::CheckedExpression> condition, types::CheckedBlock then_block, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> else_statement, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->as.If.condition) (decltype(condition))(move(condition));
new (&__jakt_uninit_enum->as.If.then_block) (decltype(then_block))(move(then_block));
new (&__jakt_uninit_enum->as.If.else_statement) (decltype(else_statement))(move(else_statement));
new (&__jakt_uninit_enum->as.If.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Block(types::CheckedBlock block, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->as.Block.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Block.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Loop(types::CheckedBlock block, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->as.Loop.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Loop.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::While(NonnullRefPtr<typename types::CheckedExpression> condition, types::CheckedBlock block, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 8;
new (&__jakt_uninit_enum->as.While.condition) (decltype(condition))(move(condition));
new (&__jakt_uninit_enum->as.While.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.While.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Return(JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> val, JaktInternal::Optional<utility::Span> span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->as.Return.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.Return.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Break(utility::Span value){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->as.Break.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Continue(utility::Span value){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 11;
new (&__jakt_uninit_enum->as.Continue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Throw(NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->as.Throw.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Throw.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Yield(JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> expr, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 13;
new (&__jakt_uninit_enum->as.Yield.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Yield.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::InlineCpp(JaktInternal::DynamicArray<ByteString> lines, utility::Span span){
NonnullRefPtr<CheckedStatement> __jakt_uninit_enum = adopt_ref(*new CheckedStatement);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->as.InlineCpp.lines) (decltype(lines))(move(lines));
new (&__jakt_uninit_enum->as.InlineCpp.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedStatement> CheckedStatement::Garbage(utility::Span value){
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
JaktInternal::Optional<utility::Span> types::CheckedStatement::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<utility::Span>, JaktInternal::Optional<utility::Span>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<utility::Span>>(span));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<utility::Span> const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* Break */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Break;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* Continue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Continue;utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.value;
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

JaktInternal::Optional<NonnullRefPtr<typename types::CheckedStatement>> types::CheckedStatement::none() {
{
return JaktInternal::OptionalNone();
}
}

ByteString types::NumberConstant::debug_description() const {
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
bool types::NumberConstant::can_fit_number(ids::TypeId const type_id,NonnullRefPtr<types::CheckedProgram> const program) const {
{
NonnullRefPtr<typename types::Type> const type_ = ((program)->get_type(type_id));
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
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(value,static_cast<i64>(0LL)));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(value,static_cast<i64>(0LL)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((((program)->is_integer(type_id)) && [](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(value,((type_)->min()))) && [](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(value,(infallible_integer_cast<i64>((((type_)->max())))))));
};/*case end*/
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
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
default: {
return JaktInternal::ExplicitValue((((program)->is_integer(type_id)) && [](u64 const& self, u64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(value,((type_)->max()))));
};/*case end*/
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
case 10 /* F32 */: {
{
utility::todo((ByteString::from_utf8_without_validation("Implement casting f32 to f64"sv)));
}
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(true);
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

size_t types::NumberConstant::to_usize() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Signed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Signed;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((value))));
};/*case end*/
case 1 /* Unsigned */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Unsigned;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((value))));
};/*case end*/
case 2 /* Floating */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Floating;f64 const& value = __jakt_match_value.value;
{
utility::panic((ByteString::from_utf8_without_validation("to_usize on a floating point constant"sv)));
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

ByteString types::CheckedNumericConstant::debug_description() const {
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
JaktInternal::Optional<types::NumberConstant> types::CheckedNumericConstant::number_constant() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, JaktInternal::Optional<types::NumberConstant>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Signed((infallible_integer_cast<i64>((value)))));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Signed((infallible_integer_cast<i64>((value)))));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Signed((infallible_integer_cast<i64>((value)))));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Signed((static_cast<i64>((value)))));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Unsigned((infallible_integer_cast<u64>((value)))));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Unsigned((infallible_integer_cast<u64>((value)))));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Unsigned((infallible_integer_cast<u64>((value)))));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Unsigned((static_cast<u64>((value)))));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Unsigned((static_cast<u64>((value)))));
};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::NumberConstant::Floating(value));
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

ByteString types::StringLiteral::debug_description() const {
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
ByteString types::StringLiteral::to_string() const {
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

ByteString types::CheckedTypeCast::debug_description() const {
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
[[nodiscard]] CheckedTypeCast CheckedTypeCast::Fallible(ids::TypeId value){
CheckedTypeCast __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Fallible.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedTypeCast CheckedTypeCast::Infallible(ids::TypeId value){
CheckedTypeCast __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Infallible.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedTypeCast CheckedTypeCast::Identity(ids::TypeId value){
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
ids::TypeId types::CheckedTypeCast::type_id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Fallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fallible;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 1 /* Infallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Infallible;ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 2 /* Identity */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identity;ids::TypeId const& type_id = __jakt_match_value.value;
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

ByteString types::CheckedUnaryOperator::debug_description() const {
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
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::TypeCast(types::CheckedTypeCast value){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 12;
new (&__jakt_uninit_enum.as.TypeCast.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::Is(ids::TypeId value){
CheckedUnaryOperator __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 13;
new (&__jakt_uninit_enum.as.Is.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::IsEnumVariant(types::CheckedEnumVariant enum_variant, JaktInternal::DynamicArray<types::CheckedEnumVariantBinding> bindings, ids::TypeId type_id){
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
[[nodiscard]] CheckedUnaryOperator CheckedUnaryOperator::Sizeof(ids::TypeId value){
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
ByteString types::CheckedMatchBody::debug_description() const {
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
[[nodiscard]] CheckedMatchBody CheckedMatchBody::Expression(NonnullRefPtr<typename types::CheckedExpression> value){
CheckedMatchBody __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Expression.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedMatchBody CheckedMatchBody::Block(types::CheckedBlock value){
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
ByteString types::CheckedMatchCase::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* EnumVariant */: {
builder.append("CheckedMatchCase::EnumVariant"sv);
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
builder.appendff("body: {}, ", that.body);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
case 1 /* Expression */: {
builder.append("CheckedMatchCase::Expression"sv);
[[maybe_unused]] auto const& that = this->as.Expression;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("expression: {}, ", that.expression);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("body: {}, ", that.body);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
case 2 /* ClassInstance */: {
builder.append("CheckedMatchCase::ClassInstance"sv);
[[maybe_unused]] auto const& that = this->as.ClassInstance;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type: {}, ", that.type);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("body: {}, ", that.body);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("rebind_name: {}, ", that.rebind_name);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
case 3 /* CatchAll */: {
builder.append("CheckedMatchCase::CatchAll"sv);
[[maybe_unused]] auto const& that = this->as.CatchAll;
builder.append("("sv);
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defaults: {}, ", this->common.init_common.defaults);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("has_arguments: {}, ", that.has_arguments);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("body: {}, ", that.body);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("marker_span: {}", that.marker_span);
}
builder.append(")"sv);
break;}
}
return builder.to_string();
}
[[nodiscard]] CheckedMatchCase CheckedMatchCase::EnumVariant(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults, ByteString name, JaktInternal::DynamicArray<parser::EnumVariantPatternArgument> args, ids::TypeId subject_type_id, size_t index, ids::ScopeId scope_id, types::CheckedMatchBody body, utility::Span marker_span){
CheckedMatchCase __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.EnumVariant.name) (decltype(name))(move(name));
new (&__jakt_uninit_enum.as.EnumVariant.args) (decltype(args))(move(args));
new (&__jakt_uninit_enum.as.EnumVariant.subject_type_id) (decltype(subject_type_id))(move(subject_type_id));
new (&__jakt_uninit_enum.as.EnumVariant.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum.as.EnumVariant.scope_id) (decltype(scope_id))(move(scope_id));
new (&__jakt_uninit_enum.as.EnumVariant.body) (decltype(body))(move(body));
new (&__jakt_uninit_enum.as.EnumVariant.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedMatchCase CheckedMatchCase::Expression(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults, NonnullRefPtr<typename types::CheckedExpression> expression, types::CheckedMatchBody body, utility::Span marker_span){
CheckedMatchCase __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.Expression.expression) (decltype(expression))(move(expression));
new (&__jakt_uninit_enum.as.Expression.body) (decltype(body))(move(body));
new (&__jakt_uninit_enum.as.Expression.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedMatchCase CheckedMatchCase::ClassInstance(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults, ids::TypeId type, types::CheckedMatchBody body, JaktInternal::Optional<types::ClassInstanceRebind> rebind_name, utility::Span marker_span){
CheckedMatchCase __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.ClassInstance.type) (decltype(type))(move(type));
new (&__jakt_uninit_enum.as.ClassInstance.body) (decltype(body))(move(body));
new (&__jakt_uninit_enum.as.ClassInstance.rebind_name) (decltype(rebind_name))(move(rebind_name));
new (&__jakt_uninit_enum.as.ClassInstance.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
[[nodiscard]] CheckedMatchCase CheckedMatchCase::CatchAll(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> defaults, bool has_arguments, types::CheckedMatchBody body, utility::Span marker_span){
CheckedMatchCase __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
new (&__jakt_uninit_enum.common.init_common.defaults) (decltype(defaults))(move(defaults));
new (&__jakt_uninit_enum.as.CatchAll.has_arguments) (decltype(has_arguments))(move(has_arguments));
new (&__jakt_uninit_enum.as.CatchAll.body) (decltype(body))(move(body));
new (&__jakt_uninit_enum.as.CatchAll.marker_span) (decltype(marker_span))(move(marker_span));
return __jakt_uninit_enum;
}
CheckedMatchCase& CheckedMatchCase::operator=(CheckedMatchCase const &rhs){
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
new (&this->as.EnumVariant.body) (decltype(this->as.EnumVariant.body))(rhs.as.EnumVariant.body);
new (&this->as.EnumVariant.marker_span) (decltype(this->as.EnumVariant.marker_span))(rhs.as.EnumVariant.marker_span);
break;
case 1 /* Expression */:
new (&this->as.Expression.expression) (decltype(this->as.Expression.expression))(rhs.as.Expression.expression);
new (&this->as.Expression.body) (decltype(this->as.Expression.body))(rhs.as.Expression.body);
new (&this->as.Expression.marker_span) (decltype(this->as.Expression.marker_span))(rhs.as.Expression.marker_span);
break;
case 2 /* ClassInstance */:
new (&this->as.ClassInstance.type) (decltype(this->as.ClassInstance.type))(rhs.as.ClassInstance.type);
new (&this->as.ClassInstance.body) (decltype(this->as.ClassInstance.body))(rhs.as.ClassInstance.body);
new (&this->as.ClassInstance.rebind_name) (decltype(this->as.ClassInstance.rebind_name))(rhs.as.ClassInstance.rebind_name);
new (&this->as.ClassInstance.marker_span) (decltype(this->as.ClassInstance.marker_span))(rhs.as.ClassInstance.marker_span);
break;
case 3 /* CatchAll */:
new (&this->as.CatchAll.has_arguments) (decltype(this->as.CatchAll.has_arguments))(rhs.as.CatchAll.has_arguments);
new (&this->as.CatchAll.body) (decltype(this->as.CatchAll.body))(rhs.as.CatchAll.body);
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
this->as.EnumVariant.body = rhs.as.EnumVariant.body;
this->as.EnumVariant.marker_span = rhs.as.EnumVariant.marker_span;
break;
case 1 /* Expression */:
this->as.Expression.expression = rhs.as.Expression.expression;
this->as.Expression.body = rhs.as.Expression.body;
this->as.Expression.marker_span = rhs.as.Expression.marker_span;
break;
case 2 /* ClassInstance */:
this->as.ClassInstance.type = rhs.as.ClassInstance.type;
this->as.ClassInstance.body = rhs.as.ClassInstance.body;
this->as.ClassInstance.rebind_name = rhs.as.ClassInstance.rebind_name;
this->as.ClassInstance.marker_span = rhs.as.ClassInstance.marker_span;
break;
case 3 /* CatchAll */:
this->as.CatchAll.has_arguments = rhs.as.CatchAll.has_arguments;
this->as.CatchAll.body = rhs.as.CatchAll.body;
this->as.CatchAll.marker_span = rhs.as.CatchAll.marker_span;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedMatchCase::CheckedMatchCase(CheckedMatchCase const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.defaults) (decltype(this->common.init_common.defaults))(rhs.common.init_common.defaults);
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(rhs.as.EnumVariant.name);
new (&this->as.EnumVariant.args) (decltype(this->as.EnumVariant.args))(rhs.as.EnumVariant.args);
new (&this->as.EnumVariant.subject_type_id) (decltype(this->as.EnumVariant.subject_type_id))(rhs.as.EnumVariant.subject_type_id);
new (&this->as.EnumVariant.index) (decltype(this->as.EnumVariant.index))(rhs.as.EnumVariant.index);
new (&this->as.EnumVariant.scope_id) (decltype(this->as.EnumVariant.scope_id))(rhs.as.EnumVariant.scope_id);
new (&this->as.EnumVariant.body) (decltype(this->as.EnumVariant.body))(rhs.as.EnumVariant.body);
new (&this->as.EnumVariant.marker_span) (decltype(this->as.EnumVariant.marker_span))(rhs.as.EnumVariant.marker_span);
break;
case 1 /* Expression */:
new (&this->as.Expression.expression) (decltype(this->as.Expression.expression))(rhs.as.Expression.expression);
new (&this->as.Expression.body) (decltype(this->as.Expression.body))(rhs.as.Expression.body);
new (&this->as.Expression.marker_span) (decltype(this->as.Expression.marker_span))(rhs.as.Expression.marker_span);
break;
case 2 /* ClassInstance */:
new (&this->as.ClassInstance.type) (decltype(this->as.ClassInstance.type))(rhs.as.ClassInstance.type);
new (&this->as.ClassInstance.body) (decltype(this->as.ClassInstance.body))(rhs.as.ClassInstance.body);
new (&this->as.ClassInstance.rebind_name) (decltype(this->as.ClassInstance.rebind_name))(rhs.as.ClassInstance.rebind_name);
new (&this->as.ClassInstance.marker_span) (decltype(this->as.ClassInstance.marker_span))(rhs.as.ClassInstance.marker_span);
break;
case 3 /* CatchAll */:
new (&this->as.CatchAll.has_arguments) (decltype(this->as.CatchAll.has_arguments))(rhs.as.CatchAll.has_arguments);
new (&this->as.CatchAll.body) (decltype(this->as.CatchAll.body))(rhs.as.CatchAll.body);
new (&this->as.CatchAll.marker_span) (decltype(this->as.CatchAll.marker_span))(rhs.as.CatchAll.marker_span);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
CheckedMatchCase& CheckedMatchCase::operator=(CheckedMatchCase &&rhs){
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
new (&this->as.EnumVariant.body) (decltype(this->as.EnumVariant.body))(move(rhs.as.EnumVariant.body));
new (&this->as.EnumVariant.marker_span) (decltype(this->as.EnumVariant.marker_span))(move(rhs.as.EnumVariant.marker_span));
break;
case 1 /* Expression */:
new (&this->as.Expression.expression) (decltype(this->as.Expression.expression))(move(rhs.as.Expression.expression));
new (&this->as.Expression.body) (decltype(this->as.Expression.body))(move(rhs.as.Expression.body));
new (&this->as.Expression.marker_span) (decltype(this->as.Expression.marker_span))(move(rhs.as.Expression.marker_span));
break;
case 2 /* ClassInstance */:
new (&this->as.ClassInstance.type) (decltype(this->as.ClassInstance.type))(move(rhs.as.ClassInstance.type));
new (&this->as.ClassInstance.body) (decltype(this->as.ClassInstance.body))(move(rhs.as.ClassInstance.body));
new (&this->as.ClassInstance.rebind_name) (decltype(this->as.ClassInstance.rebind_name))(move(rhs.as.ClassInstance.rebind_name));
new (&this->as.ClassInstance.marker_span) (decltype(this->as.ClassInstance.marker_span))(move(rhs.as.ClassInstance.marker_span));
break;
case 3 /* CatchAll */:
new (&this->as.CatchAll.has_arguments) (decltype(this->as.CatchAll.has_arguments))(move(rhs.as.CatchAll.has_arguments));
new (&this->as.CatchAll.body) (decltype(this->as.CatchAll.body))(move(rhs.as.CatchAll.body));
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
this->as.EnumVariant.body = move(rhs.as.EnumVariant.body);
this->as.EnumVariant.marker_span = move(rhs.as.EnumVariant.marker_span);
break;
case 1 /* Expression */:
this->as.Expression.expression = move(rhs.as.Expression.expression);
this->as.Expression.body = move(rhs.as.Expression.body);
this->as.Expression.marker_span = move(rhs.as.Expression.marker_span);
break;
case 2 /* ClassInstance */:
this->as.ClassInstance.type = move(rhs.as.ClassInstance.type);
this->as.ClassInstance.body = move(rhs.as.ClassInstance.body);
this->as.ClassInstance.rebind_name = move(rhs.as.ClassInstance.rebind_name);
this->as.ClassInstance.marker_span = move(rhs.as.ClassInstance.marker_span);
break;
case 3 /* CatchAll */:
this->as.CatchAll.has_arguments = move(rhs.as.CatchAll.has_arguments);
this->as.CatchAll.body = move(rhs.as.CatchAll.body);
this->as.CatchAll.marker_span = move(rhs.as.CatchAll.marker_span);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
CheckedMatchCase::CheckedMatchCase(CheckedMatchCase &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
new (&this->common.init_common.defaults) (decltype(this->common.init_common.defaults))(move(rhs.common.init_common.defaults));
switch (rhs.__jakt_init_index()) {
case 0 /* EnumVariant */:
new (&this->as.EnumVariant.name) (decltype(this->as.EnumVariant.name))(move(rhs.as.EnumVariant.name));
new (&this->as.EnumVariant.args) (decltype(this->as.EnumVariant.args))(move(rhs.as.EnumVariant.args));
new (&this->as.EnumVariant.subject_type_id) (decltype(this->as.EnumVariant.subject_type_id))(move(rhs.as.EnumVariant.subject_type_id));
new (&this->as.EnumVariant.index) (decltype(this->as.EnumVariant.index))(move(rhs.as.EnumVariant.index));
new (&this->as.EnumVariant.scope_id) (decltype(this->as.EnumVariant.scope_id))(move(rhs.as.EnumVariant.scope_id));
new (&this->as.EnumVariant.body) (decltype(this->as.EnumVariant.body))(move(rhs.as.EnumVariant.body));
new (&this->as.EnumVariant.marker_span) (decltype(this->as.EnumVariant.marker_span))(move(rhs.as.EnumVariant.marker_span));
break;
case 1 /* Expression */:
new (&this->as.Expression.expression) (decltype(this->as.Expression.expression))(move(rhs.as.Expression.expression));
new (&this->as.Expression.body) (decltype(this->as.Expression.body))(move(rhs.as.Expression.body));
new (&this->as.Expression.marker_span) (decltype(this->as.Expression.marker_span))(move(rhs.as.Expression.marker_span));
break;
case 2 /* ClassInstance */:
new (&this->as.ClassInstance.type) (decltype(this->as.ClassInstance.type))(move(rhs.as.ClassInstance.type));
new (&this->as.ClassInstance.body) (decltype(this->as.ClassInstance.body))(move(rhs.as.ClassInstance.body));
new (&this->as.ClassInstance.rebind_name) (decltype(this->as.ClassInstance.rebind_name))(move(rhs.as.ClassInstance.rebind_name));
new (&this->as.ClassInstance.marker_span) (decltype(this->as.ClassInstance.marker_span))(move(rhs.as.ClassInstance.marker_span));
break;
case 3 /* CatchAll */:
new (&this->as.CatchAll.has_arguments) (decltype(this->as.CatchAll.has_arguments))(move(rhs.as.CatchAll.has_arguments));
new (&this->as.CatchAll.body) (decltype(this->as.CatchAll.body))(move(rhs.as.CatchAll.body));
new (&this->as.CatchAll.marker_span) (decltype(this->as.CatchAll.marker_span))(move(rhs.as.CatchAll.marker_span));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
CheckedMatchCase::~CheckedMatchCase(){ if (this->__jakt_variant_index == 0) return;
this->common.init_common.defaults.~DynamicArray();
this->__jakt_destroy_variant(); }
void CheckedMatchCase::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* EnumVariant */:this->as.EnumVariant.name.~ByteString();
this->as.EnumVariant.args.~DynamicArray();
this->as.EnumVariant.subject_type_id.~TypeId();
this->as.EnumVariant.scope_id.~ScopeId();
this->as.EnumVariant.body.~CheckedMatchBody();
this->as.EnumVariant.marker_span.~Span();
break;
case 1 /* Expression */:this->as.Expression.expression.~NonnullRefPtr();
this->as.Expression.body.~CheckedMatchBody();
this->as.Expression.marker_span.~Span();
break;
case 2 /* ClassInstance */:this->as.ClassInstance.type.~TypeId();
this->as.ClassInstance.body.~CheckedMatchBody();
this->as.ClassInstance.rebind_name.~Optional();
this->as.ClassInstance.marker_span.~Span();
break;
case 3 /* CatchAll */:this->as.CatchAll.body.~CheckedMatchBody();
this->as.CatchAll.marker_span.~Span();
break;
}
}
ByteString types::CheckedExpression::debug_description() const {
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Boolean(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, bool val, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 1;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Boolean.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.Boolean.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::NumericConstant(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, types::CheckedNumericConstant val, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 2;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.NumericConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.NumericConstant.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.NumericConstant.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::QuotedString(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, types::CheckedStringLiteral val, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 3;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.QuotedString.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.QuotedString.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::ByteConstant(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, ByteString val, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 4;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.ByteConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.ByteConstant.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::CharacterConstant(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, ByteString val, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 5;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.CharacterConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.CharacterConstant.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::CCharacterConstant(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, ByteString val, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 6;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.CCharacterConstant.val) (decltype(val))(move(val));
new (&__jakt_uninit_enum->as.CCharacterConstant.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::UnaryOp(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, types::CheckedUnaryOperator op, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 7;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.UnaryOp.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.UnaryOp.op) (decltype(op))(move(op));
new (&__jakt_uninit_enum->as.UnaryOp.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.UnaryOp.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::BinaryOp(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> lhs, types::CheckedBinaryOperator op, NonnullRefPtr<typename types::CheckedExpression> rhs, utility::Span span, ids::TypeId type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::JaktTuple(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 9;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.JaktTuple.vals) (decltype(vals))(move(vals));
new (&__jakt_uninit_enum->as.JaktTuple.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.JaktTuple.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Range(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> from, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> to, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 10;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Range.from) (decltype(from))(move(from));
new (&__jakt_uninit_enum->as.Range.to) (decltype(to))(move(to));
new (&__jakt_uninit_enum->as.Range.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Range.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::JaktArray(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> repeat, utility::Span span, ids::TypeId type_id, ids::TypeId inner_type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::JaktSet(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> vals, utility::Span span, ids::TypeId type_id, ids::TypeId inner_type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 12;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.JaktSet.vals) (decltype(vals))(move(vals));
new (&__jakt_uninit_enum->as.JaktSet.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.JaktSet.type_id) (decltype(type_id))(move(type_id));
new (&__jakt_uninit_enum->as.JaktSet.inner_type_id) (decltype(inner_type_id))(move(inner_type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::JaktDictionary(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> vals, utility::Span span, ids::TypeId type_id, ids::TypeId key_type_id, ids::TypeId value_type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedExpression(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, NonnullRefPtr<typename types::CheckedExpression> index, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 14;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.IndexedExpression.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedExpression.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedExpression.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.IndexedExpression.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedDictionary(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, NonnullRefPtr<typename types::CheckedExpression> index, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 15;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.IndexedDictionary.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.IndexedDictionary.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.IndexedDictionary.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.IndexedDictionary.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedTuple(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, size_t index, utility::Span span, bool is_optional, ids::TypeId type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedStruct(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, ByteString name, JaktInternal::Optional<ids::VarId> index, utility::Span span, bool is_optional, ids::TypeId type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::IndexedCommonEnumMember(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, ByteString index, utility::Span span, bool is_optional, ids::TypeId type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::ComptimeIndex(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, NonnullRefPtr<typename types::CheckedExpression> index, bool is_optional, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 19;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.ComptimeIndex.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.ComptimeIndex.index) (decltype(index))(move(index));
new (&__jakt_uninit_enum->as.ComptimeIndex.is_optional) (decltype(is_optional))(move(is_optional));
new (&__jakt_uninit_enum->as.ComptimeIndex.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Match(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, JaktInternal::DynamicArray<types::CheckedMatchCase> match_cases, utility::Span span, ids::TypeId type_id, bool all_variants_constant){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::EnumVariantArg(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, types::CheckedEnumVariantBinding arg, types::CheckedEnumVariant enum_variant, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 21;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.EnumVariantArg.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.EnumVariantArg.arg) (decltype(arg))(move(arg));
new (&__jakt_uninit_enum->as.EnumVariantArg.enum_variant) (decltype(enum_variant))(move(enum_variant));
new (&__jakt_uninit_enum->as.EnumVariantArg.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Call(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, types::CheckedCall call, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 22;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Call.call) (decltype(call))(move(call));
new (&__jakt_uninit_enum->as.Call.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Call.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::MethodCall(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, types::CheckedCall call, utility::Span span, bool is_optional, ids::TypeId type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::NamespacedVar(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<types::CheckedNamespace> namespaces, NonnullRefPtr<types::CheckedVariable> var, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 24;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.NamespacedVar.namespaces) (decltype(namespaces))(move(namespaces));
new (&__jakt_uninit_enum->as.NamespacedVar.var) (decltype(var))(move(var));
new (&__jakt_uninit_enum->as.NamespacedVar.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Var(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<types::CheckedVariable> var, utility::Span span){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 25;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Var.var) (decltype(var))(move(var));
new (&__jakt_uninit_enum->as.Var.span) (decltype(span))(move(span));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::OptionalNone(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 26;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.OptionalNone.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.OptionalNone.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::OptionalSome(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 27;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.OptionalSome.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.OptionalSome.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.OptionalSome.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::ForcedUnwrap(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 28;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.ForcedUnwrap.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.ForcedUnwrap.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.ForcedUnwrap.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Block(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, types::CheckedBlock block, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 29;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Block.block) (decltype(block))(move(block));
new (&__jakt_uninit_enum->as.Block.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Block.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Function(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<types::CheckedCapture> captures, JaktInternal::DynamicArray<types::CheckedParameter> params, bool can_throw, ids::TypeId return_type_id, types::CheckedBlock block, utility::Span span, ids::TypeId type_id, JaktInternal::Optional<ids::FunctionId> pseudo_function_id, ids::ScopeId scope_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::DependentFunction(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, JaktInternal::DynamicArray<types::CheckedCapture> captures, JaktInternal::DynamicArray<types::CheckedParameter> params, bool can_throw, ids::TypeId return_type_id, parser::ParsedBlock block, utility::Span span, ids::TypeId type_id, JaktInternal::Optional<ids::FunctionId> pseudo_function_id, ids::ScopeId scope_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Must(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 32;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Must.expr) (decltype(expr))(move(expr));
new (&__jakt_uninit_enum->as.Must.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Must.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Try(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedExpression> expr, JaktInternal::Optional<types::CheckedBlock> catch_block, JaktInternal::Optional<utility::Span> catch_span, JaktInternal::Optional<ByteString> catch_name, utility::Span span, ids::TypeId type_id, ids::TypeId inner_type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::TryBlock(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, NonnullRefPtr<typename types::CheckedStatement> stmt, types::CheckedBlock catch_block, ByteString error_name, utility::Span error_span, utility::Span span, ids::TypeId type_id){
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
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Reflect(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, ids::TypeId type, utility::Span span, ids::TypeId type_id){
NonnullRefPtr<CheckedExpression> __jakt_uninit_enum = adopt_ref(*new CheckedExpression);
__jakt_uninit_enum->__jakt_variant_index = 35;
new (&__jakt_uninit_enum->common.init_common.generic_inferences) (decltype(generic_inferences))(move(generic_inferences));
new (&__jakt_uninit_enum->as.Reflect.type) (decltype(type))(move(type));
new (&__jakt_uninit_enum->as.Reflect.span) (decltype(span))(move(span));
new (&__jakt_uninit_enum->as.Reflect.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<CheckedExpression> CheckedExpression::Garbage(JaktInternal::Optional<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> generic_inferences, utility::Span span, ids::TypeId type_id){
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
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(rhs.as.IndexedExpression.span);
new (&this->as.IndexedExpression.type_id) (decltype(this->as.IndexedExpression.type_id))(rhs.as.IndexedExpression.type_id);
break;
case 14 /* IndexedDictionary */:
new (&this->as.IndexedDictionary.expr) (decltype(this->as.IndexedDictionary.expr))(rhs.as.IndexedDictionary.expr);
new (&this->as.IndexedDictionary.index) (decltype(this->as.IndexedDictionary.index))(rhs.as.IndexedDictionary.index);
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
this->as.IndexedExpression.span = rhs.as.IndexedExpression.span;
this->as.IndexedExpression.type_id = rhs.as.IndexedExpression.type_id;
break;
case 14 /* IndexedDictionary */:
this->as.IndexedDictionary.expr = rhs.as.IndexedDictionary.expr;
this->as.IndexedDictionary.index = rhs.as.IndexedDictionary.index;
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
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(rhs.as.IndexedExpression.span);
new (&this->as.IndexedExpression.type_id) (decltype(this->as.IndexedExpression.type_id))(rhs.as.IndexedExpression.type_id);
break;
case 14 /* IndexedDictionary */:
new (&this->as.IndexedDictionary.expr) (decltype(this->as.IndexedDictionary.expr))(rhs.as.IndexedDictionary.expr);
new (&this->as.IndexedDictionary.index) (decltype(this->as.IndexedDictionary.index))(rhs.as.IndexedDictionary.index);
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
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(move(rhs.as.IndexedExpression.span));
new (&this->as.IndexedExpression.type_id) (decltype(this->as.IndexedExpression.type_id))(move(rhs.as.IndexedExpression.type_id));
break;
case 14 /* IndexedDictionary */:
new (&this->as.IndexedDictionary.expr) (decltype(this->as.IndexedDictionary.expr))(move(rhs.as.IndexedDictionary.expr));
new (&this->as.IndexedDictionary.index) (decltype(this->as.IndexedDictionary.index))(move(rhs.as.IndexedDictionary.index));
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
this->as.IndexedExpression.span = move(rhs.as.IndexedExpression.span);
this->as.IndexedExpression.type_id = move(rhs.as.IndexedExpression.type_id);
break;
case 14 /* IndexedDictionary */:
this->as.IndexedDictionary.expr = move(rhs.as.IndexedDictionary.expr);
this->as.IndexedDictionary.index = move(rhs.as.IndexedDictionary.index);
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
new (&this->as.IndexedExpression.span) (decltype(this->as.IndexedExpression.span))(move(rhs.as.IndexedExpression.span));
new (&this->as.IndexedExpression.type_id) (decltype(this->as.IndexedExpression.type_id))(move(rhs.as.IndexedExpression.type_id));
break;
case 14 /* IndexedDictionary */:
new (&this->as.IndexedDictionary.expr) (decltype(this->as.IndexedDictionary.expr))(move(rhs.as.IndexedDictionary.expr));
new (&this->as.IndexedDictionary.index) (decltype(this->as.IndexedDictionary.index))(move(rhs.as.IndexedDictionary.index));
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
this->as.IndexedExpression.span.~Span();
this->as.IndexedExpression.type_id.~TypeId();
break;
case 14 /* IndexedDictionary */:this->as.IndexedDictionary.expr.~NonnullRefPtr();
this->as.IndexedDictionary.index.~NonnullRefPtr();
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
JaktInternal::Optional<types::NumberConstant> types::CheckedExpression::to_number_constant(NonnullRefPtr<types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, JaktInternal::Optional<types::NumberConstant>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;types::CheckedNumericConstant const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(((val).number_constant()));
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_158; {
JaktInternal::Optional<types::NumberConstant> result = JaktInternal::OptionalNone();
__jakt_var_158 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>,JaktInternal::Optional<types::NumberConstant>> {
auto __jakt_enum_value = (((op).__jakt_init_index() == 11 /* TypeCast */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_159; {
types::CheckedTypeCast const cast = (op).as.TypeCast.value;
if ((!(((cast).__jakt_init_index() == 1 /* Infallible */)))){
(result = JaktInternal::OptionalNone());
}
if (((!(((program)->is_integer(type_id)))) && (!(((program)->is_floating(type_id)))))){
(result = JaktInternal::OptionalNone());
}
if (((expr)->__jakt_init_index() == 1 /* NumericConstant */)){
types::CheckedNumericConstant const val = (expr)->as.NumericConstant.val;
(result = ((val).number_constant()));
}
__jakt_var_159 = result; goto __jakt_label_153;

}
__jakt_label_153:; __jakt_var_159.release_value(); }));
}
else {
{
return JaktInternal::OptionalNone();
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_152;

}
__jakt_label_152:; __jakt_var_158.release_value(); }));
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

utility::Span types::CheckedExpression::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3 /* ByteConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ByteConstant;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4 /* CharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CharacterConstant;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5 /* CCharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CCharacterConstant;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 18 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 25 /* OptionalNone */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalNone;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 30 /* DependentFunction */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentFunction;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 31 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 32 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 34 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 35 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;utility::Span const& span = __jakt_match_value.span;
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

bool types::CheckedExpression::is_mutable(NonnullRefPtr<types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 1 /* NumericConstant */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 2 /* QuotedString */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 3 /* ByteConstant */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 4 /* CharacterConstant */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5 /* CCharacterConstant */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->is_mutable));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 18 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_160; {
bool result = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
if (((val)->is_mutable(program))){
(result = true);
break;
}
}

}
}

__jakt_var_160 = result; goto __jakt_label_154;

}
__jakt_label_154:; __jakt_var_160.release_value(); }));
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_161; {
bool result = false;
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename types::CheckedExpression> val = (_magic_value.value());
{
if (((val)->is_mutable(program))){
(result = true);
break;
}
}

}
}

__jakt_var_161 = result; goto __jakt_label_155;

}
__jakt_label_155:; __jakt_var_161.release_value(); }));
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_162; {
bool result = false;
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> ___val__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>> const jakt_____val__ = ___val__;
NonnullRefPtr<typename types::CheckedExpression> const _ = ((jakt_____val__).template get<0>());
NonnullRefPtr<typename types::CheckedExpression> const val = ((jakt_____val__).template get<1>());

if (((val)->is_mutable(program))){
(result = true);
break;
}
}

}
}

__jakt_var_162 = result; goto __jakt_label_156;

}
__jakt_label_156:; __jakt_var_162.release_value(); }));
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* Dereference */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *((program)->get_type(((expr)->type())));
switch(__jakt_match_variant.__jakt_init_index()) {
case 29 /* MutableReference */: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 26 /* RawPtr */: {
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
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
}));
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
}));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
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
});
}
}

bool types::CheckedExpression::can_throw() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(((call).callee_throws));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(((call).callee_throws));
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(((val).may_throw));
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
});
}
}

ids::TypeId types::CheckedExpression::type() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Boolean */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Bool()));
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(((val).type_id));
};/*case end*/
case 3 /* ByteConstant */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U8()));
};/*case end*/
case 5 /* CCharacterConstant */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::CChar()));
};/*case end*/
case 4 /* CharacterConstant */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U32()));
};/*case end*/
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;types::CheckedEnumVariantBinding const& arg = __jakt_match_value.arg;
return JaktInternal::ExplicitValue(((arg).type_id));
};/*case end*/
case 23 /* NamespacedVar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NamespacedVar;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->type_id));
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->type_id));
};/*case end*/
case 18 /* ComptimeIndex */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Unknown()));
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 14 /* IndexedDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedDictionary;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 25 /* OptionalNone */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalNone;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 30 /* DependentFunction */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentFunction;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 31 /* Must */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Must;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 32 /* Try */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Try;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 34 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 35 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;ids::TypeId const& type_id = __jakt_match_value.type_id;
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

types::BlockControlFlow types::CheckedExpression::control_flow() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
bool const& all_variants_constant = __jakt_match_value.all_variants_constant;
return JaktInternal::ExplicitValue(({ Optional<types::BlockControlFlow> __jakt_var_163; {
JaktInternal::Optional<types::BlockControlFlow> control_flow = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedMatchCase case_ = (_magic_value.value());
{
types::BlockControlFlow const case_control_flow = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = case_;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((expr)->control_flow()));
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
};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((expr)->control_flow()));
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
};/*case end*/
case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((expr)->control_flow()));
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
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((expr)->control_flow()));
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
if (((control_flow).has_value())){
(control_flow = (((control_flow.value())).branch_unify_with(case_control_flow)));
}
else {
(control_flow = case_control_flow);
}

}

}
}

__jakt_var_163 = control_flow.value_or_lazy_evaluated([&] { return types::BlockControlFlow::MayReturn(); }); goto __jakt_label_157;

}
__jakt_label_157:; __jakt_var_163.release_value(); }));
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,types::BlockControlFlow> {
auto __jakt_enum_value = (((type_id).equals(types::never_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::BlockControlFlow::NeverReturns());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,types::BlockControlFlow> {
auto __jakt_enum_value = (((type_id).equals(types::never_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(types::BlockControlFlow::NeverReturns());
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<types::BlockControlFlow> __jakt_var_164; {
__jakt_var_164 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,types::BlockControlFlow> {
auto __jakt_enum_value = (((stmt)->__jakt_init_index() == 5 /* Block */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<types::BlockControlFlow> __jakt_var_165; {
types::CheckedBlock const block = (stmt)->as.Block.block;
__jakt_var_165 = ((((block).control_flow)).branch_unify_with(((catch_block).control_flow))); goto __jakt_label_159;

}
__jakt_label_159:; __jakt_var_165.release_value(); }));
}
else {
{
utility::panic((ByteString::from_utf8_without_validation("Try block doesn't have a block"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}); goto __jakt_label_158;

}
__jakt_label_158:; __jakt_var_164.release_value(); }));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::BlockControlFlow::MayReturn());
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

ByteString types::ValueImpl::debug_description() const {
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
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Struct(JaktInternal::DynamicArray<types::Value> fields, ids::StructId struct_id, JaktInternal::Optional<ids::FunctionId> constructor){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 18;
new (&__jakt_uninit_enum->as.Struct.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum->as.Struct.struct_id) (decltype(struct_id))(move(struct_id));
new (&__jakt_uninit_enum->as.Struct.constructor) (decltype(constructor))(move(constructor));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Class(JaktInternal::DynamicArray<types::Value> fields, ids::StructId struct_id, JaktInternal::Optional<ids::FunctionId> constructor){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 19;
new (&__jakt_uninit_enum->as.Class.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum->as.Class.struct_id) (decltype(struct_id))(move(struct_id));
new (&__jakt_uninit_enum->as.Class.constructor) (decltype(constructor))(move(constructor));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Enum(JaktInternal::DynamicArray<types::Value> fields, ids::EnumId enum_id, ids::FunctionId constructor){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 20;
new (&__jakt_uninit_enum->as.Enum.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum->as.Enum.enum_id) (decltype(enum_id))(move(enum_id));
new (&__jakt_uninit_enum->as.Enum.constructor) (decltype(constructor))(move(constructor));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktArray(JaktInternal::DynamicArray<types::Value> values, ids::TypeId type_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 21;
new (&__jakt_uninit_enum->as.JaktArray.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktArray.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktDictionary(JaktInternal::DynamicArray<types::Value> keys, JaktInternal::DynamicArray<types::Value> values, ids::TypeId type_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 22;
new (&__jakt_uninit_enum->as.JaktDictionary.keys) (decltype(keys))(move(keys));
new (&__jakt_uninit_enum->as.JaktDictionary.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktDictionary.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktSet(JaktInternal::DynamicArray<types::Value> values, ids::TypeId type_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 23;
new (&__jakt_uninit_enum->as.JaktSet.values) (decltype(values))(move(values));
new (&__jakt_uninit_enum->as.JaktSet.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::RawPtr(NonnullRefPtr<typename types::ValueImpl> value){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 24;
new (&__jakt_uninit_enum->as.RawPtr.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::OptionalSome(types::Value value){
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
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::JaktTuple(JaktInternal::DynamicArray<types::Value> fields, ids::TypeId type_id){
NonnullRefPtr<ValueImpl> __jakt_uninit_enum = adopt_ref(*new ValueImpl);
__jakt_uninit_enum->__jakt_variant_index = 27;
new (&__jakt_uninit_enum->as.JaktTuple.fields) (decltype(fields))(move(fields));
new (&__jakt_uninit_enum->as.JaktTuple.type_id) (decltype(type_id))(move(type_id));
return __jakt_uninit_enum;
}
[[nodiscard]] NonnullRefPtr<ValueImpl> ValueImpl::Function(JaktInternal::Dictionary<ByteString,types::Value> captures, JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>> params, ids::TypeId return_type_id, ids::TypeId type_id, types::CheckedBlock block, bool can_throw, JaktInternal::DynamicArray<types::CheckedParameter> checked_params, ids::ScopeId scope_id, JaktInternal::Optional<ids::FunctionId> pseudo_function_id){
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
ErrorOr<ids::TypeId> types::ValueImpl::type_id(NonnullRefPtr<types::CheckedProgram>& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<ids::TypeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(types::void_type_id());
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Bool()));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U8()));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U16()));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U32()));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::U64()));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::I8()));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::I16()));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::I32()));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::I64()));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::F32()));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::F64()));
};/*case end*/
case 12 /* USize */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::Usize()));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue((TRY((((((program)))->find_type_in_scope(((((program)))->prelude_scope_id()),(ByteString::from_utf8_without_validation("String"sv)),false,JaktInternal::OptionalNone())))).value()));
};/*case end*/
case 14 /* StringView */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::JaktString()));
};/*case end*/
case 15 /* CChar */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::CChar()));
};/*case end*/
case 16 /* CInt */: {
return JaktInternal::ExplicitValue(types::builtin(types::BuiltinType::CInt()));
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue(((((program)))->find_or_add_type_id(types::Type::Struct(parser::CheckedQualifiers(false),struct_id),((struct_id).module),false)));
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue(((((program)))->find_or_add_type_id(types::Type::Struct(parser::CheckedQualifiers(false),struct_id),((struct_id).module),false)));
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(((((program)))->find_or_add_type_id(types::Type::Enum(parser::CheckedQualifiers(false),enum_id),((enum_id).module),false)));
};/*case end*/
default: {
{
utility::panic((ByteString::from_utf8_without_validation("Reflected value type not implemented"sv)));
}
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

NonnullRefPtr<typename types::ValueImpl> types::ValueImpl::copy() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, NonnullRefPtr<typename types::ValueImpl>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(types::ValueImpl::Void());
};/*case end*/
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::Bool(x));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::U8(x));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::U16(x));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::U32(x));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::U64(x));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::I8(x));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::I16(x));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::I32(x));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::I64(x));
};/*case end*/
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::F32(x));
};/*case end*/
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::F64(x));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::USize(x));
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::JaktString(x));
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::StringView(x));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::CChar(x));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::CInt(x));
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_166; {
JaktInternal::DynamicArray<types::Value> fields_copy = DynamicArray<types::Value>::create_with({});
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
((fields_copy).push(((field).copy())));
}

}
}

__jakt_var_166 = types::ValueImpl::Struct(fields_copy,struct_id,constructor); goto __jakt_label_160;

}
__jakt_label_160:; __jakt_var_166.release_value(); }));
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(types::ValueImpl::Class(fields,struct_id,constructor));
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
ids::FunctionId const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_167; {
JaktInternal::DynamicArray<types::Value> fields_copy = DynamicArray<types::Value>::create_with({});
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
((fields_copy).push(((field).copy())));
}

}
}

__jakt_var_167 = types::ValueImpl::Enum(fields_copy,enum_id,constructor); goto __jakt_label_161;

}
__jakt_label_161:; __jakt_var_167.release_value(); }));
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_168; {
JaktInternal::DynamicArray<types::Value> values_copy = DynamicArray<types::Value>::create_with({});
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
((values_copy).push(((value).copy())));
}

}
}

__jakt_var_168 = types::ValueImpl::JaktArray(values_copy,type_id); goto __jakt_label_162;

}
__jakt_label_162:; __jakt_var_168.release_value(); }));
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_169; {
JaktInternal::DynamicArray<types::Value> values_copy = DynamicArray<types::Value>::create_with({});
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
((values_copy).push(((value).copy())));
}

}
}

JaktInternal::DynamicArray<types::Value> keys_copy = DynamicArray<types::Value>::create_with({});
{
JaktInternal::ArrayIterator<types::Value> _magic = ((keys).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value key = (_magic_value.value());
{
((keys_copy).push(((key).copy())));
}

}
}

__jakt_var_169 = types::ValueImpl::JaktDictionary(keys_copy,values_copy,type_id); goto __jakt_label_163;

}
__jakt_label_163:; __jakt_var_169.release_value(); }));
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_170; {
JaktInternal::DynamicArray<types::Value> values_copy = DynamicArray<types::Value>::create_with({});
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
((values_copy).push(((value).copy())));
}

}
}

__jakt_var_170 = types::ValueImpl::JaktSet(values_copy,type_id); goto __jakt_label_164;

}
__jakt_label_164:; __jakt_var_170.release_value(); }));
};/*case end*/
case 23 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;NonnullRefPtr<typename types::ValueImpl> const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::RawPtr(value));
};/*case end*/
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(types::ValueImpl::OptionalSome(((value).copy())));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(types::ValueImpl::OptionalNone());
};/*case end*/
case 26 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_171; {
JaktInternal::DynamicArray<types::Value> values_copy = DynamicArray<types::Value>::create_with({});
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
((values_copy).push(((value).copy())));
}

}
}

__jakt_var_171 = types::ValueImpl::JaktTuple(values_copy,type_id); goto __jakt_label_165;

}
__jakt_label_165:; __jakt_var_171.release_value(); }));
};/*case end*/
case 27 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::Dictionary<ByteString,types::Value> const& captures = __jakt_match_value.captures;
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename parser::ParsedExpression>,ids::ScopeId>>>> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::TypeId const& type_id = __jakt_match_value.type_id;
types::CheckedBlock const& block = __jakt_match_value.block;
JaktInternal::DynamicArray<types::CheckedParameter> const& checked_params = __jakt_match_value.checked_params;
ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
JaktInternal::Optional<ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(types::ValueImpl::Function(captures,params,return_type_id,type_id,block,can_throw,checked_params,scope_id,pseudo_function_id));
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

bool types::ValueImpl::equals(NonnullRefPtr<typename types::ValueImpl> const other) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(((other)->__jakt_init_index() == 0 /* Void */));
};/*case end*/
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((x) == (y)));
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
return JaktInternal::ExplicitValue(((x) == (y)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
return JaktInternal::ExplicitValue(((y) == (x)));
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
}));
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
});
}
}

ByteString types::NumericOrStringValue::debug_description() const {
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
