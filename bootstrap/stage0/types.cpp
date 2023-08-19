#include "types.h"
namespace Jakt {
namespace types {
ErrorOr<DeprecatedString> comptime_format_impl(DeprecatedString const format_string,JaktInternal::ArraySlice<types::Value> const arguments,NonnullRefPtr<types::CheckedProgram> const& program) {
{
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
size_t current_argument_index = static_cast<size_t>(0ULL);
DeprecatedStringBuilder format_field_builder = DeprecatedStringBuilder::create();
JaktInternal::Optional<size_t> index_in_field = JaktInternal::OptionalNone();
bool expect_close_brace = false;
Function<JaktInternal::Tuple<JaktInternal::Optional<size_t>,DeprecatedString>(DeprecatedString)> const argument_and_index = [](DeprecatedString str) -> JaktInternal::Tuple<JaktInternal::Optional<size_t>,DeprecatedString> {
{
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
if (([](u32 const& self, u32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(code_point,static_cast<u32>(U'0')) && [](u32 const& self, u32 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> jakt__prelude__operators::Ordering {
{
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
DeprecatedString const index_str = ((str).substring(static_cast<size_t>(0ULL),slice_end));
JaktInternal::Optional<u32> const index = ((index_str).to_uint());
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<DeprecatedString>>{
auto __jakt_enum_value = (code_point);
if (__jakt_enum_value == static_cast<u32>(U'{')) {
{
if ((((index_in_field).has_value()) && (((index_in_field.value())) == (static_cast<size_t>(0ULL))))){
TRY((((builder).append_code_point(static_cast<u32>(U'{')))));
(index_in_field = JaktInternal::OptionalNone());
}
else if (((index_in_field).has_value())){
TRY((((format_field_builder).append_code_point(static_cast<u32>(U'{')))));
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
TRY((((builder).append_code_point(static_cast<u32>(U'}')))));
(expect_close_brace = false);
}
else if ((!(((index_in_field).has_value())))){
(expect_close_brace = true);
}
else {
(index_in_field = JaktInternal::OptionalNone());
DeprecatedString const fmt_string = TRY((((format_field_builder).to_string())));
((format_field_builder).clear());
JaktInternal::Tuple<JaktInternal::Optional<size_t>,DeprecatedString> const index_format_string_ = argument_and_index(fmt_string);
JaktInternal::Optional<size_t> const index = ((index_format_string_).template get<0>());
DeprecatedString const format_string = ((index_format_string_).template get<1>());

size_t const effective_index = index.value_or_lazy_evaluated([&] { return ((current_argument_index++)); });
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(effective_index,((arguments).size()))){
return Error::__jakt_from_string_literal((StringView::from_string_literal("Not enough arguments for format string"sv)));
}
DeprecatedString const effective_format_string = TRY((__jakt_format((StringView::from_string_literal("{{{}}}"sv)),format_string)));
TRY((((builder).append(TRY((types::format_value_impl(effective_format_string,((arguments)[effective_index]),program)))))));
}

}
return JaktInternal::ExplicitValue<void>();
}
else {
{
if (((index_in_field).has_value())){
TRY((((format_field_builder).append_code_point(code_point))));
}
else {
TRY((((builder).append_code_point(code_point))));
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

return TRY((((builder).to_string())));
}
}

ids::TypeId builtin(types::BuiltinType const builtin) {
{
return ids::TypeId(ids::ModuleId(static_cast<size_t>(0ULL)),((builtin).id()));
}
}

ids::TypeId void_type_id() {
{
return types::builtin( types::BuiltinType { typename types::BuiltinType::Void() } );
}
}

ids::TypeId unknown_type_id() {
{
return types::builtin( types::BuiltinType { typename types::BuiltinType::Unknown() } );
}
}

ids::TypeId never_type_id() {
{
return types::builtin( types::BuiltinType { typename types::BuiltinType::Never() } );
}
}

ErrorOr<DeprecatedString> format_value_impl(DeprecatedString const format_string,types::Value const value,NonnullRefPtr<types::CheckedProgram> const& program) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::Bool>();
bool const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U8>();
u8 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U16>();
u16 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U32>();
u32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U64>();
u64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::USize>();
size_t const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I8>();
i8 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I16>();
i16 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I32>();
i32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I64>();
i64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::F32>();
f32 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::F64>();
f64 const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CChar>();
char const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CInt>();
int const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
DeprecatedString const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::StringView>();
DeprecatedString const& v = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,v))));
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,TRY(DeprecatedString::from_utf8("(void)"sv))))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Struct>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_130; {
types::CheckedStruct const structure = ((((program)))->get_struct(struct_id));
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
JaktInternal::DynamicArray<DeprecatedString> field_names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
TRY((((builder).append(((structure).name)))));
if (((constructor).has_value())){
NonnullRefPtr<types::CheckedFunction> const function = ((((program)))->get_function((constructor.value())));
TRY((((builder).append((StringView::from_string_literal("::"sv))))));
TRY((((builder).append(((function)->name)))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter parameter = (_magic_value.value());
{
TRY((((field_names).push(((((parameter).variable))->name)))));
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
TRY((((field_names).push(((((((program)))->get_variable(((field).variable_id))))->name)))));
}

}
}

}

TRY((((builder).append_code_point(static_cast<u32>(U'(')))));
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
(index,static_cast<size_t>(0ULL))){
TRY((((builder).append((StringView::from_string_literal(", "sv))))));
}
TRY((((builder).append(((field_names)[index])))));
TRY((((builder).append((StringView::from_string_literal(": "sv))))));
TRY((((builder).append(TRY((types::format_value_impl(format_string,field,program)))))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

TRY((((builder).append_code_point(static_cast<u32>(U')')))));
__jakt_var_130 = TRY((((builder).to_string()))); goto __jakt_label_124;

}
__jakt_label_124:; __jakt_var_130.release_value(); }));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Class>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_131; {
types::CheckedStruct const structure = ((((program)))->get_struct(struct_id));
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
JaktInternal::DynamicArray<DeprecatedString> field_names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
TRY((((builder).append(((structure).name)))));
if (((constructor).has_value())){
NonnullRefPtr<types::CheckedFunction> const function = ((((program)))->get_function((constructor.value())));
TRY((((builder).append((StringView::from_string_literal("::"sv))))));
TRY((((builder).append(((function)->name)))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter parameter = (_magic_value.value());
{
TRY((((field_names).push(((((parameter).variable))->name)))));
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
TRY((((field_names).push(((((((program)))->get_variable(((field).variable_id))))->name)))));
}

}
}

}

TRY((((builder).append_code_point(static_cast<u32>(U'(')))));
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
(index,static_cast<size_t>(0ULL))){
TRY((((builder).append((StringView::from_string_literal(", "sv))))));
}
TRY((((builder).append(((field_names)[index])))));
TRY((((builder).append((StringView::from_string_literal(": "sv))))));
TRY((((builder).append(TRY((types::format_value_impl(format_string,field,program)))))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

TRY((((builder).append_code_point(static_cast<u32>(U')')))));
__jakt_var_131 = TRY((((builder).to_string()))); goto __jakt_label_125;

}
__jakt_label_125:; __jakt_var_131.release_value(); }));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Enum>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
ids::FunctionId const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_132; {
types::CheckedEnum const enum_ = ((((program)))->get_enum(enum_id));
NonnullRefPtr<types::CheckedFunction> const function = ((((program)))->get_function(constructor));
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
JaktInternal::DynamicArray<DeprecatedString> field_names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
TRY((((builder).append(((enum_).name)))));
TRY((((builder).append((StringView::from_string_literal("::"sv))))));
TRY((((builder).append(((function)->name)))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((function)->params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter parameter = (_magic_value.value());
{
TRY((((field_names).push(((((parameter).variable))->name)))));
}

}
}

TRY((((builder).append_code_point(static_cast<u32>(U'(')))));
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
(index,static_cast<size_t>(0ULL))){
TRY((((builder).append((StringView::from_string_literal(", "sv))))));
}
TRY((((builder).append(((field_names)[index])))));
TRY((((builder).append((StringView::from_string_literal(": "sv))))));
TRY((((builder).append(TRY((types::format_value_impl(format_string,field,program)))))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

TRY((((builder).append_code_point(static_cast<u32>(U')')))));
__jakt_var_132 = TRY((((builder).to_string()))); goto __jakt_label_126;

}
__jakt_label_126:; __jakt_var_132.release_value(); }));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::OptionalSome>();types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::format_value_impl(TRY((__jakt_format((StringView::from_string_literal("Some({})"sv)),format_string))),value,program))));
};/*case end*/
case 25: {
return JaktInternal::ExplicitValue(TRY((__jakt_format(format_string,TRY(DeprecatedString::from_utf8("None"sv))))));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktTuple>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_133; {
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 26: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')}));
};/*case end*/
case 20: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')}));
};/*case end*/
case 22: {
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
TRY((((builder).append_code_point(((surrounding).template get<0>())))));
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
(index,static_cast<size_t>(0ULL))){
TRY((((builder).append((StringView::from_string_literal(", "sv))))));
}
TRY((((builder).append(TRY((types::format_value_impl(format_string,field,program)))))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

TRY((((builder).append_code_point(((surrounding).template get<1>())))));
__jakt_var_133 = TRY((((builder).to_string()))); goto __jakt_label_127;

}
__jakt_label_127:; __jakt_var_133.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktArray>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_134; {
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 26: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')}));
};/*case end*/
case 20: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')}));
};/*case end*/
case 22: {
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
TRY((((builder).append_code_point(((surrounding).template get<0>())))));
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
(index,static_cast<size_t>(0ULL))){
TRY((((builder).append((StringView::from_string_literal(", "sv))))));
}
TRY((((builder).append(TRY((types::format_value_impl(format_string,field,program)))))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

TRY((((builder).append_code_point(((surrounding).template get<1>())))));
__jakt_var_134 = TRY((((builder).to_string()))); goto __jakt_label_128;

}
__jakt_label_128:; __jakt_var_134.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktSet>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_135; {
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
JaktInternal::Tuple<u32,u32> const surrounding = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<u32,u32>, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.index()) {
case 26: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'('), static_cast<u32>(U')')}));
};/*case end*/
case 20: {
return JaktInternal::ExplicitValue((Tuple{static_cast<u32>(U'['), static_cast<u32>(U']')}));
};/*case end*/
case 22: {
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
TRY((((builder).append_code_point(((surrounding).template get<0>())))));
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
(index,static_cast<size_t>(0ULL))){
TRY((((builder).append((StringView::from_string_literal(", "sv))))));
}
TRY((((builder).append(TRY((types::format_value_impl(format_string,field,program)))))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

TRY((((builder).append_code_point(((surrounding).template get<1>())))));
__jakt_var_135 = TRY((((builder).to_string()))); goto __jakt_label_129;

}
__jakt_label_129:; __jakt_var_135.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktDictionary>();JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_136; {
DeprecatedStringBuilder builder = DeprecatedStringBuilder::create();
TRY((((builder).append_code_point(static_cast<u32>(U'[')))));
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
(index,static_cast<size_t>(0ULL))){
TRY((((builder).append((StringView::from_string_literal(", "sv))))));
}
TRY((((builder).append(TRY((types::format_value_impl(format_string,key,program)))))));
TRY((((builder).append((StringView::from_string_literal(": "sv))))));
TRY((((builder).append(TRY((types::format_value_impl(format_string,((values)[index]),program)))))));
((index) += (static_cast<size_t>(1ULL)));
}

}
}

TRY((((builder).append_code_point(static_cast<u32>(U']')))));
__jakt_var_136 = TRY((((builder).to_string()))); goto __jakt_label_130;

}
__jakt_label_130:; __jakt_var_136.release_value(); }));
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

ErrorOr<DeprecatedString> types::CheckedNamespace::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedNamespace("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("scope: {}", scope));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedNamespace::CheckedNamespace(DeprecatedString a_name, ids::ScopeId a_scope) :name(move(a_name)), scope(move(a_scope)){}

ErrorOr<DeprecatedString> types::Module::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Module("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("id: {}, ", id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("functions: {}, ", functions));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("structures: {}, ", structures));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("enums: {}, ", enums));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("scopes: {}, ", scopes));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("types: {}, ", types));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("traits: {}, ", traits));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("variables: {}, ", variables));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("imports: {}, ", imports));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("resolved_import_path: \"{}\", ", resolved_import_path));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("builtin_implementation_structs: {}, ", builtin_implementation_structs));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_root: {}", is_root));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ids::FunctionId types::Module::next_function_id() const {
{
return ids::FunctionId(((*this).id),((((*this).functions)).size()));
}
}

ErrorOr<ids::FunctionId> types::Module::add_function(NonnullRefPtr<types::CheckedFunction> const checked_function) {
{
ids::FunctionId const new_id = ((*this).next_function_id());
TRY((((((*this).functions)).push(checked_function))));
return new_id;
}
}

bool types::Module::is_prelude() const {
{
return ((((((*this).id)).id)) == (static_cast<size_t>(0ULL)));
}
}

types::Module::Module(ids::ModuleId a_id, DeprecatedString a_name, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> a_functions, JaktInternal::DynamicArray<types::CheckedStruct> a_structures, JaktInternal::DynamicArray<types::CheckedEnum> a_enums, JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> a_scopes, JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> a_types, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> a_traits, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> a_variables, JaktInternal::DynamicArray<ids::ModuleId> a_imports, DeprecatedString a_resolved_import_path, JaktInternal::Dictionary<size_t,ids::StructId> a_builtin_implementation_structs, bool a_is_root): id(move(a_id)), name(move(a_name)), functions(move(a_functions)), structures(move(a_structures)), enums(move(a_enums)), scopes(move(a_scopes)), types(move(a_types)), traits(move(a_traits)), variables(move(a_variables)), imports(move(a_imports)), resolved_import_path(move(a_resolved_import_path)), builtin_implementation_structs(move(a_builtin_implementation_structs)), is_root(move(a_is_root)){}
ErrorOr<NonnullRefPtr<Module>> types::Module::__jakt_create(ids::ModuleId id, DeprecatedString name, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedFunction>> functions, JaktInternal::DynamicArray<types::CheckedStruct> structures, JaktInternal::DynamicArray<types::CheckedEnum> enums, JaktInternal::DynamicArray<NonnullRefPtr<types::Scope>> scopes, JaktInternal::DynamicArray<NonnullRefPtr<typename types::Type>> types, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedTrait>> traits, JaktInternal::DynamicArray<NonnullRefPtr<types::CheckedVariable>> variables, JaktInternal::DynamicArray<ids::ModuleId> imports, DeprecatedString resolved_import_path, JaktInternal::Dictionary<size_t,ids::StructId> builtin_implementation_structs, bool is_root) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Module (move(id), move(name), move(functions), move(structures), move(enums), move(scopes), move(types), move(traits), move(variables), move(imports), move(resolved_import_path), move(builtin_implementation_structs), move(is_root)))); return o; }
ErrorOr<ids::VarId> types::Module::add_variable(NonnullRefPtr<types::CheckedVariable> const checked_variable) {
{
size_t const new_id = ((((*this).variables)).size());
TRY((((((*this).variables)).push(checked_variable))));
return ids::VarId(((*this).id),new_id);
}
}

ErrorOr<ids::TypeId> types::Module::new_type_variable(JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> const implemented_traits) {
{
size_t const new_id = ((((*this).types)).size());
JaktInternal::DynamicArray<ids::TypeId> const empty_implementation = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
JaktInternal::DynamicArray<ids::TypeId> const trait_implementations = implemented_traits.value_or_lazy_evaluated([&] { return empty_implementation; });
TRY((((((*this).types)).push(TRY((types::Type::template __jakt_create<typename types::Type::TypeVariable>(parser::CheckedQualifiers(false),TRY((__jakt_format((StringView::from_string_literal("T{}"sv)),new_id))),trait_implementations,false)))))));
return ids::TypeId(((*this).id),new_id);
}
}

ErrorOr<DeprecatedString> types::GenericInferences::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("GenericInferences("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("values: {}", values));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> types::GenericInferences::set_all(JaktInternal::DynamicArray<types::CheckedGenericParameter> const keys,JaktInternal::DynamicArray<ids::TypeId> const values) {
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
TRY((((*this).set(key,value))));
}

}
}

}
return {};
}

ErrorOr<void> types::GenericInferences::set_from(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const checkpoint) {
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

TRY((((*this).set(key,value))));
}

}
}

}
return {};
}

ErrorOr<JaktInternal::Optional<ids::TypeId>> types::GenericInferences::find_and_map(DeprecatedString const name,NonnullRefPtr<types::CheckedProgram> const& program) const {
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

if (((((((program)))->get_type(type_id)))->index() == 18 /* TypeVariable */)){
DeprecatedString const var_name = ((((((program)))->get_type(type_id)))->get<types::Type::TypeVariable>()).name;
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

types::GenericInferences::GenericInferences(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> a_values) :values(move(a_values)){}

void types::GenericInferences::restore(JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const checkpoint) {
{
(((*this).values) = checkpoint);
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

ErrorOr<JaktInternal::Dictionary<ids::TypeId,ids::TypeId>> types::GenericInferences::perform_checkpoint(bool const reset) {
{
JaktInternal::Dictionary<ids::TypeId,ids::TypeId> const result = ((*this).values);
(((*this).values) = (TRY((Dictionary<ids::TypeId, ids::TypeId>::create_with_entries({})))));
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

TRY(((*this).values).set(key, value));
}

}
}

}
return result;
}
}

JaktInternal::Optional<ids::TypeId> types::GenericInferences::get(ids::TypeId const key) const {
{
return ((((*this).values)).get(key));
}
}

JaktInternal::Dictionary<ids::TypeId,ids::TypeId> types::GenericInferences::iterator() const {
{
return ((*this).values);
}
}

ErrorOr<void> types::GenericInferences::set(ids::TypeId const key,ids::TypeId const value) {
{
if (((key).equals(value))){
outln((StringView::from_string_literal("Warning: Generic parameter {} is being bound to itself"sv)),key);
abort();
}
ids::TypeId const mapped_value = ((*this).map(value));
if (((key).equals(mapped_value))){
return {};
}
TRY(((*this).values).set(key, mapped_value));
}
return {};
}

ErrorOr<DeprecatedString> types::TypecheckFunctions::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("TypecheckFunctions("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("block: {}, ", block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("register_function: {}", register_function));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::TypecheckFunctions::TypecheckFunctions(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>)> a_block, Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> a_register_function): block(move(a_block)), register_function(move(a_register_function)){}
ErrorOr<NonnullRefPtr<TypecheckFunctions>> types::TypecheckFunctions::__jakt_create(Function<ErrorOr<types::CheckedBlock>(parser::ParsedBlock, ids::ScopeId, types::SafetyMode, JaktInternal::Optional<ids::TypeId>)> block, Function<ErrorOr<ids::FunctionId>(NonnullRefPtr<types::CheckedFunction>)> register_function) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) TypecheckFunctions (move(block), move(register_function)))); return o; }
ErrorOr<DeprecatedString> types::CheckedProgram::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedProgram("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("compiler: {}, ", *compiler));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("modules: {}, ", modules));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("loaded_modules: {}", loaded_modules));
}
TRY(builder.append(")"sv));return builder.to_string(); }
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

ids::ModuleId types::CheckedProgram::prelude_module_id() const {
{
return ids::ModuleId(static_cast<size_t>(0ULL));
}
}

ErrorOr<JaktInternal::Optional<ids::ScopeId>> types::CheckedProgram::find_namespace_in_immediate_children_of_scope(ids::ScopeId const scope_id,DeprecatedString const name,bool const treat_aliases_as_imports) const {
{
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
NonnullRefPtr<types::Scope> const child_scope = TRY((((*this).get_scope(child))));
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

ErrorOr<ids::StructId> types::CheckedProgram::find_struct_in_prelude(DeprecatedString const name) const {
{
ids::ScopeId const scope_id = ((*this).prelude_scope_id());
JaktInternal::Optional<ids::StructId> const struct_id = TRY((((*this).find_struct_in_scope(scope_id,name,true))));
if (((struct_id).has_value())){
return ((struct_id).value());
}
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("internal error: {} builtin definition not found"sv)),name)))))));
}
}

ErrorOr<NonnullRefPtr<types::Scope>> types::CheckedProgram::get_scope(ids::ScopeId const id) const {
{
size_t const max_scope = JaktInternal::checked_sub(((((((((*this).modules))[((((id).module_id)).id)]))->scopes)).size()),static_cast<size_t>(1ULL));
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
(((id).id),max_scope)){
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("scope_id {} does not exist in module"sv)),id)))))));
}
return ((((((((*this).modules))[((((id).module_id)).id)]))->scopes))[((id).id)]);
}
}

bool types::CheckedProgram::is_floating(ids::TypeId const type_id) const {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 10: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 11: {
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

ErrorOr<JaktInternal::Optional<ids::FunctionId>> types::CheckedProgram::find_default_constructors_in_scope(ids::ScopeId const parent_scope_id,DeprecatedString const function_name) const {
{
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const results = TRY((((*this).find_functions_with_name_in_scope(parent_scope_id,function_name,false))));
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
if (((((function)->type)).index() == 2 /* ImplicitConstructor */)){
return id;
}
}

}
}

return JaktInternal::OptionalNone();
}
}

ErrorOr<JaktInternal::Optional<ids::StructId>> types::CheckedProgram::find_struct_in_scope(ids::ScopeId const scope_id,DeprecatedString const name,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<ids::StructId>(scope_id,(([name, this](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<ids::StructId>> {
{
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<ids::StructId> const maybe_struct = ((((scope)->structs)).get(name));
if (((maybe_struct).has_value())){
return  typename utility::IterationDecision<ids::StructId> { typename utility::IterationDecision<ids::StructId>::Break((maybe_struct.value())) } ;
}
return  typename utility::IterationDecision<ids::StructId> { typename utility::IterationDecision<ids::StructId>::Continue() } ;
}
}
)),ignore_mixin_scopes))));
}
}

ErrorOr<JaktInternal::Optional<ids::TypeId>> types::CheckedProgram::find_type_in_scope(ids::ScopeId const scope_id,DeprecatedString const name,bool const ignore_mixin_scopes) const {
{
return ((TRY((((*this).find_type_scope(scope_id,name,ignore_mixin_scopes))))).map([](auto& _value) { return _value.template get<0>(); }));
}
}

