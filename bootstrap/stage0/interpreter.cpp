#ifdef _WIN32
extern "C" __cdecl int SetConsoleOutputCP(unsigned int code_page);
#endif
#include "interpreter.h"
#include "jakt__path.h"
#include "jakt__arguments.h"
#include "jakt__prelude__operators.h"
#include "jakt__prelude__static_array.h"
namespace Jakt {
namespace interpreter {
ErrorOr<size_t> align_of_impl(Jakt::ids::TypeId const type_id,NonnullRefPtr<Jakt::interpreter::Interpreter> const interpreter) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = *((((interpreter)->program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).size_t_alignment()))));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).pointer_alignment()))));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).int_alignment()))));
};/*case end*/
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 32 /* Const */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 19 /* Dependent */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 22 /* GenericTraitInstance */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 23 /* GenericResolvedType */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
Function<Jakt::ids::TypeId(Jakt::ids::TypeId)> const resolve_type_id = [&struct_, &args](Jakt::ids::TypeId type_id) -> Jakt::ids::TypeId {{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_6([&] {
((i) += (static_cast<i64>(1LL)));
});
if (((((param).type_id)).equals(type_id))){
return ((args)[i]);
}
}

}
}

return type_id;
}
}
;
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
size_t const field_alignment = TRY((Jakt::interpreter::align_of_impl(resolve_type_id(((((((interpreter)->program))->get_variable(((field)->variable_id))))->type_id)),interpreter)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(field_alignment,align)){
(align = field_alignment);
}
}

}
}

return JaktInternal::ExplicitValue<size_t>(align);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
Jakt::types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
Function<Jakt::ids::TypeId(Jakt::ids::TypeId)> const resolve_type_id = [&struct_, &args](Jakt::ids::TypeId type_id) -> Jakt::ids::TypeId {{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_7([&] {
((i) += (static_cast<i64>(1LL)));
});
if (((((param).type_id)).equals(type_id))){
return ((args)[i]);
}
}

}
}

return type_id;
}
}
;
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
size_t const field_alignment = TRY((Jakt::interpreter::align_of_impl(resolve_type_id(((((((interpreter)->program))->get_variable(((field)->variable_id))))->type_id)),interpreter)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(field_alignment,align)){
(align = field_alignment);
}
}

}
}

return JaktInternal::ExplicitValue<size_t>(align);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
Function<Jakt::ids::TypeId(Jakt::ids::TypeId)> const resolve_type_id = [&enum_, &args](Jakt::ids::TypeId type_id) -> Jakt::ids::TypeId {{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_8([&] {
((i) += (static_cast<i64>(1LL)));
});
if (((((param).type_id)).equals(type_id))){
return ((args)[i]);
}
}

}
}

return type_id;
}
}
;
return JaktInternal::ExplicitValue<size_t>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>> {
auto __jakt_enum_value = (((((enum_).underlying_type_id)).equals(Jakt::types::void_type_id())));
if (__jakt_enum_value == true) {
{
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
size_t const variant_align = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((Jakt::interpreter::align_of_impl(resolve_type_id(type_id),interpreter))));
};/*case end*/
case 2 /* WithValue */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId field = (_magic_value.value());
{
size_t const field_alignment = TRY((Jakt::interpreter::align_of_impl(resolve_type_id(((((((interpreter)->program))->get_variable(field)))->type_id)),interpreter)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(field_alignment,align)){
(align = field_alignment);
}
}

}
}

return JaktInternal::ExplicitValue<size_t>(align);
}
VERIFY_NOT_REACHED();
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
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(variant_align,align)){
(align = variant_align);
}
}

}
}

Jakt::types::BuiltinType const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BuiltinType,ErrorOr<size_t>> {
auto __jakt_enum_value = (((((enum_).variants)).size()));
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::U8());
}
else {
return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::Usize());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
size_t const index_align = TRY((Jakt::interpreter::align_of_impl(Jakt::types::builtin(index_type),interpreter)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index_align,align)){
(align = index_align);
}
return JaktInternal::ExplicitValue<size_t>(align);
}
VERIFY_NOT_REACHED();
}
else {
return JaktInternal::ExplicitValue(TRY((Jakt::interpreter::align_of_impl(((enum_).underlying_type_id),interpreter))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
Jakt::types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
Function<Jakt::ids::TypeId(Jakt::ids::TypeId)> const resolve_type_id = [&enum_, &args](Jakt::ids::TypeId type_id) -> Jakt::ids::TypeId {{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_9([&] {
((i) += (static_cast<i64>(1LL)));
});
if (((((param).type_id)).equals(type_id))){
return ((args)[i]);
}
}

}
}

return type_id;
}
}
;
return JaktInternal::ExplicitValue<size_t>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>> {
auto __jakt_enum_value = (((((enum_).underlying_type_id)).equals(Jakt::types::void_type_id())));
if (__jakt_enum_value == true) {
{
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
size_t const variant_align = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(TRY((Jakt::interpreter::align_of_impl(resolve_type_id(type_id),interpreter))));
};/*case end*/
case 2 /* WithValue */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId field = (_magic_value.value());
{
size_t const field_alignment = TRY((Jakt::interpreter::align_of_impl(resolve_type_id(((((((interpreter)->program))->get_variable(field)))->type_id)),interpreter)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(field_alignment,align)){
(align = field_alignment);
}
}

}
}

return JaktInternal::ExplicitValue<size_t>(align);
}
VERIFY_NOT_REACHED();
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
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(variant_align,align)){
(align = variant_align);
}
}

}
}

Jakt::types::BuiltinType const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BuiltinType,ErrorOr<size_t>> {
auto __jakt_enum_value = (((((enum_).variants)).size()));
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::U8());
}
else {
return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::Usize());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
size_t const index_align = TRY((Jakt::interpreter::align_of_impl(Jakt::types::builtin(index_type),interpreter)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(index_align,align)){
(align = index_align);
}
return JaktInternal::ExplicitValue<size_t>(align);
}
VERIFY_NOT_REACHED();
}
else {
return JaktInternal::ExplicitValue(TRY((Jakt::interpreter::align_of_impl(((enum_).underlying_type_id),interpreter))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* RawPtr */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).pointer_alignment()))));
};/*case end*/
case 27 /* Trait */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 28 /* Reference */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).pointer_alignment()))));
};/*case end*/
case 29 /* MutableReference */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).pointer_alignment()))));
};/*case end*/
case 30 /* Function */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 31 /* Self */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
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

ErrorOr<size_t> size_of_impl(Jakt::ids::TypeId const type_id,NonnullRefPtr<Jakt::interpreter::Interpreter> const interpreter) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = *((((interpreter)->program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 16 /* Unknown */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 17 /* Never */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Bool */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(2ULL));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
};/*case end*/
case 10 /* F32 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(4ULL));
};/*case end*/
case 11 /* F64 */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(8ULL));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).size_t_size()))));
};/*case end*/
case 13 /* JaktString */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).pointer_size()))));
};/*case end*/
case 14 /* CChar */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(1ULL));
};/*case end*/
case 15 /* CInt */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).int_size()))));
};/*case end*/
case 18 /* TypeVariable */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 32 /* Const */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 19 /* Dependent */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 22 /* GenericTraitInstance */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 23 /* GenericResolvedType */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
Function<Jakt::ids::TypeId(Jakt::ids::TypeId)> const resolve_type_id = [&struct_, &args](Jakt::ids::TypeId type_id) -> Jakt::ids::TypeId {{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_10([&] {
((i) += (static_cast<i64>(1LL)));
});
if (((((param).type_id)).equals(type_id))){
return ((args)[i]);
}
}

}
}

return type_id;
}
}
;
size_t size = static_cast<size_t>(0ULL);
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
Jakt::ids::TypeId type_id = resolve_type_id(((((((interpreter)->program))->get_variable(((field)->variable_id))))->type_id));
size_t const field_size = TRY((Jakt::interpreter::size_of_impl(type_id,interpreter)));
size_t const field_align = TRY((Jakt::interpreter::align_of_impl(type_id,interpreter)));
size_t const slack = JaktInternal::checked_mod(size,field_align);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(field_align,slack)));
}
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(align,field_align)){
(align = field_align);
}
((size) += (field_size));
}

}
}

if (((size) == (static_cast<size_t>(0ULL)))){
(size = static_cast<size_t>(1ULL));
}
else {
size_t const total_slack = JaktInternal::checked_mod(size,align);
if (((total_slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(align,total_slack)));
}
}

return JaktInternal::ExplicitValue<size_t>(size);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
Jakt::types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
Function<Jakt::ids::TypeId(Jakt::ids::TypeId)> const resolve_type_id = [&struct_, &args](Jakt::ids::TypeId type_id) -> Jakt::ids::TypeId {{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((struct_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_11([&] {
((i) += (static_cast<i64>(1LL)));
});
if (((((param).type_id)).equals(type_id))){
return ((args)[i]);
}
}

}
}

return type_id;
}
}
;
size_t size = static_cast<size_t>(0ULL);
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
Jakt::ids::TypeId type_id = resolve_type_id(((((((interpreter)->program))->get_variable(((field)->variable_id))))->type_id));
size_t const field_size = TRY((Jakt::interpreter::size_of_impl(type_id,interpreter)));
size_t const field_align = TRY((Jakt::interpreter::align_of_impl(type_id,interpreter)));
size_t const slack = JaktInternal::checked_mod(size,field_align);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(field_align,slack)));
}
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(align,field_align)){
(align = field_align);
}
((size) += (field_size));
}

}
}

if (((size) == (static_cast<size_t>(0ULL)))){
(size = static_cast<size_t>(1ULL));
}
else {
size_t const total_slack = JaktInternal::checked_mod(size,align);
if (((total_slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(align,total_slack)));
}
}

return JaktInternal::ExplicitValue<size_t>(size);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
Function<Jakt::ids::TypeId(Jakt::ids::TypeId)> const resolve_type_id = [&enum_, &args](Jakt::ids::TypeId type_id) -> Jakt::ids::TypeId {{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_12([&] {
((i) += (static_cast<i64>(1LL)));
});
if (((((param).type_id)).equals(type_id))){
return ((args)[i]);
}
}

}
}

return type_id;
}
}
;
return JaktInternal::ExplicitValue<size_t>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>> {
auto __jakt_enum_value = (((((enum_).underlying_type_id)).equals(Jakt::types::void_type_id())));
if (__jakt_enum_value == true) {
{
size_t size = static_cast<size_t>(0ULL);
size_t container_align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
size_t const variant_size = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
size_t const align = TRY((Jakt::interpreter::align_of_impl(resolve_type_id(type_id),interpreter)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(align,container_align)){
(container_align = align);
}
return JaktInternal::ExplicitValue<size_t>(TRY((Jakt::interpreter::size_of_impl(type_id,interpreter))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* WithValue */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
size_t size = static_cast<size_t>(0ULL);
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId field = (_magic_value.value());
{
Jakt::ids::TypeId const type_id = resolve_type_id(((((((interpreter)->program))->get_variable(field)))->type_id));
size_t const field_size = TRY((Jakt::interpreter::size_of_impl(type_id,interpreter)));
size_t const field_alignment = TRY((Jakt::interpreter::align_of_impl(type_id,interpreter)));
size_t const slack = JaktInternal::checked_mod(size,field_alignment);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(field_alignment,slack)));
}
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(align,field_alignment)){
(align = field_alignment);
}
((size) += (field_size));
}

}
}

if (((size) == (static_cast<size_t>(0ULL)))){
(size = static_cast<size_t>(1ULL));
}
else {
size_t const total_slack = JaktInternal::checked_mod(size,align);
if (((total_slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(align,total_slack)));
}
}

if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(align,container_align)){
(container_align = align);
}
return JaktInternal::ExplicitValue<size_t>(size);
}
VERIFY_NOT_REACHED();
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
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(variant_size,size)){
(size = variant_size);
}
}

}
}

Jakt::types::BuiltinType const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BuiltinType,ErrorOr<size_t>> {
auto __jakt_enum_value = (((((enum_).variants)).size()));
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::U8());
}
else {
return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::Usize());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
size_t const index_align = TRY((Jakt::interpreter::align_of_impl(Jakt::types::builtin(index_type),interpreter)));
size_t const index_size = TRY((Jakt::interpreter::size_of_impl(Jakt::types::builtin(index_type),interpreter)));
size_t const index_slack = JaktInternal::checked_mod(size,index_align);
if (((index_slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(index_align,index_slack)));
}
((size) += (index_size));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(container_align,index_align)){
size_t const slack = JaktInternal::checked_mod(size,container_align);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(container_align,slack)));
}
}
return JaktInternal::ExplicitValue<size_t>(size);
}
VERIFY_NOT_REACHED();
}
else {
return JaktInternal::ExplicitValue(TRY((Jakt::interpreter::align_of_impl(((enum_).underlying_type_id),interpreter))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const args = DynamicArray<Jakt::ids::TypeId>::create_with({});
{
Jakt::types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
Function<Jakt::ids::TypeId(Jakt::ids::TypeId)> const resolve_type_id = [&enum_, &args](Jakt::ids::TypeId type_id) -> Jakt::ids::TypeId {{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((enum_).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter param = (_magic_value.value());
{
ScopeGuard __jakt_var_13([&] {
((i) += (static_cast<i64>(1LL)));
});
if (((((param).type_id)).equals(type_id))){
return ((args)[i]);
}
}

}
}

return type_id;
}
}
;
return JaktInternal::ExplicitValue<size_t>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t,ErrorOr<size_t>> {
auto __jakt_enum_value = (((((enum_).underlying_type_id)).equals(Jakt::types::void_type_id())));
if (__jakt_enum_value == true) {
{
size_t size = static_cast<size_t>(0ULL);
size_t container_align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((enum_).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
size_t const variant_size = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<size_t>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
size_t const align = TRY((Jakt::interpreter::align_of_impl(resolve_type_id(type_id),interpreter)));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(align,container_align)){
(container_align = align);
}
return JaktInternal::ExplicitValue<size_t>(TRY((Jakt::interpreter::size_of_impl(type_id,interpreter))));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* WithValue */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
size_t size = static_cast<size_t>(0ULL);
size_t align = static_cast<size_t>(0ULL);
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId field = (_magic_value.value());
{
Jakt::ids::TypeId const type_id = resolve_type_id(((((((interpreter)->program))->get_variable(field)))->type_id));
size_t const field_size = TRY((Jakt::interpreter::size_of_impl(type_id,interpreter)));
size_t const field_alignment = TRY((Jakt::interpreter::align_of_impl(type_id,interpreter)));
size_t const slack = JaktInternal::checked_mod(size,field_alignment);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(field_alignment,slack)));
}
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(align,field_alignment)){
(align = field_alignment);
}
((size) += (field_size));
}

}
}

if (((size) == (static_cast<size_t>(0ULL)))){
(size = static_cast<size_t>(1ULL));
}
else {
size_t const total_slack = JaktInternal::checked_mod(size,align);
if (((total_slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(align,total_slack)));
}
}

if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(align,container_align)){
(container_align = align);
}
return JaktInternal::ExplicitValue<size_t>(size);
}
VERIFY_NOT_REACHED();
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
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(variant_size,size)){
(size = variant_size);
}
}

}
}

Jakt::types::BuiltinType const index_type = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::BuiltinType,ErrorOr<size_t>> {
auto __jakt_enum_value = (((((enum_).variants)).size()));
if (__jakt_enum_value >= static_cast<size_t>(0ULL)&& __jakt_enum_value < static_cast<size_t>(256ULL)) {
return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::U8());
}
else {
return JaktInternal::ExplicitValue(Jakt::types::BuiltinType::Usize());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
size_t const index_align = TRY((Jakt::interpreter::align_of_impl(Jakt::types::builtin(index_type),interpreter)));
size_t const index_size = TRY((Jakt::interpreter::size_of_impl(Jakt::types::builtin(index_type),interpreter)));
size_t const index_slack = JaktInternal::checked_mod(size,index_align);
if (((index_slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(index_align,index_slack)));
}
((size) += (index_size));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(container_align,index_align)){
size_t const slack = JaktInternal::checked_mod(size,container_align);
if (((slack) != (static_cast<size_t>(0ULL)))){
((size) += (JaktInternal::checked_sub(container_align,slack)));
}
}
return JaktInternal::ExplicitValue<size_t>(size);
}
VERIFY_NOT_REACHED();
}
else {
return JaktInternal::ExplicitValue(TRY((Jakt::interpreter::align_of_impl(((enum_).underlying_type_id),interpreter))));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* RawPtr */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).pointer_size()))));
};/*case end*/
case 27 /* Trait */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 28 /* Reference */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).pointer_size()))));
};/*case end*/
case 29 /* MutableReference */: {
return JaktInternal::ExplicitValue(TRY((((TRY((Jakt::jakt__platform::Target::active()))).pointer_size()))));
};/*case end*/
case 30 /* Function */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
};/*case end*/
case 31 /* Self */: {
return JaktInternal::ExplicitValue(static_cast<size_t>(0ULL));
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

ErrorOr<Jakt::types::Value> cast_value_to_type(Jakt::types::Value const this_value,Jakt::ids::TypeId const type_id,NonnullRefPtr<Jakt::interpreter::Interpreter> const interpreter,bool const saturating) {
{
NonnullRefPtr<typename Jakt::types::Type> const type = ((((interpreter)->program))->get_type(type_id));
bool const is_optional = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
return JaktInternal::ExplicitValue(((id).equals(TRY((((((interpreter)->program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Optional"sv)))))))));
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
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U8((infallible_integer_cast<u8>((value)))),((this_value).span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U8((infallible_integer_cast<u8>((value)))),((this_value).span)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U8((infallible_integer_cast<u8>((value)))),((this_value).span)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U8((infallible_integer_cast<u8>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
case 3 /* U16 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U16((infallible_integer_cast<u16>((value)))),((this_value).span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U16((infallible_integer_cast<u16>((value)))),((this_value).span)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U16((infallible_integer_cast<u16>((value)))),((this_value).span)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U16((infallible_integer_cast<u16>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
case 4 /* U32 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U32((infallible_integer_cast<u32>((value)))),((this_value).span)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U32((infallible_integer_cast<u32>((value)))),((this_value).span)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U32((infallible_integer_cast<u32>((value)))),((this_value).span)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U32((infallible_integer_cast<u32>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
case 5 /* U64 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64((infallible_integer_cast<u64>((value)))),((this_value).span)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64((infallible_integer_cast<u64>((value)))),((this_value).span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64((infallible_integer_cast<u64>((value)))),((this_value).span)));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64((infallible_integer_cast<u64>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
case 6 /* I8 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I8((infallible_integer_cast<i8>((value)))),((this_value).span)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I8((infallible_integer_cast<i8>((value)))),((this_value).span)));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I8((infallible_integer_cast<i8>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
case 7 /* I16 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I16((infallible_integer_cast<i16>((value)))),((this_value).span)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I16((infallible_integer_cast<i16>((value)))),((this_value).span)));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I16((infallible_integer_cast<i16>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
case 8 /* I32 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I32((infallible_integer_cast<i32>((value)))),((this_value).span)));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I32((infallible_integer_cast<i32>((value)))),((this_value).span)));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I32((infallible_integer_cast<i32>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
case 9 /* I64 */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I64((infallible_integer_cast<i64>((value)))),((this_value).span)));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I64((infallible_integer_cast<i64>((value)))),((this_value).span)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I64((infallible_integer_cast<i64>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
case 12 /* Usize */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::USize((infallible_integer_cast<size_t>((value)))),((this_value).span)));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(this_value);
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
}));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_optional);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
return JaktInternal::ExplicitValue(this_value);
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(this_value);
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(this_value),((this_value).span)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
return JaktInternal::ExplicitValue(this_value);
}
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

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> value_to_checked_expression(Jakt::types::Value const this_value,NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((this_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
{
TRY((((interpreter)->error((ByteString::from_utf8_without_validation("Cannot convert void to expression"sv)),((this_value).span)))));
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::Boolean(JaktInternal::OptionalNone(),x,((this_value).span)));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U8(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::U8())));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U16(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::U16())));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U32(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::U32())));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::U64(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::U64())));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I8(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::I8())));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I16(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::I16())));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I32(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::I32())));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I64(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::I64())));
};/*case end*/
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::F32(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::F32())));
};/*case end*/
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::F64(x),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::F64())));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::USize((infallible_integer_cast<u64>((x)))),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::Usize())));
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::QuotedString(JaktInternal::OptionalNone(),Jakt::types::CheckedStringLiteral(Jakt::types::StringLiteral::Static(Jakt::utility::escape_for_quotes(x)),((((interpreter)->program))->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),TRY((((((interpreter)->program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("String"sv))))))),((((interpreter)->program))->prelude_module_id()),false)),false),((this_value).span)));
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::QuotedString(JaktInternal::OptionalNone(),Jakt::types::CheckedStringLiteral(Jakt::types::StringLiteral::Static(Jakt::utility::escape_for_quotes(x)),((((interpreter)->program))->find_or_add_type_id(Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),TRY((((((interpreter)->program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("StringView"sv))))))),((((interpreter)->program))->prelude_module_id()),false)),false),((this_value).span)));
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::CCharacterConstant(JaktInternal::OptionalNone(),__jakt_format((StringView::from_string_literal("{}"sv)),x),((this_value).span)));
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::NumericConstant(JaktInternal::OptionalNone(),Jakt::types::CheckedNumericConstant::I32((infallible_integer_cast<i32>((x)))),((this_value).span),Jakt::types::builtin(Jakt::types::BuiltinType::CInt())));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::OptionalNone(JaktInternal::OptionalNone(),((this_value).span),Jakt::types::unknown_type_id()));
};/*case end*/
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr = TRY((Jakt::interpreter::value_to_checked_expression(value,interpreter)));
Jakt::ids::TypeId const inner_type_id = ((expr)->type());
Jakt::ids::StructId const optional_struct_id = TRY((((((interpreter)->program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Optional"sv))))));
NonnullRefPtr<typename Jakt::types::Type> const type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({inner_type_id}));
Jakt::ids::TypeId const type_id = ((interpreter)->find_or_add_type_id(type));
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::OptionalSome(JaktInternal::OptionalNone(),expr,((this_value).span),type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::Value field = (_magic_value.value());
{
((vals).push(TRY((Jakt::interpreter::value_to_checked_expression(field,interpreter)))));
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::JaktTuple(JaktInternal::OptionalNone(),vals,((this_value).span),type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
if ((!(((constructor).has_value())))){
TRY((((interpreter)->error_with_hint((ByteString::from_utf8_without_validation("Cannot convert struct to expression without constructor"sv)),((this_value).span),(ByteString::from_utf8_without_validation("Given struct cannot be created from its contents in any known way"sv)),((this_value).span)))));
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> materialised_fields = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::Value field = (_magic_value.value());
{
((materialised_fields).push(TRY((Jakt::interpreter::value_to_checked_expression(field,interpreter)))));
}

}
}

Jakt::types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> reversed_namespace = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = ((struct_).scope_id);
while (((scope_id).has_value())){
NonnullRefPtr<Jakt::types::Scope> const scope = ((((interpreter)->program))->get_scope((scope_id.value())));
if (((((scope)->namespace_name)).has_value())){
((reversed_namespace).push(Jakt::types::ResolvedNamespace((((scope)->namespace_name).value()),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
}
(scope_id = ((scope)->parent));
}
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> namespace_ = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((reversed_namespace).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((namespace_).push(((reversed_namespace)[JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))])));
}

}
}

NonnullRefPtr<Jakt::types::CheckedFunction> const callee = ((((interpreter)->program))->get_function((constructor.value())));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((materialised_fields).size()),((((callee)->params)).size()))){
TRY((((interpreter)->error_with_hint((ByteString::from_utf8_without_validation("Too many arguments for constructor"sv)),((this_value).span),__jakt_format((StringView::from_string_literal("Expected at most {} arguments, got {}"sv)),((((callee)->params)).size()),((materialised_fields).size())),((this_value).span)))));
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
ByteString const name = ((struct_).name);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> args = DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((materialised_fields).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const arg = ((materialised_fields)[i]);
ByteString const label = ((((((((callee)->params))[i])).variable))->name);
((args).push((Tuple{label, arg})));
}

}
}

Jakt::types::CheckedCall const call = Jakt::types::CheckedCall(namespace_,name,args,DynamicArray<Jakt::ids::TypeId>::create_with({}),constructor,((struct_).type_id),((callee)->can_throw),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default());
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Call(JaktInternal::OptionalNone(),call,((this_value).span),((struct_).type_id)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
if ((!(((constructor).has_value())))){
TRY((((interpreter)->error_with_hint((ByteString::from_utf8_without_validation("Cannot convert struct to expression without constructor"sv)),((this_value).span),(ByteString::from_utf8_without_validation("Given struct cannot be created from its contents in any known way"sv)),((this_value).span)))));
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> materialised_fields = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::Value field = (_magic_value.value());
{
((materialised_fields).push(TRY((Jakt::interpreter::value_to_checked_expression(field,interpreter)))));
}

}
}

Jakt::types::CheckedStruct const struct_ = ((((interpreter)->program))->get_struct(struct_id));
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> reversed_namespace = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = ((struct_).scope_id);
while (((scope_id).has_value())){
NonnullRefPtr<Jakt::types::Scope> const scope = ((((interpreter)->program))->get_scope((scope_id.value())));
if (((((scope)->namespace_name)).has_value())){
((reversed_namespace).push(Jakt::types::ResolvedNamespace((((scope)->namespace_name).value()),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
}
(scope_id = ((scope)->parent));
}
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> namespace_ = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((reversed_namespace).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((namespace_).push(((reversed_namespace)[JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))])));
}

}
}

NonnullRefPtr<Jakt::types::CheckedFunction> const callee = ((((interpreter)->program))->get_function((constructor.value())));
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((materialised_fields).size()),((((callee)->params)).size()))){
TRY((((interpreter)->error_with_hint((ByteString::from_utf8_without_validation("Too many arguments for constructor"sv)),((this_value).span),__jakt_format((StringView::from_string_literal("Expected at most {} arguments, got {}"sv)),((((callee)->params)).size()),((materialised_fields).size())),((this_value).span)))));
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
ByteString const name = ((struct_).name);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> args = DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((materialised_fields).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const arg = ((materialised_fields)[i]);
ByteString const label = ((((((((callee)->params))[i])).variable))->name);
((args).push((Tuple{label, arg})));
}

}
}