ErrorOr<void> types::CheckedProgram::set_loaded_module(DeprecatedString const module_name,types::LoadedModule const loaded_module) {
{
TRY((((((*this).loaded_modules)).set(module_name,loaded_module))));
}
return {};
}

ErrorOr<ids::ScopeId> types::CheckedProgram::find_type_scope_id(ids::TypeId const type_id) {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::ScopeId, ErrorOr<ids::ScopeId>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_struct(struct_id))).scope_id));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_struct(struct_id))).scope_id));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_enum(enum_id))).scope_id));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();ids::EnumId const& enum_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_enum(enum_id))).scope_id));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
ids::TraitId const& trait_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_trait(trait_id)))->scope_id));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();ids::TraitId const& trait_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((*this).get_trait(trait_id)))->scope_id));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::ScopeId,ErrorOr<ids::ScopeId>>{
auto __jakt_enum_value = (((type)->is_builtin()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((((*this).get_struct(TRY((((*this).builtin_implementation_struct(((type)->as_builtin_type()),((*this).prelude_module_id())))))))).scope_id));
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

bool types::CheckedProgram::is_integer(ids::TypeId const type_id) const {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 6: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 14: {
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

ErrorOr<ids::ScopeId> types::CheckedProgram::create_scope(JaktInternal::Optional<ids::ScopeId> const parent_scope_id,bool const can_throw,DeprecatedString const debug_name,ids::ModuleId const module_id,bool const for_block) {
{
if (((parent_scope_id).has_value())){
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
((((((parent_scope_id.value())).module_id)).id),((((*this).modules)).size()))){
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("create_scope: parent_scope_id.module is invalid! No module with id {}."sv)),(((((parent_scope_id.value())).module_id)).id))))))));
}
if ([](size_t const& self, size_t rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
((((parent_scope_id.value())).id),((((((((*this).modules))[(((((parent_scope_id.value())).module_id)).id)]))->scopes)).size()))){
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("create_scope: parent_scope_id.id is invalid! Module {} does not have a scope with id {}."sv)),(((((parent_scope_id.value())).module_id)).id),(((parent_scope_id.value())).id))))))));
}
}
JaktInternal::Optional<DeprecatedString> const none_string = JaktInternal::OptionalNone();
NonnullRefPtr<types::Scope> const scope = TRY((types::Scope::__jakt_create(none_string,JaktInternal::OptionalNone(),(TRY((Dictionary<DeprecatedString, ids::VarId>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, types::Value>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, ids::StructId>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, JaktInternal::DynamicArray<ids::FunctionId>>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, ids::EnumId>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, ids::TypeId>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, ids::TraitId>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, ids::ModuleId>::create_with_entries({})))),(TRY((Dictionary<DeprecatedString, ids::ScopeId>::create_with_entries({})))),parent_scope_id,JaktInternal::OptionalNone(),(TRY((DynamicArray<ids::ScopeId>::create_with({})))),can_throw,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),(TRY((DynamicArray<parser::IncludeAction>::create_with({})))),(TRY((DynamicArray<parser::IncludeAction>::create_with({})))),debug_name,(TRY((DynamicArray<ids::ScopeId>::create_with({})))),for_block,JaktInternal::OptionalNone(),(TRY((Dictionary<DeprecatedString, types::SpecializedType>::create_with_entries({})))))));
TRY((((((((((*this).modules))[((module_id).id)]))->scopes)).push(scope))));
return ids::ScopeId(module_id,JaktInternal::checked_sub(((((((((*this).modules))[((module_id).id)]))->scopes)).size()),static_cast<size_t>(1ULL)));
}
}

NonnullRefPtr<types::Module> types::CheckedProgram::get_module(ids::ModuleId const id) const {
{
return ((((*this).modules))[((id).id)]);
}
}

ErrorOr<DeprecatedString> types::CheckedProgram::type_name(ids::TypeId const type_id,bool const debug_mode) const {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
return TRY((((TRY((((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<DeprecatedString>>{
auto __jakt_enum_value = (((((type)->qualifiers())).is_immutable));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("const "sv)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})) + (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString,ErrorOr<DeprecatedString>>{
auto __jakt_enum_value = (debug_mode);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(TRY((((TRY((__jakt_format((StringView::from_string_literal("({}@{}) "sv)),((type_id).id),((((type_id).module)).id))))) + (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 18: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("var "sv)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}))))));
}
else {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8(""sv)));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))))) + (({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 17: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("never"sv)));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("f32"sv)));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("f64"sv)));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i8"sv)));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i16"sv)));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i32"sv)));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i64"sv)));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u8"sv)));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u16"sv)));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u32"sv)));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u64"sv)));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("usize"sv)));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("c_char"sv)));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("c_int"sv)));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("bool"sv)));
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("void"sv)));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("unknown"sv)));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("builtin(String)"sv)));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Dependent>();ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("{}::{}"sv)),TRY((((*this).type_name(namespace_type,debug_mode)))),name))));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_trait(id)))->name));
};/*case end*/
case 31: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Self"sv)));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_137; {
JaktInternal::DynamicArray<DeprecatedString> param_names = (TRY((DynamicArray<DeprecatedString>::create_with({}))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId x = (_magic_value.value());
{
TRY((((param_names).push(TRY((((*this).type_name(x,debug_mode))))))));
}

}
}

DeprecatedString const return_type = TRY((((*this).type_name(return_type_id,debug_mode))));
__jakt_var_137 = TRY((__jakt_format((StringView::from_string_literal("fn({}) -> {}"sv)),TRY((utility::join(param_names,TRY(DeprecatedString::from_utf8(", "sv))))),return_type))); goto __jakt_label_131;

}
__jakt_label_131:; __jakt_var_137.release_value(); }));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_enum(id))).name));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((*this).get_struct(id))).name));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_138; {
DeprecatedString output = TRY((__jakt_format((StringView::from_string_literal("enum {}"sv)),((((*this).get_enum(id))).name))));
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8("<"sv)))));
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
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).type_name(arg,debug_mode)))))));
}

}
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(">"sv)))));
__jakt_var_138 = output; goto __jakt_label_132;

}
__jakt_label_132:; __jakt_var_138.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_139; {
DeprecatedString output = TRY((__jakt_format((StringView::from_string_literal("trait {}"sv)),((((*this).get_trait(id)))->name))));
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8("<"sv)))));
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
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).type_name(arg,debug_mode)))))));
}

}
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(">"sv)))));
__jakt_var_139 = output; goto __jakt_label_133;

}
__jakt_label_133:; __jakt_var_139.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_140; {
ids::StructId const array_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Array"sv))))));
ids::StructId const dictionary_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Dictionary"sv))))));
ids::StructId const optional_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Optional"sv))))));
ids::StructId const range_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Range"sv))))));
ids::StructId const set_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Set"sv))))));
ids::StructId const tuple_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("Tuple"sv))))));
ids::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
DeprecatedString output = TRY(DeprecatedString::from_utf8(""sv));
if (((id).equals(array_struct_id))){
(output = TRY((__jakt_format((StringView::from_string_literal("[{}]"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))))));
}
else if (((id).equals(dictionary_struct_id))){
(output = TRY((__jakt_format((StringView::from_string_literal("[{}:{}]"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode)))),TRY((((*this).type_name(((args)[static_cast<i64>(1LL)]),debug_mode))))))));
}
else if (((id).equals(optional_struct_id))){
(output = TRY((__jakt_format((StringView::from_string_literal("{}?"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))))));
}
else if (((id).equals(range_struct_id))){
(output = TRY((__jakt_format((StringView::from_string_literal("{}..{}"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode)))),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))))));
}
else if (((id).equals(set_struct_id))){
(output = TRY((__jakt_format((StringView::from_string_literal("{{{}}}"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))))));
}
else if (((id).equals(tuple_struct_id))){
(output = TRY(DeprecatedString::from_utf8("("sv)));
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
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).type_name(arg,debug_mode)))))));
}

}
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(")"sv)))));
}
else if (((id).equals(weak_ptr_struct_id))){
(output = TRY((__jakt_format((StringView::from_string_literal("weak {}"sv)),TRY((((*this).type_name(((args)[static_cast<i64>(0LL)]),debug_mode))))))));
}
else {
types::CheckedStruct const structure = ((*this).get_struct(id));
(output = ((structure).name));
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8("<"sv)))));
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
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).type_name(arg,debug_mode)))))));
}

}
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(">"sv)))));
}

__jakt_var_140 = output; goto __jakt_label_134;

}
__jakt_label_134:; __jakt_var_140.release_value(); }));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<DeprecatedString> __jakt_var_141; {
DeprecatedString output = ((((*this).get_struct(id))).name);
bool first = true;
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8("<"sv)))));
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
TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(", "sv)))));
}
else {
(first = false);
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY((((*this).type_name(type_id,debug_mode)))))));
}

}
}

TRY(([](DeprecatedString& self, DeprecatedString rhs) -> ErrorOr<void> {
{
(self = TRY((((self) + (rhs)))));
}
return {};
}
(output,TRY(DeprecatedString::from_utf8(">"sv)))));
__jakt_var_141 = output; goto __jakt_label_135;

}
__jakt_label_135:; __jakt_var_141.release_value(); }));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::TypeVariable>();DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("raw {}"sv)),TRY((((*this).type_name(type_id,debug_mode))))))));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("&{}"sv)),TRY((((*this).type_name(type_id,debug_mode))))))));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((__jakt_format((StringView::from_string_literal("&mut {}"sv)),TRY((((*this).type_name(type_id,debug_mode))))))));
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Const>();
types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::comptime_format_impl(TRY(DeprecatedString::from_utf8("comptime {}"sv)),(((TRY((DynamicArray<types::Value>::create_with({value})))))[(JaktInternal::Range<i64>{static_cast<i64>(0LL),static_cast<i64>(9223372036854775807LL)})]),((*this))))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})))));
}
}

ErrorOr<JaktInternal::Optional<bool>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope_impl(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<bool>>(ids::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback,bool const ignore_mixin_scopes) const {
{
if (ignore_mixin_scopes){
return TRY((((*this).for_each_scope_accessible_unqualified_from_scope_direct_chain(scope_id,callback))));
}
AK::Queue<ids::ScopeId> scopes_to_check = AK::Queue<ids::ScopeId>();
JaktInternal::Set<ids::ScopeId> seen = (TRY((Set<ids::ScopeId>::create_with_values({}))));
((scopes_to_check).enqueue(scope_id));
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((TRY((((*this).get_scope(scope_id)))))->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
((scopes_to_check).enqueue(child));
}

}
}

while ((!(((scopes_to_check).is_empty())))){
ids::ScopeId const scope_id = ((scopes_to_check).dequeue());
if (((seen).contains(scope_id))){
continue;
}
TRY((((seen).add(scope_id))));
typename utility::IterationDecision<bool> const res = TRY((callback(scope_id,JaktInternal::OptionalNone(),false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<bool>>::Break>();
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
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
{
JaktInternal::DictionaryIterator<DeprecatedString,ids::ScopeId> _magic = ((((scope)->aliases)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,ids::ScopeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,ids::ScopeId> name__alias__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,ids::ScopeId> const jakt__name__alias__ = name__alias__;
DeprecatedString const name = ((jakt__name__alias__).template get<0>());
ids::ScopeId const alias = ((jakt__name__alias__).template get<1>());

typename utility::IterationDecision<bool> const res = TRY((callback(alias,name,true)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<bool>>::Break>();
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

if (((((scope)->parent)).has_value())){
((scopes_to_check).enqueue((((scope)->parent).value())));
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((TRY((((*this).get_scope((((scope)->parent).value()))))))->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
((scopes_to_check).enqueue(child));
}

}
}

}
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->resolution_mixins)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId entry = (_magic_value.value());
{
((scopes_to_check).enqueue(entry));
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((TRY((((*this).get_scope(entry)))))->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
((scopes_to_check).enqueue(child));
}

}
}

}

}
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
((scopes_to_check).enqueue(child));
}

}
}

}
ids::ModuleId const module_id = ((scope_id).module_id);
ids::ScopeId const search_scope_id = ids::ScopeId(module_id,static_cast<size_t>(0ULL));
NonnullRefPtr<types::Scope> const search_scope = TRY((((*this).get_scope(search_scope_id))));
{
JaktInternal::DictionaryIterator<DeprecatedString,ids::ModuleId> _magic = ((((search_scope)->imports)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<DeprecatedString,ids::ModuleId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<DeprecatedString,ids::ModuleId> name__module__ = (_magic_value.value());
{
JaktInternal::Tuple<DeprecatedString,ids::ModuleId> const jakt__name__module__ = name__module__;
DeprecatedString const name = ((jakt__name__module__).template get<0>());
ids::ModuleId const module = ((jakt__name__module__).template get<1>());

ids::ScopeId const import_scope_id = ids::ScopeId(module,static_cast<size_t>(0ULL));
typename utility::IterationDecision<bool> const res = TRY((callback(import_scope_id,name,false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(res);
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<bool>>::Break>();
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

ErrorOr<bool> types::CheckedProgram::is_scope_directly_accessible_from(ids::ScopeId const check_scope_id,ids::ScopeId const scope_id,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<bool>(scope_id,(([check_scope_id](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<bool>> {
{
if (((check_scope_id).equals(scope_id))){
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Break(true) } ;
}
return  typename utility::IterationDecision<bool> { typename utility::IterationDecision<bool>::Continue() } ;
}
}
)),ignore_mixin_scopes)))).value_or_lazy_evaluated([&] { return false; });
}
}

ErrorOr<bool> types::CheckedProgram::is_string(ids::TypeId const type_id) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *((*this).get_type(type_id));
switch(__jakt_match_variant.index()) {
case 13: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("String"sv))))))).equals(struct_id)));
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

ids::ScopeId types::CheckedProgram::prelude_scope_id() const {
{
return ids::ScopeId(ids::ModuleId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL));
}
}

NonnullRefPtr<types::CheckedTrait> types::CheckedProgram::get_trait(ids::TraitId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->traits))[((id).id)]);
}
}

NonnullRefPtr<types::CheckedVariable> types::CheckedProgram::get_variable(ids::VarId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->variables))[((id).id)]);
}
}

types::CheckedProgram::CheckedProgram(NonnullRefPtr<compiler::Compiler> a_compiler, JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> a_modules, JaktInternal::Dictionary<DeprecatedString,types::LoadedModule> a_loaded_modules): compiler(move(a_compiler)), modules(move(a_modules)), loaded_modules(move(a_loaded_modules)){}
ErrorOr<NonnullRefPtr<CheckedProgram>> types::CheckedProgram::__jakt_create(NonnullRefPtr<compiler::Compiler> compiler, JaktInternal::DynamicArray<NonnullRefPtr<types::Module>> modules, JaktInternal::Dictionary<DeprecatedString,types::LoadedModule> loaded_modules) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) CheckedProgram (move(compiler), move(modules), move(loaded_modules)))); return o; }
ErrorOr<ids::ModuleId> types::CheckedProgram::create_module(DeprecatedString const name,bool const is_root,JaktInternal::Optional<DeprecatedString> const path) {
{
size_t const new_id = ((((*this).modules)).size());
ids::ModuleId const module_id = ids::ModuleId(new_id);
NonnullRefPtr<types::Module> const module = TRY((types::Module::__jakt_create(module_id,name,(TRY((DynamicArray<NonnullRefPtr<types::CheckedFunction>>::create_with({})))),(TRY((DynamicArray<types::CheckedStruct>::create_with({})))),(TRY((DynamicArray<types::CheckedEnum>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<types::Scope>>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<typename types::Type>>::create_with({TRY((types::Type::template __jakt_create<typename types::Type::Void>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::Bool>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::U8>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::U16>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::U32>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::U64>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::I8>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::I16>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::I32>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::I64>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::F32>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::F64>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::Usize>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::JaktString>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::CChar>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::CInt>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::Unknown>(parser::CheckedQualifiers(false)))), TRY((types::Type::template __jakt_create<typename types::Type::Never>(parser::CheckedQualifiers(false))))})))),(TRY((DynamicArray<NonnullRefPtr<types::CheckedTrait>>::create_with({})))),(TRY((DynamicArray<NonnullRefPtr<types::CheckedVariable>>::create_with({})))),(TRY((DynamicArray<ids::ModuleId>::create_with({})))),path.value_or_lazy_evaluated([&] { return (((((((*this).compiler))->current_file_path()).value())).to_string()); }),(TRY((Dictionary<size_t, ids::StructId>::create_with_entries({})))),is_root)));
TRY((((((*this).modules)).push(module))));
return module_id;
}
}

NonnullRefPtr<types::CheckedFunction> types::CheckedProgram::get_function(ids::FunctionId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->functions))[((id).id)]);
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> types::CheckedProgram::find_type_scope(ids::ScopeId const scope_id,DeprecatedString const name,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>(scope_id,(([name, this](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>> {
{
JaktInternal::Optional<ids::TypeId> const maybe_type = ((((TRY((((*this).get_scope(scope_id)))))->types)).get(name));
if (((maybe_type).has_value())){
return  typename utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>> { typename utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>::Break((Tuple{(maybe_type.value()), scope_id})) } ;
}
return  typename utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>> { typename utility::IterationDecision<JaktInternal::Tuple<ids::TypeId,ids::ScopeId>>::Continue() } ;
}
}
)),ignore_mixin_scopes))));
}
}

ErrorOr<ids::StructId> types::CheckedProgram::builtin_implementation_struct(types::BuiltinType const builtin,ids::ModuleId const for_module) {
{
size_t const id = ((builtin).id());
NonnullRefPtr<types::Module> module = ((((*this).modules))[((for_module).id)]);
if (((((module)->builtin_implementation_structs)).contains(id))){
return ((((module)->builtin_implementation_structs))[id]);
}
ids::ScopeId const scope_id = TRY((((*this).create_scope(JaktInternal::OptionalNone(),false,TRY((__jakt_format((StringView::from_string_literal("builtin({})"sv)),TRY((((builtin).constructor_name())))))),for_module,false))));
JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> const trait_implementations = (TRY((Dictionary<DeprecatedString, JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>>::create_with_entries({}))));
utility::Span const name_span = utility::Span(utility::FileId(static_cast<size_t>(0ULL)),static_cast<size_t>(0ULL),static_cast<size_t>(0ULL));
ids::StructId const struct_id = ids::StructId(for_module,((((module)->structures)).size()));
ids::TypeId const struct_type_id = TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(parser::CheckedQualifiers(false),struct_id))),for_module,false))));
types::CheckedStruct const struct_ = types::CheckedStruct(TRY((__jakt_format((StringView::from_string_literal("Builtin_{}"sv)),TRY((((builtin).constructor_name())))))),name_span,(TRY((DynamicArray<types::CheckedGenericParameter>::create_with({})))),JaktInternal::OptionalNone(),(TRY((DynamicArray<types::CheckedField>::create_with({})))),scope_id, parser::DefinitionLinkage { typename parser::DefinitionLinkage::External() } ,trait_implementations, parser::RecordType { typename parser::RecordType::Struct((TRY((DynamicArray<parser::ParsedField>::create_with({})))),JaktInternal::OptionalNone()) } ,struct_type_id,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),types::builtin(builtin));
TRY((((((module)->structures)).push(struct_))));
TRY(((module)->builtin_implementation_structs).set(id, struct_id));
return struct_id;
}
}

ErrorOr<JaktInternal::Optional<types::Value>> types::CheckedProgram::find_comptime_binding_in_scope(ids::ScopeId const scope_id,DeprecatedString const name,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<types::Value>(scope_id,(([name, this](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<types::Value>> {
{
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<types::Value> const maybe_binding = ((((scope)->comptime_bindings)).get(name));
if (((maybe_binding).has_value())){
return  typename utility::IterationDecision<types::Value> { typename utility::IterationDecision<types::Value>::Break((maybe_binding.value())) } ;
}
return  typename utility::IterationDecision<types::Value> { typename utility::IterationDecision<types::Value>::Continue() } ;
}
}
)),ignore_mixin_scopes))));
}
}

ErrorOr<ids::TypeId> types::CheckedProgram::substitute_typevars_in_type_helper(ids::TypeId const type_id,types::GenericInferences const generic_inferences,ids::ModuleId const module_id) {
{
NonnullRefPtr<typename types::Type> const type_ = ((*this).get_type(type_id));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<ids::TypeId>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.index()) {
case 18: {
{
JaktInternal::Optional<ids::TypeId> const replacement_type_id = ((generic_inferences).get(type_id));
if (((replacement_type_id).has_value())){
return (replacement_type_id.value());
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Dependent>();ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
DeprecatedString const& name = __jakt_match_value.name;
{
ids::TypeId const mapped_type_id = TRY((((*this).substitute_typevars_in_type(namespace_type,generic_inferences,module_id))));
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(mapped_type_id));
if (((type)->index() == 18 /* TypeVariable */)){
return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Dependent>(parser::CheckedQualifiers(false),mapped_type_id,name))),module_id,false))));
}
JaktInternal::Optional<types::StructLikeId> const struct_like_id = TRY((types::StructLikeId::from_type_id(mapped_type_id,((*this)))));
if (((struct_like_id).has_value())){
ids::ScopeId const scope_id = TRY(((((struct_like_id.value())).associated_scope_id(((*this))))));
JaktInternal::Optional<ids::TypeId> const found_type = TRY((((*this).find_type_in_scope(scope_id,name,false))));
if (((found_type).has_value())){
types::GenericInferences copied_inferences = generic_inferences;
if ((((((struct_like_id.value())).generic_arguments())).has_value())){
TRY((((copied_inferences).set_all(TRY(((((struct_like_id.value())).generic_parameters_as_checked(((*this)))))),((((struct_like_id.value())).generic_arguments()).value())))));
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
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<ids::TypeId> new_args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((new_args).ensure_capacity(((args).size())))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
TRY((((new_args).push(TRY((((*this).substitute_typevars_in_type(arg,generic_inferences,module_id))))))));
}

}
}

return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericTraitInstance>(parser::CheckedQualifiers(false),id,new_args))),module_id,false))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<ids::TypeId> new_args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((new_args).ensure_capacity(((args).size())))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
TRY((((new_args).push(TRY((((*this).substitute_typevars_in_type(arg,generic_inferences,module_id))))))));
}

}
}

return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(parser::CheckedQualifiers(false),id,new_args))),module_id,false))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
{
JaktInternal::DynamicArray<ids::TypeId> new_args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((new_args).ensure_capacity(((args).size())))));
{
JaktInternal::ArrayIterator<ids::TypeId> _magic = ((args).iterator());
for (;;){
JaktInternal::Optional<ids::TypeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::TypeId arg = (_magic_value.value());
{
TRY((((new_args).push(TRY((((*this).substitute_typevars_in_type(arg,generic_inferences,module_id))))))));
}

}
}

return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericEnumInstance>(parser::CheckedQualifiers(false),id,new_args))),module_id,false))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
ids::StructId const& struct_id = __jakt_match_value.value;
{
types::CheckedStruct const struct_ = ((*this).get_struct(struct_id));
if ((!(((((struct_).generic_parameters)).is_empty())))){
JaktInternal::DynamicArray<ids::TypeId> new_args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((new_args).ensure_capacity(((((struct_).generic_parameters)).size())))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter arg = (_magic_value.value());
{
TRY((((new_args).push(TRY((((*this).substitute_typevars_in_type(((arg).type_id),generic_inferences,module_id))))))));
}

}
}

return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(parser::CheckedQualifiers(false),struct_id,new_args))),module_id,false))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
ids::EnumId const& enum_id = __jakt_match_value.value;
{
types::CheckedEnum const enum_ = ((*this).get_enum(enum_id));
if ((!(((((enum_).generic_parameters)).is_empty())))){
JaktInternal::DynamicArray<ids::TypeId> new_args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((new_args).ensure_capacity(((((enum_).generic_parameters)).size())))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter arg = (_magic_value.value());
{
TRY((((new_args).push(TRY((((*this).substitute_typevars_in_type(((arg).type_id),generic_inferences,module_id))))))));
}

}
}

return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericEnumInstance>(parser::CheckedQualifiers(false),enum_id,new_args))),module_id,false))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
ids::TypeId const& rawptr_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename types::Type> const rawptr_type = TRY((types::Type::template __jakt_create<typename types::Type::RawPtr>(parser::CheckedQualifiers(false),TRY((((*this).substitute_typevars_in_type(rawptr_type_id,generic_inferences,module_id)))))));
return TRY((((*this).find_or_add_type_id(rawptr_type,module_id,false))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
ids::TypeId const& ref_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename types::Type> const ref_type = TRY((types::Type::template __jakt_create<typename types::Type::Reference>(parser::CheckedQualifiers(false),TRY((((*this).substitute_typevars_in_type(ref_type_id,generic_inferences,module_id)))))));
return TRY((((*this).find_or_add_type_id(ref_type,module_id,false))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
ids::TypeId const& ref_type_id = __jakt_match_value.value;
{
NonnullRefPtr<typename types::Type> const ref_type = TRY((types::Type::template __jakt_create<typename types::Type::MutableReference>(parser::CheckedQualifiers(false),TRY((((*this).substitute_typevars_in_type(ref_type_id,generic_inferences,module_id)))))));
return TRY((((*this).find_or_add_type_id(ref_type,module_id,false))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
{
JaktInternal::DynamicArray<ids::TypeId> new_params = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
TRY((((new_params).ensure_capacity(((params).size())))));
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
TRY((((new_params).push(new_param))));
}

}
}

ids::TypeId const return_type_substitute = TRY((((*this).substitute_typevars_in_type(return_type_id,generic_inferences,module_id))));
(is_different = (is_different || (!(((return_type_substitute).equals(return_type_id))))));
if ((!(is_different))){
return type_id;
}
NonnullRefPtr<types::CheckedFunction> const previous_function = ((*this).get_function(pseudo_function_id));
JaktInternal::DynamicArray<types::CheckedParameter> replacement_params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
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
types::CheckedParameter const new_param = types::CheckedParameter(((param).requires_label),TRY((types::CheckedVariable::__jakt_create(((((param).variable))->name),((new_params)[i]),((((param).variable))->is_mutable),((((param).variable))->definition_span),((((param).variable))->type_span),((((param).variable))->visibility),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()))),((param).default_value));
TRY((((replacement_params).push(new_param))));
}

}
}

NonnullRefPtr<types::CheckedFunction> const new_function = TRY((types::CheckedFunction::__jakt_create(((previous_function)->name),((previous_function)->name_span),((previous_function)->visibility),return_type_substitute,((previous_function)->return_type_span),replacement_params,((previous_function)->generics),((previous_function)->block),can_throw,((previous_function)->type),((previous_function)->linkage),((previous_function)->function_scope_id),((previous_function)->struct_id),((previous_function)->is_instantiated),((previous_function)->parsed_function),((previous_function)->is_comptime),((previous_function)->is_virtual),((previous_function)->is_override),((previous_function)->is_unsafe),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(), parser::InlineState { typename parser::InlineState::Default() } )));
ids::FunctionId const new_function_id = TRY((((((((*this).modules))[((module_id).id)]))->add_function(new_function))));
return TRY((((*this).find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Function>(parser::CheckedQualifiers(false),new_params,can_throw,return_type_substitute,new_function_id))),module_id,false))));
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

ErrorOr<JaktInternal::Optional<bool>> types::CheckedProgram::for_each_scope_accessible_unqualified_from_scope_direct_chain(ids::ScopeId const scope_id,Function<ErrorOr<typename utility::IterationDecision<bool>>(ids::ScopeId, JaktInternal::Optional<DeprecatedString>, bool)> const& callback) const {
{
ids::ScopeId current_scope = scope_id;
for (;;){
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(current_scope))));
typename utility::IterationDecision<bool> const maybe_result = TRY((callback(current_scope,JaktInternal::OptionalNone(),false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(maybe_result);
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<bool>>::Break>();
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
{
JaktInternal::ArrayIterator<ids::ScopeId> _magic = ((((scope)->children)).iterator());
for (;;){
JaktInternal::Optional<ids::ScopeId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ids::ScopeId child = (_magic_value.value());
{
typename utility::IterationDecision<bool> const maybe_result = TRY((callback(child,JaktInternal::OptionalNone(),false)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<JaktInternal::Optional<bool>>>{
auto&& __jakt_enum_value = JaktInternal::deref_if_ref_pointer(maybe_result);
if (__jakt_enum_value.index() == 0 /* Break */) {
auto& __jakt_match_value = __jakt_enum_value.template get<typename JaktInternal::RemoveRefPtr<utility::IterationDecision<bool>>::Break>();
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

if (((((scope)->parent)).has_value())){
ids::ScopeId const id = (((scope)->parent).value());
(current_scope = id);
}
else {
break;
}

}
return JaktInternal::OptionalNone();
}
}

i64 types::CheckedProgram::get_bits(ids::TypeId const type_id) const {
{
return ((((*this).get_type(type_id)))->get_bits());
}
}

NonnullRefPtr<typename types::Type> types::CheckedProgram::get_type(ids::TypeId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->types))[((id).id)]);
}
}

ErrorOr<ids::TypeId> types::CheckedProgram::find_or_add_type_id(NonnullRefPtr<typename types::Type> const type,ids::ModuleId const module_id,bool const only_in_current_module) {
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

TRY((((((((((*this).modules))[((module_id).id)]))->types)).push(type))));
return ids::TypeId(module_id,JaktInternal::checked_sub(((((((((*this).modules))[((module_id).id)]))->types)).size()),static_cast<size_t>(1ULL)));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>>> types::CheckedProgram::find_namespace_in_scope(ids::ScopeId const scope_id,DeprecatedString const name,bool const treat_aliases_as_imports,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<ids::ScopeId,bool>>(scope_id,(([name, treat_aliases_as_imports, this](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>> {
{
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<DeprecatedString> const effective_name = name_override.value_or_lazy_evaluated_optional([&] { return ((scope)->namespace_name); });
bool const is_import = (((name_override).has_value()) && (!(is_alias)));
if ((((effective_name).has_value()) && (((effective_name.value())) == (name)))){
return  typename utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>> { typename utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>::Break((Tuple{scope_id, (is_import || (is_alias && treat_aliases_as_imports))})) } ;
}
return  typename utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>> { typename utility::IterationDecision<JaktInternal::Tuple<ids::ScopeId,bool>>::Continue() } ;
}
}
)),ignore_mixin_scopes))));
}
}

ErrorOr<JaktInternal::Optional<ids::TraitId>> types::CheckedProgram::find_trait_in_scope(ids::ScopeId const scope_id,DeprecatedString const name,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<ids::TraitId>(scope_id,(([name, this](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<ids::TraitId>> {
{
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<ids::TraitId> const maybe_trait = ((((scope)->traits)).get(name));
if (((maybe_trait).has_value())){
return  typename utility::IterationDecision<ids::TraitId> { typename utility::IterationDecision<ids::TraitId>::Break((maybe_trait.value())) } ;
}
return  typename utility::IterationDecision<ids::TraitId> { typename utility::IterationDecision<ids::TraitId>::Continue() } ;
}
}
)),ignore_mixin_scopes))));
}
}

types::CheckedEnum types::CheckedProgram::get_enum(ids::EnumId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->enums))[((id).id)]);
}
}

ErrorOr<ids::TypeId> types::CheckedProgram::apply_qualifiers_to_type(parser::CheckedQualifiers const qualifiers,ids::TypeId const type_id) {
{
NonnullRefPtr<typename types::Type> const type = ((*this).get_type(type_id));
if ([](parser::CheckedQualifiers const& self, parser::CheckedQualifiers rhs) -> bool {
{
return (!(((self).equals(rhs))));
}
}
(qualifiers,((type)->qualifiers()))){
return TRY((((*this).find_or_add_type_id(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::Type>, ErrorOr<ids::TypeId>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Void>(qualifiers))));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Bool>(qualifiers))));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::U8>(qualifiers))));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::U16>(qualifiers))));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::U32>(qualifiers))));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::U64>(qualifiers))));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::I8>(qualifiers))));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::I16>(qualifiers))));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::I32>(qualifiers))));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::I64>(qualifiers))));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::F32>(qualifiers))));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::F64>(qualifiers))));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Usize>(qualifiers))));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::JaktString>(qualifiers))));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::CChar>(qualifiers))));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::CInt>(qualifiers))));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Unknown>(parser::CheckedQualifiers(false)))));
};/*case end*/
case 17: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Never>(parser::CheckedQualifiers(false)))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::TypeVariable>();DeprecatedString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<ids::TypeId> const& trait_implementations = __jakt_match_value.trait_implementations;
bool const& is_value = __jakt_match_value.is_value;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::TypeVariable>(qualifiers,name,trait_implementations,is_value))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Dependent>();ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Dependent>(qualifiers,namespace_type,name))));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(qualifiers,id,args))));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();ids::EnumId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::GenericEnumInstance>(qualifiers,id,args))));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();ids::TraitId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::GenericTraitInstance>(qualifiers,id,args))));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::GenericResolvedType>(qualifiers,id,args))));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(qualifiers,id))));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Enum>(qualifiers,id))));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::RawPtr>(qualifiers,id))));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Trait>(qualifiers,id))));
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Reference>(qualifiers,id))));
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
ids::TypeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::MutableReference>(qualifiers,id))));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::FunctionId const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Function>(qualifiers,params,can_throw,return_type_id,pseudo_function_id))));
};/*case end*/
case 31: {
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Self>(qualifiers))));
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Const>();
types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::Type::template __jakt_create<typename types::Type::Const>(qualifiers,value))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),((type_id).module),true))));
}
else {
return type_id;
}

}
}

ErrorOr<JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>>> types::CheckedProgram::find_functions_with_name_in_scope(ids::ScopeId const parent_scope_id,DeprecatedString const function_name,bool const ignore_mixin_scopes) const {
{
return ((TRY((((*this).find_scoped_functions_with_name_in_scope(parent_scope_id,function_name,ignore_mixin_scopes))))).map([](auto& _value) { return _value.template get<0>(); }));
}
}

ErrorOr<JaktInternal::Optional<NonnullRefPtr<types::CheckedVariable>>> types::CheckedProgram::find_var_in_scope(ids::ScopeId const scope_id,DeprecatedString const var,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<NonnullRefPtr<types::CheckedVariable>>(scope_id,(([var, this](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>> {
{
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<ids::VarId> const maybe_var = ((((scope)->vars)).get(var));
if (((maybe_var).has_value())){
return  typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>> { typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>::Break(((*this).get_variable((maybe_var.value())))) } ;
}
return  typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>> { typename utility::IterationDecision<NonnullRefPtr<types::CheckedVariable>>::Continue() } ;
}
}
)),ignore_mixin_scopes))));
}
}

ErrorOr<JaktInternal::Optional<ids::FunctionId>> types::CheckedProgram::find_function_in_scope(ids::ScopeId const parent_scope_id,DeprecatedString const function_name) const {
{
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const results = TRY((((*this).find_functions_with_name_in_scope(parent_scope_id,function_name,false))));
if ((!(((results).has_value())))){
return JaktInternal::OptionalNone();
}
JaktInternal::DynamicArray<ids::FunctionId> const functions = ((results).value());
if (((((functions).size())) != (static_cast<size_t>(1ULL)))){
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("internal error: found {} functions with name '{}', but expected 1"sv)),((functions).size()),function_name)))))));
}
return ((functions)[static_cast<i64>(0LL)]);
}
}

types::CheckedStruct types::CheckedProgram::get_struct(ids::StructId const id) const {
{
return ((((((((*this).modules))[((((id).module)).id)]))->structures))[((id).id)]);
}
}

ErrorOr<JaktInternal::Optional<ids::StructId>> types::CheckedProgram::check_and_extract_weak_ptr(ids::StructId const struct_id,JaktInternal::DynamicArray<ids::TypeId> const args) const {
{
ids::StructId const weak_ptr_struct_id = TRY((((*this).find_struct_in_prelude(TRY(DeprecatedString::from_utf8("WeakPtr"sv))))));
if (((struct_id).equals(weak_ptr_struct_id))){
if (((((args).size())) != (static_cast<size_t>(1ULL)))){
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("Internal error: Generic type is WeakPtr but there are not exactly 1 type parameter. There are {} parameters."sv)),((args).size()))))))));
}
ids::TypeId const inner_type_id = ((args)[static_cast<i64>(0LL)]);
NonnullRefPtr<typename types::Type> const inner_type = ((*this).get_type(inner_type_id));
if (((inner_type)->index() == 24 /* Struct */)){
ids::StructId const inner_struct_id = ((inner_type)->get<types::Type::Struct>()).value;
return inner_struct_id;
}
utility::panic(TRY((__jakt_format((StringView::from_string_literal("Internal error: Inner type of WeakPtr is not a struct. It is {}."sv)),inner_type))));
}
else {
return JaktInternal::OptionalNone();
}

}
}

ErrorOr<JaktInternal::Optional<ids::EnumId>> types::CheckedProgram::find_enum_in_scope(ids::ScopeId const scope_id,DeprecatedString const name,bool const ignore_mixin_scopes) const {
{
return TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<ids::EnumId>(scope_id,(([name, this](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<ids::EnumId>> {
{
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<ids::EnumId> const maybe_enum = ((((scope)->enums)).get(name));
if (((maybe_enum).has_value())){
return  typename utility::IterationDecision<ids::EnumId> { typename utility::IterationDecision<ids::EnumId>::Break((maybe_enum.value())) } ;
}
return  typename utility::IterationDecision<ids::EnumId> { typename utility::IterationDecision<ids::EnumId>::Continue() } ;
}
}
)),ignore_mixin_scopes))));
}
}

JaktInternal::Optional<types::LoadedModule> types::CheckedProgram::get_loaded_module(DeprecatedString const module_name) const {
{
return ((((*this).loaded_modules)).get(module_name));
}
}

ErrorOr<JaktInternal::Optional<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> types::CheckedProgram::find_scoped_functions_with_name_in_scope(ids::ScopeId const parent_scope_id,DeprecatedString const function_name,bool const ignore_mixin_scopes) const {
{
JaktInternal::DynamicArray<ids::FunctionId> result_ids = (TRY((DynamicArray<ids::FunctionId>::create_with({}))));
JaktInternal::Optional<ids::ScopeId> result_scope = JaktInternal::OptionalNone();
TRY((((*this).template for_each_scope_accessible_unqualified_from_scope<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>(parent_scope_id,(([function_name, &result_ids, &result_scope, this](ids::ScopeId scope_id, JaktInternal::Optional<DeprecatedString> name_override, bool is_alias) -> ErrorOr<typename utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>> {
{
NonnullRefPtr<types::Scope> const scope = TRY((((*this).get_scope(scope_id))));
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const maybe_functions = ((((scope)->functions)).get(function_name));
if (((maybe_functions).has_value())){
TRY((((result_ids).push_values((((maybe_functions.value())))))));
if ((!(((result_scope).has_value())))){
(result_scope = scope_id);
}
}
return  typename utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>> { typename utility::IterationDecision<JaktInternal::Tuple<JaktInternal::DynamicArray<ids::FunctionId>,ids::ScopeId>>::Continue() } ;
}
}
)),ignore_mixin_scopes))));
if ((!(result_scope).has_value())){
return JaktInternal::OptionalNone();
}
return (Tuple{result_ids, (result_scope.value())});
}
}

bool types::CheckedProgram::is_signed(ids::TypeId const type_id) const {
{
return ((((*this).get_type(type_id)))->is_signed());
}
}

bool types::CheckedProgram::is_numeric(ids::TypeId const type_id) const {
{
return (((*this).is_integer(type_id)) || ((*this).is_floating(type_id)));
}
}

ErrorOr<types::StructOrEnumId> types::CheckedProgram::find_reflected_primitive(DeprecatedString const primitive) const {
{
ids::ScopeId const scope_id = ((*this).prelude_scope_id());
JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>> const maybe_namespace = TRY((((*this).find_namespace_in_scope(scope_id,TRY(DeprecatedString::from_utf8("Reflect"sv)),false,true))));
if ((!(((maybe_namespace).has_value())))){
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("internal error: builtin namespace 'Reflect' not found"sv)))))))));
}
ids::ScopeId const reflect_namespace_scope_id = (((maybe_namespace.value())).template get<0>());
JaktInternal::Optional<ids::EnumId> const enum_id = TRY((((*this).find_enum_in_scope(reflect_namespace_scope_id,primitive,false))));
if (((enum_id).has_value())){
return  types::StructOrEnumId { typename types::StructOrEnumId::Enum((enum_id.value())) } ;
}
JaktInternal::Optional<ids::StructId> const struct_id = TRY((((*this).find_struct_in_scope(reflect_namespace_scope_id,primitive,false))));
if (((struct_id).has_value())){
return  types::StructOrEnumId { typename types::StructOrEnumId::Struct((struct_id.value())) } ;
}
TRY((((((*this).compiler))->panic(TRY((__jakt_format((StringView::from_string_literal("internal error: definition for reflect builtin '{}' not found"sv)),primitive)))))));
}
}

ErrorOr<DeprecatedString> types::FunctionGenericParameter::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("FunctionGenericParameter("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("kind: {}, ", kind));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("checked_parameter: {}", checked_parameter));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<types::FunctionGenericParameter> types::FunctionGenericParameter::parameter(ids::TypeId const type_id,utility::Span const span) {
{
return types::FunctionGenericParameter( types::FunctionGenericParameterKind { typename types::FunctionGenericParameterKind::Parameter() } ,TRY((types::CheckedGenericParameter::make(type_id,span))));
}
}

ids::TypeId types::FunctionGenericParameter::type_id() const {
{
return ((((*this).checked_parameter)).type_id);
}
}

types::FunctionGenericParameter::FunctionGenericParameter(types::FunctionGenericParameterKind a_kind, types::CheckedGenericParameter a_checked_parameter) :kind(move(a_kind)), checked_parameter(move(a_checked_parameter)){}

ErrorOr<DeprecatedString> types::ResolvedNamespace::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("ResolvedNamespace("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("external_name: {}, ", external_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generic_parameters: {}", generic_parameters));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::ResolvedNamespace::ResolvedNamespace(DeprecatedString a_name, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<JaktInternal::DynamicArray<ids::TypeId>> a_generic_parameters) :name(move(a_name)), external_name(move(a_external_name)), generic_parameters(move(a_generic_parameters)){}

parser::ExternalName types::ResolvedNamespace::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return  parser::ExternalName { typename parser::ExternalName::Plain(((*this).name)) } ; });
}
}

ErrorOr<DeprecatedString> types::FieldRecord::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("FieldRecord("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("struct_id: {}, ", struct_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("field_id: {}", field_id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::FieldRecord::FieldRecord(ids::StructId a_struct_id, ids::VarId a_field_id) :struct_id(move(a_struct_id)), field_id(move(a_field_id)){}

ErrorOr<DeprecatedString> types::CheckedCall::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedCall("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("namespace_: {}, ", namespace_));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("args: {}, ", args));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_args: {}, ", type_args));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("function_id: {}, ", function_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("return_type: {}, ", return_type));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("callee_throws: {}, ", callee_throws));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("external_name: {}, ", external_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("force_inline: {}", force_inline));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedCall::CheckedCall(JaktInternal::DynamicArray<types::ResolvedNamespace> a_namespace_, DeprecatedString a_name, JaktInternal::DynamicArray<JaktInternal::Tuple<DeprecatedString,NonnullRefPtr<typename types::CheckedExpression>>> a_args, JaktInternal::DynamicArray<ids::TypeId> a_type_args, JaktInternal::Optional<ids::FunctionId> a_function_id, ids::TypeId a_return_type, bool a_callee_throws, JaktInternal::Optional<parser::ExternalName> a_external_name, parser::InlineState a_force_inline) :namespace_(move(a_namespace_)), name(move(a_name)), args(move(a_args)), type_args(move(a_type_args)), function_id(move(a_function_id)), return_type(move(a_return_type)), callee_throws(move(a_callee_throws)), external_name(move(a_external_name)), force_inline(move(a_force_inline)){}

parser::ExternalName types::CheckedCall::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return  parser::ExternalName { typename parser::ExternalName::Plain(((*this).name)) } ; });
}
}