Jakt::types::CheckedCall const call = Jakt::types::CheckedCall(namespace_,name,args,DynamicArray<Jakt::ids::TypeId>::create_with({}),constructor,((struct_).type_id),((callee)->can_throw),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default());
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Call(JaktInternal::OptionalNone(),call,((this_value).span),((struct_).type_id)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
Jakt::ids::FunctionId const& constructor = __jakt_match_value.constructor;
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> materialised_fields = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::Value field = (_magic_value.value());
{
((materialised_fields).push(TRY((Jakt::interpreter::value_to_checked_expression(field,interpreter)))));
}

}
}

Jakt::types::CheckedEnum const enum_ = ((((interpreter)->program))->get_enum(enum_id));
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> reversed_namespace = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
JaktInternal::Optional<Jakt::ids::ScopeId> scope_id = ((enum_).scope_id);
while (((scope_id).has_value())){
NonnullRefPtr<Jakt::types::Scope> const scope = ((((interpreter)->program))->get_scope((scope_id.value())));
if (((((scope)->namespace_name)).has_value())){
((reversed_namespace).push(Jakt::types::ResolvedNamespace((((scope)->namespace_name).value()),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
}
(scope_id = ((scope)->parent));
}
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> namespace_ = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(((reversed_namespace).size())),static_cast<size_t>(static_cast<size_t>(0ULL))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((namespace_).push(((reversed_namespace)[JaktInternal::checked_sub(i,static_cast<size_t>(1ULL))])));
}

}
}

((namespace_).push(Jakt::types::ResolvedNamespace(((enum_).name),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
ByteString const name = ((enum_).name);
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> args = DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((materialised_fields).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const arg = ((materialised_fields)[i]);
((args).push((Tuple{(ByteString::from_utf8_without_validation(""sv)), arg})));
}

}
}

NonnullRefPtr<Jakt::types::CheckedFunction> const callee = ((((interpreter)->program))->get_function(constructor));
Jakt::types::CheckedCall const call = Jakt::types::CheckedCall(namespace_,((callee)->name),args,DynamicArray<Jakt::ids::TypeId>::create_with({}),constructor,((enum_).type_id),((callee)->can_throw),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default());
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Call(JaktInternal::OptionalNone(),call,((this_value).span),((enum_).type_id)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::Value value = (_magic_value.value());
{
((vals).push(TRY((Jakt::interpreter::value_to_checked_expression(value,interpreter)))));
}

}
}

Jakt::ids::TypeId const inner_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((((interpreter)->program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
default: {
{
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Expected generic instance of Array while materialising an array"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::JaktArray(JaktInternal::OptionalNone(),vals,JaktInternal::OptionalNone(),((this_value).span),type_id,inner_type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> vals = DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((vals).push((Tuple{TRY((Jakt::interpreter::value_to_checked_expression(((keys)[i]),interpreter))), TRY((Jakt::interpreter::value_to_checked_expression(((values)[i]),interpreter)))})));
}

}
}

JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> const key_type_id_value_type_id_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((((interpreter)->program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue((Tuple{((args)[static_cast<i64>(0LL)]), ((args)[static_cast<i64>(1LL)])}));
};/*case end*/
default: {
{
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Expected generic instance of Dictionary while materialising an array"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::TypeId const key_type_id = ((key_type_id_value_type_id_).template get<0>());
Jakt::ids::TypeId const value_type_id = ((key_type_id_value_type_id_).template get<1>());

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::JaktDictionary(JaktInternal::OptionalNone(),vals,((this_value).span),type_id,key_type_id,value_type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> vals = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((values).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((vals).push(TRY((Jakt::interpreter::value_to_checked_expression(((values)[i]),interpreter)))));
}

}
}

Jakt::ids::TypeId const value_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((((interpreter)->program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(((args)[static_cast<i64>(0LL)]));
};/*case end*/
default: {
{
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Expected generic instance of Set while materialising an array"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::JaktSet(JaktInternal::OptionalNone(),vals,((this_value).span),type_id,value_type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 27 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::Dictionary<ByteString,Jakt::types::Value> const& captures = __jakt_match_value.captures;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const& checked_params = __jakt_match_value.checked_params;
Jakt::ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
{
NonnullRefPtr<Jakt::types::Scope> const parent_scope = ((((interpreter)->program))->get_scope(((block).scope_id)));
Jakt::ids::ScopeId const inherited_scope_id = ((((interpreter)->program))->create_scope(((block).scope_id),((parent_scope)->can_throw),__jakt_format((StringView::from_string_literal("synthetic({})"sv)),((parent_scope)->debug_name)),((type_id).module),true));
NonnullRefPtr<Jakt::types::Scope> inherited_scope = ((((interpreter)->program))->get_scope(inherited_scope_id));
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> statements = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::DictionaryIterator<ByteString,Jakt::types::Value> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,Jakt::types::Value> capture = (_magic_value.value());
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const value = TRY((Jakt::interpreter::value_to_checked_expression(((capture).template get<1>()),interpreter)));
Jakt::ids::VarId const var_id = ((((((interpreter)->program))->get_module(((type_id).module))))->add_variable(Jakt::types::CheckedVariable::__jakt_create(((capture).template get<0>()),((value)->type()),false,((this_value).span),JaktInternal::OptionalNone(),Jakt::types::CheckedVisibility::Public(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone())));
((statements).push(Jakt::types::CheckedStatement::VarDecl(var_id,value,((this_value).span))));
((((inherited_scope)->comptime_bindings)).set(((capture).template get<0>()),((capture).template get<1>())));
}

}
}

((statements).push_values(((((block).statements)))));
Jakt::types::CheckedBlock const new_block = Jakt::types::CheckedBlock(statements,inherited_scope_id,((block).control_flow),((block).yielded_type),((block).yielded_none));
NonnullRefPtr<Jakt::types::CheckedFunction> const checked_function = Jakt::types::CheckedFunction::__jakt_create((ByteString::from_utf8_without_validation("synthetic_lambda"sv)),((this_value).span),Jakt::types::CheckedVisibility::Public(),return_type_id,JaktInternal::OptionalNone(),checked_params,Jakt::types::FunctionGenerics::__jakt_create(inherited_scope_id,checked_params,DynamicArray<Jakt::types::FunctionGenericParameter>::create_with({}),DynamicArray<JaktInternal::DynamicArray<Jakt::ids::TypeId>>::create_with({})),new_block,can_throw,Jakt::parser::FunctionType::Expression(),Jakt::parser::FunctionLinkage::Internal(),inherited_scope_id,JaktInternal::OptionalNone(),true,JaktInternal::OptionalNone(),false,false,false,false,false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),false,JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default(),false);
Function<ErrorOr<Jakt::ids::FunctionId>(NonnullRefPtr<Jakt::types::CheckedFunction>)> const& register_function = ((((((interpreter)->typecheck_functions))->register_function)));
Jakt::ids::FunctionId const pseudo_function_id = TRY((register_function(checked_function)));
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Function(JaktInternal::OptionalNone(),DynamicArray<Jakt::types::CheckedCapture>::create_with({}),checked_params,can_throw,return_type_id,new_block,((this_value).span),type_id,pseudo_function_id,scope_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((interpreter)->error(__jakt_format((StringView::from_string_literal("Cannot materialise the type {}"sv)),((this_value).impl)),((this_value).span)))));
((((interpreter)->compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
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

ByteString Jakt::interpreter::InterpreterScope::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("InterpreterScope("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("bindings: {}, ", bindings);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("parent: {}, ", parent);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("type_bindings: {}, ", type_bindings);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("defers: {}, ", defers);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("runtime_scope_id: {}", runtime_scope_id);
}
builder.append(")"sv);return builder.to_string(); }
NonnullRefPtr<Jakt::interpreter::InterpreterScope> Jakt::interpreter::InterpreterScope::create(JaktInternal::Dictionary<ByteString,Jakt::types::Value> const bindings,JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> const parent,JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const type_bindings,NonnullRefPtr<Jakt::compiler::Compiler> const compiler,JaktInternal::Optional<Jakt::ids::ScopeId> const runtime_scope_id) {
{
return Jakt::interpreter::InterpreterScope::__jakt_create(bindings,parent,type_bindings,DynamicArray<Jakt::interpreter::Deferred>::create_with({}),compiler,runtime_scope_id);
}
}

NonnullRefPtr<Jakt::interpreter::InterpreterScope> Jakt::interpreter::InterpreterScope::from_runtime_scope(Jakt::ids::ScopeId const scope_id,NonnullRefPtr<Jakt::types::CheckedProgram> const program,JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> const parent) {
{
JaktInternal::Dictionary<ByteString,Jakt::types::Value> bindings = Dictionary<ByteString, Jakt::types::Value>::create_with_entries({});
JaktInternal::Optional<Jakt::ids::ScopeId> current_id = scope_id;
while (((current_id).has_value())){
NonnullRefPtr<Jakt::types::Scope> const scope = ((program)->get_scope((current_id.value())));
{
JaktInternal::DictionaryIterator<ByteString,Jakt::types::Value> _magic = ((((scope)->comptime_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,Jakt::types::Value> pair = (_magic_value.value());
{
if (((bindings).contains(((pair).template get<0>())))){
continue;
}
((bindings).set(((pair).template get<0>()),((pair).template get<1>())));
}

}
}

{
JaktInternal::ArrayIterator<Jakt::types::ResolutionMixin> _magic = ((((scope)->resolution_mixins)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::ResolutionMixin> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::ResolutionMixin mixin = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::Scope> const mixin_scope = ((program)->get_scope(((mixin).scope_id)));
{
JaktInternal::DictionaryIterator<ByteString,Jakt::types::Value> _magic = ((((mixin_scope)->comptime_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,Jakt::types::Value> pair = (_magic_value.value());
{
if (((bindings).contains(((pair).template get<0>())))){
continue;
}
((bindings).set(((pair).template get<0>()),((pair).template get<1>())));
}

}
}

}

}
}

(current_id = ((scope)->parent));
}
return Jakt::interpreter::InterpreterScope::__jakt_create(bindings,parent,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),DynamicArray<Jakt::interpreter::Deferred>::create_with({}),((program)->compiler),scope_id);
}
}

ErrorOr<Jakt::types::Value> Jakt::interpreter::InterpreterScope::must_get(ByteString const name) const {
{
if (((((*this).bindings)).contains(name))){
return ((((*this).bindings))[name]);
}
JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> scope = ((*this).parent);
while (((scope).has_value())){
if ((((((scope.value()))->bindings)).contains(name))){
return (((((scope.value()))->bindings))[name]);
}
(scope = (((scope.value()))->parent));
}
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Could not find binding"sv))));
}
}

ErrorOr<void> Jakt::interpreter::InterpreterScope::set(ByteString const name,Jakt::types::Value const value) {
{
if (((((*this).bindings)).contains(name))){
((*this).bindings).set(name, value);
return {};
}
JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> scope = ((*this).parent);
while (((scope).has_value())){
if ((((((scope.value()))->bindings)).contains(name))){
(((scope.value()))->bindings).set(name, value);
return {};
}
(scope = (((scope.value()))->parent));
}
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Could not find binding"sv))));
}
return {};
}

JaktInternal::Dictionary<ByteString,Jakt::types::Value> Jakt::interpreter::InterpreterScope::all_bindings() const {
{
JaktInternal::Dictionary<ByteString,Jakt::types::Value> bindings = Dictionary<ByteString, Jakt::types::Value>::create_with_entries({});
JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> scope = static_cast<JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>>>(*this);
while (((scope).has_value())){
{
JaktInternal::DictionaryIterator<ByteString,Jakt::types::Value> _magic = (((((scope.value()))->bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,Jakt::types::Value> pair = (_magic_value.value());
{
if (((bindings).contains(((pair).template get<0>())))){
continue;
}
((bindings).set(((pair).template get<0>()),((pair).template get<1>())));
}

}
}

(scope = (((scope.value()))->parent));
}
return bindings;
}
}

Jakt::ids::TypeId Jakt::interpreter::InterpreterScope::map_type(Jakt::ids::TypeId const id) const {
{
if (((((*this).type_bindings)).contains(id))){
return ((((*this).type_bindings))[id]);
}
JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> scope = ((*this).parent);
while (((scope).has_value())){
if ((((((scope.value()))->type_bindings)).contains(id))){
return (((((scope.value()))->type_bindings))[id]);
}
(scope = (((scope.value()))->parent));
}
return id;
}
}

void Jakt::interpreter::InterpreterScope::type_map_for_substitution_helper(JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId>& map) const {
{
if (((((*this).parent)).has_value())){
(((((*this).parent).value()))->type_map_for_substitution_helper(map));
}
{
JaktInternal::DictionaryIterator<Jakt::ids::TypeId,Jakt::ids::TypeId> _magic = ((((*this).type_bindings)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<Jakt::ids::TypeId,Jakt::ids::TypeId> pair = (_magic_value.value());
{
((((map))).set(((pair).template get<0>()),((pair).template get<1>())));
}

}
}

}
}

Jakt::types::GenericInferences Jakt::interpreter::InterpreterScope::type_map_for_substitution() const {
{
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> map = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
((*this).type_map_for_substitution_helper(((map))));
return Jakt::types::GenericInferences(map);
}
}

ErrorOr<void> Jakt::interpreter::InterpreterScope::perform_defers(NonnullRefPtr<Jakt::interpreter::Interpreter> interpreter,Jakt::utility::Span const span) {
{
while ((!(((((*this).defers)).is_empty())))){
JaktInternal::Optional<Jakt::interpreter::Deferred> const deferred = ((((*this).defers)).pop());
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<void>>{
auto&& __jakt_match_variant = (deferred.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((interpreter)->execute_expression(expr,*this)))));
};/*case end*/
case 1 /* Statement */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Statement;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& statement = __jakt_match_value.value;
return JaktInternal::ExplicitValue(TRY((((interpreter)->execute_statement(statement,*this,span)))));
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
return {};
}

void Jakt::interpreter::InterpreterScope::defer_expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr) {
{
((((*this).defers)).push(Jakt::interpreter::Deferred::Expression(expr)));
}
}

void Jakt::interpreter::InterpreterScope::defer_statement(NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement) {
{
((((*this).defers)).push(Jakt::interpreter::Deferred::Statement(statement)));
}
}

Jakt::interpreter::InterpreterScope::InterpreterScope(JaktInternal::Dictionary<ByteString,Jakt::types::Value> a_bindings, JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> a_parent, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> a_type_bindings, JaktInternal::DynamicArray<Jakt::interpreter::Deferred> a_defers, NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, JaktInternal::Optional<Jakt::ids::ScopeId> a_runtime_scope_id): bindings(move(a_bindings)), parent(move(a_parent)), type_bindings(move(a_type_bindings)), defers(move(a_defers)), compiler(move(a_compiler)), runtime_scope_id(move(a_runtime_scope_id)){}
NonnullRefPtr<InterpreterScope> Jakt::interpreter::InterpreterScope::__jakt_create(JaktInternal::Dictionary<ByteString,Jakt::types::Value> bindings, JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> parent, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> type_bindings, JaktInternal::DynamicArray<Jakt::interpreter::Deferred> defers, NonnullRefPtr<Jakt::compiler::Compiler> compiler, JaktInternal::Optional<Jakt::ids::ScopeId> runtime_scope_id) { auto o = adopt_ref(*new InterpreterScope (move(bindings), move(parent), move(type_bindings), move(defers), move(compiler), move(runtime_scope_id))); return o; }
ByteString Jakt::interpreter::Interpreter::debug_description() const { auto builder = ByteStringBuilder::create();builder.append("Interpreter("sv);{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("compiler: {}, ", *compiler);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("program: {}, ", *program);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("spans: {}, ", spans);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("reflected_type_cache: {}, ", reflected_type_cache);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("seen_reflected_types: {}, ", seen_reflected_types);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("current_function_id: {}, ", current_function_id);
JaktInternal::PrettyPrint::must_output_indentation(builder);
builder.appendff("typecheck_functions: {}", *typecheck_functions);
}
builder.append(")"sv);return builder.to_string(); }
NonnullRefPtr<Jakt::interpreter::Interpreter> Jakt::interpreter::Interpreter::create(NonnullRefPtr<Jakt::compiler::Compiler> const compiler,NonnullRefPtr<Jakt::types::CheckedProgram> const program,NonnullRefPtr<Jakt::types::TypecheckFunctions> const typecheck_functions,JaktInternal::DynamicArray<Jakt::utility::Span> const spans) {
{
return Jakt::interpreter::Interpreter::__jakt_create(compiler,program,spans,Dictionary<Jakt::ids::TypeId, Jakt::types::Value>::create_with_entries({}),Set<Jakt::ids::TypeId>::create_with_values({}),JaktInternal::OptionalNone(),typecheck_functions);
}
}

void Jakt::interpreter::Interpreter::enter_span(Jakt::utility::Span const span) {
{
((((*this).spans)).push(span));
}
}

void Jakt::interpreter::Interpreter::leave_span() {
{
JaktInternal::Optional<Jakt::utility::Span> const dummy = ((((*this).spans)).pop());
}
}

ErrorOr<Jakt::types::CheckedBlock> Jakt::interpreter::Interpreter::perform_final_interpretation_pass(Jakt::types::CheckedBlock const block,JaktInternal::Optional<Jakt::ids::ScopeId> const runtime_scope,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope,JaktInternal::Optional<Jakt::ids::FunctionId> const function_id) {
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> statements = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> statement = (_magic_value.value());
{
NonnullRefPtr<typename Jakt::types::CheckedStatement> const new_statement = TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))));
((statements).push(new_statement));
}

}
}

return Jakt::types::CheckedBlock(statements,((block).scope_id),((block).control_flow),((block).yielded_type),((block).yielded_none));
}
}

ErrorOr<Jakt::types::CheckedBlock> Jakt::interpreter::Interpreter::perform_final_interpretation_pass(Jakt::parser::ParsedBlock const block,Jakt::ids::ScopeId const runtime_scope,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope,JaktInternal::Optional<Jakt::ids::FunctionId> const function_id) {
{
NonnullRefPtr<Jakt::types::Scope> rscope = ((((*this).program))->get_scope(runtime_scope));
{
JaktInternal::DictionaryIterator<ByteString,Jakt::types::Value> _magic = ((((scope)->all_bindings())).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,Jakt::types::Value>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,Jakt::types::Value> name__value__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,Jakt::types::Value> const jakt__name__value__ = name__value__;
ByteString const name = ((jakt__name__value__).template get<0>());
Jakt::types::Value const value = ((jakt__name__value__).template get<1>());

((((rscope)->comptime_bindings)).set(name,value));
}

}
}

return ((((*this).perform_final_interpretation_pass(TRY((((*this).typecheck_block(block,runtime_scope,function_id)))),runtime_scope,scope,function_id))));
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>> Jakt::interpreter::Interpreter::perform_final_interpretation_pass(NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope,JaktInternal::Optional<Jakt::ids::FunctionId> const function_id) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedStatement>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::Expression(TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),span));
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& statement = __jakt_match_value.statement;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::Defer(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id)))),span));
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename Jakt::types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::DestructuringAssignment(vars,TRY((((*this).perform_final_interpretation_pass(var_decl,scope,function_id)))),span));
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;Jakt::ids::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& init = __jakt_match_value.init;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::VarDecl(var_id,TRY((((*this).perform_final_interpretation_expr_pass(init,scope,function_id)))),span));
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const new_condition = TRY((((*this).perform_final_interpretation_expr_pass(condition,scope,function_id))));
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> then_statements = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = ((((then_block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> statement = (_magic_value.value());
{
((then_statements).push(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))))));
}

}
}

Jakt::types::CheckedBlock const new_then_block = Jakt::types::CheckedBlock(then_statements,((then_block).scope_id),((then_block).control_flow),((then_block).yielded_type),((then_block).yielded_none));
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const new_else_statement = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>>> {
auto __jakt_enum_value = (((else_statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>>>(TRY((((*this).perform_final_interpretation_pass((else_statement.value()),scope,function_id))))));
}
else {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(Jakt::types::CheckedStatement::If(new_condition,new_then_block,new_else_statement,span));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> statements = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> statement = (_magic_value.value());
{
((statements).push(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))))));
}

}
}

Jakt::types::CheckedBlock const new_block = Jakt::types::CheckedBlock(statements,((block).scope_id),((block).control_flow),((block).yielded_type),((block).yielded_none));
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(Jakt::types::CheckedStatement::Block(new_block,span));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> statements = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> statement = (_magic_value.value());
{
((statements).push(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))))));
}

}
}

Jakt::types::CheckedBlock const new_block = Jakt::types::CheckedBlock(statements,((block).scope_id),((block).control_flow),((block).yielded_type),((block).yielded_none));
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(Jakt::types::CheckedStatement::Loop(new_block,span));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<typename Jakt::types::CheckedExpression> const new_condition = TRY((((*this).perform_final_interpretation_expr_pass(condition,scope,function_id))));
JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> statements = DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = ((((block).statements)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> statement = (_magic_value.value());
{
((statements).push(TRY((((*this).perform_final_interpretation_pass(statement,scope,function_id))))));
}

}
}

Jakt::types::CheckedBlock const new_block = Jakt::types::CheckedBlock(statements,((block).scope_id),((block).control_flow),((block).yielded_type),((block).yielded_none));
return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedStatement>>(Jakt::types::CheckedStatement::While(new_condition,new_block,span));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& val = __jakt_match_value.val;
JaktInternal::Optional<Jakt::utility::Span> const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedStatement>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>>> {
auto __jakt_enum_value = (((val).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::Return(TRY((((*this).perform_final_interpretation_expr_pass((val.value()),scope,function_id)))),span));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(statement);
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 9 /* Break */: {
return JaktInternal::ExplicitValue(statement);
};/*case end*/
case 10 /* Continue */: {
return JaktInternal::ExplicitValue(statement);
};/*case end*/
case 13 /* InlineCpp */: {
return JaktInternal::ExplicitValue(statement);
};/*case end*/
case 14 /* Garbage */: {
return JaktInternal::ExplicitValue(statement);
};/*case end*/
case 11 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::Throw(TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),span));
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedStatement>,ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedStatement>>> {
auto __jakt_enum_value = (((expr).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::CheckedStatement::Yield(TRY((((*this).perform_final_interpretation_expr_pass((expr.value()),scope,function_id)))),span));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(statement);
}
VERIFY_NOT_REACHED();
}());
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

ErrorOr<Jakt::types::CheckedBlock> Jakt::interpreter::Interpreter::typecheck_block(Jakt::parser::ParsedBlock const block,Jakt::ids::ScopeId const scope,JaktInternal::Optional<Jakt::ids::FunctionId> const function_id) {
{
return ((Jakt::interpreter::Interpreter::invoke_typecheck_block(((((((*this).typecheck_functions))->block))),block,scope,function_id)));
}
}