ErrorOr<DeprecatedString> types::CheckedBlock::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedBlock("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("statements: {}, ", statements));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("scope_id: {}, ", scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("control_flow: {}, ", control_flow));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("yielded_type: {}, ", yielded_type));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("yielded_none: {}", yielded_none));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedBlock::CheckedBlock(JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedStatement>> a_statements, ids::ScopeId a_scope_id, types::BlockControlFlow a_control_flow, JaktInternal::Optional<ids::TypeId> a_yielded_type, bool a_yielded_none) :statements(move(a_statements)), scope_id(move(a_scope_id)), control_flow(move(a_control_flow)), yielded_type(move(a_yielded_type)), yielded_none(move(a_yielded_none)){}

ErrorOr<DeprecatedString> types::OperatorTraitImplementation::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("OperatorTraitImplementation("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trait_id: {}, ", trait_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trait_generic_arguments: {}, ", trait_generic_arguments));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("call_expression: {}", call_expression));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::OperatorTraitImplementation::OperatorTraitImplementation(ids::TraitId a_trait_id, JaktInternal::DynamicArray<ids::TypeId> a_trait_generic_arguments, types::CheckedCall a_call_expression) :trait_id(move(a_trait_id)), trait_generic_arguments(move(a_trait_generic_arguments)), call_expression(move(a_call_expression)){}

ErrorOr<DeprecatedString> types::LoadedModule::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("LoadedModule("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("module_id: {}, ", module_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("file_id: {}", file_id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::LoadedModule::LoadedModule(ids::ModuleId a_module_id, utility::FileId a_file_id) :module_id(move(a_module_id)), file_id(move(a_file_id)){}

ErrorOr<DeprecatedString> types::ResolvedForallChunk::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("ResolvedForallChunk("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("parameters: {}, ", parameters));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("parsed_namespace: {}, ", parsed_namespace));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generated_scopes: {}", generated_scopes));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::ResolvedForallChunk::ResolvedForallChunk(JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<utility::Span,ids::TypeId>>> a_parameters, parser::ParsedNamespace a_parsed_namespace, JaktInternal::DynamicArray<ids::ScopeId> a_generated_scopes) :parameters(move(a_parameters)), parsed_namespace(move(a_parsed_namespace)), generated_scopes(move(a_generated_scopes)){}

ErrorOr<DeprecatedString> types::SpecializedType::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("SpecializedType("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("base_type_id: {}, ", base_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("arguments: {}, ", arguments));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_id: {}", type_id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::SpecializedType::SpecializedType(ids::TypeId a_base_type_id, JaktInternal::DynamicArray<ids::TypeId> a_arguments, ids::TypeId a_type_id) :base_type_id(move(a_base_type_id)), arguments(move(a_arguments)), type_id(move(a_type_id)){}

ErrorOr<DeprecatedString> types::Scope::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Scope("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("namespace_name: {}, ", namespace_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("external_name: {}, ", external_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("vars: {}, ", vars));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("comptime_bindings: {}, ", comptime_bindings));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("structs: {}, ", structs));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("functions: {}, ", functions));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("enums: {}, ", enums));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("types: {}, ", types));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("traits: {}, ", traits));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("imports: {}, ", imports));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("aliases: {}, ", aliases));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("parent: {}, ", parent));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("alias_scope: {}, ", alias_scope));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("children: {}, ", children));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("can_throw: {}, ", can_throw));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("import_path_if_extern: {}, ", import_path_if_extern));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("alias_path: {}, ", alias_path));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("after_extern_include: {}, ", after_extern_include));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("before_extern_include: {}, ", before_extern_include));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("debug_name: \"{}\", ", debug_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("resolution_mixins: {}, ", resolution_mixins));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_block_scope: {}, ", is_block_scope));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("resolved_forall_chunks: {}, ", resolved_forall_chunks));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("explicitly_specialized_types: {}", explicitly_specialized_types));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::Scope::Scope(JaktInternal::Optional<DeprecatedString> a_namespace_name, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Dictionary<DeprecatedString,ids::VarId> a_vars, JaktInternal::Dictionary<DeprecatedString,types::Value> a_comptime_bindings, JaktInternal::Dictionary<DeprecatedString,ids::StructId> a_structs, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<ids::FunctionId>> a_functions, JaktInternal::Dictionary<DeprecatedString,ids::EnumId> a_enums, JaktInternal::Dictionary<DeprecatedString,ids::TypeId> a_types, JaktInternal::Dictionary<DeprecatedString,ids::TraitId> a_traits, JaktInternal::Dictionary<DeprecatedString,ids::ModuleId> a_imports, JaktInternal::Dictionary<DeprecatedString,ids::ScopeId> a_aliases, JaktInternal::Optional<ids::ScopeId> a_parent, JaktInternal::Optional<ids::ScopeId> a_alias_scope, JaktInternal::DynamicArray<ids::ScopeId> a_children, bool a_can_throw, JaktInternal::Optional<DeprecatedString> a_import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> a_alias_path, JaktInternal::DynamicArray<parser::IncludeAction> a_after_extern_include, JaktInternal::DynamicArray<parser::IncludeAction> a_before_extern_include, DeprecatedString a_debug_name, JaktInternal::DynamicArray<ids::ScopeId> a_resolution_mixins, bool a_is_block_scope, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> a_resolved_forall_chunks, JaktInternal::Dictionary<DeprecatedString,types::SpecializedType> a_explicitly_specialized_types): namespace_name(move(a_namespace_name)), external_name(move(a_external_name)), vars(move(a_vars)), comptime_bindings(move(a_comptime_bindings)), structs(move(a_structs)), functions(move(a_functions)), enums(move(a_enums)), types(move(a_types)), traits(move(a_traits)), imports(move(a_imports)), aliases(move(a_aliases)), parent(move(a_parent)), alias_scope(move(a_alias_scope)), children(move(a_children)), can_throw(move(a_can_throw)), import_path_if_extern(move(a_import_path_if_extern)), alias_path(move(a_alias_path)), after_extern_include(move(a_after_extern_include)), before_extern_include(move(a_before_extern_include)), debug_name(move(a_debug_name)), resolution_mixins(move(a_resolution_mixins)), is_block_scope(move(a_is_block_scope)), resolved_forall_chunks(move(a_resolved_forall_chunks)), explicitly_specialized_types(move(a_explicitly_specialized_types)){}
ErrorOr<NonnullRefPtr<Scope>> types::Scope::__jakt_create(JaktInternal::Optional<DeprecatedString> namespace_name, JaktInternal::Optional<parser::ExternalName> external_name, JaktInternal::Dictionary<DeprecatedString,ids::VarId> vars, JaktInternal::Dictionary<DeprecatedString,types::Value> comptime_bindings, JaktInternal::Dictionary<DeprecatedString,ids::StructId> structs, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<ids::FunctionId>> functions, JaktInternal::Dictionary<DeprecatedString,ids::EnumId> enums, JaktInternal::Dictionary<DeprecatedString,ids::TypeId> types, JaktInternal::Dictionary<DeprecatedString,ids::TraitId> traits, JaktInternal::Dictionary<DeprecatedString,ids::ModuleId> imports, JaktInternal::Dictionary<DeprecatedString,ids::ScopeId> aliases, JaktInternal::Optional<ids::ScopeId> parent, JaktInternal::Optional<ids::ScopeId> alias_scope, JaktInternal::DynamicArray<ids::ScopeId> children, bool can_throw, JaktInternal::Optional<DeprecatedString> import_path_if_extern, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedNamespace>> alias_path, JaktInternal::DynamicArray<parser::IncludeAction> after_extern_include, JaktInternal::DynamicArray<parser::IncludeAction> before_extern_include, DeprecatedString debug_name, JaktInternal::DynamicArray<ids::ScopeId> resolution_mixins, bool is_block_scope, JaktInternal::Optional<JaktInternal::DynamicArray<types::ResolvedForallChunk>> resolved_forall_chunks, JaktInternal::Dictionary<DeprecatedString,types::SpecializedType> explicitly_specialized_types) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Scope (move(namespace_name), move(external_name), move(vars), move(comptime_bindings), move(structs), move(functions), move(enums), move(types), move(traits), move(imports), move(aliases), move(parent), move(alias_scope), move(children), move(can_throw), move(import_path_if_extern), move(alias_path), move(after_extern_include), move(before_extern_include), move(debug_name), move(resolution_mixins), move(is_block_scope), move(resolved_forall_chunks), move(explicitly_specialized_types)))); return o; }
JaktInternal::Optional<parser::ExternalName> types::Scope::namespace_name_for_codegen() const {
{
if (((((*this).external_name)).has_value())){
return ((*this).external_name);
}
if (((((*this).namespace_name)).has_value())){
return  parser::ExternalName { typename parser::ExternalName::Plain((((*this).namespace_name).value())) } ;
}
return JaktInternal::OptionalNone();
}
}

ErrorOr<DeprecatedString> types::CheckedVarDecl::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedVarDecl("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_mutable: {}, ", is_mutable));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("span: {}, ", span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_id: {}", type_id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedVarDecl::CheckedVarDecl(DeprecatedString a_name, bool a_is_mutable, utility::Span a_span, ids::TypeId a_type_id) :name(move(a_name)), is_mutable(move(a_is_mutable)), span(move(a_span)), type_id(move(a_type_id)){}

ErrorOr<DeprecatedString> types::CheckedEnum::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedEnum("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name_span: {}, ", name_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generic_parameters: {}, ", generic_parameters));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("variants: {}, ", variants));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("fields: {}, ", fields));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("scope_id: {}, ", scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("definition_linkage: {}, ", definition_linkage));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trait_implementations: {}, ", trait_implementations));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("record_type: {}, ", record_type));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("underlying_type_id: {}, ", underlying_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_id: {}, ", type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_boxed: {}", is_boxed));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedEnum::CheckedEnum(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, JaktInternal::DynamicArray<types::CheckedEnumVariant> a_variants, JaktInternal::DynamicArray<types::CheckedField> a_fields, ids::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> a_trait_implementations, parser::RecordType a_record_type, ids::TypeId a_underlying_type_id, ids::TypeId a_type_id, bool a_is_boxed) :name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)), variants(move(a_variants)), fields(move(a_fields)), scope_id(move(a_scope_id)), definition_linkage(move(a_definition_linkage)), trait_implementations(move(a_trait_implementations)), record_type(move(a_record_type)), underlying_type_id(move(a_underlying_type_id)), type_id(move(a_type_id)), is_boxed(move(a_is_boxed)){}

ErrorOr<DeprecatedString> types::CheckedStruct::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedStruct("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name_span: {}, ", name_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generic_parameters: {}, ", generic_parameters));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generic_parameter_defaults: {}, ", generic_parameter_defaults));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("fields: {}, ", fields));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("scope_id: {}, ", scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("definition_linkage: {}, ", definition_linkage));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trait_implementations: {}, ", trait_implementations));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("record_type: {}, ", record_type));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_id: {}, ", type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("super_struct_id: {}, ", super_struct_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("external_name: {}, ", external_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("implements_type: {}", implements_type));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedStruct::CheckedStruct(DeprecatedString a_name, utility::Span a_name_span, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Optional<ids::TypeId>>> a_generic_parameter_defaults, JaktInternal::DynamicArray<types::CheckedField> a_fields, ids::ScopeId a_scope_id, parser::DefinitionLinkage a_definition_linkage, JaktInternal::Dictionary<DeprecatedString,JaktInternal::DynamicArray<JaktInternal::Tuple<ids::TraitId,JaktInternal::DynamicArray<ids::TypeId>>>> a_trait_implementations, parser::RecordType a_record_type, ids::TypeId a_type_id, JaktInternal::Optional<ids::StructId> a_super_struct_id, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<ids::TypeId> a_implements_type) :name(move(a_name)), name_span(move(a_name_span)), generic_parameters(move(a_generic_parameters)), generic_parameter_defaults(move(a_generic_parameter_defaults)), fields(move(a_fields)), scope_id(move(a_scope_id)), definition_linkage(move(a_definition_linkage)), trait_implementations(move(a_trait_implementations)), record_type(move(a_record_type)), type_id(move(a_type_id)), super_struct_id(move(a_super_struct_id)), external_name(move(a_external_name)), implements_type(move(a_implements_type)){}

parser::ExternalName types::CheckedStruct::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return  parser::ExternalName { typename parser::ExternalName::Plain(((*this).name)) } ; });
}
}

ErrorOr<DeprecatedString> types::CheckedField::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedField("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("variable_id: {}, ", variable_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("default_value: {}, ", default_value));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("default_value_expression: {}", default_value_expression));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedField::CheckedField(ids::VarId a_variable_id, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> a_default_value, JaktInternal::Optional<NonnullRefPtr<typename parser::ParsedExpression>> a_default_value_expression) :variable_id(move(a_variable_id)), default_value(move(a_default_value)), default_value_expression(move(a_default_value_expression)){}

ErrorOr<DeprecatedString> types::CheckedParameter::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedParameter("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("requires_label: {}, ", requires_label));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("variable: {}, ", *variable));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("default_value: {}", default_value));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<types::CheckedParameter> types::CheckedParameter::map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) const {
{
return types::CheckedParameter(((*this).requires_label),TRY((((((*this).variable))->map_types(map)))),((*this).default_value));
}
}

types::CheckedParameter::CheckedParameter(bool a_requires_label, NonnullRefPtr<types::CheckedVariable> a_variable, JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>> a_default_value) :requires_label(move(a_requires_label)), variable(move(a_variable)), default_value(move(a_default_value)){}

ErrorOr<DeprecatedString> types::CheckedBinaryOperator::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedBinaryOperator("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("op: {}, ", op));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("trait_implementation: {}", trait_implementation));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedBinaryOperator::CheckedBinaryOperator(parser::BinaryOperator a_op, JaktInternal::Optional<types::OperatorTraitImplementation> a_trait_implementation) :op(move(a_op)), trait_implementation(move(a_trait_implementation)){}

ErrorOr<DeprecatedString> types::Value::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("Value("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("impl: {}, ", impl));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("span: {}", span));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<types::Value> types::Value::copy() const {
{
return types::Value(TRY((((((*this).impl))->copy()))),((*this).span));
}
}

ErrorOr<DeprecatedString> types::Value::type_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *((*this).impl);
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("void"sv)));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("bool"sv)));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u8"sv)));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u16"sv)));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u32"sv)));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("u64"sv)));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i18"sv)));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i16"sv)));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i32"sv)));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("i64"sv)));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("f32"sv)));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("f64"sv)));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("usize"sv)));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("String"sv)));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("StringView"sv)));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("c_char"sv)));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("c_int"sv)));
};/*case end*/
case 17: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("struct <T>"sv)));
};/*case end*/
case 18: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("class <T>"sv)));
};/*case end*/
case 19: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("enum <T>"sv)));
};/*case end*/
case 20: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Array"sv)));
};/*case end*/
case 21: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Dictionary"sv)));
};/*case end*/
case 22: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Set"sv)));
};/*case end*/
case 23: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("raw <T>"sv)));
};/*case end*/
case 24: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Some"sv)));
};/*case end*/
case 25: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("None"sv)));
};/*case end*/
case 26: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Tuple"sv)));
};/*case end*/
case 27: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Function"sv)));
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

types::Value::Value(NonnullRefPtr<typename types::ValueImpl> a_impl, utility::Span a_span) :impl(move(a_impl)), span(move(a_span)){}

ErrorOr<types::Value> types::Value::cast(types::Value const expected,utility::Span const span) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((*this).impl);
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U8>();
u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 3: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U16>((infallible_integer_cast<u16>((value)))))),span));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U32>((infallible_integer_cast<u32>((value)))))),span));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U64>((infallible_integer_cast<u64>((value)))))),span));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::USize>((infallible_integer_cast<size_t>((value)))))),span));
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
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U16>();
u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 4: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U32>((infallible_integer_cast<u32>((value)))))),span));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U64>((infallible_integer_cast<u64>((value)))))),span));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::USize>((infallible_integer_cast<size_t>((value)))))),span));
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
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U32>();
u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 5: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U64>((infallible_integer_cast<u64>((value)))))),span));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::USize>((infallible_integer_cast<size_t>((value)))))),span));
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
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U64>();
u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 12: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::USize>((infallible_integer_cast<size_t>((value)))))),span));
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
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I8>();
i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 7: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I16>((infallible_integer_cast<i16>((value)))))),span));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I32>((infallible_integer_cast<i32>((value)))))),span));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I64>((infallible_integer_cast<i64>((value)))))),span));
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
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I16>();
i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 8: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I32>((infallible_integer_cast<i32>((value)))))),span));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I64>((infallible_integer_cast<i64>((value)))))),span));
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
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I32>();
i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 9: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I64>((infallible_integer_cast<i64>((value)))))),span));
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
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I64>();
i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 12: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::USize>((infallible_integer_cast<size_t>((value)))))),span));
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
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::USize>();
size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 5: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U64>((infallible_integer_cast<u64>((value)))))),span));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::CInt>((infallible_integer_cast<int>((value)))))),span));
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
case 24: {
return JaktInternal::ExplicitValue(*this);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::Value, ErrorOr<types::Value>>{
auto&& __jakt_match_variant = *((expected).impl);
switch(__jakt_match_variant.index()) {
case 24: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::OptionalSome>(*this))),span));
};/*case end*/
case 25: {
return JaktInternal::ExplicitValue(types::Value(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::OptionalSome>(*this))),span));
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

ErrorOr<DeprecatedString> types::CheckedFunction::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedFunction("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name_span: {}, ", name_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("visibility: {}, ", visibility));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("return_type_id: {}, ", return_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("return_type_span: {}, ", return_type_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("params: {}, ", params));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generics: {}, ", *generics));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("block: {}, ", block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("can_throw: {}, ", can_throw));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type: {}, ", type));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("linkage: {}, ", linkage));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("function_scope_id: {}, ", function_scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("struct_id: {}, ", struct_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_instantiated: {}, ", is_instantiated));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("parsed_function: {}, ", parsed_function));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_comptime: {}, ", is_comptime));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_virtual: {}, ", is_virtual));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_override: {}, ", is_override));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_unsafe: {}, ", is_unsafe));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("specialization_index: {}, ", specialization_index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("owner_scope: {}, ", owner_scope));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_fully_checked: {}, ", is_fully_checked));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("external_name: {}, ", external_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("deprecated_message: {}, ", deprecated_message));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("stores_arguments: {}, ", stores_arguments));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("force_inline: {}", force_inline));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<void> types::CheckedFunction::map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) {
{
(((*this).return_type_id) = TRY((map(((*this).return_type_id)))));
JaktInternal::DynamicArray<types::CheckedParameter> changed_params = (TRY((DynamicArray<types::CheckedParameter>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedParameter> _magic = ((((*this).params)).iterator());
for (;;){
JaktInternal::Optional<types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedParameter param = (_magic_value.value());
{
TRY((((changed_params).push(TRY((((param).map_types(map))))))));
}

}
}

(((*this).params) = changed_params);
}
return {};
}

ErrorOr<bool> types::CheckedFunction::is_static() const {
{
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
(((((*this).params)).size()),static_cast<size_t>(1ULL))){
return true;
}
return [](DeprecatedString const& self, DeprecatedString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(((((((((*this).params))[static_cast<i64>(0LL)])).variable))->name),TRY(DeprecatedString::from_utf8("this"sv)));
}
}

ErrorOr<bool> types::CheckedFunction::is_mutating() const {
{
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
(((((*this).params)).size()),static_cast<size_t>(1ULL))){
return false;
}
NonnullRefPtr<types::CheckedVariable> const first_param_variable = ((((((*this).params))[static_cast<i64>(0LL)])).variable);
return (((((first_param_variable)->name)) == (TRY(DeprecatedString::from_utf8("this"sv)))) && ((first_param_variable)->is_mutable));
}
}

types::CheckedFunction::CheckedFunction(DeprecatedString a_name, utility::Span a_name_span, types::CheckedVisibility a_visibility, ids::TypeId a_return_type_id, JaktInternal::Optional<utility::Span> a_return_type_span, JaktInternal::DynamicArray<types::CheckedParameter> a_params, NonnullRefPtr<types::FunctionGenerics> a_generics, types::CheckedBlock a_block, bool a_can_throw, parser::FunctionType a_type, parser::FunctionLinkage a_linkage, ids::ScopeId a_function_scope_id, JaktInternal::Optional<ids::StructId> a_struct_id, bool a_is_instantiated, JaktInternal::Optional<parser::ParsedFunction> a_parsed_function, bool a_is_comptime, bool a_is_virtual, bool a_is_override, bool a_is_unsafe, JaktInternal::Optional<size_t> a_specialization_index, JaktInternal::Optional<ids::ScopeId> a_owner_scope, bool a_is_fully_checked, JaktInternal::Optional<parser::ExternalName> a_external_name, JaktInternal::Optional<DeprecatedString> a_deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> a_stores_arguments, parser::InlineState a_force_inline): name(move(a_name)), name_span(move(a_name_span)), visibility(move(a_visibility)), return_type_id(move(a_return_type_id)), return_type_span(move(a_return_type_span)), params(move(a_params)), generics(move(a_generics)), block(move(a_block)), can_throw(move(a_can_throw)), type(move(a_type)), linkage(move(a_linkage)), function_scope_id(move(a_function_scope_id)), struct_id(move(a_struct_id)), is_instantiated(move(a_is_instantiated)), parsed_function(move(a_parsed_function)), is_comptime(move(a_is_comptime)), is_virtual(move(a_is_virtual)), is_override(move(a_is_override)), is_unsafe(move(a_is_unsafe)), specialization_index(move(a_specialization_index)), owner_scope(move(a_owner_scope)), is_fully_checked(move(a_is_fully_checked)), external_name(move(a_external_name)), deprecated_message(move(a_deprecated_message)), stores_arguments(move(a_stores_arguments)), force_inline(move(a_force_inline)){}
ErrorOr<NonnullRefPtr<CheckedFunction>> types::CheckedFunction::__jakt_create(DeprecatedString name, utility::Span name_span, types::CheckedVisibility visibility, ids::TypeId return_type_id, JaktInternal::Optional<utility::Span> return_type_span, JaktInternal::DynamicArray<types::CheckedParameter> params, NonnullRefPtr<types::FunctionGenerics> generics, types::CheckedBlock block, bool can_throw, parser::FunctionType type, parser::FunctionLinkage linkage, ids::ScopeId function_scope_id, JaktInternal::Optional<ids::StructId> struct_id, bool is_instantiated, JaktInternal::Optional<parser::ParsedFunction> parsed_function, bool is_comptime, bool is_virtual, bool is_override, bool is_unsafe, JaktInternal::Optional<size_t> specialization_index, JaktInternal::Optional<ids::ScopeId> owner_scope, bool is_fully_checked, JaktInternal::Optional<parser::ExternalName> external_name, JaktInternal::Optional<DeprecatedString> deprecated_message, JaktInternal::Optional<JaktInternal::DynamicArray<JaktInternal::Tuple<size_t,parser::ArgumentStoreLevel>>> stores_arguments, parser::InlineState force_inline) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) CheckedFunction (move(name), move(name_span), move(visibility), move(return_type_id), move(return_type_span), move(params), move(generics), move(block), move(can_throw), move(type), move(linkage), move(function_scope_id), move(struct_id), move(is_instantiated), move(parsed_function), move(is_comptime), move(is_virtual), move(is_override), move(is_unsafe), move(specialization_index), move(owner_scope), move(is_fully_checked), move(external_name), move(deprecated_message), move(stores_arguments), move(force_inline)))); return o; }
ErrorOr<parser::ParsedFunction> types::CheckedFunction::to_parsed_function() const {
{
if ((!(((((*this).parsed_function)).has_value())))){
utility::panic(TRY(DeprecatedString::from_utf8("to_parsed_function() called on a synthetic function"sv)));
}
return (((*this).parsed_function).value());
}
}

bool types::CheckedFunction::is_specialized_for_types(JaktInternal::DynamicArray<ids::TypeId> const types) const {
{
return ((((*this).generics))->is_specialized_for_types(types));
}
}

void types::CheckedFunction::set_param_default_value(size_t const param_index,NonnullRefPtr<typename types::CheckedExpression> const default_value) {
{
(((((((*this).params))[param_index])).default_value) = default_value);
(((((((((*this).generics))->base_params))[param_index])).default_value) = default_value);
}
}

ErrorOr<bool> types::CheckedFunction::signature_matches(NonnullRefPtr<types::CheckedFunction> const other,bool const ignore_this) const {
{
if ((([](DeprecatedString const& self, DeprecatedString rhs) -> bool {
{
return (!(((self) == (rhs))));
}
}
(((*this).name),((other)->name)) || ((((*this).can_throw)) != (((other)->can_throw)))) || ((((*this).is_comptime)) != (((other)->is_comptime))))){
return false;
}
if (((((((*this).params)).size())) != (((((other)->params)).size())))){
return false;
}
if (((((((((*this).generics))->params)).size())) != (((((((other)->generics))->params)).size())))){
return false;
}
JaktInternal::Set<ids::TypeId> lhs_generic_type_ids = (TRY((Set<ids::TypeId>::create_with_values({}))));
JaktInternal::Set<ids::TypeId> rhs_generic_type_ids = (TRY((Set<ids::TypeId>::create_with_values({}))));
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
TRY((((lhs_generic_type_ids).add(type_id))));
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
TRY((((rhs_generic_type_ids).add(type_id))));
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

ErrorOr<NonnullRefPtr<types::CheckedFunction>> types::CheckedFunction::copy() const {
{
return TRY((types::CheckedFunction::__jakt_create(((*this).name),((*this).name_span),((*this).visibility),((*this).return_type_id),((*this).return_type_span),((*this).params),((*this).generics),((*this).block),((*this).can_throw),((*this).type),((*this).linkage),((*this).function_scope_id),((*this).struct_id),((*this).is_instantiated),((*this).parsed_function),((*this).is_comptime),((*this).is_virtual),((*this).is_override),((*this).is_unsafe),((*this).specialization_index),((*this).owner_scope),((*this).is_fully_checked),((*this).external_name),((*this).deprecated_message),((*this).stores_arguments), parser::InlineState { typename parser::InlineState::Default() } )));
}
}

parser::ExternalName types::CheckedFunction::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return  parser::ExternalName { typename parser::ExternalName::Plain(((*this).name)) } ; });
}
}

ErrorOr<void> types::CheckedFunction::add_param(types::CheckedParameter const checked_param) {
{
TRY((((((*this).params)).push(checked_param))));
TRY((((((((*this).generics))->base_params)).push(checked_param))));
}
return {};
}

ErrorOr<void> types::CheckedFunction::set_params(JaktInternal::DynamicArray<types::CheckedParameter> const checked_params) {
{
(((*this).params) = checked_params);
(((((*this).generics))->base_params) = checked_params);
}
return {};
}

ErrorOr<DeprecatedString> types::FunctionGenerics::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("FunctionGenerics("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("base_scope_id: {}, ", base_scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("base_params: {}, ", base_params));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("params: {}, ", params));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("specializations: {}", specializations));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::FunctionGenerics::FunctionGenerics(ids::ScopeId a_base_scope_id, JaktInternal::DynamicArray<types::CheckedParameter> a_base_params, JaktInternal::DynamicArray<types::FunctionGenericParameter> a_params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> a_specializations): base_scope_id(move(a_base_scope_id)), base_params(move(a_base_params)), params(move(a_params)), specializations(move(a_specializations)){}
ErrorOr<NonnullRefPtr<FunctionGenerics>> types::FunctionGenerics::__jakt_create(ids::ScopeId base_scope_id, JaktInternal::DynamicArray<types::CheckedParameter> base_params, JaktInternal::DynamicArray<types::FunctionGenericParameter> params, JaktInternal::DynamicArray<JaktInternal::DynamicArray<ids::TypeId>> specializations) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) FunctionGenerics (move(base_scope_id), move(base_params), move(params), move(specializations)))); return o; }
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

ErrorOr<DeprecatedString> types::CheckedGenericParameter::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedGenericParameter("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_id: {}, ", type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("constraints: {}, ", constraints));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("span: {}", span));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<types::CheckedGenericParameter> types::CheckedGenericParameter::make(ids::TypeId const type_id,utility::Span const span) {
{
return types::CheckedGenericParameter(type_id,(TRY((DynamicArray<ids::TraitId>::create_with({})))),span);
}
}

types::CheckedGenericParameter::CheckedGenericParameter(ids::TypeId a_type_id, JaktInternal::DynamicArray<ids::TraitId> a_constraints, utility::Span a_span) :type_id(move(a_type_id)), constraints(move(a_constraints)), span(move(a_span)){}

ErrorOr<DeprecatedString> types::CheckedEnumVariantBinding::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedEnumVariantBinding("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: {}, ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("binding: \"{}\", ", binding));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_id: {}, ", type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("span: {}", span));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedEnumVariantBinding::CheckedEnumVariantBinding(JaktInternal::Optional<DeprecatedString> a_name, DeprecatedString a_binding, ids::TypeId a_type_id, utility::Span a_span) :name(move(a_name)), binding(move(a_binding)), type_id(move(a_type_id)), span(move(a_span)){}

ErrorOr<DeprecatedString> types::CheckedTrait::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedTrait("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name_span: {}, ", name_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("requirements: {}, ", requirements));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("generic_parameters: {}, ", generic_parameters));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("scope_id: {}", scope_id));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::CheckedTrait::CheckedTrait(DeprecatedString a_name, utility::Span a_name_span, types::CheckedTraitRequirements a_requirements, JaktInternal::DynamicArray<types::CheckedGenericParameter> a_generic_parameters, ids::ScopeId a_scope_id): name(move(a_name)), name_span(move(a_name_span)), requirements(move(a_requirements)), generic_parameters(move(a_generic_parameters)), scope_id(move(a_scope_id)){}
ErrorOr<NonnullRefPtr<CheckedTrait>> types::CheckedTrait::__jakt_create(DeprecatedString name, utility::Span name_span, types::CheckedTraitRequirements requirements, JaktInternal::DynamicArray<types::CheckedGenericParameter> generic_parameters, ids::ScopeId scope_id) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) CheckedTrait (move(name), move(name_span), move(requirements), move(generic_parameters), move(scope_id)))); return o; }
ErrorOr<DeprecatedString> types::CheckedStringLiteral::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedStringLiteral("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("value: {}, ", value));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_id: {}, ", type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("may_throw: {}", may_throw));
}
TRY(builder.append(")"sv));return builder.to_string(); }
DeprecatedString types::CheckedStringLiteral::to_string() const {
{
return ((((*this).value)).to_string());
}
}

types::CheckedStringLiteral::CheckedStringLiteral(types::StringLiteral a_value, ids::TypeId a_type_id, bool a_may_throw) :value(move(a_value)), type_id(move(a_type_id)), may_throw(move(a_may_throw)){}

ErrorOr<DeprecatedString> types::CheckedVariable::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("CheckedVariable("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_id: {}, ", type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_mutable: {}, ", is_mutable));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("definition_span: {}, ", definition_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("type_span: {}, ", type_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("visibility: {}, ", visibility));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("owner_scope: {}, ", owner_scope));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("external_name: {}", external_name));
}
TRY(builder.append(")"sv));return builder.to_string(); }
ErrorOr<NonnullRefPtr<types::CheckedVariable>> types::CheckedVariable::map_types(Function<ErrorOr<ids::TypeId>(ids::TypeId)> const& map) const {
{
return TRY((types::CheckedVariable::__jakt_create(((*this).name),TRY((map(((*this).type_id)))),((*this).is_mutable),((*this).definition_span),((*this).type_span),((*this).visibility),((*this).owner_scope),((*this).external_name))));
}
}

parser::ExternalName types::CheckedVariable::name_for_codegen() const {
{
return ((*this).external_name).value_or_lazy_evaluated([&] { return  parser::ExternalName { typename parser::ExternalName::Plain(((*this).name)) } ; });
}
}

types::CheckedVariable::CheckedVariable(DeprecatedString a_name, ids::TypeId a_type_id, bool a_is_mutable, utility::Span a_definition_span, JaktInternal::Optional<utility::Span> a_type_span, types::CheckedVisibility a_visibility, JaktInternal::Optional<ids::ScopeId> a_owner_scope, JaktInternal::Optional<parser::ExternalName> a_external_name): name(move(a_name)), type_id(move(a_type_id)), is_mutable(move(a_is_mutable)), definition_span(move(a_definition_span)), type_span(move(a_type_span)), visibility(move(a_visibility)), owner_scope(move(a_owner_scope)), external_name(move(a_external_name)){}
ErrorOr<NonnullRefPtr<CheckedVariable>> types::CheckedVariable::__jakt_create(DeprecatedString name, ids::TypeId type_id, bool is_mutable, utility::Span definition_span, JaktInternal::Optional<utility::Span> type_span, types::CheckedVisibility visibility, JaktInternal::Optional<ids::ScopeId> owner_scope, JaktInternal::Optional<parser::ExternalName> external_name) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) CheckedVariable (move(name), move(type_id), move(is_mutable), move(definition_span), move(type_span), move(visibility), move(owner_scope), move(external_name)))); return o; }
ErrorOr<DeprecatedString> types::ClassInstanceRebind::debug_description() const { auto builder = DeprecatedStringBuilder::create();TRY(builder.append("ClassInstanceRebind("sv));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name: \"{}\", ", name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("name_span: {}, ", name_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_mutable: {}, ", is_mutable));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.appendff("is_reference: {}", is_reference));
}
TRY(builder.append(")"sv));return builder.to_string(); }
types::ClassInstanceRebind::ClassInstanceRebind(DeprecatedString a_name, utility::Span a_name_span, bool a_is_mutable, bool a_is_reference) :name(move(a_name)), name_span(move(a_name_span)), is_mutable(move(a_is_mutable)), is_reference(move(a_is_reference)){}

ErrorOr<DeprecatedString> types::CheckedUnaryOperator::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* PreIncrement */: {
return DeprecatedString("CheckedUnaryOperator::PreIncrement"sv);
break;}
case 1 /* PostIncrement */: {
return DeprecatedString("CheckedUnaryOperator::PostIncrement"sv);
break;}
case 2 /* PreDecrement */: {
return DeprecatedString("CheckedUnaryOperator::PreDecrement"sv);
break;}
case 3 /* PostDecrement */: {
return DeprecatedString("CheckedUnaryOperator::PostDecrement"sv);
break;}
case 4 /* Negate */: {
return DeprecatedString("CheckedUnaryOperator::Negate"sv);
break;}
case 5 /* Dereference */: {
return DeprecatedString("CheckedUnaryOperator::Dereference"sv);
break;}
case 6 /* RawAddress */: {
return DeprecatedString("CheckedUnaryOperator::RawAddress"sv);
break;}
case 7 /* Reference */: {
return DeprecatedString("CheckedUnaryOperator::Reference"sv);
break;}
case 8 /* MutableReference */: {
return DeprecatedString("CheckedUnaryOperator::MutableReference"sv);
break;}
case 9 /* LogicalNot */: {
return DeprecatedString("CheckedUnaryOperator::LogicalNot"sv);
break;}
case 10 /* BitwiseNot */: {
return DeprecatedString("CheckedUnaryOperator::BitwiseNot"sv);
break;}
case 11 /* TypeCast */: {
TRY(builder.append("CheckedUnaryOperator::TypeCast"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedUnaryOperator::TypeCast>();
TRY(builder.appendff("({})", that.value));
break;}
case 12 /* Is */: {
TRY(builder.append("CheckedUnaryOperator::Is"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedUnaryOperator::Is>();
TRY(builder.appendff("({})", that.value));
break;}
case 13 /* IsEnumVariant */: {
TRY(builder.append("CheckedUnaryOperator::IsEnumVariant"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedUnaryOperator::IsEnumVariant>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("enum_variant: {}, ", that.enum_variant));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("bindings: {}, ", that.bindings));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 14 /* IsSome */: {
return DeprecatedString("CheckedUnaryOperator::IsSome"sv);
break;}
case 15 /* IsNone */: {
return DeprecatedString("CheckedUnaryOperator::IsNone"sv);
break;}
case 16 /* Sizeof */: {
TRY(builder.append("CheckedUnaryOperator::Sizeof"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedUnaryOperator::Sizeof>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::NumericOrStringValue::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* StringValue */: {
TRY(builder.append("NumericOrStringValue::StringValue"sv));
[[maybe_unused]] auto const& that = this->template get<NumericOrStringValue::StringValue>();
TRY(builder.appendff("(\"{}\")", that.value));
break;}
case 1 /* SignedNumericValue */: {
TRY(builder.append("NumericOrStringValue::SignedNumericValue"sv));
[[maybe_unused]] auto const& that = this->template get<NumericOrStringValue::SignedNumericValue>();
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* UnsignedNumericValue */: {
TRY(builder.append("NumericOrStringValue::UnsignedNumericValue"sv));
[[maybe_unused]] auto const& that = this->template get<NumericOrStringValue::UnsignedNumericValue>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::FunctionGenericParameterKind::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* InferenceGuide */: {
return DeprecatedString("FunctionGenericParameterKind::InferenceGuide"sv);
break;}
case 1 /* Parameter */: {
return DeprecatedString("FunctionGenericParameterKind::Parameter"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::Type::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Void */: {
return DeprecatedString("Type::Void"sv);
break;}
case 1 /* Bool */: {
return DeprecatedString("Type::Bool"sv);
break;}
case 2 /* U8 */: {
return DeprecatedString("Type::U8"sv);
break;}
case 3 /* U16 */: {
return DeprecatedString("Type::U16"sv);
break;}
case 4 /* U32 */: {
return DeprecatedString("Type::U32"sv);
break;}
case 5 /* U64 */: {
return DeprecatedString("Type::U64"sv);
break;}
case 6 /* I8 */: {
return DeprecatedString("Type::I8"sv);
break;}
case 7 /* I16 */: {
return DeprecatedString("Type::I16"sv);
break;}
case 8 /* I32 */: {
return DeprecatedString("Type::I32"sv);
break;}
case 9 /* I64 */: {
return DeprecatedString("Type::I64"sv);
break;}
case 10 /* F32 */: {
return DeprecatedString("Type::F32"sv);
break;}
case 11 /* F64 */: {
return DeprecatedString("Type::F64"sv);
break;}
case 12 /* Usize */: {
return DeprecatedString("Type::Usize"sv);
break;}
case 13 /* JaktString */: {
return DeprecatedString("Type::JaktString"sv);
break;}
case 14 /* CChar */: {
return DeprecatedString("Type::CChar"sv);
break;}
case 15 /* CInt */: {
return DeprecatedString("Type::CInt"sv);
break;}
case 16 /* Unknown */: {
return DeprecatedString("Type::Unknown"sv);
break;}
case 17 /* Never */: {
return DeprecatedString("Type::Never"sv);
break;}
case 18 /* TypeVariable */: {
TRY(builder.append("Type::TypeVariable"sv));
[[maybe_unused]] auto const& that = this->template get<Type::TypeVariable>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("qualifiers: {}, ", that.qualifiers));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("trait_implementations: {}, ", that.trait_implementations));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_value: {}", that.is_value));
}
TRY(builder.append(")"sv));
break;}
case 19 /* Dependent */: {
TRY(builder.append("Type::Dependent"sv));
[[maybe_unused]] auto const& that = this->template get<Type::Dependent>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("qualifiers: {}, ", that.qualifiers));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("namespace_type: {}, ", that.namespace_type));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\"", that.name));
}
TRY(builder.append(")"sv));
break;}
case 20 /* GenericInstance */: {
TRY(builder.append("Type::GenericInstance"sv));
[[maybe_unused]] auto const& that = this->template get<Type::GenericInstance>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("qualifiers: {}, ", that.qualifiers));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("id: {}, ", that.id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("args: {}", that.args));
}
TRY(builder.append(")"sv));
break;}
case 21 /* GenericEnumInstance */: {
TRY(builder.append("Type::GenericEnumInstance"sv));
[[maybe_unused]] auto const& that = this->template get<Type::GenericEnumInstance>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("qualifiers: {}, ", that.qualifiers));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("id: {}, ", that.id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("args: {}", that.args));
}
TRY(builder.append(")"sv));
break;}
case 22 /* GenericTraitInstance */: {
TRY(builder.append("Type::GenericTraitInstance"sv));
[[maybe_unused]] auto const& that = this->template get<Type::GenericTraitInstance>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("qualifiers: {}, ", that.qualifiers));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("id: {}, ", that.id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("args: {}", that.args));
}
TRY(builder.append(")"sv));
break;}
case 23 /* GenericResolvedType */: {
TRY(builder.append("Type::GenericResolvedType"sv));
[[maybe_unused]] auto const& that = this->template get<Type::GenericResolvedType>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("qualifiers: {}, ", that.qualifiers));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("id: {}, ", that.id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("args: {}", that.args));
}
TRY(builder.append(")"sv));
break;}
case 24 /* Struct */: {
TRY(builder.append("Type::Struct"sv));
[[maybe_unused]] auto const& that = this->template get<Type::Struct>();
TRY(builder.appendff("({})", that.value));
break;}
case 25 /* Enum */: {
TRY(builder.append("Type::Enum"sv));
[[maybe_unused]] auto const& that = this->template get<Type::Enum>();
TRY(builder.appendff("({})", that.value));
break;}
case 26 /* RawPtr */: {
TRY(builder.append("Type::RawPtr"sv));
[[maybe_unused]] auto const& that = this->template get<Type::RawPtr>();
TRY(builder.appendff("({})", that.value));
break;}
case 27 /* Trait */: {
TRY(builder.append("Type::Trait"sv));
[[maybe_unused]] auto const& that = this->template get<Type::Trait>();
TRY(builder.appendff("({})", that.value));
break;}
case 28 /* Reference */: {
TRY(builder.append("Type::Reference"sv));
[[maybe_unused]] auto const& that = this->template get<Type::Reference>();
TRY(builder.appendff("({})", that.value));
break;}
case 29 /* MutableReference */: {
TRY(builder.append("Type::MutableReference"sv));
[[maybe_unused]] auto const& that = this->template get<Type::MutableReference>();
TRY(builder.appendff("({})", that.value));
break;}
case 30 /* Function */: {
TRY(builder.append("Type::Function"sv));
[[maybe_unused]] auto const& that = this->template get<Type::Function>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("qualifiers: {}, ", that.qualifiers));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("params: {}, ", that.params));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("can_throw: {}, ", that.can_throw));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("return_type_id: {}, ", that.return_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("pseudo_function_id: {}", that.pseudo_function_id));
}
TRY(builder.append(")"sv));
break;}
case 31 /* Self */: {
return DeprecatedString("Type::Self"sv);
break;}
case 32 /* Const */: {
TRY(builder.append("Type::Const"sv));
[[maybe_unused]] auto const& that = this->template get<Type::Const>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
u64 types::Type::max() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, u64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 14: {
return JaktInternal::ExplicitValue(static_cast<u64>(127ULL));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(static_cast<u64>(2147483647ULL));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(static_cast<u64>(127ULL));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(static_cast<u64>(32767ULL));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(static_cast<u64>(2147483647ULL));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(static_cast<u64>(9223372036854775807ULL));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(static_cast<u64>(255ULL));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(static_cast<u64>(65535ULL));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(static_cast<u64>(4294967295ULL));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(static_cast<u64>(18446744073709551615ULL));
};/*case end*/
case 12: {
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

bool types::Type::equals(NonnullRefPtr<typename types::Type> const rhs) const {
{
return (((((rhs)->qualifiers())).equals(((*this).qualifiers()))) && ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(((rhs)->index() == 0 /* Void */));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(((rhs)->index() == 1 /* Bool */));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(((rhs)->index() == 2 /* U8 */));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(((rhs)->index() == 3 /* U16 */));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(((rhs)->index() == 4 /* U32 */));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(((rhs)->index() == 5 /* U64 */));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(((rhs)->index() == 6 /* I8 */));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(((rhs)->index() == 7 /* I16 */));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(((rhs)->index() == 8 /* I32 */));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(((rhs)->index() == 9 /* I64 */));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(((rhs)->index() == 10 /* F32 */));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(((rhs)->index() == 11 /* F64 */));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(((rhs)->index() == 12 /* Usize */));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(((rhs)->index() == 13 /* JaktString */));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(((rhs)->index() == 14 /* CChar */));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(((rhs)->index() == 15 /* CInt */));
};/*case end*/
case 31: {
return JaktInternal::ExplicitValue(((rhs)->index() == 31 /* Self */));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(((rhs)->index() == 16 /* Unknown */));
};/*case end*/
case 17: {
return JaktInternal::ExplicitValue(((rhs)->index() == 17 /* Never */));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::TypeVariable>();DeprecatedString const& lhs_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_142; {
if (((rhs)->index() == 18 /* TypeVariable */)){
DeprecatedString const rhs_name = ((rhs)->get<types::Type::TypeVariable>()).name;
return ((lhs_name) == (rhs_name));
}
__jakt_var_142 = false; goto __jakt_label_136;

}
__jakt_label_136:; __jakt_var_142.release_value(); }));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Dependent>();ids::TypeId const& namespace_type = __jakt_match_value.namespace_type;
DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({ Optional<bool> __jakt_var_143; {
if (((rhs)->index() == 19 /* Dependent */)){
ids::TypeId const rhs_namespace_type = ((rhs)->get<types::Type::Dependent>()).namespace_type;
DeprecatedString const rhs_name = ((rhs)->get<types::Type::Dependent>()).name;
return (((namespace_type).equals(rhs_namespace_type)) && ((name) == (rhs_name)));
}
__jakt_var_143 = false; goto __jakt_label_137;

}
__jakt_label_137:; __jakt_var_143.release_value(); }));
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Const>();
types::Value const& lhs_value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *rhs;
switch(__jakt_match_variant.index()) {
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Const>();
types::Value const& rhs_value = __jakt_match_value.value;
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
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();ids::StructId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs)->index() == 20 /* GenericInstance */)){
ids::StructId const rhs_id = ((rhs)->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<ids::TypeId> const rhs_args = ((rhs)->get<types::Type::GenericInstance>()).args;
if ((((lhs_id).equals(rhs_id)) && ((((lhs_args).size())) == (((rhs_args).size()))))){
size_t idx = static_cast<size_t>(0ULL);
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
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();ids::StructId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs)->index() == 20 /* GenericInstance */)){
ids::StructId const rhs_id = ((rhs)->get<types::Type::GenericInstance>()).id;
JaktInternal::DynamicArray<ids::TypeId> const rhs_args = ((rhs)->get<types::Type::GenericInstance>()).args;
if ((((lhs_id).equals(rhs_id)) && ((((lhs_args).size())) == (((rhs_args).size()))))){
size_t idx = static_cast<size_t>(0ULL);
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
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();ids::TraitId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs)->index() == 22 /* GenericTraitInstance */)){
ids::TraitId const rhs_id = ((rhs)->get<types::Type::GenericTraitInstance>()).id;
JaktInternal::DynamicArray<ids::TypeId> const rhs_args = ((rhs)->get<types::Type::GenericTraitInstance>()).args;
if ((((lhs_id).equals(rhs_id)) && ((((lhs_args).size())) == (((rhs_args).size()))))){
size_t idx = static_cast<size_t>(0ULL);
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
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();ids::EnumId const& lhs_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& lhs_args = __jakt_match_value.args;
{
if (((rhs)->index() == 21 /* GenericEnumInstance */)){
ids::EnumId const rhs_id = ((rhs)->get<types::Type::GenericEnumInstance>()).id;
JaktInternal::DynamicArray<ids::TypeId> const rhs_args = ((rhs)->get<types::Type::GenericEnumInstance>()).args;
if ((((lhs_id).equals(rhs_id)) && ((((lhs_args).size())) == (((rhs_args).size()))))){
size_t idx = static_cast<size_t>(0ULL);
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
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
ids::StructId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->index() == 24 /* Struct */)){
ids::StructId const rhs_id = ((rhs)->get<types::Type::Struct>()).value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
ids::EnumId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->index() == 25 /* Enum */)){
ids::EnumId const rhs_id = ((rhs)->get<types::Type::Enum>()).value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::RawPtr>();
ids::TypeId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->index() == 26 /* RawPtr */)){
ids::TypeId const rhs_id = ((rhs)->get<types::Type::RawPtr>()).value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Reference>();
ids::TypeId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->index() == 28 /* Reference */)){
ids::TypeId const rhs_id = ((rhs)->get<types::Type::Reference>()).value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::MutableReference>();
ids::TypeId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->index() == 29 /* MutableReference */)){
ids::TypeId const rhs_id = ((rhs)->get<types::Type::MutableReference>()).value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
ids::TraitId const& lhs_id = __jakt_match_value.value;
{
if (((rhs)->index() == 27 /* Trait */)){
ids::TraitId const rhs_id = ((rhs)->get<types::Type::Trait>()).value;
return ((lhs_id).equals(rhs_id));
}
return false;
}
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
{
if (((rhs)->index() == 30 /* Function */)){
JaktInternal::DynamicArray<ids::TypeId> const rhs_params = ((rhs)->get<types::Type::Function>()).params;
bool const rhs_can_throw = ((rhs)->get<types::Type::Function>()).can_throw;
ids::TypeId const rhs_return_type_id = ((rhs)->get<types::Type::Function>()).return_type_id;
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

ErrorOr<DeprecatedString> types::Type::constructor_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Void"sv)));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Bool"sv)));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("U8"sv)));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("U16"sv)));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("U32"sv)));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("U64"sv)));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("I8"sv)));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("I16"sv)));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("I32"sv)));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("I64"sv)));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("F32"sv)));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("F64"sv)));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Usize"sv)));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("JaktString"sv)));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("CChar"sv)));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("CInt"sv)));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Unknown"sv)));
};/*case end*/
case 17: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Never"sv)));
};/*case end*/
case 18: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("TypeVariable"sv)));
};/*case end*/
case 19: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Dependent"sv)));
};/*case end*/
case 20: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("GenericInstance"sv)));
};/*case end*/
case 21: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("GenericEnumInstance"sv)));
};/*case end*/
case 22: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("GenericTraitInstance"sv)));
};/*case end*/
case 23: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("GenericResolvedType"sv)));
};/*case end*/
case 24: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Struct"sv)));
};/*case end*/
case 25: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Enum"sv)));
};/*case end*/
case 26: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("RawPtr"sv)));
};/*case end*/
case 27: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Trait"sv)));
};/*case end*/
case 28: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Reference"sv)));
};/*case end*/
case 29: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("MutableReference"sv)));
};/*case end*/
case 30: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Function"sv)));
};/*case end*/
case 31: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Self"sv)));
};/*case end*/
case 32: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Const"sv)));
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