ErrorOr<Jakt::types::CheckedBlock> Jakt::interpreter::Interpreter::invoke_typecheck_block(Function<ErrorOr<Jakt::types::CheckedBlock>(Jakt::parser::ParsedBlock, Jakt::ids::ScopeId, Jakt::types::SafetyMode, JaktInternal::Optional<Jakt::ids::TypeId>, JaktInternal::Optional<Jakt::ids::FunctionId>)> const& function,Jakt::parser::ParsedBlock const block,Jakt::ids::ScopeId const parent_scope_id,JaktInternal::Optional<Jakt::ids::FunctionId> const function_id) {
{
return ((function(block,parent_scope_id,Jakt::types::SafetyMode::Safe(),JaktInternal::OptionalNone(),function_id)));
}
}

ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>> Jakt::interpreter::Interpreter::perform_final_interpretation_expr_pass(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope,JaktInternal::Optional<Jakt::ids::FunctionId> const function_id) {
{
if (((expr)->__jakt_init_index() == 6 /* UnaryOp */)){
Jakt::types::CheckedUnaryOperator const op = (expr)->as.UnaryOp.op;
if (((op).__jakt_init_index() == 11 /* TypeCast */)){
warnln((StringView::from_string_literal("{0:c}[31mFixup{0:c}[0m {1}"sv)),static_cast<i64>(27LL),expr);
}
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::CheckedExpression>, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* ComptimeIndex */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ComptimeIndex;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& index = __jakt_match_value.index;
bool const& is_optional = __jakt_match_value.is_optional;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::interpreter::StatementResult const index_result = TRY((((*this).execute_expression(index,scope))));
Jakt::types::NumericOrStringValue const index_constant = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::NumericOrStringValue, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = index_result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::NumericOrStringValue, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::StringValue(val));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::UnsignedNumericValue((static_cast<u64>((val)))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::UnsignedNumericValue((infallible_integer_cast<u64>((val)))));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::SignedNumericValue((infallible_integer_cast<i64>((val)))));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& val = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::NumericOrStringValue::SignedNumericValue((static_cast<i64>((val)))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Index expression evaluation failed: expected numeric or string type, found {}"sv)),((value).impl)),span))));
return Jakt::types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Index expression evaluation returned an invalid object {}"sv)),index_result),span))));
return Jakt::types::CheckedExpression::Garbage(JaktInternal::OptionalNone(),span,Jakt::types::builtin(Jakt::types::BuiltinType::Void()));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = index_constant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* StringValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringValue;ByteString const& field = __jakt_match_value.value;
{
Jakt::ids::TypeId const checked_expr_type_id = ((scope)->map_type(((expr)->type())));
NonnullRefPtr<typename Jakt::types::Type> const checked_expr_type = ((((*this).program))->get_type(checked_expr_type_id));
Jakt::ids::StructId const optional_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Optional"sv))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *checked_expr_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& id = __jakt_match_value.id;
JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
Jakt::ids::TypeId type_id = checked_expr_type_id;
if (is_optional){
if ((!(((id).equals(optional_struct_id))))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Optional chaining is only allowed on optional types"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid operation"sv))));
}
(type_id = ((args)[static_cast<i64>(0LL)]));
}
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
Jakt::types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> member_id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = ((((*this).program))->get_variable(((member_id)->variable_id)));
if (((((member)->name)) == (field))){
Jakt::ids::TypeId resolved_type_id = ((scope)->map_type(((member)->type_id)));
if (is_optional){
(resolved_type_id = ((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({resolved_type_id})))));
}
return Jakt::types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),expr,field,((member_id)->variable_id),span,is_optional,resolved_type_id);
}
}

}
}

TRY((((*this).error(__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid operation"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> member_id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = ((((*this).program))->get_variable(((member_id)->variable_id)));
if (((((member)->name)) == (field))){
Jakt::ids::TypeId resolved_type_id = ((scope)->map_type(((member)->type_id)));
if (is_optional){
(resolved_type_id = ((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),optional_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({resolved_type_id})))));
}
return Jakt::types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),expr,field,((member_id)->variable_id),span,is_optional,resolved_type_id);
}
}

}
}

TRY((((*this).error(__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid operation"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Member field access on value of non-struct type ‘{}’"sv)),TRY((((((*this).program))->type_name(checked_expr_type_id,false))))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid operation"sv))));
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
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
if (is_optional){
TRY((((*this).error((ByteString::from_utf8_without_validation("Optional chaining is not allowed on non-optional types"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid operation"sv))));
}
Jakt::types::CheckedStruct const structure = ((((*this).program))->get_struct(struct_id));
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((structure).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> member_id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const member = ((((*this).program))->get_variable(((member_id)->variable_id)));
if (((((member)->name)) == (field))){
Jakt::ids::TypeId const resolved_type_id = ((scope)->map_type(((member)->type_id)));
return Jakt::types::CheckedExpression::IndexedStruct(JaktInternal::OptionalNone(),expr,field,((member_id)->variable_id),span,is_optional,resolved_type_id);
}
}

}
}

TRY((((*this).error(__jakt_format((StringView::from_string_literal("unknown member of struct: {}.{}"sv)),((structure).name),field),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid operation"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Member field access on value of non-struct type ‘{}’"sv)),TRY((((((*this).program))->type_name(checked_expr_type_id,false))))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid operation"sv))));
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
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* UnsignedNumericValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnsignedNumericValue;u64 const& val = __jakt_match_value.value;
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Unimplemented expression"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* SignedNumericValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.SignedNumericValue;i64 const& val = __jakt_match_value.value;
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Unimplemented expression"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
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
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedUnaryOperator const& op = __jakt_match_value.op;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::UnaryOp(JaktInternal::OptionalNone(),TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedUnaryOperator, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;Jakt::types::CheckedTypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedUnaryOperator::TypeCast(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::CheckedTypeCast, ErrorOr<NonnullRefPtr<typename Jakt::types::CheckedExpression>>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Fallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fallible;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedTypeCast::Fallible(((scope)->map_type(type_id))));
};/*case end*/
case 1 /* Infallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Infallible;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedTypeCast::Infallible(((scope)->map_type(type_id))));
};/*case end*/
case 2 /* Identity */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identity;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::CheckedTypeCast::Identity(((scope)->map_type(type_id))));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
default: {
return JaktInternal::ExplicitValue(op);
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span,((scope)->map_type(type_id))));
};/*case end*/
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
Jakt::types::CheckedBinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(Jakt::types::CheckedExpression::BinaryOp(JaktInternal::OptionalNone(),TRY((((*this).perform_final_interpretation_expr_pass(lhs,scope,function_id)))),op,TRY((((*this).perform_final_interpretation_expr_pass(rhs,scope,function_id)))),span,((scope)->map_type(type_id))));
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> new_args = DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> arg = (_magic_value.value());
{
((new_args).push((Tuple{((arg).template get<0>()), TRY((((*this).perform_final_interpretation_expr_pass(((arg).template get<1>()),scope,function_id))))})));
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::Call(JaktInternal::OptionalNone(),Jakt::types::CheckedCall(((call).namespace_),((call).name),new_args,((call).type_args),((call).function_id),((call).return_type),((call).callee_throws),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default()),span,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedCall const& call = __jakt_match_value.call;
Jakt::utility::Span const& span = __jakt_match_value.span;
bool const& is_optional = __jakt_match_value.is_optional;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> new_args = DynamicArray<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> arg = (_magic_value.value());
{
((new_args).push((Tuple{((arg).template get<0>()), TRY((((*this).perform_final_interpretation_expr_pass(((arg).template get<1>()),scope,function_id))))})));
}

}
}

return JaktInternal::ExplicitValue<NonnullRefPtr<typename Jakt::types::CheckedExpression>>(Jakt::types::CheckedExpression::MethodCall(JaktInternal::OptionalNone(),TRY((((*this).perform_final_interpretation_expr_pass(expr,scope,function_id)))),Jakt::types::CheckedCall(((call).namespace_),((call).name),new_args,((call).type_args),((call).function_id),((call).return_type),((call).callee_throws),JaktInternal::OptionalNone(),Jakt::parser::InlineState::Default()),span,is_optional,type_id));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(expr);
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

bool Jakt::interpreter::Interpreter::get_prelude_function(Jakt::ids::ScopeId const scope_id) const {
{
Jakt::ids::ScopeId current_scope_id = scope_id;
Jakt::ids::ScopeId const prelude_scope_id = ((((*this).program))->prelude_scope_id());
for (;;){
if (((current_scope_id).equals(prelude_scope_id))){
return true;
}
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(current_scope_id));
if (((((scope)->parent)).has_value())){
(current_scope_id = (((scope)->parent).value()));
continue;
}
return false;
}
}
}

Jakt::ids::TypeId Jakt::interpreter::Interpreter::find_or_add_type_id(NonnullRefPtr<typename Jakt::types::Type> const type) {
{
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::Module>> _magic = ((((((*this).program))->modules)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::Module>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::Module> module = (_magic_value.value());
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
return Jakt::ids::TypeId(((module)->id),id);
}
}

}
}

}

}
}

((((((((((*this).program))->modules))[static_cast<i64>(0LL)]))->types)).push(type));
return Jakt::ids::TypeId(Jakt::ids::ModuleId(static_cast<size_t>(0ULL)),JaktInternal::checked_sub(((((((((((*this).program))->modules))[static_cast<i64>(0LL)]))->types)).size()),static_cast<size_t>(1ULL)));
}
}