bool types::Type::is_concrete() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 18: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 31: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 19: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 16: {
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

i64 types::Type::get_bits() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue(static_cast<i64>(8LL));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(static_cast<i64>(8LL));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(static_cast<i64>(8LL));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(static_cast<i64>(16LL));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(static_cast<i64>(16LL));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(static_cast<i64>(64LL));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(static_cast<i64>(32LL));
};/*case end*/
case 11: {
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

i64 types::Type::specificity(NonnullRefPtr<types::CheckedProgram> const program,i64 const base_specificity) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<i64, i64>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 18: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 19: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 32: {
return JaktInternal::ExplicitValue(base_specificity);
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<i64> __jakt_var_144; {
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

__jakt_var_144 = specificity; goto __jakt_label_138;

}
__jakt_label_138:; __jakt_var_144.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<i64> __jakt_var_145; {
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

__jakt_var_145 = specificity; goto __jakt_label_139;

}
__jakt_label_139:; __jakt_var_145.release_value(); }));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericResolvedType>();JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(({ Optional<i64> __jakt_var_146; {
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

__jakt_var_146 = specificity; goto __jakt_label_140;

}
__jakt_label_140:; __jakt_var_146.release_value(); }));
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::Function>();JaktInternal::DynamicArray<ids::TypeId> const& params = __jakt_match_value.params;
return JaktInternal::ExplicitValue(({ Optional<i64> __jakt_var_147; {
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

__jakt_var_147 = specificity; goto __jakt_label_141;

}
__jakt_label_141:; __jakt_var_147.release_value(); }));
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

types::BuiltinType types::Type::as_builtin_type() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BuiltinType, types::BuiltinType>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::Void() } );
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::Bool() } );
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::U8() } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::U16() } );
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::U32() } );
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::U64() } );
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::I8() } );
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::I16() } );
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::I32() } );
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::I64() } );
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::F32() } );
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::F64() } );
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::Usize() } );
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::JaktString() } );
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::CChar() } );
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue( types::BuiltinType { typename types::BuiltinType::CInt() } );
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

bool types::Type::is_builtin() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 15: {
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
switch(__jakt_match_variant.index()) {
case 14: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(128LL))));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(2147483648LL))));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(128LL))));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(32768LL))));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue((-(static_cast<i64>(2147483648LL))));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(JaktInternal::checked_sub((-(static_cast<i64>(9223372036854775807LL))),static_cast<i64>(1LL)));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(static_cast<i64>(0LL));
};/*case end*/
case 12: {
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

ErrorOr<ids::TypeId> types::Type::flip_signedness() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<ids::TypeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 6: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } ));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } ));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } ));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } ));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } ));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } ));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } ));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } ));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Unknown() } ));
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
switch(__jakt_match_variant.index()) {
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
ids::StructId const& struct_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)->get_struct(struct_id))).record_type)).index() == 1 /* Class */));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();ids::StructId const& struct_id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((((((program)->get_struct(struct_id))).record_type)).index() == 1 /* Class */));
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
ids::EnumId const& enum_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((program)->get_enum(enum_id))).is_boxed));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();ids::EnumId const& enum_id = __jakt_match_value.id;
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

bool types::Type::is_signed() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 6: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 11: {
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

ErrorOr<DeprecatedString> types::ValueImpl::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Void */: {
return DeprecatedString("ValueImpl::Void"sv);
break;}
case 1 /* Bool */: {
TRY(builder.append("ValueImpl::Bool"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::Bool>();
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* U8 */: {
TRY(builder.append("ValueImpl::U8"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::U8>();
TRY(builder.appendff("({})", that.value));
break;}
case 3 /* U16 */: {
TRY(builder.append("ValueImpl::U16"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::U16>();
TRY(builder.appendff("({})", that.value));
break;}
case 4 /* U32 */: {
TRY(builder.append("ValueImpl::U32"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::U32>();
TRY(builder.appendff("({})", that.value));
break;}
case 5 /* U64 */: {
TRY(builder.append("ValueImpl::U64"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::U64>();
TRY(builder.appendff("({})", that.value));
break;}
case 6 /* I8 */: {
TRY(builder.append("ValueImpl::I8"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::I8>();
TRY(builder.appendff("({})", that.value));
break;}
case 7 /* I16 */: {
TRY(builder.append("ValueImpl::I16"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::I16>();
TRY(builder.appendff("({})", that.value));
break;}
case 8 /* I32 */: {
TRY(builder.append("ValueImpl::I32"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::I32>();
TRY(builder.appendff("({})", that.value));
break;}
case 9 /* I64 */: {
TRY(builder.append("ValueImpl::I64"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::I64>();
TRY(builder.appendff("({})", that.value));
break;}
case 10 /* F32 */: {
TRY(builder.append("ValueImpl::F32"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::F32>();
TRY(builder.appendff("({})", that.value));
break;}
case 11 /* F64 */: {
TRY(builder.append("ValueImpl::F64"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::F64>();
TRY(builder.appendff("({})", that.value));
break;}
case 12 /* USize */: {
TRY(builder.append("ValueImpl::USize"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::USize>();
TRY(builder.appendff("({})", that.value));
break;}
case 13 /* JaktString */: {
TRY(builder.append("ValueImpl::JaktString"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::JaktString>();
TRY(builder.appendff("(\"{}\")", that.value));
break;}
case 14 /* StringView */: {
TRY(builder.append("ValueImpl::StringView"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::StringView>();
TRY(builder.appendff("(\"{}\")", that.value));
break;}
case 15 /* CChar */: {
TRY(builder.append("ValueImpl::CChar"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::CChar>();
TRY(builder.appendff("({})", that.value));
break;}
case 16 /* CInt */: {
TRY(builder.append("ValueImpl::CInt"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::CInt>();
TRY(builder.appendff("({})", that.value));
break;}
case 17 /* Struct */: {
TRY(builder.append("ValueImpl::Struct"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::Struct>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("fields: {}, ", that.fields));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("struct_id: {}, ", that.struct_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("constructor: {}", that.constructor));
}
TRY(builder.append(")"sv));
break;}
case 18 /* Class */: {
TRY(builder.append("ValueImpl::Class"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::Class>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("fields: {}, ", that.fields));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("struct_id: {}, ", that.struct_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("constructor: {}", that.constructor));
}
TRY(builder.append(")"sv));
break;}
case 19 /* Enum */: {
TRY(builder.append("ValueImpl::Enum"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::Enum>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("fields: {}, ", that.fields));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("enum_id: {}, ", that.enum_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("constructor: {}", that.constructor));
}
TRY(builder.append(")"sv));
break;}
case 20 /* JaktArray */: {
TRY(builder.append("ValueImpl::JaktArray"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::JaktArray>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("values: {}, ", that.values));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 21 /* JaktDictionary */: {
TRY(builder.append("ValueImpl::JaktDictionary"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::JaktDictionary>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("keys: {}, ", that.keys));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("values: {}, ", that.values));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 22 /* JaktSet */: {
TRY(builder.append("ValueImpl::JaktSet"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::JaktSet>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("values: {}, ", that.values));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 23 /* RawPtr */: {
TRY(builder.append("ValueImpl::RawPtr"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::RawPtr>();
TRY(builder.appendff("({})", that.value));
break;}
case 24 /* OptionalSome */: {
TRY(builder.append("ValueImpl::OptionalSome"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::OptionalSome>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("value: {}", that.value));
}
TRY(builder.append(")"sv));
break;}
case 25 /* OptionalNone */: {
return DeprecatedString("ValueImpl::OptionalNone"sv);
break;}
case 26 /* JaktTuple */: {
TRY(builder.append("ValueImpl::JaktTuple"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::JaktTuple>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("fields: {}, ", that.fields));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 27 /* Function */: {
TRY(builder.append("ValueImpl::Function"sv));
[[maybe_unused]] auto const& that = this->template get<ValueImpl::Function>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("captures: {}, ", that.captures));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("params: {}, ", that.params));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("return_type_id: {}, ", that.return_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("block: {}, ", that.block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("can_throw: {}, ", that.can_throw));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("checked_params: {}, ", that.checked_params));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("scope_id: {}, ", that.scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("pseudo_function_id: {}", that.pseudo_function_id));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
bool types::ValueImpl::equals(NonnullRefPtr<typename types::ValueImpl> const other) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(((other)->index() == 0 /* Void */));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::Bool>();
bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::Bool>();
bool const& y = __jakt_match_value.value;
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
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U8>();
u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U8>();
u8 const& y = __jakt_match_value.value;
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
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U16>();
u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U16>();
u16 const& y = __jakt_match_value.value;
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
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U32>();
u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U32>();
u32 const& y = __jakt_match_value.value;
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
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U64>();
u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U64>();
u64 const& y = __jakt_match_value.value;
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
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I8>();
i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I8>();
i8 const& y = __jakt_match_value.value;
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
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I16>();
i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I16>();
i16 const& y = __jakt_match_value.value;
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
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I32>();
i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I32>();
i32 const& y = __jakt_match_value.value;
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
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I64>();
i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I64>();
i64 const& y = __jakt_match_value.value;
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
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::F32>();
f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::F32>();
f32 const& y = __jakt_match_value.value;
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
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::F64>();
f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::F64>();
f64 const& y = __jakt_match_value.value;
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
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::USize>();
size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::USize>();
size_t const& y = __jakt_match_value.value;
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
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
DeprecatedString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
DeprecatedString const& y = __jakt_match_value.value;
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
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::StringView>();
DeprecatedString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::StringView>();
DeprecatedString const& y = __jakt_match_value.value;
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
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CChar>();
char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CChar>();
char const& y = __jakt_match_value.value;
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
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CInt>();
int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *other;
switch(__jakt_match_variant.index()) {
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CInt>();
int const& y = __jakt_match_value.value;
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

ErrorOr<ids::TypeId> types::ValueImpl::type_id(NonnullRefPtr<types::CheckedProgram>& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<ids::TypeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(types::void_type_id());
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } ));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U16() } ));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } ));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U64() } ));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I8() } ));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I16() } ));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I32() } ));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::I64() } ));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::F32() } ));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::F64() } ));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Usize() } ));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue((TRY((((((program)))->find_type_in_scope(((((program)))->prelude_scope_id()),TRY(DeprecatedString::from_utf8("String"sv)),false)))).value()));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::JaktString() } ));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } ));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::CInt() } ));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Struct>();ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue(TRY((((((program)))->find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(parser::CheckedQualifiers(false),struct_id))),((struct_id).module),false)))));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Class>();ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue(TRY((((((program)))->find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Struct>(parser::CheckedQualifiers(false),struct_id))),((struct_id).module),false)))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Enum>();ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(TRY((((((program)))->find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::Enum>(parser::CheckedQualifiers(false),enum_id))),((enum_id).module),false)))));
};/*case end*/
default: {
{
utility::panic(TRY(DeprecatedString::from_utf8("Reflected value type not implemented"sv)));
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

ErrorOr<NonnullRefPtr<typename types::ValueImpl>> types::ValueImpl::copy() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::ValueImpl>, ErrorOr<NonnullRefPtr<typename types::ValueImpl>>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::Void>())));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::Bool>();
bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::Bool>(x))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U8>();
u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U8>(x))));
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U16>();
u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U16>(x))));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U32>();
u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U32>(x))));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::U64>();
u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::U64>(x))));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I8>();
i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I8>(x))));
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I16>();
i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I16>(x))));
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I32>();
i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I32>(x))));
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::I64>();
i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::I64>(x))));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::F32>();
f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::F32>(x))));
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::F64>();
f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::F64>(x))));
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::USize>();
size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::USize>(x))));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::JaktString>();
DeprecatedString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::JaktString>(x))));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::StringView>();
DeprecatedString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::StringView>(x))));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CChar>();
char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::CChar>(x))));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::CInt>();
int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::CInt>(x))));
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Struct>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_148; {
JaktInternal::DynamicArray<types::Value> fields_copy = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
TRY((((fields_copy).push(TRY((((field).copy())))))));
}

}
}

__jakt_var_148 = TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::Struct>(fields_copy,struct_id,constructor))); goto __jakt_label_142;

}
__jakt_label_142:; __jakt_var_148.release_value(); }));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Class>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<ids::FunctionId> const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::Class>(fields,struct_id,constructor))));
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Enum>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::EnumId const& enum_id = __jakt_match_value.enum_id;
ids::FunctionId const& constructor = __jakt_match_value.constructor;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_149; {
JaktInternal::DynamicArray<types::Value> fields_copy = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value field = (_magic_value.value());
{
TRY((((fields_copy).push(TRY((((field).copy())))))));
}

}
}

__jakt_var_149 = TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::Enum>(fields_copy,enum_id,constructor))); goto __jakt_label_143;

}
__jakt_label_143:; __jakt_var_149.release_value(); }));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktArray>();JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_150; {
JaktInternal::DynamicArray<types::Value> values_copy = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
TRY((((values_copy).push(TRY((((value).copy())))))));
}

}
}

__jakt_var_150 = TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::JaktArray>(values_copy,type_id))); goto __jakt_label_144;

}
__jakt_label_144:; __jakt_var_150.release_value(); }));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktDictionary>();JaktInternal::DynamicArray<types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_151; {
JaktInternal::DynamicArray<types::Value> values_copy = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
TRY((((values_copy).push(TRY((((value).copy())))))));
}

}
}

JaktInternal::DynamicArray<types::Value> keys_copy = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((keys).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value key = (_magic_value.value());
{
TRY((((keys_copy).push(TRY((((key).copy())))))));
}

}
}

__jakt_var_151 = TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::JaktDictionary>(keys_copy,values_copy,type_id))); goto __jakt_label_145;

}
__jakt_label_145:; __jakt_var_151.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktSet>();JaktInternal::DynamicArray<types::Value> const& values = __jakt_match_value.values;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_152; {
JaktInternal::DynamicArray<types::Value> values_copy = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
TRY((((values_copy).push(TRY((((value).copy())))))));
}

}
}

__jakt_var_152 = TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::JaktSet>(values_copy,type_id))); goto __jakt_label_146;

}
__jakt_label_146:; __jakt_var_152.release_value(); }));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::ValueImpl::RawPtr>();
NonnullRefPtr<typename types::ValueImpl> const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::RawPtr>(value))));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::OptionalSome>();types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::OptionalSome>(TRY((((value).copy())))))));
};/*case end*/
case 25: {
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::OptionalNone>())));
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::JaktTuple>();JaktInternal::DynamicArray<types::Value> const& fields = __jakt_match_value.fields;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::ValueImpl>> __jakt_var_153; {
JaktInternal::DynamicArray<types::Value> values_copy = (TRY((DynamicArray<types::Value>::create_with({}))));
{
JaktInternal::ArrayIterator<types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::Value value = (_magic_value.value());
{
TRY((((values_copy).push(TRY((((value).copy())))))));
}

}
}

__jakt_var_153 = TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::JaktTuple>(values_copy,type_id))); goto __jakt_label_147;

}
__jakt_label_147:; __jakt_var_153.release_value(); }));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::ValueImpl::Function>();JaktInternal::Dictionary<DeprecatedString,types::Value> const& captures = __jakt_match_value.captures;
JaktInternal::Dictionary<DeprecatedString,JaktInternal::Tuple<ids::TypeId,JaktInternal::Optional<NonnullRefPtr<typename types::CheckedExpression>>>> const& params = __jakt_match_value.params;
bool const& can_throw = __jakt_match_value.can_throw;
ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
ids::TypeId const& type_id = __jakt_match_value.type_id;
types::CheckedBlock const& block = __jakt_match_value.block;
JaktInternal::DynamicArray<types::CheckedParameter> const& checked_params = __jakt_match_value.checked_params;
ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
JaktInternal::Optional<ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
return JaktInternal::ExplicitValue(TRY((types::ValueImpl::template __jakt_create<typename types::ValueImpl::Function>(captures,params,return_type_id,type_id,block,can_throw,checked_params,scope_id,pseudo_function_id))));
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

ErrorOr<DeprecatedString> types::BlockControlFlow::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* AlwaysReturns */: {
return DeprecatedString("BlockControlFlow::AlwaysReturns"sv);
break;}
case 1 /* AlwaysTransfersControl */: {
TRY(builder.append("BlockControlFlow::AlwaysTransfersControl"sv));
[[maybe_unused]] auto const& that = this->template get<BlockControlFlow::AlwaysTransfersControl>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("might_break: {}", that.might_break));
}
TRY(builder.append(")"sv));
break;}
case 2 /* NeverReturns */: {
return DeprecatedString("BlockControlFlow::NeverReturns"sv);
break;}
case 3 /* MayReturn */: {
return DeprecatedString("BlockControlFlow::MayReturn"sv);
break;}
case 4 /* PartialAlwaysReturns */: {
TRY(builder.append("BlockControlFlow::PartialAlwaysReturns"sv));
[[maybe_unused]] auto const& that = this->template get<BlockControlFlow::PartialAlwaysReturns>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("might_break: {}", that.might_break));
}
TRY(builder.append(")"sv));
break;}
case 5 /* PartialAlwaysTransfersControl */: {
TRY(builder.append("BlockControlFlow::PartialAlwaysTransfersControl"sv));
[[maybe_unused]] auto const& that = this->template get<BlockControlFlow::PartialAlwaysTransfersControl>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("might_break: {}", that.might_break));
}
TRY(builder.append(")"sv));
break;}
case 6 /* PartialNeverReturns */: {
TRY(builder.append("BlockControlFlow::PartialNeverReturns"sv));
[[maybe_unused]] auto const& that = this->template get<BlockControlFlow::PartialNeverReturns>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("might_break: {}", that.might_break));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
types::BlockControlFlow types::BlockControlFlow::updated(types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(second);
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(((*this).unify_with(second)));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(((*this).unify_with(second)));
};/*case end*/
case 6: {
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

bool types::BlockControlFlow::is_reachable() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue(false);
};/*case end*/
case 1: {
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

bool types::BlockControlFlow::always_returns() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
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

bool types::BlockControlFlow::always_transfers_control() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 1: {
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

types::BlockControlFlow types::BlockControlFlow::branch_unify_with(types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue(second);
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(might_break) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(might_break) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(might_break) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(might_break) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(might_break) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(might_break) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(might_break) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(this_might_break) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(this_might_break) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(this_might_break) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns((might_break || this_might_break)) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns((might_break || this_might_break)) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(this_might_break) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(this_might_break) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(this_might_break) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns((might_break || this_might_break)) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns((might_break || this_might_break)) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& this_might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(this_might_break) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(this_might_break) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(this_might_break) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl((might_break || this_might_break)) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns((might_break || this_might_break)) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns((might_break || this_might_break)) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((might_break || this_might_break)) } );
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

types::BlockControlFlow types::BlockControlFlow::definitive() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
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

types::BlockControlFlow types::BlockControlFlow::partial() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(false) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(false) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(might_break) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(might_break) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(might_break) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(might_break) } );
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

bool types::BlockControlFlow::may_break() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(might_break);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(might_break);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(might_break);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
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

types::BlockControlFlow types::BlockControlFlow::unify_with(types::BlockControlFlow const second) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue(second);
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(lhs) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(lhs) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(lhs) } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(lhs) } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(might_break) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns(might_break) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(might_break) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(might_break) } );
};/*case end*/
default: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysReturns((lhs || might_break)) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysReturns() } );
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(lhs) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(lhs) } );
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(lhs) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl(lhs) } );
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& lhs = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, types::BlockControlFlow>{
auto&& __jakt_match_variant = second;
switch(__jakt_match_variant.index()) {
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialNeverReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns((lhs || might_break)) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::PartialAlwaysReturns>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialAlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 0: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl(lhs) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::BlockControlFlow::AlwaysTransfersControl>();bool const& might_break = __jakt_match_value.might_break;
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::AlwaysTransfersControl((lhs || might_break)) } );
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::PartialNeverReturns(lhs) } );
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
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