ErrorOr<Jakt::interpreter::StatementResult> Jakt::interpreter::Interpreter::call_prelude_function(ByteString const prelude_function,JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> const namespace_,JaktInternal::Optional<Jakt::types::Value> const this_argument,JaktInternal::DynamicArray<Jakt::types::Value> const arguments,Jakt::utility::Span const call_span,JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> const type_bindings,JaktInternal::Optional<Jakt::ids::ScopeId> const runtime_scope_id) {
{
if (((((namespace_).size())) != (static_cast<size_t>(1ULL)))){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "format"sv) {
{
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Expected string as first argument to format, got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(TRY((Jakt::types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))))),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "println"sv) {
{
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("println expects a string as its first argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const formatted_string = TRY((Jakt::types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "println"sv) {
return ({outln((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "eprintln"sv) {
return ({warnln((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "print"sv) {
return ({out((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else {
return ({warn((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "eprintln"sv) {
{
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("println expects a string as its first argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const formatted_string = TRY((Jakt::types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "println"sv) {
return ({outln((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "eprintln"sv) {
return ({warnln((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "print"sv) {
return ({out((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else {
return ({warn((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "print"sv) {
{
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("println expects a string as its first argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const formatted_string = TRY((Jakt::types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "println"sv) {
return ({outln((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "eprintln"sv) {
return ({warnln((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "print"sv) {
return ({out((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else {
return ({warn((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "eprint"sv) {
{
ByteString const format_string = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("println expects a string as its first argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
ByteString const formatted_string = TRY((Jakt::types::comptime_format_impl(format_string,((arguments)[(JaktInternal::Range<i64>{static_cast<i64>(static_cast<i64>(1LL)),static_cast<i64>(9223372036854775807LL)})]),((((*this).program))))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "println"sv) {
return ({outln((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "eprintln"sv) {
return ({warnln((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "print"sv) {
return ({out((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
else {
return ({warn((StringView::from_string_literal("{}"sv)),formatted_string);}), JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "as_saturated"sv) {
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = ((((*this).program))->get_function((((TRY((((((*this).program))->find_functions_with_name_in_scope(((((*this).program))->prelude_scope_id()),(ByteString::from_utf8_without_validation("as_saturated"sv)),false,JaktInternal::OptionalNone())))).value()))[static_cast<i64>(0LL)])));
JaktInternal::Optional<Jakt::ids::TypeId> const output_type_id = ((type_bindings).get(((((((((function)->generics))->params))[static_cast<i64>(0LL)])).type_id())));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(TRY((Jakt::interpreter::cast_value_to_type(((arguments)[static_cast<i64>(0LL)]),(output_type_id.value()),*this,true)))));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "unchecked_mul"sv) {
{
Jakt::types::Value const lhs_value = ((arguments)[static_cast<i64>(0LL)]);
Jakt::types::Value const rhs_value = ((arguments)[static_cast<i64>(1LL)]);
Jakt::utility::Span const span = call_span;
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8(Jakt::unchecked_mul<u8>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16(Jakt::unchecked_mul<u16>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32(Jakt::unchecked_mul<u32>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64(Jakt::unchecked_mul<u64>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8(Jakt::unchecked_mul<i8>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16(Jakt::unchecked_mul<i16>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32(Jakt::unchecked_mul<i32>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64(Jakt::unchecked_mul<i64>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F32(Jakt::unchecked_mul<f32>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F64(Jakt::unchecked_mul<f64>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize(Jakt::unchecked_mul<size_t>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "unchecked_add"sv) {
{
Jakt::types::Value const lhs_value = ((arguments)[static_cast<i64>(0LL)]);
Jakt::types::Value const rhs_value = ((arguments)[static_cast<i64>(1LL)]);
Jakt::utility::Span const span = call_span;
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8(Jakt::unchecked_add<u8>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16(Jakt::unchecked_add<u16>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32(Jakt::unchecked_add<u32>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64(Jakt::unchecked_add<u64>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8(Jakt::unchecked_add<i8>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16(Jakt::unchecked_add<i16>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32(Jakt::unchecked_add<i32>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64(Jakt::unchecked_add<i64>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F32(Jakt::unchecked_add<f32>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F64(Jakt::unchecked_add<f64>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize(Jakt::unchecked_add<size_t>(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "abort"sv) {
{
Jakt::abort();
}
}
else if (__jakt_enum_value == "Set"sv) {
{
if (((((type_bindings).size())) != (static_cast<size_t>(1ULL)))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Set constructor expects one generic argument"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
Jakt::ids::StructId const set_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Set"sv))))));
Jakt::ids::TypeId const type_id = ((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),set_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({(((type_bindings).get(((((type_bindings).keys()))[static_cast<i64>(0LL)]))).value())}))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktSet(DynamicArray<Jakt::types::Value>::create_with({}),type_id),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "Dictionary"sv) {
{
if (((((type_bindings).size())) != (static_cast<size_t>(2ULL)))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Dictionary constructor expects two generic argumenst"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
Jakt::ids::StructId const dictionary_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Dictionary"sv))))));
Jakt::ids::TypeId const type_id = ((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),dictionary_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({(((type_bindings).get(((((type_bindings).keys()))[static_cast<i64>(0LL)]))).value()), (((type_bindings).get(((((type_bindings).keys()))[static_cast<i64>(1LL)]))).value())}))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktDictionary(DynamicArray<Jakt::types::Value>::create_with({}),DynamicArray<Jakt::types::Value>::create_with({}),type_id),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "from_string_literal"sv) {
{
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(((arguments)[static_cast<i64>(0LL)])));
}
VERIFY_NOT_REACHED();
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function {}::{} is not implemented yet"sv)),namespace_,prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((((namespace_)[static_cast<i64>(0LL)])).name));
if (__jakt_enum_value == "Error"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "from_errno"sv) {
{
Jakt::types::Value const err = ((arguments)[static_cast<i64>(0LL)]);
Jakt::ids::StructId const error_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Error"sv))))));
Jakt::types::CheckedStruct const error_struct = ((((*this).program))->get_struct(error_struct_id));
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((error_struct).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const constructors = ((((scope)->functions)).get((ByteString::from_utf8_without_validation("from_errno"sv))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({err}),error_struct_id,(((constructors.value()))[static_cast<i64>(0LL)])),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "from_string_literal"sv) {
{
Jakt::types::Value const err = ((arguments)[static_cast<i64>(0LL)]);
Jakt::ids::StructId const error_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Error"sv))))));
Jakt::types::CheckedStruct const error_struct = ((((*this).program))->get_struct(error_struct_id));
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((error_struct).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const constructors = ((((scope)->functions)).get((ByteString::from_utf8_without_validation("from_string_literal"sv))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({err}),error_struct_id,(((constructors.value()))[static_cast<i64>(0LL)])),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "code"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& code = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::I32(code),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Error should have `i32` as its code, but got {}"sv)),((((fields)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `Error::code` expects an Error as its this argument, but got {}"sv)),(((this_argument.value())).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `Error::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "File"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "open_for_reading"sv) {
{
ByteString const requested_path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::{}` expects a string as its first argument, but got {}"sv)),prelude_function,((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::jakt__path::Path const path = (((((((((((*this).program))->compiler))->get_file_path(((call_span).file_id))).value())).parent())).join(requested_path));
Jakt::types::Value const path_value = Jakt::types::Value(Jakt::types::ValueImpl::JaktString(((path).to_string())),call_span);
if ((!(((path).exists())))){
return Jakt::interpreter::StatementResult::Throw(TRY((((*this).error_value(__jakt_format((StringView::from_string_literal("Could not find file at path {}"sv)),((path).to_string())),call_span)))));
}
Jakt::ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("File"sv))))));
Jakt::types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((file_struct).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const constructors = ((((scope)->functions)).get((ByteString::from_utf8_without_validation("open_for_reading"sv))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({path_value}),file_struct_id,(((constructors.value()))[static_cast<i64>(0LL)])),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "open_for_writing"sv) {
{
ByteString const requested_path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::{}` expects a string as its first argument, but got {}"sv)),prelude_function,((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::jakt__path::Path const path = (((((((((((*this).program))->compiler))->get_file_path(((call_span).file_id))).value())).parent())).join(requested_path));
Jakt::types::Value const path_value = Jakt::types::Value(Jakt::types::ValueImpl::JaktString(((path).to_string())),call_span);
if ((!(((path).exists())))){
return Jakt::interpreter::StatementResult::Throw(TRY((((*this).error_value(__jakt_format((StringView::from_string_literal("Could not find file at path {}"sv)),((path).to_string())),call_span)))));
}
Jakt::ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("File"sv))))));
Jakt::types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((file_struct).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const constructor = ((((scope)->functions)).get((ByteString::from_utf8_without_validation("open_for_writing"sv))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({path_value}),file_struct_id,(((constructor.value()))[static_cast<i64>(0LL)])),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "read_all"sv) {
{
ByteString const path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("invalid type for File::read_all"sv)));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::read_all` expects a `File` as its this argument, but got {}"sv)),(((this_argument.value())).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("File"sv))))));
Jakt::types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((file_struct).scope_id)));
Jakt::ids::FunctionId const open_for_reading = (((((((scope)->functions)).get((ByteString::from_utf8_without_validation("open_for_reading"sv)))).value()))[static_cast<i64>(0LL)]);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
if (((!(((constructor).has_value()))) || (!((((constructor.value())).equals(open_for_reading)))))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Cannot read from a file not opened for reading"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected struct as this argument"sv)));
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
NonnullRefPtr<File> file = TRY((File::open_for_reading(path)));
JaktInternal::DynamicArray<Jakt::types::Value> result_values = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<u8> _magic = ((TRY((((file)->read_all())))).iterator());
for (;;){
JaktInternal::Optional<u8> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
u8 byte = (_magic_value.value());
{
((result_values).push(Jakt::types::Value(Jakt::types::ValueImpl::U8(byte),call_span)));
}

}
}

Jakt::ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(result_values,((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),array_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({Jakt::types::builtin(Jakt::types::BuiltinType::U8())}))))),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "read"sv) {
{
ByteString const path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("invalid type for File::read"sv)));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::read` expects a `File` as its this argument, but got {}"sv)),(((this_argument.value())).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("File"sv))))));
Jakt::types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((file_struct).scope_id)));
Jakt::ids::FunctionId const open_for_reading = (((((((scope)->functions)).get((ByteString::from_utf8_without_validation("open_for_reading"sv)))).value()))[static_cast<i64>(0LL)]);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
if (((!(((constructor).has_value()))) || (!((((constructor.value())).equals(open_for_reading)))))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Cannot read from a file not opened for reading"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected struct as this argument"sv)));
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
NonnullRefPtr<File> file = TRY((File::open_for_reading(path)));
JaktInternal::DynamicArray<Jakt::types::Value> values_buffer = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::Value>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(values);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::read` expects a `[u8]` as its argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<u8> byte_buffer = DynamicArray<u8>::filled(((values_buffer).size()), static_cast<u8>(0));
size_t const bytes_read = TRY((((file)->read(byte_buffer))));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((byte_buffer).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
(((values_buffer)[i]) = Jakt::types::Value(Jakt::types::ValueImpl::U8(((byte_buffer)[i])),call_span));
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(bytes_read),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "exists"sv) {
{
ByteString const requested_path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::{}` expects a string as its first argument, but got {}"sv)),prelude_function,((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::jakt__path::Path const path = (((((((((((*this).program))->compiler))->get_file_path(((call_span).file_id))).value())).parent())).join(requested_path));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((path).exists())),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "write"sv) {
{
ByteString const path = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("invalid type for File::write"sv)));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::write` expects a `File` as its this argument, but got {}"sv)),(((this_argument.value())).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::StructId const file_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("File"sv))))));
Jakt::types::CheckedStruct const file_struct = ((((*this).program))->get_struct(file_struct_id));
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((file_struct).scope_id)));
Jakt::ids::FunctionId const open_for_writing = (((((((scope)->functions)).get((ByteString::from_utf8_without_validation("open_for_writing"sv)))).value()))[static_cast<i64>(0LL)]);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
if (((!(((constructor).has_value()))) || (!((((constructor.value())).equals(open_for_writing)))))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Cannot write to a file not opened for writing"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected struct as this argument"sv)));
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
NonnullRefPtr<File> file = TRY((File::open_for_writing(path)));
JaktInternal::DynamicArray<Jakt::types::Value> data_values = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::Value>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(values);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::write` expects a `[u8]` as its argument, but got {}"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<u8> data = DynamicArray<u8>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = ((data_values).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::Value val = (_magic_value.value());
{
((data).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u8, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((val).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected byte"sv)));
}
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
})));
}

}
}

size_t const bytes_written = TRY((((file)->write(data))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(bytes_written),call_span)));
}
VERIFY_NOT_REACHED();
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `File::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "StringBuilder"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "create"sv) {
{
Jakt::ids::StructId const string_builder_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("StringBuilder"sv))))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::JaktString((ByteString::from_utf8_without_validation(""sv))),call_span)}),string_builder_struct_id,JaktInternal::OptionalNone()),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "append"sv) {
{
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString> fields_current_string_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{fields, value}));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of prelude StringBuilder"sv)));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid call"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> fields = ((fields_current_string_).template get<0>());
ByteString current_string = ((fields_current_string_).template get<1>());

ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append(current_string));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "append"sv) {
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid use of StringBuilder::append({})"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "append_escaped_for_json"sv) {
return ({((builder).append_escaped_for_json(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid use of StringBuilder::append_escaped_for_json()"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "append_code_point"sv) {
return ({((builder).append_code_point(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u32, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid use of StringBuilder::append_code_point()"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));}), JaktInternal::ExplicitValue<void>();
}
else {
{
Jakt::abort();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((fields)[static_cast<i64>(0LL)]) = Jakt::types::Value(Jakt::types::ValueImpl::JaktString(((builder).to_string())),call_span));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "append_code_point"sv) {
{
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString> fields_current_string_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{fields, value}));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of prelude StringBuilder"sv)));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid call"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> fields = ((fields_current_string_).template get<0>());
ByteString current_string = ((fields_current_string_).template get<1>());

ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append(current_string));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "append"sv) {
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid use of StringBuilder::append({})"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "append_escaped_for_json"sv) {
return ({((builder).append_escaped_for_json(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid use of StringBuilder::append_escaped_for_json()"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "append_code_point"sv) {
return ({((builder).append_code_point(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u32, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid use of StringBuilder::append_code_point()"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));}), JaktInternal::ExplicitValue<void>();
}
else {
{
Jakt::abort();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((fields)[static_cast<i64>(0LL)]) = Jakt::types::Value(Jakt::types::ValueImpl::JaktString(((builder).to_string())),call_span));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "append_escaped_for_json"sv) {
{
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString> fields_current_string_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,ByteString>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{fields, value}));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of prelude StringBuilder"sv)));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid call"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> fields = ((fields_current_string_).template get<0>());
ByteString current_string = ((fields_current_string_).template get<1>());

ByteStringBuilder builder = ByteStringBuilder::create();
((builder).append(current_string));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "append"sv) {
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* StringView */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StringView;ByteString const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return ({((builder).append(value));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid use of StringBuilder::append({})"sv)),((((arguments)[static_cast<i64>(0LL)])).impl)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "append_escaped_for_json"sv) {
return ({((builder).append_escaped_for_json(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid use of StringBuilder::append_escaped_for_json()"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));}), JaktInternal::ExplicitValue<void>();
}
else if (__jakt_enum_value == "append_code_point"sv) {
return ({((builder).append_code_point(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u32, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid use of StringBuilder::append_code_point()"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));}), JaktInternal::ExplicitValue<void>();
}
else {
{
Jakt::abort();
}
return JaktInternal::ExplicitValue<void>();
}
return JaktInternal::ExplicitValue<void>();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((fields)[static_cast<i64>(0LL)]) = Jakt::types::Value(Jakt::types::ValueImpl::JaktString(((builder).to_string())),call_span));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "to_string"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(((fields)[static_cast<i64>(0LL)])));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "is_empty"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((value).is_empty())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of prelude StringBuilder"sv)));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "length"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(((value).length())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of prelude StringBuilder"sv)));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "clear"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_fields = fields;
(((((mutable_fields)[static_cast<i64>(0LL)])).impl) = Jakt::types::ValueImpl::JaktString((ByteString::from_utf8_without_validation(""sv))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` expects a StringBuilder as its this argument"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `StringBuilder::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "Dictionary"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "Dictionary"sv) {
{
if (((((type_bindings).size())) != (static_cast<size_t>(2ULL)))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Dictionary constructor expects two generic argumenst"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
Jakt::ids::StructId const dictionary_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Dictionary"sv))))));
Jakt::ids::TypeId const type_id = ((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),dictionary_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({(((type_bindings).get(((((type_bindings).keys()))[static_cast<i64>(0LL)]))).value()), (((type_bindings).get(((((type_bindings).keys()))[static_cast<i64>(1LL)]))).value())}))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktDictionary(DynamicArray<Jakt::types::Value>::create_with({}),DynamicArray<Jakt::types::Value>::create_with({}),type_id),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "get"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::Optional<size_t> found_index = JaktInternal::OptionalNone();
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((keys)[i])).impl))->equals(((((arguments)[static_cast<i64>(0LL)])).impl)))){
(found_index = i);
break;
}
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((found_index).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(((values)[(found_index.value())])),call_span));
}
else {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),call_span));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::get()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "set"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::Optional<size_t> found_index = JaktInternal::OptionalNone();
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((keys)[i])).impl))->equals(((((arguments)[static_cast<i64>(0LL)])).impl)))){
(found_index = i);
break;
}
}

}
}

JaktInternal::DynamicArray<Jakt::types::Value> mutable_keys = keys;
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
if (((found_index).has_value())){
(((mutable_values)[(found_index.value())]) = ((arguments)[static_cast<i64>(1LL)]));
}
else {
((mutable_keys).push(((arguments)[static_cast<i64>(0LL)])));
((mutable_values).push(((arguments)[static_cast<i64>(1LL)])));
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::set()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "is_empty"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool((((keys).is_empty()) && ((values).is_empty()))),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::is_empty()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "contains"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
{
bool found = false;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((keys)[i])).impl))->equals(((((arguments)[static_cast<i64>(0LL)])).impl)))){
(found = true);
break;
}
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(found),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::contains()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "remove"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::Optional<size_t> found_index = JaktInternal::OptionalNone();
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((keys)[i])).impl))->equals(((((arguments)[static_cast<i64>(0LL)])).impl)))){
(found_index = i);
break;
}
}

}
}

if (((found_index).has_value())){
JaktInternal::DynamicArray<Jakt::types::Value> keys_without = DynamicArray<Jakt::types::Value>::create_with({});
JaktInternal::DynamicArray<Jakt::types::Value> values_without = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((i) == ((found_index.value())))){
continue;
}
((keys_without).push(((keys)[i])));
((values_without).push(((values)[i])));
}

}
}

JaktInternal::DynamicArray<Jakt::types::Value> mutable_keys = keys;
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_keys).shrink(static_cast<size_t>(0ULL)));
((mutable_values).shrink(static_cast<size_t>(0ULL)));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((keys_without).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((mutable_keys).push(((keys_without)[i])));
((mutable_values).push(((values_without)[i])));
}

}
}

}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((found_index).has_value())),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::remove()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "ensure_capacity"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& capacity = __jakt_match_value.value;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_keys = keys;
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_keys).ensure_capacity(capacity));
((mutable_values).ensure_capacity(capacity));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Dictionary::ensure_capacity must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::ensure_capacity()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "capacity"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(((keys).capacity())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::capacity()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "clear"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_keys = keys;
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_keys).shrink(static_cast<size_t>(0ULL)));
((mutable_values).shrink(static_cast<size_t>(0ULL)));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::clear()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "size"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(((keys).size())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::size()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "keys"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generics = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::ids::TypeId>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected generic instance"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((((generics).size())) == (static_cast<size_t>(2ULL))));
if (__jakt_enum_value == true) {
{
Jakt::ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
Jakt::ids::TypeId const type_id = ((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),array_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({((generics)[static_cast<i64>(0LL)])}))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(keys,type_id),call_span)));
}
VERIFY_NOT_REACHED();
}
else {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("dictionary should have 2 generic args. one for keys, one for values"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::keys()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "iterator"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
{
Jakt::ids::StructId const struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("DictionaryIterator"sv))))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({(this_argument.value()), Jakt::types::Value(Jakt::types::ValueImpl::USize(static_cast<size_t>(0ULL)),call_span)}),struct_id,JaktInternal::OptionalNone()),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Dictionary::iterator()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `Dictionary::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "Array"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "iterator"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
{
Jakt::ids::StructId const struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("ArrayIterator"sv))))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({(this_argument.value()), Jakt::types::Value(Jakt::types::ValueImpl::USize(static_cast<size_t>(0ULL)),call_span)}),struct_id,JaktInternal::OptionalNone()),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::iterator()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "size"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(((values).size())),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::size()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "push"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_values).push(((arguments)[static_cast<i64>(0LL)])));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::push()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "push_values"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::Value value = (_magic_value.value());
{
((mutable_values).push(value));
}

}
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
return ({TRY((((*this).error((ByteString::from_utf8_without_validation("Only argument to push_values needs to be another Array"sv)),call_span))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::push_values()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "pop"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
JaktInternal::Optional<Jakt::types::Value> const value = ((mutable_values).pop());
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((value).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue((value.value())));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),call_span)));
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
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::push()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "first"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
JaktInternal::Optional<Jakt::types::Value> const value = ((mutable_values).first());
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((value).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue((value.value())));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),call_span)));
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
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::push()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "last"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
JaktInternal::Optional<Jakt::types::Value> const value = ((mutable_values).last());
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((value).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue((value.value())));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),call_span)));
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
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::push()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "contains"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
bool found = false;
{
JaktInternal::ArrayIterator<Jakt::types::Value> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::Value> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::Value value = (_magic_value.value());
{
if (((((value).impl))->equals(((((arguments)[static_cast<i64>(0LL)])).impl)))){
(found = true);
break;
}
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(found),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::contains()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "is_empty"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((values).is_empty())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::is_empty()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "capacity"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(((values).capacity())),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::capacity()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "ensure_capacity"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& capacity = __jakt_match_value.value;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_values).ensure_capacity(capacity));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Array::ensure_capacity must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::ensure_capacity()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "add_capacity"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& capacity = __jakt_match_value.value;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_values).add_capacity(capacity));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Array::add_capacity must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::add_capacity()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "shrink"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& size = __jakt_match_value.value;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_values).shrink(size));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Array::shrink must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Array::shrink()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `Array::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "ArrayIterator"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "next"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
{
size_t const index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid ArrayIterator index configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> mutable_fields = fields;
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((values).size()),index));
if (__jakt_enum_value == true) {
{
(((mutable_fields)[static_cast<i64>(1LL)]) = Jakt::types::Value(Jakt::types::ValueImpl::USize(JaktInternal::checked_add(index,static_cast<size_t>(1ULL))),call_span));
return JaktInternal::ExplicitValue<Jakt::types::Value>(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(((values)[index])),call_span));
}
VERIFY_NOT_REACHED();
}
else {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),call_span));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid ArrayIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid ArrayIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `ArrayIterator::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "Range"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "next"sv) {
{
JaktInternal::DynamicArray<Jakt::types::Value> fields = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::Value>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
return JaktInternal::ExplicitValue(fields);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Range::next()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
u64 const start = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((static_cast<u64>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid type for comptime range"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
u64 const end = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((static_cast<u64>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid type for comptime range"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((start) == (end))){
return Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),call_span));
}
if ([](u64 const& self, u64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(start,end)){
(((fields)[static_cast<i64>(0LL)]) = Jakt::types::Value(Jakt::types::ValueImpl::U64(JaktInternal::checked_sub(start,static_cast<u64>(1ULL))),call_span));
}
else {
(((fields)[static_cast<i64>(0LL)]) = Jakt::types::Value(Jakt::types::ValueImpl::U64(JaktInternal::checked_add(start,static_cast<u64>(1ULL))),call_span));
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(Jakt::types::Value(Jakt::types::ValueImpl::U64(start),call_span)),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "inclusive"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& constructor = __jakt_match_value.constructor;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_fields = fields;
u64 const end = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((static_cast<u64>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid type for comptime range"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(((((mutable_fields)[static_cast<i64>(1LL)])).impl) = Jakt::types::ValueImpl::U64(JaktInternal::checked_add(end,static_cast<u64>(1ULL))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(fields,struct_id,constructor),(((this_argument.value())).span))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Range::inclusive()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "exclusive"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue((this_argument.value())));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Range::exclusive()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `Range::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "String"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "is_empty"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((value).is_empty())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "length"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(((value).length())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "hash"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::U32(((value).hash())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "substring"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& start = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((static_cast<size_t>((start))),(static_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((static_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((static_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((static_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((static_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& start = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(static_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& start = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(static_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& start = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(static_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& start = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(static_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& length = __jakt_match_value.value;
{
ByteString const result = ((value).substring((infallible_integer_cast<size_t>((start))),(infallible_integer_cast<size_t>((length)))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(result),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::substring must be called with unsigned arguments"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "number"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(ByteString::number((static_cast<i64>((number))))),call_span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))),call_span)));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))),call_span)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))),call_span)));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))),call_span)));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))),call_span)));
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& number = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(ByteString::number((infallible_integer_cast<i64>((number))))),call_span)));
};/*case end*/
case 12 /* USize */: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::number must not be called with a usize or u64"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
case 5 /* U64 */: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::number must not be called with a usize or u64"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::number must be called with an integer"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "to_number"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(((type_bindings).size()),static_cast<size_t>(1ULL))){
TRY((((*this).error((ByteString::from_utf8_without_validation("to_number expects one generic argument"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
NonnullRefPtr<typename Jakt::types::Type> const target_type = ((((*this).program))->get_type((((type_bindings).get(((((type_bindings).keys()))[static_cast<i64>(0LL)]))).value())));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *target_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
{
JaktInternal::Optional<i32> const v = ((value).template to_number<i32>());
NonnullRefPtr<typename Jakt::types::ValueImpl> const impl = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((v).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::OptionalSome(Jakt::types::Value(Jakt::types::ValueImpl::I32((v.value())),call_span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(impl,call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
{
JaktInternal::Optional<u32> const v = ((value).template to_number<u32>());
NonnullRefPtr<typename Jakt::types::ValueImpl> const impl = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((v).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::OptionalSome(Jakt::types::Value(Jakt::types::ValueImpl::U32((v.value())),call_span)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(impl,call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid or unsupported type for String::to_number"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "is_whitespace"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((value).is_whitespace())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "contains"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& arg = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((value).contains(arg))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::contains must be called with a string"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "replace"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& replace = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& with = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(((value).replace(replace,with))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::replace must be called with strings"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::replace must be called with strings"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "byte_at"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::U8(((value).byte_at((static_cast<size_t>((index)))))),call_span)));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))),call_span)));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))),call_span)));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))),call_span)));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& index = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::U8(((value).byte_at((infallible_integer_cast<size_t>((index)))))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::byte_at must be called with an unsigned integer"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "split"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& c = __jakt_match_value.value;
{
JaktInternal::DynamicArray<ByteString> const values = ((value).split(c));
JaktInternal::DynamicArray<Jakt::types::Value> result = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<ByteString> _magic = ((values).iterator());
for (;;){
JaktInternal::Optional<ByteString> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
ByteString value = (_magic_value.value());
{
((result).push(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(value),call_span)));
}

}
}

Jakt::ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(result,((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),array_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({TRY((((*this).string_type())))}))))),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::split must be called with a c_char"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "starts_with"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& arg = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((value).starts_with(arg))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::starts_with must be called with a string"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "ends_with"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& arg = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((value).ends_with(arg))),call_span)));
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::ends_with must be called with a string"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid String"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "repeated"sv) {
{
if (((((arguments).size())) != (static_cast<size_t>(2ULL)))){
TRY((((*this).error((ByteString::from_utf8_without_validation("String::repeated must be called with a c_char and a usize"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
JaktInternal::Tuple<char,size_t> const character_count_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<char,size_t>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& arg = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<char,size_t>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& c = __jakt_match_value.value;
return JaktInternal::ExplicitValue((Tuple{arg, c}));
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::repeated must be called with a usize"sv)),((((arguments)[static_cast<i64>(1LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error((ByteString::from_utf8_without_validation("String::repeated must be called with a c_char"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
char const character = ((character_count_).template get<0>());
size_t const count = ((character_count_).template get<1>());

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(ByteString::repeated(character,count)),call_span)));
}
VERIFY_NOT_REACHED();
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `String::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "Set"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "Set"sv) {
{
if (((((type_bindings).size())) != (static_cast<size_t>(1ULL)))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Set constructor expects one generic argument"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
Jakt::ids::StructId const set_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Set"sv))))));
Jakt::ids::TypeId const type_id = ((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),set_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({(((type_bindings).get(((((type_bindings).keys()))[static_cast<i64>(0LL)]))).value())}))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktSet(DynamicArray<Jakt::types::Value>::create_with({}),type_id),call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "is_empty"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(((values).is_empty())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Set"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "contains"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
bool found = false;
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((values).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((values)[i])).impl))->equals(((((arguments)[static_cast<i64>(0LL)])).impl)))){
(found = true);
break;
}
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(found),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Set"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "add"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_values).push(((arguments)[static_cast<i64>(0LL)])));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Set"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "remove"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
bool found = false;
JaktInternal::DynamicArray<Jakt::types::Value> values_without = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((values).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((values)[i])).impl))->equals(((((arguments)[static_cast<i64>(0LL)])).impl)))){
(found = true);
continue;
}
((values_without).push(((values)[i])));
}

}
}

JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_values).shrink(static_cast<size_t>(0ULL)));
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((values_without).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
((mutable_values).push(((values_without)[i])));
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(found),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Set"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "clear"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_values).shrink(static_cast<size_t>(0ULL)));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Set"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "size"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(((values).size())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Set"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "capacity"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(((values).capacity())),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Set"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "ensure_capacity"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((arguments)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& capacity = __jakt_match_value.value;
{
JaktInternal::DynamicArray<Jakt::types::Value> mutable_values = values;
((mutable_values).ensure_capacity(capacity));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Set::ensure_capacity must be called with a usize"sv)),((((arguments)[static_cast<i64>(0LL)])).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Set"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "iterator"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
{
Jakt::ids::StructId const struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("SetIterator"sv))))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({(this_argument.value()), Jakt::types::Value(Jakt::types::ValueImpl::USize(static_cast<size_t>(0ULL)),call_span)}),struct_id,JaktInternal::OptionalNone()),call_span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid use of Set::iterator()"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `Set::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "SetIterator"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "next"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
{
size_t const index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid SetIterator index configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> mutable_fields = fields;
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((values).size()),index));
if (__jakt_enum_value == true) {
{
(((mutable_fields)[static_cast<i64>(1LL)]) = Jakt::types::Value(Jakt::types::ValueImpl::USize(JaktInternal::checked_add(index,static_cast<size_t>(1ULL))),call_span));
return JaktInternal::ExplicitValue<Jakt::types::Value>(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(((values)[index])),call_span));
}
VERIFY_NOT_REACHED();
}
else {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),call_span));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid SetIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid SetIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `ArrayIterator::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "DictionaryIterator"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "next"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
{
size_t const index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(1LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid DictionaryIterator index configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> mutable_fields = fields;
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((fields)[static_cast<i64>(0LL)])).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<Jakt::types::Value> const& keys = __jakt_match_value.keys;
JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((keys).size()),index) && [](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(((values).size()),index)));
if (__jakt_enum_value == true) {
{
(((mutable_fields)[static_cast<i64>(1LL)]) = Jakt::types::Value(Jakt::types::ValueImpl::USize(JaktInternal::checked_add(index,static_cast<size_t>(1ULL))),call_span));
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generics = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::ids::TypeId>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected generic instance"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::StructId const tuple_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Tuple"sv))))));
Jakt::ids::TypeId const tuple_type_id = ((*this).find_or_add_type_id(Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),tuple_struct_id,generics)));
return JaktInternal::ExplicitValue<Jakt::types::Value>(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(Jakt::types::Value(Jakt::types::ValueImpl::JaktTuple(DynamicArray<Jakt::types::Value>::create_with({((keys)[index]), ((values)[index])}),tuple_type_id),call_span)),call_span));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),call_span));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid DictionaryIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid DictionaryIterator configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `DictionaryIterator::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "Optional"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (prelude_function);
if (__jakt_enum_value == "has_value"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(true),call_span)));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(false),call_span)));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Optional configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "value"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 25 /* OptionalNone */: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Cannot unwrap optional none"sv)),prelude_function),call_span))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::Throw(TRY((((*this).error_value((ByteString::from_utf8_without_validation("Attempt to unwrap None"sv)),call_span))))));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Optional configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "map"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
{
Jakt::types::Value const mapper_value = ((arguments)[static_cast<i64>(0LL)]);
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((((mapper_value).impl))->__jakt_init_index() == 27 /* Function */));
if (__jakt_enum_value == true) {
{
Jakt::types::CheckedBlock const block = (((mapper_value).impl))->as.Function.block;
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>> const params = (((mapper_value).impl))->as.Function.params;
Jakt::ids::TypeId const return_type_id = (((mapper_value).impl))->as.Function.return_type_id;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const checked_params = (((mapper_value).impl))->as.Function.checked_params;
NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),JaktInternal::OptionalNone(),Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),runtime_scope_id);
bool first = true;
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = ((checked_params).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedParameter declared_param = (_magic_value.value());
{
ByteString const name = ((((declared_param).variable))->name);
JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>> const param_type_id___ = ((params)[name]);
Jakt::ids::TypeId const param_type_id = ((param_type_id___).template get<0>());
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>> const _ = ((param_type_id___).template get<1>());

if (first){
(first = false);
((((scope)->bindings)).set(name,TRY((Jakt::interpreter::cast_value_to_type(value,param_type_id,*this,false)))));
}
else {
break;
}

}

}
}

Jakt::interpreter::StatementResult const result = TRY((((*this).execute_block(block,scope,call_span))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((result).__jakt_init_index() == 5 /* JustValue */));
if (__jakt_enum_value == true) {
{
Jakt::types::Value const blk = (result).as.JustValue.value;
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(blk));
}
VERIFY_NOT_REACHED();
}
else {
{
return result;
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
}
else {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid mapper type in Optional::map"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue((this_argument.value())));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Optional configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == "value_or"sv) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(((arguments)[static_cast<i64>(0LL)])));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid Optional configuration"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `Optional::{}` is not implemented"sv)),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Prelude function `{}::{}` is not implemented"sv)),((((namespace_)[static_cast<i64>(0LL)])).name),prelude_function),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<Jakt::interpreter::StatementResult> Jakt::interpreter::Interpreter::call_compiler_interface_function(NonnullRefPtr<Jakt::types::CheckedFunction> const function,JaktInternal::DynamicArray<Jakt::types::Value> const arguments,Jakt::utility::Span const call_span,JaktInternal::Optional<Jakt::ids::ScopeId> const scope_id) {
{
if (((((((function)->params)).size())) != (((arguments).size())))){
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Compiler interface function '{}' called with wrong number of arguments, expected {} but got {}"sv)),((function)->name),((((function)->params)).size()),((arguments).size())),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Mismatching arguments"sv))));
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((function)->name));
if (__jakt_enum_value == "target_triple_string"sv) {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(TRY((((((*this).compiler))->target_triple).try_value_or_lazy_evaluated([&]() -> ErrorOr<ByteString> { return TRY((((TRY((Jakt::jakt__platform::Target::active()))).name(false)))); })))),call_span)));
}
else if (__jakt_enum_value == "user_configuration_value"sv) {
{
NonnullRefPtr<typename Jakt::types::ValueImpl> impl = Jakt::types::ValueImpl::OptionalNone();
JaktInternal::Optional<ByteString> const value = ((((((*this).compiler))->user_configuration)).get(TRY((((*this).string_from_value(((arguments)[static_cast<i64>(0LL)])))))));
if (((value).has_value())){
(impl = Jakt::types::ValueImpl::OptionalSome(TRY((((*this).string_value((value.value()),call_span))))));
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(impl,call_span)));
}
VERIFY_NOT_REACHED();
}
else if (__jakt_enum_value == "debug_this_scope"sv) {
{
if ((!(scope_id).has_value())){
warnln((StringView::from_string_literal("No scoping information available"sv)));
}
i32 scope_count = static_cast<i32>(0);
JaktInternal::Optional<Jakt::ids::ScopeId> current_scope_id = scope_id;
while (((current_scope_id).has_value())){
((scope_count) += (static_cast<i32>(1)));
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope((current_scope_id.value())));
warnln((StringView::from_string_literal("====== Scope {} ({}) ======"sv)),((scope)->debug_name),(current_scope_id.value()));
warnln((StringView::from_string_literal("{:#}"sv)),scope);
warnln((StringView::from_string_literal("====== Scope {} ======"sv)),((scope)->debug_name));
warnln((StringView::from_string_literal(""sv)));
(current_scope_id = ((scope)->parent));
}
if (((((((arguments)[static_cast<i64>(0LL)])).impl))->__jakt_init_index() == 1 /* Bool */)){
bool const value = (((((arguments)[static_cast<i64>(0LL)])).impl))->as.Bool.value;
if (value){
return Jakt::interpreter::StatementResult::Throw(TRY((((*this).error_value((ByteString::from_utf8_without_validation("Debugging breakpoint"sv)),call_span)))));
}
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::I32(scope_count),call_span)));
}
VERIFY_NOT_REACHED();
}
else {
{
warnln((StringView::from_string_literal("Compiler interface function '{}' is not implemented"sv)),((function)->name));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<Jakt::interpreter::ExecutionResult> Jakt::interpreter::Interpreter::execute(Jakt::ids::FunctionId const function_to_run_id,JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>> namespace_,JaktInternal::Optional<Jakt::types::Value> const this_argument,JaktInternal::DynamicArray<Jakt::types::Value> const arguments,Jakt::utility::Span const call_span,JaktInternal::Optional<NonnullRefPtr<Jakt::interpreter::InterpreterScope>> const invocation_scope) {
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function_to_run = ((((*this).program))->get_function(function_to_run_id));
((*this).enter_span(call_span));
JaktInternal::Optional<Jakt::ids::FunctionId> const old_function_id = ((*this).current_function_id);
(((*this).current_function_id) = function_to_run_id);
ScopeGuard __jakt_var_14([&] {
{
(((*this).current_function_id) = old_function_id);
((*this).leave_span());
}

});
bool is_prelude_function = false;
JaktInternal::Optional<Jakt::ids::ScopeId> const runtime_scope_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ids::ScopeId>,ErrorOr<Jakt::interpreter::ExecutionResult>> {
auto __jakt_enum_value = (((invocation_scope).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::ids::ScopeId>,ErrorOr<Jakt::interpreter::ExecutionResult>> {
auto __jakt_enum_value = ((((((invocation_scope.value()))->runtime_scope_id)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((((invocation_scope.value()))->runtime_scope_id));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((((function_to_run)->linkage)).__jakt_init_index() == 1 /* External */)){
NonnullRefPtr<Jakt::types::Scope> const function_scope = ((((*this).program))->get_scope(((function_to_run)->function_scope_id)));
ByteString const parent_scope_name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString,ErrorOr<Jakt::interpreter::ExecutionResult>> {
auto __jakt_enum_value = (((((function_scope)->parent)).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((((((*this).program))->get_scope((((function_scope)->parent).value()))))->debug_name));
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
if (((parent_scope_name) == ((ByteString::from_utf8_without_validation("module(jakt__compiler)"sv))))){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::ExecutionResult, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = TRY((((*this).call_compiler_interface_function(function_to_run,arguments,call_span,runtime_scope_id))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(value));
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
if ((!(((*this).get_prelude_function(((function_to_run)->function_scope_id)))))){
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Cannot call external function '{}'"sv)),((function_to_run)->name)),call_span))));
return Jakt::interpreter::ExecutionResult::Throw(TRY((((*this).error_value((ByteString::from_utf8_without_validation("Attempt to call external function"sv)),call_span)))));
}
(is_prelude_function = true);
}
if (((((function_to_run)->is_static())) == (((this_argument).has_value())))){
ByteString expected = (ByteString::from_utf8_without_validation("did not expect"sv));
if ((!(((function_to_run)->is_static())))){
(expected = (ByteString::from_utf8_without_validation("expected"sv)));
}
ByteString not_provided = (ByteString::from_utf8_without_validation(" not"sv));
if (((this_argument).has_value())){
(not_provided = (ByteString::from_utf8_without_validation(""sv)));
}
((((((*this).compiler))->errors)).push(Jakt::error::JaktError::Message(__jakt_format((StringView::from_string_literal("function call {} a this argument, yet one was{} provided"sv)),expected,not_provided),((function_to_run)->name_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid this argument"sv))));
}
size_t this_offset = static_cast<size_t>(0ULL);
if (((this_argument).has_value())){
(this_offset = static_cast<size_t>(1ULL));
}
if (((JaktInternal::checked_sub(((((function_to_run)->params)).size()),this_offset)) != (((arguments).size())))){
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Function called with wrong number of arguments, expected {} but got {}"sv)),((((function_to_run)->params)).size()),((arguments).size())),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Mismatching arguments"sv))));
}
if (is_prelude_function){
if ((((this_argument).has_value()) && ((!(((namespace_).has_value()))) || (((namespace_.value())).is_empty())))){
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> effective_namespace = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *(((this_argument.value())).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("String"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::ids::TypeId>, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to call a prelude function  on a non-generic array"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Array"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::ids::TypeId>, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to call a prelude function  on a non-generic dictionary"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Dictionary"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
if (((((((*this).program))->get_type(type_id)))->__jakt_init_index() == 20 /* GenericInstance */)){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = (((((*this).program))->get_type(type_id)))->as.GenericInstance.args;
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Set"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
else {
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to call a prelude function  on a non-generic set"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace(((((((*this).program))->get_struct(struct_id))).name),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace(((((((*this).program))->get_struct(struct_id))).name),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace(((((((*this).program))->get_enum(enum_id))).name),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* OptionalNone */: {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Optional"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* OptionalSome */: {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Optional"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to call an instance method on a non-struct/enum type"sv)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
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
(namespace_ = effective_namespace);
}
JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> type_bindings = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
if (((invocation_scope).has_value())){
(type_bindings = (((invocation_scope.value()))->type_bindings));
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::ExecutionResult, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = TRY((((*this).call_prelude_function(((function_to_run)->name),(namespace_.value()),this_argument,arguments,call_span,type_bindings,runtime_scope_id))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(value));
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = ((function_to_run)->type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Normal */: {
{
NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),invocation_scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),runtime_scope_id);
ScopeGuard __jakt_var_15([&] {
{
MUST((((scope)->perform_defers(*this,call_span))));
}

});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((function_to_run)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((((this_offset) != (static_cast<size_t>(0ULL))) && ((i) == (static_cast<size_t>(0ULL))))){
continue;
}
ByteString const param_name = ((((((((function_to_run)->params))[i])).variable))->name);
Jakt::types::Value const param_value = ((arguments)[JaktInternal::checked_sub(i,this_offset)]);
((scope)->bindings).set(param_name, param_value);
}

}
}

if (((this_argument).has_value())){
((((scope)->bindings)).set((ByteString::from_utf8_without_validation("this"sv)),(this_argument.value())));
}
Jakt::interpreter::StatementResult const blk = TRY((((*this).execute_block(((function_to_run)->block),scope,call_span))));
if (((blk).__jakt_init_index() == 5 /* JustValue */)){
Jakt::types::Value const x = (blk).as.JustValue.value;
if (((((x).impl))->__jakt_init_index() == 0 /* Void */)){
warnln((StringView::from_string_literal("Comptime function returned void, scope: {}"sv)),((((((*this).program))->get_scope(((function_to_run)->function_scope_id))))->debug_name));
Jakt::abort();
}
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::ExecutionResult, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = blk;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(TRY((Jakt::interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(TRY((Jakt::interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7 /* Closure */: {
{
NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),invocation_scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),runtime_scope_id);
ScopeGuard __jakt_var_16([&] {
{
MUST((((scope)->perform_defers(*this,call_span))));
}

});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((function_to_run)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((((this_offset) != (static_cast<size_t>(0ULL))) && ((i) == (static_cast<size_t>(0ULL))))){
continue;
}
ByteString const param_name = ((((((((function_to_run)->params))[i])).variable))->name);
Jakt::types::Value const param_value = ((arguments)[JaktInternal::checked_sub(i,this_offset)]);
((scope)->bindings).set(param_name, param_value);
}

}
}

if (((this_argument).has_value())){
((((scope)->bindings)).set((ByteString::from_utf8_without_validation("this"sv)),(this_argument.value())));
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::ExecutionResult, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block(((function_to_run)->block),scope,call_span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(TRY((Jakt::interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(TRY((Jakt::interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* Expression */: {
{
NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),invocation_scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),runtime_scope_id);
ScopeGuard __jakt_var_17([&] {
{
MUST((((scope)->perform_defers(*this,call_span))));
}

});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((function_to_run)->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if ((((this_offset) != (static_cast<size_t>(0ULL))) && ((i) == (static_cast<size_t>(0ULL))))){
continue;
}
ByteString const param_name = ((((((((function_to_run)->params))[i])).variable))->name);
Jakt::types::Value const param_value = ((arguments)[JaktInternal::checked_sub(i,this_offset)]);
((scope)->bindings).set(param_name, param_value);
}

}
}

if (((this_argument).has_value())){
((((scope)->bindings)).set((ByteString::from_utf8_without_validation("this"sv)),(this_argument.value())));
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::ExecutionResult, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block(((function_to_run)->block),scope,call_span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(TRY((Jakt::interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Return(TRY((Jakt::interpreter::cast_value_to_type(value,((function_to_run)->return_type_id),*this,false)))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::ExecutionResult::Throw(value));
};/*case end*/
case 3 /* Continue */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 4 /* Break */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* ImplicitConstructor */: {
{
NonnullRefPtr<typename Jakt::types::Type> const result_type = ((((*this).program))->get_type(((function_to_run)->return_type_id)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *result_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
Jakt::ids::FunctionId const constructor = function_to_run_id;
NonnullRefPtr<typename Jakt::types::ValueImpl> const impl = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Struct(arguments,struct_id,constructor));
};/*case end*/
case 1 /* Class */: {
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Class(arguments,struct_id,constructor));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Cannot create instance of non-struct type {}"sv)),((struct_).name)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Jakt::interpreter::ExecutionResult::Return(Jakt::types::Value(impl,call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
Jakt::types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
Jakt::ids::FunctionId const constructor = function_to_run_id;
NonnullRefPtr<typename Jakt::types::ValueImpl> const impl = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = ((struct_).record_type);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Struct(arguments,struct_id,constructor));
};/*case end*/
case 1 /* Class */: {
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Class(arguments,struct_id,constructor));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Cannot create instance of non-struct type {}"sv)),((struct_).name)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Jakt::interpreter::ExecutionResult::Return(Jakt::types::Value(impl,call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Implicit constructor can only return a struct or a generic instance"sv))),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
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
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* ImplicitEnumConstructor */: {
{
NonnullRefPtr<typename Jakt::types::Type> const result_type = ((((*this).program))->get_type(((function_to_run)->return_type_id)));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::ExecutionResult>>{
auto&& __jakt_match_variant = *result_type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
Jakt::ids::FunctionId const constructor = function_to_run_id;
NonnullRefPtr<typename Jakt::types::ValueImpl> const impl = Jakt::types::ValueImpl::Enum(arguments,enum_id,constructor);
return Jakt::interpreter::ExecutionResult::Return(Jakt::types::Value(impl,call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
Jakt::types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
Jakt::ids::FunctionId const constructor = function_to_run_id;
NonnullRefPtr<typename Jakt::types::ValueImpl> const impl = Jakt::types::ValueImpl::Enum(arguments,enum_id,constructor);
return Jakt::interpreter::ExecutionResult::Return(Jakt::types::Value(impl,call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Implicit enum constructor can only return an enum or a generic instance of one"sv))),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
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
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Function type {} is not implemented"sv)),((function_to_run)->type)),call_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}

ErrorOr<Jakt::interpreter::StatementResult> Jakt::interpreter::Interpreter::execute_statement(NonnullRefPtr<typename Jakt::types::CheckedStatement> const statement,NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope,Jakt::utility::Span const call_span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *statement;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
{
return ((((*this).execute_expression(expr,scope))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Defer */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Defer;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& statement = __jakt_match_value.statement;
{
((scope)->defer_statement(statement));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* DestructuringAssignment */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DestructuringAssignment;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& vars = __jakt_match_value.vars;
NonnullRefPtr<typename Jakt::types::CheckedStatement> const& var_decl = __jakt_match_value.var_decl;
{
if (((var_decl)->__jakt_init_index() == 3 /* VarDecl */)){
Jakt::ids::VarId const var_id = (var_decl)->as.VarDecl.var_id;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const init = (var_decl)->as.VarDecl.init;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(init,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& var_value = __jakt_match_value.value;
{
((scope)->bindings).set(((((((*this).program))->get_variable(var_id)))->name), var_value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedStatement>> _magic = ((vars).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedStatement> var = (_magic_value.value());
{
if (((var)->__jakt_init_index() == 3 /* VarDecl */)){
Jakt::ids::VarId const var_id = (var)->as.VarDecl.var_id;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const init = (var)->as.VarDecl.init;
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(init,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& var_value = __jakt_match_value.value;
{
((scope)->bindings).set(((((((*this).program))->get_variable(var_id)))->name), var_value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
else {
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected vardecl"sv)));
}

}

}
}

}
else {
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected vardecl"sv)));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* VarDecl */: {
auto&& __jakt_match_value = __jakt_match_variant.as.VarDecl;Jakt::ids::VarId const& var_id = __jakt_match_value.var_id;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& init = __jakt_match_value.init;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(init,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& var_value = __jakt_match_value.value;
{
((scope)->bindings).set(((((((*this).program))->get_variable(var_id)))->name), var_value);
if (((((var_value).impl))->__jakt_init_index() == 27 /* Function */)){
Jakt::types::CheckedBlock const block = (((var_value).impl))->as.Function.block;
JaktInternal::Optional<Jakt::ids::FunctionId> const pseudo_function_id = (((var_value).impl))->as.Function.pseudo_function_id;
if (((pseudo_function_id).has_value())){
Jakt::ids::FunctionId const id = (pseudo_function_id.value());
(((((((*this).program))->get_function(id)))->block) = block);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* If */: {
auto&& __jakt_match_value = __jakt_match_variant.as.If;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& then_block = __jakt_match_value.then_block;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedStatement>> const& else_statement = __jakt_match_value.else_statement;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
bool const cond = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(condition,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<bool, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("if condition must be a boolean, but got {}"sv)),((value).impl)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::Optional<Jakt::types::CheckedBlock> const block = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::CheckedBlock>,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (cond);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::CheckedBlock>>(then_block));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Optional<Jakt::types::CheckedBlock>,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((else_statement).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(static_cast<JaktInternal::Optional<Jakt::types::CheckedBlock>>(Jakt::types::CheckedBlock(DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedStatement>>::create_with({(else_statement.value())}),((then_block).scope_id),Jakt::types::BlockControlFlow::MayReturn(),JaktInternal::OptionalNone(),false)));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(JaktInternal::OptionalNone());
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((block).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block((block.value()),scope,span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Return(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Throw(value));
};/*case end*/
case 5 /* JustValue */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),span)));
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Continue());
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Break());
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
NonnullRefPtr<Jakt::interpreter::InterpreterScope> new_scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),((scope)->runtime_scope_id));
ScopeGuard __jakt_var_18([&] {
MUST((((new_scope)->perform_defers(*this,span))));
});
return ((((*this).execute_block(block,new_scope,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 6 /* Loop */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Loop;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
for (;;){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block(block,scope,span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 7 /* While */: {
auto&& __jakt_match_value = __jakt_match_variant.as.While;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& condition = __jakt_match_value.condition;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
for (;;){
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(condition,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& x = __jakt_match_value.value;
{
if (((((x).impl))->__jakt_init_index() == 1 /* Bool */)){
bool const cond = (((x).impl))->as.Bool.value;
if ((!(cond))){
return JaktInternal::LoopBreak{};
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_block(block,scope,span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 8 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& val = __jakt_match_value.val;
{
if (((val).has_value())){
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((val.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Return(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Throw(value));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Return(value));
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Continue());
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Break());
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return Jakt::interpreter::StatementResult::Return(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 9 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 10 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 12 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& expr = __jakt_match_value.expr;
{
if ((!(((expr).has_value())))){
return Jakt::interpreter::StatementResult::Yield(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span));
}
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((expr.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Yield(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 11 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 13 /* InlineCpp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.InlineCpp;Jakt::utility::Span const& span = __jakt_match_value.span;
return ({TRY((((*this).error((ByteString::from_utf8_without_validation("Cannot run inline cpp at compile time"sv)),span))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
case 14 /* Garbage */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Garbage;Jakt::utility::Span const& span = __jakt_match_value.value;
return ({TRY((((*this).error((ByteString::from_utf8_without_validation("Cannot run invalid statements at compile time"sv)),span))));}), JaktInternal::ExplicitValue<void>();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span));
}
}

ErrorOr<Jakt::interpreter::StatementResult> Jakt::interpreter::Interpreter::execute_block(Jakt::types::CheckedBlock const block,NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope,Jakt::utility::Span const call_span) {
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
((*this).enter_span(((statement)->span()).value_or_lazy_evaluated([&] { return call_span; })));
ScopeGuard __jakt_var_19([&] {
((*this).leave_span());
});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_statement(statement,scope,call_span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 5 /* JustValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Yield(value);
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

return Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),call_span));
}
}

ErrorOr<void> Jakt::interpreter::Interpreter::error(ByteString const message,Jakt::utility::Span const span) {
{
((((((*this).compiler))->errors)).push(Jakt::error::JaktError::Message(message,span)));
TRY((((((*this).compiler))->print_errors())));
}
return {};
}

ErrorOr<void> Jakt::interpreter::Interpreter::error_with_hint(ByteString const message,Jakt::utility::Span const span,ByteString const hint_message,Jakt::utility::Span const hint_span) {
{
((((((*this).compiler))->errors)).push(Jakt::error::JaktError::MessageWithHint(message,span,hint_message,hint_span)));
TRY((((((*this).compiler))->print_errors())));
}
return {};
}

ErrorOr<Jakt::interpreter::StatementResult> Jakt::interpreter::Interpreter::execute_binary_operator(Jakt::types::Value const lhs_value,Jakt::types::Value const rhs_value,Jakt::parser::BinaryOperator const op,Jakt::utility::Span const span,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Add */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F32(((x) + (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F64(((x) + (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize(JaktInternal::checked_add(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::JaktString(((x) + (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 1 /* Subtract */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F32(((x) - (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F64(((x) - (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize(JaktInternal::checked_sub(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 2 /* Multiply */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F32(((x) * (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F64(((x) * (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize(JaktInternal::checked_mul(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 3 /* Divide */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F32(((x) / (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::F64(((x) / (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize(JaktInternal::checked_div(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 9 /* Equal */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) == (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 10 /* NotEqual */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) != (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 5 /* LessThan */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u8 const& self, u8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u16 const& self, u16 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u16 const& self, u16 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u32 const& self, u32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u64 const& self, u64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i8 const& self, i8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i8 const& self, i8 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i16 const& self, i16 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i16 const& self, i16 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i32 const& self, i32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i32 const& self, i32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](f32 const& self, f32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](f32 const& self, f32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](f64 const& self, f64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](f64 const& self, f64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) < (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 6 /* LessThanOrEqual */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u8 const& self, u8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u16 const& self, u16 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u16 const& self, u16 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u32 const& self, u32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u64 const& self, u64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i8 const& self, i8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i8 const& self, i8 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i16 const& self, i16 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i16 const& self, i16 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i32 const& self, i32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i32 const& self, i32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](f32 const& self, f32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](f32 const& self, f32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](f64 const& self, f64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](f64 const& self, f64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) <= (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 7 /* GreaterThan */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u8 const& self, u8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u16 const& self, u16 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u16 const& self, u16 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u32 const& self, u32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u64 const& self, u64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i8 const& self, i8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i8 const& self, i8 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i16 const& self, i16 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i16 const& self, i16 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i32 const& self, i32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i32 const& self, i32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](f32 const& self, f32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](f32 const& self, f32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](f64 const& self, f64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](f64 const& self, f64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) > (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 8 /* GreaterThanOrEqual */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u8 const& self, u8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u8 const& self, u8 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u16 const& self, u16 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u16 const& self, u16 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u32 const& self, u32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u32 const& self, u32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](u64 const& self, u64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i8 const& self, i8 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i8 const& self, i8 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i16 const& self, i16 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i16 const& self, i16 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i32 const& self, i32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i32 const& self, i32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](i64 const& self, i64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](i64 const& self, i64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 10 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](f32 const& self, f32 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](f32 const& self, f32 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 11 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](f64 const& self, f64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](f64 const& self, f64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool(((x) >= (y))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 11 /* BitwiseAnd */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8((static_cast<u8>(((x & y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16((static_cast<u16>(((x & y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32((x & y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64((x & y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8((static_cast<i8>(((x & y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16((static_cast<i16>(((x & y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32((x & y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64((x & y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize((x & y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 13 /* BitwiseOr */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8((static_cast<u8>(((x | y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16((static_cast<u16>(((x | y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32((x | y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64((x | y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8((static_cast<i8>(((x | y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16((static_cast<i16>(((x | y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32((x | y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64((x | y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize((x | y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 12 /* BitwiseXor */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8((static_cast<u8>(((x ^ y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16((static_cast<u16>(((x ^ y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32((x ^ y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64((x ^ y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8((static_cast<i8>(((x ^ y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16((static_cast<i16>(((x ^ y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32((x ^ y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64((x ^ y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize((x ^ y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 14 /* BitwiseLeftShift */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8((static_cast<u8>(((x << y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16((static_cast<u16>(((x << y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8((static_cast<i8>(((x << y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16((static_cast<i16>(((x << y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 15 /* BitwiseRightShift */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8((static_cast<u8>(((x >> y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16((static_cast<u16>(((x >> y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32((x >> y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64((x >> y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8((static_cast<i8>(((x >> y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16((static_cast<i16>(((x >> y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32((x >> y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64((x >> y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize((x >> y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 16 /* ArithmeticLeftShift */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8((static_cast<u8>(((x << y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16((static_cast<u16>(((x << y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8((static_cast<i8>(((x << y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16((static_cast<i16>(((x << y))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize((x << y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 17 /* ArithmeticRightShift */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U8(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U16(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U32(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::U64(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I8(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I16(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I32(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::I64(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::USize(JaktInternal::arithmetic_shift_right(x,y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 19 /* LogicalOr */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool((x || y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 18 /* LogicalAnd */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<NonnullRefPtr<typename Jakt::types::ValueImpl>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((rhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& y = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::ValueImpl::Bool((x && y)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operands '{}' and '{}' to binary operation"sv)),((lhs_value).type_name()),((rhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),span)));
};/*case end*/
case 21 /* Assign */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(rhs_value));
};/*case end*/
case 22 /* BitwiseAndAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::BitwiseAnd(),span,scope)))));
};/*case end*/
case 23 /* BitwiseOrAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::BitwiseOr(),span,scope)))));
};/*case end*/
case 24 /* BitwiseXorAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::BitwiseXor(),span,scope)))));
};/*case end*/
case 25 /* BitwiseLeftShiftAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::BitwiseLeftShift(),span,scope)))));
};/*case end*/
case 26 /* BitwiseRightShiftAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::BitwiseRightShift(),span,scope)))));
};/*case end*/
case 27 /* AddAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::Add(),span,scope)))));
};/*case end*/
case 28 /* SubtractAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::Subtract(),span,scope)))));
};/*case end*/
case 29 /* MultiplyAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::Multiply(),span,scope)))));
};/*case end*/
case 30 /* ModuloAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::Modulo(),span,scope)))));
};/*case end*/
case 31 /* DivideAssign */: {
return JaktInternal::ExplicitValue(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,Jakt::parser::BinaryOperator::Divide(),span,scope)))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Unimplemented binary operator '{}'"sv)),op),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
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

ErrorOr<void> Jakt::interpreter::Interpreter::update_binding(NonnullRefPtr<typename Jakt::types::CheckedExpression> const binding,NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope,Jakt::types::Value const value,Jakt::utility::Span const span) {
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<void>>{
auto&& __jakt_match_variant = *binding;
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
{
TRY((((scope)->set(((var)->name),value))));
if (((((value).impl))->__jakt_init_index() == 27 /* Function */)){
Jakt::types::CheckedBlock const block = (((value).impl))->as.Function.block;
JaktInternal::Optional<Jakt::ids::FunctionId> const pseudo_function_id = (((value).impl))->as.Function.pseudo_function_id;
if (((pseudo_function_id).has_value())){
Jakt::ids::FunctionId const id = (pseudo_function_id.value());
(((((((*this).program))->get_function(id)))->block) = block);
}
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& name = __jakt_match_value.name;
{
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,Jakt::ids::StructId> fields_struct_id_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,Jakt::ids::StructId>, ErrorOr<void>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,Jakt::ids::StructId>, ErrorOr<void>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue((Tuple{fields, struct_id}));
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
return JaktInternal::ExplicitValue((Tuple{fields, struct_id}));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid left-hand side in assignment"sv)));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Should not be happening here"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> fields = ((fields_struct_id_).template get<0>());
Jakt::ids::StructId struct_id = ((fields_struct_id_).template get<1>());

JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> const field_decls = ((((((*this).program))->get_struct(struct_id))).fields);
size_t field_index = static_cast<size_t>(0ULL);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((field_decls).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((((*this).program))->get_variable(((((field_decls)[i]))->variable_id))))->name)) == (name))){
(field_index = i);
break;
}
}

}
}

(((fields)[field_index]) = value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& index = __jakt_match_value.index;
{
JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,Jakt::ids::EnumId> fields_enum_id_ = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,Jakt::ids::EnumId>, ErrorOr<void>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::Tuple<JaktInternal::DynamicArray<Jakt::types::Value>,Jakt::ids::EnumId>, ErrorOr<void>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
return JaktInternal::ExplicitValue((Tuple{fields, enum_id}));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid left-hand side in assignment"sv)));
}
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
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Should not be happening here"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> fields = ((fields_enum_id_).template get<0>());
Jakt::ids::EnumId enum_id = ((fields_enum_id_).template get<1>());

JaktInternal::DynamicArray<NonnullRefPtr<Jakt::types::CheckedField>> const field_decls = ((((((*this).program))->get_enum(enum_id))).fields);
size_t field_index = static_cast<size_t>(0ULL);
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((field_decls).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
if (((((((((*this).program))->get_variable(((((field_decls)[i]))->variable_id))))->name)) == (index))){
(field_index = i);
break;
}
}

}
}

(((fields)[field_index]) = value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid left-hand side of assignment {}"sv)),binding),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
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
}
return {};
}

ErrorOr<Jakt::interpreter::StatementResult> Jakt::interpreter::Interpreter::execute_expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((((*this).current_function_id)).has_value()));
if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(TRY((((*this).execute_expression_without_cast(expr,scope)))));
}
else {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression_without_cast(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Return(TRY((Jakt::interpreter::cast_value_to_type(value,((((((*this).program))->get_function((((*this).current_function_id).value()))))->return_type_id),*this,false)))));
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(TRY((Jakt::interpreter::cast_value_to_type(value,((expr)->type()),*this,false)))));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Throw(value));
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Yield(value));
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Break());
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Continue());
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
}
}

ErrorOr<Jakt::interpreter::StatementResult> Jakt::interpreter::Interpreter::execute_expression_without_cast(NonnullRefPtr<typename Jakt::types::CheckedExpression> const expr,NonnullRefPtr<Jakt::interpreter::InterpreterScope> scope) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *expr;
switch(__jakt_match_variant.__jakt_init_index()) {
case 7 /* BinaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.BinaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& lhs = __jakt_match_value.lhs;
Jakt::types::CheckedBinaryOperator const& op = __jakt_match_value.op;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& rhs = __jakt_match_value.rhs;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::types::Value const lhs_value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(lhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::interpreter::StatementResult const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = ((op).op);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* NoneCoalescing */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid left-hand side of NoneCoalescing"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
case 32 /* NoneCoalescingAssign */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 25 /* OptionalNone */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid left-hand side of NoneCoalescing"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
case 18 /* LogicalAnd */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (x);
if (__jakt_enum_value == ((((op).op)).__jakt_init_index() == 18 /* LogicalAnd */)) {
return JaktInternal::ExplicitValue(((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})).cast(lhs_value,span)));
}
else {
return JaktInternal::ExplicitValue(lhs_value);
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operand '{}' to binary operation"sv)),((lhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
case 19 /* LogicalOr */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((lhs_value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (x);
if (__jakt_enum_value == ((((op).op)).__jakt_init_index() == 18 /* LogicalAnd */)) {
return JaktInternal::ExplicitValue(((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})).cast(lhs_value,span)));
}
else {
return JaktInternal::ExplicitValue(lhs_value);
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid operand '{}' to binary operation"sv)),((lhs_value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
default: {
{
Jakt::types::Value const rhs_value = ((({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(rhs,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})).cast(lhs_value,span));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(TRY((((*this).execute_binary_operator(lhs_value,rhs_value,((op).op),span,scope)))));
}
VERIFY_NOT_REACHED();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = value;
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return ({({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = ((op).op);
switch(__jakt_match_variant.__jakt_init_index()) {
case 21 /* Assign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* BitwiseAndAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 23 /* BitwiseOrAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* BitwiseXorAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* BitwiseLeftShiftAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 26 /* BitwiseRightShiftAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 27 /* AddAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 28 /* SubtractAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 29 /* MultiplyAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 30 /* ModuloAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 31 /* DivideAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 32 /* NoneCoalescingAssign */: {
{
TRY((((*this).update_binding(lhs,scope,value,span))));
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
});}), JaktInternal::ExplicitValue<void>();
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
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* UnaryOp */: {
auto&& __jakt_match_value = __jakt_match_variant.as.UnaryOp;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedUnaryOperator const& op = __jakt_match_value.op;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 16 /* Sizeof */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Sizeof;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::USize(TRY((Jakt::interpreter::size_of_impl(type_id,*this)))),span)));
};/*case end*/
default: {
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = op;
switch(__jakt_match_variant.__jakt_init_index()) {
case 9 /* LogicalNot */: {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Bool */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Bool;bool const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool((!(value))),span)));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 1 /* PostIncrement */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::U8(JaktInternal::checked_add(x,static_cast<u8>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::I8(JaktInternal::checked_add(x,static_cast<i8>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::U16(JaktInternal::checked_add(x,static_cast<u16>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::I16(JaktInternal::checked_add(x,static_cast<i16>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::U32(JaktInternal::checked_add(x,static_cast<u32>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::I32(JaktInternal::checked_add(x,static_cast<i32>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::U64(JaktInternal::checked_add(x,static_cast<u64>(1ULL))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::I64(JaktInternal::checked_add(x,static_cast<i64>(1LL))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::CChar(JaktInternal::checked_add(x,static_cast<char>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::CInt(JaktInternal::checked_add(x,static_cast<int>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::USize(JaktInternal::checked_add(x,static_cast<size_t>(1ULL))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
case 0 /* PreIncrement */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::U8(JaktInternal::checked_add(x,static_cast<u8>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::I8(JaktInternal::checked_add(x,static_cast<i8>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::U16(JaktInternal::checked_add(x,static_cast<u16>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::I16(JaktInternal::checked_add(x,static_cast<i16>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::U32(JaktInternal::checked_add(x,static_cast<u32>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::I32(JaktInternal::checked_add(x,static_cast<i32>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::U64(JaktInternal::checked_add(x,static_cast<u64>(1ULL))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::I64(JaktInternal::checked_add(x,static_cast<i64>(1LL))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::CChar(JaktInternal::checked_add(x,static_cast<char>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::CInt(JaktInternal::checked_add(x,static_cast<int>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::USize(JaktInternal::checked_add(x,static_cast<size_t>(1ULL))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
case 3 /* PostDecrement */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::U8(JaktInternal::checked_sub(x,static_cast<u8>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::I8(JaktInternal::checked_sub(x,static_cast<i8>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::U16(JaktInternal::checked_sub(x,static_cast<u16>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::I16(JaktInternal::checked_sub(x,static_cast<i16>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::U32(JaktInternal::checked_sub(x,static_cast<u32>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::I32(JaktInternal::checked_sub(x,static_cast<i32>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::U64(JaktInternal::checked_sub(x,static_cast<u64>(1ULL))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::I64(JaktInternal::checked_sub(x,static_cast<i64>(1LL))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::CChar(JaktInternal::checked_sub(x,static_cast<char>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::CInt(JaktInternal::checked_sub(x,static_cast<int>(1))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
{
TRY((((*this).update_binding(expr,scope,Jakt::types::Value(Jakt::types::ValueImpl::USize(JaktInternal::checked_sub(x,static_cast<size_t>(1ULL))),span),span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
case 2 /* PreDecrement */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::U8(JaktInternal::checked_sub(x,static_cast<u8>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::I8(JaktInternal::checked_sub(x,static_cast<i8>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::U16(JaktInternal::checked_sub(x,static_cast<u16>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::I16(JaktInternal::checked_sub(x,static_cast<i16>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::U32(JaktInternal::checked_sub(x,static_cast<u32>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::I32(JaktInternal::checked_sub(x,static_cast<i32>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::U64(JaktInternal::checked_sub(x,static_cast<u64>(1ULL))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::I64(JaktInternal::checked_sub(x,static_cast<i64>(1LL))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 15 /* CChar */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CChar;char const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::CChar(JaktInternal::checked_sub(x,static_cast<char>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* CInt */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CInt;int const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::CInt(JaktInternal::checked_sub(x,static_cast<int>(1))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
{
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::USize(JaktInternal::checked_sub(x,static_cast<size_t>(1ULL))),span);
TRY((((*this).update_binding(expr,scope,value,span))));
return JaktInternal::ExplicitValue<Jakt::types::Value>(value);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid type for unary operator"sv))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
case 11 /* TypeCast */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeCast;Jakt::types::CheckedTypeCast const& cast = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = cast;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Identity */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Identity;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(TRY((Jakt::interpreter::cast_value_to_type(value,type_id,*this,false)))));
};/*case end*/
case 1 /* Infallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Infallible;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(TRY((Jakt::interpreter::cast_value_to_type(value,type_id,*this,false)))));
};/*case end*/
case 0 /* Fallible */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Fallible;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(TRY((Jakt::interpreter::cast_value_to_type(value,type_id,*this,false)))),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 13 /* IsEnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IsEnumVariant;Jakt::types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
JaktInternal::DynamicArray<Jakt::types::CheckedEnumVariantBinding> const& bindings = __jakt_match_value.bindings;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::FunctionId const& constructor = __jakt_match_value.constructor;
{
ByteString const constructor_name = ((((((*this).program))->get_function(constructor)))->name);
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(((enum_variant).name()),constructor_name)){
return Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(false),span));
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(true),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid value for unary operator '{}'"sv)),op),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
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
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Unimplemented unary operator '{}'"sv)),op),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 9 /* Range */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Range;JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& from = __jakt_match_value.from;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& to = __jakt_match_value.to;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::types::Value const start = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((from).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((from.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
else if (__jakt_enum_value == false) {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Partial ranges are not implemented"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::Value const end = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((to).has_value()));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((to.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
else if (__jakt_enum_value == false) {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Partial ranges are not implemented"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::StructId const range_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Range"sv))))));
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const range_constructors = (TRY((((((*this).program))->find_functions_with_name_in_scope(((((((*this).program))->get_struct(range_struct_id))).scope_id),(ByteString::from_utf8_without_validation("Range"sv)),false,JaktInternal::OptionalNone())))).value());
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({start, end}),range_struct_id,((range_constructors)[static_cast<i64>(0LL)])),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* Call */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Call;Jakt::types::CheckedCall const& call = __jakt_match_value.call;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
if ((!(((((call).function_id)).has_value())))){
JaktInternal::DynamicArray<Jakt::types::Value> arguments = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> arg = (_magic_value.value());
{
((arguments).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((arg).template get<1>()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
})));
}

}
}

return ((((*this).call_prelude_function(((call).name),DynamicArray<Jakt::types::ResolvedNamespace>::create_with({}),JaktInternal::OptionalNone(),arguments,span,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((scope)->runtime_scope_id)))));
}
NonnullRefPtr<Jakt::types::CheckedFunction> const function_to_run = ((((*this).program))->get_function((((call).function_id).value())));
if (((((function_to_run)->type)).__jakt_init_index() == 7 /* Closure */)){
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Cannot call a closure (nyi)"sv))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
JaktInternal::Optional<Jakt::types::Value> this_argument = JaktInternal::OptionalNone();
JaktInternal::DynamicArray<Jakt::types::Value> arguments = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> arg = (_magic_value.value());
{
((arguments).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((arg).template get<1>()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
})));
}

}
}

JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> type_bindings = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((((function_to_run)->generics))->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
Jakt::types::FunctionGenericParameter const param = ((((((function_to_run)->generics))->params))[i]);
((type_bindings).set(((param).type_id()),((((call).type_args))[i])));
}

}
}

JaktInternal::Dictionary<ByteString,Jakt::types::Value> const empty_bindings = Dictionary<ByteString, Jakt::types::Value>::create_with_entries({});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute((((call).function_id).value()),static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>>>(((call).namespace_)),this_argument,arguments,span,Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),JaktInternal::OptionalNone(),type_bindings,((*this).compiler),((scope)->runtime_scope_id))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Throw(value));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 22 /* MethodCall */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MethodCall;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedCall const& call = __jakt_match_value.call;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::types::Value const this_argument = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> effective_namespace = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((this_argument).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("String"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::ids::TypeId>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to call a prelude function  on a non-generic array"sv)),((this_argument).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Array"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 21 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::ids::TypeId>, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(type_id));
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
return JaktInternal::ExplicitValue(args);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to call a prelude function  on a non-generic dictionary"sv)),((this_argument).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Dictionary"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 22 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
if (((((((*this).program))->get_type(type_id)))->__jakt_init_index() == 20 /* GenericInstance */)){
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = (((((*this).program))->get_type(type_id)))->as.GenericInstance.args;
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Set"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
else {
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to call a prelude function  on a non-generic set"sv)),((this_argument).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}

}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace(((((((*this).program))->get_struct(struct_id))).name),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace(((((((*this).program))->get_struct(struct_id))).name),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace(((((((*this).program))->get_enum(enum_id))).name),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 25 /* OptionalNone */: {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Optional"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 24 /* OptionalSome */: {
{
JaktInternal::DynamicArray<Jakt::ids::TypeId> const generic_parameters = DynamicArray<Jakt::ids::TypeId>::create_with({});
((effective_namespace).push(Jakt::types::ResolvedNamespace((ByteString::from_utf8_without_validation("Optional"sv)),JaktInternal::OptionalNone(),generic_parameters)));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to call an instance method on a non-struct/enum type"sv)),((this_argument).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
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
if ((!(((((call).function_id)).has_value())))){
JaktInternal::DynamicArray<Jakt::types::Value> arguments = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> arg = (_magic_value.value());
{
((arguments).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((arg).template get<1>()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
})));
}

}
}

return ((((*this).call_prelude_function(((call).name),effective_namespace,this_argument,arguments,span,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((scope)->runtime_scope_id)))));
}
NonnullRefPtr<Jakt::types::CheckedFunction> const function_to_run = ((((*this).program))->get_function((((call).function_id).value())));
JaktInternal::DynamicArray<Jakt::types::Value> arguments = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((((call).args)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,NonnullRefPtr<typename Jakt::types::CheckedExpression>> arg = (_magic_value.value());
{
((arguments).push(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((arg).template get<1>()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
})));
}

}
}

JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::ids::TypeId> type_bindings = Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({});
{
JaktInternal::Range<size_t> _magic = (JaktInternal::Range<size_t>{static_cast<size_t>(static_cast<size_t>(0ULL)),static_cast<size_t>(((((((function_to_run)->generics))->params)).size()))});
for (;;){
JaktInternal::Optional<size_t> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
size_t i = (_magic_value.value());
{
Jakt::types::FunctionGenericParameter const param = ((((((function_to_run)->generics))->params))[i]);
((type_bindings).set(((param).type_id()),((((call).type_args))[i])));
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute((((call).function_id).value()),static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>>>(((call).namespace_)),this_argument,arguments,span,Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),JaktInternal::OptionalNone(),type_bindings,((*this).compiler),((scope)->runtime_scope_id))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Throw(value));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* OptionalNone */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalNone;Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalNone(),span)));
};/*case end*/
case 26 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::interpreter::StatementResult const result = TRY((((*this).execute_expression(expr,scope))));
if (((result).__jakt_init_index() == 5 /* JustValue */)){
Jakt::types::Value const value = (result).as.JustValue.value;
return Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::OptionalSome(value),span));
}
return result;
}
};/*case end*/
case 27 /* ForcedUnwrap */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ForcedUnwrap;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if (((((value).impl))->__jakt_init_index() == 25 /* OptionalNone */)){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to unwrap an optional value that was None"sv)),((value).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* OptionalSome */: {
auto&& __jakt_match_value = __jakt_match_variant.as.OptionalSome;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid type for unwrap"sv)),((value).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 28 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(TRY((((*this).execute_block(block,scope,span)))));
};/*case end*/
case 3 /* ByteConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ByteConstant;ByteString const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::U8(((val).byte_at(static_cast<size_t>(0ULL)))),span)));
};/*case end*/
case 24 /* Var */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Var;NonnullRefPtr<Jakt::types::CheckedVariable> const& var = __jakt_match_value.var;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(TRY((((scope)->must_get(((var)->name)))))));
};/*case end*/
case 13 /* IndexedExpression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedExpression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& index_expr = __jakt_match_value.index;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::Value const index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(index_expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<Jakt::types::Value> const& values = __jakt_match_value.values;
{
u64 const numeric_index = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<u64, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((index).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((static_cast<u64>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<u64>((x))));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid type for repeat"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
if ([](u64 const& self, u64 rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](u64 const& self, u64 rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) != (static_cast<u8>(0)));
}
}
(numeric_index,(infallible_integer_cast<u64>((((values).size())))))){
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Index {} out of bounds (max={})"sv)),numeric_index,((values).size())),span))));
return Jakt::interpreter::StatementResult::Throw(TRY((((*this).error_value((ByteString::from_utf8_without_validation("Invalid type"sv)),span)))));
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(((values)[numeric_index])));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid or unsupported indexed expression"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 0 /* Boolean */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Boolean;bool const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Bool(val),span)));
};/*case end*/
case 16 /* IndexedStruct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedStruct;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& name = __jakt_match_value.name;
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 17 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
Jakt::types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
i64 idx = static_cast<i64>(0LL);
JaktInternal::Optional<i64> found_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
if (((((((((*this).program))->get_variable(((field)->variable_id))))->name)) == (name))){
(found_index = idx);
break;
}
((idx) += (static_cast<i64>(1LL)));
}

}
}

if ((!(((found_index).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a field that does not exist"sv)),((value).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(((fields)[(found_index.value())])));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 18 /* Class */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Class;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::StructId const& struct_id = __jakt_match_value.struct_id;
{
Jakt::types::CheckedStruct const struct_ = ((((*this).program))->get_struct(struct_id));
i64 idx = static_cast<i64>(0LL);
JaktInternal::Optional<i64> found_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((struct_).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
if (((((((((*this).program))->get_variable(((field)->variable_id))))->name)) == (name))){
(found_index = idx);
break;
}
((idx) += (static_cast<i64>(1LL)));
}

}
}

if ((!(((found_index).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a field that does not exist"sv)),((value).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(((fields)[(found_index.value())])));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a field on a non-struct/enum type"sv)),((value).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 17 /* IndexedCommonEnumMember */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedCommonEnumMember;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
ByteString const& index = __jakt_match_value.index;
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
{
Jakt::types::CheckedEnum const enum_ = ((((*this).program))->get_enum(enum_id));
i64 idx = static_cast<i64>(0LL);
JaktInternal::Optional<i64> found_index = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((enum_).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
if (((((((((*this).program))->get_variable(((field)->variable_id))))->name)) == (index))){
(found_index = idx);
break;
}
((idx) += (static_cast<i64>(1LL)));
}

}
}

if ((!(((found_index).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a field that does not exist"sv)),((value).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(((fields)[(found_index.value())])));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a field on a non-struct/enum type"sv)),((value).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* JaktDictionary */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktDictionary;JaktInternal::DynamicArray<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const& vals = __jakt_match_value.vals;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::types::Value> keys = DynamicArray<Jakt::types::Value>::create_with({});
JaktInternal::DynamicArray<Jakt::types::Value> values = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> k__v__ = (_magic_value.value());
{
JaktInternal::Tuple<NonnullRefPtr<typename Jakt::types::CheckedExpression>,NonnullRefPtr<typename Jakt::types::CheckedExpression>> const jakt__k__v__ = k__v__;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const k = ((jakt__k__v__).template get<0>());
NonnullRefPtr<typename Jakt::types::CheckedExpression> const v = ((jakt__k__v__).template get<1>());

Jakt::types::Value const key = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(k,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
Jakt::types::Value const val = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(v,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
((keys).push(key));
((values).push(val));
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktDictionary(keys,values,type_id),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* NumericConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.NumericConstant;Jakt::types::CheckedNumericConstant const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = val;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I8(x),span));
};/*case end*/
case 1 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I16(x),span));
};/*case end*/
case 2 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I32(x),span));
};/*case end*/
case 3 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::I64(x),span));
};/*case end*/
case 4 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U8(x),span));
};/*case end*/
case 5 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U16(x),span));
};/*case end*/
case 6 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U32(x),span));
};/*case end*/
case 7 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::U64(x),span));
};/*case end*/
case 8 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::USize((infallible_integer_cast<size_t>((x)))),span));
};/*case end*/
case 9 /* F32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F32;f32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::F32(x),span));
};/*case end*/
case 10 /* F64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.F64;f64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::types::Value(Jakt::types::ValueImpl::F64(x),span));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
})));
};/*case end*/
case 2 /* QuotedString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.QuotedString;Jakt::types::CheckedStringLiteral const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((((val).type_id)).equals(Jakt::types::builtin(Jakt::types::BuiltinType::JaktString()))));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktString(Jakt::utility::interpret_escapes(((val).to_string()))),span)));
}
else if (__jakt_enum_value == false) {
{
Jakt::ids::FunctionId const function_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::FunctionId, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((val).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((((((*this).program))->get_struct(struct_id))).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const overloads = ((((scope)->functions)).get((ByteString::from_utf8_without_validation("from_string_literal"sv))));
if ((!(((overloads).has_value())))){
Jakt::utility::panic(__jakt_format((StringView::from_string_literal("Failed to find a from_string_literal overload in {}"sv)),TRY((((((*this).program))->type_name(((val).type_id),false))))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>(((((overloads.value())).first()).value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((((((*this).program))->get_struct(struct_id))).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const overloads = ((((scope)->functions)).get((ByteString::from_utf8_without_validation("from_string_literal"sv))));
if ((!(((overloads).has_value())))){
Jakt::utility::panic(__jakt_format((StringView::from_string_literal("Failed to find a from_string_literal overload in {}"sv)),TRY((((((*this).program))->type_name(((val).type_id),false))))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>(((((overloads.value())).first()).value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((((((*this).program))->get_enum(enum_id))).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const overloads = ((((scope)->functions)).get((ByteString::from_utf8_without_validation("from_string_literal"sv))));
if ((!(((overloads).has_value())))){
Jakt::utility::panic((ByteString::from_utf8_without_validation("Failed to find a from_string_literal overload"sv)));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>(((((overloads.value())).first()).value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(((((((*this).program))->get_enum(enum_id))).scope_id)));
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const overloads = ((((scope)->functions)).get((ByteString::from_utf8_without_validation("from_string_literal"sv))));
if ((!(((overloads).has_value())))){
Jakt::utility::panic((ByteString::from_utf8_without_validation("Failed to find a from_string_literal overload"sv)));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>(((((overloads.value())).first()).value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Invalid type {} for string literal"sv)),((((*this).program))->get_type(((val).type_id)))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace> const ns = DynamicArray<Jakt::types::ResolvedNamespace>::create_with({});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute(function_id,static_cast<JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::types::ResolvedNamespace>>>(ns),JaktInternal::OptionalNone(),DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::JaktString(Jakt::utility::interpret_escapes(((val).to_string()))),span)}),span,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::Throw(value));
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
}
VERIFY_NOT_REACHED();
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 5 /* CCharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CCharacterConstant;ByteString const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::CChar((infallible_integer_cast<char>((((val).byte_at(static_cast<size_t>(0ULL))))))),span)));
};/*case end*/
case 4 /* CharacterConstant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CharacterConstant;ByteString const& val = __jakt_match_value.val;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
DeprecatedStringCodePointIterator code_points = ((val).code_points());
JaktInternal::Optional<u32> const code_point = ((code_points).next());
if ((!(((code_point).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Invalid character constant"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid character constant"sv))));
}
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::U32((code_point.value())),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* JaktArray */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktArray;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& repeat = __jakt_match_value.repeat;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((repeat).has_value()));
if (__jakt_enum_value == true) {
{
size_t const count = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression((repeat.value()),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<size_t, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 6 /* I8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I8;i8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
case 7 /* I16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I16;i16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
case 8 /* I32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I32;i32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
case 9 /* I64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.I64;i64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
case 2 /* U8 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U8;u8 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
case 3 /* U16 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U16;u16 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
case 4 /* U32 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U32;u32 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
case 5 /* U64 */: {
auto&& __jakt_match_value = __jakt_match_variant.as.U64;u64 const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((infallible_integer_cast<size_t>((x))));
};/*case end*/
case 12 /* USize */: {
auto&& __jakt_match_value = __jakt_match_variant.as.USize;size_t const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue((static_cast<size_t>((x))));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid type for repeat"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::Value const value_to_repeat = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(((vals)[static_cast<i64>(0LL)]),scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(DynamicArray<Jakt::types::Value>::filled(count, value_to_repeat),TRY((((((*this).program))->substitute_typevars_in_type(type_id,((scope)->type_map_for_substitution()),((type_id).module)))))),span)));
}
VERIFY_NOT_REACHED();
}
else {
{
JaktInternal::DynamicArray<Jakt::types::Value> values = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> value = (_magic_value.value());
{
Jakt::types::Value const val = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(value,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
((values).push(val));
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(values,TRY((((((*this).program))->substitute_typevars_in_type(type_id,((scope)->type_map_for_substitution()),((type_id).module)))))),span)));
}
VERIFY_NOT_REACHED();
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
};/*case end*/
case 15 /* IndexedTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.IndexedTuple;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
size_t const& index = __jakt_match_value.index;
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult,ErrorOr<Jakt::interpreter::StatementResult>> {
auto __jakt_enum_value = (((((value).impl))->__jakt_init_index() == 26 /* JaktTuple */));
if (__jakt_enum_value == true) {
{
JaktInternal::DynamicArray<Jakt::types::Value> const fields = (((value).impl))->as.JaktTuple.fields;
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(((fields)[index])));
}
VERIFY_NOT_REACHED();
}
else {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("expected tuple"sv)));
}
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 19 /* Match */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Match;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
JaktInternal::DynamicArray<Jakt::types::CheckedMatchCase> const& match_cases = __jakt_match_value.match_cases;
bool const& all_variants_constant = __jakt_match_value.all_variants_constant;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
Jakt::ids::FunctionId const& constructor = __jakt_match_value.constructor;
{
ByteString const constructor_name = ((((((*this).program))->get_function(constructor)))->name);
JaktInternal::Optional<Jakt::types::CheckedMatchBody> catch_all_case = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::types::CheckedMatchBody> found_body = JaktInternal::OptionalNone();
JaktInternal::Optional<JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument>> found_args = JaktInternal::OptionalNone();
JaktInternal::Optional<size_t> found_variant_index = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::utility::Span> span = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedMatchCase match_case = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const& args = __jakt_match_value.args;
size_t const& index = __jakt_match_value.index;
Jakt::types::CheckedMatchBody const& body = __jakt_match_value.body;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
if ([](ByteString const& self, ByteString rhs) -> bool {{
return (!(((self) == (rhs))));
}
}
(name,constructor_name)){
return JaktInternal::LoopContinue{};
}
(found_body = body);
(found_args = args);
(found_variant_index = index);
(span = marker_span);
return JaktInternal::LoopBreak{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Value matches are not allowed on enums"sv)),marker_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Value matches are not allowed on enums"sv)),marker_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;Jakt::types::CheckedMatchBody const& body = __jakt_match_value.body;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
(catch_all_case = body);
(span = marker_span);
return JaktInternal::LoopContinue{};
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

if (((!(((catch_all_case).has_value()))) && (!(((found_body).has_value()))))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Match is not exhaustive"sv)),(span.value())))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
(found_body = found_body.value_or_lazy_evaluated([&] { return (catch_all_case.value()); }));
JaktInternal::DynamicArray<Jakt::parser::EnumVariantPatternArgument> const empty_args = DynamicArray<Jakt::parser::EnumVariantPatternArgument>::create_with({});
(found_args = found_args.value_or_lazy_evaluated([&] { return empty_args; }));
NonnullRefPtr<Jakt::interpreter::InterpreterScope> new_scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),((scope)->runtime_scope_id));
ScopeGuard __jakt_var_20([&] {
MUST((((new_scope)->perform_defers(*this,(span.value())))));
});
if ((((found_variant_index).has_value()) && (!((((found_args.value())).is_empty()))))){
Jakt::types::CheckedEnumVariant const variant = ((((((((*this).program))->get_enum(enum_id))).variants))[(found_variant_index.value())]);
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Untyped */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* WithValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Typed */: {
{
if ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(2)));
}
}
((((found_args.value())).size()),static_cast<size_t>(0ULL))){
((((new_scope)->bindings)).set((((((found_args.value()))[static_cast<i64>(0LL)])).binding),((fields)[static_cast<i64>(0LL)])));
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& variant_fields = __jakt_match_value.fields;
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((variant_fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId var_id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const field = ((((*this).program))->get_variable(var_id));
{
JaktInternal::ArrayIterator<Jakt::parser::EnumVariantPatternArgument> _magic = (((found_args.value())).iterator());
for (;;){
JaktInternal::Optional<Jakt::parser::EnumVariantPatternArgument> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::parser::EnumVariantPatternArgument arg = (_magic_value.value());
{
ByteString const matched_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); });
if (((matched_name) == (((field)->name)))){
((((new_scope)->bindings)).set(((arg).binding),((fields)[i])));
break;
}
}

}
}

((i) += (static_cast<i64>(1LL)));
}

}
}

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
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = (found_body.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
{
Jakt::interpreter::StatementResult const result = TRY((((*this).execute_expression(expr,new_scope))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 5 /* JustValue */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 0 /* Return */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 1 /* Throw */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.value;
{
Jakt::interpreter::StatementResult const result = TRY((((*this).execute_block(block,new_scope,(span.value())))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 5 /* JustValue */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 0 /* Return */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 1 /* Throw */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
JaktInternal::Optional<Jakt::types::CheckedMatchBody> catch_all_case = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::types::CheckedMatchBody> found_body = JaktInternal::OptionalNone();
JaktInternal::Optional<Jakt::utility::Span> span = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedMatchCase> _magic = ((match_cases).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedMatchCase> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedMatchCase match_case = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = match_case;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;Jakt::types::CheckedMatchBody const& body = __jakt_match_value.body;
NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expression = __jakt_match_value.expression;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
Jakt::types::Value const value_to_match_against = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expression,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
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
});
if (((((value_to_match_against).impl))->equals(((value).impl)))){
(found_body = static_cast<JaktInternal::Optional<Jakt::types::CheckedMatchBody>>(body));
(span = static_cast<JaktInternal::Optional<Jakt::utility::Span>>(marker_span));
return JaktInternal::LoopBreak{};
}
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* CatchAll */: {
auto&& __jakt_match_value = __jakt_match_variant.as.CatchAll;Jakt::types::CheckedMatchBody const& body = __jakt_match_value.body;
Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
(catch_all_case = body);
(span = marker_span);
return JaktInternal::LoopContinue{};
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* ClassInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.ClassInstance;Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Class instance matches are not implemented yet"sv)),marker_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* EnumVariant */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariant;Jakt::utility::Span const& marker_span = __jakt_match_value.marker_span;
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Value matches cannot have enum variant arms (matching on {})"sv)),((value).type_name())),marker_span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
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

if (((!(found_body).has_value()) && (!(catch_all_case).has_value()))){
TRY((((*this).error(__jakt_format((StringView::from_string_literal("No match found for value of type {}"sv)),((value).type_name())),(((((*this).spans)).last()).value())))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
(found_body = found_body.value_or_lazy_evaluated([&] { return (catch_all_case.value()); }));
NonnullRefPtr<Jakt::interpreter::InterpreterScope> new_scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),((scope)->runtime_scope_id));
ScopeGuard __jakt_var_21([&] {
MUST((((new_scope)->perform_defers(*this,(span.value())))));
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = (found_body.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Expression */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Expression;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.value;
{
Jakt::interpreter::StatementResult const result = TRY((((*this).execute_expression(expr,new_scope))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 5 /* JustValue */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 0 /* Return */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 1 /* Throw */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Block */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Block;Jakt::types::CheckedBlock const& block = __jakt_match_value.value;
{
Jakt::interpreter::StatementResult const result = TRY((((*this).execute_block(block,new_scope,(span.value())))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(value));
};/*case end*/
case 3 /* Continue */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 4 /* Break */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 5 /* JustValue */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 0 /* Return */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
case 1 /* Throw */: {
return JaktInternal::ExplicitValue(result);
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* EnumVariantArg */: {
auto&& __jakt_match_value = __jakt_match_variant.as.EnumVariantArg;NonnullRefPtr<typename Jakt::types::CheckedExpression> const& expr = __jakt_match_value.expr;
Jakt::types::CheckedEnumVariantBinding const& arg = __jakt_match_value.arg;
Jakt::types::CheckedEnumVariant const& enum_variant = __jakt_match_value.enum_variant;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(expr,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
}
};/*case end*/
default: VERIFY_NOT_REACHED();}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value> const& fields = __jakt_match_value.fields;
Jakt::ids::EnumId const& enum_id = __jakt_match_value.enum_id;
Jakt::ids::FunctionId const& constructor = __jakt_match_value.constructor;
{
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> found_variant = JaktInternal::OptionalNone();
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((((((*this).program))->get_enum(enum_id))).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
if (((((variant).name())) == (((enum_variant).name())))){
(found_variant = variant);
break;
}
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::interpreter::StatementResult, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = (found_variant.value());
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Typed */: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(((fields)[static_cast<i64>(0LL)])));
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;JaktInternal::DynamicArray<Jakt::ids::VarId> const& variant_fields = __jakt_match_value.fields;
{
i64 i = static_cast<i64>(0LL);
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((variant_fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId var_id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const field = ((((*this).program))->get_variable(var_id));
ByteString const matched_name = ((arg).name).value_or_lazy_evaluated([&] { return ((arg).binding); });
if (((matched_name) == (((field)->name)))){
break;
}
((i) += (static_cast<i64>(1LL)));
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(((fields)[i])));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),span)));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Value matches cannot have enum variant arms (matching on {})"sv)),((value).type_name())),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* JaktTuple */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktTuple;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::types::Value> fields = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> val = (_magic_value.value());
{
Jakt::types::Value const value = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(val,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
{
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid control flow"sv))));
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
((fields).push(value));
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktTuple(fields,type_id),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* JaktSet */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktSet;JaktInternal::DynamicArray<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const& vals = __jakt_match_value.vals;
Jakt::utility::Span const& span = __jakt_match_value.span;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
JaktInternal::DynamicArray<Jakt::types::Value> values = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<typename Jakt::types::CheckedExpression>> _magic = ((vals).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<typename Jakt::types::CheckedExpression>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<typename Jakt::types::CheckedExpression> v = (_magic_value.value());
{
Jakt::types::Value const val = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::types::Value, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_expression(v,scope))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Throw(value);
}
};/*case end*/
case 5 /* JustValue */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JustValue;Jakt::types::Value const& value = __jakt_match_value.value;
return JaktInternal::ExplicitValue(value);
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
};/*case end*/
case 2 /* Yield */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Yield;Jakt::types::Value const& expr = __jakt_match_value.value;
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
((values).push(val));
}

}
}

return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::JaktSet(values,type_id),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 30 /* DependentFunction */: {
auto&& __jakt_match_value = __jakt_match_variant.as.DependentFunction;JaktInternal::DynamicArray<Jakt::types::CheckedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const& params = __jakt_match_value.params;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::parser::ParsedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
{
JaktInternal::Dictionary<ByteString,Jakt::types::Value> resolved_captures = Dictionary<ByteString, Jakt::types::Value>::create_with_entries({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedCapture> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedCapture capture = (_magic_value.value());
{
ByteString const name = ((capture).common.init_common.name);
if ((((capture).__jakt_init_index() == 0 /* ByValue */) || ((capture).__jakt_init_index() == 3 /* ByComptimeDependency */))){
((resolved_captures).set(name,TRY((((scope)->must_get(name))))));
}
else {
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Cannot capture by reference in a comptime function (nyi)"sv))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}

}

}
}

Jakt::types::GenericInferences const type_map = ((scope)->type_map_for_substitution());
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>> resolved_params = Dictionary<ByteString, JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>>::create_with_entries({});
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> checked_params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedParameter param = (_magic_value.value());
{
Jakt::ids::TypeId const param_type_id = TRY((((((*this).program))->substitute_typevars_in_type(((((param).variable))->type_id),type_map,((((((param).variable))->type_id)).module)))));
((resolved_params).set(((((param).variable))->name),(Tuple{param_type_id, ((param).default_value_expression)})));
((checked_params).push(Jakt::types::CheckedParameter(((param).requires_label),Jakt::types::CheckedVariable::__jakt_create(((((param).variable))->name),param_type_id,((((param).variable))->is_mutable),((((param).variable))->definition_span),((((param).variable))->type_span),((((param).variable))->visibility),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()),((param).default_value_expression))));
}

}
}

Jakt::types::CheckedBlock const fixed_block = TRY((((*this).perform_final_interpretation_pass(block,scope_id,Jakt::interpreter::InterpreterScope::create(resolved_captures,scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),scope_id),pseudo_function_id))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Function(resolved_captures,resolved_params,TRY((((((*this).program))->substitute_typevars_in_type(return_type_id,type_map,((return_type_id).module))))),TRY((((((*this).program))->substitute_typevars_in_type(type_id,type_map,((type_id).module))))),fixed_block,can_throw,checked_params,scope_id,pseudo_function_id),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 29 /* Function */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Function;JaktInternal::DynamicArray<Jakt::types::CheckedCapture> const& captures = __jakt_match_value.captures;
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> const& params = __jakt_match_value.params;
Jakt::ids::TypeId const& return_type_id = __jakt_match_value.return_type_id;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
Jakt::types::CheckedBlock const& block = __jakt_match_value.block;
Jakt::utility::Span const& span = __jakt_match_value.span;
bool const& can_throw = __jakt_match_value.can_throw;
Jakt::ids::ScopeId const& scope_id = __jakt_match_value.scope_id;
JaktInternal::Optional<Jakt::ids::FunctionId> const& pseudo_function_id = __jakt_match_value.pseudo_function_id;
{
JaktInternal::Dictionary<ByteString,Jakt::types::Value> resolved_captures = Dictionary<ByteString, Jakt::types::Value>::create_with_entries({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedCapture> _magic = ((captures).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedCapture> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedCapture capture = (_magic_value.value());
{
ByteString const name = ((capture).common.init_common.name);
if ((((capture).__jakt_init_index() == 0 /* ByValue */) || ((capture).__jakt_init_index() == 3 /* ByComptimeDependency */))){
((resolved_captures).set(name,TRY((((scope)->must_get(name))))));
}
else {
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Cannot capture by reference in a comptime function (nyi)"sv))),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}

}

}
}

Jakt::types::GenericInferences const type_map = ((scope)->type_map_for_substitution());
JaktInternal::Dictionary<ByteString,JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>> resolved_params = Dictionary<ByteString, JaktInternal::Tuple<Jakt::ids::TypeId,JaktInternal::Optional<JaktInternal::Tuple<NonnullRefPtr<typename Jakt::parser::ParsedExpression>,Jakt::ids::ScopeId>>>>::create_with_entries({});
JaktInternal::DynamicArray<Jakt::types::CheckedParameter> checked_params = DynamicArray<Jakt::types::CheckedParameter>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedParameter> _magic = ((params).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedParameter param = (_magic_value.value());
{
Jakt::ids::TypeId const param_type_id = TRY((((((*this).program))->substitute_typevars_in_type(((((param).variable))->type_id),type_map,((((((param).variable))->type_id)).module)))));
((resolved_params).set(((((param).variable))->name),(Tuple{param_type_id, ((param).default_value_expression)})));
((checked_params).push(Jakt::types::CheckedParameter(((param).requires_label),Jakt::types::CheckedVariable::__jakt_create(((((param).variable))->name),param_type_id,((((param).variable))->is_mutable),((((param).variable))->definition_span),((((param).variable))->type_span),((((param).variable))->visibility),JaktInternal::OptionalNone(),JaktInternal::OptionalNone(),JaktInternal::OptionalNone()),((param).default_value_expression))));
}

}
}

Jakt::types::CheckedBlock const fixed_block = TRY((((*this).perform_final_interpretation_pass(block,scope_id,Jakt::interpreter::InterpreterScope::create(resolved_captures,scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),scope_id),pseudo_function_id))));
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Function(resolved_captures,resolved_params,TRY((((((*this).program))->substitute_typevars_in_type(return_type_id,type_map,((return_type_id).module))))),TRY((((((*this).program))->substitute_typevars_in_type(type_id,type_map,((type_id).module))))),fixed_block,can_throw,checked_params,scope_id,pseudo_function_id),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 33 /* TryBlock */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TryBlock;NonnullRefPtr<typename Jakt::types::CheckedStatement> const& stmt = __jakt_match_value.stmt;
Jakt::types::CheckedBlock const& catch_block = __jakt_match_value.catch_block;
ByteString const& error_name = __jakt_match_value.error_name;
Jakt::utility::Span const& span = __jakt_match_value.span;
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = TRY((((*this).execute_statement(stmt,scope,span))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 5 /* JustValue */: {
{
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Throw;Jakt::types::Value const& value = __jakt_match_value.value;
{
NonnullRefPtr<Jakt::interpreter::InterpreterScope> catch_scope = Jakt::interpreter::InterpreterScope::create(Dictionary<ByteString, Jakt::types::Value>::create_with_entries({}),scope,Dictionary<Jakt::ids::TypeId, Jakt::ids::TypeId>::create_with_entries({}),((*this).compiler),((scope)->runtime_scope_id));
ScopeGuard __jakt_var_22([&] {
MUST((((catch_scope)->perform_defers(*this,span))));
});
((((catch_scope)->bindings)).set(error_name,value));
Jakt::interpreter::StatementResult const result = TRY((((*this).execute_block(catch_block,catch_scope,span))));
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::interpreter::StatementResult>>{
auto&& __jakt_match_variant = result;
switch(__jakt_match_variant.__jakt_init_index()) {
case 3 /* Continue */: {
{
return result;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return result;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Return */: {
{
return result;
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 1 /* Throw */: {
{
return result;
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
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Return */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Return;Jakt::types::Value const& value = __jakt_match_value.value;
{
return Jakt::interpreter::StatementResult::Return(value);
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 4 /* Break */: {
{
return Jakt::interpreter::StatementResult::Break();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* Continue */: {
{
return Jakt::interpreter::StatementResult::Continue();
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 2 /* Yield */: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Invalid control flow"sv)));
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
return JaktInternal::ExplicitValue<Jakt::interpreter::StatementResult>(Jakt::interpreter::StatementResult::JustValue(Jakt::types::Value(Jakt::types::ValueImpl::Void(),span)));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 34 /* Reflect */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reflect;Jakt::ids::TypeId const& type_id = __jakt_match_value.type;
Jakt::utility::Span const& span = __jakt_match_value.span;
return JaktInternal::ExplicitValue(Jakt::interpreter::StatementResult::JustValue(TRY((((*this).reflect_type(type_id,span,scope))))));
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("expression not implemented: {}"sv)),expr),((expr)->span())))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
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

ErrorOr<Jakt::ids::TypeId> Jakt::interpreter::Interpreter::array_type_of_struct(Jakt::ids::StructId const struct_id) {
{
Jakt::ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
NonnullRefPtr<typename Jakt::types::Type> const type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),array_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({((((((*this).program))->get_struct(struct_id))).type_id)}));
return ((*this).find_or_add_type_id(type));
}
}

ErrorOr<Jakt::types::Value> Jakt::interpreter::Interpreter::array_value_of_type(JaktInternal::DynamicArray<Jakt::types::Value> const values,Jakt::ids::TypeId const type,Jakt::utility::Span const span) {
{
Jakt::ids::StructId const array_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Array"sv))))));
NonnullRefPtr<typename Jakt::types::Type> const array_type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),array_struct_id,DynamicArray<Jakt::ids::TypeId>::create_with({type}));
Jakt::ids::TypeId const array_type_id = ((*this).find_or_add_type_id(array_type));
return Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(values,array_type_id),span);
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::interpreter::Interpreter::tuple_type(JaktInternal::DynamicArray<Jakt::ids::TypeId> const members) {
{
Jakt::ids::StructId const tuple_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Tuple"sv))))));
NonnullRefPtr<typename Jakt::types::Type> const type = Jakt::types::Type::GenericInstance(Jakt::parser::CheckedQualifiers(false),tuple_struct_id,members);
return ((*this).find_or_add_type_id(type));
}
}

ErrorOr<Jakt::types::Value> Jakt::interpreter::Interpreter::tuple_value(JaktInternal::DynamicArray<Jakt::types::Value> const members,Jakt::ids::TypeId const type,Jakt::utility::Span const span) {
{
return Jakt::types::Value(Jakt::types::ValueImpl::JaktTuple(members,type),span);
}
}

ErrorOr<Jakt::types::Value> Jakt::interpreter::Interpreter::bool_value(bool const value,Jakt::utility::Span const span) {
{
return Jakt::types::Value(Jakt::types::ValueImpl::Bool(value),span);
}
}

ErrorOr<Jakt::types::Value> Jakt::interpreter::Interpreter::error_value(ByteString const string,Jakt::utility::Span const span) {
{
Jakt::ids::StructId const struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("Error"sv))))));
Jakt::ids::FunctionId const constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(struct_id))).scope_id),(ByteString::from_utf8_without_validation("from_string_literal"sv)),JaktInternal::OptionalNone())))).value());
return Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(string,span))))}),struct_id,constructor),span);
}
}

ErrorOr<Jakt::ids::TypeId> Jakt::interpreter::Interpreter::string_type() {
{
Jakt::ids::StructId const string_struct_id = TRY((((((*this).program))->find_struct_in_prelude((ByteString::from_utf8_without_validation("String"sv))))));
NonnullRefPtr<typename Jakt::types::Type> const type = Jakt::types::Type::Struct(Jakt::parser::CheckedQualifiers(false),string_struct_id);
return ((*this).find_or_add_type_id(type));
}
}

ErrorOr<Jakt::types::Value> Jakt::interpreter::Interpreter::string_value(ByteString const string,Jakt::utility::Span const span) {
{
return Jakt::types::Value(Jakt::types::ValueImpl::JaktString(string),span);
}
}

ErrorOr<ByteString> Jakt::interpreter::Interpreter::string_from_value(Jakt::types::Value const value) {
{
return ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<ByteString>>{
auto&& __jakt_match_variant = *((value).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 13 /* JaktString */: {
auto&& __jakt_match_value = __jakt_match_variant.as.JaktString;ByteString const& x = __jakt_match_value.value;
return JaktInternal::ExplicitValue(x);
};/*case end*/
default: {
{
TRY((((*this).error((ByteString::from_utf8_without_validation("Expected string value"sv)),((value).span)))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
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

ErrorOr<Jakt::types::Value> Jakt::interpreter::Interpreter::reflect_methods(Jakt::ids::ScopeId const scope_id,Jakt::utility::Span const span,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const interpreter_scope) {
{
Jakt::ids::StructId const method_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Method"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Method to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::StructId const function_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Function"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Function to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const method_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(method_struct_id))).scope_id),(ByteString::from_utf8_without_validation("Method"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::FunctionId const function_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(function_struct_id))).scope_id),(ByteString::from_utf8_without_validation("Function"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::TypeId const type_type_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Type"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(((((((*this).program))->get_enum(id))).type_id));
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Type to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> method_values = DynamicArray<Jakt::types::Value>::create_with({});
NonnullRefPtr<Jakt::types::Scope> const scope = ((((*this).program))->get_scope(scope_id));
{
JaktInternal::DictionaryIterator<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> _magic = ((((scope)->functions)).iterator());
for (;;){
JaktInternal::Optional<JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> name__ids__ = (_magic_value.value());
{
JaktInternal::Tuple<ByteString,JaktInternal::DynamicArray<Jakt::ids::FunctionId>> const jakt__name__ids__ = name__ids__;
ByteString const name = ((jakt__name__ids__).template get<0>());
JaktInternal::DynamicArray<Jakt::ids::FunctionId> const ids = ((jakt__name__ids__).template get<1>());

{
JaktInternal::ArrayIterator<Jakt::ids::FunctionId> _magic = ((ids).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::FunctionId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::FunctionId id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedFunction> const function = ((((*this).program))->get_function(id));
Jakt::types::Value const value = Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).array_value_of_type(DynamicArray<Jakt::types::Value>::create_with({}),type_type_id,span)))), TRY((((*this).reflect_type(((function)->return_type_id),span,interpreter_scope)))), TRY((((*this).bool_value(((function)->can_throw),span)))), TRY((((*this).bool_value(((function)->is_comptime),span))))}),function_struct_id,function_struct_constructor),span);
((method_values).push(Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({value}),method_struct_id,method_struct_constructor),span)));
}

}
}

}

}
}

return Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(method_values,TRY((((*this).array_type_of_struct(method_struct_id))))),span);
}
}

ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>> Jakt::interpreter::Interpreter::reflect_fields(JaktInternal::DynamicArray<Jakt::ids::VarId> const fields,Jakt::utility::Span const span,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope) {
{
Jakt::ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const field_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(field_struct_id))).scope_id),(ByteString::from_utf8_without_validation("Field"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::EnumId const visibility_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Visibility"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Visibility to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const visibility_public_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(visibility_enum_id))).scope_id),(ByteString::from_utf8_without_validation("Public"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::FunctionId const visibility_private_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(visibility_enum_id))).scope_id),(ByteString::from_utf8_without_validation("Private"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::StructId const variable_declaration_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("VariableDeclaration"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected VariableDeclaration to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const variable_declaration_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(variable_declaration_struct_id))).scope_id),(ByteString::from_utf8_without_validation("VariableDeclaration"sv)),JaktInternal::OptionalNone())))).value());
JaktInternal::DynamicArray<Jakt::types::Value> record_type_fields = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::ids::VarId> _magic = ((fields).iterator());
for (;;){
JaktInternal::Optional<Jakt::ids::VarId> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::ids::VarId var_id = (_magic_value.value());
{
NonnullRefPtr<Jakt::types::CheckedVariable> const field = ((((*this).program))->get_variable(var_id));
Jakt::types::Value const variable = Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::JaktString(((field)->name)),span), TRY((((*this).reflect_type(((field)->type_id),span,scope)))), Jakt::types::Value(Jakt::types::ValueImpl::Bool(((field)->is_mutable)),span)}),variable_declaration_struct_id,variable_declaration_struct_constructor),span);
Jakt::types::Value const field_value = Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({variable, Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({}),visibility_enum_id,({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::FunctionId, ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>>>{
auto&& __jakt_match_variant = ((field)->visibility);
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Public */: {
return JaktInternal::ExplicitValue(visibility_public_constructor);
};/*case end*/
case 1 /* Private */: {
return JaktInternal::ExplicitValue(visibility_private_constructor);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Not implemented"sv)));
}
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
})),span)}),field_struct_id,field_struct_constructor),span);
((record_type_fields).push(field_value));
}

}
}

return record_type_fields;
}
}

ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>> Jakt::interpreter::Interpreter::reflect_sum_enum_variants(Jakt::types::CheckedEnum const subject_enum,Jakt::utility::Span const span,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope) {
{
Jakt::ids::EnumId const sum_enum_variant_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("SumEnumVariant"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected SumEnumVariant to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const typed_variant_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(sum_enum_variant_enum_id))).scope_id),(ByteString::from_utf8_without_validation("Typed"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::FunctionId const struct_like_variant_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(sum_enum_variant_enum_id))).scope_id),(ByteString::from_utf8_without_validation("StructLike"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::FunctionId const untyped_variant_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(sum_enum_variant_enum_id))).scope_id),(ByteString::from_utf8_without_validation("Untyped"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
JaktInternal::DynamicArray<Jakt::types::Value> result = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedEnumVariant> _magic = ((((subject_enum).variants)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedEnumVariant> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedEnumVariant variant = (_magic_value.value());
{
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<JaktInternal::DynamicArray<Jakt::types::Value>>>{
auto&& __jakt_match_variant = variant;
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Typed */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Typed;ByteString const& name = __jakt_match_value.name;
Jakt::ids::TypeId const& type_id = __jakt_match_value.type_id;
{
Jakt::types::Value const type_value = TRY((((*this).reflect_type(type_id,span,scope))));
Jakt::types::Value const variant_value = Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span)))), type_value}),sum_enum_variant_enum_id,typed_variant_constructor),span);
((result).push(variant_value));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 0 /* Untyped */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Untyped;ByteString const& name = __jakt_match_value.name;
{
Jakt::types::Value const variant_value = Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span))))}),sum_enum_variant_enum_id,untyped_variant_constructor),span);
((result).push(variant_value));
}
return JaktInternal::ExplicitValue<void>();
};/*case end*/
case 3 /* StructLike */: {
auto&& __jakt_match_value = __jakt_match_variant.as.StructLike;ByteString const& name = __jakt_match_value.name;
JaktInternal::DynamicArray<Jakt::ids::VarId> const& fields = __jakt_match_value.fields;
{
JaktInternal::DynamicArray<Jakt::types::Value> const reflected_fields = TRY((((*this).reflect_fields(fields,span,scope))));
Jakt::types::Value const variant_value = Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).array_value_of_type(reflected_fields,TRY((((*this).array_type_of_struct(field_struct_id)))),span))))}),sum_enum_variant_enum_id,struct_like_variant_constructor),span);
((result).push(variant_value));
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

return result;
}
}

ErrorOr<Jakt::types::Value> Jakt::interpreter::Interpreter::reflect_type(Jakt::ids::TypeId const type_id,Jakt::utility::Span const span,NonnullRefPtr<Jakt::interpreter::InterpreterScope> const scope) {
{
Jakt::ids::TypeId const mapped_type_id = ((scope)->map_type(type_id));
if (((((*this).reflected_type_cache)).contains(mapped_type_id))){
return (((((*this).reflected_type_cache)).get(mapped_type_id)).value());
}
((((*this).seen_reflected_types)).add(mapped_type_id));
ScopeGuard __jakt_var_23([&] {
((((*this).seen_reflected_types)).remove(mapped_type_id));
});
NonnullRefPtr<typename Jakt::types::Type> const type = ((((*this).program))->get_type(mapped_type_id));
Jakt::ids::EnumId const reflected_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Type"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Reflect::Type to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::CheckedEnum const reflected_enum = ((((*this).program))->get_enum(reflected_enum_id));
Jakt::types::Value result = Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({}),reflected_enum_id,Jakt::ids::FunctionId(((type_id).module),static_cast<size_t>(0ULL))),span);
((((*this).reflected_type_cache)).set(mapped_type_id,result));
JaktInternal::DynamicArray<Jakt::types::Value> fields = DynamicArray<Jakt::types::Value>::create_with({});
Jakt::ids::FunctionId const found_constructor = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::FunctionId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Void */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 6 /* I8 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 7 /* I16 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 8 /* I32 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 9 /* I64 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 2 /* U8 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 3 /* U16 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 4 /* U32 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 5 /* U64 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 12 /* Usize */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 10 /* F32 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 11 /* F64 */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 13 /* JaktString */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 14 /* CChar */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 15 /* CInt */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 1 /* Bool */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 16 /* Unknown */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 17 /* Never */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),(ByteString::from_utf8_without_validation("TypeVariable"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
(fields = DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span))))}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 26 /* RawPtr */: {
auto&& __jakt_match_value = __jakt_match_variant.as.RawPtr;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
Jakt::ids::FunctionId const constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone())))).value());
(fields = DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).reflect_type(type_id,span,scope))))}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>(constructor);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 28 /* Reference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Reference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
Jakt::ids::FunctionId const constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone())))).value());
(fields = DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).reflect_type(type_id,span,scope))))}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>(constructor);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 29 /* MutableReference */: {
auto&& __jakt_match_value = __jakt_match_variant.as.MutableReference;Jakt::ids::TypeId const& type_id = __jakt_match_value.value;
{
Jakt::ids::FunctionId const constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),((type)->constructor_name()),JaktInternal::OptionalNone())))).value());
(fields = DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).reflect_type(type_id,span,scope))))}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>(constructor);
}
VERIFY_NOT_REACHED();
};/*case end*/
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;Jakt::ids::StructId const& struct_id = __jakt_match_value.id;
{
Jakt::types::CheckedStruct const subject_struct = ((((*this).program))->get_struct(struct_id));
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),(ByteString::from_utf8_without_validation("StructureOrEnum"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
Jakt::ids::StructId const record_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Record"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Record to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const record_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(record_struct_id))).scope_id),(ByteString::from_utf8_without_validation("Record"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::EnumId const record_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("RecordType"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected RecordType to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const record_type_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),(ByteString::from_utf8_without_validation("Struct"sv)),JaktInternal::OptionalNone())))).value());
Jakt::types::Value const methods = TRY((((*this).reflect_methods(((subject_struct).scope_id),span,scope))));
Jakt::ids::TypeId const tuple_type = TRY((((*this).tuple_type(DynamicArray<Jakt::ids::TypeId>::create_with({TRY((((*this).string_type()))), ((reflected_enum).type_id)})))));
Jakt::types::Value const generic_parameters = TRY((((*this).array_value_of_type(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::Value>, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
size_t i = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<Jakt::types::Value> result = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((subject_struct).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((generic_parameter).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Unknown kind of generic parameter in struct definition"sv)));
}
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
Jakt::ids::TypeId const t = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,((args).size())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((args)[i]));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Unknown()));
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
((result).push(TRY((((*this).tuple_value(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).reflect_type(t,span,scope))))}),tuple_type,span))))));
((i) += (static_cast<size_t>(1ULL)));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<Jakt::types::Value>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<Jakt::types::Value>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),tuple_type,span))));
JaktInternal::DynamicArray<Jakt::ids::VarId> reflected_fields = DynamicArray<Jakt::ids::VarId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((subject_struct).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
((reflected_fields).push(((field)->variable_id)));
}

}
}

JaktInternal::DynamicArray<Jakt::types::Value> const record_type_fields = TRY((((*this).reflect_fields(reflected_fields,span,scope))));
Jakt::ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(fields = DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(((subject_struct).name),span)))), methods, generic_parameters, Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(record_type_fields,TRY((((*this).array_type_of_struct(field_struct_id))))),span)}),record_type_enum_id,record_type_struct_constructor),span)}),record_struct_id,record_struct_constructor),span)}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 24 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& struct_id = __jakt_match_value.value;
{
Jakt::types::CheckedStruct const subject_struct = ((((*this).program))->get_struct(struct_id));
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),(ByteString::from_utf8_without_validation("StructureOrEnum"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
Jakt::ids::StructId const record_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Record"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Record to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const record_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(record_struct_id))).scope_id),(ByteString::from_utf8_without_validation("Record"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::EnumId const record_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("RecordType"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected RecordType to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const record_type_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),(ByteString::from_utf8_without_validation("Struct"sv)),JaktInternal::OptionalNone())))).value());
Jakt::types::Value const methods = TRY((((*this).reflect_methods(((subject_struct).scope_id),span,scope))));
Jakt::ids::TypeId const tuple_type = TRY((((*this).tuple_type(DynamicArray<Jakt::ids::TypeId>::create_with({TRY((((*this).string_type()))), ((reflected_enum).type_id)})))));
Jakt::types::Value const generic_parameters = TRY((((*this).array_value_of_type(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::Value>, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
size_t i = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<Jakt::types::Value> result = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((subject_struct).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((generic_parameter).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Unknown kind of generic parameter in struct definition"sv)));
}
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
Jakt::ids::TypeId const t = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,((args).size())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((args)[i]));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Unknown()));
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
((result).push(TRY((((*this).tuple_value(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).reflect_type(t,span,scope))))}),tuple_type,span))))));
((i) += (static_cast<size_t>(1ULL)));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<Jakt::types::Value>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<Jakt::types::Value>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),tuple_type,span))));
JaktInternal::DynamicArray<Jakt::ids::VarId> reflected_fields = DynamicArray<Jakt::ids::VarId>::create_with({});
{
JaktInternal::ArrayIterator<NonnullRefPtr<Jakt::types::CheckedField>> _magic = ((((subject_struct).fields)).iterator());
for (;;){
JaktInternal::Optional<NonnullRefPtr<Jakt::types::CheckedField>> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
NonnullRefPtr<Jakt::types::CheckedField> field = (_magic_value.value());
{
((reflected_fields).push(((field)->variable_id)));
}

}
}

JaktInternal::DynamicArray<Jakt::types::Value> const record_type_fields = TRY((((*this).reflect_fields(reflected_fields,span,scope))));
Jakt::ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(fields = DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(((subject_struct).name),span)))), methods, generic_parameters, Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(record_type_fields,TRY((((*this).array_type_of_struct(field_struct_id))))),span)}),record_type_enum_id,record_type_struct_constructor),span)}),record_struct_id,record_struct_constructor),span)}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 21 /* GenericEnumInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericEnumInstance;Jakt::ids::EnumId const& enum_id = __jakt_match_value.id;
{
Jakt::types::CheckedEnum const subject_enum = ((((*this).program))->get_enum(enum_id));
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),(ByteString::from_utf8_without_validation("StructureOrEnum"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
Jakt::ids::StructId const record_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Record"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Record to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const record_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(record_struct_id))).scope_id),(ByteString::from_utf8_without_validation("Record"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::EnumId const record_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("RecordType"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected RecordType to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool const is_value_enum = ((((subject_enum).underlying_type_id)).equals(Jakt::types::unknown_type_id()));
Jakt::ids::FunctionId const record_type_struct_constructor = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::FunctionId,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_value_enum);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),(ByteString::from_utf8_without_validation("ValueEnum"sv)),JaktInternal::OptionalNone())))).value()));
}
else {
return JaktInternal::ExplicitValue((TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),(ByteString::from_utf8_without_validation("SumEnum"sv)),JaktInternal::OptionalNone())))).value()));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::Value const methods = TRY((((*this).reflect_methods(((subject_enum).scope_id),span,scope))));
Jakt::ids::TypeId const tuple_type = TRY((((*this).tuple_type(DynamicArray<Jakt::ids::TypeId>::create_with({TRY((((*this).string_type()))), ((reflected_enum).type_id)})))));
Jakt::types::Value const generic_parameters = TRY((((*this).array_value_of_type(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::Value>, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
size_t i = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<Jakt::types::Value> result = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((subject_enum).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((generic_parameter).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Unknown kind of generic parameter in struct definition"sv)));
}
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
Jakt::ids::TypeId const t = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,((args).size())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((args)[i]));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Unknown()));
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
((result).push(TRY((((*this).tuple_value(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).reflect_type(t,span,scope))))}),tuple_type,span))))));
((i) += (static_cast<size_t>(1ULL)));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<Jakt::types::Value>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<Jakt::types::Value>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),tuple_type,span))));
JaktInternal::DynamicArray<Jakt::types::Value> record_type_fields = DynamicArray<Jakt::types::Value>::create_with({});
if (is_value_enum){
TRY((((*this).error((ByteString::from_utf8_without_validation("Unimplemented reflected type: value enum"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
else {
(record_type_fields = TRY((((*this).reflect_sum_enum_variants(subject_enum,span,scope)))));
}

Jakt::ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(fields = DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(((subject_enum).name),span)))), methods, generic_parameters, Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).bool_value(((subject_enum).is_boxed),span)))), Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(record_type_fields,TRY((((*this).array_type_of_struct(field_struct_id))))),span)}),record_type_enum_id,record_type_struct_constructor),span)}),record_struct_id,record_struct_constructor),span)}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 25 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& enum_id = __jakt_match_value.value;
{
Jakt::types::CheckedEnum const subject_enum = ((((*this).program))->get_enum(enum_id));
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),(ByteString::from_utf8_without_validation("StructureOrEnum"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
Jakt::ids::StructId const record_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Record"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Record to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::ids::FunctionId const record_struct_constructor = (TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_struct(record_struct_id))).scope_id),(ByteString::from_utf8_without_validation("Record"sv)),JaktInternal::OptionalNone())))).value());
Jakt::ids::EnumId const record_type_enum_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::EnumId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("RecordType"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 1 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;Jakt::ids::EnumId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected RecordType to be an enum"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
bool const is_value_enum = ((((subject_enum).underlying_type_id)).equals(Jakt::types::unknown_type_id()));
Jakt::ids::FunctionId const record_type_struct_constructor = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::FunctionId,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = (is_value_enum);
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue((TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),(ByteString::from_utf8_without_validation("ValueEnum"sv)),JaktInternal::OptionalNone())))).value()));
}
else {
return JaktInternal::ExplicitValue((TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(record_type_enum_id))).scope_id),(ByteString::from_utf8_without_validation("SumEnum"sv)),JaktInternal::OptionalNone())))).value()));
}
}());
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
Jakt::types::Value const methods = TRY((((*this).reflect_methods(((subject_enum).scope_id),span,scope))));
Jakt::ids::TypeId const tuple_type = TRY((((*this).tuple_type(DynamicArray<Jakt::ids::TypeId>::create_with({TRY((((*this).string_type()))), ((reflected_enum).type_id)})))));
Jakt::types::Value const generic_parameters = TRY((((*this).array_value_of_type(({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<JaktInternal::DynamicArray<Jakt::types::Value>, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *type;
switch(__jakt_match_variant.__jakt_init_index()) {
case 20 /* GenericInstance */: {
auto&& __jakt_match_value = __jakt_match_variant.as.GenericInstance;JaktInternal::DynamicArray<Jakt::ids::TypeId> const& args = __jakt_match_value.args;
{
size_t i = static_cast<size_t>(0ULL);
JaktInternal::DynamicArray<Jakt::types::Value> result = DynamicArray<Jakt::types::Value>::create_with({});
{
JaktInternal::ArrayIterator<Jakt::types::CheckedGenericParameter> _magic = ((((subject_enum).generic_parameters)).iterator());
for (;;){
JaktInternal::Optional<Jakt::types::CheckedGenericParameter> const _magic_value = ((_magic).next());
if ((!(((_magic_value).has_value())))){
break;
}
Jakt::types::CheckedGenericParameter generic_parameter = (_magic_value.value());
{
ByteString const name = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<ByteString, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((((*this).program))->get_type(((generic_parameter).type_id)));
switch(__jakt_match_variant.__jakt_init_index()) {
case 18 /* TypeVariable */: {
auto&& __jakt_match_value = __jakt_match_variant.as.TypeVariable;ByteString const& name = __jakt_match_value.name;
return JaktInternal::ExplicitValue(name);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Unknown kind of generic parameter in struct definition"sv)));
}
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
Jakt::ids::TypeId const t = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::TypeId,ErrorOr<Jakt::types::Value>> {
auto __jakt_enum_value = ([](size_t const& self, size_t rhs) -> bool {{
return (((infallible_integer_cast<u8>(([](size_t const& self, size_t rhs) -> Jakt::jakt__prelude__operators::Ordering {{
return (infallible_enum_cast<Jakt::jakt__prelude__operators::Ordering>((JaktInternal::compare(self,rhs))));
}
}
(self,rhs))))) == (static_cast<u8>(0)));
}
}
(i,((args).size())));
if (__jakt_enum_value == true) {
return JaktInternal::ExplicitValue(((args)[i]));
}
else if (__jakt_enum_value == false) {
return JaktInternal::ExplicitValue(Jakt::types::builtin(Jakt::types::BuiltinType::Unknown()));
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
((result).push(TRY((((*this).tuple_value(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(name,span)))), TRY((((*this).reflect_type(t,span,scope))))}),tuple_type,span))))));
((i) += (static_cast<size_t>(1ULL)));
}

}
}

return JaktInternal::ExplicitValue<JaktInternal::DynamicArray<Jakt::types::Value>>(result);
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
return JaktInternal::ExplicitValue(DynamicArray<Jakt::types::Value>::create_with({}));
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
}),tuple_type,span))));
JaktInternal::DynamicArray<Jakt::types::Value> record_type_fields = DynamicArray<Jakt::types::Value>::create_with({});
if (is_value_enum){
TRY((((*this).error((ByteString::from_utf8_without_validation("Unimplemented reflected type: value enum"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
else {
(record_type_fields = TRY((((*this).reflect_sum_enum_variants(subject_enum,span,scope)))));
}

Jakt::ids::StructId const field_struct_id = ({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<Jakt::ids::StructId, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = TRY((((((*this).program))->find_reflected_primitive((ByteString::from_utf8_without_validation("Field"sv))))));
switch(__jakt_match_variant.__jakt_init_index()) {
case 0 /* Struct */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Struct;Jakt::ids::StructId const& id = __jakt_match_value.value;
return JaktInternal::ExplicitValue(id);
};/*case end*/
default: {
{
Jakt::utility::panic((ByteString::from_utf8_without_validation("Expected Field to be a struct"sv)));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
(fields = DynamicArray<Jakt::types::Value>::create_with({Jakt::types::Value(Jakt::types::ValueImpl::Struct(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).string_value(((subject_enum).name),span)))), methods, generic_parameters, Jakt::types::Value(Jakt::types::ValueImpl::Enum(DynamicArray<Jakt::types::Value>::create_with({TRY((((*this).bool_value(((subject_enum).is_boxed),span)))), Jakt::types::Value(Jakt::types::ValueImpl::JaktArray(record_type_fields,TRY((((*this).array_type_of_struct(field_struct_id))))),span)}),record_type_enum_id,record_type_struct_constructor),span)}),record_struct_id,record_struct_constructor),span)}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
case 30 /* Function */: {
{
JaktInternal::Optional<Jakt::ids::FunctionId> const constructor = TRY((((((*this).program))->find_function_in_scope(((((((*this).program))->get_enum(reflected_enum_id))).scope_id),(ByteString::from_utf8_without_validation("Function"sv)),JaktInternal::OptionalNone()))));
if ((!(((constructor).has_value())))){
TRY((((*this).error((ByteString::from_utf8_without_validation("Attempted to access a variant that does not exist"sv)),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Invalid type"sv))));
}
(fields = DynamicArray<Jakt::types::Value>::create_with({}));
return JaktInternal::ExplicitValue<Jakt::ids::FunctionId>((constructor.value()));
}
VERIFY_NOT_REACHED();
};/*case end*/
default: {
{
TRY((((*this).error(__jakt_format((StringView::from_string_literal("Type reflection not implemented: {}"sv)),type),span))));
((((*this).compiler))->panic((ByteString::from_utf8_without_validation("Not yet implemented"sv))));
}
};/*case end*/
}/*switch end*/
}()
);
    if (_jakt_value.is_return())
        return _jakt_value.release_return();
    _jakt_value.release_value();
});
({
    auto&& _jakt_value = ([&]() -> JaktInternal::ExplicitValueOrControlFlow<void, ErrorOr<Jakt::types::Value>>{
auto&& __jakt_match_variant = *((result).impl);
switch(__jakt_match_variant.__jakt_init_index()) {
case 19 /* Enum */: {
auto&& __jakt_match_value = __jakt_match_variant.as.Enum;JaktInternal::DynamicArray<Jakt::types::Value>& x = __jakt_match_value.fields;
Jakt::ids::FunctionId& constructor = __jakt_match_value.constructor;
{
(constructor = found_constructor);
(x = fields);
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
return result;
}
}

Jakt::interpreter::Interpreter::Interpreter(NonnullRefPtr<Jakt::compiler::Compiler> a_compiler, NonnullRefPtr<Jakt::types::CheckedProgram> a_program, JaktInternal::DynamicArray<Jakt::utility::Span> a_spans, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::types::Value> a_reflected_type_cache, JaktInternal::Set<Jakt::ids::TypeId> a_seen_reflected_types, JaktInternal::Optional<Jakt::ids::FunctionId> a_current_function_id, NonnullRefPtr<Jakt::types::TypecheckFunctions> a_typecheck_functions): compiler(move(a_compiler)), program(move(a_program)), spans(move(a_spans)), reflected_type_cache(move(a_reflected_type_cache)), seen_reflected_types(move(a_seen_reflected_types)), current_function_id(move(a_current_function_id)), typecheck_functions(move(a_typecheck_functions)){}
NonnullRefPtr<Interpreter> Jakt::interpreter::Interpreter::__jakt_create(NonnullRefPtr<Jakt::compiler::Compiler> compiler, NonnullRefPtr<Jakt::types::CheckedProgram> program, JaktInternal::DynamicArray<Jakt::utility::Span> spans, JaktInternal::Dictionary<Jakt::ids::TypeId,Jakt::types::Value> reflected_type_cache, JaktInternal::Set<Jakt::ids::TypeId> seen_reflected_types, JaktInternal::Optional<Jakt::ids::FunctionId> current_function_id, NonnullRefPtr<Jakt::types::TypecheckFunctions> typecheck_functions) { auto o = adopt_ref(*new Interpreter (move(compiler), move(program), move(spans), move(reflected_type_cache), move(seen_reflected_types), move(current_function_id), move(typecheck_functions))); return o; }
ByteString Jakt::interpreter::Deferred::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Expression */: {
builder.append("Deferred::Expression"sv);
[[maybe_unused]] auto const& that = this->as.Expression;
builder.appendff("({})", that.value);
break;}
case 1 /* Statement */: {
builder.append("Deferred::Statement"sv);
[[maybe_unused]] auto const& that = this->as.Statement;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] Deferred Deferred::Expression(NonnullRefPtr<typename Jakt::types::CheckedExpression> value){
Deferred __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Expression.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] Deferred Deferred::Statement(NonnullRefPtr<typename Jakt::types::CheckedStatement> value){
Deferred __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Statement.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
Deferred& Deferred::operator=(Deferred const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(rhs.as.Expression.value);
break;
case 1 /* Statement */:
new (&this->as.Statement.value) (decltype(this->as.Statement.value))(rhs.as.Statement.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.value = rhs.as.Expression.value;
break;
case 1 /* Statement */:
this->as.Statement.value = rhs.as.Statement.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Deferred::Deferred(Deferred const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(rhs.as.Expression.value);
break;
case 1 /* Statement */:
new (&this->as.Statement.value) (decltype(this->as.Statement.value))(rhs.as.Statement.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
Deferred& Deferred::operator=(Deferred &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(move(rhs.as.Expression.value));
break;
case 1 /* Statement */:
new (&this->as.Statement.value) (decltype(this->as.Statement.value))(move(rhs.as.Statement.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
this->as.Expression.value = move(rhs.as.Expression.value);
break;
case 1 /* Statement */:
this->as.Statement.value = move(rhs.as.Statement.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
Deferred::Deferred(Deferred &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Expression */:
new (&this->as.Expression.value) (decltype(this->as.Expression.value))(move(rhs.as.Expression.value));
break;
case 1 /* Statement */:
new (&this->as.Statement.value) (decltype(this->as.Statement.value))(move(rhs.as.Statement.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
Deferred::~Deferred(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void Deferred::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Expression */:this->as.Expression.value.~NonnullRefPtr();
break;
case 1 /* Statement */:this->as.Statement.value.~NonnullRefPtr();
break;
}
}
ByteString Jakt::interpreter::ExecutionResult::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Return */: {
builder.append("ExecutionResult::Return"sv);
[[maybe_unused]] auto const& that = this->as.Return;
builder.appendff("({})", that.value);
break;}
case 1 /* Throw */: {
builder.append("ExecutionResult::Throw"sv);
[[maybe_unused]] auto const& that = this->as.Throw;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] ExecutionResult ExecutionResult::Return(Jakt::types::Value value){
ExecutionResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Return.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] ExecutionResult ExecutionResult::Throw(Jakt::types::Value value){
ExecutionResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Throw.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
ExecutionResult& ExecutionResult::operator=(ExecutionResult const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(rhs.as.Return.value);
break;
case 1 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(rhs.as.Throw.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
this->as.Return.value = rhs.as.Return.value;
break;
case 1 /* Throw */:
this->as.Throw.value = rhs.as.Throw.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ExecutionResult::ExecutionResult(ExecutionResult const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(rhs.as.Return.value);
break;
case 1 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(rhs.as.Throw.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
ExecutionResult& ExecutionResult::operator=(ExecutionResult &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(move(rhs.as.Return.value));
break;
case 1 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(move(rhs.as.Throw.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
this->as.Return.value = move(rhs.as.Return.value);
break;
case 1 /* Throw */:
this->as.Throw.value = move(rhs.as.Throw.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
ExecutionResult::ExecutionResult(ExecutionResult &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(move(rhs.as.Return.value));
break;
case 1 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(move(rhs.as.Throw.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
ExecutionResult::~ExecutionResult(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void ExecutionResult::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Return */:this->as.Return.value.~Value();
break;
case 1 /* Throw */:this->as.Throw.value.~Value();
break;
}
}
ByteString Jakt::interpreter::StatementResult::debug_description() const {
auto builder = ByteStringBuilder::create();
switch (this->__jakt_init_index()) {case 0 /* Return */: {
builder.append("StatementResult::Return"sv);
[[maybe_unused]] auto const& that = this->as.Return;
builder.appendff("({})", that.value);
break;}
case 1 /* Throw */: {
builder.append("StatementResult::Throw"sv);
[[maybe_unused]] auto const& that = this->as.Throw;
builder.appendff("({})", that.value);
break;}
case 2 /* Yield */: {
builder.append("StatementResult::Yield"sv);
[[maybe_unused]] auto const& that = this->as.Yield;
builder.appendff("({})", that.value);
break;}
case 3 /* Continue */: {
return ByteString("StatementResult::Continue"sv);
break;}
case 4 /* Break */: {
return ByteString("StatementResult::Break"sv);
break;}
case 5 /* JustValue */: {
builder.append("StatementResult::JustValue"sv);
[[maybe_unused]] auto const& that = this->as.JustValue;
builder.appendff("({})", that.value);
break;}
}
return builder.to_string();
}
[[nodiscard]] StatementResult StatementResult::Return(Jakt::types::Value value){
StatementResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 1;
new (&__jakt_uninit_enum.as.Return.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StatementResult StatementResult::Throw(Jakt::types::Value value){
StatementResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 2;
new (&__jakt_uninit_enum.as.Throw.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StatementResult StatementResult::Yield(Jakt::types::Value value){
StatementResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 3;
new (&__jakt_uninit_enum.as.Yield.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
[[nodiscard]] StatementResult StatementResult::Continue(){
StatementResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 4;
return __jakt_uninit_enum;
}
[[nodiscard]] StatementResult StatementResult::Break(){
StatementResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 5;
return __jakt_uninit_enum;
}
[[nodiscard]] StatementResult StatementResult::JustValue(Jakt::types::Value value){
StatementResult __jakt_uninit_enum;
__jakt_uninit_enum.__jakt_variant_index = 6;
new (&__jakt_uninit_enum.as.JustValue.value) (decltype(value))(move(value));
return __jakt_uninit_enum;
}
StatementResult& StatementResult::operator=(StatementResult const &rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(rhs.as.Return.value);
break;
case 1 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(rhs.as.Throw.value);
break;
case 2 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(rhs.as.Yield.value);
break;
case 3 /* Continue */:
break;
case 4 /* Break */:
break;
case 5 /* JustValue */:
new (&this->as.JustValue.value) (decltype(this->as.JustValue.value))(rhs.as.JustValue.value);
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
this->as.Return.value = rhs.as.Return.value;
break;
case 1 /* Throw */:
this->as.Throw.value = rhs.as.Throw.value;
break;
case 2 /* Yield */:
this->as.Yield.value = rhs.as.Yield.value;
break;
case 3 /* Continue */:
break;
case 4 /* Break */:
break;
case 5 /* JustValue */:
this->as.JustValue.value = rhs.as.JustValue.value;
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
StatementResult::StatementResult(StatementResult const &rhs){VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(rhs.as.Return.value);
break;
case 1 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(rhs.as.Throw.value);
break;
case 2 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(rhs.as.Yield.value);
break;
case 3 /* Continue */:
break;
case 4 /* Break */:
break;
case 5 /* JustValue */:
new (&this->as.JustValue.value) (decltype(this->as.JustValue.value))(rhs.as.JustValue.value);
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
StatementResult& StatementResult::operator=(StatementResult &&rhs){
{VERIFY(this->__jakt_variant_index != 0 && rhs.__jakt_variant_index != 0);
if (this->__jakt_variant_index != rhs.__jakt_variant_index) {
this->__jakt_destroy_variant();
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(move(rhs.as.Return.value));
break;
case 1 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(move(rhs.as.Throw.value));
break;
case 2 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(move(rhs.as.Yield.value));
break;
case 3 /* Continue */:
break;
case 4 /* Break */:
break;
case 5 /* JustValue */:
new (&this->as.JustValue.value) (decltype(this->as.JustValue.value))(move(rhs.as.JustValue.value));
break;
}
} else {
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
this->as.Return.value = move(rhs.as.Return.value);
break;
case 1 /* Throw */:
this->as.Throw.value = move(rhs.as.Throw.value);
break;
case 2 /* Yield */:
this->as.Yield.value = move(rhs.as.Yield.value);
break;
case 3 /* Continue */:
break;
case 4 /* Break */:
break;
case 5 /* JustValue */:
this->as.JustValue.value = move(rhs.as.JustValue.value);
break;
}
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
return *this;
}
StatementResult::StatementResult(StatementResult &&rhs){
{VERIFY(rhs.__jakt_variant_index != 0);
switch (rhs.__jakt_init_index()) {
case 0 /* Return */:
new (&this->as.Return.value) (decltype(this->as.Return.value))(move(rhs.as.Return.value));
break;
case 1 /* Throw */:
new (&this->as.Throw.value) (decltype(this->as.Throw.value))(move(rhs.as.Throw.value));
break;
case 2 /* Yield */:
new (&this->as.Yield.value) (decltype(this->as.Yield.value))(move(rhs.as.Yield.value));
break;
case 3 /* Continue */:
break;
case 4 /* Break */:
break;
case 5 /* JustValue */:
new (&this->as.JustValue.value) (decltype(this->as.JustValue.value))(move(rhs.as.JustValue.value));
break;
}
this->__jakt_variant_index = rhs.__jakt_variant_index;
}
}
StatementResult::~StatementResult(){ if (this->__jakt_variant_index == 0) return;
this->__jakt_destroy_variant(); }
void StatementResult::__jakt_destroy_variant() {
switch (this->__jakt_init_index()) {
case 0 /* Return */:this->as.Return.value.~Value();
break;
case 1 /* Throw */:this->as.Throw.value.~Value();
break;
case 2 /* Yield */:this->as.Yield.value.~Value();
break;
case 3 /* Continue */:break;
case 4 /* Break */:break;
case 5 /* JustValue */:this->as.JustValue.value.~Value();
break;
}
}
}
} // namespace Jakt