bool types::BlockControlFlow::may_return() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 3: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 6: {
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
switch(__jakt_match_variant.index()) {
case 2: {
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

ErrorOr<DeprecatedString> types::CheckedMatchBody::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Expression */: {
TRY(builder.append("CheckedMatchBody::Expression"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedMatchBody::Expression>();
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Block */: {
TRY(builder.append("CheckedMatchBody::Block"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedMatchBody::Block>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::CheckedStatement::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Expression */: {
TRY(builder.append("CheckedStatement::Expression"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Expression>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 1 /* Defer */: {
TRY(builder.append("CheckedStatement::Defer"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Defer>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("statement: {}, ", that.statement));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 2 /* DestructuringAssignment */: {
TRY(builder.append("CheckedStatement::DestructuringAssignment"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::DestructuringAssignment>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("vars: {}, ", that.vars));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("var_decl: {}, ", that.var_decl));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 3 /* VarDecl */: {
TRY(builder.append("CheckedStatement::VarDecl"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::VarDecl>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("var_id: {}, ", that.var_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("init: {}, ", that.init));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 4 /* If */: {
TRY(builder.append("CheckedStatement::If"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::If>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("condition: {}, ", that.condition));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("then_block: {}, ", that.then_block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("else_statement: {}, ", that.else_statement));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 5 /* Block */: {
TRY(builder.append("CheckedStatement::Block"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Block>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("block: {}, ", that.block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 6 /* Loop */: {
TRY(builder.append("CheckedStatement::Loop"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Loop>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("block: {}, ", that.block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 7 /* While */: {
TRY(builder.append("CheckedStatement::While"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::While>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("condition: {}, ", that.condition));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("block: {}, ", that.block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 8 /* Return */: {
TRY(builder.append("CheckedStatement::Return"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Return>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("val: {}, ", that.val));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 9 /* Break */: {
TRY(builder.append("CheckedStatement::Break"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Break>();
TRY(builder.appendff("({})", that.value));
break;}
case 10 /* Continue */: {
TRY(builder.append("CheckedStatement::Continue"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Continue>();
TRY(builder.appendff("({})", that.value));
break;}
case 11 /* Throw */: {
TRY(builder.append("CheckedStatement::Throw"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Throw>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 12 /* Yield */: {
TRY(builder.append("CheckedStatement::Yield"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Yield>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 13 /* InlineCpp */: {
TRY(builder.append("CheckedStatement::InlineCpp"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::InlineCpp>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("lines: {}, ", that.lines));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 14 /* Garbage */: {
TRY(builder.append("CheckedStatement::Garbage"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedStatement::Garbage>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
JaktInternal::Optional<utility::Span> types::CheckedStatement::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<utility::Span>, JaktInternal::Optional<utility::Span>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Expression>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<utility::Span>>(span));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Defer>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::DestructuringAssignment>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::VarDecl>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::If>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Block>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Loop>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::While>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Return>();JaktInternal::Optional<utility::Span> const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Break>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Continue>();
utility::Span const& span = __jakt_match_value.value;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Throw>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::Yield>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedStatement::InlineCpp>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedStatement::Garbage>();
utility::Span const& span = __jakt_match_value.value;
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

ErrorOr<DeprecatedString> types::CheckedEnumVariant::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Untyped */: {
TRY(builder.append("CheckedEnumVariant::Untyped"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedEnumVariant::Untyped>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("enum_id: {}, ", that.enum_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 1 /* Typed */: {
TRY(builder.append("CheckedEnumVariant::Typed"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedEnumVariant::Typed>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("enum_id: {}, ", that.enum_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 2 /* WithValue */: {
TRY(builder.append("CheckedEnumVariant::WithValue"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedEnumVariant::WithValue>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("enum_id: {}, ", that.enum_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 3 /* StructLike */: {
TRY(builder.append("CheckedEnumVariant::StructLike"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedEnumVariant::StructLike>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("enum_id: {}, ", that.enum_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("fields: {}, ", that.fields));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
ids::EnumId types::CheckedEnumVariant::enum_id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::EnumId, ids::EnumId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue(enum_id);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();ids::EnumId const& enum_id = __jakt_match_value.enum_id;
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

DeprecatedString types::CheckedEnumVariant::name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, DeprecatedString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();DeprecatedString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();DeprecatedString const& name = __jakt_match_value.name;
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

bool types::CheckedEnumVariant::equals(types::CheckedEnumVariant const other) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();DeprecatedString const& this_name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = other;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();DeprecatedString const& other_name = __jakt_match_value.name;
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

utility::Span types::CheckedEnumVariant::span() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<utility::Span, utility::Span>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Untyped>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::Typed>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::WithValue>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedEnumVariant::StructLike>();utility::Span const& span = __jakt_match_value.span;
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

ErrorOr<DeprecatedString> types::CheckedMatchCase::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* EnumVariant */: {
TRY(builder.append("CheckedMatchCase::EnumVariant"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedMatchCase::EnumVariant>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("defaults: {}, ", that.defaults));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("args: {}, ", that.args));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("subject_type_id: {}, ", that.subject_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("index: {}, ", that.index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("scope_id: {}, ", that.scope_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("body: {}, ", that.body));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("marker_span: {}", that.marker_span));
}
TRY(builder.append(")"sv));
break;}
case 1 /* Expression */: {
TRY(builder.append("CheckedMatchCase::Expression"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedMatchCase::Expression>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("defaults: {}, ", that.defaults));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expression: {}, ", that.expression));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("body: {}, ", that.body));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("marker_span: {}", that.marker_span));
}
TRY(builder.append(")"sv));
break;}
case 2 /* ClassInstance */: {
TRY(builder.append("CheckedMatchCase::ClassInstance"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedMatchCase::ClassInstance>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("defaults: {}, ", that.defaults));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type: {}, ", that.type));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("body: {}, ", that.body));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("rebind_name: {}, ", that.rebind_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("marker_span: {}", that.marker_span));
}
TRY(builder.append(")"sv));
break;}
case 3 /* CatchAll */: {
TRY(builder.append("CheckedMatchCase::CatchAll"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedMatchCase::CatchAll>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("defaults: {}, ", that.defaults));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("has_arguments: {}, ", that.has_arguments));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("body: {}, ", that.body));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("marker_span: {}", that.marker_span));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::CheckedTypeCast::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Fallible */: {
TRY(builder.append("CheckedTypeCast::Fallible"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedTypeCast::Fallible>();
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Infallible */: {
TRY(builder.append("CheckedTypeCast::Infallible"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedTypeCast::Infallible>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
ids::TypeId types::CheckedTypeCast::type_id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedTypeCast::Fallible>();
ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedTypeCast::Infallible>();
ids::TypeId const& type_id = __jakt_match_value.value;
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

ErrorOr<DeprecatedString> types::NumberConstant::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Signed */: {
TRY(builder.append("NumberConstant::Signed"sv));
[[maybe_unused]] auto const& that = this->template get<NumberConstant::Signed>();
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Unsigned */: {
TRY(builder.append("NumberConstant::Unsigned"sv));
[[maybe_unused]] auto const& that = this->template get<NumberConstant::Unsigned>();
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* Floating */: {
TRY(builder.append("NumberConstant::Floating"sv));
[[maybe_unused]] auto const& that = this->template get<NumberConstant::Floating>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
ErrorOr<bool> types::NumberConstant::can_fit_number(ids::TypeId const type_id,NonnullRefPtr<types::CheckedProgram> const program) const {
{
NonnullRefPtr<typename types::Type> const type_ = ((program)->get_type(type_id));
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Signed>();
i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.index()) {
case 9: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(value,static_cast<i64>(0LL)));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue([](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(value,static_cast<i64>(0LL)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(((((program)->is_integer(type_id)) && [](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
return (infallible_enum_cast<jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(value,((type_)->min()))) && [](i64 const& self, i64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> jakt__prelude__operators::Ordering {
{
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
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Unsigned>();
u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.index()) {
case 5: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
default: {
return JaktInternal::ExplicitValue((((program)->is_integer(type_id)) && [](u64 const& self, u64 rhs) -> bool {
{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> jakt__prelude__operators::Ordering {
{
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
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Floating>();
f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<bool>>{
auto&& __jakt_match_variant = *type_;
switch(__jakt_match_variant.index()) {
case 10: {
{
utility::todo(TRY(DeprecatedString::from_utf8("Implement casting f32 to f64"sv)));
}
};/*case end*/
case 11: {
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

ErrorOr<size_t> types::NumberConstant::to_usize() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Signed>();
i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((value))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Unsigned>();
u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((value))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::NumberConstant::Floating>();
f64 const& value = __jakt_match_value.value;
{
utility::panic(TRY(DeprecatedString::from_utf8("to_usize on a floating point constant"sv)));
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

ErrorOr<DeprecatedString> types::CheckedVisibility::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Public */: {
return DeprecatedString("CheckedVisibility::Public"sv);
break;}
case 1 /* Private */: {
return DeprecatedString("CheckedVisibility::Private"sv);
break;}
case 2 /* Restricted */: {
TRY(builder.append("CheckedVisibility::Restricted"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedVisibility::Restricted>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("scopes: {}, ", that.scopes));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::CheckedNumericConstant::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* I8 */: {
TRY(builder.append("CheckedNumericConstant::I8"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::I8>();
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* I16 */: {
TRY(builder.append("CheckedNumericConstant::I16"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::I16>();
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* I32 */: {
TRY(builder.append("CheckedNumericConstant::I32"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::I32>();
TRY(builder.appendff("({})", that.value));
break;}
case 3 /* I64 */: {
TRY(builder.append("CheckedNumericConstant::I64"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::I64>();
TRY(builder.appendff("({})", that.value));
break;}
case 4 /* U8 */: {
TRY(builder.append("CheckedNumericConstant::U8"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::U8>();
TRY(builder.appendff("({})", that.value));
break;}
case 5 /* U16 */: {
TRY(builder.append("CheckedNumericConstant::U16"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::U16>();
TRY(builder.appendff("({})", that.value));
break;}
case 6 /* U32 */: {
TRY(builder.append("CheckedNumericConstant::U32"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::U32>();
TRY(builder.appendff("({})", that.value));
break;}
case 7 /* U64 */: {
TRY(builder.append("CheckedNumericConstant::U64"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::U64>();
TRY(builder.appendff("({})", that.value));
break;}
case 8 /* USize */: {
TRY(builder.append("CheckedNumericConstant::USize"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::USize>();
TRY(builder.appendff("({})", that.value));
break;}
case 9 /* F32 */: {
TRY(builder.append("CheckedNumericConstant::F32"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::F32>();
TRY(builder.appendff("({})", that.value));
break;}
case 10 /* F64 */: {
TRY(builder.append("CheckedNumericConstant::F64"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedNumericConstant::F64>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
JaktInternal::Optional<types::NumberConstant> types::CheckedNumericConstant::number_constant() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, JaktInternal::Optional<types::NumberConstant>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I8>();
i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Signed((infallible_integer_cast<i64>((value)))) } );
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I16>();
i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Signed((infallible_integer_cast<i64>((value)))) } );
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I32>();
i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Signed((infallible_integer_cast<i64>((value)))) } );
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::I64>();
i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Signed((infallible_integer_cast<i64>((value)))) } );
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U8>();
u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Unsigned((infallible_integer_cast<u64>((value)))) } );
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U16>();
u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Unsigned((infallible_integer_cast<u64>((value)))) } );
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U32>();
u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Unsigned((infallible_integer_cast<u64>((value)))) } );
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::U64>();
u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Unsigned((infallible_integer_cast<u64>((value)))) } );
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::USize>();
u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Unsigned((infallible_integer_cast<u64>((value)))) } );
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedNumericConstant::F64>();
f64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue( types::NumberConstant { typename types::NumberConstant::Floating(value) } );
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

ErrorOr<DeprecatedString> types::CheckedCapture::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* ByValue */: {
return DeprecatedString("CheckedCapture::ByValue"sv);
break;}
case 1 /* ByReference */: {
return DeprecatedString("CheckedCapture::ByReference"sv);
break;}
case 2 /* ByMutableReference */: {
return DeprecatedString("CheckedCapture::ByMutableReference"sv);
break;}
case 3 /* ByComptimeDependency */: {
return DeprecatedString("CheckedCapture::ByComptimeDependency"sv);
break;}
case 4 /* AllByReference */: {
return DeprecatedString("CheckedCapture::AllByReference"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::StructOrEnumId::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Struct */: {
TRY(builder.append("StructOrEnumId::Struct"sv));
[[maybe_unused]] auto const& that = this->template get<StructOrEnumId::Struct>();
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Enum */: {
TRY(builder.append("StructOrEnumId::Enum"sv));
[[maybe_unused]] auto const& that = this->template get<StructOrEnumId::Enum>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::SafetyMode::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Safe */: {
return DeprecatedString("SafetyMode::Safe"sv);
break;}
case 1 /* Unsafe */: {
return DeprecatedString("SafetyMode::Unsafe"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::MaybeResolvedScope::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Resolved */: {
TRY(builder.append("MaybeResolvedScope::Resolved"sv));
[[maybe_unused]] auto const& that = this->template get<MaybeResolvedScope::Resolved>();
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Unresolved */: {
TRY(builder.append("MaybeResolvedScope::Unresolved"sv));
[[maybe_unused]] auto const& that = this->template get<MaybeResolvedScope::Unresolved>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("parent_scope: {}, ", that.parent_scope));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("relative_name: \"{}\"", that.relative_name));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
ErrorOr<NonnullRefPtr<typename types::MaybeResolvedScope>> types::MaybeResolvedScope::try_resolve(NonnullRefPtr<types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename types::MaybeResolvedScope>, ErrorOr<NonnullRefPtr<typename types::MaybeResolvedScope>>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::MaybeResolvedScope::Resolved>();
ids::ScopeId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((types::MaybeResolvedScope::template __jakt_create<typename types::MaybeResolvedScope::Resolved>(id))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::MaybeResolvedScope::Unresolved>();NonnullRefPtr<typename types::MaybeResolvedScope> const& parent_scope = __jakt_match_value.parent_scope;
DeprecatedString const& relative_name = __jakt_match_value.relative_name;
return JaktInternal::ExplicitValue(({ Optional<NonnullRefPtr<typename types::MaybeResolvedScope>> __jakt_var_154; {
NonnullRefPtr<typename types::MaybeResolvedScope> parent = TRY((((parent_scope)->try_resolve(program))));
if (((parent)->index() == 0 /* Resolved */)){
ids::ScopeId const parent_scope_id = ((parent)->get<types::MaybeResolvedScope::Resolved>()).value;
ids::ScopeId const scope = parent_scope_id;
JaktInternal::Optional<ids::ScopeId> scope_id = JaktInternal::OptionalNone();
if ((!(((scope_id).has_value())))){
JaktInternal::Optional<ids::StructId> const struct_ = TRY((((program)->find_struct_in_scope(scope,relative_name,false))));
if (((struct_).has_value())){
(scope_id = ((((program)->get_struct((struct_.value())))).scope_id));
}
}
if ((!(((scope_id).has_value())))){
JaktInternal::Optional<ids::EnumId> const enum_ = TRY((((program)->find_enum_in_scope(scope,relative_name,false))));
if (((enum_).has_value())){
(scope_id = ((((program)->get_enum((enum_.value())))).scope_id));
}
}
if ((!(((scope_id).has_value())))){
JaktInternal::Optional<JaktInternal::Tuple<ids::ScopeId,bool>> const ns = TRY((((program)->find_namespace_in_scope(scope,relative_name,false,false))));
if (((ns).has_value())){
(scope_id = (((ns.value())).template get<0>()));
}
}
if ((!(((scope_id).has_value())))){
JaktInternal::Optional<JaktInternal::DynamicArray<ids::FunctionId>> const ids = TRY((((program)->find_functions_with_name_in_scope(scope,relative_name,false))));
if (((ids).has_value())){
(scope_id = ((((program)->get_function((((ids.value()))[static_cast<i64>(0LL)]))))->function_scope_id));
}
}
if (((scope_id).has_value())){
return TRY((types::MaybeResolvedScope::template __jakt_create<typename types::MaybeResolvedScope::Resolved>((scope_id.value()))));
}
}
__jakt_var_154 = TRY((types::MaybeResolvedScope::template __jakt_create<typename types::MaybeResolvedScope::Unresolved>(parent,relative_name))); goto __jakt_label_148;

}
__jakt_label_148:; __jakt_var_154.release_value(); }));
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

ErrorOr<DeprecatedString> types::StringLiteral::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Static */: {
TRY(builder.append("StringLiteral::Static"sv));
[[maybe_unused]] auto const& that = this->template get<StringLiteral::Static>();
TRY(builder.appendff("(\"{}\")", that.value));
break;}
}
return builder.to_string();
}
DeprecatedString types::StringLiteral::to_string() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, DeprecatedString>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StringLiteral::Static>();
DeprecatedString const& value = __jakt_match_value.value;
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

ErrorOr<DeprecatedString> types::StructLikeId::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Struct */: {
TRY(builder.append("StructLikeId::Struct"sv));
[[maybe_unused]] auto const& that = this->template get<StructLikeId::Struct>();
TRY(builder.appendff("({})", that.value));
break;}
case 1 /* Enum */: {
TRY(builder.append("StructLikeId::Enum"sv));
[[maybe_unused]] auto const& that = this->template get<StructLikeId::Enum>();
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* Trait */: {
TRY(builder.append("StructLikeId::Trait"sv));
[[maybe_unused]] auto const& that = this->template get<StructLikeId::Trait>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
ErrorOr<JaktInternal::Optional<types::StructLikeId>> types::StructLikeId::from_type_id(ids::TypeId const type_id,NonnullRefPtr<types::CheckedProgram> const& program) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::StructLikeId>, ErrorOr<JaktInternal::Optional<types::StructLikeId>>>{
auto&& __jakt_match_variant = *((((program)))->get_type(type_id));
switch(__jakt_match_variant.index()) {
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericInstance>();ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Struct(args,struct_id) } );
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Struct>();
ids::StructId const& struct_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Struct(args,struct_id) } );
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericEnumInstance>();ids::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Enum(args,enum_id) } );
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Enum>();
ids::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Enum(args,enum_id) } );
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::Type::GenericTraitInstance>();ids::TraitId const& trait_id = __jakt_match_value.id;
JaktInternal::DynamicArray<ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Trait(args,trait_id) } );
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::Type::Trait>();
ids::TraitId const& trait_id = __jakt_match_value.value;
JaktInternal::DynamicArray<ids::TypeId> const args = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
return JaktInternal::ExplicitValue( types::StructLikeId { typename types::StructLikeId::Trait(args,trait_id) } );
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

ErrorOr<JaktInternal::DynamicArray<ids::TypeId>> types::StructLikeId::generic_parameters(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
JaktInternal::DynamicArray<types::CheckedGenericParameter> const parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::CheckedGenericParameter>, ErrorOr<JaktInternal::DynamicArray<ids::TypeId>>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Struct>();
ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_struct(id))).generic_parameters));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Enum>();
ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_enum(id))).generic_parameters));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Trait>();
ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_trait(id)))->generic_parameters));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<ids::TypeId> result = (TRY((DynamicArray<ids::TypeId>::create_with({}))));
{
JaktInternal::ArrayIterator<types::CheckedGenericParameter> _magic = ((parameters).iterator());
for (;;){
JaktInternal::Optional<types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
types::CheckedGenericParameter parameter = (_magic_value.value());
{
TRY((((result).push(((parameter).type_id)))));
}

}
}

return result;
}
}

ErrorOr<ids::ScopeId> types::StructLikeId::associated_scope_id(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::ScopeId, ErrorOr<ids::ScopeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Struct>();
ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_struct(id))).scope_id));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Enum>();
ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_enum(id))).scope_id));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Trait>();
ids::TraitId const& id = __jakt_match_value.value;
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

ErrorOr<JaktInternal::DynamicArray<types::CheckedGenericParameter>> types::StructLikeId::generic_parameters_as_checked(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<types::CheckedGenericParameter>, ErrorOr<JaktInternal::DynamicArray<types::CheckedGenericParameter>>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Struct>();
ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_struct(id))).generic_parameters));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Enum>();
ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_enum(id))).generic_parameters));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Trait>();
ids::TraitId const& id = __jakt_match_value.value;
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

ErrorOr<ids::ScopeId> types::StructLikeId::scope_id(NonnullRefPtr<types::CheckedProgram> const& program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::ScopeId, ErrorOr<ids::ScopeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Struct>();
ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_struct(id))).scope_id));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Enum>();
ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((program)))->get_enum(id))).scope_id));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Trait>();
ids::TraitId const& id = __jakt_match_value.value;
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

ErrorOr<ids::TypeId> types::StructLikeId::specialized_by(JaktInternal::DynamicArray<ids::TypeId> const arguments,NonnullRefPtr<types::CheckedProgram>& program,ids::ModuleId const module_id,parser::CheckedQualifiers const qualifiers) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ErrorOr<ids::TypeId>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Struct>();
ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((((program)))->find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericInstance>(qualifiers,id,arguments))),module_id,false)))));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Enum>();
ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((((program)))->find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericEnumInstance>(qualifiers,id,arguments))),module_id,false)))));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::StructLikeId::Trait>();
ids::TraitId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((((program)))->find_or_add_type_id(TRY((types::Type::template __jakt_create<typename types::Type::GenericTraitInstance>(qualifiers,id,arguments))),module_id,false)))));
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

ErrorOr<DeprecatedString> types::CheckedExpression::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Boolean */: {
TRY(builder.append("CheckedExpression::Boolean"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Boolean>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("val: {}, ", that.val));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 1 /* NumericConstant */: {
TRY(builder.append("CheckedExpression::NumericConstant"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::NumericConstant>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("val: {}, ", that.val));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 2 /* QuotedString */: {
TRY(builder.append("CheckedExpression::QuotedString"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::QuotedString>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("val: {}, ", that.val));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 3 /* ByteConstant */: {
TRY(builder.append("CheckedExpression::ByteConstant"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::ByteConstant>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("val: \"{}\", ", that.val));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 4 /* CharacterConstant */: {
TRY(builder.append("CheckedExpression::CharacterConstant"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::CharacterConstant>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("val: \"{}\", ", that.val));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 5 /* CCharacterConstant */: {
TRY(builder.append("CheckedExpression::CCharacterConstant"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::CCharacterConstant>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("val: \"{}\", ", that.val));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 6 /* UnaryOp */: {
TRY(builder.append("CheckedExpression::UnaryOp"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::UnaryOp>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("op: {}, ", that.op));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 7 /* BinaryOp */: {
TRY(builder.append("CheckedExpression::BinaryOp"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::BinaryOp>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("lhs: {}, ", that.lhs));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("op: {}, ", that.op));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("rhs: {}, ", that.rhs));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 8 /* JaktTuple */: {
TRY(builder.append("CheckedExpression::JaktTuple"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::JaktTuple>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("vals: {}, ", that.vals));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 9 /* Range */: {
TRY(builder.append("CheckedExpression::Range"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Range>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("from: {}, ", that.from));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("to: {}, ", that.to));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 10 /* JaktArray */: {
TRY(builder.append("CheckedExpression::JaktArray"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::JaktArray>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("vals: {}, ", that.vals));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("repeat: {}, ", that.repeat));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("inner_type_id: {}", that.inner_type_id));
}
TRY(builder.append(")"sv));
break;}
case 11 /* JaktSet */: {
TRY(builder.append("CheckedExpression::JaktSet"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::JaktSet>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("vals: {}, ", that.vals));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("inner_type_id: {}", that.inner_type_id));
}
TRY(builder.append(")"sv));
break;}
case 12 /* JaktDictionary */: {
TRY(builder.append("CheckedExpression::JaktDictionary"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::JaktDictionary>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("vals: {}, ", that.vals));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("key_type_id: {}, ", that.key_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("value_type_id: {}", that.value_type_id));
}
TRY(builder.append(")"sv));
break;}
case 13 /* IndexedExpression */: {
TRY(builder.append("CheckedExpression::IndexedExpression"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::IndexedExpression>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("index: {}, ", that.index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 14 /* IndexedDictionary */: {
TRY(builder.append("CheckedExpression::IndexedDictionary"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::IndexedDictionary>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("index: {}, ", that.index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 15 /* IndexedTuple */: {
TRY(builder.append("CheckedExpression::IndexedTuple"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::IndexedTuple>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("index: {}, ", that.index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_optional: {}, ", that.is_optional));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 16 /* IndexedStruct */: {
TRY(builder.append("CheckedExpression::IndexedStruct"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::IndexedStruct>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("name: \"{}\", ", that.name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("index: {}, ", that.index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_optional: {}, ", that.is_optional));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 17 /* IndexedCommonEnumMember */: {
TRY(builder.append("CheckedExpression::IndexedCommonEnumMember"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::IndexedCommonEnumMember>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("index: \"{}\", ", that.index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_optional: {}, ", that.is_optional));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 18 /* ComptimeIndex */: {
TRY(builder.append("CheckedExpression::ComptimeIndex"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::ComptimeIndex>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("index: {}, ", that.index));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_optional: {}, ", that.is_optional));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 19 /* Match */: {
TRY(builder.append("CheckedExpression::Match"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Match>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("match_cases: {}, ", that.match_cases));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("all_variants_constant: {}", that.all_variants_constant));
}
TRY(builder.append(")"sv));
break;}
case 20 /* EnumVariantArg */: {
TRY(builder.append("CheckedExpression::EnumVariantArg"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::EnumVariantArg>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("arg: {}, ", that.arg));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("enum_variant: {}, ", that.enum_variant));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 21 /* Call */: {
TRY(builder.append("CheckedExpression::Call"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Call>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("call: {}, ", that.call));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 22 /* MethodCall */: {
TRY(builder.append("CheckedExpression::MethodCall"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::MethodCall>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("call: {}, ", that.call));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("is_optional: {}, ", that.is_optional));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 23 /* NamespacedVar */: {
TRY(builder.append("CheckedExpression::NamespacedVar"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::NamespacedVar>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("namespaces: {}, ", that.namespaces));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("var: {}, ", that.var));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 24 /* Var */: {
TRY(builder.append("CheckedExpression::Var"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Var>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("var: {}, ", that.var));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}", that.span));
}
TRY(builder.append(")"sv));
break;}
case 25 /* OptionalNone */: {
TRY(builder.append("CheckedExpression::OptionalNone"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::OptionalNone>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 26 /* OptionalSome */: {
TRY(builder.append("CheckedExpression::OptionalSome"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::OptionalSome>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 27 /* ForcedUnwrap */: {
TRY(builder.append("CheckedExpression::ForcedUnwrap"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::ForcedUnwrap>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 28 /* Block */: {
TRY(builder.append("CheckedExpression::Block"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Block>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("block: {}, ", that.block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 29 /* Function */: {
TRY(builder.append("CheckedExpression::Function"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Function>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("captures: {}, ", that.captures));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("params: {}, ", that.params));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("can_throw: {}, ", that.can_throw));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("return_type_id: {}, ", that.return_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("block: {}, ", that.block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("pseudo_function_id: {}, ", that.pseudo_function_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("scope_id: {}", that.scope_id));
}
TRY(builder.append(")"sv));
break;}
case 30 /* DependentFunction */: {
TRY(builder.append("CheckedExpression::DependentFunction"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::DependentFunction>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("captures: {}, ", that.captures));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("params: {}, ", that.params));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("can_throw: {}, ", that.can_throw));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("return_type_id: {}, ", that.return_type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("block: {}, ", that.block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("pseudo_function_id: {}, ", that.pseudo_function_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("scope_id: {}", that.scope_id));
}
TRY(builder.append(")"sv));
break;}
case 31 /* Try */: {
TRY(builder.append("CheckedExpression::Try"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Try>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("expr: {}, ", that.expr));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("catch_block: {}, ", that.catch_block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("catch_span: {}, ", that.catch_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("catch_name: {}, ", that.catch_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}, ", that.type_id));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("inner_type_id: {}", that.inner_type_id));
}
TRY(builder.append(")"sv));
break;}
case 32 /* TryBlock */: {
TRY(builder.append("CheckedExpression::TryBlock"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::TryBlock>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("stmt: {}, ", that.stmt));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("catch_block: {}, ", that.catch_block));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("error_name: \"{}\", ", that.error_name));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("error_span: {}, ", that.error_span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 33 /* Reflect */: {
TRY(builder.append("CheckedExpression::Reflect"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Reflect>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type: {}, ", that.type));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
case 34 /* Garbage */: {
TRY(builder.append("CheckedExpression::Garbage"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedExpression::Garbage>();
TRY(builder.append("("sv));
{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("span: {}, ", that.span));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));
TRY(builder.appendff("type_id: {}", that.type_id));
}
TRY(builder.append(")"sv));
break;}
}
return builder.to_string();
}
bool types::CheckedExpression::can_throw() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(((call).callee_throws));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();types::CheckedCall const& call = __jakt_match_value.call;
return JaktInternal::ExplicitValue(((call).callee_throws));
};/*case end*/
case 2: {
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

JaktInternal::Optional<types::NumberConstant> types::CheckedExpression::to_number_constant(NonnullRefPtr<types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>, JaktInternal::Optional<types::NumberConstant>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NumericConstant>();types::CheckedNumericConstant const& val = __jakt_match_value.val;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(((val).number_constant()));
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_155; {
JaktInternal::Optional<types::NumberConstant> result = JaktInternal::OptionalNone();
__jakt_var_155 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<types::NumberConstant>,JaktInternal::Optional<types::NumberConstant>>{
auto __jakt_enum_value = (((op).index() == 11 /* TypeCast */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<JaktInternal::Optional<types::NumberConstant>> __jakt_var_156; {
types::CheckedTypeCast const cast = ((op).get<types::CheckedUnaryOperator::TypeCast>()).value;
if ((!(((cast).index() == 1 /* Infallible */)))){
(result = JaktInternal::OptionalNone());
}
if (((!(((program)->is_integer(type_id)))) && (!(((program)->is_floating(type_id)))))){
(result = JaktInternal::OptionalNone());
}
if (((expr)->index() == 1 /* NumericConstant */)){
types::CheckedNumericConstant const val = ((expr)->get<types::CheckedExpression::NumericConstant>()).val;
(result = ((val).number_constant()));
}
__jakt_var_156 = result; goto __jakt_label_150;

}
__jakt_label_150:; __jakt_var_156.release_value(); }));
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
}); goto __jakt_label_149;

}
__jakt_label_149:; __jakt_var_155.release_value(); }));
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
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Boolean>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NumericConstant>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::QuotedString>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ByteConstant>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 4: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::CharacterConstant>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 5: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::CCharacterConstant>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::BinaryOp>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktTuple>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Range>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktArray>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktSet>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktDictionary>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedExpression>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedDictionary>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedTuple>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedStruct>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedCommonEnumMember>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ComptimeIndex>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Match>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::EnumVariantArg>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NamespacedVar>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Var>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::OptionalNone>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::OptionalSome>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ForcedUnwrap>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Block>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Function>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::DependentFunction>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Try>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::TryBlock>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 33: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Reflect>();utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(span);
};/*case end*/
case 34: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Garbage>();utility::Span const& span = __jakt_match_value.span;
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

ids::TypeId types::CheckedExpression::type() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ids::TypeId, ids::TypeId>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Bool() } ));
};/*case end*/
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::QuotedString>();types::CheckedStringLiteral const& val = __jakt_match_value.val;
return JaktInternal::ExplicitValue(((val).type_id));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U8() } ));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::CChar() } ));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::U32() } ));
};/*case end*/
case 20: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::EnumVariantArg>();types::CheckedEnumVariantBinding const& arg = __jakt_match_value.arg;
return JaktInternal::ExplicitValue(((arg).type_id));
};/*case end*/
case 23: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NamespacedVar>();NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->type_id));
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Var>();NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->type_id));
};/*case end*/
case 18: {
return JaktInternal::ExplicitValue(types::builtin( types::BuiltinType { typename types::BuiltinType::Unknown() } ));
};/*case end*/
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::NumericConstant>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 7: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::BinaryOp>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 8: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktTuple>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 9: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Range>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktArray>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktSet>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktDictionary>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedExpression>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedDictionary>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedTuple>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedStruct>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 17: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedCommonEnumMember>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Match>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 25: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::OptionalNone>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 26: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::OptionalSome>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ForcedUnwrap>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 28: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Block>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 29: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Function>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 30: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::DependentFunction>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 31: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Try>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::TryBlock>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 33: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Reflect>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(type_id);
};/*case end*/
case 34: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Garbage>();ids::TypeId const& type_id = __jakt_match_value.type_id;
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

ErrorOr<types::BlockControlFlow> types::CheckedExpression::control_flow() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 19: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Match>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
utility::Span const& span = __jakt_match_value.span;
ids::TypeId const& type_id = __jakt_match_value.type_id;
bool const& all_variants_constant = __jakt_match_value.all_variants_constant;
return JaktInternal::ExplicitValue(({ Optional<types::BlockControlFlow> __jakt_var_157; {
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = case_;
switch(__jakt_match_variant.index()) {
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::EnumVariant>();types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((expr)->control_flow()))));
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
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::Expression>();types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((expr)->control_flow()))));
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
case 2: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::ClassInstance>();types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((expr)->control_flow()))));
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
case 3: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedMatchCase::CatchAll>();types::CheckedMatchBody const& body = __jakt_match_value.body;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow, ErrorOr<types::BlockControlFlow>>{
auto&& __jakt_match_variant = body;
switch(__jakt_match_variant.index()) {
case 1: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Block>();
types::CheckedBlock const& block = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((block).control_flow));
};/*case end*/
case 0: {
auto&& __jakt_match_value = __jakt_match_variant.template get<typename types::CheckedMatchBody::Expression>();
NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((expr)->control_flow()))));
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

__jakt_var_157 = control_flow.value_or_lazy_evaluated([&] { return  types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } ; }); goto __jakt_label_151;

}
__jakt_label_151:; __jakt_var_157.release_value(); }));
};/*case end*/
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (((type_id).equals(types::never_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 21: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Call>();ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (((type_id).equals(types::never_type_id())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::NeverReturns() } );
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 32: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::TryBlock>();NonnullRefPtr<typename types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
return JaktInternal::ExplicitValue(({ Optional<types::BlockControlFlow> __jakt_var_158; {
__jakt_var_158 = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<types::BlockControlFlow,ErrorOr<types::BlockControlFlow>>{
auto __jakt_enum_value = (((stmt)->index() == 5 /* Block */));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({ Optional<types::BlockControlFlow> __jakt_var_159; {
types::CheckedBlock const block = ((stmt)->get<types::CheckedStatement::Block>()).block;
__jakt_var_159 = ((((block).control_flow)).branch_unify_with(((catch_block).control_flow))); goto __jakt_label_153;

}
__jakt_label_153:; __jakt_var_159.release_value(); }));
}
else {
{
utility::panic(TRY(DeprecatedString::from_utf8("Try block doesn't have a block"sv)));
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
return JaktInternal::ExplicitValue( types::BlockControlFlow { typename types::BlockControlFlow::MayReturn() } );
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

bool types::CheckedExpression::is_mutable(NonnullRefPtr<types::CheckedProgram> const program) const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 24: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::Var>();NonnullRefPtr<types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(((var)->is_mutable));
};/*case end*/
case 16: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedStruct>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 13: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedExpression>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 18: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ComptimeIndex>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 15: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedTuple>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 14: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::IndexedDictionary>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 27: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::ForcedUnwrap>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
return JaktInternal::ExplicitValue(((expr)->is_mutable(program)));
};/*case end*/
case 10: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktArray>();JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
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
case 11: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktSet>();JaktInternal::DynamicArray<NonnullRefPtr<typename types::CheckedExpression>> const& vals = __jakt_match_value.vals;
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
case 12: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::JaktDictionary>();JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename types::CheckedExpression>,NonnullRefPtr<typename types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
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
case 6: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::UnaryOp>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
types::CheckedUnaryOperator const& op = __jakt_match_value.op;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.index()) {
case 5: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, bool>{
auto&& __jakt_match_variant = *((program)->get_type(((expr)->type())));
switch(__jakt_match_variant.index()) {
case 29: {
return JaktInternal::ExplicitValue(true);
};/*case end*/
case 26: {
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
case 22: {
auto&& __jakt_match_value = __jakt_match_variant.template get<types::CheckedExpression::MethodCall>();NonnullRefPtr<typename types::CheckedExpression> const& expr = __jakt_match_value.expr;
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

ErrorOr<DeprecatedString> types::BuiltinType::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Void */: {
return DeprecatedString("BuiltinType::Void"sv);
break;}
case 1 /* Bool */: {
return DeprecatedString("BuiltinType::Bool"sv);
break;}
case 2 /* U8 */: {
return DeprecatedString("BuiltinType::U8"sv);
break;}
case 3 /* U16 */: {
return DeprecatedString("BuiltinType::U16"sv);
break;}
case 4 /* U32 */: {
return DeprecatedString("BuiltinType::U32"sv);
break;}
case 5 /* U64 */: {
return DeprecatedString("BuiltinType::U64"sv);
break;}
case 6 /* I8 */: {
return DeprecatedString("BuiltinType::I8"sv);
break;}
case 7 /* I16 */: {
return DeprecatedString("BuiltinType::I16"sv);
break;}
case 8 /* I32 */: {
return DeprecatedString("BuiltinType::I32"sv);
break;}
case 9 /* I64 */: {
return DeprecatedString("BuiltinType::I64"sv);
break;}
case 10 /* F32 */: {
return DeprecatedString("BuiltinType::F32"sv);
break;}
case 11 /* F64 */: {
return DeprecatedString("BuiltinType::F64"sv);
break;}
case 12 /* Usize */: {
return DeprecatedString("BuiltinType::Usize"sv);
break;}
case 13 /* JaktString */: {
return DeprecatedString("BuiltinType::JaktString"sv);
break;}
case 14 /* CChar */: {
return DeprecatedString("BuiltinType::CChar"sv);
break;}
case 15 /* CInt */: {
return DeprecatedString("BuiltinType::CInt"sv);
break;}
case 16 /* Unknown */: {
return DeprecatedString("BuiltinType::Unknown"sv);
break;}
case 17 /* Never */: {
return DeprecatedString("BuiltinType::Never"sv);
break;}
}
return builder.to_string();
}
ErrorOr<DeprecatedString> types::BuiltinType::constructor_name() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<DeprecatedString, ErrorOr<DeprecatedString>>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Void"sv)));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Bool"sv)));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("U8"sv)));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("U16"sv)));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("U32"sv)));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("U64"sv)));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("I8"sv)));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("I16"sv)));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("I32"sv)));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("I64"sv)));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("F32"sv)));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("F64"sv)));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Usize"sv)));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("JaktString"sv)));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("CChar"sv)));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("CInt"sv)));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Unknown"sv)));
};/*case end*/
case 17: {
return JaktInternal::ExplicitValue(TRY(DeprecatedString::from_utf8("Never"sv)));
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

size_t types::BuiltinType::id() const {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, size_t>{
auto&& __jakt_match_variant = *this;
switch(__jakt_match_variant.index()) {
case 0: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 2: {
return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
};/*case end*/
case 3: {
return JaktInternal::ExplicitValue(static_cast<size_t>(3ULL));
};/*case end*/
case 4: {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
};/*case end*/
case 5: {
return JaktInternal::ExplicitValue(static_cast<size_t>(5ULL));
};/*case end*/
case 6: {
return JaktInternal::ExplicitValue(static_cast<size_t>(6ULL));
};/*case end*/
case 7: {
return JaktInternal::ExplicitValue(static_cast<size_t>(7ULL));
};/*case end*/
case 8: {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
};/*case end*/
case 9: {
return JaktInternal::ExplicitValue(static_cast<size_t>(9ULL));
};/*case end*/
case 10: {
return JaktInternal::ExplicitValue(static_cast<size_t>(10ULL));
};/*case end*/
case 11: {
return JaktInternal::ExplicitValue(static_cast<size_t>(11ULL));
};/*case end*/
case 12: {
return JaktInternal::ExplicitValue(static_cast<size_t>(12ULL));
};/*case end*/
case 13: {
return JaktInternal::ExplicitValue(static_cast<size_t>(13ULL));
};/*case end*/
case 14: {
return JaktInternal::ExplicitValue(static_cast<size_t>(14ULL));
};/*case end*/
case 15: {
return JaktInternal::ExplicitValue(static_cast<size_t>(15ULL));
};/*case end*/
case 16: {
return JaktInternal::ExplicitValue(static_cast<size_t>(16ULL));
};/*case end*/
case 17: {
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

ErrorOr<DeprecatedString> types::CheckedTraitRequirements::debug_description() const {
auto builder = DeprecatedStringBuilder::create();
switch (this->index()) {case 0 /* Nothing */: {
return DeprecatedString("CheckedTraitRequirements::Nothing"sv);
break;}
case 1 /* Methods */: {
TRY(builder.append("CheckedTraitRequirements::Methods"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedTraitRequirements::Methods>();
TRY(builder.appendff("({})", that.value));
break;}
case 2 /* ComptimeExpression */: {
TRY(builder.append("CheckedTraitRequirements::ComptimeExpression"sv));
[[maybe_unused]] auto const& that = this->template get<CheckedTraitRequirements::ComptimeExpression>();
TRY(builder.appendff("({})", that.value));
break;}
}
return builder.to_string();
}
}
} // namespace Jakt
